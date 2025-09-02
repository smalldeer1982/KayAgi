# BerDonalds

## 题目描述

BerDonalds, a well-known fast food restaurant, is going to open a cafe in Bertown. The important thing is to choose the new restaurant's location so that it would be easy to get there. The Bertown road system is represented by $ n $ junctions, connected by $ m $ bidirectional roads. For each road we know its length. We also know that we can get from any junction to any other one, moving along the roads.

Your task is to find such location of the restaurant, that the shortest distance along the roads from the cafe to the farthest junction would be minimum. Note that the restaurant can be located not only on the junction, but at any point of any road.

## 样例 #1

### 输入

```
2 1
1 2 1
```

### 输出

```
0.50
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
```

### 输出

```
1.00
```

## 样例 #3

### 输入

```
3 2
1 2 100
2 3 1
```

### 输出

```
50.50
```

# 题解

## 作者：suxxsfe (赞：6)

https://www.cnblogs.com/suxxsfe/p/15253132.html  

图的绝对中心在某节点或边上，使得所有节点到此点的距离最大值最小。  

如果绝对中心在点上，那么直接对于每个 $u$ 处理出 $dis_{u,x}$ 最大的 $x$ 即可。  

考虑在边上的情况，若在边 $(u,v,w)$ 上距离 $u$ 长度为 $x$，则节点 $i$ 到此点距离为 $\min(dis_{u,i}+x,dis_{v,i}+(w-x))$。  
把这个东西关于 $x$ 的图像画出来就是一个单峰的折线。  
把 $n$ 个点的所有折线都画出来就是这样（来自 oi-wiki）：  

