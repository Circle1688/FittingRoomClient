// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "RegisterAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API URegisterAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 用户注册
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Register user"))
	static URegisterAsync* Register(const FString& UserName, const FString& Password, const FString& Mobile);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& UserName, const FString& Password, const FString& Mobile);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& UserName, const FString& Password, const FString& Mobile);
};
