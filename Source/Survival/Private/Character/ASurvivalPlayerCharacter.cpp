// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASurvivalPlayerCharacter.h"

#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AASurvivalPlayerCharacter::AASurvivalPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true; //让摄像机与Pawn相同旋转
	SpringArm->TargetArmLength = 0;
	SpringArm->SetupAttachment(GetMesh(),FName(TEXT("S_Camera")));
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//第三人称Mesh，只用作显示影子使用！不能处理任何碰撞等..
	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonMesh"));
	ThirdPersonMesh->SetupAttachment(GetMesh());
	ThirdPersonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ThirdPersonMesh->SetHiddenInGame(true);
	ThirdPersonMesh->SetCastHiddenShadow(true);//打开隐藏阴影，即使HideInGame也能投射Shadow
}

void AASurvivalPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//隐藏Mesh头部，避免遮挡射线机
	if (IsLocallyControlled())
	{
		GetMesh()->HideBoneByName(FName(TEXT("head")), PBO_None);
	}
}


void AASurvivalPlayerCharacter::HandleInputMove(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MoveVector.X);
		AddMovementInput(GetActorRightVector(), MoveVector.Y);
	}
}

void AASurvivalPlayerCharacter::HandleInputLook(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-LookVector.Y);
	}
}

void AASurvivalPlayerCharacter::HandleInputShoot(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("AASurvivalPlayerCharacter : TRY SHOOT"));
}
