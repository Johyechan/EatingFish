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
#include "Skills/EFSkillDataBase.h"

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

	Status.MaxLife = 100;
	Status.AtkRange = 100;
	Status.MoveSpeed = 500;
	Status.Power = 10;

	Status.Life = Status.MaxLife;


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetRelativeRotation(FRotator(00, -90, 90));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -20));

	GetCapsuleComponent()->InitCapsuleSize(25, 50);
	GetCapsuleComponent()->SetRelativeRotation(FRotator(90, 0, 0));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->MaxSwimSpeed = Status.MoveSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20;
	GetCharacterMovement()->BrakingDecelerationSwimming = 1000;
	GetCharacterMovement()->GravityScale = 0;

	

	AIControllerClass = AEFEnemyFishAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	
	

	

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
	return Status.AtkRange;
}

float AEFEnemyFishBase::GetLife()
{
	return Status.Life;
}

void AEFEnemyFishBase::DecreaseHp(float Amt)
{
	Status.Life -= Amt;
	Status.Life = FMath::Clamp(Status.Life, 0, Status.MaxLife);
	if (Status.Life <= 0) {
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
	const FVector EndPos = StartPos + GetActorForwardVector() * Status.AtkRange;

	bool IsHit = GetWorld()->SweepSingleByChannel(OutHitRes, StartPos, EndPos, FQuat::Identity, ECC_Camera, FCollisionShape::MakeSphere(Status.AtkRange), Params);
	if (IsHit) {
		AEFCharacterPlayer* PC = Cast<AEFCharacterPlayer>(OutHitRes.GetActor());
		if (PC) {
			UGameplayStatics::ApplyDamage(PC, Status.Power, GetController(), nullptr, nullptr);
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

void AEFEnemyFishBase::UseSkill()
{
	for (auto Skill : Skills)
	{
		if (Skill->GetSkillUseState()) {
			Skill->Use(this);
			return;
		}
	}
}

uint8 AEFEnemyFishBase::ExamineSkillUse(AActor* Target)
{
	float Dist = (Target->GetActorLocation() - GetActorLocation()).Length();
	for(auto Skill : Skills)
	{
		if (Dist <= Skill->Range) {
			if (Skill->GetSkillUseState())
				return true;
		}
	}

	return false;
}

FEFStat AEFEnemyFishBase::GetStat()
{
	return Status;
}

void AEFEnemyFishBase::SetStat(float Amount, EStatusType Type)
{
	switch (Type)
	{
	case EStatusType::MaxLife:
		Status.MaxLife += Amount;
		if (Amount >= 0)
			Status.Life += Amount;
		Status.Life = FMath::Clamp(Status.Life, 0, Status.MaxLife);
		break;
	case EStatusType::Power:
		Status.Power += Amount;
		break;
	case EStatusType::AtkRange:
		Status.AtkRange += Amount;
		break;
	case EStatusType::MoveSpeed:
		Status.MoveSpeed += Amount;
		GetCharacterMovement()->MaxSwimSpeed = Status.MoveSpeed;
		break;
	default:
		break;
	}
}

