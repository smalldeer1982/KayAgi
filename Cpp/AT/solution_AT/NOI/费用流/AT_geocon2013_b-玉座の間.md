# 玉座の間

## 题目描述

[problemUrl]: https://atcoder.jp/contests/geocon2013/tasks/geocon2013_b

 あなたは、両親から引き継いだ、川と緑に囲まれた小さいながらも豊かな王国の統治者です。  
 王位を引き継ぐにあたって玉座の間の改装を行うことにしました。  
 とても几帳面なあなたは家具が左右対称になっていないと気がすみません。  
 しかし、家具をあちこち移動させていると改装費がかさんでしまいます。  
 あなたは家具を左右対称になるように動かす時の、家具の移動距離の合計を最小化することにしました。

 家具は2次元上の点として考えます。家具には種類がなく、区別しません。  
 左右対称な状態とは、y軸について反転させた時に同じ状態になることです。  
 例えば、(-1,0),(0,0),(1,0)に家具がある状態は、反転させると(-1,0),(0,0),(1,0)となり、同じ状態なので左右対称です。  
 しかし、(-1,0),(1,0),(1,0)に家具がある状態は、反転させると(-1,0),(-1,0),(1,0)となり、違う状態なので左右対称ではありません。  
 家具はどのような経路でも動かせて、家具同士が重なってもかまいません。

 入力は以下の形式で標準入力から与えられる。 > $ N $ $ X1\ Y1 $ $ X2\ Y2 $ $ ... $ $ XN\ YN $

- 1行目には家具の数を表す整数 $ N $ が与えられる。
- 2行目からN+1行目には家具の座標を表す整数 $ Xi\ Yi\ (1\ ≦\ i\ ≦\ N\ ,\ -1000\ ≦\ Xi,Yi\ ≦\ 1000) $ が空白区切りで与えられる。
- 与えられる家具の座標はすべて異なる。すなわち、$ i\ ≠\ j $ ならば $ (Xi,Yi)\ ≠\ (Xj,Yj) $ を満たす。
 
 左右対称にするのに必要な家具の移動距離の合計の最小値を出力すること。  
 小数点以下何桁でも出力してよく、絶対誤差・相対誤差の少なくとも片方が10-6以下であれば正答と見なされる。 この問題は(1)〜(4)の部分点に分かれていて、それぞれ以下の条件を満たします。

- (1) 50点 : $ N\ =\ 1 $
- (2) 50点 : $ 1\ ≦\ N\ ≦\ 10 $
- (3) 50点 : $ 1\ ≦\ N\ ≦\ 20 $
- (4) 50点 : $ 1\ ≦\ N\ ≦\ 100 $
 
```

1
1 0
```

 ```

1.0000000
```

 ```

3
-1 0
0 0
1 0
```

 ```

0.0000000
```

すでに左右対称なので家具を移動させる必要はありません。

 ```

2
2 2
-2 1
```

 ```

1.0000000
```

例えば、家具を(2,1.5),(-2,1.5)に移動させると移動距離の合計は1になります。

 ```

8
2 2
7 1
9 -4
-10 1
-6 -9
-6 10
8 8
2 -4
```

 ```

15.6593790
```

# 题解

## 作者：heheheheehhejie (赞：14)

这道题是一道典型的费用流

首先，不存在把家具移动到y轴另一面的情况

其次，每个家具移动后要么与另一个家具对称，要么在y轴上~~（废话）~~

那么拆点限流

将每个家具拆成 2 * n 个点，分别为 i和i+n

首先对于每个i，建立一条S到i的边，流量为1，费用为0，表示一个家具只能移到Y轴或与另外一个家具对称。建一条i+n到T的边，与上一条边同理。

对于一个家具移动后在X轴上的情况，i和i+n之间建一条费用为abs(x[i]),流量为1的边，表示如果这个家具移动到y轴上，需要移动至少abs(x[i])的距离

然 后 对 于 i 家 具 与 j 家 具 ， 建 立 一 条 ( i , j + n )  费用为 i 关 于 Y 轴 对 称 点 与 j 的 距 离 ， 流 量 为 1 的 边 ，表 示 使 移 动 后 这 两 个 家 具 关 于 y 轴 对 称

即( 费 用 为 dis ( -x[i] , y[y] , x[j] , y[j] ) )

这样，能够处理的所有情况的边就建好了。
最后跑一遍最小费用最大流，最小费用就是答案了

# 最后上代码

