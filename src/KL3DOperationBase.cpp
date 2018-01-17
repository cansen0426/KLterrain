#include "KL3DOperationBase.h"

KL3DOperationBase::KL3DOperationBase()
{

}


KL3DOperationBase::KL3DOperationBase(KL3DMapManager* pMapManager) :
	m_mapManager(pMapManager)
{

}


KL3DOperationBase::~KL3DOperationBase()
{

}


void KL3DOperationBase::init()
{

}


void KL3DOperationBase::build()
{

}


//*******************KL3DSelExtent********************//

KL3DSelExtent::KL3DSelExtent() :
	m_upLeftCoord(osg::Vec3(0.0,0.0,0.0)),
	m_upRightCoord(osg::Vec3(0.0,0.0,0.0)),
	m_downRightCoord(osg::Vec3(0.0,0.0,0.0)),
	m_downLefeCoord(osg::Vec3(0.0,0.0,0.0)),
	m_windowXmin(FLT_MAX),
	m_windowXmax(FLT_MAX),
	m_windowYmin(FLT_MAX),
	m_windowYmax(FLT_MAX),
	m_screenArray(new osg::Vec2Array()),
	m_selectType(SEL_REC),
	m_isPtSel(false),
	m_pushToLocalCoor(osg::Vec3(0.0,0.0,0.0))
{

}


KL3DSelExtent::KL3DSelExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft) :
	m_upLeftCoord(upLeft),
	m_upRightCoord(upRight),
	m_downRightCoord(downRight),
	m_downLefeCoord(downLeft)
{

}


KL3DSelExtent::~KL3DSelExtent()
{
	
}


void KL3DSelExtent::setExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft)
{
	m_upLeftCoord = upLeft;
	m_upRightCoord = upRight;
	m_downRightCoord = downRight;
	m_downLefeCoord = downLeft;
}


void KL3DSelExtent::setExtentWindow(const float& xmin, const float& ymin, const float& xmax, const float& ymax)
{
	m_windowXmin = xmin;
	m_windowYmin = ymin;
	m_windowXmax = xmax;
	m_windowYmax = ymax;
}


void KL3DSelExtent::setPolygonExtentWindow(osg::Vec2Array* pscreenArray)
{
	m_screenArray->clear();
	for(unsigned int i = 0; i < pscreenArray->size(); i++)
	{
		osg::Vec2 temp ;
		temp.x() = (*pscreenArray)[i].x();
		temp.y() = (*pscreenArray)[i].y();

		m_screenArray->push_back(temp);
	}

	osg::Vec2 temp2;
	temp2.x() = (*pscreenArray)[0].x();
	temp2.y() = (*pscreenArray)[0].y();
	m_screenArray->push_back(temp2);
}


void KL3DSelExtent::setLocalExtent(osg::Vec3Array* plocalArray)
{
	osg::ref_ptr<osg::Vec3Array> pArray = new osg::Vec3Array();
	for(unsigned int i = 0; i < plocalArray->size(); i++)
	{
		osg::Vec3 temp;
		temp.x() = (*plocalArray)[i].x();
		temp.y() = (*plocalArray)[i].y();
		temp.z() = (*plocalArray)[i].z();
		pArray->push_back(temp);
	}
	osg::Vec3 temp2;
	temp2.x() = (*plocalArray)[0].x();
	temp2.y() = (*plocalArray)[0].y();
	temp2.z() = (*plocalArray)[0].z();
	pArray->push_back(temp2);

	m_localArrayVector.push_back(pArray);
}


void KL3DSelExtent::clearLocalExtent()
{
	m_localArrayVector.clear();
}


bool KL3DSelExtent::isInExtent(const osg::Vec3& coord)
{
	for(unsigned int num = 0; num < m_localArrayVector.size(); num++)
	{
		osg::ref_ptr<osg::Vec3Array> pLocalArray = m_localArrayVector[num];
		if(isInOnePolygonExtent(coord, pLocalArray))
		{
			return true;
		}
	}

	return false;
}


