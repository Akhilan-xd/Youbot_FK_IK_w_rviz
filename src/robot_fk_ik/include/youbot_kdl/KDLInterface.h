/*
Name: KDLInterface.h
Author(s):
Date:
Assignment:
Copyright:
*/

#ifndef KDLINTERFACE_H_
#define KDLINTERFACE_H_

#include <iostream>
using namespace std;

#include <vector>
#include <math.h>
#include <Eigen/Core>
#include <kdl/tree.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <urdf_parser/urdf_parser.h>
// #include <urdf_model/model.h>
#include <kdl/frames.hpp>
#include <kdl/frames_io.hpp>
#include <kdl/chainiksolverpos_lma.hpp>


class KDLInterface{
private:
    double d2r(double v);
    double r2d(double v);
    KDL::Chain chain_dh;
    KDL::Chain chain_urdf;
    KDL::Tree youbot_tree; 
    int nr_joints;
    int nr_joints_urdf;
    KDL::Frame pos;

public:
    KDLInterface();
    ~KDLInterface();
    bool iksolver(KDL::Frame &pos, double joint_positions[]);
    bool fksolver(double joint_positions[], KDL::Frame &pos);
    bool fksolver(double joint_positions[], KDL::Frame &pos, int link);

};


#endif /* KDLINTERFACE_H_*/
