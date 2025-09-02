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

他写下 $n$ 个整数 $a_{1},a_{2},\cdots,a_{n}$ 。这些整数中的每一个都只能是 0 或 1。他只被允许进行一次操作：他选择两个索引 $i$ 和 $j$（$1\leq i\leq j\leq n$），并翻转所有位置在区间 $[i,j]$ 内的 $a_{k}$ 的值（即 $i\leq k\leq j$）。翻转 $x$ 的值意味着执行操作 $x = 1 - x$。

游戏的目标是在恰好进行一次操作后，得到尽可能多的 1。编写一个程序来解决 Iahub 的这个小游戏。

## 说明/提示
在第一个样例中，翻转从 2 到 5 的区间（$i = 2$，$j = 5$）。这次翻转改变了序列，它变成了：\[1 1 1 0 1\]。所以，它包含四个 1。没有办法让整个序列都等于 \[1 1 1 1 1\]。

在第二个样例中，只翻转第二个和第三个元素（$i = 2$，$j = 3$）将使所有数字都变成 1。

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
这些题解提供了多种解决该问题的思路，主要可分为暴力枚举和优化算法两类。

- **暴力枚举类**：通过枚举左右端点确定翻转区间，再计算翻转后 1 的个数，时间复杂度多为 $O(n^3)$ 或 $O(n^2)$ 。这种方法思路直接，但效率较低。
- **优化算法类**：包括前缀和优化、动态规划和转化为最大子段和问题，时间复杂度可优化到 $O(n)$ ，效率更高。

### 所选题解
- **若如初见（4星）**
    - **关键亮点**：将问题转化为求“贡献”序列的最大子段和，时间复杂度为 $O(n)$ ，空间复杂度为 $O(1)$ ，思路巧妙且代码简洁。
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
**核心实现思想**：假定 1 对答案的贡献为 -1，0 对答案的贡献为 1，对“贡献”序列求最大子段和，答案为最大子段和与原序列中 1 的个数之和。

- **小豆子范德萨（4星）**
    - **关键亮点**：将问题转化为求最大连续子序列和问题，使用动态规划求解，时间复杂度为 $O(n)$ ，思路清晰。
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
**核心实现思想**：引入数组 $b$ 记录每次反转的“收益”，通过动态规划求 $b$ 数组的最大连续子序列和，答案为原序列中 1 的个数加上最大连续子序列和。

### 最优关键思路或技巧
将问题转化为最大子段和问题是最优思路。通过重新定义元素的贡献（1 为 -1，0 为 1），可以将求翻转后最大 1 的个数问题转化为求最大子段和问题，时间复杂度可优化到 $O(n)$ 。

### 拓展思路
同类型题或类似算法套路：
- 区间修改问题：可以使用差分数组、线段树等数据结构进行优化。
- 最大子段和问题的变种：如环形数组的最大子段和、二维数组的最大子矩阵和等。

### 推荐洛谷题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)
- [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)

### 个人心得摘录与总结
- **封禁用户**：提到数据水，$\mathcal{O}(n^3)$ 能过不太合理，提醒我们在做题时要思考优化算法，不能仅满足于暴力解法。
- **若如初见**：给出了此题的加强版，鼓励我们挑战更高效率的算法，培养优化意识。 

---
处理用时：29.48秒