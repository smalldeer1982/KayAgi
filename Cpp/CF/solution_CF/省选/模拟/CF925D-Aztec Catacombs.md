# Aztec Catacombs

## 题目描述

一位探险者发现了古代阿兹特克人的地下墓穴，里面有一个金色的神像。地下墓穴由 $n$ 个密室组成。每对密室都连接着一条**双向**走廊，走廊有开放和封闭两种状态。墓穴的入口在 $1$ 号密室，神像和出口在 $n$ 号密室。



当探险者从 $x$ 密室经过开放的走廊进入 $y$ 密室时，与 $x$ 密室相连的所有走廊都会改变其状态（所有开放的走廊都会封闭，所有封闭的走廊都会打开）。探险者希望从 $1$ 号密室穿过尽可能少的走廊到达 $n$ 号密室。请你帮助他找到最佳路径，或者确定不可能走出地下墓穴。

## 说明/提示

$2 \leq n \leq 3 \cdot 10^5$

$0 \leq m \leq 3 \cdot 10^5$

数据保证没有重复的走廊

可以证明，路径长度一定不大于 $10^6$。

## 样例 #1

### 输入

```
4 4
1 2
2 3
1 3
3 4
```

### 输出

```
2
1 3 4 
```

## 样例 #2

### 输入

```
4 2
1 2
2 3
```

### 输出

```
4
1 2 3 1 4 
```

# 题解

## 作者：KSCD_ (赞：1)

### 思路
把初始开启的走廊放到一张图上，发现这张图上的简单路径一定能走，所以这张图上 $1$ 到 $n$ 的最短路就是一种方案，设其长度为 $d$。

考虑通过别的方法走到 $n$，发现若 $(1,n)$ 初始关闭，那么走完第一条边后就会开启，只要再走回 $1$ 就可以直接走到 $n$。那么 $1\to x\to y\to 1\to n$ 就是一种路径，其中 $(1,x),(x,y)$ 初始开启，$(y,1),(1,n)$ 初始关闭，长度为 $4$。

由于这已经是最短的**初始不完整**的路径，所以若最短路长度 $d\le 4$，就可以直接用最短路。

分析这种路径什么时候存在，发现只要有点 $y$ 与点 $1$ 的距离为 $2$，那么就存在 $x$ 使得 $(1,x),(x,y)$ 初始开启，且 $(1,y)$ 初始关闭，否则距离会变为 $1$。同时如果 $(1,n)$ 初始开启，则最短路 $d=1$，不会再用长为 $4$ 的路径，所以 $(1,n)$ 初始关闭，可以确定有这样的路径。

如果没有这种路径，那么初始与 $1$ 号点在同一个连通块中的所有点全都与 $1$ 号点有直接连边，那么先走到 $x$，以 $x$ 为新的起点寻找上一种路径，也就是 $1\to x \to y\to z\to x\to n$，其中 $(z,x),(x,n)$ 初始关闭，其余初始开启，长度为 $5$。

考虑这种路径什么时候存在，发现同上只要有点 $z$ 与点 $x$ 的距离为 $2$ 即可。那么当且仅当所有与 $1$ 连通的点 $x$ 都没有合法的 $z$ 时会无解，也就是连通块内每个点都与其他所有点有连边，即这个连通块子图是完全图。

由于在完全图上每次走边都会使出发点被完全孤立开来，只会让完全图连通块越来越小，所以这种路径也不存在时就可以确定无解了。

具体寻找路径时直接遍历所有的出边即可，时间复杂度的话第一种路径时每条边只会作为 $(x,y)$ 被搜到一次，第二种路径时 $(x,y,z)$ 似乎相当于三元环记数那种复杂度？笔者太菜不会证。
### 代码

