// Fill out your copyright notice in the Description page of Project Settings.


#include "EFCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AEFCharacterPlayer::AEFCharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // 4미터
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

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
}

void AEFCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AEFCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Triggered, this,
		&AEFCharacterPlayer::UpDown);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		&AEFCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this,
		&AEFCharacterPlayer::Attack);
}

void AEFCharacterPlayer::UpDown(const FInputActionValue& Value)
{
	float UpDownValue = Value.Get<float>();

	// 현재 캐릭터 위치 가져오기
	FVector CurrentLocation = GetActorLocation();

	// Up/Down 값을 Z축에 반영하여 새로운 위치 계산
	// 여기서 UpDownValue가 양수면 위로, 음수면 아래로 이동합니다.
	FVector NewLocation = CurrentLocation + FVector(0.f, 0.f, UpDownValue * UpDownSpeed);

	// 캐릭터의 위치 업데이트
	SetActorLocation(NewLocation);
}

void AEFCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AEFCharacterPlayer::Attack(const FInputActionValue& Value)
{

}


