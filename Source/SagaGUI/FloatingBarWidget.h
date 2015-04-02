#pragma once

#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 *	Widget for floating bars. Institiates with the static Create() method.
 */
UCLASS()
class SAGAGUI_API UFloatingBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFloatingBarWidget(const class FObjectInitializer& objectInitializer);

	/************************************************************************/
	/* Blueprint parameters                                                 */
	/************************************************************************/

	/* Hide the widget, when distane between follow target and the master controller is more than this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating bar parameters")
	float VisibleRadius = 1500.f;

	/* Speed of revealing\hiding the widget, controlled by visible radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating bar parameters")
	float VisibilityTransitionSpeed = 5.f;

	/************************************************************************/
	/* Public API                                                           */
	/************************************************************************/

	/** 
	 *	Creates the widget and adds it to the viewport.
	 *	@param masterController Controller of the player, that will own the widget.
	 *	@param followTarget An actor, which the widget will allign itsels with.
	 *	@param offset Offset to the follow target location in world space.
	 *	@return Instance of the created widget.
	 */
	static UFloatingBarWidget* Create(APlayerController* masterController, AActor* followTarget, FVector offset);

	/**
	 *	Sets the fill amount of the progress bar. 
	 *	@param value Fill value. Should be in 0.0 to 1.0 range.
	 */
	FORCEINLINE void SetFillAmount(const float& value) { floatingBar->SetPercent(value); }
	
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
	static TSubclassOf<class UFloatingBarWidget> widgetInstance;

	UPROPERTY() UProgressBar* floatingBar;
	UPROPERTY() AActor* followTarget;
	UPROPERTY() AController* masterController;
	UPROPERTY() AActor* masterActor;
	UPROPERTY() FVector offset;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;
};
