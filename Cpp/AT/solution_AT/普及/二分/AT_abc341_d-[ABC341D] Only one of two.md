# [ABC341D] Only one of two

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc341/tasks/abc341_d

正整数 $ N $, $ M $, $ K $ が与えられます。ここで、$ N $ と $ M $ は異なります。  
正の整数であって、$ N $ と $ M $ のうち **ちょうど一方のみ** で割り切れる数のうち小さい方から $ K $ 番目のものを出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N,\ M\leq\ 10^8 $
- $ 1\leq\ K\leq\ 10^{10} $
- $ N\neq\ M $
- $ N $, $ M $, $ K $ は整数

### Sample Explanation 1

$ 2 $ と $ 3 $ のうちちょうど一方のみで割り切れる正整数は小さい方から順に $ 2,3,4,8,9,10,\ldots $ です。 ここで、$ 6 $ は $ 2 $ と $ 3 $ の両方で割り切れるため条件をみたさないことに注意してください。 条件をみたす正整数のうち小さい方から $ 5 $ 番目の数は $ 9 $ であるため、$ 9 $ を出力します。

### Sample Explanation 2

条件をみたす数は小さい方から順に $ 1,3,5,7,\ldots $ です。

## 样例 #1

### 输入

```
2 3 5```

### 输出

```
9```

## 样例 #2

### 输入

```
1 2 3```

### 输出

```
5```

## 样例 #3

### 输入

```
100000000 99999999 10000000000```

### 输出

```
500000002500000000```

# 题解

## 作者：cjh20090318 (赞：5)

赛后在讨论区里看到都是二分的解法？那我来补一个非二分的。

## 题意

求第 $K$ 小能整除 $N,M$ 其中**只有一个**的正整数。

## 分析

设 $L=\operatorname{lcm}(N,M)$。

我们把所有满足条件的数列出来排序，观察到 $\dfrac L N + \dfrac L M - 2$ 是一个周期。

如何证明？小于 $L$ 的 $N$ 的倍数有 $\dfrac L N -1$ 个，$M$ 的倍数有 $\dfrac L M - 1$ 个。

容易证明，相邻两个周期之间相同位置的数相差 $L$。

所以直接求出第一个周期就可以了。

时间复杂度 $O(N+M)$，最坏情况是 $\gcd(N,M)=1$，可以通过此题。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef __int128 ll;
int n,m;
LL k;
void write(const ll&x){
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
	scanf("%d%d%lld",&n,&m,&k);
	--k;
	LL lcm=(LL)n/__gcd(n,m)*m;//求出最小公倍数。
	int r=lcm/n+lcm/m-2;
	ll b=(ll)k/r*lcm;//求出这是第几个周期再加上周期相差的最小公倍数。
	k%=r;
	LL x=n,y=m;//求出最初的周期。
	for(int i=0;i<k;i++){
		if(x<y) x+=n;
		else y+=m;
	}
	write(min(x,y)+b);
	return 0;
}
```



---

## 作者：midsummer_zyl (赞：4)

总结：这次比赛还比较简单，水。

建议评黄。

**二分**大法好啊！

### 二分模版：

```cpp
LL l = 0, r = 5e18; // 赋值
while(l <= r) {
	LL mid = l + ((r - l) >> 1); 
	if(check(mid)) l = mid + 1;
	else r = mid - 1;
}
```
详见此处：[二分](https://oi-wiki.org/basic/binary/)

## 思考：

由于数据范围过大，一眼二分。

主要是 ``check`` 部分用了一小点数学，思考可知二分答案，若求得的 $sum$ 小于 $k$，移动左端点，否则移动右端点。

$sum$ 代表 $mid$ 是第 $sum$ 个满足条件的数。

下面讲求 $sum$ 的方法。

由于只能是 $n$ 或 $m$ 的倍数，那么，用[容斥原理](https://blog.csdn.net/ResumeProject/article/details/114487546)可知，当前数应是第 ``mid / n + mid / m - mid / x * 2`` 个。为什么减两倍？这是因为不能为 $n$ 和 $m$ 的公倍数。

## Code:

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n, m, k, x; 
inline LL check(LL mid) {
	LL sum = mid / n + mid / m - mid / x * 2;
	return sum < k;
}
int main() {
	scanf("%lld%lld%lld", &n, &m, &k);
//	if(n < m) swap(n, m);
	LL l = 0, r = 5e18;
	x = n * m / __gcd(n, m);
	while(l <= r) {
		LL mid = l + ((r - l) >> 1); 
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	printf("%lld", l);
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_d)

提供一种不一样的思路。

下记 $l=\operatorname{lcm}(n,m)$。

容易发现，所有满足要求的数是有周期的。$1 \sim l$ 中有 $\frac{l}{n}+\frac{l}{m}-2$ 个满足要求的数。

先把整的部分从 $k$ 中踢掉。

剩下的部分维护两个指针去算。一个表示 $n$ 的倍数，一个表示 $m$ 的倍数。

每次两个指针哪个小哪个加上 $n$ 或者 $m$，直到算到第 $k \bmod (\frac{l}{n}+\frac{l}{m}-2)$ 个为止。

注意特判一下 $k$ 能整除 $\frac{l}{n}+\frac{l}{m}-2$ 的情况。

这样做的瓶颈在于维护两个指针去算，而那部分的复杂度是 $\mathcal O(k \bmod (\frac{l}{n}+\frac{l}{m}-2))$ 的，即最坏情况下是 $\mathcal O(\frac{l}{n}+\frac{l}{m}-2)$。而这个东西最坏情况下是 $\mathcal O(n+m)$ 的，不会超时。

[code](https://atcoder.jp/contests/abc341/submissions/50368922)

---

## 作者：Shunpower (赞：2)

## Statement

给你三个整数 $n,m,k$，求所有满足能被 $n,m$ 中恰好一个整除的数中的第 $k$ 小。

$1\le n,m\le 10^8,1\le k\le 10^{10},n\neq m$。

## Solution

一个显然的想法是二分答案 $mid$，然后看有多少个 $\leq mid$ 的数满足被 $n,m$ 中恰好一个整除，调整二分上下界。

求出 $\leq mid$ 中恰好被 $n,m$ 之一整除的数是简单的：使用容斥即可得到数量是 $\left\lfloor\frac{mid}{n}\right\rfloor+\left\lfloor\frac{mid}{m}\right\rfloor-2\times \left\lfloor\frac{mid}{\text{lcm}(n,m)}\right\rfloor$

考虑答案上界应该是 $\max(n,m)k$ 的级别，但还有一些小常数，我们直接把二分右端点开到 `LONG_LONG_MAX`（也可以取 $9\times 10^{18}$）即可。

---

## 作者：xiaofu15191 (赞：2)

找规律数学题。

分组考虑，每一组的数字个数相同，容易发现每一组的数字值域为 $[x+1,x+\operatorname{lcm}(n,m)-1]$，其中 $x$ 为 $\operatorname{lcm}(n,m)$ 的倍数，且每一组的数字个数为 $(\operatorname{lcm}(n,m)/n-1)+(\operatorname{lcm}(n,m)/m-1)$。

令 $a$ 为每组的数字个数，$b=k/a$，$c=k \bmod a$，则答案为 $\operatorname{lcm}(n,m) \times b$ 之后的第 $c$ 个可行解，直接枚举即可，注意特判 $c=0$ 的情况。

时间复杂度为 $O(n+m)$，但是应该不好卡满。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long gcd(long long t1,long long t2)
{
	if(t1<t2)
	{
		long long t=t1; 
		t1=t2;
		t2=t;
	}
	if(t1==0||t2==0) return 1;
	if(t1%t2==0) return t2;
	else return gcd(t2,t1%t2);
}
long long lcm(long long t1,long long t2)
{
	return t1*t2/gcd(t1,t2);
}
int main()
{
	long long n,m,k;
	scanf("%lld%lld%lld",&n,&m,&k);
	if(n>m) swap(n,m);
	long long LCM=lcm(n,m);
	long long tmp=LCM/n-1+LCM/m-1;
	long long tmp2=k/tmp,tmp3=k%tmp;
	if(tmp3==0)
	{
		printf("%lld\n",LCM*tmp2-n);
		return 0;
	}
	long long l=tmp2*LCM+n,r=tmp2*LCM+m;
	for(long long i=1;i<=tmp3;i++)
	{
		if(l<r)
		{
			if(i==tmp3)
			{
				printf("%lld\n",l);
				break;
			}
			l+=n;
		}
		else
		{
			if(i==tmp3)
			{
				printf("%lld\n",r);
				break;
			}
			r+=m;
		}
	}
	return 0;
}
```

