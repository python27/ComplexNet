// ComplexNetView.cpp : CComplexNetView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ComplexNet.h"
#endif

#include "ComplexNetDoc.h"
#include "ComplexNetView.h"
#include "DlgExampleNets.h"
#include "DlgCommuNumSet.h"
#include "RegularDlg.h"
#include "RandomDlg.h"
#include "WSSmallDlg.h"
#include "NWSmallDlg.h"
#include "DeterminDlg.h"
#include "BAModelDlg.h"
#include "DialogDrawCurve.h"
#include "DrawCurve.h"
#include "GroupNetDlg.h"
#include "NetFileSaveAs.h"
#include "controllability.h"
#include "DlgDrivers.h"
#include "Synchronization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComplexNetView
IMPLEMENT_DYNCREATE(CComplexNetView, CScrollView)

BEGIN_MESSAGE_MAP(CComplexNetView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CComplexNetView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FEATURE_DEGREE, &CComplexNetView::OnFeatureDegree)
	ON_COMMAND(ID_FEATURE_DEGREEDIS, &CComplexNetView::OnFeatureDegreedis)
	ON_COMMAND(ID_FEATURE_DEGREECORR, &CComplexNetView::OnFeatureDegreecorr)
	ON_COMMAND(ID_FEATURE_CLUSTER, &CComplexNetView::OnFeatureCluster)
	ON_COMMAND(ID_FEATURE_AVECLUSTER, &CComplexNetView::OnFeatureAvecluster)
	ON_COMMAND(ID_FEATURE_CLUSTERDIS, &CComplexNetView::OnFeatureClusterdis)
	ON_COMMAND(ID_FEATURE_CLUSTERDEGREE, &CComplexNetView::OnFeatureClusterdegree)
	ON_COMMAND(ID_FEATURE_APL, &CComplexNetView::OnFeatureApl)
	ON_COMMAND(ID_FEATURE_PATHDIS, &CComplexNetView::OnFeaturePathdis)
	ON_COMMAND(ID_FEATURE_APPEIGENVECTOR, &CComplexNetView::OnAppEigenvector)
	ON_COMMAND(ID_FEATURE_CLOSENESS, &CComplexNetView::OnCloseness)
	ON_COMMAND(ID_FEATURE_APPFLOWBETW, &CComplexNetView::OnAppFlowBetw)
	ON_COMMAND(ID_FEATURE_NOMINATION, &CComplexNetView::OnNomination)
	ON_COMMAND(ID_GROUP_KL, &CComplexNetView::OnKernighanLin)
	ON_COMMAND(ID_EXAMPLE_NINENODES, &CComplexNetView::On9nodes)
	ON_COMMAND(ID_EXAMPLE_THIRTEENNODES1, &CComplexNetView::On13nodes)
	ON_COMMAND(ID_EXAMPLE_THIRTEENNODES2, &CComplexNetView::On13nodestwo)
	ON_COMMAND(ID_EXAMPLE_TENNODES, &CComplexNetView::On10nodes)
	ON_COMMAND(ID_EXAMPLE_SEXNETWORK, &CComplexNetView::OnSexnetwork)
	ON_COMMAND(ID_EXAMPLE_KARATENETWORK, &CComplexNetView::OnKarate)
	ON_COMMAND(ID_NET_REGULAR, &CComplexNetView::OnNewRegular)
	ON_COMMAND(ID_NET_RANDOM, &CComplexNetView::OnNetRandom)
	ON_COMMAND(ID_NET_WSSMALL, &CComplexNetView::OnNetWssmall)
	ON_COMMAND(ID_NET_NWSMALL, &CComplexNetView::OnNetNWSmall)
	ON_COMMAND(ID_NET_BA, &CComplexNetView::OnNetBA)
	ON_COMMAND(ID_DETERMIN_EI, &CComplexNetView::OnDeterminswei)
	ON_COMMAND(ID_DETERMIN_URT, &CComplexNetView::OnDeterminUrt)
	ON_COMMAND(ID_DETERMIN_SWURT, &CComplexNetView::OnDeterminSwurt)
	ON_COMMAND(ID_DETERMIN_PINWHEEL, &CComplexNetView::OnDeterminPinwheel)
	ON_COMMAND(ID_DETERMIN_SWIRL, &CComplexNetView::OnDeterminSwirl)
	ON_COMMAND(ID_DETERMIN_TSSFSW, &CComplexNetView::OnDeterminTssfsw)
	ON_COMMAND(ID_DETERMIN_TS, &CComplexNetView::OnDeterminTs)
	ON_COMMAND(ID_DETERMIN_MEI, &CComplexNetView::OnDeterminMei)
	ON_COMMAND(ID_GROUP_BOXCOUNTING, &CComplexNetView::OnBoxCounting)
	ON_COMMAND(ID_GROUPNET_SIMPLE, &CComplexNetView::OnGroupnetSimple)
	ON_COMMAND(ID_SYNC_LAMDA2, &CComplexNetView::OnSyncLamda2)
	ON_COMMAND(ID_FILE_SAVE, &CComplexNetView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CComplexNetView::OnFileSaveAs)
	ON_COMMAND(ID_FEATURE_AVEDEGREE, &CComplexNetView::OnFeatureAvedegree)
	ON_COMMAND(ID_NET_URT, &CComplexNetView::OnNetUrt)
	ON_COMMAND(ID_NET_MYNET1, &CComplexNetView::OnNetMynet1)
	ON_COMMAND(ID_32785, &CComplexNetView::OnDriverNodesStructuralControllability)
	ON_COMMAND(ID_32786, &CComplexNetView::OnDriverNodesExactControllability)
	ON_COMMAND(ID_DRIVER_FAST_ALGO, &CComplexNetView::OnDriverFastAlgo)
	ON_COMMAND(ID_DRIVERS_RANK_FAST, &CComplexNetView::OnDriversRankFast)
	ON_COMMAND(ID_SYNC_LAMDARATIO, &CComplexNetView::OnSyncLamdaratio)
	ON_COMMAND(ID_SYNC_OPT_SA, &CComplexNetView::OnSyncOptSa)
END_MESSAGE_MAP()

// CComplexNetView ����/����
CComplexNetView::CComplexNetView()
{
	// TODO: �ڴ˴���ӹ������

}

CComplexNetView::~CComplexNetView()
{
}

