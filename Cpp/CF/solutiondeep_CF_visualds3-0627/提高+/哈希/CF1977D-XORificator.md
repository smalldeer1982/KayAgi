# 题目信息

# XORificator

## 题目描述

You are given a binary (consisting only of 0s and 1s) $ n \times m $ matrix. You are also given a XORificator, using which you can invert all the values in a chosen row (i.e. replace 0 with 1 and 1 with 0).

A column in the matrix is considered special if it contains exactly one 1. Your task is to find the maximum number of columns that can be made special at the same time, and the set of rows the XORificator should be used on to achieve that.

## 说明/提示

In the first test case, you can use the XORificator on the second row to make the columns $ 2 $ , $ 3 $ , and $ 4 $ special.

In the second test case, the only column is already special, so you don't need to use the XORificator.

## 样例 #1

### 输入

```
5
3 4
1010
0110
0100
1 1
1
1 1
0
2 5
00101
10110
3 3
101
111
000```

### 输出

```
3
010
1
0
1
1
3
00
2
010```

# AI分析结果



**算法分类**  
哈希、贪心

---

### **题解思路与算法要点**

1. **核心思路**  
   枚举每个可能的 $(i,j)$，假设第 $j$ 列的第 $i$ 行是唯一一个 $1$，此时可唯一确定需要翻转的行集合。统计所有可能的翻转方案出现次数，最大值即为答案。

2. **解决难点**  
   - **高效哈希表示**：将翻转方案（行集合）映射为哈希值，避免直接存储二进制状态。  
   - **快速计算哈希**：利用前缀后缀异或优化，单列处理时间复杂度为 $O(n)$。  
   - **冲突处理**：部分题解使用双哈希或随机大质数降低冲突概率。

3. **关键变量与数据结构**  
   - **哈希函数**：每行分配随机大数，翻转方案通过异或行哈希值表示。  
   - **前缀后缀数组**（`pre`, `suf`）：快速计算翻转某行后的总哈希值。

---

### **题解评分 ≥4星**

1. **phigy (赞：6) ⭐⭐⭐⭐⭐**  
   **亮点**：随机哈希 + 前后缀优化，代码简洁高效。  
   **代码可读性**：结构清晰，变量命名合理。  
   **核心代码**：  
   ```cpp
   for (int j=1; j<=m; j++) {
       // 计算前缀后缀异或
       for (int i=1; i<=n; i++) pre[i] = pre[i-1] ^ (hsh[i] * s(i,j));
       for (int i=n; i>=1; i--) suf[i] = suf[i+1] ^ (hsh[i] * s(i,j));
       // 枚举i，计算哈希并统计
       for (int i=1; i<=n; i++) {
           unsigned long long now = pre[i-1] ^ suf[i+1] ^ (hsh[i] * (1-s(i,j)));
           mp_num[now]++;
       }
   }
   ```

2. **Yc_cY (赞：4) ⭐⭐⭐⭐**  
   **亮点**：双哈希避免冲突，代码注释详细。  
   **优化点**：使用质数模数和幂次预处理，安全性高。  
   **核心代码**：  
   ```cpp
   for (int j=1; j<=m; j++) {
       // 计算原始哈希
       for (int i=1; i<=n; i++) h1 = (h1*P + s[i][j]) % Mod1;
       // 枚举i，生成双哈希值
       for (int i=1; i<=n; i++) {
           array<int,2> t = {h1 + ((s[i][j]^1) * p1[n-i]) % Mod1, ...};
           mp[t]++;
       }
   }
   ```

3. **Priestess_SLG (赞：0) ⭐⭐⭐⭐**  
   **亮点**：哈希异或优化，代码可读性强。  
   **技巧**：自然溢出与模数结合，兼顾速度与安全性。  
   **核心代码**：  
   ```cpp
   for (int j=1; j<=m; j++) {
       // 计算异或前缀后缀
       for (int i=1; i<=n; i++) pre[i] = pre[i-1] ^ (s[i][j] ? Hash[i] : 0);
       for (int i=n; i>=1; i--) suf[i] = suf[i+1] ^ (s[i][j] ? Hash[i] : 0);
       // 生成翻转方案哈希
       for (int i=1; i<=n; i++) {
           int now = pre[i-1] ^ suf[i+1] ^ (Hash[i] * (s[i][j]^1));
           mp[now]++;
       }
   }
   ```

