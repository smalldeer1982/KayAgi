# [USACO07DEC] Sightseeing Cows G

## 题目描述

农夫约翰决定奖励他的奶牛们的辛勤工作，带它们去大城市游览！奶牛们必须决定如何最好地度过它们的空闲时间。

幸运的是，它们有一张详细的城市地图，显示了 $L$ $(2 \leq L \leq 1000)$ 个主要地标（方便地编号为 $1$ 到 $L$）和 $P$ $(2 \leq P \leq 5000)$ 条连接这些地标的单向牛道。农夫约翰会把奶牛们送到它们选择的一个起始地标，从那里它们将沿着牛道走到一系列其他地标，最后回到它们的起始地标，农夫约翰会在那里接它们回农场。由于城市空间有限，牛道非常狭窄，因此每条牛道的旅行只能沿着一个固定方向进行。

虽然奶牛们可以在城市里待多久都行，但它们很容易感到无聊。参观每个新的地标很有趣，但在它们之间行走需要时间。奶牛们知道每个地标 $i$ 的确切乐趣值 $F_i$ $(1 \leq F_i \leq 1000)$。

奶牛们还了解牛道。牛道 $i$ 连接地标 $L1_i$ 到 $L2_i$（方向为 $L1_i \to L2_i$），需要时间 $T_i$ $(1 \leq T_i \leq 1000)$ 来穿越。

为了度过一个最好的假期，奶牛们希望最大化它们旅行的单位时间平均乐趣值。当然，地标只有在第一次访问时才有趣；奶牛们可以多次经过地标，但它们不会再次感受到它的乐趣值。此外，农夫约翰要求奶牛们至少访问两个地标，以便在假期中得到一些锻炼。

帮助奶牛们找到它们能够实现的最大单位时间乐趣值。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 7
30
10
10
5
10
1 2 3
2 3 2
3 4 5
3 5 2
4 5 5
5 1 3
5 2 2```

### 输出

```
6.00```

# 题解

## 作者：木木！ (赞：65)

题解里似乎都没有提到这么一种情况，如果环里经过一个点两次（去一次，回来一次），点的`fi`只会被计算一次，但是如果按照题解里的算法的话，这个点的`fi`会被计算两次。

如果一个点被计算两次的话，分子上的东西就比分母上的东西少，以下推导都没法进行。

（这个bug让我在模拟赛里面不敢写0/1规划算法，最后此题0分QwQ

现在就要证明，如果环上的比率最优，则必然不会有一个点被经过两次。

首先，如果一个环经过一个点两次，则必然可以通过那个点（设为$P_x$）分成两个没有相交点的环。方便起见，设两个环的快乐值总和分别为$F_1$和$F_2$，用时总和分别为$T_1$和$T_2$，x点的快乐值为$F_x$

我们的目标就是证明：

$$\frac{F_1}{T_1}\geq\frac{F_1+F_2-F_x}{T_1+T_2}\space\space\space or\space\space\space\frac{F_2}{T_2}\geq\frac{F_1+F_2-F_x}{T_1+T_2}$$

由于右式含有`T1+T2`作为分母，因此就可以考虑将两环求平均数。即，只需要证明：

$$\frac{F_1}{2\times T_1}+\frac{F_2}{2\times T_2} \geq \frac{F_1+F_2-F_x}{T_1+T_2}$$

$$\frac{F_1T_2+F_2T_1}{2(T_1+T_2)}\geq\frac{F_1+F_2-F_x}{T_1+T_2}$$

因为我们分的两个都是环，至少要经过两条边，同时题目保证$T_i\geq1$，所以可以得出$T_1\geq2$且$T_2\geq2$。

因此，可得：

$$\frac{F_1T_2+F_2T_1}{2(T_1+T_2)}\geq\frac{F_1+F_2}{T_1+T_2}> \frac{F_1+F_2-F_x}{T_1+T_2}$$

Q.E.D.

因此，我们可以得出，该算法只适用于$T_i\geq1$的题目，如果允许边权等于0或者为小于1的小数的话，就得另找算法。

（很有可能是爆搜了QwQ）

其他部分题解的各位神仙已经讲得很清楚了，为了内容的完整性，还是写完吧QwQ。

首先，原题可以转化为，求一个环，使得$\frac{\sum F_i}{\sum T_i}$最小。由于上面花了几行证明上下齐项，可以应用0/1分数规划。

对于0/1分数规划，考虑二分。二分可将一个最优化问题转化为一个判定问题。如果二分出来的`mid`为$L$，则问题就转化为是否存在一个$\frac{\sum F_i}{\sum T_i}> L$

分数乘过去（保证$T_i>0$），减回来，得：

$$\sum(F_i-L\times T_i) > 0$$

由于左式不好搞，考虑变换。如果将左式乘以-1，原式变为：

$$\sum(L\times T_i-F_i)>0$$

既然所有边成一个环，那不就是一个负环的方程嘛？？

于是算法就出来了，先二分答案，然后对于一个`mid`，将边权变为边权乘`mid`再减去一个端点的`F[i]`（随便入端点还是出端点，反正是个环），最后`stacked spfa`找负环判定。

附AC代码：

```cpp
#include <stack>
#include <cmath>
#include <cstdio>
using namespace std;

