// NetworkFun.cpp : 定义NetworkFun V1.0那部分 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "NetworkFun.h"
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <fstream>
#include <sstream>
#include <io.h> 
#include <fcntl.h> 
#include <sys/stat.h>
#include <queue>
#include <set>
int ReadNetworkFile(char * filename,NETWORK *ntwk)
{
	long int source_index, target_index;
	long int flag1,flag2,i;
	long int abc;
	long int numberOfVertices;
	long int row, col;
	unsigned long int posi1,posi2;
	double weight,weight0,posi;
	char temp[768];
	string line, buffer;
	vector<Node>::iterator iter;//Node类型的迭代器
	ifstream infile(filename);//定义ifstream的对象infile,打开文件
	flag1=0;
	flag2=2;
    ntwk->Directed=false;
	ntwk->Weighted=false;
    ntwk->NodeNumber=0;
    ntwk->LinkNumber=0;
    ntwk->DegreeNumber=0;
    ntwk->IndegreeNumber=0;
    ntwk->OutdegreeNumber=0;
    ntwk->Averagedegree=0.0;
    ntwk->Averageindegree=0.0;
    ntwk->Averageoutdegree=0.0;
    ntwk->Clustercoeff=0.0;
    ntwk->Inclustercoeff=0.0;
    ntwk->Outclustercoeff=0.0;
	ntwk->ClustercoeffNumber=0;
	ntwk->Diameter=0;
	ntwk->AverageDistance=0;
    srand((unsigned)time(NULL));
	ntwk->Net.resize(0);
	while(getline(infile,line))
	{
		if(line.find("*Vertices") != string::npos)
		{
	        istringstream line_stream(line);

			//read *Vertices and Number of Vertices
			line_stream>>buffer>>numberOfVertices;
			if(numberOfVertices<=0||numberOfVertices>MAXNODES)return -2;
			
			//Apply memory
			ntwk->Net.resize(numberOfVertices);
			if(ntwk->Net.size()!=numberOfVertices)return -1;

			//****Initialization NodeNo, NodeName X Y Z  Edges+++starts
			for(i=0;i<numberOfVertices;i++)
			{
			   ntwk->Net[i].NodeNo=i+1;
			   sprintf_s(temp,"%d",i+1);
			   strcpy_s(ntwk->Net[i].NodeName,temp);
			   ntwk->Net[i].X=(double)rand()/(double)RAND_MAX+0.0001;
			   ntwk->Net[i].Y=(double)rand()/(double)RAND_MAX+0.0001;
			   ntwk->Net[i].Z=(double)rand()/(double)RAND_MAX+0.0001;
			   ntwk->Net[i].Edges.clear();
			}
			//****Initialization NodeNo, NodeName X Y Z  Edges+++ends
		
			
			//read nodeno nodename and positions of vertices++++starts
			while(getline(infile, line) && line.find("*") == string::npos)
			{
	            istringstream line_stream1(line);
				if(line_stream1>>source_index)
				{
					if(source_index>0)
					{
					  //NodeNo
					  ntwk->Net[source_index - 1].NodeNo=source_index;

					  //****NodeName*****
					  line_stream1>>buffer;
					  posi1=line.find_first_of("\"");
					  posi2=line.find_last_of("\"");
					  if(posi1!=string::npos&&posi2!=string::npos)
					  {
					    strcpy_s(ntwk->Net[source_index - 1].NodeName,line.substr(posi1,posi2).c_str());
					    line_stream1.seekg(posi2+1);
					  }
					  else
					    strcpy_s(ntwk->Net[source_index - 1].NodeName,buffer.c_str());
                      //****NodeName*****
					  
                      //****X Y Z*****
					  if(line_stream1>>posi)
					  {
						if(posi>0&&posi<=1)
						  ntwk->Net[source_index - 1].X=posi;
					  }
					  if(line_stream1>>posi)
					  {
						if(posi>0&&posi<=1)
						  ntwk->Net[source_index - 1].Y=posi;
					  }
					  if(line_stream1>>posi)
					  {
						if(posi>0&&posi<=1)
						  ntwk->Net[source_index - 1].Z=posi;
					  }
					}
				}
			}
			//read nodeno nodename and positions of vertices++++ends
		}
		if(line.find("*Arcs") != string::npos)
		{
			//Read Arcs' source end and weight+++++starts
			while(getline(infile, line) && line.find("*") == string::npos)
			{
				istringstream line_stream2(line);
				if(line_stream2>>source_index)
				{
	                ntwk->Directed=true;
					line_stream2>>target_index;
					if(line_stream2>>weight)
					{
					   while(flag1==0)//judge if the weights are the same
					   {
						 weight0=weight;
						 flag1=1;
					   }
					   if(weight!=weight0)ntwk->Weighted=true;
					}
					else
					{
					   weight=1.0;
					}
					if(source_index > 0&&target_index>0)
					{
						//out
						ntwk->Net[source_index - 1].Edges.insert(make_pair(target_index - 1,Edge(source_index, target_index, weight)));
						//in
						ntwk->Net[target_index - 1].Edges.insert(make_pair(source_index - 1,Edge(source_index, target_index, weight)));
					}
				}
			}
			//Read Arcs' source end and weight+++++ends
		}
		if(line.find("*Arcslist") != string::npos)
		{
			while(getline(infile, line) && line.find("*") == string::npos)
			{
	            istringstream line_stream3(line);
				if(line_stream3>>source_index)
				{
	                ntwk->Directed=true;
					if(source_index > 0)
					{
						iter = ntwk->Net.begin() + source_index - 1;
						
						while(line_stream3>>target_index)
						{
							if(target_index>0)
							{
							  //out
							  iter->Edges.insert(make_pair(target_index - 1,Edge(source_index, target_index, 1.0)));
							  //in
							  ntwk->Net[target_index-1].Edges.insert(make_pair(source_index - 1,Edge(source_index, target_index, 1.0)));
							}
						}
					}
					else
					{
						while(line_stream3>>target_index)
						{
							if(target_index>0)
							{
							  //out
							  ntwk->Net[target_index-1].Edges.insert(make_pair(-source_index - 1,Edge(target_index,-source_index, 1.0)));
							  //in
							  ntwk->Net[-source_index - 1].Edges.insert(make_pair(target_index-1,Edge(target_index,-source_index, 1.0)));
							}
						}
					}
				}
			}
		}
		if(line.find("*Edges") != string::npos)//如果找到“边”的位置没有到文件头。string 类提供了 6 种查找函数,每种函数以不同形式的 find 命名。这些操作全都返回 string::size_type 类型的值，以下标形式标记查找匹配所发生的位置；或者返回一个名为 string::npos 的特殊值，说明查找没有匹配。string 类将 npos 定义为保证大于任何有效下标的值。
		{
			while(getline(infile, line) && line.find("*") == string::npos)
			{
	            istringstream line_stream4(line);//定义了一个字符串流
				if(line_stream4>>source_index)
				{
					line_stream4>>target_index;
					if(line_stream4>>weight)
					{
					   while(flag1==0)
					   {
						 weight0=weight;
						 flag1=1;
					   }
					   if(weight!=weight0)ntwk->Weighted=true;//判断是否为加权网络
					}
					else
					{
					   weight=1.0;
					}
                    if(source_index>0&&target_index>0)
					{
					  //out
					  ntwk->Net[source_index - 1].Edges.insert(make_pair(target_index - 1,Edge(source_index, target_index, weight)));//insert()第一个实参是指定要插入元素的位置的迭代器，第二个实参是要插入的元素。
					  //in
					  ntwk->Net[target_index - 1].Edges.insert(make_pair(source_index - 1,Edge(source_index, target_index, weight)));//使用make_pair函数创建新的pair对象
					}
				}
			}
		}
		if(line.find("*Edgeslist") != string::npos)
		{
			while(getline(infile, line) && line.find("*") == string::npos)
			{
				istringstream line_stream5(line);
				if(line_stream5>>source_index)
				{
					if(source_index > 0)
					{
						iter = ntwk->Net.begin() + source_index - 1;
						
						while(line_stream5>>target_index)
						{
							if(target_index>0)
							{
							  //out
							  iter->Edges.insert(make_pair(target_index - 1,Edge(source_index, target_index, 1.0)));
							  //in
							  ntwk->Net[target_index-1].Edges.insert(make_pair(source_index - 1,Edge(source_index, target_index, 1.0)));
							}
						}
					}
					else
					{
						while(line_stream5>>target_index)
						{
							if(target_index>0)
							{
							  //out
							  ntwk->Net[target_index-1].Edges.insert(make_pair(-source_index - 1,Edge(target_index,-source_index, 1.0)));
							  //in
							  ntwk->Net[-source_index - 1].Edges.insert(make_pair(target_index-1,Edge(target_index,-source_index, 1.0)));
							}
						}
					}
				}
			}
		}
        if(line.find("*Matrix") != string::npos)
		{
            ntwk->Directed=true;
			row = 0;
			while(getline(infile, line) && line.find("*") == string::npos)
			{
				istringstream line_stream5(line);
				col = 0;
				while(line_stream5 >> abc)
				{
					if(abc != 0)
					{
						ntwk->Net[row].Edges.insert(make_pair(col,Edge(row+1, col+1, abs(abc))));
						ntwk->Net[col].Edges.insert(make_pair(row,Edge(row+1, col+1, abs(abc))));
						if(abs(abc)!=1.0)ntwk->Weighted=true;
					}
					col++;
				}
				row++;
			}
		}
	}
	ntwk->LinkNumber = 0;
	for(i = 0; i<(long int)ntwk->Net.size(); i++)
		ntwk->LinkNumber +=ntwk->Net[i].Edges.size();
	ntwk->LinkNumber/=2;
	if(ntwk->LinkNumber<=0||ntwk->LinkNumber>MAXLINKS)return -3;
	ntwk->NodeNumber=ntwk->Net.size();
	return 0;
}

