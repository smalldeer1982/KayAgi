# 题目信息

# Candies

## 题目描述

Recently Vova found $ n $ candy wrappers. He remembers that he bought $ x $ candies during the first day, $ 2x $ candies during the second day, $ 4x $ candies during the third day, $ \dots $ , $ 2^{k-1} x $ candies during the $ k $ -th day. But there is an issue: Vova remembers neither $ x $ nor $ k $ but he is sure that $ x $ and $ k $ are positive integers and $ k > 1 $ .

Vova will be satisfied if you tell him any positive integer $ x $ so there is an integer $ k>1 $ that $ x + 2x + 4x + \dots +       2^{k-1} x = n $ . It is guaranteed that at least one solution exists. Note that $ k > 1 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, one of the possible answers is $ x=1, k=2 $ . Then $ 1 \cdot 1 + 2 \cdot 1 $ equals $ n=3 $ .

In the second test case of the example, one of the possible answers is $ x=2, k=2 $ . Then $ 1 \cdot 2 + 2 \cdot 2 $ equals $ n=6 $ .

In the third test case of the example, one of the possible answers is $ x=1, k=3 $ . Then $ 1 \cdot 1 + 2 \cdot 1 + 4 \cdot       1 $ equals $ n=7 $ .

In the fourth test case of the example, one of the possible answers is $ x=7, k=2 $ . Then $ 1 \cdot 7 + 2 \cdot 7 $ equals $ n=21 $ .

In the fifth test case of the example, one of the possible answers is $ x=4, k=3 $ . Then $ 1 \cdot 4 + 2 \cdot 4 + 4 \cdot       4 $ equals $ n=28 $ .

## 样例 #1

### 输入

```
7
3
6
7
21
28
999999999
999999984```

### 输出

```
1
2
1
7
4
333333333
333333328```

# AI分析结果

### 题目内容
# 糖果

## 题目描述
最近沃娃发现了\(n\)个糖果包装纸。他记得第一天买了\(x\)颗糖果，第二天买了\(2x\)颗糖果，第三天买了\(4x\)颗糖果，\(\cdots\)，第\(k\)天买了\(2^{k - 1}x\)颗糖果。但有个问题：沃娃既不记得\(x\)也不记得\(k\)，但他确定\(x\)和\(k\)是正整数且\(k > 1\)。

如果你能告诉沃娃任意一个正整数\(x\)，使得存在整数\(k > 1\)，满足\(x + 2x + 4x + \cdots + 2^{k - 1}x = n\)，他就会满意。保证至少存在一个解。注意\(k > 1\)。

你必须回答\(t\)个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，一个可能的答案是\(x = 1\)，\(k = 2\)。那么\(1×1 + 2×1\)等于\(n = 3\)。

在示例的第二个测试用例中，一个可能的答案是\(x = 2\)，\(k = 2\)。那么\(1×2 + 2×2\)等于\(n = 6\)。

在示例的第三个测试用例中，一个可能的答案是\(x = 1\)，\(k = 3\)。那么\(1×1 + 2×1 + 4×1\)等于\(n = 7\)。

在示例的第四个测试用例中，一个可能的答案是\(x = 7\)，\(k = 2\)。那么\(1×7 + 2×7\)等于\(n = 21\)。

在示例的第五个测试用例中，一个可能的答案是\(x = 4\)，\(k = 3\)。那么\(1×4 + 2×4 + 4×4\)等于\(n = 28\)。

## 样例 #1
### 输入
```
7
3
6
7
21
28
999999999
999999984
```
### 输出
```
1
2
1
7
4
333333333
333333328
```

### 算法分类
数学

### 题解综合分析与结论
所有题解都基于将\(x + 2x + 4x + \cdots + 2^{k - 1}x\)化简为\(x(2^k - 1)\)这一数学推导，从而将问题转化为寻找满足\(n\)能被\(2^k - 1\)整除的\(x = n / (2^k - 1)\)。不同点在于实现方式：
 - **PersistentLife**：通过快速幂计算\(2^k - 1\)，然后枚举\(k\)来找到满足条件的\(x\)。
 - **andyli**：枚举\(n\)的因数\(m\)，并通过两种方式判断是否存在正整数\(k\)使得\(\frac{n}{m} = 2^k - 1\)，一种是\(O(1)\)的位运算判断，一种是\(O(\log n)\)的枚举判断。
 - **do_while_true**：思路和PersistentLife类似，直接枚举\(k\)看\(n\)能否整除\(2^k - 1\) 。
 - **Sora1336**：打表列出所有可能的\(2^k - 1\)值，再尝试能否被\(x\)整除。
 - **神眷之樱花**：通过等比数列求和公式或错位相减法化简式子，预处理\(2^k - 1\)的值，判断能否整除。

### 通用建议与扩展思路
通用思路是利用数学性质将原式化简，再通过枚举等方式找到满足条件的解。扩展思路上，可以考虑优化枚举过程，比如利用数论知识进一步缩小枚举范围。对于同类型题，通常是围绕等比数列求和以及数的整除关系进行变形，解题关键在于准确化简式子并合理利用数学性质。

### 洛谷题目推荐
 - [P1939 【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)：涉及等比数列相关的递推关系，通过矩阵加速优化计算。
 - [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：需要对给定数据进行分析和组合判断，与本题分析数的关系有相似之处。
 - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考查数论中同余方程的求解，和本题利用数的整除关系解题类似。 

---
处理用时：43.17秒