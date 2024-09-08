// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/UploadAvatarAsync.h"
#include "Utils/FittingRoomUtils.h"
#include "Misc/Paths.h"


UUploadAvatarAsync* UUploadAvatarAsync::UploadAvatar(const FString& FilePath)
{
	UUploadAvatarAsync* Node = NewObject<UUploadAvatarAsync>();
	Node->SendRequest(FilePath);
	return Node;
}

void UUploadAvatarAsync::SendRequest(const FString& FilePath)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl = UFittingRoomUtils::GetServerUrl() + TEXT("/upload_avatar");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	// Request header
	FString Boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW" + FString::FromInt(FMath::Rand());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

	//The bit array format of the request's content
	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *FilePath))
	{
		// Begin Boundry
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		// File Header
		FString FileHeader = "Content-Disposition: form-data;name=\"file\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(FilePath) + "\"\r\n");
		FileHeader.Append("Content-Type: image/png\r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
	
		// File Content
		RequestContent.Append(FileContent);
	}
	
	// End Boundry
	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);

	
	Request->OnProcessRequestComplete().BindUObject(this, &UUploadAvatarAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UUploadAvatarAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			FString Message = JsonObj->GetStringField(TEXT("message"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, Message);
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}
