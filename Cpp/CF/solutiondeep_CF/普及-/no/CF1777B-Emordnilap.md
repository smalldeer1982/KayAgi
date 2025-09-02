# 题目信息

# Emordnilap

## 题目描述

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array). There are $ n! = n \cdot (n-1) \cdot (n - 2) \cdot \ldots \cdot 1 $ different permutations of length $ n $ .

Given a permutation $ p $ of $ n $ numbers, we create an array $ a $ consisting of $ 2n $ numbers, which is equal to $ p $ concatenated with its reverse. We then define the beauty of $ p $ as the number of inversions in $ a $ .

The number of inversions in the array $ a $ is the number of pairs of indices $ i $ , $ j $ such that $ i < j $ and $ a_i > a_j $ .

For example, for permutation $ p = [1, 2] $ , $ a $ would be $ [1, 2, 2, 1] $ . The inversions in $ a $ are $ (2, 4) $ and $ (3, 4) $ (assuming 1-based indexing). Hence, the beauty of $ p $ is $ 2 $ .

Your task is to find the sum of beauties of all $ n! $ permutations of size $ n $ . Print the remainder we get when dividing this value by $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case of the example, $ p = [1] $ is the only permutation. $ a = [1, 1] $ has $ 0 $ inversions.

For the second test case of the example, the permutations are $ [1, 2] $ and $ [2, 1] $ . Their respective $ a $ arrays are $ [1, 2, 2, 1] $ and $ [2, 1, 1, 2] $ , both of which have $ 2 $ inversions.

## 样例 #1

### 输入

```
3
1
2
100```

### 输出

```
0
4
389456655```

# AI分析结果

### 题目内容
# Emordnilap

## 题目描述
长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（数组中 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n = 3$ 但数组中有 $4$）。长度为 $n$ 的排列共有 $n! = n \cdot (n - 1) \cdot (n - 2) \cdot \ldots \cdot 1$ 种不同的排列。

给定一个长度为 $n$ 的排列 $p$，我们创建一个由 $2n$ 个数组成的数组 $a$，它等于 $p$ 与其反转数组拼接在一起。然后我们将 $p$ 的美丽值定义为 $a$ 中的逆序对数量。

数组 $a$ 中的逆序对数量是指满足 $i < j$ 且 $a_i > a_j$ 的索引对 $(i, j)$ 的数量。

例如，对于排列 $p = [1, 2]$，$a$ 将是 $[1, 2, 2, 1]$。$a$ 中的逆序对是 $(2, 4)$ 和 $(3, 4)$（假设基于 1 索引）。因此，$p$ 的美丽值是 $2$。

你的任务是找到所有 $n!$ 个长度为 $n$ 的排列的美丽值之和。输出该值除以 $1000000007$（$10^9 + 7$）的余数。

## 说明/提示
对于示例中的第一个测试用例，$p = [1]$ 是唯一的排列。$a = [1, 1]$ 有 $0$ 个逆序对。

对于示例中的第二个测试用例，排列是 $[1, 2]$ 和 $[2, 1]$。它们各自的 $a$ 数组分别是 $[1, 2, 2, 1]$ 和 $[2, 1, 1, 2]$，两者都有 $2$ 个逆序对。

## 样例 #1
### 输入
```
3
1
2
100
```
### 输出
```
0
4
389456655
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过找规律或数学推导得出每个排列对应的逆序对数量固定，进而通过该固定值与排列数 $n!$ 的乘积得到最终答案。各题解的主要区别在于规律的发现方式和推导过程的详细程度。部分题解通过具体枚举小 $n$ 值的排列来观察规律，部分则从排列和逆序对的数学性质出发进行推导。

### 所选的题解
- **作者：arrow_king（5星）**
  - **关键亮点**：思路清晰，先通过枚举 $n = 3$ 的所有排列找到规律，即每种排列的逆序对数量相同，再从数学原理上进行严谨推导，得出逆序对数量的计算公式，代码极度精简。
  - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define mod 1000000007
#define il inline
#define ll long long
ll t,n;
il ll frac(ll n) {
    ll ans=1;
    for(int i=2;i<=n;i++) ans=(ans*i)%mod;
    return ans;
}
int main() {
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld",&n);
        printf("%lld\n",((n*(n-1))%mod*frac(n))%mod);
    }
    return 0;
}
```
  - **核心实现思想**：通过 `frac` 函数计算阶乘，在 `main` 函数中根据推导出的公式 `n*(n - 1)*n!` 计算答案并取模输出。
