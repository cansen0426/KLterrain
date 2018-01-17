
#include <omp.h> 

#include "KL3DTerrainTileManager.h"
#include <osg/Vec3f>

#include<iostream>

bool isExistInvalidValue(osg::HeightField* hf, double x, double y)
{
	double r, c;
	c = (x - hf->getOrigin().x()) / hf->getXInterval();
	r = (y - hf->getOrigin().y()) / hf->getYInterval();

	int rowMin = osg::maximum((int)floor(r), 0);
	int rowMax = osg::maximum(osg::minimum((int)ceil(r), (int)(hf->getNumRows()-1)), 0);
	int colMin = osg::maximum((int)floor(c), 0);
	int colMax = osg::maximum(osg::minimum((int)ceil(c), (int)(hf->getNumColumns()-1)), 0);

	if(rowMin > rowMax) rowMin = rowMax;
	if(colMin > colMax) colMin = colMax;

	if(hf->getHeight(colMax, rowMax) == -99999 || hf->getHeight(colMin, rowMax) == -99999 ||
		hf->getHeight(colMax, rowMin) == -999999 || hf->getHeight(colMin, rowMin) == -99999)
		return true;
	else
		return false;
}


KL3DTerrainTileManager::KL3DTerrainTileManager(osg::Node* rootNode):
		m_root(rootNode),
		m_curPos(0),
		m_paralNum(PARALLELNUM),
		m_xOffset(0.0f),
		m_yOffset(0.0f)
{

}

/**
* �������m_TileMap��Ȼ������m_memVisitor�࣬������OSG�������У���Ч��TerrainTile�ڵ㡣
*/
void KL3DTerrainTileManager::gatherCurrentOSGScenceTerrainTile()
{
	m_tileMap.clear();
	m_extentsVect.clear();
	m_tileIDVect.clear();
	KL3DTerrainTileVisitor m_memVisitor(this);
	m_root->accept(m_memVisitor);
}


/**
* �õ�zֵ������x��yֵ�ڵ�ǰ��ͼ�ϣ�ͨ����ֵ�õ���Ӧ�ĸ߳�ֵ
*/
void KL3DTerrainTileManager::getValue(float x, float y, float& z)
{
	osg::Vec3f vec;
	vec.x()=x;
	vec.y()=y;

	if ((m_extentsVect.size() > 0) && (m_extentsVect[m_curPos].isContain(vec)))
	{
		//�ڵ�ǰָ�򻺴���
		osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[m_curPos]]->getElevationLayer());
		/*z=getInterpolatedValue(hf->getHeightField(),x,y);
				return;*/
		if(!isExistInvalidValue(hf->getHeightField(), x, y))
			z = getInterpolatedValue(hf->getHeightField(), x, y);
		else
			z = -99999;
		return;
		
	}

	//��ֵx��y���ڵ�tile
	for(int i=0;i<m_extentsVect.size();i++)
	{		
		if (m_extentsVect[i].isContain(vec))
		{
			//���ҵ��ڴ�ģ�鷶Χ
			osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[i]]->getElevationLayer());
			/*z=getInterpolatedValue(hf->getHeightField(),x,y);
			m_curPos=i;
			break;*/
			if(!isExistInvalidValue(hf->getHeightField(),x ,y))
				z = getInterpolatedValue(hf->getHeightField(), x, y);
			else
				z = -99999;
			m_curPos = i;
			break;

		}
	}
}


/**
* �õ�zֵ������x��yֵ�ڵ�ǰ��ͼ�ϣ�ͨ����ֵ�õ���Ӧ�ĸ߳�ֵ
*/
void KL3DTerrainTileManager::getValue(float x, float y, osg::Vec3f& value)
{
}


