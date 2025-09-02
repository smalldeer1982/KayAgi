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
来自ABBYY的聪明海狸开始为孩子们开发一款新的教育游戏。游戏规则相当简单，如下所述。

游戏场地是一个由 $n$ 个非负整数 $a_{i}$ 组成的序列，编号从 $1$ 到 $n$ 。游戏的目标是使数字 $a_{1},a_{2},...,a_{k}$ （即序列的某个前缀）对于某个固定的 $k$ （$k < n$）等于零，并且这应该在尽可能少的移动次数内完成。

一次移动是选择一个整数 $i$（$1 \leq i \leq n$），使得 $a_{i} > 0$，以及一个整数 $t$（$t \geq 0$），使得 $i + 2^{t} \leq n$ 。在选择了 $i$ 和 $t$ 的值之后，$a_{i}$ 的值减 $1$，$a_{i + 2^{t}}$ 的值加 $1$ 。例如，设 $n = 4$ 且 $a = (1, 0, 1, 2)$，那么可以进行移动 $i = 3$，$t = 0$，得到 $a = (1, 0, 0, 3)$，或者进行移动 $i = 1$，$t = 1$，得到 $a = (0, 0, 2, 2)$（唯一可能的其他移动是 $i = 1$，$t = 0$ ）。

给定 $n$ 和初始序列 $a_{i}$ 。任务是计算对于每个可能的 $k$（$1 \leq k < n$），使原始序列的前 $k$ 个元素等于零所需的最少移动次数。

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
贪心

### 题解综合分析与结论
- **思路**：这几道题解都围绕如何将前面位置的数通过每次移动一个单位到后面位置，使得前 $k$ 个位置变为零的最少移动次数这一核心问题。
- **算法要点**：
    - **123456zmy和大宝和小宝**：利用贪心策略，每次尽可能将数往后移，通过位运算找到在规定范围内最大的 $2^t$ 。
    - **SXZM_1和Smg18**：使用二进制思想，通过递归计算二进制中1的个数来确定移动次数，从 $i + 1$ 循环到 $n$ 找最小值。
- **解决难点**：关键在于如何高效地确定每次移动的最佳位置以达到最少移动次数。123456zmy和大宝和小宝的方法通过贪心和位运算优化了移动策略；SXZM_1和Smg18的方法相对暴力，通过循环和递归计算最小移动次数。

123456zmy和大宝和小宝的题解在思路清晰度、代码可读性和优化程度上表现更好，采用贪心和位运算优化，使时间复杂度达到 $O(n\log n)$ ，而SXZM_1和Smg18的方法时间复杂度较高，代码相对复杂且可读性较差。

### 所选的题解
- **123456zmy题解**
  - **星级**：5星
  - **关键亮点**：利用贪心策略，一次尽可能往后移对全局最优，通过位运算优化，单次询问达到 $O(\log n)$ 复杂度，整体 $O(n\log n)$ 。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long ans,n,a_,a[100001];
int main()
{
    scanf("%llu",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%llu",&a_);
        a[i]+=a_;
        ans+=a[i];
        printf("%llu\n",ans);
        int i1=n-i;
        while(i1&i1-1)i1&=i1-1;
        a[i+i1]+=a[i];
    }
    return 0;
}
```
  - **核心实现思想**：读入数据，将当前值累加到 $a[i]$ 并累加到 $ans$ 作为当前答案输出，通过位运算找到能移动的最大距离 $i1$ ，将 $a[i]$ 累加到 $a[i + i1]$ 。
- **大宝和小宝题解**
  - **星级**：5星
  - **关键亮点**：同样利用贪心和位运算，思路清晰，代码简洁明了。
  - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

long long n,a,ans,A[100010];

int main () {
    cin >> n;
    for(int i = 1;i < n;i++) {
        cin >> a;
        A[i] += a;
        ans += A[i];
        cout << ans << "\n";
        int k = n-i;
        while(k&k-1) 
            k &= k-1;
        A[i+k] += A[i];
    }
    return 0;
}
```
  - **核心实现思想**：读入数据，将当前值累加到 $A[i]$ 并累加到 $ans$ 输出，通过位运算找到最大可移动距离 $k$ ，将 $A[i]$ 累加到 $A[i + k]$ 。

### 最优关键思路或技巧
贪心策略结合位运算。贪心策略保证每次移动尽可能往后，以达到全局最优；位运算高效地找到在规定范围内最大的 $2^t$ ，优化了移动位置的选择，从而降低时间复杂度。

### 可拓展思路
同类型题通常围绕在一定规则下的元素移动、状态改变等问题，类似算法套路是在这类有明确移动规则且求最优解的问题中，尝试使用贪心策略，并结合一些位运算等优化技巧来提高效率。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略解决合并问题，与本题贪心思路类似。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要运用贪心思想来确定游戏策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：同样是利用贪心算法解决排序和最优解问题。

### 个人心得
无。

---
处理用时：59.39秒