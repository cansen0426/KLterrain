#include "KL3DLine.h"


KL3DLine::KL3DLine():
	m_id(0),
	m_isSelected(false),
	m_isForbidden(false),
	m_vertexArray(new osg::Vec3Array()),
	m_colorArray(new osg::Vec3Array()),
	m_flagArray(new osg::FloatArray()),
	m_pointsVector(new KL3DPointVector())
{

}


KL3DLine::~KL3DLine()
{
	KL3DPoint* pDel = NULL;
	KL3DPointVector::iterator pointsIter = m_pointsVector->begin();
	for(unsigned int i = 0; i < m_pointsVector->size(); ++i)
	{
		pDel = (*m_pointsVector)[i];
		delete pDel;
		pDel = NULL;
	}

	m_pointsVector->clear();
	delete m_pointsVector;
	m_pointsVector = NULL;
}


void KL3DLine::setID(const double& id)
{
	m_id = id;
}


double KL3DLine::getID() const
{
	return m_id;
} 


void KL3DLine::setType(KL3DLineType type)
{
	m_type = type;
}


KL3DLineType KL3DLine::getType() const
{
	return m_type;
}


void KL3DLine::setIsSelected(bool isSelected)
{
	 m_isSelected = isSelected;
}


bool KL3DLine::getIsSelected() const
{
	return m_isSelected;
}


void KL3DLine::setIsForbidden(bool isForbidden)
{
	m_isForbidden = isForbidden;
}


bool KL3DLine::getIsForbidden() const
{
	return m_isForbidden;
}


bool KL3DLine::insertPoint(KL3DPoint* pPoint)
{
	float pointID = pPoint->getID();
	m_pointsVector->push_back(pPoint);

	return true;
}


KL3DPoint* KL3DLine::getPoint(const double& pointID, const short& samestakeID)
{
	KL3DPointVector::iterator pointIter = m_pointsVector->begin();
	while(pointIter != m_pointsVector->end())
	{
		KL3DPoint* p3DPoint = *pointIter;
		if((p3DPoint->getID() == pointID) && (p3DPoint->getSameStakeID() == samestakeID))
		{
			return p3DPoint;
		}
		pointIter++;

	}

	return NULL;
}


KL3DPointVector* KL3DLine::getPointVector()
{
	return m_pointsVector;
}


void KL3DLine::setVertexArray(osg::ref_ptr<osg::Vec3Array> pVertexArray)
{
	m_vertexArray = pVertexArray;
}


osg::Vec3Array* KL3DLine::getVertexArray()
{
	return m_vertexArray;
}


void KL3DLine::setColorArray(osg::ref_ptr<osg::Vec3Array> pColorArray)
{
	m_colorArray = pColorArray;
}


osg::Vec3Array* KL3DLine::getColorArray()
{
	return m_colorArray;
}


void KL3DLine::setFlagArray(osg::ref_ptr<osg::FloatArray> pFlagArray)
{
	m_flagArray = pFlagArray;
}


osg::FloatArray* KL3DLine::getFlagArray()
{
	return m_flagArray;
}