# [ABC285G] Tatami

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc285/tasks/abc285_g

縦 $ H $ マス、横 $ W $ マスのグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と呼びます。

このグリッドを縦 $ 1 $ マス $ \times $ 横 $ 1 $ マスのタイルと縦 $ 1 $ マス $ \times $ 横 $ 2 $ マスのタイルで、重ならないように、隙間ができないように覆います（タイルは回転してもよい）。

各マスには `1`, `2`, `?` のいずれかが書かれています。マス $ (i,j) $ に書かれている文字は $ c_{i,j} $ です。  
`1` が書かれたマスは $ 1\times\ 1 $ のタイルで、`2` が書かれたマスは $ 1\times\ 2 $ のタイルで覆わなければなりません。`?` が書かれたマスはどちらのタイルで覆っても構いません。

そのようなタイルの置き方があるかどうか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 300 $
- $ H,W $ は整数
- $ c_{i,j} $ は `1`, `2`, `?` のいずれか

### Sample Explanation 1

例えば以下のようなタイルの置き方で条件を満たすことができます。 !\[\](https://img.atcoder.jp/abc285/d984ec33355bac05ecebc41076d9a8df.png)

### Sample Explanation 2

条件を満たすようなタイルの置き方は存在しません。

## 样例 #1

### 输入

```
3 4
2221
?1??
2?21```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 4
2?21
??1?
2?21```

### 输出

```
No```

## 样例 #3

### 输入

```
5 5
11111
11111
11211
11111
11111```

### 输出

```
No```

# 题解

## 作者：Reunite (赞：5)

随手秒了，然后一遍过，然后看一眼题解区，咋全是神秘二分图匹配或者是上下界啊，只需要普通最大流就行。

### 一
---

首先，$1$ 类格子没有任何用处，我们也不需要考虑任何 $1\times 1$ 的骨牌，只需要考虑是否能用 $1\times 2$ 的骨牌合法地覆盖完所有的 $2$ 类格子，剩下的用 $1\times 1$ 的随便填。

$2$ 类格子要想被覆盖，只能是一个骨牌覆盖两个 $2$ 类格子，或者是覆盖一个 $2$ 类格子，一个无限制格子，而我们希望每个 $2$ 类格子都能被覆盖，因此直接拆点。每个 $2$ 类格子，其左部点向其四联通的 $2$ 类格子或者无限制格子的右部点连一条容量为 $1$ 的边，表示一个骨牌覆盖两个，源点向所有 $2$ 类格子左部点连边，所有 $2$ 类格子和无限制格子的右部点向汇点连边，容量均为 $1$。

说明一下这样建的正确性，首先必要性：不满流一定无解，这个显然；对于充分性，唯一可能有问题的地方是，在若干个格子之间连的边，流量发生了错位，即流量流出了一个 $A\rightarrow B'$，但是 $B$ 并没有流向 $A'$ 而是流向了 $C'$，等等，也就是错位了，并没有达到直观上的一个骨牌覆盖了 $A,B$。但实际上这个确实没有问题，如果有 $A\rightarrow B'$，我们假设就在新的网格图上连上 $(A,B)$ 这条边，因为流量守恒，所有点的度数都 $\le 2$，所以这个图会形成若干链和环，所有出边都是由 $2$ 类格子连出，所有无限制点都没有出边，首先看链。

需要明白的是，这样的链一定是以一个 $2$ 类格子开始，一直到一个无限制格子结束，假设链长为 $len$，若 $2\mid len$，则就按照这个链的顺序放 $1\times2$ 的就行，否则的话看似放不了了，但我们知道最后一个一定是无限制的！所以在奇数的情况下可以直接丢掉最后的那个无限制格子，于是又可以放了。

对于环，这个错位的情况会形成若干个置换环，一个重要的地方是，所有的边都建立在四联通的情况下的，这样，任意一个置换环大小一定为偶数，而网格四联通图上任意一个偶环进行 $1\times 2$ 的覆盖，随便怎么覆盖都有解。因此，我们证明了这样连边的正确充要性。

---
### 二

其实上面的证明是我在写题解的时候发现问题，并加以证明解决的，我写的时候好像没在意会出现错位产生置换环的问题。

点数 $O(nm)$，边数 $O(nm)$，复杂度 $O(X)$，反正 AT 的模板快。

这样严谨又简单的题解和做法不支持一下吗？

```cpp
#include <cstdio>
#include <atcoder/maxflow>
#define ad g.add_edge
#define id(x,y) (x-1)*m+y
using namespace std;

int n,m;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
char c[305][305];

int main(){
    scanf("%d%d",&n,&m);
    atcoder::mf_graph <int> g(2*n*m+3);
    for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
    int S=2*n*m+1,T=S+1,cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]!='1') ad(n*m+id(i,j),T,1);
            if(c[i][j]!='2') continue;
            ad(S,id(i,j),1);
            cnt++;
            for(int k:{0,1,2,3}){
                int x=i+dx[k],y=j+dy[k];
                if(!x||!y||x>n||y>m) continue;
                if(c[x][y]!='1') ad(id(i,j),n*m+id(x,y),1);
            }
        }
    }
    puts(g.flow(S,T)==cnt?"Yes":"No");

    return 0;
}
```

---

## 作者：igAC (赞：4)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc285_g)

[AT link](https://atcoder.jp/contests/abc285/tasks/abc285_g)

简要题意（摘自洛谷翻译）：

请用若干个 $1 \times 1$ 和 $1 \times 2$ 的瓷砖（可以旋转）不重叠地完全覆盖 $H \times W$ 的长方形网格。第 $i$ 行第 $j$ 列的网格有字符 $c_{i,j}$，含义如下：

- `1`：该网格只能用 $1 \times 1$ 的瓷砖覆盖。
- `2`：该网格只能用 $1 \times 2$ 的瓷砖覆盖。
- `?`：该网格无特殊限制。

如果存在方案可以满足上述条件，输出 `Yes`，否则输出 `No`。

# $\text{Solution}$

挺板的一道网络流吧。。。

我们将每个点拆为入点和出点。

入点指从这个点开始覆盖，出点指覆盖到这个点结束。

- 对于方格为 ``1`` 的点，只能用 $1 \times 1$ 的瓷砖覆盖，于是入点连向出点。

- 对于方格为 ``2`` 的点，只能用 $1 \times 2$ 的瓷砖覆盖，于是我们枚举上下左右四个方向的点，看看是否能作为出点进行覆盖。

- 对于方格为 ``?`` 的点，无限制，于是就包含了以上两种情况。

用此方法建图，跑 max_flow，跑出来的答案就是最多能覆盖的网格。

判断最多能覆盖的网格数量是否等于总数量即可。

网络流点数：$2 \times n \times m$。

边数（有向边）：$4nm + 2nm + 8nm = 14nm$。

若整个网格都为 ``?`` 的话，最坏边数是可以取到的。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 180005
#define M 1260005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,s,t;
int dis[N];
bool vis[N],Vis[N];
int head[N],tot=1;
char a[305][305];
struct Edge{
	int to,nxt;
	int val;
}e[M];
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
void add_edge(int x,int y,int z){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	e[tot].val=z;
	head[x]=tot;
	e[++tot].to=x;
	e[tot].nxt=head[y];
	e[tot].val=0;
	head[y]=tot;
}
bool SPFA(){
	for(int i=0;i<=t;++i) dis[i]=INF;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	dis[s]=0,vis[s]=true,q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(e[i].val && dis[y]>dis[x]+1){
				dis[y]=dis[x]+1;
				if(!vis[y]){
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	return dis[t]!=INF;
}
int dfs(int x,int sum){
	if(x==t) return sum;
	int res=0;
	Vis[x]=true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(!Vis[y] && e[i].val && dis[y]==dis[x]+1){
			int k=dfs(y,min(sum,e[i].val));
			if(!k) dis[y]=INF;
			res+=k,sum-=k;
			e[i].val-=k,e[i^1].val+=k;
			if(!sum) break;
		}
	}
	Vis[x]=false;
	return res;
}
int Dinic(){
	int flow=0;
	while(SPFA()){
		int k=dfs(s,INF);
		flow+=k;
		if(!k) break;
	}
	return flow;
}
int pos(int i,int j,int d){return (i-1)*m+j+d*n*m;}
bool check(int i,int j){return (1<=i && i<=n && 1<=j && j<=m && (a[i][j]=='2' || a[i][j]=='?'));}
int main(){
	n=read(),m=read(),s=0,t=2*n*m+1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			add_edge(s,pos(i,j,0),1);
			add_edge(pos(i,j,1),t,1);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(a[i][j]=='1' || a[i][j]=='?') add_edge(pos(i,j,0),pos(i,j,1),1);
			if(a[i][j]=='2' || a[i][j]=='?'){
				for(int k=0;k<4;++k){
					int nx=i+dx[k];
					int ny=j+dy[k];
					if(check(nx,ny)) add_edge(pos(i,j,0),pos(nx,ny,1),1);
				}
			}
		}
	}
	puts(Dinic()==n*m?"Yes":"No");
	return 0;
}
```

