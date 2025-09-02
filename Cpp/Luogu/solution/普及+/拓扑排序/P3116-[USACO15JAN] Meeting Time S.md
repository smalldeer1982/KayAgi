# [USACO15JAN] Meeting Time S

## 题目描述

$\texttt{Bessie}$ 和她的妹妹 $\texttt{Elsie}$ 想从粮仓去她们最喜欢的田地，也就是能够使她们一起从粮仓离开，并且能同一时间到达的田地。

这个农场是由 $N$ 块 $(1\leq N\leq 100)$ 编号为 $1\cdots N$ 的田地构成的，第一块田地就是粮仓，并且第 $N$ 块田地是她们最喜欢的田地。

这个农场建在山的一边，所以，如果 $X < Y$ 的话则满足第 $X$ 块田地的高度要高于第 $Y$ 块田地的高度。在这之中，有 $M$ 条交错纵横的路径将不同的田地连接起来。

不过，显而易见的是，因为每条路都太陡了，所以这些小路只能沿着从高到低的方向走。例如，一条连接第 $5$ 块田地和 $8$ 块田地的小路只能沿着 $5\to 8$ 的方向走，而不能沿着其他方向，因为那样会成为上坡路。每两块田地最多只能有一条路径相连接，所以一定有 $M \leq \dfrac{N(N-1)}{2}$。

有可能的是，$\texttt{Bessie}$ 和 $\texttt{Elsie}$ 两个人走同一条小路会耗费不同的时间；比如，通过同一条小路，$\texttt{Bessie}$ 可能会耗费 $10$ 个单位的时间，而 $\texttt{Elsie}$ 会耗费 $20$ 个单位的时间。

此外，$\texttt{Bessie}$ 和 $\texttt{Elsie}$ 只会在通过连接两块田地的小路时耗费时间——因为她们太匆忙了，在穿过田地时不会耗费任何时间，也从来不在任何地方停下来等待。

现在，请你判断出，能够满足使 $\texttt{Bessie}$ 和 $\texttt{Elsie}$ 同时出发并且同时到达她们喜欢的田地的最短的时间。

## 说明/提示

$\texttt{Bessie}$ 在每一条路都比 $\texttt{Elsie}$ 快两倍。

如果 $\texttt{Bessie}$ 经过 $1\to 2\to 3$ 的路线，$\texttt{Elsie}$ 经过 $1\to 3$ 的路线，他们可以同时到达。

## 样例 #1

### 输入

```
3 3 
1 3 1 2 
1 2 1 2 
2 3 1 2 
```

### 输出

```
2 ```

# 题解

## 作者：amstar (赞：9)

**这道题可以用动规做，f[i][j]表示经过长度为j的路径能否到达i点，g[][]数组同理，只不过是题目中的第二组数据。**


**然后我们会用到拓扑，为什么用拓扑呢？因为要满足动规的无后效性，必须要用已经完成（没有点可以在更改当他的值，即没有边在通向他）的点，这一点很重要！！！**


**但是一件惊人的件事情：不用拓扑居然也可能过！！！你在逗我吗？提交代码时写错了个地方，代码第28行的ru[b]++忘记写了，就交了，然后呢，就A了，，，我能说啥。。。**


**没加28行，意味着说有的点会按顺序加入队列中，然后相当于枚举了所有的点一遍而已，也就没用到拓扑。数据也没这么弱的吧！！！**


**注意：46行不能有等号，数组最大是MAXE-1，不然会RE！**




```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN = 110;
const int MAXE = 10010;
struct Edge{
    int to,nxt,w1,w2;
}e[MAXE];
bool f[MAXN][MAXE],g[MAXN][MAXE],vis[MAXN];
int head[MAXN],ru[MAXN];
int n,m,tot;
queue<int>q;
int main()
{
    scanf("%d%d",&n,&m);
    for (int x,y,a,b,i=1; i<=m; ++i)
    {
        scanf("%d%d%d%d",&a,&b,&x,&y);
        e[++tot].nxt = head[a];    //建边 
        e[tot].to = b;
        e[tot].w1 = x;
        e[tot].w2 = y;
        head[a] = tot;
        ++ru[b];
    }
    for (int i=1; i<=n; ++i)    //拓扑 
        if (!ru[i]) q.push(i);
    f[1][0] = g[1][0] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i=head[u]; i; i=e[i].nxt)
        {
            int w1 = e[i].w1, w2 = e[i].w2, v = e[i].to;
            for (int j=0; j+w1<MAXE; ++j) f[v][j+w1] |= f[u][j];
            for (int j=0; j+w2<MAXE; ++j) g[v][j+w2] |= g[u][j];
            ru[v]--;
            if (!ru[v]) q.push(v);
        }
    }
    for (int i=0; i<MAXE; ++i)
        if (f[n][i]&&g[n][i]){ printf("%d",i); return 0; }
    printf("IMPOSSIBLE");
    return 0;
}
```

---

## 作者：Kancolle砍口垒 (赞：8)

# ~~退役选手的第一篇题解~~
### 看了好多题解都是拓扑，但蒟蒻我非常懒，就直接写了搜索优化。
~~懒蒟蒻没救了，不过数据非常小，优化下就能过了~~

##### 思路：找哥哥的最短路，然后找妹妹的，最短不行就第二短，说白了就是跑两遍k短路。

|
K短路A*优化：
A*优化建立在bfs之上，仅仅是队列换成了优先队列。

优先队列的判断条件为tot，即总值。tot=past（当前状态已经走过的长度）+exp（期望）。

期望是解决问题的最好情况，在不同题中有不同意义。

本题中k短路的exp为当前点到终点的最短距离，需要预处理，即简历反图用最短路算法跑一边终点到任意一点的最短路即可。


代码中结构体省略了exp
tot=past+exp ==>>
tot=past+tod[x]

