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

private:
	TArray<UQuest*> Quests;
	TArray<UQuest*> FilteredQuests;

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetAllQuests();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& GetQuestsByStatus(EQuestStatus Status);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	UQuest* GetQuestByID(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	EQuestStatus GetQuestStatus(FName QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestStatus(FName QuestID, EQuestStatus Status);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddNewQuest(UQuest* NewQuest);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestByStatus();
};
