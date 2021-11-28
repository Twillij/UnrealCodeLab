#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.h"
#include "QuestManager.generated.h"

UCLASS()
class UNREALCODELAB_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestManager();

	UPROPERTY(BlueprintReadOnly)
	TArray<UQuest*> Quests;

private:
	TArray<UQuest*> FilteredQuests;

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	const TArray<UQuest*>& GetQuestsByStatus(EQuestStatus FilteredStatus);

	UFUNCTION(BlueprintCallable)
	void SetQuestStatusByIndex(int ArrayIndex, EQuestStatus Status);

	UFUNCTION(BlueprintCallable)
	void SetQuestStatusByID(const FName& QuestID, EQuestStatus Status);

	UFUNCTION(BlueprintCallable)
	void AddNewQuest(UQuest* NewQuest);
};
