// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/EFReplicateSelfSkill.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UEFReplicateSelfSkill::Use(IEFStatusEntities* User)
{
	ACharacter* Fish = Cast<ACharacter>(User);

	if (Fish) {
		FVector SpLoc = Fish->GetActorLocation();
		FVector RandLoc = FVector::OneVector;

		RandLoc.X *= FMath::RandRange(-CopyRange, CopyRange);
		RandLoc.Y *= FMath::RandRange(-CopyRange, CopyRange);
		RandLoc.Z *= FMath::RandRange(-CopyRange, CopyRange);
		const FTransform SpTrm(Fish->GetActorRotation(), SpLoc + RandLoc);


		ACharacter* Cop = GetWorld()->SpawnActorDeferred<ACharacter>(Fish->GetClass(), SpTrm);
		if (Cop) {
			Cop->FinishSpawning(SpTrm);
		}
	}
}

uint8 UEFReplicateSelfSkill::GetSkillUseState()
{
	if (Super::GetSkillUseState()) {
		TArray<AActor*> AllActors = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

		return AllActors.Num() < 10;
	}
	return false;
}
