#include <omp.h>
#include <iostream>
#include <math.h>
#include "KL3DOperationSel.h"

KL3DOperationSel::KL3DOperationSel(KL3DMapManager* pMapManager, KL3DSelExtent* pSelExtent) :
		KL3DOperationBase(pMapManager),
		m_selExtents(pSelExtent),
		m_editObject(pMapManager->getEditObject())
{

}


KL3DOperationSel::~KL3DOperationSel()
{

}


void KL3DOperationSel::init()
{

}


void KL3DOperationSel::build()
{
	//��ȡ��ʾ�ڵ�
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();

	//�������£���������������ѡ�����
	KL3DMapCache* pCache = m_mapManager->getMainCache();

	//���߽��б���
	KL3DLineSet* pLines = NULL;
	if(m_editObject == KL3D_SHOTPOINT_EDIT && pDesignNode->getPointsNode(KL3D_SHOTLINE)->getIsVisible() && pDesignNode->getIsVisble())
	{
		pLines = pCache->getShotLineSet();
		if(m_selExtents->getIsPtSel())
			selPointByOmpForPtClick(pCache, pLines);
		else
			selPointByOmp(pCache, pLines);
	}
	else if(m_editObject == KL3D_RCVPOINT_EDIT && pDesignNode->getPointsNode(KL3D_RCVLINE)->getIsVisible() && pDesignNode->getIsVisble())
	{
		pLines = pCache->getRcvLineSet();
		if(m_selExtents->getIsPtSel())
			selPointByOmpForPtClick(pCache, pLines);
		else
			selPointByOmp(pCache, pLines);
	}
	else if(m_editObject == KL3D_POINT_EDIT && pDesignNode->getIsVisble())
	{
		long beginTime = clock();
		if(pDesignNode->getPointsNode(KL3D_SHOTLINE)->getIsVisible() && pDesignNode->getPointsNode(KL3D_RCVLINE)->getIsVisible())
		{
			pLines = pCache->getShotLineSet();
			KL3DLineSet* pLines2 = pCache->getRcvLineSet();
			if(m_selExtents->getIsPtSel())
			{
				selPointByOmpForPtClick(pCache, pLines, pLines2);
			}
				
			else
			{
				selPointByOmp(pCache, pLines);
				selPointByOmp(pCache, pLines2);
			}
		}
		else if(pDesignNode->getPointsNode(KL3D_SHOTLINE)->getIsVisible())
		{
			pLines = pCache->getShotLineSet();
			if(m_selExtents->getIsPtSel())
				selPointByOmpForPtClick(pCache, pLines);
			else
				selPointByOmp(pCache, pLines);
		}
		else if(pDesignNode->getPointsNode(KL3D_RCVLINE)->getIsVisible())
		{
			pLines = pCache->getRcvLineSet();
			if(m_selExtents->getIsPtSel())
				selPointByOmpForPtClick(pCache, pLines);
			else
				selPointByOmp(pCache, pLines);
		}

		std::cout<<"sel point use time:"<<clock() - beginTime <<"ms"<<std::endl;
	}
	else if(m_editObject == KL3D_SHOTLINE_EDIT)
	{
		pLines = pCache->getShotLineSet();
		if(m_selExtents->getIsPtSel())
			selLineByOmpForPtClick(pCache, pLines);
		else
			selLineByOmp(pCache, pLines);
	}
	else if(m_editObject == KL3D_RCVLINE_EDIT)
	{
		pLines = pCache->getRcvLineSet();
		if(m_selExtents->getIsPtSel())
			selLineByOmpForPtClick(pCache, pLines);
		else
			selLineByOmp(pCache, pLines);
	}
	else if(m_editObject == KL3D_LINE_EDIT)
	{
		long beginTime = clock();
		pLines = pCache->getShotLineSet();
		KL3DLineSet* pLines2 = pCache->getRcvLineSet();
		if(m_selExtents->getIsPtSel())
		{
			selLineByOmpForPtClick(pCache, pLines, pLines2);
		}	
		else
		{
			selLineByOmp(pCache, pLines);
			selLineByOmp(pCache, pLines2);
		}
			
		std::cout<<"sel Line use time:"<<clock() - beginTime <<"ms"<<std::endl;
	}
}


