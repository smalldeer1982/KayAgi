# Explorer

## 题目背景

提示：本题数据较水，通过本题不代表程序/做法完全正确。

## 题目描述

给出两条直线，上面分别有 $n,m$ 个点，求这 $n+m$ 个点组成的最小生成树。


## 说明/提示

$n,m \le 100000$，$AX,AY,BX,BY,CX,CY,DX,DY$ 的绝对值均小于等于 $10^5$，$0 \le t \le 1$。


------------
2024/2/8 添加一组 hack 数据。

## 样例 #1

### 输入

```
4 4 
0 0 10 10 
0 10 10 0 
0.1 0.3 0.6 0.8 
0.1 0.3 0.6 0.8```

### 输出

```
19.638```

# 题解

## 作者：I_am_AKed_by_NOI (赞：5)

## 题目大意

给定两条直线，其中一条上有 $n$ 个点，另一条上有 $m$ 个点，求这 $n+m$ 个点的最小生成树。

## 题目思路

假设我们把这 $n+m$ 个点两两连线，就会形成一个非常非常稠密的图，一共有 $\frac{(n+m)^2}{2}$ 条边，显然是不可取的。

事实上，我们可以减少一下不必要的边。


- 同一条直线上，只需要连接相邻的连个点即可。

证明：

这个还是比较显然的。

如果 $a_1,a_2,a_3$ 从左到右在同一条直线上，那么 $a_1$ 与 $a_3$ 就不必相连，因为 $a_3$ 肯定会与 $a_2$ 相连，那么连接 $a_1,a_3$ 的代价相当于连接 $a_1,a_2$ 再连接 $a_2,a_3$，前者只联通了 $a_1,a_3$ 两个点，而后者联通了 $a_1,a_2,a_3$ 三个点，显然后者比前者更优。所以在同一条直线上，只需要连接相邻的连个点即可。


- 若一个点要另一条直线所在的点，则只需连接有这点向另一条直线做垂线得到的垂足旁边的两个点

证明：

垂线段最短，所以这垂足旁两个点到这个点的距离最短。设该点为 $x$，垂足旁的两个点为 $a_1,a_2$（假设 $a_1$ 离 $x$ 更近），与它们在同一直线上的任意一点为 $a_3$。

这里默认 $a_1,a_2,a_3$ 从左到右，其他情况与此情况类似。

要让他们联通，连接 $x,a_1$ 和 $a_1,a_2$ 与 $a_2,a_3$ 显然是最优的，所以 $x$ 不会与 $a_3$ 连接，那么结论得证。

这样子边数就从 $\frac{(n+m)^2}{2}$ 减少很多，可以通过。



---

## 作者：AstaVenti_ (赞：3)

# $\mathbf{0x00}$ 序

第一篇蓝题题解。

# $\mathbf{0x10}$ 题

两条直线上分别有 $n,m$ 个点，求这 $(n+m)$ 个点的最小生成树。

# $\mathbf{0x20}$ 解

以下设 $k=n+m$。

## $\mathbf{0x21}$ 暴力做法

对于这 $k$ 个点，给它们两两建边，一共会有 $\frac{(1+k)k}{2}$ 条边，而 $n,m\leq1\times10^5$，显然是不行的。~~数据范围告诉我们这样会喜提爆零。~~

## $\mathbf{0x22}$ 优化后

我们能不能删去某些边？当然。以下记连接节点 $a,b$ 的边为 $x_{a,b}$，其边权为 $y_{a,b}$，第一条直线为 $l_1$，第二条直线为 $l_2$。

分类讨论一下：

- 对于从左到右在同一直线上的三个点 $a_1,a_2,a_3$，暴力的话会连上三条边：$x_{a_1,a_2},x_{a_2,a_3},x_{a_1,a_3}$，但是我们会发现 $y_{a_1,a_2}+y_{a_2,a_3}=y_{a_1,a_3}$。前两条边边权之和等于第三条边的边权，当然连上三个点总比连上两个点好，因此可以舍弃 $x_{a_1,a_3}$。

- 对于在 $l_1$ 上的点 $a_1$ 和在 $l_2$ 上且在 $l_1$ 垂足旁边的点 $b_1,b_2$，不妨设 $y_{a_1,b_1}<y_{a_1,b_2}$，由于**垂线段最短**，因此我们只需要连接 $a_1,b_1$ 和 $b_1,b_2$ 即可。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/sanpog4z.png)

# $\mathbf{0x30}$ 合

其余的就和最小生成树一样了，跑一遍 Kruskal 即可。

---

## 作者：zzxLLL (赞：3)

下文中 $l_0, l_1$ 分别代指第一条，第二条直线。

直接两两连边，边数是 $O((n + m)^2)$ 的，不可取。

考虑舍弃掉一些显然不优的的边：

1. 对于一条直线，只用将相邻的点连边，边权为两者的距离。

