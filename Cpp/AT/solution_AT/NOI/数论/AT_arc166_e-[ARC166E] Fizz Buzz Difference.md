# [ARC166E] Fizz Buzz Difference

## 题目描述

给定正整数 $n,\ a,\ b$，且满足 $a < b$。

对于满足 $1 \leq L \leq R$ 的整数对 $(L, R)$，如果满足以下条件，则称其为**良好组**：

- 在 $L$ 到 $R$ 之间的所有整数中，$a$ 的倍数的个数为 $n_a$，$b$ 的倍数的个数为 $n_b$，若 $n_a - n_b = n$，则 $(L, R)$ 为良好组。

可以证明，良好组一定存在。在所有良好组中，输出 $R-L$ 最大的那一个。如果有多个满足条件的组，则输出其中 $L$ 最小的那一个（由于 $1 \leq L$，所以一定存在 $L$ 最小的组，且答案唯一）。

给定 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 数据范围

- $1 \leq T \leq 2 \times 10^5$
- $1 \leq n \leq 10^6$
- $1 \leq a < b \leq 10^6$

### 样例解释 1

$(L, R) = (4, 35)$ 时，$n_a = 10,\ n_b = 7$，因此是良好组。其他如 $(1, 26)$、$(10, 41)$ 也是良好组。在这些组中，$(1, 26)$ 的 $R-L$ 不是最大值，所以不是答案；$(10, 41)$ 的 $R-L$ 虽然最大，但 $L$ 不是最小，所以也不是答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
3 3 5```

### 输出

```
4 35```

## 样例 #2

### 输入

```
5
4 3 5
6 2 4
1 1 2
123 456 789
9876 54 321```

### 输出

```
10 50
3 29
2 4
5473 140447
163 641411```

# 题解

## 作者：Schi2oid (赞：8)


假如找到合法区间 $[L_0,R_0]$，将 $R_0$ 不断 $-1$ 得到一系列区间，它们的 $n_a-n_b$ 取值一定恰好覆盖 $[1,n]$。因此 $n$ 是 $[1,n]$ 中限制最严格的，可以将题目限制修改为 $n_a-n_b\le n$。

那么合法的区间一定满足 $a\mid L-1,a\mid R+1$，否则可以将端点外移让区间长度变长且 $n_a-n_b$ 不会变大。设 $L=ak_1+1,R=ak_2-1(k_1<k_2)$，首先来最大化 $R-L$，即最大化 $x=k_2-k_1$。

确定 $x$ 后，$n_a=x-1$，因此只需最大化 $n_b$。一旦确定区间中第一个 $b$ 的倍数的位置 $pos$，那么 $n_b$ 也唯一确定，故只需要最小化 $pos-L$。设 $g=\gcd(a,b)$，那么 $pos-L$ 最小能恰好取到 $g-1$。因此，确定 $x$ 后可以直接求得最小可能 $n_a-n_b$，且此值关于 $x$ 具有单调性（由于 $g$ 是固定的）。直接二分 $x$ 即可。

记求得的最大 $x$ 为 $X$，此时区间内至少需要出现 $c=X-1-n$ 个 $b$ 的倍数。此限制可以表示为 $R-L-R\bmod b\ge b(c-1)$，即 $(L+aX-2)\bmod b\in[0, aX-2-b(c-1)]$，如果 $aX-2-b(c-1)\ge b$，这意味着这条限制不存在，直接令 $L=1$ 即可；否则问题可以转化成 $ak_1\bmod b\ge (1-aX)\bmod b$，求最小合法 $k_1$。这是一个经典问题，可以在 $O(\log V)$ 的时间复杂度内解决，详细做法请看：[一种欧几里得算法求解线性同余不等式](https://www.luogu.com.cn/blog/Schi2oid/yi-zhong-ou-ji-li-dei-suan-fa-qiu-xie-xian-xing-tong-yu-bu-deng-shi)。~~对，我写这篇题解就是为了推销这个的~~

总时间复杂度 $O(T\log V)$。

---

## 作者：Leasier (赞：4)

- **弱化限制。**

注意到若我们设 $f(l, r)$ 表示 $[l, r]$ 中 $a$ 的倍数减去 $b$ 的倍数的个数，$f(l, l) \in \{0, 1\}$，$|f(l, r) - f(l, r + 1)| \leq 1$。

于是我们可以将问题弱化为：

- 求区间 $[L, R]$，使得 $f(L, R) \leq n$。
- 你需要在 $R - L$ 最大的情况下最小化 $L$。

------------

首先考虑如何最大化 $R - L$。

一个显然的想法是令 $1 \leq k_1 < k_2, L = ak_1 + 1, R = ak_2 - 1$，则 $f(L, R) = (k_2 - k_1 - 1) - (\lfloor \frac{ak_2 - 1}{b} \rfloor - \lfloor \frac{ak_1}{b} \rfloor)$。

我们期待在 $p = k_2 - k_1$ 一定时，$L, R$ 中 $b$ 的倍数尽量多，这样就可以尽量合法。

令 $d = \gcd(a, b)$，则 $\lfloor \frac{ak_2 - 1}{b} \rfloor - \lfloor \frac{ak_1}{b} \rfloor \leq \lfloor \frac{ap + (b - d) - 1}{b} \rfloor$。不难发现这个上限是可以取到的：取 $(ak_1 + d) \bmod b = d$ 即可。

又因为右边那坨有单调性，于是我们二分 $p$ 即可求出 $\max(R - L) = ap - 2$。

------------

接下来考虑如何最小化 $L$，也即最小化 $k_1$。

我们期待 $\lfloor \frac{a(k_1 + p) - 1}{b} \rfloor - \lfloor \frac{ak_1}{b} \rfloor = \lfloor \frac{ap + (b - d) - 1}{b} \rfloor$。

首先判掉 $ap \bmod b \leq d$ 的情况，此时令 $k_1 = 1$ 即可。

否则，我们需要找出一个最小的 $k_1$，使得  $\displaystyle\sum_{i = 1}^{k_1} \lfloor \frac{a(i + p) - 1}{b} \rfloor - \lfloor \frac{ai}{b} \rfloor > k_1 (\lfloor \frac{ap + (b - d) - 1}{b} \rfloor - 1)$。

二分后类欧即可。

------------

综上，时间复杂度为 $O(T \log^2 w)$，其中 $w$ 为值域 $10^6$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll sum1(int n){
	return (ll)n * (n + 1) / 2;
}

ll solve(int n, int a, int b, int c){
	if (a == 0) return (ll)(n + 1) * (b / c);
	if (a >= c || b >= c) return (a / c) * sum1(n) + (ll)(n + 1) * (b / c) + solve(n, a % c, b % c, c);
	ll t = ((ll)a * n + b) / c;
	return n * t - solve(t - 1, c, c - b - 1, a);
}

int main(){
	int t;
	scanf("%d", &t);
	for (register int i = 1; i <= t; i++){
		int n, a, b, d, pos;
		ll l = 0, r = 1e12, cnt, rem;
		scanf("%d %d %d", &n, &a, &b);
		d = gcd(a, b);
		while (l <= r){
			ll mid = (l + r) >> 1;
			if ((mid - 1) - (a * mid + (b - d) - 1) / b <= n){
				l = mid + 1;
				cnt = mid;
			} else {
				r = mid - 1;
			}
		}
		rem = a * cnt % b;
		if (rem <= d){
			pos = 1;
		} else {
			int l = 0, r = 1e6;
			while (l <= r){
				int mid = (l + r) >> 1;
				if (solve(mid, a, rem - 1, b) - solve(mid, a, 0, b) > 0){
					r = mid - 1;
					pos = mid;
				} else {
					l = mid + 1;
				}
			}
		}
		printf("%lld %lld\n", (ll)a * pos + 1, a * (pos + cnt) - 1);
	}
	return 0;
}
```

