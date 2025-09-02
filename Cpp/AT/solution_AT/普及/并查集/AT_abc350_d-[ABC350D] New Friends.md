# [ABC350D] New Friends

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_d

$ 1 $ から $ N $ の番号がついた $ N $ 人のユーザが利用している SNS があります。

この SNS では $ 2 $ 人のユーザが互いに**友達**になれる機能があります。  
 友達関係は双方向的です。すなわち、ユーザ X がユーザ Y の友達であるならば、必ずユーザ Y はユーザ X の友達です。

現在 SNS 上には $ M $ 組の友達関係が存在し、$ i $ 組目の友達関係はユーザ $ A_i $ とユーザ $ B_i $ からなります。

以下の操作を行える最大の回数を求めてください。

- 操作：3 人のユーザ X, Y, Z であって、X と Y は友達、Y と Z は友達であり、X と Z は友達でないようなものを選ぶ。X と Z を友達にする。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- 入力は全て整数である
 
### Sample Explanation 1

次のようにして「友達の友達と新たに友達になる」という操作は $ 3 $ 回行えます。 - ユーザ $ 1 $ が友達(ユーザ $ 2 $)の友達であるユーザ $ 3 $ と新たに友達になる - ユーザ $ 3 $ が友達(ユーザ $ 1 $)の友達であるユーザ $ 4 $ と新たに友達になる - ユーザ $ 2 $ が友達(ユーザ $ 1 $)の友達であるユーザ $ 4 $ と新たに友達になる $ 4 $ 回以上行うことはできません。

### Sample Explanation 2

もともと友達関係が存在しないとき、新たな友達関係は発生しません。

## 样例 #1

### 输入

```
4 3
1 2
2 3
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
3 0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 8
1 2
2 3
3 4
4 5
6 7
7 8
8 9
9 10```

### 输出

```
12```

# 题解

## 作者：Harrylzh (赞：4)

## 题意

有 $n$ 个人，其中有 $m$ 对朋友关系，朋友关系总是相互的。如果 A 和 B 是朋友关系且 B 和 C 是朋友关系，则添加一对 A 和 C 的朋友关系定义为一次操作。求可以操作的最多次数。

## 思路

