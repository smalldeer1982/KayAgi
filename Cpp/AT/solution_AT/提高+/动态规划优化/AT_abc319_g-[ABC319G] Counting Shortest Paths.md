# [ABC319G] Counting Shortest Paths

## 题目描述

对于一个有 $N$ 个顶点的无向完全图 $G$，进行如下操作：

> 对于每个 $i = 1, 2, \ldots, M$，删除连接顶点 $u_i$ 和顶点 $v_i$ 的无向边。

在操作后的 $G$ 中，判断是否存在从顶点 $1$ 到顶点 $N$ 的路径。如果存在，请求出从顶点 $1$ 到顶点 $N$ 的最短路径的个数，并对 $998244353$ 取模。

这里，从顶点 $1$ 到顶点 $N$ 的最短路径是指所有从顶点 $1$ 到顶点 $N$ 的路径中，所经过的边数最少的路径。

## 说明/提示

## 限制条件

- $2 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq \min\lbrace 2 \times 10^5, N(N-1)/2 \rbrace$
- $1 \leq u_i, v_i \leq N$
- $u_i \neq v_i$
- $i \neq j \implies \lbrace u_i, v_i \rbrace \neq \lbrace u_j, v_j \rbrace$
- 所有输入均为整数

## 样例解释 1

操作后的 $G$ 中，从顶点 $1$ 到顶点 $N$ 的最短路径包含 $3$ 条边，共有如下 $3$ 条路径：

- 顶点 $1 \rightarrow$ 顶点 $2 \rightarrow$ 顶点 $3 \rightarrow$ 顶点 $6$
- 顶点 $1 \rightarrow$ 顶点 $2 \rightarrow$ 顶点 $5 \rightarrow$ 顶点 $6$
- 顶点 $1 \rightarrow$ 顶点 $4 \rightarrow$ 顶点 $5 \rightarrow$ 顶点 $6$

## 样例解释 2

操作后的 $G$ 中没有任何边，因此不存在从顶点 $1$ 到顶点 $N$ 的路径，输出 `-1`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 7
4 3
1 3
2 4
1 6
4 6
5 1
6 2```

### 输出

```
3```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
-1```

# 题解

## 作者：RiceFruit (赞：15)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_g)
## 题目大意

给你一张 $n$ 个点的完全图和 $m$ 条边，让你求出该完全图删除这 $m$ 条边后最短路径条数。

## 思路

考虑对于每个点，按照与 $1$ 的距离分层，相同距离的在同一层，样例 $1$ 的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/j1cr5svg.png)

其中 $1$ 在第 $1$ 层，$2,4$ 在第 $2$ 层，$3,5$ 在第 $3$ 层，$6$ 在第 $4$ 层。

接下来考虑如何求出每个点和 $1$ 号点的距离。

我们考虑 `bfs`，记 `set` 维护当前未被访问的点，取出队首后，枚举补图中所有与它有连边的点，如果他们在集合中，则将他们标记，遍历完后，没有被标记的点就是可以转移到的下一层的点。

然后考虑如何统计方案数。

