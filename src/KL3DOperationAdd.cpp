#include "KL3DOperationAdd.h"

KL3DOperationAdd::KL3DOperationAdd(KL3DMapManager* pMapManager) :
	KL3DOperationBase(pMapManager)
	{

	}


KL3DOperationAdd::~KL3DOperationAdd()
{

}


void KL3DOperationAdd::init()
{

}


void KL3DOperationAdd::build()
{
	//��ȡMapCache����
	KL3DMapCache* pCache = m_mapManager->getMainCache();
	KL3DDesignNode* p3DDesignNode = m_mapManager->getMainDesignNode();
	float xBase = pCache->getXOffset();
	float yBase = pCache->getYOffset();

	//����ѡ�б༭�㼯�ϵ�״̬
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
			KL3DLine* pLine = pCache->getLine(id,type);

			//call the add edit point func
			addEditPoint(p3DPoint, pLine, xBase, yBase);
		}
	}
	pEditPointSet->clear();

	//����ѡ�б༭�߼��ϵ�״̬
	KL3DEditLineSet* pEditLineSet = pCache->getEditLines();
	if(pEditLineSet->size() != 0)
	{
		KL3DEditLineSet::iterator iterEditLine = pEditLineSet->begin();
		for(; iterEditLine != pEditLineSet->end(); ++iterEditLine)
		{
			KL3DLine* pEditLine = *iterEditLine;
			addEditLine(pEditLine, pCache, p3DDesignNode, xBase, yBase);
		}
	}
	pEditLineSet->clear();

	//�ػ�۲�ϵͳ�ڵ�
	p3DDesignNode->reDraw();
}


void KL3DOperationAdd::addEditPoint(KL3DPoint* pAddPoint, KL3DLine* pLine, const float& xBase /* = 0 */, const float& yBase /* = 0 */)
{
	osg::Vec3Array* pVertexArray = pLine->getVertexArray();
	osg::Vec3Array* pColorArray = pLine->getColorArray();
	osg::FloatArray* pFlagArray = pLine->getFlagArray();
	osg::Vec3 base(xBase, yBase, 0);
	osg::Vec3 color;
	if(pLine->getType() ==  KL3D_SHOTLINE)
	{
		color = KL3D_SHOTPOINT_DEFAULTCOLOR;
	}
	else
	{
		color = KL3D_RCVPOINT_DEFAULTCOLOR;
	}

	//1���ҵ�pAddPoint������
	bool isInsert = false;
	KL3DPointVector* p3DPointVector = pLine->getPointVector();
	for(int i = 0; i < p3DPointVector->size(); ++i)
	{
		if(pAddPoint->getID() < (*p3DPointVector)[i]->getID())
		{
			pAddPoint->setIndex(i);
			p3DPointVector->insert(p3DPointVector->begin() + i, pAddPoint);
			pVertexArray->insert(pVertexArray->begin() + i, pAddPoint->getCoord() - base);
			pColorArray->insert(pColorArray->begin() + i, color);
			pFlagArray->insert(pFlagArray->begin() + i, 1.0f);
			isInsert = true;
			break;
		}
		else if((pAddPoint->getID() == (*p3DPointVector)[i]->getID()) && (pAddPoint->getSameStakeID() < (*p3DPointVector)[i]->getSameStakeID()))
		{
			pAddPoint->setIndex(i);
			p3DPointVector->insert(p3DPointVector->begin() + i, pAddPoint);
			pVertexArray->insert(pVertexArray->begin() + i, pAddPoint->getCoord() - base);
			pColorArray->insert(pColorArray->begin() + i, color);
			pFlagArray->insert(pFlagArray->begin() + i, 1.0f);
			isInsert = true;
			break;
		}
	}

	//��������м���룬��˵���õ����ߵ����
	if(!isInsert)
	{
		pAddPoint->setIndex(p3DPointVector->size());
		p3DPointVector->push_back(pAddPoint);
		pVertexArray->push_back(pAddPoint->getCoord() - base);
		pColorArray->push_back(color);
		pFlagArray->push_back(1.0f);
	}

	//2��construct the vertexArray & colorArray & flagArray
	unsigned int size = pVertexArray->size();
	for(unsigned int i = 0; i < size; ++i)
	{
		(*p3DPointVector)[i]->setIndex(i);
	}
}


void KL3DOperationAdd::addEditLine(KL3DLine* pAddLine, KL3DMapCache* pCache, KL3DDesignNode* pDesignNode, const float& xBase /* = 0 */, const float& yBase /* = 0 */)
{
	//1���򷽰��������ά��
	pCache->insertLine(pAddLine);

	//2�����ɸ��߶�Ӧ�Ļ��ƽڵ�
	KL3DPointsNode* pPointsNode = pDesignNode->getPointsNode(pAddLine->getType());

	osg::ref_ptr<KL3DPointGeode> pPointGeode = new KL3DPointGeode();
	pPointGeode->setID(pAddLine->getID());
	pPointGeode->setType(pAddLine->getType());
	pPointGeode->setLineData(pAddLine);
	pPointGeode->setVertexArray(pAddLine->getVertexArray());
	pPointGeode->setVertexIndex(pPointsNode->getVertexIndex());
	pPointGeode->setColorArray(pAddLine->getColorArray());
	pPointGeode->setColorIndex(pPointsNode->getColorIndex());
	pPointGeode->setFlagArray(pAddLine->getFlagArray());
	pPointGeode->setFlagIndex(pPointsNode->getFlagIndex());

	pPointGeode->m_xCoordBase = xBase;
	pPointGeode->m_yCoordBase = yBase;

	pPointGeode->init();
	pPointsNode->insertPointGeode(pPointGeode);
	pPointsNode->addChild(pPointGeode);

	//3�����ɻ��ƽڵ���߽ڵ�
	KL3DLinesNode* pLinesNode = pDesignNode->getLinesNode(pAddLine->getType());

	osg::ref_ptr<KL3DLineGeode> pLineGeode = new KL3DLineGeode();
	pLineGeode->setID(pPointGeode->getID());
	pLineGeode->setType(pPointGeode->getType());
	pLineGeode->setVertexArray(pPointGeode->getVertexArray());
	pLineGeode->setXCoordBase(pPointGeode->m_xCoordBase);
	pLineGeode->setYCoordBase(pPointGeode->m_yCoordBase);

	pLineGeode->setVertexIndex(pLinesNode->getVertexIndex());
	pLineGeode->setColorIndex(pLinesNode->getColorIndex());

	pLineGeode->init();

	pLinesNode->insertLineGeode(pLineGeode);
	pLinesNode->addChild(pLineGeode);

	//������״̬�����Ƿ���ʾ�߽ڵ�
	pLineGeode->setIsDisplay(pLinesNode->getIsDisplay());
	//������״̬�����Ƿ���ʾ�߱�ע
	pLineGeode->setLineLabelIsVisible(pLinesNode->getLinesLabelIsVisible());



}