inline double lfabs(double x)
{
	return x<0?-x:x;
}

int beg[1005];
int ed[5005];
int nxt[5005];
int len[5005];
int top;

void addedge(int a,int b,int c)
{
	++top;
	ed[top] = b;
	len[top] = c;
	nxt[top] = beg[a];
	beg[a] = top;
}
int n;
int fi[5005];
int inq[5005];
int inqn[5005];
double dist[5005];

bool spfa(int s,double delta)
{
	dist[s] = 0;
	inq[s] = 0;
	
	stack<int> stk;
	stk.push(s);
	
	while(!stk.empty())
	{
		int th = stk.top();
		stk.pop();
		inq[th] = 0;
		
		for(int p=beg[th]; p; p=nxt[p])
		{
			if(dist[th] + (delta*len[p]-fi[th]) < dist[ed[p]])
			{
				dist[ed[p]] = dist[th] + (delta*len[p]-fi[th]);
				
				if(!inq[ed[p]])
				{
					stk.push(ed[p]);
					++inqn[ed[p]];
					inq[ed[p]] = 1;
					
					if(inqn[ed[p]] > n+10)
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

int main()
{
	int p;
	scanf("%d%d",&n,&p);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",fi+i);
	}
	for(int i=1; i<=p; ++i)
	{
		int a,b,t;
		scanf("%d%d%d",&a,&b,&t);
		addedge(a,b,t);
	}
	
	double l = 0;
	double r = 1005;
	while(lfabs(r-l) >= 0.0001)
	{
		double mid = (l+r)/2;
		
		for(int i=1; i<=n; ++i)
		{
			dist[i] = 99999999;
			inq[i] = inqn[i] = 0;
		}
		
		for(int i=1; i<=n; ++i)
		{
			if(!inqn[i])
			{
				if(spfa(i,mid))
				{
					l = mid;
					goto die;
				}
			}
		}
		
		r = mid;
		
		die:;
	}
	
	printf("%.2lf",l+0.00005);
}
```

---

## 作者：niiick (赞：30)

0/1分数规划经典模型【最优比率环】

###[0/1分数规划 详解](https://blog.csdn.net/niiick/article/details/80925267)

为方便描述，记环$S=(\{v_i\},\{e_i\})$，
其中$\{v_i\}$为环上结点的集合，$\{e_i\}$为环上的边的集合

仿照0/1分数规划模型

不难想到要二分一个mid然后判定图上**是否存在一个环S**

使得$\frac{\sum_{i=1}^tFun[v_i]}{\sum_{i=1}^tTim[e_i]}>mid$

即该环是否满足$\sum_{i=1}^t(Fun[v_i]-mid*Tim[e_i])>0$

若是则$L=mid$，否则$R=mid$

但是这样在图中判定显然很麻烦，
所以我们试着把上式两边**同时乘-1**

变成$\sum_{i=1}^t(mid*Tim[e_i]-Fun[v_i])<0$

这样我们就把问题转化成了判定图中**是否存在负环**

到了这里方法已经很显然了

对于一条入点为$u_i$，出点为$v_i$的边$e_i$，
我们把这条边的边权看作$mid*Tim[e_i]-Fun[u_i]$，
然后在图上判负环，若有负环则$L=mid$，否则$R=mid$，
直到达到精度要求
*************************

```
#include<iostream>
#include<map>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef double dd;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=1010;
int n,m;
int a[maxn];
struct node{int v,dis,nxt;}E[5010];
int head[maxn],tot;
int vis[maxn],num[maxn];
dd d[maxn]; 

void add(int u,int v,int dis)
{
    E[++tot].nxt=head[u];
    E[tot].v=v; E[tot].dis=dis;
    head[u]=tot;
}

int check(dd x)
{
    queue<int> q; 
    for(int i=1;i<=n;++i)//因为图不一定连通，所以初始所有结点入队
    {
    	q.push(i);
    	d[i]=0; vis[i]=num[i]=1;
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop(); vis[u]=0;
        for(int i=head[u];i;i=E[i].nxt)
        {
            int v=E[i].v; dd dis=(dd)E[i].dis;
            if(d[v]>d[u]+x*dis-(dd)a[u])//边权为mid*Tim[e_i]-Fun[u_i]
            {
                d[v]=d[u]+x*dis-(dd)a[u];
                if(!vis[v])
                {
                    q.push(v); vis[v]=1;
                    if(++num[v]>=n) return 1;
                }
            }
        }
    }
    return 0;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;++i)a[i]=read();
    for(int i=1;i<=m;++i)
    {
        int u=read(),v=read(),dis=read();
        add(u,v,dis);
    }
    dd L=0,R=1000010,mid;
    while(R-L>1e-4)
    {
        mid=(L+R)/2;
        if(check(mid))L=mid;
        else R=mid;
    }
    printf("%.2lf",L);
    return 0;
    //niiick
}

```

---

## 作者：Ccliang (赞：10)

提供一个暴力算法。

我们今天考了这道题目，然后我一看这东西一副不可做的样子。然后就用30min打了一个暴力，结果有80？

于是我又加上一些玄学的STL的优化过掉了考试的数据，在洛谷上开O2也可以卡过去。

思路：
~~显而易见~~我们可以枚举每一个点，然后以它为起点跑最短路，找到一个单位时间快乐值最大的环，其可以更新最优解的条件~~显然~~是当前到这个点最优的路径的单位时间乐趣值小于本条路径的单位时间乐趣值。

~~至于为什么自己想想。。。~~

实际上这道题目的难点只是在于怎样判断一个点经过两次的情况。那么我们可以定义一个结构体：

```cpp
struct node{
	int u;//当前节点的编号
	bool used[N];//编号为 i 的点是否经过了一次
	void init(int x)
	{
		u=x;
		memset(used,false,sizeof(used));
	}
}st;
```
这样我们就可以在跑最短路的时候往队列里丢这个结构体类型的变量就可以了。

附上考场代码：

```
void bfs(int s)
{
	memset(Fsum,0,sizeof(Fsum));
	memset(Tsum,0,sizeof(Tsum));
	memset(vis,false,sizeof(vis));
	Fsum[s]=F[s];
	st.init(s);
	st.used[s]=true;
	q.push(st),vis[s]=true;
	while(!q.empty())
	{
		node qq=q.front();
		int u=qq.u;
		q.pop(),vis[u]=false;
		for(int e=head[u];e;e=r[e].next)
		{
			int v=r[e].to,w=r[e].w;
			if(Fsum[v]==0||Tsum[v]==0)//如果还没有走到这里
			{
				node c=qq;
				c.u=v;
				Fsum[v]=Fsum[u];
				if(!c.used[v])Fsum[v]+=F[v],c.used[v]=true;
				Tsum[v]=Tsum[u]+w,q.push(c);
				vis[v]=true;
			}
			else
			{
				double x=Fsum[v]/Tsum[v],y;
				node c=qq;
				int fs=Fsum[u],ts=Tsum[u]+w;
				if(!c.used[v])fs+=F[v];
				y=fs/ts;
				if(x<y)//走到过这里但是当前解更优
				{
					c.used[v]=true;
					c.u=v;
					Fsum[v]=fs,Tsum[v]=ts;
					if(!vis[v])q.push(c);
				}
			}
		}
	}
}//被卡了精度多WA了一个点TAT
```
但是这样的算法时间复杂度很高，尤其在结构体的预处理和状态继承的时候。

于是我们想到，STL里有个叫做bitset的东西：

```
bitset<N> b[N];
```
这个东西表示一个 N 位的二进制数，相当于一个二维的布偶型数组，但有一个不一样的地方，它支持这样的操作：

```cpp
b[v]=b[u];
```
于是它就可以跑得~~飞快~~

然后代码写出来就成了这样：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<bitset>
using namespace std;

const int N = 1000 + 10;
const int M = 5000 + 10;

inline int read()
{
 	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
	return res;
}

int n,m;

struct edge{
	int next,to,w;
}r[M];

int head[N],tot;

void add(int u,int v,int w)
{
	tot++;
	r[tot].next=head[u];
	head[u]=tot;
	r[tot].to=v;
	r[tot].w=w;
}

int F[N],Fsum[N],Tsum[N];

bool vis[N];

bitset<N> b[N];

queue<int> q;

void bfs(int s)
{
	for(int i=1;i<=n;i++)
		b[i]=Fsum[i]=Tsum[i]=0,vis[i]=false;
	Fsum[s]=F[s];
	q.push(s),vis[s]=true;
	b[s][s]=1;
	while(!q.empty())
	{
		int u=q.front();
		for(int e=head[u];e;e=r[e].next)
		{
			int v=r[e].to,w=r[e].w,fs=Fsum[u]+(!b[u][v]?F[v]:0),ts=Tsum[u]+w;
			double x=Fsum[v]*1.0/Tsum[v],y=fs*1.0/ts;
			if(!Tsum[v]||x<y)
			{
				Fsum[v]=fs;
				b[v]=b[u],b[v][v]=1;
				Tsum[v]=ts;
				if(!vis[v])q.push(v),vis[v]=true;
			}
		}
		q.pop(),vis[u]=false;
	}
}

double ans;

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		F[i]=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
	}
	for(int i=1;i<=n;i++)
	{
		bfs(i);
		if(Tsum[i]!=0)ans=max(ans,Fsum[i]*1.0/Tsum[i]);
//		cout<<Fsum[i]<<" "<<Tsum[i]<<endl;
	}
	printf("%.2f\n",ans);
    return 0;
}
```
但毕竟是个暴力，在洛谷上只能吸氧过了，我好菜啊qwq

---

## 作者：Azazеl (赞：4)

#### 2020/11/7：修正了一个笔误

#### 题意  
$\ \ \ \ $给出一个 $n$ 个点 $m$ 条的有点权与边权的有向图，求一个环使得环上的点权和除以边权和最大。  


------------
#### 题解  
$\ \ \ \ $设答案为 $p$ ,环上第 $i$ 个点的点权为 $a_i$ ，第 $i$ 条边的边权为 $b_i$。  
$\ \ \ \ $可得：  
$$\dfrac{{\sum_{i=1}^n}a_i}{\sum_{i=1}^{m}b_i}=p$$  
$$\sum_{i=1}^{n} a_i=\sum_{i=1}^m (b_i\times p)$$  
$$\sum_{i=1}^{n} a_i-\sum_{i=1}^m (b_i\times p)=0$$

$\ \ \ \ $（令上式中左式为$\Delta$）  
$\ \ \ \ $但我们不知道任意一个条件，因此这也不能得到答案。  
$\ \ \ \ $但是如果我们把 $p$ 二分出来，我们就可以把问题转化为判定，易知：  
$\ \ \ \ $①当 $\Delta<0$ 时，$p$ 过大，应该缩小。  
$\ \ \ \ $②当 $\Delta ≥0$时，$p$ 满足题意，但仍可放大去寻找最大值。  
$\ \ \ \ $继续化式子，可以得到：  
$$\sum_{i=1}^{n}a_i-p\times \sum_{i=1}^m b_i=0$$  

$\ \ \ \ $很容易观察出这个式子形似最短路中的三角不等式，因此我们可以用 SPFA 求解，刚好我们判定原式与 $0$ 的关系就相当于在图中找一个满足条件的**正环**，因此使用 DFS 实现的 SPFA 即可。  

$\ \ \ \ $此外还有一个问题，你会发现把式子取反变成判断负环会 TLE ，这里还不知道为什么。但讨论区里似乎也有跑正环会 TLE，负环就过了的代码，具体原因还有待考证。  



------------
#### 代码
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int p[1005];
double dis[1005];
bool vis[1005];
int n,m;
vector < pair<int,int> > G[1005];
bool SPFA(int u,double s)
{
	vis[u]=1;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i].first,w=G[u][i].second;
		if(dis[v]<dis[u]-s*w+p[u])
		{
			dis[v]=dis[u]-s*w+p[u];
			if(vis[v]||SPFA(v,s)) return true;
		}	
	} 
	vis[u]=0;
	return false;
}

bool check(double s)
{
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		memset(dis,128,sizeof(dis));
		dis[i]=0;
		if(SPFA(i,s)) return true;
	} 
	return false;
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d %d %d",&u,&v,&w);
		G[u].push_back(make_pair(v,w));
	}
	double l=0,r=1000005,mid,ans;
	while(r-l>=0.00001)
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid,ans=mid;//有负环
		else r=mid; 
	}
	printf("%.2lf",ans);
	return 0;
}
```


------------
既然选择了远方/便只顾风雨兼程

---

## 作者：fanfansann (赞：4)

根据题意，我们要环上各点权值之和除以各边权值之和最大。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200701083925332.png)
求最大答案，很明显可以使用二分答案。那么我们假设当前答案为 x，如果有更大的答案，那么方程就可以按下式转换：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200701083949492.png)
也就是说如果有更大的答案，则有一个环是负环（环边权总和为负数）。也就是说我们把求最大答案的问题转换为了判断当前建的图中是否存在负环。
我们可以将每一条边的边权设为
![在这里插入图片描述](https://img-blog.csdnimg.cn/202007010839572.png)
然后使用 $spfa$ 判断是否有负环。
使用spfa判断是否有负环，我们只需要用一个cnt数组存储每一个点的从起点到该点的最短路径包含的边数，在每次更新dis[y]的时候,判断$cnt[y] = cnt[x] + 1 ) > n$，若大于n则存在负环。这是一种效率较高的判断负环的方法。
```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;

