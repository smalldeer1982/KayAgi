# [ABC103C] Modulo Summation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc103/tasks/abc103_c

$ N $ 個の正整数 $ a_1,\ a_2,\ ...,\ a_N $ が与えられます。

非負整数 $ m $ に対して、$ f(m)\ =\ (m\ mod\ a_1)\ +\ (m\ mod\ a_2)\ +\ ...\ +\ (m\ mod\ a_N) $ とします。

ここで、$ X\ mod\ Y $ は $ X $ を $ Y $ で割った余りを表します。

$ f $ の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 2\ \leq\ N\ \leq\ 3000 $
- $ 2\ \leq\ a_i\ \leq\ 10^5 $

### Sample Explanation 1

$ f(11)\ =\ (11\ mod\ 3)\ +\ (11\ mod\ 4)\ +\ (11\ mod\ 6)\ =\ 10 $ が $ f $ の最大値です。

## 样例 #1

### 输入

```
3
3 4 6```

### 输出

```
10```

## 样例 #2

### 输入

```
5
7 46 11 20 11```

### 输出

```
90```

## 样例 #3

### 输入

```
7
994 518 941 851 647 2 581```

### 输出

```
4527```

# 题解

## 作者：Brian_WBY (赞：7)

题意：求
$$f(m)=\sum_{i=1}^{n}m\bmod a_i$$
的最大值，$m$是任意整数。

显然，$x\bmod y\leq y-1$，所以
$$f(m)\leq\sum_{i=1}^{n}a_i-1$$

求出了理论最值后，我们需要构造一组值来说明这个值取得到，如何构造呢？

我们考虑对任意$a_i$，$m\bmod a_i$什么时候取到$a_i-1$，由余数定义，取$m=ka_i-1(k\in\mathbf{N}^* )$即可。

所以对于所有$a_i$，取
$$m=\prod_{i=1}^{n}a_i-1$$
即可。

所以能取到的最大值就是

$$\sum_{i=1}^{n}a_i-1$$

那代码就很好写了：

```cpp
#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);//输入n
	int ans=0,x;
	for (int i=1;i<=n;++i)//输入每个数，这样可以省数组
	{
		scanf("%d",&x);
		ans+=x-1;
	}
	printf("%d\n",ans);//输出答案，记得换行
	return 0;
}
```

因为$3000\times10^5<2147483647$，所以使用`int`即可

---

## 作者：RioBlu (赞：4)

这是翻译
```
输入N和a1,a2,...,aN

f(m)=(m mod a1)+(m mod a2)+...+(m mod aN)

问f(m)最大是多少（m可为任意整数）

其中2≤N≤3000,2≤ai≤10^5
```
其实十分好理解我们令w满足：
```
m mod a1 =a1-1  得 m-a1+1 是 a1 的倍数,即 m+1 是 a1 的倍数
m mod a2 =a2-1  得 m-a2+1 是 a2 的倍数,即 m+1 是 a2 的倍数
...
m mod aN =aN-1  得 m-aN+1 是 aN 的倍数,即 m+1 是 aN 的倍数
```

此时$f(m)$最大

那么我们令$m=(a_1*a_2*...*a_N)-1$

那这个问题就迎刃而解了

此时$w+1=(a_1*a_2*...*a_N)$，是$a_1,a_2,...,a_N$的倍数

此时$f(m)=(a_1+a_2+...+a_N)-N$，没有比这个更大的了

---

## 作者：晴空一鹤 (赞：2)

这道题其实就是让我们求式子 $\sum\limits_{i=1}^{n}m\,\bmod\,a_i$ 在 $m$ 为整数时的最大值。

该怎么做呢？

首先，我们可以发现这个式子的最大值必定不会超过 $\sum\limits_{i=1}^{n}(a_i-1)$ （~~很显然~~）。

而 $m$ 又可以为任意整数，因此我们就猜想：对于任意一个数组 $a$ ,一定存在一个数 $m$ ,使得 $\sum\limits_{i=1}^{n}m\,\bmod\,a_i$ $=$ $\sum\limits_{i=1}^{n}(a_i-1)$  。

但光想不管用，我们还需要证明，证明过程如下：

$1.$ 设 $k$ 为  $\displaystyle\prod_{i = 1}^{n}a_i$ ，此时的 $k$ 一定为整数（因为对于任意 $i$ , $a_i$ 均为整数）。

$2.$ 设 $m$ 为 $k-1$ , 此时对于任意的 $i$ ,均满足 ${m\,\bmod\,a_i}=a_i-1$，所以这时式子 $\sum\limits_{i=1}^{n}m\,\bmod\,a_i$ 的值为     $\sum\limits_{i=1}^{n}(a_i-1)$ ,且 $m$ 为整数，而这个结果恰为此式能取到的最大值。

