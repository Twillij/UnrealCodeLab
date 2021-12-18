#include "QuestManager.h"

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

	for (int i = 0; i < Quests.Num(); ++i)
	{
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			if (Quests[i]->CompareQuestID(Quests[j]))
			{
				UE_LOG(LogTemp, Warning, TEXT("Found a duplicate quest ID: %s"), *Quests[i]->GetQuestID().ToString());
			}
		}
	}
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const TArray<UQuest*>& AQuestManager::GetAllQuests()
{
	return Quests;
}

const TArray<UQuest*>& AQuestManager::GetQuestsByStatus(EQuestStatus Status)
{
	FilteredQuests.Empty();

	for (UQuest* quest : Quests)
	{
		if (quest->GetQuestStatus() == Status)
		{
			FilteredQuests.Add(quest);
		}
	}

	return FilteredQuests;
}

UQuest* AQuestManager::GetQuestByID(FName QuestID)
{
	for (UQuest* quest : Quests)
	{
		if (quest->GetQuestID() == QuestID)
		{
			return quest;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Get quest failed: Invalid ID"));
	return nullptr;
}

EQuestStatus AQuestManager::GetQuestStatus(FName QuestID)
{
	if (UQuest* quest = GetQuestByID(QuestID))
	{
		return quest->GetQuestStatus();
	}

	return EQuestStatus();
}

void AQuestManager::SetQuestStatus(FName QuestID, EQuestStatus Status)
{
	if (UQuest* quest = GetQuestByID(QuestID))
	{
		quest->SetQuestStatus(Status);
	}
}

void AQuestManager::AddNewQuest(UQuest* NewQuest)
{
	for (UQuest* quest : Quests)
	{
		if (quest->CompareQuestID(NewQuest))
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding new quest failed: Quest ID already exists"));
			return;
		}
	}

	Quests.Add(NewQuest);
	NewQuest->Init();
}

const TArray<UQuest*>& AQuestManager::SortQuestsByDisplayName()
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

const TArray<UQuest*>& AQuestManager::SortQuestsByID()
{
	// Use selection sort
	for (int i = 0; i < Quests.Num(); ++i)
	{
		FName id = Quests[i]->GetQuestID();
		int smallest = i;

		// Find the index of quest with smallest ID value in the array
		for (int j = i + 1; j < Quests.Num(); ++j)
		{
			// If the compared ID has a smaller value, then change the index
			smallest = (id.LexicalLess(Quests[j]->GetQuestID())) ? smallest : j;
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

const TArray<UQuest*>& AQuestManager::SortQuestByStatus()
{
	// Use selection sort
	for (int i = 0; i < Quests.Num(); ++i)
	{
		EQuestStatus status = Quests[i]->GetQuestStatus();
		int smallest = i;

		// If the status is already the smallest enum value, skip the sort
		if (status == EQuestStatus::Available)
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
