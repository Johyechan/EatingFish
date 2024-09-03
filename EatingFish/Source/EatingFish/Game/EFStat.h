#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EFStat.generated.h"

UENUM()
enum class EStatusType {
	MaxLife,
	Power,
	AtkRange,
	MoveSpeed,


};

USTRUCT(BlueprintType)
struct FEFStat {
	GENERATED_BODY()

public:
	FEFStat() : MaxLife(0), Life(0), Power(0), AtkRange(0), MoveSpeed(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Life;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AtkRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MoveSpeed;
};