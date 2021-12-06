#include "Quest.h"
#include "QuestObjective.h"

void UQuest::Init()
{
	for (UQuestObjective* objective : QuestObjectives)
	{
		objective->OwningQuest = this;
	}
}

const FName& UQuest::GetQuestID()
{
	return QuestID;
}

EQuestStatus UQuest::GetQuestStatus()
{
	return QuestStatus;
}

void UQuest::SetQuestStatus(EQuestStatus NewStatus)
{
	if (NewStatus == QuestStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: New status is the same as current status"));
		return;
	}

	QuestStatus = NewStatus;
	OnQuestStatusChanged(NewStatus);
}

void UQuest::SetObjectiveStatusByIndex(int ArrayIndex, bool bIsComplete)
{
	if (ArrayIndex < 0 || ArrayIndex >= QuestObjectives.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Set objective status failed: Invalid index"));
		return;
	}

	QuestObjectives[ArrayIndex]->SetObjectiveStatus(bIsComplete);
}

void UQuest::SetObjectiveStatusByID(const FName& ObjectiveID, bool bIsComplete)
{
	for (UQuestObjective* objective : QuestObjectives)
	{
		if (objective->ObjectiveID == ObjectiveID)
		{
			objective->SetObjectiveStatus(bIsComplete);
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Set objective status failed: Invalid ID"));
}

void UQuest::AddObjective(UQuestObjective* Objective)
{
	if (Objective == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Add quest objective failed: Null quest objective"));
		return;
	}

	QuestObjectives.Add(Objective);
	Objective->OwningQuest = this;
}

bool UQuest::CompareQuestID(UQuest* OtherQuest)
{
	bool bIsUnique = (QuestID.Compare(OtherQuest->QuestID) != 0) ? true : false;
	return bIsUnique;
}
