# MOD - Power Modulo Inverted

## 题目描述

Given 3 positive integers _x_, _y_ and _z_, you can find _k = x $ ^{y} $ %z_ easily, by fast power-modulo algorithm. Now your task is the inverse of this algorithm. Given 3 positive integers _x_, _z_ and _k_, find the smallest non-negative integer _y_, such that _k%z = x $ ^{y} $ %z_.

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0```

### 输出

```
9
No Solution```

# 题解

## 作者：i207M (赞：9)

## 简介

$ A^x=B(mod C) $ 已知ABC，求x；

如果互质 $ O(sqrt(phi(C)) $ 大步小步算法（分块）

## 方法

![](https://cdn.luogu.com.cn/upload/pic/28471.png)

先利用剩余系的性质，提出几个A，约去约数，使AC互质；

假设提出了k个A，因为要求最小正整数解，ans-k可能为负数，被舍去，所以暴力判断[0,k]；

先判特解：B==1，则x==0；

注意判无解：B不能整除gcd(A,C)（一定要在上一步之后）；

然后由欧拉定理可知，答案在[0,phi(c))之间，所以分块，一块一块用map判断；

## 注意事项

**WTF**，调了一晚上；

1.一定要把
```
(b *= inv(a2, c)) %= c;
    if (b == 1) {
        ans = k;
        return 1;
    }
