#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEST_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float HP;

	float MaxHP;

	int32 Ammo;

	int32 MaxAmmo;

public:

	const float GetHealthRatio() { return HP / MaxHP;  }

	const int32 GetAmmo() { return Ammo; }

	virtual	void Serialize(FArchive& Ar) override;
};
