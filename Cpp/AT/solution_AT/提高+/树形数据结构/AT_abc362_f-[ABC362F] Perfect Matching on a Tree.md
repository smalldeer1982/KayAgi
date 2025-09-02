# [ABC362F] Perfect Matching on a Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_f

$ N $ 頂点の木 $ T $ が与えられます。$ T $ の頂点には $ 1 $ から $ N $ の番号がついており、 $ i\,(1\leq\ i\ \leq\ N-1) $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいます。

$ T $ を用いて、$ N $ 頂点の完全グラフ $ G $ を次のように定めます。

- $ G $ の頂点 $ x $ と頂点 $ y $ の間の辺の重み $ w(x,y) $ を、$ T $ における頂点 $ x $ と頂点 $ y $ の間の最短距離とする
 
$ G $ の**最大重み最大マッチング**を一つ求めてください。すなわち、$ \lfloor\ N/2\ \rfloor $ 個の頂点のペアの集合 $ M=\{(x_1,y_1),(x_2,y_2),\dots,(x_{\lfloor\ N/2\ \rfloor},y_{\lfloor\ N/2\ \rfloor})\} $ であって、各頂点 $ 1,2,\dots,\ N $ が $ M $ に現れる回数がたかだか $ 1 $ 回であるようなもののうち、 $ \displaystyle\ \sum_{i=1}^{\lfloor\ N/2\ \rfloor}\ w(x_i,y_i) $ が最大であるものを一つ求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- 入力されるグラフは木である
- 入力はすべて整数
 
### Sample Explanation 1

$ T $ において、頂点 $ 2,4 $ 間の距離は $ 2 $、頂点 $ 1,3 $ 間の距離は $ 2 $ なので、マッチング $ \{(2,4),(1,3)\} $ の重みは $ 4 $ です。重みが $ 4 $ より大きいマッチングは存在しないので、これが最大重み最大マッチングの一つです。他にも、 ``` 2 3 1 4 ``` などを出力しても正解になります。

### Sample Explanation 2

