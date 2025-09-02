# [ARC173C] Not Median

## 题目描述

你有一个从 $1$ 到 $n$ 的整数排列 $P$ 。

对于所有 $ i=1,2,\dots,N $ ，输出满足以下所有条件的一对整数 $ (l,r) $ 的 $ r-l+1 $ 的最小值。如果不存在这样的 $ (l,r) $ ，则输出 `-1` 。

- $1 \le l \le i \le r \le N$ 。
- $r-l+1$ 是奇数。
- $ P_i $ **不是** $P$ 的子序列 $ (P_l,P_{l+1},\dots,P_r) $ 的中位数。

长度为 $ L $（奇数）的整数序列 $A$ 的中位数被定义为按升序对 $ A $ 排序后的序列 $ A' $ 的第 $ \frac{L+1}{2} $ 个值。

## 样例 #1

### 输入

```
5
1 3 5 4 2```

### 输出

```
3 3 3 5 3```

## 样例 #2

### 输入

```
3
2 1 3```

### 输出

```
-1 3 3```

## 样例 #3

### 输入

```
14
7 14 6 8 10 2 9 5 4 12 11 3 13 1```

### 输出

```
5 3 3 7 3 3 3 5 3 3 5 3 3 3```

# 题解

## 作者：wosile (赞：8)

真的只需要凭感觉就能过了。

直觉上，随机时这个答案应该很小，从而答案较大的位置周边必然有一些特殊性质。

首先，我们对于位置 $i$ 求答案时，如果 $p_{i-1}$ 和 $p_{i+1}$ 的值都在 $p_i$ 的同一侧，那么 $[i-1,i+1]$ 区间中的中位数就不是 $p_i$，从而答案为 $3$。也就是说，答案不为 $3$ 时 $i$ 附近的数和 $p_i$ 的大小关系要么是 `+ 0 -`，要么是 `- 0 +`。

例如，我们考虑中间的 $4$：

`1 7 2 4 6 3 5`

这个 $4$ 对应的答案是 $-1$。为什么呢？

比如我们现在有一个不满足条件（i.e.中位数是 $4$）的长度为奇数的区间 $[l,r]$，考虑另一个区间 $[l,r+2]$，如果 $p_{r+1}$ 和 $p_{r+2}$ 在 $4$ 的同侧，即 $(p_{r+1}-4)(p_{r+2}-4)>0$，那么 $[l,r+2]$ 的中位数就不可能仍然是 $4$（一次往一个方向放两个数肯定会偏对吧），从而使得 $[l,r+2]$ 符合题目条件。

$[l-2,r]$ 同理。

由此可见，只要所求位置附近有两个连续的数值在所求位置数值的同侧，就容易构造出一个包含这两个连续数值的较短的合法区间。而上面的例子中所有数和 $4$ 的大小关系是 `- + - 0 + - +`，不存在两个相邻的又在 $4$ 同侧的数。

也就是说，答案超过 $x$ 时，$[i-x,i+x]$ 中的数和 $p_i$ 的大小关系要么是 `... - + - + - + - + 0 - + - + - + - + ...`，要么是 `... + - + - + - + - 0 + - +  - + -+ - ...`。

注意，我们求两侧（$i=1$ 和 $i=n$）的答案时，即使存在两个相邻同侧数，也未必存在合适的 $l$ 使得 $[l,r]$ 长度为奇数，从而未必存在合法的 $[l,r+2]$。

例如：

`4 3 5 6 2 1 7`

虽然 $p_3=5$ 和 $p_4=6$ 在 $p_1=4$ 的同侧，但是 $[1,2]$ 的长度为偶数，所以很可惜没法用。

既然位置 $i$ 的答案几乎由离 $i$ 最近的相邻同侧数决定，我们就可以直接以 $i$ 为中心向两边查找，每次检查边界上的相邻数是否在 $p_i$ 同侧即可。

但是这样每次扫描都是 $O(n)$ 的，难道不是 $O(n^2)$ 过不去吗？

并不是。考虑在对 $i$ 的扫描中我们扫描到长度为 $k$ 才找到了一对相邻同侧数对（位置分别在 $x_1=i+k$ 和 $x_2=i+k+1$），那么对于每个 $i<j<x_1$，$p_{j-1}$ 和 $p_{j+1}$ 一定在 $p_j$ 的同侧（否则在这里就找到同侧数对了，想想为什么）。所以 $j$ 位置处的答案无需计算一定是 $3$。

接下来到 $x_1$ 才需要再次开始向两侧找答案。

因此，如果只考虑向右的扫描，每个位置最多被扫描到一次。而左右扫描是同步的，因此总时间复杂度为 $O(n)$。

