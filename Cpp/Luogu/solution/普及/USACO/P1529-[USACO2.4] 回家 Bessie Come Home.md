# [USACO2.4] 回家 Bessie Come Home

## 题目描述

现在是晚餐时间，而母牛们在外面分散的牧场中。 

Farmer John 按响了电铃，所以她们开始向谷仓走去。 你的工作是要指出哪只母牛会最先到达谷仓（在给出的测试数据中，总会**有且只有**一只最快的母牛）。在挤奶的时候（晚餐前），每只母牛都在她自己的牧场上，一些牧场上可能没有母牛。

每个牧场由一条条道路和一个或多个牧场连接（可能包括自己）。有时，两个牧场（可能是字母相同的）之间会有超过一条道路相连。至少有一个牧场和谷仓之间有道路连接。因此，所有的母牛最后都能到达谷仓，并且母牛总是走最短的路径。当然，母牛能向着任意一方向前进，并且她们以相同的速度前进。牧场被标记为 $\texttt{a} \ldots \texttt{z}$ 和 $\texttt{A} \ldots \texttt{Y}$，在用大写字母表示的牧场中有一只母牛，小写字母中则没有。 谷仓的标记是 $\texttt{Z}$，注意没有母牛在谷仓中。

**注意 $\texttt{m}$ 和 $\texttt{M}$ 不是同一个牧场**。

## 说明/提示

翻译来自 NOCOW

USACO 2.4


## 样例 #1

### 输入

```
5
A d 6
B d 3
C e 9
d Z 8
e Z 3```

### 输出

```
B 11
```

# 题解

## 作者：封禁用户 (赞：26)

这一题看见大家用dijkstra,spfa，不禁感慨，这年头都不看数据范围吗？最多52个点

flyod稳过呀，见丑陋代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1<<30;
int dist[60][60];
int getnum(char c){
	if(c>='a'&&c<='z')return c-'a'+26;
	else return c-'A';
}
int main(){
	for(int i=0;i<60;i++)for(int j=0;j<60;j++)dist[i][j]=inf-1;
	int m;
	cin>>m;
	while(m--){
		string s1,s2;int d;
		cin>>s1>>s2>>d;
		//cout<<getnum(s1[0])<<" "<<getnum(s2[0])<<" "<<d<<endl;
		dist[getnum(s1[0])][getnum(s2[0])]=min(dist[getnum(s1[0])][getnum(s2[0])],d);
		dist[getnum(s2[0])][getnum(s1[0])]=min(dist[getnum(s2[0])][getnum(s1[0])],d);
		//cout<<getnum(s1[0])<<" "<<getnum(s2[0])<<" "<<d<<" "<<dist[getnum(s1[0])][getnum(s2[0])]<<endl;
	}
	for(int k=0;k<60;k++)for(int i=0;i<60;i++)for(int j=0;j<60;j++)if(dist[i][k]+dist[k][j]<dist[i][j])dist[i][j]=dist[i][k]+dist[k][j];
	char ansc;int ans=inf;
	for(int i=0;i<25;i++)if(dist[i][25]<=ans){
		ans=dist[i][25];ansc=i+'A';
	}
	cout<<ansc<<" "<<ans<<endl;
	return 0;
}

