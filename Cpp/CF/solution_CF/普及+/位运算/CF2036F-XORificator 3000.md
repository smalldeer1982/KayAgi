# XORificator 3000

## 题目描述

### 题面描述

多次询问，每次给定 $l,r,i,k$，求 $[l,r]$ 内所有满足 $x \not\equiv  k\pmod{2^i}$ 的 $x$ 的异或和。

## 说明/提示

保证 $1\le t\le 10^4$，$1\le l\le r\le 10^{18}$，$0\le i\le 30$，$0\le k < 2^i$。

## 样例 #1

### 输入

```
6
1 3 1 0
2 28 3 7
15 43 1 0
57 2007 1 0
1010 1993 2 2
1 1000000000 30 1543```

### 输出

```
2
2
13
0
4
1000000519```

# 题解

## 作者：Super_Cube (赞：5)

# Solution

其实是求 $\left(\displaystyle\bigoplus_{i=l}^{r}i\right)\oplus\left(\displaystyle\bigoplus_{x\equiv k\pmod {2^i},x\in[l,r]}x\right)$。

首先要了解到一个结论：$\displaystyle\bigoplus_{i=1}^{n}i=\begin{cases}1&n\bmod4=1\\n+1&n\bmod4=2\\0&n\bmod4=3\\n&n\bmod4=0\end{cases}$。

怎么证明？可以打表找到规律，也可以用数学归纳法。归纳法证明主要关注每个数的二进制表示，这里就不展开了，读者可自行尝试。

有什么用呢？异或是可以拆开的：$\displaystyle\bigoplus_{i=l}^{r}i=\left(\displaystyle\bigoplus_{i=1}^{r}i\right)\oplus\left(\displaystyle\bigoplus_{i=1}^{l-1}i\right)$。

现在就只关心后面那一大坨了。

实质上是在枚举 $k$ 在 $[l,r]$ 的超集计算异或和，那就可以把 $x$ 写成 $k+j\cdot 2^i$，其中 $j\in\left[\left\lceil\dfrac{l-k}{2^i}\right\rceil,\left\lfloor\dfrac{r-k}{2^i}\right\rfloor\right]$。

把 $x$ 的异或和拆成二进制下末尾 $i$ 位和高于 $i$ 位的两部分进行计算。由于末尾 $i$ 位全为 $k$，其异或和结果只与合法 $x$ 的个数奇偶性相关。高于 $i$ 位的部分就是 $j\cdot 2^i$ 的异或和，可以把 $2^i$ 拿到外面来乘，其实为合法 $j$ 的异或和。现在 $j$ 的范围是已知的，所以套用前面的公式也能计算出来。

# Code

