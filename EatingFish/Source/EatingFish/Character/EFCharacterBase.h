// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/EFAnimationAttackInterface.h"
#include "EFCharacterBase.generated.h"

UCLASS()
class EATINGFISH_API AEFCharacterBase : public ACharacter, public IEFAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEFCharacterBase();

protected:

	// Attack을 멈추게 해야해

	virtual void AttackHitCheck() override;
};