$ T $ において、頂点 $ 1,3 $ 間の距離は $ 2 $ なので、マッチング $ \{(1,3)\} $ の重みは $ 2 $ です。重みが $ 2 $ より大きいマッチングは存在しないので、これが最大重み最大マッチングの一つです。他にも、 ``` 3 1 ``` を出力しても正解になります。

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
2 4
1 3```

## 样例 #2

### 输入

```
3
1 2
2 3```

### 输出

```
1 3```

# 题解

## 作者：BrotherCall (赞：22)

非常奇妙的一题。

设 $dis(u,v)$ 代表 $u$ 到 $v$ 的距离。

对于任意两对点 $(u_i,v_i)$ 和 $(u_j , v_j)$，若两者的路径没有交点，则此时交换 $v_i$ 和 $v_j$，新点对的路径一定存在交点，且 $dis(u_i,v_j) + dis(u_j,v_i) > dis(u_i,v_i) + dis(u_j,v_j)$。

所以选出来的点对的路径一定是**两两相交**的。

而由于又是在树上，所以这些路径**至少存在同一个交点**。

**用归纳法证明:**

当 $i = 2$ 时，两条路径存在至少一个交点。

假如已经有 $i \geq 2$ 条路径两两相交，再加进去一条路径和前 $i$ 条路径都有交点，若这些交点中存在 不是前 $i$ 条路径共同的交点 的点，则一定会成环，与树的性质矛盾。

所以新加的点对的路径与老路径的交点一定被老交点包含。

**所以题目转化为：构造点对使所有点对形成的路径经过同一个点，并使 $\sum dis(u_i,v_i)$ 最大。**

我们令这个经过的交点为树的根，记为 $rt$。

为了使每条路径都穿过 $rt$，每次需要找 $rt$ 的两个不同子节点子树中没选过的点 作为一对点对。

根据这个我们知道，当根固定时，答案也固定，为 $\sum dis(u,rt)$。

看到这个式子很容易想到树形 dp，但事实上若 $rt$ 不是树的重心，根本无法取到合法的点集，所以只需要找到树的重心再分配就行了，无需 dp。

**关于“若 $rt$ 不是树的重心，根本无法取到合法的点集”的证明：**

若 $rt$ 不是树的重心，则 $rt$ 子节点中一定存在一个点数 $\displaystyle > \lfloor \frac{n}{2} \rfloor$ 的子树，这样的话无法从其他子节点子树中找到足够多的点和这个子树中的点配对。

所以题意就被转化为：找到树的重心 $rt$，将其定为根，再找 $\displaystyle \lfloor \frac{n}{2}\rfloor$ 个点对，使每个点对的两个数分别属于 $rt$ 不同子节点的子树中。

现在只剩最后一步了，如何选出这些点对。

我的做法是给 $rt$ 的每个子节点开一个 vector，记录其中有哪些点。再开个大根堆，第一维是子树中未匹配元素的个数，第二维是子树根节点的编号。每次取堆顶的两个对应的子树中的点，然后再让两者点数减一，若点数为 0 则不再加进堆中即可。

[提交记录。](https://atcoder.jp/contests/abc362/submissions/55605028)

[视频讲解。](https://www.bilibili.com/video/BV16b421E7eq)

---

## 作者：zrl123456 (赞：9)

[[ABC362F] Perfect Matching on a Tree ](https://www.luogu.com.cn/problem/AT_abc362_f)  

题目考察：dfs，重心。   
题目简述：  
给你一棵 $n$ 个点的树，选出 $\displaystyle\lfloor\frac{n}{2}\rfloor\times2$ 个点，这些点两两不同，有 $\displaystyle\lfloor\frac{n}{2}\rfloor$ 个点设为 $\{x_{\lfloor\frac{n}{2}\rfloor}\}$，另外 $\displaystyle\lfloor\frac{n}{2}\rfloor$ 个点设为 $\{y_{\lfloor\frac{n}{2}\rfloor}\}$，使得 $\displaystyle\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}\text{dist}(x_i,y_i)$ 最大。  
其中 $\text{dist}(x,y)$ 表示从点 $x$ 到点 $y$ 所经过的最少边数。  
数据范围：  
- $2\le n\le 2\times 10^5$
------------
首先我们猜想，若 $\displaystyle\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}\text{dist}(x_i,y_i)$ 最大，则从 $x_i$ 到 $y_i$ 的这条路径一定经过了这棵树的重心。   
证明：  
我们设根节点为重心，再设从 $x_k$ 到 $y_k$ 的这条路径没有经过这棵树的重心，则一定有一从 $x_j$ 到 $y_j$ 的路径不与其相交，因为若所有 $x_i$ 到 $y_i$ 的路径都与其相交，则所有的点对中要么有至少一个点在 $x_k$ 和 $y_k$ 的子树内（然而这是不可能的，因为根据重心的定义，不会有一个子树的大小超过 $\displaystyle\lfloor\frac{n}{2}\rfloor$），要么所有的点都能在不经过重心的情况下到达 $x_k$ 到 $y_k$ 的路径上的一个点（然而这也是不可能的，因为这个点、$x_k$ 和 $y_k$ 路径上的一个点和重心形成了一个环，这不符合树的定义）。总而言之，所有 $x_i$ 到 $y_i$ 的路径两两相交。  
下面我们继续来证明选重心为根节点存在最优解。若不选重心作伪根节点，则有一组 $x_k$ 和 $y_k$ 没有经过重心，那么我们找来一组 $x_j$ 和 $y_j$（$x_j$ 和 $y_j$ 都不在 $x_k$ 和 $y_k$ 所在的子树内），将 $y_j$ 与 $y_k$ 交换，若存在最优解，则 $\text{dist}(x_j,y_j)+\text{dist}(x_k,y_k)<\text{dist}(x_j,y_k)+\text{dist}(x_k,y_j)$。  
下面我们来证明该式成立（下面设点 $u$ 的深度为 $dep_u$，$u$ 和 $v$ 的 LCA 为 $\text{lca}(u,v)$）：  
$$\text{dist}(x_j,y_j)+\text{dist}(x_k,y_k)=dep_{x_j}+dep_{y_j}+dep_{x_k}+dep_{y_k}-2dep_{\text{lca}(x_k,y_k)}$$
而：   
$$\text{dist}(x_j,y_k)+\text{dist}(x_k,y_j)=dep_{x_j}+dep_{y_j}+dep_{x_k}+dep_{y_k}$$
因为 $dep_{\text{lca}(x_k,y_k)}>0$，所以 $\text{dist}(x_j,y_j)+\text{dist}(x_k,y_k)<\text{dist}(x_j,y_k)+\text{dist}(x_k,y_j)$。  
证毕。  

由于选择重心的话最后的答案是相同的（甚至选一个最大子树的大小不大于 $\displaystyle\lfloor\frac{n}{2}\rfloor$ 都可以），上面已经证明，答案是 $\displaystyle\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}dep_{x_i}+dep_{y_i}$，则我们在其里面任选一个即可。  

那么我们考虑如何选出这些点对，由于重心的基本性质没有任意一颗子树的大小超过 $\displaystyle\lfloor\frac{n}{2}\rfloor$，所以我们设 $\{dfn_n\}$ 为以树的重心为根所得的前序遍历，则点 $dfn_i$ 和点 $\displaystyle dfn_{i+\lfloor\frac{n}{2}\rfloor}$ 一定不在一个子树内，所以将 $dfn_i$ 和 $\displaystyle dfn_{i+\lfloor\frac{n}{2}\rfloor}$ 放在一组是没有问题的。  
如果 $n$ 是奇数怎么办？由于答案是 $\displaystyle\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}dep_{x_i}+dep_{y_i}$，所以我们要丢弃最小的 $dep_i$，于是我们丢弃根节点（重心）。  

时间复杂度为 $\Theta(n)$。  
代码：  
```cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define int long long
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(reg int i=x;i<=(y);++i) 
#define per(i,x,y) for(reg int i=x;i>=(y);--i)
#define rpr(i,x,y,z) for(reg int i=x;i<=(y);i+=z)
#define epe(i,x,y,z) for(reg int i=x;i>=(y);i-=z)
#define repe(i,x,y) for(i=x;i<=(y);++i) 
#define endl '\n'
#define INF 1e16
#define pb push_back
#define fi first
#define se second
#define lcm(x,y) x/__gcd(x,y)*y
#define ull unsigned long long
#define prr make_pair
#define pii pair<int,int> 
#define gt(s) getline(cin,s)
#define at(x,y) for(reg auto x:y)
#define ff fflush(stdout)
#define mt(x,y) memset(x,y,sizeof(x))
#define idg isdigit
#define fp(s) string ssss=s;freopen((ssss+".in").c_str(),"r",stdin);freopen((ssss+".out").c_str(),"w",stdout);
#define sstr stringstream 
#define all(x) x.begin(),x.end()
#define mcy(a,b) memcpy(a,b,sizeof(b))
using namespace std;
const int N=2e5+5;
vector<int>g[N],dfn(1,0);
bool vis[N];
int siz[N],mx[N];
inl void dfs(int u,int &rt,int n){
	vis[u]=siz[u]=1;
	at(v,g[u])
		if(!vis[v]){
			dfs(v,rt,n);
			siz[u]+=siz[v];
			mx[u]=max(mx[u],siz[v]);
		}
	mx[u]=max(mx[u],n-siz[u]);
	if(mx[u]<=n>>1) rt=u;
	vis[u]=0;
}
inl void dfs2(int u){
	vis[u]=1;
	dfn.pb(u);
	at(v,g[u])
		if(!vis[v]) dfs2(v);
	vis[u]=0;
}
signed main(){
	fst;
	reg int n,rt=0;
	cin>>n;
	rep(i,2,n){
		reg int u,v;
		cin>>u>>v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1,rt,n);
	dfs2(rt);
	if(n&1)
		rep(i,2,(n>>1)+1) cout<<dfn[i]<<' '<<dfn[i+(n>>1)]<<endl;
	else rep(i,1,n>>1) cout<<dfn[i]<<' '<<dfn[i+(n>>1)]<<endl;
	return 0;
}
```

---

## 作者：Engulf (赞：1)

发现一个良好的性质：每条路径都至少交于一个点。

如果两条路径 $(x_1, y_1), (x_2, y_2)$ 不相交，交换一下端点变为 $(x_1, y_2), (x_2, y_1)$ 答案一定不劣。

考虑这些路径交于哪个点。就设它是 $x$，则至少得存在 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 个点对，它们不在以 $x$ 为根的情况下的同一个子树内。不难发现树的**重心**满足这个性质。以重心为根，每个子树大小都不超过 $\left\lfloor\dfrac{n}{2}\right\rfloor$。

发现以重心为根来取的话，答案是固定的，就是 $\sum\limits_{i = 1}^n \textrm{dis}_i$，即到根的距离，因为每次都选取过重心的一条路径。

既然答案固定，只需每次取出两个位于不同子树的点即可。

现在思路就明了了。
- 通过一遍 dfs 找出树的重心。
- 以重心为根来一遍 dfs 找出每个子树。
- 每次都取大小最大的两个子树中的两个点，然后删除，这个可以用 `set` 维护。
- $O(n \log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n;
vector<int> g[N];

int centroid;
int siz[N];

void getCentroid(int u, int fa) {
    siz[u] = 1;
    int mx = 0;
    for (auto v: g[u]) {
        if (v == fa) continue;
        getCentroid(v, u);
        siz[u] += siz[v];
        mx = max(mx, siz[v]);
    }
    mx = max(mx, n - siz[u]);
    if (mx <= n / 2) centroid = u;
}

vector<int> sub[N];

void dfs(int u, int fa, int rt) {
    sub[rt].emplace_back(u);
    for (auto v: g[u]) {
        if (v == fa) continue;
        dfs(v, u, rt);
    }
}

struct cmp {
    bool operator()(int a, int b) const {return sub[a].size() > sub[b].size();}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // sub[0].emplace_back(3), sub[1].emplace_back(1), sub[1].emplace_back(1);
    // set<int, cmp> t;
    // t.insert(0), t.insert(1);
    // for (auto x: t) debug("%d\n", x);
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    getCentroid(1, 0);

    multiset<int, cmp> st;
    for (auto v: g[centroid]) {
        dfs(v, centroid, v);
        st.insert(v);
    }

    for (int i = 1; i <= n / 2; i++) {
        int x = *st.begin();
        st.erase(st.begin());
        cout << sub[x].back() << " ";
        sub[x].pop_back();
        if (!st.size()) {
            cout << centroid << "\n";
            break;
        }
        int y = *st.begin();
        st.erase(st.begin());
        cout << sub[y].back() << "\n";
        sub[y].pop_back();

        if (sub[y].size()) st.insert(y);
        if (sub[x].size()) st.insert(x);
    }

    return 0;
}
```

