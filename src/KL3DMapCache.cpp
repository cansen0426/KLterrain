#include "KL3DMapCache.h"

KL3DMapCache::KL3DMapCache():
	m_id(""),
	m_editPoints(0),
	m_shotLines(new KL3DLineSet()),
	m_rcvLines(new KL3DLineSet()),
	m_xOffset(0.0f),
	m_yOffset(0.0f),
	m_depature(0.0),
	m_xMoveOffset(0.0),
	m_yMoveOffset(0.0)
{

}


KL3DMapCache::~KL3DMapCache()
{
	KL3DLine* pDel = NULL;

	//delete shotLine
	KL3DLineSet::iterator shotLineIter = m_shotLines->begin();
	while(shotLineIter != m_shotLines->end())
	{
		pDel = shotLineIter->second;
		delete pDel;

		pDel = NULL;

		m_shotLines->erase(shotLineIter);
		shotLineIter = m_shotLines->begin();
	}
	delete m_shotLines;
	m_shotLines = NULL;

	//delete rcvline
	KL3DLineSet::iterator rcvLineIter = m_rcvLines->begin();
	while(rcvLineIter != m_rcvLines->end())
	{
		pDel = rcvLineIter->second;
		delete pDel;
		pDel = NULL;

		m_rcvLines->erase(rcvLineIter);
		rcvLineIter = m_rcvLines->begin();
	}

	delete m_rcvLines;
	m_rcvLines = NULL;
}


void KL3DMapCache::setID(const std::string& id)
{
	m_id = id;
}


std::string KL3DMapCache::getID() const
{
	return m_id;
}


KL3DLineSet* KL3DMapCache::getShotLineSet()
{
	return m_shotLines;
}


KL3DLineSet* KL3DMapCache::getRcvLineSet()
{
	return m_rcvLines;
}


KL3DEditPointSet* KL3DMapCache::getEditPoints()
{
	return &m_editPoints;
}


KL3DEditLineSet* KL3DMapCache::getEditLines()
{
	return &m_editLines;
}


bool KL3DMapCache::insertLine(KL3DLine* pLine)
{
	double lineID = pLine->getID();
	KL3DLineType lineType = pLine->getType();

	KL3DLineSet* pLines = NULL;
	if(lineType == KL3D_SHOTLINE)
	{
		pLines = m_shotLines;
	}
	else
	{
		pLines = m_rcvLines;
	}

	KL3DLineSet::iterator lineIter = pLines->find(lineID);
	if(lineIter == pLines->end())
	{
		if(lineType == KL3D_SHOTLINE)
		{
			m_shotLines->insert(std::make_pair(lineID, pLine));
		}
		else
		{
			m_rcvLines->insert(std::make_pair(lineID, pLine));
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool KL3DMapCache::deleteLine(KL3DLine* pLine)
{
	double id = pLine->getID();
	KL3DLineType type = pLine->getType();

	KL3DLineSet* pLines = NULL;
	if(type == KL3D_SHOTLINE)
	{
		pLines = m_shotLines;
	}
	else
	{
		pLines = m_rcvLines;
	}

	pLines->erase(id);
	delete pLine;
	pLine = NULL;

	return true;
}


KL3DLine* KL3DMapCache::getLine(double id, KL3DLineType type)
{
	KL3DLine* pLine = NULL;

	KL3DLineSet::iterator iterLine;
	if(type == KL3D_SHOTLINE)
	{
		iterLine = m_shotLines->find(id);
		if(iterLine == m_shotLines->end())
		{
			return NULL;
		}
	}
	else
	{
		iterLine = m_rcvLines->find(id);
		if(iterLine == m_rcvLines->end())
		{
			return NULL;
		}
	}

	pLine = iterLine->second;
	return pLine;
}


KL3DPoint* KL3DMapCache::get3DPoint(const double& lineID, const double& pointID, const short& samestakeID, KL3DLineType lineType)
{
	//得到对应的线
	KL3DLine* p3DLine = getLine(lineID, lineType);

	//得到点
	KL3DPoint* p3DPoint = p3DLine->getPoint(pointID, samestakeID);

	return p3DPoint;
}


bool KL3DMapCache::insertEditPoint(KL3DEditPoint pEditPoint)
{
	m_editPoints.push_back(pEditPoint);
	return true;
}


bool KL3DMapCache::insertEditLine(KL3DLine* pLine)
{
	m_editLines.push_back(pLine);
	return true;
}


void KL3DMapCache::clearEditData()
{
	m_editPoints.clear();
	m_editLines.clear();
}


bool KL3DMapCache::insertPatchSelPoint(KL3DEditPoint pPatchSelPoint)
{
	m_patchSelPoints.push_back(pPatchSelPoint);

	return true;
}


KL3DEditPointSet* KL3DMapCache::getPatchSelPoints()
{
	return &m_patchSelPoints;
}


KL3DEditPointSet* KL3DMapCache::getPatchDstPoints()
{
	return &m_patchDstPoints;
}


void KL3DMapCache::clearPatchPoints()
{
	m_patchSelPoints.clear();
	m_patchDstPoints.clear();
}


void KL3DMapCache::setXOffset(const float& xOffset)
{
	m_xOffset = xOffset;
}


void KL3DMapCache::setYOffset(const float& yOffset)
{
	m_yOffset = yOffset;
}


float KL3DMapCache::getXOffset() const
{
	return m_xOffset;
}


float KL3DMapCache::getYOffset() const
{
	return m_yOffset;
}


void KL3DMapCache::setXMoveOffset(double& offset)
{
	m_xMoveOffset = offset;
}


void KL3DMapCache::setYMoveOffset(double& offset)
{
	m_yMoveOffset = offset;
}


double KL3DMapCache::getXMoveOffset() const
{
	return m_xMoveOffset;
}


double KL3DMapCache::getYMoveOffset() const
{
	return m_yMoveOffset;
}


void KL3DMapCache::setDePature(const double& depature)
{
	m_depature = depature;
}


double KL3DMapCache::getDepature() const
{
	return m_depature;
}