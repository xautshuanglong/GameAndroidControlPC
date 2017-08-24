#pragma once

#include "stdafx.h"

namespace Shuanglong::Utils
{
    class AbstractAlgorithm
    {
    public:
        AbstractAlgorithm() {};
        virtual ~AbstractAlgorithm() {};

        virtual std::string Compute(std::string inString) = 0;
        virtual std::string Compute(const char* inBuffer, int inLength) = 0;
        virtual void Compute(const char* inBuffer, int inLength, const char* outBuffer, int outLength) = 0;
    };
}

