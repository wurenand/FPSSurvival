// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInformHUDSignature,float, Value);

/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	//通知当前的HUD切换显示页面
	UFUNCTION(Client, Reliable)
	void ChangeOverlayPage(FName PageName);
	UFUNCTION(Client,Unreliable)
	void CL_AttackHit();

	//~Begin HUD Delegates
	UPROPERTY(BlueprintAssignable)
	FInformHUDSignature OnAttackHitDelegate;//攻击成功命中 Value无意义
	//~End HUD Delegates

protected:
	virtual void SetupInputComponent() override;
	
	UFUNCTION(Server,Unreliable)
	void SRV_UpdateAimDirection();
	
	//~Begin Input
	void ForwardInputMove(const FInputActionValue& Value);
	void ForwardInputLook(const FInputActionValue& Value);
	void ForwardInputShootTriggered(const FInputActionValue& Value);
	void ForwardInputShootCompleted(const FInputActionValue& Value);
	void ForwardInputReload(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionMove;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionLook;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionShoot;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ActionReload;
	//~End Input
};
