
#include "Character/SurvivalEnemyCharacter.h"

#include "Game/SurvivalGameMode.h"
#include "Player/SurvivalPlayerController.h"

ASurvivalEnemyCharacter::ASurvivalEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Team = ETeam::ETeam_Enemy;
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
			SurvivalGameMode->EnemyEliminated(this,Attacker);
		}
	}
}

