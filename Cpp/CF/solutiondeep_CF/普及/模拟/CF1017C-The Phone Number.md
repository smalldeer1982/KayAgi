# 题目信息

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4
```

### 输出

```
3 4 1 2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1
```

# AI分析结果

### 题目翻译
## 电话号码

### 题目描述
史密斯夫人试图联系她的丈夫约翰·史密斯，但她忘记了秘密电话号码！

史密斯夫人唯一记得的是，$n$ 的任何排列都可能是秘密电话号码。只有那些使秘密值最小的排列才可能是她丈夫的电话号码。

如果一个包含 $n$ 个整数的序列包含从 $1$ 到 $n$ 的所有整数且每个整数仅出现一次，则该序列称为一个排列。

电话号码的秘密值定义为最长上升子序列（LIS）的长度与最长下降子序列（LDS）的长度之和。

对于一个子序列 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$，其中 $1\leq i_1 < i_2 < \ldots < i_k\leq n$，如果 $a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k}$，则称该子序列为上升子序列；如果 $a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k}$，则称该子序列为下降子序列。上升/下降子序列如果在所有上升/下降子序列中长度最大，则称为最长上升/下降子序列。

例如，如果有一个排列 $[6, 4, 1, 7, 2, 3, 5]$，该排列的 LIS 为 $[1, 2, 3, 5]$，因此 LIS 的长度等于 $4$。LDS 可以是 $[6, 4, 1]$、$[6, 4, 2]$ 或 $[6, 4, 3]$，因此 LDS 的长度为 $3$。

注意，LIS 和 LDS 的长度可能不同。

请帮助史密斯夫人找到一个使 LIS 和 LDS 长度之和最小的排列。

### 说明/提示
在第一个样例中，可以构造排列 $[3, 4, 1, 2]$。LIS 为 $[3, 4]$（或 $[1, 2]$），因此 LIS 的长度等于 $2$。LDS 可以是 $[3, 1]$、$[4, 2]$、$[3, 2]$ 或 $[4, 1]$ 中的任意一个。LDS 的长度也等于 $2$。两者之和等于 $4$。注意，$[3, 4, 1, 2]$ 不是唯一有效的排列。

在第二个样例中，可以构造排列 $[2, 1]$。LIS 为 $[1]$（或 $[2]$），因此 LIS 的长度等于 $1$。LDS 为 $[2, 1]$，因此 LDS 的长度等于 $2$。两者之和等于 $3$。注意，排列 $[1, 2]$ 也是有效的。

### 样例 #1
#### 输入
```
4
```
#### 输出
```
3 4 1 2
```

### 样例 #2
#### 输入
```
2
```
#### 输出
```
2 1
```

### 综合分析与结论
这些题解的核心思路均为通过分块构造排列来使最长上升子序列（LIS）和最长下降子序列（LDS）长度之和最小。大部分题解先通过数学推导得出块长取 $\sqrt{n}$ 时能使 LIS + LDS 最小，然后按照块内升序、块外降序的方式构造排列。
- **思路对比**：部分题解通过模拟数据找规律得出结论，部分题解运用数学定理（如 dilworth 定理、基本不等式）进行推导。
- **算法要点**：确定块长为 $\sqrt{n}$，然后根据块长和总长度 $n$ 构造排列。
- **解决难点**：主要难点在于如何证明块长取 $\sqrt{n}$ 时 LIS + LDS 最小，以及如何根据块长构造出满足条件的排列。

### 所选题解
- **FxorG（5星）**
    - **关键亮点**：思路清晰，直接点明最优构造方式为分块，且块长取 $\sqrt{n}$，代码简洁易懂。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n,bl;

int main() {
    scanf("%d",&n);
    bl=sqrt(n);
    while(n>0) {
        for(int i=n-bl+1;i<=n;i++) {
            if(i>0) printf("%d ",i);
        }
        n-=bl;
    }
    return 0;
}
```
核心实现思想：先计算块长 $bl = \sqrt{n}$，然后从后往前依次输出每个块内的元素，每次输出完一个块后更新剩余元素数量 $n$。

- **沉石鱼惊旋（4星）**
    - **关键亮点**：思路简洁明了，先说明分块思路和块长选择的原因，再给出构造排列的代码。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    int m = sqrt(n);
    for (int i = 1; i <= (n + m - 1) / m; i++)
    {
        for (int j = n - i * m + 1; j <= n - (i - 1) * m; j++)
            if (j > 0)
                cout << j << " ";
    }
    cout << endl;
    return 0;
}
```
核心实现思想：计算块长 $m = \sqrt{n}$，通过两层循环输出排列，外层循环控制块的数量，内层循环输出每个块内的元素。

- **Scrutiny（4星）**
    - **关键亮点**：先证明了一个 $1\sim n$ 的排列的 LIS 和 LDS 长度之和不小于 $\lceil 2\sqrt{n}\rceil$，然后给出构造排列的方法。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,step;
int main(){
    cin>>n;
    len=sqrt(n);
    step=ceil(sqrt(n))+1;
    while(step){
        --step;
        for(int i=max(1,n-len+1);i<=n;++i){
            printf("%d ",i);
        }
        n-=len;
    }
    return 0;
}
```
核心实现思想：计算块长 $len = \sqrt{n}$ 和步数 $step$，通过循环依次输出每个块内的元素，每次输出完一个块后更新剩余元素数量 $n$。

### 最优关键思路与技巧
- **思维方式**：运用分块思想，将排列划分为多个块，通过控制块长和块的数量来优化 LIS 和 LDS 的长度之和。
- **数学推导**：利用基本不等式证明块长取 $\sqrt{n}$ 时 LIS + LDS 最小。

### 拓展思路
同类型题可能会改变排列的构造规则或子序列的定义，例如求最长不上升子序列和最长不下降子序列长度之和最小的排列。类似算法套路包括分块构造、数学推导优化等。

### 推荐题目
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：涉及最长不上升子序列和最长上升子序列的求解。
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：考察最长公共子序列的求解。
- [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)：需要将问题转化为最长上升子序列问题进行求解。

### 个人心得摘录与总结
- **agicy**：一开始手动模拟数据得出错误结论，后来使用计算机模拟大量数据才找到正确规律。总结：计算能力很重要，手动模拟数据可能会得出错误结论，应借助计算机进行更全面的模拟。

---
处理用时：40.98秒