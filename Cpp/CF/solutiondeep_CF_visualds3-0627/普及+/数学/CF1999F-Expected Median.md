# 题目信息

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# AI分析结果



## 唯一算法分类  
**组合数学**

---

## 综合分析与结论  
**题目核心**：计算所有长度为k的二进制数组子序列的中位数之和。  
**关键公式**：中位数为1的条件是子序列中1的数量 ≥ m = (k+1)/2。  
**数学转化**：答案等价于所有满足条件的子序列数量之和，即：  
$$\text{ans} = \sum_{i=m}^k \binom{c_1}{i} \cdot \binom{c_0}{k-i}$$  
其中，c₁为原数组1的数量，c₀为0的数量。  

**解决难点**：  
1. **组合数预处理**：通过阶乘和逆元预处理实现O(1)查询组合数。  
2. **边界处理**：当i超过c₁或k-i超过c₀时组合数为0，需跳过。  

**可视化设计**：  
- **动态柱状图**：展示每个i对应的组合数值（C(c₁,i)和C(c₀,k-i)）及乘积。  
- **颜色高亮**：当前计算的i值以高亮显示，乘积结果以不同颜色叠加。  
- **复古像素风格**：使用8位像素动画，每次计算时播放音效，总和以像素数字递增。  

---

## 题解清单 (≥4星)  
1. **aeiouaoeiu（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码结构清晰，预处理阶乘和逆元，直接计算核心公式。  
   - **代码**：使用预处理的阶乘数组和逆元数组，循环简洁。  

2. **Pink_Cut_Tree（⭐⭐⭐⭐）**  
   - **亮点**：快速幂求逆元，代码可读性高。  
   - **心得**：明确将问题转化为组合数求和，注释清晰。  

3. **cjh20090318（⭐⭐⭐⭐）**  
   - **亮点**：优化逆元计算顺序，预处理阶乘逆元。  
   - **技巧**：利用逆元递推公式减少计算量。  

---

## 最优思路与技巧提炼  
**关键步骤**：  
1. 统计原数组中1的数量c₁和0的数量c₀。  
2. 预处理阶乘fact和逆元inv数组，快速计算组合数C(n, k)。  
3. 遍历i从m到min(k, c₁)，累加组合数乘积。  

**代码片段**：  
```cpp  
// 预处理阶乘和逆元  
fact[0] = 1;  
for(int i=1; i<maxn; i++) fact[i] = fact[i-1] * i % mod;  
inv[maxn-1] = qpow(fact[maxn-1], mod-2);  
for(int i=maxn-2; i>=0; i--) inv[i] = inv[i+1] * (i+1) % mod;  

// 计算组合数  
ll C(ll a, ll b) {  
    return (a < b || b < 0) ? 0 : fact[a] * inv[b] % mod * inv[a-b] % mod;  
}  

// 主计算逻辑  
for(int i=m; i<=k; i++)  
    ans = (ans + C(c1, i) * C(c0, k-i)) % mod;  
```

---

## 类似题目推荐  
1. **P1771 组合数问题**（组合数预处理与应用）  
2. **CF1342E Placing Rooks**（组合数模型转化）  
3. **AT_abc132E Hopscotch Addict**（组合计数与模运算）  

---

## 个人心得摘录  
- **调试教训**：组合数边界处理易错，需严格判断i ≤ c₁且k-i ≤ c₀。  
- **优化顿悟**：预处理逆元数组时，反向递推比单独计算更快。  

---

## 可视化算法演示  
**复古像素动画设计**：  
1. **界面布局**：  
   - 左侧显示原数组（0/1像素块），右侧显示当前i值和累加结果。  
   - 底部动态柱状图展示C(c₁,i)和C(c₀,k-i)的值。  

2. **交互设计**：  
   - **步进控制**：按空格单步执行i的遍历。  
   - **音效**：计算成功时播放8-bit音效，错误时播放低沉音。  
   - **自动模式**：AI自动推导流程，类似贪吃蛇路径演示。  

**代码片段（Canvas绘制）**：  
```javascript  
// 绘制组合数柱状图  
function drawBars(i, c1, c0, k) {  
    ctx.fillStyle = '#FF0000';  
    ctx.fillRect(100, 200, 50, C(c1, i) * 2); // 红色柱：C(c1,i)  
    ctx.fillStyle = '#00FF00';  
    ctx.fillRect(160, 200, 50, C(c0, k-i) * 2); // 绿色柱：C(c0,k-i)  
}  
```  

**音效触发**：  
```javascript  
// 成功音效（8-bit风格）  
const successSound = new Audio('data:audio/wav;base64,UklGRl9...');  
successSound.play();  
```  

--- 

通过上述设计，学习者可直观理解组合数求和过程，并通过交互深入掌握核心数学逻辑。

---
处理用时：76.75秒