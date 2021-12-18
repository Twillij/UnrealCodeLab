#include "CustomGameInstance.h"
#include "QuestManager.h"

void UCustomGameInstance::Init()
{
	Super::Init();

	if (QuestManagerClass)
		QuestManager = NewObject<AQuestManager>(this, QuestManagerClass, "Quest Manager");
	else
		UE_LOG(LogTemp, Warning, TEXT("Quest manager has not been set."));
}

AQuestManager* UCustomGameInstance::GetQuestManager()
{
	return QuestManager;
}
