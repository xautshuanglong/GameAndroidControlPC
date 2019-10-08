#pragma once

namespace Shuanglong
{
    namespace Utils
    {
        //************************************************************************\
        //    Author     : JiangChuanbiao
        //    Date       : 2019-10-8
        //    Description: 单例模式的模板实现，简化繁琐的编码。
        //************************************************************************/
        template <typename T>
        class SingletonUtil
        {
        public:
            SingletonUtil();
            ~SingletonUtil();
        };
    }
}
