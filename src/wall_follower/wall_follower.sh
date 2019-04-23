#!/bin/sh
pkgsrc_dir=/home/workspace/catkin_ws/src

#Launch turtlebot in the custom world
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$pkgsrc_dir/ming_world/simple_world.world" &
sleep 2

#Launch gmapping demo
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 2

#run wall_follower node
xterm -e " rosrun wall_follower wall_follower_node " &
sleep 5

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 200

#run map server for save a map
xterm -e " rosrun map_server map_saver -f /home/workspace/catkin_ws/src/ming_world/ming_map" &
sleep 2

