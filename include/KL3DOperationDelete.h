#ifndef __KL3DOPERATIONDELETE_H__
#define __KL3DOPERATIONDELETE_H__

#include "KL3DOperationBase.h"

/*!********************************************
<br>类说明：三维观测系统删除类
**********************************************/

class KL3DOperationDelete : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationDelete(KL3DMapManager* pMapManager);

	/*!默认析构函数*/
	~KL3DOperationDelete();

	/*!重写初始化函数*/
	virtual void init();

	/*!重写build函数*/
	virtual void build();

protected:
	/*!清除点数组*/
	void deleteEditPoint(KL3DPoint* pDelPoint, KL3DLine* pLine);

	/*!清除线数组*/
	void deleteEditLine(KL3DLine* pLine);
private:

};


#endif