```cpp
#include<bits/stdc++.h>
inline long long f(long long x){
	switch(x&3){case 0:return x;case 1:return 1;case 2:return x+1;default:return 0;}
}
long long l,r,ans;
int T,x,y;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%d%d",&l,&r,&x,&y);
		ans=f(r)^f(l-1);
		r=r-y>>x;l=(l-y-1>>x)+1;
		if(l<0)l=0;
		if(r-l+1&1)ans^=y;
		ans^=(f(r)^f(l-1))<<x;
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：Eason_cyx (赞：5)

挺有意思的，赛时吃了两发过了。

**警示后人：CF 的 C++ 17 没有 `__int128` 支持，我也不知道为啥。需要开 C++ 20。**

------

### 题意简述

给定 $l,r,i,k$，求在 $[l,r]$ 之间的所有正整数 $x$ 中，所有满足 $ x \not\equiv k (\bmod 2^i) $ 的 $x$ 异或起来的和。

### 思路

首先我们知道异或的运算律：如果 $a \operatorname*{xor} b = c$，那么有 $c \operatorname*{xor} b = a$。代入本题，$c$ 代表 $[l,r]$ 中所有正整数异或起来的值，$a$ 表示在 $[l,r]$ 之间的所有正整数 $x$ 中，所有满足 $ x \not\equiv k (\bmod 2^i) $ 的 $x$ 异或起来的和，那么 $b$ 就表示在 $[l,r]$ 之间的所有正整数 $x$ 中，所有满足 $ x \equiv k (\bmod 2^i) $ 的 $x$ 异或起来的和。显然 $b$ 更好求，那么我们可以求出 $b$ 和 $c$，就可以求出 $a$ 了。

首先看怎么求 $c$。可以利用前缀和的思想，设 $f(x)$ 表示 $1 \sim x$ 异或起来的值，则有 $c=f(r)-f(l-1)$。那么怎么求 $f$ 呢？打个表可以发现，这个东西长这样：

$$f(x) = \begin{cases}
  1 & x \bmod 4 = 1 \\
  x+1 & x \bmod 4 = 2 \\
  0 & x \bmod 4 = 3 \\
  x & x \bmod 4 = 0
\end{cases}$$

这样，$f(x)$ 显然可以 $O(1)$ 计算。

再来看 $b$。因为所有满足 $ x \equiv k (\bmod 2^i) $ 的数显然二进制的最后 $i$ 位都相同，那么如果这些数一共有奇数个，那么最后 $i$ 位就等于 $k$；否则为 $0$。那么剩下的位呢？你可以二分找到最小的使得 $L \times 2^i + k > l$ 的 $l$，以及最大的使得 $R \times 2^i + k \le r$ 的 $R$，那么这些 $x$ 除最后 $i$ 位以外剩下的位就组成了一些新的连续的数。又因为 $\operatorname*{xor}$ 表示的是**按位**异或，所以可以将这两部分分开计算。后 $i$ 位可以 $O(1)$ 计算，前 $63-i$ 位可以 $O(\log r)$ 求出左右区间后按照前面 $f$ 函数 $O(1)$ 计算。设后 $i$ 位结果为 $q$，前面 $63-i$ 位结果为 $w$，那么显然就有 $b=w\times2^i+q$。

这样就可以求出 $a$，也就是答案了。时间复杂度 $O(\log r)$，瓶颈在二分。

**注意二分边界。**

在最小情况下，也就是当 $k \ge l$ 时，此时二分的 $L$ 应当是 $0$；在最大极端情况下，可能有 $r=10^{18},i=0,k=0$ 的情况，此时右端点 $R$ 应当是 $10^{18}$。那么如果二分上界为 $10^{18}$，而 $i=30$ 时，此时最大值可能会达到 $10^{18} \times 10^9 = 10^{27}$，会炸 `long long`（此时会 `Wrong Answer On Test 5`），需要开 `__int128`。

代码很丑。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
ll xorsum(ll x) {
	if(x % 4 == 1) return 1;
	if(x % 4 == 2) return (x+1);
	if(x % 4 == 3) return 0;
	if(x % 4 == 0) return x;
}
__int128 read() {
	__int128 x = 0, w = 1; 
	char ch = 0;
	while (!isdigit(ch)) {
		if (ch == '-') w = -1;      
		ch = getchar();        
	}
	while (isdigit(ch)) { 
		x = x * 10 + (ch - '0');       
		ch = getchar();                 
	}
	return x * w;                    
}
void write(__int128 x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);       
	putchar(x % 10 + '0');      
}
int main() {
	srand(time(0));
	int t = 10000; cin >> t;
	for(int i = 1;i <= t;i++) {
		ll l = read(),r = read(),x = read(),k = read();
		ll qs = xorsum(r) ^ xorsum(l-1); 
		ll nx = 1;
		for(int i = 1;i <= x;i++) nx = nx * 2ll;
		x = nx;
		ll L = 0,R = 1e18;
		while(L < R) {
			ll mid = (L + R) >> 1;
			if((x * mid + k) >= l) R = mid;
			else L = mid+1;
		}
		ll lft = L; 
		L = 0,R = 1e18;
		while(L < (R-1)) {
			ll mid = (L + R) >> 1;
			if((x * mid + k) > r) R = mid-1;
			else L = mid;
		}
		ll rgt = ((x * R + k) <= r ? R : L); ll ans = 0;
		if(rgt == 0) {
			ans = qs ^ (k >= l && k <= r ? k : 0);
		}
		else {
			ll qian = (lft != 0 ? xorsum(rgt) ^ xorsum(lft-1) : xorsum(rgt));
			ll hou = ((rgt-lft+1) % 2 ? k : 0);
			ll cur = qian * x + hou;
			ans = qs ^ cur;
		}
		write(ans); cout << endl;
	}
	return 0;
}
```

