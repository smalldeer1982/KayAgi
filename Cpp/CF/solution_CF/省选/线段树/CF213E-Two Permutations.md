# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 样例 #1

### 输入

```
1 1
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 2
1
2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3
```

### 输出

```
0
```

# 题解

## 作者：ywy_c_asm (赞：10)

这题好妙啊……

我们考虑枚举$x$的值，接下来就要判定把排列$a$加上$x$之后在$b$里的先后顺序是否不变。

注意到一个事实就是此时$a$的**值域**完全是$[1+x,n+x]$这段区间，那么我们对$b$搞出一个下标为值的数组$f[i]$表示$i$这个数在$b$中的出现位置，显然我们现在就只需考虑$f[1+x…n+x]$这一段了。

那么接下来的做法就很显然了，开个平衡树按照$f[i]$维护$[1+x,n+x]$这一段数（因为我们相当于是滑动窗口这一段，直接插入删除即可），然后我们要判断这个平衡树存的序列是否等于$a$排列全都加上$x$，考虑平衡树维护$Hash$，然后$a+x$的$Hash$显然就是$Hash(a)+x\sum_{i=1}^nk^i$，就可以比较了，这题就做完了。$O(n\log n)$。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p1 998244353
#define p2 1000000007
#define dk 1000003ll
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll dk1[200001], dk2[200001];
	int ch[300001][2], tmp[300001], gptr = 1, size[300001];
	unsigned char isdel[300001];
	int sz[300001], a[200001], b[200001], fan[200001];
	ll h1[300001], h2[300001];
	inline void up(int tree) {
	    size[tree] = size[ch[tree][0]] + size[ch[tree][1]] + 1;
	    sz[tree] = sz[ch[tree][0]] + sz[ch[tree][1]] + (!isdel[tree]);
	    if (isdel[tree]) {
	        h1[tree] = (h1[ch[tree][0]] * dk1[sz[ch[tree][1]]] + h1[ch[tree][1]]) % p1;
	        h2[tree] = (h2[ch[tree][0]] * dk2[sz[ch[tree][1]]] + h2[ch[tree][1]]) % p2;
	    } else {
	        h1[tree] = (((h1[ch[tree][0]] * dk + tree) % p1) * dk1[sz[ch[tree][1]]] + h1[ch[tree][1]]) % p1;
	        h2[tree] = (((h2[ch[tree][0]] * dk + tree) % p2) * dk2[sz[ch[tree][1]]] + h2[ch[tree][1]]) % p2;
	    }
	}
	void dfs(int tree) {
	    if (!tree)
	        return;
	    dfs(ch[tree][0]);
	    if (!isdel[tree])
	        tmp[gptr] = tree, gptr++;
	    dfs(ch[tree][1]);
	}
	int build(int l, int r) {
	    if (l > r)
	        return (0);
	    int mid = (l + r) >> 1, tree = tmp[mid];
	    ch[tree][0] = build(l, mid - 1);
	    ch[tree][1] = build(mid + 1, r);
	    up(tree);
	    return (tree);
	}
	void insert(int &tree, int me) {
	    if (!tree) {
	        tree = me;
	        up(me);
	        return;
	    }
	    insert(ch[tree][fan[me] > fan[tree]], me);
	    up(tree);
	    if (max(size[ch[tree][0]], size[ch[tree][1]]) >= (double)size[tree] * 0.66) {
	        gptr = 1;
	        dfs(tree);
	        tree = build(1, gptr - 1);
	    }
	}
	void del(int tree, int me) {
	    if (tree == me) {
	        isdel[me] = 1;
	        up(tree);
	        return;
	    }
	    del(ch[tree][fan[me] > fan[tree]], me);
	    up(tree);
	}
	void ywymain() {
	    int n = get(), m = get();
	    dk1[0] = dk2[0] = 1;
	    for (register int i = 1; i <= m; i++) {
	        dk1[i] = (dk1[i - 1] * dk) % p1;
	        dk2[i] = (dk2[i - 1] * dk) % p2;
	    }
	    ll ha1 = 0, ha2 = 0, kd1 = 0, kd2 = 0;
	    for (register int i = 1; i <= n; i++) {
	        int x = get();
	        ha1 = (ha1 * dk + x) % p1;
	        ha2 = (ha2 * dk + x) % p2;
	        kd1 = (kd1 * dk + 1) % p1;
	        kd2 = (kd2 * dk + 1) % p2;
	    }
	    for (register int i = 1; i <= m; i++) fan[get()] = i;
	    int rt = 0;
	    for (register int i = 1; i < n; i++) insert(rt, i);
	    int ans = 0;
	    for (register int i = 0; i <= m - n; i++) {
	        insert(rt, n + i);
	        if ((ha1 + kd1 * i) % p1 == h1[rt]) {
	            if ((ha2 + kd2 * i) % p2 == h2[rt])
	                ans++;
	        }
	        del(rt, 1 + i);
	    }
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：MorsLin (赞：10)

因为我们要比较区间，所以先将$a$排列 hash  
注意，因为$a$是一个排列，所以它里面的元素一定是从$1$~$n$的，所以，我们可以使``pos[b[i]] = i``，然后判断``pos[i-n+1]``~``pos[i]``和$a$排列是否符合要求  
这里的符合要求包括：
1. ``pos[i-n+1]``~``pos[i]``减去$x$等于$a$排列
2. ``b[pos[i-n+1]]``~``b[pos[i]]``是$b$的子序列

而这两个要求都可以通过计算``b[pos[i-n+1]]``~``b[pos[i]]``在原排列里构成的子序列的hash值来判断  
之后我们要做的就是快速的求出``b[pos[i-n+1]]``~``b[pos[i]]``在原排列$b$中构成的子序列的hash值  
因为$b_i$并不连续，用线段树维护hash值  
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ULL unsigned long long
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;
int read() {
    int k = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
      k = k * 10 + c - 48, c = getchar();
    return k * f;
}
int a[200010], b[200010], pos[200010], ans;
ULL hasha, qpow[200010] = {1}, sum;
struct zzz{
    ULL a, tot;
}tree[200010 << 2];
void up(int l, int r, int p) {
    tree[p].tot = tree[ls].tot + tree[rs].tot;
    tree[p].a = tree[ls].a * qpow[tree[rs].tot] + tree[rs].a;
}
void update(int l, int r, int pos, int p, int k) {
    if(l == r) {
        if(!k) tree[p].tot -= 1;
        else tree[p].tot += 1;
        tree[p].a = k; return ;
    }
    if(pos <= mid) update(l, mid, pos, ls, k);
    if(pos > mid) update(mid+1, r, pos, rs, k);
    up(l, r, p);
}
int main() {
    int n = read(), m =read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read(), hasha = hasha * 23 + a[i];
        qpow[i] = qpow[i-1] * 23;
        sum += qpow[i-1];
    }
    for(int i = 1; i <= m; ++i) b[i] = read(), pos[b[i]] = i;
    for(int i = 1; i <= m; ++i) {
        if(i > n) update(1, m, pos[i-n], 1, 0);
        update(1, m, pos[i], 1, i);
        int d = i - n;
        if(d >= 0 && tree[1].a == d*sum+hasha) ++ans;
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：7)

首先把重要的放前面，防止大家踩坑。

单哈希一定要用 `unsigned long long` 自然溢出！！

~~我是不会告诉你我试了 $15$ 个模数的。~~

------------

首先将 $a$ 哈希一下。然后考虑每次加 $x$，原数列变成 $\{ a_i + x\}$，它的哈希变成 $\sum \limits_{i = 1}^{n} (a_i + x) \times p ^ {n - i} = \sum \limits_{i = 1}^{n} a_i \times p ^ {n - i} + x \sum \limits_{i = 1}^{n} p ^ {n - i}$。设 $s = \sum \limits_{i = 1}^{n} p ^ {n - i}$，则新的哈希就是原哈希 $ + xs$。

枚举 $x \in [0, m - n]$，计算出 $\{ a_i + x\}$ 的哈希并存储。可以搞个 `map / unordered_map` 之类的存。

接下来该解决 $b$ 序列的匹配问题了。考虑到 $a$ 是一个排列，那么 $b$ 的合法子序列一定是排序后连续的。考虑将 $b$ 按照权值排序，然后按照权值插入空序列，插入位置为其在原序列位置，即保持原偏序不变。然后每插入一次求一边当前哈希，看看 `map / unordered_map` 中有没有对应的 $a$ 序列。如果当前序列 $b$ 构造的新序列长度大于 $n$，那么就删除新序列中权值最小的点。

要求支持插入和删除操作，显然一个权值线段树就能搞。由于平衡树太难写了，所以我拿权值线段树实现的。时间复杂度 $O(n \log n)$。我在这里假设 $n, m$ 同阶。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

#define int long long

using namespace std;

using ULL = unsigned long long;
using PII = pair<int, int>;
const int N = 200010;
const int P = 23;

int n, m, a[N], b[N], ans;
ULL h1[N], p[N], Base;
map<ULL, bool> Map;
PII tmp[N];

struct node {
	int l, r;
	ULL hash;
	int size;
}tr[N << 2];
#define ls u << 1
#define rs u << 1 | 1

void pushup(int u) {
	tr[u].size = tr[ls].size + tr[rs].size;
	tr[u].hash = (ULL)tr[rs].hash + tr[ls].hash * p[tr[rs].size];
}
void build(int u, int l, int r) {
	tr[u] = {l, r, 0, 0};
	if (l == r) return;
	int mid = l + r >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}
void insert(int u, int x, int v) {
	if (tr[u].l == tr[u].r) {
		tr[u].hash = v; tr[u].size = 1;
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) insert(ls, x, v);
	else insert(rs, x, v);
	pushup(u);
}
void remove(int u, int x) {
	if (tr[u].l == tr[u].r) {
		tr[u].hash = tr[u].size = 0;
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) remove(ls, x);
	else remove(rs, x);
	pushup(u);
}
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &a[i]);
	for (int i = 1; i <= m; i ++ )
		scanf("%lld", &b[i]);
	p[0] = 1;
	for (int i = 1; i <= n; i ++ )
		h1[i] = h1[i - 1] * P + a[i];
	for (int i = 1; i <= m; i ++ )
		p[i] = p[i - 1] * P;
	for (int i = 0; i < n; i ++ )
		Base = Base + p[i];
	for (int i = 0; i <= m - n; i ++ )
		Map[h1[n] + Base * i] = true;
	
	for (int i = 1; i <= m; i ++ )
		tmp[i] = {b[i], i};
	sort(tmp + 1, tmp + m + 1);
	build(1, 1, m);
	for (int i = 1; i <= n; i ++ )
		insert(1, tmp[i].second, tmp[i].first);
	for (int i = n + 1; i <= m; i ++ ) {	
		int hash = tr[1].hash;
		if (Map[hash]) ans ++ ;
		remove(1, tmp[i - n].second);
		insert(1, tmp[i].second, tmp[i].first);
	}
	if (Map[tr[1].hash]) ans ++ ;
	printf("%lld\n", ans);
	return 0;
}
```

我试了 $P = 13, 23, 1331$，$mod = 998244353, 10 ^ 9 + 7, 10 ^ 9 + 9, 999988883$ 都被卡了。然而自然溢出却可以过。我只能说我谔谔。

---

## 作者：CaoXian (赞：5)

题目要求的是新的 $a$ 序列是 $b$ 序列的**子序列**的个数！而不是子串（或者连续子序列）。我因为读错题调 KMP 调了一个小时。

如果要求的是子串那做法就大不相同了。

进入正题，首先思考没有 $+ x$ 的操作时怎么做。

因为 $a$ 序列和 $b$ 序列都是**排列**，所以出现的元素一定是 $1 \sim n$ 和 $1 \sim m$ 并且每种元素正好出现一次。

利用这一点我们可以把 $b$ 序列中没有在 $a$ 序列中出现过的元素排除掉。

具体地，我们需要只把 $b$ 序列中属于 $[1, n]$ 的元素按照原来的相对顺序保存下来即可。

做完这一步后，我们已经把一个**可能符合要求的子序列**提取出来了。

因为若出现了别的元素那么一定不会符合题目要求。

接下来需要我们判断这个子序列是否和 $a$ 相同，我们可以 $\mathcal{O}(n)$ 地扫一遍，但是在 $n$ 很大的时候效率会非常低。

尝试改成哈希，我们就将判断的时间复杂度从 $\mathcal{O}(n)$ 降到了 $\mathcal{O}(1)$，但是相应地，预处理的时间复杂度就从 $\mathcal{O}(1)$增长到了 $\mathcal{O}(n)$。（这里指的是比较两序列是否相同的时间复杂度，不包括前文提到的提取子序列的复杂度。）

乍一看改成哈希没有什么优化，但是这仅仅是不考虑 $+ x$ 操作的情况。

这时候把题目给的 $+ x$ 操作加上来。

如果对原序列所有元素都 $+ x$，对序列哈希值的贡献就是：

$$
x\times\sum\limits_{i = 1}^{n}base^{i - 1}
$$

这里的 $\sum\limits_{i = 1}^{n}base^{i - 1}$ 可以提前计算，更改时只需要乘上 $x$ 就好。

这样，我们就做到了 $\mathcal{O}(n)$ 预处理，$\mathcal{O}(1)$ 更改哈希值和 $\mathcal{O}(1)$ 比较了。

然后就是考虑如何快速提取 $b$ 中的子序列。

注意到前文所述的“把 $b$ 序列中属于 $[1, n]$ 的元素按照原来的相对顺序保存下来”，假设 $x = 1$，那么我们要保存的元素区间就是 $[2, n + 1]$ 了。

因为 $b$ 序列是排列，所以范围区间 $[1, n]$ 到 $[2, n + 1]$ 只会引起删除掉一个元素和加入一个新的元素的变化。

又因为 $b$ 序列是静态的，所以属于 $[2, n]$ 的元素的相对顺序不会变化，我们们只需要先删除掉 $1$ 元素，再找到 $n + 1$ 元素应该处于的位置插入即可，删除和插入的时候同时维护一下序列哈希值。

类似的，我们可以从 $[1, n]$ 变为 $[2, n + 1]$ 推广到 $[l, r]$ 变为 $[l + 1, r + 1]$，具体步骤不再阐述。

我们需要一个动态维护序列的，可以快速删除指定位置元素，快速在指定位置插入元素的数据结构，平衡树可以满足这些要求。

对于处理出一个元素应该在子序列中的哪个位置，只需要知道在它前面有多少个元素即可，这一点可以用树状数组实现，为了方便操作以及优化时间复杂度，可以提前按照元素从小到大的顺序为 $b$ 序列排序，同时要保存元素在原 $b$ 序列的位置。

给出代码实现（双哈希+平衡树+树状数组）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod1 = 998244353, mod2 = 1000000007, mul1 = 299983, mul2 = 19260817;
int n, m, ans, l, mid, r, pos, a[200005], b[200005], c[200005], rnk[200005];
ll state1, state2, add1, add2, power1[200005], power2[200005];
struct FHQ_Treap {
	struct node {
		ll v1, v2, len;
		node(ll V1 = 0, ll V2 = 0, ll Len = 0): v1(V1), v2(V2), len(Len) {}
		node operator = (const node& _) {
			v1 = _.v1, v2 = _.v2, len = _.len;
			return *this;
		}
		node operator + (const node& _) const {
			return node((_.v1 + v1 * power1[_.len] % mod1) % mod1, (_.v2 + v2 * power2[_.len] % mod2) % mod2, len + _.len);
		}
	} hsh[200005];
	int idx, root, lc[200005], rc[200005], val[200005], size[200005], priority[200005];
	int new_node(ll v = 0) {
		++idx;
		hsh[idx] = node(v, v, 1), val[idx] = v, lc[idx] = rc[idx] = 0, size[idx] = 1;
		priority[idx] = rand();
		return idx;
	}
	void push_up(int cur) {
		size[cur] = size[lc[cur]] + size[rc[cur]] + 1;
		hsh[cur] = hsh[lc[cur]] + node(val[cur], val[cur], 1) + hsh[rc[cur]];
	}
	void split(int cur, int rank, int& l, int& r) {
		if(!cur) return (l = r = 0, void());
		if(size[lc[cur]] < rank) {
			l = cur;
			split(rc[cur], rank - size[lc[cur]] - 1, rc[cur], r);
		}
		else {
			r = cur;
			split(lc[cur], rank, l, lc[cur]);
		}
		push_up(cur);
	}
	int merge(int curl, int curr) {
		if(!curl || !curr) return curl | curr;
		if(priority[curl] < priority[curr]) {
			rc[curl] = merge(rc[curl], curr);
			push_up(curl);
			return curl;
		}
		else {
			lc[curr] = merge(curl, lc[curr]);
			push_up(curr);
			return curr;
		}
	}
} treap;
int lowbit(int x) {return x & -x;}
void change(int x, int v) {
	while(x <= 200000) c[x] += v, x += lowbit(x);
}
int ask(int x) {
	int ret = 0;
	while(x) ret += c[x], x -= lowbit(x);
	return ret;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	srand(time(nullptr));
	cin >> n >> m;
	power1[0] = power2[0] = 1;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		state1 = (state1 * mul1 + a[i]) % mod1;
		state2 = (state2 * mul2 + a[i]) % mod2;
		power1[i] = power1[i - 1] * mul1 % mod1;
		power2[i] = power2[i - 1] * mul2 % mod2;
		add1 = (add1 + power1[i - 1]) % mod1;
		add2 = (add2 + power2[i - 1]) % mod2;
	}
	for(int i = 1; i <= m; ++i) {
		cin >> b[i];
		rnk[i] = i;
	}
	stable_sort(rnk + 1, rnk + 1 + m, [&](int p1, int p2) -> bool {return b[p1] < b[p2];});
	for(int i = 1; i <= m; ++i) {
		if(i > n) {
			pos = ask(rnk[i - n]);
			change(rnk[i - n], -1);
			treap.split(treap.root, pos, l, r);
			treap.split(l, pos - 1, l, mid);
			treap.root = treap.merge(l, r);
		}
		pos = ask(rnk[i]);
		change(rnk[i], 1);
		treap.split(treap.root, pos, l, r);
		treap.root = treap.merge(treap.merge(l, treap.new_node(i)), r);
		if(i >= n) {
			if(treap.hsh[treap.root].v1 == state1 && treap.hsh[treap.root].v2 == state2) ++ans;
			state1 = (state1 + add1) % mod1;
			state2 = (state2 + add2) % mod2;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Meteor_ (赞：3)

# CF213E Two Permutations 题解

## 题目大意

给出两个排列 $a, b$，长度分别为 $n, m$，你需要计算有多少个 $x$，使得 $a_1 + x, a_2 + x, \dots, a_n + x$ 是 $b$ 的子序列

$n \leq m \leq 2 \times 10^5$

## 分析

挺不错的一道题。

判断两个排列是否相同，不难想到哈希。动态维护哈希值，不难想到线段树。

## 题解

其实分析里已经把思路说的差不多了，就是动态维护哈希值并判断是否相等。

可以发现，$x$ 一定不会很大，具体来说，$x \in [0, m - n]$。

所以我们可以枚举每一个 $x$，判断在排列 $b$ 中，值域在 $[x, n + x]$ 里的子序列构成的哈希值与 $a$ 排列的哈希值是否相等。

主要来说说每次让 $x$ 加一时两个排列的哈希值怎么变。

设一个排列 $p$ 的哈希值 $Hash_p = base^{n - 1} \times p_1 + base^{n - 2} \times p_2 + \dots + base^0 \times p_n$。

每次 $x$ 加一时，$Hash_a$ 会加上 $base^{n - 1} + base^{n - 2} + \dots + base^0$，这个不难发现。而这个值我们可以预处理出来，每次直接加就行。

$Hash_b$ 的变化比较复杂。我们把 $b$ 序列的哈希值拆分到各个数上去维护，具体来说，如果一个值 $b_i$ 在当前排列的值域中，那么此位置的 $has_i$ 就等于 $base^{cnt} \times b_i$，$cnt$ 表示在 $i$ 右边的、也在这个排列中的数的个数；如果一个数不在当前排列的值域，那么 $has_i = 0$。而 $Hash_b = \sum_{i = 1}^{m} has_i$。由于值域发生变化，有一个值 $b_j$ 需要被移出排列，那么在位置 $j$ 之前的所有的位置的哈希值都需要除以 $base$；还有一个值 $b_k$ 需要被加入排列，那么在位置 $k$ 之前的所有位置的哈希值都需要乘上 $base$。

所以这就是个线段树，支持区间乘，区间个数查询（就是上述的 $cnt$），区间和查询。

答案就很容易得出来了，$ans = \sum_{x = 0}^{m - n} [Hash_a = Hash_b]$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int M = 200005;
const int mod = 1e9 + 21;
const int base = 13331;
int n, m, a[M], stand, b[M], loc[M], ans, has[M], inv, tmp;
int sum[M << 2], lazy[M << 2], cnt[M << 2];

inline int quick_pow(int base, int ci, int pp) {
    int res = 1;
    while(ci) {
        if(ci & 1)
            res = res * base % pp;
        base = base * base % pp;
        ci >>= 1;
    }
    return res;
}

inline void push_down(int rt) {
    if(lazy[rt] != 1) {
        int ls = rt << 1, rs = ls | 1;
        sum[ls] = sum[ls] * lazy[rt] % mod;
        sum[rs] = sum[rs] * lazy[rt] % mod;
        lazy[ls] = lazy[rt] * lazy[ls] % mod;
        lazy[rs] = lazy[rt] * lazy[rs] % mod;
        lazy[rt] = 1;
    }
}

void build(int rt, int l, int r) {
    sum[rt] = 0;
    lazy[rt] = 1;
    if(l == r)
        return;
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}

int ask(int rt, int l, int r, int zuo, int you) {
    if(zuo <= l && r <= you) 
        return cnt[rt];
    push_down(rt);
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1, res = 0;
    if(zuo <= mid)
        res = ask(ls, l, mid, zuo, you);
    if(you > mid)
        res = (res + ask(rs, mid + 1, r, zuo, you)) % mod;
    sum[rt] = (sum[ls] + sum[rs]) % mod;
    return res;
}

void add(int rt, int l, int r, int zuo, int you, int addend) {
    if(zuo <= l && r <= you) {
        lazy[rt] = lazy[rt] * addend % mod;
        sum[rt] = sum[rt] * addend % mod;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1;
    if(zuo <= mid)
        add(ls, l, mid, zuo, you, addend);
    if(you > mid)
        add(rs, mid + 1, r, zuo, you, addend);
    sum[rt] = (sum[ls] + sum[rs]) % mod;
}

void change(int rt, int l, int r, int pos, int addend) {
    cnt[rt] += addend > 0 ? 1 : -1;
    if(l == r) {
        sum[rt] = addend > 0 ? addend : 0;
        return;
    }
    push_down(rt);
    int mid = (l + r) >> 1, ls = rt << 1, rs = ls | 1;
    if(pos <= mid)
        change(ls, l, mid, pos, addend);
    else
        change(rs, mid + 1, r, pos, addend);
    sum[rt] = (sum[ls] + sum[rs]) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    inv = quick_pow(base, mod - 2, mod);
    has[0] = 1;
    for(int i = 1; i <= n; ++ i) {
        cin >> a[i];
        stand = (stand * base + a[i]) % mod;
        has[i] = has[i - 1] * base % mod;
        tmp += has[i - 1];
    }
    for(int i = 1; i <= m; ++ i) 
        cin >> b[i], loc[b[i]] = i;
    int cur = 0;
    build(1, 1, m);
    for(int i = 1; i <= m; ++ i)
        if(b[i] <= n)
            ++ cur, change(1, 1, m, i, b[i] * has[n - cur] % mod);
    if(sum[1] == stand)
        ++ ans;
    for(int i = n + 1; i <= m; ++ i) {
        add(1, 1, m, 1, loc[i - n], inv);
        change(1, 1, m, loc[i - n], -1);
        add(1, 1, m, 1, loc[i], base);
        change(1, 1, m, loc[i], i * has[ask(1, 1, m, loc[i], m)] % mod);
        stand = (stand + tmp) % mod;
        if(sum[1] == stand)
            ++ ans;
    }
    cout << ans;
}
```

