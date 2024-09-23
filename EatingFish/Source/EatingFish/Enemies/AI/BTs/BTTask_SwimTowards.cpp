// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AI/BTs/BTTask_SwimTowards.h"
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemies/Character/EFEnemyFishBase.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_SwimTowards::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Res =  Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	//if (!OwnerPawn) {
	//	UE_LOG(LogTemp, Warning, TEXT("There is no ownerPawn!!!!!!!!!!!!!!1"));
	//}
	if (OwnerPawn) {
		ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerPawn);

		if (OwnerCharacter) {
			UObject* KeyValue = BBComp->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
			AActor* TargetActor = Cast<AActor>(KeyValue);

			if (TargetActor) {
				FVector MyPos = OwnerPawn->GetActorLocation();
				FVector Dir = TargetActor->GetActorLocation() - MyPos;
				

				//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), (Speed * Dir.GetSafeNormal()).X, (Speed * Dir.GetSafeNormal()).Y, (Speed * Dir.GetSafeNormal()).Z);

				OwnerCharacter->GetCharacterMovement()->Velocity = Speed * Dir.GetSafeNormal();

				FRotator Rot = UKismetMathLibrary::FindLookAtRotation(MyPos, OwnerCharacter->GetVelocity() + MyPos);
				Rot.Add(90, 0, 0);
				OwnerCharacter->SetActorRotation(Rot);

				return EBTNodeResult::Succeeded;

			}
		}
		
	}

	return EBTNodeResult::Failed;
}
