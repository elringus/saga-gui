#include "SGUI.h"
#include "SagaWidget.h"

TArray<UClass*> USagaWidget::widgetClassesCache;

void USagaWidget::CacheWidgetClasses()
{
	if (widgetClassesCache.Num() > 0) return;

	TArray<FString> widgetPaths;
	widgetPaths.Add(TEXT("/Game/SGUI/UMG/AllyDot.AllyDot_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/UMG/FloatingBar.FloatingBar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/UMG/FloatingText.FloatingText_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/UMG/Inventory.Inventory_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/UMG/PlayerHP.PlayerHP_C"));

	for (int i = 0; i < widgetPaths.Num(); i++)
	{
		auto widgetClass = LoadObject<UClass>(NULL, *widgetPaths[i]);
		if (widgetClass) widgetClassesCache.AddUnique(widgetClass);
	}
}
