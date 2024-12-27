// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CollisionInteract/CollisionInteractActorBase.h"

#include "Components/SphereComponent.h"
#include "Survival/Survival.h"


ACollisionInteractActorBase::ACollisionInteractActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractComponent"));
	InteractCollision->SetCollisionObjectType(ECC_PlayerInteract);
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	InteractCollision->SetCollisionResponseToChannel(ECC_PlayerInteract, ECR_Ignore);
	SetRootComponent(InteractCollision);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(InteractCollision);
	StaticMesh->SetCollisionObjectType(ECC_PlayerInteract);
	StaticMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	StaticMesh->SetCollisionResponseToChannel(ECC_PlayerInteract, ECR_Ignore);

	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &ACollisionInteractActorBase::OnInteractHit);
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACollisionInteractActorBase::OnMeshHit);
	bUseLifeSpan = false;
}

void ACollisionInteractActorBase::OnInteractHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
{
}

void ACollisionInteractActorBase::OnMeshHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
}