[Atcoder AC 记录](https://atcoder.jp/contests/abc285/submissions/42298647) [洛谷 AC 记录](https://www.luogu.com.cn/record/112813632)

---

## 作者：DaiRuiChen007 (赞：3)

# ABC285G 题解



## 思路分析

用 $1\times 2$ 骨牌覆盖网格图立刻想到黑白染色建立二分图，对于已经被 $1\times 1$ 覆盖的方格先删除，我们只需要为所有 $c_{i,j}=2$ 的位置找到匹配即可，剩下的位置用 $1\times 1$ 填补。

正解好像是网络流，这里只提供一种乱搞做法：

对于每个 $c_{i,j}=2$ 的没有匹配的点，直接在二分图上暴力搜出增广路，如果搜不出来增广路则输出 `No`。

时间复杂度 $\Theta(h^2w^2)$。

注意到实际上很难卡满时间复杂度，因此注意一下实现的常数（例如用时间戳标记 `vis[]` 数组避免过多的 `memset` 操作）即可通过本题。

upd：原本的代码被 hack 了，原因是正常的二分图匹配算法搜增广路只会考虑长度为奇数的增广路，而本题可以添加一条长度为偶数且以 `?` 结尾的增广路，即让最后一个 `?` 变为不匹配的状态。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=305,MAXV=1e5+5;
vector <int> G[MAXV];
int tar[MAXV],vis[MAXV];
char val[MAXV];
inline bool dfs(int x,int t) {
	if(vis[x]==t) return false;
	vis[x]=t;
	if(val[x]=='?') return tar[x]=-1,true;
	for(int p:G[x]) if(vis[p]<t) {
		vis[p]=t;
		if(tar[p]==-1||dfs(tar[p],t)) return tar[p]=x,tar[x]=p,true;
	}
	return false;
}
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char a[MAXN][MAXN];
int id[MAXN][MAXN]; 
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%s",a[i]+1);
	for(int i=1,cnt=0;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			id[i][j]=++cnt,val[cnt]=a[i][j];
		}
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		if(a[i][j]=='1'||(i+j)%2==0) continue;
		for(int k:{0,1,2,3}) {
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>m||a[x][y]=='1') continue;
			G[id[i][j]].push_back(id[x][y]);
			G[id[x][y]].push_back(id[i][j]);
		}
	}
	memset(tar,-1,sizeof(tar));
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j){
		if(a[i][j]=='2'&&tar[id[i][j]]==-1) {
			if(!dfs(id[i][j],id[i][j])) {
				puts("No"); 
				return 0;
			}
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：SkyRainWind (赞：2)

[A-G题解](https://www.cnblogs.com/SkyRainWind/p/17060088.html)

考虑了一下普通的图论做法好像没法做，想到网络流。

注意网格图是个天然的二分图（只有 $i+j$ 奇偶性不同的点才能连边）。

$(i,j)$ 能向 $(i,j+1)$ 或 $(i+1,j)$ 连边 当且仅当 两个点都没有 1。

显然我们只需要关心所有的 2 是否有地方放，这就是一个匹配问题！

因为我们要求所有的 2 必须匹配，因此可以考虑将 $(S,i)$ 或者 $(i,T)$（$i$ 为这个点）的容量下限设为 1，然后对于所有的边的容量上限均设为 1 ，跑上下界可行流。

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 2e5+5;

int n,m;
struct ed{
	LL from,to,cap,flow,rev;
	ed(){}
	ed(LL from,LL to,LL cap,LL flow,LL rev):from(from),to(to),cap(cap),flow(flow),rev(rev){}
};
vector<ed>g[maxn];

struct netflow{
	int cur[maxn]; 
	int d[maxn], q[maxn], hd, tl;
	int in[maxn], out[maxn];
	int s, t;	// 源 汇 
	
	netflow(){s=t=-1;}
	
	void clear(){
		s = t = -1;
		for(int i=1;i<=n+m+10;i++)g[i].clear(), in[i] = out[i] = 0;
	}
	
	void init(int s0,int t0){
		s = s0, t = t0;
	}

	void add(int x,int y,LL v){
		g[x].push_back(ed(x,y,v,0,g[y].size()));
		g[y].push_back(ed(y,x,0,0,g[x].size() - 1));
	}
	
	void adde(int x,int y,int l,int r){	// x->y [l,r]
		add(x, y, r-l);
		out[x] += l; in[y] += l;
	}
	
	int bfs(){
		memset(d,0, sizeof d);
		hd = tl = 0;
		q[tl ++] = s;
		d[s] = 1;
		while(hd != tl){
			int now = q[hd ++];
			for(int i = 0;i<g[now].size();i++){
				ed &e = g[now][i];
				if(!d[e.to] && e.cap > e.flow)d[e.to] = d[now] + 1, q[tl ++] = e.to;
			}
		}
		return d[t];
	}
	
	LL dfs(int now,LL rem){	// rem 当前流量 
		if(now == t || !rem)return rem;
		LL flow = 0;
		for(int &i = cur[now]; i < g[now].size();i ++){
			ed &e = g[now][i];
				// 分层图 & 残量不为0 
			if(d[e.to] == d[now] + 1 && e.cap > e.flow){
				LL f = dfs(e.to, min(rem, e.cap - e.flow));
				rem -= f, flow += f, e.flow += f, g[e.to][e.rev].flow -= f;
			}
			if(!rem)break;
		}
		if(rem)d[now] = -1;
		return flow;
	}
	
	LL dinic(){
		assert(s!=-1);
		LL flow = 0;
		while(bfs()){
			memset(cur, 0, sizeof cur);
			flow += dfs(s, 1ll << 62);
		}
		return flow;
	}
	
	LL pflow(int S0, int T0, int S, int T, int point){	// possible flow
		// S0 T0 源点汇点 ST 超源超汇 point 有多少点 
		LL lim = 0;
		for(int i=1;i<=point;i++){
			int cur = in[i] - out[i];
			if(in[i] == out[i] && in[i] == 0)continue;
			if(cur > 0)add(S, i, cur), lim += cur;
			else add(i, T, -cur);
		}
		add(T0, S0, inf);
		init(S, T);
		LL res = dinic();
		if(res < lim)return -1;
		init(S0, T0);
		return dinic();
	}
}nf;
int S0, T0, S, T;
int h,w;
char s[305][305];

int ind(int x,int y){return (x-1) * w + y;}
int rnd(int x,int y){
	if(s[x][y] == '2')return 1;
	return 0;
}
signed main(){
	scanf("%d%d",&h,&w);
	S0 = h*w+1, T0 = h*w+2, S = h*w+3, T = h*w+4;
	for(int i=1;i<=h;i++)scanf("%s",s[i] + 1);
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)if(s[i][j] != '1'){
			if((i+j) & 1){
				int le = rnd(i, j);
				nf.adde(ind(i, j), T0, le, 1);
			}else{
				int le = rnd(i, j);
				nf.adde(S0, ind(i, j), le, 1);
			}
		}
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)if(s[i][j] != '1'){
			if(i+1<=h && s[i+1][j] != '1'){
				int x1 = ind(i,j),x2 = ind(i+1,j);
				if((i+j)&1)swap(x1, x2); 
				nf.adde(x1, x2, 0, 1);
			}
			if(j+1<=w && s[i][j+1] != '1'){
				int x1 = ind(i,j), x2 = ind(i, j+1);
				if((i+j)&1)swap(x1, x2);
				nf.adde(x1, x2, 0, 1);
			}
		}
	ll res = nf.pflow(S0, T0, S, T, h*w+2);
	puts(~res ? "Yes" : "No");

	return 0;
}
```

---

## 作者：0x3F (赞：1)

注意到只需要对网格图进行二分图匹配，$1$ 类型的点视为障碍，要求所有 $2$ 类型的点都有匹配。

我们可以将二分图两侧 $?$ 类型的点之间全部连起来，然后补点使得二分图两侧点数相等，补的点向另一侧所有 $?$ 类型的点连边，然后直接判完美匹配即可。

但是“$?$ 类型的点两两连边”使得边数可能是 $\mathcal{O}(V^2)=\mathcal{O}(n^4)$ 的。处理方法是在网络流中建虚点，将边数减少为 $\mathcal{O}(n^2)$。

然后直接跑 Dinic 即可。

时间复杂度为 $\mathcal{O}(E\sqrt{V})=\mathcal{O}(n^3)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 310;
const int __ = 1e5 + 10;
const int ___ = 1e6 + 10;
int n, m, N, S, T, id[_][_], col[_][_], e = 1, hd[__], cr[__], dis[__], nx[___], to[___], ln[___], Q[__], L, R, cntl, cntr, rest, flow;
inline void r_add(int u, int v, int w) {
    e++;
    nx[e] = hd[u];
    to[e] = v;
    ln[e] = w;
    hd[u] = e;
}
inline void add(int u, int v, int w) {
    r_add(u, v, w);
    r_add(v, u, 0);
}
inline bool bfs(void) {
    for (int i = 1; i <= N; i++) {
        cr[i] = hd[i];
        dis[i] = 0;
    }
    dis[S] = 1;
    L = R = 1;
    Q[1] = S;
    while (L <= R) {
        int u = Q[L++];
        for (int i = hd[u]; i; i = nx[i]) {
            if (ln[i]) {
                int v = to[i];
                if (!dis[v]) {
                    dis[v] = dis[u] + 1;
                    Q[++R] = v;
                }
            }
        }
    }
    return dis[T];
}
int dfs(int u, int flow) {
    if (u == T) return flow;
    int ans = 0;
    for (int i = cr[u]; i; i = nx[i]) {
        cr[u] = i;
        if (ln[i]) {
            int v = to[i];
            if (dis[v] == dis[u] + 1) {
                int tmp = dfs(v, min(flow, ln[i]));
                flow -= tmp;
                ans += tmp;
                ln[i] -= tmp;
                ln[i^1] += tmp;
                if (!flow) break;
            }
        }
    }
    if (!ans) dis[u] = 0;
    return ans;
}
int main() {
    S = 1;
    T = 2;
    N = 2;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= m; j++) {
            switch (str[j-1]) {
                case '?': {
                    col[i][j] = 0;
                    break;
                }
                case '1': {
                    col[i][j] = 1;
                    break;
                }
                case '2': {
                    col[i][j] = 2;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (col[i][j] != 1) {
                N++;
                id[i][j] = N;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (col[i][j] != 1) {
                if ((i ^ j) & 1) {
                    cntl++;
                    add(S, id[i][j], 1);
                } else {
                    cntr++;
                    add(id[i][j], T, 1);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            if (col[i][j] != 1 && col[i][j+1] != 1) {
                if (col[i][j] == 2 || col[i][j+1] == 2) {
                    if ((i ^ j) & 1) {
                        add(id[i][j], id[i][j+1], 1);
                    } else {
                        add(id[i][j+1], id[i][j], 1);
                    }
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (col[i][j] != 1 && col[i+1][j] != 1) {
                if (col[i][j] == 2 || col[i+1][j] == 2) {
                    if ((i ^ j) & 1) {
                        add(id[i][j], id[i+1][j], 1);
                    } else {
                        add(id[i+1][j], id[i][j], 1);
                    }
                }
            }
        }
    }
    int VP = ++N;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (col[i][j] == 0) {
                if ((i ^ j) & 1) {
                    add(id[i][j], VP, 1);
                } else {
                    add(VP, id[i][j], 1);
                }
            }
        }
    }
    if (cntl < cntr) {
        int VPL = ++N;
        add(S, VPL, cntr - cntl);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (col[i][j] == 0) {
                    if (!((i ^ j) & 1)) {
                        add(VPL, id[i][j], 1);
                    }
                }
            }
        }
    } else if (cntl > cntr) {
        int VPR = ++N;
        add(VPR, T, cntl - cntr);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (col[i][j] == 0) {
                    if ((i ^ j) & 1) {
                        add(id[i][j], VPR, 1);
                    }
                }
            }
        }
    }
    rest = max(cntl, cntr);
    while (bfs()) {
        flow += dfs(S, 19260817);
    }
    if (flow == rest) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：1)

## [ABC285 G-Tatami](https://atcoder.jp/contests/abc285/tasks/abc285_g)

题意：$n\times m$ 的矩阵，使用 $1\times 1$ 或者 $1\times 2$ 的小矩形填满。$1\le n,m\le 300$

已知一些点被 $1\times 1$ 或者 $1\times 2$ 的小矩形覆盖了。求使用这两种矩形填满矩阵的可行性。

分析：其实就是要求所有标记 $2$ 数字的位置能够匹配到相邻四联通的矩形。

于是我们黑白染色这张图，然后所有起点连接所有白点，所有黑点连接终点，所有流量都是 $1$。

然后对于左侧的白点，如果右侧有相邻且可行的黑点，那么就连接一条边到黑点，流量为 $1$。

判断可行性就判断残量网络：每个标记 $2$ 的节点左端或者右端有 $1$ 的流即可。

但是，该做法在考场上 WA 了 $11$ 个点，所以需要证伪或者改进。

---

这个做法为什么是错的呢？因为在这张二分图上面最大流跑出来往往不是完美匹配，而最大流不能保证经过所有的标记 $2$ 的节点，它只能保证最大流，如果经过标记 $2$ 节点时候占用了一些节点使得无法跑满最大流，它就会毫不犹豫地放弃标记 $2$ 节点，但是实际上可以牺牲最大流而满足所有 $2$ 的条件。

那么我们强制限定标记 $2$ 节点到 $T$ 或者从 $S$ 到它的所有边的最小流量为 $1$，最大流量也为 $1$；其他边的最小流量为 $0$，最大流量为 $1$ 即可。即可使用上下界有源汇可行流解决问题。

---

有源汇通常转成无源汇可行流，即从 $T$ 向 $S$ 连接一条上限流量为无穷大、下限流量为 $0$ 的边即可。

假设每条边的上限流量是 $u(i,j)$，下限流量为 $d(i,j)$，我们需要给每条边定一个流量 $f(i,j)$，使得流量平衡且在限制内。

那么不妨考虑每条边已经流了 $d(i,j)$ 的流量，所以只能多流 $u(i,j)-d(i,j)$ 的流量。

设一个节点 $x$ 初始入流流量减去初始出流流量的流量差 $W$。

如果 $W=0$，就什么也无需修改。

如果 $W<0$，说明出流量过大。为了维护图的正确性，需要把 $x$ 连接一个附加的汇点 $T'$，流量为 $-W$。这样的意义是为了提高 $x$ 的入流量：从 $x$ 走到 $T'$ 显然比绕别的弯路要容易，所以在满足条件的情况之下，跑最大流的时候就一定会给入流流量提高 $-W$，换而言之，让 $x$ 流正确的流不是它缺什么就给什么，而是提高对它的要求。

如果 $W>0$，说明入流量过大。为了维护图的正确性，需要把新建的源点 $S'$ 连接 $x$，流量为 $W$。这样的意义就是为了扩大 $x$ 的出流量：证明同理。

于是我们对于 $S'$ 到 $T'$ 跑最大流，枚举 $S'$ 的所有出边，观察到如果这几条边都不能跑满，那么就是失败；对于 $T'$ 也是同理。为什么连没有跑满就算失败呢？因为它连基础的源汇点赋予它的使命——流量平衡都无法满足，只能退而求其次，这种图，怎么能说它是可行的呢？

---

本题之中，需要改变一些建图方式。

只有 $S$ 到所有白点的边才有可能有下界 $d$，所以枚举标记为 $2$ 的白点，$W$ 值就是 $1$，所以 $S'$ 向它连接一条容量为 $1$ 的边；

只有所有黑点到 $T$ 的边才有可能有下界 $d$，所以枚举标记为 $2$ 的黑点，$W$ 值是 $-1$，所以它向 $T'$ 连接一条容量为 $1$ 的边；

其他边的连接状况和流量状况都不变。

最后连接 $T$ 和 $S$ 容量为无穷大，$T$ 的 $W$ 值为所有标记为 $2$ 的黑点数量（设之为 $sum2$），那么连接 $S'$ 和 $T$ 点，容量为 $sum2$。

对于 $S$ 点的 $W$ 值就是所有标记为 $2$ 的白点数量的相反数（设之为 $sum1$，且 $sum2-sum1=$矩阵中 $2$ 的个数），容量为 $-sum1$。

对 $S'$ 到 $T'$ 跑最大流，然后对于 $S'$ 流出的、$T'$ 流入的，看看有没有流满。

时间复杂度是 $O((HW)^{1.5})$，可以通过。

---

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#include<atcoder/maxflow>
using namespace std;typedef int I;const I inf=1073741824;typedef long long LL;I FL,CH;template<typename T>bool in(T&a){for(FL=1;!isdigit(CH)&&CH!=EOF;CH=getchar())if(CH=='-')FL=-1;for(a=0;isdigit(CH);CH=getchar())a=a*10+CH-'0';return a*=FL,CH==EOF?0:1;}template<typename T,typename...Args>I in(T&a,Args&...args){return in(a)+in(args...);}
const I N=1e5+10,M=1e7+10;
I n,m,id;
I s,t;
const I dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
I r,c,cntb,cntw,s0,t0;
I g(I x,I y){
	return (x-1)*c+y;}
I a[301][301];
#define cconn G.add_edge
int main(){
	in(r,c);
	for(I i=1;i<=r;++i){
		for(I j=1;j<=c;++j){
			while(!isgraph(CH))CH=getchar();
			a[i][j]=CH;CH=getchar();}}
	s0=r*c+1;t0=r*c+2;s=r*c+3;t=n=r*c+4;
	atcoder::mf_graph<I>G(n+1);
	for(I i=1;i<=r;++i)
		for(I j=1;j<=c;++j){
			if((i+j)&1)continue;
			if(a[i][j]=='1')continue; 
			for(I k=0,x,y;k<=3;++k){
				x=i+dx[k];
				y=j+dy[k];
				if(x<1||x>r||y<1||y>c)continue;
				if(a[x][y]=='1')continue;
				cconn(g(i,j),g(x,y),1);
			}
		}
	for(I i=1;i<=r;++i)for(I j=1;j<=c;++j){
		if(a[i][j]=='2'){
			if((i+j)&1)cconn(g(i,j),t,1),++cntb;
			else cconn(s,g(i,j),1),++cntw;
		}else if(a[i][j]=='?'){
			if((i+j)&1)cconn(g(i,j),t0,1);
			else cconn(s0,g(i,j),1);
		}}
	cconn(s,t0,cntb);
	//调一下 bug 
	cconn(s0,t,cntw);
	cconn(t0,s0,inf);
	I res=G.flow(s,t);
	if(res!=cntb+cntw)return puts("No"),0;
	puts("Yes"); 
	return 0;
}
```

做这道题的时候还是很艰辛的，先是改了两个 bug ，然后发现 TLE 了，于是改成了题解的构造，发现 WA 了，于是改回了原来的构造，苦思冥想，估计是我自己 dinic 常数的问题，于是改成了 ATcoder Library 的网络流，最终 AC 了。

~~人傻常数大实锤了。~~

---

## 作者：Crane_w (赞：1)

# ABC 285 G - Tatami

## Solution 网络流

网格图是一个天然二分图， 可以按 横纵坐标之和 的奇偶性将相邻两格分属于左部和右部。

记 `?` 或 $2$ 的格子为待匹配点， 记横纵坐标之和为奇数的为奇待匹配点， 即 $(i + j)$ 为 $odd$。

将匹配点向相邻匹配点连边，建 $S$ 和 $T$ 超级源汇， 将 $S$ 与奇待匹配点连边， 偶待匹配点与 $T$ 连边。

容量皆为 $1$，跑一边最大流，最后检查与 $S$, $T$ 相连的 $2$ 边是否都为零即可。

可惜的是，这种思路只能过赛时数据，被 after-contest hack 掉了， 这里提供一组数据：

Input

```
4 4
11?1
?222
1211
1?11
```

Output

```
Yes
```

可以看出， 最大流有多种情况，$2$ 与 $2$ 的方格不一定能连边。

所以只能跑一遍有源汇上下界可行流了。

[关于上下界可行流可以看这篇Blog](https://zhuanlan.zhihu.com/p/324507636)。

```cpp
#include <bits/stdc++.h>
#define for_(i,a,b) for (ll i = (a); i < (b); i++)
#define rep_(i,a,b) for (ll i = (a); i <= (b); i++)
#define fi first 
#define se second
#define sz(a) a.size()
using namespace std;
const int maxn = 1e6 + 10, mod = 1e9 + 7;// mod = 1949777;
const double EPS = 1e-3;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
int n, m; 
char c[505][505];
int inf = 1 << 29;
int id[505][505];
int dx[5] = {0, 0, 1, -1};
int dy[5] = {1, -1, 0, 0}; 
int d[maxn]; 
int tot = 1, maxflow;
int nxt[maxn], head[maxn], v[maxn], e[maxn], tag[maxn];
int now[maxn];// 当前弧优化
int Vin[maxn], Vout[maxn];
void add(int x, int y, int c) {
    v[++tot] = y, e[tot] = c, nxt[tot] = head[x]; head[x] = tot;
    v[++tot] = x, e[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}
int s, t;
bool bfs(){
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s);
    d[s] = 1; now[s] = head[s];
    while(q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i]) {
            if (e[i] && !d[v[i]]) {
                d[v[i]] = d[x] + 1;
                now[v[i]] = head[v[i]];
                q.push(v[i]);
                if (v[i] == t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int x, int flow){
    if (x == t) return flow;
    int res = flow, k;
    for (int i = now[x]; i && res; i = nxt[i]) {
        now[x] = i;
        if (e[i] && d[v[i]] == d[x] + 1) {
            k = dinic(v[i], min(res, e[i]));
            if (!k) d[v[i]] = 0;
            e[i] -= k;
            e[i^1] += k;
            res -= k;
        }
    }
    return flow - res;
}
int cnt = 0;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> c[i][j];
            id[i][j] = ++cnt; // 标号 预处理比较方便... 
        }
    }
    s = 0, t = n * m + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[i][j] == '1') continue;
            if ((i + j) & 1) { // 奇带匹配点 
                if (c[i][j] == '2') {
                    add(s, id[i][j], 0); // 连一条upper减去lower的边 此处上界为1， 下界为1 ， 1 - 1 = 0 
                    // 也可以不连， 此处写出是为了清楚 
                    Vin[id[i][j]]++; // 处于维护流量平衡, 需要记录每个点的流入量&流出量 
                    Vout[s]++;  
                } else add(s, id[i][j], 1);
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx >= 1 && ny >= 1 && nx <= n && ny <= m) {
                        add(id[i][j], id[nx][ny], 1); //带匹配点连边 
                    }
                }
            } else {
                if (c[i][j] == '2') { //同上 
                    Vin[t]++;
                    Vout[id[i][j]]++;
                    add(id[i][j], t, 0);
                } else add(id[i][j], t, 1);
            }
        }
    }
    add(t, s, 1e9); // 原图的汇向源连一条inf边，以下皆是上下界可行流的常规操作。 
    s = n * m + 2, t = n * m + 3; // 新建源汇 
    for (int i = 0; i <= n * m + 1; i++) {
        if (Vin[i] > Vout[i]) {
            add(s, i, Vin[i] - Vout[i]);
        } else if (Vin[i] < Vout[i]){
            add(i, t, Vout[i] - Vin[i]);
        }
    }
    int flow, maxflow = 0;
    // 在差网络上跑最大流 
    while(bfs()) {
        while(flow = dinic(s, inf)) maxflow += flow;
    }
    int ok = 1;
    for (int i = head[s]; i; i = nxt[i]) {
        if (e[i]) ok = 0; //判断有无解 
    }
    if (ok) cout << "Yes" << endl;
    else cout << "No" <<endl;
     return 0; 
} 


```

## Solution 二分图最大匹配

原先的最大流思路真的不行吗?

如果我们跳出网络流是个天然二分图这个思路， 重新建图，另辟蹊径，即是柳暗花明。

我们知道，原先的想法只是卡在达到最大匹配数但是不是所有的 $2$ 都被匹配。我们是不是可以交换一些 `?` 与 $2$ 的匹配， 转而变成 $2$ 与 $2$ 的匹配，我看到洛谷上有大神已经怎么写的了，他是不断寻找增广路，使得每一个 $2$ 都尽可能被匹配，在此 %%%。

也可以重新建图，求出最大匹配， 然后看匹配数是否等于 $2$ 的个数即可。



```cpp
#include <bits/stdc++.h>
#define for_(i,a,b) for (ll i = (a); i < (b); i++)
#define rep_(i,a,b) for (ll i = (a); i <= (b); i++)
#define fi first 
#define se second
#define sz(a) a.size()
#define int long long
#define pb push_back
#define CE cout << endl;
#define CO cout << "OK" << endl;
using namespace std;
const int maxn = 2e6 + 10, mod = 1e9 + 7;// mod = 1949777;
const double EPS = 1e-3;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
int n, m; 
char c[505][505];
int inf = 1 << 29;
int id[505][505];
int dx[5] = {0, 0, 1, -1};
int dy[5] = {1, -1, 0, 0}; 
int d[maxn]; 
int tot = 1, maxflow;
int nxt[maxn], head[maxn], v[maxn], e[maxn], tag[maxn];
int now[maxn];// 当前弧优化
int Vin[maxn], Vout[maxn];
void add(int x, int y, int c) {
    v[++tot] = y, e[tot] = c, nxt[tot] = head[x]; head[x] = tot;
    v[++tot] = x, e[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}
int s, t;
bool bfs(){
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s);
    d[s] = 1; now[s] = head[s];
    while(q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i]) {
            if (e[i] && !d[v[i]]) {
                d[v[i]] = d[x] + 1;
                now[v[i]] = head[v[i]];
                q.push(v[i]);
                if (v[i] == t) return 1;
            }
        }
    }
    return 0;
}
int dinic(int x, int flow){
    if (x == t) return flow;
    int res = flow, k;
    for (int i = now[x]; i && res; i = nxt[i]) {
        now[x] = i;
        if (e[i] && d[v[i]] == d[x] + 1) {
            k = dinic(v[i], min(res, e[i]));
            if (!k) d[v[i]] = 0;
            e[i] -= k;
            e[i^1] += k;
            res -= k;
        }
    }
    return flow - res;
}
int cnt = 0;
signed main() { 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>> n >> m;
    int K = 0;
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> c[i][j];
            if (c[i][j] == '2') K++;
            id[i][j] = ++cnt;
        }
    }
    s = 0, t = 3 * n * m + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (c[i][j] == '1') continue;
            if (c[i][j] == '2') {
                add(s, id[i][j], 1);
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx >= 1 && ny >= 1 && nx <= n && ny <= m) {
                        if (c[nx][ny] != '1') add(id[i][j], id[nx][ny] + n * m, 1);
                    }
                }
            }
            add(id[i][j] + n * m, t, 1);
        }
    }
    int flow, maxflow = 0;
    while(bfs()) {
        while(flow = dinic(s, inf)) maxflow += flow;
    }
    if (maxflow == K) cout << "Yes" << endl;
    else cout << "No" <<endl;
     return 0; 
} 

```


---

## 作者：lfxxx (赞：0)

讲一种上下界可行流的思路。

首先问题简化成只用 $1 \times 2$ 的矩形覆盖所有 $c_{i,j} = 2$ 的点，剩下的用 $1 \times 1$ 的矩形一定可以覆盖。并且由于 $1 \times 2$ 的矩形一定覆盖两个相邻的格子，所以可以对网格黑白染色。

然后按以下方案连边：

# 白点

假若一定要被覆盖，那么 $add(s,pos_{i,j},1,1)$。

假若可以被覆盖，那么 $add(s,pos_{i,j},0,1)$。

以上两种点皆向相邻且可以覆盖的黑点连下届为 $0$ 上界为 $1$ 的边。

# 黑点

假若一定要被覆盖，那么 $add(pos_{i,j},t,1,1)$。

假若可以被覆盖，那么 $add(pos_{i,j},t,0,1)$。

那么最后判断可行流是否存在即可。

由于建出来的图是一张二分图，所以复杂度为 $O(H^{1.5} \times W^{1.5})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 114;
const int inf = 1e9 + 114;
namespace ChiFAN {
struct edge {
    int to, next, w;
} e[N << 1];
int n, m, S, T, sum, tot = 1, maxflow, d[N], in[N], cur[N], head[N];
void add(int x, int y, int z) {
    e[++tot] = (edge) {y, head[x], z}, head[x] = tot;
    e[++tot] = (edge) {x, head[y], 0}, head[y] = tot;
}
bool bfs() {
    memset(d, 0, sizeof(d)), d[S] = 1;
    queue <int> q;
    q.push(S);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int i = head[x]; i; i = e[i].next)
            if (e[i].w && !d[e[i].to]) {
                q.push(e[i].to);
                d[e[i].to] = d[x] + 1;

                if (e[i].to == T)
                    return 1;
            }
    }

    return 0;
}
int dinic(int x, int flow) {
    if (x == T)
        return flow;

    int k, res = 0;

    for (int i = cur[x]; i && flow; i = e[i].next) {
        cur[x] = i;
        int y = e[i].to;

        if (e[i].w && d[y] == d[x] + 1) {
            k = dinic(y, min(flow, e[i].w));

            if (!k)
                d[y] = 0;

            e[i].w -= k, e[i ^ 1].w += k;
            res += k, flow -= k;
        }
    }

    return res;
}

void add_ULFlow(int x, int y, int l, int r) {
    add(x, y, r - l);
    in[x] -= l, in[y] += l;
}

bool work(int n, int s, int t) {
    S = 0, T = n + 1;
    
	add_ULFlow(t, s, 0, inf);
	
    for (int i = 1; i <= n; ++i)
        if (in[i] > 0)
            add(S, i, in[i]), sum += in[i];
        else
            add(i, T, -in[i]);

    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        maxflow += dinic(S, inf);
    }

    return sum == maxflow;
}
};
char c[400][400];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int n,m;
int pos[400][400],cnt,s,t;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	s=++cnt,t=++cnt;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			pos[i][j]=++cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i+j)%2==0){
				if(c[i][j]=='2'){
					ChiFAN::add_ULFlow(s,pos[i][j],1,1);
				}
				if(c[i][j]=='?'){
					ChiFAN::add_ULFlow(s,pos[i][j],0,1);
				}
				if(c[i][j]=='2'||c[i][j]=='?'){
					for(int k=0;k<4;k++){
						int nx=i+dx[k],ny=j+dy[k];
						if(c[nx][ny]=='2'||c[nx][ny]=='?') ChiFAN::add_ULFlow(pos[i][j],pos[nx][ny],0,1);
					}
				}
			}
			else{
				if(c[i][j]=='2'){
					ChiFAN::add_ULFlow(pos[i][j],t,1,1);
				}
				if(c[i][j]=='?'){
					ChiFAN::add_ULFlow(pos[i][j],t,0,1);
				}
			}
		}
	}
	cout<<(ChiFAN::work(cnt,s,t)==true?"Yes\n":"No\n");
}
```


---

## 作者：cwfxlh (赞：0)

# [AT_abc285_g](https://www.luogu.com.cn/problem/AT_abc285_g)    
网络流经典题。      

对于这种覆盖直接乱搞一个建模：     

把每个格子拆一个入点出点，源点向入点连一条容量为 $1$ 的边，出点向汇点连一条容量为 $1$ 的边。对于为 $1$ 的点，从其入点向出点连一条容量为 $1$ 的边，对于为 $2$ 的点，考察其四联通中可以用 $1\times 2$ 覆盖的格子，从当前点的入点向另一个点的出点连容量为 $1$ 的边。最后跑一遍最大流，如果流量到达 $n\times m$，则合法，否则非法。     

说一下含义和正确性，每一份流量都意味着一个格子是否被覆盖，某一个点的入点进来的流量，他所对应的出边意味着他在哪里被覆盖结束。首先，很明显一个格子无法被覆盖两次，因为其流量是 $1$，并且，明显的，任意方案的覆盖都是可以在图上实现的。最后，图上每一种流的方案都可以对应一种覆盖，值为 $1$ 的覆盖是明显可实现的，唯一的问题在于，如果某个格子选择了与另外一个格子覆盖 $1\times 2$，但是另一个格子选择了 $1\times 1$，不过这样是可以直接改个路径就可以了，所以流的方案完全对应匹配的方案。于是正确性就得到保证了。    

另外这题需要当前弧。   

代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,ans,k1,k2,k3,k4,k5,k6,k7,k8,k9;
string s[503];
int head[200003],cur[200003],fx[7][2]={{-1,0},{0,1},{1,0},{0,-1}};
struct Edge{
	int ed;
	int v;
	int nxt;
}E[4000003];
int totE=1;
void addEdge(int st,int ed,int v){
	E[++totE].ed=ed;
	E[totE].v=v;
	E[totE].nxt=head[st];
	head[st]=totE;
	return;
}
int hs(int X,int Y){
	return (X-1)*w+Y;
}
int cs[500003];
queue<int>q;
bool bfs(){
	for(int i=1;i<=2*h*w+10;i++)cs[i]=-1;
	cs[2*h*w+1]=1;
	q.push(2*h*w+1);
	while(!q.empty()){
		k1=q.front();
		q.pop();
		for(int i=head[k1];i;i=E[i].nxt){
			if(E[i].v<=0)continue;
			if(cs[E[i].ed]!=-1)continue;
			cs[E[i].ed]=cs[k1]+1;
			q.push(E[i].ed);
		}
	}
	return (cs[2*h*w+2]!=-1);
}
int dfs(int now,int fl){
	if(now==2*h*w+2||fl==0)return fl;
	int rem=fl,uu;
	for(int i=cur[now];i;i=E[i].nxt){
		if(E[i].v<=0)continue;
		if(cs[now]+1!=cs[E[i].ed])continue;
		uu=dfs(E[i].ed,min(rem,E[i].v));
		E[i].v-=uu;
		E[i^1].v+=uu;
		cur[now]=i;
		rem-=uu;
		if(rem==0)return fl;
	}
	return fl-rem;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>h>>w;
	for(int i=1;i<=h;i++)cin>>s[i];
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			addEdge(2*h*w+1,hs(i,j),1);
			addEdge(hs(i,j),2*h*w+1,0);
			addEdge(hs(i,j)+h*w,2*h*w+2,1);
			addEdge(2*h*w+2,hs(i,j)+h*w,0);
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(s[i][j-1]=='?'||s[i][j-1]=='1'){
				addEdge(hs(i,j),hs(i,j)+h*w,1);
				addEdge(hs(i,j)+h*w,hs(i,j),0);
			}
			if(s[i][j-1]=='?'||s[i][j-1]=='2'){
				for(int u=0;u<=3;u++){
					if(i+fx[u][0]<1||i+fx[u][0]>h||j+fx[u][1]<1||j+fx[u][1]>w)continue;
					if(s[i+fx[u][0]][j+fx[u][1]-1]=='1')continue;
					addEdge(hs(i,j),hs(i+fx[u][0],j+fx[u][1])+h*w,1);
					addEdge(hs(i+fx[u][0],j+fx[u][1])+h*w,hs(i,j),0);
				} 
			}
		}
	}
	while(bfs()){
		for(int i=1;i<=2*h*w+2;i++)cur[i]=head[i];
		ans+=dfs(2*h*w+1,214748364);
	}
	if(ans>=h*w)puts("Yes");
	else puts("No");
	return 0;
}
```


