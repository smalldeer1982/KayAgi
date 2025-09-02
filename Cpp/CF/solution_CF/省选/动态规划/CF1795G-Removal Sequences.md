# Removal Sequences

## 题目描述

You are given a simple undirected graph, consisting of $ n $ vertices and $ m $ edges. The vertices are numbered from $ 1 $ to $ n $ . The $ i $ -th vertex has a value $ a_i $ written on it.

You will be removing vertices from that graph. You are allowed to remove vertex $ i $ only if its degree is equal to $ a_i $ . When a vertex is removed, all edges incident to it are also removed, thus, decreasing the degree of adjacent non-removed vertices.

A valid sequence of removals is a permutation $ p_1, p_2, \dots, p_n $ $ (1 \le p_i \le n) $ such that the $ i $ -th vertex to be removed is $ p_i $ , and every removal is allowed.

A pair $ (x, y) $ of vertices is nice if there exist two valid sequences of removals such that $ x $ is removed before $ y $ in one of them and $ y $ is removed before $ x $ in the other one.

Count the number of nice pairs $ (x, y) $ such that $ x < y $ .

## 样例 #1

### 输入

```
4
3 2
1 0 1
2 3
1 2
3 3
1 2 0
1 2
2 3
1 3
5 6
3 0 2 1 0
1 2
4 1
4 2
3 4
2 3
5 1
1 0
0```

### 输出

```
1
0
4
0```

# 题解

## 作者：chroneZ (赞：5)

记 $N(u)$ 表示图上与点 $u$ 相邻的点，$p_u = deg_u - a_u$，其中 $deg_u$ 为无向图上点 $u$ 的度数。首先要删除 $p_u = 0$ 的点，同时 $\forall v \in N(u), p_v \gets p_v - 1$，归纳地考虑 $p$ 为 $0$ 的点即可。由于题目中保证至少存在一个移除序列，所以通过此方式一定可以求得一组合法解。

Additionally: 若给出序列不存在任何合法解，当且仅当在上述算法中，出现了 $p_u < 0$ 的点或算法结束后仍有未被删除的点。

构造出一组合法解后，考虑该解有何性质。

---

$\text{Lemma 1.}$ 对于节点 $u$，点集 $N(u)$ 中有且仅有 $p_u$ 个先于它被删除的节点，且对于所有的合法移除序列，这 $p_u$ 个节点是相同的（$\text{i.e.}$ 这 $p_u$ 个节点总是先于 $u$ 被移除）。

$\text{Proof.}$ 由于节点 $u$ 可被移除当且仅当 $p_u = 0$，显然我们需要 $p_u$ 个先于 $u$ 被删除的节点。假设 $N(u)$ 中存在一个不属于原先 $p_u$ 个节点中的节点 $t$，使得 $t$ 先于 $u$ 被移除，这也意味着原先的 $p_u$ 个节点中出现了一个节点 $k$ 需要后于 $u$ 被删除。这样一来，节点 $k$ 原先需要在点集 $N(k) \backslash \{ u \}$ 中选 $p_k$ 个先于 $k$ 删除的节点，现在只需选择 $p_k - 1$ 个节点，类似地，剩余那个节点也只需要选择（原先需要的点数 - 1）个节点。这个过程形成了一个**归纳**，归纳到最后，我们一定会遇到 $p$ 值为 $0$ 的节点，这个节点原先需要先于任何与之相邻的节点被删除，然而归纳过程中我们先删除了与其相邻的某个节点，这就导致不合法情况的诞生。因此假设不成立，证毕。

---

因此，由引理，只需要构造出一组合法解，便可知**点对被移除的先后顺序是否固定**。我们可以对原图中所有无向边按该解中的先后顺序定向，具体地，对于边 $(u, v)$，若 $u$ 在序列中先于 $v$ 出现，则连接一条 $u \to v$ 的有向边。这样一来，若两点在新图上连通，则其被删除的先后顺序一定是确定的。这样一来就是一个**有向图可达点对计数**问题了。记可达点对数为 $num$，则答案为 $\frac{n(n - 1)}{2} - num$。

