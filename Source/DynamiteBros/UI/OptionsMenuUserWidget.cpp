#include "OptionsMenuUserWidget.h"
#include "GameFramework/GameUserSettings.h"


void UOptionsMenuUserWidget::NativeConstruct() {
    Super::NativeConstruct();

    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    int level = UserSettings->GetOverallScalabilityLevel();
    UE_LOG(LogTemp, Warning, TEXT("the current level is %d"), level);
    if(level == -1) { 
        level = 3; 
        // set default setting
        SetCurrentGraphicSetting(level);
    }
    CurrentGraphicSetting = (GraphicsSettings) level;
}

void UOptionsMenuUserWidget::CloseWidget(){
    this->RemoveFromParent();
}

void UOptionsMenuUserWidget::GoNextGraphicSetting() {
    int c = (int) CurrentGraphicSetting;
    c = (c + 1) % GraphicSettingsSize;
    CurrentGraphicSetting = (GraphicsSettings) c;
}

void UOptionsMenuUserWidget::GoPrevGraphicSetting(){
    int c = (int) CurrentGraphicSetting;
    c--;
    if(c < 0) c = GraphicSettingsSize - 1;
    CurrentGraphicSetting = (GraphicsSettings) c;
}

FString UOptionsMenuUserWidget::GetCurrentGraphicSettingAsString() {
    switch(CurrentGraphicSetting){
        case GraphicsSettings::LOW:
            return TEXT("LOW");
        case GraphicsSettings::MEDIUM:
            return TEXT("MEDIUM");
        case GraphicsSettings::HIGH:
            return TEXT("HIGH");
        case GraphicsSettings::EPIC:
            return TEXT("EPIC");
        case GraphicsSettings::ULTRA:
            return TEXT("ULTRA");
        default:
            return TEXT("INVALID");
    }
}

void UOptionsMenuUserWidget::SetCurrentGraphicSetting(int GraphicSetting){
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

    if (UserSettings) {
        UserSettings->SetOverallScalabilityLevel(GraphicSetting);
        UserSettings->ApplySettings(false);
        UserSettings->SaveSettings();
        UE_LOG(LogTemp, Warning, TEXT("changed settings to %d"), GraphicSetting);
    }
}

void UOptionsMenuUserWidget::DoApplySettings(){
    SetCurrentGraphicSetting((int)CurrentGraphicSetting);
}