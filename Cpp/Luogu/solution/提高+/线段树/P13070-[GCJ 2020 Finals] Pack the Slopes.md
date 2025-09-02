# [GCJ 2020 Finals] Pack the Slopes

## 题目描述

你正在组织一群滑雪者。滑雪者们将前往一座被全天租用的大型雪山。

雪山上有编号为 $1$ 到 $\mathbf{N}$ 的 $\mathbf{N}$ 个休息点，它们通过 $\mathbf{N}-1$ 条滑雪道相连。每条滑雪道从一个休息点出发，直接通向另一个休息点，中途没有其他滑雪道或休息点。滑雪道只能单向通行。

每位滑雪者从山顶休息点（编号 $1$）出发，沿一条滑雪道到达另一个休息点。之后，滑雪者可以继续沿另一条滑雪道前往下一个休息点，以此类推。当滑雪者到达目标休息点时，他们会结束当天的滑雪并前往滑雪小屋享用热可可。目标休息点不能是山顶休息点。但注意，滑雪者的目标休息点可以是零条或多条滑雪道的起点——即滑雪者不一定要用完所有可用滑雪道：他们可以小心地步行下山！对于所有休息点，从山顶休息点出发到达它的滑雪道序列是唯一的。

每条滑雪道每天仅能容纳一定数量的滑雪者，超过后雪道会因积雪过乱而无法使用。此外，滑雪场会根据滑雪者使用的每条滑雪道收取费用或发放奖励。每条滑雪道的价格可能不同，每位滑雪者需支付其使用的每条滑雪道的价格。价格可以是正数、零甚至负数（负数代表测试该滑雪道的奖励）。作为组织者，你需要代表滑雪者支付所有费用并收取所有奖励。注意，若多名滑雪者使用同一条滑雪道，该滑雪道的费用或奖励会被多次计算。你$ $支付的总费用减去收取的总奖励即为本次旅行的总支出。支出可能为正、零或负（负支出表示你实际上赚了钱）。

作为组织者，你需要计算能安排到雪山上的最大滑雪者数量，并求出在该最大数量下的最小可能支出。

## 说明/提示

**样例解释**

在样例 #1 中，可以安排 $1$ 名滑雪者前往休息点 $4$，$1$ 名前往休息点 $3$，$2$ 名前往休息点 $2$。

在样例 #2 中，可以安排 $3$ 名滑雪者前往休息点 $2$，$2$ 名前往休息点 $5$，$2$ 名前往休息点 $4$。

注意：测试用例中第一条滑雪道的起点不一定是山顶休息点，且可能存在 $\mathbf{U_i} > \mathbf{V_i}$ 的情况。

**数据范围**

- 对所有 $i$，满足 $1 \leqslant \mathbf{U_i} \leqslant \mathbf{N}$。
- 对所有 $i$，满足 $2 \leqslant \mathbf{V_i} \leqslant \mathbf{N}$（没有滑雪道以山顶休息点为终点）。
- 对所有 $i$，满足 $\mathbf{U_i} \neq \mathbf{V_i}$。
- 对所有 $i$，满足 $1 \leqslant \mathbf{S_i} \leqslant 10^5$。
- 对所有 $i$，满足 $-10^5 \leqslant \mathbf{C_i} \leqslant 10^5$。
- 对所有休息点 $r$，从山顶休息点到 $r$ 的滑雪道序列唯一。

**测试集 1（10 分，可见判定）**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $2 \leqslant \mathbf{N} \leqslant 1000$。

**测试集 2（22 分，隐藏判定）**

- $\mathbf{T} = 17$。
- $2 \leqslant \mathbf{N} \leqslant 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
4
1 2 2 5
1 3 2 5
3 4 1 -2
7
4 7 2 2
1 3 5 5
1 4 2 -1
3 2 3 -2
3 5 2 -1
3 6 2 2```

### 输出

```
Case #1: 4 18
Case #2: 7 15```

# 题解

## 作者：Jorisy (赞：0)

