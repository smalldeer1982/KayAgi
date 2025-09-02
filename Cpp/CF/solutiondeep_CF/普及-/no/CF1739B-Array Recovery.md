# 题目信息

# Array Recovery

## 题目描述

For an array of non-negative integers $ a $ of size $ n $ , we construct another array $ d $ as follows: $ d_1 = a_1 $ , $ d_i = |a_i - a_{i - 1}| $ for $ 2 \le i \le n $ .

Your task is to restore the array $ a $ from a given array $ d $ , or to report that there are multiple possible arrays.

## 说明/提示

In the second example, there are two suitable arrays: $ [2, 8, 5] $ and $ [2, 8, 11] $ .

## 样例 #1

### 输入

```
3
4
1 0 2 5
3
2 6 3
5
0 0 0 0 0```

### 输出

```
1 1 3 8
-1
0 0 0 0 0```

# AI分析结果

### 题目内容
# 数组恢复

## 题目描述
对于一个大小为 $n$ 的非负整数数组 $a$，我们按如下方式构造另一个数组 $d$：$d_1 = a_1$，对于 $2 \leq i \leq n$，$d_i = |a_i - a_{i - 1}|$。

你的任务是从给定的数组 $d$ 中恢复出数组 $a$，或者报告存在多种可能的数组。

## 说明/提示
在第二个样例中，有两个合适的数组：$[2, 8, 5]$ 和 $[2, 8, 11]$。

## 样例 #1
### 输入
```
3
4
1 0 2 5
3
2 6 3
5
0 0 0 0 0
```
### 输出
```
1 1 3 8
-1
0 0 0 0 0
```
### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是围绕由 $d_i = |a_i - a_{i - 1}|$ 推导出的 $a_i = a_{i - 1} + d_i$ 或 $a_i = a_{i - 1} - d_i$ 这两个式子展开。由于数组 $a$ 是非负整数数组，所以关键在于判断每个 $a_i$ 是否有唯一解。若对于某个 $i$，$a_{i - 1} - d_i \geq 0$ 且 $d_i \neq 0$，则说明 $a_i$ 有两种取值可能，数组 $a$ 不唯一，输出 $-1$；否则，将 $a_{i - 1} + d_i$ 作为 $a_i$ 的值。各题解在具体实现上略有差异，但整体思路一致。

### 通用建议与扩展思路
通用建议：在处理这类问题时，要紧扣题目给出的条件，尤其是数组元素非负这一关键条件。在代码实现上，注意边界条件的处理和变量的初始化。
扩展思路：同类型题目可能会改变数组元素的取值范围，或者改变构造数组 $d$ 的规则，例如 $d_i$ 为 $a_i$ 和 $a_{i - 1}$ 的其他函数关系。类似算法套路是根据给定的关系，分析出可能存在多种解的情况，并通过代码实现判断。

### 洛谷相似题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046) 

---
处理用时：19.48秒