# Dynamic TSP Problem

## 题目描述

A 国有 $n$ 个城市被 $n-1$ 条道路连接！这 $n$ 座城市从 $1$ 至 $n$ 编号，其中第 $i$ 座城市有三个值 $A_i$、$B_i$ 以及 $C_i$ 分别表示该城市的繁荣度、利润额和销售额。

你作为一个流浪商人，想要进行环游 A 国的 $m$ 次旅行。第 $i$ 次旅行可以描述为：以 $X$ 元的资金从城市 $S_i$ 以最短距离走到城市 $T_i$，且最终资本需要大于等于 $Y_i$，还有一个参数 $K_i$。你一路破产，一路贸易，一路生花。
* 一路破产：你需要最开始携带 $X$ 元的资金，从城市 $S_i$ 开始出发。
* 一路贸易：**你在途经的所有城市都需要进行贸易，包括出发城市和结束城市。** 假设你刚来到城市 $i$ 拥有资金 $w$ 元，若资本 $w$ 不小于该城市的繁荣度 $A_i$，那么你可以在此获利 $B_i$。否则你会消耗 $C_i$ 元的资金。路途中资金可以小于 $0$。
* 一路生花：抵达城市 $T_i$ 并在城市 $T_i$ 完成贸易后，你希望最后至少有 $Y_i$ 元的资金，且在路途中至少完成 $K_i$ 次获利（即至少有 $K_i$ 个城市满足当前资本不小于该城市的繁荣度 $A_i$）。$Y_i$ 可以小于 $X$，因为你深知破产无关紧要，绕远的路，总有风景。

你需计算 $X$ 的最小值，使得每次旅行都以 $X$ 元资金出发，且最后都至少有 $Y_i$ 元的剩余且获利至少 $K_i$ 次。保证 $K_i$ 小于等于路径长度。



## 说明/提示



**【数据规模与约定】**

**本题开启子任务捆绑测试**。本题自动开启 O2 优化。


* Subtask 1（10 pts）：$n\leq 100$，$m\leq 100$。
* Subtask 2（25 pts）：$n\leq 500$，$m\leq 3000$。
* Subtask 3（10 pts）：$A_i=B_i$，$C_i=0$。
* Subtask 4（10 pts）：$B_i=0$。
* Subtask 5（10 pts）：$C_i=0$。
* Subtask 6（10 pts）：A 国的道路是一条链。
* Subtask 7（25 pts）：$n\leq 500$，$m\leq 2\times 10^5$。

对于所有测试点满足 $n\leq 500$，$m\leq 2\times 10^5$，$0\leq A_i,B_i,C_i\leq 2\times 10^{14}$，$S_i\not= T_i$，$1\leq K_i\leq n$，$1\leq Y_i\leq 10^{17}$。


## 样例 #1

### 输入

```
3 3
2 1
3 1
3 9 0
5 5 0
7 6 7
3 2 4 2
2 1 8 1
3 1 4 1```

### 输出

```
7```

## 样例 #2

### 输入

```
4 5
2 1
3 1
4 3
1 8 5
7 8 6
1 9 2
1 8 0
1 4 8 1
3 2 7 2
3 4 3 1
2 3 9 2
2 4 7 1```

### 输出

```
7```

# 题解

## 作者：Mr_Az (赞：5)

# [P11744 Dynamic TSP Problem](https://www.luogu.com.cn/problem/P11744)

### Algorithm:

二分。

~~好像爆标了？~~

### Solution:

观察到答案具有单调性（你带的钱越多获利的次数越多剩的钱也越多），因此考虑二分答案。

考虑最显然的 $\text{O}(nm\log V)$，遍历每一条路径判断合法性。

观察到 $n$ 和 $m$ 的大小差距十分的大，所以 $m$ 条路径有许多是重复遍历到的。因此我们可以考虑把每一条路径拿 vector 存下来，每次 check 只需要从 $n$ 个点出发，记录起点，当前资金，获利次数，每次走到一个点 $u$ 就查询所有起点到 $u$ 的路径，检查合法性。

