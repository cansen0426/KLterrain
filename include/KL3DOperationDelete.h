#ifndef __KL3DOPERATIONDELETE_H__
#define __KL3DOPERATIONDELETE_H__

#include "KL3DOperationBase.h"

/*!********************************************
<br>��˵������ά�۲�ϵͳɾ����
**********************************************/

class KL3DOperationDelete : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationDelete(KL3DMapManager* pMapManager);

	/*!Ĭ����������*/
	~KL3DOperationDelete();

	/*!��д��ʼ������*/
	virtual void init();

	/*!��дbuild����*/
	virtual void build();

protected:
	/*!���������*/
	void deleteEditPoint(KL3DPoint* pDelPoint, KL3DLine* pLine);

	/*!���������*/
	void deleteEditLine(KL3DLine* pLine);
private:

};


#endif