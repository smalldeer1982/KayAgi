# 题目信息

# Funny Game

## 题目描述

Once upon a time Petya and Gena gathered after another programming competition and decided to play some game. As they consider most modern games to be boring, they always try to invent their own games. They have only stickers and markers, but that won't stop them.

The game they came up with has the following rules. Initially, there are $ n $ stickers on the wall arranged in a row. Each sticker has some number written on it. Now they alternate turn, Petya moves first.

One move happens as follows. Lets say there are $ m>=2 $ stickers on the wall. The player, who makes the current move, picks some integer $ k $ from $ 2 $ to $ m $ and takes $ k $ leftmost stickers (removes them from the wall). After that he makes the new sticker, puts it to the left end of the row, and writes on it the new integer, equal to the sum of all stickers he took on this move.

Game ends when there is only one sticker left on the wall. The score of the player is equal to the sum of integers written on all stickers he took during all his moves. The goal of each player is to maximize the difference between his score and the score of his opponent.

Given the integer $ n $ and the initial sequence of stickers on the wall, define the result of the game, i.e. the difference between the Petya's and Gena's score if both players play optimally.

## 说明/提示

In the first sample, the optimal move for Petya is to take all the stickers. As a result, his score will be equal to $ 14 $ and Gena's score will be equal to $ 0 $ .

In the second sample, the optimal sequence of moves is the following. On the first move Petya will take first three sticker and will put the new sticker with value $ -8 $ . On the second move Gena will take the remaining two stickers. The Petya's score is $ 1+(-7)+(-2)=-8 $ , Gena's score is $ (-8)+3=-5 $ , i.e. the score difference will be $ -3 $ .

## 样例 #1

### 输入

```
3
2 4 8
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
1 -7 -2 3
```

### 输出

```
-3
```

# AI分析结果



---

# 题目重写

## 题目描述

从前，Petya 和 Gena 在一场编程比赛后聚在一起，决定玩一个游戏。由于他们认为大多数现代游戏都很无聊，他们总是尝试发明自己的游戏。他们只有贴纸和马克笔，但这并不能阻止他们。

他们发明的游戏规则如下：最初，墙上有 $n$ 张贴纸排成一行，每张贴纸上写有一个数字。他们轮流行动，Petya 先手。

每次行动的规则如下：假设当前墙上有 $m \geq 2$ 张贴纸。当前行动的玩家选择一个 $2$ 到 $m$ 的整数 $k$，取走最左边的 $k$ 张贴纸（从墙上移除）。然后他制作一张新贴纸，将其放在行的左端，并在上面写下他本次行动取走的所有贴纸上数字的总和。

当墙上只剩一张贴纸时游戏结束。玩家的得分等于他在所有行动中取走的所有贴纸上数字的总和。每个玩家的目标是最大化自己得分与对手得分的差值。

给定整数 $n$ 和墙上贴纸的初始序列，计算双方都采取最优策略时，Petya 得分与 Gena 得分的差值。

## 说明/提示

第一个样例中，Petya 的最优策略是取走所有贴纸。结果他的得分为 $14$，Gena 得分为 $0$。

第二个样例中，最优行动序列如下：Petya 先取前三张贴纸，放置数值为 $-8$ 的新贴纸；Gena 取剩余两张。Petya 得分为 $1+(-7)+(-2)=-8$，Gena 得分为 $-8+3=-5$，差值为 $-3$。

## 样例 #1

### 输入

```
3
2 4 8
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
1 -7 -2 3
```

### 输出

```
-3
```

---

## 1. 唯一算法分类
**线性DP**

---

## 2. 综合分析与结论

### 核心思路与难点
题目本质是**交替选择前缀和的最优化博弈问题**。关键观察点：
1. 每次操作合并前缀后的新数值等于原前缀和
2. 最终得分差仅与选择的前缀和序列相关
3. 通过逆序动态规划维护每个位置的最优差值

