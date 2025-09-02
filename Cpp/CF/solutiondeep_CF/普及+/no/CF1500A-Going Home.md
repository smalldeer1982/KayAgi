# 题目信息

# Going Home

## 题目描述

It was the third month of remote learning, Nastya got sick of staying at dormitory, so she decided to return to her hometown. In order to make her trip more entertaining, one of Nastya's friend presented her an integer array $ a $ .

Several hours after starting her journey home Nastya remembered about the present. To entertain herself she decided to check, are there four different indices $ x, y, z, w $ such that $ a_x + a_y = a_z + a_w $ .

Her train has already arrived the destination, but she still hasn't found the answer. Can you help her unravel the mystery?

## 说明/提示

In the first example $ a_2 + a_3 = 1 + 5 = 2 + 4 = a_1 + a_6 $ . Note that there are other answer, for example, 2 3 4 6.

In the second example, we can't choose four indices. The answer 1 2 2 3 is wrong, because indices should be different, despite that $ a_1 + a_2 = 1 + 3 = 3 + 1 = a_2 + a_3 $

## 样例 #1

### 输入

```
6
2 1 5 2 7 4```

### 输出

```
YES
2 3 1 6```

## 样例 #2

### 输入

```
5
1 3 1 9 20```

### 输出

```
NO```

# AI分析结果

### 题目中文重写
# 回家

## 题目描述
远程学习的第三个月， Nastya 厌倦了待在宿舍，于是她决定回到家乡。为了让旅途更有趣， Nastya 的一个朋友送给她一个整数数组 $a$。

在回家的旅程开始几个小时后， Nastya 想起了这份礼物。为了自娱自乐，她决定检查是否存在四个不同的索引 $x, y, z, w$，使得 $a_x + a_y = a_z + a_w$。

她的火车已经到达目的地，但她仍然没有找到答案。你能帮她解开这个谜团吗？

## 说明/提示
在第一个样例中，$a_2 + a_3 = 1 + 5 = 2 + 4 = a_1 + a_6$。注意，还有其他答案，例如 2 3 4 6。
在第二个样例中，我们无法选择四个索引。答案 1 2 2 3 是错误的，因为索引应该是不同的，尽管 $a_1 + a_2 = 1 + 3 = 3 + 1 = a_2 + a_3$。

## 样例 #1
### 输入
```
6
2 1 5 2 7 4
```
### 输出
```
YES
2 3 1 6
```

## 样例 #2
### 输入
```
5
1 3 1 9 20
```
### 输出
```
NO
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举数组中两两元素的和，利用桶或类似的数据结构记录已经出现过的和及其对应的索引，当再次遇到相同的和且对应的索引满足互不相同的条件时，就找到了符合要求的四个索引。

- **思路对比**：大部分题解都是直接枚举所有数对，检查和是否重复；部分题解还对时间复杂度进行了理论分析，利用抽屉原理说明该算法的可行性。
- **算法要点**：使用桶（数组或结构体数组）来记录和及其对应的索引，通过两层循环枚举所有数对。
- **解决难点**：主要难点在于如何保证找到的四个索引互不相同，以及如何证明该算法在给定数据范围内不会超时。

### 所选题解
- **作者：TonyYin (赞：11)，4星**
    - **关键亮点**：思路清晰，对暴力算法的时间复杂度进行了详细的证明，代码简洁明了。
    - **个人心得**：提到这题在比赛时只有不到 2000 人 A 掉，且指出这是一道结论题。
- **作者：Blunt_Feeling (赞：9)，4星**
    - **关键亮点**：解释了为什么可以用数组代替 `map` 进行哈希，对数据范围和时间复杂度的分析较为详细。
    - **个人心得**：称这题很玄学，比赛时加了查找次数判断，赛后分析发现该判断不必要。
- **作者：tommymio (赞：3)，4星**
    - **关键亮点**：对暴力枚举做法的正确性进行了证明，时间复杂度分析简洁。
    - **个人心得**：提到比赛时用双指针做法失败。

### 重点代码
以下是 TonyYin 题解的核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10, MAXC = 2e6 + 5e5 + 10;
int n;
int x[MAXC << 1], y[MAXC << 1];
int a[MAXN], cnt[MAXC << 1];
bool have_ans;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(cnt[a[i] + a[j]]) {
                if(x[a[i] + a[j]] != i && y[a[i] + a[j]] != i 
                && x[a[i] + a[j]] != j && y[a[i] + a[j]] != j) {
                    cout << "YES" << endl << i << " " << j << " " << x[a[i] + a[j]] << " " << y[a[i] + a[j]] << endl;
                    return 0;
                }
            } else {
                cnt[a[i] + a[j]]++;
                x[a[i] + a[j]] = i; y[a[i] + a[j]] = j;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}
```
**核心实现思想**：通过两层循环枚举所有数对，用 `cnt` 数组记录和是否出现过，`x` 和 `y` 数组记录和对应的索引。当和已经出现过且索引互不相同，输出结果；否则记录该和及其索引。

### 扩展思路
同类型题或类似算法套路：
- 寻找数组中满足特定关系的元素组合，如 $a + b = c$ 等，可以采用类似的枚举和记录的方法。
- 处理数据范围较大但值域有限的问题时，可以考虑使用桶来优化算法。

### 推荐洛谷题目
1. P1102 A-B 数对：在数组中寻找满足 $A - B = C$ 的数对。
2. P1638 逛画展：寻找满足特定条件的连续区间。
3. P1996 约瑟夫问题：模拟一个出圈的过程，需要枚举和判断。 

---
处理用时：43.43秒