#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LocationMarker.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLocationReached, AActor* /* Location Marker */, AActor* /* Overlapped Actor */);

UINTERFACE(MinimalAPI)
class ULocationMarker : public UInterface
{
	GENERATED_BODY()
};

class QUESTSYSTEM_API ILocationMarker
{
	GENERATED_BODY()

public:
	virtual void NotifyOverlapWithActor(AActor* LocationMarker, AActor* OverlappedActor)
	{
		if (OnLocationReached.IsBound())
		{
			OnLocationReached.Broadcast(LocationMarker, OverlappedActor);
		}
	}

	FOnLocationReached OnLocationReached;
};

UCLASS()
class QUESTSYSTEM_API ALocationMarkerActor : public AActor, public ILocationMarker
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void OnOverlappedByActor(AActor* OverlappingActor)
	{
		NotifyOverlapWithActor(this, OverlappingActor);
	}
};
