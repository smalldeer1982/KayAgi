# 题目信息

# Roof Construction

## 题目描述

It has finally been decided to build a roof over the football field in School 179. Its construction will require placing $ n $ consecutive vertical pillars. Furthermore, the headmaster wants the heights of all the pillars to form a permutation $ p $ of integers from $ 0 $ to $ n - 1 $ , where $ p_i $ is the height of the $ i $ -th pillar from the left $ (1 \le i \le n) $ .

As the chief, you know that the cost of construction of consecutive pillars is equal to the maximum value of the bitwise XOR of heights of all pairs of adjacent pillars. In other words, the cost of construction is equal to $ \max\limits_{1 \le i \le n - 1}{p_i \oplus p_{i + 1}} $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find any sequence of pillar heights $ p $ of length $ n $ with the smallest construction cost.

In this problem, a permutation is an array consisting of $ n $ distinct integers from $ 0 $ to $ n - 1 $ in arbitrary order. For example, $ [2,3,1,0,4] $ is a permutation, but $ [1,0,1] $ is not a permutation ( $ 1 $ appears twice in the array) and $ [1,0,3] $ is also not a permutation ( $ n=3 $ , but $ 3 $ is in the array).

## 说明/提示

For $ n = 2 $ there are $ 2 $ sequences of pillar heights:

- $ [0, 1] $ — cost of construction is $ 0 \oplus 1 = 1 $ .
- $ [1, 0] $ — cost of construction is $ 1 \oplus 0 = 1 $ .

For $ n = 3 $ there are $ 6 $ sequences of pillar heights:

- $ [0, 1, 2] $ — cost of construction is $ \max(0 \oplus 1, 1 \oplus 2) = \max(1, 3) = 3 $ .
- $ [0, 2, 1] $ — cost of construction is $ \max(0 \oplus 2, 2 \oplus 1) = \max(2, 3) = 3 $ .
- $ [1, 0, 2] $ — cost of construction is $ \max(1 \oplus 0, 0 \oplus 2) = \max(1, 2) = 2 $ .
- $ [1, 2, 0] $ — cost of construction is $ \max(1 \oplus 2, 2 \oplus 0) = \max(3, 2) = 3 $ .
- $ [2, 0, 1] $ — cost of construction is $ \max(2 \oplus 0, 0 \oplus 1) = \max(2, 1) = 2 $ .
- $ [2, 1, 0] $ — cost of construction is $ \max(2 \oplus 1, 1 \oplus 0) = \max(3, 1) = 3 $ .

## 样例 #1

### 输入

```
4
2
3
5
10```

### 输出

```
0 1
2 0 1
3 2 1 0 4
4 6 3 2 0 8 9 1 7 5```

# AI分析结果

### 题目内容
# 屋顶建造

## 题目描述
最终决定在179中学的足球场上方建造一个屋顶。建造屋顶需要放置 $n$ 根连续的垂直支柱。此外，校长希望所有支柱的高度形成一个从 $0$ 到 $n - 1$ 的整数排列 $p$，其中 $p_i$ 是从左数第 $i$ 根支柱的高度 ($1 \leq i \leq n$)。

作为负责人，你知道连续支柱的建造成本等于所有相邻支柱对高度的按位异或的最大值。换句话说，建造成本等于 $\max\limits_{1 \leq i \leq n - 1}{p_i \oplus p_{i + 1}}$，其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

找到任何长度为 $n$ 的支柱高度序列 $p$，使其建造成本最小。

在本题中，排列是指由 $n$ 个从 $0$ 到 $n - 1$ 的不同整数按任意顺序组成的数组。例如，$[2,3,1,0,4]$ 是一个排列，但 $[1,0,1]$ 不是排列（数组中 $1$ 出现了两次），$[1,0,3]$ 也不是排列（$n = 3$，但数组中有 $3$）。

## 说明/提示
对于 $n = 2$，有 $2$ 种支柱高度序列：
 - $[0, 1]$ —— 建造成本是 $0 \oplus 1 = 1$。
 - $[1, 0]$ —— 建造成本是 $1 \oplus 0 = 1$。

对于 $n = 3$，有 $6$ 种支柱高度序列：
 - $[0, 1, 2]$ —— 建造成本是 $\max(0 \oplus 1, 1 \oplus 2) = \max(1, 3) = 3$。
 - $[0, 2, 1]$ —— 建造成本是 $\max(0 \oplus 2, 2 \oplus 1) = \max(2, 3) = 3$。
 - $[1, 0, 2]$ —— 建造成本是 $\max(1 \oplus 0, 0 \oplus 2) = \max(1, 2) = 2$。
 - $[1, 2, 0]$ —— 建造成本是 $\max(1 \oplus 2, 2 \oplus 0) = \max(3, 2) = 3$。
 - $[2, 0, 1]$ —— 建造成本是 $\max(2 \oplus 0, 0 \oplus 1) = \max(2, 1) = 2$。
 - $[2, 1, 0]$ —— 建造成本是 $\max(2 \oplus 1, 1 \oplus 0) = \max(3, 1) = 3$。

