#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollectibleActor.generated.h"

UINTERFACE(MinimalAPI)
class UCollectibleActor : public UInterface
{
	GENERATED_BODY()
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBeingPickedUp, AActor* /* Collectible Itself */, AActor* /* Actor picking up the box */);

class QUESTSYSTEM_API ICollectibleActor
{
	GENERATED_BODY()

public:
	virtual void AnnouncePickUpEvent(AActor* Collectible, AActor* Collector)
	{
		if (OnBeingPickedUp.IsBound())
		{
			OnBeingPickedUp.Broadcast(Collectible, Collector);
		}
	}

	FOnBeingPickedUp OnBeingPickedUp;
};

UCLASS()
class QUESTSYSTEM_API ACollectibleActorObject : public AActor, public ICollectibleActor  //provided by Very Dumb Naming Inc.
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
		void OnCollisionWithActor(AActor* OverlappingActor)
		{
			AnnouncePickUpEvent(this, OverlappingActor);
		}

};
