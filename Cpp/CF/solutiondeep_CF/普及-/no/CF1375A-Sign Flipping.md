# 题目信息

# Sign Flipping

## 题目描述

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ , where $ n $ is odd. You are allowed to flip the sign of some (possibly all or none) of them. You wish to perform these flips in such a way that the following conditions hold:

1. At least $ \frac{n - 1}{2} $ of the adjacent differences $ a_{i + 1} - a_i $ for $ i = 1, 2, \dots, n - 1 $ are greater than or equal to $ 0 $ .
2. At least $ \frac{n - 1}{2} $ of the adjacent differences $ a_{i + 1} - a_i $ for $ i = 1, 2, \dots, n - 1 $ are less than or equal to $ 0 $ .

Find any valid way to flip the signs. It can be shown that under the given constraints, there always exists at least one choice of signs to flip that satisfies the required condition. If there are several solutions, you can find any of them.

## 说明/提示

In the first test case, the difference $ (-4) - (-2) = -2 $ is non-positive, while the difference $ 3 - (-4) = 7 $ is non-negative.

In the second test case, we don't have to flip any signs. All $ 4 $ differences are equal to $ 0 $ , which is both non-positive and non-negative.

In the third test case, $ 7 - (-4) $ and $ 4 - (-6) $ are non-negative, while $ (-4) - (-2) $ and $ (-6) - 7 $ are non-positive.

## 样例 #1

### 输入

```
5
3
-2 4 3
5
1 1 1 1 1
5
-2 4 7 -6 4
9
9 7 -4 -2 1 -3 9 -4 -5
9
-4 1 9 4 8 9 5 1 -9```

### 输出

```
-2 -4 3
1 1 1 1 1
-2 -4 7 -6 4
-9 -7 -4 2 1 -3 -9 -4 -5
4 -1 -9 -4 -8 -9 -5 -1 9```

# AI分析结果

### 题目内容
# 符号翻转

## 题目描述
给定 $n$ 个整数 $a_1, a_2, \dots, a_n$ ，其中 $n$ 为奇数。你可以翻转其中一些（可能是全部或一个都不翻转）数的符号。你希望通过这些翻转，使得以下条件成立：
1. 对于 $i = 1, 2, \dots, n - 1$ ，至少有 $\frac{n - 1}{2}$ 个相邻差值 $a_{i + 1} - a_i$ 大于或等于 $0$ 。
2. 对于 $i = 1, 2, \dots, n - 1$ ，至少有 $\frac{n - 1}{2}$ 个相邻差值 $a_{i + 1} - a_i$ 小于或等于 $0$ 。

找出任何一种有效的符号翻转方式。可以证明，在给定的约束条件下，总是至少存在一种符号翻转的选择，能够满足所需条件。如果有多个解决方案，找出其中任何一个即可。

## 说明/提示
在第一个测试用例中，差值 $(-4) - (-2) = -2$ 是非正数，而差值 $3 - (-4) = 7$ 是非负数。

在第二个测试用例中，我们无需翻转任何符号。所有 $4$ 个差值都等于 $0$ ，$0$ 既是非正数也是非负数。

在第三个测试用例中，$7 - (-4)$ 和 $4 - (-6)$ 是非负数，而 $(-4) - (-2)$ 和 $(-6) - 7$ 是非正数。

## 样例 #1
### 输入
```
5
3
-2 4 3
5
1 1 1 1 1
5
-2 4 7 -6 4
9
9 7 -4 -2 1 -3 9 -4 -5
9
-4 1 9 4 8 9 5 1 -9
```
### 输出
```
-2 -4 3
1 1 1 1 1
-2 -4 7 -6 4
-9 -7 -4 2 1 -3 -9 -4 -5
4 -1 -9 -4 -8 -9 -5 -1 9
```
### 算法分类
构造
### 综合分析与结论
这些题解的核心思路大多是通过构造让数列中的数正负交替排列，利用正数与负数相减，其差值正负性不同的特点，满足至少 $\frac{n - 1}{2}$ 个相邻差值大于等于 $0$ 且至少 $\frac{n - 1}{2}$ 个相邻差值小于等于 $0$ 的条件。因为 $n$ 为奇数，$n - 1$ 为偶数，这样构造能保证差值按正负交替出现，从而满足题目要求。各题解的主要差异在于代码实现细节，如输入输出方式、对数字符号处理的具体写法等。
### 所选的题解
- **作者：huayucaiji (5星)**
    - **关键亮点**：思路清晰，先点明题目本质，利用数学结论“如果 $a < 0, b > 0$，则 $a - b < 0, b - a > 0$”，通过判断数组下标奇偶性来改变数的符号，代码实现简洁明了。
    - **重点代码**：
```cpp
for(int i = 1; i <= n; i++) {
    a[i] = read();
    if(i & 1 && a[i] > 0) {
        a[i] = -a[i];
    }
    if(i % 2 == 0 && a[i] < 0) {
        a[i] = -a[i];//改变正负
    }
}
```
    - **核心实现思想**：遍历输入的数，当数组下标为奇数且数为正时，将其变为负数；当下标为偶数且数为负时，将其变为正数，从而实现正负交替。
- **作者：Andrewzdm (4星)**
    - **关键亮点**：直接阐述构造思路，让 $a_i$ 的符号按“正、负、正、负、正……”的顺序排列，不考虑 $0$ 的特殊情况，代码简洁高效。
    - **重点代码**：
```cpp
for(int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    if(i & 1)
        cout << abs(x) << ' ';
    else
        cout << -abs(x) << ' ';
}
```
    - **核心实现思想**：根据输入数的下标奇偶性，直接输出对应绝对值的正负形式，奇数下标输出正数，偶数下标输出负数。
- **作者：_cmh (4星)**
    - **关键亮点**：代码简洁，不使用数组，直接在输入时根据下标奇偶性和数的正负判断是否需要改变符号，边输入边处理输出。
    - **重点代码**：
```cpp
for(int i = 1; i <= n; i++) {
    cin >> x;
    if((i % 2 && x < 0) || (i % 2 == 0 && x > 0)) cout << -x << " ";
    else cout << x << " ";
}
```
    - **核心实现思想**：输入每个数时，当下标为奇数且数为负，或下标为偶数且数为正时，输出其相反数，否则直接输出原数。
### 最优关键思路或技巧
通过让数列中的数正负交替排列来满足相邻差值的条件，利用下标奇偶性处理数的符号，避免复杂的计算和判断，简化代码实现。
### 拓展思路
同类型题可考察不同的构造条件，如对相邻元素的和、积等提出条件要求，或改变数列长度的奇偶性等。类似算法套路可用于解决一些需要通过特定排列来满足条件的构造类问题，关键在于找到满足条件的排列规律。
### 洛谷相似题目
- **P1080 [NOIP2012 提高组] 国王游戏**：通过合理构造顺序解决贪心构造类问题。
- **P1464 Function**：需要构造函数来满足给定条件，与本题构造数列满足条件类似。
- **P2678 [NOIP2015 提高组] 跳石头**：通过构造一种移除石头的方式满足题目要求，同样是构造类问题。 

---
处理用时：46.75秒