int RegularNetworkGenerate(char * filename,long int m_reg_nodes,long int m_reg_neighbors)
{
	long int i,j;
	long int fr,to;
	char a[768];
	double section;
	char temp[768];
	if(m_reg_nodes<3||m_reg_nodes>50000)return -1;
	if(m_reg_neighbors<2||m_reg_neighbors%2!=0||m_reg_neighbors>m_reg_nodes-1)
	  return -2;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network Regular\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_reg_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_reg_nodes;
	for(i=0;i<m_reg_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	for(j=0;j<m_reg_nodes;j++)
	{
	  for(i=1;i<=m_reg_neighbors/2;i++)
	  {
	    fr=j;
		to=j+i;
		if(to>=m_reg_nodes)to=to-m_reg_nodes;
		sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	    strcpy_s(a,temp);
	    _write(fh,a,strlen(a));
	  }
	}
	_close(fh);
	return 0;
}

int RandomNetworkGenerate(char * filename,long int m_ran_nodes,long int m_ran_edges)
{
	long int i,j;
	char a[768];
	double section,c,d;
	char temp[768];
	if(m_ran_nodes<3||m_ran_nodes>50000)return -1;
	if(m_ran_edges<1||m_ran_edges>m_ran_nodes*(m_ran_nodes-1)/2||m_ran_edges>1000000)
	  return -2;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
    if(fh==-1)return -3;
	strcpy_s(a,"*Network Random\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_ran_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_ran_nodes;
	for(i=0;i<m_ran_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	long int edges;
    srand( (unsigned)time( NULL ) );
	edges=0;
//	while(edges<m_ran_edges)
	//{
	  //fr=(int)((double)rand()/(double)RAND_MAX*(double)(m_ran_nodes-1))+1;
	  //to=(int)((double)rand()/(double)RAND_MAX*(double)(m_ran_nodes-1))+1;
	  //while(to==fr)
	    // to=(int)((double)rand()/(double)RAND_MAX*(double)(m_ran_nodes-1))+1;
	  //c=(double)rand()/(double)RAND_MAX;
	  //if(c<2.0*(double)m_ran_edges/(double)m_ran_nodes/(double)(m_ran_nodes-1))
	 // {
	//	sprintf_s(temp,"%d %d 1\n",fr,to);
	  //  a+=temp;
	//	edges++;
	 // }
	//}
    for(i=0;i<m_ran_nodes;i++)
	{
	  if(edges>=m_ran_edges)break;
	  for(j=i+1;j<m_ran_nodes;j++)
	  {
		 if(edges>=m_ran_edges)break;
		 c=(double)rand()/(double)RAND_MAX;
		 d=2.0*(double)m_ran_edges/(double)m_ran_nodes/(double)(m_ran_nodes-1);
		 if(c<d)
		 {
		   sprintf_s(temp,"%d %d 1\n",i+1,j+1);
	       strcpy_s(a,temp);
	       _write(fh,a,strlen(a));
		   edges++;
		 }
	  }
	}
	_close(fh);
	return 0;
}

int WSSmallWorldNetworkGenerate(char * filename,long int m_wssmall_nodes,long int m_wssmall_neighbors,double m_wssmall_prob)
{
	long int i,j,ii,k;
	long int fr,to;
	char a[768];
	double section,b,c;
	long int *unlinked;
	char temp[768];
	if(m_wssmall_prob<0||m_wssmall_prob>1)return -4;
	if(m_wssmall_nodes<4||m_wssmall_nodes>50000)return -1;
	if(m_wssmall_neighbors<2||m_wssmall_neighbors%2!=0||m_wssmall_neighbors>m_wssmall_nodes/2)
	  return -2;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network WS_SmallWorld\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_wssmall_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_wssmall_nodes;
	for(i=0;i<m_wssmall_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
    srand( (unsigned)time( NULL ) );
	unlinked=new long int [m_wssmall_nodes-m_wssmall_neighbors-1];
	if(unlinked==NULL)return -5;
	for(j=0;j<m_wssmall_nodes;j++)
	{
	  for(i=m_wssmall_neighbors/2+1;i<=m_wssmall_nodes-m_wssmall_neighbors/2-1;i++)
	  {
		k=i-m_wssmall_neighbors/2-1;
		unlinked[k]=j+i;
		if(unlinked[k]>=m_wssmall_nodes)
		  unlinked[k]=unlinked[k]-m_wssmall_nodes;
	  }
	  for(i=1;i<=m_wssmall_neighbors/2;i++)
	  {
		fr=j;
		to=j+i;
		if(to>=m_wssmall_nodes)to=to-m_wssmall_nodes;
		b=(double)rand()/(double)RAND_MAX;
		if(m_wssmall_prob!=0&&b<=m_wssmall_prob)
		{
		  c=(double)rand()/(double)RAND_MAX;
		  ii=(long int)(c*(double)(m_wssmall_nodes-m_wssmall_neighbors-1));
		  if(ii!=0)
		  {
			to=unlinked[ii-1];
			unlinked[ii-1]=j+i;
			if(unlinked[ii-1]>=m_wssmall_nodes)
			  unlinked[ii-1]=unlinked[ii-1]-m_wssmall_nodes;
		  }
		}
		sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	    strcpy_s(a,temp);
	    _write(fh,a,strlen(a));
	  }
	}
	_close(fh);
	delete []unlinked;
	return 0;
}

int NWSmallWorldNetworkGenerate(char * filename,long int m_nwsmall_nodes,long int m_nwsmall_neighbors,double m_nwsmall_prob)
{
	long int i,j;
	long int fr,to;
	char a[768];
	double section,b;
	char temp[768];
	if(m_nwsmall_prob<0||m_nwsmall_prob>1)return -4;
	if(m_nwsmall_nodes<4||m_nwsmall_nodes>50000)return -1;
	if(m_nwsmall_neighbors<2||m_nwsmall_neighbors%2!=0||m_nwsmall_neighbors>m_nwsmall_nodes/2)
	  return -2;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network NW_SmallWorld\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_nwsmall_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_nwsmall_nodes;
	for(i=0;i<m_nwsmall_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
    srand( (unsigned)time( NULL ) );
	for(j=0;j<m_nwsmall_nodes;j++)
	{
	  for(i=1;i<=m_nwsmall_neighbors/2;i++)
	  {
		fr=j;
		to=j+i;
		if(to>=m_nwsmall_nodes)to=to-m_nwsmall_nodes;
		sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	    strcpy_s(a,temp);
	    _write(fh,a,strlen(a));
	  }
	  if(m_nwsmall_nodes%2!=0)
	  {
	    for(i=m_nwsmall_neighbors/2+1;i<=m_nwsmall_nodes/2;i++)
		{
		  b=(double)rand()/(double)RAND_MAX;
		  if(m_nwsmall_prob!=0&&b<=m_nwsmall_prob)
		  {
		    fr=j;
		    to=j+i;
		    if(to>=m_nwsmall_nodes)to=to-m_nwsmall_nodes;
		    sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	        strcpy_s(a,temp);
	        _write(fh,a,strlen(a));
		  }
		}
	  }
	  else
	  {
	    for(i=m_nwsmall_neighbors/2+1;i<=m_nwsmall_nodes/2-1;i++)
		{
		  b=(double)rand()/(double)RAND_MAX;
		  if(m_nwsmall_prob!=0&&b<=m_nwsmall_prob)
		  {
		    fr=j;
		    to=j+i;
		    if(to>=m_nwsmall_nodes)to=to-m_nwsmall_nodes;
		    sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	        strcpy_s(a,temp);
	        _write(fh,a,strlen(a));
		  }
		}
		b=(double)rand()/(double)RAND_MAX;
		if(m_nwsmall_prob!=0&&b<=m_nwsmall_prob&&j<m_nwsmall_nodes/2)
		{
		    fr=j;
		    to=j+m_nwsmall_nodes/2;
		    if(to>=m_nwsmall_nodes)to=to-m_nwsmall_nodes;
		    sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	        strcpy_s(a,temp);
	        _write(fh,a,strlen(a));
		}
	  }
	}
	_close(fh);
	return 0;
}

int BANetworkGenerate(char * filename,long int m_ba_inodes,long int m_ba_onodes,long int m_ba_iterations)
{
	long int i,j,ite,nodes,links,newlinks;
	char a[768];
	double b,c;
	long int *degree,*sta,*end,tempn,no;
	bool *linked;
	char temp[768];
	if(m_ba_iterations<1||m_ba_iterations>2000)return -4;
	if(m_ba_inodes<2||m_ba_inodes>20)return -1;
	if(m_ba_onodes<2||m_ba_onodes>m_ba_inodes)
	  return -2;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network BA_ScaleFree\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_ba_inodes+m_ba_iterations);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	linked=new bool[m_ba_inodes+m_ba_iterations];
	if(linked==NULL)return -5;
	degree=new long int[m_ba_inodes+m_ba_iterations];
	if(degree==NULL)
	{
		delete []linked;
		return -5;
	}
    srand( (unsigned)time( NULL ) );
	for(i=0;i<m_ba_inodes+m_ba_iterations;i++)
	{
		  b=(double)rand()/(double)RAND_MAX;
		  c=(double)rand()/(double)RAND_MAX;
          sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  b+0.00001, 
		  c+0.00001,0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	sta=new long int[2*m_ba_onodes*m_ba_iterations-m_ba_onodes];
	if(sta==NULL)
	{
		delete []linked;
		delete []degree;
		return -5;
	}
	end=new long int[2*m_ba_onodes*m_ba_iterations-m_ba_onodes];
	if(end==NULL)
	{
		delete []linked;
		delete []degree;
		delete []sta;
		return -5;
	}
	nodes=m_ba_inodes;
	links=0;
	newlinks=0;
	for(ite=0;ite<m_ba_iterations;ite++)
	{
	  for(i=0;i<nodes;i++)
		linked[i]=false;
	  if(ite==0)
	  {
	     while(newlinks!=m_ba_onodes)
		 {
           b=(double)rand()/(double)RAND_MAX;
		   tempn=(long int)(b*(m_ba_inodes-1));
		   if(linked[tempn]==true)continue;
		   sta[newlinks]=tempn+1;
		   linked[sta[newlinks]-1]=true;
           end[newlinks]=m_ba_inodes;
		   sprintf_s(temp,"%d %d 1\n",sta[newlinks],end[newlinks]);
	       strcpy_s(a,temp);
	       _write(fh,a,strlen(a));
		   newlinks++;
		 }
		 links+=newlinks;
		 newlinks=0;
	  }
	  else
	  {
	     no=0;
		 while(newlinks!=m_ba_onodes)
		 {
           b=(double)rand()/(double)RAND_MAX;
		   c=(double)degree[no]/(double)(2*m_ba_onodes*ite-m_ba_onodes);
		   if(b<c)
		   {
             if(linked[no]==true)continue;
		     sta[links+newlinks]=no+1;
		     linked[sta[links+newlinks]-1]=true;
             end[links+newlinks]=m_ba_inodes+ite;
		     sprintf_s(temp,"%d %d 1\n",sta[links+newlinks],end[links+newlinks]);
	         strcpy_s(a,temp);
	         _write(fh,a,strlen(a));
		     newlinks++;
		   }
		   no++;
		   if(no==nodes)no=0;
		 }
		 links+=newlinks;
		 newlinks=0;
	  }
	  nodes++;
	  for(i=0;i<nodes;i++)
		degree[i]=0;
	  for(i=0;i<nodes;i++)
	  {
		 for(j=0;j<links;j++)
		 {
			 if(sta[j]==i+1||end[j]==i+1)degree[i]=degree[i]+1;
		 }
	  }
	}
	_close(fh);
    delete []linked;
	delete []sta;
	delete []degree;
	delete []end;
	return 0;
}
void CalculateDegrees(NETWORK *ntwk)
{
   long int i,j;
   double sum,sumin,sumout;
   multimap <long int,Edge>::iterator iter;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	  ntwk->Net[j].Indegree=0;
	  ntwk->Net[j].Degree=0;
	  ntwk->Net[j].Outdegree=0;
   }
   for(i=0;i<ntwk->NodeNumber;i++)
   {
	   for(iter=ntwk->Net[i].Edges.begin();iter!=ntwk->Net[i].Edges.end();iter++)
	   {
	      if(iter->second.Tail-1==i)
		  {
		    ntwk->Net[i].Indegree++;
			ntwk->Net[i].Degree++;
		  }
	      else
		  {
		    ntwk->Net[i].Outdegree++;
			ntwk->Net[i].Degree++;
		  }
	   }
   }
   sum=0.0;
   sumin=0.0;
   sumout=0.0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	  sum+=ntwk->Net[j].Degree;
	  sumin+=ntwk->Net[j].Indegree;
	  sumout+=ntwk->Net[j].Outdegree;
   }
   ntwk->Averagedegree=(float)(sum/(double)ntwk->NodeNumber);
   ntwk->Averageindegree=(float)(sumin/(double)ntwk->NodeNumber);
   ntwk->Averageoutdegree=(float)(sumout/(double)ntwk->NodeNumber);
}

int CalculateNetworkDegreeDistribution(NETWORK *ntwk,double *degree,double *prob)
{
   long int i,j,k,l,index;
   double temp,max;
  // double *out;
   double *in;
   in=new double [ntwk->NodeNumber];
   if(in==NULL)return -1;
   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	   in[j]=ntwk->Net[j].Degree;
   }
   for(i=0;i<ntwk->NodeNumber-1;i++)
   {
	  index=i;
	  for(j=i+1;j<ntwk->NodeNumber;j++)
	  {
		if(in[index]>in[j]) 
		{
		  index=j;
		}  //end of for j,get the index
	  }
	  if(index==i)  //Minimal 
	  {
	    continue;//next i
	  }
	  temp=in[i];
	  in[i]=in[index];
	  in[index]=temp;
   }

   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
     if(in[j]>max)
	 {
	   max=in[j];
	   degree[k]=max;
	   if(k>0)prob[k-1]=(double)l/(double)ntwk->NodeNumber;
	   k++;
	   l=1;
	 }
	 else
	 {
	   l++;
	 }
   }
   prob[k-1]=(double)l/(double)ntwk->NodeNumber;
   ntwk->DegreeNumber=k;
   delete []in;
   return 0;
}

int CalculateNetworkDegreeCorrelation(NETWORK *ntwk,double *degree,double *corr)
{
   long int i,j,k,kk,l,index,neighbor,own;
   double temp,max,sum;
   double *out;
   double *in;
   out=new double [ntwk->NodeNumber];
   if(out==NULL)
   {
	  return -1;
   }
   in=new double [ntwk->NodeNumber];
   if(in==NULL)
   {
	  delete []out;
	  return -1;
   }
   multimap <long int, Edge>::iterator iter;

   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	   for(iter=ntwk->Net[j].Edges.begin();iter!=ntwk->Net[j].Edges.end();iter++)
	   {
	      if(iter->second.Tail-1==j)
		  {
		    neighbor=iter->second.Head;
			own=iter->second.Tail;
		  }
		  else
		  {
		    neighbor=iter->second.Tail;
			own=iter->second.Head;
		  }

          if(own>max)
		  {
	        max=own;
            for(i=0;i<ntwk->NodeNumber;i++)
			{ 
	          if(ntwk->Net[i].NodeNo==max)
			  {
		        in[k]=ntwk->Net[i].Degree;
		        break;
			  }
			}
	        if(k>0) out[k-1]=sum/l;
	        k++;
	        l=1;
	        for(i=0;i<ntwk->NodeNumber;i++)
			{ 
	          if(ntwk->Net[i].NodeNo==neighbor)
			  {
			    sum=ntwk->Net[i].Degree;
			    break;
			  }
			}
		  }
	      else
		  {
	        l++;
	        for(i=0;i<ntwk->NodeNumber;i++)
			{ 
	          if(ntwk->Net[i].NodeNo==neighbor)
			  {
			    sum=sum+ntwk->Net[i].Degree;
			    break;
			  }
			}
		  }
	   }
   }
   out[k-1]=sum/l;

   for(i=0;i<k-1;i++)
   {
	  index=i;
	  for(j=i+1;j<k;j++)
	  {
		if(in[index]>in[j]) 
		{
		  index=j;
		}  //end of for j,get the index
	  }
	  if(index==i)  //Minimal 
	  {
	    continue;//next i
	  }
	  temp=in[i];
	  in[i]=in[index];
	  in[index]=temp;
	  temp=out[i];
	  out[i]=out[index];
	  out[index]=temp;
   }
   kk=k;
   max=-1;
   k=0;
   for(j=0;j<kk;j++)
   {
     if(in[j]>max)
	 {
	   max=in[j];
	   degree[k]=max;
	   if(k>0)corr[k-1]=sum/l;
	   k++;
	   l=1;
	   sum=out[j];
	 }
	 else
	 {
	   l++;
	   sum=sum+out[j];
	 }
   }
   corr[k-1]=sum/l;
   ntwk->DegreeNumber=k;
   delete []in;
   delete []out;
   return 0;
}