显然，$f_{v \in to_u}=\sum f_u$，其中满足 $dis[v]=dis[u]+1$。考虑如何在正确的时间复杂度内求得它。注意到删除的边只有 $m$ 条，可以考虑总的贡献减去删除的边的贡献。具体实现方法就是先把所有的 $f_v$ 赋值成 上一层的点的 $f$ 值之和。然后对于上一层的点连出去的所有需要删除的边，如果终点在这一层中，则减去这个 $f_x$。最后输出 $f_n$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200200,mod=998244353;
inline int read();
int n,m,sum;
set<int>G[N];
set<int>p[N];
int f[N];
int dis[N];
set<int>S,S1;
queue<int>q;
signed main(){
	n=read(),m=read();
	for(int i=2;i<=n;i++)
		S.insert(i);
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		G[u].insert(v);
		G[v].insert(u);
	}
	q.push(1);
	dis[1]=1;
	while(q.size()){
		S1=S;
		int u=q.front();q.pop();
		for(int x:G[u]){
			if(S1.find(x)!=S1.end())
				S1.erase(x);
		}
		for(int v:S1){
			dis[v]=dis[u]+1;
			q.push(v);
			S.erase(v);
		}
	}
	if(!dis[n]){
		puts("-1");
		return 0;
	}
	f[1]=sum=1;
	for(int i=1;i<=n;i++)
		p[dis[i]].insert(i);
	for(int i=2;i<=dis[n];i++){
		for(int x:p[i])
			f[x]=sum;
		for(int x:p[i-1]){
			for(int y:G[x]){
				if(p[i].find(y)!=p[i].end())
					(f[y]+=mod-f[x])%=mod;
			}
		}
		sum=0;
		for(int x:p[i])
			(sum+=f[x])%=mod;
	}
	printf("%lld\n",f[n]);
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
```

---

## 作者：hzjnsy (赞：10)

鲜花：有个 shaber 叫[蒟蒻·廖子阳](https://www.luogu.com.cn/user/539211)，赛后过 G，望周知。

声明：本做法笔者从 Cu 大佬 [matrix_ok](https://www.luogu.com.cn/user/592690) 处得到启发，并自己口胡了计数的部分。

**[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_g)**

> - 给出一张 $n$ 个点的无向完全图，边权均为 $1$，删去 $m$ 条边，求新图上 $1$ 到 $n$ 的最短路条数。
>
> - $n,m\le 2\times 10^5$。

要做最短路计数，肯定要先求最短路，但是边数爆炸。不过我们这么想，若不删边，就是每个点向 $[1,n]$ 区间内的点连边（自环无所谓，因为不优没贡献）。点向区间连边，不难想到线段树优化建图。不删边的时候，**千万别像某个 shaber 一样只考虑删边的情况，先越界，然后又忘记连边**。

若删边，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pwdcon7d.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)

则是向橙色的四段区间连边，用 $()$ 和 $[]$ 表示端点的开闭。**千万别像某个 shaber 一样搞错边界**。

好那么最短路求出来了，如何计数？考虑对点 $u$ 进行最短路计数（求 $cnt_u$），由于边权为 $1$，因此前驱的最短路一定为 $dis_u-1$，所以将所有点按照最短路从小到大排序，开一个桶 $tot$ 维护 $tot_d = \sum\limits_{dis_x=d}cnt_x$，先令 $cnt_u=tot_{dis_u-1}$。**千万别像某个 shaber 一样，到达不了的点还计数，结果访问 $\inf - 1$ 的下标越界了**。但是可能某些 $dis_v=dis_u-1$ 的点 $v$ 和 $u$ 之间的连边被删了，那么枚举以 $u$ 为顶点的被删掉的边，单独减去那些点的贡献。

时间复杂度为 $\mathcal{O}((n+m)\log^2n)$，空间复杂度为 $\mathcal{O}((n+m)\log n)$。线段树优化建图部分贺了[板子](https://codeforces.com/problemset/submission/786/222656336)，所以代码比较抽象，而且这题时间可以用 01 BFS 优化到 $\mathcal{O}((n+m)\log n)$。

**[评测记录](https://atcoder.jp/contests/abc319/submissions/45419760)**

```cpp
#pragma GCC optimzie("Ofast")
#include<bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define fi first 
#define se second 
#define mp make_pair
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
using namespace std;
const int N=2.5e5+5,inf=0x3f3f3f3f3f3f3f3f, mod = 998244353;
int n,m,id[N],dis[N<<3], cnt[N], tot[N];
bool vis[N<<3];
vector<pii>g[N<<3];
vector<int>h[N];
struct node{
    int v,w;
    bool operator<(const node&o)const{
        return w>o.w;
    }
};
priority_queue<node>q;
struct item {
    int d, id;
    bool operator<(const item &o) const {
        return d < o.d;
    }
}a[N];
void build(int x,int l,int r){
    if(l==r){
        g[x].emplace_back(x+(n<<2),0);
        id[l]=x;
        return;
    }
    int mid=(l+r)>>1;
    g[x].emplace_back(ls(x),0);
    g[x].emplace_back(rs(x),0);
    g[ls(x)+(n<<2)].emplace_back(x+(n<<2),0);
    g[rs(x)+(n<<2)].emplace_back(x+(n<<2),0);
    build(ls(x),l,mid);
    build(rs(x),mid+1,r);
}
void link(int x,int l,int r,int ql,int qr,int k,int w){
    if (ql > qr) return;
    if(ql<=l&&r<=qr){
        g[k+(n<<2)].emplace_back(x,w);
        return;
    }
    int mid=(l+r)>>1;
    if(ql<=mid){
        link(ls(x),l,mid,ql,qr,k,w);
    }
    if(qr>mid){
        link(rs(x),mid+1,r,ql,qr,k,w);
    }
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>m;
    build(1,1,n);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        h[u].emplace_back(v), h[v].emplace_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        if (!h[i].size()) { link(1, 1, n, 1, n, id[i], 1); continue; };
        sort(h[i].begin(), h[i].end());
        if (h[i][0] > 1) link(1, 1, n, 1, h[i][0] - 1, id[i], 1);
        for (int j = 1; j < h[i].size(); ++j) {
            if (h[i][j] > h[i][j - 1] + 1) link(1, 1, n, h[i][j - 1] + 1, h[i][j] - 1, id[i], 1);
        }
        if (h[i][h[i].size() - 1] + 1 <= n) {
            link(1, 1, n, h[i][h[i].size() - 1] + 1, n, id[i], 1);
        }
    }
    memset(dis,0x3f,sizeof dis);
    dis[id[1]]=0;
    q.emplace(node{id[1],0});
    while(q.size()){
        node t=q.top();
        q.pop();
        if(vis[t.v]){
            continue;
        }
        vis[t.v]=1;
        for(pii i:g[t.v]){
            if(dis[i.fi]>t.w+i.se){
                dis[i.fi]=t.w+i.se;
                q.emplace(node{i.fi,dis[i.fi]});
            }
        }
    }
    if (dis[id[n]] == inf) return cout << -1, 0;
    for (int i = 1; i <= n; ++i) a[i].d = dis[id[i]], a[i].id = i;
    sort(a + 1, a + 1 + n);
    cnt[a[1].id] = 1, tot[0] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i].d == inf) continue;
        cnt[a[i].id] = tot[a[i].d - 1];
        for (int v : h[a[i].id]) {
            if (dis[id[v]] == a[i].d - 1) {
                cnt[a[i].id] = (cnt[a[i].id] - cnt[v] + mod) % mod;
            }
        }
        tot[a[i].d] = (tot[a[i].d] + cnt[a[i].id]) % mod;
    }
    cout << cnt[n] % mod;
    return 0;
}
```


---

## 作者：Flanksy (赞：7)

### 最短路、动态规划

好题，场上写的做法 TLE 了五个点，所以写一篇题解。

~~我是不是已经退役一个月了。~~

2023/9/11：更正了由 [AcO2d](https://www.luogu.com.cn/user/224663) 指出的语义混淆。


------------

#### 题意

在有 $n$ 个节点的无向完全图上删除 $m$ 条边，判断节点 $1$ 和节点 $n$ 是否连通。

若节点 $1$ 和节点 $n$ 不连通，输出 $-1$。

否则输出节点 $1$ 到节点 $n$ 的最短路数量对 $998244353$ 取模的值。

------------

#### 分析

以下所有讨论的对象均为**原图**。

建出原图的时间复杂度为 $O(n^2)$，不可接受。考虑一个稠密图遍历方法：对于点 $i$，记录所有与其**未连边**的点。记录所有**未被遍历**的点，形成一个集合。

初始时将起点入队，在未被遍历的点的集合中删除起点。

遍历未被遍历的点的集合并查询点 $i$ 与队首之间**是否未连边**，如果连边，那么在未被遍历的点的集合中删除点 $i$，更新 $i$ 到起点的距离并将 $i$ 入队。

由于指定删除的边数量至多 $2 \times 10^5$ 条，至多 $2 \times 10^5$ 次查询结果为**未连边**，否则点 $i$ 将会入队。也就是说，起点可达的所有点全部入队之前至多进行 $4 \times 10^5$ 次查询。

由于 $n$、$m$ 同阶，在使用 `unordered_set` 的情况下，这一部分的时间复杂度为 $O(n)$。

既然最短路长度已经求得，是不是可以连边后拓扑排序计算其数量了？否。即使边数有所减少，连边的代价仍然是不可接受的。

令 $dis_i$ 为节点 $i$ 到节点 $1$ 的最短距离。对于点对 $u,v$，只有在 $dis_u=dis_v+1$ 或 $dis_v=dis_u+1$ 时相互之间产生贡献。

**原图中几乎所有符合以上条件的点对之间存在贡献。**

对于 $dis=i+1$ 的点 $u$，将其答案初始化为所有 $dis=i$ 的点的答案之和，因为几乎所有 $dis=i$ 的点都可以到达点 $u$。然后枚举所有与 $u$ **未连边**的点 $v$，如果符合 $dis_u=dis_v+1$ 就将 $v$ 的答案从 $u$ 的答案中扣除。

总体时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int mod=998244353;
vector<int> e[200005],v[200005];
int n,m,dp[200005],dis[200005];
unordered_set<int> s,w[200005];
queue<int> q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) s.emplace(i);
	for(int i=1;i<=m;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		w[x].emplace(y);//bfs时查询连边用 
		w[y].emplace(x);
		v[x].push_back(y);//计算最短路数量用 
		v[y].push_back(x);
	}
	dp[1]=1,dis[1]=1,s.erase(1);
	for(q.push(1);!q.empty();q.pop()){
		vector<int> trash;
		int now=q.front();
		for(int i:s) if(!w[now].count(i)){
			dis[i]=dis[now]+1;
			q.push(i);
			trash.push_back(i);
		}
		for(int i:trash) s.erase(i);
	}
	if(dis[n]==0) return puts("-1"),0;
	for(int i=1;i<=n;i++) e[dis[i]].push_back(i);
	for(int i=2;i<=dis[n];i++){
		long long sum=0ll;
		for(int j:e[i-1]) sum+=dp[j];//完全图在任意点之间都有连边 
		for(int j:e[i]){//枚举dis[j]=i的点 
			long long ans=sum;
			for(int k:v[j]) if(dis[k]==dis[j]-1) ans-=dp[k];//减去没有连边的点的贡献 
			dp[j]=(ans%mod+mod)%mod;
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：7)

# 思路

这里给出两道同样套路的题目。
- CF920E
- CF1242B

这里类似的我们也用一个数组来进行统计可以转移的点，因为要支持删除就用 set 了。

首先跑一遍 bfs，用寻常方法求出距离 $1$ 的距离后考虑怎么用距离来求方案数。

这里因为 $dis_{u}$ 是从 $dis_{v}+1$ 转移过来的，那么我们就先开一个桶来记录每个距离的节点类似下面代码。

`st[dis[i]].push_back(i)`

首先来考虑怎么用很短的时间求出来到点 $u$ 的方案数，因为这是个完全图，就先把他赋值为 $dis_u-1$ 的个数，然后减去删掉的边，这里看一下代码大概就会了。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (l); i >= (r); i--)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000010, mod = 998244353;
vector<int> e[maxn];
set<int> S;
map<pair<int, int>, bool> mp;
int dis[maxn];
vector<int> st[maxn];
int ans[maxn];
int t[maxn];
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        mp[{u, v}] = 1;
        mp[{v, u}] = 1;
    }
    rep(i, 1, n) {
        S.insert(i);
        dis[i] = -1;
    }
    dis[1] = 0;
    queue<int> Q;
    S.erase(S.begin());
    Q.push(1);
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        vector<int> del;
        for (auto it = S.begin(); it != S.end(); it++) {
            int v = *it;
            if (mp[{u, v}]) {
                continue;
            }
            Q.push(v);
            dis[v] = dis[u] + 1;
            del.push_back(v);
        }
        for (int v : del) {
            S.erase(v);
        }
        if (S.size() == 0) {
            break;
        }
    }
    if (dis[n] == -1) {
        cout << -1 << "\n";
        return 0;
    }
    rep(i, 1, n) {
        if (dis[i] != -1) {
            st[dis[i]].push_back(i);
        }
    }
    t[0] = 1;
    ans[1] = 1;
    rep(i, 1, n) {
        for (int u : st[i]) {
            ans[u] = t[i - 1];
            for (int v : e[u]) {
                if (dis[u] == dis[v] + 1) {
                    ans[u] -= ans[v];
                    ans[u] += mod;
                    ans[u] %= mod;
                }
            }
            t[i] += ans[u];
            t[i] = t[i] % mod;
        }
    }
    cout << ans[n];
    return 0;
}
```

