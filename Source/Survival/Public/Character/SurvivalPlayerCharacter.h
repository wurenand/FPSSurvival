// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "Interface/HandleInputInterface.h"
#include "SurvivalPlayerCharacter.generated.h"

class UPlayMontageCallbackProxy;
class UAbilityComponent;
class USpringArmComponent;
class UCameraComponent;
class AWeaponBase;

UCLASS()
class SURVIVAL_API ASurvivalPlayerCharacter : public ASurvivalCharacterBase, public IHandleInputInterface
{
	GENERATED_BODY()

	friend class UAbilityComponent;

public:
	ASurvivalPlayerCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//~Begin InputComponent
	virtual void HandleInputMove(const FInputActionValue& Value) override;
	virtual void HandleInputLook(const FInputActionValue& Value) override;
	virtual void HandleInputJump(const FInputActionValue& Value) override;
	virtual void HandleInputTagInputTriggered(FGameplayTag InputTag) override;
	//~End InputComponent


	//~Begin ICombatInterface
	virtual ETeam GetCharacterTeam() override;
	virtual void CombatTakeDamage(ASurvivalCharacterBase* DamageInstigator, float DamageValue) override;
	//~End ICombatInterface

	virtual void SetPendingDeath(bool bQuickDestroy = false) override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//TODO:
	//在Server端调用，用于获得PS中的Component
	virtual void PossessedBy(AController* NewController) override;
	//在Client端调用，用于获得PS中的Component
	virtual void OnRep_PlayerState() override;

	//~Begin Delegate
	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnMagCountChanged;
	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnMaxMagCountChanged;
	//广播当前玩家准心是否对准了敌人 1为true 0为false
	UPROPERTY(BlueprintAssignable)
	FOnCharacterValueChangedSignature OnIsAimingEnemyChanged;
	//~End Delegate

	//AnimInstance
	UPROPERTY(Replicated)
	float AimDirection;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	//第三人称Mesh，为了解决隐藏第一人称头部导致的阴影消失问题，只做显示阴影使用！
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Mesh")
	TObjectPtr<USkeletalMeshComponent> ThirdPersonMesh;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;

	//得到AbilityComponent后的初始化  负责Weapon，HUD Params，AbilityComponent的初始化
	virtual void InitializeCharacter() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Weapon, Category="Weapon")
	TObjectPtr<AWeaponBase> Weapon;
	UFUNCTION()
	void OnRep_Weapon();

	
	void BindAttributeDelegatesFromSet();

	//~Begin Shoot相关逻辑
	UPROPERTY(Replicated, BlueprintReadOnly, Category="Shoot")
	bool bIsReloading = false;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Shoot")
	bool bIsShooting = false;
	FTimerHandle ShootTimer;
	
	UFUNCTION(Server, Reliable, Category= "Shoot")
	void SRV_ShootWeapon(bool bShouldShooting, FVector LocalAimTargetPoint);
	//多播，负责处理蒙太奇，音效，特效
	UFUNCTION(NetMulticast, Reliable, Category = "Shoot")
	void Mult_ShootWeaponEffect(FVector Location);
	void ShootWeaponLoop();

	UFUNCTION(Server, Reliable, Category ="Reload")
	void SRV_ReloadWeapon();
	UFUNCTION(NetMulticast, Reliable, Category ="Reload")
	void Mult_ReloadWeaponEffect();
	//加上UProperty用于GC
	UPROPERTY()
	TObjectPtr<UPlayMontageCallbackProxy> ReloadMontageProxy;
	//~End Shoot

	//~Begin Aim
	//Tick检测是否瞄准了目标，用于Broadcast给UI变红
	void HitTraceTick(float DeltaSeconds);
	FHitResult HitTraceResult;
	float HitTickFrequency = 0.1f;
	float HitTickCount = 0.f;
	//记录玩家瞄准的位置
	FVector AimTargetPoint;
	UPROPERTY(EditAnywhere)
	float AimLength = 3000.f;
	//~End

	//~Begin Death
	//这里重写只是为了隐藏掉第三人称Mesh的模型
	virtual void Mult_DeathEffect_Implementation() override;
	//~End Death

	//~Begin Montage Callback
	UFUNCTION()
	void OnReceiveMontageNotifyBegin(FName NotifyName);
	UFUNCTION()
	void OnReceiveMontageCompleted(FName NotifyName);
	//~End
};
