#include "KL3DOperationDelete.h"

KL3DOperationDelete::KL3DOperationDelete(KL3DMapManager* pMapManager):
	KL3DOperationBase(pMapManager)
{

}


KL3DOperationDelete::~KL3DOperationDelete()
{

}


void KL3DOperationDelete::init()
{

}


void KL3DOperationDelete::build()
{
	//获取MapCache对象
	KL3DMapCache* pCache = m_mapManager->getMainCache();
	KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();

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
			KL3DLine* pLine = pCache->getLine(id, type);

			//call tne delete edit point func
			deleteEditPoint(p3DPoint,pLine);
		}
	}
	pEditPointSet->clear();

	//设置选中编辑线集合的状态
	KL3DEditLineSet* p3DLines =pCache->getEditLines();
	for(unsigned int i = 0; i < p3DLines->size(); ++i)
	{
		KL3DLine* p3dLine = (*p3DLines)[i];
		//删除线号标识
		KL3DLineGeode* p3DLineGeode = p3DDesignNode->getLinesNode(p3dLine->getType())->getLineGeode(p3dLine->getID());
		p3DLineGeode->deleteLineLabel();

		deleteEditLine(p3dLine);
	}

	//重绘观测系统节点
	p3DDesignNode->reDraw();
	p3DLines->clear();
}


/*
void KL3DOperationDelete::deleteEditPoint(KL3DPoint* pDelPoint, KL3DLine* pLine)
{
	//1.clear the KL3DPoint stored in map of KL3DLine
	unsigned int indexDel = pDelPoint->getIndex();

	KL3DPointVector* pPointsVector = pLine->getPointVector();
	KL3DPointVector::iterator iterDelPointVector = pPointsVector->begin();
	while(iterDelPointVector != pPointsVector->end())
	{
		if(((*iterDelPointVector)->getID() == pDelPoint->getID()) && ((*iterDelPointVector)->getSameStakeID() == pDelPoint->getSameStakeID()))
		{
			pPointsVector->erase(iterDelPointVector);
			break;
		}
		iterDelPointVector++;
	}
	delete pDelPoint;

	//2.construct the vertexArray & colorArray & flagArray
	osg::Vec3Array* pVertexArray = pLine->getVertexArray();
	osg::Vec3Array* pColorArray = pLine->getColorArray();
	osg::FloatArray* pFlagArray = pLine->getFlagArray();
	unsigned int size = pVertexArray->size();

	osg::ref_ptr<osg::Vec3Array> pNewVertexArray = new osg::Vec3Array();
	osg::ref_ptr<osg::Vec3Array> pNewColorArray = new osg::Vec3Array();
	osg::ref_ptr<osg::FloatArray> pNewFlagArray = new osg::FloatArray();

	for(unsigned int i = 0; i < pVertexArray->size(); ++i)
	{
		if(i != indexDel)
		{
			pNewVertexArray->push_back((*pVertexArray)[i]);
			pNewColorArray->push_back((*pColorArray)[i]);
			pNewFlagArray->push_back((*pFlagArray)[i]);
			(*pPointsVector)[pNewVertexArray->size() - 1]->setIndex(pNewVertexArray->size() - 1);
		}
	}
	
	pLine->setVertexArray(pNewVertexArray);
	pLine->setColorArray(pNewColorArray);
	pLine->setFlagArray(pNewFlagArray);

	KL3DPointsNode* pPointsNode = m_mapManager->getMainDesignNode()->getPointsNode(pLine->getType());
	KL3DPointGeode* pPointGeode = pPointsNode->getPointGeode(pLine->getID());
	pPointGeode->setVertexArray(pLine->getVertexArray());
	pPointGeode->setColorArray(pLine->getColorArray());
	pPointGeode->setFlagArray(pLine->getFlagArray());
	pPointGeode->reBindingArray();

	KL3DLinesNode* pLinesNode = m_mapManager->getMainDesignNode()->getLinesNode(pPointGeode->getType());
	KL3DLineGeode* pLineGeode = pLinesNode->getLineGeode(pPointGeode->getID());
	pLineGeode->setVertexArray(pPointGeode->getVertexArray());
	pLineGeode->reBindingArray();
}*/


void KL3DOperationDelete::deleteEditPoint(KL3DPoint* pDelPoint, KL3DLine* pLine)
{
	//1.clear the KL3DPoint stored in map of KL3DLine
	unsigned int indexDel = pDelPoint->getIndex();

	KL3DPointVector* pPointsVector = pLine->getPointVector();
	KL3DPointVector::iterator iterDelPointVector = pPointsVector->begin();
	while(iterDelPointVector != pPointsVector->end())
	{
		if(((*iterDelPointVector)->getID() == pDelPoint->getID()) && ((*iterDelPointVector)->getSameStakeID() == pDelPoint->getSameStakeID()))
		{
			iterDelPointVector = pPointsVector->erase(iterDelPointVector);
			break;
		}
		iterDelPointVector++;
	}
	delete pDelPoint;
	//找到删除的点后，将删除点后边的点的index减1（即后边的点的索引号向前移动一位）
	for(; iterDelPointVector != pPointsVector->end(); iterDelPointVector++)
	{
		(*iterDelPointVector)->setIndex((*iterDelPointVector)->getIndex() - 1);
	}

	//2.construct the vertexArray & colorArray & flagArray
	osg::Vec3Array* pVertexArray = pLine->getVertexArray();
	osg::Vec3Array* pColorArray = pLine->getColorArray();
	osg::FloatArray* pFlagArray = pLine->getFlagArray();

	osg::Vec3Array::iterator pDelVertexVec = pVertexArray->begin() + indexDel;
	pVertexArray->erase(pDelVertexVec);
	osg::Vec3Array::iterator pDelColorVec = pColorArray->begin() + indexDel;
	pColorArray->erase(pDelColorVec);
	osg::FloatArray::iterator pDelFlagVec = pFlagArray->begin() + indexDel;
	pFlagArray->erase(pDelFlagVec);

}


void KL3DOperationDelete::deleteEditLine(KL3DLine* pLine)
{
	KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();
	p3DDesignNode->deleteGeode(pLine->getType(), pLine->getID());

	KL3DMapCache* pCache = m_mapManager->getMainCache();
	pCache->deleteLine(pLine);
}