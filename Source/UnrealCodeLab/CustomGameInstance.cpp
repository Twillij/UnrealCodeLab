#include "CustomGameInstance.h"
#include "QuestManager.h"

void UCustomGameInstance::Init()
{
	Super::Init();

	QuestManager = (QuestManagerClass) ? NewObject<UQuestManager>(this, QuestManagerClass, "Quest Manager") : NewObject<UQuestManager>(this, UQuestManager::StaticClass(), "Quest Manager");
	QuestManager->Init();
}

UQuestManager* UCustomGameInstance::GetQuestManager()
{
	return QuestManager;
}
