# 题目信息

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3
```

### 输出

```
YES
1 0
2 3
4 1
```

## 样例 #2

### 输入

```
4 4 7
```

### 输出

```
NO
```

# AI分析结果



## 唯一算法分类
数论（因数分解与最大公约数）

---

## 综合分析与结论

### 核心算法流程
1. **面积合法性验证**：根据皮克定理，三角形面积必须为 ½ 的整数倍，即 `2nm` 必须能被 `k` 整除，否则无解。
2. **因数分解与坐标构造**：将 `k` 的质因数分解到 `n` 和 `m` 的因数中，使得调整后的 `x = 2n/gcd(2n, k)` 和 `y = m/(k/gcd(2n, k))`，保证 `x*y = 2nm/k`。
3. **边界调整**：若 `x > n` 则 `x` 减半、`y` 加倍（需确保 `y ≤ m`），最终构造直角顶点在坐标轴上的三角形。

### 可视化设计思路
- **动画方案**：在 Canvas 中绘制网格坐标系，高亮原点 `(0,0)`、`(x,0)` 和 `(0,y)` 三点，动态显示 `x` 和 `y` 的调整过程。
- **颜色标记**：红色标记当前操作的坐标轴点，绿色虚线显示面积计算公式 `x*y/2`，蓝色高亮边界调整时的坐标变化。
- **步进控制**：允许单步查看因数分解、gcd 计算、边界调整等关键步骤，速度可调。

### 复古像素风格实现
- **8位风格**：使用 16 色调色板，网格线为灰色，坐标轴点为黄色像素块，面积公式显示为复古字体。
- **音效触发**：分解质因数时播放短促“点击”音效，调整坐标时播放“滑动”音效，无解时播放低沉音效。
- **自动演示**：自动执行算法步骤，每步间隔 1.5 秒，可暂停观察中间状态。

---

## 题解清单 (≥4星)

### 1. da32s1da（★★★★☆）
- **亮点**：直接通过 gcd 分解 2n 和 k，逻辑清晰，代码简洁。
- **核心代码**：
  ```cpp
  X = (2*n)/gcd(2*n, k);
  if(X > n) X/=2, m*=2;
  Y = m/(k/gcd(2*n, k));
  ```

### 2. DJRzjl（★★★★☆）
- **亮点**：分奇偶讨论 k，处理 2 的因子更系统。
- **关键步骤**：
  ```cpp
  if(k%2==0) res = solve(k/2, n, m);
  else res = solve(k, n, m) 并调整其中一个坐标乘2;
  ```

### 3. wjyyy（★★★★☆）
- **亮点**：详细数学推导，上下界优化避免 TLE。
- **代码优化**：
  ```cpp
  for(int i=(n/tt)?(n/tt):1; i<=up; ++i) // 从合理起点枚举因数
  ```

---

## 最优思路提炼

### 关键技巧
1. **质因数分配**：将 `k` 的质因数优先分配给 `n` 或 `m`，利用 `gcd` 快速分解。
2. **奇偶性处理**：当 `k` 为奇数时，将 `2` 分配给 `n` 或 `m` 的较小者以保持范围。
3. **坐标调整**：若 `x` 越界则 `x/=2` 且 `y*=2`，确保 `y` 仍满足 `y ≤ m`。

### 代码实现
```cpp
LL n, m, k;
cin >> n >> m >> k;
if (2LL * n * m % k != 0) cout << "NO";
else {
    LL g = gcd(2*n, k);
    LL x = 2*n / g;
    LL y = m / (k / g);
    if (x > n) x /= 2, y *= 2;
    cout << "YES\n0 0\n" << x << " 0\n0 " << y;
}
```

---

## 同类题目推荐
1. **CF448E** - Divisors（因数分解与构造）
2. **ABC191D** - Circle Lattice Points（格点与几何）
3. **洛谷P2651** - 添加括号（因数分配优化）

---
处理用时：74.48秒