# [ABC183F] Confluence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc183/tasks/abc183_f

$ N $ 人の生徒が登校しようとしています。生徒 $ i $ はクラス $ C_i $ に属しています。

各生徒はそれぞれの家から出発したあと、他の生徒と合流を繰り返しながら学校へ向かいます。一度合流した生徒が分かれることはありません。

$ Q $ 個のクエリが与えられるので、順番に処理してください。クエリには $ 2 $ 種類あり、入力形式とクエリの内容は以下の通りです。

- `1 a b` : 生徒 $ a $ を含む集団と、生徒 $ b $ を含む集団が合流する (既に合流しているときは何も起こらない)
- `2 x y` : クエリの時点で既に生徒 $ x $ と合流している生徒(生徒 $ x $ を含む)のうち、クラス $ y $ に属している生徒の数を求める

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C_i,a,b,x,y\ \leq\ N $
- `1 a b` のクエリにおいて、$ a\ \neq\ b $
- 入力はすべて整数

### Sample Explanation 1

$ 3 $ 番目のクエリの時点で、生徒 $ 1 $ は、生徒 $ 2,5 $ と合流しています。生徒 $ 1,2,5 $ のうちクラス $ 1 $ に属する生徒は $ 2 $ 人です。 $ 5 $ 番目のクエリの時点で、生徒 $ 3 $ は、生徒 $ 4 $ と合流しています。生徒 $ 3,4 $ のうちクラス $ 4 $ に属する生徒は $ 0 $ 人です。

### Sample Explanation 2

すでに同じ集団に属している生徒に対して、`1 a b` のクエリが与えられることもあります。

## 样例 #1

### 输入

```
5 5
1 2 3 2 1
1 1 2
1 2 5
2 1 1
1 3 4
2 3 4```

### 输出

```
2
0```

## 样例 #2

### 输入

```
5 4
2 2 2 2 2
1 1 2
1 1 3
1 2 3
2 2 2```

### 输出

```
3```

## 样例 #3

### 输入

```
12 9
1 2 3 1 2 3 1 2 3 1 2 3
1 1 2
1 3 4
1 5 6
1 7 8
2 2 1
1 9 10
2 5 6
1 4 8
2 6 1```

### 输出

```
1
0
0```

# 题解

## 作者：卷王 (赞：5)

## 大致题意

你需要维护一种数据结构，满足可以进行以下操作：
* 合并两个元素所在集合
* 查询一个元素所在集合有多少个类型为指定类型的元素

## 大体思路

一道很板的题。

看到第一种操作就会想到并查集，由第二种操作想到启发式合并。

怎么合并？可以用一个 map 数组 $mp_{i,j}$ 来记录第 $i$ 个集合，类型（即题目中的 $C_i$）为 $j$ 的学生数，则合并就很简单了：

```cpp
f[x] = y;
for(auto v: mp[x]) mp[y][v.first] += v.second;
```

一个小细节，我们可以把元素少的集合合并到元素多的集合，这样 `for` 的时候就可以减少复杂度，所以只需加上这句话：

```cpp
if(mp[x].size() > mp[y].size()) swap(x, y);
```

并查集总代码：

```cpp
int f[200007];
map<int, int> mp[200007];

int find(int x) {
	if(f[x] == x) return x;
	return f[x] = find(f[x]);
}
inline void join(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return ;
	if(mp[x].size() > mp[y].size()) swap(x, y);
	f[x] = y;
	for(auto v: mp[x])
		mp[y][v.first] += v.second;
}
```

---

## 作者：Nightingale_OI (赞：5)

## AT_abc183_f

### 题面

$N$ 个学生，学生 $i$ 属于班级 $C_i$，学生们会组成一个个集合（不一定同班）。

初始每位学生所属集合只包含自己，有 $Q$ 次操作：

`1 a b` 合并 $a$ 和 $b$ 所在的集合（在同一集合里则什么也不发生）。

`2 x y` 问 $x$ 所在的集合里有多少 $y$ 班的学生。

### 思路

朴素想法是用并查集维护每位学生属于哪个集合，询问时把所有学生扫一遍。

