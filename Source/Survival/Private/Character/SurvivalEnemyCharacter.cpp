
#include "Character/SurvivalEnemyCharacter.h"

ASurvivalEnemyCharacter::ASurvivalEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
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
		Destroy();
		//TODO:这里AI死亡，可以增加Player的击杀数，播放Montage等
	}
}

