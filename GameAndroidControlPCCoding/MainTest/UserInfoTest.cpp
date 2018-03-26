#include "UserInfoTest.h"

#include "Log.h"
#include "UserInfo.pb.h"

using namespace Shuanglong::ProtoBufMsg;

namespace Shuanglong::Test
{
    UserInfoTest::UserInfoTest()
    {}

    UserInfoTest::~UserInfoTest()
    {}

    UserInfoTest* UserInfoTest::GetInstance()
    {
        static UserInfoTest instance;
        return &instance;
    }

    void UserInfoTest::Entry()
    {
        this->MessageTestProto2Test();
    }

    void UserInfoTest::Exit()
    {
        ;
    }

    void UserInfoTest::MessageTestProto2Test()
    {
        UserInfo userInfo;

        userInfo.set_id(110);
        userInfo.set_name("police");
        userInfo.set_sex(false);
        
        Log::GetInstance()->Console(SL_CODE_LOCATION,"UserInfo: %s", userInfo.SerializeAsString().c_str());

        std::string tempString = userInfo.SerializeAsString();

        UserInfo newUserInfo;
        newUserInfo.ParseFromString(tempString);

        //unsigned int n = 0;
        //do 
        //{
        //    int x = static_cast<int>((n >> 1) ^ ~(n & 1) + 1);
        //    printf_s("n:%d  --> %d\n", n, x);
        //    ++n;
        //} while (n <= 6);

        //int n2 = 1;
        //do
        //{
        //    int x2 = (static_cast<unsigned int>(-n2) << 1) ^ static_cast<unsigned int>(-n2 >> 31);
        //    int x3 = (static_cast<unsigned int>(n2) << 1) ^ static_cast<unsigned int>(n2 >> 31);
        //    printf_s("n2:%d  --> %d\nn2:%d  --> %d\n", -n2, x2, n2, x3);
        //    ++n2;
        //} while (n2 <= 6);
    }
}
