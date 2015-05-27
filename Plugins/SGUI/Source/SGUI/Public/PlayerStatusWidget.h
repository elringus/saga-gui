#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

/**
 *  Widget for player status. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UPlayerStatusWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates player status widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Player Status", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|PlayerStatus")
	static UPlayerStatusWidget* Create(UObject* worldContextObject);

	/**
	*  Sets fill amount of the player hp bar.
	*  @param value Fill value. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player HP"), Category = "SagaGUI|PlayerStatus")
	void SetHPFillAmount(const float& value);

	/**
	*  Sets fill amount of the player stamina bar.
	*  @param value Fill value. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player Stamina"), Category = "SagaGUI|PlayerStatus")
	void SetStaminaFillAmount(const float& value);

	/**
	*  Binds fill amount of the hp progress bar.
	*  @param functor The lambda expression, which will be called on every tick to update fill value.
	*    Should return float and take no parameters.
	*/
	template<typename FunctorType>
	FORCEINLINE void BindHPFillAmount(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float deltaTime) override;

private:
	UProgressBar* hpBar;
	UTextBlock* hpLabel;
	UProgressBar* staminaBar;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;
	
	
};
