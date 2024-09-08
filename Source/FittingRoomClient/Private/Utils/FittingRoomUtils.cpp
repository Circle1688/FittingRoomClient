// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/FittingRoomUtils.h"
#include "FittingRoomClient.h"
#include "Modules/ModuleManager.h"
#include "Utils/FittingRoomSettings.h"

FString MakeJsonData(const FString& UrlType, const FString& Url)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("urltype"), UrlType);
	Body->SetStringField(TEXT("url"), Url);
	Body->SetStringField(TEXT("token"), UFittingRoomUtils::GetToken());
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}


FString UFittingRoomUtils::GetServerUrl()
{
	// FFittingRoomClientModule& mod = FModuleManager::Get().LoadModuleChecked<FFittingRoomClientModule>("FittingRoomClient");
	// return mod.ServerUrl;

	UFittingRoomSettings* Setting = UFittingRoomSettings::GetFittingRoomSettings();
	return Setting->Url;
}

FString UFittingRoomUtils::ParseException(const FString& InData)
{
	// FString 转 JsonObj
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InData);
	TSharedPtr<FJsonObject> RootJsonObj = MakeShareable(new FJsonObject);

	FJsonSerializer::Deserialize(JsonReader, RootJsonObj);

	return RootJsonObj->GetStringField(TEXT("detail"));
}

TSharedPtr<FJsonObject> UFittingRoomUtils::GetJsonObject(const FString& InData)
{
	// FString 转 JsonObj
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InData);
	TSharedPtr<FJsonObject> RootJsonObj = MakeShareable(new FJsonObject);

	FJsonSerializer::Deserialize(JsonReader, RootJsonObj);

	return RootJsonObj;
}

void UFittingRoomUtils::SetToken(FString Token)
{
	FFittingRoomClientModule& mod = FModuleManager::Get().LoadModuleChecked<FFittingRoomClientModule>("FittingRoomClient");
	mod.Token = Token;
}

FString UFittingRoomUtils::GetToken()
{
	FFittingRoomClientModule& mod = FModuleManager::Get().LoadModuleChecked<FFittingRoomClientModule>("FittingRoomClient");
	return mod.Token;
}

void UFittingRoomUtils::Logout()
{
	FFittingRoomClientModule& mod = FModuleManager::Get().LoadModuleChecked<FFittingRoomClientModule>("FittingRoomClient");
	mod.Token = "";
}

FString UFittingRoomUtils::PixelStreamUploadAvatar()
{
	FString RequestUrl = GetServerUrl() + TEXT("/upload_avatar");
	
	return MakeJsonData(TEXT("upload_avatar"), RequestUrl);
}

FString UFittingRoomUtils::PixelStreamSaveGalleryImage(const FString& Url)
{
	FString RequestUrl = GetServerUrl() + TEXT("/get_gallery_image/") + Url;
	
	return MakeJsonData(TEXT("get_gallery_image"), RequestUrl);
}

void UFittingRoomUtils::ParsePixelStreamResponse(const FString& Descriptor, EUICommandNodePin& Result, bool& Success, int32& Code, FString& Message)
{
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Descriptor);
	TSharedPtr<FJsonObject> RootJsonObj = MakeShareable(new FJsonObject);
		
	FJsonSerializer::Deserialize(JsonReader, RootJsonObj);
	
	FString Rsp_Type = RootJsonObj->GetStringField("rsp_type");
	Code = RootJsonObj->GetNumberField("code");
	Message = RootJsonObj->GetStringField("message");
	
	Success = Code == 200;

	if (Rsp_Type == "upload_avatar")
	{
		Result = EUICommandNodePin::UploadAvatar;
	}
}
