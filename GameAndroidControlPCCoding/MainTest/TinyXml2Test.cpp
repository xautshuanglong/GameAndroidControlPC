#include "stdafx.h"
#include "TinyXml2Test.h"

#include <TinyXML2/TinyXML2.h>

namespace Shuanglong::Test
{
    TinyXml2Test::TinyXml2Test()
    {
    }

    TinyXml2Test::~TinyXml2Test()
    {
    }

    TinyXml2Test* TinyXml2Test::GetInstance()
    {
        static TinyXml2Test instance;
        return &instance;
    }

    void TinyXml2Test::Entry()
    {
        std::cout << "---------------------------------- TinyXml2Test ----------------------------------" << std::endl;
        //GetInstance()->XmlParseTest();
    }

    void TinyXml2Test::Exit()
    {
        ;
    }

    void TinyXml2Test::XmlParseTest()
    {
        static const char* test[] =
        { 
            "<element />",
            "<element></element>",
            "<element><subelement/></element>",
            "<element><subelement></subelement></element>",
            "<element><subelement><subsub/></subelement></element>",
            "<!--comment beside elements--><element><subelement></subelement></element>",
            "<!--comment beside elements, this time with spaces-->  \n <element>  <subelement> \n </subelement> </element>",
            "<element attrib1='foo' attrib2=\"bar\" ></element>",
            "<element attrib1='foo' attrib2=\"bar\" ><subelement attrib3='yeehaa' /></element>",
            "<element>Text inside element.</element>",
            "<element><b></b></element>",
            "<element>Text inside and <b>bolded</b> in the element.</element>",
            "<outer><element>Text inside and <b>bolded</b> in the element.</element></outer>",
            "<element>This &amp; That.</element>",
            "<element attrib='This&lt;That' />",
            0
        };

        for (int i = 0; test[i]; ++i)
        {
            TinyXML2::XMLDocument doc;
            doc.Parse(test[i]);
            if (!doc.Error())
            {
                doc.Print();
                printf("----------------------------------------------\n");
            }
        }
    }
}
