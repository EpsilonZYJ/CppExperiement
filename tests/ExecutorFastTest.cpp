#include <gtest/gtest.h>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
    TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
    {
        //given
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); 

        //when
        executor->Execute("FM");//FM:F状态下Move

        //then
        const Pose target{2, 0, 'E'};
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); 
        executor->Execute("FL");
        const Pose target{1, 0, 'N'};
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); 
        executor->Execute("FR");
        const Pose target{1, 0, 'S'};
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
    {
        std::unique_ptr<Executor> executor(Executor::NewExecutor());
        executor->Execute("FFM");
        const Pose target{0, 1, 'N'};
        ASSERT_EQ(target, executor->Query());
    }
}