---

### **最优思路提炼**

1. **核心策略**  
   - **枚举每个可能的唯一 $1$**：确定 $(i,j)$ 后，翻转方案唯一。  
   - **哈希统计频率**：将翻转方案映射为哈希值，统计出现次数，最大值即答案。

2. **优化技巧**  
   - **随机哈希**：每行分配随机大数，异或操作快速计算翻转集合。  
   - **前后缀分解**：单列处理时，通过 `pre` 和 `suf` 数组快速计算当前行翻转后的总哈希。

3. **实现细节**  
   - **避免哈希冲突**：使用双哈希或大质数模数。  
   - **快速输出方案**：记录哈希值对应的 $(i,j)$，最终根据记录的坐标生成翻转结果。

---

### **同类型题与算法套路**

- **相似题目**  
  1. [LeetCode 1072. Flip Columns For Maximum Number of Equal Rows](https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/)  
  2. [Codeforces 1005D. Polycarp and Div 3](https://codeforces.com/problemset/problem/1005/D)  
  3. [洛谷 P3812 【模板】线性基](https://www.luogu.com.cn/problem/P3812)（异或操作优化）

- **通用套路**  
  - **哈希统计最优解**：当状态空间大但可哈希时，通过频率统计快速找最优。  
  - **行列分解优化**：将二维问题分解为行或列的独立处理。

---

### **推荐洛谷题目**

1. **P1879 [USACO06NOV] Corn Fields**  
   - **关键词**：状态压缩、位运算、动态规划  
   - **关联点**：处理二维矩阵状态，类似翻转问题。

2. **P2704 [NOI2001] 炮兵阵地**  
   - **关键词**：状态压缩、动态规划  
   - **关联点**：枚举合法状态，统计最大值。

3. **P2622 关灯问题II**  
   - **关键词**：位运算、广度优先搜索  
   - **关联点**：状态翻转与哈希优化。

---

### **个人心得摘录**

- **phigy**：  
  > “同一列确定的翻转方案不同，因此只需统计哈希出现次数。”  
  **总结**：通过唯一性保证统计正确性。

- **_Deer_Peach_**：  
  > “双哈希日常被卡，所以多写点模数。”  
  **教训**：哈希冲突需谨慎，多模数或随机数更安全。

---

### **可视化与算法演示**

**动画设计**  
1. **像素风格界面**：  
   - **8位色彩**：行用绿色（未翻转）、红色（翻转），列用蓝色高亮当前处理列。  
   - **Canvas 网格**：绘制矩阵，点击列后显示翻转方案和哈希值。

2. **关键步骤演示**：  
   - **枚举 $(i,j)$**：高亮第 $j$ 列和第 $i$ 行，显示翻转后的状态。  
   - **哈希计算**：动态显示 `pre` 和 `suf` 异或过程，最终哈希值生成。  
   - **统计哈希表**：右侧面板显示哈希值及其出现次数，最大值实时更新。

3. **交互功能**：  
   - **步进控制**：暂停/继续观察每列处理细节。  
   - **音效**：翻转时播放“哔”声，统计更新时播放“叮”声。

**核心代码片段（JS）**  
```javascript
// 初始化 Canvas 和音效
const canvas = document.getElementById("grid");
const ctx = canvas.getContext("2d");
const flipSound = new Audio("flip.wav"); 

// 绘制矩阵和翻转状态
function drawGrid(matrix, flippedRows) {
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            const value = matrix[i][j] ^ flippedRows.has(i);
            ctx.fillStyle = value ? "#00FF00" : "#FF0000";
            ctx.fillRect(j * 20, i * 20, 18, 18);
        }
    }
}

// 自动演示处理列
async function processColumn(j) {
    let pre = 0, suf = 0;
    for (let i = 0; i < n; i++) {
        pre ^= hash[i] * matrix[i][j];
        ctx.fillStyle = "#0000FF"; // 高亮当前列
        ctx.fillRect(j * 20, i * 20, 18, 18);
        await sleep(500);
    }
    // 更新哈希表并统计...
}
```

---

**总结**  
通过哈希高效统计翻转方案，结合行列分解优化，最终在 $O(nm)$ 时间复杂度内解决问题。可视化设计突出行列处理与哈希统计过程，适合理解核心思想。

---
处理用时：104.27秒