int CalculateNetworkClusterCoeff(NETWORK *ntwk)
{
   long int i,j,l,k,m;
   long int *linked,*num;
   linked= new long int [ntwk->NodeNumber];
   if(linked==NULL)return -1;
   num= new long int [ntwk->NodeNumber];
   if(num==NULL)
   {
     delete []linked;
	 return -1;
   }
   multimap <long int, Edge>::iterator iter1,iter2;
   double sum;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	   ntwk->Net[j].Clustercoeff=(float)((ntwk->Net[j].Degree-1)*ntwk->Net[j].Degree);
	   k=0;
	   for(iter1=ntwk->Net[j].Edges.begin();iter1!=ntwk->Net[j].Edges.end();iter1++)
	   {
		  linked[k]=iter1->first+1;
		  k++;
	   }
	   num[j]=0;
       for(i=0;i<ntwk->NodeNumber;i++)
	   {
         for(iter1=ntwk->Net[i].Edges.begin();iter1!=ntwk->Net[i].Edges.end();iter1++)
		 {
		    for(l=0;l<k;l++)
			{
		      for(m=0;m<l;m++)
			  {
			    if((iter1->second.Head==linked[l]&&iter1->second.Tail==linked[m])
					||(iter1->second.Head==linked[m]&&iter1->second.Tail==linked[l]))
				{
			      num[j]++;
				} 
			  }
			}
		  }
	   }
	   if(ntwk->Net[j].Clustercoeff>0.0)
	     ntwk->Net[j].Clustercoeff=(float)((double)num[j]/ntwk->Net[j].Clustercoeff);
	   else
	     ntwk->Net[j].Clustercoeff=0.0;
   }

   sum=0.0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	  if(ntwk->Net[j].Degree!=0)
	  sum+=ntwk->Net[j].Clustercoeff;
   }
   ntwk->Clustercoeff=(float)(sum/(double)ntwk->NodeNumber);
   delete []linked;
   delete []num;
   return 0;
}

