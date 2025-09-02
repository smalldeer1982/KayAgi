# 题目信息

# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3```

# AI分析结果



# 魔法图书馆

## 题目描述

这是一个交互题。

奥森弗特学院超自然现象研究部开放了魔法图书馆，这里收藏着雷坦尼亚最伟大术士们的著作——共 $n$（$3 \leq n \leq 10^{18}$）种图书，编号从 $1$ 到 $n$。每种图书在馆内都有且仅有两本副本！某夜，你发现三本不同颜色的典籍被盗，需要找出这三个被盗的编号 $a,b,c$（互不相同）。

你只能使用一个魔法查询：
- `xor l r`：询问编号在 $[l,r]$ 范围内所有现存图书的异或和（每个现存图书的编号出现一次）。

最多进行 150 次查询，要求找出 $a,b,c$。

---

### 题解分析与结论

各题解核心思路均围绕异或性质与二分法展开，核心分为两种情形：

1. **异或和不为零**：通过两次二分确定最小值和最大值
2. **异或和为零**：利用二进制位特性确定其中一个数，再二分处理

#### 精选题解（评分≥4星）

1. **沉石鱼惊旋（5星）**
   - **关键亮点**：清晰处理两种情形，利用最高位特性破解零异或难题
   - **核心代码**：
     ```cpp
     ll axbxc = query(1, n);
     if (axbxc == 0) {
         // 处理最高位找到最小值
         for (int i = 60; i >= 0; i--) {
             ll t = query(1, (1LL << i) - 1);
             if (t) { /*...*/ }
         }
     } else {
         // 二分查找极值
     }
     ```
   - **心得**：通过枚举二进制位快速定位缺失数，减少查询次数

2. **Priestess_SLG（4星）**
   - **关键亮点**：严谨证明二进制位分布特性，确保正确性
   - **思路**：当异或和为0时，三个数的最高位必然成对出现，通过最高位分割区间

3. **wly09（4星）**
   - **关键亮点**：简洁实现二分逻辑，处理边界清晰
   - **代码片段**：
     ```cpp
     int64_t bs(int64_t st, int64_t n) {
         while(l<=r) if(区间异或非零) 调整边界
     }
     ```

---

### 最优思路总结

**关键技巧**：
1. **整体异或和判零**：初始查询`xor 1 n`获取三数异或和，分情形处理
2. **极值二分法**：
   - 非零情形：二分查找第一个非零前缀（最小值）、最后一个非零后缀（最大值）
   - 零异或情形：枚举最高位，确定最小数后二分剩余区间
3. **二进制位分析**：利用异或和为零时最高位成对出现的特性

**拓展思考**：
- 类似问题可考虑位分解与区间分割的结合
- 交互题常用二分框架，需注意单调性证明

---

### 推荐练习
1. [CF1771F] 模板题（异或性质+主席树）
2. [P8056] 高维异或（二进制分解）
3. [CF1851G] 异或最短路（位运算+图论）

---
处理用时：50.03秒