void KL3DOperationSel::selPoint(KL3DMapCache* pCache, KL3DLineSet* pLines)
{
	KL3DLineSet::iterator lineIter = pLines->begin();
	for(; lineIter != pLines->end(); ++lineIter)
	{
		KL3DLine* pLine = lineIter->second;
		//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

		KL3DPointVector* pPoints = pLine->getPointVector();
		KL3DPointVector::iterator pointIter = pPoints->begin();
		for(; pointIter != pPoints->end(); ++pointIter)
		{
			KL3DPoint* pPoint = *pointIter;

			//��ȡ������꣬Ȼ������ж�
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);
			if(m_mapManager->getMainTextureManager()) //���ڵ�������½���Ļ����ת��Ϊ������ꣿ
			{
				if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
				{
					pPoint->setIsSelected(true);
					osg::Vec3Array* pColorArray = pLine->getColorArray();
					unsigned int index = pPoint->getIndex();
					(*pColorArray)[index] = KL3D_POINT_SELCOLOR;

					KL3DEditPoint editPoint;
					editPoint.m_lineID = pLine->getID();
					editPoint.m_type = pLine->getType();
					editPoint.m_editPoint = pPoint;

					pCache->insertEditPoint(editPoint);
				}
			}
			else  //���β����ڵ�����½��������ת������Ļ���ꣿ
			{
				if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
				{
					pPoint->setIsSelected(true);
					osg::Vec3Array* pColorArray = pLine->getColorArray();
					unsigned int index = pPoint->getIndex();
					(*pColorArray)[index] = KL3D_POINT_SELCOLOR;

					KL3DEditPoint editPoint;
					editPoint.m_lineID = pLine->getID();
					editPoint.m_type = pLine->getType();
					editPoint.m_editPoint = pPoint;

					pCache->insertEditPoint(editPoint);
				}
			}

		}

	}

	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();
	pDesignNode->reDraw();
}


