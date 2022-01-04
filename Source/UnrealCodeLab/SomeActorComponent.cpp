#include "SomeActorComponent.h"
#include "CustomFunctionLibrary.h"
#include "Quest.h"
#include "QuestManager.h"
#include "QuestObjective.h"

USomeActorComponent::USomeActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USomeActorComponent::BeginPlay()
{
	Super::BeginPlay();

	InitRelatedObjectives();
}

void USomeActorComponent::InitRelatedObjectives()
{
	UQuestManager* questManager = UCustomFunctionLibrary::GetQuestManager(this);

	if (!questManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Requesting objective pointers failed: Quest Manager is null."));
		return;
	}

	bool bBindObjectiveSetter = false;

	for (auto objectiveInfo : RelatedObjectivesInfo)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = questManager->GetQuestByClass(objectiveInfo.QuestClass);
		
		// Get objective ptr if Quest is not null, otherwise set objective as null.
		UQuestObjective* objective = (quest) ? quest->GetObjectiveByClass(objectiveInfo.ObjectiveClass) : nullptr;

		if (objective)
		{
			// If ptr exists, store the ptr to the objective info.
			objectiveInfo.Objective = objective;
		}
		else
		{
			// If ptr is null, bind an objective setter function later.
			bBindObjectiveSetter = true;
		}
	}

	if (bBindObjectiveSetter)
	{
		// Set the objective ptrs when its quest is added to the QuestManager.
		questManager->OnAnyQuestAdded.AddDynamic(this, &USomeActorComponent::SetObjectiveByQuest);
	}
}

void USomeActorComponent::SetObjectiveByQuest(UQuest* NewQuest)
{
	for (FQuestObjectiveInfo objectiveInfo : RelatedObjectivesInfo)
	{
		// If the objective ptr already exists, continue to the next objective info.
		if (objectiveInfo.Objective)
		{
			continue;
		}

		// If the objective has the same quest class as the new quest...
		if (objectiveInfo.QuestClass == NewQuest->GetClass())
		{
			// Try to find a matching objective from the quest.
			UQuestObjective* objective = NewQuest->GetObjectiveByClass(objectiveInfo.ObjectiveClass);

			// If a matching objective is found, set it as the new objective ptr.
			objectiveInfo.Objective = (objective) ? objective : nullptr;
		}
	}
}
