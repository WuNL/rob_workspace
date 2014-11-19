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

#include "net_transfor.h"
#include <queue>
#include "boost/thread.hpp"


#include<pcl/filters/voxel_grid.h>

#define PAI 3.1415926

typedef pcl::PointXYZ PointType;
typedef pcl::PointCloud<PointType> PCLPointCloud;
PCLPointCloud::Ptr final(new PCLPointCloud);//convert to PointCloud2 to publish
PCLPointCloud::Ptr final_filtered(new PCLPointCloud);//convert to PointCloud2 to publish
pcl::VoxelGrid<pcl::PointXYZ> sor;


using namespace std;
boost::mutex io_mutex;
void senddata(std::queue<pcl::PointCloud<pcl::PointXYZ> > *p_q)
{
    cout <<"in thread"<<endl;
    Net_transfor n1(0);
    pcl::PointCloud<pcl::PointXYZ> cloud_copy;
    while(ros::ok())
    {
        if(p_q->empty())
            continue;
        cloud_copy.clear();
        cout <<"p_q.size()="<<p_q->size()<<endl;
        {
            boost::mutex::scoped_lock lock(io_mutex);
            cloud_copy = p_q->front();
            p_q->pop();
        }
        n1.send(cloud_copy);
    }
    cout <<"ready to close send socket"<<endl;
    n1.close();
}

class PointCloudOdom
{
    public:
        PointCloudOdom();
        ~PointCloudOdom();

        void scanCallBack(const sensor_msgs::LaserScan &ls);
        void motorRotateStart(const std_msgs::Bool &is_run);
        void motorParamGet(const dlut_pc_odom::motor &motor_msg);
        void odomGet(const nav_msgs::Odometry &odom);

        geometry_msgs::Vector3 rpyGet(const tf::Quaternion &qua);
        geometry_msgs::Vector3 rpyGet(const geometry_msgs::Quaternion &qua);

        ros::NodeHandle nh_;

    private:
        ros::Publisher point_cloud2_pub_;//publish the PointCloud and PointCloud2 message

        ros::Subscriber laser_scan_sub_,rotate_start_sub_,motor_param_sub_,odom_sub_;

        std_msgs::Bool is_rotate_;//message which show the sick begin to rotate or not
        dlut_pc_odom::motor motor_param_;//motor's parameters
        sensor_msgs::PointCloud odom_cloud_;//the point cloud corrected by odom

        ros::Time time_begin_rotate_,time_end_rotate_;//the time which the sick begin to rotate and stop to rotate

        double angle_rotated_;//the angle which the sick rotated
        bool is_first_flag_;//whether the first data after the sick rotated
        unsigned int num_points_;//the points num of the cloud

        unsigned int laser_seq_;//the sequence number of the laser data
        unsigned int num_per_cloud_;//the scan number of one cloud
        unsigned int points_per_scan_;//the points number per scan


        tf::TransformListener odom_tf_listener_;
        geometry_msgs::Vector3 ypr_;//yaw,pitch,roll

        double alpha_,beta_,gamma_,length_;//the parameters of the hokuyo platform
        double h2p_a_,h2p_b_,h2p_c_,h2p_d_,h2p_e_,h2p_f_,h2p_g_,h2p_h_,h2p_i_;//hokuyo激光到云台变换矩阵R中的值
        double p2r_a_,p2r_b_,p2r_c_,p2r_d_,p2r_e_,p2r_f_,p2r_g_,p2r_h_,p2r_i_;//云台到机器人变换矩阵R中的值
        double t_h2p_a_,t_h2p_b_,t_h2p_c_;//云台到激光的平移矩阵T

        bool is_first_circle_;//是否是第一圈激光数据
        bool is_local_map;
        bool start_get_data;
        bool marker0,marker1;
        bool first_circle;
        bool first_circle1;
        double motorSpeed_rad;
        std::queue<pcl::PointCloud<pcl::PointXYZ> > point_queue;
        PointType point2_;//save a temporary point
};

