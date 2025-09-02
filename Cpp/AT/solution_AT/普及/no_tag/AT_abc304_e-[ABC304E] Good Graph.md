# [ABC304E] Good Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc304/tasks/abc304_e

$ N $ 頂点 $ M $ 辺の無向グラフ $ G $ が与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺です。

$ N $ 頂点のグラフは、すべての $ i\ =\ 1,\ 2,\ \ldots,\ K $ について下記の条件が成り立つとき、**良いグラフ**と呼ばれます。

- $ G $ 上で頂点 $ x_i $ と頂点 $ y_i $ を結ぶパスが存在しない。
 
与えられるグラフ $ G $ は良いグラフです。

$ Q $ 個の独立な質問が与えられるので、それらすべてに答えてください。 $ i\ =\ 1,\ 2,\ \ldots,\ Q $ について、$ i $ 番目の質問は

- 入力で与えられたグラフ $ G $ に頂点 $ p_i $ と頂点 $ q_i $ を結ぶ無向辺を $ 1 $ 本追加して得られるグラフ $ G^{(i)} $ は良いグラフですか？
 
という質問です。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ 1\ \leq\ K\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- $ x_i\ \neq\ y_i $
- $ i\ \neq\ j\ \implies\ \lbrace\ x_i,\ y_i\ \rbrace\ \neq\ \lbrace\ x_j,\ y_j\ \rbrace $
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ K $ について次が成り立つ：頂点 $ x_i $ と頂点 $ y_i $ を結ぶパスは存在しない。
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ p_i,\ q_i\ \leq\ N $
- $ p_i\ \neq\ q_i $
- 入力はすべて整数
 
### Sample Explanation 1

\- $ 1 $ 番目の質問に関して、グラフ $ G^{(1)} $ は良いグラフではありません。なぜなら、頂点 $ x_1\ =\ 1 $ と頂点 $ y_1\ =\ 5 $ を結ぶパス $ 1\ \rightarrow\ 2\ \rightarrow\ 5 $ を持つからです。よって、`No` と出力します。 - $ 2 $ 番目の質問に関して、グラフ $ G^{(2)} $ は良いグラフではありません。なぜなら、頂点 $ x_2\ =\ 2 $ と頂点 $ y_2\ =\ 6 $ を結ぶパス $ 2\ \rightarrow\ 6 $ を持つからです。よって、`No` と出力します。 - $ 3 $ 番目の質問に関して、グラフ $ G^{(3)} $ は良いグラフです。よって、`Yes` と出力します。 - $ 4 $ 番目の質問に関して、グラフ $ G^{(4)} $ は良いグラフです。よって、`Yes` と出力します。 この入力例のように、与えられるグラフ $ G $ が自己ループや多重辺を持つ場合があることに注意してください。

## 样例 #1

### 输入

```
6 6
1 2
2 3
2 3
3 1
5 4
5 5
3
1 5
2 6
4 3
4
2 5
2 6
5 6
5 4```

### 输出

```
No
No
Yes
Yes```

# 题解

## 作者：cjh20090318 (赞：5)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给你一个有 $N$ 个点 $M$ 条边的无向图。

**注意：图中可能会有重边和自环。**

接着有 $K$ 个约束条件，约束 $x_i$ 到 $y_i$ 之间没有一条路径可以到达。

最后有 $Q$ 个询问，询问如果连接 $p_i$ 和 $q_i$，是否满足所有的约束条件。

## 分析

经过观察，不难发现这是一道维护连通性的题，于是就很容易想到了并查集。

首先建图时把每一条边上的两点在并查集中合并。

接着给出了 $K$ 个约束条件，只需要把约束的两个点所对应的连通块标记一下即可。因为连通块的值可能很大，数组存不下，这里就需要使用 `map`。

最后 $Q$ 个询问,如果两个连接的点所在的连通块被标记，那么就无法满足约束条件，否则就满足。

