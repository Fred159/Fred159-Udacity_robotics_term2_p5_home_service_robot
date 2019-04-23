#!/bin/sh
pkgsrc_dir=/home/workspace/catkin_ws/src

#Launch turtlebot in the custom world
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$pkgsrc_dir/ming_world/simple_world.world" &
sleep 10

#Launch gmapping demo
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$pkgsrc_dir/ming_world/ming_map.yaml" &
sleep 5

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
sleep 5
