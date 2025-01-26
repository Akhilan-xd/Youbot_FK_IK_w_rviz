#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/TransformStamped.h"
from moveit_commander import RobotCommander

void joint_states_callback(const sensor_msgs::JointState::ConstPtr& msg) {
    ROS_INFO("Received joint state data!");
}

int main(int argc, char** argv) {
    // Initialize the ROS node
    ros::init(argc, argv, "ee_pose");
    ros::NodeHandle nh;

    // Publishers
    ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/joint_states", 10);
    ros::Rate rate(100);  // 100 Hz loop rate

    // Define start and end joint states
    std::vector<double> start_joint_states = {0.29, 1.56, -3.49, 2.72, 2.87, 0.01, 0.01};
    std::vector<double> end_joint_states = {1.1538, 2.3047, 5.0877, 0.5217, 5.6785, 0.00893, 0.00585};
    std::vector<std::string> joint_names = {"arm_joint_1", "arm_joint_2", "arm_joint_3", "arm_joint_4", "arm_joint_5", "gripper_finger_joint_l", "gripper_finger_joint_r"};

    // Total movement time in seconds
    double total_time = 5;  // 5 seconds to reach the target position
    int total_steps = total_time * 100;  // 100 Hz rate * total_time
    std::vector<double> current_joint_states = start_joint_states;

    // Interpolation step size for each joint
    std::vector<double> step_size(7);
    for (int i = 0; i < 7; i++) {
        step_size[i] = (end_joint_states[i] - start_joint_states[i]) / total_steps;
    }

    // Loop to gradually move joints to the target position
    for (int step = 0; step <= total_steps && ros::ok(); step++) {
        sensor_msgs::JointState joint_state_msg;
        joint_state_msg.header.stamp = ros::Time::now();
        joint_state_msg.name = joint_names;

        // Increment each joint position
        for (int i = 0; i < 7; i++) {

            if (current_joint_states[0] == end_joint_states[0]){
                step_size[0]=0;
            }

            else if(current_joint_states[1] == end_joint_states[1]){
                step_size[1]=0;
            }
            
            else if(current_joint_states[2] == end_joint_states[2]){
                step_size[2]=0;
            }

            else if(current_joint_states[3] == end_joint_states[3]){
                step_size[3]=0;
            }

            else if(current_joint_states[4] == end_joint_states[4]){
                step_size[4]=0;
            }

            else if(current_joint_states[5] == end_joint_states[5]){
                step_size[5]=0;
            }

            else if(current_joint_states[6] == end_joint_states[6]){
                step_size[6]=0;
            }

            else if(current_joint_states[7] == end_joint_states[7]){
                step_size[7]=0;
            }

            else{
                current_joint_states[i] += step_size[i];    
            }
        }



        joint_state_msg.position = current_joint_states;

        // Publish the joint states
        joint_states_pub.publish(joint_state_msg);

        ROS_INFO("Publishing joint states at step %d", step);

        ros::spinOnce();
        rate.sleep();
    }

    ROS_INFO("Movement completed!");

    return 0;
}

// #include "ros/ros.h"
// #include "sensor_msgs/JointState.h"
// #include "geometry_msgs/Pose.h"
// #include "tf2_ros/transform_listener.h"
// #include "tf2_ros/buffer.h"
// #include "geometry_msgs/TransformStamped.h"

// void joint_states_callback(const sensor_msgs::JointState::ConstPtr& msg) {
//     // Callback logic (if needed)
//     ROS_INFO("Received joint state data!");
// }

// int main(int argc, char** argv) {
//     // Initialize the ROS node
//     ros::init(argc, argv, "ee_pose");
//     ros::NodeHandle nh;

//     // Publisher for the end-effector pose
//     ros::Publisher pose_pub = nh.advertise<geometry_msgs::Pose>("/ee_pose", 10);
//     // Subscriber for joint states
//     ros::Subscriber joint_states_sub = nh.subscribe("/joint_states", 10, joint_states_callback);
//     ros::Rate rate(100); // 100 Hz for joint state updates
    
//     while (ros::ok()) {
//         // Your code logic here
//         ros::spinOnce();
//         rate.sleep();

//         // Create a publisher for joint states
//     ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/joint_states", 10);

//     // Total movement time in seconds
//     double total_time = 5.0;  // 5 seconds to reach the target position
//     int total_steps = total_time * 100;  // 100 Hz rate * total_time
//     std::vector<double> current_joint_states = start_joint_states;

//     // To Create a home joint state message
//     sensor_msgs::JointState start_joint_states;
//     start_joint_states.header.seq = 21828;  // Sequence number
//     start_joint_states.header.stamp = ros::Time::now();  // Current timestamp
//     start_joint_states.header.frame_id = "";  // No frame ID for this message

//     start_joint_states.name.resize(7);
//     start_joint_states.position.resize(7);

//     joint_name = ["arm_joint_1","arm_joint_2","arm_joint_3","arm_joint_4","arm_joint_5","gripper_finger_joint_l","gripper_finger_joint_r"]
//     start_joint_states=[0.0,0.0,0.0,0.0,0.0,0.0,0.0]
//     end_joint_states=[1.1538026194722737,2.3047470622665571,5.0877307626692305,0.5216614601288221,5.6784636279476155,0.00893,0.0058519999999999996]
//     movement_joint_states = [0.0,0.0,0.0,0.0,0.0,0.0,0.0]


