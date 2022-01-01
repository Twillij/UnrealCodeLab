#include "Quest.h"
#include "CustomFunctionLibrary.h"
#include "QuestManager.h"
#include "QuestObjective.h"
#include "QuestRewards.h"

void UQuest::Init()
{
	for (auto objectiveClass : QuestObjectiveClasses)
	{
		UQuestObjective* objective = NewObject<UQuestObjective>(this, objectiveClass);
		objective->OwningQuest = this;
		QuestObjectives.Add(objective);
	}
}

bool UQuest::IsQuestStatusBlocked(const FProgressStatusBlockFlags& Flags)
{
	return (QuestStatus == EProgressStatus::Locked && Flags.bBlockLocked) ||
		(QuestStatus == EProgressStatus::Unlocked && Flags.bBlockUnlocked) ||
		(QuestStatus == EProgressStatus::Started && Flags.bBlockStarted) ||
		(QuestStatus == EProgressStatus::Abandoned && Flags.bBlockAbandoned) ||
		(QuestStatus == EProgressStatus::Failed && Flags.bBlockFailed) ||
		(QuestStatus == EProgressStatus::Completed && Flags.bBlockCompleted);
}

EProgressStatus UQuest::GetQuestStatus()
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

bool UQuest::LockQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::UnlockQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::StartQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::AbandonQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::FailQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::CompleteQuest(FProgressStatusBlockFlags Flags)
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

bool UQuest::CompareQuestID(UQuest* OtherQuest)
{
	return (QuestID.Compare(OtherQuest->QuestID) != 0) ? true : false;
}

bool UQuest::CheckCompletionConditions_Implementation()
{
	bool bIsCompleted = true;

	for (UQuestObjective* objective : QuestObjectives)
	{
		if (objective->GetObjectiveStatus() != EProgressStatus::Completed)
		{
			bIsCompleted = false;
			break;
		}
	}

	return bIsCompleted;
}

void UQuest::OnQuestUpdated_Implementation()
{
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestUpdated.Broadcast(this);
	TimeLastUpdated = FDateTime::UtcNow();
}

void UQuest::ResetProgress_Implementation()
{
	for (UQuestObjective* objective : QuestObjectives)
	{
		objective->ResetProgress();
	}
}
