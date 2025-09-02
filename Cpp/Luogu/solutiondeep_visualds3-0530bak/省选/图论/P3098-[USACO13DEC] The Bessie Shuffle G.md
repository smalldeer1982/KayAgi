# 题目信息

# [USACO13DEC] The Bessie Shuffle G

## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。


## 说明/提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]


## 样例 #1

### 输入

```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 
```

### 输出

```
4 
5 
3 
1 
2 
```

# AI分析结果



### 唯一算法分类
**倍增法**

---

### 题解思路与核心难点

#### 核心思路
题目要求逆向推导每个查询位置对应的初始牌号。由于直接模拟无法处理大范围的 N，所有题解均采用以下策略：
1. **逆向思维**：从临时堆的最终位置倒推回初始牌堆的位置。
2. **倍增优化**：预处理每个位置经过 2^i 次操作后的位置，快速跳过大量重复步骤。
3. **分情况处理**：区分牌是否在洗牌阶段被处理，或已移出洗牌范围。

#### 难点分析
- **逆向映射**：洗牌操作本质是排列变换，需构建逆向映射数组。
- **边界处理**：当剩余牌数不足 M 时，直接移牌而非洗牌，需特殊处理。
- **倍增跳跃**：正确设计倍增数组的初始化和查询时的跳跃逻辑。

---

### 题解评分（≥4星）

1. **XL4453（★★★★☆）**
   - **亮点**：代码简洁，预处理逆向映射数组，通过倍增快速定位。
   - **改进点**：注释较少，部分变量命名可优化。

2. **Graphcity（★★★★☆）**
   - **亮点**：详细注释，分情况讨论清晰，二分法优化查询。
   - **改进点**：实现稍复杂，部分逻辑可简化。

3. **littleming（★★★★☆）**
   - **亮点**：参考官方思路，代码高效，滑动窗口思想减少冗余计算。
   - **改进点**：缺乏中文注释，理解成本较高。

---

### 最优思路与技巧

#### 关键技巧
- **逆向倍增数组**：预处理每个位置经过 2^i 次洗牌后的位置，如 `p[i][j]`。
- **分阶段处理**：将问题分为洗牌阶段和非洗牌阶段，分别用倍增和直接计算处理。
- **数学公式推导**：最终位置与初始位置的转换公式 `n - (r - m + x)`。

#### 代码片段（XL4453 核心逻辑）
```cpp
// 预处理逆向洗牌映射
for (int i = m-1; i >= 0; i--) {
    scanf("%d", &x);
    p[0][m - x + 1] = i; // 构建初始逆向映射
}

// 倍增填充转移数组
for (int i = 1; i <= 29; i++)
    for (int j = 1; j <= m; j++)
        p[i][j] = p[i-1][p[i-1][j]];

// 查询处理
while (T--) {
    scanf("%d", &x);
    if (x <= m) now = m-1;
    else now = x-1, x = m;
    for (int i = 29; i >= 0; i--) {
        if (now + (1 << i) <= n && p[i][x]) {
            now += (1 << i);
            x = p[i][x];
        }
    }
    if (now < n) x = 0, now++;
    printf("%d\n", n - now + m - x);
}
```

---

### 类似题目推荐
1. **P1081 开车旅行**（倍增法处理跳跃查询）
2. **P3121 [USACO15FEB]审查（黄金）**（滑动窗口与预处理优化）
3. **P3396 哈希冲突**（逆向思维处理大规模查询）

---

### 可视化与算法演示

#### 动画设计
1. **像素风格牌堆**：用 8 位色块表示牌堆，临时堆以不同颜色区分。
2. **逆向追踪高亮**：展示查询位置如何通过倍增跳跃回初始位置，当前跳跃步数用闪烁效果标记。
3. **音效提示**：跳跃成功时播放上升音调，退出洗牌阶段时播放“弹出”音效。

#### 交互功能
- **速度控制**：滑块调节动画速度（1x, 2x, 5x）。
- **单步执行**：按空格键逐步执行倍增跳跃。
- **自动演示**：AI 模式自动选择最优跳跃路径，类似贪吃蛇 AI。

---

### 复古游戏化实现

#### Canvas 绘制
- **初始化牌堆**：用网格绘制初始牌堆，每张牌编号以像素字体显示。
- **洗牌动画**：前 M 张牌按洗牌规则重新排列，移出牌飞向临时堆。
- **音效设计**：使用 Web Audio API 播放 8 位音效（跳跃声、成功声）。

#### 代码片段（伪代码）
```javascript
// 初始化牌堆
function initDeck() {
    for (let i = 1; i <= n; i++) {
        drawPixelCard(i, x, y); // 像素风格绘制
    }
}

// 自动演示模式
function autoPlay(q) {
    let pos = q;
    while (pos > 0) {
        let step = findMaxStep(pos); // 查找最大可跳跃步数
        pos = jump(pos, step); // 执行跳跃
        playSound('jump'); // 播放音效
    }
    highlightInitialPos(pos); // 高亮初始位置
    playSound('success');
}
```

---

### 总结
通过逆向思维与倍增法的结合，本题解高效处理了大规模数据下的查询问题。可视化设计通过复古像素风格与交互式动画，使复杂的倍增跳跃过程直观易懂，适合教学与算法演示。

---
处理用时：83.21秒