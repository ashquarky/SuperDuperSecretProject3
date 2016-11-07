/*	SuperDuperSecretProject3
	gaaaah
*/

#ifndef _EMULATIONMANAGER_H_
#define _EMULATIONMANAGER_H_

#define CPU_CYCLES_PER_FRAME 1000

bool EmulationManagerInit();
bool EmulationManagerDeInit();
bool EmulationManagerLoadROM(char* path);
void EmulationManagerRunFrame();

#endif //_EMULATIONMANAGER_H_
