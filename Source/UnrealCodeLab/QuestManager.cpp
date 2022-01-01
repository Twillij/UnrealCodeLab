#include "QuestManager.h"
#include "Quest.h"
#include "QuestObjective.h"

// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();

#if !UE_BUILD_SHIPPING
	for (int i = 0; i < Quests.Num(); ++i)
	{
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			if (Quests[i]->CompareQuestID(Quests[j]))
			{
				UE_LOG(LogTemp, Warning, TEXT("Found a duplicate quest ID: %s"), *Quests[i]->QuestID.ToString());
			}
		}
	}
#endif
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const TArray<AQuest*>& AQuestManager::GetAllQuests()
{
	return Quests;
}

const TArray<AQuest*>& AQuestManager::GetQuestsByStatus(EProgressStatus Status)
{
	FilteredQuests.Empty();

	for (AQuest* quest : Quests)
	{
		if (quest->GetQuestStatus() == Status)
		{
			FilteredQuests.Add(quest);
		}
	}

	return FilteredQuests;
}

AQuest* AQuestManager::GetQuestByID(FName QuestID)
{
	for (AQuest* quest : Quests)
	{
		if (quest->QuestID == QuestID)
		{
			return quest;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Get quest failed: Invalid ID"));
	return nullptr;
}

void AQuestManager::AddNewQuest(AQuest* NewQuest, bool bOverwriteDuplicateID)
{
	for (AQuest* quest : Quests)
	{
		if (quest->CompareQuestID(NewQuest))
		{
			if (bOverwriteDuplicateID)
			{
				Quests.Remove(quest);
				break;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding new quest failed: Quest ID already exists"));
				return;
			}
		}
	}

	Quests.Add(NewQuest);
	NewQuest->Init();
}

const TArray<AQuest*>& AQuestManager::SortQuestsByDisplayName()
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

const TArray<AQuest*>& AQuestManager::SortQuestsByID()
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

const TArray<AQuest*>& AQuestManager::SortQuestByStatus()
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
