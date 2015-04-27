#include "SGUI.h"
#include "SagaWidget.h"

TArray<TSubclassOf<class USagaWidget>> USagaWidget::widgetClassesCache;

USagaWidget::USagaWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
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
		ConstructorHelpers::FObjectFinder<UClass> widgetClass(*widgetPaths[i]);
		if (widgetClass.Succeeded()) widgetClassesCache.AddUnique(widgetClass.Object);
	}
}
