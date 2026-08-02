/**
* Copyright(C) 2024 | Created by Krileon
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Delegates/IDelegateInstance.h"
#include "AsyncForLoop.generated.h"

UCLASS( Blueprintable )
class ASYNCLOOPS_API UAsyncForLoop : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOAsyncForLoopSignature, int, Index );

	virtual void Activate() override;		

	UPROPERTY( BlueprintAssignable, Category = "AsyncLoops" )
		FOAsyncForLoopSignature LoopBody;

	UPROPERTY( BlueprintAssignable, Category = "AsyncLoops" )
		FOAsyncForLoopSignature Completed;

	UFUNCTION( BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true" ), Category = "AsyncLoops", DisplayName = "Async For Loop" )
		static UAsyncForLoop* AsyncForLoop(
			int FirstIndex = 0,
			int LastIndex = 0
		);

	UFUNCTION( BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ), Category = "AsyncLoops", DisplayName = "Async Delay For Loop" )
		static UAsyncForLoop* AsyncDelayForLoop(
			UObject* WorldContextObject,
			int FirstIndex = 0,
			int LastIndex = 0,
			float Delay = 0.01f
		);

	UFUNCTION( BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject" ), Category = "AsyncLoops", DisplayName = "Async Burst For Loop" )
		static UAsyncForLoop* AsyncBurstForLoop(
			UObject* WorldContextObject,
			int FirstIndex = 0,
			int LastIndex = 0,
			float Delay = 0.1f,
			int Burst = 5
		);

protected:
	class UWorld* World = nullptr;
	int FirstIndex = 0;
	int LastIndex = 0;
	int CurrentIndex = 0;
	float Delay = 0.f;
	int Burst = 0;
	FTimerHandle DelayTimerHandle;

	UFUNCTION()
		void DelayLoop();
};