PointCloudOdom::PointCloudOdom():is_local_map(true)
{
    laser_scan_sub_ = nh_.subscribe("scan", 1000, &PointCloudOdom::scanCallBack,this);
    rotate_start_sub_ = nh_.subscribe("is_run_pch", 1, &PointCloudOdom::motorRotateStart,this);
    motor_param_sub_ = nh_.subscribe("motor_param", 1000, &PointCloudOdom::motorParamGet,this);
    odom_sub_ = nh_.subscribe("odom", 1000, &PointCloudOdom::odomGet,this);
    point_cloud2_pub_ = nh_.advertise<PCLPointCloud> ("hokuyo_point_cloud2", 1);
    //point_stamp_pub = nh_.advertise<geometry_msgs::PointStamped>("point_stamp", 1000);

    is_rotate_.data = false;
    angle_rotated_ = 0.0;

    is_first_flag_ = false;

    num_points_ = 0;
    laser_seq_ = 0;



    alpha_ = 0.0095;
    beta_ = 0.0017;
    gamma_ = -0.0262;
    length_ = -0.0040;

    h2p_a_ = cos(beta_)*cos(gamma_) - sin(alpha_)*sin(beta_)*sin(gamma_);
    h2p_b_ = -cos(beta_)*sin(gamma_) - sin(alpha_)*sin(beta_)*cos(gamma_);
    h2p_c_ = -cos(alpha_)*sin(beta_);
    h2p_d_ = cos(alpha_)*sin(gamma_);
    h2p_e_ = cos(alpha_)*cos(gamma_);
    h2p_f_ = -sin(alpha_);
    h2p_g_ = sin(beta_)*cos(gamma_) + sin(alpha_)*cos(beta_)*sin(gamma_);
    h2p_h_ = -sin(beta_)*sin(gamma_) + sin(alpha_)*cos(beta_)*cos(gamma_);
    h2p_i_ = cos(alpha_)*cos(beta_);

    p2r_a_ = 0.999942368044831;   p2r_b_ = 0.00616103270670958;   p2r_c_ = 0.00879217065821694;
    p2r_d_ = -0.00613654752375238;p2r_e_ = 0.999977225469970;     p2r_f_ = -0.00280915038216528;
    p2r_g_ = -0.00880927768804484;p2r_h_ = 0.00275503491225531;   p2r_i_ = 0.999957402297342;

    t_h2p_a_ = -0.143284347080846;t_h2p_b_ = -0.00961421703449155;t_h2p_c_ = 0.575167371824827;

    is_first_circle_ = true;
    start_get_data = false;
    marker0 = true;
    marker1 = true;
    first_circle = true;
    first_circle1 = true;
    boost::thread send_data(boost::bind(senddata,&point_queue));
}

PointCloudOdom::~PointCloudOdom()
{

}

