#ifndef __KL3DPOINTGEODE_H__
#define __KL3DPOINTGEODE_H__

#include <osg/Geode>
#include <osg/Geometry>

#include "KL3DCommonStruct.h"
#include "KL3DLine.h"

/*!************************************************************
<br>类说明：三维观测系统中，一条线上所有点组成的osg叶节点
**************************************************************/

class KL3DPointGeode: public osg::Geode
{
public:
	/*!默认构造函数*/
	KL3DPointGeode();

	/*!默认初始化函数*/
	virtual void init();

	/*!重新缓冲区数组*/
	virtual void reBindingArray();

	/*!重绘函数*/
	virtual void reDraw();

	/*!设置ID:唯一标识*/
	void setID(const double& id);

	/*!得到ID*/
	double getID() const;

	/*!设置类型*/
	void setType(KL3DLineType type);

	/*!得到类型*/
	virtual KL3DLineType getType() const;

	/*!设置显示节点对应的数据*/
	void setLineData(KL3DLine* p3DLine);

	/*!设置顶点数组*/
	void setVertexArray(osg::Vec3Array* pVertexArray);

	/*!得到顶点数组*/
	osg::Vec3Array* getVertexArray();

	/*!设置颜色数组*/
	void setColorArray(osg::Vec3Array* pColorArray);

	/*!得到颜色数组*/
	osg::Vec3Array* getColorArray();

	/*!设置标识数组*/
	void setFlagArray(osg::FloatArray* pFlagArray);

	/*!设置点的大小*/
	void setSize(const float& size);

	/*!得到点的大小*/
	float getSize() const;

	/*!设置顶点数组索引*/
	void setVertexIndex(const GLuint& index);

	/*!得到顶点数组索引*/
	GLuint getVertexIndex() const;

	/*!设置颜色数组索引*/
	void setColorIndex(const GLuint& index);

	/*!得到颜色数组索引*/
	GLuint getColorIndex() const;

	/*!设置标识索引*/
	void setFlagIndex(const GLuint& index);

	/*!得到标识索引*/
	GLuint getFlagIndex() const;

	/*!设置是否显示炮检点标注*/
	void setLabelIsVisible(bool isVisible);

	/*!设置标注间隔*/
	void setLabelInterval(const unsigned int& interval);

protected:
	/*!默认析构函数*/
	virtual ~KL3DPointGeode();

private:
	/*!ID:叶节点的唯一标识*/
	double m_id;

	/*!绘制节点类型*/
	KL3DLineType m_type;

	/*!该节点的状态集*/
	osg::ref_ptr<osg::StateSet> m_stateSet;

	/*!对应的绘制节点Geometry*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!顶点数组*/
	osg::Vec3Array* m_vertexArray;

	/*!颜色数组*/
	osg::Vec3Array* m_colorArray;

	/*!表示数组*/
	osg::FloatArray* m_flagArray;

	/*!绘制节点的大小*/
	float m_size;

	/*顶点数组索引*/
	GLuint m_vertexIndex;

	/*!颜色数组索引*/
	GLuint m_colorIndex;

	/*!标识数组索引*/
	GLuint m_flagIndex;

	/*!炮检点标注显示节点*/
	osg::ref_ptr<osg::Group> m_labelRoot;

	/*!当前标注的间隔*/
	unsigned int m_currentLabelInterval;

	/*!三维线数据*/
	KL3DLine* m_line;

	/*!标注是否显示：默认否*/
	bool m_isLabelVisible;

public:
	/*!x方向坐标偏移量*/
	float m_xCoordBase;

	/*!y方向坐标偏移量*/
	float m_yCoordBase;

};

#endif