考虑每次有效合并两个集合时新建一个点 $x$，使两个集合的代表（$u$、$v$）都指向 $x$（$fa_u=fa_v=x$）。

同时，在一张图 $G$ 里连 $x$ 到 $u$、$v$ 的各一条有向边（显然该图一定是森林）。

发现这样每个集合都在 $G$ 里形成了一棵有向树，询问时把 $x$ 所在集合的代表 $p$ 记录一下并离线，答案就是 $p$ 的子树里有多少点属于班级 $y$ （新建的点不属于任何班级）。

后续新建的节点不会影响之前的记录的答案的子树，所以答案可以之后一起求。

处理完输入以后跑出 DFS 序，根据其性质可以把子树问题转化成区间问题，即问 $[l,r]$ 内有多少学生是 $y$ 班的，直接差分就好。

时间复杂度为线性（默认并查集复杂度为常数）。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
using namespace std;
int n,m,s,l;
struct pwf{
    int p,w,f;
}ls;
int a[505050];
int b[505050];
int c[505050];
int fa[505050];
int ans[505050];
int dfn[505050][2];
int ask[505050][2];
vector<int>q[505050];
vector<pwf>r[505050];
int fifa(int x){return x==fa[x]?x:fa[x]=fifa(fa[x]);}
void dfs(int x){
    dfn[x][0]=++m;
    f(i,1,q[x].size())dfs(q[x][i-1]);
    dfn[x][1]=m;
}
signed main(){
    int x,y,z;
    cin>>n>>m;s=n;
    g(i,n*2,1)fa[i]=i;
    f(i,1,n)scanf("%lld",&a[i]);
    f(i,1,m){
        scanf("%lld %lld %lld",&z,&x,&y);
        if(z==1){
            x=fifa(x);y=fifa(y);
            if(x==y)continue;
            fa[x]=fa[y]=++s;
            q[s].push_back(x);
            q[s].push_back(y);
        }else{
            ask[++l][0]=fifa(x);ask[l][1]=y;
        }
    }
    m=0;
    f(i,1,s)if(fifa(i)==i)dfs(i);
    f(i,1,s)b[dfn[i][0]]=a[i];
    f(i,1,l){
        x=ask[i][0];y=ask[i][1];
        r[dfn[x][0]-1].push_back((pwf){-1,y,i});
        r[dfn[x][1]].push_back((pwf){1,y,i});
    }
    f(i,1,s){
        ++c[b[i]];
        f(j,1,r[i].size()){
            ls=r[i][j-1];
            ans[ls.f]+=ls.p*c[ls.w];
        }
    }
    f(i,1,l)printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：CarroT1212 (赞：2)

### 题目大意

有 $N$ 个学生，第 $i$ 位学生在第 $C_i$ 个班级。这 $N$ 位学生将会组成一些集合。初始时每位学生所在集合都互不相同。给定 $Q$ 次操作，询问格式有两种：

+ `1 a b`：将第 $a$ 位学生和第 $b$ 位学生所在的集合合并。如果已在同一集合，不会有任何变化。
+ `2 x y`：询问第 $x$ 位学生所在的集合有多少位 $y$ 班的学生。

数据范围：$1 \le N,Q \le 2\times10^5$，$1 \le C_i\le N$。

------------

### 解法分析

首先我们可以想到用并查集维护每位学生所在集合，并开一个二维数组 $mp$，$mp_{i,j}$ 表示第 $i$ 个集合中 $j$ 班学生的人数，初始化 $mp_{i,C_i}=1$，其余为 $0$。遇到 1 操作就把两学生所在集合中其中一个集合的每班人数信息加到另外一个集合去，遇到 2 操作就输出对应的值。

不作处理的话肯定是时空双爆，考虑优化一下：

+ 1 操作时，若两学生所在集合相同就跳过，否则把两个集合中人数较少的转移到另一个集合。看起来好像没什么影响，最坏情况下转移次数依然是 $N^2$ 次左右，但实际上远没有这么大。由于最开始每个集合都仅有 $1$ 人，优化之后，我们每次需要转移的人数最多也只是从 $1$ 开始逐次两倍两倍增加的。当这个数字接近 $N$ 的时候，大多数 1 操作都会因两集合相同而被跳过。由倍增的知识我们可以知道这样转移次数最大也只能到 $N\log N$ 的级别，在第二个优化的帮助下就可以成功卡进时限了。
+ 使用 `map` 存储 $mp$，即定义时写成 `map <int,int> mp[200007]`。可以发现，在上一个优化下，这样存储最坏空间复杂度也只有 $O(N \log N)$ 左右，成功卡进空限。

------------

### 代码

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N=2e5+7;
int n,q,c[N],f[N];
map <int,int> mp[N]; // 优化 2
int fnd(int x) { return f[x]==x?x:f[x]=fnd(f[x]); }
int main() {
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) f[i]=i,scanf("%d",&c[i]),mp[i][c[i]]=1;
	for (int op,x,y;q--;) {
		scanf("%d%d%d",&op,&x,&y);
		if (op==1) {
			int fx=fnd(x),fy=fnd(y);
			if (fx!=fy) {
				if (mp[fx].size()>mp[fy].size()) swap(fx,fy); // 优化 1
				for (pii i:mp[fx]) mp[fx][i.first]=0,mp[fy][i.first]+=i.second; // 转移
				f[fx]=fy;
			}
		}
		else printf("%d\n",mp[fnd(x)][y]);
	}
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：1)

