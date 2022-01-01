#include "Quest.h"
#include "CustomFunctionLibrary.h"
#include "QuestManager.h"
#include "QuestObjective.h"
#include "QuestRewards.h"

bool AQuest::IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags)
{
	return (QuestStatus == EProgressStatus::Locked && Flags.bBlockLocked) ||
		(QuestStatus == EProgressStatus::Unlocked && Flags.bBlockUnlocked) ||
		(QuestStatus == EProgressStatus::Started && Flags.bBlockStarted) ||
		(QuestStatus == EProgressStatus::Abandoned && Flags.bBlockAbandoned) ||
		(QuestStatus == EProgressStatus::Failed && Flags.bBlockFailed) ||
		(QuestStatus == EProgressStatus::Completed && Flags.bBlockCompleted);
}

EProgressStatus AQuest::GetQuestStatus()
{
	return QuestStatus;
}

UQuestObjective* AQuest::GetObjectiveByID(FName ObjectiveID)
{
	for (UQuestObjective* objective : Objectives)
	{
		if (objective->ObjectiveID == ObjectiveID)
		{
			return objective;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not find objective ID: %s"), *ObjectiveID.ToString());
	return nullptr;
}

const TArray<UQuestObjective*>& AQuest::GetObjectives()
{
	return Objectives;
}

const TArray<UQuestObjective*>& AQuest::GetActiveObjectiveGroup()
{
	return ActiveObjectiveGroup;
}

TArray<UQuestObjective*> AQuest::GetObjectivesByGroupIndex(int Index, bool bEqualsIndex)
{
	TArray<UQuestObjective*> groupedObjectives;

	if (Index < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get objectives by group index failed: Invalid objective group index %i"), Index);
	}

	for (UQuestObjective* objective : Objectives)
	{
		if (bEqualsIndex && objective->ObjectiveGroupIndex == Index)
		{
			groupedObjectives.Add(objective);
		}
		else if (!bEqualsIndex && objective->ObjectiveGroupIndex != Index)
		{
			groupedObjectives.Add(objective);
		}
	}

	return groupedObjectives;
}

void AQuest::SetActiveObjectiveGroup(int GroupIndex, bool bHideInactiveGroups)
{
	if (GroupIndex < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get objectives by group index failed: Invalid objective group index %i"), GroupIndex);
		return;
	}

	TArray<UQuestObjective*> newActiveObjectives = GetObjectivesByGroupIndex(GroupIndex);
	
	if (newActiveObjectives.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Get objectives by group index failed: Cannot find objectives of group index %i"), GroupIndex);
		return;
	}

	if (bHideInactiveGroups)
	{
		for (UQuestObjective* objective : Objectives)
		{
			objective->bIsHidden = (objective->ObjectiveGroupIndex != GroupIndex) ? true : objective->bIsHidden;
		}
	}

	ActiveObjectiveGroup = newActiveObjectives;
}

bool AQuest::SetQuestStatus(EProgressStatus NewStatus, FProgressStatusBlockFlags Flags)
{
	if (QuestStatus == NewStatus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set quest status failed: Passed status is the same as current status"));
		return false;
	}
	else if (NewStatus == EProgressStatus::Locked)
	{
		return LockQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Unlocked)
	{
		return UnlockQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Started)
	{
		return StartQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Abandoned)
	{
		return AbandonQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Failed)
	{
		return FailQuest(Flags);
	}
	else if (NewStatus == EProgressStatus::Completed)
	{
		return CompleteQuest(Flags);
	}

	return false;
}

bool AQuest::LockQuest(FProgressStatusBlockFlags Flags)
{
	if (!IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Locked;
	OnQuestLocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestLocked.Broadcast(this);

	return true;
}

bool AQuest::UnlockQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Unlocked;
	OnQuestUnlocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestUnlocked.Broadcast(this);

	return true;
}

bool AQuest::StartQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Started;
	OnQuestStarted();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestStarted.Broadcast(this);
	TimeLastStarted = FDateTime::UtcNow();

	return true;
}

bool AQuest::AbandonQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Abandon quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Abandoned;
	OnQuestAbandoned();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestAbandoned.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool AQuest::FailQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Failed;
	OnQuestFailed();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestFailed.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();

	return true;
}

bool AQuest::CompleteQuest(FProgressStatusBlockFlags Flags)
{
	if (IsQuestStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Complete quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EProgressStatus::Completed;
	OnQuestCompleted();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestCompleted.Broadcast(this);
	TimeLastCompleted = FDateTime::UtcNow();

	return true;
}

bool AQuest::CheckCompletionConditions_Implementation()
{
	bool bIsCompleted = true;

	for (UQuestObjective* objective : Objectives)
	{
		if (objective->GetObjectiveStatus() != EProgressStatus::Completed)
		{
			bIsCompleted = false;
			break;
		}
	}

	return bIsCompleted;
}

void AQuest::OnQuestUpdated_Implementation()
{
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestUpdated.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();
}

void AQuest::ResetProgress_Implementation()
{
	for (UQuestObjective* objective : Objectives)
	{
		objective->ResetProgress();
	}
}

void AQuest::BeginPlay()
{
	Super::BeginPlay();

	for (auto objectiveClass : QuestObjectiveClasses)
	{
		UQuestObjective* objective = NewObject<UQuestObjective>(this, objectiveClass);
		objective->OwningQuest = this;
		Objectives.Add(objective);
	}
}
