// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Blueprint/UserWidget.h"

void UNetworkGameInstance::Init()
{
	Super::Init();

    sessionInterface = IOnlineSubsystem::Get()->GetSessionInterface();

    if (sessionInterface != nullptr)
    {
        //�����κ��� �̺�Ʈ ���� ���� �Լ��� �����Ѵ�.
        sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,
            &UNetworkGameInstance::OnCreatedSession);
        sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,
            &UNetworkGameInstance::OnFoundSessions);
        sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this,&UNetworkGameInstance::OnJoinedSession);
    }

    //�� ������ ������ ���� ��û�Ѵ�.
    //FTimerHandle createHandler;

}

void UNetworkGameInstance::CreateSession(FString roomName, FString hostName, int32 playerCount)
{
    // ���� ���� ���� �ɼ��� �����ϱ� ���� ����ü ����
    FOnlineSessionSettings sessionSettings;
    sessionSettings.bIsDedicated = false;
    sessionSettings.bAllowInvites = true;
    sessionSettings.bAllowJoinInProgress = true;
    sessionSettings.bAllowJoinViaPresence = true;
    sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
    sessionSettings.bShouldAdvertise = true;
    sessionSettings.bUseLobbiesIfAvailable = true;
    sessionSettings.NumPublicConnections = playerCount;

    // Ŀ���� ���� ���� �߰��ϱ�
    sessionSettings.Set(FName("Room Name"), roomName, EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);
    sessionSettings.Set(FName("Host Name"), hostName, EOnlineDataAdvertisementType::Type::ViaOnlineServiceAndPing);

    sessionInterface->CreateSession(0, mySessionName, sessionSettings);
    UE_LOG(LogTemp, Warning, TEXT("Try to Create Session..."));
    UE_LOG(LogTemp, Warning, TEXT("Current Platform: %s"), *IOnlineSubsystem::Get()->GetSubsystemName().ToString());
}

void UNetworkGameInstance::FindSession()
{
    onFindButtonToggle.Broadcast(false);

    // ���� �˻� ������ �����ϱ�
    sessionSearch = MakeShareable(new FOnlineSessionSearch());
    sessionSearch->bIsLanQuery = true;
    sessionSearch->MaxSearchResults = 10;
    sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);

    // ������ ���� �˻��� ��û�ϱ�
    sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void UNetworkGameInstance::JoinSession(int32 roomNumber)
{
    sessionInterface->JoinSession(0, mySessionName, sessionSearch->SearchResults[roomNumber]);
}

void UNetworkGameInstance::OnCreatedSession(FName sessionName, bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("Session Name: %s"), *sessionName.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Session Create: %s"), bWasSuccessful ? *FString("Success!") : *FString("Failed..."));

    // ��Ƽ �÷��̸� �� ������ �̵��Ѵ�.
    ///Script/Engine.World'/Game/Maps/YJ/YJ_LobbyMap.YJ_LobbyMap'
    GetWorld()->ServerTravel("/Game/Maps/LobbyMap2?Listen", true);
}

void UNetworkGameInstance::OnFoundSessions(bool bWasSuccessful)
{
    TArray<FOnlineSessionSearchResult> results = sessionSearch->SearchResults;

    UE_LOG(LogTemp, Warning, TEXT("Find Results: %s"), bWasSuccessful ? *FString("Success!") : *FString("Failed..."));

    if (bWasSuccessful)
    {
        int32 sessionNum = results.Num();
        UE_LOG(LogTemp, Warning, TEXT("Session Count: %d"), results.Num());
        onNewSearchComplete.Broadcast();

        //for (const FOnlineSessionSearchResult& result : results)
        for (int32 i = 0; i < results.Num(); i++)
        {
            FString foundRoomName;
            results[i].Session.SessionSettings.Get(FName("Room Name"), foundRoomName);
            FString foundHostName;
            results[i].Session.SessionSettings.Get(FName("Host Name"), foundHostName);

            int32 maxPlayerCount = results[i].Session.SessionSettings.NumPublicConnections;
            int32 currentPlayerCount = maxPlayerCount - results[i].Session.NumOpenPublicConnections;

            int32 pingSpeed = results[i].PingInMs;

            // �α׷� Ȯ���ϱ�
            UE_LOG(LogTemp, Warning, TEXT("Room Name: %s\nHost Name: %s\nPlayer Count: (%d/%d)\nPing: %d ms\n\n"), *foundRoomName, *foundHostName, currentPlayerCount, maxPlayerCount, pingSpeed);

            // ��������Ʈ �̺�Ʈ �����ϱ�
            onCreateSlot.Broadcast(foundRoomName, foundHostName, currentPlayerCount, maxPlayerCount, pingSpeed, i);
        }

        onFindButtonToggle.Broadcast(true);
    }

}

void UNetworkGameInstance::OnJoinedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
    UE_LOG(LogTemp, Warning, TEXT("Joined Session: %s"), *sessionName.ToString());

    switch (result)
    {
    case EOnJoinSessionCompleteResult::Success:
    {
        UE_LOG(LogTemp, Warning, TEXT("Join Success!"));

        APlayerController* pc = GetWorld()->GetFirstPlayerController();
        FString url;
        sessionInterface->GetResolvedConnectString(sessionName, url, NAME_GamePort);
        UE_LOG(LogTemp, Warning, TEXT("url: %s"), *url);
            
        if(pc!=nullptr)
        {
            pc->ClientTravel(url, ETravelType::TRAVEL_Absolute);
        }

        break;
    }
    case EOnJoinSessionCompleteResult::SessionIsFull:
        UE_LOG(LogTemp, Warning, TEXT("Session is full..."));
        break;
    case EOnJoinSessionCompleteResult::SessionDoesNotExist:
        UE_LOG(LogTemp, Warning, TEXT("Session Does Not Exist..."));
        break;
    case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
        UE_LOG(LogTemp, Warning, TEXT("Could Not Retrieve Address..."));
        break;
    case EOnJoinSessionCompleteResult::AlreadyInSession:
        UE_LOG(LogTemp, Warning, TEXT("You are already in this session..."));
        break;
    case EOnJoinSessionCompleteResult::UnknownError:
        UE_LOG(LogTemp, Warning, TEXT("Unknown Error occurred!"));
        break;
    default:
        break;
    }
}