BOOL CComplexNetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CComplexNetView ����
void CComplexNetView::OnDraw(CDC* pDC)
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//+++++++++++++++���ǵĴ���++++++++++++��ʼ
	if (!pDoc)
		return;
	CBrush cb,cb1,*cbold;//The Current brush and the old brush
	CPen cp,*cpold,cp1;
	long int a,b;
	a =GetSystemMetrics(SM_CXFULLSCREEN);
    b = GetSystemMetrics(SM_CYFULLSCREEN);
	 
	  
	////If the image size is not right, set the screen dark
	if(pDoc->NetTxtFileOpened==FALSE)
	{
	  cb.CreateSolidBrush(RGB(128,128,128));
	  cbold=pDC->SelectObject(&cb);
	  pDC->Rectangle(0,0,a,b);
	  pDC->SelectObject(cbold);
	  return;
	}
	
	////Else clear the user screen in white
	cb.CreateSolidBrush(RGB(255,255,255));
	cbold=pDC->SelectObject(&cb);
	pDC->Rectangle(0,0,a,b);
	pDC->SelectObject(cbold);//Restore the old Brush
	//Delete the brush object cb
	::DeleteObject(&cb);

	pDC->SetTextColor(RGB(255,0,0));
    CString	tempstr=pDoc->GetTitle();
	char temp[256];
	if(pDoc->net.Directed==true)
	  tempstr+=" (Directed&";
	else
	  tempstr+=" (Undirected&";
	if(pDoc->net.Weighted==true)
	  tempstr+="Weighted)";
	else
	  tempstr+="Unweighted)";
	sprintf_s(temp,"%s; Nodes: %d; Links: %d",tempstr,pDoc->unet->GetTopology()->GetNumberOfNodes(),pDoc->unet->GetTopology()->GetNumberOfEdges());
	pDC->TextOut(10,20,temp);
	pDC->SetTextColor(RGB(0,0,255));
	//display the nodes
    cp.CreatePen(PS_SOLID,1,RGB(0,0,255));
	cpold=pDC->SelectObject(&cp);
	cb1.CreateSolidBrush(RGB(0,0,255));
	cbold=pDC->SelectObject(&cb1);
	if(pDoc->unet->GetTopology()->GetNumberOfNodes()<4000)
	{
	  auto graph=pDoc->unet->GetTopology();
	  for(auto node=graph->begin();node!=graph->end();node++)
	  {
        auto posi=pDoc->unet->GetNodePosition(*node);
		if(posi[0]<=1&&posi[0]>=0&&posi[1]<=1&&posi[1]>=0)
		{
		   pDC->Ellipse((long int)(posi[0]*800.0)+20,(long int)(posi[1]*600.0)+40,(long int)(posi[0]*800.0)+30,(long int)(posi[1]*600.0)+50);
		   sprintf_s(temp,"%d",*node);
		   pDC->TextOut((long int)(posi[0]*800.0)+25,(long int)(posi[1]*600.0)+50,temp);
		}
	  } 
	}
    
	pDC->SelectObject(cbold);//Restore the old Brush
	//Delete the brush object cb
	::DeleteObject(&cb1);
	pDC->SelectObject(cpold);//Restore the old Brush
	//Delete the brush object cb
	::DeleteObject(&cp);

	cp1.CreatePen(PS_SOLID,1,RGB(255,0,0));
	cpold=pDC->SelectObject(&cp1);
	long int a1,a2,b1,b2;
	if(pDoc->unet->GetTopology()->GetNumberOfNodes()<4000&&pDoc->unet->GetTopology()->GetNumberOfEdges()<10000)
	{
       auto graph=pDoc->unet->GetTopology();
	   for(auto node=graph->begin();node!=graph->end();node++)
	   {
		  auto posi=pDoc->unet->GetNodePosition(*node);
		  for(auto othernd=node->begin();othernd!=node->end();othernd++)
		  {
	          auto posi2=pDoc->unet->GetNodePosition(*othernd);
			  a1=(long int)(posi[0]*800.0)+25;
	          a2=(long int)(posi2[0]*800.0)+25;
	          b1=(long int)(posi[1]*600.0)+45;
	          b2=(long int)(posi2[1]*600.0)+45;
	          pDC->MoveTo(a1,b1);
		      pDC->LineTo(a2,b2);
		  }
	  }
	}	
	pDC->SelectObject(cpold);//Restore the old Brush
	//Delete the brush object cb
	::DeleteObject(&cp);
   //+++++++++++++++���ǵĴ���++++++++++++����


	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CComplexNetView::OnInitialUpdate()
{
	//+++++++++++++++���ǵĴ���++++++++++++��ʼ
	//��ʼ������СΪ������Ļ
	CSize sizeTotal;
	sizeTotal.cx =GetSystemMetrics(SM_CXFULLSCREEN);
	sizeTotal.cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetScrollSizes(MM_TEXT,sizeTotal);
	//+++++++++++++++���ǵĴ���++++++++++++����
	CScrollView::OnInitialUpdate();
}


// CComplexNetView ��ӡ


void CComplexNetView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CComplexNetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CComplexNetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CComplexNetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CComplexNetView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CComplexNetView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CComplexNetView ���

#ifdef _DEBUG
void CComplexNetView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CComplexNetView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CComplexNetDoc* CComplexNetView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComplexNetDoc)));
	return (CComplexNetDoc*)m_pDocument;
}
#endif //_DEBUG


// CComplexNetView ��Ϣ�������


//NetworkFun.dll�ȼ��㲻��Ҫר�ź�����ֻ��unet������ຯ��
//ƽ���Ⱥ���ComputeAverageDegree����NetworkFun.dll
void CComplexNetView::OnFeatureDegree()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	
    char temp[256];//For string generation
    CString bookstr,txtname;//For string written
	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\degrees.txt";
    //Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
	
    //Save file
    sprintf_s(temp,"%s     %s\r\n","Node","Degree");
    
    bookstr=temp;
    fh.Write(bookstr,bookstr.GetLength());
    bookstr="";
   //Only for Undirected network now
   auto graph=pDoc->unet->GetTopology();
   vector<pair<size_t,size_t>> templist;
   for(auto node=graph->begin();node!=graph->end();node++)
   {
	templist.push_back(make_pair(*node,node->GetDegree()));
   }
   sort(templist.begin(),templist.end());
   for(auto node=templist.begin();node!=templist.end();node++)
   {
     sprintf_s(temp,"%u ",node->first);
	 bookstr+=temp;
     sprintf_s(temp,"%u\r\n",node->second);
	 bookstr+=temp;
  }
  fh.Write(bookstr,bookstr.GetLength());//write string
  bookstr="";
  sprintf_s(temp,"%s     %.2f\r\n","Average Degree=",pDoc->ComputeAverageDegree(graph));
  bookstr=temp;
  fh.Write(bookstr,bookstr.GetLength());
  //close the file 
  fh.Close();
  MessageBox(_T("�ȼ������Ѵ浽�ļ�degrees.txt"),_T("�ȼ�����"),MB_OK|MB_ICONINFORMATION);
}

//������ʾƽ���ȣ�����ComputeAverageDegree����NetworkFun.dll
void CComplexNetView::OnFeatureAvedegree()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	char temp[256];
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	sprintf_s(temp,"%s     %.6f\r\n","Average Degree=",pDoc->ComputeAverageDegree(pDoc->unet->GetTopology()));
    MessageBox(temp);
}

//�������ʾ�ȷֲ�������GetDegreeDistribution����NetworkFun.dll
void CComplexNetView::OnFeatureDegreedis()
{
	// TODO: �ڴ���������������CNetAllDoc* pDoc = GetDocument();
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	vector<pair<size_t, size_t>> pairs;
	size_t total=pDoc->unet->GetTopology()->GetNumberOfNodes();
	pDoc->GetDegreeDistribution(pairs,pDoc->unet->GetTopology());
	double *ppp;
	double *kkk;
	ppp=new double [total];
	if(ppp==NULL)
	{
		MessageBox(_T("Memory Error"));
		return;
	}
	kkk=new double [total];
	if(kkk==NULL)
	{
		MessageBox(_T("Memory Error"));
		delete []ppp;
		return;
	}
		
	//Gnuplot plot;
    //plot.set_title("degree distribution");
    //plot.plot_equation("sin(x)");
	//plot.savetopng("sin.png");
	//plot.plot_histograms(pairs);
    //plot.showonscreen();
	
    char temp[256];//For string generation
    CString bookstr,txtname;//For string written
	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\p(k).txt";
    //Open the file in WriteOnly Mode
    CFile fh(txtname.GetBuffer(txtname.GetLength()),CFile::modeCreate|CFile::modeWrite);
    //Save file
    sprintf_s(temp,"%s %s\r\n","K","P(K)");
    bookstr=temp;
    fh.Write(bookstr,bookstr.GetLength());
    bookstr="";
    size_t length=0;
    for(auto x=pairs.begin();x!=pairs.end();x++)
    {
	  kkk[length]=x->first;
	  sprintf_s(temp,"%f     ",kkk[length]);
	  bookstr+=temp;
	  ppp[length]=(double)(x->second)/total;
	  sprintf_s(temp,"%.4f\r\n",ppp[length]);
	  bookstr+=temp;	 
	  length++;
   }
   fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("�ȷֲ��������Ѵ浽�ļ�p(k).txt"),_T("�ȷֲ�������"),MB_OK|MB_ICONINFORMATION);
   
   CDialogDrawCurve a;
   CDrawCurve c;
   a.m_lNumberofSamples=length;
   a.m_bSampleDimensions=2;
   a.m_dDataX=kkk;
   c.m_DataX=a.m_dDataX;
   a.m_dDataY=ppp;
   c.m_DataY=a.m_dDataY;
   c.m_Dimension=2;
   c.m_Length=length;
   if(c.SetDefaultCDF())
   {
	  c.GetCDFData(&a.cdf);
	  strcpy_s(a.cdf.m_sTitles[0],"Degree Distribution Histogram");
	  strcpy_s(a.cdf.m_sTitles[1],"Fig.1 Degree Distribution Histogram");
	  strcpy_s(a.cdf.m_sTitles[2],"Degree");
	  strcpy_s(a.cdf.m_sTitles[3],"Percent");
	  a.DoModal();
   }
   delete []ppp;
   delete []kkk;
   Invalidate(FALSE);
}

