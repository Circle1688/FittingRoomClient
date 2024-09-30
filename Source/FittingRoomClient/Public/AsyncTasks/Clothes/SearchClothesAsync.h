// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FittingRoomTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "SearchClothesAsync.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSearchClothesHttpDelegate, int32, Code, const TArray<FClothesInfoStruct>&, Results, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API USearchClothesAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 多关键词搜索衣服数据库
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Clothes", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Search Clothes"))
	static USearchClothesAsync* SearchClothes(const FString& Keywords);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FSearchClothesHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FSearchClothesHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& Keywords);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& Keywords);
};
