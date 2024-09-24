// Fill out your copyright notice in the Description page of Project Settings.


#include "EFCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Enemies/EFEnemySource.h>

AEFCharacterPlayer::AEFCharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	FollowEnemySource = CreateDefaultSubobject<UEFEnemySource>(TEXT("FollowEnemySource"));

	GetCharacterMovement()->GravityScale = 1.0f;
	UpDownSpeed = 2.0f;
	AttackSpeed = 1000.0f;
	AttackTime = 0.5f;
	bIsAttack = false;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>InputMappingContextRef(TEXT("/Game/EF/Inputs/EFInputMap.EFInputMap"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionUpDown(TEXT("/Game/EF/Inputs/IAUpDown.IAUpDown"));
	if (nullptr != InputActionUpDown.Object)
	{
		UpDownAction = InputActionUpDown.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionMove(TEXT("/Game/EF/Inputs/IAMove.IAMove"));
	if (nullptr != InputActionMove.Object)
	{
		MoveAction = InputActionMove.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionAttack(TEXT("/Game/EF/Inputs/IAAttack.IAAttack"));
	if (nullptr != InputActionAttack.Object)
	{
		AttackAction = InputActionAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionLook(TEXT("/Game/EF/Inputs/IALook.IALook"));
	if (nullptr != InputActionLook.Object)
	{
		LookAction = InputActionLook.Object;
	}
}

void AEFCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	bIsGround = true;

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance Class: %s"), *AnimInstance->GetClass()->GetName());

		EFAnimInstance = Cast<UEFAnimInstance>(AnimInstance);

		if (EFAnimInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully cast to UEFAnimInstance"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UEFAnimInstance"));
		}
	}
}

void AEFCharacterPlayer::Tick(float DeltaTime)
{
	if (die)
	{
		EFAnimInstance->SetIsDie(true);
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	}
	else
	{
		if (bIsGround)
		{
			bIsOnce = true;
			GetCharacterMovement()->GravityScale = 1.0f;
			EFAnimInstance->SetIsInWater(false);
			EFAnimInstance->SetIsGround(true);
		}
		else
		{
			if (bIsOnce)
			{
				FVector CurrentLocation = GetActorLocation();
				if (CurrentLocation.Z < -100.0f)
				{
					GetCharacterMovement()->GravityScale = 0.0f;
					CurrentLocation.Z += 50.0f;
					SetActorLocation(CurrentLocation);
					bIsOnce = false;
				}
			}
			EFAnimInstance->SetIsInWater(true);
			EFAnimInstance->SetIsGround(false);
		}
	}
}

void AEFCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Triggered, this, &AEFCharacterPlayer::UpDown);
	EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Completed, this, &AEFCharacterPlayer::UpDownEnd);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEFCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AEFCharacterPlayer::MoveEnd);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AEFCharacterPlayer::Attack);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEFCharacterPlayer::Look);
}

void AEFCharacterPlayer::UpDown(const FInputActionValue& Value)
{
	if (!bIsGround && !bIsAttack)
	{
		float UpDownValue = Value.Get<float>();

		if (UpDownValue < 0)
		{
			EFAnimInstance->SetIsUp(false);
			EFAnimInstance->SetIsDown(true);
		}
		else if (UpDownValue > 0)
		{
			EFAnimInstance->SetIsUp(true);
			EFAnimInstance->SetIsDown(false);
		}

		FVector CurrentLocation = GetActorLocation();
		
		if (CurrentLocation.Z < -30.0f)
		{
			CurrentLocation.Z += UpDownValue * UpDownSpeed;
			SetActorLocation(CurrentLocation);
		}
		else
		{
			float before = CurrentLocation.Z;
			CurrentLocation.Z += UpDownValue * UpDownSpeed;
			float after = CurrentLocation.Z;
			if (before > after)
			{
				SetActorLocation(CurrentLocation);
			}
		}
	}
}

void AEFCharacterPlayer::UpDownEnd(const FInputActionValue& Value)
{
	EFAnimInstance->SetIsUp(false);
	EFAnimInstance->SetIsDown(false);

	FVector CurVelocity = GetCharacterMovement()->Velocity;
	GetCharacterMovement()->Velocity = FVector(CurVelocity.X, CurVelocity.Y, 0);
}

void AEFCharacterPlayer::Move(const FInputActionValue& Value)
{
	if (!bIsAttack)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AEFCharacterPlayer::MoveEnd(const FInputActionValue& Value)
{
	FVector CurVelocity = GetCharacterMovement()->Velocity;
	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, CurVelocity.Z);
}

void AEFCharacterPlayer::Attack(const FInputActionValue& Value)
{
	if (!bIsAttack && !bIsGround)
	{
		bIsAttack = true;
		EFAnimInstance->SetIsAttack(bIsAttack);

		FVector ForwardDirection = GetActorForwardVector();

		FVector AttackVelocity = ForwardDirection * AttackSpeed;

		LaunchCharacter(AttackVelocity, true, true);

		GetWorld()->GetTimerManager().SetTimer(AttackTimeHandler, this, &AEFCharacterPlayer::AttackEnd, AttackTime, false);
	}
}

void AEFCharacterPlayer::AttackEnd()
{
	bIsAttack = false;
	EFAnimInstance->SetIsAttack(bIsAttack);

	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
}

void AEFCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}