bool KL3DSelExtent::isInOnePolygonExtent(const osg::Vec3& coord, osg::Vec3Array* pLocalArray)
{
	unsigned int Count = pLocalArray->size();

	if(Count < 3) return false;
	int* alpha = new int[Count];

	int i;
	for(i=0; i<Count; i++)
	{
		osg::Vec2 pt;
		pt.y() = (*pLocalArray)[i].y() - coord.y();
		pt.x() = (*pLocalArray)[i].x() - coord.x();
		if(pt.y() >= 0 && pt.x() >= 0) alpha[i] = 0;
		if(pt.y() >= 0 && pt.x() < 0) alpha[i] = 3;
		if(pt.y() <= 0 && pt.x() > 0) alpha[i] = 1;
		if(pt.y() < 0 && pt.x() <=0) alpha[i] = 2;
	}

	int total = 0;
	for(i=1; i<Count; i++)
	{
		int delta = alpha[i] - alpha[i-1];
		if(delta >= -1 && delta <=1) total+=delta;
		if(delta > 2) total += delta - 4;
		if(delta < -2) total += delta + 4;
		if(delta == 2 || delta == -2)
		{
			osg::Vec2 pt, pt1, pt2, pt3, pt4;
			pt1.y() = (*pLocalArray)[i].y() - coord.y();
			pt1.x() = (*pLocalArray)[i].x() - coord.x();
			pt2.y() = (*pLocalArray)[i-1].y() - coord.y();
			pt2.x() = (*pLocalArray)[i-1].x() - coord.x();
			double lamta;
			bool bNeedPart = true;
			pt3.y() = 0;
			if(pt2.y() != 0)
			{
				lamta =-double(pt1.y()/pt2.y());
				pt3.x() = (pt1.x() + lamta * pt2.x()) /  (1.0 + lamta);
			}
			else if(pt1.y() != 0)
			{
				lamta =-double(pt2.y()/pt1.y());
				pt3.x() = (pt2.x() + lamta * pt1.x()) /  (1.0 + lamta);
			}
			else bNeedPart = false;

			pt4.x() = 0;
			if(pt2.x() != 0)
			{
				lamta =-double(pt1.x() / pt2.x());
				pt4.y() = (pt1.y() + lamta* pt2.y()) / (1.0+lamta);
			}
			else if(pt1.x() !=0)
			{
				lamta =- double(pt2.x() / pt1.x());
				pt4.y() = (pt2.y() + lamta * pt1.y()) / (1+lamta);
			}
			else bNeedPart = false;

			if(!bNeedPart) total += delta;
			else
			{
				pt3.y() = (pt3.y() + pt4.y()) / 2;
				pt3.x() = (pt3.x() + pt4.x()) / 2;
				int talpha = 0;
				if(pt3.y()>=0 && pt3.x() >=0)  talpha = 0;
				if(pt3.y()>=0 &&pt3.x() < 0)  talpha = 3;
				if(pt3.x() <=0 && pt3.x() > 0) talpha = 1;
				if(pt3.y()<0 && pt3.x() <=0)  talpha = 2;
				int delta1 = 0;
				delta1 = alpha[i]-talpha;
				if(delta1 >= -1 && delta1 <= 1) total += delta1;
				if(delta1 > 2) total += delta1 - 4;
				if(delta1 < -2) total += delta1 + 4;
				delta1 = talpha - alpha[i-1];
				if(delta1 >= -1 && delta1 <=1) total += delta1;
				if(delta1 > 2) total += delta1 - 4;
				if(delta1 < -2) total += delta1 + 4;
			}
		}
	}
	delete[]alpha;
	return !(!total);
}


bool KL3DSelExtent::isInExtentWindow(const osg::Vec3& coord)
{
	if(m_selectType == SEL_REC)
	{
		return isInRecExtentWindow(coord);
	}
	else if(m_selectType == SEL_POLOYGON)
	{
		return isInPolygonExtentWindow(coord);
	}
	else
	{
		return false;
	}
}


void KL3DSelExtent::changeSelExtent(const osg::Vec3& offset)
{
	for(unsigned int i = 0; i < m_localArrayVector.size(); i++)
	{
		osg::ref_ptr<osg::Vec3Array> pArray = m_localArrayVector[i];
		for(unsigned int j = 0; j < pArray->size(); j++)
		{
			(*pArray)[j] += offset;
		}
	}
}


