# 题目信息

# Common Generator

## 题目描述

For two integers $ x $ and $ y $ ( $ x,y\ge 2 $ ), we will say that $ x $ is a generator of $ y $ if and only if $ x $ can be transformed to $ y $ by performing the following operation some number of times (possibly zero):

- Choose a divisor $ d $ ( $ d\ge 2 $ ) of $ x $ , then increase $ x $ by $ d $ .

For example,

- $ 3 $ is a generator of $ 8 $ since we can perform the following operations: $ 3 \xrightarrow{d = 3} 6 \xrightarrow{d = 2} 8 $ ;
- $ 4 $ is a generator of $ 10 $ since we can perform the following operations: $ 4 \xrightarrow{d = 4} 8 \xrightarrow{d = 2} 10 $ ;
- $ 5 $ is not a generator of $ 6 $ since we cannot transform $ 5 $ into $ 6 $ with the operation above.

Now, Kevin gives you an array $ a $ consisting of $ n $ pairwise distinct integers ( $ a_i\ge 2 $ ).

You have to find an integer $ x\ge 2 $ such that for each $ 1\le i\le n $ , $ x $ is a generator of $ a_i $ , or determine that such an integer does not exist.

## 说明/提示

In the first test case, for $ x=2 $ :

- $ 2 $ is a generator of $ 8 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 4} 8 $ ;
- $ 2 $ is a generator of $ 9 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 3} 9 $ .
- $ 2 $ is a generator of $ 10 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 2} 8 \xrightarrow{d = 2} 10 $ .

In the second test case, it can be proven that it is impossible to find a common generator of the four integers.

## 样例 #1

### 输入

```
4
3
8 9 10
4
2 3 4 5
2
147 154
5
3 6 8 25 100000```

### 输出

```
2
-1
7
3```

# AI分析结果



**唯一算法分类**: 数论  

---

### **综合分析与结论**  
**核心思路**：  
1. **质数处理**：质数只能由自身生成。若数组中有多个质数，无解。  
2. **合数处理**：2 能生成所有合数。若数组无质数，答案为 2。  
3. **唯一质数验证**：若数组恰有一个质数 p，需验证其他元素是否满足生成条件：  
   - **偶合数**：需满足 `x ≥ 2p`。  
   - **奇合数**：需满足 `x - p0 ≥ 2p`（`p0` 为 x 的最小质因子）。  

**关键公式与推导**：  
- **偶合数条件**：`x ≥ 2p`（直接通过连续加 2 生成）。  
- **奇合数条件**：`x - p0 ≥ 2p`（通过生成 `x - p0` 的偶数再一步操作）。  

**可视化设计思路**：  
- **像素动画**：展示生成路径（如 `p → 2p → ... → a_i`），高亮每一步的 `d` 和中间结果。  
- **条件判断**：用颜色区分偶数和奇合数，动态标注 `2p` 和 `x - p0` 的阈值比较。  
- **自动推导模式**：模拟自动生成路径，触发音效提示关键条件是否满足。  

---

### **题解清单 (≥4星)**  
1. **作者：_lmh_（5星）**  
   - **亮点**：严格数学证明引理，代码预处理 `rem` 数组高效判断条件，逻辑清晰。  
   - **代码核心**：线性筛预处理最小质因子，快速验证每个元素的条件。  

2. **作者：ny_jerry2（4星）**  
   - **亮点**：完整引理推导，代码简洁，直接使用线性筛预处理最小质因子。  
   - **关键代码**：通过 `num[next] = next - p[j]` 存储奇合数条件值。  

3. **作者：Exp10re（4星）**  
   - **亮点**：详细证明生成条件，结合贪心策略，代码直接判断奇偶条件。  

---

### **最优思路与代码实现**  
**关键思路**：  
- 预处理每个数的最小质因子 `p0`，计算奇合数的 `(x - p0)/2`。  
- 唯一质数验证时，只需检查所有元素的 `rem[x] ≥ p`。  

**代码片段**：  
```cpp
void initPrime(ll n=N-1){
    ok[1]=1;
    for (int i=2;i<N;++i){
        if (!ok[i]) prime[++nP]=i;
        for (int j=1;j<=nP&&i*prime[j]<=n;++j){
            ll o=i*prime[j];
            ok[o]=1;
            if (o%2==0) rem[o]=o/2;       // 偶合数：x/2
            else rem[o]=prime[j]*(i-1)/2; // 奇合数：(x - p0)/2
            if (i%prime[j]==0) break;
        }
    }
}
// 检查条件：所有非 p 的 a_i 满足 rem[a_i] >= p
for (int i=1;i<=n;++i) if (x!=a[i]&&rem[a[i]]<x) x=-1;
```

---

### **同类型题套路**  
- **质数生成条件**：质数只能由自身生成，多质数直接无解。  
- **合数生成规则**：偶数递推（加 2），奇数减最小质因子转偶数。  
- **预处理技巧**：线性筛预处理最小质因子加速条件判断。  

---

### **推荐题目**  
1. [CF1350B - Orac and Models](https://www.luogu.com.cn/problem/CF1350B)  
2. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)  
3. [CF1474C - Array Destruction](https://www.luogu.com.cn/problem/CF1474C)  

---

### **可视化与复古动画方案**  
**核心动画设计**：  
1. **像素风格界面**：  
   - **颜色方案**：8-bit 色调（深蓝背景，亮绿/红高亮关键值）。  
   - **Canvas 绘制**：每个数显示为像素块，质数红色，合数绿色，当前操作块黄色。  

2. **生成路径演示**：  
   - 动态展示 `p → 2p → ... → a_i` 的路径，每次操作高亮 `d` 和结果。  
   - 奇合数操作时，弹出 `p0` 提示并显示 `x - p0` 是否满足 `≥ 2p`。  

3. **音效与交互**：  
   - **音效**：成功生成时播放上扬音效，失败时短促提示。  
   - **步进控制**：支持暂停/继续，调节动画速度观察中间值。  

**代码片段（Canvas 绘制）**：  
```javascript
// 绘制数块示例
ctx.fillStyle = isPrime ? '#FF0000' : '#00FF00';
ctx.fillRect(x * 30, y * 30, 25, 25);
// 高亮当前操作
ctx.fillStyle = '#FFFF00';
ctx.fillRect(currentX * 30, currentY * 30, 25, 25);
```

---
处理用时：112.91秒