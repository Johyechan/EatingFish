// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EFCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEFCharacterBase::AEFCharacterBase()
{
    // Pawn
    bUseControllerRotationPitch = false; 
    bUseControllerRotationYaw = false; 
    bUseControllerRotationRoll = false;

    // Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); 
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    //Movement 
    GetCharacterMovement()->bOrientRotationToMovement = true; 
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
    GetCharacterMovement()->JumpZVelocity = 700.0f; 
    GetCharacterMovement()->AirControl = 0.35f; 
    GetCharacterMovement()->MaxWalkSpeed = 500.0f; 
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f; 
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

    // Mesh
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f)); 
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); 
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMeshRef(TEXT("/Game/FemaleAndroid/Mesh/SK_FemaleAndroid.SK_FemaleAndroid")); 
    if (CharacterMeshRef.Object) 
    { 
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstanceClassRef(TEXT("/Game/EF/Animations/ABP_EFCharacter.ABP_EFCharacter_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }
}

