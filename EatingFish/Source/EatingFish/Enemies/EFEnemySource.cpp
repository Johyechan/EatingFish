// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EFEnemySource.h"
#include "Enemies/Character/EFEnemyFishBase.h"
#include "Enemies/Character/EFEnemyFishFire.h"

// Sets default values for this component's properties
UEFEnemySource::UEFEnemySource()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SpawnGap = 1.0f;
	SpawnRange = 500.0f;

	SpawnableEnemies.Add(AEFEnemyFishFire::StaticClass());
	//################################юс╫ц############################
}


// Called when the game starts
void UEFEnemySource::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UEFEnemySource::SpawnEnemy, SpawnGap, false);
	
}

void UEFEnemySource::SpawnEnemy()
{
	FVector SpLoc = GetOwner()->GetActorLocation();
	FVector RandLoc = FVector::OneVector;

	RandLoc.X *= FMath::RandRange(-SpawnRange, SpawnRange);
	RandLoc.Y *= FMath::RandRange(-SpawnRange, SpawnRange);
	RandLoc.Z *= FMath::RandRange(-SpawnRange, SpawnRange);
	FTransform SpTrm(FQuat::Identity, SpLoc + RandLoc);

	FHitResult Hit;
	bool IsHit = GetWorld()->SweepSingleByChannel(Hit, SpLoc, SpLoc + RandLoc, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(1.0f));
	if (IsHit) {
		SpTrm = FTransform(Hit.Location + FVector::UpVector * 100);
	}
	int32 EnemyTypeIdx = FMath::RandRange(0, SpawnableEnemies.Num() - 1);
	TSubclassOf<AEFEnemyFishBase> Selected = SpawnableEnemies[EnemyTypeIdx];

	if (Selected) {
		AEFEnemyFishBase* ECh = GetWorld()->SpawnActorDeferred<AEFEnemyFishBase>(Selected, SpTrm);
		if (ECh) {
			ECh->FinishSpawning(SpTrm);
		}
	}
}


