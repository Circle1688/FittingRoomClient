// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/CaptureTexture2D.h"
#include "ImageUtils.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

UCaptureTexture2D* UCaptureTexture2D::CaptureTexture2D(UObject* WorldContextObject, bool bCaptureUI)
{
	UCaptureTexture2D* Node = NewObject<UCaptureTexture2D>();
	Node->CaptureHandle = UGameViewportClient::OnScreenshotCaptured().AddUObject(Node, &UCaptureTexture2D::ScreenCaptureCompleted);

	if(bCaptureUI)
	{
		FString Resolution = FString::Printf(TEXT("Shot ShowUI"));
		GEngine->GameViewport->Exec(WorldContextObject->GetWorld(), *Resolution, *GLog);
	}
	else
	{
		FString Resolution = FString::Printf(TEXT("Shot"));
		GEngine->GameViewport->Exec(WorldContextObject->GetWorld(), *Resolution, *GLog);
	}
	// // 不会捕获UI
	// FString Resolution = FString::Printf(TEXT("Shot"));
	// GEngine->GameViewport->Exec(WorldContextObject->GetWorld(), *Resolution, *GLog);
	
	return Node;
}

void UCaptureTexture2D::ScreenCaptureCompleted(int32 InWidth, int32 InHeight, const TArray<FColor>& InColor)
{
	// PNG格式压缩
	TArray64<uint8> PNGResult;
	FImageUtils::PNGCompressImageArray(InWidth, InHeight, InColor, PNGResult);

	// 转换
	TArray<uint8> BinaryImage(PNGResult);
	
	if(UTexture2D* NewTexture = FImageUtils::ImportBufferAsTexture2D(BinaryImage))
	{
		if (OnSuccess.IsBound()) OnSuccess.Broadcast(NewTexture, BinaryImage);
	}
	else
	{
		if (OnFail.IsBound()) OnFail.Broadcast(nullptr, {});
	}
	
	UGameViewportClient::OnScreenshotCaptured().Remove(CaptureHandle);
}
