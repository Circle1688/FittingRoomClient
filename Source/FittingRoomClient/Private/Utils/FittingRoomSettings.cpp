// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/FittingRoomSettings.h"

UFittingRoomSettings* UFittingRoomSettings::GetFittingRoomSettings()
{
	UFittingRoomSettings* Setting = GetMutableDefault<UFittingRoomSettings>();
	return Setting;
}