int CalculateNetworkClusteringDistribution(NETWORK *ntwk,double *cluster,double *prob)
{
   long int i,j,k,l,index;
   double temp,max;
   double *in;
   in=new double [ntwk->NodeNumber];
   if(in==NULL)return -1;
   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	   in[j]=ntwk->Net[j].Clustercoeff;
   }
   for(i=0;i<ntwk->NodeNumber-1;i++)
   {
	  index=i;
	  for(j=i+1;j<ntwk->NodeNumber;j++)
	  {
		if(in[index]>in[j]) 
		{
		  index=j;
		}  //end of for j,get the index
	  }
	  if(index==i)  //Minimal 
	  {
	    continue;//next i
	  }
	  temp=in[i];
	  in[i]=in[index];
	  in[index]=temp;
   }

   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
     if(in[j]>max)
	 {
	   max=in[j];
	   cluster[k]=max;
	   if(k>0)prob[k-1]=(double)l/(double)ntwk->NodeNumber;
	   k++;
	   l=1;
	 }
	 else
	 {
	   l++;
	 }
   }
   prob[k-1]=(double)l/(double)ntwk->NodeNumber;
   ntwk->ClustercoeffNumber=k;
   delete []in;
   return 0;
}

int CalculateNetworkClusterDegreeCorrelation(NETWORK *ntwk,double *degree,double *corr)
{
   long int i,j,k,l,index;
   double temp,max,sum;
   double *out;
   double *in;
   out=new double [ntwk->NodeNumber];
   if(out==NULL)
   {
	  return -1;
   }
   in=new double [ntwk->NodeNumber];
   if(in==NULL)
   {
	  delete []out;
	  return -1;
   }
   for(j=0;j<ntwk->NodeNumber;j++)
   {
	  in[j]=ntwk->Net[j].Degree;
	  out[j]=ntwk->Net[j].Clustercoeff;
   }
   for(i=0;i<ntwk->NodeNumber-1;i++)
   {
	  index=i;
	  for(j=i+1;j<ntwk->NodeNumber;j++)
	  {
		if(in[index]>in[j]) 
		{
		  index=j;
		}  //end of for j,get the index
	  }
	  if(index==i)  //Minimal 
	  {
	    continue;//next i
	  }
	  temp=in[i];
	  in[i]=in[index];
	  in[index]=temp;
	  temp=out[i];
	  out[i]=out[index];
	  out[index]=temp;
   }
   max=-1;
   k=0;
   for(j=0;j<ntwk->NodeNumber;j++)
   {
     if(in[j]>max)
	 {
	   max=in[j];
	   degree[k]=max;
	   if(k>0)corr[k-1]=sum/l;
	   k++;
	   l=1;
	   sum=out[j];
	 }
	 else
	 {
	   l++;
	   sum=sum+out[j];
	 }
   }
   corr[k-1]=sum/l;
   ntwk->DegreeNumber=k;
   delete []in;
   delete []out;
   return 0;
}

void CalculateNetworkAverageDistanceAndDiameter(NETWORK *ntwk)
//implemented by SPFA
{
	long int i,j;
	long int distance;
	long int front;
	if(ntwk->Net.size()<2)return;
	ntwk->DistanceNum.clear();
	ntwk->DistanceNum.resize(ntwk->Net.size()-1);
	ntwk->Diameter=0;
	//initial
	long int distance_total=0, node_pair_total=0;
	//main part
	vector<long int>	shortest_distance(ntwk->Net.size());
	queue<long int>	queue_buffer;
	vector<bool>	IsInQueue(ntwk->Net.size(), false);
	vector<Node>::iterator iter_node;
	multimap<long int, Edge>::iterator iter_edge;
	for(i=0;i<(long int)ntwk->Net.size();i++)
	{//iterate every node
		shortest_distance.assign(ntwk->Net.size(), 2*ntwk->Net.size());
		shortest_distance[i] = 0;
		//SPFA part
		queue_buffer.push(i);//push source node
		while(!queue_buffer.empty())
		{
			front = queue_buffer.front();
			queue_buffer.pop();
			IsInQueue[front] = false;
			iter_node = ntwk->Net.begin() + front;
			for(iter_edge = iter_node->Edges.begin();iter_edge != iter_node->Edges.end();
			iter_edge++)
			{
				if(IsInQueue[iter_edge->first] == false &&
				shortest_distance[front] + 1 < shortest_distance[iter_edge->first])
				{
					shortest_distance[iter_edge->first] = shortest_distance[front] + 1;
					queue_buffer.push(iter_edge->first);
					IsInQueue[iter_edge->first] = true;
				}
			}
		}
		for(j= 0; j < (long int)shortest_distance.size(); j++)
		{
			distance = shortest_distance[j];
			//statictis
			if(distance > 0 && distance < (long int)(2*ntwk->Net.size()))
			{
				distance_total += distance;
				node_pair_total++;
				if(distance>ntwk->Diameter)ntwk->Diameter=distance;
				ntwk->DistanceNum[distance]=ntwk->DistanceNum[distance]+1;
			}
		}
	}
	if(node_pair_total>0)
	  ntwk->AverageDistance=(double)(distance_total)/(double)node_pair_total;
	else
	  ntwk->AverageDistance=0.0;
}

