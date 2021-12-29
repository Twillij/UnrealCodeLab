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

bool UQuest::IsStatusBlocked(const FQuestStatusBlockFlags& Flags)
{
	return (QuestStatus == EQuestStatus::Locked && Flags.bBlockLocked) ||
		(QuestStatus == EQuestStatus::Unlocked && Flags.bBlockUnlocked) ||
		(QuestStatus == EQuestStatus::Accepted && Flags.bBlockAccepted) ||
		(QuestStatus == EQuestStatus::Abandoned && Flags.bBlockAbandoned) ||
		(QuestStatus == EQuestStatus::Failed && Flags.bBlockFailed) ||
		(QuestStatus == EQuestStatus::Completed && Flags.bBlockCompleted);
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

bool UQuest::LockQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
	}

	if (!IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Locked;
	OnQuestLocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestLocked.Broadcast(this);

	return true;
}

bool UQuest::UnlockQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
		Flags.bBlockAccepted = true;
		Flags.bBlockAbandoned = true;
		Flags.bBlockFailed = true;
		Flags.bBlockCompleted = true;
	}

	if (IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Unlocked;
	OnQuestUnlocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestUnlocked.Broadcast(this);

	return true;
}

bool UQuest::AcceptQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
		Flags.bBlockAccepted = true;
		Flags.bBlockCompleted = bIsRepeatable ? false : true;
	}

	if (IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlock quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Accepted;
	OnQuestAccepted();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestAccepted.Broadcast(this);

	return true;
}

bool UQuest::AbandonQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
		Flags.bBlockUnlocked = true;
		Flags.bBlockAbandoned = true;
		Flags.bBlockFailed = true;
		Flags.bBlockCompleted = true;
	}

	if (IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Abandon quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Abandoned;
	OnQuestAbandoned();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestAbandoned.Broadcast(this);

	return true;
}

bool UQuest::FailQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
		Flags.bBlockUnlocked = true;
		Flags.bBlockAbandoned = true;
		Flags.bBlockFailed = true;
		Flags.bBlockCompleted = true;
	}

	if (IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Failed;
	OnQuestFailed();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestFailed.Broadcast(this);

	return true;
}

bool UQuest::CompleteQuest(FQuestStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
		Flags.bBlockUnlocked = true;
		Flags.bBlockAbandoned = true;
		Flags.bBlockFailed = true;
		Flags.bBlockCompleted = true;
	}

	if (IsStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Complete quest failed: Quest status is blocked."));
		return false;
	}

	QuestStatus = EQuestStatus::Completed;
	OnQuestCompleted();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyQuestCompleted.Broadcast(this);

	return true;
}

bool UQuest::CompareQuestID(UQuest* OtherQuest)
{
	return (QuestID.Compare(OtherQuest->QuestID) != 0) ? true : false;
}

bool UQuest::CheckUnlockConditions_Implementation()
{
	return true;
}

bool UQuest::CheckCompletionConditions_Implementation()
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

	return bIsCompleted;
}

void UQuest::ResetProgress_Implementation()
{
	for (UQuestObjective* objective : QuestObjectives)
	{
		objective->ResetProgress();
	}
}
