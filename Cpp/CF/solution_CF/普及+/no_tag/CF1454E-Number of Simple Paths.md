# Number of Simple Paths

## 题目描述

给你一张 $ n $ 个节点 $ n $ 条边的**无向连通简单图**， 请你计算出这张图中长度大于等于 $ 1 $ 的不同的**简单路径**的数量， 保证图中没有自环和重边。其中， 简单路径中的节点必须互不相同， 一条路径的长度定义为它所包含的边的数量。

两条路径仅有方向不同时被认为是同一条， 例如 $ 1 -> 2 $ 和 $ 2 -> 1 $。

## 样例 #1

### 输入

```
3
3
1 2
2 3
1 3
4
1 2
2 3
3 4
4 2
5
1 2
2 3
1 3
2 5
4 3```

### 输出

```
6
11
18```

# 题解

## 作者：胖头鱼学员 (赞：3)

# CF1454E

[CF传送门](http://codeforces.com/problemset/problem/1454/E)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1454E)

## $QuestionMeaning$

给定一颗基环树，问图中的大于$1$的不同简单路径数量。

## $Solution$

考虑容斥：

图中不同简单路径数量 = 树上简单路径数量 - 环上简单路径数量, 即：

$$
C = \frac{n \times (n - 1)}{2} - \frac{siz \times siz}{2}
$$

按公式计算即可。

## $Code$
```
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 2e5 + 1;

int T, n, x, y, p;
long long ans, sum;

struct V {
  bool e;
  long long s;
  vector<int> y;
} v[kMaxN];

void Init() {
  ans = sum = 0;
  for (int i = 1; i <= n; i++) {
    v[i].e = v[i].s = 0;
    v[i].y.clear();
  }
}

bool Dfs1(int u, int fa) {
  if (v[u].e) {
    return p = u;
  }
  v[u].e = 1;
  for (int i = 0; i < v[u].y.size(); i++) {
    int to = v[u].y[i];
    if (to != fa && Dfs1(to, u)) {
      v[u].e = p;
      p = (u != p) * p;
      return 1;
    }
  }
  return v[u].e = 0;
}

void Dfs2(int u, int fa) {
  for (int i = 0; i < v[u].y.size(); i++) {
    int to = v[u].y[i];
    if (to != fa && !v[to].e) {
      Dfs2(to, u);
      ans += v[to].s * v[u].s;
      v[u].s += v[to].s;
    }
  }
  ans += v[u].s;
  v[u].s++;
}

void Solve() {
  scanf("%d", &n);
  Init();
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &x, &y);
    v[x].y.push_back(y);
    v[y].y.push_back(x);
  }
  Dfs1(1, 0);
  for (int i = 1; i <= n; i++) {
    if (v[i].e) {
      Dfs2(i, 0);
      ans += sum * v[i].s * 2;
      sum += v[i].s;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    Solve();
  }
  return 0;
}
```

---

## 作者：两年打铁 (赞：3)

这里有一个非常显然又麻烦的做法

对于两个点之间的路径，如果经过环的话，是有两条路径的。

那我们先缩点，考虑以环为根的树，注意像下图这样的1和2是要算在同一颗子树里的


![](https://cdn.luogu.com.cn/upload/image_hosting/dexi0b43.png)

因为他们之间的路径没有经过环。

具体要找出来的话只需要拎出环上每个点连的点的个数即可


------------


对于连向环的子树我们设$sz[i]$为当前子树的大小，设环上的点个数为$t$

当前子树的贡献为

#### 到其他子树的贡献
$sz[i]*(n-sz[i]-t)*2$(经过环）
#### 子树内
$sz[i]*(sz[i]-1)/2$
#### 到环上的点
$sz[i]+sz[i]*(t-1)*2$(单独加一个是因为子树到相连的环上的那个点的路径只有一条）

然后这题就做完了

```cpp
#include<bits/stdc++.h>
#define huan putchar('\n')
#define kong putchar(' ')
#define bug puts("QWQ")
#define swap mswap
#define int long long 
using namespace std;
 
inline int max(int x,int y)
{
	return x>y?x:y;
}
 
inline int min(int x,int y)
{
	return x<y?x:y;
}
 
const int big=1e9;
 
inline void mswap(int &x,int &y)
{
    x^=y^=x^=y;
}
 
template <class T>
inline void read(T &x)
{
    x=0;register char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
 
template<class T>
void write(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}
 
template <class T>
inline void wrl(T x)
{
    write(x);
    huan;
}
 
template<class T>
inline void wrs(T x)
{
    write(x);
    kong;
}
 
 
const int MX=1e5+233;
const int N=4e5+233;
 
int n,h[N],dfn[N],low[N];
int t,num,id[N],cnt,sz[N];
int cc[N];
vector<int>g[N];
 
int pp[N];
struct dd
{
	int begin,end,nt;
}e[N<<1];
 
 
inline void add(int begin,int end)
{
	++t;
	e[t].end=end;
	e[t].begin=begin;
	e[t].nt=h[begin];
	h[begin]=t;
}
stack <int >st;
void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++num;
	st.push(x);
	for(register int i=h[x];i;i=e[i].nt)
	{
		int u=e[i].end;
		if(u==fa)continue;
		if(!dfn[u])
		{
			tarjan(u,x);
			low[x]=min(low[x],low[u]);
		}
		else if(!id[u])low[x]=min(low[x],dfn[u]);
	}
    if(dfn[x]==low[x])
    {
        id[x]=++cnt;
        cc[cnt]++;
        while(st.top()!=x)
        {
            id[st.top()]=cnt;
            cc[cnt]++;
            st.pop();
        }
        st.pop();
    }
}
 
void dfs(int x,int fa)
{
	sz[x]=1;
	for(register int i=0;i<(int)g[x].size();++i)
	{
		int u=g[x][i];
		if(u==fa)continue;
		dfs(u,x);
		sz[x]+=sz[u];
	}
}
 
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n);
		t=0;
		num=0;
		cnt=0;
		int oo=0;
		for(register int i=1;i<=n;++i)
		{
			h[i]=0;
			cc[i]=0;
			dfn[i]=0;
			id[i]=0;
			g[i].clear();
		}
		int x,y;
		for(register int i=1;i<=n;++i)
		{
			read(x);
			read(y);
			add(x,y);
			add(y,x);
		}
		for(register int i=1;i<=n;++i)
		{
			if(!dfn[i])tarjan(i,0);
		}
		
		long long  ans=0;
		int k;
		for(register int i=1;i<=cnt;++i)
		{
			if(cc[i]>1)
			{
				k=i;
				break;
			}
		}
		for(register int i=1;i<=t;++i)
		{
			if(id[e[i].begin]!=id[e[i].end])
			{
				g[id[e[i].begin]].push_back(id[e[i].end]);
			}
		}
		dfs(k,0);
		long long ss=0;
		for(register int i=1;i<=n;++i)
		{
			if(id[i]==k)
			{
				int cnt=0;
				for(register int j=h[i];j;j=e[j].nt)
				{
					if(id[e[j].end]!=k)
					cnt+=sz[id[e[j].end]];
				}
				if(cnt)
				pp[++oo]=cnt;
			}
		}
		for(register int i=1;i<=oo;++i)
		{
			ss+=pp[i]*(n-pp[i]-cc[k])*2;
			ans+=1ll*pp[i]*(pp[i]-1)/2+pp[i]+1ll*pp[i]*(cc[k]-1)*2;
		}
		ans+=1ll*cc[k]*(cc[k]-1);
		write(ans+ss/2);
		huan;
	}
	return 0;
}
```


---

## 作者：oymz (赞：2)

## 题意

有一个 $N$ 个点，$N$ 条边的无向图，求简单路径数除 $2$。

## 思路

$N$ 个点，$N$ 条边，很容易发现这是一棵基环树。

接着，可以对简单路径两端的点的关系进行分类讨论。

- 简单路径两端的点在同一颗子树上。则两点之间有 $1$ 条路径；

- 简单路径两端的点在不同一颗子树上。则两点之间有 $2$ 条路径；

```cpp
     o     o
      \   /
       \ /
  o     o
   \   /
    \ /
     o
    / \
   /   \
  /     \
 o       o
  \     /
   \   /
    \ /
     o
    / \
   /   \
  o     o
       / \
      /   \
     o     o

```
所以，可以用拓扑排序搜出环上的点，再对每一个环上的点搜出他的子树大小，最后组合数求解。

**时间复杂度 —— $O(N)$。**

- 拓扑排序 —— $O(N)$；

- 搜子树大小 —— $O(N)$。

**空间复杂度 —— $O(N)$。**

- 标记点是否在环上 —— $O(N)$；

- 子树大小 —— $O(N)$。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;

vector<int> G[N];

ll t, n;
ll d[N], sz[N], vis[N];

void Kahn(){
  queue<int> q;
  for(int i = 1; i <= n; i++){
    if(d[i] == 1){
      q.push(i);
    }
  }
  while(!q.empty()){
    int u = q.front();
    q.pop();
    vis[u] = 1;
    for(int v : G[u]){
      d[v]--;
      if(d[v] == 1){
        q.push(v);
      }
    }
  }
}

void dfs(int u, int f){
  sz[u] = 1;
  for(int v : G[u]){
    if(v != f && vis[v]){
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
}

void Init(){
  for(int i = 1; i <= n; i++){
    G[i].clear();
    sz[i] = d[i] = vis[i] = 0;
  }
}

void Solve(){
  Init();
  cin >> n;
  for(int i = 1, u, v; i <= n; i++){
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
    d[v]++, d[u]++;
  }
  Kahn();
  ll ans = 0;
  for(int i = 1; i <= n; i++){
    if(!vis[i]){
      dfs(i, 0);
      ans += sz[i] * (sz[i] - 1) + sz[i] * (n - sz[i]) * 2;
    }
  }
  cout << ans / 2 <<'\n';
}

int main(){
  cin >> t;
  while(t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Remake_ (赞：2)

闲话：考场上一眼就看出来的伸臂题，但是由于样例过水导致花了1h才过掉，最终错失AK。

考虑一个简单容斥，我们知道当所有点都在一个环上时每两点之间都有$2$条简单路径，这时总路径为$\frac{n(n-1)}{2}\times2=n(n-1)$条。

那么答案也可以看做$n(n-1)-$两点间只有一条简单路径的点对

那么两点间只有一条简单路径的点对有哪些呢？我们知道环上的一个点及其子树内的所有点两两之间互只有$1$条简单路径。

所以我们设环上的所有点为$s_i$，则答案为$n(n-1)-\sum\frac{size_{s_i}(size_{s_i-1})}{2}$

找环的话用topo即可：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, u, v, du[200005], ans, siz[200005], tmp;
bool vis[200005];
vector<long long> e[200005];
queue<long long> tpo, emp;
void findSIZE(int dep, int fa)
{
    siz[dep] = 1;
    for (int i = 0; i < e[dep].size(); i++)
    {
        if (e[dep][i] != fa)
        {
            findSIZE(e[dep][i], dep);
            siz[dep] += siz[e[dep][i]];
        }
    }
}
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            e[i].clear();
            du[i] = 0;
            siz[i] = 0;
            vis[i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
            ++du[u];
            ++du[v];
        }
        tpo = emp;
        for (int i = 1; i <= n; i++)
            if (du[i] == 1)
                tpo.push(i);
        while (tpo.size())
        {
            int tp = tpo.front();
            tpo.pop();
            for (int i = 0; i < e[tp].size(); i++)
                if (--du[e[tp][i]] == 1)
                    tpo.push(e[tp][i]);
        }
        for (int i = 1; i <= n; i++)
            if (du[i] > 1)
                vis[i] = 1;
        for (int i = 1; i <= n; i++)
            if (vis[i])
            {
                tmp = 0;
                for (int j = 0; j < e[i].size(); j++)
                {
                    if (!vis[e[i][j]])
                    {
                        findSIZE(e[i][j], i);
                        tmp += siz[e[i][j]];
                    }
                }
                ans += tmp;
                ans += tmp * (tmp - 1) / 2;
            }
        cout << n * (n - 1) - ans << endl;
    }
}
```


---

## 作者：Tarsal (赞：2)

### 题目大意

一颗基环树，请你计算出这张图中长度大于等于 $1$ 的不同的简单路径的数量。

### 题解

我们遇到基环树，先去考虑树的情况。

首先，如果这题是树的话，那么所有的点两两之间的路径都必然是长度大于等于 $1$。

所以这时候的数量是: $\frac{n \times (n - 1)}{2}$ ($n$ 为树的节点数量)

再来考虑基环树的情况，首先有一种不可实现的做法就是，枚举边，然后看贡献，~~显然不可做~~

那么再考虑其他的做法。

是不是有个很显然的容斥？

有哪些边是不合法的？

是不是就是环上的点之间连边，这肯定有 $2$ 种不同的路径。

所以我们用总的减去不合法的即可。

答案即：$\frac{n \times (n - 1)}{2} - \frac{siz \times (siz - 1)}{2}$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid (l + r >> 1)
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i; i = edge[i].nxt)
int read() {
    char c = getchar(); int f = 1, x = 0;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
using namespace std;
const int maxn = 200010;
vector<int> w, v[maxn];
int x, y, fa[maxn], tag[maxn], siz[maxn], vis[maxn];
void dfs1(int i) {vis[i] = true;
	for(int j = 0; j < v[i].size(); ++ j) {
		int to = v[i][j];
		if(to == fa[i]) continue;
		if(vis[to]) x = to, y = i;
        else fa[to] = i, dfs1(to);
	}
}
void dfs2(int i, int fa) { siz[i] = 1;
	for(int j = 0; j < v[i].size(); ++ j) { int to = v[i][j];
		if(to == fa || tag[to]) continue;
		dfs2(to, i); siz[i] += siz[to];
	}
}
signed main() { int T = read();
	while(T --) { int n = read();
        Rep(i, 1, n) v[i].clear(), vis[i] = false, tag[i] = false;
	    Rep(i, 1, n) { int u = read(), w = read();
			v[u].push_back(w), v[w].push_back(u);
		} dfs1(1), w.clear();
		while(1) { w.push_back(x), tag[x] = true;
			if(x == y) break; x = fa[x];
		} int ans = 0;
		for(int i = 0; i < w.size(); ++ i) dfs2(w[i], 0), ans += siz[w[i]] * (siz[w[i]] - 1) / 2;
		for(int i = 0; i < w.size(); ++ i) ans += siz[w[i]] * (n - siz[w[i]]);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Lily_White (赞：1)

首先要注意到给出的图**是一棵基环树**！如果没有这个条件，那么这个问题就无法解决了。

现在有了这个条件，我们就可以分类讨论了。

下文我们设 $L$ 为环的长度。我们称所有不属于图中的唯一一个环的点为『树』。

- **从环上一点到环上另外一点：**  这种情况可以轻松得出有 $L(L-1)$ 个路径

- **从环上一点到树上一点：** 这种情况下，如果环上的点就是那棵树的接入点，则有一种。否则各有两种（按照两个方向绕），因此对答案的贡献是 $(2L-1)S$，其中 $S$ 为树的大小。

- **从树上一点到树上另一点：** 这种情况又要分两个情况讨论：

	+ **如果两个点属于同一个树：** 那么方案数为 $1$。
    + **否则：** 方案数为 $2$。
    
   因此，在这种情况下，要对答案加上的是这两种情况之和。我们可以先算后一种再减去前一种。
   
```cpp
// Problem: E. Number of Simple Paths
// Contest: Codeforces - Codeforces Round #686 (Div. 3)
// URL: https://codeforces.com/contest/1454/problem/E
// Written by RavenclawOIer on 11-24-2020

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define ttt template <typename T>
#define chmax(a, b) a = max(a, b)
#define int long long
#define chmin(a, b) a = min(a, b)
const int INF = 0x3f3f3f3f;
ttt inline void rd(T& x) {
  x = 0;
  T neg = 1;
  char c = 0;
  while (c < '0' || c > '9') {
    if (c == '-') neg = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - 48;
    c = getchar();
  }
  x *= neg;
}
const int N = 200020;
int n;
vector<int> g[N];
int vis[N];
vector<int> cyc;
bool incyc[N];
int fa[N];

int tsz[N];
int vc;
int cnt;
LL ans = 0;
void cleanup() {
  rep(i, n + 1) g[i].clear();
  rep(i, n + 1) vis[i] = 0;
  cyc.clear();
  vc = 0;
  //  memset(incyc, false, sizeof(incyc));
  //  memset(tsz, 0, sizeof(tsz));
  // memset(fa, 0, sizeof(fa));
  rep(i, n + 1) { incyc[i] = tsz[i] = fa[i] = 0; }
}
void dfs(int u) {
  vis[u] = ++vc;
  for (auto v : g[u]) {
    if (v == fa[u]) continue;
    if (vis[v]) {
      if (vis[v] < vis[u]) continue;
      cyc.push_back(v);
      for (; v != u; v = fa[v]) {
        cyc.push_back(fa[v]);
      }
    } else
      fa[v] = u, dfs(v);
  }
}

void dfs2(int u, int f) {
  cnt++;
  for (auto v : g[u]) {
    if (incyc[v] || v == f) continue;
    dfs2(v, u);
  }
}
void work() {
  ans = 0;
  for (auto x : cyc) incyc[x] = true;
  int cl = cyc.size();
  ans += cl * (cl - 1);
  //  cerr << ans << endl;
  int tot = 0;
  for (auto x : cyc) {
    cnt = 0;
    //    cerr << "x = "<< x << endl;
    dfs2(x, 0);
    //    cerr << cnt << endl;
    ans += (cnt - 1) * (cl - 1) * 2;
    tot += cnt - 1;
    tsz[x] = cnt - 1;
  }
  // cerr << ans << endl;
  // cerr << tot << endl;
  ans += tot * (tot - 1);
  ans += tot;
  for (auto x : cyc) {
    ans -= tsz[x] * (tsz[x] - 1) / 2;
  }
  printf("%lld\n", ans);
}
void solve() {
  //  cerr << "---\n";
  rd(n);
  repn(i, n) {
    int u, v;
    rd(u);
    rd(v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  work();
  cleanup();
}
signed main() {
  int T = 1;
  rd(T);
  while (T--) solve();
  return 0;
}
```

---

## 作者：紊莫 (赞：0)

>这么巧，上午刚看了基环树。

首先考虑断掉一条环上的边构成一棵树，那么树上这样的答案是很好计算的，答案即为 $n(n-1)$，然后考虑加上这个边，计算经过这条边的贡献，那么考虑环外的子树。  
![](https://cdn.luogu.com.cn/upload/image_hosting/wjb5mwj2.png)  

发现任意两个子树之间都可以经过这条红色边，那么答案加上两两相乘之积，这东西很板可以线性计算。  

当然根据题中的顺序要求，你需要将刚刚的答案除以二。  

基环树的代码有一点细节，可以参考我的[示例代码](https://www.luogu.com.cn/paste/1ynks6iv)。

---

