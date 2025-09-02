# [ZSHOI-R1] 巡城

## 题目背景

在 X 国国王多年的建设之下，她的国家发生了质的蜕变，从众多 $n$ 座城市却只有 $n-1$ 条道路的国家中脱颖而出。也就是说，X 国不再是一棵树了，而是一张图。

## 题目描述

国王为了能够集中自己的权力，稳固城邦，她对国家道路设计要求十分严苛，**任何两个城市之间的路径至多只有一条不经过首都**，虽然但是，没有人知道为什么这样能够更好地稳固 X 国。

有一天，X 国国王决定巡视所有的城市，她通过无线电在巡城前一天向所有的城市通知了这个好消息。热情的群众们也积极地做出了响应，准备迎接国王的到来。

国王一天只能造访一座城市，而且第一天她会从首都开始。

在之后的每一天，她会随机从与她所在城市直接相连的城市中**等概率**地选择一个她**没有前往过的城市**前往。如果不存在这样的城市，她会立即**原路返回**，从她来这个城市的路回去，再重复上述操作，因为有携带宇宙射线的传送门，这个过程**不消耗时间**。

爱戴她的群众们想要知道，他们的国王第一次到达他们所在城市的日期（她造访首都的那一天为 $1$，之后每一天一次加 $1$）的期望是多少，答案对 $998244353$ 取模。

保证城市构成的图是连通图，无自环与重边，且首都编号为 $1$。

## 说明/提示

