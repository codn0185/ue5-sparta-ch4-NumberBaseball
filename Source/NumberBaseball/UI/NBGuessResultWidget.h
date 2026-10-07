#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBGuessResultWidget.generated.h"

UCLASS()
class NUMBERBASEBALL_API UNBGuessResultWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> ListView_GuessResult;

  public:
	void Add(const FString GuessNumberString, const int32 StrikeCount, const int32 BallCount);

	void Clear();
};
