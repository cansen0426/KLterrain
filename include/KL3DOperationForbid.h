#ifndef __KL3DOPERATIONFORBID_H__
#define __KL3DOPERATIONFORBID_H__

#include "KL3DOperationBase.h"

/*!**********************************************
<br>��˵������ά�۲�ϵͳ��ֹ����
************************************************/
class KL3DOperationForbid : public KL3DOperationBase
{
public:
	/*!���캯��*/
	KL3DOperationForbid(KL3DMapManager* pMapManager);

	/*!��������*/
	virtual ~KL3DOperationForbid();

	/*!��д��ʼ������*/
	virtual void init();

	/*!��дbuild����*/
	virtual void build();

private:

};

#endif