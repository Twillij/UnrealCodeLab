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
	UCustomFunctionLibrary::GetQuestManager(this)->OnQuestLocked.Broadcast(this);

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
	OnQuestLocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnQuestUnlocked.Broadcast(this);

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
	UCustomFunctionLibrary::GetQuestManager(this)->OnQuestAccepted.Broadcast(this);

	return false;
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