---

## 作者：tanghg (赞：1)

## 题目大意
给出一个节点个数为 $n$ 的树，将它分成 $\lfloor\frac{n}{2}\rfloor$ 个点对，使得点对的距离之和最大，输出一组可行的方案。

$2\leq n \leq2\times10^5$
## 思路
直接这么做显然是不好的，可以考虑转成一条边的贡献。设以 $u$ 为根的字数大小 $s_u$。则对于点对和可以转化成

$$\sum_{i=1}^{n-1} \min(s_{u_i},n-s_{u_i})$$

那么为了让它最大我们希望让每一个子树大小平均，自然选择重心即可。这样的话我们输出方案就可以随便连，只要不在同一颗子树即可。那就按子树顺序放进一个序列 $a$ 里，然后根如果 $n$ 为奇就不选，否则放进最初或最后随便匹配一下即可。之后按顺序输出 $(a_i,a_{i+\lfloor\frac{n}{2}\rfloor})$。
## 代码
```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=2e5+5;
vector<ll>adj[MAXN];
ll n;
ll sz[MAXN],core,num;
void dfs(ll u,ll fa){
    sz[u]=1;
    ll val=-1e18;
    for(auto v:adj[u]){
        if(v==fa){
            continue;
        }
        dfs(v,u);
        val=max(val,sz[v]);
        sz[u]+=sz[v];
    }
    val=max(val,n-sz[u]);
    if(val<num){
        num=val;
        core=u;
    }
}
ll a[MAXN],tot;
void ga(ll u,ll fa){
    if(u!=core){
        a[++tot]=u;
    }
    for(auto v:adj[u]){
        if(v==fa){
            continue;
        }
        ga(v,u);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    num=1e18;
    for(int i=1;i<n;++i){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    if(!(n&1)){
        a[++tot]=core;
    }
    ga(core,0);
    for(int i=1;i<=n/2;++i){
        cout<<a[i]<<" "<<a[i+n/2]<<endl;
    }
    return 0;
}
```

