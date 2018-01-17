#ifndef __KL3DOPERATIONMOVE_H__
#define __KL3DOPERATIONMOVE_H__

#include "KL3DOperationBase.h"

/*!************************************************
<br> ��˵������ά�۲�ϵͳ�ƶ�����
**************************************************/

class KL3DOperationMove : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationMove(KL3DMapManager* pMapManager, const osg::Vec3& offset);

	/*!��������*/
	virtual ~KL3DOperationMove();

	/*!��дbuild����*/
	virtual void build();

private:
	/*!ƫ�ƾ���*/
	osg::Vec3 m_distanceOffset;
};

#endif
