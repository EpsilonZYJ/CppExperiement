#pragma once

#include "ExecutorImpl.hpp"

namespace adas{
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
} // namespace adas