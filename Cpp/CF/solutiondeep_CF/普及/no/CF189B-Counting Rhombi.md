# 题目信息

# Counting Rhombi

## 题目描述

You have two positive integers $ w $ and $ h $ . Your task is to count the number of rhombi which have the following properties:

- Have positive area.
- With vertices at integer points.
- All vertices of the rhombi are located inside or on the border of the rectangle with vertices at points $ (0,0) $ , $ (w,0) $ , $ (w,h) $ , $ (0,h) $ . In other words, for all vertices $ (x_{i},y_{i}) $ of the rhombus the following conditions should fulfill: $ 0<=x_{i}<=w $ and $ 0<=y_{i}<=h $ .
- Its diagonals are parallel to the axis.

Count the number of such rhombi.

Let us remind you that a rhombus is a quadrilateral whose four sides all have the same length.

## 说明/提示

In the first example there exists only one such rhombus. Its vertices are located at points $ (1,0) $ , $ (2,1) $ , $ (1,2) $ , $ (0,1) $ .

## 样例 #1

### 输入

```
2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
0
```

# AI分析结果



# Counting Rhombi 题目中文翻译

## 题目描述

给定两个正整数 $w$ 和 $h$，统计满足以下条件的菱形数量：
1. 具有正面积。
2. 顶点为整数点。
3. 所有顶点位于以 $(0,0)$、$(w,0)$、$(w,h)$、$(0,h)$ 为顶点的矩形内部或边界上。
4. 对角线平行于坐标轴。

## 样例 #1

### 输入
```
2 2
```

### 输出
```
1
```

## 样例 #2

### 输入
```
1 2
```

### 输出
```
0
```

---

**算法分类**：数学、组合数学

---

## 题解分析与结论

所有题解均通过将菱形问题转化为矩形计数问题，利用数学公式直接计算。核心思路是：
1. 菱形对角线对应矩形的长宽必须是偶数
2. 计算水平和垂直方向的有效长度组合数
3. 结果公式为：$\frac{(w^2 - (w \mod 2))(h^2 - (h \mod 2))}{16}$

---

### 精选题解

#### 1. 作者：Sammy_prime（★★★★☆）
**关键亮点**：
- 直接给出数学公式实现
- 代码简洁高效，时间复杂度 O(1)
```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h;
int main(){ 
    scanf("%d%d",&w,&h);
    printf("%lld\n",(w*w-w%2)*(h*h-h%2)/16);
    return 0;
}
```

#### 2. 作者：封禁用户（★★★★☆）
**关键亮点**：
- 明确推导公式的数学背景
- 将问题类比为小学奥数题，便于理解
**个人心得**：
> "将菱形问题转化为偶长度矩形计数，利用奇偶性处理平方项"

#### 3. 作者：PvbeLLN（★★★★☆）
**关键亮点**：
- 使用图示辅助理解菱形与矩形的关系
- 强调数据类型转换防止溢出
```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h;
int main(){ 
    cin>>w>>h;
    cout<<(long long)(w*w-w%2)*(h*h-h%2)/16;
    return 0;
}
```

---

## 核心代码实现
所有题解共享同一核心公式：
```cpp
long long ans = (w*w - w%2) * (h*h - h%2) / 16;
```
**实现思想**：
1. 对 w 和 h 的平方进行奇偶修正
2. 乘积除以 16 处理两维方向的组合数

---

## 拓展与相似题目
1. **P2735 电网**（坐标网格中的几何计数）
2. **P1582 倒水**（位运算与数学结合）
3. **CF630C Lucky Numbers**（组合数学公式应用）

---
处理用时：122.53秒