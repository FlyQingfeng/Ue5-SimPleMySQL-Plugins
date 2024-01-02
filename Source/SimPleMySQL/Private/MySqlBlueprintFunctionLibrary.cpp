// Fill out your copyright notice in the Description page of Project Settings.


#include "MySqlBlueprintFunctionLibrary.h"
//bool UMySqlBlueprintFunctionLibrary::InitSql()
//{
//	MYSQL* conn = mysql_init(NULL);
//	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "GBK");
//	
//
//	if (!mysql_real_connect(conn, TCHAR_TO_UTF8(*host), TCHAR_TO_UTF8(*user), TCHAR_TO_UTF8(*pw), TCHAR_TO_UTF8(*data_name), port, NULL, 0)) {
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EROER"));
//		return false;
//	}
//	FString sql = "SELECT * FROM " + table_name + " WHERE id<10;";
//	if (mysql_query(conn, TCHAR_TO_UTF8(*sql)))
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EROER"));
//		return false;
//	}
//	MYSQL_RES* res = mysql_store_result(conn);
//	MYSQL_ROW row;
//	row = mysql_fetch_row(res);
//	while (row)
//	{
//		row = mysql_fetch_row(res);
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PF"));
//	}
//	return true;
//}
