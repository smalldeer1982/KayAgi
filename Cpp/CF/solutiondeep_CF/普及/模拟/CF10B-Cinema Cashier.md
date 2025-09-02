# 题目信息

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 样例 #1

### 输入

```
2 1
1 1
```

### 输出

```
1 1 1
-1
```

## 样例 #2

### 输入

```
4 3
1 2 3 1
```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1
```

# AI分析结果

### 题目中文重写
# 电影院售票员

## 题目描述
在伯兰，所有电影院的影厅都是矩形，每个影厅有 $K$ 排，每排有 $K$ 个座位，且 $K$ 是奇数。排号和座位号都从 $1$ 到 $K$ 编号。出于安全考虑，到售票处买票的人不允许自己选择座位。以前，座位的选择由售票员负责，但现在这一职责由一个特殊的座位安排程序承担。人们发现，伯兰的绝大多数居民去电影院是为了看电影，因此他们希望尽可能坐在影厅中心附近。此外，一群 $M$ 个人一起去看电影时，他们必须占据同一排的 $M$ 个连续座位。下面我们来阐述该程序选择座位并售票的算法。当收到需要 $M$ 个座位的请求时，程序应确定排号 $x$ 以及这一排中座位号的区间 $[y_{l},y_{r}]$，其中 $y_{r}-y_{l}+1 = M$。在所有可能的方案中，程序应选择总座位到影厅中心距离函数值最小的方案。设 $(zx, zy)$ 为最“中心”座位的排号和座位号，那么座位到影厅中心的距离函数值为 $\sum_{i = 1}^{M}(|x - zx|+|y_{i}-zy|)$。如果有多个方案的最小函数值相同，程序应选择离屏幕更近的方案（即排号 $x$ 更小）。如果方案仍然有多个，应选择 $y_{l}$ 最小的方案。现在，你的任务是模拟这个程序的工作。

## 样例 #1
### 输入
```
2 1
1 1
```
### 输出
```
1 1 1
-1
```

## 样例 #2
### 输入
```
4 3
1 2 3 1
```
### 输出
```
2 2 2
1 1 2
3 1 3
2 1 1
```

### 题解综合分析与结论
|作者|思路|算法要点|解决难点|时间复杂度|评分|
| ---- | ---- | ---- | ---- | ---- | ---- |
|404Not_Found|枚举所有可能的座位安排方案，用树状数组维护每行的座位占用情况，通过数学方法计算总花费，选择花费最小的方案|树状数组维护区间和，分类讨论计算总花费|计算总花费时需根据座位位置与中心位置的关系分类讨论|$O(nk^2logk)$|4星|
|ncwzdlsd|枚举每一波人坐在哪一行以及该行的起始位置，判断能否坐下并计算总花费，选择花费最小的方案|直接枚举，贪心策略（同一行的人坐得越紧凑，总花费越小）|判断座位是否被占用，计算总花费|$O(NK^3)$|3星|
|一铭君一|枚举每一波人这一排左侧排头的位置，暴力检查后续位置是否为空并计算总花费，选择花费最小的方案，有小优化|直接枚举，小优化（一个位置被证明不行，它后面至少 len 个也不行）|判断座位是否被占用，计算总花费|$O(nk^2)$|4星|
|YNH_QAQ|枚举能坐下时坐在哪一行的起始位置，用数组存储电影院状态，选择花费最小的方案|贪心策略，枚举起始位置|判断座位是否被占用，计算总花费|$O(k^3n)$|3星|

### 所选题解
- 404Not_Found（4星）
    - 关键亮点：使用树状数组维护每行的座位占用情况，通过数学方法分类讨论计算总花费，优化了计算过程。
    - 重点代码：
```cpp
inline int sum(int line,int x)
{
    int res=0;
    for(int i=x;i>=1;i-=lowbit(i))
        res+=tree[line][i];
    return res;
}
inline int query(int line,int l,int r)
{
    return sum(line,r)-sum(line,l-1);
}
inline void add(int line,int x)
{
    for(int i=x;i<=k;i+=lowbit(i))
        tree[line][i]++;
}
inline int cost(int l,int r)
{
    return (l+r)*(r-l+1)>>1;
}
```
    - 核心实现思想：`sum` 函数用于计算树状数组前缀和，`query` 函数用于查询区间和，`add` 函数用于更新树状数组，`cost` 函数用于计算等差数列的和。通过这些函数，结合分类讨论计算总花费，选择最优方案。
- 一铭君一（4星）
    - 关键亮点：直接暴力枚举，复杂度分析准确，有小优化，代码简洁易懂。
    - 重点代码：
```cpp
pair<bool, int> CalcCost(const int &x, const int &y, const int &len)
{
  int sum = 0;
  if(y + len - 1 > k)
    return make_pair(false, len);
  for(int j = 0 ; j < len; j ++)
  {
    if(sits[x][y + j])
      return make_pair(false, j);
    sum += abs(x - mid) + abs(y + j - mid);
  }
  return make_pair(true, sum);
}
```
    - 核心实现思想：`CalcCost` 函数用于检查以 $(x, y)$ 为起始位置的连续 `len` 个座位是否可用，并计算总花费。若可用返回 `true` 和总花费，否则返回 `false` 和不可用的位置。

### 最优关键思路或技巧
- 使用树状数组维护每行的座位占用情况，可在 $O(logk)$ 时间内完成区间查询和单点更新，提高效率。
- 对于总花费的计算，通过数学方法分类讨论，避免了循环累加的 $O(m)$ 复杂度。
- 暴力枚举时，一个位置被证明不行，它后面至少 `len` 个也不行，可跳过这些位置，减少不必要的计算。

### 可拓展之处
同类型题可能会改变座位布局（如非矩形）、增加限制条件（如不同区域票价不同）等。类似算法套路可用于解决资源分配问题，如会议室安排、教室分配等，核心思路都是枚举所有可能的方案，根据一定的规则选择最优方案。

### 推荐洛谷题目
- P1006 传纸条：二维动态规划，涉及路径选择和最优解问题。
- P1048 采药：经典的 0 - 1 背包问题，需要在一定限制条件下选择最优方案。
- P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles：动态规划基础题，从顶部到底部选择一条路径使路径上数字之和最大。

### 个人心得摘录与总结
- 404Not_Found：表示从树状数组标签找过来，发现没题解就来写一篇。强调了题目的翻译不清楚，靠度娘才看懂题。总结：做题时可能会遇到题目表述不清的情况，需要借助其他工具理解题意；同时，发现没有题解时可以自己尝试写，分享解题思路。
- 一铭君一：认为不管是赛场还是平时练习，预估好复杂度后要写最简单的代码，既不易出错又节省时间，使用数据结构锻炼思维也可以。总结：在解题时要平衡代码复杂度和效率，根据实际情况选择合适的方法。 

---
处理用时：40.72秒