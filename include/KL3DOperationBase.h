#ifndef __KL3DPERATIONBASE_H__
#define __KL3DPERATIONBASE_H__

#include "KL3DMapManager.h"

/*!**********************************************************
<br> ��˵������ά�۲�ϵͳ�����Ļ���
***********************************************************/

class KL3DOperationBase
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DOperationBase();

	/*!���캯��*/
	KL3DOperationBase(KL3DMapManager* pMapManager);

	/*!Ĭ����������*/
	virtual ~KL3DOperationBase();

	/*!��ʼ������*/
	virtual void init();

	/*!������������*/
	virtual void build();

protected:
	/*!�����ڶ෽���������*/
	KL3DMapManager* m_mapManager;
};

/*!��ѡ������*/
typedef enum
{
	SEL_REC,
	SEL_POLOYGON
}KL3DSelectType;


/*!*************************************************************
<br>��˵������ѡ��Χ��
****************************************************************/

class KL3DSelExtent
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DSelExtent();

	/*!���ع��캯��*/
	KL3DSelExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft);

	/*!Ĭ����������*/
	virtual ~KL3DSelExtent();

	/*!����selExtent�ķ�Χ*/
	void setExtent(osg::Vec3& upLeft, osg::Vec3& upRight, osg::Vec3& downRight, osg::Vec3& downLeft);

	/*!����setExtentWindow�ķ�Χ*/
	void setExtentWindow(const float& xmin, const float& ymin, const float& xmax, const float& ymax);

	/*!���ö���ο�ѡ�ķ�Χ*/
	void setPolygonExtentWindow(osg::Vec2Array* pscreenArray);

	/*!������Ļѡ���Ӧ�ľֲ���Χ*/
	void setLocalExtent(osg::Vec3Array* plocalArray);

	/*!�����Ļѡ���Ӧ�ľֲ���Χ*/
	void clearLocalExtent();

	/*!�ж��Ƿ���ѡ����һ����������Χ�ڣ���Ļ����ת�ֲ����꣩*/
	bool isInExtent(const osg::Vec3& coord);

	/*!�ж��Ƿ���ĳ����ѡ��Χ�ڣ���Ļ����ת�ֲ����꣩*/
	bool isInOnePolygonExtent(const osg::Vec3& coord, osg::Vec3Array* pLocalArray);

	/*!�ж��Ƿ��ڶ�ѡ����*/
	bool isInExtentWindow(const osg::Vec3& coord);

	/*!ѡ��������Ļ���������Ӧ�ľֲ�����������һ��ƫ��������Ϊ�ֲ�ѡ�����һ��ƫ����*/
	void changeSelExtent(const osg::Vec3& offset);

	/*!���ÿ�ѡ����*/
	void setSelectType(const KL3DSelectType pType);

	/*!�����Ƿ��ѡ*/
	void setIsPtSel(bool pIsPtSel){m_isPtSel = pIsPtSel;};

	/*!�õ��Ƿ��ѡ*/
	bool getIsPtSel(){return m_isPtSel;};

	/*!����pushʱ��Ļ���Ӧ�ľֲ�������*/
	void setPushToLocalCoor(const osg::Vec3& pPustTocal){m_pushToLocalCoor = pPustTocal;};

	/*!pushʱ��Ļ���Ӧ�ľֲ���*/
	osg::Vec3 getPushToLocalCoor(){return m_pushToLocalCoor;};

protected:
	/*!�ж��Ƿ��ھ��ζ�ѡ���ڣ��ֲ�����ת��Ϊ��Ļ���꣩*/
	bool isInRecExtentWindow(const osg::Vec3& coord);

	/*!�ж��Ƿ��ڶ���ζ�ѡ���ڣ��ֲ�����ת��Ϊ��Ļ���꣩*/
	bool isInPolygonExtentWindow(const osg::Vec3& coord);

private:
	/*!ѡ���������Ͻ�ӳ�䵽���ε�����*/
	osg::Vec3 m_upLeftCoord;

	/*!ѡ���������Ͻ�ӳ�䵽���ε�����*/
	osg::Vec3 m_upRightCoord;

	/*!ѡ���������½�ӳ�䵽���ε�����*/
	osg::Vec3 m_downRightCoord;

	/*!ѡ���������½�ӳ�䵽���ε�����*/
	osg::Vec3 m_downLefeCoord;

	/*!ѡ��������Ļ����x*/
	float m_windowXmin, m_windowXmax;

	/*!ѡ��������Ļ����y*/
	float m_windowYmin, m_windowYmax;

	/*!ѡ��������Ļ��������*/
	osg::ref_ptr<osg::Vec2Array> m_screenArray;

	/*!ѡ��������Ļ���������Ӧ�ľֲ���������(���ѡ��Ĵ洢)*/
	std::vector<osg::ref_ptr<osg::Vec3Array>> m_localArrayVector;

	/*!��ѡ������*/
	KL3DSelectType m_selectType;

	/*���Ƿ�Ϊ��ѡ*/
	bool m_isPtSel;

	/*!�����¼��Ļpush���Ӧ�ľֲ������*/
	osg::Vec3 m_pushToLocalCoor;
};
#endif