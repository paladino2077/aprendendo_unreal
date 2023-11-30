#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Personagem_FPS.generated.h"

UCLASS()
class DARKAGE_API APersonagem_FPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagem_FPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverFrenteTras(float Valor);

	void MoverEsquerdaDireita(float Valor);

	void Agachar();

	void Desagachar();

	void Pular();

	void Despular();

	UPROPERTY(EditAnywhere, Category = "Arma")
	TSubclassOf<class AArma> BP_ArmaRifle;

	UPROPERTY(BlueprintReadOnly, Category = "Pulo")
	bool bEstaPulando;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmCamera;

public:	

	class AArma* ArmaPlayer;

	void Atirar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
