# [ICPC 2014 WF] Sensor Network

## 题目描述

一个无线传感器网络由分散在环境中的自主传感器组成，它们监测温度、声音和压力等条件。

Samantha 是一名研究人员，正在从事亚马逊二氧化碳测量（ACM）项目。在该项目中，亚马逊雨林中的无线传感器网络收集环境信息。亚马逊雨林储存的碳量相当于全球化石燃料排放量的十年，并在全球氧气传输过程中发挥着关键作用。由于这片森林的巨大规模，森林的变化不仅影响当地环境，还通过改变风和洋流模式影响全球气候。ACM 项目的目标是帮助科学家更好地理解地球复杂的生态系统以及人类活动的影响。

Samantha 有一个重要的假设，为了验证她的假设，她需要找到一个传感器子集，其中每对传感器可以直接相互通信。一个传感器可以与距离不超过 $d$ 的任何其他传感器直接通信。为了使她的实验尽可能准确，Samantha 希望选择尽可能多的传感器。

由于不能简单地进入亚马逊，Samantha 不能添加新的传感器或移动当前的位置。因此，给定传感器的当前位置，她需要你的帮助来找到满足她标准的最大子集。为简单起见，将每个传感器的位置表示为二维平面上的一个点，两个点之间的距离为通常的欧几里得距离。

## 说明/提示

