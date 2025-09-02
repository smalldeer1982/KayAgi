# [AGC059B] Arrange Your Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc059/tasks/agc059_b

あなたは、色 $ C_1,\ C_2,\ \ldots,\ C_N $ の $ N $ 個のボールを持っています。 ここで、すべての色は $ 1 $ 以上 $ N $ 以下の整数により表されます。 あなたは、これらのボールを円周上に並べようとしています。その後、色のペア $ (X,\ Y) $ であって、$ X\ <\ Y $ であり、色 $ X $ と $ Y $ の二つの隣接するボールが存在するようなペアの個数を数えます。

そのようなペアの個数を最小化する配置を求めてください。そのような配置が多数存在する場合は、そのうちのいずれかを求めてください。

例えば、色 $ 1,\ 1,\ 2,\ 3 $ のボールについて、$ 1,\ 1,\ 2,\ 3 $ と並べると、$ (1,\ 2),\ (2,\ 3),\ (1,\ 3) $ という $ 3 $ つのペアが現れます。$ 1,\ 2,\ 1,\ 3 $ と並べると、現れるペアは $ (1,\ 2),\ (1,\ 3) $ の $ 2 $ つのみです。

各入力ファイルについて、$ T $ 個のテストケースを解いてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 5\ \cdot\ 10^4 $
- $ 3\ \le\ N\ \le\ 2\ \cdot\ 10^5 $
- $ 1\ \le\ C_i\ \le\ N $
- 各入力ファイル内の $ N $ の総和は $ 2\cdot\ 10^5 $ を超えない。
- 入力中のすべての値は整数である。

## 样例 #1

### 输入

```
3
3
1 2 3
4
1 2 1 3
5
2 2 5 3 3```

### 输出

```
1 2 3 
2 1 3 1 
3 3 2 5 2```

# 题解

## 作者：junxis (赞：2)

# Perface
Namomo Winter Camp Div.1 Day1：构造专项训练。
# Analysis
令 $m$ 为不同的颜色种类个数。

注意到答案显然有上界 $m$。给出构造：排序，首尾相接。

将每种颜色抽象成一个点，由于连成了一个环，那么这些点之间必然联通，那么最优的情形便是在环上相邻颜色间连边后形成一个树形结构。此时，答案便为 $(m-1)$。

难点在于，如何给出上述情形的构造，或判定其不存在。

如下图：![](https://cdn.luogu.com.cn/upload/image_hosting/ayqhfome.png)

红色部分为树。我们只需延蓝色部分所画的轨迹，将沿途经过的颜色输出即可，容易发现，一个颜色被输出的次数（由绿色标出）即为其度数。

所以，每个点的度数不能超过其出现次数（无需恰好等于，多余部分在一处重复输出即可），我们只需再此条件下构造出这棵树即可。

显然，我们只需每次选度数最小的，连向较大的即可。

实质上是一层层确定叶子，只要保证叶子不连向叶子即可。

最后，dfs 模拟上图蓝色轨迹即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod=1000000007;
int rnd(int x) { return mrand() % x; }
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for (;b;b>>=1) { if (b&1) res=res*a%mod; a=a*a%mod;} return res;}
ll gcd(ll a, ll b) {return b?gcd(b,a%b):a;}
// head

const int N = 201000;
int n, ext[N];
VI e[N];

void solve() {
	scanf("%d", &n);
	map<int, int> cnt;
	rep(i,1,n+1) {
		int x;
		scanf("%d", &x);
		cnt[x] += 1;
		e[i].clear();
	}
	int m = SZ(cnt);
	set<PII> st;
	for (auto [col, deg] : cnt) st.insert({deg, col});
	rep(i,1,m) {
		auto u = *st.begin(), v = *st.rbegin();
		if (u.fi <= 0 || v.fi <= 0) {
			for (auto [col, deg] : cnt) while (deg--) printf("%d ", col);
			puts("");
			return;
		} // 度数太小，无法构造出树
		st.erase(u); st.erase(v);
		e[u.se].pb(v.se); e[v.se].pb(u.se);
		ext[u.se] = u.fi - 1;  // 多余的度数
		st.insert({v.fi - 1, v.se});
	}
	auto [deg, root] = *st.begin();
	ext[root] = deg;
	VI ans;
	function<void(int, int)> dfs = [&](int u, int f) {
		ans.pb(u);
		while (ext[u]--) ans.pb(u);
		for (auto v : e[u]) if (v != f) {
			dfs(v, u);
			ans.pb(u);
		}
	};
	dfs(root, 0);
	ans.pop_back(); // 最后回到起点多加了一次
	for (auto c : ans) printf("%d ", c); puts("");
}

int main() {
	int _;
	for (scanf("%d", &_); _; _--) {
		solve();
	}
}
```

---

## 作者：ღꦿ࿐ (赞：2)

按顺序相同颜色的球一段一段放下去，这样每种颜色产生一次相邻的贡献，答案是 颜色数 $c$ 。 

就像 a bb cc dd ee (- a) 就是 $5$ 种颜色。

也容易发现答案不可能小于 $c - 1$ ，这样总存在两种颜色之间不能到达。

如何构造答案为 $c-1$ 的情况？ 

为最小化不同颜色的相邻数，我们要尽可能利用已经有的相邻，使这种相邻出现两次。

样例 ``3 3 2 5 2`` 给了我们一种灵感：让一个球两边的颜色相同。

前面举的例子中  a bb cc dd ee (- a) 答案是 $5$ ， 考虑避免 e 和 a 颜色不同， 我们就需要在中间放入 b 使得它是已经与 a 相邻过的球，同理放入 c ， d  ，最后形成的就是 a b c d ee d c b (-a) ，答案为 $4$。

手玩一下会发现一个例子 a b a c a d a e a f ，用一个字母把其它字母岔开。

构造方式就显而易见了：

称只出现一次的字母集合为 $S$ , 出现更多次的集合为 $T$ 。

若 $S$ 非空，从 $S$ 中取出元素放入环。

若 $T$ 非空，从 $T$ 中取出两个相同元素放在之前的两边，若还有还有该元素，重复以下操作：

若 $S$ 非空，从 $S$ 中取出元素放入环的某侧。

从 $T$ 中取出元素放在同侧。

直至 $T$ 为空。

此时 $|S|\leq 1$ 则答案为 $k - 1$，直接放入即可。

否则答案为 $k$ ，排序或直接放入均可。

结论 : $\sum_{a\in T} Cnt_a - 2
|T| + 2\geq |S|$ 时答案为 $k - 1$，否则为 $k$。

构造用一个 deque 可以简单地实现，时间复杂度 $O(n)$



---

## 作者：enucai (赞：0)

## B - Arrange Your Balls

我们令出现过的颜色种类数为 $m$，答案的上界是 $m$（直接排序即可），下界是 $m-1$，证明见下：

- 我们吧每种颜色看作一个点，由于要构成一个环，所有所有的点一定是联通的，每条边都会对答案有 $1$ 的贡献，所以最有情况是一棵树，此时答案为 $m-1$。

于是我们只要考虑能否构造出一棵树即可。每种颜色的出现次数代表了这种颜色在树上度数的上界（度数不够可以原地跳）。

只要最多边数 $\ge m-1$，一定能构造出来。考虑将所有点按度数从大到小排序，然后维护两个指针从右往左扫，左指针表示最右边的剩余度数 $\not=1$ 的节点，不行了就往左移，拿 $1$ 的度数用于连向父亲。然后 dfs 整棵树即可。

提交记录：[link](https://atcoder.jp/contests/agc059/submissions/37026547)。

---

