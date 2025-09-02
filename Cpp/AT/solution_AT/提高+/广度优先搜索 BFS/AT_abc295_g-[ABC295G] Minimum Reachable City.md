# [ABC295G] Minimum Reachable City

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc295/tasks/abc295_g

$ N $ 頂点の有向グラフ $ G_S $ があり、頂点には $ 1 $ から $ N $ までの番号が付けられています。 $ G_S $ には $ N-1 $ 本の辺があり、$ i $ 本目 $ (1\leq\ i\ \leq\ N-1) $ の辺は頂点 $ p_i\ (1\leq\ p_i\ \leq\ i) $ から頂点 $ i+1 $ に伸びています。

$ N $ 頂点の有向グラフ $ G $ があり、頂点には $ 1 $ から $ N $ までの番号が付けられています。 最初、$ G $ は $ G_S $ と一致しています。 $ G $ に関するクエリが $ Q $ 個与えられるので、与えられた順番に処理してください。クエリは次の $ 2 $ 種類のいずれかです。

- `1 u v` : $ G $ に頂点 $ u $ から頂点 $ v $ に伸びる辺を追加する。 このとき、以下の条件が満たされることが保証される。
  - $ u\ \neq\ v $
  - $ G_S $ 上で頂点 $ v $ からいくつかの辺を辿ることで頂点 $ u $ に到達可能である
- `2 x` : $ G $ 上で頂点 $ x $ からいくつかの辺を辿ることで到達可能な頂点 (頂点 $ x $ を含む) のうち、最も番号が小さい頂点の番号を出力する。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ p_i\leq\ i $
- $ 1 $ 番目の形式のクエリについて、
  - $ 1\leq\ u,v\ \leq\ N $
  - $ u\ \neq\ v $
  - $ G_S $ 上で頂点 $ v $ からいくつかの辺を辿ることで頂点 $ u $ に到達可能である
- $ 2 $ 番目の形式のクエリについて、$ 1\leq\ x\ \leq\ N $
- 入力は全て整数
 
### Sample Explanation 1

\- $ 1 $ 個目のクエリの時点で、$ G $ 上で頂点 $ 4 $ からいくつかの辺を辿ることで到達可能な頂点は $ 4 $ のみです。 - $ 3 $ 個目のクエリの時点で、$ G $ 上で頂点 $ 4 $ からいくつかの辺を辿ることで到達可能な頂点は $ 2,3,4,\ 5 $ です。 - $ 5 $ 個目のクエリの時点で、$ G $ 上で頂点 $ 4 $ からいくつかの辺を辿ることで到達可能な頂点は $ 1,2,3,4,5 $ です。

## 样例 #1

### 输入

```
5
1 2 3 3
5
2 4
1 4 2
2 4
1 5 1
2 4```

### 输出

```
4
2
1```

## 样例 #2

### 输入

```
7
1 1 2 2 3 3
10
2 5
1 5 2
2 5
1 2 1
1 7 1
1 6 3
2 5
2 6
2 1
1 7 1```

### 输出

```
5
2
1
1
1```

# 题解

## 作者：EnofTaiPeople (赞：5)

题意给定一棵外向树，每次修改为连一条有向边 $(u,v)$ 保证 $v$ 可以到达 $u$，查询某一个节点能到达的编号最小的点。

发现每次连边是缩点的过程，而且**一定**是将 $u,v$ 路径上强连通分量合并，显然可以用并查集维护。

当然，$u,v$ 路径中的点也会一同合并，具体地，用编号最小点表示一个强连通分量，每次只需要将 $v$ 往上跳并将沿途的所有强连通分量的父亲指向 $u$ 就可以了。

时间复杂度 $O(q\alpha(n)+n)$，空间 $O(n)$。