## 样例 #1
### 输入
```
4
2
3
5
10
```
### 输出
```
0 1
2 0 1
3 2 1 0 4
4 6 3 2 0 8 9 1 7 5
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路较为一致，都围绕寻找使得相邻元素按位异或最大值最小的排列展开。首先确定一个关键值 $k$，它与 $n - 1$ 的二进制最高位相关，即 $k$ 满足 $2^k \leq n - 1 < 2^{k + 1}$。通过证明得出最小建造成本为 $k$，因为必然存在至少一个大于等于 $k$ 的数与小于 $k$ 的数相邻，其异或值大于等于 $k$，同时两类数（大于等于 $k$ 和小于 $k$）内部两两异或值小于 $k$。然后通过构造特定的排列，如将小于 $k$ 的数放在一侧，大于等于 $k$ 的数放在另一侧，并让 $k$ 与 $0$ 相邻，使得相邻元素按位异或最大值恰好为 $k$。不同题解在表述、证明细节和代码实现上略有差异。

### 所选的题解
- **作者：Jorge_Filho (赞：13)  星级：5星**
    - **关键亮点**：思路清晰，先给出关键值 $k$ 的定义及最小建造成本为 $k$ 的证明，再详细说明构造序列的方式及原理，代码简洁明了且注释详细。
    - **个人心得**：无
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int T=1e4,N=2e5;
    int t,n,k,a[N+5],top;

    int  main()
    {
        scanf("%d",&t);
        while(t--)
        {
            scanf("%d",&n);
            k=1;
            top=0;
            while(k<n)
            {
                k<<=1;
            }
            k>>=1;
            for(int i=n-1;i>=k;i--)
            {
                a[++top]=i;
            }
            for(int i=0;i<k;i++)
            {
                a[++top]=i;
            }
            for(int i=1;i<=top;i++)
            {
                printf("%d ",a[i]); 
            }
            printf("\n");
        }
        return 0;
    }
    ```
    - **核心代码简述**：先通过循环找到小于 $n$ 的最大的 $2$ 的整数次幂 $k$，然后分别将大于等于 $k$ 的数从大到小、小于 $k$ 的数从小到大存入数组，最后依次输出数组元素。
- **作者：include_BM (赞：6)  星级：4星**
    - **关键亮点**：简洁地阐述了关键值 $k$ 与最小建造成本的关系及证明，直接给出符合要求的序列，表述精炼。
    - **个人心得**：无
    ```cpp
    // 无代码，思路为：因为 k^0=k，所以可以得到一个符合要求的序列 n-1,n-2,…,k,0,1,2,…,k-1
    ```
    - **核心代码简述**：按照思路，若要实现，可类似其他题解，先找 $k$，再按序输出上述序列。
- **作者：qzhwlzy (赞：2)  星级：4星**
    - **关键亮点**：对思路的阐述详细，从分析最小代价不小于 $2^k$ 入手，再分别说明两类数内部异或情况，最后给出具体可构造的排列形式，逻辑连贯。
    - **个人心得**：无
    ```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    int t,n;
    int main(){
        scanf("%d",&t);
        while(t--){
            scanf("%d",&n);
            int k=0;
            while(1<<(k+1)<=(n-1)) k++;
            for(int i=(1<<k)-1;i>=0;i--) printf("%d ",i);
            for(int i=(1<<k);i<n;i++) printf("%d ",i);
            printf("\n");
        }
        return 0;
    }
    ```
    - **核心代码简述**：通过循环确定 $k$，然后分别输出小于 $2^k$ 的数从大到小、大于等于 $2^k$ 的数从小到大。

### 最优关键思路或技巧
通过对 $n - 1$ 进行二进制分析确定关键值 $k$，利用按位异或在不同区间数上的特性，将数分为大于等于 $k$ 和小于 $k$ 两类进行构造排列，巧妙地使相邻元素按位异或最大值达到最小。

### 可拓展思路
此类题目属于构造类问题，通常需要深入分析题目条件背后的数学原理，利用特定运算（本题为按位异或）的性质来构造满足要求的解。类似题目可能会改变运算规则或限制条件，例如改变为其他位运算，或者对排列有更多约束，解题时需抓住核心运算的特点进行分析构造。

### 推荐洛谷题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：通过贪心策略构造最小数，与本题通过分析特性构造序列思路类似。
- [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)：利用贪心思想构造最优合并方案，同样是通过分析问题特性来找到最优解。
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：运用二分答案的方式构造满足条件的方案，与本题构造满足特定条件序列的思路有相通之处。

### 个人心得摘录与总结
- **作者：GoodLuckCat**：强调变量初始化的重要性，若 $k$ 未赋值会导致超时，提醒编程时要注意变量初始化，避免因小失大。 

---
处理用时：67.88秒