// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/HTTPResponseManager.h"


void UHTTPResponseManager::OnHttpResponseReceivedManagerStatic(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, const FGameFuseAPIResponseCallback* CompletionCallback)
{
    const int32 ResponseCode = Response->GetResponseCode();
    const FString ResponseStr = Response->GetContentAsString();

    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Failed"));
        if (CompletionCallback->IsBound()) CompletionCallback->Execute(bWasSuccessful, "Game Fuse HTTP Request Failed");
        return;
    }
    
    if (ResponseCode == 200)
    {
        // const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
        // TSharedPtr<FJsonObject> JsonObject;
        //
        // if (!FJsonSerializer::Deserialize(Reader, JsonObject))
        // {
        //     UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Failed To Parse JSON Response From API"));
        //     if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, 0, "Game Fuse Failed To Parse JSON Response From API");
        //     return;
        // }

        // if(JsonObject->HasField("id") && JsonObject->HasField("game_variables")) // the request is for SetUpGame and Variables
        // {
        //     SetSetUpGameInternal(JsonObject);
        //     SetVariablesInternal(ResponseStr);
        // }
        // else if (JsonObject->HasField("leaderboard_entries"))                    // the request is for : Leaderboards
        // {
        //     SetLeaderboardsInternal(JsonObject);
        // }else if (JsonObject->HasField("store_items"))                           // the request is for : Store Items
        // {
        //     SetStoreItemsInternal(JsonObject);
        // }else if (JsonObject->HasField("mailer_response"))                       // the request is for : forgot email
        // {
        //     UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Forgot Password Email Sent!"));
        // }else                                                                    // the request is for : nothings !
        // {
        //     UE_LOG(LogTemp, Warning, TEXT("LogGameFuse :  Unknown Json"));
        // }
        
        if (CompletionCallback->IsBound()) CompletionCallback->Execute(bWasSuccessful, ResponseStr);
    }
    else
    {
        if (CompletionCallback->IsBound()) CompletionCallback->Execute(bWasSuccessful, ResponseStr);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Returned Status Code %d"), ResponseCode);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Response : %s"), *ResponseStr);
    }
}

void UHTTPResponseManager::OnHttpResponseReceivedManagerUser(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, const FGameFuseAPIResponseCallback CompletionCallback)
{
    const int32 ResponseCode = Response->GetResponseCode();
    const FString ResponseStr = Response->GetContentAsString();

    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Failed"));
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, "Game Fuse HTTP Request Failed");
        return;
    }
    
    if (ResponseCode == 200)
    {
        // const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
        // TSharedPtr<FJsonObject> JsonObject;
        //
        // if (!FJsonSerializer::Deserialize(Reader, JsonObject))
        // {
        //     UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Failed To Parse JSON Response From API"));
        //     if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, "Game Fuse Failed To Parse JSON Response From API");
        //     return;
        // }
        //
        // if(JsonObject->HasField("id") && JsonObject->HasField("username")) // the request is for : SignUp or SignIn
        // {
        //     SetSignInInternal(JsonObject);
        // }
        // else if (JsonObject->HasField("game_user_attributes"))             // the request is for : Attributes
        // {
        //     SetAttributesInternal(JsonObject);
        // }else if (JsonObject->HasField("game_user_store_items"))           // the request is for : User Store Items
        // {
        //     SetCreditsInternal(JsonObject);
        //     SetStoreItemsInternal(JsonObject);
        // }else if (JsonObject->HasField("leaderboard_entries"))                    // the request is for : Leaderboards
        // {
        //     SetLeaderboardsInternal(JsonObject);
        // }else if (JsonObject->HasField("credits"))                         // the request is for : Update the Credits
        // {
        //     SetCreditsInternal(JsonObject);
        // }else if (JsonObject->HasField("score"))                           // the request is for : Update the Scores
        // {
        //     SetScoresInternal(JsonObject);
        // }else                                                              // the request is for : nothings !
        // {
        //     UE_LOG(LogTemp, Warning, TEXT("LogGameFuse :  Unknown Json"));
        // }
        
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
    }
    else
    {
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Returned Status Code %d"), ResponseCode);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Response : %s"), *ResponseStr);
    }
}
