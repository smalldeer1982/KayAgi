# Increase and Decrease

## 题目描述

Polycarpus has an array, consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Polycarpus likes it when numbers in an array match. That's why he wants the array to have as many equal numbers as possible. For that Polycarpus performs the following operation multiple times:

- he chooses two elements of the array $ a_{i} $ , $ a_{j} $ $ (i≠j) $ ;
- he simultaneously increases number $ a_{i} $ by $ 1 $ and decreases number $ a_{j} $ by $ 1 $ , that is, executes $ a_{i}=a_{i}+1 $ and $ a_{j}=a_{j}-1 $ .

The given operation changes exactly two distinct array elements. Polycarpus can apply the described operation an infinite number of times.

Now he wants to know what maximum number of equal array elements he can get if he performs an arbitrary number of such operation. Help Polycarpus.

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 4 1
```

### 输出

```
3
```

# 题解

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF246B)

### [题意解析]
有 $n$ 个数字，每次可以让不同的两个数加一，减一。问通过这种操作**最多**能让多少个数字变得相同。

### [思路分析]
**我们发现无论哪两个数加 $1$，减 $1$，$n$ 个数的总和永远都是不变的**。所以我们用贪心的思想，能得到最优的解，也就是数字相同的个数最多解，最多有 $n$ 个，最少有 $n-1$。也就是：

+ $n$ 个数的总和是 $n$ 的倍数，就能使 $n$ 个数全部相同。
+ 否则只能使 $n-1$ 个数相同。

### **[贴上代码]**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,ans;
signed main(){
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>x,ans+=x;
	if(ans % n == 0) cout<<n;
	else cout<<n-1;
	return 0;
}
```


---

## 作者：Vibration886 (赞：1)

### [CF246B Increase and Decrease](https://www.luogu.com.cn/problem/CF246B)

## 题意

给定 $n$ 个数，每次可以将其中不相同的两个数一个加 $1$，一个减 $1$。问最多可以得到多少个相同的数。

## 思路

很容易发现，一个加 $1$，一个减 $1$，那么 $n$ 个数原来的总和肯定不变。

如果这 $n$ 个数的和是 $n$的倍数，那么就是得到最多相同的数的情况。

如果不是，那我们采用贪心的思想，可以得到最多有 $n-1$ 个数相同，剩余的一个数已经无所谓了。

## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int num;
		cin>>num;
		sum+=num;
	}
	sum%n==0?cout<<n:cout<<n-1;//如果总和是n的倍数，输出n，否则输出n-1 
	return 0;
}
```


---

## 作者：TheCliffSwallow (赞：1)

### [CF原题链接](https://codeforces.com/contest/246/problem/B)

### 题意简述
给一个数列 $a$，可以将不相等的两个数分别加一减一，求最多可得多少个相同的数。
### 分析

1. 样例一，数列的和始终为 $3$（因为每次操作是同时加一或减一，下处同理），$3\bmod 2=1\ne0$，输出结果为 $1$。
1. 样例二，数列的和始终为 $6$，$6\bmod 3=0$，输出结果为 $3$。
1. 若输入的数列为 $1\,1\,4\,5\,1\,4$，数列的和始终为 $16$，$16\bmod6=4\ne0$，输出结果应为 $5$。
1. 若输入的数列为 $2\,4\,6$，数列的和始终为 $12$，$12\bmod 3=0$，输出结果应为 $3$。


### 思路
通过分析，我们可以得到一个结论：数列和如果模 $n$ 为 $0$ 的话，那么最多可得 $n$ 个相同的数，否则最多可以得到 $(n-1)$ 个相同的数。其实也可以很容易想出来，如果数列和模 $n$ 为 $0$，那么不断地加一减一最终会把每个数之间的差变成 $0$，如果不为 $0$，那么可以把所有的多余的加一或减一都给同一个数，那么最后就有一个数不同于其他数，最多有 $(n-1)$ 个数相同。

### AC CODE
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,s,a[100005];
int main(){
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];//计算数列和
	}
	s%n==0 ? cout<<n:cout<<n-1;//判断数列和模n是否为0
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

给出 $n$ 个数，每次操作可以使一个数加 $1$，一个数减 $1$。问经过若干次操作后最多有多少个数是相等的。

## 思路

经过简单思考容易发现，一个数加 $1$，一个数减 $1$，$n$ 个数的总和是不变的。

总和不变，如果 $n$ 个数的总和是 $n$ 的倍数，就说明可以通过操作使得所有数都相等。否则，我们可以舍弃一个数，让其他数相等，每个数都和他一起进行操作，就一定能有 $n-1$ 个数相等。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum,x;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		sum+=x;
	}
	if(sum%n==0)printf("%lld",n);
	else printf("%lld",n-1);
	return 0;
}
```

