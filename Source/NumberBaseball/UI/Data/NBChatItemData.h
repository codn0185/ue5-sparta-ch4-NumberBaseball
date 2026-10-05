#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "NBChatItemData.generated.h"

UCLASS()
class NUMBERBASEBALL_API UNBChatItemData : public UObject
{
	GENERATED_BODY()

  public:
	// 이름
	FText NameText;
	FColor NameColor;

	// 메시지
	FText MessageText;
	FColor MessageColor;
};
