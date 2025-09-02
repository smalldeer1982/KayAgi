# [NWRRC 2017] Equal Numbers

## 题目描述

给定一个包含 $n$ 个整数 $a_{1}, \ldots, a_{n}$ 的列表。你可以执行以下操作：选择某个 $a_{i}$ 并将其乘以任意正整数。  

你的任务是计算在进行 $k$ 次操作后列表中可能出现的不同整数的最小数量，要求对所有 $0 \le k \le n$ 都进行计算。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6
3 4 1 2 1 2
```

### 输出

```
4 4 3 3 2 2 1
```

# 题解

## 作者：_GW_ (赞：3)

## 思路

1. 首先，若要让不同的数的数量减少，必须要把某个数赶尽杀绝，全部同化成其他数，其代价是数组内该数的出现次数。

2. 其次，考虑操作的策略，要么改成数组内的其他数（记为方案 $1$），要么就干脆一劳永逸，改成所有数的公倍数（记为方案 $2$）。

3. 然后，再考虑如何在这两种方案中抉择，发现把第一次使用方案 $1$ 时，极有可能没有让不同的数的数量减少，如果已经使用了一次方案 $1$，那么后续再使用方案 $1$ 是显然比方案 $2$ 只优不劣的。即可发现要么全用方案 $1$，要么全用方案 $2$。

4. 之后就好办了，详见代码。

## code


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int a[N],cnt[N],vis[N],sum[N],n,m,k,x,y,b[N],c[N],d[N],T,len;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>d[i];
    vis[d[i]]++;//输入并记录每个数的出现次数 
  }
  sort(d+1,d+1+n);
  for(int i=1;i<=n;i++)
  {
    if(d[i]!=d[i-1])
    {
      a[++m]=d[i];
      c[m]=vis[d[i]];//手动去重，并记录每个数改成所有数的最小公倍数的代价 （即其出现次数）
    }
  }
  for(int i=1;i<=m;i++)
  {
    for(int j=a[i]*2;j<=1e6;j+=a[i])//这个东西是nlogn的 ,但我不会证 
    {
      if(vis[j])
      {
        b[++len]=vis[a[i]];//寻找每个元素在数组组中是否有倍数，并记录该元素改成其倍数的代价（即其出现次数） 
        break;
      }
    }
  }
  sort(c+1,c+1+m);
  sort(b+1,b+1+len);//记得排序，毕竟选越小的越优 
  for(int i=1;i<=n;i++)
  {
    sum[i]=sum[i-1]+c[i];cnt[i]=cnt[i-1]+b[i];//前缀和优化 
  }
  int x=0,y=0;
  for(int i=0;i<=n;i++)
  {
    while(x+1<=m&&sum[x+1]<=i) ++x;
    while(y+1<=len&&cnt[y+1]<=i) ++y;//对于每个k，看是变成最小公倍数更优还是变成数列中的其他数更优 
    cout<<(m-max(x-1,y))<<' '; 
  }cout<<'\n';
  return 0;
} 
```

---

## 作者：Starlight237 (赞：1)

首先一个核心的观察是答案单调，这种答案单调而且重复段较长的可以考虑反过来求，即求出 $k_{cnt}$ 表示使最终数列有最多 cnt 种数所需要的最少操作次数，然后在这个数组上跑一遍还原答案即可。

**Lemma0** 存在一种操作方式，每次仅乘以 $\text{LCM}\{a_1...a_n\}$ 的约数即能达到最优情况。  
证明：显然。乘上其他数是没有意义的。  

**Lemma1** 最优情况下任何数只会被操作一次。  
证明：若被操作了两次，显然合并为一次具有完全等价的效果。  

**Lemma2** 将一个数其操作成 $\operatorname{LCM}\{a_1...a_n\}$ 一定不会比操作成其他**原数列没有的数**更劣。  
证明：这样的 $a_i$ 若对答案有贡献，则一定是和另一个（些） $a_j$ 被操作为相同的数 $t$（$t$ 不在原数列中，$a_j|t$）。若一个 $a_k$ 可以被操作成 $t$，当然也可以被操作成 $t$ 的倍数。由 Lemma0，$t|LCM$，从而直接操作成 LCM 不会更劣。  