![](https://oi-wiki.org//graph/images/mdst-plot2.svg)  

实线是 $n$ 个点的折线取完 $\max$ 的图像，然后发现所有实线的极小值的横坐标是可能的 $x$ 的取值。  
由于斜率一定，可以按照 $dis_{u,i}$ 从大到小考虑。  
设 $p$ 是目前考虑过的所有 $i$ 中使得 $dis_{v,i}$ 最大的那个，此时 $p$ 的那条折线的递减部分一定是完全暴露在外的。  
因此若此时有 $dis_{v,i}>dis_{v,p}$，则会在 $p$ 的递减部分产生一个新的合法最小值拐点。  
那么此时 $dis_{u,i}+x$ 和 $dis_{v,p}+(w-x)$ 一定同时是最长路径（还没考虑到的点的拐点在 $i$ 的后面，而交点是在 $i$ 的拐点前面，因此图像都在 $i$ 下面），由此计算更新答案。  

```cpp  
#define N 206
#define M 40006
int n,m;
int val[N];
int dis[N][N],rank[N][N];
int u[M],v[M],w[M];
int main(){
	n=read();m=read();
	std::memset(dis,0x3f,sizeof dis);
	for(reg int i=1;i<=n;i++) dis[i][i]=0;
	for(reg int u,v,i=1;i<=m;i++){
		u=::u[i]=read();v=::v[i]=read();
		dis[u][v]=dis[v][u]=std::min(dis[u][v],w[i]=read());
	}
	for(reg int k=1;k<=n;k++){
		for(reg int i=1;i<=n;i++)for(reg int j=1;j<=n;j++) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	for(reg int i=1;i<=n;i++){
		for(reg int j=1;j<=n;j++) val[j]=dis[i][j],rank[i][j]=j;
		std::sort(rank[i]+1,rank[i]+1+n,[](const int &a,const int &b){return val[a]<val[b];});
	}
	int ans=1e9;
	for(reg int i=1;i<=n;i++) ans=std::min(ans,dis[i][rank[i][n]]<<1);
	for(reg int i=1;i<=m;i++){
		int u=::u[i],v=::v[i],w=::w[i];
		for(reg int j=n-1,p=n;j;j--)if(dis[v][rank[u][j]]>dis[v][rank[u][p]]){
			ans=std::min(ans,dis[u][rank[u][j]]+dis[v][rank[u][p]]+w);
			p=j;
		}
	}
	printf("%lf\n",ans/2.0);
	return 0;
}
```

---

## 作者：Lynkcat (赞：1)

考虑答案会是什么样子的。

考虑一个点 $a$ 对于一条边 $(u,v,w)$ 的答案，随着关键点不断从 $u$ 移动至 $v$ ，设关键点与 $u$ 的距离为 $x$，答案一定是慢慢变大然后直到$dis(a,u)+x=dis(a,v)+w-x$，然后答案慢慢变小。（这里假设 $dis(a,u)\leq dis(a,v)$）。

我们再考虑这个答案的极大值 $dis(a,u)+x=dis(a,v)+w-x$，移项得 $x=\frac{abs(dis(a,u)-dis(a,v))+w}{2}$。

由于分子是正整数，我们发现 $x$ 的小数部分要么是 $0$ 要么是 $0.5$。

接下来考虑多个点对一条边答案的影响，我们发现将这些答案的变化放到坐标系上是若干条先向上再往下的折线![](https://oi-wiki.org//graph/images/mdst-plot2.svg)。

（图片来自 @suxxsfe 的题解，懒得画了。）

显然答案就是若干个交点的最小值。

那么考虑这东西怎么算，有一种简单的想法是把所有折线抠出来之后先按 $dis(u,i)$ 从小到大排序，然后单调栈维护一个 $dis(v,i)$ 递减的序列，所有的交点即为栈中相邻两个折线的交点。

但是这样做是 $O(n^3 \log n)$ 的，显然不够。

接着你会发现当我们按 $dis(u,i)$ 排序时与 $dis(v,i)$ 的顺序无关，然后枚举边的时候只要先固定 $u$ 排完序后，直接枚举别的 $v$ 直接扫就行了。

总时间复杂度 $O(n^3+n^2\log n)$ 。

至于算两条折线的交点，那直接把折点在前面的那条折线的前半部分往上折后变成两条斜率为 $1$ 的直线求交点 $O(1)$ 算就行。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define inf 1000000005
#define mod 998244353
#define int ll
#define N 505
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int f[N][N];
vector<int>G[N];
int sta[N];
int c[N],d[N],e[N];
int n,m;
double ans;
struct node
{
	int u,v;
	double w;
}E[N*N];
inline double calc(double x,double y,double xx,double yy,double k)
{
	double X=(x+y+k)*1.0/2;
	x=(X+(X-x));
	return (x+xx)*1.0/2;
}
signed main()
{
	n=read(),m=read();
	memset(f,0x3f,sizeof(f));
	ans=f[0][0];
	bool bl=1;
	for (int i=1;i<=n;i++) f[i][i]=0;
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		if (u>v) swap(u,v);
		bl&=(w==2);
		f[u][v]=f[v][u]=min(f[u][v],w);
		E[i]={u,v,w};
		G[u].push_back(i);
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			if (i!=k)
				for (int j=1;j<=n;j++)
					if (i!=j&&j!=k)
						f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
	for (int i=1;i<=n;i++)
	{
		if (G[i].size()==0) continue;
		vector<pa>g;
		for (int j=1;j<=n;j++)
			g.push_back({f[j][i],j});
		sort(g.begin(),g.end());
		for (int j=1;j<=n;j++)
			c[g[j-1].se]=j,d[j]=g[j-1].fi;
		for (auto u:G[i])
		{
			re int tp=0;
			for (int j=1;j<=n;j++) 
				e[c[j]]=f[j][E[u].v];
			for (int j=1;j<=n;j++)
			{
				while (tp&&e[sta[tp]]<=e[j]) tp--;
				sta[++tp]=j;
			}
			for (int j=2;j<=tp;j++)
			{
				ans=min(ans,calc(e[sta[j-1]],d[sta[j-1]],e[sta[j]],d[sta[j]],E[u].w));
			}
			ans=min(ans,e[sta[1]]*1.0);
			ans=min(ans,d[sta[tp]]*1.0);
		}
	}
	printf("%.10f",ans);
			
}
/*

*/


---

## 作者：白依尘_轩子墨 (赞：0)

[具体内容](https://oi-wiki.org/graph/mdst/)

题意：

求一张图的最小直径生成树的最小直径。

前置芝士：

图的绝对中心

图的绝对中心可以存在于一条边或某个点上，中心到所有点的最短距离的最大值最小。

根据图的绝对中心的定义可以知道，到绝对中心距离最远的结点至少有两个。

最小直径生成树的最小直径即为这两个结点到绝对中心的距离和

分析：

$2\leq n \leq 200$，所以我们可以用 floyd 或者 Johnson 求出一个 $dis_{i,j}$ 表示 $i,j$ 之间的最短距离。

求出 $f_{i,j}$ 表示距离结点 $i$ 第 $j$ 远的结点的编号。

大家最爱的分类讨论：

当图的绝对中心在结点上时，显然我们可以通过遍历每一个结点，更新距离这个结点最远的结点到这个结点的距离作为中心在结点上的最小直径，即 $ans=\min(2 \times dis_{i,f_{i,n}},ans)$。

当图的绝对中心在边上时：

假设绝对中心 $c$ 在边 $w=(u,v)$ 上，那么中心距离 $u$ 的距离为 $x(x \leq w)$，距离 $v$ 的长度就是 $w-x$。

那么对图中一点 $i$，$dis_{c,i}=\min(dis_{u,i}+x,dis_{v,i}+(w-x))$。

RT:

![](https://cdn.luogu.com.cn/upload/image_hosting/zl5bv63v.png)

于是我们从距离 $u$ 最远的结点开始倒着枚举点，
设目前到这条边上直径最小的结点到 $u$ 是第 $p$ 远的，对于 $i\in (f_{u,p-1},1)$，$dis_{u,f_{u,i}}<dis_{u,f_{u,p}}$，可能出现 $dis_{v,f_{u,i}}>dis_{v,f_{u,p}}$ 时,此时更新答案的最小值，即 $ans=\min (dis_{u,f_{u,i}}+dis_{v,f_{u,p}}+w,ans)$。


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1000;
const int mod=1e9+7;
typedef long long ll;
const ll inf=1e17;
namespace io{
	const int _SIZE=(1<<21)+1;
	char ibuf[_SIZE],*iS,*iT,c,stk[40];int tot;
	#define gc()getchar()
	template<class I>
	inline void read(I &_x){
		I fl=1;
		for(c=gc();c<'0'||c>'9';c=gc()) if(c=='-') fl=-1;
		for(_x=0;c>='0'&&c<='9';c=gc()) _x=(_x<<3)+(_x<<1)+(c&15);
		_x*=fl;
	}
	template<class I>
	inline void prt(I _x,char ch='\0'){
		tot=0;
		if(_x<0) putchar('-'),_x*=-1;
		do{
			stk[tot++]=_x%10|48;_x/=10;
		}while(_x);
		do{
			putchar(stk[--tot]);
		}while(tot);
		if(ch)putchar(ch);
	}
}
using io::read;
using io::prt;
ll n,m;
ll dis[Maxn][Maxn],f[Maxn][Maxn],c[Maxn],ans,pos;
bool cmp(int a,int b){return c[a]<c[b];}
struct edge{
	int u,v,w;
}e[Maxn*Maxn];
void init(){
	ans=inf;
	for(int i=1;i<=501;i++)
		for(int j=1;j<=501;j++)
			dis[i][j]=inf;
	for(int i=1;i<=501;i++) dis[i][i]=0;
}
void floyd(){ 
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
#define fname "test"
int main(){
//	freopen(fname".in","r",stdin);
//	freopen(fname".out","w",stdout);
	read(n),read(m);
	init();
	for(int i=1;i<=m;i++){
		int u,v,w;
		read(u),read(v),read(w);
		dis[u][v]=dis[v][u]=w;
		e[i]=(edge){u,v,w};
	}
	floyd();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=j;
			c[j]=dis[i][j];
		}
		sort(f[i]+1,f[i]+1+n,cmp);
	}
	for(int i=1;i<=n;i++) ans=min(ans,dis[i][f[i][n]]*2);
	for(int i=1;i<=m;i++){
		ll u=e[i].u,v=e[i].v,w=e[i].w;
		pos=n;
		for(int i=n-1;i>=1;i--){
			if(dis[v][f[u][i]]>dis[v][f[u][pos]]){
				ans=min(dis[u][f[u][i]]+dis[v][f[u][pos]]+w,ans);
				pos=i;
			}
		}
	}
	printf("%.2lf",ans/2.0);
	return 0;
}
```


---

