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
		//Ű������ �Է°��� ���� , ũ�ν���� �Ѵ� �ޱ�
		//������ �Է°��� ȸ������ �ޱ� => ȸ���� ���������� �ް��ϱ�
		//���ڽ��� ������ �����ϱ�
		//CurrentValue ���� ������ �ؾ���
		
		SetActorRotation(rot);
		//cannon->SetActorLocation(GetActorLocation() + currentValue * crossHairOffest * GetWorld()->GetDeltaSeconds(), true);
		//crossHair->SetActorLocation(GetActorLocation() + currentValue * cannonOffest * GetWorld()->GetDeltaSeconds(), true);
	}
}

void APlayerPawn::InputFire(const FInputActionValue& Value)
{
	if (Controller && Value.Get<bool>() == true) //������ ������ . �Է°� 
		{

			// �Ѿ� �����ϱ�
			
			// 1) �Ѿ� BP �����
			// 2) �Ѿ��� projectile���� �Ҳ��� , physics���� �Ұ��� �����ϱ� 
			
			// ���� (��� ����-), �Ҹ��� ���� , �Ҹ� �� ��ġ 
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSound, myArrowComp->GetComponentLocation());
			
		}
}