对于所有的数据点，$1\leqslant n\leqslant 5 \times 10^5$，$1\leqslant m \leqslant 6 \times 10^5$。
| 数据点 | n | m |
| :----------: | :----------: | :----------: |
| 1~2 | $5$ | $7$ |
| 3~5 | $\leqslant10^4$ | $n-1$ |
| 6~8 | $\leqslant10^4$ | $n$ |
| 9~10 | $\leqslant10^4$ | $2n-3$ |
| 11~15 | $\leqslant10^4$ | $\leqslant2\times10^4$ |
| 16~20 | $\leqslant5\times10^5$ | $\leqslant6\times10^5$ |

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
4 3
1 2
2 3
2 4
```

### 输出

```
1 2 499122180 499122180 
```

## 样例 #3

### 输入

```
5 7
5 4
2 4
4 3
1 3
1 2
1 4
1 5
```

### 输出

```
1 249561092 249561092 249561091 249561092 
```

# 题解

## 作者：寻逍遥2006 (赞：4)

[传送门](https://www.luogu.com.cn/problem/P9454)

图满足**任何两点之间的简单路径至多只有一条不经过 $1$ 节点**，所以删去 $1$ 节点之后，图中**如任何两点之间至多只有一条简单路径**。则删去 $1$ 节点之后的图构成森林，此时的每一个连通块为一颗树（注意不是原图的树）。

所以本题的边数范围是 $n-1\leq m\leq n-2+n-1=2n-3$。

题意为求从 $1$ 开始 dfs，每一个点的 dfs 序期望，也就是要求对于每个节点 $u$ 期望有多少个点在 $u$ 之前深搜到，答案就是其 $+1$。

由于原图满足删去 $1$ 节点之后的图构成森林，所以在进入了某棵树之后，只有将这颗树深搜完才能进入别的树。

考虑将点对间贡献分为树内和树外两种。

#### 先考虑树内贡献：

假如只有一个节点能够作为这整棵树中第一个搜到的节点，我们令其为根。

那么对于树中的一个节点 $u$：$u$ 的祖先必然对 $u$ 做 $1$ 的贡献；$u$ 的子孙必然不对 $u$ 做贡献；其他节点对 $u$ 做 $\frac{1}{2}$ 的贡献，就是在这个点 $v$ 和 $u$ 的 LCA 处先走向 $u$ 或先走向 $v$，二者概率均为 $\frac{1}{2}$。

记 $T_u$ 为 $u$ 所在的树，$anc_u$ 为 $u$ 的祖先集合，$sub_u$ 为 $u$ 的子孙集合，则 $u$ 点在树内的dfs序期望为 $\dfrac{|T_u|+|anc_u|-|sub_u|}{2}$。

对于所有 $|anc_u|$ 和 $|sub_u|$ 的求值是 $O(n)$ 的。

由于有多个节点可能和 $1$ 相连，它们等概率地可能成为这棵树的根，如果暴力对于每一个点进行一次深搜，最坏复杂度是 $O(n^2)$。

改为换根DP，维护每个点到所有可能成为根的点的距离和，以及对于每种根对应的子树大小和。

随便钦定一个点为根，考虑先深搜维护出每个点到子树内所有可能为根的点的距离，以及对于子树内所有点对应的子树大小和。

这两部分均可以实现 $O(1)$ 转移，所以换根DP复杂度为 $O(n)$。

#### 再考虑树间贡献：

对于两颗树 $S$ 和 $T$，我们记它们分别和 $1$ 节点分别有 $cnt_S$ 和 $cnt_T$ 个点相连。

我们考虑 $T$ 节点在 $S$ 节点之前搜到的概率应为 $\dfrac{cnt_T}{cnt_S+cnt_T}$，可以理解为将所有和 $1$ 节点相连的点随意排列作为 $1$ 节点开始深搜的顺序，则 $T$ 树在 $S$ 树之前搜的概率等价于 $T$ 树的 $cnt_T$ 个节点中最靠前的节点在 $S$ 树的 $cnt_S$ 个节点中最靠前的节点之前的概率，等价于在 $cnt_T$ 个黑球和 $cnt_S$ 个白球选出一个球，它是黑色的概率。

所以 $T$ 树对 $S$ 树每个节点的贡献为 $\dfrac{cnt_T|T|}{cnt_S+cnt_T}$。

暴力考虑树间两两贡献的最劣复杂度也是是 $O(n^2)$ 的，尝试优化。

假设对于两棵树 $T_1$ 和 $T_2$，满足 $cnt_{T_1}=cnt_{T_2}$，则它们对于其他树的贡献只有 $|T_1|$ 和 $|T_2|$ 的区别，而和 $S$ 有关的分母是不变的。

所以考虑将所有 $cnt_T=k$ 的数分在一组，然后统一处理，然后剔除掉自己对自己的贡献即可。

由于 $\sum cnt_T\leq n$，所以不同的 $cnt_T$ 只至多 $O(\sqrt{n})$，然后再两两暴力维护复杂度就是 $O(n)$ 的了。

所以总体复杂度是 $O(n)$。

---

## 作者：zifanwang (赞：3)

[题面](https://www.luogu.com.cn/problem/P9454)

因为**任何两个城市之间的路径至多只有一条不经过 $1$ 号节点**，所以删掉 $1$ 号节点后，剩下的图成一个森林。题意就是求从点 $1$ 开始 $\tt dfs$，每个点的 $\tt dfs$ 序的期望。

先考虑每个树内部的贡献。我们以这个树内第一个被搜到的节点为根，对于树内的任意一个节点，它的所有祖先对它的贡献是 $1$，所有子孙对它没有贡献，其它节点对它的贡献是 $\frac{1}{2}$（在 $\tt lca$ 处有两个子树各有一半概率被先搜到）。

可以树形 $\tt dp$，分别求出 $E(\text{祖先个数})$ 和 $E(\text{子树大小})$，树内的贡献就是 $\frac{\text{树的大小}+E(\text{祖先个数})-E(\text{子树大小})}{2}$。实现方法比较容易就不多讲了。

再考虑不同树之间的贡献。对于两棵树 $S$ 和 $T$，我们记它们与点 $1$ 有一条边直接连接的点的个数分别是 $c_S$ 和 $c_T$。只考虑这两棵树的遍历顺序，很容易可以得到 $S$ 对 $T$ 中每个点的贡献是 $\frac{c_S|S|}{c_S+c_T}$，于是就有了一种 $O(n^2)$ 的做法。

考虑怎么优化，发现 $c_S$ 最多只有 $\sqrt n$ 种不同的值，可以将这些树分在一组，统一处理，最后减去自己对自己的贡献，两两暴力计算的时间复杂度是 $O(n)$。

总时间复杂度 $O(n+m)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 500003
#define md 998244353
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int power(int x,int y){
	int ans=1;
	for(;y;y>>=1){
		if(y&1)ans=(ll)ans*x%md;
		x=(ll)x*x%md;
	}
	return ans;
}
int n,m,c,c1,a[mxn],d[mxn],f[mxn],s[mxn],sm[mxn],sz[mxn],up[mxn],as[mxn],ans[mxn];
vector<int>e,g[mxn];
bool v[mxn],b[mxn];
ll xi;
void dfs(int x){
	v[x]=1,c++,sz[x]=1;
	if(b[x])c1++;
	for(int i:g[x])if(!v[i]){
		dfs(i);
		s[x]+=s[i];
		sz[x]+=sz[i];
	}
}
void dfs1(int x,int fa){
	f[x]=s[x]-b[x];
	ans[x]=c+1;
	for(int i:g[x])if(i!=fa&&i!=1){
		dfs1(i,x);
		f[x]=(f[x]+f[i])%md;
	}
}
void dfs2(int x,int fa){
	a[x]=c,d[x]=c1;
	if(fa)up[x]=(up[fa]+(c1-s[x])+f[fa]-f[x]-s[x])%md;
	ans[x]=(ans[x]+(up[x]+f[x])*xi)%md;
	ans[x]=(ans[x]-(c-sz[x])*xi%md*s[x])%md;
	for(int i:g[x])if(i!=fa&&i!=1)ans[x]=(ans[x]-sz[i]*xi%md*(c1-s[i]))%md;
	for(int i:g[x])if(i!=fa&&i!=1){
		dfs2(i,x);
	}
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=0,x,y;i<m;++i){
		scanf("%d%d",&x,&y);
		g[x].pb(y),g[y].pb(x);
		if(x==1)b[y]=1,s[y]++;
		if(y==1)b[x]=1,s[x]++;
	}
	v[1]=1;
	for(int i:g[1])if(!v[i]){
		c=0,c1=0;
		dfs(i);
		xi=power(c1,md-2);
		dfs1(i,0);dfs2(i,0);
		sm[c1]=(sm[c1]+c)%md;
	}
	rep(i,1,n)if(sm[i])e.pb(i);
	for(int i:e){
		for(int j:e)if(i!=j)as[i]=(as[i]+(ll)sm[j]*j%md*power(i+j,md-2))%md;
	}
	rep(i,1,n){
		ans[i]=(ans[i]*499122177ll%md+md)%md;
		ans[i]=(ans[i]+as[d[i]]+(sm[d[i]]-a[i])*499122177ll%md)%md;
	}
	rep(i,1,n)printf("%d ",(ans[i]+1)%md);
	return 0;
}
```