标签不诈骗题，这和启发式合并啥关系？用线段树、树链剖分维护简单贪心。

设根到节点 $i$ 的边权和为 $a_i$。则一个显然的贪心是，我们肯定会让一个人走到当前所能走到的点中 $a_i$ 最小的。

证明很容易。

不妨设我们依次选择的节点 $i$ 对应的 $a_i$ 单调不降。

如果不走到当前最优的点，而是走到其他更劣的点，那么就会有一段原本需要被走的边没有被走。由于决策逐渐变劣，所以这些边此后也一定能走。那么显然可以改变决策，抛弃劣的方案，选择走这些边，使得方案更优。

于是用树剖维护每个点还能被多少人经过即可。时间复杂度 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define N 100005
#define ll long long
#define mod 
#define inf (ll)1e18
using namespace std;

vector<int>g[N];
int n,fa[N],dfn[N],idfn[N],sz[N],top[N],son[N];
ll a[N],c[N];
struct segt{
    #define mid (l+r>>1)
    #define lc (mid<<1)
    #define rc (mid<<1|1)
    struct node{
        ll mins,tag;
    }sgt[N<<1];

    void upd(node &x,node y,node z)
    {
        x.mins=min(y.mins,z.mins);
    }

    void build(int i,int l,int r)
    {
        sgt[i].tag=0;
        if(l>=r)
        {
            sgt[i].mins=c[idfn[r]];
            return;
        }
        build(lc,l,mid);
        build(rc,mid+1,r);
        upd(sgt[i],sgt[lc],sgt[rc]);
    }

    void psd(int i,int l,int r)
    {
        ll d=sgt[i].tag;
        sgt[i].tag=0;
        sgt[lc].mins+=d;
        sgt[lc].tag+=d;
        sgt[rc].mins+=d;
        sgt[rc].tag+=d;
    }

    void mdf(int i,int l,int r,int x,int y,int d)
    {
        if(x<=l&&r<=y)
        {
            sgt[i].mins+=d;
            sgt[i].tag+=d;
            return;
        }
        if(sgt[i].tag) psd(i,l,r);
        if(x<=mid) mdf(lc,l,mid,x,y,d);
        if(y>mid) mdf(rc,mid+1,r,x,y,d);
        upd(sgt[i],sgt[lc],sgt[rc]);
    }

    ll qry(int i,int l,int r,int x,int y)
    {
        if(x<=l&&r<=y) return sgt[i].mins;
        if(sgt[i].tag) psd(i,l,r);
        ll res=inf;
        if(x<=mid) res=min(res,qry(lc,l,mid,x,y));
        if(y>mid) res=min(res,qry(rc,mid+1,r,x,y));
        return res;
    }
}sgt;

void dfs0(int x,int lst)
{
    fa[x]=lst;
    sz[x]=1;
    a[x]+=a[lst];
    for(auto y:g[x])
    {
        dfs0(y,x);
        sz[x]+=sz[y];
        if(sz[son[x]]<sz[y]) son[x]=y;
    }
}

void dfs(int x,int tp)
{
    top[x]=tp;
    dfn[x]=++dfn[0];
    idfn[dfn[0]]=x;
    if(son[x]) dfs(son[x],tp);
    for(auto y:g[x])
    {
        if(y==son[x]) continue;
        dfs(y,y);
    }
}

ll qry(int u)
{
    ll res=inf;
    while(u)
    {
        res=min(res,sgt.qry(1,1,n,dfn[top[u]],dfn[u]));
        u=fa[top[u]];
    }
    return res;
}

void mdf(int u,int x)
{
    while(u)
    {
        sgt.mdf(1,1,n,dfn[top[u]],dfn[u],-x);
        u=fa[top[u]];
    }
}