//���������ԣ�����GetPSDegreeCorrelation����NetworkFun.dll
//�������ϵ��������GetPearsonCorrCoeff����NetworkFun.dll
void CComplexNetView::OnFeatureDegreecorr()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	char temp[256];//For string generation
    sprintf_s(temp,"%s     %.6f\r\n","Pearson Correlation Coefficient=",pDoc->GetPearsonCorrCoeff(pDoc->unet->GetTopology()));
	MessageBox(temp);
	vector<pair<size_t,double>> corre;
	pDoc->GetPSDegreeCorrelation(corre,pDoc->unet->GetTopology());
	double *knn;
	double *kkk;
	knn=new double [corre.size()];
	if(knn==NULL)
	{
		MessageBox(_T("Memory Error"));
		return;
	}
	kkk=new double [corre.size()];
	if(kkk==NULL)
	{
		MessageBox(_T("Memory Error"));
		delete []knn;
		return;
	}
	
    
    CString bookstr,txtname;//For string written
    txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\knn(k).txt";
    //Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","K","Knn");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";
   size_t ind=0;
   for(auto k=corre.begin();k!=corre.end();k++)
   {
	 kkk[ind]=k->first;
	 sprintf_s(temp,"%.2f     ",kkk[ind]);
	 bookstr+=temp;
	 knn[ind]=k->second;
     sprintf_s(temp,"%.2f\r\n",knn[ind]);
	 bookstr+=temp;
	 ind++;
   }
   fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("��-����ؼ������Ѵ浽�ļ�knn(k).txt"),_T("����ؼ�����"),MB_OK|MB_ICONINFORMATION);

   CDialogDrawCurve a;
   CDrawCurve c;
   a.m_lNumberofSamples=corre.size();
   a.m_bSampleDimensions=2;
   a.m_dDataX=kkk;
   c.m_DataX=a.m_dDataX;
   a.m_dDataY=knn;
   c.m_DataY=a.m_dDataY;
   c.m_Dimension=1;
   c.m_Length=corre.size();
   if(c.SetDefaultCDF())
   {
	  c.GetCDFData(&a.cdf);
	  strcpy_s(a.cdf.m_sTitles[0],"Degree-degree Correlation");
	  strcpy_s(a.cdf.m_sTitles[1],"Fig.1 Degree-degree Correlation");
	  strcpy_s(a.cdf.m_sTitles[2],"k");
	  strcpy_s(a.cdf.m_sTitles[3],"knn");
	  a.DoModal();
   }
   Invalidate(FALSE);
   delete []knn;
   delete []kkk;
}

//������ڵ㼯��ϵ��,����GetClusteringCoeff����NetworkFun.dll
void CComplexNetView::OnFeatureCluster()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	char temp[256];//For string generation
    CString bookstr,txtname;//For string written
    txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\clustercoeff.txt";
    //Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);

    sprintf_s(temp,"%s     %s\r\n","Node","ClusterCoeff");
    bookstr=temp;
    fh.Write(bookstr,bookstr.GetLength());
    bookstr="";
	UGraph::pGraph gra=pDoc->unet->GetTopology();
	
	vector<pair<size_t,double>> templist;
	for(auto ii=gra->begin();ii!=gra->end();ii++)
    {
		templist.push_back(make_pair(*ii,pDoc->GetClusteringCoeff(pDoc->unet->GetTopology(),*ii)));
    }
	sort(templist.begin(),templist.end());
    double total=0.0,single;
	size_t number=0;
	for(auto ii=templist.begin();ii!=templist.end();ii++)
    {
	 sprintf_s(temp,"%u     ",ii->first);
	 bookstr+=temp;
	 sprintf_s(temp,"%.6f\r\n",ii->second);
	 bookstr+=temp;
	 total=total+ii->second;
	 number++;
    }
    fh.Write(bookstr,bookstr.GetLength());//write string
    bookstr="";
    sprintf_s(temp,"%s     %.6f\r\n","Average",pDoc->GetClusteringCoeff(pDoc->unet->GetTopology(),NaF));
	bookstr=temp;
    fh.Write(bookstr,bookstr.GetLength());
    //close the file 
    fh.Close();
    MessageBox(_T("����ϵ���������Ѵ浽�ļ�clustercoeff.txt"),_T("�ȼ�����"),MB_OK|MB_ICONINFORMATION);
}

//����ƽ������ϵ��,����GetClusteringCoeff����NetworkFun.dll���ڶ�����������NaF
void CComplexNetView::OnFeatureAvecluster()
{
	// TODO: �ڴ���������������
	char temp[256];//For string generation
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    sprintf_s(temp,"%s     %.6f\r\n","Network Clustering Coefficient=",pDoc->GetClusteringCoeff(pDoc->unet->GetTopology(),NaF));
    MessageBox(temp);
}

//���㼯��ϵ���ֲ�,����GetClusteringCoeffDis����NetworkFun.dll
void CComplexNetView::OnFeatureClusterdis()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	vector<pair<double, double>> distribution;
	pDoc->GetClusteringCoeffDist(distribution,pDoc->unet->GetTopology(),0);
	double *ppp;
	double *ccc;
	ppp=new double [distribution.size()];
	if(ppp==NULL)
	{
		MessageBox(_T("Memory Error"));
		return;
	}
	ccc=new double [distribution.size()];
	if(ccc==NULL)
	{
		MessageBox(_T("Memory Error"));
		delete []ppp;
		return;
	}
    
    char temp[256];//For string generation
    CString bookstr,txtname;//For string written
    
    txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\p(c).txt";
    //Open the file in WriteOnly Mode
     CFile fh(txtname.GetBuffer(txtname.GetLength()),CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","C","P(C)");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";
   size_t ind=0;
   for(auto k=distribution.begin();k!=distribution.end();k++)
   {
	 ccc[ind]=k->first;
	 sprintf_s(temp,"%.2f     ",ccc[ind]);
	 bookstr+=temp;
	 ppp[ind]=k->second;
     sprintf_s(temp,"%.2f\r\n",ppp[ind]);
	 bookstr+=temp;
	 ind++;
   }
   fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("����ϵ���ֲ��������Ѵ浽�ļ�p(c).txt"),_T("����ϵ���ֲ�������"),MB_OK|MB_ICONINFORMATION);
   
   CDialogDrawCurve a;
	CDrawCurve c;
	a.m_lNumberofSamples=distribution.size();
	a.m_bSampleDimensions=2;
	a.m_dDataX=ccc;
	c.m_DataX=a.m_dDataX;
	a.m_dDataY=ppp;
	c.m_DataY=a.m_dDataY;
	c.m_Dimension=1;
	c.m_Length=distribution.size();
	if(c.SetDefaultCDF())
	{
	  c.GetCDFData(&a.cdf);
	  strcpy_s(a.cdf.m_sTitles[0],"Clustering Coeff Distribution");
	  strcpy_s(a.cdf.m_sTitles[1],"Fig.1 Clustering Coeff Distribution");
	  strcpy_s(a.cdf.m_sTitles[2],"Clustering Coefficients");
	  strcpy_s(a.cdf.m_sTitles[3],"Percent");
	  a.DoModal();
	}
	delete []ppp;
    delete []ccc;
    Invalidate(FALSE);
}

