# [SEERC 2019] Tree Permutations

## 题目描述

有一天，Cool 先生建了一棵 $n$ 个点的树（没有环的无向连通图），他给任一编号 $i > 1$ 的点规定了两个值：$p_i < i$ 代表点 $i$ 的父节点，与 $w_i$ 代表 $i$ 与 $p_i$ 之间的边的边权。点 $1$ 是树根，所以它没有父节点。

你想知道 Cool 先生建的树长啥样，但是 Cool 先生拒绝告诉你，但他给了你一些提示：

他把所有的 $p_i$ 和 $w_i$ 值写成一列，得到了长为 $2 \cdot n - 2$ 的数列 $b$。

$$ b=[p_2, w_2, p_3, w_3, \dots, p_{n-1}, w_{n-1}, p_n, w_n] $$

然后他将其随机打乱，得到了数列 $a$，并将 $a$ 告诉你。

然而只知道数列 $a$ 是无法还原那棵树的，你决定解决一个更难的问题。

定义一个树是 *$k$ 长*的，当且仅当点 $1$ 到点 $n$ 的路径上有恰好 $k$ 条边。

定义一个树是 *$k$ 完美*的，当且仅当这棵树是 *$k$ 长*的且点 $1$ 到点 $n$ 的路径上的边的边权之和是所有 *$k$ 长*的树中最大的。

你的任务是计算出每个 $k$ 值对应的 *$k$ 完美*的树中，点 $1$ 到点 $n$ 的路径上的边的边权之和。如果某个 $k$ 值不存在 *$k$ 完美*的树，则在该位置输出 $-1$。

## 说明/提示

第一个样例中，*$1$ 完美*的树由数列 $[1, 2, 1, 2]$ 构成（即，$p_2=1, w_2=2, p_3=1, w_3=2$），*$2$ 完美*的树由数列 $[1, 2, 2, 1]$ 构成（即，$p_2=1, w_2=2, p_3=2, w_3=1$）。以下是这两棵树的图形（点 $1$ 到点 $n$ 的路径上的边都为粗线）。

