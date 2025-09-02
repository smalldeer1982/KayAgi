# Kill Demodogs

## 题目描述

给定一个数$n$,表示有一个 $n \times n$ 的方格。每个格子里都有一个数，第 $i$ 行第 $j$ 列的格子值为 $i⋅j$。现在Hawkins要从 $(1,1)$ 走到 $(n,n)$,每次只能从 $(i,j)$ 走到 $(i,j+1)$ 或 $(i+1,j)$, 每走到一个格子就能获得格子中的一个数，最大化数字之和。

## 样例 #1

### 输入

```
4
2
3
50
1000000000```

### 输出

```
14154
44484
171010650
999589541```

# 题解

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 级蒟蒻 CJH。

## 题意

~~题面翻译十分清楚。~~

## 分析

一道显然的贪心题目，本人提供一种懒人做法（同时也是洛谷最短解）。

只需要不停地向右、向下取每一个数即可。

这里推荐一个网站：[OEIS](http://oeis.org/?language=chineseS)。

这是一个数列分析网站，收录了许许多多的数列。

你只需要把前几个手算出来，接着以逗号或者空格为分隔符的形式输入进去。如果担心不是这个规律，你可以多算几个。

你可以找到这个答案的数列为：[OEIS A002412](http://oeis.org/A002412)。

可以发现数列的通项公式即答案为 $\dfrac{n(n+1)(4n-1)}{6}$。

又因为 $2\le n\le 10^9$，所以答案一定是小于 $2^{127}\approx10^{36}$ 的，完全可以使用 `__int128` 来存储！再也不需要担心溢出了！

在输出的时候取模完后直接强制转换类型为 `long long` 即可！单次时间复杂度 $O(1)$。

## 注意事项

- `__int128` 在部分语言标准中是无法使用的（会编译错误），所以使用时请选择 **`C++17`** 及以上的语言标准。
- 在计算 $4n-1$ 时，要使用 __`4ll*n-1`__ 而不是 `4*n-1`，否则会默认为 `int` 类型导致溢出。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
void solve(){
	int n;scanf("%d",&n);
	printf("%lld\n",(long long)((__int128)((__int128)n*(n+1)*(4ll*n-1)/6)%mod*2022%mod));//取模以后再强转类型！否则可能会溢出！
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

*如有笔误，请在此博客下回复或者私信我，本人将尽快修改！*

---

## 作者：Engulf (赞：1)

首先要知道，当两个数和一定的时候，差越小，积越大。

所以我们可以发现最优的路线就是走一个斜线下去。

这样的话答案就是

$$1 \times 1 + 1 \times 2 + 2 \times 2 + 2 \times 3 + \cdots + (n - 1) \times n + n \times n$$

即

$$\sum\limits_{i = 1} ^ {n} i^2 + \sum\limits_{i = 2}^n (i - 1) \times i$$

均可使用公式求出。

最终答案即

$$\dfrac{(n + 1)(2n + 1)}{6} + \dfrac{(n - 1)n(n + 1)}{3}$$

当然上面的式子不够美观，通过 [oeis](http://oeis.org/A002412) 可得上式的更简洁形式为

$$\dfrac{n(n + 1)(4n - 1)}{6}$$

---

## 作者：aimcf (赞：0)

容易发现，当走到了第 $i$ 个方格的时候，设这个方格的坐标为 $(x, y)$，那么一定有 $x+y-1=i$。

由于差小积最大，所以可以考虑贪心：

+ 如果 $i\bmod 2 = 0$，那么可以选择 $(\frac{i}{2}, \frac{i}{2}+1)$。
+ 如果 $i\bmod 2 = 1$，那么可以选择 $(\frac{i}{2} + 0.5, \frac{i}{2} + 0.5)$。

[![pSArWwD.png](https://s1.ax1x.com/2023/01/06/pSArWwD.png)](https://imgse.com/i/pSArWwD)

然而 $n\le 10^9$，无法暴力计算。

通过 [OEIS](http://oeis.org/A000330) 可以得到，$\sum_{i=1}^n i^2=\frac{n\times (n+1)\times(2\times n + 1)}{6}$。

那么对于所有 $x=y$（$i\bmod 2 = 1$）的位置而言，贡献就是 $2022\times n\times (n+1)\times (2\times n+1)$。

对于 $i\bmod 2 = 0$（$x\neq y$）的位置而言，答案为 $\sum_{i=1}^{n-1} (i\times (i+1))\times 2022$。

化简式子得到：

$(1\times 2 + 2\times 3 + 3\times 4 + \ldots + (n - 1) \times n)\times 2022$

$(1\times 1 + 2\times 2 + 3\times 3 + \ldots + (n-1)\times (n-1)+1+2+3+\ldots+(n-1))\times 2022$

$(\frac{n\times (n-1)\times (2\times n - 1)}{6} + \frac{n\times (n-1)}{2})\times 2022$

将前面的式子和上面的式子相加就得到了答案。

但是由于会爆 `long long`，需要使用逆元（P党当我没说）。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10, mod = 1e9 + 7;
int a[N];

int ksm(int a, int b, int c)
{
  if (!b) return 1;
  int ans = ksm(a, b >> 1, c);
  ans = ans * ans % c;
  if (b & 1) ans = ans * a % c;
  return ans;
}

void solve()
{
  int n;
  cin >> n;
  int r1 = n * (n + 1) % mod * (2 * n + 1) % mod * ksm(6, mod - 2, mod) % mod;
  (r1 *= 2022) %= mod;
  int r2 = n * (n - 1) % mod * (2 * n - 1) % mod * ksm(6, mod - 2, mod) % mod + n * (n - 1) % mod * ksm(2, mod - 2, mod) % mod;
  (r2 *= 2022) %= mod;
  // cout << r1 << ' ' << r2 << '\n';
  cout << (r1 + r2) % mod << '\n';
}

signed main()
{
  int T;
  cin >> T;
  while (T --)
    solve();
  return 0;
}

```



---

## 作者：yinhee (赞：0)

[题目传送门](https://codeforces.com/contest/1731/problem/B)

## 解题思路：贪心

可以发现，每一次移动都会将 $i+j$ 的值 $+1$。所以每一个 $i+j$ 的值都只能取到一次。和一定，差小积大。所以 $i$ 和 $j$ 尽可能接近，走法即为下右下右重复。答案即为 $\sum_{i=1}^n i^2+\sum_{i=1}^{n-1}(i\times(i+1))$。利用公式可化为 $\frac{n\times(n+1)\times(2\times n+1)}6+\frac{(n-1)\times n\times(2\times n-1)}6+\frac{n\times(n-1)}2$。

code：

```cpp
ll n;
ll qpow(ll x,int y){
	ll ret=1;
	while(y){
		if(y&1)ret=ret*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ret;
}
void solve(){
	scanf("%lld",&n);
	ll a=n*(n+1)%mod*(2*n+1)%mod*qpow(6,mod-2)%mod,
	b=n*(n-1)/2%mod+n*(n-1)%mod*(2*n-1)%mod*qpow(6,mod-2)%mod;
	printf("%lld\n",(a+b)*2022%mod);
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：loser_seele (赞：0)

证明参考了官方题解。

我们的最优策略是每次向右向下移动，则答案为 $ \sum_{i=1}^n i^2+\sum_{i=1}^{n-1}i\times (i+1)=\frac{n(n+1)(4n+1)}{6} $。

这个数列是 [OEIS A002412](http://oeis.org/A002412)，直接套公式即可。

接下来证明为什么这样是对的：

设 $ d_{i,j} $ 表示到达 $ (i,j) $ 时候的最大答案，$ a_{a,b,c,d} $ 表示从 $ (a,b) $ 到 $ (c,d) $ 的路径长度，在下面的假设中总是保证路径唯一。

则显然有 $ d_{n-1,n-1} \geq d_{i,n-1}+a_{i+1,n-1,n-1,n-1}=d_{i,n-1}+\frac{(n-1-i)(n-1)^2}{2} $。

设 $ f_{i,j} $ 表示经过某个边界 $ (i,n) $ 到达 $ (n,n) $ 的最大答案，$ ans_{i,j} $ 表示按照上述策略行走路线得到的最大答案。则显然有 $ ans_{n,n}=d_{n-1,n-1}+n \times (n-1)+n^2,f_{n,n}=d_{i,n-1}+a_{i,n,n,n}=\frac{(n+1-i)(n+i)n}{2},d_{n,n}-f_{n,n}=d_{n-1,n-1}+n \times (n-1) + n^2-d_{i,n-1}-\frac{(n-1-i)(n-1)^2}{2} $，来自上面推出的式子。

于是 $ ans_{n,n}-f_{n,n} \geq d_{i,n-1}+\frac{(n+1-i)(n+i)n}{2}+n \times (n-1) + n^2-d_{i,n-1}-\frac{(n-1-i)(n-1)^2}{2} $，消去 $ d_{i,n-1} $，有 $ ans_{n,n}-f_{n,n} \geq \frac{(n+1-i)(n+i)n}{2}+n \times (n-1) + n^2-\frac{(n-1-i)(n-1)^2}{2}=\frac{2n^2-3n-n \times i-i-1}{2} $。

这里首先有当 $ i $ 在区间 $ [1,n-2] $ 中的时候，不难证明 $ \frac{2n^2-3n-n \times i-i-1}{2}\geq 0 $，所以发现 $ ans_{n,n} \geq f_{n,n} $，按照这个方法构造总是最优，得证。

关于取模问题：

首先不难发现 $ 2022 $ 是 $ 6 $ 的倍数，直接乘上 $ 337 $ 即可，当然这里是用乘法逆元实现。

时间复杂度 $ \mathcal{O}(T) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int p[4000040];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int ksm(int a,int b,int mod)
{
	int res=1;
	while(b)
	{
		if(b&1)
		res=res*a,res%=mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int sum[20000020];
const int mod=1e9+7;
signed main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		int n;
		cin>>n;
		int ans=n*(n + 1)%mod*(4*n - 1)%mod*ksm(6,mod-2,mod)%mod;
		cout<<ans*2022%mod<<'\n';
	}
}
```


---