细节稍微有一点，详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int L=i,R=i,ans=3;
		while(L>=1 || R<=n){
			// 这里把 [l,r]->[l-1,r+1] 也算作一种扩展而不特殊处理。
			if(L>1 && R<n && 1LL*(a[L-1]-a[i])*(a[R+1]-a[i])>0)break;
			if(L>2 && 1LL*(a[L-1]-a[i])*(a[L-2]-a[i])>0)break;
			if(R<n-1 && 1LL*(a[R+1]-a[i])*(a[R+2]-a[i])>0)break;
			if(i>1 && R<n && 1LL*(a[R]-a[i])*(a[R+1]-a[i])>0)break;// 排除 i=1 的理由见题解
			if(i<n && L>1 && 1LL*(a[L]-a[i])*(a[L-1]-a[i])>0)break;// 排除 i=n 的理由见题解
			ans+=2,L-=2,R+=2;
		}
		if(L>=1 || R<=n)printf("%d ",ans);
		else printf("-1 ");
	}
	return 0;
}
```

下面这个是开玩笑的，但是真的很短对吧。

```cpp
#include<iostream>
#define c(x,y,z) (x>0&&y<=n&&1LL*(a[x]-a[z])*(a[y]-a[z])>0)
int a[300005],n;int main(){std::cin>>n;for(int i=1;i<=n;i++)std::cin>>a[i];for(int i=1;i<=n;i++){int L=i,R=i,s=3;while(s<=n){if(c(L-1,R+1,i)|c(L-2,L-1,i)|c(R+1,R+2,i)|i>1&c(R,R+1,i)|i<n&c(L-1,L,i))break;s+=2,L-=2,R+=2;}printf("%d ",s<=n?s:-1);}}
```

---

## 作者：TernaryTree (赞：3)

赛后一分钟过题，嘲讽。

考虑什么样的区间不符合条件，并且其所有子区间都不符合条件。如果这个区间左端点奇偶性和当前 $i$ 相同，那么显然把 $i$ 左侧的两两分组，一定是一个小于一个大于，右边一样。否则，一定是 $i-1$ 和 $i+1$ 一个小于一个大于，$i-1$ 左侧与 $i+1$ 右侧同理两两分组。

于是按值从小到大处理，考虑一个序列 $now$，将 $<P_i$ 的赋值为 $0$，大于的赋值为 $1$，记 $s_i=now_i+now_{i+1}$，然后用两棵线段树维护奇数下标和偶数下标的 $s_i$ 前后缀连续 $1$ 个数，即可模拟上一段所述的过程。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const int inf = 1e18;
const bool multidata = 0;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n;
int p[maxn], q[maxn];
int now[maxn];
int s[maxn];

struct seg {
	struct node {
		int len, pre, suf;
		node() = default;
	} tr[maxn << 2];
	
	void pushup(node &u, node l, node r) {
		u.len = l.len + r.len;
		u.pre = l.pre + (l.len == l.pre ? r.pre : 0);
		u.suf = r.suf + (r.len == r.suf ? l.suf : 0);
	}
	
	void modify(int u, int l, int r, int p, int x) {
		if (l == r) {
			tr[u].len = 1;
			tr[u].pre = tr[u].suf = (x == 1);
			return;
		}
		if (p <= mid) modify(lc, p, x);
		else modify(rc, p, x);
		pushup(tr[u], tr[ls], tr[rs]);
	}
	
	node query(int u, int l, int r, int ql, int qr) {
		if (ql > qr) return {0, 0, 0};
		if (ql <= l && r <= qr) return tr[u];
		if (ql <= mid && mid < qr) {
			node ans;
			pushup(ans, query(lc, ql, qr), query(rc, ql, qr));
			return ans;
		} else if (ql <= mid) return query(lc, ql, qr);
		else return query(rc, ql, qr);
	}
} tr[2];

void md(int p, int x) {
	if (p > 1) s[p - 1] -= now[p];
	if (p < n) s[p] -= now[p];
	now[p] = x;
	if (p > 1) s[p - 1] += now[p];
	if (p < n) s[p] += now[p];
	if (p > 1) tr[(p - 1) & 1].modify(1, 1, (n + 1) / 2, p / 2, s[p - 1]);
	if (p < n) tr[p & 1].modify(1, 1, (n + 1) / 2, (p + 1) / 2, s[p]);
}

int ans[maxn];

void fake_main() {
	cin >> n;
	rep(i, 1, n) cin >> p[i], q[p[i]] = i, md(i, 1), ans[i] = inf;
	rep(v, 1, n) {
		int i = q[v];
		md(i, 3);
		int ansr = tr[(i + 1) & 1].query(1, 1, (n + 1) / 2, (i + 2) / 2, (n + 1) / 2).pre;
		int r = i + (ansr + 1) * 2;
		int ansl = tr[i & 1].query(1, 1, (n + 1) / 2, 1, (i - 1) / 2).suf;
		int l = i - (ansl + 1) * 2;
		if (l >= 1) ans[i] = min(ans[i], i - l + 1);
		if (r <= n) ans[i] = min(ans[i], r - i + 1);
		if (i > 1 && i < n) {
			if (p[i - 1] < p[i] && p[i] < p[i + 1] || p[i - 1] > p[i] && p[i] > p[i + 1]) {
				ansr = tr[(i + 2) & 1].query(1, 1, (n + 1) / 2, (i + 3) / 2, (n + 1) / 2).pre;
				r = i + 1 + (ansr + 1) * 2;
				ansl = tr[(i - 1) & 1].query(1, 1, (n + 1) / 2, 1, (i - 2) / 2).suf;
				l = i - 1 - (ansl + 1) * 2;
				if (l >= 1) ans[i] = min(ans[i], i - l + 2);
				if (r <= n) ans[i] = min(ans[i], r - i + 2);
			} else {
				ans[i] = min(ans[i], 3ll);
			}
		}
		md(i, 0);
	}
	for (int i = 1; i <= n; i++) {
		if (ans[i] == inf) cout << -1 << " ";
		else cout << ans[i] << " ";
	}
	cout << endl;
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}



```