---

## 作者：escapist404 (赞：0)

### Statement

请用若干个 $1 \times 1$ 和 $1 \times 2$ 的瓷砖（可以旋转）不重叠地完全覆盖 $H \times W$ 的长方形网格。第 $i$ 行第 $j$ 列的网格有字符 $c_{i,j}$，含义如下：

- `1`：该网格只能用 $1 \times 1$ 的瓷砖覆盖。
- `2`：该网格只能用 $1 \times 2$ 的瓷砖覆盖。
- `?`：该网格无特殊限制。

如果存在方案可以满足上述条件，输出 `Yes`，否则输出 `No`。

$1 \leq H,W \leq 300$。

### Solution

每个格子只能被覆盖一次，考虑拆点网络流。

#### Conclusion

* 设源点 $S$，汇点 $T$。从 $S$ 向入点连边，从出点向 $T$ 连边。
* 如果某个方格上是 $1$，将它代表的点的入点向出点连边。
* 如果是 $2$，从其入点向它四连通的 $2$ 或 $?$ 方格的出点连边。
* 如果是 $?$，当作其为 $1$ 和 $2$ 处理。
* 所连的边容量均为 $1$。

求解最大流 $f$，若 $f = nm$ 则有解；反之无解。

#### Proof

对于 $1$ 类方格（方格上写着 $1$，下同），求解最大流时必然有 $1$ 的贡献。

