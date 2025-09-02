# 题目信息

# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 样例 #1

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

# AI分析结果

### 题目内容重写

**题目描述**

最近，Vladimir 在代数考试中又得了低分。为了避免将来再次发生这种不愉快的事情，他决定训练自己的算术技能。他在黑板上写了四个整数 $a$、$b$、$c$、$d$。在接下来的三分钟里，他每分钟从黑板上选取两个数（不一定相邻），并用它们的和或积替换它们。最终，他得到了一个数。不幸的是，由于记忆力太差，他忘记了那个数，但他记得四个原始数、操作的顺序以及他对结果非常小的惊讶。帮助 Vladimir 回忆起那个被遗忘的数：找出通过给定操作顺序从原始数中得到的最小可能数。

**样例 #1**

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

**样例 #2**

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

**样例 #3**

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

### 题解综合分析与结论

本题的核心是通过给定的操作顺序，从四个数中通过加法和乘法操作得到最小的结果。由于数据范围较小，大多数题解采用了暴力搜索的方法，通过枚举所有可能的操作顺序来找到最小值。部分题解还引入了回溯、全排列等技巧来优化搜索过程。

### 所选高星题解

#### 1. **作者：linyinuo2008 (赞：13)**  
**星级：★★★★★**  
**关键亮点：**  
- 使用深度优先搜索（DFS）进行暴力枚举，思路清晰。
- 通过 `vis` 数组记录操作状态，确保每次操作的正确性。
- 代码结构清晰，注释详细，便于理解。

**核心代码：**
```cpp
void dfs(int cur) {
    if (cur == 3) {
        for (int i = 0; i < 4; i++)
            if (!vis[i])
                ans = min(ans, a[i]);
        return;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j || vis[i] || vis[j]) continue;
            long long p = a[i];
            vis[j] = 1;
            if (ope[cur] == '+') a[i] += a[j];
            else if (ope[cur] == '*') a[i] *= a[j];
            dfs(cur + 1);
            vis[j] = 0;
            a[i] = p;
        }
    }
}
```

#### 2. **作者：翼德天尊 (赞：4)**  
**星级：★★★★☆**  
**关键亮点：**  
- 使用回溯法进行搜索，确保每次操作后能够还原现场。
- 通过 `vis` 数组标记已使用的数，避免重复操作。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
void dfs(int d) {
    if (d == 4) {
        int zc = 0;
        for (int i = 1; i <= 4; i++) {
            if (!vis[i]) zc = a[i];
        }
        ans = min(ans, zc);
        return;
    }
    for (int i = 1; i <= 4; i++) {
        if (!vis[i]) {
            for (int j = i + 1; j <= 4; j++) {
                if (!vis[j]) {
                    vis[i] = 1;
                    int s = a[j];
                    if (b[d] == '+') a[j] += a[i];
                    else if (b[d] == '*') a[j] *= a[i];
                    dfs(d + 1);
                    a[j] = s;
                    vis[i] = 0;
                }
            }
        }
    }
}
```

#### 3. **作者：Suuon_Kanderu (赞：2)**  
**星级：★★★★☆**  
**关键亮点：**  
- 使用 `vector` 动态管理操作数，简化了删除和回溯操作。
- 通过递归实现深度优先搜索，代码简洁明了。
- 适合初学者理解动态数据结构的使用。

**核心代码：**
```cpp
void dfs(vector<ll> a, int now) {
    if (now == 4) {
        ans = min(ans, a[0]);
        return;
    }
    vector<int> b = a;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            if (op[now] == '+') a[i] = a[i] + a[j];
            if (op[now] == '*') a[i] = a[i] * a[j];
            a.erase(a.begin() + j);
            dfs(a, now + 1);
            a = b;
        }
    }
}
```

### 最优关键思路与技巧

1. **暴力搜索与回溯**：通过枚举所有可能的操作顺序，结合回溯法确保每次操作后能够还原现场，避免重复计算。
2. **状态标记**：使用 `vis` 数组或 `vector` 动态管理操作数，确保每次操作的正确性。
3. **动态数据结构**：使用 `vector` 等动态数据结构简化删除和回溯操作，适合初学者理解。

### 可拓展之处

- **类似题目**：可以扩展到更多数的操作，或者引入更多操作符（如减法、除法）。
- **优化思路**：对于更大的数据范围，可以考虑剪枝优化或动态规划来减少计算量。

### 推荐题目

1. **P1003 铺地毯**：考察暴力枚举和状态标记。
2. **P1020 导弹拦截**：考察动态规划和贪心算法。
3. **P1044 栈**：考察回溯和递归的应用。

### 个人心得摘录

- **调试经历**：部分题解提到在调试过程中遇到回溯未完全还原的问题，导致结果错误，提醒了回溯时要注意所有状态的还原。
- **顿悟感想**：通过暴力搜索和回溯的结合，能够有效解决小规模数据的问题，且代码易于理解和实现。

---
处理用时：52.56秒