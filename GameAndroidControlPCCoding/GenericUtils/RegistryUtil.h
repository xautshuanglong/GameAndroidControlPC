#pragma once
#include "CommonDefines.h"

namespace ShuangLong
{
	namespace Utils
	{
		class EXPORT_API RegistryUtil sealed
		{
		public:
			RegistryUtil() = delete;
			RegistryUtil(const RegistryUtil& originalObj) = delete;
			RegistryUtil(RegistryUtil&& originalObj) = delete;
		};
	}
}
