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
本题核心是静态区间最值查询（RMQ），主流解法聚焦于 **ST表、线段树、树状数组、分块** 等数据结构。各解法对比：
- **ST表**：最优时间复杂度（O(nlogn)预处理 + O(1)查询），代码简洁，适合本题高查询量（Q=1.8e5）
- **线段树**：通用性强，但常数较大，适用于动态更新场景（本题无需）
- **树状数组**：递归查询效率较低，代码复杂度高，非最优解
- **分块**：预处理O(n)，查询O(√n)，在特定场景下表现优秀

---

### 精选题解与评分

#### 1. 白烛葵（ST表） ⭐⭐⭐⭐⭐
- **关键亮点**：
  - 完整ST表模板实现，清晰拆分最大/最小值预处理
  - 高效查询（316ms），代码仅28行
  - 预处理循环边界处理严谨（`j <= 21`避免溢出）
- **核心代码**：
  ```cpp
  void ST() {
      for(int j=1; (1<<j)<=n; j++)
          for(int i=1; i+(1<<j)-1<=n; i++) {
              f1[i][j] = max(f1[i][j-1], f1[i+(1<<(j-1))][j-1]);
              f2[i][j] = min(f2[i][j-1], f2[i+(1<<(j-1))][j-1]);
          }
  }
  int query(int l, int r) {
      int k = log2(r-l+1);
      return max(f1[l][k], f1[r-(1<<k)+1][k]) - min(f2[l][k], f2[r-(1<<k)+1][k]);
  }
  ```

#### 2. Yeji_（RMQ） ⭐⭐⭐⭐
- **关键亮点**：
  - 详细讲解RMQ原理与状态转移方程
  - 分函数实现极大提升可读性
  - 预处理log值优化查询效率
- **调试心得**：
  > "RMQ的区间拆分思想需要仔细理解，特别是当区间长度不是2的幂时，使用两个重叠区间的覆盖是关键技巧"

#### 3. Newuser（分块） ⭐⭐⭐⭐
- **关键亮点**：
  - 创新性使用前缀/后缀极值预处理
  - 块间ST表优化提升查询效率
  - 实测180ms高效表现
- **核心代码**：
  ```cpp
  void Init() {
      for(int i=1; i<=s; i++) // 块内极值
          for(int j=bl[i]; j<=br[i]; j++)
              mex[i][i] = max(mex[i][i], a[j]);
      for(int i=1; i<s; i++) // 块间极值ST表
          for(int j=i+1; j<=s; j++)
              mex[i][j] = max(mex[i][j-1], mex[j][j]);
  }
  ```

---

### 最优思路总结
**ST表双表法**为核心解法：
1. **预处理**：对每个点i，计算从i开始2^j长度的区间极值
2. **查询优化**：将任意区间分解为两个2^k长度的重叠区间（k=⌊log2(len)⌋）
3. **极值差计算**：O(1)时间内获取最大最小值差

---

### 相似题目推荐
1. [P3865 ST表模板](https://www.luogu.com.cn/problem/P3865) - 标准RMQ问题
2. [P1816 忠诚](https://www.luogu.com.cn/problem/P1816) - 多区间最小值查询
3. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440) - 滑动窗口极值（单调队列）

---

### 关键代码实现（ST表）
完整预处理与查询逻辑：
```cpp
int st_max[N][20], st_min[N][20], log_2[N];

void init() {
    for(int i=1; i<=n; i++) {
        st_max[i][0] = st_min[i][0] = a[i];
    }
    for(int j=1; (1<<j)<=n; j++) {
        for(int i=1; i+(1<<j)-1<=n; i++) {
            st_max[i][j] = max(st_max[i][j-1], st_max[i+(1<<(j-1))][j-1]);
            st_min[i][j] = min(st_min[i][j-1], st_min[i+(1<<(j-1))][j-1]);
        }
    }
    // 预处理log表加速
    for(int i=2; i<=n; i++) log_2[i] = log_2[i>>1] + 1;
}

int query(int l, int r) {
    int k = log_2[r-l+1];
    int maxv = max(st_max[l][k], st_max[r-(1<<k)+1][k]);
    int minv = min(st_min[l][k], st_min[r-(1<<k)+1][k]);
    return maxv - minv;
}
```

---
处理用时：61.88秒