![样例1](https://cdn.luogu.com.cn/upload/image_hosting/lgpg0jne.png)

第二个样例中，不存在能通过重排 $a$ 构造出的 *$k$ 完美*的树。

第三个样例中，只有 *$4$ 完美*的和 *$5$ 完美*的树可以被构造出。它们分别由数列 $[1, 4, 2, 4, 3, 4, 4, 4, 4, 5]$ 和 $[1, 4,2, 4, 3, 4, 4, 4, 5, 4]$ 构成。以下是这两棵树的图形。

![样例3](https://cdn.luogu.com.cn/upload/image_hosting/rz04b4ro.png)

## 样例 #1

### 输入

```
3
1 1 2 2```

### 输出

```
2 3```

## 样例 #2

### 输入

```
3
2 2 2 2```

### 输出

```
-1 -1```

## 样例 #3

### 输入

```
6
1 4 5 4 4 4 3 4 4 2```

### 输出

```
-1 -1 -1 17 20```

# 题解

## 作者：Leasier (赞：3)

首先对 $a$ 排序。

- 若存在 $a_i > i$，则一定无解。

证明：已知 $p_i < i$，但此时构造出的 $p_{i + 1} > i$，则不合法。

- 所有 $a_i = i$ 的 $i$ 一定在 $1 \to n$ 的路径上。

证明：此时任何从 $\leq i$ 的点到 $> i$ 的点的路径都要经过 $i$。

- $1 \to n$ 的路径长度大于等于 $a_i = i$ 的 $i$ 的个数且小于等于 $a$ 去重后的元素个数。

证明：由上一条以及 $p_i < i$ 可得。

- 设上一条中确定的上下界为 $[l, r]$，则 $\forall k \in [l, r]$ 均存在满足条件的树。

证明：我们可以构造如下一棵树：

- $1 \to n$ 的路径的父亲序列由 $a_i = i$ 的 $i$（设其有 $i$ 个）、其他元素中互异且前 $k - cnt$ 小者组成。
- $1 \to n$ 的路径的边权序列由余下元素中前 $k$ 大组成。
- 其他信息由余下元素组成。

而我们构造出的树同样满足权值最大的性质，于是我们维护一棵支持单点删除、求前 $k$ 大的线段树即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;

typedef struct {
	int l;
	int r;
	int cnt;
	ll sum;
} Node;

int a[200007], b[200007], diff[100007];
bool mark[100007], vis[100007];
Node tree[800007];

inline void update(int x){
	int ls = x * 2, rs = x * 2 + 1;
	tree[x].cnt = tree[ls].cnt + tree[rs].cnt;
	tree[x].sum = tree[ls].sum + tree[rs].sum;
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r){
		tree[x].cnt = 1;
		tree[x].sum = b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	update(x);
}

void erase(int x, int pos){
	if (tree[x].l == tree[x].r){
		tree[x].cnt = tree[x].sum = 0;
		return;
	}
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		erase(x * 2, pos);
	} else {
		erase(x * 2 + 1, pos);
	}
	update(x);
}

ll get_sum(int x, int k){
	if (tree[x].cnt == k) return tree[x].sum;
	int ls = x * 2;
	if (k <= tree[ls].cnt) return get_sum(ls, k);
	return get_sum(x * 2 + 1, k - tree[ls].cnt) + tree[ls].sum;
}

int main(){
	int n, m, mink = 0, cnt = 0, maxk = 0;
	cin >> n;
	m = (n - 1) * 2;
	for (register int i = 1; i <= m; i++){
		cin >> a[i];
	}
	sort(a + 1, a + m + 1);
	for (register int i = 1; i <= m; i++){
		if (a[i] > i){
			for (register int j = 1; j < n; j++){
				cout << -1 << " ";
			}
			return 0;
		}
		if (a[i] == i){
			mink++;
			mark[a[i]] = true;
		} else {
			b[++cnt] = a[i];
		}
		if (!vis[a[i]]){
			vis[a[i]] = true;
			maxk++;
		}
	}
	if (mink >= n || mink > maxk){
		for (register int i = 1; i < n; i++){
			cout << -1 << " ";
		}
		return 0;
	}
	reverse(b + 1, b + cnt + 1);
	for (register int i = cnt, j = 0; i >= 1; i--){
		if (!mark[b[i]] && b[i] != b[i + 1]) diff[++j] = i;
	}
	build(1, 1, cnt);
	for (register int i = 1; i < mink; i++){
		cout << -1 << " ";
	}
	for (register int i = mink; i <= maxk; i++){
		if (i > mink) erase(1, diff[i - mink]);
		cout << get_sum(1, i) << " ";
	}
	for (register int i = maxk + 1; i < n; i++){
		cout << -1 << " ";
	}
	return 0;
}
```

---

## 作者：win114514 (赞：1)

性质结论题。

### 思路

以下的性质都是在 $a_i$ 有序的情况下拥有的。

**性质一：**

有解的必要条件为 $\forall i\in[1,n-1],a_i\le i$。

> 证明：
> 如果存在 $a_i>i$，那么点 $i+1$ 在前 $i$ 个点合法的前提下无法找到一个父亲，所以无法形成一棵树。

**性质二：**

在有解的情况下，对于 $a_i=i,i\in[1,n-1]$，点 $i$ 必定在 $1\sim n$ 的路径上。

> 证明：
> 如果 $a_i=i$，那么点 $i+1$ 及后面的点的父亲节点的编号必然不小于 $i$，所以一定会经过点 $i$。

**性质三：**

$1\sim n$ 的路径上的点数不会超过 $a$ 的种类数。

> 证明：
> 显然。

**推论：**

在满足性质一，性质二的前提下，任意一条合法的 $1\sim n$ 的路径都可以对应到一个树上。

所以我们就只需要贪心的往路径中添加最小的点，查询最大的点的和就可以了。

时间复杂度：$O(n\log n)$。

### Code

```cpp
/*
  ! 以渺小启程，以伟大结束。
  ! Created: 2024/06/29 20:55:24
*/
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 200010;
const int M = 131072;

using i64 = long long;

int n, m, tp, ct, a[N], b[N], v[N];
int sz[M << 1];
i64 vl[M << 1], ans[N];

inline void FAIL() { fro(i, 1, n - 1) cout << -1 << " "; exit(0); }
inline void add(int x, int c) { x += M; while (x) vl[x] += c, sz[x]++, x >>= 1; }
inline void del(int x, int c) { x += M; while (x) vl[x] -= c, sz[x]--, x >>= 1; }
inline auto ask(int p) {
  i64 t = 1, res = 0;
  while (p != 0) {
    if (t > M) res += (t - M) * p, p = 0;
    else if (p == sz[t]) res += vl[t], p -= sz[t];
    else if (p <= sz[t << 1 | 1]) t = t << 1 | 1;
    else res += vl[t << 1 | 1], p -= sz[t << 1 | 1], t = t << 1;
  }
  return res;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n, m = n * 2 - 2;
  fro(i, 1, m) cin >> a[i], b[a[i]] = 1;
  sort(a + 1, a + m + 1);
  fro(i, 1, m) add(a[i], a[i]);
  fro(i, 1, n - 1) if (a[i] > i) FAIL();
  fro(i, 1, n - 1) if (a[i] == i) v[i] = 1, ct++, del(i, i);
  fill(ans + 1, ans + n, -1);
  fro(i, 1, n - 1) {
    if (b[i] && v[i] == 0) del(i, i), v[i] = 1, ct++;
    ans[ct] = ask(ct);
  }
  fro(i, 1, n - 1) cout << ans[i] << " \n"[i == n - 1];
  return 0;
}
```

---

## 作者：Sharpsmile (赞：1)

# P5803 [SEERC2019] Tree Permutations 

模拟赛考的，猜性质选手赢麻了。找到这个题的原因是同学在主页上看到了大佬建议给这个题评难度的帖子点进去发现是模拟赛的原题。

## 题意 

有一颗以 $1$ 为根的有根树，对于点 $1<i\leq n$ ，其父亲是 $p_i\leq i-1$，和父亲之间边的权值是 $w_i\leq n-1$。现在给定了一个长度为 $2n-2$ 的数组 $b$，是把  打乱之后得到的。

定义一棵树是合法的，当且仅当这棵树的 $\{p_2,\cdots p_n,w_2,\cdots w_n\}$ 通过任意方式排列可以得到 $b$。

定义 $f_k$ 表示所有合法的树中，点 $n$ 的深度恰为 $k$（$1$ 的深度为 $0$），从 $n$ 到 $1$ 路径上边权和的最大值。

## 解法
不妨令 $cnt_i$ 为 $i$ 在 $b$ 中出现的次数，$pre_i$ 为 $cnt_i$ 的前缀和。

首先我们考虑确定 $p$ 长啥样。或者说我们不需要确定 $p$ 的全貌，我们只需要知道 $1-n$ 的链长成啥样即可。因为在选好这个链之后，$p$ 剩下的部分我们只需要贪心的取最小的一些即可。因为这样即可以尽量满足 $p_i\leq i-1$ 的性质，同时剩下用于赋边权的部分也可以尽量大。

同时因为 $p_i\leq i-1$，也就是每个点可以匹配上一个前缀，所以一个必要的要求就是 $pre_i\geq i$，此时我们贪心按照顺序依次取最小的即可，否则一定不行。

我们考虑如何取这个链，会发现这实际上就是相当于是选出若干点 $s_1,s_2,\cdots s_k,s_{k+1}$ ，满足 $s_1=1,s_{k+1}=n$ 然后使  $p_{s_i+1}=p_{s_i}$。

而我们这样 “跳跃” 着选择这些路径上的点，相对于贪心的取，显然是会影响到一些点的。具体的，我们选择 $s_i$ 之后，$(s_i,s_{i+1})$ 这部分的可以匹配的前缀中就会少一个，但是对 $s_{i+1}$ 之后没有影响。

那么通过全局来看，也就是所有没有被选择的点的选择会少一个。

这意味着所有满足 $pre_{i-1}={i-1}$ 的 $i$，都必须被选择，而剩下的只要满足 $cnt_i\not =0$ 也可以被选择（除了 $n$ 和 $1$，$n$ 因为不会被后面指向所以可以无视 $cnt$ 限制，$1$ 因为是根，如果没有 $1$ 显然全局无解）。

所以记 $l$ 为 $pre_{i-1}=i-1$ 的位置数量，$t$ 为 $pre_{i-1}>i-1,cnt_i>0$ 的数量，那么有且仅有 $k\in[l,l+t]$ 时有解。

再贪一下心，那些可以选择在不在链上的点，被选已经不会再影响 $n$ 深度为 $k$ 的树是否存在了。那么我们在加入这些点的时候从小到大加显然是最优的。

然后考虑维护边权，我们想要知道，现在剩下的元素中，最大的 $k$ 个的和。可以使用各种数据结构 $\log$ 解决。

但是考虑一个性质。就是我们的 $k$ 是递增的。我们维护一个指向当前用到的最小元素的指针，当前使用的元素个数 $ct$，答案 $now$，再开一个桶维护当前元素剩余的个数。

如果当前的元素个数不够，就移那个指针然后用桶维护一下每个位置能加多少直到够了为止。然后我们会发现需要删除一些元素。会发现删除的元素不重复且至少出现过一次，如果当前被删除的元素大于指针指向的，也就是他为 $now$ 做了贡献，就减掉他的一份贡献的同时，$ct-\rightarrow ct-1$，然后继续更新即可。

这样均摊复杂度就是线性的，现在是最优解。

赛时代码很丑陋。

```cpp
//#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <istream>
#include <string>
#include <queue>
#include <deque>
#include <random>
#include <stack>
#include <set>
#include <string.h>
#include <map>
#include <unordered_map>
#include <sstream>
#include <bitset>
#include <fstream>
#include <climits>
#include <time.h>
using namespace std;
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")

//#include "atcoder/all"
// using namespace atcoder;

#define endl "\n"
#define int long long
#define double long double
#define pii pair<int, int>
#define p1(x) (x).first
#define p2(x) (x).second
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define i128 __int128_t
int n;
int cnt[100030];
int sc[100030];
bool vis[100030];
int NOW;
vector<int> T;
int ct = 0;
int lim;
int res = 0;
inline void upd() {
    while (ct) {
        if (!cnt[lim])
            lim--;
        int t = min(ct, cnt[lim]);
        cnt[lim] -= t;
        ct -= t;
        res += t * lim;
    }
}
inline void slv() {
    cin >> n;
    lim = n;
    vector<int> E;
    for (int i = 1; i <= 2 * n - 2; i++) {
        int x;
        cin >> x;
        cnt[x]++;
        sc[x]++;
    }
    E.push_back(1);
    NOW = 1;
    for (int i = 1; i < n; i++) {
        sc[i] += sc[i - 1];
        if (sc[i] == i)
            E.push_back(i + 1), vis[i + 1] = 1, cnt[i + 1]--, NOW++;
        else if (sc[i] < i) {
            for (int i = 1; i <= n - 1; i++) cout << -1 << " ";
            return;
        }
    }
    E.push_back(n);
    int lst = 1;
    for (int x : E) {
        for (int i = lst + 1; i < x; i++)
            if (cnt[i])
                T.push_back(i);
        lst = x;
    }
    auto it = T.begin();
    ct = NOW;
    for (int i = 1; i <= n - 1; i++) {
        if (NOW < i && it != T.end()) {
            NOW++, vis[*it] = 1;
            ct++;
            if (!cnt[*it])
                ct++, res -= *it;
            else
                cnt[*it]--;
            it++;
        }
        if (NOW != i)
            cout << -1 << " ";
        else {
            upd();
            cout << res << " ";
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    // freopen("serialize.in", "r", stdin);
    // freopen("serialize.out", "w", stdout);
    slv();
    cout.flush();
    return 0;
}
/*
 */
```


---

## 作者：_Cheems (赞：0)

题意：有一个 $n$ 个点的树，根为 $1$。记 $p_i<i$ 为 $i$ 的父亲，$w_i$ 为父亲边权。现将 $p,w$ 随机打乱得到 $a$，对每个 $k\in [1,n)$，当 $1\to n$ 路径上有 $k$ 条边，输出最长长度或报告无解。$n\le 10^5$。

将 $a$ 排序。首先初始思路是找出 $x_1\dots x_k$，其中 $x_1=1,x_i<x_{i+1}$，也就是 $1\to n$ 的链，然后在剩下的元素中贪心选取最小的构成 $p$。那么问题是怎么确定 $x$。

尝试观察性质，不断强化条件，从而推出正解：

1. $\forall i,a_{i}<i$ 否则无解。显然。
2. 若 $a_i=i$，则 $i$ 一定在 $1\to n$ 路径上。证明：对于 $j\in [2,i]$，只能选取 $a_1\dots a_{i-1}$ 作为父亲节点，所以 $j\in [i+1,n]$ 无法一步跳到 $[1,i-1]$，所以必然经过 $i$。
3. $k=\sum [a_i=i]$ 时一定有解。证明：首先让他们构成 $1\to n$ 的链，然后考虑剩下的点，对于 $j\in (x_i,x_{i+1})$，都有 $a_j<j$，所以一定有解。构造方案即为选取剩下的 $a$ 中最小的那些。
4. 记 $mx$ 为 $a$ 不同元素个数，则有 $k\le mx$。显然。
5. 对于 $\sum[a_i=i]\le k\le mx$ 均有解。证明：增量法，每次选取剩下元素中最小且与 $x$ 不同的元素加入 $1\to n$ 链上，则剩下的节点一定有相应的 $p$ 可匹配。因为考虑拿走的元素 $y$，设 $q$ 为 $y$ 此前对应的 $p$，设拿走 $y$ 后节点 $z$ 失去对应 $p$，由于 $q<y<z$ 所以让 $z$ 与 $q$ 匹配即可。

综上，恰在区间内的 $k$ 才有解。每次删去新增元素，并选取剩下的前 $k$ 大作为链边权即可。可以做到 $O(n)$，但我偷懒用线段树 $O(n\log n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n, m, a[N], buc[N], cnt;
bool vis[N];
vector<int> del; 

namespace Sg_Tree{
	#define lt (u << 1)
	#define rt (u << 1 | 1)
	#define mid (l + r >> 1)
	int t[N << 2], s[N << 2];
	
	inline void psup(int u) {t[u] = t[lt] + t[rt], s[u] = s[lt] + s[rt];}
	inline void upd(int u, int l, int r, int k, int p){
		if(l == r) {t[u] += k * p, s[u] += p; return ;}
		if(k <= mid) upd(lt, l, mid, k, p);
		else upd(rt, mid + 1, r, k, p);
		psup(u);
	}
	inline int fid(int u, int l, int r, int k){
		if(l == r) return l * k;
		if(s[rt] <= k) return t[rt] + fid(lt, l, mid, k - s[rt]);
		return fid(rt, mid + 1, r, k);
	}
}using namespace Sg_Tree;
signed main(){
	cin >> n, m = 2 * n - 2;
	for(int i = 1; i <= m; ++i) scanf("%d", &a[i]), ++buc[a[i]], upd(1, 1, n, a[i], 1);
	sort(a + 1, a + 1 + m);
	for(int i = 1; i <= m; ++i){
		if(a[i] > i) {for(int i = 1; i < n; ++i) printf("-1 "); return 0;}
		if(a[i] == i){
			vis[i] = true;
			--buc[a[i]], upd(1, 1, n, a[i], -1), ++cnt;
		}
	}
	for(int i = 1; i < cnt; ++i) printf("-1 ");
	if(cnt) printf("%lld ", fid(1, 1, n, cnt));
	for(int i = 1; i < n; ++i) 
		if(buc[i] && !vis[i]){
			upd(1, 1, n, i, -1), ++cnt;
			printf("%lld ", fid(1, 1, n, cnt));
		}
	for(int i = cnt + 1; i < n; ++i) printf("-1 ");
	return 0;
}
```

---

