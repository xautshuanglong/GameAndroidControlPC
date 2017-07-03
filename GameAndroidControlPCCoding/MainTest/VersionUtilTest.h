#pragma once

#include "Log.h"

namespace ShuangLong
{
	namespace Test
	{
		class VersionUtilTest sealed
		{
		private:
			VersionUtilTest();
			Log* mpLog;

		public:
			~VersionUtilTest();

			static VersionUtilTest *mpInstance;
			static void Entry();

			void GetFileVersionInfoTest();
		};
	}
}

