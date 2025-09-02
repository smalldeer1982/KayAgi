# 题目信息

# Birthday

## 题目描述

A MIPT student named Misha has a birthday today, and he decided to celebrate it in his country house in suburban Moscow. $ n $ friends came by, and after a typical party they decided to play blind man's buff.

The birthday boy gets blindfolded and the other players scatter around the house. The game is played in several rounds. In each round, Misha catches exactly one of his friends and has to guess who it is. The probability of catching the $ i $ -th friend does not change between rounds and is equal to $ p_{i} $ percent (as we know, it is directly proportional to the amount of alcohol consumed by the $ i $ -th friend) and $ p_{1}+p_{2}+...+p_{n}=100 $ holds. Misha has no information about who he caught. After Misha makes an attempt to guess the caught person, the round ends. Even then, Misha isn't told whether he guessed correctly, and a new round begins.

The game ends when Misha guesses every friend at least once, that is, there exists such set of rounds $ k_{1},k_{2},...,k_{n} $ , that during round number $ k_{i} $ Misha caught the $ i $ -th friend and guessed him. Misha wants to minimize the expectation of the number of rounds of the game. Despite the fact that at any point in the game Misha has no information about who he has already guessed, his friends are honest, and if they see that the condition for the end of the game is fulfilled, the game ends immediately. Find the expectation of the number of rounds in the game if Misha plays optimally.

## 说明/提示

The optimal strategy in the first sample is to guess friends alternately.

## 样例 #1

### 输入

```
2
50 50
```

### 输出

```
5.0000000000
```

## 样例 #2

### 输入

```
4
50 20 20 10
```

### 输出

```
39.2846263444
```

# AI分析结果


### 💡 Kay的C++算法解析：Birthday 深入学习指南 💡

**引言**  
今天我们来分析"Birthday"这道概率期望题。本指南将帮助你理解最优策略设计、期望计算和贪心证明，并通过像素动画直观感受算法过程。

---

### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：概率期望与贪心策略  

🗣️ **初步分析**：  
> 本题可类比为"多桶投球游戏"——每个桶（朋友）有不同开口大小（概率 $p_i$），每次投球（猜人）需最小化投球次数期望使所有桶至少进一球。**贪心策略**是核心：每次选择能使"游戏结束概率"增幅最大的桶。  
> - **核心难点**：  
>   - 游戏结束概率是乘积形式 $\prod (1-(1-p_i)^{c_i})$  
>   - 期望计算需差分概率：$E = \sum k \times (F(k)-F(k-1))$  
> - **算法流程**：  
>   1. 初始化：每个朋友猜一次（前 $n$ 轮）  
>   2. 迭代：每轮选使 $\frac{(1-p_i)^{c_i} p_i}{1-(1-p_i)^{c_i}}$ 最大的 $i$  
>   3. 更新概率并累加期望  
> - **可视化设计**：  
>   - 复古像素风桶阵（每个桶代表朋友，高度表 $(1-p_i)^{c_i}$）  
>   - 球投中时桶高下降，进度条显式结束概率  
>   - 音效：投球"叮"声，进度满时胜利音效  
>   - 交互：单步/自动模式，高亮显示最优桶选择  

---

### 2. 精选优质题解参考  
**题解一：Su_Zipei (5星)**  
* **点评**：  
  思路清晰引入贪心正确性证明（借鉴官方调整法），代码简洁高效。变量 `nowp[i]` 精妙表示 $(1-p_i)^{c_i}$，增量计算 `(1-nowp[j]*p[j])/(1-nowp[j])` 直指核心。边界处理严谨，直接输出概率更新公式，实践参考价值极高。

**题解二：DarthVictor (4星)**  
* **点评**：  
  用 `f[i]` 表示 $1-(1-p_i)^{c_i}$ 显著提升可读性，增量比 `cal(j)/f[j]` 的计算简洁易懂。虽未给出贪心证明，但算法有效性毋庸置疑。代码中 `lst` 和 `g` 的滚动更新避免冗余计算，适合竞赛直接使用。

**题解三：sodak (4星)**  
* **点评**：  
  采用堆优化（`priority_queue`）将选择复杂度降至 $O(\log n)$，适合 $n$ 较大场景。公式推导详细解释 $g_i$ 与 $P_i$ 的关系，变量名 `lans[i]` 和 `unp` 含义明确。初始化部分 `now=∏p_i` 体现严谨数学思维。

---