[考场上](https://atcoder.jp/contests/abc295/submissions/40040053)是暴力跳的，似乎并没有被卡？

---

## 作者：Zimo_666 (赞：3)

# [[ABC295G] Minimum Reachable City](https://www.luogu.com.cn/problem/AT_abc295_g)

### Description

给定一张点数为 $N$ 的有向图，初始 $p_i(1\leq p_i \leq i,1 \leq i < N)$ 连向 $i+1$。

$Q$ 次操作，有两种：

\- `1 u v`：$u$ 向 $v$ 连一条有向边，保证最开始时 $v$ 能到达 $u$，$u \ne v$。

\- `2 x`：询问 $x$ 能到达的点中编号最小的点。

### Solutions

- 操作一可以看作 $u \to v$ 路径上所有点向 $v$ 连边，我们可以优化为每个点向父节点连边。

- 操作二相当于从 $x$ 出发，沿我们添加的边向上走到最高点。

  我们考虑使用并查集实现，操作一暴力跳就可以。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n,q,op,u,v;
int p[N],f[N];
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x==y) return;
	f[y]=x;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i) scanf("%d",&p[i]);
	for(int i=1;i<=n;++i) f[i]=i;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&u,&v);
			u=find(u);
			while(u>v){
				merge(p[u],u);u=find(u);
			}
		}
		else scanf("%d",&u),printf("%d\n",find(u));
	}
	return 0;
}
```



---

## 作者：Alarm5854 (赞：2)

题意：给定一张有向树，边从父亲走向儿子，然后加入一些边 $(u,v)$，满足在原先的有向树中 $v$ 可达 $u$，求出一个节点 $u$ 的所有可达点中编号最小的点是什么。

这道题目的核心就是在于父亲的编号一定小于儿子的编号，以及新加入的边可以马上构成一个简单环，有了这两点，其实就可以用并查集了。

观察 $(u,v)$ 一定是返祖边，于是在 $u$ 跳到深度不大于 $v$ 之前，可以暴力合并 $u$ 和最近一个不与 $u$ 在同一个并查集里的 $w$，然后合并 $u$ 和 $w$。查询操作就是查询与 $u$ 在同一个并查集的最小节点。由于每合并一次，总有效点的数量都会减一，因此，时间复杂度为 $O(n\alpha(n))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n,q,op,u,v,p[N],f[N];
int get(int x){
	return x==f[x]?x:f[x]=get(f[x]);
}
void merge(int x,int y){//注意，这里强制 x<y
	x=get(x);
	y=get(y);
	if(x==y)
		return;
	f[y]=x;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i)
		scanf("%d",p+i);
	for(int i=1;i<=n;++i)
		f[i]=i;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&u,&v);
			u=get(u);
			while(u>v){//直接暴力合并即可
				merge(p[u],u);//一定是 p[u] 在前
				u=get(u);
			}
		}
		else{
			scanf("%d",&u);
			printf("%d\n",get(u));
		}
	}
	return 0;
}
```

---

## 作者：Register_int (赞：1)

考虑动态将树上的 SCC 缩成一点。根据题目操作的条件，容易发现每次最多将一段链缩为一点。维护一个并查集，每个并查集表示一个 SCC。修改时，我们不断从 $u$ 所在的并查集往上跳，同时合并尚未被合并的 $p_u$ 与 $u$。容易发现，任意一个节点最多只会与他的父节点合并一次，因此时间复杂度为 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, q, p[MAXN], fa[MAXN];

int find(int k) {
	return k == fa[k] ? k : fa[k] = find(fa[k]);
}

int merge(int u, int v) {
	return (u = find(u)) != (v = find(v)) ? fa[u] = v : 0;
}

int ans[MAXN];

inline 
int &get(int k) {
	return ans[find(k)];
}

