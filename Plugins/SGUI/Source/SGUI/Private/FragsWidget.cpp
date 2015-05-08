#include "SGUI.h"
#include "FragsWidget.h"

UFragsWidget* UFragsWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UFragsWidget>(worldContextObject);

	widget->fragsLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("FragsLabel")));

	return widget;
}

void UFragsWidget::SetFragsCount(int32 value)
{
	fragsLabel->SetText(FText::FromString(FString::Printf(TEXT("Frags: %d"), value)));
}
