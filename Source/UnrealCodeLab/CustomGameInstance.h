#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class UQuestManager;

UCLASS()
class UNREALCODELAB_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "Quest Manager")
	TSubclassOf<UQuestManager> QuestManagerClass;

private:
	UQuestManager* QuestManager;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuestManager* GetQuestManager();
};