void sol()
{
    cin>>n;
    for(int i=1;i<=n;i++) g[i].clear();
    fill(sz+1,sz+n+1,0);
    fill(son+1,son+n+1,0);
    a[1]=0;
    c[1]=inf;
    for(int i=1;i<n;i++)
    {
        int u,v,s,x;
        cin>>u>>v>>s>>x;
        g[u].push_back(v);
        c[v]=s;
        a[v]=x;
    }
    dfn[0]=0;
    dfs0(1,0);
    dfs(1,1);
    sgt.build(1,1,n);
    vector<pair<ll,int>>vec;
    for(int i=2;i<=n;i++) vec.push_back({a[i],i});
    sort(vec.begin(),vec.end());
    ll cnt=0,ans=0;
    static int cas=0;
    for(auto [i,j]:vec)
    {
        ll x=qry(j);
        if(!x) continue;
        cnt+=x;
        ans+=i*x;
        mdf(j,x);
    }
    cout<<"Case #"<<++cas<<": "<<cnt<<' '<<ans<<'\n';
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) sol();
    return 0;
}
```

---

## 作者：冷却心 (赞：0)

我再也不诋毁拿不拿不写摇滚了。我宣布逃亡是神曲。

标签诈骗题，这和线段树，树链剖分啥关系？用启发式合并维护简单贪心。

我们对每个节点维护一个可重集 $\{(w,c)\}$ 表示以当前节点为根的子树内的答案，$(w,c)$ 表示路径总和为 $w$ 的人数为 $c$。考虑合并子树的答案。设当前位于点 $u$，他的若干儿子为 $v_i$，每个儿子的可重集为 $S_i$，到这个儿子的边的两个权分别为 $w_i,c_i$。首先每个儿子 $v_i$ 的答案都要走到父亲的这一条边，所以要支持集合 $S_i$ 全局加法 $c_i$，懒标记直接做，并且现在多出一种从儿子直接走到父亲的路径，所以在全局加法之前要加入 $(0,w_i)$，但是此时答案集合的总人数可能大于了边的承载量 $w_i$，所以要维护每个集合的人数总和，然后贪心的优先删除花费更大的人数。最后把这些集合合并得到当前点的答案。

时间复杂度 $\mathcal O(n\log^2 n)$，启发式合并一只 $\log$，`multiset` 一只 $\log$。注意贪心删除人数使得总人数满足限制这个的实现，笔者第一发写假被卡成变成 $\mathcal O(n^2 \log n)$ /ll。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
int n; 
struct Info { int v; LL w, c; };
vector<Info> G[N];
multiset<pair<LL, LL> > st[N]; LL tag[N], sum[N]; int rt[N], ptot;
int merge(int a, int b) {
	if (st[a].size() < st[b].size()) swap(a, b);
	for (auto [x, y] : st[b]) st[a].insert({x + tag[b] - tag[a], y});
	st[b].clear(); sum[a] += sum[b]; sum[b] = 0; return a;
}
void DFS(int u) {
	rt[u] = ++ ptot;
	for (auto [v, w, c] : G[u]) {
		DFS(v); sum[rt[v]] += w, st[rt[v]].insert({0 - tag[rt[v]], w}); tag[rt[v]] += c;
		while (sum[rt[v]] > w) {
			auto [a, b] = *st[rt[v]].rbegin(); 
			st[rt[v]].erase(st[rt[v]].find({a, b}));
			sum[rt[v]] -= b; if (sum[rt[v]] >= w) continue;
			b = w - sum[rt[v]]; sum[rt[v]] = w; st[rt[v]].insert({a, b});
		} rt[u] = merge(rt[u], rt[v]);
	} return ;
}
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	for (int __ = 1; __ <= _; __ ++) {
		cin >> n;
		for (int i = 1, u, v, w, c; i < n; i ++)
			cin >> u >> v >> w >> c, G[u].push_back({v, w, c});
		DFS(1); LL res = 0, cnt = 0;
		for (auto [a, b] : st[rt[1]]) res += 1ll * (a + tag[rt[1]]) * b, cnt += b;
		cout << "Case #" << __ << ": " << cnt << " " << res << "\n";
		ptot = 0; for (int i = 1; i <= n; i ++) G[i].clear(), rt[i] = sum[i] = tag[i] = 0, st[i].clear();
	}
	return 0;
}
```

---

