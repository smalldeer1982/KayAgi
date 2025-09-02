# Count Pairs

## 题目描述

给定一个质数 $p$，$n$ 个整数 $a_1, a_2, \ldots, a_n$，以及一个整数 $k$。

请你计算有多少对下标 $(i, j)$（$1 \le i < j \le n$）满足 $(a_i + a_j)(a_i^2 + a_j^2) \equiv k \pmod{p}$。

## 说明/提示

在第一个样例中：

$(0+1)(0^2 + 1^2) = 1 \equiv 1 \pmod{3}$。

$(0+2)(0^2 + 2^2) = 8 \equiv 2 \pmod{3}$。

$(1+2)(1^2 + 2^2) = 15 \equiv 0 \pmod{3}$。

因此，只有 $1$ 对满足条件。

在第二个样例中，有 $3$ 对满足条件，分别是 $(1, 5)$、$(2, 3)$、$(4, 6)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 0
0 1 2
```

### 输出

```
1```

## 样例 #2

### 输入

```
6 7 2
1 2 3 4 5 6
```

### 输出

```
3```

# 题解

## 作者：lukelin (赞：16)

### 前言
**首先~~当然要~~安利一下博客啦**  
[更好的阅读体验](https://www.cnblogs.com/linzhengmin/p/11142652.html)  
这道题目是道好题。  
第一次div-2进前100，我太弱了。
### 题解
#### 公式推导
我们观察这个式子。
$$(a_i+a_j)(a_i^2+a_j^2)\equiv k \mod p$$
感觉少了点什么，我们想到两边同时乘一个$(a_i-a_j)$。  
于是它变成了:  
$$(a_i^2-a_j^2)(a_i^2+a_j^2) \equiv k(a_i-a_j) \mod p$$
也就是：  
$$a_i^4-a_j^4 \equiv k(a_i-a_j) \mod p$$
把$k$乘进去变成:  
$$a_i^4-a_j^4 \equiv ka_i-ka_j \mod p$$
变换一下就是
$$a_i^4-ka_i \equiv a_j^4-ka_j \mod p$$
公式到这里就推完了  
#### 代码实现
实现很简单，根据上面的的公式，由于k是确定的，我们对于所有的$a_i$把$(a_i^4-ka_i)$取模之后放入一个STL map中，然后我们就可以计算有多少数跟它相同了。  
### 复杂度
鉴于STL map的复杂度，时间复杂度为$\Theta(nlog_2n)$。
### 代码
```cpp
#include <cstdio>
#include <map>
 
using namespace std;
 
long long read(){
    long long x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}
 
map<long long, long long> mp;
 