---

## 作者：是青白呀 (赞：1)

注意到由于 $b>a$，因此我们在最大化 $R-L$ 的前提下，区间内两数倍数的出现次数之差一定越大越好。因此我们可以把限制设成 $a$ 的倍数比 $b$ 的倍数最多多 $n$ 个。

首先找到一个合法区间 $[L,R]$ 的必要条件：$L-1$ 和 $R+1$ 均是 $a$ 的倍数。若不是，则可以在不使答案更劣的前提下继续延长区间。不妨设 $L-1=ax$，$R+1=ay$。

其次，我们希望尽可能多地装 $b$，因此我们希望首个 $b$ 尽可能靠前。因此我们可以找到一个合法区间的充分条件：大于等于 $L$ 的下一个 $b=ax+\gcd(a,b)$。这显然是最靠前的一个 $b$ 的位置。于是可以计算出满足该前提的区间内 $b$ 的个数为：$\frac{ay-1-ax-\gcd(a,b)}{b}+1$。于是我们有如下式子需要满足：
$$
(y-x-1)-(\lfloor\frac{a(y-x)-\gcd(a,b)-1}{b}\rfloor+1)\le n
$$
注意到 $y-x$ 每次增大 $1$ 时，被减数立即增大 $1$，而减数平均每次增加 $\frac{a}b$，虽然有突变，但被减数是均匀增加，且突变值显然不超过间隔次数，故左式有单调性，二分即可求得最大的 $y-x$，也即最大的 $R-L$。

