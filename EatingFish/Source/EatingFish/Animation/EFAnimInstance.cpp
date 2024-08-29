// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EFAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UEFAnimInstance::UEFAnimInstance()
{
	MovingThreshould = 3.0f;
}

void UEFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UEFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		Velocity = Movement->Velocity;
		Speed = Velocity.Size2D();
		bIsIdle = Speed < MovingThreshould;
	}
}


