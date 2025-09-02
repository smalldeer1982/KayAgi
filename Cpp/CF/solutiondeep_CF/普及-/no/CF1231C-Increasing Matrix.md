# 题目信息

# Increasing Matrix

## 题目描述

In this problem, a $ n \times m $ rectangular matrix $ a $ is called increasing if, for each row of $ i $ , when go from left to right, the values strictly increase (that is, $ a_{i,1}<a_{i,2}<\dots<a_{i,m} $ ) and for each column $ j $ , when go from top to bottom, the values strictly increase (that is, $ a_{1,j}<a_{2,j}<\dots<a_{n,j} $ ).

In a given matrix of non-negative integers, it is necessary to replace each value of $ 0 $ with some positive integer so that the resulting matrix is increasing and the sum of its elements is maximum, or find that it is impossible.

It is guaranteed that in a given value matrix all values of $ 0 $ are contained only in internal cells (that is, not in the first or last row and not in the first or last column).

## 说明/提示

In the first example, the resulting matrix is as follows:

```
<pre class="verbatim"><br></br>1 3 5 6 7<br></br>3 6 7 8 9<br></br>5 7 8 9 10<br></br>8 9 10 11 12<br></br>
```

In the second example, the value $ 3 $ must be put in the middle cell.

In the third example, the desired resultant matrix does not exist.

## 样例 #1

### 输入

```
4 5
1 3 5 6 7
3 0 7 0 9
5 0 0 0 10
8 9 10 11 12
```

### 输出

```
144
```

## 样例 #2

### 输入

```
3 3
1 2 3
2 0 4
4 5 6
```

### 输出

```
30
```

## 样例 #3

### 输入

```
3 3
1 2 3
3 0 4
4 5 6
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 3
1 2 3
2 3 4
3 4 2
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 递增矩阵

## 题目描述
在本题中，一个 \(n \times m\) 的矩形矩阵 \(a\) 被称为递增矩阵，当且仅当对于每一行 \(i\)，从左到右，矩阵元素严格递增（即 \(a_{i,1}<a_{i,2}<\dots<a_{i,m}\) ），并且对于每一列 \(j\)，从上到下，矩阵元素也严格递增（即 \(a_{1,j}<a_{2,j}<\dots<a_{n,j}\) ）。

给定一个非负整数矩阵，需要将其中每个值为 \(0\) 的元素替换为某个正整数，使得得到的矩阵是递增的，并且其元素之和最大，或者判断这是否不可能实现。

保证在给定的矩阵中，所有值为 \(0\) 的元素仅包含在内部单元格中（即不在第一行或最后一行，也不在第一列或最后一列）。

## 说明/提示
在第一个示例中，得到的矩阵如下：
```
1 3 5 6 7
3 6 7 8 9
5 7 8 9 10
8 9 10 11 12
```

在第二个示例中，中间单元格必须填入值 \(3\)。

在第三个示例中，不存在所需的结果矩阵。

## 样例 #1
### 输入
```
4 5
1 3 5 6 7
3 0 7 0 9
5 0 0 0 10
8 9 10 11 12
```
### 输出
```
144
```

## 样例 #2
### 输入
```
3 3
1 2 3
2 0 4
4 5 6
```
### 输出
```
30
```

## 样例 #3
### 输入
```
3 3
1 2 3
3 0 4
4 5 6
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
3 3
1 2 3
2 3 4
3 4 2
```
### 输出
```
-1
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路基本一致，均利用贪心思想。核心思路是对于值为 \(0\) 的元素，为使其所在行和列都递增且总和最大，将其赋值为右侧和下侧元素中的最小值减 \(1\) 。解决难点在于遍历顺序，若从左上角开始遍历，可能出现右侧或下侧元素仍为 \(0\) 的情况，导致赋值错误，所以需从右下角开始遍历。最后再检查生成的矩阵是否满足递增条件，若满足则输出元素总和，不满足则输出 \(-1\) 。

### 通用建议与扩展思路
解决此类问题，关键在于理解贪心策略的应用场景，即每一步决策都追求局部最优以达到全局最优。在实现过程中，要注意边界条件和遍历顺序对结果的影响。同类型题目通常围绕在满足特定条件下对矩阵或序列进行元素填充、修改等操作以实现最值，类似算法套路为利用条件确定每个位置的最优取值策略。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
3. [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937) 

---
处理用时：36.94秒