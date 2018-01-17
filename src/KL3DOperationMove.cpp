#include "KL3DOperationMove.h"

KL3DOperationMove::KL3DOperationMove(KL3DMapManager* pMapManager, const osg::Vec3& offset) :
	KL3DOperationBase(pMapManager),
	m_distanceOffset(offset)
{

}


KL3DOperationMove::~KL3DOperationMove()
{

}


void KL3DOperationMove::build()
{
	//获取MapCache对象，设置选中编辑点集合
	KL3DMapCache* pCache = m_mapManager->getMainCache();
	KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();
	double x = m_distanceOffset.x();
	double y = m_distanceOffset.y();
	pCache->setXMoveOffset(x);
	pCache->setYMoveOffset(y);

	//设置选中编辑点集合的状态
	KL3DEditPointSet* pEditPointSet = pCache->getEditPoints();
	if(pEditPointSet->size() != 0)
	{
		KL3DEditPointSet::iterator iterEditPoint = pEditPointSet->begin();
		for(; iterEditPoint != pEditPointSet->end(); ++iterEditPoint)
		{
			KL3DEditPoint editPoint = *iterEditPoint;
			double id = editPoint.m_lineID;
			KL3DLineType type = editPoint.m_type;
			KL3DPoint* p3DPoint = editPoint.m_editPoint;
			p3DPoint->setCoord(p3DPoint->getCoord() + m_distanceOffset);

			KL3DLine* pLine = pCache->getLine(id, type);
			osg::Vec3Array* pVertexArray = pLine->getVertexArray();
			(*pVertexArray)[p3DPoint->getIndex()] += m_distanceOffset;
		}
	}

	//设置选中编辑线集合的状态
	KL3DEditLineSet* p3DLines = pCache->getEditLines();
	for(unsigned int i = 0; i < p3DLines->size(); ++i)
	{
		KL3DLine* p3DLine = (*p3DLines)[i];
		osg::Vec3Array* pVertexArray = p3DLine->getVertexArray();
		KL3DPointVector* p3DPoints = p3DLine->getPointVector();
		for(unsigned int j = 0; j < p3DPoints->size(); ++j)
		{
			KL3DPoint* p3DPoint = (*p3DPoints)[j];
			p3DPoint->setCoord(p3DPoint->getCoord() + m_distanceOffset);
			(*pVertexArray)[p3DPoint->getIndex()] += m_distanceOffset;
		}
	}

	p3DDesignNode->reDraw();
}