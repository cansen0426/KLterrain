#ifndef __KL3DDESIGNNODE_H__
#define __KL3DDESIGNNODE_H__

#include <osg/MatrixTransform>
//#include<boost//function.hpp>

#include "KL3DPointsNode.h"
#include "KL3DLinesNode.h"
#include "KL3DMapCache.h"
#include "KL3DTextureManager.h"

/*!****************************************************
<br>类说明：三维观测系统显示节点
******************************************************/
/*!关联色表的色标函数指针*/
//typedef boost::function<osg::Vec4(const double& lineID, const float& pointID, const short& sameStakeID, bool isShotLine)> multiAttributeColorFunc;

class KL3DDesignNode : public osg::Group
{
public:
	/*!默认构造函数*/
	KL3DDesignNode(KL3DMapCache* pCache, KL3DTextureManager* pTextureManager);

	/*!初始化函数*/
	virtual void init();

	/*!重绘函数*/
	virtual void reDraw();

	/*!设置ID*/
	void setID(const std::string& id);

	/*!得到ID*/
	std::string getID();

	/*!设置地形节点*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!得到地形节点*/
	osg::Node* getTerrainNode();

	/*!设置地形拉伸系数*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!设置观测系统节点是否显示*/
	void setIsVisible(bool isVisible);

	/*!得到观测系统节点是否显示*/
	bool getIsVisble();

	/*!设置炮检点桩号是否显示*/
	void setLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!设置标注显示间隔*/
	void setLabelInterval(const unsigned int& interval, KL3DLineType type);

	/*!设置炮检线线号是否显示*/
	void setLinesLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!设置初始炮检点贴图*/
	void initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage);

	/*!设置炮检点贴图*/
	void setPointImage(osg::Image* image, KL3DLineType type);

	/*!设置炮检点大小*/
	void setPointSize(const float& pointsize, KL3DLineType type);

	/*!设置炮检点是否可调整大小*/
	void setPointSizeChange(const bool& isChange, const bool& isScroll);

	/*!删除显示节点*/
	bool deleteGeode(KL3DLineType type, const double& id);

	/*!得到炮检点显示节点*/
	KL3DPointsNode* getPointsNode(KL3DLineType type);

	/*!得到炮检线显示节点*/
	KL3DLinesNode* getLinesNode(KL3DLineType type);

	/*!设置纹理管理对象*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!添加高程纹理管理器*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!设置Z方向偏移量*/
	void setDepature(const double& depature);

	/*!得到Z方向偏移量*/
	double getDepature() const;

	/*!设置资源路径*/
	void setSourcePath(const std::string& sourcePath);

	/*!设置函数指针*/
	//void setColorFunc(multiAttributeColorFunc pfn);

	/*!得到函数指针*/
	//multiAttributeColorFunc getColorFunc();

	/*!设置炮点多属性显示*/
	void setShotPointsMultiAttribute(bool isMultiAttribute);

	/*!设置检波点多属性显示*/
	void setRcvPointsMultiAttribute(bool isMultiAttribute);

	/*!得到炮点多属性显示*/
	bool getShotPointsMultiAttribute() const;

	/*!得到检波点多属性显示*/
	bool getRcvPointsMultiAttribute() const;

protected:
	/*!析构函数*/
	virtual ~KL3DDesignNode();

	/*!创建炮检点显示节点*/
	KL3DPointsNode* creatPointsNode(KL3DLineType type);

	/*!创建炮检线显示节点*/
	KL3DLinesNode* createLinesNode(KL3DLineType type);

private:
	/*!三维观测系统显示节点的唯一标识，与对应的数据管理类KL3DMapCache*/
	std::string m_id;

	/*!炮点显示节点*/
	osg::ref_ptr<KL3DPointsNode> m_shotPointsNode;

	/*!检波点显示节点*/
	osg::ref_ptr<KL3DPointsNode> m_rcvPointsNode;

	/*!炮线显示节点*/
	osg::ref_ptr<KL3DLinesNode> m_shotLinesNode;

	/*!检波线显示节点*/
	osg::ref_ptr<KL3DLinesNode> m_rcvLinesNode;

	/*!炮检点、炮检线节点是否被创建*/
	bool m_isPointsNodeCreated, m_isLinesNodeCreated;

	/*!显示节点对应的地形节点*/
	osg::Node* m_terrainNode;

	/*!是否在地形节点上显示*/
	bool m_isExistTerrain;

	/*!纹理观测对象*/
	KL3DTextureManager* m_textureManager;

	/*!显示节点对应的数据管理引擎*/
	KL3DMapCache* m_cache;

	/*!资源路径*/
	std::string m_sourcePath;

	/*!控制x坐标基数*/
	float m_xBase;

	/*!控制y坐标基数*/
	float m_yBase;

	/*!控制Z方向的偏移量:用于井深设计*/
	double m_depature;

	/*!关联色标的函数指针*/
	//multiAttributeColorFunc m_pfn;

	/*!设置炮点是否多属性显示*/
	bool m_isShotPointsMultiAttribute;

	/*!设置检波点是否多属性显示*/
	bool m_isRcvPointsMultiAttribute;

	/*!地形拉伸系数矩阵*/
	osg::MatrixTransform* m_terrainScaleTransform;

	/*!炮点贴图*/
	osg::Image* m_shotPointImage;

	/*!检波点贴图*/
	osg::Image* m_rcvPointImage;

};
#endif