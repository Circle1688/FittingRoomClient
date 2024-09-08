// Copyright Epic Games, Inc. All Rights Reserved.

#include "FittingRoomClient.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Utils/FittingRoomSettings.h"

#define LOCTEXT_NAMESPACE "FFittingRoomClientModule"

void FFittingRoomClientModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingModule->RegisterSettings("Project", "Plugins", "FittingRoomSettings",
			LOCTEXT("RuntimeSettingsName", "Fitting Room"),
			LOCTEXT("RuntimeSettingsDescription", "Configure fitting room settings"),
			GetMutableDefault<UFittingRoomSettings>()
		);
	}
}

void FFittingRoomClientModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "FittingRoomSettings");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFittingRoomClientModule, FittingRoomClient)