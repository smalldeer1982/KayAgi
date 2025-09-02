# Apple Tree Traversing

## 题目描述

有一棵 $n$ 个点的苹果树，每个结点上有一棵苹果。你有一张白纸。

你将要在苹果树上穿梭，重复做以下事情直到苹果树上没有苹果：
- 选择一条路径 $(u,v)$，满足这条路径上所有点上都有苹果。
- 拿走这条路径上的所有苹果，设你这次拿了 $d$ 个苹果，在你的纸上依次写下三个数字 $d$，$u$ 和 $v$。

称结束后你的纸上的数字构成的数列为 $a$。输出可能的字典序最大的 $a$。

## 说明/提示

在第一组数据中，我们进行以下操作：
- 选择路径 $(4,3)$，拿走结点 $1,3,4$ 上面的苹果，在纸上写下 $3,4,3$。
- 选择路径 $(2,2)$，拿走结点 $2$ 上面的苹果，在纸上写下 $1,2,2$。

最终形成了 $a=(3,4,3,1,2,2)$，可以证明这是字典序最大的合法结果。

By chenxi2009

## 样例 #1

### 输入

```
6
4
1 2
1 3
1 4
4
2 1
2 4
2 3
5
1 2
2 3
3 4
4 5
1
8
6 3
3 5
5 4
4 2
5 1
1 8
3 7
6
3 2
2 6
2 5
5 4
4 1```

### 输出

```
3 4 3 1 2 2 
3 4 3 1 1 1 
5 5 1 
1 1 1 
5 8 7 2 4 2 1 6 6 
5 6 1 1 3 3```

# 题解

## 作者：沉石鱼惊旋 (赞：7)

# 题意

给定一棵 $n$ 个点的树，每次选一个路径 $u\to v$，依次写下 $\operatorname{distance}(u,v),u,v$ 这三个数。

显然你会写下不超过 $3n$ 个数。找到最大字典序的三元组序列。

多测，$1\leq t\leq 10^4$，$1\leq n,\sum n\leq 1.5\times 10^5$。

# 前言

我爆标了。我爆标了。我爆标了。

第一次爆非朴素题的标！！！

# 做法

省流：编一个比 std 更聪明的暴力，发现是 $\operatorname{polylog}$ 的。

就这个题意很显然每次在当前所有连通块里找到直径，然后把直径删掉。如果你这一步不选直径，显然选直径字典序更大。

