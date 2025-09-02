# One or All

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2019/tasks/kupc2019_k

アンジェは変数で遊ぶのが好きです。

今日は $ 3 $ つの変数 $ x,~y,~z $ を用意して、これらを使って遊ぶことにしました。 $ 3 $ つの変数は $ 0 $ で初期化されています。

アンジェは、これらの変数に対して、以下の操作のいずれかを選んで行うことを $ n $ 回繰り返すつもりです。

- 変数を $ 1 $ つ選ぶ。その変数の値を $ 1 $ 増やす、もしくは $ 1 $ 減らす。
- $ 3 $ つの変数全ての値を $ 1 $ ずつ増やす、もしくは $ 1 $ ずつ減らす。

$ n $ 回の操作を行ったあとに、$ x,~y,~z $ を $ m $ で割った余りがそれぞれ $ p,~q,~r $ であるとき、 アンジェは満足します。

アンジェは、自分が満足できるような $ n $ 回の操作列が何種類あるのかに興味を持ちました。 彼女の代わりに、そのような操作列の種類数を数えて、$ 998244353 $ で割った余りを出力してください。

ここで $ 2 $ つの操作列は、ある整数 $ i\ (1\ \leq\ i\ \leq\ n) $ が存在して、$ i $ 回目の操作後に $ 1 $ つ以上の変数の値が異なるとき、別の種類であるとみなします。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ n\ \leq\ 10^6 $
- $ 1\ \leq\ m\ \leq\ 10^6 $
- $ 0\ \leq\ p,\ q,\ r\ <\ m $

### Sample Explanation 1

$ 1 $ 回の操作で、ある $ 1 $ つの変数の値だけを $ 1 $ 増やし、残り $ 2 $ つの変数の値を $ 1 $ 減らすことはできません。

### Sample Explanation 2

まず、$ 3 $ つすべての変数の値を $ 1 $ 減らします。次に $ x $ の値だけを $ 1 $ 減らすことで、$ x $ の値は $ -2 $、 $ y $ の値は $ -1 $、$ z $ の値は $ -1 $ になります。 これらを $ 3 $ で割った余りはそれぞれ $ 1,~2,~2 $ であるため、アンジェはこの操作列に満足します。 アンジェが満足する操作列は、この操作列を含めて $ 2 $ 種類あります。

## 样例 #1

### 输入

```
1 3 1 2 2```

### 输出

```
0```

## 样例 #2

### 输入

```
2 3 1 2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
1000000 4 1 2 3```

### 输出

```
333551635```

# 题解

## 作者：wangziyue_AK (赞：3)