------------

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdlib>
#include<iostream>
#include<cmath>
#define MAXM 30000010
#define MAXN 51000
#define INF 0x3f3f3f3f
using namespace std;
struct int_Edge
{
	int u,v;
	int w;
	double cost;
	int next;
}Edge[MAXM];
int dis[MAXN],head[MAXN],pre[MAXN],cnt_Edge=1,Maxf_S,Maxf_T;
inline void Insert_Edge(int u,int v,int w,double cost)
{
	++cnt_Edge;Edge[cnt_Edge].u=u;Edge[cnt_Edge].v=v;Edge[cnt_Edge].w=w;Edge[cnt_Edge].cost= cost;Edge[cnt_Edge].next=head[u];head[u]=cnt_Edge;
	++cnt_Edge;Edge[cnt_Edge].u=v;Edge[cnt_Edge].v=u;Edge[cnt_Edge].w=0;Edge[cnt_Edge].cost=-cost;Edge[cnt_Edge].next=head[v];head[v]=cnt_Edge;
}
bool vis[MAXN];
double h[MAXN];
inline bool MCMFSPFA()
{
	static int v;
	for(int i=1;i<MAXN;i++)
		h[i]=1e9+7;
	memset(pre,-1,sizeof(pre));
	h[Maxf_S]=0;
	queue<int>q;
	q.push(Maxf_S);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		vis[u]=false;
		for(register int i=head[u];i;i=Edge[i].next)
		{
			v=Edge[i].v;
			if((h[v]>h[u]+Edge[i].cost)&&Edge[i].w>0)
			{
				h[v]=h[u]+Edge[i].cost;
				pre[v]=i;
				if(!vis[v])
				{
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
	return pre[Maxf_T]!=-1;
}
int MAX_FLOW=0;
double MIN_COST=0.0000000;
inline void MCMF()
{
	while(MCMFSPFA())
	{
		int delt=0x3f3f3f3f;
		double coss=0;
		for(register int i=Maxf_T;i!=Maxf_S;i=Edge[pre[i]].u)
			delt=min(delt,Edge[pre[i]].w);
		for(register int i=Maxf_T;i!=Maxf_S;i=Edge[pre[i]].u)
		{
			Edge[pre[i]].w-=delt;
			Edge[pre[i]^1].w+=delt;
			coss+=Edge[pre[i]].cost;
		}
		
		MAX_FLOW+=delt;
		MIN_COST+=(coss*delt);
	}
}//上面的为费用流的模板
double x[MAXN],y[MAXN];
int main()
{
	int n;
	scanf("%d",&n);
	int SS=n*2+2,TT=n*2+3,TTT=n*3+4;
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
	{
		Insert_Edge(SS,i,1,0.0000000);
		Insert_Edge(i+n,TT,1,0);
		Insert_Edge(i,i+n,1,abs(x[i]));
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)
				continue;
			Insert_Edge(i,j+n,1,sqrt((x[i]+x[j])*(x[i]+x[j])+(y[i]-y[j])*(y[i]-y[j]))/2);
		}
	}
	Insert_Edge(TT,TTT,n,0.0000000);
	Maxf_S=SS;
	Maxf_T=TTT;
	MCMF();
	printf("%.7f",MIN_COST);
	return 0;
}
```


---

## 作者：pure__Elysia (赞：9)

[题目链接](https://www.luogu.com.cn/problem/AT655)

[通过记录](https://www.luogu.com.cn/record/89697881)

# 前言

//前置知识学习 [网络流](https://www.luogu.com.cn/problem/P3376)→[费用流](https://www.luogu.com.cn/problem/P3381)→[（可选）如何尝试建立网络图](https://www.luogu.com.cn/problem/P4048)

# 题目描述
&emsp;&emsp;由于是外面 OJ 的题，稍微简明地翻译一下。

&emsp;&emsp;在平面直角坐标系中，给你 $n$ 个点以及其横纵坐标（都是整数），你的任务是把这些点移动几下，使得这些点沿着 $y$ 轴“对称”。但是移动距离要最少。

&emsp;&emsp;另外，多个点可以放在一个位置。但“对称”的要求是左右对应位置的点数量也要一致。特殊说明，放在 $y$ 轴上的点也算是“对称”的。

# 算法思路
&emsp;&emsp;先说结论：费用流。

```
if（你只想听费用流怎么实现） 

	goto 具体操作

else 

	goto 思路引入
```

## 思路引入

&emsp;&emsp;（先说好奥，你要是都不知道，或者说是没听说过网络流，很难讲了。虽然作为黑题水了点，但多少紫以上，肯定要点前置知识。这里主要是引入如何想到费用流）。

&emsp;&emsp;首先我们想象最简单的情况，两个点怎么对称。

![](https://cdn.luogu.com.cn/upload/image_hosting/vmpx6xjg.png)

&emsp;&emsp;这个问题其实很好想。首先我们不可能傻到把 $A$ 点移动到右边，再把 $B$ 移到左边。我们现在有两个想法，一个是我们传统理解的左右对称，一个是把 $A$ 和 $B$ 都移到 $y$ 轴上。都移到 $y$ 的代价是 $|X_A|+|X_B|$ 。这里也很明显。如果我们采取了这种策略，那么两个点一起和两个点分开想，两者是没有什么区别的。这种策略下， $A$ 和 $B$ 是这样，$A$ 和 $C$ 也这样。所以我们记录时，直接记录在单个点上即可，代价即为 $|X_A|$ 。

&emsp;&emsp;那么左右对称呢。画一个图，易知，如下是最优的（显然，即使 $AB$ 在同侧也是这样的哦）：

![](https://cdn.luogu.com.cn/upload/image_hosting/qrjhjme5.png)

&emsp;&emsp;我们把一个点作对称，与另一个点取中点，那这个点就是咱们要移动的中点（当然，这个点分布在两侧）。这个代价也是好计算的，直接两点间距离公式即可。总代价为 $ \sqrt{(X_A-X_B)^2+(Y_A-Y_B)^2} $ 。这个倒是不像刚才可以记在单个点上，只能存个表（斯……存表？存边？）。

&emsp;&emsp;从三个点开始，其实我们也只能把他们分成一个个的“两个点”“一个点”的情况去考虑。那就涉及到一个分组的问题。

&emsp;&emsp;如果我们确定了 $A-B$ 这样的对应关系的分组，那么就不再可能出现 $A-C$ 、 $B-C$ 这样的对应关系。那么我们要不断尝试的，就是那些能使得所有点都可以分到的组。对于那种直接移到 $y$ 的利己主义或者说是个人英雄主义者，我们就让他变成自己和自己分组就好，方便咱们归纳。

&emsp;&emsp;我怎么总听着没对啊。又是“建图”“建边”，又是“分配”的。我们最近做过的网络流里，似乎就有这些特性。（这里推荐一手 [我之前的blog](https://www.luogu.com.cn/blog/Elysian-Realm/p4048-jsoi2010-leng-dong-bo)，分析了如何去从题目分析想到采用网络流做法）。哦哦哦，这类题应该去尝试网络流的相关做法。

## 具体操作

&emsp;&emsp;我们很强，想到了这题应该尝试用网络流的相关做法。首先先想清楚网络流必备的几个要素：源点、汇点的设立意义，建边的准则，跑网络流的算法。

&emsp;&emsp;我们采取网络流就是因为可以检测一类“分组”问题是否“分组”完全。源点在这里还真不重要，就是让大家“有水可流”就行。汇点使我们用来检测是否分完组的，不能大意。那我们每次分组成功后，就把分好了的点的水流向汇点，设置流量为 $1$ 。这样汇点最后流量总和就是我们分了多少个点。是 $n$ 就说明全部彳亍了。当然，这也就是该网络图的最大流了。所以咱们要求的就是“费用最小最大流”，即“费用流”。（在流量最大的情况下，使得总费用最小）

&emsp;&emsp;之后是建边。我们知道 $A-B$ $B-A$ 这两个分组意义是一样的，但是网络图是不允许有环出现的。那么我们考虑用手捏一些点出来，建立为 $B-A'$ 和 $A-B'$ 这两条边。我们肯定让这种边的流量为 $1$ ，因为一个数分了组之后，怎么能还让你和别的数分组呢。同时，我们思考费用。刚才说到这种分组的总代价是 $ \sqrt{(X_A-X_B)^2+(Y_A-Y_B)^2} $ ，但现在分成了两条边，所以每条边的值要除以 $2$ 。至于自己和自己分组这种，我们仍然记录为 $A-A'$ 。但是这种边又只有一条，所以不做变化，费用就是 $|X_A|$ 。

&emsp;&emsp;这里我们默认了一件事。那就是只准真的点连向我们手搓的点，那我们流向汇点的时候，其实就只建立这些手搓的点流向汇点。

&emsp;&emsp;那我们就处理完了，从头理一遍流程，顺便思考费用流的可行性与细节。

## 流程

&emsp;&emsp;首先，依次读入坐标。读的时候可以同时建立以下的边：（录入函数 `lr()` 内依次是建边的起点，终点，流量，费用，并同时建立反向边，具体写法见代码）

>1.从源点到这个点的。`lr(0,i,1,0.0)`
>
>2.自己与自己分组的。`lr(i,i+n,1,abs(x[i]))`
>
>3.手搓点到汇点的。`lr(i+n,t,1,0.0)`

&emsp;&emsp;然后，依据每两个点的距离、坐标，建立两两分组的边：
> `lr(i,j+n,1,calc(i,j))` （`calc` 用来计算距离）

&emsp;&emsp;然后，拿着这个图给他跑个费用流。最后的费用就是我们的答案了。

&emsp;&emsp;没什么问题？是的，那就是这样做的了。

# 特殊处理

&emsp;&emsp;相对于一道建图的题，只是套了一个费用流的版子。只需要注意就是费用是用 `double` 存，稍微改改，其实和 [冷冻波](https://www.luogu.com.cn/problem/P4048) 这道题真的很像，都是计算几何建边后跑网络图，只不过一个是网络最大流，一个是费用最小最大流。但是那道题实际难点在于计算几何和二分跑网络流的想法，这道题难点在于想到费用流去处理并想到如何存边。或许真的是个水黑题，但是绝对紫题以上是有的。

&emsp;&emsp;另外，费用流几乎就把最弔的 Dinic 给禁了，老老实实跑 SPFA 吧。

# 代码实现
```cpp
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ri register int//小习惯

int n,m,s,t;
int maxflow;
double mincost;

struct side{//存边所用结构体
	int v,w;//终点，流量
	double cos;//费用
	int dmbh;//反向边的编号
};
vector<side>edge[500];//vector单推人捏
//像这样存图，真是好快活呀

int zbx[500],zby[500];//坐标x与坐标y

inline int rd()//读入优化，小小地卡个常
{
	int a=0,f=1;
	char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) a=(a<<1)+(a<<3)+c-'0';
	return a*f;
}

