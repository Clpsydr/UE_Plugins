#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaSelector.generated.h"

class UMediaPlayer;
class UButton;
class UImage;
class USizeBox;

UCLASS()
class FPSTEST_API UMediaSelector : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMediaPlayer* MediaPlayer;
	
	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
		UButton* SelectMediaButton;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidget))
		UImage* ImagePresenter;

	UPROPERTY(EditDefaultsOnly, Meta = (BindWidgetOptional))
		USizeBox* ScaleSetter;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> FoundActors;

	// possibly needs a scalebox, to set up dimensions

public:
	UFUNCTION()
		void OnMediaButtonPress();
};
