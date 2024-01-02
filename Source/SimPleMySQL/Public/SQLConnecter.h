// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MySQL/include/mysql.h"
//#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "SQLConnecter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSimPleMySQLPlugin, Log, All);
DEFINE_LOG_CATEGORY(LogSimPleMySQLPlugin);

USTRUCT(BlueprintType)
struct FSQLConnectStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSQLConnectStruct")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSQLConnectStruct")
	FString User;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSQLConnectStruct")
	FString Pass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSQLConnectStruct")
	FString Data_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSQLConnectStruct")
	int Port;

	
	FSQLConnectStruct():
		Host("127.0.0.1"), User("root"), Pass("123456"), Data_name(""), Port(3306)
	{
	}
};

USTRUCT(BlueprintType)
struct FSQLRow
{
	GENERATED_BODY()

	// 正确使用UPROPERTY宏来声明嵌套的TArray
	UPROPERTY(BlueprintReadWrite, Category = "FSQLRow")
	TArray<FString> RowData;

};

UCLASS()
class SIMPLEMYSQL_API ASQLConnecter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASQLConnecter();

	MYSQL* SQL;
	FSQLConnectStruct SqlStruct;

	UFUNCTION(BlueprintCallable, Category = "SQL")
	bool InitSql(FString host, FString user, FString pw,FString data_name,int port);

	UFUNCTION(BlueprintCallable, Category = "SQL")
	bool InitSqlFromStruct(FSQLConnectStruct st);

	UFUNCTION(BlueprintCallable, Category = "SQL")
	TArray<FSQLRow> Query(FString sqlMes,bool& isSuccess);

	UFUNCTION(BlueprintCallable, Category = "SQL")
	TArray<FString> GetTableColumns(FString tablename);

	/*UFUNCTION(BlueprintCallable, Category = "SQL")
	FString GetValue(FString tableName,FString columnName, int row, int num = 1);*/

	UFUNCTION(BlueprintCallable, Category = "SQL")
	FSQLRow GetRow(FString tablename, FString mainkeyValue);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
