#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "NBChatList.generated.h"

UCLASS()
class NUMBERBASEBALL_API UNBChatList : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UListView> ListView_Chat;

  public:
	// 채팅 추가
	void Add(class UNBChatItemData* ChatItemData);

	// 채팅 클리어
	void Clear();
};
