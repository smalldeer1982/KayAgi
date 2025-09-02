# Strange Set

## 题目描述

**请注意本题的时间与空间限制**   
  
你有两个长度均为 $n$ 的序列 $a_1,a_2,\dots,a_n$ 和 $b_1,b_2,\dots,b_n$。  
  
我们定义一个集合 $S\subseteq\{1,2,\dots,n\}$ 是奇怪的，当且仅当：对于任意 $i\in S$，如果有 $j\in [1,i-1]$，满足 $a_j|a_i$，则也有 $j\in S$。特别地，**空集**总是一个奇怪的集合。  
  
定义一个集合 $S$ 的权为 $\sum_{i\in S} b_i$。请求出所有奇怪集合的最大权。

## 说明/提示

第一个样例中，权值最大的奇怪集合为 $\{1,2,4,8,9\}$。   
   
第二个样例中，权值最大的奇怪集合为 $\varnothing$。

## 样例 #1

### 输入

```
9
4 7 3 4 5 6 7 8 13
-2 3 -19 5 -6 7 -8 9 1```

### 输出

```
16```

## 样例 #2

### 输入

```
2
42 42
-37 13```

### 输出

```
0```

## 样例 #3

### 输入

```
2
42 42
13 -37```

### 输出

```
13```

# 题解

## 作者：wsyhb (赞：8)

## 题意简述

给定长度为 $n$ 的数列 $a$ 和 $b$，设 $S \subset \{1,2,3,\cdots,n\}$，其满足对于任意的 $i \in S$，$j \in [1,i-1]$，若 $a_i$ 被 $a_j$ 整除，则 $j \in S$。求 $\sum_{i \in S}b_i$ 的最大值。

**数据范围**：$n \le 3000$，$1 \le a_i \le 100$，$-10^5 \le b_i \le 10^5$

## 分析 + 题解

看完题意，你可能会觉得这是一道贪心题，但是一看到数据范围 $n \le 3000$，就感觉不太对劲——为何 $n$ 这么小？再仔细一想，这是一道**有依赖关系的、数据范围不是很大的最优性选择问题**，于是考虑**网络流**。~~事实上我在比赛过程中压根没想到这一点。~~

如果想到了网络流，那很明显这是一种**最小割**模型，建图方法如下：

设源点为 $s$，汇点为 $t$，第 $i$ 个元素对应 $i$ 号点。对于每一个 $i$，设 $j<i$ 且 $a_i$ 被 $a_j$ 整除，则由 $i$ 号点 向 $j$ 号点连一条流量为 $inf$ 的边。若 $b_i>0$，则由 $s$ 向 $i$ 号点连一条流量为 $b_i$ 的边；否则，$b_i<0$，则由 $i$ 号点向 $t$ 连一条流量为 $-b_i$ 的边。

**说明**：首先考虑所有 $b_i>0$ 的 $i$ 号点，若选择 $i$，即 $i \in S$，则必然选择与之有依赖关系的 $b_j<0$ 的 $j$——事实上，$i$ 到 $j$ 有流量为 $inf$ 的边恰好满足了这一点。而这张图的割分为两部分，左半部分对应**没有选择**的 $b_i>0$ 的 $b_i$ 之和，右半部分对应**被迫选择**的 $b_i<0$ 的 $-b_i$ 之和，因此**答案**恰为 **$\sum_{b_i>0}b_i$ 减去最小割**。

## 代码实现

注意到若所有的 $a$ 相等，则边数会到达上界 $O(n^2)$，而这道题的空间为 32MB，根本存不下。由于 $1 \le a_i \le 100$，我们将其改进为，对于每个 $i$，枚举 $a_i$ 的约数，找到每个约数最后一次出现的位置 $j$，由 $i$ 向 $j$ 连一条流量为 $inf$ 的边，边数上界降为 $12n$。

由于最小割和最大流相等，只需按上述方法建图跑最大流即可。

