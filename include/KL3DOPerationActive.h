#ifndef __KL3DOPERATIONACTIVE_H__
#define __KL3DOPERATIONACTIVE_H__

#include "KL3DOperationBase.h"

/*!**************************************************
<br>��˵������ά�۲�ϵͳ�������
****************************************************/

class KL3DOperationActive : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationActive(KL3DMapManager* pMapManager);

	/*!��������*/
	virtual ~KL3DOperationActive();

	/*!��д��ʼ������*/
	virtual void init();

	/*!��дbuild����*/
	virtual void build();

private:

};

#endif