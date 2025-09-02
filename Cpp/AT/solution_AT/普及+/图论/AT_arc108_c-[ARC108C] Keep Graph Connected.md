# [ARC108C] Keep Graph Connected

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_c

$ 1 $ から $ N $ の番号がついた $ N $ 個の頂点と $ 1 $ から $ M $ の番号がついた $ M $ 本の辺からなる連結な無向グラフが与えられます。 このグラフに多重辺は存在するかもしれませんが、自己ループはありません。

このグラフのそれぞれの辺には $ 1 $ 以上 $ N $ 以下の整数で表されるラベルがついています。 辺 $ i $ はラベル $ c_i $ がついており、頂点 $ u_i,v_i $ を双方向につなぐ辺です。

すぬけ君はそれぞれの頂点に $ 1 $ 以上 $ N $ 以下の整数を書き込んだのち(頂点に書き込まれた整数に重複があっても構いません)、以下の条件を満たす辺のみを残してそれ以外の辺を取り除くことにしました。

**条件**：辺の両端の頂点に書き込まれた整数を $ x,y $ として、$ x,y $ のいずれか一方**のみ**が辺についたラベルと等しい

上記の条件を満たさない辺を取り除いたあとのグラフも連結のままであるような頂点への整数の書き込み方を *よい書き込み方* と呼びます。よい書き込み方が存在するかどうかを判定し、存在するならばその一例を示してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i,v_i,c_i\ \leq\ N $
- 与えられるグラフは連結
- 与えられるグラフに自己ループはない

### Sample Explanation 1

\- 頂点 $ 1,2,3 $ にそれぞれ $ 1,2,1 $ を書き込みます。 - 辺 $ 1 $ は頂点 $ 1,2 $ をつないでおり、ラベルが $ 1 $ です。 - 頂点 $ 1 $ に書き込まれた整数のみが辺についたラベルと等しいため辺 $ 1 $ は取り除かれません。 - 辺 $ 2 $ は頂点 $ 2,3 $ をつないでおり、ラベルが $ 2 $ です。 - 頂点 $ 2 $ に書き込まれた整数のみが辺についたラベルと等しいため辺 $ 2 $ は取り除かれません。 - 辺 $ 3 $ は頂点 $ 1,3 $ をつないでおり、ラベルが $ 3 $ です。 - どちらの頂点に書き込まれた整数も辺についたラベルと異なるため辺 $ 3 $ は取り除かれます。 - 辺 $ 4 $ は頂点 $ 1,3 $ をつないでおり、ラベルが $ 1 $ です。 - どちらの頂点に書き込まれた整数も辺についたラベルと等しいため辺 $ 4 $ は取り除かれます。 - 辺 $ 3,4 $ が取り除かれたあともグラフは連結なので、この書き込み方はよい書き込み方です。

## 样例 #1

### 输入

```
3 4
1 2 1
2 3 2
3 1 3
1 3 1```

### 输出

```
1
2
1```

# 题解

## 作者：bobo2007 (赞：1)

### 题意

给定一个图，边有边权，值在 $ 1 \sim n$ 之间 ，要为每个点赋点权（也是 $ 1 \sim n$ 之间），然后删除图中的边，满足对于所有剩下的边，边的两个端点权值**恰好**有一个和边权相等，**构造**一种方案使得新图连通。
若无解输出 “NO” ，保证原图连通。

### 题解

根据以下构造方法，可以证明只要原图连通，则能保证有**一定**有合法解。

首先我们对原图求任意的生成树，`dfs` 树或用并查集都可以，然后将 `1` 号点赋权为任意，接着开始  `dfs`。

遍历到一个点时，若它的父亲的点权与它连接父亲的那条边权**相同**，这也就意味着这个点不能再染成连父亲的边权了，否则这条边会出现两个端点点权都为边权的情况，边断开，图不连通，此时我们将这个点赋值为除了父亲点权的任意值。

若**不同**，则将这个点点权赋值为那条边的边权，保证这条边有且仅有一个端点权值与边权相同，可以保证连通。

