# 题目信息

# Hemose Shopping

## 题目描述

Hemose was shopping with his friends Samez, AhmedZ, AshrafEzz, TheSawan and O\_E in Germany. As you know, Hemose and his friends are problem solvers, so they are very clever. Therefore, they will go to all discount markets in Germany.

Hemose has an array of $ n $ integers. He wants Samez to sort the array in the non-decreasing order. Since it would be a too easy problem for Samez, Hemose allows Samez to use only the following operation:

- Choose indices $ i $ and $ j $ such that $ 1 \le i, j \le n $ , and $ \lvert i - j \rvert \geq x $ . Then, swap elements $ a_i $ and $ a_j $ .

Can you tell Samez if there's a way to sort the array in the non-decreasing order by using the operation written above some finite number of times (possibly $ 0 $ )?

## 说明/提示

In the first test case, you can't do any operations.

In the second test case, the array is already sorted.

In the third test case, you can do the operations as follows:

- $ [5,1,2,3,4] $ , $ swap(a_1,a_3) $
- $ [2,1,5,3,4] $ , $ swap(a_2,a_5) $
- $ [2,4,5,3,1] $ , $ swap(a_2,a_4) $
- $ [2,3,5,4,1] $ , $ swap(a_1,a_5) $
- $ [1,3,5,4,2] $ , $ swap(a_2,a_5) $
- $ [1,2,5,4,3] $ , $ swap(a_3,a_5) $
- $ [1,2,3,4,5] $

(Here $ swap(a_i, a_j) $ refers to swapping elements at positions $ i $ , $ j $ ).

## 样例 #1

### 输入

```
4
3 3
3 2 1
4 3
1 2 3 4
5 2
5 1 2 3 4
5 4
1 2 3 4 4```

### 输出

```
NO
YES
YES
YES```

# AI分析结果

### 题目内容
# Hemose购物

## 题目描述
Hemose和他的朋友Samez、AhmedZ、AshrafEzz、TheSawan以及O\_E在德国购物。如你所知，Hemose和他的朋友们都是解题高手，所以他们非常聪明。因此，他们会去德国所有的折扣市场。

Hemose有一个包含\(n\)个整数的数组。他希望Samez将数组按非递减顺序排序。由于这对Samez来说是一个太简单的问题，Hemose只允许Samez使用以下操作：
- 选择索引\(i\)和\(j\)，使得\(1 \leq i, j \leq n\)，且\(\lvert i - j \rvert \geq x\)。然后，交换元素\(a_i\)和\(a_j\)。

你能告诉Samez是否有一种方法，通过有限次（可能为\(0\)次）使用上述操作将数组按非递减顺序排序吗？

## 说明/提示
在第一个测试用例中，你不能进行任何操作。

在第二个测试用例中，数组已经排序。

在第三个测试用例中，你可以按如下方式进行操作：
- \([5,1,2,3,4]\)，\(swap(a_1,a_3)\)
- \([2,1,5,3,4]\)，\(swap(a_2,a_5)\)
- \([2,4,5,3,1]\)，\(swap(a_2,a_4)\)
- \([2,3,5,4,1]\)，\(swap(a_1,a_5)\)
- \([1,3,5,4,2]\)，\(swap(a_2,a_5)\)
- \([1,2,5,4,3]\)，\(swap(a_3,a_5)\)
- \([1,2,3,4,5]\)

（这里\(swap(a_i, a_j)\)指交换位置\(i\)和\(j\)处的元素）。

## 样例 #1
### 输入
```
4
3 3
3 2 1
4 3
1 2 3 4
5 2
5 1 2 3 4
5 4
1 2 3 4 4
```
### 输出
```
NO
YES
YES
YES
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是基于对\(x\)与\(n\)关系的分析。当\(2x \leq n\)时，数组可任意交换从而一定能排序；当\(2x > n\)时，中间\([n - x + 1, x]\)区间的元素相对位置无法改变，需判断该区间元素在原数组和排序后数组中的位置是否一致。各题解在表述和实现细节上略有差异，但整体思路相近。

### 通用建议与扩展思路
对于此类问题，关键在于分析操作的限制条件对数组元素交换的影响。可以进一步思考如果操作条件改变，如交换距离的限制更为复杂，或者对数组排序的要求变为特定的模式排序，应如何解决。还可以拓展到多维数组的类似交换排序问题。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：27.79秒