时间限制：2000 毫秒，内存限制：1048576 kB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 1
0 0
0 1
1 0
1 1
```

### 输出

```
2
1 2
```

## 样例 #2

### 输入

```
5 20
0 0
0 2
100 100
100 110
100 120
```

### 输出

```
3
4 3 5
```

# 题解

## 作者：Froggy (赞：5)

## Sol 1：乱搞

爆搜/模拟退火/……

暴力求最大团，其实就是这题-> [外太空旅行](https://www.luogu.com.cn/problem/P4212)

## Sol 2：正经做法：

放到平面上，其实就有优秀的多项式做法了。

枚举最大团最远的点对，如果两点之间连一条直线，剩下的可用的点就被分到两个区域内。如果把这些点中不能同时被选的点连一条边，容易发现这是个二分图，因为区域内部的点之间不可能连边。

放个图更好理解一点：（两个黑点是钦定的最远点对）

![](https://cdn.luogu.com.cn/upload/image_hosting/529t8sk5.png)

然后求二分图最大独立集即可。

时间复杂度应该的 $\mathcal{O}(n^{4.5})$ 的吧，反正常数极小跑的飞快。

---

***code:***

```cpp
const int inf=0x3f3f3f3f;
#define N 155
namespace Maxflow{
	int cnt,S,T,dep[N],head[N],pre[N];
	struct Edge{
		int to,nxt,val;
	}edge[N*N<<1];
	void Clear(){
		memset(head,0,sizeof(head));
		cnt=1;
	}
	void add(int a,int b,int c){
		edge[++cnt]={b,head[a],c};
		head[a]=cnt;
	}
	void adde(int a,int b,int c){
		add(a,b,c),add(b,a,0);
	}
	queue<int> q;
	bool bfs(){
		memset(dep,0,sizeof(dep));
		dep[S]=1;
		q.push(S);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=head[u];i;i=edge[i].nxt){
				int v=edge[i].to;
				if(edge[i].val&&!dep[v]){
					dep[v]=dep[u]+1;
					q.push(v);
				}
			}
		}
		return dep[T]>0;
	}
	int dfs(int u,int limit){
		if(u==T)return limit;
		int flow=0;
		for(int &i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==dep[u]+1&&edge[i].val){
				int k=dfs(v,min(limit,edge[i].val));
				edge[i].val-=k;
				edge[i^1].val+=k;
				flow+=k;
				limit-=k;
			}
			if(!limit)break;
		}
		if(!flow)dep[u]=inf;
		return flow;
	}
	int Dinic(){
		memcpy(pre,head,sizeof(head));
		int maxflow=0;
		while(bfs()){
			maxflow+=dfs(S,inf);
			memcpy(head,pre,sizeof(head));
		}
		return maxflow;
	}
	bool vis[N];
	void dfs(int u){
		vis[u]=true;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].val&&!vis[v])dfs(v);
		}
	}
	void Plan(){
		memset(vis,false,sizeof(vis));
		dfs(S);
	}
}
int n,D;
vector<int> ans;
struct Point{
	int x,y;
	Point(int _x=0,int _y=0){x=_x,y=_y;}
	Point operator -(const Point b){
		return Point(x-b.x,y-b.y);
	}
	int operator %(const Point b){
		return x*b.y-y*b.x;
	}
}p[N];
inline int Dis(Point &a,Point &b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline bool Left(Point a,Point b){
	return a%b<0;
}
inline bool Para(Point a,Point b){
	return a%b==0;
}
void Solve(int a,int b){
	static int type[N];
	static vector<int> res;
	res.clear();
	int tot=0,lim=Dis(p[a],p[b]);
	Maxflow::Clear();
	Maxflow::S=a,Maxflow::T=b;
	res.push_back(a),res.push_back(b);
	for(int i=1;i<=n;++i){
		type[i]=-1;
		if(i==a||i==b)continue;
		if(Dis(p[a],p[i])>lim||Dis(p[b],p[i])>lim)continue;
		
		if(Para(p[i]-p[a],p[b]-p[a])){
			res.push_back(i);continue;
		}
		
		type[i]=Left(p[i]-p[a],p[b]-p[a]);
	}
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		type[i]==0?Maxflow::adde(a,i,1):Maxflow::adde(i,b,1);
	}
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		for(int j=i+1;j<=n;++j){
			if(!~type[j])continue;
			if(type[i]^type[j]){
				if(Dis(p[i],p[j])>lim){
					type[i]==0?Maxflow::adde(i,j,1):Maxflow::adde(j,i,1);
				}
			}
		}
	}
	Maxflow::Dinic();
	Maxflow::Plan();
	for(int i=1;i<=n;++i){
		if(!~type[i])continue;
		if(type[i]^Maxflow::vis[i])res.push_back(i);
	}
	if(res.size()>ans.size()){
		ans=res;
	}
}
int main(){
	n=read(),D=read();
	for(int i=1;i<=n;++i){
		p[i].x=read(),p[i].y=read();
	}
	ans.push_back(1);
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(Dis(p[i],p[j])<=D*D){
				Solve(i,j);
			}
		}
	}
	printf("%d\n",(int)ans.size());
	for(auto x:ans){
		printf("%d ",x);
	}
	printf("\n");
	return 0;
}
```

---

## 作者：CoronaQL (赞：4)

# 写法
这题可以用随机化来做，每找到一个符合条件的值，就让这个序列重新随机化的排序，这里蒟蒻是用了一个STL中的函数random_shuffle，从而使代码简化，包括结构体和子程序，都是用来简化程序并加速的，而且有一些重要操作放在子程序中返回后，会减少主程序的篇幅及编程者的压力，比如蒟蒻用的sqr，就是模仿乘方操作，并直接在dis里调用，有一些变量也可以在结构体中直接定义，这样就方便了主程序和子程序的编写，蒟蒻就是这么做的，楼下大佬的代码篇幅都好长啊，虽然也有用了随机化的大佬，但是篇幅明显比蒟蒻长，这里不用bitset的原因也是因为太麻烦。下面来看一下蒟蒻的加注释版代码吧！
# accepted answer
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ph//结构体，运行速度快 
{
    int x,y,p;
}p[101],path[101];
int n,m,ans,apa[101],e;
int sqr(int x) //子程序，方便主程序调用 
{
    return x*x;//乘方 
}
int dis(ph a,ph b)
{
   return sqr(a.x-b.x)+sqr(a.y-b.y);//把这行返回 
}
bool check(int x)//比较 
{
    for(int i=1;i<=e;++i)
      if(dis(p[x],path[i])>m*m)
        return false;//找不到正确答案，就返回0 
    return true;//相反则返回1 
}
int main()
{
    scanf("%d%d",&n,&m);//速度快 
    for(int i=1;i<=n;++i)
      {
        scanf("%d%d",&p[i].x,&p[i].y);
        p[i].p=i;
      }
    for(int i=1;i<=1000;++i)
      {
        random_shuffle(p+1,p+1+n);//random_shuffle是用来对一个元素序列进行随机化重新排序（怕大家看不懂） 
        e=0;//e重新赋值 
        for(int j=1;j<=n;++j)
          if(check(j))
            path[++e]=p[j];
        if(e>ans)
          {
            ans=e;//e>ans，ans直接改为t的值 
            for(int j=1;j<=e;++j)
              apa[j]=path[j].p;
          }
      }
    printf("%d\n",ans);
    for(int i=1;i<ans;++i)
      printf("%d ",apa[i]);
    printf("%d\n",apa[ans]);//都是输出 
    return 0;
}
```
希望管理员同志能过一下，蒟蒻感激不尽