//����۶������,����GetClusteringCoeffDis����NetworkFun.dll
void CComplexNetView::OnFeatureClusterdegree()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	pair<double, vector<pair<size_t, double>>> correlation;
	pDoc->GetClusteringDegreeCorre(correlation,pDoc->unet->GetTopology());
	double *cnn;
	double *kkk;
	cnn=new double [correlation.second.size()];
	if(cnn==NULL)
	{
		MessageBox(_T("Memory Error"));
		return;
	}
	kkk=new double [correlation.second.size()];
	if(kkk==NULL)
	{
		MessageBox(_T("Memory Error"));
		delete []cnn;
		return;
	}
    char temp[256];//For string generation
    CString bookstr,txtname;//For string written
    
    txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\cnn(k).txt";
    //Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","K","Cnn");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";
   size_t ind=0;
   for(auto k=correlation.second.begin();k!=correlation.second.end();k++)
   {
	 kkk[ind]=k->first;
	 sprintf_s(temp,"%.2f     ",kkk[ind]);
	 bookstr+=temp;
	 cnn[ind]=k->second;
     sprintf_s(temp,"%.2f\r\n",cnn[ind]);
	 bookstr+=temp;
	 ind++;
   }
   fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("��-����ؼ������Ѵ浽�ļ�cnn(k).txt"),_T("��-����ؼ�����"),MB_OK|MB_ICONINFORMATION);
   CDialogDrawCurve a;
   CDrawCurve c;
   a.m_lNumberofSamples=correlation.second.size();
   a.m_bSampleDimensions=2;
   a.m_dDataX=kkk;
   c.m_DataX=a.m_dDataX;
   a.m_dDataY=cnn;
   c.m_DataY=a.m_dDataY;
   c.m_Dimension=1;
   c.m_Length=correlation.second.size();
   if(c.SetDefaultCDF())
   {
	  c.GetCDFData(&a.cdf);
	  strcpy_s(a.cdf.m_sTitles[0],"Cluster-degree Correlation");
	  strcpy_s(a.cdf.m_sTitles[1],"Fig.1 Cluster-degree Correlation");
	  strcpy_s(a.cdf.m_sTitles[2],"k");
	  strcpy_s(a.cdf.m_sTitles[3],"cnn");
	  a.DoModal();
   }
   delete []cnn;
   delete []kkk;
   
   Invalidate(FALSE);
}

//����ƽ�������ֱ��������GetDiameterAndAverageDistance����NetworkFun.dll
void CComplexNetView::OnFeatureApl()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	char temp[256];
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	double apl;
	size_t diam;
	pDoc->GetDiameterAndAverageDistance(diam,apl,pDoc->unet->GetTopology());
    sprintf_s(temp,"The average distance: %f; The Diameter: %d",apl,diam);
    MessageBox(temp);

}

//�������ֲ�,����GetShortestDistanceDistribution����NetworkFun.dll
void CComplexNetView::OnFeaturePathdis()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	char temp[256];
	double *L;
	double *PL;
	size_t diameter=pDoc->GetDiameter(pDoc->unet->GetTopology());
	L=new double [diameter];
	PL=new double [diameter];
	CString bookstr,txtname;//For string written
    vector<pair<size_t,size_t>> distribution;
	size_t total=pDoc->unet->GetTopology()->GetNumberOfNodes();
	total=total*(total-1);
	pDoc->GetShortestDistanceDistribution(distribution,pDoc->unet->GetTopology());
	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\p(L).txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
	//Save file
    sprintf_s(temp,"%s %s\r\n","L","P(L)");
    bookstr=temp;
    fh.Write(bookstr,bookstr.GetLength());
    bookstr="";
    diameter=0;
	for(auto ii=distribution.begin();ii!=distribution.end();ii++)
	{	
		L[diameter]=ii->first;
		PL[diameter]=ii->second/(double)total;
		sprintf_s(temp,"%f %.6f  \r\n",L[diameter],PL[diameter]);
		bookstr+=temp;
		diameter++;
	}
	
   fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("����ֲ��������Ѵ浽�ļ�p(L).txt"),_T("����ֲ�������"),MB_OK|MB_ICONINFORMATION);
   
   CDialogDrawCurve a;
   CDrawCurve c;
   a.m_lNumberofSamples=diameter;
   a.m_bSampleDimensions=2;
   a.m_dDataX=L;
   c.m_DataX=a.m_dDataX;
   a.m_dDataY=PL;
   c.m_DataY=a.m_dDataY;
   c.m_Dimension=2;
   c.m_Length=diameter;
   if(c.SetDefaultCDF())
   {
	  c.GetCDFData(&a.cdf);
	  strcpy_s(a.cdf.m_sTitles[0],"Distance Distribution Histogram");
	  strcpy_s(a.cdf.m_sTitles[1],"Fig.1 Distance Distribution Histogram");
	  strcpy_s(a.cdf.m_sTitles[2],"Distance");
	  strcpy_s(a.cdf.m_sTitles[3],"Percent");
	  a.DoModal();
   }
   delete []L;
   delete []PL;
}

//Ŀǰ�ù��ܲ���ʹ���ȴ�����
void CComplexNetView::OnAppEigenvector()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	MessageBox("Ŀǰ�ù��ܲ���ʹ���ȴ�����");
	/*double *feature;
	double *temptemp;
	feature=new double [pDoc->net.NodeNumber];
	temptemp=new double [pDoc->net.NodeNumber];
		
	pDoc->CalculateNodesCentralityAppEigenvector(&pDoc->net,feature,temptemp);
	
    char temp[256];//For string generation
	WORD k;
    CString bookstr,txtname;//For string written

	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\AppEigenvector.txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","Node","AppEigenvector");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";	
   for(k=0;k<pDoc->net.NodeNumber;k++)
   {
     sprintf_s(temp,"%u ",pDoc->net.Net[k].NodeNo);
	 bookstr+=temp;     
	 sprintf_s(temp,"%.6f \r\n",feature[k]);
	 bookstr+=temp;	
   }    

	fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
	fh.Close();
    MessageBox(_T("������������ָ��������Ѵ浽�ļ�AppEigenvector.txt"),_T("������������ָ�������"),MB_OK|MB_ICONINFORMATION);
	delete [] feature;
	delete [] temptemp;*/
}

