# 题目信息

# Almost Identity Permutations

## 题目描述

A permutation $ p $ of size $ n $ is an array such that every integer from $ 1 $ to $ n $ occurs exactly once in this array.

Let's call a permutation an almost identity permutation iff there exist at least $ n-k $ indices $ i $ ( $ 1<=i<=n $ ) such that $ p_{i}=i $ .

Your task is to count the number of almost identity permutations for given numbers $ n $ and $ k $ .

## 样例 #1

### 输入

```
4 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5 3
```

### 输出

```
31
```

## 样例 #4

### 输入

```
5 4
```

### 输出

```
76
```

# AI分析结果

### 题目内容
# 近似恒等排列

## 题目描述
一个大小为 $n$ 的排列 $p$ 是一个数组，使得从 $1$ 到 $n$ 的每个整数在该数组中恰好出现一次。

如果存在至少 $n - k$ 个索引 $i$（$1 \leq i \leq n$）使得 $p_i = i$，我们就称这个排列为近似恒等排列。

你的任务是计算给定数字 $n$ 和 $k$ 的近似恒等排列的数量。

## 样例 #1
### 输入
```
4 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4 2
```
### 输出
```
7
```

## 样例 #3
### 输入
```
5 3
```
### 输出
```
31
```

## 样例 #4
### 输入
```
5 4
```
### 输出
```
76
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是基于组合数学与错排原理。由于 $k$ 的值较小（$k \leq 4$），题解主要围绕对 $k$ 进行分类讨论，通过计算组合数与错排数来求解近似恒等排列的数量。不同题解在实现细节上略有差异，如组合数和错排数的计算方式、代码结构等。

### 所选的题解
- **作者：Karry5307 (5星)**
    - **关键亮点**：思路清晰，将问题转化为至多 $k$ 个位置满足 $\pi_i\neq i$，利用二项式系数算出位置方案数乘上错排，代码简洁高效，通过预处理错排数和组合数，以线性时间复杂度解决问题。
    - **重点代码核心实现思想**：通过预处理错排数数组 `d` 和利用二项式系数计算组合数，循环累加不同错排个数的情况得到结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
ll n,kk,binom,res;
ll d[10]={1,0,1,2,9};
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),kk=read(),binom=1;
	for(register int i=0;i<=kk;i++)
	{
		res+=d[i]*binom,binom=binom*(n-i)/(i+1);
	}
	printf("%lld\n",res);
}
```
- **作者：xiaohuang (4星)**
    - **关键亮点**：对每种 $k$ 值的情况分析详细，通过组合数公式计算不同错排个数下的排列数，逻辑清晰，代码可读性强。
    - **重点代码核心实现思想**：定义函数 `Combination` 计算组合数，根据 $k$ 的不同取值，分别计算并输出结果。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
int n, k;
inline LL Combination(int x, int y) {//求组合数
    LL ret = 1;
    for (int i = x; i >= x - y + 1; i--)
        ret *= i;
    for (int i = 1; i <= y; i++)
        ret /= i;
    return ret;
}
int main() {
    scanf("%d%d", &n, &k);
    if (k == 1) printf("1\n"); else
    if (k == 2) printf("%lld\n", Combination(n, 2) + 1); else
    if (k == 3) printf("%lld\n", Combination(n, 2) + Combination(n, 3) * 2 + 1); else
    if (k == 4) printf("%lld\n", Combination(n, 2) + Combination(n, 3) * 2 + Combination(n, 4) * 9 + 1);//分类讨论
    return 0;
}
```
- **作者：Coros_Trusds (4星)**
    - **关键亮点**：明确指出问题本质是错排问题，利用错排公式递推出错排数，结合组合数计算答案，代码结构完整，注释详细。
    - **重点代码核心实现思想**：通过 `init` 函数预处理组合数，利用错排公式递推错排数，循环累加不同错排个数的情况并加上 $k = 1$ 时的情况得到结果。
```cpp
#define int long long

const int ma=1005;

int dp[ma];

int C[ma][ma];

int n,k;

inline void init()
{
	C[0][0]=1;
	
	for(register int i=1;i<=1e3;i++)
	{
		C[i][0]=1;
		 
		for(register int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
}

#undef int

int main(void)
{
	#define int long long
	
	n=read(),k=read();
	
	init();
	
	if(k==1)
	{
		printf("1\n");
	}
	
	else
	{
		int ans(0);
		
		dp[2]=1;
		
		for(register int i=3;i<=n;i++)
		{
			dp[i]=(i-1)*(dp[i-1]+dp[i-2]);
		}
		
		for(register int i=2;i<=k;i++)
		{
			ans+=C[n][i]*dp[i];
		}
		
		printf("%lld\n",ans+1);
	}
	
	return 0;
}
```

### 最优关键思路或技巧
1. **利用错排原理**：将问题转化为错排问题，通过错排公式 $d_i=(i - 1)\times(d_{i - 1}+d_{i - 2})$ 递推错排数，结合组合数计算满足条件的排列数。
2. **分类讨论与组合数计算**：由于 $k$ 值较小，对 $k$ 进行分类讨论，分别计算每种情况下的组合数，再根据乘法原理得到每种情况的排列数，最后累加得到结果。

### 拓展
此类题目属于组合数学中的错排相关问题，类似套路是遇到有特定位置限制的排列问题时，考虑能否转化为错排问题，利用错排公式和组合数计算。同类型题通常会改变限制条件或数据范围，例如改变错排个数的限制、增大 $n$ 和 $k$ 的范围等。

### 相似知识点洛谷题目
1. **P1595 信封问题**：经典错排问题，与本题中错排原理的应用相似。
2. **P3197 [HNOI2008]越狱**：涉及组合数学中利用总数减去不满足条件的数量来求解满足条件的方案数。
3. **P2606 [ZJOI2010]排列计数**：同样是关于排列组合的问题，需要结合组合数和一些特定条件来计算排列的数量。 

---
处理用时：55.72秒