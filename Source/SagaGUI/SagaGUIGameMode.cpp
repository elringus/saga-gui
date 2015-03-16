// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SagaGUI.h"
#include "SagaGUIGameMode.h"
#include "SagaGUICharacter.h"

ASagaGUIGameMode::ASagaGUIGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