---

## 作者：Genius_Star (赞：6)

- ``2023/9/22 修改了被 after_contest 制裁的题解``（感谢大佬 [zhongpeilin](https://www.luogu.com.cn/user/751855)，[ran_qwq](https://www.luogu.com.cn/user/743048)，[OIerLKL2578](https://www.luogu.com.cn/user/557754) 的帮助）

### 题意：

现在又一个 $n$ 个点的无向完全图，删除了 $m$ 条边之后，问你从 $1$ 号点到达 $n$ 号点的最短路径条数是多少？

### 思路：

~~赛后第一次切 G 题诶！~~

看到这里，大家可能会想到 [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)，直接暴力删边直接做的话，可以使用 ``BFS`` 来求，但是这样的时间复杂度也是 $O(n^2)$ 的，所以要想想怎么优化。

其实有一个挺简单的做法，定义 $f_i$ 为到达 $i$ 号点的最短路径条数，$dis_i$ 为到达 $i$ 号点的最短路径，$s_i$ 为当前层次不能到达 $i$ 号点的条数，$sum$ 为当前层次所有点的最短路径数量之和。

我们从一号点开始入队（初始肯定定义 $dis_1=f_1=1$），然后宽搜一下，设队头为 $u$，对于所有删除了 $u$ 号点的边，找到删除的边的另外一条边，将 $s_v \to s_v + f_u$（因为这条边被删除了，所以这个点不能直接过去，所以累加在 $s_v$ 中）。

如果当前队为空了，我们需要加入新的点了，遍历这 $n$ 个点，寻找每一个没有找到最短路径的并且 $s_i \ne sum$ 的点 $i$，然后将 $dis_i \to dis_u+1$，同时将这个这个点的最短路径的条数 $f_i \to (sum-s_i)$，最后将 $i$ 入队。

现在想想为什么要这样？

我们知道 $sum$ 为当前所有点的最短路径数量之和，如果 $s_i=sum$ 的话，这说明在当前层次没有一个点可以通向 $i$ 这个点，所以不用访问。

还有如果 $dis_i$ 已经有值了，说明前面已经有一个最近的路径了，所以也不用访问。

更新 $i$ 号点的答案就是当前层次所有的条数减去不能到达当前点的条数（毕竟在同一层次的点，到达 $i$ 号点的距离都是 $1$，毕竟之前是一个完全图）。

因为 $sum$ 和 $s_i$ 都是当前层次的，即每次入队之后就将 $sum=s_i=0$。

最后我们的答案就是 $f_n$。（注意如果 $f_n$ 为 $0$ 就输出 $-1$）

因为是按照层次分的，所以时间复杂度为：$O(n+m)$。

#### 新增部分：

因为有模数，所以可能 $sum$ 不等于 $g_i$ 但是 $sum$ 模 $mod$ 同于 $g_i$，这样会导致计算错误，其实，我们只需要讲模式改为 $998244353$ 的倍数即可（这样不好改变答案），最后再重新模上 $998244353$ 即可。

我这里新设置的模式是 $998244353^2$，这样就可以避免 ``after_contest`` 卡 $998244353$ 的数据。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200200;
const ll mod=(998244353ll)*(998244353ll);
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,sum=0;
ll dis[N],f[N],s[N];
vector<ll> E[N];
queue<ll> q;
void add(ll u,ll v){ //建边 
	E[u].push_back(v);
	E[v].push_back(u);
} 
int main(){
	n=read(),m=read(); 
	for(int u,v,i=1;i<=m;i++){
		u=read(),v=read();
		add(u,v);
	}
	q.push(1);
	dis[1]=1;
	f[1]=1;
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		for(auto v:E[u]) //删除的边 
	      s[v]=(s[v]+f[u])%mod;
	    sum=(sum+f[u])%mod; //累加条数 
		if(q.empty()){ //增点 
			for(ll i=1;i<=n;i++){
				if(!dis[i]&&s[i]!=sum){
					dis[i]=dis[u]+1;
					f[i]=(sum-s[i]+mod)%mod;
					q.push(i);
				}
				s[i]=0;
			}
			sum=0;
		}
	}
	if(!f[n])
	  puts("-1"); 
	else
	  write(f[n]%998244353ll);
	return 0;
}
```


---

## 作者：TernaryTree (赞：3)

赛时调半天发现没取模/fn/fn/fn 终于在最后一分钟过了/ll

首先我们先考虑补图的最短路怎么求。先上一个最经典的无向无权 bfs，我们扔一个 set 表示当前没搜到的地方，然后每次搜这个 set 看看有没有与这个点没有连边的，我们就推进队列，把这个点删掉，如果 set 空了就退出。

接下来是方案数怎么求。观察一个结点 $u$，它只可能从 $dis_f=dis_u-1$ 的地方转移过来，这样才是最短路，并且 $u$ 与 $f$ 之间没有连边。记 $t_i=\sum\limits_{dis_u=i}ans_u$，则 $ans_u=t_{dis_u-1}-\sum\limits_{f\to u}ans_f [dis_f=dis_u-1]$。这东西可以很高兴的按照 $i$ 递增下去算就行了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 998244353;

int n, m;
set<int> g[maxn];
set<int> cur;
queue<int> q;
int dis[maxn];
int ans[maxn]; 
int tmp[maxn];
vector<int> pos[maxn];
vector<int> del;

signed main() {
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].insert(v);
		g[v].insert(u);
	}
	for (int i = 1; i <= n; i++) {
		dis[i] = -1;
		if (i >= 2) cur.insert(i);
	}
	q.push(1);
	dis[1] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		del.clear();
		for (auto it = cur.begin(); it != cur.end(); it++) {
			int v = *it;
			if (g[u].find(v) == g[u].end()) {
				q.push(v);
				dis[v] = dis[u] + 1;
				del.push_back(v);
			}
		}
		for (int v : del) cur.erase(v);
		if (cur.empty()) break;
	}
	if (dis[n] == -1) {
		cout << -1 << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		if (dis[i] == -1) continue;
		pos[dis[i]].push_back(i);
	}
	tmp[0] = 1;
	ans[1] = 1;
	set<int> now;
	for (int i = 2; i <= n; i++) now.insert(i);
	for (int i = 1; i <= n; i++) {
		if (!pos[i].size()) break;
		for (int u : pos[i]) {
			ans[u] = tmp[i - 1];
			for (int v : g[u]) {
				if (dis[u] == dis[v] + 1) ((ans[u] -= ans[v]) += mod) %= mod;
			}
			(tmp[i] += ans[u]) %= mod;
		}
	}
	cout << ans[n] << endl;
	return 0;
}
```

