#pragma once

#include "Executor.hpp"
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
        // 私有数据成员，汽车当前姿态
        Pose pose;
        //是否处于加速状态，默认是false
        bool isFast;
        void Move(void) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;
        void Fast(void) noexcept;

        bool IsFast(void) const noexcept;

        class ICommand
        {
        public:
        virtual ~ICommand() = default;
        virtual void DoOperate(ExecutorImpl& ExecutorImpl) const noexcept = 0;
        };

        class MoveCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl& executor) const noexcept override
            {
                if(executor.IsFast())
                {
                    executor.Move();
                }
                executor.Move();
            }
        };
        class TurnLeftCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl& executor) const noexcept override
            {
                if(executor.IsFast())
                {
                    executor.Move();
                }
                executor.TurnLeft();
            }
        };
        class TurnRightCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl& executor) const noexcept override
            {
                if(executor.IsFast())
                {
                    executor.Move();
                }
                executor.TurnRight();
            }
        };
        class FastCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl& executor) const noexcept override
            {
                executor.Fast();
            }
        };
    };
}