#include "QuestObjective.h"
#include "Quest.h"

UQuest* UQuestObjective::GetOwningQuest()
{
	if (!OwningQuest->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Objective does not have an owning quest. Is this intended?"))
	}

	return OwningQuest;
}

void UQuestObjective::SetObjectiveStatus(bool bIsComplete)
{
	if (bIsComplete && bIsLocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set objective status failed: Objective is locked."));
		return;
	}

	bIsCompleted = bIsComplete;
}
