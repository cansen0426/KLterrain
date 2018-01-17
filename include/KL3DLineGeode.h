#ifndef __KL3DLINEGEODE_H__
#define __KL3DLINEGEODE_H__

#include <osg/Geode>
#include <osg/Geometry>

#include "KL3DCommonStruct.h"

/*!****************************************************
<br>类说明：炮检线绘制的叶节点
*******************************************************/
class KL3DLineGeode : public osg::Geode
{
public:
	/*!默认构造函数*/
	KL3DLineGeode();

	/*!析构函数*/
	~KL3DLineGeode();

	/*!初始化函数*/
	virtual void init();

	/*!重绘函数*/
	virtual void reDraw();

	/*!设置线显示节点的ID*/
	virtual void setID(const double& id);

	/*!得到线显示节点的ID*/
	virtual double getID() const;

	/*!设置线显示节点的类型*/
	virtual void setType(KL3DLineType type);

	/*!得到线显示节点的类型*/
	virtual KL3DLineType getType() const;

	/*!设置显示状态*/
	virtual void setIsDisplay(bool isDisplay);

	/*!得到显示状态*/
	virtual bool getIsDisplay() const;

	/*!设置是否显示炮检线标注*/
	void setLineLabelIsVisible(bool isVisible);

	/*!设置顶点数组*/
	virtual void setVertexArray(osg::Vec3Array* pVertexArray);

	/*!得到顶点数组*/
	virtual osg::Vec3Array* getVertexArray();

	/*!设置线的颜色*/
	virtual void setColor(const osg::Vec4& color);

	/*!得到线的颜色*/
	virtual osg::Vec4 getColor() const;

	/*!设置颜色数组*/
	virtual void setColorArray(osg::Vec3Array* pColorArray);

	/*!得到颜色数组*/
	virtual osg::Vec3Array* getColorArray();

	/*!设置顶点数组索引*/
	virtual void setVertexIndex(const GLuint& vertexIndex);

	/*!设置顶点颜色数索引*/
	virtual void setColorIndex(const GLuint& colorIndex);

	/*!设置x方向坐标基数*/
	virtual void setXCoordBase(const float& xCoordBase);

	/*!设置y方向坐标基数*/
	virtual void setYCoordBase(const float& yCoordBase);

	/*!重新绑定顶点数组*/
	void reBindingArray();

	/*!删除线号标注*/
	void deleteLineLabel();

private:
	/*!叶节点唯一标识*/
	double m_id;

	/*!绘制叶节点的类型*/
	KL3DLineType m_type;

	/*!该叶节点的状态集*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!标识：绘制节点是否显示*/
	bool m_isDisplay;

	/*!叶节点的绘制几何节点*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!顶点数组*/
	osg::Vec3Array* m_vertexArray;

	/*!线的颜色*/
	osg::Vec4 m_color;

	/*!颜色数组*/
	osg::ref_ptr<osg::Vec3Array> m_colorArray;

	/*!线宽*/
	float m_size;

	/*!顶点数组索引*/
	GLuint m_vertexIndex;

	/*!颜色数组索引*/
	GLuint m_colorIndex;

	/*!x坐标方向基数*/
	float m_xCoordBase;

	/*!y坐标方向基数*/
	float m_yCoordBase;

	/*!炮检线编号显示节点*/
	osg::ref_ptr<osg::Group> m_lineLabelRoot;

	/*!炮检线编号是否显示*/
	bool m_isLineLabelVisible;
};
#endif