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
史密斯夫人试图联系她的丈夫约翰·史密斯，但她忘记了那个秘密电话号码！

史密斯夫人唯一记得的是，$n$ 的任何排列都可能是秘密电话号码。只有那些使秘密值最小的排列才可能是她丈夫的电话号码。

如果一个包含 $n$ 个整数的序列包含从 $1$ 到 $n$ 的所有整数，且每个整数仅出现一次，那么这个序列就被称为一个排列。

电话号码的秘密值被定义为最长上升子序列（LIS）的长度与最长下降子序列（LDS）的长度之和。

一个子序列 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$（其中 $1\leq i_1 < i_2 < \ldots < i_k\leq n$），如果满足 $a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k}$，则称其为上升子序列；如果满足 $a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k}$，则称其为下降子序列。上升/下降子序列中长度最大的被称为最长上升/下降子序列。

例如，对于排列 $[6, 4, 1, 7, 2, 3, 5]$，其 LIS 为 $[1, 2, 3, 5]$，所以 LIS 的长度为 $4$；LDS 可以是 $[6, 4, 1]$、$[6, 4, 2]$ 或 $[6, 4, 3]$，所以 LDS 的长度为 $3$。

注意，LIS 和 LDS 的长度可能不同。

请帮助史密斯夫人找到一个能使 LIS 和 LDS 长度之和最小的排列。

### 说明/提示
在第一个样例中，可以构造排列 $[3, 4, 1, 2]$。LIS 为 $[3, 4]$（或 $[1, 2]$），所以 LIS 的长度为 $2$；LDS 可以是 $[3, 1]$、$[4, 2]$、$[3, 2]$ 或 $[4, 1]$，LDS 的长度也为 $2$，它们的和为 $4$。注意，$[3, 4, 1, 2]$ 不是唯一有效的排列。

在第二个样例中，可以构造排列 $[2, 1]$。LIS 为 $[1]$（或 $[2]$），所以 LIS 的长度为 $1$；LDS 为 $[2, 1]$，所以 LDS 的长度为 $2$，它们的和为 $3$。注意，排列 $[1, 2]$ 也是有效的。

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
这些题解的核心思路均为分块构造排列，使最长上升子序列（LIS）和最长下降子序列（LDS）长度之和最小。多数题解通过数学推导得出块长取 $\sqrt{n}$ 时最优，再依据此构造排列。
- **思路对比**：部分题解借助基本不等式推导最优块长，部分通过模拟数据找规律，还有的运用 Dilworth 定理证明。
- **算法要点**：确定最优块长后，按块内升序、块外降序的规则构造排列。
- **解决难点**：关键在于证明块长为 $\sqrt{n}$ 时 LIS + LDS 最小，以及如何依据此块长构造出符合要求的排列。

### 所选题解
- **FxorG（5星）**：
    - **关键亮点**：思路清晰，通过简单数学分析得出最优块长，代码简洁易懂。
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
核心实现思想：先计算出块长为 $\sqrt{n}$，然后从后往前按块输出，每个块内元素升序排列。

- **Scrutiny（4星）**：
    - **关键亮点**：给出了不同于其他题解的证明方法，逻辑严谨。
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
核心实现思想：先证明 LIS 和 LDS 长度之和不小于 $\lceil 2\sqrt{n}\rceil$，然后确定 LIS 长度为 $\lfloor\sqrt{n}\rfloor$，LDS 长度为 $\lceil\dfrac{n}{\sqrt{n}}\rceil$，按此构造排列。

- **yijan（4星）**：
    - **关键亮点**：运用定理进行推导，详细解释了构造排列的原理。
    - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,block;
int main(void){
    int n,q;cin >> n;
    block = sqrt(n);
    for(q=1;n-block*q >= 0; ++q)
        for(int i=1;i<=block;++i)
            printf("%d ",n-block*q+i);
    for(int i=1;i<=n-block*(q-1);++i)
        printf("%d ",i);
}
```
核心实现思想：根据基本不等式得出当块长为 $\sqrt{n}$ 时 LIS + LDS 最小，然后按此构造排列。

### 最优关键思路或技巧
- **数学推导**：利用基本不等式证明块长为 $\sqrt{n}$ 时 LIS + LDS 最小。
- **分块构造**：按块内升序、块外降序的规则构造排列，简化问题求解。

### 可拓展之处
同类型题目可能会改变排列的条件或子序列的定义，例如求最长不上升子序列和最长不下降子序列长度之和最小的排列。解题套路依然是通过数学分析确定最优参数，再进行构造。

### 推荐题目
- [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)：涉及最长上升子序列和最长不上升子序列的求解。
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：求解最长公共子序列，与最长上升子序列有一定关联。
- [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)：可转化为最长上升子序列问题求解。

### 个人心得摘录与总结
- **agicy**：最初手动模拟数据得出错误结论，后借助计算机模拟大量数据才找到正确规律。总结为手动模拟数据可能不全面，利用计算机辅助模拟能提高结论的准确性。 

---
处理用时：34.98秒