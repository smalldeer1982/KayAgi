# 题目信息

# Divide and Sum

## 题目描述

You are given an array $ a $ of length $ 2n $ . Consider a partition of array $ a $ into two subsequences $ p $ and $ q $ of length $ n $ each (each element of array $ a $ should be in exactly one subsequence: either in $ p $ or in $ q $ ).

Let's sort $ p $ in non-decreasing order, and $ q $ in non-increasing order, we can denote the sorted versions by $ x $ and $ y $ , respectively. Then the cost of a partition is defined as $ f(p, q) = \sum_{i = 1}^n |x_i - y_i| $ .

Find the sum of $ f(p, q) $ over all correct partitions of array $ a $ . Since the answer might be too big, print its remainder modulo $ 998244353 $ .

## 说明/提示

Two partitions of an array are considered different if the sets of indices of elements included in the subsequence $ p $ are different.

In the first example, there are two correct partitions of the array $ a $ :

1. $ p = [1] $ , $ q = [4] $ , then $ x = [1] $ , $ y = [4] $ , $ f(p, q) = |1 - 4| = 3 $ ;
2. $ p = [4] $ , $ q = [1] $ , then $ x = [4] $ , $ y = [1] $ , $ f(p, q) = |4 - 1| = 3 $ .

In the second example, there are six valid partitions of the array $ a $ :

1. $ p = [2, 1] $ , $ q = [2, 1] $ (elements with indices $ 1 $ and $ 2 $ in the original array are selected in the subsequence $ p $ );
2. $ p = [2, 2] $ , $ q = [1, 1] $ ;
3. $ p = [2, 1] $ , $ q = [1, 2] $ (elements with indices $ 1 $ and $ 4 $ are selected in the subsequence $ p $ );
4. $ p = [1, 2] $ , $ q = [2, 1] $ ;
5. $ p = [1, 1] $ , $ q = [2, 2] $ ;
6. $ p = [2, 1] $ , $ q = [2, 1] $ (elements with indices $ 3 $ and $ 4 $ are selected in the subsequence $ p $ ).

## 样例 #1

### 输入

```
1
1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
2
2 1 2 1```

### 输出

```
12```

## 样例 #3

### 输入

```
3
2 2 2 2 2 2```

### 输出

```
0```

## 样例 #4

### 输入

```
5
13 8 35 94 9284 34 54 69 123 846```

### 输出

```
2588544```

# AI分析结果

### 题目翻译
## 划分与求和

### 题目描述
给定一个长度为 $2n$ 的数组 $a$。考虑将数组 $a$ 划分为两个长度均为 $n$ 的子序列 $p$ 和 $q$（数组 $a$ 中的每个元素应恰好属于一个子序列：要么在 $p$ 中，要么在 $q$ 中）。

我们将 $p$ 按非降序排序，将 $q$ 按非升序排序，排序后的版本分别记为 $x$ 和 $y$。那么，一种划分的代价定义为 $f(p, q) = \sum_{i = 1}^n |x_i - y_i|$。

求数组 $a$ 所有正确划分下 $f(p, q)$ 的和。由于答案可能非常大，请输出其对 $998244353$ 取模的结果。

### 说明/提示
如果子序列 $p$ 中包含的元素的索引集合不同，则认为数组的两种划分是不同的。

在第一个样例中，数组 $a$ 有两种正确的划分：
1. $p = [1]$，$q = [4]$，则 $x = [1]$，$y = [4]$，$f(p, q) = |1 - 4| = 3$；
2. $p = [4]$，$q = [1]$，则 $x = [4]$，$y = [1]$，$f(p, q) = |4 - 1| = 3$。

在第二个样例中，数组 $a$ 有六种有效的划分：
1. $p = [2, 1]$，$q = [2, 1]$（原数组中索引为 $1$ 和 $2$ 的元素被选入子序列 $p$）；
2. $p = [2, 2]$，$q = [1, 1]$；
3. $p = [2, 1]$，$q = [1, 2]$（索引为 $1$ 和 $4$ 的元素被选入子序列 $p$）；
4. $p = [1, 2]$，$q = [2, 1]$；
5. $p = [1, 1]$，$q = [2, 2]$；
6. $p = [2, 1]$，$q = [2, 1]$（索引为 $3$ 和 $4$ 的元素被选入子序列 $p$）。

### 样例 #1
#### 输入
```
1
1 4
```
#### 输出
```
6
```

### 样例 #2
#### 输入
```
2
2 1 2 1
```
#### 输出
```
12
```

### 样例 #3
#### 输入
```
3
2 2 2 2 2 2
```
#### 输出
```
0
```

### 样例 #4
#### 输入
```
5
13 8 35 94 9284 34 54 69 123 846
```
#### 输出
```
2588544
```

### 算法分类
组合数学

