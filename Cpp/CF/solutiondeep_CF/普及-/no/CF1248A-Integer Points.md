# 题目信息

# Integer Points

## 题目描述

DLS and JLS are bored with a Math lesson. In order to entertain themselves, DLS took a sheet of paper and drew $ n $ distinct lines, given by equations $ y = x + p_i $ for some distinct $ p_1, p_2, \ldots, p_n $ .

Then JLS drew on the same paper sheet $ m $ distinct lines given by equations $ y = -x + q_i $ for some distinct $ q_1, q_2, \ldots, q_m $ .

DLS and JLS are interested in counting how many line pairs have integer intersection points, i.e. points with both coordinates that are integers. Unfortunately, the lesson will end up soon, so DLS and JLS are asking for your help.

## 说明/提示

The picture shows the lines from the first test case of the example. Black circles denote intersection points with integer coordinates.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248A/8a7326901424797e600db27d56ff13441fc9fe8a.png)

## 样例 #1

### 输入

```
3
3
1 3 2
2
0 3
1
1
1
1
1
2
1
1
```

### 输出

```
3
1
0
```

# AI分析结果

### 题目内容
# 整数点

## 题目描述
DLS和JLS在上数学课的时候觉得很无聊。为了找点乐子，DLS拿了一张纸，画了 $n$ 条不同的直线，其方程为 $y = x + p_i$，其中 $p_1, p_2, \ldots, p_n$ 各不相同。

然后JLS在同一张纸上画了 $m$ 条不同的直线，其方程为 $y = -x + q_i$，其中 $q_1, q_2, \ldots, q_m$ 各不相同。

DLS和JLS想知道有多少对直线的交点是整数点，即坐标 $(x, y)$ 均为整数的点。不幸的是，课很快就要结束了，所以DLS和JLS向你求助。

## 说明/提示
此图展示了示例中第一个测试用例的直线。黑色圆圈表示坐标为整数的交点。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248A/8a7326901424797e600db27d56ff13441fc9fe8a.png)

## 样例 #1
### 输入
```
3
3
1 3 2
2
0 3
1
1
1
1
1
2
1
1
```
### 输出
```
3
1
0
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过联立直线方程 $y = x + p_i$ 和 $y = -x + q_j$，得到 $2x = q_j - p_i$，进而得出当 $q_j - p_i$ 能被2整除时，交点为整数点。基于此，利用奇数相加减、偶数相加减结果为偶数的性质，通过统计 $p_i$ 和 $q_j$ 序列中奇数和偶数的个数，根据计数原理计算满足条件的交点对数。各题解的主要差异在于代码实现细节，如变量命名、输入输出方式、统计奇数偶数个数的具体写法等。整体来看，思路较为直接，实现难度不大。

### 通用建议与扩展思路
对于此类问题，关键在于通过数学推导找出满足条件的判定依据，再利用计数原理简化计算。可以进一步拓展到更复杂的直线方程组合，或在更高维度空间中考虑类似的整数点问题。同时，在实现代码时，要注意变量类型的选择，避免因数据范围问题导致错误。

### 相似知识点洛谷题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：通过枚举和数学判断解决数字组合问题，与本题利用数学性质解决问题的思路类似。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：同样需要通过数学推导找到解题思路，利用等差数列求和公式等知识解决问题。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：虽然看似是贪心问题，但也涉及到一定的数学计算，通过计算不同购买方案的花费来得出最优解。

### 个人心得摘录与总结
多位作者提到不开 `long long` 会导致错误，强调了在处理数据时要注意数据类型和数据范围，避免因数据溢出等问题导致程序出错。 

---
处理用时：47.73秒