# Fibonaccharsis

## 题目描述

Ntarsis 在他的生日的时候收到了两个整数 $n$ 和 $k$ 。他想知道有多少个长度为 $k$ 的斐波那契序列可以用 $n$ 作为序列的第 $k$ 个元素。

如果一个单调不降的非负整数序列 $f$，对任意的 $i > 2$，都有 $f_i=f_{i-1}+f_{i-2}$，则该序列被视为斐波那契类序列，其中 $f_i$ 表示序列中的第 $i$ 个元素。请注意，$f_1$ 和 $f_2$ 可以是任意的非负整数。

例如 $[4，5，9，14 ]$ 和 $[0，1，1]$ 被认为是斐波那契类序列，而 $[ 0，0，0，1，1]$ , $[1，2，1，3]$ 和 $[−1，−1，−2]$ 却不是：前两个并不总是满足 $f_i=f_{i-1}+f_{i-2}$ ，后者不满足元素是非负的。

通过帮助 Ntarsis 完成这项任务来打动他。

## 说明/提示

对于 $n=22$ , $k=4$ 有4种有效的斐波那契类序列:

- $[6,8,14,22]$ ，

- $[4,9,13,22]$ ，

- $[2,10,12,22]$ ，

- $[0,11,11,22]$ 。

对于 $n=3$，$k=9$，可以证明没有满足给定条件的斐波那契类序列。

对于 $n=55$，$k=11$， $[0,1,1,2,3,5,8,13,21,34,55]$ 是唯一类似斐波那契的序列。

## 样例 #1

### 输入

```
8
22 4
3 9
55 11
42069 6
69420 4
69 1434
1 3
1 4```

### 输出

```
4
0
1
1052
11571
0
1
0```

# 题解

## 作者：信息向阳花木 (赞：8)

这道题看起来很难的样子，特别是 $k$ 的范围，很令人绝望。不过我们不难发现，虽然 $k \le 10^9$，但只要 $k \ge 30$，无论如何 $f_k$ 都会大于等于 $2 \times 10^5$。您可以写一个暴力程序验算。

因此，当 $k \ge 30$ 时，直接输出 $0$ 即可。我们将 $k$ 的范围成功缩小到 $k \le 30$。这样我们就可以枚举了。

我们知道 $f_k = n$，我们只要枚举 $f_{k-1}$，利用 $f_i = f_{i + 2} - f_{i+1}$ 往前推算就可以了。如果对于任意的 $i$（$1 \le i \le k$），$f_i \ge 0$，那么这种情况成立。否则不成立。其实我们只需要判断 $f_1$ 是否大于等于 $0$ 即可。

时间复杂度 $O(nk)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
 
using namespace std;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int t, n, k;
int f[110];

