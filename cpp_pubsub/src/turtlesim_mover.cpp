// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "geometry_msgs/msg/twist.hpp"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>



using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalPublisher::timer_callback, this));

  }

private:
  void timer_callback()
  {
  signal++;

  if(signal ==1)
  {
    cmd_vel.linear.x = x_velocity;
    cmd_vel.linear.y = 0;
    RCLCPP_INFO(this->get_logger(), "right!");
  }

  if(signal == 2)
  {
    cmd_vel.linear.x = 0;
    cmd_vel.linear.y = y_velocity;
    RCLCPP_INFO(this->get_logger(), "Up!");
  }

  if(signal == 3)
  {
    cmd_vel.linear.x = -x_velocity;
    cmd_vel.linear.y = 0;
    RCLCPP_INFO(this->get_logger(), "Left!");
  }

  if(signal == 4)
  {
    cmd_vel.linear.x = 0;
    cmd_vel.linear.y = -y_velocity;
    RCLCPP_INFO(this->get_logger(), "Down!");

    signal = 0;
  }


    publisher_->publish(cmd_vel);

    //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

  //-Init variables
  geometry_msgs::msg::Twist cmd_vel;
  double x_velocity = 3;
  double y_velocity = 3;
  double ang_velocity = 1;
  int signal = 0; //

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
