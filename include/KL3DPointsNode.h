#ifndef __KL3DPOINTSHODE_H__
#define __KL3DPOINTSHODE_H__

#include <osg/Switch>

#include "KL3DPointGeode.h"
#include "KL3DTextureManager.h"

/*!*********************************************
<br>类说明：三维观测系统炮检点显示节点的父节点
***********************************************/
/*!定义绘制叶节点的集合*/
#define KL3DPointGeodeSet std::map<double, KL3DPointGeode*>

class KL3DPointsNode : public osg::Switch
{
public:
	/*!默认构造函数*/
	KL3DPointsNode();

	/*!初始化函数*/
	virtual void init();

	/*!绘制函数*/
	virtual void reDraw();

	/*!设置类型*/
	void setType(KL3DLineType type);

	/*!得到类型*/
	KL3DLineType getType() const;

	/*!得到点的集合*/
	KL3DPointGeodeSet* getPointGeodes();

	/*!根据ID得到点集合中的绘制节点*/
	KL3DPointGeode* getPointGeode(double id);

	/*!向显示列表中插入炮检点绘制节点*/
	bool insertPointGeode(KL3DPointGeode* pPointGeode);

	/*!根据ID删除炮检点绘制节点*/
	bool deletePointGeode(const double& id);

	/*!设置地形节点*/
	void setTerrainNode(osg::Node* pTerrainNode);

	/*!设置地形拉伸系数*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!设置地形拉伸系数*/
	void setTerrainScale(const float& pScale);

	/*!设置地形拉伸系数*/
	float getTerrainScale();

	/*!得到地形节点*/
	osg::Node* getTerrainNode();

	/*!设置纹理管理对象*/
	void setTextureManager(KL3DTextureManager* pTextureManager);

	/*!添加高程纹理管理器*/
	void notifyAddTextureManager(KL3DTextureManager* pTextureManager);

	/*!得到Vertex索引值*/
	GLuint getVertexIndex() const;

	/*!得到color索引值*/
	GLuint getColorIndex() const;

	/*!得到flag索引值*/
	GLuint getFlagIndex() const;

	/*!设置初始炮检点贴图*/
	void initPointImage(osg::Image* pointImage);

	/*!设置点的贴图*/
	void setPointImage(osg::Image* pointImage);

	/*!设置点的大小*/
	void setPointSize(const float& size);

	/*!设置炮检点是否可调整大小*/
	void setPointSizeChange(const bool& isChange, const bool& isScroll);

	/*!得到炮检点的大小*/
	float getPointSize() const;

	/*!设置资源路径*/
	void setSourcePath(const std::string& sourcePath);

	/*!设置x方向的基数*/
	void setXBase(float xBase);

	/*!得到x方向的基数*/
	float getXBase() const;

	/*!设置y方向的基数*/
	void setYBase(float yBase);

	/*!得到y方向的基数*/
	float getYBase() const;

	/*!设置当前的显示状态*/
	void setIsVisible(bool isVisible);

	/*!得到当前的显示状态*/
	bool getIsVisible();

	/*!设置标注是否可见*/
	void setLabelIsVisible(bool isVisible);

	/*!设置标注间隔*/
	void setLabelInterval(const unsigned int& interval);

protected:
	/*!析构函数*/
	virtual ~KL3DPointsNode();

private:
	/*!类型*/
	KL3DLineType m_type;

	/*!对应得状态集*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!炮检点对应的绘制叶节点的集合*/
	KL3DPointGeodeSet m_pointGeodes;

	/*!地形节点*/
	osg::Node* m_terrainNode;

	/*!地形拉伸系数*/
	float m_terrainScale;

	/*!纹理观测对象*/
	KL3DTextureManager* m_textureManager;

	/*!顶点数组索引*/
	GLuint m_vertexIndex;

	/*!顶点颜色数组索引*/
	GLuint m_colorIndex;

	/*!顶点是否显示纹理的标识索引*/
	GLuint m_flagIndex;

	/*!高程纹理索引*/
	int m_demTextureIndex;

	/*!炮检点纹理索引*/
	int m_pointTextureIndex;

	/*!点大小*/
	float m_pointSize;

	/*!点的大小是否可改变*/
	bool m_isPointSizeChange;

	/*!是否为鼠标滚轮操作*/
	bool m_isScroll;

	/*!资源路径*/
	std::string m_sourcePath;

	/*!x,y方向的坐标基数*/
	float m_xBase, m_YBase;

	/*!炮检点贴图*/
	osg::Image* m_pointImage;



};


#endif