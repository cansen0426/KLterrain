#include <osg/Point>
#include <osg/PointSprite>
#include <osgDB/ReadFile>

#include "KL3DDesignNode.h"

KL3DDesignNode::KL3DDesignNode(KL3DMapCache* pCache, KL3DTextureManager* pTextureManager) :
	m_cache(pCache),
	m_textureManager(pTextureManager),
	m_id(pCache->getID()),
	m_terrainNode(NULL),
	m_shotPointsNode(NULL),
	m_rcvPointsNode(NULL),
	m_shotLinesNode(NULL),
	m_rcvLinesNode(NULL),
	m_isPointsNodeCreated(false),
	m_isLinesNodeCreated(false),
	m_sourcePath(""),
	m_xBase(100000.0f),
	m_yBase(100000.0f),
	m_depature(pCache->getDepature()),
	m_isShotPointsMultiAttribute(false),
	m_isRcvPointsMultiAttribute(false),
	m_terrainScaleTransform(NULL),
	m_shotPointImage(NULL),
	m_rcvPointImage(NULL)
{
	//is exist terrain node
	if(pTextureManager)
	{
		m_terrainNode = pTextureManager->getTerrainNode();
		m_isExistTerrain = true;
	}
}


KL3DDesignNode::~KL3DDesignNode()
{

}


void KL3DDesignNode::init()
{
	//create the pointsNode
	m_shotPointsNode = creatPointsNode(KL3D_SHOTLINE);
	m_rcvPointsNode = creatPointsNode(KL3D_RCVLINE);

	//create the linesNode
	m_shotLinesNode = createLinesNode(KL3D_SHOTLINE);
	m_rcvLinesNode = createLinesNode(KL3D_RCVLINE);

}


void KL3DDesignNode::reDraw()
{
	m_shotPointsNode->reDraw();
	m_rcvPointsNode->reDraw();

	m_shotLinesNode->reDraw();
	m_rcvLinesNode->reDraw();

}


KL3DPointsNode* KL3DDesignNode::getPointsNode(KL3DLineType type)
{
	if(type == KL3D_SHOTLINE)
	{
		return m_shotPointsNode;
	}
	else
	{
		return m_rcvPointsNode;
	}
}


KL3DLinesNode* KL3DDesignNode::getLinesNode(KL3DLineType type)
{
	if(type == KL3D_SHOTLINE)
	{
		return m_shotLinesNode;
	}
	else
	{
		return m_rcvLinesNode;
	}
}


bool KL3DDesignNode::deleteGeode(KL3DLineType type, const double& id)
{
	KL3DPointsNode* pPointsNode = NULL;
	KL3DLinesNode* pLinesNode = NULL;

	if(type == KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
		pLinesNode = m_shotLinesNode;
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
		pLinesNode = m_rcvLinesNode;
	}

	pPointsNode->deletePointGeode(id);
	pLinesNode->deleteLineGeode(id);

	return true;
}


void KL3DDesignNode::setSourcePath(const std::string& sourcePath)
{
	m_sourcePath = sourcePath;
}


void KL3DDesignNode::setDepature(const double& depature)
{
	m_depature = depature;
}


double KL3DDesignNode::getDepature() const
{
	return m_depature;
}


void KL3DDesignNode::setIsVisible(bool isVisible)
{
	setNodeMask(isVisible);
}


bool KL3DDesignNode::getIsVisble()
{
	return getNodeMask();
}


void KL3DDesignNode::setLabelIsVisible(bool isVisible, KL3DLineType type)
{
	KL3DPointsNode* pPointsNode = NULL;
	if(type ==  KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
	}

	pPointsNode->setLabelIsVisible(isVisible);
}


void KL3DDesignNode::setLabelInterval(const unsigned int& interval, KL3DLineType type)
{
	KL3DPointsNode* pPointsNode = NULL;
	if(type == KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
	}

	pPointsNode->setLabelInterval(interval);
}


void KL3DDesignNode::setLinesLabelIsVisible(bool isVisible, KL3DLineType type)
{
	KL3DLinesNode* pLinesNode = NULL;
	if(type == KL3D_SHOTLINE)
	{
		pLinesNode = m_shotLinesNode;
	}
	else
	{
		pLinesNode = m_rcvLinesNode;
	}
	pLinesNode->setLinesLabelIsVisible(isVisible);
}


void KL3DDesignNode::initPointImage(osg::Image* shotPointImage, osg::Image* rcvPointImage)
{
	m_shotPointImage = shotPointImage;
	m_rcvPointImage = rcvPointImage;
}


