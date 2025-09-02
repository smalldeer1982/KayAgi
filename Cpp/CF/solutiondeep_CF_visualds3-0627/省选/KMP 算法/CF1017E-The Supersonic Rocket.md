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



## 算法分类
几何、凸包、字符串匹配（KMP）

---

## 题解思路与解决难点

### 核心思路
题目要求两个点集的凸包在允许平移旋转后，其生成的power field具备摧毁任意点后仍然保持原结构。等价于判断两个凸包的几何结构是否可以通过旋转平移相互转换。所有题解均采用以下核心步骤：
1. **凸包构建**：对两个点集求凸包，得到多边形。
2. **特征序列生成**：将凸包的几何特征（边长、角度、向量关系）编码为线性序列。
3. **循环同构判断**：通过KMP算法判断两个序列是否循环同构。

### 关键难点与解决方案
1. **几何特征提取**：
   - 难点：需选取旋转平移不变的特征（如边长的比值、角度关系）。
   - 解法：多数题解采用边-角组合或附加边（如三角形第三条边）作为序列元素。
   
2. **浮点精度处理**：
   - 难点：浮点数运算存在精度误差，可能导致匹配失败。
   - 解法：使用`eps`容差比较（如`fabs(a-b) <= 1e-8`），或改用整数运算（如点积叉积）。

3. **循环序列匹配**：
   - 难点：凸包的起点不固定，需判断任意起点的循环排列是否匹配。
   - 解法：将特征序列复制一倍后拼接，用KMP在长序列中查找目标序列。

---

## 题解评分（≥4星）

### 题解1（cjlak1o1）：★★★★☆
- **亮点**：引入三角形稳定性，构造唯一性强的特征序列；代码清晰，处理共线情况。
- **不足**：未显式处理浮点精度，可能在某些数据出错。

### 题解2（Nelofus）：★★★★☆
- **亮点**：哈希函数结合向量点积与长度，避免浮点运算；特判线段情况。
- **不足**：哈希碰撞风险未讨论。

### 题解3（KKarshilov）：★★★☆☆
- **亮点**：显式处理角度计算与浮点误差，代码完整。
- **不足**：序列生成逻辑复杂，可读性稍低。

---

## 最优思路提炼
1. **凸包标准化**：通过Andrew算法构建凸包，处理共线点。
2. **特征序列构造**：将凸包拆解为边-角-边-角交替序列，或添加辅助边增强唯一性。
3. **KMP循环匹配**：将序列视为环状结构，通过复制+KMP实现高效匹配。

---

## 同类型题与算法套路
- **几何同构判断**：将几何结构编码为字符串或哈希值进行比较。
- **循环序列匹配**：最小表示法、KMP处理循环同构问题。

---

## 推荐题目
1. [P2742 凸包模板](https://www.luogu.com.cn/problem/P2742)
2. [P3375 KMP模板](https://www.luogu.com.cn/problem/P3375)
3. [P1709 隐藏口令（循环同构）](https://www.luogu.com.cn/problem/P1709)

---

## 个人心得摘录
> "Andrew算法排序时注意上下凸壳的处理，避免漏点。" —— cjlak1o1  
> "哈希函数中加入点积与长度平方，减少浮点误差影响。" —— Nelofus  
> "被NaN坑惨了，特判所有角度计算中的除零情况！" —— Hoks  

---

## 可视化算法演示

### 核心流程
1. **凸包构建**：动态展示Andrew算法逐点加入凸包的过程，红色高亮当前处理点。
2. **特征序列生成**：以不同颜色方块表示边（绿色）、角（蓝色）、辅助边（黄色），在Canvas网格中排列。
3. **KMP匹配**：展示模式串与文本串的滑动匹配过程，匹配成功时触发像素闪烁。

### 复古像素风格设计
- **颜色方案**：16色调色板，凸包边用#00FF00（绿），角度用#0000FF（蓝）。
- **音效**：凸包构建时播放“滴”声，KMP匹配成功时播放8-bit胜利音效。
- **自动演示**：按空格键切换手动/自动模式，自动模式下算法逐步执行，速度可调。

### 关键代码片段（伪代码）
```javascript
// 凸包构建可视化
function drawConvexHull(points) {
  sort(points); // 按x,y排序
  for (let p of points) {
    while (hull.length >= 2 && cross(...hull.slice(-2), p) <= 0) {
      hull.pop(); // 回退，Canvas绘制红色撤销动画
    }
    hull.push(p); // 绿色高亮加入点
  }
}

// KMP匹配动画
function kmpVisual(s, p) {
  let j = 0;
  for (let i = 0; i < s.length; i++) {
    while (j > 0 && s[i] !== p[j]) {
      j = next[j-1]; // 黄色高亮回退操作
    }
    if (s[i] === p[j]) j++;
    // 蓝色高亮当前匹配位置
    if (j === p.length) return true;
  }
  return false;
}
```

---

**总结**：通过凸包特征提取与字符串匹配技术的结合，将几何问题转化为序列比对问题，是此类题目的核心解法。可视化设计通过复古像素风格与音效增强理解趣味性。

---
处理用时：76.75秒