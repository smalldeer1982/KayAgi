# [ABC348G] Max (Sum - Max)

## 题目描述

给定两个长度为 $N$ 的整数序列 $A$ 和 $B$。对于 $k = 1, 2, \ldots, N$，请解决以下问题：

- 从 $1$ 到 $N$ 中选择 $k$ 个互不相同的整数。设选出的整数集合为 $S$，求 $\displaystyle\left(\sum_{i \in S} A_i\right) - \max_{i \in S} B_i$ 可能取得的最大值。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $-10^9 \leq A_i \leq 10^9$
- $-2 \times 10^{14} \leq B_i \leq 2 \times 10^{14}$

## 样例解释 1

以下是每种 $k$ 的最优选择方式。
- $k = 1$：$S = \{1\}$
- $k = 2$：$S = \{1, 3\}$
- $k = 3$：$S = \{1, 2, 3\}$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4 1
5 6
3 2```

### 输出

```
3
5
6```

## 样例 #2

### 输入

```
2
0 1
0 1```

### 输出

```
-1
-1```

## 样例 #3

### 输入

```
6
9 7
2 4
7 1
-1000 0
3 4
8 5```

### 输出

```
6
10
17
20
22
-978```

# 题解

## 作者：睿智的憨憨 (赞：11)

写篇题解记录一下第一次干出 G。

[原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc348_g)。

## 题目大意

给出两个长度为 $n$ 的整数序列 $A,B$。对于 $1 \sim n$ 中的每一个数 $k$，找出一个由 $1 \sim n$ 组成的大小为 $k$ 的集合 $S$，使得 $(\sum\limits_{i\in S} A_i) - \max\limits_{i\in S}B_i$ 最大，输出这个值。

## 解法分析

若单独考虑一个 $k$ 的问题，解法是将 $(A_i,B_i)$ 按照 $B_i$ 递增的顺序排序（之后的下标均为排序后的下标），接着枚举 $B_j$ 作为 $\max\limits_{i\in S} B_i$，要取出 $A_{1 \sim j}$ 中最大的 $k$ 个组成当前最大值。建立 $n$ 棵主席树，每次查询 $A_{1 \sim j}$ 前 $k$ 大就在第 $j$ 棵主席树上二分。离散化版本是 $O(n \log n)$。动态开点代码稍短，$O(n \log V)$，$V$ 为值域。

接下来按 $k$ 从小到大的顺序考虑问题。假设 $k=x$ 时选择 $B_j$ 作为最大值是最优的。$k=x+1$ 时，$j$ 这个决策点由于比 $j-1$ 多了一个可选数 $A_j$，因此肯定增长幅度会比 $j-1$ 更大一点，加上本来 $j$ 就已经比 $j-1$ 优秀了，$j-1$ 就更不行了，归纳可得 $1 \sim j-1$ 都已经不需要再考虑了。

于是用分治来利用这一性质。设当前区间为 $[l,r]$，可选决策点为 $[L,R]$。取 $[l,r]$ 的中间值 $mid$，枚举 $[L,R]$ 中的决策点，获得 $k=mid$ 时的最优决策点 $P$，则左边区间的可选决策点变为 $[L,P]$，右边区间可选决策点为 $[P,R]$，这样类似线段树得递归下去，每层的决策点区间长度和为 $O(n)$，故每层的时间复杂度为 $O(n\log V)$，共 $\log n$ 层，总时间复杂度 $O(n \log n \log V)$。

## 参考代码

代码中的主席树每次二分是 $O(\log V)$，如果离散化可以更快，不过也没必要，反正都能过。

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;
const int N = 200010, M = 1e7 + 10;

struct Num{
	ll a, b;
} x[N];
int rt[N], idx, lx[M], rx[M];
int cnt[M];
ll val[M];
void pushup(int x){
	cnt[x] = cnt[lx[x]] + cnt[rx[x]];
	val[x] = val[lx[x]] + val[rx[x]];
}
void mdf(int y, int &x, ll l, ll r, ll v){
	if (!x)
		x = ++idx;
	if (l == r){
		val[x] = val[y] + v;
		cnt[x] = cnt[y] + 1;
		return ;
	}
	ll mid = (l + r) >> 1;
	if (v <= mid){
		rx[x] = rx[y];
		mdf(lx[y], lx[x], l, mid, v);
	}
	else{
		lx[x] = lx[y];
		mdf(rx[y], rx[x], mid + 1, r, v);
	}
	pushup(x);
}
ll qry(int x, ll l, ll r, int k){
	if (!k)
		return 0;
	if (l == r)
		return k * l;
	ll mid = (l + r) >> 1;
	if (cnt[rx[x]] >= k)
		return qry(rx[x], mid + 1, r, k);
	return val[rx[x]] + qry(lx[x], l, mid, k - cnt[rx[x]]);
}

int n;
ll ans[N];

void get(int l, int r, int L, int R){//考虑[l,r]的答案，决策点为[L,R]
	if (l > r)
		return ;
	int mid = (l + r) >> 1, p = 0;
	int L2 = max(L, mid);
	ans[mid] = -9e18;
	for (int i = L2; i <= R; i++){
		ll now = qry(rt[i], -1e9, 1e9, mid);
		if (now - x[i].b > ans[mid]){
			ans[mid] = now - x[i].b;
			p = i;
		}
	}
	get(l, mid - 1, L, p);
	get(mid + 1, r, p, R);
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &x[i].a, &x[i].b);
	sort(x + 1, x + n + 1, [](Num x, Num y){return x.b < y.b;});
	for (int i = 1; i <= n; i++)
		mdf(rt[i - 1], rt[i], -1e9, 1e9, x[i].a);
	get(1, n, 1, n);
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：快乐的大童 (赞：6)

将 $b$ 升序排序考虑问题，那么最大值就是下标最大的 $b_i$。下文的 $a_i,b_i$ 都是排序过后的。

考虑 $k$ 固定怎么做：枚举 $b_i$ 作为最大值，那么最大值为 $b_i$ 时的答案最大值为此时 $a$ 的前 $i$ 项的前 $k$ 大值的和减去 $b_i$。将每次计算的结果取 max 即可。取区间前 $k$ 大值的和可以主席树上二分 $O(\log n)$ 做。

现在考虑所有的 $k$。设 $f_i$ 为当 $k=i$ 时的答案，转移是简单的，时间复杂度 $O(n^2\log n)$。

发现 $f_i$ 的转移具有决策单调性，简单证明一下，设 $F(i,j)$ 表示 $f_i$ 在 $j$ 处转移的答案，假设 $f_i$ 的最优决策点在 $x$，则对于所有 $y<x$，有 $F(i,y)<F(i,x)$。那么对于所有 $i<i'\le n$，$F(i',x)$ 相对于 $F(i,x)$ 增加的答案严格不小于 $F(i',y)$ 相对于 $F(i,y)$ 增加的答案，因为 $a_{1,2,\cdots, x}$ 的可选择范围严格包含 $a_{1,2,\cdots, y}$ 的可选择范围，所以有 $F(i',y)<F(i',x)$，故决策单调性成立。

发现 $f$ 的转移与 $f$ 无关，可以分治。算上求区间前 $k$ 大值的和的主席树，总时间复杂度 $O(n\log^2n)$。

[code](https://atcoder.jp/contests/abc348/submissions/52225107)

---

## 作者：Eraine (赞：5)

编号：AT_abc348_g

tag：贪心，分治，主席树

难度：*2559

独立切橙！！！~~虽然是赛后~~

考虑固定 $k$ 和 $\text{limit}=\max b_i$，所有的二元组 $(a_i,b_i)$ 分成 3 类。

第 1 类：$b_i\lt\text{limit}$。

第 2 类：$b_i=\text{limit}$。

第 3 类：$b_i\gt\text{limit}$。

第 3 类明显不可取，第 2 类中必须至少取 1 个二元组，第 1 类和第 2 类中要取 $k$ 个二元组。

观察题目中的式子：

$$\max\ (\sum_{i\in S}a_i)-\max_{i\in S}b_i$$

显然，当 $\max b_i$ 固定后，最大化 $\sum_{i\in S}a_i$ 即可。由于要满足第 2 类二元组至少要选一组，所以有一个很明显的贪心策略：在第 2 类中选出 $a$ 最大的一个二元组，然后将第 1 类二元组和剩下的第 2 类二元组共同构成的集合中选取 $a$ 前 $k-1$ 大的二元组即可得出答案。

拓展到 $\max b_i$ 不固定的情况。考虑扫描线，从小到大遍历出现过的 $b_i$。这是一个很经典的数据结构问题，动态增删（这里删除第 2 类二元组单独选出的那一组，在查询的时候直接加上即可）集合中的元素，查询集合中前 $k$ 大元素之和。权值线段树简单维护即可。

拓展到 $k=[1\dots n]$ 的情况，观察样例，发现每组答案对应的 $\max b_i$ 单调递增，我们猜想有结论：

对于 $i\lt j$，有 $\min(\max b_i)\le\min(\max b_j)$。

这就是经典的决策单调性优化的式子。下面我们来证明一下正确性。

考虑反证法。假设存在 $i\in[1,n-1]$ 使得 $\min(\max b_i)\gt\min(\max b_{i+1})$。设 $f_i$ 为 $k$ 取 $i$ 时的答案，令 $S=\min(\max b_i),T=\min(\max b_{i+1})$。当 $\max b_i$ 取 $S$ 时的答案 $f_i^{\prime}$ 和当 $\max b_i$ 取 $T$ 时的答案 $f_i^{\prime\prime}$，显然有 $f_i^{\prime}\gt f_i^{\prime\prime}$。考虑当 $k$ 取 $i+1$ 的增量的大小关系。当 $\max b_i$ 取 $T$ 时，显然第 1 类和第 2 类所有二元组构成的集合中取了前 $k-1$ 大，设 $B$ 为集合中第 $k$ 大的元素，那么当 $\max b_{i+1}$ 取 $T$ 时的增量 $\Delta_T\le B$。当 $\max b_{i+1}$ 取 $S$ 时，由于新增的新的若干组第 2 类二元组，所以增量至少会取原先第 $k$ 大元素，即 $\Delta_S\ge B$。于是有： $\Delta_S\ge\Delta_T$。联立 $f_i^{\prime}\gt f_i^{\prime\prime}$，有 $f_i^{\prime}+\Delta_S\gt f_i^{\prime\prime}+\Delta_T$。也就意味着，当 $k$ 取 $i+1$ 时，$\max b_{i+1}$ 取 $S$ 比取 $T$ 更优。与假设矛盾。故得证。

那么我们便可以用分治解决决策单调性的瓶颈，将原本循环 $\Theta(n)$ 从小到大遍历 $b_i$ 的部分优化到 $\Theta(\log n)$。这时候瓶颈在于分治的每一个节点都要重置线段树，时间和空间都会爆。考虑预处理出所有信息，即用主席树 $\Theta(n\log n)$ 预处理，然后每一层就相当于遍历主席树，时间复杂度 $\Theta(n\log n)$。分治共有 $\Theta(\log n)$ 层。

$\Theta(n\log^2n)$。

[submission](https://atcoder.jp/contests/abc348/submissions/52158820)

如有任何错误请指出，虚心接受您的意见。

---

## 作者：xiezheyuan (赞：4)

## 简要题意

有 $n$ 个二元组 $(a_i,b_i)$，定义一个二元组可重集的权值，表示所有 $a_i$ 的和减去 $b_i$ 的最大值。

对于每个 $k$，你需要选出 $k$ 个二元组，使得构成的可重集权值尽可能大，输出这个权值。

$1\leq n\leq 2\times 10^5,|a_i|,|b_i|\leq 2\times 10^{14}$。

## 思路

也是一道比较神奇的题目。

首先看到这种题目，一种常见的套路就是将所有二元组按照 $b_i$ 从小到大排序，每次固定一个最右的二元组，则接下来选择的二元组一定在左侧，且 $b$ 的最大值已经确定，故只需要选择前面 $a$ 的前 $k-1$ 大即可。

设 $w(i,j)$ 表示选择 $i$ 个二元组，最右的二元组下标为 $j$ 的最大权值，则这玩意可以建立可持久化权值线段树，在上面做二分，可以做到 $O(\log a_i)$ 单次回答询问。

然而 $O(n^2\log a_i)$ 的时间复杂度是无法接受的，考虑优化。

这个时候就需要一点人类智慧了，先来一个引理：

> 引理，对于任意的 $i<j$，设 $s(x)$ 表示使得 $w(x,y)$ 最大的 $y$，则有 $s(i)<s(j)$。

感性理解不难，可以用反证法，假设 $s(i)>s(j)$，则 $s(i)$ 可以取到更小。

于是我们发现这玩意很像决策单调性，考虑借助决策单调性分治的方法去求解。

决策单调性分治并不是什么很难的科技，可以参考 [我 P4767 的题解](https://www.luogu.com.cn/article/px1mu837)。主要是决策单调性分治用在不是优化 dp 的情形还是挺罕见的吧。


时间复杂度 $O(n\log a_i\log n)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (t[i].l)
#define rs (t[i].r)
#define mid ((l + r) >> 1)
#define int long long
using namespace std;

const int N = 2e5 + 5, BOUND = 2e14;
int n;
struct node{ int a, b; } a[N];

struct tnode{
    int l, r, cnt, val;
} t[N << 6];
int root[N], tot;

void update(int p, int v, int &i, int l, int r){
    t[++tot] = t[i], i = tot;
    t[i].val += v, t[i].cnt++;
    if(l == r) return;
    if(p <= mid) update(p, v, ls, l, mid);
    else update(p, v, rs, mid + 1, r);
}

int query(int k, int i, int l, int r){
    if(l == r) return (t[i].val / t[i].cnt) * min(k, t[i].cnt);
    if(t[rs].cnt >= k) return query(k, rs, mid + 1, r);
    else return t[rs].val + query(k - t[rs].cnt, ls, l, mid);
}

int w(int i, int j){
    return query(i, root[j], 1, BOUND << 1) - a[j].b;
}
int f[N];

void solve(int l, int r, int L, int R){
    if(l > r) return;
    int pos = -1, val = LLONG_MIN;
    for(int i=max(mid, L);i<=R;i++){
        int tmp = w(mid, i);
        if(tmp > val) val = tmp, pos = i;
    }
    f[mid] = val;
    solve(l, mid - 1, L, pos);
    solve(mid + 1, r, pos, R);    
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i].a >> a[i].b;
    sort(a + 1, a + n + 1, [](node x, node y){
        return x.b == y.b ? x.a < y.a : x.b < y.b;
    });
    for(int i=1;i<=n;i++){
        root[i] = root[i - 1];
        update(a[i].a + BOUND, a[i].a, root[i], 1, BOUND << 1);
    }
    solve(1, n, 1, n);
    for(int i=1;i<=n;i++) cout << f[i] << '\n';
    return 0;
}

// Written by xiezheyuan

```

