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

	for (auto questObjectiveClass : RelatedQuestObjectiveClasses)
	{
		// Get quest ptr from the QuestManager.
		UQuest* quest = questManager->GetQuestByClass(questObjectiveClass.Key);
		
		// Get objective ptr if Quest is not null, otherwise set objective as null.
		UQuestObjective* objective = (quest) ? quest->GetObjectiveByClass(questObjectiveClass.Value) : nullptr;

		// If ptr is null, bind the ??? function to QuestManager's OnQuestStarted
		objective = (objective) ? objective : NewObject<UQuestObjective>(this, questObjectiveClass.Value);

		// Store the ptr to the array.
		RelatedObjectives.Add(objective);
	}
}

void USomeActorComponent::AddRelatedObjective(UQuestObjective* ObjectivePtr)
{
	for (auto questObjectiveClass : RelatedQuestObjectiveClasses)
	{
		// If the objective ptr has a matching quest and objective ID with the stored classes...
		if (ObjectivePtr->Quest->GetClass() == questObjectiveClass.Key && ObjectivePtr->GetClass() == questObjectiveClass.Value)
		{
			bool bObjectiveExists = false;

			// Check if the objective ptr already exists in this component's array.
			for (UQuestObjective* objective : RelatedObjectives)
			{
				if (objective->Quest->QuestID == ObjectivePtr->Quest->QuestID && objective->ObjectiveID == ObjectivePtr->ObjectiveID)
				{
					bObjectiveExists = true;
					break;
				}
			}

			// If the objective does not already exist, store it in the array.
			if (!bObjectiveExists)
			{
				RelatedObjectives.Add(ObjectivePtr);
			}
		}
	}
}
