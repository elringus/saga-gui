#include "SGUI.h"
#include "SagaWidget.h"

TArray<UClass*> USagaWidget::widgetClassesCache;

void USagaWidget::DestroyAllWidgets(UObject* worldContextObject)
{
	worldContextObject->GetWorld()->GetGameViewport()->RemoveAllViewportWidgets();
	widgetClassesCache.Empty();
}

void USagaWidget::CacheWidgetClasses()
{
	// It seems GC cleans the cache while in build.
	// So disabling it and waiting for Epic to fix the static UMG refs bug.
	//if (widgetClassesCache.Num() > 0) return;
	widgetClassesCache.Empty();

	TArray<FString> widgetPaths;
	widgetPaths.Add(TEXT("/Game/SGUI/ActionBar/ActionBarButton.ActionBarButton_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/ActionBar/ActionBar.ActionBar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/ActionTable/ActionTable.ActionTable_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/AllyDot/AllyDot.AllyDot_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/FloatingBar/FloatingBar.FloatingBar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/FloatingText/FloatingText.FloatingText_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/Frags/Frags.Frags_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/GroupStatus/GroupStatus.GroupStatus_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/GroupStatus/GroupMember.GroupMember_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/Inventory/Inventory.Inventory_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/PlayerAvatar/PlayerAvatar.PlayerAvatar_C"));
	widgetPaths.Add(TEXT("/Game/SGUI/PlayerStatus/PlayerStatus.PlayerStatus_C"));

	for (int i = 0; i < widgetPaths.Num(); i++)
	{
		auto widgetClass = LoadObject<UClass>(NULL, *widgetPaths[i]);
		if (widgetClass) widgetClassesCache.AddUnique(widgetClass);
	}
}
