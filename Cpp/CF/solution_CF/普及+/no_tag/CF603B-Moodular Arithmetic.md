# Moodular Arithmetic

## 题目描述

As behooves any intelligent schoolboy, Kevin Sun is studying psycowlogy, cowculus, and cryptcowgraphy at the Bovinia State University (BGU) under Farmer Ivan. During his Mathematics of Olympiads (MoO) class, Kevin was confronted with a weird functional equation and needs your help. For two fixed integers $ k $ and $ p $ , where $ p $ is an odd prime number, the functional equation states that

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/ed6bc974175d6ded86ca0d36ce0ca4605575bbb9.png)for some function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/3d499b5681b890bdb5d1b1234e5b8d6e9d7e27b1.png). (This equation should hold for any integer $ x $ in the range $ 0 $ to $ p-1 $ , inclusive.)

It turns out that $ f $ can actually be many different functions. Instead of finding a solution, Kevin wants you to count the number of distinct functions $ f $ that satisfy this equation. Since the answer may be very large, you should print your result modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, $ p=3 $ and $ k=2 $ . The following functions work:

1. $ f(0)=0 $ , $ f(1)=1 $ , $ f(2)=2 $ .
2. $ f(0)=0 $ , $ f(1)=2 $ , $ f(2)=1 $ .
3. $ f(0)=f(1)=f(2)=0 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
25
```

# 题解

## 作者：jun头吉吉 (赞：6)

## 题意：
找出一组数$f\in\{0,1,\ldots,p-1\}$，使得$\forall x\in\{0,1,\ldots,p-1\}\text{，都有}f(x\times k \mod p)= k\times f(x) \mod p$，求$f$的组数
## 题解
数学老师说，要**分类讨论**
1. 显然，对于$k=0$的情况，$f(0\times x)=0\times f(x)=0$，故除了$f(0)=0$以外，所有的数都可以在$\{0,1,\ldots,p-1\}$中任选，答案为$p^{p-1}$
1. 对于$k=1$的情况，也很容易考虑，$f(1\times x)=1\times f(x)$，每一个$f(x)$的值互不影响，因此每个数都可以随便取，答案为$p^p$
1. 对于$k>1$的情况，稍微有点思维难度 ~~那也不至于评黑题呀~~

首先，对于$f(0)$，$f(k\times 0)=k\times f(0)$，
$$(k-1)f(0)=0\Rightarrow f(0)=0$$
因此在下面的讨论中不管$f(0)$

首先对于一个数$f(x)$，他可以影响到：
$$f(k\times x),f(k^2\times x),\ldots f(k^{(m-1)}\times x) \ \text{其中}k^m= 1 \mod p$$
因此一个数定下来后，能再影响$m$个值，一共有$p-1$个位置（不包括$0$），有$\frac {p-1} m$个环，每个环有$p$种可能，因此最终的答案为$p^{\frac {p-1} m}$

~~别问我怎么找$m$，问就是暴力~~
## 代码
```cpp
#pragma optimize(2)
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
typedef long long ll;
ll k,p;
const ll mod=1e9+7;
ll fpow(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1)ret=ret*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ret;
}
signed main(){
	read(p,k);
	if(k==0)write(fpow(p,p-1)),exit(0);
	if(k==1)write(fpow(p,p)),exit(0);
	int m=1;ll x=k;
	while(x!=1)
		m++,x=x*k%p;
	write(fpow(p,(p-1)/m));
}

```


---

## 作者：enyyyyyyy (赞：2)

- 思路：

   数学题！可以把 $1$ 到 $p$ 分组，每组之间互不干扰，，每一个组内都有 $p$ 中方案合法，最后乘起来即可。

- 提示：

	$k = 1$ 要特判，因为 $f(0)$ 可以取到 $0$。还有不要忘了取模。
    
- 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
typedef string st;
inline lint read() {
	lint s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(lint x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll k, p, ans = 1, cnt, op = 1;
int main() {
	p = read(), k = read();
	do {
		op = op * k % p;
		++cnt;
	} while (op > 1);//模拟快速幂
	for (ll i = 1; i <= (p - 1) / cnt; i++)
		ans = ans * p % 1000000007;//乘法
	if (k == 1) ans = ans * p % 1000000007;//特判
	print(ans);
	return 0;
}


```



---

## 作者：huangkx (赞：1)

## 闲话

模拟赛 $T 1$ 考了这题。和 $T 2$ 一起想了差不多 $2 h$ 后终于写出来了。

然后看到思路和题解区的大佬们的不太一样。可能会复杂一点，但思路应该更直观。

## 思路

### 当 $k = 0$ 时

显然，$f ( 0 ) = 0$，即 $f ( 0 )$ 的取值只有 $1$ 种；而 $f ( 1 ) , f ( 2 ) , \ldots , f ( p - 1 )$ 都可以为 $0 , 1 , \ldots , p - 1$，即它们的取值都有 $p$ 种。

所以答案为 $p ^ { p - 1 }$。

### 当 $k \geq 1$ 时

考虑建图：每个 $x$ 为结点，每个 $f ( x )$ 为结点 $x$ 的权值；对于每个条件 $f ( k \times x \bmod p ) \equiv k \times f ( x ) \pmod p$，可以转换成 $f ( k \times x \bmod p ) = k \times f ( x ) \bmod p$，然后连一条从 $x$ 到 $k \times x \bmod p$ 的边。

显然，每个结点有且仅有一条出边。定义两点 $u , v$ 连通表示从 $u$ 出发能到达 $v$ 或者从 $v$ 出发能到达 $u$。由若干个两两之间互相连通的点组成的极大集合为连通块。手玩一下可以发现，一个连通块中有且仅有一个环。

