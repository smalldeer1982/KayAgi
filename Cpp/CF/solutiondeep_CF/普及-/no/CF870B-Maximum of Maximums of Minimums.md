# 题目信息

# Maximum of Maximums of Minimums

## 题目描述

You are given an array $ a_{1},a_{2},...,a_{n} $ consisting of $ n $ integers, and an integer $ k $ . You have to split the array into exactly $ k $ non-empty subsegments. You'll then compute the minimum integer on each subsegment, and take the maximum integer over the $ k $ obtained minimums. What is the maximum possible integer you can get?

Definitions of subsegment and array splitting are given in notes.

## 说明/提示

A subsegment $ [l,r] $ ( $ l<=r $ ) of array $ a $ is the sequence $ a_{l},a_{l+1},...,a_{r} $ .

Splitting of array $ a $ of $ n $ elements into $ k $ subsegments $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , ..., $ [l_{k},r_{k}] $ ( $ l_{1}=1 $ , $ r_{k}=n $ , $ l_{i}=r_{i-1}+1 $ for all $ i>1 $ ) is $ k $ sequences $ (a_{l1},...,a_{r1}),...,(a_{lk},...,a_{rk}) $ .

In the first example you should split the array into subsegments $ [1,4] $ and $ [5,5] $ that results in sequences $ (1,2,3,4) $ and $ (5) $ . The minimums are $ min(1,2,3,4)=1 $ and $ min(5)=5 $ . The resulting maximum is $ max(1,5)=5 $ . It is obvious that you can't reach greater result.

In the second example the only option you have is to split the array into one subsegment $ [1,5] $ , that results in one sequence $ (-4,-5,-3,-2,-1) $ . The only minimum is $ min(-4,-5,-3,-2,-1)=-5 $ . The resulting maximum is $ -5 $ .

## 样例 #1

### 输入

```
5 2
1 2 3 4 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 1
-4 -5 -3 -2 -1
```

### 输出

```
-5
```

# AI分析结果

### 题目中文重写
# 最小值中的最大值

## 题目描述
给定一个由 $n$ 个整数组成的数组 $a_{1},a_{2},\cdots,a_{n}$ 以及一个整数 $k$。你需要将该数组恰好分割成 $k$ 个非空子段。接着，你要计算每个子段中的最小整数，然后取这 $k$ 个最小值中的最大值。你能得到的最大整数是多少？

子段和数组分割的定义在注释中给出。

## 说明/提示
数组 $a$ 的子段 $[l,r]$（$l\leq r$）是指序列 $a_{l},a_{l + 1},\cdots,a_{r}$。

将包含 $n$ 个元素的数组 $a$ 分割成 $k$ 个子段 $[l_{1},r_{1}]$，$[l_{2},r_{2}]$，$\cdots$，$[l_{k},r_{k}]$（$l_{1}=1$，$r_{k}=n$，对于所有 $i > 1$ 有 $l_{i}=r_{i - 1}+1$），即得到 $k$ 个序列 $(a_{l1},\cdots,a_{r1}),\cdots,(a_{lk},\cdots,a_{rk})$。

在第一个示例中，你应该将数组分割成子段 $[1,4]$ 和 $[5,5]$，得到序列 $(1,2,3,4)$ 和 $(5)$。最小值分别为 $\min(1,2,3,4)=1$ 和 $\min(5)=5$。最终的最大值为 $\max(1,5)=5$。显然，你无法得到更大的结果。

在第二个示例中，你唯一的选择是将数组分割成一个子段 $[1,5]$，得到一个序列 $(-4,-5,-3,-2,-1)$。唯一的最小值是 $\min(-4,-5,-3,-2,-1)=-5$。最终的最大值是 $-5$。

