#include "setmgr/SettingsManager.h"

#include "Language.h"
#include "Globals.h"

#include "KMbox/KmboxB.h"
#include "KMbox/KmBoxNetManager.h"
#include "KMbox/kmboxNetPlusManager.cpp"

#ifndef NTSTATUS
typedef long NTSTATUS;
#endif

#include "CheatsThread.h"

#include <iostream>
#include <filesystem>
#include <windows.h>

#include "utils/XorStr.h"
#include "utils/JunkCode.h"

#pragma comment(lib, "D3DX11.lib")

namespace fs = std::filesystem;

std::string readFile(const std::string& path) {
	std::ifstream file(path);
	if (!file) return "";
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}


void main(HMODULE module) {
	// Inject junk code to alter binary layout
	JunkEngine::RunAllJunk();

	std::cout << XS(" -- Initialized -- ") << std::endl << std::endl;

	std::cout << XS("[*] Starting...") << std::endl;
	settingsJson.LoadSettings();
	std::cout << XS("[*] Settings parsed") << std::endl;
	{
		const auto& type = settingsJson.type;
		if (type == XS("net")) {
			if (KmBoxMgr.InitDevice(settingsJson.ip, settingsJson.port, settingsJson.uuid) != 0)
			{
				std::cout << XS("[*] Error! KmBoxNet Initialize failed.") << std::endl;
				return;
			}
			KmBox::type = XS("net");
			std::cout << XS("[*] Net connected!") << std::endl;
		}
		else if (type == XS("net+")) {
			if (kmboxnew::kmNet_init(const_cast<char*>(settingsJson.ip.c_str()), (char*)settingsJson.port, const_cast<char*>(settingsJson.uuid.c_str()))) {
				std::cout << XS("[*] Error! KmBoxNet-2 Initialize failed.") << std::endl;
				return;
			}
			KmBox::type = XS("net2");
			std::cout << XS("[*] Net+ connected!") << std::endl;
		}
		else if (type == XS("b")) {
			if (kmBoxBMgr.init() != 0) {
				std::cout << XS("[*] Error! KmBoxB Initialize failed.") << std::endl;
				return;
			}
			std::cout << XS("[*] BPro connected!") << std::endl;

			KmBox::type = XS("b");
		}
		else {
			KmBox::type = XS("None");
		}
	}

	// Scatter junk code between functional blocks
	JunkEngine::ScatterJunk1();

	auto ProcessStatus = ProcessMgr.Attach(XS("cs2.exe").c_str());

	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << XS("[*] Error! Failed to attach process, StatusCode:") << ProcessStatus << std::endl;
		return;
	}

	std::cout << XS("[*] Attached to game process") << std::endl;

	std::string offsets = readFile(XS("offsets.json"));

	std::cout << XS("[*] Loaded offsets") << std::endl;

	std::string client = readFile(XS("client_dll.json"));

	std::cout << XS("[*] Loaded client data") << std::endl;

	Offset::UpdateOffsets(offsets, client);

	std::cout << XS("[*] Updated offsets") << std::endl;

	// More junk code
	JunkEngine::ScatterJunk2();

	ProcessMgr.init_keystates();

	if (!gGame.InitAddress())
	{
		std::cout << XS("[*] Error! Failed to call InitAddress().") << std::endl;
		return;
	}

	if (!fs::directory_entry(MenuConfig::path).exists()) {
		fs::create_directory(MenuConfig::path);
		std::cout << XS("[*] Created config folder") << std::endl;
	}

	std::cout << XS("[*] Starting threads...") << std::endl;

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateMatrix), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(LoadLocalEntity), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(LoadEntity), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateEntityListEntry), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(ScatterReadThreads), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(UpdateWeaponNameThreads), NULL, 0, 0);

	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(KeysCheckThread), NULL, 0, 0);

	if (settingsJson.language == XS("en")) lang.english();
	else if (settingsJson.language == XS("ch")) lang.chineese();
	else lang.english();

	SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);

	// Final junk code block
	JunkEngine::ScatterJunk3();

	std::cout << XS("[*] Ready $") << std::endl;

	Gui.NewWindow(XS("Overlay"), Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), Cheats::Run);
}