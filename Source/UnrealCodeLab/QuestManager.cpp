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
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const TArray<UQuest*>& AQuestManager::GetQuestsByStatus(EQuestStatus FilteredStatus)
{
	FilteredQuests.Empty();

	for (UQuest* quest : Quests)
	{
		if (quest->GetQuestStatus() == FilteredStatus)
		{
			FilteredQuests.Add(quest);
		}
	}

	return FilteredQuests;
}

void AQuestManager::SetQuestStatusByIndex(int ArrayIndex, EQuestStatus Status)
{
	if (ArrayIndex < 0 || ArrayIndex >= Quests.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Set quest status failed: Invalid index"));
		return;
	}

	Quests[ArrayIndex]->SetQuestStatus(Status);
}

void AQuestManager::SetQuestStatusByID(const FName& QuestID, EQuestStatus Status)
{
	for (UQuest* quest : Quests)
	{
		if (quest->QuestID == QuestID)
		{
			quest->SetQuestStatus(Status);
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Set quest status failed: Invalid ID"));
}

void AQuestManager::AddNewQuest(UQuest* NewQuest)
{
	for (UQuest* quest : Quests)
	{
		if (quest->CompareID(NewQuest))
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding new quest failed: Quest ID already exists"));
			return;
		}
	}

	Quests.Add(NewQuest);
}
