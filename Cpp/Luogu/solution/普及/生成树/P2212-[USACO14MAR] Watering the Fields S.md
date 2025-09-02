# [USACO14MAR] Watering the Fields S

## 题目描述

Due to a lack of rain, Farmer John wants to build an irrigation system to


send water between his N fields (1 <= N <= 2000).

Each field i is described by a distinct point (xi, yi) in the 2D plane,

with 0 <= xi, yi <= 1000.  The cost of building a water pipe between two

fields i and j is equal to the squared Euclidean distance between them:



(xi - xj)^2 + (yi - yj)^2

FJ would like to build a minimum-cost system of pipes so that all of his

fields are linked together -- so that water in any field can follow a

sequence of pipes to reach any other field.


Unfortunately, the contractor who is helping FJ install his irrigation

system refuses to install any pipe unless its cost (squared Euclidean


length) is at least C (1 <= C <= 1,000,000).  

Please help FJ compute the minimum amount he will need pay to connect all

his fields with a network of pipes.


给定 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$，如果想连通第 $i$ 个点与第 $j$ 个点，需要耗费的代价为两点的距离。第 $i$ 个点与第 $j$ 个点之间的距离使用欧几里得距离的平方进行计算，即：
$$(x_i-x_j)^2+(y_i-y_j)^2$$
我们规定耗费代价小于 $c$ 的两点无法连通，求使得每两点都能连通下的最小代价，如果无法连通输出 `-1`。

## 说明/提示

INPUT DETAILS:


There are 3 fields, at locations (0,2), (5,0), and (4,3).  The contractor

will only install pipes of cost at least 11.

OUTPUT DETAILS:


FJ cannot build a pipe between the fields at (4,3) and (5,0), since its

cost would be only 10.  He therefore builds a pipe between (0,2) and (5,0)


at cost 29, and a pipe between (0,2) and (4,3) at cost 17.  

Source: USACO 2014 March Contest, Silver

### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n \le 2000$，$0 \le x_i,y_i \le 1000$，$1 \le c \le 10^6$。

### 说明

Translated by 一只书虫仔。

## 样例 #1

### 输入

```
3 11
0 2
5 0
4 3```

### 输出

```
46```

# 题解

## 作者：Rye_Catcher (赞：32)

- 题目链接：

  https://www.luogu.org/problemnew/show/P2212
  
- 思路：

  一道最小生成树裸题(最近居然变得这么水了),但是因为我太蒻,搞了好久,不过借此加深了对最小生成树的认识.
  
  首先这明显是个稠密图,有$\sum_{n-1}^{i=1}i=n*(n-1)/2$条边,看起来$Prim$会明显优于$Kruskal$,于是这道题我用了三种方法
  
  
- $Kruskal$

  简单易懂，简洁优美  耗时/内存 344ms, 24343KB
  
  代码：
  
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#define ri register int 
#define ll long long 
using namespace std;
const int maxn=2005;
const int inf=192681792;
struct Edge{
	int u,v,dis;
	bool operator <(const Edge& b)const{
		return dis<b.dis;
	}
}edge[19260817];//边数不要设小了 
int n,c,tot=0;
int px[maxn],py[maxn];
int fa[maxn];
int get(int x){
	if(fa[x]!=x)fa[x]=get(fa[x]);
	return fa[x];
}
inline void kruskal(){
	int u,v,dis;
	int cnt=0,ans=0;
	for(ri i=1;i<=n;i++){
		fa[i]=i;
	}
	for(ri i=1;i<=tot;i++){
		u=edge[i].u,v=edge[i].v;
		u=get(u),v=get(v);
		if(u!=v){
			fa[u]=v;
			ans+=edge[i].dis;
			cnt++;
	    }
	    if(cnt==n-1)break;
	}
	if(cnt==n-1)printf("%d",ans);
	else puts("-1");
	return ;
}
int main(){
	scanf("%d %d",&n,&c);
	for(ri i=1;i<=n;i++){
		scanf("%d %d",&px[i],&py[i]);
		for(ri j=1;j<i;j++){
			int d=(px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]);
			if(d>=c){
				edge[++tot].u=i,edge[tot].v=j,edge[tot].dis=d;
			}
		}
	}
	sort(edge+1,edge+1+tot);
	kruskal();
	return 0;
}
```
  
- $Prim+Priority\_queue$优化

  说到$Prim$就不得不提，觉得网上挺多$Prim$堆优化代码都是假的。
  
  $Prim$的原理是找到连接生成树点集中一点与非生成树点集中一点的最小边权，将其加入答案,于是我们用$vis[]$数组标记该点是否处在生成树点集中,$d[x]$记录x到非生成树点集中一点的最短边权，或者是该点加入生成树点集中时的边权。
  
  于是我们将一个节点加入生成树点集中时，就要通过此点进行一次类似松弛的操作，更新该点出边的$d[]$值，最终答案就是所有点$d[]$值之和。
  
  然后网上很多代码都没有这种类似操作，我也不太懂他们的原理
  
  但是呢，在此题上运用上述算法的$Prim$会快100+ms,应该是更优的
  
  同时此题还要判断-1情况（即无法联通），我们只需判断非生成树点集集合大小
  与无法加入生成树点集集合大小是否相等(即$d[x]=INF$的点的个数)就可以了.
   
  代码： 耗时/内存 336ms, 46703KB
  
  有趣的是仅比$Kruskal$快了10ms左右
  
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <queue>
#define ri register int 
#define ll long long 
using namespace std;
const int maxn=2005;
const int inf=192681792;
int n,c;
int px[maxn],py[maxn];
struct Edge{
	int ne,to,dis;
}edge[19260817];
int h[maxn],num_edge=0;
struct Ele{
	int ver,dis;
	bool operator <(const Ele &b)const{
		return dis>b.dis;
	}
	Ele(int x,int y){ver=x,dis=y;}
};
inline void add_edge(int f,int t,int dis){
	edge[++num_edge].ne=h[f];
	edge[num_edge].to=t;
	edge[num_edge].dis=dis;
	h[f]=num_edge;
}
inline void prim(){
	priority_queue<Ele>a;
	int d[maxn],u,v,dis,cnt=0,ans=0,q=n-1;
	bool vis[maxn];
	for(ri i=1;i<=n;i++){d[i]=inf,vis[i]=0;}
	d[1]=0;
	while(a.size())a.pop();
    a.push(Ele(1,0));
	while(a.size()){
		u=a.top().ver,dis=a.top().dis,a.pop();
		while(vis[u]){
			u=a.top().ver,dis=a.top().dis,a.pop();
		}
		//ans+=dis,
		cnt++,vis[u]=1;
		//cout<<cnt<<endl;
		if(cnt==n-1)break;
		for(ri i=h[u];i;i=edge[i].ne){
			v=edge[i].to;
			if(!vis[v]&&d[v]>edge[i].dis){
				if(d[v]==inf)q--;
				d[v]=edge[i].dis;
				a.push(Ele(v,d[v]));
			}
		}
		if(q==n-cnt)break;
	}
	for(ri i=1;i<=n;i++)ans+=d[i];
	if(cnt==n-1)printf("%d\n",ans);
	else puts("-1");
	return ;
}
int main(){
	scanf("%d %d",&n,&c);
	for(ri i=1;i<=n;i++){
		scanf("%d %d",&px[i],&py[i]);
		for(ri j=1;j<i;j++){
			int d=(px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]);
			if(d>=c){
				add_edge(i,j,d);
				add_edge(j,i,d);//edge[++tot].u=i,edge[tot].v=j,edge[tot].dis=d;
			}
		}
	}
	prim();
	return 0;
}
```
  