```cpp
#include<iostream>
#include<vector> 
#include<queue>
using namespace std; 
const int N=3e5+10;
int n,m,fa[N],dis[N],te[N];
vector <int> edge[N]; 
queue <int> q;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v; cin>>u>>v;
		edge[u].push_back(v),edge[v].push_back(u);
	}
	q.push(n),dis[n]=1;
	while(q.size())
	{
		int u=q.front(); q.pop();
		for(int v:edge[u]) if(!dis[v]) dis[v]=dis[u]+1,fa[v]=u,q.push(v);
	} 
	if(dis[1]&&dis[1]<=5)
	{
		cout<<dis[1]-1<<'\n'; int p=1;
		while(p!=n) cout<<p<<' ',p=fa[p];
		cout<<n; return 0;
	} //原图最短路 
	for(int x:edge[1]) te[x]=1;
	for(int x:edge[1]) for(int y:edge[x]) if(y!=1&&te[y]!=1) 
	{
		cout<<4<<'\n'<<1<<' '<<x<<' '<<y<<' '<<1<<' '<<n;
		return 0;
	} //第一种 
	for(int x:edge[1])
	{
		for(int y:edge[x]) te[y]=x;
		for(int y:edge[x]) if(y!=1) for(int z:edge[y]) if(z!=x&&te[z]!=x)
		{
			cout<<5<<'\n'<<1<<' '<<x<<' '<<y<<' '<<z<<' '<<x<<' '<<n;
			return 0;
		}
	} //第二种 
	cout<<-1;
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：1)

如果最短路 $\le 4$ 就直接用最短路，否则 $1\to n$ 的边不存在，可能存在一组形如 $1\to x\to y\to x\to n$ 的解，否则就只能存在 $1\to x\to y\to z\to x\to n$ 的解了。

此时的 $1\to x$ 能到达所有的 $x$，因为如果不能直接到达，可以在 $1\to x$ 的路径中间找一个 $y$ 形成 $1\to y\to x\to 1\to n$ 的更优答案，因此这样做可以遍历所有的三元环，正确性得到保证。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5; 

int n, m, d[N], vis[N], p[N]; 
vector<int> G[N]; 

void dfs(int x) {
    cout << x << " "; 
    if (x != n) dfs(p[x]); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m; 
    while (m--) {
        int u, v; cin >> u >> v; 
        G[u].emplace_back(v); G[v].emplace_back(u); 
    }
    d[n] = 1; 
    queue<int> q; q.push(n); 
    while (!q.empty()) {
        int u = q.front(); q.pop(); 
        for (int v : G[u]) if (!d[v]) d[v] = d[u] + 1, p[v] = u, q.push(v); 
    }
    int nv = 1e9, p = -1; 
    if (d[1] != 0) nv = d[1], p = 1; 
    if (nv <= 4) {
        cout << nv - 1 << "\n"; 
        dfs(1); 
        return 0; 
    }
    
    for (int x : G[1]) vis[x] = 1; 
    for (int u : G[1]) for (int v : G[u]) if (v != 1 && !vis[v]) {
        cout << 4 << "\n"; 
        cout << 1 << " " << u << " " << v << " " << 1 << " " << n << "\n"; 
        return 0; 
    }
    
    for (int x : G[1]) {
        for (int y : G[x]) vis[y] = x; 
        for (int y : G[x]) if (y != 1)
            for (int z : G[y]) if (vis[z] != x && z != 1 && z != x) {
                cout << 5 << '\n';
                cout << 1 << ' ' << x << ' ' << y << ' ' << z << ' ' << x << ' ' << n << '\n';
                return 0;
            }
    }
    

    cout << "-1\n"; 

    return 0;
}
```

---

## 作者：Mr_Wu (赞：1)

赛时（vp）写错了一个字符，所以没过去

1. 首先先观察样例，若 $1\rightarrow x\rightarrow y\not\rightarrow n$，那么就可以用 4 步 $1\rightarrow x\rightarrow y\rightarrow1\rightarrow n$

2. 所以就有一个结论，若 $1$ 与 $n$ 连通且 $1$ 到 $n$ 的最短路 $\le 4$，则直接走过去。否则不考虑直接从 $1$ 走到 $n$。

- 设这条路是 $a_0,a_1,\cdots,a_k(k>4)$，因为你直接走过去而不是用上面的 $4$ 步法，所以 $a_0,a_2$ 之间是有边的。那么这条路就不是最短路了。

- 如果有一个 $\le 4$ 的最短路但你不用，则说明有一个 $\le 3$ 的方式且不是从 $1$ 直接走到 $n$。但这不太可能，因为这只能是一个点本来不能到 $n$ 但做了一些事后突然能到 $n$，所以你只能是 $1\rightarrow x\rightarrow 1\rightarrow n$ 这样，但这不太现实。

