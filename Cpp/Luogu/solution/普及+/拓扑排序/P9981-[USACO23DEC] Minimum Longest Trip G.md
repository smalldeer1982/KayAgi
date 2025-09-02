# [USACO23DEC] Minimum Longest Trip G

## 题目描述

Bessie 正在奶牛大陆上旅行。奶牛大陆由从 $1$ 到 $N$ 编号的 $N$（$2 \le N \le 2\cdot 10^5$）座城市和 $M$（$1 \le M \le 4\cdot 10^5$）条单向道路组成。第 $i$ 条路从城市 $a_i$ 通向城市 $b_i$，标签为 $l_i$。

由城市 $x_0$ 开始的长度为 $k$ 的旅程被定义为一个城市序列 $x_0,x_1,\ldots,x_k$，对于所有的 $0 \le i < k$，存在由城市 $x_i$ 到 $x_{i+1}$ 的路。保证在奶牛大陆上不存在长度无限的旅程，不存在两条路连接一对相同的城市。

对于每座城市，Bessie 想知道从它开始的最长旅程。对于一些城市，从它们开始的最长旅程不唯一，Bessie 将选择其中道路标签序列字典序更小的旅程。一个序列比等长的另一个序列字典序更小，当且仅当在它们不同的第一个位置，前者比后者的元素更小。

输出 Bessie 在每座城市选择的旅途的长度和道路标签之和。

## 说明/提示

### 样例解释 2

在下面的解释中，我们用 $a_i\xrightarrow{l_i} b_i$ 表示由城市 $a_i$ 通往 $b_i$，标签为 $l_i$ 的单向道路。

从城市 $4$ 出发有多条旅程，包含 $4\xrightarrow{4} 3\xrightarrow 5 1$，$4\xrightarrow 1 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$。在这些旅程中，$4\xrightarrow{4} 3\xrightarrow 5 1$ 和 $4\xrightarrow 2 2\xrightarrow{10} 1$ 是最长的。它们的长度均为 $2$，道路标签序列分别为 $[4,5]$ 和 $[2,10]$。$[2,10]$ 是字典序更小的那一个，它的和为 $12$。

### 测试点性质

- 测试点 $5-6$ 满足所有道路的标签相同。
- 测试点 $7-8$ 满足所有道路的标签不相同。
- 测试点 $9-10$ 满足 $N,M \le 5000$。
- 测试点 $11-20$ 没有额外限制。

## 样例 #1

### 输入

```
4 5
4 3 10
4 2 10
3 1 10
2 1 10
4 1 10```

### 输出

```
0 0
1 10
1 10
2 20```

## 样例 #2

### 输入

```
4 5
4 3 4
4 2 2
3 1 5
2 1 10
4 1 1```

### 输出

```
0 0
1 10
1 5
2 12```

## 样例 #3

### 输入

```
4 5
4 3 2
4 2 2
3 1 5
2 1 10
4 1 1```

### 输出

```
0 0
1 10
1 5
2 7```

## 样例 #4

### 输入

```
4 5
4 3 2
4 2 2
3 1 10
2 1 5
4 1 1```

### 输出

```
0 0
1 5
1 10
2 7```

# 题解

## 作者：0000pnc (赞：15)

感觉大家都在写倍增 hash。但是有一个简单的方法。

----

题意：给出一个 DAG，边有标签且长度均为 $1$，对于每个结点，求：

* 从这个点出发的最长路长度。
* 最长路中，边的标签组成的序列字典序最小的路径的**标签之和**。

首先对于最长路，可以按照拓扑序 dp，这是容易的。

然后考虑第二问怎么做。设已经得到的结点 $x$ 第一问答案为 $f_{x}$。

我们考虑这个拓扑序 dp 的过程，其本质就是在结点 $u$ 的各个出边中，寻找最优的答案。

那么我们有以下想法：如果我们能够求出 $f_{u}=k$ 的结点中字典序最小的最长路的排名，那么在递推 $f_{u}=k+1$ 的点的答案时可以直接使用出边 $\{w,v\}$ 中 $w$ 最小且 $v$ 的排名尽量靠前的。然后所有 $f_{u}=k+1$ 的推完再 `sort` 一下就可以知道新的排名（代码里是用的 `priority_queue`，二者无区别）。那么第二问就做完了。

时间复杂度 $\mathcal{O}(m+n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct edge {
	int to, w;
};
int n, m, tot, cnt, tp[200005], siz[200005], dep[200005], rk[200005], id[200005];
long long ans[200005];
vector<edge> v[200005], v2[200005];
struct res {
	int e, rnk, to;
};

bool operator< (res x, res y) {
	if (x.e < y.e) return true;
	else if (x.e > y.e) return false;
	return x.rnk > y.rnk;
}
bool cmp(int x, int y) { return dep[x] < dep[y]; }

void topo() {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (!siz[i]) q.push(i);
	}
	while (!q.empty()) {
		int x = q.front(); q.pop();
		tp[++tot] = x;
		for (auto tmp : v2[x]) {
			if (siz[tmp.to]) {
				siz[tmp.to]--;
				if (!siz[tmp.to]) q.push(tmp.to);
			}
		}
	}
}

void dp() {
	for (int i = 1; i <= n; i++) {
		int x = tp[i];
		for (auto tmp : v2[x]) {
			dep[tmp.to] = max(dep[tmp.to], dep[x] + 1);
		}
	}
	for (int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + n + 1, cmp);
}

