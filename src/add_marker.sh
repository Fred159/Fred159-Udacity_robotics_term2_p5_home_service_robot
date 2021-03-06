#!/bin/sh
pkgsrc_dir=/home/workspace/catkin_ws/src

#Launch turtlebot in the custom world
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$pkgsrc_dir/ming_world/simple_world.world " &
sleep 5

xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$pkgsrc_dir/ming_world/ming_map.yaml " &
sleep 3

#launch add_markers_node
xterm -e " rosrun add_markers add_markers_node " &
sleep 3

#Start pick objects node
xterm -e " rosrun pick_objects pick_objects_node " &
sleep 3

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch "
