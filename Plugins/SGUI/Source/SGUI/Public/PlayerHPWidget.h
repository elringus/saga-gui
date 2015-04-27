#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 *	Widget for player HP. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UPlayerHPWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*	Creates the widget and adds it to the viewport.
	*	@param masterController Controller of the player, that will own the widget.
	*	@return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|PlayerHPWidget")
	static UPlayerHPWidget* Create(APlayerController* masterController);

	/**
	*	Sets the fill amount of the progress bar.
	*	@param value Fill value. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|PlayerHPWidget")
	void SetFillAmount(const float& value);

	/**
	*	Binds the fill amount of the progress bar.
	*	@param functor The lambda expression, which will be called on every tick to update fill value.
	*	Should return float and take no parameters.
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