---

## 作者：roger_yrj (赞：1)

我们希望每一对点的路径尽可能的经过根节点，我们考虑构造。

我们发现树的重心有个很好的性质：每个子树大小不会超过 $\lfloor \frac{n}{2}\rfloor$。通过这个性质，考虑以下构造：

以重心为根，求出每个点的 dfn，每次将 dfn 为 $i$ 的点与 dfn 为 $i+\lfloor \frac{n}{2}\rfloor$ 的点配对。容易证明这一对点不会在同一个子树内。

如果 $n$ 为奇数，那么就去掉根节点即可。

```cpp
void getrt(int u,int fa){
	siz[u]=1;
	for(int i=fst[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		getrt(v,u);
		siz[u]+=siz[v];
		maxx[u]=max(maxx[u],siz[v]);
	}
	maxx[u]=max(maxx[u],n-siz[u]);
	if(!rt||maxx[u]<maxx[rt])rt=u;
}
void dfs(int u,int fa){
	vis[++tcnt]=u;
	for(int i=fst[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
void solve(){
	maxx[0]=1145141919;
	cin>>n; 
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		adde(u,v);
		adde(v,u);
	}
	getrt(1,0);
	dfs(rt,0);
	if(n&1){
		for(int i=1;i<=n/2;i++){
			cout<<vis[i+1]<<" "<<vis[i+1+n/2]<<"\n";
		}
	}else{
		for(int i=1;i<=n/2;i++){
			cout<<vis[i]<<" "<<vis[i+n/2]<<"\n";
		}
	}
}
```

---

## 作者：封禁用户 (赞：1)

做法：结论。

这题需要用一个类似**邻项交换法**的思想，但是并不算是邻项。

考虑被匹配的两条路径 $(a_1,b_1),(a_2,b_2)$。如果 $(a_1,b_1)$ 与 $(a_2,b_2)$ **没有公共点**，那么我们可以得出 $(a_1,b_2)$ 与 $(a_2,b_1)$ 总长度比原两条路径总长度长并且它们之间必然有公共点。

于是可以得到所有匹配点对的路径互相相交。

而接下来我们要证明所有路径都有一个公共点。

设有三条路径没有公共点，而它们两两之间的分别有一个公共点 $S,T,U$。那么 $S,T,U$ 互相之间都存在一个不经过零一个点的简单路径，树上存在环，矛盾。命题得证。

我们只需要求出这个公共点即可。

若以公共点点为根，存在它的一个儿子使得以其为根的子树大小大于 $\frac{n}{2}$，那么这棵子树内必存在两个点互相匹配，矛盾。

