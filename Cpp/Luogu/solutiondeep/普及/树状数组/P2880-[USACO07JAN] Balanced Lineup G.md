# 题目信息

# [USACO07JAN] Balanced Lineup G

## 题目描述

For the daily milking, Farmer John's N cows (1 ≤ N ≤ 50,000) always line up in the same order. One day Farmer John decides to organize a game of Ultimate Frisbee with some of the cows. To keep things simple, he will take a contiguous range of cows from the milking lineup to play the game. However, for all the cows to have fun they should not differ too much in height.

Farmer John has made a list of Q (1 ≤ Q ≤ 180,000) potential groups of cows and their heights (1 ≤ height ≤ 1,000,000). For each group, he wants your help to determine the difference in height between the shortest and the tallest cow in the group.

每天,农夫 John 的 $n(1\le n\le 5\times 10^4)$ 头牛总是按同一序列排队。

有一天, John 决定让一些牛们玩一场飞盘比赛。他准备找一群在队列中位置连续的牛来进行比赛。但是为了避免水平悬殊，牛的身高不应该相差太大。John 准备了 $q(1\le q\le 1.8\times10^5)$ 个可能的牛的选择和所有牛的身高 $h_i(1\le h_i\le 10^6,1\le i\le n)$。他想知道每一组里面最高和最低的牛的身高差。

## 样例 #1

### 输入

```
6 3
1
7
3
4
2
5
1 5
4 6
2 2```

### 输出

```
6
3
0```

# AI分析结果

### 综合分析与结论

该题目要求在一个区间内查询最大值与最小值的差，属于典型的区间查询问题（RMQ）。题解中主要使用了以下几种算法：

1. **ST表**：通过预处理O(nlogn)的时间复杂度，支持O(1)的查询，适合处理大量查询的场景。
2. **线段树**：预处理O(n)，查询O(logn)，适合动态更新的场景，但本题不需要更新操作。
3. **树状数组**：预处理O(nlogn)，查询O(logn)，虽然不如ST表高效，但代码实现简单。
4. **分块**：预处理O(n)，查询O(sqrt(n))，适合查询次数较少的场景。

从题解质量来看，ST表和线段树的实现较为清晰，且代码可读性较高。树状数组和分块的实现相对复杂，且效率不如ST表。因此，ST表是最优的选择。

### 所选高星题解

#### 1. 题解作者：白烛葵
- **星级**：★★★★★
- **关键亮点**：使用ST表实现，代码简洁，思路清晰，预处理和查询部分都写得非常清楚，适合初学者理解。
- **核心代码**：
  ```cpp
  void ST(){
      for(int i=1;i<=n;i++){
          st_max[i][0]=a[i];
          st_min[i][0]=a[i];
      }
      int t=log(n)/log(2)+1;
      for(int j=1;j<t;j++){
          for(int i=1;i<=n-(1<<j)+1;i++){
              st_max[i][j]=max(st_max[i][j-1],st_max[i+(1<<(j-1))][j-1]);
              st_min[i][j]=min(st_min[i][j-1],st_min[i+(1<<(j-1))][j-1]);
          }
      } 
  }
  int st_maxn(int l,int r){
      int k=log(r-l+1)/log(2);
      return max(st_max[l][k],st_max[r-(1<<k)+1][k]);
  }
  int st_minn(int l,int r){
      int k=log(r-l+1)/log(2);
      return min(st_min[l][k],st_min[r-(1<<k)+1][k]);
  }
  ```
- **个人心得**：作者提到ST表是“短、少、快”的算法，非常适合处理这类问题，且代码量少，容易实现。

#### 2. 题解作者：Eason_AC
- **星级**：★★★★☆
- **关键亮点**：使用ST表实现，代码结构清晰，预处理和查询部分分开，逻辑分明，适合进阶学习。
- **核心代码**：
  ```cpp
  void pre() {
      for(int j = 1; j <= 20; ++j)
          for(int i = 1; i + (1 << j) - 1 <= n; ++i)
              f1[i][j] = max(f1[i][j - 1], f1[i + (1 << (j - 1))][j - 1]), 
              f2[i][j] = min(f2[i][j - 1], f2[i + (1 << (j - 1))][j - 1]);
  }
  int RMQ(int l, int r) {
      int k = log2(r - l + 1);
      return max(f1[l][k], f1[r - (1 << k) + 1][k]) - min(f2[l][k], f2[r - (1 << k) + 1][k]);
  }
  ```
- **个人心得**：作者提到ST表是“神奇的算法”，强调了其预处理和查询的高效性，适合处理大量查询的场景。

#### 3. 题解作者：stone_juice石汁
- **星级**：★★★★
- **关键亮点**：使用树状数组实现，虽然效率不如ST表，但代码实现较为详细，适合学习树状数组的读者。
- **核心代码**：
  ```cpp
  void _add(int x, int k) {
      for(; x <= n; x += lowbit(x)) {
          treex[x] = max(treex[x], k);
          treen[x] = min(treen[x], k);
      }
  }
  int _findmax(int x, int y) {
      if(y > x) {
          if(y - lowbit(y) > x) return max(treex[y], _findmax(x, y - lowbit(y)));
          else return max(a[y], _findmax(x, y - 1));
      }
      return a[x];
  }
  ```
- **个人心得**：作者详细解释了树状数组的维护过程，适合对树状数组不熟悉的读者学习。

### 最优关键思路与技巧

1. **ST表的倍增思想**：通过预处理将区间查询问题转化为O(1)的查询，适合处理大量查询的场景。
2. **线段树的区间维护**：虽然查询效率不如ST表，但适合动态更新的场景。
3. **树状数组的维护**：虽然效率不如ST表，但代码实现简单，适合初学者理解。

### 拓展思路

- **动态更新**：如果题目要求支持动态更新，线段树是更好的选择。
- **多维度查询**：如果题目要求多维度的区间查询，可以考虑使用二维线段树或树状数组。

### 推荐题目

1. **P3865 【模板】ST表**：练习ST表的实现与应用。
2. **P3372 【模板】线段树 1**：练习线段树的实现与应用。
3. **P3368 【模板】树状数组 1**：练习树状数组的实现与应用。

### 个人心得总结

- **ST表的优势**：预处理时间O(nlogn)，查询时间O(1)，适合处理大量查询的场景。
- **线段树的灵活性**：虽然查询时间O(logn)，但支持动态更新，适合更复杂的场景。
- **树状数组的简洁性**：代码实现简单，适合初学者理解，但效率不如ST表。

---
处理用时：49.13秒