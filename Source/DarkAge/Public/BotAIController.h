#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class DARKAGE_API ABotAIController : public AAIController
{
	GENERATED_BODY()
	
	protected:
		ABotAIController();

		virtual void OnPossess(APawn* InPawn) override;

		UPROPERTY(EditDefaultsOnly)
		class UPawnSensingComponent* PawnSensingComp;

		UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;

		UPROPERTY(EditDefaultsOnly)
		class UBehaviorTreeComponent* BehaviorTreeComp;

		UPROPERTY(EditDefaultsOnly)
		class UBlackboardComponent* BlackBoardComp;

		UFUNCTION()
		void OnSeePawn(class APawn* SensedPawn);

};
