#include "UI/NBChatList.h"

#include "Components/ListView.h"
#include "UI/Data/NBChatItemData.h"

void UNBChatList::Add(UNBChatItemData* ChatItemData)
{
	if (!IsValid(ChatItemData))
	{
		return;
	}

	if (!IsValid(ListView_Chat))
	{
		return;
	}

	ListView_Chat->AddItem(ChatItemData);
}

void UNBChatList::Clear()
{
	if (!IsValid(ListView_Chat))
	{
		return;
	}

	ListView_Chat->ClearListItems();
}
