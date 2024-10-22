#include "ExecutorImpl.hpp"

#include <new>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose), isFast(false) {}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    /*
        std::nothrow 是 C++ 标准库中的一个常量，用于指示在分配内存时不抛出任何异常
        它是 std::nothrow_t 类型的实例，通常用在 new 运算符和 std::nothrow 命名空间中，
        以请求内存分配器在分配失败时返回一个空指针，而不是抛出 std::bad_alloc 异常
    */
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose);
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        // 遍历commands里面的每个指令cmd
        for (const auto cmd : commands)
        {
            // 如果是M指令
            if (cmd == 'M')
            {
               Move(); 
            }
            else if (cmd == 'L')
            {
                TurnLeft();
            }
            else if (cmd == 'R')
            {
                if (pose.heading == 'E')
                {
                    pose.heading = 'S';
                }
                else if (pose.heading == 'S')
                {
                    pose.heading = 'W';
                }
                else if (pose.heading == 'W')
                {
                    pose.heading = 'N';
                }
                else if (pose.heading == 'N')
                {
                    pose.heading = 'E';
                }
            }
        }
    }

    void ExecutorImpl::Move() noexcept
    {
        if(pose.heading == 'E')
        {
            ++pose.x;
        }else if(pose.heading == 'W'){
            --pose.x;
        }else if(pose.heading == 'N'){
            ++pose.y;
        }else if(pose.heading == 'S'){
            --pose.y;
        }
    }

    void ExecutorImpl::TurnLeft() noexcept
    {
        if (pose.heading == 'E')
        {
            pose.heading = 'N';
        }
        else if (pose.heading == 'W')
        {
            pose.heading = 'S';
        }
        else if (pose.heading == 'N')
        {
            pose.heading = 'W';
        }
        else if (pose.heading == 'S')
        {
            pose.heading = 'E';
        }
    }
    
}