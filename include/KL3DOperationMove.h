#ifndef __KL3DOPERATIONMOVE_H__
#define __KL3DOPERATIONMOVE_H__

#include "KL3DOperationBase.h"

/*!************************************************
<br> 类说明：三维观测系统移动操作
**************************************************/

class KL3DOperationMove : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationMove(KL3DMapManager* pMapManager, const osg::Vec3& offset);

	/*!析构函数*/
	virtual ~KL3DOperationMove();

	/*!重写build函数*/
	virtual void build();

private:
	/*!偏移距离*/
	osg::Vec3 m_distanceOffset;
};

#endif
