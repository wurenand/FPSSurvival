
#include "Character/SurvivalEnemyCharacter.h"

ASurvivalEnemyCharacter::ASurvivalEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

ETeam ASurvivalEnemyCharacter::GetCharacterTeam()
{
	return Team;
}

