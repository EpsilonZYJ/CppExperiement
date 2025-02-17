#include "PoseHandler.hpp"

namespace adas{
    PoseHandler::PoseHandler(const Pose &pose) noexcept
        //初始化Pose改为初始化Point和Direction
        : point(pose.x, pose.y)
        , facing(&Direction::GetDirection(pose.heading)) {}

    void PoseHandler::Forward() noexcept{
        // 将当前坐标加上方向向量
        point += facing->Move();
    }

    void PoseHandler::Backward() noexcept{
        // 将当前坐标减去方向向量
        point -= facing->Move();
    }

    void PoseHandler::TurnLeft() noexcept{
        //左转
        facing = &(facing->LeftOne());
    }

    void PoseHandler::TurnRight() noexcept{
        //右转
        facing = &(facing->RightOne());
    }

    void PoseHandler::Fast() noexcept{
        fast = !fast;
    }

    void PoseHandler::Reverse() noexcept{
        reverse = !reverse;
    }

    bool PoseHandler::IsReverse() const noexcept{
        return reverse;
    }

    bool PoseHandler::IsFast() const noexcept{
        return fast;
    }

    Pose PoseHandler::Query(void) const noexcept{
        return {point.GetX(), point.GetY(), facing->GetHeading()};
    }
}