时间复杂度 $O(Q \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<map>
#include<utility>
#define MAXN 200002
#define mp std::make_pair
int n,m,k,q;
int fa[MAXN];
inline int find(const int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void merge(int x,int y){x=find(x),y=find(y);if(x!=y)fa[x]=y;}
std::map<std::pair<int,int>,bool> M;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=0,u,v;i<m;i++){
		scanf("%d%d",&u,&v);
		merge(u,v);//并查集将 u 和 v 进行合并。
	}
	scanf("%d",&k);
	for(int i=0,u,v;i<k;i++){
		scanf("%d%d",&u,&v);
		M[mp(find(u),find(v))]=M[mp(find(v),find(u))]=1;//标记两个点所在的连通块。
	}
	scanf("%d",&q);
	for(int i=0,u,v;i<q;i++){
		scanf("%d%d",&u,&v);
		puts(M.find(mp(find(u),find(v)))!=M.end()||M.find(mp(find(v),find(u)))!=M.end()?"No":"Yes");//如果被标记为 No，否则为 Yes。
	}
	return 0;
}
```

---

## 作者：Nemophery (赞：3)

我们用并查集来维护联通块。

首先我们要知道，连接一条边不可能让不好的图变成好的图。那么我们只要判断给出的图是不是好的，如果不是，下面全部输出 `No`。否则就判断是否有把一对 $p_i$ 和 $q_i$ 所在的联通块合并，如果有就输出 `No`，否则输出 `Yes`。

AC code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define dou double
const int inf = INT_MAX;
const int xinf = 0x3f3f3f3f;
const ll linf = LLONG_MAX;
using namespace std;
const int N = 2e5 + 1;
int n, m;
int fa[N];
map <pair <int, int>, bool> mp;
void init(int n) {
    for (int i = 1; i <= n; i++) { fa[i] = i; }
}
int find(int x) {
    if (x == fa[x]) { return x; }
    else {
        fa[x] = find(fa[x]);
        return fa[x];
    }
}
void merge(int i, int j) {
    fa[find(i)] = find(j);
}
int main() {
	scanf("%d%d", &n, &m);
	init(n);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		merge(x, y);
	}
	int k;
	scanf("%d", &k);
	bool flag = false;
	for (int i = 1; i <= k; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x = find(x), y = find(y); //为了方便
		if (x > y) { swap(x, y); }
		mp[{x, y}] = true; //记录两个 p[i] 和 q[i] 所在的联通块
		if (x == y) { flag = true; } //如果 p[i] 和 q[i] 在同一个联通块就全部输出 No
	}
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (flag) {
			printf("No\n");
			continue;
		}
		x = find(x), y = find(y);
		if (x > y) { swap(x, y); }
		printf((mp[{x, y}] ? "No\n" : "Yes\n")); //判断是否连接了两个 p[i] 和 q[i] 的所在联通块
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：3)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_abc304_e)

#### 题目大意

定义一个图是好的，需满足给出的 $K$ 对点 $x_i$ 与 $y_i$ 没有可达路径。
给出一个有 $N$ 个顶点和 $M$ 个边的无向图 $G$，给出 $Q$ 个独立的问题，判断在连接顶点 $p_i$ 和 $q_i$ 后，$G$ 是否还是一个好图。

#### 思路

由于是判断两个点是否有可达路径，不难想到用并查集优化，有一种暴力的做法，每输入一对 $p_i$ 和 $q_i$ 后，将两个连起来，然后循环一遍看 $x_i$ 与 $y_i$ 是否有可达路径，最后还原 （因为是 $Q$ 个独立的问题），但这种明显会超时，所以我们需要换一种方法。

不难发现，我们只关心给出的 $K$ 对点 $x_i$ 与 $y_i$ 有没有可达路径，而由于 $x_i,y_i \le n$，所以我们可以用 map 离散化将它两的父亲建立关系，标记为 $1$，如果输入的这对 $p_i$ 的父亲和 $q_i$ 的父亲 为 $K$ 对点中任意一对 $x_i$ 与 $y_i$ 的父亲，那么输出 No，否则输出 Yes。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,m,u,v,a[200010],b[200010],f[200010],f1[200010],q,x,y,l,lll;
map<pair<int,int>,bool>wh;
int find(int x)//并查集
{
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
int main()
{
	cin >> n >> m;
	for(int i = 1;i <= n;i++) f[i] = i;
	for(int i = 1;i <= m;i++) scanf("%d %d",&u,&v),f[find(u)] = find(v);
	cin >> k;
	for(int i = 1;i <= k;i++) 
	{
		scanf("%d %d",&a[i],&b[i]);
      wh[{find(a[i]),find(b[i])}] = wh[{find(b[i]),find(a[i])}] = 1;//建立关系
		
	}
	cin >> q;	
	while(q--)
	{
		scanf("%d %d",&x,&y);
		if(wh[{find(x),find(y)}]) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

```




