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
        //this->MessageTestProto2Test();
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
    }
}
