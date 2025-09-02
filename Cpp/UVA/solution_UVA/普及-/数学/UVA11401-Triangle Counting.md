# Triangle Counting

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2396

[PDF](https://uva.onlinejudge.org/external/114/p11401.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11401/5eaa7dd447e7d2ae45ba394b0c6ba6a37f3cba8d.png)

## 说明/提示

给定$n$条边，长度分别为$1,2,3,...,n$。用其中三条边构成一个三角形，有多少种不同的方案？注意，一条边只能使用一次。

**输入格式**

每行输入包含一个数字$n(3 \leq n \leq 10^6)$，含义如上所示。
结束标志为$n <3$。

**输出格式**

对于每组数据，输出如前所述的方案数。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
5
8
0```

### 输出

```
3
22```

# 题解

## 作者：论文 (赞：14)

**结论**：苯题存在 $O(1)$ 做法。


先求不可行的，因为总方案（无序）易知为：

$$
\frac{n(n-1)(n-2)}{6}
$$

最后输出答案时求个补即可。

枚举两条小的边之和，则不可行的方案数为：

$$
S=\sum\limits_{i=3}^n((n-i+1)\times\lfloor\frac{i-1}{2}\rfloor)
$$

则

$$
\begin{aligned}

2S&=\sum\limits_{i=2}^{n-1}((n-i)\times(2\times\lfloor\frac{i}{2}\rfloor)) \\
&=\sum\limits_{i=2}^{n-1}((n-i)\times(i-[i\equiv 1\mod 2])) \\
&=\sum\limits_{i=2}^{n-1}((n-i)\times i)-\sum\limits_{i=2}^{n-1}[i\equiv 1 \mod 2] (n-i)

\end{aligned}
$$

而 $ \sum\limits_{i=0}^{m}i^k $ 这样形式的和式可以用扰动法或者其它科技机械化地求出封闭形式。特别地，此处 $k=2$ 时，用扰动法给出推导：

$$
\begin{aligned}

\sum\limits_{i=0}^{m}i^3&=\sum\limits_{i=0}^m (i+1)^3-(m+1)^3\\
&=\sum\limits_{i=0}^m(i^3+3i^2+3i+1)-(m+1)^3\\

\implies 0 &=\sum\limits_{i=0}^m(3i^2+3i+1)-(m+1)^3 \\
\implies \sum\limits_{i=0}^mi^2 &= \frac{m(m+1)(2m+1)}{6}\\



\end{aligned}
$$

所以 $S$ 是可以 $O(1)$ 算的。

------------

最后结果我写在草稿纸上，忘了，为了证明我没在乱口胡，应该输出的结果其实就是：

```cpp
n*(n-1)*(n-2)/6-(n*(n+1)*(n-2)/2-(n-1)*n*(2*n-1)/6+1-n*(n/2-1)+((n-1<=2)? 0:((4+(n-2)/2*2)*(((n-2)/2*2-2)/2+1)/2)))/2
```

---

## 作者：hyjdouSHEN (赞：7)

[原题传送门](https://www.luogu.com.cn/problem/UVA11401)

## 题目分析
三重循环的时间复杂度为 $\Theta(n^{3})$，采用暴力肯定超时。这样的规模即使是 $\Theta(n^{2})$ 时间的算法都很难承受，那么只能进行一些数学分析了。

用加法原理，设最大边长为 $x$ 的三角形有 $c(x)$ 个，另外两条边长分别为 $y$ 和 $z$，根据三角形两边之和大于第三边有 $y+z>x$。所以 $z$ 的范围是 $x-y<z<x$。

根据这个不等式，可得： $y=1$ 时 $x-1<z<x$，显然无解； $y=2$ 时只有一个解 $z=x-1$； $y=3$ 时有两个解，以此类推，直到 $y=x-1$ 时有 $x-2$ 个解。根据等差数列求和公式，一共有 $(x-1)(x-2)/2$ 个解。

可惜，这并不是 $c(x)$ 的正确数值，因为上面的解包含了 $y=z$ 的情况，而且每个三角形算了两边。解决方法很简单，这里就留给读者去思考了。

原题要求的实际上是最大边不超过 $n$ 的三角形数目 $f(n)$。根据加法原理，可知 $f(n)=c(1)+c(2)+...+c(n)$。代码如下。 

## 代码部分

```cpp
#include<iostream>
using namespace std;
long long f[1000010];//不开long long见祖宗 
int main()
{
	f[3]=0;
	for(long long x=4;x<=1000000;x++)
		f[x]=f[x-1]+((x-1)*(x-2)/2-(x-1)/2)/2;  //递推 
	int n;
	while(cin>>n){
		if(n<3) break;
		cout<<f[n]<<endl;
	}
	return 0;
}
```
希望这篇题解对你有帮助

---

## 作者：Mutsumi_0114 (赞：7)

本题根据数据范围可看出大概是$O(N)$或$O(Nlog(N))$复杂度算法。

考虑打表找规律：

```cpp
#include <cstdio>
using namespace std;
int main()
{
	int ans=0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(i+j>k)
					ans++;
	printf("%d",ans);
	return 0;
}
```

得出如下数列：

```
N   : 3 4 5 6 7  8  9  10 11 12 13  14
ans : 0 1 3 7 13 22 34 50 70 95 125 161
```

观察$ans$相邻两项差值得到如下数列：

```
x : 1 2 4 6 9 12 16 20 25 30 36
```

不难发现数列$x$中奇数项为平方数，偶数项为相邻两整数乘积的平方根。

我们根据找到的规律先打出初步代码：

```cpp
#include <cstdio>
using namespace std;
int n;
long long ans;
int main()
{
	scanf("%d",&n);
	while(n>=3)
	{
		ans=0;
		long long k=n/2-1;
		for(long long i=1;i<=k;i++)
			ans+=i*i;
		for(long long i=1;i<k;i++)
			ans+=i*(i+1);
		if(n%2)
			ans+=k*(k+1);//若n为偶，则x数列末项为平方数，反之则为相邻整数乘积
		printf("%lld\n",ans);
		scanf("%d",&n);
	}
	return 0;
}
```

有了这个程序之后，为了保险，将它与暴力程序对拍。因为刚才暴力的复杂度为$O(N^3)$，所以可以尝试数据$N=1000$，$N=999$（为了保险可以再稍微大一些），发现答案无误，可以确定规律无误。

做完之后了解到正解递推为：

$f[x]$ 表示前$x - 1$个数中两个数的和大于$x$的方案数，$f[x] = f[x-2] + x - 3$。

具体的证明通过数学可以简单证得：

### ([OEIS](https://oeis.org/search?q=1%2C3%2C7%2C13%2C22%2C34%2C50%2C70%2C95%2C125%2C161&language=english&go=Search))

### 2019-7-22：修改错误“乘积的平方根”一处

---

## 作者：M_seа (赞：4)

O(n)递推

f[x] 表示前x-1个数中两个数的和大于x的方案数

f[4] = 1 (2+3)  ->  1

f[5] = 2 (2+4, 3+4) -> 2

f[6] = 4 (2+5, 3+5, 4+5, 3+4) -> 3+1

f[7] = 6 (2+6, 3+6, 4+6, 5+6, 3+5, 4+5) -> 4+2

····

所以得到递推式子 f[x] = f[x-2]+i-3
再统计前缀和

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[1000010];
int main()
{
    int n;
    for(int i = 4; i <= 1000000; i++)
        f[i] = f[i-2] + i-3;
    for(int i = 4; i <= 1000000; i++)
        f[i] += f[i-1];
    while(scanf("%d", &n) && n>=3)
        printf("%lld\n", f[n]);
    return 0;
}

```


---

## 作者：fanfansann (赞：3)

**Problem B Triangle Counting**（[UVA11401](https://www.luogu.com.cn/problem/UVA11401) ）


给定 $n$ 条边，长度分别为 $1,2,3,...,n$ 。用其中三条边构成一个三角形，有多少种不同的方案？注意，一条边只能使用一次。

$n\le 10^6$

**Solution**

计算能组成三角形的选择方案数，为了补充不漏的计数，我们可以考虑固定三角形中的最长边 $x$，讨论另外两条边 $y, z$ 的情况。

发现我们有且只有一个能用的性质：三角形中，两边之和大于第三边。

假定我们已知 $x$ ，则有：
$$
y+z>x
$$
对于当前的 $x$，考虑合法的 $y$ 的范围，显然有：

$$x-z<y<x$$

尝试讨论：当 $y=1$ 时，显然 $z$ 无解。当 $y=2$ 时，$z$ 只有 $1$ 个解：$x-1$；当 $y=3$ 时 $z$ 有 $2$ 个解：$x-2,x-1$， $\cdots$，当 $y=x-1$，$z$ 有 $x-2$ 个解：$2,3,\cdots,x-1$。显然方案数呈等差数列，故总的解数为：
$$
\dfrac{(x-1)(x-2)}{2}
$$
现在是满足 $y+z>x$ 的方案数，但是题目中规定每条边只能只用一次，所以要去掉 $y=z$ 的情况：
$$
\begin{aligned}&y=z,x-z<y<x
&\\&\Rightarrow x-y<y \Rightarrow y>\frac{x}{2}&\\&
\Rightarrow\frac{x}{2}<y<x&\\&\Rightarrow \frac{x}{2}+1\le y\le x-1\end{aligned}
$$
则共有 $x-1-(\dfrac{x}{2}+1)+1=\dfrac{x+2}{2}$ 种情况。

题目规定必须是不同的三角形，即 $y=10,z=5$ 与 $z=5,y=10$ 是同种方案，所以最后答案需要再除以二。



综上所述，答案 $f(x)$ 表示最长边为 $x$ 时，可以组成的不同的三角形的方案数：
$$
f(x)=\dfrac{\dfrac{(x-1)(x-2)}{2}-\dfrac{x+2}{2}}{2}=\dfrac{(x+2)^2}{4}
$$
那么对于数列 ${1,2,\cdots n}$，总方案数显然为 $\sum\limits_{i=3}^{n}f(i)$ 。前缀和预处理即可。



**Code**

```cpp
// Problem: UVA11401 Triangle Counting
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/UVA11401
// Memory Limit: 0 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
const int N = 2e6 + 7;

int n, m, s, t, k, ans, a[N];
ll f[N];
	
void prework(int x) 
{
	f[1] = f[2] = 0;
	for (int i = 3; i <= x; ++ i) {
		f[i] = f[i - 1] + 1ll * (i - 2) * (i - 2) / 4;
	}
}

int main()
{
	prework(N - 5);
	while(scanf("%d", &n) != EOF && n) {
		if(n < 3) return 0;
		cout << f[n] << endl; 
	}
	return 0;
} 
```



---

## 作者：gb530 (赞：2)

### 题意：1~n中取三数，能够成三角形的个数
### O($x^{3}$)枚举明显炸，O($x^{2}$)也不行，便想到数学推导
### $\because$ y+z>x 
### $\therefore$ x-y<z<x
### $\therefore$ x=1无解，x=2一个解，x=3两个解···
### 共(x-1)(x-2)/2个解
### 但是，以上包含了y=z的情况，且一个解被算了2遍
## $\therefore$f(x)=$\frac{1}{2}(\frac{(x-1)(x-2)}{2}-\lfloor\frac{x-1}{2}\rfloor)$
```cpp
#include<bits/stdc++.h>
using namespace std；
long long f[1000010];
int main(){
	for(long long i=4;i<=1000000;i++){
		f[i]=f[i-1]+((i-1)*(i-2)/2-(i-1)/2)/2;
	}
	long long n;
	while(cin>>n){
		if(n<3) break;
		cout<<f[n]<<endl;
	}
	return 0;
}
```

---

## 作者：小明小红 (赞：1)

# UVA11401题解

**解答**：由于 $n$ 的上限很大，所以暴力这个思路是直接被否决的。为了能够不重复地统计三角形的数量，先将三角形按最长边进行分类计数。令 $C(x)$ 表示三角形中最长边为 $x$ 时的不同三角形数量，同时另外的两条边的边长分别为 $y$ 和 $z$，根据三角形的边不等式有

$y+z>x$

易得

$x-y<z<x$

由于题目约束三角形的三条边长均不相同，则当 $y=1$,不等式无解；当 $y=2$ 时，$z$ 只有 $1$ 个解，分别是 $x-1$；当 $y=3$ 时 $z$ 有 $2$ 个解，分别是 $x-2$、$x-1$……当 $y=x-1$，$z$ 有 $x-2$ 个解,分别是 $2$、$3$、…、$x-1$。观察得到，解的数量构成了等差数列，故总的解数量为

$\frac{(x-1)(x-2)}{2}$。

不过这不是 $C(x)$ 的值。如题意，$y=z$ 时不符要求的，要将它剔除，当 $y=z$ 时，共要剔除

$(x-1)-(\frac{x}{2}+1)+1=\frac{(x-2)}{2}$

种，由于 $x$ 和 $y$ 交换是相同的三角形，故还要剔除，得 

$C(x)=\frac{\frac{(x-1)(x-2)}{2}-\frac{x-2}{2}}{2}=\frac{(x-2)^{2}}{4}$。

最后，由于题目求最大边长不超过 $n$ 的不同三角形数量 $F(n)$，有 $F(n)=C(1)+C(2)+…+C(n)=F(n-1)+C(n)$。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,f[1000009]; 
int main()
{
	for(ll i=3;i<=1000000;i++)//预处理 
	{
		f[i]=f[i-1]+(i-2)*(i-2)/4;
	}
	while(1)//输入输出 
	{
		cin>>n;
		if(n<3) 
			break;
		cout<<f[n]<<endl;
	}
	return 0;
 } 
```




---

## 作者：bifanwen (赞：1)

[洛谷博客同步](https://www.luogu.com.cn/blog/bfw/solution-uva11401)

[博客园同步](https://www.cnblogs.com/bifanwen/p/13027697.html)

[CSDN同步](https://blog.csdn.net/bifanwen/article/details/106482134)

[原题链接](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2396)

简要题意：

若干组数据，每组数据给出一个 $n$ ，求出 **三边均 $\leq n$ 且互不相等** 的三角形个数。两个三角形不同当且仅当至少有一边长度不同。

首先我们应当考虑三角形的性质。设三边为 $x,y,z$ 且 $x>y>z$.

则：

$$x < y+z$$

可以得到 $y$ 的范围：

$$x-z < y < x$$

假设 $f_x$ 表示 $x$ 为最长边时的答案。

此时应存在：

$$f_x = x - (x-z) - 1 = z - 1$$

显然这是已知 $z$ 的情况。$z \leq x-2$，所以：

$$f_x = \sum_{z=1}^{x-2} z-1 = \sum_{z=1}^{x-1} z = \frac{(x-1)(x-2)}{2}$$

但是你会发现这并不正确。$y=z$ 的情况需要剔除，这是一个简单的容斥思想。

当 $y=z$ 时，显然存在：

$$\frac{x}{2} + 1 \leq y = z \leq x-1$$

所以这种情况的方案数为：

$$(x-1) - (\frac{x}{2} + 1) = \frac{x-2}{2}$$

考虑原来可能把 $y=2 , z = x-1$ 和 $y=x-1 , z=2$ 重复计算，因此可得：

$$f_x = \frac{ \frac{(x-1)(x-2)}{2} - \frac{x-2}{2} }{2} =\frac{(x-2)^2}{4}$$

当 $x$ 为自然数时应向下取整。

因此，若 $g_x$ 表示题目所求，则：

$$\begin{cases}
g_x = 0 , x=1,2,3 \\
g_x = g_{x-1} + f_x , x >3 \\
\end{cases}
$$

以此类推即可。

时间复杂度：$O(n+T)$. （$T$ 为数据组数）

实际得分：$100pts$.

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

typedef __int128 ll;
const int N=1e6+1;

inline int read(){char ch=getchar(); int f=1; while(ch<'0' || ch>'9') {if(ch=='-') f=-f; ch=getchar();}
	int x=0; while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar(); return x*f;}

inline void write(ll x) {
	if(x<0) {putchar('-');write(-x);return;}
	if(x<10) {putchar(char(x%10+'0'));return;}
	write(x/10);putchar(char(x%10+'0'));
}

ll f[N]; int n;

int main() {
	f[1]=f[2]=f[3]=0ll;
	for(ll i=4;i<N;i++) f[i]=f[i-1]+(i-2)*(i-2)/4;
	while(1) {
		n=read(); if(n<3) return 0;
		write(f[n]); putchar('\n');
	}
	return 0;
}


```

---

## 作者：zhangzihang (赞：0)

### 题意分析


------------

- 对于每一个 $n$ 询问在以 $1,2,3,...,n$ 中的数为边的三角形共有多少个。
- 一个数只能用一次。
- 多组询问以 $n<3$ 的询问为结束标志。

------------

### 算法分析



------------

考虑线性递推，提前预处理出对于每个 $n$ 的方案数，每次询问时就可以 $\mathcal{O}(1)$ 的复杂度输出，而预处理复杂度为 $\mathcal{O}(n)$ 理论可以通过此题。

如何预处理？

令 $f(x)$ 表示 $x$ 的方案数。

若三角形中不含长度为 $x$ 的边，情况数为 $f(x-1)$。

若三角形中含有长度为 $x$ 的边，由三角形两边之和大于第三边，即询问有多少组 $a,b\in [1,n]$ 满足 $a+b>x$。

不妨 $a\le b$ 则 $b> \dfrac{x}{2}$ 此时 $a\in [x+1-b,b)$ 共 $2b-x-1$ 个。

方便起见，我们令 $t=\left\lceil\dfrac{x+1}{2}\right\rceil$。

所以 $f(x)=f(x-1)+\sum\limits_{i=t}^x 2i-x-1$。

化简得 $f(x)=f(x-1)+\dfrac{(2t -4)(x-t)}{2}=f(x-1)+(t-2)(x-t)$。



------------

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[1000005];
signed main(){
	for(int i=4;i<=1000000;i++){
	    int t=(i+2)/2;
		f[i]=f[i-1]+(t-2)*(i-t);
	}
	int n;
	while(cin>>n){
		if(n<3) return 0;
		cout<<f[n]<<"\n";
	}
	return 0;
}
```

有任何问题请私信。








---

## 作者：ncwzdlsd (赞：0)

三重循环的时间复杂度为 $O(n^3)$，必然会$\text{TLE}$，预计得分：$0$。

用加法原理，设最大边长为 $x$ 的三角形有 $c(x)$个，另外两条边长分别为 $y$ 和 $z$，$y+z>x$，$x-y<z<x$。

当 $y=1$ 时，$x-1<y<x$，无解；$y=2$ 时只有一个解（$z=x-1$）；$y=3$ 时有两个解（$z=x-1$ 或 $z=x-2$）……直到 $y=x-1$ 时有 $x-2$ 个解。一共有 $0+1+2+...+(x-3)+(x-2)=\dfrac{(x-1)(x-2)}{2}$ 个解。

但是，上面的解包含了 $y=z$ 的情况，而且每个三角形算了两遍。

解决方案：首先统计 $y=z$ 的情况。这部分一共有 $x-1-\dfrac{x-1}{2}$ 个解。把这部分解扣除，再除以 $2$，即

$$
c(x)=\dfrac{1}{2}\left( \dfrac{(x-1)(x-2)}{2}-\lfloor \dfrac{x-1}{2} \rfloor \right)
$$

代码如下：
```cpp
#include<iostream> 
using namespace std; 

long long f[1000010];

int main() 
{ 
    f[3] = 0; 
    for(long long x = 4;x <= 1000000;x++)
        f[x] = f[x-1] + ((x-1)*(x-2)/2 - (x-1)/2)/2; 
    int n; 
    while(cin >> n) 
    { 
        if(n < 3) 
            break; 
        else
            cout << f[n] << endl; 
    } 
    return 0; 
}
```

---

## 作者：翼德天尊 (赞：0)

一道不错的推式子题。

我们不妨设三角形的三条边长分别为 $x,y,z$，其中 $x<y<z$。

考虑将三角形按照最长边边长分类，用 $w_z$ 表示三角形最长边为 $z$ 时的方案数。

由三角形三边不等式得，$x+y>z$，所以 $z-x<y<z$。

当 $x=1$ 时，易知 $y$ 无解。

当 $x=2$ 时，$y$ 有唯一解 $y=z-1$。

当 $x=z-1$ 时，$1<y<z$，即有 $z-2$ 个解。

综上，一共有 $\frac{(z-2)(z-1)}{2}$ 个方案。

但是还没完。由于上述解当中可能会出现 $x=y$ 的情况，并不符合题目要求。故我们需要将 $x=y$ 的方案数剔除出来。

易知，当 $z>x\ge\left\lceil\frac{z}{2}\right\rceil$ 时，$y$ 可以取到 $x$，此时 $x$ 可以取 $z-1,z-2\dots,\left\lceil\frac{n}{2}\right\rceil$ 等 $\left\lfloor\frac{n+1}{2}\right\rfloor$ 个取值，故总方案数应该减去 $\left\lfloor\frac{n+1}{2}\right\rfloor$。

又因为 $x$ 和 $y$ 无序，所以我们在考虑方案的过程中相当于将每个方案考虑了 $2$ 遍，故最终的方案数还需要再除以 $2$。

综上，$w_z=$

$$\frac{\frac{(z-2)(z-1)}{2}-\left\lfloor\frac{n+1}{2}\right\rfloor}{2}$$

最后，我们可以递推快速预处理出 $n$ 取每一个值时的答案，即

$$ans_i=ans_{i-1}+w_i$$

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 1000000
ll n,sum[N+5];

ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	for (ll i=4;i<=N;i++){
		ll x=((i-2)*(i-1)/2-(i-1)/2)/2;
		sum[i]=sum[i-1]+x;
	}
	n=read();
	while (n>=3){
		printf("%lld\n",sum[n]);
		n=read(); 
	}
	return 0;
}
```


---

## 作者：wsk_1202 (赞：0)

题意：从 $1,2,...n$ 中选出三个数，使其能构成三角形，求方案总数。

观察$N$的范围，易知需要使用数学方法或$O(N)$、$O(N  logN)$的递推。

数学方法？~~推不出来~~

于是先手算出$N$较小情况时的解 $ans[N]$：

$ans[3]=0$
$ans[4]=1$
$ans[5]=3$
$ans[6]=7$
$ans[7]=13$
$ans[8]=22...$

再算一下相邻解之间的差 $x[i,j]$：

$x[3,4]=1$
$x[4,5]=2$
$x[5,6]=4$
$x[6,7]=6$
$x[7,8]=9...$

这个时候，已经有大佬找出 $x$ 数组的数学规律了，然而由于当时并没有认真找规律，只是发现这个 $x$ 数组相邻两数的差有较明显的规律：

$x[4,5]-x[3.4]=1$

$x[5,6]-x[4,5]=x[6,7]-x[5,6]=2$

$x[7,8]-x[5,6]=x[8,9]-x[7,8]=3$

最后将其优化至一维： $x[i]=x[i-1]+(i+1)/2$

于是也可得到 $ans$ 数组的递推式： $ans[i]=ans[i-1]+x[i-3], i>3$

具体的证明可以用数学方法证出。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long //数据很大，需要long long
using namespace std;
int x[1000005],ans[1000005],n;
signed main()
{
	for(int i=1;i<=1000005;i++)x[i]=x[i-1]+(i+1)/2;
	for(int i=4;i<=1000005;i++)ans[i]=ans[i-1]+x[i-3];//O(n)预处理ans数组
	scanf("%lld",&n);
	while(n>=3)
	{
		printf("%lld\n",ans[n]);//对于每一次询问，直接输出答案
		scanf("%lld",&n);
	}
	return 0;
}
```

---

