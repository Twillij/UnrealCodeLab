#include "QuestObjective.h"

void UQuestObjective::SetObjectiveStatus(bool bIsComplete)
{
	// If the objective completion status has changed
	if (bIsComplete != bIsCompleted)
	{
		OnObjectiveComplete();
		bIsCompleted = bIsComplete;
	}
}
