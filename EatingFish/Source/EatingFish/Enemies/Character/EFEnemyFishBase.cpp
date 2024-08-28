// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Character/EFEnemyFishBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemies/AI/EFEnemyFishAI.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "Enemies/Animation/EFEnemyAnimInst.h"
#include "Character/EFCharacterPlayer.h"
#include "Character/EFCharacterBase.h"

// Sets default values
AEFEnemyFishBase::AEFEnemyFishBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FishObjRef(TEXT("/Game/AnimatedFantasyFish/Meshes/SM_Piranha.SM_Piranha"));
	if (FishObjRef.Object) {
		GetMesh()->SetSkeletalMesh(FishObjRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAnimRef(TEXT("/Game/AnimatedFantasyFish/Animations/EFAnim_Piranha_attack_Montage.EFAnim_Piranha_attack_Montage"));
	if (AttackAnimRef.Object) {
		AttackAnim = AttackAnimRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DieAnimRef(TEXT("/Game/AnimatedFantasyFish/Animations/EFAnim_Piranha_death_Montage.EFAnim_Piranha_death_Montage"));
	if (DieAnimRef.Object) {
		DieAnim = DieAnimRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClassRef(TEXT("/Game/EF/Animations/EFPiranhaAnim.EFPiranhaAnim_C"));
	if (AnimClassRef.Class) {
		GetMesh()->SetAnimClass(AnimClassRef.Class);
	}


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetRelativeRotation(FRotator(00, -90, 90));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -20));

	GetCapsuleComponent()->InitCapsuleSize(25, 50);
	GetCapsuleComponent()->SetRelativeRotation(FRotator(90, 0, 0));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->MaxSwimSpeed = 500;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20;
	GetCharacterMovement()->BrakingDecelerationSwimming = 1000;
	GetCharacterMovement()->GravityScale = 0;

	

	AIControllerClass = AEFEnemyFishAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	
	

	Life = MaxLife;
	AtkRange = 200;

}

// Called when the game starts or when spawned
void AEFEnemyFishBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->StartSwimming(GetActorLocation(), GetVelocity(), 0.1f, 0, 5);
}

// Called every frame
void AEFEnemyFishBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEFEnemyFishBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEFEnemyFishBase::GetAtkRange()
{
	return AtkRange;
}

float AEFEnemyFishBase::GetLife()
{
	return Life;
}

void AEFEnemyFishBase::DecreaseHp(float Amt)
{
	Life -= Amt;
	Life = FMath::Clamp(Life, 0, MaxLife);
	if (Life <= 0) {
		DoDie();
	}
}

void AEFEnemyFishBase::DoDie()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	if (AnimIns) {
		AnimIns->StopAllMontages(0);
		AnimIns->Montage_Play(DieAnim);
	}
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	AEFEnemyFishAI* FishAI = Cast<AEFEnemyFishAI>(GetController());
	if (FishAI) {
		FishAI->StopAI();
	}

	FTimerHandle Dier;
	GetWorld()->GetTimerManager().SetTimer(Dier, FTimerDelegate::CreateLambda([&]() {Destroy(); }), 5.0f, false);
}

void AEFEnemyFishBase::DoAttack()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetMesh()->GetAnimInstance()->Montage_Play(AttackAnim);

	FOnMontageEnded OnEnd;
	OnEnd.BindUObject(this, &AEFEnemyFishBase::EndAnim);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnEnd, AttackAnim);
}

void AEFEnemyFishBase::Bite()
{
	FHitResult OutHitRes;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const FVector StartPos = GetActorLocation();
	const FVector EndPos = StartPos + GetActorForwardVector() * 25;

	bool IsHit = GetWorld()->SweepSingleByChannel(OutHitRes, StartPos, EndPos, FQuat::Identity, ECC_Camera /*�����÷��̾�����ϴ�ä��*/, FCollisionShape::MakeSphere(25), Params);
	if (IsHit) {
		AEFCharacterPlayer* PC = Cast<AEFCharacterPlayer>(OutHitRes.GetActor());
		if (PC) {
			UGameplayStatics::ApplyDamage(PC, 10, GetController(), nullptr, nullptr);
		}
	}
}

void AEFEnemyFishBase::DeleteSelf()
{
	Destroy();
}

void AEFEnemyFishBase::EndAnim(UAnimMontage* Montage, bool IsPropEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
}

float AEFEnemyFishBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DecreaseHp(DamageAmount);
	return DamageAmount;
}

