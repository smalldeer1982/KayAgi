# Yet Another Counting Problem

## 题目描述

You are given two integers $ a $ and $ b $ , and $ q $ queries. The $ i $ -th query consists of two numbers $ l_i $ and $ r_i $ , and the answer to it is the number of integers $ x $ such that $ l_i \le x \le r_i $ , and $ ((x \bmod a)       \bmod b) \ne ((x \bmod b) \bmod a) $ . Calculate the answer for each query.

Recall that $ y \bmod z $ is the remainder of the division of $ y $ by $ z $ . For example, $ 5 \bmod 3 = 2 $ , $ 7 \bmod 8       = 7 $ , $ 9 \bmod 4 = 1 $ , $ 9 \bmod 9 = 0 $ .

## 样例 #1

### 输入

```
2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200```

### 输出

```
0 0 0 2 4 
0 91```

# 题解

## 作者：无咕_ (赞：6)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）

是否吸氧：否

不压行代码长度：29

这篇题解挺长的，慎点。

------------

## 题目大意
题面： [<传送门>](https://www.luogu.com.cn/problem/CF1342C)

题意：

------------

初始给出 $a,b$ 给出 $q$ 次询问，每次询问如下：

给出 $l,r$，求在区间 $[l,r]$ 中，有多少个数 $i$ 满足 $(i\bmod a)\bmod b\ne (i\bmod b)\bmod a$。

**有 $T$ 组询问！**

------------

~~术语理解： 小学数学，周期问题和最小公倍数。~~

## Solution

首先排除暴力，单是一组极限数据 $1\le l_i\le r_i \le 10^{18}$ 就爆了，更别说 $1\le q\le 500$ 和 $1\le T\le 100$ 了。

### Part 1 思路引入

我们先来看这个：

$$a\bmod b=(b+a)\bmod b=(2b+a)\bmod b=(3b+a)\bmod b=……=(kb+a)\bmod b$$

这证明，取模的结果是有一定规律的 ~~突然回到扩欧~~。

比如：

$$2\bmod 3=2$$


我们把 $x\bmod 3=2$ 中的 $x$ 都列出来：

$$2,5,8,11,14,17,20,……$$

我们发现，这些数之间是有一定规律的，相邻两个数的差是 $3$。

可以得出：

$$a\bmod b=(xb+a)\bmod b$$

我们把原题的式子拿过来嗷：

$$(i\bmod a)\bmod b\ne (i\bmod b)\bmod a$$

我们先处理一个：

$$(i\bmod a)\bmod b$$

$$(i\bmod a)\bmod b=((ab+i)\bmod a)\bmod b$$

我们在计算是 $a,b$ 分别会被消去，所以并无大碍。

而我们之前说过，取模的结果是有一定规律的。所以，我们可以得出这玩意：

$$(i\bmod a)\bmod b=((ab+i)\bmod a)\bmod b=((2ab+i)\bmod a)\bmod b=……=((abx+i)\bmod a)\bmod b$$

我们再把另一个式子也进行这样处理（这里不放了，与这个一样，就是把模数换了）。于是，这就成了一个周期问题。

### Part 2 周期问题

Q：这啥啊，跟这题有关联吗？

A：没关联我能放上来嘛？ ~~好像真能~~ 

我们再把刚刚求得的公式搬过来：

$$(i\bmod a)\bmod b=((ab+i)\bmod a)\bmod b=((2ab+i)\bmod a)\bmod b=……=((abx+i)\bmod a)\bmod b$$

我们发现，相邻的两个数之间的不同是 $1ab$ 。那么，我们是否可以转化成之前那样的等差数列形式呢？答案是可以的。

$$(i\bmod a)\bmod b,((ab+i)\bmod a)\bmod b,((2ab+i)\bmod a)\bmod b,……,((abx+i)\bmod a)\bmod b$$

如果抛去取模不说，相邻两个数之间的差异确实是 $1ab$。这样，不就构成了一个循环的周期（因为答案都相同）？

如果我们处理第二组中的数时，是否可以看出处理第一组中的数呢？答案是可以的。

举个取模的例子，比如 $\bmod 3$

可以轻松得出一个周期是：

$$0,1,2$$

那我们求任何一个周期中的某数时，是不是也可以从这个周期里找呢？比如我们求 $5\bmod 3$ ，我们可以知道 $5$ 在第二个周期中（因为 $\lceil \frac{5}{3}\rceil = 2$），而在第二个中多了 $5-3\times \lfloor \frac{5}{3}\rfloor =2$ 所以我们直接找第二个周期中的第二个就行。可所有周期都一样，我们也可以在第一个周期中找！

这个问题不就轻松解决了？

### Part 3 整理思路

之前我们说过了，一个周期就是 $1ab$ 。那我们只需要预处理出第一个周期，剩下的周期都迎刃而解了！

看到这种题很容易想到前缀和吧？既省时又省力。

那怎么求最小公倍数呢？

$$ab=\gcd(a,b)\operatorname{lcm}(a,b)$$

这里 $lcm$ 就是最小公倍数的意思，至于这个式子的证明……可以去学一下算数基本定理，建议直接 bdfs 。

注意！有一个坑点！最后我们在处理每对 $l,r$ 时，虽然只需要前缀和处理一下就完了，但是要注意前缀和的处理！

因为 $l,r$ 有可能不在同一个周期里，所以我们要将 $[1,l-1]$ 和 $[1,r]$ 都处理出来再相减！具体意思可以看代码里的注释。

## AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAX=40009;
typedef long long ll;
int t,q;
ll s[MAX];
ll a,b;
int gcd(int a,int b){//获取最大公因数
    return b==0?a:gcd(b,a%b);
}int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld %d",&a,&b,&q);
        ll _lcmab=a*b/gcd(a,b);//前面说过这个方法
        for(int i=1;i<=_lcmab;i++){//注意是处理到lcm(a,b)
            s[i]=s[i-1];//首先赋值过来
            if(i%a%b!=i%b%a)s[i]++;//如果符合要求就+1
        }for(int i=1;i<=q;i++){
            ll l,r;
            scanf("%lld %lld",&l,&r);
            //前面说过，要求出1到l-1和1到r的值后再相减，因为l和r可能不在一个区间中
            ll rx=(r/_lcmab)/*周期数*/*s[_lcmab]/*完整周期的计算*/+s[r%_lcmab/*剩下的数量*/]/*剩下的值（构不成周期的）*/;
            ll lx=((l-1)/_lcmab/*周期数*/)*s[_lcmab]/*完整周期计算*/+s[(l-1)%_lcmab/*剩下的数量*/]/*剩下的值*/;
            printf("%lld ",rx-lx);//输出跟空格即可
        }
    }
    return 0;
}
```

AC 记录 [<传送门>](https://www.luogu.com.cn/record/55439498)

## 类似题目

此题考查了最小公倍数和最大公约数的求法，最简单的例题：

[P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)



---

## 作者：一扶苏一 (赞：5)

## 【CF1342C】 Yet Another Counting Problem

### Analysis

对于给定的 $a, b$ 和任意正整数 $x$，显然有 

$$(((ab + x) \bmod a) \bmod b = ((x \bmod a) \bmod b)$$

$$(((ab + x) \bmod b) \bmod a = ((x \bmod b) \bmod a)$$

因此先模 $a$ 再模 $b$ 的结果和先模 $b$ 再模 $a$ 的结果是每 $ab$ 个一循环的。

一次询问可以转化成一次前缀相减的形式，即 $ans(r) - ans(l - 1)$。对于求 $ans(x)$，只需要先暴力预处理出 $0 \sim ab - 1$ 的答案并做前缀和，就可以 $O(1)$ 求了，答案即为 $\lceil\frac{x}{ab}\rceil \times \operatorname{sum}_{ab - 1} + \operatorname{sum}_{x \bmod ab}$。

时间复杂度 $O(T(ab + q))$。

### Code

```cpp
namespace Fusu {

const int maxn = 40005;

int T, x, y, q, t;
int sum[maxn];
ll l, r;

void calc();
ll query(ll u);

void Main() {
  qr(T);
  while (T--) {
    qr(x); qr(y); qr(q);
    calc();
    while (q--) {
      qr(l); qr(r);
      qw(query(r) - query(l - 1), ' ');
    }
      putchar('\n');
  }
}

void calc() {
  t = x * y;
  for (int i = 0; i < t; ++i) if ((i % x % y) != (i % y % x)) {
    sum[i] = 1;
  } else {
    sum[i] = 0;
  }
  for (int i = 1; i < t; ++i) sum[i] += sum[i - 1];
}

ll query(ll u) {
  if (u == 0) return 0;
  ll v = u / t, ret = sum[t - 1] * v;
  u -= v * t;
  return ret + sum[u];
}

} // namespace Fusu
```





---

## 作者：do_while_true (赞：3)

很容易发现 $i\bmod a\bmod b$ 和 $i\bmod b\bmod a$ 的值是循环的，两个组合在一起时，循环节的长度是 $lcm(a,b)$。所以我们预处理出这个循环节的前缀和（这里是统计前缀和是有多少满足答案的）。对于每一组 $l,r$，算出 $1$ 到 $r$ 和 $1$ 到 $l-1$ 有多少循环节，然后根据前缀和数组算出 $1$ 到 $r$ 和 $1$ 到 $l-1$ 的答案数量，相减即可。

### $\mathcal{Code:}$
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,q,T,lcm;
long long ans,l,r;
int sum[40010];
inline int gcd(int x,int y)
{
	return y==0 ? x : gcd(y,x%y);
}
long long work(long long x)
{
	long long num=x/lcm;
	return num*1ll*sum[lcm]+1ll*sum[x-num*lcm];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&a,&b,&q);
		int gccd=gcd(a,b);
		lcm=a*b/gccd;
		for(int i=1;i<=lcm;i++)
			sum[i]=sum[i-1]+(i%a%b!=i%b%a);
		while(q--)
		{
			scanf("%lld%lld",&l,&r);
			printf("%lld ",work(r)-work(l-1));
		}
	}
}
```


