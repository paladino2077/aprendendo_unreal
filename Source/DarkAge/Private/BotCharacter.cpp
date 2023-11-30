#include "BotCharacter.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"


ABotCharacter::ABotCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ArmaInimigo = GetWorld()->SpawnActor<AArma>(BP_ArmaRifle, FTransform(), Parametros);
	ArmaInimigo->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketArma"));
}

void ABotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