---

## 作者：markding (赞：2)

提供一种奇奇怪怪的思路。

设 $f_{i,j}$ 表示从点 $1$ 走 $i$ 步到点 $j$ 的方案数。

初值为 $f_{0,1}=1,\ f_{0,i}=0\ (2\le i\le n)$。

转移式为 $f_{i,j}=\sum_{(j,k)\in E} f_{i-1,k}$。

而此题要求的答案则为 $f_{t,n}$，其中 $t$ 是最小的一个数满足 $f_{t,n}>0$。若这样的 $t$ 不存在，输出 $-1$。

对于 $f$ 数组从 $f_{i-1,j}$ 向 $f_{i,j}$ 的转移，有 $O(N+M)$ 的方法。

首先我们算出 $\sum^n_{j=1}f_{i-1,j}$ 的值，记为 $sum$，则 $f_{i,j}=sum-\sum_{(j,k)\notin E}f_{i-1,k}$。

由于这是一个删去了 $M$ 条边的无向完全图，故 $\sum_{1\le j,k\le n}[(j,k)\notin E]$ 的值是 $N+2M$。我们只需求和后做 $N+2M$ 次减法就行了。

注意到题目中的最短路不会很长（？），所以我们直接套用上述做法 $666$ 次即可。

如果在第 $t$ 次迭代后 $f_{t,n}>0$，那么答案就是 $f_{t,n}$。

