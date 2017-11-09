#include <windows.h>

#include "DataUtil.h"

DataUtil* DataUtil::m_pInstance = NULL;
DataUtil::Helpper DataUtil::helpper;

DataUtil::DataUtil()
{
	m_timeCacheCount = 0;
	m_quternionCacheCount = 0;
	m_frameTimingCacheCount = 0;

	LARGE_INTEGER largeInt;
	QueryPerformanceFrequency(&largeInt);
	m_sysFrequency = largeInt.QuadPart;

	m_osFile.open(DEFAULT_FILENAME, std::ios::out);
}

DataUtil::~DataUtil()
{
	m_osFile.close();
}

DataUtil* DataUtil::GetInstance()
{
	return m_pInstance;
}

void DataUtil::WriteFile(char *pData)
{
	if (m_osFile.is_open())
	{
		m_osFile << pData << std::endl;
	}
}

void DataUtil::SetTime(TimeIndicator whichTime, long long time)
{
	switch (whichTime)
	{
	case TIME_INDICATOR_SEND:
		m_sendTime = time;
		break;
	case TIME_INDICATOR_RECV:
		m_recvTime = time;
		break;
	default:
		break;
	}
}

long long DataUtil::GetTime(TimeIndicator whichTime)
{
	long long retValue = 0;
	switch (whichTime)
	{
	case TIME_INDICATOR_SEND:
		retValue = m_sendTime;
		break;
	case TIME_INDICATOR_RECV:
		retValue = m_recvTime;
		break;
	default:
		break;
	}

	return retValue;
}

double DataUtil::GetPerformanceFrequency()
{
	return m_sysFrequency;
}

void DataUtil::RecordTimeDelay(long long sendTime, long long serTime, long long recvTime)
{
	if (m_timeCacheCount < DEFAULT_TIMEDELAY_LENGTH)
	{
		// 记录 客户端发送时间、服务端收到时间、客户端收到时间
		m_cacheTimeArr[m_timeCacheCount * TIME_DELAY_UNIT] = sendTime;
		m_cacheTimeArr[m_timeCacheCount * TIME_DELAY_UNIT + 1] = serTime;
		m_cacheTimeArr[m_timeCacheCount * TIME_DELAY_UNIT + 2] = recvTime;

		m_timeCacheCount++;
	}
	else if (m_timeCacheCount == DEFAULT_TIMEDELAY_LENGTH)
	{
		char timeStr[100];
		double frequency = DataUtil::GetInstance()->GetPerformanceFrequency();

		for (int i = 0; i < m_timeCacheCount; i++)
		{
			sprintf(timeStr, "%lf\t%lf\t%lf", m_cacheTimeArr[i*TIME_DELAY_UNIT] * 1000 / frequency, m_cacheTimeArr[i*TIME_DELAY_UNIT + 1] * 1000 / frequency, m_cacheTimeArr[i*TIME_DELAY_UNIT + 2] * 1000 / frequency);
			DataUtil::GetInstance()->WriteFile(timeStr);
		}
		m_timeCacheCount++;
	}
}

void DataUtil::RecordQuaternion(float w, float x, float y, float z)
{
	if (m_quternionCacheCount < DEFAULT_TIMEDELAY_LENGTH)
	{
		// 记录 四元数
		m_cacheQuternionArr[m_quternionCacheCount].w = w;
		m_cacheQuternionArr[m_quternionCacheCount].x = x;
		m_cacheQuternionArr[m_quternionCacheCount].y = y;
		m_cacheQuternionArr[m_quternionCacheCount].z = z;

		LARGE_INTEGER largerInt;
		QueryPerformanceCounter(&largerInt);
		double timeStamp = largerInt.QuadPart * 1000 / m_sysFrequency;
		m_cacheQuternionArr[m_quternionCacheCount].timeStamp = timeStamp;

		m_quternionCacheCount++;
	}
	else if (m_quternionCacheCount == DEFAULT_TIMEDELAY_LENGTH)
	{
		char timeStr[100];

		for (int i = 0; i < m_quternionCacheCount; i++)
		{
			sprintf(timeStr, "%.1f\t%f\t%f\t%f\t%f", m_cacheQuternionArr[i].timeStamp, m_cacheQuternionArr[i].w, m_cacheQuternionArr[i].x, m_cacheQuternionArr[i].y, m_cacheQuternionArr[i].z);
			DataUtil::GetInstance()->WriteFile(timeStr);
		}
		m_quternionCacheCount++;
	}
}

void DataUtil::RecordFrameTiming(vr::Compositor_FrameTiming frameTiming)
{
	if (m_frameTimingCacheCount < DEFAULT_FRAMETIMING_COUNT)
	{
		// 记录 帧计时
		m_frameTimingArr[m_frameTimingCacheCount] = frameTiming;

		//LARGE_INTEGER largerInt;
		//QueryPerformanceCounter(&largerInt);
		//double timeStamp = largerInt.QuadPart * 1000 / m_sysFrequency;
		//m_cacheQuternionArr[m_quternionCacheCount].timeStamp = timeStamp;

		m_frameTimingCacheCount++;
	}
	else if (m_frameTimingCacheCount == DEFAULT_FRAMETIMING_COUNT)
	{
		char frameTimingStr[256];

		for (int i = 0; i < m_frameTimingCacheCount; i++)
		{
			sprintf(frameTimingStr, "%d\t%d\t%d\t%d\t%d\t%d\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f",
				m_frameTimingArr[i].m_nSize,
				m_frameTimingArr[i].m_nFrameIndex,
				m_frameTimingArr[i].m_nNumFramePresents,
				m_frameTimingArr[i].m_nNumMisPresented,
				m_frameTimingArr[i].m_nNumDroppedFrames,
				m_frameTimingArr[i].m_nReprojectionFlags,
				m_frameTimingArr[i].m_flSystemTimeInSeconds,
				m_frameTimingArr[i].m_flPreSubmitGpuMs,
				m_frameTimingArr[i].m_flPostSubmitGpuMs,
				m_frameTimingArr[i].m_flTotalRenderGpuMs,
				m_frameTimingArr[i].m_flCompositorRenderGpuMs,
				m_frameTimingArr[i].m_flCompositorRenderCpuMs,
				m_frameTimingArr[i].m_flCompositorIdleCpuMs,
				m_frameTimingArr[i].m_flClientFrameIntervalMs,
				m_frameTimingArr[i].m_flPresentCallCpuMs,
				m_frameTimingArr[i].m_flWaitForPresentCpuMs,
				m_frameTimingArr[i].m_flSubmitFrameMs,
				m_frameTimingArr[i].m_flWaitGetPosesCalledMs,
				m_frameTimingArr[i].m_flNewPosesReadyMs,
				m_frameTimingArr[i].m_flNewFrameReadyMs,
				m_frameTimingArr[i].m_flCompositorUpdateStartMs,
				m_frameTimingArr[i].m_flCompositorUpdateEndMs,
				m_frameTimingArr[i].m_flCompositorRenderStartMs
			);
			DataUtil::GetInstance()->WriteFile(frameTimingStr);
		}
		m_frameTimingCacheCount++;
	}
}
