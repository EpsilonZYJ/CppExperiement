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
    class ReverseCommand final
    {
    public:
        void operator()(PoseHandler& poseHandler) const noexcept{
            poseHandler.Reverse();
        }
    };
    
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
        // const std::function<void(PoseHandler& PoseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
        //     if(poseHandler.IsFast()){
        //         poseHandler.Move();
        //     }
        //     poseHandler.Move();
        // };

        void operator()(PoseHandler& poseHandler) const noexcept{
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    poseHandler.Backward();
                }else{
                    poseHandler.Forward();
                }
            }

            if(poseHandler.IsReverse()){
                poseHandler.Backward();
            }else{
                poseHandler.Forward();
            }
        }
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

        // const std::function<void(PoseHandler& PoseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
        //     if(poseHandler.IsFast()){
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnLeft();
        // };

        void operator()(PoseHandler& poseHandler) const noexcept{
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    poseHandler.Backward();
                }else{
                    poseHandler.Forward();
                }
            }
            
            if(poseHandler.IsReverse()){
                poseHandler.TurnRight();
            }else{
                poseHandler.TurnLeft();
            }
        }
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
        // const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
        //     if(poseHandler.IsFast()){
        //         poseHandler.Move();
        //     }
        //     poseHandler.TurnRight();
        // };

        void operator()(PoseHandler& poseHandler) const noexcept{
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    poseHandler.Backward();
                }else{
                    poseHandler.Forward();
                }
            }

            if(poseHandler.IsReverse()){
                poseHandler.TurnLeft();
            }else{
                poseHandler.TurnRight();
            }
        }
    };

    class FastCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler& poseHandler) const noexcept override
        // {
        //     poseHandler.Fast();
        // }
        // const std::function<void(PoseHandler& poseHandler)> operate = [](PoseHandler& poseHandler) noexcept{
        //     poseHandler.Fast();
        // };

        void operator()(PoseHandler& poseHandler) const noexcept{
            poseHandler.Fast();
        }
    };

} // namespace adas