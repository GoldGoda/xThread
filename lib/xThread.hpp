#pragma once

#include "typeAliases.hpp"  // cstdint, vector, thread, queue, functional
#include <condition_variable>
#include <mutex>

namespace xThread
{

class ThreadPool
{

private:
    threadCount_t           mThreadCount  { 0 };
    threadList_t            mThreadList   { 0 };
    taskList_t              mTaskList     {   };
    bool                    mIsRunning    { true };
    std::mutex              mMutex        {   };
    std::condition_variable mCV           {   };

public:
    explicit ThreadPool(threadCount_t threadCount = std::thread::hardware_concurrency()) : 
        mThreadCount(threadCount), mThreadList(threadCount) {  }

    
    threadCount_t threadCount() const noexcept { return mThreadCount; }


    void addTask(task_t&& task) noexcept {
        {
            std::lock_guard<std::mutex> mutexGuard( mMutex );
            mTaskList.push( std::move(task) );
        }
        mCV.notify_one();
    }

    void run() noexcept
    {
        for (auto& thread : mThreadList)
        {
            thread = std::thread( [this](){
                while ( mIsRunning )
                {
                    executePendingTask();
                }
            } );
        }
            
        for (auto& thread : mThreadList) {
            if( thread.joinable() ){
                thread.join();
            }
        }
    }

    ~ThreadPool(){
        mIsRunning = false;
        mCV.notify_all();
    }

private:
    void executePendingTask() noexcept
    {
        std::unique_lock<std::mutex> mutexGuard( mMutex );
        mCV.wait(mutexGuard, [this] { return !mTaskList.empty(); });
        auto task = std::move(mTaskList.front());
        mTaskList.pop();
        mutexGuard.unlock();
        task();
    }
};


} // namespace xThread

