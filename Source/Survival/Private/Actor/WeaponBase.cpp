#include "Actor/WeaponBase.h"

#include "Character/SurvivalPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetRootComponent(WeaponMesh);
	bReplicates = true;
}

void AWeaponBase::EquipWeapon(ASurvivalPlayerCharacter* InCharacter)
{
	RootComponent->AttachToComponent(InCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                                 SnapSocketName);
	if (WeaponInfo.ReloadMontage)
	{
		InCharacter->PlayAnimMontage(WeaponInfo.ReloadMontage,1,TEXT("EquipStart"));
	}
}

void AWeaponBase::HandleShootEffect()
{
	SpawnShootParticle();
	SpawnShootSound();
}

void AWeaponBase::SpawnShootParticle()
{
	if (!WeaponInfo.ShootingParticle)
	{
		return;
	}
	UGameplayStatics::SpawnEmitterAttached(WeaponInfo.ShootingParticle,GetWeaponMesh(),TEXT("S_Muzzle"));
}

void AWeaponBase::SpawnShootSound()
{
	if (!WeaponInfo.ShootingSFX)
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(this,WeaponInfo.ShootingSFX,GetActorLocation());
}
