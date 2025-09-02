# 题目信息

# Alyona and mex

## 题目描述

Alyona's mother wants to present an array of $ n $ non-negative integers to Alyona. The array should be special.

Alyona is a capricious girl so after she gets the array, she inspects $ m $ of its subarrays. Subarray is a set of some subsequent elements of the array. The $ i $ -th subarray is described with two integers $ l_{i} $ and $ r_{i} $ , and its elements are $ a[l_{i}],a[l_{i}+1],...,a[r_{i}] $ .

Alyona is going to find mex for each of the chosen subarrays. Among these $ m $ mexes the girl is going to find the smallest. She wants this minimum mex to be as large as possible.

You are to find an array $ a $ of $ n $ elements so that the minimum mex among those chosen by Alyona subarrays is as large as possible.

The mex of a set $ S $ is a minimum possible non-negative integer that is not in $ S $ .

## 说明/提示

The first example: the mex of the subarray $ (1,3) $ is equal to $ 3 $ , the mex of the subarray $ (2,5) $ is equal to $ 3 $ , the mex of the subarray $ (4,5) $ is equal to $ 2 $ as well, thus the minumal mex among the subarrays chosen by Alyona is equal to $ 2 $ .

## 样例 #1

### 输入

```
5 3
1 3
2 5
4 5
```

### 输出

```
2
1 0 2 1 0
```

## 样例 #2

### 输入

```
4 2
1 4
2 4
```

### 输出

```
3
5 2 0 1```

# AI分析结果

### 题目内容
# 阿廖娜和mex

## 题目描述
阿廖娜的母亲想送给阿廖娜一个由n个非负整数组成的数组。这个数组应该很特别。

阿廖娜是个任性的女孩，所以在她得到数组后，她会检查其中m个子数组。子数组是数组中一些连续元素的集合。第i个子数组由两个整数$l_i$和$r_i$描述，其元素为$a[l_i],a[l_i + 1],...,a[r_i]$ 。

阿廖娜要为每个选定的子数组找到mex值。在这m个mex值中，女孩要找到最小的那个。她希望这个最小的mex值尽可能大。

你需要找到一个由n个元素组成的数组a，使得阿廖娜所选子数组中的最小mex值尽可能大。

集合S的mex值是指不在S中的最小非负整数。

## 说明/提示
第一个例子：子数组(1, 3)的mex值等于3，子数组(2, 5)的mex值等于3，子数组(4, 5)的mex值也等于2，因此阿廖娜所选子数组中的最小mex值等于2。

## 样例 #1
### 输入
```
5 3
1 3
2 5
4 5
```
### 输出
```
2
1 0 2 1 0
```

## 样例 #2
### 输入
```
4 2
1 4
2 4
```
### 输出
```
3
5 2 0 1
```
• **算法分类**：构造
• **综合分析与结论**：这些题解思路基本一致，都基于一个关键结论，即一个区间$[l,r]$的最大$mex$值为区间长度$r - l + 1$ ，所以所有区间$mex$最小值的最大值就是所有区间长度的最小值。构造序列时，循环输出$0$到该最小值减$1$ ，可保证每个区间都包含$[0, r - l]$ ，从而使$mex$达到最大。各题解在代码实现上略有差异，如输入输出方式、变量命名等，但核心思路相同。
• **通用建议与扩展思路**：此类构造题关键在于找到关键结论，明确如何构造能满足题目要求。对于类似题目，可先分析所求值与给定条件（如区间长度）的关系，再思考如何通过构造数据满足条件。同类型题常涉及对特定性质（如本题$mex$定义）的深入理解和运用，通过分析性质来确定构造方向。
• **洛谷相似题目**：
  - P1102 A-B 数对，通过构造合适的算法利用数组特性解题。
  - P1036 选数，结合数论知识构造方案满足条件。
  - P1433 吃奶酪，构造路径方案解决旅行商问题变体。 

---
处理用时：31.49秒