# 题目信息

# Petya and Square

## 题目描述

Little Petya loves playing with squares. Mum bought him a square $ 2n×2n $ in size. Petya marked a cell inside the square and now he is solving the following task.

The task is to draw a broken line that would go along the grid lines and that would cut the square into two equal parts. The cutting line should not have any common points with the marked cell and the resulting two parts should be equal up to rotation.

Petya wants to determine whether it is possible to cut the square in the required manner given the sizes of the square side and the coordinates of the marked cell. Help him.

## 说明/提示

A sample test from the statement and one of the possible ways of cutting the square are shown in the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF112B/73a8bd680c4d33b060b29ddcf134c8221469d9f6.png)

## 样例 #1

### 输入

```
4 1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2 2
```

### 输出

```
NO
```

# AI分析结果



# Petya and Square

## 题目描述

小 Petya 喜欢玩正方形。妈妈给他买了一个边长为 2n×2n 的正方形。Petya 在正方形内标记了一个单元格，现在他要解决以下任务：

任务是沿着网格线画一条折线，将正方形切割为两个相等的部分。切割线不能与标记的单元格有任何公共点，且切割后的两部分通过旋转能够重合。

给定正方形的边长参数 n 和标记单元格的坐标 (x,y)，请判断是否存在这样的切割方式。

## 说明/提示

样例示意图展示了当标记单元格不在中心区域时的可行切割方案，以及标记单元格在中心区域时的不可行情况。

## 样例 #1

### 输入
```
4 1 1
```

### 输出
```
YES
```

## 样例 #2

### 输入
```
2 2 2
```

### 输出
```
NO
```

---

**算法分类**：数学

---

## 题解综合分析与结论

所有题解的核心思路是：当且仅当标记单元格位于正方形的中心四个格子时无法分割。数学本质是任何对称切割都必须经过几何中心区域，若标记点占据中心四个格子之一，必然与所有有效切割路径相交。

### 精选题解（评分≥4星）

1. **作者：simonG（4星）**  
   **关键亮点**：通过多张示意图清晰展示对称切割原理，证明中心四个格子是唯一阻碍点  
   **核心代码**：
   ```cpp
   if((n-k/2==0||n-k/2==1)&&(m-k/2==0||m-k/2==1))
       puts("NO");
   else
       puts("YES");
   ```

2. **作者：Stephen_Curry（4星）**  
   **关键亮点**：使用三目运算符精简代码，明确表达条件判断逻辑  
   **核心代码**：
   ```cpp
   cout << ((x == n/2 || x == n/2+1) && (y == n/2 || y == n/2+1) ? "NO" : "YES");
   ```

3. **作者：SqrtSecond（4星）**  
   **关键亮点**：通过坐标位移转换简化条件判断，增强代码可读性  
   **核心代码**：
   ```cpp
   int tx = n/2, ty = n/2;
   if ((tx == x || tx+1 == x) && (ty == y || ty+1 == y)) puts("NO");
   ```

---

## 最优解题思路

**关键技巧**：将几何问题转化为坐标区间判断  
1. 计算正方形的几何中心区域为坐标范围 [n/2, n/2+1] × [n/2, n/2+1]
2. 只需判断给定坐标是否落在此区间内

**数学推导**：  
设正方形边长为2n，几何中心点为(n, n)。有效切割线必经过中心区域，标记点若占据中心四个格子（坐标范围为n/2 ≤ x ≤ n/2+1且同理y），则所有合法切割路径都会被阻挡。

---

## 拓展与相似题目

**同类问题套路**：几何对称性判断、中心区域判定、坐标区间分析  
**推荐题目**：
1. [P2181 对角线](https://www.luogu.com.cn/problem/P2181) - 几何组合数学
2. [CF1110A Parity](https://www.luogu.com.cn/problem/CF1110A) - 数学奇偶性判断
3. [P5712 Apples](https://www.luogu.com.cn/problem/P5712) - 坐标范围判断

---

## 题解个人心得摘录

1. **爱瑶瑶公主**：误认为切割线不能触碰标记单元格的边界，实际应理解为切割路径不得与单元格共享任何网格线或顶点  
   **正确理解**：题目要求切割线不能与单元格有公共点（包括边线和顶点）

2. **hensier**：通过中心对称性证明切割必然经过中心区域，将问题转化为纯坐标判断，体现了数学抽象能力  
   **启示**：复杂几何问题可尝试寻找对称性特征转化为代数条件

3. **W_churchill**：指出所有合法切割线必然经过几何中心，这一关键观察是解题的核心突破口  
   **应用**：当题目涉及对称分割时，优先分析几何中心区域的特性

---
处理用时：53.87秒