# 题目信息

# Inversion Graph

## 题目描述

You are given a permutation $ p_1, p_2, \dots, p_n $ . Then, an undirected graph is constructed in the following way: add an edge between vertices $ i $ , $ j $ such that $ i < j $ if and only if $ p_i > p_j $ . Your task is to count the number of connected components in this graph.

Two vertices $ u $ and $ v $ belong to the same connected component if and only if there is at least one path along edges connecting $ u $ and $ v $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

Each separate test case is depicted in the image below. The colored squares represent the elements of the permutation. For one permutation, each color represents some connected component. The number of distinct colors is the answer.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638C/555cddc5b98ba416425dd4322ce8f820d678b370.png)

## 样例 #1

### 输入

```
6
3
1 2 3
5
2 1 4 3 5
6
6 1 4 2 5 3
1
1
6
3 2 1 6 5 4
5
3 1 5 2 4```

### 输出

```
3
3
1
1
2
1```

# AI分析结果

### 题目内容重写

#### 题目描述
给定一个排列 $p_1, p_2, \dots, p_n$，构造一个无向图：当且仅当 $i < j$ 且 $p_i > p_j$ 时，在顶点 $i$ 和 $j$ 之间添加一条无向边。你的任务是计算这个图中连通块的数量。

两个顶点 $u$ 和 $v$ 属于同一个连通块，当且仅当存在至少一条路径连接 $u$ 和 $v$。

一个排列是由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

#### 输入格式
第一行一个整数 $T$，表示测试组数。  
每组第一行一个整数 $n$，表示排列的长度。  
每组第二行 $n$ 个整数 $p_1, p_2, \dots, p_n$，表示给定的排列。

#### 输出格式
对于每组测试，输出一个整数，表示图中连通块的数量。

#### 样例
**输入：**
```
6
3
1 2 3
5
2 1 4 3 5
6
6 1 4 2 5 3
1
1
6
3 2 1 6 5 4
5
3 1 5 2 4
```
**输出：**
```
3
3
1
1
2
1
```

### 算法分类
**图论**

### 题解分析与结论
本题的核心是通过排列构造图并计算连通块的数量。大多数题解都利用了排列的性质，通过维护前缀最大值或后缀最小值来判断连通块的边界。以下是各题解的主要思路对比：

1. **前缀和与排列性质**：通过计算前缀和，判断当前前缀是否构成 $1$ 到 $i$ 的排列，从而确定连通块的边界。时间复杂度为 $O(n)$。
2. **单调栈与后缀最小值**：利用单调栈维护连通块的最小值，通过后缀最小值判断连通块的边界。时间复杂度为 $O(n)$。
3. **树状数组与区间查询**：使用树状数组记录比当前元素小的元素数量，判断连通块的边界。时间复杂度为 $O(n \log n)$。

最优的思路是利用排列的性质，通过维护前缀最大值来判断连通块的边界，时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

### 高星题解推荐

#### 题解1：作者：lnwhl (5星)
**关键亮点**：
- 利用排列的性质，通过前缀和判断连通块的边界。
- 代码简洁，时间复杂度为 $O(n)$。

**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100005],ans=0;
long long sum=0;
int main()
{
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];sum+=a[i];
            if(sum==1LL*(1+i)*i/2)ans++;
        }
        cout<<ans<<endl;sum=0;ans=0;
    }
    return 0;
}
```

#### 题解2：作者：hzy1 (4星)
**关键亮点**：
- 通过单调栈维护连通块的最小值，判断连通块的边界。
- 时间复杂度为 $O(n)$。

**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100005],ans=0;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        int mx=0,ans=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            mx=max(mx,a[i]);
            if(mx==i)ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

#### 题解3：作者：lingfunny (4星)
**关键亮点**：
- 通过维护前缀最大值和后缀最小值，判断连通块的边界。
- 时间复杂度为 $O(n)$。

**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100005],ans=0;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        int mx=0,ans=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            mx=max(mx,a[i]);
            if(mx==i)ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

### 最优思路总结
最优的思路是利用排列的性质，通过维护前缀最大值来判断连通块的边界。具体实现时，只需遍历排列，记录当前最大值，当最大值等于当前索引时，说明前 $i$ 个元素构成了一个连通块，答案加 $1$。

### 拓展思路
类似的问题可以通过维护前缀或后缀信息来判断区间性质，例如判断区间是否有序、区间内元素是否满足某种条件等。这类问题通常可以通过一次遍历解决，时间复杂度为 $O(n)$。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：37.31秒