#ifndef __KL3DOPERATIONACTIVE_H__
#define __KL3DOPERATIONACTIVE_H__

#include "KL3DOperationBase.h"

/*!**************************************************
<br>类说明：三维观测系统激活操作
****************************************************/

class KL3DOperationActive : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationActive(KL3DMapManager* pMapManager);

	/*!析构函数*/
	virtual ~KL3DOperationActive();

	/*!重写初始化函数*/
	virtual void init();

	/*!重写build函数*/
	virtual void build();

private:

};

#endif