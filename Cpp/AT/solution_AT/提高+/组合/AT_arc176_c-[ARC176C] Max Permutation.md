# [ARC176C] Max Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc176/tasks/arc176_c

$ (1,2,\dots,N) $ の順列 $ P=(P_1,P_2,\dots,P_N) $ のうち、以下の条件を全て満たすものの個数を $ 998244353 $ で割ったあまりを出力してください。

- $ \max(P_{A_i},P_{B_i})\ =\ C_i\ (1\ \le\ i\ \le\ M) $

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ <\ B_i\ \le\ N $
- $ 1\ \le\ C_i\ \le\ N $
- $ i\ \neq\ j $ ならば $ (A_i,B_i)\ \neq\ (A_j,B_j) $
 
### Sample Explanation 1

条件を満たす $ P $ は $ (4,1,2,3),(4,2,1,3) $ の $ 2 $ 個です。

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
6 3
1 4 3
2 5 6
3 4 2```

### 输出

```
8```

## 样例 #3

### 输入

```
20 17
9 16 13
5 14 20
15 20 14
5 13 17
18 20 14
14 20 20
6 13 11
12 16 19
2 15 10
6 17 11
7 18 7
8 18 12
8 16 13
6 16 13
2 18 10
9 10 15
7 14 20```

### 输出

```
1209600```

# 题解

## 作者：vegetable_king (赞：12)

[可能更好的阅读体验](https://yjh965.github.io/post/arc176c-max-permutation-ti-jie/)

A > B > C。

从大往小填，思考当前未填的最大值 $x$ 应该填哪儿？考虑 $\max(p_u, p_v) = x$ 的限制的情况。

- 没有该限制，只能填在任意未填孤立点上，$ans \gets ans \times cnt, cnt \gets cnt - 1$。
- 只有一个该限制：

	- 如果该限制两个端点都连了其它点，则无解。

	- 如果该限制只有一个端点连了其它点，就直接填在另一个端点上。

	- 否则任意选一个端点填并删去该限制，另一个端点变为未填孤立点，$ans \gets 2ans, cnt \gets cnt + 1$（这里新增的孤立点是只有以后更小的数字能填的）。

- 有两个或以上的该限制：

	- 如果这些限制的导出子图构成菊花图，就填在中心上，并将所有该限制删去，更新孤立点。

		- 如果该点有连边权更小的边，则无解。（场上的数据是没有这种情况的的，对此有[一组 hack](https://www.luogu.com.cn/discuss/811565))

	- 如果不是，就无解。

发现每种有解的情况都能将该限制删光并直接确立该点的位置，于是做完了，时间复杂度 $O(n + m)$。[代码](https://atcoder.jp/contests/arc176/submissions/52665985)。

---

## 作者：Register_int (赞：11)

有点厉害。

首先建图，边权为 $C_i$。先拉出来一个引理：

- 若有一个点 $u$ 的度数 $d_u\ge2$，那么要么这个点被确定，要么这个点连接的至少 $d_u-1$ 个点被确定。去掉所有确定的点后，每个点的度数至多为 $1$。

考虑这个点 $u$ 的出边权值从小到大排序为 $c_{1\sim d_u}$，那么有以下几种情况：

- 存在一个 $c_i$ 出现多次。由于 $p$ 是个排列，这已经表明了 $p_u=c_i$。若 $c_i$ 不是最小值，那么必然有 $p_u>c_1$，矛盾。若 $c_i$ 是最小值，那么 $p_u$ 已经被确定。此时 $p_u$ 会被去掉。

- $c_i$ 互不相同，那么由于 $u\le c_1$，$c_{2\sim d_u}$ 所对应的点已经全都被确定。此时这 $d_u-1$ 个点都被去掉，$u$ 的度数最多为 $1$。

先把这些预处理出来，再得出每个点的上界 $b_u$。此时所剩的图仅剩两点链或者孤立点。

对于两点链 $(u,v)$，显然有 $b_u,b_v\le c$。若 $b_u<c$ 或 $b_v<c$，则这个链已经被确定了，会变成孤立点。所以两点链只有 $b_u=b_v=c$ 的情况。

情况已经被简化的非常彻底了，最后就是计数部分。将两点链和孤立点按 $b_u$ 从小到大排序，两点链在孤立点之前。动态维护 $\le b_u$ 的可用位置数 $x$，那么：

- 对于两点链，$x<2$ 则直接无解，否则选择一个点为 $b_u$，另一个点在 $1\sim b_u-1$ 中选，方案数为 $2(x-1)$。

- 对于孤立点，$x<1$ 则直接无解，否则方案数显然为 $x$。

乘法原理乘起来即可，时间复杂度 $O(n+m\log m)$。记得特判一车的恶心 corner。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 998244353;

struct edge {
	int v, w;
	edge(int v = 0, int w = 0) : v(v), w(w) {}
	bool operator < (const edge &rhs) const { return w < rhs.w; }
}; vector<edge> g[MAXN];

struct node {
	int u, v, w;
	bool operator < (const node &rhs) const { return w == rhs.w ? v > rhs.v : w < rhs.w; }
} t[MAXN]; int tot;

int n, m, a[MAXN], b[MAXN], d[MAXN], cnt[MAXN];

bool vis[MAXN]; ll ans = 1;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w), d[u]++;
		g[v].emplace_back(u, w), d[v]++;
	}
	for (int i = 1; i <= n; i++) b[i] = n;
	for (int u = 1; u <= n; u++) {
		for (edge x : g[u]) b[u] = min(b[u], x.w);
	}
	for (int u = 1; u <= n; u++) {
		if (g[u].size() <= 1) continue;
		sort(g[u].begin(), g[u].end());
		if (g[u][0].w == g[u][1].w) a[u] = g[u][0].w;
		else b[u] = g[u][0].w; b[g[u][0].v] = min(b[g[u][0].v], g[u][0].w);
		for (int i = 1, v, w; i < g[u].size(); i++) {
			if (g[u][i].w == g[u][0].w) { b[g[u][i].v] = min(b[g[u][i].v], g[u][i].w); continue; }
			if (g[u][i].w == g[u][i - 1].w) return puts("0"), 0;
			v = g[u][i].v, w = g[u][i].w;
			if (a[v] && a[v] != w) return puts("0"), 0; a[v] = w;
		}
	}
	for (int u = 1; u <= n; u++) {
		for (edge x : g[u]) {
			if (a[x.v] > x.w) return puts("0"), 0;
			if (a[x.v] && a[x.v] < x.w || b[x.v] < x.w) {
				if (a[u] && a[u] != x.w || !a[u] && b[u] < x.w) return puts("0"), 0;
				a[u] = x.w, b[x.v] = min(b[x.v], x.w - 1);
			}
		}
	}
	for (int u = 1; u <= n; u++) if (a[u]) for (edge x : g[u]) d[x.v]--;
	for (int u = 1; u <= n; u++) if (a[u]) d[u] = 0;
	for (int u = 1; u <= n; u++) if (a[u] > b[u]) return puts("0"), 0;
	for (int i = 1; i <= n; i++) if (a[i]) cnt[a[i]]++;
	for (int i = 1; i <= n; i++) if (cnt[i] > 1) return puts("0"), 0;
	for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
	for (int u = 1; u <= n; u++) {
		if (!d[u]) continue;
		for (edge x : g[u]) if (x.v > u && d[x.v]) t[++tot] = { u, x.v, x.w }; 
	}
	for (int u = 1; u <= n; u++) if (!a[u] && !d[u]) t[++tot] = { u, 0, b[u] };
	sort(t + 1, t + tot + 1);
	for (int i = 1, x = 0, w; i <= tot; i++) {
		w = t[i].w;
		if (!t[i].v) {
			if (w - cnt[w] - x < 1) return puts("0"), 0;
			ans = ans * (w - cnt[w] - x) % mod, x++;
		} else {
			if (w - cnt[w] - x < 2 || vis[w]) return puts("0"), 0;
			ans = ans * (w - cnt[w] - x - 1) % mod * 2 % mod, x += 2, vis[w] = 1;
		}
	}
	printf("%lld", ans);
}
```

