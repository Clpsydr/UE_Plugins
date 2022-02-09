#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveStateWindow.generated.h"

class UEditableTextBox;
class UButton;

UCLASS()
class FPSTEST_API USaveStateWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* SlotNameEntry;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* VarToSave;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* CustomMessage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* CloseBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* LoadBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* SaveBtn;
};
