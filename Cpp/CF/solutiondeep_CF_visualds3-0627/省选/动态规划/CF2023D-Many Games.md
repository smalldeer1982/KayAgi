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

## 【题目翻译】

# 多场游戏

## 题目描述

最近，你获得了一张稀有门票，可以进入世界上唯一一家真正能赚到钱的赌场。你想充分利用这次机会。

赌场的规则如下：

- 赌场共有 $n$ 场游戏。
- 每场游戏最多只能玩一次。
- 每场游戏有两个参数：$p_i$（$1 \le p_i \le 100$）和 $w_i$，分别表示获胜的概率（百分比）和获胜时的奖金。
- 如果你在任意选择的游戏中失败，你将一无所获（即使其他选择的游戏获胜）。

你需要提前选择一个游戏集合，使得你的奖金期望值最大化。

若选择下标为 $i_1 < i_2 < \ldots < i_k$ 的游戏，则全胜的概率为 $\prod\limits_{j=1}^k \frac{p_{i_j}}{100}$，此时奖金为 $\sum\limits_{j=1}^k w_{i_j}$。期望值为两者的乘积。

## 输入输出样例

（样例内容与原文一致，此处略）

---

## 唯一算法分类：0-1背包

---

## 综合分析与结论

### 核心思路
1. **分组贪心**：将相同概率 $p_i$ 的游戏分为一组，每组按 $w_i$ 降序排列。对于每组，最多选取前 $k$ 个（$k \le \frac{100}{100-p_i}$），总物品数被约束至约 481 个。
2. **背包优化**：基于题目条件 $w_i \cdot p_i \le 2 \times 10^5$，推导出 $\sum w_i$ 的上界约为 $2 \times 10^5$，将背包容量压缩至可行范围。
3. **动态规划**：用 $f[j]$ 表示总奖金为 $j$ 时的最大概率积，状态转移方程为：
   $$
   f[j] = \max(f[j],\ f[j-w] \times \frac{p}{100})
   $$

### 关键难点
- **物品数量爆炸**：通过分组和选取上限将 $n$ 从 $2 \times 10^5$ 压缩至约 500。
- **背包容量爆炸**：利用数学推导证明 $\sum w_i$ 的上界，将容量约束至 $2 \times 10^5$。

### 可视化设计
1. **像素风格网格**：用 Canvas 绘制背包数组，每个格子表示 $f[j]$ 的值，颜色深浅表示概率大小。
2. **音效触发**：
   - 物品选中时播放「滴」声
   - 更新最大值时播放「叮」声
3. **动态高亮**：
   ```javascript
   // 伪代码：更新背包时高亮变化位置
   ctx.fillStyle = `hsl(${200*(1-f[j])}, 70%, 50%)`; // 根据概率值映射颜色
   ctx.fillRect(j%50*10, Math.floor(j/50)*10, 8, 8); // 10x10 像素格子
   ```
4. **自动演示模式**：按物品分组逐步加载，展示贪心选择过程与背包更新。

---

## 题解清单（4星及以上）

### 1. 作者：LKY928261（⭐⭐⭐⭐⭐）
- **亮点**：数学推导严谨，代码简洁高效（仅 20 行），背包容量论证清晰。
- **核心代码**：
  ```cpp
  for(j=_;j-->x;) // 逆序更新背包
    d[j] = max(d[j], d[j-x]*i/100);
  ```

### 2. 作者：SwordDance（⭐⭐⭐⭐）
- **亮点**：引入调和级数分析物品总数，代码中加入详细注释。
- **关键注释**：
  ```cpp
  // 根据 p 计算最大可选数：x=100/(100-i)
  ```

### 3. 作者：HaneDaniko（⭐⭐⭐⭐）
- **亮点**：详细推导正收益条件，给出多组测试数据验证。

---

## 最优代码实现

### LKY928261 的核心代码
```cpp
for(i=1;i<=99;i++){
    for(y=100/(100-i);y&&b[i].size();y--){ // 按分组上限选取
        x=b[i].top(),b[i].pop();
        for(j=_;j-->x;) // 逆序背包更新
            d[j]=max(d[j],d[j-x]*i/100);
    }
}
```

---

## 同类型题目推荐
1. **P1105 [NOIP2010 普及组] 三国游戏**（贪心+背包思想）
2. **P1064 [NOIP2006 提高组] 金明的预算方案**（分组背包）
3. **P1853 投资的最大效益**（期望值优化）

---

## 复古像素化演示代码片段
```javascript
// Canvas 初始化
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');
ctx.fillStyle = '#333'; // 背景色
ctx.fillRect(0, 0, 500, 500);

// 背包更新动画
function updateDP(j, value) {
    const x = (j % 50) * 10, y = Math.floor(j / 50) * 10;
    ctx.fillStyle = `hsl(${200*(1-value)}, 70%, 50%)`; // 概率越高，色调越蓝
    ctx.fillRect(x, y, 8, 8);
    playSound('blip'); // 触发音效
}
```

---

## 个人心得摘录
> "赛时卡在数学推导，后来发现物品数上界是调和级数求和，立刻想到背包可行性。" —— LKY928261  
> "将 $p=100$ 特判后，代码简洁性提升 50%。" —— SwordDance

---

## 可视化算法演示
### 动态规划状态转移
1. **初始状态**：$f[0] = 1$（全黑格子），其他为 0（白色）。
2. **物品加入**：
   - 选中物品 $w=80, p=80\%$ 时，更新 $f[80] = 0.8$（蓝色格子）。
3. **音效反馈**：每次更新播放 8-bit 音效，最大值更新时音调升高。
4. **最终展示**：红色高亮 $\max(f[j] \times (j + k))$ 的位置。

![dp-grid](https://via.placeholder.com/500x500/333/fff?text=DP+Grid+Demo)  
（示意图：每个格子表示背包状态，颜色深浅反映概率值）

---
处理用时：78.27秒