---

## 作者：Imken (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc304_e)

## 题目简述

给定一张无向图和两个数列 $X, Y$。

有 $K$ 次询问，每次询问需要判断在询问的 $u, v$ 之间建边之后，判断「对于所有 $X_i$ 和 $ Y_i$ 之间都不存在路径」是否成立。

保证原图不存在 $X_i, Y_i$ 之间有路径。

## 思路分析

容易发现，在同一个连通块中的所有点都存在相互可达的路径。如果新加入的边连接了两个连通块，那么这两个连通块之间的所有点就都存在路径相互可达。

因此，对于每一对 $X_i, Y_i$，只需判断「新加入的边是否连通了这两个点所在的连通块」。可以用 map 来实现对应操作。

Code:


```
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int u, v;
int n, m, k;
int q;

vector<int> G[200005];

// ltk = 连通块id
int ltcnt = 0, ltk[200005];
int ys_x[200005], ys_y[200005];

map<pair<int, int>, int> mp;

void dfs(int x)
{
	ltk[x] = ltcnt;
	for (auto y : G[x]) {
		if (!ltk[y]) dfs(y);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!ltk[i]) ltcnt++, dfs(i);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", &u, &v);
		// 这里类似双向建边
		mp[{ltk[u], ltk[v]}] = 1;
		mp[{ltk[v], ltk[u]}] = 1;
	}
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &u, &v);
		if (mp.find({ltk[u], ltk[v]}) == mp.end()) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
	return 0;
}
```


---

## 作者：Xiphi (赞：2)

题意具有歧义，建议多读几遍在阅读此题解。

本题甚至比第 $4$  题还要好想。我们考虑直接模拟。对于判断是否存在路径，我们考虑使用并查集维护。对于查询有没有这对顶点，我们考虑用 `map` 存储，同时，你也可以用  `hash` 做到 $O(1)$ 而不是 $O(log_2 n)$ 的查询复杂度。要注意的是，在 $q$ 次询问中，我们并不用像题目描述的一样去加边并撤销这条边，只需要判断有没有一对顶点是 `find(p),find(q)` 即可。

代码实现：

```cpp
#include<iostream>
#include<map>
using namespace std;
int fa[200005];
int n,m;
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	fa[find(y)]=find(x);
}
map<pair<int,int>,int> mp;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		merge(u,v);
	}
	int k;
	cin>>k;
	for(int i=1,x,y;i<=k;++i){
		cin>>x>>y;
		mp[{find(x),find(y)}]=1;
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;++i){
		int u,v,flag=1;
		cin>>u>>v;
		if(mp[{find(u),find(v)}]==1||mp[{find(v),find(u)}]==1) puts("No");//“双向判断”，防止遗漏。
		else puts("Yes");
	}
	return 0;
}
 
```

---

## 作者：szhqwq (赞：2)

## $\tt{Solution}$

考虑并查集 + `map`。

开始将 $u_i,v_i$ 合并在一起，此题要求 $k$ 对点 $(x,y)$ 不能连通，可以使用 `map` 将 $x$ 的祖先和 $y$ 的祖先标记一下，每次询问只需要查询所询问的两个点的祖先是否被标记过即可。

**注意：标记的时候需要标记两次，正着一次，反着一次，查询时同理。**

## $\tt{AC \ Code \ of}$ [$\tt{ABC304E}$](https://www.luogu.com.cn/problem/AT_abc304_e)