```
放在它的前边：
```
if (b % gcd(a, c))  return 0;
```

因为当b==1时的情况要提前特判；

2.此题卡常，必须用扩展欧几里得；

3.一定要记得每次清空block；

## 代码


```cpp
//%:pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
il char gc() {
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define int ll
il int getphi(int x) {
    int res = 1;
    for (int i = 2, mi = sqrt(x); i <= mi; ++i)
        if (x % i == 0) {
            res *= i - 1, x /= i;
            while (x % i == 0) res *= i, x /= i;
        }
    if (x > 1) res *= x - 1;
    return res;
}
il int qpow(int a, int b, int md) {  // calc a^b%md
    int ret = 1;
    for (; b; b >>= 1, (a *= a) %= md) if (b & 1) (ret *= a) %= md;
    return ret;
}
il void exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
il int inv(int a, int md) {
    int x, y;
    exgcd(a, md, x, y);
    return x < 0 ? x + md : x;
}
il int gcd(ri a, ri b) {
    ri t;
    while (b) {
        t = a, a = b, b = t % a;
    }
    return a;
}
#define N 100000
map<int, int>block;
il bool bigsmall(int a, int b, int c, int &ans) { // calc a^x==b(mod c)
    int k = 0, a2 = 1, bb = b, cc = c;
    ri t;
    while ((t = gcd(a, c)) > 1 && !(b % t)) {
        b /= t, c /= t, ++k, (a2 *= a / t) %= c;
    }
    (b *= inv(a2, c)) %= c;
    if (b == 1) {
        ans = k;
        return 1;
    }
    if (b % gcd(a, c))  return 0;
    t = 1;
    for (ri i = 0; i <= k; ++i, (t *= a) %= cc) {
        if (t == bb) {
            ans = i;
            return 1;
        }
    }
    ri sq = (int)ceil(sqrt((double)getphi(c)));
    t = 1;
    for (ri i = 0; i <= sq; ++i, (t *= a) %= c)
        if (!block.count(t)) block[t] = i;
    for (ri i = 0, pow = qpow(a, sq, c), ta = 1; i <= sq; ++i, (ta *= pow) %= c) {
        if (block.count(t = (b * inv(ta, c) % c))) {
            ans = i * sq + block[t] + k;
            return 1;
        }
    }
    return 0;
}
int a, b, c, ans;
signed main() {
    while (in(a), in(c), in(b), a || b || c) {
        b %= c;
        if (bigsmall(a, b, c, ans)) printf("%lld\n", ans);
        else puts("No Solution");
        block.clear();
    }
    return 0;
}

```

---

## 作者：ioker (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/SP3105)

## 题目大意：
给出 $n,m,p$,求出关于 $x$ 的方程的最小解：$n^x\equiv m\pmod p$

### 坑点：
1. 多组数据
2. 要开 ```long long```
3. 一些奇怪的特判
4. $n$ 与 $p$ 并不互质

OI Wiki 上的 [BSGS](https://oi-wiki.net/math/number-theory/bsgs/) 讲得很清楚，认真看看就会这题的基础思路了，但是 $n$ 与 $p$ 并不互质，不能保证 $n$ 存在模 $p$ 意义下的逆元，那么我们就让 $n$ 与 $p$ 互质([exBSGS](https://oi-wiki.net/math/number-theory/bsgs/#_8))

明白了方法，代码也好实现，至于 ```map```，我用的是 ```unordered_map```，何必加一个 $\text{log}$ 呢？

```cpp
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <unordered_map>
namespace stream {
template <typename T> inline T read() {
    T n = 0, m = 0;
    char c = getchar();

    while (!isdigit(c)) {
        m |= c == '-';
        c = getchar();
    }

    while (isdigit(c)) {
        n = (n << 1) + (n << 3) + c - '0';
        c = getchar();
    }

    return m ? -n : n;
}
template <typename T> inline void write(T n, char c) {
    int tot = 0, a[101];

    if (n < 0)
        n = -n, putchar('-');

    while (n)
        a[++tot] = n % 10, n /= 10;

    if (!tot)
        putchar('0');

    while (tot)
        putchar(a[tot--] + 48);

    if (c)
        putchar(c);
}
template <typename T> inline void print(T n, char c) {
    printf("%d", n);

    if (c)
        putchar(c);
}
}
using namespace stream;
#define read read<int>()
#define int long long//开 long long 类型
int n, m, p;
int power(int n, int m, int p) {
    int ans = 1;

    while (m) {
        if (m & 1)
            ans = ans * n % p;

        m >>= 1;
        n = n * n % p;
    }

    return ans;
}
int gcd(int n, int m) {
    return !m ? n : gcd(m, n % m);
}
void exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }

    exgcd(b, a % b, x, y);
    int t = x;
    x = y, y = t - a / b * y;
}
int exBSGS(int n, int m, int p) {
    if (m == 1 || p == 1)
        return 0;//特殊情况

    int z = 1, sum = 0, x, y;

    while (1) {
        int d = gcd(n, p);

        if (d == 1)
            break;

        if (m % d)
            return -1;

        m /= d, p /= d, z = 1ll * z * n / d % p, sum++;

        if (z == m)
            return sum;
    }

    exgcd(z, p, x, y);
    m = 1ll * m * ((x % p + p) % p) % p, n %= p;
    std::unordered_map<int, int> mp;
    int t = ceil(sqrt(p)), c = 1;

    for (int i = 0; i < t; i++)
        mp[1ll * m * c % p] = i, c = c * n % p;

    n = c, c = 1;

    for (int i = 1; i <= t; i++) {
        c = 1ll * c * n % p;
        int x = c;

        if (mp.find(x) != mp.end())//等价于 mp[x]!=0，但速度似乎更快
            return i * t - mp[x] + sum;
    }

    return -1;
}
signed main() {
    while (scanf("%lld%lld%lld", &n, &p, &m)) {//多组数据
        if (!p && !n && !m)
            return 0;

        int k = exBSGS(n, m, p);

        if (k == -1)
            puts("No Solution");
        else
            write<int>(k, 10);
    }

    return 0;
}
```

---

## 作者：chzhc (赞：4)

可以到[我的博客](https://www.cnblogs.com/chzhc-/p/13572209.html)里查看，体验可能更好点？

我们需要解决 $a^x \equiv b \ (\bmod \ M)$ 的一个解 $x$。其中 $a, p$ 互质。

首先，如果有解，那么解一定在 $[0, p]$ 这个区间内，根据抽屉原理，$a^x \bmod p$ 只会有 $p - 1$ 个取值，故 $[0, p]$ 中至少会存在两个相同余数的数，即一定存在一对 $i, j$ 满足 $a^i\equiv a^j \ (\bmod \ M)$，那么在 $i$ 之后，$a^i \bmod \ M, a^{i + 1} \bmod \ M, \cdots a^{j} \bmod \ M$ 这些数会循环出现，故如果有解，那么解一定在 $[0, p]$ 这个区间内。

我们考虑把 $x$ 进行拆分，$x=qm-p$，其中 $m=\left\lfloor\sqrt{x}\right\rfloor+1$，$q \in [1, m]$，$p \in [0, m]$。

显然，$qm-p$ 可以表示出 $0 \sim m$ 中的所有数。

我们把原式修改一下得到 $a^{qm-p} \equiv b \ (\bmod \ M)$，$a^{qm} \equiv b \times a^{p} \ (\bmod \ M)$

我们发现 $q$ 与 $p$ 没有关系了，考虑先 $O(\sqrt{x})$ 枚举 $p$，把 $(b \times a^p) \bmod M$ 放入哈希表（map 也行），然后再 $O(\sqrt{x})$ 枚举 $a^{qm}$，找到最小的 $q$ 满足 $a^{qm} \bmod M$ 在哈希表中出现过，那么 $qm+p$ 就是最小的答案。

[code](https://paste.ubuntu.com/p/GvSY5FGCCW/)

扩展 BSGS

我们要解决的还是 $a^x\equiv b \ (\bmod \ p)$ 这个问题，只是不满足 $a$ 与 $p$ 互质。

若 $a$ 与 $p$ 互质，那么就会存在逆元，可以将 $x$ 分解为 $qm - p$ 来求解，所以我们要想办法让 $a, p$ 变得互质。

我们考虑把这个式子转化为不定方程，$a^x -yp = b$，首先，我们求出 $d_1=\gcd(a, p)$，然后整个式子都除以 $d_1$，若 $b$ 与 $d_1$ 互质，那么就无解，否则我们继续求出 $d2=\gcd(a, p)$，一直进行下去，直到 $a$ 与 $p$ 互质。

假设进行了 $k$ 次，最后得到式子就是 $\dfrac{a^k}{\prod\limits_{i=1}^{k}d_i}\times a^{x-k}-\dfrac{yp}{\prod\limits_{i=1}^{k}d_i}=\dfrac{b}{\prod\limits_{i=1}^{k}d_i}$，其中 $a$ 与 $p$ 互质。

我们再化为同余方程的形式，$\dfrac{a^k}{\prod\limits_{i=1}^{k}d_i}\times a^{x-k}\equiv \dfrac{b}{\prod\limits_{i=1}^{k}d_i} \ (\bmod \dfrac{p}{\prod\limits_{i=1}^{k}d_i})$，显然，求出 $\dfrac{a^k}{\prod\limits_{i=1}^{k}d_i}$ 的逆元，然后直接移到右边，直接用 BSGS 来解决，然后最后把答案加上 $k$ 即可。

注意，不保证答案小于 $k$ 的情况，故在消因子前做一下 $O(k)$ 枚举，直接验证 $a^i \equiv b \ (\bmod \ p)$，就能避免这种情况。

[code](https://paste.ubuntu.com/p/7MTXR7vn2p/)

---

## 作者：liuyifan (赞：4)

## [P4195双倍经验](https://www.luogu.org/problemnew/show/P4195)

刚学完EXBSGS,来发篇题解

似乎不需要[楼下](https://www.luogu.org/blog/i207M/tai-bu-xiao-bu-suan-fa-mu-ban-sp3105-post)这么复杂的写法,可以不用求逆元,直接递归分块后BSGS即可,时间复杂度O(logn*BSGS)

极限卡常code:（注释见下）
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register卡常
#define ll long long
using namespace std;
ll a,p,b;
inline ll cal(reg ll a,reg ll b,reg ll p)
{
	return a*b%p;//计算
}//inline内联函数卡常
inline ll exbsgs(reg ll x,reg ll y,reg ll p)
{
 	unordered_map<ll,ll>h;//unordered_map理论更快(自带哈希)
    //仅支持C++11及以上，NOIP慎用
    //理论上局部变量比全局变量快
	reg ll cnt=0,d,k=1,t,tt=1;
	if(y==1)return 0;
    while((d=__gcd(x,p))^1)
    //c++异或(^)法则:0^0=0,0^1=1,1^0=1,1^1=0(可以理解为不进位二进制加法)
    {
        if(y%d!=0)return -1;
        y/=d;
		p/=d;
		cnt++;
        k=cal(k,x/d,p);
        if(k==y)return cnt;
    }//分块
    t=sqrt(p)+1;
    h.clear();//操作同map
    for(reg ll i=0;i<t;i++)
    {
        h[cal(tt,y,p)]=i;
        tt=cal(tt,x,p);
    }
    k=cal(k,tt,p);
    for(reg ll i=1;i<=t;i++)//BSGS
    {
        if(h.find(k)!=h.end())return i*t-h[k]+cnt;//找到解,返回
        //find:找到的位置,end:结尾
        k=cal(k,tt,p);
    }
    return -1;//无解情况,返回-1
}
int main()
{
	while(scanf("%lld%lld%lld",&a,&p,&b)==3&&a&&b&&p)~exbsgs(a,b,p)?printf("%lld",exbsgs(a,b,p)):put("No Solution");
	//~：c++二进制按位取反(~0=1,~1=0)
	//main内极致压行
    return 0;
}
```
## 拒绝抄袭,共建和谐洛谷

---

## 作者：Morax_ (赞：1)

# [SP3105 MOD - Power Modulo Inverted](https://www.luogu.com.cn/problem/SP3105) 题解

