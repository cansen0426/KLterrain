#include <osg/Program>
#include <osg/Shader>
#include <osg/Texture2D>
#include <osg/Uniform>
#include <osg/PointSprite>
#include <osg/Point>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osg/Material>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>

#include "KL3DPointsNode.h"

const std::string m_vertexShaderPath = "shaders/KL3DDesignPointsRender.vert";
const std::string m_fragShaderPath = "shaders/KL3DDesignPointsRender.frag";

KL3DPointsNode::KL3DPointsNode() :
	m_stateSet(NULL),
	m_terrainNode(NULL),
	m_textureManager(NULL),
	m_terrainScale(1.0f),
	m_vertexIndex(0),
	m_colorIndex(1),
	m_flagIndex(2),
	m_demTextureIndex(0),
	m_pointTextureIndex(1),
	m_pointSize(10.0f),
	m_isPointSizeChange(false),
	m_isScroll(false),
	m_sourcePath(""),
	m_xBase(0.0f),
	m_YBase(0.0f),
	m_pointImage(NULL)
{

}


KL3DPointsNode::~KL3DPointsNode()
{

}

void KL3DPointsNode::init()
{
	//init the stateSet in pointsNode
	m_stateSet = getOrCreateStateSet();

	//create program attribute
	osg::ref_ptr<osg::Program> pProgram = new osg::Program();
	pProgram->addBindAttribLocation("vertexArr", m_vertexIndex);
	pProgram->addBindAttribLocation("colorArr",m_colorIndex);
	pProgram->addBindAttribLocation("flagArr",m_flagIndex);

	//add Shader to render the points
	std::string vertexShaderPath = m_sourcePath + m_vertexShaderPath;
	std::string fragShaderPath = m_sourcePath + m_fragShaderPath;
	osg::ref_ptr<osg::Shader> pVertexShader = osg::Shader::readShaderFile(osg::Shader::VERTEX, vertexShaderPath);
	osg::ref_ptr<osg::Shader> pFragShader = osg::Shader::readShaderFile(osg::Shader::FRAGMENT, fragShaderPath);

	//add Shader to Program
	pProgram->addShader(pVertexShader);
	pProgram->addShader(pFragShader);
	m_stateSet->setAttribute(pProgram);

	//判断地形是否存在
	if(m_textureManager)
	{
		//add uniform to the stateSet
		osg::ref_ptr<osg::Texture2D> pDemTexture = m_textureManager->getOrCreateDemTexture();
		osg::ref_ptr<osg::Uniform> pUniformTexture = new osg::Uniform("terrainTexture",m_demTextureIndex);
		m_stateSet->addUniform(pUniformTexture);
		m_stateSet->setTextureAttributeAndModes(m_demTextureIndex, pDemTexture);

		osg::Vec3 minCoord(m_textureManager->getTerrainBoundingBox()._min);
		osg::Vec3 maxCoord(m_textureManager->getTerrainBoundingBox()._max);
		minCoord.x() -= m_xBase;
		maxCoord.x() -= m_xBase;
		minCoord.y() -= m_YBase;
		maxCoord.y() -= m_YBase;
		osg::ref_ptr<osg::Uniform> pUniformMinCoord = new osg::Uniform("minCoord", minCoord);
		osg::ref_ptr<osg::Uniform> pUniformMaxCoord = new osg::Uniform("maxCoord", maxCoord);
		m_stateSet->addUniform(pUniformMinCoord);
		m_stateSet->addUniform(pUniformMaxCoord);

		bool isTerrainExist = true;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);

		osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale", m_terrainScale);
		m_stateSet->addUniform(pTerrainScaleUniform);

		osg::ref_ptr<osg::Uniform> pShiftAltitude = new osg::Uniform("shiftAltitude", m_pointSize/3);
		m_stateSet->addUniform(pShiftAltitude);
	}
	else
	{
		bool isTerrainExist = false;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);
	}

	//set the point sprite attribute and mapping the texture to per point
	osg::ref_ptr<osg::Point> pPoint = new osg::Point();
	pPoint->setSize(m_pointSize);
	m_stateSet->setAttribute(pPoint);
	m_stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED);

	//启用混合，设置炮检点图片透明的部分可以透视
	m_stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	m_stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	//启用深度测试，是炮检点不透明的部分遮挡住后面的物体
	m_stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	//设置渲染优先级
	m_stateSet->setRenderBinDetails(11, "RenderBin");

	osg::ref_ptr<osg::PointSprite> pPointSprite = new osg::PointSprite();

	m_stateSet->setTextureAttributeAndModes(m_pointTextureIndex, pPointSprite, osg::StateAttribute::ON);

	osg::ref_ptr<osg::Texture2D> pPointTexture = new osg::Texture2D();
	pPointTexture->setImage(m_pointImage);
	m_stateSet->setTextureAttributeAndModes(m_pointTextureIndex, pPointTexture, osg::StateAttribute::ON);
	osg::ref_ptr<osg::Uniform> pUniformPointTex = new osg::Uniform("pointTexture", m_pointTextureIndex);
	m_stateSet->addUniform(pUniformPointTex);
}


