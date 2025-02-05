#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "FlightPlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    Velocity = FVector::ZeroVector;
    // ��Ʈ �浹 ������Ʈ ����
    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    // Skeletal Mesh ������Ʈ ����
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Skeletal Mesh ����
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/VigilanteContent/Vehicles/East_Fighter_Su30/SK_East_Fighter_Su30.SK_East_Fighter_Su30"));
    if (SkeletalMeshAsset.Succeeded())
    {
        MeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
    }

    // ������ �� ������Ʈ ����
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.0f;
    SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));

    // ī�޶� ������Ʈ ����
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    CollisionComponent->SetCapsuleSize(100.0f, 200.0f); // (Radius, Half-Height)
    CollisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Z�� �� ����

}


void  AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AFlightPlayerController* PlayerController = Cast<AFlightPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::MoveAction
                );
            }


            if (PlayerController->YawPitchAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->YawPitchAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::YawPitchAction
                );
            }


            if (PlayerController->RollAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->RollAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::RollAction
                );
            }
        }
    }
}



void AMyPawn::MoveAction(const FInputActionValue& value)
{
    if (!Controller) return;

    // �̵� �ӵ� ����
    float moveSpeed = 100.0f;

    // W/S - X�� (��/��)
    // A/D - Y�� (��/��)
    // Space/Shift - Z�� (��/��)
    FVector inputVector = value.Get<FVector>();

    // �̵� ó��
    AddActorLocalOffset(GetActorForwardVector() * inputVector.X * moveSpeed);
    AddActorLocalOffset(GetActorRightVector() * inputVector.Y * moveSpeed);
    AddActorLocalOffset(FVector(0.0f, 0.0f, inputVector.Z * moveSpeed));
}






void AMyPawn::YawPitchAction(const FInputActionValue& value)
{
    if (!Controller) return;

    // ���콺 �̵����� ȸ�� ó��
    FVector2D YawPitchVector = value.Get<FVector2D>();

    // ���� ȸ���� ��������
    FRotator currentRotation = GetActorRotation();

    // Yaw (Z�� ȸ��) ó��: �¿� �ݴ�� ȸ��
    float newYaw = currentRotation.Yaw - YawPitchVector.X; // �¿� �ݴ�� ȸ���ϵ��� ���� ����
    currentRotation.Yaw = newYaw;

    // Pitch (Y�� ȸ��) ó��
    float newPitch = currentRotation.Pitch + YawPitchVector.Y; // ���� ���콺 �̵����� Pitch �� ����
    currentRotation.Pitch = FMath::Clamp(newPitch, -80.0f, 80.0f); // Pitch�� ������ -80 ~ 80���� ����

    // ȸ�� ����
    SetActorRotation(currentRotation);
}


void AMyPawn::RollAction(const FInputActionValue& value)
{
    if (!Controller) return;

    // X�� ȸ��(Roll) ó��
    float rollInput = value.Get<float>();

    FRotator newRotation(0.0f, 0.0f, rollInput * 10.0f); // ȸ�� �ӵ� ��� ���� ����
    AddActorLocalRotation(newRotation);
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}





