# 题目信息

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1```

### 输出

```
18
10
0```

# AI分析结果



---

**唯一算法分类**：置换环分解

---

### **题解思路与算法分析**

#### **核心思路**
题目本质为寻找置换环，并为环中的元素分配数值，使得相邻元素的绝对值差之和最大。每个环的贡献由其长度决定：环长 $L$ 贡献 $\lfloor L/2 \rfloor$ 对最大差值对。总答案为 $2k(n-k)$，其中 $k$ 是所有环的贡献之和。

#### **解决难点**
1. **置换环的构建**：通过颜色在两个带子中的位置关系，构造置换映射，形成环结构。
2. **贪心策略**：每个环中尽可能多地将大数和小数配对，最大贡献为 $\lfloor L/2 \rfloor$ 对。
3. **数学推导**：总和公式 $2k(n-k)$ 的推导基于最大差值对的对称性（前 $k$ 小和后 $k$ 大数的差）。

#### **关键步骤**
1. **输入处理**：将颜色在第一个带子的位置存入映射数组。
2. **寻找置换环**：遍历第二个带子的颜色，通过映射找到环结构。
3. **统计贡献**：计算每个环的 $\lfloor L/2 \rfloor$，累加得到 $k$。

---

### **题解评分与亮点**

#### **评分 ≥4星的题解**
1. **I_am_Accepted (★★★★☆)**  
   - **亮点**：思路清晰，代码简洁，DFS 找环，直接计算贡献。
   - **代码片段**：
     ```cpp
     int dfs(int x) {
         vis[x] = 1;
         if (vis[b[x]]) return 1;
         else return 1 + dfs(b[x]);
     }
     ```
2. **Leasier (★★★★☆)**  
   - **亮点**：置换环分析详细，贪心策略解释透彻。
   - **代码片段**：
     ```cpp
     for (int k = j; !vis[k]; k = b[pos[k]]) {
         vis[k] = true;
         size++;
     }
     ```
3. **Renshey (★★★★☆)**  
   - **亮点**：代码简洁高效，直接统计环长并计算贡献。
   - **代码片段**：
     ```cpp
     for (int j = i; !vis[j]; j = b[a[j]]) vis[j] = true, len++;
     ```

---

### **最优思路提炼**
1. **置换环分解**：将颜色映射为图中的环结构。
2. **贡献计算**：每个环贡献 $\lfloor L/2 \rfloor$，总和 $k$。
3. **公式推导**：最优差值和为 $2k(n-k)$，源自最大与最小数的对称分配。

---

### **类似题目推荐**
1. **P1963 变换序列**（置换环应用）
2. **P1667 数列**（排列的环分解）
3. **P1533 可怜的狗狗**（置换相关操作）

---

### **可视化与算法演示**

#### **动画设计**
1. **置换环构建**：动态显示颜色在两个带子中的位置连接成环。
2. **环遍历高亮**：用颜色标记当前遍历的节点，显示环的形成过程。
3. **贡献计算**：统计每个环的 $\lfloor L/2 \rfloor$，实时更新 $k$ 的值。
4. **公式展示**：最终显示 $2k(n-k)$ 的计算过程。

#### **复古像素效果**
- **像素风格**：8-bit 风格界面，环节点用不同颜色方块表示。
- **音效提示**：遍历时播放“滴”声，统计完成时播放胜利音效。
- **自动演示**：按步自动遍历环，显示当前操作节点。

---

### **核心代码实现**
以 **I_am_Accepted** 的代码为例：
```cpp
int dfs(int x) {
    vis[x] = 1;
    return vis[b[x]] ? 1 : 1 + dfs(b[x]);
}

void work() {
    For(i, 1, n) vis[i] = 0;
    int k = 0;
    For(i, 1, n) if (!vis[i]) k += dfs(i) / 2;
    cout << 2 * k * (n - k) << endl;
}
```

---

### **总结**
通过置换环分解和贪心策略，问题转化为环长的统计与简单公式计算。核心在于将颜色位置映射为图结构，并利用数学对称性最大化差值。

---
处理用时：130.53秒