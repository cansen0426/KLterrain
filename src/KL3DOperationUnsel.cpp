#include "KL3DOperationUnsel.h"

KL3DOperationUnsel::KL3DOperationUnsel(KL3DMapManager* pMapManager) :
	KL3DOperationBase(pMapManager)
{

}


KL3DOperationUnsel::~KL3DOperationUnsel()
{

}


void KL3DOperationUnsel::build()
{
	//从MapManager中获取到编辑点集合，将其清除
	KL3DDesignNode* p3DDeignNode = m_mapManager->getMainDesignNode();
	KL3DMapCache* pCache = m_mapManager->getMainCache();

	//清空编辑点集合
	KL3DEditPointSet* pEditPoints = pCache->getEditPoints();
	clearAllEditPoints(pCache, p3DDeignNode, pEditPoints);

	//清空编辑线集合
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	clearAllEditLines(pCache, p3DDeignNode, pEditLines);

	//清空关系片选择点集合
	KL3DEditPointSet* pPatchSelPoints = pCache->getPatchSelPoints();
	clearAllEditPoints(pCache, p3DDeignNode, pPatchSelPoints);

	//清空关系片目标点集合
	KL3DEditPointSet* pPatchDstPoints = pCache->getPatchDstPoints();
	clearAllEditPoints(pCache, p3DDeignNode, pPatchDstPoints);
}


void KL3DOperationUnsel::clearAllEditPoints(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode, KL3DEditPointSet* pEditPoints)
{
	if(pEditPoints->size() != 0)
	{
		KL3DEditPointSet::iterator pointIter = pEditPoints->begin();
		for(; pointIter != pEditPoints->end(); ++pointIter)
		{
			KL3DEditPoint& pEditPoint = *pointIter;

			double id = pEditPoint.m_lineID;
			KL3DLineType type = pEditPoint.m_type;
			KL3DPoint* p3DPoint = pEditPoint.m_editPoint;

			//根据点的类型恢复不同的默认颜色
			osg::Vec3 color(1.0f, 1.0f, 1.0f);
			if(type == KL3D_SHOTLINE)
			{
				color = KL3D_SHOTPOINT_DEFAULTCOLOR;
			}
			else if(type == KL3D_RCVLINE)
			{
				color = KL3D_RCVPOINT_DEFAULTCOLOR;
			}

			KL3DLine* pLine = pCache->getLine(id, type);
			osg::Vec3Array* pColorArray = pLine->getColorArray();
			osg::FloatArray* pFlagArray = pLine->getFlagArray();

			//如果flag为0，表示为多属性显示，则根据函数指针从色标中获取该点对应的颜色值
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAtrributeColorFunc pfn = p3DDesingNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(),tempColor.y(),tempColor.z());
			}

			//判断点是否处于禁止状态
			if(p3DPoint->getIsForbidden() || pLine->getIsForbidden())
			{
				color = KL3D_POINT_FORBIDCOLOR;
			}

			(*pColorArray)[p3DPoint->getIndex()] = color;

			p3DPoint->setIsSelected(false);
		}
		p3DDesingNode->reDraw();
	}

	//清空编辑数组
	pEditPoints->clear();
}


void KL3DOperationUnsel::clearAllEditLines(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode,KL3DEditLineSet* pEditLines)
{
	if(pEditLines->empty())
	{
		return;
	}

	for(unsigned int i = 0; i < pEditLines->size(); i++)
	{
		KL3DLine* pLine = (*pEditLines)[i];
		double id = pLine->getID();
		KL3DLineType type = pLine->getType();

		//根据点的类型恢复不同的默认颜色
		osg::Vec3 color(1.0f, 1.0f, 1.0f);
		if(type == KL3D_SHOTLINE)
		{
			color = KL3D_SHOTPOINT_DEFAULTCOLOR;
		}
		else if(type == KL3D_RCVLINE)
		{
			color = KL3D_RCVPOINT_DEFAULTCOLOR;
		}

		KL3DLineGeode* p3DLineGeode = p3DDesingNode->getLinesNode(type)->getLineGeode(id);
		if(p3DLineGeode != NULL)
		{
			p3DLineGeode->setColor(osg::Vec4(color, 0.0f));
			p3DLineGeode->setIsDisplay(p3DDesingNode->getLinesNode(type)->getIsDisplay());
		}

		osg::Vec3Array* pColorArray = pLine->getColorArray();
		osg::FloatArray* pFlagArray = pLine->getFlagArray();

		KL3DPointVector* p3DPoints = pLine->getPointVector();
		for(unsigned int i = 0; i < p3DPoints->size(); i++)
		{
			KL3DPoint* p3DPoint = (*p3DPoints)[i];

			//如果flag为0，表示为多属性显示，则根据函数指针从色标中获取该点对应的颜色值
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAtrributeColorFunc pfn = p3DDesingNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(),tempColor.y(),tempColor.z());
			}

			//判断点是否处于禁止状态
			if(p3DPoint->getIsForbidden() || pLine->getIsForbidden())
			{
				color = KL3D_POINT_FORBIDCOLOR;
			}

			(*pColorArray)[p3DPoint->getIndex()] = color;
		}
			pLine->setIsSelected(false);
	}

	p3DDesingNode->reDraw();
	pEditLines->clear();
}