---

## 作者：Segment_Treap (赞：3)

### $\textbf{1. Problem Statement}$
本题使用多测，共 $t$ 组数据。\
对于每一组数据，输入一行 $4$ 个整数 $l, r, n, k$，求 $(\bigoplus\limits_{l \leq x \leq r, x \not\equiv k \pmod {2^n}}x)$。\
$1 \leq t \leq 10^4$, $1 \leq l \leq r \leq 10^{18}$, $0 \leq i \leq 30$, $0 \leq k < 2^i$
### $\textbf{2. Hints}$
#### $\textbf{2.1 Hint 1}$
> 所有满足条件的数的异或和很难直接算，正难则反，可以计算所有数的异或和异或上不满足条件的数的异或和。
#### $\textbf{2.2 Hint 2}$
> 求某个区间中数的异或和，可以转换成两个前缀异或值异或起来的结果。
### $\textbf{3. Solution}$ 
在 $\textbf{2.1 Hint 1}$ 中提到：
> 所有满足条件的数的异或和很难直接算，正难则反，可以计算所有数的异或和异或上不满足条件的数的异或和。

那么可以将题目转换一下：
> $(\bigoplus\limits_{l \leq x \leq r, x \not\equiv k \pmod {2^n}}x) = (\bigoplus\limits_{x=l}^{r}x) \oplus (\bigoplus\limits_{l \leq x \leq r, x \equiv k \pmod {2^n}}x)$

在 $\textbf{2.2 Hint 2}$ 中提到：
> 求某个区间中数的异或和，可以转换成两个前缀异或值异或起来的结果。

那么可以将题目再转换一下：

> $(\bigoplus\limits_{x=l}^{r}x)=(\bigoplus\limits_{x=0}^{l-1}x) \oplus (\bigoplus\limits_{x=0}^{r}x)$\
> $(\bigoplus\limits_{l \leq x \leq r, x \equiv k \pmod {2^n}}x)=(\bigoplus\limits_{0 \leq x < l, x \equiv k \pmod {2^n}}x) \oplus (\bigoplus\limits_{0 \leq x \leq r, x \equiv k \pmod {2^n}}x)$

其中，形如 $(\bigoplus\limits_{x=0}^{p}x)$ 的式子就可以二进制拆位 $\Theta(\log w)$ 算出来。

而另一种式子形如 $(\bigoplus\limits_{0 \leq x \leq p, x \equiv k \pmod {2^n}}x)$，$x$ 的后 $n$ 位一定是 $k$，所以得数后 $n$ 位的异或值可以 $\Theta(1)$ 直接算，而除了后 $n$ 位以外的位，值是 $0 \times 2^n$, $1 \times 2^n$, $2 \times 2^n$, $3 \times 2^n \dots$ 可以发现和第一类式子类似，就是在 $(\bigoplus\limits_{x=0}^{p}x)$ 的基础上乘了一个 $2^n$，也可以 $\Theta(\log w)$ 算出来。

