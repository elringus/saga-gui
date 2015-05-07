#pragma once

#include "Blueprint/UserWidget.h"
#include "GroupMemberWidget.generated.h"

/**
*  Widget for group member. 
*  Should not be instantiated manually.
*/
UCLASS()
class SGUI_API UGroupMemberWidget : public USagaWidget
{
	GENERATED_BODY()

	friend class UGroupStatusWidget;

public:
	/**
	*  Sets fill amount of the group member hp bar.
	*  @param value Fill value. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Group Member HP"), Category = "SagaGUI|GroupStatus")
	void SetHPFillAmount(const float& value);

private:
	static UGroupMemberWidget* Create(UObject* worldContextObject, FText memberName);

	class UProgressBar* hpBar;
	class UTextBlock* hpLabel;
	class UTextBlock* nameLabel;
};
