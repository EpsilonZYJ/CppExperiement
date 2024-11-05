#include "ExecutorImpl.hpp"

#include <new>
#include <memory>
#include <unordered_map>

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
        //表驱动
        std::unordered_map<char, std::function<void(PoseHandler& PoseHandler)>> cmderMap;
        //建立操作M和前进指令的映射关系
        cmderMap.emplace('M', MoveCommand());
        //建立操作L和左转指令的映射关系
        cmderMap.emplace('L', TurnLeftCommand());
        //建立操作R和右转指令的映射关系
        cmderMap.emplace('R', TurnRightCommand());
        //建立操作F和快速指令的映射关系
        cmderMap.emplace('F', FastCommand());

        // 遍历commands里面的每个指令cmd
        for (const auto cmd : commands)
        {
            //根据操作查找表驱动
            const auto it = cmderMap.find(cmd);
            // 如果找到表驱动，执行操作对应的指令
            if(it != cmderMap.end()){
                it->second(poseHandler);
            }
        }
    }
}