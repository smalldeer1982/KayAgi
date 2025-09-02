# 题目信息

# Perfect Permutation

## 题目描述

You are given a positive integer $ n $ .

The weight of a permutation $ p_1, p_2, \ldots, p_n $ is the number of indices $ 1\le i\le n $ such that $ i $ divides $ p_i $ . Find a permutation $ p_1,p_2,\dots, p_n $ with the minimum possible weight (among all permutations of length $ n $ ).

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the only valid permutation is $ p=[1] $ . Its weight is $ 1 $ .

In the second test case, one possible answer is the permutation $ p=[2,1,4,3] $ . One can check that $ 1 $ divides $ p_1 $ and $ i $ does not divide $ p_i $ for $ i=2,3,4 $ , so the weight of this permutation is $ 1 $ . It is impossible to find a permutation of length $ 4 $ with a strictly smaller weight.

## 样例 #1

### 输入

```
2
1
4```

### 输出

```
1
2 1 4 3```

# AI分析结果

### 题目中文重写
# 完美排列

## 题目描述
给定一个正整数 $n$。

一个排列 $p_1, p_2, \ldots, p_n$ 的权重是满足 $i$ 能整除 $p_i$ 的索引 $1\leq i\leq n$ 的数量。请找出权重最小的排列 $p_1,p_2,\dots, p_n$（在所有长度为 $n$ 的排列中）。

排列是一个由 $n$ 个从 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是一个排列（$2$ 在数组中出现了两次），$ [1,3,4] $ 也不是一个排列（$n = 3$，但数组中有 $4$）。

## 说明/提示
在第一个测试用例中，唯一有效的排列是 $p = [1]$，其权重为 $1$。

在第二个测试用例中，一个可能的答案是排列 $p = [2,1,4,3]$。可以验证，$1$ 能整除 $p_1$，而对于 $i = 2,3,4$，$i$ 不能整除 $p_i$，所以这个排列的权重为 $1$。不可能找到一个长度为 $4$ 且权重更小的排列。

## 样例 #1
### 输入
```
2
1
4
```
### 输出
```
1
2 1 4 3
```

### 综合分析与结论
这些题解的核心目标都是构造一个长度为 $n$ 的排列，使排列的权重最小。由于任何正整数都能被 $1$ 整除，所以排列的最小权重至少为 $1$，题解的关键在于让除第一个元素外的其他元素不满足被其索引整除的条件。

### 思路与算法要点
- **错位法**：将第一个元素设为 $n$，其余元素按顺序从 $1$ 到 $n - 1$ 排列，即排列为 $[n, 1, 2, \cdots, n - 1]$。利用相邻整数互质的性质，保证除第一个元素外，其他元素不满足整除条件。
- **调换法**：当 $n$ 为偶数时，交换相邻的两个数；当 $n$ 为奇数时，先输出 $1$，再交换后续相邻的两个数。同样基于相邻整数互质的性质。
- **通用构造法**：让每个位置 $i$ 上的元素为 $i + 1$ 或 $i - 1$，并使用数组标记避免重复，保证元素不越界。

### 解决难点
主要难点在于如何构造出满足条件的排列，使权重最小。题解通过利用相邻整数互质的性质，巧妙地解决了这一问题。

### 题解评分
| 作者 | 评分 | 理由 |
| --- | --- | --- |
| diqiuyi | 4星 | 提供两种思路，思路清晰，但未给出代码。 |
| shenyiran | 4星 | 思路明确，代码简洁易懂。 |
| sw2022 | 4星 | 提供两种方法，代码完整，解释清晰。 |
| arkerny | 3星 | 思路和代码基本正确，但权重定义解释有误。 |
| Shimotsuki | 3星 | 思路清晰，但未给出代码。 |
| 封禁用户 | 4星 | 思路清晰，代码完整，有总结和心得。 |
| Jeremiahy | 3星 | 思路和代码正确，给出相关习题。 |
| _Ad_Astra_ | 3星 | 思路和代码正确，但表述较口语化。 |
| qip101 | 3星 | 思路和代码正确，但代码有小错误（输出格式问题）。 |
| Failure_Terminator | 3星 | 思路和代码正确，使用快读但代码稍复杂。 |
| zhicheng | 3星 | 思路和代码正确，但代码注释较少。 |
| Scorilon | 3星 | 思路正确，使用数组判重，但代码较复杂。 |
| __KrNalty__ | 3星 | 思路正确，分类讨论但代码未完整给出。 |

### 所选题解
- **作者：diqiuyi（4星）**
    - **关键亮点**：提供两种思路，一种是构造 $p_i = i + 1$，$p_n = 1$；另一种是根据 $n$ 的奇偶性进行不同构造，思路全面。
- **作者：shenyiran（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接输出 $i + 1$，最后输出 $1$。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n;
    int main(){
        scanf("%d",&t);
        while(t--){
            scanf("%d",&n);
            for(int i=1;i<=n-1;i++){
                printf("%d ",i+1);
            }
            printf("1 ");
            printf("\n");
        }
        return 0;
    } 
    ```
- **作者：封禁用户（4星）**
    - **关键亮点**：思路清晰，代码完整，有总结和心得，提到从最小情况入手构造最优解的策略。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n;
    int main(){
        cin>>t;
        while(t--){
            cin>>n;
            cout<<n<<" ";
            for(int i=1;i<=n-1;i++){
                cout<<i<<" ";
            }
            cout<<endl;
        }
        return 0;
    } 
    ```

### 最优关键思路或技巧
利用相邻整数互质的性质，通过错位或调换相邻元素的方法，构造出权重最小的排列。

### 拓展思路
同类型题目可能会改变排列的条件或权重的定义，解题时可以考虑利用数论中的其他性质，如质数、最大公约数等进行构造。

### 推荐题目
1. [P5436 【XR-2】缘分](https://www.luogu.com.cn/problem/P5436)
2. [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
3. [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)

### 个人心得摘录与总结
- **封禁用户**：提到在做构造题时，从最小情况入手，慢慢推导最优结果，类似于贪心策略，同时注意输出格式，避免罚时。

---
处理用时：33.02秒