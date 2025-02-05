#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class ASSIGNMENT7_API AMyPawn : public APawn
{
    GENERATED_BODY()

public:
    AMyPawn();
   

public:
    virtual void Tick(float DeltaTime) override;

protected:
    //virtual void BeginPlay() override;
    FVector Velocity;
    UPROPERTY(VisibleAnywhere)
    class UCapsuleComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
    class USkeletalMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere)
    class UFloatingPawnMovement* MovementComponent; // Ãß°¡

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
    float MoveSpeed = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
    float RotationSpeed = 50.0f;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void MoveAction(const FInputActionValue& value);
    UFUNCTION()
    void YawPitchAction(const FInputActionValue& value);
    UFUNCTION()
    void RollAction(const FInputActionValue& value);

};