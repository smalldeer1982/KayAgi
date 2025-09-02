# Number Of Permutations

## 题目描述

You are given a sequence of $ n $ pairs of integers: $ (a_1, b_1), (a_2, b_2), \dots , (a_n, b_n) $ . This sequence is called bad if it is sorted in non-descending order by first elements or if it is sorted in non-descending order by second elements. Otherwise the sequence is good. There are examples of good and bad sequences:

- $ s = [(1, 2), (3, 2), (3, 1)] $ is bad because the sequence of first elements is sorted: $ [1, 3, 3] $ ;
- $ s = [(1, 2), (3, 2), (1, 2)] $ is bad because the sequence of second elements is sorted: $ [2, 2, 2] $ ;
- $ s = [(1, 1), (2, 2), (3, 3)] $ is bad because both sequences (the sequence of first elements and the sequence of second elements) are sorted;
- $ s = [(1, 3), (3, 3), (2, 2)] $ is good because neither the sequence of first elements $ ([1, 3, 2]) $ nor the sequence of second elements $ ([3, 3, 2]) $ is sorted.

Calculate the number of permutations of size $ n $ such that after applying this permutation to the sequence $ s $ it turns into a good sequence.

A permutation $ p $ of size $ n $ is a sequence $ p_1, p_2, \dots , p_n $ consisting of $ n $ distinct integers from $ 1 $ to $ n $ ( $ 1 \le p_i \le n $ ). If you apply permutation $ p_1, p_2, \dots , p_n $ to the sequence $ s_1, s_2, \dots , s_n $ you get the sequence $ s_{p_1}, s_{p_2}, \dots , s_{p_n} $ . For example, if $ s = [(1, 2), (1, 3), (2, 3)] $ and $ p = [2, 3, 1] $ then $ s $ turns into $ [(1, 3), (2, 3), (1, 2)] $ .

## 说明/提示

In first test case there are six permutations of size $ 3 $ :

1. if $ p = [1, 2, 3] $ , then $ s = [(1, 1), (2, 2), (3, 1)] $ — bad sequence (sorted by first elements);
2. if $ p = [1, 3, 2] $ , then $ s = [(1, 1), (3, 1), (2, 2)] $ — bad sequence (sorted by second elements);
3. if $ p = [2, 1, 3] $ , then $ s = [(2, 2), (1, 1), (3, 1)] $ — good sequence;
4. if $ p = [2, 3, 1] $ , then $ s = [(2, 2), (3, 1), (1, 1)] $ — good sequence;
5. if $ p = [3, 1, 2] $ , then $ s = [(3, 1), (1, 1), (2, 2)] $ — bad sequence (sorted by second elements);
6. if $ p = [3, 2, 1] $ , then $ s = [(3, 1), (2, 2), (1, 1)] $ — good sequence.

## 样例 #1

### 输入

```
3
1 1
2 2
3 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
2 3
2 2
2 1
2 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
1 1
1 1
2 3
```

### 输出

```
4
```

# 题解

## 作者：米奇 (赞：3)

## 做法：思维

发现题意就是任意交换二元组，使得n个二元组不存在一维单调不减。

简单的转换：答案=总方案-单调不减的方案数

由于有两维，容斥，单调不减=第一维单调不减+第二维单调不减-两维都单调不减

