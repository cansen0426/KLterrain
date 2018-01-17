#include <osg/PositionAttitudeTransform>
#include <osg/BillBoard>
#include <osgText/Text>

#include <sstream>
#include <iostream>
#include <string>

#include "KL3DLineGeode.h"

KL3DLineGeode::KL3DLineGeode() :
	m_id(0.0),
	m_stateSet(NULL),
	m_isDisplay(false),
	m_geometry(NULL),
	m_vertexArray(NULL),
	m_colorArray(NULL),
	m_color(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	m_size(4.0f),
	m_vertexIndex(0),
	m_colorIndex(1),
	m_xCoordBase(0.0f),
	m_yCoordBase(0.0f),
	m_lineLabelRoot(NULL),
	m_isLineLabelVisible(false)
{

}


KL3DLineGeode::~KL3DLineGeode()
{

}


void KL3DLineGeode::init()
{
	//create geometry
	m_geometry = new osg::Geometry();

	//binding vertex array
	m_geometry->setVertexAttribArray(m_vertexIndex, m_vertexArray);
	m_geometry->setVertexAttribBinding(m_vertexIndex, osg::Geometry::BIND_PER_VERTEX);

	//binding color array
	if(m_type == KL3D_SHOTLINE)
	{
		m_color = osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		m_color = osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	m_colorArray = new osg::Vec3Array();
	m_colorArray->push_back(osg::Vec3(m_color.x(), m_color.y(), m_color.z()));
	m_geometry->setVertexAttribArray(m_colorIndex, m_colorArray);
	m_geometry->setVertexAttribBinding(m_colorIndex, osg::Geometry::BIND_OVERALL);

	//create primitiveSet
	m_geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, m_vertexArray->size()));

	//add geometry to geode
	addDrawable(m_geometry);
}


void KL3DLineGeode::reBindingArray()
{
	//binding vertex array
	m_geometry->setVertexAttribArray(m_vertexIndex, m_vertexArray);
	m_geometry->setVertexAttribBinding(m_vertexIndex, osg::Geometry::BIND_PER_VERTEX);

	//binding color array
	m_geometry->setVertexAttribArray(m_colorIndex, m_colorArray);
	m_geometry->setVertexAttribBinding(m_colorIndex, osg::Geometry::BIND_PER_VERTEX);
}


void KL3DLineGeode::reDraw()
{
	m_geometry->removePrimitiveSet(0, 1);
	m_geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, m_vertexArray->size()));

	//标注也重新绘制
	if(m_lineLabelRoot != NULL)
	{
		getParent(0)->getParent(0)->removeChild(m_lineLabelRoot);
		m_lineLabelRoot = NULL;
	}

	setLineLabelIsVisible(m_isLineLabelVisible);
}


void KL3DLineGeode::setID(const double& id)
{
	m_id = id;
}


double KL3DLineGeode::getID() const
{
	return m_id;
}


void KL3DLineGeode::setType(KL3DLineType type)
{
	m_type = type;
}


KL3DLineType KL3DLineGeode::getType() const
{
	return m_type;
}


void KL3DLineGeode::setIsDisplay(bool isDisplay)
{
	setNodeMask(isDisplay);
	m_isDisplay = isDisplay;
	if(!isDisplay)
	{
		if(m_lineLabelRoot != NULL)
			m_lineLabelRoot->setNodeMask(isDisplay);
	}
	else
	{
		if(m_isLineLabelVisible)
		{
			if(m_lineLabelRoot != NULL)
			{
				m_lineLabelRoot->setNodeMask(isDisplay);
			}
			setLineLabelIsVisible(m_isLineLabelVisible);
		}
	}
}


bool KL3DLineGeode::getIsDisplay() const
{
	return m_isDisplay;
}


void KL3DLineGeode::setLineLabelIsVisible(bool isVisible)
{
	m_isLineLabelVisible = isVisible;

	//设置显示，并且线上的顶点数组大于零的时候设置标注
	if(m_isDisplay && (m_vertexArray->size() > 0))
	{
		if(!m_isLineLabelVisible)
		{
			if(m_lineLabelRoot != NULL)
			{
				getParent(0)->getParent(0)->removeChild(m_lineLabelRoot);
			}
			m_lineLabelRoot = NULL;
			return ;
		}

		if(m_lineLabelRoot != NULL)
		{
			getParent(0)->getParent(0)->removeChild(m_lineLabelRoot);
		}
		m_lineLabelRoot = NULL;
		m_lineLabelRoot = new osg::Group();
		for(unsigned int i = 0; i < 2; i++)
		{
			osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
			if( i = 0)
			{
				pat->setPosition(osg::Vec3((*m_vertexArray)[0].x(), (*m_vertexArray)[0].y(), (*m_vertexArray)[0].z()));
			}
			else
			{
				pat->setPosition(osg::Vec3((*m_vertexArray)[m_vertexArray->size() - 1].x(), (*m_vertexArray)[m_vertexArray->size() - 1].y(), (*m_vertexArray)[m_vertexArray->size() - 1].z()));
			}

			std::stringstream value;
			value << m_id;
			std::string strID = value.str();

			osg::ref_ptr<osg::Billboard> billBoard = new osg::Billboard();
			billBoard->setMode(osg::Billboard::POINT_ROT_WORLD);

			osg::ref_ptr<osgText::Text> label = new osgText::Text();
			label->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
			label->setText(strID);
			label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
			label->setCharacterSize(20);
			label->setPosition(osg::Vec3(0, 0, 9));
			label->setAlignment(osgText::Text::CENTER_BOTTOM);
			label->setAutoRotateToScreen(true);

			billBoard->addDrawable(label.get());
			pat->addChild(billBoard.get());

			m_lineLabelRoot->addChild(pat.get());
		}

		getParent(0)->getParent(0)->addChild(m_lineLabelRoot);
	}
}


void KL3DLineGeode::setVertexArray(osg::Vec3Array* pVertexArray)
{
	m_vertexArray = pVertexArray;
}


osg::Vec3Array* KL3DLineGeode::getVertexArray()
{
	return m_vertexArray;
}


void KL3DLineGeode::setColorArray(osg::Vec3Array* pColorArray)
{
	m_colorArray = pColorArray;
}


osg::Vec3Array* KL3DLineGeode::getColorArray()
{
	return m_colorArray;
}


void KL3DLineGeode::setColor(const osg::Vec4& color)
{
	m_color = color;
    (*m_colorArray)[0].x() = color.x();
	(*m_colorArray)[0].y() = color.y();
	(*m_colorArray)[0].z() = color.z();

	reDraw();
}


osg::Vec4 KL3DLineGeode::getColor() const
{
	return m_color;
}


void KL3DLineGeode::setVertexIndex(const GLuint& vertexIndex)
{
	m_vertexIndex = vertexIndex;
}


void KL3DLineGeode::setColorIndex(const GLuint& colorIndex)
{
	m_colorIndex = colorIndex;
}


void KL3DLineGeode::setXCoordBase(const float& xCoordBase)
{
	m_xCoordBase = xCoordBase;
}


void KL3DLineGeode::setYCoordBase(const float& yCoordBase)
{
	m_yCoordBase = yCoordBase;
}


void KL3DLineGeode::deleteLineLabel()
{
	if(m_lineLabelRoot != NULL)
	{
		getParent(0)->getParent(0)->removeChild(m_lineLabelRoot);
		m_lineLabelRoot = NULL;
	}
}