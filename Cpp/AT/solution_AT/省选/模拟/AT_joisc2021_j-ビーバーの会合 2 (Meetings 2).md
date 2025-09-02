# ビーバーの会合 2 (Meetings 2)

## 题目描述

给出一棵大小为 $N$ 的树。

对于树上的一个点集 $S$，定义其权值为满足 $\sum\limits_{u\in S} dis(u,x)$ 取到最小值的 $x$ 的数量。

对于每一个 $1\le i \le N$，求出当点集大小为 $i$ 时的最大权值。

$1\le N \le 2\times 10^5$

## 样例 #1

### 输入

```
5
1 2
2 3
4 2
3 5```

### 输出

```
1
4
1
2
1```

## 样例 #2

### 输入

```
7
1 2
2 3
3 4
4 5
2 6
3 7```

### 输出

```
1
5
1
3
1
2
1```

# 题解

## 作者：Inui_Sana (赞：6)

唯一的一篇题解用了点分治。太暴力了！这很蠢（指做法）。我们有一个优美的做法。

首先 $n$ 为奇数时，答案一定为 $1$。

证明：设答案点集为 $T$，则 $T$ 显然一定为一个连通块。考虑从 $T$ 中一个点 $x$ 移动到 $y$ 时，$S$ 中有些点对答案距离贡献增加，有些减少。只有这两者相等时答案不变。但是 $n$ 为奇数，不可能取等，所以 $|T|=1$。

类似地，我们发现当 $n$ 为偶数时，$T$ 中的点组成一条链。因为只有这样，从上述 $x$ 移动到 $y$ 时总贡献不变。

考虑拎出这条链的两个端点 $x,y$，那么要求就转化成，以这条链为根时，以 $x,y$ 为根的子树大小 $siz_x,siz_y\ge \frac{|S|}{2}$，并且这条链要尽可能长。

如果我们没有这个抽象的 $siz$ 的限制，那这个答案就是树的直径长度。但是有，怎么办呢。

发挥想象力，我们把每个点一开始看作独立的。每次发现有一个叶子 $x$ 不满足 $siz$ 的限制，我们就把他删掉。同时，将 $siz_{fa_x}\to siz_{fa_x}+siz_x$，也就是把 $x$ 并入 $fa_x$。动态维护。这样每次只会剩下可能被选作直径端点的点。使用拓扑排序实现。

于是变成了一个要求支持删点，查询直径长度的问题。删点难难难，但是这些修改和查询显然可以离线，进行一个时光的倒流，加点好好好。变成支持加点，查询直径长度。维护原来的直径两端点 $(x,y)$，加入 $u$，于是根据经典结论，直径一定是 $(x,y),(x,u),(y,u)$ 其一。于是每次查询树上两点距离即可。

做完了，时间复杂度 $O(n\log n)$。使用树剖求 LCA 跑的飞快，现在（24.7.15）是最优解并遥遥领先哈哈哈哈哈哈。

code：

