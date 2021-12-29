#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PublicObjectTypes.h"
#include "QuestManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStatusChanged, UQuest*, Quest);

UCLASS()
class UNREALCODELAB_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestManager();

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestLocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestUnlocked;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestAccepted;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestAbandoned;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestFailed;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnAnyQuestCompleted;

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
	// Adds a new quest to the manager's quest list, and performs any necessary initialisation.
	// * bOverride = Whether the function overrides any existing quest with the same ID.
	void AddNewQuest(UQuest* NewQuest, bool bOverride = false);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByDisplayName();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestsByID();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<UQuest*>& SortQuestByStatus();
};