inline double ABS(double x){if(x<0) return -x;else return x;}
//据说自带的min,max,abs都巨慢，咱们手写吧

inline double calc(int i,int j)//计算距离，单独写因为写在里面太挤了
{
	double x_2=(zbx[i]+zbx[j])*(zbx[i]+zbx[j]);
	double y_2=(zby[i]-zby[j])*(zby[i]-zby[j]);
	return sqrt((double)x_2+y_2)/2;
}

inline void lr(int u,int v,int w,double cos)//录入存边
{
	side x;
	
	x.cos=cos, x.dmbh=edge[v].size(),x.v=v,x.w=w;
    //说明一下，vector存反向边编号时要注意
    //这里直接size()，下面存回来时因为存了本条边，所以要size()-1
    
	edge[u].push_back(x);
	
	x.dmbh=edge[u].size()-1;
	x.v=u, x.cos=-cos, x.w=0.0;//反向边流量为0
	
	edge[v].push_back(x);
	
	return ;
}

int flow[500];//SPFA所用到的此时的流量
double cost[500];//此时的费用
bool bj[500];//松弛标记
queue<int>que;//用于优化的队列
int last[500];//每个点前驱连向他时，边的编号
int qq[500];//每个点的前驱

inline int minof(int a,int b){if(a>b)return b;else return a;}
//手写min

inline bool spfa()
{
	memset(flow,127,sizeof(flow));
	memset(cost,127,sizeof(cost));
	memset(bj,0,sizeof(bj));//重要的初始化
	
	que.push(s),bj[s]=1,cost[s]=0.0,qq[t]=-1;//压入源点
	
	while(!que.empty())
	{
		int u=que.front();
		bj[u]=0;
		que.pop();
		int S=edge[u].size();
		for(ri i=0;i<S;i++)//遍历松弛每条边
		{
			int v=edge[u][i].v;
			if(edge[u][i].w>0 && cost[v]>cost[u]+edge[u][i].cos) 
			{//在网络流中，我们只松弛正边
				cost[v]=cost[u]+edge[u][i].cos;
				qq[v]=u;
				last[v]=i;
				flow[v]=minof(flow[u],edge[u][i].w);
				if(!bj[v])
				{
					bj[v]=1;
					que.push(v);
				}
			}
		}
	}
	
	return qq[t]!=-1;
	
}

