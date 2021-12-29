#include "QuestObjective.h"
#include "CustomFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"

bool UQuestObjective::IsObjectiveStatusBlocked(const FProgressStatusBlockFlags& Flags)
{
	return (ObjectiveStatus == EProgressStatus::Locked && Flags.bBlockLocked) ||
		(ObjectiveStatus == EProgressStatus::Unlocked && Flags.bBlockUnlocked) ||
		(ObjectiveStatus == EProgressStatus::Started && Flags.bBlockStarted) ||
		(ObjectiveStatus == EProgressStatus::Abandoned && Flags.bBlockAbandoned) ||
		(ObjectiveStatus == EProgressStatus::Failed && Flags.bBlockFailed) ||
		(ObjectiveStatus == EProgressStatus::Completed && Flags.bBlockCompleted);
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

bool UQuestObjective::LockObjective(FProgressStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockLocked = true;
	}

	if (!IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Locked;
	OnObjectiveLocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveLocked.Broadcast(this);

	return true;
}

bool UQuestObjective::UnlockObjective(FProgressStatusBlockFlags Flags)
{
	if (Flags.bUseDefaultFlags)
	{
		Flags.bBlockStarted = true;
		Flags.bBlockAbandoned = true;
		Flags.bBlockFailed = true;
		Flags.bBlockCompleted = true;
	}

	if (!IsObjectiveStatusBlocked(Flags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lock objective failed: Objective status is blocked."));
		return false;
	}

	ObjectiveStatus = EProgressStatus::Unlocked;
	OnObjectiveUnlocked();
	UCustomFunctionLibrary::GetQuestManager(this)->OnAnyObjectiveUnlocked.Broadcast(this);

	return true;
}

bool UQuestObjective::CheckCompletionConditions_Implementation()
{
	return true;
}