下面设 $y-x=t$。此时需要找到最小的 $x$ 使得 $[ax+1,a(x+t)-1]$ 合法。注意这里沿用 $x$ 的原因是 $L-1=ax$，$R+1=ay$ 为区间合法的必要条件。

$[ax+1,a(x+t)-1]$ 中 $b$ 的个数为 $\lfloor\frac{a(x+t)-1}{b}\rfloor-\lfloor\frac{ax}{b}\rfloor$。由于所有区间内 $b$ 的取值个数的极差不超过 $1$，故不合法时，$b$ 的个数为 $(\lfloor\frac{at-\gcd(a,b)-1}{b}\rfloor+1)-1$，我们希望找到首个合法的位置。考虑我们对每一个 $x$ 对应的 $b$ 的个数作前缀和累加，设 $f(x)=\sum_{i=0}^x\lfloor\frac{ai+at-1}{b}\rfloor-\lfloor\frac{ai}{b}\rfloor$，我们只需要找到首个 $x$ 使得 $f(x)>(x+1)\times (\lfloor\frac{at-\gcd(a,b)-1}{b}\rfloor)$ 即可，因为一个最小的合法 $x$，一定是首个对应合法 $b$ 的数量大于 $\lfloor\frac{at-\gcd(a,b)-1}{b}\rfloor$ 的位置，又因为所有 $x$ 对应的数量都不可能小于这个值，所以找到首个前缀个数和大于最低线的位置即可。