---

## 作者：LKY928261 (赞：3)

## 题意

给定排列 $p$，对于位置 $i$ 定义一个区间合法当且仅当：

- 区间包含位置 $i$；
- 区间长度为奇数；
- $p_i$ **不是**区间的中位数。

对每个 $i\in[1,n]$，求出最短的合法区间的长度；若不存在则输出 `-1`。

## 分析

记 $ans_i$ 表示位置 $i$ 的最终答案。

注意到：因为 $p$ 是一个排列，$p_i$ 互不相同，所以对于任意一个长度为正奇数的区间，有且仅有一个位置是该区间的中位数。

所以满足 $ans_i$ 大于正奇数 $k$ 的 $i$ 的个数不超过 $\lceil\dfrac{n}{k}\rceil$。

于是考虑从小到大依次枚举区间长度 $k$，每次对还未确定答案的位置判断是否存在长度为 $k$ 的合法区间。

而 $\sum\limits_{1}^{\lceil\frac{n}{2}\rceil}{\lceil\dfrac{n}{2i-1}\rceil}$ 是 $O(n\ln n)$ 级别的，所以只需要能够 $O(1)$ 判断，时间复杂度就是对的。

问题就转化成了：对于位置 $i$，已知 $ans_i\ge k$，要求 $O(1)$ 判断是否 $ans_i>k$。

当 $ans_i>k$ 时，$p_i$ 必须是每个包含它的长度为 $k$ 的区间的中位数。若使用 `+` 表示 $>p_i$ 的元素，`-` 表示 $<p_i$ 的元素，`0` 表示 $p_i$ 本身，那么这些区间内的 `+` 和 `-` 必须相互抵消才能使 $p_i$ 成为区间中位数。

于是，假定 $i$ 左右两侧都有足够多的元素，那么 $k=3$ 时 $i$ 周围元素的分布只有 `+-0+-` 和 `-+0-+` 两种情况。在此基础上，容易推出 $k=5$ 的情况是 `+-+-0+-+-` 和 `-+-+0-+-+`。依此类推，对任意奇数 $k$，仅有 `+-...+-0+-...+-` 和 `-+...-+0-+...-+` 两种状态能够满足 $ans_i>k$。

因为已知 $<k$ 的情况不成立，所以每次判断只需要在前面的基础上判断常数种情况，单次复杂度 $O(1)$，符合要求。

