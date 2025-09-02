# 题目信息

# The Supersonic Rocket

## 题目描述

After the war, the supersonic rocket became the most common public transportation.

Each supersonic rocket consists of two "engines". Each engine is a set of "power sources". The first engine has $ n $ power sources, and the second one has $ m $ power sources. A power source can be described as a point $ (x_i, y_i) $ on a 2-D plane. All points in each engine are different.

You can manipulate each engine separately. There are two operations that you can do with each engine. You can do each operation as many times as you want.

1. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i+a, y_i+b) $ , $ a $ and $ b $ can be any real numbers. In other words, all power sources will be shifted.
2. For every power source as a whole in that engine: $ (x_i, y_i) $ becomes $ (x_i \cos \theta - y_i \sin \theta, x_i \sin \theta + y_i \cos \theta) $ , $ \theta $ can be any real number. In other words, all power sources will be rotated.

The engines work as follows: after the two engines are powered, their power sources are being combined (here power sources of different engines may coincide). If two power sources $ A(x_a, y_a) $ and $ B(x_b, y_b) $ exist, then for all real number $ k $ that $ 0 \lt k \lt 1 $ , a new power source will be created $ C_k(kx_a+(1-k)x_b,ky_a+(1-k)y_b) $ . Then, this procedure will be repeated again with all new and old power sources. After that, the "power field" from all power sources will be generated (can be considered as an infinite set of all power sources occurred).

A supersonic rocket is "safe" if and only if after you manipulate the engines, destroying any power source and then power the engine, the power field generated won't be changed (comparing to the situation where no power source erased). Two power fields are considered the same if and only if any power source in one field belongs to the other one as well.

Given a supersonic rocket, check whether it is safe or not.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/1f54366cb2efd6f1fd1d0617b722b5e3979dfd89.png)Those near pairs of blue and orange points actually coincide.First, manipulate the first engine: use the second operation with $ \theta = \pi $ (to rotate all power sources $ 180 $ degrees).

The power sources in the first engine become $ (0, 0) $ , $ (0, -2) $ , and $ (-2, 0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/d9732486b953667a46772450be0d244f2cb20626.png)Second, manipulate the second engine: use the first operation with $ a = b = -2 $ .

The power sources in the second engine become $ (-2, 0) $ , $ (0, 0) $ , $ (0, -2) $ , and $ (-1, -1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1017E/f5d3a1ffc842f837240530d5f9c0ef57b3d408b7.png)You can examine that destroying any point, the power field formed by the two engines are always the solid triangle $ (0, 0) $ , $ (-2, 0) $ , $ (0, -2) $ .

In the second sample, no matter how you manipulate the engines, there always exists a power source in the second engine that power field will shrink if you destroy it.

## 样例 #1

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 4
0 0
0 2
2 0
0 2
2 2
2 0
0 0
```

### 输出

```
NO
```

# AI分析结果


### 💡 Kay的C++算法解析：The Supersonic Rocket 深入学习指南 💡

#### **1. 题目解读与核心算法识别**
✨ **本题主要考察**：计算几何（凸包） + 字符串匹配（KMP/哈希）  
🗣️ **初步分析**：
> 题目本质是判断两个点集的凸包是否全等（旋转平移后重合）。核心思想是将凸包转化为特征序列：
> - **凸包构建**：通过Andrew算法提取点集的凸包轮廓  
> - **序列编码**：记录凸包边长和角度信息形成特征序列  
> - **循环匹配**：使用KMP算法判断两个序列是否循环同构  
>  
> **可视化设计**：  
> 采用8位像素风格展示凸包构建过程：  
> - 红色像素块标记当前凸包点，绿色线段动态绘制凸包边  
> - 特征序列生成时，播放"叮"音效并高亮对应边  
> - 匹配阶段显示KMP指针移动动画，成功时触发胜利音效

---

#### **2. 精选优质题解参考**
**题解一（作者：cjlak1o1）**  
* **点评**：  
  思路清晰，创新性采用三角形稳定性原理（记录三条边）构建特征序列，避免浮点误差。代码结构规范，变量命名合理（如`_dis`计算距离）。亮点在于用几何特性替代角度计算，提升鲁棒性。实践价值高，适合竞赛直接应用。

**题解二（作者：Nelofus）**  
* **点评**：  
  采用整型哈希避免浮点精度问题，哈希函数设计巧妙（结合向量点积和模长）。代码模块化优秀（分离凸包构建和哈希计算），边界处理严谨。亮点是自创旋转不变哈希函数，时间复杂度优化至O(n)。

**题解三（作者：KKarshilov）**  
* **点评**：  
  经典角度+边长编码方案，详细处理浮点误差（`dcmp`比较函数）。代码注释完整，凸包退化情况（线段）单独处理。亮点是结合最小表示法思想，通过KMP实现循环同构检测。

---

#### **3. 核心难点辨析与解题策略**
1. **凸包退化处理**  
   * **分析**：所有点共线时凸包退化成线段，需特殊判断（如题解三的`if(top==4)`）  
   * 💡 **学习笔记**：凸包点数=3时实际为线段，需单独计算长度比较

2. **特征序列设计**  
   * **分析**：既要旋转不变又要唯一标识凸包。优质解法采用：  
     - 边长+角度组合（KKarshilov）  
     - 三边构成三角形（cjlak1o1）  
     - 向量哈希（Nelofus）  
   * 💡 **学习笔记**：避免直接用角度可防浮点误差

3. **浮点精度控制**  
   * **分析**：比较需用`eps`阈值（如`fabs(a-b)<=1e-8`）。KKarshilov的`dcmp`函数和Hoks的`chdb`是典范  
   * 💡 **学习笔记**：整型运算 > 浮点运算 > 浮点比较+eps

### ✨ 解题技巧总结
- **几何问题代数化**：将凸包转化为特征序列，用字符串算法处理  
- **鲁棒性优先**：整型哈希 > 三边定理 > 浮点角度  
- **模块化封装**：分离凸包构建、序列生成、匹配验证三个模块  
- **退化情况测试**：单点、线段、共线等边界用例必测

---

#### **4. C++核心代码实现赏析**
**通用核心实现（综合题解优化）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;

struct Point { double x, y; };
double dis(Point a, Point b) { 
    return hypot(a.x-b.x, a.y-b.y);
}

vector<Point> convexHull(vector<Point> p) {
    sort(p.begin(), p.end(), [](auto a, auto b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    vector<Point> stk;
    for (int i = 0; i < 2; i++) {
        for (auto pt : p) {
            while (stk.size() >= 2) {
                auto a = stk[stk.size()-2];
                auto b = stk.back();
                if ((b.x-a.x)*(pt.y-b.y) <= (b.y-a.y)*(pt.x-b.x))
                    stk.pop_back();
                else break;
            }
            stk.push_back(pt);
        }
        reverse(p.begin(), p.end());
    }
    return stk;
}
```

