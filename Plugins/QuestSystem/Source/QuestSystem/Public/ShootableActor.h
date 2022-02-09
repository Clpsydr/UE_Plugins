#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShootableActor.generated.h"

UINTERFACE(MinimalAPI)
class UShootableActor : public UInterface
{
	GENERATED_BODY()
};


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHitByProjectile, AActor* /* Target */, AActor* /* Projectile */);

class QUESTSYSTEM_API IShootableActor
{
	GENERATED_BODY()

public:
	virtual void AnnounceTargetHit(AActor* HitTarget, AActor* HitProjectile)
	{
		if (OnHitByProjectile.IsBound())
		{
			OnHitByProjectile.Broadcast(HitTarget, HitProjectile);  
		}
	}

	FOnHitByProjectile OnHitByProjectile;
};

UCLASS()
class QUESTSYSTEM_API AShootableActorObject : public AActor, public IShootableActor
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void OnProjectileCollision(AActor* Projectile)			
		{
			AnnounceTargetHit(this, Projectile->GetOwner());
		}
};