如果 $666$ 次迭代后 $f_{666,n}$ 的值依旧为 $0$，那么直接输出 $-1$ 即可（？）。

本人的实现复杂度为 $O(round(n+m))\approx4\times10^8$（代码中 $round$ 的值为 $666$），时间较满。

**UPD 于 2024/5/3:** 被 after_contest 制裁力（大悲），hack 数据的答案是 $998244353$ 的倍数，取模后等于 $0$，会被当做无解输出。

解决方法很简单，我们只需将代码中的运算对 $998244353d$（$d$ 为正整数）取模，最后对于 $998244353$ 取模后输出即可。

当 $d$ 越大时，数据便越难构造（？），我们卡过去的概率越大，代码中 $d=7$。

```cpp
#include<iostream>
#define int long long
#define mod 998244353
#define Mod 6987710471
#define N 200005
using namespace std;
int n,m,u[N],v[N],f[N],g[N];
signed main()
{
	cin>>n>>m,f[1]=1;
	for(int i=1;i<=m;i++)cin>>u[i]>>v[i];
	for(int rd=1;rd<=666;rd++)
	{
		int sum=0;
		for(int i=1;i<=n;i++)sum=(sum+f[i])%Mod;
		for(int i=1;i<=n;i++)g[i]=(sum-f[i]+Mod)%Mod;
		for(int i=1;i<=m;i++)
			g[u[i]]=(g[u[i]]-f[v[i]]+Mod)%Mod,
			g[v[i]]=(g[v[i]]-f[u[i]]+Mod)%Mod;
		for(int i=1;i<=n;i++)f[i]=g[i];
		if(f[n]){cout<<f[n]%mod;return 0;}
	}
	cout<<-1;
}
```