于是我们就得到了这一份 WA 掉的[代码](https://atcoder.jp/contests/arc173/submissions/51134837)。

## 细节

这里有一个坑点。上面的推论都是建立在“$i$ 左右两侧都有足够多的元素”的假设上进行的，在边界处会有例外。比如下面这组我赛时 hack 掉了我自己的数据：

```text
5
3 1 5 4 2
```

整个排列相对于 $p_1=3$ 的状态是 `0-++-`，而 $ans_1=-1$。这是因为 $1$ 的左侧没有其它元素，右侧只要两个一组能够配对即可。

存在这种 corner case 的位置只有 $1$ 和 $n$，特殊处理一下即可。

## 复杂度

时间复杂度为调和级数的 $O(n\ln n)$……吗？

赛时我确实是这么认为的，不过写这篇题解时注意到实际上不是这样。

考虑某个 $i\in[2,n-1]$，若 $ans_i=k>3$，那么根据上面的推论，$i$ 左右两侧都是 `+-+-...+-` 或 `-+-+...-+`。注意到 `+-+` 和 `-+-` 都会使中间位置的元素不可能是中位数，也就是 $i$ 周围 $\Theta(k)$ 个位置的答案均为 $3$。

于是 $\sum{ans_i}$ 是线性的，从而时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;
typedef long long ll;
const ll _=5e5+5;
ll n,a[_],s[_],i,k;vector<ll>b,c;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=n;i++){
		if(i>2&&((a[i-2]<a[i])==(a[i-1]<a[i])))s[i]=3;
		else if(i>1&&i<n&&((a[i-1]<a[i])==(a[i+1]<a[i])))s[i]=3;
		else if(i<n-1&&((a[i+1]<a[i])==(a[i+2]<a[i])))s[i]=3;
		else c.eb(i);
	}
	for(k=5;k<=n;k+=2){
		b=c;c.clear();
		for(auto i:b){
			if(i-k+2>0&&i<n&&(a[i-k+2]<a[i])!=(a[i-1]<a[i]))s[i]=k;
			else if(i-k+1>0&&(a[i-k+1]<a[i])==(a[i-k+2]<a[i]))s[i]=k;
			else if(i+k-2<=n&&i>1&&(a[i+k-2]<a[i])!=(a[i+1]<a[i]))s[i]=k;
			else if(i+k-1<=n&&(a[i+k-1]<a[i])==(a[i+k-2]<a[i]))s[i]=k;
			else c.eb(i);
		}
	}
	for(auto i:c)s[i]=-1;
	for(i=1;i<=n;i++)cout<<s[i]<<' ';
}
```

---

## 作者：Eraine (赞：2)

编号：AT_arc173_c

tag：贪心

难度 *2008

我们设第 $i$ 位的答案为 $f_i$。

> Lemma 1 对于任意不同的两个数 $i$ 和 $j$，$\min(f_i,f_j)\le j-i$，也就是 $f_i$ 和 $f_j$ 至少有一个小于 $j-i+1$。

证明：

分两类讨论：

当 $j-i+1$ 为奇数时，区间 $[i,j]$ 是一个统计的合法区间。由于一个区间只能有一个中位数，所以在区间 $[i,j]$ 内 $a_i$ 和 $a_j$ 至多有一个是中位数。不是中位数的数答案 $\le j-i-1$。

当 $j-i+1$ 为奇数时，区间 $[i-1,j]$ 和 $[i,j+1]$ 中至少有一个是统计的合法区间（区间 $[1,n]$ 除外）。由于一个区间只能有一个中位数，所以在区间 $[i-1,j]$ 或 $[i,j+1]$ 内 $a_{i-1}/a_i$ 和 $a_j/a_{j+1}$ 至多有一个是中位数。不是中位数的数答案 $\le j-i$。

故得证。

> Lemma 2 $\sum f_i\le \Theta(n\log n)$。

证明：

我们考虑分批处理 $f$。一开始不知道任何一个 $f$。我们考虑把 $n$ 个数根据下标顺序两两分组，若剩下 $1$ 个则单独分组。共分成 $\lceil \frac{n}{2}\rceil$ 组。对于每个大小为 $2$ 的组，假设长度为 $len$，那么至少有一个 $f\le len$。那么在 $n$ 个数中，有 $\lfloor \frac{n}{2}\rfloor$ 个数 $\sum\lt f$。我们再考虑剩下 $\lceil \frac{n}{2}\rceil$ 个数，同样地递归处理，故得证。

> Lemma 3 对于任意的 $i$ 使得 $f_i\neq -1$，存在一个区间 $[l,r]$，使得 $p_i$ 不是中位数，$l\le i\le r$，且 $l\in[i-1,i]$ 和 $r\in[i,i+1]$ 至少有一个条件满足。

证明：

考虑数学归纳法。假设存在一个区间 $[l,r]$ 使得 $p_i$ 不是中位数，$l\le i\le r$，且 $l\le i-2,r\ge i+2$。设 $p_j\lt p_i$ 的贡献为 $-1$， $p_j\gt p_i$ 的贡献为 $1$，则 $[l,r]$ 的总贡献不为 $0$。当 $[l+2,r]$ 和 $[l,r-2]$ 至少有一个区间总贡献不为 $0$ 时，显然取其中一个不为 $0$ 的更优。否则 $[l+2,r]$ 和 $[l,r-2]$ 总贡献均为 $0$。设一个区间 $[i,j]$ 的贡献为 $w(i,j)$，把第二种情况转换成符号语言：$w(l,r)\neq0,w(l+2,r)=w(l,r-2)=0$。显然有等式 $w(l,r)+w(l+2,r-2)=w(l+2,r)+w(l,r-2)$，所以 $w(l+2,r-2)\neq 0$，此时取区间 $[l+2,r-2]$ 更优。所以区间 $[l.r]$ 总能找到子区间满足。故成立。

所以暴力的思路是，固定左区间 $i$ 和 $i-1$，暴力拓展右区间断点，对称同理。两类暴力拓展同时做，均摊即可过题。由于是暴力，常数很小。43 ms。

$\Theta(n\log n)$。

[Submission](https://atcoder.jp/contests/arc173/submissions/51134639)

各位客官点个赞再走吧 qwq

---

## 作者：lingziyi2025 (赞：1)

# [ARC173C] Not Median 题解

## 题意

给定一个由 $1$ 到 $N$ 之间的整数构成的排列 $P=(P_1,P_2,...,P_N)$。

求对于每个 $i=1,2,...,N$，输出符合以下条件的数对 $(l,r)$，使 $r-l+1$ 尽量小；

- $1\le l \le i \le r \le N$；

- $r-l+1$ 为奇数；

- 序列 $P$ 的连续部分 $(P_l,P_{l+1},...,P_r)$ 的中位数**不为** $P_i$。

    定义一些数的中位数为：若数的个数为 $L$，则中位数是这些数中排名为 $\frac{L+1}{2}$ 的数的数值。

如果找不到满足条件的 $(l,r)$ ，输出 `-1`。

数据范围：$3\le N \le 3\times 10^5$，输入值为整数。

### 题解

这种题十分奇怪，难以下手，不如先模拟数据，推一推满足条件的区间有什么性质。

为了方便，将比 $P_i$ 小表示为 `-`，将比 $P_i$ 大表示为 `+`，将 $P_i$ 表示为 `0`。

则区间可以表示为 `...-+-0+-+...` 或 `...+-+0-+-...`。

当出现两个相邻的 `++` 或 `--` 时，区间就符合中位数的条件。

而题目要求区间最小，于是先考虑一下暴力扩展。

这里用到的实现技巧很妙：

首先扩展时需要保证区间长度为奇数，所以每次拓展考虑加入两个数。

由于向左还是向右不确定，考虑合并：发现怎么拓展对答案贡献都为 `2`，而且我们不关心这个区间长啥样，

所以可以同时进行向左向右，而此时 $l,r$ 的定义也变为当前能扩展出的所有区间的范围。

一旦扩展到合法区间就退出，否则同时向左向右扩展 $l=l-2,r=r+2$。

但是对答案贡献仅为 `2`。

而判断扩展时是否有合法区间即分类讨论新加入的两个数，判断是否同 `+` 或同 `- `。

但是注意：我们初始的结论是：当出现两个相邻的 `++` 或 `--` 时，区间符合条件。

所以还可以出现 $P_{R},P_{R+1}>P_i$ 的情况。

但是依然要保证区间长度为奇数：推一下数据发现，$P_{i-1}<P_i$，所以能补一个数；（ 但 $i=1$ 时不行 ）

$P_{L},P_{L-1}$ 同理。

考虑这个暴力行不行：

发现是可以的，时间复杂度为 $O(n)$，证明如下：

对于每个搜索的区间，当前位置的两边必然是 `+`，`-` 的交替。

因为只有这样才不会按照上面条件被 break 掉。

如： `+-+-0+-+-+-++`，里面有很多 `-+-` 和 `+-+` ，这两种区间的答案都是 `3`。

那么当遍历到这些小区间的位置时，只会造成 `3` 的贡献。

于是每个位置造成的贡献为 `4`（ 大区间 `1` 次，小区间 `3` 次 ）。

所以时间复杂度为 $O(n)$。

### Code

```c++
#include<bits/stdc++.h>
#define frein freopen("in.txt","r",stdin);
#define freout freopen("out.txt","w",stdout);
#define fre(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define outa(LL,RR,AA) {for(rg O=LL;O<=RR;O++)cout<<AA[O]<<" ";cout<<endl;}
#define outm(LL1,RR1,LL2,RR2,AA) {for(rg U=LL1;U<=RR1;U++){for(rg V=LL2;V<=RR2;V++)cout<<AA[U][V]<<" ";cout<<endl;}cout<<endl;}
#define BZ printf("--------\n");
#define rg register int
#define ll long long
using namespace std;
#define inf 1e9
const int N=3e5+5;
int n,a[N],l,r,ans,p;
bool pd(int l,int r,int i){return 1ll*(a[l]-a[i])*(a[r]-a[i])>0;}
int main(){
	std::ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(rg i=1;i<=n;i++)cin>>a[i];
	for(rg i=1;i<=n;i++){
		ans=3,l=r=i;
		while(1<=l||r<=n){
			if(l>1&&r<n&&pd(l-1,r+1,i))break;
			if(l>2&&pd(l-1,l-2,i))break;
			if(r<n-1&&pd(r+1,r+2,i))break;
			if(i>1&&r<n&&pd(r,r+1,i))break;
			if(i<n&&l>1&&pd(l,l-1,i))break;
			ans+=2,l-=2,r+=2;
		}
		if(1<=l||r<=n)cout<<ans<<" ";
		else cout<<"-1 ";
	}
	return 0;
}
```

---

## 作者：Naganorhara_Yoimiya (赞：0)

# 题解：AT_arc173_c [ARC173C] Not Median
## 题目描述
给出一个数列 $a$，对于 $\forall i \in [1,n]$，求出一对 $(l,r)$，满足：
$$\begin{cases}
  l \le i \le r\\
 (r - l + 1) \bmod 2 = 1\\
  a_i 不为序列 \{a_l,a_{l+1},\dots,a_{r}\}的中位数\\
l-r+1 的值为所有符合条件的(l,r)中最小的\\
\end{cases}$$ 

## 思路分析
先手玩样例：``1,3,5,4,2``。

假如说现在需要选择 $3$，那么我们对原序列进行下面的处理：记比 $3$ 大的为 $1$，比 $3$ 小的为 $-1$，于是我们得到以下序列：``-1,0,1,1,-1``。

接下来，观察一下结果，显然一种可行的情况是将 $3$ 向后扩展 $2$ 位，答案是 $3$。

因此，多手玩几组样例我们可以知道，我们只需要让选择的序列有两个 $-1$ 或者 $1$ 相邻即可。

所以，我们可以得到一种朴素的暴力算法：

枚举 $i$，向两边扩展，每次扩展两个单位。

如果扩展到边界，那么退出。

如果判断到有相邻的 $1$ 或者 $-1$，那么输出答案并退出。

否则，判断是否有一边的 $-1$ 或者 $1$ 相邻。

不过，上面的算法基于 $i$ 可以向两边无限扩展，还有边界情况需要特判。

边界情况下，只需要向一边进行扫描，找到两个相邻的相等的输出答案即可。

时间复杂度 $O(n)$。

关于时间复杂度的证明，其它题解写的已经很明白了，~~虽然我打出来之前一直认为这个是暴力。~~

## AC Code
一些细节在注释里面解释了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[300005],n,L,R,ans;

bool check(int &i){
	//边界情况 
	if(i > 1 && R < n && (a[R]-a[i]) * (a[R+1]-a[i])>0 
	|| i < n && L > 1 && (a[L]-a[i]) * (a[L-1]-a[i])>0) return 1;
	//一般情况 
	if(L > 1 && R < n && (a[L-1]-a[i]) * (a[R+1]-a[i])>0 
	|| L > 2 && (a[L-1]-a[i]) * (a[L-2]-a[i])>0 
	|| R < n-1 && (a[R+1]-a[i]) * (a[R+2]-a[i])>0) return 1;
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++){
		//稍微解释一下，因为（如果有解）答案最小是3，而我们是先扫描再更新L和R的值，如果扫到了，直接加上 
		L = i,R = i,ans = 3;
		while(L >= 1 || R <= n){
			if(check(i) == 1) break;
			ans += 2,L -= 2,R += 2;
			//还是要解释一下，虽然L和R同时扩展，但是我只需要取一边相等就可以了 
		}
		if(L >= 1 || R <= n) cout << ans << " ";
		else cout << -1 << " ";
	}
	return 0;
}
```

