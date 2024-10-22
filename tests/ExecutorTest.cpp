#include "Executor.hpp"
#include "PoseEq.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <tuple>

namespace adas
{
    // // 重载Pose的==，用的全局函数，用于比较两个姿态对象是不是相对
    // bool operator==(const Pose &lhs, const Pose &rhs)
    // {
    //     return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
    // }

    // 下面两个测试用例，测试静态方法Executor::NewExecutor
    // 测试用例1
    TEST(ExecutorTest, should_return_init_pose_when_without_command)
    {
        // given 给定测试条件
        // 测试条件就是调用Executor的静态方法NewExecutor 返回一个指向Executor对象的智能指针executor，这样我们就不需要去delete了
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势

        // when

        // then
        const Pose target({0, 0, 'E'}); // 构造一个姿势对象target，其内容为{0, 0, 'E'}
        // 既然构造Executor对象时的初始姿势是{0, 0, 'E'}，那么executor->Query返回的Executor对象的姿势必须等于target
        // 所以这里用了断言：executor->Query()返回的Executor对象的姿势必须等于target，否则测试失败，说明Executor的实现有问题
        ASSERT_EQ(target, executor->Query()); // ASSERT_EQ内部调用了重载的Pose的==
    }
    // 测试用例2
    TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
    {
        // given
        std::unique_ptr<Executor> executor(Executor::NewExecutor()); // 没有给初始姿势

        // when

        // then
        const Pose target({0, 0, 'N'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试M指令
    // 测试用例3 测试Execute方法，在朝向为E，起点为 （0，0） 时去执行M指令是否正确
    TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'})); // 给了初始姿势，当前朝向是E，起点（0，0）

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("M");

        // then
        const Pose target({1, 0, 'E'});       // 如果执行M指令正确，新的姿势应该是target：{1， 0， 'E'}
        ASSERT_EQ(target, executor->Query()); // 当M指令执行完，executor->Query返回的汽车姿势应该等于target: {1， 0， 'E'}
    }
    TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("M");

        // then
        const Pose target({-1, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("M");

        // then
        const Pose target({0, 1, 'N'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("M");

        // then
        const Pose target({0, -1, 'S'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试L指令
    TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("L");

        // then
        const Pose target({0, 0, 'N'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("L");

        // then
        const Pose target({0, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("L");

        // then
        const Pose target({0, 0, 'S'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("L");

        // then
        const Pose target({0, 0, 'E'});
        ASSERT_EQ(target, executor->Query());
    }

    // 测试R指令
    TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("R");

        // then
        const Pose target({0, 0, 'S'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("R");

        // then
        const Pose target({0, 0, 'W'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("R");

        // then
        const Pose target({0, 0, 'N'});
        ASSERT_EQ(target, executor->Query());
    }
    TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N)
    {
        // given 给定一个executor
        std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

        // when 调用executor的Execute方法去执行M指令
        executor->Execute("R");

        // then
        const Pose target({0, 0, 'E'});
        ASSERT_EQ(target, executor->Query());
    }
}