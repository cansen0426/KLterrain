#include <osg/LineWidth>
#include <math.h>
#include "KL3DEntityLine.h"

KL3DEntityLine::KL3DEntityLine():
	m_pointArray(NULL),
	m_lineWidth(NULL),
	m_lineStyle(0xFFFF),
	m_terrainTileManager(NULL),
	m_nPointCount(0)
{

}

void KL3DEntityLine::init()
{
	m_geometry = new osg::Geometry();
	
	//计算x、y坐标偏移量
	float xBase = 0.0f;
	float yBase = 0.0f;
	float sampleXCoord = (*m_pointArray)[0].x();
	float sampleYCoord = (*m_pointArray)[0].y();
	xBase = floorf(sampleXCoord / m_xBaseNum);
	yBase = floorf(sampleYCoord / m_yBaseNum);
	(xBase >= 1.0) ? m_xOffset = xBase * m_xBaseNum : m_xOffset = 0.0f;
	(yBase >= 1.0) ? m_yOffset = yBase * m_yBaseNum : m_yOffset = 0.0f;

	osg::ref_ptr<osg::Vec3Array> p3DLineArray = new osg::Vec3Array();
	int interval = 0;
	float twoPointDis = 0.0;
	//循环遍历控制点，每隔距离为5的两点之间进行插值
	for (unsigned int i = 0; i < m_pointArray->size();++i)
	{
		osg::Vec3 start = (*m_pointArray)[i];
		osg::Vec3 end = (*m_pointArray)[i+1];

		twoPointDis = sqrt((end.x()-start.x())+(end.y()-start.y())*(end.y()-start.y()));
		interval = floor(twoPointDis/5.0);
		if (interval == 0 || interval == 1)
		{
			start.x() -= m_xOffset;
			start.y() -= m_yOffset;
			end.x() -= m_xOffset;
			end.y() -= m_yOffset;
			p3DLineArray->push_back(start);
			p3DLineArray->push_back(end);
		}
		else
		{
			float x_interval = (end.x() - start.x())/interval;
			float y_interval = (end.y() - start.y())/interval;
			//得到每个插值点的坐标，并将其传入到p3DLineArray中
			for (unsigned ins = 0; ins < interval; ++ins)
			{ 
				if (start == end) break;
				osg::Vec3 temp;
				temp.x() = start.x() + ins * x_interval;
				temp.y() = start.y() + ins * y_interval;
				temp.z() = start.z();
				m_terrainTileManager->getValue(temp.x(),temp.y(),temp.z());
				temp.x() -= m_xOffset;
				temp.y() -= m_yOffset;
				p3DLineArray->push_back(temp);
				
			}
		}
	}
	m_geometry->setVertexArray(p3DLineArray);
	
	//creat primitiveSet
	m_geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,p3DLineArray->size()));

	osg::ref_ptr<osg::StateSet> pStateset = m_geometry->getOrCreateStateSet();

	//若设置了线宽
	if (!(m_lineWidth == NULL))
	{
		osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth();
		lw->setWidth(m_lineWidth);
		pStateset->setAttribute(lw);
	}

	pStateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	//反走样的fastest效果设置
	pStateset->setRenderingHint(GL_FASTEST);
	//允许设置线的样式
	pStateset->setMode(GL_LINE_STIPPLE,osg::StateAttribute::ON);

	//线样式的设置
	osg::ref_ptr<osg::LineStipple> pLineStipple = new osg::LineStipple(1,m_lineStyle);
	pStateset->setAttribute(pLineStipple,osg::StateAttribute::ON);

	osg::ref_ptr<osg::Uniform> colorUniform = new osg::Uniform("color",m_color);
	pStateset->addUniform(colorUniform);

	addDrawable(m_geometry);
}

KL3DEntityLine::~KL3DEntityLine()
{

}

void KL3DEntityLine::setPointArray(osg::Vec3Array* pPointArray)
{
	m_pointArray = pPointArray;
}

void KL3DEntityLine::setLineWidth(const float& pLineWidth)
{
	m_lineWidth = pLineWidth;
}

void KL3DEntityLine::setLineStyle(const std::string& pLineStyle)
{
	if (pLineStyle == "LineSolid")
	{
		m_lineStyle = 0xFFFF;
	}
	else if (pLineStyle == "LineDash")
	{
		m_lineStyle = 0xFFF8;
	}
	else if (pLineStyle == "LineDot")
	{
		m_lineStyle = 0xF0F0;
	}
	else if (pLineStyle == "LineDashDot")
	{
		m_lineStyle = 0xFFCC;
	}
}

void KL3DEntityLine::setTerrainTileManager(KL3DTerrainTileManager* terrainTileManager)
{
	m_terrainTileManager = terrainTileManager;
}
