// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EFEnemySource.h"
#include "Enemies/Character/EFEnemyFishBase.h"

// Sets default values for this component's properties
UEFEnemySource::UEFEnemySource()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SpawnGap = 2.5f;
	SpawnRange = 500.0f;

	SpawnableEnemies.Add(AEFEnemyFishBase::StaticClass());
	//################################юс╫ц############################
}


// Called when the game starts
void UEFEnemySource::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UEFEnemySource::SpawnEnemy, SpawnGap, true);
	
}

void UEFEnemySource::SpawnEnemy()
{
	FVector SpLoc = GetOwner()->GetActorLocation();
	FVector RandLoc = FVector::OneVector;

	RandLoc.X *= FMath::RandRange(-SpawnRange, SpawnRange);
	RandLoc.Y *= FMath::RandRange(-SpawnRange, SpawnRange);
	const FTransform SpTrm(FQuat::Identity, SpLoc + RandLoc);

	int32 EnemyTypeIdx = FMath::RandRange(0, SpawnableEnemies.Num() - 1);
	TSubclassOf<AEFEnemyFishBase> Selected = SpawnableEnemies[EnemyTypeIdx];

	if (Selected) {
		AEFEnemyFishBase* ECh = GetWorld()->SpawnActorDeferred<AEFEnemyFishBase>(Selected, SpTrm);
		if (ECh) {
			ECh->FinishSpawning(SpTrm);
		}
	}
}


