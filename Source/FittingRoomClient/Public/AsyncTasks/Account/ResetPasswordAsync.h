// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "ResetPasswordAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResetPasswordHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UResetPasswordAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 通过用户名和手机号重置密码
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Reset Password"))
	static UResetPasswordAsync* ResetPassword(const FString& UserName, const FString& NewPassword, const FString& Mobile);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FResetPasswordHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FResetPasswordHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& UserName, const FString& Password, const FString& Mobile);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& UserName, const FString& Password, const FString& Mobile);
};