void bfs() {
	topo(); dp();
	priority_queue<res> pq;
	int mxdep = 0;
	for (int i = 1; i <= n; i++) {
		int x = id[i];
		if (dep[x] != mxdep) {
			mxdep = dep[x];
			while (!pq.empty()) {
				auto tmp = pq.top(); pq.pop();
				rk[tmp.to] = ++cnt;
			}
		}
		if (dep[x]) {
			int mn = 0x3f3f3f3f, mx = 0;
			for (auto tmp : v[x]) {
				if (dep[tmp.to] == dep[x] - 1) mn = min(mn, tmp.w);
			}
			for (auto tmp : v[x]) {
				if (dep[tmp.to] == dep[x] - 1 && tmp.w == mn) mx = max(mx, rk[tmp.to]);
			}
			for (auto tmp : v[x]) {
				if (dep[tmp.to] == dep[x] - 1 && tmp.w == mn && rk[tmp.to] == mx) {
					ans[x] = ans[tmp.to] + tmp.w;
					pq.push({tmp.w, rk[tmp.to], x});
					break;
				}
			}
		}
		else pq.push({0, 0, x});
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1, x, y, w; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &w);
		v[x].push_back({y, w}); siz[x]++;
		v2[y].push_back({x, w});
	}
	bfs();
	for (int i = 1; i <= n; i++) printf("%d %lld\n", dep[i], ans[i]);
	return 0;
}
```

---

## 作者：yuanruiqi (赞：7)

DAG 最长路是容易的，考虑归纳地求出字典序排名和答案。先按照最长路长度将点分层，并只保留连接相邻层的边。按从小到大处理每个层级，最小层级没有出边，显然字典序排名相同。接下来考虑推导出下一层。具体的，对于 $u$，枚举出边 $(u,v)$，按照边权为第一关键字，$v$ 在上一层的排名为第二关键字排序，即可得到 $u$ 的最佳转移。再将同一层级所有的转移类似地排序，便得到当前层的排名。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int maxn = 200000 + 10;
constexpr int maxm = 400000 + 10;
struct edge
{
    int v, w, nxt;
} e[maxm << 1];
int h[maxn], cnt;
void addedge(int u, int v, int w)
{
    e[++cnt].nxt = h[u];
    e[h[u]=cnt].v = v;
    e[cnt].w = w;
}
int dep[maxn];
void dfs(int u)
{
    for (int i=h[u];i;i=e[i].nxt)
    {
        int v = e[i].v;
        if (!dep[v]) dfs(v);
        dep[u] = max(dep[u], dep[v]);
    }
    ++dep[u];
}
int rk[maxn];
i64 ans[maxn];
int tot;
vector<int> c[maxn];
struct ppi
{
    int x, y, z;
    inline ppi(int a=0, int b=0, int c=0) : x(a), y(b), z(c) {}
} sa[maxn];
struct cmp
{
    inline bool operator()(const ppi& a, const ppi& b) const
    {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i=1;i<=m;++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
    }
    for (int i=1;i<=n;++i)
        if (!dep[i]) dfs(i);
    for (int i=1;i<=n;++i)
        c[dep[i]].emplace_back(i);
    for (int t=2;t<=n&&c[t].size();++t)
    {
        int top = 0;
        for (int u : c[t])
        {
            int mn = 0, to = 0;
            for (int i=h[u];i;i=e[i].nxt)
            {
                int v = e[i].v;
                if (dep[v] != dep[u] - 1) continue;
                if (!to || mn > e[i].w || (mn == e[i].w && rk[v] < rk[to]))
                {
                    to = v;
                    mn = e[i].w;
                }
            }
            ans[u] = mn + ans[to];
            sa[++top] = (ppi(mn, rk[to], u));
        }
        sort(sa+1, sa+top+1, cmp());
        for (int i=1;i<=top;++i) rk[sa[i].z] = ++tot;
    }
    for (int i=1;i<=n;++i)
        cout << dep[i] - 1 << ' ' << ans[i] << '\n';
    return 0;
}
```


---

## 作者：cjh20090318 (赞：5)

## 题意

$N$ 个点 $M$ 条边的有向无环图，对于每一个点 $i$ 你需要求出一条从 $i$ 出发的最长路径且路径上边权组成的序列字典序最小。

求每一条路径的长度和边权和。

## 分析

