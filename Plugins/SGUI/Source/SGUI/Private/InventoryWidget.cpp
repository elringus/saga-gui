#include "SGUI.h"
#include "InventoryWidget.h"

TSubclassOf<class UInventoryWidget> UInventoryWidget::widgetInstance;

UInventoryWidget::UInventoryWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UClass> widgetBP(TEXT("/Game/SGUI/UMG/Inventory.Inventory_C"));
	if (widgetBP.Succeeded()) widgetInstance = widgetBP.Object;
}

UInventoryWidget* UInventoryWidget::Create(APlayerController* masterController)
{
	auto widget = CreateWidget<UInventoryWidget>(masterController, widgetInstance);
	widget->AddToViewport();

	return widget;
}



