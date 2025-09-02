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



**算法分类**  
其他搜索（逆向思维 + 倍增优化）

---

### **题解思路与解决难点**

#### **核心思路**  
所有题解均采用逆向思维，从最终位置反推初始位置，结合倍增优化处理大规模轮次。核心步骤：  
1. **逆向建模**：将最终临时堆的位置视为初始状态，逐步倒推回原始牌堆的位置。  
2. **倍增预处理**：预处理每个位置在多次洗牌后的转移路径，利用二进制分解快速跳跃。  
3. **分类处理**：分情况讨论牌是否在洗牌阶段脱离，动态调整计算逻辑。  

#### **解决难点**  
- **大规模轮次无法模拟**：通过倍增将时间复杂度从 O(N) 降至 O(logN)。  
- **洗牌与直接移牌的边界处理**：通过预计算洗牌阶段的转移函数，结合条件判断处理不同阶段的移动。  
- **逆向路径的追踪**：用数组记录每个位置的逆向映射关系，避免直接模拟复杂的洗牌过程。  

---

### **题解评分**  

1. **XL4453 的题解（★★★★☆）**  
   - **思路清晰**：简洁的倍增预处理与跳跃逻辑。  
   - **代码简洁**：仅用 20 行核心代码实现。  
   - **优化高效**：时间复杂度 O(Q logN)，适用于大范围数据。  
   - **实现提示**：预处理反向映射时需注意数组下标。  

2. **littleming 的题解（★★★★☆）**  
   - **逆向处理明确**：直接引用 USACO 题解思路，逻辑严谨。  
   - **滑动窗口优化**：动态调整洗牌与非洗牌阶段的移动。  
   - **代码注释清晰**：关键步骤有详细注释，便于理解。  

3. **FQ04gty 的题解（★★★☆☆）**  
   - **逻辑正确**：类似倍增思路，但预处理细节稍复杂。  
   - **实现冗余**：部分边界条件处理不够直观。  

---

### **最优思路与技巧提炼**  

1. **逆向追踪 + 倍增跳跃**  
   - 预处理每个位置在 2^i 次操作后的转移位置，通过二进制分解快速计算总移动次数。  
   - 核心代码片段：  
     ```cpp  
     // 预处理倍增数组  
     for (int i = 1; i <= 29; ++i)  
         for (int j = 1; j <= m; ++j)  
             p[i][j] = p[i-1][p[i-1][j]];  
     ```  

2. **动态分类处理**  
   - 当剩余牌数不足 M 时，直接移动而非洗牌。需分阶段计算：  
     ```cpp  
     if (now + (1 << i) <= n && p[i][x]) {  
         now += (1 << i);  // 跳跃 2^i 轮  
         x = p[i][x];      // 更新当前位置  
     }  
     ```  

3. **位置映射公式**  
   - 最终位置与原始位置的转换公式需考虑逆向偏移：  
     ```cpp  
     printf("%d\n", n - now + m - x);  
     ```  

---

### **同类题目推荐**  

1. **P1081 [NOIP2012 提高组] 开车旅行**  
   - 倍增预处理动态决策路径。  

2. **P3582 [POI2015] KIN**  
   - 滑动窗口与逆向思维结合。  

3. **P4197 Peaks**  
   - 倍增跳跃处理离线查询。  

---

### **可视化与算法演示**  

**动画设计**：  
1. **牌移动轨迹**：用网格表示牌堆，不同颜色区分洗牌阶段与非洗牌阶段。  
2. **倍增跳跃高亮**：当算法跳跃 2^i 轮时，高亮当前跳跃步长与目标位置。  
3. **音效与进度条**：  
   - **跳跃音效**：每次跳跃时播放短促“滴”声。  
   - **完成音效**：找到初始位置时播放上扬音调。  

**复古像素风格**：  
- **8-bit 牌堆**：用 16x16 像素块表示每张牌，牌编号以像素字体显示。  
- **Canvas 绘制**：动态更新牌的位置，洗牌时添加“闪光”动画。  

**交互控制**：  
- **步进按钮**：允许单步执行倍增跳跃，观察每步的 now 和 x 变化。  
- **速度调节**：滑动条控制动画播放速度（1x~10x）。  

---

### **代码片段（XL4453 题解核心）**  

```cpp  
// 预处理逆向映射  
for (int i = m-1; i >= 0; --i) {  
    scanf("%d", &x);  
    p[0][m - x + 1] = i;  // 反向映射  
}  

// 处理查询  
while (T--) {  
    scanf("%d", &x);  
    if (x <= m) now = m-1;  
    else now = x-1, x = m;  
    // 倍增跳跃  
    for (int i = 29; i >= 0; --i) {  
        if (now + (1<<i) <= n && p[i][x]) {  
            now += (1<<i);  
            x = p[i][x];  
        }  
    }  
    // 计算最终位置  
    printf("%d\n", n - now + m - x);  
}  
```  

---

**总结**：通过逆向建模与倍增优化，将大规模问题转化为对数级别计算，是处理类似“循环转移”问题的经典思路。

---
处理用时：93.87秒