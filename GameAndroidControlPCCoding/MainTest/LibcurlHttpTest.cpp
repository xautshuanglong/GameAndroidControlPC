#include "LibcurlHttpTest.h"

#include <curl/curl.h>

namespace Shuanglong::Test
{
    LibcurlHttpTest::LibcurlHttpTest()
    {}

    LibcurlHttpTest::~LibcurlHttpTest()
    {}

    LibcurlHttpTest* LibcurlHttpTest::GetInstance()
    {
        static LibcurlHttpTest instance;
        return &instance;
    }

    void LibcurlHttpTest::Entry()
    {
        std::cout << "----------------------------- Libcurl Http Testing -----------------------------" << std::endl;
        mpLog = Log::GetInstance();

        //CurlHttpGetTest();
    }

    void LibcurlHttpTest::Exit()
    {
        ;
    }

    void LibcurlHttpTest::CurlHttpGetTest()
    {
        CURL *curl;
        CURLcode res;
        FILE *fp;
        bool openSuccess = true;
        if ((fopen_s(&fp, "./CurlHttpGetTest.html", "w")) != 0)  // 返回结果用文件存储
        {
            openSuccess = false;
            fp = stdout;
        }

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: Agent-007");
        curl = curl_easy_init();
        if (curl)
        {
            //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp);
            res = curl_easy_perform(curl);   // 执行
            if (res != 0)
            {
                curl_slist_free_all(headers);
                curl_easy_cleanup(curl);
            }
        }
        if (openSuccess)
        {
            fclose(fp);
        }
    }
}