void KL3DOperationSel::selPointByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines)
{
	KL3DLineSet::iterator lineIter = pLines->begin();
	std::vector<KL3DLine*> lineVector;
	for(; lineIter != pLines->end(); ++lineIter)
	{
		lineVector.push_back(lineIter->second);
	}
	std::vector<KL3DLine*>::iterator lineVectorIter = lineVector.begin();

	//���ò����߳�����
	int procsNum = omp_get_num_procs();
	omp_set_num_threads(procsNum);
	//������������Ų���ѡ��õ��ĵ�
	std::vector<std::vector<KL3DEditPoint>> ompEditVector;
	for(int i = 0; i < procsNum; i++)
	{
		std::vector<KL3DEditPoint> editVector;
		ompEditVector.push_back(editVector);
	}
	//�õ�ÿ�������߳���Ҫ����ĸ���
	int blockNum = lineVector.size()/procsNum;
	int j, pos, vectorNum;
#pragma omp parallel for private(j, pos, vectorNum)
	for(int i = 0; i < procsNum; i++)
	{
		pos = i*blockNum;
		vectorNum = i;
	
		for(j = 0; j < blockNum; j++,pos++)
		{
			KL3DLine* pLine =*(lineVectorIter + pos);
			//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

			KL3DPointVector* pPoints = pLine->getPointVector();
			KL3DPointVector::iterator pointIter = pPoints->begin();
			for(; pointIter != pPoints->end(); ++pointIter)
			{
				KL3DPoint* pPoint = *pointIter;

				//��ȡ������꣬Ȼ������ж�
				osg::Vec3f coord = pPoint->getCoord();
				osg::Vec3 windowCoord = localToScreen(coord);

				if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
				{
					pPoint->setIsSelected(true);
					osg::Vec3Array* pColorArray = pLine->getColorArray();
					unsigned int index = pPoint->getIndex();
					(*pColorArray)[index] = KL3D_POINT_SELCOLOR;

					KL3DEditPoint editPoint;
					editPoint.m_lineID = pLine->getID();
					editPoint.m_type = pLine->getType();
					editPoint.m_editPoint = pPoint;

					ompEditVector[vectorNum].push_back(editPoint);
				}
			}

		}
	}

	for(unsigned int i = 0; i < ompEditVector.size(); i++)
	{
		for(unsigned int j = 0; j < ompEditVector[i].size(); j++)
		{
			pCache->insertEditPoint(ompEditVector[i][j]);
		}
		ompEditVector[i].clear();
	}
	ompEditVector.clear();

	//�Զ���Ĳ��ֽ��д���
	for(int pos = procsNum*blockNum; pos < lineVector.size(); pos++)
	{
		KL3DLine* pLine =*(lineVectorIter + pos);
		//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

		KL3DPointVector* pPoints = pLine->getPointVector();
		KL3DPointVector::iterator pointIter = pPoints->begin();
		for(; pointIter != pPoints->end(); ++pointIter)
		{
			KL3DPoint* pPoint = *pointIter;

			//��ȡ������꣬Ȼ������ж�
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);

			if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
			{
				pPoint->setIsSelected(true);
				osg::Vec3Array* pColorArray = pLine->getColorArray();
				unsigned int index = pPoint->getIndex();
				(*pColorArray)[index] = KL3D_POINT_SELCOLOR;

				KL3DEditPoint editPoint;
				editPoint.m_lineID = pLine->getID();
				editPoint.m_type = pLine->getType();
				editPoint.m_editPoint = pPoint;

				pCache->insertEditPoint(editPoint);
			}
		}
	}
	lineVector.clear();

	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();
	pDesignNode->reDraw();
}


void KL3DOperationSel::selPointByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 /* = NULL */)
{
	KL3DEditPoint pOnlyEditPt;
	osg::Vec3 pushToLocalCoor = m_selExtents->getPushToLocalCoor();

	KL3DEditPoint pOnlyEditPt1;
	bool isGetPt1 = false;
	KL3DEditPointSet pAllSelPoint1 = getAllEditPointByPtClick(pCache, pLines);
	if(pAllSelPoint1.size() != 0)
	{
		pOnlyEditPt1 = getEditPointByCoor(pushToLocalCoor,pAllSelPoint1);
		isGetPt1 = true;
	}
	pAllSelPoint1.clear();

	KL3DEditPoint pOnlyEditPt2;
	bool isGetPt2 = false;
	if(pLines2)
	{
		KL3DEditPointSet pAllSelPoint2 = getAllEditPointByPtClick(pCache, pLines2);
		if(pAllSelPoint2.size() != 0)
		{
			pOnlyEditPt2 = getEditPointByCoor(pushToLocalCoor,pAllSelPoint2);
			isGetPt2 = true;
		}
		pAllSelPoint2.clear();
	}

	bool isOnlyEditPtExist = false;
	if(isGetPt1 && isGetPt2)
	{
		KL3DEditPointSet pEditPtVec;
		pEditPtVec.push_back(pOnlyEditPt1);
		pEditPtVec.push_back(pOnlyEditPt2);

		pOnlyEditPt = getEditPointByCoor(pushToLocalCoor,pEditPtVec);
		isOnlyEditPtExist = true;
		pEditPtVec.clear();
	}
	else if(isGetPt1)
	{
		pOnlyEditPt = pOnlyEditPt1;
		isOnlyEditPtExist = true;
	}
	else if(isGetPt2)
	{
		pOnlyEditPt = pOnlyEditPt2;
		isOnlyEditPtExist = true;
	}


	//�������һ������뵽pcache�ı༭����,����ѡ����
	if(isOnlyEditPtExist)
	{
		pOnlyEditPt.m_editPoint->setIsSelected(true);
		osg::Vec3Array* pColorArray = pCache->getLine(pOnlyEditPt.m_lineID,pOnlyEditPt.m_type)->getColorArray();
		unsigned int index = pOnlyEditPt.m_editPoint->getIndex();
		(*pColorArray)[index] = KL3D_POINT_SELCOLOR;

		pCache->insertEditPoint(pOnlyEditPt);
	}

	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();
	pDesignNode->reDraw();
}


