# 题目信息

# Vlad and Avoiding X

## 题目描述

Vladislav has a grid of size $ 7 \times 7 $ , where each cell is colored black or white. In one operation, he can choose any cell and change its color (black $ \leftrightarrow $ white).

Find the minimum number of operations required to ensure that there are no black cells with four diagonal neighbors also being black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/b96bca00ab008cd943717e290ba9a2dfa2e51cb4.png)The left image shows that initially there are two black cells violating the condition. By flipping one cell, the grid will work.

## 说明/提示

The first test case is illustrated in the statement.

The second test case is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/7822d3ff7cf3565e0c2fe901fc2a936bc32a31de.png)In the third test case, the grid already satisfies the condition.

## 样例 #1

### 输入

```
4
WWWWWWW
WWWWBBB
WWWWWBW
WWBBBBB
WWWBWWW
WWBBBWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
WBBBBBW
WBBBBBW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
BBBBBBB
BBBBBBB
WWWWWWW
BBBBBBB
BBBBBBB
BBBBBBB```

### 输出

```
1
2
0
5```

# AI分析结果

### 题目翻译
**Vlad and Avoiding X**

**题目描述**

Vladislav 有一个大小为 $7 \times 7$ 的网格，每个单元格被涂成黑色或白色。在一次操作中，他可以选择任何一个单元格并改变其颜色（黑色 $\leftrightarrow$ 白色）。

找到确保没有黑色单元格的四个对角线相邻单元格也是黑色的最小操作次数。

**说明/提示**

第一个测试用例在题目描述中已经说明。

第二个测试用例如下图所示：

在第三个测试用例中，网格已经满足条件。

**样例 #1**

### 输入

```
4
WWWWWWW
WWWWBBB
WWWWWBW
WWBBBBB
WWWBWWW
WWBBBWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
WBBBBBW
WBBBBBW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
BBBBBBB
BBBBBBB
WWWWWWW
BBBBBBB
BBBBBBB
BBBBBBB```

### 输出

```
1
2
0
5```

### 算法分类
**枚举**

### 题解分析与结论
题目要求通过最少的操作次数，使得网格中没有黑色单元格的四个对角线相邻单元格也是黑色。题解中普遍采用了枚举的思路，通过将网格分为两类（红色和蓝色），分别进行枚举和检查，最终得到最小操作次数。

### 所选高分题解
#### 题解作者：WaterSun (5星)
**关键亮点**：
1. 通过将网格分为红色和蓝色两类，分别进行枚举和检查，减少了问题的复杂度。
2. 使用DFS进行暴力枚举，确保找到最小操作次数。
3. 代码结构清晰，逻辑严谨，易于理解。

**核心代码**：
```cpp
bool dfs(int u,int res,int op){
    if (!res) return check(op);
    if (u == g[op].size()) return false;
    bool ok = false;
    point x = g[op][u];
    ok |= dfs(u + 1,res,op);
    arr[x.x][x.y] ^= 1;
    ok |= dfs(u + 1,res - 1,op);
    arr[x.x][x.y] ^= 1;
    return ok;
}
```
**核心思想**：通过DFS枚举每个可能的反转操作，检查是否满足条件。

#### 题解作者：Annihilation_y (4星)
**关键亮点**：
1. 通过染色将网格分为红色和绿色两类，分别进行枚举和检查。
2. 使用暴力枚举的方法，确保找到最小操作次数。
3. 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
bool Check1(){//对红色块的检查 
    bool flag=1;
    for(int i=2;i<=6;i++){
        if(flag==0) break;
        for(int j=2;j<=6;j++){
            if((i+j)%2==1) continue;
            if(flag==0) break;
            if(mp[i][j]&&mp[i-1][j-1]&&mp[i-1][j+1]&&mp[i+1][j-1]&&mp[i+1][j+1]) {
                flag=0;
            }
        }
    }
    if(flag) return 1;
    else return 0;
}
```
**核心思想**：通过暴力枚举红色和绿色块的反转操作，检查是否满足条件。

#### 题解作者：沉石鱼惊旋 (4星)
**关键亮点**：
1. 通过染色将网格分为红色和绿色两类，分别进行枚举和检查。
2. 使用暴力枚举的方法，确保找到最小操作次数。
3. 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
bool ok(int x, int y) {
    return c[x - 1][y - 1] == 'W' && c[x - 1][y + 1] == 'W' && c[x + 1][y - 1] == 'W' && c[x + 1][y + 1] == 'W';
}
```
**核心思想**：通过暴力枚举红色和绿色块的反转操作，检查是否满足条件。

### 最优关键思路或技巧
1. **网格分类**：将网格分为红色和蓝色两类，分别进行枚举和检查，减少了问题的复杂度。
2. **DFS枚举**：使用DFS进行暴力枚举，确保找到最小操作次数。
3. **剪枝优化**：在枚举过程中，通过剪枝减少不必要的计算，提高效率。

### 可拓展之处
1. **类似题目**：可以扩展到更大规模的网格，或者不同的颜色反转规则。
2. **算法优化**：可以考虑使用动态规划或其他优化算法，进一步提高效率。

### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)

---
处理用时：39.25秒