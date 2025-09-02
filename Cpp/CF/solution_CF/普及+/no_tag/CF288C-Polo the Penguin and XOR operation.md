# Polo the Penguin and XOR operation

## 题目描述

Little penguin Polo likes permutations. But most of all he likes permutations of integers from $ 0 $ to $ n $ , inclusive.

For permutation $ p=p_{0},p_{1},...,p_{n} $ , Polo has defined its beauty — number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/6024047c9c91de0156ffb9e5c8b6ac649d55fe1e.png).

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the operation of bitwise excluding "OR" to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in language C++ and Java it is represented as "^" and in Pascal — as "xor".

Help him find among all permutations of integers from $ 0 $ to $ n $ the permutation with the maximum beauty.

## 样例 #1

### 输入

```
4
```

### 输出

```
20
0 2 1 4 3
```

# 题解

## 作者：ztxtjz (赞：1)

## 【题意】
给定一个$n(1 <= n <= 10^6)$，求$(0 \otimes p0) + (1 \otimes p1) + (2 \otimes p2) +…… + (n \otimes pn)$ 的最大值，其中$p0$到$pn$为$0$到$n$中的数，且每个数只能用一次。
## 【思路】
根据异或的性质，$1\otimes1=0,1\otimes0=1,0\otimes0=0$，进行异或的两个数只需要能将所有位上的$0$全部变为$1$，就能够取到最大值。

$i$从$n$到$0$循环，$t=log2(i)+1$，$t$是$i$转换为二进制后的位数。

$k=(1<<t)-1$，$k$为$t$位二进制每位都是$1$的数。

$ans[i]=k \otimes i,ans[k \otimes i]=i$，$k \otimes i$与$i$每位上相反。

最大值即为$\sum\limits_{i=0}^nans[i]$，可以发现这个值与$n \cdot (n+1)$相等。

时间复杂度$O(n)$
## 【代码】
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans[1000005];
int main()
{
    scanf("%lld",&n);
    memset(ans,-1,sizeof(ans));
    for(int i=n;i>=0;i--)
    {
        if(ans[i]!=-1) continue;
        ll k=(1<<(ll)(log2(i)+1))-1;
        ans[k^i]=i,ans[i]=k^i;
    }
    printf("%lld\n",n*(n+1));
    for(int i=0;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：AC_love (赞：1)

首先可以对 $n$ 比较小的情况爆搜一下看看答案是多少，爆搜之后我们得到如下结果：

```
n = 1, ans = 2
n = 2, ans = 6
n = 3, ans = 12
n = 4, ans = 20
n = 5, ans = 30
……
```

不难发现答案应该是 $n(n + 1)$，然后我们思考如何构造这个答案。

我们希望得到的结果尽可能的大，那么我们肯定希望每一位都 $0 \oplus 1 = 1$。

所以我们只要让进行异或的两个数的二进制位上的 $0$ 和 $1$ 正好错开就行了。

我们发现其实这是很容易做到的，只要让一个数异或上一串 $1$ 就行了。

[点我查看代码](https://codeforces.com/contest/289/submission/233751123)

---

