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

#include <sys/socket.h> 
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "time.h" 
#include <math.h>
#include <netinet/in.h>

#include <ros/ros.h> 
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include "dlut_move_base/Height.h"


#define DEFAULT_PORT 1
#define DEFAULT_BAUDRATE 19200
#define DEFAULT_DIRECTION 0 //counterclockwise
#define DEFAULT_FRE 760
#define DEFAULT_ANGEL 720
#define PAI 3.141592653
#define SCALE 3
#define DIAMETER 0.046
#define PULSE_PERCIRCLE 200

using namespace std;
class motor
{
	public:
	motor();
	~motor();
	void comCallBack(const dlut_move_base::Height &height);//send the control cmd to the port by Velocity
	int comInit();
  int openPort(int fd_, int comport);//open the serial port
  int setOpt(int fd_,int nspeed,int nbits,char nevent,int nstop);//config the serial port
  int operate(int,int);
	int stop();

	private:
	ros::NodeHandle n;
	ros::Subscriber sub_cmd_height;
  int port_,baudrate_;
	int fd_;
  int nwrite_; 
  double length;
  double num;
  double NUM;
  int num_pulse;
  double b;
  char command_buff_[30];	
  char buff[5];
  int buf;
  char motor_dir_;//indicate the rotating direction of the sick
};


motor::motor()
{
	comInit();
	sub_cmd_height = n.subscribe("height_control", 1000, &motor::comCallBack,this);
}

motor::~motor()
{
	close(fd_);
}

void motor::comCallBack(const dlut_move_base::Height &height)
{
	if(height.stop!=true)
	{
		operate(height.pulse,height.freq);
	}
	else
	{
		stop();
	}
}

int motor::stop()
{
  sprintf(command_buff_,"MS");//generate the control command
  //ROS_INFO("%s\n",command_buff_);
  nwrite_ = write(fd_,command_buff_,strlen(command_buff_));//send the control command to the serial port
	//ROS_INFO("nwrite==%d",nwrite_);
  if(nwrite_ < 0)
  {
    ROS_INFO("serial send data error!\n");	
		return 0;
  }
	memset(command_buff_,0,strlen(command_buff_));
  sprintf(command_buff_,"MU");//generate the control command
  //ROS_INFO("%s\n",command_buff_);
  nwrite_ = write(fd_,command_buff_,strlen(command_buff_));//send the control command to the serial port
	//ROS_INFO("nwrite==%d",nwrite_);
  if(nwrite_ < 0)
  {
    ROS_INFO("serial send data error!\n");	
		return 0;
  }
	memset(command_buff_,0,strlen(command_buff_));
	return 0;
}

int motor::operate(int num_pulse,int freq)
{
  ROS_INFO("pulse==%d\tfreq==%d\tfd_==%d\n",num_pulse,freq,fd_);
  motor_dir_='0';
  if (num_pulse<0) 
  {
    num_pulse= (-num_pulse);
    motor_dir_='1';
  }
  sprintf(command_buff_,"M%c%06d%06d",motor_dir_,freq,num_pulse);//generate the control command
  //ROS_INFO("%s\n",command_buff_);
  nwrite_ = write(fd_,command_buff_,strlen(command_buff_));//send the control command to the serial port
	//ROS_INFO("nwrite==%d",nwrite_);
  if(nwrite_ < 0)
  {
    ROS_INFO("serial send data error!\n");	
  }
  return 0;
}


int motor::comInit()
{
  int i;

  if((fd_ = openPort(fd_,DEFAULT_PORT)) < 0)
  {
    ROS_INFO("failed to setup the serial!");
    return 0;
  }

  if((i = setOpt(fd_,DEFAULT_BAUDRATE,8,'N',1)) < 0)
  {
    ROS_INFO("failed to setup the serial!");
    return 0;
  }

  ROS_INFO("the serial openned，setup the serial successed。the file operator = %d\n",fd_); 
  
  return 0;
}

