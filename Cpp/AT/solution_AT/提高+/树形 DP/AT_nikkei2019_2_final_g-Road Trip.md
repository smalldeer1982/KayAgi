# Road Trip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_g

$ N $ 頂点の無向木があり、頂点には $ 1 $ から $ N $ の、辺には $ 1 $ から $ N-1 $ の番号がついています。辺 $ i $ は 頂点 $ A_i $ と 頂点 $ B_i $ を結んでおり、$ C_i $ の重みを持ちます。重みの値は負である可能性もあることに注意してください。

この木の連結な部分グラフを「運転部分木」と呼び、特に頂点 $ u $ と頂点 $ v $ を含むものを「$ u-v $ 運転部分木」とします。ある運転部分木が持つ辺の重みの合計を、その運転部分木の「楽しさ」とします。

$ Q $ 個の整数組 $ (U_i,\ V_i) $ が与えられるので、各 $ i $ に対して次の質問に答えてください。

- $ U_i-V_i $ 運転部分木の楽しさとしてあり得る最大値は何か。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N\ (1\ \leq\ i\ \leq\ N\ -\ 1) $
- 与えられるグラフは木を成す
- $ -10^9\ \leq\ C_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N\ -\ 1) $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_i\ <\ V_i\ \leq\ N\ (1\ \leq\ i\ \leq\ Q) $
- 入力はすべて整数である

### Sample Explanation 1

\- $ 1 $ つ目の質問に対しては、頂点 $ 2,\ 3,\ 4 $ からなる部分グラフを運転部分木として選ぶと楽しさは $ 20+(-1) $ となり、これが $ 2-3 $ 運転部分木の楽しさのうち最大です。 - $ 2 $ つ目と $ 3 $ つ目の質問に対しては、頂点 $ 1,\ 2,\ 3,\ 5,\ 6,\ 7 $ からなる部分グラフを運転部分木として選ぶと楽しさは $ (-10)+20+1+3+2 $ となり、どちらの質問でもこれが最大です。

## 样例 #1

### 输入

```
7
1 3 -10
2 3 20
3 4 -1
1 6 1
5 6 3
6 7 2
3
3 4
5 7
2 6```

### 输出

```
19
16
16```

## 样例 #2

### 输入

```
7
1 3 -1100000
2 3 -1010000
3 4 -1001000
1 6 -1000100
5 6 -1000010
6 7 -1000001
3
3 4
5 7
2 6```

### 输出

```
-1001000
-2000011
-3110100```

## 样例 #3

### 输入

```
18
2 8 -133775141
3 16 -311103251
4 11 849496136
9 14 -442278959
8 13 946094213
8 14 714669159
5 8 210787603
5 11 8973730
10 15 581490293
10 16 -347827761
10 11 -126622449
7 11 431568122
6 7 -458490133
6 17 -314331217
1 6 -220056853
1 12 -981864951
12 18 183014767
20
1 15
7 10
6 12
1 18
3 16
4 8
9 12
2 14
1 11
3 8
14 17
4 17
12 18
3 17
1 10
5 9
9 15
4 13
5 11
4 7```

### 输出

```
2937909821
3616456807
2139059637
2139059637
2957525795
3616456807
1696780678
3482681666
2937909821
2957525795
2843635457
2843635457
2139059637
2184704445
2937909821
3174177848
3174177848
3616456807
3616456807
3616456807```

# 题解

## 作者：ARIS2_0 (赞：3)

### 前言

校内模拟赛考了，感觉是道非常不错的题目。

### 思路

我们设每次询问给出的点为 $s,t$，且 $\operatorname{LCA}(s,t)=l$。

我们将可能要选的边分为以下几种：

- $s$ 到 $t$ 的路径上的，必须选。

- $s$ 子树内和 $t$ 子树内的。

- 点 $l$ 上面的边。

- $s,t$ 路径上的点（不包括 $s,t$）的子树内。

第一种贡献显然可以树剖/倍增维护。

第二种贡献，我们设 $f_i$ 为 $i$ 子树内，选若干条边能得到的最大贡献，则有：

$$f_i=\sum\limits_{x} \max(0,f_{x}+val_{x})$$

其中 $x$ 为 $i$ 的儿子，$val_x$ 为 $i$ 连向 $x$ 的边的边权。

第三种贡献，我们设 $g_i$ 为选若干条 $i$ 上面的边能得到的最大贡献，则有：

$$g_i=\max(0,g_{fa_i}+f_{fa_i}-\max(0,f_i+val_i)+val_i)$$

其中，$fa_i$ 表示 $i$ 的祖先。

$g_{fa_i}+f_{fa_i}-\max(0,f_i+val_i)$ 是点 $fa_i$ **无视子树 $i$ 可以得到的贡献**，$+val_i$ 是要保证选出的边和点 $i$ 连通。

第四种贡献，我们考虑暴力枚举路径上的每个点 $i$（不包括 $s,t$），这个点对答案的贡献为：

$$f_i-\sum\limits_u \max(0,f_u+val_u)$$

其中 $u$ 满足点 $u$ 在路径上且是 $i$ 的儿子。

