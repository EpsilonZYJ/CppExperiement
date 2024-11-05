#include "ExecutorImpl.hpp"

#include <new>
#include <memory>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose){}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
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
            //声明一个ICommand类型的智能指针
            std::unique_ptr<ICommand> cmder = nullptr;
            if (cmd == 'M')
            {
                //智能指针指向子类MoveCommand实例
                cmder = std::make_unique<MoveCommand>();
            }
            else if (cmd == 'L')
            {
                cmder = std::make_unique<TurnLeftCommand>();
            }
            else if (cmd == 'R')
            {
                cmder = std::make_unique<TurnRightCommand>();
            }
            else if(cmd == 'F')
            {
                cmder = std::make_unique<FastCommand>();
            }

            if(cmder)
            {
                cmder->DoOperate(poseHandler);
            }
        }
    }
}