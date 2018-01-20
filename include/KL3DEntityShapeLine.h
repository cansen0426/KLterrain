#ifndef __KL3DENTITYSHAPELINE_H__
#define __KL3DENTITYSHAPELINE_H__

#include <osg/MatrixTransform>
#include <osgSim/OverlayNode>

//#include "KL3DVScene.h"
//#include "KL3DVisualObject.h"
#include "KL3DEntityLine.h"
#include "KL3DEntityText.h"
#include "KL3DTerrainTileManager.h"
#include "KL3DTextureManager.h"

//#include "KL3DDesignMacro.h"

/*!***************************************
<br>类说明： 三维线状通用图元
*****************************************/
#define KL3DEntityLineSet std::map<std::string,osg::ref_ptr<KL3DEntityLine> >
#define KL3DEntityLineNameLabelSet std::map<std::string, osg::ref_ptr<KL3DEntityText> >

//三维线状图元
struct KL3DEntityLineStruct 
{
	KL3DEntityLineStruct():
		m_id("-1"),
		m_name(""),
		m_color(osg::Vec4(1.0f,1.0f,1.0f,1.0f)),
		m_lineStyle("LineSolid"),
		m_lineWidth(4.0f)
		{

		};
		std::string m_id;
		std::string m_name;
		osg::ref_ptr<osg::Vec3Array> m_vertexArray;
		float m_lineWidth;
		//线样式（LineSolid、LineDash、LineDot、LineDashDot）
		std::string m_lineStyle;
		osg::Vec4 m_color;
};

#endif