void KL3DOperationSel::selLine(KL3DMapCache* pCache, KL3DLineSet* pLines)
{
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();

	//����ȷ��ѡ������ĵ�
	KL3DLineSet::iterator lineIter = pLines->begin();
	for(; lineIter != pLines->end(); ++lineIter)
	{
		KL3DLine* pLine = lineIter->second;
		osg::Vec3Array* pVertexArray = pLine->getVertexArray();

		KL3DPointVector* pPoints = pLine->getPointVector();
		KL3DPointVector::iterator pointIter = pPoints->begin();
		for(;pointIter != pPoints->end(); ++pointIter) //�������е�ÿһ���㣬�����һ�����ڷ�Χ�ڣ���ôѡ�д�����
		{
			KL3DPoint* pPoint = *pointIter;

			//��ȡ������꣬Ȼ������ж�
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);

			if(m_selExtents->isInExtentWindow(windowCoord) && pLine->getIsSelected() == false)
			{
				pLine->setIsSelected(true);
				pCache->insertEditLine(pLine);

				break;
			}
		}
	}

	//��ѡ�е�����ɫ���øı�
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	for(unsigned int i = 0; i < pEditLines->size(); ++i)
	{
		KL3DLine* pLine = (*pEditLines)[i];
		osg::Vec3Array* pColorArray = pLine->getColorArray();
		for(unsigned int j = 0; j < pColorArray->size(); ++j)
		{
			(*pColorArray)[j] = KL3D_POINT_SELCOLOR;
		}

		KL3DLineGeode* pLineGeode = pDesignNode->getLinesNode(pLine->getType())->getLineGeode(pLine->getID());
		pLineGeode->setColor(osg::Vec4(KL3D_POINT_SELCOLOR, 0.0f));
		pLineGeode->setIsDisplay(true);

	}

	pDesignNode->reDraw();
}


