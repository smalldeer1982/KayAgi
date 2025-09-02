# [AGC067A] Big Clique Everywhere

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc067/tasks/agc067_a

$ 1 $ から $ N $ までの番号がついた $ N $ 頂点の単純無向グラフ $ G $ が与えられます。 $ G $ は $ M $ 本の辺を持ち、$ i $ 本目の辺は頂点 $ A_i $ と $ B_i $ を結びます。

$ G $ が次の条件を満たすか判定してください。

- 頂点集合 $ \{1,2,\cdots,N\} $ のすべての部分集合 $ X $ に対して、$ X $ の部分集合 $ Y $ であって $ |Y|\ge\ \frac{|X|}{2} $ かつ $ Y $ がクリークを形成するものが存在する。

解くべきテストケースは $ T $ 個あります。

## 说明/提示

### 制約

- $ 1\le\ T\ \le\ 10^3 $
- $ 1\le\ N\ \le\ 10^5 $
- $ 0\ \le\ M\ \le\ 10^6 $
- $ 1\ \le\ A_i,B_i\ \le\ N $
- 与えられるグラフは自己辺も多重辺も含まない。
- ひとつの入力の中のテストケースすべてにわたる $ N $ の総和は $ 10^5 $ 以下である。
- ひとつの入力の中のテストケースすべてにわたる $ M $ の総和は $ 10^6 $ 以下である。
- すべての入力値は整数である。

### Sample Explanation 1

$ 1 $ 番目のテストケースについて、$ G $ は条件を満たします。 この場合、すべての部分集合 $ X $ がクリークであるため、単に $ Y=X $ とできます。 $ 2 $ 番目のテストケースについて、$ G $ は条件を満たします。 例えば、$ X=\{2,3\} $ に対しては、$ Y=\{2\} $ とできます。 $ 4 $ 番目のテストケースについて、$ G $ は条件を満たしません。 $ X=\{1,2,3\} $ とすると、条件を満たす $ X $ の部分集合 $ Y $ はありません。

## 样例 #1

### 输入

```
4
3 3
1 2
1 3
2 3
3 2
1 2
1 3
3 1
1 2
3 0```

### 输出

```
Yes
Yes
Yes
No```

# 题解

## 作者：251Sec (赞：12)

哥们这题真难吧？

---

在补图上考虑问题，那么团就是独立集了。发现如果有一个奇环那么这个奇环怎么都选不出来一个大小为一半的独立集。而如果没有奇环，那么说明是二分图，那么对于任何集合 $S$，二分图的两边至少有一边大小大于等于 $\frac{|S|}{2}$，选这边就可以了。

所以合法当且仅当补图是二分图。暴力判断是 $O(n^2)$ 的。但是注意到 $m < \frac{n(n - 1)}{2} - \left\lfloor\frac{n}{2}\right\rfloor\left(n -\left\lfloor\frac{n}{2}\right\rfloor\right)$ 的时候一定不合法。那么判掉这个之后 $m$ 和 $n^2$ 同阶。复杂度就是 $O(m)$ 了。

---

## 作者：0xyz (赞：2)

给你一个 $n$ 个点 $m$ 条边的简单无向图 $G$，你需要判定是否 $G$ 中所有点导出子图 $X$ 都存在点数不少于一半的完全图 $Y$。

如果 $G$ 中所有点导出子图 $X$ 都存在点数不少于一半的完全图 $Y$，那么把任意一个点导出子图变成它的补图，原本的属于完全图上的点之间两两没有边，也就是这些点构成一个独立集。从而， $G$ 的补图中所有点导出子图 $X$ 都存在点数不少于一半的的独立集 $Y$。

对 $G$ 的补图进行研究，如果存在奇环，那么取 $X$ 为这个奇环，容易发现最大独立集 $Y$ 有 $2|Y|\le |X|-1$，矛盾。从而 $G$ 的补图中没有奇环，也就是 $G$ 的补图是二分图。

另一个方面，如果 $G$ 的补图是二分图，我们不妨将 $G$ 中的点染成黑色和白色，使得每条边的两个端点一黑一白，那么对于任意的 $X$，如果白点个数大于等于一半，则取 $Y$ 为 $X$ 中所有白点；白点个数小于一半，那么黑点个数一定大于一半，从而可以取 $Y$ 为 $X$ 中所有黑点。综上，$G$ 的补图是二分图时，$G$ 一定满足条件。