```cpp
#include <bits/stdc++.h>

#define int long long
#define rep(i,l,r) for (int i = l; i <= (int)r; ++ i )
#define rep1(i,l,r) for (int i = l; i >= (int)r; -- i )
#define rep_r(i,l,r) rep(i,l,r) a[i] = read()
#define il inline
#define fst first
#define snd second
#define pb push_back
#define Yes cout << "Yes" << '\n'
#define No cout << "No" << '\n'
#define YES cout << "YES" << '\n'
#define NO cout << "NO" << '\n'
#define lcm(x,y) x * y / __gcd(x,y)

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 2e5 + 10,inf = 1e9,inff = 1e18;
//int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
int n,m,k,q;
int fa[N];
map<int,bool> st[N];

inline void read(int &x) {
	x = 0;
	short flag = true;
	char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') flag = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
	x *= flag;
}

il int find(int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}

signed main() {
	read(n); read(m);
	rep(i,0,n) fa[i] = i;
	while (m -- ) {
		int a,b;
		read(a),read(b);
		fa[find(a)] = find(b);
	}
	read(k);
	rep(i,1,k) {
		int x,y;
		read(x),read(y);
		st[find(x)][find(y)] = st[find(y)][find(x)] = 1;
	}
	read(q);
	while (q -- ) {
		int a,b;
		read(a),read(b);
		if (st[find(a)][find(b)] || st[find(b)][find(a)]) No;
		else Yes;
	}
	return 0;
}

```

---

## 作者：DengDuck (赞：1)

非常简单的并查集。

无向图的连通性可以用并查集解决。

首先维护出原图的并查集。

对于每个限制，可以认为是限制两个连通块不可以联通，我们用 `set` 保存下来，连边时查询即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=5e5+5;
LL n,m,k,q,x,y,fa[N];
set<LL>s;
LL find(LL x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		LL fx=find(x),fy=find(y);
		if(fx==fy)continue;
		fa[fx]=fy;
	}
	scanf("%lld",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%lld%lld",&x,&y);
		LL fx=find(x),fy=find(y);
		s.insert(fx*N+fy),s.insert(fy*N+fx);
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld",&x,&y);
		LL fx=find(x),fy=find(y);
		if(s.count(fx*N+fy)||s.count(fy*N+fx))
		{
			puts("No");
		}
		else
		{
			puts("Yes");
		}
	}
}
```

---

## 作者：封禁用户 (赞：1)

## 分析

不难发现，在某个图是“好图”的时候，每两个 $x_i,y_i$ 所在的集合一定是不同的，因为是无向图，一旦两点在同一集合就一定联通。我们可以用并查集算出每个点所在的集合，将组 $x_i,y_i$ 所在集合标记，表示这两个集合不能有交集。在询问的时候只需要求出来要连边的两个点所在的集合能否有交集即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int k,q;
int x,y; 
const int N=1e6+10;
int fa[N];//存每个点的集合 
map<int,map<int,int> > mp;//标记集合能否有交集，用map是为了防止爆炸
int find(int x){
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		int x=find(u),y=find(v);
		fa[x]=y;
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		int a,b;cin>>a>>b;
		x=find(a),y=find(b);
		mp[x][y]=mp[y][x]=1;//标记不能连的集合 
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int u,v;cin>>u>>v;
		x=find(u),y=find(v);
		if(mp[x][y]||mp[y][x]) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```


---

## 作者：shinzanmono (赞：1)

# [ABC304E] Good Graph

题意：定义一个图是好的，当且仅当给定的 $K$ 对点对 $(x_i,y_i)$ 之间没有路径相通，给定一个无向图 $G$，有 $Q$ 个询问，询问之间相互独立，每次询问给定点对 $(p_i,q_i)$，如果连接 $p,q$，图 $G$ 是否还是好的。

我们使用并查集维护无向图 $G$，将所有边加完后，我们会得到一些连通块，且对于 $K$ 个点对 $(x_i,y_i)$，$x,y$ 不在同一个连通块中。

我们观察并查集的合并操作是将两个连通块的根相连，所以我们把 $Q$ 次操作中连接 $p_i,q_i$ 改为链接 $fa_{p_i},fa_{q_i}$，其中 $fa_i$ 表示 $i$ 在并查集中的根。