优先队列按tot从小到大排序即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
int n,m;//n 点 m 边；
struct edge
{
	int f;
	int t;
	int c;
};
vector<edge> bro[100+10];
vector<edge> sis[100+10];
vector<edge> antibro[100+10];
vector<edge> antisis[100+10];
int ansb[100000000];
int anss[100000000];
int bmin=0;
int smin=0;
/////////////////////////////////////////////////
int inqb[100+10];
int todb[100+10];
void antispfab(int x)//spfa求哥哥 终点到任意一点的最短路
{
	memset(todb,0x3f,sizeof(todb));
	queue<int> q;
	q.push(x);
	todb[x]=0;
	inqb[x]=true;
	while(!q.empty())
		{
			int now=q.front();
			q.pop();
			inqb[now]=false;
			int lb=antibro[now].size();
			for(int i=0; i<lb; i++)
				{
					edge next=antibro[now][i];
					if(todb[next.t]>todb[next.f]+next.c)
						{
							todb[next.t]=todb[next.f]+next.c;
							if(inqb[next.t]!=true)
								{
									q.push(next.t);
									inqb[next.t]=true;
								}
						}
				}
		}
	return ;
}
////////////////////////////////////////////////////
int inqs[100+10];
int tods[100+10];
void antispfas(int x)//spfa求妹妹 终点到任意一点的最短路
{
	memset(tods,0x3f,sizeof(tods));
	queue<int> q;
	q.push(x);
	tods[x]=0;
	inqs[x]=true;
	while(!q.empty())
		{
			int now=q.front();
			q.pop();
			inqs[now]=false;
			int ls=antisis[now].size();
			for(int i=0; i<ls; i++)
				{
					edge next=antisis[now][i];
					if(tods[next.t]>tods[next.f]+next.c)
						{
							tods[next.t]=tods[next.f]+next.c;
							if(inqs[next.t]!=true)
								{
									q.push(next.t);
									inqs[next.t]=true;
								}
						}
				}
		}
	return ;
}
////////////////////////////////////////////////////

