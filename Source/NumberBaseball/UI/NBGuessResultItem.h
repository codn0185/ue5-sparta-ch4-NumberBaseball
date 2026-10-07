#pragma once

#include "CoreMinimal.h"

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"

#include "NBGuessResultItem.generated.h"

class UTextBlock;

UCLASS()
class NUMBERBASEBALL_API UNBGuessResultItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

  protected:
	// 시도 횟수
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_CurrentTryCount;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_MaxTryCount;

	// 유추 숫자
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_GuessNumber;

	// 유추 결과
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_StrikeCount;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_BallCount;

  protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