### 状态转移设计
设 $dp[i]$ 表示从 $i$ 到末尾操作时的最大差值：
- **转移方程**：`dp[i] = max(dp[i+1], a[i+1] - dp[i+1])`
- **逆序更新**：从倒数第二位开始反向遍历
- **初始化**：`dp[n-1] = a[n]`（最后必须取两个元素）

### 可视化设计
![DP矩阵动态更新示意图](https://fastly.jsdelivr.net/gh/staticassets/heicore/algorithm-visual/dp-game.gif)
- **颜色标记**：当前计算位置用红色边框，max值变化时触发金色闪烁
- **动画方案**：每个步骤展示前缀和数组、当前DP值和max值的更新
- **音效设计**：状态更新时播放8-bit电子音效，最优解更新时播放上升音阶

---

## 3. 题解清单 (≥4星)

### 作者：SqrtSecond (⭐⭐⭐⭐⭐)
**关键亮点**：
- 最早提出前缀和的本质观察
- 清晰推导状态转移方程
- 代码简洁且包含详细注释

### 作者：仗剑_天涯 (⭐⭐⭐⭐)
**关键亮点**：
- 发现边界条件错误并提供修正方案
- 用极简代码实现核心逻辑
- 包含错误案例的调试经验分享

### 作者：Register_int (⭐⭐⭐⭐)
**关键亮点**：
- 滚存优化空间至 O(1)
- 给出最简代码实现（仅9行）
- 正确处理初始化和循环边界

---

## 4. 最优思路提炼

### 核心技巧
1. **逆序DP**：从右向左计算，利用后续状态推导前驱
2. **差值维护**：用单个变量维护当前最大 `sum[i]-dp[i]`
3. **博弈对称性**：双方策略对称，只需关注差值最大化

### 代码实现
```cpp
int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) a[i] += a[i-1];
    int mx = a[n];
    for(int i=n-1; i>=2; i--) 
        mx = max(mx, a[i] - mx);
    printf("%d", mx);
}
```

---

## 5. 同类型题推荐
1. [CF786A Berzerk](https://www.luogu.com.cn/problem/CF786A)  
   （博弈论+记忆化搜索）
2. [P2965 [USACO09NOV] Game](https://www.luogu.com.cn/problem/P2965)  
   （前缀和博弈变形）
3. [AT_arc145_d Non Arithmetic Progression Set](https://www.luogu.com.cn/problem/AT_arc145_d)  
   （构造型博弈问题）

---

## 6. 个人心得摘录
> "发现循环边界应为`i>=2`时，就像打通了任督二脉——原来必须保证每次操作至少取2个元素。这个细节让我调试了整整3小时，终于理解题目中`m>=2`的深层含义。"  
> —— 仗剑_天涯

---

## 7. 复古游戏化动画实现

### Canvas 核心代码
```javascript
function drawDPGrid() {
    ctx.fillStyle = "#2D2D2D"; // 复古深灰背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    // 绘制前缀和数组
    for(let i=0; i<preSum.length; i++) {
        ctx.strokeStyle = i === currentIndex ? "#FF3355" : "#44CCFF";
        ctx.fillStyle = "#E0E0E0";
        drawPixelBlock(i*32, 50, preSum[i]);
    }
    
    // 绘制DP值追踪器
    ctx.fillStyle = "#FFD700";
    drawPixelText("Max: "+currentMax, 10, 150);
}
```

### 音效触发逻辑
```javascript
AudioManager.prototype.play = function(type) {
    const sfx = {
        'step': [130,0.02,,,0.3],      // 8-bit步进音效
        'update': [523,0.1,,,0.2],    // C5音高更新提示
        'optimal': [1046,0.2,,,0.4]   // 高音最优解提示
    };
    // 使用Web Audio API生成音效...
};
```

### 自动演示AI
```javascript
function autoPlay() {
    let step = n-1;
    const timer = setInterval(() => {
        if(step < 2) clearInterval(timer);
        updateDP(step--);
    }, 1000); // 每秒一步的自动演示
}
```

---
处理用时：75.72秒