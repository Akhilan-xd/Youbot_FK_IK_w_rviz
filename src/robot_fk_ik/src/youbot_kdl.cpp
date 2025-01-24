/*
Name: youbot_kdl.cpp
Author(s):
Date:
Assignment:
Copyright:
*/

#include <youbot_kdl/KDLInterface.h>

int main(){
    KDLInterface solver;
    KDL::Frame pos;
    bool flag;

    //candle position
    double positions[5]={
        2.9496, 1.13446, -2.54818, 1.78896, 2.93075
    };
    
    solver.fksolver(positions,pos);
    solver.fksolver(positions,pos,3);
    solver.iksolver(pos,positions);

    return 0;
}
