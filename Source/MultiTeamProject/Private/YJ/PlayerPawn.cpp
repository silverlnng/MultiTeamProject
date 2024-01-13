// Fill out your copyright notice in the Description page of Project Settings.


#include "YJ/PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	myBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	SetRootComponent(myBoxComp);
	myMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshCompo"));
	myMeshComp->SetupAttachment(myBoxComp);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);

		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &APlayerPawn::Move);

		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Triggered, this, &APlayerPawn::InputFire);
	}
	
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector currentValue = Value.Get<FVector>();
	const double curX = currentValue.X* cannonOffest_x;
	const double curY = currentValue.Y* cannonOffest_y;
	FRotator rot =FRotator(curY,curX,0);
	
	if (Controller)
	{
		UE_LOG(LogTemp, Log, TEXT("input Vector :: %s"), *currentValue.ToString());
		//키보드의 입력값을 대포 , 크로스헤어 둘다 받기
		//대포는 입력값을 회전에만 받기 => 회전을 연속적으로 받게하기
		//나자신을 대포로 생각하기
		//CurrentValue 값도 제한을 해야함
		
		SetActorRotation(rot);
		//cannon->SetActorLocation(GetActorLocation() + currentValue * crossHairOffest * GetWorld()->GetDeltaSeconds(), true);
		//crossHair->SetActorLocation(GetActorLocation() + currentValue * cannonOffest * GetWorld()->GetDeltaSeconds(), true);
	}
}

void APlayerPawn::InputFire(const FInputActionValue& Value)
{
	if (Controller && Value.Get<bool>() == true) //콘텐츠 외적인 . 입력계 
		{

			// 총알 스폰하기
			
			// 1) 총알 BP 만들기
			// 2) 총알을 projectile으로 할껀지 , physics으로 할건지 선택하기 
			
			// 월드 (어느 월드-), 소리낼 사운드 , 소리 날 위치 
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSound, myArrowComp->GetComponentLocation());
			
		}
}