int main()
{
	in(t);
	while (t -- )
	{
		int ans = 0;
		in(n); in(k);
		if(k >= 30)
		{
			puts("0");
			continue;
		}
		f[k] = n;
		for (int j = (n + 1)/ 2; j <= n; j ++ )
		{
			f[k - 1] = j;
			for (int i = k - 2; i >= 1; i -- )
			{
				f[i] = f[i + 2] - f[i + 1];
				if(f[i] < 0) { f[1] = -1; break; }
			}
			if(f[1] >= 0 && f[1] <= f[2]) ans ++;
		}
		printf("%d\n", ans); 
	}
	return 0;
}
```

---

## 作者：atomic_int (赞：5)

## 题意：

如果一个数列满足 $f_{i}=f_{i-1}+f_{i-2}$（即满足斐波那契数列的性质），就认为这是一个斐波那契数列。给定整数 $n,k$，设有一个长度为 $k$ 的数列 $f$，其中 $f_k=n$，请找出 $f$ 可以构造出多少种斐波那契数列（需要保证 $f$ 是单调不减的）。

## 分析：

- 一个显然的想法：一个满足斐波那契数列性质的数列，当 $i > 2$ 时的 $f_i$ 肯定是由多少个 $f_1$ 和多少个 $f_2$ 相加得到的。
- 因为斐波那契数列的性质是当 $i > 2$ 时 $f_{i}=f_{i-1}+f_{i-2}$，所以 $f_1$ 的个数就是 $f_{i-1}$ 中的 $f_1$ 的个数加上 $f_{i-2}$ 中的 $f_1$ 的个数，$f_2$ 同理，可以发现第 $i$ 项中的 $f_1$ 的数量和 $f_2$ 的数量也满足斐波那契数列的性质。
- 可以算出当 $k =1,2,3$ 时 $f_1$ 和 $f_2$ 分别有 $(1,0)$，$(0,1)$，$(1,1)$（第一项是 $f_1$ 的个数，第二项是 $f_2$ 的个数），可以发现 $f_1$ 和 $f_2$ 的数量就是斐波那契数列，第 $i$ 项中 $f_1$ 的个数是 ${\rm Fibonacci}(i-2)$，$f_2$ 的个数是 ${\rm Fibonacci}(i-1)$。（${\rm Fibonacci}(x)$ 表示斐波那契数列第 $x$ 项）
- 设 $a={\rm Fibonacci}(k-2)$，$b={\rm Fibonacci}(k-1)$，即 $f_1$ 和 $f_2$ 的数量，设 $x=f_1$，$y=f_2$，问题变成 $ax+by=n$ 中，$x,y \ge 0$ 且 $x \le y$ 的解的数量。

##  代码：

```cpp
void solve() {
    int n, k;
    cin >> n >> k;
    int a = fib(k - 2), b = fib(k - 1);
    int cnt = 0;
    for (int x = 0; x < n / a; x++) {
        int y = (n - a * x) / b;
        if (a * x + b * y == n && x >= 0 && y >= 0 && x <= y) cnt++;
    }
    cout << cnt << '\n';
}
```



---

## 作者：2huk (赞：4)

# [CF1853B Fibonaccharsis](https://codeforces.com/contest/1853/problem/B)

## Description

类斐波那契数列的定义如下：

- 单调递增；
- 不存在负数；
- $f_1,f_2$ 为非负整数；
- $f_n = f_{n - 1} + f_{n - 2}$。

求有多少个类斐波那契数列满足 $f_k = n$。

$t, n \le 2 \times 10^5$，$k \le 10^9$。

## Solution

首先~~容易~~发现，当 $k$ 过大时答案一定为 $0$。在 $k \ge 30$ 时，$f_k$ 是一定大于等于 $2 \times 10^5$。因此可以直接特判掉。

接下来 $k$ 就变得非常小，我们可以直接枚举 $k - 1$ 位填什么，倒着求出这个数列，再判断数列是否合法即可。

复杂度 $\mathcal{O}(kn)$。

## Code

```cpp
int Solve()
{
    n = read(), k = read();
    if (k > 30) return 0;

    f[k] = n;
    int res = 0;

    fup (i, 1, n)
    {
        f[k - 1] = i;
        fdw (j, k - 2, 1)
        {
            f[j] = f[j + 2] - f[j + 1];
            if (f[j] < 0)
            {
                f[1] = -114514;
                break;
            }
        }

        res += f[1] >= 0 && f[1] <= f[2];
    }

    return res;
}
```



---

## 作者：_Only_this (赞：3)

### CF1853B Fibonaccharsis 题解

------------

一眼又是不会的数论题，等等，这题是不是可以暴力模拟。。

------------

给定 $n$ 和 $k$，问有多少单调不降且非负的斐波那契数列的第 $k$ 项等于 $n$，统计方案数。

------------

既然 $f_k$ 都知道了，那就枚举一下 $f_{k-1}$，往前一直递推直到总项数等于 $k$，如果在递推的过程中条件不符合了，就跳出循环，最后统计一下答案即可。

思路很暴力，因为斐波那契数列往回跳是个 $\log$ 的，所以时间复杂度只有 $\operatorname{O}(n\log{n})$，不会超时。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,k;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		ll ans=0;
		for(int i=n;i>=0;i--){
			bool flag=0;
			int x=n,y=i,z;
			for(int j=1;j<=k-2;j++){
				z=x-y;
				if(z>y){
					flag=1;
					break;
				}
				x=y,y=z;
			}
			ans+=(!flag);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：mRXxy0o0 (赞：2)

此篇题解可以通过 $1\le t\le 2\times10^5,1\le n,k\le10^{18}$ ，不保证 $\sum n\le2\times 10^5$ 的数据~~（绝对不是因为没仔细看数据范围）~~。

# 题意

$t$ 组询问，每组给出 $n$ 和 $k$，求有多少个单调不递减且非负的类斐波那契数列满足 $f_k=n$。

# 分析

类斐波那契数列有性质：

$$f_n=f_1\times F_{n-2}+f_2\times F_{n-1}$$

其中，$F$ 表示以 $F_1=1,F_2=1$ 作为起始的斐波那契数列。它的证明方法可以使用定义 $f_n=f_{n-1}+f_{n-2}$，不断把下标大的一项展开成两项之和，具体过程这里就不细说了。

对于这道题，相当于求解方程 $f_1\times F_{k-2}+f_2\times F_{k-1}=n$。

题目中 $1\le k\le10^9$，似乎无法简单求出 $F_{k-2}$ 与 $F_{k-1}$ 的值~~（假装你不知道矩阵快速幂）~~。但是观察到，题目要求这个序列非负，所以 $n\ge F_{k-1}\ge F_{k-2}$。

可以得出结论，当 $F_{k-1}>n$ 时，答案为 $0$。就算当 $n=10^{18}$ 时，$k$ 最大只能取值为 $88$。

这样一来，就可以套上扩欧板子解出一组解 $(f_1',f_2')$。而对于这一类方程，有通解：

$$
\begin{cases}
f_1=f_1'-x\times\dfrac{F_{k-1}}{\gcd(F_{k-1},F_{k-2})}\\
f_2=f_2'+x\times\dfrac{F_{k-2}}{\gcd(F_{k-1},F_{k-2})}
\end{cases}
$$

易证，$\gcd(F_{k-1},F_{k-2})=1$，所以：

$$
\begin{cases}
f_1=f_1'-x\times F_{k-1}\\
f_2=f_2'+x\times F_{k-2}
\end{cases}
$$

由于题目要求，我们还需要满足 $0\le f_1\le f_2$。以下默认每算出一个 $x$，就按照上式更新一次 $(f_1,f_2)$。

考虑满足非负性，可以通过取模的方式得到一个使 $f_2\ge0$ 且 $f_2$ 最小的解，并相减算出增加的 $x$ 的值。

然后，如果不满足 $f_1\le f_2$，为了使 $f_2$ 满足上述条件且最小，可以得到 $x=\lceil\dfrac{f_2-f_1}{F_{k-1}+F_{k-2}}\rceil$。

观察通解形式，$f_2$ 随着 $x$ 的增大而增大，$f_1$ 随着 $x$ 的增大而减小，那么若 $x\ge0$，总是满足 $f_1\le f_2$。所以答案即为 $\lfloor\dfrac{f_1}{F_{k-1}}\rfloor+1$。

具体可以对照代码理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll N=2e5+10,inf=1e18;
ll T,n,k,f[N];
inline void init(){
	f[1]=f[2]=1;
	for(int i=3;;++i){
		f[i]=f[i-1]+f[i-2];
		if(f[i]>inf) break;
	}
}
inline ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
int main(){
	init();
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		int px=upper_bound(f+1,f+89,n)-f;
		ll x,y;
		if(k>px){
			puts("0");
			continue;
		}
		ll d=exgcd(f[k-2],f[k-1],x,y);
		if(n%d){
			puts("0");
			continue;
		}
		x*=n/d,y*=n/d;//解出一组解 
		ll t=((y%f[k-2]+f[k-2])%f[k-2]-y)/f[k-2];
		x-=t*f[k-1],y+=t*f[k-2];//让 f2 非负 
		if(x>y){//让 f1<=f2 
			t=(x-y+f[k-1]+f[k-2]-1)/(f[k-1]+f[k-2]);
			x-=t*f[k-1],y+=t*f[k-2];
		}
		if(x<0) {
			puts("0");
			continue;
		}
		printf("%lld\n",x/f[k-1]+1);
	}
	return 0;
}
```


