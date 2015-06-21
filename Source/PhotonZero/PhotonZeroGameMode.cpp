// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PhotonZero.h"
#include "PhotonZeroGameMode.h"
#include "PhotonZeroPlayerController.h"
#include "PhotonZeroCharacter.h"

APhotonZeroGameMode::APhotonZeroGameMode()
{
	// use our custom PlayerController class
	
	PlayerControllerClass = APhotonZeroPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}