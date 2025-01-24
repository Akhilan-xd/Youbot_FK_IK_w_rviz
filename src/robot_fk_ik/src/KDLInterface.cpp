/*
Name: KDLInterface.cpp
Author(s): Akhilan Ashokan
Date: 28/11/2024
Assignment: 04
Copyright: HBRS_RM_24-25
*/
#include "youbot_kdl/KDLInterface.h"

KDLInterface::KDLInterface(){
	double offset[5] = {d2r(-169),d2r(-65),d2r(151),d2r(-102.5),d2r(-165)};

	//Use your DH parameters here!
	/** 
	 * See example in:
	 * https://github.com/orocos/orocos_kinematics_dynamics/blob/master/orocos_kdl/tests/solvertest.cpp 
	 * code lines: 105-121. 
	*/
	using namespace KDL;
	using namespace std;

	KDL::Chain chain_dh;
	KDL::Chain chain_urdf;
	/* 
	Following is the function signature for DH_Craig1989:

	Frame Frame::DH_Craig1989(double a,double alpha,double d,double theta)
	*/

	// Base Joint --> Fixed --> Data's are as per the URDF || NOTE: This not urdf, this is DH parameters.
	chain_dh.addSegment(Segment(Joint(Joint::None), Frame::DH_Craig1989(0.1430, d2r(0), 0.0460, d2r(0))));
	// Joint 1
	chain_dh.addSegment(Segment(Joint(Joint::RotZ), Frame::DH_Craig1989(0.0240, d2r(0), 0.0960, d2r(170))));
	// Joint 2
	chain_dh.addSegment(Segment(Joint(Joint::RotZ), Frame::DH_Craig1989(0.0330, d2r(0), 0.0190, d2r(0))));
	// Joint 3
	chain_dh.addSegment(Segment(Joint(Joint::RotZ), Frame::DH_Craig1989(0.0, d2r(0), 0.1550, d2r(0))));
	// Joint 4
	chain_dh.addSegment(Segment(Joint(Joint::RotZ), Frame::DH_Craig1989(0.0, d2r(0), 0.1350, d2r(0))));
	// Joint 5
	chain_dh.addSegment(Segment(Joint(Joint::RotZ), Frame::DH_Craig1989(-0.0020, d2r(0), 0.1300, d2r(167.50))));
	
	// We have successfully created the chain. Now we can get the number of joints. 

	nr_joints = chain_dh.getNrOfJoints();

	// Print the number of joints
	cout << "Number of Joints using the DH parameters: " << nr_joints << endl;

	// - - - - - - - - - - - - - - - - - - - - - - - - - Using urdf_files - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //	

<<<<<<< HEAD
	Tree youbot_tree;
	if (!kdl_parser::treeFromFile("/home/akhilan/Downloads/RM_TA_WS_24/24_25 ASSGN_04_Feedback/robot-manipualtion-ws-2425-Akhilan-xd/src/robot/urdf/youbot_arm_only.urdf",youbot_tree)){
=======
	KDL::Tree youbot_tree;
	if (!kdl_parser::treeFromFile("/home/akhilan/Downloads/robot-manipualtion-ws-2425-Akhilan-xd/urdf/youbot_arm_only.urdf",youbot_tree)){
>>>>>>> e703913f1da2ecf7b58860e969b3b61210c628ff
		std::cout << "Oops!!!\n";
	}


	// In the urdf arm_only there are 6 links starting from 0 - 5(6)

	std::string base_link = "arm_link_0";
	std::string end_link = "arm_link_5";

	youbot_tree.getChain(base_link,end_link,chain_urdf);
	// getting the number of joints in the urdf file 
	nr_joints_urdf	 = chain_urdf.getNrOfJoints();
	cout<<"The number of joints from urdf: "<<nr_joints_urdf<<endl;

	



}

KDLInterface::~KDLInterface(){

}

double KDLInterface::d2r(double v) {
	return v / 180 * M_PI;
}

//rad to degree

double KDLInterface::r2d(double v) {
	return v * 180 / M_PI;
}
/*
The following function is used to convert a KDL::Frame to a homogeneous transformation matrix.
*/
void FrameToHomogeneous(const KDL::Frame& frame, double H[4][4]) {
    // Extract rotation matrix
    const KDL::Rotation& R = frame.M;
    const KDL::Vector& t = frame.p;

    // Fill in the homogeneous transformation matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            H[i][j] = R(i, j); // Rotation part
        }
        H[i][3] = t[i]; // Translation part
    }

    // Set the last row
    H[3][0] = 0.0;
    H[3][1] = 0.0;
    H[3][2] = 0.0;
    H[3][3] = 1.0;
}


