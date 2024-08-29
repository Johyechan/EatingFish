// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EFCharacterBase.h"
#include "InputActionValue.h"
#include <EatingFish/Animation/EFAnimInstance.h>
#include "EFCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class EATINGFISH_API AEFCharacterPlayer : public AEFCharacterBase
{
	GENERATED_BODY()

public:
	AEFCharacterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	float GetPlayerZLocation(UWorld* World);

// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UCameraComponent> FollowCamera;

// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> UpDownAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

	void UpDown(const FInputActionValue& Value);
	void UpDownEnd(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
		UEFAnimInstance* EFAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		float UpDownSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		float SurfaceSwimZ = -30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		float UnderwaterSwimZ = -100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		bool bIsInWater;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		bool bCanJump;
};
