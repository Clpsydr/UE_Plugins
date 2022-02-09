#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInteractObject.generated.h"

UINTERFACE(MinimalAPI)
class UQuestInteractObject : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinished, AActor* /* Interactable Object */, AActor* /* Interacting Actor */);

class QUESTSYSTEM_API IQuestInteractObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Interact(AActor* InteractingActor);

	UFUNCTION()
		virtual void Interact_Implementation(AActor* InteractingActor) {};

//	UFUNCTION()
	virtual void NotifyInteractionFinished(AActor* InteractableObject, AActor* InteractingActor)
	{
		if (OnInteractionFinished.IsBound())
		{
			OnInteractionFinished.Broadcast(InteractableObject, InteractingActor);
		}
	}

	FOnInteractionFinished OnInteractionFinished;

	// to make a function that returns delegate, it should be visible to blueprints.
	// that requires making delegate dynamic
};