---

## 作者：Reunite (赞：1)

喵喵题。

首先，因为任意两点间最多有一条路径不经过 $1$ 号点，那么如果删去 $1$ 号点，剩下的一定是一个森林，森林中每棵树都有至少一个点与 $1$ 有连边。

考虑 $\text{dfs}$ 序的意义，即深搜时排在每个点前面的点个数，而这个值是可以拆到每个点上的贡献的，具体地，若 $P(x,y)$ 表示随机选边深搜过程中 $x$ 在 $y$ 之前的概率，则 $dfn_u=\sum_vP(u,v)$。因为深搜一定是搜到底，所以在从 $1$ 开始进入到某棵树之后，不可能没搜完就返回 $1$，也就是说真正的遍历顺序是按照所有顺序进入每棵树，然后遍历完整棵树之后返回 $1$。

这启示我们把贡献拆为同一棵树内的贡献和树之间的贡献，容易发现树之间的贡献和具体点无关，仅于进入的概率有关。我们先考虑树内的贡献：

对于一棵有 $rs$ 个与 $1$ 相连的树 $T$，我们需要处理每个与 $1$ 有边的点为根时的情况。显然 $u$ 祖先节点排在 $u$ 前的概率是 $1$，$u$ 的后代节点排在 $u$ 前的概率是 $0$，剩余的节点，考察在他们的 $\text{lca}$ 处进行决策，因为我们只关注这对节点，因此先进入另一棵子树的概率时 $\frac{1}{2}$，该点一定会造成 $\frac{1}{2}$ 的贡献。记 $s1,s2$ 分别为当前根意义下 $u$ 的祖先节点个数（包括 $u$），$u$ 的子树大小（不包括 $u$），那么树内贡献为 $s1+\frac{(|T|-s1+s2)}{2}=\frac{|T|+s1-s2}{2}$。