---

## 作者：FiraCode (赞：2)

### 题解思路：

我们就设 $a>b$。

那么当 $x<a$，那么 $x \bmod a$ 就是无效操作。

而 $x \bmod b +
\bmod a$ 中 $\bmod a$ 也是无效的。

那么 $x \bmod b = x \bmod b \bmod a$

那么 $a$ 和 $b$ 的 $\operatorname{lcm}$，若 $x \bmod\operatorname{lcm} = 0$。

那么就相当于 $x \bmod a = 0$ 并且 $x \bmod b = 0$。

当 $x = \operatorname{lcm} + 1$。

那么 $x \bmod a = 1,x \bmod b = 1$。

当 $x = \operatorname{lcm} + a - 1$。

那么 $x \bmod a = a - 1,x \bmod b = x \bmod a - 1$。

那么一般情况 $x = [k \cdot \operatorname{lcm}$ ~ $k \cdot \operatorname{lcm} + a - 1]$ 里的 $x\mod a$ 和 $x\mod b$ 是相同的，否则就是不同的。

那么对于一个区间 $[l,r]$ 我们要看这里面有多少个 $\operatorname{lcm}$，那么我们就用前缀。

那么就是 $(sum_{r \div \operatorname{lcm}} - sum_{l \div \operatorname{lcm}}) \times (\operatorname{lcm} - a)$。

