#pragma once

#include "core/PoseHandler.hpp"
#include <functional>
#include "ActionGroup.hpp"

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
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept{
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
            return actionGroup;
        }
        
    };
    
    class MoveCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept{
            // 创建actionGroup对象
            ActionGroup actionGroup;

            // 如果当前是倒车状态，action为ActionType::BACKWARD_1_STEP_ACTION
            // 如果当前不是倒车状态，action为ActionType::FORWARD_1_STEP_ACTION
            const auto action = poseHandler.IsReverse() ?
                ActionType::BACKWARD_1_STEP_ACTION : 
                ActionType::FORWARD_1_STEP_ACTION;

            // 如果当前是加速状态，则额外执行一次action
            // 所以要额外地将action加到actionGroup
            // 因为ActionGroup里面是要执行的action序列
            if(poseHandler.IsFast()){
                actionGroup.PushAction(action);
            }

            // 无论是否为加速状态，这一个action是必须要加入到actionGroup去执行
            actionGroup.PushAction(action);
            return actionGroup;
        }
    };
    class TurnLeftCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept{
            ActionGroup actionGroup;
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }

            if(poseHandler.IsReverse()){
                actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            }else{
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            }
            return actionGroup;
        }
    };
    class TurnRightCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept{
            ActionGroup actionGroup;
            if(poseHandler.IsFast()){
                if(poseHandler.IsReverse()){
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                }else{
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                }
            }

            if(poseHandler.IsReverse()){
                actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            }else{
                actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            }
            return actionGroup;
        }
    };

    class FastCommand final //: public ICommand
    {
    public:
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
            ActionGroup actionGroup;
            actionGroup.PushAction(ActionType::BE_FAST_ACTION);
            return actionGroup;
        }
    };

    class TurnRoundCommand final {
    public:
        ActionGroup operator()(PoseHandler& poseHandler) const noexcept{
            // 如果是倒车状态
            if(poseHandler.IsReverse()){
                return ActionGroup();//倒车状态下不执行任何操作
            }
            else{
                if(poseHandler.IsFast()){
                    return ActionGroup({
                        ActionType::FORWARD_1_STEP_ACTION, //前进一步
                        ActionType::TURNLEFT_ACTION, //左转
                        ActionType::FORWARD_1_STEP_ACTION, //前进一步
                        ActionType::TURNLEFT_ACTION, //左转
                    });
                }
                else{//正常状态
                    return ActionGroup({
                        ActionType::TURNLEFT_ACTION, //左转
                        ActionType::FORWARD_1_STEP_ACTION, //前进一步
                        ActionType::TURNLEFT_ACTION, //左转
                    });
                }
            }
        }
    };
    

} // namespace adas