这样做单次询问是 $O(n)$ 的，显然超时。

因为除了点 $l$，所有点都**有且只有一个满足条件的 $u$ 点**，我们考虑将贡献放到 $u$ 点计算。

设 $det_u=f_{fa_u}-\max(0,f_u+val_u)$，则第四类贡献等价于：

$$(\sum\limits_i det_i)-f_l$$

其中 $i$ 在路径上且 $i\not=l$。

要减去 $f_{l}$ 的原因是，$l$ 有两个符合条件的 $u$ 点，所以 $f_l$ 多算了一边，要减去。

上面这个式子显然可以树剖/倍增维护，于是就做完了。

### Code

虽然理论上是要判 $s,t$ 的 $\operatorname{LCA}$ 是 $s$ 或 $t$ 的情况的，但是因为答案的神秘容斥，不特判也能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//因为 C++20 下 size 是关键字所以 define 了一下
#define size skdjrugfhksug
const int maxn=2e5+10;
int n,q;
struct node{int to,v;};
vector<node>v[maxn];
int f[maxn],g[maxn];
int dep[maxn],size[maxn],wc[maxn],fa[maxn],val[maxn];
bool isw[maxn];
void dfs1(int x){
    size[x]=1;
    for(node pos:v[x]){
        int y=pos.to,va=pos.v;
        if(y!=fa[x]){
            fa[y]=x;
            dep[y]=dep[x]+1;
            val[y]=va;
            dfs1(y);
            size[x]+=size[y];
            f[x]+=max(0ll,f[y]+val[y]);
            if(size[y]>size[wc[x]])wc[x]=y;
        }
    }
    isw[wc[x]]=1;
}
int top[maxn],d[maxn],p[maxn],tot=0;
int det[maxn];
void dfs2(int x){
    d[p[x]=++tot]=x;
    top[x]=isw[x]?top[fa[x]]:x;
    if(wc[x]){
        det[wc[x]]=f[x]-max(0ll,f[wc[x]]+val[wc[x]]);
        g[wc[x]]=max(0ll,g[x]+det[wc[x]]+val[wc[x]]);
        dfs2(wc[x]);
    }
    for(node pos:v[x]){
        int y=pos.to;
        if(y!=fa[x] and y!=wc[x]){
            det[y]=f[x]-max(0ll,f[y]+val[y]);
            g[y]=max(0ll,g[x]+det[y]+val[y]);
            dfs2(y);
        }
    }
}
int sval[maxn],sdet[maxn];
void presolve(){
    for(int i=1;i<=n;i++){
        sval[i]=sval[i-1]+val[d[i]];
        sdet[i]=sdet[i-1]+det[d[i]];
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
int valsum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans+=sval[p[x]]-sval[p[top[x]]-1];
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    ans+=sval[p[y]]-sval[p[x]];
    return ans;
}
int detsum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ans+=sdet[p[x]]-sdet[p[top[x]]-1];
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    ans+=sdet[p[y]]-sdet[p[x]];
    return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
    for(int i=1,ps,qs,rs;i<n;i++){
        cin>>ps>>qs>>rs;
        v[ps].push_back(node{qs,rs});
        v[qs].push_back(node{ps,rs});
    }
    dfs1(1);
    dfs2(1);
    presolve();
    cin>>q;
    while(q--){
        int x,y;cin>>x>>y;
        if(dep[x]>dep[y])swap(x,y);
        int pos=lca(x,y);
        cout<<valsum(x,y)+f[x]+f[y]+g[pos]+detsum(x,y)-f[pos]<<"\n";
    }
	return 0;
}
```

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_2_final_g)。

非常典且好想的容斥。

## 思路

设 $u\to v$ 的路径为 $P$，令 $d=\mathrm{LCA}(u,v)$，$f_u$ 表示在 $u$ 子树下包含 $u$ 节点联通块的最大权值，$g_u$ 表示 $u$ 不包括 $u$ 子树下节点但包括 $u$ 节点联通块的最大权值，这两个可以用换根 DP 求出，那么答案就是

$$\sum_{x\in P}\left(f_x- \sum_{y\in son_x\cap P}\max(f_y+w,0)\right) +g_d +W(u,v) $$

$w(u,v)$ 表示 $u\to v$ 的距离。

前缀和维护即可，时间复杂度 $\mathcal O(n+q\log n)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define mk make_pair
using namespace std;

const int Maxn=1e6+7;
int n,Q;
vector<pii >e[Maxn];

ll f[Maxn],g[Maxn],sum[Maxn],sumf[Maxn];
int son[Maxn],top[Maxn],id[Maxn],dfn[Maxn],tot,sz[Maxn],fa[Maxn],dep[Maxn];
void dfs1(int u,int ft){
    sz[u]=1; fa[u]=ft; dep[u]=dep[ft]+1;
    for(auto [v,w]:e[u]){
        if(v==ft) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]) son[u]=v;
        f[u]+=max(f[v]+w,0ll); sum[v]=max(f[v]+w,0ll)-w;
    }
    sumf[u]=f[u];
}
void dfs2(int u,int tp){
    top[u]=tp; dfn[u]=++tot; id[tot]=u;
    sumf[u]+=sumf[fa[u]];sum[u]+=sum[fa[u]];
    for(auto [v,w]:e[u])
        if(v!=fa[u]) g[v]=max(0ll,g[u]+f[u]-max(0ll,f[v]+w)+w);
    if(son[u]) dfs2(son[u],tp);
    for(auto [v,w]:e[u]){
        if(v==son[u] or v==fa[u]) continue;
        dfs2(v,v);
    }
}
inline int LCA(int u,int v){
    while(top[u]^top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    return v;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        e[u].emplace_back(v,w);
        e[v].emplace_back(u,w);
    }
    dfs1(1,0);
    dfs2(1,1);

    scanf("%d",&Q);
    while(Q--){
        int u,v;
        scanf("%d%d",&u,&v); int d=LCA(u,v);
        ll ans=sumf[u]+sumf[v]-sumf[d]-sumf[fa[d]];
        ans=ans-(sum[u]+sum[v]-sum[d]*2); 
        printf("%lld\n",ans+g[d]);     
    }

    return 0;
}

```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{AT\_nikkei2019\_2\_final\_g}$

