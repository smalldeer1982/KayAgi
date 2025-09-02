# 题目信息

# [USACO06DEC] The Fewest Coins G

## 题目描述

Farmer John has gone to town to buy some farm supplies. Being a very efficient man, he always pays for his goods in such a way that the smallest number of coins changes hands, i.e., the number of coins he uses to pay plus the number of coins he receives in change is minimized. Help him to determine what this minimum number is.

FJ wants to buy T (1 ≤ T ≤ 10,000) cents of supplies. The currency system has N (1 ≤ N ≤ 100) different coins, with values V1, V2, ..., VN (1 ≤ Vi ≤ 120). Farmer John is carrying C1 coins of value V1, C2 coins of value V2, ...., and CN coins of value VN (0 ≤ Ci ≤ 10,000). The shopkeeper has an unlimited supply of all the coins, and always makes change in the most efficient manner (although Farmer John must be sure to pay in a way that makes it possible to make the correct change).

农夫 John 想到镇上买些补给。为了高效地完成任务，他想使硬币的转手次数最少。即使他交付的硬 币数与找零得到的的硬币数最少。 


John 想要买价值为 $T$ 的东西。有 $N$（$1 \le N \le 100$）种货币参与流通，面值分别为 $V_1,V_2,\dots,V_N$（$1 \le V_i \le 120$）。John 有 $C_i$ 个面值为 $V_i$ 的硬币（$0 \le C_i \le 10 ^ 4$）。

我们假设店主有无限多的硬币， 并总按最优方案找零。**注意**无解输出 `-1`。


## 说明/提示

Farmer John pays 75 cents using a 50 cents and a 25 cents coin, and receives a 5 cents coin in change, for a total of 3 coins used in the transaction.


## 样例 #1

### 输入

```
3 70
5 25 50
5 2 1```

### 输出

```
3```

# AI分析结果



# 算法分类
**动态规划（多重背包 + 完全背包）**

---

## 题解思路与算法要点
### **核心逻辑**
1. **问题拆解**  
   - **John的支付**：有限硬币数量 → 多重背包，求支付金额为 `i` 时的最少硬币数 `f[i]`  
   - **店主的找零**：无限硬币数量 → 完全背包，求找零金额为 `j` 时的最少硬币数 `g[j]`  
   - **最终答案**：枚举 John 支付的金额 `i`（`i ≥ T`），计算 `f[i] + g[i-T]` 的最小值  

2. **关键难点**  
   - **枚举上界**：需证明找零金额的上界为 `V_max²`（`V_max` 为最大面值）。通过鸽巢原理，超过 `V_max²` 的金额可用更大面值硬币优化。  
   - **多重背包优化**：使用二进制拆分将多重背包转化为 01 背包，降低时间复杂度。  

3. **算法流程**  
   - **完全背包（店主找零）**：  
     ```python  
     for 每种硬币面值 v in V:  
         for j = v to max_bound:  
             g[j] = min(g[j], g[j-v] + 1)  
     ```  
   - **多重背包（John支付）**：  
     ```python  
     for 每种硬币面值 v in V:  
         将数量 c 拆分为二进制组（如 1,2,4,...）  
         for 每组拆分后的数量 k:  
             for j = max_bound down to v*k:  
                 f[j] = min(f[j], f[j-v*k] + k)  
     ```  
   - **枚举答案**：  
     ```python  
     min_val = INF  
     for i = T to T + V_max²:  
         min_val = min(min_val, f[i] + g[i-T])  
     ```  

---

## 题解评分（≥4星）
1. **hkr04（★★★★☆）**  
   - **亮点**：详细证明枚举上界，代码清晰，二进制优化实现完整。  
   - **代码**：完整展示多重背包拆分逻辑，初始化与边界处理严谨。  

2. **RedreamMer（★★★★☆）**  
   - **亮点**：数学证明完整，代码简洁，对同余性质有直观解释。  
   - **引用**：“前缀和数组的差为 `k*V_max`，可替换为大面值硬币优化数量”。  

3. **installb（★★★★☆）**  
   - **亮点**：提出 `2*V_max²` 的更强上界，代码注释详细。  
   - **引用**：“找零中面值最大的币少于 `V_max` 个，非最大面值的币最多 `V_max` 个”。  

---

## 最优思路与技巧
### **关键优化**
1. **二进制拆分**  
   - 将多重背包的 `c_i` 个物品拆分为 `1,2,4,...,c_i-2^k` 的组，转化为 01 背包问题，时间复杂度从 `O(N*C*T)` 降为 `O(N*logC*T)`。  

2. **枚举上界证明**  
   - 利用鸽巢原理证明：超过 `V_max²` 的金额可通过同余性质优化，确保答案在 `T + V_max²` 范围内。  

### **代码实现**
```cpp
// 完全背包初始化
memset(g, 0x3f, sizeof(g));
g[0] = 0;
for (int i = 1; i <= n; i++) {
    for (int j = v[i]; j <= max_bound; j++) {
        g[j] = min(g[j], g[j - v[i]] + 1);
    }
}

// 多重背包二进制拆分
for (int i = 1; i <= n; i++) {
    int cnt = c[i];
    for (int j = 1; j <= cnt; j <<= 1) {
        cnt -= j;
        int val = j * v[i];
        for (int k = max_bound; k >= val; k--) {
            f[k] = min(f[k], f[k - val] + j);
        }
    }
    if (cnt > 0) {
        int val = cnt * v[i];
        for (int k = max_bound; k >= val; k--) {
            f[k] = min(f[k], f[k - val] + cnt);
        }
    }
}
```

---

## 类似题目与扩展
1. **P1776 宝物筛选**（多重背包模板题）  
2. **P1616 疯狂的采药**（完全背包模板题）  
3. **P1064 金明的预算方案**（背包问题的变种与组合）  

---

## 可视化与动画设计
### **动画方案**
1. **动态表格高亮**  
   - **完全背包**：以绿色高亮 `g[j]` 的更新位置，展示 `g[j-v] → g[j]` 的转移。  
   - **多重背包**：以红色高亮拆分后的硬币组，逐步填充 `f[j]` 的值。  
   - **枚举答案**：用黄色标记当前最优解，滑动条控制枚举范围。  

2. **复古像素风格**  
   - **Canvas 绘制**：硬币堆叠为像素方块，面值用不同颜色区分（如红=1元，蓝=5元）。  
   - **音效**：  
     - 硬币碰撞：短促“叮”声（Web Audio API 的 `OscillatorNode`）。  
     - 最优解发现：8-bit 胜利音效。  

3. **交互控制**  
   - **步进执行**：按钮控制算法单步执行，观察 `f` 和 `g` 数组更新。  
   - **速度调节**：滑动条调整动画速度（`requestAnimationFrame` 控制帧率）。  

---

## 总结
本题通过 **多重背包（二进制优化）** 与 **完全背包** 的组合，结合数学证明确定枚举上界，是动态规划的经典应用。核心难点在于理解枚举范围的推导与背包优化的实现细节。

---
处理用时：79.57秒