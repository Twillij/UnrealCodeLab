#include "QuestMarker.h"
#include "CustomFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"

AQuestMarker::AQuestMarker()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AQuestMarker::BeginPlay()
{
	Super::BeginPlay();

	if (bSetRootObjectAsQuestGiver)
	{
		//QuestGiver = this.parent
	}

	InitAssignedQuests();
}

void AQuestMarker::InitAssignedQuests_Implementation()
{
	UQuestManager* questManager = UCustomFunctionLibrary::GetQuestManager(this);

	if (!questManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Requesting quest pointers failed: Quest Manager is null."));
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

TArray<UQuest*> AQuestMarker::GetAssignedQuests_Implementation()
{
	return AssignedQuests;
}