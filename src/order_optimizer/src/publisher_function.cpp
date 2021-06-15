#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <vector>
#include <iostream>

using namespace std;

using namespace std::chrono_literals;

geometry_msgs::msg::PoseStamped current_pos;
int order_id;
std::string order_description;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class SendOrder : public rclcpp::Node
{
public:
  SendOrder()
  : Node("SendOrder")
  {
    publisher_1 = this->create_publisher<std_msgs::msg::String>("CurrentPosition", 10);
    publisher_2 = this->create_publisher<std_msgs::msg::String>("NextOrder", 10);
    timer_1 = this->create_wall_timer(
      500ms, std::bind(&SendOrder::current_position_callback, this));
    timer_2 = this->create_wall_timer(
              500ms, std::bind(&SendOrder::next_order_callback, this));
  }

private:
  void current_position_callback()
  {
    auto message_1 = std_msgs::msg::String();
    message_1.data = std::to_string(current_pos.pose.position.x) +"|"+ std::to_string(current_pos.pose.position.y);
            RCLCPP_INFO(this->get_logger(), "Value: '%s'", message_1.data.c_str());
    publisher_1->publish(message_1);
  }
  void next_order_callback()
    {
        auto message_2 = std_msgs::msg::String();
        message_2.data = std::to_string(order_id) +"|"+ order_description;
        RCLCPP_INFO(this->get_logger(), "Values: '%s'", message_2.data.c_str());
        publisher_2->publish(message_2);
    }
    rclcpp::TimerBase::SharedPtr timer_1;
    rclcpp::TimerBase::SharedPtr timer_2;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_1;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_2;

};

int main(int argc, char **argv){

    //
    //check number of arguments
    //
    if (argc != 9) {
        std::cerr << "Usage: ros2 run order_optimizer SendOrder " << std::endl;
        std::cerr << "       -id    ->    order id" << std::endl;
        std::cerr << "       -de    ->    order description" << std::endl;
        std::cerr << "       -x     ->    x coordinate of current position" << std::endl;
        std::cerr << "       -y     ->    y coordinate of current position" << std::endl;
        return 1;
    }
    int id;
    int parameters=0;
    float x, y;
    std::string error_message = "";
    std::string de;
    for (int i=0; i<8; i++){
        std::string arg = argv[i];
        if (arg=="-id"){
            try{
            id = std::stoi(argv[i+1]);
            parameters++;
            }
            catch(int e){
                error_message = error_message + "Order ID should be a number. Please use some number (int type) for order ID. ";
            }
        }
        if (arg=="-de"){
            try{
                de = argv[i+1];
                parameters++;
            }
            catch(int e){
                error_message = error_message + "Problem with order description. Please add it correct.";
            }
        }
        if (arg =="-x"){
            try{
                x = std::stof(argv[i+1]);
            //x = boost::lexical_cast<std::float>(argv[i+1].c_str());
            parameters++;
            }
            catch(int e){
                error_message = error_message + "X coordinate should be a number. Please use some number (float type) for x coordinate. ";
            }
        }
        if (arg =="-y"){
            try{
            y = std::stof(argv[i+1]);
            parameters++;
            }
            catch(int e){
                error_message = error_message +  "Y coordinate should be a number. Please use some number (float type) for y coordinate.";
            }
        }
    }
    if (parameters!=4){
        std::cerr << error_message << std::endl;
        std::cerr << "Usage: ros2 run order_optimizer SendOrder -id <order id> -de <order description> -x <x coordinate> -y <y coordinate>" << std::endl;
        return 1;
    }
    current_pos.pose.position.x = x;
    current_pos.pose.position.y = y;
    order_id = id;
    order_description = de;

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SendOrder>());
  rclcpp::shutdown();
  return 0;
}