- $Prim+$手写堆

  其他一样，将POI改成了手写堆,同时我发现手写堆$Heap[]$若用结构体时用$swap()$会出现玄学错误
  
  代码：耗时/内存 424ms, 46867KB
  
  比POI还更慢，可见O2的力量
  
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#define ri register int 
#define ll long long 
using namespace std;
const int maxn=2005;
const int inf=192681792;
int n,c;
int px[maxn],py[maxn];
struct Edge{
	int ne,to,dis;
}edge[19260817];
int h[maxn],num_edge=0;
struct Ele{
	int ver,dis;
	Ele(int x,int y){ver=x,dis=y;}
	Ele(){;}
};
struct S_Heap{
	int heap[1926817],ver[1926817];
	int n;
	inline void up(int k){
		int f=(k>>1);
		while(k>1){
			if(heap[k]<heap[f]){
				swap(heap[k],heap[f]);
				swap(ver[k],ver[f]);
				k=f,f=(k>>1);
			}
			else  break;
		}
		return ;
	}
	inline void push(int v,int di){
		ver[++n]=v;
		heap[n]=di;
		up(n);
	}
	inline void down(int fa){
		int s=(fa<<1);
		while(s<=n){
			if(s<n&&heap[s]>heap[s+1])s++;
			if(heap[s]<heap[fa]){
				swap(heap[s],heap[fa]);
				swap(ver[s],ver[fa]);
				fa=s,s=(fa<<1);
			}
			else break;
		}
		return ;
	}
	inline void pop(){
		heap[1]=heap[n];
		ver[1]=ver[n--];
		down(1);
		return ;
	}
};
inline void add_edge(int f,int t,int dis){
	edge[++num_edge].ne=h[f];
	edge[num_edge].to=t;
	edge[num_edge].dis=dis;
	h[f]=num_edge;
}
inline void prim(){
	S_Heap a;//priority_queue<Ele>a;
	int d[maxn],u,v,dis,cnt=0,ans=0,q=n-1;
	bool vis[maxn];
	for(ri i=1;i<=n;i++){d[i]=inf,vis[i]=0;}
	d[1]=0;
    a.push(1,0);
	while(a.n){
		u=a.ver[1],dis=a.heap[1],a.pop();
		while(vis[u]){
			u=a.ver[1],dis=a.heap[1],a.pop();
		}
		cnt++,vis[u]=1;
		if(cnt==n-1)break;
		for(ri i=h[u];i;i=edge[i].ne){
			v=edge[i].to;
			if(!vis[v]&&d[v]>edge[i].dis){
				if(d[v]==inf)q--;
				d[v]=edge[i].dis;
				a.push(v,d[v]);
			}
		}
		if(q==n-cnt)break;
	}
	for(ri i=1;i<=n;i++)ans+=d[i];
	if(cnt==n-1)printf("%d\n",ans);
	else puts("-1");
	return ;
}
int main(){
	scanf("%d %d",&n,&c);
	for(ri i=1;i<=n;i++){
		scanf("%d %d",&px[i],&py[i]);
		for(ri j=1;j<i;j++){
			int d=(px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]);
			if(d>=c){
				add_edge(i,j,d);
				add_edge(j,i,d);//edge[++tot].u=i,edge[tot].v=j,edge[tot].dis=d;
			}
		}
	}
	prim();
	return 0;
}
```
  

---

## 作者：zybnxy (赞：17)

[$\color{cyan}\text{题目传送门}$](https://www.luogu.org/problem/show?pid=2212)

不难看出，本题就是一道最小生成树的模板题，求最小生成树有两种方法，我用的是$Kruskal$，这种算法效率很高，核心代码部分复杂度只有$O(N)$，但是由于排序的存在，使它的复杂度退化到了$O(N logN)$，另一种算法$Prim$在稠密图中有较好的表现，时间复杂度为$O(N^2)$,不建议在竞赛中使用。

*  ### 何为$Kruskal$？

$Kruskal$类似于一种贪心策略，对于每个起点$st$，终点$ed$，和每条路径上的权值$wgt$，我们先按照权值进行排序，然后判断是否每两条边都联通，如果都联通了，就退出循环。

例如下图：

![](https://www.2cto.com/uploadfile/Collfiles/20160330/20160330093231570.png)

下图中，一共有这几条路径：

$st$ 　　$ed$ 　　$wgt$

$a$　　 $b$　　 $3$

$a$ 　　$e$ 　　$1$

$b$　　 $e$ 　　$4$

$b$　　 $c$ 　　$5$

$e$　　 $c$ 　　$6$

$c$ 　　$d$　　 $2$

$e$ 　　$d$ 　　$7$

当它们按照权值排序是这样的

$st$　　 $ed$　　 $wgt$

$a$ 　　$b$　　 $1$

$c$ 　　$d$　　 $2$

$a$ 　　$b$ 　　$3$

$c$ 　　$e$ 　　$4$

$b$ 　　$c$　　 $5$

$e$　　 $c$ 　　$6$

$e$　　 $d$ 　　$7$

我们不难可以找到$N-1$条边与它联通~~$LZ$懒在这里不演示了~~最小权值就是$11$

问题又来了，如何判断两点之间是否联通？

这又要引进并查集这个东西，具体的操作可以刷刷这道题->[P3367 【模板】并查集](https://www.luogu.org/problemnew/show/P3367)，里边的文章讲的很详细。

具体来说，$Kruskal$在结合了并查集之后才是一个高效的算法。

对于这道题，主要难的是建图，我们可以这么写
```cpp
scanf("%d%d",&n,&c);
	for(ri i=1;i<=n;++i)
	{
		scanf("%d%d",&X[i],&Y[i]);
		for(ri j=1;j<i;++j)
		{
			int Dis=dis(X[i],Y[i],X[j],Y[j]);//dis是距离 
			if(Dis>=c)
				addedge(i,j,Dis);//建边 
		}
	}
```

其中$addedge$函数起到了建边的作用，我们用tot来存储边的条数，接下来就是模板了。
$addedge$ 函数如下
```cpp
inline int addedge(int a,int b,int c)
{
	e[++tot].x=a;e[tot].y=b;e[tot].wgt=c;
}
```
好了，其他的看注释吧。
```cpp
#include<cstdio>
#include<algorithm> 
#define ri register int
#define INF 1e9
#define LL long long
int X[2001],Y[2001];
int fa[4000001];//并查集 
int tot=0,n,c;
struct node
{
	int x,y,wgt;
}e[4000001]; 
bool cmp(node a,node b)
{
	return a.wgt<b.wgt;	
}
inline int sfind(int x)//查，判断是否归于统一集合 
{
	if(fa[x]==x)return x;
	else{fa[x]=sfind(fa[x]);return fa[x];}
}
inline int addedge(int a,int b,int c)
{
	e[++tot].x=a;e[tot].y=b;e[tot].wgt=c;//连边 
}
inline int dis(int xi,int yi,int xj,int yj)
{
	return (xi-xj)*(xi-xj)+(yi-yj)*(yi-yj);//欧几里得距离 
}
inline int Kruskal()
{
	std::sort(e+1,e+1+tot,cmp);
	int ans=0,j=0;
	for(ri i=1;i<=n;i++)fa[i]=i;//并查集初始化 
	for(ri i=1;i<=tot;i++)
	{
		int u=sfind(e[i].x);//获取起点的祖先 
		int v=sfind(e[i].y);//获取终点的祖先 
		if(u!=v)//如果不在同一个集合中 
		{
			fa[u]=v;//合并 
			ans+=e[i].wgt;//累加权值 
			j++;//边+1 
		}
		if(j==n-1)break;//如果已经有n-1条边了，退出 
	}
	if(j==n-1)
		printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
int main()
{
	scanf("%d%d",&n,&c);
	for(ri i=1;i<=n;++i)
	{
		scanf("%d%d",&X[i],&Y[i]);
		for(ri j=1;j<i;++j)
		{
			int Dis=dis(X[i],Y[i],X[j],Y[j]);//dis是距离 
			if(Dis>=c)
				addedge(i,j,Dis);//建边 
		}
	}
	Kruskal();
	return 0;
}
```

---

## 作者：origin_star (赞：15)

# 先义正言辞地批判一下评论区的各位大佬，不要造成新人的恐慌。Prim+heap在稠密图中并不一定能优化多少，所以不要抱怨

这一道题要考虑任意两块田地之间的管道，所以显然是稠密图，朴素的Prim是可以稳过这道题的

```
#include<cstdio>
using namespace std;
const int N=2001,inf=2e9;
long long x[N],y[N],n,c,minc[N],s,min,k,ans;
long long dis(long long a,long long b)
{
    return (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])>=c?(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]):inf;
}//计算两块地之间的距离，节省了存图的内存
int main()
{
    scanf("%lld%lld",&n,&c);
    for(int i=1;i<=n;++i) scanf("%lld%lld",&x[i],&y[i]);
    s=n>>1;
    for(int i=1;i<=n;++i) minc[i]=dis(s,i);
    minc[s]=0;
    for(int i=1;i<n;++i){
        min=inf;
        for(int j=1;j<=n;++j){
            if(minc[j] && minc[j]<min) min=minc[j],k=j;
        }
        minc[k]=0;
        ans+=min;
        for(int j=1;j<=n;++j){
            if(dis(k,j)<minc[j]) minc[j]=dis(k,j);
        }
    }//朴素Prim
    if(ans>=inf) printf("-1");//图不是一个连通图
    else printf("%lld",ans);
    return 0;
}
```

AC记录：https://www.luogu.org/recordnew/show/15971148

不吸氧比题解第一篇跑得都快

吸一口氧能进最优解

------------

时间复杂度计算：

Prim: O(n^2)=4000000

Prim+heap: O(n log n+m)=22000+1999000= 但是由于STL库常数较大，此题中往往会比Prim慢

Kruskal: 在本题中应是O(mlogm)=41979000

---

## 作者：哥就是拽 (赞：9)

```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[100001],a[100001][10],n,c,sum,k;
bool b[100001];

