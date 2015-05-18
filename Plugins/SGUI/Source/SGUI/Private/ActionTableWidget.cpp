#include "SGUI.h"
#include "ActionTableWidget.h"

UActionTableWidget* UActionTableWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionTableWidget>(worldContextObject);

	widget->actionGrid = Cast<UGridPanel>(widget->GetWidgetFromName(TEXT("ActionGrid")));

	return widget;
}

void UActionTableWidget::AddTextLabel(UObject* worldContextObject, FText labelText, int32 column, int32 row)
{
	auto textLabelWidget = CreateWidget<UUserWidget>(worldContextObject->GetWorld(), TextLabelTemplate);
	textLabelWidget->AddToViewport();

	auto textLabel = Cast<UTextBlock>(textLabelWidget->GetWidgetFromName(TEXT("TextLabel")));
	textLabel->SetText(labelText);

	auto slot = actionGrid->AddChildToGrid(textLabel);
	slot->SetColumn(column);
	slot->SetRow(row);
}

USagaButtonWidget* UActionTableWidget::AddButton(UObject* worldContextObject, UTexture2D* buttonTexture, FText tooltipTxt, int32 column, int32 row)
{
	auto buttonWidget = CreateWidget<UUserWidget>(worldContextObject->GetWorld(), ButtonTemplate);
	buttonWidget->AddToViewport();

	auto button = Cast<USagaButtonWidget>(buttonWidget);
	button->InitializeButton(Cast<UButton>(buttonWidget->GetWidgetFromName(TEXT("Button"))));
	if (buttonTexture) button->SetTexture(buttonTexture);
	button->SetTooltip(tooltipTxt);

	auto slot = actionGrid->AddChildToGrid(button);
	slot->SetColumn(column);
	slot->SetRow(row);

	return button;
}

