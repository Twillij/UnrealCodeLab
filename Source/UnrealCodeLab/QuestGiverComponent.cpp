#include "QuestGiverComponent.h"
#include "CustomFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"

UQuestGiverComponent::UQuestGiverComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAssignedQuests();
}

void UQuestGiverComponent::InitAssignedQuests()
{
	UQuestManager* questManager = UCustomFunctionLibrary::GetQuestManager(this);

	if (!questManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Init assigned quests failed: Quest Manager is null."));
		return;
	}

	for (auto questClass : AssignedQuestClasses)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = questManager->GetQuestByClass(questClass);

		// If ptr is null, create a new quest object.
		quest = (quest) ? quest : NewObject<UQuest>(this, questClass);

		// Store the ptr to the array.
		AssignedQuests.Add(quest);
	}
}

UQuest* UQuestGiverComponent::GetQuestByClass(TSubclassOf<UQuest> QuestClass)
{
	for (UQuest* quest : AssignedQuests)
	{
		if (quest->GetClass() == QuestClass)
		{
			return quest;
		}
	}

	return nullptr;
}

UQuest* UQuestGiverComponent::GetQuestByID(FName QuestID)
{
	for (UQuest* quest : AssignedQuests)
	{
		if (quest->QuestID == QuestID)
		{
			return quest;
		}
	}

	return nullptr;
}

TArray<UQuest*> UQuestGiverComponent::GetAssignedQuests()
{
	return AssignedQuests;
}

TArray<UQuest*> UQuestGiverComponent::GetQuestsByStatus(EProgressStatus QuestStatus)
{
	TArray<UQuest*> filteredQuests;

	for (UQuest* quest : AssignedQuests)
	{
		if (quest->GetQuestStatus() == QuestStatus)
		{
			filteredQuests.Add(quest);
		}
	}

	return filteredQuests;
}