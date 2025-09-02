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

### 题目翻译
# 电影院售票员

## 题目描述
Berland的所有电影院大厅都是矩形，每排有 $K$ 个座位，共 $K$ 排，且 $K$ 是奇数。排号和座位号从 $1$ 到 $K$ 编号。出于安全考虑，到售票处买票的人不允许自己选择座位。以前，座位选择由售票员负责，但现在这由一个特殊的座位安排程序负责。人们发现，Berland的绝大多数居民去电影院是为了看电影，因此他们希望尽可能坐在大厅中心附近。此外，一群 $M$ 个人来看电影，他们必须在同一排占据 $M$ 个连续的座位。让我们来阐述一下程序选择座位和售票的算法。当有 $M$ 个座位的请求到来时，程序应确定排号 $x$ 以及该排座位号的区间 $[y_{l},y_{r}]$，其中 $y_{r}-y_{l}+1 = M$。在所有可能的方案中，程序应选择使所有座位到中心的总距离函数值最小的方案。设 $(zx,zy)$ 是最 “中心” 座位的排号和座位号。那么座位到大厅中心的距离函数值为 $\sum_{i = 1}^{M}(|x - zx|+|y_{i}-zy|)$。如果有多个方案的最小函数值相同，程序应选择离屏幕更近的方案（即排号 $x$ 更小）。如果仍然有多个方案，应选择 $y_{l}$ 最小的方案。如果到现在你还没明白，你的任务就是模拟这个程序的工作。

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
- **思路对比**：
    - 404Not_Found：使用树状数组维护每一行的区间和，枚举所有合法方案，通过数学推导分类讨论计算花费，选择花费最小的方案。
    - ncwzdlsd：采用贪心策略，认为同一行的人坐得越紧凑越好，直接枚举每一波人坐在哪一行以及该行的起始位置，判断能否坐下并计算花费。
    - 一铭君一：直接暴力枚举每一排人左侧排头的位置，检查后续位置是否为空，计算总花费更新答案，还进行了小优化。
    - YNH_QAQ：同样是贪心，枚举能坐下时坐在哪一行的起始位置，用数组存储电影院状态。
- **算法要点对比**：
    - 404Not_Found：树状数组维护区间和，等差数列求和公式计算花费。
    - ncwzdlsd：暴力枚举和简单的曼哈顿距离计算。
    - 一铭君一：暴力枚举和小优化（跳过无效位置）。
    - YNH_QAQ：暴力枚举和曼哈顿距离计算。
- **难点对比**：
    - 404Not_Found：树状数组的使用和花费计算的分类讨论。
    - ncwzdlsd：无明显难点，主要是枚举和判断。
    - 一铭君一：小优化的实现和复杂度分析。
    - YNH_QAQ：无明显难点，主要是枚举和判断。

### 所选题解
- **404Not_Found（5星）**：
    - **关键亮点**：思路清晰，使用树状数组优化区间查询，通过数学推导优化花费计算，复杂度分析准确。
    - **核心代码**：
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
- **一铭君一（4星）**：
    - **关键亮点**：强调了暴力解法的可行性，进行了小优化，复杂度分析合理，提醒在比赛和练习中根据复杂度选择简单代码。
    - **核心代码**：
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

### 最优关键思路或技巧
- 使用树状数组维护每一行的区间和，优化区间查询操作。
- 通过数学推导分类讨论计算花费，避免循环累加，提高计算效率。
- 在暴力枚举时进行小优化，跳过无效位置，减少不必要的计算。

### 可拓展之处
同类型题可能会改变座位的排列方式（如非矩形）、增加限制条件（如不同区域票价不同）等。类似算法套路有枚举法、贪心算法、数据结构优化等。

### 洛谷推荐题目
- P1007 独木桥
- P1223 排队接水
- P1090 合并果子

### 个人心得摘录与总结
- 404Not_Found：表示从树状数组标签找过来，发现没题解就来写一篇，还提到题目的翻译不清楚，靠度娘才看懂题。总结：在做题时可能会遇到题目描述不清楚的情况，需要借助其他工具理解题意，同时可以积极分享自己的题解帮助他人。
- 一铭君一：强调不管是比赛还是练习，预估好复杂度后要写出最简单的代码，既不容易出错还节省时间，使用数据结构锻炼思维也未尝不可。总结：在解题时要根据复杂度选择合适的解法，简单代码在很多情况下更具优势。 

---
处理用时：35.08秒