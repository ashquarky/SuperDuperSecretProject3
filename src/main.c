#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/thread.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>
#include <sysapp/launch.h>

#include <stdio.h>

#include "emu/EmulationManager.h"

bool MainLoop() {

}

bool initialized = false;
bool InitApp() {
	bool error = false;

	error |= EmulationManagerLoadROM("/vol/content/test.nes");
	OSReport("Loaded ROM, error %d", error);
	error |= EmulationManagerInit();
	OSReport("Initialized EmulationManager, error %d", error);

	if (error) {
		initialized = false;
		OSFatal("Could not init app!");
		return true;
	}

	initialized = true;
	return false;
}

bool DeInitApp() {
	bool error = false;

	error |= EmulationManagerDeInit();

	if (error) {
		initialized = true;
		OSFatal("Could not deinit app!");
		return true;
	}

	initialized = false;
	return false;
}

bool RunApp() {
	if(!OSIsMainCore()) {
		ProcUISubProcessMessages(true);
	} else {
		ProcUIStatus status = ProcUIProcessMessages(true);

		if(status == PROCUI_STATUS_EXITING) {
			DeInitApp();
			ProcUIShutdown();
			return true;
		} else if(status == PROCUI_STATUS_RELEASE_FOREGROUND) {
			DeInitApp();
			ProcUIDrawDoneRelease();
		} else if(status == PROCUI_STATUS_IN_FOREGROUND) {
			if (!initialized) InitApp();
			if (MainLoop()) return true;
		}
	}
	return false;
}

//TODO: Learn about this function
void SaveCallback() {
	OSSavesDone_ReadyToRelease();
}

int main(int argc, char **argv) {
	printf("Deal with it.");

	while(!RunApp());
	if (initialized) DeInitApp();
	return 0;
}