---

## 作者：User_Unauthorized (赞：2)

## 题意

给定由 $N$ 个节点组成的无向完全图 $G$，并删去 $M$ 条边，求该图的最短路数量。

（$2 \le N \le 2 \times 10^5, 0 \le M \le \min\left\{2 \times 10^5, \dfrac{N(N - 1)}{2}\right\}$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ABC319G.html)

首先考虑若有一张边数较少的无向图该如何对最短路计数，由于边不带权，所以一个节点到 $1$ 号节点的最短路就是该节点在以 $1$ 号节点为根的 $\tt{BFS}$ 生成树深度。故可进行转移，设 $\operatorname{count}_u$ 表示从 $1$ 号节点到节点 $u$ 的最短路个数，$\operatorname{dist}_u$ 表示从 $1$ 号节点到节点 $u$ 的最短路长度，那么有转移

$$\operatorname{count}_u = \sum\limits_{\left(u, v\right) \in G \land \operatorname{dist}_v = \operatorname{dist}_u - 1} \operatorname{count}_v$$

但是由于此图边数过多，暴力转移是不可行的。考虑也按完全图删边的思想进行转移，即首先设当前图为完全图进行转移，然后将通过被删除的边转移而来的非法贡献去除，设被删除的边组成的图为 $G^{\prime}$，那么有转移

$$\operatorname{count}_u = \sum\limits_{\operatorname{dist}_v = \operatorname{dist}_u - 1} \operatorname{count}_v - \sum\limits_{\left(u, v\right) \in G^{\prime} \land \operatorname{dist}_v = \operatorname{dist}_u - 1} \operatorname{count}_v$$

在求出每个节点的 $\operatorname{count}$ 后维护一个数组 $sum_x = \sum\limits_{\operatorname{dist}_u = x} \operatorname{count}_u$ 即可快速转移，这部分复杂度为 $\mathcal{O}(N + M)$。

现在还需要解决的问题是如何快速的从当前节点扩展到其他节点，可以发现每个节点只会进入队列一次，故可以维护一个列表，代表未进队的节点，每次扩展节点时遍历列表，并检查边 $(u, v)$ 是否被删除即可。具体的，可以维护一个 $\tt{bool}$ 数组，每次扩展节点前遍历所有从当前节点出发被删除的边，并打上标记，然后遍历列表后清空即可。可以发现每条被删除的边最多引起一次对列表单个元素的重复遍历，故这部分复杂度为 $\mathcal{O}(N + M)$。

总复杂度为 $\mathcal{O}(N + M)$，可以通过本题。

## Code

