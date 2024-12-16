// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectiles/ProjectileRocket.h"

#include "Character/SurvivalCharacterBase.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SurvivalPlayerController.h"


class ICombatInterface;
class ASurvivalPlayerController;

void AProjectileRocket::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	//Spawn命中特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, ProjectileMesh->GetComponentLocation());
	//造成伤害
	if (HasAuthority())
	{
		TArray<AActor*> OverlappedCharacters;
		UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), Radius,
		                                          TArray<TEnumAsByte<EObjectTypeQuery>>(),
		                                          ASurvivalCharacterBase::StaticClass(), TArray<AActor*>(),
		                                          OverlappedCharacters);
		bool bMakeDamage = false;
		for (auto Character : OverlappedCharacters)
		{
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Character))
			{
				if (CombatInterface->GetCharacterTeam() != Cast<ASurvivalCharacterBase>(GetInstigator())->
					GetCharacterTeam())
				{
					CombatInterface->CombatTakeDamage(Cast<ASurvivalCharacterBase>(GetInstigator()), Damage);
					bMakeDamage = true;
				}
			}
		}
		//通知开火者成功命中
		if (bMakeDamage)
		{
			if (ASurvivalPlayerController* SurvivalPlayerController = Cast<ASurvivalPlayerController>(
				GetInstigator()->GetController()))
			{
				SurvivalPlayerController->CL_AttackHit();
			}
		}
		Destroy();
	}
}
