// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// 위치 및 회전 값
FVector position = FVector(0, 50, 0);
FVector rotation = FVector(0, 0, 0);

float elapsedTime = 0;	// delay 구현을 위한 경과 시간
int cnt = 1;			// 호출 횟수
int evtCnt = 0;			// 이벤트 발생 횟수
float dist = 0;			// 총 이동한 거리
int lastCnt = 11;		// 이동 종료 횟수

void Move(FVector& pos);
void Turn(FVector& rot);
void TriggerEvent();

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (cnt < lastCnt) elapsedTime += DeltaTime;

	// 이동 및 회전
	if(cnt < lastCnt && elapsedTime > 1.0f){
		GEngine->AddOnScreenDebugMessage(
			-1, 
			3, 
			FColor::White, 
			FString::Printf(TEXT("현재 이동 수: %d"), cnt));

		Move(position);
		Turn(rotation);

		cnt++;
		elapsedTime = 0;
	}
	//데이터 요약 리포트 출력
	else if (cnt == lastCnt) {
		cnt++;
		GEngine->AddOnScreenDebugMessage(
			-1, 
			3, 
			FColor::Yellow, 
			FString::Printf(TEXT("총 이동 거리: %.2fcm"), dist)
		);

		GEngine->AddOnScreenDebugMessage(
			-1,
			3,
			FColor::Yellow,
			FString::Printf(TEXT("이벤트 발생 횟수: %d"), evtCnt)
		);
	}
}

// 이동 및 이벤트 호출
void Move(FVector& pos) {
	// 랜덤값(0~10)
	int dx = FMath::RandRange(0, 10);
	int dy = FMath::RandRange(0, 10);
	int dz = FMath::RandRange(0, 10);

	// 이동한 거리 계산
	float newDist = FVector::Dist(pos, pos + FVector(dx, dy, dz));
	dist += newDist;

	pos.X += dx;
	pos.Y += dy;
	pos.Z += dz;

	GEngine->AddOnScreenDebugMessage(
		-1,
		3,
		FColor::Cyan,
		FString::Printf(TEXT("이동한 좌표: (%.1f, %.1f, %.1f)"), pos.X, pos.Y, pos.Z)
	);

	// 이벤트 호출(50%)
	int evtOcur = FMath::RandRange(0, 1);
	if (evtOcur == 1) TriggerEvent();
}

// 회전
void Turn(FVector& rot) {
	// 랜덤값 연산(-10~10)
	rot.X += FMath::RandRange(-10, 10);
	rot.Y += FMath::RandRange(-10, 10);
	rot.Z += FMath::RandRange(-10, 10);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3,
		FColor::Magenta,
		FString::Printf(TEXT("현재 회전 값: (%.1f, %.1f, %.1f)"), rot.X, rot.Y, rot.Z)
	);
}

// 이벤트 발생
void TriggerEvent() {
	GEngine->AddOnScreenDebugMessage(
		-1,
		3,
		FColor::Red,
		FString::Printf(TEXT("이벤트 발생!!! 그러나 아무일도 일어나지 않았다..."))
	);
	evtCnt++;
}

