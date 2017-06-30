using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using CSharpCommon.Utils;

namespace CSharpUnitTest.TestUtils
{
	[TestClass]
	public class DirectoryUtilTest
	{
		[TestMethod]
		public void GetUserProfileDir()
		{
			string userProfile = DirectoryUtil.GetUserProfileDir();
		}
	}
}
