# 题目信息

# Permutations

## 题目描述

You are given a permutation $ p $ of numbers $ 1,2,...,n $ . Let's define $ f(p) $ as the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B1/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)Find the lexicographically $ m $ -th permutation of length $ n $ in the set of permutations having the maximum possible value of $ f(p) $ .

## 说明/提示

In the first example, both permutations of numbers {1, 2} yield maximum possible $ f(p) $ which is equal to 4. Among them, $ (2,1) $ comes second in lexicographical order.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 3 2 
```

# AI分析结果

### 题目内容（中文重写）
# 排列

## 题目描述
给定一个数字 $1,2,\cdots,n$ 的排列 $p$。定义 $f(p)$ 为以下求和式：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B1/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)
找出在所有使得 $f(p)$ 取得最大值的长度为 $n$ 的排列集合中，字典序第 $m$ 小的排列。

## 说明/提示
在第一个样例中，数字 $\{1, 2\}$ 的两个排列都能使 $f(p)$ 取得最大值，该最大值等于 4。在这些排列中，$(2,1)$ 在字典序中排第二。

## 样例 #1
### 输入
```
2 2
```
### 输出
```
2 1 
```

## 样例 #2
### 输入
```
3 2
```
### 输出
```
1 3 2 
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是先枚举所有排列，计算每个排列的 $f(p)$ 值，找出 $f(p)$ 的最大值，然后再枚举所有排列，找出使得 $f(p)$ 等于最大值的字典序第 $m$ 小的排列。

不同题解的实现方式略有不同，主要区别在于枚举全排列的方法：有的使用深度优先搜索（DFS），有的使用 `next_permutation` 函数。在计算 $f(p)$ 时，都是通过三重循环枚举子段并求最小值求和。

### 题解评分
- Universal_xtr：3星。思路清晰，有详细注释，但使用 Python 实现，对于 C++ 题目参考性稍弱。
- Fire_flame：3星。使用 DFS 实现，代码结构清晰，但部分变量命名可优化。
- xvl_：3星。使用两次 DFS 分别求最大值和第 $m$ 个排列，逻辑较清晰。
- 封禁用户：3星。使用 `next_permutation` 函数，代码简洁，但变量命名较随意。
- WangBng：3星。使用 `next_permutation` 函数，代码结构清晰，但部分变量命名可优化。
- Eason_AC：3星。使用 `next_permutation` 函数，代码有一定封装，但自定义宏 `F` 可能增加理解难度。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
- 通用建议：在枚举全排列时，要注意按字典序枚举，确保结果的正确性。在计算 $f(p)$ 时，可以考虑优化子段最小值的计算，减少不必要的计算量。
- 扩展思路：对于此类枚举排列并计算特定值的题目，可以先分析排列的性质，尝试找出使特定值最大或最小的排列规律，从而减少枚举的范围。

### 重点代码
以下是使用 `next_permutation` 函数的示例代码，核心思想是先枚举所有排列求出 $f(p)$ 的最大值，再枚举所有排列找出第 $m$ 个使 $f(p)$ 等于最大值的排列。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=20;
ll n,m,minn,maxx,cnt,ans,a[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        a[i]=i;
    }
    do
    {
        ans=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j<=n;j++)
            {
                minn=n+1;
                for(int k=i;k<=j;k++)
                {
                    minn=min(minn,a[k]);
                }
                ans+=minn;
            }
        }
        maxx=max(maxx,ans);
    }
    while(next_permutation(a+1,a+n+1));
    for(int i=1;i<=n;i++)
    {
        a[i]=i;
    }
    do
    {
        ans=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j<=n;j++)
            {
                minn=n+1;
                for(int k=i;k<=j;k++)
                {
                    minn=min(minn,a[k]);
                }
                ans+=minn;
            }
        }
        if(ans==maxx)
        {
            cnt++;
        }
        if(cnt==m)
        {
            for(int i=1;i<=n;i++)
            {
                cout<<a[i]<<" ";
            }
            cout<<"\n";
            return 0;
        }
    }
    while(next_permutation(a+1,a+n+1));
    return 0;
}
```

### 推荐题目
- [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：考察全排列的生成。
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)：涉及排列的字典序问题。
- [P2386 放苹果](https://www.luogu.com.cn/problem/P2386)：需要枚举不同的放置方案。

### 个人心得摘录与总结
Universal_xtr 提到在函数开始要 `global` 引入全局变量，否则会抛出 `UnBoundLocalError`，这是 Python 中使用全局变量的一个注意点。同时还提到枚举全排列时要按字典序枚举，以及在个数超过 $m$ 时可以提前结束程序，这些都是提高效率和保证结果正确性的关键。 

---
处理用时：33.54秒