/**
* ����vec3f�е�x,y�õ�z ,��vec�е�x,y���������ģ������ٶȻ�ȽϿ�
*/
void KL3DTerrainTileManager::getValue(std::vector<osg::Vec3f>& vecs)
{
	if (vecs.size()<m_paralNum)
	{ //����������٣��������ò���
		for (int i=0;i<vecs.size();i++)
		{
			getValue(vecs[i].x(),vecs[i].y(),vecs[i].z());
		}
	}
	else
	{
		//ʹ�ò��д���
		//���ò����߳�����
		int prossNum=omp_get_num_procs();
		omp_set_num_threads(prossNum);
		//�õ����鲢�еĿ���
		int blockNum=vecs.size()/prossNum;
		int j,pos,curPos;
#pragma omp parallel for private(j,pos,curPos)
		for (int i=0;i<prossNum;i++)
		{
			pos=i*blockNum;
			curPos=0; //��ʶ��ǰheightfieldlayerλ��
			for (j=0;j<blockNum;j++,pos++)
			{
				
				if (m_extentsVect[curPos].isContain(vecs[pos]))
				{
					//�ڵ�ǰָ�򻺴���
					osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[curPos]]->getElevationLayer());
					vecs[pos].z()=getInterpolatedValue(hf->getHeightField(),vecs[pos].x(),vecs[pos].y());
				}else{
					//��ֵx��y���ڵ�tile
					for(int d=0;d<m_extentsVect.size();d++)
					{		
						if (m_extentsVect[d].isContain(vecs[pos]))
						{
							//���ҵ��ڴ�ģ�鷶Χ
							osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[d]]->getElevationLayer());
							vecs[pos].z()=getInterpolatedValue(hf->getHeightField(),vecs[pos].x(),vecs[pos].y());
							curPos=d;						
						}else
						{
							continue;
						}
					}
				}
			}			
		}//end  parallel for 
		//����ʣ�����ֵ

		for (int pos=prossNum*blockNum;pos<vecs.size();pos++)
		{
			getValue(vecs[pos].x(),vecs[pos].y(),vecs[pos].z());
		}
	}

}

void KL3DTerrainTileManager::getValue(osg::Vec3Array* vecs, int size)
{
	int jingshen = false;
	if (size<m_paralNum)
	{ //����������٣��������ò���
		for (int i=0;i<size;i++)
		{
			getValue((*vecs)[i].x(),(*vecs)[i].y(),(*vecs)[i].z());
		}
	}
	else
	{
		////ʹ�ò��д���
		//���ò����߳�����
		int prossNum=omp_get_num_procs();
		//omp_set_num_threads(prossNum);
		//�õ����鲢�еĿ���
		int blockNum=size/prossNum;
		int j,pos,curPos;
		//#pragma omp parallel for private(j,pos,curPos)
		for (int i=0;i<prossNum;i++)
		{
			pos=i*blockNum;
			curPos=0;                   //��ʶ��ǰheightfieldlayerλ��
			for (j=0;j<blockNum;j++,pos++)
			{

				if ((m_extentsVect.size() > 0) && (m_extentsVect[curPos].isContain( (*vecs)[pos] )))
				{
					//�ڵ�ǰָ�򻺴���
					osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[curPos]]->getElevationLayer());
					/*(*vecs)[pos].z()=getInterpolatedValue(hf->getHeightField(),(*vecs)[pos].x(),(*vecs)[pos].y());*/
					if(!isExistInvalidValue(hf->getHeightField(),(*vecs)[pos].x(),(*vecs)[pos].y()))
					{
						float heightValue = getInterpolatedValue(hf->getHeightField(),(*vecs)[pos].x(),(*vecs)[pos].y());
						if(heightValue != -99999.0f)
						{
							(*vecs)[pos].z() = heightValue;
						}
						else
						{
							jingshen = true;
						}
					}
					else
					{
						jingshen = true;
					}
				}else{
					//��ֵx��y���ڵ�tile
					for(int d=0;d<m_extentsVect.size();d++)
					{		
						if (m_extentsVect[d].isContain((*vecs)[pos]))
						{
							//���ҵ��ڴ�ģ�鷶Χ
							osgTerrain::HeightFieldLayer* hf=dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[d]]->getElevationLayer());
							/*(*vecs)[pos].z()=getInterpolatedValue(hf->getHeightField(),(*vecs)[pos].x(),(*vecs)[pos].y());
							curPos=d;*/
							if(!isExistInvalidValue(hf->getHeightField(),(*vecs)[pos].x(),(*vecs)[pos].y()))
							{
								float heightValue = getInterpolatedValue(hf->getHeightField(), (*vecs)[pos].x(),(*vecs)[pos].y());
								if(heightValue != -99999.0f)
								{
									(*vecs)[pos].z() = heightValue;
								}
								else
								{
									jingshen = true;
								}
							}
							else
							{
								jingshen = true;
							}
							curPos = d;
						}else
						{
							continue;
						}
					}
				}
			}			
		}//end  parallel for 
		//����ʣ�����ֵ

		for (int pos=prossNum*blockNum;pos<size;pos++)
		{
			getValue((*vecs)[pos].x(),(*vecs)[pos].y(),(*vecs)[pos].z());
		}
	}
}