long int ComputeDistance(NETWORK ntwk,long int Node1,long int Node2)
//implemented by SPFA
{
	//initial
	size_t distance_total=0, node_pair_total=0;
	//main part
	vector<size_t>	shortest_distance(ntwk.Net.size());//距离容器个数初始化为网络节点数目
	queue<size_t>	queue_buffer;//队列容器
	vector<bool>	IsInQueue(ntwk.Net.size(), false);//二值容器全初始化为假
	shortest_distance.assign(ntwk.Net.size(), 2*ntwk.Net.size());//初始化网络节点个2倍网络节点数的元素
	shortest_distance[Node1-1] = 0;
	//SPFA part
	queue_buffer.push(Node1-1);//push source node//末尾增加一个元素
	long int front;
	vector<Node>::iterator iter_node;//节点容器
	multimap<long int, Edge>::iterator iter_edge;
	while(!queue_buffer.empty())
	{
		front = queue_buffer.front();//返回第一个元素
		queue_buffer.pop();//删除第一个元素
		IsInQueue[front] = false;
		iter_node = ntwk.Net.begin() + front;
		for(iter_edge = iter_node->Edges.begin();
		iter_edge != iter_node->Edges.end(); iter_edge++)
		{
				if(IsInQueue[iter_edge->first] == false &&
				shortest_distance[front] + 1 < shortest_distance[iter_edge->first])
				{
					shortest_distance[iter_edge->first] = shortest_distance[front] + 1;
					queue_buffer.push(iter_edge->first);//zengjia
					IsInQueue[iter_edge->first] = true;
				}
		}  
	}
	return shortest_distance[Node2-1];
}

size_t GetShortestDistanceA(NETWORK ntwk,size_t indexOfSource, size_t indexOfTarget)
{
   //breadth-first search
   queue<size_t> search_queue;
   unordered_map<size_t, size_t> distance;
   unordered_set<size_t> in_queue;
   size_t front;
   //initial
   distance[indexOfSource] = 0;
   search_queue.push(indexOfSource);
   in_queue.insert(indexOfSource);
   
   while(!search_queue.empty())
   {
      front = search_queue.front();
      search_queue.pop();
      in_queue.erase(front);

	  auto& edge = ntwk.Net[front].Edges;
      for(auto other = edge.begin(); other != edge.end(); other++)
      {
		  if(other->first == indexOfTarget)
			  return distance[front] + 1;

		  if(in_queue.find(other->first) == in_queue.end() &&
			  (distance.find(other->first) == distance.end() || distance[front] + 1 < distance[other->first]))
		{
			distance[other->first] = distance[front] + 1;
			search_queue.push(other->first);
			in_queue.insert(other->first);
		}
      }
   }
   //if this point is reached, the indexOfTarget is an isolated node 
   return size_t(-1);
}
//Zhang Zhi Zhong的算法
int EdgeIterationDeterminSWNetworkGenerate(char *filename,long int m_iterations)
{
	long int i;
	long int nodes;
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<1||m_iterations>1000)return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -2;
	strcpy_s(a,"*Network Edge Iteration Determined Small-World\n");
	_write(fh,a,strlen(a));
	nodes=(long int)pow(2.0,m_iterations) * 3;
	sprintf_s(temp," %d\n",nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)nodes;
	for(i=0;i<nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
   list<pair<size_t, size_t>> new_edges;
   list<pair<size_t, size_t>> previous_new_edges;
   size_t node_count = 3;
   //time 0
   for(size_t i = 0; i < 3; i++)
   {
	  sprintf_s(temp,"%d %d 1\n",i+1,(i+1)% 3 + 1);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
      new_edges.push_back(make_pair(i, (i+1) % 3));
   }
   //add
   for(int j = 0; j < m_iterations; j++)
   {
      previous_new_edges.clear();
      swap(previous_new_edges, new_edges);
      for(auto edge = previous_new_edges.begin(); 
	  edge != previous_new_edges.end(); edge++)
      {
	     size_t new_node = ++node_count;
	     //triple(new_node, edge->first, edge->second)
	     sprintf_s(temp,"%d %d 1\n",new_node, edge->first + 1);
	     strcpy_s(a,temp);
	     _write(fh,a,strlen(a));
	     sprintf_s(temp,"%d %d 1\n",new_node, edge->second + 1);
	     strcpy_s(a,temp);
	     _write(fh,a,strlen(a));
	     new_edges.push_back(make_pair(new_node, edge->first));
	     new_edges.push_back(make_pair(new_node, edge->second));
      }
   }
	_close(fh);
	return 0;
}

//非小世界网络的确定性模型
int DeterminURTNetworkGenerate(char *filename,long int m_iterations)
{
	long int i,j;
	long int fr,to,nodes;
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<1||m_iterations>1000)return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -2;
	strcpy_s(a,"*Network Determin URT\n");
	_write(fh,a,strlen(a));
	nodes=(long int)pow(2.0,m_iterations);
	sprintf_s(temp," %d\n",nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)nodes;
	for(i=0;i<nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	for(i=0;i<m_iterations;i++)
	{
	   nodes=(long int)pow(2.0,i);
	   for(j=0;j<nodes;j++)
	   {
		   fr=j;
		   to=j+nodes;
		   sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	       strcpy_s(a,temp);
	       _write(fh,a,strlen(a));
	   }
	}
	_close(fh);
	return 0;
}

//陆哲明和郭世泽的算法在physica A 2012年
//Zhe-Ming Lu, and Shi-Ze Guo(2012). A small-world network derived from the deterministic uniform recursive tree. Physica A. 391(1-2), 87-92.
int DeterminSWURTNetworkGenerate(char *filename,long int m_iterations)
{
	long int i,j;
	long int fr,to,nodes;
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<1||m_iterations>1000)return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -2;
	strcpy_s(a,"*Network Determin Small-World URT\n");
	_write(fh,a,strlen(a));
	nodes=(long int)pow(2.0,m_iterations);
	sprintf_s(temp," %d\n",nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)nodes;
	for(i=0;i<nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	for(i=0;i<m_iterations;i++)
	{
	   nodes=(long int)pow(2.0,i);
	   for(j=0;j<nodes;j++)
	   {
		   fr=j;
		   to=j+nodes;
		   sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	       strcpy_s(a,temp);
	       _write(fh,a,strlen(a));
	   }
	   if(nodes>=2)
	   {
	     for(j=0;j<nodes;j++)
		 {
		   fr=j;
		   to=nodes*2-1-j;
		   sprintf_s(temp,"%d %d 1\n",fr+1,to+1);
	       strcpy_s(a,temp);
	       _write(fh,a,strlen(a));
		 } 
	   }
	}
	_close(fh);
	return 0;
}