> - 给定 $n$ 个点的树，边带权，$q$ 次询问给定 $u_i,v_i$，选出一个包含 $u_i,v_i$ 的连通块并最大化边权和。
> - $1 \le n,q \le 2 \cdot 10^5,0 \le |w_i| \le 10^9$。

这玩意还 $^*3000$，感觉最多 $^*2000$，哈哈。

显然 $u_i \to v_i$ 的路径必选，剩余部分大概有三部分（令 $d = \operatorname{LCA}(u_i,v_i)$）：

- $u_i,v_i$ 的子树内部。
- $d$ 的祖先。
- $u_i \to d \to v_i$ 的链的两侧。

我们一步一步的来处理。

### [1] $u_i,v_i$ 的子树内部。

考虑设 $f_i$ 表示选以 $i$ 为根的连通块的最大权值，显然有转移 $f_u = \sum \limits_{v \in \text{son}(u)} \max(f_v + w_{u,v},0)$。从下到上转移，时间复杂度线性。

### [2] $d$ 的祖先。

设 $g_i$ 表示选 $i$ 为叶子和其祖先的连通块的最大权值，有 $g_i = \max(0,g_{fa_i} + f_{fa_i} - \max(f_i+w_{i,fa_{i}},0))$。从上到下转移，时间复杂度线性。

### [3] $u_i \to d \to v_i$ 的链的两侧。

考虑对原树重链剖分，令 $h_i = f_i - \max(f_{son}+w_{son,i},0)$，其中 $son$ 是重儿子。那么对于一段完整的重链，可以直接对 $h_i$ 求链和。从链顶 $u$ 跳父亲时，只需要考虑 $fa$ 的贡献，显然是 $f_{fa} - \max(f_u+w_{u,fa},0)$。这部分时间复杂度 $\mathcal O(n \log n)$。

---

上面的做法太暴力啦！

注意到我们把两侧的点的贡献挂到父亲上减去儿子即可。即 $\max(f_d+w_{d,fa_d},0)-w_{d,fa_d}+\sum\limits_{i \in \operatorname{path}(u,v)} f_i - \max(f_i + w_{i,fa_i},0)+w_{i,fa_i}$，维护前缀和时间复杂度线性。

那么这道题至此就做完了，瓶颈在求 $\operatorname{LCA}$，时间复杂度 $\mathcal O(n \log n + q)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 27.03.2024 19:29:37
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,u,v,w,st[20][N],dfn[N],tot,val[N],q,d; 
vector<pair<int,int>> gr[N]; ll f[N],g[N],sm1[N];
void dfs1(int u,int fa){
    st[0][dfn[u] = ++tot] = fa;
    for(auto [v,w] : gr[u]) if(v != fa)
        dfs1(v,u),val[v] = w,f[u] += max(f[v] + w,0ll);
}void dfs2(int u,int fa){
    g[u] = max(0ll,g[fa] + f[fa] - max(f[u] + val[u],0ll) + val[u]), 
    sm1[u] = sm1[fa] + f[u] - max(f[u] + val[u],0ll) + val[u];
    for(auto [v,w] : gr[u]) if(v != fa) dfs2(v,u);
}int cmp(int u,int v){return dfn[u] < dfn[v] ? u : v;}
int lca(int u,int v){
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
    int k = __lg(v - u);
    return cmp(st[k][u+1],st[k][v-(1<<k)+1]);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> u >> v >> w,gr[u].emplace_back(v,w),gr[v].emplace_back(u,w);
    dfs1(1,0),dfs2(1,0);
    for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)  
        st[j][i] = cmp(st[j-1][i],st[j-1][i+(1<<j-1)]);
    for(cin >> q;q --;)
        cin >> u >> v,d = lca(u,v),
        cout << sm1[u] + sm1[v] - 2 * sm1[d] + f[d] + g[d] << "\n";
}
```

---

