# Points Movement

## 题目描述

There are $ n $ points and $ m $ segments on the coordinate line. The initial coordinate of the $ i $ -th point is $ a_i $ . The endpoints of the $ j $ -th segment are $ l_j $ and $ r_j $ — left and right endpoints, respectively.

You can move the points. In one move you can move any point from its current coordinate $ x $ to the coordinate $ x - 1 $ or the coordinate $ x + 1 $ . The cost of this move is $ 1 $ .

You should move the points in such a way that each segment is visited by at least one point. A point visits the segment $ [l, r] $ if there is a moment when its coordinate was on the segment $ [l, r] $ (including endpoints).

You should find the minimal possible total cost of all moves such that all segments are visited.

## 说明/提示

In the first test case the points can be moved as follows:

- Move the second point from the coordinate $ 6 $ to the coordinate $ 5 $ .
- Move the third point from the coordinate $ 14 $ to the coordinate $ 13 $ .
- Move the fourth point from the coordinate $ 18 $ to the coordinate $ 17 $ .
- Move the third point from the coordinate $ 13 $ to the coordinate $ 12 $ .
- Move the fourth point from the coordinate $ 17 $ to the coordinate $ 16 $ .

The total cost of moves is $ 5 $ . It is easy to see, that all segments are visited by these movements. For example, the tenth segment ( $ [7, 13] $ ) is visited after the second move by the third point.

Here is the image that describes the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566F/fb3ae267381ee4489ed15f996142ccf4215128ee.png)

## 样例 #1

### 输入

```
2
4 11
2 6 14 18
0 3
4 5
11 15
3 5
10 13
16 16
1 4
8 12
17 19
7 13
14 19
4 12
-9 -16 12 3
-20 -18
-14 -13
-10 -7
-3 -1
0 4
6 11
7 9
8 10
13 15
14 18
16 17
18 19```

### 输出

```
5
22```

# 题解

## 作者：forest114514 (赞：6)

### CF1566F Points Movement

老套路了，线段只有相交没有包含，包含的只需满足较小的那条就行了，这样线段的端点就单增。

当然，现在已经有点被包含的线段也不用算了！

这样就只剩一堆单调的线段和一堆点交替出现，我们加两个虚点坐标为 $\pm inf$，方便算一点。

我们可以花费 $1$ 的代价移动某个点，最终使得每条线段上都有曾有点经过。

一个点的走法有四种：

1. 只向左走
2. 只向右走
3. 向左走一段，原路返回后向右走
4. 向右有一段，原路返回后向左走

但其实只用考虑情况 3,4 因为情况 1,2 等价于向反方向走了长度为 $0$ 的一段再折回。

更一般，这两种情况其实可以一起取 $\min$。

如果我们记 $f_{i,j}$ 为考虑到第 $i$ 个点，向右最远走到了线段 $j$ 的最少操作数，考虑到每一个点向右到下一个点左端的的线段数是连续的一段，所以均摊下只有 $m$ 规模的状态，开一个 $2D$ 的状态太浪费了！

考虑每个点的移动一定在上一个点与这一个点的范围内，所以我们只考虑它一开始向左/右走，同时我们采用贡献转移的思路，将往右走的贡献”送“给右端的点。

记 $f_{i,0/1}$ 为考虑到第 $i$ 个点，一开始走的方向为左/右的最小操作次数，我们枚举上一个点向右走到的线段位置，则有状态转移方程：
$$
f_{i,0}=\min\limits_{k\And l_k,r_k\in(a_{i-1,a_i})}\min{\{f_{i-1,0}+dis(a_{i-1},l_{k-1})+2\times dis(r_k,a_i),f_{i-1,1}+2\times dis(a_{i-1},l_{-1})+2\times dis(r_k,a_i)\}}
$$

$$
f_{i,1}=\min\limits_{k\And l_k,r_k\in(a_{i-1,a_i})}\min{\{f_{i-1,0}+dis(a_{i-1},l_{k-1})+ dis(r_k,a_i),f_{i-1,1}+2\times dis(a_{i-1},l_{k-1})+ dis(r_k,a_i)\}}
$$

答案为 $\min{\{f_{n+1,0},f_{n+1,1}\}}$

时间复杂度为 $O(N\log N)$，瓶颈在于给点和线段排序以及一开始的二分判断。

CODE：

