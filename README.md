# RealHorror Game


## 해야할 것
1. 오브젝트와 일정 거리 이하가 되면 포커스 점 표시 (지금은 거리상관없이 표시되어 있음) -> 아마 캐릭터에 Overlap 걸고 InteractInterface 캐스팅 되면 표시하는 식으로 하면 될듯
2. 오브젝트 바라보면 나오는 글씨 [E]로 고정되어있는데 상황에 맞는 글씨로 바꾸는 기능 (해당 오브젝트를 상속해서 override하고 그 값을 beginplay 할 때 적용하면 될듯)
3. 오브젝트 (수집가능한 것) 상호작용하면 커지면서 돌려볼 수 있게 (동영상 강의 참고)
4. 인벤토리 만들어서 '키' 나 다른 물품들 저장 가능하게
## 완료한 것
1. 오브젝트를 바라보면 아웃라인 그려지고 포커스 점 사라지면서 [E] 글씨 나타남

## 깨달은 점
1. Custom Depth
    1. Custom Depth Stencil 을 활용하고 싶다면
        1. 프로젝트 세팅에서
            1. 커스텀 뎁스-스텐실 패스 (Custom Depth-Stencil) 을 Enabled with Stencil 로 변경
            2. 커스텀 깊이 TTA 지터 (Custom Depth TTA Jitter)는 체크 해제
        2. 포스트 프로세스 볼륨에서 
            1. 포스트 프로세스 머터리얼 (Weighted Blendables)에 배열 엘리먼트 추가 -> 에셋 레퍼런스 -> 적용할 머테리얼 선택
            2. 무한 규모 (unbound) 체크 (해당 바운드에만 적용하고 싶다면 체크해제)
        3. 적용하고하 하는 스태틱 메시에 custom depth 검색
            1. 커스텀 뎁스 패스 렌더 (Render Custom Depth) 체크
            2. 커스텀 깊이 스텐실 값 (Custom Depth Stencil Value) 를 적절하게 조절
    1. c++ 에서 CustomDepth 설정을 건들고 싶다면 Set Function을 활용하자
    (직접 변수 자체를 바꾸는건 작동 안함)
    ```c++
    StaticMeshComponent->bRenderCustomDepth = true;                 // 작동 X
    StaticMeshComponent->SetRenderCustomDepth(true);                // 작동 O
    StaticMeshComponent->CustomDepthStencilValue = 1;               // 작동 X
    StaticMeshComponent->SetCustomDepthStencilValue(1);             // 작동 O
    ```