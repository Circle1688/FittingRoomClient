// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FittingRoomTypes.generated.h"

UENUM(BlueprintType)
enum class EEthnicity: uint8
{
	EAsian		UMETA(DisplayName = "Asian"),
	EBlack		UMETA(DisplayName = "Black or African American"),
	EHispanic	UMETA(DisplayName = "Hispanic or Latino"),
	EWhite		UMETA(DisplayName = "White"),
	EOther		UMETA(DisplayName = "Other")
};

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Info")
	FString Mobile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Info")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Info")
	int64 Birth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Info")
	EEthnicity Ethnicity = EEthnicity::EAsian;
};

USTRUCT(BlueprintType)
struct FClothesInfoStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Preview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	float Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Brand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Clothes Info")
	FString Description;
};