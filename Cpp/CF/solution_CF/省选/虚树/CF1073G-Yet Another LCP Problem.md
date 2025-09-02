# Yet Another LCP Problem

## 题目描述

设 $ \text{LCP}(s, t) $ 表示字符串 $ s $ 和 $ t $ 的最长公共前缀的长度。记 $ s[x \dots y] $ 表示字符串 $ s $ 从下标 $ x $ 到下标 $ y $（包含两端）的子串。例如，若 $ s = $ "abcde"，则 $ s[1 \dots 3] = $ "abc"，$ s[2 \dots 5] = $ "bcde"。

给定一个长度为 $ n $ 的字符串 $ s $ 和 $ q $ 个询问。每个询问包含两个整数集合 $ a_1, a_2, \dots, a_k $ 和 $ b_1, b_2, \dots, b_l $。对于每个询问，计算 $ \sum\limits_{i = 1}^{k} \sum\limits_{j = 1}^{l}{\text{LCP}(s[a_i \dots n], s[b_j \dots n])} $。

## 说明/提示

关于询问的说明：

1. 在第一个询问中，$ s[1 \dots 7] = \text{abacaba} $ 和 $ s[2 \dots 7] = \text{bacaba} $ 被考虑。该询问的答案为 $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{bacaba}) + \text{LCP}(\text{bacaba}, \text{abacaba}) + \text{LCP}(\text{bacaba}, \text{bacaba}) = 7 + 0 + 0 + 6 = 13 $。
2. 在第二个询问中，$ s[1 \dots 7] = \text{abacaba} $，$ s[2 \dots 7] = \text{bacaba} $，$ s[3 \dots 7] = \text{acaba} $ 和 $ s[7 \dots 7] = \text{a} $ 被考虑。该询问的答案为 $ \text{LCP}(\text{abacaba}, \text{a}) + \text{LCP}(\text{bacaba}, \text{a}) + \text{LCP}(\text{acaba}, \text{a}) = 1 + 0 + 1 = 2 $。
3. 在第三个询问中，$ s[1 \dots 7] = \text{abacaba} $ 与所有后缀进行比较。答案为所有非零值之和：$ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{acaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{abacaba}, \text{a}) = 7 + 1 + 3 + 1 = 12 $。
4. 在第四个询问中，$ s[1 \dots 7] = \text{abacaba} $ 和 $ s[5 \dots 7] = \text{aba} $ 被考虑。该询问的答案为 $ \text{LCP}(\text{abacaba}, \text{abacaba}) + \text{LCP}(\text{abacaba}, \text{aba}) + \text{LCP}(\text{aba}, \text{abacaba}) + \text{LCP}(\text{aba}, \text{aba}) = 7 + 3 + 3 + 3 = 16 $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 4
abacaba
2 2
1 2
1 2
3 1
1 2 3
7
1 7
1
1 2 3 4 5 6 7
2 2
1 5
1 5
```

### 输出

```
13
2
12
16
```

# 题解

## 作者：攀岩高手 (赞：24)

## 题意 ##

给出一个长度为 $n$ 的字符串 $s$ 和 $q$ 次询问，每次询问给出两个集合 $A,B$ ，求

$$ \sum_{i\in A}\sum_{j\in B} lcp(i,j)$$

## 思路 ##

- 求后缀之间的 LCP 之和，自然地想到使用后缀数组；
- 对字符串 $s$ 后缀排序并求出 $height$ 数组，以下提供三种统计答案的方式：

### 一. 分块 ###

- 分块思路简单，代码好写，用来混部分分十分容易；
- 考虑对于集合 $B$ 中的每一个元素向集合 $A$ 统计答案；
- 首先把集合 $A$ **按 $rank$ 排序**后分为约 $\sqrt n$ 个大小为 $\sqrt n$ 的块：
![](https://cdn.luogu.com.cn/upload/pic/52688.png)
- 对于集合 $B$ 中的每一个元素到 $A$ 中的每一个块，计算它对答案的贡献：
![](https://cdn.luogu.com.cn/upload/pic/52689.png)
- 接下来要用到一个定理：$lcp(i,j)=min_{k={rank[i]+1}}^{rank[j]} height[k]\;(i<j)$ 。这个公式的意思是，两个后缀 $i,j\;(i<j)$ 的 LCP 等于从 $rank[i]+1$ 到 $rank[j]$ 的 $height$ 的最小值；
- 有了这个定理，我们可以用一个ST表来维护区间 $height$ 最小值，定义函数 $lcp(i,j)$ 表示后缀$i,j$之间的 LCP 长度，则 $lcp(i,j)$ 可以 O(1) 求出；
- 然后对于每个块，分别求出块中每一个元素到块的左右端点的 LCP ：
![](https://cdn.luogu.com.cn/upload/pic/52690.png)
- 对上面求的东西做一个**前缀和**，用途见下文；
- 统计集合 $B$ 中的某一元素到 $A$ 的一个块的答案分以下三种情况：
1. 当前块左端点的 $rank$ $\leq$ 当前元素的 $rank$ $\leq$ 当前块右端点的 $rank$ :
![](https://cdn.luogu.com.cn/upload/pic/52692.png)
  遇到这种情况，就暴力统计当前元素到块中每一个元素的 LCP ，并将其加到答案中。这是最简单的一种情况；
2. 当前元素的 $rank$ $<$ 当前块左端点的 $rank$ :
![](https://cdn.luogu.com.cn/upload/pic/52693.png)
  如上图，根据上文提到的定理，可以得出块的左端点到块中元素的 LCP 是递减的。先求出当前元素到块的左端点的 LCP 为 $d$ ，那么由定理得，该元素这个块的总答案就是 $\sum_{i\in block} min(d, lcp(block.left,i))$ 。可以在块中二分查找出最后一个与左端点的 LCP 不小于 $d$ 的元素 $p$，则在这个块中，以 $p$ 为分界，左边部分（即紫色部分）的每一个元素的答案都是 $d$ ，答案总和就是 $d$ 乘上这部分的长度；右边部分（即橙色部分）的答案就是它与左端点的 LCP ，使用上文中我们预处理的前缀和即可快速统计；
3. 当前元素的 $rank$ $>$ 当前块右端点的 $rank$ :
  同情况 2 ，预处理出块中每个元素到这个块的右端点的 LCP 的前缀和即可用类似方法统计答案。

#### 复杂度分析 ####

- 倍增法求后缀数组，时间复杂度 $O(nlogn)$ ；
- 集合 $B$ 中有 $O(n)$ 个元素，集合 $A$ 分成 $O(\sqrt n)$ 个块，并对块做了一次二分查找，时间复杂度为 $O(n \sqrt n log \sqrt n)$ ；
- 综上，分块方法的时间复杂度为 $O(n \sqrt n log \sqrt n)$ ，**不能通过本题** 。

#### 代码 ####

```cpp
// 后缀数组+分块 O(n sqrt(n) log sqrt(n)) 
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int MAXN=220000;
const int MAXQ=500;
const int MAXS=256;
const int MAXB=20;
int n, q; char s[MAXN];
int a[MAXN], b[MAXN];
int sa[MAXN], rnk[2*MAXN], rnk1[2*MAXN];
int ct[MAXS], cnt[MAXN], tmp[MAXN];
int height[MAXN], lg[MAXN], h[MAXN][MAXB];
int lef[MAXQ], righ[MAXQ];
int pos[MAXN], cl[MAXN], cr[MAXN];
long long sl[MAXN], sr[MAXN];
inline bool cmp(int a, int b)
{
	return rnk[a]<rnk[b];
}
inline int query(int l, int r)
{
	int k=lg[r-l+1];
	return min(h[l][k], h[r-(1<<k)+1][k]);
}
inline int lcp(int i, int j)
{
	if (i==j) return n-i+1;
	if (rnk[i]>rnk[j]) swap(i, j);
	return query(rnk[i]+1, rnk[j]);
}
int main()
{
//	freopen("CF1073G.in", "r", stdin);
//	freopen("CF1073G.out", "w", stdout);
	scanf("%d%d%s", &n, &q, s+1);
	memset(ct, 0, sizeof ct);
	memset(rnk, 0, sizeof rnk);
	for (int i=1; i<=n; i++) ct[s[i]]=1;
	for (int i=1; i<MAXS; i++) ct[i]+=ct[i-1];
	for (int i=1; i<=n; i++) rnk[i]=ct[s[i]];
	for (int k=0, p=1; k!=n; p<<=1)
	{
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i+p]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) tmp[cnt[rnk[i+p]]--]=i;
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) sa[cnt[rnk[tmp[i]]]--]=tmp[i];
		memcpy(rnk1, rnk, sizeof rnk1);
		rnk[sa[1]]=k=1;
		for (int i=2; i<=n; i++)
		{
			if (rnk1[sa[i]]!=rnk1[sa[i-1]]||rnk1[sa[i]+p]!=rnk1[sa[i-1]+p])
				k++;
			rnk[sa[i]]=k;
		}
	}
	for (int i=1, k=0; i<=n; i++)
	{
		if (rnk[i]==1)
		{
			height[rnk[i]]=k=0;
			continue;
		}
		if (--k<0) k=0;
		while (s[i+k]==s[sa[rnk[i]-1]+k]) k++;
		height[rnk[i]]=k;
	}
	lg[0]=0;
	for (int i=1; i<=n; i++)
		lg[i]=lg[i-1]+(1<<lg[i-1]+1==i);
	for (int i=1; i<=n; i++) h[i][0]=height[i];
	for (int j=1; 1<<j<=n; j++)
		for (int i=1; i+(1<<j)-1<=n; i++)
			h[i][j]=min(h[i][j-1], h[i+(1<<j-1)][j-1]);
	while (q--)
	{
		int k, l;
		scanf("%d%d", &k, &l);
		for (int i=1; i<=k; i++) scanf("%d", &a[i]);
		for (int i=1; i<=l; i++) scanf("%d", &b[i]);
		sort(a+1, a+k+1, cmp);
		int sz=sqrt(k), m=(k-1)/sz+1;
		for (int i=1; i<=m; i++)
			lef[i]=sz*(i-1)+1, righ[i]=min(sz*i, k);
		for (int i=1; i<=k; i++) pos[i]=(i-1)/sz+1;
		for (int i=1; i<=k; i++)
		{
			cl[i]=lcp(a[i], a[lef[pos[i]]]);
			cr[i]=lcp(a[i], a[righ[pos[i]]]);
		}
		sl[0]=sr[0]=0;
		for (int i=1; i<=k; i++) sl[i]=sl[i-1]+cl[i];
		for (int i=1; i<=k; i++) sr[i]=sr[i-1]+cr[i];
		long long ans=0;
		for (int i=1; i<=l; i++)
			for (int j=1; j<=m; j++)
			{
				if (rnk[b[i]]<rnk[a[lef[j]]])
				{
					int d=lcp(b[i], a[lef[j]]);
					int p=upper_bound(cl+lef[j], cl+righ[j]+1, d, greater<int>())-cl;
					ans+=1ll*d*(p-lef[j])+(sl[righ[j]]-sl[p-1]);
				}
				else if (rnk[b[i]]>rnk[a[righ[j]]])
				{
					int d=lcp(b[i], a[righ[j]]);
					int p=lower_bound(cr+lef[j], cr+righ[j]+1, d)-cr-1;
					ans+=1ll*d*(righ[j]-p)+(sr[p]-sr[lef[j]-1]);
				}
				else
					for (int t=lef[j]; t<=righ[j]; t++)
						ans+=lcp(b[i], a[t]);
			}
		printf("%I64d\n", ans);
	}
	return 0;
}
```

#### 提交记录 ####

![](https://cdn.luogu.com.cn/upload/pic/52695.png)

---

### 二. 线段树 ###

- 我们尝试对以上分块的做法进行一些改进。上面的方法之所以要分块，是因为要统计 $B$ 中的元素到 $A$ 中 $rank$ 小于/大于它的 $rank$ 的元素的 LCP 的前缀和。那么我们可不可以做到动态维护这个东西呢？
- 不妨把 $B$ 中的元素也**按 $rank$ 排序**。对于 $B$ 排序后的第 $i$ 个元素，设它与 $A$ 中 $rank$ 小于等于它的元素 $k$ 的 LCP 为 $d[i][j]$ （$j$ 表示 $k$ 按 $rank$ 排序在 $A$ 中排第 $j$ 名）。那么，根据上文提到的定理，从 $d[i]$ 转移到 $d[i+1]$ 时，只需要把所 $d[i]$ 中所有大于 $lcp(B[i],B[i+1])$ 的都改成 $lcp(B[i],B[i+1])$ （这一部分和分块中二分查找的那段实现的是同一个目的），再将 $d[i+1][j]$ 中加入 $A$ 中 $rank[B[i]]<rank[A[k]]\leq rank[B[i+1]]$ 的元素（$j,k$ 含义见上文）就行了；
- 我们发现以上维护 $d[i]$ 的过程，需要支持两个操作：
1. 把所有大于 $k$ 的数改为 $k$ ；
2. 单点修改一个元素。
- 容易发现，$d[i]$ 其实是一个单调的数组，也就是说，所有大于 $k$ 的数都会连在一起。也就是说，可以将其转化为区间修改操作；
- $B[i]$ 的答案，就是 $d[i]$ 的和。因此，还需要支持一个区间求和的操作；
- 综上，我们发现可以用线段树维护整个 $d[i]$ 转移的操作。一颗线段树维护一层 $d[i]$ ，层层递推，即可统计所有 $B[i]$ 的答案；
- 以上过程统计了 $B[i]$ 与 $A[k]\;(rank[A[k]]<=rank[B[i]])$ 的答案。再反向做一遍，即可类似地统计 $B[i]$ 与 $A[k]\;(rank[A[k]]>rank[B[i]])$ 的答案。这两部分的答案相加，就是最终的答案。

#### 复杂度分析 ####

- 倍增法求后缀数组，时间复杂度 $O(nlogn)$ ；
- 线段树的区间修改和单点修改，都是 $O(logn)$ 的。一共要修改 $n$ 次，所以总时间复杂度为 $O(nlogn)$ ，**可以通过本题**。

#### 代码 ####

```cpp
// 后缀数组+线段树 O(nlogn) 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=220000;
const int MAXS=256;
const int MAXB=20;
namespace ST
{
	struct Node
	{
		int l, r;
		long long sum;
		int maxx, minx, cov;
	} tr[4*MAXN];
	struct SegmentTree
	{
		#define lc (o<<1)
		#define rc (o<<1|1)
		inline void assign(int o, int k)
		{
			tr[o].sum=1ll*k*(tr[o].r-tr[o].l+1);
			tr[o].maxx=tr[o].minx=k;
		}
		inline void pushup(int o)
		{
			tr[o].sum=tr[lc].sum+tr[rc].sum;
			tr[o].maxx=max(tr[lc].maxx, tr[rc].maxx);
			tr[o].minx=min(tr[lc].minx, tr[rc].minx);
		}
		inline void cover(int o, int k)
		{
			tr[o].cov=k;
			assign(o, k);
		}
		inline void pushdown(int o)
		{
			if (tr[o].cov==-1) return;
			cover(lc, tr[o].cov);
			cover(rc, tr[o].cov);
			tr[o].cov=-1;
		}
		void build(int o, int l, int r)
		{
			tr[o].l=l; tr[o].r=r; tr[o].cov=-1;
			if (l==r) { assign(o, 0); return; }
			int mid=l+r>>1;
			build(lc, l, mid);
			build(rc, mid+1, r);
			pushup(o);
		}
		void change(int o, int x, int k)
		{
			if (tr[o].l==tr[o].r) { assign(o, k); return; }
			pushdown(o);
			int mid=tr[o].l+tr[o].r>>1;
			if (x<=mid) change(lc, x, k);
			else change(rc, x, k);
			pushup(o);
		}
		void update(int o, int k)
		{
			if (tr[o].maxx<=k) return;
			if (tr[o].minx>k) { cover(o, k); return; }
			pushdown(o);
			update(lc, k);
			update(rc, k);
			pushup(o);
		}
		inline long long query(int o)
		{
			return tr[o].sum;
		}
		#undef lc
		#undef rc
	};
}
int n, q; char s[MAXN];
int a[MAXN], b[MAXN];
int sa[MAXN], rnk[2*MAXN], rnk1[2*MAXN];
int ct[MAXS], cnt[MAXN], tmp[MAXN];
int height[MAXN], lg[MAXN], h[MAXN][MAXB];
ST::SegmentTree st;
inline bool cmp(int a, int b)
{
	return rnk[a]<rnk[b];
}
inline int query(int l, int r)
{
	int k=lg[r-l+1];
	return min(h[l][k], h[r-(1<<k)+1][k]);
}
inline int lcp(int i, int j)
{
	if (i==j) return n-i+1;
	if (rnk[i]>rnk[j]) swap(i, j);
	return query(rnk[i]+1, rnk[j]);
}
int main()
{
//	freopen("CF1073G.in", "r", stdin);
//	freopen("CF1073G.out", "w", stdout);
	scanf("%d%d%s", &n, &q, s+1);
	memset(ct, 0, sizeof ct);
	memset(rnk, 0, sizeof rnk);
	for (int i=1; i<=n; i++) ct[s[i]]=1;
	for (int i=1; i<MAXS; i++) ct[i]+=ct[i-1];
	for (int i=1; i<=n; i++) rnk[i]=ct[s[i]];
	for (int k=0, p=1; k!=n; p<<=1)
	{
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i+p]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) tmp[cnt[rnk[i+p]]--]=i;
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) sa[cnt[rnk[tmp[i]]]--]=tmp[i];
		memcpy(rnk1, rnk, sizeof rnk1);
		rnk[sa[1]]=k=1;
		for (int i=2; i<=n; i++)
		{
			if (rnk1[sa[i]]!=rnk1[sa[i-1]]||rnk1[sa[i]+p]!=rnk1[sa[i-1]+p])
				k++;
			rnk[sa[i]]=k;
		}
	}
	for (int i=1, k=0; i<=n; i++)
	{
		if (rnk[i]==1)
		{
			height[rnk[i]]=k=0;
			continue;
		}
		if (--k<0) k=0;
		while (s[i+k]==s[sa[rnk[i]-1]+k]) k++;
		height[rnk[i]]=k;
	}
	lg[0]=0;
	for (int i=1; i<=n; i++)
		lg[i]=lg[i-1]+(1<<lg[i-1]+1==i);
	for (int i=1; i<=n; i++) h[i][0]=height[i];
	for (int j=1; 1<<j<=n; j++)
		for (int i=1; i+(1<<j)-1<=n; i++)
			h[i][j]=min(h[i][j-1], h[i+(1<<j-1)][j-1]);
	while (q--)
	{
		int k, l;
		scanf("%d%d", &k, &l);
		for (int i=1; i<=k; i++) scanf("%d", &a[i]);
		for (int i=1; i<=l; i++) scanf("%d", &b[i]);
		sort(a+1, a+k+1, cmp);
		sort(b+1, b+l+1, cmp);
		long long ans=0;
		st.build(1, 1, k);
		for (int i=1, j=1; i<=l; i++)
		{
			st.update(1, lcp(b[i], b[i-1])); 
			while (j<=k&&rnk[a[j]]<=rnk[b[i]])
				st.change(1, j, lcp(b[i], a[j])), j++;
			ans+=st.query(1);
		}
		st.build(1, 1, k);
		for (int i=l, j=k; i>=1; i--)
		{
			st.update(1, lcp(b[i], b[i+1]));
			while (j>=1&&rnk[a[j]]>rnk[b[i]])
				st.change(1, j, lcp(b[i], a[j])), j--;
			ans+=st.query(1);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
```

#### 提交记录 ####

![](https://cdn.luogu.com.cn/upload/pic/52698.png)

---

### 三. 单调栈 ###

- 换一个思路，单调栈也可以解决本题；
- 本题单调栈的做法与 [POJ3415](http://poj.org/problem?id=3415) 类似，可以先尝试一下这道题；
- 把集合 $A$ 与集合 $B$ 放在一起得到多重集合 $C$ ，并将 $C$ 按 $rank$ 排序；
- 为了方便，我们定义 $hgt[i]=lcp(C[i], C[i-1])$ 。其实这个 $hgt$ 数组的意义和 $height$ 数组是类似的；
- 维护一个单调栈。栈中的每个元素是一个二元组 $(i,j)$ ，表示这个元素是按 $rank$ 排序后的第 $i$ 名，最前面的 $hgt$ 值大于 $hgt[i]$ 的元素是 $C[j]$ 。这个单调栈中的元素的 $hgt[i]$ 的值是递增的。
- 若发现当前元素 $C[i]$ 的 $hgt$ 值小于栈顶元素的 $hgt$ 值，则将栈顶元素弹出。设栈顶元素为 $C[top]$，则 $[C[top].j-1,C[top].i-1]$ 中每一个元素与 $[C[top].i,i-1]$ 中的每一个元素的 LCP 都是 $hgt[C[top].i]$ 。根据乘法原理，两个区间的长度相乘再乘上 LCP 就是这个区间对答案的贡献。最后，将当前元素入栈，它的 $j$ 就是这次弹出的元素的 $j$ 的最小值；
- 形象一点，单调栈其实维护的是这个东西：
![](https://cdn.luogu.com.cn/upload/pic/52703.png)
- 在上图中，最后一个元素把第五个元素弹出栈，第五个元素维护的就是红色的那个区间。还是根据那个定理，底下绿色区间中的每一个元素与蓝色区间的每一个元素的 LCP 都是第五个元素的高度（即 $hgt[5]$）。这个区间对答案的贡献就是 $3*3*hgt[5]$ ；
- 最后不要忘记把栈中元素弹尽，把答案统计完整。

#### 复杂度分析 ####

- 倍增法求后缀数组，时间复杂度 $O(nlogn)$ ；
- 排序 $O(nlogn)$ ；
- 单调栈中每个元素最多进栈一次出栈一次，因此均摊复杂度为 $O(n)$ ；
- 综上，总时间复杂度为 $O(nlogn)$ 。

#### 代码 ####

```cpp
// 后缀数组+单调栈 O(nlogn) 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=220000;
const int MAXS=256;
const int MAXB=20;
int n, q; char s[MAXN];
int a[MAXN], b[MAXN], c[2*MAXN]; bool d[2*MAXN];
int sa[MAXN], rnk[2*MAXN], rnk1[2*MAXN];
int ct[MAXS], cnt[MAXN], tmp[MAXN];
int height[MAXN], lg[MAXN], h[MAXN][MAXB];
long long sum[2*MAXN];
struct Node
{
	int id, pos;
	Node(int i=0, int p=0): id(i), pos(p) {}
} sta[2*MAXN];
int top;
inline bool cmp(int a, int b)
{
	return rnk[a]<rnk[b];
}
inline int query(int l, int r)
{
	int k=lg[r-l+1];
	return min(h[l][k], h[r-(1<<k)+1][k]);
}
inline int lcp(int i, int j)
{
	if (i==j) return n-i+1;
	if (rnk[i]>rnk[j]) swap(i, j);
	return query(rnk[i]+1, rnk[j]);
}
int main()
{
//	freopen("CF1073G.in", "r", stdin);
//	freopen("CF1073G.out", "w", stdout);
	scanf("%d%d%s", &n, &q, s+1);
	memset(ct, 0, sizeof ct);
	memset(rnk, 0, sizeof rnk);
	for (int i=1; i<=n; i++) ct[s[i]]=1;
	for (int i=1; i<MAXS; i++) ct[i]+=ct[i-1];
	for (int i=1; i<=n; i++) rnk[i]=ct[s[i]];
	for (int k=0, p=1; k!=n; p<<=1)
	{
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i+p]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) tmp[cnt[rnk[i+p]]--]=i;
		memset(cnt, 0, sizeof cnt);
		for (int i=1; i<=n; i++) cnt[rnk[i]]++;
		for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
		for (int i=n; i>=1; i--) sa[cnt[rnk[tmp[i]]]--]=tmp[i];
		memcpy(rnk1, rnk, sizeof rnk1);
		rnk[sa[1]]=k=1;
		for (int i=2; i<=n; i++)
		{
			if (rnk1[sa[i]]!=rnk1[sa[i-1]]||rnk1[sa[i]+p]!=rnk1[sa[i-1]+p])
				k++;
			rnk[sa[i]]=k;
		}
	}
	for (int i=1, k=0; i<=n; i++)
	{
		if (rnk[i]==1)
		{
			height[rnk[i]]=k=0;
			continue;
		}
		if (--k<0) k=0;
		while (s[i+k]==s[sa[rnk[i]-1]+k]) k++;
		height[rnk[i]]=k;
	}
	lg[0]=0;
	for (int i=1; i<=n; i++)
		lg[i]=lg[i-1]+(1<<lg[i-1]+1==i);
	for (int i=1; i<=n; i++) h[i][0]=height[i];
	for (int j=1; 1<<j<=n; j++)
		for (int i=1; i+(1<<j)-1<=n; i++)
			h[i][j]=min(h[i][j-1], h[i+(1<<j-1)][j-1]);
	while (q--)
	{
		int k, l;
		scanf("%d%d", &k, &l);
		for (int i=1; i<=k; i++) scanf("%d", &a[i]);
		for (int i=1; i<=l; i++) scanf("%d", &b[i]);
		sort(a+1, a+k+1, cmp);
		sort(b+1, b+l+1, cmp);
		for (int i=1, j=1, t=1; i<=k||j<=l; t++)
		{
			if (i<=k&&(j>l||rnk[a[i]]<=rnk[b[j]]))
				c[t]=a[i++], d[t]=0;
			else if (j<=l&&(i>k||rnk[a[i]]>rnk[b[j]]))
				c[t]=b[j++], d[t]=1;
		}
		long long ans=0;
		sum[0]=0; top=0;
		for (int i=1; i<=k+l; i++) sum[i]=sum[i-1]+d[i];
		for (int i=1; i<=k+l; i++)
		{
			int t=i;
			while (top>0&&lcp(c[i], c[i-1])<lcp(c[sta[top-1].id], c[sta[top-1].id-1]))
			{
				t=min(t, sta[--top].pos);
				ans+=(1ll*(sum[sta[top].id-1]-sum[sta[top].pos-2])
				         *((i-sta[top].id)-(sum[i-1]-sum[sta[top].id-1]))
					 +1ll*((sta[top].id-sta[top].pos+1)-(sum[sta[top].id-1]-sum[sta[top].pos-2]))
					     *(sum[i-1]-sum[sta[top].id-1]))*lcp(c[sta[top].id], c[sta[top].id-1]);
			}
			sta[top++]=Node(i, t);
		}
		while (top>0)
		{
			top--;
			ans+=(1ll*(sum[sta[top].id-1]-sum[sta[top].pos-2])
			         *((k+l-sta[top].id+1)-(sum[k+l]-sum[sta[top].id-1]))
				 +1ll*((sta[top].id-sta[top].pos+1)-(sum[sta[top].id-1]-sum[sta[top].pos-2]))
				     *(sum[k+l]-sum[sta[top].id-1]))*lcp(c[sta[top].id], c[sta[top].id-1]);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
```

#### 提交记录 ####

![](https://cdn.luogu.com.cn/upload/pic/52701.png)

## 总结 ##

后缀数组可以与多种算法/数据结构结合，比如

- 二分
- 分块
- 单调队列/单调栈
- RMQ数据结构（ST表）
- 树状数组/线段树

灵活应用算法/数据结构和 $height$ 数组的性质，是处理这一类问题的主要方式。

---

## 作者：EnofTaiPeople (赞：12)

### Part1 前言

一打开题解，发现一道字符串 Hash 的题目能看到的却是：
1. SAM+虚树；
2. SA+分块；
3. SA+单调栈。

并不是说这些做法不好，只是我不想写。

### Part2 前置知识

1. 字符串 Hash；
2. 最长公共前缀 LCP；
3. 并查集与最小瓶颈路。

### Part3 前置结论

以下字符串的比较均为字典序的比较。

题目给定了字符串 $S$，我们对它处理 Hash 数组后就可以用二分快速求 $\operatorname{lcp}(x,y)$，进而比较 $S[x\dots n]$ 与 $S[y\dots n]$，时间复杂度为 $O(\log_2n)$。

对于三个字符串 $A,B,C,A\le B\le C$，一定有 $\operatorname{lcp}(A,C)=\min\{\operatorname{lcp}(A,B),\operatorname{lcp}(B,C)\}$，证明如下：

首先，$\operatorname{lcp}(A,C)\le \operatorname{lcp}(A,B)$，因为如果 $\operatorname{lcp}(A,C)>\operatorname{lcp}(A,B)$，那么 $A$ 和 $B$ 在 $\operatorname{lcp}(A,C)$ 前就“分出胜负”了，就必有 $B<A$ 或 $B>C$，不符合前提，同理有 $\operatorname{lcp}(A,C)\le \operatorname{lcp}(B,C)$，于是 $\operatorname{lcp}(A,C)\le \min\{\operatorname{lcp}(A,B),\operatorname{lcp}(B,C)\}$。

然后因为 $A,B$ 的前 $\operatorname{lcp}(A,B)$ 个字符相同，$B,C$ 的前 $\operatorname{lcp}(B,C)$ 个字符相同，所以必有 $A,C$ 的前 $\min\{\operatorname{lcp}(A,B),\operatorname{lcp}(B,C)\}$ 个字符相同，固有 $\operatorname{lcp}(A,C)\ge \min\{\operatorname{lcp}(A,B),\operatorname{lcp}(B,C)\}$。

综上，$\operatorname{lcp}(A,C)=\min\{\operatorname{lcp}(A,B),\operatorname{lcp}(B,C)\}$。

注意这个命题是很显然的，但已经是本题最深的结论了。

### Part4 转化

题目要求：$\sum\limits_{x\in A,y\in B}\operatorname{lcp}(x,y)$。

考虑将 $A,B$ 归并在一起，去重。

然后按字典序排，这一步是复杂度瓶颈，$O(n\log_2^2n)$。

设排完序的数组为 $C_i$，我们可以看作 $C_i$ 和 $C_{i+1}$ 之间边权为 $\operatorname{lcp}(C_i,C_{i+1})$，这时就有 $\operatorname{lcp}(C_x,C_y)$ 为它们之间的边权最小值，也即最小瓶颈路（弱化）。

### Part5 计算

按边权从大到小处理，处理完一条边之后将两点所在并查集并在一起，该边的贡献就是两边连通块相异集合的方案数乘上边权，这里具体化就是记录连通块的 $sz_{x,0}$（$A$ 集合）与 $sz_{x,1}$（$B$ 集合），贡献就是 $w_i(sz_{x,0}sz_{y,1}+sz_{x,1}sz_{y,0})$。

注意这里有一类贡献无法计算，即 $a_x=b_y$ 时，它们直接跳过了合并的过程，所以要特殊处理，即出现这种情况时让答案加上 $n-a_x+1$。

自然溢出单 Hash 被卡了，所以附加了一个取模的 Hash，可以通过，代码较短，不到 2K：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6,M=1e9+7;
using ll=long long;
using ul=unsigned long long;
char s[N];
int n,q,K,L,m,a[N],b[N],c[N],p[N];
int U[N],V[N],w[N],f[N],sz[N][2];
ul pw[N],hs[N],ans;
int rw[N],rs[N];
int gf(int x){return x==f[x]?x:f[x]=gf(f[x]);}
ul gh(int l,int r){
	return hs[r]-hs[l-1]*pw[r-l+1];
}这里是两个 Hash
int gr(int l,int r){
	return(rs[r]+M-ul(rs[l-1])*rw[r-l+1]%M)%M;
}
int \operatorname{lcp}(int x,int y){
	int rl=0,l=1,r=min(n-x+1,n-y+1),md;
	while(l<=r){
		md=l+r>>1;
		if(gh(x,x+md-1)==gh(y,y+md-1)&&gr(x,x+md-1)==gr(y,y+md-1))rl=md,l=md+1;
		else r=md-1;
	}二分求 LCP
	return rl;
}
int main(){
	int i,j,k,x,y;
	scanf("%d%d%s",&n,&q,s+1);
	for(i=pw[0]=1;i<=n;++i)pw[i]=pw[i-1]*41719;
	for(i=1;i<=n;++i)hs[i]=hs[i-1]*41719+s[i];
	for(i=rw[0]=1;i<=n;++i)rw[i]=417191ll*rw[i-1]%M;
	for(i=1;i<=n;++i)rs[i]=(417191ll*rs[i-1]+s[i])%M;预处理双 Hash
	while(q--){
		scanf("%d%d",&K,&L);
		for(i=1;i<=K;++i)scanf("%d",a+i);
		for(i=1;i<=L;++i)scanf("%d",b+i);
		merge(a+1,a+K+1,b+1,b+L+1,c+1);
		for(i=2,ans=0;i<=K+L;++i)特判a_x=b_y
			if(c[i]==c[i-1])ans+=n-c[i]+1;
		m=unique(c+1,c+K+L+1)-c-1;
		stable_sort(c+1,c+m+1,[&](int x,int y){
			int k=\operatorname{lcp}(x,y);暴力排序，复杂度瓶颈
			return s[x+k]<s[y+k];
		});
		for(i=1;i<=m;++i)
			sz[c[i]][0]=sz[c[i]][1]=0,f[c[i]]=c[i];清空大小及父亲数组
		for(i=1;i<m;++i)
			U[i]=c[i],V[i]=c[i+1],w[i]=\operatorname{lcp}(c[i],c[i+1]),p[i]=i;记边权
		for(i=1;i<=K;++i)++sz[a[i]][0];记点权
		for(i=1;i<=L;++i)++sz[b[i]][1];
		sort(p+1,p+m,[&](int x,int y){return w[x]>w[y];});排边权
		for(i=1;i<m;++i){
			x=gf(U[p[i]]),y=gf(V[p[i]]);
			ans+=ul(w[p[i]])*sz[x][0]*sz[y][1];
			ans+=ul(w[p[i]])*sz[x][1]*sz[y][0];
			f[x]=y,sz[y][0]+=sz[x][0],sz[y][1]+=sz[x][1];
        	合并！
		}printf("%llu\n",ans);
	}
	return 0;
}
```

---

## 作者：command_block (赞：12)

题意:先给出一个串$T$然后每次给出两个后缀集合$A,B$,询问$\sum\limits_{i∈A,j∈B}lcp(i,j)$

解法:**后缀树+虚树**

首先建立原串的后缀树,这里我使用了SAM,因为反串的parent tree就是后缀树,当然你喜欢Ukk也行。

然后,根据$lcp(i,j)=dep(lca(i,j))$,即两个后缀在后缀树上的$lca$的深度等于他们的$lcp$。

那么我们对这些后缀对应的点建立虚树,然后树形统计每个点被作为$lca$的次数,乘上该点到根的距离然后贡献。

dp方法考虑简单容斥,具体见代码$dfs$函数部分。

此外这题建虚树的时候$O(logn)$求$lca$有点不稳,于是就采用了$O(1)$的$ST$表求法。

没有什么细节,写起来很流畅,就是注意数组别爆了。

总的复杂度$O(n+SlogS)$($S=\sum k_i+l_i$)

**Code:**

```cpp
#include<algorithm>
#include<vector>
#include<cstdio>
#define MaxN 200500
using namespace std;
inline int read()
{
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
struct Node
{int t[26],f,len;}a[MaxN<<1];
int tn,las;
char str[MaxN];
void ins(int c)
{
  int np=++tn,p=las; las=np;
  a[np].len=a[p].len+1;
  for (;p&&!a[p].t[c];p=a[p].f)a[p].t[c]=np;
  if (!p)a[np].f=1;
  else {
    int v=a[p].t[c];
    if (a[p].len+1==a[v].len)a[np].f=v;
    else {
      int nv=++tn; a[nv]=a[v];
      a[nv].len=a[p].len+1;
      for (;p&&a[p].t[c]==v;p=a[p].f)a[p].t[c]=nv;
      a[v].f=a[np].f=nv;
    }
  }
}
int tp[MaxN],dis[MaxN<<1],p[21][MaxN<<2],
    dfn[MaxN<<1],tim;
bool cmp(int A,int B){return dfn[A]<dfn[B];}
vector<int> g[MaxN<<1];
void dfspre(int num)
{
  p[0][dfn[num]=++tim]=num;
  for (int i=0;i<g[num].size();i++){
    dis[g[num][i]]=dis[num]+1;
    dfspre(g[num][i]);
    p[0][++tim]=num;
  }
}
int lg2[MaxN<<2];
int minp(int u,int v)
{return dis[u]<dis[v] ? u : v;}
void InitST()
{
  for (int j=0;(1<<(j+1))<=tim;j++)
    for (int i=1;i+(1<<j)<=tim;i++)
      p[j+1][i]=minp(p[j][i],p[j][i+(1<<j)]);
  for (int i=2;i<=tim;i++)lg2[i]=lg2[i/2]+1;
}
int lca(int x,int y)
{
  x=dfn[x];y=dfn[y];
  if (x>y)swap(x,y);
  int j=lg2[y-x+1];
  return minp(p[j][x],p[j][y-(1<<j)+1]);
}
int len,q,a1[MaxN],a2[MaxN],
    in[MaxN<<1],ef,t[MaxN<<1],tot;
inline void add(int pos)
{
  if (in[pos]<ef)
    in[t[++tot]=pos]=ef;
}
int stk[MaxN<<1],top;
long long sum;
int s1[MaxN<<1],s2[MaxN<<1];
void dfs(int num)
{
  int sav=s1[num];
  for (int i=0,v;i<g[num].size();i++){
    dfs(v=g[num][i]);
    s1[num]+=s1[v];
    s2[num]+=s2[v];
  }
  for (int i=0;i<g[num].size();i++)
    sum+=1ll*s1[g[num][i]]*(s2[num]-s2[g[num][i]])*a[num].len;
  sum+=1ll*sav*s2[num]*a[num].len;
}
int main()
{
  len=read();q=read();
  scanf("%s",str);
  las=tn=1;
  for (int i=len-1;i>=0;i--)ins(str[i]-'a');
  for (int i=len-1,p=1;i>=0;i--){
    p=a[p].t[str[i]-'a'];
    tp[i+1]=p;
  }
  for (int i=2;i<=tn;i++)
    g[a[i].f].push_back(i);
  dfspre(1);
  InitST();
  for (int i=1;i<=tn;i++)g[i].clear();
  for (int qt=1,n1,n2;qt<=q;qt++){
    n1=read();n2=read();++ef;
    for (int i=1,sav;i<=n1;i++)
      {add(sav=tp[read()]);s1[sav]++;}
    for (int i=1,sav;i<=n2;i++)
      {add(sav=tp[read()]);s2[sav]++;}
    sort(t+1,t+tot+1,cmp);
    int tmp=tot;
    for (int i=1;i<tmp;i++)
      add(lca(t[i],t[i+1]));
    sort(t+1,t+tot+1,cmp);
    stk[top=1]=t[1];
    for (int i=2;i<=tot;i++){
      while(lca(stk[top],t[i])!=stk[top])top--;
      g[stk[top]].push_back(t[i]);
      stk[++top]=t[i];
    }
    sum=0;dfs(t[1]);
    printf("%I64d\n",sum);
    for (int i=1;i<=tot;i++){
      s1[t[i]]=s2[t[i]]=0;
      g[t[i]].clear();
    }tot=0;
  }
  return 0;
}
```

---

## 作者：Sooke (赞：7)

### 解题思路

太菜不会后缀自动机，来个后缀数组的做法吧。

后缀数组最擅长的就是这类 $lcp$ 问题。不管怎样，先把板子打了。

我们知道：

$$lcp(l,\ r) = \left\{\begin{matrix} n + 1 - l\ \ (rnk_l = rnk_r)\\ \min\limits_{i \in (rnk_l,\ rnk_r]} \{ height_i \}\ \ (rnk_l < rnk_r)\\ \min\limits_{i \in (rnk_r,\ rnk_l]} \{ height_i \}\ \ (rnk_l > rnk_r) \end{matrix}\right.$$

但在这题中，询问的 $a_{1..n}$ 和 $b_{1..n}$ 的大小关系是不确定的。因此，我们首先给它们分别按 $rnk$ 排个序。

排完序后，$a_i$ 可以直接改为 $rnk_{a_i}$，$b_i$ 同理，因为还可以用 $sa$ 转回来。因为懒，下面 $lcp$ 定义直接是：

$$lcp(l,\ r) = \left\{\begin{matrix} n + 1 - sa_l\ \ (l = r)\\ \min\limits_{i \in (l,\ r]} \{ height_i \}\ \ (l < r)\\  \min\limits_{i \in (r,\ l]} \{ height_i \}\ \ (l > r) \end{matrix}\right.$$

然后，我们按着 $lcp$ 的定义，分 $3$ 种情况做，在代码实现中我把第 $1$ 种和第 $2$ 种合并了。又因为第 $2$、$3$ 种情况的做法类似，只需思考其中一种即可。

现在考虑 $b_j \leqslant a_i$ 怎么求 $lcp$ 长度之和。

容易想到 $O(n^2)$ 算法，枚举所有的 $b_j \leqslant a_i$ 结合 $ST$ 表暴力搞 $lcp$。

仔细一想，对于选定的一个 $b_j$，随着 $a_i$ 的增大，$lcp(b_j,\ a_i)$ 是不增的。

所以，可以顺着枚举 $a_i$，之后分 $2$ 种情况。$\forall\ b_j \in (a_{i-1},\ a_i]$，它们在之前没有计算过贡献，因此这些可以暴力求。$\forall\ b_j \leqslant a_{i-1}$，它们在 $a_{i-1}$ 的时候就已经有贡献了，正如上一段所说，这个贡献不增，可以先求出 $(a_{i-1},\ a_i]$ 的 $height$ 最小值，把那些贡献都 $min$ 上这个数。

增加某个值的贡献、给某个区间的值取 $min$……权值线段树的基本操作！

给权值线段树上一个 $clear$ 标记。至于 $j$，也是随着 $i$ 的递增而递增的，比较好维护。

同理，可以求出 $b_j \geqslant a_i$，把重复的 $b_j= a_i$ 的贡献减掉就 $ojbk$ 了。

### 代码实现

超长代码预警！

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

inline int read() {
    char c = getchar(); int n = 0; bool f = false;
    while (c < '0' || c > '9') { if (c == '-') { f = true; } c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return f ? -n : n;
}

const int maxN = 200005, maxLog = 21;

int n, m, max, num, numA, numB, logN, a[maxN], b[maxN], sa[maxN], rnk[maxN], cnt[maxN], old[maxN], f[maxLog][maxN], g[maxN], height[maxN];
std::string str;

typedef long long lol;

struct SegmentTree {
    int cnt[maxN << 2]; lol sum[maxN << 2]; bool clr[maxN << 2];

    inline void pushUp(int u) { cnt[u] = cnt[u << 1] + cnt[u << 1 | 1]; sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
    inline void pushClr(int u) { clr[u] = true; cnt[u] = sum[u] = 0; }
    inline void pushDown(int u) { if (clr[u]) { clr[u] = false; pushClr(u << 1); pushClr(u << 1 | 1); } }
    void modify(int u, int l, int r, int p, int x) {
        if (!p) { return; }
        if (l == r) { cnt[u] += x; sum[u] += 1ll * x * l; return; }
        int mid = l + r >> 1; pushDown(u);
        if (p <= mid) { modify(u << 1, l, mid, p, x); } else { modify(u << 1 | 1, mid + 1, r, p, x); }
        pushUp(u);
    }
    void query(int u, int l, int r, int pl, int pr, int &res) {
        if (pl > pr) { return; }
        if (l == pl && r == pr) { res += cnt[u]; pushClr(u); return; }
        int mid = l + r >> 1; pushDown(u);
        if (pr <= mid) { query(u << 1, l, mid, pl, pr, res); }
        else if (pl > mid) { query(u << 1 | 1, mid + 1, r, pl, pr, res); }
        else { query(u << 1, l, mid, pl, mid, res); query(u << 1 | 1, mid + 1, r, mid + 1, pr, res); }
        pushUp(u);
    }
} tr;

inline void radixSort() {
    for (int i = 1; i <= max; i++) { cnt[i] = 0; }
    for (int i = 1; i <= n; i++) { cnt[rnk[i]]++; }
    for (int i = 2; i <= max; i++) { cnt[i] += cnt[i - 1]; }
    for (int i = n; i; i--) { sa[cnt[rnk[old[i]]]--] = old[i]; }
}
void suffixSort() {
    for (int i = 1; i <= n; i++) { max = std::max(max, rnk[i] = str[i] - 'a' + 1); old[i] = i; }
    radixSort();
    for (int len = 1; true; len <<= 1) {
        for (int i = n - len + 1; i <= n; i++) { old[++num] = i; }
        for (int i = 1; i <= n; i++) { if (sa[i] > len) { old[++num] = sa[i] - len; } }
        radixSort(); memcpy(old, rnk, sizeof(rnk)); rnk[sa[1]] = max = 1;
        for (int i = 2; i <= n; i++) { rnk[sa[i]] = old[sa[i - 1]] == old[sa[i]] && old[sa[i - 1] + len] == old[sa[i] + len] ? max : ++max; }
        if (max >= n) { num = 0; break; } else { num = 0; }
    }
    for (int i = 1, j; i <= n; i++) {
        if (rnk[i] == 1) { height[1] = num = 0; continue; }
        j = sa[rnk[i] - 1]; num = num ? num - 1 : 0;
        while (i + num <= n && j + num <= n && str[i + num] == str[j + num]) { num++; }
        height[rnk[i]] = num;
    }
}

void buildST() {
    for (int i = 1; i <= logN; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) { f[i][j] = std::min(f[i - 1][j], f[i - 1][j + (1 << i - 1)]); }
    }
}
inline int getLcp(int l, int r) {
    if (l > r) { std::swap(l, r); } else if (l == r) { return n + 1 - sa[l]; } else { l++; }
    int logLen = g[r - l + 1]; return std::min(f[logLen][l], f[logLen][r - (1 << logLen) + 1]);
}

int main() {
    n = read(); m = read(); while (1 << logN + 1 <= n) { logN++; }
    std::cin >> str; str = " " + str; suffixSort();
    for (int i = 1; i <= n; i++) { f[0][i] = height[i]; g[i] = log(i) / log(2); } buildST();
    for (lol ans = 0; m; m--, ans = 0) {
        numA = read(); numB = read();
        for (int i = 1; i <= numA; i++) { a[i] = rnk[read()]; } std::sort(a + 1, a + numA + 1);
        for (int i = 1; i <= numB; i++) { b[i] = rnk[read()]; } std::sort(b + 1, b + numB + 1);
        for (int i = 1, j = 1; i <= numA; i++) {
            if (i == 1) { tr.pushClr(1); } else {
                int lcp = getLcp(a[i - 1], a[i]), tmp = 0;
                tr.query(1, 1, n, lcp + 1, n, tmp);
                if (lcp) { tr.modify(1, 1, n, lcp, tmp); }
            }
            for (; j <= numB && b[j] <= a[i]; j++) { tr.modify(1, 1, n, getLcp(b[j], a[i]), 1); }
            ans += tr.sum[1];
        }
        for (int i = 1, j = 1; i <= numB; i++) {
            if (i == 1) { tr.pushClr(1); } else {
                int lcp = getLcp(b[i - 1], b[i]), tmp = 0;
                tr.query(1, 1, n, lcp + 1, n, tmp);
                if (lcp) { tr.modify(1, 1, n, lcp, tmp); }
            }
            for (; j <= numA && a[j] < b[i]; j++) { tr.modify(1, 1, n, getLcp(a[j], b[i]), 1); }
            for (; j <= numA && a[j] <= b[i]; j++) { tr.modify(1, 1, n, getLcp(a[j], b[i]), 1); ans -= getLcp(a[j], b[i]); }
            ans += tr.sum[1];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
```

---

## 作者：万弘 (赞：6)

## CF1073G
题意：求$\sum_i^{|A|}\sum_j^{|B|}\operatorname{LCP}(\operatorname{suf}(a_i),\operatorname{suf}(b_j))$.  $\operatorname{suf}(x)$表示$[x...n]$这个后缀.
 
首先两后缀的 LCP 即为其对应终止节点在后缀树上的 LCA 的状态，那么显然有 LCP 的长度即为后缀树上 LCA 的深度（表示的状态的长度）

那么问题转化为，给两个点集 $A,B,$求
$$
\sum_{a\in A}\sum_{b\in B}\operatorname{dep}(\operatorname{LCA}(a,b))
$$
这就很裸了吧，就是 	[GXOI/GZOI2019]旧词 那题的套路。对于每个 $b$,将其到根的路径上每个点的点权+1，$a$ 的贡献就转化为到根的路径上点权和。直接 LCT/树剖维护就好了。

两个小细节：

1. 可以用 SAM建后缀树。
2. 后缀树是经过压缩的，LCA的深度并不直接是根到他的距离，而应是其表示的状态的长度。

同时那些被压掉的点也是有贡献的，但这些点没有必要真的去修改点权，直接加到下面连的没有被压掉的点上就好了，就变成链上每个点加定值，询问链和，用树剖+线段树/LCT维护。


PS：其实用 LCT 写会短很多~~但我写挂了~~
```cpp
#define MAXN 400011
struct SAM
{
    int t[MAXN][26],pre[MAXN],len[MAXN];
    int last,tot;
    SAM(){tot=last=1;}
    void insert(int w)
    {
        int pos=last,cur=++tot;
        len[cur]=len[pos]+1,last=cur;
        while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
        if(!pos){pre[cur]=1;return;}
        int nxt=t[pos][w];
        if(len[nxt]==len[pos]+1)pre[cur]=nxt;
        else
        {
            int tmp=++tot;
            len[tmp]=len[pos]+1;
            memcpy(t[tmp],t[nxt],sizeof t[nxt]);
            pre[tmp]=pre[nxt],pre[nxt]=pre[cur]=tmp;
            while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
        }
    }
}sam;
struct Segment_Tree
{
    struct node
    {
        ll sum,k,tag;
    }t[MAXN<<2|1];
    #define rt t[num]
    #define tl t[num<<1]
    #define tr t[num<<1|1]
    void pushdown(un l,un r,un num)
    {
        if(!rt.tag)return;
        un mid=(l+r)>>1;
        tl.sum+=tl.k*rt.tag,tl.tag+=rt.tag;
        tr.sum+=tr.k*rt.tag,tr.tag+=rt.tag;
        rt.tag=0;
    }
    void build(int* arr,un l=1,un r=sam.tot,un num=1)
    {
        if(l==r)rt.k=arr[l];
        else
        {
            un mid=(l+r)>>1;
            build(arr,l,mid,num<<1),build(arr,mid+1,r,num<<1|1);
            rt.k=tl.k+tr.k;
        }
    }
    void modify(un ql,un qr,ll k,un l=1,un r=sam.tot,un num=1)
    {
        if(ql<=l&&r<=qr){rt.sum+=k*rt.k,rt.tag+=k;return;}
        pushdown(l,r,num);
        un mid=(l+r)>>1;
        if(ql<=mid)modify(ql,qr,k,l,mid,num<<1);
        if(qr>mid)modify(ql,qr,k,mid+1,r,num<<1|1);
        rt.sum=tl.sum+tr.sum;
    }
    ll Qsum(un ql,un qr,un l=1,un r=sam.tot,un num=1)
    {
        if(ql<=l&&r<=qr)return rt.sum;
        pushdown(l,r,num);
        un mid=(l+r)>>1;ll ans=0;
        if(ql<=mid)ans+=Qsum(ql,qr,l,mid,num<<1);
        if(qr>mid)ans+=Qsum(ql,qr,mid+1,r,num<<1|1);
        return ans;
    }
}sgt;
struct edge{int v,nxt;}e[MAXN];
int cnt=0,last[MAXN];
void adde(int u,int v){e[++cnt].v=v,e[cnt].nxt=last[u],last[u]=cnt;}
int size[MAXN],fa[MAXN],mson[MAXN];
void dfs1(int u)
{
    size[u]=1;
    for(int i=last[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        fa[v]=u,dfs1(v);
        if(size[v]>size[mson[u]])mson[u]=v;
        size[u]+=size[v];
    }
}
int top[MAXN],dfn[MAXN],w[MAXN], cur=0;
void dfs2(int u,int now_top)
{
    top[u]=now_top,dfn[u]=++cur,w[cur]=sam.len[u]-sam.len[fa[u]];
    if(mson[u])dfs2(mson[u],now_top);
    for(int i=last[u];i;i=e[i].nxt)
        if(e[i].v!=mson[u])dfs2(e[i].v,e[i].v);
}
void add_to_root(int u,int k)
{
    while(u)sgt.modify(dfn[top[u]],dfn[u],k),u=fa[top[u]];
}
ll Qsum_to_root(int u)
{
    ll res=0;
    while(u)res+=sgt.Qsum(dfn[top[u]],dfn[u]),u=fa[top[u]];
    return res;
}
int ed[MAXN],a[MAXN],b[MAXN];
char s[MAXN];
int main()
{
    int n=read(),m=read();scanf("%s",s+1);
    for(int i=n;i;--i)sam.insert(s[i]-'a'),ed[i]=sam.last;//建反串SAM
    for(int i=2;i<=sam.tot;++i)adde(sam.pre[i],i);//建后缀树
    dfs1(1),dfs2(1,1),sgt.build(w);
    while(m--)
    {
        int k=read(),l=read();
        ll ans=0;
        for(int i=1;i<=k;++i)a[i]=read();
        for(int i=1;i<=l;++i)b[i]=read(),add_to_root(ed[b[i]],1);
        for(int i=1;i<=k;++i)ans+=Qsum_to_root(ed[a[i]]);
        for(int i=1;i<=l;++i)add_to_root(ed[b[i]],-1);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：1kri (赞：6)

#### ~~马上就AHOI了，现在除了简单字符串啥都不会。~~

---

#### 看到这道题目，很容易想到[这题](https://www.luogu.com.cn/problem/P4248)。

然后发现两题本质没有太大区别，都是求 $\sum lcp(i,j)$ 一类的问题。

我们回想一下那道题目应该怎么做：先用 $SA$ 求出 $height$ 数组，然后在 $height$ 数组中跑单调栈。

对于这道题目，显然不能直接建 $height$ ，会超时。

---

#### 我们来看下 $height$ 数组的定义： 
排名为 $i$ 的后缀与排名为 $i-1$ 的后缀的 $LCP$ 。这道题目恰好也是 $LCP$ ，但是是每次给出关键点。

---

#### 关键点？于是易想到类似虚树的套路：
我们可以把排名相邻的关键点的 $LCP$ 求出，然后就成了那题。

---

#### 可是排名相邻的关键点的 $LCP$ 怎么求呢？

显然 $LCP(i,j)$ $=$ $\min \limits_{k=i+1}^j LCP(k-1,k)$ ，也就是 $\min \limits_{k=i+1}^j height_k$ 。
（此处 $i,j,k$ 均指排名）。

可以直接线段树维护，这样问题就成功的转换了。

---

#### 然后发现题目是在集合A和B中各选一个数，并不是在同一个集合中

这并不难转换，考虑简单容斥。

令 $calc(A)$ 表示对于集合 $A$ 的答案，那么 $ans=calc(A\cup B)-calc(A)-calc(B)$ 。

然后就做完了，时间复杂度 $O(n\log n)$ 。

#### 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std; 
char s[200005];
int n,T,m,sa[400005],rk[400005],tp[400005],tax[400005],h[400005],height[400005];
struct SGT{
	int tree[1000005];
	SGT(){
		memset(tree,0x7f,sizeof(tree));
		return;
	}
	inline void pushup(int now){
		tree[now]=min(tree[now*2],tree[now*2+1]);
		return;
	}
	inline void tree_update(int now,int nowl,int nowr,int pos,int val){
		if (nowl==nowr){
			tree[now]=val;
			return;
		}
		int mid=(nowl+nowr)/2;
		if (pos<=mid)tree_update(now*2,nowl,mid,pos,val);
		else tree_update(now*2+1,mid+1,nowr,pos,val);
		pushup(now);
		return;
	}
	inline void update(int pos,int val){
		tree_update(1,1,n,pos,val);
		return;
	}
	inline int tree_query(int now,int nowl,int nowr,int lt,int rt){
		if (nowl>=lt&&nowr<=rt)return tree[now];
		int mid=(nowl+nowr)/2,s=1e9;
		if (mid>=lt)s=min(s,tree_query(now*2,nowl,mid,lt,rt));
		if (mid+1<=rt)s=min(s,tree_query(now*2+1,mid+1,nowr,lt,rt));
		return s;
	}
	inline int query(int l,int r){
		return tree_query(1,1,n,l,r);
	}
}sgt;
inline void Qsort(){
	memset(tax,0,sizeof(tax));
	for (int i=1;i<=n;i++)tax[rk[i]]++;
	for (int i=1;i<=m;i++)tax[i]+=tax[i-1];
	for (int i=n;i>=1;i--)
		sa[tax[rk[tp[i]]]--]=tp[i];
	return;
}
inline void Suffix_Sorting(){
	m=200;
	for (int i=1;i<=n;i++)tp[i]=i,rk[i]=(int)(s[i]); 
	Qsort();
	for (int w=1,p=0;p<n;m=p,w*=2){
		p=0;
		for (int i=n-w+1;i<=n;i++)tp[++p]=i;
		for (int i=1;i<=n;i++)
			if (sa[i]>w)tp[++p]=sa[i]-w;
		Qsort();
		swap(rk,tp);
		rk[sa[1]]=1;
		p=1;
		for (int i=2;i<=n;i++){
			if (tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])rk[sa[i]]=p;
			else rk[sa[i]]=++p;
		}
	}
	return;
} 
inline void Get_Height(){
	for (int i=1;i<=n;i++){
		h[i]=max(0,h[i-1]-1);
		while(s[i+h[i]]==s[sa[rk[i]-1]+h[i]]&&i+h[i]<=n&&sa[rk[i]-1]+h[i]<=n)h[i]++;
	}
	for (int i=1;i<=n;i++)height[i]=h[sa[i]];
	return;
}
int a[200005],b[200005],c[400005],tot;
int tail;
struct node{
	int cnt,val;
	node(){
		cnt=val=0;
	}
}q[400005];
ll calc(){
	for (int i=1;i<=tot;i++)c[i]=rk[c[i]];
	sort(c+1,c+1+tot);
	if (tot==1)return 0; 
	tot--;
	for (int i=1;i<=tot;i++)
		if (c[i]==c[i+1])c[i]=n-sa[c[i]]+1;
		else c[i]=sgt.query(c[i]+1,c[i+1]);
	ll nowsum=0,sum=0;
	tail=0;
	for (int i=1;i<=tot;i++){
		node now;
		now.cnt=1,now.val=c[i];
		while(tail>0&&q[tail].val>now.val){
			now.cnt+=q[tail].cnt;
			nowsum-=q[tail].cnt*q[tail].val;
			tail--;
		}
		q[++tail]=now;
		nowsum+=q[tail].cnt*q[tail].val;
		sum+=nowsum;
	}
	return sum;
}
int main(){
	freopen("1073G.in","r",stdin);
	freopen("1073G.out","w",stdout);
	cin>>n>>T;
	scanf("%s",s+1);
	Suffix_Sorting();
	Get_Height();
	for (int i=2;i<=n;i++)sgt.update(i,height[i]);
	while(T--){
		int l1,l2;
		scanf("%d%d",&l1,&l2);
		for (int i=1;i<=l1;i++)scanf("%d",&a[i]);
		for (int i=1;i<=l2;i++)scanf("%d",&b[i]);
		ll ans=0;
		tot=0;
		for (int i=1;i<=l1;i++)c[++tot]=a[i];
		ans-=calc();
		tot=0;
		for (int i=1;i<=l2;i++)c[++tot]=b[i];
		ans-=calc();
		tot=0;
		for (int i=1;i<=l1;i++)c[++tot]=a[i];
		for (int i=1;i<=l2;i++)c[++tot]=b[i];
		ans+=calc();
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：1saunoya (赞：5)

### 题意:

~~题目翻译很清楚，告辞。~~


### sol:

我们考虑到 $lcp(x,y)$ 等价于反串SAM上的 $dep_{lca(x,y)}$。

然后我们对 给出串的反串 建一个后缀自动机，然后记一下 $pos_x$ 是 $x$ 这个位置在后缀自动机上的节点位置。

怎么求 $\sum_{a\in A} \sum_{b \in B} lca(a,b)$ 。

考虑给出的集合 $\sum A,\sum B \leq 4\times10^5$。

我们直接虚树就好了吧。如果你做过品酒大会，你应该会下面这个套路。

```cpp
// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
#define Tp template
#define fir first
#define sec second
Tp<class T> void cmax(T& x, const T& y) {
  if (x < y) x = y;
}
Tp<class T> void cmin(T& x, const T& y) {
  if (x > y) x = y;
}
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
Tp<class T> void sort(vector<T>& v) { sort(all(v)); }
Tp<class T> void reverse(vector<T>& v) { reverse(all(v)); }
Tp<class T> void unique(vector<T>& v) { sort(all(v)), v.erase(unique(all(v)), v.end()); }
inline void reverse(string& s) { reverse(s.begin(), s.end()); }
const int SZ = 1 << 23 | 233;
struct FILEIN {
  char qwq[SZ], *S = qwq, *T = qwq, ch;
#ifdef __WIN64
#define GETC getchar
#else
  inline char GETC() { return (S == T) && (T = (S = qwq) + fread(qwq, 1, SZ, stdin), S == T) ? EOF : *S++; }
#endif
  inline FILEIN& operator>>(char& c) {
    while (isspace(c = GETC()))
      ;
    return *this;
  }
  inline FILEIN& operator>>(string& s) {
    s.clear();
    while (isspace(ch = GETC()))
      ;
    if (!~ch) return *this;
    s = ch;
    while (!isspace(ch = GETC()) && ~ch) s += ch;
    return *this;
  }
  inline FILEIN& operator>>(char* str) {
    char* cur = str;
    while (*cur) *cur++ = 0;
    cur = str;
    while (isspace(ch = GETC()))
      ;
    if (!~ch) return *this;
    *cur = ch;
    while (!isspace(ch = GETC()) && ~ch) *++cur = ch;
    *++cur = 0;
    return *this;
  }
  Tp<class T> inline void read(T& x) {
    bool f = 0;
    while ((ch = GETC()) < 48 && ~ch) f ^= (ch == 45);
    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = GETC()) > 47) x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }
  inline FILEIN& operator>>(int& x) { return read(x), *this; }
  inline FILEIN& operator>>(ll& x) { return read(x), *this; }
  inline FILEIN& operator>>(uint& x) { return read(x), *this; }
  inline FILEIN& operator>>(ull& x) { return read(x), *this; }
  inline FILEIN& operator>>(double& x) {
    read(x);
    bool f = x < 0;
    x = f ? -x : x;
    if (ch ^ '.') return *this;
    double d = 0.1;
    while ((ch = GETC()) > 47) x += d * (ch ^ 48), d *= .1;
    return x = f ? -x : x, *this;
  }
} in;
struct FILEOUT {
  const static int LIMIT = 1 << 22;
  char quq[SZ], ST[233];
  int sz, O, pw[233];
  FILEOUT() {
    set(7);
    rep(i, pw[0] = 1, 9) pw[i] = pw[i - 1] * 10;
  }
  ~FILEOUT() { flush(); }
  inline void flush() { fwrite(quq, 1, O, stdout), fflush(stdout), O = 0; }
  inline FILEOUT& operator<<(char c) { return quq[O++] = c, *this; }
  inline FILEOUT& operator<<(string str) {
    if (O > LIMIT) flush();
    for (char c : str) quq[O++] = c;
    return *this;
  }
  inline FILEOUT& operator<<(char* str) {
    if (O > LIMIT) flush();
    char* cur = str;
    while (*cur) quq[O++] = (*cur++);
    return *this;
  }
  Tp<class T> void write(T x) {
    if (O > LIMIT) flush();
    if (x < 0) {
      quq[O++] = 45;
      x = -x;
    }
    do {
      ST[++sz] = x % 10 ^ 48;
      x /= 10;
    } while (x);
    while (sz) quq[O++] = ST[sz--];
  }
  inline FILEOUT& operator<<(int x) { return write(x), *this; }
  inline FILEOUT& operator<<(ll x) { return write(x), *this; }
  inline FILEOUT& operator<<(uint x) { return write(x), *this; }
  inline FILEOUT& operator<<(ull x) { return write(x), *this; }
  int len, lft, rig;
  void set(int l) { len = l; }
  inline FILEOUT& operator<<(double x) {
    bool f = x < 0;
    x = f ? -x : x, lft = x, rig = 1. * (x - lft) * pw[len];
    return write(f ? -lft : lft), quq[O++] = '.', write(rig), *this;
  }
} out;
#define int long long
struct Math {
  vector<int> fac, inv;
  int mod;
  void set(int n, int Mod) {
    fac.resize(n + 1), inv.resize(n + 1), mod = Mod;
    rep(i, fac[0] = 1, n) fac[i] = fac[i - 1] * i % mod;
    inv[n] = qpow(fac[n], mod - 2);
    Rep(i, n - 1, 0) inv[i] = inv[i + 1] * (i + 1) % mod;
  }
  int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % mod)
      if (y & 1) ans = ans * x % mod;
    return ans;
  }
  int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
  }
  int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
  int lcm(int x, int y) { return x * y / gcd(x, y); }
} math;

int n;
const int maxn = 4e5 + 54;

vector<int> g[maxn];
struct suffixautomaton {
  int las, cnt;
  suffixautomaton() { las = cnt = 1; }
  int ch[maxn][26], fa[maxn], len[maxn], pos[maxn];

  void ins(int c, int id) {
    int p = las, np = las = ++cnt;
    len[np] = len[p] + 1, pos[id] = np;
    for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if (!p) {
      fa[np] = 1;
    } else {
      int q = ch[p][c];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        int nq = ++cnt;
        memcpy(ch[nq], ch[q], sizeof(ch[q]));
        len[nq] = len[p] + 1, fa[nq] = fa[q], fa[q] = fa[np] = nq;
        for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
      }
    }
  }

  void ins(char* S) {
    char* Cur = S;
    int qwq = 0;
    while (*Cur) ins((*Cur++) - 'a', ++qwq);
  }

  void build() { rep(i, 2, cnt) g[fa[i]].pb(i); }
} sam;

int dfn[maxn], ed[maxn], idx = 0;

struct LCA {
  int f[maxn][22], dep[maxn];

  void dfs(int u) {
    dfn[u] = ++idx;
    for (int v : g[u]) dep[v] = dep[u] + 1, f[v][0] = u, dfs(v);
    ed[u] = ++idx;
  }

  void solve() {
    dfs(1);
    rep(j, 1, 20) rep(i, 1, sam.cnt) f[i][j] = f[f[i][j - 1]][j - 1];
  }

  int lca(int x, int y) {
    if (dep[x] < dep[y]) x ^= y ^= x ^= y;
    for (int i = 20; ~i; i--)
      if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y) return x;
    for (int i = 20; ~i; i--)
      if (f[x][i] ^ f[y][i]) {
        x = f[x][i], y = f[y][i];
      }
    return f[x][0];
  }
} Lca;

// lcp = rev sam

char s[maxn];

struct Tree {
  int dp[maxn][2], op[maxn << 1], tot = 0, st[maxn], top = 0;
  bool book[maxn];

  int solve(int k1, int k2) {
    tot = 0;
    rep(i, 1, k1) {
      int x;
      in >> x, x = n - x + 1, x = sam.pos[x], dp[x][0] = 1;
      if (!book[x]) op[++tot] = x, book[x] = 1;
    }
    rep(i, 1, k2) {
      int x;
      in >> x, x = n - x + 1, x = sam.pos[x], dp[x][1] = 1;
      if (!book[x]) op[++tot] = x, book[x] = 1;
    }
    sort(op + 1, op + tot + 1, [](int x, int y) { return dfn[x] < dfn[y]; });
    for (int i = 1, lim = tot; i < lim; ++i) {
      int lca = Lca.lca(op[i], op[i + 1]);
      if (!book[lca]) op[++tot] = lca, book[lca] = 1;
    }
    rep(i, 1, tot) book[op[i]] = false;
    for (int i = 1, lim = tot; i <= lim; ++i) op[++tot] = -op[i];
    sort(op + 1, op + tot + 1,
         [](int x, int y) { return (x > 0 ? dfn[x] : ed[-x]) < (y > 0 ? dfn[y] : ed[-y]); });
    int ans = 0;
    rep(i, 1, tot) {
      if (op[i] > 0) {
        int u = op[i];
        st[++top] = u, ans += sam.len[u] * dp[u][0] * dp[u][1];
      } else {
        if (top == 1) {
          dp[st[top]][0] = dp[st[top]][1] = 0, top--;
        } else {
          int u = st[top--], f = st[top];
          ans += sam.len[f] * (dp[f][0] * dp[u][1] + dp[f][1] * dp[u][0]);
          dp[f][0] += dp[u][0], dp[f][1] += dp[u][1], dp[u][0] = dp[u][1] = 0;
        }
      }
    }
    return ans;
  }
} tree;

signed main() {
  // code begin.
  int _;
  in >> n >> _ >> s;
  reverse(s, s + n), sam.ins(s), sam.build(), Lca.solve();
  while (_--) {
    int k1, k2;
    in >> k1 >> k2;
    out << tree.solve(k1, k2) << '\n';
  }
  return 0;
  // code end.
}
```

---

## 作者：2018ljw (赞：3)

首先建立后缀数组，然后考虑处理询问。

一个很显然的做法是按 $height$ 从大到小分组，每次合并时统计两半贡献。使用并查集维护，单次做是 $O(n\alpha(n))$ 的，无法通过。

考虑根号分治，设定阈值 $M$，当 $|A|\ge M$ 时候使用该做法，当 $|A|\le M$ 时，发现暴力复杂度为 $\sum|A||B|\le M\sum|B|$。

总复杂度 $O(\frac {n^2\alpha(n)}{M}+nM)$，平衡复杂度的时候需要 $M$ 略大于 $\sqrt n$，进行一些常数优化即可卡过，[record](https://codeforces.com/contest/1073/submission/202589661)。

$|A|\le M$ 部分纯粹的暴力肯定没有优化空间了，所以考虑着手 $|A|\ge M$ 部分优化。

原做法不优主要因为每次 $height$ 都从 $n$ 枚举到 $1$，但事实上很多时候合并都是无效的，发生有效合并的 $height$ 不超过 $|A|+|B|$ 个，所以只需要把这些 $height$ 拎出来合并即可，复杂度 $O(n\log n)$，[record](https://codeforces.com/contest/1073/submission/202593572)。

---

## 作者：pidan (赞：3)

## 题解 CF1073G Yet Another LCP Problem
[题目链接](https://codeforces.ml/problemset/problem/1073/G)

题意描述
>定义$LCP(S_i,S_j)$为字符串$S$的后缀$i$和后缀$j$的最长公共前缀长度。
>给定一个长为$n$的字符串$S$，$q$次询问，每次询问给出两个正整数集合$A,B$，大小分别为$k,l$，求$\sum\limits_{i\in A,j\in B}LCP(S_i,S_j)$

Solution：

看到单字符串和$LCP$，马上想到后缀树，用$SAM$建出后缀树后，$LCP(S_i,S_j)$就是后缀树上的$Dep_{LCA(S_i,S_j)}$。

现在看到数据范围：$\sum\limits_{i=1}^{q}k_i,\sum\limits_{i=1}^{q}l_i\leq2\times10^5$，直接明示虚树。考虑怎样$DP$，有一个经典的树上统计每条边的经过次数问题，答案是$\sum\limits_{(u,v)\in E}Size_v\times(n-Size_v)$。现在转化成$LCA$的数量，考虑容斥，设$Size_{u,0/1}$表示u的子树中在$A/B$集合中的点数，一个节点子树内的答案就是每个儿子$v$中$A$集合内的点数乘其它儿子中$B$集合内的点数，再加上这个节点上的$A$集合内的点数乘子树中$B$集合内的点数，最后乘上深度。即
$$\sum\limits_{u=1}^{n}[(\sum\limits_{v\in Son(u)}Size_{v,0}\times\sum\limits_{w\in Son(u),w\not= v}Size_{w,1})+(Size_{u,0}-\sum\limits_{v\in Son(u)}Size_{v,0})\times Size_{u,1}]\times Dep_u$$

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
#define N 400005
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define il inline
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
il int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
struct Edge{
	int next,to;
}edge[N<<2];
char S[N];
int n,q,rev[N];
int head[N],num;
void add(int u,int v){
	edge[++num].next=head[u];
	edge[num].to=v;head[u]=num;
}
namespace SAM{
	struct Node{
		int len,link,ch[26];
	}t[N];
	int tot=1,cur=1;
	void extend(char c){
		int p=c-'a',u=++tot;
		t[u].len=t[cur].len+1;
		swap(u,cur);
		while(u&&!t[u].ch[p])t[u].ch[p]=cur,u=t[u].link;
		if(!u)return t[cur].link=1,void();
		int v=t[u].ch[p];
		if(t[v].len==t[u].len+1)return t[cur].link=v,void();
		int w=++tot;
		t[w].len=t[u].len+1;
		t[w].link=t[v].link;
		t[v].link=t[cur].link=w;
		for(int i=0;i<26;i++)t[w].ch[i]=t[v].ch[i];
		while(u&&t[u].ch[p]==v)t[u].ch[p]=w,u=t[u].link;
	}
	void build(){
		int u=1;
		for(int i=n;i>=1;i--){
			u=t[u].ch[S[i]-'a'];
			rev[i]=u;
		}
		for(int i=2;i<=tot;i++)add(t[i].link,i);
	}
}
namespace Tree{
	struct Node{
		int dep,fa,sz,son,seg,top,bot;
	}t[N];
	int dfn;
	void dfs1(int u,int fa){
		t[u].dep=t[fa].dep+1;
		t[u].fa=fa;t[u].sz=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(v==fa)continue;
			dfs1(v,u);
			t[u].sz+=t[v].sz;
			if(t[v].sz>t[t[u].son].sz)t[u].son=v;
		}
	}
	void dfs2(int u,int topf){
		t[u].top=topf;
		t[u].seg=++dfn;
		if(t[u].son)dfs2(t[u].son,topf);
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(v==t[u].fa||v==t[u].son)continue;
			dfs2(v,v);
		}
		t[u].bot=dfn;
	}
	int LCA(int x,int y){
		int fx=t[x].top,fy=t[y].top;
		while(fx!=fy){
			if(t[fx].dep<t[fy].dep)swap(fx,fy),swap(x,y);
			x=t[fx].fa;fx=t[x].top;
		}
		if(t[x].dep>t[y].dep)swap(x,y);
		return x;
	}
}
namespace VirTree{
	vector<int>vir,G[N];
	int stk[N],top;
	int sum[N][2];
	int ans;
	bool cmp(int x,int y){return Tree::t[x].seg<Tree::t[y].seg;}
	void build(){
		sort(vir.begin(),vir.end(),cmp);
		for(int i=vir.size()-2;~i;i--)vir.pb(Tree::LCA(vir[i],vir[i+1]));
		sort(vir.begin(),vir.end(),cmp);
		vir.erase(unique(vir.begin(),vir.end()),vir.end());
		top=0;
		for(auto u:vir){
			while(top&&Tree::t[stk[top]].bot<Tree::t[u].seg)top--;
			if(top)G[stk[top]].pb(u);
			stk[++top]=u;
		}
	}
	void clear(){
		for(auto u:vir)G[u].clear(),sum[u][0]=sum[u][1]=0;
		vir.clear();ans=0;
	}
	void dfs(int u){
		int tmp=sum[u][0];
		for(auto v:G[u]){
			dfs(v);
			sum[u][0]+=sum[v][0];
			sum[u][1]+=sum[v][1];
		}
		for(auto v:G[u])ans+=sum[v][0]*(sum[u][1]-sum[v][1])*SAM::t[u].len;
		ans+=tmp*sum[u][1]*SAM::t[u].len;
	}
}
signed main(){
	n=read();q=read();
	scanf("%s",S+1);
	for(int i=n;i>=1;i--)SAM::extend(S[i]);
	SAM::build();
	Tree::dfs1(1,0);
	Tree::dfs2(1,1);
	while(q--){
		int kl=read(),kr=read();
		for(int i=1,u;i<=kl;i++)
			VirTree::vir.pb(u=rev[read()]),VirTree::sum[u][0]++;
		for(int i=1,u;i<=kr;i++)
			VirTree::vir.pb(u=rev[read()]),VirTree::sum[u][1]++;
		VirTree::build();
		VirTree::dfs(VirTree::stk[1]);
		printf("%lld\n",VirTree::ans);
		VirTree::clear();
	}
	return 0;
}
```
还没完，这题还有另一个做法：

看到$\sum$和$LCA$，马上想到[[GXOI/GZOI2019]旧词](https://www.luogu.com.cn/problem/P5305)的套路，将$A$集合中的点到根的路径区间$+1$，然后区间查询$B$集合中的点到根的路径上权的和。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
#define N 400005
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define il inline
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
il int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
struct Edge{
	int next,to;
}edge[N<<2];
char S[N];
int n,q,rev[N],pos[N];
int kl,A[N],kr,B[N],ans;
int head[N],num;
void add(int u,int v){
	edge[++num].next=head[u];
	edge[num].to=v;head[u]=num;
}
namespace SAM{
	struct Node{
		int len,link,ch[26];
	}t[N];
	int tot=1,cur=1;
	void extend(char c){
		int p=c-'a',u=++tot;
		t[u].len=t[cur].len+1;
		swap(u,cur);
		while(u&&!t[u].ch[p])t[u].ch[p]=cur,u=t[u].link;
		if(!u)return t[cur].link=1,void();
		int v=t[u].ch[p];
		if(t[v].len==t[u].len+1)return t[cur].link=v,void();
		int w=++tot;
		t[w].len=t[u].len+1;
		t[w].link=t[v].link;
		t[v].link=t[cur].link=w;
		for(int i=0;i<26;i++)t[w].ch[i]=t[v].ch[i];
		while(u&&t[u].ch[p]==v)t[u].ch[p]=w,u=t[u].link;
	}
	void build(){
		int u=1;
		for(int i=n;i>=1;i--){
			u=t[u].ch[S[i]-'a'];
			rev[i]=u;
		}
		for(int i=2;i<=tot;i++)add(t[i].link,i);
	}
}
namespace SGT{
	int Sum[N<<2],Val[N<<2],Tag[N<<2],Clr[N<<2];
	void pushup(int k){Sum[k]=Sum[ls]+Sum[rs];}
	void pushdown(int k,int l,int r){
		if(Clr[k]){
			Sum[ls]=Sum[rs]=0;
			Tag[ls]=Tag[rs]=0;
			Clr[ls]=Clr[rs]=1;
			Clr[k]=0;
		}
		if(!Tag[k])return;
		Sum[ls]=Sum[ls]+Tag[k]*Val[ls];
		Sum[rs]=Sum[rs]+Tag[k]*Val[rs];
		Tag[ls]+=Tag[k];
		Tag[rs]+=Tag[k];
		Tag[k]=0;
	}
	void build(int k,int l,int r){
		if(l==r){
			Val[k]=pos[l];
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		Val[k]=Val[ls]+Val[rs];
	}
	void modify(int k,int l,int r,int x,int y){
		if(l>y||r<x||l>r||x>y)return;
		if(l>=x&&r<=y){
			Sum[k]+=Val[k];
			Tag[k]+=1;
			return;
		}
		pushdown(k,l,r);
		if(x<=mid)modify(ls,l,mid,x,y);
		if(mid<y)modify(rs,mid+1,r,x,y);
		pushup(k);
	}
	int query(int k,int l,int r,int x,int y){
		if(l>y||r<x||l>r||x>y)return 0;
		if(l>=x&&r<=y)return Sum[k];
		pushdown(k,l,r);
		if(y<=mid)return query(ls,l,mid,x,y);
		if(mid<x)return query(rs,mid+1,r,x,y);
		return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
	}
}
namespace Tree{
	struct Node{
		int dep,fa,sz,son,seg,top,bot;
	}t[N];
	int dfn;
	void dfs1(int u,int fa){
		t[u].dep=t[fa].dep+1;
		t[u].fa=fa;t[u].sz=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(v==fa)continue;
			dfs1(v,u);
			t[u].sz+=t[v].sz;
			if(t[v].sz>t[t[u].son].sz)t[u].son=v;
		}
	}
	void dfs2(int u,int topf){
		t[u].top=topf;
		t[u].seg=++dfn;
		pos[dfn]=SAM::t[u].len-SAM::t[t[u].fa].len;
		if(t[u].son)dfs2(t[u].son,topf);
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(v==t[u].fa||v==t[u].son)continue;
			dfs2(v,v);
		}
		t[u].bot=dfn;
	}
	int LCA(int x,int y){
		int fx=t[x].top,fy=t[y].top;
		while(fx!=fy){
			if(t[fx].dep<t[fy].dep)swap(fx,fy),swap(x,y);
			x=t[fx].fa;fx=t[x].top;
		}
		if(t[x].dep>t[y].dep)swap(x,y);
		return x;
	}
	void ask_modify(int x,int y){
		int fx=t[x].top,fy=t[y].top;
		while(fx!=fy){
			if(t[fx].dep<t[fy].dep)swap(fx,fy),swap(x,y);
			SGT::modify(1,1,SAM::tot,t[fx].seg,t[x].seg);
			x=t[fx].fa;fx=t[x].top;
		}
		if(t[x].dep>t[y].dep)swap(x,y);
		SGT::modify(1,1,SAM::tot,t[x].seg,t[y].seg);
	}
	int ask_query(int x,int y){
		int fx=t[x].top,fy=t[y].top,res=0;
		while(fx!=fy){
			if(t[fx].dep<t[fy].dep)swap(fx,fy),swap(x,y);
			res+=SGT::query(1,1,SAM::tot,t[fx].seg,t[x].seg);
			x=t[fx].fa;fx=t[x].top;
		}
		if(t[x].dep>t[y].dep)swap(x,y);
		res+=SGT::query(1,1,SAM::tot,t[x].seg,t[y].seg);
		return res;
	}
}
void solve(){
	for(int i=1;i<=kl;i++)
		Tree::ask_modify(1,A[i]);
	for(int i=1;i<=kr;i++)
		ans+=Tree::ask_query(1,B[i]);
}
signed main(){
	n=read();q=read();
	scanf("%s",S+1);
	for(int i=n;i>=1;i--)SAM::extend(S[i]);
	SAM::build();
	Tree::dfs1(1,0);
	Tree::dfs2(1,1);
	SGT::build(1,1,SAM::tot);
	while(q--){
		kl=read(),kr=read();
		for(int i=1;i<=kl;i++)A[i]=rev[read()];
		for(int i=1;i<=kr;i++)B[i]=rev[read()];
		SGT::Clr[1]=1;
		SGT::Sum[1]=SGT::Tag[1]=ans=0;
		solve();
		printf("%lld\n",ans);
	}
	return 0;
}
```
一些细节：

1.$SAM$建后缀树要从后往前插入。

2.第二种做法中，一个节点的贡献并不是深度，而是它在$SAM$中的对应位置的$len$

3.来自pidan血的教训：第二种做法挂两个$log$，跑得极慢，要卡卡常。

---

## 作者：Alex_Wei (赞：3)

> [题目传送门](https://www.luogu.com.cn/problem/CF1073G)。

> 题意简述：给出 $s$，多次询问给出长度分别为 $k,l$ 的序列 $a,b$，求 $\sum_{i=1}^k\sum_{j=1}^l\mathrm{LCP}(s[a_i:n],s[b_j:n])$。

[在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/CF1073G.html)。

Yet Another 套路题。

---

如果你做过 [P4248 [AHOI2013]差异](https://www.luogu.com.cn/problem/P4248) 应该可以很快秒掉这题。

我们先对 $s$ 进行后缀排序，求出 height 数组，并将 $a_i,b_i$ 替换为 $rk_{a_i},rk_{b_i}$，那么题目就变为 $\sum_{i=1}^k\sum_{j=1}^l\min_{k=\min(a_i,b_i)+1}^{\max(a_i,b_i)}ht_k$。

预处理出 $ht$ 的 ST 表以 $\mathcal{O}(1)$ RMQ。然后使用类似上面那题的套路，单调栈求出答案。

具体地，我们要从小到大考虑 $a,b$ 中的每一个位置 $pos$（注意这里的位置指的是排名，因为前面用 $rk_a,rk_b$ 替换了 $a,b$），求出在它前面的所有位置 $p_i\ (p_i\leq pos)$（注意这里可能取到等于号，因为 $a,b$ 中可能有相同的位置）中，与它类型不同的（即若 $pos$ 是 $b$ 中的位置，则 $p_i$ 应该是 $a$ 中的）所有位置 $+1$ 后与它的区间 $ht$ 最小值之和：对 $a,b$ 分别维护一个单调栈 $A,B$。先用 $val=\min_{i=pre+1}^{pos} ht_i$ 更新**两个**单调栈 $A,B$（$pre$ 是上一次考虑的 $pos$），如果 $pre=pos$ 则用 $val=n-sa_{pos}+1$ 更新，**需要注意的是这里的更新不是将一个数压入单调栈 $A$ 或 $B$，因为这个数是不算贡献的（如果算贡献，会导致计算了同属于 $a$ 或同属于 $b$ 的两个位置之间的重复贡献），相当于我们压入了一个宽为 $0$，高为 $val$ 的矩形；** 然后，若当前位置属于 $a$，则计算单调栈 $B$ 中的 “矩形面积和”，否则计算 $A$ 中的矩形面积和；最后，若当前位置属于 $a$，将 $n-sa_{pos}+1$ 压入单调栈 $A$，否则将其压入 $B$，相当于我们压入了一个宽为 $1$，高为 $n-sa_{pos}+1$ 的矩形。所有计算出的 “矩形面积和” 之和即为答案。

时间复杂度 $\mathcal{O}(n\log n+\sum k\log\sum k+\sum l\log \sum l)$（后面的 $\log$ 是排序所需的 $\log$）。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e5+5;
const int K=18;

struct MonotoneStack{
	ll stc[N],l[N],top,sum;
	void modify(int val){
		int len=0;
		while(top&&stc[top]>=val)sum-=stc[top]*l[top],len+=l[top--];
		sum+=len*val,stc[++top]=val,l[top]=len;
	} void push(int val){
		stc[++top]=val,l[top]=1,sum+=val;
	}
}ta,tb;

int n,q,k,l,a[N],b[N];
ll sta[N],stb[N];
char s[N];
struct SA{
	int sa[N],rk[N<<1],ork[N<<1],ht[N];
	int buc[N],id[N],px[N],mi[N][K];
	bool cmp(int a,int b,int w){
		return ork[a]==ork[b]&&ork[a+w]==ork[b+w];
	} void build(){
		int m=1<<7,p=0;
		for(int i=1;i<=n;i++)buc[rk[i]=s[i]]++;
		for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
		for(int i=n;i;i--)sa[buc[rk[i]]--]=i;
		for(int w=1;w<=n;w<<=1,m=p,p=0){
			for(int i=n;i>n-w;i--)id[++p]=i;
			for(int i=1;i<=n;i++)if(sa[i]>w)id[++p]=sa[i]-w;
			for(int i=0;i<=m;i++)buc[i]=0;
			for(int i=1;i<=n;i++)buc[px[i]=rk[id[i]]]++;
			for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
			for(int i=n;i;i--)sa[buc[px[i]]--]=id[i];
			for(int i=1;i<=n;i++)ork[i]=rk[i]; p=0;
			for(int i=1;i<=n;i++)rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		} for(int i=1,k=0;i<=n;i++){
			if(k)k--;
			while(s[i+k]==s[sa[rk[i]-1]+k])k++;
			ht[rk[i]]=k;
		} for(int j=0;j<K;j++)
			for(int i=1;i<=n;i++)
				if(j)mi[i][j]=min(mi[i][j-1],mi[i+(1<<j-1)][j-1]);
				else mi[i][j]=ht[i];
	} int query(int l,int r){
		if(l>r)swap(l,r);
		if(l==r)return n-sa[l]+1;
		if(l+1==r)return ht[r];
		int d=log2(r-(l++));
		return min(mi[l][d],mi[r-(1<<d)+1][d]);
	} ll run(ll k,ll l){
		for(int i=1;i<=k;i++)a[i]=rk[a[i]];
		for(int i=1;i<=l;i++)b[i]=rk[b[i]];
		sort(a+1,a+k+1),sort(b+1,b+l+1);
		ll lp=1,rp=1,ans=0,pre=0;
		while(lp<=k||rp<=l){
			int tp,pos;
			if(lp>k||rp<=l&&b[rp]<a[lp])tp=2,pos=b[rp++];
			else tp=1,pos=a[lp++];
			int val=query(pre,pos);
			ta.modify(val),tb.modify(val);
			if(tp==1)ans+=tb.sum,ta.push(n-sa[pos]+1);
			else ans+=ta.sum,tb.push(n-sa[pos]+1);
			pre=pos;
		} return ans;
	}
}sa;

int main(){
	scanf("%d%d%s",&n,&q,s+1),sa.build();
	while(q--){
		scanf("%d%d",&k,&l);
		for(int i=1;i<=k;i++)scanf("%d",&a[i]);
		for(int i=1;i<=l;i++)scanf("%d",&b[i]);
		cout<<sa.run(k,l)<<endl;
		ta.top=tb.top=ta.sum=tb.sum=0; 
	}
	return 0;
}
```

---

## 作者：shadowice1984 (赞：3)

后缀自动姬/后缀数组都能做

手懒了就打了个后缀自动姬

____________________
### 前置芝士:后缀自动姬

~~不会后缀自动姬的话可以出门左转你站模板区，保教包会~~

### 前置芝士：虚树

~~不会虚树的话可以在你站随便找几道关于虚树的题做做，然后就会了~~

## 本题题解

一句话题意，记lcp(i.j)表示i这个后缀和j这个后缀的最长公共前缀长度

给定一个字符串，每次询问的时候给出两个正整数集合A和B,求

$$\sum_{i \in A,j \in B}lcp(i,j)$$

的值
### 关于parent树的一些常识

你需要知道的事情是,后缀自动姬有n个表示前缀的节点，还有一些表示其他子串的节点，这些点共同构成了后缀自动姬

而后缀自动姬上一个节点i的right集合其实就是i子树中出现的前缀节点，如果p这个前缀节点在i的子树中出现了，那i的right集合中就有p

那么我们借此可以使用后缀自动姬来求两个前缀的最长公共后缀

假设其中一个前缀在后缀自动姬上对应的节点是u另一个节点在后缀自动姬上对应的节点是v的话，这两个前缀的最长公共后缀长度就是lca(u,v)这个节点所能表示的最长子串长度，换句话说就是lca(u,v)的len值

_______________

### 虚树

那好了有了这个结论我们能做什么呢？

我们把原来的串反过来跑后缀自动姬，那么两个后缀在反串上就是两个前缀，而最长公共前缀也变成了最长公共后缀

那么根据我们刚才的转化就是两个节点的lca的len值

但是问题是我们的A和B是两个节点的集合，直接大力枚举点对求lca显然会tle导致gg

怎么办呢？

我们对这两个点集的并集建一个虚树出来

在虚树上dfs，假设我们dfs到了一个点p，那么我们就统计有多少个点对(u,v)满足lca(u,v)=p,然后令答案加上len(p)×点对个数就行了

怎么统计点对个数呢？

我们将所有属于A集合的点染成白色而所有属于B集合的点染成黑色,当然一些点可能没有颜色而另一些点可能既是白色又是黑色

我们令dp(u,0/1)表示u子树当中的白点和黑点的个数转移十分显然

当我们合并两个节点(u,v)其中u是v的父亲的时候，我们会发现以u为lca的点对个数多了

$$dp(u,0)dp(v,1)+dp(u,1)dp(u,0)$$

这么多个，直接给答案贡献上就ok了

然后代码相当好写~

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=2*1e5+10;typedef long long ll;
int n;int m;char mde[N];int v[2*N];int x[2*N];int ct;int al[2*N];int len[2*N];
int fa[2*N][22];int dep[2*N];int dfi[2*N];int dfo[2*N];int df;
bool book[2*N];int op[4*N];int tpop;int st[2*N];int tp;int dp[2*N][2];
inline bool cmp(int a,int b){return ((a<0)?dfo[-a]:dfi[a])<((b<0)?dfo[-b]:dfi[b]);}
inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}
struct suffixautomaton//简易后缀自动姬模板 
{
	int mp[2*N][30];int fa[2*N];int ct;
	inline void ih(){for(int i=1;i<=n;i++)len[i]=i;ct=n+1;}
	inline void ins(int nw,int c)
	{
		int p=(nw==1)?n+1:nw-1;for(;p&&mp[p][c]==0;p=fa[p])mp[p][c]=nw;
		if(p==0){fa[nw]=n+1;return;}int q=mp[p][c];
		if(len[q]==len[p]+1){fa[nw]=q;return;}++ct;len[ct]=len[p]+1;
		for(int i=1;i<=26;i++)mp[ct][i]=mp[q][i];
		for(;p&&mp[p][c]==q;p=fa[p])mp[p][c]=ct;fa[ct]=fa[q];fa[q]=fa[nw]=ct;
	}
	inline void build(){for(int i=1;i<=ct;i++)if(fa[i])add(fa[i],i);}
}sam;
inline void dfs(int u)//倍增求lca 
{
	dfi[u]=++df;
	for(int i=0;fa[u][i];i++)fa[u][i+1]=fa[fa[u][i]][i];dep[u]=dep[fa[u][0]]+1;
	for(int i=al[u];i;i=x[i])fa[v[i]][0]=u,dfs(v[i]);dfo[u]=++df;
}
inline int lca(int u,int v)
{
	if(dep[u]<dep[v])swap(u,v);for(int d=dep[u]-dep[v],i=0;d;d>>=1,i++)if(d&1)u=fa[u][i];
	if(u==v)return u;for(int i=18;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int main()
{
	scanf("%d%d",&n,&m);scanf("%s",mde+1);sam.ih();reverse(mde+1,mde+n+1);
	for(int i=1;i<=n;i++)sam.ins(i,mde[i]-'a'+1);sam.build();dfs(n+1);
	for(int z=1,k1,k2;z<=m;z++)//虚树板子 
	{
		scanf("%d%d",&k1,&k2);tpop=0;
		for(int i=1,t;i<=k1;i++)scanf("%d",&t),t=n-t+1,dp[t][0]=1,op[++tpop]=t,book[t]=true;
		for(int i=1,t;i<=k2;i++)
			{scanf("%d",&t),t=n-t+1,dp[t][1]=1;if(!book[t])op[++tpop]=t,book[t]=true;}
		sort(op+1,op+tpop+1,cmp);
		for(int i=1,lim=tpop,lc;i<lim;i++)
			{lc=lca(op[i],op[i+1]);if(!book[lc])op[++tpop]=lc,book[lc]=true;}
		for(int i=1;i<=tpop;i++)book[op[i]]=false;
		for(int i=1,lim=tpop;i<=lim;i++)op[++tpop]=-op[i];sort(op+1,op+tpop+1,cmp);
		ll ans=0;
		for(int i=1;i<=tpop;i++)
			if(op[i]>0){int u=op[i];st[++tp]=u;ans+=(ll)len[u]*dp[u][0]*dp[u][1];}
			else 
			{
				if(tp==1){dp[st[tp]][0]=dp[st[tp]][1]=0;tp--;continue;}	
				int u=st[tp];tp--;int f=st[tp];
				ans+=(ll)len[f]*((ll)dp[f][0]*dp[u][1]+(ll)dp[f][1]*dp[u][0]);
				dp[f][0]+=dp[u][0];dp[f][1]+=dp[u][1];dp[u][0]=dp[u][1]=0;
			}printf("%lld\n",ans);
	}return 0;//拜拜程序~ 
}
```




---

## 作者：Gaode_Sean (赞：2)

题解区里似乎还没有 SA + 并查集的做法，这里补上。

由于题面中出现了“子串”这个词，我们很容易想到用后缀数组解决此题。

依照套路先求出 SA 数组以及 rank 数组，并在此基础上求出 height 数组（$\text{height}_i=\text{LCP}(\text{sa}_{i},\text{sa}_{i-1})$）。

对于一个长度为 $\text{len}$ 的子串，如果它在字符串中出现了 $x$ 次，那么一定能找到一个 $k$，使得 $\min \{ \text{height}_{k \dots k+x-2} \} \ge \text{len}$。

我们可以枚举子串的长度 $\text{len}$，但是复杂度会爆炸。

考虑使用并查集。具体地，我们从大到小枚举 $\text{len}$，对于 $\text{height}_i=\text{len}$ 的情况，合并 $i$ 和 $i-1$ 两个块。

接下来我们考虑容斥。不难发现，答案是关于 $H(A+B)-H(A)-H(B)$ 的形式，所以可以对于每一组询问，进行 $3$ 次同样的计算即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n,q,m,len;
int x[N],y[N],sa[N],rk[N],c[N],a[N],he[N],f[N][20],lg[20],h[N],fa[N],b[N],d[N];
bool v[N];
char s[N];
ll sz[N];
vector<int> vec[N],ve;
void prework()
{
	lg[0]=1;
	for(int i=1;i<20;i++) lg[i]=lg[i-1]<<1;
}
int get(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
int ask(int l,int r)
{
	if(l>r) return (ll)n-sa[r]+1;
	int k=(int)(log(r-l+1)/log(2));
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
void SA()
{
	m=122;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=2;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y),num=1,x[sa[1]]=1;
		for(int i=2;i<=n;i++)
		{
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
			else x[sa[i]]=++num;
		}
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]>1)
		{
		    if(k) k--;
		    while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		    he[rk[i]]=k;
		}
   }
   for(int i=1;i<=n;i++) f[rk[i]][0]=he[rk[i]];
   int t=(int)(log(n)/log(2))+1;
   for(int j=1;j<=t;j++)
   {
        for(int i=1;i<=n-lg[j]+1;i++) f[i][j]=min(f[i][j-1],f[i+lg[j-1]][j-1]);
   }
}
ll solve()
{
	ll ans=0;
	sort(a+1,a+1+len,[](const int &x,const int &y){return rk[x]<rk[y];});
    for(int i=2;i<=len;i++) h[i]=ask(rk[a[i-1]]+1,rk[a[i]]),vec[h[i]].push_back(i);
    for(int i=2;i<=len;i++) if(!v[h[i]]) ve.push_back(h[i]),v[h[i]]=1;
    for(int i=1;i<=len;i++) fa[i]=i,sz[i]=1;
    sort(ve.begin(),ve.end()),reverse(ve.begin(),ve.end());
    for(int i:ve)
    {
    	for(auto j:vec[i])
    	{
    		int x=get(j),y=get(j-1);
    		if(x==y) continue;
    		ans+=1ll*i*sz[x]*sz[y];
    		sz[x]+=sz[y],fa[y]=x;
		}
	}
	for(int i=2;i<=len;i++) vec[h[i]].clear(),v[h[i]]=0;
    ans<<=1; ve.clear();
	for(int i=1;i<=len;i++) ans+=(ll)(n-a[i]+1);
	return ans;
}
void work()
{
	ll ans=0; int k,l;
	scanf("%d%d",&k,&l);
	for(int i=1;i<=k;i++) scanf("%d",&b[i]),a[i]=b[i];
	for(int i=1;i<=l;i++) scanf("%d",&d[i]);
	len=k,ans-=solve(),len=l;
	for(int i=1;i<=len;i++) a[i]=d[i];
	ans-=solve();
	for(int i=1;i<=k;i++) a[i+l]=b[i];
	len+=k,ans+=solve();
	printf("%lld\n",ans>>1);
}
int main()
{
    scanf("%d%d%s",&n,&q,s+1); prework(); SA();
    while(q--) work();
    return 0;
}
```

---

## 作者：_lbw_ (赞：2)

题意：

给一字符串，$q$ 次询问，每次询问给定 $A,B$ 两个集合，求

$$\sum_{p_a\in A}\sum_{p_b\in B}\textsf{lcp}(p_a,p_b)$$

其中 $\textsf{lcp}(x,y)$ 表示 $x$ 这个后缀和 $y$ 这个后缀的最长公共前缀长度

题解：

首先考虑求 $H(A)=\sum_{p_1\in A}\sum_{p_2\in A}\textsf{lcp}(p_1,p_2)$ （这里是 $p_1,p_2$ 是无序的）

因为有 $\textsf{lcp}$，所以考虑求后缀数组和 $\textsf{height}$ 数组

$\textsf{lcp(x,y)}=\min \textsf{height}_i (i\in [x,y])$

所以将 $A$ 中元素排序后，问题便转化为了求：

$$\sum_{i=1}\sum_{j=i}\min \textsf{height}_k(k\in [i,j])$$

这个问题可以用单调栈求出每个数左边第一个比他大的和右边第一个比他大的（用二分 st 表也可），然后就可以快速求出答案，详见 P4248

最后将 $\sum_{p_a\in A}\sum_{p_b\in B}\textsf{lcp}(p_a,p_b)$ 转化为 $H(A+B)-H(A)-H(B)$ 就可以求出答案

[码](https://www.luogu.com.cn/paste/holhtztg)

---

## 作者：FjswYuzu (赞：2)

考虑到又是一个做 $\operatorname{lcp}$ 的问题。显然需要串反转然后用一个处理后缀的工具去做这个题。这种题见的多了打这句话都暴躁了。这里用的后缀自动机。

一个熟知结论是后缀自动机上两个结点 $\operatorname{parent}$ 树上的 $\operatorname{LCA}$ 表示的最长串就是这两个结点表示的串的 $\operatorname{lcp}$。那就往这个方面做，首先把树建出来。

发现因为查询的点很多，自然想到虚树。

在虚树上求答案的时候，一个比较方便的处理方法是在某一个结点，处理完以其为根结点的子树内的跨子树贡献（即贡献来自的点在两个子树）。这个问题比较显然，直接求出有多少个集合 $A$ 中的后缀出现在这个子树内，然后分子树算贡献就行了。

需要特殊处理的是当前结点。具体做法是看看标记就行了。这里可以看代码。

太好了这个题不是傻逼 SvT 不卡常！！！太好了！！！1

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(LL x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const int Sigma=26;
char s[500005];
int pos[500005],n,dep[1000005],fa[1000005][21],lgs[1000005],dfn[1000005],sjc,val[1000005],sr[1000005],len,len1,len2,siza[1000005],sizb[1000005];
bool tek1[1000005],tek2[1000005];
vector<int> G[1000005],vir[1000005];
LL ans;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
struct SAM{
	int las,cnt,ch[1000005][Sigma],len[1000005],fa[1000005];
	SAM(){las=cnt=1;}
	void extend(int c)
	{
		int p=las,cur=++cnt;
		len[cur]=len[las]+1;
		las=cur;
		while(p && !ch[p][c])	ch[p][c]=cur,p=fa[p];
		if(!p)	fa[cur]=1;
		else
		{
			int q=ch[p][c];
			if(len[p]+1==len[q])	fa[cur]=q;
			else
			{
				int clone=++cnt;
				len[clone]=len[p]+1;
				memcpy(ch[clone],ch[q],sizeof ch[q]);
				fa[clone]=fa[q];
				fa[q]=fa[cur]=clone;
				while(ch[p][c]==q)	ch[p][c]=clone,p=fa[p];
			}
		}
	}
	void build(){for(int i=2;i<=cnt;++i)	G[fa[i]].push_back(i);}
}sam;
void dfs(int now)
{
	dep[now]=dep[sam.fa[now]]+1;
	fa[now][0]=sam.fa[now];
	val[now]=sam.len[now];
	dfn[now]=++sjc;
	for(int i=1;i<=20;++i)	fa[now][i]=fa[fa[now][i-1]][i-1];
	for(unsigned int i=0;i<G[now].size();++i)	dfs(G[now][i]);
}
int LCA(int u,int v)
{
	if(dep[u]>dep[v])	u^=v^=u^=v;
	while(dep[u]<dep[v])	v=fa[v][lgs[dep[v]-dep[u]]];
	if(u==v)	return u;
	for(int i=20;~i;--i)	if(fa[u][i]!=fa[v][i])	u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
void dfs2(int now)
{
	for(unsigned int i=0;i<vir[now].size();++i)
	{
		int to=vir[now][i];
		dfs2(to);
		siza[now]+=siza[to],sizb[now]+=sizb[to];
	}
	for(unsigned int i=0;i<vir[now].size();++i)
	{
		int to=vir[now][i];
		ans+=LL(siza[now]-siza[to])*(LL)sizb[to]*(LL)val[now];
	}
	if(tek1[now] && !tek2[now])
	{
		++siza[now];
		ans+=(LL)val[now]*(LL)sizb[now];
	}
	else if(!tek1[now] && tek2[now])
	{
		++sizb[now];
		ans+=(LL)val[now]*(LL)siza[now];
	}
	else if(tek1[now]&tek2[now])
	{
		ans+=(LL)val[now]*LL(siza[now]+sizb[now]+1);
		++siza[now],++sizb[now];
	}
}
int main(){
	int T;
	n=read(),T=read();
	scanf("%s",s+1);
	reverse(s+1,s+1+n);
	for(int i=1;i<=n;++i)	sam.extend(s[i]-'a'),pos[i]=sam.las;
	sam.build();
	for(int i=2;i<=1000000;++i)	lgs[i]=lgs[i>>1]+1;
	dfs(1);
	while(T-->0)
	{
		len1=read(),len2=read();
		len=len1+len2;
		for(int i=1;i<=len1;++i)	tek1[sr[i]=pos[n-read()+1]]=true;
		for(int i=len1+1;i<=len;++i)	tek2[sr[i]=pos[n-read()+1]]=true;
		sort(sr+1,sr+1+len,cmp);
		len=unique(sr+1,sr+1+len)-sr-1;
		for(int i=1;i<len;++i)	sr[len+i]=LCA(sr[i],sr[i+1]);
		len=2*len-1;
		sort(sr+1,sr+1+len,cmp);
		len=unique(sr+1,sr+1+len)-sr-1;
		for(int i=2;i<=len;++i)	vir[LCA(sr[i-1],sr[i])].push_back(sr[i]);
		ans=0;
		dfs2(sr[1]);
		write(ans);
		puts("");
		for(int i=1;i<=len;++i)	vir[sr[i]].clear(),siza[sr[i]]=sizb[sr[i]]=0,tek1[sr[i]]=tek2[sr[i]]=false;
	}
	return 0;
}
```

---

## 作者：Caro23333 (赞：2)

一种略微不同的~~丑陋的~~做法。

首先把每次查询转化为在后缀数组中的$\textrm{height}$数组上，给定两个端点集合$A,B$，求所有两个端点分别来自两个集合的左开右闭区间的最小值之和。

**我们考虑用分治来解决这个问题。** 一次查询中，我们首先把所有出现过的端点（来自$A$或$B$）组成的序列从小到大排序，并预处理每个端点在$A$还是在$B$出现，或是都出现过。设此序列为$Q$，大小为$c$。约定第$i$个端点为$Q_i$。

接下来令$s(l,r)$为考虑$Q$中编号在$[l,r]$上的所有的端点，组成的所有左开右闭区间最小值之和，$s(1,c)$即为所求答案。

设$mid=\lfloor \frac{l+r}{2}\rfloor$，假设我们已经计算完了$s(l,mid)$与$s(mid+1,r)$，那么现在还需要知道两个端点的编号分别在$[l,mid]$与$[mid+1,r]$中的区间对答案造成的贡献。

对于$s(l,r)$，定义$p_x(x\in [l,r])$：

- 若$x\in [l,mid]$，$p_x=\min\limits_{i=Q_x+1}^{Q_{mid}} \textrm{height}_i$

- 若$x\in [mid+1,r]$，$p_x=\min\limits_{i=Q_{mid}+1}^{Q_x} \textrm{height}_i$

特别地，定义$\min\limits_{i=Q_{mid}+1}^{Q_{mid}} \textrm{height}_i = +\infty$。

如果我们固定了左端点编号$x\in [l,mid]$，那么在右端点$y$任意取值的过程中，有两种情况：

- $p_y<p_x$，则该区间的贡献为$p_y$;

- $p_x\le p_y$，则该区间的贡献为$p_x$。

考虑到对于$y>mid$，$p_y$关于$y$是递增的，这就说明两种贡献应该有一个分界$t$隔开：当$y\le t$时贡献为$p_x$，当$y>t$时贡献为$p_y$。

如果$Q_x$在$A$中出现过，那么值为$p_x$的贡献我们可以通过统计$[mid+1,t]$上在$B$中出现过的端点个数来计算，而值为$p_y$的贡献可以通过统计$[t+1,r]$上在$B$中出现过的端点之和来计算：这些都是可以$O(r-l+1)$处理的。反之亦然。

假设我们从$mid$到$l$来枚举$x$，那么$p_x$是逐渐减小的，这意味着我们可以用$\textrm{two-pointer}$技术来维护分界线$t$的取值，复杂度是$O(r-l+1)$的。

设$T(n)$为对于长度为$n$的区间$[l,r]$计算$s(l,r)$的复杂度，我们有：

$$T\left(n\right)=2T\left(\frac{n}{2}\right)+O(n)$$

分析易得计算$s(1,c)$的复杂度为$O(c\log c)$。由于对于每次查询，$c\le |A|+|B|$，则$\sum c\le \sum |A|+|B|\le 4\times 10^5$，从而总复杂度是正确的。

**虽然分治统计答案的做法在这道题中又难写又慢，但是它启发我们不要小觑分治这一初学时就接触的思想，它有可能在许多地方大放异彩。**

实现细节看代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#define inf (1<<30)
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
struct Node
{
    int fi,se,idx;
}pa[MAXN],pb[MAXN];
int n,m,a,b,x[MAXN],y[MAXN];
char str[MAXN];
int pre[MAXN],sa[MAXN],rk[MAXN],h[MAXN],height[MAXN];
inline void buildSA()
{
	memset(pre,0,sizeof(pre));
    for(int i = 1; i<=n; i++)
	    pre[str[i]]++;
	for(int i = 1; i<=255; i++)
	    pre[i] += pre[i-1];
	for(int i = 1; i<=n; i++)
	    sa[pre[str[i]]--] = i;
	int tot = 0;
	for(int i = 1; i<=n; i++)
	{
        if(i>1&&str[sa[i]]==str[sa[i-1]])
            rk[sa[i]] = tot;
        else
            rk[sa[i]] = ++tot;
	}
	for(int j = 1; j<=n; j <<= 1)
	{
        memset(pre,0,sizeof(pre));
        for(int i = 1; i<=n; i++)
            pa[i].fi = rk[i], pa[i].se = i+j>n?0:rk[i+j], pa[i].idx = i;
		for(int i = 1; i<=n; i++)
		    pre[pa[i].se]++;
		for(int i = 1; i<=n; i++)
		    pre[i] += pre[i-1];
		tot = 0;
		for(int i = 1; i<=n; i++)
		    pb[pre[pa[i].se]--] = pa[i];
		memset(pre,0,sizeof(pre));
		for(int i = 1; i<=n; i++)
		    pre[pb[i].fi]++;
		for(int i = 1; i<=n; i++)
		    pre[i] += pre[i-1];
		for(int i = n; i>=1; i--)
		    pa[pre[pb[i].fi]--] = pb[i];
		tot = 0;
		for(int i = 1; i<=n; i++)
		{
            if(i>1&&pa[i].fi==pa[i-1].fi&&pa[i].se==pa[i-1].se)
                rk[pa[i].idx] = tot;
            else
                rk[pa[i].idx] = ++tot;
		}
	}
	for(int i = 1; i<=n; i++)
	    sa[rk[i]] = i;
}
inline void getHeight()
{
	int tmp,pos;
	for(int i = 1; i<=n; i++)
	{
        if(rk[i]==1)
            continue;
        tmp = max(h[i-1]-1,0);
        pos = sa[rk[i]-1];
        while(tmp+pos<=n&&tmp+i<=n&&str[tmp+pos]==str[tmp+i])
            tmp++;
        h[i] = tmp;
	}
	for(int i = 1; i<=n; i++)
	    height[rk[i]] = h[i];
}
int st[MAXN][19],bin[MAXN];
inline void buildST()
{
    for(int i = 2; i<=n; i++)
	    bin[i] = bin[i>>1]+1;
	for(int i = 1; i<=n; i++)
	    st[i][0] = height[i];
	for(int j = 1; (1<<j)<=n; j++)
	    for(int i = 1; i+(1<<j)-1<=n; i++)
            st[i][j] = min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
inline int query(int l, int r)
{
	if(r<l)
	    return inf;
	int k = bin[r-l+1];
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
map<int,int> mq;
map<int,int>::iterator it;
pii q[MAXN];
int now[MAXN];
ll tpre[MAXN][2],cpre[MAXN][2];
int cnt = 0;
inline ll solve(int l, int r)
{
	if(l==r)
        return q[l].se==3?n-sa[q[l].fi]+1:0;
    int mid = (l+r)>>1;
    ll res = solve(l,mid)+solve(mid+1,r);
    for(int i = l; i<=mid; i++)
        now[i] = query(q[i].fi+1,q[mid].fi);
	for(int i = mid+1; i<=r; i++)
        now[i] = query(q[mid].fi+1,q[i].fi);
    tpre[mid][0] = tpre[mid][1] = 0;
    cpre[mid][0] = cpre[mid][1] = 0;
    for(int i = mid+1; i<=r; i++)
    {
        tpre[i][0] = tpre[i-1][0]+(q[i].se!=2?now[i]:0);
        tpre[i][1] = tpre[i-1][1]+(q[i].se!=1?now[i]:0);
        cpre[i][0] = cpre[i-1][0]+(q[i].se!=2);
        cpre[i][1] = cpre[i-1][1]+(q[i].se!=1);
	}
	int pos1 = mid+1, pos2 = mid+1;
	for(int i = mid; i>=l; i--)
	{
        if(q[i].se!=2)
        {
            while(pos1<=r&&!(q[pos1].se!=1&&now[pos1]<now[i]))
                pos1++;
            res += tpre[r][1]-tpre[pos1-1][1]+cpre[pos1-1][1]*now[i];
		}
		if(q[i].se!=1)
		{
			while(pos2<r&&!(q[pos2].se!=2&&now[pos2]<now[i]))
			    pos2++;
			res += tpre[r][0]-tpre[pos2-1][0]+cpre[pos2-1][0]*now[i];
		}
	}
	return res;
}

int main()
{
	n = readint(), m = readint();
	scanf("%s",str+1);
	buildSA(), getHeight(), buildST();
	while(m--)
	{
        a = readint(), b = readint();
		mq.clear();
        for(int i = 1; i<=a; i++)
            mq[rk[readint()]] += 1; 
		for(int i = 1; i<=b; i++)
        	mq[rk[readint()]] += 2;
        cnt = 0;
        for(it = mq.begin(); it!=mq.end(); it++)
            q[++cnt] = mp(it->fi,it->se);
        sort(q+1,q+cnt+1);
		printf("%lld\n",solve(1,cnt));
	}
	return 0;
}

```


---

## 作者：Arghariza (赞：1)

一道 *2600 调了一年，代码细节是有点粪了，但自己菜也是挺菜的。/oh/oh

考虑容斥，令 $f(A)=\sum\limits_{i,j\in A}\operatorname{lcp}(i,j)$，那么答案就是 $f(A\cup B)-f(A)-f(B)$（这里的并表示**可重集合并**）。

令 $A=\{a_1,a_2,\cdots ,a_m\}$，并且 $a_1\le a_2\le\cdots\le a_m$，那么 $f(A)=\sum\limits_{1\le i\le j\le m}\operatorname{lcp}(i,j)$。

由于我们先前进行了容斥，所以可以忽略 $i=j$ 的贡献，只需要考虑 $\sum\limits_{1\le i<j\le m}\operatorname{lcp}(i,j)$ 即可。但是注意到 $a_i$ **仍然有可能等于** $a_j$。

建出后缀数组。为了方便，令 $a_i\gets \operatorname{rk}_{a_i}$，那么对于 $a_i< a_j$，$\operatorname{lcp}(\operatorname{sa}_i,\operatorname{sa}_j)=\min\limits_{k\in [{a_i}+1,a_j]}\operatorname{height}_k$，变成了一个子区间最小值之和的问题，可以分治解决；对于 $a_i=a_j$，单独计算每种 $a_i$ 的贡献，只需要求出 $a_j=k$ 的 $j$ 的个数 $c_{k}$，那么 $k$ 的贡献即为 $\dbinom{c_k}{2}(n-\operatorname{sa}_{k}+1)$。

然后就做完了，复杂度 $O(n\log n)$，注意分治时不能统计到 $a_i=a_j$ 的贡献。

```cpp
// Problem: G. Yet Another LCP Problem
// Contest: Codeforces - Educational Codeforces Round 53 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1073/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int N = 4e5 + 400;
const int M = 20;

ll sum[N];
int n, m, q, len, a[N], b[N], pr[N], sf[N], f[N][M];
int id[N], ct[N], rk[N], sa[N], ht[N];
char s[N];

void rst() {
	memset(ct, 0, sizeof(int) * (m + 5));
	for (int i = 1; i <= n; i++) ct[rk[i]]++;
	for (int i = 1; i <= m; i++) ct[i] += ct[i - 1];
	for (int i = n; i; i--) sa[ct[rk[id[i]]]--] = id[i];
}

void SA() {
	m = 30;
	for (int i = 1; i <= n; i++) rk[i] = s[i] - 'a' + 1, id[i] = i;
	rst();
	for (int w = 1, p = 0; w <= n && p != n; w <<= 1, m = p) {
		p = 0;
		for (int i = n - w + 1; i <= n; i++) id[++p] = i;
		for (int i = 1; i <= n; i++) if (sa[i] > w) id[++p] = sa[i] - w;
		rst(), swap(rk, id), p = rk[sa[1]] = 1;
		for (int i = 2; i <= n; i++) rk[sa[i]] = (id[sa[i]] == id[sa[i - 1]] && id[sa[i] + w] == id[sa[i - 1] + w]) ? p : ++p;
	}
	for (int i = 1, j = 0; i <= n; i++) {
		if (j) j--;
		while (s[i + j] == s[sa[rk[i] - 1] + j]) j++;
		ht[rk[i]] = j;
	}
}

int qry(int l, int r) {
	if (l > r) return 0; 
	int len = __lg(r - l + 1);
	return min(f[l][len], f[r - (1 << len) + 1][len]);
}

ll conq(int l, int r) {
	if (l == r) return 0;
	int mid = (l + r) >> 1;
	ll res = conq(l, mid) + conq(mid + 1, r); sum[mid] = 0;
	for (int i = mid; i >= l; i--) sf[i] = qry(a[i] + 1, a[mid + 1]);
	for (int i = mid + 1; i <= r; i++) pr[i] = qry(a[mid] + 1, a[i]), sum[i] = sum[i - 1] + pr[i];
	int p = mid + 1, q = mid;
	while (p <= r && a[p] == a[mid]) p++;
	while (q >= l && a[q] == a[mid + 1]) q--;
	if (a[mid] == a[mid + 1]) res += 1ll * (sum[r] - sum[p - 1]) * (mid - q);
	for (int i = mid + 1; i <= r; i++) pr[i] = qry(a[q] + 1, a[i]), sum[i] = sum[i - 1] + pr[i];
	for (int i = q, j = mid + 1; i >= l; i--) {
		while (j <= r && sf[i] <= pr[j]) j++;
		res += 1ll * (j - mid - 1) * sf[i] + sum[r] - sum[j - 1];
	}
	return res;
}

ll calc(int l, int r) {
	for (int i = l; i <= r; i++) a[i] = b[i];
	sort(a + l, a + r + 1);
	ll res = 0;
	for (int i = l; i <= r; i++) {
		int j = i;
		while (j < r && a[j + 1] == a[i]) j++;
		res += 1ll * (j - i + 1) * (j - i) / 2 * (n - a[i] + 1), i = j;
	}
	for (int i = l; i <= r; i++) a[i] = rk[a[i]];
	sort(a + l, a + r + 1);
	return res + conq(l, r);
}

void solve() {
	cin >> n >> q >> (s + 1), SA();
	for (int i = 1; i <= n; i++) f[i][0] = ht[i];
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
	while (q--) {
		int l1, l2; cin >> l1 >> l2;
		for (int i = 1; i <= l1; i++) cin >> b[i];
		for (int i = 1; i <= l2; i++) cin >> b[l1 + i];
		ll s1 = calc(1, l1 + l2), s2 = calc(1, l1), s3 = calc(l1 + 1, l1 + l2);
		// cout << s1 << ' ' << s2 << ' ' << s3 << '\n';
		cout << s1 - s2 - s3 << '\n';
	}
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：_LiWenX_ (赞：1)

~~其实本来是想做虚树的，看到虚树tag就进来了~~。

首先我们考虑快速计算 $\text{lcp}(x,y)$，如果学过后缀数组，那么就可以快速想到利用后缀数组的 hight 数组预处理出 ST 表，然后 $O(1)$ 查询，但这样复杂度是 $O(AB)$ 的，于是我们可以考虑一下我们的式子：

$$\sum\limits_{i=1}^A\sum\limits_{j=1}^B \min_{k=rk_{a_i}+1}^{rk_{b_i}} h_k$$

其中的 $rk_i$ 是后缀 $i$ 的排名，这样稍微看起来有点麻烦，我们直接把 $a_i$ 改写为 $rk_{a_i}$，$b$ 数组同理。

那式子就是：

$$\sum\limits_{i=1}^A\sum\limits_{j=1}^B \min_{a_i+1}^{b_i} h_k$$

那么就不难想到去改变枚举顺序，我们可以枚举 $h$ 的最小值，再分治下去计算，这个过程类似序列启发式分裂。

具体来说，假设我们的分治区间为 $l\sim r$ ，其中 $h$ 的最小值为 $val$，它的位置为 $pos$，那么这次分治对答案的贡献就是：

$$val\times (\sum\limits_{i=1}^A[l\le a_i<val]\times \sum\limits_{i=1}^B[val \le b_i \le r]+\sum\limits_{i=1}^B[l\le b_i<val]\times \sum\limits_{i=1}^A[val \le a_i \le r])$$

发现对于这个式子，我们可以轻松用树状数组维护，然后再递归分治下去，那么你就做完了。

注意要去特判一下 $a_i=b_i$ 时，答案贡献是 $n-sa_{a_i}+1$，这个在递归的边界处理就好了。

然后是一个卡常小技巧（其实根本用不上但我还是写了），就是每次分治的时候为了防止当前的 $pos$ 对答案没有贡献而白白空递归一次，浪费一次 ST 表的查询和两次树状数组的查询，我们可以递归的时候把这个区间中的 $a,b$ 数组对应下标拿出来，这在排序后一定是一个连续段，所以用四个变量即可维护，递归的话就每次二分下一次对应的区间。

考虑复杂度，加上优化后，每次分治必然使得某段或多段至少减少 $1$ 个数，所以分治最多遍历 $O(A+B)$ 个区间，每次都是 $O(\log n)$ 计算答案的，时间复杂度：$O((n+\sum A+\sum B)\log n)$。

擅长写分治的话代码还比较好写，这个做法常数也不错：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[300001];
int x[300001],y[300001],t[300001];
int h[300001],m=127,sa[300001];
pair<int,int> f[200001][20];
void rsort(){
	for(int i=1;i<=m;i++) t[i]=0;
	for(int i=1;i<=n;i++) t[x[i]]++;
	for(int i=1;i<=m;i++) t[i]+=t[i-1];
	for(int i=n;i;i--) sa[t[x[y[i]]]--]=y[i]; 
}
void Sort(){
	for(int i=1;i<=n;i++){
		x[i]=s[i];
		y[i]=i;
	}
	rsort();
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(int i=n-k+1;i<=n;i++) y[++p]=i;
		for(int i=1;i<=n;i++){
			if(sa[i]>k) y[++p]=sa[i]-k;
		}
		rsort();
		swap(x,y);
		x[sa[1]]=p=1;
		for(int i=2;i<=n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		}
		m=p;
	}
	int p=0;
	for(int i=1;i<=n;i++){
		if(p) p--;
		while(s[i+p]==s[sa[x[i]-1]+p]) p++;
		h[x[i]]=p;
	}
	for(int i=1;i<=n;i++){
		f[i][0]=make_pair(h[i],i);
	}
	for(int j=1;j<20;j++){
		for(int i=1;i<=n;i++){
			if(i+(1<<(j-1))>n) break;
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
pair<int,int> lcp(int x,int y){
	if(x==y) return make_pair(n-sa[x]+1,x);
	if(x>y) swap(x,y);
	x++;
	int k=log2(y-x+1);
	return min(f[x][k],f[y-(1<<k)+1][k]);
}
int Q;
int a[300001],b[300001];
struct BIT{
	int c[300001];
	#define lb(x) (x&-x)
	void add(int x,int k){
		while(x<=n){
			c[x]+=k;
			x+=lb(x);
		}
	}
	int ask(int x){
		if(x<=0) return 0;
		int ret=0;
		while(x){
			ret+=c[x];
			x-=lb(x);
		}
		return ret;
	}
	int ask(int l,int r){
		if(l>r) return 0;
		return ask(r)-ask(l-1);
	}
}Ta,Tb;
long long solve(int l,int r,int la,int ra,int lb,int rb){
	if(la>ra||lb>rb) return 0;
	l=max(l,min(a[la],b[lb]));
	r=min(r,max(a[ra],b[rb]));
	if(l==r){
		if(la<=ra&&lb<=rb) return n-sa[l]+1;
		return 0;
	}
	pair<int,int> LCP=lcp(l,r);
	int val=LCP.first,mid=LCP.second;
	int le,re,pos1=ra+1,pos2=rb+1;
	le=la,re=ra;
	while(le<=re){
		int Mid=(le+re)>>1;
		if(a[Mid]>=mid){
			pos1=Mid;
			re=Mid-1;
		}
		else le=Mid+1;
	}
	le=lb,re=rb;
	while(le<=re){
		int Mid=(le+re)>>1;
		if(b[Mid]>=mid){
			pos2=Mid;
			re=Mid-1;
		}
		else le=Mid+1;
	}
	long long ret=0;
	long long Sla=Ta.ask(l,mid-1),Sra=Ta.ask(mid,r);
	long long Slb=Tb.ask(l,mid-1),Srb=Tb.ask(mid,r);
	ret+=(Sla*Srb+Sra*Slb)*val;
	ret+=solve(l,mid,la,pos1-1,lb,pos2-1)+solve(mid,r,pos1,ra,pos2,rb);
	return ret;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>Q>>(s+1);
	Sort();
	while(Q--){
		int A,B;
		cin>>A>>B;
		for(int i=1;i<=A;i++){
			cin>>a[i];
			a[i]=x[a[i]];
			Ta.add(a[i],1);
		}
		for(int i=1;i<=B;i++){
			cin>>b[i];
			b[i]=x[b[i]];
			Tb.add(b[i],1);
		}
		sort(a+1,a+1+A);
		sort(b+1,b+1+B);
		cout<<solve(1,n,1,A,1,B)<<'\n';
		for(int i=1;i<=A;i++){
			Ta.add(a[i],-1);
		}
		for(int i=1;i<=B;i++){
			Tb.add(b[i],-1);
		}
	}
}
```

---

## 作者：__stick (赞：1)



## 题意

给出一个字符串，有若干次询问，每次给出两个集合 $A,B$ ，求：
$$
\sum_{i\in A}\sum_{j\in B}\operatorname{LCP}(i,j)
$$

## 思路

因为不会 SAM，所以使用后缀数组。

首先求出后缀数组。

然后思考如果 $A=B=\{1,\cdots n\}$ 。

此时就有两种经典的处理方式： 单调栈和并查集。

如果 $A,B$ 是一个子集，则可以直接将给出的后缀按照 $rk_i$ 然后放在一起排序。

这样实际上又变回了全集的处理方式。

因为我们相当于还是将给出的后缀排序了，然后此时需要快速求出 $height$ 数组，则可以使用 ST 表+求原来字符串中的区间最小值来实现。

然后这里明显使用并查集更加方便。

方法还是按 $height$ 从大到小合并后缀，对每个连通块维护两个值，分别表示当前连通块中属于 $A$  集合和 $B$ 集合的有多少个点。

然后再合并的时候，两个连通块内部的贡献已经计算完了，只需要计算跨连通块的贡献即可。

也就是跨连通块且所属种类不同的后缀对的个数乘上当前合并的 lcp 的长度，直接计算即可。

然后每次的复杂度就是 $O\left((|A|+|B|)\log(|A|+|B|)\right) $。

所以总复杂度仍然是一个 $\log $ 而且常数比较小。

## code

后缀数组板子就不放了。

```c++
const int K=18;
int F[K+1][MAXN];
int n;
inline int ask(int x,int y)
{
	if(x==y)return n-sa[x]+1;//小心，这里的 x，y 已经变成 rk[x] 了
	int k=31-__builtin_clz(y-x);
	return min(F[k][x+1],F[k][y-(1<<k)+1]);
}
inline void solve()
{
	int n1,n2;
	cin>>n1>>n2;
	int x;
	vector<pii>ve;
	for(int i=1;i<=n1;i++)cin>>x,ve.eb(rk[x],1);
	for(int i=1;i<=n2;i++)cin>>x,ve.eb(rk[x],2);
	sort(all(ve));
	vector<pii>h;
	for(int i=1;i<sz(ve);i++)
	{
		h.eb(ask(ve[i-1].X,ve[i].X),i);
	}
	sort(all(h),greater<>());
	vi F(sz(ve));iota(all(F),0);
	function<int(int)>getf=[&](int x){return F[x]==x?x:F[x]=getf(F[x]);};
	vector<ll>s1(sz(ve)),s2(sz(ve));
	for(int i=0;i<sz(ve);i++)
	{
		if(ve[i].Y==1)s1[i]++;
		else s2[i]++;
	}
	ll ans=0;
	for(int i=0,j;i<sz(h);i=j)
	{
		j=i;
		auto merge=[&](int x,int y)
		{
			x=getf(x),y=getf(y);
			if(x==y)return;
			ans+=s1[x]*s2[y]*h[i].X;
			ans+=s2[x]*s1[y]*h[i].X;
			F[x]=y;
			s1[y]+=s1[x],s2[y]+=s2[x];
		};
		while(j<sz(h)&&h[j].X==h[i].X)//这里好像没必要同时加入长度相同的
		{
			merge(h[j].Y-1,h[j].Y);
			j++;
		}
	}
	cout<<ans<<'\n';
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int m;
	cin>>n>>m;
	cin>>(s+1);
	get_sa(n,'z'),get_hi(n);
	//for(int i=1;i<=n;i++)cerr<<hi[i]<<' ';cerr<<'\n';
	for(int i=1;i<=n;i++)F[0][i]=hi[i];
	for(int i=1;i<=K;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			F[i][j]=min(F[i-1][j],F[i-1][j+(1<<(i-1))]);
	while(m--)
	{
		solve();
	}
	return 0;
} 
```



---

## 作者：黑影洞人 (赞：1)

首先关于快速求 LCP 的问题，一般可以转化到反串的后缀链接树上（这样前缀就会变成后缀，方便统计）。

然后后缀链接树有一个性质，就是该节点到父节点的有一些子串（状态）会被压缩，我们这时候要统计树上问题就要考虑到。

我们有一个结论:

$$lcp(i,j)=dis(lca(i,j))$$

每个节点到其父节点的权值，要设置为他和他的父节点所对应的的串的长度差。

我很菜，不会证明，但是看图感觉是对的。

显然，观察下图可以得到，当然对于正串说求的是最长公共后缀。

图片来自OI-wiki：

![](https://oi-wiki.org/string/images/SAM/SA_suffix_links.svg)

很自然的就码出来后缀自动机。

然后就是树上的统计了。

我们要求一对节点的最近公共祖先的深度，对于小数据，一般会暴力 LCA 。

但是碰到大数据那就未必了。

我们冷静下来分析，首先可以肯定的是，每个节点到其父节点的权值，要设置为他和他的父节点所对应的的串的长度差。

如果不能理解观察上面 OI-wiki 的那张图，也许就可以理解。

于是这时候问题就变成了，给你两组节点，点带权，求 $\sum dis(root,lca(u,v))$

惊喜的是，这个柿子可以用 LCT 求解。

具体如何实现呢？

我们先将第一组作为起点的点向根节点的路径上加一（中间压缩的节点就乘一下），然后从第二组出发，依次累加每个终点到根节点的答案，这样，两个点一来一去，正好算清楚了 $dis(root,lca(u,v))$。

有人就会问了，这样会算上 $dis(v,kca(u,v))$ 呀。

显然的是 $dis(v,kca(u,v))$ 的路径产生的贡献属于与另一个第一组节点产生的贡献，不影响结果。

因此我们只需要使用 LCT 维护节点值，链和，节点原来的权值，和链原来的权值即可。

于是我们可以愉快的使用 LCT 维护了。

代码太丑了，就不展示了。


---

## 作者：Leasier (赞：1)

前置芝士：[后缀自动机（SAM）](https://oi-wiki.org/string/sam/)、[虚树](https://oi-wiki.org/graph/virtual-tree/)

首先对反串建后缀自动机，容易发现此时 fail 树上两个代表后缀的节点的 LCA 为代表其 LCP 的节点。

于是原式可以转化为 $\displaystyle\sum_{i \in A} \sum_{j \in B} len_{lca(pos_i, pos_j)}$，其中 $pos_i$ 表示 fail 树上代表 $i \sim n$ 的后缀的节点，$len_u$ 表示 fail 树上 $u$ 点对应的等价类中最长字符串的长度。

于是可以对满足 $\forall i \in A \operatorname{or} i \in B$ 的 $pos_i$ 建虚树求解。时间复杂度为 $O(n \log n + \sum (x_i + y_i) \log (x_i + y_i) + \log n \sum (x_i + y_i))$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <stack>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct Node_tag {
	int pos;
	int dfn;
	Node_tag(){}
	Node_tag(int pos_, int dfn_){
		pos = pos_;
		dfn = dfn_;
	}
} Node;

int lst = 1, id = 1, cnt1 = 0, cnt2 = 0;
int len[400007], nxt[400007][27], fa[400007][27], pos[400007], head1[400007], depth[400007], in[400007], out[400007], a[200007], b[200007], head2[400007], size1[400007], size2[400007];
char s[200007];
bool vis[400007], mark1[400007], mark2[400007];
Edge edge1[400007], edge2[400007];
Node c[400007];
stack<int> stk;

bool operator <(const Node a, const Node b){
	return a.dfn < b.dfn;
}

bool operator ==(const Node a, const Node b){
	return a.pos == b.pos;
}

inline int insert(int ch){
	int u = lst, v = lst = ++id;
	len[v] = len[u] + 1;
	while (u != 0 && nxt[u][ch] == 0){
		nxt[u][ch] = v;
		u = fa[u][0];
	}
	if (u == 0){
		fa[v][0] = 1;
		return v;
	}
	int w = nxt[u][ch];
	if (len[w] == len[u] + 1){
		fa[v][0] = w;
		return v;
	}
	int x = ++id;
	len[x] = len[u] + 1;
	fa[x][0] = fa[w][0];
	fa[v][0] = fa[w][0] = x;
	for (register int i = 1; i <= 26; i++){
		nxt[x][i] = nxt[w][i];
	}
	while (nxt[u][ch] == w){
		nxt[u][ch] = x;
		u = fa[u][0];
	}
	return v;
}

inline void add_edge1(int start, int end){
	cnt1++;
	edge1[cnt1].nxt = head1[start];
	head1[start] = cnt1;
	edge1[cnt1].end = end;
}

void dfs1(int u, int &id){
	int t;
	depth[u] = depth[fa[u][0]] + 1;
	t = log2(depth[u]);
	in[u] = ++id;
	for (register int i = 1; i <= t; i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (register int i = head1[u]; i != 0; i = edge1[i].nxt){
		int x = edge1[i].end;
		if (x != fa[u][0]) dfs1(x, id);
	}
	out[u] = id;
}

inline int lca(int u, int v){
	if (depth[u] < depth[v]) swap(u, v);
	while (depth[u] > depth[v]) u = fa[u][(int)log2(depth[u] - depth[v])];
	if (u == v) return u;
	for (register int i = log2(depth[u]); i >= 0; i--){
		if (fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

inline bool check(int u, int v){
	return in[u] <= in[v] && in[v] <= out[u];
}

inline void add_edge2(int start, int end){
	cnt2++;
	edge2[cnt2].nxt = head2[start];
	head2[start] = cnt2;
	edge2[cnt2].end = end;
}

ll dfs2(int u){
	ll ans;
	if (mark1[u]){
		size1[u] = 1;
	} else {
		size1[u] = 0;
	}
	if (mark2[u]){
		size2[u] = 1;
	} else {
		size2[u] = 0;
	}
	if (mark1[u] && mark2[u]){
		ans = len[u];
	} else {
		ans = 0;
	}
	for (register int i = head2[u]; i != 0; i = edge2[i].nxt){
		int x = edge2[i].end;
		ans += dfs2(x);
		ans += len[u] * ((ll)size1[u] * size2[x] + (ll)size1[x] * size2[u]);
		size1[u] += size1[x];
		size2[u] += size2[x];
	}
	return ans;
}

int main(){
	int n, q, dfn_id = 0;
	scanf("%d %d", &n, &q);
	scanf("%s", &s[1]);
	for (register int i = n; i >= 1; i--){
		pos[i] = insert(s[i] - 'a' + 1);
	}
	for (register int i = 1; i <= id; i++){
		if (fa[i][0] != 0) add_edge1(fa[i][0], i);
	}
	dfs1(1, dfn_id);
	for (register int i = 1; i <= q; i++){
		int x, y, z, cnt;
		scanf("%d %d", &x, &y);
		z = x + y;
		for (register int j = 1; j <= x; j++){
			scanf("%d", &a[j]);
			a[j] = pos[a[j]];
			c[j].pos = a[j];
			c[j].dfn = in[a[j]];
			vis[a[j]] = mark1[a[j]] = true;
		}
		for (register int j = 1; j <= y; j++){
			int j_ = j + x;
			scanf("%d", &b[j]);
			b[j] = pos[b[j]];
			c[j_].pos = b[j];
			c[j_].dfn = in[b[j]];
			vis[b[j]] = mark2[b[j]] = true;
		}
		sort(c + 1, c + z + 1);
		z = unique(c + 1, c + z + 1) - c - 1;
		cnt = z;
		for (register int j = 1; j < z; j++){
			int cur_lca = lca(c[j].pos, c[j + 1].pos);
			if (!vis[cur_lca]){
				vis[cur_lca] = true;
				c[++cnt] = Node(cur_lca, in[cur_lca]);
			}
		}
		if (!vis[1]){
			vis[1] = true;
			c[++cnt] = Node(1, 1);
		}
		sort(c + 1, c + cnt + 1);
		while (!stk.empty()) stk.pop();
		for (register int j = 1; j <= cnt; j++){
			while (!stk.empty() && !check(stk.top(), c[j].pos)) stk.pop();
			if (!stk.empty()) add_edge2(stk.top(), c[j].pos);
			stk.push(c[j].pos);
		}
		cout << dfs2(1) << endl;
		cnt2 = 0;
		for (register int j = 1; j <= cnt; j++){
			head2[c[j].pos] = 0;
			vis[c[j].pos] = mark1[c[j].pos] = mark2[c[j].pos] = false;
		}
	}
	return 0;
}
```

---

## 作者：绝顶我为峰 (赞：1)

对于后缀 lcp 这种问题，先无脑对反串建个 SAM，然后 lcp 就变成后缀树上 lca 的 len 了。

考虑如果只有一次询问怎么做：对两个集合内的后缀所在结点打不同的标记，直接 dfs 一遍后缀树，维护子树内两种标记的数量，直接相乘再乘上 $len_k-len_{link_k}$ 即可。（这里不直接乘上 lcp 的长度 $len_k$ 是因为这些贡献会在当前点到根的路径上每个点都被算一次，这样就不会算重。）

但是现在有多次询问，不能每次都 dfs，但是所有询问的集合总大小是有限制的。

俗话说：“见 $\sum$，想虚树。”

于是直接每次从后缀树上拉一颗虚树出来跑 dfs，就做完了。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
struct edge
{
    int nxt,to;
}e[200001<<1];
int n,m,tot,h[200001<<1],cnt,lst,link[200001<<1],ch[200001<<1][26],len[200001<<1],s[200001<<1][2],fa[200001<<1][21],dep[200001<<1],dfn[200001<<1],id,num[200001],top,t[200001],q[200001<<1];
long long ans;
string str;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
inline void add(int x,int y)
{
    e[++tot].nxt=h[x];
    h[x]=tot;
    e[tot].to=y;
}
inline void build(int c)
{
    int cur=++cnt,p=lst;
    len[cur]=len[lst]+1;
    lst=cur;
    for(;~p;p=link[p])
        if(!ch[p][c])
            ch[p][c]=cur;
        else
            break;
    if(p==-1)
        return;
    int q=ch[p][c];
    if(len[p]+1==len[q])
    {
        link[cur]=q;
        return;
    }
    int clone=++cnt;
    link[clone]=link[q];
    len[clone]=len[p]+1;
    for(int i=0;i<26;++i)
        ch[clone][i]=ch[q][i];
    link[cur]=link[q]=clone;
    for(;~p;p=link[p])
        if(ch[p][c]==q)
            ch[p][c]=clone;
        else
            break;
}
inline void dfs1(int k,int f,int deep)
{
    dep[k]=deep;
    fa[k][0]=f;
    dfn[k]=++id;
    for(int i=1;i<=20;++i)
        fa[k][i]=fa[fa[k][i-1]][i-1];
    for(int i=h[k];i;i=e[i].nxt)
        dfs1(e[i].to,k,deep+1);
}
inline int LCA(int x,int y)
{
    if(dep[x]<dep[y])
        x^=y^=x^=y;
    for(int d=dep[x]-dep[y],i=0;1<<i<=d;++i)
        if(d&(1<<i))
            x=fa[x][i];
    if(x==y)
        return x;
    for(int i=20;~i;--i)
        if(fa[x][i]^fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    return fa[x][0];
}
inline void dfs2(int k,int f)
{
    for(int i=h[k];i;i=e[i].nxt)
    {
        dfs2(e[i].to,k);
        s[k][0]+=s[e[i].to][0];
        s[k][1]+=s[e[i].to][1];
    }
    if(k)
        ans+=1ll*s[k][0]*s[k][1]*(len[k]-len[f]);
}
inline void dfs3(int k)
{
    for(int i=h[k];i;i=e[i].nxt)
        dfs3(e[i].to);
    h[k]=s[k][0]=s[k][1]=0;
}
int main()
{
    n=read(),m=read();
    cin>>str;
    link[0]=-1;
    for(int i=n-1;~i;--i)
    {
        build(str[i]-'a');
        num[i+1]=lst;
    }
    for(int i=1;i<=cnt;++i)
    {
        add(link[i],i);
        //cout<<link[i]<<" "<<i<<'\n';
    }
    dfs1(0,-1,1);
    dfs3(0);
    tot=0;
    while(m--)
    {
        int p1=read(),p2=read();
        t[top=1]=0;
        for(int i=1;i<=p1;++i)
            ++s[q[i]=num[read()]][0];
        for(int i=1;i<=p2;++i)
            ++s[q[i+p1]=num[read()]][1];
        sort(q+1,q+p1+p2+1,cmp);
        q[0]=0;
        for(int i=1;i<=p1+p2;++i)
        {
            if(q[i]==q[i-1])
                continue;
            int lca=LCA(t[top],q[i]);
            if(lca!=t[top])
            {
                while(dfn[lca]<dfn[t[top-1]])
                {
                    add(t[top-1],t[top]);
                    --top;
                }
                if(lca!=t[top-1])
                {
                    add(lca,t[top]);
                    t[top]=lca;
                }
                else
                    add(lca,t[top--]);
            }
            t[++top]=q[i];
        }
        while(top>1)
        {
            add(t[top-1],t[top]);
            --top;
        }
        ans=0;
        dfs2(0,0);
        cout<<ans<<'\n';
        dfs3(0);
        tot=0;
    }
    return 0;
}
```

---

## 作者：Fading (赞：1)

有经验的选手应该可以秒杀这个套路题。

首先，LCP 问题可以转化成后缀树上的 lca 问题，然后就可以建虚树，枚举 lca ，开一个桶，批量处理了。

最优复杂度$O(n+\sum{(k_i+q_i)})$。当然这个做法比较没意思，我们想想后缀数组怎么做。

首先，LCP 问题可以转化成区间最小值问题（rmq），然后问题相当于给你两个集合$A,B$，询问两两之间最小值之和。

基础好的选手可以很快的看出解法。先用两个集合给出的值来把数组分段，一个段对应一个区间，显然最小值都是拿这些整段拼起来的。

然后枚举每一段的贡献。用单调栈计算出一个段作为最小值贡献到的端点，然后用一个前缀和计算有多少个区间落在这个范围内就好了。

最优复杂度$O(n+\sum{(k_i+q_i)})$。

代码好写，这里就不贴了。

---

