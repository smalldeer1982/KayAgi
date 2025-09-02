# Your Loss

## 题目描述

给定一棵有 $n$ 个节点的树，节点编号为 $1$ 到 $n$，以及一个长度为 $n$ 的数组。第 $i$ 个节点的权值为 $a_i$。有 $q$ 个询问，每个询问给定两个节点 $x$ 和 $y$。

考虑从编号为 $x$ 的节点到编号为 $y$ 的节点的路径。设该路径为 $x = p_0, p_1, p_2, \ldots, p_r = y$，其中 $p_i$ 表示路径上的中间节点。请计算 $\sum_{i=0}^{r} a_{p_i} \oplus i$ 的值，其中 $\oplus$ 表示 [异或](https://en.wikipedia.org/wiki/Exclusive_or) 运算。

更正式地说，计算
$$
\sum_{i =0}^{r} a_{p_i}\oplus i
$$
。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
4
1 2
2 3
3 4
2 3 6 5
3
1 4
3 4
1 1```

### 输出

```
14
10
2```

# 题解

## 作者：Risa (赞：3)

编号：CF1983G

tag：倍增，树形 dp

难度：*3172（$\texttt{Clist}$ 数据）

大号社贡满了，匀点给小号（雾，其实以后 ABC 和 CF Div.2 的题解都在这个号上写了）。

感觉严格定义从根向叶子转移的 dp 应该叫线性 dp？？？

回归正题。考虑到原题的式子长这样：

$$\sum_{i=0}^ra_i\oplus i$$

假设右边为序列 $b,b_i:=i$。

一个经典 trick：观察到这个运算符有个特殊的性质，每位都是独立的，所以我们将每个位拆开分别做。发现这样好像简洁很多。

那么也就变成了一个 $01$ 序列和 $2^{bit}$ 个 $0$，$2^{bit}$ 个 $1$ 交替而成的无限序列异或相加乘上系数 $2^{bit}$。

但是我们发现前面的序列是树上序列，好像不太好做，于是我们求出 $LCA$ 后将其拆成两个序列 $u\to LCA$ 和 $LCA\to v$ 即可。那么询问也就变成了两个端点满足一个端点必定是另一个的祖先。

直接做处理好像很麻烦。这时候询问变成了从节点 $u$ 向上跳 $k$ 步所形成的 $01$ 序列与 $2^{bit}$ 个 $0$，$2^{bit}$ 个 $1$ 交替而成的无限序列的 **子段** 异或相加的结果。首尾都处理，真的很麻烦（没人会爱写这东东吧）。那么就差分一下，假设原先询问为 $u\to v(dep_u\ge dep_v)$，再拆成两个询问 $u\to 1$ 和 $fa_v\to 1$，系数分别为 $1,-1$。两者结果相加即可。

问题再次转化成求 $1$ 到 $u$ 的路径与 $2^{bit}$ 个 $0$，$2^{bit}$ 个 $1$ 交替而成的无限序列的 **子段** 异或相加的结果。注意到从 $u$ 出发会经过若干个权值为 $0$ 或 $1$ 的节点，接下来就是确定的 $2^{bit}$ 个 $1$ 或 $0$ 交替而成的序列。将这两段分类讨论。

首先要确定这两段的分割点。发现这两段的分割点和 $u$ 对应的 $b_i$（即 $u$ 的标号）有关。而当 $bit$ 递增时，观察到分割点 $x$ 要么不变，要么向上跳 $2^{bit-1}$ 格，于是可以通过维护当前 $x$ 和 $x$ 的虚拟（因为 $x$ 当前不一定在 $u\to v$ 上，甚至有可能不在树上，不在树上 $x$ 为 $0$，当且仅当 $x$ 跳出根节点 $1$）标号实现每次 $\Theta(1)$ 跳。

然后是两段信息。这个显然前缀和很好维护。$f_{u,0/1/2/3}$ 表示在链 $1\to u$，$b_i$ 的第 $bit$ 位均为 $0/1$，$b_i$ 的第 $bit$ 位恰好结尾为其中一段 $0/1$ 的结尾，遂维护之。这样遍历是 $\Theta(n)$ 的。

共有 $\log V$ 位，每位需要一遍 $\Theta(n)$ 预处理前缀和和对每个询问分别拆掉的 $\Theta(1)$ 跳分割点和 $\Theta(1)$ 查询。

$\Theta((n+q)\log V)$。

[submission](https://codeforces.com/contest/1983/submission/269406071)

**注：未计算 $\text{getlca}$ 函数复杂度，可以做到 $\Theta(n)$，本份代码为倍增 LCA，故时间复杂度为 $\Theta(n\log n)$。**

@sunkuangzheng 似乎有根号 $\log$ 的做法，实现出来并通过了此题，拜谢。

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：sunkuangzheng (赞：3)

$\textbf{CF1983G *3100}$

> - 给定一棵树，点带权，$q$ 次询问给出 $u,v$，设 $u \to v$ 路径上的点为 $p_0,p_1,\ldots,p_m$，求 $\sum \limits_{i=0}^m a_{p_i} \oplus i$。
> - $1 \le n,a_i \le 5 \cdot 10^5,1 \le q \le 10^5$。

考虑先对树重链剖分，将路径拆到若干重链上转化为序列问题。现在的问题是，给定长为 $m$ 的序列 $a$，每次询问给出 $x,y$ 求 $\sum \limits_{i=0}^y a_i \oplus(x+i)$ 或 $\sum \limits_{i=0}^y a_i \oplus(x-i)$ 的结果。

拆位计算贡献。注意到 $x,x+1,\ldots,x+y$ 的某一位在二进制下的表示形如 $0000111100001111\ldots$，考虑根号分治，设阈值 $B$。


- 对于 $j \le B$ 的位 $j$，本质不同的 $x$ 只有 $\mathcal O(2^j)$ 种，可以对于每一种都计算答案，复杂度 $\mathcal O(\sum \limits_{j=0}^B m2^j) = \mathcal O(m2^B)$。
- 对于 $j > B$ 的位 $j$，其是由 $\mathcal O(\dfrac{m}{2^j})$ 个模式相同的串拼起来的。预处理 $0,1$ 数量的前缀和后可以 $\mathcal O(\dfrac{m}{2^j})$ 回答单组询问。这里的总复杂度是 $\mathcal O(\dfrac{mq \log n}{2^j})$。

取 $2^B = \sqrt {m \log n}$ 的复杂度即为 $\mathcal O((n+q) \sqrt {n \log n})$，然而由于树剖常数很小，可以在 2.5 秒内卡过。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 07.07.2024 23:01:40
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 1e6+5,B = 9;
using namespace std;
int T,n,u,v; vector<int> g[N];
int dep[N],siz[N],son[N],dfn[N],a[N],top[N],fa[N],ct,q,b[N],nb[N]; 
vector<tuple<int,int,int,int>> qr[N]; vector<tuple<int,int,int>> tp[N];
ll res[N]; int pre[N];
void dfs1(int u,int f){
    dep[u] = dep[f] + 1,fa[u] = f,siz[u] = 1,son[u] = 0;
    for(int v : g[u]) if(v != f) if(dfs1(v,u),siz[u] += siz[v],siz[v] > siz[son[u]]) son[u] = v;
}void dfs2(int u,int tp){
    top[u] = tp,dfn[u] = ++ct; if(son[u]) dfs2(son[u],tp);
    for(int v : g[u]) if(v != fa[u] && v != son[u]) dfs2(v,v);
}void qry(int u,int v,int i){
    vector<pair<int,int>> pa,pb;
    while(top[u] != top[v]){
        if(dep[top[u]] > dep[top[v]])
            pa.emplace_back(top[u],u),u = fa[top[u]];
        else pb.emplace_back(top[v],v),v = fa[top[v]];
    }if(dfn[u] > dfn[v]) pa.emplace_back(v,u);
    else pb.emplace_back(u,v); reverse(pb.begin(),pb.end());
    int now = 0;
    for(auto [u,v] : pa){
        int lt = now + (dfn[v] - dfn[top[u]]);
        qr[top[u]].emplace_back(v,lt,i,-1);
        if(u != top[u]) qr[top[u]].emplace_back(fa[u],lt,-i,-1);
        now += dfn[v] - dfn[u] + 1;
    }for(auto [u,v] : pb){
        int lt = now - (dfn[u] - dfn[top[u]]); 
        qr[top[u]].emplace_back(v,lt,i,1); 
        if(u != top[u]) qr[top[u]].emplace_back(fa[u],lt,-i,1);
        now += dfn[v] - dfn[u] + 1;
    }
}void sol(int u){
    vector<int> a; int v = u;
    while(v) a.push_back(b[v]),nb[v] = dfn[v] - dfn[u],v = son[v];
    int m = a.size(),B = max(-1,(int)sqrt(ceil(log2(m))) + 2);
    for(int i = 0;i <= B;i ++){ 
        int md = (1 << i + 1);
        for(auto [v,t,id,tt] : qr[u]) 
            if(tt > 0) tp[(t % md + md) % md].emplace_back(nb[v],1,id);
            else tp[(((md - t) % md + md) % md + (1 << i) - 1 + md) % md].emplace_back(nb[v],1,id);
        for(int j = 0;j < (1 << i);j ++){
            for(int k = 0;k < m;k ++){
                int bt = (k % md);
                int cb = (bt >= (1 << i) - j && bt < md - j) ^ ((a[k] >> i) & 1);
                pre[k] = (!k ? 0 : pre[k - 1]) + cb;
            }for(auto [v,t,id] : tp[j]) res[abs(id)] += (id > 0 ? 1 : -1) * (pre[v]) * (1ll << i); 
        }
        for(int j = 0;j < (1 << i);j ++){
            for(int k = 0;k < m;k ++){
                int bt = (k % md);
                int cb = 1 ^ (bt >= (1 << i) - j && bt < md - j) ^ ((a[k] >> i) & 1);
                pre[k] = (!k ? 0 : pre[k - 1]) + cb;
            }
            for(auto [v,t,id] : tp[j + (1 << i)]) res[abs(id)] += (id > 0 ? 1 : -1) * (pre[v]) * (1ll << i); 
        }
        for(auto [v,t,id,tt] : qr[u]) 
            if(tt > 0) tp[(t % md + md) % md].pop_back();
            else tp[(((md - t) % md + md) % md + (1 << i) - 1 + md) % md].pop_back();
    }
    for(int i = B + 1;i <= 19;i ++){  
        int md = (1 << i + 1);
        for(auto [v,t,id,tt] : qr[u]) 
            if(tt > 0) tp[0].emplace_back(nb[v],(t + md) % md,id);
            else tp[0].emplace_back(nb[v],((md - t + md) % md + (1 << i) - 1 + md) % md,id);
        for(int j = 0;j < m;j ++)
            pre[j] = (!j ? 0 : pre[j - 1]) + ((a[j] >> i) & 1);
        for(auto [v,t,id] : tp[0]){
            auto c1 = [&](int l,int r){
                r = min(r,v);
                if(l > r) return 0;
                return pre[r] - (!l ? 0 : pre[l - 1]);
            }; auto c0 = [&](int l,int r){
                r = min(r,v);
                if(l > r) return 0;
                return r - l + 1 - c1(l,r);
            };
            if(t < (1 << i)){
                int px = (1 << i) - t,tp = c1(0,px-1);  
                for(;px <= v;px += md) tp += c0(px,px + (1 << i) - 1) + c1(px + (1 << i),px + (1 << i + 1) - 1);
                res[abs(id)] += (id > 0 ? 1 : -1) * tp * (1ll << i); 
            }else{
                t -= (1 << i);
                int px = (1 << i) - t,tp = c0(0,px-1); 
                for(;px <= v;px += md) tp += c1(px,px + (1 << i) - 1) + c0(px + (1 << i),px + md - 1);
                res[abs(id)] += (id > 0 ? 1 : -1) * tp * (1ll << i); 
            }
        }tp[0].clear();
    }
}
void los(){
    cin >> n,ct = 0;
    for(int i = 1;i <= n;i ++) g[i].clear(),qr[i].clear();
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    for(int i = 1;i <= n;i ++) cin >> b[i];
    cin >> q,dfs1(1,0),dfs2(1,1);
    for(int i = 1;i <= q;i ++) res[i] = 0,cin >> u >> v,qry(u,v,i);
    for(int i = 1;i <= n;i ++) if(qr[i].size()) sol(i);
    for(int i = 1;i <= q;i ++) cout << res[i] << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：_Ch1F4N_ (赞：2)

但凡再给我 $10$ 分钟就过了，我是真的小丑，哈哈哈。

考虑把一条路径拆成两条链，对于一条链可以再差分成两条点到根的链。

然后考虑，假设起点异或上的值是 $s$，那么在第 $i$ 位的贡献形如前 $s$ 的前 $i-1$ 位组成的数个点异或的值第 $i$ 位与 $s$ 第 $i$ 位一致，然后前 $i-1$ 位变成了全 $0$，注意到接下来第 $i$ 位的 $1,0$ 交替变成以 $2^i$ 为周期，我们把形成周期后的贡献称为 $dp_{u,i,0/1}$ 这里 $0/1$ 表示第一个周期是 $0$ 还是 $1$，那么不难发现的是 $dp_{u,i,0/1}$ 可以由 $u$ 的 $2^i$ 祖先的 $dp$ 值贡献加上其到这个祖先的链上权值第 $i$ 位是 $0/1$ 的点的贡献，对于后者可以预处理出 $pre_{u,i}$ 表示点 $u$ 到根的路径上第 $i$ 位是 $1$ 的数个数，对于前者可以从上往下树形 dp。

对于形成周期以前的部分可以通过倍增暴力跳 $k$ 级祖先找到这个部分的起点终点再用处理出的 $pre$ 数组相仿地计算贡献即可。

时间复杂度 $O(n \log V + q \log n \log V)$。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int maxn = 5e5+114;
int pre[maxn][21];//拆位后节点 u 到根路径上第 i 位的 1 数量
int dep[maxn];
int fa[maxn][21];
int lg[maxn];
int a[maxn];
int n,q;
vector<int> E[maxn];
int dp[maxn][21][2];//dp[u][i][0/1] 点 u 第 i 位的答案 除以了 2^i 且从 0/1 开始跳
void dfs1(int u,int father){
    fa[u][0]=father;
    dep[u]=dep[father]+1;
    for(int i=0;i<=20;i++){
        pre[u][i]=pre[father][i]+(((1<<i)&a[u])?1:0);
    }
    for(int i=1;i<=20;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int v:E[u]){
        if(v!=fa[u][0]){
            dfs1(v,u);
        }
    }
}
void dfs2(int u){
    for(int i=0;i<=20;i++){
        dp[u][i][0]=dp[fa[u][i]][i][1]+(pre[u][i]-pre[fa[u][i]][i]);
        dp[u][i][1]=dp[fa[u][i]][i][0]+((dep[u]-dep[fa[u][i]])-(pre[u][i]-pre[fa[u][i]][i]));
    }
    for(int v:E[u]){
        if(v!=fa[u][0]){
            dfs2(v);
        }
    }
}
int LCA(int u,int v){
    if(dep[u]<dep[v]) swap(u,v);
    while(dep[u]>dep[v]) u=fa[u][lg[dep[u]-dep[v]]-1];
    if(u==v) return u;
    for(int i=20;i>=0;i--){
        if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
    }
    return fa[u][0];
}
int kfa(int u,int k){
    if(k>=dep[u]) return 0;
    int to=dep[u]-k;
    while(dep[u]>to) u=fa[u][lg[dep[u]-to]-1];
    return u;
}
long long ask1(int u,int s){
    long long res=0;
    int sum=0;//低位之和
    for(int i=0;i<=20;i++){
        //残段
        int len=(1<<i)-sum;
        int nxt=kfa(u,len);
        if((1<<i)&s){
            res+=(1ll<<i)*((dep[u]-dep[nxt])-(pre[u][i]-pre[nxt][i]));
            res+=(1ll<<i)*dp[nxt][i][0];
            sum+=(1<<i);
        }else{
            res+=(1ll<<i)*(pre[u][i]-pre[nxt][i]);
            res+=(1ll<<i)*dp[nxt][i][1];
        }
    }
    return res;
}//编号递增
long long ask2(int u,int s){
    long long res=0;
    int sum=0;//低位之和
    for(int i=0;i<=20;i++){
        //残段
        int len=sum+1;
        int nxt=kfa(u,len);
        if((1<<i)&s){
            res+=(1ll<<i)*((dep[u]-dep[nxt])-(pre[u][i]-pre[nxt][i]));
            res+=(1ll<<i)*dp[nxt][i][0];
            sum+=(1<<i);
        }else{
            //cout<<res<<' ';
            res+=(1ll<<i)*(pre[u][i]-pre[nxt][i]);
            res+=(1ll<<i)*dp[nxt][i][1];
        }
    }
    return res;
}//编号递减
void work(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=20;j++){
            fa[i][j]=pre[i][j]=dp[i][j][0]=dp[i][j][1]=0;
        }
        E[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
	for(int i=1;i<=n;i++){
        cin>>a[i];
        lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	}
	dfs1(1,0);
	dfs2(1);
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        int dis=dep[x]+dep[y]-2*dep[lca];
        long long ans=0;
        ans+=(ask1(x,0)-ask1(lca,dep[x]-dep[lca]));
        ans+=(ask2(y,dis)-ask2(lca,dep[x]-dep[lca]));
        ans+=(a[lca]^(dep[x]-dep[lca]));
        cout<<ans<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        work();
    }
}
/*
1
4
1 2
2 3
3 4
2 3 6 5
1
1 4
*/
```

---

## 作者：Naib (赞：1)

先拆位。

容易发现从 $u$ 开始走，每一位的值是一个周期。

设 $f_{u,i},g_{u,i}$ 表示从节点 $u$ 开始（且为 $i$ 周期开头）到根，第 $i$ 位的贡献之和。容易对于每个 $i$ 做到 $O(n)$。

对于每个询问 $(u,v)$，$k=lca(u,v)$，拆成 $u\to k,k\to 1,1\to fa_{k},k\to v$。

如果一个询问起点不是 $0$，那么先通过倍增跳到周期点，这过程中的点显然也是属于同一个周期的，可以 $O(1)$ 计算答案。

注意到对于不同的位实际上可以一起跳（每次跳 lowbit 就好了）。这样查询就是 $O(1)$ 的。复杂度 $O(n\log n)$。

[submission](https://codeforces.com/contest/1983/submission/270562384)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1983G)

**题目大意**

> 给定 $n$ 个点的树，点有点权 $a$，$q$ 次询问 $u,v$，设 $u\to v$ 路径为 $p_0\sim p_m$，求 $\sum i\oplus a_{p_i}$。
>
> 数据范围：$n\le 5\times 10^5,q\le 10^5$。

**思路分析**

把询问拆成 $u\to \mathrm{LCA}$ 的递增路径和 $\mathrm{LCA}\to v$ 的递减路径。

先计算 $F(u,d)$ 表示 $u\to fa^{d-1}(u)$ 的答案。

先拆位，对每个 $k$ 求出 $\sum i\oplus a_{p_i}$ 第 $k$ 位为 $1$ 的个数。

观察 $i$ 的第 $k$ 位如何变化，容易发现其以 $2^{k+1}$ 为周期，交替出现 $0,1$。

那么我们可以设 $f_{u,k}$ 表示 $u\to rt$ 路径的答案，差分 $f_{u,k}-f_{v,k}$ 可以算出 $u\to v$ 路径的答案，但这要求 $2^k\mid \mathrm{dis}(u,v)$。

那么求 $F(u,d)$ 的时候把这条路径分成 $d=2^{k_1}+2^{k_2}+\dots +2^{k_s}$ 若干段，其中 $k_1>k_2>\dots >k_s$。

每段 $k_i$ 算权值是容易的，只要把 $k_1\sim k_{i-1}$ 对应的位贡献翻转。

同理 $G(u,d)$ 表示 $u\gets  fa^{d-1}(u)$ 的方案，$g_{u,k}$ 表示 $rt\to u$ 路径的答案，做类似的过程即可。

时间复杂度 $\mathcal O(n\log n+q\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e5+5,K=19;
int n,q,a[MAXN],dep[MAXN],fa[MAXN][K],c[MAXN][K];
int f[MAXN][K],g[MAXN][K];
ll dis[MAXN];
vector <int> G[MAXN];
void dfs(int u,int fz) {
	dep[u]=dep[fz]+1,dis[u]=dis[fz]+a[u];
	fa[u][0]=fz;
	for(int k=0;k<K;++k) c[u][k]=c[fz][k]+(a[u]>>k&1?-1:1);
	for(int k=1;k<K;++k) fa[u][k]=fa[fa[u][k-1]][k-1];
	for(int k=0;k<K;++k) {
		int x=fa[u][k],y=fa[fa[u][k]][k];
		f[u][k]=f[y][k]+c[x][k]-c[y][k];
		g[u][k]=g[y][k]+c[u][k]-c[x][k];
	}
	for(int v:G[u]) if(v^fz) dfs(v,u);
}
int LCA(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	for(int k=K-1;~k;--k) if(dep[fa[u][k]]>=dep[v]) u=fa[u][k];
	if(u==v) return u;
	for(int k=K-1;~k;--k) if(fa[u][k]^fa[v][k]) u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}
ll qf(int u,int d) {
	ll ans=0;
	for(int i=K-1;~i;--i) if(d>>i&1) {
		int v=fa[u][i];
		for(int j=0;j<i;++j) ans+=(1ll<<j)*(f[u][j]-f[v][j]);
		for(int j=K-1;j>i;--j) if(d>>j&1) ans+=(1ll<<j)*(c[u][j]-c[v][j]);
		u=v;
	}
	return ans;
}
ll qg(int u,int d) {
	ll ans=0;
	for(int i=0;i<K;++i) if(d>>i&1) {
		int v=fa[u][i];
		for(int j=0;j<i;++j) ans+=(1ll<<j)*(g[u][j]-g[v][j]);
		for(int j=i+1;j<K;++j) if(d>>j&1) ans+=(1ll<<j)*(c[u][j]-c[v][j]);
		u=v;
	}
	return ans;
}
void solve() {
	cin>>n;
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;++i) cin>>a[i];
	G[0].push_back(1),a[0]=0,dfs(0,0);
	cin>>q;
	for(int u,v,w;q--;) {
		cin>>u>>v,w=LCA(u,v);
		ll ans=qf(u,dep[u]-dep[w]+1);
		if(w!=v) ans+=qg(v,dep[u]+dep[v]-2*dep[w]+1)-qg(w,dep[u]-dep[w]+1);
		cout<<ans+dis[u]+dis[v]-dis[w]*2+a[w]<<"\n";
	}
	for(int i=0;i<=n;++i) G[i].clear();
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Acoipp (赞：0)

首先，对于一条路径 $u \to v$ 我们需要计算的答案可以拆分成若干条 $u \to root$ 的路径，并且每条路径的答案要么是：

$$
\sum_{i=0}^k (a_{p_i} \operatorname{xor} (v+i))
$$

要么是：

$$
\sum_{i=0}^k (a_{p_i} \operatorname{xor} (v-i))
$$

我们以第一种为例介绍以下这个题目的做法。

因为 $p_k=1$，所以我们先考虑 $v=0$ 的情况如何处理，根据位运算题目的经典结论，每个位是相对独立的，因此我们对每个位分开处理。

设当前是第 $k$ 位，容易发现这条路径上的点值先是 $2^k$ 个异或上 $0$，然后 $2^k$ 个异或上 $1$ 这么循环往复，于是我们可以在一遍 DFS 的时候处理完所有位的答案，就可以 $O(n \log n)$ 预处理，$O(1)$ 查询，至此，我们解决了 $v=0$ 的情况。

考虑 $v$ 不等于 $0$，还是第 $k$ 位，我们可以算出从路径的底部往上跳什么时候能够满足 $v$ 的后 $k+1$ 位为 $0$（第 $0 \sim k$ 位）就可以了，剩下的还是像 $v=0$ 那样维护即可，这里需要用到倍增处理（或者离线下来用 $k$ 级祖先做），时间复杂度可以做到 $O(q \log V)$。

第二种情况同理，于是我们在 $O((n+q) \log V)$ 的时间复杂度内解决这道题。

我的代码有点卡空间，并且时间复杂度是 $O(n \log V+q \log n \log V)$，请开 C++20 提交：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
using namespace std;
vector<int> op[N];
ll T,n,i,j,q,x,y,a[N];
int ans0[N][21],ans1[N][21],st[N][21],tg[N][21],sta[N],top,dep[N];
inline ll lca(ll x,ll y){
	if(dep[x]>dep[y]) x^=y^=x^=y;
	for(ll i=20;i>=0;i--) if(dep[st[y][i]]>=dep[x]) y=st[y][i];
	if(x==y) return x;
	for(ll i=20;i>=0;i--) if(st[x][i]!=st[y][i]) x=st[x][i],y=st[y][i];
	return st[x][0];
}
inline ll calc1(ll top,ll bottom,ll bit){return tg[bottom][bit]-tg[st[top][0]][bit];}
inline ll calc0(ll top,ll bottom,ll bit){return dep[bottom]-dep[st[top][0]]-calc1(top,bottom,bit);}
inline void dfs(ll x,ll fa){
	sta[++top] = x;
	for(ll i=0;i<=20;i++) if((a[x]>>i)&1) tg[x][i]++;
	for(ll i=1;i<=20;i++) st[x][i]=st[st[x][i-1]][i-1];
	for(ll i=0;i<=20;i++){
		if(dep[x]>=(1ll<<i)){
			ans0[x][i]=ans1[sta[top-(1ll<<i)]][i]+calc1(sta[top-(1ll<<i)+1],x,i);
			ans1[x][i]=ans0[sta[top-(1ll<<i)]][i]+calc0(sta[top-(1ll<<i)+1],x,i);
		}
		else ans0[x][i]=calc1(1,x,i),ans1[x][i]=calc0(1,x,i);
	}
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		st[op[x][i]][0] = x,dep[op[x][i]] = dep[x]+1;
		for(ll j=0;j<=20;j++) tg[op[x][i]][j]=tg[x][j];
		dfs(op[x][i],x);
	}
	top--;
}
inline ll get_step(ll x,ll step){
	for(ll i=20;i>=0;i--) if((step>>i)&1) x=st[x][i];
	return x;
}
inline ll solve1(ll x,ll v){
	if(x==0) return 0;
	ll ans = 0;
	for(ll i=0;i<=20;i++){
		ll res = 0;
		if((v>>i)&1){
			ll step = (1<<(i+1))-(v&((1<<i+1)-1));
			ll top = get_step(x,step-1);
			res += calc0(top,x,i)+ans0[st[top][0]][i];
		}
		else{
			ll step = (1<<i)-(v&((1<<i+1)-1));
			ll top = get_step(x,step-1);
			res += calc1(top,x,i)+ans1[st[top][0]][i];
		}
		ans += res*(1ll<<i);
	}
	return ans;
}
inline ll solve2(ll x,ll v){
	if(x==0) return 0;
	ll ans = 0;
	for(ll i=0;i<=20;i++){
		ll res = 0;
		if((v>>i)&1){
			ll step = (v&((1<<i+1)-1))-(1ll<<i)+1;
			ll top = get_step(x,step-1);
			res += calc0(top,x,i)+ans0[st[top][0]][i];
		}
		else{
			ll step = (v&((1<<i+1)-1))+1;
			ll top = get_step(x,step-1);
			res += calc1(top,x,i)+ans1[st[top][0]][i];
		}
		ans += res*(1ll<<i);
	}
	return ans;
}
inline ll solve(ll x,ll y){
	ll z = lca(x,y);
	return solve1(x,0)-solve1(st[z][0],dep[x]-dep[st[z][0]])+solve2(y,dep[x]-dep[z]+dep[y]-dep[z])-solve2(z,dep[x]-dep[z]);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n;
		for(i=1;i<n;i++) cin>>x>>y,op[x].push_back(y),op[y].push_back(x);
		for(i=1;i<=n;i++) cin>>a[i];
		dep[1]=1,dfs(1,-1);
		cin>>q;
		while(q--) cin>>x>>y,cout<<solve(x,y)<<endl;
		for(i=1;i<=n;i++){
			op[i].clear(),dep[i]=0,a[i]=0;
			for(j=0;j<=20;j++) st[i][j]=tg[i][j]=ans0[i][j]=ans1[i][j]=0;
		}
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：0)

### [CF1983G Your Loss](https://www.luogu.com.cn/problem/CF1983G)

类似题目：[P6623](https://www.luogu.com.cn/problem/P6623)。

差分转化为对某个 $v$ 和从 $x$ 到根的链 $p_0, p_1, \cdots, p_k$ 求
$$
\sum_{i = 0} ^ k a_{p_i} \oplus (v + i),\quad \sum_{i = 0} ^ k a_{p_i} \oplus (v - i)
$$
对位运算求和的常用套路是按位考虑。设 $b_i$ 为 $a_i$ 在当前位是否为 $1$，则异或操作相当于从某个点开始，向上 $2 ^ c$ 个点的 $b$ 值异或 $1$，再向上 $2 ^ c$ 个点 $b$ 值不变，重复该过程直到跳到根，最后求 $x$ 到根的 $b$ 值的和。

使用 P6623 的套路，求出 $s_i$ 表示 $b_i$ 关于每个点的父亲的前缀和，$t_i$ 表示 $(b_i\oplus 1) - b_i$ 关于每个点的 $2 ^ {c + 1}$ 级父亲的前缀和，则要求的值相当于 $s_x$ 加上一段或两段总长为 $2 ^ c$ 的点的 $t$ 值之和，通过预处理 $t_i$ 关于每个点的父亲的前缀和快速计算。可通过将所有位置取反避免出现两段的情况，减少分类讨论。

跳到开始异或 $1$ 的位置要求 $k$ 级祖先，可离线做到 $\mathcal{O}(1)$。时间复杂度 $\mathcal{O}(n\log V + qu\log V)$，其中 $u$ 是计算 $k$ 级祖先的复杂度。[代码](https://codeforces.com/contest/1983/submission/270724363)。

---