void KL3DDesignNode::setPointImage(osg::Image* image, KL3DLineType type)
{
	KL3DPointsNode* pPointsNode = NULL;

	if(type ==  KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
	}

	pPointsNode->setPointImage(image);
}


void KL3DDesignNode::setPointSize(const float& pointsize, KL3DLineType type)
{
	KL3DPointsNode* pPointsNode = NULL;

	if(type == KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
	}

	pPointsNode->setPointSize(pointsize);
}


void KL3DDesignNode::setPointSizeChange(const bool& isChange, const bool& isScroll)
{
	KL3DPointsNode* pShotPointsNode = m_shotPointsNode;
	pShotPointsNode->setPointSizeChange(isChange, isScroll);
	KL3DPointsNode* pRcvPointsNode = m_rcvPointsNode;
	pRcvPointsNode->setPointSizeChange(isChange, isScroll);
}


osg::Node* KL3DDesignNode::getTerrainNode()
{
	return m_terrainNode;
}


void KL3DDesignNode::setTerrainScale(osg::MatrixTransform* mt)
{
	m_terrainScaleTransform = mt;
}


/*
void KL3DDesignNode::setColorFunc(multiAttributeColorFunc pfn)
{
	m_pfn = pfn;
}*/


/*
multiAttributeColorFunc KL3DDesignNode::getColorFunc()
{
	return m_pfn;
}*/


void KL3DDesignNode::setShotPointsMultiAttribute(bool isMultiAttribute)
{
	m_isShotPointsMultiAttribute = isMultiAttribute;
}


void KL3DDesignNode::setRcvPointsMultiAttribute(bool isMultiAttribute)
{
	m_isRcvPointsMultiAttribute = isMultiAttribute;
}


bool KL3DDesignNode::getShotPointsMultiAttribute() const
{
	return m_isShotPointsMultiAttribute;
}


bool KL3DDesignNode::getRcvPointsMultiAttribute() const
{
	return m_isRcvPointsMultiAttribute;
}


KL3DPointsNode* KL3DDesignNode::creatPointsNode(KL3DLineType type)
{
	osg::ref_ptr<KL3DPointsNode> pPointsNode = NULL;
	KL3DLineSet* pLineSet = NULL;
	if(type == KL3D_SHOTLINE)
	{
		pPointsNode = m_shotPointsNode;
		pLineSet = m_cache->getShotLineSet();
	}
	else
	{
		pPointsNode = m_rcvPointsNode;
		pLineSet = m_cache->getRcvLineSet();
	}

	if(m_isPointsNodeCreated)
	{
		return pPointsNode;
	}

	//create KL3DPointsNode
	pPointsNode = new KL3DPointsNode();
	pPointsNode->setTerrainNode(m_terrainNode);
	pPointsNode->setTextureManager(m_textureManager);
	pPointsNode->setSourcePath(m_sourcePath);
	if(type == KL3D_SHOTLINE)
		pPointsNode->initPointImage(m_shotPointImage);
	else
		pPointsNode->initPointImage(m_rcvPointImage);
	pPointsNode->setType(type);

	//create  point Geode
	float xBase = 0.0f;
	float yBase = 0.0f;
	KL3DLineSet::iterator lineIter = pLineSet->begin();

	for(; lineIter != pLineSet->end(); ++lineIter)
	{
		KL3DLine* pTempLine = lineIter->second;
		osg::Vec3Array* pTempArray = pTempLine->getVertexArray();
		if(pTempArray->size() > 0)
		{
			float sampleXCoord = (*(pTempLine->getVertexArray()))[0].x();
			float sampleYCoord = (*(pTempLine->getVertexArray()))[0].y();
			xBase = floorf(sampleXCoord / m_xBase);
			yBase = floorf(sampleYCoord / m_yBase);
			break;
		}
	}

	lineIter = pLineSet->begin();
	for(; lineIter != pLineSet->end(); ++lineIter)
	{
		KL3DLine* pLine = lineIter->second;
		osg::ref_ptr<KL3DPointGeode> pPointGeode = new KL3DPointGeode();
		pPointGeode->setID(pLine->getID());
		pPointGeode->setType(pLine->getType());
		pPointGeode->setLineData(pLine);
		pPointGeode->setVertexArray(pLine->getVertexArray());
		pPointGeode->setVertexIndex(pPointsNode->getVertexIndex());
		pPointGeode->setColorArray(pLine->getColorArray());
		pPointGeode->setColorIndex(pPointsNode->getColorIndex());
		pPointGeode->setFlagArray(pLine->getFlagArray());
		pPointGeode->setFlagIndex(pPointsNode->getFlagIndex());

		(xBase >= 1.0) ? pPointGeode->m_xCoordBase = xBase * m_xBase : pPointGeode->m_xCoordBase = 0.0f;
		(yBase >= 1.0) ? pPointGeode->m_yCoordBase = yBase * m_yBase : pPointGeode->m_yCoordBase = 0.0f;

		pPointGeode->init();

		//insert the pointGeode into pointsNode
		pPointsNode->insertPointGeode(pPointGeode);
		pPointsNode->addChild(pPointGeode);
	}

	pPointsNode->setXBase(xBase * m_xBase);
	pPointsNode->setYBase(yBase * m_yBase);

	//初始化时设置地形拉伸系数
	pPointsNode->setTerrainScale(m_terrainScaleTransform);
	pPointsNode->init();

	//根据x、y坐标基数为变换矩阵的偏移量设置
	osg::ref_ptr<osg::MatrixTransform> pMatrixTransform = new osg::MatrixTransform();
	pMatrixTransform->setMatrix(osg::Matrix::translate(xBase * m_xBase, yBase * m_yBase, m_depature));
	pMatrixTransform->addChild(pPointsNode);
	addChild(pMatrixTransform);

	//为cache添加x,y方向的偏移量，以方便如KL3DTerrainTileManager类计算瓦片包围盒等
	m_cache->setXOffset(pPointsNode->getXBase());
	m_cache->setYOffset(pPointsNode->getYBase());

	return pPointsNode;
}


