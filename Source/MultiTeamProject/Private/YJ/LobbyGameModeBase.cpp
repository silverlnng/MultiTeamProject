// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ/LobbyGameModeBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	randomInt =FMath::RandRange(1,4);
	UE_LOG(LogTemp, Warning, TEXT("%s(%d) playerNum :%d"), *FString(__FUNCTION__), __LINE__,randomInt);
}

AActor* ALobbyGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	++playerNum;
	UE_LOG(LogTemp, Warning, TEXT("%s(%d) playerNum :%d"), *FString(__FUNCTION__), __LINE__,playerNum);

	//�κ񿡼� �������� �غ���
	//ó�� �κ񷹺��� �����ɶ� 1~4 ������ ���� ���� ����

	// ���� playerNum == ���� ���ڸ� 1���� . �������� 3����
	if(playerNum==randomInt)
	{
		Player->PlayerState->SetActorLabel(FString("TeamSolo"));
		//���⼭ ������ġ�� ����
	}
	else
	{
		Player->PlayerState->SetActorLabel(FString("TeamTriple"));
	}

	if(Player->PlayerState->GetActorLabel()==FString("TeamSolo"))
	{
		
	}
	
	//playerNum �� 4�� �Ǹ� ȣ��Ʈ -> serverTravel ����
	if(playerNum>=3)
	{
		GetWorld()->ServerTravel("Game/Maps/Lv_main?Listen",true);
	}

	
	
	return Super::ChoosePlayerStart_Implementation(Player);
}
