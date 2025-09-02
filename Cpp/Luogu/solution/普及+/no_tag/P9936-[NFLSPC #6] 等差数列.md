# [NFLSPC #6] 等差数列

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/asxexdko.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/rzayzc9p.png)

## 题目描述

*Alek 岁*在某知名 OJ *代码力量*上做了 $a_i$ 道难度为 $i$ 的题。他希望做一些题使得 $a_i$ 形成 **公差非正** 的等差数列，这样画出来的统计图表很好看。

尽管 *Alek 岁*一天能做 42 道题，但他依然希望做尽可能少的题达到目标。你需要求出新做题数的最小值。

你可以认为 OJ 上有足够多的各种难度的题目。

## 说明/提示

对于所有数据，$1\leq T\leq 100$，$1\leq n, \sum n\leq 10 ^ 5$，$1\leq a_i\leq 10 ^ 9$。

- 子任务 1（$30$ 分）：$\sum n \leq 10 ^ 3$。
- 子任务 2（$70$ 分）：无特殊限制。

Source：NFLSPC #6 L by Alex_Wei

## 样例 #1

### 输入

```
6
2
822 1064
2
1064 822
4
1 3 4 2
4
2 4 3 1
6
2 6 2 1 4 4
9
9 9 8 2 4 4 3 5 3
```

### 输出

```
242
0
6
4
17
25
```

# 题解

## 作者：lizhous (赞：6)

考虑枚举公差 $d$，如何求得最少题数 $m$？

贪心的想，我们希望的等差数列是一条直线，而增加的数最少就相当于让直线最低且任意点不低过原序列。扫一遍序列，动态维护当先最少需要增加的数 $f$ 和当前末项大小 $g$，如果下一项 $a_i<g-d$，那么直接把下一项增加 $g-d-a_i$ 即可，否则需要把直线上移 $a_i-(g-d)$。归纳不难得出这样是最优的。

得到结论，令 $f(d)=m$，大胆猜想 $f$ 是单谷函数。

为什么？考虑直线变斜的过程，我们称完全贴合原序列的点为支点，那么不难发现支点是逐渐后移的。又因为斜度的增加，支点前的点贡献一定单调不减，支点后一定单调不增。所以支点前总贡献不降，支点后总共献不增。又因为 $f(d)$ 就是这两个贡献加起来，所以 $f(d)$ 是单谷的。

套上三分即可。

讲得比较抽象。

---

## 作者：251Sec (赞：2)

一个等差数列被首项和公差唯一确定。假设我们已知公差为 $-d$，为了使其合法，则等差数列每一项均大于等于原数列对应项。设首项为 $x$，即 $\forall i, x-(i-1)d \ge a_i$。这样我们可以在已知 $d$ 时求出 $x$ 的最小值，进而求出答案为 $\sum\limits_{i=1}^n x-(i-1)d-a_i=nx-\dfrac{n(n-1)}{2}d-\sum a_i$。

我们不可能枚举 $d$，但是我们发现 $x=\max\limits_{i=1}^n\left(a_i+(i-1)d\right)$，即一堆一次函数的最大值，是一个凸函数。于是我们的答案是一个凸函数减去一个一次函数减去一堆常数，最后还是个凸函数。所以直接在上面三分即可，复杂度 $O(n \log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n;
ll a[100005];
ll Calc(ll d) {
    ll x = 0, s = 0;
    for (int i = 1; i <= n; i++) x = max(x, a[i] + (i - 1) * d);
    for (int i = 1; i <= n; i++) s += x - (i - 1) * d - a[i];
    return s;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        ll l = 0, r = 1e9;
        while (r - l > 3) {
            ll lm = l + r >> 1, rm = lm + 1;
            if (Calc(lm) < Calc(rm)) r = rm;
            else l = lm;
        }
        ll ans = 1e18;
        for (ll i = l; i <= r; i++) ans = min(ans, Calc(i));
        printf("%lld\n", ans);
    }
    return 0;
} 
```

---

## 作者：EuphoricStar (赞：2)

对 $(i, a_i)$ 求出下凸包，那么一条凸包的斜率**非正**的切线是候选答案。

只考虑切凸包上第 $i$ 个点的切线，那么斜率的左边界是过凸包第 $i$ 和第 $i + 1$ 个点的直线斜率，右边界是过凸包第 $i - 1$ 和第 $i$ 个点的直线斜率。最优方案的切线斜率一定要么贴着左边界，要么贴着右边界，分类取个 $\max$ 即可。

注意斜率要是整数，上/下取整处理一下即可。

时间复杂度 $O(n)$。

```cpp
// Problem: P9936 [NFLSPC #6] 等差数列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9936
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 100100;

ll n, a[maxn], stk[maxn], top;
struct node {
	ll x, y;
	node(ll a = 0, ll b = 0) : x(a), y(b) {}
} b[maxn];

inline node operator + (const node &a, const node &b) {
	return node(a.x + b.x, a.y + b.y);
}

inline node operator - (const node &a, const node &b) {
	return node(a.x - b.x, a.y - b.y);
}

inline ll operator * (const node &a, const node &b) {
	return a.x * b.y - a.y * b.x;
}