最长的路径很好求，在 DAG 上拓扑排序后动态规划即可。（具体的实现可以参考 [OI-Wiki](https://oi-wiki.org/graph/dag/#dp-%E6%B1%82%E6%9C%80%E9%95%BF%E7%9F%AD%E8%B7%AF)）

现在的问题就变成了怎么求字典序最小。

如果朴素的进行比较判断时间复杂度在最坏情况下是 $O(N^2)$，难以通过此题，考虑优化。

> 一个序列比等长的另一个序列字典序更小，当且仅当在它们不同的第一个位置，前者比后者的元素更小。

说明序列的字典序只和其中一个数有关，于是需要一个更快的方法，来找到第一个不同的位置。

类似于字符串哈希的方法，可以预处理前缀哈希使得单次查询一个子串的复杂度变成 $O(1)$。但是因为没有记录一条链上的所有节点所以不便于二分，考虑换成倍增。

然后是类似于最近公共祖先的倍增写法，不断的向上跳找到第一个标签值不同的位置，然后比较即可。

时间复杂度 $O(M \log N)$，可以通过此题。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<queue>
#include<utility>
#include<vector>
#define MAXN 200002
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const unsigned int p=131;//自然溢出哈希底数。
int n,m,in[MAXN];
int tp[MAXN],c=0;
vector<PII> G[MAXN];
int f[MAXN];//最长链的长度。
LL s[MAXN];//标签和。
int fa[MAXN][19];//链上节点倍增。
ULL pn[MAXN<<2],hs[MAXN][19];//倍增哈希。
int main(){
	pn[0]=1;
	for(int i=1,mi=MAXN<<2;i<mi;i++) pn[i]=pn[i-1]*p;//预处理哈希底数的幂次。
	scanf("%d%d",&n,&m);
	for(int i=0,u,v,w;i<m;i++)
		scanf("%d%d%d",&u,&v,&w),
		G[u].emplace_back(v,w),++in[v];
	queue<int> Q;
	for(int i=1;i<=n;i++)if(!in[i]) Q.push(i);
	for(int u;!Q.empty();){//对图进行拓扑排序。
		u=Q.front(),Q.pop();
		tp[++c]=u;
		for(const auto&[v,w]:G[u])if(!--in[v]) Q.push(v);
	}
	for(int i=n,u;i>0;--i){//根据拓扑序倒推。
		u=tp[i];
		for(const auto&[v,w]:G[u])
			if(f[u]<f[v]+1||(f[u]==f[v]+1&&(ULL)w<*hs[u]))//存在更长的路径或长度相同但当前标签比答案更小就直接更新答案。
				f[u]=f[v]+1,s[u]=s[v]+w,*fa[u]=v,*hs[u]=w;
			else if(f[u]==f[v]+1&&(ULL)w==*hs[u]){//长度相同且第一位也相同，才有必要进行进一步的判断。
				int x=*fa[u],y=v;
				for(int k=18;k>=0;--k)if(fa[x][k] && fa[y][k] && hs[x][k]==hs[y][k])
					x=fa[x][k],y=fa[y][k];//向上跳找到第一个不同的点。
				if(x&&y&&*hs[y]<*hs[x])
					f[u]=f[v]+1,s[u]=s[v]+w,*fa[u]=v,*hs[u]=w;//不同的位置更小，更新答案。
			}
		for(int k=1;k<19;k++)
			fa[u][k]=fa[fa[u][k-1]][k-1],
			hs[u][k]=hs[fa[u][k-1]][k-1]*pn[1<<(k-1)]+hs[u][k-1];//倍增处理祖先和祖先的哈希。
	}
	for(int i=1;i<=n;i++) printf("%d %lld\n",f[i],s[i]);
	return 0;
}
```

---

## 作者：naoliaok_lovely (赞：3)

关于这是金组 T2，二分/三分模板是 T3 这事……  
谁组的题啊喂！！！

## 分析
首先不考虑字典序的问题，只考虑路径长度。这是一个 DAG 的 dp 基础题，按照拓扑排序的顺序进行 dp 转移即可。

恶心的地方在于字典序。我们不可能记录下整条路径，那么怎么求解最小字典序呢？  
首先思考这样一个问题：如果存的下，我们又怎么办呢？我们将问题抽象为如下模型：给定若干个字符串，每次要比较其中两个，问谁大谁小。我们都知道字符串直接比较的复杂度为 $O(len)$ 的，十分优秀。这里用到了字符串的好工具：**哈希**。我们首先对于每一个字符串的前缀，预处理出它的哈希数组。在比较的时候，直接二分 lcp（最长公共前缀），然后比较下一位即可。正确性显然，复杂度 $O(n\log n)$，可以接受。  

回到原问题，相信答案也已经呼之欲出了。我们不可能存下所有前缀的哈希，所以我们对于每一个起点处理出它倍增的位置和哈希值，再进行二分即可。

```
#include<bits/stdc++.h>
using namespace std;
#define u64 unsigned long long
#define LL long long

const int N = 2e5 + 10, M = 2 * N, P = 13331;
int n, m, du[N];
int len[N], to[N][20];
LL f[N];
u64 p[N], ha[N][20];

int h[N], ne[M], e[M], w[M], idx;
void add(int a, int b, int c)
{
	e[++idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

int q[N], hh = 1, tt;
void topsort()
{
	for(int i = 1; i <= n; i++)
		if(!du[i]) q[++tt] = i;
	while(hh <= tt)
	{
		int t = q[hh++];
		for(int i = 1; 1 << i <= len[t]; i++)
			to[t][i] = to[to[t][i - 1]][i - 1], ha[t][i] = ha[t][i - 1] * p[1 << i - 1] + ha[to[t][i - 1]][i - 1];
			
		for(int i = h[t]; i; i = ne[i])
		{
			if(len[e[i]] <= len[t] + 1)
			{
				int j = e[i];
				if(len[j] < len[t] + 1)
					len[j] = len[t] + 1, f[j] = f[t] + w[i], to[j][0] = t, ha[j][0] = w[i];
				else
				{
					if(ha[j][0] != w[i])
					{
						if(ha[j][0] > w[i])
							f[j] = f[t] + w[i], to[j][0] = t, ha[j][0] = w[i];
					}
					else
					{
						int k = to[j][0], l = t;
						for(int j = 18; ~j; j--)
							if(1 << j <= len[k] && ha[k][j] == ha[l][j])
								k = to[k][j], l = to[l][j];
						if(ha[k][0] > ha[l][0])
							f[j] = f[t] + w[i], to[j][0] = t, ha[j][0] = w[i];
					}
				}
			}
			if(!--du[e[i]]) q[++tt] = e[i];
		}
	}
}

int main()
{
	cin >> n >> m;
	for(int i = 1, a, b, c; i <= m; i++)
		scanf("%d%d%d", &a, &b, &c), add(b, a, c), du[a]++;
	p[0] = 1;
	for(int i = 1; i <= n; i++) p[i] = p[i - 1] * P;
	topsort();
	
	for(int i = 1; i <= n; i++)
		printf("%d %lld\n", len[i], f[i]);
	return 0;
}
```

---

## 作者：Zi_Gao (赞：2)

> 题意：
>
> 给定 $n$ 个点 $m$ 条边的的带边权 DAG，问原图从每个点出发的最长路径上，由边权依次组成的字符串字典序最小的路径，求出这个路径长度和边权和。注意路径长度是不带权路径，即只计算路径条数。
>
> $n\leq 2\cdot 10^5,m\leq 4\cdot10^5,l_i\leq 10^9$ 其中 $l_i$ 是边权。

考虑拓扑排序然后 dp，但是由于有相同的边权不能直接 dp，因为你无法判断这个这个字符串是否更优，一个暴力的想法是记录转移，然暴力比较两个字符串，然后就能得到一个 $\mathcal{O}\left(n^2\right)$ 的做法。在这个过程中可以发现有大部分的操作是不必要的，因为比较两个字符串只需要比较他们的第一个不同的字符大小即可，找到这个字符的位置，就能快速比较。现在的问题就是如何找到两个字符串第一个不同的位置，可以考虑在转移上倍增，记录字符串哈希，倍增到第一个不同点然后去比较即可。

话说这是 CWOI 原题，太典了。实现上字符集太大了，有点不好字符串哈希，可以离散化下来然后哈希，这样字符集小了很多。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000093,base=1000639;
inline long long read(){
    long long x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
struct edge{long long v,w,nxt;}e[400010];
long long head[200010],tot,deg[200010],h[200010][24],pw[200010],p[200010][24],lst[200010];
void add(long long u,long long v,long long w){e[++tot]=(edge){v,w,head[u]},head[u]=tot,deg[v]++;}
struct Node{
    long long u,val,len,hsh,ans;
    bool operator <(const Node &x)const{
        if(len!=x.len)return len<x.len;if(val!=x.val)return val>x.val;long long a=u,b=x.u;
        for(long long i=23;i>=0;i--)if(p[a][i]!=0&&p[b][i]!=0&&h[a][i]==h[b][i])a=p[a][i],b=p[b][i];return lst[a]>lst[b];
    }
}f[200010];
Node max(Node x,Node y){return (x<y)?y:x;}
std::map<int,int> mp;
signed main(){
    long long n=read(),m=read();pw[0]=1ll;for(long long i=1;i<=n;i++)pw[i]=pw[i-1]*base%mod;
    for(long long i=1,u,v,w;i<=m;i++)u=read(),v=read(),mp[w=read()]=1,add(v,u,w);
    int iii=1;
    for(auto val:mp) mp[val.first]=++iii;
    queue<long long>q;for(long long i=1;i<=n;i++)if(deg[i]==0)q.push(i);
    while(!q.empty()){
        long long u=q.front();q.pop();
        for(long long i=head[u];i;i=e[i].nxt){;
            long long v=e[i].v,w=mp[e[i].w];f[v]=max(f[v],(Node){u,w,f[u].len+1,(f[u].hsh+w)*base%mod,f[u].ans+e[i].w});
            if((--deg[v])==0){q.push(v);p[v][0]=f[v].u,h[v][0]=lst[v]=f[v].val;for(long long j=1;j<=22;j++)p[v][j]=p[p[v][j-1]][j-1],h[v][j]=(h[p[v][j-1]][j-1]*pw[1<<(j-1)]+h[v][j-1])%mod;}
        }
    }
    for(long long i=1;i<=n;i++) printf("%lld %lld\n",f[i].len,f[i].ans);
    return 0;
}
```


---

## 作者：学委 (赞：2)

- 题意：拓扑图的每条边有一个权重。对每个点，求其拓扑图上最深路径，若有多个最深路径，求路径上权值序列字典序最小的一个。

考虑对出度为 $0$ 的点优先做拓扑排序。对一个点 $u$ 考虑其后继 $v_i$，若 $v_i$ 深度大于 $v_j$ 则显然前者更优，若深度一致，则所连边的权重较小者更优。若权重一样，则需考虑 $v_i$ 和 $v_j$ 分别的后继为多少。

这种情况下不可按照后继依次比较，否则会超时。考虑对那些深度为 $k$ 的点进行排名。排名依据依次为 $(\text{最优后继边权重}, \text{最优后继边排名})$（也就是说，深度为 $k$ 的所有点的排名依赖于深度为 $k - 1$ 的点的排名）。那么深度一致的后继点，可以直接选择排名靠前的点。 

复杂度 $O(M + N\log(N))$。



```cpp
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int M = 4e5 + 10;
vector<int> e[N];
vector<int> own[N];
vector<int> w[N];

int dep[N];
int out[N];
int nxt[N], ansl[N], rnk[N];
ll sum[N];
int ids[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        e[u].push_back(v);
        w[u].push_back(l);
        own[v].push_back(u);
        out[u]++;
    }
    vector<int> cur_len_nodes;
    vector<int> nxt_len_nodes;
    for (int i = 1; i <= n; i++) {
        if (!out[i]) {
            dep[i] = 1;
            cur_len_nodes.push_back(i);
            sum[i] = 0;
        }
    }
    int cur_len = 1;
    while (!cur_len_nodes.empty()) {
        // 获取长度为 1 的路径...
        ++cur_len;
        for (int v: cur_len_nodes) {
            for (int u: own[v]) {
                if (--out[u] == 0) {
                    nxt_len_nodes.push_back(u);
                    dep[u] = cur_len;
                    ansl[u] = 1e9 + 7;
                }
            }
        }
        for (int u: nxt_len_nodes) {
            for (int i = 0; i < e[u].size(); i++) {
                int v = e[u][i];
                int l = w[u][i];
                if (dep[v] == cur_len - 1) {
                    if (l < ansl[u]) {
                        ansl[u] = l;
                        nxt[u] = v;
                        sum[u] = sum[v] + l;
                    } else if (l == ansl[u] && rnk[v] < rnk[nxt[u]]) {
                        // rnk 针对同级
                        nxt[u] = v;
                        sum[u] = sum[v] + l;
                    }
                }
            }
        }
        int cnt = 0;
        for (int u: nxt_len_nodes) {
            ids[++cnt] = u;
        }
        sort(ids + 1, ids + cnt + 1, [&](const int& a, const int& b) {
            if (ansl[a] != ansl[b])
                return ansl[a] < ansl[b];
            return rnk[nxt[a]] < rnk[nxt[b]];
        });
        for (int i = 1; i <= cnt; i++) {
            rnk[ids[i]] = i;
        }
        swap(cur_len_nodes, nxt_len_nodes);
        nxt_len_nodes.clear();
        // 稍后计算 rnk
    }
    for (int i = 1; i <= n; i++) {
        printf("%d %lld\n", dep[i] - 1, sum[i]);
    }
    return 0;
}


```

---

## 作者：lfxxx (赞：2)

由于不存在长度为无限的路径，所以不难发现这是一个 DAG。

然后第一问是最长路，直接拓扑排序时 dp 就可以了。

第二问要找字典序最小的最长路，所以考虑怎么比较字典序的问题，比较字典序时一般使用的工具是二分哈希，即二分最长公共前缀并且用哈希来判定，这里同理，我们考虑倍增出每一个点的前驱节点，然后记录一个到目前这个节点为止的哈希值，那么就可以快速地求出一段路径的哈希值，因为预处理的是倍增出数组，所以直接在倍增数组上跳最长公共前缀即可。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
//#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 5e5+114;
const int base = 1145141;
int fa[maxn][25];
int val[maxn],d[maxn],Hash[maxn];
int _pow[maxn];
int lst_E[maxn];
int Out[maxn];
vector<int> edge[maxn],fedge[maxn];
int n,m;
map<int,int> w[maxn];
void topo(){
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(Out[i]==0){
			q.push(i);
		}
	}
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int v:fedge[u]){
			Out[v]--;
			if(Out[v]==0){
				vector<int> L;
				int mx=0;
				for(int lst:edge[v]){
					if(d[lst]>mx){
						L.clear();
						mx=d[lst];
						L.push_back(lst);
					}
					else if(d[lst]==mx) L.push_back(lst);
				}
				d[v]=mx+1;
				int mi=L.back();
				L.pop_back();
				for(int lst:L){
					if(w[v][lst]!=w[v][mi]){
						if(w[v][lst]<w[v][mi]) mi=lst;
						else continue;
					}
					int U=mi,V=lst;
					for(long long i=23;i>=0;i--){
						if((Hash[mi]-Hash[fa[U][i]])==(Hash[lst]-Hash[fa[V][i]])){
							U=fa[U][i];
							V=fa[V][i];
						}
					}
					if(lst_E[U]>lst_E[V]){
						mi=lst;
					}
				}
				fa[v][0]=mi;
				for(int i=1;i<=23;i++){
					fa[v][i]=fa[fa[v][i-1]][i-1];
				}
				Hash[v]=(Hash[mi]+w[mi][v]*_pow[d[v]]);
				val[v]=val[mi]+w[mi][v];
				lst_E[v]=w[mi][v];
				q.push(v);
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	_pow[0]=1;
	for(int i=1;i<=m;i++) _pow[i]=_pow[i-1]*base;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v>>w[u][v];
		w[v][u]=w[u][v];
		Out[u]++;
		edge[u].push_back(v);
		fedge[v].push_back(u);
	}
	topo();
	for(int i=1;i<=n;i++) cout<<d[i]<<' '<<val[i]<<'\n';
	return 0;
}

```


---

## 作者：mRXxy0o0 (赞：1)

# 题意

求 DAG 上最长路径时走过的边的字典序最小。输出两者之和。

# 分析

DAG 上最长路，显然是拓扑排序，考虑怎么求字典序。显然，直接存下来是肯定不行的，我们考虑一种优美的思路。

倍增。明显，讨论的这个点之前的所有点都是已经确定的。因此，我们可以维护每个点的倍增数组，以此找到两个转移边集的 $lcp$ 。在实现方面，可以参考树上倍增，记录一个深度和哈希值，然后比较第一个不同位置的边权即可。

实际上，这种思路可以拓展，这里不用保证是一个 DAG，仅仅有向图就可以了，思路类似。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2e5+10,M=4e5+10;
const ull sd=13331;
int n,m,h[N],ne[M],e[M],w[M],idx,du[N],q[N],hh,tt,f[N][20],dp[N],dep[N];
ll s[N];
ull g[N][20],pw[N];
bool vis[N];
inline void add(int u,int v,int x){
	ne[++idx]=h[u],h[u]=idx,e[idx]=v,w[idx]=x;
}
inline bool check(int u,int v){
	for(int i=19;~i;--i){
		if(dep[u]>(1<<i)&&g[u][i]==g[v][i]) u=f[u][i],v=f[v][i];
	}
	return g[u][0]>g[v][0];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,z;i<=m;++i){
		scanf("%d%d%d",&x,&y,&z);
		add(y,x,z);
		++du[x];
	}
	hh=1;
	pw[0]=1;
	for(int i=1;i<=n;++i){
		if(!du[i]) q[++tt]=i;
		pw[i]=pw[i-1]*sd;
	}
	while(hh<=tt){
		int u=q[hh++];
		dep[u]=dep[f[u][0]]+1;
		s[u]=s[f[u][0]]+g[u][0];
		for(int i=1;1<<i<dep[u];++i){
			f[u][i]=f[f[u][i-1]][i-1];
			g[u][i]=g[f[u][i-1]][i-1]*pw[1<<(i-1)]+g[u][i-1];
		}
		for(int i=h[u];i;i=ne[i]){
			int v=e[i];
			if(dp[v]<dp[u]+1) dp[v]=dp[u]+1,f[v][0]=u,g[v][0]=w[i];
			else if(dp[v]==dp[u]+1&&(w[i]<g[v][0]||(w[i]==g[v][0]&&check(f[v][0],u)))) dp[v]=dp[u]+1,f[v][0]=u,g[v][0]=w[i];
			--du[v];
			if(!du[v]) q[++tt]=v;
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d %lld\n",dp[i],s[i]);
	}
	return 0;
}
```


---

## 作者：Jerrywang09 (赞：0)

首先原图是一个 DAG，果断想到拓扑排序，先找到拓扑序。

然后倒序枚举拓扑序上的每个点 $u$。然后找到 $u$ 的走得最长且标签最小的出边，在从这些出边走出的路径中选字典序最小的一条。果断想到倍增哈希。

```cpp
// Title:  Minimum Longest Trip
// Source: USACO23DEC Gold
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll unsigned long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=200010, lg=18, inf=INT_MAX, B=13331;
using namespace std;

int n, m, q[N], hh=1, tt, deg[N];
vector<pii> g[N];
int d[N], to[N][lg+1]; ll pw[N], sum[N], h[N][lg+1];
int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%d%d", &n, &m);
    pw[0]=1; rep(i, 1, n) pw[i]=pw[i-1]*B;
    rep(i, 1, m)
    {
        int u, v, l; scanf("%d%d%d", &u, &v, &l);
        g[u].push_back({v, l}), deg[v]++;
    }
    rep(i, 1, n) if(!deg[i]) q[++tt]=i;
    while(hh<=tt)
    {
        int u=q[hh++];
        for(auto [v,l]:g[u]) if(!--deg[v]) q[++tt]=v;
    }
    for(int i=n; i; i--)
    {
        int u=q[i], mn=inf, w=0;
        for(auto [v,l]:g[u]) d[u]=max(d[u], d[v]+1);
        for(auto [v,l]:g[u]) if(d[u]==d[v]+1) mn=min(mn, l);
        for(auto [v,l]:g[u]) if(d[u]==d[v]+1 && l==mn)
        {
            if(!w) {w=v; continue;}
            int vv=v, ww=w;
            for(int i=lg; i>=0; i--)
            {
                if(to[vv][i] && h[vv][i]==h[ww][i])
                    vv=to[vv][i], ww=to[ww][i];
            }
            if(h[vv][0]<h[ww][0])
                w=v;
        }
        if(g[u].size()) sum[u]=sum[w]+mn;
        to[u][0]=w, h[u][0]=mn;
        rep(i, 1, lg)
            to[u][i]=to[to[u][i-1]][i-1],
            h[u][i]=h[u][i-1]*pw[1<<i-1]+h[to[u][i-1]][i-1];
    }
    rep(i, 1, n) printf("%d %lld\n", d[i], sum[i]);
    
    return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定一个有以下特性的图。
- 有向
- 有 $n$ 个点 $(2\le n\le2\times10^5)$
- 有 $m$ 条有权值的边 $(1\le m\le4\times10^5)$
- 只能从编号大的点到编号小的点

现在问对于每一个点，从它开始最多能遍历边的数量以及这些边的权值之和。这里还有一个要求，对于一个点，如果它的遍历尽可能边有多种选择，择其中按遍历顺序边的权值的字典序最小的一种。
# 思路
其实解决第一个问题也就是**求最多遍历边的数量**是很容易解决的，我们只需要建立一个反图，从最小的点开始遍历，不断更新全图就可以了。更难的其实是**求字典序最小的边遍历序**。

对于这个问题，首先我们肯定是从图的最深处开始往上递推（整体来说就是从小往大）然后扩散到全图。

关于具体如何推导，这里有用到大佬 0000pnc 的思路。

我们用到一个优先队列去存储每一层边权值的大小顺序，然后等到了要推导这一层的点的最小字典序路径时，取出来并且赋值，这样就可以通过赋值的大小判断它的优劣。

最后我们只需先找到直接相连儿子节点中边权最小的点集，然后再在这个点集中去找上文提到的编号最大的就可以得到最优的一个点了，然后把推导完的点加入优先队列继续递推，最终可以得到答案。
# 实现
```cpp
#include<iostream>
#include<vector>
#include<algorithm> 
#include<queue>
#define int long long
#define N 200005
using namespace std;
vector<pair<int,int>> r[N],h[N];
int n,m,f[N],ans[N],vv[N],id[N],val[N];
bool cmp(int a,int b){return f[a]<f[b];}
void dfs(int u){
	for(auto t:r[u]){
		int v=t.first,w=t.second;
		if(f[u]+1>f[v])f[v]=f[u]+1,dfs(v);
	}vv[u]=1;
}struct node{int w,val,v;};
bool operator<(node a,node b){
	if(a.w<b.w)return true;
	else if(a.w>b.w)return false;
	return a.val>b.val;
}void bfs(){
	priority_queue<node> q;
	int cnt=0,d;
	for(int i=1;i<=n;i++){
		int u=id[i];
		if(d!=f[u]){d=f[u];while(!q.empty()){val[q.top().v]=++cnt;q.pop();}}
		if(f[u]){
			int Minw=2147483647,Maxv=0;
			for(auto t:h[u])if(f[u]-1==f[t.first])Minw=min(Minw,t.second);
			for(auto t:h[u])if(f[u]-1==f[t.first]&&t.second==Minw)Maxv=max(Maxv,val[t.first]);
			for(auto t:h[u])
				if(f[u]-1==f[t.first]&&t.second==Minw&&val[t.first]==Maxv){
					ans[u]=ans[t.first]+t.second;
					q.push({t.second,val[t.first],u});
					break;
				}
		}else q.push({0,0,u});
	}
}signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)scanf("%lld%lld%lld",&u,&v,&w),r[v].push_back({u,w}),h[u].push_back({v,w});
	for(int i=1;i<=n;i++){
		if(!vv[i])dfs(i);
		id[i]=i;
	}sort(id+1,id+n+1,cmp);
	bfs();
	for(int i=1;i<=n;i++)printf("%lld %lld\n",f[i],ans[i]);
	return 0;
}
```

---

## 作者：LincW (赞：0)

这道题如果去掉字典序最小的要求，解法就是显然的：记忆化搜索一下，继承后续最长的相邻节点就行。

瓶颈就是比较两个节点的后续的字典序的复杂度。直接暴力做单次查询是 $O(m)$ 的，显然无法接受。

所以可以想想字典序比较算法有什么。

比较容易想到的是哈希+二分，这样就可以将查询复杂度降到 $O(\log m)$。

但这样还有问题，时间复杂度够了，但是哈希数组还是开不下（对于每个节点都要开一个 $O(m)$ 的数组）。

考虑使用倍增记录路径信息（途经点、标签和、哈希值），然后这道题就做完了。

时间复杂度 $O(n\log^2 m+m)$，空间复杂度 $O(n\log m+m)$。

参考代码（常数有点大）：

```cpp
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pil;
const int N=200000+5;
const int LOG2N=20+5;
const int P=1001015413;
const int B=13331;
vector<int> adj[N];
vector<int> id[N];
int len[N];
ll sum[N];
int to[N][LOG2N];
int tid[N][LOG2N];
ll p[N][LOG2N];
int lg[N];
ll pw[N];
bool vis[N];
int n,m;
int get_to(int pt,int i)
{
	if(1<<lg[i]==i) return to[pt][lg[i]];
	else return get_to(to[pt][lg[i]],i-(1<<lg[i]));
}
int get_tid(int pt,int i)
{
	if(1<<lg[i]==i) return tid[pt][lg[i]];
	else return get_tid(to[pt][lg[i]],i-(1<<lg[i]));
}
ll get_p(int pt,int i)
{
	if(1<<lg[i]==i) return p[pt][lg[i]];
	else return (get_p(to[pt][lg[i]],i-(1<<lg[i]))*pw[1<<lg[i]]%P+p[pt][lg[i]])%P;
}
int read()
{
	int res=0;
	char c=0;
	while((c>'9' || c<'0'))
	{
		c=getchar();
	}
	while(c<='9' && c>='0')
	{
		res*=10;
		res+=(ll)(c-'0');
		c=getchar();
	}
	return res;
}
bool cmp(int pt1,int pt2,int l,int r)
{
	if(l==r)
	{
		return get_tid(pt1,l)<get_tid(pt2,l);
	}
	int mid=(l+r)>>1;
	if(get_p(pt1,mid)!=get_p(pt2,mid))
	{
		return cmp(pt1,pt2,l,mid);
	}
	else
	{
		return cmp(pt1,pt2,mid+1,r);
	}
}
void dfs(int cur)
{
	vis[cur]=1;
	int cb=0,cw=1000000005; 
	for(int i=0;i<adj[cur].size();++i)
	{
		if(!vis[adj[cur][i]])
		{
			dfs(adj[cur][i]);
		}
		if(len[cb]<len[adj[cur][i]])
		{
			cb=adj[cur][i];
			cw=id[cur][i];
		}
		else if(len[cb]==len[adj[cur][i]])
		{
			if(id[cur][i]<cw)
			{
				cb=adj[cur][i];
				cw=id[cur][i];
			}
			else if(id[cur][i]==cw)
			{
				if(len[cb]!=0&&cmp(adj[cur][i],cb,1,len[cb]))
				{
					cb=adj[cur][i];
					cw=id[cur][i];
				}
			}
		}
	}
	if(cw==1000000005)
	{
		return;
	}
	for(int i=1;i<=lg[len[cb]+1];++i)
	{
		to[cur][i]=get_to(cb,(1<<i)-1);
	}
	to[cur][0]=cb;
	for(int i=1;i<=lg[len[cb]+1];++i)
	{
		tid[cur][i]=get_tid(cb,(1<<i)-1);
	}
	tid[cur][0]=cw;
	for(int i=1;i<=lg[len[cb]+1];++i)
	{
		p[cur][i]=(get_p(cb,(1<<i)-1)*B%P+cw)%P;
	}
	p[cur][0]=cw%P;
	sum[cur]=sum[cb]+cw;
	len[cur]=len[cb]+1;
}
int main()
{
	n=read();
	m=read();
	pw[0]=1;
	lg[1]=0;
	for(int i=2;i<=n;++i)
	{
		lg[i]=lg[i/2]+1;
	} 
	for(int i=1;i<=n;++i)
	{
		pw[i]=pw[i-1]*B%P;
	}
	for(int i=1;i<=m;++i)
	{
		int a,b,l;
		a=read();
		b=read();
		l=read();
		adj[a].push_back(b);
		id[a].push_back(l);
	}
	for(int i=1;i<=n;++i)
	{
		if(!vis[i])
		{
			dfs(i);
		}
	}
	for(int i=1;i<=n;++i)
	{
		printf("%d %lld\n",len[i],sum[i]);
	}
	return 0;
}
```

另外感觉这个做法不太好写。

---

## 作者：SFlyer (赞：0)

首先，最长的路径长度非常好求（直接 topo sort）。要确保字典序最小，就要确定

- 第一个边的权值是可能中的最小的。

- 满足第一个条件后，所有路径当中去掉第一个边，字典序最小的。

发现解决最长路径为 $d$ 的问题，转化成了如果能求出为 $d-1$ 的所有点的最小字典序的 rank，就可以了。其次发现，topo sort 的时候一定是 $d-1$ 在 $d$ 前面。所以可以在出现 $d$ 之前就预处理好 $d-1$ 的 rank。

因此就做完了。具体看代码。$\mathcal{O}(N\log N)$。


```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 4e5+5;
const int inf = 2e9;

