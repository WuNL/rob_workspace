/*
*  Software License Agreement (BSD License)
*  Copyright (c) 2013, Intelligent Robotics Lab, DLUT.
*  All rights reserved.
*  Author:¡­¡­
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Intelligent Robotics Lab nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*/

#include <sys/types.h>
#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ros/ros.h"
#include "dlut_move_base/Velocity.h"
#include "dlut_move_base/Height.h"
#include "dlut_move_base/Laser.h"
#include <signal.h>
#include <termios.h>
#include "time.h"
#include <sys/file.h>
#include <pthread.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"

#define SERVPORT 3333
#define BACKLOG 10
#define MAX_CONNECT_NO 10
#define MAXDATASIZE 20
#define MAXBUF 2



class server
{

public:
	server();
	~server();
	void run();

private:

	int file_fd;
	int nwrite,nread;
	int freq,pulse;
	bool stop,height_flag;
	double linear_, angular_;
	const double l_scale_, a_scale_;
	char buff_write[2],buff_read[2];
	bool obstacle_present,obstacle_obvious,send_flag;
	int kfd;
  dlut_move_base::Velocity vel;
	dlut_move_base::Height height;


  struct sockaddr_in server_sockaddr,client_sockaddr;
  int recvbytes,sendbytes;
  socklen_t sin_size;
  int sockfd,client_fd;
  char buf[MAXDATASIZE];
  fd_set rfds;//define a file describer set
  int retval,maxfd;

  struct timeval tv;
	ros::NodeHandle n;
	ros::Publisher velocity_pub;
	ros::Publisher is_run_pub1_,is_run_pub2_,height_pub;
  //std_msgs::Bool is_motor_run_; 
	dlut_move_base::Laser laser_motor; 
	
	int num,freq_hokuyo;

};

server::server():l_scale_(0.1),a_scale_(0.1),freq(1000),pulse(0),stop(false),height_flag(false),num(0),freq_hokuyo(0)
{
	ROS_INFO("into \n");
	vel.linear = 0.0;
	vel.angular = 0.0;
	

	  /*create a socket*/
  if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
  {
    perror("socket");
    exit(1);
  }

  ROS_INFO("socket success!,sockfd = %d\n",sockfd);
  server_sockaddr.sin_family = AF_INET;
  server_sockaddr.sin_port = htons(5678);
  server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bzero(&(server_sockaddr.sin_zero),8);

  /*°ó¶šº¯Êýbind*/
  if (bind(sockfd,(struct sockaddr*)&server_sockaddr,sizeof(struct sockaddr)) == -1)
  {
    perror("bind");
    exit(1);
  }
  ROS_INFO("bind success!\n");

  /*µ÷ÓÃlisten º¯Êý*/
  if(listen(sockfd,BACKLOG) == -1)
  {
    perror("listen");
    exit(1);
  }
  ROS_INFO("listening...\n");

		
	velocity_pub = n.advertise<dlut_move_base::Velocity>("/turtle1/command_velocity", 1);
  is_run_pub1_ = n.advertise<dlut_move_base::Laser>("is_run", 1000);
  is_run_pub2_ = n.advertise<dlut_move_base::Laser>("is_run_pch", 1000);
	height_pub = n.advertise<dlut_move_base::Height>("height_control",1000);
	buf[MAXDATASIZE] = '\0';
  sin_size  = sizeof(struct sockaddr); 
  client_fd = accept(sockfd,(struct sockaddr*)&client_sockaddr,&sin_size);
  if(client_fd == -1)
  {
    perror("accept");
    exit(1);
  }
  //ROS_INFO("server: got connection from %s,port %d,socket %d\n",inet_ntoa(server_sockaddr.sin_addr),
  //ntohs(server_sockaddr.sin_port),client_fd);

}

server::~server()
{
	close(client_fd); 
	close(sockfd);
}

