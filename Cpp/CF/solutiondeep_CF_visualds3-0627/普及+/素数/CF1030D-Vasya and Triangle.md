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



**唯一算法分类**：数论（最大公约数与因数分解）

---

### **题解思路、算法要点与解决难点**

**核心思路**：构造以原点为直角顶点的直角三角形，面积为 $\frac{nm}{k}$。  
**关键条件**：$2nm \bmod k = 0$（否则无解）。通过分解 $k$ 的因数分配到 $n$ 和 $m$ 中，调整 $x$ 和 $y$ 的值满足范围限制。

**解决难点**：
1. **因数分配**：将 $k$ 的质因数分解到 $n$ 和 $m$ 的因子中，确保 $x=\frac{2n}{\gcd(2n,k)}$ 和 $y=\frac{m}{\frac{k}{\gcd(2n,k)}}$ 不越界。
2. **奇偶调整**：当 $k$ 为奇数时，需调整 $x$ 或 $y$ 的倍数以满足条件。

---

### **题解评分 (≥4星)**

1. **da32s1da (★★★★★)**  
   - **亮点**：简洁利用 GCD 分解因数，逻辑清晰，代码高效。直接通过调整因数倍数解决边界问题。
   - **代码**：通过计算 $\gcd(2n, k)$ 快速分配因数，处理奇偶情况灵活。

2. **DJRzjl (★★★★☆)**  
   - **亮点**：分奇偶讨论，质因数分解后动态调整，确保可行性。提供详细数学证明。
   - **优化点**：质因数分解可能增加复杂度，但通过分治优化。

3. **wjyyy (★★★★☆)**  
   - **亮点**：结合皮克定理的严格证明，上下界优化避免超时。强调面积必须为 $\frac{1}{2}$ 的倍数。
   - **心得**：调试中处理了质因数分解的边界情况，强调枚举起始点的优化。

---

### **最优思路或技巧提炼**

1. **数学推导**：利用直角三角形的面积公式 $S = \frac{xy}{2}$，转化为 $xy = \frac{2nm}{k}$。
2. **因数分配**：通过 $\gcd$ 分解 $k$ 的因数到 $n$ 和 $m$，确保 $x \leq n$ 和 $y \leq m$。
3. **调整策略**：若 $x$ 越界，则将其减半并倍增 $y$（或反之），保持乘积不变。

**代码片段（da32s1da）**：
```cpp
LL gcd(LL u,LL v){return v?gcd(v,u%v):u;}
int main(){
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    if(k/gcd(n*m,k)>2) puts("NO"); // 判断无解
    else {
        X=(2*n)/gcd(2*n,k);
        if(X>n) X/=2, m*=2; // 调整越界的X
        Y=m/(k/gcd(2*n,k));
        printf("0 0\n%I64d 0\n0 %I64d\n",X,Y);
    }
}
```

---

### **同类型题或类似算法套路**

- **因数分解与构造**：类似问题需将目标值分解为两个数的乘积，并满足范围限制。
- **几何构造**：利用坐标系特性（如原点、轴对齐）简化问题。

**推荐题目**：
1. [CF1114C - Trailing Loves (or L'oeufs?)](https://www.luogu.com.cn/problem/CF1114C)（因数分解）
2. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)（数论优化）
3. [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)（格点与GCD）

---

### **可视化与算法演示**

**动画方案**：
1. **像素风格网格**：绘制 $n \times m$ 网格，原点高亮。
2. **因数分解步骤**：以动态颜色块表示 $k$ 的因数分配到 $n$ 和 $m$。
3. **调整过程**：若 $x$ 越界，动画显示 $x$ 减半和 $y$ 倍增的步骤，保持乘积不变。
4. **音效**：分解成功时播放上升音效，调整时播放“点击”音效。

**交互设计**：
- **步进控制**：允许单步观察因数分配和调整。
- **自动模式**：AI 自动完成因数分解和调整，类似贪吃蛇路径搜索。
- **失败提示**：无解时播放低沉音效，显示红色提示框。

---

### **个人心得摘录**

- **调试经验**：枚举 $x$ 时需从 $\sqrt{S}$ 开始，避免超时（wjyyy）。
- **数学直觉**：面积必须为 $\frac{1}{2}$ 的倍数是解题突破口（DJRzjl）。

---
处理用时：100.27秒