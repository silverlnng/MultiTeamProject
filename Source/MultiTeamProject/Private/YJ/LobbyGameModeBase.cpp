// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ/LobbyGameModeBase.h"

AActor* ALobbyGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if(playerNum==0)
	{
		hostPlayer = Player;
	}
	
	++playerNum;
	UE_LOG(LogTemp, Warning, TEXT("%s(%d) playerNum :%d"), *FString(__FUNCTION__), __LINE__,playerNum);
	//playerNum 이 4명 되면 호스트 -> serverTravel 실행
	///Script/Engine.World'/Game/Maps/Lv_main.Lv_main'
	if(playerNum>=4)
	{
		GetWorld()->ServerTravel("Game/Maps/Lv_main?Listen",true);
	}
	
	
	return Super::ChoosePlayerStart_Implementation(Player);
}
