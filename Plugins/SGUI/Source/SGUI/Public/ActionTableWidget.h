#pragma once

#include "Blueprint/UserWidget.h"
#include "ActionTableWidget.generated.h"

/**
 *  Widget for action table. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UActionTableWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/* Prototype for the text labels created on AddTextLabel() calls. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	TSubclassOf<UUserWidget> TextLabelTemplate;

	/* Prototype for the buttons created on AddButton() calls. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	TSubclassOf<UUserWidget> ButtonTemplate;

	/* Prototype for the text boxes created on AddTextBox() calls. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	TSubclassOf<UUserWidget> TextBoxTemplate;

	/**
	*  Creates action table widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Action Table",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionTable")
	static UActionTableWidget* Create(UObject* worldContextObject);

	/**
	*  Adds a text label to the table. 
	*  @param worldContextObject Any UObject to get world context from.
	*  @param labelText The text to show on the added label.
	*  @param column ID of the column where label will be kept.
	*  @param row ID of the row where label will be kept.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Text Label",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionTable")
	void AddTextLabel(UObject* worldContextObject, FText labelText, int32 column = 0, int32 row = 0);

	/**
	*  Adds a button to the table.
	*  To implement OnClick event, use the returned USagaButtonWidget instance.
	*  @param worldContextObject Any UObject to get world context from.
	*  @param buttonTexture The texture to use for the action button.
	*  @param tooltipTxt The tooltip text to show on hover for the action button.
	*  @param column ID of the column where button will be kept.
	*  @param row ID of the row where button will be kept.
	*  @return Instance of the created button.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Button",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionTable")
	USagaButtonWidget* AddButton(UObject* worldContextObject, UTexture2D* buttonTexture = nullptr, 
									FText tooltipTxt = FText::FromString(TEXT("")), int32 column = 0, int32 row = 0);

	/**
	*  Adds a text box to the table.
	*  You may use the returned UTextBoxWidget instance to set and get text.
	*  @param worldContextObject Any UObject to get world context from.
	*  @param text The initial text to set for the text box.
	*  @param column ID of the column where text box will be kept.
	*  @param row ID of the row where text box will be kept.
	*  @return Instance of the created text box.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Text Box",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionTable")
	USagaTextBoxWidget* AddTextBox(UObject* worldContextObject, FText text = FText::FromString(TEXT("")), int32 column = 0, int32 row = 0);

private:
	class UGridPanel* actionGrid;
	
};