记 $c_u$ 表示 $u$ 到 $n$ 个点是否可达的状态（使用 bitset）。容易发现最终得到的图一定是一个 DAG，建反图后进行拓扑排序，按拓扑序先后考虑，对于节点 $u$，$\forall v \in N(u), c_v \gets c_u \text{ or } c_v$ 即可。时间复杂度 $\mathcal{O} (\frac{n ^ 2}{w})$，空间复杂度 $\mathcal{O} (\frac{n ^ 2}{w})$，大约 $\text{1192 MB}$。分段考虑，每次只考虑每个点点到 $1000$ 个点是否可达的状态，这样便可以优化空间了。（官方题解还有一种更好的做法，以 64 为段长并使用 unsigned long long 代替 bitset，使用 __builtin_popcountll 函数统计，此时 $w = 64$，可以大幅降低用时，~~学到了~~）

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 1e5 + 10, B = 1000;

int deg[N], a[N], p[N], n, m;
vector<int> G[N], G2[N];
vector<int> res;
queue<int> S;
bitset<B> c[N];
void topo1(){
	res.clear();
	for(int i = 1; i <= n; i++)
		if(p[i] == 0) S.push(i);
	while(!S.empty()){
		int u = S.front(); S.pop(); res.push_back(u);
		for(auto &v : G[u])
			if(--p[v] == 0) S.push(v);
	}
}
void topo2(){
	res.clear();
	for(int i = 1; i <= n; i++)
		if(deg[i] == 0) S.push(i);
	while(!S.empty()){
		int u = S.front(); S.pop(); res.push_back(u);
		for(auto &v : G2[u])
			if(--deg[v] == 0) S.push(v);
	}
}
void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i], deg[i] = 0, G[i].clear(), G2[i].clear();
	vector<int> u(m), v(m);
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		G[u[i]].push_back(v[i]); G[v[i]].push_back(u[i]);
		deg[u[i]]++, deg[v[i]]++;
	}
	for(int i = 1; i <= n; i++)
		p[i] = deg[i] - a[i];
	topo1();
	vector<int> inv(n + 1);
	for(int i = 0; i < n; i++)
		inv[res[i]] = i;
	for(int i = 1; i <= n; i++)
		deg[i] = 0;
	for(int i = 0; i < m; i++){
		if(inv[u[i]] < inv[v[i]])
			G2[v[i]].push_back(u[i]), deg[u[i]]++;
		else G2[u[i]].push_back(v[i]), deg[v[i]]++;
		// 注意 G2 是一个反图
	}
	topo2();
	i64 ans = 1ll * n * (n - 1) / 2;
	for(int i = 1; i <= n; i += B){
		for(int j = 0; j < n; j++){
			int x = res[j];
			if(i <= x && x < i + B) c[x][x - i] = 1, ans++;
			for(auto &y : G2[x])
				c[y] |= c[x];
		}
		for(int j = 1; j <= n; j++)
			ans -= c[j].count(), c[j].reset();
	}
	cout << ans << "\n";
}
```


---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1795G)

## 思路

一道遗恨千年的 $\rm Div2\ G$，如果当时能仔细思考一会，也许就切了。

先考虑怎么找出一个合法的移除序列，设 $d_i$ 表示第 $i$ 个点初始的度数，显然的，若存在 $d_i<a_i$，则必定无解。

先令所有 $d_i$ 都减去 $a_i$，然后拓扑排序一遍即可找到合法解，并判断出是否不存在合法解。

接下来考虑找出所有美好点对 $(x,y)$。

我们可以依据拓扑序给图中的每条边定向，也十分显然的，若这张有向图中存在两个点能相互到达，那么这两个点必定不是美好点对。

接下来就是【模板】有向图可达点对计数，$\rm bitset$ 即可，为了优化空间，可以分段 $\rm bitset$。

时间复杂度 $\mathcal O(\text{可过})$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e5+10;
vector<int>b[N];bitset<1001>f[N];
inline void solve(){
    int n,m;cin>>n>>m;
    vector<int>p(n+1),s(n+1),a(n+1),d(n+1);
    for (int i=1;i<=n;++i) cin>>a[i],d[i]=0,b[i].clear();
    while (m--){
        int u,v;cin>>u>>v;
        b[u].push_back(v);
        b[v].push_back(u);
        ++d[u],++d[v];
    }
    queue<int>q;
    for (int i=1;i<=n;++i){
        d[i]-=a[i];
        if (d[i]<0) return cout<<0<<'\n',void();
        if (!d[i]) q.push(i);
    }
    int cnt=0;
    while (!q.empty()){
        int x=q.front();q.pop();p[s[x]=++cnt]=x;
        for (auto v:b[x]) if (d[v] && !--d[v]) q.push(v);
    }
    int ans=n*(n-1)/2;
    for (int i=1;i<=n;i+=1000){
        for (int j=1;j<=n;++j){
            if (j>=i && j<i+1000) f[p[j]][j-i]=1,++ans;
            for (auto v:b[p[j]])
                if (j<s[v]) f[v]|=f[p[j]];
        }
        for (int j=1;j<=n;++j) ans-=f[j].count();
        for (int j=1;j<=n;++j) f[j].reset();
    }
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--) solve();
    return 0;
}
```


