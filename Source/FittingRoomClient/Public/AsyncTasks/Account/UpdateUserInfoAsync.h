// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FittingRoomTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "UpdateUserInfoAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUserInfoHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UUpdateUserInfoAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 用户注册
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Update User Info"))
	static UUpdateUserInfoAsync* Register(const FUserInfo& UserInfo);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FUpdateUserInfoHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FUpdateUserInfoHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FUserInfo& UserInfo);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FUserInfo& UserInfo);
};