这题是非常明显的 [exBSGS 的板子](https://www.luogu.com.cn/problem/P4195)，直接套就行。

[OI-wiki](https://oi-wiki.org/math/number-theory/bsgs/#%E6%89%A9%E5%B1%95%E7%AF%87) 上讲解得很详细，我就简单说说。

~~如果连 BSGS 都不会就算了吧。~~

BSGS 解决的是这样的问题：给定整数 $a,b,p$，其中 $a,p$ 互质，求方程 $a^x\equiv b(mod\ p)$ 的最小整数解 $x$。

我们设 $x=i\times m-j,m=\lceil\sqrt p\rceil,1\le i,j\le m$。

因此，将方程变为 $a^{i\times m-j}\equiv b\pmod {p}$。

然后，再转化成 $a^{i\times m}\equiv b\times a^j\pmod {p}$。

这时再把 $a^{i\times m}$ 和 $b\times a^j$ 预处理一下放在哈希表里就可以了。

但是，exBSGS 中，$a,p$ 不互质，所以我们要转换一下。

设 $d=gcd(a,p)$ ，那么方程可以变为 $\frac{a^x}{d}\equiv \frac{b}{d}\pmod {\frac{p}{d}}$。

此时的无解的情况就是 $d\not\mid b$ 且 $b\not=1$。

然后重复以上过程 $k$ 次，直到 $a,\frac{p}{d}$ 互质。

所以原式可以写成以下形式：

$a^{x-k}\equiv \frac{b}{\prod^k_{i=1}g\times\prod^k_{i=1}\frac{a}{d_i}}\pmod {\frac{p}{\prod^k_{i=1}d}}$

然后就可以用 BSGS 求解了。

注意因为在化简过程中的 $a,p$ 不互质，不可以使用费马小定理求逆元。

还有，如果你在 BSGS 中使用了 C++ 自带的 map 的话可能会被卡，但是你可以试试下面的方式，具体看代码。

## Code

```c++
#include <stdio.h>
#include <math.h>
#include <ext/pb_ds/assoc_container.hpp>//哈希表的头文件

using namespace __gnu_pbds;
gp_hash_table <long long, long long> f;//哈希表，用法和map一样的

inline long long gcd (register long long a, register long long b) {
    long long i = a % b;
    for (; i != 0; a = b, b = i, i = a % b) ;
    return b;
}//gcd

inline void exgcd (register long long a, register long long b, register long long &x, register long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd (b, a % b, x, y);
    long long tx = x;
    x = y; 
    y = tx - a / b * y;
}//exgcd

inline long long inv (register long long a, register long long b) {
    register long long x, y;
    exgcd (a, b, x, y);
    return (x % b + b) % b;
}//exgcd求逆元

inline long long power (register long long a, register long long b, register long long p) {
    register long long ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % p;
        b >>= 1;
        a = (a * a) % p;
    }
    return ans % p;
}//快速幂

inline long long bsgs (register long long a, register long long b, register long long p) {
    f.clear ();
    register long long m = ceil (sqrt (p));
    b %= p;
    for (register long long i = 1; i <= m; i ++) {
        b = b * a % p;
        f [b] = i;
    }
    register long long tmp = power (a, m, p);
    b = 1;
    for (register long long i = 1; i <= m; i ++) {
        b = b * tmp % p;
        if (f [b]) return(i * m - f [b] + p) % p;
    }
    return -1;
}//bsgs
inline long long exbsgs (register long long a, register long long b, register long long p) {
    if (b == 1 || p == 1) return 0;//特判，此时最优解为0
    register long long g = gcd (a, p), k = 0, na = 1;
    while (g > 1) {
        if (b % g != 0) return -1;
        k ++;
        b /= g;
        p /= g;
        na = na * (a / g) % p;
        if (na == b) return k;
        g = gcd (a, p);
    }
    register long long f = bsgs (a, b * inv (na, p) % p, p);
    if (f == -1) return-1;
    return f + k;
}//exbsgs

int main () {
    long long a, p, b;
    while (scanf("%lld%lld%lld", &a, &p, &b) && a && b && p) {
        a %= p; 
        b %= p;
        register long long t = exbsgs (a, b, p);
        if (t == -1) printf("No Solution\n");
        else printf("%lld\n", t);
    }
}
```

---

完！

点个赞吧！


---

## 作者：月下萤火 (赞：1)

### 题意
求最小的 $y$ 使得 $z\equiv y^{x}\left ( mod\ p \right )$  
无解则输出 "No Solution"  
注意与题目的 $x,y,k$ 一一对应
### 思路
很明显，这题考察的内容是 $BSGS$ ，但是没有限定 $p$ 为质数，所以我们考虑拓展  $BSGS$ 的实现

步骤如下:
- 改写方程为等式形式  
$   $  

$\ \ \ \ \ \ \ \ \ \ \ \ \ \  \ \ \ \ \ \ y^{x}+kp=z$
$   $  
- 由于$z$必须为 $gcd(y,p)$ 的倍数，于是等式左右同除以 $gcd(y,p)$ ，如下:  
$   $  

$\ \ \ \ \ \ \ \ \ \ \ \ \ \  \ \ \ \frac{y}{gcd\left ( y,p \right )}y^{x-1}+k\frac{p}{gcd\left ( y,p \right )}=\frac{z}{gcd\left ( y,p \right )}$  
$   $  

- 不断检查 $gcd\left ( \frac{z}{d} ,y\right )$ ，一直除到互质为止，结果如下:  
$   $

$\ \ \ \ \ \ \ \ \ \ \ \ \ \  \ \frac{y^{k}}{gcd\left ( y,p \right )}y^{x-k}=\frac{z}{gcd(y,p)}\left ( mod\ \frac{p}{d} \right )$  
$   $  

- 最后利用 $BSGS$ 求解即可  

### 代码
```c
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

int x,z,k;

int qpow(int a,int b,int mod){
	int res=1;
	while(b){
		if(b&1)	res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return res;
}

int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}

const int HashMod=100007;

struct HashTable{
	struct Line{int u,v,next;}e[100000];
	int h[HashMod],cnt;
	void Add(int u,int v,int w){e[++cnt]=(Line){w,v,h[u]};h[u]=cnt;}
	void clear(){memset(h,0,sizeof(h));cnt=0;}
	void Insert(int x,int i){
		int k=x%HashMod;
		Add(k,i,x);
	}
	int Query(int x){
		for(int i=h[x%HashMod];i;i=e[i].next)
			if(e[i].u==x)return e[i].v;
		return -1;
	}
}Hash;

void ex_BSGS(int y,int z,int p){
	if(z==1){puts("0");return;}
	int k=0,a=1;
	while(233){
		int d=gcd(y,p);if(d==1)break;
		if(z%d){puts("No Solution");return;}
		z/=d;p/=d;++k;a=1ll*a*y/d%p;
		if(z==a){printf("%d\n",k);return;}
	}
	Hash.clear();
	int m=sqrt(p)+1;
	for(int i=0,t=z;i<m;++i,t=1ll*t*y%p)Hash.Insert(t,i);
	for(int i=1,tt=qpow(y,m,p),t=1ll*a*tt%p;i<=m;++i,t=1ll*t*tt%p){
		int B=Hash.Query(t);if(B==-1)continue;
		printf("%d\n",i*m-B+k);return;
	}
	puts("No Solution");
}

int main(){
	while(~scanf("%d%d%d",&x,&z,&k),x||z||k){
		ex_BSGS(x,k,z);
	}	
}
```


---

## 作者：冘木 (赞：1)

# [原题传送门](https://www.luogu.com.cn/problem/SP3105)

[~~经验*=2~~](https://www.luogu.com.cn/problem/P4195)

# 正文

其实吧，这题就是到模板题，考点就是[扩展BSGS](https://oi-wiki.org//math/bsgs/#_8) ，因为题目给出的模数 $z$ 不一定是质数，所以普通的 $BSGS$ 是做不了的。

至于解释原理。。。。难道你还不会扩展$BSGS$ 吗？[快康康这里](https://oi-wiki.org//math/bsgs/#_8) 。

$SO$，解题过程=读入+模板+输出，直接放代码。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){
		x=1;
		y=0;
		return a;
	}
	ll d=exgcd(b,a%b,x,y);
	ll t=x;
	x=y;
	y=t-a/b*y;
	return d;
}
ll exBSGS(ll a,ll b,ll n){
	if (b==1) return 0;
	ll cnt=0,x,y;
	ll w=1;
	while(1){
		ll d=exgcd(a,n,x,y);
		if (d==1) break;
		if (b%d!=0) return -1;
		b/=d;
		n/=d;
		w=w*a/d%n;
		cnt++;
		if (b==w) return cnt;
	}
	exgcd(w,n,x,y);
	b=(ll)b*(x%n+n)%n;
	a%=n;
	gp_hash_table<int,ll> hash;
	int t=ceil(sqrt(n));
	ll z=1;
	for (int i=0;i<t;i++){
		hash[b*z%n]=i;
		z=z*a%n;
	}
	ll now=1;
	for (int i=1;i<=t;i++){
		now=now*z%n;
		if (hash.find(now)!=hash.end()){
			return i*t-hash[now]+cnt;
		}
	}
	return -1;
}
int main(){
	ll k,x,z;
	for (;scanf("%lld %lld %lld",&x,&z,&k);){
		if (x==0 && z==0 && k==0) break;
		ll ans=exBSGS(x%z,k%z,z);
		if (ans==-1) puts("No Solution");
		else printf("%lld\n",ans);
	}
	return 0;
}
```




---

## 作者：MY（一名蒟蒻） (赞：1)

[我的 BSGS 算法学习笔记](https://www.luogu.com.cn/blog/nizhuan/bsgs-xue-xi-bi-ji)

[SP3105 MOD - Power Modulo Inverted](https://www.luogu.com.cn/problem/SP3105)

[P4195 【模板】扩展 BSGS/exBSGS](https://www.luogu.com.cn/problem/P4195)

好耶，紫色的双倍经验！

普通的 BSGS 只能解决 $a$ 与 $p$ 互质的情况，而 exBSGS 不需要这个条件。

不互质咋办？变成互质！

[OI Wiki 上的讲解](https://oi-wiki.org/math/bsgs/#_8)

方程两边同时除以 $\gcd(a,p)$ ，注意模数 $p$ 也要除，若 $\gcd(a,p) \nmid b$ 则无解。

若仍不互质则重复进行上述过程，直至 $p$ 与 $a$ 互质。

记 $d$ 为每次的 $\gcd$ 的乘积，一共除了 $cnt$ 次，则方程转化为：

$$\frac{a^{cnt}}{d}\times a^{x-cnt} \equiv \frac{b}{d}\pmod {\frac{p}{d}}$$

因为 $a\perp \frac{p}{d}$ ，所以 $\frac{a^{cnt}}{d}$ 在 $\bmod \frac{p}{d}$ 意义下有逆元，移项求解 $x-cnt$ 然后加上 $cnt$ 即可。

当然有时候 $x=cnt$ ，这种情况直接返回 $cnt$ 就好了。

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

int exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1; y=0; return a;}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

map <int,int> _hash;
inline int exBSGS(int a,int b,int p)
{
	a%=p; b%=p;
	if(b == 1 || p == 1) return 0;
	int d,ax=1,cnt=0,x,y;
	while((d=exgcd(a,p,x,y))^1)
	{
		if(b%d) return -1;
		b/=d; p/=d; cnt++;
		ax=1ll*ax*(a/d)%p;
		if(ax == b) return cnt;
	}
	
	exgcd(ax,p,x,y);
	int inv=(x%p+p)%p;
	b=1ll*b*inv%p;
	
//	BSGS
	_hash.clear();
	int t=ceil(sqrt(p)),val=1;
	for(int i=0;i<t;i++)
	{
		_hash[1ll*b*val%p]=i;
		val=1ll*val*a%p;
	}
	a=val; val=1;
	
	if(!a) return !b? 1+cnt:-1;
	for(int i=0,j;i<=t;i++)
	{
		j=_hash.find(val) == _hash.end()? -1:_hash[val];
		if(~j && i*t-j >= 0) return i*t-j+cnt;
		val=1ll*val*a%p;
	}
	return -1;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	int a,b,p,ans;
	while(scanf("%d%d%d",&a,&p,&b) == 3 && a && b && p)
	{
		ans=exBSGS(a,b,p);
		if(~ans) printf("%d\n",ans);
		else puts("No Solution");
	}
//	fclose(stdin); fclose(stdout);
	return 0;
}
```

由于我太菜，在 luogu 上没找到其他 exBSGS 的题，如果您有这样的题目推荐，可以私信或者下方回复。谢谢您的鼓励和支持！

## $\text{Thank you for your reading !}$

---

## 作者：accomplishment (赞：0)

[传送门 1](https://www.luogu.com.cn/problem/P4195)

[传送门 2](https://www.luogu.com.cn/problem/SP3105)

这题是 exBSGS 模板题。

## 什么是 BSGS？

BSGS 是用来解决高次同余方程**模数是质数**的一种算法。

### 高次同余方程

已知整数 $a, b, p$，其中 $p$ 为质数，求最小的非负整数 $x$，使得 $a^x \equiv b \pmod{p}$。

因为 $p$ 是质数，根据费马小定理，$a^{p-1} \equiv 1 \pmod{p}$。又知道 $a^0 \equiv 1 \pmod{p}$，所以幂有长度不超过 $p$ 的循环节。暴力枚举 $x < p$ 即可。

但是如果 $p$ 达到了 $10^9$ 级别怎么办？

### 引入 BSGS

**BSGS = Baby Steps Giant Steps**，可以音译为北上广深，拔山盖世（你也可以音译为爆杀高三），只要见到别不认识就行。

BSGS 算法的思想是 meet in the middle，时间复杂度 $O(\sqrt{p})$。

设 $x = im - j$（$x$ 相当于被除数，$m$ 相当于除数，$i$ 相当于商，$j$ 相当于负余数），其中 $m = \left\lceil \sqrt{p} \right\rceil$，这样原式变为 $a^{im-j} \equiv b \pmod{p}$，可以进一步变形得到：

$$(a^m)^i \equiv b \cdot a^j \pmod{p}$$

$j$ 的取值范围是 $[0, m)$，可以直接枚举等号右边，把 $(b \cdot a^j, j)$ 加入哈希表（可以用 `unordered_map` 实现）。如果有相同的 $\text{key}$，用新的代替旧的 $\text{key}$（这样的 $j$ 更大，可以保证 $im - j$ 更小）。

$i$ 的取值范围是 $[1, m]$，可以直接枚举等号左边，到哈希表中去找是否有相同的值。找到的第一个相等的 $i$，对应的 $im - j$ 就是最小的 $x$。

## 什么是 exBSGS

exBSGS 是用来解决高次同余方程**通用**的一种算法。

### 引入 exGSGS

**exBSGS = 扩展 BSGS 算法**，针对 $p$ 可能不是质数的情况。

无解的判定条件是：$(a, p) \nmid b$ 且 $b \neq 1$。

对于式子：

$$a^x \equiv b \pmod{p}, g = (a, p)$$

两边同时除掉 $g$：

$$a^{x-1} \cdot \frac{a}{g} \equiv \frac{b}{g} \pmod{\frac{p}{g}}$$

设 $a' = \frac{a}{g}, b' = \frac{b}{g}, p' = \frac{p}{g}$。

原式变成：

$$a^{x-1} \cdot a' \equiv b' \pmod{p'}$$

一直这样迭代下去，直到无解或者 $a', p'$ 互质即可。

最终原式变为（设 $M = \prod\limits_{i=1}^kg_i$）：

$$a^{x-k} \cdot \frac{a^k}{M} \equiv \frac{b}{M} \pmod{\frac{p}{M}}$$

此时 $\frac{a^k}{M}$ 与 $\frac{p}{M}$ 互质，可以用正常的 BSGS 解决。

### 本题代码

那么这题就可以按照上面的思路写代码啦！注意别忘了特判 `No Solution`。

[代码](https://www.luogu.com.cn/paste/utiv1x10)

> 附：我的[学习笔记](https://www.luogu.com.cn/blog/accomplishmentblog/BSGS-and-exBSGS)

---

## 作者：LittleMoMol (赞：0)

## exBSGS

### 问题

给定正整数 $a,b,p$，其中 $a,p$ 不一定互质，求满足 $a^t \equiv b \pmod p$ 的**最小非负整数** $t$。

### 推导

分类讨论

- $x=0$ 时满足 $1 \equiv b \pmod p$，$\mathcal{Ans}=0$
- $x>0$
  - $\gcd(a,p)=1$，用朴素 $\operatorname {BSGS}$ 求解
  - $\gcd(a,p) \not= 1$ 见下文

由裴蜀定理得 $a^t + kp = b$，设 $\gcd(a,p) = d$。

若 $d \nmid p$，则无解；否则，等式两边同时除以 $d$ 得到
$$
\dfrac{a}{d} a ^{t - 1} + k \dfrac{p}{d} = \dfrac{b}{d} \iff \dfrac{a}{d} a^{t-1} \equiv \dfrac{b}{d} \pmod {\dfrac{p}{d}}
$$
由于 $\gcd(\dfrac{a}{d}, \dfrac{p}{d}) = 1$，将 $\dfrac{a}{d}$ 移到等式右边，即乘 $\dfrac{a}{d}$ 的逆元，得到
$$
a^{t-1} \equiv \dfrac{b}{d} (\dfrac{a}{d})^{-1} \pmod {\dfrac{p}{d}}
$$
令 $a'=a,\ b' = \dfrac{b}{d} (\dfrac{a}{d})^{-1},\ p'= \dfrac{p}{d}$ 则
$$
 (a')^{t-1} \equiv b' \pmod {p'}
$$
此时递归调用 $\operatorname{exBSGS}$ 即可，若返回值为 $t'$，那么答案就为 $t'+1$，因为此时 $a'$ 的幂是 $t-1$。

### Code
```cpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

typedef long long LL;
const int INF = 1e8;

int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	
	int res = exgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - (a / b) * y;
	return res;
}

int bsgs(int a, int b, int p)
{
	if (1 % p == b % p) return 0;
	int k = sqrt(p) + 1;
	unordered_map<int, int> hash;
	for (int i = 0, j = b % p; i < k; i ++ )
	{
		hash[j] = i;
		j = (LL) j * a % p;
	}
	
	int ak = 1;
	for (int i = 0; i < k; i ++ ) ak = (LL) ak * a % p;
	
	for (int i = 1, j = ak; i <= k; i ++ )
	{
		if (hash.count(j)) return i * k - hash[j];
		j = (LL) j * ak % p;
	}
	
	return -INF;
}

int exbsgs(int a, int b, int p)
{
	b = (b % p + p) % p;
	if (1 % p == b % p) return 0;
	
	int x, y;
	int d = exgcd(a, p, x, y);
	if (d > 1)
	{
		if (b % d) return -INF;
		exgcd(a / d, p / d, x, y);
		return exbsgs(a, (LL) b / d * x % (p / d), p / d) + 1;
	}
	
	return bsgs(a, b, p);
}

int main()
{
	int a, p, b;
	while (cin >> a >> p >> b, a || p || b)
	{
		int ans = exbsgs(a, b, p);
		if (ans < 0) cout << "No Solution" << endl;
		else cout << ans << endl;
	}
	
	return 0;
}

```

---

## 作者：DengDuck (赞：0)


注意到不互质，那我们就要想办法让它互质

$a^x \equiv b(mod\;p)$

得 $a^x - kp=b$

设 $d=gcd(a,p)$


若 $d|b$ 不成立，则无解

式子除 $d$ 得

$$
a^{x-1}\frac{a}{d}- k\frac{p}{d}=\frac{b}{d}
$$


改记为 $a^{x-1}a'- kp'=b'$
即 

$$
a^{x-1}a'\equiv b'(mod\; p')
$$

如此反复，直到互质为止，差不多就是

$$
a^{x-cnt}a'\equiv b'(mod\; p')
$$

注意，操作时如果两边值相等了，答案就是 $cnt$

然后就是个普通 BSGS ,变了一点点，左边需要乘上 $a'$，其他都是一模一样的

求出答案之后答案要加上 $cnt$ ,因为我们求出的是 $x-cnt$

本题时限高达 4s ，就算不写哈希用 map 也能通过

参考如下实现

```cpp
vector<pair<ll, int> > v[ 1000013];
int vis[1000003];
inline ll exBSGS(ll a,ll b,ll p)
{
    memset( vis,0,sizeof(vis));
    if(p==0)return -1;
    if(p==1)
    {
        if(b==0)return 0;
        return -1;
    }
    if (b == 1) {
        if (a == 0)
            return -1;
        return 1;
    }
    if (b == 0) {
        if (a == 0)
            return 1;
        return -1;
    }
    if (a == 0) {
        return -1;
    }
    ll ak=0,t=1,d=gcd(a,p);
    while(d!=1)
    {
        ak++;
        t*=a;
        t/=d;
        p/=d;
        if(b%d!=0)return -1;
        b/=d;
        if(t%p==b%p)return ak;
        d=gcd(a,p);
        t%=p;
    }
    ll m = ceil(sqrt(p)), res=t%p,cnt=1;
    
    for (int r = 1; r <= m; r++) {
        cnt = ksc(cnt, a, p);
        ll hash=(ksc(cnt, b, p)) % mod;
        if(vis[hash]==0)
        {
            vis[hash]=1;
            v[hash].clear();
        }
        v[hash].push_back(make_pair(ksc(cnt, b, p), r));
    }
    for (int k = 1; k <= m; k++) {
        res = ksc(cnt, res, p);
        ll hash=res%mod;
        if (vis[hash])
        {
            for (int j = v[hash].size() - 1; j >= 0; j--)
            {
                if (v[hash][j].first ==res)
                {
                    return m * k - v[hash][j].second+ak; 
                }                
            }                           
        }
    }
    return -1;
}
```



---

## 作者：mango09 (赞：0)

**前置芝士：[$\rm BSGS$](https://www.cnblogs.com/mangoworld/p/Baby-Step-Giant-Step.html)**

当 $a,b,p$ 均为整数时，请求出方程

$$
a^x\equiv b\pmod p
$$

的最小非负整数解.

对于普通的 $\rm BSGS$，必须在 $a,p$ 互质时才能求.

当 $a,p$ 不互质时，需要用到扩展 $\rm BSGS$，即 $\rm exBSGS$.

我们考虑：
$$
a^x\equiv b\pmod p\\
设 \gcd(a,p)=g_1\\
\dfrac{a^x}{g_1}\equiv \dfrac{b}{g_1}\pmod{\dfrac{p}{g_1}}
$$
那么当 $g_1\nmid b$ 时，无解.

否则继续：
$$
a^{x-1}\cdot\dfrac{a}{g_1}\equiv \dfrac{b}{g_1}\pmod{\dfrac{p}{g_1}}\\
设 \gcd(a,\dfrac{p}{g_1})=g_2\\
a^{x-2}\cdot\dfrac{a^2}{g_1g_2}\equiv\dfrac{b}{g_1g_2}\pmod{\dfrac{p}{g_1g_2}}
$$
一直往下除，直到 $a,\dfrac{p}{g_1g_2\dots g_k}$ 互质，其中 $k$ 是除的次数.

我们设 $g_1g_2\cdots g_k=f$，那么最终就是
$$
a^{x-k}\cdot\dfrac{a^k}{f}\equiv\dfrac{b}{f}\pmod{\dfrac{p}{f}}
$$
这时 $a,\dfrac{p}{f}$ 互质，所以 $a^k,\dfrac{p}{f}$ 互质，则 $\dfrac{a^k}{f},\dfrac{p}{f}$ 互质，那么 $\dfrac{a^k}{f}$ 在模 $\dfrac{p}{f}$ 的意义下有逆元，所以
$$
a^{x-k}\equiv\dfrac{b}{f}\cdot\operatorname{inv}(\dfrac{a^k}{f})\pmod{\dfrac{p}{f}}
$$
这样就转化成了一个普通的 $\rm BSGS$.

预处理的时间复杂度为 $O(p\log p)$。

[P4195 【模板】扩展 BSGS/exBSGS](https://www.luogu.com.cn/problem/P4195)

$\text{Code}$

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
typedef long long ll;
using namespace std;

int phi(int p)
{
	int ans = p;
	for (int i = 2; (ll)i * i <= (ll)p; i++)
	{
		if (p % i == 0)
		{
			ans = ans / i * (i - 1);
			while (p % i == 0)
			{
				p /= i;
			}
		}
	}
	if (p != 1)
	{
		ans = ans / p * (p - 1);
	}
	return ans;
}

int bsgs(int a, int b, int p)
{
	map<int, int> hash;
	int t = ceil(sqrt(phi(p))), aj = 1;
	for (int j = 0; j < t; j++)
	{
		int val = (ll)b * aj % p;
		hash[val] = j;
		aj = (ll)aj * a % p;
	}
	a = aj;
	if (!a)
	{
		if (!b)
		{
			return 1;
		}
		return -1;
	}
	int ai = 1;
	for (int i = 0; i <= t; i++)
	{
		if (hash.find(ai) != hash.end())
		{
			int j = hash[ai];
			if (i * t - j >= 0)
			{
				return i * t - j;
			}
		}
		ai = (ll)ai * a % p;
	}
	return -1;
}

int gcd(int a, int b)
{
	if (!b)
	{
		return a;
	}
	return gcd(b, a % b);
}

int x, y;

void exgcd(int a, int b)
{
	if (!b)
	{
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b);
	int tmp = x;
	x = y;
	y = tmp - a / b * y;
}

int inv(int a, int p)
{
	exgcd(a, p);
	x = (x % p + p) % p;
	return x;
}

int exbsgs(int a, int b, int p)
{
	if (b == 1 || p == 1) //特判
	{
		return 0;
	}
	a %= p, b %= p;
	int g = gcd(a, p), f = 1, k = 0;
	while (g > 1)
	{
		if (b % g)
		{
			return -1;
		}
		k++;
		b /= g, p /= g;
		f = (ll)f * (a / g) % p; //一定要先把 p 除以 g 再取模
		if (f == b) //相等就可以直接返回
		{
			return k;
		}
		g = gcd(a, p);
	}
	int res = bsgs(a, (ll)b * inv(f, p) % p, p);
	if (res == -1)
	{
		return -1;
	}
	return res + k;
}

int main()
{
	int a, b, p;
	while (scanf("%d%d%d", &a, &p, &b), a || b || p)
	{
		int res = exbsgs(a, b, p);
		if (res == -1)
		{
			puts("No Solution");
		}
		else
		{
			printf("%d\n", res);
		}
	}
	return 0;
}
```

---

## 作者：Rui_R (赞：0)

$ \text{EXBSGS} $ 模板题。

题意：给定 $a,p,b$ ，求最小的自然数 $x$ ，使 $a^x \equiv b \pmod p$。不存在输出"No Solution"。多组数据。

$a,p,b \le 1e9$

[原题](https://www.luogu.com.cn/problem/SP3105)

首先，我们来看看 $(a,p)=1$ 的情况。 这里（）表示 $\gcd$。

此时，根据欧拉定理，有 $a^{\varphi(p)} \equiv 1 \pmod p$ ，也就是 $a^x$ 在模 $p$ 意义下有循环节，且该循环节小于 $p$。

也就是说，只要研究 $p$ 以内的 $x$ 即可。

那么 $x$ 可以被表示为 $A \lceil p \rceil-B$ 这样的形式，其中 $A,B$ 都在 $\lceil p \rceil$ 以内。

那么 $a^x \equiv b \pmod p$ 等价于 $a^{A \lceil p \rceil} \equiv b \cdot a^{B} \pmod p$

既然 $A,B$ 在 $\lceil p \rceil$ 以内，那么枚举 $A,B$ 就是可以接受的。于是我们可以枚举 $B$，得到 $b \cdot a^{B} \pmod p$ 的所有结果，用哈希表存起来，然后枚举 $A$ ，判断是否存在 $b \cdot a^{B} \pmod p$ 与当前算出的结果一致。

若存在，则 $x$ 为 $A \lceil p \rceil -B$

如果 $A$ 枚举到了尽头，还是没结果，那就没答案喽。

复杂度 $O(\sqrt{n})$，奇妙的应用了分块思想。由于枚举B的时候步子很小，枚举A的时候步子很大，所以这种算法被称为~~北宋高僧~~ $\text{Baby Steps Giant Steps,BSGS}$.

那么我们来看看本题：没保证 $(a,p)=1$。也就是说欧拉定理不再适用，我们不知道 $x$ 的范围。

于是我们可以把 $\text{BSGS}$ 稍微扩展一下。

原式等价于 $a \cdot a^{x-1} \equiv b \pmod p$

令 $g=(a,p),g > 1$ 

 $ a \cdot a^{x-1} + k\cdot p = b ,g(\dfrac{a}{g} \cdot a^{x-1} + k \cdot\dfrac{p}{g})=b$

如果此时 $b$ 是 $g$ 的倍数：

  $\dfrac{a}{g} \cdot a^{x-1} +k \cdot \dfrac{p}{g} = \dfrac{b}{g}$

$\dfrac{a}{g} \cdot a^{x-1} \equiv \dfrac{b}{g} \pmod {\dfrac{p}{g}}$，将 $b,p$ 除以 $g$ 得到 $b',p'$ 然后继续。

如果此时 $b$ 不是 $g$ 的倍数，则无解。原因显然。

注意，如果发现 $w=b'$ ，输出 $w$ 中 $a$ 的个数。此时等式已成立。$w$意义见下。

如此循环往复直至 $a,p'$ 互质。

此时有 $w \cdot a^x\equiv b' \pmod {p'}$，$w$ 为一堆 $\dfrac{a}{g}$ 的积。

那么我们可以上普通的 $\text{BSGS}$ 处理了。对于那个多出来的 $w$，你可以求逆元然后把它扔到右边，也可以在枚举 $A$ 的时候将 $a^{A \lceil p' \rceil}$ 给乘上 $w$。

由于 $w$ 里面也有一些被除掉的 $a$ ，最后答案要加上 $w$ 中 $a$ 的个数。

然后，还要有一些小特判：

$b=0$ 时，我们的算法会裂开。（为什么 $b$ 会等于0？因为这是模意义下的 $b$）

此时原式等价于 $a^x=kp,k=\dfrac{a^x}{p},k \in Z$

暴力枚举 $x$ 即可，每次把 $p$ 除掉 $(a,p)$ 直到 $p=1$即得到答案或者$p\ne1,(a,p)=1$即无解。

$a=0$ 时，由于判掉了 $b=0$ ，无解。

$b=1$ 时，由于判掉了 $a=0$ ，输出0。

代码：（手写哈希表）

```
#include <cstdio>
#include <cmath>

typedef long long ll;

struct Hash_Map{
	static const int maxn=2e6+5,mod=120011;
	struct data{
		ll key,val;int nxt;
	}a[maxn];int p,fir[maxn];
	Hash_Map(){p=0;}
	void clear(){p=0;for(int i=0;i<maxn;i++) fir[i]=0;}
	inline ll hash(ll val){return val%mod;}
	void insert(ll key,ll val){
		ll now=hash(key);
		a[++p].nxt=fir[now];a[p].key=key,a[p].val=val;fir[now]=p;
	}
	ll operator[](ll key){
		ll now=hash(key);
		for(int i=fir[now];i;i=a[i].nxt){
			if(a[i].key==key) return a[i].val;
		}
		return -1;
	}
}hp;

inline ll gcd(ll a,ll b){
	if(!b) return a;
	return gcd(b,a%b);
}

ll a,p,b;

void BSGS(){
	a%=p,b%=p;hp.clear();ll g=-1;
	if(b==0){
		ll ans=0;
		while((g=gcd(a,p))!=1){
			ans++,p/=g;
			if(p==1){printf("%lld\n",ans);return;}
		}
		printf("No Solution\n");return;
	}
	if(!a){printf("No Solution\n");return;}
	if(b==1){printf("0\n");return;}//以上为特判
	ll ret=0,w=1;
	while((g=gcd(a,p))!=1){
		ret++,p/=g;w=(w*(a/g))%p;
		if(b%g){printf("No Solution\n");return;}b/=g;
		if(w==b){printf("%lld\n",ret);return;}
	}
	ll key=std::sqrt(p),temp=b;if(key*key!=p) key++;
	for(int i=0;i<=key;i++){hp.insert(temp,i);temp=(temp*a)%p;}
	ll giant=1;for(int i=1;i<=key;i++) giant=(giant*a)%p;temp=w*giant%p;
	for(int i=1;i<=key;i++){
		if(hp[temp]!=-1){
			printf("%lld\n",((ret+i*key-hp[temp])%p+p)%p);
			return;
		}
		temp=(temp*giant)%p;//BSGS
	}
	printf("No Solution\n");
}

int main(){
	while(scanf("%lld%lld%lld",&a,&p,&b)==3){
		if(a==0&&p==0&&b==0) break;
		BSGS();
	}
	return 0;
}
```

---

## 作者：Vidoliga (赞：0)

# 哎呀$,$这不是BSGS的模板题吗

### BSGS算法不会$??$看这篇[$blog$](https://blog.csdn.net/ACdreamers/article/details/8579511?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160732688819724839512751%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=160732688819724839512751&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v29-10-8579511.nonecase&utm_term=Baby%20Step%20Giant%20Step%20%E8%AF%A6%E7%BB%86%E8%AE%B2%E8%A7%A3&spm=1018.2118.3001.4449)
这里就不做详细讲解了

直接放出代码$:$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod = 99991;
const int n = 100005;
struct Hash{
	bool f;
	int id;
	int val;
}hash[n];
void init(){
	for(int i=0;i<n;i++){
		hash[i].f=0;
		hash[i].id = -1;
		hash[i].val = -1;
	}
}
void insert(int id,LL val){
	LL t = val % mod;
	while(hash[t].f && hash[t].val != val){
		t++;
		t %= mod;
	} 
	if(!hash[t].f){
		hash[t].f = 1;
		hash[t].id = id;
		hash[t].val = val;
	}
}
int find(LL val){
	LL t = val % mod;
	while(hash[t].f && hash[t].val != val){
		t++;
		t%=mod;
	}
	if(!hash[t].f) return -1;
	return hash[t].id;
}
LL gcd(LL a,LL b){
	return b ? gcd(b,a%b):a;

}
void exgcd(LL a,LL b,LL &x,LL &y){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	LL tmp = x;
	x = y;
	y = tmp - (a / b) * y;
}
LL BSGS(LL A,LL B,LL C){
	LL ret = 1;
	for(int i = 0;i <= 50;i++){
		if(ret == B) return i;
		ret = ret * A % C;
	}
	LL ans = 1;
	LL tmp,cnt = 0;
	while((tmp = gcd(A,C)) != 1){
		if(B % tmp) return -1;
		B /= tmp;
	 	C /= tmp;
	 	ans = ans*(A/tmp)%C;
	 	cnt++;
	}
	LL M = ceil(sqrt(1.0*C));
	LL t = 1;
	for(int i = 0;i < M;i++){
		insert(i,t);
		t = t * A % C;
	}
	for(int i = 0;i < M;i++){
	 	LL x,y;
	 	exgcd(ans,C,x,y);
	 	LL val = x * B % C;
	 	val = (val % C + C) % C;
	 	LL j = find(val);
	 	if(j!=-1) return i * M + j + cnt;
	 	ans = ans * t % C;
	}
	return -1; 
}
int main(){
	LL A,B,C;
	while(scanf("%lld %lld %lld",&A,&C,&B)){
		init();
		if(A + B + C == 0) break;
		A%=C;B%=C;
		LL ans = BSGS(A,B,C);
		if(ans == -1){
			puts("No Solution");
			continue;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
完结$,$撒花

---

## 作者：hzoi_liuchang (赞：0)

### UPDATE ON 2020.12.23 更新了原代码中的错误
## BSGS算法
$BSGS(baby-step giant-step)$，即大步小步算法。常用于求解离散对数问题。

形式化地说，该算法可以在 $O \sqrt{p}$ 的时间内求解

 $$ a^x \equiv b (mod\ p)$$
 
 其中 $gcd(a,p)=1$

根据欧拉定理，当 $gcd(a,p)=1$ 时，$a^{\varphi(p)}mod\ p=1$

而 $a^0mod\ p=1$

所以从 $1 \sim \varphi(p)$ 出现了一个循环节

因此，我们只需要求出 $a^1 \sim a^{\varphi(p)}$ 

然后分别带入左右两边判断是否相等

一般的题目中 $p$ 为质数，所以 $\varphi(p)=p-1$

一般就用 $p$ 替代

但是这样做时间复杂度太高，可以用分块的思想优化

令 $a^x=a^{km-t}$，那么原式就变成了

 $$ a^{km} \equiv ba^t (mod\ p)$$
 
 我们只需要分别求出 $t=1 \sim m$ 时 $ba^t$ 的值，将其存到哈希表里
 
 然后从 $1 \sim p/m$ 枚举 $k$ ，判断哈希表中有没有和 $a^{km}$ 相等的数
 
 当 $m=\sqrt{p}$ 时最优
 
## 扩展BSGS算法
求解

 $$ a^x \equiv b (mod\ p)$$
 
 其中 $a,p$ 不一定互质
 
 这个时候就不能再找 $1 \sim \varphi(p)$ 的循环节了，因为不满足欧拉定理的条件
 
 我们把式子变一下，可以写成 
 
$$a \times a^{x-1}+kp=b$$

的形式

根据裴蜀定理，当 $gcd(a,p)|b$ 时方程有解，否则无解

所以在有解的情况下，我们可以把方程左右两边同时除以 $gcd(a,p)$，等号不变

 此时原方程变为
 
 $$\frac{a}{gcd(a,p)} \times a^{x-1}+k \frac{p}{gcd(a,p)}=\frac{b}{gcd(a,p)}$$
 
把 $\frac{p}{gcd(a,p)}$ 看成新的 $p$
 
把 $\frac{b}{gcd(a,p)}$ 看成新的 $b$
  
同时记录一下左边的系数之积 $\frac{a}{gcd(a,p)}$，并不断地提出 $a$
  
这样在最后一定会出现 $gcd(a,p)=1$ 的情况，用普通的 $bsgs$ 即可
  
不要忘了把提出去的 $a$ 的系数加上

### 代码
[模板题](https://www.luogu.com.cn/problem/SP3105)
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=1e5+5,mod=1e5+3;
int h[maxn],tot=1;
struct asd{
	int nxt,val,num;
}b[maxn];
void ad(int val,int id){
	rg int now=val%mod;
	for(rg int i=h[now];i!=-1;i=b[i].nxt){
		rg int cs=b[i].val;
		if(cs==val){
			if(b[i].num<id) b[i].num=id;
			return;
		}
	}
	b[tot].val=val;
	b[tot].nxt=h[now];
	b[tot].num=id;
	h[now]=tot++;
}
int cx(int val){
	rg int now=val%mod;
	for(rg int i=h[now];i!=-1;i=b[i].nxt){
		rg int cs=b[i].val;
		if(cs==val) return b[i].num;
	}
	return -1;
}
int bsgs(rg int a,rg int p,rg int n,rg int xs){
	memset(h,-1,sizeof(h));
	tot=1;
	rg int blo=sqrt(p)+1;
	rg int ac1=n,ac2=1,ac3=xs;
	for(rg int i=1;i<=blo;i++){
		ac1=1LL*ac1*a%p;
		ad(ac1,i);
		ac2=1LL*ac2*a%p;
	}
	for(rg int i=1;i<=blo;i++){
		ac3=1LL*ac3*ac2%p;
		ac1=cx(ac3);
		if(ac1!=-1) return i*blo-ac1;
	}
	return -1;
}
int gcd(rg int aa,rg int bb){
	return bb==0?aa:gcd(bb,aa%bb);
}
int main(){
	rg int a,p,n,haha=1,now,ans,cnt;
	rg bool jud=0;
	while(1){
		a=read(),p=read(),n=read();
		if(a==0 && p==0 && n==0) break;
		haha=1,jud=0,cnt=0;
		a%=p,n%=p;
		if(n==1){
			printf("0\n");
		} else if(a==0 && n==0){
			printf("0\n");
		} else if(a==0){
			printf("No Solution\n");
		} else if(n==0){
			while(1){
				if(p==1){
					printf("%d\n",cnt);
					break;
				}
				now=gcd(a,p);
				if(now==1 && p!=-1){
					printf("No Solution\n");
					break;
				}
				cnt++,p/=now;
			}
		} else {
			while(1){
				now=gcd(a,p);
				if(n%now!=0){
					jud=1;
					break;
				}
				if(now==1){
					ans=bsgs(a,p,n,haha);
					if(ans==-1) jud=1;
					ans+=cnt;
					break;
				}
				cnt++,p/=now,n/=now;
				haha=1LL*haha*(a/now)%p;
				if(haha==n){
					ans=cnt;
					break;
				}
			}
			if(jud){
				printf("No Solution\n");
			} else {
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
```

---