int DeterminTSSWNetworkGenerate(char *filename,long int m_iterations)
{
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<1||m_iterations>30) return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network Determin TS\n");
	_write(fh,a,strlen(a));
	long int m_nodes;
	m_nodes=(long int)pow(2.0,m_iterations+1)-1;
	sprintf_s(temp," %d\n",m_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_nodes;
	for(int i=0;i<m_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	//special conditions
	if(m_nodes == 1)
	{
		_close(fh);
		return 0;
	}
	sprintf_s(temp,"1 2 1\n");
	strcpy_s(a,temp);	
	sprintf_s(temp,"1 3 1\n");
	strcat_s(a,temp);	
	sprintf_s(temp,"2 3 1\n");
	strcat_s(a,temp);	
	_write(fh,a,strlen(a));
	if(m_nodes == 3)
	{
		_close(fh);
		return 0;
	}
   //begin to normal procedure
   queue<pair<size_t, vector<size_t>> > leaf_queue;//pair<self, ancestor>
   leaf_queue.push(make_pair(1, vector<size_t>(1)));
   leaf_queue.push(make_pair(2, vector<size_t>(1)));
   //construct node in breadth-first order
   size_t records = 0;
   int current_number = 3;
   while(current_number < m_nodes)
   {
      auto current = leaf_queue.front();
      leaf_queue.pop();
      //left node
      size_t left = current_number++;
	  sprintf_s(temp,"%d %d 1\n",current.first+1,left+1);
	  strcpy_s(a,temp);
	  //add ancestor
	  sprintf_s(temp,"%d %d 1\n",left+1,current.second[current.second.size()-1] + 1);
	  strcat_s(a,temp);
	  _write(fh,a,strlen(a));
      //right node
      size_t right = 0;
      right = current_number++;
		sprintf_s(temp,"%d %d 1\n",current.first+1,right+1);
		strcpy_s(a,temp);
	    sprintf_s(temp,"%d %d 1\n",left+1,right+1);
		strcat_s(a,temp);
	    //add ancestor
		sprintf_s(temp,"%d %d 1\n",right+1,current.second[current.second.size()-1]+1);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
      //add ancestor list
      vector<size_t> temp(current.second.begin(), current.second.end());
      temp.push_back(current.first);
      leaf_queue.push(make_pair(left, temp));
      leaf_queue.push(make_pair(right, temp));
   }
	_close(fh);
	return 0;
}


//郭世泽、李宠、陆哲明和乔玉龙的算法
//Shi-Ze Guo, Chong Li, Zhe-Ming Lu and Yu-Long Qiao (2012). A Pinwheel-Shaped Determinstic Small-World Network. ICIC Express Letters. 6(7):1809-1814.
int PinWheelDeterminSWNetworkGenerate(char *filename,long int m_iterations)
{
	long int i,j;
	long int fr,to,frtemp1=6,frtemp2=8;
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<0||m_iterations>50000)return -1;
	
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network PinWheel SW Determin\n");
	_write(fh,a,strlen(a));
	long int m_pinwheel_nodes=m_iterations*4+5;
	sprintf_s(temp," %d\n",m_pinwheel_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_pinwheel_nodes;
	for(i=0;i<m_pinwheel_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	fr=1;
	to=2;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	fr=1;
	to=3;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	fr=1;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	fr=1;
	to=5;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	fr=2;
	to=3;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	fr=2;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	fr=2;
	to=5;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	fr=3;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	fr=3;
	to=5;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	fr=4;
	to=5;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	_write(fh,a,strlen(a));
	for(j=0;j<m_iterations;j++)
	{	
		fr=6+j*4;
		to=6+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=6+j*4;
		to=6+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);		
		fr=7+j*4;
		to=7+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
		fr=7+j*4;
		to=7+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=7+j*4;
		to=7+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);		
		fr=8+j*4;
		to=8+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
		fr=8+j*4;
		to=8+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=8+j*4;
		to=8+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);	
		fr=9+j*4;
		to=9+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
		fr=9+j*4;
		to=9+j*4-7;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=9+j*4;
		to=9+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		fr=9+j*4;
		to=9+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));		
		if((frtemp1-2)%4!=0)
		{
		fr=frtemp1;
		to=1;
		frtemp1+=3;
		}
		else
		{
		fr=frtemp1;
		to=1;
		frtemp1+=7;
		}
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		/*if((frtemp2-2)%4!=0)
		{
		fr=frtemp2;
		to=1;
		frtemp2+=3;
		}
		else
		{
		fr=frtemp2;
		to=1;
		frtemp2+=7;
		}
		sprintf_s(temp,"%d %d 1\n",fr,to);
		a+=temp;*/
		_write(fh,a,strlen(a));
	}
	_close(fh);
	return 0;
}  