上面的证明也说明了不存在 $\le 3$ 的特殊情况，所以现在可以只考虑情况 1,2 都没有的情况了。首先易证 $1$ 的连通块内每个点的最短路 $\le 2$，然后枚举所有的情况，就发现每个边双只能是下列情况中的一个

![](https://cdn.luogu.com.cn/upload/image_hosting/e4g5ioqt.png)

这里面只有右上角那个有新东西，就是 $1$ 与 $A,B,C$ 连边，$A$ 与 $B,C$ 连边，$B,C$ 间无边。此时可以 5 步，就是从 $1$ 到 $B$ 然后用 4 步走法。

那最后的任务就是判这个东西，我在 vp 时的做法是随机化，先找出 $1$ 连出去的所有点 $V$，然后对 $V$ 内每个点处理出出边与 $V$ 的交，然后每次随 $V$ 中的一个 $A$，再从 $A$ 的处理出的出边中随两个 $B,C$，用 set 判 $B,C$ 间是否有边。做 $1e6$ 次。（**这是假的，怎么卡留给读者做练习**）

但其实也可以这样做，首先把所有与 $1$ 连边的点都找出来，那么就是要找这些点中的一个 有-有-无 形式的环。考虑抽出一个连通块中的任一个点，做 bfs，若 bfs 的深度 $\ge 2$ 就找到了，否则就是要找到一个点对之间没有边。若点对数 $\le 5e5$ 就暴力枚举，否则随机化。在最大情况下成功的概率是 $\frac{3e5}{5e5}$，随 50 次差不多就可以了。~~我没写过~~



```cpp
#include<cstdio>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<set>
using namespace std;
 
typedef long long ll;
const int MAXN=3e5+5;
 
int N,M,dis[MAXN],pre[MAXN],stk[MAXN],slen,go[MAXN];
struct node{int v,next;}E[MAXN<<1];int head[MAXN],Elen;
void add(int u,int v){
	++Elen,E[Elen].v=v,E[Elen].next=head[u],head[u]=Elen;
}
queue<int> Q;
 
int cnt[MAXN];
vector<int> out[MAXN];
set<int> S[MAXN];
 
inline int rnd(int l,int r){
	return rand()%(r-l+1)+l;
}
int vis[MAXN];
int main(){
	scanf("%d%d",&N,&M);int u,v;
	for(int i=1;i<=M;++i){
		scanf("%d%d",&u,&v),add(u,v),add(v,u);
		S[u].insert(v),S[v].insert(u);
	}
	dis[1]=1,Q.push(1);
	while(!Q.empty()){
		u=Q.front();Q.pop();
		for(int i=head[u];i;i=E[i].next)if(!dis[E[i].v]){
			dis[E[i].v]=dis[u]+1,pre[E[i].v]=u,Q.push(E[i].v);
		}
	}
	if(dis[N]&&dis[N]<=4){
		printf("%d\n",dis[N]-1);
		u=N;
		while(u!=1){
			stk[++slen]=u;
			u=pre[u];
		}
		printf("1 ");
		while(slen)printf("%d ",stk[slen--]);
	}else{
		for(int i=head[1];i;i=E[i].next)go[E[i].v]=1;
		for(int i=2;i<=N;++i)if(dis[i]==3&&!go[i]){
			printf("4\n");
			printf("1 %d %d 1 %d\n",pre[i],i,N);
			return 0;
		}
		vector<int> V;
		for(int i=head[1];i;i=E[i].next){
			V.push_back(E[i].v),vis[E[i].v]=1;
		}
		if(V.size()){
			srand(time(0));
			for(int i=0;i<V.size();++i){
				int u=V[i];
				for(int j=head[u];j;j=E[j].next)if(vis[E[j].v]){
					out[u].push_back(E[j].v);
				}
			}
			for(int turn=1;turn<=1000000;++turn){
				int A=V[rnd(0,V.size()-1)];
				if(out[A].size()){
					int B=out[A][rnd(0,out[A].size()-1)],C=out[A][rnd(0,out[A].size()-1)];
					if(B==C)continue;
					if(S[B].find(C)==S[B].end()){
						//printf("A=%d,B=%d,C=%d\n",A,B,C);
						printf("5\n");
						printf("1 %d %d %d %d %d\n",B,A,C,B,N);
						return 0;
					}
				}
			}
		}
		puts("-1");
	}
	return 0;
}
```



---

