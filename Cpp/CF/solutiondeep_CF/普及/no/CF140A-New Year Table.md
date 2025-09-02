# 题目信息

# New Year Table

## 题目描述

Gerald is setting the New Year table. The table has the form of a circle; its radius equals $ R $ . Gerald invited many guests and is concerned whether the table has enough space for plates for all those guests. Consider all plates to be round and have the same radii that equal $ r $ . Each plate must be completely inside the table and must touch the edge of the table. Of course, the plates must not intersect, but they can touch each other. Help Gerald determine whether the table is large enough for $ n $ plates.

## 说明/提示

The possible arrangement of the plates for the first sample is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140A/89a963dd60d2b50871a138411d49010a4f94431a.png)

## 样例 #1

### 输入

```
4 10 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 10 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 10 10
```

### 输出

```
YES
```

# AI分析结果



# New Year Table

## 题目描述

Gerald正在布置新年餐桌。餐桌的形状是一个半径为$R$的圆形。Gerald邀请了许多客人，他想知道餐桌是否足够放下所有客人的盘子。所有盘子都是圆形且半径相同为$r$。每个盘子必须完全位于餐桌内部且与餐桌边缘相切，盘子之间不能相交但可以相碰。请帮助Gerald判断能否放下$n$个盘子。

## 说明/提示

第一个样例的可能摆放方式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140A/89a963dd60d2b50871a138411d49010a4f94431a.png)

## 样例 #1

### 输入

```
4 10 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 10 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 10 10
```

### 输出

```
YES
```

---

**算法分类**：数学

**综合分析结论**：
所有题解均采用几何解法，核心思路是计算小圆圆心角并判断总个数。关键难点在于三角函数推导和精度处理，需注意特判n=1和小圆半径超过半桌面的情况。

---

### 精选题解分析

#### 题解1：Buried_Dream（4星）
**关键亮点**：
1. 完整处理了三种边界情况：小圆半径过大、n=1的特殊情况、圆半径超过桌面
2. 精度处理采用角度计算后加微小量判断
3. 代码结构清晰，包含完整输入输出处理

**核心代码思想**：
```cpp
double s = asin((double) r / (R - r));
if(Pr / s + 1e-12 > n) return puts("YES");
```

#### 题解2：wangyixuan_s_father（4星）
**关键亮点**：
1. 独创性的正多边形几何推导
2. 采用余弦定理替代主流解法中的正弦解法
3. 包含详细数学公式推导过程

**核心代码思想**：
```cpp
// 正n边形几何解法
R_min = r / cos((n-2)*0.5*pi/n) + r
if(R >= R_min) return YES
```

#### 题解3：Nightsky_Stars（3.5星）
**亮点**：
1. 代码简洁，包含必要特判
2. 使用long double提高精度
3. 注释清晰说明关键计算步骤

**调试心得**：
"这题有点卡精度" → 提醒需特别注意浮点运算误差

---

### 最优解题技巧总结
1. **几何建模**：构造大圆圆心、小圆圆心、切点组成的直角三角形
2. **三角函数应用**：sinθ = r/(R-r) → θ = 2*arcsin(r/(R-r))
3. **精度处理**：在最终比较时添加微小量（如1e-12）避免浮点误差
4. **特判机制**：
   - n=1时直接比较R≥r
   - r>R/2时只能放1个
   - r>R时绝对无法放置

---

### 拓展训练建议
相似题目推荐：
1. P1665 圆覆盖问题（几何覆盖判断）
2. P1516 青蛙的约会（扩展欧几里得+同余方程）
3. CF1114C 数论中的因子分解（数学问题转换）

---

### 题解个人心得摘录
1. "精度太屑了" → 强调几何问题必须考虑浮点精度处理
2. "被精度卡自闭了" → 提醒测试边界数据的重要性
3. "一遍过" → 展示正确建模的关键性
4. "疯狂特判" → 体现全面考虑边界条件的必要性

---
处理用时：44.43秒