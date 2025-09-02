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



# 【唯一算法分类】
动态规划（背包问题）

---

## 【综合分析与结论】

### 核心思路
题目要求找到**最大席位且不可移除任意成员的联合政府**，本质是寻找一个满足以下条件的最大子集：
1. 子集和 > 总席位数的一半
2. 任意元素移除后，剩余和 ≤ 总席位数的一半

### 关键算法流程
1. **排序**：将政党按席位数从大到小排序，确保后续处理的元素是当前最小的。
2. **背包DP**：维护一个布尔型数组 `f[j]` 表示能否凑出席位数 `j`。
3. **条件检查**：在更新背包时，若 `j > sum/2` 且 `j - a[i] ≤ sum/2`，则记录为候选解。
4. **路径回溯**：通过记录状态转移路径，还原选中的政党。

### 解决难点
- **冗余性判断**：通过排序确保每次处理的元素是当前最小的，只需检查移除该元素后是否仍满足条件。
- **空间优化**：使用滚动数组或 `bitset` 压缩状态。
- **路径记录**：通过二维数组或 `bitset` 记录每个状态的选择情况。

### 可视化设计
1. **动画方案**：
   - **排序展示**：用像素风格展示政党按席位数从高到低排列的过程。
   - **背包更新**：每次处理一个政党时，高亮该元素并展示对应背包状态的更新。
   - **条件检查**：当 `j > sum/2` 时，用闪烁效果提示候选解。
2. **复古风格**：
   - **8位音效**：在选中政党时播放“拾取”音效，找到最优解时播放胜利音效。
   - **像素网格**：用不同颜色方块表示已选/未选政党，背包状态以进度条形式展示。
3. **交互功能**：
   - **步进控制**：允许单步执行观察背包更新。
   - **自动演示**：模拟“AI”自动运行算法，展示关键步骤。

---

## 【题解清单 (≥4星)】

### 1. CodyTheWolf 的题解（★★★★☆）
- **亮点**：逆序排序消除后效性，简洁的背包实现。
- **核心代码**：
  ```cpp
  sort(a+1,a+n+1);
  for(int i=n;i>=1;i--)
    for(int k=s/2+a[i].first; k>=a[i].first; k--)
      if(bag[k-a[i].first] && !bag[k]) bag[k]=i;
  ```

### 2. Irisany 的题解（★★★★☆）
- **亮点**：`bitset` 优化空间，代码简洁。
- **核心代码**：
  ```cpp
  bitset<MAXN> b[MAXM];
  if (!f[v] && f[v - base[i].fr])
    b[v] = b[v - base[i].fr], b[v].set(base[i].sc);
  ```

### 3. Hope2075 的题解（★★★★☆）
- **亮点**：二维数组记录路径，直观易懂。
- **核心代码**：
  ```cpp
  if(pr[i-1][j]) pr[i][j] = 1;
  if(pr[i-1][j] && j <= sum/2 && list[i].num+j > sum/2)
    termcnt = list[i].num+j;
  ```

---

## 【最优思路提炼】

### 核心技巧
1. **排序消除后效性**：从大到小处理元素，确保后续选择不会破坏冗余性条件。
2. **背包状态压缩**：使用一维数组或 `bitset` 优化空间。
3. **路径回溯**：通过记录转移路径或 `bitset` 快速还原方案。

### 思维突破点
- 将冗余性条件转化为数学不等式：`sum - a_i ≤ total/2`
- 将问题转换为背包问题的变形，寻找满足特殊约束的最大值。

---

## 【同类型题推荐】
1. **P4394 [BalticOI 2008]选举**（本题双倍经验）
2. **P1064 金明的预算方案**（依赖背包）
3. **P1048 采药**（经典01背包）

---

## 【个人心得摘录】
- **CodyTheWolf**：排序后处理避免后效性，是本题的关键。
- **Irisany**：贪心无法处理冗余条件，必须依赖动态规划。
- **Hope2075**：二维数组路径记录需注意空间限制，可用 `char` 类型优化。

---

## 【可视化代码片段（伪代码）】
```javascript
// 排序与背包更新动画
function visualize() {
  let parties = sortedData; // 已排序的政党数据
  let dp = new Array(total+1).fill(false);
  dp[0] = true;

  for (let i = 0; i < parties.length; i++) {
    // 高亮当前处理的政党
    highlightParty(parties[i]);
    
    for (let j = total; j >= parties[i].seats; j--) {
      if (dp[j - parties[i].seats] && !dp[j]) {
        dp[j] = true;
        // 更新背包状态显示
        updateDPCell(j);
        
        // 检查是否为候选解
        if (j > halfTotal && j - parties[i].seats <= halfTotal) {
          flashCandidate(j);
        }
      }
    }
  }
}
```

---
处理用时：68.75秒