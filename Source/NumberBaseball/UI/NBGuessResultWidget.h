#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBGuessResultWidget.generated.h"

struct FNBGuessResultData;

UCLASS()
class NUMBERBASEBALL_API UNBGuessResultWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> ListView_GuessResult;

  public:
	void Add(const FNBGuessResultData& GuessResultData);

	void Clear();
};