//     // filling the name using a for loop
//     for (int i = 0; i < 7; i++) {
//         start_joint_states.name[i] = joint_name[i];
//         start_joint_states.position[i] = start_joint_states[i];
//     }
//     // Publish start joint states
//     joint_states_pub.publish(start_joint_states);
//     ROS_INFO("Published home joint states");
    
//     // Creating and filling a JointState message
//     sensor_msgs::JointState movement_joint_states;
//     movement_joint_states.header.seq = 21828;  // Sequence number
//     movement_joint_states.header.stamp = ros::Time::now();  // Current timestamp
//     movement_joint_states.header.frame_id = "";  // No frame ID for this message

//     movement_joint_states.name.resize(7);
//     movement_joint_states.position.resize(7);
    
//     for (int i = 0; i < 7; i++) {
//         movement_joint_states.name[i] = joint_name[i];
//         // calculating the movement joint states
//         movement_joint_states.position[i] = end_joint_states[i] - start_joint_states[i];
//     }

//     // Publish joint states
//     joint_states_pub.publish(move_joint_states);
//     ROS_INFO("Published joint states");

//     // TF2 Buffer and Listener
//     tf2_ros::Buffer tfBuffer;
//     tf2_ros::TransformListener tfListener(tfBuffer);
//     }

//     return 0;
// }


// #include "ros/ros.h"
// #include "sensor_msgs/JointState.h"
// #include "geometry_msgs/Pose.h"
// #include "tf2_ros/transform_listener.h"
// #include "tf2_ros/buffer.h"
// #include "geometry_msgs/TransformStamped.h"
// #include <cmath>

// // Target end-effector pose (for example purposes)
// geometry_msgs::Pose target_pose;

// // Function to compute the difference between two poses
// void computePoseError(const geometry_msgs::Pose& current_pose, const geometry_msgs::Pose& target_pose,
//                       double& pos_error, double& ori_error) {
//     // Position error (Euclidean distance)
//     double dx = target_pose.position.x - current_pose.position.x;
//     double dy = target_pose.position.y - current_pose.position.y;
//     double dz = target_pose.position.z - current_pose.position.z;
//     pos_error = std::sqrt(dx * dx + dy * dy + dz * dz);

//     // Simplified orientation error as a placeholder (use quaternion math for precise calculations)
//     ori_error = 0.0; // Add proper quaternion comparison if needed.
// }

// int main(int argc, char** argv) {
//     // Initialize the ROS node
//     ros::init(argc, argv, "ee_pose_controller");
//     ros::NodeHandle nh;

//     // Publisher for the end-effector pose and joint states
//     ros::Publisher pose_pub = nh.advertise<geometry_msgs::Pose>("/ee_pose", 10);
//     ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/joint_states", 10);

//     // TF2 Buffer and Listener
//     tf2_ros::Buffer tfBuffer;
//     tf2_ros::TransformListener tfListener(tfBuffer);

//     // Initialize target pose
//     target_pose.position.x = 0.5;
//     target_pose.position.y = 0.0;
//     target_pose.position.z = 0.3;
//     target_pose.orientation.w = 1.0; // Identity quaternion

//     ros::Rate rate(100); // Control loop rate

//     while (ros::ok()) {
//         try {
//             // Get current end-effector pose using TF2
//             geometry_msgs::TransformStamped transformStamped =
//                 tfBuffer.lookupTransform("arm_link_0", "arm_link_0", ros::Time(0));

//             geometry_msgs::Pose current_pose;
//             current_pose.position.x = transformStamped.transform.translation.x;
//             current_pose.position.y = transformStamped.transform.translation.y;
//             current_pose.position.z = transformStamped.transform.translation.z;
//             current_pose.orientation = transformStamped.transform.rotation;

//             // Compute pose error
//             double position_error, orientation_error;
//             computePoseError(current_pose, target_pose, position_error, orientation_error);

//             // Stop condition
//             if (position_error < 0.01) {
//                 ROS_INFO("Target pose reached!");
//                 break;
//             }

//             // Proportional control logic (for demonstration)
//             sensor_msgs::JointState joint_states;
//             joint_states.header.stamp = ros::Time::now();

//             // Example joint names (adjust according to your robot)
//             joint_states.name = {"arm_joint_1", "arm_joint_2", "arm_joint_3", "arm_joint_4", "arm_joint_5",
//                                  "gripper_finger_joint_l", "gripper_finger_joint_r"};

//             // Example simple control - adjust joint positions to reduce error
//             // (In practice, use inverse kinematics to compute precise adjustments)
//             joint_states.position = {0.1 * position_error, 0.1 * position_error, 0.1 * position_error,
//                                       0.1 * position_error, 0.1 * position_error, 0.0, 0.0};

//             // Publish joint states
//             joint_states_pub.publish(joint_states);
//             ROS_INFO("Publishing joint states to reduce error: position_error = %.3f", position_error);

//             // Publish current pose for visualization/debugging
//             pose_pub.publish(current_pose);

//         } catch (tf2::TransformException& ex) {
//             ROS_WARN("Could not transform: %s", ex.what());
//         }

//         ros::spinOnce();
//         rate.sleep();
//     }

//     return 0;
// }
