#pragma once

#include "PoseHandler.hpp"
#include <functional>

namespace adas{
    // class ICommand
    // {
    // public:
    // virtual ~ICommand() = default;
    // virtual void DoOperate(PoseHandler& poseHandler) const noexcept = 0;
    // };

    class MoveCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler& poseHandler) const noexcept override
        // {
        //     if(poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.Move();
        // }
        
        // 定义函数对象operate，接收参数PoseHandler，返回void
        const std::function<void(PoseHandler& PoseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
            if(poseHandler.IsFast()){
                poseHandler.Move();
            }
            poseHandler.Move();
        };
    };
    class TurnLeftCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler& poseHandler) const noexcept override
        // {
        //     if(poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnLeft();
        // }

        const std::function<void(PoseHandler& PoseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
            if(poseHandler.IsFast()){
                poseHandler.Move();
            }
            poseHandler.TurnLeft();
        };
    };
    class TurnRightCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler& poseHandler) const noexcept override
        // {
        //     if(poseHandler.IsFast())
        //     {
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnRight();
        // }
        const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
            if(poseHandler.IsFast()){
                poseHandler.Move();
            }
            poseHandler.TurnRight();
        };
    };

    class FastCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler& poseHandler) const noexcept override
        // {
        //     poseHandler.Fast();
        // }
        const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
            poseHandler.Fast();
        };
    };
} // namespace adas