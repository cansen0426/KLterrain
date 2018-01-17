#ifndef __KL3DDESIGNSHAPE_H__
#define __KL3DDESIGNSHAPE_H__

#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgTerrain/Terrain>

#include <osg/BoundingBox>
#include <osg/MatrixTransform>

#include "KL3DMapManager.h"
#include "KL3DDesignHandle.h"
#include "KL3DDesignPolygonHandle.h"

/*!*******************************************************
<br>��˵������ά�۲�ϵͳͼԪ�ࣨ��Ϊû�ж�ά�۲�ϵͳ��֧�֣���������Ͷ�����Ŀ���ܴ�
*********************************************************/

class KL3DDesignShape
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DDesignShape();

	/*!��������*/
	~KL3DDesignShape();

	/*!��ʼ������*/
	virtual void init();

	/*!���ø��ڵ�*/
	void setRootNode(osg::Node* rootNode);

	/*!������Դ·��*/
	void setSourcePath(const std::string sourcePath);

	/*!�����ļ����ɹ۲�ϵͳ����*/
	bool generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain, std::string dataFileName);

	/*!���ݵ����Լ����������ɹ۲�ϵͳ����*/
	bool generate3DDesignData(osgViewer::Viewer* pViewer,osgTerrain::Terrain* pTerrain);

	/*!�����Ƿ���ʾ�۲�ϵͳ�ڵ�*/
	void setDesignNodeVisible(bool isVisible);

	/*!�����Ƿ���ʾ�ڼ��*/
	void setPointsVisible(bool isVisible, KL3DLineType type);

	/*!�����Ƿ���ʾ�ڼ��׮��*/
	void setLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!���ñ�ע���*/
	void setLabelInterval(const unsigned int& interval, KL3DLineType type);

	/*!�����Ƿ���ʾ�ڼ���*/
	void setLinesVisible(bool isVisible, KL3DLineType);

	/*!�����Ƿ���ʾ�ڼ����ߺ�*/
	void setLinesLabelIsVisible(bool isVisible, KL3DLineType type);

	/*!������ʼ���ڼ����ͼ*/
	osg::ref_ptr<osg::Image> createPointImage(KL3DLineType type);

	/*!�����ڼ���С*/
	void setPointSize(const float& PointSize, KL3DLineType type);

	/*!�Ƿ���ڵ���*/
	bool isTerrainExist();

	/*!���õ�������ϵ��*/
	void setTerrainScale(osg::MatrixTransform* mt);

	/*!���ý����¼���*/
	void setCurrentEventHandle(osg::ref_ptr<KL3DBaseHandler> pHandle);

protected:
	/*!������λ�߲��뵽�۲�ϵͳ��*/
	void generate3DLines(KL3DMapCache* pCache);

private:
	/*!��ά�����Ӿ���*/
	osgViewer::Viewer* m_viewer;

	/*!��ά�������ڵ�*/
	osg::Node* m_root;

	/*!KL3DMapManager����*/
	KL3DMapManager* m_mapManager;

	/*!�����Դ·��*/
	std::string m_designSourcePath;

	/*!��������ϵ������*/
	osg::MatrixTransform* m_terrainScaleTranform;

	/*!��ά�۲�ϵͳ�ڼ�㽻�������*/
	osg::ref_ptr<KL3DDesignHandle> m_3DDesignHandle;

	/*!��ά�۲�ϵͳ�ڼ�����ν��������*/
	osg::ref_ptr<KL3DDesignPolygonHandle> m_3DDesignPolygonHandle;

	//*****************�ڼ����ͼ����***********************//
	/*!��ȡ��ǰ���ڵ�ͼ�������*/
	//std::string m_currentSpImageName;

	/*!��ȡ��ǰ���ͼ�������*/
	//std::string m_currentRvImageName;

	/*!��ȡ��ǰ���ڵ������ɫ*/
	//osg::Vec4 m_currentSpFillColor;

};

#endif