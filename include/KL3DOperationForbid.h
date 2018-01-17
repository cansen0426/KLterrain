#ifndef __KL3DOPERATIONFORBID_H__
#define __KL3DOPERATIONFORBID_H__

#include "KL3DOperationBase.h"

/*!**********************************************
<br>类说明：三维观测系统禁止操作
************************************************/
class KL3DOperationForbid : public KL3DOperationBase
{
public:
	/*!构造函数*/
	KL3DOperationForbid(KL3DMapManager* pMapManager);

	/*!析构函数*/
	virtual ~KL3DOperationForbid();

	/*!重写初始化函数*/
	virtual void init();

	/*!重写build函数*/
	virtual void build();

private:

};

#endif