#ifndef __KL3DGEOSPATIALEXTENTS_H__
#define __KL3DGEOSPATIALEXTENTS_H__

#include <osg/Vec2>
#include <osg/Vec2d>
/*#include "osg/CoordinateSystemNode"
#include "osg/Notify"*/
#include <osg/BoundingBox>
#include <osg/BoundingSphere>

#include <float.h>

/** GeospatialExtents contains xmin/max and ymin/max for a spatial boundary.
*/
/*!******************************************************
<br> ��˵������ά�۲�ϵͳextents��
********************************************************/
class KL3DGeospatialExtents
{
public:
	/*��Χ����Сֵ*/
    osg::Vec2d  _min;

	/*��Χ�����ֵ*/
    osg::Vec2d  _max;

	/*��־�� ��ʾ�Ƿ�Ϊ��ط�Χ*/
    bool        _isGeographic;
    
	/*Ĭ�Ϲ��캯��*/
    inline KL3DGeospatialExtents() : 
        _min(DBL_MAX,DBL_MAX),
        _max(-DBL_MAX,-DBL_MAX),
        _isGeographic(false) {}

	/*�������캯��*/
    inline KL3DGeospatialExtents(const KL3DGeospatialExtents& rhs):
        _min(rhs._min),
        _max(rhs._max),
        _isGeographic(rhs._isGeographic) {}

  /** ���ع��캯����xmin xΪ��Сֵ��ymin y��Сֵ�� xmax x���ֵ�� ymax y���ֵ��isGeographic �Ƿ�Ϊ��ط�Χ
  */
    inline KL3DGeospatialExtents(double xmin, double ymin, double xmax, double ymax, bool isGeographic) :
        _min(xmin, ymin),
        _max(xmax, ymax),
        _isGeographic(isGeographic) {}
   
	/*��ֵ����*/
    KL3DGeospatialExtents& operator = (const KL3DGeospatialExtents& rhs)
    {
        _min = rhs._min;
        _max = rhs._max;
        _isGeographic = rhs._isGeographic;
        return *this;
    }

	/*�����������=*/
    bool operator != (const KL3DGeospatialExtents& rhs) const
    {
        return (_min != rhs._min) || (_max != rhs._max) || (_isGeographic != rhs._isGeographic);
    }

	/*���������==*/
    bool operator == (const KL3DGeospatialExtents& rhs) const
    {
        return (_min == rhs._min) && (_max == rhs._max) && (_isGeographic == rhs._isGeographic);
    }

	/*���������>=*/
	bool operator >= (const KL3DGeospatialExtents& rhs) const
	{
		return (_min.x() <= rhs._min.x()) && (_min.y() <= rhs._min.y()) &&(_max.x() >= rhs._max.x()) &&(_max.y() >= rhs._max.y()) && (_isGeographic == rhs._isGeographic);
	}

	/*�ж��Ƿ����*/
    bool equivalent(const KL3DGeospatialExtents& rhs, double epsilon=1e-6) const
    {
        return osg::equivalent(_min.x(),rhs._min.x(),epsilon) &&
               osg::equivalent(_min.y(),rhs._min.y(),epsilon) && 
               osg::equivalent(_max.x(),rhs._max.x(),epsilon) && 
               osg::equivalent(_max.y(),rhs._max.y(),epsilon) && 
               _isGeographic == rhs._isGeographic;
    }

	/*�õ�x��Сֵ*/
    inline double& xMin() { return _min.x(); }
    inline double xMin() const { return _min.x(); }

	/*�õ�y��Сֵ*/
    inline double& yMin() { return _min.y(); }
    inline double yMin() const { return _min.y(); }

	/*�õ�x���ֵ*/
    inline double& xMax() { return _max.x(); }
    inline double xMax() const { return _max.x(); }

	/*�õ�y���ֵ*/
    inline double& yMax() { return _max.y(); }
    inline double yMax() const { return _max.y(); }

	/*��ʼ������*/
    inline void init()
    {
        _min.set(DBL_MAX,DBL_MAX);
        _max.set(-DBL_MAX,-DBL_MAX);
    }

	/*�ж϶����Ƿ���Ч*/
    inline bool valid() const
    {
        return _max.x()>=_min.x() &&  _max.y()>=_min.y();
    }

	/*�жϰ�Χ�в�Ϊ��*/
    inline bool nonZeroExtents() const
    {
        return valid() && _max.x()!=_min.x() &&  _max.y()!=_min.y();
    }

	/*�õ���Χ�а뾶*/
    inline double radius() const
    {
        return sqrt((radius2()));
    }

	/*��Χ�а뾶��ƽ��*/
    inline double radius2() const
    {
        return 0.25f*((_max-_min).length2());
    }

	/*�ж��Ƿ��ཻ��GeospatialExtents Ϊ�ཻ������ e �жϵķ�Χ�� xoffset ƫ����*/
    KL3DGeospatialExtents intersection(const KL3DGeospatialExtents& e, double xoffset) const
    {
        return KL3DGeospatialExtents(osg::maximum(xMin(),e.xMin()+xoffset),osg::maximum(yMin(),e.yMin()),
                                 osg::minimum(xMax(),e.xMax()+xoffset),osg::minimum(yMax(),e.yMax()),_isGeographic);
    }

