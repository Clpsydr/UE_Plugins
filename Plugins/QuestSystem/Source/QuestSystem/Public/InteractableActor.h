#pragma once

#include "CoreMinimal.h"
#include "QuestInteractObject.h"
#include "InteractableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API AInteractableActor : public AActor, public IQuestInteractObject
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable)
		void OnInteractionFinished(AActor* InteractInstigator)
		{
			NotifyInteractionFinished(this, InteractInstigator);
		};
};
