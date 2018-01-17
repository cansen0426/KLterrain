#ifndef __KL3DOPERATION_H__
#define __KL3DOPERATION_H__

#include "KL3DOperationBase.h"

/*!****************************************************
<br>��˵������ά�۲�ϵͳ�ڼ�����Ӳ���
******************************************************/

class KL3DOperationAdd : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationAdd(KL3DMapManager* pMapManager);

	/*!Ĭ����������*/
	virtual ~KL3DOperationAdd();

	/*!��д��ʼ������*/
	virtual void init();

	/*!��дbuild����*/
	virtual void build();

protected:

	/*!��ӵ�*/
	void addEditPoint(KL3DPoint* pAddPoint, KL3DLine* pLine, const float& xBase = 0, const float& yBase = 0);

	/*!�����*/
	void addEditLine(KL3DLine* pAddLine, KL3DMapCache* pCache, KL3DDesignNode* pDesignNode, const float& xBase = 0, const float& yBase = 0);

private:

};

#endif