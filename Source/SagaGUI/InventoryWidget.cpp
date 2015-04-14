#include "SagaGUI.h"
#include "InventoryWidget.h"

TSubclassOf<class UInventoryWidget> UInventoryWidget::widgetInstance;

UInventoryWidget::UInventoryWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/Inventory.Inventory'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UInventoryWidget* UInventoryWidget::Create(APlayerController* masterController)
{
	auto widget = CreateWidget<UInventoryWidget>(masterController, widgetInstance);
	widget->AddToViewport();

	return widget;
}



