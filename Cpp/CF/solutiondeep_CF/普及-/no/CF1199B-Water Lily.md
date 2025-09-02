# 题目信息

# Water Lily

## 题目描述

While sailing on a boat, Inessa noticed a beautiful water lily flower above the lake's surface. She came closer and it turned out that the lily was exactly $ H $ centimeters above the water surface. Inessa grabbed the flower and sailed the distance of $ L $ centimeters. Exactly at this point the flower touched the water surface.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1199B/42f6cea9c2bcade7ac8750d98129857158bca8c3.png)Suppose that the lily grows at some point $ A $ on the lake bottom, and its stem is always a straight segment with one endpoint at point $ A $ . Also suppose that initially the flower was exactly above the point $ A $ , i.e. its stem was vertical. Can you determine the depth of the lake at point $ A $ ?

## 样例 #1

### 输入

```
1 2
```

### 输出

```
1.5000000000000
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
2.6666666666667
```

# AI分析结果

### 题目内容
# 睡莲

## 题目描述
在乘船航行时，伊内萨注意到湖面上方有一朵美丽的睡莲。她靠近后发现，这朵睡莲恰好高出水面 \( H \) 厘米。伊内萨抓住这朵花，然后乘船移动了 \( L \) 厘米。恰好在这个位置，这朵花接触到了水面。

假设睡莲生长在湖底的某点 \( A \) 处，并且它的茎始终是一条直线段，其中一个端点在点 \( A \) 处。同时假设最初这朵花正好在点 \( A \) 的正上方，即它的茎是垂直的。你能确定点 \( A \) 处湖水的深度吗？

## 样例 #1
### 输入
```
1 2
```
### 输出
```
1.5000000000000
```
## 样例 #2
### 输入
```
3 5
```
### 输出
```
2.6666666666667
```
### 算法分类
数学
### 综合分析与结论
所有题解思路一致，均通过设水深为 \( x \) ，利用勾股定理构建方程 \( x^2 + L^2 = (x + H)^2 \) ，再对方程化简求解得出 \( x = \frac{L^2 - H^2}{2H} \) ，最后根据该公式编写代码计算并输出结果。主要差异在于代码实现细节，如变量类型定义、输入输出方式及精度控制。

所有题解质量相近，整体未达4星标准，无需返回具体题解。
### 通用建议与扩展思路
 - **思路清晰化**：在解题前，可更详细地阐述如何根据题目描述构建出勾股定理方程，帮助读者更好理解从实际问题到数学模型的转化过程。
 - **代码规范与注释**：添加适当注释，使代码逻辑更清晰，尤其是对关键计算步骤和变量含义进行说明。同时，注意选择合适的变量类型和精度控制，以适应不同规模的数据。
 - **拓展同类型题**：此类题目属于利用几何定理（勾股定理）解决实际问题的类型，类似的题目还可能涉及其他几何图形和定理，如利用相似三角形、三角函数等解决实际场景中的长度、角度问题。可通过多练习此类题目，强化将实际问题抽象为数学模型并求解的能力。
### 推荐题目
 - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：考察数论相关知识，与本题类似，需通过数学推导得出解题公式。
 - [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：主要涉及数论中的同余方程求解，锻炼数学思维和方程求解能力。
 - [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过分析题目条件建立数学模型，与本题构建方程求解思路相似。 

---
处理用时：27.87秒