// ShuanglongService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SimpleService.h"
#include "CheckerService.h"

using namespace Shuanglong::Service;

#define SERVICE_NAME_SIMPLE             TEXT("ShuanglongChecker")
#define SERVICE_DISPLAY_NAME_SIMPLE     TEXT("Shuanglong PC Check Service")
#define SERVICE_START_TYPE              SERVICE_DEMAND_START
#define SERVICE_DEPENDENCIES            TEXT("")
#define SERVICE_ACCOUNT                 TEXT("NT AUTHORITY\\LocalService")
#define SERVICE_PASSWORD                NULL

#define SERVICE_NAME_SHADOW             TEXT("ShuanglongListener")
#define SERVICE_DISPLAY_NAME_SHADOW     TEXT("Shuanglong TCP/IP Listen Service")

int main(int argc, char **argv)
{
    SimpleService service(
        SERVICE_NAME_SIMPLE,
        SERVICE_DISPLAY_NAME_SIMPLE,
        SERVICE_START_TYPE,
        SERVICE_DEPENDENCIES,
        SERVICE_ACCOUNT,
        SERVICE_PASSWORD,
        TRUE, TRUE, TRUE);
    CheckerService serviceShadow(
        SERVICE_NAME_SHADOW,
        SERVICE_DISPLAY_NAME_SHADOW,
        SERVICE_START_TYPE,
        SERVICE_DEPENDENCIES,
        SERVICE_ACCOUNT,
        SERVICE_PASSWORD,
        TRUE, TRUE, TRUE);

    ServiceList services;
    services.push_back(&service);
    services.push_back(&serviceShadow);

    if ((argc > 1) && ((*argv[1] == '-' || (*argv[1] == '/'))))
    {
        if (_stricmp("install", argv[1] + 1) == 0)
        {
            // "-install" or "/install"
            ServiceBase::Install(services);
        }
        else if (_stricmp("remove", argv[1] + 1) == 0)
        {
            // "-remove" or "/remove"
            ServiceBase::Uninstall(services);
        }
    }
    else
    {
        printf_s("Parameters:\n");
        printf_s(" -install  to install the service.\n");
        printf_s(" -remove   to remove the service.\n");

        if (!ServiceBase::Run(services))
        {
            printf_s("Service failed to run w/err 0x%08lx\n", GetLastError());
        }
    }
    return 0;
}
