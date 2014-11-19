/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <ros/ros.h>
#include <iostream>
#include "../include/pcdviewer/main_window.hpp"
#include <QVTKWidget.h>
#include <QMessageBox>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <vector>

#include <pcl/filters/statistical_outlier_removal.h>

//#include <pcl/registration/ndt.h>
#include <pcl/filters/passthrough.h>

#include <pcl/visualization/pcl_visualizer.h>
//#include <boost/thread/thread.hpp>
#include <pcl/registration/ia_ransac.h>
#include <eigen3/Eigen/Dense>

#include <boost/thread.hpp> 


#include <pcl/filters/voxel_grid.h>
//用于boost网络传输
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>


#include "net_transfor.h"
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace pcdviewer {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
	//viewer = new pcl::visualization::CloudViewer("Cloud Viewer by WuNL");
	//ui.gridLayout->addWidget(viewer);
	pcdwidget = new PointCloudWidget(this);
	ui.gridLayout_viewer->addWidget(pcdwidget);

}

void wait(int sec)
{
    boost::this_thread::sleep(boost::posix_time::seconds(sec));
}
MainWindow::~MainWindow() {
	delete pcdwidget;
}
void MainWindow::count(int id)
{
    while(1)
    {
    cout <<"id=\t"<<id<<endl;
    wait(1);
    
    }
}




