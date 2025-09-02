# 题目信息

# Odds and Ends

## 题目描述

Where do odds begin, and where do they end? Where does hope emerge, and will they ever break?

Given an integer sequence $ a_{1},a_{2},...,a_{n} $ of length $ n $ . Decide whether it is possible to divide it into an odd number of non-empty subsegments, the each of which has an odd length and begins and ends with odd numbers.

A subsegment is a contiguous slice of the whole sequence. For example, $ {3,4,5} $ and $ {1} $ are subsegments of sequence $ {1,2,3,4,5,6} $ , while $ {1,2,4} $ and $ {7} $ are not.

## 说明/提示

In the first example, divide the sequence into $ 1 $ subsegment: $ {1,3,5} $ and the requirements will be met.

In the second example, divide the sequence into $ 3 $ subsegments: $ {1,0,1} $ , $ {5} $ , $ {1} $ .

In the third example, one of the subsegments must start with $ 4 $ which is an even number, thus the requirements cannot be met.

In the fourth example, the sequence can be divided into $ 2 $ subsegments: $ {3,9,9} $ , $ {3} $ , but this is not a valid solution because $ 2 $ is an even number.

## 样例 #1

### 输入

```
3
1 3 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
1 0 1 5 1
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
3
4 3 1
```

### 输出

```
No
```

## 样例 #4

### 输入

```
4
3 9 9 3
```

### 输出

```
No
```

# AI分析结果

【题目内容（中文重写）】
# 奇偶问题

## 题目描述
奇数从哪里开始，又在哪里结束？希望从哪里出现，又是否会破灭？

给定一个长度为 $n$ 的整数序列 $a_{1},a_{2},\cdots,a_{n}$ 。判断是否有可能将其划分为奇数个非空子段，且每个子段的长度为奇数，并且首尾元素均为奇数。

子段是整个序列的连续切片。例如，$ {3,4,5} $ 和 $ {1} $ 是序列 $ {1,2,3,4,5,6} $ 的子段，而 $ {1,2,4} $ 和 $ {7} $ 不是。

## 说明/提示
在第一个样例中，将序列划分为 $1$ 个子段：$ {1,3,5} $ ，满足要求。

在第二个样例中，将序列划分为 $3$ 个子段：$ {1,0,1} $ ，$ {5} $ ，$ {1} $ 。

在第三个样例中，其中一个子段必须以偶数 $4$ 开头，因此不满足要求。

在第四个样例中，序列可以划分为 $2$ 个子段：$ {3,9,9} $ ，$ {3} $ ，但这不是一个有效的解决方案，因为 $2$ 是偶数。

## 样例 #1
### 输入
```
3
1 3 5
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
5
1 0 1 5 1
```
### 输出
```
Yes
```

## 样例 #3
### 输入
```
3
4 3 1
```
### 输出
```
No
```

## 样例 #4
### 输入
```
4
3 9 9 3
```
### 输出
```
No
```

【算法分类】
数学

【综合分析与结论】
- **思路对比**：各位作者思路基本一致，都依据“奇数个奇数的和是奇数”这一数学原理，得出序列长度 $n$ 必须为奇数，且序列首尾元素也必须为奇数这两个关键条件。满足这两个条件则输出 "Yes"，否则输出 "No"。
- **算法要点**：核心在于对序列长度和首尾元素奇偶性的判断。部分作者使用位运算（如 `x & 1`）来优化奇偶性判断，提高效率。
- **解决难点**：本题难点在于理解题目条件背后的数学逻辑，即奇数个奇数长度的子段组合起来，总长度必然是奇数，且首尾子段的首尾元素决定了原序列的首尾元素必须为奇数。

【所选题解】
- **作者：Karry5307 (4星)**
    - **关键亮点**：思路清晰，代码中使用了快速读入模板，且通过位运算判断奇偶性，优化了代码效率。
    - **个人心得**：提醒自己有些显而易见的结论（如奇数不等于偶数）在做题时容易忘记，要时刻留意。
- **作者：DPair (4星)**
    - **关键亮点**：简洁明了地阐述了思路，强调了位运算在本题中的优化作用，代码结构清晰。
- **作者：lhjy666 (4星)**
    - **关键亮点**：直接指出本题只需特判总数量和首尾元素，代码简洁易懂。

【重点代码】
```cpp
// Karry5307 的代码
puts((n&1)&&(x[1]&1)&&(x[n]&1)?"Yes":"No");

// DPair 的代码
if(!(n & 1)) {
    printf("No");
    return 0;
}
if(!(a[1] & 1) || !(a[n] & 1)) {
    printf("No");
    return 0;
}
printf("Yes");

// lhjy666 的代码
if(n%2==0) {
    printf("No");
    return 0;
}
if(a[1]%2==0||a[n]%2==0) {
    printf("No");
    return 0;
}
printf("Yes");
```
【核心实现思想】
通过判断序列长度 $n$ 是否为奇数，以及序列首尾元素是否为奇数，来确定是否满足题目要求。若都满足则输出 "Yes"，否则输出 "No"。

【最优关键思路或技巧】
- **数学思维**：利用“奇数个奇数的和是奇数”这一数学结论，快速确定解题方向。
- **位运算优化**：使用 `x & 1` 来判断一个数的奇偶性，比 `x % 2` 效率更高。

【拓展思路】
同类型题目可能会对划分条件进行变化，如要求划分为偶数个子段，或子段的其他属性（如元素和、元素积等）满足特定条件。解题时仍需从数学原理出发，分析条件之间的逻辑关系。

【推荐题目】
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察对条件的分析和逻辑判断。
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要根据给定条件进行合理的模拟和判断。
3. [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)：涉及对序列性质的分析和判断。

---
处理用时：33.41秒