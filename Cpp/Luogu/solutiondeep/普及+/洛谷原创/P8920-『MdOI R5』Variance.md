# 题目信息

# 『MdOI R5』Variance

## 题目背景

Subtask 1~5 为原数据，Subtask 6 为 hack 数据。

## 题目描述

给定两个长度为 $n$ 的整数序列 $a,b$，满足：
- $\forall i\in [1,n),a_i\le a_{i+1},b_i\le b_{i+1}$。

- $\forall i\in [1,n],a_i\le b_i$。

有一个长度为 $n$ 的实数序列 $c$，满足 $c_i\in [a_i,b_i]$，求 $c$ 的方差的最大值。

你只需要输出答案乘上 $n^2$ 之后的结果。容易证明这是一个整数。

### 提示

一个长度为 $n$ 的序列 $a$ 的方差为：$\dfrac{1}{n}\sum\limits_{i=1}^n (a_i-\overline{a})^2$。其中 $\overline{a}=\dfrac{1}{n}\sum\limits_{i=1}^n a_i$。

本题的计算过程中可能会涉及到超过 `long long` 范围的数，此时可能需要用到 `__int128` 进行处理。

我们提供了以下代码，它可以用于输出一个 `__int128` 类型的数：

``` cpp
void print(__int128 x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x<10)
	{
		putchar(x+48);
		return;
	}
	print(x/10);
	putchar(x%10+48);
}
```

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le a_i,b_i\le 10^9$。

$\operatorname{Subtask} 1(10\%)$：$n\le 2\times 10^3$，$a_i=b_i\le 10^5$。

$\operatorname{Subtask} 2(20\%)$：$n\le 10$，$a_i,b_i\le 5$。

$\operatorname{Subtask} 3(20\%)$：$n\le 2\times 10^3$，$a_i,b_i\le 10^5$。

$\operatorname{Subtask} 4(20\%)$：$n\le 10^5$，$a_i,b_i\le 2\times 10^3$。

$\operatorname{Subtask} 5(30\%)$：无特殊限制。

#### 样例说明 1

$c$ 只可能为 $(1,10)$。

#### 样例说明 2

一种最优的 $c$ 为 $(1,2,5)$。

## 样例 #1

### 输入

```
2
1 10
1 10```

### 输出

```
81```

## 样例 #2

### 输入

```
3
1 2 3
3 4 5```

### 输出

```
26```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过分析方差的性质，得出最优的序列 \( c \) 必然存在一种形式：前半段取 \( a \) 数组，后半段取 \( b \) 数组，然后通过枚举分割点来计算方差的最大值。

1. **思路方面**：多数题解先证明了最优解的一些性质，如存在单调不降的最优解、存在一个分割点 \( i \) 使得 \( c \) 前半段为 \( a \) 后半段为 \( b \) 等，然后基于这些性质进行求解。
2. **算法要点**：利用前缀和、后缀和预处理数据，结合方差公式的变形 \( S^2*n^2 = n*(\sum_{i=1}^n c_i^2)-(\sum_{i=1}^n c_i)^2 \)，在 \( O(n) \) 时间复杂度内枚举分割点计算方差最大值。
3. **解决难点**：难点在于证明最优解的性质，以及对方差公式的推导变形，以便快速计算方差。

### 所选的题解
1. **作者：Kubic (5星)**
    - **关键亮点**：思路清晰，先给出三个重要结论并进行了严谨的证明，通过结论直接得出枚举分割点的做法，代码简洁明了。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000005
