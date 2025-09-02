# 题目信息

# Shohag Loves XOR (Hard Version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ x \oplus y $ is divisible $ ^{\text{∗}} $ by either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ a $ is divisible by the number $ b $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 说明/提示

In the first test case, for $ x = 7 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 10 $ , and they are $ 1 $ , $ 7 $ , and $ 9 $ .

- $ y = 1 $ is valid because $ x \oplus y = 7 \oplus 1 = 6 $ and $ 6 $ is divisible by $ y = 1 $ .
- $ y = 7 $ is valid because $ x \oplus y = 7 \oplus 7 = 0 $ and $ 0 $ is divisible by both $ x = 7 $ and $ y = 7 $ .
- $ y = 9 $ is valid because $ x \oplus y = 7 \oplus 9 = 14 $ and $ 14 $ is divisible by $ x = 7 $ .

## 样例 #1

### 输入

```
5
7 10
2 3
6 4
1 6
4 1```

### 输出

```
3
2
2
6
1```

# AI分析结果



**唯一算法分类**：位运算与数学分析

---

### **题解思路与解决难点**

**核心思路**：
1. **分治处理**：将y分为两部分处理：
   - **低位（y < 2^b）**：暴力枚举，直接判断是否满足条件。
   - **高位（y ≥ 2^b）**：利用异或性质，仅需统计x的倍数对应的k值，通过数学公式快速计算合法数量。

**关键变量**：
- `t = 2^b`：b为x的最高二进制位+1，如x=7（111），则b=3，t=8。此时，若y ≥ t，异或结果的高位固定，无法被y整除。

**解决难点**：
- **暴力枚举的优化**：对于y < t的情况直接暴力枚举，时间复杂度O(t)。
- **高位数学分析**：当y ≥ t时，x⊕y必须是x的倍数，即x⊕y = kx。解得y = kx ⊕ x，进一步推导k的取值范围为1 ≤ kx ⊕ x ≤ m，转化为k的统计问题。
- **边界处理**：通过二分法或近似公式快速计算合法k的范围，并修正边界附近的误差。

---

### **题解评分（≥4星）**

1. **littlebug（4星）**：
   - **亮点**：利用最高位分治，二分法加速统计，边界修正确保正确。
   - **代码优化**：通过`gm(x)`快速计算t，二分法处理高位部分，暴力修正最后10个值。

2. **LiJoQiao（4星）**：
   - **亮点**：详细分类讨论，数学推导k的范围，避免重复计数。
   - **代码逻辑**：分情况处理x异或y整除x或y的情况，枚举验证边界。

3. **SUNCHAOYI（4星）**：
   - **亮点**：结合异或性质与数学分析，分两种情况统计。
   - **代码简洁性**：直接枚举y ≤ x和k的范围，通过循环验证边界。

---

### **最优思路提炼**

1. **最高位分治**：
   - 计算x的最高二进制位b，构造t=2^(b+1)。
   - y < t时暴力枚举，y ≥ t时仅需统计x的倍数。

2. **数学推导高位部分**：
   - 对于y ≥ t，x⊕y必须是x的倍数，即x⊕y = kx → y = kx ⊕ x。
   - k的取值范围：1 ≤ k ≤ m/x + 1，通过二分或公式快速计算合法k值。

3. **边界修正**：
   - 二分法可能因单调性不完美导致误差，需暴力验证最后10个值。

---

### **相似题目推荐**
1. [CF1772D](https://www.luogu.com.cn/problem/CF1772D)：位运算与数学分析结合。
2. [P2114](https://www.luogu.com.cn/problem/P2114)：异或性质与统计问题。
3. [CF1847C](https://www.luogu.com.cn/problem/CF1847C)：最高位分治处理异或问题。

---

### **可视化与算法演示**

**动画设计**：
- **像素风格界面**：左侧显示二进制位网格，右侧为统计结果。
- **关键步骤**：
  1. **低位枚举**：红色方块遍历y=1到t，绿色表示合法。
  2. **高位计算**：蓝色方块表示k值，黄色箭头显示kx⊕x的生成过程。
  3. **边界修正**：闪烁提示最后10个k值的暴力验证。

**音效与交互**：
- **音效**：合法值触发“叮”声，错误值触发“哔”声。
- **自动演示**：播放/暂停按钮控制算法流程，速度调节支持慢放观察。

**代码片段（关键逻辑）**：
```cpp
// 计算最高位构造的t
int gm(int x) {
    int ans = 0;
    while (x) ans++, x >>= 1;
    return (1LL << ans) - 1;
}

// 二分法统计合法k值
int l = 1, r = m / x + 100;
while (l < r) {
    int mid = (l + r + 1) >> 1;
    (x * mid ^ x) <= m ? l = mid : r = mid - 1;
}
cnt += l - 1;

// 修正边界
for (int i = l - 10; i <= l + 10; i++) {
    if ((x * i ^ x) <= m) cnt++;
}
```

---

### **总结**
通过分治与数学推导，将问题复杂度从O(m)优化至O(log m)，显著提升效率。关键点在于最高位分治与异或性质的应用，结合二分法与暴力修正确保正确性。

---
处理用时：100.04秒