KL3DLinesNode* KL3DDesignNode::createLinesNode(KL3DLineType type)
{
	osg::ref_ptr<KL3DLinesNode> pLinesNode = NULL;
	KL3DPointsNode* pPointsNode = NULL;
	if(type == KL3D_SHOTLINE)
	{
		pLinesNode = m_shotLinesNode;
		pPointsNode = m_shotPointsNode;
	}
	else if(type == KL3D_RCVLINE)
	{
		pLinesNode = m_rcvLinesNode;
		pPointsNode = m_rcvPointsNode;
	}

	if(m_isLinesNodeCreated)
	{
		return pLinesNode;
	}

	//set the base information to pLinesNode
	pLinesNode = new KL3DLinesNode();
	pLinesNode->setType(type);
	pLinesNode->setTerrainNode(m_terrainNode);
	pLinesNode->setTextureManager(m_textureManager);
	pLinesNode->setSourcePath(m_sourcePath);

	//add lineGeode to linesNode
	KL3DPointGeodeSet::iterator pointGeodeIter = pPointsNode->getPointGeodes()->begin();
	for(; pointGeodeIter != pPointsNode->getPointGeodes()->end(); pointGeodeIter++)
	{
		KL3DPointGeode* pPointGeode = pointGeodeIter->second;
		osg::ref_ptr<KL3DLineGeode> pLineGeode = new KL3DLineGeode();
		pLineGeode->setID(pPointGeode->getID());
		pLineGeode->setType(pPointGeode->getType());
		pLineGeode->setVertexArray(pPointGeode->getVertexArray());
		pLineGeode->setXCoordBase(pPointGeode->m_xCoordBase);
		pLineGeode->setYCoordBase(pPointGeode->m_yCoordBase);

		pLineGeode->setVertexIndex(pLinesNode->getVertexIndex());
		pLineGeode->setColorIndex(pLinesNode->getColorIndex());

		pLineGeode->init();
		pLineGeode->setIsDisplay(false);

		pLinesNode->insertLineGeode(pLineGeode);
		pLinesNode->addChild(pLineGeode);
	}
	pLinesNode->setXBase(pPointsNode->getXBase());
	pLinesNode->setYBase(pPointsNode->getYBase());

	//初始化时设置地形拉伸系数
	pLinesNode->setTerrainScale(m_terrainScaleTransform);
	pLinesNode->init();

	//根据x,y坐标基数为变化矩阵的偏移量
	osg::ref_ptr<osg::MatrixTransform> pMatrixTransform = new osg::MatrixTransform();
	pMatrixTransform->setMatrix(osg::Matrix::translate(pLinesNode->getXBase(), pLinesNode->getYBase(), m_depature));
	pMatrixTransform->addChild(pLinesNode);
	addChild(pMatrixTransform);

	return pLinesNode;

}


void KL3DDesignNode::notifyAddTextureManager(KL3DTextureManager* pTextureManager)
{
	m_shotPointsNode->notifyAddTextureManager(pTextureManager);
	m_rcvPointsNode->notifyAddTextureManager(pTextureManager);

	m_shotLinesNode->notifyAddTextureManager(pTextureManager);
	m_rcvLinesNode->notifyAddTextureManager(pTextureManager);
}