#define lll __int128
int n,a[N],b[N];lll s1,s2,ans;
void print(lll x)
{
    if(x<10) {putchar(x+48);return;}
    print(x/10);putchar(x%10+48);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) scanf("%d",&b[i]);
    for(int i=1;i<=n;++i) s1+=a[i],s2+=1ll*a[i]*a[i];
    ans=s2*n-s1*s1;
    for(int i=n;i;--i)
    {
        s1+=b[i]-a[i];s2+=1ll*b[i]*b[i]-1ll*a[i]*a[i];
        ans=max(ans,s2*n-s1*s1);
    }print(ans);return 0;
}
```
    - **核心实现思想**：先计算初始情况下（全取 \( a \) 数组）的和 \( s1 \) 与平方和 \( s2 \)，并得到此时的方差值 \( ans \)。然后从后往前枚举分割点 \( i \)，每次更新和与平方和，并计算新的方差值与当前 \( ans \) 取最大值。

2. **作者：David_Mercury (4星)**
    - **关键亮点**：先阐述题目大意与方差定义，结合题目条件直观得出前半段选 \( a \) 后半段选 \( b \) 的思路，详细推导方差公式，代码实现清晰，注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
__int128 ans, qz[MAXN], hz[MAXN], qz2[MAXN], hz2[MAXN];
int n, a[MAXN], b[MAXN];
void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x < 10){
        putchar(x+48);
        return;
    }
    print(x/10);
    putchar(x%10+48);
}
int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    for(int i=1; i<=n; i++) scanf("%d", b+i);
    for(int i=1; i<=n; i++) qz[i] = qz[i-1]+a[i];
    for(int i=n; i>=1; i--) hz[i] = hz[i+1]+b[i];
    for(int i=1; i<=n; i++){
        qz2[i] = a[i];
        qz2[i] = qz2[i]*qz2[i]+qz2[i-1];
    }
    for(int i=n; i>=1; i--){
        hz2[i] = b[i];
        hz2[i] = hz2[i]*hz2[i]+hz2[i+1];
    }
    for(int i=0; i<=n; i++)
        ans = max(ans, (qz2[i]+hz2[i+1])*n-(qz[i]+hz[i+1])*(qz[i]+hz[i+1]));
    print(ans);
    return 0;
}
```
    - **核心实现思想**：预处理 \( a \) 的前缀和 \( qz \)、平方前缀和 \( qz2 \)，\( b \) 的后缀和 \( hz \)、平方后缀和 \( hz2 \)。枚举分割点 \( i \)，通过公式计算不同分割情况下的方差值并取最大值。

3. **作者：strcmp (4星)**
    - **关键亮点**：对每个引理都进行了较为详细的证明，从理论上严谨地推出最优解的形式，代码实现简洁，还提及了可能存在的三分做法。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
typedef __int128 ll;
const int maxn = 1e6 + 10;
__int128 a[maxn], b[maxn], s1, s2, ans = 0; int n;
inline void read(ll &x){
    x=0;char e=0;
    while (!isdigit(e))e=getchar();
    while (isdigit(e)) x=x*10+(e^48),e=getchar();
}
void print(__int128 x){
    if(x < 10){
        putchar(x + 48);
        return;
    }
    print(x / 10);
    putchar(x % 10 + 48);
}
int main() { scanf("%d", &n);
    for (re int i = 1; i <= n; i++)read(a[i]);
    for (re int i = 1; i <= n; i++)read(b[i]);
    for (re int i = 1; i <= n; i++)s1 += a[i], s2 += a[i] * a[i];
    ans = s2 * n - s1 * s1;
    for (re int i = n; i >= 1; i--){
        s1 += b[i] - a[i], s2 += b[i] * b[i] - a[i] * a[i];
        ans = max(ans, s2 * n - s1 * s1);
    }
    print(ans);
    return 0;
}
```
    - **核心实现思想**：与 Kubic 的代码类似，先计算全取 \( a \) 数组时的和与平方和，得到初始方差值。然后从后往前枚举分割点，更新和与平方和，计算新方差值并与当前最大值比较。

### 最优关键思路或技巧
1. **数学推导**：对方差公式进行推导变形，得到 \( S^2*n^2 = n*(\sum_{i=1}^n c_i^2)-(\sum_{i=1}^n c_i)^2 \)，使得计算方差时只需维护序列的和与平方和，降低时间复杂度。
2. **性质证明**：通过反证法等方式证明最优解的性质，如存在单调不降的最优解，存在一个分割点使得 \( c \) 由 \( a \) 的前半段和 \( b \) 的后半段组成，从而简化问题求解。

### 可拓展之处
同类型题通常围绕在给定限制条件下求某种统计量（如方差、均值等）的最值。类似算法套路是先分析目标统计量的性质，结合给定条件找出最优解的可能形式，再通过枚举、贪心、动态规划等方法求解。

### 相似知识点洛谷题目
1. **P1303 计算系数**：涉及多项式展开与组合数学知识，与本题类似在于需要对数学公式进行推导和运用。
2. **P2181 对角线**：通过找规律和数学推导解决问题，和本题一样需要挖掘问题背后的数学性质。
3. **P3951 小凯的疑惑**：利用数论知识解决问题，本题是利用方差性质，都需要对相关领域知识进行分析和运用。 

---
处理用时：74.23秒