综上所述，单组测试时间复杂度为 $\Theta(\log w)$。
### $\textbf{4. Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long l,r,n,k,ans;
long long Xor(long long num){
	long long ret=0;
	for(long long i=0;i<=60;i++){
		long long sum=num/(1ll<<(i+1))*(1ll<<i);
		if(num/(1ll<<(i+1))*(1ll<<(i+1))+(1ll<<i)<=num){
			sum+=num-num/(1ll<<(i+1))*(1ll<<(i+1))-(1ll<<i)+1;
		}
		ret^=(1ll<<i)*(sum%2);
	}
	return ret;
}
inline void work(){
	ans=0;
	scanf("%lld%lld%lld%lld",&l,&r,&n,&k),l--;
	ans^=(Xor(l)^Xor(r));
	if(l>=k){
		l=(l-k)/(1<<n),r=(r-k)/(1<<n);
		ans^=(Xor(l)^Xor(r))*(1<<n)+((r-l)%2)*k;
	}else{
		if(r>=k){
			r=(r-k)/(1<<n);
			ans^=Xor(r)*(1<<n)+((r+1)%2)*k;
		}
	}
	printf("%lld\n",ans);
}
int main(){
	scanf("%d",&t);
	for(;t--;) work();
}
```

---

## 作者：liuChF (赞：2)

## CF2036F.XORificator 3000

比较恶心的位运算做法，每次询问复杂度 $O(1)$。

### 思路

根据异或的性质，不难想到：记函数 `query(n)` 表示 $[0,n]$ 内满足 $x\bmod 2^i =k$ 的所有 $x$ 的异或和，答案就是 `query(r) ^ query(l - 1)`。

考虑怎么求 `query(n)`，先给个例子 `n = 13, k = 3, i = 2`，不妨将 $[0,13]$ 这些数按 $i$ 分成两部分：

```cpp
	  i = 2
