// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "LoginAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLoginHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API ULoginAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 用户登录
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "User Login"))
	static ULoginAsync* Login(const FString& UserName, const FString& Password);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FLoginHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FLoginHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& UserName, const FString& Password);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& UserName, const FString& Password);
};
