# 题目信息

# Progress Bar

## 题目描述

A progress bar is an element of graphical interface that displays the progress of a process for this very moment before it is completed. Let's take a look at the following form of such a bar.

A bar is represented as $ n $ squares, located in line. To add clarity, let's number them with positive integers from $ 1 $ to $ n $ from the left to the right. Each square has saturation ( $ a_{i} $ for the $ i $ -th square), which is measured by an integer from $ 0 $ to $ k $ . When the bar for some $ i $ ( $ 1<=i<=n $ ) is displayed, squares $ 1,2,...\ ,i-1 $ has the saturation $ k $ , squares $ i+1,i+2,...\ ,n $ has the saturation $ 0 $ , and the saturation of the square $ i $ can have any value from $ 0 $ to $ k $ .

So some first squares of the progress bar always have the saturation $ k $ . Some last squares always have the saturation $ 0 $ . And there is no more than one square that has the saturation different from $ 0 $ and $ k $ .

The degree of the process's completion is measured in percents. Let the process be $ t $ % completed. Then the following inequation is fulfilled:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71B/4e9efb78cef50edf8afa424b4903c5e6bf3cc77f.png)An example of such a bar can be seen on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71B/151c399de3b500275514615e73a7da37fbaf060b.png)For the given $ n $ , $ k $ , $ t $ determine the measures of saturation for all the squares $ a_{i} $ of the progress bar.

## 样例 #1

### 输入

```
10 10 54
```

### 输出

```
10 10 10 10 10 4 0 0 0 0 ```

## 样例 #2

### 输入

```
11 13 37
```

### 输出

```
13 13 13 13 0 0 0 0 0 0 0 ```

# AI分析结果



# Progress Bar

## 题目描述

进度条是图形界面中显示进程当前完成度的元素。考虑如下形式的进度条：

由 $n$ 个连续方块组成，从左到右编号为 $1$ 到 $n$。每个方块的饱和度 $a_i$ 是 $0$ 到 $k$ 的整数。当进度条显示到某个位置 $i$ 时：
- 前 $i-1$ 个方块饱和度为 $k$
- 第 $i$ 个方块饱和度 $0 \leq a_i \leq k$
- 后续方块饱和度为 $0$

给定 $n$、$k$、$t$，确定所有方块的饱和度，使得满足：
$$\frac{\sum_{i=1}^n a_i}{n \cdot k} \leq \frac{t}{100} \leq \frac{\sum_{i=1}^n a_i + 1}{n \cdot k}$$

**算法分类**：构造

---

### 精选题解分析

#### 题解1：VitrelosTia（★★★★★）
**关键思路**：
1. 数学推导确定分界点：前 $p$ 个全为 $k$，第 $p+1$ 个为 $x$，后续全为 $0$
2. 推导得到 $p = \lfloor \frac{n \cdot t}{100} \rfloor$
3. $x = \frac{n \cdot k \cdot t}{100} - p \cdot k$
4. 时间复杂度 $O(n)$，直接构造结果

**核心代码**：
```cpp
int p = n * t / 100;
int x = n * k * t / 100 - p * k;
for (int i = 1; i <= p; i++) a[i] = k;
if (p + 1 <= n) a[p + 1] = x;
```

#### 题解2：Lyrella（★★★★★）
**亮点**：
- 通过不等式变形严格推导 $p$ 的表达式
- 特别处理边界情况：当 $p = n$ 时无需填充 $x$
- 代码实现简洁高效

**实现要点**：
```cpp
int m = t * n / 100;
int ans = n * k * t / 100 - m * k;
for (int i = 1; i <= m; i++) cout << k << ' ';
if (m < n) cout << ans << ' ';
for (int i = m + 2; i <= n; i++) cout << 0 << ' ';
```

---

### 最优思路总结
1. **数学建模**：将原式转化为 $\frac{pk + x}{nk} \leq \frac{t}{100}$ 的形式，推导得到分界点 $p$
2. **整数运算**：利用整除特性避免浮点误差，直接通过整数运算计算 $p$ 和 $x$
3. **构造技巧**：分三段构造数组（全 $k$ 段、过渡值、全 $0$ 段）

---

### 拓展应用
类似构造题型可考虑：
1. 分段函数模型（如 CF1593B）
2. 数学公式转化（如 AT_abc283_e）
3. 边界条件处理（如 P5723）

**推荐练习**：
1. [CF1593B - Make It Divisible by 25](https://www.luogu.com.cn/problem/CF1593B)
2. [AT_abc283_e - Don't Isolate Elements](https://www.luogu.com.cn/problem/AT_abc283_e)
3. [P5723 质数口袋](https://www.luogu.com.cn/problem/P5723)

---
处理用时：75.13秒