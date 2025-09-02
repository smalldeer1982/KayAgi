# 题目信息

# [ICPC 2020 Shanghai R] Sky Garden

## 题目描述

Prof. Du and Prof. Pang plan to build a sky garden near the city of Allin. In the garden, there will be a plant maze consisting of straight and circular roads.

On the blueprint of the plant maze, Prof. Du draws $n$ circles indicating the circular roads. All of them have center $(0, 0)$. The radius of the $i$-th circle is $i$.

Meanwhile, Prof. Pang draws $m$ lines on the blueprint indicating the straight roads. All of the lines pass through $(0, 0)$. Each circle is divided into $2m$ parts with equal lengths by these lines.

Let $Q$ be the set of the $n+m$ roads. Let $P$ be the set of all intersections of two different roads in $Q$. Note that each circular road and each straight road have two intersections.

For two different points $a\in P$ and $b\in P$, we define $dis(\{a, b\})$ to be the shortest distance one needs to walk from $a$ to $b$ along the roads. Please calculate the sum of $dis(\{a, b\})$ for all $\{a, b\}\subseteq P$. 

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/81sxvtcp.png)

$dis(p_1, p_2)=dis(p_2, p_3)=dis(p_3, p_4)=dis(p_1, p_4)=\frac{\pi}{2}$

$dis(p_1, p_5)=dis(p_2, p_5)=dis(p_3, p_5)=dis(p_4, p_5)=1$

$dis(p_1, p_3)=dis(p_2, p_4)=2$

## 样例 #1

### 输入

```
1 2```

### 输出

```
14.2831853072```

## 样例 #2

### 输入

```
2 3```

### 输出

```
175.4159265359```

# AI分析结果



### 综合分析与结论

本题核心在于高效计算所有交点间最短路径总和。关键难点在于：① 处理同一圆上的弧长与直径决策；② 不同圆间的路径降层优化。各题解主要采用数学推导或递推公式，利用对称性减少重复计算。最优解法通过分析几何性质建立数学模型，分情况讨论后转化为可快速计算的数学表达式。

---

### 高星题解推荐

#### 1. 作者：Nuyoah_awa（⭐⭐⭐⭐⭐）
**关键亮点**：
- 提出O(n)递推公式，通过分层计算贡献值
- 引入对称性思想大幅减少计算量
- 代码结构清晰，预处理关键参数g₁
```cpp
// 预处理同层点贡献
for(int i=1;i < m;i++)
    tmp += min(i * pi / m, 2.0L);
tmp = tmp*2 + 2; // 对称点处理

// 递推计算各层贡献
for(int i=2;i<=n;i++){
    g[i] = g[1] * i;
    f[i] = f[i-1] + 2*m*(i-1) + g[i];
}
```

#### 2. 作者：Ydoc770（⭐⭐⭐⭐）
**关键亮点**：
- 将答案拆分为π项与常数项分别计算
- 推导出封闭数学表达式实现O(1)计算
- 详细划分三种情况（同圆/不同圆/圆心）
```cpp
const int k = int(2 * m / pi);
// 圆心贡献计算
if(m >= 2) ans2 += n * m * (n + 1);
// 内外圆贡献公式
ans1 += 0.5 * n * k * (k + 1) * (n + 1);
ans2 += n * m * (n + 1) * (2 * m - 2 * k - 1);
```

#### 3. 作者：lailai0916（⭐⭐⭐⭐）
**关键亮点**：
- 将Nuyoah_awa的DP公式转化为O(1)解
- 提炼出关键数学参数t与求和公式
- 代码极简（仅10行核心逻辑）
```cpp
ll t=m*2/pi;
ll p=t*(t+1)*n*(n+1)*(n*2+1)/6;
ll q=m*n*(n+1)*(m*n*6-t*n*4-t*2-n*2-1+(m>1)*3)/3;
cout << p*pi+q; // 直接输出结果
```

---

### 最优关键思路提炼

1. **对称性利用**：同一圆上所有点贡献相同，只需计算基准点后乘2m
2. **降层优化定理**：外层点必先降至内层再计算路径，避免重复计算
3. **临界值k**：通过k=⌊2m/π⌋确定弧长与直径的决策分界点
4. **分治求和**：将答案拆分为π项与常数项，分别推导求和公式

---

### 相似题目推荐

1. [P1971 晨练路线](https://www.luogu.com.cn/problem/P1971) - 环形路径的最优决策
2. [CF598C 极角排序](https://www.luogu.com.cn/problem/CF598C) - 处理圆周点对关系
3. [P1298 最接近的分数](https://www.luogu.com.cn/problem/P1298) - 临界值分析与分数逼近

---
处理用时：54.67秒