```cpp
//G
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;
typedef std::queue<valueType> queue;
typedef std::list<valueType> list;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    ValueMatrix G(N + 1);

    for (valueType i = 0; i < M; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    ValueVector dist(N + 1, N + 100), count(N + 1, -1), sum(N + 1, 0);
    bitset removed(N + 1, false);
    list Q(N - 1);

    queue que;

    dist[1] = 1;
    count[1] = 1;
    sum[0] = 1;
    que.push(1);
    std::iota(Q.begin(), Q.end(), 2);

    while (!que.empty()) {
        valueType const u = que.front();

        que.pop();

        count[u] = sum[dist[u] - 1];

        for (auto const &iter: G[u]) {
            if (dist[iter] == dist[u] - 1) {
                Dec(count[u], count[iter]);
            }

            removed[iter] = true;
        }

        Inc(sum[dist[u]], count[u]);

        for (auto iter = Q.begin(); iter != Q.end();) {
            if (!removed[*iter]) {
                dist[*iter] = dist[u] + 1;

                que.push(*iter);

                iter = Q.erase(iter);
            } else {
                ++iter;
            }
        }

        for (auto const &iter: G[u])
            removed[iter] = false;
    }

    std::cout << count[N] << std::endl;

    return 0;
}
```

---

## 作者：linyihdfj (赞：1)

