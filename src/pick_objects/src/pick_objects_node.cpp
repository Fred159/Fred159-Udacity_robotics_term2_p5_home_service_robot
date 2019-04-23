#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
//   ros::init(argc, argv, "simple_navigation_goals");
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  ros::NodeHandle n;
  //Should add a publisher for publish the pick position
  //set up publisher to broadcast if robot is at pick up location
  ros::Publisher location_pub = n.advertise<std_msgs::UInt8>("reach_goal", 1);
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

std_msgs::UInt8 msg;  
msg.data = 0;
ROS_INFO("The message is %d", msg.data);
location_pub.publish(msg);

  // set up the frame parameters
  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -4.8;
   goal.target_pose.pose.position.y = -7;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending single goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
    ROS_INFO("Hooray, robot reach first goal");
    // std_msgs::UInt8 msg;
    msg.data = 1;
    ROS_INFO("The message is %d", msg.data);
    location_pub.publish(msg);
    msg.data = 2;
    ROS_INFO("After hold 5 seconds, The message is %d", msg.data);
    location_pub.publish(msg);
    sleep(5);
    }
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");


// second goal position published
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -2.0;
  goal.target_pose.pose.position.y = -7;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending second goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
    ROS_INFO("Hooray, the base reached the second goal");
    // std_msgs::UInt8 msg;
    msg.data = 3;
    ROS_INFO("The message is %d", msg.data);
    location_pub.publish(msg);
    
    sleep(5);
    msg.data = 4;
    ROS_INFO("The message is %d", msg.data);
    ROS_INFO("complete mission . wait for new command");
    location_pub.publish(msg);
    }
  else
    ROS_INFO("The base failed to reach second goal with some reasons");

  return 0;
}