单调不减可以排序然后O（n）求出方案数

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define next Next
#define gc getchar
#define int long long
const int mod=998244353;
const int N=1e6+5;
int n,ans1,ans2,ans3,jc[N];
struct node{
	int x,y;
}a[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
inline int read()
{
    int ret=0,f=0;char c=gc();
    while(!isdigit(c)){if(c=='-')f=1;c=gc();}
    while(isdigit(c)){ret=ret*10+c-48;c=gc();}
    if(f)return -ret;return ret;
}
bool cmp(node a,node b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}
signed main()
{
	n=read();
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%mod;
	for(int i=1;i<=n;i++)
	{
		a[i].x=read();a[i].y=read();
	}
	sort(a+1,a+n+1,cmp);
	ans1=1;
	for(int l=1,r=1;l<=n;l=r+1)
	{
		r=l;
		while(r<n&&a[r+1].x==a[r].x)r++;
		int x=r-l+1;
		ans1=ans1*jc[x]%mod;
	}
	sort(a+1,a+n+1,cmp2);
	ans2=1;
	for(int l=1,r=1;l<=n;l=r+1)
	{
		r=l;
		while(r<n&&a[r+1].y==a[r].y)r++;
		int x=r-l+1;
		ans2=ans2*jc[x]%mod;
	}
	sort(a+1,a+n+1,cmp);
	bool flag=0;
	for(int i=2;i<=n;i++)
		if(a[i].y<a[i-1].y)
		{
			ans3=0;
			flag=1;
		}
		if(!flag){
			ans3=1;
			for(int l=1,r=1;l<=n;l=r+1)
			{
				r=l;
				while(r<n&&a[r+1].x==a[r].x&&a[r+1].y==a[r].y)r++;
				int x=r-l+1;
				ans3=ans3*jc[x]%mod;
			}
		}
	int x=((ans1+ans2-ans3)%mod+mod)%mod;
	x=(jc[n]-x+mod)%mod;
	cout<<x;
}
```

---

## 作者：Lolierl (赞：3)

容斥计数题。

先将问题转化为，求$s$的一个排列，求使$s$双关键字都不按不降序排列的方案个数。这里两个排列不同排列是指只要有两个元素在这两个排列中位置相同而原序列中的下标不同，也就是相同元素交换位置生成的排列也是不同的

直接计算似乎不太好算，我们考虑容斥

设$c1$为使第一关键字按不降序排列的方案个数

$c2$为使第二关键字按不降序排列的方案个数

$c3$为使两个关键字都按不降序排列的方案个数

根据容斥原理，$ans = n! - c1 - c2 + c3$

那么它们怎么计算呢？
以$c1$为例
它有不同的方案当且仅当有相同元素，那么把它们交换位置就生成了一种不同方案。显然不同元素值之间是独立的，那么我们只需要将每个元素出现次数的阶乘乘起来就好了。甚至不需要求逆元。

再注意一下$c3 = 0$的情况就好了

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int, int>
using namespace std; 
 
const int M = 998244353; 
int n, cnt[1000001], t[1000001]; 
pii s[1000001]; 
 
void init()
{
	t[0] = 1; t[1] = 1; 
	for(int i = 2; i <= n; i++)
		t[i] = (1ll * t[i - 1] * i) % M; 
}
int main()
{
	scanf("%d", &n); 
	init(); 
	
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &s[i].first, &s[i].second); 
		cnt[s[i].first]++; 
	}
	
	long long c1 = 1; 
	for(int i = 1; i <= n; i++)
		if(cnt[i])c1 = c1 * t[cnt[i]] % M; 
	
	memset(cnt, 0, sizeof(cnt)); 
	for(int i = 1; i <= n; i++)
		cnt[s[i].second]++; 
	
	long long c2 = 1; 
	for(int i = 1; i <= n; i++)
		if(cnt[i])c2 = c2 * t[cnt[i]] % M; 
	
	sort(s + 1, s + n + 1); 
	long long c3 = 1; 
	int p = 1; 
	for(int i = 2; i <= n; i++)
	{
		if(s[i].second < s[i - 1].second){c3 = 0; break; }
		if(s[i].first == s[i - 1].first && s[i].second == s[i - 1].second)
			p++; 
		else
		{
			c3 = c3 * t[p] % M; 
			p = 1; 
		}
	}
	c3 = c3 * t[p] % M; 
	long long ans = t[n] - c1 - c2 + c3; 
	while(ans < 0)ans += M; 
	printf("%I64d", ans); 
	return 0; 
}
```

---

## 作者：fsy_juruo (赞：2)

题目要求满足两维数字均不有序的序列的个数，很明显可以将其转化为一个容斥问题：$cnt(GoodSequence) = cnt(All) - cnt(ASorted) - cnt(BSorted) + cnt(ASorted \&\&BSorted)$

其次，考虑如何计数。

$cnt(All)$ 就等于其所有的可能排列个数，明显等于 $n!$。

再考虑如何计算 $cnt(ASorted)$。设第一维中不同元素个数为 $m$，从小到大排序后这 $m$ 个元素为 $a_1, a_2, \cdots, a_m$，其在第一维中出现的个数分别为 $c_1, c_2, \cdots, c_m$。很明显，对于一个元素 $a_i$，它只有 $c_i$ 个位置可放置，产生的不同情况数即为 $c_i !$。

举个例子，对于序列 $[1,2,2,2,3,1,2,2,3,3]$，$m = 3$，$a = [1, 2, 3]$，$c = [2, 5, 3]$。对于两个 $1$，它只有在前 $2$ 个位置的时候，数组才可能有序。不同的情况数为 $2!$。

所以，根据乘法原理，$cnt(ASorted) = \prod_{i=1}^{m}c_i !$。$cnt(BSorted)$ 做法类似。

$cnt(ASorted\&\&BSorted)$ 也可以用类似方法计算，但是可能存在第一维有序，但第二维无序的情况。所以要先将读进来的数对按照第一维为第一关键字，第二维为第二关键字排序。再线性扫一遍第二维。如果第二维中存在整数 $i$ 使得 $B[i] > B[i+1]$，则 $cnt(ASorted \&\& BSorted) = 0$，反之照上面的做法计算即可。

**代码：**

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = '\n') {
	write(x); putchar(sp);
}
const int maxn = 3e5 + 10;
const LL mod = 998244353ll;
LL n, fac[maxn];
pair<int, int> perm[maxn];
map<pair<int, int>, int> ds;
map<int, int> aa, bb;
int main() {
	read(n);
	fac[0] = 1;
	_rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	_rep(i, 1, n) {
		read(perm[i].first); read(perm[i].second);
        aa[perm[i].first]++; bb[perm[i].second]++;
        ds[perm[i]]++;
	}
    sort(perm + 1, perm + n + 1);
    LL ans = fac[n], tmpa = 1, tmpb = 1, tmpab = 1, valid = 1;
    _rep(i, 2, n) {
        if(perm[i].second < perm[i - 1].second) valid = 0;
    }
    map<int, int> :: iterator it;
    for(it = aa.begin(); it != aa.end(); it++) {
        pair<int, int> p = *it;
        tmpa = 1ll * tmpa * fac[p.second] % mod;
    }
    for(it = bb.begin(); it != bb.end(); it++) {
        pair<int, int> p = *it;
        tmpb = 1ll * tmpb * fac[p.second] % mod;
    }
    map<pair<int, int>, int> :: iterator ab;
    for(ab = ds.begin(); ab != ds.end(); ab++) {
        int cnt = (*ab).second;
        tmpab = 1ll * tmpab * fac[cnt] % mod;
    }
    writesp((ans - tmpa + mod - tmpb + mod + tmpab * valid + mod) % mod);
	return 0;
}
```



---

## 作者：nytyq (赞：1)

## 思路

正难则反和简单容斥原理。  

**好序列**数量=总数-$a_i$ 有序的方案数-$b_i$ 有序的方案数+$(a_i,b_i)$ 都有序的方案数。

1. 总数即乱排数量，为 $n!$。
2. $a_i$ 有序的排列，每一块相同的数内，可以随意交换，即 $[l,r]$ 中的 $a_i=a_j(l \le i,j \le r)$ 满足，即可随意交换，考虑其数量为 $p$，则有 $p!$ 种情况。考虑到计数，$\text{cnt}_i$ 为 $i$ 的出现次数，则这种情况的答案数为 $\displaystyle \prod _{i=1} ^ \text{n} (\text{cnt}_i!)$。
3. $b_i$ 与 $a_i$ 讨论相同。
4. 最后考虑如何 $(a_i,b_i)$ 都有序的方案数，同理有 $[l,r]$ 中的 $a_i=a_j,b_i=b_j(l \le i,j \le r)$ 满足，即可任意交换，考虑其数量为 $q$，则有 $q!$ 种情况。考虑到计数，令 $\text{pro}_{i,j}$ 为 $(i,j)$ 出现的次数。此情况答案为 $\displaystyle \prod _{i=1}^\text{n} \text {pro}_{a_i,b_i}$。

但注意细节，$0!=1$，而且在过程中出现了减法，令 $P=998244353$，则考虑 $\text{ans}=(\text{ans}$ $\text{mod}$ $P$ + $P)$ $\text{mod}$ $P$。

---

## 作者：mango2011 (赞：1)

这道题大概的思路就是用容斥，答案为：

总方案数 $-$ $a_i$ 有序的方案数 $-$ $b_i$ 有序的方案数 $+$ $a_i,b_i$ 同时有序的方案数。

考虑逐个击破：

1) 总方案数为“所有都乱排”的方案数，为 $n!$。

2) 发现 $a_i$ 有序与 $b_i$ 有序是一个问题，只讨论 $a_i$ 的情形。考虑怎样的情况下才可以产生新的方案：

对于 $a_1,a_2,a_3,\dots,a_n$，对于 $l,r(1\le l\le r\le n)$ 使得 $a_i=a_j(l\le i,j\le r)$，那么 $l$ 与 $r$ 间的所有元素都可以互换顺序；反之，则不能随意互换顺序。于是考虑统计每一个数的出现次数，答案为 $\prod\limits_{i=1}^{n} cnt_{i}!$，$cnt_i$ 表示 $i$ 出现的次数。

3) 延续上面的思路。首先可以进行一轮排序，如果不存在方案，直接给出 $0$，否则：

对于 $s_1,s_2,s_3,\dots,s_n$，对于 $l,r(1\le l\le r\le n)$，如果 $a_i=a_j,b_i=b_j(l\le i,j\le r)$，那么 $l$ 与 $r$ 间的所有元素可以互换顺序。于是考虑统计每一个“对”出现的次数，答案为 $\prod\limits_{i=1}^{n}cnt_{a_i,b_i}!$，其中，$cnt_{x,y} $ 表示 $(x,y)$ 出现的次数。

**注意：对于每一个对，如果已经计算过 $cnt_{x,y}$，则直接把 $cnt_{x,y}$ 设置为 $0$，以避免重复计算。**

代码实现过程中，首先预处理 $k!$，注意 $0!=1$。后面的话开若干个桶统计个数，计算答案即可。

**注意：在统计答案过程中出现了减法，所以答案为**  $(ans\bmod 998244353+998244353)\bmod 998244353$。

综上，我们就把这道题做完了。

---

## 作者：_Communist (赞：0)

### 1.分析

如果直接看第一关键字或第二关键字是否不按升序排序，不好统计数量，假设原答案为 $|Ans|$，可以考虑用全集（即所有排列共 $n!$ 种）$|S|$ 减去 $|\overline{Ans}|$，即用 $n!$ 减去 $a$ 和 $b$ 任意一个升序排列的方案数。

如果设 $a$ 升序的方案为 $|A|$，$b$ 升序的方案为 $|B|$，那么 $|\overline{Ans}|$ 就等于 $|A|+|B|$ 吗？不是的。因为有可能有 $a$ 升序**并且** $b$ 同时升序的方案，而这种方案会被 $|A|$ 和 $|B|$ 都算到。根据容斥原理，得 $|\overline{Ans}|=|A|+|B|-|A \cap B|$。

所以，答案 $|Ans|=|S|-|A|-|B|+|A \cap B|$。

如何计算？$|S|$ 显然为 $n!$，$|A|$ 可以用一个桶维护，因为 $1\leq a_i\leq n$，所以遍历一遍桶，此时元素一定从小到大，而对于相同元素，可以随便排列，但不同的元素不能交换，因为要从小到大。因此，假设 $c_i$ 表示 $a$ 中 $i$ 出现的次数，那么 $|A|=\prod\limits_{i=1}^{n}c_i!$，因为对于每个相同的元素，都有 $A_{c_i}^{c_i} = c_i!$ 种排列方式。不同元素不能交换（在排序后）。

同理，假设 $d_i$ 表示 $b$ 中 $i$ 出现的次数，那么 $|B|=\prod\limits_{i=1}^{n}d_i!$。

接下来，我们要计算 $|A \cap B|$。从定义出发，$A \cap B$ 表示 $a$ 和 $b$ 都单调不降的方案集合。所以可以将二元组 $a_i,b_i$ 按第一关键字从小到大排序，第一关键字相同按第二关键字从小到大排序，只要中间有一个 $b_i>b_{i-1}$，说明没有方案，$|A \cap B|=0$。对于所有的 $a_i=a_j$ 且 $b_i=b_j(j  \not=i)$，都可以交换位置，可以按照上面的思路计算。

### 2.代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[300005], b[300005], c[300005][2], f[300005];
long long ans, suma, sumb, sum;
const int mod = 998244353;
pair<int, int> p[300005];
inline long long qpow(long long x, int y) {
	long long res = 1;
	while (y) {
		if (y & 1) res = res * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return res;
}
signed main() {
	cin >> n;
	f[0] = 1;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
		++c[a[i]][0], ++c[b[i]][1], f[i] = f[i - 1] * i % mod;
		p[i] = make_pair(a[i], b[i]);
	}
	sort(p + 1, p + 1 + n);
	sum = sumb = suma = 1;
	ans = f[n];
	for (int i = 1; i <= n; ++i) {
		if (!c[i][0]) continue;
		suma = suma * f[c[i][0]] % mod;
	}
	for (int i = 1; i <= n; ++i) {
		if (!c[i][1]) continue;
		sumb = sumb * f[c[i][1]] % mod;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (p[i - 1].second > p[i].second) {
			sum = 0; break;
		}
		if (p[i].first == p[i - 1].first && p[i].second == p[i - 1].second) ++cnt;
		else sum = sum * f[cnt] % mod, cnt = 1;
	}
	sum = sum * f[cnt] % mod;
	cout << (((ans - suma + mod) % mod - sumb + mod) + sum) % mod;
	return 0;
}
```

---

