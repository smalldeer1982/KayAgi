# 题目信息

# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9```

### 输出

```
10
3
1```

# AI分析结果



【题目中文翻译】
# 网格中的最大公约数

## 题目描述

不久前，Egor学习了用于求两数最大公约数的欧几里得算法。两个数$a$和$b$的最大公约数是能同时整除$a$和$b$的最大整数。凭借这一知识，Egor现在可以解决一个曾经难住他的问题。

Vasily有一个$n$行$m$列的网格，第$i$行第$j$列的格子上写有整数${a_i}_j$。Egor想从左上角（第一行第一列）移动到右下角（最后一行最后一列），并计算路径上所有整数的最大公约数。他只能向右或向下移动。Egor记录了几条路径的不同GCD值，现在想找出可能的最大GCD。

## 样例 #1

### 输入
```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9```

### 输出
```
10
3
1```

---

## 题解对比分析

### 关键思路总结
1. **因数枚举法**：答案必为起点与终点值的GCD的因数，只需枚举该GCD的所有因数
2. **降序验证**：将因数从大到小排序，优先验证大因数，找到第一个可行解即可返回
3. **路径验证优化**：使用动态规划或BFS验证路径存在性，避免暴力枚举所有路径
4. **空间复用技巧**：采用滚动标记或递增计数器代替memset清空数组，提升效率

### 最优题解推荐
#### 1. 菲斯斯夫斯基（★★★★☆）
**核心亮点**：
- 预处理因数降序排列，优先尝试大值
- 状态转移方程简洁，使用位运算优化逻辑判断
- 手动初始化替代memset提升效率

**核心代码**：
```cpp
bool check(int k) {
    for(int i=1;i<=n;i++) // 手动初始化
        for(int j=1;j<=m;j++)
            dp[i][j] = 0;
    
    dp[1][1] = 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((i!=1||j!=1) && a[i][j]%k==0)
                dp[i][j] = dp[i-1][j] | dp[i][j-1];
    return dp[n][m];
}
```

#### 2. Wyy_w123（★★★★☆）
**核心亮点**：
- 分步初始化首行首列，逻辑清晰
- 使用位运算优化状态转移
- 函数式封装提升代码可读性

**核心代码**：
```cpp
bool B(int x) {
    // 初始化首列
    for(int i=1;i<=n;i++) 
        dp[i][1] = dp[i-1][1] & !(a[i][1]%x);
    // 初始化首行
    for(int j=1;j<=m;j++)
        dp[1][j] = dp[1][j-1] & !(a[1][j]%x);
        
    for(int i=2;i<=n;i++) // 状态转移
        for(int j=2;j<=m;j++)
            dp[i][j] = (a[i][j]%x == 0) && (dp[i-1][j] || dp[i][j-1]);
    return dp[n][m];
}
```

#### 3. Iniaugoty（★★★☆☆）
**核心亮点**：
- BFS验证路径存在性，适合稀疏可达场景
- 队列实现空间换时间，减少无效计算

**核心代码**：
```cpp
bool Check(int w) {
    queue<node> q;
    q.push({1,1});
    while(!q.empty()) {
        node u = q.front();
        if(u.x==n && u.y==m) return true; // 提前终止
        // 扩展右、下节点
        if(右节点合法) q.push(...);
        if(下节点合法) q.push(...);
    }
    return false;
}
```

---

## 拓展与总结
### 同类题型推荐
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS路径搜索
2. [P1027 Car的旅行路线](https://www.luogu.com.cn/problem/P1027) - 网格路径规划
3. [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074) - 状态压缩与剪枝

### 调试经验总结
- **因数预处理**：注意处理平方数情况（i*i==g时只记录一次）
- **初始化优化**：使用滚动标记法（如cnt变量）替代memset
- **降序枚举**：优先尝试大因数能显著减少验证次数
- **路径验证**：动态规划法在稠密网格中效率优于BFS

### 关键技巧
```cpp
// 因数降序枚举模板
vector<int> factors;
for(int i=1; i*i<=g; ++i) {
    if(g%i == 0) {
        factors.push_back(g/i);
        if(i != g/i) factors.push_back(i);
    }
}
sort(factors.rbegin(), factors.rend());
```

---
处理用时：79.44秒