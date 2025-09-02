# 题目信息

# [ABC197D] Opposite

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc197/tasks/abc197_d

$ \mathrm{x} $ 軸の正の向きを右、$ \mathrm{y} $ 軸の正の向きを上とする $ 2 $ 次元座標平面上に、$ p_0,\ p_1,\ p_2,\ \dots,\ p_{N\ -\ 1} $ の $ N $ 個の頂点からなる正 $ N $ 角形があります。  
 ここで $ N $ は偶数であることが保証され、頂点 $ p_0,\ p_1,\ p_2,\ \dots,\ p_{N\ -\ 1} $ はこの順に反時計回りに並んでいます。  
 $ p_i $ の座標を $ (x_i,\ y_i) $ とします。  
 $ x_0,\ y_0,\ x_{\frac{N}{2}},\ y_{\frac{N}{2}} $ が与えられるので、$ x_1,\ y_1 $ を求めてください。

## 说明/提示

### 制約

- $ 4\ \le\ N\ \le\ 100 $
- $ N $ は偶数
- $ 0\ \le\ x_0,\ y_0\ \le\ 100 $
- $ 0\ \le\ x_{\frac{N}{2}},\ y_{\frac{N}{2}}\ \le\ 100 $
- $ (x_0,\ y_0)\ \neq\ (x_{\frac{N}{2}},\ y_{\frac{N}{2}}) $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ p_0\ =\ (1,\ 1),\ p_2\ =\ (2,\ 2) $ という情報が与えられています。 $ p_0,\ p_1,\ p_2,\ p_3 $ が正方形をなし、反時計回りに並んでいるという情報から残りの頂点の座標は一意に定まり、以下のようになります。 - $ p_1\ =\ (2,\ 1) $ - $ p_3\ =\ (1,\ 2) $

## 样例 #1

### 输入

```
4

1 1

2 2```

### 输出

```
2.00000000000 1.00000000000```

## 样例 #2

### 输入

```
6

5 3

7 4```

### 输出

```
5.93301270189 2.38397459622```

# AI分析结果



# [ABC197D] Opposite 题解

## 题目描述

在二维坐标平面上，有一个由 $N$ 个顶点组成的正 $N$ 边形（$N$ 为偶数）。顶点按逆时针顺序排列为 $p_0,p_1,p_2,\dots,p_{N-1}$。已知顶点 $p_0(x_0,y_0)$ 和其对顶点 $p_{\frac{N}{2}}(x_{\frac{N}{2}},y_{\frac{N}{2}})$ 的坐标，求顶点 $p_1$ 的坐标。

## 算法分类
数学（几何旋转）

---

## 题解分析与结论

### 核心思路
1. **圆心计算**：正多边形对顶点连线为外接圆直径，圆心为两点的中点。
2. **旋转公式**：将 $p_0$ 绕圆心逆时针旋转 $\frac{2\pi}{N}$ 得到 $p_1$。
3. **坐标系转换**：先将坐标平移至以圆心为原点，旋转后再平移回来。

### 最优解关键点
- **旋转矩阵应用**：$(x,y)$ 绕原点旋转 $\theta$ 后的坐标为 $(x\cos\theta - y\sin\theta, x\sin\theta + y\cos\theta)$。
- **复数优化**：用复数乘法实现旋转（如 `complex<double>`）。

---

## 精选题解

### 题解1：ChuYilin2011（★★★★★）
**亮点**：
- 详细推导几何原理与旋转公式
- 提供完整数学证明框架
- 代码清晰展示坐标变换过程

**核心代码**：
```cpp
double XO = (X0+Xk)*0.5;
double YO = (Y0+Yk)*0.5;
double theta = 2*M_PI/n;

X1 = (X0-XO)*cos(theta) - (Y0-YO)*sin(theta) + XO;
Y1 = (Y0-YO)*cos(theta) + (X0-XO)*sin(theta) + YO;
```

### 题解2：loser_seele（★★★★☆）
**亮点**：
- 利用复数简化旋转计算
- 代码简洁高效（仅10行核心逻辑）
- 直接调用标准库复数运算

**核心代码**：
```cpp
auto rotate(double x, double y, int n) {
    complex<double> c(x, y), alpha(cos(2*M_PI/n), sin(2*M_PI/n));
    c *= alpha;
    return {c.real(), c.imag()};
}

auto [x1,y1] = rotate(x0-xg, y0-yg, n);
```

### 题解3：Symbolize（★★★★☆）
**亮点**：
- 提供直观几何图示说明
- 直接套用绕角公式
- 变量命名清晰便于理解

**核心公式**：
```cpp
double theta = pi/n;
printf("%.11lf %.11lf\n",
    (x0-xc)*cos(theta) - (y0-yc)*sin(theta) + xc,
    (x0-xc)*sin(theta) + (y0-yc)*cos(theta) + yc);
```

---

## 类似题目推荐
1. [P1742 最小圆覆盖](https://www.luogu.com.cn/problem/P1742)（几何旋转应用）
2. [CF598C Nearest vectors](https://www.luogu.com.cn/problem/CF598C)（极角排序与旋转）
3. [AT_abc259_d Circumferences](https://www.luogu.com.cn/problem/AT_abc259_d)（圆与几何变换）

---

## 实现技巧与心得
1. **避免变量名冲突**：`y0` 和 `y1` 是 C 标准库函数，需使用其他变量名如 `Y0`。
2. **复数优化**：通过复数运算简化旋转代码实现。
3. **调试技巧**：使用画图工具验证几何关系，例如验证旋转后的坐标是否位于正确方位。

---
处理用时：49.14秒