PS：如果你不会写最大流，建议前往 [P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376) 进行学习。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int N,S,T;
const int max_N=3e3+5;//3000+2 个点 
const int max_M=39e3+5;//12*3000+3000 条边 
const int inf=1e9;
int End[max_M<<1],Last[max_N],Next[max_M<<1],cap[max_M<<1],e=1;//注意 e 初始为 1（正反边常规操作） 
inline void add_edge(int x,int y,int c)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	cap[e]=c;
	End[++e]=x;
	Next[e]=Last[y];
	Last[y]=e;
	cap[e]=0;
}
int dis[max_N],q[max_N],_head,_tail;
int Last1[max_N],cnt[max_N];
void bfs()
{
	for(int i=1;i<=N;++i)
		dis[i]=N,cnt[i]=0;
	dis[T]=0;
	_head=1,_tail=0;
	q[++_tail]=T;
	while(_head<=_tail)
	{
		int x=q[_head++];
		for(int i=Last[x];i;i=Next[i])
		{
			int y=End[i];
			if(cap[i^1]>0&&dis[y]>dis[x]+1)
			{
				dis[y]=dis[x]+1;
				q[++_tail]=y;
			}
		}
	}
	for(int i=1;i<=N;++i)
	{
		Last1[i]=Last[i];
		++cnt[dis[i]];
	}
}
int dfs(int x,int flow)
{
	if(x==T)
		return flow;
	int flow_now=0;
	for(int &i=Last1[x];i;i=Next[i])
	{
		int y=End[i];
		if(dis[x]==dis[y]+1&&cap[i]>0)
		{
			int f=dfs(y,min(cap[i],flow-flow_now));
			flow_now+=f;
			cap[i]-=f;
			cap[i^1]+=f;
			if(flow==flow_now||dis[S]==N)
				return flow_now;
		}
	}
	Last1[x]=Last[x];
	if(!(--cnt[dis[x]]))
		dis[S]=N;
	++cnt[++dis[x]];
	return flow_now;
}
/*----以上为最大流模板----*/
const int max_n=3e3+5;
int a[max_n],b[max_n];
const int max_a=100+5;
int pos[max_a];//pos[i] 记录当前 i 最后一次出现的位置 
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n;++i)
		scanf("%d",b+i);
	N=n+2,S=n+1,T=n+2;
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(b[i]>0)
		{
			add_edge(S,i,b[i]);
			ans+=b[i];
		}
		else if(b[i]!=0)
			add_edge(i,T,-b[i]);
		for(int j=1;j<=a[i];++j)
		{
			if(a[i]%j==0&&pos[j]!=0)//判断 j 是否为 a[i] 的约数及 j 是否出现过 
				add_edge(i,pos[j],inf);
		}
		pos[a[i]]=i;//更新 pos 
	}
	bfs();
	int flow=0;
	while(dis[S]<N)
		flow+=dfs(S,inf);
	printf("%d\n",ans-flow);
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

我们可以发现有若干形如

> 若 $\mathbf{A}$ 入选，那么 $\mathbf{B}$ 一定入选

的限制。

考虑最小割，设 $S$ 集合代表选择的下标，$T$ 集合代表不被选择的下标。

那么对于所有的限制条件 $\left(A, B\right)$，可以连边 $A \rightarrow B$，容量为 $\infty$。

但是由于本题空间限制很小，如此连边会导致 $\tt{MLE}$。

发现值域很小，故我们可以考虑向每种值在当前节点之前、最后一次出现的节点连边，而被连边的节点又一定会和其他在更前方且符合要求的节点连边，因此可以保证正确性。

由于 $100$ 以内的因子最多的数的因子个数为 $12$ 个。所以边数是 $\mathcal{O}(n)$ 级别的。


---

## 作者：Leap_Frog (赞：1)

~~怎么感觉这场比赛 C 比 F 难啊/px~~
### Description.
定义一个集合是好的当且仅当 $\forall i\in S,\forall j<i\land a_j|a_i,\texttt{都有},j\in S$
定义一个集合的权值是 $\sum_{i\in S}b_i$ ，求好集合中最大权值。  
### Solution.
前置知识：最大权闭合子图。  
~~当你会了前置知识后你会发现你做完了此题~~  
我们对 $i$ 向之前的所有满足 $j<i\land a_j|a_i$ 的 $j$ 拉边。  
而每个点的点权是它原来的 $b_i$。  
对这个图求一个最大权闭合子图就好了。  
不过，这题有点卡空间。  
我们发现，我们按照方法建立的最大权闭合子图最大边数可能是 $N^2$。  
那么我们考虑，如果边不是源点这一侧二分图指向汇点一侧二分图的话，我们就不要它。  
显然是对的，因为其他的边显然不会被流到。  
这样我们就成功的把边数压缩成了 $\left(\frac{N}2\right)^2$，足以通过此题。  