```cpp
struct Line{
	int l,r;
};
void solve(){
	int n,m;
	read(n,m);
	LL a[n+10];LL f[n+10][2];
	rep(i,1,n) read(a[i]);
	a[0]=-inf,a[n+1]=inf;
	sort(a,a+2+n);
	vector<Line> b; int l,r;
	repp(i,0,m){
		read(l,r);
		if(lower_bound(a,a+2+n,l)==upper_bound(a,a+2+n,r)) b.pb(Line{l,r});
	}
	auto cmp=[](Line x,Line y){
		return (x.r^y.r)?x.r<y.r:x.l>y.l;
	};
	sort(b.begin(),b.end(),cmp);
	repp(i,1,b.size()){
		if(b[i].l<=b[i-1].l||b[i].r==b[i-1].r){
			b.erase(b.begin()+i);
			--i;
		}
	}
	rep(i,1,n+1) f[i][0]=f[i][1]=INF;
	f[0][0]=f[0][1]=0;
	int now=0;
	auto min=[](LL a,LL b){
		return (a<b)?a:b;
	};	vector<LL> cl,cr;
	rep(i,1,n+1){
		cl.pb(a[i-1]);
		while(now<b.size()&&b[now].r<a[i]){
			cr.pb(b[now].r);
			cl.pb(b[now].l);
			++now;
		}
		cr.pb(a[i]);
		repp(j,0,cl.size()){
			LL disl=cl[j]-a[i-1],disr=a[i]-cr[j];
			f[i][0]=min(f[i][0],f[i-1][0]+disl+2*disr);
			f[i][0]=min(f[i][0],f[i-1][1]+2*disl+2*disr);
			f[i][1]=min(f[i][1],f[i-1][0]+disl+disr );
			f[i][1]=min(f[i][1],f[i-1][1]+2*disl+disr);
		}
		cl.clear(),cr.clear();
	} 
	write(min(f[n+1][1],f[n+1][0]),'\n');
}
```


---

## 作者：tzc_wk (赞：5)

> 摘自我的 [贪心/构造/DP 杂题选做Ⅲ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp3.html) 中的第 $63$ 题

首先踢掉所有完全包含另一个区间的区间，以及已经符合要求（即，区间中存在一个点）的区间，显然如果其他区间都符合要求了，那这些区间一定符合要求了。

不难发现剩余的区间和点一定是一段区间，后面跟着一车点，再一段区间，再一车点，并且这些区间的左右端点一定都是单调递增的。我们再来思考一下一个点的行动轨迹是什么样的，不难发现无非以下两种：先向左走一段然后掉头走到它原来的位置的左侧，或者先向右走一段然后掉头。我们考虑以此为状态设计 DP。设 $dp_{i,0/1}$ 表示已经移动了前 $i$ 个点，第 $i$ 个点先向左走/先向右走的最小代价。转移就套路地拆一下代价，将第 $i$ 个点向左走的代价放在 $dp_i$ 处计算，将走到原位置后向右走的代价放在 $dp_{i+1}$ 处计算，然后枚举上一个点的状态转移即可。时间复杂度 $\Theta(n\log n)$。

```cpp
const int MAXN = 2e5;
const int INF = 0x3f3f3f3f;
const ll INFll = 0x3f3f3f3f3f3f3f3fll;
int n, m, a[MAXN + 5];
pii p[MAXN + 5], pp[MAXN + 5];
ll dp[MAXN + 5][2];
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	a[n + 1] = INF; sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) scanf("%d%d", &p[i].fi, &p[i].se);
	sort(p + 1, p + m + 1, [&](pii lhs, pii rhs) {
		return (lhs.fi ^ rhs.fi) ? (lhs.fi < rhs.fi) : (lhs.se > rhs.se);
	});
	int mn = INF, tmp = m; m = 0;
	for (int i = tmp; i; i--) {
		int nt = lower_bound(a + 1, a + n + 1, p[i].fi) - a;
		if (p[i].fi <= a[nt] && a[nt] <= p[i].se) continue;
		if (p[i].se >= mn) continue;
		pp[++m] = p[i]; chkmin(mn, p[i].se);
	}
	if (!m) return puts("0"), void();
	reverse(pp + 1, pp + m + 1);
//	for (int i = 1; i <= m; i++) printf("[%d, %d]\n", pp[i].fi, pp[i].se);
	for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = INFll;
	ll disL, disR; int l = 1, r = 1;
	disL = (pp[1].se < a[1]) ? (a[1] - pp[1].se) : 0;
	dp[1][0] = disL * 2; dp[1][1] = disL;
	while (r <= m && pp[r].se < a[1]) ++r;
	l = r;
	for (int i = 2; i <= n; i++, l = r) {
		r = l; while (r <= m && pp[r].se < a[i]) ++r;
		for (int j = l; j <= r; j++) {
			disL = (j == l) ? 0 : (pp[j - 1].fi - a[i - 1]);
			disR = (j == r) ? 0 : (a[i] - pp[j].se);
			chkmin(dp[i][0], dp[i - 1][0] + disL + disR * 2);
			chkmin(dp[i][0], dp[i - 1][1] + disL * 2 + disR * 2);
			chkmin(dp[i][1], dp[i - 1][0] + disL + disR);
			chkmin(dp[i][1], dp[i - 1][1] + disL * 2 + disR);
		}
//		printf("DP %d %lld %lld\n", i, dp[i][0], dp[i][1]);
	}
	disR = (pp[m].fi > a[n]) ? (pp[m].fi - a[n]) : 0;
	printf("%lld\n", min(dp[n][0] + disR, dp[n][1] + disR * 2));
}
int main() {
	int qu; scanf("%d", &qu);
	while (qu--) solve();
	return 0;
}
```

