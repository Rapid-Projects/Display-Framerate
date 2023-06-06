#include <Windows.h>
#include <thread>

static __int64 rebase(__int64 address, __int64 base = 0x1E9DE1A0000)
{
	return (address - base + reinterpret_cast<__int64>(GetModuleHandle(0)));
}

static auto print = reinterpret_cast<void(__cdecl*)(__int64, const char*, ...)>(rebase(0x1E9DF15D8A0));
static auto get_task_scheduler = reinterpret_cast<__int64(__cdecl*)()>(rebase(0x1E9DEA3EA40));

void initialize()
{
	__int64 task_scheduler = get_task_scheduler();

	double framerate = 1 / *reinterpret_cast<double*>(task_scheduler + 0x158);
	print(0, "%f", framerate);
}

__int64 APIENTRY DllMain(HMODULE module, uint32_t reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		std::thread(initialize).detach();
	}
	return 1;
}
