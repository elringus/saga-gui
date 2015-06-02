#include "SGUI.h"
#include "ActionTableWidget.h"

UActionTableWidget* UActionTableWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionTableWidget>(worldContextObject);
	if (!widget) return nullptr;

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

USagaTextBoxWidget* UActionTableWidget::AddTextBox(UObject* worldContextObject, FText text, int32 column, int32 row)
{
	auto textBoxWidget = CreateWidget<UUserWidget>(worldContextObject->GetWorld(), TextBoxTemplate);
	textBoxWidget->AddToViewport();

	auto textBox = Cast<USagaTextBoxWidget>(textBoxWidget);
	textBox->InitializeTextBox(Cast<UEditableTextBox>(textBoxWidget->GetWidgetFromName(TEXT("TextBox"))));
	textBox->SetText(text);

	auto slot = actionGrid->AddChildToGrid(textBox);
	slot->SetColumn(column);
	slot->SetRow(row);

	return textBox;
}