---

## 作者：roBotic (赞：0)

今年 ARC 大賽，線性和線段樹做法大勝，STL 慘敗。羞也不羞，朋比為奸！我們需要嚴格的檢討！

来一发 `set` 题解。

我们拿其中的某一个数 $k$ 考虑，记序列中比它大的数为 $0$，比它小的为 $1$，手玩一下会发现是中位数情况只有两种：

$$ \{\cdots,0,1,0,1,k,0,1,0,1,\cdots\},\\ \{\cdots,1,0,1,0,k,1,0,1,0,\cdots\}. $$

也就是两边都 $01$ 交替，并且 $k$ 两边不同为 $0$ 或 $1$，那么非中位数的情况有：

- $k$ 两边同为 $0$ 或 $1$，答案为 $3$。
- $k$ 某一侧出现了连续两个同为 $0$ 或 $1$，我们以右侧为例，记这两个连续相同的数的第二个的下标是 $p$，则当 $p-k+1$ 为奇数时答案为 $p-k+1$，否则为 $p-k+2$。必要性是显然的因为区间长度必须奇数，但是充分性还需证明，为什么偶数时加入一个左边的数一定非法。我们假设 $k$ 左侧相邻的数为 $q\in \{0,1\}$，当 $p-k+2$ 为偶数的时候，$p$ 和 $p-1$ 这两位上的 $01$ 等于 $q$（如果不等于 $q$，会归于上一种情况），而 $k$ 到 $p$ 这一段中当 $p$ 这一位为 $0$ 的时候大于 $k$ 的更多，加上 $q$ 这一位之后大于 $k$ 的依然更多，所以不是中位数，当 $p$ 这一位小于 $0$ 同理，所以得证。当 $p$ 在 $k$ 左侧也同理，加入右侧第一个即可。