我们使用 `std::map` 维护 $K$ 个点对 $(x_i,y_i)$ 的祖先 $(fa_{x_i},fa_{y_i})$，其中 $fa_{x_i}$ 和 $fa_{y_1}$ 不能相连。

对于查询，我们查询 $fa_{p_i}$ 和 $fa_{q_i}$ 是否可以相连即可。

给出代码：
```cpp
#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<map>
struct UFS{
    std::vector<int>fa,ssz;
    void clear(int n){
        fa.assign(n+1,0),ssz.assign(n+1,1);
        std::iota(fa.begin(),fa.end(),0);
    }
    int find(int u){
        if(u==fa[u])return u;
        return fa[u]=find(fa[u]);
    }
    void merge(int u,int v){
        int fu=find(u),fv=find(v);
        if(fu==fv)return;
        if(ssz[fu]>ssz[fv])std::swap(fu,fv);
        fa[fu]=fv,ssz[fu]+=ssz[fv];
    }
}ufs;
std::map<std::pair<int,int>,bool>allow;
int main(){
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    int n,m,k,q;
    std::cin>>n>>m;
    ufs.clear(n);
    for(int i=1,u,v;i<=m;i++)
        std::cin>>u>>v,ufs.merge(u,v);
    std::cin>>k;
    for(int i=1,u,v;i<=k;i++){
        std::cin>>u>>v;
        int fu=ufs.find(u),fv=ufs.find(v);
        if(fu>fv)std::swap(fu,fv);
        allow[std::make_pair(fu,fv)]=true;
    }
    std::cin>>q;
    for(int i=1,u,v;i<=q;i++){
        std::cin>>u>>v;
        int fu=ufs.find(u),fv=ufs.find(v);
        if(fu>fv)std::swap(fu,fv);
        if(allow[std::make_pair(fu,fv)])std::cout<<"No\n";
        else std::cout<<"Yes\n";
    }
    return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc304_e)    
这个蒟蒻赛时想到了一个奇奇怪怪的并查集做法。      
## 题意
我们称一个无向图是“好图”，需要满足以下条件：    
- 对于给定的 $k$ 对点，第 $i$ 对点为 $(x_i,y_i)$。要求在图中 $x_i$ 和 $y_i$ 不能有任何一条路径连接。     

问题来了，如果给定一个图和“好图”的判断条件，那么我们加一条边，这个图是否是“好图”呢？     
一共加 $q$ 次边，询问的加边相互独立。     
## 解法
我们可以用并查集存边，给出判断条件后先判断是否为“好图”。如果不是，那么后面的询问就都是 `No`。               
如果原图已经是“好图”，那么怎么判呢？        
设这次加了连接 $x$ 和 $y$ 的一条边，$\operatorname{f}(x)$ 为并查集 find 操作。      
那么我们很容易发现，如果这次的 $\operatorname{f}(x)$ 和 $\operatorname{f}(y)$ 在以前的判断条件里出现过，那么就不是“好图”。            
所以，我们在输入判断条件时可以用 vector 存起来，存的是并查集中的祖先。       
我们查边是否出现时，可以先排序，后使用二分法。注意要判断边界，边界有以下几个：    
- 如果比第一个点都要小，那么 `Yes`。    
- 如果比最后一个点都要大，那么 `Yes`。    
- 如果这个点里的大小为 $0$，那么 `Yes`。     

之后用 lower_bound 实现即可。         
[CODE](https://www.luogu.com.cn/paste/p5us6slw)

---

## 作者：FreedomKing (赞：1)

### 思路

一眼并查集板子题。

我们只需维护给定图的并查集，对于每对不能相同的点，标记这对点的两个不同根，判断每组询问的两个点的根是否被标记过即可。

### AC Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],x[N],y[N],f[N],sz[N],n,m,t,k;
vector<int>G[N];
void I(int n){
	for(int i=1;i<=n;i++){
		f[i]=i;
		sz[i]=1;
	}
}
int find(int x){
	return x==f[x]?x:f[x]=find(f[x]);
}
void U(int x,int y){
	x=find(x),y=find(y);
	if(x!=y){
		f[y]=x;
		sz[x]+=sz[y];
		sz[y]=0;
	}
}
map<pair<int,int>,bool>vis;
int main(){
	cin>>n>>m;
	I(n);
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		U(u,v);
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		vis[{find(x),find(y)}]=1;
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if((!vis[{find(x), find(y)}])&&(!vis[{find(y),find(x)}])){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

简单并查集。

考虑先对图进行并查集，令 $f_i$ 表示 $i$ 号节点在并查集中用 `getfa` 找到的结果。

对于添加边 $u \leftrightarrow v$，$u$ 和 $v$ 分别所在的连通块中的每一对点都会变得联通，也就是对于所有 $x,y(f_x = f_u, f_y=f_v)$，$x$ 和 $y$ 会从本身不连通变成联通，于是我们只需要处理这 $k$ 组中是否有一组满足这个条件，用 `set` 即可。

```cpp
#include <bits/stdc++.h>
//#include <bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
//using namespace __gnu_cxx;
//#define int long long

