#pragma once

#include <cstdint>
#include <functional>
#include <thread>
#include <queue>


namespace xThread
{
    
using task_t        = std::function<void()>;
using threadCount_t = std::size_t;
using threadList_t  = std::vector<std::thread>;
using taskList_t    = std::queue<task_t>;

} // namespace xThread