显然，把有朋友关系的人连上边，一个连通块内的所有人都可以通过若干次操作来互相成为朋友。求出每个连通块的大小，人数和已有的朋友关系，就可以求出连通块内未有的朋友关系，也就是答案。这个过程可以用并查集维护。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long fath[1000000+5];
long long sz[1000000+5];//已有关系数
long long lsz[1000000+5];//人数
long long getfather(long long i)
{
	return fath[i]==i?i:fath[i]=getfather(fath[i]);
}
bool vis[1000000+5];
int main()
{
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=1000000;i++)
	{
		fath[i]=i;
		lsz[i]=1;
		sz[i]=0;
	}
	for(long long i=1;i<=m;i++)
	{
		long long x,y;
		scanf("%lld%lld",&x,&y);
		long long fx=getfather(x);
		long long fy=getfather(y);
		if(fx==fy)
		{
			sz[fx]++;
		}
		else
		{
			sz[fx]=sz[fy]+sz[fx]+1;
			lsz[fx]+=lsz[fy];
			fath[fy]=fx;
		}
	}
	long long ans=0;
	for(long long i=1;i<=n;i++)
	{
		long long fx=getfather(i);
		if(vis[fx]) continue;
		vis[fx]=1;
		ans+=lsz[fx]*(lsz[fx]-1)/2-sz[fx];//可以有的朋友关系数-已有的朋友关系数
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：OAer (赞：3)

### 题意

社交媒体上有 $N$ 个用户，有 $M$ 个**双向的**好友关系，第 $i$ 条说明了用户 $A_i$ 和用户 $B_i$ 是好友。

接下来你要进行下面的操作**尽可能多次**：选择 $3$ 个用户 $x,y,z$，其中 $x$ 和 $y$ 是好友，$y$ 和 $z$ 是好友，但 $x$ 和 $z$ 不是好友。然后使 $x$ 和 $z$ 成为好友。

问你能操作多少次？

### 分析

考虑转图论。若将“用户”换成节点，“关系”变成无向边，这题就变成了这样：

> 给你一张无向图，问你最多能执行下面的操作多少次：
> 
> 选择 $3$ 个点，它们之间**有且只有** $2$ 条边。在这个子图上，将度为 $1$ 的两个点用无向图连接。

不难发现，不联通的点不能参与进行操作，完全图内不能进行操作。而对于一个联通的图（点数大于 $2$），其中必定存在两条有公共点的边，只要不是完全图，就可以进行操作。

综上所述，对于每一个联通的子图，在这个图中能操作的次数就是变成完全图需要添加的边数。若这个子图有 $k$ 个点，那么这个图中能操作的次数就是 $\frac{k(k-1)}{2}$ （完全图的边数）减去这个图中的边数。

用并查集维护连通图的点数和边数即可。合并的时候，若两个点在同一集内，只需要单纯增加边数。注意在合并的时候，要加上额外连的一条边。

PS：对于点数为 $1$ 和 $2$ 的子图，自身已经构成完全图，操作次数可以表述为上面说的公式。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
int fa[500005];//父节点 
ll e[500005];//边数 
ll sz[500005];//点数 
int Find(int x){//寻找父亲节点 
	if(fa[x]==x) return x;
	else return fa[x]=Find(fa[x]);
}
void Union(int x,int y){
	int s=Find(x),t=Find(y);
	if(s==t) e[s]++;//合并的时候加边 
	else{
		fa[s]=t;
		e[t]=e[s]+e[t]+1;//注意要加1 
		sz[t]=sz[s]+sz[t];//大小 
	}
}
ll Wanquan(ll x){//完全图的点数 
	return x*(x-1)/2;
}
int n,q;ll ans;
int main(){
	scanf("%d %d",&n,&q);
	rep(i,1,n){
		fa[i]=i;
		sz[i]=1;//初始化的时候点数为1，边数为0 
	}
	while(q--){
		int x,y;
		scanf("%d %d",&x,&y);
		Union(x,y);
	}
	rep(i,1,n){
		if(fa[i]==i)
			ans+=(Wanquan(sz[i])-e[i]);//如题 
	}
	printf("%lld",ans);
	return 0;
}

```

[AT 记录](https://atcoder.jp/contests/abc350/submissions/52600972)

### 最后的忠告

开 `long long`！

---

## 作者：MMXIandCCXXII (赞：2)

$\Large{\text{solution}}$

想清楚了其实很简单，不难发现，一条链上的点都会双双链接（可以看样例三）。连接好这些边后，肯定又会产生新的链，一直连，直到无法连为止。最后就会发现，一个联通块里的点都会两两相连。所以只需要统计每个联通块里点的数量，答案就是 $\sum \frac{a(a-1)}{2} - m$，$a$ 就是每个联通块点的数量。

$\Large{\text{code}}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

vector <int> v[200010];
bool vis[200010];
int cnt;

void dfs(int u)
{
    cnt++;
    vis[u] = true;
    for (int j : v[u])
    {
        if (vis[j]) continue;
        dfs (j);
    }
}

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back (b);
        v[b].push_back (a);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) cnt = 0, dfs (i), ans += cnt * (cnt - 1) / 2;
    cout << ans - m << endl;
    return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC350D] New Friends](https://www.luogu.com.cn/problem/AT_abc350_d)

掉分，或许也是好事。

考虑建图，发现最后会形成很多个连通块，则每个联通块中的人互相都是朋友关系。设该联通块中共有 $sum$ 个人，最初已经形成朋友关系的有 $cnt$ 对，则新增加的朋友对数为 $\dfrac{sum \times (sum-1)}{2} - cnt$。累加答案即可。注意：最初形成的朋友关系在图中表现为有直接边相连的两个点。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n, m, st, sum, cnt, a[N], b[N], ans;
bool vis[N];
vector <int> G[N];
void dfs(int x)
{
	if (!vis[x]) sum++, vis[x] = 1;
	for (auto i : G[x]) {
		cnt ++; // 记录最初的朋友个数（的两倍）
		if (!vis[i]) dfs(i);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a[i] >> b[i];
		int u = a[i], v = b[i];
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= m; i++) {
		if (!vis[b[i]]) { // 新的连通块
			cnt = 0, sum = 0;
			dfs(b[i]);
			ans += (sum * (sum - 1))/2 - cnt/2;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：MicroSun (赞：1)

考虑抽象为图论模型，对于每对朋友建双向边。

注意到操作结束后这张图中的每一个连通分量必定变为完全图，于是对与每一个连通分量，计算其边数，并与完全图的边数作差即可。

可以用并查集维护，但是我写了个 `dfs`，调了 20min。

复杂度 $\Omicron(n+m)$。

[Code](https://atcoder.jp/contests/abc350/submissions/52634946)

---

## 作者：Special_Tony (赞：1)

个人认为 C>D。
# 思路
首先对于每个连通块，我们尽量让它们都变成完全图。然后判连通块可以用并查集，也可以用 BFS，本人用了并查集。注意最后要减去现有的 $m$ 条边。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, f[200005], q, x, y, s[200005];
ll sum;
int find (int x) {
	return x == f[x] ? x : f[x] = find (f[x]);
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i)
		f[i] = i;
	sum = -q;
	while (q --) {
		cin >> x >> y;
		f[find (x)] = find (y);
	}
	for (int i = 1; i <= n; ++ i)
		++ s[find (i)];
	for (int i = 1; i <= n; ++ i)
		if (s[i])
			sum += s[i] * (s[i] - 1ll) / 2;
	cout << sum;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

看到这样的输入格式，不难想到先建图。进而，我们去考虑什么时候无法再添加朋友。如果说当前这些有朋友关系的人已经两两是朋友，那么就无法添加了；否则，只要这些人的数量达到 $2$ 个，就可以给他们交朋友直到上述情况。把这个思路转成图论模型那就是，把每个连通块转为完全图还缺的边数。最后把所有连通块的答案加起来即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
int vis[N],ltkn[N],lcnt=0,ltk[N],in[N];
vector<int> G[N],ltks[N];
void dfs(int u)
{
	if(vis[u]) return;
	ltk[u]=lcnt;
	ltkn[lcnt]++;
	ltks[lcnt].push_back(u);
	vis[u]=1;
	for(auto v:G[u]) dfs(v);
}
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		in[u]++;
	} 
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		lcnt++;
		dfs(i);
	}
	int ans=0;
	for(int i=1;i<=lcnt;i++)
	{
		int now=0;
		for(auto u:ltks[i]) now+=in[u];
		ans+=ltkn[i]*(ltkn[i]-1)/2-now;
	}
	cout<<ans;
	return 0;
}

---

## 作者：_Weslie_ (赞：0)

赛时分析错并查集复杂度导致 $\tt rating$ 减 $16$。

### 思路

根据样例，我们可以发现这个图可能会有许多连通块。

对于其中一个连通块分析：如果它不是一个完全连通块，那么把它变为完全连通块是最优的。

而一个完全连通块（有 $n$ 个节点）有 $\dfrac{n(n-1)}{2}$ 条边，但是众所周知这之中有一些边，所以我们要把它们减掉。

怎么计算这之中的边数呢？预处理每个点的度数（即相连接的边数）。

处理到这个点就加上这个点的度数。

但是每一条边连着两个点，这意味着我们统计出来的边数是实际边数的 $2$ 倍。

如此计算便能得出答案。

### 代码实现

有并查集和 $\tt bfs$ 两种写法，这里采用 $\tt bfs$ 写法。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int u,v,nxt;
}e[400005];
int head[200005],cnt,vis[200005];
void add(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m;
long long ans=0,du[200005];
queue<int>q;
long long bfs(int _){
	q.push(_);
	long long sum=0;
	long long summ=0;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		if(vis[now])continue;
//		cout<<now<<endl;
		vis[now]=1;
		sum++;
		summ+=du[now];
		for(int i=head[now];i;i=e[i].nxt){
			if(!vis[e[i].v])q.push(e[i].v); 
		}
	}
	return sum*(sum-1)/2-summ/2;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
		du[u]++;
		du[v]++;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			ans+=bfs(i);
		} 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_KHIN (赞：0)

### 题意简述

有一张无向图，上面有一些边，注意：**图不一定连通**。

你可以选择三个满足 $X$ 与 $Y$ 相连，$Y$ 与 $Z$ 相连，$X$ 与 $Z$ 不相连的点 $X,Y,Z$，然后在 $X$ 与 $Z$ 之间连一条边，请问最多能执行多少次这样的操作。

### 思路

首先可以得到的性质是，对于任意一个连通块，一定可以通过若干次操作将它变成完全图。

具体的证明考虑归纳，假设现在已经构造出了大小为 $n-1$ 的完全图，由于第 $n$ 个点和这个完全图之间至少有一条边，我们用这条边和完全图中已有的边即可使点 $n$ 与每个点之间有连边。

每操作一次增加一条边，所以对于一个点数为 $n$，边数为 $m$ 的联通块，能执行的操作个数为 $\frac{n\times (n-1)}{2}-m$。

显然我们只需要知道边的总数为 $m$，而不关心具体每个连通块有多少边。那么现在的问题是如何求出每个连通块的点数。

考虑用并查集维护，以 $i$ 为根连通块的大小就是 $\text{find}(x)=i$ 的个数。

时间复杂度 $\mathcal{O}(n\log n)$。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],b[200005],n,m,f[200005],ans[200005],cnt;
int find(int x)
{
	if(x==f[x])
	{
		return f[x];
	}
	return f[x]=find(f[x]);
}//并查集，如果没学过请移步 P3367
signed main()
{
 	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
	}//初始化
	for(int i=1;i<=m;i++)
	{
		cin>>a[i]>>b[i];
		f[find(b[i])]=find(a[i]);//合并
	}
	for(int i=1;i<=n;i++)
	{
		ans[find(i)]++;//统计答案
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]>=1)//不然会 re
		{
			cnt+=ans[i]*(ans[i]-1)/2;
		}
	}
	cout<<cnt-m;
    return 0v0;
}
```

---

## 作者：fuxiheng (赞：0)

### 题意
给你一个图，有一些边。如果有两个点它们连通但并没有直接相连，那么可以给它们连上一条边。求最多可以再连上多少条边。
### 分析
首先，图的连通性，一眼并查集。其次，我们发现每一个连通块最后都可以连成完全图。而完全图的边数是很好算的，所以答案就是每一个连通块成为完全图之后的边数之和再减去初始边数。当时脑子或许有点抽，代码实现有些麻烦了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005;
	int fa[MAXN], sz[MAXN], Sz[MAXN];
	int belong(int x){
		if(fa[x] == x) return x;
		return fa[x] = belong(fa[x]);
	}
	void Union(int x, int y){
		int X = belong(x), Y = belong(y);
		Sz[X]++;
		if(X == Y) return ;
		if(sz[X] < sz[Y]) swap(X, Y);
		fa[Y] = X;
		sz[X] += sz[Y];
		Sz[X] += Sz[Y]; 
	}
	int t[MAXN];
	int main(){
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1;i <= n;i++){
			fa[i] = i;
			sz[i] = 1;
		}
		for(int i = 1, a, b;i <= m;i++){
			scanf("%d%d", &a, &b);
			Union(a, b);
		}
		long long ans = 0;
		for(int i = 1;i <= n;i++){
			int u = belong(i);
			if(t[u]) continue;
			t[u] = 1;
			ans += 1ll * sz[u] * (sz[u] - 1) / 2 - Sz[u];
		}
		printf("%lld", ans);
		return 0;
	}
} 
int main(){
	return Luo_ty::main();
}
```

---

## 作者：Lotus_Land (赞：0)

### 题意

有一个由 $N$ 个用户使用的 SNS，用户标记为从 $1$ 到 $N$ 的数字。

在这个 SNS 中，两个用户可以成为朋友。友谊是双向的；如果用户 $X$ 是用户 $Y$ 的朋友，那么用户 $Y$ 也是用户 $X$ 的朋友。

目前，在 SNS 上有 $M$ 对友谊，第 $i$ 对由用户 $A_i$ 和 $B_i$ 组成。

确定可以执行以下操作的最大次数：

操作：选择三个用户 $X$、$Y$ 和 $Z$，满足 $X$ 和 $Y$ 是朋友，$Y$ 和 $Z$ 是朋友，但 $X$ 和 $Z$ 不是朋友。使 $X$ 和 $Z$ 成朋友。

### 分析

显然后面的操作连起来的朋友一定有个共同的朋友。如果两个人原本没有共同的朋友，那么他们永远都不会连在一起。

用并查集把有朋友关系的人存储在同一个连通块中，连通块可能不止一个。操作只能对于在同一个连通块里的人进行。在一个有 $m$ 个人的连通块中，原先已有 $e$ 对朋友，那么还可以再连上 $m\times(m-1)\times\dfrac{1}{2}-e$ 对。

```cpp
int n,m,a[N],b[N];
int fa[N],siz[N],s[N];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>a[i]>>b[i];
		fa[find(a[i])]=find(b[i]);
	}
	for(int i=1;i<=n;i++){
		fa[i]=find(i);
		s[fa[i]]++;
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		siz[fa[a[i]]]++;
	}
	for(int i=1;i<=n;i++){
		ans+=(s[i]-1)*s[i]/2-siz[i];
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：PDAST (赞：0)

赛时最后一分钟调出来，还是那句话，十年 OI 一场空，不开 long long 见祖宗（详见[我的忏悔录](https://www.luogu.com.cn/article/bn6qm53q)）。
## 题意
这里有一个社交平台，上面有 $n$ 个用户，现在给你 $m$ 条关系，每条关系代表两个人 $a$ 和 $b$ 是朋友，每次可以进行一个操作，当 $x$ 是 $y$ 的朋友且 $y$ 是 $z$ 的朋友并且 $x$ 和 $z$ 不是好友时，可以让 $x$ 和 $z$ 成为朋友。求最多能进行几次这样的操作。
## 思路
我最开始想的是图，但发现数据范围略略有些恐怖，就想到了图的兄弟，并查集。并查集是个好东西，经过路径压缩和按秩合并后，复杂度很低，不会的可以看[这篇文章](https://blog.csdn.net/weixin_51250927/article/details/113448263)。当我们有了并查集这个东西时，一切都迎刃而解。他会有一条条友链，我们只需要求出每个友链有多少人就可以求出每个友链的最大连接数，累加后减去现有关系数即可。
## 具体实现
每次输入后就合并一次，然后接一个循环，枚举每个用户，如果他的父亲的父亲不是他的父亲（即他不是直接连接祖先节点）时，进行一次路径压缩，压缩完后把这个友链的用户数加一，接着再一个循环做累加，求出最多可以存在多少个关系，再减去 $m$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[200001],h[200001],n,m,k,a[200001],ans;
void Init() {
	for(int i=1; i<=n; i++) {
		f[i]=i;
		h[i]=0;
	}
}
int Find(int i) {
	return (f[i]==i?f[i]:f[i]=Find(f[i]));
}
void merge(int a,int b) {
	int fa=Find(a),fb=Find(b);
	if(fa!=fb) {
		if(h[fa]<h[fb]) {
			f[fa]=fb;
		} else {
			f[fb]=fa;
			if(h[fa]==h[fb]) {
				h[fa]++;
			}
		}
	}
}
signed main() {
	cin>>n>>m;
	Init();
	for(int i=1; i<=m; i++) {
		int x,y;
		cin>>x>>y;
		merge(x,y);
	}
	for(int i=1; i<=n; i++) {
		if(f[f[i]]!=f[i]) {
			int x=Find(i);
		}
		a[f[i]]++;
	}
	for(int i=1; i<=n; i++) {
		ans+=(a[i]*(a[i]-1))/2;
	}
	cout<<ans-m;
	return 0;
}
```

---

## 作者：Starrykiller (赞：0)

显然不同的连通块之间不影响，我们分成不同连通块考虑。

我们有如下结论：

> **结论** 一个连通块在操作到不能操作时，这个连通块构成的子图是一个完全图。

证明是比较显然的。

于是我们 dfs 出连通块，然后答案就是

$$\sum_i \frac{siz_i(siz_i-1)}{2}-m$$

其中 $siz_i$ 表示第 $i$ 个连通块的大小。

时间复杂度 $\Theta(n+m)$。

[My implementation](https://atcoder.jp/contests/abc350/submissions/52570669) (For reference only)

---