然后我们考虑维护，我们从小到大加入数字，标记为 $1$，便记录了这一个 $01$ 序列，然后用一个 $set$ 维护相邻相同的位置即可，每次 `lower_bound` 查询最近的第一个相邻就好了。

但是注意我们这样做需要保证 $k$ 有左侧和右侧，所以序列首尾两个数要单独处理，会发现首尾两个数不是中位数是平凡的。以第一个数为例，$[1,r]$ 这个序列可以作为答案当且仅当 $r$ 是奇数并且 $[2,r]$ 中大于 $P_1$ 的个数不等于小于 $P_1$ 的个数。这个也可以处理一个 $01$ 列然后前缀和一下。最后一个数也同理。

然后做完了。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 3e5 + 10;
int n, A[N], id[N], Ans[N], B[N];

int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; for (int i = 1; i <= n; id[A[i]] = i, i ++) cin >> A[i];
	memset(Ans, -1, sizeof Ans);
	for (int i = 2; i <= n; i ++) B[i] = B[i - 1] + (A[i] > A[1]);
	for (int i = 3; i <= n; i += 2) if (B[i] != i / 2) { Ans[1] = i; break; }
	B[n] = 0;
	for (int i = n - 1; i >= 1; i --) B[i] = B[i + 1] + (A[i] > A[n]);
	for (int i = n - 2; i >= 1; i -= 2) if (B[i] != (n - i) / 2) { Ans[n] = n - i + 1; break; }
	set<int> s; for (int i = 1; i <= n - 1; i ++) s.insert(i);
	for (int i = 1; i <= n; i ++) {
		int u = id[i];
		if (u != 1 && u != n) {
			if ((A[u - 1] < A[u]) == (A[u + 1] < A[u])) Ans[u] = 3;
			else {
				auto it = s.lower_bound(u + 1);
				if (it != s.end()) {
					int tmp = *it - u + 2; if (tmp % 2 == 0) ++ tmp;
					if (Ans[u] == -1) Ans[u] = tmp;
					else Ans[u] = min(Ans[u], tmp);
				}
				it = s.lower_bound(u - 1);
				if (it != s.begin()) {
					it --; int tmp = u - *it + 1; if (tmp % 2 == 0) ++ tmp;
					if (Ans[u] == -1) Ans[u] = tmp;
					else Ans[u] = min(Ans[u], tmp);
				}
			}
		}
		if (u > 1) {
			if (A[u - 1] < i) s.insert(u - 1);
			else s.erase(u - 1);
		}
		if (u < n) {
			if (A[u + 1] < i) s.insert(u);
			else s.erase(u);
		}
	}
	for (int i = 1; i <= n; i ++) cout << Ans[i] << " \n"[i == n];
	return 0;
}
```

---

## 作者：Crosser (赞：0)

简单一点讲一下吧。

观察到答案会有很多 $3$，$5$ 之类的小数，因此构造一个具有巨大答案的数列：$\{-a,a,-b,b,0,-c,c,-d,d\}$（相对大小）。

尽管我们要计算出 $0$ 处的答案需要扫过大量的元素，但是手玩一下这个数列，可以发现：**非边界元素都可以确定对应答案为 $\bm 3$。**

于是我们就可以在扫的过程当中确定哪些点的答案肯定是 $3$，不用再次计算。这样就可以做到**均摊** $\mathcal {O(n)}$。

实际上实现会有一些麻烦。会有几种情况停止扫描：

1. 在当前元素的左面 / 右面连着出现两个符号相同的。
2. 关于当前元素对称的两个位置上元素符号相同。

注意优先级。条件 $1$ 的长度更短，所以优先判断条件 $1$。至于左右没有优先级。

但是条件 $1$ 有一个 Corner Case：假如截下来长度不是奇数，就只能往反方向借一个。但是对于数列首尾，就没法借了，所以只能暴力算首尾位置的答案。

注意：如果这里能借一个，就保证满足条件。如果不满足早就在之前被判掉了。

细节大概就这么多。如果你担心填 $3$ 填的太多了少填两三个爆算也行。

这就做完了。[AC Code](https://atcoder.jp/contests/arc173/submissions/57232284)。

---

## 作者：N_Position (赞：0)

# AT_arc173_c

## 题目大意

给你一个由 $1$ 到 $N$ 的整数组成的排列 $P=(P_1,P_2,\dots,P_N)$。

对于每个 $i=1,2,\dots,N$，打印满足以下所有条件的一对整数 $(l,r)$ 的 $r-l+1$ 的最小值。如果不存在这样的 $(l,r)$，则打印 `-1`。

- $1 \leq l \leq i \leq r \leq N$。
- $r-l+1$ 是奇数。
- $P$ 的连续子序列 $(P_l,P_{l+1},\dots,P_r)$ 的中位数不是 $P_i$。

## 题目分析

设每个位置的答案为 $ans_i$。

### 简化题目1

若只询问答案为 $3$ 的位置，该怎么做？

发现中位数是否为一个数，只与其它数与这个数的大小关系有关。

所以，我们可以对于一个数设比他小的用 `-` 表示，比它大的用 `+` 表示，本身用 `0` 表示。

设用 $b_i$ 表示上述的符号。

容易发现，答案不为 $3$ 只有两种情况： `-+0-+` 和 `+-0+-`。

$O(N)$ 枚举即可。

### 简化题目2

若只询问答案为 $3$ 和 $5$ 的位置，该怎么做？

我们当然可以枚举两遍。

这个地方答案不能说 $3$ 和 $5$，只有两种情况： `-+-+0-+-+` 和 `+-+-0+-+-`。

但是我们发现，如果 $ans_i\neq3$，只有当 $b_{i-4}\neq b_{i-3}$ 且 $b_{i-3}\neq b_{i-2}$ 且 $b_{i+4}\neq b_{i+3}$ 且 $b_{i+3}\neq b_{i+2}$ 时，这里不能是 $5$。

### 简化题目3

若 $N\leq1\times10^4$，按照上面的思路该怎么做？

枚举答案的大小和位置即可，时间复杂度 $O(N^2)$。

### 回到原题

我们发现，答案算出来的位置就可以不用再计算了，据说这样的复杂度是对的，为 $O(N)$。

可以感性证明，如果一个地方的答案很大，那么它的周围就有很多 `-+-+...-+-+0-+-+...-+-+`，或者另一种情况。

但是同时 `-+-` 和 `+-+` 的重复出现，使得答案中有很多的 $3$，所以答案的和不会太大，即枚举次数不会太大。

### 一个特殊情况

特别的，需要注意以下特殊情况：
```
5
3 5 1 2 4
```

显然 $ans_1=-1$，但是，如果你按照上面的思路判断的话，惊奇的发现，求出的 $ans_1=5$，为什么呢？

以上样例对于 $P_1$ 的 $b$ 数组为 `0+--+`，但是我们发现，虽然有两个 `-` 但是并不能取到。

这是因为，对于非开头，比如 $3$ 的左边再有一个比 $3$ 小的数，那么，$b$ 数组就是 `-0+--+` ，显然可以取 $\left[1,5\right]$，作为答案。

即如果右边还有数时，才可以满足中位数不是自己这个限制。

所以对于 $1$ 和 $N$ 两个位置，加一个特判即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int a[N],ans[N];
queue<int> x,y;
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		if(i-2 > 0 && (a[i-2] < a[i]) == (a[i-1] < a[i])){
			ans[i] = 3;
		}else if(i-1 > 0 && i+1 <= n && (a[i-1] < a[i]) == (a[i+1] < a[i])){
			ans[i] = 3;
		}else if(i+2 <= n && (a[i+1] < a[i]) == (a[i+2] < a[i])){
			ans[i] = 3;
		}else{
			x.push(i);
		}
	}
	for(int l=5;l<=n;l+=2){
		while(!x.empty()){
			int i = x.front();
			x.pop();
			if(i-l+1 > 0 && (a[i-l+1] < a[i]) == (a[i-l+2] < a[i])){
				ans[i] = l;
			}
			if(i != n /*注意这个特判*/ && i-l+2 > 0 && (a[i-l+2] < a[i]) == (a[i-l+3] < a[i])){
				ans[i] = l;
			}
			if(i+l-1 <= n && (a[i+l-1] < a[i]) == (a[i+l-2] < a[i])){
				ans[i] = l;
			}
			if(i!= 1 /*注意这个特判*/ && i+l-2 <= n && (a[i+l-2] < a[i]) == (a[i+l-3] < a[i])){
				ans[i] = l;
			}
			if(!ans[i]){
				y.push(i);
			}
		}
		x = y;
		while(!y.empty())y.pop();
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i] == 0?-1:ans[i]);
	}
}
```

---

