# Youbot Visulaization with rviz

Make sure you are in the current workspace and run the following command.

	catkin_make

After the successful build of the repo

Source the env by running the following command

	source /devel/setup.bash

Once the env is sourced. To visualize the robot run the following commnd.

	roslaunch robot rviz.launch

Now, you will see a rviz screnn with nothing in it. What to do?

Follow the following instructions to visualize the robot
- First change the Fixed Frame in the Global options in RVIZ to base_link
- In the bottom right, there is add option.
- In that, add the "RobotModel" from display type

Now you should be able to visulaize the robot.

There are also `joint_state_publishers` you can use this to play with the robot_arm to see how it moves around.










***
### Useful Links
[Visualizing RobotModel from Scratch using ROS noetic in RVIZ](https://www.youtube.com/watch?v=OAdSxAcel9g)