//Ŀǰ�ù��ܲ���ʹ���ȴ�����
void CComplexNetView::OnCloseness()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	MessageBox("Ŀǰ�ù��ܲ���ʹ���ȴ�����");
/*	double *feature;
	feature=new double [pDoc->net.NodeNumber];
	pDoc->CalculateNodesCentralityCloseness(&pDoc->net,feature);
	
    char temp[256];//For string generation
	WORD k;
    CString bookstr,txtname;//For string written

	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\Closeness.txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","Node","Closeness");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";	
   for(k=0;k<pDoc->net.NodeNumber;k++)
   {
     sprintf_s(temp,"%u ",pDoc->net.Net[k].NodeNo);
	 bookstr+=temp;     
	 sprintf_s(temp,"%.6f \r\n",feature[k]);
	 bookstr+=temp;	
   }
    
	fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
   fh.Close();
   MessageBox(_T("���ܶ�ָ��������Ѵ浽�ļ�Closeness.txt"),_T("���ܶ�ָ�������"),MB_OK|MB_ICONINFORMATION);	
	delete [] feature;*/
	
}
//Ŀǰ�ù��ܲ���ʹ���ȴ�����
void CComplexNetView::OnAppFlowBetw()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	MessageBox("Ŀǰ�ù��ܲ���ʹ���ȴ�����");
/*	double *feature;
	double *temptemp;
	feature=new double [pDoc->net.NodeNumber];
	temptemp=new double [pDoc->net.NodeNumber];
	
	pDoc->CalculateNodesCentralityAppFlowBetweenness(&pDoc->net,feature,temptemp);
	
    char temp[256];//For string generation
	WORD k;
    CString bookstr,txtname;//For string written

	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\AppFlowBetweenness.txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","Node","AppFlowBetweenness");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";	
   for(k=0;k<pDoc->net.NodeNumber;k++)
   {
     sprintf_s(temp,"%u ",pDoc->net.Net[k].NodeNo);
	 bookstr+=temp;     
	 sprintf_s(temp,"%.6f \r\n",feature[k]);
	 bookstr+=temp;	
   }      
	fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
	fh.Close();
   MessageBox(_T("����������ָ��������Ѵ浽�ļ�AppFlowBetweenness.txt"),_T("����������ָ�������"),MB_OK|MB_ICONINFORMATION);
	delete [] feature;
	delete [] temptemp;*/
}
//Ŀǰ�ù��ܲ���ʹ���ȴ�����
void CComplexNetView::OnNomination()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	MessageBox("Ŀǰ�ù��ܲ���ʹ���ȴ�����");
	/*double *feature;
	double *temptemp;
	double *temp1;
	feature=new double [pDoc->net.NodeNumber];
	temptemp=new double [pDoc->net.NodeNumber];
	temp1=new double [pDoc->net.NodeNumber];
	
	pDoc->CalculateNodesCentralityNomination(&pDoc->net,feature,temptemp,temp1);
	
    char temp[256];//For string generation
	WORD k;
    CString bookstr,txtname;//For string written

	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\Nomination.txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","Node","Nomination");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   bookstr="";	
   for(k=0;k<pDoc->net.NodeNumber;k++)
   {
     sprintf_s(temp,"%u ",pDoc->net.Net[k].NodeNo);
	 bookstr+=temp;     
	 sprintf_s(temp,"%.6f \r\n",feature[k]);
	 bookstr+=temp;	
   }    

	fh.Write(bookstr,bookstr.GetLength());//write string
   //close the file 
	fh.Close();
   MessageBox(_T("�ۼ�����ָ��������Ѵ浽�ļ�Nomination.txt"),_T("�ۼ�����ָ�������"),MB_OK|MB_ICONINFORMATION);
   	delete [] feature;
	delete [] temptemp;
	delete [] temp1;*/
}

//Ŀǰ�ù��ܲ���ʹ���ȴ�����
void CComplexNetView::OnKernighanLin()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}
	MessageBox("Ŀǰ�ù��ܲ���ʹ���ȴ�����");
	/*CDlgCommuNumSet dr;
	dr.DoModal();
	int *comlist;
	comlist=new int [pDoc->net.NodeNumber];
	
	if(pDoc->CalculateNetworkCommunityKernighanLin(pDoc->net,dr.m_Commu_One_Num,dr.m_Commu_Two_Num,comlist)!=0)
	{
      MessageBox(_T("Wrong input paramete!!"));
	  return;	
	}
    char temp[256];//For string generation
	WORD k;
    CString bookstr,txtname,bookstrA,bookstrB;//For string written
	txtname=pDoc->CurrentWorkPath;
	txtname+="\\Results\\KernihanLin.txt";
	//Open the file in WriteOnly Mode
    CFile fh(txtname,CFile::modeCreate|CFile::modeWrite);
   //Save file
   sprintf_s(temp,"%s %s\r\n","Node","KernighanLin");
   bookstr=temp;
   fh.Write(bookstr,bookstr.GetLength());
   sprintf_s(temp,"%s %s \r\n","Community","No. one");
   bookstrA=temp;
   sprintf_s(temp,"%s %s \r\n","Community","No. two");
   bookstrB=temp;	
   for(k=0;k<pDoc->net.NodeNumber;k++)
   {
	   if(comlist[k])
	   {
	    sprintf_s(temp,"%u \r\n",pDoc->net.Net[k].NodeNo);
		bookstrA+=temp; 
	   }
	   else
	   {
		   sprintf_s(temp,"%u \r\n",pDoc->net.Net[k].NodeNo);
		   bookstrB+=temp;	
	   
	   }
   }    
	fh.Write(bookstrA,bookstrA.GetLength());//write string
	fh.Write(bookstrB,bookstrB.GetLength());//write string
   //close the file 
	fh.Close();
    MessageBox(_T("KernighanLin��������Ѵ浽�ļ�KernighanLin.txt"),_T("KernighanLin�������"),MB_OK|MB_ICONINFORMATION);
	delete [] comlist;*/
}


//9�ڵ������ļ����ɣ���������
void CComplexNetView::On9nodes()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("�Žڵ���������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ��Žڵ������ļ������ɴ��룬����Ϊ�����������ɵĲο���
	    long int i;
	    long int fr,to;
	    char a[256];
		char temp[256];	
		int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
    	strcpy_s(a,"*Nine Nodes Network\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",9);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
		double coordinate[]={0.194,0.417,0.194,0.667,0.325,0.597,0.490,0.597,0.647,0.597,
						0.386,0.417,0.586,0.417,0.780,0.417,0.780,0.667};
	    for(i=0;i<9;i++)
	    { 
	       sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, coordinate[2*i],  coordinate[2*i+1],0.5);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
        strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));
	    int nodetonode[]={1,2,1,3,2,3,3,4,3,6,4,5,5,7,5,8,5,9,6,7,8,9};
	    for(i=0;i<11;i++)
	    { 
	       fr=nodetonode[2*i];
	       to=nodetonode[2*i+1];
	       sprintf_s(temp,"%d %d 1\n",fr,to);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
	    _close(fh);		

		//NetworkFun.dll �洢Dot��Png�ļ�
		CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//10�ڵ������ļ�����,��������
void CComplexNetView::On10nodes()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("ʮ�ڵ���������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ�ʮ�ڵ������ļ������ɴ��룬����Ϊ�����������ɵĲο���
	    long int i;
	    long int fr,to;
	    char a[256];
		char temp[256];		
	    int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
		strcpy_s(a,"*Ten Nodes Network\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",10);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
	    double coordinate[]={0.440,0.770,0.564,0.77,0.630,0.588,0.761,0.445,0.503,0.447,
						0.37,0.588,0.227,0.588,0.227,0.382,0.37,0.382,0.503,0.207};
	    for(i=0;i<10;i++)
	    {
	      sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, coordinate[2*i],  coordinate[2*i+1],0.5);
	      strcpy_s(a,temp);
		  _write(fh,a,strlen(a));
	    }
	    strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));
	    int nodetonode[]={1,2,1,3,1,5,1,6,1,7,2,3,2,5,2,6,2,7,3,4,3,5,3,6,4,5,4,6,5,6,5,
					  9,5,10,6,7,6,8,6,9,7,8,7,9,8,9,9,10};
	    for(i=0;i<24;i++)
	    {
	      fr=nodetonode[2*i];
	      to=nodetonode[2*i+1];
	      sprintf_s(temp,"%d %d 1\n",fr,to);
	      strcpy_s(a,temp);
		  _write(fh,a,strlen(a));
	    }
	    _close(fh);
		//NetworkFun.dll �洢Dot��Png�ļ�
        CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//13�ڵ�����1�ļ�����,��������
void CComplexNetView::On13nodes()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("ʮ���ڵ����磨1������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ�ʮ���ڵ������ļ������ɴ��룬����Ϊ�����������ɵĲο���
        long int i;
	    long int fr,to;
	    char a[256];
	    char temp[256];		
	    int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
		strcpy_s(a,"*Thirteen Nodes Network One\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",13);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
		double coordinate[]={0.467,0.220,0.409,0.340,0.529,0.340,0.467,0.463,0.467,0.582,
						0.395,0.678,0.290,0.695,0.366,0.820,0.246,0.820,0.546,0.678,
						0.636,0.695,0.573,0.820,0.695,0.820};
	    for(i=0;i<13;i++)
	    {
	       sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, coordinate[2*i],  coordinate[2*i+1],0.5);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));
	    int nodetonode[]={1,2,1,3,2,3,2,4,3,4,4,5,5,6,5,10,6,7,6,8,7,8,7,9,8,9,10,11,10,
					  12,11,12,11,13,12,13};
	    for(i=0;i<18;i++)
	    {
	       fr=nodetonode[2*i];
	       to=nodetonode[2*i+1];
	       sprintf_s(temp,"%d %d 1\n",fr,to);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
		}
	    _close(fh);
		//NetworkFun.dll �洢Dot��Png�ļ�
		CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//13�ڵ�����2�ļ�����,��������
