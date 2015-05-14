#include "SGUI.h"
#include "SagaButtonWidget.h"

void USagaButtonWidget::InitializeButton(UButton* button)
{
	this->button = button;
	button->OnClicked.AddUniqueDynamic(this, &USagaButtonWidget::DoClick);
}

void USagaButtonWidget::DoClick()
{
	if (OnSagaButtonClicked.IsBound())
		OnSagaButtonClicked.Broadcast();
}

void USagaButtonWidget::SetTexture(UTexture2D* texture)
{
	//const auto size = FVector2D(texture->GetSizeX(), texture->GetSizeY());
	//auto path = texture->GetPathName();
	//path.Split(TEXT("."), &path, nullptr);
	//path.Append(TEXT(".png"));

	//auto sagaGUIResources = FSlateGameResources::New(FName("SagaGUIResources"), "/Game/SGUI/ActionBar/Textures", "/Game/SGUI/ActionBar/Textures");
	//FSlateStyleRegistry::RegisterSlateStyle(sagaGUIResources.Get());

	//FSlateImageBrush brush = FSlateImageBrush(*sagaGUIResources.Get().GetDynamicImageBrush(FName("DefaultButton")));
	//brush.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());
	//actionButton->WidgetStyle.SetNormal(brush);
	//actionButton->WidgetStyle.Hovered.SetResourceObject(texture);
	//actionButton->WidgetStyle.Pressed.SetResourceObject(texture);
	//actionButton->WidgetStyle.Disabled.SetResourceObject(texture);
}

void USagaButtonWidget::SetTooltip(FText text)
{
	if (button) button->SetToolTipText(text);
}
