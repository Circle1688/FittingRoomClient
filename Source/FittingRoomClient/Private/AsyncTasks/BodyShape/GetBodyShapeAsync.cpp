// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/BodyShape/GetBodyShapeAsync.h"
#include "Utils/FittingRoomUtils.h"


UGetBodyShapeAsync* UGetBodyShapeAsync::GetBodyShape()
{
	UGetBodyShapeAsync* Node = NewObject<UGetBodyShapeAsync>();
	Node->SendRequest();
	return Node;
}

void UGetBodyShapeAsync::SendRequest()
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/get_all_bodyshape");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &UGetBodyShapeAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetBodyShapeAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FBodyShapeMapWrapper BodyShapes;
	
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			
			for (auto KeyValue: JsonObj->Values)
			{
				const FString& Key = KeyValue.Key;
				float Value = KeyValue.Value->AsNumber();
				BodyShapes.FBodyShapeMap.Add(Key, Value);
			}
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, BodyShapes, TEXT("Get all body shapes successfully"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, BodyShapes, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, BodyShapes, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