### Coding.
```cpp
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;typedef long long typf;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}
struct edge{int to,w,nxt;}e[2551005];int et=1,head[3005],s,t;
int d[3005],cur[3005];const typf INF=(typf)0x3f3f3f3f3f3f3f3f;
inline void ADDE(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void adde(int x,int y,int w) {ADDE(x,y,w),ADDE(y,x,0);}
inline char	bfs(int s,int t)
{
	queue<int>q;memset(d,0,sizeof(d)),d[s]=1,q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt) if(!d[e[i].to]&&e[i].w) q.push(e[i].to),d[e[i].to]=d[x]+1;
	}
	return !!d[t];
}
inline int dfs(int x,int t,int lim=(int)INF)
{
	int f=lim;if(x==t) return lim;
	for(int &i=cur[x];i;i=e[i].nxt) if(e[i].w&&d[e[i].to]==d[x]+1)
		{int g=dfs(e[i].to,t,min(f,e[i].w));e[i].w-=g,e[i^1].w+=g,f-=g;if(!f) break;}
	return lim-f;
}
inline typf dinic(int s,int t) {typf r=0;while(bfs(s,t)) memcpy(cur,head,sizeof(cur)),r+=dfs(s,t);return r;}
int n,a[3005],b[3005];
int main()
{
	read(n),s=n+1,t=s+1;for(int i=1;i<=n;i++) read(a[i]);
	int cnt=0;for(int i=1;i<=n;i++) read(b[i]);
	for(int i=1;i<=n;i++) if(b[i]<0) adde(i,t,-b[i]);else cnt+=b[i],adde(s,i,b[i]);
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(a[j]%a[i]==0&&b[j]>0&&b[i]<0) adde(j,i,(int)INF);
	return printf("%lld\n",cnt-dinic(s,t)),0;
}
```

---

## 作者：MiRaciss (赞：1)

这里提供一种非常简单，而且贼有效的连边方式

首先因为靠后的点会被靠前的点限制，所以这是一道 最大闭合子图 的板题。

但是出题人卡了空间，当所有的 $a_i$ 相同的时候，连边的复杂度是 $n^2$ 的，会被卡掉。

我们考虑优化，因为 $a_i \leq 100$，所以我们最多只需要连 $100$ 条边就可以了，所以我们当 $i$ 已经向 $j$ 连边了，那么当 $a_k=a_j,k\neq j$ 的时候，我们就不需要由 $i$ 向 $k$ 连边了。这个可以直接用桶来实现。

那么我们就把空间复杂度优化到了 $O(n)$ 级别。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int INF=0x3f3f3f3f;

struct zz{
	int u,w,id;
};
vector<zz> v[200005];
struct Dinic{
	int dist[200005],be[200005];
	int s,t;
	void Add(int x,int y,int z){
		int idx=v[x].size(),idy=v[y].size();
		v[x].push_back((zz){y,z,idy});
		v[y].push_back((zz){x,0,idx});
	}
	bool BFS(){
		bool f=0;memset(dist,-1,sizeof dist);
		queue<int> q;q.push(s);
		dist[s]=be[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			int siz=v[x].size();
			for(int i=0;i<siz;i++){
				int y=v[x][i].u,w=v[x][i].w;
				if(!w||dist[y]!=-1) continue;
				q.push(y),be[y]=0,dist[y]=dist[x]+1;
				if(y==t) f=1;
			}
		}
		return f;
	}
	int DFS(int x,int sum){
		if(x==t||!sum) return sum;
		int siz=v[x].size(),ans=0;
		for(int i=be[x];i<siz;i++){
			int y=v[x][i].u,w=v[x][i].w,id=v[x][i].id;be[x]=i;
			if(!w||dist[x]!=dist[y]-1) continue;
			int now=DFS(y,min(sum-ans,w));
			if(!now) dist[y]=0;
			v[x][i].w-=now,v[y][id].w+=now,ans+=now;
		}
		return ans;
	}
	int dinic(){
		int ans=0,now=0;
		while(BFS()) while(now=DFS(s,INF)) ans+=now;
		return ans;
	}
}T;
int n,sum=0;
int a[10005],b[10005];
bool f[3005];

vector<int> V[100005];