inline ll f(ll n) {
	return n * (n + 1) / 2;
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		b[i] = node(i, a[i]);
	}
	top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top >= 2 && (b[stk[top]] - b[stk[top - 1]]) * (b[i] - b[stk[top - 1]]) >= 0) {
			--top;
		}
		stk[++top] = i;
	}
	ll ans = 1e18;
	for (int i = 1; i <= top; ++i) {
		ldb l = -1.1e9, r = 0;
		if (i > 1) {
			r = min(r, (ldb)(b[stk[i]].y - b[stk[i - 1]].y) / (b[stk[i]].x - b[stk[i - 1]].x));
		}
		if (i < top) {
			l = max(l, (ldb)(b[stk[i]].y - b[stk[i + 1]].y) / (b[stk[i]].x - b[stk[i + 1]].x));
		}
		for (ll x = ceil(l); x <= r && x - l <= 2; ++x) {
			ans = min(ans, a[stk[i]] * n - x * f(stk[i] - 1) + x * f(n - stk[i]));
		}
		for (ll x = floor(r); x >= l && r - x <= 2; --x) {
			ans = min(ans, a[stk[i]] * n - x * f(stk[i] - 1) + x * f(n - stk[i]));
		}
	}
	for (int i = 1; i <= n; ++i) {
		ans -= a[i];
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：Meickol (赞：1)

假设构成的新数列为 $B=(B_1,B_2,\dots,B_n)$，则答案即为 $\sum \limits _{i=1}^n (B_i -A_i)$。

因为新数列构成了单调不增的等差数列，设 $d \ge 0$，有 $B_i=B_1 - (i-1) \times d$。

即答案为 $\sum \limits _{i=1}^n (B_1 - (i-1) \times d -A_i)$。

基于等差数列求和公式，整理得 $n \times B_1 - \dfrac{n(n-1)}{2}\times d - \large \sum \limits _{i=1}^nA_i $。

这时式中有两个未知数，考虑消去其中一个未知数。

对 $\forall i \in [1,n]$，有 $B_i \ge A_i$，即 $B_1 - (i-1) \times d \ge A_i$，移项得 $B_1 \ge A_i + (i-1) \times d$。

显然取等时新做题数最少，即 $B_1 = \max \limits _{i=1}^n (A_i+(i-1) \times d)$。

将 $B_1$ 代入前面答案的式子，即 $n \times \max \limits _{i=1}^n (A_i+(i-1) \times d) - \dfrac{n(n-1)}{2}\times d - \sum \limits _{i=1}^nA_i $。

令 $f(d)=n \times \max \limits _{i=1}^n (A_i+(i-1) \times d) - \dfrac{n(n-1)}{2}\times d - \sum \limits _{i=1}^nA_i $。

求导发现 $i \in [1,n]$ 时 $f'(d) \le 0$ 恒成立，即 $i \in [1,n]$ 时 $f(d)$ 单调递减。

最后使用三分法求一下函数谷值即可。



**最终代码**

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=1e5+5;
LL n;
LL sum;
LL a[N];
LL calc(LL d){
	LL b=0;
	rep(i,1,n) b=max(b,a[i]+(i-1)*d);
	return n*b-n*(n-1)/2*d-sum;
}
void solve(){
	sum=0;
	cin>>n;
	rep(i,1,n) cin>>a[i],sum+=a[i];
	LL l=0,r=1e9;
	while(l<r){
		LL m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(calc(m1)>calc(m2)) l=m1+1;
		else r=m2-1;
	}
	cout<<calc(l);
}
```

---

## 作者：MYJ_aiie (赞：0)

### [P9936 [NFLSPC #6] 等差数列](https://www.luogu.com.cn/problem/P9936)
**题意：**   
$T$ 次查询，给定一个长为 $n$ 的序列，每次可以给其中一个数加一，求让序列变成单调不增的等差序列的最小操作数。$1\leq T\leq 100$，$1\leq n, \sum n\leq 10 ^ 5$，$1\leq a_i\leq 10 ^ 9$。  
**思路：**  
简单推一下，发现公差 $d$ 和答案并不是单调的。所以看看柿子吧。  
设公差为 $d$，操作完成的序列为 $s$。那我们可以知道 $s_i\leq a_i$，同时 $s_i=s_1+(i-1)\times d$。  把第二个式子代入第一个，得到 $s_1+(i-1)\times d\leq a_i$。因为要求最小操作次数，所以 $s_1$ 越小越好，也就是 $s_1$ 为 $a_i-(i-1)\times d$ 的最大值（题总不能越做越少吧）。  
答案是什么呢？答案就是原序列变到答案序列的操作总和，也就是差值和：$ \sum\limits_{i=1}^{n}(s_i-a_i) $。因为是等差序列，再根据上面我们推出来的 $s_1$，可以得出最终答案是 $\sum\limits_{i=1}^{n}[s_1+(i-1)\times d-a_i]$。把这个式子拆开，发现是凸的。我们可以用三分来找凸函数的最值。  
**注意：** 如果你把最后的答案化简成带 $n$ 的项了，注意 $n$ 也要开 $\texttt {long long}$。  
**code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int N=1e5+5;
const ll inf9=1e9;
ll n;
ll a[N];
ll ans;
int T;
ll read(){
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
ll solve(ll x){
	ll p=0;
	for(int i=1;i<=n;i++){
		p=max(p,a[i]+(i-1)*x);
	}
	ll sum=0;
	for(int i=1;i<=n;i++){
		sum+=p-(i-1)*x-a[i];
	}
	return sum;
}
int main(){
	scanf("%d",&T);
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
		}
		ll l=0,r=inf9;
		ans=0;
		while(l<r){
			ll lo=l+(r-l)/3,rr=r-(r-l)/3;
			if(solve(lo)<=solve(rr)) 	r=rr-1;
			else l=lo+1;
		}
		printf("%lld\n",solve(l));
	} 
	return 0;
}
```

---

