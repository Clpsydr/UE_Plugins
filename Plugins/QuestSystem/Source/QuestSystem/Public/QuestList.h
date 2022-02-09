#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestList.generated.h"

class AQuest;
class UObjectiveWatcherWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestUpdate, AQuest*);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestList : public UActorComponent
{
	GENERATED_BODY()

public:
	void AddQuest(AQuest* Quest);

	const TArray<AQuest*>& GetAllQuests() { return AcceptedQuests; }

	AQuest* GetActiveQuest() const { return ActiveQuest; }

	void PurgeQuests();

	void SetActiveQuest(AQuest* Quest);

	FOnQuestUpdate OnActiveQuestUpdated;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		TArray<AQuest*> AcceptedQuests;

	UPROPERTY()
		AQuest* ActiveQuest;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UObjectiveWatcherWidget> ObjectiveWatcherWidgetClass;
};