---

## 作者：Tou_ch (赞：1)

## 分析
首先观察到对于每个值 $x$，我们能在 $O(1)$ 时间内判断它是第几个数字：

$$ rnk = \lfloor x \div m \rfloor + \lfloor x \div n \rfloor - 2 \times \lfloor x \div h \rfloor$$

其中 $h = \operatorname{lcm}(n, m)$。

请读者自行思考为什么。

显然，答案满足单调性，考虑二分 $x$。

### 为何答案一定为 $n$ 或 $m$的倍数
由于二分查找的是“第一个满足 $check$ 的值”，因此反证法，若答案为 $ans$ 且不被 $n$ 或 $m$ 整除，那么一定存在一个值比 $ans$ 小，且满足其 $rnk$不变，与 $ans$ 为“第一个满足 $check$ 的值”的假设相矛盾。因此，二分的最后结果一定是 $n$ 或 $m$ 的倍数。

### 注意事项
记得加 `long long`。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
int n, m, k, h;

bool check(int x) {
	return (x / n) + (x / m) - 2*(x / h) >= k;
}

signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	h = n * m / __gcd(n, m);
	int l = 1, r = ~(1ll << 63);
	while(l < r) {
		int mid = l + ((r-l)>>1);
		if(check(mid)) {
			r = mid;
		} else l = mid + 1;
	}
	printf("%lld\n", l);
	return 0;
}
```




---

## 作者：Clay_L (赞：1)

### 算法分析

可以用二分找第 $k$ 个数，包含一点点容斥思想。

容易得到的，设答案为 $x$，则 $k=\lfloor\frac xn\rfloor+\lfloor\frac xm\rfloor-2\times\lfloor\frac x{\operatorname{lcm}\left(m,n\right)}\rfloor$。我们可以将这个当作 `check` 函数来二分。其中 $\operatorname{lcm}$  函数用来求最小公倍数。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=10*x+ch-'0',ch=getchar();
	return x*f;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n=read(),m=read(),k=read(),lnm=n/__gcd(n,m)*m;//lcm(x,y)=x/gcd(x,y)*y
inline int check(int x){
	return x/n+x/m-x/lnm*2;
}
inline int binans(){
	int l=1,r=1e18+10,mid;
	while(l<r){
		mid=l+r>>1;
		if(check(mid)<k)l=mid+1;
		else r=mid;
	}
	return r;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	write(binans());
	return 0;
}

```

完结撒花。

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑二分。

根据题意，我们要求仅为 $n$ 的倍数或者仅为 $m$ 的倍数的数中从小到大第 $k$ 个，很明显我们可以二分这个值。设当前二分的值为 $mid$，$n$ 与 $m$ 的最小公倍数为 $lcm$，据容斥可得满足题目条件的数的个数为 $\lfloor \frac{mid}{n} \rfloor + \lfloor \frac{mid}{m} \rfloor - 2 \times \lfloor \frac{mid}{lcm} \rfloor$。

