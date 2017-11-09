#pragma once
#include <fstream>

// OpenGL SteamVR 游戏 Demo
#include <openvr.h>

#define DEFAULT_FILENAME "D:\\OpenGL_DebugData.txt"
#define DEFAULT_TIMEDELAY_LENGTH 10000
#define DEFAULT_FRAMETIMING_COUNT 10000
#define TIME_DELAY_UNIT 3

struct TempRotationInfo 
{
	float x;
	float y;
	float z;
	float w;
	double timeStamp;
};

enum TimeIndicator
{
	TIME_INDICATOR_SEND,// 协议发送时间
	TIME_INDICATOR_RECV // 协议接收时间
};

class DataUtil
{
public:
	static DataUtil* GetInstance();
	void WriteFile(char *pData);
	void SetTime(TimeIndicator whichTime, long long time);
	long long GetTime(TimeIndicator whichTime);
	double GetPerformanceFrequency();
	void RecordTimeDelay(long long sendTime, long long serTime, long long recvTime);
	void RecordQuaternion(float w, float x, float y, float z);
	void RecordFrameTiming(vr::Compositor_FrameTiming frameTiming);

private:
	DataUtil();
	~DataUtil();
	static DataUtil* m_pInstance;

	std::ofstream m_osFile;
	double m_sysFrequency;

	// 记录时间戳
	int m_timeCacheCount;
	long long m_sendTime, m_recvTime;
	long long m_cacheTimeArr[DEFAULT_TIMEDELAY_LENGTH * TIME_DELAY_UNIT];

	// 记录四元数
	int m_quternionCacheCount;
	TempRotationInfo m_cacheQuternionArr[DEFAULT_TIMEDELAY_LENGTH];

	// 记录帧计时
	int m_frameTimingCacheCount;
	vr::Compositor_FrameTiming m_frameTimingArr[DEFAULT_FRAMETIMING_COUNT];

	class Helpper
	{
	public:
		Helpper()
		{
			m_pInstance = new DataUtil();
		}
		~Helpper()
		{
			if (m_pInstance != NULL)
			{
				delete m_pInstance;
			}
		}
	};
	static Helpper helpper;
};
