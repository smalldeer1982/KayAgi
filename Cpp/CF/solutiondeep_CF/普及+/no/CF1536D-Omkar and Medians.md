# 题目信息

# Omkar and Medians

## 题目描述

Uh oh! Ray lost his array yet again! However, Omkar might be able to help because he thinks he has found the OmkArray of Ray's array. The OmkArray of an array $ a $ with elements $ a_1, a_2, \ldots, a_{2k-1} $ , is the array $ b $ with elements $ b_1, b_2, \ldots, b_{k} $ such that $ b_i $ is equal to the median of $ a_1, a_2, \ldots, a_{2i-1} $ for all $ i $ . Omkar has found an array $ b $ of size $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ -10^9 \leq b_i \leq 10^9 $ ). Given this array $ b $ , Ray wants to test Omkar's claim and see if $ b $ actually is an OmkArray of some array $ a $ . Can you help Ray?

The median of a set of numbers $ a_1, a_2, \ldots, a_{2i-1} $ is the number $ c_{i} $ where $ c_{1}, c_{2}, \ldots, c_{2i-1} $ represents $ a_1, a_2, \ldots, a_{2i-1} $ sorted in nondecreasing order.

## 说明/提示

In the second case of the first sample, the array $ [4] $ will generate an OmkArray of $ [4] $ , as the median of the first element is $ 4 $ .

In the fourth case of the first sample, the array $ [3, 2, 5] $ will generate an OmkArray of $ [3, 3] $ , as the median of $ 3 $ is $ 3 $ and the median of $ 2, 3, 5 $ is $ 3 $ .

In the fifth case of the first sample, the array $ [2, 1, 0, 3, 4, 4, 3] $ will generate an OmkArray of $ [2, 1, 2, 3] $ as

- the median of $ 2 $ is $ 2 $
- the median of $ 0, 1, 2 $ is $ 1 $
- the median of $ 0, 1, 2, 3, 4 $ is $ 2 $
- and the median of $ 0, 1, 2, 3, 3, 4, 4 $ is $ 3 $ .

In the second case of the second sample, the array $ [1, 0, 4, 3, 5, -2, -2, -2, -4, -3, -4, -1, 5] $ will generate an OmkArray of $ [1, 1, 3, 1, 0, -2, -1] $ , as

- the median of $ 1 $ is $ 1 $
- the median of $ 0, 1, 4 $ is $ 1 $
- the median of $ 0, 1, 3, 4, 5 $ is $ 3 $
- the median of $ -2, -2, 0, 1, 3, 4, 5 $ is $ 1 $
- the median of $ -4, -2, -2, -2, 0, 1, 3, 4, 5 $ is $ 0 $
- the median of $ -4, -4, -3, -2, -2, -2, 0, 1, 3, 4, 5 $ is $ -2 $
- and the median of $ -4, -4, -3, -2, -2, -2, -1, 0, 1, 3, 4, 5, 5 $ is $ -1 $

For all cases where the answer is NO, it can be proven that it is impossible to find an array $ a $ such that $ b $ is the OmkArray of $ a $ .

## 样例 #1

### 输入

```
5
4
6 2 1 3
1
4
5
4 -8 5 6 -7
2
3 3
4
2 1 2 3```

### 输出

```
NO
YES
NO
YES
YES```

## 样例 #2

### 输入

```
5
8
-8 2 -6 -5 -4 3 3 2
7
1 1 3 1 0 -2 -1
7
6 12 8 6 2 6 10
6
5 1 2 3 6 7
5
1 3 4 3 0```

### 输出

```
NO
YES
NO
NO
NO```

# AI分析结果

### 题目翻译
# Omkar和中位数

## 题目描述
糟糕！Ray又把他的数组弄丢了！不过，Omkar可能能帮上忙，因为他觉得自己找到了Ray数组的Omk数组。对于一个元素为 $a_1, a_2, \ldots, a_{2k - 1}$ 的数组 $a$，其Omk数组是一个元素为 $b_1, b_2, \ldots, b_{k}$ 的数组 $b$，其中 $b_i$ 等于 $a_1, a_2, \ldots, a_{2i - 1}$ 的中位数（对于所有的 $i$）。Omkar 找到了一个长度为 $n$ 的数组 $b$（$1 \leq n \leq 2 \cdot 10^5$，$-10^9 \leq b_i \leq 10^9$）。给定这个数组 $b$，Ray 想验证 Omkar 的说法，看看 $b$ 是否真的是某个数组 $a$ 的 Omk 数组。你能帮帮 Ray 吗？

一组数 $a_1, a_2, \ldots, a_{2i - 1}$ 的中位数是数 $c_{i}$，其中 $c_{1}, c_{2}, \ldots, c_{2i - 1}$ 表示按非降序排序后的 $a_1, a_2, \ldots, a_{2i - 1}$。

## 说明/提示
在第一个样例的第二个情况中，数组 $[4]$ 会生成一个 Omk 数组 $[4]$，因为第一个元素的中位数是 $4$。

在第一个样例的第四个情况中，数组 $[3, 2, 5]$ 会生成一个 Omk 数组 $[3, 3]$，因为 $3$ 的中位数是 $3$，$2, 3, 5$ 的中位数也是 $3$。

