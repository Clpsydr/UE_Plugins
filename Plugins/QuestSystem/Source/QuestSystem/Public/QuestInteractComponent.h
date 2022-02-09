#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "QuestInteractComponent.generated.h"

class UUserWidget;

UCLASS(ClassGroup = "Collision", meta  = (DisplayName = "Interaction Collision", BlueprintSpawnableComponent))
class QUESTSYSTEM_API UQuestInteractComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UQuestInteractComponent();

	UFUNCTION(BlueprintCallable)
		void Interact();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> InteractMessageClass;

	UPROPERTY()
		UUserWidget* InteractMsgWidget;

	UPROPERTY()
		AActor* ActorToInteract;

	UFUNCTION()
		void OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
