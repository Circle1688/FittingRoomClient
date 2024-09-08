// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/BodyShape/UpdateBodyShapeAsync.h"
#include "Utils/FittingRoomUtils.h"


UUpdateBodyShapeAsync* UUpdateBodyShapeAsync::UpdateBodyShape(const FString& FieldName, float Value)
{
	UUpdateBodyShapeAsync* Node = NewObject<UUpdateBodyShapeAsync>();
	Node->SendRequest(FieldName, Value);
	return Node;
}

void UUpdateBodyShapeAsync::SendRequest(const FString& FieldName, float Value)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/update_bodyshape");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("PATCH");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(FieldName, Value);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UUpdateBodyShapeAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UUpdateBodyShapeAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
		FString Message;
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			Message = JsonObj->GetStringField(TEXT("message"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, Message);
			}
		}
		else
		{
			Message = UFittingRoomUtils::ParseException(Data);
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

FString UUpdateBodyShapeAsync::MakeRequestBody(const FString& FieldName, float Value)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("body_shape_name"), FieldName);
	Body->SetNumberField(TEXT("body_shape_value"), Value);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
