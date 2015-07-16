// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "JsonFieldData.generated.h"

// Generate a delegate for the OnGetResult event
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGetResult);

// Generate a delegate for the OnFailed event
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFailed);

UCLASS(BlueprintType, Blueprintable)
class UJsonFieldData : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	/* Internal bind method for the IHTTPRequest::OnProcessRequestCompleted() event */
	void OnReady(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/* Resets the current post data */
	void Reset();

	/* Prefixes the input URL with http:// if needed */
	static FString CreateURL(FString inputURL);

	void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);
public:
	UObject* contextObject;

	/* The actual field data */
	TSharedPtr<FJsonObject> Data;

	/* Contains the actual page content, as a string */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JSON")
	FString Content;

	/* Event which triggers when the content has been retrieved */
	UPROPERTY(BlueprintAssignable, Category = "JSON")
	FOnGetResult OnGetResult;

	/* Event which triggers when the request failed */
	UPROPERTY(BlueprintAssignable, Category = "JSON")
	FOnFailed OnFailed;

	/* Creates a new post data object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON Data", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	static UJsonFieldData* Create(UObject* WorldContextObject);

	/* Adds string data to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add String Field"), Category = "JSON")
	UJsonFieldData* SetString(const FString& key, const FString& value);

	/* Adds a string array to the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add String Array Field"), Category = "JSON")
	UJsonFieldData* SetStringArray(const FString& key, const TArray<FString> arrayData);

	/* Sets nested object data to the post array */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Data Field"), Category = "JSON")
	UJsonFieldData* SetObject(const FString& key, const UJsonFieldData* objectData);

	/* Adds a new post data field to the specified data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Add Object Array Field"), Category = "JSON")
	UJsonFieldData* SetObjectArray(const FString& key, const TArray<UJsonFieldData*> arrayData);

	/* Gets string data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Field"), Category = "JSON")
	FString GetString(const FString& key) const;

	/* Gets a string array with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Array Field", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	TArray<FString> GetStringArray(const FString& key);

	/* Fetches nested post data from the post data */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Data Field", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	UJsonFieldData* GetObject(const FString& key);

	/* Gets an array with post data with the specified key */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Array Field", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	TArray<UJsonFieldData*> GetObjectArray(UObject* WorldContextObject, const FString& key);

	/* Get all keys from the object */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	TArray<FString> GetObjectKeys(UObject* WorldContextObject);

	/* Creates new data from the input string */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "From String"), Category = "JSON")
	void FromString(const FString& dataString);

	/* Creates new data from text json file */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "From File"), Category = "JSON")
	void FromFile(const FString& FilePath);

	/* Posts a request with the supplied post data to the specified page */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Post JSON Request", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	void PostRequest(UObject* WorldContextObject, const FString& url);

	/* Requests a page from the internet with a JSON response */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get JSON Request", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
	static UJsonFieldData* GetRequest(UObject* WorldContextObject, const FString& url);
};