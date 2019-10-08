#pragma once

#include <iostream>
#include <mutex>
#include <atomic>

namespace Shuanglong
{
    namespace Utils
    {
        //************************************************************************\
                //    Author     : JiangChuanbiao
//    Date       : 2019-10-8
//    Description: 单例模式的模板实现，简化繁琐的编码。
//************************************************************************/
        template <typename T>
        class SingletonUtil
        {
        private:
            static std::mutex      mInstanceMutex;
            static std::atomic<T*> mpInstance;

            class DestructHellpper
            {
            public:
                DestructHellpper()
                {
                    std::cout << "DestructHellpper::DestructHellpper()" << std::endl;
                }

                ~DestructHellpper()
                {
                    std::cout << "DestructHellpper::~DestructHellpper()" << std::endl;

                    //T *pInstance = mpInstance.load(std::memory_order_acquire);
                    //if (pInstance != nullptr && mpInstance.compare_exchange_strong(pInstance, nullptr))
                    //{
                    //    std::cout << "atomic compare successfully ..." std::endl;
                    //    //delete pInstance;
                    //    //pInstance = nullptr;
                    //    //mpInstance.store(pInstance, std::memory_order_release);
                    //}
                    //else
                    //{
                    //    std::cout << "atomic compare failed ..." std::endl;
                    //}
                }
            };
            static DestructHellpper mDestructHellper;

        public:
            virtual ~SingletonUtil()
            {
                std::cout << "SingletonUtil()::~SingletonUtil()" << std::endl;
            }

            static T* GetInstance()
            {
                T *pInstance = mpInstance.load(std::memory_order_acquire);
                if (pInstance == nullptr)
                {
                    std::lock_guard<std::mutex> lock(mInstanceMutex);
                    pInstance = mpInstance.load(std::memory_order_relaxed);
                    if (pInstance == nullptr)
                    {
                        pInstance = new T();
                        mpInstance.store(pInstance, std::memory_order_release);
                    }
                }

                return pInstance;
            }

        protected:
            SingletonUtil()
            {
                std::cout << "SingletonUtil()::SingletonUtil()" << std::endl;
            }

            SingletonUtil(const SingletonUtil& otherObj)
            {
                std::cout << "SingletonUtil()::SingletonUtil(const SingletonUtil& otherObj)" << std::endl;
            }

            SingletonUtil& operator = (const SingletonUtil& othrerObj)
            {
                std::cout << "SingletonUtil()::operator= return reference" << std::endl;
            }
        };

        template<typename T>
        std::atomic<T*> SingletonUtil<T>::mpInstance = nullptr;
        template<typename T>
        std::mutex      SingletonUtil<T>::mInstanceMutex;
        template<typename T>
        typename SingletonUtil<T>::DestructHellpper SingletonUtil<T>::mDestructHellper;
    }
}