/**
* ���ݸ߳���x��y���꣨ʵ������ֵ��,�õ��߳�ֵ
*/
float KL3DTerrainTileManager::getInterpolatedValue(osg::HeightField* hf, double x, double y)
{
	double r, c;
	c = (x - hf->getOrigin().x()) / hf->getXInterval();
	r = (y - hf->getOrigin().y()) / hf->getYInterval();

	int rowMin = osg::maximum((int)floor(r), 0);
	int rowMax = osg::maximum(osg::minimum((int)ceil(r), (int)(hf->getNumRows()-1)), 0);
	int colMin = osg::maximum((int)floor(c), 0);
	int colMax = osg::maximum(osg::minimum((int)ceil(c), (int)(hf->getNumColumns()-1)), 0);

	if (rowMin > rowMax) rowMin = rowMax;
	if (colMin > colMax) colMin = colMax;

	float urHeight = hf->getHeight(colMax, rowMax);
	float llHeight = hf->getHeight(colMin, rowMin);
	float ulHeight = hf->getHeight(colMin, rowMax);
	float lrHeight = hf->getHeight(colMax, rowMin);

	double x_rem = c - (int)c;
	double y_rem = r - (int)r;

	double w00 = (1.0 - y_rem) * (1.0 - x_rem) * (double)llHeight;
	double w01 = (1.0 - y_rem) * x_rem * (double)lrHeight;
	double w10 = y_rem * (1.0 - x_rem) * (double)ulHeight;
	double w11 = y_rem * x_rem * (double)urHeight;

	float result = (float)(w00 + w01 + w10 + w11);

	return result;
}

/**
* ����ʹ�ã�Ϊ����ָ���Ķ���ֵ���������Χ�ĸ��������ֵ                                                                      
*/
void KL3DTerrainTileManager::printSroundVec(std::vector<osg::Vec3f>& vecs)
{
	for (int i=0;i<vecs.size();i++)
	{
		for(int j=0;j<m_extentsVect.size();j++)
		{		
			if (m_extentsVect[j].isContain(vecs[i]))
			{
				//���ҵ��ڴ�ģ�鷶Χ
				osg::HeightField* hf=(dynamic_cast<osgTerrain::HeightFieldLayer*>(m_tileMap[m_tileIDVect[j]]->getElevationLayer()))->getHeightField();
				double r, c;
				c = (vecs[i].x() - hf->getOrigin().x()) / hf->getXInterval();
				r = (vecs[i].y() - hf->getOrigin().y()) / hf->getYInterval();

				int rowMin = osg::maximum((int)floor(r), 0);
				int rowMax = osg::maximum(osg::minimum((int)ceil(r), (int)(hf->getNumRows()-1)), 0);
				int colMin = osg::maximum((int)floor(c), 0);
				int colMax = osg::maximum(osg::minimum((int)ceil(c), (int)(hf->getNumColumns()-1)), 0);

				if (rowMin > rowMax) rowMin = rowMax;
				if (colMin > colMax) colMin = colMax;

				/*float urHeight = hf->getHeight(colMax, rowMax);
				float llHeight = hf->getHeight(colMin, rowMin);
				float ulHeight = hf->getHeight(colMin, rowMax);
				float lrHeight = hf->getHeight(colMax, rowMin);*/
				osg::Vec3f urvec3f=hf->getVertex(colMax,rowMax);
				osg::Vec3f llvec3f=hf->getVertex(colMin,rowMin);
				osg::Vec3f ulvec3f=hf->getVertex(colMin,rowMax);
				osg::Vec3f lrvec3f=hf->getVertex(colMax,rowMin);
				//print sround vertex
				std::cout<< "----------sround vertex ----------------" <<std::endl;
				std::cout << llvec3f.x() <<" " <<llvec3f.y()<< " "<<llvec3f.z() <<std::endl;
				std::cout << ulvec3f.x() << " "<< ulvec3f.y()<< " " << ulvec3f.z() << std::endl;
				std::cout<< lrvec3f.x() << " "<< lrvec3f.y()<< " " << lrvec3f.z() << std::endl;
				std::cout<< urvec3f.x() << " "<< urvec3f.y() << " "<< urvec3f.z() << std::endl;
				std::cout<< vecs[i].x()<< " "<<vecs[i].y()<< " "<< vecs[i].z()<<std::endl;

			}
		}
	}
}


void KL3DTerrainTileManager::setXOffset(const float& xOffset)
{
	m_xOffset = xOffset;
}


void KL3DTerrainTileManager::setYOffset(const float& yOffset)
{
	m_yOffset = yOffset;
}


float KL3DTerrainTileManager::getXOffset() const
{
	return m_xOffset;
}



float KL3DTerrainTileManager::getYOffset() const
{
	return m_yOffset;
}