0	0 0 | 0 0
1	0 0 | 0 1
2	0 0 | 1 0
3	0 0 | 1 1 	✔
------------- 2 ^ i
4	0 1 | 0 0
5	0 1 | 0 1
6	0 1 | 1 0
7	0 1 | 1 1 	✔
-------------
8	1 0 | 0 0
9	1 0 | 0 1
10	1 0 | 1 0
11	1 0 | 1 1 	✔
-------------
12	1 1 | 0 0
13	1 1 | 0 1
```

打 ✔ 的是剔除的数，其他数的异或值为 $14$。记剔除的数为 $cnt$，可以得到 $cnt=\lfloor \dfrac{n}{2^i}\rfloor+[x \bmod 2^i =k]$，就是整段数量加上末尾是否有多的一小段，此时 $cnt=3$，（换成 $k=1$ 就是 $4$）。然后分左右进行计算。

记 `Xor(n)` 表示 $\oplus_{i=0}^ni$ 的值，左边一段的异或和就是 `(Xor(x) >> i) << i`，再异或上剔除的数的左部分，这部分观察一下就是 $0 \oplus 1\oplus2$，再左移 $i$ 位，两者异或一下就行了。

再考虑右部分，一样先全部异或，再剔除。全部异或的值为 `Xor(n) % (1 << i)`，剔除的异或和要么是 $k$，要么是 $0$，取决于 $cnt$ 的奇偶性。

两者相加或者异或一下就行了，因为互不相交。

### 做法

`Xor(n)` 的写法百度一下就有，或者看题解区其他题解。注意 $i=0$ 要特判。

### 代码

``` cpp
#include <bits/stdc++.h>
#define int long long
#define fq(i,d,u) for(int i(d); i <= u; ++i)
#define fr(i,u,d) for(int i(u); i >= d; --i)
using namespace std;
const int N = 1e5 + 10;
int T, l, r, i, k;
int Xor(int x) {
	int t = x & 3;
	if (t & 1) return t >> 1 ^ 1;
	return t / 2 ^ x;
}
int query(int x) {
	if (i == 0) return 0;
	int cnt = x / (1 << i), ans = Xor(x) % (1 << i);
	if (x % (1 << i) >= k) cnt++;
	if (cnt & 1) ans ^= k;
	if (!(x & 1)) ans += ((x >> i) << i);
	ans ^= (Xor(cnt - 1) << i);
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> l >> r >> i >> k;
		cout << (query(r) ^ query(l - 1)) << '\n';
	}
	return 0;
}
```

---

## 作者：KaruAWA (赞：1)

给出一种更像数数题的做法。

根据异或的特性，很容易想到容斥，将区间内所有值全部异或起来，再把不符合条件（即 $x\equiv k\pmod {2^i}$）异或一遍，就相当于没异或这些不符合条件的数。然后这种可容斥区间（即 $[l,r]$ 这一段的价值可以由若干个小区间组成）的题，一般都要容斥一下，将 $(l,r)$ 的询问变成 $(1,r)-(1,l-1)$，由于前缀的约束小于区间，所以这样肯定是好做一些的。

观察一下性质，$\bmod 2^i$ 等价于保留二进制下最低的 $i$ 位。那么一次 $(1,x)$ 的前缀查询就被转化成了两个问题：

1. $1\oplus2...x-1\oplus x$ 的值是多少。
2. 将最低的 $i$ 位改成 $k$ 的值，还有多少种方案数使得填出来的值 $\le x$。

第一问很好处理，很经典的结论是 $4i\oplus 4i+1\oplus 4i+2\oplus 4i+3 = 0$，所以只需要扫 $[x-x\bmod 4, x]$ 这一段的区间异或值即可。

第二问卡了我十年/tuu，第一次做以为是数位 dp，但是实在是大材小用了一点。将每一位分开考虑，观察一位如果取 $0$，那么肯定对最后这一位的异或值没影响，因此只考虑取 $1$ 的情况。一开始没想清楚，以为这一位取 $1$ 的方案数只取决于前面都取到上限之后，后面的方案数。虽说大致没问题，但实际忽略了很多细节，导致最后调了十年，并不是一个好习惯。因此，令这一位为 $i$，去掉后面固定的位数后还剩 $m$ 位，分类讨论一下：

1. $a_i = 1$：此时又有两种情况，分别是前 $i-1$ 位是否是贴着上限取的。如果是贴着上限取的，那么前面的方案数是 $1$，后面的方案数是 $[i+1,m]$ 组成的数再加上 $1$（后面全部取 $0$）。否则，前面的方案数是 $[1,i-1]$ 组成的数（实际上要加上 $1$ [全部取 $0$]，再减去 $1$ [不能取到上限]），后面的方案数是 $2^{m-i}$。看似好像一定是偶数对吧，但是当 $i=m$ 时，后者是个奇数，要特判一下这个情况。

2. $a_i  = 0$：此时前 $i-1$ 为必须取不到上限，即前面的方案数为 $[1,i-1]$ 组成的数（同上，实际上要减去一再加一），后面的方案数依旧是 $2^{m-i}$，特判一下即可。

但此时还有一种情况没考虑，如果在固定的位数删掉，原本的 $x$ 比 $k$ 小，那么前 $m$ 位是不能取到上限的，因此前面的分类讨论都要特判一下这种情况，奇偶性会发生改变。

最后的方案数是 $[1,m]$ 组成的数 $-$ 前 $m$ 位能否取到上限 $-$ 前 $m$ 位能否全取 $0$（即 $k$ 是否等于 $0$），如果方案数是 $0$，那么还要加上 $k$。

时间复杂度级别大概是 $O(t\log n)$，代码如下：

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 31;
const int M = 61;
int n, m;
int a[M];
ll b[M];
ll qw[M];
ll ansi;

ll query(ll x, int k) {
    if(!x) return 0;
    m = 0;
    ll tmp = x;
    while(x) {
        a[++m] = (x & 1);
        x >>= 1;
    }
    for(int i = m + 1; i <= max(m, n); ++i)
        a[i] = 0;
    m = max(m, n);
    reverse(a + 1, a + m + 1);
    x = tmp;

    ansi = 0;
    for(ll i = x - (x % 4); i <= x; ++i) ansi ^= i;
    b[m - n + 1] = 0;
    for(int i = m - n; i >= 1; --i)
        b[i] += b[i + 1] + 1ll * a[i] * qw[m - n - i];

    ll sum = 0, pre = 0;
    bool f = false;
    for(int i = m - n + 1; i <= m; ++i) pre += 1ll * a[i] * qw[m - i];
    if(pre < k) f = true;
    pre = 0;
    for(int i = 1; i <= m - n; ++i) {
        bool now = 0;
        if(a[i]) {
            if(i == m - n) {
                if(!f) now = ((pre + 1) & 1);
                else now = (pre & 1);
            }
            else {
                if(!f) now = ((b[i + 1] + 1) & 1);
                else now = (b[i + 1] & 1);
            }
        }
        else {
            if(i == m - n) 
                now = (pre & 1);
        }
        if(now)
            sum += qw[m - i];
        pre = (pre << 1) + a[i];
    }
    f ^= (b[1] & 1);
    if(k) f ^= 1;
    if(f) sum += k;
    for(int i = 1; i <= m; ++i) a[i] = b[i] = 0;
    return ansi ^ sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    qw[0] = 1;
    for(int i = 1; i <= 60; ++i) qw[i] = 1ll * qw[i - 1] * 2;
    int t;
    cin >> t;
    while(t--) {
        ll l, r;
        int k;
        cin >> l >> r >> n >> k;
        if(!n) cout << "0\n";
        else cout << (query(r, k) ^ query(l - 1, k)) << "\n";
    }
    return 0;
}
~~~

---

## 作者：Liyunze123 (赞：0)

设 $f(p)$ 为前 $p$ 个数中满足条件的数的异或和。我们求的是 $f(r)-f(l-1)$。
# 如何求 $f(p)$
可以求出 $1$ 到 $p$ 的异或和，[我的这篇题解](https://www.luogu.com.cn/article/gkpjq4k3)中有详细思路。我们可以求出不满足条件数的异或和。具体方法：求出个数，如果个数为奇则异或上 $2^i$。对小于 $2^i$ 的部分再做一次前缀异或和就可以了。

单次询问时间复杂度 $O(\log(r))$，瓶颈在前缀异或和。
```
#include<bits/stdc++.h>
using namespace std;
int q,i,k;
long long l,r;
long long f(long long r){
	long long ans=0;
	for(int w=62;w>=0;w--){
		long long h=(r+1)/(1ll<<w);
		if(h%2){if((h/2*(1ll<<w)+(r+1)%(1ll<<w))%2)ans^=(1ll<<w);}
		else if((h/2*(1ll<<w))%2)ans^=(1<<w);
	}
	return ans;
}
long long g(long long r){
	if(r<k)return f(r); 
	long long ans=f(r),p=(r-k)/(1<<i)+1;
	if(p%2)ans^=k;
	return ans^(f(p-1)<<i);
}
int main(){
	scanf("%d",&q);
	while(q--)scanf("%lld%lld%d%d",&l,&r,&i,&k),printf("%lld\n",g(r)^g(l-1));
	return 0;
}
```
代码链接[在此](https://codeforces.com/contest/2036/submission/293095361)

---

## 作者：CJ_Fu (赞：0)

## [CF2036F XORificator 3000](https://codeforces.com/problemset/problem/2036/F)

求 $[l,r]$ 中满足 $x\not\equiv k\pmod{2^i}$ 的 $x$ 的异或和。

$T\le 10^4,1\le l\le r\le 10^{18},0\le i\le 30,0\le k< 2^i$

首先由于异或满足 $a\oplus b\oplus b=a$，所以考虑拆分问题，分别求出 $[1,l-1]$ 和 $[1,r]$ 的答案再异或即可。

再考虑容斥，将区间 $[1,x]$ 的答案转化成 $[1,x]$ 所有数的异或和再异或上区间内满足 $x\equiv k\pmod{2^i}$ 的数。

对于求 $[1,x]$ 所有数的异或和，这里直接摆结论了，证明可以看 [这里](https://www.cnblogs.com/Mychael/p/8633365.html)，打表也能发现一定规律。

$$\bigoplus\limits_{i=1}^{x} i=\begin{cases}
    x&x\equiv 0\pmod{4}\\
    1&x\equiv 1\pmod{4}\\
    x+1&x\equiv 2\pmod{4}\\
    0&x\equiv 3\pmod{4}
\end{cases}$$

于是 $[1,x]$ 的异或和我们就可以 $O(1)$ 求了，接下来考虑求满足 $x\equiv k\pmod{2^i}$ 的数的异或和。

这些数二进制下的后（低位）$i$ 位都一样，为 $k$，而高位上都形如 $0\times 2^i,1\times 2^i,2\times 2^i,...,t\times 2^i$，$t$ 为 $x$ 的数量。

由于异或对于每一位的独立性，诶你发现求这一部分的异或和，是不是相当于高位求一遍 $[1,t]$ 的异或和，再异或上 $t$ 个 $k$（由于 $a\oplus a=0$，所以只用在 $t$ 为奇数的时候异或一次 $k$ 即可），时间复杂度 $O(1)$。

综上时间复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int getxor(int x){
    if(x%4==0) return x;
    if(x%4==1) return 1;
    if(x%4==2) return x+1;
    return 0;
}
int get(int x,int pos,int k){
    if(x==0) return 0;
    int t=(x>>pos);
    if(x%(1<<pos)>=k) t++;
    // t 为 [1,x] 中 mod (1<<pos) = k 的数的个数
    return getxor(x)^(getxor(t-1)<<pos)^((t&1)*k);
}
void solve(){
    int l,r,I,k;
    cin>>l>>r>>I>>k;
    cout<<(get(r,I,k)^get(l-1,I,k))<<'\n';
}
signed main(){
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2036F)

一道乱搞题。

记 $sum_1(l,r)$ 表示从 $l$ 到 $r$ 的异或和，$sum_2(l,r)$ 表示对于所有 $l\le x\le r$ 且 $x\equiv k\space(\bmod\space 2^i)$ 的异或和。

又有 $sum_1(l,r) = sum_1(1,r) \bigoplus sum_1(1,l-1)$，$sum_2(l,r)$ 同理。

$sum_1(l,r)$ 是易求的，主要来看 $sum_2(l,r)$。

在求 $sum_2(1,x)$ 时，我们假设 $x=a\times 2^i+k$，那么其在二进制下的表现形式应该是末 $i$ 位与 $k$ 相同，从末尾的 $i + 1$ 位往上与 $a$ 相同。例如 $x=3\times 2^ 2 + 1$ 的二进制形式为 $\texttt{1101}$。

我们成功的将 $x$ 拆成了末 $i$ 位和其他部分，我们令 $t = \lfloor\frac{(x + 1)}{2^i}\rfloor-1$。如果 $t \ge 0$，则末 $i$ 位会有 $t$ 个 $k$ 进行异或，末 $i+1$ 位往上是从 $1\sim t$ 异或起来，也就是 $sum_1(1,t)$。

最后 $x$ 可能还有一点残余部分，即 $x\bmod 2^i$。如果这一部分大于等于 $k$，返回答案时还要再异或上 $(t+1)\times 2^i+k$。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll T, l, r, i, k;
ll pow2[35];
ll query1(ll x) {
	if (x % 4 == 0) return x;
	if (x % 4 == 1) return 1;
	if (x % 4 == 2) return x + 1;
	return 0;
}
ll query1(ll l, ll r) { return query1(r) ^ query1(l - 1); }
ll query2(ll x) {
	ll res = 0, tmp = (x + 1) / pow2[i] - 1;
	if (tmp >= 0) {
		res = query1(tmp) << i;
		if (tmp % 2 == 0) res += k;
	}
	if ((x + 1) % pow2[i] - 1 >= k) res ^= (((x + 1) / pow2[i]) << i) + k;
	return res;
}
ll query2(ll l, ll r) { return query2(r) ^ query2(l - 1); }
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	pow2[0] = 1;
	for (int i = 1; i <= 30; i++) pow2[i] = pow2[i - 1] * 2;
	cin >> T;
	while (T--) {
		cin >> l >> r >> i >> k;
		cout << (query1(l, r) ^ query2(l, r)) << '\n';
	}
	return 0;
}
```

---

