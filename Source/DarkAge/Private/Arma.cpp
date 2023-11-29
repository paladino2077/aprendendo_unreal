#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "WorldCollision.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"

AArma::AArma()
{
	PrimaryActorTick.bCanEverTick = true;

	EfeitoMuzzle = nullptr;
	ImpactoSangue = nullptr;
	ImpactoGeral = nullptr;
	DecalImpactoGeral = nullptr;
	SomTiro = nullptr;

	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MalhaDaArma"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshDaArma(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));

	if (MeshDaArma.Succeeded()) {
		MalhaDaArma->SetSkeletalMesh(MeshDaArma.Object);
	}

	RootComponent = MalhaDaArma;

	SetaArma = CreateDefaultSubobject<UArrowComponent>(FName("SetaCanoArma"));
	SetaArma->SetupAttachment(MalhaDaArma, FName("MuzzleFlashSocket"));
	SetaArma->SetRelativeLocation(FVector(1.5f, 0.f, -1.2f));
	SetaArma->SetRelativeScale3D(FVector(0.3f, 0.8f, 0.7f));
}

void AArma::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArma::Atirar()
{
	SetaArma = FindComponentByClass<UArrowComponent>();
	if (SetaArma) {
		FVector Inicio = SetaArma->GetComponentLocation();
		FVector Direcao = SetaArma->GetComponentRotation().Vector();
		FVector Fim = Inicio + (Direcao * 1000);

		FHitResult InfoImpacto;
		FCollisionQueryParams Parametros;
		Parametros.AddIgnoredActor(this);
		Parametros.AddIgnoredActor(GetOwner());
		Parametros.bTraceComplex = true;

		bool AcertouAlgo = GetWorld()->LineTraceSingleByChannel(InfoImpacto, Inicio, Fim, ECollisionChannel::ECC_Visibility, Parametros);
	
		if (SomTiro) {
			UGameplayStatics::PlaySoundAtLocation(SetaArma, SomTiro, Inicio);
		}

		if (AcertouAlgo) {
			UE_LOG(LogTemp, Warning, TEXT("Acertou em Algo"));
			AActor* Ator = InfoImpacto.GetActor();
			
			if (Ator->GetClass()->IsChildOf(ACharacter::StaticClass()) && ImpactoSangue) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoSangue, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);
			}
			else if (ImpactoGeral) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoGeral, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);
				FVector TamanhoVariavel = FVector(FMath::RandRange(10.f, 50.f));
				UGameplayStatics::SpawnDecalAttached(DecalImpactoGeral, TamanhoVariavel, InfoImpacto.GetComponent(), NAME_None, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 60.f);
			}
		}

		if (EfeitoMuzzle) {
			FVector Localizacao = SetaArma->GetComponentLocation();
			FRotator Rotacao = SetaArma->GetComponentRotation();
			FVector Escala = FVector(0.9f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EfeitoMuzzle, Localizacao, Rotacao, Escala, true);
		}

	}

}