---

## 作者：白简 (赞：1)

### 题目大意
对于一个类斐波那契数列，有以下定义：

1. 满足单调递增；
2. 每一项均为非负整数；
4. $f_n = f_{n - 1} + f_{n - 2}$。

求有多少个类斐波那契数列满足 $f_k = n$，其中 $t, n \le 2 \times 10^5$，$k \le 10^9$。
### 思路
$k$ 的范围十分吓人，但我们发现，斐波那契数列的第 $28$ 项是 $317811$，显然已经超过了 $2 \times 10^5$ 这个范围。

但还要考虑我们这个数列不是真正的斐波那契数列，可以有第一项为 $0$ 的情况，每一项会整体后移一位，所以当 $k \geq 29$ 时，答案为 $0$。

那么我们现在只需要考虑 $k \leq 28$ 的情况了，直接枚举前两项显然是不现实的，我们考虑换一个思路。

显然，对于这个数列，我们只要有其中两个相邻项的值，就可以递推求出每一项的值。

那我们可以枚举第 $k-1$ 项的值，递推求出前两项的值，判断前两项是否合法（非递减且为非负整数序列）。

### Code

```cpp
void Work() {
    cin >> n >> k;
    
    if(k >= 29) {
        cout << "0\n";
        return ;
    }
    
    f[k] = n;
    for(int i = 1;i <= n; i++) {   
        f[k - 1] = i;
        for(int j = k - 2;j >= 1; j--) 
            f[j] = f[j + 2] - f[j + 1];
        
        if(f[2] >= f[1] && f[1] >= 0)
            ans ++;
    }

    cout << ans << "\n";
    return ;
}
```