---

## 作者：zhongpeilin (赞：4)

## 题目大意：
有 $n$ 个二元组 $a_{i}, b_{i}$，设选中一组集合为 $S$ 的二元组，那么他的代价为 $\sum_{i \in S} a_{i} - \max_{i \in S} b_{i}$，现在问你对于每个 $k = 1 \dots n$，当 $S$ 的大小强制为 $k$ 时的答案。  
## 解题思路：
首先我们发现，$a$ 的顺序并不重要，而 $b$ 因为有一个 $\max$ 操作，所以可以先按 $b$ 从小到大排序，那么就有一个 $O(n^2 \log n)$ 的做法，就是枚举 $k$，然后枚举 $i$ 算出前 $i$ 个数中，$a$ 值前 $k$ 大的是多少，不难想到用主席树预处理一下，然后 $\log$ 询问。  
但在此以后，我们发现用正常的优化已经优化不了了，因为里面有个主席树的询问，所以我们大胆猜测：最优决策点单调不降，这样就可以决策单调性优化了。  
$O(n \log^2 n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int a, b;
}num[200005];
struct Segment_Tree{
	int lson, rson, sz, sum;
}tree[200005*22];
int n, lsh[200005], tot, dp[200005], rt[200005];

bool cmp(node x, node y){
	return x.b < y.b;
}