上面是 $2 \times \lfloor \frac{mid}{lcm} \rfloor$ 的原因是 $n$ 和 $m$ 的最小公倍数在 $n$ 和 $m$ 上都有一次贡献。

```cpp
#include <bits/stdc++.h>

#define int long long
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for (int i = (int)(l); i <= (int)(r); ++ i )
#define rep1(i,l,r) for (int i = (int)(l); i >= (int)(r); -- i )
#define il inline
#define fst first
#define snd second
#define ptc putchar
#define Yes ptc('Y'),ptc('e'),ptc('s')
#define No ptc('N'),ptc('o')
#define YES ptc('Y'),ptc('E'),ptc('S')
#define NO ptc('N'),ptc('O')
#define pb emplace_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define debug() puts("------------------")

using namespace std;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
namespace szhqwq {
	template<class T> il void read(T &x) {
		x = 0; T f = 1; char ch = getchar();
		while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
		while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
		x *= f;
	}
	template<class T,class... Args> il void read(T &x,Args &...x_) { read(x); read(x_...); }
	template<class T> il void print(T x) {
		if (x < 0) ptc('-'), x = -x; 
		if (x > 9) print(x / 10); ptc(x % 10 + '0');
	}
	template<class T> il void write(T x) { print(x); ptc(' '); }
	template<class T,class... Args> il void write(T x,Args ...x_) { write(x); write(x_...); }
	template<class T,class T_> il void chmax(T &x,T_ y) { x = max(x,y); }
	template<class T,class T_> il void chmin(T &x,T_ y) { x = min(x,y); }
	template<class T,class T_,class T__> il T qmi(T a,T_ b,T__ p) {
		T res = 1; while (b) {
			if (b & 1) res = res * a % p;
			a = a * a % p; b >>= 1;
		} return res;
	}
	template<class T> il int getinv(T x,T p) { return qmi(x,p - 2,p); }
} using namespace szhqwq;
const int N = 2e5 + 10,inf = 1e9,mod = 998244353;
const ll inff = 1e18;
int n,m,k;

il void solve() {
	//------------code------------
	read(n,m,k);
	int lcm = n * m / __gcd(n,m);
	int l = 0,r = inff,res;
	while (l <= r) {
		int mid = l + r >> 1;
		int val = mid / n + mid / m - 2 * (mid / lcm);
		if (val < k) l = mid + 1,res = mid + 1;
		else r = mid - 1;
	}
	write(res);
	return ;
}

il void init() {
	return ;
}

signed main() {
	// init();
	int _ = 1;
	// read(_);
	while (_ -- ) solve();
	return 0;
}
```

---

## 作者：2huk (赞：1)

## Problem Statement

给你三个正整数 $n, m, k$。保证 $n \ne m$。

求第 $k$ 小的正整数满足它能被 $n, m$ 中的恰好一个数整除。

## Solution

首先如果 $x$ 是答案，即第 $k$ 小的满足条件的值，那么显然 $x$ 是满足 $1 \sim x$ 中有**至少** $k$ 个满足条件的数的**最小值**。

所以可以二分答案 $x$。然后问题转化成了 $1 \sim x$ 中有多少个数能被 $n, m$ 中的恰好一个数整除。

首先考虑如果问题是“能被 $n, m$ 中的任意一个数整除”怎么做。这其实就是经典容斥。

即 $a$ 表示能被 $n$ 整除的数量，$b$ 表示能被 $m$ 整除的数量，$c$ 表示能被 $n$ 整除且能被 $m$ 整除的数量。那么根据容斥原理，答案为 $a + b - c$。

由于 $n$ 的倍数会在所有正整数中每 $n$ 个数出现一次，所以不难发现 $a = \lfloor \frac xn \rfloor, b = \lfloor \frac xm \rfloor$。

同时，如果一个数被 $n$ 整除且能被 $m$ 整数，即这个数是 $n$ 的倍数也是 $m$ 的倍数，那么这个数一定是 $\operatorname{lcm}(n, m)$ 的倍数。

所以有 $c = \left \lfloor \frac x{\operatorname{lcm}(n, m)} \right \rfloor$。

那么如果有了”恰好一个数“这个条件，实际上我们只需要将上述答案再减去能被 $n$ 整除且能被 $m$ 整除的数量即可。所以答案为：
$$
\left \lfloor \frac xn \right \rfloor + \left \lfloor \frac xm \right \rfloor - 2 \times \left \lfloor \frac x{\operatorname{lcm}(n, m)} \right \rfloor
$$

## Code

```cpp
int n = read(), m = read(), k = read(), res;
int l = 1, r = 1e18, p = n * m / __gcd(n, m);
while (l <= r) {
	int mid = l + r >> 1;
	if (mid / m + mid / n - mid / p * 2 >= k) res = mid, r = mid - 1;
	else l = mid + 1;
}
wel(res);
```

---

## 作者：Genius_Star (赞：1)

### 题意：

给你三个正整数 $N$、$M$ 和 $K$。


请列出能被 $N$ 和 $M$ 中的**其中一个数**整除的第 $K$ 个正整数。

### 思路：

定义 $f(n)$ 表示 $[1,n]$ 范围内能被 $N$ 和 $M$ 中的**其中一个数**整除的个数。

根据容斥原理，应该等于范围内被 $N$ 整除的个数加上被 $M$ 整除的个数减去被 $\operatorname{lcm}(N,M)$ 整除的个数的 $2$ 倍，即：

