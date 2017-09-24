#pragma once

namespace Shuanglong::Test
{
    class TinyXml2Test
    {
    private:
        TinyXml2Test();
        static TinyXml2Test* GetInstance();

    public:
        ~TinyXml2Test();
        void XmlParseTest();
        static void Entry();
        static void Exit();
    };
}