任意取某连通块中的一个结点，则一定能用它的权值递推出这个连通块中的环上每个结点的权值。显然，环上每个结点的权值可以被递推出若干遍。找到第一个权值被递推出两遍的结点，计算它的取值个数。设开始时的结点的权值为 $a$，第一个权值被递推出两遍的结点的权值为 $s \times a$，同时也是 $t \times a$，则可以列出方程 $s \times a \equiv t \times a \pmod p$。于是可以得出 $\mid s - t \mid \times a \equiv 0 \pmod p$，即 $\mid s - t \mid \times a \bmod p = 0$。对 $a$ 是否为 $0$ 分类讨论，设 $b = \frac { p } { \gcd ( p , \mid s - t \mid ) }$，仔细想想可以得出 $a$ 的取值有 $\lfloor \frac { p - 1 } { b } \rfloor + 1$ 种。注意如果 $\mid s - t \mid = 0$，这里的 $\gcd$ 就为 $p$。显然，对于每个确定的 $a$，可以对这个连通块中的每个结点找到确定的权值。所以这个连通块的取值就有 $\lfloor \frac { p - 1 } { b } \rfloor + 1$ 种。每个连通块的方案是独立的，所以把每个连通块的取值种数乘起来即为答案。

时间复杂度为 $\mathcal { O } ( p \log p )$，瓶颈在 $\gcd$。

## 问题

"对于每个确定的 $a$，可以对这个连通块中的每个结点找到确定的权值。"

这个结论真的对吗？

但是这份代码能 $AC$。

### Update：

这个结论是对的。因为由某个结点的权值推出其他结点的权值的过程可以分为两种情况：沿边的方向顺着推和逆着推。顺着推可以直接求值。逆着推相当于解一个线性同余方程 $a x \equiv b \pmod p$。而因为 $p$ 为质数，又由于 $a$ 相当于题目中的 $k$，在当前情况下 $1 \leq k \leq p - 1$，所以 $\gcd ( a , p ) = 1$。因此这个方程在模 $p$ 的完全剩余系 $\{ 0 , 1 , \ldots , p - 1 \}$ 中有且仅有一个解。综上所述，此结论是正确的。

参考资料：

[知乎——如何证明：任意自然数a,b,m；ax=b mod m 在Z_m中要么无解要么有gcd(m,a)个解？](https://www.zhihu.com/question/537420893)

[百度百科——线性同余方程](https://baike.baidu.com/item/%E7%BA%BF%E6%80%A7%E5%90%8C%E4%BD%99%E6%96%B9%E7%A8%8B/5544515)

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int o = 1, x = 0;
	char c = getchar();
	while('0' > c || c > '9'){
		if(c == '-') o = - 1;
		c = getchar();
	}
	while('0' <= c && c <= '9'){
		x = x * 10 + c - '0';
		c = getchar();
	}
	return o * x;
}
void write(int x)
{
	if(x < 0) putchar('-'), x = - x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e6;
int p, k;
bool vis[N + 1];
int now[N + 1];
inline int gcd(int a, int b)
{
	if(! a || ! b) return a + b;
	return __gcd(a, b);
}
int DFS(int i, int x)
{
	if(vis[i] && ! now[i]) return 1;
	if(now[i]){
		int res = (p - 1) / (p / gcd(abs(now[i] - x), p)) + 1;
		now[i] = 0;
		return res;
	}
	vis[i] = 1;
	now[i] = x;
	int res = DFS(k * i % p, k * x % p);
	now[i] = 0;
	return res;
}
void solve()
{
	const int P = 1e9 + 7;
	p = read(), k = read();
	if(k == 0){
		int ans = 1;
		for(int i = 1; i <= p - 1; i ++) ans = ans * p % P;
		write(ans), puts("");
	}else{
		int ans = 1;
		for(int i = 0; i <= p - 1; i ++) ans = ans * DFS(i, 1) % P;
		write(ans), puts("");
	}
}
signed main()
{
	int t = 1;
	while(t --) solve();
	return 0;
}
```

2023.8.23

update 2023.8.23 修改了部分公式；证明了一个结论。

---

## 作者：hgzxwzf (赞：1)

## [CF603B](https://codeforces.com/contest/603/problem/B)

注意到我们可以把 $1$ 到 $p$ 分组，每组之间互不干扰，既可以独立处理，每一个组内都有 $p$ 中方案合法，因为我们只需要关心每组的第一个数，知道第一个数后其他的数就都确定了，最后乘起来即可。

特判 $k=1$ 的情况，因为 $k=1$ 时 $f(0)$ 可以取 $0$。
### 代码：

```cpp
#include<cstdio>
#include<algorithm>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;
const int N=1e6+10,mod=1e9+7;

int ksm(int x,int y)
{
	int s=1;
	while(y)
	{
		if(y&1) s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}

bool bo[N];

int main()
{
	int p,k;
	scanf("%d%d",&p,&k);
	if(k==1) return printf("%d",ksm(p,p)),0;
	int ans=1;
	rep(i,1,p-1)
	{
		if(bo[i]) continue;
		for(int j=i;;)
		{
			if(bo[j]) break;
			bo[j]=1;
			j=1ll*j*k%p;
		}
		ans=1ll*ans*p%mod;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Anita_Hailey (赞：0)

**题意**，给你一个函数映射，其值域是 $0$ 至 $p-1$。这个函数满足，一个循环节的性质。

由于 $p$ 是质数。所以，$k^{p-1}$ 一定是模 p 余 1 的。所以我们只要所以这个 $m$，m是一个循环节，一定是 $p-1$ 的因数。于是，答案即为

- $k=0$ ，$ans=p^{p-1}$
- $k=1$ ，$ans =p^p$
- else $ans=p^{\frac{p-1}{m}}$



---