signed main()
{
	int n=rd();
	s=0,t=n*2+2;//给源点和汇点以编号
	
	for(ri i=1;i<=n;i++)
	{
		int x=rd(),y=rd();
		zbx[i]=x,zby[i]=y;
		
		lr(0,i,1,0.0);
		lr(i,n+i,1,ABS((double)x));
		lr(n+i,t,1,0.0);//读入顺便存边，详见上文
	}
	
	for(ri i=1;i<=n;i++)//挨个每局每两个点，建立边
		for(ri j=i+1;j<=n;j++)
		{
			lr(i,j+n,1,calc(i,j));
			lr(j,i+n,1,calc(i,j));
		}
		
	
	while(spfa())//跑费用流模板
	{
		int x=t;
		maxflow+=flow[t];
		mincost+=flow[t]*cost[t];
		while(x!=s)
		{
			int u=qq[x],i=last[x];
			edge[u][i].w-=flow[t];
			edge[x][edge[u][i].dmbh].w+=flow[t];
			x=qq[x];
		}
	}
	
	printf("%.7f\n",mincost);//搞定！
	
	return 0;
	
} 
```

---

## 作者：lzyqwq (赞：7)

最小费用最大流，首先考虑建模。

考虑拆点，将每个家具 $i$ 拆成 $i$ 和 $i'$。建以下几种边：

- 从 源点 $S$ 向 $i$ 连容量为 $1$， 费用为 $0$ 的边，表示初始的 $n$ 个家具。

- 从 $i'$ 向汇点 $T$ 连容量为 $1$，费用为 $0$ 的边，表示 $n$ 个家具都已经对称了。

- 从 $i$ 向 $i'$ 连容量为 $1$，费用为 $|x_i|$ 的边，表示将家具 $i$ 移到 $y$ 轴上使其与自己对称。

- 对于任意两个家具 $i,j(i\ne j)$，从 $i$ 向 $j'$ 连容量为 $1$，费用为 $\dfrac{\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}}{2}$ 的边，表示将家具 $i$ 移到与家具 $j$ 关于 $y$ 轴对称的点。

这样的建模能保证最大流为 $n$，即每个家具都能对称，同时用费用流求出最小费用，即为答案。

关于第四种边的费用，作者做一些解释：

#### 为什么要除以 $2$？

首先明确一点，移动 $i$ 使 $i,j$ 两点对称的最少费用（每我们要的肯定是最少费用，因为只有每次移动的费用都小到不能再小了，最终的总费用才会最小）为 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$，即家具 $i$ 和与家具 $j$ 关于 $y$ 轴对称的点之间的欧几里得距离（就是最短距离）。

因为与 $j$ 关于 $y$ 轴对称的点坐标为 $P(-x_j,y_j)$，两点欧几里得距离为 $\sqrt{[x_i-(-x_j)]^2+(y_i-y_j)^2}=\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$。

说明完上面的事实后，我们需要将其与具体的算法流程结合起来理解为什么要除以 $2$ 的问题。

因为在使用 `EK+SPFA` 做最小费用最大流的时候，`SPFA` 每次找的是最短的增广路。

然而对于我们刚才的建边方式，可以看出 $i\rightarrow j'$ 的费用等于 $j\rightarrow i'$ 的费用，因此若将一次 `SPFA` 求出的最短增广路中的所有边 $i\rightarrow j'$ 换成 $j\rightarrow i'$（源点 $S$，汇点 $T$ 除外），这条路仍然是最短的。

因此对于任意两点 $i,j$，只要增广了 $i\rightarrow j'$，我们就会去增广 $j\rightarrow i'$。

然而增广一条边的意义是使 $i,j$ 关于 $y$ 轴对称。也就是说在增广第一条边时，$i,j$ 已经对称了，我们不需要计算增广第二条边的费用。

但是这样在算法实现中是不切实际的。

因此我们将费用除以 $2$，这样两条边都被增广后，由于两条边费用相同，除以 $2$ 被抵消掉，因此就算增广了这两条边，使 $i,j$ 两点对称实际付出的费用仍然是 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$，符合事实。

另外一种理解就是，将 $i,j$ 向另一点关于 $y$ 轴的对称点连成线段，将 $i,j$ 移到线段的中点。这种解释看上去貌似更简短，但实际上这种移动方式让人一头雾水，且证明起来更为麻烦。

解决完建模问题后，上板子就行了。注意小数点以及精度问题。

代码如下：

```cpp
//在代码中，源点 S 用 0 表示，i 就用 i 表示，i' 用 i + n 表示，汇点 T 用 2 * n + 1 表示
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5;
int n, hd[N], q[N], h, t, T, cnt = 1, la[N];
bool vis[N];
double d[N], ans;
struct point {
    int x, y;
}a[N];
struct edge {
    int v, w;
    double c;
    int nxt;
}g[N];
inline double dis(int x, int y, int _x, int _y) {
    return sqrt(1.0 * (x - _x) * (x - _x) + 1.0 * (y - _y) * (y - _y));
}
inline void add(int u, int v, int w, double c) {
    g[++cnt] = edge{v, w, c, hd[u]};
    hd[u] = cnt;
}
inline bool spfa() {
    for (int i = 0; i <= T; ++i) {
        d[i] = 1e18;
        vis[i] = 0;
    }
    d[q[h = t = 1] = 0] = 0;
    while (h <= t) {
        int x = q[h++];
        vis[x] = 0;
        for (int i = hd[x]; i; i = g[i].nxt) {
            if (g[i].w && d[x] + g[i].c < d[g[i].v]) {
                la[g[i].v] = i;
                d[g[i].v] = d[x] + g[i].c;
                if (!vis[g[i].v]) {
                    vis[q[++t] = g[i].v] = 1;
                }
            }
        }
    }
    return d[T] < 1e18;
}
signed main() {
    scanf("%lld", &n);
    T = (n << 1) + 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &a[i].x, &a[i].y);
        add(0, i, 1, 0);
        add(i, 0, 0, 0);
        add(i + n, T, 1, 0);
        add(T, i + n, 0, 0);
        add(i, i + n, 1, 1.0 * abs(a[i].x));
        add(i + n, i, 0, -1.0 * abs(a[i].x));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j) {
                add(i, j + n, 1, dis(a[i].x, a[i].y, -a[j].x, a[j].y) / 2);
                add(j + n, i, 0, -dis(a[i].x, a[i].y, -a[j].x, a[j].y) / 2);
            }
        }
    }
    while (spfa()) {
        ans += d[T];
        //增广路流量只能为 1，不需要再乘以流量了，
        //首先，每条增广路上不可能出现流量为 0 的瓶颈边（即决定这条增广路流量的边），
        //因为只有一条边在残量网络中还有流量才会去增广这条边，
        //其次，瓶颈边也不可能比 1 大，因为全图的非 0 边流量都为 1
        for (int i = T; i; i = g[la[i] ^ 1].v) {
            --g[la[i]].w;//增广路流量只能为 1，直接减掉、反向边加上就行了
            ++g[la[i] ^ 1].w;
        }
    }
    printf("%.7lf\n", ans);
    return 0;
}
```

---

## 作者：Gmt丶FFF (赞：5)

首先我们要学习一下费用流。

费用流是什么呢，可以理解为边带权值的网络流。

那么最小费用最大流，是指在满足最大流的情况下的最小费用。

那么我们就要实现这个过程。

首先对于一条有向边，建立的反向边的权值为原权值的相反数。

所以明显图带负数，只能用 SPFA，~~泪目~~。

每一次跑一次 SPFA 找到最短路，当然计算最短路时没有流量的边是不能走的，期间记录流量。

如果发现汇点最短路发生了更新，那么可以从汇点出发，往回跑最短路，然后就是减去流量，对反向边增加流量的操作了。

往回跑最短路可以由每次更新一个点的最短路值时记录从哪一个点转移过来的即可。

本题也是一个费用流。

首先可以保证，在 $y$ 轴同侧的两点不会出现一个点跑到另一个坐标轴与另外一点进行匹配的情况，这个应该很好证。

所以对于坐标轴两边的点，可能都是能匹配的，那么就可以连边，而对于每一个点，也可以连 $y$ 轴，所以也与 $y$ 轴连边。

综上，我们可以考虑建出这个图。

首先，将每个点复制成两份，从 $1$ 到 $n$，与从 $n+1$ 到 $2\times n$。

第二步，将源点 $S$ 与 $1$ 到 $n$ 连边，流量为 $1$，边权为 $0$。

第三步，走 $y$ 轴，可以理解为自己与自己匹配，连接 $i$ 与 $i+n$，流量为 $1$，边权为 $\left|x_i\right|$。

第四步，连接坐标轴两边的点，当 $x_i\times x_j<0$ 时，说明在坐标轴两端，连接 $i$ 与 $j+n$，流量为 $1$，边权为 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}\div 2$。因为如果要匹配会匹配两次，所以要每次除以 $2$，而连向 $y$ 轴只有一次，所以不需要除以 $2$。

第五步，连接 $n+1$ 到 $2\times n$ 与汇点 $T$，流量为 $1$，边权为 $0$。

最后跑最小费用最大流即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<deque>
#include<vector>
using namespace std;
const int N=205;
int n;
inline double tabs(int x)
{
	return x>0?x:-x;
}
struct node2
{
	int x,y;
}t[N];
struct node
{
	int to,v;
	double w;
};
vector<node>a[N];
vector<int>b[N];
deque<int>q;
double dis[N],ans;
bool vis[N];
int incf[N],pre[N];
bool spfa()
{
	for(int i=1;i<=2*n+3;i++)dis[i]=1e9;
	memset(vis,0,sizeof(vis));
	q.push_back(2*n+1);
	dis[2*n+1]=0;
	incf[2*n+1]=1e9;
	while(!q.empty())
	{
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		int len=a[x].size();
		for(int i=0;i<len;i++)
		{
			if(!a[x][i].v)continue;
			if(dis[x]+a[x][i].w<dis[a[x][i].to])
			{
				dis[a[x][i].to]=dis[x]+a[x][i].w;
				incf[a[x][i].to]=min(incf[x],a[x][i].v);
				pre[a[x][i].to]=b[x][i];
				if(!vis[a[x][i].to])
				{
					if(!q.empty()&&dis[a[x][i].to]<dis[q.front()])q.push_front(a[x][i].to);
					else q.push_back(a[x][i].to);
					vis[a[x][i].to]=0;
				}
			}
		}
	}
	if(dis[2*n+3]<1e9-1e-9)return true;
	return false;
}
void dinic()
{
	while(spfa())
	{
		int x=2*n+3;
		ans+=dis[2*n+3]*incf[2*n+3];
		while(x!=2*n+1)
		{
			int t=pre[x];
			int p=a[x][t].to;
			a[x][t].v+=incf[2*n+3];
			a[p][b[x][t]].v-=incf[2*n+3];
			x=p;
		}
	}
}
int main()
{
	//freopen("aichemy.in","r",stdin);
	//freopen("aichemy.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&t[i].x,&t[i].y);
	for(int i=1;i<=n;i++)
	{
		a[2*n+1].push_back({i,1,0});
		a[i].push_back({2*n+1,0,0});
		b[2*n+1].push_back(a[i].size()-1);
		b[i].push_back(a[2*n+1].size()-1);
		for(int j=1;j<=n;j++)
		{
			if(t[j].x*t[i].x<0)
			{
				a[i].push_back({j+n,1,sqrt((t[i].x+t[j].x)*(t[i].x+t[j].x)+(t[i].y-t[j].y)*(t[i].y-t[j].y))/2});
				a[j+n].push_back({i,0,-sqrt((t[i].x+t[j].x)*(t[i].x+t[j].x)+(t[i].y-t[j].y)*(t[i].y-t[j].y))/2});
				b[i].push_back(a[j+n].size()-1);
				b[j+n].push_back(a[i].size()-1);
			}
		}
		a[i+n].push_back({2*n+3,1,0});
		a[2*n+3].push_back({i+n,0,0});
		b[i+n].push_back(a[2*n+3].size()-1);
		b[2*n+3].push_back(a[i+n].size()-1);
		a[i].push_back({i+n,1,tabs(t[i].x)});
		a[i+n].push_back({i,0,-tabs(t[i].x)});
		b[i].push_back(a[i+n].size()-1);
		b[i+n].push_back(a[i].size()-1);
	}
	dinic();
	printf("%.7lf",ans);
	return 0;
}
/*
3
1 2
-1 3
-2 0
*/
```


