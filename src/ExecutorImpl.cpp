#include "ExecutorImpl.hpp"

#include "cmder/CmdFactory.hpp"
#include "core/Singleton.hpp"

#include "cmder/BusOrchestrator.hpp"
#include "cmder/NormalOrchestrator.hpp"
#include "cmder/SportsCarOrchestrator.hpp"
#include <algorithm>
// #include <new>
// #include <memory>
// #include <unordered_map>

namespace adas
{
    ExecutorImpl::ExecutorImpl(const Pose &pose, CmderOrchestrator* orchestrator) noexcept : poseHandler(pose), orchestrator(orchestrator){}

    Pose ExecutorImpl::Query(void) const noexcept
    {
        return poseHandler.Query();
    }

    /*
        std::nothrow 是 C++ 标准库中的一个常量，用于指示在分配内存时不抛出任何异常
        它是 std::nothrow_t 类型的实例，通常用在 new 运算符和 std::nothrow 命名空间中，
        以请求内存分配器在分配失败时返回一个空指针，而不是抛出 std::bad_alloc 异常
    */
    Executor *Executor::NewExecutor(const Pose &pose, const ExecutorType executorType) noexcept
    {
        CmderOrchestrator *orchestrator = nullptr;

        switch (executorType)
        {
            case ExecutorType::NORMAL:{
                orchestrator = new(std::nothrow) NormalOrchestrator();
                break;
            }

            case ExecutorType::SPORTS_CAR:{
                orchestrator = new(std::nothrow) SportsCarOrchestrator();
                break;
            }

            case ExecutorType::BUS:{
                orchestrator = new(std::nothrow) BusOrchestrator();
                break;
            }
        }

        return new(std::nothrow) ExecutorImpl(pose, orchestrator);
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

        std::for_each(
            cmders.begin(),
            cmders.end(),
            [this](const Cmder &cmder) noexcept {
                cmder(poseHandler, *orchestrator).DoOperate(poseHandler);
            }
        );
    }
}