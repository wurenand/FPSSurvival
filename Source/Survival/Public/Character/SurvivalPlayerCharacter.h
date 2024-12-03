// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalCharacterBase.h"
#include "Interface/HandleInputInterface.h"
#include "SurvivalPlayerCharacter.generated.h"

class UAbilityComponent;
class USpringArmComponent;
class UCameraComponent;
class AWeaponBase;

UCLASS()
class SURVIVAL_API ASurvivalPlayerCharacter : public ASurvivalCharacterBase, public IHandleInputInterface
{
	GENERATED_BODY()

public:
	ASurvivalPlayerCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	//~Begin InputComponent
	virtual void HandleInputMove(const FInputActionValue& Value) override;
	virtual void HandleInputLook(const FInputActionValue& Value) override;
	virtual void HandleInputShoot(const FInputActionValue& Value) override;
	//~End InputComponent

	virtual void BeginPlay() override;
	//TODO:
	//在Server端调用，用于获得PS中的Component
	virtual void PossessedBy(AController* NewController) override;
	//在Client端调用，用于获得PS中的Component
	virtual void OnRep_PlayerState() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	//第三人称Mesh，为了解决隐藏第一人称头部导致的阴影消失问题，只做显示阴影使用！
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Mesh")
	TObjectPtr<USkeletalMeshComponent> ThirdPersonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,ReplicatedUsing = OnRep_Weapon,Category="Weapon")
	TObjectPtr<AWeaponBase> Weapon;
	UFUNCTION()
	void OnRep_Weapon();
	
	//从PS中获得 自己不构造
	UPROPERTY()
	TObjectPtr<UAbilityComponent> AbilityComponent;
	//得到AbilityComponent后的初始化
	void InitializeAbilityComponent();
};

