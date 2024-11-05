#include <gtest/gtest.h>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas{
    // 测试输入：BM
    TEST(ExecutorFastTest, should_return_x_minus_1_given_status_is_reverse_command_is_M_and_facing_is_E){
        //given
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
        //when
        executor->Execute("BM");
        //then
        const Pose target{-1, 0, 'E'};
        ASSERT_EQ(target, executor->Query());
    }

    // 测试输入：BL
    TEST(ExecutorFastTest, should_return_S_given_status_is_reverse_command_is_L_and_facing_is_E){
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
        executor->Execute("BL");
        const Pose target{0, 0, 'S'};
        ASSERT_EQ(target, executor->Query());
    }

    // 测试输入：BR
    TEST(ExecutorFastTest, should_return_N_given_status_is_reverse_command_is_R_and_facing_is_E){
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
        executor->Execute("BR");
        const Pose target{0, 0, 'N'};
        ASSERT_EQ(target, executor->Query());
    }

    // 测试输入：BBM
    TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_BBM_and_facing_is_N){
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
        executor->Execute("BBM");
        const Pose target{0, 1, 'N'};
        ASSERT_EQ(target, executor->Query());
    }
}