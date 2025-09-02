# [PA 2025] 重金属 / Heavy Metal

## 题目背景

PA 2025 R5B.

## 题目描述


扩音系统由 $n$ 个路由器和 $m$ 个放大器组成。麦克风连接到第 $1$ 号路由器，扬声器连接到第 $n$ 号路由器。

每个放大器连接两个路由器（输入和输出），**增益系数**为 $w_i$。路由器的最大带宽为 $p_i$。  

麦克风的信号功率为 $1$。配置系统，使信号在放大器、路由器中传输。信号经过放大器后，功率会乘以该放大器的增益系数，但是为了避免烧毁，通过路由器的信号功率必须**不大于** $p_i$。

**信号可以多次通过同一路由器或放大器**。最终将信号传输到扬声器（到达 $n$ 号路由器），在路由器不烧毁的前提下，最大化信号的功率。求出可能的最大功率。



## 说明/提示



### 样例解释

$114(514)$ 表示，信号到达第 $114$ 个路由器时，功率为 $514$。

- 样例 $1$ 解释：

最优路径：$1(1)\to 1(1\times 2)\to 2(2\times 3)\to 1(6\times 37)\to 2(222\times 3)$。

- 样例 $2$ 解释：

最优路径：$1(1)\to 1(2)\to 1(4)\to 1(8)\to 2(8)\to 2(24)\to 2(72)\to 2(216)\to 3(216)\to 3(1080)$。  

- 样例 $3$ 解释：

最优路径：$1\to 1(2)\to 1(4)\to 2(4)$。

- 样例 $4$ 解释：路由器 $2$ 一定会被烧毁，所以无法传到路由器 $2$。

### 数据范围

- $1\le n,\sum n\le 100$；
- $1\le m,\sum m\le 200$；
- $1\le p_i\le 10^9$；
- $1\le a_i,b_i\le n$；
- $1\le w_i\le 10^9$。



## 样例 #1

### 输入

```
4
2 3
250 1000
1 1 2
1 2 3
2 1 37
3 5
500 800 1100
1 1 2
1 2 1
2 2 3
2 3 1
3 3 5
2 2
4 4
1 1 2
1 2 1
2 1
10 10
1 2 1000000000```

### 输出

```
666
1080
4
-1```

# 题解

## 作者：rainygame (赞：2)

一道很好的 meet-in-middle 题。

首先看到这个乘法，那么大概率就和值域 $V$ 有关了，但是“最多只经过 $O(\log V)$ 条边权不为 $1$ 的边”貌似没有什么用。观察到 $n$ 很小，小到 $O(n\sqrt V)$ 都是可以接受的。那么可以考虑把路径分成两段边权不超过 $\sqrt V$ 的部分，分别处理，最后再枚举中间连接的边统计答案，这就有了一个 meet-in-middle 的壳子。

考虑统计的是 $u\rightarrow v$ 这条边，边权为 $w$。那么应该需要维护两个信息：$f_{i,j}$ 表示是否有一条 $1\rightarrow i$ 的路径边权积为 $j$；$g_{i,j}$ 表示所有 $i\rightarrow n$ 的边权积为 $j$ 的路径中，可以接受的 $1\sim i$ 的最大边权积。求出 $f$ 和 $g$ 只有，对 $f_u$ 和 $g_v$ 双指针一下就可以更新答案了。

$f$ 是好求的。考虑在反图上求出 $g$，对于反图上的一条边 $u\rightarrow v$，可以用 $\min\{\lfloor\dfrac{g_{u,j}}{w}\rfloor,p_v\}$ 更新 $g_{v,jw}$。需要类似 Dijkstra 的转移才能保证正确性，注意优先队列是从大到小排。

时间复杂度为 $O(n\sqrt V\log m)$，平衡一下可以做到 $O(n\sqrt{V\log m})$，但是我懒。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 105
#define MAXK 32005

int t, n, m; int p[MAXN];
bool f[MAXN][MAXK], vis[MAXN][MAXK]; int h[MAXN][MAXK];
vector<pair<int, int>> e[MAXN], g[MAXN];

