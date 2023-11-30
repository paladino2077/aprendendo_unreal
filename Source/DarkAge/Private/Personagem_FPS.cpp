#include "Personagem_FPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "WorldCollision.h"

APersonagem_FPS::APersonagem_FPS()
{
	PrimaryActorTick.bCanEverTick = true;
	bEstaPulando = false;

	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmCamera")); 
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.0f, 40.0f, 50.0f));
	SpringArmCamera->bEnableCameraLag = true;
	SpringArmCamera->CameraLagSpeed = 40.f;
	SpringArmCamera->SetupAttachment(RootComponent);

	CameraPersonagem = CreateDefaultSubobject<UCameraComponent>(FName("CameraPersonagem"));
	CameraPersonagem->SetupAttachment(SpringArmCamera);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->JumpZVelocity = 125.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APersonagem_FPS::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ArmaPlayer = GetWorld()->SpawnActor<AArma>(BP_ArmaRifle, FTransform(), Parametros);

	ArmaPlayer->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SocketArma"));

}

void APersonagem_FPS::MoverFrenteTras(float Valor)
{
	AddMovementInput(GetActorForwardVector() * Valor);
}

void APersonagem_FPS::MoverEsquerdaDireita(float Valor)
{
	AddMovementInput(GetActorRightVector() * Valor);
}

void APersonagem_FPS::Agachar()
{
	Crouch();
}

void APersonagem_FPS::Desagachar()
{
	UnCrouch();
}

void APersonagem_FPS::Pular()
{
	bEstaPulando = true;
}

void APersonagem_FPS::Despular()
{
	bEstaPulando = false;
}

void APersonagem_FPS::Atirar()
{
	ArmaPlayer->Atirar();
}

// Called every frame
void APersonagem_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APersonagem_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoverFrenteTras", this, &APersonagem_FPS::MoverFrenteTras);
	PlayerInputComponent->BindAxis("MoverEsquerdaDireita", this, &APersonagem_FPS::MoverEsquerdaDireita);
	PlayerInputComponent->BindAxis("OlharCimaBaixo", this, &APersonagem_FPS::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("OlharDireitaEsquerda", this, &APersonagem_FPS::AddControllerYawInput);

	PlayerInputComponent->BindAction("Agachar", EInputEvent::IE_Pressed, this, &APersonagem_FPS::Agachar);
	PlayerInputComponent->BindAction("Agachar", EInputEvent::IE_Released, this, &APersonagem_FPS::Desagachar);

	PlayerInputComponent->BindAction("Pular", EInputEvent::IE_Pressed, this, &APersonagem_FPS::Pular);
	PlayerInputComponent->BindAction("Pular", EInputEvent::IE_Released, this, &APersonagem_FPS::Despular);
	
	PlayerInputComponent->BindAction("Atirar", EInputEvent::IE_Pressed, this, &APersonagem_FPS::Atirar);

}