---

## 作者：DiruiXiao (赞：4)

## [AT655 玉座の間](https://www.luogu.com.cn/problem/AT655)

**【题意简述】**

给定 $n$ 个点，第 $i$ 个点的位置坐标为 $(x_i,y_i)$。现可以花费 $\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}$  将其移动到 $(y_i,y_j)$。现要求最小化花费 $C$，使得该平面上所以的点组成的图案关于 $y$ 轴对称。

**【解题思路】**

发现点的移动只有两种方案，要么移动到 $y$ 轴，要么与 $y$ 轴另一边的点匹配。~~有点像二分图匹配~~

于是考虑网络流，建立超级源点 $S$，超级汇点 $T$，并且将第 $i$ 个点拆成 $i$ 和 $i +n$ 两个点。

首先从 $S$ 向 $i$ 建一条流量为 $1$，费用为 $0$ 的边。

然后对于所有 $i$ 和 $i +n$ 的点建一条流量为 $1$，费用为 $|x_i|$  的边，表示将 $i$ 移到 $y$ 轴。

而对于所有 $i\neq j$ 的点，建一条流量为 $1$，费用为 $\dfrac{\sqrt{(x_i+x_j)^2+(y_i-y_j)}}{2}$ 的边（除以 $2$ 是因为如果匹配 $i$ 和 $j$，可以看做同时增广了 $E(i,j)$ 和 $E(j,i)$）。

