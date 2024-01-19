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

	//로비에서 팀나누기 해보기
	//처음 로비레벨이 생성될때 1~4 사이의 랜덤 숫자 생성

	// 만약 playerNum == 랜덤 숫자면 1인팀 . 나머지는 3인팀
	if(playerNum==randomInt)
	{
		Player->PlayerState->SetActorLabel(FString("TeamSolo"));
		//여기서 스폰위치도 지정
	}
	else
	{
		Player->PlayerState->SetActorLabel(FString("TeamTriple"));
	}

	if(Player->PlayerState->GetActorLabel()==FString("TeamSolo"))
	{
		
	}
	
	//playerNum 이 4명 되면 호스트 -> serverTravel 실행
	if(playerNum>=3)
	{
		GetWorld()->ServerTravel("Game/Maps/Lv_main?Listen",true);
	}

	
	
	return Super::ChoosePlayerStart_Implementation(Player);
}
