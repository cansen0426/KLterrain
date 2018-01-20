#ifndef __KL3DBASEENTITY_H__
#define __KL3DBASEENTITY_H__

#include <osg/Geode>
#include <osg/Geometry>

#include <osg/LineWidth>
#include <osg/LineStipple>

#include "KL3DTerrainTileManager.h"
//#include "KL3DMacro.h"
/*!***************************************
<br>��˵���� ͨ��ͼԪ����
*****************************************/
class KL3DBaseEntity: public osg::Geode
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DBaseEntity();

	/*!��ʼ������*/
	virtual void init();
	
	/*!�ػ溯��*/
	virtual void reDraw();
	
	/*!����ID*/
	void setID(const std::string& id);
	
	/*!�õ�ID*/
	std::string getID() const;
	
	/*!��������*/
	void setName(const std::string& name);
	
	/*!�õ�����*/
	std::string getName() const;
	
	/*!����ͼԪ��ͼ*/
	void setImage(osg::ref_ptr<osg::Image> pImage);
	
	/*!������ɫ*/
	void setColor(const osg::Vec4f& color);

	/*!�õ���ɫ*/
	osg::Vec4f getColor() const;

	/*!�õ�ͼԪ����*/
	osg::Vec3 getEntityCore() const;

	/*!�õ�x����ƫ����*/
	float getXoffset();

	/*!�õ�y����ƫ����*/
	float getYoffset();

	/*!Ĭ����������*/
	virtual ~KL3DBaseEntity();

protected:
	/*!ͼԪ�����ݿ�ID���������ݿ�ı���¼��ÿһ��ͼԪΨһ��Ӧһ��ID��idһֱ������ɾ���Ĳ��ᱻ�ظ�ʹ��*/
	std::string m_id;

	/*!ͼԪ���ƣ�����Ϊ��*/
	std::string m_name;

	/*!��ɫ*/
	osg::Vec4f m_color;

	/*!ͼԪ���ƽڵ�*/
	osg::ref_ptr<osg::Geometry> m_geometry;

	/*!x�����ƫ����*/
	float m_xOffset;

	/*!y�����ƫ����*/
	float m_yOffset;

	/*!����x�����ƫ�ƻ���*/
	float m_xBaseNum;

	/*!����y�����ƫ�ƻ���*/
	float m_yBaseNum;

	/*!ͼԪ��ͼ*/
	osg::ref_ptr<osg::Image> m_image;

	/*!ͼԪ���ģ�����ͼԪ���Ƶ�λ�ã�*/
	osg::Vec3 m_entityCore;
};
#endif