但我们少加了一些值，那么我们要再加上 $r \bmod \operatorname{lcm} - a + 1$。

但 $l$ 这部分多加了，所以我们要减去 $l \bmod \operatorname{lcm} - a$。
### AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        ll a, b, q;
        cin >> a >> b >> q;
        if (a < b)
            swap(a, b);
        ll lcm = a * b / __gcd(a, b);
        ll len = lcm - a;
        while (q--)
        {
            ll ans = 0;
            ll l, r;
            cin >> l >> r;
            ll x = r / lcm - l / lcm;
            ans += x * len;
            r %= lcm;
            if (r >= a)
                ans += r - a + 1;
            l %= lcm;
            if (l > a)
                ans -= l - a;
            cout << ans << ' ';
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Echo_Long (赞：0)

### [Yet Another Counting Problem](https://www.luogu.com.cn/problem/CF1342C)

可以看出循环节为 $ab$，那么我们对于每一组数据，预处理 $\operatorname{lcm}(a,b)$ 之间的答案存在数组 $sum$ 中，用前缀和查询即可。

这里注意答案的组成：将对于 $x$ 的一次查询分成整段和散段，整段贡献为 $\frac {x} {\operatorname{lcm}(a,b)}\times sum[\operatorname{lcm}(a,b)]$，对于散段，计入答案即为 $sum[x\bmod \operatorname{lcm}(a,b)]$。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define getchar() cin.get()
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
const int N = 1e5 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int a , b , q , sum[N] , lim;

int query ( int x ) { return sum[x%lim] + sum[lim] * ( x / lim ); }

signed main ()
{
    ios::sync_with_stdio(false);
    cin.tie(0) , cout.tie(0);
    int T = read();
    while ( T -- )
    {
        a = read() , b = read() , q = read();
        lim = a * b / __gcd ( a , b );
        for ( int i = 1 ; i <= lim ; i ++ ) sum[i] = sum[i-1] + ( i % a % b != i % b % a );
        for ( int i = 1 ; i <= q ; i ++ )
        {
            int l = read() , r = read();
            cout << query(r) - query(l-1) << ' ';
        }
        cout << endl;
    }
    return 0;
}

```

### 

---

## 作者：pragma_GCC (赞：0)

# 题目大意

有$T$组数据,每组数据给定 $x$ 、$y$ 与 $q$ 个 $l$ , $r$ 。对于每个 $l$ , $r$ ,计算出 $[l,r]$ 中，有多少个数 x 满足:  

$$(x\bmod a)\bmod b ≠ (x \bmod b) \bmod a$$

# 思路

显然，对于任意的 $x$ , $a$ , $b$ ,都有:  
$$ ((k×\operatorname{lcm}(a,b)+x) \bmod a) \bmod b=(x \bmod a) $$  
所以，对于每一组数据，我们可以用 $O(\operatorname{lcm}(a,b))$ 的时间复杂度预处理每个 $\operatorname{lcm}(a,b)$ 以内的满足条件的数的个数的**前缀和**,再用 $O(1)$ 的时间复杂度回答每个问题。总时间复杂度 $O(T(\operatorname{lcm}(a,b)+q))$ 。

## AC Code
```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;
long long t,a,b,q,l,r,u,k;
long long ans[40010];
long long ji(long long g) {//时间复杂度O(1)
	long long xx=g/k*ans[k];/*计算有多少个完整的lcm(a,b)*/
	long long yy=g%k;/*处理剩余部分*/
	return xx+ans[yy];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);/*输入优化*/
	cin>>t;
	while(t--) {
		cin>>a>>b>>q;
		k=a*b/__gcd(a,b);/*求lcm(a,b)*/
		for(int i=1;i<=k;i++){
			if((i%a)%b!=(i%b)%a){
				ans[i]=ans[i-1]+1;//求前缀和
			}else{
				ans[i]=ans[i-1];
			}
		}
		while(q--) {
			cin>>l>>r;
			cout<<ji(r)-ji(l-1)<<' ';
		}
		for(int i=1;i<=k;i++){
			ans[i]=0;//清空(memset可能会超时)
		}
		cout<<'\n';
	}
   return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/122484101)