---

## 作者：Graphcity (赞：1)

不妨考虑时间倒流。显然最后被删去的点一定是 $a_i=0$ 的点。那么这个点 $x$ 所连接的所有边都一定要在它前面被选。也就是说，$x$ 的所有邻居都会保留一条连向 $x$ 的边到最后。将这些邻居的 $a$ 值减去一之后，删掉 $x$，就变成了原来的一个子问题。然后用一个队列求解即可。

最后我们会连出来一个偏序的 DAG。如果两个点 $(x,y)$ 不是美好的，当且仅当 $x,y$ 之间有一条路径。问题转化为了求 DAG 上每个点能到达的点数。设 $f_i$ 为 $i$ 能到达的点集，则有 $f_i=\cup_{i\to j}f_j$。那么按照拓扑排序反着推，使用 bitset 求集合并即可。

交上去之后你会发现 MLE 了。解决办法也很粗暴，将值域分成常数个区间分开求解即可。时间复杂度 $O(\dfrac{n^2}{\omega})$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,B=1e4;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,m,a[Maxn+5],deg[Maxn+5],vis[Maxn+5]; ll ans;
vector<int> v[Maxn+5],w[Maxn+5];
bitset<B+5> f[Maxn+5];
queue<int> q;

inline void Clear()
{
    For(i,1,n) vector<int>().swap(v[i]);
    For(i,1,n) vector<int>().swap(w[i]);
    For(i,1,n) vis[i]=0;
}
inline void Solve()
{
    n=read(),m=read();
    For(i,1,n) a[i]=read(),deg[i]=0;
    For(i,1,m)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a),deg[a]++,deg[b]++;
    }
    For(i,1,n) if(a[i]==0) q.push(i);
    static int st[Maxn+5]; int top=0;
    while(!q.empty())
    {
        int x=q.front(); q.pop(),vis[x]=1,st[++top]=x;
        for(auto y:v[x]) if(!vis[y])
        {
            a[y]--,w[x].push_back(y);
            if(!a[y]) q.push(y);
        }
    }
    ans=1ll*n*(n-1)/2;
    for(int l=1,r;l<=n;l=r+1)
    {
        r=min(l+B,n);
        For(i,1,n) f[i].reset();
        For(i,l,r) f[i][i-l]=1;
        Rof(id,top,1)
        {
            int i=st[id]; for(auto j:w[i]) f[i]|=f[j];
            int k=f[i].count(); ans-=k;
        }
    }
    cout<<ans+n<<endl; Clear();
}

