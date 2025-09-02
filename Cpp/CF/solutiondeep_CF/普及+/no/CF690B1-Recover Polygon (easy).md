# 题目信息

# Recover Polygon (easy)

## 题目描述

The zombies are gathering in their secret lair! Heidi will strike hard to destroy them once and for all. But there is a little problem... Before she can strike, she needs to know where the lair is. And the intel she has is not very good.

Heidi knows that the lair can be represented as a rectangle on a lattice, with sides parallel to the axes. Each vertex of the polygon occupies an integer point on the lattice. For each cell of the lattice, Heidi can check the level of Zombie Contamination. This level is an integer between $ 0 $ and $ 4 $ , equal to the number of corners of the cell that are inside or on the border of the rectangle.

As a test, Heidi wants to check that her Zombie Contamination level checker works. Given the output of the checker, Heidi wants to know whether it could have been produced by a single non-zero area rectangular-shaped lair (with axis-parallel sides). ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690B1/6a1d528b09269e46ea8342fade1ffbca11000e9c.png)

## 说明/提示

The lair, if it exists, has to be rectangular (that is, have corners at some grid points with coordinates $ (x_{1},y_{1}) $ , $ (x_{1},y_{2}) $ , $ (x_{2},y_{1}) $ , $ (x_{2},y_{2}) $ ), has a non-zero area and be contained inside of the grid (that is, $ 0<=x_{1}<x_{2}<=N $ , $ 0<=y_{1}<y_{2}<=N $ ), and result in the levels of Zombie Contamination as reported in the input.

## 样例 #1

### 输入

```
6
000000
000000
012100
024200
012100
000000
```

### 输出

```
Yes
```

# AI分析结果

### 题目内容
# 恢复多边形（简单）

## 题目描述
僵尸们正在它们的秘密巢穴聚集！海蒂将给予沉重打击，一举消灭它们。但有个小问题……在她发动攻击之前，她需要知道巢穴在哪里。而她所掌握的情报并不太准确。

海蒂知道，巢穴可以在网格上表示为一个矩形，其边与坐标轴平行。多边形的每个顶点都位于网格上的一个整数点。对于网格的每个单元格，海蒂可以检测僵尸污染程度。这个程度是一个介于0和4之间的整数，等于该单元格在矩形内部或边界上的角的数量。

作为一次测试，海蒂想检查她的僵尸污染程度检测器是否有效。给定检测器的输出，海蒂想知道它是否可能是由一个非零面积的矩形巢穴（边与坐标轴平行）产生的。![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690B1/6a1d528b09269e46ea8342fade1ffbca11000e9c.png)

## 说明/提示
如果存在巢穴，它必须是矩形（即角位于某些网格点，坐标为$(x_{1},y_{1})$，$(x_{1},y_{2})$，$(x_{2},y_{1})$，$(x_{2},y_{2})$），具有非零面积，并且包含在网格内（即$0<=x_{1}<x_{2}<=N$，$0<=y_{1}<y_{2}<=N$），并产生输入中报告的僵尸污染程度。

## 样例 #1
### 输入
```
6
000000
000000
012100
024200
012100
000000
```
### 输出
```
Yes
```

### 算法分类
模拟

### 综合分析与结论
所有题解思路基本一致，均利用题目数据范围小（$n \leq 50$）的特点，采用暴力模拟的方法解决问题。核心思路是遍历二维数组中的每个元素，对于值不为0的元素，统计其四个角上非零元素的个数，并与该元素的值进行比较。若所有元素都满足此条件，则输出“Yes”，否则输出“No”。部分题解使用方向数组简化代码实现，在判断角上元素时更加简洁。在实现细节上，有的题解用字符读入再转换为数字，有的直接用数字读入；有的通过continue跳过值为0的元素，有的则先判断值是否为0再进行后续操作。整体来看，这些题解质量较为接近，均围绕暴力模拟这一核心思路展开。

### 通用建议与扩展思路
- 建议在实现时合理使用方向数组，简化代码逻辑，提高代码可读性。同时注意边界条件的处理，避免数组越界。
- 类似题目通常给定特定条件下的二维数组，要求判断数组是否满足某种规则或性质。可拓展思路为处理更复杂的形状判断，如判断是否为平行四边形、梯形等，此时可能需要更复杂的条件判断和几何知识；或者增加数据规模，考虑优化算法以降低时间复杂度。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合的方式解决问题，与本题暴力遍历判断的思路类似。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：对每个灯进行状态模拟，与本题对二维数组每个元素进行判断有相似之处。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过枚举不同购买方案进行比较，和本题暴力模拟的思想一致。 

---
处理用时：44.52秒