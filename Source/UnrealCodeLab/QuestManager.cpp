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

const TArray<UQuest*>& UQuestManager::GetAllQuests()
{
	return Quests;
}

const TArray<UQuest*>& UQuestManager::GetTrackedQuests()
{
	return TrackedQuests;
}

TArray<UQuest*> UQuestManager::GetQuestsByStatus(EProgressStatus Status)
{
	TArray<UQuest*> filteredQuests;

	for (UQuest* quest : Quests)
	{
		if (quest->GetQuestStatus() == Status)
		{
			filteredQuests.Add(quest);
		}
	}

	return filteredQuests;
}

UQuest* UQuestManager::GetQuestByClass(TSubclassOf<UQuest> QuestClass)
{
	for (UQuest* quest : Quests)
	{
		if (quest->GetClass() == QuestClass)
		{
			return quest;
		}
	}

	return nullptr;
}

UQuest* UQuestManager::GetQuestByID(FName QuestID)
{
	for (UQuest* quest : Quests)
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
	for (UQuest* quest : Quests)
	{
		if (quest->QuestID == QuestID)
		{
			return true;
		}
	}

	return false;
}

void UQuestManager::AddNewQuest(UQuest* NewQuest, bool bOverwriteDuplicateID)
{
	if (UQuest* quest = GetQuestByID(NewQuest->QuestID))
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
	NewQuest->Init(this);
	OnAnyQuestAdded.Broadcast(NewQuest);
}

void UQuestManager::TrackQuest(UQuest* Quest, bool bReplaceOldest)
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

const TArray<UQuest*>& UQuestManager::SortQuestsByDisplayName()
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
			UQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}

const TArray<UQuest*>& UQuestManager::SortQuestsByID()
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
			UQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}

const TArray<UQuest*>& UQuestManager::SortQuestByStatus()
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
			UQuest* temp = Quests[i];
			Quests[i] = Quests[smallest];
			Quests[smallest] = temp;
		}
	}

	return Quests;
}