对于一条由 $2$ 类方格组成的链，长度为 $n$，显然地，求解最大流必然有 $\lfloor\frac{n}{2}\rfloor$ 的贡献。

观察到如果不是链，总可以将叶子位置的方格换到别的叶子后面去，从而转化成一条链的情况。

### Code

```cpp
#include <bits/stdc++.h>

struct Edge {
	int to, nxt, cap, flow;
	Edge() = default;
	Edge(int to, int nxt, int cap, int flow) : to(to), nxt(nxt), cap(cap), flow(flow) {}
};

class Graph {
public:
	int n, m;
	std::vector<Edge> ed;
	std::vector<int> head;
	int cnt;
	void add_edge(int u, int v) { ed[++cnt].to = v, ed[cnt].nxt = head[u], head[u] = cnt; }
	Graph(int n, int m) : n(n), m(m), ed(m), head(n + 1, -1), cnt(-1) {}
};

class NetworkFlow : public Graph {
private:
	const int INF = 0x3f3f3f3f;
	std::vector<int> dep;

	bool bfs(int s, int t) {
		std::queue<int> q;
		while (q.size()) q.pop();
		dep.assign(n + 1, 0);
		dep[s] = 1;
		q.push(s);
		while (q.size()) {
			int x = q.front();
			q.pop();
			for (int i = head[x]; ~i; i = ed[i].nxt) {
				if ((!dep[ed[i].to]) && (ed[i].cap > ed[i].flow)) {
					dep[ed[i].to] = dep[x] + 1;
					q.push(ed[i].to);
				}
			}
		}
		return dep[t] > 0;
	}

	int dfs(const int x, const int t, int flow) {
		if (x == t || (!flow)) return flow;
		int ret = 0;
		for (int& i = cur[x]; ~i; i = ed[i].nxt) {
			int d;
			if ((dep[ed[i].to] == dep[x] + 1) &&
				(d = dfs(ed[i].to, t, std::min(flow - ret, ed[i].cap - ed[i].flow)))) {
				ret += d;
				ed[i].flow += d;
				ed[i ^ 1].flow -= d;
				if (ret == flow) return ret;
			}
		}
		return ret;
	}

public:
	int s, t;
	std::vector<int> cur;

	NetworkFlow(int n, int m) : Graph(n + 3, m), dep(n + 3), s(n + 1), t(n + 2), cur(n + 3) {}

	void add_edge(int u, int v, int w) {
		ed[++cnt].to = v, ed[cnt].nxt = head[u], head[u] = cnt;
		ed[cnt].cap = w, ed[cnt].flow = 0;
	}

	int dinic() {
		int max_flow = 0;
		while (bfs(s, t)) {
			cur = head;
			max_flow += dfs(s, t, INF);
		}
		return max_flow;
	}
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	NetworkFlow G(n * m * 2, n * m * 14);
	std::vector<std::vector<int>> a(n + 2, std::vector<int>(m + 2));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char x;
			std::cin >> x;
			if (x == '?')
				a[i][j] = 0;
			else if (x == '1')
				a[i][j] = 1;
			else
				a[i][j] = 2;
		}
	}

	auto valid = [&a, n, m](int x, int y) {
		return x >= 1 && x <= n && y >= 1 && y <= m && (a[x][y] == 2 || a[x][y] == 0);
	};
	auto convert = [n, m](int x, int y, bool f) { return (x - 1) * m + y + f * n * m; };

	int dx[4] = {-1, 1, 0, 0};
	int dy[4] = {0, 0, -1, 1};

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			G.add_edge(G.s, convert(i, j, 0), 1);
			G.add_edge(convert(i, j, 0), G.s, 0);
			G.add_edge(convert(i, j, 1), G.t, 1);
			G.add_edge(G.t, convert(i, j, 1), 0);
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == 1 || a[i][j] == 0) {
				G.add_edge(convert(i, j, 0), convert(i, j, 1), 1);
				G.add_edge(convert(i, j, 1), convert(i, j, 0), 0);
			}
			if (a[i][j] == 2 || a[i][j] == 0) {
				for (int k = 0; k < 4; ++k) {
					if (!valid(i + dx[k], j + dy[k])) continue;
					G.add_edge(convert(i, j, 0), convert(i + dx[k], j + dy[k], 1), 1);
					G.add_edge(convert(i + dx[k], j + dy[k], 1), convert(i, j, 0), 0);
				}
			}
		}
	}

	int max_flow = G.dinic();
	std::cerr << max_flow << '\n';
	if (max_flow == n * m)
		std::cout << "Yes" << '\n';
	else
		std::cout << "No" << '\n';
	return 0;
}
```


