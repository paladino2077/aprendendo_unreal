// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arma.generated.h"

UCLASS()
class DARKAGE_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arma", meta = (AllowPrivateAccess = "true"));
	class USkeletalMeshComponent* MalhaDaArma;

	UPROPERTY(EditAnywhere, Category = "Arma")
	class USoundBase* SomTiro;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arma", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* SetaArma; 

	UPROPERTY(EditAnywhere, Category = "EfeitosArma")
	class UParticleSystem* EfeitoMuzzle;

	UPROPERTY(EditAnywhere, Category = "EfeitosImpacto")
	class UParticleSystem* ImpactoSangue;

	UPROPERTY(EditAnywhere, Category = "EfeitosImpacto")
	class UParticleSystem* ImpactoGeral;

	UPROPERTY(EditAnywhere, Category = "EfeitoImpacto")
	class UMaterialInterface* DecalImpactoGeral;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Atirar();

};