于是得出结论：公共点为整棵树的**重心**。

如果 $n$ 是偶数：如果存在两个重心，那么两个重心的答案必然相同（因为割掉连接两个重心的边后剩余两个连通块大小均为 $\frac{n}{2}$），不必特判。

如果 $n$ 是奇数：不可能同时有两个重心。如果要使答案最大，唯一不参与匹配的点应该是重心。

实现：

以 $1$ 为根遍历一遍，然后筛选出一个所有儿子子树大小不超过 $\frac{n}{2}$，且自身子树大小不低于 $\frac{n}{2}$ 的点，这个点就是树的重心。

以这个重心为根，把所有根的儿子的子树遍历拍平。每次都需要从两个来自不同子树（如果 $n$ 是偶数那么其中一个点可以是根）的点配对。为了防止最后把除了一棵子树外的所有点删光，可以用优先队列维护点数（虽然有点冗余）。时间复杂度 $O(n\log n)$，但是实现难度基本为 $0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,fat[200005],amt[200005],now_rot;
vector<int>mp[200005],sons[200005];
priority_queue<pair<int,int> >q;

void dfs(int now,int fa){
	fat[now]=fa;amt[now]=1;
	for(int o=0;o<mp[now].size();o++){
		if(mp[now][o]==fa)continue;
		dfs(mp[now][o],now);amt[now]+=amt[mp[now][o]];
	}
}

void paper(int now,int fa,int rot){
	sons[rot].push_back(now);
	for(int o=0;o<mp[now].size();o++){
		if(mp[now][o]==fa)continue;
		paper(mp[now][o],now,rot);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		mp[u].push_back(v);mp[v].push_back(u);
	}
	dfs(1,1);
	for(int i=1;i<=n;i++){
		bool is_true=1;
		if(amt[i]*2<n)continue;
		for(int o=0;o<mp[i].size();o++){
			if(mp[i][o]==fat[i])continue;
			if(amt[mp[i][o]]*2>n){
				is_true=0;break;
			}
		}
		if(is_true){
			now_rot=i;break;
		}
	}
	for(int o=0;o<mp[now_rot].size();o++){
		paper(mp[now_rot][o],now_rot,mp[now_rot][o]);
		q.push(make_pair(sons[mp[now_rot][o]].size(),mp[now_rot][o]));
	}
	sons[now_rot].push_back(now_rot);
	if(n%2==0)q.push(make_pair(1,now_rot));
	for(int i=1;i<=n/2;i++){
		pair<int,int>tp1,tp2;
		tp1=q.top();q.pop();tp2=q.top();q.pop();
		cout<<sons[tp1.second][tp1.first-1]<<' '<<sons[tp2.second][tp2.first-1]<<endl;
		q.push(make_pair(tp1.first-1,tp1.second));
		q.push(make_pair(tp2.first-1,tp2.second));
	}
	return 0;
}
```

---

## 作者：xlpg0713 (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/CF1387B2)。

先随便设一个根。考虑树上一条边的贡献，即他被包含在多少个点对的匹配中。设较深的节点的子树大小为 $sz$，那么贡献即为 $\min(sz,n-sz)$。

如果可以构造使得每条边都达到这个上界，那么一定最优。

还是考虑随便钦定一个根，划分成若干颗子树，一个匹配的两个端点要么在一个子树内，要么跨越两个子树。不难发现在一个子树内不优，因为如果可以往子树外匹配可以增加 $\operatorname{lca}(x,y)$ 到根的价值。于是最优策略一定是一个点贪心的向往所在子树外面匹配。

发现如果对于一个根可以构造，那么每条边的贡献都能被卡满，即此时一定更优，考虑什么时候不能构造，即一个子树的大小大于剩下的部分。如何避免呢？找重心即可。剩下的子树之间的匹配时普及组知识。

注意 $n$ 为偶数的时候重心也要参与到匹配里。

---

## 作者：Inui_Sana (赞：1)

唯一一道有意思的，诈骗题。

结论：所有路径一定过重心。

证明：若有一对 $(u,v)$ 不过重心，则找另一对 $(x,y)$ 满足 $(x,u),(y,u)$ 都过重心。由于删掉重心后分成的连通块大小全部 $\le \left\lfloor\frac{n}{2}\right\rfloor$，所以一定能找到。然后发现这样将 $(u,v),(x,y)$ 变为 $(u,x),(v,y)$ 多出了 $\operatorname{lca(u,v)}$ 到重心的那一段，于是一定更优。

有了这个结论就可以知道 $ans=\sum dep_i$，以重心为根。可能会考虑到如果重心不止一个怎么办，但是又发现这个 $ans$ 是一样的，由于重心的基本性质。

于是找出重心，找出重心隔开的若干连通块，然后每次取出 $siz$ 最大的两个，从里面任意各选一个点配对即可。用了一个复杂度可能稍劣但是准确度高的用优先队列的写法。$O(n\log n)$。

code：

```cpp
int n,m,s,siz[N],dep[N];
vector<int> g[N];
priority_queue<pii> q;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
int rt;
void getRt(int u,int f){
	siz[u]=1;
	int mx=0;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		getRt(v,u);
		siz[u]+=siz[v];
		mx=max(mx,siz[v]);
	}
	mx=max(mx,n-siz[u]);
	if(mx<=n/2){
		rt=u;
	}
}
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs(v,u);
	}
}
void getG(int u,int f){
	g[s].eb(u);
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		getG(v,u);
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n-1){
		int u,v;read(u,v);
		add(u,v),add(v,u);
	}
	getRt(1,0);
	go(i,rt){
		int v=e[i].to;
		s++,getG(v,rt);
	}
	if((n+1)&1){
		g[0].eb(rt);
	}
	rep(i,0,s){
		q.emplace(g[i].size(),i);
	}
	while(q.size()>1){
		int x=q.top().se;q.pop();
		int y=q.top().se;q.pop();
		printf("%d %d\n",g[x].back(),g[y].back());
		g[x].pop_back(),g[y].pop_back();
		if(g[x].size()){
			q.emplace(g[x].size(),x);
		}
		if(g[y].size()){
			q.emplace(g[y].size(),y);
		}
	}
	// dfs(rt,0);
	// ll ans=0;
	// rep(i,1,n){
		// ans+=dep[i];
	// }
	// printf("%lld\n",ans-2*(n/2)-(n&1));这里是计算最大值
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

