# 题目信息

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
111111011
2
```

### 输出

```
169
```

# AI分析结果



**唯一算法分类**  
数位动态规划（数位DP）  

---

### **题解思路、算法要点与解决难点**  
**核心逻辑**：  
1. **预处理操作次数**：  
   - 由于第一次操作后的数 ≤ 1000，预处理所有数变为 1 的最小操作次数 `cnt[]`。  
   - 递推公式：`cnt[i] = cnt[sum[i]] + 1`，其中 `sum[i]` 是 `i` 的二进制中 1 的个数。  

2. **数位 DP 统计**：  
   - **状态设计**：`dfs(pos, count_ones, is_limit)`，表示当前处理到第 `pos` 位，已选 `count_ones` 个 1，是否受原数上限限制。  
   - **转移逻辑**：  
     - 若当前位允许填 1，则递归填 1 并增加 `count_ones`。  
     - 若当前位可填 0，则递归填 0 保持 `count_ones` 不变。  
   - **记忆化优化**：通过 `f[pos][count_ones][is_limit]` 缓存计算结果。  

3. **特判处理**：  
   - `k=0` 时仅 1 是合法解。  
   - `k=1` 时需排除数 1 的影响（因 1 需 0 次操作）。  

**解决难点**：  
- **数位限制处理**：需动态判断是否顶到原数上限，避免统计超出 `n` 的情况。  
- **状态剪枝**：通过记忆化优化重复子问题，避免指数级复杂度。  

---

### **题解评分 (≥4星)**  
1. **Yt_pY 题解（5星）**  
   - **亮点**：  
     - 完整预处理 `sum[]` 和 `cnt[]`，逻辑清晰。  
     - 记忆化 DFS 实现高效数位 DP。  
     - 明确处理 `k=0` 和 `k=1` 的特判。  

2. **qwaszx 题解（4星）**  
   - **亮点**：  
     - 组合数优化快速统计合法数目。  
     - 简洁处理特判与边界条件。  

3. **carp_oier 题解（4星）**  
   - **亮点**：  
     - 结合组合数与递推预处理，逻辑简洁。  
     - 游戏化思路增添趣味性。  

---

### **最优思路或技巧提炼**  
1. **预处理加速**：预处理操作次数 `cnt[]` 是核心，避免每次动态计算。  
2. **状态压缩**：数位 DP 通过 `count_ones` 和 `is_limit` 两个关键状态压缩问题规模。  
3. **组合数优化**：对于固定位数和 1 的数量，直接使用组合数计算可能解。  

---

### **同类型题或类似算法套路**  
1. **数位限制问题**：如统计区间内满足某条件的数（如不含 4 的数）。  
2. **操作次数递推**：如多次操作后转化为特定值的计数问题。  

---

### **推荐相似题目**  
1. **CF1036C - Classy Numbers**：统计区间内非零数字不超过 3 的数的个数。  
2. **Luogu P2657 - windy数**：统计区间内相邻数字差至少为 2 的数的个数。  
3. **LeetCode 600 - Non-negative Integers without Consecutive Ones**：二进制数中不包含连续 1 的数的个数。  

---

### **个人心得摘录**  
- **Yt_pY**：强调数位 DP 的模板化应用，但需注意特判。  
- **carp_oier**：通过组合数预处理优化时间复杂度，但需处理上界限制。  

---

### **可视化与算法演示**  
**动画方案设计**：  
1. **像素风格界面**：  
   - **颜色方案**：8 位色调色板，绿色表示已选 1，红色表示当前位限制。  
   - **Canvas 网格**：按二进制位排列为方格，点击位切换 0/1。  

2. **动态演示**：  
   - **步进控制**：单步执行数位选择，显示 `count_ones` 和 `is_limit` 变化。  
   - **音效触发**：  
     - **填位音效**：8 位“哔”声。  
     - **合法解音效**：上扬音调提示成功。  

3. **自动模式**：  
   - AI 自动填位，展示最优路径选择过程。  

**关键代码片段（JS）**：  
```javascript
// 初始化像素画布
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
ctx.fillStyle = '#00FF00'; // 绿色表示1

function drawBit(pos, value) {
  ctx.fillRect(pos * 10, 0, 8, 8); // 8x8像素方块
  if (value === 1) playSound('beep'); // 触发音效
}

// 单步执行DFS
function stepDFS(pos, count, limit) {
  if (pos === len) {
    if (cnt[count] === k-1) playSound('success');
    return;
  }
  // 绘制当前位选择
  drawBit(pos, currentChoice);
}
```

---

### **核心代码实现（Yt_pY题解）**  
```cpp
int dfs(int s, int c, int lim) {
    if (s == 0) return (c != 0 && cnt[c] + 1 == k);
    if (f[s][c][lim] != -1) return f[s][c][lim];
    
    int res = 0;
    if (lim) {
        if (num[s] == 0) res = dfs(s-1, c, 1);
        else {
            res = (dfs(s-1, c, 0) + dfs(s-1, c+1, 1)) % mod;
        }
    } else {
        res = (dfs(s-1, c, 0) + dfs(s-1, c+1, 0)) % mod;
    }
    return f[s][c][lim] = res;
}
```

---
处理用时：98.96秒