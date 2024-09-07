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
		float UpDownSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		float AttackDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Speed, Meta = (AllowPrivateAccess = "true"))
		float AttackSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool, Meta = (AllowPrivateAccess = "true"))
		bool bIsGround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool, Meta = (AllowPrivateAccess = "true"))
		bool bIsOnce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bool, Meta = (AllowPrivateAccess = "true"))
		bool bIsAttack;

	void AttackEnd();
};
