// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EFCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Physics/EFCollision.h"

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
    GetCharacterMovement()->MaxSwimSpeed = 500.0f;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
    GetCharacterMovement()->BrakingDecelerationSwimming = 2000.0f;

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

void AEFCharacterBase::AttackHitCheck()
{
    // ÀÌ»õ³¢ ¿Ö ¹°ÀÌ¶û ´êÀ½?
    FHitResult OutHitResult; 
    FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);
    const float AttackRange = 40.0f; 
    const float AttackRadius = 50.0f; 
    const float AttackDamage = 30.0f; 
    const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius(); 
    const FVector End = Start + GetActorForwardVector() * AttackRange;
    bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity,
        CCHANNEL_EFACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

    if (HitDetected) 
    {

    }

#if ENABLE_DRAW_DEBUG
    FVector CapsuleOrigin = Start + (End - Start) * 0.5f; 
    float CapsuleHalfHeight = AttackRange * 0.5f; 
    FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
    DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius,
        FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

