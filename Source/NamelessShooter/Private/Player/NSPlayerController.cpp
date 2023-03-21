// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/NSPlayerController.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"

void ANSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
}

void ANSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (0) SetPawnRotationToMouse();
}

//������������� ����������� ����� � ����� 
void ANSPlayerController::SetPawnRotationToMouse()
{
	if (!GetWorld() || !GetPawn()) return;
	FVector MouseLocation;
	FVector MouseDirection;
	
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	auto PawnSpringArmComponent = Cast<USpringArmComponent>(GetPawn()->GetComponentByClass(USpringArmComponent::StaticClass()));

	auto WorldMouseLocation = MouseLocation + (-MouseDirection * (1170.0f/ MouseDirection.Z));
	auto CurrentMouseLocation = FVector(WorldMouseLocation.X, WorldMouseLocation.Y, GetPawn()->GetActorLocation().Z + 50);

	UE_LOG(LogTemp, Error, TEXT("loc %f, dir %f"), MouseLocation.Z, MouseDirection.Z);


	//(���� ����� ����� 120 �� ����������)
	if ((CurrentMouseLocation - GetPawn()->GetActorLocation()).Size() > 120.0f)
	{
		NeedToRotating = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), CurrentMouseLocation);
	}
	
	GetPawn()->SetActorRotation(FRotator(GetPawn()->GetActorRotation().Pitch, NeedToRotating.Yaw, GetPawn()->GetActorRotation().Roll));
	DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), WorldMouseLocation, FColor::Red, false, 0.2f);
}
