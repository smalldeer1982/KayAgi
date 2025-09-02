# Split the Tree

## 题目描述

给定一棵有 $n$ 个结点的有根树，根为编号为 $1$ 的结点。第 $i$ 个结点上有一个数 $w_i$。请将这棵树划分为尽可能少的“竖直路径”，使得每条路径包含的结点数不超过 $L$，且每条路径上所有 $w_i$ 的和不超过 $S$。每个结点必须且只能属于一条路径。

一条“竖直路径”定义为一组结点 $v_1, v_2, \ldots, v_k$，其中 $v_i$（$i \ge 2$）是 $v_{i-1}$ 的父结点。

## 说明/提示

在第一个样例中，树被划分为 $\{1\},\ \{2\},\ \{3\}$。

在第二个样例中，树可以划分为 $\{1,\ 2\},\ \{3\}$ 或 $\{1,\ 3\},\ \{2\}$。

在第三个样例中，无法划分该树。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1 3
1 2 3
1 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3 6
1 2 3
1 1
```

### 输出

```
2```

## 样例 #3

### 输入

```
1 1 10000
10001
```

### 输出

```
-1```

# 题解

## 作者：EternalAlexander (赞：8)

对每个点预处理出它在不超过S和L的限制的情况下最多能够向上伸展几个点，记为$len[i]$,可以用倍增在$O(nlogn)$的时间内完成。

考虑dp，$dp[i]$表示第i个点的子树用最少的路径覆盖的情况下第i个点最多能向上伸展的点数,ans[i]表示此时第i个点的子树所需的路径覆盖数。

那么$dp[i]=max(dp[j])-1,ans[i]=\sum ans[j](fa[j]=i)$,特别地，如果dp[i]=-1,那么$dp[i]=len[i],ans[i]+=1$

答案是$ans[1]$

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define maxn 100005
int anc[100005][20],depth[100005]={0}, fa[maxn],head[maxn]={0}, tail=0, vis[maxn]={0};
int len[100005], dp[100005], ans[100005];
int n, l; long long s;
long long depth2[100005]={0};
long long val[100005];
struct edge {
    int v, next;
}edges[maxn*2];
inline void add_edge(int u, int v) {
    edges[++tail].v=v;
    edges[tail].next=head[u];
    head[u]=tail;
}
int cmp(int a, int b) {return depth[a]>depth[b];}
void dfs(int u, int f) {
    depth2[u]=depth2[f]+val[u];
    depth[u]=depth[f]+1; anc[u][0]=f;
    for (int i=1;(1<<i)<=depth[u];i++) {
        anc[u][i]=anc[anc[u][i-1]][i-1];
    }
    for (int i=head[u];i;i=edges[i].next) {
        if (edges[i].v!=f) {
            dfs(edges[i].v, u);
        }
    } fa[u]=f;
}

int dfs2(int u) {
    dp[u]=-1; ans[u]=0;int flag=0;
    for (int i=head[u];i;i=edges[i].next) {
        flag=1;
        if (edges[i].v!=fa[u]) {
            dfs2(edges[i].v);
            ans[u]+=ans[edges[i].v];
            dp[u]=std::max(dp[u], dp[edges[i].v]-1);
        }
    }if (flag==0) {dp[u]=len[u]-1; ans[u]=1; return 0;}
    if (dp[u]==-1) {
        dp[u]=len[u]-1;
        ans[u]++;
    }
    return 0;
}
    

int main() {
    std::cin >> n >> l >> s;
    if (l==0) {
        printf("-1"); return 0;
    }
    for (int i=1;i<=n;++i) {
        std::cin >> val[i];
        if (val[i]>s) {printf("-1"); return 0;}
    }
    for (int i=2;i<=n;++i) {
        int u; scanf("%d", &u);
        add_edge(i, u); add_edge(u, i);
    }dfs(1, 0);
    for (int i=1;i<=n;++i) {
        int u=i;
        for (int j=20;j>=0;--j) {
            if (anc[u][j]!=0&&depth2[i]-depth2[fa[anc[u][j]]]<=s&&depth[i]-depth[fa[anc[u][j]]]<=l) 
                u=anc[u][j];
        } //printf("%d->%d\n", i, u);
        len[i]=depth[i]-depth[u]+1;
        //printf("%d ", len[i]);
    }dfs2(1);
    printf("%d", ans[1]);/*
    for (int i=1;i<=n;++i) {
        printf("%d %d\n", ans[i], dp[i]);
    }*/
    return 0;
}
```