void PointCloudOdom::scanCallBack(const sensor_msgs::LaserScan &ls)
{
    static double t_detect =0.0;
    static double t =0.0;
    static double t_pre =0.0;
    points_per_scan_ = (ls.angle_max - ls.angle_min)/ls.angle_increment;
    motorSpeed_rad = 2*PAI*motor_param_.motor_freq.data/motor_param_.num_of_pulse_per_circle.data;
    if(is_first_flag_)
    {
        points_per_scan_ = (ls.angle_max - ls.angle_min)/ls.angle_increment;
        motorSpeed_rad = 2*PAI*motor_param_.motor_freq.data/motor_param_.num_of_pulse_per_circle.data;
        is_first_flag_ = false;
        final->clear();
        final->header.stamp = ros::Time::now().toSec();
        final->header.frame_id = "pch_frame";
        return;
    }
    double r_begin = ls.ranges[0];
    double r_end = ls.ranges[1078];

    if((r_begin<0.21) && marker0)
    {
        cout <<"detect marker0,point_queue.size="<<point_queue.size()<<endl;
        t_detect = ros::Time::now().toSec();
        if(first_circle == false)
        {
            boost::mutex::scoped_lock lock(io_mutex);
            sor.setInputCloud(final);
            sor.setLeafSize(0.02f,0.02f,0.02f);
            sor.filter(*final_filtered);
            cout <<"ready to send "<<final_filtered->points.size()<<endl;
            point_queue.push(*final_filtered);
            final_filtered->clear();
            final->clear();
            final->header.stamp = ros::Time::now().toSec();
            final->header.frame_id = "pch_frame";
        }
        first_circle = false;
        start_get_data = true;
        marker0 = false;
    }
    if(r_begin > 0.22)
        marker0 = true;
    if((r_end<0.21) && marker1)
    {
        cout <<"detect marker1,point_queue.size="<<point_queue.size()<<endl;
        boost::mutex::scoped_lock lock(io_mutex);
        sor.setInputCloud(final);
        sor.setLeafSize(0.02f,0.02f,0.02f);
        sor.filter(*final_filtered);
        cout <<"ready to send "<<final_filtered->points.size()<<endl;
        point_queue.push(*final_filtered);
        final_filtered->clear();
        final->clear();
        final->header.stamp = ros::Time::now().toSec();
        final->header.frame_id = "pch_frame";
        /*
           t_detect = ros::Time::now().toSec();
        //
        cout <<"ready to send "<<final->points.size()<<endl;
        boost::mutex::scoped_lock lock(io_mutex);

        final->clear();
        final->header.stamp = ros::Time::now().toSec();
        final->header.frame_id = "pch_frame";
        */
        marker1 = false;
        first_circle1 = false;
    }
    if(r_end >0.22)
        marker1 = true;
    t = (ros::Time::now().toSec()-t_detect);
    double t_ =t;
    double t_pre_ = t_pre;
    /*
       if(((t_pre_<1.41) && (t_ >1.41)) && (first_circle1 == false))
       {
       cout <<"time 1\n";
       cout <<"ready to send "<<final->points.size()<<endl;
       boost::mutex::scoped_lock lock(io_mutex);
       point_queue.push(*final);
       final->clear();
       final->header.stamp = ros::Time::now().toSec();
       final->header.frame_id = "pch_frame";
       }
       if(((t_pre_<2.83) && (t_ >2.83)) && (first_circle1 == false))
       {
       cout <<"time 2\n";
       cout <<"ready to send "<<final->points.size()<<endl;
       boost::mutex::scoped_lock lock(io_mutex);
       point_queue.push(*final);
       final->clear();
       final->header.stamp = ros::Time::now().toSec();
       final->header.frame_id = "pch_frame";
       }
       */
    /*
       if(((t_pre_<3.09) && (t_ >3.09)) && (first_circle1 == false))
       {
       cout <<"time 3\n";
       boost::mutex::scoped_lock lock(io_mutex);
       point_queue.push(*final);
       final->clear();
       final->header.stamp = ros::Time::now().toSec();
       final->header.frame_id = "pch_frame";
       }
       */
    if(start_get_data)
    {
        static double t0 = ros::Time::now().toSec();

        angle_rotated_ = (ros::Time::now().toSec()-t0)*motorSpeed_rad;

        tf::StampedTransform transform;
        try
        {
            odom_tf_listener_.lookupTransform("odom", "base_link", ros::Time(0), transform);
        }
        catch (tf::TransformException ex)
        {
            ROS_ERROR("TransformException:%s",ex.what());
        }

        double transform_x = transform.getOrigin().x();
        double transform_y = transform.getOrigin().y();
        double transform_z = transform.getOrigin().z();
        double transform_th = rpyGet(transform.getRotation()).z;//获取里程计变换

        /*double transform_x = 0.0;

          double transform_y = 0.0;
          double transform_z = 0.0;
          double transform_th = 0.0;//获取里程计变换*/
        //double transform_rotation_x = transform.getRotation().x();
        //double transform_rotation_y = transform.getRotation().y();
        //double transform_rotation_z = transform.getRotation().z();
        //double transform_rotation_w = transform.getRotation().w();

        /*计算里程计原始数据时间戳start*/
        ros::Time now_range = ros::Time::now();
        double time_stamp = (now_range-time_begin_rotate_).toSec();
        /*计算里程计原始数据时间戳end*/


        for(unsigned int i = 0;i < points_per_scan_; i++)
        {
            if(ls.ranges[i]>5)
                continue;
            //计算激光坐标系下激光点坐标,激光坐标系下激光扫描角度为：
            double theta = ls.angle_min + i*ls.angle_increment;
            //激光坐标系下激光点坐标为:
            double x = ls.ranges[i]*cos(theta);
            double y = ls.ranges[i]*sin(theta);
            double z = 0;

            //将激光坐标系进行旋转以后为(乘以旋转矩阵R)：P_ = R*P
            double rx = h2p_a_*x + h2p_b_*y + h2p_c_*z;
            double ry = h2p_d_*x + h2p_e_*y + h2p_f_*z;
            double rz = h2p_g_*x + h2p_h_*y + h2p_i_*z;

            //将激光坐标系转换为云台坐标系Pyuntai
            double yt_x = -ry*cos(angle_rotated_) + (rz + length_)*sin(angle_rotated_);
            double yt_y = -ry*sin(angle_rotated_) - (rz + length_)*cos(angle_rotated_);
            double yt_z = rx;

            //从云台坐标系转换到机器人坐标系:Probot=RZ*Pyuntai+T
            double x_robot = p2r_a_*yt_x + p2r_b_*yt_y + p2r_c_*yt_z + t_h2p_a_;
            double y_robot = p2r_d_*yt_x + p2r_e_*yt_y + p2r_f_*yt_z + t_h2p_b_;
            double z_robot = p2r_g_*yt_x + p2r_h_*yt_y + p2r_i_*yt_z + t_h2p_c_;
            //机器人运动过程中，还需要将点云平移后绕z轴旋转方可

            //先绕z轴旋转，旋转角度是机器人转角
            double x_end = x_robot*cos(transform_th) - y_robot*sin(transform_th);
            double y_end = x_robot*sin(transform_th) + y_robot*cos(transform_th);
            double z_end = z_robot;

            //再平移
            x_end += transform_x;
            y_end += transform_y;
            z_end += transform_z;

            point2_.x = x_end;
            point2_.y = y_end;
            point2_.z = z_end;
            //point2_.rgb = ...;//pointcloud has no colour at the present
            final->points.push_back(point2_);
        }
    }
    t_pre = t;
}