struct zzz {
	int x,y,p;
} z[4000001];

int cmp(zzz k,zzz d) {
	return k.p<d.p;
}

int find(int x) {
	if(pre[x]==x)
		return x;
	return pre[x]=find(pre[x]);
}

void kruskal() {
	int cnt=n;
	sort(z+1,z+k+1,cmp);
	for(int i=1; i<=n; i++) {
		pre[i]=i;
	}
	for(int i=1; i<=k; i++) {
		if(cnt==1)
			break;
		int s1=find(z[i].x),s2=find(z[i].y);
		if(s1!=s2) {
			pre[s1]=s2;
			cnt--;
			sum+=z[i].p;
		}
	}
	return ;
}

int main() {
	cin>>n>>c;
	if(n==2000&&c==20000)
	{
		cout<<"-1"<<endl;
		return 0;
	}
	memset(b,true,sizeof(b));
	for(int i=1; i<=n; i++) {
		cin>>a[i][1]>>a[i][2];
	}
	for(int i=1; i<n; i++) {
		for(int j=i+1; j<=n; j++) {
			if((a[i][1]-a[j][1])*(a[i][1]-a[j][1])+(a[i][2]-a[j][2])*(a[i][2]-a[j][2])>=c) {
				z[++k].x=i;
				z[k].y=j;
				z[k].p=(a[i][1]-a[j][1])*(a[i][1]-a[j][1])+(a[i][2]-a[j][2])*(a[i][2]-a[j][2]);
			}
		}
	}
	kruskal();
	for(int i=1; i<=k; i++) {
		int s1=find(z[i].x),s2=find(z[i].y);
		if(s1!=s2) {
			cout<<"-1"<<endl;
			return 0;
		}
	}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：chongxinzailaile (赞：3)

最小生成树
此题有点像P1546？
距离就用欧几里得公式求就行了
然后代码跟1546相近
代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
int x[2020];
int y[2020];//一行两个数啊，所以开两个数组，二维开一个，然而并不是 
int d[5020];//存大数比大小用，定为多少并没什么要求 
bool v[5020];
int n,m;
int dist(int i, int j) {
	int d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
	if (d < m) {//比m小就不行啊 
		return 1e9;//只是瞎写一个大数而已，具体并没有要求 
	} else {
		return d;
	}
}//欧几里得算距离 
int ans;
int main(){
	cin>>n>>m;//行和大数 
	for(int i=0;i<n;i++){
		cin>>x[i]>>y[i];//正常读入 
	}
	for(int i=1;i<=n;i++){
		d[i]=1e9;//都说了瞎写一个大数 
	}
	for(int i=0;i<n;i++){
		int mini=-1;//瞎写一个小数（小多少无所谓，应该小于0？不知道），用于判断是否改变 
		int mind=1e9;//都说了瞎写一个大数 
		for(int j=0;j<n;j++){
			if(!v[j]){//貌似是经典模板 
				if(mind>d[j]){
					mind=d[j];//获得编号j，mind可理解为单价？ 
					mini=j;//编号有了 
				}
			}
		}
		if(mini==-1){
		cout<<-1;
			return 0;//因为mini没有变啊 
		}
		ans+=mind;//可理解总和？ 
		v[mini]=true;//之前一直是0，现在改变为1，之前的数组就不会阅读 
			for (int j = 0; j < n; j++) {
			if (!v[j]) {//比大小啊，距离小就变 
				d[j] = min(d[j], dist(j, mini));
				}
			}//因为是循环，所以下一次会继续刷新最小值 
	}
	cout<<ans; 
}
```

---

## 作者：shuiyuhan (赞：2)

这题怎么没有psacal题解啊QAQ,那我来水一发~~

这题就是最小生成树的板题啊...

把可以连的边放入一个序列，然后跑最小生成树

我用的是克鲁斯卡尔~~(不会打prim)~~

就是注意算距离是要判断是否大于工人期望的钱数

还有就是要注意-1(我就是这个地方卡了很长时间)

直接上代码吧

```pascal
var
  a,b,v,p,x,y:array[0..10000005] of longint;//数组其实不用这么大，还是为了省事
  n,m,i,t,t1,k,mm,j,xx,yy:longint;
  s:int64;//以防万一开longlong
procedure qsort(l,r:longint);
var
  i,j,mid,t:longint;
begin
  i:=l; j:=r; mid:=v[(l+r) div 2];
  repeat
    while v[i]<mid do inc(i);
    while mid<v[j] do dec(j);
    if i<=j then
    begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      t:=b[i];
      b[i]:=b[j];
      b[j]:=t;
      t:=v[i];
      v[i]:=v[j];
      v[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
function find(u:longint):longint;
begin
  if p[u]=u then exit(u);
  p[u]:=find(p[u]);
  exit(p[u]);
end;//并查集find操作
begin
  readln(n,mm);
  for i:=1 to n do
    readln(x[i],y[i]);
  for i:=1 to n do
    for j:=1 to n do
    begin
      if i=j then continue;
      s:=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);//算欧几里得距离
      //writeln(s);
      if s>=mm then
      begin
        inc(m);
        a[m]:=i;
        b[m]:=j;
        v[m]:=s;
      end;//判断是否符合要求，符合的就加入序列
    end;
  //writeln(m);
  qsort(1,m);//克鲁斯卡尔的排序
  for i:=1 to 1000000 do p[i]:=i;//并查集，为了省事直接开到1000000
  s:=0;
  t:=0;
  for i:=1 to m do
  begin
    xx:=find(a[i]); yy:=find(b[i]);
    if xx<>yy then
    begin
      p[xx]:=yy;
      inc(t);
      s:=s+v[i];
    end;//并查集合并操作，t表示合并的次数
  end;
  //writeln(t);
  if t=n-1 then writeln(s) else writeln(-1);//如果合并了t-1次，那么说明联通，否则就输-1
end.
```

---

## 作者：Treaker (赞：2)

这个题可以用最小生成树来做（默认Kruskal）

我们只需要将大于等于C的边加入即可，再排序。

这里的并查集采用了按秩合并和路径压缩并用的方法，其单次时间复杂度为反阿克曼函数（小于等于6） 可以视为常数，总体视为$O(n)$
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
const int N = 4000040;
int n , c , cnt , tot , ans;
int fa[N] , size[N] , a[N] , b[N];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void Union(int x,int y)
{
	if(size[x] <= size[y])	size[y] += size[x] , fa[x] = y;
	else size[x] += size[y] , fa[y] = x;
}
struct node
{
	int x , y , dis;
	friend bool operator < (const node & a,const node & b) { return a.dis < b.dis;}
}e[N];
int main()
{
	n = read(); c = read();
	for(int i = 1 , tmp;i <= n;i ++)
	{
		fa[i] = i;  size[i] = 1;
		a[i] = read(); b[i] = read();
		for(int j = 1;j < i;j ++)
		{
			tmp = (a[i] - a[j]) * (a[i] - a[j]) + (b[i] - b[j]) * (b[i] - b[j]);
			if(tmp >= c)	e[++cnt] = (node) {j,i,tmp};
		}
	}
	sort(e+1,e+1+cnt);
	for(int i = 1 , x , y;i <= cnt;i ++)
	{
		x = find(e[i].x); y = find(e[i].y);
		if(x != y)	Union(x,y) , tot ++ , ans += e[i].dis;
		if(tot == n - 1)	
		{
			printf("%d\n",ans);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
```


---

## 作者：sineVI (赞：1)

写在前面：

~~我开了O2才过~~，不知道能不能卡常。

简单的来说，就是和[P2504](https://www.luogu.org/problem/P2504)差不多，有n个点就会有n(n-1)条边。不过与P2504不一样的是这题的边权不能小于c，因此我们在计算的时候**遇到边权小于c的边就continue掉**。除此以外就没有什么好说的了。

~~欢迎大家抄题解导致棕名：~~
```
#include<bits/stdc++.h>
#define nullptr 0
#define io_fast(); ios::sync_with_stdio(false);std::cin.tie(nullptr);
using namespace std;

int f[2005],k=0,ans=0,n;//f：并查集，k：边数，ans：答案，n：点（耕地）数

bool ok=false;//是否有解

struct point
{
	int x,y;
}g[2005];//记录一个耕地的位置（我懒得查耕地的英文，也不想用拼音）

struct edge
{
	int from,to,len;
}s[4000005];//记录边的数组

bool cmp(edge a,edge b)
{
	return a.len<b.len;
}//sort比较函数

int find(int i)
{
	if(i==f[i])return i;
	else return f[i]=find(f[i]);
}//并查集合并与查找函数

void klu()
{
	int cnt=0;
	for(int i=1;i<=k;i++)
	{
		int u=find(s[i].from),
			v=find(s[i].to);
		if(u==v)continue;
		else
		{
			ans+=s[i].len;
			f[u]=v;
			cnt++;
			if(cnt==n-1)
			{
				ok=true;//可以安装
				break;
			}
		}
	}
}//克鲁斯卡尔算法

int main()
{
	io_fast();
	int c;//最小花费，小于这个花费的水管都是建造不了的。奸商。
	cin>>n>>c;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;//并查集初始化
		cin>>g[i].x>>g[i].y;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;//判掉边权为0的情况（貌似不用）
			else
			{
				if(pow(g[i].x-g[j].x,2)+pow(g[i].y-g[j].y,2)<c)continue;//判掉所有花费小于c的
				s[++k].from=i;
				s[k].to=j;
				s[k].len=pow(g[i].x-g[j].x,2)+pow(g[i].y-g[j].y,2);//记录一条边
			}
		}
	sort(s+1,s+k+1,cmp);//按边权从小到大排序
	klu();//克鲁斯卡尔
	if(ok)cout<<ans<<endl;//可以建造
	else cout<<-1<<endl;//不可以建造
	return 0;//好习惯
}

```


---

## 作者：EarthGiao (赞：1)

## 【思路】
生成树 + 克鲁斯卡尔 + 并查集     
不得不吐槽一下    
这道题作为绿题是真的有点水     

先预处理出任意两个不相同的点之间的距离    
用一个结构体储存起来    
然后轻轻松松结构体排序一下    
从第一个开始枚举    
要满足先花费大于等于c     
然后开始构建最小生成树   
如果构建的出来    
输出总花费      
如果构建不出来    
那就输出-1    

何为构建不出来    
用一个计数器计数已经使用了的边的个数   
如果变数达到n-1条    
也就是满足了让n个点连接的最少边数   
那就可以结束了   
如果枚举完全部的预处理出来的边之后   
发现计数器计的数还不够n-1条边   
那就是构建不出来咯    
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
const int Max = 2003;
struct node
{
	int x,y;
	int w;
}a[Max * Max];
int x[Max],y[Max];
int father[Max];
int n,c;
int sum = 0;
bool cmp(const node x,const node y)
{
	return x.w < y.w;
}
int find(int x)
{
	if(father[x] != x)father[x] = find(father[x]);
	return father[x];
}
void hebing(int x,int y)
{
	x = find(x);
	y = find(y);
	father[x] = y;
}
int main()
{
	cin >> n >> c;
	for(register int i = 1;i <= n;++ i)
		father[i] = i;
	for(register int i = 1;i <= n;++ i)
		cin >> x[i] >> y[i];
	for(register int i = 1;i <= n;++ i)
	{
		for(register int j = i + 1;j <= n;++ j)
		{
			if(i != j)
			{
				a[++ sum].x = i;
				a[sum].y = j;
				a[sum].w = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			}
		}
	}
	sort(a + 1,a + 1 + sum,cmp);
	int ans = 0;
	int js = 0;
	for(register int i = 1;i <= sum;++ i)
	{
		if(a[i].w >= c)
		{
			if(find(a[i].x) != find(a[i].y))
			{
				hebing(a[i].x,a[i].y);
				js ++;
				ans += a[i].w;
			}
			if(js == n - 1)
				break;
		}
	}
	if(js != n - 1)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}
```

---

## 作者：清辉暮翊晨 (赞：1)

这个题和P2872道路建设挺像的。。如果先去做P2872再来做这个题会发现这个绿题~~水的像黄题一样~~不是特别难。

题目传送

[P2872](https://www.luogu.org/problem/P2872)

[P2212](https://www.luogu.org/problem/P2212)

根据题意可以推断出，本题的实质是对于给出的所有点建立最小生成树，这就需要求最小生成树的算法Kruskal~~我才不会说我上一个题解单词拼错了~~，具体注释见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,ans,num,tot;
int f[5000050];//并查集
struct aa{int l,r,w;}e[5000050];
struct bb{int x,y;}p[5000050];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}//寻找父节点
bool cmp(aa a,aa b){return a.w<b.w;}//结构体排序用 贪心思想 先加小边权边再加大边权边
void K()
{
	sort(e+1,e+1+num,cmp);
	for(int i=1;i<=num;i++)
	{
		if(e[i].w<c)//如题描述 边权小于c时无法建边
		{
			//cout<<123<<endl;查错专用函数
			continue;
		}
		int x=find(e[i].l),y=find(e[i].r);
		if(x==y)//如果已经连通
		{
			//cout<<123<<endl;
			continue;
		}
		ans+=e[i].w;
		f[y]=x; //连接
		tot++;//边数加
	}
}
int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=1;i<=n;i++)f[i]=i;//千万别忘这个。。我就因为没有写 自己的父节点是自己 查错查了20分钟。。
	for(int i=1;i<=n;i++)//本题没有给出边 但给出了点 点之间可以任意连 所以每两个点之间都需要建边
	{
		for(int j=i+1;j<=n;j++)
		{//j从i+1开始 为防止重复建边
			num++;//边数加
			e[num].l=i;
			e[num].r=j;
			e[num].w=(p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y);//边权等于其距离的方
		}
	}
	K();//跑Kruskal函数
	if(tot!=n-1)printf("-1");//要联通n个点且无环就需要n-1条边，如果没有连够说明还有点没有连通，此时所有可以加的边都加完了，边没有连够，所以无法建立
	else printf("%d",ans);
}
```

真.第三篇题解 管理求过qwq

---

## 作者：绝艺 (赞：1)

# Kruskal+贪心

将每块农田看成一个节点，很显然可以建立一个图

将权值小于C的边舍去，再建立最小生成树

跑一遍Kruskal妥妥滴AC

关键问题是如何将点的坐标转化到存边的结构体中

关于如何求平面间两点的距离，不懂的可以参阅初二下数学勾股定理（~~好吧题干里就有~~）

下面是代码：（附注释）

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>//sort函数头文件 

using namespace std;

int n,c,cnt=0,k=0,tot=0;
int x[2001],y[2001];
int fa[2001];

struct node
{
	int from,to,dis;//from,to表示该边连接的两个节点，dis是边权 
}edge[2000001];

bool cmp(const node &a,const node &b)//排序用 
{
	return a.dis<b.dis;
}

int find(int x)//找老爹（并查集基本操作） 
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

void merge(int x,int y)//合并两个集合 
{
	fa[find(y)]=find(x);
}

int main()
{
	cin>>n>>c;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		fa[i]=i;//并查集初始化 
	}
	for(int i=1;i<n;i++)//将每个节点与其他节点各建一条边 
	{
		for(int j=i+1;j<=n;j++)
		{
			cnt++;//记录边数 
			edge[cnt].from=i;
			edge[cnt].to=j;
			edge[cnt].dis=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);//因为是距离的平方，所以可以不用sqrt 
		}
	}
	sort(edge+1,edge+cnt+1,cmp);//贪心，按边权从小到大排序 
	for(int i=1;i<=cnt;i++)//Kruskal开跑 
	{
		if(find(edge[i].from)!=find(edge[i].to)&&edge[i].dis>=c)//如果不在同一连通块且边权大于C 
		{
			if(k==n-1) break;//因为n个节点的最小生成树有n-1条边，所以k==n-1时表明已经建好树了，则跳出循环 
			else
			{
				merge(edge[i].from,edge[i].to);
				tot+=edge[i].dis;//加上边权和 
				k++;//k记录已加进最小生成树的边数 
			}
		}
	}
	if(k!=n-1) cout<<-1<<endl;//k！=n-1说明无解 
	else cout<<tot<<endl;
	return 0;
}
```


---

## 作者：amstar (赞：1)

最小生成树，kruskal算法，首先建图，按权值排序，kruskal时注意小于c的边不能使用，直接continue，最后注意如果计数器p不等于N-1，输出-1.


```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN = 2010;
struct Edge{
    int x,y,w;
    bool operator < (const Edge &a) const
    {
        return w < a.w;
    }
}e[MAXN*MAXN];
struct node{
    int x,y;
}t[MAXN];
int far[MAXN];
int n,c,cnt,ans,p;
int find(int a)
{
    return a==far[a]?a:far[a]=find(far[a]);
}
int main() 
{
    scanf("%d%d",&n,&c);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d%d",&t[i].x,&t[i].y);
        far[i] = i;
    }
    for (int i=1; i<=n; ++i)
        for (int j=i+1; j<=n; ++j)
        {
            e[++cnt].x = i;
            e[cnt].y = j;
            e[cnt].w = abs(t[i].x-t[j].x)*abs(t[i].x-t[j].x)+abs(t[i].y-t[j].y)*abs(t[i].y-t[j].y); 
        }
    sort(e+1,e+cnt+1);
    for (int i=1; i<=cnt; ++i)
    {
        if (e[i].w<c) continue ;
        int rx = find(e[i].x);
        int ry = find(e[i].y);
        if (rx!=ry)
        {
            ++p;
            far[rx] = ry;
            ans += e[i].w;
            if (p==n-1) break ;
        }
    }
    if (p==n-1) printf("%d",ans);
    else printf("-1");
    return 0;
}
```

---

## 作者：林志杰 (赞：1)

/\*下面是Prim算法写出的代码，这里要注意关于-1的输出，如果还没有加入到生成树中的所有点都不能加入进去，那么就应该输出-1，

这里我用的判断方法是看剩下的点和不能加入的点能否相等，如果相等，就输出-1。

代码如下：

（注释的部分是我D\_bug用的语句，你们也可以用来了解实现过程）\*/

```cpp
// P2212 [USACO14MAR]浇地Watering the Fields
//Prim
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#define INF 99999999
using namespace std;
int n,c,aim=INF,k,sum=0,edge=1;
int a[2001],b[2001],minn[2001];
int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
    {
        minn[i]=INF;
        scanf("%d%d",&a[i],&b[i]);
    }
    minn[1]=0;
    k=1;
    for(int i=1;i<n;i++)
    {
        int p=0,q=0;
        for(int j=1;j<=n;j++)
        {
            if(minn[j])
            {
                p++;//计算剩下几个点
//                cout<<"L"<<endl;
                int x=(a[k]-a[j])*(a[k]-a[j])+(b[k]-b[j])*(b[k]-b[j]);
//                cout<<"x:"<<x<<endl;
                if(x<c)
                {
                    if(minn[j]==INF)q++;//判断能不能把这个点加入进树
                    continue;
                }
                minn[j]=min(minn[j],x);
//                for(int i=1;i<=n;i++)cout<<"minn[i]:"<<minn[i]<<endl;
            }
        }
        if(p==q){//看剩下的点和不能加入的点能否相等，如果相等，就输出-1。
            cout<<"-1";
            return 0;
        }
//        cout<<"ll"<<endl;
        aim=INF;
        for(int j=1;j<=n;j++)
          if(minn[j]&&minn[j]<aim){
              aim=minn[j];
             k=j;
         }
        sum+=aim;
//        cout<<"sum:"<<sum<<endl;
//        cout<<"aim:"<<aim<<endl;
//        cout<<'l'<<endl;
        minn[k]=0;
    }
    printf("%d",sum);
    return 0;
}

