#pragma once

class FSGUI : public ISGUI
{
public:
	/** IModuleInterface implementation */
	void StartupModule();
	void ShutdownModule();
};