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



**唯一算法分类**: 组合数学

---

### **题解思路与解决难点**

#### **核心思路**
所有题解均基于以下关键观察：
- 子序列的中位数为1 ⇨ 子序列中1的数量 ≥ m = (k+1)/2  
- 统计所有满足条件的子序列数目 ⇨ 组合数求和：  
  `sum( C(cnt1, i) * C(cnt0, k-i) )`，其中i ∈ [m, k]

#### **算法实现要点**
1. **预处理阶乘与逆元**：  
   - 预计算阶乘数组 `fact[]` 和逆元数组 `inv[]`  
   - 使用费马小定理快速计算逆元：`inv[i] = fact[i]^(MOD-2) % MOD`  
   - 核心函数 `C(n, m)` 通过 `fact[n] * inv[m] * inv[n-m] % MOD` 实现O(1)组合数查询  

2. **边界处理**：  
   - 当 `n < m` 或 `m < 0` 时返回0  
   - 枚举i的范围为 `[m, min(k, cnt1)]`，避免无效计算  

#### **解决难点**
- **大数取模下的组合数计算**：通过预处理阶乘和逆元避免重复计算  
- **高效处理多组测试数据**：预处理阶乘仅需一次，每组数据只需统计0/1数量并枚举i  

---

### **题解评分 (≥4星)**

1. **aeiouaoeiu (4.5星)**  
   - **亮点**：代码简洁，预处理阶乘和逆元方式高效，边界处理清晰  
   - **代码可读性**：变量命名明确，组合数函数封装合理  
   - **核心代码**：
     ```cpp
     ll C(ll a,ll b){ return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p; }
     ```

2. **cjh20090318 (4星)**  
   - **亮点**：快速幂逆元与阶乘预处理分离，注释清晰  
   - **优化点**：处理逆元时直接复用阶乘数组，减少计算量  
   - **关键逻辑**：
     ```cpp
     inv[maxn-5] = qpow(fact[maxn-5], MOD-2);
     for (int i = maxn-6; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % MOD;
     ```

3. **PineappleSummer (4星)**  
   - **亮点**：代码模块化，预处理与计算逻辑分离  
   - **实践性**：直接给出核心循环，便于快速理解算法流程  
   - **代码片段**：
     ```cpp
     for (int i = k / 2 + 1; i <= k; i++)
         ans = (ans + C(cnt, i) * C(n - cnt, k - i)) % mod;
     ```

---

### **最优思路与技巧提炼**

1. **组合数预处理模板**  
   ```cpp
   fact[0] = 1;
   for (int i=1; i<=N; i++) fact[i] = fact[i-1] * i % MOD;
   inv[N] = qpow(fact[N], MOD-2);
   for (int i=N-1; i>=0; i--) inv[i] = inv[i+1] * (i+1) % MOD;
   ```

2. **枚举条件优化**  
   - 枚举i的范围为 `max(m, k - cnt0)` 到 `min(k, cnt1)`，避免无效循环  

3. **二进制特性利用**  
   - 仅需统计0/1数量，无需关心具体位置，将问题转化为纯组合计数  

---

### **相似题目推荐**

1. [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)  
   - **相似点**：组合数取模计算，大数处理  

2. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)  
   - **相似点**：利用二项式定理与组合数求解多项式系数  

3. [P3197 越狱](https://www.luogu.com.cn/problem/P3197)  
   - **相似点**：组合数学逆向思维，快速幂优化  

---

### **可视化与算法演示设计**

#### **动画方案**
1. **初始界面**  
   - 左侧显示原数组（0/1用不同颜色方块表示）  
   - 右侧显示动态组合数计算过程  

2. **关键步骤演示**  
   - **步骤1**：统计0/1数量，显示 `cnt0` 和 `cnt1`  
   - **步骤2**：枚举i值，高亮当前i对应的组合数项 `C(cnt1, i)` 和 `C(cnt0, k-i)`  
   - **步骤3**：动态累加结果，显示当前总和与贡献值  

3. **复古像素风格**  
   - **颜色方案**：1用绿色像素块，0用红色像素块，当前选中项用黄色边框  
   - **音效**：  
     - 枚举i时播放短促"滴"声  
     - 计算组合数时播放"咔嗒"声  
     - 累加成功时播放上升音阶  

4. **交互控制**  
   - **速度调节**：滑动条控制动画速度（1x-5x）  
   - **单步执行**：按钮手动触发下一步  
   - **自动模式**：AI自动演示，动态显示i的取值范围变化  

#### **核心JavaScript片段**
```javascript
// 绘制像素化数组
function drawArray(arr, ctx) {
    arr.forEach((num, idx) => {
        ctx.fillStyle = num === 1 ? '#00FF00' : '#FF0000';
        ctx.fillRect(idx * 20, 0, 18, 18);
    });
}

// 组合数计算动画
async function animateCombination(cnt1, cnt0, k) {
    let sum = 0;
    for (let i = Math.ceil(k/2); i <= k; i++) {
        // 高亮当前i值
        highlightCurrent(i);
        // 计算组合数并播放音效
        const c1 = combination(cnt1, i);
        const c0 = combination(cnt0, k - i);
        sum += c1 * c0;
        // 更新界面显示
        updateSumDisplay(sum);
        await sleep(animationSpeed);
    }
}
```

---

### **总结**
本题通过组合数学将问题转化为枚举符合条件的1的数量，利用预处理阶乘和逆元优化计算效率。核心代码模板可广泛应用于需快速计算组合数的场景。可视化设计通过像素风格和音效增强学习趣味性，帮助理解动态枚举过程。

---
处理用时：82.65秒