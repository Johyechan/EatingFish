// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Animation/AnimNotify_DoAttackNotify.h"
#include "AnimNotify_DoAttackNotify.h"
#include "Enemies/Character/EFEnemyFishBase.h"

void UAnimNotify_DoAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp) {
		AEFEnemyFishBase* Attacker = Cast<AEFEnemyFishBase>(MeshComp->GetOwner());
		if (Attacker) {
			Attacker->Bite();
		}
	}
}
