# [ABC143F] Distinct Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc143/tasks/abc143_f

高橋くんは $ N $ 枚のカードを持っています。 $ i $ 番目のカードには整数 $ A_i $ が書かれています。

高橋くんは整数 $ K $ を選びます。そして、以下の操作を何度か繰り返します。

- 書かれている整数が互いに異なるちょうど $ K $ 枚のカードを選び、食べる（食べたカードは消滅する）

$ K\ =\ 1,2,\ \ldots,\ N $ のそれぞれに対して、操作を行える最大の回数を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ N $
- 入力はすべて整数

### Sample Explanation 1

$ K\ =\ 1 $ のとき、操作を以下のように行うことができます。 - $ 1 $ 枚目のカードを選び、食べる - $ 2 $ 枚目のカードを選び、食べる - $ 3 $ 枚目のカードを選び、食べる また、$ K\ =\ 2 $ のとき、操作を以下のように行うことができます。 - $ 1 $ 枚目のカードと $ 2 $ 枚目のカードを選び、食べる $ K\ =\ 3 $ のときは、操作を行うことができません。$ 1 $ 枚目のカードと $ 3 $ 枚目のカードを同時に選べないことに注意してください。

## 样例 #1

### 输入

```
3
2 1 2```

### 输出

```
3
1
0```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
5
2
1
1
1```

## 样例 #3

### 输入

```
4
1 3 3 3```

### 输出

```
4
1
0
0```

# 题解

## 作者：yemuzhe (赞：7)

[题目传送门](/problem/AT_abc143_f)

### 解法

这里给出一种严格线性做法。

观察到答案只和原数字出现的次数相关，使用 $cnt _ i$ 统计原数字 $i$ 的出现次数。

继续发掘性质。发现如果取了 $x$ 次，那么对于任意 $cnt _ i$，它最多且可以被取 $\min \{cnt _ i, x\}$ 次。

*（可略过）*必要性是显然的。至于充分性，对于每个 $i$，我们考虑对于当前取的数个数最少的 $\min \{cnt _ i, x\}$ 次，都让它们取一个 $i$。

这样就保证了当前取的数的个数最多的和最少的相差不超过 $1$，这样显然保证方案合法且最优。

---

对于 $\min \{cnt _ i, x\}$，可以分类讨论：

1. 如果 $cnt _ i \le x$，则它们总共被取的次数为 $\sum _ {cnt _ i \le x} cnt _ i$。
2. 否则，它们总共被取次数为 $\sum _ {cnt _ i > x} x = k \sum _ {cnt _ i > x} 1$。

这分别是前缀和与后缀和的形式。

我们可以处理出每个 $cnt _ i$ 分别出现了多少次（套娃），记为 $ccnt _ i$。

令 $pcnt _ x = \sum _ {i = 1} ^ x ccnt _ i \cdot i$，$scnt _ x = \sum _ {i = x + 1} ^ n ccnt _ i$（这里的 $i$ 其实相当于上文的 $cnt _ i$），则总共被取次数为 $f (x) = pcnt _ x + k \cdot scnt _ {x + 1}$。

---

发现对于一组 $(k, x)$ 合法，当且仅当 $k \cdot x \le f (x)$（当前取走的次数不能超过总共可被取的次数）。

那怎么统计答案呢？其实不用二分，注意到随着 $k$ 的增大，答案会单调不增，可以考虑跑一遍双指针。

时间复杂度：$O (n)$。

### AC Code

```cpp
#include <cstdio>
#define N 300005
using namespace std;

int n, cnt[N], ccnt[N], pcnt[N], scnt[N];

// 取 x 次：s[x] + x * scnt[x + 1]
int calc (int x) {return pcnt[x] + x * scnt[x + 1];}

