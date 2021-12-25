#include "QuestObjective.h"
#include "Quest.h"

void UQuestObjective::SetObjectiveStatus(bool bIsComplete)
{
	if (bIsComplete && bIsLocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set objective status failed: Objective is locked."));
		return;
	}

	bIsCompleted = bIsComplete;
}