最后对于所有 $n+i$ 的点，向 $T$ 连一条流量为 $1$ 费用为 $0$ 的边用于统计答案。

此时的答案即是构造的网络中的最小费用最大流。

我用的是 $\texttt{Dinic}$ 版本的 $\texttt{MCMF}$ 。

**【AC代码】**

```cpp
#include<bits/stdc++.h>
#define MAXN 250
#define MAXM 15050
#define INF (int)(1e9)
using namespace std;

struct Edge{
	int v, nex, w; double c;
} edge[MAXM << 1];

int x[MAXN], y[MAXN], head[MAXN], ecnt = 1, S = 0, T, maxflow, n;
double dis[MAXN], mincost;
bool inq[MAXN];

inline void addEdge(int u, int v, int w, double c) {
	edge[++ecnt].v = v;
	edge[ecnt].nex = head[u];
	edge[ecnt].w = w;
	edge[ecnt].c = c;
	head[u] = ecnt;
	edge[++ecnt].v = u;
	edge[ecnt].nex = head[v];
	edge[ecnt].w = 0;
	edge[ecnt].c = -c;
	head[v] = ecnt;
}

inline bool SPFA() {
    for (int i = 1; i <= n * 2 + 5; ++i) dis[i] = INF, inq[i] = 0;
    queue<int> q; q.push(S); dis[S] = 0; inq[S] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inq[u] = 0;
        for (int i = head[u]; i; i = edge[i].nex) {
        	int v = edge[i].v;
			if (edge[i].w > 0 && dis[v] > dis[u] + edge[i].c) {
				dis[v] = dis[u] + edge[i].c;
				if (!inq[v]) {
					q.push(v);
					inq[v] = 1;
				}
			}
        }
    }
    if (dis[T] == (double)INF) return 0;
    return 1;
}

inline int DFS(int u, int sum) {
	if (u == T) return sum;
	int res = 0, k;
	for (int i = head[u]; i && sum; i = edge[i].nex) {
		int v = edge[i].v;
		if (inq[v]) continue;
		if (edge[i].w > 0 && dis[v] == dis[u] + edge[i].c) {
			inq[v] = 1;
			k = DFS(v, min(sum, edge[i].w));
			inq[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			res += k;
			sum -= k;
		}
	}
	return res;
}


inline void MCMF() {
	while (SPFA()) {
		int d = DFS(S, INF);
		mincost += d * dis[T];
	}
}

int main() {
	scanf("%d", &n);
	S = n * 2 + 2, T = n * 2 + 3;
	for (int i = 1; i <= n; ++i) scanf("%d %d", x + i, y + i);
	for (int i = 1; i <= n; ++i) {
		addEdge(S, i, 1, 0);
		addEdge(n + i, T, 1, 0);
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue; 
			addEdge(i, n + j, 1, sqrt(1.0 * (x[i] + x[j]) * (x[i] + x[j]) + 1.0 * (y[i] - y[j]) * (y[i] - y[j])) / 2);
		}
		addEdge(i, i + n, 1, abs(x[i]));
	}
	MCMF();
	printf("%.7lf\n", mincost);
	return 0;
}
```



---

## 作者：SuBtitle (赞：3)

# AT655 玉座の間

## 分析

#### 如何构造对称

- 首先，一个物体不可能从 y 轴的一边移动到另一边。为什么？考虑几种情况
  - 坐标轴两边的物体相匹配。此时两个物体只需在各自的半轴移动就可以对称，最优解就是 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$
  - 坐标轴同侧的物体相匹配。将一个物体移到另一侧的代价是 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$，而将两个物体都移到 y 轴的代价为 $\lvert x_i+x_j \rvert$ 
