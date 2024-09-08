// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetBodyShapeAsync.generated.h"


USTRUCT(BlueprintType)
struct FBodyShapeMapWrapper
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Body Shape")
	TMap<FString, float> FBodyShapeMap;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGetBodyShapeHttpDelegate, int32, Code, const FBodyShapeMapWrapper&, BodyShapes, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetBodyShapeAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 获取身材数据，返回Map，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Body Shape", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get All Body Shape"))
	static UGetBodyShapeAsync* GetBodyShape();

	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetBodyShapeHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetBodyShapeHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest();

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
