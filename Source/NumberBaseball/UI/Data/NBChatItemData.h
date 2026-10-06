#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "NBChatItemData.generated.h"

USTRUCT()
struct FNBChatData
{
	GENERATED_BODY()

  public:
	// 이름
	UPROPERTY()
	FText NameText;
	UPROPERTY()
	FColor NameColor;

	// 메시지
	UPROPERTY()
	FText MessageText;
	UPROPERTY()
	FColor MessageColor;
};

UCLASS()
class NUMBERBASEBALL_API UNBChatItemData : public UObject
{
	GENERATED_BODY()

  public:
	// 채팅 데이터
	UPROPERTY()
	FNBChatData ChatData;
};
