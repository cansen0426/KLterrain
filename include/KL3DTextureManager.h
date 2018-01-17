#ifndef __KL3DTEXTUREMANAGER_H__
#define __KL3DTEXTUREMANAGER_H__

#include <osg/Camera>
#include <osg/Texture2D>
#include <osgTerrain/TerrainTile>

#define TEXTURESIZE 2048

/*!**********************************************************
<br>��˵����������������࣬������󱣴���εĸ߳�
*************************************************************/

class KL3DTextureManager: public osg::Camera
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DTextureManager(osg::Node*pTerrainNode);

	/*!��ʼ������*/
	virtual void init();

	/*!����ID*/
	void setID(osg::Node* id);

	/*!�õ�ID*/
	osg::Node* getID();

	/*!�õ����νڵ�*/
	osg::Node* getTerrainNode();

	/*!�õ����νڵ��Χ��*/
	osg::BoundingBox getTerrainBoundingBox() const;

	/*!�õ����ߴ����߳�����*/
	osg::ref_ptr<osg::Texture2D> getOrCreateDemTexture();

	/*!������Դ·��*/
	void setSourcePath(const std::string& sourcePath);

protected:
	/*!��������*/
	virtual ~KL3DTextureManager();

private:
	/*!��ʶ��������������󣬶�Ӧÿһ���۲�ϵͳ*/
	osg::Node* m_id;

	/*!״̬������*/
	osg::StateSet* m_stateSet;

	/*!��ά�������*/
	osg::ref_ptr<osg::Texture2D> m_demTexture;

	/*!���νڵ�*/
	osg::Node* m_terrainNode;

	/*!���ΰ�Χ�д�С*/
	osg::BoundingBox m_terrainBounding;

	/*!��Դ·��*/
	std::string m_sourcePath;

};

/*!*************************************************
<br>��˵�������һ�����»ص���ʹ����ά�۲�ϵͳ�������ֺ�һ��ʱ�䣬rtt�����������Ⱦ���Ӷ�����Ӱ����ȾЧ��
****************************************************/
//�����ٽ�ֵ
#define  RTTCOUNT 10
class KL3DRttCallback: public osg::NodeCallback
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DRttCallback(osg::Node* pRttCamera);

	/*!��д()����*/
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
	/*!Ĭ����������*/
	virtual ~KL3DRttCallback();

private:
	/*!������*/
	unsigned int m_count;

	/*!��Ⱦ������ڵ�*/
	osg::Node* m_rttCamera;
};

#endif