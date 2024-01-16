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

	//���� �������̽� ����
	IOnlineSessionPtr sessionInterface;

	//������ ������ ������ �� �ֵ��� �� ���ΰ� -> playerRange
	void CreateSession(FString sessionName, FString hostName, int32 playerCount);
	void FindSession();

private:
	FName mySessionName = FName("sessac session");
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	void OncreatedSession(FName roomName, bool bWasSuccessful);
	void OnFoundSessions(bool bWasSuccessful);
};


