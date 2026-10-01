#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class NUMBERBASEBALL_API UNBChatInput : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
};