void server::run()
{
  while(1)
	{
	  /*receive the message from the connection*/
	  bzero(buf,MAXDATASIZE);
	  recvbytes = recv(client_fd,buf,20,0);

	  if (recvbytes == -1 || recvbytes == 0)
	  {
	    ROS_INFO("\nquit\n");
	    return;
	  }

	  ROS_INFO("received a connection : %s\n",buf);
	  ROS_INFO("received bytes: %d\n",recvbytes);

		linear_ = angular_ = 0.0;
		bool is_control_command = false;//is control command or not
    bool is_data_command = false; 
		height_flag = false;
		stop = false;
	  //the robot stopped moving or not
		bool is_stop_move = 0;

		//the robot begin getting the laser data or not
		int begin_get_data = 0; 

		//the robot stop getting the laser data or not
		int stop_get_data = 0;  
		ROS_INFO("buf==%s",buf);
	  switch(buf[0])
	  {
	    case 'L':
	    {  
        ROS_DEBUG("LEFT");
        angular_ = 1.0;
        is_control_command = true;
	      break;
	    }
	    case 'R':
	    {            
        ROS_DEBUG("RIGHT");
        angular_ = -1.0;
        is_control_command = true;
	      break;
	    } 
	    case 'B':
	    {
        ROS_DEBUG("DOWN");
        linear_ = -1.0;
        is_control_command = true;
	      break;
	    }
	    case 'F':
	    {
        ROS_DEBUG("UP");
        linear_ = 1.0;
        is_control_command = true;
	      break;
	    }
	    case 'T':
	    {
				ROS_DEBUG("STOP");
				is_stop_move = 1;
        is_control_command = true;
	      break;
	    }
      case '0':
			{
				ROS_INFO("BEGIN");
				begin_get_data = 1;
        is_data_command = true;
				sscanf(buf,"0 %d %d",&num,&freq_hokuyo);
				ROS_INFO("%d\t%d",num,freq_hokuyo);
				laser_motor.num = num;
				laser_motor.freq = freq_hokuyo;	
        break;
			}
			case 'N':
			{
				ROS_DEBUG("END");
				stop_get_data = 1;
        is_data_command = true;
        break;
			}


			//+
			case 'q':
			{
				ROS_DEBUG("q");
				pulse = 159;
        height_flag = true;
        break;
			}
			case 'w':
			{
				ROS_DEBUG("w");
				pulse = 159*2;
        height_flag = true;
        break;
			}
			case 'e':
			{
				ROS_DEBUG("e");
				pulse = 159*5;
        height_flag = true;
        break;
			}
			case 'r':
			{
				ROS_DEBUG("r");
				pulse = 159*10;
        height_flag = true;
        break;
			}
			case 't':
			{
				ROS_DEBUG("t");
				pulse = 159*20;
        height_flag = true;
        break;
			}
			case 'y':
			{
				ROS_DEBUG("y");
				pulse = 159*30;
        height_flag = true;
        break;
			}
			case 'u':
			{
				ROS_DEBUG("u");
				pulse = 159*50;
        height_flag = true;
        break;
			}

			//-
			case 'a':
			{
				ROS_DEBUG("a");
				pulse = -159;
        height_flag = true;
        break;
			}
			case 's':
			{
				ROS_DEBUG("s");
				pulse = -159*2;
        height_flag = true;
        break;
			}
			case 'd':
			{
				ROS_DEBUG("d");
				pulse = -159*5;
        height_flag = true;
        break;
			}
			case 'f':
			{
				ROS_DEBUG("f");
				pulse = -159*10;
        height_flag = true;
        break;
			}
			case 'g':
			{
				ROS_DEBUG("g");
				pulse = -159*20;
        height_flag = true;
        break;
			}
			case 'h':
			{
				ROS_DEBUG("h");
				pulse = -159*30;
        height_flag = true;
        break;
			}
			case 'j':
			{
				ROS_DEBUG("j");
				pulse = -159*50;
        height_flag = true;
        break;
			}

	    default:
	    break;	
	  }
    vel.angular = vel.angular + a_scale_*angular_;
    vel.linear = vel.linear + l_scale_*linear_;

    //add the following two if in case the function gcvt convert 0 to a numner very near to 0
    if(vel.angular > -0.001 && vel.angular < 0.001)
    {
      vel.angular = 0.0;	
    }

    if(vel.linear > -0.001 && vel.linear < 0.001)//the robot runs faster at 0.05 than 								at 0.1,it's abnormal
    {
      vel.linear = 0.0;	
    }

    if(is_stop_move == 1)
    {
      vel.angular = 0.0;
      vel.linear = 0.0;	
      is_stop_move = 0;	
    }

    if(begin_get_data == 1)
    {
      laser_motor.is_rotate = true;
      begin_get_data = 0;
    }

    if(stop_get_data == 1)
    {
      laser_motor.is_rotate = false;
			laser_motor.num = 0;
			laser_motor.freq = 0;
      stop_get_data = 0;
    }

    if(is_control_command == true)//is control command, so publish it
    {
      velocity_pub.publish(vel); 
      is_control_command = false;
    }

    if(is_data_command == true)
    {
      is_run_pub1_.publish(laser_motor);//tell the motor under the sick to rotate
      is_run_pub2_.publish(laser_motor);//publish the signal to save the laser data or not
      is_data_command = false;
    }

		if(height_flag == true)
		{
			ROS_INFO("freq=%d\n",freq);
			height.freq = freq;
			height.pulse = pulse;
			height.stop = stop;
			height_pub.publish(height);
			stop = false;
			height_flag = false;
		}	
  }


 
	return;
}

int main(int argc, char **argv)
{
  ros::init(argc,argv,"server");
	server server;
	server.run();
  
  
	return 0;
}



