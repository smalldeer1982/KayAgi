# 题目信息

# Carousel of Combinations

## 题目描述

You are given an integer $ n $ . The function $ C(i,k) $ represents the number of distinct ways you can select $ k $ distinct numbers from the set { $ 1, 2, \ldots, i $ } and arrange them in a circle $ ^\dagger $ .

Find the value of 
$$
\sum\limits_{i=1}^n \sum\limits_{j=1}^i \left( C(i,j) \bmod j \right)
$$
Here, the operation  $ x \\bmod y $  denotes the remainder from dividing  $ x $  by  $ y $ .</p><p>Since this value can be very large, find it modulo  $ 10^9+7 $ .</p><p> $ ^\\dagger $  In a circular arrangement, sequences are considered identical if one can be rotated to match the other. For instance,  $ \[1, 2, 3\] $  and  $ \[2, 3, 1\]$$$ are equivalent in a circle.

## 说明/提示

In the first test case, $ C(1,1) \bmod 1 = 0 $ .

In the second test case:

- $ C(1,1)=1 $ (the arrangements are: $ [1] $ );
- $ C(2,1)=2 $ (the arrangements are: $ [1] $ , $ [2] $ );
- $ C(2,2)=1 $ (the arrangements are: $ [1, 2] $ );
- $ C(3,1)=3 $ (the arrangements are: $ [1] $ , $ [2] $ , $ [3] $ );
- $ C(3,2)=3 $ (the arrangements are: $ [1, 2] $ , $ [2, 3] $ , $ [3, 1] $ );
- $ C(3,3)=2 $ (the arrangements are: $ [1, 2, 3] $ , $ [1, 3, 2] $ ).

 In total, $ \left(C(1,1) \bmod 1\right) + \left(C(2,1) \bmod 1\right) + \left(C(2,2) \bmod 2\right) + \left(C(3,1) \bmod 1\right) + \left(C(3,2) \bmod 2\right) + \left(C(3,3) \bmod 3\right) = 4 $ .

## 样例 #1

### 输入

```
4
1
3
6
314159```

### 输出

```
0
4
24
78926217```

# AI分析结果



**唯一算法分类**：数论 + 预处理/差分数组

---

### **综合分析与结论**

**核心思路**：  
题目要求计算双重求和式 $\sum_{i=1}^n \sum_{j=1}^i (C(i,j) \bmod j)$，其中 $C(i,j)$ 是圆排列数。通过数论分析发现：  
1. **威尔逊定理**：当 $j$ 为质数时，$(j-1)! \equiv -1 \pmod j$；  
2. **特殊处理**：$j=4$ 时 $(j-1)! \equiv 2 \pmod 4$；  
3. **合数贡献**：其他合数的贡献为 $0$。  

利用差分数组预处理每个质数和 $j=4$ 的贡献，最终通过两次前缀和得到答案。

**关键难点**：  
1. **快速推导模结果**：结合卢卡斯定理简化组合数模运算；  
2. **高效预处理**：对每个质数 $j$ 的贡献区间进行差分标记，避免重复计算；  
3. **复杂度优化**：通过调和级数性质实现 $O(n \log \log n)$ 预处理。

---

### **题解清单 (≥4星)**

1. **William2022 (5星)**  
   - **亮点**：公式推导清晰，完整代码实现差分数组，预处理逻辑简洁。  
   - **关键点**：利用差分数组标记区间贡献，两次前缀和完成答案计算。  

2. **沉石鱼惊旋 (5星)**  
   - **亮点**：详细解释数论定理的应用，强调质数与 $j=4$ 的特殊处理。  
   - **心得**：“多打表发现规律，不要随便化简式子”体现调试经验。  

3. **Starrykiller (4星)**  
   - **亮点**：代码结构清晰，单独处理 $j=4$ 的贡献。  
   - **技巧**：使用 `__int128` 避免大数溢出。

---

### **最优思路与代码实现**

**核心代码片段**：  
```cpp
const int N = 1e6;
ll a[N+5]; // 差分数组

// 处理质数j的贡献
void solve(int p) {
    for (int i = p; i <= N; i += p) {
        int l = i, r = min(i + p - 1, N);
        int val = (i / p * (p - 1)) % p;
        a[l] = (a[l] + val) % mod;
        a[r+1] = (a[r+1] - val + mod) % mod;
    }
}

// 处理j=4的贡献
void solve4() {
    for (int i = 4; i <= N; i += 4) {
        int val = (i / 4 * 2) % 4;
        a[i] = (a[i] + val) % mod;
        a[i+4] = (a[i+4] - val + mod) % mod;
    }
}

int main() {
    // 预处理质数
    sieve();
    for (int p : primes) solve(p);
    solve4();
    
    // 计算前缀和
    for (int i=1; i<=N; ++i) a[i] = (a[i] + a[i-1]) % mod; // 差分转原数组
    for (int i=1; i<=N; ++i) a[i] = (a[i] + a[i-1]) % mod; // 原数组转前缀和
}
```

**实现思想**：  
1. **差分数组标记**：对每个质数 $j$，将其贡献分段标记到差分数组中；  
2. **两次前缀和**：第一次将差分转为原数组，第二次计算前缀和得到最终答案；  
3. **特殊处理j=4**：单独计算其贡献并合并到差分数组中。

---

### **可视化设计要点**

**动画方案**：  
1. **像素风格展示**：  
   - **颜色标记**：质数贡献区间用绿色高亮，$j=4$ 用蓝色标记。  
   - **网格绘制**：在 Canvas 上绘制 $n \times n$ 的网格，横向为 $i$，纵向为 $j$。  

2. **关键步骤演示**：  
   - **差分更新**：当处理质数 $j$ 时，动画显示区间 $[kj, (k+1)j)$ 被标记，并更新差分数组。  
   - **前缀和计算**：用流动的光标从左到右累加差分数组，展示两次前缀和的过程。  

3. **音效提示**：  
   - **区间标记**：播放短促的“滴”声；  
   - **质数处理完成**：播放上升音调；  
   - **计算完成**：播放 8-bit 胜利音效。  

**交互设计**：  
- **速度控制**：滑动条调节动画速度（1x, 2x, 5x）；  
- **单步执行**：允许用户逐步查看每个质数的贡献区间；  
- **自动演示**：AI 模式自动遍历所有质数和 $j=4$ 的处理。  

---

### **相似题目推荐**

1. **P3912 素数个数**（质数筛法应用）  
2. **P2424 约数和**（调和级数求和与差分）  
3. **P2261 余数求和**（分块处理模运算）

---

**总结**：本题通过数论定理与差分数组的巧妙结合，将复杂问题转化为高效预处理问题。可视化设计通过像素动画和音效，直观展示了数学定理与算法优化的协同作用。

---
处理用时：61.40秒