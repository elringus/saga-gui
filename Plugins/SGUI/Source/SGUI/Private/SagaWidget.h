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
	static WidgetType* InstantiateWidget(UObject* worldContextObject = nullptr, int32 zOrder = 0)
	{
		CacheWidgetClasses();

		auto widgetClass = widgetClassesCache.FindByPredicate([](UClass* wc){ return Cast<WidgetType>(wc->GetDefaultObject()); });
		if (!widgetClass) UE_LOG(SagaGUI, Fatal, TEXT("InstantiateWidget(): Can't find widget class in the cache."));

		auto masterController = GetPlayerController(worldContextObject);
		if (!masterController) UE_LOG(SagaGUI, Fatal, TEXT("InstantiateWidget(): Can't get player controller."));

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
