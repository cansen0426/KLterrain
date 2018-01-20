#include <iostream>
#include <string>

using namespace std;

#include <osgText/Text>
#include <osgText/String>
//#include <QtCore/QTextCodec>

#include "KL3DBaseEntity.h"

//const std::string m_vertexShaderPatch = "/shaders/KL3DDesignBoundaryRender.vert";
//const std::string m_fragShaderPatch = "/shaders/KL3DDesignBoundaryRender.frag";
KL3DBaseEntity::KL3DBaseEntity():
	m_id("0"),
	m_name(""),
	m_color(osg::Vec4(1.0f,1.0f,1.0f,1.0f)),
	m_geometry(NULL),
	m_xOffset(0.0f),
	m_yOffset(0.0f),
	m_xBaseNum(10000.0f),
	m_yBaseNum(10000.0f),
	m_image(NULL),
	m_entityCore(1.0,1.0,1.0)
{

}

KL3DBaseEntity::~KL3DBaseEntity()
{

}

void KL3DBaseEntity::init()
{

}

void KL3DBaseEntity::reDraw()
{

}

void KL3DBaseEntity::setID(const std::string& id)
{
	m_id = id;
}

std::string KL3DBaseEntity::getID() const
{
	return m_id;
}

void KL3DBaseEntity::setName(const std::string& name)
{
	m_name = name;
}

std::string KL3DBaseEntity::getName() const
{
	return m_name;
}

void KL3DBaseEntity::setColor(const osg::Vec4f& color)
{
	m_color = color;
}

osg::Vec4f KL3DBaseEntity::getColor() const
{
	return m_color;
}

osg::Vec3 KL3DBaseEntity::getEntityCore() const
{
	return m_entityCore;
}

void KL3DBaseEntity::setImage(osg::ref_ptr<osg::Image> pImage)
{
	m_image = pImage;
}

float KL3DBaseEntity::getXoffset()
{
	return m_xOffset;
}

float KL3DBaseEntity::getYoffset()
{
	return m_yOffset;
}