const int N = 1e4+7;
const int M = 5e4+7;
const double eps = 1e-6;
int f[N];
int head[N],ver[M],nex[M],tot;
double edge[M];
int n,m;
int a[N];
double dis[N];
bool vis[N];//判断是否在队列里
int cnt[N];//表示的是从起点到x的最短路径包含的边数


void add(int x,int y,double z){
    ver[++tot] = y;
    nex[tot] = head[x];
    edge[tot] = z;
    head[x] = tot;
}
//判断是否存在负环，cnt[i]大于n则有负环（一共n个点，如果没有负环就最多等于n）
bool spfa(){
    queue<int>q;
    //没有起点，每个人都是起点
    for(int i = 1;i <= n;++i){
        q.push(i);
        dis[i] = 0;
        vis[i] = 1;
    }
    memset(cnt,0,sizeof cnt);
    while(q.size()){
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for(int i = head[x];i;i = nex[i]){
            int y = ver[i];
            if(dis[y] > dis[x] + edge[i]){
                dis[y] = dis[x] + edge[i];
                if((cnt[y] = cnt[x] + 1 ) > n)return 1;
                if(!vis[y]){
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
        
    }
    return 0;
}
int x[N],y[N], z[N];

bool check(double w){
    tot = 0;
    memset(head,0,sizeof head);
    for(int i = 1;i <= m;++i)
        add(x[i],y[i],w * z[i] - f[x[i]]);//减去出点权值
    return spfa();
}

int main(){
    cin>>n>>m;
    for(int i = 1;i <= n;++i)
        scanf("%d",&f[i]);
    for(int i = 1;i <= m;++i)
        scanf("%d %d %d",&x[i],&y[i],&z[i]);
    double l = 0,r = 1000;
    while(r - l > eps){
        double mid = (l + r) / 2;
        if(check(mid))l = mid;
        else r = mid;
    }
    printf("%.2f",l);
    return 0;
}
```


---

## 作者：QwQ_operator (赞：4)

思路：

奶牛们从起点出发然后在回到起点，也就是说奶牛走过的路径为一个环，在奶牛走的这个环中ans=所有的乐趣数/路上消耗的所有的时间。

我们将上面的式子进行变形，可以得到路上消耗的所有时间\*ans=所有的乐趣数。——>路上消耗的所有时间\*ans-所有的乐趣数=0；

然后我们在进行二分答案，处理出ans，然后对于每一个ans跑n个spfa，判断是否存在负环，如果存在负环就说明当前方案不是最佳答案（存在负环条件：当前点入队次数大于n，当然这种情况是当我们用bfs的spfa时），让我们用dfs的spfa时，我们用一个bool变量表示这个数有没有被访问过，如果被访问过，说明他出现了负环直接结束循环。我们的ans还能有更大的解，即当路上消耗的所有的时间\*ans-所有的乐趣数<0时我们的ans不是当前最优解继续更新最优解

注意：二分结束的条件为r-l>0.000001，否则会爆long long


当然你会发现我们会TLE既然这样我们就写dfs的spfa判负环，在这之前我有一篇博客讲过这种写法http://www.cnblogs.com/z360/p/6883351.html


```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 51000
using namespace std;
bool vis[N];
int n,m,x,y,z,tot;
int c[N],num[N],head[N];
double ans,mid,l,r,w[N],dis[N];
struct Edge
{
    int to,dis,from,next;
}edge[N];
int add(int x,int y,int z)
{
    tot++;
    edge[tot].to=y;
    edge[tot].dis=z;
    edge[tot].next=head[x];
    head[x]=tot;
}
int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
int spfa(int x)
{
    vis[x]=true;
    for(int i=head[x];i;i=edge[i].next)
    {
        int t=edge[i].to;
        if(dis[t]>dis[x]+w[i])
        {
            dis[t]=dis[x]+w[i];
            if(vis[t]||spfa(t))
            {
                vis[x]=false;
                return true;
            }  
        }
    }
    vis[x]=false;
    return false;
}
int pd()
{
    for(int i=1;i<=n;i++)
        if(spfa(i)) return true;
    return false;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=m;i++)
    {
        x=read(),y=read(),z=read();
        add(x,y,z);
    }
    l=0,r=100005;
    while(r-l>0.0000001)
    {
        mid=(l+r)/2;
        for(int i=1;i<=tot;i++)
        {
            int t=edge[i].to;
            w[i]=(double)mid*edge[i].dis-c[t];
        }
        if(pd())
        {
            ans=mid;
            l=mid;
        }
        else r=mid;
    }
    printf("%.2lf",ans);
    return 0;
}
```

---

## 作者：安好 (赞：3)

/\*
这道题...算分数规划？

设一段路程的收益是F，花费是dis，则比率为 ΣF/Σdis=r

要找出最大的r

二分出r设为x ，将每条边的边权修改为 “目的地的收益f - 边长度dis\*x”

然后SPFA检查图上是否有负环，有负环则x可以更优,答案可以增大。

\*/







```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#define N 100010
using namespace std;
const double eps=1e-5;
struct edge
{
    int v,nxt,w;
    double c;
} e[N<<1];
int head[N],f[N];
bool vis[N];
double dis[N];
int n,m,mct,u,v,w;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void add(int u,int v,int w)
{
    e[++mct].v=v;e[mct].nxt=head[u];e[mct].w=w;head[u]=mct;
}
bool SPFA(int u)
{
    vis[u]=1;
    for(int i=head[u]; i; i=e[i].nxt)
    {
        int v=e[i].v;
        if(dis[v]>dis[u]+e[i].c)
        {
            dis[v]=dis[u]+e[i].c;
            if(vis[v] || SPFA(v))
            {
                vis[v]=0;
                return 1;
            }
        }
    }vis[u]=0;return 0;
}
void judge(double r)
{
    for(int i=1; i<=mct; i++)
        e[i].c=(double)e[i].w*r-f[e[i].v];
    return;
}
bool check()
{
    for(int i=1; i<=n; i++)
        if(SPFA(i))return 1;
    return 0;
}
int main()
{
    n=read();m=read();
    for(int i=1; i<=n; i++) f[i]=read();
    for(int i=1; i<=m; i++)
    {
        u=read();v=read();w=read();
        add(u,v,w);
    }
    double l=0,r=100000,ans;
    while(r-l>eps)
    {
        double mid=(l+r)/2;
        judge(mid);
        if(check())
        {
            ans=mid;l=mid;
        }
        else r=mid;
    }
    printf("%.2f\n",ans);
    return 0;
}
```

---

## 作者：沧澜 (赞：2)

根据题目描述，起点的位置是不确定的。但是，因为奶牛们还要回到起点，所以，奶牛们所走的路径是一个环，起点在哪里是不重要的。

在奶牛们所走的环上：

\_\_ans=所有的乐趣数/路上消耗的所有的时间。

\_\_路上消耗的所有时间\*ans=所有的乐趣数。

\_\_路上消耗的所有时间\*ans-所有的乐趣数=0；

所以我们可以二分答案，ans，然后对于每一个跑n个spfa。

当路上消耗的所有的时间\*ans-所有的乐趣数<0。

那就说明r还能取更大值，r有更大的解。

```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAXN 15001
using namespace std;
int n,m,tot;
double w[MAXN],dis[MAXN];
double l=0,r=1000000,ans,mid;
int val[MAXN],vis[MAXN],num[MAXN];
int to[MAXN],net[MAXN],cap[MAXN],head[MAXN];
void add(int u,int v,int w){
    to[++tot]=v;net[tot]=head[u];cap[tot]=w;head[u]=tot;
}
bool spfa(int s){
    queue<int>que;
    memset(num,0,sizeof(num));
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    que.push(s);
    dis[s]=0;vis[s]=1;num[s]++;
    while(!que.empty()){
        int now=que.front();
        que.pop();
        vis[now]=0;
        for(int i=head[now];i;i=net[i]){
            if(dis[to[i]]>dis[now]+w[i]){
                dis[to[i]]=dis[now]+w[i];
                if(!vis[to[i]]){
                    vis[to[i]]=1;
                    num[to[i]]++;
                    que.push(to[i]);
                    if(num[to[i]]>n)    return true;
                }
            }
        }
    }
    return false;
}
void work(){
    for(int i=1;i<=tot;i++)
        w[i]=(double)cap[i]*mid-val[to[i]];
}
bool check(){
    for(int i=1;i<=n;i++)
        if(spfa(i))    return true;
    return false;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)    scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    while(r-l>0.0000001){
        mid=(l+r)/2;
        work();
        if(check()){
            ans=mid;
            l=mid;
        }
        else r=mid;
    }
    printf("%.2lf",ans);
}
```

---

## 作者：Object_ (赞：1)

**易错点：**

- 二分时，l,r,mid的类型都要设为double.
- 0/1规划问题在该类图上可转化为乘积的形式并使用spfa判断当前解是否合理.
- 注意区分i和i所代表的点a[i].

------------
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define eps 1e-3
using namespace std;
const int MAXN=2e3,MAXM=1e4;
struct Edge{
	int from,to,nxt;
	double w;
}e[MAXM];
int head[MAXN],edgeCnt=1;
void addEdge(int u,int v,double w){
	e[++edgeCnt].from=u;
	e[edgeCnt].to=v;
	e[edgeCnt].w=w;
	e[edgeCnt].nxt=head[u];
	head[u]=edgeCnt;
}
double dis[MAXN];
int n,enterNum[MAXN];
bool inQueue[MAXN];
bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(enterNum,0,sizeof(enterNum));
	queue<int> q;
	for(int i=1;i<=n;i++){
		q.push(i);
		inQueue[i]=1;
	}
	while(!q.empty()){
		if(dis[q.front()]>dis[q.back()])swap(q.front(),q.back());
		int nowPoint=q.front();q.pop();
		inQueue[nowPoint]=0;
		for(int i=head[nowPoint];i;i=e[i].nxt){
			int nowV=e[i].to;
			if(dis[nowV]>dis[nowPoint]+e[i].w){
				dis[nowV]=dis[nowPoint]+e[i].w;
				enterNum[nowV]++;
				if(enterNum[nowV]>n)return 1;
				if(inQueue[nowV])continue;
				q.push(nowV);
				inQueue[nowV]=1;
			}
		}
	}
	return 0;
}
int a[MAXM],b[MAXM],t[MAXM],f[MAXN];
int m;
bool judge(double nowValue){
	memset(head,0,sizeof(head));
	edgeCnt=1;
	for(int i=1;i<=m;i++){
		addEdge(a[i],b[i],nowValue*t[i]-f[a[i]]);
	}
	return spfa();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a[i],&b[i],&t[i]);
	}
	double l=0,r=1e3;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(judge(mid))l=mid;
		else r=mid;
	}
	printf("%.2f\n",l);
	return 0;
}
```


---

## 作者：Zekrom (赞：0)

## 方法也是一样，分数规划  
提供一些新方法  
1.  对于不同的联通块，可以创建一个虚拟节点，当然也可以直接都放入队列里（~~本质上一样~~） 
2.  判负环方法：   
1.记录最短路径边数，对于边（ x , y ) , cnt[ y ] =  cnt[ x ]+1 ,当cnt[ y ]>=n时有负环  
2.记录每个点入队次数，in_time[ i ]>=n时有负环  