void CComplexNetView::On13nodestwo()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("ʮ���ڵ����磨2������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ�ʮ���ڵ������ļ������ɴ��룬����Ϊ�����������ɵĲο���
	    long int i;
	    long int fr,to;
	    char a[256];
	    char temp[256];		
	    int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
		strcpy_s(a,"*Thirteen Nodes Network Two\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",13);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
	    double coordinate[]={0.425,0.250,0.277,0.375,0.500,0.375,0.353,0.503,0.191,0.587,
						0.501,0.603,0.276,0.698,0.407,0.765,0.500,0.867,0.627,0.765,
						0.656,0.502,0.783,0.680,0.814,0.373};
	    for(i=0;i<13;i++)
	    {
	       sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, coordinate[2*i],  coordinate[2*i+1],0.5);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));
	    int nodetonode[]={1,2,1,3,2,3,2,4,3,4,3,6,3,11,4,5,4,6,4,8,5,7,6,8,6,10,6,11,7,8,
					  8,9,8,10,9,10,10,11,10,12,11,12,11,13};
 	    for(i=0;i<22;i++)
	    {
	       fr=nodetonode[2*i];
	       to=nodetonode[2*i+1];
	       sprintf_s(temp,"%d %d 1\n",fr,to);
           strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		_close(fh);
		//NetworkFun.dll �洢Dot��Png�ļ�
        CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//�Թ�ϵ�����ļ�����,��������
void CComplexNetView::OnSexnetwork()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("�Թ�ϵ��������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ��Թ�ϵ�����ļ������ɴ��룬����Ϊ�����������ɵĲο���
	    long int i;
	    long int fr,to;
	    char a[256];
	    char temp[256];		
	    int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
		strcpy_s(a,"*Sex Network\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",40);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
	 	double coordinate[]={0.156,0.305,0.133,0.432,0.095,0.528,0.121,0.622,0.185,0.493,
						0.233,0.395,0.184,0.747,0.234,0.655,0.287,0.745,0.379,0.750,
						0.270,0.565,0.356,0.652,0.456,0.783,0.456,0.677,0.323,0.493,
						0.430,0.568,0.384,0.457,0.585,0.783,0.627,0.692,0.533,0.712,
						0.456,0.458,0.524,0.445,0.554,0.543,0.564,0.642,0.482,0.323,
						0.660,0.475,0.627,0.555,0.686,0.590,0.741,0.690,0.687,0.778,
						0.769,0.508,0.810,0.623,0.806,0.728,0.893,0.655,0.866,0.510,
						0.810,0.388,0.866,0.305,0.686,0.387,0.757,0.305,0.591,0.327};
	    for(i=0;i<40;i++)
	    {
	      sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, coordinate[2*i],  coordinate[2*i+1],0.5);
	      strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));	
	    int nodetonode[]={1,2,2,5,3,5,4,5,5,6,5,11,7,8,8,9,8,11,9,10,11,16,12,16,13,14,14,
					  16,15,16,16,17,16,20,16,21,16,22,18,20,19,20,19,28,22,23,22,25,
					  22,26,23,24,26,27,26,28,26,31,26,38,28,29,29,30,31,32,31,36,32,
					  33,32,34,33,34,34,35,36,37,38,39,38,40};
	    for(i=0;i<41;i++)
	    {
	       fr=nodetonode[2*i];
	       to=nodetonode[2*i+1];
	       sprintf_s(temp,"%d %d 1\n",fr,to);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		_close(fh);
		//NetworkFun.dll �洢Dot��Png�ļ�
		CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//���ֵ������ļ�����,��������
void CComplexNetView::OnKarate()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDlgExampleNets egnet;
	egnet.path=pDoc->CurrentWorkPath;
	egnet.title=_T("���ֵ����ֲ���������");
	if(egnet.DoModal()==IDOK)
	{
		//����������������ļ������ӣ����ֵ������ļ������ɴ��룬����Ϊ�����������ɵĲο���
	    long int i;
	    long int fr,to;
	    char a[256];
		char temp[256];		
	    int fh;
	    _sopen_s(&fh,egnet.path,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	    if(fh==-1)
		{
		   MessageBox("Cannot create the net file");
		   return;
		}
		strcpy_s(a,"Katate Network\n");
	    _write(fh,a,strlen(a));
	    sprintf_s(temp," %d\n",34);
	    strcpy_s(a,"*Vertices");
	    strcat_s(a,temp);
	    _write(fh,a,strlen(a));
	    double karcoordinate[]={0.581,0.562,0.506,0.543,0.403,0.552,0.561,0.445,0.675,0.452,
						   0.729,0.473,0.735,0.570,0.501,0.698,0.401,0.475,0.369,0.293,
						   0.687,0.630,0.639,0.812,0.647,0.340,0.456,0.420,0.234,0.282,
						   0.173,0.357,0.860,0.530,0.563,0.795,0.149,0.560,0.483,0.363,
						   0.133,0.485,0.637,0.727,0.289,0.257,0.250,0.615,0.336,0.838,
						   0.291,0.790,0.137,0.283,0.295,0.653,0.323,0.588,0.165,0.452,
						   0.367,0.372,0.366,0.633,0.270,0.485,0.287,0.435};
	    for(i=0;i<34;i++)
	    {
	       sprintf_s(temp,"%d %d %f %f %f\n", i+1,i+1, karcoordinate[2*i],  karcoordinate[2*i+1],0.5);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
		strcpy_s(a,"*Edges\n");
	    _write(fh,a,strlen(a));
	    int nodetonode[]={2,1,3,1,3,2,4,1,4,2,4,3,5,1,6,1,7,1,7,5,7,6,8,1,8,2,8,3,8,4,9,1,
					  9,3,10,3,11,1,11,5,11,6,12,1,13,1,13,4,14,1,14,2,14,3,14,4,17,6,
					  17,7,18,1,18,2,20,1,20,2,22,1,22,2,26,24,26,25,28,3,28,24,28,25,
					  29,3,30,24,30,27,31,2,31,9,32,1,32,25,32,26,32,29,33,3,33,9,33,
					  15,33,16,33,19,33,21,33,23,33,24,33,30,33,31,33,32,34,9,34,10,
					  34,14,34,15,34,16,34,19,34,20,34,21,34,23,34,24,34,27,34,28,34,
					  29,34,30,34,31,34,32,34,33};
	    for(i=0;i<78;i++)
	    { 
	       fr=nodetonode[2*i];
	       to=nodetonode[2*i+1];
	       sprintf_s(temp,"%d %d 1\n",fr,to);
	       strcpy_s(a,temp);
		   _write(fh,a,strlen(a));
	    }
	    _close(fh);
		//NetworkFun.dll �洢Dot��Png�ļ�
		CString tempstr;
		UNetwork<>::pNetwork tempnet;
		tempstr=egnet.path.Left(egnet.path.GetLength()-4);
		pDoc->ReadUNetworkFromNetFile(tempnet,(char *)egnet.path.GetString());
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//�����������ɣ�����GenKNearestNetwork,writeToNetFile����NetworkFun.dll
void CComplexNetView::OnNewRegular()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRegularDlg crd;
	crd.path=pDoc->CurrentWorkPath;
	if(crd.DoModal()==IDOK)
	{
	   //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
	   UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenKNearestNetwork(crd.m_reg_nodes,crd.m_reg_neighbors)));
	   pDoc->WriteToNetFile((char *)crd.path.GetString(),tempnet);
	   CString tempstr;
	   tempstr=crd.path.Left(crd.path.GetLength()-4);
	   pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}


}


//����������ɣ�����RandomNetworkGenerate����NetworkFun.dll
void CComplexNetView::OnNetRandom()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRandomDlg crd;
	crd.path=pDoc->CurrentWorkPath;
	if(crd.DoModal()==IDOK)
	{
	   //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
	   double prob;
	   prob=2.0*(double)crd.m_ran_edges/(crd.m_ran_nodes*(crd.m_ran_nodes-1.0));
	   UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenRandomNetwork(crd.m_ran_nodes,prob)));
	   pDoc->WriteToNetFile((char *)crd.path.GetString(),tempnet);
	   CString tempstr;
	   tempstr=crd.path.Left(crd.path.GetLength()-4);
	   pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//������ȵ������������ɣ�����GenUniformRecursiveTree����NetworkFun.dll
