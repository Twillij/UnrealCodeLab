// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialActor.h"

// Sets default values
ASpecialActor::ASpecialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpecialActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpecialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