喜欢我启发式合并吗？

考虑对每个 $i$ 开一个 `map`，那么和 $i$ 在一个集合的 $j$，就会被表示成 `mp[i][j]` 为真。

考虑合并 $a,b$ 所在集合的操作，这里可以运用启发式合并的思想，也就是说在 $a$ 的集合与 $b$ 的集合里选一个大小较小的合并给较大的，不妨思考一下为什么是对的。

考虑如果说有两个集合 $a,b$，如果要使层数最多（每一层大小都是 $n$），那么 $a,b$ 的大小要尽量相等，则 $size_a \gets size_a \times 2$，那么大小按照 $2$ 倍每次增加的话，一共有 $\log n$ 层，复杂度得证。

注意合并 $a,b$ 时是合并祖先，可以并查集维护。

```cpp
const int N = 2e5 + 19;
map<int, int> mp[N];
struct {
	int f[N];
	void init(int n) {
		for (int i=1;i<=n;++i) f[i]=i;
	}
	int find(int x) {
		return f[x]==x?x:f[x]=find(f[x]);
	}
} dsu;
signed main() {
	int n, q; read(n, q);
	for (int i = 1; i <= n; ++i) {
		mp[i][read()] = 1;
	} dsu.init(n);
	while (q--) {
		int op, u, v; read(op, u, v);
		if (op == 1) {
			u = dsu.find(u); v = dsu.find(v);
			if (u == v) continue;
			if (mp[u].size() < mp[v].size()) {
				swap(u, v);
			}
			for (const auto [i,j] : mp[v]) {
				mp[u][i] += j;
				// cout << "Test: " << i << ' ' << j << '\n';
			}
			dsu.f[v] = u;
		} else {
			u = dsu.find(u);
			if (mp[u].count(v)) write(mp[u][v], '\n');
			else write(0, '\n');
		}
	}
	return 0;
}
```

---

## 作者：llqqhh (赞：1)

# AT_abc183_f

## 题面

$N$ 个学生，学生 $i$ 属于班级 $C_i$，学生们会组成一个个集合。

初始每位学生所属集合只包含自己，有 $Q$ 次操作：

`1 a b` 合并 $a$ 和 $b$ 所在的集合。

`2 x y` 问 $x$ 所在的集合里有多少 $y$ 班的学生。

## 思路

合并集合通过并查集来实现。对于每一个集合维护当前集合中属于 `c` 班级的学生数。

由于对每个点维护 $\max{c_i}$ 个信息可能爆空间， 所以需要使用 `map` 存储当前集合中班级人数不为 0 的班级的人数。