- 所以问题实际上就是求 y 轴两侧的物体的一种匹配方案，使得花费最小，当然所有物体都可以与 y 轴匹配。
- 于是就可以将其转化为最小费用最大流模型
  - 将所有点分为 $i,i+n$，代表主动匹配和被动匹配
  - 建立一个源点 $s$ 和一个汇点 $t$，将 $s$ 向 $i$ 连边，容量为 $1$，费用为 $0$，将 $i+n$ 向 $t$ 连边，容量为 $1$，费用为 $0$
  - 将 $i$ 向 $i+n$ 连边，容量为 $1$，费用为 $\lvert x_i \rvert$，代表匹配自己，也就是移到 y 轴
  - 将 $i$ 向 $j+n$ 连边，容量为 $1$，费用为 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$，代表将 $i$ 和 $j$ 匹配（注意连边时不必判断 $i,j$ 是否处于坐标轴两侧，如果处于同侧，则将其匹配不是最优方案，故不会产生贡献）

#### 关于最小费用最大流

- 可以使用最大流的 dinic 算法，将其使用 bfs 分层的过程改为用 SPFA 求最短路，将其 dfs 时的判断是否位于下一层改为判断其 $dis$ 是否由当前点得到。注意要使用 $vis$ 数组判断当前点是否已在增广路中，因为 $u\rightarrow v$ 和 $v\rightarrow u$ 的路径都可行

## 注意

- 因为在连边时，$i$ 会向 $j+n$ 连边，$j$ 也会向 $i+n$ 连边，所以 $i,j$ 的匹配会计算 $2$ 次贡献，所以要将这种连边的费用置为原来的一半

## 代码

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

const int N=210;
int n,s,t,tot=1,head[N],q[N],front,tail,first[N],ax[N],ay[N];
double anscost,dis[N];
bool vis[N];

template<typename T>inline T mabs(T x)
{
	return x>0?x:-x;
}

struct Edge
{
	int v,flow,nex;
	double cost; 
}E[N*N*3];

void AddEdge(int u,int v,int flow,double cost)
{
	++tot;
	E[tot].v=v;
	E[tot].flow=flow;
	E[tot].cost=cost;
	E[tot].nex=head[u];
	head[u]=tot;
}

bool equ(double x,double y)					//判断double型数据是否相等
{
	double tmp=x-y;
	if(tmp>-1e-12&&tmp<1e-12)
		return 1;
	return 0;
}

bool SPFA()
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n*2+2;++i)
		dis[i]=1e12;
	dis[s]=0;
	vis[s]=1;								//此处的vis和dfs中的vis是互不干扰的，因为每次SPFA过后vis都会变为0
	front=tail=1;
	tail=(tail+1)%N;
	q[tail]=s;
	int now;
	while(front!=tail)
	{
		front=(front+1)%N;
		now=q[front];
		vis[now]=0;
		for(int i=head[now];i;i=E[i].nex)
		{
			if(!E[i].flow) continue;
			int v=E[i].v;
			if(dis[v]>dis[now]+E[i].cost)
			{
				dis[v]=dis[now]+E[i].cost;
				if(!vis[v])
				{
					tail=(tail+1)%N;
					q[tail]=v;
					vis[v]=1;
				}
			}
		}
	}
	if(dis[t]!=1e12) return 1;
	return 0;
}

int dfs(int x,int mxf)						//x是当前点，mxf是找到的最大流量
{
	if(!mxf||x==t) return mxf;
	int ret=0;
	vis[x]=1;
	for(int &i=first[x];i;i=E[i].nex)
	{
		int v=E[i].v;
		if(!E[i].flow||vis[v]) continue;
		if(equ(dis[v],dis[x]+E[i].cost))
		{
			int f=dfs(v,min(mxf,E[i].flow));
			if(f)
			{
				E[i].flow-=f;
				E[i^1].flow+=f;
				anscost+=E[i].cost*f;
				ret+=f;
				mxf-=f;
			}
		}
	}
	vis[x]=0;
	return ret;
}

void dinic()
{
	while(SPFA())
	{
		memcpy(first,head,sizeof(head));
		while(dfs(s,0x7f7f7f7f));
	}
}

double GetDis(int x,int y)
{
	int x1=-ax[x];
	return sqrt((ay[x]-ay[y])*(ay[x]-ay[y])+(x1-ax[y])*(x1-ax[y]));
}

