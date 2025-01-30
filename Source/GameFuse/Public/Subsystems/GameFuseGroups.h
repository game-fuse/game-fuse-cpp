#pragma once

#include "CoreMinimal.h"
#include "GameFuseUser.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/GroupsAPIHandler.h"
#include "GameFuseGroups.generated.h"

// Single-cast delegates for C++ callbacks
DECLARE_DELEGATE_OneParam(FGFGroupCallback, const FGFGroup&);
DECLARE_DELEGATE_OneParam(FGFGroupListCallback, const TArray<FGFGroup>&);
DECLARE_DELEGATE_OneParam(FGFGroupConnectionCallback, const FGFGroupConnection&);
DECLARE_DELEGATE_OneParam(FGFGroupActionCallback, bool);

// Blueprint callback
DECLARE_DYNAMIC_DELEGATE_OneParam(FBP_GFGroupCallback, bool, bSuccess);

UCLASS()
class GAMEFUSE_API UGameFuseGroups : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// C++ API
	FGuid CreateGroup(const FGFGroup& Group, FGFGroupCallback TypedCallback);
	FGuid FetchGroup(const int32 GroupId, FGFGroupCallback TypedCallback);
	FGuid FetchAllGroups(FGFGroupListCallback TypedCallback);
	FGuid RequestToJoinGroup(int32 GroupId, FGFGroupConnectionCallback TypedCallback);
	FGuid DeleteGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid JoinGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid LeaveGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid FetchUserGroups(FGFGroupListCallback TypedCallback);
	FGuid SearchGroups(const FString& Query, FGFGroupListCallback TypedCallback);
	FGuid AddAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	FGuid RemoveAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	FGuid AddAttribute(const int32 GroupId, const FString& Key, const FString& Value, FGFGroupActionCallback TypedCallback);
	FGuid UpdateAttribute(const int32 GroupId, const int32 AttributeId, const FString& Value, FGFGroupActionCallback TypedCallback);
	FGuid DeleteAttribute(const int32 GroupId, const int32 AttributeId, FGFGroupActionCallback TypedCallback);
	FGuid RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, FGFGroupActionCallback TypedCallback);

	// Blueprint API
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_CreateGroup(const FGFGroup& Group, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_FetchGroup(const int32 GroupId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_FetchAllGroups(FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_RequestToJoinGroup(int32 GroupId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_DeleteGroup(const int32 GroupId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_JoinGroup(const int32 GroupId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_LeaveGroup(const int32 GroupId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_FetchUserGroups(FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_SearchGroups(const FString& Query, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_AddAdmin(const int32 GroupId, const int32 UserId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_RemoveAdmin(const int32 GroupId, const int32 UserId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_AddAttribute(const int32 GroupId, const FString& Key, const FString& Value, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_UpdateAttribute(const int32 GroupId, const int32 AttributeId, const FString& Value, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_DeleteAttribute(const int32 GroupId, const int32 AttributeId, FBP_GFGroupCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_AcceptGroupJoinRequest(const int32 ConnectionId, const int32 UserId, FBP_GFGroupCallback Callback)
	{
		FGFGroupActionCallback TypedCallback;
		TypedCallback.BindLambda([Callback](bool bSuccess) {
			Callback.ExecuteIfBound(bSuccess);
		});
		RespondToGroupJoinRequest(ConnectionId, UserId, EGFInviteRequestStatus::Accepted, TypedCallback);
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	void BP_DeclineGroupJoinRequest(const int32 ConnectionId, const int32 UserId, FBP_GFGroupCallback Callback)
	{
		FGFGroupActionCallback TypedCallback;
		TypedCallback.BindLambda([Callback](bool bSuccess) {
			Callback.ExecuteIfBound(bSuccess);
		});
		RespondToGroupJoinRequest(ConnectionId, UserId, EGFInviteRequestStatus::Declined, TypedCallback);
	}

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetUserGroups() const
	{
		return UserGroups;
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetAllGroups() const
	{
		return AllGroups;
	}

	TObjectPtr<UGroupsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

private:

	UPROPERTY()
	TObjectPtr<UGroupsAPIHandler> RequestHandler;

	// Cached group data
	TArray<FGFGroup> UserGroups;
	TArray<FGFGroup> AllGroups;

	// Internal response handlers
	void HandleGroupResponse(const FGFAPIResponse& Response);
	void HandleGroupListResponse(const FGFAPIResponse& Response);
	void HandleGroupConnectionResponse(const FGFAPIResponse& Response);
	void HandleGroupActionResponse(const FGFAPIResponse& Response);

	// User callbacks storage
	TMap<FGuid, FGFGroupCallback> GroupCallbacks;
	TMap<FGuid, FGFGroupListCallback> GroupListCallbacks;
	TMap<FGuid, FGFGroupConnectionCallback> GroupConnectionCallbacks;
	TMap<FGuid, FGFGroupActionCallback> GroupActionCallbacks;
};