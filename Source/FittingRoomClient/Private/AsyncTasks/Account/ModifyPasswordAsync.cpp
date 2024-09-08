// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/ModifyPasswordAsync.h"
#include "Utils/FittingRoomUtils.h"


UModifyPasswordAsync* UModifyPasswordAsync::ModifyPassword(const FString& OldPassword, const FString& NewPassword)
{
	UModifyPasswordAsync* Node = NewObject<UModifyPasswordAsync>();
	Node->SendRequest(OldPassword, NewPassword);
	return Node;
}

void UModifyPasswordAsync::SendRequest(const FString& OldPassword, const FString& NewPassword)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/modify_password");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("PATCH");

	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(OldPassword, NewPassword);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UModifyPasswordAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UModifyPasswordAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

FString UModifyPasswordAsync::MakeRequestBody(const FString& OldPassword, const FString& NewPassword)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("old_password"), OldPassword);
	Body->SetStringField(TEXT("new_password"), NewPassword);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