---

## 作者：LTb_ (赞：3)

先考虑对这些线段进行一些精简。

显然，区间内已经有点的线段可以被扔掉，完整包含了另一条线段的线段也可以被扔掉。两个过程都可以用二分实现。

观察一下整个画面现在长什么样子：大概是 一堆线段 - 一堆点 - 一堆线段 - 一堆点 这样，并且线段左端点随线段右端点递增而递增。观察一下最优方案应该长什么样子：显然，任意两个点跑过的的位置都不应该存在公共点。

设一个点初始位置为 $x$，跑过的位置为 $[l, r]$ 这个区间，那么这个点造成的花费是 $(r - l) + \min(x-l, r-x)$，变换一下形式就是 $2\min(x-l, r-x) + \max(x-l, r-x)$（其实不一定要做这个变换）。

考虑一个 dp：$dp_{i, j}$ 表示第 $i$ 个点向右跑 visit 了 $j$ 条线段时，前 $i$ 个点的答案。注意这个 dp 状态数是线性的，因为每个点向右一定不会跑过它右边的那个点（一定不优），所以总状态数就是「相邻两点之间线段数的总和」也就是 $m$。

我们设第 $i$ 和第 $i-1$ 个点之间一共有 $t$ 条线段。

有个显然的 $\mathcal O(n^2)$ dp：
$$
dp_{i, j} = \min\limits_{k} (dp_{i-1, k} + 
2\min(\text{dis}_a, \text{dis}_b) + \max(\text{dis}_a, \text{dis}_b))
$$
其中 $\text{dis}_a, \text{dis}_b$ 分别为第 $i$ 个点向左 visit $t-k$ 条线段的花费，和第 $i$ 个点向右 visit $j$ 条线段的花费。注意到 $\text{dis}_a$ 仅与 $i-1$ 和 $k$ 有关，而 $\text{dis}_b$ 仅与 $i$ 和 $j$ 有关。如果没有 $\min$ 和 $\max$ 的问题，就可以直接优化掉。

可以在存储着 $\text{dis}_a$ 的数组中二分 $\text{dis}_b$ 的位置，此位置之前 $\text{dis}_a \le \text{dis}_b$，之后 $\text{dis}_a \ge \text{dis}_b$，用前缀 / 后缀 $\min$ 分别计算着两种贡献就可以优化掉 $k$ 的枚举。时间复杂度 $\mathcal O(n \log n)$。

