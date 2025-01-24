[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/a4D75nab)
# youbot_kdl

Steps to build repository:
1. To install libkdl-parser: sudo apt-get install libkdl-parser-dev (It is a parser used to parse the existing KDL library in the given repo.)
2. From RM_Youbot_KDL_Assignment folder run: cmake -Bbuild <b>[this is one time activity after new files are added/created]</b>
3. To generate executable, from RM_Youbot_KDL_Assignment folder, run: cmake --build build [this should be run every time the code is updated/Changed]
4. To execute the file, from RM_Youbot_KDL_Assignment, run: ./build/youbot_kdl_node

Make use of the internet resources for understanding how to build the code.
- [How to use the DH Parameters](https://github.com/orocos/orocos_kinematics_dynamics/blob/master/orocos_kdl/tests/solvertest.cpp)
- [KDL:: Tree Class Reference](https://docs.ros.org/en/indigo/api/orocos_kdl/html/classKDL_1_1Tree.html)
- [Exmaple of using a KDL parser](https://robotics.stackexchange.com/questions/49286/how-to-use-the-kdl-parser)
- [dh_Carig1989Parameter_order](https://github.com/snrkiwi/orocos-kdl/blob/master/orocos_kdl/src/frames.cpp)
- [Perfect_Example for FK using DH_Craig1989](https://github.com/orocos/orocos_kinematics_dynamics/issues/268)
- [YouBot Documentation](https://www-home.htwg-konstanz.de/~bittel/LaborMobileRoboter/youBot_datenblatt_web_0514.pdf)
