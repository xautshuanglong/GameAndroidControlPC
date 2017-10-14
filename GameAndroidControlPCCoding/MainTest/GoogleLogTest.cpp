#include "stdafx.h"
#include "GoogleLogTest.h"

#include <glog/logging.h>

namespace Shuanglong::Test
{
    GoogleLogTest::GoogleLogTest()
    {
    }

    GoogleLogTest::~GoogleLogTest()
    {
    }

    GoogleLogTest* GoogleLogTest::GetInstance()
    {
        static GoogleLogTest instance;
        return &instance;
    }

    void GoogleLogTest::Entry(const char* moduleName)
    {
        GetInstance()->Initialize(moduleName);
        //GetInstance()->ShowLogMessage();
    }

    void GoogleLogTest::Exit()
    {
        GetInstance()->Uninitialize();
    }

    void GoogleLogTest::Initialize(const char* moduleName)
    {
        FLAGS_log_dir = "E:\\ShuanglongLogs";
        FLAGS_colorlogtostderr = true;
        FLAGS_stop_logging_if_full_disk = true;
        FLAGS_max_log_size = 1024 * 1024;
        FLAGS_logbufsecs = 5;
        FLAGS_minloglevel = google::GLOG_INFO;
        FLAGS_stderrthreshold = google::GLOG_INFO;
        google::InitGoogleLogging(moduleName);
        //google::SetLogDestination(google::GLOG_INFO, "E:\\ShuanglongLogs\\MainTest_Glog.");
        google::SetLogFilenameExtension("txt");
    }

    void GoogleLogTest::Uninitialize()
    {
        google::ShutdownGoogleLogging();
    }

    void GoogleLogTest::ShowLogMessage()
    {
        LOG(INFO) << "Glog Info test";
        LOG(WARNING) << "Glog Warning test";
        LOG(ERROR) << "Glog Error test";
    }
}
