# 题目信息

# Fractal Origami

## 题目描述

You have a square piece of paper with a side length equal to $ 1 $ unit. In one operation, you fold each corner of the square to the center of the paper, thus forming another square with a side length equal to $ \dfrac{1}{\sqrt{2}} $ units. By taking this square as a new square, you do the operation again and repeat this process a total of $ N $ times.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/de3bbf1154da54ac557ac761cc9644c6d1e0f30d.png) Performing operations for $ N = 2 $ .After performing the set of operations, you open the paper with the same side up you started with and see some crease lines on it. Every crease line is one of two types: a mountain or a valley. A mountain is when the paper folds outward, and a valley is when the paper folds inward.

You calculate the sum of the length of all mountain crease lines on the paper and call it $ M $ . Similarly, you calculate for valley crease lines and call it $ V $ . You want to find the value of $ \dfrac{M}{V} $ .

It can be proved that this value can be represented in the form of $ A + B\sqrt{2} $ , where $ A $ and $ B $ are rational numbers. Let this $ B $ be represented as an irreducible fraction $ \dfrac{p}{q} $ , your task is to print $ p*inv(q) $ modulo $ 999\,999\,893 $ (note the unusual modulo), where $ inv(q) $ is the [modular inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse) of $ q $ .

## 说明/提示

The blue lines in the given figures represent mountain crease lines, and the green lines represent valley crease lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/656ef1e31fbec994532b6ed88e854868aee0bb9e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1924C/4d56d193615060ea6202f89c8971139a2bc8d811.png)Crease lines after $ 1 $ operation $ (\dfrac{M}{V} = 0) $ .Crease lines after $ 2 $ operations $ (\dfrac{M}{V} = \sqrt{2} - 1) $ .

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
1
714285638```

# AI分析结果



## 数学分类选择  
**几何**

---

## 题解思路、算法要点与解决难点  
### 核心思路
所有题解均围绕以下关键发现展开：
1. **折痕对称性**：从第2次折叠开始，每次新增的山折（M）和谷折（V）长度相等。
2. **等比增长规律**：每次折叠的折痕总长度是前一次的 $\sqrt{2}$ 倍。
3. **首项差异**：首次折叠仅产生谷折 $V=2\sqrt{2}$，后续每次折叠同时增加等量的M和V。

### 数学推导
- **总折痕公式**：总折痕长度 $M+V$ 构成等比数列，公比 $q=\sqrt{2}$，首项 $a=2\sqrt{2}$。  
- **拆分关系**：$V = M + 2\sqrt{2}$，通过等比求和公式得出 $M$ 和 $V$ 的表达式。
- **分母有理化**：将 $\frac{M}{V}$ 转换为 $A+B\sqrt{2}$ 形式后，分离出系数 $B$ 并计算其模逆。

### 代码实现
- **快速幂加速**：计算 $\sqrt{2}^n$ 时利用快速幂优化。
- **扩域运算**：部分题解实现 $a+b\sqrt{2}$ 的类，支持加减乘除和模运算。
- **奇偶分治**：根据 $n$ 的奇偶性选择不同公式简化计算。

---

## 题解评分 (≥4星)  
1. **EuphoricStar (5星)**  
   - **亮点**：发现M与V的对称性，直接推导等比公式，代码清晰易读。  
   - **代码**：实现扩域类，完美处理含 $\sqrt{2}$ 的运算。

2. **MaxBlazeResFire (4星)**  
   - **亮点**：分奇偶讨论快速得出通项，代码简洁高效。  
   - **技巧**：通过分治避免复杂的有理化操作。

3. **lalaouye (4星)**  
   - **亮点**：构建递推关系 $f_i = \frac{f_{i-1} + g_{i-1}}}{\sqrt{2}} + 1$，数学推导严密。  
   - **优化**：利用递推式转化为矩阵快速幂问题。

---

## 最优思路或技巧提炼  
1. **对称性观察**：从第2次折叠开始，每次新增的M和V长度相等，将问题简化为求总和与差值。  
2. **等比模型**：总折痕长度构成公比为 $\sqrt{2}$ 的等比数列，直接套用求和公式。  
3. **扩域运算**：将 $a+b\sqrt{2}$ 封装为类，支持模运算，避免手动有理化。  
4. **奇偶分治**：根据 $n$ 的奇偶性选择不同表达式，简化计算流程。

---

## 同类型题或类似算法套路  
1. **几何递推**：分析分形或自相似结构中的几何规律（如科赫曲线）。  
2. **模逆运算**：处理含分母的模运算时，利用费马小定理求逆元。  
3. **扩域处理**：在涉及无理数的运算中，定义代数结构封装运算（如 $\mathbb{Q}(\sqrt{2})$）。

---

## 推荐相似题目  
1. **P1226 【模板】快速幂**（快速幂基础）  
2. **P2613 【模板】有理数取余**（模逆运算应用）  
3. **P1498 分形曲线**（分形几何递推）

---

## 个人心得摘录  
- **EuphoricStar**：*“手动折叠发现n=3时的M和V值，大胆猜测对称性规律”* → 实验观察是发现数学规律的关键。  
- **Z1qqurat**：*“差点放弃，但通过手工折纸顿悟增量规律”* → 物理模拟辅助抽象问题。  
- **UnyieldingTrilobite**：*“定义z_i简化递推式，避免直接处理复杂分式”* → 变量替换是化简递推的利器。

---

## 可视化与算法演示  
### 动画设计  
- **像素风格折纸模拟**：用8-bit色块展示每次折叠后的纸张层数（红绿区分M/V）。  
- **公式推导面板**：左侧画布显示折纸过程，右侧分步显示当前计算的公式项（如等比求和）。  
- **关键步骤高亮**：  
  - 首次折叠时显示 $V=2\sqrt{2}$ 的绿色线段。  
  - 后续折叠时用闪烁效果标记新增的等量M/V折痕。  
  - 最终比例计算时，用流动边框突出分母有理化步骤。  

### 代码片段（扩域类实现）  
```cpp
struct ExtNumber {
    int a, b; // 表示 a + b√2
    ExtNumber(int a, int b) : a(a%mod), b(b%mod) {}
    ExtNumber operator*(const ExtNumber& o) const {
        return ExtNumber(
            (1LL*a*o.a + 2LL*b*o.b) % mod,
            (1LL*a*o.b + 1LL*b*o.a) % mod
        );
    }
    ExtNumber inv() const {
        int den = (1LL*a*a - 2LL*b*b) % mod;
        den = (den + mod) % mod;
        int inv_den = pow(den, mod-2); // 费马小定理求逆
        return ExtNumber(1LL*a*inv_den % mod, (mod - 1LL*b*inv_den % mod) % mod);
    }
};
```

---

## 复古游戏化设计  
1. **8-bit音效**：  
   - 折叠音效：类似NES《俄罗斯方块》的方块旋转声。  
   - 正确计算：马里奥吃金币的“叮咚”声。  
   - 错误提示：经典Zelda谜题错误音。  
2. **积分系统**：  
   - 每正确折叠一次得10分，连续正确折叠触发连击倍率。  
   - 最终答案正确时播放通关动画（像素烟花+16-bit音乐）。  
3. **自动推导AI**：  
   - 模拟“贪吃蛇”路径规划，自动展开公式推导步骤。  
   - 每步推导后显示当前分数和剩余步数进度条。

---
处理用时：91.48秒