bool KDLInterface::fksolver(double joint_positions[], KDL::Frame &pos){
	// From base to tooltip
	/**
	 * See example in:
	 * http://www.orocos.org/kdl/examples
	*/
		//From base to end effector
	//From base to end effector
	// 1. Creating a solver based on the kinematic chain
	KDL::ChainFkSolverPos_recursive fksolver = KDL::ChainFkSolverPos_recursive(chain_dh);
	// cout << chain_dh.getNrOfJoints() << endl;
	// 2. Creating a joint array 
	KDL::JntArray jointpositions = KDL::JntArray(nr_joints);

	
	// std::cout<<"The joint positions are1: "<<joint_positions<<std::endl;  // it should give me a address boz it  is not in the for loop`
	
	// 3. Assigning values to the joint array which we add
	for(unsigned int i=0;i<nr_joints;i++){
        jointpositions(i)= joint_positions[i];
		// std::cout<<"jointpositions"<<i+1<<":\t"<<jointpositions(i)<<std::endl; // jointpositions are printing correctly
	}
	// 4. Creating a frame which will contain the pos
		// which is already done in the youbot_kdl.cpp
		
	// 5. Calculating the fk pos

	fksolver.JntToCart(jointpositions,pos);
	
	// the loop below checks the transformation of the Jnt to Cart has taken place

	/*if(kinematics_status>0){
		printf("hey\n");
		// cout<<kinematics_status<<std::endl;

		// return true;
	}
	else{
		printf("\nouch!!\n");
	}*/
	cout<<"\n\nThe joint position obtained from the DH_parameters are: \n"<<pos<<endl;

	// What type is the pos?
	cout<<"\nWhat is pos?\t-->"<<typeid(pos).name()<<endl;
	/*
	Refer the link below to understand the type of pos:
	"https://docs.ros.org/en/jade/api/orocos_kdl/html/classKDL_1_1Frame.html"
	*/
	
	// Using the FrameToHomogeneous function to convert the pos to a homogeneous matrix
	// Just for understanfing the pos is a Frame type and we need to convert it to a 4x4 matrix.
	double homogenous_matrix[4][4];
	FrameToHomogeneous(pos, homogenous_matrix);
	// for proper formatting
	std::cout << "\nHomogeneous matrix: " << std::endl;
	for (int i = 0; i < 4; i++) {
		cout << "| ";
		for (int j = 0; j < 4; j++) {
			cout << homogenous_matrix[i][j] << " ";
		}
		cout << "|" << endl;
	}

	// - - - - - - - - - - - - - - - - - - - - - - - - Using urdf - - - - - - - - - - - - - - - - - - - - - - - -  //
	// get this following code to the next function that is fksolver //
	KDL::Frame pos_urdf;
	KDL::ChainFkSolverPos_recursive fk_solver_urdf(chain_urdf);

	fk_solver_urdf.JntToCart(jointpositions, pos_urdf);
	cout<<"\nThe joint positions obtained from the urdf: \n"<<pos_urdf<<endl;
	

	
	return 0;
}
bool KDLInterface::fksolver(double joint_positions[], KDL::Frame &pos, int link){
	//From base to some link
	KDL::ChainFkSolverPos_recursive fksolver(chain_dh);
	KDL::JntArray jointpositions = KDL::JntArray(nr_joints); 
	for(unsigned int i=0;i<link;i++){
        jointpositions(i)= joint_positions[i];
		// std::cout<<"jointpositions"<<i+1<<":\t"<<jointpositions(i)<<std::endl; // jointpositions are printing correctly
	}
	fksolver.JntToCart(jointpositions,pos,link);
	cout<<"\n\nThe joint position of the arm from DH "<<link<<": \n"<<pos<<endl;
	// cout<<"The link number: \t"<<link<<endl;
	
	double homogenous_matrix[4][4];
	FrameToHomogeneous(pos, homogenous_matrix);
	// with proper formatting
	std::cout << "\nHomogeneous matrix form: " << std::endl;
	for (int i = 0; i < 4; i++) {
		cout << "| ";
		for (int j = 0; j < 4; j++) {
			cout << homogenous_matrix[i][j] << " ";
		}
		cout << "|" << endl;
	}
	// // // - - - - - - - - - - - - - - - - - - - - - - - - Using urdf - - - - - - - - - - - - - - - - - - - - - - - -  //
	// KDL::ChainFkSolverPos_recursive fksolver_urdf(chain_urdf);
	// fksolver_urdf.JntToCart(jointpositions,pos,link);
	// cout<<"\nThe joint position of the arm from urdf "<<link<<": \n"<<pos<<endl;
	// cout<<"The link number from urdf: \t"<<link<<endl;
	return 0;
}

