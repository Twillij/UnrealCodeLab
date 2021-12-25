#include "Quest.h"
#include "CustomFunctionLibrary.h"
#include "QuestManager.h"
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

void UQuest::OnQuestStatusChanged(EQuestStatus NewStatus)
{
	if (NewStatus == EQuestStatus::Locked)
	{
		OnQuestLocked();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestLocked.Broadcast(this);
	}
	else if (NewStatus == EQuestStatus::Unlocked)
	{
		OnQuestUnlocked();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestUnlocked.Broadcast(this);
	}
	else if (NewStatus == EQuestStatus::Accepted)
	{
		OnQuestAccepted();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestAccepted.Broadcast(this);
	}
	else if (NewStatus == EQuestStatus::Abandoned)
	{
		OnQuestAbandoned();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestAbandoned.Broadcast(this);
	}
	else if (NewStatus == EQuestStatus::Failed)
	{
		OnQuestFailed();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestFailed.Broadcast(this);
	}
	else if (NewStatus == EQuestStatus::Completed)
	{
		OnQuestCompleted();
		UCustomFunctionLibrary::GetQuestManager(this)->OnQuestCompleted.Broadcast(this);
	}
}

EQuestStatus UQuest::GetQuestStatus()
{
	return QuestStatus;
}

UQuestObjective* UQuest::GetObjectiveByID(FName ObjectiveID)
{
	for (UQuestObjective* objective : QuestObjectives)
	{
		if (objective->ObjectiveID == ObjectiveID)
		{
			return objective;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not find objective ID: %s"), *ObjectiveID.ToString());
	return nullptr;
}

const TArray<UQuestObjective*>& UQuest::GetObjectives()
{
	return QuestObjectives;
}

void UQuest::SetQuestStatus(EQuestStatus NewStatus, bool bIgnoreLock)
{
	if (QuestStatus == NewStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: New status is the same as current status."));
		return;
	}
	else if (QuestStatus == EQuestStatus::Locked && !bIgnoreLock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: Quest is currently locked."));
		return;
	}

	QuestStatus = NewStatus;

	OnQuestStatusChanged(NewStatus);
}

bool UQuest::CheckQuestComplete(bool bSetCompleted)
{
	bool bIsCompleted = true;

	for (UQuestObjective* objective : QuestObjectives)
	{
		if (!objective->bIsCompleted)
		{
			bIsCompleted = false;
			break;
		}
	}

	if (bSetCompleted)
		SetQuestStatus(EQuestStatus::Completed);

	return bIsCompleted;
}

bool UQuest::CompareQuestID(UQuest* OtherQuest)
{
	return (QuestID.Compare(OtherQuest->QuestID) != 0) ? true : false;
}
