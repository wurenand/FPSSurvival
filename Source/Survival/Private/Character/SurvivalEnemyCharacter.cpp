#include "Character/SurvivalEnemyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Game/SurvivalGameMode.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalEnemyCharacter::ASurvivalEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Team = ETeam::ETeam_Enemy;

	//Attack
	AttackCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AttackCapsule"));
	AttackCapsule->SetupAttachment(GetRootComponent());
	AttackCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackCapsule->SetCollisionResponseToAllChannels(ECR_Overlap);
	AttackCapsule->SetCollisionObjectType(ECC_Ability); //设置为ECC_Ability
	AttackCapsule->SetCollisionResponseToChannel(ECC_Ability, ECR_Ignore);
	AttackCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASurvivalEnemyCharacter::OnAttackBeginOverlap);
}


void ASurvivalEnemyCharacter::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                   bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(OtherActor))
		{
			if (CombatInterface->GetCharacterTeam() != GetCharacterTeam())
			{
				CombatInterface->CombatTakeDamage(this, 10.f);
			}
		}
	}
}


ETeam ASurvivalEnemyCharacter::GetCharacterTeam()
{
	return Team;
}

void ASurvivalEnemyCharacter::CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue)
{
	Super::CombatTakeDamage(DamageInstigator, DamageValue);
	Health -= DamageValue;
	if (Health <= 0)
	{
		if (ASurvivalGameMode* SurvivalGameMode = Cast<ASurvivalGameMode>(GetWorld()->GetAuthGameMode()))
		{
			ASurvivalPlayerController* Attacker = Cast<ASurvivalPlayerController>(DamageInstigator->GetController());
			SurvivalGameMode->EnemyEliminated(this, Attacker);
		}
	}
}

void ASurvivalEnemyCharacter::Notify_SetEnableAttackCheck(bool bIsEnable)
{
	ECollisionEnabled::Type EnabledType = bIsEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
	AttackCapsule->SetCollisionEnabled(EnabledType);
}

void ASurvivalEnemyCharacter::Mult_EnemyAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
}