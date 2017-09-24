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
        GetInstance()->ReaderTest();
    }

    void JsonTest::Exit()
    {
        ;
    }

    void JsonTest::ReaderTest()
    {
        Json::CharReaderBuilder readerBuilder;
        Json::CharReader* pReader(readerBuilder.newCharReader());
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

        /*
        Json::Reader reader;
        Json::Value root;
        bool ok = reader.parse("{ \"property\" : [\"value\", \"value2\"], \"obj\" : "
                               "{ \"nested\" : 123, \"bool\" : true}, \"null\" : "
                               "null, \"false\" : false }",
                               root);

        if (ok)
        {
            bool noError = reader.getFormattedErrorMessages().size() == 0;
            printf_s("root[\"property\"].getOffsetStart()=%lld\n", root["property"].getOffsetStart());
            printf_s("root[\"property\"][0] --> %s\n", root["property"][0].asString().c_str());
            printf_s("root[\"property\"][1] --> %s\n", root["property"][1].asString().c_str());
        }
        */
    }
}
