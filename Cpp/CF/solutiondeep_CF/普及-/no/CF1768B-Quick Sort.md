# 题目信息

# Quick Sort

## 题目描述

You are given a permutation $ ^\dagger $ $ p $ of length $ n $ and a positive integer $ k \le n $ .

In one operation, you:

- Choose $ k $ distinct elements $ p_{i_1}, p_{i_2}, \ldots, p_{i_k} $ .
- Remove them and then add them sorted in increasing order to the end of the permutation.

For example, if $ p = [2,5,1,3,4] $ and $ k = 2 $ and you choose $ 5 $ and $ 3 $ as the elements for the operation, then $ [2, \color{red}{5}, 1, \color{red}{3}, 4] \rightarrow [2, 1, 4, \color{red}{3},\color{red}{5}] $ .

Find the minimum number of operations needed to sort the permutation in increasing order. It can be proven that it is always possible to do so.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation is already sorted.

In the second test case, you can choose element $ 3 $ , and the permutation will become sorted as follows: $ [\color{red}{3}, 1, 2] \rightarrow [1, 2, \color{red}{3}] $ .

In the third test case, you can choose elements $ 3 $ and $ 4 $ , and the permutation will become sorted as follows: $ [1, \color{red}{3}, 2, \color{red}{4}] \rightarrow [1, 2, \color{red}{3},\color{red}{4}] $ .

In the fourth test case, it can be shown that it is impossible to sort the permutation in $ 1 $ operation. However, if you choose elements $ 2 $ and $ 1 $ in the first operation, and choose elements $ 3 $ and $ 4 $ in the second operation, the permutation will become sorted as follows: $ [\color{red}{2}, 3, \color{red}{1}, 4] \rightarrow [\color{blue}{3}, \color{blue}{4}, \color{red}{1}, \color{red}{2}] \rightarrow [1,2, \color{blue}{3}, \color{blue}{4}] $ .

## 样例 #1

### 输入

```
4
3 2
1 2 3
3 1
3 1 2
4 2
1 3 2 4
4 2
2 3 1 4```

### 输出

```
0
1
1
2```

# AI分析结果

### 题目内容
# 快速排序

## 题目描述
给定一个长度为 $n$ 的排列 $^\dagger$ $p$ 以及一个正整数 $k \leq n$ 。

在一次操作中，你需要：
- 选择 $k$ 个不同的元素 $p_{i_1}, p_{i_2}, \ldots, p_{i_k}$ 。
- 将它们移除，然后按升序添加到排列的末尾。

例如，如果 $p = [2,5,1,3,4]$ 且 $k = 2$ ，你选择 $5$ 和 $3$ 作为操作元素，那么 $[2, \color{red}{5}, 1, \color{red}{3}, 4] \rightarrow [2, 1, 4, \color{red}{3},\color{red}{5}]$ 。

求将该排列按升序排序所需的最少操作次数。可以证明这总是可行的。

$^\dagger$ 长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（数组中 $2$ 出现两次），$[1,3,4]$ 也不是排列（$n = 3$ 但数组中有 $4$ ）。

## 说明/提示
在第一个测试用例中，排列已经是有序的。

在第二个测试用例中，你可以选择元素 $3$ ，排列将按如下方式变为有序：$[\color{red}{3}, 1, 2] \rightarrow [1, 2, \color{red}{3}]$ 。

在第三个测试用例中，你可以选择元素 $3$ 和 $4$ ，排列将按如下方式变为有序：$[1, \color{red}{3}, 2, \color{red}{4}] \rightarrow [1, 2, \color{red}{3},\color{red}{4}]$ 。

在第四个测试用例中，可以证明一次操作无法将排列排序。然而，如果你在第一次操作中选择元素 $2$ 和 $1$ ，在第二次操作中选择元素 $3$ 和 $4$ ，排列将按如下方式变为有序：$[\color{red}{2}, 3, \color{red}{1}, 4] \rightarrow [\color{blue}{3}, \color{blue}{4}, \color{red}{1}, \color{red}{2}] \rightarrow [1,2, \color{blue}{3}, \color{blue}{4}]$ 。