### 综合分析与结论
这些题解主要围绕如何计算数组划分后的代价总和展开。多数题解先得出结论：每种划分的值都为前 $n$ 大的数之和减去前 $n$ 小的数之和，再乘以组合数 $\binom{2n}{n}$。不同题解的区别在于证明结论的方式和计算组合数的方法。部分题解通过反证法证明结论，部分题解通过分析元素的贡献来证明。在计算组合数时，有的使用快速幂求逆元，有的使用线性求逆元。

### 所选题解
- **作者：tommymio (赞：10)，4星**
  - **关键亮点**：思路简洁，直接给出结论并通过简单的分类讨论进行证明，清晰明了。
- **作者：Zenith_Yeh (赞：5)，4星**
  - **关键亮点**：详细地证明了结论，通过设数列和分配元素的方式，逻辑严谨，且给出了完整的代码实现。
- **作者：白鲟 (赞：3)，4星**
  - **关键亮点**：从特殊情况拓展到一般情况，分析每个元素的贡献，思路独特，同时给出了代码实现和注意事项。

### 重点代码
#### tommymio 的思路代码片段
```plaintext
每种划分的值都为前 $n$ 大的数之和减去前 $n$ 小的数之和。
答案就为 $(\sum_{x\in S_1} a_x-\sum_{x\in S_2} a_x)\times\binom{2n}{n}$，其中 $S_1$ 为前 $n$ 大的数构成的集合，$S_2$ 为前 $n$ 小的数构成的集合。
```
**核心实现思想**：先确定每种划分的固定值，再乘以划分的方案数得到最终答案。

#### Zenith_Yeh 的代码片段
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
#define mod 998244353
using namespace std;
int n,a[150000*2+5],f[150000*2+5],inv[150000*2+5],ans;
int ksm(int x,int y)//由于要用到逆元求组合数，所以要快速幂
{	int res=1;
	while(y)
	{	if(y&1)res=x*res%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main()
{	cin>>n;
	for(register int i=1;i<=2*n;++i)cin>>a[i];
	sort(a+1,a+n+n+1);//排序
	f[0]=1;
	for(register int i=1;i<=2*n;++i)//求逆元
	{	f[i]=f[i-1]*i%mod;
		inv[i]=ksm(f[i],mod-2);
	}
	for(register int i=2*n;i>=1;--i)//计算答案
	{	if(i<=n)ans=(ans+mod-f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为小的n个数，则减
		else ans=(ans+f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为大的n个数，则加
	}
	cout<<ans;
	return 0;
}
```
**核心实现思想**：先对数组排序，然后通过快速幂求逆元计算组合数，最后根据元素大小计算答案。

#### 白鲟的代码片段
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=3e5,mod=998244353;
int n,ans,factorial=1,t=1,a[maxn+1];
int power(int base,int exponent)
{
	int res=1;
	while(exponent)
	{
		if(exponent&1)
			res=(long long)res*base%mod;
		base=(long long)base*base%mod;
		exponent>>=1;
	}
	return res%mod;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=(n<<1);++i)
		scanf("%d",&a[i]);
	sort(a+1,a+(n<<1)+1);
	for(int i=n+1;i<=(n<<1);++i)
		factorial=(long long)factorial*i%mod;
	for(int i=1;i<=n;++i)
		t=(long long)t*i%mod;
	factorial=(long long)factorial*power(t,mod-2)%mod;
	for(int i=1;i<=n;++i)
		ans=(ans+(long long)factorial*(mod-a[i]%mod)%mod)%mod;
	for(int i=n+1;i<=(n<<1);++i)
		ans=(ans+(long long)factorial*a[i]%mod)%mod;
	printf("%d",ans);
	return 0;
}
```
**核心实现思想**：先对数组排序，计算阶乘和逆元得到组合数，再根据元素大小计算答案，同时注意取模防止溢出。

### 最优关键思路或技巧
- **结论推导**：通过分析划分的性质，得出每种划分的值都为前 $n$ 大的数之和减去前 $n$ 小的数之和，简化了计算过程。
- **组合数计算**：使用快速幂求逆元来计算组合数，避免了直接计算阶乘带来的溢出问题。

### 拓展思路
同类型题目可能会改变数组的划分规则或代价的计算方式，但核心思路仍然是分析元素的贡献和组合数的计算。类似的算法套路包括通过分析特殊情况得出一般结论，以及使用数学方法简化计算。

### 推荐题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)
- [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)
- [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)

### 个人心得摘录与总结
- **白鲟**：纪念 CF 第一次打 Div.1，第一次 FST，以及第一次掉 Rating。需要注意的是 $a_i$ 的最大值大于模数，因此读入时应对其取模，否则减法操作将为负数，自己就是因为这个 FST 掉了。总结：在处理涉及取模的问题时，要注意数据范围和取模操作的时机，避免出现负数导致错误。
- **七色丶人偶使**：一个水题，但是考场上愣是想了一个小时，最后忘了加模数再取模导致我 FST。总结：在考试中要保持冷静，仔细检查代码，特别是涉及取模的操作，确保结果的正确性。 

---
处理用时：68.90秒