void KL3DPointsNode::reDraw()
{
	KL3DPointGeode* pPointGeode = NULL;

	KL3DPointGeodeSet::iterator pointIter = m_pointGeodes.begin();
	while(pointIter != m_pointGeodes.end())
	{
		pPointGeode = pointIter->second;
		pPointGeode->reDraw();

		pointIter++;
	}
}


void KL3DPointsNode::setType(KL3DLineType type)
{
	m_type = type;
}


KL3DLineType KL3DPointsNode::getType() const
{
	return m_type;
}


void KL3DPointsNode::setTerrainNode(osg::Node* pTerrainNode)
{
	m_terrainNode = pTerrainNode;
}


osg::Node* KL3DPointsNode::getTerrainNode()
{
	return m_terrainNode;
}


void KL3DPointsNode::setTerrainScale(osg::MatrixTransform* mt)
{
	if(mt)
	{
		osg::Matrix matrix = mt->getMatrix();
		m_terrainScale = (matrix.getScale()).z();
	}

}


void KL3DPointsNode::setTerrainScale(const float& pScale)
{
	m_terrainScale = pScale;
	osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale",m_terrainScale);
	m_stateSet->addUniform(pTerrainScaleUniform);	
}


float KL3DPointsNode::getTerrainScale()
{
	return m_terrainScale;
}


void KL3DPointsNode::setTextureManager(KL3DTextureManager* pTextureManager)
{
	m_textureManager = pTextureManager;
}


KL3DPointGeodeSet* KL3DPointsNode::getPointGeodes()
{
	return &m_pointGeodes;
}


KL3DPointGeode* KL3DPointsNode::getPointGeode(double id)
{
	KL3DPointGeodeSet::iterator iterPointGeode = m_pointGeodes.find(id);
	return iterPointGeode->second;
}


GLuint KL3DPointsNode::getVertexIndex() const
{
	return m_vertexIndex;
}


GLuint KL3DPointsNode::getColorIndex() const
{
	return m_colorIndex;
}


GLuint KL3DPointsNode::getFlagIndex() const
{
	return m_flagIndex;
}


void KL3DPointsNode::initPointImage(osg::Image* pointImage)
{
	m_pointImage = pointImage;
}


void KL3DPointsNode::setPointImage(osg::Image* pointImage)
{
	osg::ref_ptr<osg::Texture2D> pPointTexture = new osg::Texture2D();
	pPointTexture->setImage(pointImage);
	m_stateSet->setTextureAttributeAndModes(m_pointTextureIndex, pPointTexture, osg::StateAttribute::ON);
}


void KL3DPointsNode::setPointSize(const float& size)
{
	if(m_isPointSizeChange ==true)
	{
		m_pointSize = 5*size;

		osg::ref_ptr<osg::Point> pPoint = new osg::Point();
		pPoint->setSize(m_pointSize);
		m_stateSet->setAttribute(pPoint);

		float pSize = m_pointSize/3;
		osg::ref_ptr<osg::Uniform> pShiftAltitude = new osg::Uniform("shiftAltitude", pSize);
		m_stateSet->addUniform(pShiftAltitude);

	}
	
	if(size < 2.0f && m_isScroll)
	{
		m_isPointSizeChange = false;
		m_isScroll = false;
		return;
	}

	m_isScroll = false;
}


void KL3DPointsNode::setPointSizeChange(const bool& isChange, const bool& isScroll)
{
	m_isPointSizeChange = isChange;
	m_isScroll = isScroll;
}