    /** Return true if this bounding box intersects the specified bounding box. */
	/*�жϵ�ǰ��Χ���Ƿ���ĳ�������ཻ*/
    bool intersects(const KL3DGeospatialExtents& bb) const
    {
        if (_isGeographic)
        {
            // first check vertical axis overlap
            if (osg::maximum(yMin(),bb.yMin()) > osg::minimum(yMax(),bb.yMax())) return false;
            
            // next check if overlaps directly without any 360 degree horizontal shifts.
            if (osg::maximum(xMin(),bb.xMin()) <= osg::minimum(xMax(),bb.xMax())) return true;
            
            // next check if a 360 rotation will produce an overlap
            float rotationAngle = (xMin() > bb.xMin()) ? 360.0 : -360;
            return (osg::maximum(xMin(),bb.xMin()+rotationAngle) <= osg::minimum(xMax(),bb.xMax()+rotationAngle));
        }
        else
        {
            return (osg::maximum(xMin(),bb.xMin()) <= osg::minimum(xMax(),bb.xMax()) &&
                    osg::maximum(yMin(),bb.yMin()) <= osg::minimum(yMax(),bb.yMax()));
        }
    }

	/*���ݰ�Χ����չ����Χ*/
    void expandBy(const osg::BoundingSphere& sh)
    {
        if (!sh.valid()) return;

        if(sh._center.x()-sh._radius<_min.x()) _min.x() = sh._center.x()-sh._radius;
        if(sh._center.x()+sh._radius>_max.x()) _max.x() = sh._center.x()+sh._radius;

        if(sh._center.y()-sh._radius<_min.y()) _min.y() = sh._center.y()-sh._radius;
        if(sh._center.y()+sh._radius>_max.y()) _max.y() = sh._center.y()+sh._radius;
    }

	/*����ĳ����չ����Χ*/
    inline void expandBy(const osg::Vec3& v)
    {
        if(v.x()<_min.x()) _min.x() = v.x();
        if(v.x()>_max.x()) _max.x() = v.x();

        if(v.y()<_min.y()) _min.y() = v.y();
        if(v.y()>_max.y()) _max.y() = v.y();
    }

	/*���� extents��չ����Χ*/
    void expandBy(const KL3DGeospatialExtents& e)
    {
        if (!e.valid()) return;

        if(e._min.x()<_min.x()) _min.x() = e._min.x();
        if(e._max.x()>_max.x()) _max.x() = e._max.x();

        if(e._min.y()<_min.y()) _min.y() = e._min.y();
        if(e._max.y()>_max.y()) _max.y() = e._max.y();
    }

	/*�ж�extents���Ƿ������v*/
	bool isContain(const osg::Vec3& v)
	{
		if (v.x()>=_min.x() &&v.y()>=_min.y()&&v.x()<=_max.x()&&v.y()<=_max.y())
		{
			return true;
		}
		return false;
	}

	/*�ж������Ƿ����extents����*/
	bool isContain(const KL3DGeospatialExtents& e)
	{
		if(e._min.x() < _min.x()) return false;
		if(e._max.x() > _max.x()) return false;

		if(e._min.y() < _min.y()) return false;
		if(e._max.y() > _max.y()) return false;

		return true;
	}
};

/*
class KLGeoPolySelectExtents
{
public:
	osg::ref_ptr<osg::Vec2Array> m_allVertexArray;
	osg::ref_ptr<osg::Vec2Array> m_boundVertexArray;

	inline KLGeoPolySelectExtents()
	{
		m_allVertexArray = new osg::Vec2Array;
		m_boundVertexArray = new osg::Vec2Array;
	}

	inline KLGeoPolySelectExtents(osg::ref_ptr<osg::Vec2Array> pointArray)
	{
		m_allVertexArray = pointArray;
		m_boundVertexArray = new osg::Vec2Array;
	}

	inline KLGeoPolySelectExtents(const KLGeoPolySelectExtents& rhs)
	{
		m_allVertexArray = rhs.m_allVertexArray;
		m_boundVertexArray = rhs.m_boundVertexArray;
	}

	KLGeoPolySelectExtents& operator = (const KLGeoPolySelectExtents& rhs)
	{
		m_allVertexArray->insert(m_allVertexArray->begin(),rhs.m_allVertexArray->begin(),rhs.m_allVertexArray->end());
		m_boundVertexArray->insert(m_boundVertexArray->begin(),rhs.m_boundVertexArray->begin(),rhs.m_boundVertexArray->end());
		return *this;
	}

	void move(float dx,float dy)
	{
		if(m_boundVertexArray.valid())
		{
			for(int i=0;i<m_boundVertexArray->size();i++)
			{
				(*m_boundVertexArray)[i].x() += dx;
				(*m_boundVertexArray)[i].y() += dy;
			}
		}
	}

	void init();

	float multiply(osg::Vec2 p1,osg::Vec2 p2,osg::Vec2 p0)
	{
		return (p1.x()-p0.x())*(p2.y()-p0.y())-(p2.x()-p0.x())*(p1.y()-p0.y());
	}

	float dis(osg::Vec2 p1,osg::Vec2 p2)
	{
		return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
	}

	void vertexSort();

	bool intersects(const GeospatialExtents& bb)const;

    void expandBy(const osg::Vec3& v)
	{
		m_allVertexArray->push_back(osg::Vec2(v.x(),v.y()));
	}

	void expandBy(const osg::Vec2& v)
	{
		m_allVertexArray->push_back(v);
	}

	void expandBy(const GeospatialExtents& e)
	{
		if(!e.valid())
			return;

		m_allVertexArray->push_back(osg::Vec2(e.xMin(),e.yMin()));
		m_allVertexArray->push_back(osg::Vec2(e.xMax(),e.yMin()));
		m_allVertexArray->push_back(osg::Vec2(e.xMin(),e.yMax()));
		m_allVertexArray->push_back(osg::Vec2(e.xMax(),e.yMax()));
	} 

	bool isContain(const osg::Vec3& v);
	bool isContain(const osg::Vec2& v);
};*/

#endif