在第一个样例的第五个情况中，数组 $[2, 1, 0, 3, 4, 4, 3]$ 会生成一个 Omk 数组 $[2, 1, 2, 3]$，因为：
- $2$ 的中位数是 $2$；
- $0, 1, 2$ 的中位数是 $1$；
- $0, 1, 2, 3, 4$ 的中位数是 $2$；
- $0, 1, 2, 3, 3, 4, 4$ 的中位数是 $3$。

在第二个样例的第二个情况中，数组 $[1, 0, 4, 3, 5, -2, -2, -2, -4, -3, -4, -1, 5]$ 会生成一个 Omk 数组 $[1, 1, 3, 1, 0, -2, -1]$，因为：
- $1$ 的中位数是 $1$；
- $0, 1, 4$ 的中位数是 $1$；
- $0, 1, 3, 4, 5$ 的中位数是 $3$；
- $-2, -2, 0, 1, 3, 4, 5$ 的中位数是 $1$；
- $-4, -2, -2, -2, 0, 1, 3, 4, 5$ 的中位数是 $0$；
- $-4, -4, -3, -2, -2, -2, 0, 1, 3, 4, 5$ 的中位数是 $-2$；
- $-4, -4, -3, -2, -2, -2, -1, 0, 1, 3, 4, 5, 5$ 的中位数是 $-1$。

对于所有答案为 NO 的情况，可以证明不可能找到一个数组 $a$ 使得 $b$ 是 $a$ 的 Omk 数组。

## 样例 #1
### 输入
```
5
4
6 2 1 3
1
4
5
4 -8 5 6 -7
2
3 3
4
2 1 2 3
```
### 输出
```
NO
YES
NO
YES
YES
```

## 样例 #2
### 输入
```
5
8
-8 2 -6 -5 -4 3 3 2
7
1 1 3 1 0 -2 -1
7
6 12 8 6 2 6 10
6
5 1 2 3 6 7
5
1 3 4 3 0
```
### 输出
```
NO
YES
NO
NO
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过分析相邻中位数 $b_{i - 1}$ 和 $b_i$ 之间的关系来判断是否存在合法的数组 $a$。每次加入两个数，中位数最多移动一位，所以需要保证在 $b_{i - 1}$ 和 $b_i$ 之间不存在其他已经出现过的中位数。

- **思路对比**：三位作者思路本质相同，都是围绕相邻中位数的关系展开判断。water_tomato 和 E1_de5truct0r 都借助 `set` 来维护已出现的中位数，丛雨除了使用 `set` 外，还提供了链表的实现方式。
- **算法要点**：利用 `set` 的有序性和查找功能，快速判断相邻中位数之间是否存在其他数；链表则通过指针操作来模拟元素的插入和查找。
- **解决难点**：关键在于理解每次加入两个数对中位数的影响，以及如何高效地判断相邻中位数之间是否存在其他数。

### 题解选择
- **water_tomato（5星）**
  - **关键亮点**：思路清晰，代码简洁易懂，详细解释了使用 `set` 维护中位数的过程和判断条件。
- **E1_de5truct0r（4星）**
  - **关键亮点**：简洁地阐述了核心思路，明确指出了判断相邻中位数关系的要点和复杂度。
- **丛雨（3星）**
  - **关键亮点**：提供了 `set` 和链表两种实现方式，对中位数移动的原理有形象的举例说明。

### 重点代码
#### water_tomato 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n;
int b[N];
set<int> s;
int main(){
    scanf("%d",&T);
    while(T--){
        bool fl=1;
        s.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i]);
            if(!s.count(b[i])) s.insert(b[i]);
            if(b[i]==b[i-1]) continue;
            if(b[i-1]<b[i]){
                if(s.upper_bound(b[i-1])!=s.find(b[i])){
                    fl=0;
                }
            }
            else{
                if(s.upper_bound(b[i])!=s.find(b[i-1])){
                    fl=0;
                }
            }
        }
        if(fl){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
```
**核心实现思想**：使用 `set` 维护已出现的中位数，遍历数组 $b$，对于相邻的 $b_{i - 1}$ 和 $b_i$，若 $b_{i - 1} < b_i$，检查 $b_{i - 1}$ 的后继是否为 $b_i$；若 $b_{i - 1} > b_i$，检查 $b_i$ 的后继是否为 $b_{i - 1}$，若不满足条件则标记为不合法。

### 最优关键思路或技巧
- **使用 `set` 维护中位数**：`set` 的有序性和查找功能可以高效地判断相邻中位数之间是否存在其他数，时间复杂度为 $O(\log n)$。
- **分析相邻中位数的关系**：通过分析每次加入两个数对中位数的影响，得出相邻中位数之间的限制条件，从而简化判断过程。

### 拓展思路
同类型题目可能会改变加入元素的数量或中位数的计算方式，但核心思路仍然是分析元素变化对中位数的影响。类似的算法套路包括利用数据结构（如 `set`、链表）维护有序序列，通过查找和比较来判断条件是否满足。

### 推荐题目
- [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
- [P2672 [NOIP2015 普及组] 推销员](https://www.luogu.com.cn/problem/P2672)
- [P1801 黑匣子](https://www.luogu.com.cn/problem/P1801)

### 个人心得
题解中未包含个人心得内容。

---
处理用时：52.79秒