int main()
{
	scanf("%d",&n);
	s=n*2+1,t=n*2+2;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&ax[i],&ay[i]);
		AddEdge(s,i,1,0);
		AddEdge(i,s,0,0);
		AddEdge(i+n,t,1,0);
		AddEdge(t,i+n,0,0);
		AddEdge(i,i+n,1,mabs(ax[i]));
		AddEdge(i+n,i,0,-mabs(ax[i]));
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
			{
				AddEdge(i,j+n,1,GetDis(i,j)/2.0);
				AddEdge(j+n,i,0,-GetDis(i,j)/2.0);
			}
	dinic();
	printf("%.7lf",anscost);
	return 0;
}
```



---

## 作者：JimmyLee (赞：1)

前置知识：[费用流](https://oi-wiki.org/graph/flow/min-cost/)

# 题目分析

## 题意

> 平面上有 $n$ 个点，你要给每个点移动位置，使得最终的图形沿 $y$ 轴对称。求移动的欧几里得距离之和的最小值。

其实从题干想到费用流确实很神奇。

但是想到之后后继步骤还是很简单的。

## 解法

首先易得以下几条结论：

- 把一个点移到 $y$ 轴的另一面并不优。（感性理解一下即可）

- 把一个点**移到 $y$ 轴上**也是满足条件的。

所以可能会想到分成 $y$ 轴左侧和 $y$ 轴右侧两部分进行匹配。

**但是两边都可以互相匹配。**

所以得到下一个神仙想法：**拆点**。

将第 $i$ 个点拆为 $L_i$ 和 $R_i$ 两个点。

源点 $S$ 向 $L_i$ 连流量为 $1$，费用为 $0$ 的边。

$R_i$ 向 汇点 $T$ 连流量为 $1$，费用为 $0$ 的边。

然后对于第 $i$ 个点来说，可以枚举另一个点 $j$，然后分成三种情况连边：

- $i=j$，自己和自己匹配，相当于**移到 $y$ 轴上**。此时从 $L_i$ 向 $R_i$ 连流量为 $1$，费用为 $x_i$ 的边。

- $i$ 和 $j$ 在 $y$ 轴同一侧，即 $x_i\times x_j\leq0$ 时。因为不优，直接跳过。

- $i$ 与 $j$ 不在 $y$ 轴同一侧，即 $x_i\times x_j>0$ 时。此时相当于将自己挪到 $j$ **沿 $y$ 轴对称的点上**。从 $L_i$ 向 $R_j$ 连流量为 $1$，**费用为 $\cfrac{\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}}{2}$ 的边。**

最后一种情况费用为 $\cfrac{\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}}{2}$ 而非 $\sqrt{(x_i+x_j)^2+(y_i-y_j)^2}$，是因为匹配是两边同时匹配，意味着 $i$ 匹配 $j$，同时 $j$ 也会匹配 $i$。匹配两次，所以费用是距离的 $\cfrac{1}{2}$。

最后跑**最小费用最大流**，结束。

# Code

一开始浮点数的费用流出了点问题。

~~后面找到了，判费用时用的是 `!cost[i]`~~

所以我把费用乘以 $10^8$，计算完后再除以 $10^8$ 即可。（只保留 7 位小数）

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;

template<typename Tp, size_t sizn, size_t sizm>
struct costflow
{
    #define pb __gnu_pbds
    typedef pb::priority_queue<pair<Tp, int>, 
                               greater<pair<Tp, int> >, 
                               pb::pairing_heap_tag> pairing_heap;

    int cnt=1, s=sizn-2, t=sizn-3;
    Tp delta=0, MXflow=0, MNcost=0;
    void link(int u, int v, Tp w, Tp f) 
    {
        to [++cnt]=v;       cap [cnt]=w;
        nxt[ cnt ]=head[u]; head[ u ]=cnt;
        cost[cnt ]=f;       from[cnt]=u;
        to [++cnt]=u;       cap [cnt]=0;
        nxt[ cnt ]=head[v]; head[ v ]=cnt;
        cost[cnt ]=-f;      from[cnt]=v;
    }

    private:

    bitset<sizn> vis;
    pairing_heap pq; 
    typename pairing_heap :: point_iterator it[sizn];
    Tp val[sizm<<1], dis[sizn], flow[sizn], cost[sizm<<1], cap[sizm<<1];
    int head[sizn], to[sizm<<1], nxt[sizm<<1], now[sizm<<1], from[sizm<<1];

    bool SPFA()
    {
        queue<int> q;
        memset(dis, 0x3f, sizeof dis);
        vis.reset();
        dis[t]=0; q.push(t);
        vis[t]=1;
        while (!q.empty())
        {
            int u=q.front(); q.pop();
            vis[u]=0;
            for(int i=head[u];i;i=nxt[i])
            {
                int v=to[i];
                Tp f=val[i^1], c=cap[i^1], len=cost[i^1];
                if(f<c&&dis[v]>dis[u]+len)
                {
                    dis[v]=dis[u]+len;
                    if(!vis[v]) vis[v]=1, q.push(v);
                }
            }
        }
        return dis[s]!=dis[0];
    }

    void reduce()
    {
        for(int i=2;i<=cnt;i++) cost[i]+=dis[to[i]]-dis[from[i]];
        delta+=dis[s];
    }

    bool Dijkstra() 
    {
        memset(dis, 0x3f, sizeof dis);
        memset(it, 0, sizeof it);
        dis[t] = 0; 
        it[t] = pq.push({dis[t], t});
        while(!pq.empty()) 
        {
            int u = pq.top().second; pq.pop();
            for(int j=head[u];j;j=nxt[j]) 
            {
                int v=to[j];
                Tp f=val[j^1], c=cap[j^1], len=cost[j^1];
                if(f<c&&dis[v]>dis[u]+len) 
                {
                    dis[v]=dis[u]+len;
                    if(it[v]==NULL) it[v]=pq.push({dis[v], v});
                    else pq.modify(it[v], {dis[v], v});
                }
            }
        }
        return dis[s] != dis[0];
    }
    
    // dfs 找增广路并处理
    Tp dfs(int idx, Tp sum)
    {
        if(idx==t) return sum;
        vis[idx]=1;
        Tp k, ret=sum;
        for(int i=head[idx];i&&sum;i=nxt[i])
        {
            int v=to[i];
            Tp f=val[i], c=cap[i], len=cost[i];
            if(!vis[v]&&f<c&&!len)
            {
                k=dfs(v, min(ret, c-f));
                val[i]+=k;
                val[i^1]-=k;    
                ret-=k;
            }
        }
        return sum-ret;
    }

    void augment()
    {
        Tp curflow=0;
        vis.reset();
        while((curflow=dfs(s, dis[0])))
        {
            MXflow+=curflow;
            MNcost+=curflow*delta;
            vis.reset();
        }
    }
    public:
    void PrimalDual()
    {
        if(!SPFA()) return;
        reduce(); augment();
        while(Dijkstra()) {reduce(); augment();}
    }
};

costflow<long long, 10005, 100005> cf;

struct dot
{
    int x, y;
    dot(int X=0, int Y=0) : x(X), y(Y) {}
    double operator-(const dot &b) { return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)); }
    dot rev() { return {-x, y}; }
};

dot vtc[105];

#define l(x) x<<1
#define r(x) x<<1|1

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>vtc[i].x>>vtc[i].y;
    for(int i=1;i<=n;i++)
    {
        cf.link(cf.s, l(i), 1, 0);
        cf.link(r(i), cf.t, 1, 0);
        cf.link(l(i), r(i), 1, abs(vtc[i].x)*1e8);
        for(int j=1;j<=n;j++)
        {
            if(vtc[j].x*vtc[i].x>=0) continue;
            cf.link(l(i), r(j), 1, (vtc[i]-(vtc[j].rev()))/2*1e8);
        }
    }
    cf.PrimalDual();
    printf("%.7f", (double)cf.MNcost/1e8);
}
```

---