struct zt//节点状态
{
	int dot;//当前点
	int past;//走过路程
	int tot;//tot=past+exp即tot=past+tod[i]
};
struct cmp
{
	bool operator ()(const zt &a,const zt &b)
	{
		if(a.tot>b.tot)	return true;
		else return false;
	}
};
void astars();
bool flag=false;//flag表示是否找到答案
void astarb()
{

	priority_queue<zt,vector<zt>,cmp> q;
	zt first;
	first.dot=1;
	first.past=0;
	first.tot=first.past+todb[first.dot];
	q.push(first);
	while(!q.empty())
		{
			if(flag==true)//找到答案停止
				{
					return;
				}
			zt now=q.top();
			q.pop();
			if(now.dot==n)//走到终点
				{
					if(ansb[now.past]==true)
						{

							continue;
						}
					else
						{

							bmin=max(bmin,now.past);
							ansb[now.past]=true;
							if(anss[now.past]==true)
								{
									flag=true;
									cout<<now.past<<endl;
									return;
								}
							if(now.past>smin)
								{

									astars();
								}
							else
								{
									continue;
								}

						}
				}
			int lb=bro[now.dot].size();
			for(int i=0; i<lb; i++)
				{
					edge temp=bro[now.dot][i];
					zt next;
					next.dot=temp.t;
					next.past=now.past+temp.c;
					next.tot=next.past+todb[next.dot];
					q.push(next);
				}
		}
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void astars()
{
	if(flag==true)//找到答案停止
		{
			return;
		}

	priority_queue<zt,vector<zt>,cmp> q;
	zt first;
	first.dot=1;
	first.past=0;
	first.tot=first.past+tods[first.dot];
	q.push(first);
	while(!q.empty())
		{ 
			if(flag==true)//找到答案停止
				{
					return;
				}
			zt now=q.top();
			q.pop();
			if(now.dot==n)
				{
					if(anss[now.past]==true)
						{

							continue;
						}
					else
						{

							smin=max(smin,now.past);
							anss[now.past]=true;
							if(ansb[now.past]==true)
								{

									cout<<now.past<<endl;
									flag=true;
									return;
								}
							else
								{

									if(now.past>bmin)
										{

											astarb();
										}
									else
										{

											continue;
										}
								}
						}

				}


			int ls=sis[now.dot].size();
			for(int i=0; i<ls; i++)
				{
					edge temp=sis[now.dot][i];
					zt next;
					next.dot=temp.t;
					next.past=now.past+temp.c;
					next.tot=next.past+tods[next.dot];
					q.push(next);
				}
		}
	return;
}
int main()
{
	cin>>n>>m;
	for(int x=1; x<=m; x++)
		{
			int a1,a2,a3,a4;
			cin>>a1>>a2>>a3>>a4;
			edge tempb,temps;
			tempb.f=a1;
			tempb.t=a2;
			tempb.c=a3;
			temps.f=a1;
			temps.t=a2;
			temps.c=a4;
			bro[tempb.f].push_back(tempb);
			swap(tempb.f,tempb.t);
			antibro[tempb.f].push_back(tempb);


			sis[temps.f].push_back(temps);
			swap(temps.f,temps.t);
			antisis[temps.f].push_back(temps);
		}
	antispfab(n);
	antispfas(n);
	astarb();
	astars();
	if(flag==false)
		cout<<"IMPOSSIBLE"<<endl;
	return 0;
}
```



---

## 作者：若如初见 (赞：6)

~~即将退役的选手来写篇题解~~  

## 此题做法：拓扑排序 + DP  

首先，根据题意我们可以得出，这是一张有向无环图（DAG），那我们也不难想到拓扑排序，同时做一遍 DP 。

由于数据范围比较小，可以设计出如下的 DP 模型-：  

状态： $f[i][j]$ 表示经过 $j$ 时间能否到达 $i$ 号结点；  

转移方程： $f[v][j]=f[u][j-edge[i].w]\ (j-edge[i].w\geq 0,(u,v)\in G)$  

边界： $f[1][0]=1$  

目标状态： $\min\{ j \},\ \text{s.t.}\  f[n][j]=1$  

注意到有两个人要走，所以我们开两个 DP 数组进行转移。最后求出最小的 $j$ ，使得 $f1[n][j]=f2[n][j]=1$即可。  

具体实现请看代码：  

```cpp
#include <cstdio>
#include <queue> 
#define rint register int //卡常加速
#define MAXN 105
using namespace std;
queue <int> q; //用队列进行拓扑排序
int n,m,cnt,head[MAXN],ind[MAXN]; 
//n:结点数 m：边数 head,cnt：链式前向星存图用 ind: 存储结点入度
bool f1[MAXN][MAXN*MAXN],f2[MAXN][MAXN*MAXN];  
  //DP数组
struct Edge{
	int next,to,w1,w2;
}edge[MAXN*MAXN];
  //链式前向星，w1、w2分别存储两个人走这条边所需的时间
inline void add(int u,int v,int w1,int w2){
	edge[++cnt].next=head[u];
	edge[cnt].to=v;
	edge[cnt].w1=w1;
	edge[cnt].w2=w2;
	head[u]=cnt;
} //加边
int main(){
	scanf("%d %d",&n,&m);
	for(rint i=1;i<=m;++i){
		int u,v,w1,w2;
		scanf("%d %d %d %d",&u,&v,&w1,&w2);
		add(u,v,w1,w2); //加边
		++ind[v]; //统计入度
	}
	for(rint i=1;i<=n;++i)
		if(!ind[i]) q.push(i); //入度为0的点入队
	f1[1][0]=f2[1][0]=1; //DP边界
	while(!q.empty()){ //拓扑排序板子
		int u=q.front();
		q.pop();
		for(rint i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			for(rint j=0;j<=10000;++j){
				if(j-edge[i].w1>=0) f1[v][j]|=f1[u][j-edge[i].w1]; //转移，注意判断j-edge[i].w>=0 
				if(j-edge[i].w2>=0) f2[v][j]|=f2[u][j-edge[i].w2];
			}
			if(--ind[v]==0) q.push(v);
		}
	}
	for(rint i=0;i<=10000;++i)
		if(f1[n][i]&&f2[n][i]){
			printf("%d",i); //输出
			return 0;
		}
	printf("IMPOSSIBLE"); //判断无解情况
	return 0;
}
```


---

## 作者：渔歌 (赞：5)

# 一个基于优先队列的做法
课上老师讲了一个 $ O( {n}^{4} ) $ 的算法，表示没有听懂，就自己~~瞎搞~~，最后整出了如这篇题解的思路。

题目给的约束条件是:

1. 两人同时到达。
2. 时间最短。

先着手考虑第二个约束条件，时间最短，那就尽可能地贪。不难联想到求两人 **$1\to n$ 的最短路**。
如果这道题只是求两人分别从 $1\to n$ 的最短路（单点 $ \to$ 单点），那么就可以用两个**优先队列**。

这里以其中一个人为例：

我们把她起始点连的所有点带上到达所需时间（边权）一起    rua 进优先队列里去，每次再拿出来优先队列里权值最小的点，再将所有的子节点带上边权再 rua 进去，直到拿出的点为 $n$ 号节点（目标节点）为止。而第一次取出 $n$ 号节点必定就是从 $1\to n$ 的最短路。

先贴代码：
```cpp
struct u2004{
	int p,t;//p为节点编号,t为从 1->n 路径权
	bool operator < (const u2004 x)const{
		if(x.t==t)return p<x.p;
		return t>x.t;
	}
};
inline void pre(){
	for(int i=head[1];i;i=e[i].nx)
		q.push((u2004){e[i].b,e[i].va});
}
inline int get(){
	while(!q.empty()){
		u2004 x=q.top();
		q.pop();
		if(x.p==n)return x.t;
		int t=x.t;
		for(int i=head[x.p];i;i=e[i].nx){
			int y=e[i].b;
			q.push((u2004){e[i].b,t+e[i].va1});
		}
	}
	return 0;
}
```
简单解释一下，设从优先队列里取出的节点是 $u$ ，则第一次取 $u$时 必定优先队列里 $1\to u$ 最短的路径。

用反证法证明一下：若第一次取出的不为 $1\to u$ 的最短路，则必有节点 $v$，使得  ${S}_{1\to v}+{S}_{v\to u}< {S}_{1\to u}$

因为路径消耗时间为正数，则必有 ${S}_{1\to v}<{S}_{1\to u}$

则理应优先取出来  $1\to v$ 的路径，并进行更新。而现在取出的路径为 $1\to u$ ,矛盾，故得证。


但是，由于约束条件一，而每条路两人所用时间不一定相同，致使两个人的最短路不一定相同，即不一定是最终解。

$But$ 我们可以利用最短路的思路。在求 $1\to n$ 最短路过程中，我们每次进行更新的结果不一定是最优解，但我们还是会老老实实rua进优先队列，那么优先队列里必定存有 $1\to n$ 的第 2 短路，第 3 短路·····第 k 短路，甚至最长路。当 $1\to u$ 的最短路被取出时，剩下的便是第二短路等**次优解**。而通过之前的证明同理可得（懒得证明），**第k次取出的 $1\to u$ 便是 $1\to u$ 的第 k 短路**。(此处为不严格第 k 短路，可能与 k-1 短路相等。)

但我们没有必要老老实实把两个人的所有路径都存起来。因为我们找到的第 k 短路是不下降的， 则我们可以动态更新，每次将耗时较少的(路径长度较短的）进行更新，再进行比较，直至相同，或 $1\to n$ 路径均被取出。

$Over$

时间 41ms,吸一口氧气后时间 37ms。

代码：
```cpp
#include<cstdio>
#include<queue>
#define N 105
using namespace std;
int n,m,last;
int head[N];
struct u2003{
	int nx,b,va1,va2;//va1,va2分别是两个人通过路径的用时
}e[N*N/2];
inline void build(int a,int b,int va1,int va2){
	e[++last].b=b;
	e[last].va1=va1;
	e[last].va2=va2;
	e[last].nx=head[a];
	head[a]=last;
}
inline void scan(){
	scanf("%d%d",&n,&m);
	int a,b,c,d;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		build(a,b,c,d);
	}
}
struct u2004{
	int p,t;
	bool operator < (const u2004 x)const{
		if(x.t==t)return p<x.p;
		return t>x.t;//可能没啥用
	}
};
priority_queue<u2004> q1,q2;
inline void pre(){
	for(int i=head[1];i;i=e[i].nx){
		q1.push((u2004){e[i].b,e[i].va1});
		q2.push((u2004){e[i].b,e[i].va2});
	}
}
inline int get1(){
	while(!q1.empty()){
		u2004 x=q1.top();
		q1.pop();
		if(x.p==n)return x.t;
		int t=x.t;
		for(int i=head[x.p];i;i=e[i].nx){
			int y=e[i].b;
			q1.push((u2004){e[i].b,t+e[i].va1});
		}
	}
	return 0;
}
inline int get2(){
	while(!q2.empty()){
		u2004 x=q2.top();	
		q2.pop();
		if(x.p==n)return x.t;
		int t=x.t;
		for(int i=head[x.p];i;i=e[i].nx){
			int y=e[i].b;
			q2.push((u2004){e[i].b,t+e[i].va2});
		}
	}
	return 0;
}
inline int suan(){
	int x1=get1();
	int x2=get2();
	while(x1!=x2){//不相等时对较小的1->n路径更新次短路
		if(x1<x2)x1=get1();
		else x2=get2();
		if(!x1||!x2)return 0;//为0即1->n所有路径与对方无重合
	}
	return x1;//x2也行
}
int main(){
	scan();
	pre();
	int x=suan();
	if(x==0)puts("IMPOSSIBLE");
	else printf("%d\n",x);
	return 0;
}
```

憨憨第一次写题解，感谢管理员大大的指点~~
~~耽误了管理好多时间~~

---

## 作者：紫薯布丁 (赞：4)

## 提供一种新的思路：K短路



- 题目大意：给定一张有向图，以及起点和终点，**两头牛移动时相同边经过的时间可能互不相同**，要求**两头牛到达终点的时间相同**，求两头牛到达终点时的最短时间。



- 考虑到，一头牛到达终点的最短路并不一定是另一只牛到达终点的最短路。

  

- 当然同样的，一头牛到达终点的次短路可能也会与另一只牛的次短路和最短路不同。所以不能用简单的最短路次短路问题解决。



- **最短路行不通，次短路行不通，我们为什么不用k短路呢？**
- 很显然的贪心策略：对于每一种牛，我们求出他的k短路，将这些路径从小到大跟另一头牛的k短路依次比较，第一次得到的答案就是最优答案。
- ~~这道题目定义k=n就可以枚举到~~


[k短路模板](https://www.luogu.org/problem/P2483)





- 那么这道题目就变成了洛谷上的又一道k短路可做的题目



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
const int ss =600800;
inline int read(){
	int x=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) c=='-'?f=-1:1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}

struct oi{
	int f,g,id;
	bool operator <(const oi a) const{
	return g>a.g;
	}
};

struct oo{
	int next,to,v;
}e[ss*4],E[ss*4],a[ss*4],A[ss*4];
int col=0,hp[ss],Col=0,Hp[ss];
int Head[ss],head[ss],Cnt=0,cnt=0;
inline void add(int x,int y,int z){
	e[++cnt]=oo{head[x],y,z};head[x]=cnt;
	E[++Cnt]=oo{Head[y],x,z};Head[y]=Cnt;
}
inline void Add(int x,int y,int z){
	a[++col]=oo{hp[x],y,z};hp[x]=col;
	A[++Col]=oo{Hp[y],x,z};Hp[y]=Col;
}

int dis[ss],Dis[ss];
bool b[ss];
inline void dij(int s){
	memset(dis,0x3f,sizeof(dis));
	memset(b,0,sizeof(b));
	dis[s]=0;b[s]=1;
	queue<int>q;
	q.push(s);
	while(q.size()){
		int u=q.front();q.pop();
		b[u]=0;
		for(int i=Head[u];i;i=E[i].next){
			int y=E[i].to,z=E[i].v;
			if(dis[y]>dis[u]+z){
				dis[y]=dis[u]+z;
				if(!b[y]){
					b[y]=1;
					q.push(y);
				}
			}
		}
	}
}
inline void spfa(int s){
	memset(Dis,0x3f,sizeof(Dis));
	memset(b,0,sizeof(b));
	Dis[s]=0;b[s]=0;
	priority_queue<pair<int,int> >q;
	q.push(make_pair(0,s));
	while(q.size()){
		int u=q.top().second;
		q.pop();
		if(b[u]) continue;b[u]=1;
		for(int i=Hp[u];i;i=A[i].next){
			int y(A[i].to),z(A[i].v);
			if(Dis[y]>Dis[u]+z){
				Dis[y]=Dis[u]+z;
				q.push(make_pair(-Dis[y],y));
			}
		}
	}
}


int Do[104][104*104/2];
int to[109];
int n,m;

inline void Astar(int s){
	priority_queue<oi>q;
	q.push(oi{0,dis[s],s});
	while(q.size()){
		int u=q.top().id,f=q.top().f,g=q.top().g;
		q.pop();
		to[u]++;
		if(to[u]>n) continue;
		Do[u][to[u]]=f;
		for(int i=head[u];i;i=e[i].next){
			int y=e[i].to,z=e[i].v;
			q.push(oi{f+z,f+z+dis[y],y});
		}
	}
}

int di[104][104*104/2];

inline void AAstar(int s){
    memset(to,0,sizeof(to));	
    priority_queue<oi>q;
    q.push(oi{0,Dis[s],s});
    while(q.size()){
    	int u=q.top().id,f=q.top().f,g=q.top().g;
    	q.pop();
    	to[u]++;
    	if(to[u]>n) continue;
    	di[u][to[u]]=f;
    	for(int i=hp[u];i;i=a[i].next){
    		int y(a[i].to),z(a[i].v);
    		q.push(oi{f+z,f+z+Dis[y],y});
		}
	}
}



int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x(read()),y(read()),z1(read()),z2(read());
		add(x,y,z1);
		Add(x,y,z2);
	}dij(n);spfa(n);
	if(dis[1]>1e9) return cout<<"IMPOSSIBLE",0;
	Astar(1);AAstar(1);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++){
	  	if(Do[n][i]==di[n][j]){
	  		return cout<<Do[n][i],0;
		  }
		if(di[n][i]==Do[n][j]){
			return cout<<di[n][i],0;
		}
	  }
}


```



