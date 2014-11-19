/**
 * @file /include/pcdviewer/main_window.hpp
 *
 * @brief Qt based gui for pcdviewer.
 *
 * @date November 2010
 **/
#ifndef pcdviewer_MAIN_WINDOW_H
#define pcdviewer_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

#include <pcl/visualization/pcl_visualizer.h>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace pcdviewer {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class PointCloudWidget : public QVTKWidget
{
Q_OBJECT
public:
    //Whatever comes before (constructor, methods, etc.)
    PointCloudWidget(QWidget *parent = 0) : QVTKWidget(parent)
	{
	   pcl::PointCloud<pcl::PointXYZ>::Ptr pc (new pcl::PointCloud<pcl::PointXYZ>);

	   vis.addPointCloud<pcl::PointXYZ>(pc);
	   vtkSmartPointer<vtkRenderWindow> renderWindow = vis.getRenderWindow();
	   this->SetRenderWindow(renderWindow);
	   vis.initCameraParameters ();
	   this->show();
	}



	//pcl::visualization::CloudViewer* viewer;
    pcl::visualization::PCLVisualizer* m_visualizer;
    pcl::visualization::PCLVisualizer vis;
    //pcl::visualization::CloudViewer viewer (" ");

	void showPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr pt)
	{
		vis.updatePointCloud<pcl::PointXYZ>(pt); 
        //vis.setFullScreen(true);
		vis.addCoordinateSystem (1.0);
		vis.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,1);
		vis.initCameraParameters ();
   		this->update();
	}

	void showPointNormal(const pcl::PointCloud<pcl::PointXYZ>::Ptr pt,const pcl::PointCloud<pcl::Normal>::Ptr pn)
	{
             vis.setBackgroundColor (0.0, 0.0, 0.5);
             vis.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(pt,pn);
   		this->update();
	}
};

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();
  void count(int id);


private Q_SLOTS:
	void on_pushButton_opnefile_clicked();
	void on_pushButton_test_clicked();
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	//void on_button_connect_clicked(bool check );

    /******************************************
    ** Manual connections
    *******************************************/

private:
	Ui::MainWindowDesign ui;
  	PointCloudWidget* pcdwidget;

};

}  // namespace pcdviewer

#endif // pcdviewer_MAIN_WINDOW_H