void MainWindow::on_pushButton_opnefile_clicked()
{
	ROS_INFO("filecatkin");
	QString path = QFileDialog::getOpenFileName(this, tr("Open PCD File"), ".", tr("PCD Files(*.PCD)")); 
	if(path.length() == 0)
	{ 
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files.")); 
    } 
    else
    { 

        std::string file = path.toLatin1().data();
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);



        std::vector<int> indices;
        pcl::PCDReader reader;

        reader.read<pcl::PointXYZ> (file, *cloud);

        pcdwidget->showPointCloud(cloud);

    }
    /****测试网络传输功能***
    using boost::asio::ip::tcp;
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(),"192.168.0.170","3456");
    tcp::resolver::iterator iterator = resolver.resolve(query);

    tcp::socket s(io_service);
    s.connect(*iterator);
    **/
}
using namespace boost;
using boost::asio::ip::tcp;
struct PointCloudBuffers
{
    //typedef boost::shared_ptr<PointCloudBuffers> Ptr;
    std::vector<short> points;
};
void MainWindow::on_pushButton_test_clicked()
{
    //测试网络传输类
    double t0 = ros::Time::now().toSec();
    Net_transfor n1(0);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    n1.receive(*cloud);
    double t1 = ros::Time::now().toSec();
    cout <<"receive time spend="<<(t1-t0)<<endl;
    pcdwidget->showPointCloud(cloud); 



    /*****测试网络传输功能，详情见PCL官网手机实时传输部fen
    pcl::PCDReader reader;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
    reader.read<pcl::PointXYZ> ("3.pcd",*cloud_source);
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud_source);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);

    std::vector<int> dics;
    pcl::removeNaNFromPointCloud(*cloud_filtered,*cloud_filtered,dics);

    sor.filter (*cloud_filtered);
    asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(),static_cast<unsigned short>(3456));
    tcp::acceptor acceptor(io_service,endpoint);
    tcp::socket socket(io_service);
    cout <<"listening to port\t"<<"3456"<<endl;
    acceptor.accept(socket);
    cout <<"size=\t"<<cloud_filtered->size()<<endl;
    const size_t nr_point = cloud_filtered->size();
    //const size_t nr_point = 1000000;
    PointCloudBuffers::Ptr new_buffers = PointCloudBuffers::Ptr(new PointCloudBuffers);
    size_t j =0;
    const int conversion = 1000;
    new_buffers->points.resize(nr_point*3);
    for(size_t i = 0;i<nr_point;++i)
    {
        const pcl::PointXYZ& point = cloud_filtered->points[i];
        new_buffers->points[j*3+0] = static_cast<short>(point.x*conversion);
        new_buffers->points[j*3+1] = static_cast<short>(point.y*conversion);
        new_buffers->points[j*3+2] = static_cast<short>(point.z*conversion);
        j++;
    }
    cout <<"数据处理完成\n";
    int num = 0;

    std::vector<int> num_of_pt(1);
    num_of_pt[0] = new_buffers->points.size();
    

    try{
    //boost::asio::write(socket,boost::asio::buffer(&new_buffers->points.front(),nr_point*3*sizeof(short)));
    boost::asio::write(socket,boost::asio::buffer(num_of_pt));
    num = boost::asio::write (socket, boost::asio::buffer (new_buffers->points));
    }
    catch(boost::system::system_error const& e)
    {
        cout <<"warning:"<<e.what()<<endl;
    }
    cout <<"发送完成\t"<<new_buffers->points.size()<<endl;
    for(int i = 0;i<40;i++)
    {
        cout <<new_buffers->points[i]<<endl;
    }
    //sleep(120);
    ******/

     /* 用于旋转点云并且简单融合
        pcl::PCDReader reader;
        pcl::PCDReader reader1;

        pcl::PointCloud<pcl::PointXYZ> cloud_a;
        pcl::PointCloud<pcl::PointXYZ> cloud_b;
        pcl::PointCloud<pcl::PointXYZ> cloud_c;
        pcl::PointCloud<pcl::PointXYZ> cloud_d;
        Eigen::Matrix4f tf;
        reader.read<pcl::PointXYZ> ("test.pcd",cloud_a);
        reader1.read<pcl::PointXYZ> ("4.pcd",cloud_b);

        cloud_c = cloud_a;
        cloud_c +=cloud_b;
        //pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_c);
        tf(0,0)= 0.999984; tf(0,1)= -0.003425; tf(0,2)= 0.00453491;
        tf(1,0)= 0.00342418; tf(1,1)= 0.999994; tf(1,2)= -0.000188075;
        tf(2,0)= -0.00453552; tf(2,1)= -0.000172543; tf(2,2)= 0.99999;
        tf(0,3) = -0.0394003;
        tf(1,3) = -0.0137822;
        tf(2,3) = 0.00719801;

        pcl::transformPointCloud(cloud_a,cloud_d,tf);
        cloud_d += cloud_b;

        pcl::io::savePCDFileASCII ("merged1.pcd", cloud_d);
    **********************************/

     /* 测试移除点云
    pcl::PCDReader reader;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
    reader.read<pcl::PointXYZ> ("4.pcd",*cloud);
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("x");
    pass.setFilterLimits (0.0, 5.0);
          //pass.setFilterLimitsNegative (true);
    pass.filter (*cloud_filtered);
    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr (&cloud);
    pcl::io::savePCDFileASCII ("test.pcd", *cloud_filtered);
    pcdwidget->showPointCloud(cloud_filtered);
    ******/


    /******
    boost::thread thrd1(boost::bind(&pcdviewer::MainWindow::count,this,1));

    while(1)
    {
        cout <<"2\n";
        wait(1);
    }
    ********/
    /*
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_copy (new pcl::PointCloud<pcl::PointXYZ>);
    

    pcl::PCDReader reader;
    reader.read ("1403838029.040296081.pcd", *cloud);
    double t1 = ros::Time::now().toSec();
    pcl::copyPointCloud(*cloud,*cloud_copy);
    double t2 = ros::Time::now().toSec();
    cout <<"copy time ="<<(t2-t1)<<endl;
    pcdwidget->showPointCloud(cloud_copy);

    cout <<"before filtered size="<<cloud->width*cloud->height<<endl;
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloud_filtered);
    cout <<"after filtered size="<<cloud_filtered->height*cloud_filtered->width<<endl;
    pcl::PCDWriter writer;
    writer.write ("table_scene_lms400_downsampled.pcd", *cloud_filtered);
    */
}
};
/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/




