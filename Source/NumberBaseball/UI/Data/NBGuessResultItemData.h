#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "NBGuessResultItemData.generated.h"

USTRUCT()
struct FNBGuessResultData
{
	GENERATED_BODY()

  public:
	// 시도 횟수
	UPROPERTY()
	int32 CurrentTryCount;
	UPROPERTY()
	int32 MaxTryCount;

	// 유추 숫자
	UPROPERTY()
	FString GuessNumberString;

	// 유추 결과
	UPROPERTY()
	int32 StrikeCount;
	UPROPERTY()
	int32 BallCount;
};

UCLASS()
class NUMBERBASEBALL_API UNBGuessResultItemData : public UObject
{
	GENERATED_BODY()

  public:
	// 유추 결과 데이터
	UPROPERTY()
	FNBGuessResultData GuessResultData;
};
