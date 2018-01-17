#ifndef __KL3DOPERATIONUNSEL_H__
#define __KL3DOPERATIONUNSEL_H__

#include "KL3DOperationBase.h"

/*!*********************************************
<br>��˵������ά�۲�ϵͳѡ�������
************************************************/

class KL3DOperationUnsel : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationUnsel(KL3DMapManager* pMapManger);

	/*!Ĭ����������*/
	~KL3DOperationUnsel();

	/*!build����*/
	virtual void build();

protected:
	/*!��ձ༭��*/
	void clearAllEditPoints(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode, KL3DEditPointSet* pEditPoints);

	/*!��ձ༭��*/
	void clearAllEditLines(KL3DMapCache* pCache, KL3DDesignNode* p3DDesingNode,KL3DEditLineSet* pEditLines);

private:

};

#endif