//李宠、郭世泽、陆哲明和乔玉龙算法
// Chong Li, Shi-Ze Guo, Zhe-Ming Lu and Yu-Long Qiao(2011): A Swirl-shaped Deterministic Network with High Clustering Coefficient. Information Technology Journal. 10(10):1994-1998.
int SwirlDeterminSWNetworkGenerate(char *filename,long int m_iterations)
{
	long int i,j;
	long int fr,to;
	char a[768];
	double section;
	char temp[768];
	if(m_iterations<0||m_iterations>50000)return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network Swirl Determin SW\n");
	_write(fh,a,strlen(a));
	long int m_swirl_nodes=m_iterations*4+4;
	sprintf_s(temp," %d\n",m_swirl_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_swirl_nodes;
	for(i=0;i<m_swirl_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	fr=1;
	to=2;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	fr=1;
	to=3;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	fr=1;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	_write(fh,a,strlen(a));
	fr=2;
	to=3;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	fr=2;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcat_s(a,temp);
	fr=3;
	to=4;
	sprintf_s(temp,"%d %d 1\n",fr,to);
	strcpy_s(a,temp);
	_write(fh,a,strlen(a));
	for(j=0;j<(m_swirl_nodes-4)/4;j++)
	{	
		fr=5+j*4;
		to=5+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
	    fr=5+j*4;
		to=5+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
	    fr=6+j*4;
		to=6+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
	    fr=6+j*4;
		to=6+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
	    fr=6+j*4;
		to=6+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=7+j*4;
		to=7+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		fr=7+j*4;
		to=7+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		fr=7+j*4;
		to=7+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
		fr=8+j*4;
		to=8+j*4-7;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcpy_s(a,temp);
		fr=8+j*4;
		to=8+j*4-4;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		fr=8+j*4;
		to=8+j*4-3;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		fr=8+j*4;
		to=8+j*4-1;
		sprintf_s(temp,"%d %d 1\n",fr,to);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
	}
	_close(fh);
	return 0;
}

int DeterminTSSFSWNetworkGenerate(char *filename,long int m_nodes)
{
	char a[768];
	double section;
	char temp[768];
	if(m_nodes<1) return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network Determin TSSFSW\n");
	_write(fh,a,strlen(a));
	sprintf_s(temp," %d\n",m_nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)m_nodes;
	for(int i=0;i<m_nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
	strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
	//special conditions
	if(m_nodes == 1)
	{
		_close(fh);
		return 0;
	}
	else if(m_nodes == 2)
	{
		sprintf_s(temp,"1 2 1\n");
	    strcpy_s(a,temp);	
	    _write(fh,a,strlen(a));
		return 0;
	}
	sprintf_s(temp,"1 2 1\n");
	strcpy_s(a,temp);	
	sprintf_s(temp,"1 3 1\n");
	strcat_s(a,temp);	
	sprintf_s(temp,"2 3 1\n");
	strcat_s(a,temp);	
	_write(fh,a,strlen(a));
	if(m_nodes == 3)
	{
		_close(fh);
		return 0;
	}
   //begin to normal procedure
   queue<pair<size_t, vector<size_t>> > leaf_queue;//pair<self, ancestor>
   leaf_queue.push(make_pair(1, vector<size_t>(1)));
   leaf_queue.push(make_pair(2, vector<size_t>(1)));
   //construct node in breadth-first order
   size_t records = 0;
   int current_number = 3;
   while(current_number < m_nodes)
   {
      auto current = leaf_queue.front();
      leaf_queue.pop();
      //left node
      size_t left = current_number++;
	  sprintf_s(temp,"%d %d 1\n",current.first+1,left+1);
	  strcpy_s(a,temp);
	  //add ancestor
	  sprintf_s(temp,"%d %d 1\n",left+1,current.second[records % current.second.size()] + 1);
	  strcat_s(a,temp);
	  _write(fh,a,strlen(a));
      //right node
      size_t right = 0;
      if(current_number != m_nodes)
      {
		right = current_number++;
		sprintf_s(temp,"%d %d 1\n",current.first+1,right+1);
		strcpy_s(a,temp);
	    sprintf_s(temp,"%d %d 1\n",left+1,right+1);
		strcat_s(a,temp);
	    //add ancestor
		sprintf_s(temp,"%d %d 1\n",right+1,current.second[records++ % current.second.size()]+1);
		strcat_s(a,temp);
		_write(fh,a,strlen(a));
      }
      if(current.second.size() != leaf_queue.front().second.size())
      {//the next node is in a new level
		records = 0;
      }
      //add ancestor list
      vector<size_t> temp(current.second.begin(), current.second.end());
      temp.push_back(current.first);
      leaf_queue.push(make_pair(left, temp));
      leaf_queue.push(make_pair(right, temp));
   }
	_close(fh);
	return 0;
}

//IEICE paper李新峰算法
int TriangleExtendedDSWNGenerate(char *filename, long int m_iterations)
{
    long int i;
    long int nodes;
    char a[768];
    double section;
    char temp[768];
    if(m_iterations<1||m_iterations>1000)return -1;
	int fh;
	_sopen_s(&fh,filename,_O_CREAT|_O_TEXT|_O_TRUNC|_O_WRONLY,_SH_DENYNO,_S_IREAD|_S_IWRITE);
	if(fh==-1)return -3;
	strcpy_s(a,"*Network TriangleExtended DSWN\n");
    _write(fh,a,strlen(a));
    nodes=(long int)(pow(2.0,m_iterations)*6-3);
    sprintf_s(temp," %d\n",nodes);
	strcpy_s(a,"*Vertices");
	strcat_s(a,temp);
	_write(fh,a,strlen(a));
	section = 2 * 3.14159 / (double)nodes;
	for(i=0;i<nodes;i++)
	{
	  sprintf_s(temp,"%d %d %f %f %f\n",
		  i+1,i+1,
		  0.5  - 0.4*cos(i * section), 
		  0.5  - 0.4*sin(i * section),0.5);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
	}
    strcpy_s(a,"*Edges\n");
	_write(fh,a,strlen(a));
    list<size_t> new_nodes;  //当前步新加入的节点
    list<size_t> previous_new_nodes; //上一步迭代新加入的节点
    size_t node_count=3;
    //time 0
    for(size_t i = 0; i < 3; i++)
    {
	  sprintf_s(temp,"%d %d 1\n",i+1,(i+1)% 3 + 1);
	  strcpy_s(a,temp);
	  _write(fh,a,strlen(a));
      new_nodes.push_back(i+1);
     }
    //add
    for(int i=0;i < m_iterations;i++)
    {
        previous_new_nodes.clear();
        swap(previous_new_nodes,new_nodes);
        for(auto node = previous_new_nodes.begin();
            node != previous_new_nodes.end();node++)
        {
            size_t leftnode = (*node) * 2 + 2;
            size_t rightnode = leftnode + 1;

            //triangle(node, leftnode, rightnode)
            sprintf_s(temp,"%d %d 1\n",*node,leftnode);
            strcpy_s(a,temp);
	        sprintf_s(temp,"%d %d 1\n",*node,rightnode);
            strcat_s(a,temp);
			sprintf_s(temp,"%d %d 1\n",leftnode,rightnode);
            strcat_s(a,temp);
			_write(fh,a,strlen(a));
            new_nodes.push_back(leftnode);
            new_nodes.push_back(rightnode);
        }
    }
    _close(fh);
	return 0;
}

void CalculateNodesCentralityCloseness(NETWORK *ntwk,double *feature)
{
   int i,j;	
   for(j = 0;j <ntwk->NodeNumber;j++)
   {
	   feature[j]=0.0;
   }
   for(i=0;i<ntwk->NodeNumber;i++)
   {
	   for(j=0;j<ntwk->NodeNumber;j++)
	   {
		   if(j!=i)
		   {
			feature[i]+=ComputeDistance(*ntwk,i+1,j+1);
		   }
	   }
	  
   }
   for(int i=0;i<ntwk->NodeNumber;i++)
   {
      feature[i]=(double)(ntwk->NodeNumber-1)/feature[i];
   }   
   
}

void CalculateNodesCentralityAppEigenvector(NETWORK *ntwk,double *feature,double *temp)
{
	CalculateNetworkAverageDistanceAndDiameter(ntwk);
	multimap <long int,Edge>::iterator iter;
	
	for(int j = 0;j < ntwk->NodeNumber;j++)
   {
	   feature[j]=1.0;	   
   }
	for(int k = 0;k <ntwk->Diameter;k++)
   {
	   double sum=0.0;
	   for(int j = 0;j < ntwk->NodeNumber;j++)
	   {
		   temp[j]=0.0;
	   }
	   for(int i = 0;i < ntwk->NodeNumber;i++)
	   {  
			for(iter=ntwk->Net[i].Edges.begin();iter!=ntwk->Net[i].Edges.end();iter++)
			{
			  temp[i]+= feature[iter->first];
			}
			sum+= temp[i];
	   }
	   for(int j = 0;j < ntwk->NodeNumber;j++)
	   {
		   feature[j]=temp[j]/sum;
	   }
   }	

}
void CalculateNodesCentralityAppFlowBetweenness(NETWORK *ntwk,double *feature,double *temp)
{
	CalculateNetworkAverageDistanceAndDiameter(ntwk);
	multimap <long int,Edge>::iterator iter;
	
	for(int i = 0;i < ntwk->NodeNumber;i++)
	{ 
			  for(int init_num = 0;init_num < ntwk->NodeNumber;init_num++)
			   {
				   feature[init_num]=0.0;
				   if(init_num!=i)
				   {
				     temp[init_num]=1.0;
				   }
				   else
				   {
				     temp[init_num]=0.0;
				   }	
			   }
		
			  for(int k = 0;k < ntwk->Diameter;k++)
			   {
					for(int j = 0;j < ntwk->NodeNumber;j++)
				   {
					   for(iter=ntwk->Net[j].Edges.begin();iter!=ntwk->Net[j].Edges.end();iter++)
						{
							if(j == i)
							{
							  feature[j] += temp[iter->first]/ntwk->Net[iter->first].Degree;
							}							
							else
							{
								if(iter->first!=i)
								{
									feature[j] += temp[iter->first]/ntwk->Net[iter->first].Degree;						
								}
							}
							
						}

					}
					for(int j = 0;j < ntwk->NodeNumber;j++)
				   {
					   temp[j]=feature[j];
					   if(j!=i)
					   {						   
						  feature[j]=0;

					   }					  	
				   }
					
			   }
			  
	}
}

void CalculateNodesCentralityNomination(NETWORK *ntwk,double *feature,double *temp,double*temp1)
{
	//ComputeAverageDistance();
	multimap <long int,Edge>::iterator iter;
	bool IterContinue=true;
	for(int j = 0;j < ntwk->NodeNumber;j++)
    {
	   feature[j]=1.0;   
    }
	while(IterContinue)
    {
	   for(int j = 0;j < ntwk->NodeNumber;j++)
	   {
		   temp1[j]=feature[j];
		   temp[j]=feature[j];
	   }	  
	   double sum=0.0;
	   
	   for(int i = 0;i < ntwk->NodeNumber;i++)
	   {  
			for(iter=ntwk->Net[i].Edges.begin();iter!=ntwk->Net[i].Edges.end();iter++)
			{
				temp[i]+= feature[iter->first];
			}
			sum+= temp[i];
	   }
	   for(int j = 0;j < ntwk->NodeNumber;j++)
	   {
		   feature[j]=temp[j]/sum;
	   }
	   for(int j = 0;j < ntwk->NodeNumber;j++)
	   { 
		   int testa=(int)(1000000000*feature[j]);
		   int testb=(int)(1000000000*temp1[j]);
		   if(testa!=testb)
		   { 
		    IterContinue=true;break;			
		   }
		   else
		   {
		    IterContinue=false;
		   }
	   }
   }
	for(int j = 0;j < ntwk->NodeNumber;j++)
   {
	   feature[j]=ntwk->NodeNumber*temp[j];   
   }
	
}

int CalculateNetworkCommunityKernighanLin(NETWORK ntwk,int numone,int numtwo,int *comlist)
{
	if( (numone+numtwo) != ntwk.NodeNumber )
	{
		return -1;
	}
	for(int j = 0;j < ntwk.NodeNumber;j++)
	{
		comlist[j]=0;   
	}

	set<int> QCommuA;											//Analyzing classification of Community One
	set<int> QCommuB;											//Analyzing classification of Community Two
	set<int> FinalQCommuA;										//Final classification of Community One
	set<int> FinalQCommuB;										//Final classification of Community Two
	set<int>::iterator itA;										//iterator of Community One 
	set<int>::iterator itB;										//iterator of Community Two
	int exchangednumA = 0 , exchangednumB = 0 , Q = 0 ,MaxQ = 0;//Had exchanged times of two Community, paramete Q, mark of the max Q to give the final result
	multimap <long int,Edge>::iterator iternetwork;				//iterator of the network
	set<int> changednodes;										//mark set for the exchanged nodes
	
	for(int j =0;j < ntwk.NodeNumber;j++) //init set
	{		
		if(j < numone)
		{
			QCommuA.insert(j);			
		}
		else 
		{
			QCommuB.insert(j);			
		}
	}								//init set
	
	
	while(exchangednumA < numone && exchangednumB < numtwo)
	{
 		int tempQ = 0,resulttempQ= -((ntwk.NodeNumber * ntwk.NodeNumber) / 2);
		int chagednodeA , chagednodeB; 
		
		for(itA = QCommuA.begin();itA != QCommuA.end();itA++)			
		{
			for(itB = QCommuB.begin();itB != QCommuB.end();itB++)
			{
				int tempQinside = 0,tempQoutside = 0;
				if(changednodes.count(*itA) || changednodes.count(*itB))
				{
				}
				else
				{
					for(int i =0;i < ntwk.NodeNumber;i++)
					{
							for(iternetwork=ntwk.Net[i].Edges.begin();iternetwork!=ntwk.Net[i].Edges.end();iternetwork++)
							{
 								if(iternetwork->first != (iternetwork->second.Tail-1) )
								{
									if(iternetwork->first != *itA && iternetwork->first != *itB && iternetwork->second.Tail-1 != *itA && iternetwork->second.Tail-1 != *itB)
									{
										if( (QCommuA.find(iternetwork->first)!=QCommuA.end() && QCommuA.find(iternetwork->second.Tail-1)!=QCommuA.end()) || ( QCommuB.find(iternetwork->first)!=QCommuB.end() && QCommuB.find(iternetwork->second.Tail-1)!=QCommuB.end() ) )
											{
												tempQinside += 1;							  
											}
											else
											{
												tempQoutside += 1;	
											}	
							 		}
									else if((iternetwork->first == *itA && iternetwork->second.Tail-1 == *itB) || (iternetwork->first == *itB && iternetwork->second.Tail-1 == *itA))
									{
										tempQoutside += 1;
									}
									else
									{
										if( (QCommuA.find(iternetwork->first)!=QCommuA.end() && QCommuB.find(iternetwork->second.Tail-1)!=QCommuB.end() ) || ( QCommuB.find(iternetwork->first)!=QCommuB.end() && QCommuA.find(iternetwork->second.Tail-1)!=QCommuA.end() ))
											{
											tempQinside += 1;							  
											}
											else
											{
											tempQoutside += 1;	
											}						
									}
								}
 							}
					}				
					tempQ=tempQinside - tempQoutside;					
					if((tempQ-Q) > resulttempQ)
					{
						resulttempQ = tempQ - Q;
						chagednodeA = *itA;
						chagednodeB = *itB;
					}
					
			  }

			}	
		}
			if(changednodes.count(chagednodeA) || changednodes.count(chagednodeB))
			{
				
			}
			else
			{ 
				
				QCommuA.erase(chagednodeA);		
				QCommuA.insert(chagednodeB);			
				QCommuB.erase(chagednodeB);		
				QCommuB.insert(chagednodeA);			
				changednodes.insert(chagednodeA);			
				changednodes.insert(chagednodeB);	
				
				Q=resulttempQ+Q;
				
				if( Q >= MaxQ)
				{
					MaxQ=Q;
					FinalQCommuA=QCommuA;
					FinalQCommuB=QCommuB;				
				}
				exchangednumA+=1;
				exchangednumB+=1;				
			  }
	}

	for(itA = FinalQCommuA.begin();itA != FinalQCommuA.end();itA++)	 //result set
	{
		int numnow = *itA;
		comlist[numnow] = 1;
	}
	for(itB = FinalQCommuB.begin();itB !=FinalQCommuB.end();itB++)
	{
		int numnow = *itB;
		comlist[numnow] = 0;
	}																//result set
	return 0;
}


vector<size_t> FindClosureGroupA(NETWORK ntwk,unordered_map<size_t, Node> graph, size_t indexOfSeed, size_t length)
{
   unordered_set<size_t> list;
   list.insert(indexOfSeed);
   //breadth-first search to find adjacent nodes
   queue<size_t> search_queue;
   unordered_set<size_t> in_queue;
   //init
   search_queue.push(indexOfSeed);
   in_queue.insert(indexOfSeed);
   //begin
   size_t front;
   while(!search_queue.empty())
   {
      front = search_queue.front();
      search_queue.pop();
      in_queue.erase(front);
	  auto& edge = graph[front].Edges;
      for(auto other = edge.begin(); other != edge.end(); other++)
      {
		  if(in_queue.find(other->first) != in_queue.end())
			continue;
		  if(list.find(other->first) != list.end())
			continue;
		  if(all_of(list.begin(), list.end(), [&](size_t i)->bool
		  {
			  if(GetShortestDistanceA(ntwk,i, other->first) < length)
				return true;
		     else
				return false;
		   }))
	 {
		 search_queue.push(other->first);
		 in_queue.insert(other->first);
		 list.insert(other->first);
	 }
      }
   }
   return vector<size_t>(list.begin(), list.end());
}

void RenormalizeByBoxCountingA(NETWORK *ntwk,size_t length)
{
   unordered_map<size_t, size_t> group_index;//stores the index of group of each
			   //previous nodes. pairs(index in graph,
			   //index of group)
   size_t numberOfGroups = 0;
   unordered_map<size_t, Node> temp_graph;
   //copy
   for(size_t i = 0; i < ntwk->Net.size(); i++)
   {
	   temp_graph[i] = ntwk->Net[i];
   }

   while(!temp_graph.empty())
   {
	   auto list = FindClosureGroupA(*ntwk,temp_graph, temp_graph.begin()->first, length);
      for(auto i = list.begin(); i != list.end(); i++)
      {
		//add to group_index
		group_index[*i] = numberOfGroups;
		//remove from temp_graph
		temp_graph.erase(*i);
      }
      numberOfGroups++;
   }
   //add node
   for(size_t i = 0; i < numberOfGroups; i++)
   {
	   temp_graph[i] = Node();
   }
   //add edge
   for(auto i = group_index.begin(); i != group_index.end();i++)
   {
	   auto& node = ntwk->Net[i->first].Edges;
      for(auto j = i; j != group_index.end(); j++)
      {
		 if(i->second != j->second && node.find(j->first) != node.end())
		{
			auto& test = temp_graph[i->second].Edges;
			if(test.find(j->second) == test.end())
			{
				temp_graph[i->second].Edges.insert(make_pair(j->second, Edge(i->second + 1, j->second + 1)));
				temp_graph[i->second].Edges.insert(make_pair(i->second, Edge(i->second + 1, j->second + 1)));
			}
		}	
      }
   } 
   //add coordinate
   vector<pair<double, double>> coordinate(numberOfGroups, make_pair(0,0));
   vector<int> count(numberOfGroups, 0);
   for(auto iter = group_index.begin(); iter != group_index.end(); iter++)
   {
	   coordinate[iter->second].first += ntwk->Net[iter->first].X;
	   coordinate[iter->second].second += ntwk->Net[iter->first].Y;
	   count[iter->second]++;
   }
   for(int i = 0; i < (int)coordinate.size(); i++)
   {
	   coordinate[i].first /= count[i];
	   coordinate[i].second /= count[i];
   }
   //copy
   ntwk->Net.assign(numberOfGroups, Node());
   for(auto iter = temp_graph.begin(); iter != temp_graph.end(); iter++)
   {
	   auto& node = ntwk->Net[iter->first];
	   node = iter->second;
	   node.X = coordinate[iter->first].first;
	   node.Y = coordinate[iter->first].second;
	   node.NodeNo = iter->first + 1;
   }
   ntwk->NodeNumber = numberOfGroups;
   ntwk->LinkNumber = 0;
   for(int i = 0; i<(int)ntwk->Net.size(); i++)
		ntwk->LinkNumber +=ntwk->Net[i].Edges.size();
	ntwk->LinkNumber/=2;
}

void CalculateHistogramDouble(double *input,double *output,long int len,long int bins,double min,double max)
{
   LONG i;
   long j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(long)((input[i]-min)*(double)(bins-1)/(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
}

void CalculateHistogramLongint(long *input,double *output,long int len,long int bins,long int min,long int max)
{
   LONG i;
   long j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(long)((double)(input[i]-min)*(double)(bins-1)/(double)(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
}
void CalculateHistogramInt(WORD *input,double *output,int len,int bins,WORD min,WORD max)
{
   LONG i;
   WORD j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(WORD)((double)(input[i]-min)*(double)(bins-1)/(double)(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
}

void CalculateHistogramChar(BYTE *input,double *output,int len,int bins,BYTE min,BYTE max)
{
   LONG i;
   WORD j;
   //set the histogram array to be zero
   for(j=0;j<bins;j++)output[j]=0.0;
   if(bins==1)
   {
	 output[0]=1.0;
	 return;
   }
   else
   {
     //get the histogram 
     for(i=0;i<len;i++)
	 {
	   j=(WORD)((double)(input[i]-min)*(double)(bins-1)/(double)(max-min)+0.5);
	   //let the k be not larger than bins-1
	   if(j>=bins-1)j=bins-1;
	   output[j]=output[j]+1.0;
	 }
   }
   for(i=0;i<bins;i++)
     output[i]/=(double)len;
}
