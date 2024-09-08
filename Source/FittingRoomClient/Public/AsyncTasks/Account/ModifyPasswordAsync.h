// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "ModifyPasswordAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FModifyPasswordHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UModifyPasswordAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 修改密码，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Change Password"))
	static UModifyPasswordAsync* ModifyPassword(const FString& OldPassword, const FString& NewPassword);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FModifyPasswordHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FModifyPasswordHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& OldPassword, const FString& NewPassword);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& OldPassword, const FString& NewPassword);
};
