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

• **综合分析与结论**：这几道题解的核心思路均是通过证明一些关键结论，确定最优解的形式，再通过预处理和枚举来求解。所有题解都指出最优解中\(c\)序列具有单调不降的性质，且存在某个位置\(i\)，使得\(c\)序列前半段取\(a\)序列的值，后半段取\(b\)序列的值。然后通过对\(n^2\)倍方差公式\(n \cdot \sum^{n}_{i=1}c_i^2 - (\sum^{n}_{i=1}c_i)^2\)的运用，结合前缀和、后缀和的预处理，以\(O(n)\)的时间复杂度求解。区别主要在于对关键结论的证明方式以及代码实现细节。

**最优关键思路或技巧**：通过数学推导和证明确定最优解的结构性质，将方差公式进行变形，利用前缀和、后缀和优化计算过程，从而高效求解问题。

**同类型题或类似算法套路**：此类题目通常结合数学性质与算法优化，先通过数学分析确定解的特征，再利用合适的数据结构或算法技巧优化实现。常见于一些涉及区间选择、最值求解且具有单调性等性质的题目。

**推荐题目**：
  - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过分析打水时间的先后顺序对总时间的影响，利用排序和贪心策略求解，与本题分析最优解结构的思路类似。
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：需要通过数学推导得出最优排列顺序，再进行计算，和本题确定最优解形式后优化求解的过程类似。
  - [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：结合二分查找和贪心策略，确定满足条件的最优分段方式，和本题通过分析性质确定最优解结构后再求解的思路类似。

**个人心得摘录与总结**：
  - **作者strcmp**：赛时通过猜测结论解题，赛后完善证明。心得为做题不能仅依赖猜测结论，要深入理解和证明，以确保对题目的真正掌握。

以下是评分较高的题解：
  - **作者：Kubic (5星)**
    - **关键亮点**：对三个关键结论的证明简洁清晰，代码实现直接明了，通过逐步推导结论确定最优解形式，利用简单的变量更新实现前缀和后缀的计算，时间复杂度最优。
    - **核心代码**：
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
    - **核心实现思想**：先初始化\(s1\)为\(a\)序列的和，\(s2\)为\(a\)序列平方和，计算初始答案。然后从后往前枚举分割点\(i\)，每次更新\(s1\)和\(s2\)，即加上\(b[i]\)与\(a[i]\)的差值和平方差，取每次计算结果的最大值作为答案。

  - **作者：David_Mercury (4星)**
    - **关键亮点**：对题目分析详细，从方差定义出发，清晰阐述了尽量让数据分散的思路，对公式变形过程完整展示，代码通过预处理前缀和、后缀和数组实现，逻辑清晰。
    - **核心代码**：
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
    for(int i=1; i<=n; i++)    scanf("%d", a+i);
    for(int i=1; i<=n; i++)    scanf("%d", b+i);
    for(int i=1; i<=n; i++)    qz[i] = qz[i-1]+a[i];
    for(int i=n; i>=1; i--)    hz[i] = hz[i+1]+b[i];
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
    - **核心实现思想**：先预处理\(a\)序列的前缀和\(qz\)、前缀平方和\(qz2\)，\(b\)序列的后缀和\(hz\)、后缀平方和\(hz2\)。然后枚举分割点\(i\)，根据公式计算并更新最大方差值。

  - **作者：strcmp (4星)**
    - **关键亮点**：对各个引理的证明严谨详细，从理论上深入分析了问题，代码实现简洁，通过预处理前缀和后缀和，以高效的方式求解。
    - **核心代码**：
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
    - **核心实现思想**：与Kubic的代码类似，先初始化\(s1\)和\(s2\)为\(a\)序列的和与平方和，计算初始答案。再从后往前枚举分割点\(i\)，更新\(s1\)和\(s2\)，取每次计算结果的最大值作为答案。 

---
处理用时：90.75秒