```

---

## 作者：Gamin (赞：23)

**本人菜鸡第一次发题解，不好请见谅**   
**~~反正也快要退役了~~**   
大佬的题解看不懂就只好自己写了……

**废话不多说了
**

------------
先说存图吧，~~存图当时我一点灵感没有~~看了下数据，邻接矩阵可以，就直接邻接矩阵了。
至于a~z和A~Z的存图，我借鉴了一下楼上大佬orz

“这题把Z（谷仓）当起点，把有牛的牧场当终点求最短路就行了。

有人会问，牧场是用字母表示的啊，怎么转成数字呢？

a~z -> 1~26

A~Z -> 27~52”————出自大佬 ZimoCP 

存图完了以后，就是找单源最短路了（这里我用 _**Dijkstra 算法**_  ）
（如果还不知道Dijkstra 算法的朋友们可以百度一下，比较简单）

从Z点出发，寻找离Z点最近的大写字母的编号~~（之前没注意看题然后就一直……）~~

还有一个小细节，就是这道题还重复输入两个点之间不同长度的边，注意要用较小的边去替换较大的边就好了。。
~~之前没注意看然后居然89分~~

下面贴AC代码：
```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 99999999
using namespace std;
int dis[100],tu[100][100];//从z出发的dis值和邻接矩阵
int p,vis[100];//道路数目、节点标记
char r;
void di(int x,int y,int w)//存图
{
	
    if(tu[x][y]==0)//读入边
    
	{
		tu[x][y]=w;
		tu[y][x]=w;
        
	}
	if(w<tu[x][y])//读入的第二条边比第一条边的权值小，就替换
	{
		tu[x][y]=w; 
		tu[y][x]=w;
	}
} 
void dj()//迪杰斯特拉裸代码（好像是啊哈算法上面的？？）
{

	int u,min;
    
	for(int i=1;i<=51;i++)
	{
		min=MAXN;
		for(int j=1;j<=51;j++)
		{
			if(vis[j]==0&&dis[j]<min)
			{
				min=dis[j];
				u=j;
			}
		}
		vis[u]=1;
		for(int v=1;v<=51;v++)
		{
			if(dis[v]>dis[u]+tu[u][v]&&vis[v]==0&&tu[u][v]<MAXN)
			dis[v]=dis[u]+tu[u][v];
		}
	}
}
int main()
{

	scanf("%d",&p);
    
	for(int i=1;i<=52;i++)
		for(int j=1;j<=51;j++)
			tu[i][j]=MAXN;
	vis[52]=1;//因为'Z'存图的时候是52，所以打上标记
	for(int i=1;i<=p;i++)//借鉴楼上的读入
	{
		char x,y;//两个点
		int c;//权值
		int xx,yy;
		scanf("\n%c %c %d",&x,&y,&c);
		if(x>='a'&&x<='z') xx=x-'a'+1;
		else xx=x-'A'+27;
		if(y>='a'&&y<='z') yy=y-'a'+1;
		else yy=y-'A'+27;
		di(xx,yy,c);
	}
	for(int i=1;i<=51;i++)
	dis[i]=tu[52][i];
	dj();int hh=MAXN,point;
	for(int i=1;i<=51;i++)//判断大写并输出
	{
		if(dis[i]<hh&&i>=27)
		{
			hh=dis[i];
			point =i;
		}
	}
	r=point-27+'A';
	printf("%c %d\n",r,hh);
} 
```

   

---

## 作者：Obito (赞：13)

## 没人用堆优化的dijkstra做，那位偶就来一发

### 有篇题解是说经典Dijkstra，不用_邻接表（邻接矩阵）_，不用_堆优化_，照样0ms；

## 那我就来一个dijkstra+邻接表+堆优化

### 首先你先得会这些

- # dijkstra（必须会）

### 其次就是优化，我在此采用的是

- ## 邻接表+优先队列

## 先看一下邻接表

```
void add(int x,int y,int u){//加入一条从x到y的单向边，长度为U
	++cnt;
	to[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt;
	w[cnt]=u;	
	}
```

## 接下来上代码（具体解释在其中）

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000+10;
const int INF=0x7ffffff;
int cnt,first[maxn],next[maxn],m,to[maxn],w[maxn],pre[maxn],dis[maxn];
priority_queue<pair<int,int> >q;//大根堆（优先队列），第一维表示dis的相反数，第二维表示结点的编号
void add(int x,int y,int u){
	++cnt;
	to[cnt]=y;
	next[cnt]=first[x];
	first[x]=cnt;
	w[cnt]=u;	
	}
void dijkstra(int s){
    for(int i=0;i<=150;i++)//把每个的距离置成无穷大
    dis[i]=INF;
    memset(pre,0,sizeof(pre));//结点标记
    dis[s]=0;//点到自己的距离为0
    q.push(make_pair(0,s));
    while(q.size()){
        int x=q.top().second;//取出堆顶
        q.pop();//弹出
        if(pre[x])continue;//标记
        else pre[x]=1;
        for(int i=first[x];i;i=next[i]){//扫描所有边
        int y=to[i];
        if(dis[y]>dis[x]+w[i]){//松弛操作
            dis[y]=dis[x]+w[i];
            q.push(make_pair(-dis[y],y));//元素插入堆
                }
            }
        }   
    }   
int main(){
	int m,s;
	cin>>m;
	for(int i=1;i<=m;i++){
	char x,y;
	int z;
	cin>>x>>y>>z;
	add((int)x,(int)y,z);//强制转换一下
	add((int)y,(int)x,z);	
	}
	dijkstra((int)'Z');
	char ans='A';
	for(int i='B';i<='Y';i++)//差不多也是在强制转换
	if(dis[(int)i]<dis[(int)ans])ans=i;
	cout<<ans<<" "<<dis[(int)ans];
	return 0;//完结散花
	}
```

## 实际上就是模板改一点点

## 感谢管理员百忙之中抽出空来审核，不足之处欢迎斧正

---

## 作者：「QQ红包」 (赞：11)

这道题Floyd就可以AC

```cpp


#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm>  
using namespace std; 
int a[200][200]={0};
int p[200]={0};
int n,i,j,k;
char A,B;
int main()
{
    scanf("%d\n",&n); 
    for (i='A';i<='z';i++)
        for (j='A';j<='z';j++)
        if(i!=j)a[i][j]=100000000;
    for (i=1;i<=n;i++)
    {
        int haha;
        scanf("%c %c %d\n",&A,&B,&haha);
        if (A>='A'&&A<='Z') p[A]=1;//标记该地有牛 
        if (B>='A'&&B<='Z') p[B]=1;
        a[A][B]= min(a[A][B],haha);
        a[B][A]=min(a[A][B],a[B][A]);
    } 
    for (k='A';k<='z';k++)//floyd
        for (i='A';i<='z';i++)
            for (j='A';j<='z';j++)
            if(a[i][j]>a[i][k]+a[k][j])
            a[i][j]= a[i][k]+a[k][j];
    int m=100000000;
    char he;
    for (i='A';i<='Y';i++)//找最快到Z的母牛
        if ((p[i]==1)&&(a[i]['Z']<m))
        {
            m=a[i]['Z'];
            he=(char)i;
        }
    cout<<he<<" "<<m;
    return 0;
} 


```

---

## 作者：KenLi (赞：10)

**这是本人第一次做题解，做得不好勿喷**

~~话说这个做题解的网页我还不怎么会用qwq~~

整体思路思路:

为每个牧场编号

邻接矩阵存图

朴素版 _Dijkstra_ 

------------

####  _Dijkstra_的原理和演示：

原文地址:https://blog.csdn.net/qq_35644234/article/details/60870719 

作者:Ouyang_Lianjun

##### 算法介绍

###### 算法特点：

迪科斯彻算法使用了广度优先搜索解决赋权有向图或者无向图的单源最短路径问题，算法最终得到一个最短路径树。该算法常用于路由算法或者作为其他图算法的一个子模块。

###### 算法思路:

Dijkstra算法采用的是一种贪心的策略，声明一个数组dis来保存源点到各个顶点的最短距离和一个保存已经找到了最短路径的顶点的集合：T，初始时，原点 s 的路径权重被赋为 0 （dis[s] = 0）。若对于顶点 s 存在能直接到达的边（s,m），则把dis[m]设为w（s, m）,同时把所有其他（s不能直接到达的）顶点的路径长度设为无穷大。初始时，集合T只有顶点s。 
然后，从dis数组选择最小值，则该值就是源点s到该值对应的顶点的最短路径，并且把该点加入到T中，OK，此时完成一个顶点， 
然后，我们需要看看新加入的顶点是否可以到达其他顶点并且看看通过该顶点到达其他点的路径长度是否比源点直接到达短，如果是，那么就替换这些顶点在dis中的值。 
然后，又从dis中找出最小值，重复上述动作，直到T中包含了图的所有顶点。

##### 算法演示:

求下图，从顶点v1到其他各个顶点的最短路径

![](https://img-blog.csdn.net/20170308144724663?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

首先第一步，我们先声明一个dis数组，该数组初始化的值为： 


![](https://img-blog.csdn.net/20170308150247263?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

我们的顶点集T的初始化为：T={v1}

既然是求 v1顶点到其余各个顶点的最短路程，那就先找一个离 1 号顶点最近的顶点。通过数组 dis 可知当前离v1顶点最近是 v3顶点。当选择了 2 号顶点后，dis[2]（下标从0开始）的值就已经从“估计值”变为了“确定值”，即 v1顶点到 v3顶点的最短路程就是当前 dis[2]值。将V3加入到T中。 
为什么呢？因为目前离 v1顶点最近的是 v3顶点，并且这个图所有的边都是正数，那么肯定不可能通过第三个顶点中转，使得 v1顶点到 v3顶点的路程进一步缩短了。因为 v1顶点到其它顶点的路程肯定没有 v1到 v3顶点短.

OK，既然确定了一个顶点的最短路径，下面我们就要根据这个新入的顶点V3会有出度，发现以v3 为弧尾的有： < v3,v4 >,那么我们看看路径：v1–v3–v4的长度是否比v1–v4短，其实这个已经是很明显的了，因为dis[3]代表的就是v1–v4的长度为无穷大，而v1–v3–v4的长度为：10+50=60，所以更新dis[3]的值,得到如下结果：

![](https://img-blog.csdn.net/20170308150707766?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

因此 dis[3]要更新为 60。这个过程有个专业术语叫做“松弛”。即 v1顶点到 v4顶点的路程即 dis[3]，通过 < v3,v4> 这条边松弛成功。这便是 Dijkstra 算法的主要思想：通过“边”来松弛v1顶点到其余各个顶点的路程。

然后，我们又从除dis[2]和dis[0]外的其他值中寻找最小值，发现dis[4]的值最小，通过之前是解释的原理，可以知道v1到v5的最短距离就是dis[4]的值，然后，我们把v5加入到集合T中，然后，考虑v5的出度是否会影响我们的数组dis的值，v5有两条出度：< v5,v4>和 < v5,v6>,然后我们发现：v1–v5–v4的长度为：50，而dis[3]的值为60，所以我们要更新dis[3]的值.另外，v1-v5-v6的长度为：90，而dis[5]为100，所以我们需要更新dis[5]的值。更新后的dis数组如下图：

![](https://img-blog.csdn.net/20171205193212203?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

然后，继续从dis中选择未确定的顶点的值中选择一个最小的值，发现dis[3]的值是最小的，所以把v4加入到集合T中，此时集合T={v1,v3,v5,v4},然后，考虑v4的出度是否会影响我们的数组dis的值，v4有一条出度：< v4,v6>,然后我们发现：v1–v5–v4–v6的长度为：60，而dis[5]的值为90，所以我们要更新dis[5]的值，更新后的dis数组如下图：

![](https://img-blog.csdn.net/20170308151732132?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

然后，我们使用同样原理，分别确定了v6和v2的最短路径，最后dis的数组的值如下： 

![](https://img-blog.csdn.net/20170308152038851?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMzU2NDQyMzQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

------------

上代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
#define INF 0x7fffffff//定义正无穷 
using namespace std;
/*变量(数组)的意义: 
以下变量为处理字符用
ind[i]:字母i(ASCII码)的编号,做下标用
ch[i]:编号为i牧场的字母,与ind[]相对 
used[i]:字母i(ASCII码)是否出现过
len:牧场的数量 
以下变量为跑dijkstra时用 
mat[i][j]:存储图用的邻接矩阵,mat[i][j]为点i到点j的权值
dis[i]:谷仓到点i的最短路径
vis[i]:记录原点到点i的路径是否为最短 
*/ 
int n,mat[64][64],ind[128],dis[64],len;
bool used[128],vis[64];
char ch[64];
int main(){
	for(int i=0;i<64;++i){
		for(int j=0;j<64;++j){
			mat[i][j]=INF;
		}
		dis[i]=INF;
	}//全部初始化为正无穷 
	ind[(int)'Z']=++len;
	dis[1]=0;
	vis[1]=true;
	cin>>n;
	for(int i=1;i<=n;++i){
		char from,to;
		int val;
		cin>>from>>to>>val;
		if(from==to){
			continue;
		}
		if(!used[(int)from]){//如果该字母没有出现过 
			used[(int)from]=true;//标记 
			ind[(int)from]=++len;//为该牧场编号 
		}
		if(!used[(int)to]){//同上 
			used[(int)to]=true;
			ind[(int)to]=++len;
		}
		if(from=='Z'){//如果这条路连接了谷仓 
			dis[ind[(int)to]]=min(dis[ind[(int)to]],val);//记录权值 
		}
		if(to=='Z'){//同上 
			dis[ind[(int)from]]=min(dis[ind[(int)from]],val);
		}
		//邻接矩阵存图 
		mat[ind[(int)from]][ind[(int)to]]=min(mat[ind[(int)from]][ind[(int)to]],val);
		mat[ind[(int)to]][ind[(int)from]]=min(mat[ind[(int)to]][ind[(int)from]],val);
		//因为本题为无向图,所以以上记录操作要做两次 
	}
	//朴素版Dijkstra,时间复杂度为O(len^2) 
	for(int i=1;i<=len;++i){
		int node=1,min_dis=INF;
		for(int j=1;j<=len;++j){//node:找到一个离谷仓(点Z)最近的牧场 
			if(!vis[j]&&min_dis>dis[j]){
				node=j;
				min_dis=dis[j];
			}
		}
		vis[node]=true;//标记为确定值 
		for(int j=1;j<=len;++j){
			if(mat[node][j]!=INF){//防止以下判断中的int溢出 
				if(dis[node]+mat[node][j]<dis[j]){
					dis[j]=dis[node]+mat[node][j];//松弛操作 
				}
			}
		}
	}
	//离线处理ch数组 
	for(int i=(int)'a';i<=(int)'z';++i){
		if(ind[i]){
			ch[ind[i]]=(char)i;
		}
	}
	for(int i=(int)'A';i<=(int)'Z';++i){
		if(ind[i]){
			ch[ind[i]]=(char)i;
		}
	}
	int min_dis=INF;
	char ans;
	for(int i=2;i<=len;++i){
		if(dis[i]<min_dis&&'A'<=ch[i]&&ch[i]<'Z'){//找到一个离谷仓最近的,编号为大写字母的牧场 
			min_dis=dis[i];
			ans=ch[i];
		}
	}
	cout<<ans<<' '<<min_dis<<endl;//输出 
	return 0;//一个好习惯 
}
```
自认为代码风格很好︿(￣︶￣)︿

---

## 作者：氢氟酸er (赞：10)

**经典Dijkstra**，**不用**\_邻接表（邻接矩阵）\_，**不用**\_堆优化\_，照样**0ms**



```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int road[53][53];//任意两个牧场的路径长度 
bool visit[53];//每个牧场是否被访问过 
const int INF=2e9;
int dis[53];//每一个牧场到起点的距离 
int P,d,k,end,minn=INF,start=26;//起点为谷仓 
char ch1,ch2;
void calcdist(char a,char b,int dist);//把两个牧场转为数字存入数组 
void dijkstra();
int main(){
    //init
    memset(visit,false,sizeof(visit));
    for(k=0;k<53;k++){
        for(int j=0;j<53;j++){
            if(k==j) road[k][j]=0;
            else road[k][j]=INF;
        }
        dis[k]=INF;
    }
    dis[start]=0;
    visit[start]=true;
    //input
    scanf("%d",&P);
    for(k=1;k<=P;k++){
        scanf(" %c %c %d",&ch1,&ch2,&d);
        calcdist(ch1,ch2,d);
    }
    //dijkstra
    dijkstra();
    //output
    printf("%c %d",start-1+'A',dis[start]);
    return 0;
}
void calcdist(char a,char b,int dist){
    int x,y;
    if(a>='a'&&a<='z'){//小写字母存入第27个到第52个 
        x=a-'a'+27;
    }
    else if(a>='A'&&a<='Z'){//大写字母存入第1个到第26个 
        x=a-'A'+1;
    }
    if(b>='a'&&b<='z'){
        y=b-'a'+27;
    }
    else if(b>='A'&&b<='Z'){
        y=b-'A'+1;
    }
    if(dist<road[x][y]){//特判，避免重复输入 
        road[x][y]=dist;
        road[y][x]=dist;
    }
}
void dijkstra(){
    while(start>=26){
        //松弛 
        for(k=1;k<53;k++){
            if(!visit[k]&&road[start][k]!=INF){
                if(dis[k]>dis[start]+road[start][k]){
                    dis[k]=dis[start]+road[start][k];
                }
            }
        }
        minn=INF;
        //找最小值 
        for(k=1;k<53;k++){
            if(!visit[k]&&dis[k]<minn){
                minn=dis[k];
                start=k;
            }
        }
        visit[start]=true;
    }
}

```

---

## 作者：Parabola (赞：6)

```cpp
//楼下是只有一篇c++的dj啊
//主要是一开始做这题没思路，图论算法只会两个
//所以选了dj（只能证明我太L
//然而不知道将谁设为起点，终点。
//翻下面的题解，但是看不懂。。（再次证明我太L
//所以我发一篇蒟蒻的题解，dalao轻喷
//存图也是直接存，也没用堆优化
//仅仅思路。
#include<iostream>
#include<cstdio>
using namespace std;
const int INF=2e9;//无限 
int a[257][257],dis[257],n,minn;//a用来存图，dis[i]是到起点到i点的距离 
char u='Z';//起点，这里把'Z'设为起点。算出起点到所有地方的最短距离 
bool vis[257];//是否确定最短距离 
int main()
{
    for(int i='A';i<='z';i++)
        for(int j='A';j<='z';j++)
            if(i!=j)    a[i][j]=INF;//自己到自己的距离是0 
    for(int i='A';i<='z';i++)
        dis[i]=INF;
    dis['Z']=0;
    vis['Z']=true;
    //上面为初始化 
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        char x,y;int k;
        cin>>x>>y>>k;
        if(a[x][y]>k)    a[x][y]=a[y][x]=k;
```
}//读入
```cpp
    while(true)//这里先用while(true)，理由下面说 
    {
        for(int i=1;i<=257;i++)
        {
            if(!vis[i]&&dis[i]>dis[u]+a[u][i])
                dis[i]=dis[u]+a[u][i];
        }
        minn=INF;
        for(int i='A';i<='z';i++)
        {
            if(!vis[i]&&dis[i]<minn)
            {
                minn=dis[i];
                u=i;
            }
        }
        vis[u]=true;
        //楼上dj模板 
        if(u>='A'&&u<'Z')//我们只要确定了到一个有牛的地方的最短距离（只要是大写字母且不为谷仓就有牛），结束循环 
            break;
    }
    putchar(u);
    cout<<' '<<minn;
    //输出 
    return 0;
}
```
/\*
希望大家能看懂，总体思路就是设谷仓为起点，算到到任意一个有牛的地方的最短距离就停，至于这些字母转ASCII就好了。

求轻喷，谢谢。


---

## 作者：ShineEternal (赞：5)

### 吐槽区：

~~我就想知道能不能仔细看看数据范围啊~~


----
进入正题：
本题显然就是个裸的最短路模板题，适用于**所有**算法。

和其他此类题目不同的是，本题没有直接在输入中给出牧场数的范围，但仔细想想字母，

**大小写加起来一共才56个**

这就意味着可以Floyd

我们可以把读入的字母都转换成1~56，甚至懒一些（比如我），直接把字母的ASCII码搬过来也能$O(n^3)$

> code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int f[505][505];
int main()
{
	int m;
	scanf("%d",&m);
	char c1,c2;
	int z;
	for(int i=1;i<=500;i++)
	{
		for(int j=1;j<=500;j++)
		{
			f[i][j]=1000000000;
		}
	}
	int maxn=0;
	for(int i=1;i<=m;i++)
	{
		cin>>c1>>c2>>z;
		int tmp1=c1,tmp2=c2;
		f[tmp2][tmp1]=f[tmp1][tmp2]=min(f[tmp1][tmp2],z);
		
		maxn=max(maxn,max(tmp1,tmp2));
	}
	for(int k=1;k<=maxn;k++)
	{
		for(int i=1;i<=maxn;i++)
		{
			for(int j=1;j<=maxn;j++)
			{
				//if(j!=i&&j!=k&&i!=j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	char tag;
	int ans=2147483647;
	for(char i='A';i<='Y';i++)
	{
		int j=i;
		if(f[j][90]<ans)
		{
			ans=f[j][90];
			tag=i;
		} 
	}
	printf("%c %d\n",tag,ans);
	return 0;
}
```

撒花~

---

## 作者：Starlight237 (赞：4)

# 堆优化Dijkstra
~~都9102年了，不用堆优化Dij，能跑进30ms都是奇迹。~~

另外由于STL的优先队列太慢了，蒟蒻又不想手写，~~（其实是不会手写堆）~~于是用了奇妙的**内存池优化**：
```cpp
static char space[10000000],*sp=space;
template<typename T>
struct myalloc:allocator<T>{
    myalloc(){}
    template<typename T2>
    myalloc(const myalloc<T2> &a){}
    template<typename T2>
    myalloc<T>& operator=(const myalloc<T2> &a){return *this;}
    template<typename T2>
    struct rebind{typedef myalloc<T2> other;};
    inline T* allocate(size_t n){
        T *result=(T*)sp;sp+=n*sizeof(T);
        return result;
    }
    inline void deallocate(T* p,size_t n){}
};
```
具体怎么处理STL的定义**见代码**

注：
- 坑点1 edges数组要开20001，否则会爆RE。
- 坑点2 priority_queue一定要定义在dij函数里面，否则#7RE（原因不明）。

AC代码如下（29ms，还是太慢了）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
namespace FastIO{
    #define IOSIZE 10000000
    static char out[IOSIZE],*q=out,ch[20],*t=ch;
    inline void write(int x){
        if(!x)*q++=48;
        while(x)*t++=x%10+48,x/=10;
        while(t!=ch)*q++=*--t;
    }
    inline void write(char s[]){for(reg char *i=s;*i!='\0';*q++=*i++);}
    struct Flusher{~Flusher(){fwrite(out,1,q-out,stdout);}}io_flusher;
}using namespace FastIO;
static char space[10000000],*sp=space;
template<typename T>
struct myalloc:allocator<T>{
    myalloc(){}
    template<typename T2>
    myalloc(const myalloc<T2> &a){}
    template<typename T2>
    myalloc<T>& operator=(const myalloc<T2> &a){return *this;}
    template<typename T2>
    struct rebind{typedef myalloc<T2> other;};
    inline T* allocate(size_t n){
        T *result=(T*)sp;sp+=n*sizeof(T);
        return result;
    }
    inline void deallocate(T* p,size_t n){}
};
namespace Dijkstra{
    static int m,head[1001],dis[1001],N;
    struct Node{int v,nxt;double w;}edges[20001];
    struct node{double dis;int to;};
    struct cmp{inline bool operator()(node a,node b){return a.dis>b.dis;}};
    inline void addedge(int u,int v,int w){
        edges[++N]=Node{v,head[u],w},head[u]=N,
        edges[++N]=Node{u,head[v],w},head[v]=N;
    }
    __inline__ __attribute__ ((always_inline)) void dij(int st){
        priority_queue<node,vector<node,myalloc<node> >,cmp > Q;
    	memset(dis,0x3f,sizeof(dis));
        Q.push(node{0,st}),dis[st]=0;
        while(!Q.empty()){
            node now=Q.top();Q.pop();
            if(now.dis!=dis[now.to])continue;
            reg int v,tp=now.to;reg double w;
            for(reg int i=head[tp];i;i=edges[i].nxt)
                v=edges[i].v,w=edges[i].w,
                dis[v]>dis[tp]+w&&(dis[v]=dis[tp]+w,Q.push(node{dis[v],v}),0);
        }
    }
}using namespace Dijkstra;
int main(){
	freopen("1.in","r",stdin);
    cin>>m;
    reg char a,b;int c;
    for(;m;--m)cin>>a>>b>>c,addedge(a,b,c);
    dij('Z');
    reg int ans='A';
    for(reg int i='B';i<'Z';++i)dis[i]<dis[ans]&&(ans=i);
    *q++=ans,*q++=' ',write(dis[ans]);
    return 0;
}
```

---

## 作者：key_rA9 (赞：4)

~~*废话不多说（其实我本来就没说废话）*~~  
## 暴力出奇迹。
直接二维存图，搜索找答案
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
int p,ans,num=0xfffffff,c,f[111][111];
char x,y;
int main()
{
    scanf("%d",&p);
    memset(f,63,sizeof(f));//初始化所有路都奆长 
    while(p--)
    {
        scanf(" %c %c%d",&x,&y,&c);//↓字符要转换成数来当下标 
        f[x-64][y-64]=f[y-64][x-64]=min(f[x-64][y-64],c);
    }//因为可能有连接同两地的不同的路要最短的↑
    for(int k=1;k<=58;k++)//枚举连接两点中间的牧场 
    for(int i=1;i<=58;i++)//枚举牧场1 
    if(i!=k)//同一点没有意义 
    {
        for(int j=1;j<=58;j++)//枚举牧场2 
            if(i!=j&&k!=j)
                f[i][j]=min(f[i][j],f[i][k]+f[j][k]);//取最短 
    }//上面部分通过一点连接1、2牧场更新最短距离 
    for(int i=1;i<26;i++)//枚举所有有牛的牧场 
    {
        if(f[i][26]<num){num=f[i][26],ans=i;}//到谷仓的距离↓
    }
    printf("%c %d\n",ans+64,num);//ans变为字母ASCLL码 
    return 0;
}
```

---

## 作者：__AFOier__ (赞：3)

这道题可以使用SPFA  不被卡，不被杀！

~~反正数据如此蒻~~

-------------------------------xcy-AK-IOI----------------------------------------

### 一 分析

1. 建图

some people think that "字符" is so difficult to "建图

However,we can use a thing called "HASH"(ASCII 码）

我们可以让：

A对应1，B对应2，……， Z对应26，a对应27，b对应28 ……z对应52

于是乎：
从A点到d点，即等价于从1号节点走到30号节点

这样，其实也得出了：

图中最多有52个节点

so，


------------


 2.算法
 
 这道题可以转化为：
 
 从Z反向回到原来奶牛地点，
 
 即：“这题把Z（谷仓）当起点，把有牛的牧场当终点求最短路就行了。“（by Gamin)
 
 由于节点最多只有52个
 
 所以——
###  可以用邻接矩阵！

###  可以用SPFA(O(KE))，DJ算法(O(N*M))，FLOYED(O(N^3))！

~~（开心）~~

但我只会SPFA(qwq)

so， this code use a algorithm called "SPFA".


------------


3. 细节

这道题需要建双向边

而且，会有这样的数据（类似，并不一定）

......

A g 12

.......

A g 2

我们需要作一些处理，防止毒瘤数据

-------------------------------xcy-AK-IOI----------------------------------------

### 二 代码

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

char a,b;
int m,x;
int g[100][100],vis[100],d[100];
queue <int> q;

int main() {
	cin>>m;
	memset(g,217,sizeof(g));
	for (int i=1; i<=m; i++) {
		cin>>a>>b>>x;
		int xx,yy;
            // 建图
		if (a<='z'&&a>='a') xx=a-'a'+27;
		else xx=a-'A'+1;//ASCII码对应
		if (b<='z'&&b>='a') yy=b-'a'+27;
		else yy=b-'A'+1;//ASCII码对应
		g[yy][xx]=min(g[yy][xx],x);
		g[xx][yy]=min(g[xx][yy],x);//防毒瘤数据
            // 建图完
	}
    //SPFA灵魂
	memset(d,217,sizeof(d));
	q.push(26),vis[26]=1,d[26]=0;//Z对应26
        while （1） ；
	while (!q.empty()) {
		int x=q.front();
		q.pop(),vis[x]=0;
		for (int i=1; i<=60; i++) {
			if (!g[x][i]) continue;
			int v=i,w=g[x][i];
                       //松弛
			if (d[x]+w<d[v]) {
				d[v]=d[x]+w;
				if (!vis[v]) q.push(v),vis[v]=1;//进队
			}
                       //松弛完
		}
	}
    //比较
	int mini,minn=1e9;
	for (int i=1; i<=25; i++) {
		if (d[i]<minn) minn=d[i],mini=i;
	}
	cout<<char(mini-1+'A')<<" "<<d[mini];
	return 0;
   //代码有大坑，3个  please save your life by "不抄题解 "
}
```

-------------------------------xcy-AK-IOI----------------------------------------

At last ,a sentences is for you :

暴力出奇迹，骗分过样例 

（PS：我这边中文不好打，有时候只能打英文（qwq））

---

## 作者：Taduro (赞：3)

竟然没有人用Floyd，本蒟蒻赶紧来水一发。

这题的数据看上去很大，但实际上完全没有什么用，因为题目已经说了，只有 2*26-1=51个牧场和一个谷仓，总共就52个点，同时有要求找所有点到谷仓的最短距离，很自然就会想到Floyd了。（当然也可以以谷仓为原点，找离谷仓最近的点，但Floyd好写不是吗）

主要思路：用点的ASCII码来代替他们的下标，这样就可以用一个二维数组表示点到点的距离，因为'Z'到'a'之间有一些乱字符，但并不碍事，把初始值附好就可以了，这样最多也就是70个以下了。

具体实现：见代码
```_ 
#include<iostream>
using namespace std;
char a,b;
int w[101][101],m,i,j,k,x,p,minn=1e7,q,n=70;//打惯了从一到n，懒得改
int main(){
	cin>>p;
	for (i=1; i<=100; i++)
	  for (j=1; j<=100; j++) w[i][j]=1e7;
	for (i=1; i<=p; i++){
		cin>>a>>b>>x;
		w[b-'A'+1][a-'A'+1]=w[a-'A'+1][b-'A'+1]=min(w[a-'A'+1][b-'A'+1],x);//直接用字符表示下表就好了，懒得再开一个变量
	}
	for (k=1; k<=n; k++)//弗洛伊德算法主题，肯定轮不到我来讲
	  for (i=1; i<=n; i++)
	    for (j=1; j<=n; j++)
	      w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
	for (i=1; i<=25; i++)//注意一定只能到25
	    if (w[i][26]<minn){minn=w[i][26]; q=i;}
	cout<<(char)(q+'A'-1)<<' '<<w[q][26];
	return 0;
}```

---

## 作者：Dog_Two (赞：3)

~~任何用空格隔开字符的题目都是耍流氓~~

仍然是鼓吹一波bellman_ford，单源最短路里面最好记的代码，很适合新人，而且效率也并不很低——和SPFA的最差情况同阶呢（逃）

注意事项：
- 在scanf里，在字符格式符前留一个空格，就可以**恰好**地过滤不必要的空格；也可以用流输入比较方便地解决

- 各种最短路算法都要采用无向图的松弛（或加边）办法，还要注意重边和自环

- 字符类的处理较复杂，建议在不影响效率的情况下不妨泛化处理（见代码）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=1e4+10;
int P;
char u[maxm],v[maxm]; int w[maxm];
//存边的数组 
int dis[200];//'z'==(int)122
int main(){
    cin>>P;
    memset(dis,0x3f,sizeof(dis)); dis['Z']=0;
    for(int i=1;i<=P;i++) scanf(" %c %c%d",&v[i],&u[i],&w[i]);
    //题意告诉我们有重边和自环,不过用数组方式存边是不用担心这种情况的 
    int k=200;
    //一般情况下，k应该是n-1，这里直接用一个不影响效率的较大数字也是没有问题的
    while(k--){
        bool if_los=false;
        for(int i=1;i<=P;i++){
            char &from=u[i],&to=v[i];
            int &cost=w[i];
            if(dis[to]>dis[from]+cost){
                dis[to]=dis[from]+cost;
                if_los=true;
            }
            if(dis[from]>dis[to]+cost){
                dis[from]=dis[to]+cost;
                if_los=true;
            }
            //无向图需要双向松弛 
        }
        if(!if_los) break;
        //没有进行松弛，则最短路求解完毕 
    }
    int ans_dis=INT_MAX;
    char ans_char;
    for(int i='A';i<'Z';i++)/*只有大写字母标记的农场有奶牛*/if(dis[i]<ans_dis){
        ans_dis=dis[i];
        ans_char=i;
    }
    cout<<ans_char<<" "<<ans_dis; 
    return 0;
}
```

---

## 作者：兮水XiShui丶 (赞：3)

洛谷 P1529 回家

- 1 （输入） 刚刚开始看这道题的时候不太会字符串的同学（比如说我），都会对题目里要求的输入有一点慌张。但是我们可以反过来想一想，比如这个点是A,我们完全可以用A的ASCLL码来表示A这个节点，我们只需要在输入时把两个字符变成它们的ASCLL码，这样一来，我们的输入就完成了。
- 2 （work） 题目要求我们输出耗时最小的牛所在的牧场和它所用的时间，而且题目中说明了只有是A-Y中的字母时才有奶牛，所以我们可以把大写字母的牧场做一个标记，这样一来在下一步跑最短路时可以大大节约效率。
- 3 （最短路）由于这个题目的数据不大，所以我们可以跑n遍SPFA来解决这个问题，每一次把到Z牧场的最短路标记下来，如果可以更新之前的答案就更新之前的答案，跑完后，标记中的点即为答案 。
- 4 （CODE） 以下是我的代码，不管你看不看，会这道题是最重要的。。。
```cpp
#include <iostream>//所有要用到的头文件
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define N 10002
#define M 10000007
using namespace std;
queue <int> qu;//队列，跑SPFA的时候要用到
struct edge{
	int from;
	int to;
	int date;
	int next;
}e[M];
bool have_cow[N],inque[N];
int n,head[N],vis[N];
int edge_num;
void add (int x,int y,int z){//基本的加边操作
	e[++edge_num].to=y;
	e[edge_num].date=z;
	e[edge_num].from=x;
	e[edge_num].next=head[x];
	head[x]=edge_num;
} 
inline void spfa (int x){//主体，SPFA
	memset (vis,63,sizeof(vis));
	memset (inque,0,sizeof(inque));
	qu.push(x);inque[x]=1;vis[x]=0;
	while(!qu.empty()){
		int j=qu.front();
		inque[j]=0;
		qu.pop();
		for (int i=head[j];i;i=e[i].next){
			int k=e[i].to;
			if (vis[k]>vis[j]+e[i].date){
				vis[k]=vis[j]+e[i].date;
				if (!inque[k]){
					inque[k]=1;
					qu.push(k);
				}
			}
		}
	}
}
int main () {
	scanf ("%d",&n);
	for (int i=1;i<=n;i++){
		char a,b;int c;
		cin>>a>>b>>c;
		//cout<<"a= "<<a<<" b= "<<b<<" c= "<<c<<endl;
		int x=a,y=b,z=c;
		//cout<<"x= "<<x<<" y= "<<y<<" z= "<<z<<endl;
		if (x>='A' && x<='Y') have_cow[x]=1;//前边说的输入和标记
		if (y>='A' && y<='Y') have_cow[y]=1;
		add (x,y,z);
		add (y,x,z);
	}
	int mins=99999999;
	int now_min=0;
	for (int i=65;i<=127;i++){
		if (have_cow[i]) { //如果有标记再跑，跑n遍SPFA
		    spfa (i);
		    if (vis[90]<mins){
			mins=vis[90];
			now_min=i;
		 }
	  }
	}
	cout<<(char)now_min<<" "<<mins<<endl;//最后标记剩下的就是答案
	/*for (int i=1;i<=edge_num;i++){
		int l=e[i].from;
		int r=e[i].to;
		cout<<"edge"<<i<<": from "<<l<<" to "<<r<<" date= "<<e[i].date<<endl;
	}*/
	return 0;
}
```

---

## 作者：HPXXZYY (赞：2)

[题目传送门](https://www.luogu.org/problemnew/show/P1529)

一看题目，第一感觉肯定要使用spfa算法

本题与普通的最短路算法不同的是，普通的最短路处理的是整数（即用整数编号牧场），但本题用字符编号牧场

所以我们可以使用c++ STL中的映射map

话不多说，直接上代码：

[评测记录：](https://www.luogu.org/recordnew/show/16249573)

状态/分数：Accepted，100分

语言/长度：C++，1.2KB

耗时/内存：49ms，1044KB

```cpp
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
map<char,int> d,head;//映射
char x,y;int cnt,n,i,ans,z;
struct node{
    int next,w;char to;
}e[20200];
void add(char a,char b,int c){
    e[++cnt]={head[a],c,b};head[a]=cnt;
}//建图
queue<char> q;//队列
map<char,bool> v;//又是映射
const int inf=0x7fffffff;
//0x7fffffff即为2147483647
void spfa(char bx){
    for(char f='a';f<='z';f++){
        d[f]=d[f-'a'+'A']=inf;
        v[f]=v[f-'a'+'A']=true;
    }
    d[bx]=0;v[bx]=0;q.push(bx);
    //初始化映射
    while (q.size()){
        char z=q.front();q.pop();v[z]=1;
        for(int i=head[z];i;i=e[i].next){
            //遍历邻接矩阵
            register char u=e[i].to;
            if (d[u]>d[z]+e[i].w){
                d[u]=d[z]+e[i].w;
                if (v[u]){
                    v[u]=0;q.push(u);
                }
            }
        }
    }
}
int main(){
//	freopen("t2.in","r",stdin);
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("\n%c %c %d",&x,&y,&z);
        //注意scanf可以读入空白字符（空格，空字符或TAB
        add(x,y,z);add(y,x,z);//建无向图
    }
    spfa('Z');ans=inf;
    for(x='A';x<'Z';x++)
    if (d[x]!=inf){
        if (d[x]<ans){
            ans=d[x];y=x;
        }
    }
    //寻找极值（即答案）
    printf("%c %d",y,ans);
    return 0;
}
```

---

## 作者：Caicz (赞：1)

### 最短路

**本题的数据较弱（最多也就52个点的图）**

**所以各路神仙算法都可以过（~~包括某已死算法~~）**

既然各路算法都可以，那为什么不用最简单的floyd呢

**但是**，虽然数据很小，但题目有好几个坑点

1.**重边重边重边**，注意读题，本蒟蒻就是因为没对重边进行比较，**89分---GET**

2.注意输入的形式。这可能是本题唯一的难点----**对字符的处理**，本蒟蒻是直接用**ASKⅡ码来进行最短路的松弛**，后果就是调了快20分钟。所以这里是建议尽量处理一下，变换为常数

代码就贴下面了
```c
#include<bits/stdc++.h>
using namespace std;
int f[200][200],Q[200];
int m,lenth=999999999;

int main()
{
	cin>>m;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=m;i++)
	{
		char a,b;
		int c;
		cin>>a>>b>>c;
		f[a][b]=f[b][a]=min(f[a][b],c);
		if(a>='A'&&a<='Z')
			Q[a]=true;
		if(b>='A'&&b<='Z')
			Q[b]=true;
	}
```
Q是**判断数组**，目的是为了分辨出有奶牛的结点
```
	Q['Z']=false;//终点无奶牛，重置为FALSE
	for(int k=1;k<=160;k++)
		for(int i=1;i<=160;i++)
			for(int j=1;j<=160;j++)
				if(f[i][j]>f[i][k]+f[k][j])
					f[i][j]=f[i][k]+f[k][j];
	char ans;
	for(int i=1;i<=160;i++)
	{
		if(!Q[i])continue;
		if(f['Z'][i]<lenth)
		{
			lenth=f['Z'][i];
			ans=i;
		}
	}
	cout<<ans<<" "<<lenth<<endl;
	return 0;
}
```


---

## 作者：Warriors_Cat (赞：1)

关于这道题，许多dalao都是用SPFA和dijkstra做的。

燃鹅，看一下数据，最多52种情况('A'~'Z', 'a'~'z')

**那暴力搜索不就行了吗？**

[$\color{red}\text{AC证据}$](https://www.luogu.org/record/22176525)

暴力搜索也跑得挺快的，才35ms。

下面讲一下我的思路：~~敲黑板划重点~~

首先，建图，直接用ASCII码+数组搞定。~~记得是无向图qwq~~

其次，暴力dfs，中间可以进行记搜剪枝。

最后，直接输出即可

时间复杂度为$O(n^3)$，对于52来说已经是绰绰有余了

---------------------------------~~完美的分割线~~---------------------------------

## Code：

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, a[256][256];
char f, t; int d;
char cow, flag; int ans;
int u[256];
bool vis[256];
void dfs(int x, int s){
	if(s >= u[x]) return;//剪枝 
	u[x] = s;
	if(x == 90){//'Z'的ASCII码值为90 
		if(s < ans){//存储 
			ans = s;
			cow = flag;
		}
		return;
	}
	else{
		for(int i = 65; i <= 90; ++i){
			if(a[x][i] == a[0][0]) continue;//没有路 
			dfs(i, s + a[x][i]);
		}//大写字母dfs 
		for(int i = 97; i <= 122; ++i){
			if(a[x][i] == a[0][0]) continue;//没有路 
			dfs(i, s + a[x][i]);
		}//小写字母dfs 
	}
}
int main(){
	memset(u, 127, sizeof(u));
	ans = u[0];//ans存个较大值 
	memset(a, 127, sizeof(a));//a也存个较大值
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> f >> t >> d;
		if(f == t) continue;
		vis[(int)f] = 1;
		vis[(int)t] = 1;//记录有牧场 
		a[(int)f][(int)t] = min(a[(int)f][(int)t], d);
		a[(int)t][(int)f] = min(a[(int)t][(int)f], d);//存图 
	}
	for(int i = 65; i <= 89; ++i){//记得！！是'A'-'Y'，被坑调了半个多小时qwq 
		if(vis[i]){
			flag = (char)i;
			dfs(i, 0);
		}
	}
	cout << cow << " " << ans;//输出 
	return 0;
}
```

以上就是本蒟蒻的思路，如有不懂者，欢迎留言

## End

---

## 作者：agicy (赞：1)

# 思路

很显然，这是一道**无向图求最短路**的题目，观察数据范围$(1<= P<=10000)$，决定用不会超时且最简单的$Dijkstra$算法来解题。

看到其他题解多次求最短路浪费时间的问题，我只能说：

**其他所有点到点$Z$的路径和点$Z$到其他所有点的路径相同**，只需以点$Z$为起点求最短路，再找到$A$~$Y$中最短路径长最短的点即可。

# 代码

采用$Dijkstra$算法、邻接表和堆（优先队列）优化，代码如下。

```cpp
#include<stdio.h>
#include<string.h>
#include<iostream>
using std::cin;
#include<queue>
using std::priority_queue;
using std::vector;
using std::greater;
/*
using std::sth;
是为了防止命名空间的污染
以上是头文件
*/
#define INF 0X3F3F3F3F
//宏定义

struct Node{
	int len;//len为这条路的长度
	int to;//to为这条路的下一个端点
	bool operator>(Node a)const{
		return this->len>a.len;
	}
};//优先队列中的元素

bool f[20001];//标记数组，防止重复
int p,head[128],Next[20001],to[20001],len[20001],d[20001],l=INF,ans;//邻接表和答案的定义
Node temp;//用于输入和插入优先队列的临时变量
priority_queue<Node,vector<Node>,greater<Node> > Q;//小根堆

void Dijkstra(int);//函数声明

int main(void){
	scanf("%d",&p);
	for(int i=1,w;i<=(p<<1);i+=2){
		char f,g;
		cin>>f>>g;//用cin读入可自动忽略空格和换行符
		scanf("%d",&w);
		Next[i]=head[f];
		head[f]=i;
		to[i]=g;
		len[i]=w;
		Next[i+1]=head[g];
		head[g]=i+1;
		to[i+1]=f;
		len[i+1]=w;//无向图记得存两遍
	}
	Dijkstra('Z');//以点Z为起点求最短路
	for(int i='A';i<='Y';i++)
		if(d[i]<l)
			l=d[i],ans=i;//枚举寻找答案
	printf("%c %d",ans,l);//输出
	return 0;//结束
}

void Dijkstra(int start){//Dijkstra算法
	memset(d,0X3F,sizeof(d));
	memset(f,0,sizeof(f));
	d[start]=0;
	temp.len=0,temp.to=start;
	Q.push(temp);
    /*上面为初始化*/
	while(Q.size()){
		temp=Q.top();
		char now=temp.to;
		Q.pop();
		if(f[now])
			continue;
		f[now]=true;
		for(int i=head[now];i;i=Next[i]){
			int node_next=to[i],len_this_way=len[i];
			if(d[node_next]>d[now]+len_this_way)
				d[node_next]=d[now]+len_this_way,
				temp.len=d[node_next],temp.to=node_next,
				Q.push(temp);
		}
	}
	return;
}
```

---

## 作者：Zimo (赞：1)

菜OJ题号：1835 http://caioj.cn/problem.php?id=1835

洛谷题号：P1529 https://www.luogu.org/problemnew/show/P1529

##### 我的思路：

这题把Z（谷仓）当起点，把有牛的牧场当终点求最短路就行了。

有人会问，牧场是用字母表示的啊，怎么转成数字呢？

a~z -> 1~26

A~Z -> 27~52

##### 代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
    int x,y,d,next;
} a[22000];//注意，我们要建双向边，所以边数要是两倍！
int last[60],len=0;
bool v[60];
int ans=999999999,ansi=0;
void ins(int x,int y,int d)
{
    len++;
    a[len].x=x;a[len].y=y;a[len].d=d;
    a[len].next=last[x];last[x]=len;
}
void dfs(int x,int s)
{
    if(s>ans) return;
    for(int k=last[x]; k; k=a[k].next)
    {
        int y=a[k].y;
        if(v[y]==false)
        {
            v[y]=true;
            if(y>26)
            {
                if(s+a[k].d<ans) {ans=s+a[k].d;ansi=y;}
            }
            else dfs(y,s+a[k].d);
            v[y]=false;
        }
    }
}
main()
{
    int m;
    scanf("%d",&m);
    for(int i=1; i<=m; i++)
    {
        char x,y;
        int c;
        scanf("\n%c %c %d",&x,&y,&c);
        int xx,yy;
        if(x>='a' && x<='z') xx=x-'a'+1;
        else  xx=x-'A'+27;
        if(y>='a' && y<='z') yy=y-'a'+1;
        else  yy=y-'A'+27;
        ins(xx,yy,c);
        ins(yy,xx,c);
    }
    v[52]=true;
    dfs(52,0);
    printf("%c %d\n",ansi-27+'A',ans);
    return 0;
}
```

---

## 作者：Silicon (赞：1)

这道题就是一道裸的单源最短路径。我们知道，对于Dijkstra，我们知道他的松弛操作时需O(n)查找最短边，那么我们可以使用一个堆来维护这个东西，时间复杂度降为O(log2m)，综合复杂度为O(nlgm) -\_-

考虑到这道题时歪果仁出的，不会卡SPFA，所以对于这道题SPFA比Dij+Heap快2-3ms，但是不管哪个都比标准Dij和Floyd高到不知道哪里去了（逃

以下是代码，存边方式是从紫书上面借鉴的一种邻接矩阵和邻接表混合的方式，兼具了邻接表的节约空间和邻接矩阵的直观，不过由于使用了vector可能会有一些奇妙的常数。。。

```cpp
#include<cstdio>
#include<bitset>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const ll mod=1000000007;//1e9+7
const int inf=0x7fffffff;
const int maxn=100;
int n,m;
struct Edge{
    int from,to,dist;
    Edge(int u,int v,int d):from(u),to(v),dist(d){}
};
struct Dij{
    vector<Edge> edge;
    vector<int> G[maxn];
    bitset<maxn> visd;
    int d[maxn];
    int m,n;
    void clear(int n)
    {
        this->n=n;
        for(int i=1;i<=n;i++)
            G[i].clear();
        edge.clear();
    }
    void addEdge(int f,int t,int v)
    {
        edge.push_back(Edge(f,t,v));
        G[f].push_back(edge.size()-1);
    }
    struct Node{
        int d,u;
        bool operator < (const Node& b) const {
            return d>b.d;
        }
    };
    void Dijkstra(int start)
    {
        priority_queue<Node> Q;
        memset(d,0x3f,sizeof(d));
        d[start]=0;
        Q.push((Node){0,start});
        while(!Q.empty())
        {
            Node x=Q.top();
            int u=x.u;
            Q.pop();
            if(visd[u])
                continue;
            visd[u]=1;
            for(int i=0;i<(int)G[u].size();i++)
            {
                Edge& e=edge[G[u][i]];
                if(d[e.to]>e.dist+d[u])
                {
                    d[e.to]=e.dist+d[u];
                    Q.push((Node){d[e.to],e.to});
                }
            }
        }
    }
    
}SL;
//以上是所有的Dijkstra操作，封在一个结构体中

int p,v,minn=0x7fffffff,fr,to,ans;
char f[5],t[5];
int main()
{
    scanf("%d",&p);
    SL.clear(60);
    for(int i=1;i<=p;i++)
    {
        scanf("%s%s%d",f,t,&v);
        fr=f[0]-'A';
        to=t[0]-'A';
        SL.addEdge(fr,to,v);
        SL.addEdge(to,fr,v);
    }
    SL.Dijkstra('Z'-'A');
    for(int i=0;i<='Y'-'A';i++)
    {
        if(SL.d[i]<minn)
        {
            ans=i;
            minn=SL.d[i];
        }
    }
    printf("%c %d",ans+'A',minn);
    return 0;
}
//sro tyc
```

---

## 作者：Refined_heart (赞：1)

来一个不用邻接矩阵，堆优化的$dijkstra$吧。

题目显然要求终点$'Z'$到其它点的最短路。

显然一遍$dijksstra$跑出来。

考虑题目细节。

首先，注意只有大写字母的点才算起点，其它的都是中转站。所以，最后遍历取$min$的时候注意特判。

不需要特别注意字母，直接转$ASCLL$码转成$int$即可。

题目得解。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
#define inf 2147483647
int m,vis[500000],tot,ans=inf,p;
int dis[500000],head[500000];
char x,y;
struct edge{
	int next,to,dis;
}e[500000];
struct node{
	int dis,pos;
	bool operator <(const node&x)const{
		return x.dis<dis;
	}
};
priority_queue<node>q;
inline void add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].next=head[u];
	e[tot].dis=w;
	head[u]=tot;
}
void dijkstra(){
	dis['Z']=0;
	q.push((node){0,'Z'});
	while(!q.empty()){
		node tmp=q.top();
		q.pop();
		int u=tmp.pos;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].dis){
				dis[v]=dis[u]+e[i].dis;
				if(!vis[v])q.push((node){dis[v],v});
			}
		}
	}
}
int main(){
	scanf("%d",&m);
	for(int i=1;i<=200;++i)dis[i]=inf;
	for(int i=1;i<=m;++i){
		cin>>x>>y;
		int w;
		scanf("%d",&w);
		add(x,y,w);add(y,x,w);
	}
	dijkstra();
	//printf("%d\n",dis['B']);
	for(int i='A';i<='z';++i){
		if(i=='Z'||dis[i]==0||dis[i]==inf||i>'Z')continue;
		if(dis[i]<ans){
			ans=dis[i];
			p=i;
		}
	}printf("%c %d",p,ans);
	return 0;
}
```


---

## 作者：Kdlyh (赞：1)

这道题总体来说并不难，纯模拟即可。**唯一的难点就是判断无解。**

我想了挺久愣是没想到什么好办法。然后我就动了点歪脑筋。

我们先来看一下这份没有判断无解情况的代码(我把他命名为**代码67**）。(思路与其他题解大体相同的，泥萌看不懂的话也可以去看其他题解的注释，然后他们判断无解的部分先忽略掉。


```cpp
#include <cstdio>
#include <iostream>

const int N = 12;
const int dirx[]={-1,0,1,0},
          diry[]={0,1,0,-1}; 

char g[N][N];
int nx,ny;
int fx,fy;
int fdir;
int ndir;
int step;

bool in_side(int x,int y) {
    return (x>=1 && x<=10 && y>=1 && y<=10);
}

void Input() {
    std::ios::sync_with_stdio(false);
    for(int i=1; i<=10; i++) {
        for(int j=1; j<=10; j++) {
            std::cin>>g[i][j];
            if(g[i][j] == 'F') {
                fx=i,fy=j;
            }
            if(g[i][j] == 'C') {
                nx=i,ny=j;
            }
        }
    }
}

void Solve() {
    while(fx != nx || fy != ny) {
        step++;
        if(!in_side(fx+dirx[fdir],fy+diry[fdir]) 
        || g[fx+dirx[fdir]][fy+diry[fdir]] == '*') {
            fdir=(fdir+1)%4;
        } else {
            fx+=dirx[fdir],fy+=diry[fdir];
        }
        if(!in_side(nx+dirx[ndir],ny+diry[ndir]) 
        || g[nx+dirx[ndir]][ny+diry[ndir]] == '*') {
            ndir=(ndir+1)%4;
        } else {
            nx+=dirx[ndir],ny+=diry[ndir];
        }
    }	 
    std::cout<<step;
}

int main(void) {
    Input();
    Solve();
    return 0;
}
```
这份代码交上去是$67$分，$TLE$了三个点。

是$TLE$而不是$WA$！原因显而易见：如果无解的话``while``循环会一直执行下去直到超时。

我们来分析一下这道题的性质：
1. 如果有解就输出正确答案，如果无解就输出零
- **不能超过时间限制**
3. 这道题有$1.6kAC$

从第三点，我们先肯定了这道题是可以$AC$的。

**既可以$AC$,又不能超过时间限制。**

我们就可以得出:**如果一个数据在时间限制内得不到解，那这个数据一定无解！**
(当然，这个结论是在保证了**代码67**的时间按复杂度较优的情况下得出的。)

由这个结论我们进而可以推导出一个特别的无解判断方法：**判断程序是否能在时间范围内得出解**

我想到了两种方法：

第一种是分析程序的复杂度，然后从``while``循环的执行次数入手:
	
   - **代码67**很明显是$o(n)$的。我们先贴一张图。
   ![](https://i.loli.net/2019/02/07/5c5baf7976dfe.png)
   
   很明显，如果``while``循环的执行次数超过了$10^7$，那就超时了。
   **于是只要在``while``循环里面加上一句``if(step > 1e7) {printf("0");return ;}``就完事了。**

第二种是利用``<ctime>``这个库直接计算程序运行时间。但是我太菜了并不熟悉怎么用。有兴趣的同学自行百度咯。

于是我这不太正常的解法就$AC$了。

AC代码
```cpp
#include <cstdio>
#include <iostream>

const int N = 12;
const int dirx[]={-1,0,1,0},
          diry[]={0,1,0,-1}; 

char g[N][N];
int nx,ny;
int fx,fy;
int fdir;
int ndir;
int step;

bool in_side(int x,int y) {
    return (x>=1 && x<=10 && y>=1 && y<=10);
}

void Input() {
    std::ios::sync_with_stdio(false);
    for(int i=1; i<=10; i++) {
        for(int j=1; j<=10; j++) {
            std::cin>>g[i][j];
            if(g[i][j] == 'F') {
                fx=i,fy=j;
            }
            if(g[i][j] == 'C') {
                nx=i,ny=j;
            }
        }
    }
}

void Solve() {
    while(fx != nx || fy != ny) {
        step++;
        if(!in_side(fx+dirx[fdir],fy+diry[fdir]) 
        || g[fx+dirx[fdir]][fy+diry[fdir]] == '*') {
            fdir=(fdir+1)%4;
        } else {
            fx+=dirx[fdir],fy+=diry[fdir];
        }
        if(!in_side(nx+dirx[ndir],ny+diry[ndir]) 
        || g[nx+dirx[ndir]][ny+diry[ndir]] == '*') {
            ndir=(ndir+1)%4;
        } else {
            nx+=dirx[ndir],ny+=diry[ndir];
        }
        if(step > 1e7) {
            printf("0");
            return ;
        }
    }	 
    std::cout<<step;
}

int main(void) {
    Input();
    Solve();
    return 0;
}
```
望题解过审。


---

## 作者：晓曦315 (赞：1)

这道图论，首先是无向图，我用了邻接矩阵存储，然后还要考虑权值覆盖的问题，因为它输入的时候两个牧场之间可能会有超过一条道路相连。然后我用了floyed算法求最短路就ok了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,z,t,min_=2000000000,a[60][60];
char b,c;
void floyed()
{
    for (int k=1;k<=52;++k)
    for (int i=1;i<=52;++i)
    for (int j=1;j<=52;++j)
    if (a[i][k]+a[k][j]<a[i][j]) a[i][j]=a[i][k]+a[k][j];
}//floyed算法 
int main()
{
    cin>>n;
    memset(a,10,sizeof(a));//a数组初始一个很大的值 
    for (int i=1;i<=n;++i)
    {
        cin>>b>>c>>z;
        if (b>='A'&&b<='Z') x=b-64;
        if (b>='a'&&b<='z') x=b-70;
        if (c>='A'&&c<='Z') y=c-64;
        if (c>='a'&&c<='z') y=c-70;//因为输入的是大小写字母，要转化一下 
        a[x][y]=min(a[x][y],z);
        a[y][x]=min(a[y][x],z);//这两句是要考虑权值覆盖的问题 
    }
    floyed();
    for (int i=1;i<=25;++i)
    {
        if (a[26][i]<min_)
        {
            min_=a[26][i];
            t=i;
        }
        if (a[i][26]<min_)
        {
            min_=a[i][26];
            t=i;
        }
    }//找最小路径 
    x=char(t+64);//因为输出的是字母，要处理一下 
    cout<<x<<" "<<min_;
    return 0;
}
```

---

## 作者：teafrogsf (赞：0)

##**真不是很懂你们用SPFA或者DJ的**

明明是一个Floyd\_只要不作死弄成单向图\_可以搞定的事情

注意判定一下有无奶牛的事就可以了

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define ff(i,a,b) for(i=a;i<=b;i++)//预定义
using namespace std;
int n,minn=100000000,minm;
int f[60][60];
bool s[60];
char instead[10];
int main()
{
    int i,j,k,z,xx,yy;
    char x,y;
    scanf("%d",&n);gets(instead);
    ff(i,1,52)
     ff(j,1,52)
     {
         if(i!=j)f[i][j]=100000000;
     }
    ff(i,1,n)
    {
        scanf("%c %c %d",&x,&y,&z);
        if(x>='A'&&x<='Z')s[x-'A'+1]=1,xx=x-'A'+1;
        else xx=x-'a'+27;
        if(y>='A'&&y<='Z')s[y-'A'+1]=1,yy=y-'A'+1;
        else yy=y-'a'+27;
        if(z<f[xx][yy])f[xx][yy]=f[yy][xx]=z;
        gets(instead);//由于洛谷那令人蛋疼的输入格式，特此用字符串解决问题
    }
    s[26]=0;//'Z'无奶牛
    
    //ff(i,1,52)printf("%d ",s[i]);
    ff(k,1,52)
     ff(i,1,52)
      ff(j,1,52)
      {
          f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
      }
    ff(i,1,51)if(f[i][26]<minn&&s[i]==1)minn=f[i][26],minm=i;
    printf("%c %d\n",minm+'A'-1,minn);
    return 0;
}
```

---

## 作者：江海寄余生 (赞：0)

显然，这道题是求一个以‘Z'为根节点单源最短路中的路径最短的大写字母节点

很自然地会想到用dijkstra嘛

为什么都用floyd呢。实验表明dijkstra比floyd确实要快那么一些

其实对于这种稠密图最好应用邻接矩阵（删去一些没用的边，比如几条连接两个相同节点的边只取其中最短的一条）

我这里只是想研究一下邻接表的优化。

还有，其实pascal对字符的运用能力很强，没必要转ascall码

二话不说上代码






```cpp
type
  adj=record
    last,wei:longint;  //last存储这个节点在链表中的上一条边的地址，wei存储权值
    too:char; //too存储这条边指向那个节点
  end;
const caps=['A'..'Z'];
var
  all:set of 'A'..'z'; 
  a:array['A'..'z','A'..'z'] of longint; //a存储这条边在链表中的地址，如果不在链表中则为0
  edge:array[1..20000] of adj; //邻接表
  head,min:array['A'..'z'] of longint; //head存储节点在链表中最后一条边的地址
  nedge,v,e,z,k,minw:longint;
  x,xx,y,yy,i,j,minv:char;
procedure add(a,b:char; w:longint); //将边插入
begin
  inc(nedge);
  edge[nedge].last:=head[a];
  edge[nedge].too:=b;
  edge[nedge].wei:=w;
  head[a]:=nedge;
end;
procedure find; //找出最小值
begin
  for i:='A' to 'z' do
  if (i in all) and (min[i]<minw) then
    begin
      minw:=min[i];
      minv:=i;
    end;
end;
procedure readin;
begin
  readln(e);
  nedge:=0;
  fillchar(head,sizeof(head),0);
  for k:=1 to e do
  begin
    readln(x,xx,y,yy,z);
    if (a[x,y]<>0) and (edge[a[x,y]].wei>z) then
    begin
      edge[a[x,y]].wei:=z;
      edge[a[y,x]].wei:=z;
      continue;
    end; //如果这条边已经读过而且新读入的权值更小则替换原来的权值，相当于给他升级
    if a[x,y]<>0 then continue; //不然不处理
    if x=y then continue; //自己指自己无意义
    all:=all+[y];
    all:=all+[x]; //加入顶点集合all
    add(x,y,z);
    a[x,y]:=nedge;//这条边是新读入的要记录地址
    add(y,x,z);
    a[y,x]:=nedge;
  end;
end;
begin
  readin;
  all:=all-['Z']; //预处理第一个点'Z'，现在all用来存储待处理的节点
  k:=head['Z']; 
  for i:='A' to 'z' do
  begin
    min[i]:=maxlongint;
  end;
  min['Z']:=0;
  while k>0 do
  if min[edge[k].too]>edge[k].wei then
  begin
    min[edge[k].too]:=edge[k].wei;
    k:=edge[k].last;
  end;  
  while all<>[] do //dijkstra
  begin
    minw:=maxlongint;
    find;
    if minv in caps then //dijkstra的最短路径长度是递增的，所以找到的第一个大写字母最短路径长度就是最小的
    begin
      write(minv,' ',minw);
      halt;
    end;
    k:=head[minv];
    while (k>0) do  //松弛
    begin
      if min[edge[k].too]>edge[k].wei+minw then
      min[edge[k].too]:=edge[k].wei+minw;
      k:=edge[k].last;
    end;
    all:=all-[minv];
  end;
end.
```

---

## 作者：404_notfound (赞：0)


被这题恶心了一下午……特地来水一发题解
## 坑点：无向边

题意其实很清楚，就是求每个点到终点的最短路

我们可以把图反过来建，跑最短路的时候反着跑

当然这是对于有向图来说，毕竟这题是个无向图

这样题目就变成了求终点到任意一个大写字母点的最短路径

另外，对于字母的问题，直接使用ascll码就可以~~毕竟我懒~~

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10005;
int n;
vector<int> son[maxn],v[maxn];
int dis[maxn],tim=0;
int vis[maxn];
struct node{
	int x;
	int dis;
	bool operator < (const node &a)const 
	{
		return dis > a.dis;//小根堆 
	}
};

void Set(char prt,char to,int d)
{
	son[(int)prt].push_back((int)to);//见到char就转成int 
	v[(int)prt].push_back(d);
}
priority_queue<node> q;
#define to son[rt.x][i] 
void Dijkstra(int S)
{
	for(int i=0;i<maxn;i++)
	{
		dis[i]=0x7fffffff;
	}
	dis[S]=0;//起点 
	int res=0;
	tim++;//时间戳 
	q.push((node){S,0});//压入起点 
	while(!q.empty())
	{
		node rt=q.top();
		q.pop();
		if(vis[rt.x]==tim)
		{
			continue;//被访问过 
		}
		vis[rt.x]=tim;
		for(int i=0;i<son[rt.x].size();i++)//枚举所有可以到达的地方 
		{
			if(dis[to]>dis[rt.x]+v[rt.x][i])//距离更优 
			{
				dis[to]=dis[rt.x]+v[rt.x][i];//更新 
				q.push((node){to,dis[to]});//强转结构体 
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char x[10],y[10];
		int z;
		scanf("%s%s%d",x,y,&z);
		if(x[0]==y[0])continue;
		Set(y[0],x[0],z);//vector建边 
		Set(x[0],y[0],z);
	}
	Dijkstra((int)'Z');//从终点开始跑 
	char ans='0';
	int anss=99999;//从终点到所有大写字母的最短路 
	for(int i=(int)'A';i<(int)'Z';i++)
	{
		if(dis[i]<anss)
		{
			anss=dis[i];
			ans=(char)i;
		}
	}
	printf("%c %d",ans,anss);
	return 0;
}

```

---

## 作者：我没有小白 (赞：0)

看了一下题解，虽然有与我相类似的解法，但其实还有不同的嘻嘻嘻

我的思路是将牧场的字符直接转化成ascll码的形式，然后输出时直接将‘A’-‘Z’比较，所以呢就不用担心空牧场的问题了
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,minn=0x7fffffff;
struct edge
{
	int next,to,dist;
} e[200000];
queue<int>q;//这里就用一下c++黑科技吧，手写队列真的难写 
int head[200000],tot,dis[200000],vis[200000];
inline void add(int x,int y,int z)
{
	e[++tot].next=head[x];
	e[tot].to=y;
	e[tot].dist=z;
	head[x]=tot;
}//邻接链表 
void spfa(int s)
{
	while(!q.empty())q.pop();
	for(int i=65; i<=122; i++)dis[i]=0x7fffffff;
	dis[s]=0;
	q.push(s);
	vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u],v; v=e[i].to,i; i=e[i].next)
			if(e[i].dist+dis[u]<dis[v])
			{
				dis[v]=dis[u]+e[i].dist;
				if(!vis[v])
					vis[v]=1,q.push(v);
			}
	}
}//spfa算法，这虽然是个板子，但是比较好用 
int main()
{
	cin>>p;
	for(int i=1; i<=p; i++)
	{
		char a,b;
		int c;
		cin>>a>>b>>c;
		add(int(a),int(b),c);
		add(int(b),int(a),c);
	}
	//这里我的思路是直接将字符变为ascll码，之后直接用ascll码来存储图
	//不要忘记建立双向边 
	int w;
	spfa(90);//从终点开始训寻找 
	for(int i=65; i<=90; i++)
	{
		if(minn>dis[i]&&i!=90&&dis[i]!=0x7fffffff)//寻找最小值 
		{
			minn=dis[i];
			w=i;
		}
	}
	cout<<char(w)<<' '<<minn;//按要求输出 
}
```
管理大大求过么么哒

---

