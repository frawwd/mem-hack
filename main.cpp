#include <Windows.h>
#include <iostream>
#include <TLHelp32.h>

#include "proc.h"



DWORD pID, baseModule;
DWORD localPlayerPtr; // 0x17E0A8
DWORD entityListPtr; // 0x18AC04
DWORD fovPtr; // 0x18A7CC
DWORD playerCountPtr; // 0x18AC0C

HANDLE handle;

int heath = 999;
int ammo = 420;
int fov = 140;

bool infammo = true;
bool infHealth = true;
bool readPlayerCount = false;

int main() {
	pID = GetProcessID(L"ac_client.exe"); // Gets the Process Id
	baseModule = GetModuleBaseAddress(pID, L"ac_client.exe"); // Gets base module
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID); // Opens Handle
	ReadProcessMemory(handle, (LPCVOID)(baseModule + 0x17E0A8), &localPlayerPtr, sizeof(localPlayerPtr), nullptr); 
	// writes from the memory address of the games player pointer and then writes it to the localplayerpointer var

	while (true) {
		if (infammo) {
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x140), &ammo, sizeof(ammo), nullptr);  // Assault Rifle ammo
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x138), &ammo, sizeof(ammo), nullptr);  // Submachine Gun ammo
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x13C), &ammo, sizeof(ammo), nullptr);  // Sniper ammo
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x134), &ammo, sizeof(ammo), nullptr);  // Shotgun ammo
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x12C), &ammo, sizeof(ammo), nullptr);  // Pistol ammo
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0x144), &ammo, sizeof(ammo), nullptr);  // Grenade ammo
		}
		if (infHealth) {
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0xEC), &heath, sizeof(heath), nullptr); // Health
			WriteProcessMemory(handle, (LPVOID)(localPlayerPtr + 0xF0), &heath, sizeof(heath), nullptr); // Aurmor
		}
		if (readPlayerCount) {
			ReadProcessMemory(handle, (LPCVOID)(baseModule + 0x18AC0C), &playerCountPtr, sizeof(playerCountPtr), nullptr);
			std::cout << playerCountPtr << std::endl;
		}
	}
}


