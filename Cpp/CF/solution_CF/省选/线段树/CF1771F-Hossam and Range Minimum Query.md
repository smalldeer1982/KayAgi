# Hossam and Range Minimum Query

## 题目描述

Hossam gives you a sequence of integers $ a_1, \, a_2, \, \dots, \, a_n $ of length $ n $ . Moreover, he will give you $ q $ queries of type $ (l, \, r) $ . For each query, consider the elements $ a_l, \, a_{l + 1}, \, \dots, \, a_r $ . Hossam wants to know the **smallest** number in this sequence, such that it occurs in this sequence an **odd** number of times.

You need to compute the answer for each query before process the next query.

## 说明/提示

In the example,

$$l_1 = 1, \, r_1 = 2, $$
$$ l_2 = 1, \, r_2 = 3, $$
$$ l_3 = 2, \, r_3 = 4, $$
$$ l_4 = 1, \, r_4 = 4, $$
$$ l_5 = 2, \, r_5 = 2, $$
$$ l_6 = 1, \, r_6 = 5. $$

## 样例 #1

### 输入

```
5
1 2 1 2 2
6
1 2
0 2
0 6
0 5
2 2
3 7```

### 输出

```
1
2
1
0
2
2```

## 样例 #2

### 输入

```
10
51 43 69 48 23 52 48 76 19 55
10
1 1
57 57
54 62
20 27
56 56
79 69
16 21
18 30
25 25
62 61```

### 输出

```
51
55
19
48
76
19
23
19
55
19```

# 题解

## 作者：World_Creater (赞：13)

吐槽：这题放在 $\text {div.2 F}$ 合适吗（

题目要你找到区间中出现次数为奇数的数中最小的那一个。

考虑使用异或哈希，给每个数一个随机权值，由于异或的优美性质，两两相消，我们有以下结论：若这个区间内存在出现次数为奇数的数，则这段区间对应的随机权值异或和不为 $0$。

这是显然的，因为出现次数为偶数的数，它们随机权值的异或和都被两两抵消了。

现在我们来找出最小的那一个。

考虑使用主席树，记录每个前缀的信息，查询时直接主席树上二分即可，复杂度为 $O((n+q)\log n)$。

代码（注意这里并没有对 $a_i$ 离散化）：
```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
const int inf=2e9;
int n,a[200005],root[200005];
mt19937 rnd(random_device{}());
map<int,int> mp;
struct node{
	int lc,rc,val;
};
struct segtree{
	node tree[20000005];
	int cnt=0;
	#define M(l,r) (l+(r-l)/2)
	void clone(int &p)
	{
		tree[++cnt]=tree[p];
		p=cnt;
	}
	void pushup(int p)
	{
		tree[p].val=tree[tree[p].lc].val^tree[tree[p].rc].val;
	}
	void modify(int &p,int l,int r,int x,int k)
	{
		clone(p);
		if(l==r)
		{
			tree[p].val^=k;
			return ;
		}
		int mid=M(l,r);
		if(x<=mid) modify(tree[p].lc,l,mid,x,k);
		else modify(tree[p].rc,mid+1,r,x,k);
		pushup(p);
	}
	int query(int p1,int p2,int l,int r)
	{
		if(l==r) return l;
		int lval=tree[tree[p1].lc].val^tree[tree[p2].lc].val;
		int mid=M(l,r);
		if(lval!=0) return query(tree[p1].lc,tree[p2].lc,l,mid);//主席树上二分，如果左子树的异或和不为 0，我们可以断言左子树内必然存在一个出现次数为奇数的数，往左子树走。
		else return query(tree[p1].rc,tree[p2].rc,mid+1,r);//否则往右子树走
	}
}T;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!mp[a[i]]) mp[a[i]]=rnd();
		root[i]=root[i-1];
		T.modify(root[i],0,inf,a[i],mp[a[i]]);
	}
	int q;
	cin>>q;
	int lst=0;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		l^=lst,r^=lst;
		lst=T.query(root[l-1],root[r],0,inf);
		if(lst==inf) lst=0;
		cout<<lst<<"\n";
	}
}
```

---

## 作者：thousands_of_years (赞：8)

望着全是随机化的题解区，仅有着一篇稍稍提起过一种不优美的分块，经过一中午的冥思苦想和带着分块的忠诚，一篇 $O(n\sqrt{n})$ 的题解终于诞生！！！~~好了批话结束~~

## Solution

