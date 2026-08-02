/**
* Copyright(C) 2024 | Created by Krileon
*/

#include "AsyncLoops/Public/AsyncForLoop.h"

void UAsyncForLoop::Activate()
{
	if ( Delay > 0.f ) {
		DelayLoop();
		return;
	}

	for ( int32 Index = FirstIndex; Index <= LastIndex; ++Index ) {
		LoopBody.Broadcast( Index );
	}

	Completed.Broadcast( 0 );

	SetReadyToDestroy();
}

void UAsyncForLoop::DelayLoop()
{
	if ( ! IsValid( World ) ) {
		Completed.Broadcast( 0 );

		SetReadyToDestroy();
		return;
	}

	World->GetTimerManager().ClearTimer( DelayTimerHandle );

	LoopBody.Broadcast( CurrentIndex );

	if ( CurrentIndex >= LastIndex ) {
		Completed.Broadcast( 0 );

		SetReadyToDestroy();
		return;
	}

	++CurrentIndex;

	if ( Burst > 1 ) {
		for ( int32 Index = FirstIndex; Index <= ( Burst - 1 ); ++Index ) {
			LoopBody.Broadcast( CurrentIndex );

			if ( CurrentIndex >= LastIndex ) {
				Completed.Broadcast( 0 );

				SetReadyToDestroy();
				return;
			}
			
			++CurrentIndex;
		}
	}

	World->GetTimerManager().SetTimer( DelayTimerHandle, this, &UAsyncForLoop::DelayLoop, Delay, false, Delay );
}

UAsyncForLoop* UAsyncForLoop::AsyncForLoop(
	int FirstIndex,
	int LastIndex
) {
	UAsyncForLoop* BlueprintNode = NewObject<UAsyncForLoop>();

	BlueprintNode->FirstIndex = FirstIndex;
	BlueprintNode->LastIndex = LastIndex;

	return BlueprintNode;
}

UAsyncForLoop* UAsyncForLoop::AsyncDelayForLoop(
	UObject* WorldContextObject,
	int FirstIndex,
	int LastIndex,
	float Delay
) {
	UAsyncForLoop* BlueprintNode = NewObject<UAsyncForLoop>();

	if ( IsValid( WorldContextObject ) ) {
		BlueprintNode->World = WorldContextObject->GetWorld();
	}

	BlueprintNode->FirstIndex = FirstIndex;
	BlueprintNode->LastIndex = LastIndex;
	BlueprintNode->Delay = Delay;

	return BlueprintNode;
}

UAsyncForLoop* UAsyncForLoop::AsyncBurstForLoop(
	UObject* WorldContextObject,
	int FirstIndex,
	int LastIndex,
	float Delay,
	int Burst
) {
	UAsyncForLoop* BlueprintNode = NewObject<UAsyncForLoop>();

	if ( IsValid( WorldContextObject ) ) {
		BlueprintNode->World = WorldContextObject->GetWorld();
	}

	BlueprintNode->FirstIndex = FirstIndex;
	BlueprintNode->LastIndex = LastIndex;
	BlueprintNode->Delay = Delay;
	BlueprintNode->Burst = Burst;

	return BlueprintNode;
}