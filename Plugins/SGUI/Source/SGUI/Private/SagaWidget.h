#pragma once

#include "Blueprint/UserWidget.h"
#include "SagaWidget.generated.h"

/**
 *  Base class for all the widgets implementations.
 */
UCLASS()
class SGUI_API USagaWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	*  Removes all the widgets from the viewport and destroys them.
	*  @param worldContextObject Any UObject to get world context from.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Destroy All Widgets",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI")
	static void DestroyAllWidgets(UObject* worldContextObject);

protected:
	class APlayerController* MasterController;

	template<typename WidgetType>
	static WidgetType* InstantiateWidget(UObject* worldContextObject, int32 zOrder = 0)
	{
		if (!worldContextObject->GetWorld()->IsPlayInEditor() && worldContextObject->GetWorld()->IsServer()) 
		{ 
			UE_LOG(SagaGUI, Error, TEXT("InstantiateWidget(): Called as server. Aborting widget creation.")); 
			return nullptr; 
		}

		CacheWidgetClasses();

		auto widgetClass = widgetClassesCache.FindByPredicate([](UClass* wc)->WidgetType*{
			// Workaround for a bug, when cached pointers becomes null. 
			// Should not be required, when Epic will fix the static UMG refs bug.
			if (!wc) { UE_LOG(SagaGUI, Error, TEXT("InstantiateWidget(): Cached pointers are null. Aborting widget creation.")); return nullptr; }
			else return Cast<WidgetType>(wc->GetDefaultObject()); 
		});
		if (!widgetClass) { UE_LOG(SagaGUI, Error, TEXT("InstantiateWidget(): Can't find widget class in the cache. Aborting widget creation.")); return nullptr; }

		auto masterController = GetPlayerController(worldContextObject);
		if (!masterController) { UE_LOG(SagaGUI, Error, TEXT("InstantiateWidget(): Can't get player controller. Aborting widget creation.")); return nullptr; }

		auto widget = CreateWidget<USagaWidget>(masterController, *widgetClass);

		widget->AddToViewport(zOrder);
		widget->MasterController = masterController;

		return Cast<WidgetType>(widget);
	}

	FORCEINLINE static UCanvasPanelSlot* GetSlot(UWidget* widget) { return Cast<UCanvasPanelSlot>(widget->Slot); }

	FORCEINLINE static FVector2D GetViewportSize() { return FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); }
	FORCEINLINE static float GetViewportScale() { return GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(GetViewportSize().X, GetViewportSize().Y)); }
	FORCEINLINE static float GetQualityScale() { Scalability::FQualityLevels scalabilityQuality = Scalability::GetQualityLevels(); return scalabilityQuality.ResolutionQuality / 100.0f; }
	FORCEINLINE static FVector2D GetViewportCenter() { return (GetViewportSize() / GetViewportScale()) / 2; }

	FORCEINLINE bool SetPositionFromWorld(FVector worldPosition, UCanvasPanelSlot* slot = nullptr, FVector2D pivotCorrection = FVector2D::ZeroVector)
	{ 
		if (!MasterController) return false;

		FVector2D screenPos;
		bool isInViewport;
		isInViewport = MasterController->ProjectWorldLocationToScreen(worldPosition, screenPos);
		if (slot) slot->SetPosition(screenPos / GetViewportScale());
		else SetPositionInViewport(screenPos / GetQualityScale() - pivotCorrection);

		return isInViewport;
	}

private:
	static TArray<UClass*> widgetClassesCache;
	static void CacheWidgetClasses();

};
