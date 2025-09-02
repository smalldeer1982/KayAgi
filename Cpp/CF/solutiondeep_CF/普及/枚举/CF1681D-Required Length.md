# 题目信息

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
4```

## 样例 #3

### 输入

```
13 42```

### 输出

```
12```

# AI分析结果

### 题目中文重写
## 所需长度

### 题目描述
给定两个整数 $n$ 和 $x$，你可以对整数 $x$ 进行若干次操作。

每次操作如下：选择 $x$ 的十进制表示中至少出现一次的任意数字 $y$，然后用 $x \cdot y$ 替换 $x$。

你希望使 $x$ 的十进制表示长度（无前导零）等于 $n$。实现这一目标所需的最少操作次数是多少？

### 说明/提示
在第二个样例中，以下操作序列可以达到目标：
1. 将 $x$ 乘以 $2$，此时 $x = 2 \cdot 2 = 4$；
2. 将 $x$ 乘以 $4$，此时 $x = 4 \cdot 4 = 16$；
3. 将 $x$ 乘以 $6$，此时 $x = 16 \cdot 6 = 96$；
4. 将 $x$ 乘以 $9$，此时 $x = 96 \cdot 9 = 864$。

### 样例 #1
#### 输入
```
2 1
```
#### 输出
```
-1
```

### 样例 #2
#### 输入
```
3 2
```
#### 输出
```
4
```

### 样例 #3
#### 输入
```
13 42
```
#### 输出
```
12
```

### 综合分析与结论
这些题解主要围绕如何通过最少操作次数使 $x$ 的十进制长度达到 $n$ 展开，使用了多种算法，包括深搜、广搜、IDA*、动态规划等，并结合了剪枝和记忆化等优化策略。

|作者|思路|算法要点|解决难点|评分|
|----|----|----|----|----|
|litachloveyou|深搜结合贪心和最优情况剪枝|从 9 开始尝试乘法，若当前次数超过答案或最优情况不如当前答案则返回|避免深搜超时|4星|
|dbxxx|广搜结合记忆化判重|过滤 0 和 1，用 set 记录已访问状态|状态数过多和值域大的问题|4星|
|qwq___qaq|IDA*算法|考虑迭代次数上限和估价函数|避免单纯 DFS 超时|3星|
|happy_dengziyue|广搜搭配 map 判重|过滤小于 2 的数字，避免重复乘法|时间复杂度优化|3星|
|CWzwz|动态规划|压缩状态，刷表转移|状态数过多问题|3星|
|Light_az|剪枝深搜|过滤 0 和 1，根据操作次数和最优解剪枝|避免深搜超时|3星|
|Cocoly1990|BFS 或 DFS 结合记忆化|根据当前操作次数和答案剪枝|减少重复状态|3星|
|YCSluogu|广搜结合剪枝|过滤位数大于 n 的状态，用 set 或 map 判重|判断位数达标和判重|3星|
|SnowTrace|广搜|枚举数位相乘，用 map 判重|数据范围大的问题|3星|
|Ice_lift|暴搜结合剪枝|可行性和最优化剪枝|避免无效搜索|3星|
|npqenqpve|建边跑最短路|若点为 n 位数则停止建边|减少不必要的建边|2星|

### 所选题解
- **litachloveyou（4星）**
    - 关键亮点：贪心和最优情况剪枝，有效减少深搜的搜索空间。
    - 核心代码：
```cpp
void bfs(ll x,ll c)
{
    if(n+c-leg(x)>=ans)return; // 最优情况剪枝
    if(leg(x)==n)
    {
        ans=c; // 更新答案
        que=true;
        return;
    }
    vector<int>a(10);
    ll k=x;
    while(k)
    {
        a[k%10]++;
        k=k/10;
    }
    for(int i=9;i>1;i--) // 从9开始
    {
        if(a[i]>=1)
        {
            bfs(x*i,c+1);
        }
    }
}
```
- **dbxxx（4星）**
    - 关键亮点：利用数的分解性质减少状态数，用 set 判重，代码简洁。
    - 核心代码：
```cpp
std::queue <pii> q;
q.emplace(x, 0);
while (!q.empty()) {
    int x = q.front().first, step = q.front().second;
    q.pop();
    if (x >= l) {
        printf("%llu\n", step);
        return 0;
    }
    std::memset(hav, false, sizeof(hav));
    int t = x;
    while (t) {
        hav[t % 10] = true;
        t /= 10;
    }
    for (int i = 2; i <= 9; ++i) if (hav[i]) {
        if (vis.count(x * i))
            continue;
        q.emplace(x * i, step + 1);
        vis.insert(x * i);
    }
}
```

### 最优关键思路或技巧
- 过滤 0 和 1：因为乘以 0 和 1 不会改变数的位数，所以在操作中直接忽略。
- 剪枝优化：通过最优情况剪枝、可行性剪枝和最优化剪枝减少不必要的搜索。
- 记忆化判重：使用 set 或 map 记录已访问的状态，避免重复搜索。
- 状态压缩：将操作过程中的数表示为 $x\cdot2^a\cdot3^b\cdot5^c\cdot7^d$ 的形式，减少状态数。

### 可拓展之处
同类型题可能涉及更多的操作规则或更复杂的状态转移，类似算法套路可用于解决其他搜索和动态规划问题，如迷宫问题、背包问题等。

### 推荐题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及状态转移和搜索，可使用 BFS 或 DFS 解决。
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：经典的 BFS 问题，通过广度优先搜索找到最短路径。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：简单的动态规划问题，可练习状态转移方程的推导。

### 个人心得摘录与总结
- **litachloveyou**：一开始想用深搜，但未优化的深搜超时，尝试贪心也超时，最终采用贪心和最优情况剪枝解决问题。总结：在搜索问题中，合理的剪枝策略可以有效减少搜索空间，避免超时。
- **Light_az**：一开始用贪心算法提交零分，后来改用深搜并结合剪枝方案解决问题。总结：贪心算法不一定适用于所有问题，当贪心不成立时，可尝试搜索算法并结合剪枝优化。 

---
处理用时：36.26秒