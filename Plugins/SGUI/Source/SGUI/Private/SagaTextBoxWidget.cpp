#include "SGUI.h"
#include "SagaTextBoxWidget.h"

void USagaTextBoxWidget::InitializeTextBox(UEditableTextBox* textBox)
{
	this->textBox = textBox;
}

void USagaTextBoxWidget::SetText(FText text)
{
	if (textBox) textBox->SetText(text);
}

FText USagaTextBoxWidget::GetText()
{
	if (textBox) return textBox->GetText();
	else return FText::GetEmpty();
}