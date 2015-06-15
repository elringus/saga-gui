#pragma once

#include "Blueprint/UserWidget.h"
#include "SagaTextBoxWidget.generated.h"

/**
*  Base widget for text boxes. 
*/
UCLASS()
class SGUI_API USagaTextBoxWidget : public USagaWidget
{
	GENERATED_BODY()

public:
	void InitializeTextBox(UEditableTextBox* textBox);

	/**
	*  Sets text to the text box.
	*  @param text The text for the text box.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Text"), Category = "SagaGUI")
	void SetText(FText text);

	/**
	*  Gets text from the text box.
	*  @return The text kept by the text box.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Text"), Category = "SagaGUI")
	FText GetText();

protected:
	class UEditableTextBox* textBox;

};
