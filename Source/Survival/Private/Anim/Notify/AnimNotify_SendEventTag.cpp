#include "Anim/Notify/AnimNotify_SendEventTag.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAnimNotify_SendEventTag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),EventTag,FGameplayEventData());
}