void CComplexNetView::OnNetUrt()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("������ȵ�������������");
	cdd.flag=1;
	if(cdd.DoModal()==IDOK)
	{
	    //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenUniformRecursiveTree(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//WSС�����������ɣ�����GenSmallWorldNetworkByWS����NetworkFun.dll
void CComplexNetView::OnNetWssmall()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CWSSmallDlg cwd;
	cwd.path=pDoc->CurrentWorkPath;
	if(cwd.DoModal()==IDOK)
	{
	  //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
   	  UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenSmallWorldNetworkByWS(cwd.m_wssmall_nodes,cwd.m_wssmall_neighbors,cwd.m_wssmall_prob)));
	  pDoc->WriteToNetFile((char *)cwd.path.GetString(),tempnet);
	  CString tempstr;
	  tempstr=cwd.path.Left(cwd.path.GetLength()-4);
	  pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}


//NWС�����������ɣ�����GenSmallWorldNetworkByNW����NetworkFun.dll
void CComplexNetView::OnNetNWSmall()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CNWSmallDlg cnd;
	cnd.path=pDoc->CurrentWorkPath;
	if(cnd.DoModal()==IDOK)
	{
	  //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
   	  UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenSmallWorldNetworkByNW(cnd.m_nwsmall_nodes,cnd.m_nwsmall_neighbors,cnd.m_nwsmall_prob)));
	  pDoc->WriteToNetFile((char *)cnd.path.GetString(),tempnet);
	  CString tempstr;
	  tempstr=cnd.path.Left(cnd.path.GetLength()-4);
	  pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}


//BA�ޱ���������ɣ�����GenScaleFreeNetwork����NetworkFun.dll
void CComplexNetView::OnNetBA()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBAModelDlg cbd;
	cbd.path=pDoc->CurrentWorkPath;
	if(cbd.DoModal()==IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenScaleFreeNetwork(cbd.m_ba_nodes,cbd.m_ba_onodes)));
	    pDoc->WriteToNetFile((char *)cbd.path.GetString(),tempnet);
		CString tempstr;
	    tempstr=cbd.path.Left(cbd.path.GetLength()-4);
	    pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//�ߵ���ȷ����С�����������ɣ�����GenSmallWorldByEdgeIteratione����NetworkFun.dll
