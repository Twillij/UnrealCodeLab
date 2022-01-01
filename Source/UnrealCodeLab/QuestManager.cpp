#include "QuestManager.h"
#include "Quest.h"
#include "QuestObjective.h"

void UQuestManager::Init()
{
#if !UE_BUILD_SHIPPING
	for (int i = 0; i < Quests.Num(); ++i)
	{
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			if (Quests[i]->QuestID == Quests[j]->QuestID)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found a duplicate quest ID: %s"), *Quests[i]->QuestID.ToString());
			}
		}
	}
#endif
}

const TArray<AQuest*>& UQuestManager::GetAllQuests()
{
	return Quests;
}

const TArray<AQuest*>& UQuestManager::GetTrackedQuests()
{
	return TrackedQuests;
}

TArray<AQuest*> UQuestManager::GetQuestsByStatus(EProgressStatus Status)
{
	TArray<AQuest*> filteredQuests;

	for (AQuest* quest : Quests)
	{
		if (quest->GetQuestStatus() == Status)
		{
			filteredQuests.Add(quest);
		}
	}

	return filteredQuests;
}

AQuest* UQuestManager::GetQuestByID(FName QuestID)
{
	for (AQuest* quest : Quests)
	{
		if (quest->QuestID == QuestID)
		{
			return quest;
		}
	}

	return nullptr;
}

bool UQuestManager::DoesQuestIDExist(FName QuestID)
{
	for (AQuest* quest : Quests)
	{
		if (quest->QuestID == QuestID)
		{
			return true;
		}
	}

	return false;
}

void UQuestManager::AddNewQuest(AQuest* NewQuest, bool bOverwriteDuplicateID)
{
	if (AQuest* quest = GetQuestByID(NewQuest->QuestID))
	{
		if (bOverwriteDuplicateID)
		{
			Quests.Remove(quest);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Add new quest failed: Quest ID already exists"));
			return;
		}
	}

	Quests.Add(NewQuest);
}

void UQuestManager::TrackQuest(AQuest* Quest, bool bReplaceOldest)
{
	if (TrackedQuests.Num() >= MaxTrackedQuests)
	{
		if (bReplaceOldest && TrackedQuests.Num() > 0)
		{
			TrackedQuests.RemoveAt(0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Track quest failed: Max tracked quests reached."));
			return;
		}
	}

	TrackedQuests.Add(Quest);
}

const TArray<AQuest*>& UQuestManager::SortQuestsByDisplayName()
{
	// Use selection sort
	for (int i = 0; i < Quests.Num(); ++i)
	{
		FText displayName = Quests[i]->QuestDisplayName;
		int smallest = i;

		displayName.CompareTo(displayName);

		// Find the index of quest with smallest ID value in the array
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			// If the compared ID has a smaller value, then change the index
			smallest = (displayName.CompareTo(Quests[j]->QuestDisplayName) < 0) ? smallest : j;
		}

		if (i != smallest)
		{
			// Swap the index of the array elements
			AQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}

const TArray<AQuest*>& UQuestManager::SortQuestsByID()
{
	// Use selection sort
	for (int i = 0; i < Quests.Num(); ++i)
	{
		FName id = Quests[i]->QuestID;
		int smallest = i;

		// Find the index of quest with smallest ID value in the array
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			// If the compared ID has a smaller value, then change the index
			smallest = (id.LexicalLess(Quests[j]->QuestID)) ? smallest : j;
		}

		if (i != smallest)
		{
			// Swap the index of the array elements
			AQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}

const TArray<AQuest*>& UQuestManager::SortQuestByStatus()
{
	// Use selection sort
	for (int i = 0; i < Quests.Num(); ++i)
	{
		EProgressStatus status = Quests[i]->GetQuestStatus();
		int smallest = i;

		// If the status is already the smallest enum value, skip the sort
		if (status == EProgressStatus())
		{
			continue;
		}

		// Find the index of quest with smallest status enum value in the array
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			// If the compared status has a smaller enum value, then change the index
			smallest = (status > Quests[j]->GetQuestStatus()) ? j : smallest;
		}

		if (i != smallest)
		{
			// Swap the index of the array elements
			AQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}
