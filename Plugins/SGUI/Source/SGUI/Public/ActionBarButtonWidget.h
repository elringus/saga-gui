#pragma once

#include "Blueprint/UserWidget.h"
#include "ActionBarButtonWidget.generated.h"

/**
*  Widget for action bar button. 
*  Should not be instantiated manually.
*/
UCLASS()
class SGUI_API UActionBarButtonWidget : public USagaButtonWidget
{
	GENERATED_BODY()

	friend class UActionBarWidget;

public:
	virtual void DoClick() override;

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float deltaTime) override;

private:
	class UTextBlock* cdLabel;

	float cd = 0.f;
	float cdTimer = 0.f;

	static UActionBarButtonWidget* Create(UObject* worldContextObject, float cooldown);
};
