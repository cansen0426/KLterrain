#ifndef __KL3DDESIGNPOLYGONHANDLE_H__
#define __KL3DDESIGNPOLYGONHANDLE_H__

#include <OpenThreads/Thread>
#include <osgTerrain/Terrain>

#include "KL3DOperationBase.h"
#include "KL3DBaseHandler.h"
#include "KL3DMapManager.h"

/*!*****************************************************
<br>��˵������ά�۲�ϵͳ����ο�ѡ������
*******************************************************/

class KL3DDesignPolygonHandle : public KL3DBaseHandler
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DDesignPolygonHandle(KL3DMapManager* pMapManager,osgTerrain::Terrain* pTerrain = NULL);

	/*!��д���̰����¼�*/
	virtual void keydownEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���̵����¼�*/
	virtual void keyupEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���push�¼�*/
	virtual void mousePushEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���Move�¼�*/
	virtual void mouseMoveEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���drag�¼�*/
	virtual void mouseDragEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���Release�¼�*/
	virtual void mouseReleaseEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���Release�¼�*/
	virtual void mouseDoubleClickEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д���Scroll�¼�*/
	virtual void mouseScrollEvent(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	/*!��д�õ���������ĺ���*/
	virtual osg::Vec3 getTerrainCoord(const float& x, const float& y);

	/*!��ֹ����*/
	virtual void forbidEditObject();

	/*!�������*/
	virtual void activeEditObject();

	/*!ɾ������*/
	virtual void deleteEditObject();

	/*!����۲�ϵͳ��ѡ����*/
	void clearEditPoints();

	/*!����۲�ϵͳ�Ķ���ο�*/
	void clearPolygonGeometry();

	/*!ѡ�к�֪ͨ��ͼˢ��*/
	bool notifyUpdateView();

	/*!֪ͨ��ͼ�Ƿ���ʾ�ڵ�༭��ť*/
	bool notifyShotUpdateView();

	/*!֪ͨ��ͼ�Ƿ���ʾ�첨��༭��ť*/
	bool notifyRcvUpdateView();

protected:
	/*!��������*/
	virtual ~KL3DDesignPolygonHandle();

	/*!��ȡ��ǰ�༭����*/
	KL3DEditObject getEditObject();

	/*!��ѡʱ���ж���갴�µ�λ���Ƿ������Ѿ�ѡ�������*/
	bool isLoactAtEditLines(const float& xWindow, const float& yWindow);

	/*!���ݵ������̸߳���cpu��ֵ�㷨��ȡ�߳�*/
	void updateDemByCPU(bool isUpdate);

	/*!�ֲ�����ת������Ļ����*/
	osg::Vec3 localToScreen(const osg::Vec3& worldpoint);

	/*!�õ���Ļ����ת��Ϊ�ֲ�����ľ�ȷֵ*/
	osg::Vec3 getTerrainCoordFine(const osgUtil::LineSegmentIntersector::Intersection* result);

	/*!������Ļ�����ȡ����ģ�͵ľֲ�����*/
	int getLocalInsectionCoord(osg::Vec3& upLeftLoaclCoord, osg::Vec3& upRightLoaclCoord, osg::Vec3& downLeftLocalCoord, osg::Vec3& downRightLoaclCoord,
		const float& xWindowMin, const float& xWindowMax, const float& yWindowMin, const float& yWindowMax );

protected:

	/*!�����ڶ෽������������*/
	KL3DMapManager* m_mapManager;

	/*!��ʶ:�ڵ��Ƿ��ڱ༭״̬*/
	bool m_isShotPointEdit;

	/*!��ʶ�������Ƿ��ڱ༭״̬*/
	bool m_isShotLineEdit;

	/*!��ʶ���첨���Ƿ��ڱ༭״̬*/
	bool m_isRcvPointEdit;

	/*!��ʶ���첨���Ƿ��ڱ༭״̬*/
	bool m_isRcvLineEdit;

	/*!�жϵ�ǰ�Ƿ�����ƶ�����*/
	bool m_isMoveOperation;

	/*!��ѡ����*/
	KL3DSelExtent* m_selExtent;

	/*!��¼��Ļ��ѡ���������*/
	osg::ref_ptr<osg::Vec2Array> m_recordScrArray;

	/*!��¼Z�����������������ڵ��С�ı仯*/
	unsigned int m_pushZ;

	/*!��¼X���������������ڼ���С�ı仯*/
	unsigned int m_pushX;

	/*!��¼C���������������ڵ��ε���ʾ*/
	unsigned int m_pushC;

	/*!��¼V�����������������ڼ��ߵ���ʾ*/
	unsigned int m_pushV;

	/*!�����ĵ�������*/
	osgTerrain::Terrain* m_terrain;
};

#endif