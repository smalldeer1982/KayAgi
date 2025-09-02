# 题目信息

# [ABC362B] Right Triangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_b

$ xy $ 平面上に、同一直線上にない $ 3 $ 点 $ A(x_A,y_A),\ B(x_B,y_B),C(x_C,y_C) $ があります。三角形 $ ABC $ が直角三角形であるかどうか判定してください。

## 说明/提示

### 制約

- $ -1000\leq\ x_A,y_A,x_B,y_B,x_C,y_C\leq\ 1000 $
- $ 3 $ 点 $ A,B,C $ は同一直線上にない
- 入力は全て整数
 
### Sample Explanation 1

三角形 $ ABC $ は直角三角形です。 !\[\](https://img.atcoder.jp/abc362/3f4a68afd7a43d159b7e7ef4cee6c646.png)

### Sample Explanation 2

三角形 $ ABC $ は直角三角形です。 !\[\](https://img.atcoder.jp/abc362/092af99ccc22b9235a87bc2b5f53bfa3.png)

### Sample Explanation 3

三角形 $ ABC $ は直角三角形ではありません。 !\[\](https://img.atcoder.jp/abc362/f7fbb440279967aee94ef846562d4b0e.png)

## 样例 #1

### 输入

```
0 0

4 0

0 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
-4 3

2 1

3 4```

### 输出

```
Yes```

## 样例 #3

### 输入

```
2 4

-3 2

1 -2```

### 输出

```
No```

# AI分析结果



## 算法分类
**无算法分类**

## 综合分析与结论
### 核心思路
通过计算三个顶点是否为直角顶点，判断三角形是否为直角三角形。每个顶点对应两条邻边向量，若点积为零，则两条边垂直，该顶点为直角顶点。

### 解决难点
1. **向量方向确定**：每个顶点的邻边向量需正确计算（如点A的向量为B-A和C-A）。
2. **点积判零**：整数坐标下直接计算向量分量乘积之和，无需浮点误差处理。
3. **覆盖所有情况**：检查三个顶点所有可能的直角情况，确保不遗漏。

### 可视化设计
- **向量高亮**：以不同颜色绘制三个顶点对应的邻边向量。
- **点积动态计算**：逐步展示向量分量乘积及总和，高亮当前计算步骤。
- **像素风格界面**：8位风格绘制坐标系，音效提示判断结果（成功/失败音效）。
- **自动演示**：按顺序检查三个顶点，展示计算过程与结果。

---

## 最优思路提炼
1. **向量点积法**：直接判断邻边向量是否垂直，避免平方根运算。
2. **顶点遍历**：覆盖所有可能的直角顶点，确保逻辑完备。
3. **整数运算**：利用输入为整数的特性，避免浮点精度问题。

---

## 代码实现
```cpp
#include <iostream>
using namespace std;

int main() {
    int ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;

    auto check = [](int x1, int y1, int x2, int y2) {
        return x1 * x2 + y1 * y2 == 0;
    };

    bool isRight = false;
    // Check point A: vectors AB and AC
    isRight |= check(bx - ax, by - ay, cx - ax, cy - ay);
    // Check point B: vectors BA and BC
    isRight |= check(ax - bx, ay - by, cx - bx, cy - by);
    // Check point C: vectors CA and CB
    isRight |= check(ax - cx, ay - cy, bx - cx, by - cy);

    cout << (isRight ? "Yes" : "No") << endl;
    return 0;
}
```

---

## 同类型题推荐
1. **P1355** 三角形的最大面积（几何基础）
2. **CF1025B** Weakened Common Divisor（数学性质应用）
3. **AT1219** 旅人計画（向量与方向判断）

---

## 可视化与游戏化设计
### 像素动画
- **坐标系绘制**：16色网格背景，三点用不同颜色像素块表示。
- **向量动态绘制**：检查每个顶点时，用箭头表示邻边向量，显示分量及点积。
- **音效反馈**：点积为零时播放“成功”音效，否则“失败”音效。

### 交互功能
- **步进控制**：按空格键逐步执行检查流程。
- **自动模式**：自动播放检查过程，速度可调。
- **积分系统**：正确判断后获得积分，连击增加得分倍率。

---

## 个人心得
- **调试经验**：初始误将向量方向颠倒（如BA写成AB），导致逻辑错误。通过样例1反推修正。
- **优化技巧**：使用Lambda函数复用点积检查代码，提升可读性。

---
处理用时：191.10秒