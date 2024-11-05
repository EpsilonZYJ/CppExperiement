#pragma once

#include "Command.hpp"
#include "Executor.hpp"
#include "PoseHandler.hpp"
#include <string>

namespace adas
{
    /*
        Executor的具体实现
    */
    class ExecutorImpl final: public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose) noexcept;
        // 默认析构函数
        ~ExecutorImpl() noexcept = default;

        // 不能拷贝
        ExecutorImpl(const ExecutorImpl &) = delete;
        // 不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        // 查询当前汽车姿态，是父类抽象方法Query的具体实现
        Pose Query(void) const noexcept override;
        // 第二结点新增加的纯虚函数，执行一个用字符串表示的指令
        void Execute(const std::string &commands) noexcept override;
        
    private:
        PoseHandler poseHandler;    //状态管理类
    };
}