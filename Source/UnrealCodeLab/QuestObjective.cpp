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
	if (bIsComplete == bIsCompleted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set objective status failed: New status is the same as current status"));
		return;
	}

	bIsCompleted = bIsComplete;
	OnObjectiveComplete();
}
