/*
* Dummy actor with only mesh and a number, the rest of the logic and physics properties are in blueprints 
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CountBlock.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS()
class FPSTEST_API ACountBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Indicator")
		UTextRenderComponent* SideNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Indicator")
		int32 BlockParam;

	virtual void Serialize(FArchive& Ar) override;

};
