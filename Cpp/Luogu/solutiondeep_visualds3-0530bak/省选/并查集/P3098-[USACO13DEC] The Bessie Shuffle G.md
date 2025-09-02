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



---

### **唯一算法分类**  
**倍增法（Binary Lifting）**

---

### **综合分析与结论**  
**核心思路**：  
题目要求通过逆向推导找到最终牌堆中指定位置的初始编号。由于直接模拟洗牌过程无法处理大范围的 N，各题解均采用**倍增法**预处理位置转移路径，将线性时间的操作优化为对数时间。核心步骤包括：  
1. **逆向建模**：从最终位置倒推其在每一轮洗牌中的位置。  
2. **倍增预处理**：构建 `p[i][j]` 或 `f[i][j]` 数组，表示经过 2^i 次操作后，位置 j 的转移结果。  
3. **二进制分解**：对每个询问，通过二进制拆分步数快速计算最终位置。  

**可视化设计**：  
- **动画方案**：  
  - 用网格表示牌堆状态，高亮当前处理的位置（如红色方块）。  
  - 每次倍增跳转时显示路径（如绿色箭头），并标注转移次数（如 2^i）。  
  - 当位置超出洗牌范围（M 张牌）时，切换为逐位移动（蓝色箭头）。  
- **复古风格**：  
  - 使用 8 位像素风格，牌堆以方格表示，颜色区分洗牌区（黄色）和非洗牌区（灰色）。  
  - 音效触发：关键操作（如倍增跳转）播放短促“滴”声，完成查询时播放上扬音效。  
- **交互控制**：支持单步执行、调整动画速度，对比不同题解的倍增路径差异。  

---

### **题解清单（≥4星）**  
1. **XL4453（5星）**  
   - **亮点**：代码简洁，预处理 `p[i][j]` 时采用自下而上初始化，通过逆向洗牌规则直接建模。  
   - **关键代码**：  
     ```cpp  
     for(int i=m-1;i>=0;i--){  
         scanf("%d",&x);  
         p[0][m-x+1]=i;  // 逆向映射洗牌规则  
     }  
     ```  
   - **心得**：“细节上注意要减一”体现对边界处理的精准把控。  

2. **Graphcity（4.5星）**  
   - **亮点**：引入 `f[i][j]` 表示走出洗牌区的状态，结合二分法处理中间轮次。  
   - **关键代码**：  
     ```cpp  
     if(Check(Start,mid,Rnd)) r=mid;  // 二分判断是否走出洗牌区  
     else l=mid+1;  
     ```  
   - **心得**：分情况讨论走出洗牌区前后的位置计算，逻辑清晰。  

3. **littleming（4星）**  
   - **亮点**：滑动窗口思想优化非洗牌部分的处理，代码注释详尽。  
   - **关键代码**：  
     ```cpp  
     ll cnt=min(x,n-m+1),t=max(0,x-(n-m+1));  // 划分洗牌与非洗牌区间  
     ```  
   - **心得**：参考官方题解思路，实现高效且可读性强。  

---

### **最优思路或技巧提炼**  
1. **逆向思维**：从最终位置反推初始位置，避免直接模拟大规模操作。  
2. **倍增预处理**：通过 `p[i][j]` 或 `f[i][j]` 数组，将单次操作复杂度降至 O(log N)。  
3. **二进制分解**：对步数进行二进制拆分，快速跳转到目标位置。  
4. **边界处理**：区分洗牌区和非洗牌区，分别设计转移规则。  

---

### **同类型题或类似算法套路**  
- **倍增法应用**：常用于处理链式跳转问题（如 LCA、后缀数组）。  
- **逆向推导**：适用于需要倒序操作的场景（如动态规划逆向状态转移）。  

---

### **相似题目推荐**  
1. **P1081 开车旅行**（倍增法预处理决策）  
2. **P3304 [SDOI2013] 直径**（树链剖分与倍增结合）  
3. **P3834 可持久化线段树**（静态区间第 K 大，逆向思维优化）  

---

### **代码核心实现**  
**XL4453 的预处理与查询逻辑**：  
```cpp  
// 预处理倍增数组  
for(int i=1;i<=29;i++)  
for(int j=1;j<=m;j++)  
    p[i][j]=p[i-1][p[i-1][j]];  

// 查询处理  
now = m-1;  
for(int i=29;i>=0;i--){  
    if(now+(1<<i)<=n && p[i][x]){  
        now += (1<<i);  
        x = p[i][x];  
    }  
}  
```  

---

### **可视化与复古游戏化设计**  
**动画实现**：  
1. **Canvas 绘制**：  
   - 初始化牌堆为纵向排列的方格，颜色区分洗牌区（黄）和非洗牌区（灰）。  
   - 当前处理位置用红色高亮，倍增跳转路径用绿色箭头连接。  
2. **音效设计**：  
   - 跳转时播放 8-bit “滴”声，完成查询时播放胜利音效。  
3. **交互控制**：  
   - 滑动条调节动画速度（1x~10x），按钮控制暂停/继续。  
   - 展示不同题解的倍增路径对比，用不同颜色区分。  

**复古风格示例**：  
```javascript  
// 伪代码：绘制牌堆  
function drawDeck(positions) {  
    ctx.fillStyle = "#FFFF00"; // 洗牌区黄色  
    for (let i=0; i<m; i++) ctx.fillRect(50, 100-i*20, 30, 15);  
    ctx.fillStyle = "#808080"; // 非洗牌区灰色  
    for (let i=m; i<n; i++) ctx.fillRect(50, 100-i*20, 30, 15);  
}  
```  

---

**总结**：本题通过逆向思维与倍增法高效解决了大规模洗牌模拟问题，可视化设计结合复古风格与交互控制，可深入理解算法核心逻辑。

---
处理用时：73.99秒