### 3. 核心难点辨析与解题策略  
1. **难点一：结束概率的乘积形式**  
   * **分析**：结束概率 $F(k)=\prod (1-(1-p_i)^{c_i})$ 需满足所有 $c_i \geq 1$。优质题解均先猜遍所有人（前 $n$ 轮），确保 $F(n)=\prod p_i >0$。  
   * 💡 **学习笔记**：初始全覆盖是计算期望的基石。  
   
2. **难点二：贪心策略的正确性**  
   * **分析**：Su_Zipei 的证明表明——若最优解 $y_i$ 与贪心解 $x_i$ 不同，可通过调整（$y_a+1, y_b-1$）使解更优，最终贪心解唯一。  
   * 💡 **学习笔记**：调整法是证明贪心的利器。  
   
3. **难点三：增量计算的精度控制**  
   * **分析**：因 $p_i \geq 0.01$，$(1-p_i)^{c_i}$ 收敛快。迭代 $3 \times 10^5$ 轮后增量 $<10^{-6}$，满足精度要求。  
   * 💡 **学习笔记**：概率衰减性质是迭代可行的保证。  

#### ✨ 解题技巧总结  
- **技巧1：滚动更新概率**  
  如 DarthVictor 用 `g = lst * cal(tmp)/f[tmp]` 避免重算全局乘积。  
- **技巧2：增量比替代绝对量**  
  `(1-new_unp)/(1-unp[i]) > (1-new_unp_j)/(1-unp[j])` 比较更高效。  
- **技巧3：堆维护最优选择**  
  sodak 的堆实现将 $O(n)$ 选择降至 $O(\log n)$。  

---

