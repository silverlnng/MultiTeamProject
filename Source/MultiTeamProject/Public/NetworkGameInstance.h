// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces//OnlineSessionInterface.h"
#include "NetworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTITEAMPROJECT_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	//세션 인터페이스 변수
	IOnlineSessionPtr sessionInterface;

	//몇명까지 서버에 접속할 수 있도록 할 것인가 -> playerRange
	void CreateSession(FString sessionName, FString hostName, int32 playerCount);
	void FindSession();

private:
	FName mySessionName = FName("sessac session");
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	void OncreatedSession(FName roomName, bool bWasSuccessful);
	void OnFoundSessions(bool bWasSuccessful);
};


