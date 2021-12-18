#include "Quest.h"
#include "QuestObjective.h"

void UQuest::Init()
{
	for (auto objectiveClass : QuestObjectiveClasses)
	{
		UQuestObjective* objective = NewObject<UQuestObjective>(this, objectiveClass);
		objective->OwningQuest = this;
		QuestObjectives.Add(objective);
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

const TArray<UQuestObjective*>& UQuest::GetObjectives()
{
	return QuestObjectives;
}

void UQuest::SetQuestStatus(EQuestStatus NewStatus)
{
	if (NewStatus == QuestStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: New status is the same as current status"));
		return;
	}

	QuestStatus = NewStatus;
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

void UQuest::SetObjectiveStatusByID(FName ObjectiveID, bool bIsComplete)
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

bool UQuest::CompareQuestID(UQuest* OtherQuest)
{
	bool bIsUnique = (QuestID.Compare(OtherQuest->QuestID) != 0) ? true : false;
	return bIsUnique;
}
