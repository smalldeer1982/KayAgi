# 题目信息

# Guess the Permutation

## 题目描述

Bob has a permutation of integers from $ 1 $ to $ n $ . Denote this permutation as $ p $ . The $ i $ -th element of $ p $ will be denoted as $ p_{i} $ . For all pairs of distinct integers $ i,j $ between $ 1 $ and $ n $ , he wrote the number $ a_{i,j}=min(p_{i},p_{j}) $ . He writes $ a_{i,i}=0 $ for all integer $ i $ from $ 1 $ to $ n $ .

Bob gave you all the values of $ a_{i,j} $ that he wrote down. Your job is to reconstruct any permutation that could have generated these values. The input will be formed so that it is guaranteed that there is at least one solution that is consistent with the information given.

## 说明/提示

In the first case, the answer can be $ {1,2} $ or $ {2,1} $ .

In the second case, another possible answer is $ {2,4,5,1,3} $ .

## 样例 #1

### 输入

```
2
0 1
1 0
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
5
0 2 2 1 2
2 0 4 1 3
2 4 0 1 3
1 1 1 0 1
2 3 3 1 0
```

### 输出

```
2 5 4 1 3
```

# AI分析结果

### 题目翻译
# 猜测排列

## 题目描述
Bob 有一个从 1 到 n 的整数排列，将这个排列记为 p。p 的第 i 个元素记为 $p_i$。对于 1 到 n 之间所有不同的整数对 i, j，他写下了数字 $a_{i,j} = min(p_i, p_j)$。对于所有从 1 到 n 的整数 i，他令 $a_{i,i} = 0$。

Bob 把他写下的所有 $a_{i,j}$ 的值都给了你。你的任务是重构出任何一个可能生成这些值的排列。输入会保证至少存在一个与给定信息一致的解。

## 说明/提示
在第一个样例中，答案可以是 {1, 2} 或 {2, 1}。

在第二个样例中，另一个可能的答案是 {2, 4, 5, 1, 3}。

## 样例 #1
### 输入
```
2
0 1
1 0
```
### 输出
```
2 1
```

## 样例 #2
### 输入
```
5
0 2 2 1 2
2 0 4 1 3
2 4 0 1 3
1 1 1 0 1
2 3 3 1 0
```
### 输出
```
2 5 4 1 3
```

### 算法分类
构造

### 综合分析与结论
- **思路对比**：
    - **lflby**：对于每个 $p_i$，搜索 $f_{i,j}$ 和 $f_{j,i}$ 取最大值，若该值已被选过则往后找第一个未被选的数。
    - **Halberd_Cease**：根据 $f_{i,j}=\min(p_i,p_j)$ 推出 $\max^n_{j=1}(f_{i,j})$ 是第 $i$ 个数的值（最大数特殊处理），排序后确定排列。
    - **yangzd**：先找到全是 1 的行确定 1 的位置，然后把矩阵中所有 1 变成 2，继续找全是 2 的行确定 2 的位置，以此类推。
    - **Saber_Master**：第 $i$ 行出现次数大于 1 的数就是 $p_i$，预处理后补上剩余空位。
- **算法要点**：
    - **lflby**：通过双重循环找最大值，用布尔数组标记已选数字。
    - **Halberd_Cease**：定义结构体存储信息，通过两次排序确定排列。
    - **yangzd**：通过多层循环模拟找数和更新矩阵的过程。
    - **Saber_Master**：用数组记录每个数的出现次数，找到出现次数大于 1 的数。
- **解决难点**：
    - 都需要处理数字重复选择的问题，不同题解采用不同方法避免重复。
    - 对于最大数的处理，不同题解有不同的思路。

### 题解评分
- **lflby**：4 星。思路清晰，代码简洁易懂，直接通过找最大值和处理重复来确定排列。
- **Halberd_Cease**：3 星。思路有一定的逻辑性，但代码中使用结构体和两次排序，相对复杂。
- **yangzd**：3 星。模拟过程较为直观，但多层循环嵌套，代码复杂度较高。
- **Saber_Master**：3 星。思路简单，但代码中使用了自定义的输入输出函数，增加了理解成本。

### 所选题解
- **lflby**：4 星。关键亮点在于思路简洁直接，通过找最大值和处理重复来确定排列，代码实现简单易懂。

### 重点代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[55][55];
bool b[55];
int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin>>a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int s = -2e9;
        for (int j = 1; j <= n; j++)
        {
            s = max(s,a[i][j]);
        }
        for (int j = 1; j <= n; j++)
        {
            s = max(s,a[j][i]);
        }
        while (b[s]) s++;
        cout<<s<<" ";
        b[s]=true; 
    }
    return 0;
 } 
```
**核心实现思想**：先读取矩阵，然后对于每一行，找到该行和该列中的最大值，若该值已被选过则往后找第一个未被选的数，将其作为当前位置的数并标记为已选。

### 最优关键思路或技巧
- 利用 $f_{i,j}=\min(p_i,p_j)$ 的性质，通过找最大值来确定排列中的数。
- 使用布尔数组标记已选数字，避免重复选择。

### 拓展思路
同类型题可能会有不同的矩阵生成规则，解题关键在于分析矩阵元素与排列元素之间的关系，通过构造的方法找到符合条件的排列。类似算法套路包括根据给定的条件逐步确定元素的位置或值。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察对问题的模拟和处理能力。
- [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)：需要对数据进行统计和处理。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过分析条件来确定最终状态。

### 个人心得
题解中未包含个人心得。

---
处理用时：30.91秒