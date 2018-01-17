
#include "KL3DCommonStruct.h"

#include "KL3DPoint.h"

KL3DPoint::KL3DPoint():
	m_id(0.0),
	m_sameStakeID(1),
	m_index(0),
	m_isSelected(false),
	m_isForbidden(false),
	m_coordinate(osg::Vec3f(0.0f,0.0f,KL3DDEFAULTVALUE))
{

}


KL3DPoint::~KL3DPoint()
{

}


void KL3DPoint::setID(const double& id)
{
	m_id = id;
}

double KL3DPoint::getID() const
{
	return m_id;
}


void KL3DPoint::setSameStakeID(const short& sameStakeID)
{
	m_sameStakeID = sameStakeID;
}


short KL3DPoint::getSameStakeID() const
{
	return m_sameStakeID;
}


void KL3DPoint::setIndex(const unsigned int& index)
{
	m_index = index;
}


unsigned int KL3DPoint::getIndex() const
{
	return m_index;
}


void KL3DPoint::setIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
}


bool KL3DPoint::getIsSelected() const
{
	return m_isSelected;
}


void KL3DPoint::setIsForbidden(bool isForbidden)
{
	m_isForbidden = isForbidden;
}


bool KL3DPoint::getIsForbidden() const
{
	return m_isForbidden;
}


void KL3DPoint::setCoord(const osg::Vec3f& coord)
{
	m_coordinate = coord;
}


osg::Vec3f KL3DPoint::getCoord() const
{
	return m_coordinate;
}