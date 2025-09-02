# MEX Game 2 (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ t $ , $ m $ and the sum of $ m $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob play yet another game on an array $ a $ of size $ n $ . Alice starts with an empty array $ c $ . Both players take turns playing, with Alice starting first.

On Alice's turn, she picks one element from $ a $ , appends that element to $ c $ , and then deletes it from $ a $ .

On Bob's turn, he picks at most $ k $ elements from $ a $ , and then deletes it from $ a $ .

The game ends when the array $ a $ is empty. Alice's score is defined to be the MEX $ ^\dagger $ of $ c $ . Alice wants to maximize her score while Bob wants to minimize it. Find Alice's final score if both players play optimally.

The array will be given in compressed format. Instead of giving the elements present in the array, we will be giving their frequencies. Formally, you will be given $ m $ , the maximum element in the array, and then $ m + 1 $ integers $ f_0, f_1, \ldots, f_m $ , where $ f_i $ represents the number of times $ i $ occurs in the array $ a $ .

 $ ^\dagger $ The $ \operatorname{MEX} $ (minimum excludant) of an array of integers is defined as the smallest non-negative integer which does not occur in the array. For example:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, the array $ a $ is $ [0, 0, 0, 0, 1, 1, 1, 1, 1] $ . A possible game with a score of $ 2 $ is as follows:

1. Alice chooses the element $ 0 $ . After this move, $ a = [0, 0, 0, 1, 1, 1, 1, 1] $ and $ c=[0] $ .
2. Bob chooses to remove the $ 3 $ elements $ 0 $ , $ 0 $ and $ 1 $ . After this move, $ a = [0, 1, 1, 1, 1] $ and $ c=[0] $ .
3. Alice chooses the element $ 1 $ . After this move, $ a = [0,1,1,1] $ and $ c=[0,1] $ .
4. Bob removes the $ 4 $ remaining elements $ 0 $ , $ 1 $ , $ 1 $ and $ 1 $ . After this move, $ a=[\,] $ and $ c=[0,1] $ .

At the end, $ c=[0,1] $ which has a MEX of $ 2 $ . Note that this is an example game and does not necessarily represent the optimal strategy for both players.

In the second test case, Alice can choose a $ 0 $ in her first turn, guaranteeing that her score is at least $ 1 $ . While Bob can remove all copies of element $ 1 $ in his first turn, thus guaranteeing that Alice's score cannot exceed $ 1 $ . So Alice's score is $ 1 $ if both players play optimally.

## 样例 #1

### 输入

```
5
1 4
4 5
2 1000000000
1000000000 1000000000 1000000000
3 2
2 3 100 1
1 1
2 2
3 1
1 1 1 1```

### 输出

```
2
1
3
2
1```

# 题解

## 作者：Alex_Wei (赞：4)

### [CF1943E1 MEX Game 2 (Easy Version)](https://www.luogu.com.cn/problem/CF1943E1)

只需检查是否无论 Bob 如何操作，Alice 都能取到 $0\sim x$。

固定 $x$，所有 $0\sim x$ 所有数等价，只关心 $f_{0\sim x}$ 形成的可重集。问题等价于给定可重集 $S$，Alice 每次删去一个数，然后 Bob 让可重集剩下的数分别减去总和不超过 $k$ 的若干个值，问 Bob 能否在 Alice 删空可重集之前让可重集出现非正数。

一个关键结论是 Alice 的策略是唯一的：她一定会删去可重集最小的数。因为对于大小相同的可重集 $S$ 和 $S'$，若对于所有 $1\leq i\leq |S|$，$S$ 的排名为 $i$ 的数不小于 $S'$ 的排名为 $i$ 的数，则 $S'$ 对 Alice 显然更优，也就是让 Bob 更难达到目标。

于是我们只需关心 Bob 如何操作，且可以认为 Bob 先手（处理掉 Alice 的第一次操作）。假设 Bob 希望在第 $i$ 次操作的时候让可重集出现非正数，那么他一定不会操作初始排名（从小往大数）大于 $i$ 的数。这个结论很好理解，因为 Bob 在第 $1\leq j\leq i$ 次操作时，只关心最小的 $i - j + 1$ 个数形成的可重集，可以对 $j$ 从 $i$ 到 $1$ 归纳。

