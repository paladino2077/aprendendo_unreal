#include "BotAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "BotCharacter.h"
#include "Engine/Engine.h"
#include "Arma.h"

ABotAIController::ABotAIController()
{
	// construtor que cria o component de sensores do BotInimigo
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensingComp"));
	
	// aqui define como os sensores do inimigo deverão atuar
	// deve fazer a varredura sensorial a cada 1/4 de segundo .25
	PawnSensingComp->SensingInterval = .25f;

	// detecção sensivel apenas de Players(Jogadores)
	PawnSensingComp->bOnlySensePlayers = true;
	
	// o angulo de visão de detecção deve ser de 180 graus, isso facilita também ver as costas
	PawnSensingComp->SetPeripheralVisionAngle(180.f); 

	// o raio de visão será de 3000 unidades
	PawnSensingComp->SightRadius = 3000.f;

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComp"));
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAIController::OnSeePawn);

	if (BehaviorTree) {
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
		BlackBoardComp->SetValueAsBool("DevePerambular", true);
	}

}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackBoardComp && SensedPawn) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Eu estou te vendo"));
		BlackBoardComp->SetValueAsObject("Inimigo", SensedPawn);
		BlackBoardComp->SetValueAsBool("DevePerambular", false);
		ABotCharacter* Bot = Cast<ABotCharacter>(GetPawn());
		Bot->ArmaInimigo->Atirar();
	}
}
