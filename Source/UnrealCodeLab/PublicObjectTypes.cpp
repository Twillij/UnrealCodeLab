#include "PublicObjectTypes.h"
#include "Quest.h"
#include "QuestObjective.h"

FQuestObjectiveInfo::FQuestObjectiveInfo(UQuestObjective* ObjectivePtr)
{
	if (ObjectivePtr)
	{
		Objective = ObjectivePtr;
		ObjectiveClass = ObjectivePtr->GetClass();
		ObjectiveID = ObjectivePtr->ObjectiveID;

		if (UQuest* questPtr = ObjectivePtr->Quest)
		{
			Quest = questPtr;
			QuestClass = questPtr->GetClass();
			QuestID = questPtr->QuestID;
		}
	}
}
