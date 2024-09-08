// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FittingRoomUtils.generated.h"

UENUM(BlueprintType)
enum class EUICommandNodePin:uint8
{
	UploadAvatar
};

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UFittingRoomUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static FString GetServerUrl();
	
	static FString ParseException(const FString& InData);
	
	static TSharedPtr<FJsonObject> GetJsonObject(const FString& InData);

	//存储登录的用户Token
	static void SetToken(FString Token);
	
	static FString GetToken();

	// 退出登录，在切换用户之前一定要记得登出
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "User Logout"), Category = "Fitting Room|Account")
	static void Logout();

	// 上传头像时，发送到像素流前端，注意一定要登录之后才能用
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pixel Stream Upload Avatar"), Category = "Fitting Room|Pixel Stream")
	static FString PixelStreamUploadAvatar();

	/* 保存生成的图时，发送到像素流前端，注意一定要登录之后才能用
	 * Url为图库中对应的图的url
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Pixel Stream Save Gallery Image"), Category = "Fitting Room|Pixel Stream")
	static FString PixelStreamSaveGalleryImage(const FString& Url);

	// 解析像素流前端发过来的信息，在像素流前端完成上传或保存时调用
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Parse Pixel Stream Response", ExpandEnumAsExecs="Result"), Category = "Fitting Room|Pixel Stream")
	static void ParsePixelStreamResponse(const FString& Descriptor, EUICommandNodePin& Result, bool& Success, int32& Code, FString& Message);
};