```cpp
int n,m,ans[N],deg[N];
bool vis[N];
int dep[N],fa[N],siz[N],son[N];
int cur,dfn[N],top[N];
priority_queue<pii> q;
vector<pii> g[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs1(int u,int f){
	siz[u]=1;
	fa[u]=f,dep[u]=dep[f]+1;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int t){
	top[u]=t,dfn[u]=++cur;
	if(!son[u]){
		return;
	}
	dfs2(son[u],t);
	go(i,u){
		int v=e[i].to;
		if(v==fa[u]||v==son[u]){
			continue;
		}
		dfs2(v,v);
	}
}
il int getLca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v);
		}
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
il int getDis(int u,int v){
	return dep[u]+dep[v]-2*dep[getLca(u,v)];
}
void Yorushika(){
	read(n);
	rep(i,1,n-1){
		int u,v;read(u,v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	dfs1(1,0),dfs2(1,1);
	rep(i,1,n){
		siz[i]=1;
		if(deg[i]<=1){
			q.emplace(-1,i);
		}
	}
	rep(j,1,n/2+1){
		while(q.size()&&-q.top().fi<j){
			int u=q.top().se;
			q.pop();
			vis[u]=1;
			go(i,u){
				int v=e[i].to;
				if(vis[v]){
					continue;
				}
				g[j].eb(u,v);
				siz[v]+=siz[u];
				if(--deg[v]==1){
					q.emplace(-siz[v],v);
				}
			}
		}
	}
	int x,y,len=1;
	x=y=q.top().se;
	drep(i,n/2+1,1){
		ans[i]=len;
		while(g[i].size()){
			auto [u,v]=g[i].back();
			g[i].pop_back();
			int A=getDis(x,y),B=getDis(x,u),C=getDis(y,u);
			if(B>A&&B>C){
				y=u;
			}else if(C>A){
				x=u;
			}
			len=max({A,B,C})+1;
		}
	}
	rep(i,1,n){
		if(i&1){
			puts("1");
		}else{
			printf("%d\n",ans[i/2]);
		}
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

怎么就和出题人电波对上了。但是感觉可能只有 *2400 左右？

---

## 作者：lzqy_ (赞：1)

考场上点分治写假了一个地方，遗憾离场。

------

考虑若集合 $S$ 固定怎么做。

如果树是一条链，根据小学奥数的知识，若 $|S| \bmod 2=1$，最小化距离总和的点即为中心点，否则为两个中心点间的任意点（包括端点）。

考虑这个结论的证明。若将点左移一步，则左侧的点代价全部加 $-1$，右侧点代价全部 $+1$，所以在中心处最优。

根据证明，发现可以将该结论扩展到树上，而“中心点”的定义改为删掉该点后的，剩余两个连通块中关键点个数之差 $\le 1$。

容易发现当 $|S|\bmod 2=1$ 时，中心点只有一个，否则有两个，证明类似于重心个数的证明。

也就是说，若 $|S|\bmod 2=1$，则价值为 $1$，否则价值为两个中心点间的路经长。

-------

观察到价值一定是一条路径，所以考虑点分治计算每条路径的贡献。

对于路径 $u,v$，若可以对 $|S|=k$ 产生贡献，那么有 $sz_u \ge k,sz_v\ge k$（注意当 $u,v$ 有祖先关系时，要去除掉另一个节点所在的子树大小）。用BIT维护后缀 $\max$ ，打个差分即可。

时间复杂度 $O(n\log^2 n)$，还是比较套路的。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=200010;
const int inf=1<<30;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
il void chkmax(int &x,int y){if(y>x)x=y;}
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
bool vis[maxn];
int rt,n;
int sz[maxn],maxp[maxn];
int siz[maxn],c[maxn];
void getrt(int fa,int x,int tot){
	sz[x]=1,maxp[x]=0;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa&&!vis[e[i].v]){
			getrt(x,e[i].v,tot),sz[x]+=sz[e[i].v];
			chkmax(maxp[x],sz[e[i].v]);
		}
	chkmax(maxp[x],tot-sz[x]);
	if(!rt||maxp[x]<maxp[rt]) rt=x;
}
void init(int fa,int x){
	siz[x]=1;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa&&!vis[e[i].v]) 
			init(x,e[i].v),siz[x]+=siz[e[i].v];
}
int Tree[maxn];
il void A(int k,int x){
	k=n-k+1;
	for(;k>0&&k<=n;k+=k&-k) chkmax(Tree[k],x);
}
il int Q(int k){
	k=n-k+1;int Mx=-inf;
	for(;k>0;k-=k&-k) chkmax(Mx,Tree[k]);
	return Mx;
}
il void cl(int k){
	k=n-k+1;
	for(;k>0&&k<=n;k+=k&-k) Tree[k]=-inf;
}
void calc1(int fa,int x,int s,int D=2){
	chkmax(c[siz[x]],Q(siz[x])+D-1);
	chkmax(c[min(siz[x],s)],D);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa&&!vis[e[i].v])
		 	calc1(x,e[i].v,s,D+1);
}
void calc2(int fa,int x,int D=2){
	A(siz[x],D);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa&&!vis[e[i].v])
			calc2(x,e[i].v,D+1);
}
void clear(int fa,int x){
	cl(siz[x]);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa&&!vis[e[i].v])
			clear(x,e[i].v);
}
int st[maxn],top;
il void Solve(int x){
	init(0,x),top=0;
//	printf("!!!%d(%d)\n",x,siz[x]);
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]){
			calc1(x,e[i].v,siz[x]-siz[e[i].v]);
			calc2(x,e[i].v),st[++top]=e[i].v;
		}
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]) clear(x,e[i].v);
	for(int i=top;i;i--){
		calc1(x,st[i],siz[x]-siz[st[i]]);
		calc2(x,st[i]);
	}
	for(int i=top;i;i--) clear(x,st[i]);
}
void dfs(int x){
	Solve(x),vis[x]=1;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v])
			rt=0,getrt(x,e[i].v,sz[e[i].v]),dfs(rt);
}
int main(){
//	freopen("island.in","r",stdin);
//	freopen("island.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	for(int i=1;i<=n;i++) 
		Tree[i]=-inf,c[i]=1;
	rt=0,getrt(0,1,n),dfs(rt);
	for(int i=n;i;i--) chkmax(c[i],c[i+1]);
	for(int i=1;i<=n;i++)
		printf("%d\n",(i&1)?1:c[i>>1]);
	return 0;
}
/*
5
1 2
2 3
4 2
3 5

7
1 2
2 3
3 4
4 5
2 6
3 7

*/

```

---

