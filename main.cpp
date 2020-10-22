#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>


using namespace std;

BOOL writeMemory(uintptr_t const address, vector<uint8_t> const& bytes) {
	return WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), nullptr);
}

DWORD base = (DWORD)GetModuleHandleA("GameAssembly.dll");

DWORD WINAPI main(LPVOID lpParam) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	SetConsoleTitleA("No kill cooldown by 3rA");
	if (writeMemory(base + 0x88C47A, { 0x31, 0xC0, 0x89, 0x46, 0x44 }))
		cout << "Cheat injected!" << endl;
	FreeConsole();
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	if (reason == DLL_PROCESS_ATTACH) 
		CreateThread(0, 4096, &main, 0, 0, NULL);
	return TRUE;
}