struct Node{int u, st, d; bool operator<(Node b)const{return d < b.d;}};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    for (cin >> t; t; --t){
        cin >> n >> m; for (int i(1); i<=n; ++i) cin >> p[i];
        for (int u, v, w; m; --m) cin >> u >> v >> w, e[u].push_back({v, w}), g[v].push_back({u, w});
        queue<pair<int, int>> que; que.push({1, 1}); f[1][1] = 1;
        while (que.size()){
            int u(que.front().first), st(que.front().second); que.pop();
            for (auto i: e[u]){
                int v(i.first), w(i.second); if (w*st<=min(MAXK-1ll, p[v]) && !f[v][w*st]) f[v][w*st] = 1, que.push({v, w*st});
            }
        }
        priority_queue<Node> pq; pq.push({n, 1, h[n][1]=p[n]});
        while (pq.size()){
            int u(pq.top().u), st(pq.top().st); pq.pop(); if (vis[u][st]) continue; vis[u][st] = 1;
            for (auto i: g[u]){
                int v(i.first), w(i.second);
                if (w*st < MAXK && min(p[v], h[u][st]/w) > h[v][st*w]){
                    pq.push({v, st*w, h[v][st*w]=min(p[v], h[u][st]/w)});
                }
            }
        }
        int ans(-1);
        for (int i(1); i<=n; ++i) for (auto j: e[i]){
            int v(j.first), w(j.second);
            for (int x(1), y(MAXK-1); x<MAXK; ++x){
                for (; y && h[v][y] < w*x; --y); if (y && f[i][x]) ans = max(ans, y*w*x);
            }
        }
        cout << (n == 1 && ans == -1 ? 1 : ans) << '\n';
        for (int i(1); i<=n; ++i){
            for (int j(1); j<MAXK; ++j) vis[i][j] = f[i][j] = h[i][j] = 0;
            e[i].clear(); e[i].shrink_to_fit(); g[i].clear(); g[i].shrink_to_fit();
        }
    }

    return 0;
}
```

---

## 作者：123456xwd (赞：1)

直接去 $dp$ 需要记录此时的值，但这个值太大了，记录不下啊。

那么，我们最终答案的路径上，必定存在一条边， $(u,v,w)$，满足 $1\to u$ 和 $v\to n$ 的路径上的边权乘积都 $\le \sqrt{10^9}$，考虑枚举这条边。

先考虑求解 $1\to u$ 路径上的问题，设 $f(u,x)$ 表示从 $1$ 到 $u$ 的合法路径中，是否有一个边权乘积和为 $x$，$f$ 的转移是简单的，$x$ 小的给大的转移即可，注意 $x=1$ 的情况。

然而，$u\to n$ 路径上的问题略有不同，因为我们并不知道他到 $u$ 的时候经过的路径的乘积，不妨设 $g(u,x)$ 表示 $u\to n$ 的合法路径中，乘积和为 $x$ 时，要求 $1\to u$ 的路径乘积和最大为多少。

考虑转移，若有边 $(u,v,w)$，那么 $g(u,x\times w)\gets \min(p_u,g(v,x)/w)$。

这个转移就比较复杂了，考虑用最短路转移，每次取最大值来更新，但时间复杂度会多一个 $\log$。

那么，不妨通过调整值域使得两边平衡，$f(u,x)$ 记录 $\le B$ 的，$g(u,x)$ 记录 $\le \frac{V}{B}$ 的。

那么，这部分的时间复杂度为 $\mathcal{O}(n(B+\frac{10^9}{B}\log n))$ 的，

考虑合并，我们枚举 $l$，表示 $1\to u$ 路径乘积和为 $l$。

若 $f(u,l)=1$，那么枚举边 $(u,v,w)$，那么我们想要找到一个最大的 $r$，满足 $g(v,r)\ge l\times w$，若有，那么对于答案的贡献为 $l\times w\times r$。

不妨把合法的 $l\times w$ 从小到大排序，然后对于每个 $v$ 都维护一个指针即可。

时间为 $\mathcal{O}(Bm+\frac{10^9}{B}n)$。

总的时间为 $\mathcal{O}(B(n+m)+\frac{10^9}{B}(n\log n+n))$。

那么，$B$ 大概取到 $40000$ 左右。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=200+5,B=40100,C=25000,INF=0x3f3f3f3f;

int n,m,p[N];
vector<pii> G[N],E[N];
vector<int> e[N];
bool f[N][B+5];
int g[N][C+5];
bool cmp(pii x,pii y){return x.se<y.se;}
priority_queue<pair<int,pii> > q;
bool vis[N][C+5];
vector<int> A[N];
stack<int> s;
void solve(){
    n=rd(),m=rd();
    for(int i=1;i<=n;i++) p[i]=rd();
    for(int i=1;i<=m;i++){
        int u=rd(),v=rd(),w=rd();
        G[u].p_b(m_p(v,w));
        E[v].p_b(m_p(u,w));
        if(w==1) e[u].p_b(v);
    }
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end(),cmp),memset(f[i],0,sizeof(f[i]));
    f[1][1]=1;
    for(int x=1;x<=B;x++){
        for(int u=1;u<=n;u++) if(f[u][x]) s.push(u);
        while(!s.empty()){
            int u=s.top();s.pop();
            for(auto v : e[u]) if(p[v]>=x&&!f[v][x]) f[v][x]=1,s.push(v);
        }
        for(int u=1;u<=n;u++){
            if(!f[u][x]) continue;
            for(auto [v,w] : G[u]) if(x*w<=B&&x*w<=p[v]) f[v][x*w]=1; 
        }
    }
    for(int i=1;i<=n;i++)memset(g[i],-INF,sizeof(g[i])),memset(vis[i],0,sizeof(vis[i]));
    g[n][1]=p[n];
    q.push(m_p(p[n],m_p(n,1)));
    while(!q.empty()){
        auto [u,x]=q.top().se;q.pop();
        if(vis[u][x]) continue;
        vis[u][x]=1;
        for(auto [v,w] : E[u]){
            if(x*w<=C&&g[v][x*w]<min(p[v],g[u][x]/w)){
                g[v][x*w]=min(p[v],g[u][x]/w);
                q.push(m_p(g[v][x*w],m_p(v,x*w)));
            }
        }
    }
    for(int l=1;l<=B;l++){
        for(int u=1;u<=n;u++){
            if(!f[u][l]) continue;
            for(auto [v,w] : G[u]) A[v].p_b(w*l);
        }
    }
    int ans=-1;
    for(int u=1,r;u<=n;u++){
        sort(A[u].begin(),A[u].end());r=C;
        for(auto w : A[u]){
            while(r>=1&&g[u][r]<w) r--;
            if(r) ans=max(ans,r*w);
        }
    }
    printf("%lld\n",ans);
}

void clean(){
    for(int i=1;i<=n;i++) A[i].clear(),G[i].clear(),E[i].clear(),e[i].clear();
}
signed main(){
    int T=rd();
    while(T--) solve(),clean();
    return 0;
}
```

---

