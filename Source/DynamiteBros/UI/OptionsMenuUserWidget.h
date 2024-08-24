#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenuUserWidget.generated.h"

UENUM()
enum class GraphicsSettings : uint8 {
	LOW = 0,
	MEDIUM = 1,
	HIGH = 2,
	EPIC = 3,
	ULTRA = 4,
};

UCLASS()
class DYNAMITEBROS_API UOptionsMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	GraphicsSettings CurrentGraphicSetting;
	int GraphicSettingsSize = 5;
	
public:

	virtual void NativeConstruct() override;

	UFUNCTION(Blueprintcallable)
	void CloseWidget();

	UFUNCTION(Blueprintcallable)
	void GoNextGraphicSetting();

	UFUNCTION(Blueprintcallable)
	void GoPrevGraphicSetting();

	UFUNCTION(Blueprintcallable)
	FString GetCurrentGraphicSettingAsString();

	UFUNCTION(Blueprintcallable)
	void DoApplySettings();

	void SetCurrentGraphicSetting(int GraphicSetting);
};