---

## 作者：_蒟蒻__ (赞：2)

好像有很多大佬用拓扑……

突然感觉自己好菜, 都没想到这一点……

其实可以用bfs啦!

dis[i][j]表示到第i个点是否有长为j的路径, 两个人分别bfs一下, 最后枚举一下长度

好像有位大佬瞎蒙了一下j的枚举上限为7000, (~~我也蒙过其他数字但T了~~)

其实这样会产生很多重复转移, bfs进队的时候记录一下当前更新的j是多少就好啦

生命苦短, 直接上代码


```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#include <bitset>
#define mk make_pair
using namespace std;
const int N=10010;
int n, m;
struct edge{
	int to, v, nxt;
}e1[N<<1], e2[N<<1]; int head[N], ecnt;																
																				
inline void add(int fr, int to, int v1, int v2)																	
{																					
	e1[++ecnt]= (edge) { to, v1, head[fr] };																
	e2[ecnt]  = (edge) { to, v2, head[fr] };																		
	head[fr]  = ecnt;																	
}																			
																				
bitset <N> dis[N], mp;													
																			
inline void bfs(edge *e)											
{
	for(int i=1; i<=n; i++) dis[i].reset();
	queue < pair <int, int> > q;
	q.push(mk(1, 0));
	dis[1][0]=1; // 其实写不写一个样 
	while(!q.empty())
	{
		int x=q.front().first, y=q.front().second;  
		q.pop();
		for(int i=head[x]; i; i=e[i].nxt)
		if(!dis[e[i].to][y+e[i].v])
		{
			dis[e[i].to][y+e[i].v]=1;
			q.push(mk(e[i].to, y+e[i].v));
		}
	}
	for(int i=0; i<=10000; i++) // 试了试用bitset._Find_first()和.Find_next()好像更慢 
	if(dis[n][i])
	{
		if(mp[i]) cout<<i, exit(0); // 如果出现过, 当前肯定是在第二次bfs中, 并且i在第一次bfs中出现过 
		else mp[i]=1;
	}
}
																										
int main()
{
	ios::sync_with_stdio(false);														
	cin>>n>>m;					
	for(int i=1, x, y, v1, v2; i<=m; i++)										
	{
		cin>>x>>y>>v1>>v2;
		if(x>y) swap(x, y);
		add(x, y, v1, v2);																
	}
	bfs(e1);
	bfs(e2);
	return cout<<"IMPOSSIBLE", 0;
}
```


