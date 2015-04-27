#pragma once

#include "Blueprint/UserWidget.h"
#include "SagaWidget.generated.h"

/**
 *	Base class for all the widgets implementations.
 */
UCLASS()
class SGUI_API USagaWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USagaWidget(const class FObjectInitializer& objectInitializer);
	static void CacheWidgetClasses();

protected:
	class APlayerController* MasterController;

	template<typename WidgetType>
	static WidgetType* InstantiateWidget(APlayerController* masterController)
	{
		CacheWidgetClasses();

		auto widgetClass = widgetClassesCache.FindByPredicate([](UClass* wc){ return Cast<WidgetType>(wc->GetDefaultObject()); });
		if (!widgetClass) throw ("SagaGUI: Can't find widget class in the cache.");

		auto widget = CreateWidget<USagaWidget>(masterController, *widgetClass);

		widget->AddToViewport();
		widget->MasterController = masterController;

		return Cast<WidgetType>(widget);
	}

	FORCEINLINE static UCanvasPanelSlot* GetSlot(UWidget* widget) { return Cast<UCanvasPanelSlot>(widget->Slot); }

	FORCEINLINE static FVector2D GetViewportSize() { return FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); }
	FORCEINLINE static float GetViewportScale() { return GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(GetViewportSize().X, GetViewportSize().Y)); }
	FORCEINLINE static float GetQualityScale() { Scalability::FQualityLevels scalabilityQuality = Scalability::GetQualityLevels(); return scalabilityQuality.ResolutionQuality / 100.0f; }
	FORCEINLINE static FVector2D GetViewportCenter() { return (GetViewportSize() / GetViewportScale()) / 2; }

	FORCEINLINE bool SetPositionFromWorld(FVector worldPosition, FVector2D pivotCorrection = FVector2D::ZeroVector) 
	{ 
		FVector2D screenPos;
		bool isInViewport;
		isInViewport = MasterController->ProjectWorldLocationToScreen(worldPosition, screenPos);
		SetPositionInViewport(screenPos / GetQualityScale() - pivotCorrection);

		return isInViewport;
	}

private:
	static TArray<UClass*> widgetClassesCache;
};