---

## 作者：bai_tang (赞：3)

只要有信念，就一定能成功！

### [题意](https://www.luogu.com.cn/problem/CF213E)
给定长为 $n$ 的排列 $a$，问有多少个 $x$，使得 $a$ 的每个元素加上 $x$ 恰好是排列 $b$ 中的一个子序列，$n\le m\le 2\times 10^5$。

### 分析
一种简单的方法是枚举 $x$ 来判断，那样子复杂度是 $O(m^2)$ 的，根本跑不过。

我们遇到的困难是：问题是不连续的子序列，很难处理，但是我们也看到了我们拥有的特殊性质：问题是一个排列。

进行维度转换，我们将问题转化为了连续问题，现在我们要解决的问题是：$b$ 存在多少个子串，使得它的相对次序和 $a$ 一样，看似问题并没有被简化，其实不然，我们已经可以哈希了，设一个长度为 $k$ 的排列的哈希值为：
$$\sum_{i=1}^kp_i\cdot B^{i-1}$$
这就是一个不错的哈希呀，它易于合并，然后也可以用线段树方便地改变，一个小技巧就是相对次序改变之后的全局减法可以转化为对原序列 $a$ 的全局加法，简化代码，[代码](https://www.luogu.com.cn/paste/5giod4to)。

---

## 作者：conti123 (赞：2)

### 前言
~~有些离谱~~非常好的哈希题。

### 题意
给定一个长度为 $n$ 的排列 $a$ 和一个长度为 $m$ 的排列 $b$，求有多少个 $x$ 满足排列 $a$ 中的每一项加上 $x$ 后是排列 $b$ 的**子序列**。 

## 分析
这是经典的匹配问题，考虑使用哈希。

那么原排列 $a$ 的哈希值可以算出，考虑怎么递推到加上 $x$ 后的哈希值。

易得：
$p$ 进制下的数 $abc=a\times p^2+b\times p+c$

而把这个数每一位都加上 $x$ 后可得其值为： $(a+x)\times p^2+(b+x)\times p+(c+x)=a\times p^2+b\times p+c+x(1+p+p^2)$

所以我们只要求出 $\sum_0^{n-1}p^i$ 就可以推出排列 $a$ 变换后的哈希值。

至于匹配，我们考虑维护一棵线段树，支持加入，删除，更新操作，用它来记录当前排列 $b$ 的哈希值。

我们只维护值和改变后的排列 $a$ 的值相等的排列 $b$ 的元素的位置，这样根节点的哈希值就是此时排列 $b$ **选出元素**的值的哈希值。

所以我们记录值为 $k$ 的元素的位置为 $pos_k$，在 $k$ 位于排列 $a$ 中，我们将其以 $pos_k$ 的位置加入线段树，同时删掉已经不在排列 $a$ 中的值的位置。

看图更好理解：

当 $x=0$ 时：
![](https://cdn.luogu.com.cn/upload/image_hosting/2v3jbfj1.png)
哈希值为 $p+2$ 显然不等于排列 $a$ 的 $2p+1$

当 $x=1$ 时：
![](https://cdn.luogu.com.cn/upload/image_hosting/d1ulkxte.png)
哈希值为 $3p+2$ 显然等于此时排列 $a$ 的 $3p+2$

所以我们就可以愉快的写代码了：

```
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
using namespace std;
const int N=1e6+1,p=1331,mod=1e9+7;
int n,m,ha,x,pos[N],ans,sum;
int qmi(int x,int y){
	int res=1;
	while(y>0){
		if(y&1)
			res*=x,res%=mod;
		x*=x,x%=mod,y>>=1;
	}
	return res;
}
struct Tr{
	int ls[N],rs[N],cnt[N],ha[N],mid;
	void pushup(int x){
		cnt[x]=cnt[ls[x]]+cnt[rs[x]];
		ha[x]=ha[ls[x]]*qmi(p,cnt[rs[x]])%mod+ha[rs[x]];
		ha[x]%=mod;
	}
	void add(int x,int l,int r,int pos,int k){
		if(l==r){
			cnt[x]=1,ha[x]=k;
			return ;
		}
		mid=(l+r)>>1;
		ls[x]=x<<1,rs[x]=x<<1|1;
		if(pos<=mid)add(ls[x],l,mid,pos,k);
		else add(rs[x],mid+1,r,pos,k);
		pushup(x);
	}
	void del(int fa,int ls_,int x,int l,int r,int pos){
		if(l==r){
			(ls_==1?ls[fa]:rs[fa])=0;
			cnt[x]=0,ha[x]=0;
			return ;
		}
		mid=(l+r)>>1;
		if(pos<=mid)del(x,1,ls[x],l,mid,pos);
		else del(x,0,rs[x],mid+1,r,pos);
		pushup(x);
	}
}tree;
void solve(){
	for(int i=1;i<=m;i++){
		int haA=ha+sum*(i-n)%mod;
		haA%=mod;
		if(i>n)
			tree.del(1,0,1,1,m,pos[i-n]);
		tree.add(1,1,m,pos[i],i);
		if(i>=n&&tree.ha[1]==haA)
		    ans++;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	    cin>>x,sum+=qmi(p,i-1),sum%=mod,ha=(ha*p+x)%mod;
	for(int i=1;i<=m;i++)
		cin>>x,pos[x]=i;
	solve();
	cout<<ans;
	return 0; 
}
```

[提交记录](https://codeforces.com/contest/213/submission/244534708)

---

## 作者：_Cheems (赞：2)

前言：线段树维护哈希好题，想通一点就容易做了，但是不看题解切掉还是挺困难的。

考虑如何匹配，有枚举值、匹配下标和枚举下标、匹配值两种方案，由于要求合法的 $x$ 的数量，因此枚举值看起来更合理点（或者两种都试试）。

考虑枚举 $x$，等价于在 $B$ 上枚举区间 $[x,x+n-1]$。考虑下标如何匹配，我们令 $A_i$ 表示 $i$ 在 $a$ 中的下标，同理有 $B_i$，那么只需比较 $B[x,x+n-1]$ 离散化后与 $A$ 是否完全相同即可。

考虑哈希，维护 $B[x,x+n-1]$ 离散化后的哈希值 $HASH$。暴力处理 $B[1,n]$ 的哈希值，那么接下来考虑相邻区间的转化即可，即删去第一个元素并在后面增加一个元素。

补充概念：字符串哈希等价于 $base$ 进制，即 $HASH(S[1,n])=\sum S_i\times base^{n-i}$，我们称 $base^{n-i}$ 项为 $S_i$ 的权重。

定义 $query(l,r)$ 表示区间内元素的权重之和，$rk(k)$ 表示 $k$ 离散化后的值。前者开一棵权值线段树维护，后者使用树状数组维护。

考虑删去区间第一个元素 $k$。首先将 $HASH-rk(k)\times base^{n-1}$，除此之外 $HASH-query(k+1,m)$，这是因为删去 $k$ 后区间内 $>k$ 的元素离散化后的值都会 $-1$，即少一个权重。同时维护线段树。

考虑在区间后面接一个元素 $k$。同上，先将 $HASH\times base+rk(k)$，然后 $HASH+query(k+1,m)$。同时维护线段树。

复杂度 $O(n\log n)$。 

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5, base = 1331, mod = 1e9 + 7;
int n, m, a[N], b[N], t[N], bas[N];
int A[N], B[N], S[N], hsh, hsh2, ans;

inline void upd(int a, int k) {for(; a < N; a += a & -a) t[a] += k;}
inline int rk(int a) {int res = 0; for(; a > 0; a -= a & -a) res += t[a]; return res;}
namespace Sg_Tree{
	#define lt (u << 1)
	#define rt (u << 1 | 1)
	#define mid (l + r >> 1)
	int s[N << 2], tag[N << 2];
	
	inline void psup(int u) {s[u] = (s[lt] + s[rt]) % mod;}
	inline void psdw(int u) {
		s[lt] = s[lt] * tag[u] % mod, s[rt] = s[rt] * tag[u] % mod;
		tag[lt] = tag[lt] * tag[u] % mod, tag[rt] = tag[rt] * tag[u] % mod;
		tag[u] = 1;
	}
	inline void build(int u, int l, int r){
		tag[u] = 1;
		if(l == r) {s[u] = S[l]; return ;}
		build(lt, l, mid), build(rt, mid + 1, r);
		psup(u);
	}
	inline void upd1(int u, int l, int r, int k, int op){
		if(l == r) {s[u] = tag[u] = op; return ;}
		psdw(u);
		if(k <= mid) upd1(lt, l, mid, k, op);
		else upd1(rt, mid + 1, r, k, op);
		psup(u);
	}
	inline void upd2() {s[1] = s[1] * base % mod; tag[1] = tag[1] * base % mod;}
	inline int query(int u, int l, int r, int ll, int rr){
		if(ll > rr) return 0;
		if(ll <= l && r <= rr) return s[u];
		psdw(u);
		int res = 0;
		if(ll <= mid) res = query(lt, l, mid, ll, rr);
		if(rr > mid) res = (res + query(rt, mid + 1, r, ll, rr)) % mod;
		psup(u);
		return res;
	}
}
using namespace Sg_Tree;
signed main(){
	cin >> n >> m;
	for(int i = 0; i <= m; ++i) bas[i] = !i ? 1 : bas[i - 1] * base % mod;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), A[a[i]] = i;
	for(int i = 1; i <= m; ++i) scanf("%lld", &b[i]), B[b[i]] = i;
	if(n > m) {cout << 0; return 0;}
	
	for(int i = 1; i <= n; ++i) 
		hsh = (hsh * base % mod + A[i]) % mod, upd(B[i], 1);
	for(int i = 1; i <= n; ++i) 
		hsh2 = (hsh2 * base % mod + rk(B[i])) % mod;
	
	S[B[n]] = 1;
	for(int i = n - 1; i >= 1; --i) S[B[i]] = S[B[i + 1]] * base % mod; 
	build(1, 1, m);
	
	for(int i = 1; i <= m - n + 1; ++i){
		if(hsh == hsh2) ++ans;
		if(i + n <= m){
			int R = i + n;
			//删首
			hsh2 = (((hsh2 - bas[n - 1] * rk(B[i]) % mod)) % mod + mod) % mod; 
			hsh2 = ((hsh2 - query(1, 1, m, B[i] + 1, m)) % mod + mod) % mod;
			upd1(1, 1, m, B[i], 0), upd(B[i], -1);
			//加尾
			upd2(), hsh2 = (hsh2 * base + rk(B[R]) + 1)% mod;
			hsh2 = (hsh2 + query(1, 1, m, B[R] + 1, m)) % mod;
			upd1(1, 1, m, B[R], 1), upd(B[R], 1);
		}
	}
	cout << ans;
	return 0;
}
```




---

## 作者：wcyQwQ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF213E)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/01/14/CF213E%20Two%20Permutations/)

## 前言

集训讲的一道高妙 DS。

### 前置芝士

平衡树，序列 Hash

## 分析

首先子序列并不是连续的一段，不好维护，考虑到给排列 $a$ 每一项都加上 $x$ 后在值域上依旧是连续的一段，所以我们记 $pos_{b_i} = i$，那么现在的问题就变成，我们每次从 $pos$ 数组中选一个长度为 $n$ 的子段，然后判断这个子段所对应的子序列是否和 $a_i$ 变化后相同。

我们考虑用平衡树来维护序列，我们用 $(p, v)$ 来表示一个位置在 $p$，值为 $v$ 的点，然后每次以 $p$ 为关键字插入，然后考虑判断序列相等，这里我们可以用序列 Hash 来快速判断，平衡树维护 Hash 是平凡的，而 $a$ 排列每次 Hash 的增量也是好计算的，由于我们平衡树插入了一个哨兵，序列右移一维，所以在用 $\text{Hash(a)} \times P$ 来判断。

## 代码

```c++
#include <bits/stdc++.h>
#define ull unsigned long long

const int N = 2e5 + 10, P = 1331, INF = 1 <<30;
ull p[N], hasha, sump;
int pos[N];
struct Splay {
	int s[2], p, sz, pos;
	ull v, sum;
	void init(ull _v, int _p, int _pos) {
		v = sum = _v, p = _p, pos = _pos, sz = 1;
	}
} t[N << 1];
int root, tot;

inline int read() {
	int x = 0, y = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * y;
}

inline void pushup(int x) {
	t[x].sz = t[t[x].s[0]].sz + t[t[x].s[1]].sz + 1;
	t[x].sum = (t[t[x].s[0]].sum * P + t[x].v) * p[t[t[x].s[1]].sz] + t[t[x].s[1]].sum;
}

inline void rotate(int x) {
	int y = t[x].p, z = t[y].p, k = t[y].s[1] == x;
	t[z].s[t[z].s[1] == y] = x, t[x].p = z;
	t[y].s[k] = t[x].s[!k], t[t[x].s[!k]].p = y;
	t[x].s[!k] = y, t[y].p = x;
	pushup(y), pushup(x);
}

inline void splay(int x, int k) {
	while (t[x].p != k) {
		int y = t[x].p, z = t[y].p;
		if (z != k)
			if ((t[z].s[1] == y) ^ (t[y].s[1] == x)) rotate(x);
			else rotate(y);
		rotate(x);
	}
	if (!k) root = x;
}

inline void insert(int pos, int v) {
	int u = root, p = 0;
	while (u) p = u, u = t[u].s[pos > t[u].pos];
	u = ++tot;
	if (p) t[p].s[pos > t[p].pos] = u;
	t[u].init((ull)v, p, pos);
	splay(u, 0);
}

inline void del(int pos) {
	int u = root;
	while (u) {
		if (t[u].pos == pos) break;
		else if (t[u].pos > pos) u = t[u].s[0];
		else u = t[u].s[1];
	}
	splay(u, 0);
	int l = t[u].s[0], r = t[u].s[1];
	while (t[l].s[1]) l = t[l].s[1];
	while (t[r].s[0]) r = t[r].s[0];
	splay(l, 0), splay(r, l);
	t[r].s[0] = 0;
	pushup(r), pushup(l);
}

int main() {
	int n = read(), m = read();
	p[0] = sump = 1;
	insert(-INF, 0), insert(INF, 0);
	for (int i = 1; i <= 2e5; i++) p[i] = p[i - 1] * P;
	for (int i = 1; i <= n - 1; i++) sump += p[i];
	for (int i = 1; i <= n; i++) hasha = hasha * P + read();
	for (int i = 1; i <= m; i++) pos[read()] = i;
	for (int i = 1; i <= n - 1; i++) insert(pos[i], i);
	int res = 0;
	for (int i = n; i <= m; i++) {
		insert(pos[i], i);
		if (t[root].sum == hasha * P) res++;
		hasha += sump;
		del(pos[i - n + 1]);
	}
	printf("%d\n", res);
	return 0;
}
```



---

## 作者：nofind (赞：2)

## [题意](https://www.luogu.com.cn/problem/CF213E)

考虑枚举$x$，快速判断是否合法：  
现在$a$数组是$a_1+x,a_2+x,...,a_n+x$，我们同时要求这些数在$b$中都要出现，并且位置是从小到大的。  
显然$x\in[0,m-n]$时都会出现。  
设$posb_i$表示$i$在$b$中出现的位置，我们的要求即为：$posb_{a_1}<posb_{a_2}<...<posb_{a_n}$。  
我们可以维护$a$的哈希值，将$b$中的$posb_{a_1}<posb_{a_2}<...<posb_{a_n}$都提出来也求一个哈希值，如果两个哈希值相同，则$x$满足条件。

我们从小到大枚举$x$，那么$a$的哈希值是很好维护的，对于$b$的哈希值，我们用线段树维护即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
typedef long long ll;
const int maxn=2e5+10;
const ll base=23;
const ll mod=19260817;
int n,m,ans;
int a[maxn],b[maxn],posb[maxn];
ll hasha,delta;
ll pw[maxn];
inline int readint()
{
	char c=getchar();int res=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
	return res*f;
}
inline ll add(ll x,ll y){return x+y>=mod?x+y-mod:x+y;}
inline ll dec(ll x,ll y){return x-y<0?x-y+mod:x-y;}
int size[maxn<<2];
ll sum[maxn<<2];
inline void up(int p,int l,int r)
{
	size[p]=size[ls(p)]+size[rs(p)];
	sum[p]=add(sum[ls(p)]*pw[size[rs(p)]]%mod,sum[rs(p)]);
}
void change(int p,int l,int r,int pos,int k)
{
	if(l==r){size[p]+=(!k)?-1:1,sum[p]=k;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)change(ls(p),l,mid,pos,k);
	else change(rs(p),mid+1,r,pos,k);
	up(p,l,r);
}
int main()
{
	n=readint(),m=readint();
	for(int i=1;i<=n;i++)a[i]=readint();
	for(int i=1;i<=m;i++)posb[b[i]=readint()]=i;
	pw[0]=1;
	for(int i=1;i<=n;i++)
	{
		hasha=add(hasha*base%mod,a[i]);
		pw[i]=pw[i-1]*base%mod;
		delta=add(delta,pw[i-1]);
	}
	for(int i=1;i<=n;i++)change(1,1,m,posb[i],i);
	if(sum[1]==hasha)ans++;
	for(int i=n+1;i<=m;i++)
	{
		change(1,1,m,posb[i-n],0);
		change(1,1,m,posb[i],i);
		hasha=add(hasha,delta);
		if(sum[1]==hasha)ans++;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：lfxxx (赞：0)

由于排列的良好性质，我们在值域上考虑判定的问题。

显然 $a_i + x$ 构成了值域上一段长度为 $n$ 的连续段，那么限制等价于将值域为 $i$ 的位置记作 $p_i$，排列 $b$ 的一段值域产生的 $p$ 与 $a$ 排列产生的 $p$ 离散化后相同。

两个序列离散化后相同，这个问题已经被出烂了，由于这里是两个排列，所以我们直接令位置 $i$ 的权值为满足 $j<i$ 且 $p_j < p_i$ 的 $j$ 的数量，利用这个权值哈希即可判断。

由于要在排列 $b$ 的值域上双指针并动态维护哈希值，所以开两个树状数组分别维护值域上的桶与带权桶，分别用作往后面加入一个数时计算 $j$ 的数量和将开头的数删去时计算其作为 $j$ 所造成的贡献减少的量。

总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+9;
const int base = 1331;
const int maxn = 2e5+114;
int _pow[maxn];
int inv[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int tr[maxn][2];
int A[maxn],B[maxn];
int a[maxn],b[maxn];
int n,m;
void add(int u,int c,int ty){
    while(u<maxn) tr[u][ty]=(tr[u][ty]+c)%mod,u+=(u&(-u));
}
int pre(int u,int ty){
    int res=0;
    while(u>0) res=(res+tr[u][ty])%mod,u-=(u&(-u));
    return res;
}
int Hasha;
int Hashb;
int ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    _pow[0]=inv[0]=1;
    for(int i=1;i<maxn;i++) _pow[i]=_pow[i-1]*base%mod,inv[i]=qpow(_pow[i],mod-2);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        A[a[i]]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
        B[b[i]]=i;
    }
    for(int i=1;i<=n;i++){
        Hasha=(Hasha+_pow[i]*pre(A[i],0)%mod)%mod;
        add(A[i],1,0);
    }
    for(int i=1;i<=n;i++) add(A[i],mod-1,0);
    for(int i=1;i<=n;i++){
        Hashb=(Hashb+_pow[i]*pre(B[i],0)%mod)%mod;
        add(B[i],1,0);
        add(B[i],_pow[i],1);
    }
    for(int i=1;i<=m-n+1;i++){
        //先计算贡献再移动区间
        if(Hasha*_pow[i-1]%mod==Hashb) ans++;
        if(i==m-n+1) break;
        //点 i 贡献删去
        Hashb=(Hashb-0)%mod;
        add(B[i],mod-1,0);
        add(B[i],(mod-_pow[i])%mod,1);
        Hashb=(Hashb+mod-(pre(maxn-1,1)+mod-pre(B[i],1))%mod)%mod;
        //点 i+n 贡献加入
        Hashb=(Hashb+_pow[i+n]*pre(B[i+n],0)%mod)%mod;
        add(B[i+n],1,0);
        add(B[i+n],_pow[i+n],1);
    }
    cout<<ans<<'\n';
    return 0;
}
/*
3 7
1 2 3
1 2 3 4 5 7 6
*/
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

 想必除了枚举 $x$，我们没有更有效的方法来统计合法的 $x$ 的个数了。现在的问题就是我们知道了 $x$ 后，怎么样快速判断当前的 $x$ 是否合法呢？

其实判断合法就是要判定 $a$ 假加上 $x$ 后在 $b$ 上的先后顺序是否不变。

注意到 $a$ 是一个排列，所以此时 $a$ 的**值域**完全是 $[1+x,n+x]$ 这段区间。那么我们就可以建立一个映射数组为 $p_i$ 表示数值 $i$ 在 $b$ 中的下标为 $p_i$，那么我们只需要考虑区间 $p_{1+x\sim n+x}$ 即可。

我们用平衡树动态维护区间 $[1+x,n+x]$ 即可，可以发现很像滑动窗口。

注意这里的 $p_i$ 维护的是 $i$ 在 $b$ 中的实际下标，但因为平衡树的特殊性质（我们以实际下标为关键字），其在平衡树中的编号恰好是其相对编号（即把 $b$ 中等于 $a_1+x\sim a_n+x$ 的数字提出来，单独的排序，这恰好是我们需要的）。

那么我们现在的任务就是快速判断平衡树中维护的信息和当前 $a$ 的相对位置信息是否相同即可。我们把平衡树压扁，变成一个有序的序列 $l$，然后记录 $r_i$ 表示初始 $a$ 中值为 $i$ 的数字的下标，每次判断 $l$ 和 $r$ 是否相等即可。这里我们不需要维护 $r$，因为 $a$ 是所有数字都加上 $x$，相对位置不会改变。我们在修改平衡树时顺便修改其哈希值（即l的哈希），然后就可以愉快的用哈希来判断了（判断 $l$ 的哈希和提前计算出的 $r$ 的哈希是否相等）。

---

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e3+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD2=1e9+7;

const int MOD1=998244353;
const int P=M<<1|1;

int hasl[M], hasr[M];
int tr[M][2], tmp[M], f = 1, siz[M];
int rt,ans;
bool tag[M];    
int n,m;

int has1, has2, t, tt;
int sz[M], a[M], b[M], p[M];
int h1[M], h2[M];

namespace PHT{

	inline void pushup(int x) {
	    siz[x] = siz[tr[x][0]] + siz[tr[x][1]] + 1;
	    sz[x] = sz[tr[x][0]] + sz[tr[x][1]] + (!tag[x]);
	    if (tag[x]) {
	        h1[x] = (h1[tr[x][0]] * hasl[sz[tr[x][1]]] + h1[tr[x][1]]) % MOD1;
	        h2[x] = (h2[tr[x][0]] * hasr[sz[tr[x][1]]] + h2[tr[x][1]]) % MOD2;
	    } else {
	        h1[x] = (((h1[tr[x][0]] * P + x) % MOD1) * hasl[sz[tr[x][1]]] + h1[tr[x][1]]) % MOD1;
	        h2[x] = (((h2[tr[x][0]] * P + x) % MOD2) * hasr[sz[tr[x][1]]] + h2[tr[x][1]]) % MOD2;
	    }
	}
	int build(int hasl, int hasr) {
	    if (hasl > hasr)return 0;
	    int mid = (hasl + hasr) >> 1, x = tmp[mid];
	    tr[x][0] = build(hasl, mid - 1);
	    tr[x][1] = build(mid + 1, hasr);
	    pushup(x);
	    return (x);
	}
	void dfs(int x) {
	    if (!x)return;
        dfs(tr[x][0]);
	    if (!tag[x])
	        tmp[f] = x, f++;
            dfs(tr[x][1]);
	}
	void rebuild(int &x){
		f = 1;
	        dfs(x);
	        x = build(1, f - 1);
	}
	void insert(int &x, int cur) {
	    if (!x) {
	        x = cur;
	        pushup(cur);
	        return;
	    }
	    insert(tr[x][p[cur] > p[x]], cur);
	    pushup(x);
	    if (max(siz[tr[x][0]], siz[tr[x][1]]) >= (double)siz[x] * 0.66)rebuild(x);
	    
	}
	void del(int x, int cur) {
	    if (x == cur) {
	        tag[cur] = 1;
	        pushup(x);
	        return;
	    }
	    del(tr[x][p[cur] > p[x]], cur);
	    pushup(x);
	}
}

using namespace PHT;

void init(){
    hasl[0] = hasr[0] = 1;
    for (int i = 1; i <= m; i++) {//预处理哈希表
        hasl[i] = (hasl[i - 1] * P) % MOD1;
        hasr[i] = (hasr[i - 1] * P) % MOD2;
    }
    for (int i = 1; i <= n; i++) {//计算哈希
        int x = rd;
        has1 = (has1 * P + x) % MOD1;
        has2 = (has2 * P + x) % MOD2;
        t = (t * P + 1) % MOD1;
        tt = (tt * P + 1) % MOD2;
    }
}
signed main() {
    n = rd, m = rd;
    init();
    for (int i = 1; i <= m; i++) p[rd] = i;
    for (int i = 1; i < n; i++) {
        int x=rd;
        insert(x, i);
    }
    for (int i = 0; i <= m - n; i++) {
        insert(rt, n + i);//滑动窗口
        if ((has1 + t * i) % MOD1 == h1[rt]&&(has2 + tt * i) % MOD2 == h2[rt])ans++;
        del(rt, 1 + i);
    }
    cout << ans << endl;
}

```




---

## 作者：小超手123 (赞：0)



### 分析：

一个很自然的思路是直接枚 $x$，然后只保留 $b$ 中值域在 $[x+1,x+n]$ 的数，然后利用哈希判断 $a$ 与 $b$ 是否相同。

显然是可行的，看看如何维护 $a$ 与 $b$ 的哈希值。

维护 $a$ 的哈希值是简单的，记 $S=\sum_{i=1}^{n}a_i\times base^{n-i+1}$，显然 $\sum_{i=1}^{n}(a_i+x) \times base^{n-i+1}=S+x\sum_{i=1}^{n}base^{n-i+1}$。

$b$ 的哈希也不难，考虑保留值域从 $[l,r]$ 到 $[l+1,r+1]$ 的过程，明显删掉了 $l$，加上了 $r$。

我们可以利用线段树动态维护每个点的 $b_i \times base^{n-i+1}$，删掉一个数后前面的数都要除以 $base$，加入一个数后前面的数都要乘上 $base$。

在线段树里面维护两个值 $c_1,c_2$ 分别记录这个区间的 $\sum b_i \times base^{n-i+1}$ 和**里面有值的数的数量**。

这个线段树需要支持区间乘、单点赋值、区间查询。

时间复杂度为:$O(n \log n)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define base 1000000007
#define mod 998244353
#define N 200005
using namespace std;
int read() {
	char ch = getchar(); int x = 0, f = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
}
int Pow(int a, int n) {
	if(n == 0) return 1;
	if(n == 1) return a % mod;
	int x = Pow(a, n / 2);
	if(n % 2 == 0) return x * x % mod;
	else return x * x % mod * a % mod;
}
int inv(int x) {
	return Pow(x, mod - 2);
}
int n, m, hx, ans;
int a[N], b[N], h[N], f[N], S;
int c1[N * 4], c2[N * 4], tag[N * 4]; //c1记录hash值,c2记录有值的个数 
void pushup(int u) {
	c1[u] = (c1[u * 2] + c1[u * 2 + 1]) % mod;
	c2[u] = c2[u * 2] + c2[u * 2 + 1];
}
void maketag(int u, int x) {
	if(tag[u] != -1) tag[u] = tag[u] * x % mod; 
	else tag[u] = x % mod;
	if(c1[u] != -1) c1[u] = c1[u] * x % mod;
	else c1[u] = x % mod;
}
void pushdown(int u) {
	if(tag[u] == -1) return;
	maketag(u * 2, tag[u]);
	maketag(u * 2 + 1, tag[u]);
	tag[u] = -1;
}
void update1(int u, int L, int R, int x, int y) { //c1[x]=y 
	if(L == R) {
		if(c1[u] != 0 && y == 0) c2[u] = 0;
		else if(c1[u] == 0 && y != 0) c2[u] = 1;
		c1[u] = y;
		return;
	}
	int mid = (L + R) / 2;
	pushdown(u);
	if(x <= mid) update1(u * 2, L, mid, x, y);
	else update1(u * 2 + 1, mid + 1, R, x, y);
	pushup(u);
}
void update2(int u, int L, int R, int l, int r, int x) { //c1[l...r]乘上x 
	if(r < L || R < l) return;
	if(l <= L && R <= r) {
		maketag(u, x);
		return; 
	}
	pushdown(u);
	int mid = (L + R) / 2;
	update2(u * 2, L, mid, l, r, x);
	update2(u * 2 + 1, mid + 1, R, l, r, x);
	pushup(u);
}
int query(int u, int L, int R, int l, int r) { //查询[l,r]的c2 
	if(r < L || R < l) return 0;
	if(l <= L && R <= r) return c2[u];
	pushdown(u);
	int mid = (L + R) / 2;
	return query(u * 2, L, mid, l, r) + query(u * 2 + 1, mid + 1, R, l, r);
}
void Insert(int x, int y) { //在x处插入y 
    int z = query(1, 1, m, x + 1, m);
	update1(1, 1, m, x, y * h[z] % mod);
	update2(1, 1, m, 1, x - 1, base);
}
void Delete(int x) {
	update1(1, 1, m, x, 0);
	update2(1, 1, m, 1, x - 1, inv(base) % mod);
}
signed main() {
	memset(tag, -1, sizeof(tag));
    n = read(), m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= m; i++) b[i] = read(), f[b[i]] = i;
    h[0] = 1; 
	for(int i = 1; i <= 200000; i++) h[i] = h[i - 1] * base % mod;
	for(int i = 1; i <= n; i++) {
		S += h[n - i]; S %= mod;
		hx += a[i] * h[n - i] % mod; hx %= mod;
	}
	for(int i = 1; i <= n; i++) Insert(f[i], b[f[i]]);
	for(int x = 0; x <= m - n; x++) { //保留b值域为 [1+x, x+n] 的数 
		if(x) {
			hx += S % mod; hx %= mod;
			Delete(f[x]);
			Insert(f[x + n], b[f[x + n]]);
		}
		if(c1[1] == hx) ans++;
	}
	write(ans);
	return 0;
}
```



---

## 作者：251Sec (赞：0)

大家好我是试图对排列建子序列自动机的弱智。

---

我们使用经典的数列哈希方式：$h=\left(\sum\limits_{i=1}^n a_i b^{n-i}\right) \bmod P$。

考虑枚举 $x$，维护 $\{a_i+x\}$ 这个序列的哈希值，显然 $x$ 递增的时候是可以 $O(1)$ 更新的。然后对于 $\{a_i+x\}$ 这个序列值域是 $[x+1,x+n]$，而且每个数又只在 $b$ 里出现一次，于是直接在 $b$ 里找到这些数，按顺序排好，维护它们组成的序列的哈希值，判断是否与 $\{a_i+x\}$ 的哈希值相等。考虑 $x$ 增加时 $b$ 里只会删除一个数，插入一个数，平衡树维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P1 = 1e9 + 7, P2 = 1e9 + 9;
struct Node {
    int ls, rs, siz, pos;
    ll h1, h2, s1, s2;
} f[200005];
int tcn, rt;
ll pw1[200005], pw2[200005];
ll ud1, ud2, ha1, ha2;
int NewNode(int pos, int val) {
    int p = ++tcn;
    f[p].siz = 1; f[p].pos = pos;
    f[p].h1 = f[p].h2 = f[p].s1 = f[p].s2 = val;
    return p;
}
void Pushup(int p) {
    f[p].siz = f[f[p].ls].siz + 1 + f[f[p].rs].siz;
    f[p].s1 = (f[f[p].ls].s1 * pw1[f[f[p].rs].siz + 1] % P1 + f[p].h1 * pw1[f[f[p].rs].siz] % P1 + f[f[p].rs].s1) % P1;
    f[p].s2 = (f[f[p].ls].s2 * pw2[f[f[p].rs].siz + 1] % P2 + f[p].h2 * pw2[f[f[p].rs].siz] % P2 + f[f[p].rs].s2) % P2;
}
mt19937 rnd(363415);
void Split(int p, int rk, int &x, int &y) {
    if (!p) return void(x = y = 0);
    if (f[p].pos <= rk) {
        x = p;
        Split(f[p].rs, rk, f[p].rs, y);
    }
    else {
        y = p;
        Split(f[p].ls, rk, x, f[p].ls);
    }
    Pushup(p);
}
int Merge(int x, int y) {
    if (!x || !y) return x | y;
    if (rnd() % (f[x].siz + f[y].siz) < f[x].siz) {
        f[x].rs = Merge(f[x].rs, y);
        Pushup(x);
        return x;
    }
    else {
        f[y].ls = Merge(x, f[y].ls);
        Pushup(y);
        return y;
    }
}
int b[200005], bp[200005];
void Ins(int w) {
    int p = NewNode(bp[w], w);
    int x, y;
    Split(rt, bp[w], x, y);
    rt = Merge(x, p);
    rt = Merge(rt, y);
}
void Del(int w) {
    int x, y, z;
    Split(rt, bp[w], y, z); Split(y, bp[w] - 1, x, y);
    rt = Merge(x, z);
}
int n, m, ans;
int main() {
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= 200000; i++) pw1[i] = pw1[i - 1] * 251 % P1, pw2[i] = pw2[i - 1] * 251 % P2;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) ud1 = (ud1 + pw1[i]) % P1, ud2 = (ud2 + pw2[i]) % P2;
    for (int i = 1; i <= n; i++) {
        int w; scanf("%d", &w);
        ha1 = (ha1 * 251 + w) % P1; ha2 = (ha2 * 251 + w) % P2;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", b + i);
        bp[b[i]] = i;
    }
    for (int i = 1; i <= n; i++) Ins(i);
    ans += f[rt].s1 == ha1 && f[rt].s2 == ha2;
    for (int i = n + 1; i <= m; i++) {
        Del(i - n); Ins(i);
        ha1 = (ha1 + ud1) % P1; ha2 = (ha2 + ud2) % P2;
        ans += f[rt].s1 == ha1 && f[rt].s2 == ha2;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：iCostalymh (赞：0)

[My Blog](https://www.cnblogs.com/voah/p/17818780.html)

[Luogu](https://www.luogu.com.cn/problem/CF213E)
[CodeForces](https://codeforces.com/problemset/problem/213/E)

首先数据范围是 $2\times10^5$，支持枚举，问题留给了判断子序列。不简单想到了哈希，一开始想到的是树状数组，发现树状数组比较菜，就转向了线段树。

一开始先把 $b$ 中的 $1\sim n$ 加到线段树里，然后不断的删除最小的，加入最大的，这个过程只需要单点修改，不需要建树，也不需要 `pushdown`，线段树的每个节点维护出现的有效数字个数和这个区间的哈希值即可。

对于枚举的 $a$ 的哈希值，还需要维护一个 $base$ 的前缀和。每次统计答案直接判断 $a$ 的哈希值和线段树维护的哈希值是否相等即可。

$base$ 取个质数就行，模数要注意一下。

代码实现较为简单，个人感觉有点难想。

```cpp
#include <bits/stdc++.h>
#define int long long

const int N(200005), Base(13331), Mod(998244853);

inline int read() {
    int f(1), x(0);
    char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c & 15);
    return f * x;
}

int n, m, a[N], b[N], bs[N], sbs[N], hsa, rnk[N], ans;

namespace SegmentTree {
    #define lid p << 1
    #define rid p << 1 | 1

    struct Tree {
        int hsh, cnt;
    } t[N << 2];

    inline void pushup(int p) {
        t[p].cnt = t[lid].cnt + t[rid].cnt;
        t[p].hsh = (t[lid].hsh * bs[t[rid].cnt] % Mod + t[rid].hsh) % Mod;
    }

    void update(int p, int pl, int pr, int x, int v) {
        if (pl == pr) {
            t[p].hsh = v;
            t[p].cnt = (v > 0) ? 1 : 0;
            return;
        }
        int mid = (pl + pr) >> 1;
        if (x <= mid) update(lid, pl, mid, x, v);
        else update(rid, mid + 1, pr, x, v);
        pushup(p);
    }

    #undef lid
    #undef rid
} using namespace SegmentTree;

signed main() {
    bs[0] = sbs[0] = 1;
    for (int i = 1; i <= 200000; ++i) bs[i] = bs[i - 1] * Base % Mod;
    for (int i = 1; i <= 200000; ++i) sbs[i] = (sbs[i - 1] + bs[i]) % Mod;

    n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        hsa = (hsa * bs[1] % Mod + a[i]) % Mod;
    }
    for (int i = 1; i <= m; ++i) {
        b[i] = read();
        rnk[b[i]] = i;
        if (b[i] <= n) update(1, 1, m, rnk[b[i]], b[i]);
    }

    ans += (hsa == t[1].hsh);

    for (int i = n + 1; i <= m; ++i) {
        int j = i - n;
        update(1, 1, m, rnk[j], 0);
        update(1, 1, m, rnk[i], i);
        hsa = (hsa + sbs[n - 1]) % Mod;
        ans += (hsa == t[1].hsh);
    }

    printf("%lld\n", ans);
}
```

---

## 作者：bwartist (赞：0)

# CF213E Two Permutations 题解

[也许更好的阅读体验](https://www.cnblogs.com/bwartist/p/17809547.html)

下文的 $a+x$ 表示 $a_1+x,a_2+x,...a_n+x$ 这个序列。

发现 $n,m$ 不大，所以可以枚举 $x$，然后快速判断是否合法。

考虑如何快速判断一个 $x$ 是否合法。

注意到 $a,b$ 都是**排列**。

$a_1+x,a_2+x,...a_n+x$ 的数在 $[1+x,n+x]$ 范围内。

想象一下，把 $b$ 中不在 $[1+x,n+x]$ 范围内的数都锁起来不管，只留下 $[1+x,n+x]$ 范围内的数，设这时的 $b$ 数组中**没有被锁的数组成的子序列**为 $b'$。$b'$ 和 $a+x$ 相等，那么这个 $x$ 就是合法的，这里快速判断两个数组相等显然可以想到**哈希**。

---

怎么求 $b'$ 的哈希值？

从小到大枚举 $x$，在上一个 $x$ 时，$b'$ 中的数范围为 $[x,n+x-1]$，所以我们只需要在之前的 $b'$ 的基础上删去 $x$ 这个数，然后再加上 $n+x$ 这个数。

设 $pos_i$ 为 $i$ 在 $b$ 数组中的位置。
在 $b$ 数组上的操作就是：锁住 $b_{pos_{x}}$，解锁 $b_{pos_{n+x}}$

所以，用**线段树**维护 $b'$ 的哈希值。仅需要修改操作即可（具体看代码）。

---

怎么快速求出 $a+x$ 的哈希值？

自己写一下哈希的式子就知道了。具体见代码。

---

$Code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int x=0;char c=getchar();bool f=0;
    while(c>'9'||c<'0'){f|=(c=='-');c=getchar();}
    while(c<='9'&&c>='0'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return f?-x:x;
}
typedef long long ll;
const ll mod=1e9+7;
const ll base=31;
const int MAXN=2e5+5;
int a[MAXN],b[MAXN],pos[MAXN];
int n,m;
#define lch (u<<1)
#define rch (u<<1|1)
ll sum[MAXN<<4],cnt[MAXN<<4];
ll pw[MAXN],S;
void up(int u){
    cnt[u]=cnt[lch]+cnt[rch];
    sum[u]=(sum[lch]*pw[cnt[rch]]%mod+sum[rch])%mod;
}
void add(int u,int l,int r,int p,int val){
    if(l==r){
        cnt[u]+=val;
        sum[u]=cnt[u]*b[p]%mod;
        return;
    }
    int mid=l+r>>1;
    if(p<=mid)   add(lch,l,mid,p,val);
    else    add(rch,mid+1,r,p,val);
    up(u);
}
int main(){
    n=read(),m=read();
    ll A=0;pw[0]=1ll;ll S=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        A=(A*base%mod+a[i])%mod;
        pw[i]=pw[i-1]*base%mod;
        S=(S+pw[i-1])%mod;
    }
    for(int i=1;i<=m;i++){b[i]=read();pos[b[i]]=i;}
    int ans=0;
    //初始所有数都被锁住
    for(int i=1;i<=m;i++){//b数组中出现 [i-n+1,i]
        add(1,1,m,pos[i],1);//解锁 i
        if(i>n) add(1,1,m,pos[i-n],-1);//锁住 i-n
        if(i>=n){
            int x=i-n;
            ll C=(A+x*S%mod)%mod,B=sum[1];//C就是a+x的hash值
            if(C==B)    ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~这题是给人做的吗？！~~

------------
## 警钟敲烂：
这道题作为一道字符串题，十分的恶心，因为，它在最终判断是否是子序列的时候，可以**跳着看**~~原谅我的无知~~！！！

------------
## 大致思路：
这道题是一道平衡树的经典例题，而题目的目的是找出有多少种 $x$ 让 $a_i$ 加上 $x$ 的序列是 $b$ 序列的子序列。

首先这道题**搜索枚举等暴力思路**不难想，但是这道题的数据范围直接把你卡到原地升天，因此我们要想一下更优的解法。

我们先注意到操作的东西是一串数列 $a$，那么我们就可以将这串数列转化成**字符串**，并用哈希储存起来。这个步骤的操作我们在一开始输入 $a$ 字符串时就可以预处理好，为后面的计算做好准备。处理完后，我们建造一颗从 $1$ 到 $m$ 的平衡树，为后面插入 $b$ 字符串中的数进行匹配做好准备。

然后，我们从 $1$ 枚举到 $m$，依次插入 $b$ 字符串中的数。**比较的是整个区间的相对顺序是否和** $a$ **串一致**。比如说 $a$ 串中的数是 $1,3,2$，那么将第二个串的 $1,2,3$ 插入到线段树中后，如果其相对顺序也是 $1,3,2$，那么它的 hash 值肯定一样。但是注意的是，如果继续插入 $4$ 这个数字，肯定要把 $1$ 删掉，因为要保持平衡树的稳定。那么这时候的 hash 值是 $2,3,4$ 这种组合 hash。可以发现每一权都加了 $1$，那么这个在操作开始之前预处理一下就可以了。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF 1000003ll
#define inf 999997ll
const int N = 2e5 + 1;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct Seg_tree
{
    int left, right;
    int size;
    int hash1, hash2;
} tree[N << 2];
int n, m;
int a[N], b[N], p[N];
int fact_2[N] = {1}, fact_1[N] = {1};
int ha1, ha2;
int sum1, sum2;
void bulid(int k, int l, int r)
{
    tree[k].left = l;
    tree[k].right = r;
    tree[k].hash1 = tree[k].hash2 = 0ll;
    tree[k].size = 0;
    if (l == r)
    {
        return;
    }
    int m = (l + r) >> 1;
    bulid(k * 2, l, m);
    bulid(k * 2 + 1, m + 1, r);
}
void push_up(int k)
{
    tree[k].size = tree[k * 2].size + tree[k * 2 + 1].size;
    tree[k].hash1 = tree[k * 2].hash1 * fact_1[tree[k * 2 + 1].size] + tree[k * 2 + 1].hash1;
    tree[k].hash2 = tree[k * 2].hash2 * fact_2[tree[k * 2 + 1].size] + tree[k * 2 + 1].hash2;
}
void update(int k, int pos, int val, int kk)
{
    if (tree[k].left == pos && tree[k].right == pos)
    {
        tree[k].size += kk;
        tree[k].hash1 += kk * val;
        tree[k].hash2 += kk * val;
        return;
    }
    int m = (tree[k].left + tree[k].right) >> 1;
    if (pos <= m)
    {
        update(k * 2, pos, val, kk);
    }
    else
    {
        update(k * 2 + 1, pos, val, kk);
    }
    push_up(k);
}

signed main()
{
    n = read();
    m = read();
    ha1 = ha2 = 0;
    sum1 = sum2 = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        ha1 = ha1 * INF + a[i];
        ha2 = ha2 * inf + a[i];
        sum1 += fact_1[i - 1];
        sum2 += fact_2[i - 1];
        fact_1[i] = fact_1[i - 1] * INF;
        fact_2[i] = fact_2[i - 1] * inf;
    }
    for (int i = 1; i <= m; i++)
    {
        b[i] = read();
        p[b[i]] = i;
    }
    int ans = 0;
    bulid(1, 1, m);
    for (int i = 1; i <= m; i++)
    {
        update(1, p[i], i, 1);
        if (i > n)
        {
            update(1, p[i - n], i - n, -1);
        }
        int d = i - n;
        if (d >= 0 && tree[1].hash1 == d * sum1 + ha1 && tree[1].hash2 == d * sum2 + ha2)
        {
            ans++;
        }
    }
    cout << ans;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121896459)

---

## 作者：Gaode_Sean (赞：0)

好题，独立想出来之后还是很有成就感的。

考虑使用哈希来判断两个序列是否完全相同。预处理出排列 $a$ 的哈希值，并以此线性推出 $x \in [0,m-n]$ 的哈希值（相信大家都会）。

开一个长度为 $m$ 的数组 $pos$，$pos_i$ 表示数字 $i$ 在排列 $b$ 中的位置。

我们按照 $pos$ 建立一棵平衡树，并在每个节点上记录该子树的哈希值。

先将 $i\in [1,n] \ pos_i$ 插入到平衡树中。接下来从小到大枚举 $x$，判断整棵平衡树的哈希值是否和 $a_1+x,a_2+x \cdots \  a_n+x$ 的哈希值相等，并更新答案，最后从平衡树中删除 $pos_{x+1}$。

时间复杂度 $\mathcal{O}(m \log n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int tot,root,n,m,ans,f[N];
typedef unsigned long long ll;
ll h,t,hah[N];
struct Treap
{
	int l,r,val,dat,cnt,size;
	ll sum,h;
}a[N];
int New(int val,ll sum)
{
	a[++tot].val=val; a[tot].dat=rand(); a[tot].cnt=a[tot].size=1; a[tot].sum=a[tot].h=sum;
	return tot;
}
void Update(int p)
{
	a[p].size=a[a[p].l].size+a[a[p].r].size+a[p].cnt;
	a[p].h=(a[a[p].l].h*131+a[p].sum)*hah[a[a[p].r].size]+a[a[p].r].h;
}
void zig(int &p)
{
	int q=a[p].l;
	a[p].l=a[q].r,a[q].r=p,p=q;
	Update(a[p].r),Update(p);
}
void zag(int &p)
{
	int q=a[p].r;
	a[p].r=a[q].l,a[q].l=p,p=q;
	Update(a[p].l),Update(p);
}
void Insert(int &p,int val,ll sum)
{
	if(!p){p=New(val,sum);return;}
	if(val<a[p].val)
	{
		Insert(a[p].l,val,sum);
		if(a[p].dat<a[a[p].l].dat) zig(p);
	}
	else
	{
		Insert(a[p].r,val,sum);
		if(a[p].dat<a[a[p].r].dat) zag(p);
	}
	Update(p);
}
void Remove(int &p,int val)
{
	if(!p) return;
	if(val==a[p].val)
	{
		if(a[p].cnt>1)
		{
			a[p].cnt--; Update(p);
			return;
		}
	    if(a[p].l||a[p].r)
	    {
		    if(!a[p].r||a[a[p].l].dat>a[a[p].r].dat) zig(p),Remove(a[p].r,val);
		    else zag(p),Remove(a[p].l,val);
		    Update(p);
	    }
	    else p=0;
	    return; 
    }
	val<a[p].val?Remove(a[p].l,val):Remove(a[p].r,val);
	Update(p);
}
int main()
{
	scanf("%d%d",&n,&m);
	hah[0]=t=1llu;
	for(int i=1;i<n;i++) hah[i]=hah[i-1]*131,t+=hah[i];
    for(ll i=1,x;i<=n;i++) scanf("%llu",&x),h=h*131+x;
    for(int i=1,x;i<=m;i++) scanf("%d",&x),f[x]=i; 
    for(ll i=1;i<=n-1;i++) Insert(root,f[i],i);
    for(ll i=n;i<=m;i++)
    {
    	Insert(root,f[i],i);
    	if(h==a[root].h) ans++;
    	h+=t;
    	Remove(root,f[i-n+1]);
	}
	printf("%d",ans); 
	return 0;
}
```

---

## 作者：tommymio (赞：0)

由于 $n+x\leq m$， $x$ 是可被枚举的，所以考虑先枚举 $x$，再判断是否合法。

我们预处理出 $a$ 序列的 $\text{Hash}$ 值 $h_a$，则序列 $a+x$（$a$ 按位加上 $x$ 后所得的序列）的 $\text{Hash}$ 值为 $h_a+x\sum\limits_{i=0}^{n-1} B^i$，其中 $B$ 为 $\text{Hash}$ 的基数。现在考虑快速比对这个值和 $b$ 序列的一个子序列的值，$b$ 序列的这个子序列值域已经被确定为 $[1+x,n+x]$，所以考虑 $\text{two-pointer}$ 依次加入，维护其 $\text{Hash}$ 值，与 $a+x$ 的 $\text{Hash}$ 值比对即可。可以使用线段树或平衡树实现，时间复杂度为 $O(m \log m)$。




---

