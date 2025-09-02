# [ABC052C] Factors of Factorial

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc052/tasks/arc067_a

整数 $ N $ が与えられます。 $ N! $ の正の約数の個数を $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1≦N≦10^3 $

### Sample Explanation 1

$ 3! $ $ =6 $ です。$ 6 $ の正の約数は $ 1,2,3,6 $ の $ 4 $ 個なので、$ 4 $ を出力します。

## 样例 #1

### 输入

```
3```

### 输出

```
4```

## 样例 #2

### 输入

```
6```

### 输出

```
30```

## 样例 #3

### 输入

```
1000```

### 输出

```
972926972```

# 题解

## 作者：苏联小渣 (赞：3)

## 题目大意

求 $n!$ （即 $n$ 的阶乘）的约数个数。

## 分析

求约数个数，考虑用约数个数定理：

若一个正整数 $n>1$，且可分解为一系列质因数的积：

$$n=\prod_{i=1}^kp_i^{a_i}$$

则 $n$ 的约数个数 $f(n)$ 为：

$$f(n)=\prod_{i=1}^k(a_i+1)$$

接下来思考如何用该定理实现。

由于观察到数据并不大，$n \le 1000$，我们可以考虑从 $1$ 到 $n$，每乘到一个数时，都分解一次质因数，用一个 map 数组统计可分解的质因数个数。中间的每个数可以分解的质因数指数都加 1，到最后就统计出了 $n!$ 的质因数分解形式。时间复杂度 $\mathcal{O}(n^2)$。

思路如此，那么接下来介绍一下本题需要用到的 map 相关操作：

```
1、map <int, int> mp
（定义一个 map 类型的容器）
2、map <int, int> :: iterator p
（定义一个 map 类型的指针变量 p）
其中对于 mp[a]=b,p->first 表示 a,p->second 表示 b。
3、for (p=mp.begin(); p!=mp.end(); p++)
（遍历 map 数组）
```

那么 map 容器有何好处呢？

map 表示映射，即不需要像一般数组一样占用太多的内存，并且可以支持负数下标。

map 还有其他较为常用的函数，可以参考[oi-wiki](https://oi-wiki.org/lang/csl/associative-container/)。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mo = 1e9 + 7;
int n, s=1;
map <int, int> mp;
map <int, int> :: iterator p;
void work(int x){
	for (int i=2; i<=x; i++) while (x % i == 0) x /= i, mp[i] ++;
}
signed main(){
	scanf ("%lld", &n);
	for (int i=1; i<=n; i++) work(i);
	for (p=mp.begin(); p!=mp.end(); p++) s = s *  (p->second + 1) % mo;
	printf ("%lld\n", s);
	return 0;
}
```

---

## 作者：_wjr_ (赞：2)

## 0X01 题目大意

题目的大意十分明了：给出 $N$，让我们求 $N!$ 的约数个数。

那么，一个数的约数到底有多少个呢？

## 0X02 解题思路

假设一个数为 $x$，它可以表示为 $ p_1^{a_1} \times p_2^{a_2} \times \cdots \times p_k^{a_k} $ ，那么，对于每一个 $p_1 , p_2 , \cdots , p_k $，分别能取 $a_1,a_2, \cdots ,a_k$ 个。而且，任意情况都是可行的。如果都取 $0$ 的话，这个约数就是 $1$。

那么，这个问题就变成了如何将 $N!$ 中每个数分解质因数的问题了。我们可以一个一个数字暴力枚举，如果这个数是质数，那么得到的质因子个数都保存在一个数组中，并把原数除以这个质数。如果它是一个合数，其中的每个质因子必然在之前已经被计算完毕，这个数已经不能被这个合数整除了，无需进行特殊处理。如果这方面不太明白如何操作，可以去[P2043 质因子分解](https://www.luogu.com.cn/problem/P2043)进行练习。

最后，我们将这个数组中的每一项加一后相乘在取模，我们就得到了答案。

接下来，献上 AC 代码！

## 0X03 AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int p = 1000000007;
int a[1010];

signed main()
{
	int n;
	int ans = 1;
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
	 	int x = i;//N! = 1 * 2 * 3 * … * N，对于其中每一个数，都对其分解并记录下来，这样就无需先求N!的具体值，再分解了。
	
		for (int j = 2; j <= i; j++)
		{
		    while (x % j == 0) 
		    {
		        a[j]++;
		        x /= j;
		    }//分解质因子
		}
  	}	
	for (int i = 1; i <= 1000; i++)
	{
        if (a[i]) 
        {
            ans *= (a[i] + 1);
            ans %= p;//相乘，取模
        }
	}
	cout << ans;
    return 0;
}
```

这样，又一道题目就解出来了。感谢各位的观看！

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2286)

小学生又双叒叕来写题解啦！

这题要用到[因数个数定理](https://baike.baidu.com/item/%E7%BA%A6%E6%95%B0%E4%B8%AA%E6%95%B0%E5%AE%9A%E7%90%86/4926961?fr=aladdin)，没学过的童鞋自己了解一下。

由于和质数有关，我使用**质数筛法**。

我使用较快的**欧拉筛法**算质数（[想学就做这题](https://www.luogu.com.cn/problem/P3383)）。

事实上，由于范围不大，使用普通的埃氏筛也行。

最后一个问题是：枚举质因数个数。

相信这不难，只需**暴力分解质因数**即可。

把上文提到的三个模块结合起来即可。

## 送上AC代码

```cpp
#include <iostream>
#include <cstdio>
#define MOD (int)(1e9 + 7)
using namespace std;
int p[1005], cur;
bool flag[1005]; //true 是合数，false 是质数。 
void ES(int n)
//欧拉筛。 
{
	flag[0] = true, flag[1] = true; //特判。 
	for (long long i = 2; i <= n; i++)  //枚举范围。 
	{
		if (flag[i] == false)  //i 是质数。 
		{
			cur++;
			p[cur] = i;  //存入质数数组。 
		}
		//扫一遍 p 数组。此处 i 的作用为：倍数。
		for (int j = 1; j <= cur; j++)
		{
			//很好理解。超出范围，用不着枚举。 
			if (i * p[j] > n) break; 
			//若没有跳出，记录合数（筛掉）。
			flag[i * p[j]] = true;  
			//较难理解。简单地说，p[j] 的"过关门槛"比 i低，所以在这之前，已经筛过了。  
			if (i % p[j] == 0) break;  
		}
	}
}
int fac[1005]; //因数个数。 
void calc(int n) //作用为：分解 n的质因数。 
{
	for (int i = 1; i <= cur && n != 1; i++)
		while (n % p[i] == 0)
		{
			fac[i]++;
			n /= p[i];
		}
}
int main()
{
	int n;
	scanf("%d", &n);
	ES(n);
	for (int i = 1; i <= n; i++) //枚举n中的每一个数。 
	{
		int t = i;
		calc(t); //分解 t。 
	}
	long long mul = 1;
	//别忘开 long long，为什么开不解释。 
	for (int i = 1; i <= cur; i++) mul = (mul * (fac[i] + 1)) % MOD;   //因数个数定理。 
	printf("%lld\n", mul); //AT题祖传换行。
 	return 0;
}
```
超时是不可能的，跑得飞快！

[不信戳这](https://www.luogu.com.cn/record/68143714)

---