---

## 作者：shadowice1984 (赞：2)

本蒟蒻觉得好像不用拓扑吧。。。

才疏学浅。。。

下面分析下思路；

设d（i，j）为是否存在长为j的路径通向i点；

那么显然

如果d（i，j）是存在的

并且存在由i通向k的道路，那么d（k，cost[i]【k】+j）也是存在的（cost[i][k]是由i到k的路径长）；

所以跑个循环，把所有点遍历，就可以得到通向i的所有长度，（采用权值1）；

再报一遍，就可以得到采用权值2的所有长度；

两个集合取交，再取最小值就好了。

上代码~

            
            
    
```cpp
#include<stdio.h>
using namespace std;
int n;int m;int map1[100][100];int map2[100][100];//邻接矩阵存图
bool d1[100][7000];bool d2[100][7000];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            map1[i][j]=-1;map2[i][j]=-1;//初始化
        }
    }
    for(int i=0;i<m;i++)
    {
        int u;int v;int a;int b;
        scanf("%d%d%d%d",&u,&v,&a,&b);
        map1[u-1][v-1]=a;map2[u-1][v-1]=b;
    }
    d1[0][0]=true;d2[0][0]=true;//设置边界条件
    for(int i=0;i<n;i++)//遍历所有点
    {
        for(int j=0;j<7000;j++)//合理瞎蒙，到终点不太可能突破7000
        {
            if(d1[i][j]==true)//这样的路径是否存在
            {
                for(int k=0;k<n;k++)
                {
                    if(map1[i][k]!=-1)//通向下一个点道路是否存在
                    {  
                        d1[k][j+map1[i][k]]=true;//更新
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++)//再跑一遍权值2
    {
        for(int j=0;j<7000;j++)
        {
            if(d2[i][j]==true)
            {
                for(int k=0;k<n;k++)
                {
                    if(map2[i][k]!=-1)
                    {
                        d2[k][j+map2[i][k]]=true;
                    }
                }
            }
        }
    }
    int res=-1;
    for(int i=0;i<7000;i++)//从0开始，这样第一个交集元素就是最小元素
    {
        if(d1[n-1][i]&&d2[n-1][i])
        {
            res=i;break;
        }
    }
    if(res==-1)
    {
        printf("IMPOSSIBLE");
    }
    else 
    {
        printf("%d",res);
    }
    return 0;//拜拜程序~
}

```

---

## 作者：xayata_ (赞：2)

666
爱过不过，呵！呵！呵！


/\*
拓扑序dp；

这道题目规定了起点是1；

直接把1放进队列里然后拓扑，错误

原因很简单；

除了1以外，还有很多入度为0的点；

（当然1的入度可能不为0，没关系）

如果直接从1遍历；

就会导致有些点的入度永远不为0；

所以我们要先把的入度==0的非1点先跑一遍拓扑；

跑完后，整个图只有1是入度为0的了；

这样再从1开始跑；

\*/


    


        
```cpp
#include<cstdio>//cfb
#include<iostream>
#include<cstring>
using namespace std;
struct cs{int to,next,A,B;}a[100001]; 
int head[101],s[101],q[105]; 
bool aa[101][20001],bb[101][20001];
int n,m,x,y,z,A,B,ll,l,r;
void init(int x,int y,int A,int B)
{
    ll++;
    a[ll].to=y;
    a[ll].A=A;
    a[ll].B=B;
    a[ll].next=head[x];
    head[x]=ll;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x,&y,&A,&B);
        init(x,y,A,B);
        s[y]++;
    }
    for(int i=2;i<=n;i++)if(!s[i])q[++r]=i;
    while(r>l)
    {
        x=q[++l];
        for(int k=head[x];k;k=a[k].next)
        {
            y=a[k].to;
            if(!--s[y])q[++r]=y;
        }
    }
    q[1]=1;
    aa[1][0]=bb[1][0]=1;
    r=1; l=0;
    while(r>l)
    {
        x=q[++l];
        for(int k=head[x];k;k=a[k].next)
        {
            y=a[k].to;
            s[y]--;
            if(!s[y])q[++r]=y;
            for(int i=0;i<=10000;i++)
            {
                if(aa[x][i])aa[y][i+a[k].A]=1;
                if(bb[x][i])bb[y][i+a[k].B]=1;
            }
        }
    }
    for(int i=0;i<=10000;i++)
        if(aa[n][i]&&bb[n][i])
        {
            printf("%d",i);
            return 0;
        }
    printf("IMPOSSIBLE");
    return 0;
}
```