$3.$所以，对于任意的 $a$ 数组， $\sum\limits_{i=1}^{n}m\,\bmod\,a_i$ 的最大值为 $\sum\limits_{i=1}^{n}(a_i-1)$ 。


代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,sum,x;
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
  cin>>x;
  sum+=x;
  }
  cout<<sum-n<<endl;
}
```








---

## 作者：Eason_AC (赞：2)

## Content
给定 $n$ 个数 $a_1,a_2,\dots,a_n$，定义 $f(m)=\sum\limits_{i=1}^n(m\bmod a_i)$，求 $f(m)$ 的最大值。

**数据范围：$2\leqslant n\leqslant 3000$，$2\leqslant a_i\leqslant 10^5$。**
## Solution
由于 $m$ 可以是任意整数，因此我们直接构造出 $M=\operatorname{lcm}\{a_i\}-1$，此时，我们不难发现 $\forall i\in[1,n]$，$M\bmod a_i=a_i-1$。因此答案就是 $\sum\limits_{i=1}^n (a_i-1)$。

代码就不放了。

---

## 作者：BeetyX (赞：0)

题目说要我们输入一个数列（这里假设是a[n]），然后找到一个数（这里假设是M），使得这个数除以数列
里的每一个数的余数相加起来最大，最后输出这个和

其实这个涉及到余数的数学知识，既然余数要大，那么这个M就要比数列里的数小并且尽可能接近。

## **推理过程如下：**

我们知道：A÷B=C······D，D尽可能大，但是不可能超过除数B，最大也只能是B-1。放到这道题里去看，余数要尽量大，所以得出：

M mod a[n]=a[n]-1
 
移项不难发现：M+1是a[n]的若干倍，所以M=a[n]*k-1（k为正整数）
 
接下来要用到余数的数学知识了：由于a[n]各不相同，所以只能取所有a[n]的乘积，即M=a[1]*a[2]*a[3] *…… *a[n]-1就好了

带入进去，最终输出的数ans就是(a[1]​+a[2]​+...+a[n]​)−N ，没有比这个更大的了

------------
## 代码如下
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,ans=0;//ans用来储存最后的数组所有数之和
	cin>>n;
	int a[n];
	for(int i=1;i<=n;i++)//输入数组
                               
	{
        cin>>a[i];
	}
	for(int j=1;j<=n;j++)//计算和
    {
        ans=ans+a[j];
    }
    cout<<ans-n;//输出
	return 0;
}
```

---

## 作者：MujicaSaki (赞：0)

### 简要题意:
给出一个数列，要求任意一个数使得除以这个数列的每一个数的和最大，求出这个数。

### 思路：

运用余数的知识，可以知道，一个数模任意一个数，余数最大的情况就是这个数 $-1$。

我们只用把数列里的数每个 $-1$ 然后加起来就可以了。

### 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],s;
int main(){
cin>>n;
for(int i=1;i<=n;i++) cin>>a[i];
for(int i=1;i<=n;i++) s+=a[i]-1;
cout<<s;
}
```


---

## 作者：3a51_ (赞：0)

### 题目大意

给定 $n$ ,数组 $a[1…n]$ ，求出 $\sum{m}\mod{a_i}$ 。

### 思路分析

可以看出，对于任何的 $x$ ，当 $m=x\times k-1$ 时， $m \mod x=x-1$ 。

所以取 $m=[a_1,a_2...a_n]-1$ 就可以使得和最大，达到 $\sum a[i]-1$ 。

### 代码分析

在输入时，每次将和加上当前数字之后减一，最后输出。

### AC代码

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int x,sum=0;
	while(n--)
		cin>>x,sum+=x-1;//加和
	cout<<sum;//输出
	return 0;
}
```

---

## 作者：hero_brine (赞：0)

**$LateX$可能无法正常显示，请在我的博客查看：[myblog](https://hero-brine.blog.luogu.org/solution-at4172)**

题意：给出$N$和$a_1,a_2,a_3,...,a_n$,求出
$$
f(m)=(\displaystyle\sum\limits_{i=1}^n(m\ mod\ a_i))_{max}
$$
不难验证当$m=\displaystyle\prod_{i=1}^n(a_i-1)$时
$$
f(m)=\displaystyle\sum\limits_{i=1}^n(a_i-1)
$$
~~一行perl代码或成最短题解？~~
```perl
<>;$\+=$_-1for glob<>;print
```

---