$$f(n)=\lfloor \frac{n}{N} \rfloor + \lfloor \frac{n}{M} \rfloor - 2 \times \lfloor \frac{n}{\operatorname{lcm}(N,M)} \rfloor$$

那么二分答案即可。

时间复杂度为 $O(N \log^2 W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef double db;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,k,ans;
ll check(ll x){
	ll a=x/n,b=x/m;
	ll d=__gcd(n,m);
	ll c=n/d*m;
	c=x/c;
	return a+b-2ll*c;
}
int main(){
	n=read(),m=read(),k=read();
	check(5);
	ll l=1,r=1e18;
	while(l<r){
		ll mid=(l+r)>>1;
		if(check(mid)>=k){
			ans=mid;
			r=mid;
		}
		else
		  l=mid+1; 
	}
	write(ans);
	return 0;
}
```


---

## 作者：No_Rest (赞：1)

## 思路

很有意思的数学题。

首先考虑 $1 \sim x$ 中有多少个数满足题目条件。

显然 $1 \sim x$ 中有 $\lfloor \frac{x}{n} \rfloor$ 个 $n$ 的倍数和 $\lfloor \frac{x}{m} \rfloor$ 个 $m$ 的倍数。再考虑重复的部分，发现重复的数都是 $\mathrm {lcm}(n, m)$ 的倍数，共 $\lfloor \frac{x}{\mathrm {lcm}(n, m)} \rfloor$ 个。因为原来既算成了 $n$ 的倍数，又算成了 $m$ 的倍数，然而题目不让算，所以重复部分要减去两倍。所以 $1 \sim x$ 中共有 $\lfloor \frac{x}{n} \rfloor + \lfloor \frac{x}{m} \rfloor - 2 \times \lfloor \frac{x}{\mathrm {lcm}(n, m)} \rfloor$ 个符合题意的数。

于是就可以上二分了，上界大概为 $nk$，即 $10^{18}$，这里我保险开了 $2 \times 10^{18}$。

时间复杂度 $\mathcal O(\log nk)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf = 2e18;//上界
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll n = read(), m = read(), k = read(), lc = n * m / __gcd(n, m), l = 1, r = inf, mid, ans;
ll check(ll x){ return x / n + x / m - 2 * (x / lc); }//1 ~ x 中符合题意的数的个数
int main(){
	while(l <= r){//二分
		mid = (l + r) >> 1;
		if(check(mid) >= k) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%lld", ans);
    return 0;
}
```

---

## 作者：endswitch (赞：1)

思路：

考虑到题目所求出现了 **第 $k$** 这类字眼，所以固然是具有单调性的。于是我们想到了二分。

我们二分枚举 $x$，然后计算 $[1,x]$ 中的答案。

不难发现答案是范围中 $n,m$ 的倍数减去两倍 $\operatorname{lcm}(n,m)$ 的倍数（因为不能是 $n,m$ 的公倍数，容斥一下即得）。即：
$$\lfloor \frac{x}{n} \rfloor + \lfloor \frac{x}{m} \rfloor -2 \lfloor \frac{x}{\operatorname{lcm}(n,m)} \rfloor$$

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, l = 1, r = 4e18, lc, mid, ans;
inline bool check(int x) {return (x / n + x / m - 2 * (x / lc)) >= k;}
signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m >> k;
	lc = n * m / __gcd(n, m);
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：MorLeaves (赞：0)

## **题意：**

有三个数 $n$，$m$，$k$ ，$n$ 的倍数与 $m$ 的倍数去除 $n$ 和 $m$ 的公倍数并升序排序后得到一个数列，求出这个数列的第 $k$ 项。（$1 \le n , m \le 10^8 , 1 \le k \le 10^{10}$）

例如 $n=2 , m=3 , k=5$ ，该数列为 $2,3,4,8,9,10……$ ，则答案为 $9$ 。

## **思路：**

赛时其实也是有点靠运气，设 $p=\operatorname{lcm}(n,m)$ ，观察数列可以发现，每个 $p$ 的倍数之间间隔的数的数量是固定的，而这个固定数量其实就是 $(\frac{p}{n}+\frac{p}{m}-2)$ 。还是拿 $n=2 , m=3 , k=5$ 举例子， $p$ 显然为 $6$ ，而在数列中，$<6$ 的数有 $3$ 个， $>6$ 且 $<12$ 的数也有 $3$ 个，而 $3=(\frac{6}{2}+\frac{6}{3}-2)$，以此类推。

我们设 $x=(\frac{p}{n}+\frac{p}{m}-2)$ ，然后求出 $a_k$ 属于哪一个间隔内。设数列的第 $i$ 项为 $a_i$，若 $k \bmod x=0 $，则 $a_k=\frac{k}{x} \times p - \min\{n,m\}$ ；否则，显然有一 $a_i=\lfloor \frac{k}{x} \rfloor \times p+\min\{n,m\}$，从而 $a_k=a_{i+k \bmod x-1}$ 。

## **CODE:**

好多大佬都是用二分写的，因为蒟蒻太弱了，所以只能用这种偏暴力的做法，复杂度不是最优，最后奉上带注释的代码。

```cpp
#include<iostream>
#include<cstdio>
typedef long long ll;
using namespace std;
ll gcd(ll a,ll b) {return a%b==0?b:gcd(b,a%b);}//求 a,b 的最大公因数 
ll lcm(ll a,ll b) {return a*b/gcd(a,b);}//求 a,b 的最小公倍数，lcm(a,b)=a*b/gcd(a,b) 
int main() {
	ll n,m,k,x,y,z;
	scanf("%lld %lld %lld",&n,&m,&k);
	if (n>m) swap(n,m);//让 n 始终 < m 
	x=lcm(n,m);//求最小公倍数 
	y=x/n+x/m-2;//求“间隔”的长度 
	z=k/y*x;//求出与 a[k] 较近的 x 的倍数
	ll a=z,b=z,ans=z-n;// ans 初始为 z-n ，为了特判 k%y==0 的情况 
	for(ll i=1;i<=k%y;i++) {//往上找 a[k] 
		if (a+n<b+m) {
			a+=n;
			ans=a;
		}
		else {
			b+=m;
			ans=b;
		}
	}
	printf("%lld",ans);
	return 0;//完美结束撒花！！！ 
}
```

---

## 作者：__Dist__ (赞：0)

二分。

算是道数学题吧。简单推一下：

设 $l = \text{lcm}(n, m)$，那么有 $\lfloor {\frac{x}{l}} \rfloor$ 个不大于 $x$ 的正整数能被 $\lfloor{\frac{x}{l}}\rfloor$ 整除。因此，有 $\lfloor \frac{x}{n}\rfloor + \lfloor \frac{x}{m} \rfloor - 2\times \lfloor \frac{x}{l} \rfloor$ 个 $\le x$ 的整数可以且仅可以被 $n$ 或 $m$ 整除。

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long

using namespace std;

const int MAXN = 1e5 + 5;

ll read() {
	ll x = 0, f = 1;char ch = gt();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
	while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
	return x * f;
}

ll n, m, k;

int main() {
	n = read(), m = read(), k = read();
	ll lc = n * m / __gcd(n, m);
	ll l = 0, r = 1e18;
	while(l < r) {
		ll mid = (l + r) >> 1;
		if(mid / n + mid / m - 2 * (mid / lc) >= k) r = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```



---

## 作者：xxr___ (赞：0)

### 思路：
首先 $K$ 很大所以枚举是行不通的，因为一个数的下一个数要么比这个数符合的多要么一样多，所以是满足单调性的，遂考虑二分答案。二分 $x$ 如果这个 $x$ 符合要求那么一定是答案遂输出即可。
#### 检查函数咋写？
考虑容斥，把能被其中一个整除的和再减去能被两者的最小公倍数整除的数。
### 代码：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5+5;
#define int long long
int k,n,m;
int check(int x){
	int t=x/n+x/m-(x/(n*m/__gcd(n,m)))*2;
	if(t==k)return 1;
	if(t<k)return 2;
	return 3; 
}
signed main(){
	long long l=1,r=1e18;
	long long ans=0;
	cin>>n>>m>>k;
	while(l<=r){
		long long mid=(l+r)>>1;
		int u=check(mid);
		if(u==1&&(mid%n==0||mid%m==0)&&(mid%n+mid%m!=0)){
			cout<<mid;return 0;
		}
		else if(u==2)l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 赛时思路
找出 $n$ 和 $m$ 的最小公倍数。

然后找出最小公倍数是 $n$ 的几倍和 $m$ 的几倍，然后计算“一组”的数量，去掉重复的 $2$ 个最小公倍数，然后记录用 $k$ 可以整除“一组”的数量，然后答案加上可以整除“一组”的数量再乘上最小公倍数，然后用 $k$ 取余“一组”的数量，然后结合 $n$ 和 $m$ 的倍数，然后用一个数组存储，排序，答案加上 $a_k$，最后输出答案就可以啦，是不是非常简单~

注意：需要特判 $n$ 是 $m$ 的 $2$ 倍或 $m$ 是 $n$ 的 $2$ 倍，那么直接输出 $n\times k-m$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<int> a;
int main(){
	ll n,m,k;
	cin>>n>>m>>k;
	if(n<m) swap(n,m);
	if(m*2==n){
		cout<<n*k-m;
		return 0;
	}
	ll j=n*m/__gcd(n,m);
	ll nn=j/n,mm=j/m;
	ll sum=nn+mm-2;
	ll ans=k/sum*j;
	k%=sum;
	ll a=1;
	ll cnt=0;
	for(ll i=m; i<=j; i+=m){
		cnt++;
		if(cnt==k){
			cout<<ans+i<<endl;
			break;
		}
		if(i<=a*n&&a*n<=i+m){
			cnt++;
			if(cnt==k){
				cout<<ans+a*n<<endl;
				break;
			}
			a++;
		}
	}
	return 0;
} 
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc341_d)     
## 题意
给定 $n,m$，求第 $k$ 小的**只**能被 $n,m$ 中的一个整除的数。    
## 解法
显然，如果同时被 $n,m$ 整除，那么这个数一定是 $\operatorname{lcm}(n,m)$ 的倍数。       
那么我们又注意到：每相邻两个 $\operatorname{lcm}(n,m)$ 的倍数中间所包含的数的数量都一样，其数量为 $\dfrac{\operatorname{lcm}(n,m)}{m}+\dfrac{\operatorname{lcm}(n,m)}{n}-2$。   
这个式子不难理解：这就是一个枚举倍数的过程，只是去掉了 $\operatorname{lcm}(n,m)$。     
那么有了这个循环节，我们直接用 $k$ 对其取模，之后暴力即可。    
为什么暴力是对的？注意到这个式子的量级最大是 $2\times10^8$，$k$ 取模后就不剩太多了，所以说暴力写的好点就能过。     
~~虽然我赛时比较怂直接开了 Ofast 优化。~~    
CODE：   
```cpp
cst int N=2e6;
ll n,m,k,l,p,S,a[(N<<1)+10];
int tot;
umap<ll,bool>mp;
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<ll>();
	m=read<ll>();
	k=read<ll>();
	if(n>m){
		_swap<ll>(n,m);
	}
	l=lcm<ll>(n,m);
	p=(l/n-1+l/m-1);
	S=l*(k/p);
	k%=p;
	if(k==0){
		S-=l;
		k+=p;
	}
	ll cnt=0;
	for(ll i=1,j=1;;){
		if(i*n<j*m){
			if(i*n%m==0){
				i++;
				continue;
			}
			cnt++;
			if(cnt==k){
				write(i*n+S);
				ret 0;
			}
			i++;
		}else{
			if(j*m%n==0){
				j++;
				continue;
			}
			cnt++;
			if(cnt==k){
				write(j*m+S);
				ret 0;
			}
			j++;
		}
	}
	ret 0;
}
```


---

## 作者：I_am_kunzi (赞：0)

# AT_abc341_d 题解

### 题目翻译

给定你 $ N , M , K$，求出第 $ K $ 小的仅被 $ N $ 或 $ M $ 整除的数。

### 题目思路

本题有二分和暴力优化两种思路。

1. 二分：我们可以求出 $ N $ 和 $ M $ 的 $ \operatorname{lcm}$（最小公倍数）当做一轮，并求出每一轮中有几个数仅被 $ N $ 或 $ M $ 整除，以此求出共有几轮（需要上取整），计算出上界；下界可以取 $ 0$。随后使用二分求解。

2. 暴力优化：前半部分思路没有变化，依然是求出每一轮中有几个数仅被 $ N $ 或 $ M $ 整除，但此时我们需要轮数下取整，以此得出有几个数不满一轮，对于不满一轮的数进行暴力求解。

### 题目代码（由于较多，所以省去头文件部分）

第一个，二分版本代码。

```cpp
long long n , m , k;
bool check(long long mid)
{
	long long rd = n / __gcd(n , m) * m; // lcm，因为下面的计算中每轮会将 lcm 多算两次，因此需要减去
	long long firstans = mid / n + mid / m; // 这里每轮 n 会计算一次 lcm，m 也会计算一次，每轮共两次
	long long secondans = firstans - mid / rd * 2;
	return secondans >= k;
}
signed main()
{
	scanf("%lld%lld%lld" , &n , &m , &k);
	long long rd = n / __gcd(n , m) * m;
	long long gs = rd / n + rd / m - 2;
	long long l = 0 , r = (long long) ceil(1.0 * k / gs) * rd; // 用 lcm 和每轮中符合条件的个数，计算出上界
	long long ans = 0;
	while(l <= r)
	{
		long long mid = l + r >> 1;
		if(check(mid))
		{
			r = mid - 1;
			ans = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%lld\n" , ans);
	return 0;
}
```

第二个，暴力优化版本代码（有两个，不过大体思路相同）。

暴力优化版本 $ 1$。

```cpp
long long n , m , k;
signed main()
{
	scanf("%lld%lld%lld" , &n , &m , &k);
	if(n > m)
	{
		swap(n , m);
	}
	long long lcm = n / __gcd(n , m) * m;
	long long gs = lcm / n + lcm / m - 2;
	long long rd = k / gs;
	long long last = k % gs; // 计算出整的轮数和剩余的个数
	if(last == 0) // 没有剩余，此时就是这轮中最大的一个数，需要 - n（前面保证 n <= m，所以减去小的就剩下大的）
	{
		printf("%lld\n" , rd * lcm - n);
		return 0;
	}
	long long now1 = n , now2 = m;
	for(int i = 1 ; i <= last ; i++)
	{
		if(now1 < now2)
		{
			if(i == last)
			{
				printf("%lld\n" , rd * lcm + now1);
				break;
			}
			now1 += n;
		}
		else
		{
			if(i == last)
			{
				printf("%lld\n" , rd * lcm + now2);
				break;
			}
			now2 += m;
		}
	}
	return 0;
}
```

暴力优化版本 $ 2$。

```cpp
long long n , m , k;
signed main()
{
	scanf("%lld%lld%lld" , &n , &m , &k);
	if(n > m)
	{
		swap(n , m);
	}
	long long lcm = n / __gcd(n , m) * m;
	long long gs = lcm / n + lcm / m - 2;
	long long rd = k / gs;
	long long last = k % gs;
	if(last == 0)
	{
		printf("%lld\n" , rd * lcm - n);
		return 0;
	}
	long long now1 = n , now2 = m; // 前半部分同暴力优化版本 1
	for(int i = 1 ; i < last ; i++) // 我们通过不断交换两数，使得 now1 <= now2，所以此时需要通过取模判断应该 + n 或 + m
	{
		if(now1 % n == 0)
		{
			now1 += n;
		}
		else
		{
			now1 += m;
		}
		if(now1 > now2)
		{
			swap(now1 , now2);
		}
	}
	printf("%lld\n" , rd * lcm + now1);
	return 0;
}
```

---

## 作者：zengziqvan (赞：0)

思考发现：符合条件的数字的数量与公倍数呈周期性。

并且第 $k$ 个周期是以 $k\times\operatorname{lcm}(n,m)$ 之前的一个符合条件的数字为结尾。

每个周期的数字的数量是：

$$
\frac{\operatorname{lcm}(n,m)}{n}+\frac{\operatorname{lcm}(n,m)}{m}-2
$$

证明：

$\operatorname{lcm}(n,m)$ 之前（包括自己）$n$ 的倍数有 $\frac{\operatorname{lcm}(n,m)}{n}$ 个。

减去公倍数本身就是 $\frac{\operatorname{lcm}(n,m)}{n}-1$。

$m$ 同理，加起来即可。

不可能会有重复，若有重复则为公倍数。

证毕。

考虑二分，二分出第 $k$ 个数所在的周期之前的周期个数 $res$。

这样就可以将 $k$ 压到最小公倍数级别。

但这样还是不够，若 $n$ 和 $m$ 两者都是质数，则一个周期的大小可以达到 $n\times m$ 级别。

所以我们再次二分，二分一个 $mid$。表示小于等于 $n\times mid$ 的符合条件的数的数量。

$m$ 倍数的数量即为 $\lfloor \frac{n\times mid}{m}\rfloor$。

二分出最大的 $mid$。使小于等于 $n\times mid$ 的数的数量 $cnt\le k$。

如果 $cnt=k$，则答案为 $res\times \operatorname{lcm}(n,m)+n\times mid$。

否则答案必定不是 $n$ 的倍数。

比当前 $m$ 的倍数的排名要大 $k-cnt$ 名，所以答案即为：

$$
res\times \operatorname{lcm}(n,m)+(\lfloor \frac{n\times mid}{m}\rfloor+k-cnt)\times m
$$

时间复杂度 $\operatorname{O}(\log k)$。

```c++
#include <bits/stdc++.h>
#define ll long long
#define FOR(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
ll n,m,k,a1=1,a2=1,ans;
ll gcd(ll x,ll y) {
	return y?gcd(y,x%y):x;
}
ll lcm(ll x,ll y) {
	return x/gcd(x,y)*y;
}
int main(){
	cin>>n>>m>>k;
	if(n==2&&m==3&&k==5) cout<<"I AK IOI!";//fcx 
	ll z=lcm(n,m)/n+lcm(n,m)/m-2,l=0,res=0,r=k;
	while(l<=r) {
		ll mid=l+r>>1;
		if(mid*z<=k) {
			res=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	k-=res*z;
	if(!k) {
		cout<<(min(n,m)+lcm(n,m)*(res-1))<<"\n";
		return 0;
	}
	ll l2=1,r2=m,re2=0;
	while(l2<=r2) {
		ll mid=l2+r2>>1;
		if((mid*n)/m+mid<=k) {
			re2=mid;
			l2=mid+1;
		}
		else r2=mid-1;
	}
	if((re2*n)/m+re2==k) ans=re2*n;
	else {
		ll num=0;
		k-=((re2*n)/m+re2);
		ans=((re2*n)/m+k)*m;
	}
	cout<<(ans+lcm(n,m)*res)<<"\n";
	return 0;
}
```

---

## 作者：vectorxyz (赞：0)

#### 题目分析
这题暴力是肯定不行的，它既然说第 $k$ 个是多少，我们不如考虑二分。

二分出来的 $mid$ 就是当前的数，那么我们怎么知道他是第几个合法的数呢？

要想得到能被 $n$ 或 $m$ 整除的序列，是不是不断把 $n$ 或 $m$ 乘以一个数。我们可以用 $mid$ 除以 $n$，得到的值就是 $mid$ 在 $n$ 的公倍数的序列中是第多少个，同理，$mid$ 除以 $m$ 也是这个意思，再把他们俩相加，注意，但是题中说不能包括公倍数，加上刚才的操作公倍数算了两次，还得减去。

具体的式子看代码。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int N, M, K;
    cin >> N >> M >> K;
    int lcm = N / __gcd(N, M) * M; // 最小公倍数
    int left = 1, right = LLONG_MAX;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if ((int)mid / N + mid / M - 2 * (mid / lcm) < K) { // 当前数在序列中是第多少个
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    cout << left << endl; 

    return 0;
}
```


[记录](https://atcoder.jp/contests/abc341/submissions/50403227)。



---

## 作者：incra (赞：0)

### Solution
发现直接做很难做，想到 $[1,x]$ 中恰好是 $n$ 或 $m$ 一者的倍数的数具有单调性，考虑二分。

如何计算 $[1,x]$ 中恰好是 $n$ 或 $m$ 一者的倍数的数？可以简单容斥一下：首先 $[1,x]$ 中，有 $\left\lfloor\dfrac{x}{n}\right\rfloor$ 个数是 $n$ 的倍数，有 $\left\lfloor\dfrac{x}{m}\right\rfloor$ 个数是 $m$ 的倍数，那么我只需要减去他们共同的倍数，即删去的数 $d$ 满足 $n|d$ 且 $m|d$，显然可以推出 $\operatorname{lcm}(n,m)|d$，所以 $[1,x]$ 中有 $\left\lfloor\dfrac{x}{\operatorname{lcm}(n,m)}\right\rfloor$ 个数是 $n$ 和 $m$ 的倍数。

这 $\left\lfloor\dfrac{x}{\operatorname{lcm}(n,m)}\right\rfloor$ 个数在 $\left\lfloor\dfrac{x}{n}\right\rfloor$ 中计算了一遍，在 $\left\lfloor\dfrac{x}{m}\right\rfloor$ 中计算了一遍，所以重复的部分应该减去两遍。

于是，这题就做完了。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
LL n,m,k;
LL gcd (LL a,LL b) {
	return !b ? a : gcd (b,a % b);
}
LL lcm (LL a,LL b) {
	return a / gcd (a,b) * b;
}
LL get (LL x) {
	return x / n + x / m - x / lcm (n,m) * 2;
}
int main () {
	cin >> n >> m >> k;
	LL l = 0,r = 1e18;
	while (l < r) {
		LL mid = l + r >> 1;
		if (get (mid) >= k) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
```

---

## 作者：tder (赞：0)

令 $L=\text{lcm}(N,M)$，即 $N$ 和 $M$ 的最小公倍数。

那么，在区间 $[1,L]$ 中，恰有 $\lfloor\frac LN\rfloor-1$ 个数为 $N$ 的倍数且不为 $M$ 的倍数，有 $\lfloor\frac LM\rfloor-1$ 个数为 $M$ 的倍数且不为 $N$ 的倍数，共 $\lfloor\frac LN\rfloor+\lfloor\frac LM\rfloor-2$ 个满足条件的数。区间 $[L+1,2\times L]$ 等同理。

一般的，在区间 $[1,P]$ 中，共有 $\lfloor\frac PN\rfloor+\lfloor\frac PM\rfloor-2\times\lfloor\frac PL\rfloor$ 个满足条件的数。显然具有单调性，因此二分即可。

时间复杂度 $\log$ 级别。

---

## 作者：JuRuoOIer (赞：0)

# 题解 ABC341D Only one of two

upd：已将所有反斜杠改为双回车并检查了其它问题。再次提交审核并致歉。

upd：刚才没写完点了保存发现它自动提交了，抱歉给管理员带来不便。

### 题意

已提交翻译。

给出 $n,m,k$，求第 $k$ 小的只能被 $n,m$ 中**恰好一个**整除的正整数。

数据范围：$n,m \le 10^8,k \le 10^{10},n \ne m$。

### 做法

考虑暴力。显然枚举 $n$ 和 $m$ 的倍数 $p_1,p_2$，每次比较 $np_1$ 和 $mp_2$ 大小，然后判一下能同时被 $n,m$ 整除的就行了。时间复杂度 $O(k)$（比这个多一点）。

在 $1$ 到 $\text{lcm}(n,m)$ 中只有 $\dfrac{\text{lcm}(n,m)}{n}$ 个能被 $n$ 整除，$\dfrac{\text{lcm}(n,m)}{m}$ 个能被 $m$ 整除。

注意到同时被 $n,m$ 整除的正整数一定是 $\text{lcm}(n,m)$ 的正整数倍，因此 $1$ 到 $\text{lcm}(n,m)$ 中只有 $\text{lcm}(n,m)$ 是能同时被 $n,m$ 整除的。

也就是说，在 $1$ 到 $\text{lcm}(n,m)$ 中，能被 $n$ 整除而不能被 $m$ 整除的数有 $\dfrac{\text{lcm}(n,m)}{n}-1$ 个，能被 $m$ 整除而不能被 $n$ 整除的有 $\dfrac{\text{lcm}(n,m)}{m}-1$ 个，总共产生 $\dfrac{\text{lcm}(n,m)}{n}+\dfrac{\text{lcm}(n,m)}{m}-2$ 的贡献。而显然每个长度为 $\text{lcm}(n,m)$ 的区间都能类似地产生这么多的贡献。

设这个贡献为 $a$，那答案就是第 $\lceil\frac{k}{a}\rceil$ 个区间中第 $k\ \text{mod}\ a$ 小的符合要求的数，此时暴力就可以在不超过 $10^8$ 次枚举的情况下求出答案，足以通过本题。

```cpp
#include<iostream>
#include<cstdio>
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
ll n,m,k,p1=1,p2=1,ans;
ll lcm(ll x,ll y){
	return x*y/__gcd(x,y);
}
ll g(ll x,ll y){
	ll l=lcm(x,y);
	return l/x+l/y-2;
}
int main(){
	cin>>n>>m>>k;
	ans=k/g(n,m)*lcm(n,m);
	k%=g(n,m);
	if(k==0){
		cout<<ans-min(n,m);
		return 0;
	}
	while(--k){
		if(n*p1<m*p2)p1++;
		else p2++;
	}
	cout<<ans+min(n*p1,m*p2);
	return 0;
}
```

---

## 作者：wly09 (赞：0)

# 题意简述

给定 $N,M,K(N\not=M)$，求第 $K$ 个能被 $N,M$ 之一整除，而不能被另一个整除的数。[原题](https://www.luogu.com.cn/problem/AT_abc341_d)

## 思路

考虑到 $K$ 最大可以达到 $10^{10}$，显然 $O(K)$ 枚举是过不了的；相反，如果给定一个数，判定这个数排在第几位较易，于是考虑二分答案。

### 计算位次

对于数 $x$，在 $(0,x]$ 中有 $\lfloor\dfrac{x}{N}\rfloor$ 个 $N$ 的倍数；有 $\lfloor\dfrac{x}{M}\rfloor$ 个 $M$ 的倍数；有 $\lfloor\dfrac{x}{\operatorname{lcm}(N,M)}\rfloor$ 个数既是 $N$ 的倍数，又是 $M$ 的倍数。故 $x$ 排在第 $\lfloor\dfrac{x}{N}\rfloor+\lfloor\dfrac{x}{M}\rfloor-2\lfloor\dfrac{x}{\operatorname{lcm}(N,M)}\rfloor$ 位。

### 时间复杂度

计算位次可以在 $O(1)$ 内完成，故复杂度为 $O(\log n)$（假设在 $[0,n)$ 内二分）。

## 代码

```c++
#include <cstdint>
#include <iostream>
using namespace std;
typedef unsigned long long ull;

ull n, m, k, lcm;

ull gcd(ull a, ull b) {
    return b? gcd(b, a % b): a;
}

inline ull count(ull x) { // 计算位次
    return x / n + x / m - x / lcm * 2;
}

ull bin(ull l, ull r) { // 二分，范围为[l,r)
    ull mid;
    while (l < r) {
        mid = (l + r) >> 1;
        ull tmp = count(mid);
        if (tmp < k)
            l = mid + 1;
        else {
            // 若 (0,mid] 间恰好有 k 个数满足条件，且 mid 满足条件
            if (tmp == k && (mid % n == 0 || mid % m == 0) && mid % lcm != 0)
                return mid;
            r = mid;
        }
    }
    return -1; // 没搜到（不可能）
}

int main() {
    cin >> n >> m >> k;
    lcm = n / gcd(n, m) * m;
    cout << bin(0, UINT64_MAX); // 注意不能传(1, UINT64_MAX)
    return 0;
}
```

[评测记录](https://www.luogu.com.cn/record/147304765)

---

