# 题目信息

# Sending a Sequence Over the Network

## 题目描述

The sequence $ a $ is sent over the network as follows:

1. sequence $ a $ is split into segments (each element of the sequence belongs to exactly one segment, each segment is a group of consecutive elements of sequence);
2. for each segment, its length is written next to it, either to the left of it or to the right of it;
3. the resulting sequence $ b $ is sent over the network.

For example, we needed to send the sequence $ a = [1, 2, 3, 1, 2, 3] $ . Suppose it was split into segments as follows: $ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $ . Then we could have the following sequences:

- $ b = [1, \color{red}{1}, 3, \color{blue}{2, 3, 1}, \color{green}{2, 3}, 2] $ ,
- $ b = [\color{red}{1}, 1, 3, \color{blue}{2, 3, 1}, 2, \color{green}{2, 3}] $ ,
- $ b = [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $ ,
- $ b = [\color{red}{1}, 1,\color{blue}{2, 3, 1}, 3, \color{green}{2, 3}, 2] $ .

If a different segmentation had been used, the sent sequence might have been different.

The sequence $ b $ is given. Could the sequence $ b $ be sent over the network? In other words, is there such a sequence $ a $ that converting $ a $ to send it over the network could result in a sequence $ b $ ?

## 说明/提示

In the first case, the sequence $ b $ could be obtained from the sequence $ a = [1, 2, 3, 1, 2, 3] $ with the following partition: $ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $ . The sequence $ b $ : $ [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $ .

In the second case, the sequence $ b $ could be obtained from the sequence $ a = [12, 7, 5] $ with the following partition: $ [\color{red}{12}] + [\color{green}{7, 5}] $ . The sequence $ b $ : $ [\color{red}{12}, 1, 2, \color{green}{7, 5}] $ .

In the third case, the sequence $ b $ could be obtained from the sequence $ a = [7, 8, 9, 10, 3] $ with the following partition: $ [\color{red}{7, 8, 9, 10, 3}] $ . The sequence $ b $ : $ [5, \color{red}{7, 8, 9, 10, 3}] $ .

In the fourth case, there is no sequence $ a $ such that changing $ a $ for transmission over the network could produce a sequence $ b $ .

## 样例 #1

### 输入

```
7
9
1 1 2 3 1 3 2 2 3
5
12 1 2 7 5
6
5 7 8 9 10 3
4
4 8 6 2
2
3 1
10
4 6 2 1 9 4 9 3 4 2
1
1```

### 输出

```
YES
YES
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容（中文重写）
# 通过网络发送序列

## 题目描述
序列 $a$ 通过网络发送的方式如下：
1. 序列 $a$ 被分割成若干段（序列中的每个元素恰好属于一段，每一段是序列中连续元素的组）；
2. 对于每一段，将其长度写在该段的旁边，可以写在左边或右边；
3. 得到的序列 $b$ 通过网络发送。

例如，我们需要发送序列 $a = [1, 2, 3, 1, 2, 3]$。假设它被分割成如下段：$ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $。那么我们可能得到以下序列：
- $ b = [1, \color{red}{1}, 3, \color{blue}{2, 3, 1}, \color{green}{2, 3}, 2] $，
- $ b = [\color{red}{1}, 1, 3, \color{blue}{2, 3, 1}, 2, \color{green}{2, 3}] $，
- $ b = [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $，
- $ b = [\color{red}{1}, 1,\color{blue}{2, 3, 1}, 3, \color{green}{2, 3}, 2] $。

如果使用不同的分割方式，发送的序列可能会不同。

给定序列 $b$。序列 $b$ 是否可以通过网络发送？换句话说，是否存在这样的序列 $a$，将 $a$ 进行转换以通过网络发送时可以得到序列 $b$？

## 说明/提示
在第一种情况下，序列 $b$ 可以从序列 $a = [1, 2, 3, 1, 2, 3]$ 通过以下分割得到：$ [\color{red}{1}] + [\color{blue}{2, 3, 1}] + [\color{green}{2, 3}] $。序列 $b$ 为：$ [\color{red}{1}, 1, \color{blue}{2, 3, 1}, 3, 2, \color{green}{2, 3}] $。

在第二种情况下，序列 $b$ 可以从序列 $a = [12, 7, 5]$ 通过以下分割得到：$ [\color{red}{12}] + [\color{green}{7, 5}] $。序列 $b$ 为：$ [\color{red}{12}, 1, 2, \color{green}{7, 5}] $。

在第三种情况下，序列 $b$ 可以从序列 $a = [7, 8, 9, 10, 3]$ 通过以下分割得到：$ [\color{red}{7, 8, 9, 10, 3}] $。序列 $b$ 为：$ [5, \color{red}{7, 8, 9, 10, 3}] $。

在第四种情况下，不存在这样的序列 $a$，使得对 $a$ 进行转换以通过网络发送时可以得到序列 $b$。

## 样例 #1
### 输入
```
7
9
1 1 2 3 1 3 2 2 3
5
12 1 2 7 5
6
5 7 8 9 10 3
4
4 8 6 2
2
3 1
10
4 6 2 1 9 4 9 3 4 2
1
1
```
### 输出
```
YES
YES
YES
NO
YES
YES
NO
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕判断给定序列 $b$ 是否能由某个序列 $a$ 按规则转换得到展开。大部分题解采用动态规划的方法，通过定义状态数组来记录前 $i$ 个元素是否合法，根据长度在段的左边或右边两种情况进行状态转移；也有使用搜索（DFS、BFS）和图论的做法。

难点在于如何准确地进行状态转移，考虑到长度在不同位置的情况，避免重复计算和越界问题。

### 所选题解
- **作者：RuntimeErr（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过状态转移方程递推得出结果。
    - **核心代码**：
```cpp
const int N=2e5+10;
int n,a[N];
bool dp[N];
void solve(){
    read(n);
    for(int i=1;i<=n;++i)read(a[i]);
    memset(dp,0,sizeof dp);dp[0]=1;
    for(int i=1;i<=n;++i){
        if(i+a[i]<=n)dp[i+a[i]]|=dp[i-1];
        if(i-a[i]-1>=0)dp[i]|=dp[i-a[i]-1];
    }
    if(dp[n])printf("YES\n");
    else printf("NO\n");
}
```
**核心实现思想**：定义 $dp_i$ 表示 $[1,i]$ 是否合法，若 $a_i$ 表示区间长度且在区间左边，则 $[1,i+a_i]$ 合法的充分条件是 $[1,i - 1]$ 合法；若 $a_i$ 在区间右边，则 $[1,i]$ 合法的充分条件是 $[1,i - a_i - 1]$ 合法。

- **作者：lenlen（4星）**
    - **关键亮点**：采用搜索的方法，通过多次优化避免了超时问题，展示了搜索算法的优化过程。
    - **核心代码**：
```cpp
const int N=2e5+32;
int n,T,ans;
int a[N];
bool vis[N];
vector<int> t[N];
void dfs(int x)
{
    vis[x]=false;
    if(ans) return ;
    if(x==n+1)
    {
        ans=1;
        return ;
    }
    if(x+a[x]+1<=n+1&&vis[x+a[x]+1]) dfs(x+a[x]+1);
    int l=t[x].size();
    for(int i=0;i<l;i++) if(vis[t[x][i]+1]) dfs(t[x][i]+1);
}
```
**核心实现思想**：从点 $1$ 开始搜索，对于每个点有两种情况：一是该点的值为段长，继续搜索 $x + a[x] + 1$；二是遍历预处理的可能的段尾，继续搜索。同时使用 $vis$ 数组记录已搜索的点，避免重复搜索。

- **作者：WaterSun（4星）**
    - **关键亮点**：思路清晰，详细解释了状态转移方程的推导，使用或运算简化代码。
    - **核心代码**：
```cpp
const int N = 2e5 + 10;
int T,n;
int arr[N];
bool dp[N];
int main(){
    T = read();
    while (T--){
        memset(dp,false,sizeof(dp));
        dp[0] = true;
        n = read();
        for (int i = 1;i <= n;i++) arr[i] = read();
        for (int i = 0;i <= n;i++){
            if (i - arr[i] - 1 >= 0) dp[i] |= dp[i - arr[i] - 1];
            if (i + 1 + arr[i + 1] <= n) dp[i + 1 + arr[i + 1]] |= dp[i];
        }
        if (dp[n]) puts("YES");
        else puts("NO");
    }
    return 0;
}
```
**核心实现思想**：定义 $dp_i$ 表示前 $i$ 位能否被构造出，根据第 $i$ 位作为末尾或长度的情况进行状态转移，使用或运算更新状态。

### 最优关键思路或技巧
- **动态规划**：定义合适的状态数组，根据长度在段的左右两边两种情况准确地进行状态转移。
- **搜索优化**：使用预处理和标记数组避免重复搜索，降低时间复杂度。

### 拓展思路
同类型题可能会有更复杂的分割规则或条件，类似的算法套路可以是定义状态数组记录中间结果，根据不同情况进行状态转移，同时注意边界条件和避免重复计算。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划的基本应用。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的线性动态规划问题，通过状态转移求解最优路径。
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察动态规划在连续子段问题中的应用。

### 个人心得摘录与总结
- **作者：lenlen**：自己没想到用 dp 做，采用搜索方法，通过多次优化避免了超时问题，展示了搜索算法的优化过程，说明在遇到问题时可以尝试不同的算法，并不断优化。 

---
处理用时：62.08秒