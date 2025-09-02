# 题目信息

# Reverse

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ of length $ n $ . You have to choose two integers $ l,r $ ( $ 1 \le l \le r \le n $ ) and reverse the subsegment $ [l,r] $ of the permutation. The permutation will become $ p_1,p_2, \dots, p_{l-1},p_r,p_{r-1}, \dots, p_l,p_{r+1},p_{r+2}, \dots ,p_n $ .

Find the lexicographically smallest permutation that can be obtained by performing exactly one reverse operation on the initial permutation.

Note that for two distinct permutations of equal length $ a $ and $ b $ , $ a $ is lexicographically smaller than $ b $ if at the first position they differ, $ a $ has the smaller element.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation has length $ 1 $ , so the only possible segment is $ [1,1] $ . The resulting permutation is $ [1] $ .

In the second test case, we can obtain the identity permutation by reversing the segment $ [1,2] $ . The resulting permutation is $ [1,2,3] $ .

In the third test case, the best possible segment is $ [2,3] $ . The resulting permutation is $ [1,2,4,3] $ .

In the fourth test case, there is no lexicographically smaller permutation, so we can leave it unchanged by choosing the segment $ [1,1] $ . The resulting permutation is $ [1,2,3,4,5] $ .

## 样例 #1

### 输入

```
4
1
1
3
2 1 3
4
1 4 2 3
5
1 2 3 4 5```

### 输出

```
1 
1 2 3 
1 2 4 3 
1 2 3 4 5```

# AI分析结果

### 题目内容
# Reverse

## 题目描述
给定一个长度为n的排列$p_1, p_2, \ldots, p_n$。你必须选择两个整数$l$和$r$（$1 \leq l \leq r \leq n$），并反转排列中的子段$[l,r]$。排列将变为$p_1,p_2, \dots, p_{l - 1},p_r,p_{r - 1}, \dots, p_l,p_{r + 1},p_{r + 2}, \dots,p_n$。

找出通过对初始排列恰好执行一次反转操作可以得到的字典序最小的排列。

注意，对于两个长度相等的不同排列$a$和$b$，如果在它们第一个不同的位置上，$a$的元素较小，那么$a$在字典序上小于$b$。

排列是一个由从1到n的n个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$是一个排列，但$[1,2,2]$不是排列（数组中2出现了两次），$[1,3,4]$也不是排列（$n = 3$但数组中有4）。

## 说明/提示
在第一个测试用例中，排列的长度为1，所以唯一可能的子段是$[1,1]$。得到的排列是$[1]$。

在第二个测试用例中，我们可以通过反转子段$[1,2]$得到单位排列。得到的排列是$[1,2,3]$。

在第三个测试用例中，最佳的子段是$[2,3]$。得到的排列是$[1,2,4,3]$。

在第四个测试用例中，没有字典序更小的排列，所以我们可以选择子段$[1,1]$保持其不变。得到的排列是$[1,2,3,4,5]$。

## 样例 #1
### 输入
```
4
1
1
3
2 1 3
4
1 4 2 3
5
1 2 3 4 5
```
### 输出
```
1 
1 2 3 
1 2 4 3 
1 2 3 4 5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为统一，均采用贪心策略。要点在于从前往后遍历排列，找到第一个$p_i \neq i$的位置$i$，再找到数字$i$所在位置$j$，将区间$[i,j]$进行反转，就能得到字典序最小的排列。证明该贪心策略的正确性是解题难点，部分题解通过分析不同策略下对字典序的影响来证明，如不将位置$i$作为子序列开头或不将数$i$所在位置$j$作为子序列结尾，得到的字典序都不如按此贪心策略操作后的字典序小。各题解在代码实现上，有的直接暴力查找并翻转，有的通过预处理记录数字位置来优化查找过程，但本质思路一致。

### 通用建议与扩展思路
对于此类贪心问题，关键在于证明贪心策略的正确性。在实现时，可以考虑通过预处理数据来优化查找等操作。同类型题通常围绕贪心策略的应用，比如在一些序列操作中，通过局部最优选择达到全局最优，类似的还有区间调度、背包等问题变种。
### 相似知识点题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) 

---
处理用时：24.28秒