$G$ 的补图有 $\frac{n(n-1)}{2}-m$ 条边，直接做会超时。注意到有 $n$ 个点的二分图至多 $\frac{n^2}{4}$ 条边，所以如果答案为 `YES`，一定要有 $\frac{n(n-1)}{2}-m\le \frac{n^2}{4}$，也就是 $n\le\sqrt{4m+1}+1$。增加了这个判断之后，$\frac{n(n-1)}{2}-m$ 降为 $O(m)$ 级别。

所以问题转化为：

- 如果 $n>\sqrt{4m+1}+1$，输出 `NO`
- 否则
  - 如果 $G$ 的补图是二分图，输出 `YES`
  - 否则输出 `NO`。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int _=2009;
int a[_*_],b[_*_],c[_],d[_][_],m,n,T;
void work(){
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!c[i]){
			c[i]=1;q.push(i);
			while(!q.empty()){
				int x=q.front();q.pop();
				for(int i=1;i<=n;i++)
					if(d[x][i]){
						if(!c[i])c[i]=3-c[x],q.push(i);
						else if(c[i]==c[x]){
							cout<<"NO\n";
							return;
						}
					}
			}
		}
	cout<<"YES\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=m;i++)cin>>a[i]>>b[i];
		if(n>sqrt(4*m+1)+3)cout<<"NO\n";
		else{
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)d[i][j]=1;
				c[i]=d[i][i]=0;
			}
			for(int i=1;i<=m;i++)d[a[i]][b[i]]=d[b[i]][a[i]]=0;
			work();
		}
	}
	return 0;
}
```

如果把题目中的“团”变成“联通块”，可以转化为 $G$ 的补图中没有三角形。

---

## 作者：Pentiment (赞：1)

团有些难搞，把图取反，对团的要求就变成了对独立集的要求。

要求每个点集都存在一个大小不小于它的一半的独立集，发现二分图满足这个要求；而且如果图中存在奇环，则奇环上的最大独立集小于一半，不符合题意。因此当且仅当补图是二分图时满足条件。

由于点数很大不能直接判，发现当 $m<\dfrac12n(n-1)-\dfrac{n^2}{4}$ 时，补图一定不是二分图（因为二分图最大边数为 $\dfrac{n^2}{4}$，再多一条边一定会在同一个部分的点中连边），代入 $m\leq 10^6$ 得 $n\leq 2002$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005, M = 1000005;
int T, n, m, c[N];
pair<int, int> e[M];
bool G[N][N];
bool dfs(int u, int x) {
	c[u] = x;
	for (int v = 1; v <= n; v++) {
		if (u == v || G[u][v]) continue;
		if (c[v] == x) return 0;
		if (!c[v] && !dfs(v, -x)) return 0;
	}
	return 1;
}
bool check() {
	memset(c, 0, n + 1 << 2);
	bool ans = 1;
	for (int i = 1; i <= n; i++) {
		if (!c[i] && !dfs(i, 1)) return 0;
	}
	return 1;
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		if (n <= 2002) G[u][v] = G[v][u] = 1, e[i] = {u, v};
	}
	if (n > 2002) return void(puts("No"));
	puts(check() ? "Yes" : "No");
	for (int i = 1, u, v; i <= m; i++) {
		u = e[i].first, v = e[i].second;
		G[u][v] = G[v][u] = 0;
	}
}
int main() {
	scanf("%d", &T);
	while (T--) solve();
}
```

---

## 作者：zxh923 (赞：1)

