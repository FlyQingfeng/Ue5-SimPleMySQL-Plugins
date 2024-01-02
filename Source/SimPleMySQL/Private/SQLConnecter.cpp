// Fill out your copyright notice in the Description page of Project Settings.


#include "SQLConnecter.h"



// Sets default values
ASQLConnecter::ASQLConnecter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ASQLConnecter::InitSql(FString host, FString user, FString pw, FString data_name, int port)
{
	SqlStruct.Host = host;
	SqlStruct.User = user;
	SqlStruct.Pass = pw;
	SqlStruct.Data_name = data_name;
	SqlStruct.Port = port;

	SQL = mysql_init(NULL);
	mysql_options(SQL, MYSQL_SET_CHARSET_NAME, "GBK");

	if (!mysql_real_connect(SQL, TCHAR_TO_UTF8(*host), TCHAR_TO_UTF8(*user), TCHAR_TO_UTF8(*pw), TCHAR_TO_UTF8(*data_name), port, NULL, 0)) {
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: %s "), *FString(mysql_error(SQL)));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: %s "), *FString(mysql_error(SQL))));
		return false;
	}
	return true;
}

bool ASQLConnecter::InitSqlFromStruct(FSQLConnectStruct st) {
	SqlStruct.Host = st.Host;
	SqlStruct.User = st.User;
	SqlStruct.Pass = st.Pass;
	SqlStruct.Data_name = st.Data_name;
	SqlStruct.Port = st.Port;

	return InitSql(SqlStruct.Host, SqlStruct.User, SqlStruct.Pass, SqlStruct.Data_name, SqlStruct.Port);

}

TArray<FSQLRow> ASQLConnecter::Query(FString sqlMes, bool& isSuccess)
{
	if (SQL==nullptr)
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: SQL is not initialized at <Query> function"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: SQL is not initialized")));
		
		isSuccess = false;
		return TArray<FSQLRow>();
	}
	if (mysql_query(SQL, TCHAR_TO_UTF8(*sqlMes)))
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: %s at <Query> function"), *FString(mysql_error(SQL)));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: %s at <Query> function"), *FString(mysql_error(SQL))));
		isSuccess = false;
		return TArray<FSQLRow>();
	}
	MYSQL_RES* res = mysql_store_result(SQL);
	if (res == NULL)
	{
		isSuccess = true;
		return TArray<FSQLRow>();
	}

	MYSQL_ROW row;
	TArray<FSQLRow> Array;
	int num_fields = mysql_num_fields(res);//获得列数
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		FSQLRow line;
		for (int i = 0; i < num_fields; i++)
		{
			FString lineItem = FString(ANSI_TO_TCHAR(row[i]));
			line.RowData.Add(lineItem);
		}
		Array.Add(line);

	}
	isSuccess = true;
	return Array;
}

TArray<FString> ASQLConnecter::GetTableColumns(FString tablename)
{
	if (SQL == nullptr)
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: SQL is not initialized at <GetTableColumns> function"), *FString(mysql_error(SQL)));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: SQL is not initialized")));
		return TArray<FString>();
	}
	FString sql = "SHOW COLUMNS FROM "+FString(tablename);
	if (mysql_query(SQL, TCHAR_TO_UTF8(*sql)))
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: %s at <GetTableColumns> function"), *FString(mysql_error(SQL)));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: %s at <GetTableColumns> function"), *FString(mysql_error(SQL))));
		return TArray<FString>();
	}
	MYSQL_RES* res = mysql_store_result(SQL);
	MYSQL_ROW row;
	TArray<FString> Columns;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		Columns.Add(FString(row[0]));
	}
	return Columns;
}


FSQLRow ASQLConnecter::GetRow(FString tablename,FString mainkeyValue)
{
	
	if (SQL == nullptr)
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: SQL is not initialized"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: SQL is not initialized")));
		return FSQLRow();
	}
	TArray<FString>  Columns = GetTableColumns(tablename);
	if (Columns.IsEmpty())
	{
		return FSQLRow();
	}
	FString TableMainKey = Columns[0];

	

	FString sql = FString::Printf(TEXT("SELECT * FROM %s WHERE `%s`='%s'"),*tablename,*TableMainKey,*mainkeyValue);
	if (mysql_query(SQL, TCHAR_TO_UTF8(*sql)))
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL EROER: %s at <GetTableColumns> function"), *FString(mysql_error(SQL)));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL EROER: %s at <GetTableColumns> function"), *FString(mysql_error(SQL))));
		return FSQLRow();
	}
	MYSQL_RES* res = mysql_store_result(SQL);

	if (res == NULL) {
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("SQL SELECT is NULL at <GetTableColumns> function"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("SQL SELECT is NULL")));
		return FSQLRow();
	}

	MYSQL_ROW row;
	FSQLRow col;
	if ((row = mysql_fetch_row(res) )== NULL)
	{
		UE_LOG(LogSimPleMySQLPlugin, Warning, TEXT("The data is not in the table"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("The data is not in the table ")));
		return FSQLRow();
	}

	int num_fields = mysql_num_fields(res);
	for (size_t i = 0; i < num_fields; i++)
	{
		col.RowData.Add(FString(row[i]));
	}
	return col;
}



// Called when the game starts or when spawned
void ASQLConnecter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASQLConnecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

