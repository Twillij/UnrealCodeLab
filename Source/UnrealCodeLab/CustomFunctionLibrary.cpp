#include "CustomFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"
#include "QuestManager.h"

UQuestManager* UCustomFunctionLibrary::GetQuestManager(const UObject* WorldContextObject)
{
    if (UCustomGameInstance* instance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject)))
    {
        return instance->GetQuestManager();
    }

    return nullptr;
}