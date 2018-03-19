#include "WindowsInfoLookerTest.h"

namespace Shuanglong::Test
{

#define SHOW_MACRO_NAME(inputX, macroX)                                           \
do                                                                                \
{                                                                                 \
    if (inputX == macroX)                                                         \
    {                                                                             \
        printf_s("SHOW_MACRO_NAME [%5ld=0x%08X] %s\n", inputX, inputX, #macroX);  \
    }                                                                             \
} while (0);

    WindowsInfoLookerTest::WindowsInfoLookerTest()
    {}

    WindowsInfoLookerTest::~WindowsInfoLookerTest()
    {}

    WindowsInfoLookerTest* WindowsInfoLookerTest::GetInstance()
    {
        static WindowsInfoLookerTest instance;
        return &instance;
    }

    void WindowsInfoLookerTest::Entry()
    {
        std::cout << "----------------------------- WindowsInfoLooker Testing -----------------------------" << std::endl;
        mpLog = Log::GetInstance();

        GetSystemInfoTest();
    }

    void WindowsInfoLookerTest::Exit()
    {
        ;
    }

    void WindowsInfoLookerTest::GetSystemInfoTest()
    {
        SYSTEM_INFO si = { 0 };
        ::GetSystemInfo(&si);
        const DWORD dwCPUCnt = si.dwNumberOfProcessors;

        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_INTEL_386);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_INTEL_486);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_INTEL_PENTIUM);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_INTEL_IA64);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_AMD_X8664);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_MIPS_R4000);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_ALPHA_21064);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_PPC_601);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_PPC_603);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_PPC_604);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_PPC_620);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_HITACHI_SH3);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_HITACHI_SH3E);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_HITACHI_SH4);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_MOTOROLA_821);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_SHx_SH3);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_SHx_SH4);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_STRONGARM);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_ARM720);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_ARM820);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_ARM920);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_ARM_7TDMI);
        SHOW_MACRO_NAME(si.dwProcessorType, PROCESSOR_OPTIL);

        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_INTEL);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_MIPS);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_ALPHA);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_PPC);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_SHX);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_ARM);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_IA64);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_ALPHA64);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_MSIL);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_AMD64);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_IA32_ON_WIN64);
        SHOW_MACRO_NAME(si.wProcessorArchitecture, PROCESSOR_ARCHITECTURE_NEUTRAL);
    }
}
