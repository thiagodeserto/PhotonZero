// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "common/LoadBalancingListener.h"
#include "GameFramework/Actor.h"
#include "PhotonLBClient.generated.h"

/**
 * 
 */
UCLASS()
class APhotonLBClient : public AActor, public BaseView
{
	GENERATED_UCLASS_BODY()
	void BeginPlay();
	void Tick(float DeltaSeconds);

public:
	// Demo BaseView overrrides (View implementation).
	virtual void info(const char* format, ...);
	virtual void warn(const char* format, ...);
	virtual void error(const char* format, ...);
//	virtual void initPlayers() {}

	// Some of the overrides used as events in UE blueprints direcltly with only int's replaced with int32's since int unsupported by UFUNCTION.	
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void removePlayer(int32 playerNr);
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void changePlayerPos(int32 playerNr, int32 x, int32 y, int32 z, int32 a, int32 b, int32 c);
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void changeCurrentPos(int32 x, int32 y, int32 z, int32 a, int32 b, int32 c);

	virtual void updateState(int state, const char* stateStr, const char* joinedRoomName) {
		updateState(state, FString(stateStr), FString(joinedRoomName));
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void updateState(int32 state, const FString& stateStr, const FString& joinedRoomName);

	virtual void addPlayer(int playerNr, const char* playerName, bool local) { 
		addPlayer(playerNr, FString(playerName), local);
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void addPlayer(int32 playerNr, const FString& playerName, bool local);

	virtual void updateRoomList(const char* roomNames[], unsigned int size) {
		TArray<FString> a;
		for (unsigned int i = 0; i < size;++i) {
			a.Push(FString(roomNames[i]));
		}
		updateRoomList(a);
	}
	UFUNCTION(BlueprintImplementableEvent, Category = "PhotonZero")
	virtual void updateRoomList(const TArray<FString>& roomNames);

	// end of Demo BaseView overrrides 

	// Exposing demo properties to blueprint 
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo)
//	bool gridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotonZero")
	FString userName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotonZero")
	FString serverAddress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotonZero")
	FString AppID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotonZero")
	FString appVersion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhotonZero")
	bool automove;

	// Exposing demo methods to blueprint 
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	void ChangeName(FString name);
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	void NewGame();
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	void Leave();
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	void JoinRoom(FString gameId);
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	void SetLocalPlayerPos(int32 x, int32 y, int32 z, int32 a, int32 b, int32 c);

	// Util
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	bool IsInLobby();
	UFUNCTION(BlueprintCallable, Category = "PhotonZero")
	bool IsInRoom();

private:
	ExitGames::LoadBalancing::Client* client;
	LoadBalancingListener* listener;
};