---

## 作者：HIMmeqq (赞：0)

## 0.题意简化：

给定一个长度为 $n$ 的一个序列，从中随意选取2个数 $a_i$ 和 $a_j$，记 $ a_{i} = a_{i} + 1 $ 和 $ a_{j} = a_{j} - 1 $ 为一次操作，总共可以进行无限次操作，问经过若干次操作之后，最多能有几个项一样。


## 1.分析题意：

考虑贪心的思想。发现不是 $n$ 就是 $n - 1$。再观察一下，这些例子的特点，不难发现，每个数的和为 $n$ 的倍数时，答案为 $n$，如果不是 $n$ 的倍数，答案就是 $n - 1$。
证明如下：

设所有数总和为 $s$，$t$ 为 $s \ \bmod \ n$。

因为每一次操作不改变总和，考虑进行分类讨论。

情况1：当 $t = 0$ 时，可以将所有数都变为 $\Large\frac{s}{n}$。

情况2：当 $t \ne 0$时，除了有一项为 $t$，其余均可变为 $\Large\frac{s - t}{n}$。

综上，当 $s \ \bmod \ n = 0$ 时，答案即为 $n$，当 $ s \ \bmod \ n \ne 0$ 时，答案即为 $n - 1$。
## 2.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+7;
int n,a[maxn],tmp,sum = 0;
int main()
{
	cin >> n;
	while(cin >> tmp)
    {
        sum += tmp;
    }
	sum % n == 0 ? cout << n : cout << n - 1;
 	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

## [$\color{Blue} \text{CF246B  Good Sequences}$](https://www.luogu.com.cn/problem/CF264B)

### $\large \text{Describe}$
给定一个严格上升的序列，求其最长的子序列，满足子序列中任两个相邻的元素不互质。

### $\large \text{Solution}$

这题要求的一眼看过去就是类似于最长上升子序列的东西，不如说是最长相邻不互质子序列。管他最长啥啥啥子序列，$O(n^2)$ 都是一定可以做到的，只要枚举这一项的前一项就好了。

至于优化——最长上升子序列可以用二分（我喜欢线段树/树状数组来搞）等算法优化，这个东西就要用一个技巧了。

首先我们考虑一个元素 $a_i$ 之前的所有元素，如果与 $a_i$ 有相同的质因子，这个元素的前一个元素可以是它。设 $\text{dp}_i$ 为以它结束的最长相邻不互质子序列，$\text{dp}_{i}= \max \limits_{\gcd(a_i,a_j)>1} \normalsize ( \text{dp}_{j}+1)$。


在这个元素之后，如果又和 $a_i$ 质因子相同的元素 $a_k$ ，那么之前 $a_i$ 枚举过的 $j$ 会再被枚举一遍。为了避免这种多次计算，我们考虑用一个数组 $f$，$f_x$ 表示当前枚举的元素之前，含有质因子 $x$ 的元素的 $\text{dp}$ 值的最大值。我们就可转化方程式，如下：

$\text{dp}_i= \max \limits_{x|a_i,x\in \text{prime}} (f_x+1)$

然后算完这个 $\text{dp}$ 值，这个元素可以为下一个元素服务了，我们要更新一下 $f$ ，对于所有的是 $a_i$ 是质因子的 $x$：

$f_x = \max \{ f_x,\text{dp}_i\}$

这样时间复杂度变成每个元素找出其质因子的枚举次数加上其质因子数量，应该是 $O(n \sqrt{n})$ 。

至于[代码](https://paste.ubuntu.com/p/PZmwhsCZxb/)，过于烂，自己看吧。

---

## 作者：Ninelife_Cat (赞：0)

~~随便猜了个结论居然对了。~~

因为我们的每次操作是将一个数加上 $1$，将另一个数减去 $1$，所以这 $n$ 个数的总和是不变的。

首先如果这 $n$ 个数的和是 $n$ 的倍数，那就说明通过一系列操作，必然可以得到 $n$ 个相同的数。

然后如果这 $n$ 个数的和不是 $n$ 的倍数，那么考虑贪心。我们随机挑选一个数，然后把多余的加 $1$ 减 $1$ 操作全部丢给它，从而保证另外的 $n-1$ 个数全部相同。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,sum;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a,sum+=a;
	if(sum%n==0) cout<<n;
	else cout<<n-1;
	return 0;
}

---