---

## 作者：封禁用户 (赞：1)

### 分析
首先，对于两个能相互通信的传感器，很容易能类比到图的边。

那么满足题目要求的最大子集，就是这个图的最大团。

最大团问题可以用 Bron-Kerbosch 算法解决，当然，作为蒟蒻的我肯定不会这个算法。

但是，有一个很好想的贪心策略：\
将 $n$ 个点按一定顺序排序好，再依次判断每个点是否可以加入最大团。\
显然，这个贪心策略是错误的。

但数据范围较小，$n\le 100$，可以考虑随机化贪心。

本题只需一个 $order$ 数组来记录点的顺序。\
即，$order_i$ 表示第 $i$ 个被判定是否能加入最大团的点。

每次循环都将 $order$ 数组随机打乱，直到 ~~TLE~~ 一定的时间为止。

### 评测
AC 记录：


![](https://cdn.luogu.com.cn/upload/image_hosting/n8fevo97.png)

---

## 作者：FutaRimeWoawaSete (赞：1)

**P6900**

讲一下怎么把自己葬送的。

先尝试判断可解性，发现就是旋转卡壳判一下就行了。

一眼下来，我们有一个很假的做法：枚举凸包的直径，然后在这上面直接暴力加独立集，但很可惜，这是错误的。

但是你发现一个事实：作为答案点集的节点集合的凸包显然存在一个直径，那我们计算所有边长作为答案的时候剩下可行边的最大团肯定是可行的。

尝试再次放缩一下边界，我在考场上想到的是直接令当前的直径边长为 $\text{2r}$，然后两个端点以 $\text {r}$ 为半径做圆交出来一个公共图形，直接数这个公共图形里的点数。

然后凭直接感觉内部还是要做一个最大团的处理，但是以为数据很水于是直接乱搞最后只有 $\text{20}$，被讹了。

其实正解就差一步：剩下的问题是，你发现以枚举的凸包直径为轴，两半节点们小于等于直径长度就连边，两半节点内部连成完全图（显然任意一半里最长边长度小于直径）。

然后直接转成补图，原问题等价于补图的最大独立集，发现直接二分图了，蚌。

刚才点开题解看了下，貌似 froggy 的图画的挺好的。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Inf = 1e9;
const int Len = 105 , MM = 10005;
int n,m;
struct P
{
	double x,y;
	P(){x = y = 0;}
	P(double X,double Y){x = X , y = Y;} 
	inline void clr(){x = y = 0;}
	inline double operator ^ (const P &Ano) const
	{return (x * Ano.y) - (y * Ano.x);}
	inline P operator - (const P &Ano) const
	{return P(x - Ano.x , y - Ano.y);}
}pt[Len];
inline double dis(P x,P y){return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));}
struct line
{
	P a,b;
	line(){a.clr() , b.clr();}
	line(P A,P B){a = A , b = B;}
};
inline bool judge(line A,P bot)
{
	return ((A.b - A.a) ^ (A.b - bot)) <= 0;
}
struct XYL
{
	int head[Len],cnt,dep[Len],cur[Len],flag[Len],S,T,N;
	XYL(){cnt = 1;}
	struct node
	{
		int next,to,w;
	}edge[MM << 1];
	inline void add(int from,int to,int w)
	{
		edge[++ cnt].to = to;
		edge[cnt].next = head[from];
		edge[cnt].w = w;
		head[from] = cnt;
	}
	inline void adeg(int from,int to,int w){add(from , to , w) , add(to , from , 0);}
	inline void clr(){S = n + 1 , T = n + 2;for(int i = 1 ; i <= n + 2 ; i ++) head[i] = 0;cnt = 1;}
	inline int BFS()
	{
		queue<int> Q;
		for(int i = 1 ; i <= n + 2 ; i ++)
		{
			dep[i] = Inf , cur[i] = flag[i] = 0;
		}
		Q.push(S);
		dep[S] = 1 , cur[S] = head[S];
		while(!Q.empty())
		{
			int p = Q.front();Q.pop();
			for(int e = head[p] ; e ; e = edge[e].next)
			{
				int to = edge[e].to;
				if(dep[to] == Inf && edge[e].w)
				{
					dep[to] = dep[p] + 1;
					cur[to] = head[to];
					Q.push(to);
					if(to == T) return 1;
				}
			}
		}
		return 0;
	}
	int dfs(int u,int In)
	{
		if(u == T) return In;
		int Out = 0;
		flag[u] = 1;
		for(int e = cur[u] ; e && In > 0 ; e = edge[e].next)
		{
			cur[u] = e;
			int to = edge[e].to;
			if(edge[e].w && dep[to] == dep[u] + 1 && !flag[to])
			{
				int res = dfs(to , min(In , edge[e].w));
				In -= res;
				Out += res; 
				edge[e].w -= res;
				edge[e ^ 1].w += res;
			}
		}
		flag[u] = 0;
		if(!Out){return dep[u] = 0;}
		return Out;
 	}
}S;
struct BOT
{
	double ds;int w;
	BOT(){ds = w = 0;}
	BOT(double DS,int W){ds = DS , w = W;}
}M[Len * Len * Len];int len;
bool cmp(BOT x,BOT y){return x.ds < y.ds;}
vector<int> P;
signed main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%lf %lf",&pt[i].x,&pt[i].y);
	}
	int mx = 0;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = i + 1 ; j <= n ; j ++)
		{
			//printf("!!!%d %d\n",i,j);
			S.clr();line now = line(pt[i] , pt[j]);double ds = dis(pt[i] , pt[j]);
			if(ds > m) continue;
			vector<int> V;
			for(int k = 1 ; k <= n ; k ++)
			{
				if(max(dis(pt[k] , pt[i]) , dis(pt[k] , pt[j])) > ds) continue;
				if(k == i || k == j) continue;
				V.push_back(k);
				if(judge(now , pt[k])) 
				{
					S.adeg(S.S , k , 1);
				}
				else S.adeg(k , S.T , 1);
			}
			const int SZ = (int)V.size();int x = 0 , y = 0;	
			//printf("%d\n",SZ);
			for(int k = 0 ; k < SZ ; k ++) 
				for(int p = k + 1 ; p < SZ ; p ++)
				{
					x = V[k] , y = V[p];
					if(!judge(now , pt[x])) swap(x , y);
					if(dis(pt[x] , pt[y]) > ds) S.adeg(x , y , Inf); 
				}
			int dl = 0;
			while(S.BFS()) dl += S.dfs(S.S , Inf);
			const int as = SZ + 2 - dl;
			if(mx < as) 
			{
				mx = as;
				P.clear();
				for(int e = S.head[S.S] ; e ; e = S.edge[e].next)
				{
					int to = S.edge[e].to;
					if(S.dep[to] != Inf) P.push_back(to);
				}
				for(int e = S.head[S.T] ; e ; e = S.edge[e].next)
				{
					int to = S.edge[e].to;
					if(S.dep[to] == Inf) P.push_back(to);
				}
				P.push_back(i) , P.push_back(j);
			}
		}
	if(!mx)
	{
		printf("1\n1\n");
		return 0;
	}
	/*sort(M + 1 , M + 1 + len , cmp);
	int bs = 0 , mx = 1;
	for(int i = 0 ; i <= m ; i ++)
	{
		while(bs + 1 <= len && M[bs + 1].ds <= i) 
		{
			bs ++;
			mx = max(mx , M[bs].w);
		}
		printf("%d ",mx);
	}*/
	printf("%d\n",mx);
	sort(P.begin() , P.end());
	for(int i = 0 ; i < (int)P.size() ; i ++) printf("%d ",P[i]);
	return 0;
}
```

---

## 作者：_cbw (赞：0)

各位大佬都用了非常好的确定性的计算几何方法！！！

蒟蒻就只能来一篇随机化题解了。（题解区的其它随机化题解好像都没分析正确率捏）

## 问题转换

考虑将可以直接通信的点对之间连边，原题转化为求一张图的最大团。

## 最大团的随机化算法

过程如下：

1. 生成一个 $1 \sim n$ 的排列，并将其随机打乱。
2. 维护集合 $S$ 表示当前求出的最大团。遍历排列，若当前点与 $S$ 内所有点都有直接连边，则向 $S$ 中加入该点。否则什么也不做。
3. 重复上述过程合适次数，并更新最优解。

## 正确率分析

考虑最坏情况下这张图会长什么样：

![三元环套菊花](https://cdn.luogu.com.cn/upload/image_hosting/wekp6l27.png)

是的，三元环套菊花。

此时，求出的解正确当且仅当排列的前两个点在 $1 \sim 3$ 之间。第一个点符合要求的概率为 $\frac{3}{n}$，在此条件下第二个点符合要求的概率为 $\frac{2}{n - 1}$。因此，随机一次的正确率为 $\frac{6}{n(n - 1)}$。由上，随机 $t$ 次的正确率为 $1 - \left[1 - \frac{6}{n(n - 1)} \right]^t$。

在本题的数据范围与时间限制下，$t$ 至少可以为 $2 \times 10^5$，相应的正确率约为 $1 - 2.199308347\times10^{-53}$，是绰绰有余的。

## 代码

如果不喜欢卡时的话可以把 `while (curtime() - bg < 1950)` 一句改为 `for (int _ = 0; _ < SuitableTimes; ++_)`。`SuitableTimes` 可以自己选一个合适的数。实测填 $300000$ 能过，最慢 $1.39\mathrm{s}$。

码风有点丑，请见谅。

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#define MAXN 103
#define curtime() (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count())
using namespace std;

inline int pow2(const int x)
{
    return x * x;
}

int main()
{
    struct
    {
        int x, y;
    } pos[MAXN];
    int ans = 0, vecp, vec[MAXN], a[MAXN], ansa[MAXN];
    bool ok[MAXN][MAXN];

    auto bg = curtime();
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, d;
    cin >> n >> d;
    for (int i = 1; i <= n; ++i)
        cin >> pos[i].x >> pos[i].y;
    d *= d;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ok[i][j] = (pow2(pos[i].x - pos[j].x) + pow2(pos[i].y - pos[j].y) <= d);
    mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    iota(a + 1, a + n + 1, 1);
    bool flag;
    while (curtime() - bg < 1950)
    {
        shuffle(a + 1, a + n + 1, rng);
        vecp = 0;
        for (int i = 1; i <= n; ++i)
        {
            flag = true;
            for (int j = 1; j <= vecp; ++j)
            {
                if (!ok[a[i]][vec[j]])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                vec[++vecp] = a[i];
        }
        if (vecp > ans)
        {
            ans = vecp;
            copy(vec + 1, vec + vecp + 1, ansa + 1);
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= ans; ++i)
        cout << ansa[i] << ' ';
    return 0;
}
```