void KL3DOperationSel::selLineByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines)
{
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();

	//����ȷ��ѡ������ĵ�
	KL3DLineSet::iterator lineIter = pLines->begin();

	std::vector<KL3DLine*> lineVector;
	for(; lineIter != pLines->end(); ++lineIter)
	{
		lineVector.push_back(lineIter->second);
	}
	std::vector<KL3DLine*>::iterator lineVectorIter = lineVector.begin();

	//���ò����߳�����
	int procsNum = omp_get_num_procs();
	omp_set_num_threads(procsNum);
	//������������Ų���ѡ��õ��ĵ�
	std::vector<std::vector<KL3DLine*>> ompEditVector;
	for(int i = 0; i < procsNum; i++)
	{
		std::vector<KL3DLine*> editVector;
		ompEditVector.push_back(editVector);
	}
	//�õ�ÿ�������߳���Ҫ����ĸ���
	int blockNum = lineVector.size()/procsNum;
	int j, pos, vectorNum;
#pragma omp parallel for private(j, pos, vectorNum)
	for(int i = 0; i < procsNum; i++)
	{
		pos = i*blockNum;
		vectorNum = i;

		for(j = 0; j < blockNum; j++,pos++)
		{
			KL3DLine* pLine =*(lineVectorIter + pos);
			//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

			KL3DPointVector* pPoints = pLine->getPointVector();
			KL3DPointVector::iterator pointIter = pPoints->begin();
			for(;pointIter != pPoints->end(); ++pointIter) //�������е�ÿһ���㣬�����һ�����ڷ�Χ�ڣ���ôѡ�д�����
			{
				KL3DPoint* pPoint = *pointIter;

				//��ȡ������꣬Ȼ������ж�
				osg::Vec3f coord = pPoint->getCoord();
				osg::Vec3 windowCoord = localToScreen(coord);

				if(m_selExtents->isInExtentWindow(windowCoord) && pLine->getIsSelected() == false)
				{
					pLine->setIsSelected(true);
					ompEditVector[vectorNum].push_back(pLine);

					break;
				}
			}
		}
	}

	for(unsigned int i = 0; i < ompEditVector.size(); i++)
	{
		for(unsigned int j = 0; j < ompEditVector[i].size(); j++)
		{
			pCache->insertEditLine(ompEditVector[i][j]);
		}
		ompEditVector[i].clear();
	}
	ompEditVector.clear();

	//�Զ���Ĳ������д���
	for(int pos = procsNum*blockNum; pos < lineVector.size(); pos++)
	{
		KL3DLine* pLine =*(lineVectorIter + pos);
		//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

		KL3DPointVector* pPoints = pLine->getPointVector();
		KL3DPointVector::iterator pointIter = pPoints->begin();
		for(;pointIter != pPoints->end(); ++pointIter) //�������е�ÿһ���㣬�����һ�����ڷ�Χ�ڣ���ôѡ�д�����
		{
			KL3DPoint* pPoint = *pointIter;

			//��ȡ������꣬Ȼ������ж�
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);

			if(m_selExtents->isInExtentWindow(windowCoord) && pLine->getIsSelected() == false)
			{
				pLine->setIsSelected(true);
				pCache->insertEditLine(pLine);

				break;
			}
		}
	}
	lineVector.clear();

	//��ѡ�е�����ɫ���øı�
	KL3DEditLineSet* pEditLines = pCache->getEditLines();
	for(unsigned int i = 0; i < pEditLines->size(); ++i)
	{
		KL3DLine* pLine = (*pEditLines)[i];
		osg::Vec3Array* pColorArray = pLine->getColorArray();
		for(unsigned int j = 0; j < pColorArray->size(); ++j)
		{
			(*pColorArray)[j] = KL3D_POINT_SELCOLOR;
		}

		KL3DLineGeode* pLineGeode = pDesignNode->getLinesNode(pLine->getType())->getLineGeode(pLine->getID());
		pLineGeode->setColor(osg::Vec4(KL3D_POINT_SELCOLOR, 0.0f));
		pLineGeode->setIsDisplay(true);

	}

	pDesignNode->reDraw();
}


