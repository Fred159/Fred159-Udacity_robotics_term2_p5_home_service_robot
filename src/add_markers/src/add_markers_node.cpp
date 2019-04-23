/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/UInt8.h>

// %EndTag(INCLUDES)%
//initialize a value for change marker behavior
uint8_t behavior = 0;

void pickobjectsCallback(const std_msgs::UInt8::ConstPtr& msg) 
  { 
    ROS_INFO("Received the cycle message from goal state. This is means robot reach the goal");
    ROS_INFO("The behavior of robot should be %d ", msg->data);
    behavior = msg->data;
   return;
  }

int main( int argc, char** argv )
{
  ROS_INFO("start add marker.cpp main.");
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
//  origin  is  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //If the data is not automated, then it do not have to subscribe to the publisher
  ros::Subscriber goal_sub = n.subscribe("/reach_goal", 1, pickobjectsCallback);

  uint32_t shape = visualization_msgs::Marker::CUBE;
// %EndTag(SHAPE_INIT)%

// %Tag(MARKER_INIT)%
  while (ros::ok())
    {   
        ros::spinOnce();

        visualization_msgs::Marker marker;
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "/map";
        marker.header.stamp = ros::Time::now();
    // %EndTag(MARKER_INIT)%

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
    // %Tag(NS_ID)%
        marker.ns = "basic_shapes";
        marker.id = 0;
    // %EndTag(NS_ID)%

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    // %Tag(TYPE)%
        marker.type = shape;
        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    // %Tag(ACTION)%

    ROS_INFO("input to the switch (the behavior) is %d", behavior);

        switch(behavior)
            {
            case 0:
                ROS_INFO("add marker file. robot still trying to get goal position, case 0");
                marker.action = visualization_msgs::Marker::ADD;
                marker.pose.position.x = -4.8;
                marker.pose.position.y = -7;
                marker.pose.position.z = 0;
                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 0.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;
                break;
                // %EndTag(POSE)%

            case 1:
                ROS_INFO("add marker file. robot reach first goal position delete marker, case 1");
                marker.action = visualization_msgs::Marker::DELETE;
                break;
                
            case 2:
                ROS_INFO("add marker file. wait for manipulating andd add second goal position. case 2");
                // Add second goal position
                marker.action = visualization_msgs::Marker::DELETE;
                break;
                
            case 3:
                ROS_INFO("add marker file .Robot reach second position. stand by for other command, case 3---");
                marker.action = visualization_msgs::Marker::ADD;
                marker.pose.position.x = -2.0;
                marker.pose.position.y = -7.0;
                marker.pose.position.z = 0;
                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 1.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;
                break;
            }
        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        // %Tag(SCALE)%
        marker.scale.x = 0.5;
        marker.scale.y = 0.5;
        marker.scale.z = 0.5;
        // %EndTag(SCALE)%
        
            // %Tag(LIFETIME)%
        marker.color.r = 1.0f;
        marker.color.g = 1.0f;
        marker.color.b = 1.0f;
        marker.color.a = 1.0;
        marker.lifetime = ros::Duration();
        // %EndTag(LIFETIME)%
            
        // Publish the marker 
        while (marker_pub.getNumSubscribers() < 1)
            {
                {
                if (!ros::ok())
                    {
                        return 0;
                    }
                ROS_WARN_ONCE("Please create a subscriber to the marker");
                sleep(2);
                }
            }

        marker_pub.publish(marker);
        r.sleep();
    }
return 0;
}