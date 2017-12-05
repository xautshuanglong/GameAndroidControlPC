#include "stdafx.h"
#include "JsonTest.h"

#include <Json/json.h>
#include <Utils/StringUtil.h>

namespace Shuanglong::Test
{
    JsonTest::JsonTest()
    {
    }

    JsonTest::~JsonTest()
    {
    }

    JsonTest* JsonTest::GetInstance()
    {
        static JsonTest instance;
        return &instance;
    }

    void JsonTest::Entry()
    {
        std::cout << "---------------------------------- JsonTest ----------------------------------" << std::endl;
        GetInstance()->ReaderTest();
        GetInstance()->WriterTest();
    }

    void JsonTest::Exit()
    {
        ;
    }

    void JsonTest::ReaderTest()
    {
        // CharReader testing
        Json::CharReaderBuilder readerBuilder;
        Json::CharReader *pReader(readerBuilder.newCharReader());
        Json::Value root;
        JSONCPP_STRING errStr;

        char const testStr[] =
            "{ \"property\" : [\"value\", \"value2\"], \"obj\" : "
            "{ \"nested\" : 123, \"bool\" : true}, \"null\" : "
            "null, \"false\" : false }";

        bool ok = pReader->parse(testStr, testStr + std::strlen(testStr), &root, &errStr);
        printf_s("root[\"property\"].isArray() --> %s\n",
                 Utils::StringUtil::BoolToString(root["property"].isArray()).c_str());
        printf_s("root[\"property\"][0] --> %s\n", root["property"][0].asString().c_str());
        printf_s("root[\"property\"][1] --> %s\n", root["property"][1].asString().c_str());

        // Reader testing have been deprecated
        //Json::Reader reader;
        //Json::Value root;
        //bool ok = reader.parse("{ \"property\" : [\"value\", \"value2\"], \"obj\" : "
        //                       "{ \"nested\" : 123, \"bool\" : true}, \"null\" : "
        //                       "null, \"false\" : false }",
        //                       root);

        //if (ok)
        //{
        //    bool noError = reader.getFormattedErrorMessages().size() == 0;
        //    printf_s("root[\"property\"].getOffsetStart()=%lld\n", root["property"].getOffsetStart());
        //    printf_s("root[\"property\"][0] --> %s\n", root["property"][0].asString().c_str());
        //    printf_s("root[\"property\"][1] --> %s\n", root["property"][1].asString().c_str());
        //}

    }

    void JsonTest::WriterTest()
    {
        // FastWriter has been deprecated
        //Json::FastWriter fastWriter;
        //Json::Value root;
        //JSONCPP_STRING fastString = fastWriter.write(root);
        //std::cout << fastString << std::endl;

        Json::StreamWriterBuilder b;
        Json::Value nullValue;
        b.settings_["dropNullPlaceholders"] = false;
        std::cout << Json::writeString(b, nullValue) << std::endl;

        b.settings_["dropNullPlaceholders"] = true;
        std::cout << Json::writeString(b, nullValue) << std::endl;

        JSONCPP_STRING binary("hi", 3);
        {
            Json::Value root;
            root = binary;
            std::cout << "root.asString() = " << root.asString();
            JSONCPP_STRING out = Json::writeString(b, root);
            std::cout << "write out string --> " << out << std::endl;
        }
        {
            Json::Value root;
            root["top"] = binary;
            std::cout << "root[\"top\"].asString() = " << root["top"].asString() << std::endl;
            JSONCPP_STRING out = Json::writeString(b, root["top"]);
            std::cout << "write out top string --> " << out << std::endl;
        }

        // Writer testing
        //JSONCPP_STRING rootString("root", 4);
        //JSONCPP_STRING topString("topString", 9);
        //Json::Value rootElement;
        //rootElement["top"] = topString;
        ////rootElement["top"] = "topValue";
        ////rootElement["top"]["second"] = "secondValue";
        //Json::StreamWriterBuilder writerBuilder;
        //Json::StreamWriter *pWriter = writerBuilder.newStreamWriter();

        //JSONCPP_STRING stdString = Json::writeString(writerBuilder, rootElement);
        //
        //std::ofstream ofStream("test.json", std::ios::out | std::ios::binary);
        //pWriter->write(rootElement, &ofStream);
        //std::cout << stdString << std::endl;

        /* Testing for dlo
        Json::Value rootElement;

        // HMD
        Json::Value hmdDriverFromHead;
        hmdDriverFromHead[0] = 0.000000;
        hmdDriverFromHead[1] = -0.150000;
        hmdDriverFromHead[2] = -0.050000;
        Json::Value hmdNeckFromHead;
        hmdNeckFromHead[0] = 0.000000;
        hmdNeckFromHead[1] = 0.130000;
        hmdNeckFromHead[2] = -0.050000;
        Json::Value hmdEle;
        hmdEle["use_controller_flag"] = true;
        hmdEle["interpupillary_distance"] = 0.062000;
        hmdEle["driver_from_head"] = hmdDriverFromHead;
        hmdEle["neck_from_head"] = hmdNeckFromHead;

        // Controller
        Json::Value controllerDriverFromHead;
        controllerDriverFromHead[0] = 0.000000;
        controllerDriverFromHead[1] = 0.007000;
        controllerDriverFromHead[2] = -0.073000;

        Json::Value controllerEle;
        controllerEle["driver_from_head"] = controllerDriverFromHead;

        rootElement["hmd"] = hmdEle;
        rootElement["controller"] = controllerEle;

        //rootElement["top"] = "topValue";
        //rootElement["top"]["second"] = "secondValue";
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder.settings_["commentStyle"] = "None";
        writerBuilder.settings_["precision"] = 6;
        Json::StreamWriter *pWriter = writerBuilder.newStreamWriter();

        JSONCPP_STRING stdString = Json::writeString(writerBuilder, rootElement);

        std::ofstream ofStream("test.json", std::ios::out | std::ios::binary);
        pWriter->write(rootElement, &ofStream);
        std::cout << stdString << std::endl;
        */
    }
}