int opt, u, v, k;

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= n; i++) fa[i] = i, ans[i] = i;
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &opt, &u);
		if (opt == 1) for (scanf("%d", &v); get(u) > v; k = get(u), get(merge(k, p[k])) = get(p[k]));
		else printf("%d\n", get(u));
	}
}
```

---

## 作者：六楼溜刘 (赞：0)

## 题意
- 给你一棵有 $N$ 个节点的树，每条边是指向子节点的有向边，子节点的权值严格大于父节点。
- 有两种操作共 $Q$ 个：
	- 第一个是连一条从某个节点连到自己某个祖先的有向边。
   - 第二个是查询某节点可到达的最小权值。
- $0 \le N,Q \le 2\times 10^5$，节点权值互不相等。

## 题解
我感觉这题比 EF 都简单，但是我赛时卡 E 了没做 QAQ。

首先由于子节点权值严格大于父节点，所以每次查询结果必定是可达的深度最小的节点。

容易发现，当我们把节点 $u$ 和某个祖先 $v$ 连在一起，从 $v$ 到 $u$ 的这条链均可到达 $v$ 节点。

我们考虑并查集，最初每个集合只有一个节点，当我们修改时，就把 $u$ 到 $v$ 这条链所有节点加到集合 $v$ 里，查询时直接查询所在集合最小的权值即可。

注意到每次修改时，可以跳到当前集合中深度最小的节点再执行合并操作，故除了每次修改的点本身以外每个点至多被访问一次。故复杂度为 $O((n+m)\log n)$（如果只跑路径压缩不跑按秩合并）。

```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define pbk(a) emplace_back(a)
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f;
int n,q,f[N];
int fa[N];
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
signed main(){
	n=read();
	forup(i,1,n-1){
		f[i+1]=read();
		fa[i]=i;
	}
	fa[n]=n;
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),v=read();
			int ll=getfa(u);
			while(ll>v){//只要跳到的地方比 v 小就说明已经跳出那条链了
				if(getfa(ll)!=getfa(f[ll])){
					fa[getfa(ll)]=getfa(f[ll]);
				}
				ll=getfa(ll);
			}
		}else{
			int x=read();
			printf("%d\n",getfa(x));
		}
	}
}
```


---

## 作者：DaydreamWarrior (赞：0)

[更坏的阅读体验](https://rainlycoris.github.io/#/post/20)

## 题意简述

给定一张点数为 $N$ 的有向图，初始 $p_i(1\leq p_i \leq i,1 \leq i < N)$ 连向 $i+1$。

$Q$ 次操作，有两种：
- `1 u v`：$u$ 向 $v$ 连一条有向边，保证最开始时 $v$ 能到达 $u$，$u \ne v$。
- `2 x`：询问 $x$ 能到达的点中编号最小的点。

## 分析

最开始时，$u$ 能到达的所有点都比 $u$ 大。而操作 $1$ 形成了一个强联通分量，走强联通分量内部的点才可能达到更小的点。

一个点 $x$ 能达到的最小的点在 $x$ 所在的强连通分量里，用并查集维护即可。

## 代码
```cpp
const int N = 200005;
int fa[N],p[N];
int n;

int find(int x){
    if(fa[x]==x)
        return fa[x];
    return fa[x]=find(fa[x]);
}

int main(){
    cin >> n;
    for(int k=2;k<=n;k++)
        cin >> p[k];
    for(int k=1;k<=n;k++)
        fa[k] = k;
    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int u,v;
            cin >> u >> v;
            u = find(u),v = find(v);
            while(find(u)!=v){
                fa[find(u)] = find(p[u]);
                u = p[u];
            }
            fa[find(u)] = v;
        }
        else{
            int x;
            cin >> x;
            cout << find(x) << endl;
        }
    }
    return 0;
}
```

## 闲话

警惕 abc 打普及 G 牌。

---

## 作者：bmatrix (赞：0)

[题面](https://www.luogu.com.cn/problem/AT_abc295_g)

不难发现初始图 $G_S$ 就是一棵树，边的方向由父亲到儿子。那么在进行连边操作之前，每个节点能到达的编号最小的节点就是其子树中编号最小的节点。又因为题目里的连边操作都是从小编号连到大编号的，所以每个节点子树中编号最小的节点就是它本身。

观察连边操作的限制：
1. $u\neq v$
2. 保证在连这条边之前，存在一条由 $v$ 到 $u$ 的路径。

显然由于第二条限制，每次连边必然出环，也就必然出现强连通分量。强连通分量里任意两点可以相互到达，所以询问时就找强连通分量里编号最小的点。由于连的一定是返租边，所以用并查集维护强连通，合并时暴力往上跳即可。感性理解或者势能分析一下都能发现均摊复杂度（应该）是 $O(n\alpha(n))$ 的。

代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
//#define int ll
#define gmin(x, y) ((x > y) && (x = y))
#define gmax(x, y) ((x < y) && (x = y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 2e5 + 5;
int n, q, pa[N], fa[N];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
vector<int> to[N];
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> n;
    rep(i, 1, n - 1) {
        int x; cin >> x;
        pa[i + 1] = x;
        to[x].push_back(i + 1);
    }
    iota(fa + 1, fa + n + 1, 1);
    cin >> q;
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int x, y; cin >> x >> y;
            y = find(y);
            for(int i = x; i != y; i = pa[i]) {
                i = find(i);
                if(i == y) break;
                fa[i] = y;
            }
        }
        else {
            int x; cin >> x;
            cout << find(x) << endl;
        }
    }
    return 0;
}
```

---