signed main(){
	cin>>n;T.s=0,T.t=n+1;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) {
		memset(f,0,sizeof f);
		for(int j=i-1;j>=1;j--){
			if(f[a[j]]) continue;
			if(a[i]%a[j]==0) T.Add(i,j,INF),f[a[j]]=1;
			
		}
	}
	for(int i=1;i<=n;i++){
		if(b[i]>=0) T.Add(T.s,i,b[i]),sum+=b[i];
		else T.Add(i,T.t,-b[i]);
	}
	printf("%lld\n",sum-T.dinic());
	return 0;
}
```

---

## 作者：STrAduts (赞：0)

> 在查看此题解前希望您能先去了解什么是最大权闭合子图，就不在题解中阐释该模型的基本原理了。优化建图才是关键嘛（（

CF 2700 确实假的离谱。

$A$ 序列已经给出了非常明确的依赖关系，且权值 $B$ 固定，所以它是一道最大权闭合子图的裸题。

但是直接莽会发现因为边数在 $A$ 中所有元素都相等的情况下会达到 $n^2$ 级别，于是考虑优化边。

很显然有这样的关系，若 $a_p=a_q=a_i(i \in [3, n], p, q \in [1, i - 1], p \neq q)$，则在依赖关系中，$a_p, a_q$ 都依赖于 $a_i$，且 $a_p$ 依赖于 $a_q$。

那么直接按照题目给定的依赖关系连边会发现我们连了 $a_p \to a_q, a_p \to a_i, a_q \to a_i$，但其实这和我们只连 $a_p \to a_q, a_q \to a_i$ 是等价的。

也就是说对于每一个 $a_i$，我们暴力枚举 $a_i$ 的约数，让该数目前最晚出现的位置与当前位置连边即可。

转化到这里，仍然是一个最大权闭合子图的裸题。

```cpp
#include <queue>
#include <cstdio>
using namespace std;

int Abs(int x) { return x < 0 ? -x : x; }
int Max(int x, int y) { return x > y ? x : y; }
int Min(int x, int y) { return x < y ? x : y; }

int read() {
    int x = 0, k = 1;
    char s = getchar();
    while(s < '0' || s > '9') {
        if(s == '-')
            k = -1;
        s = getchar();
    } 
    while('0' <= s && s <= '9') {
        x = (x << 3) + (x << 1) + (s ^ 48);
        s = getchar();
    }
    return x * k;
}

void write(int x) {
    if(x < 0) {
        x = -x;
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void print(int x, char s) {
    write(x);
    putchar(s);
}

const int MAXN = 3e3 + 5;
const int MAXM = 2e5 + 5;
const int MAXL = 3e3 + 5;
const int INF = 2147483647;

struct Maximum_flow {
    struct edge {
        int v, nxt;
        edge() {}
        edge(int V, int Nxt) {
            v = V, nxt = Nxt;
        }
    } e[MAXM << 1];
    int n, cnt, s, t;
    int Cap[MAXM << 1], Flow[MAXM << 1];
    int Lab[MAXL], Cur[MAXL], head[MAXL], Col[MAXL];
    queue<int> q;

    void init(int N, int S, int T) {
        for(int i = 0; i <= cnt; i++) 
            Flow[i] = 0, Cap[i] = 0;
        n = N, cnt = 0, s = S, t = T;
        for(int i = 1; i <= n; i++)
            head[i] = -1, Col[i] = 0;
    }

    void Add_Edge(int u, int v, int w) {
        Cap[cnt] += w;
        e[cnt] = edge(v, head[u]);
        head[u] = cnt++;
        e[cnt] = edge(u, head[v]);
        head[v] = cnt++;
    }

    bool Lab_Vertex() {
        for(int i = 1; i <= n; i++)
            Lab[i] = 0;
        Lab[t] = 1;
        while(!q.empty())
            q.pop();
        q.push(t);
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int i = head[v], u; ~i; i = e[i].nxt) {
                u = e[i].v;
                if(!Lab[u] && Cap[i ^ 1] - Flow[i ^ 1]) {
                    Lab[u] = Lab[v] + 1;
                    q.push(u);
                    if(u == s)
                        return Lab[s];
                }
            }
        }
        return Lab[s];
    }

    int Widen(int u, int Limit) {
        if(u == t)
            return Limit;
        int Used = 0, Delta;
        for(int i = Cur[u], v; ~i; i = e[i].nxt) {
            v = e[i].v;
            Cur[u] = i;
            if(Lab[v] + 1 != Lab[u] || Cap[i] - Flow[i] <= 0)
                continue;
            Delta = Widen(v, Min(Limit - Used, Cap[i] - Flow[i]));
            Used += Delta, Flow[i] += Delta, Flow[i ^ 1] -= Delta;
            if(Used == Limit)
                return Used;
        }
        return Used;
    }

    int Dinic() {
        int res = 0;
        while(Lab_Vertex()) {
            for(int i = 1; i <= n; i++)
                Cur[i] = head[i];
            res += Widen(s, INF);
            if(res < 0)
                return INF;
        }

        return res;
    }

    void Color(int u) {
        Col[u] = 1;
        for(int i = head[u]; ~i; i = e[i].nxt) 
            if(Cap[i] - Flow[i] > 0 && !Col[e[i].v])
                Color(e[i].v);
    }
} Flow_Graph;

int a[MAXN], b[MAXN], to[MAXN];

