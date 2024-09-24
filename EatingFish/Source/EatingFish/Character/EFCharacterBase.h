// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/EFAnimationAttackInterface.h"
#include <EatingFish/Animation/EFAnimInstance.h>
#include "EFCharacterBase.generated.h"

UCLASS()
class EATINGFISH_API AEFCharacterBase : public ACharacter, public IEFAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEFCharacterBase();

protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
protected:
	void HpDecrease(float Damage);
	bool die;

	float curHp;
	float maxHp;

	UEFAnimInstance* EFAnimInstance;
};