int motor::setOpt(int fd_,int nspeed,int nbits,char nevent,int nstop)
{
  struct termios newtio,oldtio;

  //check the parameter of the serial port to see whether there is error or not
  if(tcgetattr(fd_,&oldtio) != 0)
  {
    ROS_INFO("failed to setup the serial，failed to save the serial value!");
    return -1;	
  }

  bzero(&newtio,sizeof(newtio));

  newtio.c_cflag |= CLOCAL | CREAD;
  newtio.c_cflag &= ~CSIZE;

  switch(nbits)
  {
    case 7:
      newtio.c_cflag |= CS7;
      break;
    case 8:
      newtio.c_cflag |= CS8;
      break;	
  }

  switch(nevent)
  {
    case 'O': 
      newtio.c_cflag |= PARENB;
      newtio.c_cflag |= PARODD;
      newtio.c_iflag |= (INPCK | ISTRIP);
      break;
    case 'E':
      newtio.c_iflag |= (INPCK | ISTRIP);
      newtio.c_cflag |= PARENB ;
      newtio.c_cflag &= ~ PARODD;
      break;
    case 'N':
      newtio.c_cflag &= ~ PARENB;
      break;		
  }

  //setup the baud rate
  switch(nspeed)
  {
    case 2400:
      cfsetispeed(&newtio,B2400);
      cfsetospeed(&newtio,B2400);
      break;		
    case 4800:
      cfsetispeed(&newtio,B4800);
      cfsetospeed(&newtio,B4800);
      break;	
    case 9600:
      cfsetispeed(&newtio,B9600);
      cfsetospeed(&newtio,B9600);
      break;	
    case 19200:
      cfsetispeed(&newtio,B19200);
      cfsetospeed(&newtio,B19200);
      break;	
    case 38400:
      cfsetispeed(&newtio,B38400);
      cfsetospeed(&newtio,B38400);
      break;
    case 57600:
      cfsetispeed(&newtio,B57600);
      cfsetospeed(&newtio,B57600);
      break;		
    case 115200:
      cfsetispeed(&newtio,B115200);
      cfsetospeed(&newtio,B115200);
      break;	
    case 460800:
      cfsetispeed(&newtio,B460800);
      cfsetospeed(&newtio,B460800);
      break;	
    default:
      cfsetispeed(&newtio,B9600);
      cfsetospeed(&newtio,B9600);
      break;		
  }

  //setup the stop bit
  if(nstop == 1)
    newtio.c_cflag &= ~ CSTOPB;
  else if(nstop == 2)
    newtio.c_cflag |= CSTOPB;
	
  //setup the waitting time and the minimum amount of the characters received 
  newtio.c_cc[VTIME] = 0;
  newtio.c_cc[VMIN] = 0;

  //deal with the characters which were not received.
  tcflush(fd_,TCIFLUSH);

  //activate the new serial setup
  if((tcsetattr(fd_,TCSANOW,&newtio)) != 0)
  {
    ROS_INFO("failed to activate the new serial setup!");
    return -1;
  }
	
  ROS_INFO("serial setup success!\n");

  return 0;
}


//open the serial port
int motor::openPort(int fd_, int comport)
{
  if(comport == 1)//port 1
  {
    ROS_INFO("test1");
    fd_ = open("/dev/ttyUSB0",O_RDWR|O_NOCTTY|O_NDELAY);
    
    if(-1  ==  fd_)
    {
      ROS_INFO("failed to open port 1!");
      return(-1);
    }
    ROS_INFO("test2");
  }
  else if(comport == 2)//port 2
  {
    fd_ = open("/dev/ttyUSB1",O_RDWR|O_NOCTTY|O_NDELAY);
    if(-1 == fd_)
    {
      ROS_INFO("failed to open port 2!");
      return(-1);
    }
  }
  else if(comport == 3)//port 3
  {
    fd_ = open("/dev/ttyUSB2",O_RDWR|O_NOCTTY|O_NDELAY);
	
    if(-1 == fd_)
    {
      ROS_INFO("failed to open port 3!");
      return(-1);
    }
  }

  if(fcntl(fd_,F_SETFL,0) < 0)
    ROS_INFO("fcntl failed!");
  else
    ROS_INFO("fcntl=%d.",fcntl(fd_,F_SETFL,0));

  if(isatty(STDIN_FILENO) == 0)
    ROS_INFO("standsrd input is not a terminal device.");
  else
    ROS_INFO("is a tty sucess.");

  ROS_INFO("the return value of the serial open function=%d，!=-1,indicates succeed to open the serial.",fd_);
	
  return fd_;
}


int main(int argc,char **argv)
{  
  ros::init(argc, argv, "motor_control");   
  motor mt;

  ros::spin();	
  
  return 0;
}
  
