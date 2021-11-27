#include "Quest.h"
#include "QuestObjective.h"

void UQuest::SetQuestStatus(bool bIsComplete)
{
	// If the quest completion status has changed
	if (bIsComplete != bIsCompleted)
	{
		OnQuestComplete();
		bIsCompleted = bIsComplete;
	}
}
