#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "QuestGiverNpc.generated.h"

class UNpcDialogWidget;
class UWidgetComponent;
class UStaticMesh;
class AQuest;

UCLASS()
class QUESTSYSTEM_API AQuestGiverNpc : public AInteractableActor
{
	GENERATED_BODY()

public:
	AQuestGiverNpc();

protected:
	virtual void BeginPlay() override;

	TArray<AQuest*> Quests;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(AActor* InteractInstigator) override;

	UFUNCTION()
	void CheckQuestIndication(AQuest* PlayerQuest);  

	bool IsQuestAvailable(AQuest* Quest);

	bool HasQuests();

	void ChangeQuestIndication(bool FlagState);

	const TArray<AQuest*> GetQuests();

	TArray<AActor*> GetAllObjectiveComps();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UNpcDialogWidget> QuestDialogWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UWidgetComponent* StatusWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> StatusWidgetClass;

	virtual void Serialize(FArchive& Ar) override;
	
};
