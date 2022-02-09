#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWatcherWidget.generated.h"

class AQuest;
class UObjectiveWidget;
class UVerticalBox;

UCLASS()
class QUESTSYSTEM_API UObjectiveWatcherWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void SetCurrentObjective(AQuest* Quest);

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UVerticalBox* ObjectivesList;
};
