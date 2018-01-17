#ifndef __KL3DOPERATION_H__
#define __KL3DOPERATION_H__

#include "KL3DOperationBase.h"

/*!************************************************
<br> ��˵���� ��ά�۲�ϵͳѡ�������
***************************************************/

class KL3DOperationSel : public KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationSel(KL3DMapManager* pMapManager, KL3DSelExtent* pSelExtent);

	/*!Ĭ����������*/
	virtual ~KL3DOperationSel();

	/*!��ʼ������*/
	virtual void init();

	/*!build����*/
	virtual void build();

protected:
	/*!�༭����Ϊ��*/
	void selPoint(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!�༭����Ϊ�㣨����omp����ѡ��*/
	void selPointByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!�༭����Ϊ�㣨����omp����ѡ��,ѡ��ʽΪ��ѡ����ѡ�Ϳ�ѡ���õķ�����ͬ����ѡʱֻ��ѡ��һ������ʵ�;
	�����ڵ�ͼ�㵥����ѡ��ʱ����һ��Ĭ��Ϊ�գ�*/
	void selPointByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 = NULL);

	/*!�༭����Ϊ��*/
	void selLine(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!�༭����Ϊ��(����omp����ѡ��)*/
	void selLineByOmp(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!�༭����Ϊ��(����omp����ѡ��,ѡ��ʽΪ��ѡ���ȸ��ݵ�����ȡ��Χ���еĵ㣬�ҵ�����ĵ��
	���ݴ˵��ҵ�����ʵ���;�������ߺͼ��ߵ�����ѡ��ʱ����һ��Ĭ��Ϊ��)*/
	void selLineByOmpForPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines, KL3DLineSet* pLines2 = NULL);

	/*!��ѡʱ�õ��������Χ�����е�*/
	KL3DEditPointSet getAllEditPointByPtClick(KL3DMapCache* pCache, KL3DLineSet* pLines);

	/*!����õ���pushToLocalCoor�����һ����*/
	KL3DEditPoint getEditPointByCoor(const osg::Vec3& pushToLocalCoor, KL3DEditPointSet& pAllSelPoint);

	/*!�ֲ�����ת��Ϊ��Ļ����*/
	osg::Vec3 localToScreen(const osg::Vec3& worldPoint);

protected:
	/*!��ά�۲�ϵͳѡ������*/
	KL3DSelExtent* m_selExtents;

	/*!��ά�۲�ϵͳѡ��༭����*/
	KL3DEditObject m_editObject;
};


#endif