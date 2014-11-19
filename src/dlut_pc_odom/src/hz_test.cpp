/*********************************************************************
 * Software License Agreement (BSD License)
 * Copyright (c) 2013, Intelligent Robotics Lab, DLUT.
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
 *     * Neither the name of the Willow Garage, Inc. and Intelligent Robotics 
 *        Lab, DLUT nor the names of its contributors may be used to endorse or
 *       promote products derived from this software without specific prior written 
 *       permission.
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
*********************************************************************/

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <dlut_pc_odom/motor.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt32.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Vector3.h>

//#include <geometry_msgs/Point32.h>

#include <iostream>
#include <fstream>
#include <math.h>

#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>

#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include "pcl/io/pcd_io.h"

#define PAI 3.1415926

typedef pcl::PointXYZRGB PointType;
typedef pcl::PointCloud<PointType> PCLPointCloud;
PCLPointCloud::Ptr final(new PCLPointCloud);//convert to PointCloud2 to publish

class PointCloudOdom
{
public:
  PointCloudOdom();
  ~PointCloudOdom();

  void scanCallBack(const sensor_msgs::LaserScan &ls);



  ros::NodeHandle nh_;

private:


  ros::Subscriber laser_scan_sub_;

  double t0;

};

PointCloudOdom::PointCloudOdom()
{
  laser_scan_sub_ = nh_.subscribe("scan", 1000, &PointCloudOdom::scanCallBack,this);
  t0 = ros::Time::now().toSec();	
  
}

PointCloudOdom::~PointCloudOdom()
{

}

void PointCloudOdom::scanCallBack(const sensor_msgs::LaserScan &ls)
{
  double t1 = ros::Time::now().toSec();	
  static int i = 0;
  i++;
  std::cout<<"i=\t"<<i<<"\tspent time="<<(t1-t0)<<std::endl;
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "hz_test");

  PointCloudOdom pch;

  ros::spin();
  
  return 0;
}
