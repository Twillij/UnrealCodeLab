#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PublicObjectTypes.h"
#include "QuestGiverComponent.generated.h"

class UQuest;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCODELAB_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestGiverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<TSubclassOf<UQuest>> AssignedQuestClasses;

private:
	TArray<UQuest*> AssignedQuests;

public:
	virtual void BeginPlay() override;

	void InitAssignedQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByClass(TSubclassOf<UQuest> QuestClass);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetAssignedQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<UQuest*> GetQuestsByStatus(EProgressStatus QuestStatus);
};
