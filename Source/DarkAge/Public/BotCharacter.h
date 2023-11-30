#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

UCLASS()
class DARKAGE_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()

	public:
		ABotCharacter();

	protected:
		virtual void BeginPlay() override;
		
		UPROPERTY(EditAnywhere, Category = "Arma")
		TSubclassOf<class AArma> BP_ArmaRifle;
		
		UPROPERTY(EditDefaultsOnly, Category = "Health")
		float Health;

	public:	
		virtual void Tick(float DeltaTime) override;

		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
		class AArma* ArmaInimigo;

};
