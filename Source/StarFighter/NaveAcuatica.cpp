// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAcuatica.h"
#include "NaveAereaJugador.h"
#include "Kismet/GameplayStatics.h"
#include "Proyectil.h"
ANaveAcuatica::ANaveAcuatica()
{
	MoveSpeedAcuatica = 50.0f;
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 2.0f;
	bCanFire = true;

	MovingAX = 0.0f;
	MovingAY = 0.0f;

}
void ANaveAcuatica::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANaveAcuatica::FireAcuatica, 02.0f, true, 3.0f);
}

void ANaveAcuatica::Tick(float DeltaSeconds)
{

	srand(time(NULL));

	MovingAX = rand() % 18 - 10;
	MovingAY = rand() % 18 - 10;

	const FVector MoveDirection = FVector(MovingAX, MovingAY, 0.0f);
	const FVector Movement = MoveDirection * MoveSpeedAcuatica * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}

	ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); 
	if (!avatar)
	{
		return;

	}
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	toPlayer.Normalize();

	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0;
	RootComponent->SetWorldRotation(toPlayerRotation);

}

void ANaveAcuatica::FireAcuatica()
{


	bCanFire = true;
	const FVector FireDirectionAcuatica = FVector(MovingAX, MovingAY, 0.0f).GetClampedToMaxSize(1.0f); 

	FireShotAcuatica(FireDirectionAcuatica);

}

void ANaveAcuatica::FireShotAcuatica(FVector FireDirectionAcuatica)
{
	if (bCanFire == true)
	{
		if (FireDirectionAcuatica.SizeSquared() > 0.0f)
		{
			ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (!avatar)
			{
				return;

			}
			FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();

			const FRotator FireRotation = toPlayer.Rotation(); 
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAcuatica::ShotTimerExpired, FireRate);

		}
	}


}

void ANaveAcuatica::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAcuatica::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AProyectil* Choque = Cast<AProyectil>(Other); 
	if (Choque != nullptr)
	{

		Destroy();

	}
}