感觉这个做法很蠢，不知道有没有聪明做法。

---

## 作者：sunqihuan (赞：4)

**update 2024.11.28 :根据 xunhuanyihao 的提醒评论，更改了证明的部分。**

# 前言

**注意，此文章为补充题解，主要为自己对于题解的一些思考，以及让这道题更能让初学者理解，可以先看其他题解。**

感谢所有的题解，特别感谢[这篇](https://www.luogu.com.cn/article/wo0odswx)，让我看懂了。~~并借鉴了 TA 的代码~~。

# 题目大意

求出满足以下性质的排列有多少个：

第 $A_i$ 个位置和第 $B_i$ 个位置的较大值为 $C_i$。

答案对 $998244353$ 取模。

# 正文

这题很明显可以想到（算法标签？）图论，经典的思路告诉我们，我们将 $A_i$ 和 $B_i$ 连一条边，边权为 $C_i$。然后经过一顿操作就可以。

其实我们可以想到，$A_i$ 和 $B_i$ 一定有一个数是 $C_i$，另一个数小于 $C_i$。所以我们可以按边权从大到小遍历所有边，这样就可以直接填，不用考虑比它大的情况（因为已经填完了）。

另外，我们定义一个“当前自由元素个数”，大家先按名字感性理解一下，后面会解释。

所以我们以从大到小的边权的顺序遍历所有边，那么有以下情况：

- 如果没有这个边权的边，那么这个点其实是可以在当前“自由元素”中随便选一个的，答案个数乘 $cnt$。

新证明：

> 其实很简单（感性理解不严谨），就是在可以随便选取都满足方案的前提下随便选一个填入。

以下为修改前的老证明：

> 分类讨论所有情况，情况一是我们填了一个数 $x$，而 $x$ 没有出现在边权里，那么这种情况显然成立。情况二是这个 $x$ 在以前出现过，但是以前有出现过那这个元素怎么能是自由的呢，所以这种情况不存在。情况三是在以后出现过，但在以后出现过它的权值，这种情况不存在，因为只有出现过且没有限制的点才是自由点。

可以看到，我们在自由元素中随便选择了一个，所以自由元素 $cnt$ 减一。

- 如果是只有一条边的话，那么我们进行下面的讨论：

如果两个端点的位置都被填过，那么无解。

根据巨佬 xunhuanyihao 的评论中的证明：

> 然后就是两个端点还有度数就无解的证明：因为这里是最大的，如果两个端点都还有度数，那么任意一个点被填目前最大的数时在别的限制条件中就会爆

如果两个端点有一个被填过，那么答案不变。

如果两个端点都没有被填过，那么显然两种选法，即两个端点那个填 $x$，另一个端点填 $x$。但是显然这样会使得自由点的个数减一。

- 如果有两条及以上的边的话，那么只有以一个点为中心，放射状的连出去边（菊花图）才有解，因为如果成环则会出现矛盾，而放射状的连边知道了中间的值，就可以递推填出外面的点。我们选两条边，如果两条边的起点和终点有相同的话，那么这个相同的点就是待定菊花图的中心，接着判断无解和是否是菊花图即可。注意，在求解的过程中，要实时增加自由点的个数。


# 实现&代码

按上面的模拟即可，这里有一个技巧，把边的权值 $C_i$ 当成下标存储，方便查找，把起点和终点存在里面就行。

**代码：**

把上述巨佬的代码改成了```C++14```版本（去掉```auto```，改了其他的一些小地方）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=200005;
int n,m,d[N],ans=1,cnt;
vector<pair<int, int> >e[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	while(m--) {
		int u,v,w;
		cin>>u>>v>>w;
		e[w].push_back({u,v});
		d[u]++;
		d[v]++;
	}
	for(int i=1; i<=n; i++)cnt+=!d[i];
	for(int i=n; i>=1; i--) {
		if(e[i].empty()) {
			if(!cnt) {
				ans=0;
				break;
			}
			ans=1ll*ans*cnt--%mod;
		}
		if(e[i].size() == 1) {
			int u=e[i][0].first;
			int v=e[i][0].second;
			d[u]--;
			d[v]--;
			if(d[u] && d[v]) {
				ans=0;
				break;
			}
			if(!d[u] && !d[v]) {
				ans=ans*2%mod;
				cnt++;
			}
		}
		if(e[i].size()>=2) {
			int tmp=0;
			int u1=e[i][0].first;
			int v1=e[i][0].second;
			int u2=e[i][1].first;
			int v2=e[i][1].second;
			if(u1==u2 || u1==v2) tmp=u1;
			if(v1==u2 || v1==v2) tmp=v1;
			if(!tmp) {
				ans=0;
				break;
			}
			for(int j=0; j<e[i].size(); j++) {
				int x=e[i][j].first;
				int y=e[i][j].second;
				if (x!=tmp && y!=tmp) ans=0;
			}
			if(!ans) break;
			for(int j=0; j<e[i].size(); j++) {
				int x=e[i][j].first,y=e[i][j].second;
				if (x==tmp) swap(x,y);
				if (!--d[x]) cnt++;
			}
			d[tmp]=0;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：gan1234 (赞：2)

### 性质

考虑 $\max(P_{a_i},P_{b_i})=c_i$ 的这个限制，意味着 $P_{a_i}$ 和 $P_{b_i}$ 当中一定有一个等于 $c_i$。

当一个位置 $x$ 同时有多个此类限制时，我们发现这个位置最大也只能等于限制中最小的 $c_i$。

而如果 $x$ 一定不等于限制中的 $c_i$，那么只能是另一位置是 $c_i$ 了，我们就确定了这些位置的值。

我们像这样子将所有能确定的值都确定完后，发现剩下的限制都是独立的，也就是不存在两个限制同时关于一个位置。

### 做法

这样就是好做的了。

剩下的限制有两种情况：

- 只有一个位置的值确定，另一个不确定。
- 两个都不确定。

这两种情况是等价的，对于第二种情况，我们可以钦定一个位置等于 $c_i$，然后就转化为第一种情况。两种钦定方案，结果乘上 $2$ 即可。

对于第一种情况，我们将其看作是要求排列的某些位置的值小于 $c_i$，对其计数。

将这些 $c_i$ 从小到大排序，枚举依次计算方案并相乘，考虑到第 $i$ 个位置时，算出 $1$ 到 $c_i-1$ 里还剩下 $k$ 个数可以选，直接将答案乘上 $k$ 即可。

对于没有任何限制的位置，可以用剩下的数任意排列，因此再乘上剩下的位置数量的阶乘即可。

---

## 作者：TernaryTree (赞：2)

考虑对限制建一张图理解：$a_i$ 与 $b_i$ 连边权 $c_i$ 的边。

按边权从小到大考虑。假设当前枚举的边权为 $i$，分类讨论：

- 若边权为 $i$ 的边 $\ge 2$ 条：
  - 若所有这样的边不存在公共点 $u$：由于 $i$ 在排列中仅出现一次，无解。
  - 否则存在：首先一定有 $p_u=i$。
    - 若 $u$ 之前被访问过：说明 $p_u\lt i$，矛盾，无解。
    - 对所有边权为 $i$ 的边两端点中非 $u$ 的点 $v$，若未被访问过，标记其上界 $q_v=i$。
- 否则只有一条这样的边。
  - 若两端点都被访问过：说明 $p_u,p_v\lt i$，而 $\max(p_u,p_v)=i$，矛盾，无解。
  - 若恰有一个端点被访问：另一个端点权值一定为 $i$。
  - 若都未被访问：两端点等价，其一为 $i$，另一个上界为 $i$，并且可以交换。令答案翻倍，并标记 $p_u=q_v=i$。
  
在每次枚举最后将所有当前边的端点打上访问过的标记。

最后我们得到了一个数组 $p$ 表示已经确定的位置，$q$ 表示一些未确定位置的上界。若 $i$ 最终仍未被访问，则令 $q_i=n$。这样一来每个 $i$，在 $p_i,q_i$ 中恰有一个非 $0$。我们只需要记录那些 $p_i$ 为 $0$ 的有多少种填法：按 $q_i$ 升序排序，动态维护当前可选多少个数，乘上去即可。

记得特判不能存在边权为 $1$ 的边。

[Code](https://www.luogu.com.cn/paste/uq2v3v8a)。

---

## 作者：dengchengyu (赞：1)

### arc176_c Max Permutation

题目大意：求有多少个排列，满足 $m$ 个限制形如 $\max(P_{a_i},P_{b_i})=c_i$。

这一题的 $\max(P_a,P_b)=c$ 其实就是要求 $a,b$ 其中一个**等于** $c$，另一个**小于** $c$。

我们把它当做一条边 $(a,b,c)$。
有一些确定点权的方法：

* 如果有多个边权相同的边，首先它们必须有一个公共点，不然无解。然后这个公共点一定取这个边权。
* 如果我们已经确定 $(u,v,w)$ 中 $u$ 的点权 $val_u$ 且 $val_u\ne w$，则 $val_v=w$。
* 考虑如果一个点 $u$ 有多条边，那么这个点的值要小于等于所有边权的最小值 $M$。
  那么对于其它边权大于 $M$ 的边 $(u,v,w)$，$val_u$ 就不能等于 $w$ 了，则 $val_v$ 的值就确定为 $w$ 了。

我们可以跑 dfs 完成上述过程。

之后剩下的边没有公共点，只有两种情况：

* 有一个点已确定。
* 两个点都没确定。

对于第二种情况可以钦定其中一个点等于边权，答案数乘 2，就转化成了第一种情况。

那么现在的问题就是每个点 $x$，要小于一个权值 $v_x$。

枚举权值 $i$，设 $v_x=i$ 的点有 $cnt$ 个，小于 $i$ 的位置中还空了 $s$ 个，则答案乘上 $\Large\binom {s} {cnt}$，预处理阶乘即可。

最后有一些没有边的点，记它为 $c$ 个，答案还要乘上 $c!$。

时间复杂度 $O(n\log V+m\log m)$，去掉排序和用线性逆元可做到 $O(n+m)$。

AC 代码：

```cpp
const int N=2e5+5;
int n,m;
vector<pair<int,int> > g[N];
void no(){
	cout<<'0';
	exit(0);
}
int ans[N],bz[N],has[N];
void dfs(int x){
	bz[x]=1;
	sort(g[x].begin(),g[x].end(),greater<>());
	if(ans[x]>g[x].back().first)no();
	int cnt=0;
	for(auto i:g[x]){
		if(i.first==g[x].back().first)++cnt;
	}
	if(cnt>=2){
		if(ans[x]&&ans[x]!=g[x].back().first)no();
		ans[x]=g[x].back().first;
	}
	if(ans[x])for(auto i:g[x]){
		if(ans[x]!=i.first){
			if(ans[i.second]&&ans[i.second]!=i.first)no();
			ans[i.second]=i.first;
			if(!bz[i.second])dfs(i.second);
		}
	}
	for(auto i:g[x])if(i.first>g[x].back().first){
		if(ans[i.second]&&ans[i.second]!=i.first)no();
		ans[i.second]=i.first;
		if(!bz[i.second])dfs(i.second);
	}
}
const int mod=998244353;
int cnt[N];
int fac[N];
int pow1(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(ll)x*x%mod)if(y&1)res=(ll)res*x%mod;
	return res;
}
signed main(){
	read(n,m);
	fo(i,1,m){
		int u,v,w;
		read(u,v,w);
		g[u].push_back({w,v});
		g[v].push_back({w,u});
	}
	fo(i,1,n){
		if(g[i].size()>1&&!bz[i])dfs(i);
	}
	fo(i,1,n){
		if(ans[i]&&has[ans[i]])no();
		has[ans[i]]=1;
	}
	int c=0;
	int Ans=1;
	fac[0]=1;
	fo(i,1,n){
		fac[i]=(ll)fac[i-1]*i%mod;
		if(!ans[i]){
			int bz=0;
			for(auto j:g[i]){
				if(!ans[j.second]){
					Ans=Ans*2ll%mod;
					cnt[j.first]++;
					ans[j.second]=-1;
					if(has[j.first])no();
					has[j.first]=1;
					bz=1;
				}
			}
			if(!bz&&g[i].size()){
				int mn=1e9;
				for(auto j:g[i])mn=min(mn,j.first);
				cnt[mn]++;
			}
			if(!bz&&g[i].empty())++c;
		}
	}
	int ls=0;
	fo(i,1,n){
		if(cnt[i]){
			if(cnt[i]>ls)no();
			Ans=(ll)Ans*fac[ls]%mod*pow1((ll)fac[ls-cnt[i]]%mod,mod-2)%mod;
			ls-=cnt[i];
		}
		ls+=!has[i];
	}
	write((ll)Ans*fac[c]%mod);
	return 0;
}
```

---

## 作者：SJZ2010 (赞：1)

感觉别的题解没有写如何观察出所谓引理的，因此我来写下我作为一个蒟蒻的心路历程。

首先看到题我们肯定要观察。经过简单的观察我们发现根据条件可以确定一些位置的取值范围，当然怎么样个范围我们还不知道。

然后我们会想，$\max(A_i,B_i)=C_i$，表明 $P_{A_i}$ 与 $P_{B_i}$ 中有一个 $< C_i$，另一个 $=C_i$。这似乎让题目简单了一些。

为了方便思考，我们先把 $A_i, B_i$ 之间的关系当作图的边。边权即是 $C_i$。

但我们随即也会考虑到一个较复杂的情况：假如 $u$ 向外连了一堆边，又该如何处理。这反映了做题的一个技巧即按照复杂情况分类思考。

那么，我们可以通过假设 $u$ 取到某条边的权值，别的能否取到，发现：

- 如果 $u$ 确定了，那么旁边的 $v$ 的范围或是值也确定了。$u$ 确定的条件是别的点把它确定了或与它相连的边中有边权一样的。

- 如果 $u$ 不确定，那么除了与它相连的边权最短的点，别的点都可以确定。

这可以模拟样例想明白。具体见代码。

最后是计数部分。很显然我们从小往大计算答案。注意要先把必须填的填上。再计算之前只求出一个范围的情况。

[AC.](https://atcoder.jp/contests/arc176/submissions/56474346)

---

## 作者：未来姚班zyl (赞：1)

感觉 B<C<A。这题送我上黄。

## 题目大意

有一个长度为 $n$ 的排列 $P$ 和 $m$ 条性质，每一条性质形如 $\max(P_i,P_j)=w$。对满足所有条件的 $P$ 计数。

## 题目分析

首先限制相当于 $P_i\le w$ 且 $P_j\le w$，我们先对每个 $i$ 求出 $lim_i$ 表示 $i$ 可能取到的最大值。

然后考虑限制的另一个点：$P_i,P_j$ 中有一个数等于 $w$。

首先如果 $lim_i$ 和 $lim_j$ 都小于 $w$，则无解。

否则，如果其中一个 $lim\neq w$，则另一个一定是 $w$。

否则，可能是其中的一个。

还有一个特殊情况：多个限制的 $w$ 相同，则这些限制必须形如：$\max(P_i,P_j)=w,\max(P_i,P_k)=w\dots$ 即需要有一个公共的位置，且这个公共位置的取值就是 $w$。

这样下来每个值 $w$ 有三种状态：已经被分配了，需要分配到两个中的一个，可以被自由分配。而每个位置只有 $P_i\le lim_i$ 与已被分配两种状态。已被分配可以忽视，剩下的直接按照取值从小到大扫，维护 $w\le i$ 且还未分配的 $w$ 的数量，以及 $lim_x=i$ 的 $x$ 的数量，模拟分配，为答案乘上对应的系数即可。

复杂度 $O(n)$，当然排序 $O(n\log n)$ 之后写起来更方便。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,M=4e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,fac[N],iv[N];
struct node{
	int a,b,k;
}a[N];
inline void prep(){
	fac[0]=1;
	rep(i,1,N-5)fac[i]=mul(fac[i-1],i);
	iv[N-5]=INV(fac[N-5]);
	per(i,N-6,0)iv[i]=mul(iv[i+1],i+1);
}
inline int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return mul(fac[x],mul(iv[y],iv[x-y]));
}
inline int A(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return mul(fac[x],iv[x-y]);
}
int val[N],ct[N];
inline void add_(int a,int b,int c){
	val[a]=min(val[a],c);
}
inline bool cmp(node a,node b){
	return a.k<b.k;
}
bool vis[N],v[N],vs[N];
inline void Main(){
	n=read(),m=read();
	repn(i)val[i]=n;
	repm(i)a[i].a=read(),a[i].b=read(),a[i].k=read(),add_(a[i].a,a[i].b,a[i].k),add_(a[i].b,a[i].a,a[i].k);
	sort(a+1,a+m+1,cmp);
	repm(i){
		if(i<m&&a[i].k==a[i+1].k){
			vis[a[i].k]=1;
			if(a[i].a==a[i+1].a||a[i].a==a[i+1].b){
				if(val[a[i].a]==a[i].k)v[a[i].a]=1;
				else return puts("0"),void();
			}
			else if(a[i].b==a[i+1].a||a[i].b==a[i+1].b){
				if(val[a[i].b]==a[i].k)v[a[i].b]=1;
				else return puts("0"),void();
			}
			else return puts("0"),void();
			i++;
		}else {
			//cerr<<val[a[i].a]<<' '<<val[a[i].b]<<'\n';
			if(val[a[i].a]<a[i].k&&val[a[i].b]<a[i].k)return puts("0"),void();
			if(val[a[i].a]<a[i].k)v[a[i].b]=1,vis[a[i].k]=1;
			else if(val[a[i].b]<a[i].k)v[a[i].a]=1,vis[a[i].k]=1;
			else vs[a[i].k]=1;
		}
	}
	repn(i)ct[val[i]]++;
	int tot=0,cnt=0;//tot  还未分配的数的个数  cnt ：等待分配的数的个数 
	int ans=1;
	repn(i){
		cnt=ct[i];
		if(!vis[i]&&!vs[i]){
			tot++;
		}else if(vis[i]){//已经被钦定了 
			cnt--;
		} 
		else {
			cnt--;Mul(ans,2);
		}
		if(cnt>tot)return puts("0"),void();
		Mul(ans,A(tot,cnt)),tot-=cnt;
	} 
	cout <<ans;
}
signed main(){
	prep();
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：Jsxts_ (赞：1)

写得最抽象的一篇题解。

首先对于一个点，若其有权值相同的出边，则 它的权值 $w$ 就已经知道了，进而与其连着权值不为 $w$ 的边对应的点的权值也知道了，而连着权值为 $w$ 的边的点 $u$ 则获得了一个限制：$p_u<w$，记 $mn_u$ 表示 $u$ 已经得到的限制为：$p_u\le mn_u$。上述过程可以用队列模拟出。其中也包含着一些简单的是否无解的特判。

接下来，对于相互不知道点权的点建边。对于每个连通块，对其边数进行讨论（此时每个连通块的边权肯定各不相同，否则也无解）：

- 边数 $\ge$ 点数：若 $>$ 显然无解，若 $=$ 的话，每个点权会恰好对应一个边权，但是容易发现一个结论：一个点的点权必须恰好等于其最小的出边，故容易证明此时没有解。

- 边数 $=$ 点数 $-1$：即其中恰好有一个点不为边中出现的边权（称其为关键点）。还是由上面的结论，我们发现：若存在 $u,v$，满足 $u$ 最小边指向 $v$ 且 $v$ 最小边指向 $u$，那么其中必有一个是关键点。而对于一棵树，这样的对总是存在的（考虑从某个点出发一直沿最小边走，最后一定会折返）。所以，我们找到一个这样的对，然后钦定其中某个是关键点，再 dfs 整个树看其它点是否合法（其它点的点权已经确定）。

不过，对于剩下的点的方案数还需要一些讨论。剩下的点，我们可以看成是：有些数是可选的，然后需要为某些点定一个权值，并且每个点有个形如 $p_i\le w$（记为 $mn2_i$） 的限制。这个只需要按 $mn2_i$ 从小到大考虑即可。

对于一个关键点对 $(u,v)$ 来说：能成为关键点还需要看 $mn_u,mn_v$ 的限制是否满足：$u$ 能是关键点首先要满足 $mn_v\ge w$，$v$ 同理（因为另一个被钦定成 $w$）。

- 若 $mn_u\ge w,mn_v\ge w$，则将方案数乘 $2$，并加入一个点满足 $p_i\le w$。

- 若只有一个满足（记为 $v$），则只加入一个点，限制为 $p_i\le mn_u$。

- 若都不满足则无解。

对于单点，则加入限制为 $p_i\le mn_i$ 的点。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 5e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
const int mod = 998244353;
int getmod(int x) {
	return x - (x >= mod) * mod;
}
int qpow(int a,int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int n,head[N + 10],cnt,m,val[N + 10],mn2[N + 10];
map<pair<int,int>,int> mp;
struct edge {
	int v,w,nxt;
}ed[N * 2 + 10];
void add(int u,int v,int w) {
	ed[++cnt] = {v,w,head[u]};
	head[u] = cnt;
}
vector<pair<int,int> > vc[N + 10];
void add2(int u,int v,int w) {
	vc[u].push_back({v,w});
}
int fa[N + 10],ct[N + 10];
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void join(int x,int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	fa[x] = y, ct[y] += ct[x];
}
int vis[N + 10],ct2[N + 10],fl,cv[N + 10],tp,ans = 1;
pair<int,int> mn[N + 10];
int t[N + 10],tag[N + 10];
void dfs2(int x,int fa) {
	for (auto i : vc[x]) {
		int v = i.x,w = i.y;
		if (v == fa) continue;
		if (mn[x].y == v && mn[v].y == x) {
			if (fl) puts("0"), exit(0);
			fl = 1;
			tp = x;
			int ct = (mn2[x] >= w) + (mn2[v] >= w);
			if (!ct) puts("0"), exit(0);
			else if (ct == 1) t[min(mn2[x],mn2[v])] ++, tp = mn2[x] < mn2[v] ? x : v;
			else ans = 1ll * ans * ct % mod, t[w - 1] ++;
		}
		dfs2(v,x);
	}
}
void dfs(int x,int fa) {
	for (auto i : vc[x]) {
		int v = i.x,w = i.y;
		if (v == fa) continue;
		val[v] = w;
		if (x != tp && max(val[x],val[v]) != val[v]) {
			puts("0"), exit(0);
		}
		dfs(v,x);
	}
}
int main() {
	n = read(),m = read();
	for (int i = 1;i <= n;i ++ ) mn2[i] = inf, fa[i] = i;
	for (int i = 1;i <= m;i ++ ) {
		int u = read(),v = read(),w = read();
		add(u,v,w), add(v,u,w);
		if (w == 1) puts("0"), exit(0);
		if (mp[{u,w}]) {
			if (val[u] && val[u] != w) {
				puts("0");
				exit(0);
			}
			else if (!val[u]) {
				val[u] = w;
				tag[u] = 1;
			}
		}
		else if (mp[{v,w}]) {
			if (val[v] && val[v] != w) {
				puts("0");
				exit(0);
			}
			else if (!val[v]) {
				val[v] = w;
				tag[v] = 1;
			}
		}
		else {
			mp[{u,w}] = v, mp[{v,w}] = u;
			if (cv[w]) puts("0"), exit(0);
		}
		cv[w] = 1;
	}
	queue<int> q;
	for (int i = 1;i <= n;i ++ ) if (tag[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front();q.pop();
		for (int i = head[u];i;i = ed[i].nxt) {
			int v = ed[i].v;
			if (ed[i].w == val[u]) {
				mn2[v] = min(mn2[v],val[u] - 1);
				continue;
			}
			if (ed[i].w < val[u] || (val[v] && max(val[u],val[v]) != ed[i].w)) puts("0"), exit(0);
			if (!val[v]) {
				val[v] = ed[i].w;
				q.push(v);
			}
		}
	}
	for (int i = 1;i <= n;i ++ ) mn[i] = {inf,inf};
	for (int i = 1;i <= n;i ++ ) {
		if (val[i]) continue;
		for (int j = head[i];j;j = ed[j].nxt) {
			int v = ed[j].v;
			if (val[v]) continue;
			add2(i,v,ed[j].w);
			join(i,v);
			ct[find(i)] ++;
			mn[i] = min(mn[i],{ed[j].w,v});
		}
	}
	for (int i = 1;i <= n;i ++ ) ct2[find(i)] ++;
	for (int i = 1;i <= n;i ++ ) {
		if (find(i) != i || val[i]) continue;
		if (ct[i] / 2 == ct2[i]) {
			puts("0");
			exit(0);
		}
		if (ct2[i] == 1) {
			t[min(n,mn2[i])] ++;
			continue;
		}
		fl = 0, tp = 0;
		dfs2(i,0);
		dfs(tp,0);
	}
	if (t[0]) puts("0"), exit(0);
	int ct = 0;
	for (int i = 1;i <= n;i ++ ) {
		if (!cv[i]) ct ++;
		while (t[i] -- ) ans = 1ll * ans * ct % mod, ct --;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

转化题意后即：
- 每个点 $i$，均有一个限制 $p_i\leq z_i$；
- 有 $m$ 条限制要求 $p_{a_i}=c_i\vee p_{b_i}=c_i$。

考虑在值域上从大到小遍历，遍历到 $x$ 时，将 $z_i=x$ 的 $i$ 加入备选集合，特殊处理有限制的 $x$，由于限制涉及到的点一定满足 $z_i=x$，所以不需要考虑其对备选集合有特殊影响。
## 代码
```cpp
#ifdef LOCAL
#include "stdafx.h"
#else
#include <bits/stdc++.h>
#define IL inline
#define LL long long
#define eb emplace_back
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
using namespace std;

using vi = vector<int>;
#endif

constexpr int P = 998244353;

int main () {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> u(n, n - 1);
  vector<array<int, 2>> cand(n, {-1, -1});
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    --c;
    u[a] = min(u[a], c);
    u[b] = min(u[b], c);
    if (cand[c][0] < 0) {
      cand[c] = {a, b};
    } else {
      if (cand[c][0] == a || cand[c][0] == b) {
        cand[c][1] = -1;
      } else if (cand[c][1] == a || cand[c][1] == b) {
        cand[c][0] = cand[c][1];
        cand[c][1] = -1;
      } else {
        cout << "0\n";
        return 0;
      }
    }
  }
  vector<int> d(n);
  for (int i = 0; i < n; i++) {
    ++d[u[i]];
  }
  int ans = 1, all = 0;
  for (int i = n - 1; ~i; i--) {
    all += d[i];
    bool found = false;
    int c = 0;
    for (int j = 0; j < 2; j++) {
      if (~cand[i][j]) {
        found = true;
        c += u[cand[i][j]] == i;
      }
    }
    if (found) {
      ans = (LL)ans * c % P;
    } else {
      ans = (LL)ans * all % P;
    }
    --all;
  }
  cout << ans << '\n';
}
```

---

