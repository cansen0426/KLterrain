#include "KL3DOperationForbid.h"

KL3DOperationForbid::KL3DOperationForbid(KL3DMapManager* pMapManager) :
	KL3DOperationBase(pMapManager)
{

}


KL3DOperationForbid::~KL3DOperationForbid()
{

}


void KL3DOperationForbid::init()
{

}


void KL3DOperationForbid::build()
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
			double id  = editPoint.m_lineID;
			KL3DLineType type = editPoint.m_type;
			KL3DPoint* p3DPoint = editPoint.m_editPoint;

			KL3DLine* pLine = pCache->getLine(id,type);
			osg::Vec3Array* pColorArray = pLine->getColorArray();
			(*pColorArray)[p3DPoint->getIndex()] = KL3D_POINT_FORBIDCOLOR;

			p3DPoint->setIsForbidden(true);
		}

		//p3DDesignNode->reDraw();
	}


	//设置选中编辑线集合的状态
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	for(unsigned int i = 0; i < pEditLines->size(); ++i)
	{
		KL3DLine* p3DLine = (*pEditLines)[i];
		osg::Vec3Array* pColorArray = p3DLine->getColorArray();
		for(unsigned int j = 0; j < pColorArray->size(); ++j)
		{
			(*pColorArray)[j] = KL3D_POINT_FORBIDCOLOR;
		}

		KL3DLineGeode* p3DLineGeode = p3DDesignNode->getLinesNode(p3DLine->getType())->getLineGeode(p3DLine->getID());
		osg::Vec3 color = p3DLine->getType() == KL3D_SHOTLINE ? KL3D_SHOTPOINT_DEFAULTCOLOR : KL3D_RCVPOINT_DEFAULTCOLOR;
		p3DLineGeode->setColor(osg::Vec4(color,0.0f));
		p3DLineGeode->setIsDisplay(p3DDesignNode->getLinesNode(p3DLine->getType())->getIsDisplay());

		p3DLine->setIsForbidden(true);
	}

	p3DDesignNode->reDraw();
}