- **作者：rainygame（4星）**
  - **关键亮点**：详细描述了思考过程，从暴力解法开始，逐步优化时间复杂度，通过考场找规律并给出证明，还提到了预处理阶乘进一步优化时间复杂度的方法，代码实现清晰。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 1e5+1;
long long t, n, x = 1;
long long f[MAXN];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for (int i=1; i<MAXN; i++){
        x = (x*i)%MOD;
        f[i] = x;
    }
    cin >> t;
    while (t--){
        cin >> n;
        cout << (f[n]*(n-1)%MOD)*n%MOD << '\n';
    }
    return 0;
}
```
  - **核心实现思想**：先预处理出 $1$ 到 $10^5$ 的阶乘存于数组 `f` 中，每次读入 $n$ 后，根据公式 `n*(n - 1)*n!` 利用预处理的阶乘计算答案并取模输出。
- **作者：ExplodingKonjac（4星）**
  - **关键亮点**：简洁地分析出结论，即所有排列的 beauty 一样，并从构造序列的两半部分分别分析逆序对贡献，逻辑清晰，代码使用了自定义的模运算类，具有一定拓展性。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
// 快读
using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;
template<int MOD>
class Modint
{
    // 类中实现了各种模运算操作
};
constexpr int MOD=1e9+7;
using Mint=Modint<MOD>;
int T,n;
int main()
{
    qin>>T;
    while(T--)
    {
        qin>>n;
        Mint ans=n;
        ans=ans*(ans-1)/2;
        for(int i=1;i<=n;i++) ans+=(n-i);
        for(int i=1;i<=n;i++) ans*=i;
        qout.writeln(ans());
    }
    return 0;
}
```
  - **核心实现思想**：通过自定义的 `Modint` 类进行模运算，在 `main` 函数中根据结论逐步计算答案，先计算 `n*(n - 1)/2`，再累加后半部分与前半部分产生的逆序对贡献，最后乘上 $n!$ 得到答案并输出。

### 最优关键思路或技巧
通过对小 $n$ 值的排列进行枚举，观察并总结出规律，即每个排列对应的逆序对数量固定。从排列和逆序对的基本概念出发，利用排列中顺序对和逆序对的总数关系，以及前后两部分序列之间的数字大小关系，进行数学推导得出固定的逆序对数量公式 $n(n - 1)$，从而避免了枚举所有排列来计算逆序对，大大优化了时间复杂度。

### 同类型题或类似算法套路
此类题目通常需要通过对小数据的分析找出规律，再从数学原理上进行证明或推导。对于涉及排列、组合和逆序对的问题，常考虑元素之间的相对位置关系以及整体的数量关系，通过数学方法简化计算。

### 推荐洛谷题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考察组合数学和快速幂运算，与本题类似，需要通过数学推导得出计算公式。
- [P2181 对角线](https://www.luogu.com.cn/problem/P2181)：通过找规律和数学推导来解决多边形对角线相关问题，思路与本题有相似之处。
- [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)：虽然是递推问题，但同样需要通过分析小数据找规律，确定递推关系，与本题找规律的思路类似。

### 个人心得摘录与总结
rainygame提到在考场上看漏关键条件，导致花费时间优化解法。这提醒在做题时要仔细阅读题目条件，避免因疏忽而浪费时间。同时，通过不断优化解法，从暴力到逐步发现规律，体现了在解题过程中深入思考和探索的重要性。 

---
处理用时：57.67秒