**题解一赏析（cjlak1o1）**  
```cpp
// 三边特征序列生成
void build(int n) {
    for(int i=3; i<=n; i++) {
        a[cnt++] = dis(st[i-1], st[i-2]); // 边1
        a[cnt++] = dis(st[i], st[i-1]);   // 边2
        a[cnt++] = dis(st[i], st[i-2]);   // 连接边
    }
}
```
> **解读**：  
> 每三个点生成三条边构成三角形，利用SSS全等定理保证特征唯一性  
> **学习笔记**：用几何性质替代角度计算，避免浮点误差

**题解二赏析（Nelofus）**  
```cpp
// 整型哈希函数
Hash base = {rng(), rng()};
for (auto v1, v2 : vectors) {
    i64 val = Dot(v1,v1) * Dot(v1,v2); // 整型计算
    hs = hs * base + Hash(val, val);
}
```
> **解读**：  
> 通过随机基底的进制哈希实现旋转不变性，Dot用整型避免浮点误差  
> **学习笔记**：整型哈希是处理几何匹配的利器

---

#### **5. 算法可视化：像素动画演示**
![](https://cdn.luogu.com.cn/upload/image_hosting/e84vjhua.png)  
* **主题**：像素凸包构建与KMP匹配  
* **设计思路**：  
  1. **8位像素网格**：浅灰背景，深绿凸包点，黄色动态扫描线  
  2. **凸包构建动画**：红色指针移动，成功添加点时播放"叮"音效  
  3. **特征序列生成**：每添加一条边，右侧显示对应像素色块（蓝/绿/橙）  
  4. **KMP匹配演示**：  
     - 上下双序列显示，紫色指针动态跳转  
     - 匹配成功时触发胜利音效和烟花特效  
  5. **交互控制**：  
     - 速度滑块调节动画速度  
     - "单步执行"按钮逐步观察凸包构建  
     - "AI演示"自动完成全过程  

* **技术实现**：  
  ```javascript
  // 伪代码：凸包绘制
  function drawConvexHull() {
    for (let i=0; i<points.length; i++) {
      drawPixel(points[i], 0xFF0000); // 红色当前点
      playSound('select'); 
      await delay(speed);
      if(isConvexPoint()) {
        drawLine(prev, curr, 0x00FF00); // 绿色凸包边
        addToSequence(); // 生成特征色块
      }
    }
  }
  ```

---

#### **6. 拓展练习与相似问题**
* **通用技巧迁移**：  
  凸包+特征匹配适用于：  
  1. 图形识别（旋转不变性）  
  2. 运动轨迹相似度判断  
  3. 分子结构比对  

* **洛谷推荐**：  
  1. **P2742** - 凸包模板题  
     🗣️ 巩固Andrew凸包算法基础实现  
  2. **P3375** - KMP模板  
     🗣️ 掌握字符串匹配核心思想  
  3. **P3829** - 旋转卡壳  
     🗣️ 凸包进阶应用，求最大直径  

---

#### **7. 学习心得与经验分享**
> **来自KKarshilov的经验**：  
> "角度计算必须用eps比较，否则NaN会毁掉整个程序！"  
>  
> **Kay点评**：  
> 这是计算几何的黄金法则：  
> - 浮点比较必须用 `fabs(a-b) < eps`  
> - 优先考虑整型运算或几何性质替代角度  

---

通过本次分析，我们掌握了凸包全等判断的核心技巧：几何特征编码+循环匹配。记住：**浮点运算是几何计算的隐形地雷，整型运算和特征设计是避雷针**！下次遇到类似问题，试试用像素动画模拟算法流程吧！💪

---
处理用时：88.25秒