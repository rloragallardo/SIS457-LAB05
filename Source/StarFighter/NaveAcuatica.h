// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nave.h"
#include "NaveAcuatica.generated.h"

/**
 *
 */
UCLASS()
class STARFIGHTER_API ANaveAcuatica : public ANave
{
	GENERATED_BODY()
private:

	//===================================================================================================================================================================
	ANaveAcuatica();

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired; 
	FTimerHandle MemberTimerHandle;
public:
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector GunOffset;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireRate;
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedAcuatica;

	float MovingAX;
	float MovingAY;


public:

	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds);

	void FireAcuatica();
	void FireShotAcuatica(FVector FireDirectionEnemigo);


	void ShotTimerExpired();

public:
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal,
			FVector NormalImpulse, const FHitResult& Hit)override;



};

