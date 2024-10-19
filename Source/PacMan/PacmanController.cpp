// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


#include "PacmanPawn.h"


APacmanPawn * APacmanController::GetPacmanPawn() const
{
	return Cast<APacmanPawn>(GetPawn());
}

void APacmanController::SetupInputComponent() {

	Super::SetupInputComponent();

	InputComponent->BindAction("MoveUp", IE_Pressed, this, &APacmanController::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &APacmanController::MoveDown);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APacmanController::MoveLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APacmanController::MoveRight);

}

bool APacmanController::CanMoveInDirection(const FVector& Direction) const
{
    if (GetPacmanPawn() == nullptr) return false;

    // Position actuelle de Pac-Man
    FVector Start = GetPacmanPawn()->GetActorLocation();

  
    // Calcul de la fin du trace (100 unit�s dans la direction donn�e)
    FVector End = Start + (Direction * 100.0f);

    // Taille de la bo�te (ajustez selon la taille de Pac-Man)
    FVector BoxExtent(60.0f, 60.0f, 60.0f);  // Plus petite bo�te pour am�liorer la pr�cision

    // Param�tres de collision
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetPacmanPawn());  // Ignorer Pac-Man lui-m�me

    // Effectuer un BoxTrace
    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Start,
        End,
        FQuat::Identity,  // Aucune rotation
        ECC_Visibility,   // Canal de visibilit�
        FCollisionShape::MakeBox(BoxExtent),  // Cr�e la forme de la bo�te
        Params
    );

    // D�boggage : Visualiser la BoxTrace
    DrawDebugBox(GetWorld(), Start, BoxExtent, FQuat::Identity, FColor::Green, false, 1.0f);
    DrawDebugBox(GetWorld(), End, BoxExtent, FQuat::Identity, FColor::Red, false, 1.0f);

    // Retourne true si aucun mur n'est d�tect�
    return !(bHit && HitResult.GetActor()->ActorHasTag("Wall"));
}




void APacmanController::MoveUp()
{
    if (GetPacmanPawn() != nullptr && CanMoveInDirection(FVector::LeftVector)) {
        GetPacmanPawn()->SetDirection(FVector::UpVector);
    }
}

void APacmanController::MoveDown()
{
    if (GetPacmanPawn() != nullptr && CanMoveInDirection(FVector::RightVector)) {
        GetPacmanPawn()->SetDirection(FVector::DownVector);
    }
}

void APacmanController::MoveLeft()
{

    if (GetPacmanPawn() != nullptr && CanMoveInDirection(FVector(-1,0,0))) {
        GetPacmanPawn()->SetDirection(FVector::LeftVector);
    }
}

void APacmanController::MoveRight()
{
    if (GetPacmanPawn() != nullptr && CanMoveInDirection(FVector(1,0,0))) {
        GetPacmanPawn()->SetDirection(FVector::RightVector);
    }
}
