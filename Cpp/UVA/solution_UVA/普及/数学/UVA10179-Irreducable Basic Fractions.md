# Irreducable Basic Fractions

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1120

[PDF](https://uva.onlinejudge.org/external/101/p10179.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10179/9620a43ff9b7f7c199916d89f9baccfbc26a1bcb.png)

## 样例 #1

### 输入

```
12
123456
7654321
0```

### 输出

```
4
41088
7251444```

# 题解

## 作者：quest_2 (赞：2)

题是简单题，难度绿左右（可能还要低？）


------------

### 这里解读一下题意：

给定一个数 $N$ ，列出分数 $\dfrac{0}{N} ,\dfrac {1}{N} \cdots \dfrac {N-1}{N}$

他们中的一些有的能进行上下约分，而有的就不行。

求这些分数中**不可约分的分数的个数**。

------------

### 如何想到要用 $\varphi$ ？

关于 $\varphi$ ，学名叫**欧拉函数**，有关这方面的知识可以阅览一番笔者的[$\texttt\color{Orchid}\colorbox{white}{博客}$](https://www.luogu.com.cn/blog/quest233/kuo-zhan-ou-ji-li-dei-sheng-fa-ni-yuan-ju-zhen-sheng-fa)。

 _以下默认诸位都已经会了欧拉函数。_ 

什么样的分数会被约分？分子与分母有**不等于1的公约数**。这句话换个说法，就成了分子与分母**不互质**。

分子与分母不互质的会被约分。那其反命题自然是分子与分母**互质**的不会被约分。

分母是固定的，有关**互质个数**，很难不想到求 $\varphi$。

分子的范围是小于 $N$ 大于等于 0 ，正中下怀。

问题是这道题他怪得很，他认为 $\dfrac{0}{12}$ 是一个不可约分的分数，反而认为 $\dfrac{1}{12}$ 是可约分的。

不过好在多了一个又少了一个正好没差。答案还是 $\varphi(N)$ 。

我们就可以用 $\varphi$ ，求与分母互质的个数。

因为这道题给出 $N$ 的数据范围是 $1e9$ ，所以做不成递推法。只好**单点求 $\varphi$**。

### 实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int phi(int N)//单点求phi
{
     int ans = N, sqr = sqrt(N);
     for (int i = 2; i <= sqr; i++)
     {
          if (N % i == 0)
          {
               ans = ans * (i - 1) / i;
               while (N % i == 0)
               {
                    N /= i;
               }
          }
     }
     if (N >= 2)
     {
          ans = ans / N * (N - 1);
     }
     return ans;
}
signed main()
{
     int x;
     while (cin >> x && x)
          cout << phi(x) << endl;
}
```


---

## 作者：Sora1336 (赞：1)

这题算是比较简单的 $\varphi$ 函数，也是欧拉函数的应用题。个人感觉难度在绿或以下。

题意大概是这样的：给你一个数 $n$ ，然后有分数 $\frac{0}{n}, \frac{1}{n}, \frac{2}{n}...\frac{n-1}{n}$，求这些分数中不可约分的分数的个数。

很明显分子与分母不互质的可以约分，而欧拉函数的定义是一个数以内的数和该数互质的数的个数。那么已经非常显然了，对于给定的数 $n$ ，答案自然就是 $\varphi(n)$ 了。

但是由于这题的 $n$ 范围过大，所以需要单点求 $\varphi$ 。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
long long Phigros(long long n) {   // 求 phi 的函数
	long long res = n, a = n;
	for(int i = 2; i * i <= a; i ++) {
		if(a % i == 0) {
			res = res / i * (i - 1);
			while(a % i == 0) a /= i;
		}
	} if(a != 1) res = res / a  * (a - 1);
	return res;
}
int main() {
	long long x;
	while(cin >> x && x) cout << Phigros(x) << endl;
}
```



---

## 作者：respect_lowsmile (赞：0)

## 欧拉函数的应用

今天刚刚学习了同余问题中的欧拉定理，接触了欧拉函数 $ \varphi(n) $ ，找到了这道题来练习一下如何求 $ \varphi(n) $ 的值。

如果您想学习更多同余知识，您可以[戳这里](https://www.luogu.com.cn/blog/respect-lowsmile/)。

~~一开始链接放错了，给管理大大添麻烦了~~

首先看题目，大致意思就是给定一个数 $ N $ ，求分数 $ \frac{0}{N} , \frac{1}{N} ··· \frac{N-1}{N}$ 中有多少分数是可以约分的，这里题目规定 $ \frac{0}{N} $ 不可约分 , $ \frac{1}{N} $ 可约分，跟我们的正常思路有区别，但是并不影响结果。

### description

欧拉函数( $ \varphi $ ) ， $ \varphi(n) $ 是指小于或等于 $ n $ 的数中与 $ n $ 互质的数的数目，如 $\varphi(8)=4$ 。

### solution

很明显，不能约分的个数就是 $ \varphi(n) $ 的值，我们可以运用定理 $ \varphi(n) = N \times \prod_{i=1}^n(1-\frac{1}{p_i}) $ 来计算 $ \varphi(n) $ 的值，~~如果想看证明过程可以点上面的链接~~，只需枚举分解质因数即可。

### code
```cpp
/*
	欧拉函数 
	date:2022.7.12
	worked by respect_lowsmile
*/
#include<iostream>
using namespace std;
int x;
inline int read()
{
   int s=0,w=1;char ch=getchar();
   while(ch<'0'||ch>'9')
   {  if(ch=='-')  w=-1;  ch=getchar();}
   while(ch>='0'&&ch<='9')
   {  s=s*10+ch-'0'; ch=getchar();}
   return s*w;
}
int phi(int n) 
{
	int ans=n;
	for(int i=2;i*i<=n;++i)
	  if(n%i==0)
	  {
	  	ans=ans/i*(i-1);
	  	while(n%i==0)  n/=i;
	  }
	if(n>1)  ans=ans/n*(n-1);
	return ans;
}
int main()
{
	while(x=read())
	{
		if(x==0)  return 0;
		printf("%d\n",phi(x));
	}
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：0)

## 题意

给定 $n$，存在 $n$ 个分数 $\dfrac{0}{n},\dfrac{1}{n},\dfrac{2}{n}\cdots\dfrac{n-1}{n}$，求问其中哪些数不能约分。

## 解法

注意到不能约分即 $\gcd(n,x)=1$，我们可以考虑对于每一个 $n$ 进行枚举，判断何种情况满足该式，并进行统计。对于每一组时间复杂度都是 $O(n)$，而 $n$ 的最大值可达 $10^9$ 等级，于是不可接受。

于是考虑欧拉函数。

题目没有将 $\dfrac{1}{n}$ 算在不可约分之中，但是题目计算了 $\dfrac{0}{n}$，所以答案就是 $\varphi(n)$。

对正整数 $n$，欧拉函数是小于或等于 $n$ 的正整数中与 $n$ 互质的数的个数，记为 $\varphi(n)$。我们通常会用类似于线性筛的方式进行 $O(n)$ 计算所有的 $\varphi(i)\ (1\le i\le n)$，但是对于这道题目由于 $n$ 的范围过大，我们考虑单点计算。

不难发现，存在一个计算式：

$$\varphi(n)=n\prod\limits_{i=1}^{n}\left(1-\dfrac{1}{p_i}\right)$$

其中 $p_i$ 表示 $n$ 的所有质因数。

只需要分解质因数即可，代码不难实现。

---

## 作者：_Imaginary_ (赞：0)

让我们先通读一遍题目，发现题面很简单：

给定一个数n，求出 $n-φ$$(n)$ 。

$φ$$(n)$是啥？ 这就是在$\dfrac{1}{n},\dfrac{2}{n},...,\dfrac{n}{n}$中有多少个最简分数。

由[欧拉函数](https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E5%87%BD%E6%95%B0/1944850?fr=aladdin)，我们可以知道我们要干什么。

1. 将n因式分解
2. 若$n=p_1^{a_1}\times ... \times p_k^{a_k}$，那么答案就是$\sum\limits_{i=1}^k (1-\dfrac{1}{p_i})$

附上逻辑程序：
```c++
#include<bits/stdc++.h>
using namespace std;
int n,nn,ans;
int main()
{
    cin>>n;
    ans=nn=n;
    for(int i=2;i*i<=n;i++)
    {
    bool ok=0;
    	while(n%i==0)
        {
           nn/=i;
           ok=1;
        }
        if(ok) ans=ans/i*(i-1);
    }
    cout<<(n-ans);
    return 0;
}
```

---

## 作者：Insouciant21 (赞：0)

#### 题意

给出分母 $n(0<n<10^9)$ ，求最简真分数个数。

#### 分析

最简分数的分子分母只有公因数为 $1$ ，即分子分母互质。

由互质可以想到欧拉函数 $\varphi$ 。

关于 $\varphi$ 可以去 [wiki](https://oi-wiki.org/math/euler/) 学习。

因为 $n<10^9$ 所以应该对单个数进行求 $\varphi(n)$ 。

#### AC代码

```
#include <bits/stdc++.h>

using namespace std;

int euler(int n) {
    int phi = n;
    int s = int(sqrt(n) + 0.5);
    for (int i = 2; i <= s; i++) {  // 根据定义进行质因数分解
        if (n % i == 0) {
            phi = phi / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) // 分解到最后是质数
        phi = phi / n * (n - 1);
    return phi;
}

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0)
            break;
        cout << euler(n) << endl;
    }
    return 0;
}
```



---

## 作者：FxorG (赞：0)

大致题意：求多个数的欧拉函数值

这里注意一下：n<=1e9 所以数组存储炸掉，直接对于每一个x进行求φ(x)就可以，不需要先线性筛出所有数 

大概就这样吧，然后就A了。难度绿题左右。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>

#define ll long long

using namespace std;

ll phi(ll x) {
	ll num=x,y=x;
	for(int i=2;i*i<=y;i++) {
		if(y%i==0) {
			num=num/i*(i-1);
			while(y%i==0) y/=i;
		}
	}
	if(y>1) num=num/y*(y-1);
	return num;
}

ll n;

int main() {
	
	while(scanf("%lld",&n)&&n!=0) {
		printf("%lld\n",phi(n));
	}
	
	return 0;
}
```


---

## 作者：plafle (赞：0)

# 本道题的第一篇题解，也是蒟蒻的第一篇题解
## 就是一道求欧拉函数的题目
### 废话不说，上代码(有详细注释）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
bool b[1000005];
int a[100005];
int ax;
int main() {
	b[1] = 1;
	for (int i=2; i<=floor(sqrt(1000005)); i++)
		if (!b[i])
			for (int j = i; j< 1000005 / i; j++)
				b[i * j] = 1; //筛质数
	for (int i=2; i<1000005; i++)
		if (!b[i])
			a[++ax] = i; //得到质数（筛到sqrt（max（n）））即可）
			
	while (~scanf("%d",&n)) {
		if (n == 0)
			break;//退出条件
		int sum = n;
		for (int i=1; i<=ax; i++) {
			if (n % a[i] == 0) {
				while (n % a[i] == 0)
					n /= a[i];
				sum /= a[i]; //先除，保证不越界
				sum *= (a[i] - 1);
			}
		}
		if (n != 1) { //防止有大于sqrt（n）的质数捣乱
			sum /= n;
			sum *= n - 1;
		} 
	
		printf("%d\n",sum); //输出
	}
	return 0;
}
```

---

