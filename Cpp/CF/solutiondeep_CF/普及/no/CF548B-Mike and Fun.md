# 题目信息

# Mike and Fun

## 题目描述

Mike and some bears are playing a game just for fun. Mike is the judge. All bears except Mike are standing in an $ n×m $ grid, there's exactly one bear in each cell. We denote the bear standing in column number $ j $ of row number $ i $ by $ (i,j) $ . Mike's hands are on his ears (since he's the judge) and each bear standing in the grid has hands either on his mouth or his eyes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF548B/7fc4231ff2f142e0d53dc7e0b0a98c037c896437.png)
 
 They play for $ q $ rounds. In each round, Mike chooses a bear $ (i,j) $ and tells him to change his state i. e. if his hands are on his mouth, then he'll put his hands on his eyes or he'll put his hands on his mouth otherwise. After that, Mike wants to know the score of the bears.

Score of the bears is the maximum over all rows of number of consecutive bears with hands on their eyes in that row.

Since bears are lazy, Mike asked you for help. For each round, tell him the score of these bears after changing the state of a bear selected in that round.

## 样例 #1

### 输入

```
5 4 5
0 1 1 0
1 0 0 1
0 1 1 0
1 0 0 1
0 0 0 0
1 1
1 4
1 1
4 2
4 3
```

### 输出

```
3
4
3
3
4
```

# AI分析结果



# Mike and Fun 题解分析

## 题目内容重写
### 题目描述  
Mike和一些熊在玩一个游戏。熊们排成一个 $n×m$ 的网格，每个单元格中有一只熊。用 $(i,j)$ 表示第 $i$ 行第 $j$ 列的熊。每只熊的手要么放在眼睛上（用1表示）要么放在嘴巴上（用0表示）。游戏进行 $q$ 轮，每轮操作如下：  
1. 翻转某只熊的状态（0变1，1变0）
2. 查询所有行中最长的连续1序列长度的最大值

### 输入格式  
第一行三个整数 $n,m,q$  
接下来 $n$ 行每行 $m$ 个整数表示初始矩阵  
接下来 $q$ 行每行两个整数 $x,y$ 表示要翻转的位置  

### 输出格式  
每次操作后输出当前最大连续1的长度  

**算法分类**：模拟（预处理优化）

---

## 题解综合分析

### 核心解决思路对比
1. **暴力法**（Luo_gu_ykc、_Spectator_）：每次修改后遍历所有行，时间复杂度 $O(nmq)$。当 $n=500, q=5000$ 时总操作次数高达 1.25e9，导致超时。
2. **预处理行最大值法**（LYqwq、开始新的记忆、linnaeuss）：  
   - 预处理每行的最大连续1长度存入数组  
   - 每次修改后**仅重新计算受影响行**的连续1最大值  
   - 全局维护最大值，时间复杂度优化至 $O(nm + q(m + n))$  

### 最优题解亮点

#### 1. LYqwq 的预处理法（评分：★★★★☆）
**核心思路**：  
- 预处理每行的最大值 `mp[i]`  
- 修改时仅更新受影响行的 `mp[x]`  
- 每次查询遍历 `mp` 数组取最大值  

**代码实现**：
```cpp
int mp[N]; // 存储每行的最大值
// 预处理初始值
for(int i=1; i<=n; i++) {
    int sum = 0, current = 0;
    for(int j=1; j<=m; j++) {
        sum = a[i][j] ? sum+1 : 0;
        current = max(current, sum);
    }
    mp[i] = current;
}

// 每次修改后
a[x][y] = !a[x][y];
int sum = 0, new_max = 0;
for(int j=1; j<=m; j++) {
    sum = a[x][j] ? sum+1 : 0;
    new_max = max(new_max, sum);
}
mp[x] = new_max;

// 查询全局最大值
int ans = 0;
for(int i=1; i<=n; i++) 
    ans = max(ans, mp[i]);
```

#### 2. reclusive 的优化思路（评分：★★★★☆）
**关键优化**：  
- 意识到每次修改只影响当前行的连续1分布  
- 维护每行的最大值数组，避免重复计算  

**调试心得**：  
> "暴力解法在n=500, q=5000时会计算1.25e9次，必然超时。必须找到只需重新计算修改行的方法"

---

## 最优技巧总结
1. **行级预处理**：将问题分解到行级别，独立处理每行的连续1最大值  
2. **增量更新**：修改时仅重新计算受影响行，时间复杂度从 $O(nmq)$ 优化至 $O(nm + q(m + n))$  
3. **全局维护技巧**：通过维护每行的极值数组，快速获取全局最大值  

---

## 相似题目推荐
1. [P1440 求区间最小值](https://www.luogu.com.cn/problem/P1440) - 滑动窗口预处理  
2. [P2251 滑动窗口最大值](https://www.luogu.com.cn/problem/P2251) - 维护局部极值  
3. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216) - 二维极值预处理

---
处理用时：62.47秒