## 样例 #1
### 输入
```
5 2
1 2 3 4 5
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5 1
-4 -5 -3 -2 -1
```
### 输出
```
-5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过分类讨论 $k$ 的不同取值情况，利用贪心策略来求解问题。具体如下：
- **$k = 1$ 时**：整个数组作为一个子段，结果为数组中的最小值。
- **$k = 2$ 时**：两个子段分别包含数组首尾元素，结果为首尾元素中的最大值。
- **$k \geq 3$ 时**：将数组中的最大值单独作为一个子段，结果为数组中的最大值。

各题解的主要区别在于代码实现方式和对思路的解释详细程度。部分题解使用排序来获取最值，部分题解则在输入时直接记录最值，避免了排序的时间复杂度。

### 所选题解
- **HD0X（5星）**：
    - **关键亮点**：思路清晰，代码简洁，对每种情况的分析明确。
    - **核心代码**：
```c
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[100001];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    if(k==1)
    {
        sort(a+1,a+1+n);
        cout<<a[1];
    }
    else if(k>=3)
    {
        sort(a+1,a+1+n);
        cout<<a[n];
    }
    else
    {
        if(a[1]>=a[n])
        {
            cout<<a[1];
        }
        else
        {
            cout<<a[n];
        }
    }
    return 0;
}
```
核心实现思想：先读取输入的数组和 $k$ 值，然后根据 $k$ 的不同取值进行分类讨论。当 $k = 1$ 时，对数组排序后输出第一个元素（最小值）；当 $k \geq 3$ 时，排序后输出最后一个元素（最大值）；当 $k = 2$ 时，比较首尾元素大小并输出较大值。

- **lu_run_ting（4星）**：
    - **关键亮点**：使用 STL 函数简化代码，对每种情况的分析结合贪心思想，解释清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int n,k,a[N];
int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>a[i];
    if(k==1) cout<<*min_element(a,a+n)<<endl;
    else if(k==2) cout<<max(a[0],a[n-1])<<endl;
    else cout<<*max_element(a,a+n)<<endl;
    return 0; 
} 
```
核心实现思想：读取输入后，根据 $k$ 的取值，分别使用 `min_element` 函数获取最小值，`max` 函数比较首尾元素，`max_element` 函数获取最大值并输出。

- **WLR__jr（4星）**：
    - **关键亮点**：在输入时直接记录最小值和最大值，避免排序，提高效率，同时对边界值的设定有提示。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[11100000];
int main()
{
    int minn=1061109567,maxn=-1061109567;
    int n,k;scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        minn=min(minn,a[i]);
        maxn=max(maxn,a[i]);
    }
    if(k==1)printf("%d\n",minn);
    else if(k>2)printf("%d\n",maxn);
    else if(k==2)printf("%d\n",max(a[1],a[n]));
    return 0;
}
```
核心实现思想：在输入数组元素的同时，记录最小值 `minn` 和最大值 `maxn`。根据 $k$ 的取值，直接输出相应结果。

### 最优关键思路或技巧
- **分类讨论**：根据 $k$ 的不同取值情况进行分类讨论，简化问题求解过程。
- **贪心策略**：在不同情况下，通过合理分配子段，使得最终结果最大。
- **避免排序**：部分题解在输入时直接记录最小值和最大值，避免了排序的 $O(n\log n)$ 时间复杂度，将时间复杂度优化到 $O(n)$。

### 拓展思路
同类型题目通常会涉及对数组的分割和最值求解，可采用分类讨论和贪心策略。类似的算法套路包括：
- 对问题进行合理分类，针对不同情况采用不同的求解方法。
- 利用贪心思想，在每一步都做出当前最优的选择，以达到全局最优。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略解决合并果子的最小代价问题。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：利用贪心算法求解排队接水的最小等待时间。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：使用贪心策略解决部分背包问题。

### 个人心得摘录与总结
- **WLR__jr**：提到千万不能把最值的初始值定小，第一次就是跪在了 999999999 上。总结：在处理最值问题时，要合理设置初始值，避免因初始值设置不当导致错误。 

---
处理用时：48.41秒