int main() {
    int n = read(), S = n + 1, T = n + 2, ans = 0;
    Flow_Graph.init(T, S, T);
    for(int i = 1; i <= n; i++) {
        a[i] = read();
        for(int j = 1; j <= a[i]; j++)
            if(a[i] % j == 0 && to[j])
                Flow_Graph.Add_Edge(i, to[j], INF);
        to[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        b[i] = read();
        if(b[i] > 0) {
            Flow_Graph.Add_Edge(S, i, b[i]);
            ans += b[i];
        }
        else    
            Flow_Graph.Add_Edge(i, T, -b[i]);
    }
    print(ans - Flow_Graph.Dinic(), '\n');
    return 0;
}
```

---

## 作者：LTb_ (赞：0)

[更好的阅读](http://lycltb.top/post/solution-cf1473f/)

好哦 是独立（并没有）做出来的第一道 *2700

注意到这个有先决条件的选数 以及数据范围都长得很像最大权闭合子图模型，于是用这个模型去做。

超级源 $S$ 向每个正权点 $i$（$b_i$ 为正的数）连流量为 $b_i$ 的边，每个负权点 $i$（$b_i$ 为负的数）向超级汇 $T$ 连流量为 $-b_i$ 的边，所有满足 $a_j\ |\ a_i$ 且 $i\in [1,n],\  j\in [1,i-1]$ 的有序对 $(i,j)$ 连边 $(i,j)$，权值为 $\texttt{INF}$。答案即为所有正权点之和减去最小割。

到这里还没有结束，我们注意到有一个毒瘤的 32MB 的空间限制，而直接连边的话边数是 $10^7$ 级别的，刚好被卡掉。

考虑优化一下连边：如果已经有边 $(i,j)$，$(j,k)$ 存在，我们就不需要再连 $(i,j)$ 的边。开一个 $\texttt{vis}$ 数组表示 $(i,j)$ 是否还需要连边（刚好能开下）即可，连边数量降到了线性。

```cpp
// 2021.01.17
// Code by LTb
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
inline void chmax(int &x,int y){x=max(x,y);}
inline void chmin(int &x,int y){x=min(x,y);}

const int INF=1e9+7;
const int MAXN=3005;
const int MAXM=20005;
int s,t;
int Index=0;
int w[MAXM*2];
vector<int> v[MAXN];
int point[MAXM*2];
int label[MAXN];
int cur[MAXN*2];

void add_edge(int x,int y,int f){
	v[x].push_back((++Index)*2);
	v[y].push_back(Index*2+1);
	w[Index*2]=f;
	w[Index*2+1]=0;
	point[Index*2]=y;
	point[Index*2+1]=x;
}

bool bfs(){
	memset(label,0,sizeof(label));
	memset(cur,0,sizeof(cur));
	queue<int> q;
	q.push(s);
	label[s]=1;
	while (!q.empty()){
		int now=q.front();
		q.pop();
		for (int i=0;i<v[now].size();i++){
			int edge=v[now][i];
			int u=point[edge];
			if (!label[u] && w[edge]){
				label[u]=label[now]+1;
				q.push(u);
			}
		}
	}

	return label[t]!=0;
}

int dfs(int p,int limit){
	if (limit==0||p==t) return limit;

	int used=0;
	for (int i=cur[p];i<v[p].size();i++){
		cur[p]=i;
		int edge=v[p][i];
		int u=point[edge];
		if (w[edge] && label[p]+1==label[u]){
			int flow=dfs(u,min(limit-used,w[edge]));
			used+=flow;
			w[edge]-=flow;
			w[edge^1]+=flow;
			if (used==limit) break;
		}
	}

	return used;
}

int dinic(){
	int ans=0;
	while (bfs())
		ans+=dfs(s,INF);
	return ans;
}

int n;
int a[MAXN],b[MAXN];
int sum=0;
bool vis[MAXN][MAXN];

signed main()

{
	n=read();
	s=0;t=n+1;
	for (int i=1;i<=n;i++)
		a[i]=read();

	for (int i=1;i<=n;i++){
		b[i]=read();
		if (b[i]>0) {sum+=b[i];add_edge(s,i,b[i]);}
		else add_edge(i,t,-b[i]);

		for (int j=i-1;j>=1;j--){
			if (a[i]%a[j]==0 && !vis[i][j]){
				add_edge(i,j,INF);
				vis[i][j]=true;
				for (int k=1;k<j;k++)
					vis[i][k]|=vis[j][k];
			}
		}
	}

	cout<<sum-dinic()<<endl;
	return 0;
}
```



---

