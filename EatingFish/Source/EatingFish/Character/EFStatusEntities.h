// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Game/EFStat.h"
#include "EFStatusEntities.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEFStatusEntities : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EATINGFISH_API IEFStatusEntities
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FEFStat GetStat() = 0;
	virtual void SetStat(float Amount, EStatusType Type) = 0;
};
