//#include <boost/lexical_cast.hpp>

#include <osg/PositionAttitudeTransform>
#include <osg/Billboard>
#include <osgText/Text>

#include <sstream>
#include <iostream>
#include <string>
#include "KL3DPointGeode.h"

KL3DPointGeode::KL3DPointGeode() :
	m_id(0),
	m_stateSet(NULL),
	m_geometry(NULL),
	m_vertexArray(NULL),
	m_colorArray(NULL),
	m_flagArray(NULL),
	m_labelRoot(NULL),
	m_line(NULL),
	m_size(4.0f),
	m_vertexIndex(0),
	m_colorIndex(1),
	m_flagIndex(2),
	m_xCoordBase(0.0f),
	m_yCoordBase(0.0f),
	m_isLabelVisible(false),
	m_currentLabelInterval(5)
{

}


KL3DPointGeode::~KL3DPointGeode()
{

}


void KL3DPointGeode::init()
{
	for(unsigned int i = 0; i < m_vertexArray->size(); i++)
	{
		(*m_vertexArray)[i].x() -= m_xCoordBase;
		(*m_vertexArray)[i].y() -= m_yCoordBase;
	}

	//创建几何体
	m_geometry = new osg::Geometry();

	//绑定顶点数组
	m_geometry->setVertexAttribArray(m_vertexIndex, m_vertexArray);
	m_geometry->setVertexAttribBinding(m_vertexIndex, osg::Geometry::BIND_PER_VERTEX);

	//绑定颜色数组
	m_geometry->setVertexAttribArray(m_colorIndex, m_colorArray);
	m_geometry->setVertexAttribBinding(m_colorIndex, osg::Geometry::BIND_PER_VERTEX);

	//绑定标识数组
	m_geometry->setVertexAttribArray(m_flagIndex, m_flagArray);
	m_geometry->setVertexAttribBinding(m_flagIndex, osg::Geometry::BIND_PER_VERTEX);

	//创建 primitiveSet
	m_geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, m_vertexArray->size()));

	addDrawable(m_geometry);
}


void KL3DPointGeode::reBindingArray()
{
	//绑定顶点数组
	m_geometry->setVertexAttribArray(m_vertexIndex, m_vertexArray);
	m_geometry->setVertexAttribBinding(m_vertexIndex, osg::Geometry::BIND_PER_VERTEX);

	//绑定颜色数组
	m_geometry->setVertexAttribArray(m_colorIndex, m_colorArray);
	m_geometry->setVertexAttribBinding(m_colorIndex, osg::Geometry::BIND_PER_VERTEX);

	//绑定标识数组
	m_geometry->setVertexAttribArray(m_flagIndex, m_flagArray);
	m_geometry->setVertexAttribBinding(m_flagIndex, osg::Geometry::BIND_PER_VERTEX);
}

void KL3DPointGeode::reDraw()
{
	m_geometry->removePrimitiveSet(0, 1);
	m_geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, m_vertexArray->size()));

	if(!m_labelRoot)
	{
		return;
	}
	else
	{
		setLabelInterval(m_currentLabelInterval);
	}

}


void KL3DPointGeode::setID(const double& id)
{
	m_id = id;
}


double KL3DPointGeode::getID() const
{
	return m_id;
}


void KL3DPointGeode::setType(KL3DLineType type)
{
	m_type = type;
}


KL3DLineType KL3DPointGeode::getType() const
{
	return m_type;
}


void KL3DPointGeode::setLineData(KL3DLine* p3DLine)
{
	m_line = p3DLine;
}


void KL3DPointGeode::setSize(const float& size)
{
	m_size = size;
}

float KL3DPointGeode::getSize() const
{
	return m_size;
}


void KL3DPointGeode::setVertexArray(osg::Vec3Array* pVertexArray)
{
	m_vertexArray = pVertexArray;
}


osg::Vec3Array* KL3DPointGeode::getVertexArray()
{
	return m_vertexArray;
}


void KL3DPointGeode::setColorArray(osg::Vec3Array* pColorArray)
{
	m_colorArray = pColorArray;
}


osg::Vec3Array* KL3DPointGeode::getColorArray()
{
	return m_colorArray;
}


void KL3DPointGeode::setFlagArray(osg::FloatArray* pFlagArray)
{
	m_flagArray = pFlagArray;
}


void KL3DPointGeode::setVertexIndex(const GLuint& index)
{
	m_vertexIndex = index;
}


GLuint KL3DPointGeode::getVertexIndex() const
{
	return m_vertexIndex;
}


void KL3DPointGeode::setColorIndex(const GLuint& index)
{
	m_colorIndex = index;
}


GLuint KL3DPointGeode::getColorIndex() const
{
	return m_colorIndex;
}


void KL3DPointGeode::setFlagIndex(const GLuint& index)
{
	m_flagIndex = index;
}


GLuint KL3DPointGeode::getFlagIndex() const
{
	return m_flagIndex;
}


void KL3DPointGeode::setLabelInterval(const unsigned int& interval)
{
	m_currentLabelInterval = interval;

	if(!m_isLabelVisible)
	{
		return;
	}

	getParent(0)->getParent(0)->removeChild(m_labelRoot);
	m_labelRoot = NULL;
	m_labelRoot = new osg::Group();

	KL3DPointVector* p3DPoints = m_line->getPointVector();
	for(unsigned int i = 0; i < m_vertexArray->size(); i++)
	{
		float id = (*p3DPoints)[i]->getID();
		if((int)id % m_currentLabelInterval != 0)
		{
			continue;
		}

		osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
		pat->setPosition(osg::Vec3f((*m_vertexArray)[i].x(),(*m_vertexArray)[i].y(),(*m_vertexArray)[i].z()));
		std::stringstream value;
		value << id;
		std::string strID = value.str();

		osg::ref_ptr<osg::Billboard> billBoard = new osg::Billboard();
		billBoard->setMode(osg::Billboard::POINT_ROT_WORLD);

		osg::ref_ptr<osgText::Text> label = new osgText::Text();
		label->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
		label->setText(strID);
		label->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		label->setCharacterSize(15);
		label->setPosition(osg::Vec3(8,4,8));
		label->setAlignment(osgText::Text::CENTER_BOTTOM);
		label->setAutoRotateToScreen(true);

		billBoard->addDrawable(label.get());
		pat->addChild(billBoard.get());

		m_labelRoot->addChild(pat.get());
	}

	//将标注的根节点添加到显示叶节点下
	getParent(0)->getParent(0)->addChild(m_labelRoot);
}


void KL3DPointGeode::setLabelIsVisible(bool isVisible)
{
	m_isLabelVisible = isVisible;
	if(m_isLabelVisible)
	{
		setLabelInterval(m_currentLabelInterval);
	}
	else
	{
		getParent(0)->getParent(0)->removeChild(m_labelRoot);
		m_labelRoot = NULL;
	}
}