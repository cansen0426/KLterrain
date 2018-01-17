#ifndef __KL3DOPERATION_H__
#define __KL3DOPERATION_H__

#include "KL3DOperationBase.h"

/*!****************************************************
<br>类说明：三维观测系统炮检点增加操作
******************************************************/

class KL3DOperationAdd : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationAdd(KL3DMapManager* pMapManager);

	/*!默认析构函数*/
	virtual ~KL3DOperationAdd();

	/*!重写初始化函数*/
	virtual void init();

	/*!重写build函数*/
	virtual void build();

protected:

	/*!添加点*/
	void addEditPoint(KL3DPoint* pAddPoint, KL3DLine* pLine, const float& xBase = 0, const float& yBase = 0);

	/*!添加线*/
	void addEditLine(KL3DLine* pAddLine, KL3DMapCache* pCache, KL3DDesignNode* pDesignNode, const float& xBase = 0, const float& yBase = 0);

private:

};

#endif