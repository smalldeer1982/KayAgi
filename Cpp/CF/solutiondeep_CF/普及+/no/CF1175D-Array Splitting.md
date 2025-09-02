# 题目信息

# Array Splitting

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ and an integer $ k $ .

You are asked to divide this array into $ k $ non-empty consecutive subarrays. Every element in the array should be included in exactly one subarray. Let $ f(i) $ be the index of subarray the $ i $ -th element belongs to. Subarrays are numbered from left to right and from $ 1 $ to $ k $ .

Let the cost of division be equal to $ \sum\limits_{i=1}^{n} (a_i \cdot f(i)) $ . For example, if $ a = [1, -2, -3, 4, -5, 6, -7] $ and we divide it into $ 3 $ subbarays in the following way: $ [1, -2, -3], [4, -5], [6, -7] $ , then the cost of division is equal to $ 1 \cdot 1 - 2 \cdot 1 - 3 \cdot 1 + 4 \cdot 2 - 5 \cdot 2 + 6 \cdot 3 - 7 \cdot 3 = -9 $ .

Calculate the maximum cost you can obtain by dividing the array $ a $ into $ k $ non-empty consecutive subarrays.

## 样例 #1

### 输入

```
5 2
-1 -2 5 -4 8
```

### 输出

```
15
```

## 样例 #2

### 输入

```
7 6
-3 0 -1 -2 -2 -4 -1
```

### 输出

```
-45
```

## 样例 #3

### 输入

```
4 1
3 -1 6 0
```

### 输出

```
8
```

# AI分析结果

### 题目翻译
## 数组分割

### 题目描述
给定一个数组 $ a_1, a_2, \dots, a_n $ 和一个整数 $ k $。

要求将这个数组划分为 $ k $ 个非空的连续子数组，数组中的每个元素都必须恰好包含在一个子数组中。设 $ f(i) $ 为第 $ i $ 个元素所属子数组的索引，子数组从左到右编号，编号范围是从 $ 1 $ 到 $ k $。

划分的代价定义为 $ \sum\limits_{i=1}^{n} (a_i \cdot f(i)) $。例如，如果 $ a = [1, -2, -3, 4, -5, 6, -7] $，并且按如下方式将其划分为 $ 3 $ 个子数组：$ [1, -2, -3], [4, -5], [6, -7] $，那么划分的代价为 $ 1 \cdot 1 - 2 \cdot 1 - 3 \cdot 1 + 4 \cdot 2 - 5 \cdot 2 + 6 \cdot 3 - 7 \cdot 3 = -9 $。

计算将数组 $ a $ 划分为 $ k $ 个非空连续子数组所能获得的最大代价。

### 样例 #1
#### 输入
```
5 2
-1 -2 5 -4 8
```
#### 输出
```
15
```

### 样例 #2
#### 输入
```
7 6
-3 0 -1 -2 -2 -4 -1
```
#### 输出
```
-45
```

### 样例 #3
#### 输入
```
4 1
3 -1 6 0
```
#### 输出
```
8
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过数学推导简化问题，然后利用贪心策略来求解最大代价。大部分题解先计算前缀和或后缀和，再根据划分代价的公式进行化简，最后通过排序选取合适的和来得到最大代价。
- **思路对比**：部分题解从划分代价的公式出发进行化简，如将其转化为与前缀和或后缀和相关的式子；有的题解则通过观察区间移动的规律来找到解题思路。
- **算法要点**：主要是计算前缀和或后缀和，然后对其进行排序，选取最小的 $k - 1$ 个和（或最大的 $k - 1$ 个后缀和）。
- **解决难点**：关键在于如何将划分代价的公式化简，找到与前缀和或后缀和的关系，从而将问题转化为排序和贪心选择的问题。

### 所选题解
- **米奇（4星）**
    - **关键亮点**：思路清晰，通过观察区间移动的规律，将答案转化为 $k$ 段后缀区间的和，代码实现简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,k,ans,a[N],b[N];
multiset<int,greater<int> >s;
multiset<int,greater<int> >::iterator it;
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);	
    for(int i=n;i;i--)b[i]=b[i+1]+a[i];
    b[1]+=1e15;
    sort(b+1,b+n+1);
    for(int i=n;i>=n-k+1;i--)ans+=b[i];
    int x=1e15;
    printf("%lld",ans-x);
    return 0;
}
```
    - **核心实现思想**：先计算后缀和数组 `b`，为了保证区间 $[1,n]$ 一定被选中，给 `b[1]` 加上一个很大的数，然后对后缀和数组排序，选取最大的 $k$ 个和，最后减去加上的那个很大的数得到最终答案。

- **Mr_Wu（4星）**
    - **关键亮点**：详细推导了划分代价的公式，将问题转化为求最小的 $k - 1$ 个前缀和，思路严谨，代码规范。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

inline ll read()
{
    char c = getchar();
    ll ret = 0, t = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') t = -1, c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret * t;
}

#define MAXN 300005

int N, K;
ll a[MAXN], s[MAXN], ans;

int main()
{
    N = read(), K = read(); int i;
    for (i = 1; i <= N; ++i) s[i] = s[i - 1] + read();
    std::sort(s + 1, s + N);
    for (i = 1; i < K; ++i) ans -= s[i];
    ans += K * s[N];
    printf("%I64d", ans);
    return 0;
}
```
    - **核心实现思想**：先计算前缀和数组 `s`，对前缀和数组排序，选取最小的 $k - 1$ 个前缀和并从最终答案中减去，再加上 $k$ 倍的整个数组的和（即 $k * s[N]$）得到最终答案。

- **StephenYoung（4星）**
    - **关键亮点**：同样对划分代价的公式进行化简，思路简洁明了，代码实现简单。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=300050;
ll n,k,a[maxn],s[maxn],ans=-10000000000,tot;

int main()
{
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        s[i]=s[i-1]+a[i];
    }
    sort(s+1,s+n);
    for(ll i=1;i<k;i++)
    {
        tot+=s[i];
    }
    printf("%lld",s[n]*k-tot);
    return 0;
}
```
    - **核心实现思想**：计算前缀和数组 `s`，对前缀和数组排序，选取最小的 $k - 1$ 个前缀和累加到 `tot` 中，最终答案为 $k$ 倍的整个数组的和减去 `tot`。

### 关键思路或技巧
- 通过数学推导将划分代价的公式化简，转化为与前缀和或后缀和相关的式子。
- 利用排序和贪心策略，选取最小的 $k - 1$ 个前缀和或最大的 $k - 1$ 个后缀和来得到最大代价。

### 拓展思路
同类型题目可能会有不同的数组操作和代价计算方式，但核心思路可能类似，都是通过数学推导简化问题，再利用贪心策略求解。例如，可能会改变子数组的划分条件，或者改变代价的计算方式，但都可以尝试从公式化简和贪心选择的角度去思考。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P2240 【深基12.例1】部分背包问题

### 个人心得
- **米奇**：比赛时一开始以为是dp题，后来发现不对，通过观察题目的特征找到了解题思路，提醒我们遇到问题不能局限于一种思路，要多观察题目特点。
- **gorokokoro**：现场没有想到贪心的办法，通过打表发现 $f$ 满足函数凸性，使用 $\text{wqs}$ 二分解决，说明在没有思路时可以通过打表找规律，尝试不同的算法。 

---
处理用时：57.32秒