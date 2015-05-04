#pragma once

#include "Engine.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"

#include "SagaWidget.h"
#include "ActionBarButtonWidget.h"
#include "ActionBarWidget.h"
#include "AllyDotWidget.h"
#include "FloatingBarWidget.h"
#include "FloatingTextWidget.h"
#include "InventoryWidget.h"
#include "PlayerAvatarWidget.h"
#include "PlayerHPWidget.h"

#define Print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, text)

DECLARE_LOG_CATEGORY_EXTERN(SagaGUI, Log, All);

/**
*  Finds player controller for the main player.
*  @param worldContextObject Any UObject to get world context from.
*  Should be passed in case of multi-world environments.
*  @return Pointer to the found player controller.
*/
FORCEINLINE APlayerController* GetPlayerController(UObject* worldContextObject = nullptr)
{
	if (worldContextObject) 
		return UGameplayStatics::GetPlayerController(worldContextObject, 0);

	// Works only for single-world cases. Not usable for multiplayer projects.
	for (TObjectIterator<APlayerController> pc; pc; ++pc)
		if (pc->bActorInitialized) return *pc;
	return nullptr;

	// Hack for multiworld cases. Causes terrible freeze on first use. 
	// Should be avoided by using auto self refs in BP.
	// return UGameplayStatics::GetPlayerController(GEngine, 0);
}

/**
*  A hack to know if we are currently in editor mode or game simulation is running.
*  @return True if game is running.
*/
FORCEINLINE bool IsGameRunning(UObject* worldContextObject)
{
	return GetPlayerController(worldContextObject) ? true : false;
}