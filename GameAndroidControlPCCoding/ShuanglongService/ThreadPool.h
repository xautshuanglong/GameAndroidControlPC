#pragma once

#include "stdafx.h"

class ThreadPool
{
public:
    template <typename T>
    static void QueueUserWorkItem(void (T::*function)(void),
                                  T *object, ULONG flags = WT_EXECUTELONGFUNCTION)
    {
        typedef std::pair<void (T::*)(), T *> CallbackType;
        std::unique_ptr<CallbackType> p(new CallbackType(function, object));

        if (::QueueUserWorkItem(ThreadProc<T>, p.get(), flags))
        {
            // The ThreadProc now has the responsibility of deleting the pair.
            p.release();
        }
        else
        {
            throw GetLastError();
        }
    }

private:
    template <typename T>
    static DWORD WINAPI ThreadProc(PVOID context)
    {
        typedef std::pair<void (T::*)(), T *> CallbackType;

        std::unique_ptr<CallbackType> p(static_cast<CallbackType *>(context));

        (p->second->*p->first)();
        return 0;
    }
};