---

## 作者：一只绝帆 (赞：3)

这是对第一篇题解的补充。

看到这题就想到了 P5021 \[NOIP2018 提高组\] 赛道修建。

于是考虑每个点为链顶的 dp，每次传一条路径上去，但是你突然发现你不会转移了。

你不知道该传 $L$ 小的还是 $S$ 小的，你可能需要传一个凸包上去，然后复杂度爆炸。

所以需要考虑一个新的 dp 方案，你发现 $L$ 和 $S$ 在一条路径上的单调性是绑定的，也就是说每条路径只能向上延伸到一个最大限度。

所以你可以先用数据结构求出每个点为链底的最大长度 $len_x$，然后考虑每个点为链底的 dp，转移时贪心转移，能从子树接上来就接上来最短的，否则就只能新开一条。

具体的状态与第一篇题解相似，$f_x$ 表示最优情况下 $x$ 还能向上延伸多长，$ans_x$ 表示仅考虑 $x$ 子树时的答案。

转移如下：

$$(f_x,ans_x)=\left\{\begin{aligned}&\left(\max\{f_v\}-1,\sum_{fa_v=x}ans_v\right)&&\max\{f_v\}-1>0\\ &\left(len_x,1+\sum_{fa_v=x}ans_v\right)&&\max\{f_v\}-1\le0\end{aligned}\right.$$

求 $len_x$ 可以简单倍增。

注意点权倍增的写法，你考虑在最开始把限制减去 $w_x$，然后倍增数组中记录父亲的点权，这样做是为了与父亲倍增数组对应起来。

Code：
```cpp
// Problem: CF1059E Split the Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1059E
// Memory Limit: 250 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define G(i,x) for(int i(start[x]);i;i=Next[i])
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define UF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
using namespace std;typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
ll read() {
	ll s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=1e5+5,M=N<<1;
int n,l,v[M],fa[N],f[N][21],len[N],cnt,w[N],ans[N],F[N],start[N],Next[N];
ll s,g[N][21];
void add(int x,int y) {v[++cnt]=y;Next[cnt]=start[x];start[x]=cnt;}
void dp(int x) {
	G(i,x) dp(v[i]),F[x]=max(F[x],F[v[i]]-1),ans[x]+=ans[v[i]];
	if(!F[x]) F[x]=len[x],ans[x]++;
}
int main() {
	n=read();l=read()-1;/*l-1 edges*/s=read();
	F(i,1,n) w[i]=read(),w[i]>s&&(puts("-1"),exit(0),1);
	F(i,2,n) add(f[i][0]=read(),i);
	F(i,1,n) g[i][0]=w[f[i][0]];
	F(j,1,20) F(i,1,n) f[i][j]=f[f[i][j-1]][j-1],g[i][j]=g[i][j-1]+g[f[i][j-1]][j-1];
	F(i,1,n) {
		ll x=i,vs=s-w[x],vl=l;
		UF(j,20,0) if(f[x][j]&&(1<<j)<=vl&&g[x][j]<=vs) vl-=1<<j,vs-=g[x][j],x=f[x][j];
		len[i]=l-vl+1;
	} dp(1);cout<<ans[1];
	return 0;
}
```

---

## 作者：intel_core (赞：1)

从叶节点向上考虑，每个叶节点一定是一条路径的端点，然后把这条路径能覆盖的点都覆盖掉。

然后把被覆盖过的点删掉，在剩下的一棵树中接着操作上述过程，直到整棵树被删空为止。

这是一个显然的贪心，使用树形 $\text{DP}$ 的写法可以做到 $O(n \log n)$ （覆盖写法貌似无法处理根节点被删掉的情况）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
#define int long long
int n,len,lim,a[NR];
int fa[NR][20],sum[NR][20],lg[NR],depth[NR];
int f[NR],dp[NR],ans[NR];
vector<int>g[NR];
#define pb push_back

void dfs(int id,int fath){
	depth[id]=depth[fath]+1;
	fa[id][0]=fath;sum[id][0]=a[id];
	for(int i=1;i<=lg[depth[id]];i++)
		fa[id][i]=fa[fa[id][i-1]][i-1],sum[id][i]=sum[id][i-1]+sum[fa[id][i-1]][i-1];
	if(a[id]>lim){
		puts("-1");
		exit(0);
	}
	int now=id,cnt=lim;
	for(int k=lg[depth[id]];k>=0;k--)
		if(depth[now]>=(1<<k)&&f[id]+(1<<k)<=len&&cnt>=sum[now][k])
			f[id]+=(1<<k),cnt-=sum[now][k],now=fa[now][k];
	for(int x:g[id])
		if(x!=fath)dfs(x,id);
}
int jump(int id,int x){
	for(int k=lg[x];k>=0;k--)
		if(x>=(1<<k))x-=(1<<k),id=fa[id][k];
	return id;
}
void solve(int id,int fath){
	for(int x:g[id])
		if(x!=fath)solve(x,id),dp[id]=max(dp[id],dp[x]),ans[id]+=ans[x];
	dp[id]--;
	if(dp[id]==-1)dp[id]=f[id]-1,ans[id]++;
}

signed main(){
	cin>>n>>len>>lim;
	for(int i=1;i<=n;i++)scanf(" %lld",&a[i]),lg[i]=lg[i>>1]+1;
	for(int i=2,x;i<=n;i++)
		scanf(" %lld",&x),g[x].pb(i),g[i].pb(x);
	dfs(1,0);solve(1,0);
	cout<<ans[1]<<endl;
	return 0;
}
```

---

## 作者：Bring (赞：1)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12340976.html)

## 给出一个堆贪心解法

记点$u$的深度为$d_u(d_1=0)$，父亲为$f_u$，拥有儿子数量$es_u$。

首先找到每个点的最远延伸点（点$u$的最远延伸点记为$v_u$），借助树上倍增即可。

### 接下来是贪心方法

在每次链连接完后删掉这些点，那么每条链的尾端一定是一个叶子。

那么就想办法找出目前贪心最优的叶子，然后往上连接。

以下的贪心本蒟蒻并没有想出严格证明方法，只能感性理解一下了QAQ。

#### 贪心 1：目前$d_{v_u}$最小的叶子$u$是最优叶子

举个栗子：$n=5,f_{2..n}=[1,1,2,2],v_{1..n}=[1,1,3,1,2]$（请自行脑补这棵树）

现在的叶子有$3,4,5$。

因为$3$与其他叶子不冲突，所以直接考虑$4,5$即可。

如果选择$4$，那么最多可以延伸出$\{1,2,4\}$，剩下$\{3\},\{5\}$，一共$3$条。

如果选择$5$，那么最多只能延伸出$\{2,5\}$，剩下的$3,4$不能帮忙带走$1$，所以就$4$条了QAQ。

$\therefore$ 应该选择$d_{v_u}$最小的叶子$u$以求带走更多的点。

#### 贪心 2：对于最优叶子$u$，能往上连就往上连

因为是目前最优的叶子，没有其他叶子可以到达$v_u$，相比于让$v_u$重新开一条链，还是用$u$带走比较合算。

### 具体实现方法

构建一个存储点$u$，以$d_{v_u}$为关键字的小根堆。

使用 dfs 求出$v_u,es_u$，然后把叶子丢进堆里。

每次弹出一个点$u$，答案计数$+1$，并且往上连接，将路过的点用$vs_u$标记掉。

直到到达$v_u$或者该点已被标记，停止连接。

**Particularly,** 如果到达了$v_u$且没有被标记，那么$f_{v_u}$就失去了一个儿子，所以要处理$es_{f_{v_u}}$并判断入堆。

**Time complexity:** $O(n\log n)$

**Memory complexity:** $O(n\log n)$

具体见代码（$823$ms / $49.40$MB）

```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (100010)
int n,l,s,w[N],f[N][20],g[N][20],ans,d[N],es[N],lg[N]{-1},u,v[N];
bool vs[N];
vector<int>e[N];
struct Cmp{bool operator()(int a,int b)const{return d[v[a]]>d[v[b]];}};
priority_queue<int,vector<int>,Cmp>q;
void dfs(int u);
signed main(){
	Rd(n),Rd(l),Rd(s);
	Frn1(i,1,n)if(Rd(w[i])>s)wr(-1),exit(0);
	Frn1(i,2,n)e[Rd(*f[i])].push_back(i),lg[i]=lg[i>>1]+1;
	dfs(1);
	while(!q.empty()){
		u=q.top(),q.pop(),++ans;
		for(int p(u);!vs[p];p=*f[p]){
			vs[p]=1;
			if(p==v[u]){if(!--es[*f[v[u]]])q.push(*f[v[u]]);break;}
		}
	}
	wr(ans),exit(0);
}
void dfs(int u){
	Frn1(i,1,lg[d[u]])f[u][i]=f[f[u][i-1]][i-1],
		g[u][i]=g[u][i-1]+g[f[u][i-1]][i-1];
	int rs(s-w[v[u]=u]);
	Frn_(i,lg[d[u]],0)if(d[u]-d[v[u]]+(1<<i)<l&&g[v[u]][i]<=rs)
		rs-=g[v[u]][i],i=min(i,d[v[u]=f[v[u]][i]]);
	for(int i:e[u])*f[i]=u,*g[i]=w[u],d[i]=d[u]+1,dfs(i);
	if(!(es[u]=e[u].size()))q.push(u);
}
```


---

## 作者：大菜鸡fks (赞：1)

倍增预处理每个点最多可以向上延伸多少

贪心地填

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5;
struct edge{
	int link,next;
}e[N<<1];
int f[N],g[N],reach[N],fa[N][20],sum[N][20],w[N],n,L,S,tot,head[N];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read(); L=read(); S=read();
	for (int i=1;i<=n;i++){
		w[i]=read();
	}
	for (int i=2;i<=n;i++){
		insert(i,read());
	}
}
void dfs(int u,int Fa){
	fa[u][0]=Fa; sum[u][0]=w[u];
	for (int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1],sum[u][i]=sum[fa[u][i-1]][i-1]+sum[u][i-1];
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=Fa) dfs(v,u);
	}
}
void Dfs(int u,int Fa){
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=Fa){
			Dfs(v,u);
			f[u]=max(f[u],f[v]);
			g[u]+=g[v];
		}
	}
	if (!f[u]){
		f[u]=reach[u]-1; g[u]++;
	}else f[u]--;
}
inline void solve(){
	dfs(1,0);
	for (int i=1;i<=n;i++){
		int l=L,s=S,u=i;
		for (int j=19;j>=0;j--){
			if (l>=(1<<j)&&s>=sum[u][j]){
				s-=sum[u][j]; u=fa[u][j]; l-=(1<<j); 
			}
		}
		reach[i]=L-l;
		if (!reach[i]) {
			writeln(-1);
			return;
		}
	}
	Dfs(1,0);
	writeln(g[1]);
}
signed main(){
	init(); solve();
	return 0;
}
```

---

## 作者：djh0314 (赞：0)

[**洛谷**](https://www.luogu.com.cn/problem/CF1059E)       
[**Codeforces**](https://codeforces.com/problemset/problem/1059/E)

## 题意
将一棵 $n$ 个节点的以 1 为根的树拆成若干个链，每条链满足：    
1. 点数不超过 $L$。 
2. 点权和不超过 $S$。
3. 对于链上的某一位置 $i$（$i\ge 2$），满足 $v_i$ 是 $v_{i-1}$ 的父亲。

求最少分成几个链。特别的，倘若无解，输出 -1。


### 解决
显然的，我们是从儿子转移到父亲，问题就在于我们父亲节点的选择方式，是再起炉灶，还是承接某一个儿子，又承接哪一个儿子。

想想看，倘若我们将这个树当做一条链，我们应当如何解决。             

明显的，我们应该是在能延伸的情况下就尽量延伸，这样我们可以让我们这个新生的节点的末尾更远。

也就是说，当我们在树上时，我们只要有一个儿子能有余地转移，我们就应当承接转移。

接下来的问题在于承接哪一个儿子。

贪心的，我们选择可以延伸更远的那一个儿子的链。

对于处理延伸的长度，我们可以用树上倍增处理，维护 $fa$ 数组与 $sum$ 数组，在处理每个点时，先将自己加上，再从大到小枚举二进制位，倘若满足，立即转移。

总结一下，我们在解决这道题时，我们用倍增维护我们的延伸最远，再在儿子中寻找最远，倘若没有，就从自己再起炉灶。       
特殊的，为了判断 -1，我们需要在一开始就判断是否存在一个节点的权值大于 $S$，倘若存在，那我们的答案就是 -1。


### 核心代码。
~~~
inline void redfs(int now,int fath) {
	int u=now,tot=val[now],cnt=0;
	for(int i=19; ~i; --i) {
		if(cnt+(1<<i)+1>L) continue;
		if(tot+sum[u][i]>S) continue;
		cnt+=(1<<i);
		tot+=sum[u][i];
	}
	mx[now]=cnt;
	for(auto to:lj[now]) {
		if(to==fath) continue;
		redfs(to,now);
		sy[now]=max(sy[now],sy[to]-1);
	}
	if(sy[now]==-1) {
		++ans;
		sy[now]=mx[now];
	}
}
~~~

---

## 作者：zrzring (赞：0)

[更好的阅读体验](http://zrzring.cn/index.php/archives/225)

调了好久的题，还是自己码力太差了

首先可以想到从叶子贪心，能不切就不切，这样保证是最优的。然后考虑计算答案，因为限制有两个，不能直接树形dp，于是预处理出每个点能往上爬多少个点，这样一来就可以做到树形dp了

预处理的过程可以用倍增优化

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}
const int N = 2e5 + 10, inf = 1e9;
inline int read() {
    int sym = 0, res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
inline long long lread() {
    long long sym = 0, res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
struct EDGE {
    int u, v, nxt;
} edge[N];
int n, L, head[N], cnt, fa[N][30], son[N], depth[N], jp[N], f[N];
long long S, val[N], sum[N][30];
void add(int u, int v) {edge[++cnt] = (EDGE){u, v, head[u]}; head[u] = cnt;}
void dfs(int u, int last) {
    fa[u][0] = last; depth[u] = depth[last] + 1; sum[u][0] = val[last];
    for (int i = 1; (1 << i) <= depth[u]; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        sum[u][i] = sum[u][i - 1] + sum[fa[u][i - 1]][i - 1];
    }
    for (int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].v; son[u]++; dfs(v, u);
    }
}
void dfs(int u) {
    int mx = 0;
    for (int e = head[u]; e; e = edge[e].nxt) {
        int v = edge[e].v; dfs(v); mx = max(mx, jp[v]); f[u] += f[v];
    }
    if (!mx) f[u]++; else jp[u] = mx - 1;
}
int main() {
    n = read(); L = read(); S = lread();
    for (int i = 1; i <= n; i++) {
        val[i] = lread(); if (val[i] > S) {printf("-1"); return 0;}
    }
    for (int v = 2; v <= n; v++) {
        int u = read(); add(u, v);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        int u = i, s = val[u], l = 1;
        for (int j = 20; j >= 0; j--) {
            if (l + (1 << j) <= L && s + sum[u][j] <= S && fa[u][j]) {
                s += sum[u][j]; l += 1 << j; u = fa[u][j];
            }
        }
        jp[i] = l - 1;
    }
    dfs(1); printf("%d", f[1]);
    return 0;
}
```



---

## 作者：happybob (赞：0)

提供一个新做法。

无解的充要条件显然是存在 $w_u > s$。现在考虑有解情况。

注意到朴素 DP 是容易的，$f_u$ 表示以 $u$ 为根的子树的答案，$g_u = \sum \limits_{j \in son_u} f_j$。转移时考虑 $u$ 子树内一个点 $j$，满足 $j$ 到 $u$ 路径合法，则贡献为 $1+\sum \limits_{k \in path(u,j)} g_k - f_k$，注意此时 $g_u$ 已经计算，$f_u$ 没有计算，设为 $0$。这样的复杂度是 $O(n^3)$ 的。

考虑这个式子其实是很有前途的。直接线段树合并优化 DP，每个点子树维护线段树，每个点 $j$ 表示 $j$ 对 $u$ 的贡献，要维护全局 $\min$。

但是那两个限制好像不好维护。$dis_j$ 表示根到 $j$ 点权和。直接把 $dis_j$ 当作线段树下标，这样在 $u$ 的时候，$u$ 到 $j$ 路径和如果 $>s$，就是 $dis_j - dis_u + a_u > s$，也就是 $dis_j > s + dis_u - a_u$。相当于线段树后缀区间覆盖。

然后第二个限制是点数 $\leq l$。注意到经典结论，将同层的点按照 DFN 序排序，以 $u$ 为根子树中，$dep$ 为定值的点是连续区间。然后你就做完了。

注意懒标记下传不用新建节点。时空复杂度均为 $O(n \log n)$。

代码：

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;
const int N = 1e5 + 5;
const ll INF = 1e10;

int n, l;
ll s;
ll a[N];
int fa[N];
int dep[N];
ll dis[N], d2[N];
vector<pair<ll, int>> b;
int nd[N];
vector<int> G[N];
int dfn[N], idx, ra[N];
vector<int> verd[N];
ll f[N], g[N];
int sz[N];

int rt[N];

inline void chkmin(ll& x, ll y)
{
	x = min(x, y);
}

class SegmentTree
{
public:
	int idx;
	vector<int> rubbish;
	struct Node
	{
		int lson, rson;
		ll minn;
		bool tag;
		ll tags;
	}tr[N * 70];
	int newnode()
	{
		if (rubbish.size())
		{
			int u = rubbish.back();
			rubbish.pop_back();
			tr[u].lson = tr[u].rson = tr[u].tag = tr[u].tags = 0;
			tr[u].minn = INF;
			return u;
		}
		idx++;
		return idx;
	}
	void pushup(int u)
	{
		tr[u].minn = INF;
		if (tr[u].lson) chkmin(tr[u].minn, tr[tr[u].lson].minn);
		if (tr[u].rson) chkmin(tr[u].minn, tr[tr[u].rson].minn);
	}
	void pushtag(int u)
	{
		if (u)
		{
			tr[u].tag = 1;
			tr[u].minn = INF;
		}
	}
	void pushtag2(int u, ll v)
	{
		if (u)
		{
			tr[u].tags += v;
			tr[u].minn += v;
		}
	}
	void pushdown(int u)
	{
		if (!u) return;
		if (tr[u].tags)
		{
			pushtag2(tr[u].lson, tr[u].tags);
			pushtag2(tr[u].rson, tr[u].tags);
			tr[u].tags = 0ll;
		}
		if (tr[u].tag)
		{
			pushtag(tr[u].lson);
			pushtag(tr[u].rson);
			tr[u].tag = 0;
		}
	}
	int ins(int u, int x, ll v, int l, int r)
	{
		if (!u)
		{
			u = newnode();
			tr[u].minn = INF;
		}
		if (l == r)
		{
			tr[u].minn = min(tr[u].minn, v);
			return u;
		}
		if (tr[u].tag) return u;
		pushdown(u);
		int mid = l + r >> 1;
		if (x <= mid) tr[u].lson = ins(tr[u].lson, x, v, l, mid);
		else tr[u].rson = ins(tr[u].rson, x, v, mid + 1, r);
		pushup(u);
		return u;
	}
	void update(int u, int l, int r, int nl, int nr)
	{
		if (!u) return;
		if (nl >= l && nr <= r)
		{
			pushtag(u);
			return;
		}
		pushdown(u);
		int mid = nl + nr >> 1;
		if (l <= mid) update(tr[u].lson, l, r, nl, mid);
		if (r > mid) update(tr[u].rson, l, r, mid + 1, nr);
		pushup(u);
	}
	int merge(int p, int q, int l, int r)
	{
		if (!p) return q;
		if (!q) return p;
		pushdown(p), pushdown(q);
		if (l == r)
		{
			chkmin(tr[p].minn, tr[q].minn);
			rubbish.emplace_back(q);
			return p;
		}
		int mid = l + r >> 1;
		tr[p].lson = merge(tr[p].lson, tr[q].lson, l, mid);
		tr[p].rson = merge(tr[p].rson, tr[q].rson, mid + 1, r);
		rubbish.emplace_back(q);
		pushup(p);
		return p;
	}
}sgt;

void dfs(int u)
{
	if (!G[u].size())
	{
		f[u] = 1;
		g[u] = 0;
		rt[u] = sgt.ins(rt[u], nd[u], -f[u], 1, n);
		return;
	}
	ll minn = INF;
	for (auto& j : G[u])
	{
		dfs(j);
		g[u] += f[j];
		rt[u] = sgt.merge(rt[u], rt[j], 1, n);
	}
	minn = min(minn, g[u]);
	int ndep = dep[u] + l;
	// 点数<=l
	if (ndep <= n)
	{
		int ll = lower_bound(verd[ndep].begin(), verd[ndep].end(), dfn[u]) - verd[ndep].begin(), rr = upper_bound(verd[ndep].begin(), verd[ndep].end(), dfn[u] + sz[u] - 1) - verd[ndep].begin() - 1;
		//if (u == 5) cout << "??: " << ndep << " " << ll << " " << rr << " " << dfn[u] + sz[u] << " " << verd[ndep].size() << " " << dfn[u] << " " << verd[ndep][0] << "\n";
		if (ll <= rr)
		{
			for (int i = ll; i <= rr; i++)
			{
				int nu = ra[verd[ndep][i]];
				sgt.update(rt[u], nd[nu], nd[nu], 1, n);
			}
		}
	}
	// 和<=s
	// dis[j]-dis[u]+a[u]<=s
	// dis[j]<=dis[u]+s-a[u]
	// dis[j]>dis[u]+s-a[u]
	int pos = upper_bound(b.begin(), b.end(), make_pair(d2[u], (int)1e9)) - b.begin() + 1;
	if (pos <= n)
	{
		sgt.update(rt[u], pos, n, 1, n);
	}
	rt[u] = sgt.ins(rt[u], nd[u], 0ll, 1, n);
	if (rt[u]) minn = min(minn, sgt.tr[rt[u]].minn + g[u]);
	//if (u == 5) cout << "!!!!!!!: " << sgt.tr[rt[u]].minn + g[u] << "\n";
	f[u] = minn + 1ll;
	//cout << "!!!: " << u << " " << minn << " " << f[u] << " " << g[u] << "\n";
	sgt.pushtag2(rt[u], g[u] - f[u]);
}

signed main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("myans.txt", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> l >> s;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		if (a[i] > s)
		{
			cout << "-1\n";
			return 0;
		}
	}
	for (int i = 2; i <= n; i++)
	{
		cin >> fa[i];
		G[fa[i]].emplace_back(i);
	}
	auto dfs = [&](auto self, int u, int f)->void
		{
			dep[u] = dep[f] + 1;
			dfn[u] = ++idx;
			verd[dep[u]].emplace_back(dfn[u]);
			ra[idx] = u;
			dis[u] = dis[f] + a[u];
			d2[u] = dis[u] + s - a[u];
			b.emplace_back(make_pair(dis[u], u));
			//b.emplace_back(make_pair(d2[u], u));
			sz[u] = 1;
			for (auto& j : G[u])
			{
				self(self, j, u);
				sz[u] += sz[j];
			}
		};
	dfs(dfs, 1, 0);
	sort(b.begin(), b.end());
	for (int i = 1; i <= n; i++)
	{
		nd[i] = lower_bound(b.begin(), b.end(), make_pair(dis[i], i)) - b.begin() + 1;
		//nd2[i] = lower_bound(b.begin(), b.end(), make_pair(d2[i], i)) - b.begin() + 1;
	}
	for (int i = 1; i <= n; i++) sort(verd[i].begin(), verd[i].end());
	::dfs(1);
	if (f[1] >= (ll)1e9) f[1] = -1;
	cout << f[1] << "\n";
	return 0;
}
```

---

