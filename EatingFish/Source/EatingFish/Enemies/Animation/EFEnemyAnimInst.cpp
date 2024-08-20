// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Animation/EFEnemyAnimInst.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UEFEnemyAnimInst::UEFEnemyAnimInst()
{
	MovingThreshold = 5;
}

void UEFEnemyAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner) {
		Movement = Owner->GetCharacterMovement();
	}
}

void UEFEnemyAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement) {
		MoveVel = Movement->Velocity;
		GroundSpeed = MoveVel.Size2D();
		bIsIdle = GroundSpeed < MovingThreshold;
	}
}
