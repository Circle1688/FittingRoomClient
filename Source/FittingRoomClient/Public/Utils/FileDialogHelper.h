// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileDialogHelper.generated.h"

UENUM(BlueprintType)
enum class ESelectFlags:uint8
{
	ENone,
	EMultiple
};
/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UFileDialogHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*
	 * 打开图像文件选择对话框，支持常见图像格式，*.png *.jpg *.jpeg *.bmp
	 * 仅运行时
	 */
	UFUNCTION(BlueprintCallable, Category="Fitting Room|Utils|File Dialog")
	static bool OpenImageFileDialog(const FString DefaultPath, FString& FilePath);

	/*
	 * 保存PNG图像文件对话框
	 * 仅运行时
	 */
	UFUNCTION(BlueprintCallable, Category="Fitting Room|Utils|File Dialog")
	static bool SaveImageFileDialog(const FString DefaultPath, const FString DefaultFileName, FString& FilePath);
};