int main ()
{
	scanf ("%d", &n);
	for (int i = 1, x; i <= n; i ++) scanf ("%d", &x), cnt[x] ++;
	for (int i = 1; i <= n; i ++) ccnt[cnt[i]] ++;
	for (int i = 1; i <= n; i ++) pcnt[i] = pcnt[i - 1] + i * ccnt[i];
	for (int i = n; i; i --) scnt[i] = scnt[i + 1] + ccnt[i];
	for (int i = 1, ans = n; i <= n; i ++)
	{
		while (i * ans > calc (ans)) ans --;
		printf ("%d\n", ans);
	}
    return 0;
}
```



---

## 作者：Cx114514 (赞：4)

## AT_abc143_f 题解

本题要求取的次数的最大值，不妨使用二分答案。

那如何设计二分条件呢？我们可以先进行一些简单的分析：

我们设从中取 $k$ 个互不相同的数字，可以取 $n$ 次。那么当一个数字的出现次数大于 $n$ 时，他最多只能被取到 $n$ 次（只因每次取出的数字互不相同），而出现次数小于等于 $n$ 时，都可以被取到。我们可以使用数组 $b$ 记录每个数字出现的次数，数组 $c$ 中记录每个出线次数对应的数字的出现次数之和，数组 $d$ 中记录每个出现次数对应的不同数字个数。那最终能被取到的数字个数即为 $\sum\limits_{i=1}^{k}$ $\mathit{c}_{i}$ $+$ $k\sum\limits_{i=k+1}^{n}$ $\mathit{d}_{i}$，中间的求和我们可以用前缀和优化，此时，如果这个数如果大于等于 $k$ $\times$ $n$ （总共要取的数字个数），则该次二分满足条件。

单次二分的时间复杂度是 $O$($\log$ $n$)，我们需要从 $1$ $\sim$ $n$ 枚举 $k$，总时间复杂度 $O$($n$ $\log$ $n$)。

下面贴上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int E = 3e5 + 5;

int n, k, a[E], b[E], c[E], d[E], e[E], f[E];

bool judge(int x, int y)
{
	int sum = e[x] + x * (f[n] - f[x]);
	return sum >= x * y;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[a[i]]++;
	}
	for (int i = 1; i <= n; i++)
	{
		c[b[i]] += b[i];
		d[b[i]]++;
	}
	for (int i = 1; i <= n; i++)//前缀和
	{
		e[i] = e[i - 1] + c[i];
		f[i] = f[i - 1] + d[i]; 
	}
	for (int i = 1; i <= n; i++)
	{
		int l = 0, r = n / i, mid, ans;
		while (l <= r)
		{
			mid = (l + r) / 2;
			if (judge(mid, i))
			{
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
    return 0;
}

```
这样我们就愉快地 AC 了这道题了。

---

## 作者：liangbowen (赞：4)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc143_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17514668.html)

很有趣的题。提供一种和现有题解略微不同的做法。 

## 思路

突破点在于反着想。**当最多能取** $x$ **次时，每次我取的不同数字的数量，最多是多少**。

统计一下每个数字出现的次数 $cnt_i$。那么这个最多次数应为

$$\left\lfloor\dfrac{\sum\min(cnt_i, x)}x\right\rfloor$$

不妨设其为 $T(x)$，则 $[T(x+1) + 1, T(x)]$ 的答案都是 $x$。

于是直接求即可。唯一的问题是如何快速求 $T(x)$。发现所有 $T(i)$ 都得求出来，所以套个指针扫一遍即可，具体看代码。

线性复杂度。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 3e5 + 5;
int a[N], tt[N], cnt[N];
long long tmp[N], f[N], ans[N];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), tt[i] = a[i];
	
	sort(a + 1, a + n + 1), sort(tt + 1, tt + n + 1);
	int cur = unique(tt + 1, tt + n + 1) - tt - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(tt + 1, tt + cur + 1, a[i]) - tt;
	
	for (int i = 1; i <= n; i++) cnt[a[i]]++;
	sort(cnt + 1, cnt + cur + 1);
	for (int i = 1, j = 0; i <= cur; i++)
		while (j < cnt[i])
			tmp[++j] = cur - i + 1;
	long long sum = 0;
	for (int i = 1; i <= n; i++) sum += tmp[i], f[i] = sum / i;
	
	for (int i = 0; i <= n; i++)
		for (int j = f[i + 1] + 1; j <= f[i]; j++)
			ans[j] = i;
	for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

希望能帮助到大家！

---

## 作者：StarRoam (赞：1)

[ 题目传送门](https://www.luogu.com.cn/problem/AT_abc143_f)

本题中，先对种类个数进行预处理。

令 $cnt_i$ 表示：第 $i$ 种元素的个数。

令 $m$ 表示：元素的种类个数。

当一次选 $k$ 个，能选 $t$ 次时

- 对于 $cnt_i \ge t$，对于这 $t$ 次的贡献最多只有 $t$ 个。
- 对于 $cnt_i < t$，对于这 $t$ 次的贡献只能有 $cnt_i$ 个。
- 而对于所选数的总数应该为 $k \times t$ 个。
  
所以合法方案应该满足：

$$\sum_{i=1}^{m} \min(cnt_i,t) \ge k \times t$$

对于不等式左边，我们可以用前缀和与二分求出，易发现答案具有单调性，所以总时间复杂度为 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
	int f=1,k=0;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c))
		k=(k<<1)+(k<<3)+(c^48),c=getchar();
	return k*f;
}
const int N=3e5+5;
int n,m,ct[N],a[N],sum[N];
bool check(int k,int t)
{
	int num=lower_bound(a+1,a+m+1,t)-a-1;
	return (sum[num]+(m-num)*t>=k*t);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		ct[read()]++;
	for(int i=1;i<=n;i++)
		if(ct[i]>0) a[++m]=ct[i];
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++)
		sum[i]=sum[i-1]+a[i];
	int ans=n;
	for(int i=1;i<=n;i++)
	{
		while(ans>0&&check(i,ans)==false) ans--;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：1)