设当前可重集为 $s_1 \leq s_2 \leq \cdots \leq s_c$，则 Bob 在让所有数等于 $s_1$ 之前，操作 $s_1$ 是不优的，因为当 $c > 1$ 时，$s_1$  一定会被 Alice 删去，所以让减小 $s_1$ 的值操作在 $s_{2\sim c}$ 上会更好，除非所有 $s_p$ 全部相等，此时操作任何数都等价于操作 $s_1$。于是可以归纳证明，在让 $s_{p + 1\sim c}$ 等于 $s_p$ 之前，操作 $s_p$ 是不优的。我们终于找到了 Bob 的策略。

综上，从小到大枚举 $x$，再枚举 $i$，然后模拟 Bob 的操作并检查即可。

时间复杂度 $\mathcal{O}(\mathrm{poly}(m))$。[代码](https://codeforces.com/contest/1943/submission/251772270)。

---

## 作者：Purslane (赞：4)

# Solution

[学弟](https://www.luogu.com.cn/user/365654)说这是唐题。我寻思着这题我想了一段时间啊，看来不如学弟了。

考虑二分答案，变为判定 $\rm Bob$ 是否存在一种策略可以在 $\rm Alice$ 取某一堆石子之前把这一堆石子取光。

考虑把石子按照大小排序。

非常显然可以看到，$\rm Bob$ 每一次操作不会使某两堆石子的相对大小关系发生改变；$\rm Alice$ 每次必定取最小的石子。

于是假设 $\rm Bob$ 想要撅掉第 $k$ 堆石子（排序后，$k > 1$），那么再第 $1$ 到 $k-1$ 轮，$\rm Bob$ 必定选择不断地从第 $k$ 堆往后给一个连续段减一。当 $\rm Bob$ 无法删掉一个连续段的时候，他会选择删掉这个连续段的前面几个数。

模拟这个过程即可。

用 `set` 维护差分数组显然可以做到 $O(n^2 \log^2 n)$，但是过不了 $\rm Hard \ Version$，所以写了一个非常好写的 $O(n^3 \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=60;
int T,n,m,f[MAXN],g[MAXN],simulate[MAXN];
int get_longest(int rpos) {
	roff(i,rpos,2) if(simulate[i]!=simulate[i-1]) return rpos-i+1;
	return rpos;
}
void del(int l,int r,int op) {
	int rst=m;
	while(rst) {
		int len=min(r-l+1,get_longest(r)),psl=0;
		if(len!=r-l+1) psl=simulate[r-len+1]-simulate[r-len];
		else psl=INT_MAX;
		if(len*psl>=rst) {
			ffor(j,r-len+1,r) simulate[j]-=rst/len;
			ffor(j,r-len+1,r-len+rst%len) simulate[j]--;
			rst=0;
		}
		else {
			ffor(j,r-len+1,r) simulate[j]-=psl;
			rst-=len*psl;	
		}
	}
	return ;
}
int solve(int pos,int op=0) {
	ffor(i,1,n+1) simulate[i]=g[i];
	ffor(i,1,pos-1) del(i+1,pos,op);
	return simulate[pos]<=0;
}
int check(int mex) {
	int len=mex;
	ffor(i,1,len) g[i]=f[i-1];
	sort(g+1,g+len+1);
	ffor(i,2,len) if(solve(i)) return 0;
	return 1;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		ffor(i,0,n) cin>>f[i];
		int ans=0,l=1,r=n+1;
		while(l<=r) {
			int mid=l+r>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

（这种非对称竞技题对我这个 ID5 牢玩家来说还是太简单了）

答案肯定是可二分的。二分后不好直接判定，我们考虑用非对称游戏的一个经典分析方法，即反复代入双方视角。

- Bob：如果对面取走每种元素各一个，那么我被判负。那么我希望钦定一种元素，使得 Alice 取不到。（钦定哪种元素？如果直接钦定最小的那么 Alice 第一次就能取，不好进一步思考，因此代入 Alice）

- Alice：我的目的是取走每类元素至少一个，那么考虑我的其中一步取那个元素？显然没被取走的元素地位是一样的，而越少的越可能被 Bob 取完，因此**无论对面怎么决策，我都应该选最少的取**。（已经知道 Alice 的决策，因此代入 Bob）

- Bob：不妨设我希望 Alice 第 $i$ 次取不到元素，那么把初始序列排序（设为 $s$），我希望让 $s_i$ 尽快早地变成 $0$。但是如果我删 $s_i$ 太快导致其 $< s_{i - 1}$，那么 Alice 就会提前拿走 $s_i$，相当于我少了一轮操作；而不这样的话，虽然 $s_i$ 有不能小于 $s_{i - 1}$ 的限制，但是我可以先把 $s_i$ 删到和 $s_{i - 1}$ 相等，然后剩下的次数还能删删前面的元素，是不劣于上一种情况的。

我们通过夺舍 Alice 和 Bob，分析出了问题的本质：

> 对一个长度为 $n$ 的序列 $s$，反复执行以下操作：
>
> - 选出其中若干位置 ${p_1, p_2, \dots, p_m}$ 并对所有 $j \in [1, m]$ 减少 $s_{p_j}$，要求 $\sum s$ 减少量不超过 $k$。且假设这是第 $i$ 次操作，要保证 $s_{[i + 1, n]}$ 单调不降。
>
> 问 $n - 1$ 次操作能否将 $s_n$ 变为 $0$。

到这里已经是纯粹的贪心题了，考虑到题目数据范围很松，很多种实现都容易通过。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 55;
int T, n, k, f[N], s[N], t[N];
inline bool check_sum(int p_lim, int p, int lim, int hve)
{
	for(int i = p; i > p_lim; --i)
	{
		if(t[i] <= lim) return true;
		else hve -= (t[i] - lim);
		if(hve < 0) return false;
	}
	return true;
}
inline bool check_single_element(int m)
{
	for(int i = 1; i <= m; ++i) t[i] = s[i];
	for(int i = 1; i < m; ++i)
	{
		int hve = k;
		if(t[m] <= k) return false;
		for(int j = m; j > i; --j)
		{
			int l = 0, r = t[j] - 1, res = t[j];
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(check_sum(i, j, mid, hve)) res = mid, r = mid - 1;
				else l = mid + 1;
			}
			for(int k = j; k > i; --k)
			{
				hve -= max(0, t[k] - res);
				t[k] = min(t[k], res);
			}
		}
	}
	return true;
}
inline bool check_answer(int m)
{
	for(int i = 1; i <= m; ++i) s[i] = f[i - 1];
	sort(s + 1, s + m + 1);
	for(int i = 1; i <= m; ++i)
		if(!check_single_element(i))
			return false;
	return true;
}
inline void sol()
{
	cin >> n >> k;
	for(int i = 0; i <= n; ++i) cin >> f[i];
	int l = 2, r = n + 1, res = 1;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check_answer(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << res << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
/*
1
9 5
8 9 6 10 10 9 3 10 7 8
*/
```

---

## 作者：Federico2903 (赞：0)

思考一下 Alice 和 Bob 的最优策略是什么。

乍一看好像直接找最优策略非常困难，因为有 MEX 的限制。

我们可以先考虑对于一个固定的答案来寻找最优策略。不妨按出现次数排序后二分答案。

假设目前的答案是 $i$，那么 Alice 胜利当且仅当 Alice 能够取走 $0 \sim i - 1$ 各至少一个（所以数字的相对大小关系已经不重要了）。

那么 Alice 的最优策略就很显然了，每次取走目前没拿过的数字中出现次数最少的数字一定更优。

但是 Bob 的策略还是不好确定，那么我们不妨再枚举一个 $j$，表示 Bob 赶在 Alice 之前最小的删空的数字。

那么对于所有满足 $j < p < i$ 的数字我们都不需要管了，因为 Alice 和 Bob 的操作一定都不会涉及这些数字（显然的因为 Bob 需要删空最小的 $j$，所以去删除比它大的数字一定不优，由于 ? 被删空，比它大的数字 Alice 也没必要去取）。

 那么判断 $ans \ge i$ 的条件就是对于每个 $0 \le j < i$ Bob都无法满足条件。
 
那么 Bob 上来肯定会对着 $j$ 狂暴消除，吗？

显然不会是这样，根据我们刚刚推断出来的 Alice 的策略，当 $f_j < f_{j - 1}$ 时，Alice 就会把 $j$ 拿走。

所以我们可以把 Bob 的每次操作看作将出现次数最多的数字出现次数减一并重排序列，然后重复上述操作。

我们来看最后这种操作对序列的影响，比较显然的，Bob 就是把若干个极大值消到同一个位置。

那么我们考虑暴力模拟这种操作，可以轻松做到 $O(m^3\log m)$ 的复杂度，可以通过 Easy Version。

---

## 作者：larsr (赞：0)

~~把 hard 的题解搬过来了~~
## 题目大意
有一个序列 $a$ 和一个初始为空的序列 $c$。序列 $a$ 用 $f_i$ 表示，$f_i$ 表示 $a$ 中 $i$ 的数量，$a$ 的最大值为 $m$。**原题中的 Alice 和 Bob 在下文分别称为 A 和 B**。

- A 每回合从 $a$ 取一个数到 $c$ 序列，并在 $a$ 中删去这个数。
- B 每回合在 $a$ 删最多 $k$ 个数。

每回合 A 先操作。直到 $a$ 空了游戏结束，A 想让 $c$ 最终的 MEX 最大，B 想让 $c$ 最终的 MEX 最小。求 $c$ 最终的 MEX。
## Easy Version
我们可以进行**二分答案**，二分 $x$，假设序列 $a$ 只有小于等于 $x$ 的数，算出最终的 MEX 可不可以到达 $x + 1$。找出符合条件的**最大的** $x$，答案为 $x + 1$。

我们现在的任务是判断**假设**的 $a$ 出现的数是否在 $c$ 都能出现。那么 A 想的是把每种数都有一个加入到 $c$，B 想的是让 $c$ 不存在一种数（**只要**一种就可以）。

**注意**：下文中所有操作都是针对**没在** $c$ 中出现的数。定义一个序列 $F$，$F$ 中每个数代表每个**没在** $c$ 出现的数在 $a$ 中的**数量**。

A 的策略很显然。A 每次操作在 $a$ 中**数量最少**的数。

比如目前 $F=[2,3,4,5]$。如果选数量为 $2$ 的数，那么 $F=[3,4,5]$。如果选数量为 $3$ 的数，那么 $F=[2,4,5]$。第二种操作后的 $F$ 更容易让 B 把**其中的一种数删完**。

说完 A 的策略，接下来说 B 的策略。B 要在 A 之前删完一种数，那么他就要有要删的**目标**（也就是说他最终要把一种数全删完，这个过程中主要针对它删除）。

居然 B 已经有了目标，那么 B 肯定要去删它，但不是疯狂的瞎删。比如 $F=[6,8,9,10]，k=5$，B 的目标是删数量为 9 的数，如果它一开始就使劲删，那么 $F=[6,8,4,10]$，接下来 A 第一个就选择 B 的目标。

那么很显然了，B 不要一下就把目标全删，要先把数量比它小的删一些，这样目标就不会一下在就被 A 选中了。那么 B 的**策略**为如果目前有其它数的数量和目标的数量相同，那么先删和目标**数量相同**的数，再删目标。

那么想计算就很简单了，对此时每个目标都枚举一遍即可，不过要加入一些简便的方法优化一下。单次判断时间复杂度 $O(m^3)$。总时间复杂度 $O(m^3\log_2n)$。

---

## 作者：Jsxts_ (赞：0)

首先二分答案。

发现若一个数只剩 $\le k$ 个，那么 Bob 一次就能删光，所以此时 Alice 必须选一个这个数。所以若数量 $\le k$ 的数个数 $>1$ 则 Bob 胜。

另一个观察是 Alice 每次无论如何只会选当前剩余最少的数。

所以，一个显然错误的贪心为：若将 $0\sim mid-1$ 所有数按数量从小到大排序记为 $b$，首先第一个肯定被 Alice 选，之后判断 $b_i-k$ 的前缀和与 $(i-1)k$ 的大小关系即可（即，每次将个数最小的数选到恰剩 $k$ 个，再对下个操作，直到当前最小数已经为 $k$）。

这组 hack 数据可以引出正确思路：

```
3 5
10 9 8 6
```

考虑对 $mid=4$ 的 check，发现会判定为 Alice 胜，但有一个更优的策略：

- Alice 选一个 $3$，序列变为 $10,9,8$。
- Bob 选 $3$ 个 $0$，两个 $1$，序列变为 $7,7,8$。
- Alice 选一个 $0$, 序列变为 $7,8$。
- Bob 选 $2$ 个 $1$，三个 $2$，序列变为 $5,5$，显然此时 Alice 已经输了。

显然 Alice 都是最优决策，那么问题出在之前的错误思路会进行无用的操作，考虑到 Alice 只会选最小的数，不妨令时时刻刻序列中最小的数尽量大，这意味着我们会将损失降到最低，不难证明这是对的。其次，Bob 可以对每个前缀进行上述操作，并取最优结果。因为全部一起不一定最优。

那么，由于 $m$ 较小，考虑直接模拟这个过程，用 deque 即可模拟从大的部分减数以及从最小值删数。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e5;
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
int m,k,f[N + 10],b[N + 10];
deque<pair<int,int> > q;
pair<int,int> c[N + 10];
bool check(int mid) {
	int ct = 0;
	for (int i = 0;i < mid;i ++ ) ct += f[i] <= k, b[i] = max(0,f[i] - k);
	if (ct >= 2) return 0;
	sort(b,b + mid);
	for (int i = 2;i < mid;i ++ ) {
		int tt = 0;
		for (int j = i;j;j -- ) 
			if (b[j] != b[j + 1] || j == i) c[++tt] = {b[j],1};
			else c[tt].y ++;
		while (q.size()) q.pop_back();
		for (int j = 1;j <= tt;j ++ ) q.push_back(c[j]);
		for (int j = 1;j < i;j ++ ) {
			int tk = k;
			while (1) {
				auto x = q.front();q.pop_front();
				if (!q.size()) {
					if (tk >= 1ll * x.y * x.x) {
						return 0;
					}
					int ct = tk % x.y;
					x.x -= tk / x.y;
					if (ct) q.push_front({x.x - 1,ct});
					q.push_front({x.x,x.y - ct});
					break;
				}
				auto y = q.front();q.pop_front();
				ll val = 1ll * (x.x - y.x) * x.y;
				if (val <= tk) {
					tk -= val, q.push_front({y.x,y.y + x.y});
					if (!y.x) return 0;
					if (!tk) break;
				}
				else {
					int ct = tk % x.y;
					x.x -= tk / x.y;
					if (ct) {
						if (y.x == x.x - 1) q.push_front({y.x,y.y + ct});
						else q.push_front(y), q.push_front({x.x - 1,ct});
					}
					else q.push_front(y);
					q.push_front({x.x,x.y - ct});
					break;
				}
			}
			auto t = q.back();q.pop_back();
			t.y --;
			if (t.y) q.push_back(t);
		}
	}
	return 1;
}
int main() {
	int T = read();
	while (T -- ) {
		m = read(), k = read();
		for (int i = 0;i <= m;i ++ ) f[i] = read();
		int l = 0,r = m + 1;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		}
		printf("%d\n",l);
	}
	return 0;
}
```

upd: 如何优化上述做法呢？（参考官方题解）

注意：**由于我们先让 Alice 删去了第一个，接下来每次操作是看成 Bob 先删 $k$ 个，Alice 再删一个。**

考虑这个序列会减到某个时刻，满足 $b_i=\lfloor\dfrac{i+s-1}{n}\rfloor$，其中 $n$ 为序列长度，$s$ 为序列和。在这个状态后，每一次操作后必然还是这个状态，所以可以用二元组 $(n,s)$ 表示。

若我们对这个序列的每个前缀都求出了若干个二元组 $(n,s)$（显然它们可以一起考虑），对于每个 $n$ 最小的 $s$ 最优，所以考虑从 $n\to n-1$：$(n,s)\to (n-1,s-k-\lfloor\dfrac{s-k}{n}\rfloor)$。按 $n$ 从大到小转移完后，我们就求出的对每个 $n$ 最小能转移到的 $s$。只需判断能否转移到 $(1,0)$ 即可。

现在的问题为：对每个前缀求出一开始的时刻满足此时它可以用 $(n,s)$ 表示。这个时刻可以看成：$1\sim p$ 已经被 Alice 选过（这里我们确保操作的任何时刻序列都是递增的，所以这个就是 Alice 的最优策略）。那么 $p$ 要满足的不等式为（令 $pre$ 为 $b$ 的前缀和）：

$$pre_i-pre_p-pk<b_p\times(i-p)$$

发现 $p$ 满足单调性，直接双指针即可。

这一部分：

```cpp
for (int i = 1;i < mid;i ++ ) {
  while (p < i - 1 && pre[i] - pre[p + 1] - 1ll * (p + 1) * k >= 1ll * b[p + 1] * (i - (p + 1))) p ++;
  ans[i - p] = min(ans[i - p],pre[i] - pre[p] - 1ll * p * k);
}
for (int i = mid - 2;i >= 1;i -- ) ans[i] = min(ans[i],ans[i + 1] - k - (ans[i + 1] - k) / (i + 1));
return ans[1] > 0;
```

---