float KL3DPointsNode::getPointSize() const
{
	return m_pointSize;
}


void KL3DPointsNode::setSourcePath(const std::string& sourcePath)
{
	m_sourcePath = sourcePath;
}


bool KL3DPointsNode::insertPointGeode(KL3DPointGeode* pPointGeode)
{
	double id = pPointGeode->getID();
	KL3DLineType type = pPointGeode->getType();

	KL3DPointGeodeSet* pPointGeodes = &m_pointGeodes;

	KL3DPointGeodeSet::iterator pointIter = pPointGeodes->find(id);
	if(pointIter == pPointGeodes->end())
	{
		pPointGeodes->insert(std::make_pair(id, pPointGeode));
		return true;
	}
	else
	{
		return false;
	}
}


bool KL3DPointsNode::deletePointGeode(const double& id)
{
	KL3DPointGeodeSet::iterator iterGeode = m_pointGeodes.find(id);
	if(iterGeode == m_pointGeodes.end())
	{
		return false;
	}

	KL3DPointGeode* pGeode = iterGeode->second;
	removeChild(pGeode);
	m_pointGeodes.erase(id);

	return true;
}


void KL3DPointsNode::setXBase(float xBase)
{
	m_xBase = xBase;
}


float KL3DPointsNode::getXBase() const
{
	return m_xBase;
}


void KL3DPointsNode::setYBase(float yBase)
{
	m_YBase = yBase;
}


float KL3DPointsNode::getYBase() const
{
	return m_YBase;
}


void KL3DPointsNode::setIsVisible(bool isVisible)
{
	setNodeMask(isVisible);
}


bool KL3DPointsNode::getIsVisible()
{
	return getNodeMask();
}


void KL3DPointsNode::setLabelIsVisible(bool isVisible)
{
	KL3DPointGeodeSet::iterator iterGeode = m_pointGeodes.begin();
	while(iterGeode != m_pointGeodes.end())
	{
		KL3DPointGeode* pPointGeode = iterGeode->second;
		pPointGeode->setLabelIsVisible(isVisible);
		iterGeode++;
	}
}


void KL3DPointsNode::setLabelInterval(const unsigned int& interval)
{
	KL3DPointGeodeSet::iterator iterGeode = m_pointGeodes.begin();
	while(iterGeode != m_pointGeodes.end())
	{
		KL3DPointGeode* pPointGeode = iterGeode->second;
		pPointGeode->setLabelInterval(interval);

		iterGeode++;
	}
}


void KL3DPointsNode::notifyAddTextureManager(KL3DTextureManager* pTextureManager)
{
	setTextureManager(pTextureManager);
	//判断地形是否存在
	if(m_textureManager)
	{
		//add uniform to the stateSet
		osg::ref_ptr<osg::Texture2D> pDemTexture = m_textureManager->getOrCreateDemTexture();
		osg::ref_ptr<osg::Uniform> pUniformTexture = new osg::Uniform("terrainTexture",m_demTextureIndex);
		m_stateSet->addUniform(pUniformTexture);
		m_stateSet->setTextureAttributeAndModes(m_demTextureIndex, pDemTexture);

		osg::Vec3 minCoord(m_textureManager->getTerrainBoundingBox()._min);
		osg::Vec3 maxCoord(m_textureManager->getTerrainBoundingBox()._max);
		minCoord.x() -= m_xBase;
		maxCoord.x() -= m_xBase;
		minCoord.y() -= m_YBase;
		maxCoord.y() -= m_YBase;
		osg::ref_ptr<osg::Uniform> pUniformMinCoord = new osg::Uniform("minCoord", minCoord);
		osg::ref_ptr<osg::Uniform> pUniformMaxCoord = new osg::Uniform("maxCoord", maxCoord);
		m_stateSet->addUniform(pUniformMinCoord);
		m_stateSet->addUniform(pUniformMaxCoord);

		bool isTerrainExist = true;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);

		osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale", m_terrainScale);
		m_stateSet->addUniform(pTerrainScaleUniform);

		osg::ref_ptr<osg::Uniform> pShiftAltitude = new osg::Uniform("shiftAltitude", m_pointSize/3);
		m_stateSet->addUniform(pShiftAltitude);
	}
}