void KL3DOperationSel::selLineByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 /* = NULL */)
{
	KL3DDesignNode* pDesignNode = m_mapManager->getMainDesignNode();

	KL3DEditPoint pOnlyEditPt;
	osg::Vec3 pushToLocalCoor = m_selExtents->getPushToLocalCoor();

	KL3DEditPoint pOnlyEditPt1;
	bool isGetPt1 = false;
	KL3DEditPointSet pAllSelPoint1 = getAllEditPointByPtClick(pCache, pLines);
	if(pAllSelPoint1.size() != 0)
	{
		pOnlyEditPt1 = getEditPointByCoor(pushToLocalCoor,pAllSelPoint1);
		isGetPt1 = true;
	}
	pAllSelPoint1.clear();

	KL3DEditPoint pOnlyEditPt2;
	bool isGetPt2 = false;
	if(pLines2)
	{
		KL3DEditPointSet pAllSelPoint2 = getAllEditPointByPtClick(pCache, pLines2);
		if(pAllSelPoint2.size() != 0)
		{
			pOnlyEditPt2 = getEditPointByCoor(pushToLocalCoor,pAllSelPoint2);
			isGetPt2 = true;
		}
		pAllSelPoint2.clear();
	}

	bool isOnlyEditPtExist = false;
	if(isGetPt1 && isGetPt2)
	{
		KL3DEditPointSet pEditPtVec;
		pEditPtVec.push_back(pOnlyEditPt1);
		pEditPtVec.push_back(pOnlyEditPt2);

		pOnlyEditPt = getEditPointByCoor(pushToLocalCoor,pEditPtVec);
		isOnlyEditPtExist = true;
		pEditPtVec.clear();
	}
	else if(isGetPt1)
	{
		pOnlyEditPt = pOnlyEditPt1;
		isOnlyEditPtExist = true;
	}
	else if(isGetPt2)
	{
		pOnlyEditPt = pOnlyEditPt2;
		isOnlyEditPtExist = true;
	}

	//�������һ�������ڵ��߲��뵽pcache�ı༭����,����ѡ����
	if(isOnlyEditPtExist)
	{
		KL3DLine* p3DLine = pCache->getLine(pOnlyEditPt.m_lineID,pOnlyEditPt.m_type);
		if(p3DLine->getIsSelected() == false)
		{
			p3DLine->setIsSelected(true);
			pCache->insertEditLine(p3DLine);

			osg::Vec3Array* pColorArray = p3DLine->getColorArray();
			for(unsigned int j = 0; j < pColorArray->size(); ++j)
			{
				(*pColorArray)[j] = KL3D_POINT_SELCOLOR;
			}

			KL3DLineGeode* pLineGeode = pDesignNode->getLinesNode(p3DLine->getType())->getLineGeode(p3DLine->getID());
			pLineGeode->setColor(osg::Vec4(KL3D_POINT_SELCOLOR, 0.0f));
			pLineGeode->setIsDisplay(true);
		}

	}

	pDesignNode->reDraw();
}


KL3DEditPointSet KL3DOperationSel::getAllEditPointByPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines)
{
	//���ڴ洢��ѡʱ��ѡ�е����е�
	KL3DEditPointSet pAllSelPoint;

	KL3DLineSet::iterator lineIter = pLines->begin();
	std::vector<KL3DLine*> lineVector;
	for(; lineIter != pLines->end(); ++lineIter)
	{
		lineVector.push_back(lineIter->second);
	}
	std::vector<KL3DLine*>::iterator lineVectorIter = lineVector.begin();

	//���ò����߳�����
	int procsNum = omp_get_num_procs();
	omp_set_num_threads(procsNum);
	//������������Ų���ѡ��õ��ĵ�
	std::vector<std::vector<KL3DEditPoint>> ompEditVector;
	for(int i = 0; i < procsNum; i++)
	{
		std::vector<KL3DEditPoint> editVector;
		ompEditVector.push_back(editVector);
	}
	//�õ�ÿ�������߳���Ҫ����ĸ���
	int blockNum = lineVector.size()/procsNum;
	int j, pos, vectorNum;
#pragma omp parallel for private(j, pos, vectorNum)
	for(int i = 0; i < procsNum; i++)
	{
		pos = i*blockNum;
		vectorNum = i;

		for(j = 0; j < blockNum; j++,pos++)
		{
			KL3DLine* pLine =*(lineVectorIter + pos);
			//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

			KL3DPointVector* pPoints = pLine->getPointVector();
			KL3DPointVector::iterator pointIter = pPoints->begin();
			for(; pointIter != pPoints->end(); ++pointIter)
			{
				KL3DPoint* pPoint = *pointIter;

				//��ȡ������꣬Ȼ������ж�
				osg::Vec3f coord = pPoint->getCoord();
				osg::Vec3 windowCoord = localToScreen(coord);

				if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
				{
					KL3DEditPoint editPoint;
					editPoint.m_lineID = pLine->getID();
					editPoint.m_type = pLine->getType();
					editPoint.m_editPoint = pPoint;

					ompEditVector[vectorNum].push_back(editPoint);
				}
			}

		}
	}

	for(unsigned int i = 0; i < ompEditVector.size(); i++)
	{
		for(unsigned int j = 0; j < ompEditVector[i].size(); j++)
		{
			pAllSelPoint.push_back(ompEditVector[i][j]);
		}
		ompEditVector[i].clear();
	}
	ompEditVector.clear();

	//�Զ���Ĳ��ֽ��д���
	for(int pos = procsNum*blockNum; pos < lineVector.size(); pos++)
	{
		KL3DLine* pLine =*(lineVectorIter + pos);
		//osg::Vec3Array* pVertexArray = pLine->getVertexArray();

		KL3DPointVector* pPoints = pLine->getPointVector();
		KL3DPointVector::iterator pointIter = pPoints->begin();
		for(; pointIter != pPoints->end(); ++pointIter)
		{
			KL3DPoint* pPoint = *pointIter;

			//��ȡ������꣬Ȼ������ж�
			osg::Vec3f coord = pPoint->getCoord();
			osg::Vec3 windowCoord = localToScreen(coord);

			if(m_selExtents->isInExtentWindow(windowCoord) && pPoint->getIsSelected() == false)
			{
				KL3DEditPoint editPoint;
				editPoint.m_lineID = pLine->getID();
				editPoint.m_type = pLine->getType();
				editPoint.m_editPoint = pPoint;

				pAllSelPoint.push_back(editPoint);
			}
		}
	}
	lineVector.clear();

	return pAllSelPoint;
}


