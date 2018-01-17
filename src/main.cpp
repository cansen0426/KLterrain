
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ComputeBoundsVisitor>
#include <osg/MatrixTransform>

#include <osgTerrain/Terrain>
#include <osgTerrain/TerrainTile>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include "KL3DDesignShape.h"


int main()
{
	//创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	//创建场景组节点
	osg::ref_ptr<osg::Group> root = new osg::Group();

	//std::string iveFilename = "../KL3DDisplay/data/dabei/大北_xyz54.ive";
	std::string iveFilename = "../KL3DDisplay/data/puget/puget.ive";
	osg::Node* node = osgDB::readNodeFile(iveFilename);
	osgTerrain::Terrain* terrain =dynamic_cast<osgTerrain::Terrain*>(node);

	//添加到场景
	root->addChild(terrain);

	KL3DDesignShape* pDesignShape = new KL3DDesignShape();
	pDesignShape->setRootNode(root);
	pDesignShape->setSourcePath("../KL3DDisplay/");
	pDesignShape->generate3DDesignData(viewer, terrain);
	//std::string shpFilename = "data/dabei_50m.shp";
	//pDesignShape->generate3DDesignData(viewer,terrain,shpFilename);


	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->setUpViewInWindow(100, 100, 800, 600);
	//设置场景数据
	viewer->setSceneData(root.get());

	//初始化并创建窗口
	viewer->realize();

	//开始渲染
	viewer->run();

	//system("pause");

	return 0 ;
}