# 题目信息

# Koxia and Permutation

## 题目描述

Reve has two integers $ n $ and $ k $ .

Let $ p $ be a permutation $ ^\dagger $ of length $ n $ . Let $ c $ be an array of length $ n - k + 1 $ such that $ $$$c_i = \max(p_i, \dots, p_{i+k-1}) + \min(p_i, \dots, p_{i+k-1}). $ $  Let the <span class="tex-font-style-it">cost</span> of the permutation  $ p $  be the maximum element of  $ c $ .</p><p>Koxia wants you to construct a permutation with the minimum possible cost.</p><p> $ ^\\dagger $  A permutation of length  $ n $  is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array), and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4$$$ in the array).

## 说明/提示

In the first test case,

- $ c_1 = \max(p_1,p_2,p_3) + \min(p_1,p_2,p_3) = 5 + 1 = 6 $ .
- $ c_2 = \max(p_2,p_3,p_4) + \min(p_2,p_3,p_4) = 3 + 1 = 4 $ .
- $ c_3 = \max(p_3,p_4,p_5) + \min(p_3,p_4,p_5) = 4 + 2 = 6 $ .

Therefore, the cost is $ \max(6,4,6)=6 $ . It can be proven that this is the minimal cost.

## 样例 #1

### 输入

```
3
5 3
5 1
6 6```

### 输出

```
5 1 2 3 4
1 2 3 4 5
3 2 4 1 6 5```

# AI分析结果

### 题目内容
# Koxia和排列

## 题目描述
Reve有两个整数 $n$ 和 $k$ 。
设 $p$ 是一个长度为 $n$ 的排列 $ ^\dagger $ 。设 $c$ 是一个长度为 $n - k + 1$ 的数组，使得 
$$c_i = \max(p_i, \dots, p_{i+k-1}) + \min(p_i, \dots, p_{i+k-1})$$ 。设排列 $p$ 的**代价**为 $c$ 中的最大元素。
Koxia希望你构造一个具有最小可能代价的排列。
$ ^\dagger $ 长度为 $n$ 的排列是一个由从 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（数组中 $2$ 出现两次），$[1,3,4]$ 也不是排列（$n = 3$ 但数组中有 $4$）。

## 说明/提示
在第一个测试用例中，
- $c_1 = \max(p_1,p_2,p_3) + \min(p_1,p_2,p_3) = 5 + 1 = 6$ 。
- $c_2 = \max(p_2,p_3,p_4) + \min(p_2,p_3,p_4) = 3 + 1 = 4$ 。
- $c_3 = \max(p_3,p_4,p_5) + \min(p_3,p_4,p_5) = 4 + 2 = 6$ 。

因此，代价是 $\max(6,4,6)=6$ 。可以证明这是最小代价。

## 样例 #1
### 输入
```
3
5 3
5 1
6 6
```
### 输出
```
5 1 2 3 4
1 2 3 4 5
3 2 4 1 6 5
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是构造一个排列 $p$，使得 $c$ 数组中的最大值最小。多数题解先证明了答案的下界为 $n + 1$ ，因为必然存在一个长度为 $k$ 的区间包含 $n$ 和至少为 $1$ 的最小值 。然后通过不同方式构造出能达到该下界的排列。
1. **思路对比**：
    - **多数题解**：采用交叉构造的方式，即依次将当前未使用的最大值和最小值交替放入排列中，如构造出 $[n, 1, n - 1, 2, \cdots]$ 的形式。
    - **abensyl**：将 $1$ 和 $n$，$2$ 和 $n - 1$ 等数对分别放在不同的长度为 $k$ 的区间内，剩余数字随意填充。
    - **zajasi**：采用贪心思想，先放置 $k - 1$ 个最大值，再放置 $k - 1$ 个最小值，循环此过程。
    - **郑朝曦zzx**：对位置 $i \bmod k = 0$ 的位置填上 $\frac{i}{k}$，其他位置从大往小填充。
2. **算法要点**：多数题解的算法要点在于找到一种合理的元素放置顺序，保证每个长度为 $k$ 的区间内 $\max + \min$ 的值尽量小且不超过 $n + 1$。
3. **解决难点**：难点在于如何设计一种通用的构造方式，使得无论 $n$ 和 $k$ 取何值，都能满足代价最小的要求。多数题解通过分析不同 $k$ 值下的情况，找到交叉构造这一通用方法来解决此难点。

### 所选的题解
- **作者：AllenKING_RED (5星)**
    - **关键亮点**：思路清晰，先从 $k = 2$ 的简单情况入手分析，逐步推广到其他 $k$ 值的情况，逻辑连贯，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(void)
{
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            if(i%2==1)cout<<n-(i+1)/2+1<<" ";
            else cout<<i/2<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：通过循环，根据 $i$ 的奇偶性，交替输出当前未使用的最大值和最小值，从而构造出满足要求的排列。
- **作者：yangyang1000 (4星)**
    - **关键亮点**：先明确总分最小值为 $n + 1$ ，并基于此提出交叉构造的思路，逻辑较为清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int t,n,k;

int main()
{
    scanf("%d",&t);
    for(int o=1;o<=t;o++)
    {
        scanf("%d %d",&n,&k);
        int l=1,r=n;
        bool flag = 0;
        for(int i=1;i<=n;i++)
        {
            if(flag == 0)
            {
                printf("%d ",r);
                r--;
                flag = 1;
            }
            else
            {
                printf("%d ",l);
                l++;
                flag = 0;
            }
        }
        printf("\n");
    }
    return 0;
}
```
    - **核心实现思想**：利用两个指针 $l$ 和 $r$ 分别指向 $1$ 和 $n$，通过一个布尔变量 $flag$ 控制交替输出 $r$ 和 $l$ 的值，实现排列的构造。
- **作者：Night_sea_64 (4星)**
    - **关键亮点**：简洁明了地分析出要让 $n$ 和 $1$ 在同一组，$n - 1$ 和 $2$ 在同一组等，进而直接给出简洁的构造代码。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n/2;i++)
            cout<<n-i+1<<" "<<i<<" ";
        if(n%2)cout<<n/2+1;
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：通过循环，每次输出一对数，分别为当前未使用的最大值和最小值，最后处理 $n$ 为奇数时剩余的中间值。

### 最优关键思路或技巧
交叉构造的思维方式是关键技巧，通过交替放置最大值和最小值，能有效保证每个长度为 $k$ 的区间内 $\max + \min$ 的值最小且不超过 $n + 1$。

### 可拓展之处
同类型题通常围绕特定条件下的序列构造展开，类似算法套路是先分析问题的最优下界，再尝试构造出能达到该下界的方案。可以通过改变限制条件，如改变区间长度的计算方式、元素取值范围等，衍生出不同题目。

### 相似知识点洛谷题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式解决问题，与本题构造排列的思路类似，都需要根据一定条件生成满足要求的序列。
2. [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要构造等式，通过枚举和判断来找到满足条件的组合，和本题构造满足最小代价的排列思路有相似之处。
3. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：涉及路径构造，通过搜索和判断找到最优路径，和本题构造最优排列在构造最优解的思想上有共通点。

### 个人心得摘录与总结
 - **abensyl**：比赛时WA两次，但最终通过。强调构造时要注意数字放置的区间以及剩余数字的处理。总结出构造时小数需在大数之后，大值放区间第一个数，小值放区间内第二个数等经验。 

---
处理用时：54.18秒