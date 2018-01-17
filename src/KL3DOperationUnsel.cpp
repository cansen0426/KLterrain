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
	//��MapManager�л�ȡ���༭�㼯�ϣ��������
	KL3DDesignNode* p3DDeignNode = m_mapManager->getMainDesignNode();
	KL3DMapCache* pCache = m_mapManager->getMainCache();

	//��ձ༭�㼯��
	KL3DEditPointSet* pEditPoints = pCache->getEditPoints();
	clearAllEditPoints(pCache, p3DDeignNode, pEditPoints);

	//��ձ༭�߼���
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	clearAllEditLines(pCache, p3DDeignNode, pEditLines);

	//��չ�ϵƬѡ��㼯��
	KL3DEditPointSet* pPatchSelPoints = pCache->getPatchSelPoints();
	clearAllEditPoints(pCache, p3DDeignNode, pPatchSelPoints);

	//��չ�ϵƬĿ��㼯��
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

			//���ݵ�����ͻָ���ͬ��Ĭ����ɫ
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

			//���flagΪ0����ʾΪ��������ʾ������ݺ���ָ���ɫ���л�ȡ�õ��Ӧ����ɫֵ
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAtrributeColorFunc pfn = p3DDesingNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(),tempColor.y(),tempColor.z());
			}

			//�жϵ��Ƿ��ڽ�ֹ״̬
			if(p3DPoint->getIsForbidden() || pLine->getIsForbidden())
			{
				color = KL3D_POINT_FORBIDCOLOR;
			}

			(*pColorArray)[p3DPoint->getIndex()] = color;

			p3DPoint->setIsSelected(false);
		}
		p3DDesingNode->reDraw();
	}

	//��ձ༭����
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

		//���ݵ�����ͻָ���ͬ��Ĭ����ɫ
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

			//���flagΪ0����ʾΪ��������ʾ������ݺ���ָ���ɫ���л�ȡ�õ��Ӧ����ɫֵ
			if((*pFlagArray)[p3DPoint->getIndex()] == 0.0f)
			{
				osg::Vec4 tempColor(1.0f, 1.0f, 1.0f, 1.0f);
				//mutiAtrributeColorFunc pfn = p3DDesingNode->getColorFunc();
				//pfn ? tempColor = pfn(id, p3DPoint->getID(), p3DPoint->getSameStakeID(), type == KL3D_SHOTLINE) : tempColor = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
				color = osg::Vec3(tempColor.x(),tempColor.y(),tempColor.z());
			}

			//�жϵ��Ƿ��ڽ�ֹ״̬
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