void KL3DSelExtent::setSelectType(const KL3DSelectType pType)
{
	m_selectType = pType;
}


bool KL3DSelExtent::isInRecExtentWindow(const osg::Vec3& coord)
{
	if((coord.x() >= m_windowXmin) && (coord.x() <= m_windowXmax) && (coord.y() >= m_windowYmin) && (coord.y()) <= m_windowYmax)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool KL3DSelExtent::isInPolygonExtentWindow(const osg::Vec3& coord)
{
	unsigned int Count = m_screenArray->size();

	if(Count < 3) return false;
	int* alpha = new int[Count];

	int i;
	for(i=0; i<Count; i++)
	{
		osg::Vec2 pt;
		pt.y() = (*m_screenArray)[i].y() - coord.y();
		pt.x() = (*m_screenArray)[i].x() - coord.x();
		if(pt.y() >= 0 && pt.x() >= 0) alpha[i] = 0;
		if(pt.y() >= 0 && pt.x() < 0) alpha[i] = 3;
		if(pt.y() <= 0 && pt.x() > 0) alpha[i] = 1;
		if(pt.y() < 0 && pt.x() <=0) alpha[i] = 2;
	}

	int total = 0;
	for(i=1; i<Count; i++)
	{
		int delta = alpha[i] - alpha[i-1];
		if(delta >= -1 && delta <=1) total+=delta;
		if(delta > 2) total += delta - 4;
		if(delta < -2) total += delta + 4;
		if(delta == 2 || delta == -2)
		{
			osg::Vec2 pt, pt1, pt2, pt3, pt4;
			pt1.y() = (*m_screenArray)[i].y() - coord.y();
			pt1.x() = (*m_screenArray)[i].x() - coord.x();
			pt2.y() = (*m_screenArray)[i-1].y() - coord.y();
			pt2.x() = (*m_screenArray)[i-1].x() - coord.x();
			double lamta;
			bool bNeedPart = true;
			pt3.y() = 0;
			if(pt2.y() != 0)
			{
				lamta =-double(pt1.y()/pt2.y());
				pt3.x() = (pt1.x() + lamta * pt2.x()) /  (1.0 + lamta);
			}
			else if(pt1.y() != 0)
			{
				lamta =-double(pt2.y()/pt1.y());
				pt3.x() = (pt2.x() + lamta * pt1.x()) /  (1.0 + lamta);
			}
			else bNeedPart = false;

			pt4.x() = 0;
			if(pt2.x() != 0)
			{
				lamta =-double(pt1.x() / pt2.x());
				pt4.y() = (pt1.y() + lamta* pt2.y()) / (1.0+lamta);
			}
			else if(pt1.x() !=0)
			{
				lamta =- double(pt2.x() / pt1.x());
				pt4.y() = (pt2.y() + lamta * pt1.y()) / (1.0+lamta);
			}
			else bNeedPart = false;

			if(!bNeedPart) total += delta;
			else
			{
				pt3.y() = (pt3.y() + pt4.y()) / 2;
				pt3.x() = (pt3.x() + pt4.x()) / 2;
				int talpha = 0;
				if(pt3.y()>=0 && pt3.x() >=0)  talpha = 0;
				if(pt3.y()>=0 &&pt3.x() < 0)  talpha = 3;
				if(pt3.x() <=0 && pt3.x() > 0) talpha = 1;
				if(pt3.y()<0 && pt3.x() <=0)  talpha = 2;
				int delta1 = 0;
				delta1 = alpha[i]-talpha;
				if(delta1 >= -1 && delta1 <= 1) total += delta1;
				if(delta1 > 2) total += delta1 - 4;
				if(delta1 < -2) total += delta1 + 4;
				delta1 = talpha - alpha[i-1];
				if(delta1 >= -1 && delta1 <=1) total += delta1;
				if(delta1 > 2) total += delta1 - 4;
				if(delta1 < -2) total += delta1 + 4;
			}
		}
	}
	delete[]alpha;
	return !(!total);
}