---

## 作者：Special_Judge (赞：1)

本蒟蒻的做法：扩展欧几里得

设这个序列的各项分别为 $f_1,f_2,f_3...f_k$，通过简单的手玩我们可以发现：
$$
f_3=f_1+f_2
$$

$$
f_4=f_1+2f_2
$$

$$
f_5=2f_1+3f_2
$$

$$
f_6=3f_1+5f_2
$$

观察 $f_1,f_2$ 的系数：$1,1,2,3,5...$，这个序列是不是有些熟悉？事实上，假设此处定义斐波那契数列为 $fib_1=0,fib_2=1,fib_i=fib_{i-1}+fib_{i-2}$，那么就有：
$$
f_k=fib_{k-1} \times f_1+fib_k \times f_2
$$
我们继续思考，题目中的$k\le10^9$，而斐波那契数列是指数级增长的，如果 $k$ 很大，这个式子的系数就会变得非常大。但是，这是斐波那契数列的前 $28$ 项：
$$
0\;1\;1\;2\;3\;5\;8\;13\;21\dots46368\;75025\;121393\;196418
$$
可以看到在第 $28$ 项的时候，就已经非常接近 $2 \times 10^5$ （ $n$ 的上界）了！在第 $29$ 项的时候就会超过。

$f_1,f_2$ 不可能都为零，否则数列的每一项都为零，但是 $n$（即 $f_k$）$\ge 1$。但只要 $f_1,f_2$ 有一项不为零，在数列的第 $29$ 项就一定会超过 $n$ 的上界，因此我们**可以直接将 $k \ge 29 $ 的情况排除**。

```cpp
if(k>28)
{
	printf("0\n");
	return ;
}
```



题目中已经给定了，$f_k=n$，并且有了上面的发现后，我们可以计算出 $ fib_{k-1}$ 和 $fib_k$ 并且保证它们不会超出`int`的上界。

