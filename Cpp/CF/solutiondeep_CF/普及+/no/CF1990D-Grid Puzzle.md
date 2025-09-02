# 题目信息

# Grid Puzzle

## 题目描述

You are given an array $ a $ of size $ n $ .

There is an $ n \times n $ grid. In the $ i $ -th row, the first $ a_i $ cells are black and the other cells are white. In other words, note $ (i,j) $ as the cell in the $ i $ -th row and $ j $ -th column, cells $ (i,1), (i,2), \ldots, (i,a_i) $ are black, and cells $ (i,a_i+1), \ldots, (i,n) $ are white.

You can do the following operations any number of times in any order:

- Dye a $ 2 \times 2 $ subgrid white;
- Dye a whole row white. Note you can not dye a whole column white.

Find the minimum number of operations to dye all cells white.

## 说明/提示

In the first test case, you don't need to do any operation.

In the second test case, you can do:

- Dye $ (1,1), (1,2), (2,1) $ , and $ (2,2) $ white;
- Dye $ (2,3), (2,4), (3,3) $ , and $ (3,4) $ white;
- Dye $ (3,1), (3,2), (4,1) $ , and $ (4,2) $ white.

It can be proven $ 3 $ is the minimum number of operations.

In the third test case, you can do:

- Dye the first row white;
- Dye $ (2,1), (2,2), (3,1) $ , and $ (3,2) $ white.

It can be proven $ 2 $ is the minimum number of operations.

## 样例 #1

### 输入

```
10
1
0
4
2 4 4 2
4
3 2 1 0
3
0 3 0
3
0 1 3
3
3 1 0
4
3 1 0 3
4
0 2 2 2
6
1 3 4 2 0 4
8
2 2 5 2 3 4 2 4```

### 输出

```
0
3
2
1
2
2
3
2
4
6```

# AI分析结果

### 题目内容重写（中文）

#### 网格拼图

**题目描述**

给定一个大小为 $n$ 的数组 $a$。

有一个 $n \times n$ 的网格。在第 $i$ 行中，前 $a_i$ 个格子是黑色的，其他格子是白色的。换句话说，记 $(i,j)$ 为第 $i$ 行第 $j$ 列的格子，格子 $(i,1), (i,2), \ldots, (i,a_i)$ 是黑色的，格子 $(i,a_i+1), \ldots, (i,n)$ 是白色的。

你可以进行以下操作任意次数，顺序不限：

- 将一个 $2 \times 2$ 的子网格染成白色；
- 将一整行染成白色。注意你不能将一整列染成白色。

求将所有格子染成白色的最小操作次数。

**说明/提示**

在第一个测试用例中，你不需要进行任何操作。

在第二个测试用例中，你可以进行以下操作：

- 将 $(1,1), (1,2), (2,1)$ 和 $(2,2)$ 染成白色；
- 将 $(2,3), (2,4), (3,3)$ 和 $(3,4)$ 染成白色；
- 将 $(3,1), (3,2), (4,1)$ 和 $(4,2)$ 染成白色。

可以证明 $3$ 是最小的操作次数。

在第三个测试用例中，你可以进行以下操作：

- 将第一行染成白色；
- 将 $(2,1), (2,2), (3,1)$ 和 $(3,2)$ 染成白色。

可以证明 $2$ 是最小的操作次数。

### 算法分类
动态规划

### 题解分析与结论

该题的核心在于如何通过最少的操作将所有黑色格子染成白色。题解中主要采用了动态规划的思路，通过记录每行的状态来优化操作次数。以下是各题解的要点与难点对比：

1. **Muse_Dash**：通过从上到下逐行处理，记录每行未涂的格子数量，并根据情况选择使用 $2 \times 2$ 操作或整行操作。难点在于如何判断 $2 \times 2$ 操作对下一行的影响。
2. **aulive**：将问题简化为两种情况：$a_i \leq 2$ 和 $a_i \leq 4$，并分别处理。难点在于如何通过标记来记录前一行的操作对当前行的影响。
3. **SunsetLake**：通过观察 $a_i > 4$ 时只能使用整行操作，进一步优化了动态规划的状态转移。难点在于如何通过布尔变量记录前一行的操作对当前行的影响。

### 精选题解

#### 题解1：SunsetLake（评分：4星）

**关键亮点**：
- 通过观察 $a_i > 4$ 时只能使用整行操作，简化了问题。
- 使用布尔变量 $l$ 和 $r$ 记录前一行的操作对当前行的影响，优化了状态转移。

**核心代码**：
```cpp
int ans = 0;
bool l = 0, r = 0;
for(int i = 1; i <= n; ++i){
    if(a[i] == 0 || (l && a[i] <= 2)){
        l = r = 0;
        continue;
    }
    if(a[i] > 4){
        l = r = 0;
        ++ans;
        continue; 
    }
    if(l || r){
        ++ans;
        swap(l, r);
        continue;
    }
    if(a[i] > 2){
        ++ans;
        l = r = 0;
        continue;
    }
    ++ans;
    l = 1; r = 0;
}
cout << ans << endl;
```

#### 题解2：Muse_Dash（评分：4星）

**关键亮点**：
- 通过逐行处理，记录每行未涂的格子数量，并根据情况选择操作。
- 通过标记 $tmp[i]$ 记录前一行的操作对当前行的影响。

**核心代码**：
```cpp
int sum = 0;
for (int i = 1; i <= n; i++){
    if (a[i] <= 0) a[i] = 0;
    else if (a[i] <= 2){
        a[i] = 0;
        if (!tmp[i-1]) a[i+1] -= 2, tmp[i] = 1;
        else if (tmp[i-1] && a[i+1] == 3) a[i+1] = 2;
        else if (tmp[i-1] && a[i+1] > 3) a[i+1] -= 2;
        sum++;
    }
    else a[i] = 0, sum++;
}
cout << sum << '\n';
```

#### 题解3：aulive（评分：4星）

**关键亮点**：
- 将问题简化为两种情况：$a_i \leq 2$ 和 $a_i \leq 4$，并分别处理。
- 通过标记 $tag1[i]$ 和 $tag2[i]$ 记录前一行的操作对当前行的影响。

**核心代码**：
```cpp
if(a[i] <= 2){
    tag1[i] = tag1[i+1] = 1;
}else if(a[i] <= 4){
    if(tag2[i]) tag1[i] = tag1[i+1] = 1;
    else if(tag1[i]) tag2[i] = tag2[i+1] = 1;
}
ans++;
```

### 最优关键思路与技巧

1. **动态规划状态转移**：通过记录前一行的操作对当前行的影响，优化操作次数。
2. **贪心策略**：在 $a_i > 4$ 时直接使用整行操作，避免不必要的 $2 \times 2$ 操作。
3. **标记记录**：通过布尔变量或数组记录前一行的操作，简化状态转移。

### 拓展思路

类似的问题可以通过动态规划结合贪心策略来解决，尤其是在需要最小化操作次数的情况下。可以通过记录前一状态对当前状态的影响来优化转移。

### 推荐题目

1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得总结

在调试过程中，发现通过标记记录前一行的操作对当前行的影响可以大大简化状态转移。此外，贪心策略在 $a_i > 4$ 时的应用也显著减少了操作次数。

---
处理用时：58.89秒