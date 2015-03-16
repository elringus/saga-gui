#include "SagaGUI.h"
#include "FloatingBarWidget.h"

TSubclassOf<class UFloatingBarWidget> UFloatingBarWidget::widgetInstance;

UFloatingBarWidget::UFloatingBarWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/FloatingBar.FloatingBar'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UFloatingBarWidget* UFloatingBarWidget::Create(APlayerController* masterController)
{
	return CreateWidget<UFloatingBarWidget>(masterController, widgetInstance);
}

void UFloatingBarWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();


}