**Lemma3** 若只有 k 次操作机会，则最优情况下存在一种操作方法，要么就是将 k 个出现次数最小的数操作成 LCM（方案一），要么不将任何数变成 LCM，只对那些存在一个真倍数在原数列中的数操作，选择它们中出现次数最少的 k 个数变成它们的某个倍数（方案二）。  
证明：若同时有这两种操作，设 $a_i$ 被操作成 LCM，$a_j$ 被操作成 $a_k(a_j|a_k)$，则改为将 $a_i$ 和 $a_j$ 同时操作成 LCM 不会使答案更劣。两种情况下 $a_j$ 都不会对数字种类数产生贡献。

由 Lemma3，可以把两种方案的答案单独计算再取 $\text{min}$。设 $f_{cnt}$ 为方案一的答案，$g_{cnt}$ 为方案二的答案。

我们将所有数按照出现次数排序，并令 $p_1>p_2>...> p_n$ 为这些数的出现次数。则 $f_1=n,f_{i+1}=f_i-p_i$。

考虑那些存在一个真倍数在原数列中的数构成的集合 $A$（去重意义下），令 $B$ 为 $A$ 的补集（去重意义下），将 $A$ 中数字也按照出现次数排序，出现次数记为 $p_1>...>p_{|A|}$，记 $s=p_1+...+p_{|A|}$，有 $g_i=+\infty(i<|B|),g_x=s,g_{|B|+i}=g_{|B|+i-1}-p_i$。

则有 $k_{cnt}=\min\{f_{cnt},g_{cnt}\}$。