KL3DEditPoint KL3DOperationSel::getEditPointByCoor(const osg::Vec3& pushToLocalCoor, KL3DEditPointSet& pAllSelPoint)
{
	KL3DEditPoint pOnlyEditPoint;
	double minDis = 1000000;
	double dis;
	KL3DEditPointSet::iterator iterEditPoint = pAllSelPoint.begin();
	for(;iterEditPoint != pAllSelPoint.end(); ++iterEditPoint)
	{
		KL3DEditPoint pEditPoint = *iterEditPoint;
		osg::Vec3 ptCoor = pEditPoint.m_editPoint->getCoord();

		dis = pow((double)((ptCoor.x()-pushToLocalCoor.x())*(ptCoor.x()-pushToLocalCoor.x()) +
			(ptCoor.y()-pushToLocalCoor.y())*(ptCoor.y()-pushToLocalCoor.y())), 0.5);

		if(dis < minDis)
		{
			pOnlyEditPoint = pEditPoint;
			minDis = dis;
		}
	}

	return pOnlyEditPoint;


}


osg::Vec3 KL3DOperationSel::localToScreen(const osg::Vec3& worldPoint)
{
	osg::Vec3 windowPoint;

	osgViewer::Viewer* pViewer = m_mapManager->getID();
	osg::Camera* camera = pViewer->getCamera();
	osg::Matrix modelViewMatrix = camera->getViewMatrix();
	osg::Matrix projectionMatrix = camera->getProjectionMatrix();
	osg::Matrix windowMatrix = camera->getViewport()->computeWindowMatrix();

	osg::Matrix MPW = modelViewMatrix * projectionMatrix * windowMatrix;

	osg::Vec3 temLocalPoint = worldPoint;
	/*temLocalPoint.z() *= m_mapManager->getTerrainScaleZ();*/
	//��Ϊû�ж�����Ŀ�ϲ㳡�صĵ��α仯����,����ʹ���Լ���������ϵ����Zֵ��
	temLocalPoint.z() /= m_mapManager->getMainDesignNode()->getPointsNode(KL3D_SHOTLINE)->getTerrainScale();
	temLocalPoint.x() *= m_mapManager->getTerrainScaleX();
	temLocalPoint.y() *= m_mapManager->getTerrainScaleY();



	windowPoint = temLocalPoint *MPW;

	return windowPoint;
}