每次 check 时间复杂度 $\text{O}(n^2)$，总的时间复杂度 $\text{O}(n^2\log V)$。

### Code:

```cpp
namespace Mr_Az{
	const int N=508,M=2e5+8;
	int T=1;
	int n,m;
	vector<int> e[N];
	struct city{int a,b,c;}a[N];
	struct ask{int y,k;};
	vector<ask> journey[N][N];
	inline bool dfs(int u,int fa,int st,int x,int hl){
		if(x>=a[u].a) x+=a[u].b,hl++;
		else x-=a[u].c;
		if(journey[st][u].size()) for(auto [c,d]:journey[st][u]) if(x<c||hl<d) return 0;
		for(auto v:e[u]) if(v!=fa) if(!dfs(v,u,st,x,hl)) return 0;
		return 1;
	}// u: 当前节点 st: 起点 x: 当前资金 hl: 获利次数
	inline bool check(int x){
		for(rint i=1;i<=n;i++) if(!dfs(i,0,i,x,0)) return 0;
		return 1;
	}
	inline void solve(){
		read(n,m);
		for(rint i=1,u,v;i<n;i++) read(u,v),e[u].pb(v),e[v].pb(u);
		for(rint i=1,A,B,C;i<=n;i++) read(A,B,C),a[i]={A,B,C};
		for(rint i=1,A,B,C,D;i<=m;i++) read(A,B,C,D),journey[A][B].pb({C,D});
        // 由于 n 只有 500，所以直接开个 vector 把所有的旅行记录下来
		int l=0,r=INF,ans=0;
		while(l<r){
			int mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}// 二分答案
		printf("%lld\n",l);
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

---

## 作者：Kingna (赞：4)

出题人题解，很高兴被爆标了。

考虑到 $X$ 满足单调性，则可以二分。我们不需要对每一次旅行都二分一遍，我们只需要求出所有旅行的 max 值。设当前求解到第 $i$ 个旅行，已经对前 $i-1$ 个旅行求出了 $X$ 值。若对第 $i$ 个旅行计算出 $X$ 值是合法的，就不用再二分了，直接跳过。若对第 $i$ 个旅行计算出 $X$ 值不合法，那么再从 $X$ 值开始二分新的 $X$。

不难发现，这样做的复杂度基于前缀最大值数量。给出一个结论：对于长度为 $k$ 的随机排列，前缀最大值的个数是 $O(\log k)$。

**证明：** 如果一个值 $x$ 对前缀最大值产生贡献，那么说明 $x$ 是 $x,x+1,\dots,k-1,k$ 这 $k-x+1$ 个数中第一个数，概率为 $\dfrac{1}{k-x+1}$。则 $\dfrac{1}{1}+\dfrac{1}{2}+\dfrac{1}{3}+\dots+\dfrac{1}{k}=O(\log k)$。

说明我们对 $m$ 次旅行随机打乱一下，则前缀最大值期望为 $O(\log k)$。则只会二分 $\log m$ 次。总复杂度为 $O(n \log m \log V+nm)$。

---

## 作者：_lmh_ (赞：2)

所有限制作用于同一个 $X$，所以只需要对每个 $(S,T)$ 记录 $K$ 和 $Y$ 的最大值，然后二分即可。

判断一个 $X$ 是否可行时固定 $S$，做一遍 `dfs` 之后对所有的 $T$ 进行判断即可。

时间复杂度 $O(n^2\log V+m)$，其中 $V$ 为值域。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=507,M=200007;
ll n,m,ans,a[N],b[N],c[N],cnt[N],val[N],k[N][N],y[N][N];
vector<ll> to[N];
void dfs(int u,int fa){
	for (auto v:to[u]) if (v!=fa){
		if (val[u]>=a[v]){val[v]=val[u]+b[v];cnt[v]=cnt[u]+1;}
		else{val[v]=val[u]-c[v];cnt[v]=cnt[u];}
		dfs(v,u);
	}
}
bool OK(ll x){
	for (int i=1;i<=n;++i){
		if (x>=a[i]){val[i]=x+b[i];cnt[i]=1;}
		else{val[i]=x-c[i];cnt[i]=0;}
		dfs(i,0);
		for (int j=1;j<=n;++j) if (val[j]<y[i][j]||cnt[j]<k[i][j]) return 0;
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for (int u,v,i=1;i<n;++i){
		cin>>u>>v;
		to[u].emplace_back(v);to[v].emplace_back(u);
	}
	for (int i=1;i<=n;++i) cin>>a[i]>>b[i]>>c[i];
	for (ll s,t,Y,K,i=1;i<=m;++i){
		cin>>s>>t>>Y>>K;
		y[s][t]=max(y[s][t],Y);
		k[s][t]=max(k[s][t],K);
	}
	ll l=0,r=1e18,ans=1e18;
	while(l<=r){
		ll mid=l+r>>1;
		if (OK(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：1)

并查巨佬说比 T1 T2 简单。

---
### 题意：
有一个 $N$ 个点的无根树，每个点都有权值 $A_i,B_i,C_i$。

$M$ 次旅行，对于第 $i$ 次形式化为：开始自定一个 $X$，给定 $Y_i,K_i,S_i,T_i$，从起点 $S_i$ 到终点 $T_i$ 的每个点 $u$ 上进行如下操作：若 $X\ge A_u$ 则 $X\leftarrow X+B_u$，否则 $X\leftarrow X-C_u$。

需要找到一个最小的 $X$ 使得对于每个旅行 $i$ 都有：操作完后 $X\ge Y_i$，进行 $X\leftarrow X+B_u$ 操作的次数 $\ge K_i$。

### 思路：

既然题目要求最小了不难证明对于 $X$ 的合法性满足单调性。

于是我们可以二分 $X$。

但是每次 check 时我们不能直接跑每一次旅行，因为每一次旅行有可能给你卡到 $O(N)$。

容易发现起点可能重复，那我们就以每个点为起点跑 dfs，记录下以 $i,j$ 为起点终点最终的 $X$ 以及进行 $X\leftarrow X+B_u$ 操作的次数 $K$。这样一次 check 总共是 $O(N^2+M)$，加上二分总时间复杂度为 $O(N^2\log V)$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, e[1002], h[502], ne[1002], a[502], b[502], c[502], w1[502][502], w2[502][502], idx;
struct node {
	ll s, t, y, k;
}q[200002];
void add(ll x, ll y) {
	e[++ idx] = y, ne[idx] = h[x], h[x] = idx;
}
void dfs(ll x, ll fa, ll rt, ll times, ll money) {
	if (money >= a[x]) money += b[x], times ++;
	else money -= c[x];
	w1[rt][x] = money;
	w2[rt][x] = times;
	for (ll i = h[x]; i; i = ne[i]) {
		ll y = e[i];
		if (y == fa) continue;
		dfs(y, x, rt, times, money); 
	}
}
bool check(ll x) {
	for (ll i = 1; i <= n; i ++ ) dfs(i, i, i, 0, x);
	for (ll i = 1; i <= m; i ++ ) {
		if (w1[q[i].s][q[i].t] < q[i].y || w2[q[i].s][q[i].t] < q[i].k) return 0;
	}
	return 1;
}
int main() {
	cin >> n >> m;
	for (ll u, v, i = 1; i < n; i ++ ) cin >> u >> v, add(u, v), add(v, u);
	for (ll i = 1; i <= n; i ++ ) cin >> a[i] >> b[i] >> c[i]; 
	for (ll i = 1; i <= m; i ++ ) cin >> q[i].s >> q[i].t >> q[i].y >> q[i].k;
	ll l = 0, r = 1e18, ans = 0;
	while (l <= r) {
		ll mid = l + r >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans;
}
```

---

