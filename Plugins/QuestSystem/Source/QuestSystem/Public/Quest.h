#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class UQuestObjective;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusUpdated, AQuest* /* new quest */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusCompleted, AQuest* /* this quest */);

UCLASS()
class QUESTSYSTEM_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuest();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
		bool bIsCompleted;

	UPROPERTY(EditAnywhere)
		TArray<UQuestObjective*> ObjectiveSet;

	AActor* CurrentEmployer;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		FText Name;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		bool bIsStoryQuest = true;

	UPROPERTY(EditAnywhere)
		bool bAreObjectivesInSequence = true;

	UPROPERTY(EditAnywhere)
		AQuest* PrerequisiteQuest;

	UPROPERTY(VisibleAnywhere)
		bool bIsTaken;

	UFUNCTION(BlueprintCallable, CallInEditor)
		void UpdateLocation();

	UFUNCTION()
		void AcceptQuest(AActor* Character);

	UFUNCTION()
		bool IsCompleted() const;

	UFUNCTION()
		TArray<UQuestObjective*> GetObjectives() { return ObjectiveSet; }

	UFUNCTION()
		TArray<AActor*> GetObjectiveComponents();

	UFUNCTION()
		AActor* GetCurrentEmployer() { return CurrentEmployer; }

	void OnObjectiveCompleted(UQuestObjective* Objective);

	FOnQuestStatusUpdated OnQuestStatusUpdated;

	FOnQuestStatusCompleted OnQuestStatusCompleted;

	void Serialize(FArchive& Ar) override;

#if WITH_EDITOR

	UFUNCTION(CallInEditor)
		void AddInteractObjective();

	UFUNCTION(CallInEditor)
		void AddLocationObjective();

	UFUNCTION(CallInEditor)
		void AddCollectibleObjective();

	UFUNCTION(CallInEditor)
		void AddShootableObjective();

#endif
};
