# GCD of Polynomials

## 题目描述

Suppose you have two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/b88d8c9afbcdbe4c3db30f4f8047f16a3a48c8eb.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/e0c93f76951451d9aabeb4047e1f1124cfc2b66d.png). Then polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) can be uniquely represented in the following way:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/c5e7dcb363dde0ba8872328b8e411c128512b38f.png)This can be done using [long division](https://en.wikipedia.org/wiki/Polynomial_long_division). Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/a1f26d7c8115e83b311bbacc16505e6f20f92b7d.png) denotes the degree of polynomial $ P(x) $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/026a0fc1a864c69852c699730e0a6f2d32f753be.png) is called the remainder of division of polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png) by polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png), it is also denoted as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/6e44041e1df78606fc571f5db249361dad8df62e.png).

Since there is a way to divide polynomials with remainder, we can define Euclid's algorithm of finding the greatest common divisor of two polynomials. The algorithm takes two polynomials ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png). If the polynomial ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ebb5c58177e55fa198a7a231f3c0e4b1f18a6a49.png) is zero, the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/1a8148c316d81cb0dcf0ac6a016f160db2da72c1.png), otherwise the result is the value the algorithm returns for pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png). On each step the degree of the second argument decreases, so the algorithm works in finite number of steps. But how large that number could be? You are to answer this question.

You are given an integer $ n $ . You have to build two polynomials with degrees not greater than $ n $ , such that their coefficients are integers not exceeding $ 1 $ by their absolute value, the leading coefficients (ones with the greatest power of $ x $ ) are equal to one, and the described Euclid's algorithm performs exactly $ n $ steps finding their greatest common divisor. Moreover, the degree of the first polynomial should be greater than the degree of the second. By a step of the algorithm we mean the transition from pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/5a51ce4106123f55c64d5fbd31176d2fcf184db6.png) to pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF901B/ad56ca03078389def1a802276b6af4c037ddb9af.png).

## 说明/提示

In the second example you can print polynomials $ x^{2}-1 $ and $ x $ . The sequence of transitions is

 $ (x^{2}-1,x)→(x,-1)→(-1,0). $ There are two steps in it.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
0 1
0
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2
-1 0 1
1
0 1
```

# 题解

## 作者：JK_LOVER (赞：2)

## 题意
构造两个多项式函数 $g(x),f(x)$ 满足执行 $\gcd$ 时运行次数为 $n$ 。
## 分析
### 一：
多项式相模，若：
$$
A(x) = B(x)\times C(x)+D(x)
$$
则：
$$
A(x)\equiv D(x) (mod \ C(x))
$$
### 二：
构造函数：
$$
\gcd(C(x)\times A(x)\times B(x)+A(x),A(x)\times B(x))$$
$$ \Rightarrow \gcd(A(x)\times B(x),A(x))\Rightarrow \gcd(A(x),0) 
$$
因为要相模 $n$ 次，又要最高项小于等于 $n$ 次，所以每次只能减少一次。令：
$$
A(x) = 1,B(x)=x
$$
### 三：
考虑递推，令 $dp[i][j]$ 是，最高项为 $i$ 时，每一位的系数。
$$
dp[i][j] = dp[i-2][j] + dp[i-1][j-1] (1\le j)
$$
$$
dp[i][j] = dp[i-2][j] (j=0)
$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x = 0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int dp[210][210],n;
int main()
{
	n = read();
	dp[1][1] = 1;
	dp[0][0] = 1;
	for(int i = 2;i <= n;i++)
	{
		for(int j = 0;j <= i;j++)
		{
			if(j==0) dp[i][j] = dp[i-2][j];
			else dp[i][j] = (dp[i-2][j]+dp[i-1][j-1])%2;
		}
	}
	printf("%d\n",n);
	for(int i = 0;i <= n;i++)
	printf("%d ",dp[n][i]);
	printf("\n%d\n",n-1);
	for(int i = 0;i <= n-1;i++)
	printf("%d ",dp[n-1][i]);
	return 0*printf("\n");
}
```
[地址](https://www.luogu.com.cn/blog/xzc/solution-cf901b)

---

## 作者：Missa (赞：0)

半是乱搞地过了。于是决定来写一篇题解记录一下。

笔者提醒：文章最后有乱搞证明。

题意：给定 $n$，构造两个不超过 $n$ 次的多项式 $F(x),G(x)$，多项式的系数 $\in \{-1, 0, 1\}$，使得使用辗转相除法求出 $F(x),G(x)$ 的 gcd 刚好用 $n$ 次。

类比整数的 gcd，我们可以考虑递推。设对 $F_n(x)$ 与 $F_{n-1}(x)$ 求 gcd 刚好需要 $n$ 次，现在考虑弄出 $F_{n+1}(x)$ 来。

首先，明显 $\deg F_n(x) > \deg F_{n-1}(x)$，所以 $F_n(x)$ 应该恰为 $n$ 次。

设 $F_n(x) = A(x)F_{n-1}(x)+B(x)F_{n-2}(x)$，类比斐波那契数列的 $f_n=f_{n-1}+f_{n-2}$，此处构造 

$$A(x)=x,B(x)=1$$

且 

$$F_0(x)=1,F_1(x)=x$$

用一个数列表示 $F_n(x)$ 的系数，令 $s_{i,j}=[x^j]F_i(x)$，于是能写出递推式 $s_{i+1,j}=s_{i,j-1}+s_{i-1,j}$。

交上去后，WA 了。

打开 CF 看看具体错误，发现

```
Input
3
Output
3
0 2 0 1 
2
1 0 1 
Answer
3
0 0 0 1
2
-1 0 1
```

原因是输出的系数不在 $\{-1,0,1\}$ 的范围内。

但是，思路真的不对吗？

```
Input
1
Answer
1
0 1
0
1


Input
2
Answer
2
-1 0 1
1
0 1
```

观察标准答案，你会发现两个 $2$ 次多项式和两个 $1$ 次多项式是一样的，这证明了递推可行。但是，$F_3(x)=F_2(x)-F_1(x)$，这说明 $B(x)$ 可以取 $-1$。

这样，可能从 $F_n(x)$ 和 $F_{n-1}(x)$ 无法到 $F_{n-2}(x)$ 了，但是，我们能到 $-F_{n-2}(x)$。辗转相除中，正负并没有那么重要，由唯一分解定理，将被除数取相反数仅仅会让余数也取相反数，这样归纳下去仅仅会让我们初始的 $F_0(x)$ 有可能变成 $-1$，仍然不影响最后的辗转相除。
于是，乱搞做法来了：在代码中加入判断，如果 $B(x)=1$ 时会让新的 $F_n(x)$ 有系数不属于 $\{-1,0,1\}$ 时，将 $B(x)$ 取为 $-1$。

算了几项觉得很对，于是就交了，于是……就……过……了……

上代码（我不会说本来想用封装好的 `poly` 类的）：

```cpp
#include <cstdio>
using namespace std;
const int M = 155;
int s[M][M], n;
int main(){
	scanf("%d", &n);
	s[0][0] = 1;
	s[1][1] = 1;
	for(int i = 1; i <= n; i++){
		//先验证 F_n(x)=F_{n-1}(x)+F_{n-2}(x) 的情况 
		s[i+1][0] = s[i-1][0];
		for(int j = 1; j <= i+1; j++){
			s[i+1][j] = s[i][j-1] + s[i-1][j];
		}
		//进行判断 
		bool f = 1;
		for(int j = 0; j <= i+1; j++){
			if(s[i+1][j] < -1 || s[i+1][j] > 1) {f = 0; break;}
		}
		if(f) continue;
		//如果不行，就让 F_n(x)=F_{n-1}(x)-F_{n-2}(x)
		s[i+1][0] = -s[i-1][0];
		for(int j = 1; j <= i+1; j++){
			s[i+1][j] = s[i][j-1] - s[i-1][j];
		}
	}
	printf("%d\n", n);
	for(int i = 0; i <= n; i++)
		printf("%d ", s[n][i]);
	printf("\n%d\n", n-1);
	for(int i = 0; i < n; i++)
		printf("%d ", s[n-1][i]);
}
```

当然，只知道乱搞能过是不够的，我们还需要知道乱搞为什么能过。翻官方题解找到一句：

>It can be directly checked for given constraints that you can always choose  +  or  -  to satisfy coefficients constraints.

所以这个乱搞居然是对的！（虽然证明是：It can be directly checked）

那为什么 It can be directly checked 呢？

~~题解没说~~

往评论区一翻，有人也提出了这个问题。

回应？

[丢下了这个链接](https://mathoverflow.net/questions/285107/what-are-the-properties-of-this-polynomial-sequence)

实在看不懂了，总之这个乱搞是对的。于是这篇~~讲解如何乱搞的~~题解就结束了。

---