int add(int p, int l, int r, int pos, int val){
	int u = ++tot;
	tree[u] = tree[p];
	if(pos < l || r < pos) return u;
	tree[u].sum += val;
	tree[u].sz++;
	if(l == r) return u;
	
	int mid = (l + r) / 2;
	if(pos <= mid) tree[u].lson = add(tree[p].lson, l, mid, pos, val);
	else tree[u].rson = add(tree[p].rson, mid + 1, r, pos, val);
	return u;
}
int ask(int u, int l, int r, int sz){
	if(l == r) return sz * lsh[l];
	int mid = (l + r) / 2;
	if(tree[tree[u].rson].sz >= sz) return ask(tree[u].rson, mid + 1, r, sz);
	return ask(tree[u].lson, l, mid, sz - tree[tree[u].rson].sz) + tree[tree[u].rson].sum;
}

void solve(int l, int r, int L, int R){
	if(l > r || L > R) return ;
	int mid = (l + r) / 2;
	dp[mid] = -LONG_LONG_MAX;
	int id = 0;
	for(int i = max(mid, L); i <= R; i++){
		int val = ask(rt[i], 1, n, mid) - num[i].b;
		if(dp[mid] < val){
			dp[mid] = val;
			id = i;
		}
	} 
	// cout << l << " " << mid <<" " << r << " " << id << endl;
	solve(l, mid - 1, L, id);
	solve(mid + 1, r, id, R);
}
signed main(){
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1; i<= n; i++) cin >> num[i].a >> num[i].b;
	sort(num + 1, num + n + 1, cmp);
	for(int i = 1; i<= n; i++) lsh[i] = num[i].a;
	sort(lsh + 1, lsh + n + 1);
	for(int i = 1; i <= n; i++){
		num[i].a = lower_bound(lsh + 1, lsh + n + 1, num[i].a) - lsh;
		rt[i] = add(rt[i - 1], 1, n, num[i].a, lsh[num[i].a]);
	}
	solve(1, n, 1, n);
	for(int i = 1; i <= n; i++) cout << dp[i] << endl;
	return 0;
}
```
## 总结：
像这种求解时用到了十分麻烦的操作时，可以考虑一些决策上的优化。

---

## 作者：未来姚班zyl (赞：3)

因为这道题特意学习了决策单调性优化 dp，来写一篇题解。

## 题目大意

给定 $n$ 个二元组 $(A_i,B_i)$。对于每个 $k$ 求出：

- 从二元组中选出 $k$ 个数，其中 $A_i$ 之和与 $B_i$ 的最大值的差的最小值。

## 题目分析

首先按照 $B_i$ 排序。钦定最大值位置 $i$，则相当于取 $A_j(j\le i)$ 前 $k$ 大。

令 $w(k,x)$ 表示钦定最大值位置为 $x$，取 $k$ 个的答案，即 $w(k,x)=前\ x\ 个数中前\ k\  大的\ A_i\ 和 -b_x$，所以 $ans_k=\min\limits_{i\ge k}w(k,i)$。 

考虑对于 $a<b$，$w(a+1,b)+w(a,b+1)$ 与 $w(a,b)+w(a+1,b+1)$ 的大小关系。只需要考虑第 $k+1$ 大的数在哪个位置即可，后者总是更优的，所以 $w(k,x)$ 满足四边形不等式，答案就满足决策单调性，分治优化即可 $O(n\log n)$。注意计算 $w(k,x)$ 可以用主席树做，单次 $O(\log n)$，总复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L(x) xd[x].l
#define R(x) xd[x].r
#define mid (l+r>>1)
#define lc(x) L(x),l,mid
#define rc(x) R(x),mid+1,r
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,M=1.1e6+5;
const ll llf=1e18;
int n,lsh[N],b[N],ln,tot,root[N];
struct node{
	int a,b;
}a[N];
inline bool cmp(node a,node b){
	return a.b<b.b;
}
struct seg{
	int l,r,sm,w;
}xd[N*30];
inline int modify(int x,int l,int r,int p){
	xd[++tot]=xd[x],xd[tot].sm+=b[p],xd[tot].w++;
	if(l==r)return tot;
	int nw=tot;
	if(p<=mid)L(nw)=modify(lc(x),p);
	else R(nw)=modify(rc(x),p);
	return nw;
}
inline int query(int x,int l,int r,int k){
	if(!k)return 0;
	if(l==r)return k*b[l];
	if(xd[R(x)].w<=k)return xd[R(x)].sm+query(lc(x),k-xd[R(x)].w);
	return query(rc(x),k);
}
inline int w(int l,int r){
	return query(root[r],1,ln,l)-a[r].b;
}
int f[N];
inline void solve(int l,int r,int Ll,int Rr){
	if(l>r)return;
	int ans=Rr;
	rep(i,max(mid,Ll),Rr)if(w(mid,i)>w(mid,ans))ans=i;
	f[mid]=w(mid,ans);
	solve(l,mid-1,Ll,ans),solve(mid+1,r,ans,Rr);
}
inline void Main(){
	n=read();
	repn(i)lsh[i]=a[i].a=read(),a[i].b=read();
	sort(a+1,a+n+1,cmp),sort(lsh+1,lsh+n+1),lsh[n+1]=inf;
	repn(i)if(lsh[i]^lsh[i+1])b[++ln]=lsh[i];
	repn(i)a[i].a=lower_bound(b+1,b+ln+1,a[i].a)-b;
	repn(i)root[i]=modify(root[i-1],1,ln,a[i].a);
	solve(1,n,1,n);
	repn(i)cout <<f[i]<<'\n';
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：HHH6666666666 (赞：2)

首先，如果将节点按 $B$ 从小到大排序，可以轻松解决 $\max$ 的问题。~~考场到这里就不会了。~~

接下来考虑分治：对于一个区间 $[l,r]$，我们考虑只选择下标在该区间内的节点时，选 $1,2,...,r-l+1$ 个的最大答案分别是多少，令其为 $ans_i$。

将其分为区间 $[l,mid]$ 与 $[mid+1,r]$，于是只选某一边的数的情况可以递归下去做，我们只需考虑两个区间内都选了节点的情况。

经过排序，$\max B$ 只与右边如何选择有关，可以将两侧分开考虑。如果此时左边选 $i$
 个，右边选 $j$ 个。左边对答案的贡献显然是前 $i$ 大的 $A$ 之和，而右边的贡献则为区间 $[mid+1,r]$ 下的 $ans_j$（右边选 $j$ 个节点，取其 $\sum A-\max B$）。
 
于是令 $sum_i$ 表示左边前 $i$ 大的 $A$ 之和，$res_i$ 表示右边区间的答案（防重名），则当前 $ans_k=\max\limits_{i+j=k}(sum_i+res_j)$。

目前这个卷积直接做只能 $O(n^2)$，必须寻找其他性质。注意到根据 $sum_i$ 的定义其差分逐渐变小，它是凸的。

于是有一个结论：令 $p_k$ 表示使 $ans_k=\max\limits_{i+j=k}(sum_i+res_j)$ 取到最大值的 $j$，$p_k$ 单调不降。

证明：对于每个 $j$ 枚举 $i=1,2,...$ 画出点 $(j+i,res_j+sum_i)$，对应着 $j$ 对答案的贡献，如图，每种颜色对应一个 $j$。

![](https://cdn.luogu.com.cn/upload/image_hosting/47saexdw.png)

当一个 $j$ 在某个位置 $x$ 上被一个大于它的数 $k$ 取代了，由于它们长得一样且都是凸的，不会出现 $x'>x$，$j$  在 $x'$ 上的值比 $k$ 大。

现在有两个做法：

1. 决策单调性分治。求区间 $[l,r]$ 的结果时，取其中点 $mid$ 并找出使其取到最大值的 $p_{mid}$，那么根据单调性， $\forall i\in[l,mid),p_i \le p_{mid}$ 且 $\forall i \in (mid,r],p_i \ge p_{mid}$。递归时记录当前区间 $p$ 的范围，这样每层 $p$ 的范围总共为非凸序列的长度，一共 $\log$ 层。

2. 李超树。将每个 $j$ 画出的图形看作函数，对每个点求函数最值。由于其单调性，两个图形最多只有一个交点，可以用李超树维护（只要是两两间最多一个交点、可以快速求值的函数都可用李超树维护）。

两种卷积做法均为 $O(n\log n)$，套上外层分治总复杂度为 $O(n\log^2 n)$。这个卷积还有一种 $O(n)$ 做法但好像有点麻烦，能过就行。

---

## 作者：JuRuoOIer (赞：2)

# 题解 ABC348G - Max (Sum - Max)

前排提示：本题解采用**与官方题解不同**且自认为更好理解的**整体二分+主席树**做法。

### 题意

已提交翻译。

给定长为 $n$ 的序列 $a,b$，对于每个 $k=1,2,...,n$，回答如下询问：
- 从 $1$ 到 $n$ 中任意选择 $k$ 个数组成集合 $s$，$\displaystyle\left(\sum_{i \in s}a_i\right)-\max_{i\in s}b_i$ 的最大值。

数据范围：$1 \le n \le 2\times10^5,-10^9\le a_i \le 10^9,-2\times10^{14}\le b_i \le 2\times10^{14}$。

### 做法

考虑一次询问。首先因为 $b_i$ 要取最大值，所以将数组按 $b_i$ 升序排序，在 $\max b_i$ 一定时（假设是 $b_x$），显然想要最大化整个式子的值，就需要选择 $a_x$（否则 $x$ 可以减小来使 $b_x$ 减小）和 $a_1$ 至 $a_{x-1}$ 中最大的 $k-1$ 个。循环枚举 $x$ 的值，就可以暴力地完成。这样的复杂度是 $O(n^2 \log n)$ 的（枚举 $x$ 是 $O(n)$ 的，而给 $a_1$ 至 $a_x$ 排序是 $O(n \log n)$ 的）。

等等，$a_1$ 至 $a_{x-1}$ 中最大的 $k-1$ 个？这不是可以直接主席树吗？于是单组询问暴力就被优化到了 $O(n \log n)$，但还是差很远。

继续优化。发现这玩意有决策单调性（由于笔者懒，所以不证了，有兴趣的佬可以自己证），因此直接上整体二分，即定义函数 `void work(ll L,ll R,ll l,ll r)`，处理 $[L,R]$ 询问区间中 $[l,r]$ 决策区间的答案。然后就是普通的整体二分了：
- 变量 $mid=\lfloor\dfrac{l+r}{2}\rfloor$；
- 枚举找到决策区间内第 $mid$ 个询问的最优决策点 $p$；
- 更新 `ans[mid]` 并递归调用 `work(L,mid-1,l,p)` 和 `work(mid+1,R,p,r)`。

整体二分的复杂度是 $O(n \log n \log n)$ 的，而里面又套了一个 $O(\log n)$ 的主席树，所以总复杂度 $O(n \log^3 n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
struct node{//存 a 数组和 b 数组的结构体 
	ll a,b;
};
struct point{//存主席树点的结构体 
	ll l,r,ls,rs,s,sum;
};
bool cmp(node x,node y){
	return x.b<y.b;
}
point t[12000000];//200000*log(200000)*log(1e9) 大约是 200000*20*30=12000000 
ll n,rt[200010],ans[200010],pos=1;//pos 表示用到 t[pos] 了；ans 存每个询问的答案；rt 存每个版本的根 
node a[200010];
const ll INF=1000000000000000000ll;
const ll inf=1000000000;//a 的值域范围，和上面 INF 分开是防止动态开点爆炸 
void copy(ll now){//复制 now 节点 
	t[pos].l=t[now].l;
	t[pos].r=t[now].r;
	t[pos].ls=t[now].ls;
	t[pos].rs=t[now].rs;
	t[pos].s=t[now].s;
	t[pos].sum=t[now].sum;
	pos++;
}
void add(ll now,ll x){//插入 
	t[now].s++;
	t[now].sum+=x;
	if(t[now].l==t[now].r){
		return ;
	}
	ll mid=((t[now].l+t[now].r)>>1);
	if(x<=mid){
		copy(t[now].ls);
		t[now].ls=pos-1;
		t[t[now].ls].l=t[now].l;
		t[t[now].ls].r=mid;
		add(t[now].ls,x);
	}
	else{
		copy(t[now].rs);
		t[now].rs=pos-1;
		t[t[now].rs].l=mid+1;
		t[t[now].rs].r=t[now].r;
		add(t[now].rs,x);
	}
}
ll query(ll now,ll x){//查询前 x 大之和 
	if(x==0)return 0;
	if(t[now].l==t[now].r){
		return t[now].l*x;
	}
	if(t[now].rs&&x<=t[t[now].rs].s){
		return query(t[now].rs,x);
	}
	return query(t[now].ls,x-t[t[now].rs].s)+t[t[now].rs].sum;
}
void work(ll L,ll R,ll l,ll r){//整体二分 
	if(L>R)return ;
	ll mid=((L+R)>>1),mx=-INF,p=0;
	for(int i=l;i<=r;i++){
		if(i<mid)continue;//显然 x<mid 时数量不够无解 
		ll tmp=query(rt[i-1],mid-1)+a[i].a-a[i].b;
		if(tmp>=mx){
			mx=tmp;p=i;
		}
	}
	ans[mid]=mx;
	work(L,mid-1,l,p);
	work(mid+1,R,p,r);
} 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+1+n,cmp);
	t[0].l=-inf;
	t[0].r=inf;
	for(int i=1;i<=n;i++){
		rt[i]=pos;
		copy(rt[i-1]);
		add(rt[i],a[i].a);
	}
	work(1,n,1,n);
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：tobie (赞：2)

看到这个 $\max_{i\in S} B_i$，肯定是要对 $B_i$ 进行排序。

我们定义当 $k=i$ 时，最优选择时 $B_j=\max_{x\in S} B_x$，那么我们称 $j$ 为 $i$ 的最优决策点。那么可以发现最优决策点一定单调不降。感性理解一下，如果我多取了一个数最优决策反而更小，那么我一开始就可以取那个更小的决策点。

所以考虑整体二分，问题转化为求序列中前 $i$ 个数的前 $k$ 大值之和，用可持久化权值线段树维护即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int N=200009,M=1000000000,inf=1e18;
int son[N*35][2],siz[N*35],sum[N*35];
int ncnt=0;
void pushup(int now)
{
	siz[now]=siz[son[now][0]]+siz[son[now][1]];
	sum[now]=sum[son[now][0]]+sum[son[now][1]];
}
int clone(int x)
{
	ncnt++;
	son[ncnt][0]=son[x][0],son[ncnt][1]=son[x][1];
	siz[ncnt]=siz[x],sum[ncnt]=sum[x];
	return ncnt;
}
#define mid (l+(r-l)/2)
int Modify(int now,int l,int r,int pos)
{
	int p;
	if(now==0) p=++ncnt;
	else p=clone(now);
	if(l==r)
	{
		siz[p]++;
		sum[p]+=pos;
		return p;
	}
	if(pos<=mid) son[p][0]=Modify(son[p][0],l,mid,pos);
	else son[p][1]=Modify(son[p][1],mid+1,r,pos);
	pushup(p);
	return p;
}
int Query(int now,int l,int r,int cnt)
{
	if(now==0) return 0;
	if(l==r) return l*cnt;
	if(siz[son[now][1]]<cnt)
	return sum[son[now][1]]+Query(son[now][0],l,mid,cnt-siz[son[now][1]]);
	else return Query(son[now][1],mid+1,r,cnt);
}
int rt[N];
int n,ans[N];
pair<int,int> v[N];
int ask(int k,int x){return Query(rt[x-1],-M,M,k-1)+v[x].second-v[x].first;}
void solve(int l,int r,int L,int R)
{
	if(l>r) return;
	ans[mid]=-inf;int pos;
	for(int i=max(L,mid),t;i<=R;i++)
	if((t=ask(mid,i))>ans[mid]) ans[mid]=t,pos=i;
	solve(l,mid-1,L,pos);
	solve(mid+1,r,pos,R);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1,x,y;i<=n;i++) scanf("%lld%lld",&x,&y),v[i]=make_pair(y,x);
	sort(v+1,v+n+1);
	for(int i=1;i<=n;i++) rt[i]=Modify(rt[i-1],-M,M,v[i].second);
	solve(1,n,1,n);
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[AT_abc348_g [ABC348G] Max (Sum - Max)](https://www.luogu.com.cn/problem/AT_abc348_g)

# 解题思路

考虑对于一个 $k$ 我们怎么做。

注意到我们可以先把 max 这一维给从小到大排序，然后依次枚举这个 $b_i$ 并顷定 $b_i$ 为你选取所有 $b_i$ 中的最大值，考虑此时如何最优，显然选取 $k$ 个下标 $j_1, j_2, j_3, \dots, j_k$ 满足 $l \in [1,k], \ j_l \in [1,i]$，$j_l$ 互不相同，$\sum_{i=1}^{k} a_{j_i}$ 的值最大，发现这东西就是 $a$ 序列前 $i$ 个数字中的前 $k$ 大值，可持久化线段树维护即可。

接下来我们考虑将 $k$ 从小到大依次做，我们发现给予我们的决策是单调不降的，具体的，若 $j - 1$ 这个决策劣于 $j$ 这个决策，则 $j$ 这个决策将会永远优于 $j - 1$ 这个决策，于是加上决策单调性优化即可，使用分治来维护，时间复杂度 $O(n \log n \log V)$。

# 参考代码

```cpp
ll n;
struct node{
    ll x,y;
}a[200010];
bool cmp(node x,node y){
    return x.y<y.y;
}
ll rt[200010*32],id;
ll ls[200010*32],rs[200010*32],k;
ll val[200010*32],S[200010*32];
void pushup(ll x){
    val[x]=val[ls[x]]+val[rs[x]],
    S[x]=S[ls[x]]+S[rs[x]];
}
void upd(ll pre,ll&x,ll l,ll r,ll y)
{
    if(!x)
        x=++id;
    if(l==r)
    {
        val[x]=val[pre]+y;
        S[x]=S[pre]+1;
        return ;
    }
    if(y<=mid)
        rs[x]=rs[pre],
        upd(ls[pre],ls[x],l,mid,y);
    else
        ls[x]=ls[pre],
        upd(rs[pre],rs[x],mid+1,r,y);
    pushup(x);
}
ll query(ll x,ll l,ll r,ll k)
{
    if(!k)
        return 0;
    if(l==r)
        return k*l;
    if(S[rs[x]]>=k)
        return query(rs[x],mid+1,r,k);
    return val[rs[x]]+query(ls[x],l,mid,k-S[rs[x]]);
}
ll ans[200010];
void sol(ll l,ll r,ll L,ll R) //[l,r] 决策点为 [L,R]
{
    if(l>r)
        return ;
    ll id=-1,l2=max(L,mid);
    ans[mid]=-9e18;
    forl(i,l2,R)
    {
        ll now=query(rt[i],-1e9,1e9,mid);
        if(now-a[i].y>ans[mid])
            ans[mid]=now-a[i].y,
            id=i;
    }
    sol(l,mid-1,L,id);
    sol(mid+1,r,id,R);
}
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    forl(i,1,n)
        cin>>a[i].x>>a[i].y;
    sort(a+1,a+1+n,cmp);
    forl(i,1,n)
        upd(rt[i-1],rt[i],-1e9,1e9,a[i].x);
    sol(1,n,1,n);
    forl(i,1,n)
        cout<<ans[i]<<endl;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

