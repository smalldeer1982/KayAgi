# Brain Network (hard)

## 题目描述

Breaking news from zombie neurology! It turns out that – contrary to previous beliefs – every zombie is born with a single brain, and only later it evolves into a complicated brain structure. In fact, whenever a zombie consumes a brain, a new brain appears in its nervous system and gets immediately connected to one of the already existing brains using a single brain connector. Researchers are now interested in monitoring the brain latency of a zombie. Your task is to write a program which, given a history of evolution of a zombie's nervous system, computes its brain latency at every stage.

## 样例 #1

### 输入

```
6
1
2
2
1
5
```

### 输出

```
1 2 2 3 4 ```

# 题解

## 作者：AK_400 (赞：1)

注意到每次只加一个点，设原先直径的两个端点为 $p1,p2$，新加入的点为 $v$，$(x,y)$ 表示端点为 $x,y$ 的链，那么新直径只有可能是 $(p1,p2),(p1,v),(p2,v)$ 中的一条。

于是变成了动态查链的长度，lct 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int fa[200005],ch[200005][2],lz[200005],sz[200005];
void pu(int x){
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
void tr(int x){
    swap(ch[x][0],ch[x][1]);
    lz[x]^=1;
}
void pd(int x){
    if(!lz[x])return;
    if(ch[x][0])tr(ch[x][0]);
    if(ch[x][1])tr(ch[x][1]);
    lz[x]=0;
    return;
}
bool get(int x){
    return x==ch[fa[x]][1];
}
bool nr(int x){
    return x==ch[fa[x]][1]||x==ch[fa[x]][0];
}
void rot(int x){
    int y=fa[x],z=fa[y],c=get(x);
    if(nr(y))ch[z][get(y)]=x;
    fa[x]=z;
    ch[y][c]=ch[x][!c];
    if(ch[x][!c])fa[ch[x][!c]]=y;
    ch[x][!c]=y;
    fa[y]=x;
    pu(y);
    pu(x);
}
void upd(int x){
    if(nr(x))upd(fa[x]);
    pd(x);
}
void splay(int x){
    upd(x);
    for(int f=fa[x];nr(x);rot(x),f=fa[x])
        if(nr(f))rot(get(x)==get(f)?f:x);
}
void acs(int x){
    for(int p=0;x;p=x,x=fa[p]){
        splay(x),ch[x][1]=p,pu(x);
    }
}
void mkr(int x){
    acs(x),splay(x),tr(x);
}
void split(int x,int y){
    mkr(x),acs(y),splay(y);
}
int fr(int x){
    acs(x),splay(x),pd(x);
    while(ch[x][0])x=ch[x][0],pd(x);
    return splay(x),x;
}
void link(int x,int y){
    mkr(x);
    if(fr(y)!=x)fa[x]=y;    
}
void slv(){
    cin>>n;
    int p1=1,p2=1,len=0;
    for(int i=2;i<=n;i++){
        int p;
        cin>>p;
        link(i,p);
        split(p1,i);
        int len1=sz[i]-1;
        split(p2,i);
        int len2=sz[i]-1;
        if(max({len,len1,len2})==len1)len=len1,p2=i;
        else if(max({len,len1,len2})==len2)len=len2,p1=i;
        cout<<len<<endl;
    }
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：JWRuixi (赞：1)

~~为什么 Easy，Medium，hard 完全不一样啊！！~~

- 题意

初始有一颗有一个点的树，每次加入一条边，求直径，共 $n-1$ 次加边。

- 分析

首先注意到一个性质，每次是在一个叶子上新挂一个点，直径最多加 $1$。设 $S,T$ 为当前直径的两个端点，考虑如果新加入的点挂在 $S$ 或 $T$ 下面，端点直接向下移，直径加 $1$。

其次可以注意到一个性质，不管往哪里加点，$S,T$ 最多只有一个点移动，也就是说只需要对比 $\operatorname{dis}(u,T),\operatorname{dis}(u,S)$ 和当前直径即可，所以问题转化为动态维护两点距离，用树剖的话肯定不行，但是考虑到倍增只能从上往下转移，所以动态倍增就行了，连图都不用建！

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int n, dep[maxn], f[maxn][24], S, T, d;

int lca (int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 23; ~i; i--) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
	if (u == v) return u;
	for (int i = 23; ~i; i--) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

inline int dis (int u, int v) {
	return dep[u] + dep[v] - (dep[lca(u, v)] << 1);
}

int main () {
	n = read();
	S = T = 1, d = 0;
	for (int u = 2; u <= n; u++) {
		int fa = read();
		dep[u] = dep[fa] + 1, f[u][0] = fa;
		for (int i = 1; (1 << i) <= dep[u]; i++) f[u][i] = f[f[u][i - 1]][i - 1];
		if (fa == S) S = u, d++;
		else if (fa == T) T = u, d++;
		else {
			int dis1 = dis(u, T), dis2 = dis(u, S);
			if (dis1 > d) d = dis1, S = u;
			if (dis2 > d) d = dis2, T = u;
		}
		write(d), puts("");
	}
}
// I love WHQ!
```

---

## 作者：Crazyouth (赞：0)

## 分析

设我们某次操作新加的点为 $u$，其被加到了 $p$ 上，其加入之前的直径端点为 $a,b$，路径 $a,b$ 上距离 $u$ 最近的点为 $k$。

结论：$u$ 加入后直径为 $(a,b)$，$(u,a)$，$(u,b)$ 中一条。

证明：考虑反证。若不为，设新直径为 $(c,d)$，进行分类讨论。

- 若 $c,d$ 都不为 $u$，则有 $\operatorname{dist}(c,d)>\operatorname{dist}(a,b)$，与 $(a,b)$ 为原直径矛盾。

- 若 $c,d$ 中有一点为 $u$，不妨令 $d=u$。再对 $c$ 进行分类讨论：

1. 若路径 $(a,b)$ 与 $(c,u)$ 无交点，或 $c$ 在 $(a,b)$ 上，不难发现 $\operatorname{dist}(u,a)>\operatorname{dist}(u,c)$，与 $(u,c)$ 为直径矛盾。
2. 若路径 $(a,b)$ 与 $(c,u)$ 有交点，且 $c$ 不在 $(a,b)$ 上。不妨令 $\operatorname{dist}(c,a)>\operatorname{dist}(c,b)。$由于 $u$ 加入之前 $(a,b)$ 为直径，那么有 $\operatorname{dist}(p,c)\le \operatorname{dist}(p,a)$（因为与某个点最远的点必定是直径的端点之一）。在 $u$ 加入后，由上式，有 $\operatorname{dist}(u,c)=\operatorname{dist}(p,c)+1\le \operatorname{dist}(p,a)+1=\operatorname{dist}(u,a)$，则 $(u,a)$ 可以为直径，矛盾。

综上，新直径只能是 $(a,b)$，$(u,a)$，$(u,b)$ 中一条。

在有了这个结论后，我们发现只需要求出两点之间的距离即可，转为求两点之间最近公共祖先，那么由于我们要支持加点，可以使用倍增法，这样甚至不需要建图。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int fa[N][20],dep[N];
inline int lca(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=18;~i;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;
	for(int i=18;~i;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
inline int dist(int u,int v)
{
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	int x;
	cin>>x;
	int a=1,b=2;
	for(int i=0;i<=18;i++) fa[1][i]=fa[2][i]=1;
	dep[1]=0;
	dep[2]=1;
	cout<<"1 ";
	for(int i=3;i<=n;i++)
	{
		int p;
		cin>>p;
		fa[i][0]=p;
		dep[i]=dep[p]+1;
		for(int j=1;j<=18;j++) fa[i][j]=fa[fa[i][j-1]][j-1];
		if(dist(i,a)>dist(a,b)) b=i;
		else if(dist(i,b)>dist(a,b)) a=i;
		cout<<dist(a,b)<<' ';
	}
}

---

## 作者：SJH__qwq (赞：0)

动态 lca 板子。因为 lca 是从上往下计算，所以随便钦定一个 $1$ 号点为树根，那么每一次插入 $x$ 点的时候，因为 $x$ 点一定是一个叶子，所以直接倍增暴力更新答案即可。查询可以维护随便一条直径然后判断添加这个点之后答案是否更优秀，这个可以直接树上差分。

时间复杂度为 $O(n\log n)$。

---

## 作者：xzggzh1 (赞：0)

题意：

这个问题就是给出一个不断加边的树，保证每一次加边之后都只有一个连通块（每一次连的点都是之前出现过的），问每一次加边之后树的直径。

---

考虑先离线，这样方便LCA预处理出所有点之间的距离。

然后每次加入一个点，我们可以轻易证明一个结论：

每次加入点后，一定能够找到一条新的直径和加入这个点之前的一条直径存在公共点。

所以我们记录每一个状态下的直径的端点 $u,v$ ，然后每一次加点判断这个点和 $u,v$ 的路径长度是否比原来的直径长，若长则更新直径。

核心代码：

```cpp

bool update(int u, int v, int &k) {
	int a = lca(u, v);
	int d = dep[u] + dep[v] - 2 * dep[a];
	if (d > k) {
		k = d;
		return true;
	}
	return false;
}
int a[N];
int main() {
	int n;
	scanf("%d", &n);
	int u = 1, v = 1, cur = 0;
	init();
	for (int i = 2; i <= n; i++) {
		scanf("%d", a + i);
		addEdge(a[i], i);
	}
	dfs(1, -1, 0);
	calc(n);
	for (int i = 2; i <= n; i++) {
		int nv = v;
		//当前的直径的端点：u，v 
		if (update(u, i, cur)) nv = i;
		if (update(v, i, cur)) {
			u = v;
			nv = i;
		}
		v = nv;
		printf("%d ", cur);
	}
}

```

---