---

## 作者：FangZeLi (赞：0)

## Link

[[ICPC2014 WF]Sensor Network](https://www.luogu.com.cn/problem/P6900)

## Solution

~~啥，最大团问题。这不是NPC的吗，直接模拟退火啊。~~

好吧这个问题还是有点区别的，主要是因为在一个平面上。

题解区里神Froggy已经给出了一个非常优秀的多项式复杂度做法，下面我会试着从这个问题相较最大团问题的区别的角度，来试图自然的引入这个算法。

关键区别就一句话：在原有的最大团问题中，引入新的点**可能改变原有的点之间的距离**，而在这个平面图上不会。

那么基于这样一个性质，我们就可以枚举最远点对，然后找出这种情况下所有可能进入最大团的点。

然后我们再考虑这些点内部的限制，发现形式上是某些点不能同时选，是一个二分图匹配可以解决的问题，于是就做完了。

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>

#define _N 210
#define _EPS 1e-8
#define _INF 0x3f3f3f3f

struct Tuple {
	double x, y;
	Tuple() {
		x = y = 0;
	}
	Tuple(double a, double b) {
		x = a, y = b;
	}
};

Tuple inline operator -(const Tuple& left, const Tuple& right) {
	return Tuple(left.x - right.x, left.y - right.y);
}
double inline operator %(const Tuple& left, const Tuple& right) {
	return left.x * right.y - left.y * right.x;
}

struct Side {
	int to, w, nxt;
	Side() {
		to = w = nxt = 0;
	}
	Side(int x, int y, int z) {
		to = x, w = y, nxt = z;
	}
};

template<int N, int M>
struct Graph {
	int sidecnt;
	int head[N];
	Side sides[M << 1];
	void inline clear() {
		sidecnt = 1;
		memset(head, 0x00, sizeof(head));
	} 
	Graph() {
		clear();
	}
	
	void inline adde(int x, int y, int z, bool rep = true) {
//		printf("adde: %d %d %d\n", x, y, z);
		sides[++sidecnt] = Side(y, z, head[x]);
		head[x] = sidecnt;
		if (rep) {
			adde(y, x, 0, false);
		}
	}
};

typedef Tuple Point;
typedef Tuple Vec;

int inline sgn(double val) {
	if (val < -_EPS) {
		return -1;
	}
	if (val > _EPS) {
		return 1;
	}
	return 0;
}
double inline len(const Vec& val) {
	return sqrt(val.x * val.x + val.y * val.y);
}

int n, d;

bool type[_N];
Point pt[_N];

Graph<_N, _N * _N> g;

std::vector<int> ans, res;

int s, t;
bool inq[_N], vis[_N];
int e[_N], h[_N], gap[_N << 1];
std::queue<int> q;
struct cmp {
	bool operator()(int left, int right) {
		return h[left] < h[right];
	}
};
std::priority_queue<int, std::vector<int>, cmp> pq;

bool inline check(Point x, Point y, Point z, double lim) {
	return sgn(len(x - z) - lim) <= 0 && sgn(len(y - z) - lim) <= 0;
}

void inline clear() {
	memset(inq, 0x00, sizeof(inq));
	memset(e, 0x00, sizeof(e));
	memset(h, 0x3f, sizeof(h));
	memset(gap, 0x00, sizeof(gap));
	memset(vis, 0x00, sizeof(vis));
}
bool bfs() {
	h[t] = 0, q.push(t);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int nxt = g.head[x]; nxt; nxt = g.sides[nxt].nxt) {
			int y = g.sides[nxt].to, w = g.sides[nxt ^ 1].w;
			if (w && h[y] > h[x] + 1) {
				h[y] = h[x] + 1;
				q.push(y);
			}
		}
	}
	return h[s] != _INF;
}
void dfs(int x) {
	vis[x] = true;
	for (int nxt = g.head[x]; nxt; nxt = g.sides[nxt].nxt) {
		int y = g.sides[nxt].to;
		if (g.sides[nxt].w && !vis[y]) {
			dfs(y);
		}
	}
}
void push(int x) {
	for (int nxt = g.head[x]; nxt; nxt = g.sides[nxt].nxt) {
		int y = g.sides[nxt].to, w = g.sides[nxt].w;
		if (w && h[y] + 1 == h[x]) {
			int v = std::min(w, e[x]);
			e[x] -= v, e[y] += v;
			g.sides[nxt].w -= v, g.sides[nxt ^ 1].w += v;
			if (y != s && y != t && !inq[y]) {
				pq.push(y), inq[y] = true;
			}
			if (!e[x]) {
				return;
			}
		}
	}
}
void relabel(int x) {
	h[x] = _INF;
	for (int nxt = g.head[x]; nxt; nxt = g.sides[nxt].nxt) {
		int y = g.sides[nxt].to, w = g.sides[nxt].w;
		if (w && h[y] + 1 < h[x]) {
			h[x] = h[y] + 1;
		}
	}
}