int n,m,dis[N],in[N],rnk[N];
ll sum[N];
vector<pair<int,int> > g[N],rg[N]; 
pair<ll,ll> ans[N];

struct node {
	int vl,rk,id;
	bool operator < (const node &b) const {
		return vl!=b.vl?vl<b.vl:rk<b.rk;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=1; i<=m; i++){
		int a,b,l;
		cin>>a>>b>>l;
		in[a]++;
		rg[a].push_back({b,l});
		g[b].push_back({a,l});
	}
	memset(dis,-1,sizeof dis);
	int cur=0;
	queue<int> q;
	vector<node> v;
	for (int i=1; i<=n; i++){
		if (!in[i]){
			dis[i]=0;
			q.push(i);
		}
	}
	while (!q.empty()){
		int x=q.front();
		q.pop();
		if (cur!=dis[x]){
			sort(v.begin(),v.end());
			for (int i=0; i<v.size(); i++){
				rnk[v[i].id]=i;
			}
			v.clear();
			cur=dis[x];
		}
		node it={inf,inf,x};
		ll mx=0,psum=0;
		for (auto p : rg[x]){
			int y=p.first,l=p.second;
			node itt={l,rnk[y],x};
			if (itt<it&&mx==dis[y]+1 || mx<dis[y]+1){
				psum=sum[y]+l;
				mx=dis[y]+1;
				it=itt;
			}
		}
		ans[x]={mx,psum};
		sum[x]=psum;
		v.push_back(it);
		for (auto p : g[x]){
			int y=p.first,l=p.second;
			in[y]--;
			if (!in[y]){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	for (int i=1; i<=n; i++){
		cout<<ans[i].first<<" "<<ans[i].second<<"\n";
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：0)

考虑暴力，建返图后把到达每个点的字典序最小的权值序列记录下来，然后暴力比较即可。时间复杂度 $O(n^2)$。

考虑优化暴力，求最短路本身就是 $O(n)$ 的，考虑从记录序列的角度优化。比较两个序列的字典序本质上就是找到它们的 LCP 下一位看大小关系，而一个点的权值序列只会继承它的某一个入边，不难想到可持久化线段树。

类似线段树维护二进制，我们用线段树维护到每个点的权值序列。对于从 $x$ 更新到 $y$（记 $f$ 表示最短路）：

- 若 $f_x+1>f_y$，则 $y$ 直接继承 $x$，并且往线段树里面加入权值。

- 若 $f_x+1=f_y$，那么我们需要找到它们的 LCP。可以通过经典的二分+哈希的方法，用线段树维护权值序列的哈希值，在线段树上二分找到第一个不相同的位，判断哪个更大即可。

时空复杂度都是 $O(m \log n)$，实现上会有一些细节，不过很好打，而且这题不卡哈希。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, m, p, x, y, z, cnt, base=31, flag, pw[200010], t[200010], h[200010], in[200010], f[200010];
const int mo = 1e9 + 7;
struct node{
	int x, y, z, next;
}d[400010];
struct segment{
	int l, r, s, siz;
	ll tot;
}seg[10000010];
void add(int x, int y, int z){
	d[++p].y = y, d[p].z = z, d[p].next = h[x], h[x] = p;
}
map <int, int> mp;
queue <int> q;
void pushup(int p){
	seg[p].s = (seg[seg[p].r].s + 1LL * seg[seg[p].l].s * pw[seg[seg[p].r].siz] % mo) % mo;
	seg[p].siz = seg[seg[p].l].siz + seg[seg[p].r].siz;
	seg[p].tot = seg[seg[p].l].tot + seg[seg[p].r].tot;
}
void modify(int &p, int lst, int l, int r, int x, int y){
	seg[p=++cnt]=seg[lst];
	if (l == r){
		seg[p].s = seg[p].tot = y, seg[p].siz = 1;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(seg[p].l, seg[lst].l, l, mid, x, y);
	else modify(seg[p].r, seg[lst].r, mid+1, r, x, y);
	pushup(p);
}
void modify2(int &p, int l, int r, int x, int y){
	seg[++cnt] = seg[p], p = cnt;
	if (l == r){
		seg[p].s = seg[p].tot = y, seg[p].siz = 1;
		if (!y) seg[p].siz = 0;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify2(seg[p].l, l, mid, x, y);
	else modify2(seg[p].r, mid+1, r, x, y);
	pushup(p);
}
void query(int X, int Y, int l, int r){
	if (l == r){
		if (seg[X].s < seg[Y].s) flag = 1;
		return ;
	}
	int mid = l + r >> 1;
	if (seg[seg[X].r].s != seg[seg[Y].r].s) query(seg[X].r, seg[Y].r, mid+1, r);
	else if (seg[seg[X].l].s != seg[seg[Y].l].s) query(seg[X].l, seg[Y].l, l, mid);
}
int main(){
	scanf ("%d%d", &n, &m);
	for (int i=1; i<=m; i++){
		scanf ("%d%d%d", &x, &y, &z);
		add(y, x, z);
		in[x] ++;
	}
	for (int i=1; i<=n; i++){
		if (in[i] == 0) q.push(i);
	}
	pw[0] = 1;
	for (int i=1; i<=n; i++){
		pw[i] = 1LL * pw[i-1] * base % mo;
	}
	while (!q.empty()){
		int x = q.front(); q.pop();
		for (int i=h[x]; i; i=d[i].next){
			int y = d[i].y;
			if (f[x] + 1 > f[y]){
				f[y] = f[x] + 1;
				modify(t[y], t[x], 1, n, f[y], d[i].z);
			}
			else if (f[x] + 1 == f[y]){
				modify2(t[x], 1, n, f[y], d[i].z);
				flag = 0;
				query(t[x], t[y], 1, n);
				if (flag){
					t[y] = t[x];
				}
				modify2(t[x], 1, n, f[y], 0); 
			}
			if (--in[y] == 0) q.push(y);
		}
	}
	for (int i=1; i<=n; i++){
		printf ("%d %lld\n", f[i], seg[t[i]].tot);
	}
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：0)

首先把每个点为起点的最长路径求出来，以此来建出分层图，满足最长路径的限制。

对于分层图的每一层，对每个点开始的路径字典序排序。分层图从终点向起点处理，对于当前层，每个点都连向能连的字典序最小的点。连完之后对当前层的点进行排序，对于两个点，若这两个点标签不同则直接比较，若相同则直接按照指向的点的大小关系比较即可。

标签之和顺带维护即可。

瓶颈为排序，时间复杂度 $O(n\log n)$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#include<random>
#define int long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,m,k,a[N],in[N],dis[N],sum[N],to[N],val[N],b[N];
vector<pii>e[N],E[N];
vector<int>id[N];
queue<int>q;
int cmp(int x,int y){
	if(val[x]!=val[y])
		return val[x]<val[y];
	return b[to[x]]<b[to[y]];
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u].push_back(mkp(v,w));
		in[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!in[i])q.push(i);
	int tim=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		a[++tim]=u;
		for(pii i:e[u]){
			int v=i.fi;
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	for(int i=n;i>=1;i--){
		int u=a[i],res=0;
		for(pii i:e[u]){
			int v=i.fi,w=i.se;
			res=max(res,dis[v]+1);
		}
		dis[u]=res;
		id[res].push_back(u);
		for(pii i:e[u]){
			int v=i.fi,w=i.se;
			if(dis[v]+1==res){
				if(E[u].empty()){
					E[u].push_back(i);
					continue;
				}
				int p=E[u][0].se;
				if(p<w)continue;
				if(p==w){
					E[u].push_back(i);
					continue;
				}
				E[u].clear();
				E[u].push_back(i);
			}
		}
		k=max(k,res);
	}
	b[n+1]=n+1;
	for(int i=1;i<=k;i++){
		for(int u:id[i]){
			int p=n+1;
			val[u]=E[u][0].se;
			for(pii j:E[u]){
				int v=j.fi;
				if(b[v]<b[p])
					p=v;
			}
			to[u]=p;
			sum[u]=val[u]+sum[p];
		}
		sort(id[i].begin(),id[i].end(),cmp);
		for(int j=0;j<id[i].size();j++)
			b[id[i][j]]=j;
	}
	for(int i=1;i<=n;i++)
		cout<<dis[i]<<' '<<sum[i]<<'\n';
	return 0;
}
```

---