[并不推荐阅读的代码](https://codeforces.com/contest/1566/submission/132486068)



---

## 作者：Purslane (赞：1)

# Solution

基础贪心题。

分析几个性质：

1. 有用的线段是一组极大的、互不包含的，且不包含任何一个 $a_i$ 的线段的子集。并且很容易排序几次将其求出。
2. 每个 $a_i$ 经过的点的集合一定是一条线段。且最优情况下，所有线段互不相交（有公共点）。
3. 设每条有用的线段左边紧邻的 $a_i$ 为 $Lid_j$，右边紧邻的 $a_i$ 为 $Rid_j$。则 $i$ 一定是被 $Lid_j$ 向右移动覆盖，或者 $Rid_j$ 向左移动覆盖。

有了几条性质，随便 DP 即可，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int T,n,m,a[MAXN],l[MAXN],r[MAXN],dp[MAXN],Lid[MAXN],Rid[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		set<pair<int,int>> s;
		ffor(i,1,n) cin>>a[i];
		ffor(i,1,m) cin>>l[i]>>r[i];
		sort(a+1,a+n+1);
		ffor(i,1,n) s.insert({a[i],i});
		vector<pair<int,int>> seg;
		ffor(i,1,m) {
			auto it=s.lower_bound({l[i],0});
			if(it!=s.end()&&it->first<=r[i]) continue ;
			seg.push_back({l[i],r[i]});
		}
		sort(seg.begin(),seg.end(),[](pair<int,int> A,pair<int,int> B) {
			if(A.second!=B.second) return A.second<B.second;
			return A.first>B.first;
		});
		stack<pair<int,int>> st;
		int lmx=-0x3f3f3f3f3f3f3f3f;
		for(auto pr:seg) {
			if(pr.first<=lmx) continue ;
			lmx=pr.first,st.push(pr);
		}
		m=0;
		while(!st.empty()) ++m,l[m]=st.top().first,r[m]=st.top().second,st.pop();
		reverse(l+1,l+m+1),reverse(r+1,r+m+1);
		if(m==0) {cout<<0<<'\n';continue ;}
		ffor(i,1,m) dp[i]=0x3f3f3f3f3f3f3f3f;
		ffor(i,1,m) {
			Lid[i]=Rid[i]=-1;
			auto it=s.lower_bound({r[i],0});
			if(it!=s.end()) Rid[i]=it->second;
			if(it!=s.begin()) Lid[i]=prev(it)->second;	
		}
		int div=0;
		ffor(i,1,n) {
			while(div<m&&r[div+1]<a[i]) div++;
			int mn1=0x3f3f3f3f3f3f3f3f,mn2=0x3f3f3f3f3f3f3f3f,ov=dp[div];
			roff(j,div,1) {
				if(Rid[j]!=i) break ;
				dp[div]=min(dp[div],dp[j-1]+a[i]-r[j]);
				mn1=min(mn1,dp[j-1]+a[i]-r[j]);
				mn2=min(mn2,dp[j-1]+2*(a[i]-r[j]));
			}
			ffor(j,div+1,m) {
				if(Lid[j]!=i) break ;
				dp[j]=min(dp[j],ov+l[j]-a[i]);
				dp[j]=min(dp[j],mn1+2*(l[j]-a[i]));
				dp[j]=min(dp[j],mn2+l[j]-a[i]);
			}
		}
		cout<<dp[m]<<'\n';
	}
	return 0;
}
```

---

## 作者：Missa (赞：1)

感觉好难。

首先，注意到点不会互相穿过，因为穿过了替换就行，意味着相对顺序不会改变。

那么一个点最多掉头一次，并且一个点的活动范围必须在其左右两个点之间。

这好像已经可以拿来做 dp 的阶段了。设一个点的活动范围为 $[x-l, x+r]$，其中 $x$ 为初始位置，则花费的代价为 $2 \min\{l, r\} + \max\{l, r\}$。

每一条线段都必须被覆盖到。先把没用的线段去掉，再注意到如果有重叠只用满足小的那条线段就可以了。那么现在只关注相邻的两个点和中间的很多条线段，这些线段的左端点和右端点都递增，枚举一个分界，左边的线段用左侧的那个点覆盖，右边的线段用右边的那个点覆盖，也就是可以确定一个点的活动范围了。

那么 dp 时再记一下是否已经有那个 *2 了，枚举相邻的点确定活动范围转移。

感觉用确定范围更直观一些，用是否 *2 来表示也比先走或者先右更好一些。

```cpp
#include <bits/stdc++.h>

using LL = long long;

void solve() {
  int n, m; scanf("%d %d", &n, &m);
  std::vector<int> a(n);
  std::vector<std::pair<int, int>> p(m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (auto &[x, y] : p) scanf("%d %d", &x, &y);
  std::sort(a.begin(), a.end());
  std::sort(p.begin(), p.end(), [&](auto x, auto y) {
    return x.first != y.first ? x.first < y.first : x.second > y.second;
  });
  std::vector<std::pair<int, int>> b;
  int mn = 1e9 + 1;
  for (int i = m - 1; i >= 0; i--) {
    int t = std::lower_bound(a.begin(), a.end(), p[i].first) - a.begin();
    if (p[i].second >= mn) continue;
    if (t != n && p[i].first <= a[t] && a[t] <= p[i].second) continue;
    b.push_back(p[i]), mn = p[i].second;
  }
  std::reverse(b.begin(), b.end());
  m = b.size();
  if (!m) return printf("0\n"), void();
  std::vector<std::vector<LL>> f(n, std::vector<LL>(2, 1e18));
  for (int i = 0, l = 0, r = 0; i < n; i++) {
    l = r;
    while (r < m && b[r].second < a[i]) ++r;
    if (!i) {
      int disl = std::max(a[0] - b[0].second, 0);
      f[i][0] = disl, f[i][1] = 2ll * disl;
      continue;
    }
    for (int j = l; j <= r; j++) {
      int disl = j == l ? 0 : b[j - 1].first - a[i - 1];
      int disr = j == r ? 0 : a[i] - b[j].second;
      f[i][0] = std::min({f[i][0], f[i - 1][1] + disl + disr, f[i - 1][0] + 2ll * disl + disr});
      f[i][1] = std::min({f[i][1], f[i - 1][1] + disl + 2ll * disr, f[i - 1][0] + 2ll * disl + 2ll * disr});
    }
  }
  int disr = std::max(b[m - 1].first - a[n - 1], 0);
  printf("%lld\n", std::min(f[n - 1][0] + 2ll * disr, f[n - 1][1] + disr));
}

int main() {
  int T; scanf("%d", &T); while (T--) {
    solve();
  }
} 
```

---