int HLPP() {
	if (!bfs()) {
		return 0;
	}
	h[s] = n;
	for (int x = 1; x <= n; x++) {
		if (h[x] != _INF) {
			gap[h[x]]++;
		}
	}
	for (int nxt = g.head[s]; nxt; nxt = g.sides[nxt].nxt) {
		int y = g.sides[nxt].to, w = g.sides[nxt].w;
		if (w && h[y] != _INF) {
			e[y] += w;
			g.sides[nxt].w -= w, g.sides[nxt ^ 1].w += w;
			if (y != s && y != t && !inq[y]) {
				pq.push(y), inq[y] = true;
			}
		}
	}
	while (!pq.empty()) {
		int x = pq.top();
		inq[x] = false, pq.pop();
		push(x);
		if (e[x]) {
			gap[h[x]]--;
			if (!gap[h[x]]) {
				for (int y = 1; y <= n; y++) {
					if (y != s && y != t && h[y] > h[x] && h[y] < n + 1) {
						h[y] = n + 1;
					}
				}
			}
			relabel(x);
			gap[h[x]]++;
			pq.push(x), inq[x] = true;
		}
	}
	return e[t];
}

void calc(int x, int y) {
	clear();
	g.clear();
	s = x, t = y;
	double dis = len(pt[y] - pt[x]);
	for (int i = 1; i <= n; i++) {
		if (i != x && i != y && check(pt[x], pt[y], pt[i], dis)) {
			type[i] = sgn((pt[y] - pt[x]) % (pt[i] - pt[x])) >= 0;
			if (type[i]) {
				g.adde(x, i, 1);
			} else {
				g.adde(i, y, 1);
			}
		}
	}
	for (int p = 1; p <= n; p++) {
		if (p != x && p != y && check(pt[x], pt[y], pt[p], dis)) {
			for (int q = 1; q <= n; q++) {
				if (q != x && q != y && check(pt[x], pt[y], pt[q], dis)) {
					if (sgn(len(pt[q] - pt[p]) - dis) > 0) {
						if (type[p]) {
							g.adde(p, q, 1);
						} else {
							g.adde(q, p, 1);
						}
					}
				}
			}
		}
	}
	HLPP();
	dfs(x);
	for (int i = 1; i <= n; i++) {
		if (i != x && i != y && check(pt[x], pt[y], pt[i], dis) && (!type[i] ^ vis[i])) {
			res.push_back(i); 
		}
	}
	res.push_back(x);
	res.push_back(y);
	if (res.size() > ans.size()) {
		std::swap(res, ans);
	}
	res.clear();
}

 
int main() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &pt[i].x, &pt[i].y);
	}
	ans.push_back(1);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (sgn(len(pt[i] - pt[j]) - 1.0 * d) <= 0) {
				calc(i, j);
			}
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < (int)ans.size(); i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}
```

这个是对拍时候用的随机生成器：

```cpp
#include <cstdio>
#include <cstdlib>

#define _N 100
#define _LIM 10000

int main() {
	printf("%d %d\n", _N, _LIM);
	for (int i = 1; i <= _N; i++) {
		printf("%d %d\n", rand() % (_LIM + 1), rand() % (_LIM + 1));
	}
	return 0;
}
```

## Inspiration

我认为这道题的核心思路就是注意到这个题和NPC的最大团问题的区别，然后具体问题具体分析，就可以得到一个合理的多项式算法。

核心结论：

- 平面图上向团内加入一点，已有的距离不会改变。

---

