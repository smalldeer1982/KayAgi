# 题目信息

# Array Balancing

## 题目描述

You are given two arrays of length $ n $ : $ a_1, a_2, \dots, a_n $ and $ b_1, b_2, \dots, b_n $ .

You can perform the following operation any number of times:

1. Choose integer index $ i $ ( $ 1 \le i \le n $ );
2. Swap $ a_i $ and $ b_i $ .

What is the minimum possible sum $ |a_1 - a_2| + |a_2 - a_3| + \dots + |a_{n-1} - a_n| $ $ + $ $ |b_1 - b_2| + |b_2 - b_3| + \dots + |b_{n-1} - b_n| $ (in other words, $ \sum\limits_{i=1}^{n - 1}{\left(|a_i - a_{i+1}| + |b_i - b_{i+1}|\right)} $ ) you can achieve after performing several (possibly, zero) operations?

## 说明/提示

In the first test case, we can, for example, swap $ a_3 $ with $ b_3 $ and $ a_4 $ with $ b_4 $ . We'll get arrays $ a = [3, 3, 3, 3] $ and $ b = [10, 10, 10, 10] $ with sum $ 3 \cdot |3 - 3| + 3 \cdot |10 - 10| = 0 $ .

In the second test case, arrays already have minimum sum (described above) equal to $ |1 - 2| + \dots + |4 - 5| + |6 - 7| + \dots + |9 - 10| $ $ = 4 + 4 = 8 $ .

In the third test case, we can, for example, swap $ a_5 $ and $ b_5 $ .

## 样例 #1

### 输入

```
3
4
3 3 10 10
10 10 3 3
5
1 2 3 4 5
6 7 8 9 10
6
72 101 108 108 111 44
10 87 111 114 108 100```

### 输出

```
0
8
218```

# AI分析结果

### 题目内容
# 数组平衡

## 题目描述
给定两个长度为 $n$ 的数组：$a_1, a_2, \dots, a_n$ 和 $b_1, b_2, \dots, b_n$ 。
你可以执行以下操作任意次数：
1. 选择整数索引 $i$（$1 \le i \le n$）；
2. 交换 $a_i$ 和 $b_i$ 。
在执行若干次（可能为零次）操作后，$|a_1 - a_2| + |a_2 - a_3| + \dots + |a_{n - 1} - a_n| + |b_1 - b_2| + |b_2 - b_3| + \dots + |b_{n - 1} - b_n|$（换句话说，$\sum\limits_{i = 1}^{n - 1}{\left(|a_i - a_{i + 1}| + |b_i - b_{i + 1}|\right)}$）的最小可能值是多少？

## 说明/提示
在第一个测试用例中，例如，我们可以交换 $a_3$ 和 $b_3$ 以及 $a_4$ 和 $b_4$ 。我们将得到数组 $a = [3, 3, 3, 3]$ 和 $b = [10, 10, 10, 10]$，其和为 $3 \cdot |3 - 3| + 3 \cdot |10 - 10| = 0$ 。
在第二个测试用例中，数组已经具有上述最小和，等于 $|1 - 2| + \dots + |4 - 5| + |6 - 7| + \dots + |9 - 10| = 4 + 4 = 8$ 。
在第三个测试用例中，例如，我们可以交换 $a_5$ 和 $b_5$ 。

## 样例 #1
### 输入
```
3
4
3 3 10 10
10 10 3 3
5
1 2 3 4 5
6 7 8 9 10
6
72 101 108 108 111 44
10 87 111 114 108 100
```
### 输出
```
0
8
218
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要分为贪心和动态规划两种思路。贪心思路的题解认为，对于每一对相邻元素 $i$ 和 $i + 1$，交换操作只影响当前这对元素的计算结果，存在 $|a_i - a_{i + 1}| + |b_i - b_{i + 1}|$ 和 $|a_i - b_{i + 1}| + |b_i - a_{i + 1}|$ 两种情况，取最小值即可，且每个局部最优解不会影响其他局部最优解，可直接求和。动态规划思路的题解定义状态 $f_{i, j}$ 表示 $a$ 数组和 $b$ 数组前 $i$ 个这样的和，$j$ 代表是否交换 $a_i$ 和 $b_i$，通过状态转移方程计算最终结果。贪心思路相对更简洁直观，动态规划思路理论上更具通用性，但实现相对复杂。

### 所选的题解
 - **作者：_Kouki_**（5星）
    - **关键亮点**：思路清晰简洁，直接指出交换操作产生的两种情况并取最小，代码注释详细。
    - **重点代码**：
```cpp
for(int i = 1; i < n; ++i){//循环
    ans += min(abs(a[i] - a[i + 1]) + abs(b[i] - b[i + 1]), abs(a[i] - b[i + 1]) + abs(b[i] - a[i + 1]));
    /*
    * 就是我在上面讲的公式
    * 对他们取min 
    */
}
```
核心实现思想：遍历数组，对每一对相邻元素的两种可能情况取最小值并累加到结果中。

 - **作者：LYqwq**（5星）
    - **关键亮点**：对贪心思路解释清晰，通过比较相邻两项两种组合方式的大小，若后者小则交换，最后统计答案。
    - **重点代码**：
```cpp
for(int i = 1; i < n; i++){
    if(abs(a[i] - a[i + 1]) + abs(b[i] - b[i + 1]) > abs(a[i] - b[i + 1]) + abs(b[i] - a[i + 1])){
        swap(a[i + 1], b[i + 1]); // 交换
    }
}
for(int i = 1; i < n; i++){
    ans += abs(a[i] - a[i + 1]) + abs(b[i] - b[i + 1]);
}
```
核心实现思想：先遍历数组比较并交换使每对相邻元素最优，再遍历统计最终答案。

 - **作者：Exber**（4星）
    - **关键亮点**：明确指出题面可转换为求 $\sum\limits_{i = 2}^{n}|a_i - a_{i - 1}| + |b_i - b_{i - 1}|$ 的最小值，且位置 $i$ 的交换操作对后续序列无影响，进而采用贪心策略。
    - **重点代码**：
```cpp
for(int i = 2; i <= n; i++){
    if(abs(b[i] - a[i - 1]) + abs(a[i] - b[i - 1]) < abs(a[i] - a[i - 1]) + abs(b[i] - b[i - 1])){
        swap(a[i], b[i]);
    }
}
long long ans = 0;
for(int i = 1; i < n; i++){
    ans += abs(a[i] - a[i + 1]) + abs(b[i] - b[i + 1]);
}
```
核心实现思想：按顺序枚举每个位置，比较交换前后的大小决定是否交换，最后累加相邻元素差值绝对值之和。

### 最优关键思路或技巧
贪心策略，即局部最优解可构成全局最优解。通过分析发现交换操作只影响相邻元素计算结果，且存在两种固定组合形式，对每对相邻元素的两种组合取最小值，直接累加得到全局最优解。

### 拓展
同类型题常围绕数组元素操作与特定目标值优化，类似套路是分析操作对局部和整体的影响，判断是否能用贪心策略。若不能，再考虑动态规划等其他方法。

### 洛谷相似题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：50.82秒