这样构造无论哪个点都会在其中一种情况中被讨论，于是保证有解。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct NODE
{
	int next,to,s;
}b[200010];
int n,m,fa[100010],a[100010],ans[100010],tot=0;
int getfa(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
void add(int x,int y,int z){b[++tot].next=a[x];a[x]=tot;b[tot].to=y;b[tot].s=z;}
void dfs(int x,int fa)
{
	int i;
	for(i=a[x];i;i=b[i].next)
	{
		int y=b[i].to;
		if(y==fa) continue;
		if(ans[x]==b[i].s) ans[y]=ans[x]==1?2:1;
		else ans[y]=b[i].s;
		dfs(y,x);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	int i;
	for(i=1;i<=n;i++) fa[i]=i;
	for(i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		int u=getfa(x),v=getfa(y);
		if(u!=v) fa[u]=v,add(x,y,z),add(y,x,z);
	}
	ans[1]=1;dfs(1,0);
	for(i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}

```



---

## 作者：StarRoam (赞：0)

第一样看到题目，以为会是一道非常难的构造题，后面发现是一道小唐题，就来水一篇题解。

容易知道，对于一个 $n$ 个点的连通图，最少需要 $n-1$ 条边，容易想到树，于是题目就变简单了。

有构造方法：

- 如果父节点的权值不为边权值，我们只要将儿子节点的权值变为边权值。

- 否则，我们只要随机给儿子节点一个不等于父节点的值就行了。

于是我们发现，对于这样的构造方法在原图联通时一定存在，但如果图不联通，怎么构造都是不合法的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int n,m,ans[N],tot;
struct EDGE{int to,c;};
vector<EDGE> e[N];
void dfs(int pos)
{
	tot++;
	for(int i=0;i<e[pos].size();i++)
	{
		int v=e[pos][i].to,c=e[pos][i].c;
		if(ans[v]) continue;
		if(ans[pos]==c)ans[v]=(c!=1?1:2);
		else ans[v]=c;
		dfs(v);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		e[u].push_back(EDGE{v,c});
		e[v].push_back(EDGE{u,c});
	}
	ans[1]=1;
	dfs(1);
	if(tot!=n) cout<<"No";
	else{
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc108_c)

大水绿，建议降黄。

由于保证图连通，所以先构造图的任意一棵生成树。

然后以 $1$ 节点为根，从 $1$ 节点的儿子开始进行操作。设当前操作节点为 $u$，其父亲为 $f$，$i$ 节点上面的数是 $ans_i$，$u$ 与 $f$ 中间边上的数是 $w$。

- 如果 $ans_f=w$，由于这条边需要正好一个节点的 $ans$ 为 $w$，所以 $ans_u$ 为 $1$ 到 $n$ 中除 $w$ 外任何一个数。

- 如果 $ans_f\neq w$，由于这条边需要正好一个节点的 $ans$ 为 $w$，所以 $ans_u$ 为 $w$。

所以无论 $ans_f$ 为多少，总有一个 $ans_u$ 满足条件，所以保证有解。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
pii mkp(int v, int w){pii p; p.first = v, p.second = w; return p;}
int n, m, fa[200001], ans[200001];
vector<pii > g[200001];
int find(int u){if (fa[u] == u) return u; return fa[u] = find(fa[u]);}
void dfs(int u, int f, int val){//深搜，val表示当前边上的数
	if (u != 1){
		if (ans[f] == val) ans[u] = ans[f] % n + 1;
		else ans[u] = val;
	}
	for (int i = 0; i < g[u].size(); i++){
		int v = g[u][i].first, w = g[u][i].second;
		if (v != f) dfs(v, u, w);
	}
}
signed main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++){
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		int fu = find(u), fv = find(v);
		if (fu != fv){
			g[u].push_back(mkp(v, w));
			g[v].push_back(mkp(u, w));
			fa[fv] = fu;
		}//边输入边并查集
	}
	ans[1] = 1; dfs(1, 0, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：New_hope (赞：0)

要保证剩下的图联通，最坏情况是一颗树。

所以我们直接维护一颗生成树，保证树边是合法的即可。

因此，在图联通的情况下，不存在无解的情况。

参考代码：


```cpp
#include <bits/stdc++.h>
#define _ 100005
using namespace std;

struct E { int v, c; };
int n, m;
int co[_], fa[_];
bool tg[_];
vector <E> G[_];
vector <int> check[_];

void dfs (int u)
{
  for (auto i : G[u]) {
    int v = i.v, c = i.c;
    if (v == fa[u]) {
      if (co[fa[u]] == c) {
        co[u] = (c > 1 ? c - 1 : c + 1);
      } else {
        co[u] = c;
      }
    }
  }
  for (auto i : G[u]) {
    int v = i.v;
    if (tg[v]) continue;
    tg[v] = 1, fa[v] = u;
    dfs (v);
  }
}

int main()
{
  cin >> n >> m;
  for (int i = 1; i <= m; i ++) {
    int u, v, c;
    cin >> u >> v >> c;
    G[u].push_back({v, c});
    G[v].push_back({u, c});
  }
  tg[1] = 1; co[1] = 1;
  dfs (1);
  for (int i = 1; i <= n; i ++) {
    cout << co[i] << ' ';
  } cout << '\n';


  return 0;
}
/*
g++ AT_arc108_c.cpp -o c.exe -O2 -std=c++14
*/
```

---

## 作者：TLEWA (赞：0)

题目的限制条件很松，大胆猜结论：对于任意一个联通图，都可以构造出符合题意要求的点权。

考虑构造一颗生成树，注意到叶子节点只与生成树上一条边相连，于是我们可以根据这条边与父节点的匹配结果来确定是否构造点权与边权相等，此时无论父节点取何值，连接叶子节点的边都可以满足匹配条件。类似地，我们发现在取任意值均可匹配到叶子的边的情况下，父节点具有与叶子节点相似的性质，如此一直逆推到根，对于任意生成树可以构造出一个可行解，根节点取任意值即可。

## AC 代码


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100005;

int n,m;

int val[N];
vector<pair<int,int>> vec[N];

int cnt;
void dfs(int u) {
	++cnt;
	for(auto& [v,w]:vec[u]) {
		if(val[v]) continue;
		if(w==val[u]) val[v]=(w%n)+1;
		else val[v]=w;
		dfs(v);
	}
}

int main() {
	cin >> n >> m;
	
	int u,v,w;
	for(int i=1;i<=m;++i) {
		cin >> u >> v >> w;
		vec[u].push_back({v,w});
		vec[v].push_back({u,w});
	}
	
	val[1]=1;
	dfs(1);
	
	if(cnt!=n) {
		cout << "No";
		return 0;
	}
	
	for(int i=1;i<=n;++i) cout << val[i] << endl;
	
	return 0;
}

```

时间复杂度 $O(n)$。

---

## 作者：lfxxx (赞：0)

考虑一颗树怎么染色。

每个子节点染成边的颜色，如果与父亲节点相同，就随便染色（这条边的限制已经被父亲节点满足）。

那么一定可以染色。

所以把原图跑最小生成树再按上述方法染色即可。

倘若原图不连通，那么无解。

---

