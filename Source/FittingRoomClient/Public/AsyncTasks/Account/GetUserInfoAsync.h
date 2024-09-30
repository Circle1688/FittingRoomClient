// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FittingRoomTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetUserInfoAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGetUserInfoHttpDelegate, int32, Code, const FString&, Message, const FUserInfo&, UserInfo);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetUserInfoAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 用户注册
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get User Info"))
	static UGetUserInfoAsync* GetUserInfo();

	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetUserInfoHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetUserInfoHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest();

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
};