---

## 作者：Lyu_echo (赞：0)

# 题意

给定 $n \times m$ 的网格。

存在 $1 \times 1$ 和 $1\times 2$ 两种棋牌。

格子上有 `1 2 ?` 三种符号。表意如下：

- `1` 表示该格子必须用 $1\times 1$ 的棋牌覆盖；
- `2` 表示该格子必须用 $1\times 2$ 的棋牌覆盖；
- `?` 表示任意一种棋牌覆盖均可。

问是否存在合法的覆盖方案。

## 解题思路

把玩样例发现，这是一个类似匹配的问题。大致如下：

- 匹配任意的两个可以用 $1\times 2$ 棋牌覆盖的格子；
- 剩余格子用 $1\times 1$ 覆盖。

我们不妨把网格转换为图。

我们将网格上每一个顶点都转换为图上的一个节点。

考虑如下方式建图：

- 对于任意的两个相邻顶点，若两点均不为 `1`，则添加一条边。

上文中，`顶点`特指网格中的点，`节点`特指图中的点。

再次把玩样例，按照上述方法建图如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/ht9up0qt.png)

不难发现，此图仅有一个偶环，满足二分图。故样例一可以完成匹配。

综上所述，我们在建图以后从每个为 `2` 的定点搜增广路。

当最大匹配为节点数时则存在合法覆盖方案，否则不能。

