# 题目信息

# Square and Rectangles

## 题目描述

You are given $ n $ rectangles. The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if the rectangles form a square. In other words, determine if the set of points inside or on the border of at least one rectangle is precisely equal to the set of points inside or on the border of some square.

## 样例 #1

### 输入

```
5
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5
2 2 3 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5
```

### 输出

```
NO
```

# AI分析结果



### 题目重写
#### 题目名称：正方形与矩形

**题目描述**  
给定 $n$ 个矩形，每个矩形的边平行于坐标轴，且顶点坐标为整数。矩形之间不重叠（即任意两个矩形的内部区域没有交集）。判断这些矩形是否恰好拼成一个正方形（所有矩形的并集形成一个完整的实心正方形）。

**输入格式**  
第一行输入整数 $n$，表示矩形数量。接下来每行输入四个整数 $a, b, c, d$，表示矩形左下角 $(a, b)$ 和右上角 $(c, d)$ 的坐标。

**输出格式**  
若可以拼成正方形，输出 `YES`，否则输出 `NO`。

---

### 算法分类  
**数学**

---

### 题解分析与结论  
所有题解均基于以下核心思路：  
1. **计算所有矩形的总面积之和**。  
2. **找到所有矩形的最小包围矩形**（由最小左/下坐标和最大右/上坐标确定）。  
3. **判断两个条件**：  
   - 包围矩形是否为正方形（即长宽相等）。  
   - 包围矩形的面积是否等于所有矩形面积之和（确保无空隙）。  

**关键技巧**：  
- 利用极值快速计算包围矩形的范围。  
- 通过面积相等判断是否完全覆盖（因题目保证无重叠）。  

---

### 精选题解  
#### 题解1：@miraculously（5星）
**核心亮点**：  
- 代码简洁高效，变量命名清晰（如 `sx`、`tx`）。  
- 直接使用条件表达式输出结果，减少代码冗余。  
**代码片段**：  
```cpp
if(cnt==(tx-sx)*(ty-sy)&&tx-sx==ty-sy)
    printf("YES\n");
else
    printf("NO\n");
```

#### 题解2：@封禁用户（4星）
**核心亮点**：  
- 使用三目运算符简化输出逻辑。  
- 初始值设置合理（`minx=1e9`）。  
**代码片段**：  
```cpp
printf((maxx-minx==maxy-miny&&area==(maxx-minx)*(maxy-miny))?"YES\n":"NO\n");
```

#### 题解3：@01Dragon（4星）  
**核心亮点**：  
- 注释明确，增强可读性。  
- 正确处理面积符号（利用坐标差的正负不影响乘积绝对值）。  
**代码片段**：  
```cpp
sum += (a-c)*(b-d); // 负号不影响面积绝对值
```

---

### 扩展思路  
**类似题型**：  
1. **判断覆盖区域形状**（如长方形、圆形）。  
2. **动态覆盖问题**（如新增/删除矩形后重新判断覆盖区域）。  

**推荐题目**：  
1. [P1058 立体图](https://www.luogu.com.cn/problem/P1058)（二维空间覆盖可视化）。  
2. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)（极值计算与区间处理）。  
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)（二维空间覆盖判断的变体）。  

---

### 个人心得摘录  
- @Leap_Frog 指出：“题目通过率低可能是因为忽略面积与包围矩形边长的双重判断”。  
- @封禁用户 代码中直接使用 `1e9` 初始化极值，避免溢出问题。

---
处理用时：72.23秒