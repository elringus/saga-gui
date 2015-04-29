#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 *  Widget for player HP. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UPlayerHPWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates player hp bar widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Player HP Bar", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|PlayerHPBar")
	static UPlayerHPWidget* Create(UObject* worldContextObject);

	/**
	*  Sets fill amount of the player hp bar.
	*  @param value Fill value. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player HP"), Category = "SagaGUI|PlayerHPBar")
	void SetFillAmount(const float& value);

	/**
	*  Binds fill amount of the progress bar.
	*  @param functor The lambda expression, which will be called on every tick to update fill value.
	*  Should return float and take no parameters.
	*/
	template<typename FunctorType>
	FORCEINLINE void BindFillAmount(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float inDeltaTime) override;

private:
	UProgressBar* hpBar;
	UTextBlock* hpLabel;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;
	
	
};
