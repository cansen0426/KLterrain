#include <osg/LineWidth>
#include <osg/MatrixTransform>

#include "KL3DLinesNode.h"

const std::string m_vertexShaderPath = "shaders/KL3DDesignLinesRender.vert";
const std::string m_fragShaderPath = "shaders/KL3DDesignLinesRender.frag";

KL3DLinesNode::KL3DLinesNode() :
	m_stateSet(NULL),
	m_isDisplay(false),
	m_isDisplayLineLabel(false),
	m_terrainNode(NULL),
	m_textureManager(NULL),
	m_vertexIndex(0),
	m_colorIndex(1),
	m_demTextureIndex(0),
	m_lineSize(4.0f),
	m_color(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	m_sourcePatch(""),
	m_xBase(0.0f),
	m_yBase(0.0f),
	m_terrainScale(1.0f)
{

}


KL3DLinesNode::~KL3DLinesNode()
{

}


void KL3DLinesNode::init()
{
	//init the stateSet
	m_stateSet = getOrCreateStateSet();

	//create program
	osg::ref_ptr<osg::Program> pProgram = new osg::Program();
	pProgram->addBindAttribLocation("vertexArr", m_vertexIndex);
	pProgram->addBindAttribLocation("colorArr", m_colorIndex);

	//add shader to render the lines
	std::string vertexShaderPath = m_sourcePatch + m_vertexShaderPath;
	std::string fragShaderPath = m_sourcePatch + m_fragShaderPath;

	osg::ref_ptr<osg::Shader> pVertexShader = osg::Shader::readShaderFile(osg::Shader::VERTEX, vertexShaderPath);
	osg::ref_ptr<osg::Shader> pFragShader = osg::Shader::readShaderFile(osg::Shader::FRAGMENT, fragShaderPath);

	//add shader to program 
	pProgram->addShader(pVertexShader);
	pProgram->addShader(pFragShader);
	m_stateSet->setAttribute(pProgram);

	if(m_textureManager)
	{
		//add uniform to the stateSet
		osg::ref_ptr<osg::Texture2D>  pDemTexture = m_textureManager->getOrCreateDemTexture();
		osg::ref_ptr<osg::Uniform> pUniformTexture = new osg::Uniform("terrainTexture", m_demTextureIndex);
		m_stateSet->addUniform(pUniformTexture);
		m_stateSet->setTextureAttributeAndModes(m_demTextureIndex, pDemTexture);

		osg::Vec3 minCoord(m_textureManager->getTerrainBoundingBox()._min);
		osg::Vec3 maxCoord(m_textureManager->getTerrainBoundingBox()._max);
		minCoord.x() -= m_xBase;
		maxCoord.x() -= m_xBase;
		minCoord.y() -= m_yBase;
		maxCoord.y() -= m_yBase;
		osg::ref_ptr<osg::Uniform> pUniformMinCoord = new osg::Uniform("minCoord", minCoord);
		osg::ref_ptr<osg::Uniform> pUniformMaxCoord = new osg::Uniform("maxCoord", maxCoord);
		m_stateSet->addUniform(pUniformMinCoord);
		m_stateSet->addUniform(pUniformMaxCoord);

		osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale", m_terrainScale);
		m_stateSet->addUniform(pTerrainScaleUniform);

		bool isTerrainExist = true;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);

	}
	else
	{
		bool isTerrainExist = false;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);
	}


}


void KL3DLinesNode::reDraw()
{
	KL3DLineGeode* pLineGeode = NULL;

	KL3DLineGeodeSet::iterator lineGeodeIter = m_lineGeodes.begin();
	while(lineGeodeIter != m_lineGeodes.end())
	{
		pLineGeode = lineGeodeIter->second;
		pLineGeode->reDraw();
		
		lineGeodeIter++;
	}
}


void KL3DLinesNode::setType(KL3DLineType type)
{
	m_type = type;
}


KL3DLineType KL3DLinesNode::getType() const
{
	return m_type;
}


void KL3DLinesNode::setIsDisplay(bool isDisplay)
{
	m_isDisplay = isDisplay;
	
	KL3DLineGeodeSet::iterator iterLineGeode = m_lineGeodes.begin();
	while(iterLineGeode != m_lineGeodes.end())
	{
		KL3DLineGeode* p3DLineGeode = iterLineGeode->second;
		p3DLineGeode->setIsDisplay(isDisplay);
		iterLineGeode++;
	}
}


bool KL3DLinesNode::getIsDisplay() const
{
	return m_isDisplay;
}


void KL3DLinesNode::setLinesLabelIsVisible(bool isVisible)
{
	m_isDisplayLineLabel = isVisible;

	KL3DLineGeodeSet::iterator iterLineGeode = m_lineGeodes.begin();
	while(iterLineGeode != m_lineGeodes.end())
	{
		KL3DLineGeode* p3DLineGeode = iterLineGeode->second;
		p3DLineGeode->setLineLabelIsVisible(isVisible);

		iterLineGeode++;
	}
}


bool KL3DLinesNode::getLinesLabelIsVisible() const
{
	return m_isDisplayLineLabel;
}


void KL3DLinesNode::setTerrainNode(osg::Node* pTerrainNode)
{
	m_terrainNode = pTerrainNode;
}


osg::Node* KL3DLinesNode::getTerrainNode()
{
	return m_terrainNode;
}


void KL3DLinesNode::setTextureManager(KL3DTextureManager* pTextureManager)
{
	m_textureManager = pTextureManager;
}