void CComplexNetView::OnDeterminswei()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("���ڱߵ�����ȷ����С������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
	    //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenSmallWorldByEdgeIteration(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}

//ȷ���Ե������������ɣ�����GenDURT����NetworkFun.dll
void CComplexNetView::OnDeterminUrt()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("ȷ���Ծ��ȵ�������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
	    //NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenDURT(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}


//ȷ����С����������������ɣ�����GenSmallWorldNetworkFromDURT����NetworkFun.dll
//½�����͹�������㷨
//Zhe-Ming Lu, and Shi-Ze Guo(2012). A small-world network derived from the deterministic uniform recursive tree. Physica A. 391(1-2), 87-92.
void CComplexNetView::OnDeterminSwurt()
{
	// TODO: Add your command handler code here
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("ȷ���Ծ��ȵ�����С������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
		////NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenSmallWorldNetworkFromDURT(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}

//ȷ���Է糵С�����������ɣ�����GenPinWheelShapedSW����NetworkFun.dll 
//��������衢½���������������㷨
//Shi-Ze Guo, Chong Li, Zhe-Ming Lu and Yu-Long Qiao (2012). A Pinwheel-Shaped Determinstic Small-World Network. ICIC Express Letters. 6(7):1809-1814.
void CComplexNetView::OnDeterminPinwheel()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("�糵ȷ����С������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenPinWheelShapedSW(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}

//ȷ���������������ɣ�����GenSwirlShapedNetwork����NetworkFun.dll 
//��衢������½�������������㷨
// Chong Li, Shi-Ze Guo, Zhe-Ming Lu and Yu-Long Qiao(2011): A Swirl-shaped Deterministic Network with High Clustering Coefficient. Information Technology Journal. 10(10):1994-1998.
void CComplexNetView::OnDeterminSwirl()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("����ȷ������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenSwirlShapedNetwork(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}


//��״�ޱ��С����ȷ�����������ɣ�����GenTreeStructuredSFSW����NetworkFun.dll
//Zhe-Ming Lu, Yu-Xin Su, and Shi-Ze Guo(2013). Deterministic scale-free small-world network of arbitrary order. Physica A.
void CComplexNetView::OnDeterminTssfsw()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("��״�ޱ��С����ȷ������������");
	cdd.flag=1;
	if(cdd.DoModal()==IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenTreeStructuredSFSW(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}


//��״С����ȷ�����������ɣ�����GenTreeStructuredSW����NetworkFun.dll
//������½�������㷨
//Shi-Ze Guo, Zhe-Ming Lu, Guang-Yu Kang, Zhe Chen and Hao Luo (2012): A tree-structured deterministic small-world network. IEICE Transactions on Information and Systems. E95D(5): pp. 1536-1538.
void CComplexNetView::OnDeterminTs()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("��״С����ȷ������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenTreeStructuredSW(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}

//�Ľ��ıߵ���С����ȷ�����������ɣ�����GenTriangleExtendedDSWN����NetworkFun.dll 
//½���������·���㷨�����Ĵ�Ͷ
void CComplexNetView::OnDeterminMei()
{
	// TODO: �ڴ���������������
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path=pDoc->CurrentWorkPath;
	cdd.title=_T("�Ľ��ıߵ���С����ȷ������������");
	cdd.flag=0;
	if(cdd.DoModal()==IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenTriangleExtendedDSWN(cdd.m_determin_iterations)));
	    pDoc->WriteToNetFile((char *)cdd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cdd.path.Left(cdd.path.GetLength()-4);
		//pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}

//�м��������࣬����RenormalizeByBoxCounting����NetworkFun.dll 
void CComplexNetView::OnBoxCounting()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->NetTxtFileOpened==FALSE)
	{
		MessageBox("Please open a network file first","Warning!", MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	pDoc->unet.reset(new UNetwork<>(pDoc->RenormalizeByBoxCounting(pDoc->unet->GetTopology(),3)));
	Invalidate(FALSE);
}

//�����������磬����GenCommunityNetwork����NetworkFun.dll
void CComplexNetView::OnGroupnetSimple()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CGroupNetDlg cgnd;
	cgnd.path=pDoc->CurrentWorkPath;
	if(cgnd.DoModal()==IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		UNetwork<>::pNetwork tempnet(new UNetwork<>(pDoc->GenCommunityNetwork(cgnd.m_groupnet_nodes,cgnd.m_groupnet_groups,cgnd.m_groupnet_proba,cgnd.m_groupnet_probb)));
	    pDoc->WriteToNetFile((char *)cgnd.path.GetString(),tempnet);
		CString tempstr;
		tempstr=cgnd.path.Left(cgnd.path.GetLength()-4);
		pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}	
}

void CComplexNetView::OnSyncLamda2()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	double ans = GetLambda2(pgraph);

	char buf[1024] = { '\0' };
	sprintf_s(buf, 1024, "������ĵڶ���������Ϊ��%.8f", ans);
	CString info(buf);
	MessageBox(info, "�ڶ���������������", MB_ICONASTERISK);
}

void CComplexNetView::OnSyncLamdaratio()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	double ans = GetLambdaNRatioLambda2(pgraph);

	char buf[1024] = { '\0' };
	sprintf_s(buf, 1024, "������������� L_N / L_2 = %.8f", ans);
	CString info(buf);
	MessageBox(info, "�����ȼ�����", MB_ICONASTERISK);
}

void CComplexNetView::OnSyncOptSa()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();	
	SASyncOptimization sa;
	sa.Run(pgraph);
	 
	char buf[1024] = { '\0' };
	sprintf_s(buf, 1024, "�㷨��ɣ��Ż���������� SyncOptimizationBySA.txt �ļ��� !");
	CString info(buf);
	MessageBox(info, "ģ���˻��㷨�Ż�", MB_ICONASTERISK);
}

//�ļ�����Net,dot,Png���ָ�ʽ
void CComplexNetView::OnFileSave()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//NetworkFun.dll Net,dot,Png�ļ��洢
	pDoc->WriteToNetFile((char *)pDoc->NetFileName.GetString(),pDoc->unet);
	CString tempstr;
	tempstr=pDoc->NetFileName.Left(pDoc->NetFileName.GetLength()-4);
	pDoc->DrawCircleForm(pDoc->unet->GetTopology(),tempstr.GetString());
	Invalidate(FALSE);
}

//�ļ����Net,dot,Png���ָ�ʽ
void CComplexNetView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
   CComplexNetDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   CNetFileSaveAs cnfsa;
   cnfsa.path=pDoc->CurrentWorkPath;
   if(cnfsa.DoModal()==IDOK)
   {
	  //NetworkFun.dll Net,dot,Png�ļ��洢
	  pDoc->WriteToNetFile((char *)cnfsa.path.GetString(),pDoc->unet);
	  CString tempstr;
	  tempstr=cnfsa.path.Left(cnfsa.path.GetLength()-4);
	  pDoc->DrawCircleForm(pDoc->unet->GetTopology(),tempstr.GetString());
	  
	  //�ı���ʾ���ļ�����
	  pDoc->NetFileName=cnfsa.path;
	  pDoc->NetFileTitle=cnfsa.path.Right(cnfsa.path.GetLength()-pDoc->NetFileName.ReverseFind('\\')-1);
	  pDoc->SetTitle(pDoc->NetFileTitle);
	  Invalidate(FALSE);
   }
}


// ����ģ���ɶ������
void CComplexNetView::OnNetMynet1()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDeterminDlg cdd;
	cdd.path = pDoc->CurrentWorkPath;
	cdd.title = _T("������������ģ��");
	cdd.flag = 0;
	if (cdd.DoModal() == IDOK)
	{
		//NetworkFun.dll �������粢�洢Net��Dot��Png�ļ�
		int iteration_times = cdd.m_determin_iterations;

		// *************** Network Generation Algorithm begin *************//
		UGraph::pGraph graph(new UGraph());
		
		// init graph
		graph->AddNode(0);
		graph->AddNode(1);
		graph->AddEdge(0, 1);

		list<pair<size_t, size_t>> added_edges;
		added_edges.clear();
		added_edges.push_back(make_pair(0, 1));

		int cur_iteration_times = 0;
		while (cur_iteration_times < iteration_times)
		{
			list<pair<size_t, size_t>> new_added_edges;
			new_added_edges.clear();

			list<pair<size_t, size_t>>::iterator it;
			for (it = added_edges.begin(); it != added_edges.end(); ++it)
			{
				int u = it->first;
				int v = it->second;
				int n = graph->GetNumberOfNodes();
				// add middle nodes
				graph->AddNode(n);
				graph->AddNode(n + 1);
				graph->AddNode(n + 2);
				graph->RemoveEdge(u, v);
				graph->AddEdge(u, n);
				graph->AddEdge(v, n);
				// add new branch nodes and edges
				graph->AddEdge(n, n + 1);
				graph->AddEdge(n, n + 2);
				// update new added edge
				new_added_edges.push_back(make_pair(n, n + 1));
				new_added_edges.push_back(make_pair(n, n + 2));
			}

			added_edges.clear();
			added_edges = new_added_edges;
			cur_iteration_times += 1;
		}
		// ****** Network generation Algorithm end *******//

		UNetwork<>::pNetwork tempnet(new UNetwork<>(graph));
		pDoc->WriteToNetFile((char *)cdd.path.GetString(), tempnet);
		CString tempstr;
		tempstr = cdd.path.Left(cdd.path.GetLength() - 4);
		//pDoc->DrawCircleForm(tempnet->GetTopology(),tempstr.GetString());
	}
}


void CComplexNetView::OnDriverNodesStructuralControllability()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	
	MessageBox(_T("�ú���ֻ����������ṹ������!!! ������������"));

}


void CComplexNetView::OnDriverNodesExactControllability()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	set<int> driverNodesList;
	int driverNodesNum = exactControllability(*pgraph, driverNodesList);
	//int driverNodesNum = numberofDriverNodesExactControllability(*pgraph);

	CString txtname;
	txtname = pDoc->CurrentWorkPath;
	txtname += "\\Results\\driver_nodes.txt";
	std::ofstream fout(txtname);
	char temp[256] = { '\0' };
	sprintf_s(temp, 256, "%d �������ڵ����£�", driverNodesNum);
	fout << temp << endl;
	for (auto it = driverNodesList.begin(); it != driverNodesList.end(); ++it)
	{
		fout << *it << endl;
	}
	fout.close();

	char buf[256];
	sprintf_s(buf, "���� %d �����ڵ�, ����Ѿ������� driver_nodes.txt", driverNodesNum);
	CString str(buf);
	MessageBox(buf, "�����ڵ������", MB_OK | MB_ICONASTERISK);
}


void CComplexNetView::OnDriverFastAlgo()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	MessageBox("��Ҫ��ʾ:\n[1] ���㷨�������κ�����.\n[2] �㷨ֻ���������ڵ������,����Ҫ֪������������ڵ㣬�뿼��ʹ�á��ṹ�ɿ������ۡ����ϸ�ɿ������ۡ�",
				"�㷨������˵��", 
				MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION);

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	int driverNodesNum = numberofDriverNodesExactControllability(*pgraph);

	char buf[1024] = { '\0' };
	sprintf_s(buf, 1024, "�����繲�� %d �������ڵ�", driverNodesNum);
	CString info(buf);

	MessageBox(info, "�ɿ��Լ�����", MB_OK | MB_ICONASTERISK);

}


void CComplexNetView::OnDriversRankFast()
{
	CComplexNetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->NetTxtFileOpened == FALSE)
	{
		MessageBox(_T("Please open a network file first"));
		return;
	}

	MessageBox("��Ҫ��ʾ:\n[1] ���㷨֮�����ڴ���ϡ������.\n[2] �㷨ֻ���������ڵ������,����Ҫ֪������������ڵ㣬�뿼��ʹ�á��ṹ�ɿ������ۡ����ϸ�ɿ������ۡ��㷨.\n[3] ���㷨���õ����ƽ��������Ҫ��ȷ���������ʹ�á������ڵ���㡿�㷨",
		"�㷨������˵��.",
		MB_OK | MB_DEFBUTTON1 | MB_ICONEXCLAMATION);

	scn::UGraph::pGraph pgraph = pDoc->unet->GetTopology();
	int driverNodesNum = numberofDriverNodesFastRankAlgorithm(*pgraph);

	char buf[256] = { '\0' };
	sprintf_s(buf, 256, "�����繲�� %d �������ڵ�", driverNodesNum);
	CString info(buf);
	MessageBox(info, "�ɿ��Լ�����", MB_OK | MB_ICONASTERISK);
}

