#pragma once

#include <string>
#include <exception>

namespace ShuangLong
{
    namespace Socket
    {
        class SocketException : public std::exception
        {
        private:
            std::string           mExcptionMsg;

        public:
            SocketException();
            ~SocketException();

        private:
            void FormatExceptionMsg();
        };
    }
}

