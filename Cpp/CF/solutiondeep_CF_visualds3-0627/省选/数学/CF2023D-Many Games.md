# 题目信息

# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200```

### 输出

```
112.00000000```

## 样例 #2

### 输入

```
2
100 1
100 1```

### 输出

```
2.00000000```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1```

### 输出

```
20.00000000```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79```

### 输出

```
395.20423800```

# AI分析结果



---

## 唯一算法分类

组合数学

---

## 综合分析与结论

### 核心思路与数学推导
题目要求选择若干游戏使期望收益最大化。数学推导的关键在于：
1. **贪心分组策略**：将相同概率 p 的游戏分组，每组按 w 降序排列，最多选前 k 个（k=100/(100-p)）
2. **背包状态设计**：用 f[j] 表示总奖金 j 时的最大概率乘积，通过 01 背包递推
3. **上界优化**：利用题目条件 w_i*p_i ≤ 2e5 推导出总奖金上界约 2e5

关键公式推导：
- 对于 p 相同的 k 个元素，若新增第 k+1 个元素需满足：
  $$ p^{k+1}(s + w_{k+1}) > p^k s \implies p(s + w_{k+1}) > s \implies k < \frac{100}{100-p} $$

### 解决难点
1. **组合爆炸**：通过分组贪心将物品数量压缩至约 500 个
2. **概率乘积的累积**：用对数转换将乘法转换为加法（但实际代码中直接维护乘积）
3. **状态空间优化**：基于 w_i*p_i 的约束限制背包容量至 2e5

### 可视化设计
1. **像素风格动画**：  
   - 左侧展示分组过程（不同颜色代表不同 p 值组）  
   - 右侧用网格表示背包状态，每个格子代表奖金 j，颜色深浅表示概率乘积 f[j]  
   - 添加音效：当选中新物品时播放清脆音效，更新背包时播放滑动音效  
2. **动态流程**：  
   - 分阶段展示：分组选择 → 背包初始化 → 逐个物品更新背包 → 最终结果比较  
   - 高亮当前处理的物品和对应的背包状态更新  
3. **交互控制**：支持暂停/步进/加速，重点展示关键推导步骤（如分组数 k 的计算）

---

## 题解清单 (≥4星)

### 1. 作者：LKY928261 (5星)
- **亮点**：完整推导分组上限公式，代码简洁高效（优先队列处理分组）
- **核心代码**：
  ```cpp
  for(int i=1;i<=99;i++){
    int lim = 100/(100-i);
    while(lim-- && !b[i].empty()){
      int x = b[i].top(); b[i].pop();
      for(int j=2e5; j>=x; j--) 
        d[j] = max(d[j], d[j-x]*i/100);
    }
  }
  ```

### 2. 作者：SwordDance (4星)
- **亮点**：数学分析深入（推导极值点公式），代码加入分组上限预计算
- **关键推导**：
  $$ k < \frac{1}{\ln \frac{1}{p}} \implies \text{分组数量自然对数级增长} $$

### 3. 作者：weirdoX (4星)
- **亮点**：从博弈角度分析最优子结构，代码实现分组时动态判断收益
- **优化技巧**：在背包更新时实时检测是否有收益，无收益则跳过后续同组物品

---

## 最优思路提炼

1. **分组贪心**：同概率游戏按 w 降序排列，每组最多选前 ⌊100/(100-p)⌋ 个
2. **概率乘积维护**：用 01 背包维护总奖金 j 对应的最大概率乘积 f[j]
3. **上界压缩**：总奖金 ∑w_i ≤ 2e5（由 w_i*p_i ≤ 2e5 推导）
4. **特判处理**：p=100% 的游戏必选且不计入概率乘积

---

## 同类型题与算法套路

1. **组合优化问题**：在受限条件下选择最优子集（常用贪心+背包）
2. **概率期望 DP**：维护乘积形式的状态转移（常用对数转换或直接维护浮点数）
3. **分组背包**：按特定规则分组后选择物品（如多重背包的二进制优化）

---

## 推荐相似题目

1. **P1105 乘积最大子数组**（分组选择与乘积维护）
2. **P2946 Cow Frisbee Team S**（模数分组背包）
3. **P1450 硬币购物**（容斥+背包组合）

---

## 个人心得摘录

> "赛时卡 C 卡太久了没来得及做，第二天和同学讨论才想通分组策略。关键是要发现相同 p 的游戏选前 k 大 w 的数学约束。" —— LKY928261  
> "一开始没注意 p 是整数，浪费半小时推导错误公式。后来用调和级数分析总物品数才突破瓶颈。" —— hh弟中弟

---

## 可视化代码片段（像素风格核心逻辑）

```javascript
// Canvas 绘制背包状态
function drawBackpack(ctx, f, maxW) {
  const CELL_SIZE = 4;
  for (let j = 0; j <= maxW; j++) {
    const intensity = Math.log(f[j] + 1) / 10; // 对数映射颜色
    ctx.fillStyle = `hsl(240, 100%, ${50 + intensity*50}%)`;
    ctx.fillRect(j*CELL_SIZE % 800, Math.floor(j*CELL_SIZE/800)*CELL_SIZE, CELL_SIZE, CELL_SIZE);
  }
}

// 背包更新音效
function playUpdateSound() {
  const osc = audioCtx.createOscillator();
  osc.frequency.setValueAtTime(800 + Math.random()*200, audioCtx.currentTime);
  osc.connect(audioCtx.destination);
  osc.start(); osc.stop(audioCtx.currentTime + 0.05);
}
```

---
处理用时：79.66秒