2. 对于两条直线上的点之间的边，假设 $l_1$ 上的点为 $(x_1, y_1)$，向 $l_0$ 做垂线，垂足横坐标为 $x$，找到 $l_0$ 上横坐标离 $x$ 最近的两个点，向其连边即可。

然后跑最小生成树。时间复杂度 $O(n \log n)$。

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
const int M=2e5+10,N=1e6+10;
const double inf = 1e20;

int n,m,ax,ay,bx,by,cx,cy,dx,dy;
double t0[M],t1[M];

struct Line{
	double k,b;
}l0,l1;

int fa[M];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
bool qry(int x,int y){return find(x)==find(y);}

double dist(double x1,double y1,double x2,double y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

struct Edge{
	int u,v; double w;
}e[N];
int cnte;
double Kruskal(){
	for(int i=1;i<=n+m;i++) fa[i]=i;
	double sum=0;
	std::sort(e+1,e+1+cnte,[](Edge A,Edge B){return A.w<B.w;});
	for(int i=1;i<=cnte;i++){
		if(qry(e[i].u,e[i].v)) continue;
		merge(e[i].u,e[i].v),sum+=e[i].w;
	}
	return sum;
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&ax,&ay,&bx,&by);
	scanf("%d%d%d%d",&cx,&cy,&dx,&dy);
	l0.k=(bx==ax)?inf:1.*(by-ay)/(bx-ax),l0.b=ay-ax*l0.k;
	l1.k=(dx==cx)?inf:1.*(dy-cy)/(dx-cx),l1.b=cy-cx*l1.k;
	
	double t;
	for(int i=1;i<=n;i++){
		scanf("%lf",&t);
		t0[i]=ax*t+bx*(1-t);
	}
	for(int i=1;i<=m;i++){
		scanf("%lf",&t);
		t1[i]=cx*t+dx*(1-t);
	}
	std::sort(t0+1,t0+1+n),std::sort(t1+1,t1+1+m);
	
	for(int i=1;i<=m;i++){
		double x1=t1[i],y1=l1.k*t1[i]+l1.b;
		double x=(y1+x1/l0.k-l0.b)/(l0.k+1./l0.k);
		int pos=std::lower_bound(t0+1,t0+1+n,x)-t0;
		for(int j=std::max(pos-1,1);j<=std::min(pos+1,n);j++)
			e[++cnte]=(Edge){i+n,j,dist(x1,y1,t0[j],l0.k*t0[j]+l0.b)};
	}
	for(int i=1;i<n;i++){
		double x0=t0[i],y0=l0.k*t0[i]+l0.b;
		double x1=t0[i+1],y1=l0.k*t0[i+1]+l0.b;
		e[++cnte]=(Edge){i,i+1,dist(x0,y0,x1,y1)};
	}
	for(int i=1;i<m;i++){
		double x0=t1[i],y0=l1.k*t1[i]+l1.b;
		double x1=t1[i+1],y1=l1.k*t1[i+1]+l1.b;
		e[++cnte]=(Edge){i+n,i+n+1,dist(x0,y0,x1,y1)};
	}
	printf("%.3f",Kruskal());
	return 0;
}
```

正确性的证明：

旋转平移坐标系使得 $l_0$ 为 $x$ 轴，显然答案不会变。

设旋转平移后 $l_0$ 上点的横坐标为 $x_{0,1},x_{0,2},\cdots,x_{0,n}$，$l_1$ 上的点横坐标为 $x_{1,1},x_{1,2},\cdots,x_{1,m}$。

对于 $l_1$ 上的点 $(x_{1,t},f(x_{1,t}))$，如果要连向 $l_0$，显然找离 $x_{1,t}$ 最接近的  $x_{0,a},x_{0,a+1}$ 是最优的。

对于 $l_0$ 上的点，如果没有任何一个 $l_1$ 的点和他连边，那么它与 $l_0$ 的旁边两个点连边显然是最优的。故并不需要 $l_0$ 再向 $l_1$ 做垂线找最近点。

---

## 作者：Magus (赞：1)

~~唐~~题。

可以想到暴力建每一条边，边数为 $(n+m)^2$ 级别的，显然超时，考虑优化建图。

在同一条边上，只用连接相邻的点，原因显然。

在不同的边上，因为垂线段最短，所以只用连接点与垂足的两个相邻点即可。

跑一遍 kruskal，AC。

一些数学知识：

~~其实本题的主要难点是数学（~~

已知直线一般式方程 $Ax+By+C=0$，则

垂足直线公式：

$$x=\frac{B^2x0-ABy0-AC}{A^2+B^2},y=\frac{-ABx0+A^2y0-BC}{A^2+B^2}$$

当 $BX=CX$ 时斜率取 $\inf$，另一直线同理。

---

## 作者：Aliya_Hyacinth (赞：1)

感谢 PANDA 帮我发现了我的 rz 错误。
### 大意
给两条直线，一条上有  $n$  个点，一条上有 $m$ 个点，求这 $m+n$ 个点的最小生成树。

### 思路
直接建图空间极限大小为 $(n+m)^2$ 级别，需要优化。如图，对于下面的图片：
![a](https://cdn.luogu.com.cn/upload/image_hosting/bo93q23f.png)

对于任意一个点：在一条直线上时，连相邻点最优，因为隔着连点会大于相邻连点；在不同直线上时，连垂足的相邻点最优，理由如上。

### 一些知识
1. 如果直线竖直，那么斜率 $k$ 取极大值。
2. 垂足坐标公式：横坐标 $x= \frac{B^2x0-ABy0-AC}{A^2+B^2} $。
3. 上面的 $A,B,C$ 指的是直线的一般式方程 $Ax+By+C=0$。

###  CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const double MAXN=1e18;
const double eps=1e-10;
typedef long long ll;
const ll r=1;

struct node{
	int be,en;
	double va;
}e[N*5];
inline bool cmp(node aa,node bb){
	return aa.va<bb.va;
}

double poi[N],qoi[N];
double ax,ay,bx,by;
double cx,cy,dx,dy;
ll n,m,k;
double t,ans;
ll fa[N],num;
double x1[N],x2[N];
double k1,k2,b1,b2;


ll find(int w){
	if(fa[w]!=w)
		fa[w]=find(fa[w]);
	return fa[w];
}

inline double dis(double x1,double y1,double x2,double y2){
	double ans1,ans2;
	ans1=(x1-x2)*(x1-x2);
	ans2=(y1-y2)*(y1-y2);
	double ans;
	ans=sqrt(ans1+ans2);
	return ans;
}

inline void kruskal(){
	sort(e+1,e+k+1,cmp);
	ans=0,num=0;
	for(int i=1;i<=n+m;i++)
		fa[i]=i;
	for(int i=1;i<=k;i++){
		ll a=find(e[i].be),b=find(e[i].en);
		if(a!=b){
			fa[a]=fa[b];
			ans+=e[i].va;
			num++;
		}
		if(num==n+m-1){
			printf("%.3lf",ans);
			break;
		}
	}
	return ;
}

int main(){
	scanf("%lld%lld",&n,&m);
	scanf("%lf%lf%lf%lf",&ax,&ay,&bx,&by);
	scanf("%lf%lf%lf%lf",&cx,&cy,&dx,&dy);
	if(ax==bx)
		k1=MAXN;
	else{
		k1=(ay-by)/(ax-bx);
		b1=ay-k1*ax;
	}
	if(cx==dx)
		k2=MAXN;
	else{
		k2=(cy-dy)/(cx-dx);
		b2=cy-k2*cx;
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",&t);
		poi[i]=ax*t+bx*(1-t);
	}
	for(int i=1;i<=m;i++){
		scanf("%lf",&t);
		qoi[i]=cx*t+dx*(1-t);
	}
	sort(poi+1,poi+n+1);
	sort(qoi+1,qoi+m+1);
	k=0;
	for(int i=1;i<=n;i++){
		double x11,y11;
		x11=poi[i];
		y11=x11*k1+b1;
		if(i+1<=n){
			e[++k].be=i;
			e[k].en=i+1;
			e[k].va=dis(x11,y11,poi[i+1],poi[i+1]*k1+b1);
		}
		if(i-1>=1){
			e[++k].be=i;
			e[k].en=i-1;
			e[k].va=dis(x11,y11,poi[i-1],poi[i-1]*k1+b1);
		}
		double A,B,C;
		A=k2,B=-1,C=b2;
		double xx=(B*B*x11-A*B*(x11*k1+b1)-A*C)/(A*A+B*B);
		ll pos=lower_bound(qoi+1,qoi+m+1,xx)-qoi;
		for(int j=max(pos-1,r);j<=min(m,pos+1);j++){
			e[++k].be=i;
			e[k].en=j+n;
			e[k].va=dis(x11,y11,qoi[j],qoi[j]*k2+b2);
		}
	}
	for(int i=1;i<=m;i++){
		double x11,y11;
		x11=qoi[i];
		y11=x11*k2+b2;
		if(i+1<=m){
			e[++k].be=i+n;
			e[k].en=i+n+1;
			e[k].va=dis(x11,y11,qoi[i+1],qoi[i+1]*k2+b2);
		}
		if(i-1>=1){
			e[++k].be=i+n;
			e[k].en=i+n-1;
			e[k].va=dis(x11,y11,qoi[i-1],qoi[i-1]*k2+b2);
		}
		double A,B,C;
		A=k1,B=-1,C=b1;
		double xx=(B*B*x11-A*B*(x11*k1+b1)-A*C)/(A*A+B*B);
		ll pos=lower_bound(poi+1,poi+n+1,xx)-poi;
		for(int j=max(pos-1,r);j<=min(pos+1,n);j++){
			e[++k].be=i+n;
			e[k].en=j;
			e[k].va=dis(x11,y11,poi[j],poi[j]*k1+b1);
		}
	}
	kruskal();
	return 0;
}
```

---

