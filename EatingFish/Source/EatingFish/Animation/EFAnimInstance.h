// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EFAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API UEFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEFAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	FORCEINLINE void SetIsUp(bool b) { bIsUp = b; }
	FORCEINLINE void SetIsDown(bool b) { bIsDown = b; }
	FORCEINLINE void SetIsSurface(bool b) { IsSurface = b; }
	FORCEINLINE void SetIsGround(bool b) { IsGround = b; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
		TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		bool IsSurface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		bool IsGround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		bool bIsDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		bool bIsUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float MovingThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		float JumpingThreshould;
};
