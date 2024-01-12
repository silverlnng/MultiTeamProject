// Fill out your copyright notice in the Description page of Project Settings.


#include "firstPlayer.h"


// Sets default values
AfirstPlayer::AfirstPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//샘플 적용 -> 변경(-)
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/samplePlayer/Mesh/SK_EpicCharacter'"));
	if (TempMesh.Succeeded())
	{
			GetMesh()->SetSkeletalMesh(TempMesh.Object);
			GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 70));
	springArmComp->TargetArmLength = 400;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);



}

// Called when the game starts or when spawned
void AfirstPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AfirstPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AfirstPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

