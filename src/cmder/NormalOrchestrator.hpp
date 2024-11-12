#pragma once

#include "CmderOrchestrator.hpp"

namespace adas{

    class NormalOrchestrator : public CmderOrchestrator{
    public:
        ActionGroup Move(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;

            actionGroup += OnFast(poseHandler);

            actionGroup.PushAction(GetStepAction(poseHandler));

            return actionGroup;
        }

        ActionGroup TurnLeft(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;

            actionGroup += OnFast(poseHandler);

            if(poseHandler.IsReverse()){
                actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            }
            else{
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            }

            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;

            actionGroup += OnFast(poseHandler);
            if(poseHandler.IsReverse()){
                actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            }
            else{
                actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            }

            return actionGroup;
        }

        ActionGroup TurnRound(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;

            if(poseHandler.IsReverse()){
                return actionGroup;
            }
            else{
                actionGroup += OnFast(poseHandler);
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
                actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            }

            return actionGroup;
        }

    protected:
        ActionType GetStepAction(const PoseHandler& poseHandler) const noexcept{
            return poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        }

        ActionGroup OnFast(const PoseHandler& poseHandler) const noexcept{
            if(poseHandler.IsFast()){
                return ActionGroup({GetStepAction(poseHandler)});
            }

            return ActionGroup();
        }
    };
}