#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectileBase;
class ASurvivalPlayerCharacter;

/**
 * 武器的信息，包括基础伤害，换弹药速度，弹夹量。音效，蒙太奇等..
 */
USTRUCT(BlueprintType, Blueprintable)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FName WeaponName;
	UPROPERTY(EditAnywhere)
	float BaseDamage = 0;
	UPROPERTY(EditAnywhere)
	float BaseMagCount = 0;
	UPROPERTY(EditAnywhere)
	float BaseShootingSpeed = 1.0f;
	UPROPERTY(EditAnywhere)
	float BulletSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> BulletClass;
	UPROPERTY(EditAnywhere)
	FName MagBoneName;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ShootMontage = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ReloadMontage = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> ShootingSFX = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> ShootingParticle = nullptr;
};

UCLASS()
class SURVIVAL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	void EquipWeapon(ASurvivalPlayerCharacter* InCharacter);

	//处理开火时的音效和特效
	void HandleShootEffect();
	
	//用于从数据表中获得信息
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	FName WeaponName;
	FWeaponInfo WeaponInfo;

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; };

protected:
	void SpawnShootParticle();
	void SpawnShootSound();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName SnapSocketName = "S_Rifle";
};
