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
    // 루트 충돌 컴포넌트 설정
    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    // Skeletal Mesh 컴포넌트 설정
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Skeletal Mesh 설정
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/VigilanteContent/Vehicles/East_Fighter_Su30/SK_East_Fighter_Su30.SK_East_Fighter_Su30"));
    if (SkeletalMeshAsset.Succeeded())
    {
        MeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
    }

    // 스프링 암 컴포넌트 설정
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.0f;
    SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));

    // 카메라 컴포넌트 설정
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    CollisionComponent->SetCapsuleSize(100.0f, 200.0f); // (Radius, Half-Height)
    CollisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Z축 값 조정

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

    // 이동 속도 설정
    float moveSpeed = 100.0f;

    // W/S - X축 (전/후)
    // A/D - Y축 (좌/우)
    // Space/Shift - Z축 (상/하)
    FVector inputVector = value.Get<FVector>();

    // 이동 처리
    AddActorLocalOffset(GetActorForwardVector() * inputVector.X * moveSpeed);
    AddActorLocalOffset(GetActorRightVector() * inputVector.Y * moveSpeed);
    AddActorLocalOffset(FVector(0.0f, 0.0f, inputVector.Z * moveSpeed));
}






void AMyPawn::YawPitchAction(const FInputActionValue& value)
{
    if (!Controller) return;

    // 마우스 이동으로 회전 처리
    FVector2D YawPitchVector = value.Get<FVector2D>();

    // 현재 회전값 가져오기
    FRotator currentRotation = GetActorRotation();

    // Yaw (Z축 회전) 처리: 좌우 반대로 회전
    float newYaw = currentRotation.Yaw - YawPitchVector.X; // 좌우 반대로 회전하도록 음수 적용
    currentRotation.Yaw = newYaw;

    // Pitch (Y축 회전) 처리
    float newPitch = currentRotation.Pitch + YawPitchVector.Y; // 상하 마우스 이동으로 Pitch 값 변경
    currentRotation.Pitch = FMath::Clamp(newPitch, -80.0f, 80.0f); // Pitch의 범위를 -80 ~ 80도로 제한

    // 회전 적용
    SetActorRotation(currentRotation);
}


void AMyPawn::RollAction(const FInputActionValue& value)
{
    if (!Controller) return;

    // X축 회전(Roll) 처리
    float rollInput = value.Get<float>();

    FRotator newRotation(0.0f, 0.0f, rollInput * 10.0f); // 회전 속도 배수 조정 가능
    AddActorLocalRotation(newRotation);
}

void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}