## 代码实现

使用匈牙利算法跑二分图的最大匹配。

节点最多 $nm$ 个，最多 $nm$ 条边，故时间复杂度 $\mathcal{O}(n^2m^2)$。

数据 $n,m\le 300$，时间戳优化可过。

```cpp
#include <iostream>
#include <vector>
#define int long long
using namespace std;
// struct Edge{
//     int v, nxt;
// }edge[4000010];
vector<int> g[200010];
int n, m;
// int edge_cnt;
int cnt;
char a[500][500];
int match[200000], book[200000], rnk[500][500];
// int head[4000010];
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
// void add(int u, int v) {
//     edge[++edge_cnt].v = v;
//     edge[edge_cnt].nxt = head[u];
//     head[u] = edge_cnt;
// }
bool dfs(int u) {
    if (book[u] == cnt) return false;
    book[u] = cnt;
    // for (int i = head[u]; i; i = edge[i].nxt) {
    for (auto &v : g[u]) {
        // int v = edge[i].v;
        if (book[v] == cnt) continue;
        book[v] = cnt;
        if (!match[v] || dfs(match[v])) {
            match[u] = v;
            match[v] = u;
            return true;
        }
    }
    return false;
}
signed main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (a[i] + 1);
    }
    int rnk_cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            rnk[i][j] = ++rnk_cnt;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '1' || (i + j) % 2 == 0) continue;
            for (int k = 0; k < 4; k++) {
                int nx = dx[k] + i;
                int ny = dy[k] + j;
                if (a[nx][ny] == '1') continue;
                if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
                g[rnk[i][j]].push_back(rnk[nx][ny]);
                g[rnk[nx][ny]].push_back(rnk[i][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '2') {
                if (!match[rnk[i][j]]) {
                    cnt++;
                    if (!dfs(rnk[i][j])) {
                        cout << "No" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "Yes" << endl;

    return 0;
}
//链式前向星存图会被 AfterContest hack掉？？？？
```

---

