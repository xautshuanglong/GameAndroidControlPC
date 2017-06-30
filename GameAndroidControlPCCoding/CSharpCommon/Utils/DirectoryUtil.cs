using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpCommon.Utils
{
	public static class DirectoryUtil
	{
		public static string GetUserProfileDir()
		{
			return Environment.GetFolderPath(Environment.SpecialFolder.UserProfile);
		}
	}
}
