# 题目信息

# [BalticOI 2008] 选举

## 题目描述

The citizens of Byteland have recently been voting in the parliamentary elections. Now, when the results
have been published, the parties have to decide on a coalition to form the government.

Each party received a certain number of seats in the parliament. The coalition must be a subset of the
parties such that together they have strictly more than half of all the seats in the parliament. It is desirable for
the coalition to have as many seats as possible, to ensure they can still pass their proposed laws even if a few
of their members are absent from a parliament session.
A coalition is called redundant if one of its parties can be removed with the remaining ones still having
more than half of the seats in the parliament. Of course, such a removable party would effectively have no
power — the other members of the coalition would be able to force the laws regardless of its opinion.


Write a program that:

- reads the election results from the standard input,
- finds a non-redundant coalition that has the maximal possible number of seats in the parliament,
- writes the description of this coalition to the standard output.

### Input

The first line of the standard input contains one integer $n\ (1\le n\le 300)$ — the number of parties that participated in the elections. The parties are numbered from $1$ to $n$.

The second line contains n nonnegative integers $a_1,\dots,a_n$, separated by single spaces, where $a_i$
is the
number of seats received by the $i$-th party. You may assume that the total number of seats in the parliament
will be positive and lower or equal to $100000$.

Additionally, in test cases worth $40\%$ of points, the number of parties will not exceed $20$.

### Output

The first line of the standard output should contain one integer $k$ — the number of parties in a non-redundant
coalition which has the maximal number of seats.
The second line should contain $k$ distinct integers separated by single spaces — the numbers of parties
that form the coalition.

If there are several non-redundant coalitions with the maximal number of seats, you may output any of
them. The member parties can be listed in any order.

### 题目翻译

Byteland 国的居民最近一直为议会选举投票。现在，当结果公布的时候，党派不得不决定联合组建政府。 

每个党派都会获得议会中的一定席位。联合政府由这些党派中的一部分组成，他们在议会中的席位数之和**严格大于**总席位数的一半。对于联合政府来说，席位越多越好。

一个**过剩**的联合政府是指联合政府中的一个党派被移出后，剩余的联合政府在国会中仍有过半数的席位。

请写一个程序能够：

-    读取选举结果；
-    找到一个在议会中有着**最大可能席位数**且**不过剩**的联合政府；
-    输出这个联合政府的描述。


## 说明/提示

对于 $40\%$ 的数据，$n\le 20$；

对于全部数据，$1\le n\le 300$。

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
2
2 4```

# AI分析结果



**唯一算法分类**：动态规划（背包问题）

---

### 题解思路与算法要点

#### 核心问题转化
1. **非冗余条件**：联合政府总席位为 \(k\)，需满足对所有选中党派 \(a_i\)，有 \(k - a_i \leq \text{sum}/2\)。
2. **最大化 \(k\)**：在满足上述条件下，找到最大的 \(k\) 并构造方案。

#### 关键算法步骤
1. **排序预处理**：将党派按席位数从大到小排序，确保处理顺序避免后效性。
2. **动态规划（背包）**：
   - 定义 `dp[j]` 表示能否达到 \(j\) 个席位。
   - 对每个党派 \(a_i\)，逆序更新 `dp[j]`，仅允许 \(j \leq a_i + \text{sum}/2\)。
3. **路径回溯**：记录每个状态由哪个党派转移而来，用于构造最终方案。

#### 解决难点
- **后效性消除**：排序后，大党优先处理，确保后续小党加入时不会破坏已满足的条件。
- **路径记录**：通过标记状态转移来源，回溯得到具体党派组合。

---

### 题解评分（≥4星）

1. **CodyTheWolf（5星）**
   - **亮点**：代码简洁，时空复杂度优秀，排序策略清晰，路径记录高效。
   - **代码片段**：
     ```cpp
     sort(a+1,a+n+1);
     for(int i=n;i>=1;i--)
         for(int k=s/2+a[i].first; k>=a[i].first; k--)
             if(bag[k-a[i].first] && !bag[k]) 
                 bag[k] = i; // 记录转移来源
     ```

2. **Irisany（4星）**
   - **亮点**：使用 `bitset` 优化空间，并行更新状态与方案记录。
   - **代码片段**：
     ```cpp
     if (!f[v] && f[v - base[i].fr])
         b[v] = b[v - base[i].fr], b[v].set(base[i].sc), f[v] = 1;
     ```

3. **Hope2075（4星）**
   - **亮点**：二维状态数组明确，前驱记录直观。
   - **代码片段**：
     ```cpp
     if(pr[i-1][j] && j <= sum/2 && list[i].num+j > sum/2)
         termcnt = max(termcnt, list[i].num+j);
     ```

---

### 最优思路提炼

1. **排序消除后效性**：从大到小处理党派，确保每个党派加入时满足其约束条件。
2. **逆向背包更新**：逆序更新背包状态，避免重复计数。
3. **路径回溯技巧**：记录状态转移来源，快速构造方案。

---

### 同类型题推荐

1. **P4394 [BOI2008]Elect**：本题双倍经验。
2. **P2347 砝码称重**：背包问题变种，需组合不同重量。
3. **P1064 金明的预算方案**：依赖背包问题，需处理主件与附件。

---

### 算法可视化设计

1. **像素风格动态规划演示**：
   - **Canvas 绘制**：党派显示为不同颜色方块，按大小排列。
   - **背包状态更新**：选中党派时，对应背包区间颜色高亮。
   - **音效触发**：选中党派时播放“点击”音效，找到最优解时播放胜利音效。
2. **交互控制**：
   - **步进执行**：手动控制处理每个党派的背包更新。
   - **自动模式**：AI 自动执行，速度可调。
3. **状态高亮**：当前处理党派、更新的背包区间、最大合法 \(k\) 值。

**代码片段（伪代码）**：
```javascript
// 初始化 Canvas 和音效
drawParties(sortedParties);
playBackgroundMusic();

// 动态规划过程
for (let i = 0; i < n; i++) {
    highlightCurrentParty(i);
    for (let j = maxSum; j >= parties[i].seats; j--) {
        if (dp[j - parties[i].seats] && !dp[j]) {
            dp[j] = true;
            path[j] = i;
            playSound('select');
            updateCanvas(j, parties[i].color);
        }
    }
}
```

---

### 个人心得摘录

- **CodyTheWolf**：排序后处理确保每个党派的条件在加入时即被满足，避免后效性。
- **Irisany**：`bitset` 优化路径记录，空间效率极高，但需注意位操作细节。
- **Hope2075**：二维数组记录状态转移，直观但需注意内存限制，适合小规模数据。

---

**总结**：通过排序与动态规划结合，解决冗余条件约束下的最大化问题，路径记录技巧是关键。

---
处理用时：122.43秒