# 继续优化

在上面的代码中，总时间复杂度为 $O(T×(\operatorname{lcm}(a,b)+q))$ 。  
但我们可以把时间复杂度优化成 $O(T×q)$ 。  
可以证明：
$$ans[i] = \max(0,i-\max(a,b)+1)$$   
所以我们就可以根据这个性质进行优化。  
## AC Code
```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;
long long t,a,b,q,l,r,u,k,f;
long long ji(long long g) {
	long long xx=g/k*f;
	long long yy=g%k;
	return xx+max((long long)0,yy-max(a,b)+1);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--) {
		cin>>a>>b>>q;
		k=a*b/__gcd(a,b);//lcm()
		f=k-max(a,b);
		while(q--) {
			cin>>l>>r;
			cout<<ji(r)-ji(l-1)<<' ';
		}
		cout<<'\n';
	}
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/122482551)  
可以发现，时间被大幅度降低了。(156ms->78ms)

---

## 作者：OIer_ACMer (赞：0)

~~数学题的魅力。~~

------------
## 大致思路：
这道题耗的时间不长，主要是要知道数学运算规律。

假设 $a<b$ ,那么**一定不满足**答案要在 $0$ 到 $b - 1$ 内条件。

接着，运用我们聪明的大脑想一下，什么数在和 $a$ 和 $b$ 取模后答案在 $0$ 到 $b - 1$ 内呢？答案是**最小公倍数**加上 $1$ 到 $b - 1$ 内的数，因为我们知道，当用小于最小公倍数的数来除以 $a$ 和 $b$ 时，会出现在一次除商之后的余数小于 $a$ 或 $b$，那么答案**就一定会相等**，不符合条件。但是加上 $1$ 到 $b - 1$ 内的数也不是无缘无故的，这个原因就比较简单了，如果直接用最小公倍数来除，那么不用多想，肯定是 $0$ ~~这都不知道建议回到小学回炉重造~~。

最终，我们就可以推出这个~~垃圾~~神圣无比的公式：$k \times \operatorname{lcm(a,b)} + x$，$x$ 的值大于 $0$ 小于等于 $b - 1$。

注意，到了最大公约数后答案是成串出现的，所以可以用前缀和的方式来优化计算答案的时间复杂度。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
long long a, b, q, gbs;
long long solve(long long x)
{
    long long k = x / gbs;
    long long last = x % gbs + 1;
    return x - k * b - min(b, last);
}
signed main()
{
    int t;
    t = read();
    while (t--)
    {
        a = read();
        b = read();
        q = read();
        gbs = __gcd(a, b);
        if (a > b)
        {
            swap(b, a);
        }
        gbs = a * b / gbs;
        for (int i = 1; i <= q; i++)
        {
            int l, r;
            l = read();
            r = read();
            cout << solve(r) - solve(l - 1) << ' ';
        }
        cout << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121130666)

---

## 作者：jasonliujiahua (赞：0)

# CF1342C

[题目传送门](https://www.luogu.com.cn/problem/CF1342C)
## 题意简述：
有 $t$ 组数据，每组数据给定三个整数 $a,b,q$，进行 $q$ 次询问，每次询问给定 $l$ 和 $r$，问 $[l,r]$ 中有多少个 $x$ 满足
$$(x \bmod a) \bmod b \neq (x \bmod b)\bmod a$$

$1\le t \le 500 ,1 \le a,b \le 200 ,1\le q \le 500 ,1 \le l_i \le r_i \le 10^{18}$。
## 题目分析：
此处给出一个不同的做法。
### Step 1：
设 $[l,r]$ 中有 $res$ 个 $x$ 满足
$$(x \bmod a) \bmod b = (x \bmod b)\bmod a$$
显然答案等价于 $r-l+1-res$。于是接下来考虑怎么得出 $res$。
### Step 2：
不妨设 $a<b$，显然有：
$$(x \bmod a)=(x\bmod a)\bmod b$$
所以前面的式子变成了
$$x \bmod a = (x \bmod b)\bmod a$$
$$∴x \equiv (x \bmod b) \pmod a$$
$$∴x - (x \bmod b)\equiv 0 \pmod a$$
$$∴b\left \lfloor \frac{x}{b}\right \rfloor\equiv 0\pmod a$$
设 $d=\gcd(a,b)$，有：
$$\frac{b}{d} \left \lfloor \frac{x}{b}\right \rfloor\equiv 0 \pmod {\frac{a}{\gcd(a,d)}}$$
设 $b'=\frac{b}{d},a'=\frac{a}{d}$，显然 $a'$ 与 $b'$ 互质，且：
$$\frac{a}{\gcd(a,d)}=\frac{a}{d}=a'$$
$$∴b' \left \lfloor \frac{x}{b}\right \rfloor\equiv 0\pmod {a'}$$
$$∴\left \lfloor \frac{x}{b}\right \rfloor\equiv 0\pmod {a'}$$
接下来讨论怎么处理上式。
### Step 3：
看完题解区的其他做法后，我发现要处理 $[l,r]$ 中有多少个 $x$ 满足
$$\left \lfloor \frac{x}{b}\right \rfloor\equiv 0 \pmod {a'}$$
其实可以拆成两个区间相减，不过此情境下感觉没必要，因此还是只介绍我原来的方法。

类似于数论分块，可以发现有连续 $b$ 个 $x$ 具有相同的 $\left \lfloor \frac{x}{b}\right \rfloor$，而且这连续 $b$ 个 $x$ 的起点（小于某数的最大的 $a'b$ 的倍数）很好求，因此考虑像分块一样处理。
我们先将起点在 $[l,r]$ 内的块都算进答案里，如果左边少加了，就加回来，如果右边多加了，就减回去。
## 参考代码：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,a,b,q;
void work()
{
    if(a>b) swap(a,b);
    int d=__gcd(a,b);
    int a1=a/d;
    while(q--)
    {
        int l,r,res=0;
        cin>>l>>r;
        int x=(l/(b*a1))*b*a1;//最左边的起点
        int xx=(l/(b*a1));//最左边的起点对应的序号
        int y=(r/(b*a1))*b*a1;//最右边的起点
        int yy=(r/(b*a1));//最右边的起点对应的序号
        //先将起点在 [l,r] 内的块都算进答案里
        if(yy-xx>0) res+=(yy-xx)*b;
        //如果左边少加了，就加回来
        if(x+b-1>=l) res+=(x+b-1-l+1);
        //如果右边多加了，就减回去
        if(y+b-1>=r) res-=(y+b-1-r);
        cout<<r-l+1-res<<" ";
    }
}
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>a>>b>>q;
        work();
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：WeLikeStudying (赞：0)

一道有趣的结论题，思维难度不高。

题意：求 $x\in[l,r]$ 中 $(x\bmod a)\bmod b\neq(x\bmod b)\bmod a$ 的 x 的个数。

显然这里数字极大，枚举 x 是不行的，我们尝试从简单的结论推起。

**情况1：** a=b，显然没有不符合的，输出 0 即可。

**情况2：** a≠b，首先我们发现 x 是否满足条件的情况关于 $\operatorname{lcm}(a,b)$ 循环，所以我们先讨论 $0\leq x<\operatorname{lcm}(a,b)$ 的情况。

再给出一个很显然的式子：
$$\forall a<b,a\bmod b=a$$
那么，假设 $a<b$ (如果不满足，容易发现交换 a，b 也不影响答案）：

显然 $x\bmod a<a<b$ 。

于是我们就可以得到：
$$x\bmod a\neq(x\bmod b)\bmod a$$

然后我们大胆使用特殊值，发现在 $0\leq x<b$ 时，一定有 $x\bmod a=(x\bmod b)\bmod a$ 。

然后……似乎就没有别的情况不成立了？模糊想一下这大概是正确的，我们尝试证明：
$$\forall b\leq x<\operatorname{lcm}(a,b),x\bmod a\neq(x\bmod b)\bmod a$$
- 假设 $\exists b\leq x<\operatorname{lcm}(a,b)\,,x\bmod a=(x\bmod b)\bmod a$  。
- 则容易得到 $x\equiv x\bmod b \pmod a$ 即 $x-(x\bmod b)\equiv 0\pmod a$
- 显然 $x-(x\bmod b)\equiv 0\pmod b$ 。
- 于是我们得到 $x-(x\mod b)\equiv 0\pmod {\operatorname{lcm}(a,b)}$ ，即 $x\equiv x\mod b\pmod {\operatorname{lcm}(a,b)}$ 。
- 由于 $0\leq x\bmod b<b$ 得到 $0\leq x\bmod{\operatorname{lcm}(a,b)}<b$ ，与已知不符。
- 综上，得到 $\forall b\leq x<\operatorname{lcm}(a,b),x\bmod a\neq(x\bmod b)\bmod a$ (注意这里不含 $a<b$ 的条件)。

因此，我们只要求出了 lcm，就可以快速查询区间 $[0,n]$ 中有多少个满足条件的情况了。

由于答案具有可差分性，可以对于 $(l,r)$ 的询问，算出 $[0,r]$ 部分的答案和 $[0,l-1]$ 部分的答案，相减即可。

时间复杂度 $O(T(\log_2(\max(a,b))+q))$ ，可以通过本题。

以下是代码实现：

```cpp
//尊前不用翠眉颦，人生如逆旅，我亦是行人 
//显然a=b时输出0
//a<b时，每lcm(a,b)会有 b个违反 
#include<fstream>
using namespace std;
int T,a,b,q;
long long lcm;
long long gcd(long long a,long long b)
{
	return (!b)?a:gcd(b,a%b);
}
long long cnt(long long key)
{
	long long dis=key%lcm,pis=key/lcm;
	long long ans=pis*b;
	if(dis>=b-1)ans+=b;
	else ans+=dis+1;
	return key+1-ans;
}
int main()
{
	scanf("%d",&T);
	for(int i=0;i<T;i++)
	{
		scanf("%d%d%d",&a,&b,&q);
		if(a>b)swap(a,b);
		lcm=a/gcd(a,b)*b;
		for(int j=0;j<q;j++)
		{
			long long l,r;
			scanf("%lld%lld",&l,&r);
			printf("%lld ",cnt(r)-cnt(l-1));
		}
		printf("\n");
	}
	return 0;
}
```
在最后给出一个简单有趣的说明辗转相除求 gcd 复杂度上界的方法。
- 构造出一组数据，使得 gcd 运算 n 次才能结束，且数据参数尽可能小。
- 我们尝试贪心选取。
- 第一个数显然是 1。 
- 第二个数至少是 2，取 2，这时需要运算 1 次。
- 第三个数显然是 $a+2b$ 型，取 3，这时需要运算 2 次。
- 于是我们构造出了这样一个数列：
$$1,2,3,5,8,13,21,34,55,89,144,233,377\dots$$
- 这个数列显然是 Fibonacci 数列的一部分，其通项公式应该是：
$$\frac1{\sqrt 5}[(\frac{1+\sqrt5}2)^n-(\frac{1-\sqrt5}2)^n]$$
- n代表运算次数， 结果代表该运算次数下的极小较大参数。
- $(\frac{1-\sqrt5}2)^n$小于等于1，对整个式子影响可以忽略不计。
- 设 gcd 较大的参数为 a，有：
$$\frac1{\sqrt 5}(\frac{1+\sqrt5}2)^{n}=a$$
$$n=\log_{\frac {1+\sqrt5}2}{\sqrt 5 a}$$
- 考虑第一次的无效操作，时间复杂度上界应该是：
$$O(1+\log_{\frac {1+\sqrt5}2}{\sqrt 5 a})$$
- 也就是：
$$O(\log_2(\max(a,b)))$$

---

