#ifndef __KL3DDESIGNSHAPE_H__
#define __KL3DDESIGNSHAPE_H__

#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgTerrain/Terrain>

#include <osg/BoundingBox>
#include <osg/MatrixTransform>

#include "KL3DMapManager.h"
#include "KL3DDesignHandle.h"
#include "KL3DDesignPolygonHandle.h"

/*!*******************************************************
<br>类说明：三维观测系统图元类（因为没有二维观测系统的支持，所以这里和东方项目差距很大）
*********************************************************/

class KL3DDesignShape
{
public:
	/*!默认构造函数*/
	KL3DDesignShape();

	/*!析构函数*/
	~KL3DDesignShape();

	/*!初始化函数*/
	virtual void init();

	/*!设置根节点*/
	void setRootNode(osg::Node* rootNode);

	/*!设置资源路径*/
	void setSourcePath(const std::string sourcePath);

	/*!根据文件生成观测系统数据*/
	bool generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain, std::string dataFileName);

	/*!根据地形自己编数据生成观测系统数据*/
	bool generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain);

	/*!设置是否显示观测系统节点*/
	void setDesignNodeVisible(bool isVisible);

	/*!设置是否显示炮检点*/
	void setPointsVisible(bool isVisible, KL3DLineType type);

	/*!设置是否显示炮检点桩号*/
	void setLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!设置标注间隔*/
	void setLabelInterval(const unsigned int& interval, KL3DLineType type);

	/*!设置是否显示炮检线*/
	void setLinesVisible(bool isVisible, KL3DLineType);

	/*!设置是否显示炮检线线号*/
	void setLinesLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!创建初始的炮检点贴图*/
	osg::ref_ptr<osg::Image> createPointImage(KL3DLineType type);

	/*!设置炮检点大小*/
	void setPointSize(const float& PointSize, KL3DLineType type);

	/*!是否存在地形*/
	bool isTerrainExist();

	/*!设置地形拉伸系数*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!设置交互事件类*/
	void setCurrentEventHandle(osg::ref_ptr<KL3DBaseHandler> pHandle);

protected:
	/*!生成三位线插入到观测系统中*/
	void generate3DLines(KL3DMapCache* pCache);

private:
	/*!三维场景视景器*/
	osgViewer::Viewer* m_viewer;

	/*!三维场景根节点*/
	osg::Node* m_root;

	/*!KL3DMapManager对象*/
	KL3DMapManager* m_mapManager;

	/*!设计资源路径*/
	std::string m_designSourcePath;

	/*!地形拉伸系数矩阵*/
	osg::MatrixTransform* m_terrainScaleTranform;

	/*!三维观测系统炮检点交互类对象*/
	osg::ref_ptr<KL3DDesignHandle> m_3DDesignHandle;

	/*!三维观测系统炮检点多边形交互类对象*/
	osg::ref_ptr<KL3DDesignPolygonHandle> m_3DDesignPolygonHandle;

	//*****************炮检点贴图数据***********************//
	/*!获取当前的炮点图像的名字*/
	//std::string m_currentSpImageName;

	/*!获取当前检点图像的名字*/
	//std::string m_currentRvImageName;

	/*!获取当前的炮点填充颜色*/
	//osg::Vec4 m_currentSpFillColor;

};

#endif