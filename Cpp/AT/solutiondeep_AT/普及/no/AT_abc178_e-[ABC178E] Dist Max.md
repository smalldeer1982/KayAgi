# 题目信息

# [ABC178E] Dist Max

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_e

二次元平面上に $ N $ 個の点があり、$ i $ 番目の点の座標は $ (x_i,y_i) $ です。 同じ座標に複数の点があることもあります。 異なる二点間のマンハッタン距離として考えられる最大の値はいくつでしょうか。

ただし、二点 $ (x_i,y_i) $ と $ (x_j,y_j) $ のマンハッタン距離は $ |x_i-x_j|+|y_i-y_j| $ のことをいいます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i,y_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目の点と $ 2 $ 番目の点のマンハッタン距離は $ |1-2|+|1-4|=4 $ で、これが最大です。

## 样例 #1

### 输入

```
3

1 1

2 4

3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
2

1 1

1 1```

### 输出

```
0```

# AI分析结果



# [ABC178E] Dist Max 的题解分析

## 题目重述
**题目描述**  
二维平面上有 $N$ 个点，第 $i$ 个点的坐标为 $(x_i, y_i)$。可能存在多个点位于同一坐标的情况。求所有不同点对之间的曼哈顿距离的最大值。  
曼哈顿距离定义为两点 $(x_i, y_i)$ 和 $(x_j, y_j)$ 的 $|x_i - x_j| + |y_i - y_j|$。

**输入格式**  
第一行输入 $N$，随后 $N$ 行每行给出点的坐标 $(x_i, y_i)$。

**输出格式**  
输出最大的曼哈顿距离。

**样例**  
输入：
```
3
1 1
2 4
3 2
```
输出：
```
4
```

**数据范围**  
- $2 \leq N \leq 2 \times 10^5$  
- $1 \leq x_i, y_i \leq 10^9$

---

## 算法分类  
数学、曼哈顿距离转换

---

## 题解对比与结论

### 核心思路  
所有题解均基于以下关键观察：  
曼哈顿距离 $|x_i - x_j| + |y_i - y_j|$ 可转换为 $\max(\ (x_i + y_i) - (x_j + y_j),\ (x_i - y_i) - (x_j - y_j)\ )$ 的绝对值形式。因此只需维护以下四个极值：  
- $x+y$ 的最大值 $max\_plus$ 和最小值 $min\_plus$  
- $x-y$ 的最大值 $max\_minus$ 和最小值 $min\_minus$  

最终答案为 $\max(max\_plus - min\_plus,\ max\_minus - min\_minus)$

### 最优解法对比

#### 1. fish_love_cat（★★★★☆）  
**亮点**  
- 通过分类讨论引出公式转换，逻辑严密  
- 代码简洁，变量命名清晰  
**核心代码**  
```cpp
int mina=1e9, minb=1e9, maxa=-1e9, maxb=-1e9;
while(t--) {
    cin >> x >> y;
    maxa = max(maxa, x+y);  // 维护x+y的最大值
    mina = min(mina, x+y);  // 维护x+y的最小值
    maxb = max(maxb, x-y);  // 维护x-y的最大值
    minb = min(minb, x-y);  // 维护x-y的最小值
}
cout << max(maxa - mina, maxb - minb);
```

#### 2. Bluemoon_（★★★★★）  
**亮点**  
- 通过坐标系旋转 45 度的几何解释，直观呈现公式推导  
- 使用 `INT_MIN/MAX` 初始化极值变量  
**核心代码**  
```cpp
int maxx = INT_MIN, minx = INT_MAX, maxy = INT_MIN, miny = INT_MAX;
while (n--) {
    cin >> x >> y;
    int p = x + y, q = x - y;
    maxx = max(maxx, p);  // 维护x+y的极值
    minx = min(minx, p);
    maxy = max(maxy, q);  // 维护x-y的极值
    miny = min(miny, q);
}
cout << max(maxx - minx, maxy - miny);
```

#### 3. zk_y（★★★★☆）  
**亮点**  
- 采用无序点对的假设简化推导  
- 使用 `const int inf=1<<30` 处理极值边界  
**核心代码**  
```cpp
int a = -inf, b = inf, c = -inf, d = inf;
while (n--) {
    scanf("%d%d", &x, &y);
    a = max(a, x + y);  // 维护x+y的极值
    b = min(b, x + y);
    c = max(c, x - y);  // 维护x-y的极值
    d = min(d, x - y);
}
printf("%d\n", max(a - b, c - d));
```

---

## 关键技巧总结  
1. **曼哈顿距离转换**：通过数学变形将二维问题转化为一维极值问题  
2. **极值维护法**：线性遍历时维护四个极值（x+y 和 x-y 的最大/最小值）  
3. **坐标旋转思想**：将曼哈顿距离转换为切比雪夫距离坐标系中的极值差  

---

## 类似题目推荐  
1. [P5098 Cave Cows 3](https://www.luogu.com.cn/problem/P5098) - 最大曼哈顿距离应用  
2. [P2906 Cow Neighborhoods](https://www.luogu.com.cn/problem/P2906) - 曼哈顿距离与平衡树结合  
3. [CF1859E Maximum Monogonosity](https://codeforces.com/problemset/problem/1859/E) - 动态规划与曼哈顿距离特性

---
处理用时：60.67秒