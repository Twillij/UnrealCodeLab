#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class AQuestManager;

UCLASS()
class UNREALCODELAB_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "Quest Manager")
	TSubclassOf<AQuestManager> QuestManagerClass;

private:
	AQuestManager* QuestManager;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	AQuestManager* GetQuestManager();
};