---

## 作者：Expecto (赞：2)

这题dp吧。。。

设a[i][j] b[i][j] 表示一头牛是否能在j时刻到达i点，转移易得。

复杂度刚刚好啊

```cpp
0. #include<bits/stdc++.h>
0. using namespace std;
0. struct data{
0. int u,va,vb;
0. };
0. vector<data> g[111];
0. int a[105][10050]={0},b[105][10050]={0};
0. int main(){
0. int n,m;
0. cin>>n>>m;
0. while (m--){
0. int x,y,va,vb;
0. cin>>x>>y>>va>>vb;
0. g[x].push_back({y,va,vb});
0. }
0. a[1][0]=b[1][0]=1;
0. for (int i=1;i<=n;i++)
0. for (int j=0;j<g[i].size();j++){
0. int u=g[i][j].u,va=g[i][j].va,vb=g[i][j].vb;
0. for (int k=10000;k>=va;k--) a[u][k]|=a[i][k-va];
0. for (int k=10000;k>=vb;k--) b[u][k]|=b[i][k-vb];
0. }
0. for (int i=0;i<=10000;i++)
0. if (a[n][i] && b[n][i]){
0. cout<<i;
0. return 0;
0. }
0. cout<<"IMPOSSIBLE";
0. return 0;
0. }
```

---

## 作者：冷月冰瞳 (赞：2)

由于是拓扑图结构，从起点最多经过N-1条边必定会到达终点，因此最大长度也就是(N-1)\*MAXL，这里MAXL是边的最大长度，本题中为100。楼下的解题思路也都是基于这个的。我这里提出另一种用最短路求解的方法。


用D[u][v][w]表示第一个人走到了节点u，第二个人走到了节点v，第一个人走的长度减去第二个人走的长度的差为w(-MAXL<=w<=MAXL)的情况下，第一个人走的最短路长度。那么根据w的正负值，来判断下一个谁走。如果w为负数，也就是当前第一个人落后，所以这时候就是第一个人走一条边; 同理，如果w为非负，那就第二个人走。


Dijkstra求解的伪代码

```cpp
while (!vis[n][n][0] && !heap.empty()) {
    (u, v, w) = heap.top();
    vis[u][v][w] = true;
    if (w < 0) {
        for (int i = 1; i <= n; i ++) {
            if (e[u][i] > 0) update( (i, v, w+e[u][i]), dis[u][v][w]+e[u][i]) );
        }
    } else {
        for (int i = 1; i <= n; i ++) {
            if (e[v][i] > 0) update( (u, i, w-e[v][i]), dis[u][v][w]);
        }
    }
}
```

在这个方法中，节点总数为O(N\*N\*MAXL)，每个节点都连出去最多N条边，用Dijkstra求解的话，就是O(N^3\*MAXL\*log(N))。虽然复杂度看上去比楼下的方法高，但是这个方法不需要拓扑图结构，是个更一般的解法。例如下面这个例子（一般的有向图）：

```cpp
3 3
1 2 100 99
2 3 100 99
3 1 1 1
```
这个图的答案为39998，如果点数增多，答案会变得更大。


---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经了解了题目意思

题目说让我们求两只奶牛同时到达时间的最小值

显然，我们直接跑最短路是不可以的，因为你不知道最短路是不是最后的答案，而一条一条的跑很容易超时或者超空间

我们可以考虑，用拓扑来解决这个问题

用$f_i ,_j = 0/1$表示奶牛$Bessie$能否用$j$的时间到达$i$

用$g_i ,_j = 0/1$表示奶牛$Elsie$能否用$j$的时间到达$i$

每次插入一条边，我们就加一次入边

跑一边拓扑排序

最后用循环判断最小边即可

要注意一下，不可能走到的情况输出$IMPOSSIBLE$

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct node{
	int nxt;
	int to;
	int d1,d2;
}e[10010];
int f[110][10010],g[110][10010];
int vis[110];
int head[110];
int ru[110];
int n,m,cnt;
queue<int> q;
inline void add(int u,int v,int w1,int w2){
	++cnt;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].d1=w1;
	e[cnt].d2=w2;
	ru[v]++;
	head[u]=cnt;
}
signed main(){
	n=read();
	m=read();
	for(register int i=1;i<=m;++i)
		{
			int x,y,z1,z2;
			x=read();
			y=read();
			z1=read();
			z2=read();
			add(x,y,z1,z2);
		}
	for(register int i=1;i<=n;++i)
		if(!ru[i])
			q.push(i);
	f[1][0]=1;
	g[1][0]=1;
	while(!q.empty())
		{
			int tmp;
			tmp=q.front();
			q.pop();
			for(register int i=head[tmp];i;i=e[i].nxt)
				{
					int y;
					y=e[i].to;
					int z1,z2;
					z1=e[i].d1;
					z2=e[i].d2;
					for(register int j=0;j+z1<10001;++j)
						f[y][j+z1]|=f[tmp][j];
					for(register int j=0;j+z2<10001;++j)
						g[y][j+z2]|=g[tmp][j];
					ru[y]--;
					if(!ru[y])
						q.push(y);
				}
		}
	for(register int i=0;i<10001;++i)
		{
			if(f[n][i] && g[n][i])
				{
					write(i);
					return 0;
				}
		}
	puts("IMPOSSIBLE");
	return 0;
}