[更好的阅读体验](https://www.cnblogs.com/linyihdfj/p/17690698.html)
## G.Counting Shortest Paths
### 题目分析：
注意到我们只需要在所有的边都被删完了，再进行询问。

所以可以考虑直接从小到大枚举最短路长度，也就是从 $1$ 开始一步步扩展直到扩展到 $n$。

所以一个直观的想法就是一步步预处理出 $f[i][j]$ 表示 $1$ 到 $i$ 路径长度为 $j$ 的方案数，$O(n)$ 转移显然。

考虑优化，$f[i][j]$ 的第二维显然只有当 $j$ 为 $1$ 到 $i$ 的最短路时才有意义，所以可以将其它的所有忽略，总状态数变成了 $O(n)$。

对于转移，因为是现在的点对其余所有的点产生贡献，所以可以直接一起转移，只有 $O(m)$ 次转移才是需要特殊注意的，所以只需要管这 $O(m)$ 次转移，转移的总复杂度为 $O(m)$。

设 $n,m$ 同阶，则总时间复杂度为 $O(n)$。

代码中为了好写，使用了 set 复杂度会变成 $O(n \log n)$，以及有一个细节是我们如果直接将 $f$ 对 $998244353$ 取模那么就无法判断是否能转移到对应的节点，所以要特别记录一下。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
const int MOD = 998244353;
set<int> E[N],cur,lst,tmp;
int cnt[N],a[N],tot[N];
signed main(){
	int n,m;scanf("%lld%lld",&n,&m);
	for(int i=1; i<=m; i++){
		int u,v;scanf("%lld%lld",&u,&v);
		E[u].insert(v);
		E[v].insert(u);
	}
	cnt[n] = 1;
	cur.insert(n);
	for(int i=1; i<n; i++)	lst.insert(i);
	while(!cur.empty()){
		int res = 0,res2 = 0;
		for(auto now : cur)	res = (res + cnt[now])%MOD,res2++;
		for(auto to : lst)	cnt[to] = (cnt[to] + res)%MOD,tot[to] = 0;
		for(auto now : cur){
			for(auto to : E[now]){
				if(lst.find(to) != lst.end())  //避免奇奇怪怪的相互影响 
					cnt[to] = (cnt[to] - cnt[now] + MOD)%MOD,tot[to]++;
			}
		}
		for(auto now : cur){
			int tot = 0;
			for(auto to : E[now])	a[++tot] = to;
			for(int i=1; i<=tot; i++){
				E[a[i]].erase(now);
				E[now].erase(a[i]);
			}
		}
		swap(tmp,lst);
		cur.clear(),lst.clear();
		for(auto i : tmp){
			if(tot[i] != res2){  //tot 其实就是记录一下是不是有点可以转移到他 
				cur.insert(i);
				if(i == 1){
					printf("%lld\n",cnt[1]);
					return 0;
				}
			}
			else	lst.insert(i);
		}
		tmp.clear();
	}
	printf("-1\n");
	return 0;
}
```

---

## 作者：zhongpeilin (赞：0)

## 题目大意：
给你一张 $N$ 个节点的无向完全图，现在删了 $M$ 条边，请问从 `1` 出发有多少条最短路径到达 $N$？

## 解题思路：
首先有一个可以过 $N \le 5000$ 的做法，就是暴力 bfs，然后存储最短路径和方案数，向外扩张即可，$O(n^2)$。  
但是怎么才能过呢？首先我们可以将问题简化一下，假设问 `1` 到 $N$ 的最短路径长度。   
不难想到可以按照 $1 \to i$ 的最短路径长度分层。  
那么可以设 $cnt_{i}$ 表示上一层的点有多少不和 $i$ 连边，最后如果队列空了，就枚举所有未遍历的点，判断一下 $cnt_{i}$ 是否等于上一层点的个数，如果等于，说明现在它还不能被直接遍历，否则将它推进队列中。  
那么同理，设 $f_{i}$ 表示 $1 \to i$ 有几条最短路径。然后再维护 $g_{i}$ 表示在上一层不与 $i$ 连边的点的 $f_{i}$ 之和，最后算答案即可。  
时间复杂度：  
若 $N \le 5000$ 则时间复杂度为 $O(n^2 + m)$。  
若 $5000 < N \le 2 \times 10^5$ 则时间复杂度为 $O(n+m)$。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

bool vis[200005];
int CNT, cnt[200005];
int n, m, f[200005], g[200005], sum;
vector<int> G[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	queue<int> q;
	q.push(1);
	vis[1] = f[1] = 1;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		sum += f[x], CNT++;
		
		for(auto y : G[x]){
			if(vis[y]) continue;
			g[y] += f[x];
			cnt[y]++;
		}
		
		if(q.empty()){
			for(int i = 1; i <= n; i++){
				if(!vis[i] && cnt[i] != CNT){
					q.push(i);
					f[i] = (sum % mod - g[i] % mod + mod) % mod;
					vis[i] = 1;
				}
				g[i] = 0, cnt[i] = 0;
			}
			sum = 0, CNT = 0;
		}
	}
	if(!vis[n]) cout << -1 << endl;
	else cout << f[n] << endl;
	return 0;
}

---

## 作者：SegTree (赞：0)

### 题意
$n$ 个点的无向完全图，删掉 $m$ 条无向边 $(u,v)$。询问 $1$ 到 $n$ 的最短路径数对 $998244353$ 取模。

### 题解

首先你可以搞出来到每个点的最短路。这个东西直接 `bfs` 就行。维护一个 `set` 存储没有被算出距离的结点，每次访问出边的时候直接访问 `set` 里的元素就行。算出距离后把这个点从 `set` 里扔掉即可。

记 $res_i$ 为 $1$ 到点 $i$ 的最短路径数。显然有转移 $res_i$ 等于所有 $dis_j=dis_i-1$ 且 $j$ 和 $i$ 之间有边的 $res_j$ 之和。显然你把所有的结点按照 $dis$ 排序即可。

维护一个 $sum_i$ 为 $dis_j=i$ 的 $res_j$ 之和，每次需要计算的时候直接从 $sum_i$ 然后减掉 $j$ 和 $i$ 之间边被删且 $dis_j=dis_i-1$ 的 $res_j$ 即可。

### 代码

[提交记录](https://atcoder.jp/contests/abc319/submissions/45410879)。

---

## 作者：FReQuenter (赞：0)

题意：给定一张 $n$ 个点的无向完全图，删除 $m$ 条边，求最后 $1$ 到 $n$ 的最短路数量，对 $998244353$ 取模，没有最短路输出 $-1$。

考虑宽搜。但是普通的宽搜要把所有的边都访问一遍，复杂度 $O(n^2)$，需要优化。主要分为两个方面：

**计算最短路径的数量：**

我们令当前访问的点为 $u$，原图为 $G$，删掉的边连成的图为 $G'$，最短路径数量为 $f_u$，最短路径为 $d_u$，将要继承的贡献来自点 $v$。得到这样一个式子：

$$f_u=\sum_{v:d_v=d_u-1,\{u,v\}\in G}f_v=\sum_{v:d_v=d_u-1}f_v-\sum_{v:d_v=d_u-1,\{u,v\}\in G'}f_v$$

啥意思呢：对于一条边 $\{u,v\}\in G$，如果它被删掉了，那么向 $u$ 贡献的最短路就要减去 $f_v$。如果它是连着的，那么 $f_u$ 就继承 $f_v$。

这个东西转移也是 $O(n^2)$ 的，所以记录一下 $s_i=\sum_{v:d_v=i}f_v$ 就能把它降到 $O(m)$（因为只需要关注被删除的边就行了）。

**扩展新的点**

我们记录所有没有被搜索到的点，那么搜索到一个新点的时候就可以只对那些没有被搜到且在新图中和当前点相连的点就行了。因为只有那些被删除的边会重复被标记，而其它点只会被标记一次，所以这一部分是 $O(n+m)$ 的。

总复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define MAXN 200005
using namespace std;
int n,m,sum[MAXN],f[MAXN],dist[MAXN];
vector<int> rst,gv[MAXN];
bool vis[MAXN];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		gv[u].push_back(v);
		gv[v].push_back(u);
	}
	for(int i=2;i<=n;i++) rst.push_back(i);
	memset(dist,0x3f,sizeof(dist));
	dist[1]=0;
	f[1]=1;
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(u!=1) f[u]=sum[dist[u]-1];
		for(auto v:gv[u]){
			vis[v]=1;
			if(dist[v]==dist[u]-1) f[u]=(f[u]+mod-f[v])%mod;
		}
		if(u==n) break;
		sum[dist[u]]+=f[u],sum[dist[u]]%=mod;
		vector<int> tmp;
        for(auto nx:rst){
        	if(vis[nx]) tmp.push_back(nx);
        	else{
        		q.push(nx);
        		dist[nx]=dist[u]+1;
			}
		}
		rst=tmp;
		for(auto v:gv[u]) vis[v]=0;
	}
	if(dist[n]==0x3f3f3f3f3f3f3f3f) cout<<-1;
	else cout<<f[n];
}
```

---

