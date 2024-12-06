
#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "SurvivalEnemyCharacter.generated.h"

UCLASS()
class SURVIVAL_API ASurvivalEnemyCharacter : public ASurvivalCharacterBase
{
	GENERATED_BODY()

public:
	ASurvivalEnemyCharacter();
	
	//~Begin ICombatInterface
	virtual ETeam GetCharacterTeam() override;
	virtual void CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue) override;
	//~End ICombatInterface
};