于是我们就可以很愉快地用扩展欧几里得求解上述方程了，不会的可以看看[这里](https://oi-wiki.org/math/number-theory/linear-equation/)。

最终的答案就是方程的非负整数解的组数...吗？

实际上题目有**隐含条件**：$f_1 \le f_2$！

在下列推导中，为了简便，我记 $f_1=x,f_2=y,\gcd(fib_{k-1},fib_k)=g$。

首先，可以得出：若记 $d_x=\frac{fib_k}{g},d_y=\frac{fib_{k-1}}{g}$，且 $x_0,y_0$ 是原方程的一组解，那么对于任意 $t\in Z$，$x_0+td_x,y_0-td_y$ 都为原方程的一组解。我们先求出 $x$ 的最小非负整数值并计算出对应的 $y$ ，记这一组解为 $x',y'$，那么由 $x \le y$ 得 $x'+td_x \le y'-td_y$。因此 $t$ 的取值范围就是 $0 \le t \le \frac{y_0-x_0}{d_y+d_x}$。于是我们就知道了 $t$ 的整数值的个数，也就是这个方程符合要求的解的组数。

本人数论蒟蒻，很多地方都是一知半解，若您发现这篇题解的错误或您认为这篇题解还可以改进，请不吝赐教。

AC Code:

```cpp
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<vector>
#include<set>
#include<random>

#define MAXN_INT 2147483647
#define MAXN_LL 9223372036854775807

#define MOD A_NUMBER
#define N 101

//#define x0 SPJ1
//#define y0 SPJ2

#define mp make_pair

using namespace std;
long long T;
long long n,k;
long long fib[N];
long long x,y,g,dx,dy;
long long exgcd(long long a,long long b)//标准的扩展欧几里得
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	long long d=exgcd(b,a%b);
	long long temp=x;
	x=y;
	y=temp-a/b*y;
	return d;
}
void work()
{
	scanf("%lld%lld",&n,&k);
	if(k>28)//k>28直接不用看，不可能有解
	{
		printf("0\n");
		return ;
	}
	g=exgcd(fib[k-1],fib[k]);
	if(n%g!=0)//裴蜀定理，排除无解的情况
	{
		printf("0\n");
		return ;
	}
	
	x*=n/g;
	y*=n/g;
	
	dx=fib[k]/g;
	dy=fib[k-1]/g;
	
	x=(x%dx+dx)%dx;//求最小整数解
	y=(n-x*fib[k-1])/fib[k];//求对应的y
	
	cout<<1ll*floor((y-x)*1.0/(dx+dy)*1.0)+1<<endl;//赛时被printf的奇奇怪怪的问题折磨了一通之后换cout了
}
int main()
{
	fib[1]=0;
	fib[2]=1;
	for(long long i=3;i<=40;i++)
		fib[i]=fib[i-1]+fib[i-2];//预处理斐波那契额数列
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
} 
/*
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765 10946 17711 28657 46368 75025 121393 196418
*/
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题面](https://www.luogu.com.cn/problem/cf1853b)

[CodeForces 原题面](https://codeforces.com/contest/1853/problem/B)

给定 $n,k$。如果有一个数列满足 $f_i(i\ge3)=f_{i-1}+f_{i-2}$ 且 $f_2\ge f_1\ge0$，那么这是一个类斐波那契数列。求出有多少种可能的 $f_1,f_2$ 的取值，使得 $f_k=n$。

# 分析
首先最好想到的暴力枚举：枚举 $f_1,f_2$ 的取值，判断合法情况。但是此时的时间复杂度是 $O(n^2\times k)$ 的，显然不能通过。

首先想办法解决复杂度内与 $k$ 相关的问题。

我们来观察。

$f_1=1\times f_1 + 0\times f_2$ 

$f_2=0\times f_1 + 1\times f_2$

$f_3=f_1+f_2=1\times f_1+1\times f_2$

$f_4=f_2+f_3=f_1+2\times f_2$

$f_5=f_3+f_4=2\times f_1+3\times f_2$

$f_6=f_4+f_5=3\times f_1+5\times f_2$

$f_7=f_5+f_6=5\times f_1+8\times f_2$

$\dots$

可以发现，$f_i$ 的值为序列 $a_1=1,a_2=0,a_i(i\ge 3)=a_{i-2}+a_{i-1}$ 的第 $i$ 项乘 $f_1$ 加序列 $b_1=0,b_2=1,b_i(i\ge 3)=b_{i-2}+b_{i-1}$ 的第 $i$ 项。即 $f_i=a_i\times f_1+b_i\times f_2$.

那么 $O(k)$ 预处理出 $f_1,f_2$ 后，知道 $f_1,f_2$ 就可以 $O(1)$ 求解斐波那契数列的第 $i$ 项了。此时可以将时间复杂度优化为 $O(n^2)$。

但是还有一个问题：$k\ge 10^9$。但事实上，当 $k\ge 29$ 的时候，$a_k\ge317811$.

所以当 $k\ge 29$ 时，答案即为 $0$。

那么就只要最多预处理 $a_k,b_k$ 了！

> 笔者太菜了，做时只想到 $k\ge2\times 10^5$ 就一定没有解。

现在我们来解决复杂度内的 $n^2$。

注意到当 $f_1$ 一定时，$f_i(i\ge 3)$ 与 $f_2$ 成正比。

那么我们就可以枚举 $f_1$，二分 $f_2$ 即可。

时间复杂度：$O(n\log n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define no cout << "NO\n";
#define yes cout << "YES\n";
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, k;
int dpa[MAXN], dpb[MAXN];
void init(){
  dpa[1] = dpb[2] = 1;
  dpa[2] = dpb[1] = 0;
  for (int i = 3; i < MAXN; i++){
    dpa[i] = dpa[i - 1] + dpa[i - 2];
    dpb[i] = dpb[i - 1] + dpb[i - 2];
  }
}
void Solve(){
  cin >> n >> k;
  int ans = 0;
  if (k > 2e5){
    cout << "0\n";
    return ;
  }
  for (int i = 0; i <= n; i++){
    int l = i, r = n;
    while (l < r){
      int mid = (l + r + 1) >> 1;
      if (i * dpa[k] + mid * dpb[k] > n){
        r = mid - 1;
      }else {
        l = mid;
      }
    }
    if (i * dpa[k] + l * dpb[k] == n){
      ans++;
    }
  }
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  init();
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：ImposterAnYu (赞：0)

~~这篇题解是我在赛时写的，因为当时脑子要炸了，所以题解也写得很烂，请各位见谅。~~

设 
$$h_k=\begin{cases}{a}&k = 1\\{b}&k=2\\{h_{k - 1} + h_{k - 2}}&k>2\end{cases}$$

则我们的目标就是找到有多少组 $a,b(a < b)$ 使得 $h_k = n$。

我们从头开始推导：

$h_1 = a$

$h_2 = b$

$h_3 = h_1 + h_2 = a + b$

$h_4 = h_2 + h_3 = b + (a + b) = a + 2b$

$h_5 = h_3 + h_4 = (a + b) + (a + 2b) = 2a + 3b$

......

最后得到 $h_k = f_{k - 2} \times a + f_{k - 1} \times b$，其中

$$f_k=\begin{cases}{a}&k = 1\\{f_{k - 1} + f_{k - 2}}&k>2\end{cases}$$

所以我们的目标就变成了求 $f_{k - 2} \times x + f_{k - 1} \times y = n$ 的非负整数解的个数。

但是 $k$ 很大，暴力算 $f_{k}$ 会超时，就算用矩阵快速幂算也会因为溢出而导致答案错误。不过显然，$k$ 在过大的时候无解。具体地，设 $p$ 为满足 $g_{p} > n$ 的最小的 $p$，若 $k \geq p$，那么答案为 $0$。

其中

$$g_k=\begin{cases}{0}&k = 1\\{1}&k=2\\{g_{k - 1} + g_{k - 2}}&k>2\end{cases}$$

~~其实看得出来 $g$ 和 $f$ 之间的关系，但是这个彩笔脑子要炸了，所以没用 $f$ 表示 $g$~~

关于为什么 $k \geq p$ 时没答案，其实很容易想，因为 $h_k$ 的最小值就是 $g_k$（即 $a=0$，$b=1$），如果 $n$ 还没 $g_k$ 大的话，显然 $a,b$ 就不一定是非负整数了。

综上，如果 $k < p$ 的话，暴力找答案即可。

```cpp
#include<bits/stdc++.h>
#define int1 long long
#define N 500
#define mod 998244353
using namespace std;
int1 t,n,x,k,f[N + 5],p,a,b,yy,y,ans,i;//这个f数组其实算的是g（
void C(){//关同步。 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	return ;
}
int main(){
	C();
	cin >> t;
	f[1] = 0,f[2] = 1;
	for(i = 3; i <= 100; i++){
		f[i] = f[i - 1] + f[i - 2];//算g
	}
	while(t--){
		cin >> n >> k;
		p = upper_bound(f + 1,f + 101,n) - f;
		if(k >= p){//无解
			cout<< 0 << endl;
			continue;
		}
		a = f[k],b = f[k - 1],ans = 0;
		for(x = 0; x <= n; x++){
			yy = n - x * b;
			if(yy < 0){//x不能太大，不然y就会变成负数
				break;
			}
			if(!(yy % a)){//y是非负整数
				y = yy / a;
				if(x > y){//必须要a<=b
					break;
				}
				ans++;
			}
		}
		cout<< ans << endl;
	}
	return 0;
}
```

---

## 作者：Charlie1202 (赞：0)

# 题意
给定正整数 $n$，$k$，求有多少种不同的数列，满足数列的第 $k$ 项为 $n$，数列中每一个数非负且不超过 $2 \times 10^5$，从第三项开始，每一项等于前两项之和。

# 分析
注意到符合题意的数列一定单调递增，因此第 $k$ 项即 $n$ 一定是所构造数列的最大值，又由于 $n \le 2 \times 10^5$，$k$ 的值不可能很大。

考虑让前几项的值尽可能小，这样最后一项的值也会小，而最小就是斐波那契数列：$[0,1,1,2,3,5 \dots]$，写个简单程序递推几项可以发现：它的第 $28$ 项为 $196418$，而第 $29$ 项为 $317811$，已经超出数据范围。由于这是最小的第 $29$ 项了，扩展到一般情况，只可能更大，因此，当 $k \ge 29$ 时，一定不存在符合题意的数列。

数据范围缩小后，就可以暴力枚举了，顺着推比较困难，考虑逆推，注意到由于对 $\forall i \ge 3$，都有 $f_i = f_{i-1} + f_{i-2}$，且数列递增，所以当 $f_i$ 确定时，$f_{i-1}$ 最小为 $\dfrac{f_i}{2}$，此时 $f_{i-2} = f_{i-1}$。

对应到题目中，我们可以在已知 $f_k = n$ 的情况下，逆推出整个序列，判断是否符合题意，枚举起点就是 $f_{k-1} = \dfrac{n}{2}$ 到 $f_{k-1} = n$ ，递推式为 $f_i = f_{i+2} - f_{i+1}$，判断条件就是任意一项都要非负。

但这样做还有漏洞。根据递推式，对于一个整数 $f_{i+2}$，若 $f_{i+1} < \dfrac{f_{i+2}}{2}$，那么作差后一定有 $f_{i} > \dfrac{f_{i+2}}{2}$，此时 $f_i > f_{i+1}$，也要舍去。这一条可以用样例 $1$ 验证，在数列 $[6,8,14,22]$ 之后，枚举的数列为 $[8,7,15,22]$，不符合递增条件，故舍去。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[100];
signed main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		if(k>=29)
		{
			cout<<0<<"\n";
			continue;
		}
		f[k]=n;
		int flag=0,cnt=0;
		for(int i=n/2;i<=n;i++)
		{
			f[k-1]=i;
			for(int j=k-2;j>=1;j--)
			{
				f[j]=f[j+2]-f[j+1];
				if(f[j]<0||f[j]>f[j+1])//由于数列递增，有一项为负则前面所有项一定为负，不用算了；
                				//同理，存在递减部分就不符合，之后的数列也不可能符合，直接舍去
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				flag=0;
				continue;
			}
			cnt++;
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```


---

