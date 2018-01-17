
#include<osg/ComputeBoundsVisitor>

#include "KL3DTextureManager.h"

KL3DTextureManager::KL3DTextureManager(osg::Node* pTerrainNode):
	m_id(pTerrainNode),
	m_terrainNode(pTerrainNode),
	m_demTexture(NULL),
	m_sourcePath("")
{
	osg::ComputeBoundsVisitor cbVisitor;
	m_terrainNode->accept(cbVisitor);
	m_terrainBounding = cbVisitor.getBoundingBox();
}


KL3DTextureManager::~KL3DTextureManager()
{

}

void KL3DTextureManager::init()
{
	//创建二维纹理对象：用于 存储地形高程
	m_demTexture  = getOrCreateDemTexture();

	//设置渲染相机状态
	setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f,1.0f));
	setViewport(0, 0, TEXTURESIZE, TEXTURESIZE);
	setRenderOrder(osg::Camera::PRE_RENDER);
	setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);

	//投影变换，通过正投影方式，将模型放置在一个立方体中，立方体左右宽度right和上下宽度top和地形包围盒一致，深度为100~10000
	double right  = (m_terrainBounding._max.x() - m_terrainBounding._min.x())/2.0;
	double top    = (m_terrainBounding._max.y() - m_terrainBounding._min.y())/2.0;
	setProjectionMatrixAsOrtho(-right, right, -top, top, 1, 10000);

	//通过定义视点位置eyePoint、参考点位置center、视点上方向up来确定相机的位置和姿态
	//从而将相机拍摄对象从世界坐标系WCS转换为视点坐标系VCS
	osg::Vec3d center((m_terrainBounding._min.x()+ m_terrainBounding._max.x())/2,
		(m_terrainBounding._min.y()+ m_terrainBounding._max.y())/2,
		/*(m_terrainBounding._min.z()+ m_terrainBounding._max.z())/2*/m_terrainBounding._max.z()*1.2);
	osg::Vec3d upDirection(0.0, 1.0, 0.0);
	osg::Vec3d eyePoint = center + osg::Vec3d(0.0, 0.0, 10);
	setViewMatrixAsLookAt(eyePoint, center, upDirection);

	// 绑定纹理对象
	addChild(m_terrainNode);
	attach(osg::Camera::COLOR_BUFFER, m_demTexture);
	

	// 创建状态集
	m_stateSet = getOrCreateStateSet();
	osg::ref_ptr<osg::Program> m_program = new osg::Program();
	m_program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX,m_sourcePath + "shaders/KL3DDesignDepthRender.vert"));
	m_program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT,m_sourcePath + "shaders/KL3DDesignDepthRender.frag"));
	m_stateSet->setAttribute(m_program);


	//设置更新回调
	osg::ref_ptr<KL3DRttCallback> pRttCallback = new KL3DRttCallback(this);
	setUpdateCallback(pRttCallback);
}

void KL3DTextureManager::setID(osg::Node* id)
{
	m_id = id;
}

osg::Node* KL3DTextureManager::getID()
{
	return m_id;
}

osg::Node* KL3DTextureManager::getTerrainNode()
{
	return m_terrainNode;
}

osg::BoundingBox KL3DTextureManager::getTerrainBoundingBox() const
{
	return m_terrainBounding;
}

osg::ref_ptr<osg::Texture2D> KL3DTextureManager::getOrCreateDemTexture()
{
	if(!m_demTexture)
	{
		m_demTexture = new osg::Texture2D();
		m_demTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		m_demTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

		m_demTexture->setTextureSize(TEXTURESIZE,TEXTURESIZE);
		m_demTexture->setInternalFormat(GL_RGBA32F_ARB);
		m_demTexture->setSourceFormat(GL_LUMINANCE);

	}

	return m_demTexture;
}

void KL3DTextureManager::setSourcePath(const std::string& sourcePath)
{
	m_sourcePath = sourcePath;
}

//***********************************************RttCallback***********************************//
KL3DRttCallback::KL3DRttCallback(osg::Node* pRttCamera):
	m_rttCamera(pRttCamera),
	m_count(0)
{

}

KL3DRttCallback::~KL3DRttCallback()
{


}

void KL3DRttCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{

	if(m_count == RTTCOUNT)
	{
		m_rttCamera->setNodeMask(false);
	}

	if(m_count!=RTTCOUNT)
	{

		m_count++;
	}

	traverse(node, nv);
}