void PointCloudOdom::odomGet(const nav_msgs::Odometry &odom)
{
    if(is_rotate_.data == true)
    {
        //double yaw = tf::getYaw(odom.pose.pose.orientation);
        double yaw = rpyGet(odom.pose.pose.orientation).z;
        ros::Time now = ros::Time::now();
        double time_stamp = (now-time_begin_rotate_).toSec();
        //ROS_INFO("yaw = %f.",yaw);
        //odom_data_<<time_stamp<<" "<<odom.twist.twist.linear.x<<" "<< odom.twist.twist.angular.z<<" "<<odom.pose.pose.position.x<<" "<<odom.pose.pose.position.y<<" "<<yaw<<"\n";
    }
}

void PointCloudOdom::motorRotateStart(const std_msgs::Bool &is_run)
{
    is_rotate_.data = is_run.data;
    if(is_rotate_.data == true)
    {
        time_begin_rotate_ = ros::Time::now();//电机开始转动，开始存激光数据，设个起始时间
    }
    else
    {
        time_end_rotate_ = ros::Time::now();//电机停止转动，停止存激光数据，设个结束时间
    }
}

void PointCloudOdom::motorParamGet(const dlut_pc_odom::motor &motor_msg)
{
    motor_param_.motor_freq.data = motor_msg.motor_freq.data;
    motor_param_.num_of_pulse_per_circle.data = motor_msg.num_of_pulse_per_circle.data;
    //time_sick_per_circle = motor_param_.num_of_pulse_per_circle.data/motor_param_.motor_freq.data;//激光每转一圈需要的时间
    is_first_flag_ = true;
}

geometry_msgs::Vector3 PointCloudOdom::rpyGet(const tf::Quaternion &qua)
{
    double x = qua.x();
    double y = qua.y();
    double z = qua.z();
    double w = qua.w();

    geometry_msgs::Vector3 vec;
    vec.x = atan2(2*(w*x + y*z),1 - 2*(x*x + y*y));//from -pai to pai
    vec.y = asin(2*(w*y - z*x));		//from -pai/2 to pai/2
    vec.z = atan2(2*(w*z + x*y),1 - 2*(y*y + z*z));//from -pai to pai

    return vec;
}

geometry_msgs::Vector3 PointCloudOdom::rpyGet(const geometry_msgs::Quaternion &qua)
{
    double x = qua.x;
    double y = qua.y;
    double z = qua.z;
    double w = qua.w;

    geometry_msgs::Vector3 vec;
    vec.x = atan2(2*(w*x + y*z),1 - 2*(x*x + y*y));//from -pai to pai
    vec.y = asin(2*(w*y - z*x));		//from -pai/2 to pai/2
    vec.z = atan2(2*(w*z + x*y),1 - 2*(y*y + z*z));//from -pai to pai

    return vec;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_hash_v1");

    PointCloudOdom pch;

    ros::spin();

    return 0;
}
