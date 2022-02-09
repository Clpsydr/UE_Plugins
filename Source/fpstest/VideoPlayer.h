#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VideoPlayer.generated.h"

class UMediaPlayer;
class UStaticMeshComponent;

UCLASS()
class FPSTEST_API AVideoPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVideoPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMediaPlayer* MediaPlayer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TabloidBody;

};
