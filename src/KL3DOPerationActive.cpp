#include "KL3DOPerationActive.h"

KL3DOperationActive::KL3DOperationActive(KL3DMapManager* pMapManager) :
	KL3DOperationBase(pMapManager)
{

}


KL3DOperationActive::~KL3DOperationActive()
{

}


void KL3DOperationActive::init()
{

}


void KL3DOperationActive::build()
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
			osg::Vec3Array* pColorArray = pLine->getColorArray();
			osg::FloatArray* pFlagArray = pLine->getFlagArray();
			osg::Vec3 color(1.0f, 1.0f, 1.0f);
			if(type == KL3D_SHOTLINE)
			{
				color = KL3D_SHOTPOINT_DEFAULTCOLOR;
			}
			else
			{
				color = KL3D_RCVPOINT_DEFAULTCOLOR;
			}

			//如果flag为0，表示为多属性显示，则根据函数指针从色标中获取该点对应的颜色值
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAttributeColorFunc pfn = p3DDesignNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(), tempColor.y(), tempColor.z());
			}

			(*pColorArray)[p3DPoint->getIndex()] = color;

			p3DPoint->setIsForbidden(false);
		}

		//p3DDesignNode->reDraw();
	}

	//设置选中的编辑线集合状态
	KL3DEditLineSet* pEditLLines = pCache->getEditLines();
	for(unsigned int i = 0; i < pEditLLines->size(); ++i)
	{
		KL3DLine* p3DLine = (*pEditLLines)[i];
		double id = p3DLine->getID();
		KL3DLineType type = p3DLine->getType();

		osg::Vec3 color(1.0f, 1.0f, 1.0f);
		if(type == KL3D_SHOTLINE)
		{
			color = KL3D_SHOTPOINT_DEFAULTCOLOR;
		}
		else
		{
			color = KL3D_RCVPOINT_DEFAULTCOLOR;
		}

		KL3DLineGeode* p3DLineGeode = p3DDesignNode->getLinesNode(type)->getLineGeode(id);
		p3DLineGeode->setColor(osg::Vec4(color, 0.0f));
		p3DLineGeode->setIsDisplay(p3DDesignNode->getLinesNode(type)->getIsDisplay());


		osg::Vec3Array* pColorArray = p3DLine->getColorArray();
		osg::FloatArray* pFlagArray = p3DLine->getFlagArray();

		KL3DPointVector* p3DPoints = p3DLine->getPointVector();
		for(unsigned int j = 0; j < pColorArray->size(); ++j)
		{
			KL3DPoint* p3DPoint = (*p3DPoints)[j];

			//如果flag为0，表示为多属性显示，则根据函数指针从色标中获取该点对应的颜色值
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAttributeColorFunc pfn = p3DDesignNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(), tempColor.y(), tempColor.z());
			}

			(*pColorArray)[p3DPoint->getIndex()] = color;
		}
		p3DLine->setIsForbidden(false);
	}
	p3DDesignNode->reDraw();
}