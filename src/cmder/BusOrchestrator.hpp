#pragma once

#include "NormalOrchestrator.hpp"

namespace adas {

    class BusOrchestrator : public NormalOrchestrator{
    public:
        ActionGroup TurnLeft(const PoseHandler& poseHandler) const noexcept override{
            ActionGroup actionGroup;

            actionGroup += OnFast(poseHandler);

            actionGroup.PushAction(GetStepAction(poseHandler));
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

            actionGroup.PushAction(GetStepAction(poseHandler));
            if(poseHandler.IsReverse()){
                actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            }
            else{
                actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            }
            
            return actionGroup;
        }
    };
}