# 题目信息

# Olympic Medal

## 题目描述

The World Programming Olympics Medal is a metal disk, consisting of two parts: the first part is a ring with outer radius of $ r_{1} $ cm, inner radius of $ r_{2} $ cm, $ (0&lt;r2&lt;r1) $ made of metal with density $ p_{1} $ g/cm $ ^{3} $ . The second part is an inner disk with radius $ r_{2} $ cm, it is made of metal with density $ p_{2} $ g/cm $ ^{3} $ . The disk is nested inside the ring.

The Olympic jury decided that $ r_{1} $ will take one of possible values of $ x_{1},x_{2},...,x_{n} $ . It is up to jury to decide which particular value $ r_{1} $ will take. Similarly, the Olympic jury decided that $ p_{1} $ will take one of possible value of $ y_{1},y_{2},...,y_{m} $ , and $ p_{2} $ will take a value from list $ z_{1},z_{2},...,z_{k} $ .

According to most ancient traditions the ratio between the outer ring mass $ m_{out} $ and the inner disk mass $ m_{in} $ must equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215B/cd92991466e894ef37b65a9188f245d17d24ea1f.png), where $ A,B $ are constants taken from ancient books. Now, to start making medals, the jury needs to take values for $ r_{1} $ , $ p_{1} $ , $ p_{2} $ and calculate the suitable value of $ r_{2} $ .

The jury wants to choose the value that would maximize radius $ r_{2} $ . Help the jury find the sought value of $ r_{2} $ . Value $ r_{2} $ doesn't have to be an integer.

Medal has a uniform thickness throughout the area, the thickness of the inner disk is the same as the thickness of the outer ring.

## 说明/提示

In the first sample the jury should choose the following values: $ r_{1}=3 $ , $ p_{1}=2 $ , $ p_{2}=1 $ .

## 样例 #1

### 输入

```
3 1 2 3
1 2
3 3 2 1
1 2
```

### 输出

```
2.683281573000
```

## 样例 #2

### 输入

```
4 2 3 6 4
2 1 2
3 10 6 8
2 1
```

### 输出

```
2.267786838055
```

# AI分析结果



题目内容中文重写：

# 奥运奖牌

## 题目描述

世界编程奥林匹克奖牌是一个金属圆盘，由两部分组成：第一部分是外环，外半径 $r_1$ 厘米，内半径 $r_2$ 厘米（$0<r_2<r_1$），由密度为 $p_1$ g/cm³ 的金属制成；第二部分是内盘，半径为 $r_2$ 厘米，由密度为 $p_2$ g/cm³ 的金属制成。内盘嵌套在外环内部。

奥组委决定 $r_1$ 的取值可能为 $x_1,x_2,...,x_n$ 中的一个，$p_1$ 的取值可能为 $y_1,y_2,...,y_m$ 中的一个，$p_2$ 的取值可能为 $z_1,z_2,...,z_k$ 中的一个。

根据古老传统，外环质量 $m_{out}$ 与内盘质量 $m_{in}$ 的比值必须等于 $A/B$，其中 $A,B$ 是古籍中的常数。现在需要选择合适的 $r_1,p_1,p_2$ 并计算出对应的最大可能的 $r_2$ 值。

---

**算法分类**：数学、贪心

---

### 题解综合分析与结论

通过数学公式推导得出，$r_2$ 的最大值由 $r_1$ 的最大值、$p_1$ 的最大值和 $p_2$ 的最小值共同决定。关键思路是将质量比公式转化为几何关系式，通过极值分析直接确定各参数的最优选择，避免暴力枚举。

---

### 精选题解分析

#### 题解1 - 作者：Alex_Wei（⭐⭐⭐⭐⭐）
**关键亮点**：
1. 通过严谨的数学推导将质量比转化为半径平方比公式
2. 发现极值关系：$r_1$ 取最大、$p_1$ 取最大、$p_2$ 取最小时 $r_2$ 最大
3. 时间复杂度优化至线性 $O(n+m+k)$

**核心代码**：
```cpp
double r1,p1,p2=1e9;
// 取最大值
cin>>n; for(...) r1=max(r1,x); 
cin>>m; for(...) p1=max(p1,x);
// 取最小值 
cin>>k; for(...) p2=min(p2,x);
// 计算最终结果
printf("%.9lf", sqrt(r1*r1/(A*p2/(B*p1)+1)));
```

---

### 最优思路总结
1. **数学建模**：通过几何体积与密度关系建立质量比方程
2. **公式变形**：将方程转化为 $r_2^2 = \frac{r_1^2}{A p_2/(B p_1) + 1}$ 的形式
3. **极值分析**：识别出分母最小化时 $r_2$ 最大，进而确定各参数选择策略

---

### 拓展应用
同类问题可考虑：
1. 涉及比例关系的最值问题（如几何、物理公式相关）
2. 需要分析多个变量对结果的复合影响的问题
3. 通过数学推导将暴力搜索优化为极值选取的场景

---

### 推荐习题
1. [P1058 立体图](https://www.luogu.com.cn/problem/P1058) - 三维几何建模
2. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024) - 数学公式推导
3. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909) - 极值选择策略

---

### 题解心得摘录
"通过分母分析发现：当 $p_1$ 越大、$p_2$ 越小时，分母项 $A p_2/(B p_1)$ 越小，从而使整个分母值最小，最终 $r_2$ 最大。这种极值思维是解题的关键。" —— 摘自Alex_Wei题解

---
处理用时：76.87秒