## 声明：
本做法是 SSerxhs 在讲课时教授的。该做法较为清晰易懂且不需要生成函数。
## Part one：
题目中描述的运动是在三维坐标系中将三个坐标同时加一或减一，或者挑选一个坐标加一或减一。可以发现一个有八种不同的运动方式。我们直接做要枚举每类运动或每一维度的情况，复杂度较高，所以考虑能否将每一维度独立开。可以使用[这题](https://www.luogu.com.cn/problem/AT_abc221_g)或者[这题](https://www.luogu.com.cn/problem/AT_abc240_g)的做法，对坐标进行一些线性变换使得每一维的移动不对其他维产生影响。对于二维挑选一个坐标加一或减一的情况构造 $a=x+y,b=x-y$ 即可，四种运动就变成了横纵坐标分别加一或减一。那这题正好有 $8$ 种运动，猜测可以跟三维坐标分别加一或减一的 $2^3=8$ 种变换互相转化。考虑对于 $a,b,c$ 分别等于 $x,y,z$ 带上 $0,1,-1$ 之一的系数然后求和，可以找到一组合法构造：
$$a=x+y-z,b=x+z-y,c=y+z-x$$

容易验证上述构造合法，此时三维独立，可以分别计算。
在目标点为 $(x,y,z)$ 时答案为：
$$\binom{n}{(n-|x|)/2}\binom{n}{(n-|y|)/2}\binom{n}{(n-|z|)/2}$$
注意除法均为整除，除不尽即答案为 $0$。
## Part two：
上述做法在不取模且终点固定时已经可以计算了，对于取模的情况容易想到枚举每一维分别加或减了几次 $m$ 并进行计算，复杂度 $O(n+\frac{n}{m})$ 可以接受。但会发现一个问题：变换后坐标模 $m$ 同余是否等价于变换前坐标同余？验证后可以发现它只意味着变化前点 $2x,2y,2z$ 模 $m$ 同余，在 $m$ 为偶数时并不意味 $x,y,z$ 模 $m$ 同余。考虑计算了哪些点：
$$(x,y,z),(x+m/2,y,z),(x,y+m/2,z),(x,y,z+m/2)$$
有一个人类智慧做法，把模数换成 $2m$，计算的点变成了下面的：
$$(x,y,z),(x+m,y,z),(x,y+m,z),(x,y,z+m)$$
它们都属于合法点对，但还不完全，还差了如下点对：
$$(x+m,y+m,z+m),(x+m,y+m,z),(x,y+m,z+m),(x+m,y,z+m)$$
对 $(x+m,y+m,z+m)$ 再求解一次并加入答案即可。
## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef double db;
#define pb push_back
#define eb emplace_back
#define bcnt __builtin_popcount
#define TS printf("!!!tiaoshi\n")
const int p=998244353;
const int N=2e6+5;
inline void add(int &x,int y){
	(x+=y)>=p&&(x-=p);
}
inline void del(int &x,int y){
	(x-=y)<0&&(x+=p);
}
inline void mul(int &x,int y){
	x=(1ll*x*y)%p;
}
int f[N],inv[N],finv[N];
void init(){
	f[0]=finv[0]=1;
	f[1]=finv[1]=inv[1]=1;
	for(int i=2;i<=N-5;i++){
		inv[i]=1ll*(p-p/i)*inv[p%i]%p;
		f[i]=1ll*f[i-1]*i%p;
		finv[i]=1ll*finv[i-1]*inv[i]%p;
	}
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	return (1ll*(1ll*f[n]*finv[m])%p*finv[n-m])%p;
}
int n;
inline int get(int x){
	x=abs(x);
	if(x>n||(n-x)&1) return 0;
	//printf("get:%d %d %d\n",n,x,C(n,(n-x)>>1));
	return C(n,(n-x)>>1);
}
inline int qiu(int x,int mod){
	int res=0;
	for(int i=x;i<=n;i+=mod) add(res,get(i));
	for(int i=x-mod;i>=-n;i-=mod) add(res,get(i));
	//printf("qiu:%d %d %d\n",x,mod,res);
	return res; 
}
inline int sol(int x,int y,int z,int mod){
	int res=1;
	mul(res,qiu(x,mod)),mul(res,qiu(y,mod)),mul(res,qiu(z,mod));
	return res;
}
int m,x,y,z,ans;
void sol(){
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&z);init();
	int nx=x+y-z,ny=x+z-y,nz=y+z-x,m2=(m<<1);
	add(ans,sol(nx,ny,nz,m2)),add(ans,sol(nx+m,ny+m,nz+m,m2));
	printf("%d",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=1;
	//scanf("%d",&T);
	while(T--) sol();
	return 0;
}

```

---

## 作者：NaCly_Fish (赞：3)

简单分析题意，就知道我们要对于多项式
$$F=(x+1/x+y+1/y+z+1/z+xyz+1/(xyz))^n$$
求出
$$F \bmod (x^m-1)\bmod (y^m-1)\bmod (z^m-1)$$
的 $[x^py^qz^r]$ 这一项系数。首先我们可以对 $F$ 因式分解：
$$F=\left(\frac{(1-xy)(1-xz)(1-yz)}{xyz}\right)^n$$
然后分别求出 $(1-xy)^n$、$(1-xz)^n$、$(1-yz)^n$ 进行三次取模后的结果，容易得到其分别为 $G(xy)$、$G(xz)$ 和 $G(yz)$，其中
$$G(t)=(1-t)^n\bmod (t^m-1)$$
令 $p\leftarrow(p+n)\bmod m$，$q\leftarrow(q+n)\bmod m$，$r\leftarrow(r+n)\bmod m$，则答案为
$$\sum_{i,j,k}[(i+j)\bmod m =p][(i+k)\bmod m = q][(j+k)\bmod m =r]g_ig_jg_k$$
由于 $i,j,k$ 的取值范围都在 $[0,m-1]$ 内，能使得三个条件括号全部满足的只有 $\Theta(m)$ 组。因为只要枚举 $i$，满足 $(i+j)\bmod m =p$ 的 $j$ 最多只有两个，然后再解出 $k$ 即可。

直接计算，时间复杂度就是 $\Theta(n+m)$ 的。

---

## 作者：denominator (赞：1)

> [原题 in luogu](https://www.luogu.com.cn/problem/AT_kupc2019_k) / [原题 in atcoder](https://atcoder.jp/contests/kupc2019/tasks/kupc2019_k)
> - 有三个变量 $x,y,z$，初始值均为 $0$。
> - 有多少种经过 $n$ 次操作的方式（对 $998\ 244\ 353$ 取模），且每次操作在以下 $8$ 种操作之一：
>   - 将 $x,y,z$ 中的一个数 $\pm1$；
>   - 将 $x,y,z$ 中的所有数 $\pm1$，
> - 使得操作后：
>   - $x\equiv p\pmod m$； 
>   - $y\equiv q\pmod m$； 
>   - $z\equiv r\pmod m$？
> - $1\leq n,m\leq10^6$，$0\leq p,q,r<m$。

~~指责鰰把正负号写反了（（（~~

~~虽然我没发现（（（~~

这篇题解使用 ~~将鰰的生成函数做法转换成的~~ 组合语言叙述。

列出 $(\Delta x,\Delta y,\Delta z)$（$x,y,z$ 在一次操作前后变化量）的表（用 $+$ 表示 $+1$，$-$ 表示 $-1$）：

|$\bm{\Delta x}$|$\bm{\Delta y}$|$\bm{\Delta z}$|
|:-:|:-:|:-:|
|$-$|$-$|$-$|
|$-$|$0$|$0$|
|$0$|$-$|$0$|
|$0$|$0$|$-$|
|$0$|$0$|$+$|
|$0$|$+$|$0$|
|$+$|$0$|$0$|
|$+$|$+$|$+$|

毫无规律啊……

但是有一个规律：操作的数的数量均为 **奇数**。

另外一个注意是，行数 $8=2^3$？是否可以和某个 $2$ 和 $3$ 联系在一起？

又发现这里没用一个恒同变换，做起来比较麻烦。

你会发现有负，钦定一次操作后同时加一，**同时让 $\bm{p=(p+n)\bmod m}$，$\bm{q=(q+n)\bmod m}$，$\bm{r=(r+n)\bmod m}$**。这样 $\Delta x+\Delta y+\Delta z$ 就会成为一个 **偶数**，好像有匹配的希望？

|$\bm{\Delta x}$|$\bm{\Delta y}$|$\bm{\Delta z}$|
|:-:|:-:|:-:|
|$0$|$0$|$0$|
|$0$|$1$|$1$|
|$1$|$0$|$1$|
|$1$|$1$|$0$|
|$1$|$1$|$2$|
|$1$|$2$|$1$|
|$2$|$1$|$1$|
|$2$|$2$|$2$|

果然：
- $(0,0,0)=\varepsilon$；
- $(0,1,1)=(0,1,1)$；
- $(1,0,1)=(1,0,1)$；
- $(1,1,0)=(1,1,0)$；
- $(1,1,2)=(0,1,1)+(1,0,1)$；
- $(1,2,1)=(0,1,1)+(1,1,0)$；
- $(2,1,1)=(1,0,1)+(1,1,0)$；
- $(2,2,2)=(0,1,1)+(1,0,1)+(1,1,0)$。

也就是说，**一个操作一定可以被拆分为 $\bm{(0,1,1),(1,0,1),(1,1,0)}$ 三种操作中的任意几个**。

设拆分后，$(0,1,1),(1,0,1),(1,1,0)$ 的操作次数为 $i,j,k$，则：

- $j+k\equiv p\pmod m$；
- $k+i\equiv q\pmod m$；
- $i+j\equiv r\pmod m$。

有人说，那你给出 $i,j,k$ 也没用啊，一个符合的 $i,j,k$ 可以对应多个操作。你说得对，但是我们可以发现，对于 $n$ 次操作的每一次操作，我们都可以选择：把 $(0,1,1)$ 叠加于这次操作，或者不把 $(0,1,1)$ 叠加于这次操作。所以我们要叠加 $i$ 次 $(0,1,1)$ 于最终的操作中，一共有 $\dbinom{n}{i}$ 种可能！

对于 $(1,0,1)$ 与 $(1,1,0)$，均类似，于是答案就呼之欲出了：

$$
\sum_{\substack{0\leq i,j,k\leq n\\j+k\equiv p\pmod m\\k+i\equiv q\pmod m\\i+j\equiv r\pmod m}}\dbinom{n}{i}\dbinom{n}{j}\dbinom{n}{k}
$$

我觉得这个柿子不太好看，替换了一下 $i,j,k$ 的顺序：

$$
\sum_{\substack{0\leq i,j,k\leq n\\i+j\equiv p\pmod m\\i+k\equiv q\pmod m\\j+k\equiv r\pmod m}}\dbinom{n}{i}\dbinom{n}{j}\dbinom{n}{k}
$$

其实左边很大的 $\sum$ 是可以直接枚举的。

- 枚举 $i$，有 $j\equiv p-i\pmod m$，$k\equiv q-i\pmod m$；
- 因为 $0\leq j,k\leq n$，$j,k$ 均有 $\mathcal O\left(\dfrac{n}{m}\right)$ 种可能；
- 判断 $j+k\equiv r\pmod m$ 是否成立；
- $\mathcal O\left(\dfrac{n^2}{m^2}\right)$ 地求出所有满足要求的三元组 $(i,j,k)$，可以 $\mathcal O(n)-\mathcal O(1)$ 地计算 $\dbinom{n}{i}\dbinom{n}{j}\dbinom{n}{k}$；
- 总时间 $\mathcal O\left(\dfrac{n^3}{m^2}\right)$，$n$ 很大、$m$ 很小时不能通过（比如样例三会卡死）。

看到这个时间复杂度，可能有人已经开始往根号分治上想了（？）。但是这个柿子可以进一步预处理化简！

令 $a_i=\sum\limits_{\substack{0\leq j\leq n\\j\equiv i\pmod m}}\dbinom{n}{j}$，这个可以简单地 $\mathcal O(n)$ 预处理求出，那么原式即：

$$
\sum_{\substack{0\leq i,j,k< m\\i+j\equiv p\pmod m\\i+k\equiv q\pmod m\\j+k\equiv r\pmod m}}a_i\cdot a_j\cdot a_k
$$

好处是 $i,j,k$ 的上界变为了 $m-1$，这下 $j,k$ 只有一种可能了！~~（再次指责鰰，这里应当为一而非二~~

总时间为 $\mathcal O(n+m)$。代码特别简洁。

~~点评：不用生成函数太人类智慧了，大家还是用生成函数做法吧。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;
const ll mod = 998244353;
int n, m, p, q, r;
ll fac[N], ifac[N], a[N], ans;
int main () {
	scanf ("%d%d%d%d%d", &n, &m, &p, &q, &r);
	(p += n) %= m, (q += n) %= m, (r += n) %= m;
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) {
		ifac[i] = ifac[mod % i] * (mod - mod / i) % mod;
	}
	for (int i = 2; i <= n; i++) {
		fac[i] = (fac[i - 1] * i) % mod;
		(ifac[i] *= ifac[i - 1]) %= mod;
	}
	for (int i = 0; i <= n; i++) {
		a[i] = fac[n] * ifac[i] % mod * ifac[n - i] % mod;
	}
	for (int i = m; i <= n; i++) {
		(a[i % m] += a[i]) %= mod;
	}
	for (int i = 0; i < m; i++) {
		int j = (p - i + m) % m, k = (q - i + m) % m;
		if ((j + k) % m != r) {
			continue;
		}
		(ans += a[i] * a[j] % mod * a[k] % mod) %= mod;
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