bool KDLInterface::iksolver(KDL::Frame &pos, double joint_positions[]){
	// From base to tooltip
	/**
	 * See example in:
	 * http://www.orocos.org/kdl/examples
	*/

	//From base to end effector
	KDL::JntArray initial_pos(5);
    initial_pos(0) = 0.0;
    initial_pos(1) = 0.0;
    initial_pos(2) = 0.0;
    initial_pos(3) = 0.0;
    initial_pos(4) = 0.0;

	//From base to end effector
	// 1. Creating a solver based on the kinematic chain
	KDL::ChainIkSolverPos_LMA iksolver = KDL::ChainIkSolverPos_LMA(chain_urdf);
	// 2. Creating a joint array 
	KDL::JntArray jointpositions = KDL::JntArray(nr_joints);
	// 3. Assigning values to the joint array which we add
	for(unsigned int i=0;i<nr_joints;i++){
		jointpositions(i)= joint_positions[i];
		// std::cout<<"jointpositions"<<i+1<<":\t"<<jointpositions(i)<<std::endl; // jointpositions are printing correctly
	}
	// 4. Creating a frame which will contain the pos
		// which is already done in the youbot_kdl.cpp
	// 5. Calculating the fk pos
	iksolver.CartToJnt(initial_pos,pos,jointpositions);
	// the loop below checks the transformation of the Jnt to Cart has taken place
	/*if(kinematics_status>0){
		printf("hey\n");
		// cout<<kinematics_status<<std::endl;

		// return true;
	}
	else{
		printf("\nouch!!\n");
	}*/
	// std::cout<<"\n\nThe joint position obtained from the urdf_parameters are: \n"<<KDL::JntArray jointpositions<<std::endl;
	// Declare the KDL::JntArray variable

	// Use the variable in cout to display its contents
	cout << "The joint positions are: \t";
	for (unsigned int i = 0; i < jointpositions.rows(); ++i) {
		cout << jointpositions(i) << " ";
		// converting radians to degrees
		cout << r2d(jointpositions(i)) << " ";
	}
	cout << endl;

	cout << "The joint positions in degrees are: \t";
	for (unsigned int i = 0; i < jointpositions.rows(); ++i) {
	// converting radians to degrees
		cout << r2d(jointpositions(i)) << " ";
	}
	cout << endl;
	return 0;
}