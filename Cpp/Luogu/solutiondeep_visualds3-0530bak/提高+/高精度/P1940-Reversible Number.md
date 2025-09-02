# 题目信息

# Reversible Number

## 题目背景

欧拉工程 145 有改动


## 题目描述

Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely of odd (decimal) digits. For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers reversible; so 36, 63, 409, and 904 are reversible. Leading zeroes are not allowed in either n or reverse(n).


There are 120 reversible numbers below one-thousand.


How many reversible numbers are there below one-billion (10^x)?



有些正整数n可能满足n + 回文(n)（回文(n)是把n倒过来写所得的数）得到的结果的各位都是奇数。

比方说，n=36时，36+63=99;


n=409时，409+904=1313。

规定满足上述的n称为reversible数。所以36,63,409,904都是reversible数。

当然，以0开头的数统统不算啦~


那么，小于等于10^x的Reversible数有多少个？方便起见，x是大于等于3小于等于400的正整数。


## 说明/提示

30%的数据的输出在2^32-1范围内


## 样例 #1

### 输入

```
rev1.in

4

```

### 输出

```
rev1.ans

720

```

# AI分析结果



---

## **算法分类**
数学与高精度计算

---

## **综合分析与结论**
### **核心思路**
题目要求计算小于 \(10^x\) 的可逆数数目。可逆数满足 \(n + \text{reverse}(n)\) 的每一位均为奇数，且不允许前导零。通过数学推导分两类情况讨论，结合高精度计算处理大数。

### **关键难点与解决**
1. **数学推导**：
   - **奇偶性约束**：每个进位必须保持结果的每一位为奇数。需分位数奇偶性、进位情况讨论。
   - **组合数公式**：
     - **偶数位数**：每位对称为不进位奇数，公式为 \(20 \times 30^{(i-2)/2}\)。
     - **模4余3位数**：中间位特殊处理，公式为 \(20 \times 5 \times (500)^{(i-3)/4}\)。

2. **高精度实现**：
   - 自定义 `BigInt` 结构体处理大数乘法和加法，避免溢出。

### **可视化设计**
- **动画方案**：
  - **像素风格**：用不同颜色块表示不同位数类型（偶数为蓝色，模4余3为绿色）。
  - **步进控制**：展示每个 \(i\) 的计算步骤，高亮当前位数及公式推导。
  - **音效提示**：进位时播放“点击”音效，完成计算后播放成功音效。
- **Canvas 演示**：动态绘制公式推导过程，展示组合数计算和累加结果。

---

## **题解评分（4星）**
**阿丑题解（4星）**  
- **亮点**：数学推导清晰，高精度实现简洁，通过分情况讨论大幅优化时间复杂度。
- **不足**：数学部分存在笔误（如公式中的幂次基数应为30而非25），但代码正确。

---

## **最优思路提炼**
1. **数学分型**：将位数按奇偶和模4分类，推导组合数公式。
2. **高精度优化**：避免暴力枚举，直接公式计算，时间复杂度 \(O(x)\)。

---

## **相似题目推荐**
1. **P1255 数楼梯**（高精度递推）
2. **P1601 A+B Problem（高精）**（高精度加法）
3. **P1217 回文质数**（数学性质与回文数）

---

## **代码实现**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400+20;
struct BigInt {
    int a[N], len;
    void carry() { // 进位处理
        for(int i=0; i<len; i++) {
            a[i+1] += a[i]/10;
            a[i] %= 10;
            if(a[len]) len++;
        }
    }
    BigInt operator = (int x) { // 低精度赋值
        memset(a, 0, sizeof(a));
        len = 1, a[0] = x;
        carry();
        return *this;
    }
    BigInt operator * (int x) { // 高精乘低精
        BigInt res = *this;
        for(int i=0; i<res.len; i++) res.a[i] *= x;
        res.carry();
        return res;
    }
    BigInt operator + (const BigInt& t) { // 高精加高精
        BigInt res = *this;
        res.len = max(len, t.len);
        for(int i=0; i<res.len; i++) res.a[i] += t.a[i];
        res.carry();
        return res;
    }
    void output() { for(int i=len-1; i>=0; i--) printf("%d", a[i]); }
} ans;

int main() {
    int x; scanf("%d", &x);
    ans = 0;
    for(int i=1; i<=x; i++) {
        if(i % 2 == 0) { // 偶数位数情况
            BigInt tmp = 20;
            for(int j=1; j<=(i-2)/2; j++) tmp = tmp * 30;
            ans = ans + tmp;
        } else if(i % 4 == 3) { // 模4余3位数情况
            BigInt tmp = 20 * 5;
            for(int j=1; j<=(i-3)/4; j++) tmp = tmp * 500;
            ans = ans + tmp;
        }
    }
    ans.output();
    return 0;
}
```

---

## **可视化示例**
### **动画流程**
1. **输入x=4**，展示计算步骤：
   - **i=2**：20（蓝色块），播放“点击”音效。
   - **i=3**：100（绿色块），音效增强。
   - **i=4**：600（蓝色块），累计结果720，播放成功音效。
2. **Canvas动态更新**：右侧显示当前公式和计算结果。

### **像素风格**
- **位数类型**：蓝色（偶数）、绿色（模4余3）。
- **音效**：8位音效库，对应不同操作类型。

---

**关键思路通过数学分型与高效公式解决，避免暴力枚举，适合大范围计算。**

---
处理用时：145.54秒