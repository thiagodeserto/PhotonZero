// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#define _CRT_SECURE_NO_WARNINGS
#include "PhotonZero.h"
#include "PhotonLBClient.h"

void log(FString const& s, FColor color) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, color, s);
}

APhotonLBClient::APhotonLBClient(const class FObjectInitializer& PCIP)
	: Super(PCIP),
	serverAddress("ns.exitgames.com:5058"),
	AppID("<no-app-id>"),
	appVersion("1.0"),
	client(NULL),
	listener(NULL)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APhotonLBClient::BeginPlay() {
	Super::BeginPlay();
	listener = new LoadBalancingListener(this);
	client = new ExitGames::LoadBalancing::Client(*listener, *AppID, *appVersion, *userName);
	listener->setLBC(client);

	automove = listener->getAutomove();

	info("Connecting...");
	client->connect(*serverAddress);
}

void APhotonLBClient::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (client) {
		client->service();

		// should be called on props change only but how do one listen to those changes?
		listener->setAutomove(automove);

		listener->service();
	}
}


void APhotonLBClient::info(const char* format, ...)
{
	char buf[1024];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buf, format, argptr);
	va_end(argptr);

	log(FString("INFO: ") + buf, FColor::Green);
}

void APhotonLBClient::warn(const char* format, ...)
{
	char buf[1024];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buf, format, argptr);
	va_end(argptr);

	log(FString("WARN: ") + buf, FColor::Yellow);
}

void APhotonLBClient::error(const char* format, ...)
{
	char buf[1024];
	va_list argptr;
	va_start(argptr, format);
	vsprintf(buf, format, argptr);
	va_end(argptr);

	log(FString("ERROR: ") + buf, FColor::Red);
}

void APhotonLBClient::ChangeName(FString name) {
	userName = name;
}

void APhotonLBClient::NewGame() {
	listener->createRoom();
}

void APhotonLBClient::Leave() {
	listener->leave();
}

void APhotonLBClient::JoinRoom(FString gameId){
	client->opJoinRoom(ExitGames::Common::JString(*gameId));
}

void APhotonLBClient::SetLocalPlayerPos(int32 x, int32 y, int32 z, int32 a, int32 b, int32 c) {
	listener->setLocalPlayerPos(x, y, z, a, b, c);
}

bool APhotonLBClient::IsInLobby() {
	return client->getState() == ExitGames::LoadBalancing::PeerStates::JoinedLobby || client->getState() == ExitGames::LoadBalancing::PeerStates::AuthenticatedComingFromGameserver;
}

bool APhotonLBClient::IsInRoom() {
	return client->getState() == ExitGames::LoadBalancing::PeerStates::Joined;
}