不优美的分块原理是对于每一个前缀，用一个 $n$ 位的二进制串记录每个数出现次数的奇偶性。查询时异或一下，找到最低的非零位即可。因为空间爆炸，所以对原序列分块，记录每个整块末尾时的情况，因为只用奇偶性，所以可以用 `bitset` 来记录，关于这种情况可以去看 Mars\_Dingdang 大佬的[题解](https://www.luogu.com.cn/article/a7qwaztf)。

我们沿用这个思想，唯一不是 $\sqrt{n}$ 的操作为值域上找到最低的非零位，为了去除这个污点，我们可以想到值域分块，可是如何操作呢？

我们需要了解一点，值域分块的块标记不是来记录具体信息的，而是判断此处有没有解的标识，`bitset` 就是用二进制串来充当了具体信息，由于是记录每个数出现次数的奇偶性，所以它的异或就是在查看两处是否有差异，是否出现了奇数次出现次数。

所以我们将 `bitset` 的 $64$ 位扩大为 $\sqrt{n}$ 位，不记录这具体信息，而是改用哈希，这里并不是其他题解的随机化的异或哈希，这只是将 $\sqrt{n}$ 位哈希变为一个抽象信息。

在原序列分块处，你再记录一下每个整块末尾时，从第一位到当前整块末尾时值域分块上每个块的抽象信息。这里的空间复杂度是 $O(\sqrt{n} \times \sqrt{n}) = O(n)$ 的。

接下来，小于两个块长的区间暴力处理，否则先将左右两边散块分别合并到左端点所在块和右端点所在块左边的块，然后在值域分块上找最小的有差异的块，再在该块中找到最小的有差异的数，即使答案。

到此，全操作都为 $\sqrt{n}$ 的操作。

实现代码时，要注意离散化，还有这代码虽然时间复杂度为 $O(n\sqrt{n})$，但是这常数可能有点大，需加上快读和火车头。~~这怎么比不优美的分块还慢啊！！！~~

## Code

[AC code](https://codeforces.com/contest/1771/submission/325001027)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9,M=1e6+9,mod=1e9+7,has=131;
int a[N],b[N],bel[N],lenn;
bitset<200002> qq[600],q;
int f[600][600];//f[i][j] : 从第一个数到第i个序列块末尾时值域块上的抽象信息
int bell[600],lin[N];
long long op[600];int n;
inline int fac(int a,int b)//取模优化
{
	if(a>b) return a-b;
	return a-b+mod;
}
inline int qw(int a,int b)
{
	if(a+b>mod) return a+b-mod;
	return a+b;
}
inline int findd(int l,int r)//值域分块
{
	for(int i=1;i<=bel[n];i++)
	{
		if(f[l][i]!=f[r][i])
		{
			for(int j=(i-1)*lenn+1;j<=i*lenn;j++)
			{
				if(qq[l][j]!=qq[r][j])
				{
					return j;
				}
			}
			return 0;
		}
	}
	return 0;
}
signed main()
{
	cin>>n;
	lenn=sqrt(n);
	for(int i=1;i<=n;i++)
		cin>>a[i],b[i]=a[i],bel[i]=(i-1)/lenn+1;
	op[0]=1;
	for(int i=1;i<=lenn;i++)
	{
		op[i]=op[i-1]*has%mod;
	}
	sort(b+1,b+1+n);
	int len=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+1+len,a[i])-b;//离散化
	int bl=1;
	for(int i=1;i<=n;i++)//预处理
	{
		if(bl!=bel[i])
		{
			qq[bl]=q;
			for(int j=1;j<=bel[n];j++)
			{
				f[bl][j]=bell[j];
			}
			bl=bel[i];
		}
		if(q[a[i]]) q[a[i]]=0,bell[bel[a[i]]]=fac(bell[bel[a[i]]],op[a[i]-(bel[a[i]]-1)*lenn]);
		else q[a[i]]=1,bell[bel[a[i]]]=qw(bell[bel[a[i]]],op[a[i]-(bel[a[i]]-1)*lenn]);
	}
	bl=bel[n];
	qq[bl]=q;
	for(int j=1;j<=bel[n];j++)
	{
		f[bl][j]=bell[j];
	}
	int m,last=0;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int l,r;
		cin>>l>>r;
		l^=last;
		r^=last;
		int ans=99999999;
		if(bel[r]-bel[l]<=1)
		{
			for(int j=l;j<=r;j++)
			{
				lin[a[j]]++;
			}
			for(int j=l;j<=r;j++)
			{
				if(lin[a[j]]&1)
					ans=min(ans,a[j]);
			}
			for(int j=l;j<=r;j++)
			{
				lin[a[j]]=0;
			}
			if(ans==99999999)
				ans=0;
			last=b[ans];
		}
		else
		{
//			cout<<141;
			int ll=bel[l],rr=bel[r];
			for(int j=l;j<=ll*lenn;j++)//处理散块
			{
				if(qq[ll][a[j]])
				{
					qq[ll][a[j]]=0;
					f[ll][bel[a[j]]]=fac(f[ll][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
				else
				{
					qq[ll][a[j]]=1;
					f[ll][bel[a[j]]]=qw(f[ll][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
			}
			for(int j=(rr-1)*lenn+1;j<=r;j++)
			{
				if(qq[rr-1][a[j]])
				{
					qq[rr-1][a[j]]=0;
					f[rr-1][bel[a[j]]]=fac(f[rr-1][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
				else
				{
					qq[rr-1][a[j]]=1;
					f[rr-1][bel[a[j]]]=qw(f[rr-1][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
			}
			ans=findd(ll,rr-1);
			last=b[ans];
			for(int j=l;j<=ll*lenn;j++)//还原
			{
				if(qq[ll][a[j]])
				{
					qq[ll][a[j]]=0;
					f[ll][bel[a[j]]]=fac(f[ll][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
				else
				{
					qq[ll][a[j]]=1;
					f[ll][bel[a[j]]]=qw(f[ll][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
			}
			for(int j=(rr-1)*lenn+1;j<=r;j++)
			{
				if(qq[rr-1][a[j]])
				{
					qq[rr-1][a[j]]=0;
					f[rr-1][bel[a[j]]]=fac(f[rr-1][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
				else
				{
					qq[rr-1][a[j]]=1;
					f[rr-1][bel[a[j]]]=qw(f[rr-1][bel[a[j]]],op[a[j]-(bel[a[j]]-1)*lenn]);
				}
			}
		}
		cout<<last<<endl;
	}
	return 0;
}
```

---

## 作者：StayAlone (赞：6)

以此纪念自己 div2 杀到了 A。

### 题意

给定一个长度为 $n$ 的序列 $a_i$，多组询问 $[l, r]$ 中出现次数为奇数的最小值。若不存在输出 $0$。强制在线。

- $1\leq n,q \leq 2\times 10^5,1\leq a_i \leq 10^9$。

### 思路

容易联想到一个数出现奇数次异或起来是其本身，偶数次异或起来就是 $0$。顺着就能想到一种不容易出错的算法：

可持久化权值线段树维护值的异或和。叶子节点第 $i$ 个位置等于 $cnt_i \times i$，其中 $cnt_i$ 表示数 $i$ 的出现次数模 $2$。其它节点表示左右儿子的异或和。

询问时主席树上二分，如果左区间的这些值异或起来不是 $0$，就往左走；反之，往右走。

这个做法显然是错的，样例 2 非常良心地 hack 掉了。例如 $(11000)_2,(00111)_2,(11111)_2$。这三个数都只出现了一次，但是异或起来正好是 $0$，导致我们以为这里没有答案。

考虑数据随机时，这样的情况极难出现。[这个帖子](https://www.luogu.com.cn/discuss/548009) 简要地证明了其概率是小于等于 $\dfrac{1}{V}$ 的，其中 $V$ 是值域。

而此题中，我们可以考虑重新给维护的可持久化线段树定义：叶子节点第 $i$ 个位置等于 $cnt_i \times w_i$，其中 $cnt_i$ 表示数 $i$ 的出现次数模 $2$，$w_i$ 是一个随机的固定权值。

因此，为了方便主席树动态开点的空间，使用 mt19937 获得 unsigned int 范围内的随机数即可。代码中为了避免各种细节问题，将 $w_i$ 限定在 $[1,2^{30}]$ 之间。出错概率已经极低，约 $\frac{1}{10^9}$。

时间复杂度 $\Theta(n\log n)$。

[AC code record](https://www.luogu.com.cn/record/97890243)

```cpp
int n, q, a[MAXN], root[MAXN];
const int P = 1 << 30;
map <int, int> ep1;

struct setr {
	struct {
		int lp, rp, sum;
	} t[MAXN * 35 << 1];
	int tot;
	
	il void pushup(int x) {
		t[x].sum = t[t[x].lp].sum ^ t[t[x].rp].sum;
	}
	
	il int upd(int x, int l, int r, int k, int p) {
		int now = ++tot; t[now] = t[x];
		if (l == r) return t[now].sum ^= p, now;
		int mid = l + r >> 1;
		if (k <= mid) t[now].lp = upd(t[x].lp, l, mid, k, p);
		else t[now].rp = upd(t[x].rp, mid + 1, r, k, p);
		return pushup(now), now;
	}
	
	il int query(int v1, int v2, int l, int r) {
		if (l == r) return t[v2].sum ^ t[v1].sum ? l : 0;
		int now = t[t[v2].lp].sum ^ t[t[v1].lp].sum, mid = l + r >> 1;
		if (now) return query(t[v1].lp, t[v2].lp, l, mid);
		return query(t[v1].rp, t[v2].rp, mid + 1, r);
	}
} T;

int main() {
	mt19937 rand(time(0));
	read(n); rer(i, 1, n, a);
	rep1(i, 1, n) {
		if (ep1.count(a[i])) continue;
		int now = (rand() & P - 1) + 1;
		ep1[a[i]] = now;
	}
	rep1(i, 1, n) root[i] = T.upd(root[i - 1], 1, P, a[i], ep1[a[i]]);
	read(q); int l, r, S = 0;
	while (q--) {
		read(l, r); l ^= S; r ^= S;
		printf("%d\n", S = T.query(root[l - 1], root[r], 1, P));
	}
	rout;
}
```

---

## 作者：5ab_juruo (赞：3)

做法和 [Odd Mineral Resource](https://www.luogu.com.cn/problem/CF1479D) 如出一辙。

奇数次出现联想到异或，先对每个数赋随机权值。对于全局查询，可以维护权值线段树，如果一个区间的异或和为 $0$，则认为这一段不存在答案。

设随机数值域为 $w$，由于每个数都是随机的，所以一个区间答案的错误率为 $\dfrac{1}{w}$，足够小，可以忽略不计。

本题是区间查询，只需要维护主席树，然后查询时线段树二分即可。可以先离散化减小常数。

```cpp
/* name: 1771F
 * author: 5ab
 * created at: 2022-12-12
 */
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned ui;
constexpr int max_n = 200000, max_lgn = 18;

struct nd
{
	int l, r; ui v;
}
tr[(1 << (max_lgn + 1)) + (max_lgn + 1) * max_n];
int a[max_n], b[max_n], grt[max_n + 1], ind = 0;
ui rv[max_n];

inline int nnode(ui val = 0)
{
	tr[ind].l = tr[ind].r = -1;
	tr[ind].v = val;
	return ind++;
}

int build(int l, int r)
{
	int id = nnode();
	if (l < r)
	{
		int mid = (l + r) >> 1;
		tr[id].l = build(l, mid);
		tr[id].r = build(mid + 1, r);
	}
	return id;
}

int modify(int rt, int l, int r, int pos, int val)
{
	if (l == r)
		return nnode(tr[rt].v ^ val);
	int mid = (l + r) >> 1, id = ind++;
	tr[id] = tr[rt];
	
	if (pos <= mid)
		tr[id].l = modify(tr[rt].l, l, mid, pos, val);
	else
		tr[id].r = modify(tr[rt].r, mid + 1, r, pos, val);
	
	tr[id].v = (tr[tr[id].l].v ^ tr[tr[id].r].v);
	return id;
}

int query(int l, int r, int lrt, int rrt)
{
	if ((tr[rrt].v ^ tr[lrt].v) == 0)
		return r + 1;
	if (l == r)
		return l;
	int mid = (l + r) >> 1, lrs = query(l, mid, tr[lrt].l, tr[rrt].l);
	
	if (lrs != mid + 1)
		return lrs;
	return query(mid + 1, r, tr[lrt].r, tr[rrt].r);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b, b + n);
	int m = unique(b, b + n) - b;
	for (int i = 0; i < m; i++)
		rv[i] = rnd();
	
	grt[0] = build(0, m - 1);
	for (int i = 0; i < n; i++)
	{
		int pos = lower_bound(b, b + m, a[i]) - b;
		grt[i + 1] = modify(grt[i], 0, m - 1, pos, rv[pos]);
	}
	
	int q, l, r, lastans = 0;
	
	cin >> q;
	while (q--)
	{
		cin >> l >> r;
		l ^= lastans, r ^= lastans;
		
		int res = query(0, m - 1, grt[l - 1], grt[r]);
		cout << (lastans = (res < m ? b[res] : 0)) << "\n";
	}
	
	return 0;
}
// started coding at: 12-12 07:56:26
// finished debugging at: 12-12 08:25:21
```

---

## 作者：Mars_Dingdang (赞：3)

有趣的题。

## 题目大意
给定一个长度为 $n$ 的序列 $a_i$，以及 $q$ 次询问，每次询问区间 $[l,r]$ 内出现次数为奇数的数中的最小值。

$n,q\le 2\cdot 10^5$，$a_i\le 10^9$，强制在线。

## 大体思路
下面介绍三种思路。

### 我会随机化！
~~zyy：随机化没有前途~~。

一种思路是来自于 $2202$ 年 $\texttt{CSP-S}$ 第三题，即附上随机权值。本题中也可以借鉴类似的方法。

我们给序列 $a_i$ 离散化，然后为排名为 $i$ 的值附上随机权值 $w_i$。

出现次数的奇偶很容易与异或联想起来。因为奇数个相同的数的异或和非零，偶数个相同的数的异或和一定为零。

所以，我们利用主席树记录每个前缀的情况。

我们假设遇到异或和为 $0$ 说明所有数一定都出现偶数次，然后就可以用类似主席树上二分的方法，如果左子树异或和为 $0$ 则递归右子树。

虽然这一方法有一定概率不通过，但事实证明使用 `mt19937` 生成的单随机异或哈希足以通过此题。

由于 $n,q$ 同阶，时间复杂度 $O(n \log n)$。

注意到题目还要求无解时输出 $0$，可以用 `vector` 实现数值分类位置列表，每次查询到答案后二分判断一下即可。

这里附上 [另一道题](https://www.luogu.com.cn/problem/CF1746F)，同样可以用随机权值来搞，但是只做一遍随机可能不够，需要多次，可以用类似模拟退火时的卡时间来搞。

### 我会莫队！
如果这道题不强制在线，完全可以用一个 `set` 装所有出现次数为奇数的数，听起来复杂度是根号还带 $\log$。但我也没仔细想，因为这道题强制在线。

### 我会暴力！
我们不妨回过头想，怎么暴力。

我们可以对于每一个前缀，用一个 $n$ 位的二进制串记录每个数出现次数的奇偶性。查询时异或一下，找到最低的非零位即可。

这样做唯一的缺点在于空间爆炸，空间复杂度达到了惊人的 $O(n^2)$，但是时间复杂度较小。

这时候你可能想到了 `bitset`，但即使使用 `bitset` 存 $n$ 位 $01$ 串，空间复杂度依然有 $O\left(\dfrac {n^2}{\omega}\right)$，被 $2\cdot 10^5$ 卡死了。

但是，我们可以用时间换空间。我们可以对原序列分块，记录每个整块末尾时的情况，这样空间上变成了 $O\left(\dfrac{n^{1.5}}{\omega}\right)$，可以接受。时间复杂度是 $O\left(\left(\dfrac n {\omega}+\sqrt n\right)q\right)$。

根据 CF 官方的说法，手写一个压 $64$ 位的 `bitset` 就可以艹过这道题了。

## 代码
给出的是解法 $1$ 的代码。

```cpp
int n, q, a[maxn], rt[maxn];
int as[maxn], rk[maxn], wei[maxn];
struct node {
	int ls, rs, val;
	#define ls(u) tr[u].ls
	#define rs(u) tr[u].rs
} tr[maxn * 60];
int nV;
inline void expand(int &u) {
	tr[++ nV] = tr[u];
	u = nV;
}
inline void pushup(int u) {
	tr[u].val = tr[ls(u)].val ^ tr[rs(u)].val;
}
inline void modify(int &u, int l, int r, int x, int v) {
	expand(u);
	if(l == r) {
		tr[u].val ^= v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls(u), l, mid, x, v);
	else modify(rs(u), mid + 1, r, x, v);
	pushup(u);
}
inline int query(int u, int v, int l, int r) {
	if(l == r) return l;
	int lval = tr[ls(u)].val ^ tr[ls(v)].val;
	int mid = (l + r) >> 1;
	if(lval != 0) return query(ls(u), ls(v), l, mid);
	else return query(rs(u), rs(v), mid + 1, r);
}
vector <int> pos[maxn];
int main () {
	mt19937 rnd(time(0));
	read(n);
	rep(i, 1, n) read(a[i]), as[i] = a[i];
	sort(as + 1, as + n + 1);
	int nA = unique(as + 1, as + n + 1) - (as + 1);
	rep(i, 1, n) {
		rk[i] = lower_bound(as + 1, as + nA + 1, a[i]) - as;
		if(!wei[rk[i]]) wei[rk[i]] = rnd();
		rt[i] = rt[i - 1];
		modify(rt[i], 1, nA, rk[i], wei[rk[i]]);
		pos[rk[i]].push_back(i);
	}
	int ans = 0;
	read(q);
	while(q --) {
		int l, r;
		read(l); read(r);
		l ^= ans;
		r ^= ans;
		ans = query(rt[l - 1], rt[r], 1, nA);
		int tim = upper_bound(pos[ans].begin(), pos[ans].end(), r) - lower_bound(pos[ans].begin(), pos[ans].end(), l);
		if(!(tim & 1)) ans = 0;
		writeln(ans = as[ans]);
	}
	
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：2)

# CF1771F Solution
赛时没看到 F，C 还 FST 了……

因为它是出现次数奇数，而对一个数异或上奇数次有一个美好的性质：它不为 $0$。我们考虑**随机权值**。

开一棵主席树，第 $i$ 棵树维护 $[1,i]$ 的权值异或和。

若该区间的权值异或和为 $0$，说明该区间内所有数的出现次数都是偶数。反之，则该区间内一定有出现次数是奇数的数。

在查询的时候，能往左子树走就尽量往左子树走，如果不能往左子树走（即左子树权值异或和为 $0$），再往右子树走。

注意一下离散化，由于 ```rand()``` 的上限仅有 $32767$，所以这里采用了 ```mt19937 rng(time(0))``` 来生成随机权值。

```cpp
//FQDYanfei FQDWanhao FQDShenyuan
//简兮简兮，方将万舞。《诗经·简兮》
//朕躬有罪，无以万方；万方有罪，罪在朕躬。《论语·尧曰》
#include<bits/stdc++.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define clr clear
#define fi first
#define se second
#define mx3(a,b,c) ((a>b?a:b)>c?(a>b?a:b):c)
#define mn3(a,b,c) ((a<b?a:b)<c?(a<b?a:b):c)
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define ins insert
#define pii pair<int,int>
#define pqueue priority_queue
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define F2(i,a,b) for(int i=a;i<(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define lowbit(x) (x&(-x))
#define WH while
#define wh(lzm) while(lzm--)
#define CO continue
#define BR break
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
#define HH printf("\n")
#define eb emplace_back
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=109109<<1;
int ls[maxn<<5],rs[maxn<<5],t[maxn<<5],tot;
int a[maxn],b[maxn],p[maxn],h[maxn];
void build(int &o,int l,int r){
	o=++tot;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(ls[o],l,mid);
	build(rs[o],mid+1,r);
}
void update(int &o,int pre,int l,int r,int pos){
	o=++tot;
	ls[o]=ls[pre];rs[o]=rs[pre];t[o]=t[pre]^h[pos];
	int mid=(l+r)>>1;
	if(l==r) return;
    if(pos<=mid) update(ls[o],ls[pre],l,mid,pos);
    else update(rs[o],rs[pre],mid+1,r,pos);
}
int query(int o,int pre,int l,int r){
    int mid=(l+r)>>1;
    if(l==r) return l;
    if(t[ls[o]]^t[ls[pre]]) return query(ls[o],ls[pre],l,mid);
    else return query(rs[o],rs[pre],mid+1,r);
}
mt19937 rng(time(0));
signed main(){
    int n=read(),ans=0;
    F(i,1,n) b[i]=a[i]=read();
    sort(b+1,b+n+1);
    int len=unique(b+1,b+n+1)-b-1;
    F(i,1,n) a[i]=lower_bound(b+1,b+1+len,a[i])-b;
    F(i,1,n) h[i]=(int)rng();
    F(i,1,n) update(p[i],p[i-1],1,len+1,a[i]);
    int fqd=read();
    wh(fqd){
        int l=read(),r=read();
        l^=ans;
        r^=ans;
        int pos=query(p[r],p[l-1],1,len+1);
        if(pos>len) pos=n+1;
        ans=b[pos];
        printf("%lld\n",ans);
    }
}
```

---

## 作者：lzytag (赞：1)

怎么现有题解全是异或哈希？

让我来一个字符串哈希的题解。

其实思路是和其他两篇题解一样的：建立一颗主席树，第 $i$ 棵主席树的第 $j$ 个数代表 $a_1,a_2……a_i$ 中 $j$ 出现次数的奇偶性（$0$ 表示偶数 $1$ 表示 奇数）。

然后查询区间 $[l,r]$ 时直接线段树上二分第 $l-1$ 棵树和第 $r$ 棵第一个不一样的位置就是答案了！可以参考 [【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)。

对于线段树上二分，有两种方式，第一种就是**异或哈希**，给每一种值赋一个随机权值，线段树上节点记录区间内所有权值的异或和就行了，优点是常数小，而且不可能被卡。

另一种方式就是把主席树维护的序列视作字符串，进行**字符串哈希**。和上面的差不多，但他除了本题以外还有更多用法，比如[这题](https://www.luogu.com.cn/problem/P2757)。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
//file head over
const int N = 2e5;
const int M = 5e6;
const int Mod1 = 1011451423,Mod2 = 998244353;
const int bs1 = 19491001,bs2 = 13331;
int a[N+5],n,m;
int v[N+5],b[N+5];
ll pw1[N+5],pw2[N+5];
int rt[N+5];
int cnt,lc[M],rc[M];
ll val1[M],val2[M];
int build(int l,int r)
{
	int c = ++cnt;
	if(l == r) return c;
	int mid = l+r>>1;
	lc[c] = build(l,mid),rc[c] = build(mid+1,r);
	return c;
}
int Upd(int fc,int l,int r,int x)
{
	int c = ++cnt;
	if(l == r)
	{
		if(val1[fc]) val1[c] = val2[c] = 0;
		else val1[c] = val2[c] = 1;
		return c; 
	}
	int mid = (l+r>>1);
	if(mid >= x) lc[c] = Upd(lc[fc],l,mid,x),rc[c] = rc[fc];
	else rc[c] = Upd(rc[fc],mid+1,r,x),lc[c] = lc[fc];
	val1[c] = (val1[lc[c]]*pw1[r-mid] + val1[rc[c]])%Mod1;
	val2[c] = (val2[lc[c]]*pw2[r-mid] + val2[rc[c]])%Mod2;
	//cout<<val1[c]<<" ";
	return c;
}
int Qry(int c,int fc,int l,int r)
{
	if(val1[c] == val1[fc] && val2[c] == val2[fc]) return 0;
	if(l == r) return l;
	int mid = (l+r>>1);
	//cout<<"QQ"<<val1[lc[c]]<<" "<<val1[lc[fc]]<<"\n";
	if(val1[lc[c]] == val1[lc[fc]] && val2[lc[c]] == val2[lc[fc]]) return Qry(rc[c],rc[fc],mid+1,r);
	else return Qry(lc[c],lc[fc],l,mid);
}
int main()
{
	n = read();
	pw2[0] = pw1[0] = 1;
	for(int i = 1;i <= n;i++) v[i] = a[i] = read();
	for(int i = 1;i <= n;i++) pw1[i] = pw1[i-1]*bs1%Mod1,pw2[i] = pw2[i-1]*bs2%Mod2;
	sort(v+1,v+1+n);
	m = unique(v+1,v+1+n)-v-1;
	for(int i = 1;i <= n;i++) b[i] = lower_bound(v+1,v+1+m,a[i])-v;
	rt[0] = build(1,m);
	for(int i = 1;i <= n;i++){rt[i] = Upd(rt[i-1],1,m,b[i]);}
	int Q = read(),lst = 0;
	while(Q--)
	{
		int ql = read()^lst,qr = read()^lst;
		int x = Qry(rt[qr],rt[ql-1],1,m);
		printf("%d\n",lst = v[x]);
	}
	return 0;
}

```

---

## 作者：Cxny (赞：1)

题意：给定长度为 $n$ 的序列 $a$，多次询问 $[l,r]$ 内**最小的出现了奇数次的数**。强制在线。$n\le2\times10^5$。

和 $\text{CSP2022\ T3}$ 一样的套路。出现次数奇偶性？随机权值异或。

开一棵值域主席树，维护值域区间内权值的异或和。

考虑主席树上二分。权值异或和为 $0\iff$ 值域区间内所有数均出现了偶数次。

然后就做完了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ti chrono::system_clock::now().time_since_epoch().count()
#define mid ((l + r) >> 1)
const int maxn = 2e5 + 10, maxm = 2e7;
mt19937 gen(ti);
uniform_int_distribution<> rnd(1, 1e9);
int t[maxm], val[maxn], son[maxm][2], root[maxn], cnt;
void pushup(int p){t[p] = (t[son[p][0]] ^ t[son[p][1]]);}
void modify(int l, int r, int &p, int q, int pos){
    p = ++cnt, t[p] = t[q], son[p][0] = son[q][0], son[p][1] = son[q][1];
    if(l == r) return t[p] ^= val[l], void();
    if(pos <= mid) modify(l, mid, son[p][0], son[q][0], pos);
    else modify(mid + 1, r, son[p][1], son[q][1], pos);
    pushup(p);
}
int query(int l, int r, int p1, int p2){
    if(l == r) return l;
    // cerr << l << ' ' << r << ' ' << (t[son[p1][0]] ^ t[son[p2][0]]) << endl;
    if(t[son[p1][0]] ^ t[son[p2][0]]) return query(l, mid, son[p1][0], son[p2][0]);
    if(!(t[son[p1][1]] ^ t[son[p2][1]])) return 0;
    return query(mid + 1, r, son[p1][1], son[p2][1]);
}
void print(int l, int r, int p){
    if(!p) return;
    printf("%d ~ %d: %d\n", l, r, t[p]);
    print(l, mid, son[p][0]), print(mid + 1, r, son[p][1]);
}
int n, a[maxn], b[maxn], m, q;
signed main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1), m = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= m; i++) val[i] = rnd(gen);
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
        modify(1, m, root[i], root[i - 1], a[i]);
        // puts("-----------");
        // print(1, m, root[i]);
    }
    int lastans = 0;
    scanf("%d", &q);
    while(q--){
        int x, y; scanf("%d%d", &x, &y);
        x ^= lastans, y ^= lastans;
        printf("%d\n", lastans = b[query(1, m, root[x - 1], root[y])]);
    }
    return 0;
}
```

---

## 作者：Lgx_Q (赞：1)

题意：一个数列 $a_1...a_n$，有 $m$ 次询问。每次给出区间 $[l,r]$，求出该区间中出现次数为奇数的最小数。

分析：

适当拆区间 $[l,r]$，从 $[1,r]$ 和 $[1,l-1]$ 方面考虑。

记录集合 $S[i]$ 表示 $[1,i]$ 中出现次数为奇数的数字集合。

发现如果 $S[r]$ 与 $S[l-1]$ 完全相同，那么 $[l,r]$ 区间中没有出现次数为奇数的数。

设一个数 $p$。

记 $Sp[i]$ 为 $[1,i]$ 中小于等于 $p$ **且** 出现次数为奇数的数字集合。

如果 $Sp[r]$ 与 $Sp[l-1]$ 完全相同，那么 $[l,r]$ 中没有小于等于 $p$ **且** 出现次数为奇数的数字集合。

类似于二分的思想。

容易想到利用主席树维护这一二分，集合可以哈希。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=2e5+10;
ll n,m,a[maxn],h[maxn],ht,l,r,lastans,rt[maxn],lc[maxn*24],rc[maxn*24],cnt;
unsigned ll s1[maxn*24],s2[maxn*24],s3[maxn*24];
void modify(ll &p,ll q,ll l,ll r,ll x)
{
	p=++cnt;
	if(l==r)
	{
		if(!s1[q]) s1[p]=x,s2[p]=x*x,s3[p]=x*x*x;
		return;
	}
	ll mid=l+r>>1;
	lc[p]=lc[q]; rc[p]=rc[q];
	if(x<=mid) modify(lc[p],lc[q],l,mid,x);
	else modify(rc[p],rc[q],mid+1,r,x);
	s1[p]=s1[lc[p]]+s1[rc[p]];
	s2[p]=s2[lc[p]]+s2[rc[p]];
	s3[p]=s3[lc[p]]+s3[rc[p]];
}
ll query(ll p,ll q,ll l,ll r)
{
	if(l==r)
	{
		if(s1[p]==s1[q]&&s2[p]==s2[q]&&s3[p]==s3[q]) return 0;
		return l;
	}
	ll mid=l+r>>1;
	if(s1[lc[p]]==s1[lc[q]]&&s2[lc[p]]==s2[lc[q]]&&s3[lc[p]]==s3[lc[q]]) return query(rc[p],rc[q],mid+1,r);
	return query(lc[p],lc[q],l,mid);
}
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		h[++ht]=a[i];
	}
	sort(h+1,h+1+ht);
	ht=unique(h+1,h+1+ht)-h-1;
	for(ll i=1;i<=n;i++)
	{
		a[i]=lower_bound(h+1,h+1+ht,a[i])-h;
		modify(rt[i],rt[i-1],1,ht,a[i]);
	}
	scanf("%lld",&m);
	while(m--)
	{
		scanf("%lld%lld",&l,&r);
		l^=lastans; r^=lastans;
		printf("%lld\n",lastans=h[query(rt[r],rt[l-1],1,ht)]);
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

一道和星战差不多好的 Sum Hash 练习题。顺便记录一下人生中第一次场切 2F，虽然是 VP。

## 思路

考虑先给所有数进行离散化，将值域压进 $10^5$。下文中所有的 $a$ 指的都是离散化之后的。

然后考虑暴力，从 $l$ 到 $r$ 扫一遍，维护一个长度为值域的数组 $bol$，如果 $a_i$ 出现了，就给 $bol_{a_i}$ 异或上 $1$（也就是取反）。那么可以发现扫完之后所有 $bol$ 是 $1$ 的位置都出现了奇数次。

想要快速维护这个数组很简单，只需要一颗主席树。每次，当 $bol_{a_i}$ 目前是 $0$，我们就把主席树里面 $a_i$ 对应的位置改成 $1$，否则改成 $0$。注意操作完之后要给 $bol_{a_i}$ 异或上 $1$。

对于询问，我们取出 $rt_{l-1}$ 对应的线段树和 $rt_r$ 对应的线段树，这两颗线段树的叶子里面节点值不同的（也就是一个是 $0$，一个是 $1$），就是出现了奇数次的位置。

为了找到最小的，我们考虑主席树上二分。我们在两颗线段树上同时走，假设我们已经知道左边有某个 $bol$ 出现了不同的值，我就让两个指针一起走左边，如果右边出现了不同就一起走右边，如果相同我就返回 $0$。

于是问题转化为快速知道某个区间是否有某个 $bol$ 在 $l-1$ 的线段树和 $r$ 的线段树中出现了不同的值，不妨使用 Sum Hash，我给每个 $a_i$ 一个随机权值 $w_{a_i}$，然后在线段树上维护每个节点所管辖区间的随机权值的和。具体来说，维护 $bol_{a_i}\times w_{a_i}$ 这个式子的和。

容易发现如果有某个 $bol$ 出现了不同的值，那么所有包含这个位置的节点在 $l-1$ 号线段树和 $r$ 号线段树上维护的和都不同。和星战类似，错误率非常低。

由于 $bol_{a_i}$ 只有 $1\to 0$ 和 $0\to 1$ 两种，所以只需要分类讨论，然后在主席树上给 $a_i$ 对应的位置加上一个 $w_{a_i}$ 或者 $-w_{a_i}$ 即可。查询时拿出 $l-1$ 和 $r$ 的线段树，在两颗树上同时走，左边维护的和不同就一起走左边，右边维护的和不同就一起走右边，相同就直接返回 $0$。

值得注意的是，如果不采用两个指针同时走的 $O(\log n)$ 算法，而是使用在外面倍增，然后每次查询的 $O(\log^2n)$ 算法会在第 $10$ 个点 TLE。

使用 `rand()` 会在第 $15$ 个点 WA，因为 `rand()` 在 CF 评测机（以及 Windows）的上限是 $32767$（注意某些版本 Linux 下的上限可以达到 `INT_MAX`，但 CF 并不可以），可能比 $n$ 小，请使用更大的 `mt19937`。

## 代码

一些实现细节在代码里面说，感觉文字叙述还是不清晰。

```
//Author:Zealous_YH / Cream_H
//Su Chanzi & Xiao Bao
//Hey Left
//Just enjoy the loneliness
//Open a personal party always stay
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=2e5+10;
int n;
int a[N];
int b[N];
int tot;
int bk[N];
int w[N];
int tf[N];
int rt[N];
int tnt;
int q;
ll st;
map <int,int> p;
mt19937 rnd(time(0));
#define mid ((l+r)>>1)
struct Chairman_Segment_Tree{//普通主席树
    int has[N*50],ls[N*50],rs[N*50];
    il void insert(int &p,int las,int l,int r,int d,int k){
        if(!p){
            tnt++;
            p=tnt;
        }
        has[p]=has[las]+k;
        if(l==r){
            return;
        }
        if(d<=mid){
            insert(ls[p],ls[las],l,mid,d,k);
            rs[p]=rs[las];
        }
        else{
            insert(rs[p],rs[las],mid+1,r,d,k);
            ls[p]=ls[las];
        }
    }
    il ll query(int p,int l,int r,int ml,int mr){
        if(ml<=l&&r<=mr){
            return has[p];
        }
        ll ans=0;
        if(ml<=mid){
            ans+=query(ls[p],l,mid,ml,mr);
        }
        if(mid<mr){
            ans+=query(rs[p],mid+1,r,ml,mr);
        }
        return ans;
    }
    il int binary(int p1,int p2,int l,int r){//在两颗线段树上同时走
        if(has[p1]==has[p2]){//哈希值相同
            return tot+1;//和返回0的作用是一样的，都是为了在下面得到答案时得到0
        }
        if(l==r){
            return l;
        }
        if(has[ls[p1]]!=has[ls[p2]]){//左儿子哈希和不一样就走左儿子
            return binary(ls[p1],ls[p2],l,mid);
        }
        else{//否则是右儿子
            return binary(rs[p1],rs[p2],mid+1,r);
        }
    }
} T;
#undef mid
int main(){
    ios::sync_with_stdio(false);
    srand(time(0));
    cin>>n;
    fr1(i,1,n){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+n+1);//离散化
    fr1(i,1,n){
        if(!p.count(b[i])){
            tot++;
            w[tot]=rnd();//给相同的数随机一个相同的权值
            p[b[i]]=tot;
            bk[tot]=b[i];//存下离散前的值
        }
    }
    fr1(i,1,n){
        a[i]=p[a[i]];
    }
    fr1(i,1,n){
        if(tf[a[i]]==0){
            tf[a[i]]^=1;
            T.insert(rt[i],rt[i-1],1,tot,a[i],w[a[i]]);
        }
        else{
            tf[a[i]]^=1;
            T.insert(rt[i],rt[i-1],1,tot,a[i],-w[a[i]]);
        }//维护文字中说的bol，这里取名叫tf
    }
    cin>>q;
    int lst=0;
    while(q--){
        int l,r;
        cin>>l>>r;
        l^=lst;
        r^=lst;
        int now=T.binary(rt[l-1],rt[r],1,tot);//直接在两棵树上同时走即可
        lst=bk[now];//最后要得到离散前的值
        cout<<lst<<'\n';
    }
    ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji, Lin, Hao, Shun, Hang and You.
```

时间复杂度是 $O(n\log n+q\log n)$。主席树常数比较大，因此还是比较卡。

[AC 记录](https://www.luogu.com.cn/record/97870794)

---