友情提示：所有桶功能的数组一定要开够大！

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io {
#define BUFS 100000
	char in[BUFS], *p = in, *pp = in;
#define gc (p == pp && (pp = (p = in) + fread(in, 1, BUFS, stdin), p == pp) ? EOF : *p++)
	inline int read() {
		int x = 0; char ch, f = 0;
		while (!isdigit(ch = gc)) f |= ch == '-';
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc;
		return f ? -x : x;
	}
}
#define rd io :: read
const int N = 3e5 + 10, M = 1e6 + 10;
int n, buc[M], tmp[M], f[N], g[N], k[N], ans[N];
bool fl[M];
struct num {int v, cnt;} A[N], Ar[N];
inline bool operator<(const num&a, const num&b) {
	return a.cnt > b.cnt;
}
int main() {
	n = rd();
	int mx = 0;
	for (int i = 1, x; i <= n; ++i)
		x = rd(), ++buc[x], ++tmp[x], mx = max(mx, x);
	sort(tmp + 1, tmp + mx + 1, [](int a, int b){return a > b;});
	int tt;
	for (tt = 1; tmp[tt]; ++tt) ;
	--tt;
	for (int i = 1; i <= mx; ++i)
		if (buc[i])
			for (int j = i + i; j <= mx; j += i)
				buc[j] && (fl[i] = true, j = mx, false);
	int t1 = 0, t2 = 0;
	for (int i = 1; i <= mx; ++i) {
		if (fl[i] && buc[i]) A[++t1] = num {i, buc[i]};
		if (buc[i]) Ar[++t2] = num {i, buc[i]};
	}
	sort(A + 1, A + t1 + 1), sort(Ar + 1, Ar + t2 + 1);
	f[1] = n;
	for (int i = 2; i <= t2; ++i) f[i] = f[i - 1] - Ar[i - 1].cnt;
	int bb = tt - t1, s = 0;
	for (int i = 1; i <= t1; ++i) s += A[i].cnt;
	for (int i = 1; i < bb; ++i) g[i] = 0x3f3f3f3f;
	g[bb] = s;
	for (int i = 1; i <= t1; ++i) g[bb + i] = g[bb + i - 1] - A[i].cnt;
	for (int i = 1; i <= tt; ++i) k[i] = min(f[i], g[i]);
	for (int i = n, j = 1; ~i; ans[i] = j, --i)
		while (k[j] > i) ++j;
	for (int i = 0; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：陌路的花 (赞：0)

分析性质，对于一个数我们有两种对它的操作：

1. 将它变成它的倍数，且这个倍数在原数组中出现过.
2. 将它变成所有数的**最小公倍数**.

由于数的顺序并不重要，因此为了方便将相同大小的数成为同**一类数**.

再将所有数类按照能否执行操作 $2$ 分成两个集合 $A$ 和 $B$ ，显然 $|B|=\text{原本序列中不同数的个数}$ ，因为所有数都可以执行操作 $2$ .

对于操作 $1$ ，显然对于某一类数，要么全部操作完，要么操作时乘上 $1$ ，因为只操作部分对答案没有贡献.

设这样操作了 $k$ 类数，那它的答案就是 $tot-k$ ，$tot$ 指的是原序列中数的类数.

对于操作 $2$ ，等价于在操作 $1$ 的基础上新增一类数，所以如果操作了 $k$ 类的话，它的答案就是 $tot-k+1$ .

那将原本操作 $1$ 乘 $1$ 的那些操作拿来做操作 $2$ 会不会更优？

对于同一种操作，显然是优先操作所含个数更小的数类更优，下面也秉持这种思想。

注意到 $\forall i\in [1,\min(|A|,|B|)] \ , \ cnt_A[i]\ge cnt_B[i]$ ，于是推出 $A$ 中可操作的类数 $k_A$ 必定小于等于 $B$ 中的操作类数 $k_B$ .

假设等于，那么剩余的操作数显然不能在 $B$ 中完整地操作一类.

如果小于，那么剩余的操作数**最多**只能在 $B$ 中完整地操作一类，由于这样又会新增一类，所以对答案的贡献不变.

否则导致 $k_B>k_A+1$ ，此时全部执行操作 $2$ 更优.

综上，对于一个 $i$ 最多只会执行上述其中一种操作.

于是对于两个集合分别打标记维护即可，时间复杂度 $O(n\log n)$ .

---

## 作者：Union_Find (赞：0)

~~一道很抽象的题~~

# 题意

题意很简单，就是你每次操作可以将一个数乘上任意值，求当可以操作 $k\in[0,n]$ 时，最少有几个数不同。

# 思路

## First

很明显，答案是单调不递增的，因为操作次数越多，就可以减少种数，至少不会变多。

## Second

那么，减少种数只有两种办法。

1. 有两个数是倍数关系，将较小数乘上商。
2. 两个数不是倍数关系，都乘成 $LCM$。

对于以上两种方法，肯定不会既有 $1$ 又有 $2$，原因很简单，因为不会产生新的贡献。

## Third

有了以上结论，我们就可以开始愉快代码了。

代码较长，所以 `debug` 弄了很久，大约一个小时吧。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, a[300005], b[300005], en, p[300005], maxn, ans1, ans2, aa[300005], bb[300005];
set <ll> s;
map <ll, ll> t;
il bool cmp(ll a, ll b){
	if (p[a] != p[b]) return p[a] < p[b];
	return a < b;
}
int main(){
	scanf ("%lld", &n);
	for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]), p[a[i]]++, s.insert(a[i]), maxn = max(maxn, a[i]);
	for (int i = 1; i <= n; i++){
		if (t.count(a[i])){
			if (t[a[i]]) b[++en] = a[i];
			continue;
		}
		for (int j = 2; j * a[i] <= maxn; j++){
			if (s.count(a[i] * j)){
				b[++en] = a[i];
				t[a[i]] = 1;
				break;
			}
		}
		if (t.count(a[i]) == 0) t[a[i]] = 0; 
	}
	sort (a + 1, a + n + 1, cmp);
	sort (b + 1, b + en + 1, cmp);
	ans1 = s.size() + 1, ans2 = ans1 - 1;
	for (int i = 1; i < n; i++){
		if (a[i] != a[i + 1]) ans1--;
		if (i <= en && b[i] != b[i + 1]) ans2--;
		aa[i] = ans1, bb[i] = ans2;
	}
	aa[0] = bb[0] = s.size(), aa[n] = bb[n] = 1;
	for (int i = 0; i <= n; i++) printf ("%lld ", min(aa[i], bb[i]));
	return 0;
}

```

---

