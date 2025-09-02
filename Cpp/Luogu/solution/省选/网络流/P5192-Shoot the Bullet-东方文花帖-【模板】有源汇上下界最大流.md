# Shoot the Bullet|东方文花帖|【模板】有源汇上下界最大流

## 题目背景

Translated by @chen_zhe

幻想乡是一个被博丽大结界和虚幻与现实的境界所包围起来的一个美妙的地方。这里人和其他生物，例如妖怪、妖精等核平共处。

射命丸文（Syameimaru Aya）是一只鸦天狗，拥有操纵风的能力，已经活了千岁以上，是《文文。新闻》的主编，拥有着一本叫做《文花帖》的手账，记录幻想乡各地的大新闻。她不仅是天狗中速度最快的鸦天狗，思考能力非常强，以别人的几倍的思考速度思考，也拥有幻想乡最高等级的力量。

（译者内心 O.S.：远古的东方众都那么硬核科普的吗）

![](https://i.loli.net/2019/01/12/5c3970b446151.png)

## 题目描述

![](https://i.loli.net/2019/01/12/5c3971b885128.jpg)

（附注：文花帖8-8 西行寺幽幽子 「死蝶浮月」）

在接下来的 $n$ 天中，射命丸文将要拍摄幻想乡的少女的照片。并且要为第 $x$ 个少女拍摄至少 $G_x$ 张照片刊登在《文文。新闻》上。在第 $k$ 天的时候文文有 $C_k$ 位少女可以拍，且在这一天中对某个少女拍的照片数量 **必须** 在某个闭区间 $[L, R]$ 中。如果过少，文文就搞不出大新文；如果过多，就会有少女很安格瑞。

除此之外，因为拍照设备的原因，对于第 $i$ 天，每天的拍照数量不能超过 $D_i$ 张。在满足这些限定的条件下，文文希望拍到的照片尽可能地多。

由于文文需要去取材，因此她把这个任务交给了你，让你帮她去解决。

## 样例 #1

### 输入

```
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9```

### 输出

```
36```

## 样例 #2

### 输入

```
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9```

### 输出

```
36

36```

# 题解

## 作者：离散小波变换° (赞：44)

## 题目大意

Aya超可爱的~ [题目传送门](https://www.luogu.com.cn/problem/P5192)

题意非常清晰：共有若干组数据 $( \leq 10)$。每组数据文文要从 $m$ 名 $\stackrel{BBA}{\text{少女}}$ 中收集 $n$ 天的照片，其中第$i$名少女共要收集**至少** $G_i$ 张。

文文第 $i$ 天可以拍摄 $D_i$ 张照片，取材范围为$C_i$位编号为 $T_{i,j}$ 的 $\stackrel{BBA}{\text{少女}}$，其中第 $j$ 位 $\stackrel{BBA}{\text{少女}}$ 需要拍摄 $[L_{i,j},R_{i,j}]$ 张照片。

现在求文文 $n$ 天最多收集多少张照片。如果无解，输出 $-1$。

$n\leq365,m\leq 1000,G_x\in[0,10^5],(1\leq C\leq 300,0\leq D\leq30000),(0\leq T_i<m,0\leq L_{i,j} \leq R_{i,j}\leq 100)$

## 题解

(**前置知识**：网络流最大流。)

虽然题目要求有源汇有上下界的最大流，但先让我们考虑**无源汇有上下界可行流**。

### 无源汇有上下界可行流

它的定义非常简单：一张 $n$ 个点 $m$ 条边网络流，其中每条边有一个流量限制 $[L_i,R_i]$ 表示这条边**流量的范围**。因为没有源汇，所以这张网络流需要满足**流入每个点的流量总量$ = $流出的流量总量**。

既然每个点都有上下界，那么我们先满足它的下界好了。即**对于每条边先填充 $\mathbf{L_i}$ 的流量**。但是这样显然流量不平衡，也就是说，有的点凭空流出了流量，但是又有流量流入点之后消失了。不过，我们可以惊喜的发现，问题已经转化为了：

每个点有一个权值$\mathbf{W_i}$表示当前在这个点上**积蓄/欠缺的流量**，同时每条边有一个流量限制 $\mathbf{[0,R_{i}-L_{i}]}$。现在要你求出一种方案，使得每个点积蓄/欠缺的流量全部用完，并且每条边满足流量限制。

如果我们再改一下题面：有一个超级源点 $S$ 向满足 $W_i>0$ 的点连了一条容量为 $|W_i|$ 的边。同时又有一个超级汇点$T$使得所有满足$W_i<0$的边都有一条容量为 $|W_i|$ 连向了 $T$。这条题目是不是非常像有源汇的网络流最大流？

**让我们重新梳理一下上述内容**:我们强制给每条边添上了一些流，或者说将这条边的流量范围变为了 $[0,R_i-L_i]$ 的普通版最大流。这样做会造成一些点上多出或欠缺一些流量。这时我们将欠的流量当作是 $S$ 给他们的流量，多出来的流量要还给 $T$，我们就能用最大流给他们疏通疏通经脉，满足约束条件。**此时我们能够使得每条边满足约束条件并且流量平衡**。

因为对于每条边 $(u,v,w)$，我们都让它的起始点 $u$ “透支”了 $w$ 的流量，而给终止点 $v$“借了”$w$ 流量，因此整张网络上的流量总和为 $0$。

但是先别高兴，我们要解决的是**有源汇有上下界可行流**。

### 有源汇有上下界可行流

**有源汇**这个条件给了我们什么东西呢？他给了我们源点 $s$ 和汇点 $t$，其中 $s$ 只输出流量，而 $t$ 只接受流量。对于这两个点，我们不要求它们流入的量 = 流出的量。但是如何把它转化为无源汇的上下界可行流呢？

其实，我们可以通过连接一条边 $t\to s$，容量为 $[0,+\infty]$，这样就能使得 $S$ 流出的流量由 $T$ 提供，$T$ 流入的量由 $S$ 提供，进而达到收支平衡。这样子跑一遍无源汇有上下界可行流，就可以使得到一组可行解了。其中，在 $t\to s$ 这条边上**流过的**流量就是一个可行的方案的答案了。换句话说，在 $t\to s$ 这条边流过的流量就是它的反向边（即残量网络的对应边）的流量。

### 有源汇有上下界最大流

但是我们的问题是要求最大流呀！不要慌，至少我们已经找到了一种合法的情况了。最大流算法需要扩大答案怎么办？在残量网络上跑增广路。而有源汇有上下界最大流也不例外（因为我们实际上已经把问题转化为了最大流问题，不过是多出了两个特殊点 $S$ 和 $T$）。如果我们从 $s$ 向 $t$ 增广会发生什么呢？

让我们重新回忆一下增广路的概念：从点 $s$ 到点 $t$ 增广，就是尽可能地在残量网络中寻找一条 $s\to t$ 的道路并转化为 $s\to t$ 的流量。

由于 $S$ 没有入边，而 $T$ 没有出边，因此增广路不会经过 $S,T$，也就不会导致约束条件失效（即始终满足流量平衡）。

### 建图

说了那么多，应该回到题目了。记 $D'_i$ 表示每一天对应的点，$G'_i$ 为每一位少女对应的点。首先我们需要建立一个源点$s$，由于每一天拍摄的照片数量不超过$D_i$，因此从 $s$ 向 $D_i$ 连上约束为 $[0,D_i]$  的边。对于第 $i$ 天，我们从该天向少女$T_{i,j}$连上边 $D'_i\to G'_{T_{i,j}}$，约束条件为 $[L_{i,j},R_{i,j}]$。最后，每名少女需要向汇点 $T$ 连边 $G'_i\to T$，约束条件为 $[G_i,+\infty]$。跑一遍有源汇有上下界最大流即可。

**总结**：这条题目的流程为读入边，处理边，跑普通版最大流。因此编写难度并不是很大。


### 扩展：关于最高标号预留推进（HLPP）

很显然，上面利用超级源汇点疏通边权达到进出平衡的算法可以用 $\text{HLPP}$ 实现。预留推进算法实质就是从每个点向其他点“推送”流量，这刚好符合我们的意图。

不过，由于使用 HLPP 算法有点大炮打蚊子了，所以这里直接使用的 $\text{Dinic}$ 算法。

## 参考代码

```
#include <bits/stdc++.h>
using namespace std;

int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}

using i64 = long long;
const int INF  =  1e9;
const i64 INFL = 1e18;

namespace MCMF{
    const int MAXN = 1e5 + 3;
    const int MAXM = 2e5 + 3;
    int H[MAXN], V[MAXM], N[MAXM], F[MAXM], o = 1, n;
    void add0(int u, int v, int f){
        V[++ o] = v, N[o] = H[u], H[u] = o, F[o] = f;
        V[++ o] = u, N[o] = H[v], H[v] = o, F[o] = 0;
        n = max(n, u);
        n = max(n, v);
    }
    i64 D[MAXN];
    bool bfs(int s, int t){
        queue <int> Q;
        for(int i = 1;i <= n;++ i)
            D[i] = 0;
        Q.push(s), D[s] = 1;
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(int i = H[u];i;i = N[i]){
                const int &v = V[i];
                const int &f = F[i];
                if(f != 0 && !D[v]){
                    D[v] = D[u] + 1;
                    Q.push(v);
                }
            }
        }
        return D[t] != 0;
    }
    int C[MAXN];
    i64 dfs(int s, int t, int u, i64 maxf){
        if(u == t)
            return maxf;
        i64 totf = 0;
        for(int &i = C[u];i;i = N[i]){
            const int &v = V[i];
            const int &f = F[i];
            if(f && D[v] == D[u] + 1){
                i64 f = dfs(s, t, v, min(1ll * F[i], maxf));
                F[i    ] -= f;
                F[i ^ 1] += f;
                totf += f;
                maxf -= f;
                if(maxf == 0){
                    return totf;
                }
            }
        }
        return totf;
    }
    i64 mcmf(int s, int t){
        i64 ans = 0;
        while(bfs(s, t)){
            memcpy(C, H, sizeof(H));
            ans += dfs(s, t, s, INFL);
        }
        return ans;
    }
    int G[MAXN];
    void add(int u, int v, int l, int r){
        G[v] += l;
        G[u] -= l;
        add0(u, v, r - l);
    }
	void clear(){
		for(int i = 1;i <= o;++ i){
			N[i] = F[i] = V[i] = 0;
		}
		for(int i = 1;i <= n;++ i){
			H[i] = G[i] = C[i] = 0;
		}
		o = 1, n = 0;
	}
    bool solve(){				// 无源汇
        int s = ++ n;
        int t = ++ n;
        i64 sum = 0;
        for(int i = 1;i <= n - 2;++ i){
            if(G[i] < 0)
                add0(i, t, -G[i]);
            else
                add0(s, i,  G[i]), sum += G[i];
        }
        auto res = mcmf(s, t);
        if(res != sum)
            return true;
        return false;
    }
    i64 solve(int s0, int t0){	// 有源汇
        add0(t0, s0, INF);
        int s = ++ n;
        int t = ++ n;
        i64 sum = 0;
        for(int i = 1;i <= n - 2;++ i){
            if(G[i] < 0)
                add0(i, t, -G[i]);
            else
                add0(s, i,  G[i]), sum += G[i];
        }
        auto res = mcmf(s, t);
        if(res != sum)
            return -1;
        return mcmf(s0, t0);
    }
}

const int MAXN = 1e3 + 3;
const int MAXM = 365 + 3;

int G[MAXN], A[MAXN], B[MAXM];

int main(){
	ios :: sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, o = 0;
	while(cin >> n >> m){

		int s = ++ o;
		int t = ++ o;

		for(int i = 1;i <= m;++ i){
			cin >> G[i];
			A[i] = ++ o;
			MCMF :: add(A[i], t, G[i], INF);
		}
		for(int i = 1;i <= n;++ i){
			B[i] = ++ o;

			int c, d;
			cin >> c >> d;

			MCMF :: add(s, B[i], 0, d);

			for(int j = 1;j <= c;++ j){
				int t, l, r;
				cin >> t >> l >> r;
				t ++;
				MCMF :: add(B[i], A[t], l, r);
			}
		}
		cout << MCMF :: solve(s, t) << "\n\n";

		MCMF :: clear();
	}
	
	return 0;
}
```


## 后记

明明说好的是模板题，然而并不是赤裸裸的板题（虽然一眼就能看出来是板子），所以调试起来挺麻烦的。但只要你有足够扎实的最大流功底，这条题目对于你就是小菜一碟。

另外，要注意少女的下标从$0$开始。虽然题目明确指出，但还是要小心成为星际玩家orz。

~~其实我做这条题目的动机完全是因为文文~~

$$\Large\color{white}\text{鸦天狗是卵生的！！！}$$

---

## 作者：Dyd本人 (赞：9)

蒟蒻的笔记,整理一下学了这么久的思路,希望能帮到你,若有不满——~~我劝你不要不识抬举,不然我就跪下求你[doge]~~。
# 一、知识储备（会的跳吧)
## 网络流的基本概念：
一个有向图 $G=(V,E)$ ，每条有向边 $(x,y)$ 都有一个给定的**容量**记为 $c(x,y)$ （若 $c(x,y)=0$ ，就说明不存在边 $(x,y)$ ），图中还有两个特殊节点**源点**、**汇点**分别记为 $S$ 、 $T$ 。 $S$ 会源源不断地流出无穷的水流，但每条边只能通过 $c(x,y)$ 的水流， $T$ 可以容纳无穷的水流，而其余个点无法容纳水流（即流入就必须全部流出）。  
任意一种满足条件的流水方法（即让水流从 $S$ 流到 $T$ ）叫做**流函数**，记为 $f(x,y)$ （表示从点 $x$ 流向 $y$ 的水流），明显，流函数具有如下性质：
- $0 \le f(x,y) \le c(x,y)$

- $f(x,y)=-f(y,x)$ （即从 $x$ 流向 $y$ 的流量也就是从 $y$ 流向 $x$ 的流量的相反数）
- $\forall x \ne S,T, \sum\limits_{u,x\in 	E}^{}f(u,x)= \sum\limits_{x,v\in 	E}^{}f(x,v)$ （即除 $S$ ， $T$ 外其余点流入流量等于流出流量，流量守恒）
## 残量网络
对于任意合法的流函数 $f$ ，都可构建一个新图 $G2$ （其实应该记做 $G'$ 但这里为了方便记为 $G2$ ），构建方法如下：
1. 将原图每条边容量变为 $c(x,y)-f(x,y)$ （即减掉已经用掉的流量）
1. 对于每条边 $(x,y)$ ，创建它的反向边 $(y,x)$ 并令 $c(y,x)=f(x,y)$ （即以流的流量让它可以反悔再流回来）

该图G2被我们叫做**残量网络**  
需要注意的是,反向边是我们新加的,原图中并不存在,若原图中本就有边 $(x,y)$ 和边 $(y,x)$ （即原图就有反向边），应在构建原图 $G$ 时就新建一点 $z$ ，使得 $(y,x)$ 变为 $(y,z)$ ， $(z,x)$ 。  
如图（画的丑求你憋着吧！）
![输入](https://cdn.luogu.com.cn/upload/image_hosting/2fzwiq9k.png)
 $\uparrow$ 这是输入的有向图。
![G](https://cdn.luogu.com.cn/upload/image_hosting/qp8a10w5.png)
 $\uparrow$ 这是去掉反向边的原图 $G$ 。
![f](https://cdn.luogu.com.cn/upload/image_hosting/eri7qydk.png)
 $\uparrow$ 这是一个合法的流函数，图中绿色代表 $f(x,y)$ 。 
![G2](https://cdn.luogu.com.cn/upload/image_hosting/pq7ur9ym.png)
 $\uparrow$ 这是该流函数的残量网络，蓝色为原图边容量（已改变），紫色为加入的反向边。
## 最大流
给定一个网络 $G$ ,对于所有合法的 $f$ ,从 $S$ 流出的流量最大的记为该网络的最大流，如上图中最大流为 $7$ （即是绿色的流函数）  
最大流的求法很多,但基本思路大体相同：
1. 先找到任意的一个流函数 $f$ ，并构建它的残量网络 $G2$ 

1. 在 $G2$ 中寻找 $G2$ 的合法流函数（我们一般记其为 $f'$ ，文中称其为 $f2$ ， $f2$ 也叫做**增广路**）
1. 将找到的增广路加上原图的流函数构成新的流函（即 $f_{now}=f+f2$ 并将 $G2$ 更新成为 $f_{now}$ 的残量网络）
1. 重复第 $2$ ， $3$ 步直到无增广路，此时的 $f$ 即是最大流

该思路的证明比较简单，想了解的可以自己百度，下面放两种算法（都已通过[P3376](https://www.luogu.com.cn/problem/P3376)）：
#### 一.Edmonds-Karp(EK算法)  
该算法就是以上思路的直接实现，（未优化版）几乎不会用，仅了解即可
```cpp
//Edmonds-Karp    O(nm^2)
//n+m = 10^3~10^4
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=1000+5,M=20000+5;
const int INF=0x3f3f3f3f;
int n,m,S,T;	
int q[N],incf[N],pre[N];		//q队列,incf残留网络流量,pre前驱边 
bool vis[N]; 
int h[N],e[M],f[M],ne[M],idx=0;		//e目标编号,f该边流量	
void add(int x,int y,int c){		//使用成对储存的技巧i^1及是i的反向边,不懂的请看第二大部分
	e[idx]=y,f[idx]=c;
	ne[idx]=h[x],h[x]=idx++;
	
	e[idx]=x,f[idx]=0;
	ne[idx]=h[y],h[y]=idx++;
	return ;
}
bool bfs(){			//寻找增广路 
	int hh=0,tt=0;
	memset(vis,false,sizeof vis);
	q[0]=S,vis[S]=true,incf[S]=INF;		//初始化,把S的出流量定为无穷大 
	while(hh<=tt){
		int t=q[hh++];
		for(int i=h[t];i!=-1;i=ne[i]){
			int ver=e[i];
			if(!vis[ver]&&f[i]){		//未到过且还有流量 
				vis[ver]=true;
				incf[ver]=min(incf[t],f[i]);	//最大流量为各边流量最小值 
				pre[ver]=i;					//记录前驱边 
				if(ver==T) return true;		
				q[++tt]=ver;
			}
		}
	}
	return false;
}
long long EK(){
	long long maxflow=0;		//这里仅是本人习惯开了long long
	while(bfs()){		//若存在增广路 
		maxflow+=incf[T];		 
		for(int i=T;i!=S;i=e[pre[i]^1]){	//pre[i]为前驱边->pre[i]^1为前驱边的反向边 
                                                        //->e[pre[i]^]为该反向边的目标点,即是前一个点
			//更改残留网络								 
			f[pre[i]]-=incf[T];
			f[pre[i]^1]+=incf[T];
		}
	}
	return maxflow;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&S,&T);
	memset(h,-1,sizeof h);
	for(int i=1;i<=m;++i){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c);
	}	
	printf("%ld",EK());
	return 0;
}
```
#### 二.Dinic算法
通过构建**分层图**来使增广时一次性增广多条增广路,是以上思路的优化,本人较为偏爱该算法
```cpp
//Dinic   O(n^2m)
//n+m = 10^4~10^5
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll; 
const ll N=1000+5,M=20000+5;		//有方向边M要开2倍 
const ll INF=0x3f3f3f3f;
ll n,m,S,T;	
ll q[N],d[N],cur[N];		//q队列,d高度,cur当前弧优化 
ll h[N],e[M],f[M],ne[M],idx=0;		//h,e,ne,idx邻接表,f流量 
void add(ll x,ll y,ll c){		 
	e[idx]=y,f[idx]=c;
	ne[idx]=h[x],h[x]=idx++;
	
	e[idx]=x,f[idx]=0;
	ne[idx]=h[y],h[y]=idx++;
	return ; 
}
bool bfs(){			//寻找有无增广路并建立分层图 
	ll hh=0,tt=0;
	memset(d,-1,sizeof d);
	q[0]=S,d[S]=0,cur[S]=h[S];	 //S初始高度为0,当前弧初始为第一条出边 
	while(hh<=tt){
		ll t=q[hh++];
		for(ll i=h[t];i!=-1;i=ne[i]){
			ll ver=e[i];
			if(d[ver]==-1 &&f[i]){		//一定要判断容量大于0 
				d[ver]=d[t]+1;		//层数 
				cur[ver]=h[ver];	//当前弧初始为第一条出边 		
				if(ver==T) return true;		
				q[++tt]=ver;
			}
		}
	}
	return false;
}
ll find(ll u,ll limit){	//找到增广路,find(u,limit)表示从点u开始,
									//从S到u的最大容量为limit 
	if(u==T) return limit;
	ll flow=0;		//flow表示从u向T流的最大流量 
	for(ll i=cur[u];i!=-1&&flow<limit;i=ne[i]){		//从未满的路径开始搜
														//flow<limit是很重要的优化! 
		cur[u]=i;		//当前弧优化,搜到i就意味着i前的边已用完,将当前弧更新 
		ll ver=e[i];
		if(d[ver]==d[u]+1&&f[i]){		//保证当前点在上一点的下一层,同样要注意f>0 
			ll t=find(ver,min(f[i],limit-flow));	
			if(!t) d[ver]=-1;		//若t到终点无增广路径,就删去点ver(把ver高度定为-1) 
			
			f[i]-=t;
			f[i^1]+=t;
			flow+=t; 
		} 
	}
	return flow;
}
ll Dinic(){
	ll maxflow=0,flow;	
	while(bfs())		//若存在增广路 
		while(flow=find(S,INF)) 		//找出当前图上所有增广路 
			maxflow+=flow;		
	return maxflow;
}
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&S,&T);
	memset(h,-1,sizeof h);
	for(int i=1;i<=m;++i){
		ll x,y,c;
		scanf("%lld%lld%lld",&x,&y,&c);
		add(x,y,c);
	}	
	printf("%lld",Dinic());
	return 0;
}
```
#### 三.其他还有ISAP（优化后的EK），HLPP（顶流推进）这里不再赘述，对于以上所有算法仍存问题的建议去先看看[P3376的题解](https://www.luogu.com.cn/problem/solution/P3376)
## 无源汇上下界可行流
在这类问题中不在仅存在容量上界 $c$ ，还存在下界（不妨记为 $l$ ），并且不存在 $S$ ， $T$ 两点。  
对于此类问题，我们可以用如下操作变为网络最大流：
1. 新建源点和汇点

1. 为满足性质1（忘了的上去看），将 $c$ 变为 $c-l$ ，即原来 $(x,y) \le f(x,y) \le c(x,y)$ 变为 $0 \le f(x,y) \le c(x,y)-l(x,y)$ 
1. 经过第2步后我们发现流量不守恒，故用一个数组 $ve$ （Virtual Edge）储存每个点的流量变化量，即对于边 $(x,y)$ ，经第2步变化后， $x$ 的出流量少了 $l(x,y)$ ， $y$ 的入流量少了 $l(x,y)$ ，故 $ve(x)-=l(x,y)$ ， $ve(y)+=l(x,y)$ 
1. 利用第3步统计的 $ve$ 数组，新建虚拟边使流量守恒，即若 $ve(x)>0$ ，新建边 $(S,x)$ 并令 $c(S,x)=ve(x)$ ；若 $ve(x)<0$ ，新建边 $(x,T)$ 并令 $c(x,T)=-ve(x)$ ；
1. 跑一遍 $S$ 到 $T$ 的最大流，若 $S$ （或 $T$ ）的所有边都可以流满，就说明存在可行流

经过如上操作，就将其变为一个基本的最大流问题，我们把这样建成的图称作虚拟图（仅是本人习惯），记为 $G3$ 。
## 有源汇上下界可行流
终于步入正题了  
此类问题相比于上一类区别在于原题中就存在源点和汇点（为以示区别记为 $s$ 、 $t$ ）。  
而解决方式与上类问题类似，区别仅在于我们要将点 $s$ 、 $t$ 这两个不满足流量守恒的点变为普通点，再用新建的 $S$ 、 $T$ 当为源点。  
而使其守恒的方式即是新建一条边 $(t,s)$ 并令
 $c(t,s)= \infty$ （正无穷）。
## 有源汇上下界最大流
好，现在问题来了，我们求解可行流时就是求的 $G3$ 的最大流，那么如果我们现在要求原图 $G$ 的可行流中的最大流我们该怎么办？  
仔细思考，发现我们还有一个图没用——原图的残量网络 $G2$ ！辣么，我们可否使用这三个图求出答案呢？  
当然是可以的，~~不然我讲个屁啊~~，而方法如下： 
1. 同上类问题跑出 $G3$ 的最大流记为 $flow3$ ，并将此时原图中的流函数记为 $f3$ 。
1. 构建原图 $G$ 关于 $f3$ 的残量网络 $G2$ ，求出 $G2$ 中的曾广路，我们发现这就等价于求出 $G$ 的最大流 $flow$ （注意此时用的是原图 $G$ ，故应删去边 $(t,s)$ ）
1. 最后答案即是 $flow+flow3$ 
# 二、本题分析
## 题目大意
有 $n$ 天， $m$ 位少女，至少为她们每人拍 $G(i)$ 张照片，每天总的最多拍 $D(i)$ 张，且每天只能为特定的少女拍照，张数为 $x \in [L,R]$ 。
## 建立模型
我们可以很轻松的~~由题目标题~~得出应使用网络流，并在稍微，~~指3天~~，思考后得出如下方法：
- 建立原图 $G$ ：
	1. 建立源点 $s=1$ ，汇点 $t=m+n+2$ ，并将少女建为点 $2 \sim  m+1$ ，天数建为点 $m+2 \sim n+m+1$ 
    1. 将少女至少要拍的照片数 $G(i)$ 定为下界，无穷大定为上界，让少女 $x$ 与源点 $s$ 相连，即建立边 $(s,x)$ （ $x \in [2,m+1]$ ）并使 $c(s,x)=\infty -G(i)$ 
    1. 将每天的最大拍照量定为上界， $0$ 为下界，让天数 $y$ 与汇点 $t$ 相连，即建边 $(y,t)$ （ $y \in [m+2,m+n+1]$ ）并使 $c(y,t)=D(i)-0$ 
    1. 将少女与天相连，定上下界为 $[L,R]$ ，即建边 $(x,y)$ （ $x \in [2,m+1],y \in [m+2,m+n+1]$ ）并使 $c(x,y)=R-L$ 
    1. 在构建原图的同时维护 $ve$ 数组
- 构建虚拟图 $G3$ ：
	1. 建立源点 $S=0$ ， $T=n+m+3$ 
    1. 用 $ve$ 数组建立连接 $S$ ， $T$ 与其他点的边
    1. 增加边 $(t,s)$ ，并使 $c(t,s)=\infty$ 
    1. 并同时维护 $outflow$ （记录从S流出的流量,用于判定是否满流）
- 求解 $G3$ 的最大流
	1. 直接用Dinic求解
    1. 判断 $Dinic()$ 是否等于 $outflow$ ，若不等，则说明原图无可行流（原题无解）
    1. 若相等，用 $res$ 记录此时 $s$ 到 $t$ 的流量，并进入下一步
- 求解 $G$ 的最大流（即是 $G2$ 中的曾广路）
	1. 删去边 $(t,s)$ 
    1. 使 $S=s$ ， $T=t$ （即将 $G3$ 变为 $G$ ）
    1. Dinic求解最大流，答案即为 $Dinic()+res$ 
# 三、代码
如下
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000000+5,M=1000000+5,INF=2147483647;
int n,m;	//如题意 
int nn,s,t,S,T;		//nn:原图中的点数,s:原图的源点,S虚拟图的源点,t,T同理 
int q[N],d[N],cur[N],ve[N];			//q:队列,d:高度,cur:当前弧优化,ve(Virtual Edge):虚拟边 
int h[N],e[N],f[N],ne[N],idx=0;			//h,e,ne,idx:邻接表,f:流量 
inline void add(int x,int y,int c){
	e[idx]=y,f[idx]=c,ne[idx]=h[x],h[x]=idx++;
	e[idx]=x,f[idx]=0,ne[idx]=h[y],h[y]=idx++;			//使用成对储存的技巧 
	return ;
}
inline int min(int a,int b){
	return a<b? a:b;
}
bool bfs(){				//寻找有无增广路并建立分层图 
	int hh=0,tt=0;
	memset(d,-1,sizeof d);
	q[hh]=S,d[S]=0,cur[S]=h[S];			//S初始高度为0,当前弧初始为第一条出边 
	while(hh<=tt){
		int p=q[hh++];
		for(int i=h[p];i!=-1;i=ne[i]){
			int ver=e[i];
			if(d[ver]==-1&&f[i]){			//一定要判断容量大于0 
				d[ver]=d[p]+1;				//层数  
				cur[ver]=h[ver];			//当前弧初始为第一条出边 
				if(ver==T) return true;
				q[++tt]=ver;
			}
		}
	}
	return false;
}
int find(int u,int limit){			//找到增广路,find(u,limit)表示从点u开始,
									//从S到u的最大容量为limit 
	if(u==T) return limit;
	int nowflow=0;					//nowflow表示从u向T流的最大流量 
	for(int i=cur[u];i!=-1&&nowflow<limit;i=ne[i]){		//从未满的路径开始搜
														//nowflow<limit是很重要的优化! 
		cur[u]=i;			//当前弧优化,搜到i就意味着i前的边已用完,将当前弧更新 
		int ver=e[i];
		if(d[ver]==d[u]+1&&f[i]){				//保证当前点在上一点的下一层,同样要注意f>0 
			int tflow=find(ver,min(f[i],limit-nowflow));
			if(!tflow) d[ver]=-1;				//若t到终点无增广路径,就删去点ver(把ver高度定为-1) 
			f[i]-=tflow,f[i^1]+=tflow,nowflow+=tflow;
		}
	}
	return nowflow;
}
int Dinic(){
	int maxflow=0,inflow;
	while(bfs())				//若存在增广路 
		while(inflow=find(S,INF))  maxflow+=inflow;			//找出当前图上所有增广路 
	return maxflow;
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		memset(h,-1,sizeof h);
		memset(ve,0,sizeof ve);
		//构建原图 
		s=1,t=n+m+2;		//原图中s=1为源点,t=n+m+2为汇点 
		nn=n+m+2;			//nn:原图的点数 
		for(int i=2;i<=m+1;++i){	//将少女编号为2~m+1,并和源点连通 
			int G;
			scanf("%d",&G);
			add(s,i,INF-G);	
			ve[i]+=G;
			ve[s]-=G;
		}
		for(int i=m+2;i<=m+n+1;++i){	//将天数编号为m+2~m+n+1,并和汇点连通 
			int C,D;
			scanf("%d%d",&C,&D);
			add(i,t,D);
			for(int j=1;j<=C;++j){		//将天与少女连通 
				int TT,L,R;		//TT即为题中的T
				scanf("%d%d%d",&TT,&L,&R);
				TT+=2;		//注意输入中的少女是从0编号的
				add(TT,i,R-L);	
				ve[TT]-=L;			//一定要减L,别减R！ 
				ve[i]+=L; 
			}
		}
		//构建虚拟图 
		S=0,T=n+m+3;		//S=0为虚拟图源点,T=n+m+3为虚拟图汇点 
		int outflow=0;		//记录从虚拟源点出流量,用于判断是否是满流 
		for(int i=1;i<=nn;++i){		//创建虚拟边保证虚拟图中流量守恒 
			if(ve[i]>0){
				add(S,i,ve[i]);
				outflow+=ve[i]; 
			} 
			else if(ve[i]<0) add(i,T,-ve[i]);
		}
		add(t,s,INF);		//增加一条从t到s的边,保证流量守恒 
		if(Dinic()<outflow) printf("-1\n\n");		//务必两个\n 
		else{
			int res=f[idx-1];		//最后加的边的反向边的流量
									//即是当前(虚拟图的)满流中s->t的流量
			f[idx-1]=f[idx-2]=0;	//删除该边	
			S=s,T=t;		//因为现在求的是s->t的最大流量,
							//所以重新初始化源点和汇点 
			printf("%d\n\n",res+Dinic()); 		//ans即为虚拟图中s->t的流量+
												//新增加的可行流量 
		}
	}
	return 0;
}
```
# 全剧终 The End

---

## 作者：Tenshi (赞：4)

更好的阅读体验：https://www.cnblogs.com/Tenshi/p/14716271.html

## 分析
这是一道**有源汇上下界最大流**的模板题（~~废话~~）。

既然是网络流的问题，故应该先将图建出来：

根据题目特征，
+ 我们将少女和每一天看作是图中的点。

+ 当然，因为每一天都有拍照次数的限制，我们可以加一个源点 $s$ ，向每一天连边，这个边的容量范围是 $[0,D_i]$ 。
+ 类似地，因为每个少女都有一个至少拍照张数的限定，所以加一个汇点 $t$ ，然后让每个少女向汇点连边，容量范围自然是 $[G_i,∞]$ 。
+ 至于少女和每一天，根据题意，她们之间连边的容量是 $[L, R]$ 。

至此，我们便将图建好了，从图的特征以及题意可以看出，这是一个求**有源汇上下界最大流**的问题。

怎么解决呢？

如果对约定的记号不熟悉可以看看我的博客：
[这里](https://www.cnblogs.com/Tenshi/p/14706721.html)

### 无源汇上下界可行流
首先，先介绍一下**无源汇上下界可行流**的求法（即：**可行循环流**的求法）：

p.s. 如果会的可以直接跳过看下面的部分

对于**可行循环流**中的边 $(u,v)$ 有如下容量限制： $\underline{c}(u,v)\le f(u,v) \le \overline{c}(u,v)$

简单的想法是将问题转化为求**有源汇最大流**。转化的方法自然是构造，构造的原则是保证问题的**等价。**

#### 构造方式：
加入虚拟源点 $S$ ，虚拟汇点 $T$ 。

对于每个点 $x$，记它的入边（假设入点为 $u$ ）对应的容量下界为 $\underline{c}(u,x)$ ，出边 （假设出点为 $v$ ）对应的容量下界为 $\underline{c}(x,v)$ 。

如果 $c=\sum \underline{c}(u,x)-\sum \underline{c}(x,v)>0$ ，那么连边 $(S,x)$ ，容量为 $c$ 。

如果 $c=\sum \underline{c}(u,x)-\sum \underline{c}(x,v)<0$ ，那么连边 $(x,T)$ ，容量为 $-c$ 。

根据上述规则得到新图 $G'$ 。

只需证明：$G'$ 的最大流与原图 $G$ 的可行流是一一对应的。

证明一个流对应另一个流的方法：从一个流进行等价变换，所得到的新流仍然合法：即满足**容量限制，流量守恒**。

容量限制较容易证明，故本文出现的证明都是关于证明**流量守恒**的。

#### 证明：

先证明 $G$ 的一个可行流对应着 $G'$ 的一个最大流（这里的最大流要求源点、汇点与其它点的连边**满流**，在接下来的讨论中可以发现需要这个约束）。

**约定**：点 $x$ 的入点构成的集合为 $U$ ，出点构成的集合为 $V$ ，这样做可以省去求和 $\sum$ ，表述方便，即 $\sum \underline{c}(u,x)=c(U,x)$ 
，$\sum \underline{c}(x,v)=c(x,V)$ 等等。

对 $G$ 的一个可行流，自然有： $f(U,x)=f(x,V)$

等价变形： $f'(U,x)+\underline{c}(U,x)=f'(x,V)+\underline{c}(x,V)$

进而有：$f'(U,x)+\underline{c}(U,x)-\underline{c}(x,V)=f'(x,V)$

不妨设 $\underline{c}(U,x)-\underline{c}(x,V)>0$ ， 注意到 $\underline{c}(U,x)-\underline{c}(x,V)$ 恰好是 $c(S,x)$，$\underline{c}(U,x)-\underline{c}(x,V)<0$ 的情况同理，故对于新图，流量也是守恒的。

而且从中可以发现，这里的最大流要求源点、汇点与其它点的连边**满流**。

从上面的证明可以发现 $G'$ 的一个最大流也对应着 $G$ 的一个可行流，只需要将公式倒着写一遍即可（因为是恒等变换）。

至此，证明结束。

在具体操作的时候，要注意跑完最大流之后，对应的边需要加上**补偿值**才是所要求的网络（参见证明中的公式以及下面的代码）。

求取**可行循环流**具体过程可以见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=205, M=12005+N<<1;
const int INF=0x3f3f3f3f;

int n, m, S, T;
struct node{
    int to, c, l, next;
}e[M];
int h[N], tot;

void add(int u, int v, int lc, int uc){
    e[tot].to=v, e[tot].c=uc-lc, e[tot].l=lc, e[tot].next=h[u], h[u]=tot++;
    e[tot].to=u, e[tot].c=0, e[tot].next=h[v], h[v]=tot++;
}

int imo[N]; // in minus out

int d[N], q[N], cur[N];

bool bfs(){
    memset(d, -1, sizeof d);
    int tt=-1, hh=0;
    q[++tt]=S, d[S]=0, cur[S]=h[S];
    while(tt>=hh){
        int hd=q[hh++];
        for(int i=h[hd]; ~i; i=e[i].next){
            int go=e[i].to;
            if(d[go]==-1 && e[i].c){
                cur[go]=h[go];
                d[go]=d[hd]+1;
                if(go==T) return true;
                q[++tt]=go;
            }
        }
    }
    return false;
}

int find(int u, int limit){
    if(u==T) return limit;
    int flow=0;
    for(int i=cur[u]; ~i && limit>flow; i=e[i].next){
        int go=e[i].to;
        cur[u]=i;
        if(e[i].c && d[go]==d[u]+1){
            int t=find(go, min(limit-flow, e[i].c));
            if(!t) d[go]=-1;
            flow+=t, e[i].c-=t, e[i^1].c+=t;
        }
    }
    return flow;
}

int dinic(){
    int res=0, flow;
    while(bfs()) while(flow=find(S, INF)) res+=flow;
    return res; 
}

int main(){
    memset(h, -1, sizeof h);
    cin>>n>>m;
    S=0, T=n+1;
    for(int i=1; i<=m; i++){
        int u, v, lc, uc; cin>>u>>v>>lc>>uc;
        add(u, v, lc, uc);
        imo[u]-=lc, imo[v]+=lc;
    }   

    int tot=0;
    for(int i=1; i<=n; i++)
        if(imo[i]>0) add(S, i, 0, imo[i]), tot+=imo[i];
        else if(imo[i]<0) add(i, T, 0, -imo[i]);

    if(dinic()!=tot) puts("NO");
    else{
        puts("YES");
        for(int i=0; i<2*m; i+=2) cout<<e[i].l+e[i^1].c<<endl;
    }
    return 0;
}
```


接下来求**有源汇上下界最大流**：

在上面，我们已经知道了怎样求**无源汇上下界可行流**，那先看看**有源汇上下界可行流**怎么求：方法其实很简单，将汇点 $t$ 向源点 $s$ 连一条容量 $∞$ 的边（我们称之为**虚边**）即可，有个直观的比喻：就像是在汇点 $t$ 连接一台水泵，将源点 $s$ 流往 汇点 $t$ 的水重新泵上去。这样做就将问题转换为了熟悉的**无源汇上下界可行流**问题。

简单来说：

$t$ 向源点 $s$ 连一条容量 $∞$ 的边，得到循环流。

从虚拟源点 $S$ 向 $T$ 跑一遍最大流。

记录 $t$ 向 $s$ 连的边的流量（即虚边流量 $res_1$ ），然后断开虚边，从 $s$ 向 $t$ 跑一遍最大流得到新增的流量 $res_2$ ，答案就是 $res_1+res_2$ 。


注意到，**无源汇上下界可行流**对应的流网络与虚拟源汇点 $S,T$ 相连的边都是满流，所以在跑完一遍最大流之后，与虚拟源汇点 $S,T$ 相连的边都不可能再被用到，我们可以直接将它们全部拆掉，然后，再将**虚边**（水泵）拆掉，发现只需要加回**补偿值**（但事实上，因为 $t$ 向 $s$ 连的边容量范围是 $[0,∞)$ ，不需要进行补偿），所得到的流就是一个合法的**有源汇上下界可行流**了。

也就是说新图的可行流和原图（没有经过变换的，最原始的）的可行流是一一对应的，那么新图的最大流也必然是对应着原图的最大流了。

因此，最后我们从 $s$ 向 $t$ 跑一遍最大流即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1550, M=365+1000+365*1000+N<<1, INF=0x3f3f3f3f; 

int n, m, s, t, S, T;
struct node{
	int to, c, next;
}e[M];
int h[N], tot;

// 连边函数，有这样的性质：正向边^1=反向边
void add(int u, int v, int c){
	e[tot].to=v, e[tot].c=c, e[tot].next=h[u], h[u]=tot++;
	e[tot].to=u, e[tot].c=0, e[tot].next=h[v], h[v]=tot++;
}

int imo[N]; // imo 的意思是： in minus out 入减去出

int q[N], d[N], cur[N];
bool bfs(){
	memset(d, -1, sizeof d);
	int tt=-1, hh=0;
	q[++tt]=S, d[S]=0, cur[S]=h[S];
	while(tt>=hh){
		int hd=q[hh++];
		for(int i=h[hd]; ~i; i=e[i].next){
			int go=e[i].to;
			if(d[go]==-1 && e[i].c){
				d[go]=d[hd]+1;
				cur[go]=h[go];
				if(go==T) return true;
				q[++tt]=go;
			}
		}
	}
	return false;
}

int find(int u, int limit){
	if(u==T) return limit;
	int flow=0;
	for(int i=cur[u]; ~i && limit>flow; i=e[i].next){
		int go=e[i].to;
		cur[u]=i; // 当前弧优化
		if(d[go]==d[u]+1 && e[i].c){
			int t=find(go, min(e[i].c, limit-flow));
			if(!t) d[go]=-1;
			e[i].c-=t, e[i^1].c+=t, flow+=t;
		}
	}
	return flow;
}

int dinic(){
	int res=0, flow;
	while(bfs()) while(flow=find(S, INF)) res+=flow;
	return res;
}

int main(){
	while(cin>>n>>m){
		memset(h, -1, sizeof h), tot=0;
		memset(imo, 0, sizeof imo);
		
		s=0, t=n+m+1, S=n+m+2, T=S+1;
		for(int i=1; i<=m; i++){
			int G; cin>>G;
			add(i, t, INF-G);
			imo[i]-=G, imo[t]+=G;
		}
		
		for(int i=m+1; i<=m+n; i++){
			int C, D; cin>>C>>D;
			add(s, i, D); // 范围是 [0,D] 因此不需要更新 imo[]
			while(C--){
				int id, lc, uc; cin>>id>>lc>>uc;
				id++;
				add(i, id, uc-lc);
				imo[i]-=lc, imo[id]+=lc;
			}
		}
		
		int cnt=0;
		for(int i=0; i<=n+m+1; i++)
			if(imo[i]>0) add(S, i, imo[i]), cnt+=imo[i];
			else if(imo[i]<0) add(i, T, -imo[i]);
		
		add(t, s, INF); // 添加“水泵”
		
		if(dinic()!=cnt) cout<<-1<<endl<<endl;
		else{
			int res=e[tot-1].c;
			e[tot-1].c=0, e[tot-2].c=0;
			S=s, T=t;
			res+=dinic();
			cout<<res<<endl<<endl;
		}
	}
	return 0;
}
```






---

