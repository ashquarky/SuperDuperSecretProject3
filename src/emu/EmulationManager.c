/*	SuperDuperSecretProject3
	gaaaah
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <znes/cpu.h>
#include <znes/rom.h>
#include <znes/mem.h>
#include <znes/ppu.h>

extern unsigned char* znes_mem;
unsigned char* rom;

//Must load ROM FIRST
bool romloaded = false;
bool emumanagerinitialized = false;
bool EmulationManagerInit() {
	if (emumanagerinitialized) {
		return false;
	}
	if (!romloaded) {
		emumanagerinitialized = false;
		return true;
	}
	init_mem();
	init_cpu();
	init_ppu();
	emumanagerinitialized = true;
	return false;
}

bool EmulationManagerDeInit() {
	if (!emumanagerinitialized) {
		return false;
	}
	if (romloaded) {
		//unload ROM?
		romloaded = false;
	}
	if (znes_mem) {
		free(znes_mem);
	}
	emumanagerinitialized = false;
	return false;
}

bool EmulationManagerLoadROM(char* path) {
	FILE* romFile = fopen(path, "r");
	if (!romFile) {
		return true;
	}

	fseek(romFile, 0L, SEEK_END);
	unsigned int romSize = ftell(romFile);
	fseek(romFile, 0L, SEEK_SET);

	rom = malloc(romSize);
	fread((void*)rom, romSize, 1, romFile);

	init_rom(rom);
	//I hate how much of this is on trust
	romloaded = true;
	return false;
}

void EmulationManagerRunFrame() {

}
