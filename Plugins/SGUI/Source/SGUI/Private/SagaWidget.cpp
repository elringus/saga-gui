#include "SGUI.h"
#include "SagaWidget.h"

TArray<UClass*> USagaWidget::widgetClassesCache;

void USagaWidget::CacheWidgetClasses()
{
	if (widgetClassesCache.Num() > 0) return;

	TArray<FString> widgetPaths;
	widgetPaths.Add(TEXT("/Game/SGUI/ActionBar/ActionBarButton.ActionBarButton_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/ActionBar/ActionBar.ActionBar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/AllyDot/AllyDot.AllyDot_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/FloatingBar/FloatingBar.FloatingBar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/FloatingText/FloatingText.FloatingText_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/Inventory/Inventory.Inventory_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/PlayerAvatar/PlayerAvatar.PlayerAvatar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/PlayerHP/PlayerHP.PlayerHP_C"));

	for (int i = 0; i < widgetPaths.Num(); i++)
	{
		auto widgetClass = LoadObject<UClass>(NULL, *widgetPaths[i]);
		if (widgetClass) widgetClassesCache.AddUnique(widgetClass);
	}
}
