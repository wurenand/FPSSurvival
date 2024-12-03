
#include "Actor/WeaponBase.h"

#include "Character/SurvivalPlayerCharacter.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetRootComponent(WeaponMesh);
	SetReplicates(true);
}

void AWeaponBase::EquipWeapon(ASurvivalPlayerCharacter* InCharacter)
{
	RootComponent->AttachToComponent(InCharacter->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,SnapSocketName);
}