将一棵树中的点两两配对，使得一对点的距离之和最大。

### 题目分析

很明显我们不可能尝试去枚举配对方案，所以我们不妨先来考虑距离之和最大为多少。

我们考虑看每条边对答案的贡献，对于一条边分开的两棵子树 $t_u$ 和 $t_v$，我们不难发现这条边理论上能提供的贡献最多为 $t_u$ 和 $t_v$ 大小的较小值。

若要使之成立，则大小较小的子树中所有的点的“搭档”一定在另一棵子树中，但大小较大的子树中可以有些点它们“内部消化”。

所以对于每条边，我们可以给它定向，用大小较大的子树作为“父亲”，较小的子树作为儿子，最终我们会得到一棵有根树。

特别的，若一条边两边子树大小相同，我们令这两个点同为这棵树的“根”。

定完向后我们会发现这棵树的“根”就是它的重心。

因为我们定向的方法为比较两侧子树大小，所以根节点一定满足重心的定义“以树的重心为根时，所有子树的大小都不超过整棵树大小的一半”。

所以我们只需要找到重心，对于重心的多个子树中，将所有点与不在同子树的点配对即可。

对于构造，因为重心有性质：所有子树大小不大于整棵树大小的一半，所以我们不妨将所有非重心点按照 dfs 序排序，并将前一半点依次与后一半点配对，即可保证每队都不在同一棵子树中。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#define int long long

using namespace std;

const int N = 4e5 + 5;
int n, f[N], rt1, rt2;
bool tmp;
vector <int> e[N];
queue <int> q;

void dfs1(int x, int lst)
{
	bool flag = false;
	f[x] = 1;
	for(int i = 0;i < e[x].size();i++)
	{
		if(e[x][i] == lst)	continue;
		dfs1(e[x][i], x);
		f[x] += f[e[x][i]];
		if(f[e[x][i]] > n / 2)	flag = true;
	}
	if(n - f[x] > n / 2)	flag = true;
	if(!flag && rt1)
		rt2 = x;
	else if(!flag)
		rt1 = x;
}

void dfs2(int x, int lst)
{
	if(tmp)
	{
		printf("%d %d\n", q.front(), x);
		q.pop();
	}
	else
	{
		q.push(x);
	}
	if(q.size() >= n / 2)	tmp = true;
	for(int i = 0;i < e[x].size();i++)
		if(e[x][i] != lst)	dfs2(e[x][i], x);
}

