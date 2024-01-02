// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MySQL/include/mysql.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySqlBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEMYSQL_API UMySqlBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	MYSQL* SQL;
	FString host = "127.0.0.1";
	FString user = "root";
	FString pw = "123456";
	FString data_name = "gametest";
	FString table_name = "userinfo";
	int port = 3306;

	/*UFUNCTION(BlueprintCallable, Category = "SQL")
	bool InitSql();*/
};