void KL3DLinesNode::setLineSize(const float& size)
{
	m_lineSize = size;

	osg::ref_ptr<osg::LineWidth> pLineSize = new osg::LineWidth();
	pLineSize->setWidth(size);
	m_stateSet = getOrCreateStateSet();
	m_stateSet->setAttribute(pLineSize);
}


float KL3DLinesNode::getLineSize() const
{
	return m_lineSize;
}


void KL3DLinesNode::setLineColor(const osg::Vec4& color)
{
	m_color = color;

	KL3DLineGeodeSet::iterator lineGeodeIter = m_lineGeodes.begin();
	while(lineGeodeIter != m_lineGeodes.end())
	{
		KL3DLineGeode* pLineGeode = lineGeodeIter->second;
		pLineGeode->setColor(color);

		lineGeodeIter++;
	}
}


osg::Vec4 KL3DLinesNode::getLineColor() const
{
	return m_color;
}


GLuint KL3DLinesNode::getVertexIndex() const
{
	return m_vertexIndex;
}


GLuint KL3DLinesNode::getColorIndex() const
{
	return m_colorIndex;
}


void KL3DLinesNode::setSourcePath(const std::string& sourcePath)
{
	m_sourcePatch = sourcePath;
}


void KL3DLinesNode::setXBase(const float& xBase)
{
	m_xBase = xBase;
}


float KL3DLinesNode::getXBase() const
{
	return m_xBase;
}


void KL3DLinesNode::setYBase(const float& yBase)
{
	m_yBase = yBase;
}


float KL3DLinesNode::getYBase() const
{
	return m_yBase;
}


KL3DLineGeodeSet* KL3DLinesNode::getLinesGeodes()
{
	return &m_lineGeodes;
}


KL3DLineGeode* KL3DLinesNode::getLineGeode(double id)
{
	if(m_lineGeodes.size() == 0)
	{
		return NULL;
	}

	KL3DLineGeodeSet::iterator lineGeodeIter = m_lineGeodes.find(id);
	if(lineGeodeIter != m_lineGeodes.end())
	{
		return lineGeodeIter->second;
	}
	else
	{
		return NULL;
	}
}


bool KL3DLinesNode::insertLineGeode(KL3DLineGeode* pLineGeode)
{
	if(m_lineGeodes.size() == 0)
	{
		m_lineGeodes.insert(std::make_pair(pLineGeode->getID(), pLineGeode));
		return true;
	}

	double id = pLineGeode->getID();
	KL3DLineGeodeSet::iterator lineGeodeIter = m_lineGeodes.find(id);
	if(lineGeodeIter == m_lineGeodes.end())
	{
		m_lineGeodes.insert(std::make_pair(pLineGeode->getID(), pLineGeode));
		return true;
	}
	else
	{
		return
			 false;
	}
}

bool KL3DLinesNode::deleteLineGeode(const double& id)
{
	KL3DLineGeodeSet::iterator iterLineGeode = m_lineGeodes.find(id);
	if(iterLineGeode == m_lineGeodes.end())
	{
		return false;
	}

	KL3DLineGeode* pLineGeode = iterLineGeode->second;
	removeChild(pLineGeode);
	m_lineGeodes.erase(id);

	return true;
}


void KL3DLinesNode::notifyAddTextureManager(KL3DTextureManager* pTextureManager)
{
	setTextureManager(pTextureManager);

	if(m_textureManager)
	{
		//add uniform to the stateSet
		osg::ref_ptr<osg::Texture2D>  pDemTexture = m_textureManager->getOrCreateDemTexture();
		osg::ref_ptr<osg::Uniform> pUniformTexture = new osg::Uniform("terrainTexture", m_demTextureIndex);
		m_stateSet->addUniform(pUniformTexture);
		m_stateSet->setTextureAttributeAndModes(m_demTextureIndex, pDemTexture);

		osg::Vec3 minCoord(m_textureManager->getTerrainBoundingBox()._min);
		osg::Vec3 maxCoord(m_textureManager->getTerrainBoundingBox()._max);
		minCoord.x() -= m_xBase;
		maxCoord.x() -= m_xBase;
		minCoord.y() -= m_yBase;
		maxCoord.y() -= m_yBase;
		osg::ref_ptr<osg::Uniform> pUniformMinCoord = new osg::Uniform("minCoord", minCoord);
		osg::ref_ptr<osg::Uniform> pUniformMaxCoord = new osg::Uniform("maxCoord", maxCoord);
		m_stateSet->addUniform(pUniformMinCoord);
		m_stateSet->addUniform(pUniformMaxCoord);

		osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale", m_terrainScale);
		m_stateSet->addUniform(pTerrainScaleUniform);

		bool isTerrainExist = true;
		osg::ref_ptr<osg::Uniform> pTerrainUniform = new osg::Uniform("isTerrainExist", isTerrainExist);
		m_stateSet->addUniform(pTerrainUniform);

	}
}


void KL3DLinesNode::setTerrainScale(osg::MatrixTransform* mt)
{
	if(mt)
	{
		osg::Matrix intertMatrix = mt->getInverseMatrix();
		m_terrainScale = (intertMatrix.getScale()).z();
	}
}


void KL3DLinesNode::setTerrainScale(const float& pScale)
{
	m_terrainScale = pScale;
	osg::ref_ptr<osg::Uniform> pTerrainScaleUniform = new osg::Uniform("terrainScale",m_terrainScale);
	m_stateSet->addUniform(pTerrainScaleUniform);	
}