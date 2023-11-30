#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Personagem_FPS.generated.h"

UCLASS()
class DARKAGE_API APersonagem_FPS : public ACharacter
{
	GENERATED_BODY()

public:
	APersonagem_FPS();

protected:
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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
