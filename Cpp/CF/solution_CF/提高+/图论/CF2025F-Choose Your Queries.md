# Choose Your Queries

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers (numbered from $ 1 $ to $ n $ ). Initially, they are all zeroes.

You have to process $ q $ queries. The $ i $ -th query consists of two different integers $ x_i $ and $ y_i $ . During the $ i $ -th query, you have to choose an integer $ p $ (which is either $ x_i $ or $ y_i $ ) and an integer $ d $ (which is either $ 1 $ or $ -1 $ ), and assign $ a_p = a_p + d $ .

After each query, every element of $ a $ should be a non-negative integer.

Process all queries in such a way that the sum of all elements of $ a $ after the last query is the minimum possible.

## 样例 #1

### 输入

```
3 4
1 2
3 2
3 1
1 2```

### 输出

```
y+
x+
x-
y-```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
3 2```

### 输出

```
y+
y+
x-
y-```

## 样例 #3

### 输入

```
4 2
2 1
4 3```

### 输出

```
y+
x+```

# 题解

## 作者：lfxxx (赞：5)

看到从 $x_i,y_i$ 中选一个操作，想到 $x_i,y_i$ 间连边建出图。

假设我们已经直到每次操作谁来承担，也就是给每条边分配了一个端点，不妨记点 $i$ 被分配了 $d_i$ 条边，通过正负交替的构造可以得知其最后的权值为 $d_i \bmod 2$，而注意到不同连通块之间不会互相影响，同一个连通块内所有点权值之和理论为 $\sum (d_i \bmod 2) \geq (\sum d_i) \bmod 2$，于是考虑构造到这个下界。

对于每个连通块建立 dfs 生成树，将所有反祖边挂在深度更浅的端点上，然后从下往上调整，具体而言设计调整函数 $solve(u)$ 表示通过调整使得点 $u$ 子树内除了点 $u$ 之外其他点都被分配了偶数条边，对 $u$ 的所有儿子 $v$ 执行了 $solve(v)$ 后，对点 $v$ 被分配边数是奇数的 $v$ 把边 $u,v$ 分配给 $v$ 使其调整为偶数，否则把边 $u,v$ 分配给点 $u$，因为反正点 $u$ 可以等到考虑 $fa_u$ 时再调整。

于是我们通过调整使得 $\sum (d_i \bmod 2) < 2$，而 $\sum (d_i \bmod 2) \bmod 2 = (\sum d_i) \bmod 2$，于是构造到了下界。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int x[maxn],y[maxn];
char ch[maxn],add[maxn];
vector< pair<int,int> > E[maxn];//(to,id)
int vis[maxn];
int val[maxn];
int dep[maxn];
vector<int> opt[maxn];
int n,m;
void dfs(int u){
    vis[u]=1;
    for(pair<int,int> nxt:E[u]){
        int to=nxt.first,id=nxt.second;
        if(vis[to]==0){
            dep[to]=dep[u]+1;
            dfs(to);
            if(val[to]==0){
                ch[id]=(u==x[id]?'x':'y');
                val[u]^=1;
                opt[u].push_back(id);  
            }
            else{
                ch[id]=(to==x[id]?'x':'y');
                val[to]^=1;
                opt[to].push_back(id);
            }
        }else if(dep[to]>dep[u]){
            ch[id]=(u==x[id]?'x':'y');
            val[u]^=1;
            opt[u].push_back(id);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x[i]>>y[i];
        E[x[i]].push_back(make_pair(y[i],i));
        E[y[i]].push_back(make_pair(x[i],i));
    }   
    for(int i=1;i<=n;i++){
        if(vis[i]==0){
            dep[i]=1;
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++){
        sort(opt[i].begin(),opt[i].end());
        for(int j=1;j<=(opt[i].size()+1)/2;j++){
            add[opt[i][j-1]]='+';
        }
        for(int j=(opt[i].size()+1)/2+1;j<=opt[i].size();j++){
            add[opt[i][j-1]]='-';
        }
    }
    for(int i=1;i<=m;i++) cout<<ch[i]<<add[i]<<'\n';
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

## Solution

可以发现如果 $i$ 操作了 $d_i$ 次，最后它会变成 $d_i\bmod 2$。

将 $x_i,y_i$ 连边，问题变成初始全是白点，每条边选一个端点翻转颜色，最小化黑点数。

这个不好做，考虑先翻转 $x_i$ 的颜色，问题就变成同时翻转两个点的颜色或不操作。这个是经典问题，对于每个连通块，只考虑 DFS 树上的边，自底向上考虑，每个点都将儿子颜色全调整为白色，容易证明这样到达下界。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, m, A[N], B[N], vs[N], c[N], t[N];
	vector<pii> G[N];
	void dfs(int x) {
		vs[x] = 1;
		for (auto [y, i] : G[x]) {
			if (vs[y]) continue;
			dfs(y);
			if (c[y]) t[i] = 1, c[y] ^= 1, c[x] ^= 1;
		}
	}
	int main() {
		cin >> n >> m;
		REP(i, 1, m) {
			cin >> A[i] >> B[i], c[A[i]] ^= 1;
			G[A[i]].pb(B[i], i), G[B[i]].pb(A[i], i);
		}
		REP(i, 1, n)
			if (!vs[i]) dfs(i), c[i] = 0;
		REP(i, 1, m) {
			cout << (t[i] ? 'y' : 'x');
			int x = (t[i] ? B[i] : A[i]);
			cout << (c[x] ? '-' : '+') << '\n';
			c[x] ^= 1;
		}
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：2)

很久没有写题解了，感觉这题比较有意思，写一篇题解。

建议更换一下翻译，这个翻译直接省去了很重要的一步。

## 思路

因为操作只与 $x$ 或 $y$ 有关，并且 $+1/-1$ 是独立的，所以考虑先把操作分配到每个点上，然后在每个点上处理这些操作。

然后考虑~~按翻译说的~~建边，我们按照操作建若干条无向边  $(u_i,v_i)$，然后考虑定向，一个点被分配到的操作编号就是指向它的边的编号。

容易发现如果一个点的入度是奇数，那么这个点最终的结果是 $1$，否则是 $0$。

我们考虑一下答案的下界是多少，对于每个连通块：如果内部边数是奇数，至少是 $1$，否则至少是 $0$。

然后考虑构造到下界，同样对每个连通块分别考虑，建出 DFS 生成树，从下往上遍历，把返祖边挂到深度大的点上。

那么当我们处理到了 $u$ 时已经处理完了 $u$ 的所有儿子，我们考虑 $u$ 的所有儿子的入度，假设某个儿子是 $v$，如果入度是偶数，那么这条边连成 $v \rightarrow u$，否则连成 $u \rightarrow v$，对于挂在 $u$ 上的返祖边都连向 $u$ 即可，此时我们可以算出 $u$ 的入度奇偶性，递归处理即可。

容易发现只可能根不满足条件，并且不满足条件仅当边数是奇数，于是构造完了。

注意最终答案的构造需要满足任意时刻序列中的数不为负，同时要注意重边的处理。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=3e5+10;
int n,m,u[N],v[N],dep[N];bool vis[N];string ans[N];
vector< pair<int,int> >a[N];vector<int>vc[N];
inline bool dfs(int x,int fa){
	dep[x]=dep[fa]+1,vis[x]=1;
	bool rd=0,Tg=0;
	for (auto it:a[x]){
		int v=it.first,id=it.second;
		if (v==fa && !Tg){Tg=1;continue;}
        //处理重边，如果有多条连向父亲的边，把另外的边视为返祖边
		if (!vis[v]){
			bool t=dfs(v,x);
			if (t) vc[v].push_back(id);
			else rd^=1,vc[x].push_back(id);
		}else if (dep[v]<dep[x])
			rd^=1,vc[x].push_back(id);
	}
	return rd;
}
inline void solve(){
	cin>>n>>m;
	rep(i,1,m){
		cin>>u[i]>>v[i];
		a[u[i]].emplace_back(v[i],i);
		a[v[i]].emplace_back(u[i],i);
	}
	rep(i,1,n) if (!vis[i]) dfs(i,0);
	rep(i,1,n){
		int sz=vc[i].size();
		sort(all(vc[i]));
		rep(j,0,sz-1){
			int id=vc[i][j];
			if (j&1){
				if (i==u[id]) ans[id]="x-";
				else ans[id]="y-";
			}else{
				if (i==u[id]) ans[id]="x+";
				else ans[id]="y+";
			}
		}
	}
	rep(i,1,m) cout<<ans[i]<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：acb437 (赞：1)

# 题解：[CF2025F Choose Your Queries](https://www.luogu.com.cn/problem/CF2025F)
## 思路简述
**套路：**
  1. **序列上与两个位置相关的操作转为建边，位置转为点。**
  2. **没有明显性质的无向图考虑通过 DFS 生成树解决问题。**
  3. **对于这种无论怎么分配最多只有 $1$ 的贡献的题目，可以考虑证明其满足最优子结构，贪心分配。**

把操作建边，形成一张无向图，图上连接了偶数条边的点可以通过一正一负最终变回 $0$，直接做没有头绪，考虑 DFS 生成树。

DFS 生成树上，先不考虑返祖边，子树 $v$ 内的边数如果为偶数，肯定可以两两匹配消掉，否则可以剩下一条连接 $v$ 的边未被抵消。归纳证明显然。假设 $u$ 中有 $x$ 个子树内有奇数条边，子节点在集合 $v_x$ 中，$y$ 个子树有偶数条边，子节点在集合 $v_y$ 中，则：
  1. $u\rightarrow v(v\in v_x)$ 的边优先和 $v$ 匹配，因为：如果有偶数条这样的边，它们和 $u$ 匹配也只是互相抵消。如果有奇数条这样的边，和 $u$ 匹配，互相抵消完后最多减少 1，但和 $v$ 匹配一定能减少 1（$v$ 子树内有一条与 $v$ 连接的边未被抵消）。
  2. $u\rightarrow v(v\in v_y)$ 的边和 $u$ 匹配，因为 $v$ 子树内已经完全抵消，与 $v$ 匹配肯定不优。

这样，$v_x$ 在匹配与 $u$ 连接的边后完全抵消，$v_y$ 本来就完全抵消，$u$ 子树内只有 $u$ 没有完全抵消了。如果 $2|y$，那么它们可以正负交替地匹配 $u$，$u$ 的子树内有偶数条边，被完全抵消。否则，$u$ 就只能留下一条未被匹配的边，等待父节点的分配。

这样，我们就分析完了建成一颗树（森林）的最小值的构造方法。然后考虑返祖边。作为同样不属于 $v$ 子树内的边，它应该在 $v$ 的祖先 $a$ 处考虑。通过上面的分析，我们可以知道，$a$ 的子树内除 $a$ 以外的所有点都应该被完全抵消了，所以这条边等价于 $u\rightarrow v_y$，直接加入和 $a$ 匹配的边中考虑即可。

具体实现上，因为要求数列中的数必须时刻非负，所以最后还需要进行微调，对于贡献到同一个位置的操作，将编号靠前的调为正，编号靠后的调为负，正负的个数分别不变就可以了。
## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 3e5 + 5;
int n, q, x[N], y[N], cnta[N], cntd[N];string ans[N];

int idx, h[N];
struct edge{int to, nxt, i;}e[N << 1];
void addEdge(int u, int v, int i)
{
	e[++idx] = (edge){v, h[u], i};
	h[u] = idx;
}

int f[N];
bool vis[N], inStk[N];
void DFS(int u)
{
	vector <edge> vec;
	vis[u] = inStk[u] = true;
	for(int i = h[u];i;i = e[i].nxt)
	{
		int v = e[i].to;
		if(!vis[v])
		{
			DFS(v);
			if(f[v])ans[e[i].i] = (v == x[e[i].i]) ? "x-" : "y-";
			else vec.push_back(e[i]);
		}
		else if(!inStk[v])vec.push_back(e[i]);
	}
	for(int i = 0;i < vec.size();i += 2)ans[vec[i].i] = (u == x[vec[i].i]) ? "x+" : "y+";
	for(int i = 1;i < vec.size();i += 2)ans[vec[i].i] = (u == x[vec[i].i]) ? "x-" : "y-";
	inStk[u] = false, f[u] = vec.size() & 1;
}

int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1;i <= q;i++)scanf("%d%d", &x[i], &y[i]), addEdge(x[i], y[i], i), addEdge(y[i], x[i], i);
	for(int i = 1;i <= n;i++)
		if(!vis[i])
			DFS(i);
	for(int u = 1;u <= n;u++)
	{
		for(int i = h[u];i;i = e[i].nxt)
		{
			if((ans[e[i].i] == "x+" || ans[e[i].i] == "x-") && x[e[i].i] == u)cnta[u] += ans[e[i].i] == "x+", cntd[u] += ans[e[i].i] == "x-";
			if((ans[e[i].i] == "y+" || ans[e[i].i] == "y-") && y[e[i].i] == u)cnta[u] += ans[e[i].i] == "y+", cntd[u] += ans[e[i].i] == "y-";
		}
	}
	for(int i = 1;i <= q;i++)
	{
		if(ans[i] == "x+" || ans[i] == "x-")
		{
			if(cnta[x[i]])
				ans[i] = "x+", cnta[x[i]]--;
			else ans[i] = "x-", cntd[x[i]]--;
		}
		else if(ans[i] == "y+" || ans[i] == "y-")
		{
			if(cnta[y[i]])
				ans[i] = "y+", cnta[y[i]]--;
			else ans[i] = "y-", cntd[y[i]]--;
		}
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

有 $n$ 个数 $a_1,\cdots,a_n$，初始时全为 $0$。

有 $m$ 次操作，每次操作给出 $x,y$，你需要选择 $a_x,a_y$ 中的任意一个，令其加上或减去 $1$，**你需要保证任何一个数在任意时刻都是非负整数**。

你需要使得最后得到的 $n$ 个数的总和最小，输出任意一组合法的方案。

$1\leq n,m\leq 3\times 10^5$。

## 思路

感觉可能比较平凡？连我这样的构造菜鸡都可以做出来。

首先二元关系直接建图，并且将偏向关系（在本题中，就是对哪一个端点进行操作）体现为边的方向。具体地，我们可以建出一张图，边 $(x,y)$ 表示有操作 $(x,y)$。我们需要对其定向，假如存在边 $x\to y$ 表示对 $x$ 进行操作。

但是这样我们忽略了加上还是减去 $1$ 这个限制，不过稍作分析发现我们其实不需要。假如已经定向了，那么一个显然且正确的分配 $\pm 1$ 的方法是：遍历每个点的出边（按照操作时间排序），奇数次遇到的分配 $+1$，偶数次遇到的分配 $-1$，这样对于出度为奇数的点，答案的贡献是 $1$，否则是 $0$。

现在的问题是如何为我们建出的无向图每条边定向，使得奇数点最少，由于每一个连通块问题是独立的，不妨对于每一个连通块分别考虑。

不妨贪心，尽可能让每个点度数为偶数，然后你发现不会做，开始枚举可能的做法，然后你枚举到了 dfs 树。

对图跑出 dfs 树，然后递归，对于点 $u$，假设儿子节点全部调整为出度为偶数了，那么只需要考虑 $u$ 的返祖边以及与父亲直接相连的**一条边**，由于只需要保证奇偶性，因此只需要留住一条边，其他边随意定向，用留下的边就可以实现这个点出度为偶数，为了方便，将这条留下的边设定为与父亲直接相连的**一条边**即可。

这样，只要存在与父亲直接相连的边，一定可以调整到度数为偶数，故只有根节点可能无法调整，一个连通块最多贡献 $1$ 的答案。

现在我们需要证明这个做法是正确的，由于可行性显然成立，故只需要证明用我们的做法，根节点调整后为奇数时，答案同样也为 $1$。考虑反证法，若答案为 $0$，则我们需要在原本方案下，反转奇数条边，那么这同样会改变其子节点的出度，我们接下来有两种决策：

- 结束决策，反转奇数条边，一定会影响除去根节点外，一个点的入度奇偶性，答案至少为 $1$。
- 向下继续调整，由于那么在子树上回到了我们最初的问题，不能结束决策，只能继续调整，调整到叶子节点后，由于缺乏子树，无法调整，至少会产生 $1$ 的贡献。

于是证明了我们的结论，如此调整，时间复杂度 $O(n+m)$，按照实现不同，可能会带 $\log$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, m, deg[N], dep[N];
vector<pair<int,int>> g[N], g2[N];
pair<int,int> a[N];

void dfs(int u, int fa){
    dep[u] = dep[fa] + 1;
    for(auto [v, id] : g[u]){
        if(dep[v]) continue;
        dfs(v, u);
    }
    int par = 0;
    for(auto [v, id] : g[u]){
        if(dep[v] > dep[u]) continue;
        if(v == fa && !par){ par = id; continue; }
        g2[u].emplace_back(v, id);
        deg[u]++;
    }
    if(!par) return;
    if(deg[u] & 1) g2[u].emplace_back(fa, par), deg[u]++;
    else g2[fa].emplace_back(u, par), deg[fa]++;
}

string ans[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int& u = a[i].first, &v = a[i].second;
        cin >> u >> v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    for(int i=1;i<=n;i++){
        if(!dep[i]) dfs(i, 0);
    }
    for(int i=1;i<=n;i++){
        int cnt = 0;
        sort(g2[i].begin(), g2[i].end(), [](auto x, auto y){
            return x.second < y.second;
        });
        for(auto [j, id] : g2[i]){
            cnt++;
            ans[id] = a[id].first == i ? "x" : "y";
            ans[id] += cnt & 1 ? "+" : "-";
        }
    }
    for(int i=1;i<=m;i++) cout << ans[i] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：wangyibo201026 (赞：1)

## solution

ChiFAN 讲的非常好的构造题，感觉属于构造中的一个类型。

首先看似是有四种操作，但是对象只有 $x, y$ 两个，也就是说，我们需要分配 $x, y$，剩下的事情都是可以算出来的。

具体来说，假设 $x$ 被选了 $d_x$ 次，那么 $x$ 对总和造成的贡献可以正负构造到 $d_x \bmod 2$，现在我们只需要解决的问题就是如何分配 $x, y$。

按照常规思路，$x, y$ 连边，那么我们需要解决的就是一条边的代价分配到哪个端点。不难发现对于每个极大连通块 $p$，假设其边数为 $d_p$，那么这个极大连通块答案的下界是 $d_p \bmod 2$，我们尝试构造到这个下界。

将问题搬到 DFS 树上，首先考虑没有返祖边的情况，对于一个结点 $u$，我们尝试只让 $u$ 本身分配的边数为奇数个（当然也可以是偶数个），子树内部的结点分配的边数都是偶数个。当解决完一个儿子 $v$ 的问题时，如果 $v$ 分配的边数为偶数，我们就将 $v \to u$ 分配给 $u$，否则就将其分配给 $v$。不难发现如此递归构造，最后最多只会有根节点产生 $1$ 的贡献，此时当且仅当 $d_p \bmod 2 = 1$。

接下来我们将试图说明返祖边其实是没有影响的，我们将返祖边的贡献计入深度浅的结点 $x$ 处，发现当处理 $x$ 时，这些返祖边对我的答案变化量是 $1$ 的，又由于最终只有根节点可能是奇数条边，且此时当且仅当 $d_p \bmod 2 = 1$，发现搞到最后其实是没有影响的，于是我们直接将返祖边的贡献计入深度浅的结点即可。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int n, m;
int val[N], ans[N], cnt[N], u[N], v[N], dep[N];
bool vis[N];

int head[N], tot = 1;

struct Node {
  int to, id, p, next;
} edges[N << 1];

void add ( int u, int v, int id, int p ) {
  tot ++;
  edges[tot].to = v;
  edges[tot].id = id;
  edges[tot].p = p;
  edges[tot].next = head[u];
  head[u] = tot;
}

void dfs ( int x, int lst ) {
  vis[x] = true;
  for ( int i = head[x]; i; i = edges[i].next ) {
    if ( i != ( lst ^ 1 ) ) {
      if ( !vis[edges[i].to] ) {
        dfs ( edges[i].to, i );
        dep[edges[i].to] = dep[x] + 1;
        if ( val[edges[i].to] & 1 ) {
          // cout << ( edges[i].p ^ 1 ) << " " << edges[i].id << '\n';
          ans[edges[i].id] = edges[i].p ^ 1;
          val[edges[i].to] ^= 1;
        }
        else {
          // cout << edges[i].p << " " << edges[i].id << '\n';
          ans[edges[i].id] = edges[i].p;
          val[x] ^= 1;
        }
      }
      else if ( dep[edges[i].to] > dep[x] ) {
        // cout << edges[i].p << " " << edges[i].id << '\n';
        val[x] ++;
        ans[edges[i].id] = edges[i].p;
      }
    }
  }
}

void Solve () {
  cin >> n >> m;
  for ( int i = 1; i <= m; i ++ ) {
    cin >> u[i] >> v[i];
    add ( u[i], v[i], i, 0 ), add ( v[i], u[i], i, 1 );
  }
  for ( int i = 1; i <= n; i ++ ) {
    if ( !vis[i] ) {
      dfs ( i, 0 );
    }
  }
  for ( int i = 1; i <= m; i ++ ) {
    if ( !ans[i] ) {
      if ( cnt[u[i]] & 1 ) {
        cout << "x-\n";
      }
      else {
        cout << "x+\n";
      }
      cnt[u[i]] ++;
    }
    else {
      if ( cnt[v[i]] & 1 ) {
        cout << "y-\n";
      }
      else {
        cout << "y+\n";
      }
      cnt[v[i]] ++;
    }
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

## 作者：Filberte (赞：1)

听说是很经典的一个构造题。

考虑构造一个 $n$ 个点 $m$ 条边的图。对于条件 “$x_i$ 和 $y_i$ 必须选一个加一或减一”，考虑在 $x_i$ 和 $y_i$ 之间建一条无向边，二选一的过程就是给无向边定向。观察所有选择某个点 $u$ 的操作，肯定是轮流对 $u$ 加一减一，最终 $u$ 的权值只可能是 $0$ 或 $1$，只与选择 $u$ 的次数的奇偶性有关。所以原问题转化为：给定一个有向图，给每条边定向，使得入度为奇数的点的数量最少。

对于原图的每个连通块分开考虑。假如这个连通块有 $k$ 条边，那么这个连通块所有点权值之和不小于 $k$ 模 $2$ 的余数。可以证明无论连通块形态如何都可以达到这个下界，给出一种构造性证明（这题确实也要输出方案）：先构造这个图上的一个搜索树，对于每条边，在遍历到深度较浅的节点时考虑。自底向上考虑到某个点 $u$ 时，会有两种边：一是连接它的直接儿子 $v$ 的边，二是连接子树内距离为 $2$ 及以上节点 $x$ 的边。对于第一种边，如果它的儿子 $v$ 目前入度是奇数，那么定向 $u \rightarrow v$，否则定向 $u\leftarrow v$。而第二种边我们都定向 $u\leftarrow x$。此时，对于除了根节点以外任意一个点，它的父亲节点会保证它的入度是偶数，而它的其他祖先节点不会影响它的入度。因此除了根节点外所有点权均为偶数，而根节点权值的奇偶性与 $k$ 的奇偶性一样。

还有一个小细节：这题需要保证任意时刻序列中所有数的值非负。所以应该把所有定向到 $u$ 的边排序后，按照题目给定的顺序轮流加一减一，才能符合题意。

代码：

```c++
#include <bits/stdc++.h>
using namespace std;
struct Edge{
    int v, id;
};
const int N = 3e5 + 100;
vector<Edge> dw[N];
vector<int> e[N];
int n, m;
int X[N], Y[N], dep[N];
bool in_tree[N], deg[N];
void dfs(int u, int fa){
    dep[u] = dep[fa] + 1;
    for(int v : e[u]){
        if(v == fa) continue;
        dfs(v, u);
    }
}
struct dsu{
    int f[N];
    void init(){for(int i = 1;i <= n;i++) f[i] = i;}
    int find(int x){return x == f[x] ? x : (f[x] = find(f[x]));}
    bool uc(int x, int y){return find(x) != find(y);}
    void merge(int x, int y){f[find(x)] = find(y);} 
}T;
char ans[N][2];
struct Opt{
    char pc;int id;
    bool operator < (Opt &ot) const{
        return id < ot.id;
    }
};
vector<Opt> nods[N];
void dfs2(int u, int fa){
    for(int v : e[u])
        if(dep[v] == dep[u] + 1) dfs2(v, u);
    for(auto [v, id] : dw[u]){
        if(deg[v]){
            deg[v] = 0;
            nods[v].push_back({(v == X[id]) ? 'x' : 'y', id});
        }
        else{   
            deg[u] = !deg[u];
            nods[u].push_back({(u == X[id]) ? 'x' : 'y', id});
        }
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for(int i = 1, u, v;i <= m;i++){
        cin >> u >> v;
        X[i] = u, Y[i] = v;
    }  
    T.init();
    for(int i = 1;i <= m;i++){
        int u = X[i], v = Y[i];
        if(T.uc(u, v)){
            in_tree[i] = 1;
            T.merge(u, v);
            e[u].push_back(v); 
            e[v].push_back(u);
        }
    }
    for(int i = 1;i <= n;i++) if(!dep[i]) dfs(i, 0);
    for(int i = 1;i <= m;i++){
        int u = X[i], v = Y[i];
        if(dep[u] < dep[v]) dw[u].push_back({v, i});
        else dw[v].push_back({u, i});
    }
    for(int i = 1;i <= n;i++) if(dep[i] == 1) dfs2(i, 0);
    for(int i = 1;i <= n;i++){
        if(nods[i].empty()) continue;
        sort(nods[i].begin(), nods[i].end());
        bool op = 1;
        for(auto [ch, id] : nods[i]){
            ans[id][0] = ch;
            ans[id][1] = op ? '+' : '-';
            op = !op;
        }
    }
    for(int i = 1;i <= m;i++) cout << ans[i][0] << ans[i][1] << endl;
    return 0;
}
```

---