```


---

## 作者：lwyz123 (赞：1)

我来说一种 同为A*  K短路优化 但可以极大优化时长的方法

首先   两个人的最短路可以同时跑
然后   在求k短路的时候也可以同时跑；
不但可以减少代码长度，也能减少常数

### 划重点  用到STL ————MAP 
你可以把可行的路径长度放入 map 数组中；

并且把这个路径记录一下 那个走这个路径的 人的编号

如果这个路径另一个人已经走过，

那此时答案一定是最优的直接(exit(0))

停止程序

下面是代码


~~未压行 代码有些长~~
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
void r(int &x)
{
	char a;
	int f=1;
	while((a=getchar())<'0'||a>'9')if(a=='-')f=-1;
	x=a-48;
	while((a=getchar())>='0'&&a<='9')
	x=(x<<3)+(x<<1)+a-48;
	x=x*f;
}
map<int,int>ma;
struct edge{
	int to,nexty,val1,val2;
}e[50500],R[50500];
int head[105],fist[103];
int cnt,tot;
void add(int a,int b,int c,int d)
{
	e[++cnt].to=b;
	e[cnt].nexty=head[a];
	e[cnt].val1=c;
	e[cnt].val2=d;
	head[a]=cnt;
}
void add2(int a,int b,int c,int d)
{
	R[++tot]=(edge){b,fist[a],c,d};
	fist[a]=tot;
}
int dis[105][3];//dis[1]Bessie,dis[2] Elsie;
int vis[105];
void spfa(int sx)
{
	queue<int>q;
	memset(dis,0x3f,sizeof(dis));
	dis[sx][1]=0;
	dis[sx][2]=0;
	q.push(sx);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		vis[x]=0;
		int f=0;
		for(int i=head[x];i;i=e[i].nexty)
		{
			int to=e[i].to;
			if(dis[to][2]>dis[x][2]+e[i].val2)
			{
				dis[to][2]=dis[x][2]+e[i].val2;
				f=1;
			}
			if(dis[to][1]>dis[x][1]+e[i].val1)
			{
				dis[to][1]=dis[x][1]+e[i].val1;
				f=1;
			}
			if(f&&!vis[to])
			{
				vis[to]=1;
				q.push(to);
			}
		}
	}	
}
struct node{
	int x,id;
	int dis,g;
	bool operator<(const node &a)const 
	{
		return dis+g>a.g+a.dis;
	}
};
priority_queue<node>q;
int n,m;
void Astar()
{
	node begn;
	begn.x=1;
	begn.id=1;
	begn.dis=0;
	begn.g=dis[1][1];
	q.push(begn);
	begn.id=2,begn.g=dis[1][2];
	q.push(begn);
	while(!q.empty())
	{
		int x=q.top().x;
		node tp=q.top();
		q.pop();
		if(x==n)
		{
			if(!ma[tp.dis])ma[tp.dis]=tp.id;
			else if(ma[tp.dis]&&ma[tp.dis]!=tp.id){cout<<tp.dis<<"\n";exit(0);}
			continue;
		}
		for(int i=fist[x];i;i=R[i].nexty)
		{
			int to=R[i].to;
			node nx;
			if(tp.id==1) nx.dis=tp.dis+R[i].val1;
			if(tp.id==2) nx.dis=tp.dis+R[i].val2;
			nx.g=dis[to][tp.id];
			nx.x=to;
			nx.id=tp.id;
			q.push(nx);
		}
	}
}
signed main()
{
	r(n),r(m);
	for(int i=1,x,y,a,b;i<=m;i++)
	{
		r(x),r(y),r(a),r(b);
		add(y,x,a,b);
		add2(x,y,a,b);
	}	
	spfa(n);
	if(dis[1][1]==0x3f3f3f3f||dis[1][2]==0x3f3f3f3f)
	{
		cout<<"IMPOSSIBLE\n";
		exit(0);
	}
	Astar();
	return 0;
}
```


---

## 作者：qscisQJing (赞：0)

考虑 dp。

因为边权和节点数都很小，而且一条由 $ 1 $ 到 $ n $ 路径最多经过 $ n $ 个点，我们可以考虑设状态为 $ c_{i,j} $ 和 $ d_{i,j} $，分别表示两头牛在 $ j $ 这个时间能否到达第 $ i $ 个田地。它的空间复杂度是 $ O(n^3) $ 的。

此时的转移方程也十分显然了：

$ c_{i,j}=c_{i,j} \operatorname{or} c_{v,j-wc} $

$ d_{i,j}=d_{i,j} \operatorname{or} d_{v.j-wd} $

$ wc $ 与 $ wd $ 分别表示这条边对两头牛的不同的边权。转移的条件是存在一条 $ v $ 到 $ i $ 的边。

这是一个时间复杂度为 $ O(n^4) $ 的算法，已经可以通过本题。但这个 dp 的转移过程本身还可以优化。

如果改变枚举顺序，即对于每个田地，依次枚举能转移的田地，那么 $  v  $、$  wc $、$ wd $ 这三个值都是固定的。而这个 dp 剩下的转移很明显可以用 bitset  优化。

优化后的转移方程为：

$ c_i=c_i \operatorname{or} (c_v\times 2^{wc}) $

$ d_i=d_i \operatorname{or} (d_v\times 2^{wd}) $

时间复杂度优化至 $ O(\frac{n^4}{\omega}) $。

