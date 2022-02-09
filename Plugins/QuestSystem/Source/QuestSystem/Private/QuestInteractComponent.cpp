#include "QuestInteractComponent.h"
#include "Blueprint/UserWidget.h"
#include "QuestInteractObject.h"

UQuestInteractComponent::UQuestInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UQuestInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractionCompBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractionCompEndOverlap);
}

void UQuestInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestInteractComponent::Interact()
{
	if (ActorToInteract)
	{
		IQuestInteractObject::Execute_Interact(ActorToInteract, GetOwner());
	}
}

void UQuestInteractComponent::OnInteractionCompBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UQuestInteractObject>())
	{
		ActorToInteract = OtherActor;
		if (!InteractMsgWidget)
		{
			if (InteractMessageClass)
			{
				InteractMsgWidget = CreateWidget<UUserWidget>(GetWorld(), InteractMessageClass);
			}
		}

		if (InteractMsgWidget && !InteractMsgWidget->IsInViewport())
		{
			InteractMsgWidget->AddToViewport();
		}
	}
}

void UQuestInteractComponent::OnInteractionCompEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (ActorToInteract == OtherActor) 
	{
		ActorToInteract = nullptr;

		if (InteractMsgWidget)
		{
			InteractMsgWidget->RemoveFromViewport();
		}
	}
}