int main()
{
    T=read();
    while(T--) Solve();
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

好题，没想到还可以这么做，其实是我对复杂度的想法限制了思路。

首先对每个点的度数减去 $a_i$。然后从度数为 $0$ 的开始拓扑，可以把整个无向图变成一个 DAG。

考虑 $(x,y)$ 如果互相可以在对方前面，那么必定不存在 $x \rightarrow y$ 或 $y \rightarrow x$ 的边。因此我们需要知道哪些点对 $(i,j)$ 可达，用总共的 $\dfrac{n(n-1)}{2}$ 个点对减去这些即可。

我们可以对每个点开一个 bitset 表示可达的情况，那么复杂度就是 $O\left(\dfrac{n^2}{w}\right)$，空间上不能接受。因此考虑分段做，每次只考虑每个点对下标在一个区间内的点的可达情况。考虑使用一种能够存储 $K$ 位二进制数的容器，每次处理 $K$ 个，那么复杂度就是 $O\left(\dfrac{n^2}{K}\right)$，空间 $O(n)$。不难发现使用 `ull` 时 $K=64$，可以通过。

[Code & Submission](https://codeforces.com/contest/1795/submission/224309670)

---

## 作者：SkyRainWind (赞：1)

部分参考自官方题解。

删点操作有点像拓扑排序，考虑将每个点度数减去 $a_i$ 之后从新度数 $0$ 开始删点，得到一个拓扑序 $p_i$（注意题目中已经保证了有解，因此这样的拓扑序必定存在）。利用这个拓扑序可以给无向图的边定向，就得到了一个有向图。

大胆猜测一下满足要求的点对 $(x,y)$ 需要满足在新有向图中，不存在 $x\rightarrow y$ 或者 $y\rightarrow x$ 的路径。下面简要证明一下：

必要性：考虑逆否命题，即存在这样的路径，那么由拓扑排序可知无论哪种拓扑序，$(x,y)$ 必然都是某一个在前，另一个在后且顺序不会改变。

充分性：（感性理解一下）我们可以先删 $x$ 及其后继那一堆点，再删 $y$ 这样的点，也可以反过来这么做。

因此我们只需要算有向图中的点可达的点的数量，这里讲一下一种比较好写的压位做法。

每次以 $64$ 为间隔，即第一次考察所有点能到 $1..64$ 中某些点的数量，第二次为 $65..128$ .. 这样我们就可以用 `unsigned long long` 来存了，按拓扑序逆推即可。时间复杂度 $O(\frac{n^2}{64})$。

[代码](https://codeforces.com/contest/1795/submission/195267357)

---

## 作者：hgzxwzf (赞：0)

### [CF1795G](https://codeforces.com/contest/1795/problem/G)

如果将每个点 $i$ 的权值视为 $deg_i-a_i$，发现删点的过程和拓扑排序非常相似。

因为题目保证有解，所以我们可以先跑一边拓扑排序求出一种方案，并建出一张有向图，如果删除 $i$ 点时 $j$ 点还未删除并且在原图中 $i,j$ 之间有边，连一条从 $i$ 点到 $j$ 点边。

假设在有向图中 $x$ 能到达 $y$，那么就说明在所有方案中 $x$ 都在 $y$ 的前面被删掉，反之如果 $x$ 不能到达 $y$，就说明 $y$ 也可以在 $x$ 点的前面被删掉，$(x,y)$ 是好的。

所以用总对数 $\frac{n(n-1)}{2}$ 减去有向图中联通的点对数就是答案。

求有向图中一个点能被哪些点到，可以用 $\verb!std::bitset!$，时间复杂度是 $O(\frac{n^2}{64})$，时间可以接受，但是空间承受不了，可以将所有点分段处理。

[提交记录](https://codeforces.com/contest/1795/submission/194326309)。

---