## 样例 #1
### 输入
```
4
3 2
1 2 3
3 1
3 1 2
4 2
1 3 2 4
4 2
2 3 1 4
```
### 输出
```
0
1
1
2
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路一致，均基于贪心策略。要点在于找出从 $1$ 开始的最长连续递增子序列，该子序列中的元素无需操作，其余元素则需通过每次最多选择 $k$ 个元素移至末尾并排序的操作来完成整个序列的排序。操作次数为需要操作的元素个数除以 $k$ 并向上取整。各题解在代码实现上略有差异，如变量命名、输入输出方式以及具体计算操作次数的写法等，但整体思路和算法本质相同。

### 所选的题解
- **作者：0zhouyq (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，通过统计从 $1$ 开始的连续递增子序列长度，直接计算出需要操作的元素个数并得出操作次数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll t;
    scanf("%lld",&t);
    while(t--){
        ll n,k,x;
        scanf("%lld %lld",&n,&k);
        ll now=0;
        for(ll i=1;i<=n;i++){
            scanf("%lld",&x);
            if(x==now+1) now++;
        }
        n-=now;
        if(n%k==0) printf("%lld\n",n/k);
        else printf("%lld\n",n/k+1);
    }
    return 0;
}
```
    - **核心实现思想**：遍历输入序列，若当前元素等于 `now + 1`，则 `now` 自增，以此统计从 $1$ 开始的连续递增子序列长度。用总长度 `n` 减去该长度得到需要操作的元素个数，再根据是否整除 `k` 计算并输出操作次数。
- **作者：shinzanmono (4星)**
    - **关键亮点**：同样清晰地阐述了贪心思路，代码使用 `std::ceil` 函数直接进行向上取整操作，较为简洁。
    - **重点代码**：
```cpp
#include<iostream>
#include<cmath>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        int arr[n + 1];
        for (int i = 1; i <= n; i++) std::cin >> arr[i];
        int cur = 0;
        for (int i = 1; i <= n; i++)
            if (arr[i] == cur + 1) cur++;
        std::cout << static_cast<int>(std::ceil(1. * (n - cur) / k)) << "\n";
    }
    return 0;
}
```
    - **核心实现思想**：遍历数组 `arr`，若当前元素等于 `cur + 1`，则 `cur` 自增，统计从 $1$ 开始的连续递增子序列长度 `cur`。通过 `std::ceil` 函数对 `(n - cur) / k` 向上取整并输出操作次数。
- **作者：_JF_ (4星)**
    - **关键亮点**：详细解释了寻找从 $1$ 开始差值为 $1$ 的递增序列的原因，代码逻辑清晰，对操作次数的计算处理明确。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N];
int main()
{
    int n,m,t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        int step=1;
        for(int i=1;i<=n;i++)
            if(a[i]==step)
                step++;
        step--;
        int last=n-step;
        if((last%m)==0)
            cout<<last/m<<endl;
        else
            cout<<last/m+1<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：遍历数组 `a`，若当前元素等于 `step`，则 `step` 自增，统计从 $1$ 开始的连续递增子序列长度 `step`。用总长度 `n` 减去该长度得到需要操作的元素个数 `last`，根据 `last` 是否整除 `m` 计算并输出操作次数。

### 最优关键思路或技巧
关键思路在于利用贪心策略，明确从 $1$ 开始的连续递增子序列无需操作，从而简化问题为对剩余元素进行分组操作。技巧在于通过一次遍历统计该子序列长度，进而快速计算操作次数。

### 拓展
此类题目属于贪心策略在序列操作优化问题中的应用。相似套路为在给定序列操作规则下，寻找无需操作或可最后处理的部分，对剩余部分进行合理分组操作以达到最优解。例如在一些数组重排、元素移动求最小步数的问题中，可尝试寻找固定顺序的子序列，对其他元素进行相应操作。

### 推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859) 

---
处理用时：46.74秒