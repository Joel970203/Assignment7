# 프로젝트 개요

C++ 폰 클래스를 생성했습니다.
입력 매핑을 구현했고 이동을 했습니다.
6축 이동을 구현하는데, 이동자체는 잘 하나, wasd가 바라보는 방향이 아닌, 축 기준으로 이동을하는걸 해결을 하지 못했습니다.
## 동영상

[게임 동영상](https://youtu.be/Pzv5XbbWMd0)


## 기본 구현 확인
- [v] **C++로 Pawn 클래스를 올바르게 생성했는가?**  
- [v] **캡슐/박스/스피어 등 충돌 컴포넌트가 루트로 설정되었는가?**  
- [v] **SkeletalMeshComponent, SpringArm, CameraComponent가 계층 구조로 Attach되어 3인칭 시점이 구성되었는가?**  
- [v] **GameMode에서 DefaultPawnClass가 해당 Pawn 클래스로 지정되었는가?**  
- [v] **WASD, 마우스 회전 입력을 Enhanced Input 액션으로 정의했는가?**  
- [v] **Input Mapping Context (IMC)에 액션을 바인딩하고, 프로젝트/레벨에서 이를 활성화했는가?**  
- [v] **SetupPlayerInputComponent()에서 액션을 올바르게 바인딩하여, MoveForward, MoveRight, Look 등 함수를 호출하도록 했는가?**  
- [v] **AddActorLocalOffset, AddActorLocalRotation 등을 통해 키보드(WASD)와 마우스 입력에 따라 Pawn이 움직이고 회전하는가?**  
- [x] **이동 방향이 카메라 또는 Pawn의 전후좌우를 기준으로 올바르게 설정되었는가?**  
- [v] **회전 시 마우스 이동 축(X, Y)에 따라 좌우/상하 시점이 정상적으로 변하는가?**  

## 이해도 평가
- [v] **Unreal 엔진에서 Pawn이 어떻게 동작하며, PlayerController가 Pawn을 Possess해서 조작한다는 개념을 정확히 이해했는가?**  
- [v] **Pawn의 기본 라이프사이클에 대한 이해를 코드에서 확인할 수 있는가?**  
- [v] **충돌 컴포넌트를 루트로 둬야 하는 이유를 알고 있는가?**  
- [v] **Enhanced Input에서 액션, 축, 매핑 컨텍스트, 바인딩의 관계를 명확히 파악하고 있는가?**  
- [v] **Pawn 이동 시 AddActorLocalOffset, AddActorRotation을 프레임 독립적으로 사용하기 위해 DeltaTime 처리를 이해하고 있는가?**  
- [v] **카메라 회전과 Pawn 회전의 차이를 정확히 구분했는가?**  

## 우수성 평가
- [v] **6자유도 비행체 (드론) 형태로 구현해, 상하/전후/좌우 이동과 피치·롤·요 회전이 가능한가?**  
- [v] **Enhanced Input 액션을 세분화하여 매핑했는가?**  
- [x] **시연 영상에서 비행체가 자유롭게 움직이며 충돌 처리도 잘 되는지 확인되는가?**  
- [x] **Pawn이 지면 위에서만 이동하는 것이 아니라, 공중에 있을 때 중력을 받아 서서히 낙하하는 로직이 구현되었는가?**  
- [x] **착지 혹은 충돌 판정이 자연스럽게 처리되는가?**  
- [x] **에어컨트롤 (공중에서의 WASD 제어)과 낙하 속도/중력 가속도 등 세부 파라미터가 적절히 조정되어 있는가?**  