int main() {
	long long n = read(), p = read(), k = read();
	long long res = 0;
	for (int i = 1; i <= n; ++i){
		long long x = read();
		long long tmp = ((((((x * x) % p * x) % p * x) % p - k * x) % p) % p + p) % p ;
		if (mp.count(tmp) == true)
			res += mp[tmp];
		++mp[tmp];
	}
	printf("%I64d\n", res);
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

题目大概意思就是

>有几对 $i$ , $j$ 满足 $(a_i+a_j)$ * $(a_i^2 + a_j^2)$ % $p$ = $k$ % $p$

暴力的时间复杂度显然是 $θ(N^2)$ 的  , $2 <= N <= 300000$ 显然会 T 掉 而 CF T 掉是没有部分分的

好我们看 根据初中的数学知识
$$(a+b)(a-b) = a^2 - b^2$$

当我们看到 $(a_i+a_j)$ 肯定会第一个想到$(a_i-a_j)$

所以两边同乘 $(a_i-a_j)$ , 然后根据柿子
可得 
$$(a_i^2 + a_j^2)(a_i^2 - a_j^2)\%p = k(a_i-a_j)\%p$$

那么再根据柿子 
$$(a+b)(a-b) = a^2 - b^2$$
不难再次合并
可得 
$$(a_i^4 - a_j^4) = k *a_i - k * a_j$$

然后移项

$$a_i^4 - a_i *k= a_j^4 - a_j *k$$


如何$\theta(N)$ 算出答案的值呢？

```cpp
int ans = 0 ;
	for(register int i=1;i<=n;i++) {
		ans += mp[f[i]] ;
		++ mp[f[i]] ;
	}
```


记得多取模%%% + LL

```cpp
#include <bits/stdc++.h>
#define rep(i,j,n) for(register int i=j;i<=n;i++)
#define Rep(i,j,n) for(register int i=j;i>=n;i--)
#define low(x) x&(-x)
using namespace std ;
typedef long long LL ;
const int inf = INT_MAX >> 1 ;
inline LL read() {
	LL res(0) , f(1) ;
	register char c ;
#define gc c = getchar()
	while(isspace(gc)) ;
	c == '-' ? f = - 1 , gc : 0 ;
	while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(gc)) ;
	return res * f ;
#undef gc
}
 
#define int long long
int n , p , k ;
int a[300000 + 5] ;
int f[300000 + 5] ;
 
map < int , int > mp ;
inline void Ot() {
	n = read() , p = read() , k = read() ;
	for(register int i=1; i<=n; i++) a[i] = read() ;
	for(register int i=1; i<=n; i++) {
		f[i] = (a[i] * a[i]) % p * a[i] % p * a[i] % p - a[i] * k % p ;
		f[i] %= p ;
		if(f[i] < 0) f[i] += p ;
	}
	int ans = 0 ;
	for(register int i=1;i<=n;i++) {
		ans += mp[f[i]] ;
		++ mp[f[i]] ;
	}
	cout << ans << endl ;
	return ;
}
signed main() {
//  freopen("test.in","r",stdin) ;
	return Ot() , 0 ;
}
```

[cnblogs同款 qwq](https://www.cnblogs.com/qf-breeze/p/11141522.html)

---

## 作者：0xFF (赞：3)

参加模拟赛遇到了这道题，不过我太菜了考场上只会 $n^2$ 的暴力 $qwq$
### 简化题意
给出**互不相同**的一个 $a$ 序列问其中有多少对二元组 $(i,j)$ 满足
$ (a_i + a_j) * (a_i^2 + a_j^2 ) \equiv k \bmod p$

------------

### 题目分析
一看数据范围 $2≤n≤3⋅10^5$ 明显不能暴力，所以需要推式子

我们观察这个式子已经不能进行因式分解故我们可以考虑减少式子的项数

$ (a_i + a_j) * (a_i^2 + a_j^2 ) \equiv k \bmod p$，

两边同时乘以 $(a_i -a_j)$，

得到 $(a_i^4 - a_j^4) \equiv k(a_i - a_j) (\bmod p)$，

移项可以得到 $a_i^4 - ka_i \equiv a_j^4 - ka_j (\bmod p)$。

到这里，这道题的思路就已经很清晰了，只需要用一个 map，统计每个 $(a_i^4 - ka_i) \bmod p$ 出现了多少次即可。答案即为 $\textstyle \sum_{j}\begin{pmatrix}
s_j \\
2
\end{pmatrix}$
其中 $s_j$ 表示使得 $a_i^4 - ka_i \equiv j (\bmod p)$的 $i$ 的数目。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
map<long long, long long> app;
int main() {
	long long n = read(), p = read(), k = read();
	long long ans = 0;
	for (int i = 1; i <= n; ++i){
		long long x = read();
		long long tmp = ((((((x * x) % p * x) % p * x) % p - k * x) % p) % p + p) % p ;
		if (app.count(tmp) == true)
			ans += app[tmp];
		++app[tmp];
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Steam_Rg (赞：2)

# 传送门 [Count pairs](https://www.luogu.com.cn/problem/CF1188B)

这个式子只有**一边**有 $a$ 项。

所以考虑将原式子**化简**（方向肯定是一边关于 $a_i$，一边关于 $a_j$，方便**枚举**与**存储**）。

由初一数学得，看到**二次方相加**与**一次方相加**想到**平方差公式**。

那么我们可以 ~~轻松~~ 化简： 

$$
\textstyle (a_i + a_j) \times (a^2_i + a^2_j) \equiv k\bmod p
$$

$$
\textstyle (a_i + a_j) \times (a_i - a_j) \times (a^2_i + a^2_j) \equiv (a_i - a_j) \times k\bmod p
$$

$$
\textstyle (a^2_i - a^2_j) \times (a^2_i + a^2_j) \equiv (a_i - a_j) \times k\bmod p
$$

$$
\textstyle a^4_i - a^4_j \equiv a_i  \times k - a_j \times k\bmod p
$$

**整理得** $a^2_i - a_i \times k \equiv a^2_j - a_j \times k\bmod p$

（这个过程推荐自己推，唯二的难点）

已知公式，就在**输入时存起来**，同时记录**最多的数量**。

那么，最后的问题：用数组存肯定爆 **MLE**，那用什么存呢？

当然是伟大的 `STL`，**空间自动分配**，多种类型都可存的 `map` 了，完全补全了数组有**不使用的空间**而**浪费**的问题。

就不放代码了（~~太简单了~~）。

提示：不开 `long long`  ~~想见祖宗么~~。

---

## 作者：Lyrella (赞：2)

# 题意

求数对 $(i,j)(1 \le i,j \le n)$ 中满足 $(a_i+a_j)\times(a_i^2+a_j^2)\equiv k \pmod p$ 的个数。

# 题解

**尝试化简。**

这里用到**初一**的芝士：**平方差公式**

根据余数性质，先在两边同时乘上一个 $(a_i-a_j)$，原式变成：

$$(a_i-a_j)\times(a_i+a_j)\times(a_i^2+a^2_j)\equiv (a_i-a_j)\times k \pmod p$$

运用平方差公式，得：

$$a_i^4-a_j^4 \equiv ka_i-ka_j \pmod p$$

最后移项，得：

$$a_i^4-ka_i \equiv a_j^4-ka_j \pmod p$$

所以我们可以用 $map$ 来维护 $a_i^4-ka_i$，每次输入 $a_i$ 时，累加出前面 $a_j^4-ka_j(1 \le j < i) \equiv a_i^4-ka_i \pmod p$ 的个数，再将 $a_i^4-ka_i$ 放入 $\text{map}$（即 $map_{a_i^4-ka_i}+1$）。

# 注意

- 开 long long

- 多取模

- 先**累加**，再**维护**

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
map < ll, ll > mp;
ll n, mod, k, ans;
inline ll mo(ll x){return x * x % mod * x % mod * x % mod;}
signed main()
{
	scanf("%lld %lld %lld", &n, &mod, &k);
	for(int i = 1; i <= n; i++)
	{
		ll x; scanf("%lld", &x);
		ll t = (mo(x) - k * x % mod + mod) % mod;
		if(mp.count(t))ans += mp[t];
		++mp[t];
	}
	printf("%lld", ans);
	return 0;
}
```

# ending

感谢各位管理员和巨佬的莅临，小蒟蒻感激不尽。

---

## 作者：WeLikeStudying (赞：2)

**引入**
- $n$ 个数，统计 $(i,j)(i<j)$ 使 $a_i+a_j=c$。
- 显然这题我们并不需要 $n^2$ 枚举，因为对于每个 $a_i$，容易求出它所对应的 $a_j=c-a_i$，所以我们把 n 个数存进哈希表再暴力枚举一波即可做到 $O(n)$ 复杂度。
- 从本质上讲，我们将 $a_i$ 当成参数，将 $a_j$ 当成变量，进行参数与变量的分离。
- 相当于将 $h(x,y)=0$ 变成 $f(x)=g(y)$ 的形式。

**题意**
- 让我们来一道例题 [CF1188B Count Pairs](https://www.luogu.com.cn/problem/CF1188B)：$n$ 个数，统计数对 $(i,j)$ 满足 $i<j$ 使 $(a_i+a_j)\cdot(a_i^2+a_j^2)\equiv k\pmod p $。
- 数据保证 $\forall i\neq j,a_i\neq a_j$，$p$ 为质数。

**做法**
- 运用参变分离：
$$(a_i+a_j)\cdot(a_i^2+a_j^2)-k\equiv 0\pmod p $$
$$(a_i-a_j)\cdot[(a_i+a_j)\cdot(a_i^2+a_j^2)-k]\equiv 0\pmod p $$
$$(a_i-a_j)\cdot(a_i+a_j)\cdot(a_i^2+a_j^2)-k\cdot(a_i-a_j)\equiv 0\pmod p $$
$$a_i^4-a_j^4-ka_i+ka_j\equiv 0\pmod p $$
$$a_i^4-ka_i\equiv a_j^4 -ka_j\pmod p$$
- 显然，这里 $h(x,y)=[(x+y)\cdot(x^2+y^2)-k]\bmod p$，而
$g(y)=f(x)=(x^4-kx)\bmod p$。
- 然后我们就可以用与之前类似的方法(由于 $a_i$ 两两不等）(其实不相等的条件主要是提示作用）。
- 用 $O(n)$ 的时间过这道题目（或者选择用 STL 的 map $O(n\log n)$ 卡过）。
- 最后的注意事项：记得开 long long，乘起来可能会爆。
- [代码实现](https://www.luogu.com.cn/paste/w2e8gqwp)。
- 总的来说，参变分离是简化等式的一种方法，如果你看到纠缠不清难以入手的多元式子，你可以考虑参变分离。

---

## 作者：mraymes (赞：2)

本文章将同步到 [Hexo 博客](https://mraymes.github.io).

## 题意
给定一个质数 $p$, 一个数列 $a_1, a_2, \cdots, a_n$, 与一个整数 $k$.  
求满足 $(a_i + a_j)(a_i^2 +a_j^2) \equiv k \mod p$ 的数对 $(i, j)$ 的个数.

## 解析
这是一道数学题.

同余方程有一些性质:  
若 $a \equiv b \mod p$, 那么可以得出:  
$a + c \equiv b + c \mod p$  
$a \cdot c \equiv b \cdot c \mod p$

也就是说同余方程可以进行移项操作, 也可以两边同时乘一个数, 方程依然成立.

还需要了解的是平方差公式:  
$(a + b)(a - b) = a^2 - ab + ab - b^2 = a^2 - b^2$

知道上面的东西后, 便可以对式子进行一些处理.  
$$(a_i + a_j)(a_i^2 +a_j^2) \equiv k \mod p$$

两边同时乘 $a_i - a_j$ 得
$$(a_i + a_j)(a_i^2 + a_j^2) \cdot (a_i - a_j) \equiv k \cdot (a_i - a_j) \mod p$$
$$(a_i + a_j)(a_i - a_j) \cdot (a_i^2 + a_j^2) \equiv k a_i - k a_j \mod p$$

运用平方差公式进行化简
$$(a_i^2 - a_j^2)(a_i^2 + a_j^2) \equiv k a_i - k a_j \mod p$$
$$a_i^4 - a_j^4 \equiv k a_i - k a_j \mod p$$
$$a_i^4 - k a_i \equiv a_j^4 - k a_j \mod p$$

最后, 我们对于每一个 $a_i$ 算出 $a_i^4 - k a_i \bmod p$ 的值, 并且存入 `map` 中. 所有满足 $1 \leqslant j < i$ 且 $a_j^4 - k a_j \bmod p = a_i^4 - k a_i \bmod p$ (即 $a_j^4 - k a_j \equiv a_i^4 - k a_i \mod p$) 的 $j$ 的个数计入到最终答案中.

代码:

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, p, k;
ll a[300001];
map<ll, ll> b;
ll cnt = 0;

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    n = read<ll>(), p = read<ll>(), k = read<ll>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<ll>();
        ll x = a[i] * a[i] % p * a[i] % p * a[i] % p - a[i] * k % p;
        x %= p;
        x += (x < 0 ? p : 0);
        cnt += b[x]; // 先更新答案
        b[x]++;      // 后更新 map
    }

    cout << cnt << '\n';

    return 0;
}

```


---

## 作者：Eltaos_xingyu (赞：1)

高二了还做不出来这种题，看来是要退役了啊。

题意：给定 $n,p,k$ 和一个序列 $a_1,a_2,\cdots,a_n$，求满足 $(a_i+a_j)\times (a_1^2+a_j^2)\equiv k\pmod p$ 的无序对 $(i,j)$ 个数。

这种计数二元组的题目，很多是计数偏序或者计数某函数值相等。

我们往这两个方向去想，考虑我们尝试把右边的式子化一下使得其没有与 $a_i$ 和 $a_j$ 都相关的项。

容易想到平方差公式可以有效抵消这样的因数的项，于是考虑左右两边同时乘上一个 $(a_i-a_j)$，有：

$$
(a_i^2-a_j^2)\times (a_i^2+a_j^2)\equiv k(a_i-a_j)\pmod p
$$

左侧仍是一个平方差公式，继续化简，可得：

$$
a_i^4-a_j^4\equiv ka_i-ka_j\pmod p
$$

这个时候我们已经完成了抵消与 $a_i,a_j$ 都有关的项的一步，不难发现我们只需要计数 $f(x)=(a_x^4-ka_x)\bmod p$ 这个函数在定义域 $[1,n]\cap \N$ 中有多少值相同的元素对即可。`map` 或 `unordered_map` 即可。代码中使用了 `cc_hash_table`。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/exception.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
int n,p,k,x;
cc_hash_table<int,int> mp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>p>>k;
	long long ans=0;
	int tp;
	for(int i=1;i<=n;i++){
		cin>>x;
		tp=(1ll*x*x%p*x%p*x%p-1ll*x*k%p+p)%p;
		ans+=mp[tp];
		mp[tp]++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：1)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17587811.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1188B)

感觉并不是特别难的题。

首先是一个简单的推式子，有原式：

$$(a_i+a_j) \times ({a_i}^2+{a_j}^2) \equiv k (\bmod \space p)$$

如何针对 $a_i+a_j$ 进行有效处理呢？不难想到平方差公式：

$$(a_i+a_j) \times (a_i-a_j) \times ({a_i}^2+{a_j}^2) \equiv k \times (a_i-a_j) (\bmod \space p)$$

合并左式一二项，同时拆右式括号：

$$({a_i}^2-{a_j}^2) \times ({a_i}^2+{a_j}^2) \equiv k \times a_i - k \times a_j (\bmod \space p)$$

我们发现可以再针对 ${a_i}^2$ 和 ${a_j}^2$ 使用平方差公式，则有：

$${a_i}^4 - {a_j}^4 \equiv k \times a_i - k \times a_j (\bmod \space p)$$

移项得：

$${a_i}^4 - k \times a_i \equiv {a_j}^4 - k \times a_j (\bmod \space p)$$

也就是说，针对每一个 $a_i$，我们只需要注意 ${a_i}^4 - k \times a_i$ 即可。可以考虑使用 ```unordered_map``` 维护并记录方案数。

```cpp
// Problem: Count Pairs
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1188B
// Memory Limit: 250 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define ok puts("YES")
#define no puts("NO")
#define debug puts("Tomotake_Yoshino_my_wife")
#define clean fflush(stdout)
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=3e5+5;
int binpow(int a,int b,int mod){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int n,p,k;
int res,ans;
int a[maxn];
unordered_map<int,int> mp;
inline void init(){
	n=read();p=read();k=read();
	for(register int i=1;i<=n;++i) a[i]=read();
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		res=binpow(a[i],4,p)-k*a[i]%p;res=(res+p)%p;
		ans+=mp[res];ans%=p;mp[res]++;mp[res]%=p;
	}
	printf("%lld",ans);
}
```

---

## 作者：TernaryTree (赞：1)

题意：给定 $n,p,k$ 以及长为 $n$ 的序列 $a$，求有多少个二元组 $(i,j)$ 满足

$$(a_i+a_j)(a_i^2+a_j^2)\equiv k\pmod p$$

在 MO 中，看到这种倍增幂的就想到平方差公式化简。容易得到

$$
\begin{aligned}
(a_i+a_j)(a_i^2+a_j^2)&\equiv k\pmod p \\ 
(a_i-a_j)(a_i+a_j)(a_i^2+a_j^2)&\equiv k(a_i-a_j)\pmod p \\
a_i^4-a_j^4&\equiv k(a_i-a_j)\pmod p \\
a_i^4-ka_i&\equiv a_j^4-ka_j\pmod p \\
\end{aligned}
$$

左右两边的结构是类似的，我们对于每个 $a_i$ 对应 $a_i^4-ka_i\bmod p$ 的值加入哈希表，然后每次查询前面有几个相同的值求和即可。

短小精悍的代码：

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long

using namespace std;
using namespace __gnu_pbds; // pbds 的 map 实现效率比较高。

const int maxn = 3e5 + 1;

int n, p, k, ans;
int a[maxn];
gp_hash_table<int, int> g;

signed main() {
    cin >> n >> p >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int t = (a[i] % p * a[i] % p * a[i] % p * a[i] % p - a[i] % p * k % p + p) % p;
        if (g.find(t) != g.end()) {
            ans += g[t];
            g[t]++;
        } else g[t] = 1;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：swiftc (赞：1)

建议在我的博客阅读,要不然$markdown$可能会炸 QAQ

看这个式子：$(a_i+a_j)*(a_i^2+a_j^2)≡k\ mod\ p $

大家都知道平方差公式吧:

$(a+b)*(a-b)=a^2-b^2$

那么把这个式子乘上一个$(a_i-a_j)$,得：

$(a_i^2+a_j^2)*(a_i^2-a_j^2)≡k*(a_i-a_j)\ mod \ p$

即：

$(a_i^4-a_j^4)≡k*(a_i-a_j)\ mod \ p$


把$k*a_i$移到等式左边，$a_j^4$移到等式右边，就变成了：

$a_i^4-a_i*k≡a_j^4-a_j*k\ mod \ p$

就可以用map $O(n\ log\ n)$判断了

### 时间复杂度还不够低？

请出```tr1::unordered_map```，这是一个时间复杂度为$O(1)$的```map```，使用方法见我的代码

### code:

```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define int long long
using namespace std;
int n,p,k,a[300001],b[300001];
tr1::unordered_map<int,int>ma;
int qpow(int a,int b){
    if(b==0)return 1;
    int tmp=qpow(a,b/2);
    return b%2?tmp*tmp%p*a%p:tmp*tmp%p;
}
int ans=0;
main(){
    scanf("%lld%lld%lld",&n,&p,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        b[i]=(qpow(a[i],4)-k*a[i]%p)%p;
        while(b[i]<0)b[i]=(b[i]+p)%p;
    }
    for(int i=1;i<=n;i++){
        ans+=ma[b[i]];
        ma[b[i]]++;
    }
    printf("%lld\n",ans);
    return 0;
}

```




---

## 作者：WhitD (赞：0)

## 题目大意
给定一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$ 和一个整数 $k$、素数 $p$，保证序列中的元素互不相同。

求 $(i,j) (1\le i<j\le n)$ 满足 $(a_i + a_j)\cdot(a_i^2 + a_j^2 ) \equiv k \pmod p$ 的个数。
## 思路
显然朴素的暴力枚举是 $O(n^2)$ 的，会超时，我们需要考虑将式子进行转化。

首先，要知道同余有如下性质：
$$\texttt{若}\ a\equiv b\pmod p,\texttt{则}\ ac\equiv bc\pmod p$$

我们发现原式是两项（平方）的和的乘积，于是想到运用平方差公式：在同余式两边同时乘上 $(a_i-a_j)$，注意题目限定了 $a_i\neq a_j$，因此不会因为乘上 $0$ 导致多算情况：
$$(a_i-a_j)\cdot(a_i+a_j)\cdot(a_i^2+a_j^2)\equiv k\cdot(a_i-a_j)\pmod p$$
乘开后发现又有了一个平方差的形式：
$$(a_i^2-a_j^2)\cdot(a_i^2+a_j^2)\equiv ka_i-ka_j\pmod p$$
进一步化简，移项：
$$a_i^4-a_j^4\equiv ka_i-ka_j\pmod p$$
$$a_i^4-ka_i\equiv a_j^4-ka_j\pmod p$$
原题就被转化为了求有多少对 $(i,j)$ 满足上式。

由于 $k,p$ 都是定值，此时我们只需要维护一个 `map` 来记录是否出现相同的 $a_i^4-ka_i$ 并且累加答案就可以了。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define yuanshen (((((1ll*x*x)%p)*((1ll*x*x)%p))%p-(1ll*x*k)%p)+p)%p
using namespace std;
typedef long long ll;
ll ans,n,p,k;
map<ll,ll> a;
int main()
{
	a.clear();
	//freopen("date.txt","r",stdin);
	cin>>n>>p>>k;
	for(ll i=1,x;i<=n;i++)
	{
		cin>>x;
		ans+=a[yuanshen];
		a[yuanshen]++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Φρανκ (赞：0)

题意：求无序数对 $(i,j)$ 的个数，使得 $(a_i+a_j)(a_i^2+a_j^2)\equiv k\bmod p$。

核心思想：等式代换

解：

$(a_i+a_j)(a_i^2+a_j^2)\equiv k\bmod p$

$\Rightarrow (a_i-a_j)(a_i+a_j)(a_i^2+a_j^2)\equiv k(a_i-a_j)\bmod p$

$\Rightarrow a_i^4-a_j^4\equiv k(a_i-a_j)\bmod p$

$\Rightarrow a_i^4-ka_i\equiv a_j^4-ka_j\bmod p$

根据此式可定义 $b_i=a_i^4-ka_i\bmod p$，求得并排序后就可以统计 $(i,j)$ 使得 $b_i=b_j$。可以用双指针实现。前一个指向与当前数字相同的第一个数字，后一个指向当前数字。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long n, p, k, a[300001], b[300001], t1=1, t2=1, res;
map<int, int> rem;
int main()
{
	cin>>n>>p>>k;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i];
		b[i]=((a[i]*a[i]%p)*(a[i]*a[i]%p)%p-k*a[i]%p+p)%p;//计算b
	}
	sort(b+1, b+n+1);
	while(t2<n)
	{
		while(b[t1]==b[t2])//若相等
		{
			res+=t2-t1;//统计个数
			t2++;
			if(t2>n)
				break;//注意及时结束
		}
		t1=t2;//不相等则更新t1到当前数字
	}
	cout<<res;
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

# B.Count Pairs
$\mathtt{Difficulty}$=$\mathtt{2300}$

二话不说，先推一波式子

$(a_i+a_j)(a_i^2+a_j^2)\equiv k\pmod{p}$

$\Rightarrow (a_i+a_j)(a_i-a_j)(a_i^2+a_j^2)\equiv k(a_i-a_j)\pmod{p}$

$\Rightarrow a_i^4-a_j^4\equiv k(a_i-a_j)\pmod{p}$

$\Rightarrow a_i^4-ka_i\equiv a_j^4-ka_j\pmod{p}$

推到这里就够了

我们发觉可以直接用 map 记录第 $i$ 个元素的 $a_i^4-ka_i$ 对 $p$ 取模的值

然后直接算答案即可

代码不难写出
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
#define int long long
int N,K,MOD,A[300001];
map< int,int >Map;
signed main(void)
{
	BetterIO;
	register int i,Ans=0;cin>>N>>MOD>>K;
	for(i=1;i<=N;i++)
	{
		register int Remainder;cin>>A[i],A[i]%=MOD;
		Remainder=A[i]*A[i]%MOD*A[i]%MOD*A[i]%MOD-K*A[i]%MOD+MOD;
		Ans+=Map[Remainder%MOD];
		Map[Remainder%MOD]++;
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：xukuan (赞：0)

### 配方法

初二时同学们应该做过这样一道题：

因式分解： $x^{4}-y^{4}$

原式$=(x-y)(x+y)(x^{2}+y^{2})$

看这个式子：

$(a_{i}+a_{j})(a^{2}_{i}+a^2_{j})$

是不是有点似曾相识？

给两边补上 $(a_{i}-a_{j})$ =>

$a^{4}_{i}-a^{4}_{j} \equiv k(a_{i}-a_{j})(mod p)$ =>

$a^{4}_{i}-ka_{i} \equiv a^{4}_{j}-ka_{j}(mod p)$

这样，我们就可以用map统计相同余数出现的个数来判断了

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,p,k,ans;
map<ll,ll> mp;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

int main(){
	n=read(); p=read(); k=read();
	for(ll i=1; i<=n; i++){
		ll x=read()%p;
		//(x*x%p*x%p*x%p+p-k*x%p)%p=x^4%p
		ans+=mp[(x*x%p*x%p*x%p+p-k*x%p)%p];//这里直接加上之前的次数，强制在线
		//当然也可以最后再for(i:mp.begin()-mp.end())统计
		mp[(x*x%p*x%p*x%p+p-k*x%p)%p]++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：YLWang (赞：0)

这个题是属于简单的Div2E但是有点思维难度。

观察这个柿子。（式子）

因为$n$比较大，无法一一枚举。所以我们尝试将原式子转化为只基于$a_i$的。

$(a_i + a_j)(a_i^2 + a_j^2) \equiv k \ (mod\ p) $

我们尝试在式子两边乘一个$(a_i-a_j)$变成$(a_i^4 - a_j^4) \equiv k(a_i + a_j) \ (mod\ p) $

整理一下变成$a_i^4 - ka_i \equiv a_j^4 - ka_j$

发现目标达到了

于是，我们把$a_i^4 - ka_i$丢进一个$map$里维护一下就完事了。

复杂度$O(nlogn)$

代码：
```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF 2147483647/3
#define ll long long
#define int long long 
using namespace std;
inline int read()
{
    int num=0;char c=' ';
    for(;c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';num=(num*10+c-48),c=getchar());
    return num;
}
#define MAXN 300005
int n, k, MOD, a[MAXN], fac[MAXN];
map < int, int > num;

signed main()
{
    n = read(), MOD = read(), k = read();
    k = k % MOD;
    for(int i = 1; i <= n; i++) {
        int A = read();
        int tmp = (A * A) % MOD;
        tmp = (tmp * tmp) % MOD;
        a[i] = ((tmp - k * A) % MOD + MOD) % MOD;
    }
    
    for(int i = 1; i <= n; i++)
        num[a[i]]++;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int qwq = num[a[i]];
        ans += qwq * (qwq - 1) / 2;
        num[a[i]] = 0;
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：F1aMiR3 (赞：0)

题目给的条件貌似不是很好用，所以我们把它整理一下

$(a_i+a_j)(a_i^2+a_j^2)\equiv k(mod~p)$

$(a_i-a_j)(a_i+a_j)(a_i^2+a_j^2)\equiv k(a_i-a_j)(mod~p)$

$(a_i^2-a_j^2)(a_i^2+a_j^2)\equiv ka_i-ka_j(mod ~p)$

$a_i^4-ka_i\equiv a_j^4-ka_j(mod~p)$

我们可以预处理出每个 $d_i=a_i^4-ka_i$ ，如果 $d_i=d_j$ ，那么 $a_i,a_j$ 一定是满足条件的一对数

$d_i\in[0,p)$ ，这个范围显然不能用桶，我们可以将 $d$ 排序，这样相等的元素都会聚集在一起，方便统计个数

如果有 $k$ 个元素的 $d$ 相等，那么这 $k$ 个元素总共会产生 $C_k^2=\frac{k(k-1)}{2}$ 对满足条件的数

放一下代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
const int mod=1e9+7;
int n,p,k;
long long ans;
long long a[300001];
int main()
{
	scanf("%d%d%d",&n,&p,&k);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    //处理d数组
	for(int i=1;i<=n;++i)a[i]=((long long)a[i]*a[i]%p*a[i]%p*a[i]%p+p-(k*a[i]%p))%p;
    //注：下面的a数组即为d数组
	std::sort(a+1,a+1+n);
	int p=1;
	while(p<=n)
	{
		int tmp=a[p],cnt=0;
		while(a[p]==tmp)++cnt,++p;//统计相等的个数
		ans+=(long long)cnt*(cnt-1)%mod*(500000004)%mod;//添加贡献（500000004为2模1000000007意义下的逆元）
		ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

