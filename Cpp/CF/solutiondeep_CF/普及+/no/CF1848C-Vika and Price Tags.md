# 题目信息

# Vika and Price Tags

## 题目描述

Vika came to her favorite cosmetics store "Golden Pear". She noticed that the prices of $ n $ items have changed since her last visit.

She decided to analyze how much the prices have changed and calculated the difference between the old and new prices for each of the $ n $ items.

Vika enjoyed calculating the price differences and decided to continue this process.

Let the old prices be represented as an array of non-negative integers $ a $ , and the new prices as an array of non-negative integers $ b $ . Both arrays have the same length $ n $ .

In one operation, Vika constructs a new array $ c $ according to the following principle: $ c_i = |a_i - b_i| $ . Then, array $ c $ renamed into array $ b $ , and array $ b $ renamed into array $ a $ at the same time, after which Vika repeats the operation with them.

For example, if $ a = [1, 2, 3, 4, 5, 6, 7] $ ; $ b = [7, 6, 5, 4, 3, 2, 1] $ , then $ c = [6, 4, 2, 0, 2, 4, 6] $ . Then, $ a = [7, 6, 5, 4, 3, 2, 1] $ ; $ b = [6, 4, 2, 0, 2, 4, 6] $ .

Vika decided to call a pair of arrays $ a $ , $ b $ dull if after some number of such operations all elements of array $ a $ become zeros.

Output "YES" if the original pair of arrays is dull, and "NO" otherwise.

## 说明/提示

In the first test case, the array $ a $ is initially zero.

In the second test case, after the first operation $ a = [1, 2, 3], b = [0, 0, 0] $ . After the second operation $ a = [0, 0, 0], b = [1, 2, 3] $ .

In the third test case, it can be shown that the array $ a $ will never become zero.

## 样例 #1

### 输入

```
9
4
0 0 0 0
1 2 3 4
3
1 2 3
1 2 3
2
1 2
2 1
6
100 23 53 11 56 32
1245 31 12 6 6 6
7
1 2 3 4 5 6 7
7 6 5 4 3 2 1
3
4 0 2
4 0 2
3
2 5 2
1 3 4
2
6 1
4 2
2
0 0
0 3```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES```

# AI分析结果

### 题目内容重写

#### 题目描述

Vika来到她最喜欢的化妆品店“Golden Pear”。她注意到自从上次访问以来，$n$件商品的价格发生了变化。

她决定分析价格变化了多少，并计算了每件商品的旧价格和新价格之间的差异。

Vika喜欢计算价格差异，并决定继续这个过程。

设旧价格表示为一个非负整数数组$a$，新价格表示为一个非负整数数组$b$。两个数组的长度相同，均为$n$。

在一次操作中，Vika根据以下原则构造一个新数组$c$：$c_i = |a_i - b_i|$。然后，数组$c$被重命名为数组$b$，数组$b$被重命名为数组$a$，之后Vika用它们重复操作。

例如，如果$a = [1, 2, 3, 4, 5, 6, 7]$；$b = [7, 6, 5, 4, 3, 2, 1]$，那么$c = [6, 4, 2, 0, 2, 4, 6]$。然后，$a = [7, 6, 5, 4, 3, 2, 1]$；$b = [6, 4, 2, 0, 2, 4, 6]$。

Vika决定称一对数组$a$、$b$为“dull”，如果在经过若干次这样的操作后，数组$a$的所有元素都变为零。

如果原始数组对是“dull”，则输出“YES”，否则输出“NO”。

### 算法分类
数学

### 题解分析与结论

这道题的核心是通过不断对数组$a$和$b$进行操作，最终判断是否能使$a$的所有元素变为零。操作的本质是辗转相减法，类似于求最大公约数（GCD）的过程。因此，问题的关键在于理解操作的周期性以及如何通过GCD和奇偶性来判断是否满足条件。

### 所选高星题解

#### 题解1：作者：pur_lin (赞：19)  
**星级：5星**  
**关键亮点：**  
- 通过GCD和奇偶性分类，将问题简化为判断所有数对的奇偶性是否一致。
- 详细证明了数对的奇偶性分类，并给出了清晰的代码实现。

**核心代码：**
```cpp
int check(int x, int y){
    int t = gcd(x, y);
    x /= t; y /= t;
    if (x % 2 == 0) return 0;
    if (y % 2 == 0) return 1;
    return 2;
}
```
**实现思想：**  
通过GCD将数对简化为互质形式，然后根据奇偶性进行分类，最终判断所有数对的分类是否一致。

#### 题解2：作者：Phartial (赞：15)  
**星级：4星**  
**关键亮点：**  
- 通过模拟操作过程，计算每个数对变为$(0, x)$所需的步数，并判断所有步数模3是否一致。
- 优化了模拟过程，避免了直接暴力计算。

**核心代码：**
```cpp
int C(int a, int b) {
    if (!a || !b) return !!a;
    if (a < b) {
        int k = b / a, p = b % a;
        return (k & 1) ? 2 + C(p, a) : C(a, p);
    } else {
        int k = a / b, p = a % b;
        return (k & 1) ? 1 + C(b, p) : C(p, b);
    }
}
```
**实现思想：**  
通过递归模拟操作过程，计算每个数对变为$(0, x)$所需的步数，并判断所有步数模3是否一致。

#### 题解3：作者：winter2020 (赞：4)  
**星级：4星**  
**关键亮点：**  
- 通过奇偶性变化过程，将问题简化为判断所有数对的奇偶性是否一致。
- 提供了详细的奇偶性变化过程分析，并给出了简洁的代码实现。

**核心代码：**
```cpp
while (a[i] % 2 == 0 && b[i] % 2 == 0) a[i] /= 2, b[i] /= 2;
if (a[i] % 2 == 0) st[0] = true;
else if (b[i] % 2 == 0) st[1] = true;
else st[2] = true;
```
**实现思想：**  
通过不断除以2，将数对简化为至少有一个奇数，然后根据奇偶性进行分类，最终判断所有数对的分类是否一致。

### 最优关键思路或技巧

1. **GCD与奇偶性结合**：通过GCD将数对简化为互质形式，然后根据奇偶性进行分类，是解决这类问题的关键。
2. **操作步数模3判断**：通过模拟操作过程，计算每个数对变为$(0, x)$所需的步数，并判断所有步数模3是否一致，是一种有效的优化方法。
3. **不断除以2简化问题**：通过不断除以2，将数对简化为至少有一个奇数，然后根据奇偶性进行分类，可以简化问题。

### 可拓展之处

这类问题可以拓展到其他类似的操作过程，例如通过不同的操作规则来判断是否能使数组达到某种状态。类似的题目可以通过分析操作的周期性和数对的性质来简化问题。

### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1062 数列](https://www.luogu.com.cn/problem/P1062)

### 个人心得总结

在解决这类问题时，理解操作的周期性以及如何通过GCD和奇偶性来简化问题是非常重要的。通过不断模拟和分析，可以找到问题的关键点，从而设计出高效的算法。

---
处理用时：46.02秒