使用两个方法+卡时  ~~你就可以bfs过spfa了~~  
上代码  
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<cmath> 
#define N 7010
#define M 20010 
using namespace std;
int n,m,cnt[N],tot,head[N],ru[N],in_time[N],val[N];
double l,r,d[N];
bool vis[N],flag;
struct Edge{
	int v,next,z1,z2;
}edge[M];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
inline void add(int x,int y,int v){ru[y]++;edge[++tot].v=y;edge[tot].next=head[x];edge[tot].z1=v;head[x]=tot;}
inline double cal(int x,int y,double mid){return mid*y-x;}
void spfa(int s,double mid){
	for(int i=1;i<=n;i++)d[i]=0x3f3f3f3f;
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)in_time[i]=0; 
	queue<int>q;
	d[s]=0;vis[s]=1;q.push(s);cnt[s]=-1;
	while(q.size()){
		int u=q.front();q.pop();vis[u]=0;
		if(cnt[u]>=n){flag=1;return;}
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v,z1=edge[i].z1;
			if(d[v]>d[u]+cal(val[u],z1,mid))
			{
				d[v]=d[u]+cal(val[u],z1,mid);
				cnt[v]=cnt[u]+1;
				if(cnt[v]>=n){flag=1;return;}          //路径条数判负环 
				if(!vis[v]){
					q.push(v);vis[v]=1;
					in_time[v]++;
					if(in_time[v]>=n){flag=1;return;}   //入队次数判负环	
				}
			}
		}
	}
} 
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		val[i]=read(),r+=val[i];
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z); 
	} 
	for(int i=1;i<=n;i++)
		add(0,i,0);                          //虚拟结点 
	l=0.0;
	while(fabs(r-l)>1e-4){
		double mid=(l+r)/2;
		flag=0;
		spfa(0,mid);
		if(flag)l=mid;else r=mid;
	}
	printf("%.2f",(l+r)/2);
	return 0;
}

```


---