但这样做显然可以被卡到 $O(n^2)$，注意到我们难求的是所有 $s1,s2$，$s2$ 可以通过关键点在 $u$ 的每个子树方向上的个数来快速求，$s1$ 的实际意义即 $u$ 与每个关键点的距离和，这个可以用经典拆距离和方法。那么树内部分就做到 $O(n)$ 了。

树间部分更加简单，考虑 $T_1$ 在 $T_2$ 前的概率，显然为 $\frac{rs(T_1)}{rs(T_1)+rs(T_2)}$，其权值为 $|T_1|$，因此对每棵树 $T_i$，树间贡献可以写为 $\sum_{j\ne i}\frac{|T_j|rs(T_j)}{rs(T_i)+rs(T_j)}$。这个值对 $T_i$ 中的所有点显然都是一样的。

直接求会被菊花卡掉（但是也能过），发现难点在于分母不同，因为 $\sum rs(T_i)\le n$，因此不同种类的 $rs(T_i)$ 只有 $O(\sqrt n)$ 个，枚举种类累加一下贡献即可。

显然上面分析所有涉及到除法的分母都只有 $O(n)$ 级别，线性预处理逆元即可做到 $O(n+m)$ 复杂度。

---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define mod 998244353
#define int long long
using namespace std;

int n,m,cnt,cc;
int h[500005];
int bl[500005];
int rt[500005];
int rs[500005];
int rd[500005];
int rn[500005];
int mp[500005];
int sz[500005];
int ssz[500005];
int dep[500005];
int ans[500005];
int vis[500005];
int inv[1000005];
vector <int> G;
vector <int> g[500005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void init(int u,int fa){
	bl[u]=cnt;
	vis[u]=1,sz[u]=1;
	dep[u]=dep[fa]+1;
	rn[cnt]++;
	if(mp[u]) rs[cnt]++,rd[cnt]+=dep[u],ssz[u]=1;
	for(int v:g[u]) if(v^fa) init(v,u),sz[u]+=sz[v],ssz[u]+=ssz[v];
	return ;
}

inline void dfs(int u,int fa,int ss,int rt){
	ans[u]-=(rs[rt]-ssz[u])*(sz[u]-1);
	ss+=ssz[u];
	if(mp[u]) cc++,ans[u]-=rn[rt]-1;
	ans[u]+=rs[rt]*dep[u]+rd[rt]-2*ss+rs[rt]*(rn[rt]+1);
	for(int v:g[u]){
		if(v==fa) continue;
		int x=cc;
		dfs(v,u,ss,rt);
		ans[u]-=(rn[rt]-sz[v]-1)*(cc-x);
	}
	ans[u]=(ans[u]%mod+mod)%mod;
	ans[u]=1+(ans[u]*inv[rs[rt]*2])%mod;
	return ;
}

signed main(){
	in(n),in(m);
	for(int i=1;i<=m;i++){
		int u,v;
		in(u),in(v);
		if(u>v) swap(u,v);
		if(u==1) G.emplace_back(v);
		else g[u].emplace_back(v),g[v].emplace_back(u);
	}
	inv[1]=1;
	for(int i=2;i<=n+n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int v:G) mp[v]=1;
	for(int v:G) if(!vis[v]) rt[++cnt]=v,init(v,0);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=cnt;i++) dfs(rt[i],0,0,i),cc=0,vis[rs[i]]+=rn[i];
	for(int i=1;i<=n;i++) ans[i]-=rs[bl[i]]*rn[bl[i]]%mod*inv[rs[bl[i]]<<1]%mod;
	cc=0;
	for(int i=1;i<=n;i++) if(vis[i]) mp[++cc]=i;
	for(int i=1;i<=cc;i++)
		for(int j=1;j<=cc;j++)
			(h[mp[i]]+=inv[mp[i]+mp[j]]*mp[j]%mod*vis[mp[j]])%=mod;
	for(int i=1;i<=n;i++) ans[i]+=h[rs[bl[i]]];
	printf("1 ");
	for(int i=2;i<=n;i++) printf("%lld ",(ans[i]%mod+mod)%mod);
	puts("");

	return 0;
}
```

---

## 作者：Leasier (赞：1)

### 测试点 $3 \sim 5$：$m = n - 1$ 即原图为一棵树
对于求“期望第几个访问到”、“期望排名”之类的问题，我们可以考虑：

- 设我们在求 $u$ 第几个访问到。
- 答案为 $\displaystyle\sum_i P(rk_i \leq rk_u)$。

对本题而言：

- 对于 $1 \to fa_u$ 路径上的所有点 $v$，$rk_v \leq rk_u$ 一定成立。
- 对于 $u$ 子树中除 $u$ 以外的点 $v$，$rk_v > rk_u$ 一定成立。
- 对于其他点 $v$，是否成立取决于国王在 $lca(u, v)$ 处先走 $u$ 所在子树还是 $v$ 所在子树，于是 $P(rk_v \leq rk_u) = \frac{1}{2}$。

进而可以得到 $u$ 的答案为 $\frac{n + depth_u - size_u + 1}{2}$，这里 $depth_1 = 1$。

处理出深度和子树大小后即可 $O(n)$ 求解。
### 一般情况
考虑这张图的性质。

看到“任何两个城市之间的路径至多只有一条不经过首都”，考虑**把 $1$ 删掉**，此时任意两点间至多只有一条简单路径，即删后原图变成了**森林**。

对于这片森林中的一棵树 $T$，考虑抓出原图中所有 $1 \to u, u \in T$ 的点 $u$（我们称这样的 $u$ 为关键点），设 $cnt(T)$ 表示 $T$ 中关键点的数量，则对于每个 $u$，我们都有 $\frac{1}{cnt(T)}$ 的概率以它为根。在树的算法的基础上换根 dp 即可。

接下来考虑两棵树 $T_1, T_2$ 的点间的贡献，则我们有 $\frac{cnt(T_2)}{cnt(T_1) + cnt(T_2)}$ 的概率先遍历完 $T_2$，且贡献为 $|T_2|$。注意到不同的 $cnt(T)$ 有 $O(\sqrt{n})$ 个，于是我们暴力枚举两个不同的 $cnt(T)$ 即可。

综上，时间复杂度为 $O(n + m)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

const int mod = 998244353, inv2 = 499122177;
int cnt = 0;
int head[500007], belong[500007], fa[500007], size[500007], dp1[500007], dp2[500007], dp3[500007], dp4[500007], bucket[500007], sum[500007], item[1007], ref[500007];
ll inv[1000007], cross1[1007], cross2[500007];
bool mark[500007], vis[500007];
Edge edge[1000007];

inline void init(int n){
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= n; i++){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father, int bel){
	vis[u] = true;
	belong[u] = bel;
	fa[u] = father;
	size[u] = 1;
	if (mark[u]) dp1[u] = 1;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			dfs1(x, u, bel);
			size[u] += size[x];
			dp1[u] += dp1[x];
			dp2[u] = (dp2[u] + dp2[x] + dp1[x]) % mod;
		}
	}
}

void dfs2(int u){
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]){
			dp3[x] = dp3[u] + (dp1[u] - dp1[x]);
			dp4[x] = ((dp4[u] + dp3[u] + (dp2[u] - dp2[x] - dp1[x]) + (dp1[u] - dp1[x])) % mod + mod) % mod;
			dfs2(x);
		}
	}
}

int main(){
	int n = read(), m = read(), cnt = 0;
	init((n - 1) * 2);
	for (register int i = 1; i <= m; i++){
		int u = read(), v = read();
		if (u == 1){
			mark[v] = true;
		} else if (v == 1){
			mark[u] = true;
		} else {
			add_edge(u, v);
			add_edge(v, u);
		}
	}
	for (register int i = 2; i <= n; i++){
		if (!vis[i]){
			dfs1(i, 0, i);
			dfs2(i);
			bucket[dp1[i]]++;
			sum[dp1[i]] += size[i];
		}
	}
	for (register int i = 1; i < n; i++){
		if (bucket[i] > 0){
			cnt++;
			item[cnt] = i;
			ref[i] = cnt;
		}
	}
	for (register int i = 1; i <= cnt; i++){
		for (register int j = 1; j <= cnt; j++){
			cross1[i] = (cross1[i] + sum[item[j]] * (item[j] * inv[item[i] + item[j]] % mod) % mod) % mod;
		}
	}
	for (register int i = 2; i <= n; i++){
		if (belong[i] == i) cross2[i] = ((cross1[ref[dp1[i]]] - (ll)size[i] * inv2 % mod) % mod + mod) % mod;
	}
	printf("1 ");
	for (register int i = 2; i <= n; i++){
		ll val = (ll)dp3[i] * size[i] % mod;
		if (mark[i]) val = (val + size[belong[i]]) % mod;
		for (register int j = head[i]; j != 0; j = edge[j].nxt){
			int x = edge[j].end;
			if (x != fa[i]) val = (val + (ll)dp1[x] * (size[belong[i]] - size[x]) % mod) % mod;
		}
		printf("%lld ", (((size[belong[i]] + (dp2[i] + dp4[i] - val) * inv[dp1[belong[i]]] % mod) * inv2 % mod + cross2[belong[i]] + 2) % mod + mod) % mod);
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

比较锻炼基本功的好题（？）

首先分析一下图的性质，因为任意两点之间至多一条路径经过 $1$，所以把 $1$ 和所有点的连边删除之后，会形成一个森林。那么在这张图上 dfs 的过程就很清晰了：每次进入一个子树，走完这个子树之后再进别的子树。

算 dfs 序的期望实际上就是算期望几个数在自己前面，因此可以把贡献拆开。我们分成同一子树和不同子树两个部分计算。

对于同一子树的部分，是经典的，考虑 $rt\to x$ 的链 $p_1=rt,p_2,p_3,\dots p_k=x$，每次从 $p_i$ 走向 $p_{i+1}$ 的时候，其他儿子分别都有 $\frac{1}{2}$ 的概率先进入，所以每个子树贡献 $\frac{sz}{2}$。也就是所有 $x$ 子树外，不在 $x$ 到根路径上的点系数为 $\frac{1}{2}$，$x$ 到根路径上的点系数为 $1$，子树内的点系数为 $0$。

我们相当于限制了一部分点可以作为根，对每个点求所有根的答案之和。这可以用换根 dp 轻松解决。具体来说，把上面的贡献表示成 $\frac{S-sz_x+dep_x}{2}$ 的形式，就很容易处理了。

对于不同子树的部分，我们就是要考虑其他子树有多少排在要求的子树之前。对于两棵分别有 $s,t$ 个起点（与 $1$ 相连的点）的子树，含有 $s$ 个的排在含有 $t$ 个的之前的概率为 $\frac{s}{s+t}$，贡献为 $\frac{s\cdot sz}{s+t}$。

这个分式不好拆开算贡献，大概率只能硬算。仔细一想确实能算，因为不同的 $s$ 只有 $\mathcal O(\sqrt n)$ 个，所以把 $s$ 相同的放一起贡献就行了，最后再扣掉自己到自己的贡献。时间复杂度 $\mathcal O(n)$。

我偷懒了写了 $\mathcal O(n\log n)$，细节有点多，样例比较弱，不是很舒适。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e6+9,Mod=998244353,inv2=(Mod+1)>>1;
ll n,m,U[N],V[N],rt[N],tot,ans[N],bel,vis[N],s[N];
ll coef[N],coef2[N],tmp[N],tc;
ll dep[N],sz[N],szt[N],sqz[N],cnt,sumd,sumz;
ll fac[N],ifac[N],inv[N];
ll qr[N],bsz[N],ssz[N],ft[N];
vector<ll>to[N],pt;
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
void dfs1(ll x,ll fa){
    dep[x]=dep[fa]+1,sz[x]=1,szt[x]=rt[x];
    if(rt[x])sumd+=dep[x];
    pt.push_back(x);
    for(ll y:to[x]){
        if(y==fa)continue;
        dfs1(y,x);
        sz[x]+=sz[y],szt[x]+=szt[y],sqz[x]+=sqz[y];
    }
    if(rt[x])sqz[x]=sz[x],sumz+=sz[x];
}
void dfs2(ll x,ll fa,ll bel){
    vis[x]=bel,bsz[bel]++;
    for(ll y:to[x]){
        if(y==fa)continue;
        ft[y]=x;
        ans[y]=ans[x];
        ans[y]=(ans[y]-szt[y]*2+cnt)%Mod;
        dfs2(y,x,bel);
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read();
    rep(i,1,m)U[i]=read(),V[i]=read();
    rep(i,1,m){
        if(U[i]>V[i])swap(U[i],V[i]);
        if(U[i]==1)rt[V[i]]=1,tot++;
        else to[U[i]].push_back(V[i]),to[V[i]].push_back(U[i]);
    }
    rep(i,2,n){
        if(vis[i])continue;
        pt.clear(),sumd=0,sumz=0;
        dfs1(i,0),cnt=szt[i];
        ans[i]=(sz[i]*cnt+sumd+Mod)%Mod;
        dfs2(i,0,++bel);
        for(ll y:pt){
            for(ll z:to[y]){
                if(ft[z]==y){
                    ll c=szt[z];
                    ans[y]=(ans[y]-c*(sz[i]-sz[z])%Mod+Mod)%Mod;
                }
                else {
                    ll c=szt[i]-szt[y];
                    ans[y]=(ans[y]-c*sz[y]%Mod+Mod)%Mod;
                }
            }
            if(rt[y])ans[y]=(ans[y]-sz[i]+Mod)%Mod;
            ans[y]=(ans[y]+cnt)*inv2%Mod;
        }
    }
    rep(i,2,n){
        if(rt[i])s[vis[i]]++;
    }
    rep(i,1,bel)tmp[++tc]=s[i];
    sort(tmp+1,tmp+tc+1);
    tc=unique(tmp+1,tmp+tc+1)-tmp-1;
    fac[0]=1;
    rep(i,1,n)fac[i]=fac[i-1]*i%Mod;
    ifac[n]=pw(fac[n],Mod-2);
    per(i,n-1,0)ifac[i]=ifac[i+1]*(i+1)%Mod;
    rep(i,1,n)inv[i]=ifac[i]*fac[i-1]%Mod;
    rep(i,1,bel)qr[i]=lower_bound(tmp+1,tmp+tc+1,s[i])-tmp;
    rep(i,1,bel)ssz[qr[i]]+=bsz[i];
    rep(i,1,tc){
        rep(j,1,tc)coef[i]=(coef[i]+tmp[j]*inv[tmp[i]+tmp[j]]%Mod*ssz[j])%Mod;
    }
    rep(i,1,bel)coef2[i]=(coef[qr[i]]-s[i]*inv[s[i]+s[i]]%Mod*bsz[i]%Mod+Mod)%Mod;
    write(1),putchar(' ');
    rep(i,2,n)write((1+coef2[vis[i]]+ans[i]*inv[s[vis[i]]])%Mod),putchar(' ');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

思考如何刻画**任何两个城市之间的路径至多只有一条不经过首都**。

结论：**以首都为根的任意一棵 DFS 树外的边均为首都到其他一节点的边**。

证明：

考虑反证，即假设存在一条边连接 $u,v$ 且 $u,v$ 均不为首都。

这条边有两种情况。

* 若 $u,v$ 的 LCA 为根，不难发现 DFS 时一定会经过这条边，矛盾。
* 若 $u,v$ 的 LCA 不为根，不难发现这条边与 $u$ 到 LCA，$v$ 到 LCA 两条链组成一个环，环上任意两点均有两条不经过首都的路径，矛盾。

故所有边均为根到其他一节点。

------

考虑对每一个根的独立子树分别计算答案。

称子树内与根有边的点为**植入点**。

不难发现只要进入了这棵子树就一定会遍历完再出去。

考虑对于植入点 $u$ 和目标点 $v$，目标点 $v$ 期望经过几个点后到达。不难发现 $u$ 到 $v$ 路径上的所有点一定经过，以 $u$ 为根 $v$ 所在子树一定不经过。其他点均有**一半概率**经过。

证明：

不难发现到某个以 $u$ 为根，只要经过点 $w$，就一定会经过整个 $w$ 所在子树后才会离开。

对于 $u$ 到 $v$ 路径上的每个点，不难发现先经过 $v$ 所在子树和先经过任意一个其他子树的概率一样，故有一半概率会经过其他所有子树。

------

此时我们已经可以 $O(n^2)$ 计算了一个首都的子树的内部贡献。

考虑如何快速计算，即维护对于所有 $u$，$u$ 到 $v$ 距离和与 $v$ 所在子树大小和。可以使用简单树形 dp 计算，复杂度优化至 $O(n)$。


------

考虑计算首都的不同子树对每个点的贡献。对于两个植入点数量为 $a,b$ 的子树，计算先经过植入点数量为 $a$ 的子树，$\dfrac{\binom{a+b-1}{a-1}}{\binom{a+b}{a}}=\frac{a}{a+b}$。直接对于梅两个子树计算是 $O(n)$ 的。然而我们会发现**不同的子树植入点数量**是 $O(\sqrt{n})$ 级别的。于是我们可以先处理一遍将所有子树植入点数量为 $i$ 的所有子树大小和，于是就可以 $O(n\sqrt{n})$ 计算外部贡献。

------

总复杂度 $O(n\sqrt{n})$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
vector<int> vc[1000005];
int vis[1000005],ans[1000005],siz[1000005],dep[1000005],nr[1000005],sdep[1000005],udep[1000005],tag[1000005],padd,totc,tots;
vector<int> tr[1000005];
void dfs(int now){
	vis[now]=1;
	siz[now]=1;
	sdep[now]=nr[now]*dep[now];
	for(auto v:vc[now]){
		if(!vis[v]){
			tr[now].push_back(v);
			dep[v]=dep[now]+1;
			dfs(v);
			siz[now]+=siz[v];
			nr[now]+=nr[v];
			sdep[now]+=sdep[v];
		}
	} 
}
void dfs2(int now){
//	cout<<now<<" ";
	ans[now]=padd;
	for(auto v:tr[now]) (ans[now]+=nr[v]*qp(totc,-1)%mod*siz[v]%mod*inv2+(sdep[v]%mod+mod-dep[now]*nr[v]%mod)*qp(totc,-1)%mod*inv2)%=mod;
	for(auto v:tr[now]){
		udep[v]=(udep[now]+(sdep[now]%mod+mod-sdep[v]%mod)+mod-(nr[now]+mod-nr[v])*dep[now]%mod+totc+mod-nr[v])%mod;
		dfs2(v);
	}
	(ans[now]+=(totc-nr[now])*qp(totc,-1)%mod*(tots-siz[now])%mod*inv2%mod+udep[now]*qp(totc,-1)%mod*inv2)%=mod;
}
vector<int> avlen;
int tot[1000005],inv[2000005];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=2*n;i++) inv[i]=qp(i,mod-2);
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u); 
		if(u==1||v==1){
			nr[u+v-1]=1;
		}
	}
	vis[1]=ans[1]=1;
	for(auto v:vc[1]){
		if(!vis[v]){
			dfs(v);
			tag[v]=1;
			if(!tot[nr[v]]) avlen.push_back(nr[v]);
			tot[nr[v]]+=siz[v];
		}
	}
	for(auto v:vc[1]){
		if(tag[v]){
			padd=2;
			for(auto u:avlen){
				(padd+=u*inv[u+nr[v]]%mod*tot[u])%=mod;
			}
//			cout<<padd<<" ";
			(padd+=mod-siz[v]*inv2%mod)%=mod;
//			cout<<padd<<"\n";
			totc=nr[v];
			tots=siz[v];
//			cout<<totc<<" "<<tots<<" "<<sdep[v]<<"\n";
			dfs2(v);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}

```

---