# 无优化代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int c[MAXN][MAXN*MAXN],d[MAXN][MAXN*MAXN];
struct node
{
	int v,w1,w2;
};
vector<node> ve[MAXN];
int main()
{
	int n,m;cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c,d;scanf("%d%d%d%d",&u,&v,&c,&d);
		ve[v].push_back({u,c,d});
	}
	c[1][0]=d[1][0]=1;
	for(int i=2;i<=n;i++)
	{
		for(auto u:ve[i])
		{
			for(int j=u.w1;j<=10000;j++)
				c[i][j]|=c[u.v][j-u.w1];
			for(int j=u.w2;j<=10000;j++)
				d[i][j]|=d[u.v][j-u.w2];
		}
	}
	for(int i=0;i<=10000;i++)
	{
		if(c[n][i]&&d[n][i])
		{
			cout<<i;
			return 0;
		}
	}
	puts("IMPOSSIBLE");
	return 0;
}
```

# bitset优化后的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
bitset<MAXN*MAXN> c[MAXN],d[MAXN];
struct node
{
	int v,w1,w2;
};
vector<node> ve[MAXN];
int main()
{
	int n,m;cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c,d;scanf("%d%d%d%d",&u,&v,&c,&d);
		ve[v].push_back({u,c,d});
	}
	c[1][0]=d[1][0]=1;
	for(int i=2;i<=n;i++)
	{
		for(auto u:ve[i])
		{
			c[i]=c[i]|(c[u.v]<<u.w1);
			d[i]=d[i]|(d[u.v]<<u.w2);
		}
	}
	bitset<MAXN*MAXN> ans;
	ans=c[n]&d[n];
	for(int i=0;i<=10000;i++)
	{
		if(ans[i])
		{
			cout<<i;
			return 0;
		}
	}
	puts("IMPOSSIBLE");
	return 0;
}
```



---

## 作者：Error_Eric (赞：0)

### 题意

[Link](https://www.luogu.com.cn/problem/P3116)

### 解法

先指出大部分题解的一个错误，本题拓扑排序没有必要因为加边方式 $u<v$ 已经给定了 $1,2,3...n$ 是一个合法的拓扑序。

这里给出一种全新的 dp 方法： 《高精状压dp》

记 $f_i$ 的第 $j$ 位为 $1$ 表示存在 Bessie 从 $1$ 到 $i$ 耗时 $j$ 的方案。$g_i$ 的第 $j$ 位为 $1$ 表示存在 Elsie 从 $1$ 到 $i$ 耗时 $j$ 的方案。

转移方程显然：

$f_i|=f_j<<a_{j,i}\ \ (j,i)\in E$ 。

$g_i|=g_j<<b_{j,i}\ \ (j,i)\in E$ 。

从数学角度看似乎复杂度达到了及其快乐的 $O(n)$。但是哪怕是状压高精一个 ull 只有 64 位二进制位，但是这里的 $f,g$ 可以高达 $2^{10^4}$ ,常数也高达 156 这样子。

理论复杂度比题解区主流的 $O(n^3)$ 快 100 倍左右。

### Code

但是我比较懒这么宽的时限直接上 python。

python 能进前12%可见这种方法还是有用的。更何况疑似最短代码。

```python
s=input().split();n=int(s[0]);m=int(s[1])
fa=[[]for i in range(n)];a=[[]for i in range(n)];b=[[]for i in range(n)]
f=[0 for i in range(n)];g=[0 for i in range(n)]
f[0]=g[0]=1
for i in range(m):
    s=input().split();to=int(s[1])-1
    fa[to].append(int(s[0])-1)
    a[to].append(int(s[2]))
    b[to].append(int(s[3]))
for i in range(n):
    j=0
    for fr in fa[i]:
        f[i]|=(f[fr]<<a[i][j]);g[i]|=(g[fr]<<b[i][j])
        j+=1
ans=(f[n-1]&g[n-1])
cnt=0
if ans==0:
    print("IMPOSSIBLE")
else:
    while ans&1==0:
        ans>>=1;cnt+=1
    print(cnt)

```

---

## 作者：ExplodingKonjac (赞：0)

### [【原题链接】](https://www.luogu.com.cn/problem/P3116)

## 题目分析

提供一种不依赖边权范围的做法。

题意就是，给出一张 DAG，有两种边权，求出一个最小的 $w$，使得两种边权的图都存在长度为 $w$ 的 $1\to n$ 的路径。为了方便，我们设两个图为 $G_1,\ G_2$

我们设 $S_{u,i}$ 表示在 $G_i$ 中所有 $1\to u$ 的可能路径长度组成的集合。由于 $n$ 很小，我们可以把每个 $u$ 的 $S_{u,1},\ S_{u,2}$ 求出来、

假设我们在图 $G_i$ 中存在一条边 $u\to v$，其边权为 $w$。可以发现，对于 $\forall x\in S_{u,i}$，则一定有 $x+w\in S_{v,i}$。原图是 DAG，所以我们就可以按照拓扑序进行 DP。最后的答案就是 $S_{n,1}\cap S_{n,2}$ 中的最小值。

可以直接使用 `std::set` 进行如上的过程。具体而言，对于 $u$，枚举 $S_{u,i}$ 的所有元素 $x$，并将 $x+w$ 放入 $S_{v,i}$，详见代码。

容易证明，本做法复杂度为 $\Theta(玄学)$。我使用 `std::set` 并卡不过时限，所以可以用 $\text{C++11}$ 的黑科技 `std::unordered_set`。

## 代码实现

**拓扑排序一定要把所有入度为 $0$ 的点入队列！**

但是只需要给 $S_{1,1},\ S_{1,2}$ 插入一个初始值 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 
省略快读快些模板
即代码中的qin、qout
*/

int n,m,deg[105];
unordered_set<int> s1[105],s2[105];
struct Edge{ int to,nxt,w1,w2; }e[10005];
int cnt,head[105];
inline void addEdge(int u,int v,int w1,int w2)
	{ e[++cnt]=(Edge){v,head[u],w1,w2},head[u]=cnt; }
int main()
{
	qin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,w1,w2;
		qin>>u>>v>>w1>>w2;
		addEdge(u,v,w1,w2),deg[v]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(!deg[i])	q.push(i);
	s1[1].insert(0),s2[1].insert(0);
	int u,v;
	while(!q.empty())
	{
		u=q.front();
		for(int i=head[u];i;i=e[i].nxt)
		{
			v=e[i].to;
			for(auto &j: s1[u])	s1[v].insert(j+e[i].w1);
			for(auto &j: s2[u])	s2[v].insert(j+e[i].w2);
			if(!(--deg[v]))	q.push(v);
		}
		q.pop();
	}
	int ans=1e9;
	for(auto &i: s1[n])
	{
		int zt=s2[n].count(i);
		if(zt)	ans=min(ans,i);
	}
	if(ans!=1e9)	qout<<ans;
	else	qout<<"IMPOSSIBLE";
	return qout.flush(),0;
}
```


---