signed main()
{
	scanf("%lld", &n);
	for(int i = 1, u, v;i < n;i++)
	{
		scanf("%lld %lld", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1, 0);
	//printf("%d %d\n", rt1, rt2);
	if(rt2)
	{
		dfs2(rt1, rt2);
		dfs2(rt2, rt1);
	}
	else
	{
		for(int i = 0;i < e[rt1].size();i++)
			dfs2(e[rt1][i], rt1);
		if(!q.empty())
			printf("%d %d\n", q.front(), rt1);
	}
	return 0;
}
```

---

## 作者：Hadtsti (赞：0)

### 题意简述

给出有 $n$ 个节点的树，树的边权均为 $1$。我们称节点对 $(x,y)$ 的权值为 $x$ 和 $y$ 在树上的路径长度，求在每个节点出现在节点对中至多一次的前提下，节点对权值之和的最大值。

### 题目分析

赛时这题想出来了，但没时间写完……

任意钦定一个根 $rt$，记节点 $x$ 到 $rt$ 的距离为 $d_x$，节点 $x$ 的子树大小为 $sz_x$。考虑将节点随意配对，若存在两个节点对 $(u,v)$ 和 $(x,y)$ 使得 $u,v$ 都在 $rt$ 的儿子 $a$ 的子树中，则二者的权值之和为 $d_u+d_v-2d_{LCA(u,v)}+d_x+d_y-2d_{LCA(x,y)}\le d_u+d_v-2d_a+d_x+d_y=d_u+d_v+d_x+d_y-2$。而将配对方案调整为为 $(u,x)$ 和 $(v,y)$ 则权值之和为 $d_u+d_v+d_x+d_y$，一定更优。这就告诉我们节点配对时其路径应尽量经过根。但问题在于有时不能将所有节点配对，即存在一个 $rt$ 的儿子 $c$，使得 $sz_c>n-sz_c$，这种情况中一定存在 $c$ 子树里的节点配对的情况。我们显然不想要这种情况发生，而根据树的重心的性质，将它作为根就可以避免上述情况。分析到这里，剩下的就是具体配对一下重心的各子树中节点，随便做做就好了，细节看代码。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,sz[200010],mn=INT_MAX,rt,num;
vector<int>E[200010],son[200010];
priority_queue<pair<int,int> >pq;
void dfs(int x,int fa)
{
	int mx=0;
	sz[x]=1;
	for(int y:E[x])
		if(y!=fa)
		{
			dfs(y,x);
			sz[x]+=sz[y];
			mx=max(mx,sz[y]);
		}
	mx=max(mx,n-sz[x]);
	if(mx<mn)
		mn=mx,rt=x;
}
void dfs2(int x,int fa)
{
	son[num].push_back(x);
	for(int y:E[x])
		if(y!=fa)
			dfs2(y,x);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs(1,0);
	for(int y:E[rt])
	{
		num++;
		dfs2(y,rt);
		pq.push({son[num].size(),num});
	}
	while(pq.size()>1)
	{
		int x=pq.top().second;
		pq.pop();
		int y=pq.top().second;
		pq.pop();
		for(int i=0;i<min(son[x].size(),son[y].size());i++)
		{
			printf("%d %d\n",son[x].back(),son[y].back());
			son[x].pop_back();
			son[y].pop_back();
		}
		if(!son[x].empty())
			pq.push({son[x].size(),x});
		if(!son[y].empty())
			pq.push({son[y].size(),y});
	}
	if(pq.size())
		printf("%d %d\n",rt,son[pq.top().second].back());
	return 0;
}
```

---

## 作者：N_Position (赞：0)

### AT_abc362_f
非常奇妙的一道题。
#### 分析

本题有以下几个性质：

- 对于任意的 $i,j$，有路径 $(x_i,y_i)$ 与路径 $(x_j,y_j)$ 交于树的重心。

> 证明：若路径不相交，则 $(x_i,y_j)$ 与 $(x_j,y_i)$ 两路径显然更长，所以任意两条路径相交。若任意两条路径不交与一点，则显然会存在环，与树的性质矛盾，故所有路径交于一点。若这一点不是树的重心，则以该点为根节点形成的树中，至少有一个子树的结点数大于 $\frac{N}{2}$，故不可能形成 $\lfloor\frac{N}{2}\rfloor$ 条路径。综上，该性质成立。

- 以重心为根节点的树中，每个点的 dfs 序 $dfn_i$ 已知，若 $dfn_i-dfn_j\geq\lfloor\frac{N}{2}\rfloor$，则这两个点 $i,j$ 位于不同的子树中。

>证明：由重心的性质可知。

所以本题可以在 $O(N)$ 的时间复杂度内解决。

[完整代码](https://atcoder.jp/contests/abc362/submissions/55706126)

---

## 作者：mango2011 (赞：0)

### 废话：

纪念场切题&救命题。

非常有趣的一道题，由于之前做过类似的题目，所以才能做出来。

### 题意简述：

给定一棵由 $N$ 个节点构成的树。找到一个匹配 $M=\{(u_1,v_1),(u_2,v_2),(u_3,v_3),\dots,(u_{\lfloor\frac{N}{2}\rfloor},v_{\lfloor\frac{N}{2}\rfloor})\}$，其中 $1,2,3,\dots,N$ 在 $M$ 中至多出现了一次。求使得$\displaystyle\sum_{i=1}^{\lfloor\frac{N}{2}\rfloor} \operatorname{dis}(u_i,v_i)$ 最大的方案。

其中 $\operatorname{dis}(u,v)$ 表示 $u,v$ 之间的简单路径经过的边数。

### 解题思路：

为了解题方便，我们令 $A=\displaystyle\sum_{i=1}^{\lfloor\frac{N}{2}\rfloor} \operatorname{dis}(u_i,v_i)$。由于题目中说的是边，但是我个人更习惯处理点。所以重新定义两个点的距离为点数，那么 $A=\displaystyle\sum_{i=1}^{\lfloor\frac{N}{2}\rfloor} \operatorname{dis}(u_i,v_i)-\lfloor\frac{N}{2}\rfloor$，其中后面是常数。

所以我们就考虑每一个点最多被经过了多少次。这个问题难以解决，但是我们可以直观地求出来：思路就是先找到一个点 $x$，然后尽量让其它点对的路径都经过这个点（同时也能满足其他点的需求）。

我们发现当 $x$ 不是树的重心的时候总有一块的大小很大，所以直接 $x$ 取树的重心（若有多个，任取即可）。

接下来，我们考虑贪心的构造：设去掉 $x$ 点之后原本与 $x$ 连接的点分别是 $v_1,v_2,v_3,\dots,v_k$，它们的连通块大小分别是 $sz_1,sz_2,sz_3,\dots,sz_k$。每一次我们取 $sz$ 最大的连通块 $a,b$，分别取出 $a,b$ 中当前没有被用过的点（选取深度最大的那个），将他们组成点对，再将 $sz$ 减少过的 $a,b$ 扔进队列。这一过程可以用优先队列实现。

最后还有一个坑点，就是当 $N$ 为偶数的时候，重心 $x$ 就要与唯一一个未匹配的点匹配，这样就做完了。

总的复杂度是 $O(N\log N)$。

注：可能存在复杂度更优的做法，不过个人认为这个做法想法较为简单。

---

## 作者：lfxxx (赞：0)

很好的题目，考察我们先从计算出理论答案再到构造出方案的思路。

首先对于一条边而言，假若断开它后两边的子树大小分别为 $x,y$ 那么其贡献最多为 $\min(x,y)$，考虑如何构造使得答案达到这个上限。

对于 $x$ 连向父亲的边而言，假若要使得贡献达到最大值，那么有两种情况：

1. $sz_x \geq n - sz$，此时需要保证所有 $x$ 子树外的边能连向 $x$ 子树内某个点。

2. $sz_x < n - sz_x$，此时需要保证 $x$ 子树内的点都可以连向子树外。

我们发现子树内这个限制是好处理的，但是子树外就很困难了，考虑强化上面的条件，让其全部是子树内连向另一个子树内，然后这不太可能，我们退而求其次，我们先定下来一个子树外集合，然后使得每个子树内的点都连向其他子树内或者这一个已经定好的子树外集合。

观察到将原树划分为若干个子树与一个子树的补集，这就是从一个点处断开与这个点相连的所有边。

由于需要使得每个划分出的集合（包含子树与子树补集）大小尽可能都要大，所以考虑平均的划分，也就是从重心处断开与重心相连的边。

由于重心的优秀性质，从重心断开后所得到的每个连通块大小都不超过 $n$ 的一般，这说明假若将每个点所属集合看成这个点的颜色，那么颜色集合不存在绝对众数，就必然存在一种消除方式（即每次去除两个不同颜色的点并将它们消除）可以使得消除后只剩下至多 $1$ 个点，这个结论的必要性显然，充分性可以考虑每次将最多的颜色和次多的颜色中各取一个出来消除，发现一定可以消完，而这也是我们的构造方式。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
vector<int> E[maxn];
int sz[maxn],n;
int mi = 2e5+114l;
int H;
void dfs(int u,int fa){
    sz[u]=1;
    int mx=0;
    for(int v:E[u]){
        if(v!=fa) dfs(v,u),sz[u]+=sz[v],mx=max(mx,sz[v]);
    }
    if(max(mx,n-sz[u])<mi){
        mi=max(mx,n-sz[u]);
        H=u;
    }
}
int col[maxn];
int p[maxn];
vector<int> Point[maxn];
void color(int u,int fa,int cl){
    col[u]=cl;
    Point[cl].push_back(u);
    for(int v:E[u]){
        if(v!=fa) color(v,u,cl);
    }
}
set< pair<int,int> > S;
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    for(int i=1;i<=n;i++) p[i]=i;
    dfs(1,0);
    int t=0;
    for(int v:E[H]){
        color(v,H,++t);
    }
    if(n%2==0) col[H]=++t,Point[t].push_back(H);
    for(int i=1;i<=t;i++){
        S.insert(make_pair(Point[i].size(),i));
    }
    for(int i=1;i<=(n/2);i++){
        pair<int,int> A=(*S.rbegin());
        S.erase(A);
        pair<int,int> B=(*S.rbegin());
        S.erase(B);
        cout<<Point[A.second].back()<<' '<<Point[B.second].back()<<'\n';
        Point[A.second].pop_back();
        Point[B.second].pop_back();
        A.first--;
        B.first--;
        if(A.first>0) S.insert(A);
        if(B.first>0) S.insert(B);
    }
    return 0;
}

```

---

