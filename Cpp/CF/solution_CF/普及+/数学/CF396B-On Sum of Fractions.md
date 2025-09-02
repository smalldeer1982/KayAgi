# On Sum of Fractions

## 题目描述

我们设：

- $v(n)$是不超过$n$的最大素数；

- $u(n)$是大于$n$的最小素数。

计算![](https://cdn.luogu.org/upload/vjudge_pic/CF396B/35810ad29d9f6c4fb0ebb0082bbbd3e3b2a406a1.png)。

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
1/6
7/30
```

# 题解

## 作者：Moco_jof (赞：3)

## 题目大意
设
- $v(n)$ 是不超过n的最大素数；
- $u(n)$ 是大于n的最小素数。

请计算     

$$ \sum _ {i = 2} ^ n  \frac {1}{v(i)u(i)}$$

## 预备知识

~~看上去它是一道数学题，实际上他就是一道数学题~~

对于这道题，我们需要一些储备知识：**分数裂项**。

但是对分数裂项来说，其实我们只需要记住一个公式即可：

$$ \frac {1}{a\times(a+k)}=\frac{1}{k}\times(\frac{1}{a}-\frac{1}{a+k})$$

记住这个公式，你就可以推出其他的公式了。

例如：

$$\frac {1} {a\times(a+1)}=\frac {1}{a}-\frac{1}{a+1} $$

直接把 $k=1$ 代入 $ \frac {1}{a\times(a+k)}=\frac{1}{k}\times(\frac{1}{a}-\frac{1}{a+k})$ 即可得出。

# 正文

$$ \sum _ {i = 2} ^ n  \frac {1}{v(i)u(i)}$$

我们可以举一个例子：
设
$$n=9$$
则
 $$\sum _ {i = 2} ^ 9  \frac {1}{v(i)u(i)}=\frac {1}{2\times3}+\frac {1}{3\times5}+\frac {1}{3\times5}+\frac {1}{5\times7}+\frac {1}{5\times7}+\frac{1}{7\times11}+\frac{1}{7\times11}+\frac{1}{7\times11} 
$$ 

即
 $$\sum_{i=2}^9 \frac{1}{v(i)u(i)}=\frac{1}{2\times3}+\frac{2}{3\times5}+\frac{2}{5\times7}+\frac{3}{7\times11}$$ 

代入分数裂项公式可得

 $$\sum_{i=2}^9 \frac{1}{v(i)u(i)}=\frac{1}{2}-\frac{1}{7}+\frac{3}{7\times11}$$ 

我们可以发现， $ \sum _ {i = 2} ^ n  \frac {1}{v(i)u(i)}$ 当 $n=9$ 的时候，只有最后的 $\frac{3}{7\times11}$ 需要特判；

又因为，最后的这个 $\frac{3}{7\times11}$ 是由之前的三个 $\frac{1}{7\times11}$ 所合并的。

所以我们可以发现
$$\sum_{i=2}^n \frac{1}{v(i)u(i)}=\frac{1}{2}-\frac{1}{v(i)}+\frac{n-v(i)+1}{v(i)u(i)}=\frac{2n+2+v(n)u(n)-2\times u(n)-2\times v(n)}{2\times v(n)u(n)}$$
# 
# AC代码

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long //十年OI一场空，不开long long见祖宗
int t,n,v,u,a,b,gcd0;
bool p(int);
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); //关闭输入输出流
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=n;i>=2;i--){ //v(i)
			if(p(i)){
				v=i;
				break;
			}
		}
		for(int i=n+1;;i++){ //u(i)
			if(p(i)){
				u=i;
				break;
			}
		}
		a=2*n+2+u*v-2*u-2*v,b=2*v*u; //a为分子,b为分母
		gcd0=__gcd(a,b);//用 __gcd 找最大公约数
		cout<<a/gcd0<<'/'<<b/gcd0<<'\n';
	}
	return 0;
} 
bool p(int x){//简陋的判断素数
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			return false;
		}
	}
	return true;
}
```
点个赞再走吧…… QWQ

---

## 作者：hank0402 (赞：2)

### 题目大意：

定义 $v(n)$ 为不大于 $n$ 的最大素数，$u(n)$ 为大于 $n$ 的最小素数。

求 :

$$\sum^{n}_{i=2}\frac{1}{u(n)v(n)}$$

的值。
 
### 题解：

这个式子看起来很难直接做，于是我们可以试着在 $n$ 较小的情况下把它拆开找一找规律。

当 $n=11$ 时，原式为：

$$\frac{1}{2\times 3}+\frac{1}{3\times 5}+\frac{1}{3\times 5}+\frac{1}{5\times7}+\frac{1}{5\times7}+\frac{1}{7\times11}+\frac{1}{7\times11}+\frac{1}{7\times11}+\frac{1}{7\times11}+\frac{1}{11\times13}$$

我们会发现，有些分式是重复的，所以，我们可以化简为：

$$\frac{1}{2\times 3}+\frac{2}{3\times 5}+\frac{2}{5\times7}+\frac{4}{7\times11}+\frac{1}{11\times13}$$

然后，我们观察分式的分子和分母，可以发现，原式又为：

$$\frac{3-2}{2\times 3}+\frac{5-3}{3\times 5}+\frac{7-5}{5\times7}+\frac{11-7}{7\times11}+\frac{1}{11\times13}$$

这个式子的前 $4$ 项可以用小学的裂项芝士进行裂项，所以原式又可以化简为：

$$\frac{1}{2}-\frac{1}{11}+\frac{1}{11\times13}$$

考虑其更一般的形式，我们会发现，只有最后的一项不能完全的裂完，所以要分开考虑，故

$$\sum^{n}_{i=2}\frac{1}{u(n)v(n)}=\frac{1}{2}-\frac{1}{u(n)}+\sum^{n}_{i=u(n)}{\frac{1}{u(i)v(i)}}$$

考虑如何解决最后一项，我们可以发现，最后一项拆开来后的每个分式的分母都是一样的，故：

$$\sum^{n}_{i=u(n)}{\frac{1}{u(i)v(i)}}=\frac{n-u(n)+1}{u(n)v(n)}$$

所以：

$$\sum^{n}_{i=2}\frac{1}{u(n)v(n)}=\frac{1}{2}-\frac{1}{u(n)}+\frac{n-u(n)+1}{u(n)v(n)}=\frac{u(n)v(n)-2\times u(n)-2\times v(n) + 2\times n + 2}{2\times u(n)v(n)}$$

由于素数的分布比较密集，所以可以暴力得到 $u(n)$ 和 $v(n)$，最后约分输出答案即可。

### 一些粗略的证明：

Q：为什么对于任意的 $n$，拆开后除了分母为 $u(n)v(n)$ 的项，都可以组合成分数裂项的形式？

A：考虑分母为 $u(i)v(i)$ 的分式，因为 $u(i)$ 是大于 $i$ 的**最小**素数，并且 $v(i)$ 是不大于 $i$ 的**最大**素数，故分子必须不小于 $v(i)$ 且小于 $u(i)$，故除了最后的边界意外，每个分母为 $u(i)v(i)$ 的分式，都有 $u(i)-v(i)$ 个。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
bool prime(int n) { //暴力判断素数
	if(n == 1) return false;
	for(int i = 2; i * i <= n; ++i) {
		if(n % i == 0) return false;
	}
	return true;
}
int T;
int main() {
	cin >> T;
	while(T --) {
		long long n, v, u; //注意long long
		cin >> n;
		u = n + 1;
		v = n;
		while(!prime(v)) u ++; //u(n)
		while(!prime(u)) v --; //v(n)
		long long fz = v * u - 2 * u  + 2 * n - 2 * v + 2, fm = 2 * u * v; //计算分子和分母
		long long g = __gcd(fz, fm);
		fz /= g; fm /= g; //约分
		cout << fz << '/' << fm << endl;
	} 
	return 0;
}
```

---

## 作者：Jayun (赞：2)

# 链接：

[题目](https://www.luogu.com.cn/problem/CF396B)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14232457.html)

# 题目大意：

设：
- $u(n)$ 是不超过 $n$ 的最大素数。
- $v(n)$ 是大于 $n$ 的最小素数。

给定一个 $n$，求出 $\sum_{i=2}^{n}\frac{1}{u(i)v(i)}$。

# 正文：

我们尝试拆开原式：

$$\sum_{i=2}^{n}\frac{1}{u(i)v(i)}=\frac{1}{2\times3}+\frac{1}{3\times5}+\frac{1}{3\times5}+\frac{1}{5\times7}+\frac{1}{5\times7}+\cdots+\frac{1}{u(n)\times v(n)}$$

我们发现，这几个分式中有几个会是重复的，像是这里有两个 $\frac{1}{3\times5}$，和两个 \frac{1}{5\times7}。而它们的数量就是 $v(i)-u(i)$。因为重复的分式相当于是在这个区间 $\left[u,v(i)\right)$ 里。

由此可得：

$$\begin{aligned}&\frac{1}{2\times3}+\frac{1}{3\times5}+\frac{1}{3\times5}+\frac{1}{5\times7}+\frac{1}{5\times7}+\cdots+\frac{1}{u(n)\times v(n)}\\=&\frac{1}{2\times3}+\frac{5-3}{3\times5}+\frac{7-5}{5\times7}+\cdots+\frac{v(n)-u(n)}{u(n)\times v(n)}\\=&\left(\frac{1}{2}-\frac{1}{3}\right)+\left(\frac{1}{3}-\frac{1}{5}\right)+\left(\frac{1}{5}-\frac{1}{7}\right)+\cdots+\left(\frac{1}{u(n)}-\frac{1}{v(n)}\right)\end{aligned}$$

到这里，你会发现式子里面可以消掉一些分式，只剩下 $\frac{1}{2}-\frac{1}{v(n)}$。

我爱裂项题。

# 代码：

```cpp
int t;
ll n;

inline bool isPri(ll x)
{
	for (ll i = 2; i * i <= x; i ++)
		if(x % i == 0) return 0;
	return 1;
}

ll gcd (ll a, ll b) {return b? gcd (b, a % b): a;} 

int main()
{
	for (scanf ("%d", &t); t--; )
	{
		scanf ("%lld", &n);
		bool flagu = 0, flagv = 0;
		ll u = n + 1, v = n;
		for (flagu = isPri(u), flagv = isPri(v); !flagu || !flagv; )
		{
			if(!flagu) u++, flagu = isPri(u);
			if(!flagv) v--, flagv = isPri(v);
		}
		ll a = v * u - 2 * u + 2 * n - 2 * v + 2, 
		   b = 2 * u * v,
		   Gcd = gcd(a, b);
		printf ("%lld/%lld\n", a / Gcd, b / Gcd);
	}
	return 0;
}
```

---

## 作者：luuia (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF396B)
## 前置知识：裂项相消法
$\,\,\,\,\,\,\,\,\,\,$裂项法，这是分解与组合思想在数列求和中的具体应用。是将代数式中的每项分解，然后重新组合，使之能消去一些项，最终达到求和的目的。 

### 一些简单的裂项公式：

#### 基本裂项公式：
$${1 \over {n \times {(n + k)}}} = {1 \over k} \times {({1 \over n} - {1 \over{n + k}})}$$

#### 其他的一些裂项公式：

- $${1 \over {n \times {(n + 1)}}} = {{1 \over n} - {1 \over{n + 1}}}$$

- $${1 \over {(2n-1) \times {(2n + 1)}}} = {1 \over 2} \times {({1 \over 2n - 1} - {1 \over{2n + 1}})}$$

- $${1 \over {(n) \times {(n + 1)} \times (n+2)}} = {1 \over 2} \times ({1 \over {n \times {(n + 1)}}} - {1 \over (n+1) \times (n + 2)})$$

## 前置知识：素数

Q：什么是质数(素数)？

A：质数(素数)是指在大于 $1$ 的自然数中，除了 $1$ 和它本身以外不再有其他因数的自然数，例如 $2,3,5,7$ 等等。

Q：如何筛选素数？

A：一个简单的算法是筛选法。筛选法的具体做法是先把前$n$个数字从大到小排列起来。

比如：$1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22$

首先排除 $1$，$1$ 后面的第一个数是 $2$，那么把 $2$ 的所有倍数都去掉，变成下面这样：

$2,3,5,7,9,11,13,15,17,19,21$ 

$2$ 后面的第一个数是 $3$，继续同样划去 $3$ 的所有倍数，变成下面这样：

$2,3,5,7,11,13,17,19$

同理，继续划 $5,7,11,13,17,19$ 的倍数，但是由于这些数的倍数已经都被划去或不在这个序列中，那么我们便得到了这个序列中的质数。

当然，这个方法的时间复杂度还比较高，那么有没有更快的算法呢？

 **答案是：有。**

下面介绍一种算法：欧拉筛法。

### 欧拉筛法$O(n)$
欧拉筛法和埃氏筛法的区别在于，埃氏筛法其中有很多数倍筛选了很多遍，例如 $60$，它被 $2,3,5$ 都筛选过，就造成了时间的浪费。而欧拉筛法的好处在于，它其中的所有数都只会被筛选一遍。

欧拉筛法的关键便在于每个合数只被其最小的质因数筛掉，比如 $21$，它只会被 $3$ 筛掉，而在 $7$ 时，就不会去浪费时间判断了。

那么如果 $21$ 被 $3$ 筛掉，我们要研究 $7$ 应该筛到哪个数才能停止。

我们设这个数为 $n = p_1^{x_1} \times p_2^{x_2} \times \cdots \times p_m^{x_m}$

$$(p_1 \lt p_2 \lt \cdots \lt p_m,x_1,x_2,\cdots,x_m \ge 1,m \ge 2)$$

当我们筛到 $p_1$ 时继续向下筛选，不妨设此时筛选的质数为 $p_0$，那么

$$ n \times p_0 = p_0 \times p_1^{x_1} \times p_2^{x_2} \times ... \times p_m^{x_m} \  = p_1 \times p_0 \times p_1^{x_1 - 1} \times p_2^{x_2} \times ... \times p_m^{x_m} $$

那么此时 $n \times p_0$ 可以由 $p_1$ 筛选掉，就不需要 $p_0$ 来筛选了。

这样便实现了 $O(n)$ 的时间复杂度。

代码实现：
[欧拉筛法](https://www.luogu.com.cn/paste/ypk97qsn)

```cpp
int euler(int n)
{
	int d = 0;
	int p[100010] = {0};
	int f[100010] = {1,1};
	for(int i = 2;i <= n;i++)
	{
		if(f[i] == 0)
		{
			p[d++] = i;
		}
		for(int j = 0;j < d;j++)
		{
			if(p[j] * i <= n)
			{
				f[p[j] & i] = 1;
			}
			else
			{
				break;
			}
			if(i % p[j] == 0)
			{
				break;
			}
		}
	}
} 
```

**接下来，让我们回到题目**
## 题目讲解
### 题意
- $u(n)$ 是大于 $n$ 的最小素数

- $v(n)$ 是不超过 $n$ 的最大素数

求
$$
\begin{aligned}
\sum _ {i = 2} ^ n {1 \over {v(i) \times u(i)}} \\

\end{aligned}
$$

### 分析
这时候就要用到我们的裂项知识了。

#### 猜想
单看题目的式子看不出来什么，可以尝试写出前几项观察规律：
$$
\begin{aligned}
\sum _ {i = 2} ^ n {1 \over {v(i) \times u(i)}}
&= {1 \over 2 \times 3}+{1 \over 3 \times 5}+{1 \over 3 \times 5}+{1 \over 5 \times 7}+{1 \over 5 \times 7}+{1 \over 7 \times 11}+{1 \over 7 \times 11}+{1 \over 7 \times 11}+{1 \over 7 \times 11}+ \cdots +{1 \over {v(n) \times u(n)}} \\
&= {{{3-2} \over {2 \times 3}}+{{5-3} \over {3 \times 5}}+{{7-5} \over {5 \times 7}}+{{11-7} \over {7 \times 11}}+{{13-11} \over {11 \times 13}}} + \cdots + {{n - u(n) + 1} \over {v(n) \times u(n)}}\\
\end{aligned}
$$
我们发现，除了最后一项，$1 \over {v(i) \times u(i)}$ 这个式子出现了 $u(i) - v(i)$ 次,而最后一项出现了 ${n - u(n) + 1}$ 次。

通过目前发现的规律进行整理并裂项：
$$
\begin{aligned}
\sum _ {i = 2} ^ n {1 \over {v(i) \times u(i)}}
&= {{{3-2} \over {2 \times 3}}+{{5-3} \over {3 \times 5}}+{{7-5} \over {5 \times 7}}+{{11-7} \over {7 \times 11}}+{{13-11} \over {11 \times 13}}} + \cdots + {{n - u(n) + 1} \over {v(n) \times u(n)}}\\
&= {({1 \over 2} - {1 \over 3})}+{({1 \over 3} - {1 \over 5})}+{({1 \over 5} - {1 \over 7})}+{({1 \over 7} - {1 \over 11})}+{({1 \over 11} - {1 \over 13})}+ \cdots \\
&\,\,\,\,\,\,\,\,+ ({1 \over {u(u(n) - 1)}} - {1 \over {u(n)}}) + {{n - u(n) + 1} \over {v(n) \times u(n)}}\\
&= {1 \over 2} - {1 \over u(n)} + {{n - u(n) + 1} \over {v(n) \times u(n)}}\\
&= {1 \over 2} - {v(n) \over {v(n) \times u(n)}}+ {{n - u(n) + 1} \over {v(n) \times u(n)}}\\
&= {1 \over 2} + {{n - u(n) - v(n) + 1} \over {u(n) \times v(n)}}
\end{aligned}
$$

可以发现最终的答案比较简单，无需求和符号，那么如何证明我们发现的这个结论呢？
#### 证明
在区间 $[v(i),u(i))\,\,\,\,\,(i < n)$ 中，我们标每个数为 $v(i),v(i)+1,\cdots,u(i) - 1$。

那么 $v(i) = v(i) < v(i) + 1 < \cdots < u(i) - 1 < u(i)$

所以

$v(v(i)) = v(v(i)+1) = v(v(i)+2) = \cdots = v(u(i) - 1)$

$u(v(i)) = u(v(i)+1) = u(v(i)+2) = \cdots = u(u(i) - 1)$

所以在区间 $[v(i),u(i))$ 中，所有的数 $j$ 的 $v(j) \times u(j)$ 均等于 $v(i) \times u(i)$。

那么 $1 \over {v(i) \times u(i)}$ 这个式子就一共会出现 $u(i) - v(i)$ 次，得证。
#### 结论

$$
\begin{aligned}
\sum _ {i = 2} ^ n {1 \over {v(i) \times u(i)}} 
&= {{1 \over 2} + {{n - u(n) - v(n) + 1} \over {u(n) \times v(n)}}}\\
&= {{u(n) \times v(n)} \over {2 \times u(n) \times v(n)}} + {{2 \times n - 2 \times u(n) - 2 \times v(n) + 2} \over {2 \times u(n) \times v(n)}}\\
&= {{{u(n) \times v(n)} + {2 \times n - 2 \times u(n) - 2 \times v(n) + 2} } \over {2 \times u(n) \times v(n)}}
\end{aligned}
$$
由此，我们可以写出本题的 AC 代码。

### 代码
AC 代码：[AC 代码](https://www.luogu.com.cn/paste/203bnjvl)

我的 [AC](https://www.luogu.com.cn/record/121492596) 记录
```cpp
#include <bits/stdc++.h>
using namespace std;

int read()//快读 
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

void write(long long a)//快写 
{
	if(a > 9) write(a / 10);
	putchar(a % 10 + '0');
}

long long gcd(long long x,long long y)//求最小公因数
{
    if(y == 0) return x;
    else
    {
    	return gcd(y,x % y);
	}
}

bool prime(long long x)//判断是否为素数
{
	for(long long i = 2;i * i <= x;i++)
	{
		if(x % i == 0) return 0;	
	}
	return 1;
}

int solve(int n)//解决问题
{
	long long u = n + 1,v = n;
	while(!prime(u))
	{
		u++;
	}
	while(!prime(v))
	{
		v--;
	}
	long long a = (u * v) + (2 * n) - (2 * u) - (2 * v) + 2;
	long long b = 2 * u * v;
	long long d = gcd(a,b);
	a /= d;
	b /= d;
	cout << a << "/" << b << endl;
}

int main() 
{
	int T;
	T = read();
	while(T--)
	{
		int x;
		x = read();
		solve(x);
	}
	return 0;
}
```


---

## 作者：Lucifer_Bartholomew (赞：1)

# 数学
这道题只要手写模拟一下就可以找出规律了。

观察题中式子![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396B/35810ad29d9f6c4fb0ebb0082bbbd3e3b2a406a1.png),
对于满足$\frac{1}{v(i)u(i)}$的i,范围应是${v(i)}<=i<{u(i)}$。所以可以化简式子$\sum_{i=v(i)}^{u(i)-1}\frac{1}{v(i)u(i)}=\frac{u(i)-v(i)}{v(i)u(i)}=\frac{1}{v(i)}-\frac{1}{u(i)}$。设小于等于n的最大质数为$p_{1}$,大于n的最小质数为$p_{2}$,那么全部化简加起来$\sum_{i=2}^{n}=\frac{1}{2}-\frac{1}{p_{1}}+\frac{n-p{1}+1}{p_{1}p_{2}}$。

模拟通分算出这个式子后记住最后求一下gcd约分就好了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline bool pri(int x)//求是否是质数
{
	if(x==2)return 1;
	if(x==1||!(x&1))return 0;
	for(int i=2;i*i<=x;++i)
		if(!(x%i))return 0;
	return 1;
}
inline ll gcd(ll a,ll b)//求gcd
{
	return b?gcd(b,a%b):a;
}
int main()
{
	int t=read();
	while(t--)
	{
		ll n=read();
		if(n<2)puts("0");
		else
		{
			ll a;
			for(int i=n;;--i)//求小于等于n的最大质数
				if(pri(i))
				{
					a=i;
					break;
				}
			for(int i=n+1;;++i)//求大于n的最小质数
				if(pri(i))
				{
					ll t=n-a+1-i<<1,b=a*i,g=gcd(t+b,b<<1);//模拟通分
					printf("%lld/%lld\n",(t+b)/g,(b<<1)/g);
					break;
				}
		}
	}
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF396B) & [Problem](//www.luogu.com.cn/problem/CF396B)

## 题目大意

- 设 $u(n)$ 为不超过 $n$ 的最大素数，$v(n)$ 为超过 $n$ 的最小素数。

- 给定 $n$，求 $\sum\limits_{i=2}^{n}\dfrac 1{u(i)v(i)}$。

- $1\leq T\leq 500$，$1\leq n\leq 10^9$

## 解题思路

$$
\begin{aligned}
   & \sum\limits_{i=2}^{n}\dfrac 1{u(i)v(i)} \\
=\ & \dfrac 1{2\times 3}+\dfrac 1{3\times 5}+\dfrac 1{3\times 5}+\dfrac 1{5\times 7}+\dfrac 1{5\times 7}+\cdots+\dfrac 1{u(n)v(n)} \\
=\ & \dfrac{3-2}{2\times 3}+\dfrac{5-3}{3\times 5}+\dfrac{7-5}{5\times 7}+\cdots+\dfrac{u(n)-u(u(n)-1)}{u(u(n)-1)u(n)}+\dfrac{n-u(n)+1}{u(n)v(n)} \\
=\ & \left(\dfrac 12-\dfrac 13\right)+\left(\dfrac 13-\dfrac 15\right)+\left(\dfrac 15-\dfrac 17\right)+\cdots+\left(\dfrac 1{u(u(n)-1)}-\dfrac 1{u(n)}\right)+\dfrac{n-u(n)+1}{u(n)v(n)} \\
=\ & \dfrac 12-\dfrac 1{u(n)}+\dfrac{n-u(n)+1}{u(n)v(n)} \\
=\ & \dfrac 12+\dfrac{n-u(n)-v(n)+1}{u(n)v(n)}.
\end{aligned}
$$

那么只需要暴力求出 $u(n)$ 和 $v(n)$ 即可就算出答案。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int T,n;

inline bool prime(int x){
    if(x<2)return false;
    int t=sqrt(x);
    for(int i=2;i<=t;i++)
        if(x%i==0)return false;
    return true;
}

long long Gcd(long long x,long long y){
    if(y==0)return x;
    return Gcd(y,x%y);
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        int u=n+1,v=n;
        while(!prime(u))u++;
        while(!prime(v))v--;
        long long ans1=n-u-v+1,ans2=(long long)u*v;
        ans1*=2,ans2<<=1,ans1=ans2/2+ans1;
        long long gcd=Gcd(ans1,ans2);
        printf("%lld/%lld\n",ans1/gcd,ans2/gcd);
    }
    return 0;
}
```

---

## 作者：fls233666 (赞：0)

直接暴力求解题目中的式子肯定是不行的。再看到 $n$ 的取值范围极大，我们考虑**找规律**。

看到题目中 $\dfrac{1}{u(i)v(i)}$ 这部分，分母是乘积的形式，我们自然联想到**分数裂项**。我们知道，有 $\dfrac{b-a}{ab}=\dfrac{1}{a}-\dfrac{1}{b}$ ,那么是否可以套用这个公式呢？

在手算几个测试数据后，我们发现**可以套用分数裂项的公式**。在进一步考虑到**最后一项可能不能裂项**，我们将题目中的公式做如下化简：

$$
\sum\limits_{i=2}^n\dfrac{1}{u(i)v(i)}
$$
$$=\dfrac{1}{u(2)}-\dfrac{1}{u(n)}+\sum\limits_{i=u(n)}^n\dfrac{1}{u(n)v(n)}
$$
$$
=\dfrac{1}{2}-\dfrac{1}{u(n)}+\dfrac{n-u(n)+1}{u(n)v(n)}
$$
$$
=\dfrac{1}{2}-\dfrac{v(n)-n+u(n)-1}{u(n)v(n)}
$$

现在答案就很好求了。公式中的 $u(n)$ 和 $v(n)$ 只要从 $n$ 开始暴力找质数即可。最后要用 $\gcd$ 来进行约分得到最简分数。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define rgt register ll
using namespace std;

inline bool pr(ll p){  //暴力判质数
	for(rgt i=2;i*i<=p;i++)
		if(p%i==0)
			return false;
	return true;
}

ll gcd(ll a,ll b){
	if(b==0) return a;
	else return gcd(b,a%b);
}

struct frac{
	ll fz;  //分子
	ll fm;  //分母
}f1,f2;  //建分数

void print(struct frac f){
	printf("%lld/%lld\n",f.fz,f.fm);  //输出分数
}

struct frac res(struct frac a1,struct frac a2){  //分数相减
	struct frac a3;
	a3.fm=a1.fm*a2.fm;
	a3.fz=a1.fz*a2.fm-a2.fz*a1.fm;
	ll c=gcd(a3.fm,a3.fz);  //取 gcd 并约分
	a3.fz/=c; a3.fm/=c;
	return a3;
}   

int main(){
	int test;
	ll n,g1,g2;
	scanf("%d",&test);
	while(test--){
		scanf("%lld",&n);
        
		if(n==2){
			printf("1/6\n");
			continue;
		}   //2要特判，因为当 n=2 时只有1/6这一项。
        
		g1=n+1;
		while(!pr(g1))
			g1++;
                //求v(n)
         
		g2=n;
		while(!pr(g2))
			g2--;
                //求u(n)
            
		f1.fm=2;
		f1.fz=1;
		f2.fm=g1*g2;
		f2.fz=g1-n+g2-1;
		print(res(f1,f2));  //套公式算结果并输出
	}
	return 0;
}
```


---

## 作者：DarkMoon_Dragon (赞：0)

# 题意
+ 设 $u(i)$ 表示最大的不大于 $i$ 的素数，$v(i)$ 表示最小的大于$i$的素数。
+ 求
$$
f(n)=\sum ^n _{i=2}\frac{1}{u(i)*v(i)}~,~(n>1)
$$

# $Solution$
- 题意是前缀和形式
- 先考虑推前面几个小样例

$$f(i) = \frac{1}{2 * 3} + \frac{1}{3 * 5} + \frac{1}{3 * 5} + \frac{1}{5 * 7} + \frac{1}{5 * 7} + \frac{1}{7 * 11} + \frac{1}{7 * 11} + \frac{1}{7 * 11} + \frac{1}{7 * 11} + \cdots + \frac{1}{u(i) * v(i)}$$

+ 这不是长得很像裂项吗???
+ 考虑合并通项
$$f(i)=\frac{1}{2*3}+\frac{2}{3*5}+\frac{2}{5*7}+\frac{4}{7*11}+ \cdots +\frac{n-v(i)+1}{v(i)*u(i)}$$
+ 裂项
$$\frac{1}{a}-\frac{1}{b}=\frac{b-a}{b*a}$$
+ 考虑分部求
+ 前面和为
$$ \frac{1}{2} - \frac{1}{v(n)}$$
+ 后面完整部分为
$$(n-v(n)+1)*\frac{1}{v(n)*u(n)}$$
+ 通分化简得
$$f(n)=\frac{v(n)*u(n)-2*u(n)+2*n-2*v(n)+2}{v(n)*u(n)*2}$$
+ 即
$$f(n)=\frac{2*(n-v(n)+1)+(v(n)-2)*u(n)}{2*u(n)*v(n)}$$
+ $O(\sqrt{n})$找出$v(i)$，$u(i)$完事。

---
```cpp
#include<iostream>
#include<cstdio> 
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#include<cmath>
#define rr register int
using namespace std;
typedef long long ll;
inline ll read(){
    char i=getchar();
    ll f=1,res=0;
    while(i<'0'||i>'9'){if(i=='-')f=-1;i=getchar();}
    while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
    return f*res;
}
inline bool pd(int x) {
	if (x == 2) return 1;
	int sz = sqrt(x);
	for (rr i = 2; i <= sz; ++i) {
		if (x % i == 0) return 0;
	}
	return 1;
}
inline ll findl(ll x) {
	while(!pd(x)) --x;
	return x;
}
inline ll findr(ll x) {
	while(!pd(x)) ++x;
	return x;
}
inline ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
int main() {
	// freopen("prime.in", "r", stdin);
	// freopen("prime.out", "w", stdout);
	int T = read();
	while(T--) {
		ll n = read();
		ll l = findl(n);
		ll r = findr(n + 1);
		ll x = (l - 2) * r + 2 * (n - l + 1);
		ll y = l * r * 2;
		ll g = gcd(x, y);
		x /= g; 
		y /= g;
		printf("%lld/%lld\n", x, y);
	}	
}

```

---

