/**
* Copyright(C) 2024 | Created by Krileon
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAsyncLoopsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
