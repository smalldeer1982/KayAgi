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


# 💡 Kay的C++算法解析：BalticOI 2008 选举 深入学习指南 💡

> 今天我们来分析"BalticOI 2008 选举"这道C++编程题。本指南将帮助大家理解如何寻找最大席位的非冗余联合政府，掌握动态规划的核心技巧，并通过生动的像素动画直观理解算法执行过程。

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划` + `贪心策略`

🗣️ **初步分析**：
> 这道题的核心在于**动态规划背包模型**结合**贪心排序策略**。想象我们要组装一个高塔，每个党派是不同重量的积木，我们需要选择积木使总重量严格超过一半，且移走任何一块后剩余重量不超过一半。  
> - **核心难点**：需同时满足最大席位和非冗余两个条件，关键在于发现**排序后移除最小元素不影响剩余合法性**的特性  
> - **解决方案**：将党派按席位数降序排序后，用背包DP记录可达席位状态  
> - **可视化设计**：像素动画将展示积木从大到小下落，背包状态动态更新，合法解高亮闪烁  
> - **复古元素**：8-bit音效（积木落袋声、解锁音效），自动演示模式如"俄罗斯方块"逐步构建解法  

---

## 2. 精选优质题解参考

**题解一（作者：CodyTheWolf）**
* **点评**：
  思路创新性地将冗余条件转化为背包约束（$k \in [a_i, a_i+s/2]$），通过降序排序消除后效性。代码简洁高效（空间$O(n)$），回溯方案直接。变量命名`bag[mx]`稍简但逻辑清晰，竞赛实践性强。

**题解二（作者：Irisany）**
* **点评**：
  巧妙使用`bitset`记录方案，空间优化极佳。DP过程中实时检查非冗余条件，双目标同步优化。代码规范性好，`base[i].fr/sc`命名明确，适合学习STL高级技巧。

**题解三（作者：Hope2075）**
* **点评**：
  二维DP状态机思路清晰，`pr[i][j]`明确记录转移路径。边界处理严谨（初始化`pr[0][0]=1`），变量名`termcnt/termid`含义明确，教学示范性强。

---

## 3. 核心难点辨析与解题策略

1.  **关键点：冗余条件的数学转化**
    * **分析**：通过不等式 $k - a_i \leq s/2$ 将"非冗余"转化为 $a_i \geq k - s/2$。降序排序后，当前$a_i$总是最小，自然满足移除条件
    * 💡 **学习笔记**：复杂约束的数学建模是优化算法的钥匙

2.  **关键点：降序排序消除后效性**
    * **分析**：当按席位降序处理时，已选集合中当前元素最小。DP更新时只需考虑 $[a_i, a_i+s/2]$ 范围，保证后续添加更大元素不影响当前合法性
    * 💡 **学习笔记**：排序创造单调性是解决后效性问题的利器

3.  **关键点：DP状态与方案回溯**
    * **分析**：`bag[k]=i`记录最后添加的党派索引，通过`mx -= a[bag[mx]]`回溯路径。类似寻路算法中的父节点指针
    * 💡 **学习笔记**：记录转移来源是输出方案的关键技巧

### ✨ 解题技巧总结
-   **数学转化技巧**：将逻辑约束转化为代数不等式
-   **排序预处理**：创造单调性消除后效性
-   **状态记录回溯**：DP时存储决策路径
-   **边界严谨性**：初始化`dp[0]=true`作为起点

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
* **说明**：综合题解一思路，空间最优的背包实现
* **完整核心代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXT = 1e5 + 5;

pair<int, int> a[305]; // {seats, party_id}
int bag[MAXT]; // 记录到达k的最后添加元素
int ans[305], cnt;

int main() {
    int n, s = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
        s += a[i].first;
    }
    
    sort(a + 1, a + n + 1, greater<pair<int, int>>());
    bag[0] = -1; // 起始状态标记
    
    // 背包DP
    for (int i = 1; i <= n; i++)
        for (int k = s/2 + a[i].first; k >= a[i].first; k--)
            if (bag[k - a[i].first] && !bag[k])
                bag[k] = i; // 记录转移来源
    
    // 查找最大合法席位
    int mx = s;
    while (mx > s/2 && !bag[mx]) mx--;
    
    // 回溯方案
    while (mx > 0) {
        ans[cnt++] = a[bag[mx]].second;
        mx -= a[bag[mx]].first;
    }
    
    cout << cnt << endl;
    for (int i = 0; i < cnt; i++)
        cout << ans[i] << " ";
}
```

**题解一核心片段赏析**
* **亮点**：空间优化到O(n)，完美结合排序与背包
```cpp
sort(a+1, a+n+1, greater<>());
for (int i = 1; i <= n; i++)
    for (int k = s/2 + a[i].first; k >= a[i].first; k--)
        if (bag[k - a[i].first] && !bag[k]) 
            bag[k] = i;  // 关键转移
```
* **代码解读**：
  > 内层循环从`(s/2+a_i)`向下扫描，保证只考虑合法区间。`bag[k]`存储达到席位`k`的最后添加元素索引，类似"最后一步"记录器

**题解二核心片段赏析**
* **亮点**：bitset高效存储方案
```cpp
bitset<MAXN> b[MAXM]; 
for (int i = 1; i <= n; i++) {
    for (int v = sum; v >= base[i].fr; v--) {
        if (!f[v] && f[v - base[i].fr]) {
            b[v] = b[v - base[i].fr];
            b[v].set(base[i].sc);  // 设置党派选择位
            f[v] = 1;
        }
    }
}
```
* **代码解读**：
  > `b[v] = b[v-base[i].fr]`复制原方案，`b[v].set()`标记新选党派。通过位操作压缩存储方案，空间效率极高

---

## 5. 算法可视化：像素动画演示

* **主题**：8-bit风格"选举积木塔"
* **核心演示**：降序积木入包过程，DP状态实时更新

![](https://via.placeholder.com/400x200?text=像素动画示意图)  
*图：积木按大小降序下落，背包状态动态着色*

1.  **场景初始化**：
    - 顶部：党派积木按席位数降序排列（大积木在上）
    - 中部：背包状态条（0→s），过半线红色标记
    - 底部：控制面板（步进/自动/重置）

2.  **动态演示**：
    ```mermaid
    sequenceDiagram
        积木队列->>+背包: 当前积木下落
        背包->>+状态检测: 更新可达区间[s/2+a_i, a_i]
        状态检测-->>背包: 合法区域绿色高亮
        背包->>+方案记录: 存储bag[k]=i
        方案记录-->>-UI: 点亮对应党派图标
    ```

3.  **交互特效**：
    - **音效**：积木落袋(咔哒声)，解锁方案(胜利音阶)
    - **高亮**：合法区间绿色脉动，最终方案金色边框
    - **自动模式**：AI像玩俄罗斯方块自动构建最优解

4.  **游戏化设计**：
    - 每完成一个合法解获得★
    - 连续找到更优解触发Combo特效
    - 最终方案展示如通关画面

---

## 6. 拓展练习与相似问题思考

1.  **相似问题**：
    - 子集和问题（附加约束条件）
    - 背包问题+方案回溯
    - 贪心策略证明与应用

2.  **洛谷推荐**：
    - **P1064** 金明的预算方案：依赖背包的变种
    - **P1156** 垃圾陷阱：时间维背包应用
    - **P5020** 货币系统：背包求极大无关组

---

> 本次题解分析展示了如何将复杂约束转化为动态规划模型。记住：排序预处理+状态记录回溯是解决此类问题的黄金组合！继续挑战更多背包变种问题吧！💪

---
处理用时：132.97秒