合并过程需要启发式，即合并集合时将小的集合合并到大的集合中， 详细见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6+10;
map<int, int> g[N];
int n, q, fa[N];
int find(int x) {
    if(x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1, c; i <= n; i ++) {
        cin >> c;
        fa[i] = i;
        g[i].insert({c, 1});
    }
    for(int i = 1, op, x, y; i <= q; i ++) {
        cin >> op >> x >> y;
        int u = find(x), v = find(y);
        if(op == 1) {
            if(u != v) {
                if(g[u].size() > g[v].size()) swap(u, v);
                for(auto j : g[u]) g[v][j.first] += j.second;
                fa[u] = v;
            }
        } else cout << g[u][y] << '\n';
    }
    return 0;
}
```

---

## 作者：joe_zxq (赞：1)

# 思路

对于第 $1$ 种操作，使用**并查集**合并 $a$ 与 $b$ 所在的集合（记得路径压缩）。同时，记根为 $x$ 的集合中 $y$ 班的人数为 $cnt_{x,y}$。因为无法开 $(2 \times 10^5)^2$ 的数组，考虑用 map 存储。合并时将数据从 $a$ 的集合移到 $b$ 的集合时使用**启发式合并**，将小者移到大者中。

对于第 $2$ 中操作，记 $x$ 所在集合的根为 $fx$。直接输出 $cnt_{fx,y}$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, q, c[200024], fa[200024];

map<ll, ll> cnt[200024];

ll getfa(ll x) {
	if (x == fa[x]) {
		return x;
	}
	return fa[x] = getfa(fa[x]);
}

void merge(ll x, ll y) {
	x = getfa(x);
	y = getfa(y);
	if (x == y) {
		return;
	}
	if ((ll)cnt[x].size() > (ll)cnt[y].size()) {
		swap(x, y);
	}
	for (pair<ll, ll> p : cnt[x]) {
		cnt[y][p.first] += p.second;
	}
	cnt[x].clear();
	fa[x] = y;
}

ll query(ll x, ll y) {
	x = getfa(x);
	return cnt[x][y];
}

int main() {
	scanf("%lld %lld", &n, &q);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &c[i]);
		fa[i] = i;
		cnt[i][c[i]] = 1;
	}
	while (q--) {
		ll op, x, y;
		scanf("%lld %lld %lld", &op, &x, &y);
		if (op == 1) {
			merge(x, y);
		} else {
			printf("%lld\n", query(x, y));
		}
	}

	return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC183F] Confluence
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc183_f) [Atcoder 题面](https://atcoder.jp/contests/abc183/tasks/abc183_f)
### 题目大意
有 $N$ 个学生，学生 $i$ 属于班级 $C_i$，学生们会组成一个个集合（不一定同班）。  
初始每位学生所属集合只包含自己，有 $Q$ 次操作：  
`1 a b` 合并 $x$ 和 $b$ 所在的集合（在同一集合里则什么也不发生）。  
`2 x y` 问 $x$ 所在的集合里有多少 $y$ 班的学生。
### 思路
考虑建并查集维护题目中的集合，以满足合并操作。  
而在学生 $x$ 中的 $y$ 班人数可以考虑另开 `map` ，使 `mp[i][j]` 为以学生 $i$ 为祖先的并查集中，班级为 $j$ 的人数和。在每次合并时迭代 `map`，将 `mp[y][i]` 加入 `mp[x][i]`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
#define ll long long
#define pii pair<int,int>
#define endl '\n'
const int N=2e5+5;
int n,m,a[N],fa[N],opt,x,y;
map<int,int>mp[N]; 
int findf(int x);
void merge(int x,int y);
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
	f(i,1,n)cin>>a[i],fa[i]=i,mp[i][a[i]]=1;
	while(m--){
		cin>>opt>>x>>y;
		if(opt==1)
			merge(x,y);
		else
			cout<<mp[findf(x)][y]<<endl;
	} 
	return 0;
}
int findf(int x){return (fa[x]==x)?x:fa[x]=findf(fa[x]);} 
void merge(int x,int y){
	int fx=findf(x),fy=findf(y); 
	if(fx==fy)return;
	if(mp[fx].size()>mp[fy].size())swap(fx,fy);
	for(pii i:mp[fx])mp[fx][i.first]=0,mp[fy][i.first]+=i.second;
	fa[fx]=fy;
}
```
[提交记录](https://atcoder.jp/contests/abc183/submissions/45786653)

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑启发式合并。

统计 $cnt_{i,j}$ 表示在 $i$ 这个集合中，是 $j$ 班的人数。$id_{i}$ 表示 $i$ 所在集合下标。根据启发式合并模板，在保证是小集合往大集合合并的情况下，将每个小集合元素 $x$ 所在的班级都在大集合的 $cnt$ 里增加，最后清空小集合即可。对于每个询问的答案就是 $cnt_{id_{x},y}$。

$cnt$ 会爆空间，开 map 就行。复杂度 $O(n \log^2 n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e5+10;
int n,m;
struct DSU{
	vector<int> v[N];
	int id[N],c[N];
	map<int,int> cnt[N];
	il int size(int x){return v[x].size();}
	il void add(int x,int y){++cnt[x][y];}
	il void merge(int x,int y){
		if(id[x]==id[y]) return ;
		if(size(id[x])>size(id[y])) swap(x,y);
		int now=id[x];
		for(auto i:v[now]) id[i]=id[y],v[id[y]].push_back(i),add(id[y],c[i]);
		v[now].clear(),cnt[now].clear();
		return ;
	}
	il int query(int x,int y){
		return cnt[id[x]][y];
	}
}dsu;

il void solve(){
	cin>>n>>m;
	for(re int i=1;i<=n;++i)
		cin>>dsu.c[i],
		dsu.id[i]=i,dsu.v[i].push_back(i),
		dsu.add(i,dsu.c[i]);
	for(re int i=1,op,x,y;i<=m;++i){
		cin>>op>>x>>y;
		if(op==1) dsu.merge(x,y);
		else cout<<dsu.query(x,y)<<"\n";
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：Lyccrius (赞：0)



并查集套 `std::multiset` 维护集合与班级，采用启发式合并，会 TLE 两个点。

```cpp
#include <iostream>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::multiset<int> mit;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
int c[maxN + 10];
int op;
int a, b;
int x, y;

struct DisjointSetUnion {
    struct Node {
        int fa;
        mit s;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].s.size() > node[v].s.size()) std::swap(u, v);
        node[u].fa = v;
        for (auto w : node[u].s) node[v].s.insert(w);
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> q;
    DSU.Init();
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) DSU.node[i].s.insert(c[i]);
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> a >> b;
            DSU.Union(a, b);
        } else if (op == 2) {
            std::cin >> x >> y;
            std::cout << DSU.node[DSU.Find(x)].s.count(y) << '\n';
        }
    }
    return 0;
}
```

不难发现时间复杂度瓶颈在于一个班级 $C$ 在一次 `Union` 中被枚举了 $\lvert C \rvert$ 次，且单次贡献为 $1$。

使用 `std::set` 维护集合内班级类型，使用 `std::map` 维护班级内学生数量，优化为枚举 $1$ 次且单次贡献为 $\lvert C \rvert$。

```cpp
#include <iostream>
#include <map>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::map<int, int> mii;
typedef std::set<int> sit;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
int c[maxN + 10];
int op;
int a, b;
int x, y;

struct DisjointSetUnion {
    struct Node {
        int fa;
        mii m;
        sit s;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].s.size() > node[v].s.size()) std::swap(u, v);
        node[u].fa = v;
        for (auto w : node[u].s) {
            node[v].s.insert(w);
            node[v].m[w] += node[u].m[w];
        }
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> q;
    DSU.Init();
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) DSU.node[i].m[c[i]] = 1;
    for (int i = 1; i <= n; i++) DSU.node[i].s.insert(c[i]);
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> a >> b;
            DSU.Union(a, b);
        } else if (op == 2) {
            std::cin >> x >> y;
            std::cout << DSU.node[DSU.Find(x)].m[y] << '\n';
        }
    }
    return 0;
}
```

---