给个链接：[Big Clique Everywhere](https://www.luogu.com.cn/problem/AT_abc282_g)。

先说一下团（clique）是什么，其实就是完全图。

考虑什么情况下不满足题意。我们可以先建出补图，下面的东西都在补图中完成。

我们首先给出结论：如果该图中有奇环（不是二分图），则条件不成立，否则成立。

这里证明一下：如果存在奇环，则把点集设为这个奇环中的点，那么一定无法满足。显然我们无法同时选出两个相邻的点，因为在原图中，任意两个相邻的点之间没有边，所以一定选不出来至少一半的点。

然后就是，为什么是二分图一定有解。这里分类讨论一下：

+ 选的点在一部里面。此时这些点在补图中必然两两之间没有边，则在原图中他们构成一个团，显然合法。

+ 选的点横跨两部。此时必然有一部的点占到至少一半，对于这些点，就可以用上一种情况证明。

还有一个比较直观的事情，当 $n$ 比较大的时候，是一定无解的。这里其实如果 $n\ge 2002$，则直接无解。否则我们暴力建出补图，染色判断其是否为二分图即可。

代码：

```
#include<bits/stdc++.h>
#define int long long
#define N 200005
#define M 8001005
using namespace std;
int T,n,m,x[M],y[M],st[N];
int h[N],e[M],ne[M],idx;
bool edge[2009][2009];
void add(int a,int b){
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
bool dfs(int u,int c){
	st[u]=c;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(!st[j]){
			if(!dfs(j,3-c))return 0;
		}
		else if(st[j]==c)return 0;
	}
	return 1;
}
void solve(int cs){
	cin>>n>>m;
	if(n<2002){
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				edge[i][j]=0;
			}
		}
	}
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		if(n<2002)edge[x[i]][y[i]]=edge[y[i]][x[i]]=1;
	}
	if(n>=2002){
		cout<<"No\n";
		return;
	}
	idx=0;
	for(int i=1;i<=n;i++){
		h[i]=-1;
		st[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!edge[i][j])add(i,j),add(j,i);
		}
	}
	bool flag=1;
	for(int i=1;i<=n;i++){
		if(!st[i]){
			if(!dfs(i,1)){
				flag=0;
				break;
			}
		}
	}
	cout<<(flag?"Yes\n":"No\n");
}
signed main(){
	cin>>T;
	for(int cs=1;cs<=T;cs++){
		solve(cs);
	}
	return 0;
}
```

---

## 作者：strcmp (赞：0)

题意翻译说得很清楚了。

直接对着做？找 $3$ 个两两没有连边的点，找 $5$ 个最大团至多为 $2$ 的点，找 $7$ 个最大团至多为 $3$ 的点。好像都不好找。

团是完全图，直接对着完全图做并不好做，那不妨考虑其补图，如果考虑补图那么一个团在补图中两两没有连边，也就是独立集。

独立集明显比团好考虑很多了。

然后我们就希望知道补图应该是一个什么结构，能使得任意一个导出子图都存在点数大于等于一半的独立集。

链、菊花图、树等等这些结构都太平凡。但找出它们的共同点我们发现它们都是二分图。

那不妨考虑一个二分图，如果补图的一个连通块形成二分图，并且随便搞了一个它的导出子图（二分图的导出子图一定还是二分图），我们找导出子图左右部点中较大的那一个，一定就能有大小不少于一半点数的最大独立集。这就赢了！

我们考虑证明如果补图的一个连通块不是二分图，那么它一定存在导出子图找不出大小不少于一半点数的最大独立集。

其实很容易证明，不是二分图等价于存在奇环，而我们发现单个奇环的最大独立集就是点数一半下取整减一，不满足条件。

于是我们原题就弱化为：判定补图是否是二分图，是则 `Yes` 否则 `No`。

  我们不能直接做补图，因为补图的边数是 $\Theta(n^2 - m)$ 级别的。但是我们知道二分图的边数最多是 $|\text{E} : \text{K}_{n,\,n}| = n^2$，而 $2n$ 个点的完全图 $\text{K}_{2n}$ 有 $2n^2 - n$ 条边。

于是我们先判定 $m$ 是否小于 $n$ 个点的完全图和 $\text{K}_{\lfloor \frac{n}{2} \rfloor,\,\lceil \frac{n}{2} \rceil}$ 的边数差，如果小于那么就直接 `No`。

于是我们的 $n$ 被限制在了 $\Theta(\sqrt{m})$ 的范围，暴力在补图上进行 dfs 染色判定二分图即可。时间复杂度 $\Theta(n + m)$。

感觉这题难点主要是在于同时想到补图和二分图，但实际上你仔细思考会发现这是有迹可循的。独立集一般比团好考虑，而我们去思考一个独立集的结构，不难会想到二分图，毕竟二分图的一部点的所有集合都形成独立集。

感觉还是需要对图结构有比较深刻的理解的。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pq = priority_queue<int>;
using ld = double;
using pdi = pair<ld, int>;
using uint = unsigned;
using vec = vector<int>;
constexpr int maxn = 4e5 + 10, mod = 998244353; constexpr ll inf = 1e18;
int g[3005][3005], vis[3005], T, n, m, ans;
void dfs(int u) {
	rep(v, 1, n) {
		if (g[u][v] && !vis[v]) vis[v] = 3 - vis[u], dfs(v);
		else if (g[u][v] && vis[u] == vis[v]) ans = 0;
	}
}
inline int solve() {
	scanf("%d%d", &n, &m);
	if (n > 2100) return 0;
	rep(i, 1, n) rep(j, 1, n) g[i][j] = 0;
	for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), g[u][v] = g[v][u] = 1;
	rep(i, 1, n) rep(j, 1, n) if (i != j) g[i][j] ^= 1; ans = 1; 
	memset(vis, 0, sizeof(vis)); rep(i, 1, n) if (!vis[i]) vis[i] = 1, dfs(i);
	return ans;
}
int main() {
	scanf("%d", &T);
	while (T--) puts(solve() ? "Yes" : "No");
    return 0;
}
```

---

## 作者：Filberte (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_agc067_a)

## 思路
因为 $m \le 10^6$，所以在 $n > 2002$ 时显然无解。考虑原图 $G$ 的补图 $G'$，此时 $G$ 中导出子图的团对应 $G'$ 中导出子图的独立集。

结论：$G'$ 中无奇环 $\iff$ $G$ 满足题意。

必要性：$G'$ 中如果存在一个$2k + 1$ 个点的奇环，那么在这个环上最多只能选出 $k$ 个点，不满足题意。

充分性：$G'$ 中无奇环，则说明 $G'$ 是一个二分图，二分图的任意一个导出子图独立集大小 $\ge \dfrac{n}{2}$ 。

所以原问题就转为成二分图判定了。

## 代码
```cpp
#include <bits/stdc++.h>
#define de(x) cerr << #x << ":" << x << endl;
#define fp(...) fprintf(stderr,__VA_ARGS__)
#define int_32 signed
#define int long long
using namespace std;
int n, m;
bool e[2005][2005];
int col[2005];
bool dfs(int u, int c){
    col[u] = c;
    for(int v = 1;v <= n;v++){
        if(v == u || !e[u][v]) continue;
        if(col[v]){
            if(col[v] == c) return 0;
            continue;
        }
        if(!dfs(v, -c)) return 0;
    }
    return 1;
}
bool check(){
    for(int i = 1;i <= n;i++) col[i] = 0;
    for(int i = 1;i <= n;i++) if(!col[i])
        if(!dfs(i, 1)) return 0;
    return 1;
}
void sol(){
    vector<pair<int, int>> eds;
    cin >> n >> m;
    for(int i = 1, u, v;i <= m;i++){
        cin >> u >> v;
        if(n > 2002) continue;
        e[u][v] = e[v][u] = 0;
        eds.push_back({u, v});
    }
    if(n > 2002) cout << "No\n";
    else if(check()) cout << "Yes\n";
    else cout << "No\n";
    for(auto [u, v] : eds) e[u][v] = e[v][u] = 1;
}
int32_t main(){
    memset(e, 1, sizeof(e));
    int _cas = 1;
    cin >> _cas;
    while(_cas--) sol();
    return 0;
}

