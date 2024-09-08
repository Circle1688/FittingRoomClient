// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FittingRoomSettings.generated.h"

/**
 * 
 */
UCLASS(config=FittingRoomSettings)
class FITTINGROOMCLIENT_API UFittingRoomSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "General" ,meta = (DisplayName = "Server Url"))
	FString Url;

	static UFittingRoomSettings* GetFittingRoomSettings();
};
