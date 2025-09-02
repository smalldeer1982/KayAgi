# 题目信息

# Strange Test

## 题目描述

Igor is in 11th grade. Tomorrow he will have to write an informatics test by the strictest teacher in the school, Pavel Denisovich.

Igor knows how the test will be conducted: first of all, the teacher will give each student two positive integers $ a $ and $ b $ ( $ a < b $ ). After that, the student can apply any of the following operations any number of times:

- $ a := a + 1 $ (increase $ a $ by $ 1 $ ),
- $ b := b + 1 $ (increase $ b $ by $ 1 $ ),
- $ a := a \ | \ b $ (replace $ a $ with the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of $ a $ and $ b $ ).

To get full marks on the test, the student has to tell the teacher the minimum required number of operations to make $ a $ and $ b $ equal.

Igor already knows which numbers the teacher will give him. Help him figure out what is the minimum number of operations needed to make $ a $ equal to $ b $ .

## 说明/提示

In the first test case, it is optimal to apply the third operation.

In the second test case, it is optimal to apply the first operation three times.

In the third test case, it is optimal to apply the second operation and then the third operation.

## 样例 #1

### 输入

```
5
1 3
5 8
2 5
3 19
56678 164422```

### 输出

```
1
3
2
1
23329```

# AI分析结果

### 题目翻译
# 奇怪的测试

## 题目描述

Igor是11年级的学生。明天他将由学校里最严格的老师Pavel Denisovich进行一场信息学测试。

Igor知道测试的流程：首先，老师会给每个学生两个正整数 $a$ 和 $b$（$a < b$）。之后，学生可以任意次数地应用以下操作：

- $a := a + 1$（将 $a$ 增加 $1$），
- $b := b + 1$（将 $b$ 增加 $1$），
- $a := a \ | \ b$（将 $a$ 替换为 $a$ 和 $b$ 的[按位或](https://en.wikipedia.org/wiki/Bitwise_operation#OR)）。

为了在测试中获得满分，学生需要告诉老师使 $a$ 和 $b$ 相等所需的最少操作次数。

Igor已经知道老师会给他哪些数字。请帮助他计算出使 $a$ 等于 $b$ 所需的最少操作次数。

## 说明/提示

在第一个测试用例中，最优的操作是应用第三个操作。

在第二个测试用例中，最优的操作是应用第一个操作三次。

在第三个测试用例中，最优的操作是先应用第二个操作，然后再应用第三个操作。

## 样例 #1

### 输入

```
5
1 3
5 8
2 5
3 19
56678 164422```

### 输出

```
1
3
2
1
23329```

### 算法分类
位运算、枚举

### 题解分析与结论
1. **XL4453的题解**：
   - **思路**：通过枚举 $a$ 和 $b$ 的增加次数，计算使 $a$ 和 $b$ 相等的最小操作次数。重点在于理解按位或操作的性质，即 $a|b \ge a$，因此先增加 $a$ 或 $b$ 再按位或可能更优。
   - **难点**：理解按位或操作对 $a$ 和 $b$ 的影响，以及如何通过枚举找到最优解。
   - **评分**：4星
   - **关键亮点**：通过枚举和按位或操作的性质，简化了问题，代码简洁易懂。

2. **Na2PtCl6的题解**：
   - **思路**：通过二进制位分析，计算 $a$ 和 $b$ 的按位或操作后的结果，并枚举 $a$ 的增加次数，找到最小操作次数。
   - **难点**：二进制位的分析和按位或操作后的结果处理。
   - **评分**：3星
   - **关键亮点**：通过二进制位分析，深入理解了按位或操作的影响，但代码复杂度较高。

3. **OIerZhang的题解**：
   - **思路**：通过枚举 $a$ 和 $b$ 的增加次数，计算使 $a$ 和 $b$ 相等的最小操作次数。重点在于理解按位或操作的性质，即 $a|b \ge a$，因此先增加 $a$ 或 $b$ 再按位或可能更优。
   - **难点**：理解按位或操作对 $a$ 和 $b$ 的影响，以及如何通过枚举找到最优解。
   - **评分**：4星
   - **关键亮点**：通过枚举和按位或操作的性质，简化了问题，代码简洁易懂。

### 最优关键思路
通过枚举 $a$ 和 $b$ 的增加次数，结合按位或操作的性质，找到使 $a$ 和 $b$ 相等的最小操作次数。这种方法简化了问题，代码实现也较为简洁。

### 可拓展之处
类似的问题可以通过枚举和位运算的性质来解决，例如在二进制表示下的数位操作问题。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

### 个人心得摘录
- XL4453：第二段的证明想了好久，差点没整出来。当 $a>b$ 的时候，由于 $a|b\ge a$，而且没有让 $a$ 变小的方法，所以只能让 $b$ 增加，那么不取或而直接将 $b$ 增加是最好的选择。
- Na2PtCl6：对于 $a_i=1$ 的情况，如果 $b_i=0$，就要给 $b$ 加上一个数，但显然直接把 $b_i$ 变成 $1$ 很可能不是最优的。因为对于 $a_j=0$ 的情况， $b_j$ 的值是任意的，所以如果 $b_j=1$ 就可以在 $b$ 更高位需要从 $0$ 变 $1$时，把 $b_j$ 变为 $0$。

---
处理用时：30.03秒