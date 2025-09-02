# 题目信息

# Flipping Game

## 题目描述

Iahub got bored, so he invented a game to be played on paper.

He writes $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices $ i $ and $ j $ ( $ 1<=i<=j<=n $ ) and flips all values $ a_{k} $ for which their positions are in range $ [i,j] $ (that is $ i<=k<=j $ ). Flip the value of $ x $ means to apply operation $ x=1 $ - $ x $ .

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

## 说明/提示

In the first case, flip the segment from 2 to 5 $ (i=2,j=5) $ . That flip changes the sequence, it becomes: \[1 1 1 0 1\]. So, it contains four ones. There is no way to make the whole sequence equal to \[1 1 1 1 1\].

In the second case, flipping only the second and the third element $ (i=2,j=3) $ will turn all numbers into 1.

## 样例 #1

### 输入

```
5
1 0 0 1 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
4
```

# AI分析结果

### 题目翻译
# 翻转游戏

## 题目描述
Iahub 觉得无聊，于是发明了一个可以在纸上玩的游戏。

他写下 $ n $ 个整数 $ a_{1},a_{2},...,a_{n} $ 。这些整数中的每一个要么是 0，要么是 1。他只被允许进行一次操作：他选择两个索引 $ i $ 和 $ j $（$ 1\leq i\leq j\leq n $），并翻转所有位置在区间 $ [i,j] $ 内的 $ a_{k} $ 的值（即 $ i\leq k\leq j $）。翻转 $ x $ 的值意味着执行操作 $ x = 1 - x $。

游戏的目标是在恰好进行一次操作后，获得尽可能多的 1。编写一个程序来解决 Iahub 的这个小游戏。

## 说明/提示
在第一个样例中，翻转从第 2 到第 5 个元素的区间（$ i = 2 $，$ j = 5 $）。这次翻转改变了序列，使其变为：\[1 1 1 0 1\]。所以，序列中包含四个 1。没有办法使整个序列变为 \[1 1 1 1 1\]。

在第二个样例中，仅翻转第二个和第三个元素（$ i = 2 $，$ j = 3 $）将使所有数字变为 1。

## 样例 #1
### 输入
```
5
1 0 0 1 0
```
### 输出
```
4
```

## 样例 #2
### 输入
```
4
1 0 0 1
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心都是解决在给定 01 序列中，通过一次区间翻转操作得到最多 1 的问题。各题解思路和复杂度有所不同：
- **暴力枚举类**：枚举左右端点，遍历区间统计翻转后 1 的个数，复杂度为 $O(n^3)$ 或 $O(n^2)$。
- **前缀和优化类**：利用前缀和快速计算区间内 1 的个数，减少统计时间，复杂度为 $O(n^2)$。
- **动态规划类**：将问题转化为最大连续子序列和问题，复杂度为 $O(n)$。

### 高评分题解
1. **作者：若如初见（5星）**
    - **关键亮点**：思路巧妙，将问题转化为最大子段和问题，时间复杂度为 $O(n)$，空间复杂度为 $O(1)$，代码简洁高效。
    - **核心代码**：
```cpp
#include <cstdio>
int n,a,now,ans,cnt;
inline int max(int a,int b){
    return a>b?a:b;
} 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a){
            cnt++; 
            if(now) now--;
        } else now++;
        ans=max(ans,now); 
    }
    printf("%d",cnt+ans);
    return 0;
}
```
    - **核心思想**：将 1 对答案的贡献设为 -1，0 对答案的贡献设为 1，对“贡献”序列求最大子段和，答案为最大子段和与原序列中 1 的个数之和。
2. **作者：小豆子范德萨（4星）**
    - **关键亮点**：将问题转化为最大连续子序列和问题，使用动态规划求解，复杂度为 $O(n)$，思路清晰，代码规范。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
int a[maxn];		
int b[maxn];		
int dp[maxn];		

int main() {
    int n;cin>>n;
    int cnt = 0;	
    for(int i = 0;i < n;i++) {
        cin>>a[i];
        if(a[i] == 1) {
            b[i] = -1;
            cnt++;			
        }
        else b[i] = 1;
    }
    dp[0] = b[0];		
    for(int i = 1;i < n;i++) {
        dp[i] = max(b[i],dp[i-1]+b[i]);
    }
    int k = 0;		
    for(int i = 1;i < n;i++) {
        if(dp[i] > dp[k]) {
            k = i;
        }
    }
    cout<<cnt+dp[k];		
    return 0;
}
```
    - **核心思想**：引入数组 $b$ 记录每次反转的“收益”，求 $b$ 序列的最大连续子序列和，答案为原序列中 1 的个数加上最大连续子序列和。

### 最优关键思路或技巧
将原问题转化为最大连续子序列和问题，通过重新定义元素对答案的贡献，将问题简化，从而将时间复杂度从 $O(n^3)$ 或 $O(n^2)$ 优化到 $O(n)$。

### 拓展思路
同类型题可考虑其他区间操作问题，如区间修改、区间查询等。类似算法套路有前缀和、差分、动态规划等，可用于解决各种区间统计和优化问题。

### 洛谷相似题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)
3. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)

### 个人心得摘录与总结
- **作者：若如初见**：发现了 $O(n)$ 的做法，指出可以将问题转化为最大子段和问题，并给出了加强版题目，体现了对问题的深入思考和拓展。
- **作者：小豆子范德萨**：提到要将问题进行转化，判断翻转是亏是赚，将问题转化为最大连续子序列和问题，强调了问题转化的重要性。 

---
处理用时：33.48秒