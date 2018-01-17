#ifndef __KL3DOPERATIONUNSEL_H__
#define __KL3DOPERATIONUNSEL_H__

#include "KL3DOperationBase.h"

/*!*********************************************
<br>类说明：三维观测系统选择清楚类
************************************************/

class KL3DOperationUnsel : public KL3DOperationBase
{
public:
	/*!默认构造函数*/
	KL3DOperationUnsel(KL3DMapManager* pMapManger);

	/*!默认析构函数*/
	~KL3DOperationUnsel();

	/*!build函数*/
	virtual void build();

protected:
	/*!清空编辑点*/
	void clearAllEditPoints(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode, KL3DEditPointSet* pEditPoints);

	/*!清空编辑线*/
	void clearAllEditLines(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode,KL3DEditLineSet* pEditLines);

private:

};

#endif