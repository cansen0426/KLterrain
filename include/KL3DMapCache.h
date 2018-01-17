#ifndef __KL3DMAPCACHE_H__
#define __KL3DMAPCACHE_H__

#include <map>
#include <vector>

#include "KL3DLine.h"
#include "KL3DCommonStruct.h"

/*!****************************************************
<br>��˵������ά�۲�ϵͳ�����ࣨ��Ӧ�����ڵ������۲�ϵͳ��
*******************************************************/
/*!�ߵļ���*/
#define KL3DLineSet std::map<double, KL3DLine*>
#define KL3DEditPointSet std::vector<KL3DEditPoint>
#define KL3DEditLineSet std::vector<KL3DLine*>

class KL3DMapCache
{
public:
	/*!Ĭ�Ϲ��캯��*/
	KL3DMapCache();

	/*!Ĭ����������*/
	~KL3DMapCache();

	/*!����ID,�۲�ϵͳ�ı�ʶ*/
	void setID(const std::string& id);

	/*!�õ��۲�ϵͳ�ı�ʶ*/
	std::string getID() const;

	/*!�õ����ߵļ���*/
	KL3DLineSet* getShotLineSet();

	/*!�õ��첨�ߵļ���*/
	KL3DLineSet* getRcvLineSet();

	/*!�õ��༭��ļ���*/
	KL3DEditPointSet* getEditPoints();

	/*!�õ��༭�߼���*/
	KL3DEditLineSet* getEditLines();

	/*!��ѯ�õ��ڼ�����*/
	KL3DPoint* get3DPoint(const double& lineID, const double& pointID, const short& samestakeID, KL3DLineType lineType);

	/*!��۲�ϵͳ�в�������*/
	bool insertLine(KL3DLine* pLine);

	/*!ɾ����ά������*/
	bool deleteLine(KL3DLine* pLine);

	/*!�����ߺź����͵õ���ά�߶���*/
	KL3DLine* getLine(double id, KL3DLineType type);

	/*!��۲�ϵͳ�в���༭��*/
	bool insertEditPoint(KL3DEditPoint pEditPoint);

	/*!��۲�ϵͳ�в���༭��*/
	bool insertEditLine(KL3DLine* pLine);

	/*!��۲�ϵͳ�в����ϵƬ�ڵ�*/
	bool insertPatchSelPoint(KL3DEditPoint pPatchSelPoint);

	/*!�õ��۲�ϵͳ�й�ϵƬ�ڵ㼯��*/
	KL3DEditPointSet* getPatchSelPoints();

	/*!�õ��۲�ϵͳ�й�ϵƬ�첨�㼯��*/
	KL3DEditPointSet* getPatchDstPoints();

	/*!���ѡ������*/
	void clearEditData();

	/*!��չ�ϵƬ����*/
	void clearPatchPoints();

	/*!����x����ƫ����*/
	void setXOffset(const float& xOffset);

	/*!����y����ƫ����*/
	void setYOffset(const float& yOffset);

	/*!��ȡx����ƫ����*/
	float getXOffset() const;

	/*!��ȡy����ƫ����*/
	float getYOffset() const;

	/*!���ñ༭�����ƶ��ľ��룺x����*/
	void setXMoveOffset(double& offset);

	/*!���ñ༭�����ƶ��ľ��룺y����*/
	void setYMoveOffset(double& offset);

	/*!�õ��༭�����ƶ��ľ��룺x����*/
	double getXMoveOffset() const;

	/*!�õ��༭�����ƶ��ľ��룺y����*/
	double getYMoveOffset() const;

	/*!������ر�ƫ����*/
	void setDePature(const double& depature);

	/*!�õ���ر��ƫ����*/
	double getDepature() const;

private:
	/*!ID:string���ͣ��۲�ϵͳΨһ��ʶ*/
	std::string m_id;

	/*!���߼���*/
	KL3DLineSet* m_shotLines;

	/*!�첨�߼���*/
	KL3DLineSet* m_rcvLines;

	/*!�༭�㼯��*/
	KL3DEditPointSet m_editPoints;

	/*!�༭�߼���*/
	KL3DEditLineSet m_editLines;

	/*!��ϵƬ�ڵ㼯��*/
	KL3DEditPointSet m_patchSelPoints;

	/*!��ϵƬ�첨�㼯��*/
	KL3DEditPointSet m_patchDstPoints;

	/*!�༭���ƶ�ƫ�ƾ��룺x����*/
	double m_xMoveOffset;

	/*!�༭���ƶ�ƫ�ƾ��룺y����*/
	double m_yMoveOffset;

	/*!����x����ƫ����*/
	float m_xOffset;

	/*!����y����ƫ����*/
	float m_yOffset;

	/*!��ر��ƫ���������ھ������*/
	double m_depature;



};

#endif