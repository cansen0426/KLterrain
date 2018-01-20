#ifndef __KL3DBASEENTITY_H__
#define __KL3DBASEENTITY_H__

#include <osg/Geode>
#include <osg/Geometry>

#include <osg/LineWidth>
#include <osg/LineStipple>

#include "KL3DTerrainTileManager.h"
//#include "KL3DMacro.h"
/*!***************************************
<br>类说明： 通用图元基类
*****************************************/
class KL3DBaseEntity: public osg::Geode
{
public:
	/*!默认构造函数*/
	KL3DBaseEntity();

	/*!初始化函数*/
	virtual void init();
	
	/*!重绘函数*/
	virtual void reDraw();
	
	/*!设置ID*/
	void setID(const std::string& id);
	
	/*!得到ID*/
	std::string getID() const;
	
	/*!设置名称*/
	void setName(const std::string& name);
	
	/*!得到名称*/
	std::string getName() const;
	
	/*!设置图元贴图*/
	void setImage(osg::ref_ptr<osg::Image> pImage);
	
	/*!设置颜色*/
	void setColor(const osg::Vec4f& color);

	/*!得到颜色*/
	osg::Vec4f getColor() const;

	/*!得到图元重心*/
	osg::Vec3 getEntityCore() const;

	/*!得到x方向偏移量*/
	float getXoffset();

	/*!得到y方向偏移量*/
	float getYoffset();

	/*!默认析构函数*/
	virtual ~KL3DBaseEntity();

protected:
	/*!图元的数据库ID，用于数据库的表格记录，每一个图元唯一对应一个ID，id一直增长，删除的不会被重复使用*/
	std::string m_id;

	/*!图元名称，可以为空*/
	std::string m_name;

	/*!颜色*/
	osg::Vec4f m_color;

	/*!图元绘制节点*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!x坐标的偏移量*/
	float m_xOffset;

	/*!y坐标的偏移量*/
	float m_yOffset;

	/*!控制x坐标的偏移基数*/
	float m_xBaseNum;

	/*!控制y坐标的偏移基数*/
	float m_yBaseNum;

	/*!图元贴图*/
	osg::ref_ptr<osg::Image> m_image;

	/*!图元重心（绘制图元名称的位置）*/
	osg::Vec3 m_entityCore;
};
#endif