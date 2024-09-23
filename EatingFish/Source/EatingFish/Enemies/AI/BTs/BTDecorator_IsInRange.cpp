// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/BTs/BTDecorator_IsInRange.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemies/Character/EFEnemyFishBase.h"

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Res = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn) {
		AEFEnemyFishBase* Fish = Cast<AEFEnemyFishBase>(OwnerPawn);

		if (Fish) {
			UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

			if (BBComp) {
				UObject* KeyValue = BBComp->GetValueAsObject(TEXT("Target"));
				AActor* TargetActor = Cast<AActor>(KeyValue);

				
				if (TargetActor) {
					//UE_LOG(LogTemp, Warning, TEXT("Target Acquired"));
					float Dist = FVector::Dist(OwnerPawn->GetActorLocation(), TargetActor->GetActorLocation());

					if (Dist < Fish->GetStat().AtkRange) {
						return true;
					}
				}
			}
		}


		
	}

	return false;
}