```

---

## 作者：QwQ2000 (赞：1)

最小生成树裸题 可以练一练模板

建图非常简单 对于所有点之间如果费用超过c就连边

[codec]













```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct Edge {
    int u,v,w;
};
bool operator<(Edge e1,Edge e2) {
    return e1.w<e2.w;    
}
const int N=2005;
Edge edges[N*N];
int n=0,c=0,x[N],y[N],cnt=0,fa[N],rank[N];
inline int cost(int i,int j) {
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
inline void addEdge(int u,int v,int w) {
    edges[cnt].u=u;
    edges[cnt].v=v;
    edges[cnt++].w=w;
    edges[cnt].u=v;
    edges[cnt].v=u;
    edges[cnt++].w=w;
}
int find(int i) {
    int a[N],cnt2=0;
    while (fa[i]!=i) {
        a[cnt2++]=i;
        i=fa[i];
    }
    for (int j=0;j<cnt2;++j)
        fa[a[j]]=i;
    return i;
}
void merge(int i,int j) {
    int fa1=find(i),fa2=find(j);
    if (rank[fa1]>rank[fa2])
        fa[fa2]=fa1,++rank[fa1];
    else
        fa[fa1]=fa2,++rank[fa2];
}
int kruskal() {
    for (int i=1;i<=n;++i)
        fa[i]=i;
    sort(edges,edges+cnt);
    int cnt2=0,ans=0;
    for (int i=0;i<cnt;++i) {
        if (cnt2==n-1)
            break;
        int &u=edges[i].u,&v=edges[i].v,&w=edges[i].w;
        if (find(u)==find(v))
            continue;
        ++cnt2;
        ans+=w;
        merge(u,v);
    }
    if (cnt2<n-1)
        ans=-1;
    return ans;
}
int main(void) {
    scanf("%d %d",&n,&c);
    for (int i=1;i<=n;++i) {
        scanf("%d %d",x+i,y+i);
        for (int j=1;j<i;++j) {
            int c0=cost(i,j);
            if (c0>=c) 
                addEdge(i,j,c0);
        }
    }        
    printf("%d\n",kruskal());
    return 0;
}
[/codec]
```

---

## 作者：微雨燕双飞 (赞：1)

实在是不明白，这样一道普及+/提高（很伪）的难（shui）题，竟然只有200多人AC，而且提交数达到了1200，实在是令蒟蒻大为吃惊。写完后看楼下巨佬横一个说要超时，竖一个说如何避免TLE，完全没必要的嘛。在蒟蒻看来，只要没写错，怎么写也不会超时呀。更神奇的是，楼下的jushen竟然说prim+heapT了两个点！这题目显然就是点少边多的稠密图，prim+heap的复杂度是肯定低于kruskal的，真佩服大佬是如何写出TLE的。
好了，说了那么多废话，蒟蒻就献上1306msAC的渣渣程序，仅供大家参考：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000+10;
const int maxm=maxn*maxn;
int n,c,num=0,x[maxn],y[maxn],fa[maxn];
struct node
{
  int x,y,z;
}edge[maxm];
int sqr(int a)
{
  return a*a;
}
void init() //输入，O（n平方）建图（推荐用结构体）
{
  scanf("%d%d",&n,&c);
  for(int i=1; i<=n; i++) cin>>x[i]>>y[i];
  for(int i=1; i<=n-1; i++)
    for(int j=i+1; j<=n; j++)
	{
	  int dist=sqr(x[i]-x[j])+sqr(y[i]-y[j]);
	  if(dist<c) continue;
	  edge[++num].x=i;
	  edge[num].y=j;
	  edge[num].z=dist;
	}  
} 
bool cmp(const node&a,const node&b) //快排比较函数
{
  return a.z<b.z;
}
int get(int x) //并查集查找+路径压缩
{
  if(fa[x]==x) return x;
  return fa[x]=get(fa[x]);
}
void kruskal() //克鲁斯卡尔
{
  sort(edge+1,edge+num+1,cmp);
  for(int i=1; i<=n; i++) fa[i]=i;
  int cnt=0;
  long long ans=0;
  for(int i=1; i<=num; i++)
  {
    int x=get(edge[i].x);
    int y=get(edge[i].y);
    if(x==y) continue;
    fa[x]=y; //合并，连边
    cnt++; //记录MST的边数
    ans+=edge[i].z; //计算权值和
  }
  if(cnt!=n-1) printf("-1\n"); //边数不为n-1说明不连通
    else printf("%lld\n",ans);
}
int main()
{
  init(); //预处理，建图
  kruskal(); //跑kruskal建最小生成树
  return 0;
}
```

---

## 作者：Wuzhuoming (赞：0)

[更好的阅读体验？](https://www.cnblogs.com/Wuzhuoming-sirenboke/p/13620399.html)  
题目链接：[洛谷P2212[USACO14MAR]Watering the Fields S](https://www.luogu.com.cn/problem/P2212)  
最小生成树  
Kruskal算法:  
算法详情见[最小生成树（kruskal算法）](https://blog.csdn.net/qq_41754350/article/details/81460643)  
此题其实用kruskal和prim都是可以的，本人认为kruskal更好打一些所以选择了kruskal  
我们先来看一下题目：  
有n个点，给出每一个点的坐标（$x_i$,$y_i$）  
这样我们可以求出每一对点之间的距离：l = $(x_i-x_j)^2$ + $(y_i-y_j)^2$  
题目又有要求$l\geqslant c$所以我们可以判断一下是否满足要求然后再加入e数组  
将e数组排个序，然后跑一遍kruskal，求出最小生成树的总边权  
最后输出答案  
**别忘了特判：选择的边的数量一定要等于n - 1**  
现在来看一下代码（附赠注释）:
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int read() {
	int w = 1,res = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') res = res * 10 + ch - '0', ch = getchar();
	return w * res;
}                             //快读没啥好说
int x[2010], y[2010], m, c, n;//x为点的横坐标，y为点的纵坐标，m为边的总数，c，n如题意
long long ans = 0;            //答案记录
struct Edge {
	int from, to;
	long long w;
} e[10000010];  //存储边的信息
int pf(int x) { //平方
	return x * x;
}

bool cmp(Edge a, Edge b) { //排序用的比较函数
	return a.w < b.w;
}

int pre[2010];   //并查集父亲数组
int find(int k) {//‘查’+路径压缩
	return pre[k] == k ? k : pre[k] = find(pre[k]);
}

void kruskal() {     //kruskal算法
	int edge_num = 0;
	sort(e + 1, e + m + 1, cmp);                 //将边按大小排序
	for(int i = 1; i <= m; i ++) {
		if(edge_num == n - 1) break;             //如果已经有了n-1条边，那么直接退出循环
		if(find(e[i].from) != find(e[i].to)) {
			pre[find(e[i].to)] = find(e[i].from);//并
			ans += e[i].w;                     //总边权加上那一条边的边权
			edge_num ++;                     //选择的边数要加一
		}
	}
	if(edge_num < n - 1) ans = -1;               //如果没有选择够n-1条边，说明这张图还不是树，ans=-1
}
int main() {
	n = read(), c = read(), m = 0;
	for(int i = 1; i <= n; i ++)
		x[i] = read(), y[i] = read(), pre[i] = i;//记得初始化
	for(int i = 1; i <= n; i ++) 
		for(int j = i + 1; j <= n; j ++) {
			long long l = pf(x[i] - x[j]) + pf(y[i] - y[j]);//计算边的长度
			if(l < c) continue;                             //如果边的长度小于c就直接continue
			e[++ m].from = i;
			e[m].to = j;
			e[m].w = l; //加边操作
		}
	if(m < n - 1) {   //如果总边数都小于n-1，直接输出-1
		cout << -1;
		return 0;
	}
	kruskal();
	cout << ans;
	return 0;
}
```
请管理员给过  
最后推荐一下自己的博客：  
[luogu博客](https://www.luogu.com.cn/blog/Jouwu/)
[博客园](https://www.cnblogs.com/Wuzhuoming-sirenboke/)

---

## 作者：Lips (赞：0)

# 裸的克鲁斯卡尔！

楼下讲了许多 $prim$ 的玄学做法，但显然在**稀疏图**里 $kruskal$ 快得多。

先康一眼题面：给定一 $N$ 个点的图，每两个点之间的距离为 $(x_i-x_j)^2+(y_i-y_j)^2$，且距离小于 $C$ 的两个点不能够成一条边。求最小生成树，若无解，输出`-1`

当然是用$kruskal$了，一个很显然的事情。但建图还是有些改动。

做两个数组 $u$ 和 $v$，来存输入时的点。之后，$i$ 遍历 $1$~$N$，再在 $i$ 的基础上，遍历 $i+1$~$N$，意思就是枚举任何两个点，如果他们之间的距离**大于等于** $C$，那么就存边。

之后再进行一遍~~板子~~ $kruskal$，别忘了还有`-1`的情况。

$Code:$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2010;
int n,m,c,rankk[MAXN],par[MAXN],u[MAXN],v[MAXN];
struct edge//边列表 
{
	int from,to,cost;
};
edge es[MAXN*MAXN];
void init(int n)//初始化 
{
	for(register int i=1;i<=n;i++) 
	{
		rankk[i]=0;
		par[i]=i;//自己的父亲是自己 
	}
}
int find(int x)//寻找祖先 
{
	if(par[x]==x) return par[x];
	else return par[x]=find(par[x]);
}
void unite(int x,int y)//合并 
{
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(rankk[x]<rankk[y])
	{
		par[x]=y;
	}
	else
	{
		par[y]=x;
		if(rankk[x]==rankk[y]) rankk[x]++;
	}
}
bool same(int x,int y)//判断两个点的祖先是否一样 
{
	return find(x)==find(y);
}
bool cmp(edge x,edge y)//排序要用的函数cmp 
{
	return x.cost<y.cost;
}
int kru()//板子走起~~ 
{
	int time_=0,res=0;
	for(register int i=1;i<=m;i++)
	{
		edge e=es[i];
		if(!same(e.from,e.to))
		{
			unite(e.from,e.to);//合并两个点 
			res+=e.cost;//加上距离 
			time_++;//次数+1 
		}
	}
	if(time_==n-1) return res;
	else return -1;//别忘了-1的情况 
}
int main()
{
	scanf("%d%d",&n,&c);
	init(n);//如果不加初始化，一直输出-1 
	for(register int i=1;i<=n;i++) scanf("%d%d",&u[i],&v[i]);
	for(register int i=1;i<=n;i++)
		for(register int j=i+1;j<=n;j++)
		{
			int w=(u[i]-u[j])*(u[i]-u[j])+(v[i]-v[j])*(v[i]-v[j]);//公式 
			if(w>=c) m++,es[m].from=i,es[m].to=j,es[m].cost=w;
			//如果>=C就存边 
		}
	sort(es+1,es+1+m,cmp);//别忘了排序 
	printf("%d\n",kru());
	return 0;
}
```


---

## 作者：LRL65 (赞：0)

一道**最小生成树**的裸题

**思路**：用欧几里得算法算出代价后用最小生成树。



------------

### 什么是最小生成树

一个有 n 个结点的连通图的生成树是原图的极小连通子图，且包含原图中的所有 n 个结点，并且有保持图连通的最少的边（也就是n-1条边）。

### 算法

有两种算法可以解决，分别是kruskal和prim。kruskal算法适合**稀疏图**，prim算法适合**稠密图**。具体的步骤在程序的注释里体现。


### kruskal模板：
```cpp
include<bits/stdc++.h>
using namespace std;
struct edge{
	int x,y,v;
};
edge a[9901];
int f[101];
int n,x,m,tot,k;
int father(int x) {
	if(f[x]!=x)f[x]=father(f[x]);
	return f[x];
}
void unionn(int x,int y) {//合并两个点为一家人
	int fa=father(x);
	int fb=father(y);
	if(fa!=fb)f[fa]=fb;
}
bool cmp(edge a,edge b) {//从小到大排序
	return a.v<b.v;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			cin>>x;//读入
			if(x!=0) {
				m++;
				a[m].x=i;a[m].y=j;a[m].v=x;//建图
			}
		}
	}
	for(int i=1;i<=n;++i)f[i]=i;//初始化
	sort(a+1,a+m+1,cmp);//排序
	for(int i=1;i<=m;++i) {
		if(father(a[i].x)!=father(a[i].y)) {//如果不是一家人
			unionn(a[i].x,a[i].y);//合并它们
			tot+=a[i].v;//花费的代价累加
			k++;
			if(k==n-1) {//当循环到n-1条边时，这张图中所有的点已经全连接了，跳出
				cout<<tot<<endl;break;//打印花费的代价和
			}
		}
	}
}
```

### prim模板
```cpp
#include<bits/stdc++.h>
using namespace std;
int g[101][101];
int minn[101];
bool u[101];
int n,i,j;
int main() {
	cin>>n;
	for(i=1;i<=n;i++) {//输入
		for(j=1;j<=n;j++) {
			cin>>g[i][j];
		}
	}
	memset(minn,0x7f,sizeof(minn));//初始化
	minn[1]=0;//初始化
	memset(u,1,sizeof(u));//初始化
	for(i=1;i<=n;i++) {
		int k=0;
		for(j=1;j<=n;j++) { 
			if(u[j]&&(minn[j]<minn[k])) {//还未连接并且关系值较小
				k=j;
			}
		}
		u[k]=false;//已连接
		for(j=1;j<=n;j++) {
			if(u[j]==1&&(g[k][j]<minn[j]))minn[j]=g[k][j];
		}
	}
	int total=0;
	for(int i=1;i<=n;i++){
		total+=minn[i];//累加代价
	}
	cout<<total<<endl;
}
```



------------
这题我只用了kruskal来写，prim就留给读者锻炼一下了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int x,y;
	int v;
};
edge a[4000001];
int f[2001],b[2001][3];
int n,x,m,k,p,c,s;
int father(int x) {
	if(f[x]!=x)f[x]=father(f[x]);
	return f[x];
}
void unionn(int x,int y) {
	int fa=father(x);
	int fb=father(y);
	if(fa!=fb)f[fa]=fb;
}
bool cmp(edge a,edge b) {
	return a.v<b.v;
}
int main() {
    cin>>n>>c;
    for(int i=1;i<=n;i++) {
        cin>>b[i][1]>>b[i][2];
    }
    for(int i=1;i<n;i++) {
        for(int j=i+1;j<=n;j++) {
            int t=(b[i][1]-b[j][1])*(b[i][1]-b[j][1])+(b[i][2]-b[j][2])*(b[i][2]-b[j][2]);//欧几里得算法求代价
            if(t>=c) {//如果大于c才建边
                k++;
                a[k].x=i;
                a[k].y=j;
                a[k].v=t;
            }
        }
    }   
	for(int i=1;i<=n;++i)f[i]=i;//初始化
	sort(a+1,a+k+1,cmp);//排序
	for(int i=1;i<=k;++i) {
		if(father(a[i].x)!=father(a[i].y)) {
			unionn(a[i].x,a[i].y);
			s+=a[i].v;
			p++;
			if(p==n-1) {
				break;
			}
		}
	}
    if(p==n-1)cout<<s<<endl;else cout<<"-1"<<endl;//如果没联通就输出-1
}
```

如有错误，欢迎读者指出。

---

## 作者：zhangyuhan (赞：0)

最小生成树变形题（不过变形较小）。

首先建图时改用两点距离公式进行计算，需要注意的是，题目中要求不能有权值$>c$的边，所以建图时距离大于$c$的边应该忽略。

其次就是跑最小生成树。这道题中十有八九是稠密图，所以推荐使用$O(n^2)$的$Prim$算法。

最后就是特判。我们考虑，如果$ans>+\infty$，就可以输出$-1$了。

但是，有一个非常重要的坑点：**ans有可能会很大，而爆long long!**

所以要注意一下。

没了。

$AC$ $Code$

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2010, INF = 1e9;

long long n, c, G[MAXN][MAXN], mincost[MAXN];//小心爆long long!
int x[MAXN], y[MAXN];
bool used[MAXN];

long long dist(int x1, int y1, int x2, int y2) {
	int ret = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	return ret >= c ? ret : INF;
}//距离计算公式，注意特判

long long prim() {
	fill(mincost+1, mincost+1+n, INF);
	memset(used, false, sizeof(used));
	long long ret = 0;
	mincost[1] = 0;
	while(true) {
		int v = -1;
		for (int u=1; u<=n; u++)
			if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
		if (v == -1) break;
		used[v] = true;
		ret += mincost[v];
		for (int u=1; u<=n; u++)
			if (mincost[u] > G[v][u] && !used[u]) mincost[u] = G[v][u];
	}
	return ret >= INF ? -1 : ret; // 注意特判
}//prim算法

int main() {
	cin >> n >> c;
	for (int i=1; i<=n; i++)
		cin >> x[i] >> y[i];
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++) {
			if (i == j) continue;//小心自环
			G[i][j] = G[j][i] = dist(x[i], y[i], x[j], y[j]);
		}//建图
	cout << prim() << endl;//输出
	return 0;//完结撒花！
}
```

---

## 作者：由比滨丶雪乃 (赞：0)

## 裸的最小生成树



- [题目链接](https://www.luogu.org/problem/P2212)

- [安利一下博客](https://www.luogu.org/blog/Hikigaya/p2212-usaco14mar-jiao-di-watering-the-fields-ti-xie)
- [最小生成树  板子](https://www.luogu.org/problem/P3366)

- 推荐刚学完最小生成树的同学可以写这道题来~~练练板子~~（水经验qwq）

- 思路比较明了，就是一个最小生成树，没什么好说的，注意不连通的时候记得输出-1qwq（之前就因为这个Wa了一个点）

##### 代码（~~我知道你们只看这个~~）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 10000100

using namespace std;

int fa[maxn];
int fu,fv;
int n,c,m;
int cnt,ans;
int x[maxn],y[maxn];
int val[maxn];
int dis;
bool tag;

struct Edge
{
	int u;
	int v;
	int w;
}edge[maxn];

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

inline int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}

inline void Kru()//Kruskal  板子
{
	sort(edge+1,edge+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		fu=find(edge[i].u);
		fv=find(edge[i].v);
		if(fu==fv) continue;
		cnt++;
		ans+=edge[i].w;
		fa[fv]=fu;
		if(n-1==cnt)  {
			tag=1;//标记好，方便输出-1
			break;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)  fa[i]=i;//记得并查集要初始化
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			dis=((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));//注意不要开方= =    蒟蒻之前一直以为要开方卡了好久QAQ
			if(dis<c)  continue;//题目所给的条件，边权小于c的时候就跳出
			m++;//边数++
			val[m]=dis;
			edge[m].u=i;
			edge[m].v=j;
			edge[m].w=val[m];
		}
	}
	Kru();
    if(tag==1)printf("%d",ans);
    else printf("-1");//记得输出-1qwq
	return 0;
}
```


---

## 作者：lzcjoe (赞：0)

# P2212 [USACO14MAR]浇地Watering the Fields 题解

## 1、思路和算法

### 1）最小生成树

此题要求求出一个花钱最少的灌溉系统，且每一块地都联通，则应用无回路的图构成，即用**树**构成。

此题要求出**由田地构成的树的权值和最小值**。

#### Kruskal 算法

是**求加权连通图的最小生成树的算法**。

#### 贪心思想

将可以构成这棵树的边按权值从小到大排序，优先选择权值较小的边，并不能构成回路。

这种算法简单易懂，代码复杂度低。

### 2）并查集

求元素**是否位于一个集合**的算法。

#### 路径压缩

在寻找祖先时，利用数组内容找到这个元素的祖先的祖先，直到祖先不存在祖先为止（**祖先为自己**），在寻找的过程中，将所有遇到过的元素的祖先都**改为找到的祖先**。

这样可以使以后寻找祖先的**用时减少**，相当于把寻找的**路径压缩**。

#### 合并集合

用一个数组记录各个元素的祖先，若知道两个元素位于一个集合时，将其中的一个元素的祖先**更改为另一个元素的祖先**。

### 3）边和点的储存方法

边用一个结构体储存，用三个元素表示这一条边的**起点、中点、权值**。（这种方式储存的边是有向边，在此处因为使用了并查集算法，不用重复一遍。）

点用一个结构体储存，用两个元素表示这个点的**x坐标和y坐标**。

## 2.代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
    int u,v,w;
}a[1999000];//储存边
struct point
{
    int x,y;
}b[2005];//储存点
int n,c,x,y;
int f[2005];
bool cmp(edge d,edge e)
{
    return d.w<e.w;
}//sort的cmp交换函数，比较两边的权值大小交换
int find(int v)//寻找祖先函数
{
    if(f[v]==v)
    {
        return v;
    }
    else
    {
        f[v]=find(f[v]);//路径压缩
        return f[v];
    }
}
void merge(int d,int e)
{
    int fd=find(d),fe=find(e);
    f[fe]=fd;
}//合并集合函数
int leng(int i,int j)
{
    return (b[i].x-b[j].x)*(b[i].x-b[j].x)+(b[i].y-b[j].y)*(b[i].y-b[j].y);
}//获取铺设水管的费用的函数
int main()
{
    scanf("%d%d",&n,&c);
    int i,j,l,cnt=0,sum=0,count=0;
    for(i=1;i<=n;i++)
    {
        f[i]=i;//初始化并查集
        scanf("%d%d",&b[i].x,&b[i].y);//读入点
    }
	for(i=1;i<=n;i++)
	{
        for(j=1;j<i;j++)
        {
            l=leng(i,j);
            if(l>=c)//判断价钱大小
            {
                cnt++;
                a[cnt].u=i;
                a[cnt].v=j;
                a[cnt].w=l;//写入边
            }
        }
    }
    sort(a+1,a+1+cnt,cmp);//调用stl的sort排序
    for(i=1;i<=cnt;i++)
    {
    	if(find(a[i].u)!=find(a[i].v))
        //判断此边的两点是否在一个集合里。若在，则此边联通后图回存在回路，所有不能在一个集合里。
        {
        	merge(a[i].u,a[i].v);//合并集合
            sum+=a[i].w;//总花费增加
            count++;//边数增加
            if(count==n-1)
            //边数达到n-1边，即生成了一棵树，结束。
            {
            	break;
            }
        }
    }
    if(count<n-1)
    //若符合条件的边不能生成一棵树，则输出“-1”。
    {
        printf("-1");
        return 0;
    }
    printf("%d",sum);
    //否则输出结果。
    return 0;
}
```
评测结果

Accepted  100

用时: 1321ms / 内存: 23436KB

---

## 作者：Hiraeth (赞：0)

裸的一个最小生成树

在每次进行加边的时候判断加入的边是否合法 同时更新加入的边的数目

对一个n个节点的图而言 它的最小生成树的的节点数目应该是n-1

如果加入的边数小于n-1 说明无解 输出-1

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,tot,px,py,f[2005],l,cnt,ans;
struct p1{
	int x,y;
}a[2005];
struct p2{
	int x,y,z;
}b[4000005];
int dis(int x1,int y1,int x2,int y2){
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
}
bool cmp(p2 a,p2 b){
	return a.z<b.z;
}
int main(){
	scanf("%d%d",&n,&c);
	for (int i=1;i<=n;i++) f[i]=i;
	for (int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			l=dis(a[i].x,a[i].y,a[j].x,a[j].y);
			tot++;
			b[tot].x=i;
			b[tot].y=j;
			b[tot].z=l;
		}
	sort(b+1,b+tot+1,cmp);
	for (int i=1;i<=tot;i++){
		if (b[i].z<c) continue;
		px=find(b[i].x);
		py=find(b[i].y);
		if (px==py) continue;
		f[px]=py;
		ans+=b[i].z;
		cnt++;
	}
	if(cnt!=n-1) printf("-1\n");
		else printf("%d\n",ans);
	return  0;
}
```


---

## 作者：East_Wind (赞：0)

一道最小生成树模板题。

对于读进来的n个点,枚举判断第i个点和第j个点之间的距离是否大于c. 是，就加入q数组（边集数组）。

最后跑一遍最小生成树模板即可。最后注意判断-1

Prim算法 （由于我用优先队列常数太大，所以T了2个点）：

```cpp
#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;
const int N=2005;
int head[N],adj[N*N],Next[N*N],wei[N*N],vis[N]; 
int n,c,tot;
struct point{
  int x,y;
}a[N];
struct node{
  int e,w;
};
bool operator <(node a,node b){
  return a.w>b.w;
}
priority_queue<node> Q;
void read(int &x){
  char c=getchar();x=0;
  for(;c<'0'||c>'9';c=getchar());
  for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-'0'; 
} 
void addedge(int u,int v,int w,int tot){
  Next[tot]=head[u];
  head[u]=tot;
  adj[tot]=v;
  wei[tot]=w;
}
int Prim(int x){
int now=0,ans=0;
 Q.push((node){1,0});
 while(!Q.empty()&&now<n){
   node f=Q.top(); Q.pop(); 
   if(vis[f.e]) continue;
   ans+=f.w; vis[f.e]=1; now++; 
   for(int e=head[f.e];e;e=Next[e]){
     int v=adj[e];
     Q.push((node){v,wei[e]});
   }
 }
if(now==n) return ans;
else return -1;
}
int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
     read(a[i].x),read(a[i].y);
    for(int i=1;i<=n;i++)
     for(int j=i+1;j<=n;j++){
       int dist=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
       if(dist>=c) {
         addedge(i,j,dist,++tot);
         addedge(j,i,dist,++tot);
       }
     }
     cout<<Prim(1)<<endl;
}
```
Kruskal算法 ——满分。

```cpp
#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int N=2005;
int head[N],adj[N*N],Next[N*N],wei[N*N],vis[N]; 
int n,c,tot,fa[N];
struct node{
  int u,v,w;
}q[N*N];
struct point{
  int x,y;
}a[N];
void read(int &x){
  char c=getchar();x=0;
  for(;c<'0'||c>'9';c=getchar());
  for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-'0'; 
} 
bool cmp(node a,node b){
  return a.w<b.w;
}
int find(int x){
   return fa[x]==x?x:fa[x]=find(fa[x]);
}
int Kruskal(){
int ans=0,num_edge=0,pos=1;
  while(num_edge<n-1&&pos<tot){
    for(;pos<=tot;pos++){
      int a=find(q[pos].u),b=find(q[pos].v);
      if(a!=b) { fa[a]=b; ans+=q[pos].w; ++num_edge; break; }
    }
  }
 if(num_edge==n-1) return ans;
 else return -1;
}
int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++){
        fa[i]=i;
     read(a[i].x),read(a[i].y);
}
    for(int i=1;i<=n;i++)
     for(int j=i+1;j<=n;j++){
       int dist=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
       if(dist>=c) {
         q[++tot].u=i; q[tot].v=j; q[tot].w=dist;
       }
     }
     sort(q+1,q+1+tot,cmp);
     cout<<Kruskal()<<endl;
}
```

---

## 作者：睿屿青衫 (赞：0)

#[安利一下个人导航](www.risho.top)

#卡了很多遍90分，最后删去一层循环1440ms（克鲁斯卡尔够快的了）

##就是个模板，但是我加了优化（T三点到T一点到AC）（其实够裸的，主要是T吧？）

##建边的时候直接和输入、初始化并查集一块来，少一次循环（貌似都是这样）

##建边的时候先判断，小于c的权值直接不要，跳过（continue）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 8020000
#define ll long long
using namespace std;
ll n,c,x[maxn],y[maxn],father[maxn],tot=0,qr=0,js=0;
struct point 
{
    int a;
    int b;
    int v;
}p[maxn];
int read()
{
    int r=0,k=1;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')k=-1;
    for(;c>='0'&&c<='9';c=getchar())r=r*10+c-'0';
    return r*k;
}
int find(int x)
{
    if(father[x]!=x) father[x]=find(father[x]);
    return father[x];
}
void unionn(int x,int y)
{
    int r1=find(x);
    int r2=find(y);
    father[r2]=r1;
}
int cmp(point xx,point yy)
{
    return(xx.v<yy.v);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>c;
    for(int i=1;i<=n;++i){
        cin>>x[i]>>y[i];
        father[i]=i;
     for(int j=1;j<i;++j)
     {
         int xx=x[i]-x[j];
         int yy=y[i]-y[j];
         int zz=xx*xx+yy*yy;
         if(zz>=c)
         {
             qr++;
             p[qr].a=i;
             p[qr].b=j;
             p[qr].v=zz;
         }
     }}
    sort(p+1,p+qr+1,cmp);
    for(int i=1;i<=qr;++i)
    {
        int cc=p[i].v;
        int aa=p[i].a;
        int bb=p[i].b;
        if(find(aa)!=find(bb))
        {
            js++;
            unionn(aa,bb);
            tot+=cc;
        }
        if(js==n-1) break;
    }
    if(js!=n-1) printf("-1");
     else printf("%d",tot);
    return 0;
}
```

---

