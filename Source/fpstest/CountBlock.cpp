#include "CountBlock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACountBlock::ACountBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh1P = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh1P->SetupAttachment(RootComponent);

	SideNumber = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Indicator"));
	SideNumber->SetupAttachment(Mesh1P);

}

// Called when the game starts or when spawned
void ACountBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACountBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountBlock::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		FVector Loc;
		FRotator Rot;
		FVector Scal;
		if (Ar.IsSaving())
		{
			Loc = GetActorLocation();
			Rot = GetActorRotation();
			Scal = GetActorScale();
			Ar << Loc << Rot << Scal;
			Ar << BlockParam;
		}
		else
		{
			Ar << Loc << Rot << Scal;
			SetActorLocation(Loc);
			SetActorRotation(Rot);
			SetActorScale3D(Scal);
			Ar << BlockParam;
		}
	}
}