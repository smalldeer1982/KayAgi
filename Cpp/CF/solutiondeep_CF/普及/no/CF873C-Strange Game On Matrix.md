# 题目信息

# Strange Game On Matrix

## 题目描述

Ivan is playing a strange game.

He has a matrix $ a $ with $ n $ rows and $ m $ columns. Each element of the matrix is equal to either $ 0 $ or $ 1 $ . Rows and columns are $ 1 $ -indexed. Ivan can replace any number of ones in this matrix with zeroes. After that, his score in the game will be calculated as follows:

1. Initially Ivan's score is $ 0 $ ;
2. In each column, Ivan will find the topmost $ 1 $ (that is, if the current column is $ j $ , then he will find minimum $ i $ such that $ a_{i,j}=1 $ ). If there are no $ 1 $ 's in the column, this column is skipped;
3. Ivan will look at the next $ min(k,n-i+1) $ elements in this column (starting from the element he found) and count the number of $ 1 $ 's among these elements. This number will be added to his score.

Of course, Ivan wants to maximize his score in this strange game. Also he doesn't want to change many elements, so he will replace the minimum possible number of ones with zeroes. Help him to determine the maximum possible score he can get and the minimum possible number of replacements required to achieve that score.

## 说明/提示

In the first example Ivan will replace the element $ a_{1,2} $ .

## 样例 #1

### 输入

```
4 3 2
0 1 0
1 0 1
0 1 0
1 1 1
```

### 输出

```
4 1
```

## 样例 #2

### 输入

```
3 2 1
1 0
0 1
0 0
```

### 输出

```
2 0
```

# AI分析结果



# 奇怪矩阵游戏

## 题目描述

伊万正在玩一个奇怪的游戏。他有一个 $n$行$m$列的01矩阵，可以将任意数量的1变为0。最终得分计算规则为：

1. 对每一列找到最顶端的1（即行号最小的）
2. 从该位置向下取$min(k, n-i+1)$个元素，统计其中1的个数加到总分
3. 要求最大化总分，且在总分最大时使用最少的修改次数

## 算法分类
贪心 + 前缀和

---

## 题解分析

### 最优题解亮点

#### 题解1：Priori_Incantatem（⭐⭐⭐⭐⭐）
**核心思路**：  
1. 列式处理：每列独立处理，使用前缀和快速计算区间和
2. 滑动窗口：枚举每个可能的起始位置，计算固定长度k的窗口内1的个数
3. 双目标优化：同时记录最大得分和对应的最少修改次数

**关键代码**：
```cpp
for(int j=1;j<=m;++j) {
    // 计算前缀和
    for(int i=1;i<=n;++i) 
        s[i] = s[i-1] + a[i][j];
    
    // 滑动窗口找最优解
    int sum = 0, cnt = 0;
    for(int i=1; i+k-1<=n; ++i) {
        int tmp = s[i+k-1] - s[i-1];
        if(tmp > sum || (tmp == sum && s[i-1] < cnt)) {
            sum = tmp;
            cnt = s[i-1];
        }
    }
    ans += sum;
    tot += cnt;
}
```

#### 题解2：DPair（⭐⭐⭐⭐）
**核心思路**：  
1. 逆向处理：从下往上维护滑动窗口的和
2. 动态更新：记录每个位置作为起始点时的最大贡献
3. 贪心选择：优先选择更靠上的最优解，保证修改次数最少

**关键代码**：
```cpp
void work(int col) {
    // 从下到上维护窗口
    for(int i=n; i>=1; --i) {
        dp[i][col] = dp[i+1][col] + a[i][col] - a[i+k][col];
        if(a[i][col] && dp[i][col] >= dp[pos[col]][col]) 
            pos[col] = i;
    }
    ans += dp[pos[col]][col];
    ret += 前缀和[pos[col]-1];
}
```

#### 题解3：czh___（⭐⭐⭐⭐）
**核心思路**：  
1. 实时维护窗口：通过增减操作保持窗口长度
2. 贪心记录：在窗口滑动过程中记录最大值及对应位置
3. 修改次数计算：累加最优窗口前的所有1的数量

**关键代码**：
```cpp
for(int j=1;j<=m;j++) {
    int cur=0, Max=0, row;
    for(int i=1;i<=n;i++) {
        // 维护滑动窗口
        if(i>k && a[i-k][j]) cur--;
        if(a[i][j]) cur++;
        if(i>=k && cur>Max) {
            Max = cur;
            row = i; // 记录窗口右端点
        }
    }
    // 累加row-k前的所有1
    for(int i=1; i<=row-k; i++) 
        ans2 += a[i][j];
}
```

---

## 关键思路总结
1. **列式处理**：各列独立，可单独计算最优解
2. **前缀和优化**：快速计算任意区间的1的个数
3. **滑动窗口**：维护固定长度的窗口，实时更新最优解
4. **双目标处理**：优先最大化分数，其次最小化修改次数

---

## 拓展练习
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
   - 练习滑动窗口的基本应用
2. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)  
   - 二维前缀和的经典应用
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)  
   - 区间统计与贪心决策结合

---

## 心得体会
1. **读题陷阱**：多例题解提到容易误解题意，强调要仔细理解"topmost 1"的定义
2. **优化技巧**：前缀和预处理可将区间查询复杂度降至O(1)
3. **实现细节**：注意行号与数组索引的转换（题目中行列均为1-based）

---
处理用时：93.18秒