```

---

## 作者：ReTF (赞：0)

如果一张图的补图存在大小为 $x$ 的奇环，将整个环拎出来看，一定不存在一个大小大于 $\dfrac{x}{2}$ 的点集满足其中点两两无交。

原图的任何生成子图都存在大小至少为一半的团，所以原图的补图是二分图，原图的任意生成子图的补图也是二分图。

如果一张 $x$ 个点的图的补图是二分图，那么它一定存在一个大小至少为 $\dfrac{x}{2}$ 的团。这是因为二分图的某一部点中互相没有连边，所以较大的一部点（大小至少为 $\dfrac{x}{2}$）在原图中形成了一个团。

所以直接检查原图的补图是否是二分图即可。

因为 $n\ge 5000$ 一定不满足题设，特判即可。然后就可以使用邻接矩阵存边和生成补图了！

[Submission](https://atcoder.jp/contests/agc067/submissions/56889836)

---

## 作者：Phartial (赞：0)

有点厉害。

首先你取 $G$ 的补 $G'$，那么团就成了独立集。可以发现的是，如果 $G'$ 中有奇环，那么我们取这个奇环的导出子图，就只能选出小于一半的独立集。同时这一条件也是充分的，$G'$ 中没有奇环说明是一个二分图，而我们任选一个二分图的点导出子图，都可以通过只选左部点或右部点的方式得到一个点数不小于一半的独立集。

于是问题变成判定 $G'$ 是否是二分图，显然其中最多只能有 $(\frac{N}{2})^2$ 条边，于是若 $M<{N\choose 2}-(\frac{N}{2})^2$ 则 $G'$ 必然不是二分图。由于 $M\le 10^6<{2002\choose 2}-(\frac{2002}{2})^2$，故只要 $N\ge 2002$ 就可以直接判定不成立，否则暴力判定即可。

时间复杂度 $\Theta(N^2)$.

[code](https://atcoder.jp/contests/agc067/submissions/56882128).

---