![](https://cdn.luogu.com.cn/upload/image_hosting/e5f6idp5.png)

用样例举个例子。我们现在删掉了 $6\to 2$ 的这条直径。

然后 $\{7\}$ 这个连通块的直径是可以直接算的，一开始 DFS 一次就好。朴素的树形 DP 求解树的直径的思路。

$\{1,8\}$ 这个块你去暴力更新 $1$。考虑树形 DP 求解直径，就是一个点然后找两个儿子下去的最长链拼起来的。

具体的怎么暴力更新，就是你每次答案是 $(d,u,v)$ 然后你把 $\operatorname{lca}(u,v)$ 到 $\operatorname{root}$ 的链，给他对应这个子树的最长链修改掉。

分析一下这个做法的复杂度。然后发现根本卡不满每次走 $\mathcal O(n)$ 个祖先，设直径组成是 $x+1+y\ (u\to \operatorname{lca}\to v)$，然后 $\operatorname{lca}\to \operatorname{root}$ 是 $z$，那么你发现这个一定存在 $x+y\geq \max\{x,y\}+z$，取到 $x=y=z$ 才是最劣情况。

所以说如果你 $\operatorname{lca}\to \operatorname{root}$ 这个过程卡满的话每次树要删掉 $2n/3$ 个点。

然后就维护每个点往下的最长链每次取最长的出来作为直径重复这个过程。每次花费不超过 $d$ 的代价使得 $n$ 减少 $2d$。

除去 `std::set` 动态维护最大值，剩下的是线性的。复杂度 $\mathcal O(n\log n)$。

# 代码

<https://codeforces.com/contest/2107/submission/318957073>

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
void solve()
{
    int n;
    read(n);
    vector<vector<int>> a(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        read(u, v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<set<array<int, 2>, greater<array<int, 2>>>> s(n + 1);
    int times = 0;
    vector<int> fa(n + 1);
    auto dfs = [&](auto self, int u, int p) -> array<int, 2>
    {
        fa[u] = p;
        s[u].insert({0, u});
        for (int v : a[u])
        {
            if (v == p)
                continue;
            auto r = self(self, v, u);
            s[u].insert({r[0] + 1, r[1]});
        }
        return *s[u].begin();
    };
    dfs(dfs, 1, 0);
    priority_queue<array<int, 4>> q;
    for (int i = 1; i <= n; i++)
    {
        if (s[i].size() == 1)
        {
            int u = (*s[i].begin())[1];
            int v = i;
            q.push({(*s[i].begin())[0] + 1, max(u, v), min(u, v), i});
        }
        else
        {
            int u = (*s[i].begin())[1];
            int v = (*++s[i].begin())[1];
            q.push({(*s[i].begin())[0] + (*++s[i].begin())[0] + 1, max(u, v), min(u, v), i});
        }
    }
    int cnt = 0;
    while (cnt < n)
    {
        auto [d, u, v, i] = q.top();
        q.pop();
        bool ok = 1;
        if (s[i].empty())
            continue;
        // cerr << d << ' ' << u << ' ' << v << ' ' << i << '\n';
        if (s[i].size() == 1)
        {
            int tu = (*s[i].begin())[1];
            int tv = i;
            ok &= d == (*s[i].begin())[0] + 1;
            ok &= u == max(tu, tv);
            ok &= v == min(tu, tv);
        }
        else
        {
            int tu = (*s[i].begin())[1];
            int tv = (*++s[i].begin())[1];
            ok &= d == (*s[i].begin())[0] + (*++s[i].begin())[0] + 1;
            ok &= u == max(tu, tv);
            ok &= v == min(tu, tv);
        }
        if (!ok)
        {
            if (s[i].size() == 1)
            {
                int u = (*s[i].begin())[1];
                int v = i;
                q.push({(*s[i].begin())[0] + 1, max(u, v), min(u, v), i});
            }
            else
            {
                int u = (*s[i].begin())[1];
                int v = (*++s[i].begin())[1];
                q.push({(*s[i].begin())[0] + (*++s[i].begin())[0] + 1, max(u, v), min(u, v), i});
            }
            continue;
        }
        // cerr << d << ' ' << u << ' ' << v << ' ' << i << '\n';
        // cerr << s[i].size() << '\n';
        int lca = i;
        write(d, ' ');
        write(u, ' ');
        write(v, ' ');
        // cerr << d << ' ' << u << ' ' << v << '\n';
        int t = 0;
        int id = u;
        while (u != lca)
        {
            s[u].clear();
            u = fa[u];
            cnt++;
            t++;
        }
        int mx = t;
        t = 0;
        int tv = v;
        while (v != lca)
        {
            s[v].clear();
            v = fa[v];
            cnt++;
            t++;
        }
        if (t > mx || t == mx && tv > id)
            id = tv, mx = t;
        s[lca].clear();
        cnt++;
        while (fa[lca])
        {
            // cerr << lca << ' ' << mx << ' ' << id << '\n';
            if (s[fa[lca]].count({mx + 1, id}))
            {
                s[fa[lca]].erase({mx + 1, id});
                if (!s[lca].empty())
                {
                    auto r = *s[lca].begin();
                    s[fa[lca]].insert({r[0] + 1, r[1]});
                }
            }
            else
                break;
            lca = fa[lca];
            mx++;
        }
    }
    putchar('\n');
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：znzryb (赞：7)

## 思路讲解

题意就是所有点只能经过一次（选择一次），构造出字典序最大的 $(dis,u,v)$ 序列，输出这个序列。

注意到，距离是放在第一位的，所以我们肯定优先选择距离最大的。那在树上路径距离最大的是什么？树的直径呗。不过这个树的直径的取法需要优先选择大的起始点和终止点。

然后删除直径后，这张图就不联通了，只要在每个子图中我们遵循这种删除规律即可，最后形成的 ans 数组根据字典序规则排序即可。

以下是样例五的图示展示，第一层删完后，变为了两个子图，这两个子图仍然按照规则选择直径，删除直径上的点，整张图被删完后程序结束。

![](https://cdn.luogu.com.cn/upload/image_hosting/aolx2meb.png)
## 时间复杂度分析

枚举总量为，
$$
n+(n-l_1)+(n-l_1-l_2)+\cdots+(n-l_c-\cdots-l_i-\cdots -l_1)
$$
即是，
$$
(n\times c) -(l_1 \times c)-(l_2 \times (c-1))-\cdots-l_c
$$
其中 $n$ 为点的数量，$l_i$ 为第 i 层的直径总数，c 为总层数。枚举总量在逐层下降是因为每层选择的直径上的点会被删除。

n 是给定的，那么我们假设 c 最大，那么 c 最大的情况是什么呢？

c 最大的情况，就是我们每层只能删除一条直径，也就是说该图在删除直径的过程中一直保持着联通状态。把层数卡满的图可以这样构造，注意到,$分枝直径的点的数量≤\lfloor直径的点的数量/2\rfloor$，如果大于这个限制，该分枝就要被删除了。

![](https://cdn.luogu.com.cn/upload/image_hosting/793p3m0v.png)

那么近似的，我们可以得到。

$$
x+\frac{x}{2}+\frac{x}{2^2}+\cdots+\frac{x}{2^c}=n
$$

由于 $\lfloor\frac{x}{2^c}\rfloor$必须大于 $0$，我们知道 $2^c≤x<2^{c+1}$。

那么不妨令 $x=2^{c+1}$。

$$
2^{c+1}+2^c+\cdots+2=n
$$

运用等比数列求和公式。

$$
2\times(2^{c+1}-1)=n
$$

因此，$c\approx \log(n)$。

故该算法的总体时间复杂度为 $O(n \log(n))$。
## AC代码

https://codeforces.com/contest/2107/submission/318737306
    
```cpp
// Problem: D. Apple Tree Traversing
// Contest: Codeforces - Codeforces Round 1023 (Div. 2)
// URL: https://codeforces.com/contest/2107/problem/D
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// by znzryb
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define all(vec) vec.begin(),vec.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define fi first
#define se second
#define pb push_back
#define SZ(a) ((int) a.size())
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define getFro(vec) (vec.empty()?0:vec.front())
#define getBac(vec) (vec.empty()?0:vec.front())
#define debug(var) cerr << #var <<":"<<var<<"\n";
#define deShow(var) cerr << #var <<":";
#define DEBUG(variable) \
    do { \
        std::cerr << #variable << ":"; \
        for (const auto& elem : variable) { \
            std::cerr << elem << " "; \
        } \
        std::cerr << "\n"; \
    } while (0)
#define uniVec(var) \
    do { \
        sort(var.begin(),var.end());\
        var.resize(unique(var.begin(),var.end())-var.begin());\
    } while (0)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<ll,ll> pll;
typedef array<ll,2> arr;
typedef double DB;
typedef pair<DB,DB> pdd;
typedef pair<ll,bool> plb;
constexpr ll MAXN=static_cast<ll>(1e6)+10,INF=static_cast<ll>(1e18)+3;
constexpr ll mod=static_cast<ll>(1e9)+7;
constexpr double eps=1e-8;

ll N,M,K,T;
vector<ll> g[MAXN];
bool vis[MAXN]/*,isVal[MAXN]*/;
vector<arr> disNode;
vector<ll> needDel;
ll st,ed,d;
set<ll> nodes;
bool removed[MAXN];

void dfs(ll x,ll d){
  disNode.pb({d,x});
  vis[x]=true;
  FOR(i,0,SZ(g[x])-1){
    ll node=g[x][i];
    if(vis[node]) continue;
    if(removed[node]) continue;
    dfs(node,d+1);
  }
}
bool dfsDia(ll x){	// 一个比较简单的树上dp？
  vis[x]=true;
  if(x==ed){
    needDel.pb(ed);
    return true;
  }
  bool rec=false;
  FOR(i,0,SZ(g[x])-1){
    ll node=g[x][i];
    if(vis[node]) continue;
    if(removed[node]) continue;
    rec|=dfsDia(node);
  }
  if(rec) needDel.pb(x);
  return rec;
}

inline void init(){
  disNode.clear(),needDel.clear();
  FOR(i,1,N){
    vis[i]=false;
  }
}

inline bool cmp(const array<ll,3> &a,const array<ll,3> &b){
  if(a[0]!=b[0]) return a[0]>b[0];
  if(a[1]!=b[1]) return a[1]>b[1];
  return a[2]>b[2];
}

inline void solve(){
  cin>>N;
  // 所有点只能经过一次（选择一次）
  // 构造出字典序最大的(d,u,v)序列，输出这个序列
  // d要大，u要大，v要大
  disNode.clear(),needDel.clear(),nodes.clear();
  FOR(i,1,N){
    vis[i]=false;
    nodes.insert(i);
    g[i].clear();
    removed[i]=false;
  }
  FOR(i,1,N-1){
    ll u,v;
    cin>>u>>v;
    g[u].pb(v);
    g[v].pb(u);
  }
  if(N==1){	// 特判
    cout<<"1 1 1\n";
    return;
  }
  dfs(1,0);
  sort(all(disNode));
  
#ifdef LOCAL
  deShow(disNode)
    FOR(i,0,SZ(disNode)-1){
      cerr<<disNode[i][0]<<" "<<disNode[i][1]<<"\n";
    }
#endif

  st=disNode.back()[1];
  init();
  dfs(st,0);
  sort(all(disNode));
  ed=disNode.back()[1];
  d=disNode.back()[0];
  init();
  dfsDia(st);
  vector<array<ll,3>> ans;
  ans.pb({d+1,max(st,ed),min(st,ed)});
  for(const auto &node:needDel){
    nodes.erase(node);
    removed[node]=true;
  }
  for(const auto &node:nodes){
    vis[node]=false;
  }
  while(!nodes.empty()){
    disNode.clear(),needDel.clear();
    dfs(*nodes.begin(),0);
    sort(all(disNode));
    st=disNode.back()[1];
    FOR(i,0,SZ(disNode)-1){
      vis[disNode[i][1]]=false;
    }
    disNode.clear(),needDel.clear();
    dfs(st,0);
    sort(all(disNode));
    ed=disNode.back()[1];
    d=disNode.back()[0];
    ans.pb({d+1,max(st,ed),min(st,ed)});
    FOR(i,0,SZ(disNode)-1){
      vis[disNode[i][1]]=false;
    }
    dfsDia(st);
    FOR(i,0,SZ(disNode)-1){
      vis[disNode[i][1]]=false;
    }
    for(const auto &node:needDel){
      nodes.erase(node);
      removed[node]=true;
    }
  }
  sort(all(ans),cmp);
  FOR(i,0,SZ(ans)-1){
    cout<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<" ";
  }
  cout<<"\n";
#ifdef LOCAL
    DEBUG(needDel);
    cerr<<"\n";
#endif
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--){
    solve();
  }
  // solve();
  return 0;
}
/*
AC
https://codeforces.com/contest/2107/submission/318737306
*/
```

---

## 作者：sunkuangzheng (赞：7)

## $\mathcal O(n \sqrt n)$ 做法

为了让字典序最大，我们每次操作会贪心的选择一条端点最大的直径。找端点最大的直径可以直接在两遍 dfs 时对 pair $(dep_u,u)$ 取 $\max$。

考虑每次暴力 dfs 找出直径删除后递归剩余部分，我们将证明这样暴力递归的复杂度是 $\mathcal O(n \sqrt n)$ 的。

- 树的所有直径交于一点或一条边，因此删除直径后剩余部分的直径长度至少减少 $1$。注意这个点不一定是点分治里树的重心。
- 令 $l_i$ 表示第 $i$ 层递归的最大直径长度。显然 $\sum l_i \le n$ 且序列 $l$ 单调递减，因此 $l$ 中的元素个数是 $\mathcal O(\sqrt n)$ 级别的。
- 每一层递归的枚举总量是 $\mathcal O(n)$，因此总复杂度为 $\mathcal O(n \sqrt n)$。

容易根据上述证明构造一组卡满复杂度的数据：将长度为 $1,3,5,7,\ldots,\sqrt n$ 的链的中点相连即可。

## $\mathcal O(n \log n)$ 做法

该做法最早在验题时由 @[沉石鱼惊旋](https://www.luogu.com.cn/user/516346) 发现，orz /bx。

考虑 dp 求解树的直径的过程，设 $f_u$ 表示从 $u$ 往下的子树最长链，$g_u$ 表示和 $f_u$ 不在一个子树的最长链，则树的直径是 $\max \limits_{u=1}^n \{f_u + g_u\}$。

关键观察是，如果某次树的直径是 $(u,v)$，那么路径 $(\operatorname{lca}(u,v),\text{root})$ 的有效长度一定不超过 $(u,v)$（有效指的是从 lca 向上遇到第一个已经删掉的点就退出）。这就意味着暴力更改路径 $(\operatorname{lca}(u,v),\text{root})$ 的有效部分的复杂度仍然是均摊线性的。

于是做法就很简单了：对于每个节点 $u$ 用 `std::set` 存储其每个儿子子树的最长链即可维护 $f_u,g_u$，全局维护一个堆存储所有点的 $f_u,g_u$ 信息。每次找到一条直径 $(u,v)$ 时，暴力修改路径 $(u,v)$ 和 $(\operatorname{lca}(u,v),\text{root})$ 的有效部分。修改总次数为 $\mathcal O(n)$，因此总复杂度为 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
using pi = pair<int,int>;
using ti = tuple<int,int,int,int>;
int T,n,u,v,del[N],fa[N],ct;  vector<int> g[N]; set<pi> t[N];
void dfs(int u,int f){
    t[u].emplace(0,u),fa[u] = f;
    for(int v : g[u]) if(v != f){
        dfs(v,u); auto [x,y] = *--t[v].end();
        t[u].emplace(x+1,y);
    }
}ti gt(int u){
    assert(t[u].size() >= 1);
    if(t[u].size() == 1) return {0,u,u,u};
    auto [x,y] = *--t[u].end();
    auto [p,q] = *--(--t[u].end());
    return {x + p,max(y,q),min(y,q),u};
}void los(){
    cin >> n;
    for(int i = 1;i <= n;i ++) g[i].clear(),del[i] = 0,t[i].clear();
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    ct = 0,dfs(1,0); priority_queue<ti> q;
    for(int i = 1;i <= n;i ++) q.emplace(gt(i));
    while(q.size()){
        auto [di,u,v,d] = q.top(); q.pop();
        if(del[d] || ti{di,u,v,d} != gt(d)) continue;
        cout << di + 1 << " " << u << " " << v << " ";
        while(u != d) del[u] = 1,u = fa[u];
        while(v != d) del[v] = 1,v = fa[v];
        del[d] = 1; 
        auto [x,y] = *--t[d].end();
        while(fa[d] && !del[fa[d]]){
            d = fa[d];
            if(t[d].count({++x,y})) t[d].erase({x,y});
            q.emplace(gt(d));
            if(fa[d]){
                auto [a,b] = *--t[d].end();
                t[fa[d]].emplace(a+1,b);
            }
        }
    }cout << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