### 4. C++核心代码实现赏析  
**通用核心实现参考**  
* **说明**：综合优质题解思路，初始化后贪心迭代 $3 \times 10^5$ 轮。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <iomanip>
  using namespace std;

  int main() {
      int n; cin >> n;
      vector<double> p(n), unp(n);
      double prod = 1.0, ans = 0.0;

      // 初始化：前n轮每人猜一次
      for (int i = 0; i < n; i++) {
          int percent; cin >> percent;
          p[i] = percent / 100.0;
          unp[i] = 1 - p[i];       // 未被猜中概率
          prod *= (1 - unp[i]);    // 结束概率 = ∏ p_i
      }
      ans = prod * n; // 前n轮贡献

      // 贪心迭代 (n+1 到 3e5轮)
      for (int k = n + 1; k <= 300000; k++) {
          int best = 0;
          double max_increase = 0.0;

          for (int i = 0; i < n; i++) {
              double new_unp = unp[i] * (1 - p[i]); // 猜一次i后的新概率
              double new_ratio = (1 - new_unp) / (1 - unp[i]); // 增量比
              double increase = prod * (new_ratio - 1); // 绝对增量

              if (increase > max_increase) {
                  max_increase = increase;
                  best = i;
              }
          }

          // 更新最优选择
          double new_unp = unp[best] * (1 - p[best]);
          prod = prod * (1 - new_unp) / (1 - unp[best]);
          unp[best] = new_unp;
          ans += max_increase * k;
      }

      cout << fixed << setprecision(10) << ans << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  > 1. **初始化**：读入概率 $p_i$，计算初始结束概率 `prod = ∏ p_i`  
  > 2. **贪心迭代**：每轮选使增量最大的 $i$，更新 `unp[i]` 和结束概率  
  > 3. **期望累加**：`ans += k * (F(k)-F(k-1))`  

**题解一：Su_Zipei 片段赏析**  
* **亮点**：增量比计算直接嵌入循环，无冗余变量。  
* **核心代码**：  
  ```cpp
  for (int j = 2; j <= n; j++) {
      db tmp = res / (1 - nowp[j]) * (1 - nowp[j] * p[j]);
      if (tmp > now) { ... }  // 找最大增量
  }
  ans += (now - res) * i;     // 期望累加
  nowp[pos] *= p[pos];        // 更新概率
  ```
* **代码解读**：  
  > `res` 是当前结束概率，`nowp[j]` 为 $(1-p_j)^{c_j}$。增量计算 `tmp = res * (1-nowp[j]·p_j)/(1-nowp[j])` 巧妙复用历史值，避免重算全局乘积。  

**题解二：DarthVictor 片段赏析**  
* **亮点**：`f[i]` 表示 $1-(1-p_i)^{c_i}$ 提升可读性。  
* **核心代码**：  
  ```cpp
  double cal(int x) {
      return f[x] + (1 - f[x]) * p[x];  // 猜一次后的新概率
  }
  g = lst * cal(tmp) / f[tmp];         // 更新全局概率
  ```
* **学习笔记**：`cal(tmp)/f[tmp]` 即增量比，数学等价于 $\frac{1-(1-p_i)^{c_i+1}}{1-(1-p_i)^{c_i}}$。  

**题解三：sodak 片段赏析**  
* **亮点**：堆维护增量比，复杂度优化至 $O(\log n)$。  
* **核心代码**：  
  ```cpp
  priority_queue<pair<double, int>> q;
  q.push({(1 - unp[j] * p[j]) / (1 - unp[j]), j}); // 增量比入堆
  auto [ratio, id] = q.top(); q.pop();
  double new_prod = prod * ratio;  // 堆顶更新
  ```
* **学习笔记**：堆适用于 $n$ 较大场景，但需注意更新后重新计算增量比入堆。  

---

### 5. 算法可视化：像素动画演示  
<visualization_intro>  
采用 **8位像素风** 模拟"多桶投球游戏"，帮助直观理解贪心策略与概率更新。  
</visualization_intro>  

* **主题**：像素风《概率投球大冒险》  
* **核心演示**：贪心策略选桶 → 投球 → 更新桶高与全局进度  
* **设计思路**：桶高 $(1-p_i)^{c_i}$ 越降，进度条越接近1。游戏化增强趣味性。  

**动画帧步骤**：  
1. **场景初始化**：  
   - 像素网格中 $n$ 个彩色桶（FC红白机色调），桶顶标签 $p_i$  
   - 控制面板：开始/暂停、单步、速度滑块、重置  
   - 进度条：初始0%，顶部显示当前轮数 $k$ 和期望值 $E$  

2. **投球阶段（逐轮演示）**：  
   - **步骤1：计算增量**  
     - 每个桶上方显示 $\Delta_i = \frac{(1-p_i)^{c_i} p_i}{1-(1-p_i)^{c_i}}$  
     - 最大值桶高亮闪烁，播放"滴答"选择音效  
   - **步骤2：投球动画**  
     - 球划抛物线落入高亮桶，桶高度 $h_i$ 乘以 $(1-p_i)$ 下降  
     - 球命中时播放"叮"声，桶变色（如蓝→浅蓝）  
   - **步骤3：更新进度**  
     - 进度条按 $F(k) = \prod (1-h_i)$ 增长  
     - 数据区显示：$\Delta F = F(k)-F(k-1)$，$E\ += k \cdot \Delta F$  

3. **自动演示模式**：  
   - 点击"AI演示"后，算法自动运行（速度可调）  
   - 每 $10$ 轮短暂停顿，高亮关键变化  

4. **胜利条件**：  
   - 进度条达 $99.99\%$ 时，播放胜利音效 + 像素烟花动画  
   - 显示最终 $E$ 值，与代码输出对比验证  

**技术实现**：  
- Canvas 绘制桶阵/球轨迹，requestAnimationFrame 控制帧率  
- 音效：Web Audio API 生成 8-bit 音效（投球声、胜利音）  
- 游戏化：进度每增 $20\%$ 解锁"关卡"，显示鼓励标语  

---

### 6. 拓展练习与相似问题思考  
<similar_problems_intro>  
掌握贪心策略在概率期望问题中的应用，可解决以下相似问题：  
</similar_problems_intro>  

* **通用技巧迁移**：  
  1. **优惠券收集问题**：概率均等时求期望  
  2. **投篮覆盖问题**：不同命中率下最小期望次数  
  3. **图覆盖问题**：随机游走覆盖所有节点的期望步数  

* **洛谷练习推荐**：  
  1. **P3412 抽卡**  
     🗣️ 经典优惠券收集问题，巩固期望公式推导  
  2. **P2221 [省选] 投篮游戏**  
     🗣️ 篮筐命中率不同，直接应用本题贪心策略  
  3. **P6154 游走**  
     🗣️ 拓展到图结构，学习无环图上的期望 DP  

---

### 7. 学习心得与经验分享  
<insights_intro>  
Su_Zipei 的题解分享了对贪心策略的深刻理解：  
</insights_intro>  

> **参考经验**：  
> "贪心正确性可通过调整法证明：若存在更优解 $y_i \neq x_i$，则必有 $y_a < x_a$ 和 $y_b > x_b$。令 $y_a+1, y_b-1$ 后解更优，与假设矛盾。"  
>   
> **Kay点评**：  
> 调整法是证明贪心的通用工具，尤其适合涉及概率的问题。在类似问题中（如 P3412），可尝试相同证明框架。  

---

**结语**  
通过本次分析，相信大家已掌握概率期望题的贪心策略设计和期望计算技巧。记住：用调整法证明贪心，用差分概率计算期望，用像素动画辅助理解。下次挑战见！💪

---
处理用时：371.29秒