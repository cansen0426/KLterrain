#ifndef __KL3DLINESNODE_H__
#define __KL3DLINESNODE_H__

#include <osgSim/OverlayNode>

#include "KL3DLineGeode.h"
#include "KL3DTextureManager.h"

/*!***********************************************
<br>类说明：三维观测系统炮检线显示的主节点
**************************************************/
#define  KL3DLineGeodeSet std::map<double, KL3DLineGeode*>

class KL3DLinesNode: public osg::Switch
{
public:
	/*!默认构造函数*/
	KL3DLinesNode();

	/*!初始化函数*/
	virtual void init();

	/*!重绘函数*/
	virtual void reDraw();

	/*!设置类型*/
	virtual void setType(KL3DLineType type);

	/*!得到类型*/
	virtual KL3DLineType getType() const;

	/*!删除炮检线绘制节点*/
	bool deleteLineGeode(const double& id);

	/*!设置显示状态*/
	virtual void setIsDisplay(bool isDisplay);

	/*!得到显示状态*/
	virtual bool getIsDisplay() const;

	/*!设置炮检线标注是否可见*/
	void setLinesLabelIsVisible(bool isVisible);

	/*!得到炮检线标注是否可见*/
	bool getLinesLabelIsVisible() const;

	/*!设置线的大小*/
	virtual void setLineSize(const float& size);

	/*!得到线的宽度（大小）*/
	virtual float getLineSize() const;

	/*!设置线的颜色*/
	virtual void setLineColor(const osg::Vec4& color);

	/*!得到线的颜色*/
	virtual osg::Vec4 getLineColor() const;

	/*!得到炮检线绘制节点的集合*/
	virtual KL3DLineGeodeSet* getLinesGeodes();

	/*!得到指定的炮检线绘制节点*/
	virtual KL3DLineGeode* getLineGeode(double id);

	/*!向显示队列中插入炮检线显示节点*/
	virtual bool insertLineGeode(KL3DLineGeode* pLineGeode);

	/*!设置地形节点*/
	virtual void setTerrainNode(osg::Node* pTerrainNode);

	/*!得到地形节点*/
	virtual osg::Node* getTerrainNode();

	/*!设置纹理管理对象*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!添加高程纹理管理器*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!得到vertex索引值*/
	GLuint getVertexIndex() const;

	/*!得到color索引值*/
	GLuint getColorIndex() const;

	/*!设置资源路径*/
	virtual void setSourcePath(const std::string& sourcePath);

	/*!设置x方向的基数*/
	virtual void setXBase(const float& xBase);

	/*!得到x方向的基数*/
	virtual float getXBase() const;

	/*!设置y方向的基数*/
	virtual void setYBase(const float& yBase);

	/*!得到y方向的基数*/
	virtual float getYBase() const;

	/*!设置地形拉伸系数*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!设置地形拉伸系数*/
	void setTerrainScale(const float& pScale);

protected:
	/*!析构函数*/
	virtual ~KL3DLinesNode();

private:
	/*!类型*/
	KL3DLineType m_type;

	/*!对应的状态集*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!炮检线绘制节点的集合*/
	KL3DLineGeodeSet m_lineGeodes;

	/*!标识：绘制节点是否显示*/
	bool m_isDisplay;

	/*!炮检线的标注是否显示*/
	bool m_isDisplayLineLabel;

	/*!线宽*/
	float m_lineSize;

	/*!线的颜色*/
	osg::Vec4 m_color;

	/*!地形节点*/
	osg::Node* m_terrainNode;

	/*!纹理管理对象*/
	KL3DTextureManager* m_textureManager;

	/*!顶点数组索引*/
	GLuint m_vertexIndex;

	/*!颜色数组索引*/
	GLuint m_colorIndex;

	/*!高程纹理索引*/
	int m_demTextureIndex;

	/*!资源路径*/
	std::string m_sourcePatch;

	/*!x、y方向的坐标基数*/
	float m_xBase, m_yBase;

	/*!地形拉伸系数*/
	float m_terrainScale;
};

#endif