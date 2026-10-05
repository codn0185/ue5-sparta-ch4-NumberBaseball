#pragma once

#include "CoreMinimal.h"

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"

#include "NBChatItem.generated.h"

class UTextBlock;

UCLASS()
class NUMBERBASEBALL_API UNBChatItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Name;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Message;

  protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
