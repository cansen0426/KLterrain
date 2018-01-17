#ifndef __KL3DPOINT_H__
#define __KL3DPOINT_H__

#include <osg/Vec3f>

/*!*****************************************
<br>三维点数据类
*******************************************/

class KL3DPoint
{
public:
	/*!默认构造函数*/
	KL3DPoint();

	/*!默认构造函数*/
	virtual ~KL3DPoint();

	/*!设置编号*/
	void setID(const double& id);

	/*!得到编号*/
	double getID() const;

	/*!设置同桩号*/
	void setSameStakeID(const short& sameStakeID);

	/*!得到同桩号*/
	short getSameStakeID() const;

	/*!设置点的索引号*/
	void setIndex(const unsigned int& index);

	/*!得到点的索引号*/
	unsigned int getIndex() const;

	/*!设置点是否被选中*/
	void setIsSelected(bool isSelected);

	/*!得到点是否被选中*/
	bool getIsSelected() const;

	/*!设置点是否被禁止*/
	void setIsForbidden(bool isForbidden);

	/*!得到点是否被禁止*/
	bool getIsForbidden() const;

	/*!设置点的坐标*/
	void setCoord(const osg::Vec3f& coord);

	/*!得到点的坐标*/
	osg::Vec3f getCoord() const;

private:
	/*!点号*/
	double m_id;

	/*!同桩号：范围0~9,默认值是1*/
	short m_sameStakeID;

	/*!线上的索引号*/
	unsigned int m_index;

	/*!标识：点是否被选中*/
	bool m_isSelected;

	/*!标识：点是否禁止*/
	bool m_isForbidden;

	/*!点的坐标值*/
	osg::Vec3f m_coordinate;



};

#endif