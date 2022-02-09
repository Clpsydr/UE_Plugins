#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"

UENUM()
enum class EObjectiveType : uint8
{
	Ot_Location,
	Ot_Interact,
	Ot_Hit,
	Ot_Kill,
	Ot_Collect,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, UQuestObjective*)

UCLASS(Abstract)
class UQuestObjective : public UObject
{
	GENERATED_BODY()

public:
	virtual void ActivateObjective(AActor* Instigator) {};

	virtual AActor* GetInteractiveComponent() const {
		return nullptr;
	};

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		EObjectiveType Type;

	FOnObjectiveCompleted OnObjectiveCompleted;

	UPROPERTY(VisibleAnywhere)
		bool bIsCompleted;

	UPROPERTY(VisibleAnywhere)
		bool bCanBeCompleted;
};


UCLASS()
class QUESTSYSTEM_API UInteractionObjective : public UQuestObjective
{
	GENERATED_BODY()

public:
	UInteractionObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual AActor* GetInteractiveComponent() const override;

	virtual void Serialize(FArchive& Ar) override;

	//possibly InteractableActor instead?
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "QuestInteractObject"))   //Meta specifier will check which classes have the interface to be able to interact
		AActor* Target;														// could simply specify a subclass of interactable actor instead.
};


UCLASS()
class QUESTSYSTEM_API ULocationObjective : public UQuestObjective
{
	GENERATED_BODY()

public:
	ULocationObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual AActor* GetInteractiveComponent() const override;

	virtual void Serialize(FArchive& Ar) override;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "LocationMarker"))
		AActor* Marker;
};

UCLASS()
class QUESTSYSTEM_API UCollectibleObjective : public UQuestObjective
{
	GENERATED_BODY()

public:
	UCollectibleObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual AActor* GetInteractiveComponent() const override;

	virtual void Serialize(FArchive& Ar) override;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "CollectibleActor"))
		AActor* Collectible;
};

UCLASS()
class QUESTSYSTEM_API UShootableObjective : public UQuestObjective
{
	GENERATED_BODY()

public:
	UShootableObjective();

	virtual void ActivateObjective(AActor* Instigator) override;

	virtual AActor* GetInteractiveComponent() const override;

	virtual void Serialize(FArchive& Ar) override;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "ShootableActor"))
		AActor* Shootable;
};