# 题目信息

# AquaMoon and Two Arrays

## 题目描述

AquaMoon and Cirno are playing an interesting game with arrays. Cirno has prepared two arrays $ a $ and $ b $ , both consist of $ n $ non-negative integers. AquaMoon can perform the following operation an arbitrary number of times (possibly zero):

- She chooses two indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ), then decreases the $ i $ -th element of array $ a $ by $ 1 $ , and increases the $ j $ -th element of array $ a $ by $ 1 $ . The resulting values at $ i $ -th and $ j $ -th index of array $ a $ are $ a_i - 1 $ and $ a_j + 1 $ , respectively. Each element of array $ a $ must be non-negative after each operation. If $ i = j $ this operation doesn't change the array $ a $ .

AquaMoon wants to make some operations to make arrays $ a $ and $ b $ equal. Two arrays $ a $ and $ b $ are considered equal if and only if $ a_i = b_i $ for all $ 1 \leq i \leq n $ .

Help AquaMoon to find a sequence of operations that will solve her problem or find, that it is impossible to make arrays $ a $ and $ b $ equal.

Please note, that you don't have to minimize the number of operations.

## 说明/提示

In the first example, we do the following operations:

- $ i = 2 $ , $ j = 1 $ : $ [1, 2, 3, 4] \rightarrow [2, 1, 3, 4] $ ;
- $ i = 3 $ , $ j = 1 $ : $ [2, 1, 3, 4] \rightarrow [3, 1, 2, 4] $ ;

In the second example, it's impossible to make two arrays equal.

## 样例 #1

### 输入

```
4
4
1 2 3 4
3 1 2 4
2
1 3
2 1
1
0
0
5
4 3 2 1 0
0 1 2 3 4```

### 输出

```
2
2 1
3 1
-1
0
6
1 4
1 4
1 5
1 5
2 5
2 5```

# AI分析结果

### 题目内容
# AquaMoon和两个数组

## 题目描述
AquaMoon和Cirno正在玩一个关于数组的有趣游戏。Cirno准备了两个数组$a$和$b$，它们都由$n$个非负整数组成。AquaMoon可以任意多次（可能为零次）执行以下操作：
- 她选择两个索引$i$和$j$（$1 \leq i, j \leq n$），然后将数组$a$的第$i$个元素减$1$，并将数组$a$的第$j$个元素加$1$。操作后数组$a$在第$i$个和第$j$个索引处的结果值分别为$a_i - 1$和$a_j + 1$。每次操作后数组$a$的每个元素都必须是非负的。如果$i = j$，此操作不会改变数组$a$。
AquaMoon想通过一些操作使数组$a$和$b$相等。当且仅当对于所有$1 \leq i \leq n$，都有$a_i = b_i$时，两个数组$a$和$b$被认为是相等的。
帮助AquaMoon找到一系列操作来解决她的问题，或者确定无法使数组$a$和$b$相等。
请注意，你不必最小化操作次数。

## 说明/提示
在第一个示例中，我们执行以下操作：
- $i = 2$，$j = 1$：$[1, 2, 3, 4] \rightarrow [2, 1, 3, 4]$；
- $i = 3$，$j = 1$：$[2, 1, 3, 4] \rightarrow [3, 1, 2, 4]$；

在第二个示例中，无法使两个数组相等。

## 样例 #1
### 输入
```
4
4
1 2 3 4
3 1 2 4
2
1 3
2 1
1
0
0
5
4 3 2 1 0
0 1 2 3 4
```
### 输出
```
2
2 1
3 1
-1
0
6
1 4
1 4
1 5
1 5
2 5
2 5
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于操作过程中数组元素总和不变这一特性，判断能否将数组$a$变成数组$b$。若数组$a$和$b$的元素总和不相等，则一定无解；若相等，则有解。对于有解情况，不同题解在记录和输出操作方式上有所不同。有的使用队列、向量等数据结构分别记录需要减一和加一操作的下标，有的通过遍历数组找到正负差值的位置并输出操作。

### 通用建议与扩展思路
解决此类问题，关键在于抓住操作对数组某些性质（如总和）的不变性来判断可行性。在构造操作方案时，要清晰地记录和处理数据。对于类似题目，可以拓展到更复杂的数组操作规则，或者增加对操作次数的限制等条件，进一步加深对这类问题的理解和解决能力。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过简单计算和判断解决实际问题，锻炼对数据的处理和逻辑判断能力。
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要利用枚举和数学运算来找出满足等式的组合，与本题在利用数学关系解决问题上有相似之处。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：结合质数判断和回文数特性，通过合理的枚举和优化解决问题，与本题同样考察对数学概念的运用和编程实现能力。 

---
处理用时：31.42秒