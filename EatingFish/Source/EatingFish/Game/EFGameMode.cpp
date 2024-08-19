// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EFGameMode.h"
#include "EFGameMode.h"

AEFGameMode::AEFGameMode()
{
	// DefaultPawnClass // 여기 바꿔야 하나?
	static ConstructorHelpers::FClassFinder<APawn>ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn>DefaultPawnClassRef(TEXT("/Script/EatingFish.EFCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	// PlayerControllerClass
	static ConstructorHelpers::FClassFinder<APlayerController>PlayerControllerClassRef(TEXT("/Script/EatingFish.EFPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
