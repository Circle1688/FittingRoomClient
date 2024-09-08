// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Clothes/SearchClothesAsync.h"
#include "Utils/FittingRoomUtils.h"


USearchClothesAsync* USearchClothesAsync::SearchClothes(const FString& Keywords)
{
	USearchClothesAsync* Node = NewObject<USearchClothesAsync>();
	Node->SendRequest(Keywords);
	return Node;
}

void USearchClothesAsync::SendRequest(const FString& Keywords)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/search_clothes");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(Keywords);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &USearchClothesAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void USearchClothesAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TArray<FClothesInfoStruct> ClothesInfos;
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			const TArray<TSharedPtr<FJsonValue>>& Results = JsonObj->GetArrayField(TEXT("results"));
			for (auto Result : Results)
			{
				FClothesInfoStruct ClothesInfo;
				ClothesInfo.Preview = Result->AsObject()->GetStringField(TEXT("preview"));
				ClothesInfo.Price = Result->AsObject()->GetNumberField(TEXT("price"));
				ClothesInfo.Brand = Result->AsObject()->GetStringField(TEXT("brand"));
				ClothesInfo.Type = Result->AsObject()->GetStringField(TEXT("type"));
				ClothesInfo.Name = Result->AsObject()->GetStringField(TEXT("name"));
				ClothesInfo.Color = Result->AsObject()->GetStringField(TEXT("color"));
				ClothesInfo.Description = Result->AsObject()->GetStringField(TEXT("description"));

				ClothesInfos.Add(ClothesInfo);
			}
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, ClothesInfos, TEXT("OK"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, {}, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, {}, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

FString USearchClothesAsync::MakeRequestBody(const FString& Keywords)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("keywords"), Keywords);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
