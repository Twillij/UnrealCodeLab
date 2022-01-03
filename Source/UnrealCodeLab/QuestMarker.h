#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestGiver.h"
#include "QuestMarker.generated.h"

class UQuest;
class UQuestManager;

UCLASS()
class UNREALCODELAB_API AQuestMarker : public AActor, public IQuestGiver
{
	GENERATED_BODY()
	
public:
	AQuestMarker();

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	AActor* QuestGiver;

	UPROPERTY(BlueprintReadWrite, Category = "Quest")
	bool bSetRootObjectAsQuestGiver = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<TSubclassOf<UQuest>> AssignedQuestClasses;

	UPROPERTY(BlueprintReadOnly, Category = "Quest")
	TArray<UQuest*> AssignedQuests;

public:
	virtual void BeginPlay() override;
	void InitAssignedQuests_Implementation() override;
	TArray<UQuest*> GetAssignedQuests_Implementation() override;


};
