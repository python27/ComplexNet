
// ComplexNetView.h : CComplexNetView ��Ľӿ�
//

#pragma once


class CComplexNetView : public CScrollView
{
protected: // �������л�����
	CComplexNetView();
	DECLARE_DYNCREATE(CComplexNetView)

// ����
public:
	CComplexNetDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CComplexNetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On9nodes();
	afx_msg void OnFeatureDegree();
	afx_msg void OnFeatureDegreedis();
	afx_msg void OnFeatureDegreecorr();
	afx_msg void OnFeatureCluster();
	afx_msg void OnFeatureAvecluster();
	afx_msg void OnFeatureClusterdis();
	afx_msg void OnFeatureClusterdegree();
	afx_msg void OnFeatureApl();
	afx_msg void OnFeaturePathdis();
	afx_msg void OnAppEigenvector();
	afx_msg void OnCloseness();
	afx_msg void OnAppFlowBetw();
	afx_msg void OnNomination();
	afx_msg void OnKernighanLin();
	afx_msg void On13nodes();
	afx_msg void On13nodestwo();
	afx_msg void On10nodes();
	afx_msg void OnSexnetwork();
	afx_msg void OnKarate();
	afx_msg void OnNewRegular();
	afx_msg void OnNetRandom();
	afx_msg void OnNetWssmall();
	afx_msg void OnNetNWSmall();
	afx_msg void OnNetBA();
	afx_msg void OnNetLiuLai();
	afx_msg void OnDeterminswei();
	afx_msg void OnDeterminUrt();
	afx_msg void OnDeterminSwurt();
	afx_msg void OnDeterminPinwheel();
	afx_msg void OnDeterminSwirl();
	afx_msg void OnDeterminTssfsw();
	afx_msg void OnDeterminTs();
	afx_msg void OnDeterminMei();
	afx_msg void OnBoxCounting();
	afx_msg void OnGroupnetSimple();
	afx_msg void OnSyncLamda2();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFeatureAvedegree();
	afx_msg void OnNetUrt();
	afx_msg void OnNetMynet1();
	afx_msg void OnDriverNodesStructuralControllability();
	afx_msg void OnDriverNodesExactControllability();
	afx_msg void OnDriverFastAlgo();
	afx_msg void OnDriversRankFast();
	afx_msg void OnSyncLamdaratio();
	afx_msg void OnSyncOptSa();
};

#ifndef _DEBUG  // ComplexNetView.cpp �еĵ��԰汾
inline CComplexNetDoc* CComplexNetView::GetDocument() const
   { return reinterpret_cast<CComplexNetDoc*>(m_pDocument); }
#endif