原题：CF gym 104651 L。

首先考虑 $k$ 一定时怎么做。

将所有点按照 $b$ 排序，枚举 $b_{\max}=b_x$，在前面 $x-1$ 个中选出 $k-1$ 个最大的 $a$，记为 $w(k,x)$，可以用可持久化权值线段树解决。

接下来回到原题。记 $f(k)$ 为 $w(k,x)_{\max}$ 对应的 $x$。

对于 $x<y$，如果 $w(k,x)\le w(k,y)$，在 $k$ 增大时，因为 $y$ 可以选的范围一直比 $x$ 多，所以 $y$ 对应答案一定会更优，即 $\forall k'\ge k,w(k',x)\le w(k',y)$。

因此，$f(1)\le f(2)\le\dots\le f(n)$，也就是说此时有决策单调性，所以可以对 $k$ 进行分治，时间复杂度 $O(n\log^2 n)$。

注意在权值线段树中，因为值域是 $[-10^9,10^9]$，如果直接平移成 $[1,2\times 10^9+1]$ 需要记得给 $l$ 和 $r$ 开 long long。

```cpp
ll n,rt[200005],cnt;
pair<ll,ll> a[200005];
ll ls[6400005],rs[6400005],sz[6400005];
ll s[6400005];
#define mid (l+r>>1)
void ins(ll&p,ll q,ll l,ll r,ll v){//可持久化线段树
	p=++cnt;
	if(l==r){
		sz[p]=sz[q]+1,s[p]=s[q]+v-1e9-1;
		return;
	}
	if(v<=mid)rs[p]=rs[q],ins(ls[p],ls[q],l,mid,v);
	else ls[p]=ls[q],ins(rs[p],rs[q],mid+1,r,v);
	s[p]=s[ls[p]]+s[rs[p]],sz[p]=sz[ls[p]]+sz[rs[p]];
}
ll qry(ll p,ll l,ll r,ll k){
	if(!p||!k)return 0;
	if(l==r)return k*(l-1e9-1);
	if(k==sz[p])return s[p];
	ll ans=qry(rs[p],mid+1,r,min(k,sz[rs[p]]));
	if(k>sz[rs[p]])ans+=qry(ls[p],l,mid,k-sz[rs[p]]);
	return ans;
}
ll ans[200005];
void calc(ll l,ll r,ll aa,ll b){// 分治
	if(l>r)return;
	ll k=aa-1;
	ll tmp=-9e18;
	for(ll i=max(mid,aa);i<=b;i++)if(qry(rt[i],1,2e9+1,mid)-a[i].se>tmp){
		tmp=qry(rt[i],1,2e9+1,mid)-a[i].se,k=i;
	}
	ans[mid]=tmp,calc(l,mid-1,aa,k),calc(mid+1,r,k,b);
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].fi>>a[i].se,a[i].fi+=1e9+1;
	sort(a+1,a+n+1,[&](pair<ll,ll>x,pair<ll,ll>y){return x.se<y.se;});
	for(int i=1;i<=n;i++)ins(rt[i],rt[i-1],1,2e9+1,a[i].fi);
	calc(1,n,1,n);
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：xuanfeng101 (赞：0)

## **题目大意**

给定 $n$ 个二元组 $(a, b)$，从中依次寻找 $1 - k$ 个，使得对于这 $k$ 个二元组 $a$ 的和减去其中 $b$ 的最大值最大。

## **题目分析**  

整体二分，决策单调性好题。

对于朴素想法不难想到 $b$ 的值不好确定，于是可以将 $b$ 升序排序，每次枚举 $b$ 的取值，再建立主席树寻找 $k$ 个 $a$ 的最大值，这样时间复杂度为 $O(n^2 \log n)$ 显然不能通过。

于是转化思路，寻找其中的特殊性质，我们可以发现对于升序排列的 $b$，记 $f(i)$ 表示找 $i$ 个二元组的最大值，那么 $f(i)$ 的决策点（也就是对于 $b$ 的选择）单调不降，反证法，如果对于 $i$ 的最优决策点在 $i - 1$ 前面，那么 $i - 1$ 选择 $i$ 的决策点会更优秀，故决策点具有单调性。

所以，我们得到决策单调性后，不难想到二分决策点，用主席树维护对于每个决策点选 $k$ 个数的最大值，离散化后时间复杂度为 $O(n \log^2 n)$ 可以通过此题。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 1e18;
int n, idx, root[N];
int f[N];
vector<int> nums;
struct Node
{
	int l, r;
	int cnt, v;
}tr[N * 25];
struct node
{
	int a, b;
}a[N];

bool cmp(node x, node y)
{
	if (x.b == y.b) return x.a < y.a;
	return x.b < y.b;
}

//离散化 
int find(int x)
{
	return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

//初始化主席树 
int build(int l, int r)
{
	int p = ++ idx;
	if (l != r)
	{
		int mid = l + r >> 1;
		tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
	}
	return p;
}

//建立主席树 
int insert(int p, int l, int r, int v)
{
	int q = ++ idx;
	tr[q] = tr[p];
	if (l == r) tr[q].cnt ++, tr[q].v += nums[l];
	else
	{
		int mid = l + r >> 1;
		if (v <= mid) tr[q].l = insert(tr[p].l, l, mid, v);
		else tr[q].r = insert(tr[p].r, mid + 1, r, v);
		tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
		tr[q].v = tr[tr[q].l].v + tr[tr[q].r].v;
	}
	return q;
}

//查询 
int query(int q, int l, int r, int k)
{
	if (l == r) return nums[l] * k;
	else
	{
		int mid = l + r >> 1;
		int cnt = tr[tr[q].r].cnt;
		if (k <= cnt) return query(tr[q].r, mid + 1 , r, k);
		else return tr[tr[q].r].v + query(tr[q].l, l, mid, k - cnt);
	}
}

//整体二分 
void solve(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	int pos = -1, val = -1e18, mid = l + r >> 1;
	for (int i = max(mid, L); i <= R; i ++ )
	{
		int t = query(root[i], 0, nums.size() - 1, mid) - a[i].b;
		if (t > val) val = t, pos = i;
	}
	f[mid] = val;
	solve(l, mid - 1, L, pos), solve(mid + 1, r, pos, R);
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i].a >> a[i].b;
		nums.push_back(a[i].a);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	sort(a + 1, a + 1 + n, cmp);
	
	root[0] = build(0, nums.size() - 1);
	for (int i = 1; i <= n; i ++ ) root[i] = insert(root[i - 1], 0, nums.size() - 1, find(a[i].a));
	
	solve(1, n, 1, n);
	for (int i = 1; i <= n; i ++ ) cout << f[i] << endl;
	return 0;
}
```

---

## 作者：Caiest_Oier (赞：0)

# [AT_abc348_g](https://www.luogu.com.cn/problem/AT_abc348_g)       

将序列按 $B$ 升序排序，有一个暴力做法，钦定 $B$ 的 $\max$ 为 $B_i$，$i=1,2,\dots n$，然后在 $A_1,A_2,\dots A_i$ 中选出前 $k$ 大来更新 $ans_k$，使用主席树做到 $O(n^2\log V)$。          

事实上，这是具有决策单调性的，令 $calc(i,j)$ 表示 $A_1,A_2,A_3,\dots A_i$ 中选最大的 $j$ 个，求和后减去 $B_i$ 的值，$i<j$ 的时候值为 $0$。则当 $calc(i,k)\ge calc(j,k)$ 且 $i>j$ 时，$calc(i,k+1)\ge calc(j,k+1)$。       

具体证明如下。考虑 $calc(j,k+1)$ 比 $calc(j,k)$ 多选了一个数，这个数就是前 $j$ 个数中第 $k+1$ 大的数，这个数在 $calc(i,k)$ 中必定没有选中，且 $calc(i,k)\ge calc(j,k)$，于是在 $calc(i,k)$ 中添上这个数就满足 $calc(i,k+1)\ge calc(j,k+1)$ 了。      

对于一个 $k$，答案相当于 $\max_{i\in[k,n]} calc(i,k)$，于是决策点是单调不降的，使用决策单调性分治加上主席树就可以解决了。复杂度 $O(n\log n\log V)$。         

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXA 1000000000ll
using namespace std;
int n,ans[500003];
pair<int,int>v[500003];
struct Segt{
    int val;
    int val2;
    int lson;
    int rson;
}T[8000003];
int totT,rt[500003];
void modify(int now,int l,int r,int wz){
    T[now].val++;
    T[now].val2+=wz;
    if(l==r)return;
    if(wz<=((l+r)/2)){
        T[++totT]=T[T[now].lson];
        T[now].lson=totT;
        modify(T[now].lson,l,((l+r)/2),wz);
    }
    else{
        T[++totT]=T[T[now].rson];
        T[now].rson=totT;
        modify(T[now].rson,((l+r)/2)+1,r,wz);
    }
    return;
}
int BinSC(int now,int l,int r,int kkk){
    if(l==r)return kkk*l;
    if(T[T[now].rson].val>=kkk)return BinSC(T[now].rson,((l+r)/2)+1,r,kkk);
    return BinSC(T[now].lson,l,((l+r)/2),kkk-T[T[now].rson].val)+T[T[now].rson].val2;
}
void calc(int ql,int qr,int ansl,int ansr){
    if(ql>qr)return;
    if(ansl==ansr){
        for(int i=ql;i<=qr;i++)ans[i]=BinSC(rt[ansl],0,MAXA*2,i)-v[ansl].first;
        return;
    }
    register int mid=((ql+qr)/2),pp=max(ansl,mid),vv;
    for(int i=max(ansl,mid);i<=ansr;i++){
        vv=BinSC(rt[i],0,MAXA*2,mid)-v[i].first;
        if(i==max(ansl,mid)||vv>ans[mid]){
            ans[mid]=vv;
            pp=i;
        }
    }
    calc(ql,mid-1,ansl,pp);
    calc(mid+1,qr,pp,ansr);
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>v[i].second>>v[i].first;
    sort(v+1,v+n+1);
    for(int i=1;i<=n;i++)v[i].second+=MAXA;
    rt[0]=totT=1;
    for(int i=1;i<=n;i++){
        rt[i]=++totT;
        T[totT]=T[rt[i-1]];
        modify(rt[i],0,MAXA*2,v[i].second);
    }
    calc(1,n,1,n);
    for(int i=1;i<=n;i++)cout<<ans[i]-MAXA*i<<endl;
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

按照 $B_i$ 排序后可以钦定出 $\max(B_i)$ 剩下的 $A_i$ 决策集合变成一段前缀，并且一定选的是前 $k-1$ 大，由于会先选择大的再选小的，因此前 $k-1$ 大具有决策单调性，具体地，令 $dp_i$ 表示 $k = i$ 时的答案，令 $p_i$ 表示其决策点，也就是选择 $A_{p_i} - B_{p_i}$ 与 $[1,p_i-1]$ 中 $A_i$ 的前 $i-1$ 大，单次询问可以很方便的用主席树维护出来，再套一层分治优化决策单调性即可做到 $O(n \log n \log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
const int top = 1e9+114;
const int inf = 2e18+114;;
int dp[maxn];
int n;
struct Node{
    int sum,ls,rs;
	int val;
}tr[maxn*70];
struct hhx{
	int a,b;
}a[maxn];
int root[maxn],tot;
inline int kth(int lt,int rt,int L,int R,int k){
    if(lt==rt){
    	return k*lt;
	}
    int mid=(lt+rt-1)>>1;
    if((tr[tr[R].rs].sum-tr[tr[L].rs].sum)>=k){
        return kth(mid+1,rt,tr[L].rs,tr[R].rs,k);
    }
    else{
        return (tr[tr[R].rs].val-tr[tr[L].rs].val)+kth(lt,mid,tr[L].ls,tr[R].ls,k-(tr[tr[R].rs].sum-tr[tr[L].rs].sum));
    }
}
inline void add(int cur,int lst,int lt,int rt,int pos){
    tr[cur].sum=tr[lst].sum+1;
    tr[cur].val=tr[lst].val+pos;
    if(lt==rt){
        return ;
    }
    int mid=(lt+rt-1)>>1;
    if(pos<=mid){
        tr[cur].rs=tr[lst].rs;
        tr[cur].ls=++tot;
        add(tr[cur].ls,tr[lst].ls,lt,mid,pos);
    }
    else{
        tr[cur].ls=tr[lst].ls;
        tr[cur].rs=++tot;
        add(tr[cur].rs,tr[lst].rs,mid+1,rt,pos);
    }
}
void solve(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1;
	int mx=-inf,p=L;
	for(int i=L;i<=R;i++){
        if(i>=mid&&kth(-top,top,root[0],root[i-1],mid-1)+a[i].a-a[i].b>=mx){
            p=i;
            mx=kth(-top,top,root[0],root[i-1],mid-1)+a[i].a-a[i].b;
        }
	}
	dp[mid]=mx;
    solve(l,mid-1,L,p);
    solve(mid+1,r,p,R);
}
bool cmp(hhx A,hhx B){
	return A.b<B.b;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].a>>a[i].b;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) root[i]=++tot,add(root[i],root[i-1],-top,top,a[i].a);
    solve(1,n,1,n);
    for(int i=1;i<=n;i++) cout<<dp[i]<<'\n';
    return 0;
}
```

---

## 作者：__ryp__ (赞：0)

给定长为 $N$ 的两个整数列 $A$ 与 $B$，对于每个 $k = 1, 2, \cdots, N$，选择 $k$ 个互异下标组成集合 $S$，使 $(\sum\limits_{i\in S} A_i) - \max\limits_{i\in S}B_i$ 
最大。

输出每个 $k$ 对应的最大值。

------------

我用的是 $O(n\log^2 n)$ 的主席树 + 决策单调性分治，但是听说有单 $\log$ 的做法。

考虑 $k$ 固定的情况。我们枚举一个 $d\in [k, n]$ 作为 $\max B$ 的下标（先以 $B$ 为关键字排序），那么那个式子的最大值，显然是取 $k - 1$ 个最大的 **满足 $B$ 小于 $B_d$ 的 $A$ 值之和**。因为我们已经按照 $B$ 排序，那么就是取 $d$ 之前的 $k - 1$ 个最大 $A$ 值。明显主席树维护。

接下来观察单调性。一图胜千言，下面是 $k$ 与决策点的关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/z0f4d25e.png)

于是，$k$ 的决策点一定不高于 $k + 1$ 的，也不低于 $k - 1$ 的。这时，我们可以用决策单调性分治来得到 $[1, n]$ 上每个最大值。

最终复杂度是 $T(n) = T(\dfrac n 2) + O(n\log n) = O(n\log^2n)$ 的。

代码：

```c++
#include <iostream>
#include <algorithm>
#define int long long
#define fi first
#define se second
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const int N = 2e5 + 10;
const ll inf = 1e18;
int qcnt[32 * N], qsum[32 * N], ls[32 * N], rs[32 * N], rt[N], cnt = 0, nr = 0;
ll dsc[N], f[N];
pair<ll, ll> z[N];

static inline ll J (ll x) { return dsc[nr++] = x; }
static inline int Q (ll x) { return lower_bound (dsc, dsc + nr, x) - dsc + 1; }

void upd (int &u, int v, int x, int y, int k, ll val)
{
    int mid = (x + y) / 2;
    qcnt[u = ++cnt] = qcnt[v] + 1, qsum[u] = qsum[v] + val, ls[u] = ls[v], rs[u] = rs[v];
    if (x == y) return;
    if (k <= mid) upd (ls[u], ls[v], x, mid, k, val);
    else upd (rs[u], rs[v], mid + 1, y, k, val);
}

ll qry (int u, int x, int y, int k)
{
    int mid = (x + y) / 2;
    if (x == y) return dsc[x - 1] * k;
    if (k <= qcnt[rs[u]]) return qry (rs[u], mid + 1, y, k);
    else return qry (ls[u], x, mid, k - qcnt[rs[u]]) + qsum[rs[u]];
}

void solve (int l, int r, int ql, int qr)
{
    int mid = (ql + qr) / 2, mpos = -1;
    ll mval = -inf;

    if (l > r || ql > qr) return;
    for (int d = max (l, mid); d <= r; d++) {
        ll f = qry (rt[d], 1, nr, mid) - z[d].se;
        if (f > mval) mval = f, mpos = d;
    }

    f[mid] = mval;
    solve (l, mpos, ql, mid - 1), solve (mpos, r, mid + 1, qr);
}

signed main (void)
{
    int n;

    ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> z[i].fi >> z[i].se, J (z[i].fi);
    sort (z + 1, z + n + 1, [](pi &x, pi &y) { return x.se < y.se; }), sort (dsc, dsc + nr), nr = unique (dsc, dsc + nr) - dsc;
    for (int i = 1; i <= n; i++) upd (rt[i], rt[i - 1], 1, nr, Q (z[i].fi), z[i].fi);
    solve (1, n, 1, n);
    for (int i = 1; i <= n; i++) cout << f[i] << '\n';
    return 0;
}


```

---

