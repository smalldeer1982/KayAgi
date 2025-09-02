# 题目信息

# Pythagorean Theorem II

## 题目描述

In mathematics, the Pythagorean theorem — is a relation in Euclidean geometry among the three sides of a right-angled triangle. In terms of areas, it states:

 In any right-angled triangle, the area of the square whose side is the hypotenuse (the side opposite the right angle) is equal to the sum of the areas of the squares whose sides are the two legs (the two sides that meet at a right angle).

The theorem can be written as an equation relating the lengths of the sides $ a $ , $ b $ and $ c $ , often called the Pythagorean equation:

 $ a^{2}+b^{2}=c^{2} $ where $ c $ represents the length of the hypotenuse, and $ a $ and $ b $ represent the lengths of the other two sides.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF304A/dce71d69bec644282a576a6a33bfe17bb5e666a5.png)Given $ n $ , your task is to count how many right-angled triangles with side-lengths $ a $ , $ b $ and $ c $ that satisfied an inequality $ 1<=a<=b<=c<=n $ .

## 样例 #1

### 输入

```
5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
74
```

### 输出

```
35
```

# AI分析结果

### 题目内容
# 勾股定理II

## 题目描述
在数学中，勾股定理是欧几里得几何中直角三角形三边之间的一种关系。从面积角度表述为：在任意直角三角形中，以斜边（直角所对的边）为边长的正方形面积，等于以两条直角边（构成直角的两条边）为边长的两个正方形面积之和。该定理可以写成一个关于边长\(a\)、\(b\)和\(c\)的等式，通常称为勾股方程：\(a^{2}+b^{2}=c^{2}\)，其中\(c\)表示斜边的长度，\(a\)和\(b\)表示另外两条边的长度。

给定\(n\)，你的任务是统计满足不等式\(1\leq a\leq b\leq c\leq n\)的直角三角形\((a,b,c)\)的数量。

## 样例 #1
### 输入
```
5
```
### 输出
```
1
```

## 样例 #2
### 输入
```
74
```
### 输出
```
35
```

### 算法分类
数学（枚举）

### 综合分析与结论
三道题解思路基本一致，均采用枚举的方式解决问题，时间复杂度都为\(O(n^2)\) 。主要差异在于判断勾股数的具体实现和一些细节处理。
1. **zhangyuxing题解**：通过两重循环遍历斜边\(c\)和直角边\(b\)，利用勾股定理计算另一直角边\(a\)（借助`sqrt`函数），并判断其是否为整数且满足去重条件。
2. **inoichi_lim题解**：同样是两重循环遍历\(c\)和\(b\)，计算\(a\)后判断其是否为整数且满足去重条件，与上一题解不同的是使用`for`宏定义，代码风格略有不同。
3. **Arvin2018题解**：通过两重循环遍历直角边\(a\)和\(b\)，计算\(c^2\)后通过判断\(\sqrt{c^2}\)向下取整的平方是否等于\(c^2\)来确定是否为勾股数，且在判断中同时处理了\(c\)不超过\(n\)的条件。

三道题解质量相近，均未在代码可读性、优化程度等方面表现突出，都未达到4星标准。

### 通用建议与扩展思路
1. **思路优化**：当前题解都是暴力枚举，可以考虑利用勾股数的一些性质进行优化，例如勾股数的通式等，减少枚举范围从而降低时间复杂度。
2. **代码优化**：在判断勾股数时，`sqrt`函数涉及浮点数运算，可能存在精度问题，可以考虑其他方式判断，如使用整数运算判断。
3. **同类型题套路**：对于此类计算满足特定数学关系的数量问题，通常先分析数学关系的特点，再选择合适的枚举方式，并注意去重和边界条件处理。

### 洛谷相似题目
1. **P1306 斐波那契公约数**：通过对斐波那契数列性质的分析，结合数论知识解决问题，和本题一样需要利用数学性质来解题。
2. **P1403 [AHOI2005]约数研究**：通过枚举和约数相关性质来统计约数个数，与本题枚举满足条件的数的思路类似。
3. **P1075 [NOIP2012 普及组] 质因数分解**：通过对整数进行分解，找到满足条件的质因数，也是基于数学知识的枚举类型题目。 

---
处理用时：32.90秒