const int N = 2e5 + 5, MOD = 1e9 + 7; // Remember to change

int n, m, q, k;
int x[N], y[N];
vector<int> G[N]; 

class Dsu
{
public:
	int fa[N];
	void Init()
	{
		for (int i = 0; i < N; i++) fa[i] = i;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
}dd;

int main()
{
	scanf("%d%d", &n, &m);
	dd.Init();
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		dd.fa[dd.find(u)] = dd.find(v); 
	}
	scanf("%d", &k);
	set<pair<int, int> > st;
	for (int i = 1; i <= k; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		st.insert(make_pair(dd.find(x[i]), dd.find(y[i])));
	}
	scanf("%d", &q);
	while (q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u = dd.find(u), v = dd.find(v);
		if (st.count(make_pair(u, v)) || st.count(make_pair(v, u))) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

```


---

## 作者：Acee (赞：0)

首先这题是无向图连通性，考虑使用并查集维护。

然后 $K$ 个要求，将图分为了若干个联通块。

用 `std::bitset` 或 `std::set` 来维护那些联通块不能相通（也就是这 $K$ 要求）。

所以加入边 $(x, y)$ 时，只需要查询在 `bitset` 中 $x$ 所在联通块 与 $y$ 所在联通块是否相连即可。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include<assert.h>
#include <cstring>
#include <climits>
#include <cstdlib>
// #include <bitset>
// #include <vector>
// #include <queue>
// #include <stack>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
using ll = long long;
// #define int long long
namespace Main {
	const int N = 2e5 + 5;
	int fa[N], sz[N];
	int n, m, K, Q;
	inline int find(int x) {
		while (x!=fa[x])x=fa[x]=fa[fa[x]];
		return x;
	}
	void merge(int x, int y) {
		int xx=find(x), yy=find(y);
		if (xx==yy) return;
		if (sz[xx] > sz[yy]) swap(xx, yy);
		fa[xx] = yy;
		sz[yy] += sz[xx];
    }
	int scc[N];
	int U[N], V[N];
	unordered_map<int, int> S[N];
	int main() {
		ios::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin>>n>>m;
		for (int i=1; i<=n; ++i) fa[i]=i, sz[i]=1;
		for (int i=1, u, v; i<=m; ++i) {
			cin>>u>>v;
			merge(u, v);
		}
		for (int i=1; i<=n; ++i) scc[i]=find(i);
		cin >> K;
		bool flag=true;
		for (int i=1; i<=K; ++i) {
			cin >> U[i] >> V[i];
			S[scc[U[i]]][scc[V[i]]]=1;
			if (scc[U[i]] == scc[V[i]]) flag = false;
		}
		cin >> Q;
		for (int ti=1, x, y; ti<=Q; ++ti) {
			cin>>x>>y;
			if (!flag) {
				cout << "No\n";
				continue;
			}
			int xx=scc[x], yy = scc[y];
			if (S[xx].count(yy) || S[yy].count(xx)) {
				cout << "No\n";
			}
			else {
				cout<<"Yes\n";
			}
		}
		return 0;
	}
}
signed main() {
	Main :: main();
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 前言

简单的并查集题目，建议评黄。

## 思路

首先分析一下，当加入边 $(p_i,q_i)$ 时，如果 $p_i$ 的集合与任意一个 $x_j$ 的集合一样且 $q_i$ 的集合与对应的 $y_j$ 一样，或者是 $p_i$ 的集合与任意一个 $y_j$ 的集合一样且 $q_i$ 的集合与对应的 $x_j$ 一样，也就是说，边 $(p_i,q_i)$ 连接了 $x_i$ 和 $y_i$ 的集合，那么这个图就是坏的。

所以使用一个二维映射 $mp$，当 $mp_{i,j}=1$ 时，说明两个集合 $i,j$ 之间有关键点。设 $P_i$ 表示 $p_i$ 的集合，$Q_i$ 表示 $q_i$ 的集合，那么当 $mp_{P_i,Q_i}=1$ 或 $mp_{Q_i,P_i}=1$ 时输出 `No`，否则输出 `Yes` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,m,k,Q,x[N],y[N],f[N],p,q;
map<int,map<int,int> > mp;
int find(int x)
{
	if(f[x]==x) return x;
	return f[x] = find(f[x]);
}
signed main()
{
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		f[i] = i;
	for(int i = 1;i<=m;i++)
		cin>>x[0]>>y[0],f[find(x[0])] = find(y[0]);
	cin>>k;
	for(int i = 1;i<=k;i++)
		cin>>x[i]>>y[i],mp[find(x[i])][find(y[i])] = 1;
	cin>>Q;
	for(int i = 1;i<=Q;i++)
	{
		cin>>p>>q;
		if(mp[find(p)][find(q)]||mp[find(q)][find(p)])
			puts("No");
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：c1ampy (赞：0)

## 解法

无向图中，两个结点不能相互到达，等价于这两个结点不在同一个连通块。因此，结点 $ x_i $ 与 $ y_i $ 在添加新边后不能互相到达，等价于二者在添加新边后仍不在同一个连通块，等价于添加的新边没有将二者各自所属的连通块相连。

据以上分析，我们可以将结点 $ x_i $ 与 $ y_i $ 不能互相到达的条件，转化为二者各自所属的联通块之间不能连边的条件。

对于每个连通块，用一个 STL set 维护其不能连接的连通块，即可快速回答两个连通块之间是否可以连边的询问。

## 时间复杂度分析

连通块划分的时间复杂度为 $ \mathcal{O}(M + N) $。对于 $ K $ 个限制条件，每个限制条件均需要 $ \mathcal{O}(\log N) $ 的时间对两个连通块各自对应的 STL set 插入新元素。对于 $ Q $ 次询问，每次询问均需要 $ \mathcal{O}(\log N) $ 的时间在对应的 STL set 中检查元素是否存在。

综上，总时间复杂度为 $ \mathcal{O}(M + N + (K + Q)\log N) $，可以通过。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int max_N = 2e5 + 10;

vector <int> edge[max_N];
int colour[max_N], cur_colour = 0;
set <int> invalid_block[max_N];

void dfs(const int cur);

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	for (int i = 1; i <= M; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	
	for (int i = 1; i <= N; ++i) {
		if (colour[i]) {
			continue;
		}
		++cur_colour;
		dfs(i);
	}
	
	int K;
	scanf("%d", &K);
	for (int i = 1; i <= K; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		
		invalid_block[colour[x]].insert(colour[y]);
		invalid_block[colour[y]].insert(colour[x]);
	}
	
	int Q;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; ++i) {
		int p, q;
		scanf("%d %d", &p, &q);

		puts(invalid_block[colour[p]].find(colour[q]) == invalid_block[colour[p]].end() ? "Yes" : "No");
	}
	
	return 0;
}

void dfs(const int cur) {
	colour[cur] = cur_colour;
	for (const int & to : edge[cur]) {
		if (colour[to]) {
			continue;
		}
		dfs(to);
	}
}
```

---

