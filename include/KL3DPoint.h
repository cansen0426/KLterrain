#ifndef __KL3DPOINT_H__
#define __KL3DPOINT_H__

#include <osg/Vec3f>

/*!*****************************************
<br>��ά��������
*******************************************/

class KL3DPoint
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DPoint();

	/*!Ĭ�Ϲ��캯��*/
	virtual ~KL3DPoint();

	/*!���ñ��*/
	void setID(const double& id);

	/*!�õ����*/
	double getID() const;

	/*!����ͬ׮��*/
	void setSameStakeID(const short& sameStakeID);

	/*!�õ�ͬ׮��*/
	short getSameStakeID() const;

	/*!���õ��������*/
	void setIndex(const unsigned int& index);

	/*!�õ����������*/
	unsigned int getIndex() const;

	/*!���õ��Ƿ�ѡ��*/
	void setIsSelected(bool isSelected);

	/*!�õ����Ƿ�ѡ��*/
	bool getIsSelected() const;

	/*!���õ��Ƿ񱻽�ֹ*/
	void setIsForbidden(bool isForbidden);

	/*!�õ����Ƿ񱻽�ֹ*/
	bool getIsForbidden() const;

	/*!���õ������*/
	void setCoord(const osg::Vec3f& coord);

	/*!�õ��������*/
	osg::Vec3f getCoord() const;

private:
	/*!���*/
	double m_id;

	/*!ͬ׮�ţ���Χ0~9,Ĭ��ֵ��1*/
	short m_sameStakeID;

	/*!���ϵ�������*/
	unsigned int m_index;

	/*!��ʶ�����Ƿ�ѡ��*/
	bool m_isSelected;

	/*!��ʶ�����Ƿ��ֹ*/
	bool m_isForbidden;

	/*!�������ֵ*/
	osg::Vec3f m_coordinate;



};

#endif