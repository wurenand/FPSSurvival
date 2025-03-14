#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "SurvivalEnemyCharacter.generated.h"

class AAIPatrolPathSpline;

UCLASS()
class SURVIVAL_API ASurvivalEnemyCharacter : public ASurvivalCharacterBase
{
	GENERATED_BODY()

public:
	ASurvivalEnemyCharacter();
	virtual void BeginPlay() override;

	//如果有的话，则会按照设定路线巡逻，否则随机(BTTask_Route)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemyAttack")
	TObjectPtr<AAIPatrolPathSpline> PatrolPathSpline;

	virtual void InitializeCharacter() override;
	
	//~Begin ICombatInterface
	virtual ETeam GetCharacterTeam() override;
	virtual void CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue) override;
	//~End ICombatInterface

	//用于RPC到所有客户端播放攻击动画
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable)
	void Mult_PlayMontage(UAnimMontage* MontageToPlay);
	//~Begin ForAnimInstance(MontageNotify)
	void Notify_SetEnableAttackCheck(bool bIsEnable);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemyAttack")
	TObjectPtr<UCapsuleComponent> AttackCapsule;
	//TODO:后续使用一个DataTable统一进行管理，包括Level，对应的HP，Damage，AttackMontage等。暂时先这样

	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);
};