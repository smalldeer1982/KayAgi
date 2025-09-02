# 题目信息

# Educational Game

## 题目描述

The Smart Beaver from ABBYY began to develop a new educational game for children. The rules of the game are fairly simple and are described below.

The playing field is a sequence of $ n $ non-negative integers $ a_{i} $ numbered from $ 1 $ to $ n $ . The goal of the game is to make numbers $ a_{1},a_{2},...,a_{k} $ (i.e. some prefix of the sequence) equal to zero for some fixed $ k $ $ (k<n) $ , and this should be done in the smallest possible number of moves.

One move is choosing an integer $ i $ ( $ 1<=i<=n $ ) such that $ a_{i}>0 $ and an integer $ t $ $ (t>=0) $ such that $ i+2^{t}<=n $ . After the values of $ i $ and $ t $ have been selected, the value of $ a_{i} $ is decreased by $ 1 $ , and the value of $ a_{i+2^{t}} $ is increased by $ 1 $ . For example, let $ n=4 $ and $ a=(1,0,1,2) $ , then it is possible to make move $ i=3 $ , $ t=0 $ and get $ a=(1,0,0,3) $ or to make move $ i=1 $ , $ t=1 $ and get $ a=(0,0,2,2) $ (the only possible other move is $ i=1 $ , $ t=0 $ ).

You are given $ n $ and the initial sequence $ a_{i} $ . The task is to calculate the minimum number of moves needed to make the first $ k $ elements of the original sequence equal to zero for each possible $ k $ $ (1<=k<n) $ .

## 样例 #1

### 输入

```
4
1 0 1 2
```

### 输出

```
1
1
3
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8
```

### 输出

```
1
3
6
10
16
24
40
```

# AI分析结果

### 题目内容
# 教育游戏

## 题目描述
来自 ABBYY 的聪明海狸开始为孩子们开发一款新的教育游戏。游戏规则相当简单，如下所述。

游戏场地是一个由 $n$ 个非负整数 $a_{i}$ 组成的序列，编号从 $1$ 到 $n$ 。游戏的目标是使数字 $a_{1},a_{2},...,a_{k}$ （即序列的某个前缀）对于某个固定的 $k$ （$k < n$）等于零，并且应该以尽可能少的移动次数完成。

一次移动是选择一个整数 $i$ （$1 \leq i \leq n$）使得 $a_{i} > 0$ ，以及一个整数 $t$ （$t \geq 0$）使得 $i + 2^{t} \leq n$ 。在选择了 $i$ 和 $t$ 的值之后，$a_{i}$ 的值减 $1$ ，$a_{i + 2^{t}}$ 的值加 $1$ 。例如，设 $n = 4$ 且 $a = (1, 0, 1, 2)$ ，那么可以进行移动 $i = 3$ ，$t = 0$ ，得到 $a = (1, 0, 0, 3)$ ，或者进行移动 $i = 1$ ，$t = 1$ ，得到 $a = (0, 0, 2, 2)$ （唯一可能的其他移动是 $i = 1$ ，$t = 0$ ）。

给定 $n$ 和初始序列 $a_{i}$ 。任务是计算对于每个可能的 $k$ （$1 \leq k < n$），使原始序列的前 $k$ 个元素等于零所需的最小移动次数。

## 样例 #1
### 输入
```
4
1 0 1 2
```
### 输出
```
1
1
3
```

## 样例 #2
### 输入
```
8
1 2 3 4 5 6 7 8
```
### 输出
```
1
3
6
10
16
24
40
```

### 算法分类
数学

### 题解综合分析与结论
两题解思路相近，均利用二进制思想，通过计算将前 $k$ 个位置变为 $0$ 所需移动次数。
- **思路**：每次操作是将一个数中的一个 $1$ 往后移动 $2^t$ 个位置，题解都利用这一规则，计算使前 $k$ 个位置为 $0$ 的最小操作次数。
- **算法要点**：都通过计算数字间距离在二进制下 $1$ 的个数来衡量移动代价。例如，`check` 函数计算一个数在二进制下 $1$ 的个数，用来表示移动的代价。
- **解决难点**：难点在于理解操作本质并找到合适方式计算移动代价。两题解均通过分析操作与二进制关系解决，即通过 `check` 函数计算二进制下 $1$ 的个数来表示从一个位置移动到另一个位置的代价。

### 题解
#### 作者：123456zmy (星级：4 星)
- **关键亮点**：预处理代价数组，将查询复杂度优化到 $O(1)$ ，整体时间复杂度为 $O(n^2\log n)$ ，提高了效率。
- **重点代码**：
```cpp
int bitn(int k){return k?bitn(k&k-1)+1:0;}// 计算二进制下1的个数
signed main()
{
    scanf("%llu",&n);
    for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)ans[i][j]=bitn(j-i); // 预处理移动代价
    for(int i=1;i<n;i++)for(int j=n;j>1;j--)ans[i][j-1]=min(ans[i][j],ans[i][j-1]);// 优化查询
    for(int i=1;i<n;i++)
    {
        ansn=0;
        scanf("%llu",&a[i]);
        for(int j=1;j<=i;j++)ansn+=ans[j][i+1]*a[j];// 计算答案
        printf("%llu\n",ansn);
    }
    return 0;
}
```
核心实现思想：先通过 `bitn` 函数计算移动代价并预处理到 `ans` 数组，再通过双重循环优化查询，最后根据输入计算每个 $k$ 对应的最小移动次数。

#### 作者：Smg18 (星级：3 星)
- **关键亮点**：采用暴力思路，利用二进制思想，代码逻辑简单直接。
- **重点代码**：
```cpp
int check(int k){return k?check(k&k-1)+1:0;}// 计算二进制下1的个数
int main(){
    cin>>n;
    for(int i = 1;i<n;i++){
        ans=0;
        cin>>arr[i];
        for(int j = 1;j<=i;j++){
            int m = INT_MAX;
            for(int k = i+1;k<=n;k++){
                m=min(m,check(k-j));// 找最小移动代价
            }
            ans+=m*arr[j];// 计算答案
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：通过三重循环，对每个 $i$ ，遍历前 $i$ 个数，对每个数找其移动到 $i$ 之后位置的最小代价，累加得到使前 $i$ 个位置为 $0$ 的最小移动次数。

### 最优关键思路或技巧
利用二进制思想，通过计算数字在二进制下 $1$ 的个数来衡量移动代价。123456zmy 的题解通过预处理代价数组优化查询，是较好的优化方式。

### 可拓展之处
同类型题可考察对操作规则的理解与数学建模，类似算法套路是分析操作与某种数学表示（如本题二进制）的关系，通过数学方法计算代价。

### 洛谷推荐题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)：涉及数字规律与递推，和本题分析数字操作规律类似。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学方法解决连续自然数和问题，需对问题进行数学建模，和本题思路有相似处。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过分析规律计算金币数量，与本题分析操作规律计算移动次数类似。 

---
处理用时：41.43秒