不难发现一个位置大于了，之后的所有位置都满足大于的条件，故同样可以二分解决，需要快速计算：
$$
f(x)=\sum_{i=0}^x\lfloor\frac{ai+at-1}{b}\rfloor-\lfloor\frac{ai}{b}\rfloor
$$
类欧即可。总复杂度 $O(T\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int __int128
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e5+5,mo=998244353;
void read(int &p){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    p=x*w;
}
int T;
int calc(int a,int b,int c,int n){
    if(!a)return (b/c)*(n+1);
    if(a>=c||b>=c)return (a/c)*n*(n+1)/2+(n+1)*(b/c)+calc(a%c,b%c,c,n);
    int m=(a*n+b)/c;
    return n*m-calc(c,c-b-1,a,m-1);
}
void solve(){
    int n,a,b;
    read(n),read(a),read(b);
    int gcdn=__gcd(a,b);
    int le=1,ri=(ll)1e12,t=1;
    while(le<=ri){
        int mid=(le+ri)>>1;
        if(mid-1-(a*mid-gcdn-1)/b-1<=n)le=mid+1,t=mid;
        else ri=mid-1;
    }
    le=0,ri=1e12;
    int targ=(a*t-gcdn-1)/b,ans=1e12;
    while(le<=ri){
        int mid=(le+ri)>>1;
        if(calc(a,a*t-1,b,mid)-calc(a,0,b,mid)>(mid+1)*targ)ans=mid,ri=mid-1;
        else le=mid+1;
    }
    ll l=a*ans+1,r=a*(ans+t)-1;
    printf("%lld %lld\n",l,r);
}
signed main(){
    read(T);
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc166_e)

**题目大意**

> $T$ 次询问 $n,a,b$，求 $L,R$ 使得 $[L,R]$ 中 $a$ 的倍数比 $b$ 的倍数恰好多 $n$ 个，最大化 $R-L$ 的基础上最小化 $L$。
>
> 数据范围：$T\le 2\times 10^5,n,a,b\le 10^6$。

**思路分析**

很显然把可以把原限制改成 $n_a-n_b\le n$。

那么很自然的贪心想法就是取 $L\bmod a=1,R\bmod a=-1$，那么 $L=ua+1,R=va-1$。

那么 $n_a-n_b=(v-u-1)-\left(\left\lfloor\dfrac{va-1}b\right\rfloor-\left\lfloor\dfrac{ua}b\right\rfloor\right)$，枚举 $k=v-u$，那么我们肯定想令后一部分尽可能大。

设 $r=ua\bmod b$，后一部分等于 $\dfrac{va-1-(r+ka-1)\bmod b}b-\dfrac{ua-r}b=\dfrac{ka-1+(r-(r+ka-1)\bmod b)}{b}$。

那么 $r-(r+ka-1)\bmod b$ 在 $r<b-(ka-1)\bmod b$ 时是 $-(ka-1)\bmod b$，否则是 $b-(ka-1)\bmod b$。

我们显然要让 $r\ge b-(ka-1)\bmod b$，但是注意 $r=ua\bmod b$，因此 $r$ 最大值是 $b-\gcd(a,b)$。

此时原式取得 $n_a-n_b=k-\left\lfloor\dfrac{ka-1}b\right\rfloor-[\gcd(a,b)\le (ka-1)\bmod b]$。

显然这个式子具有单调性，可以直接二分。

求出 $k$ 之后，如果 $\gcd(a,b)>(ka-1)\bmod b$ 那么直接取 $u=0$ 即可，否则我们要求最小的 $u$ 使得 $ua\bmod b\ge b-(ka-1)\bmod b$。

那么我们可以看成这样一个问题，求 $L\le xa\bmod p\le R$ 的最小自然数解：

> 首先如果 $l=0$ 直接解决。
>
> 其次如果 $[l,r]$ 中有 $a$ 倍数，即 $a\left\lceil \dfrac la\right\rceil\le r$ 那么 $x_{\min}=\left\lceil \dfrac la\right\rceil$。
>
> 否则设 $k=\left\lfloor\dfrac{xa}p\right\rfloor$，我们只需最小化 $k$，此时 $x\ge \left\lfloor\dfrac{kp+l}a\right\rfloor$。
>
> 那么 $l\le ax-kp\le r$ 可以推出$ax-r\le kp\le ax-l$，进一步得到 $(-r)\bmod a\le kp\bmod a\le (-l)\bmod a$，可以递归处理。
>
> 注意到每次递归都会使得 $(a,p)\gets (p\bmod a,a)$，因此复杂度同辗转相除法。

时间复杂度 $\mathcal O(T\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e12;
ll solve(ll l,ll r,ll a,ll p) { //ax mod p in [l,r]
	if(!l) return 0;
	if((l+a-1)/a*a<=r) return (l+a-1)/a;
	// l <= ax-kp <= r
	// x >= (kp+l)/a
	// -r%a <= pk%a <= -l%a
	ll k=solve((a-r%a)%a,(a-l%a)%a,p%a,a);
	return (k*p+l+a-1)/a;
}
signed main() {
	int T;
	scanf("%d",&T);
	for(ll a,b,n;T--;) {
		scanf("%lld%lld%lld",&n,&a,&b);
		ll L=0,R=inf,g=0,d=__gcd(a,b);
		while(L<=R) {
			ll mid=(L+R)>>1;
			if((mid-1)-(a*mid-1)/b-(d<=(a*mid-1)%b)<=n) g=mid,L=mid+1;
			else R=mid-1;
		}
		ll k=(d<=(a*g-1)%b)?solve((b-(a*g-1)%b)%b,b-1,a,b):0;
		printf("%lld %lld\n",a*k+1,a*(k+g)-1);
	}
	return 0;
}
```

---