一眼题，看完题很快想到了思路。

不难发现，如果相同的一个数字出现超过 $t$ 次，则只保留其中 $t$ 个后计算所有剩余数字个数 $s$，且如果 $t\leq\lfloor\frac{s}{i}\rfloor$，那么 $\lfloor\frac{s}{i}\rfloor$ 就是最大操作次数。证明不难。

不难发现 $k$ 在增加时合法的最大 $t$ 单调递减，作双指针维护 $t$，然后同时维护 $s$ 的值即可。

```cpp
n=read();
for (int i=1;i<=n;i++)
    a[i]=read(),mp[a[i]]++;
for (int i=1;i<=n;i++)
    if (mp[i]) c[mp[i]]++;
for (int i=1,t=n,s=n,g=0;i<=n;i++){
    while (t>s/i) g+=c[t],s-=g,t--;
    cout<<s/i<<'\n';
}
```

---

## 作者：CarroT5656 (赞：1)

考虑二分答案。

设当前每次要取 $k$ 个数，二分到可以取 $l$ 次。求是否合法。

我们令 $t_i$ 表示数字 $i$ 在数组中出现的次数。

那么一共能取到 $\sum\min(t_i,l)$ 个数。判断这个数是否大于等于 $k\times l$ 即可。

这样单次检查的时间复杂度为 $O(n)$，还要算上 $k$ 的枚举，$l$ 的二分的时间。总的复杂度就已经达到了 $O(n^2\log n)$。显然需要优化。

发现时间复杂度的瓶颈在于检查的地方。

不难想到可以先给 $t_i$ 排序，那么在和式中，就可以明确地分开 $t_i$ 和 $l$ 对和式的贡献。

用前缀和优化掉，就可以做到 $O(\log n)$ 的快速检查（还需要算上找到临界点的时间）。

发现找临界点实际上会被算很多遍，而 $l$ 也有一个上限 $n$。把这个临界点预处理出来就好了。

这样就可以做到 $O(1)$ 检查。

时间复杂度 $O(n\log n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define N 300005
ll n,a[N],t[N],s[N],pos[N];//s:前缀和，pos:临界点
bool check(ll k,ll l){
	return s[pos[l]]+l*(n-pos[l])>=k*l;
} 
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),t[a[i]]++;
	sort(t+1,t+n+1);
	for(ll i=1;i<=n;i++) s[i]=s[i-1]+t[i];
	for(ll i=1;i<=n;i++) pos[i]=upper_bound(t+1,t+n+1,i)-t-1;
	for(ll i=1;i<=n;i++){
		ll l=0,r=n/i,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(check(i,mid)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc143_f)

第一眼给人的感觉就是当 $k$ 越来越大的时候，能取的数量是单调不升的，即答案满足某些单调性。于是可以套路分治。

假设当前枚举的次数是 $t$，即判断 $\sum\min({\rm cnt}_ i,t)$ 是否大于等于 $k\times t$，我同学说有点像[这道题](https://www.luogu.com.cn/problem/P3586)。当然了求和这一部分是可以 $O(n)$ 预处理出来的，于是时间复杂度应该是 $O(n\log n)$。

但是其实是分治学傻了。我们再观察一下式子，次数为 $t$ 时的最大答案应该为 $R(t)=\bigg\lfloor\dfrac{\sum\min({\rm cnt}_ i,t)}{t}\bigg\rfloor$，然后 $L(t)=R(t+1)+1$，$[L(t),R(t)]$ 这个区间的答案就都是 $t$ 了，于是就是 $O(n)$ 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,num,sum;
int cnt[N],tcnt[N],T[N],ans[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++)cnt[read()]++;
	for(int i=1;i<=n;i++)
	{
		sum+=cnt[i];
		tcnt[cnt[i]]++;
	}
	for(int i=n;i>=1;i--)
	{
		num+=tcnt[i];
		sum-=tcnt[i]*i;
		T[i]=(sum+num*i)/i;
	}
	for(int i=0;i<=n;i++)
		for(int j=T[i+1]+1;j<=T[i];j++)
			ans[j]=i;
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

