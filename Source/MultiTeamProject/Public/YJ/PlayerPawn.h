// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "PlayerPawn.generated.h"

UCLASS()
class MULTITEAMPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveIA;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireIA;
	
	UPROPERTY(EditAnywhere,Category = "Mysetting")
	class UBoxComponent* myBoxComp; 

	UPROPERTY(EditAnywhere,Category = "Mysetting")
	class UStaticMeshComponent* myMeshComp;

	UPROPERTY(EditAnywhere, Category = "Mysetting")
	AActor* crossHair;
	UPROPERTY(EditAnywhere, Category = "Mysetting")
	AActor* cannon;
	UPROPERTY(EditAnywhere, Category = "Mysetting")
    float crossHairOffest;
	UPROPERTY(EditAnywhere, Category = "Mysetting")
	float cannonOffest_x;
	UPROPERTY(EditAnywhere, Category = "Mysetting")
	float cannonOffest_y;
private:
	void Move(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);
	
};
