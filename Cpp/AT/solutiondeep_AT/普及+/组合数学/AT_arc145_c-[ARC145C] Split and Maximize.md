# 题目信息

# [ARC145C] Split and Maximize

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_c

$ (1,2,\ldots,2N) $ の順列 $ P=(P_1,P_2,\ldots,P_{2N}) $ に対し、スコアを以下で定義します。

> $ P $ を順序を保ったまま二つの長さ $ N $ の（連続するとは限らない）部分列 $ A\ =\ (A_1,A_2,\ldots,A_N),B\ =\ (B_1,B_2,\ldots,B_N) $ に分割する。分割を行ったときに得られる $ \displaystyle\sum_{i=1}^{N}A_i\ B_i $ の最大値をスコアとする。

$ (1,2,\ldots,2N) $ の順列全てについてスコアを計算し、それらの最大値を $ M $ とします。 $ (1,2,\ldots,2N) $ の順列のうち、スコアが $ M $ であるものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

考えられる順列 $ 24 $ 通りの中で、スコアの最大値 $ M $ は $ 14 $ です。スコアが $ 14 $ となる順列は $ 16 $ 通りあります。 例えば、順列 $ (1,2,3,4) $ は $ A=(1,3),\ B=(2,4) $ と分割することで、$ \sum\ _{i=1}^{N}A_i\ B_i\ =\ 14 $ となります。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを答えてください。

## 样例 #1

### 输入

```
2```

### 输出

```
16```

## 样例 #2

### 输入

```
10000```

### 输出

```
391163238```

# AI分析结果

### 题目内容中文重写
# [ARC145C] 分割并最大化

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_c

对于排列 $P=(P_1,P_2,\ldots,P_{2N})$（它是 $(1,2,\ldots,2N)$ 的一个排列），按以下方式定义得分：

> 将 $P$ 保持顺序不变地分割成两个长度为 $N$ 的（不一定连续的）子序列 $A = (A_1,A_2,\ldots,A_N)$ 和 $B = (B_1,B_2,\ldots,B_N)$。将分割后得到的 $\displaystyle\sum_{i=1}^{N}A_i B_i$ 的最大值作为得分。

计算 $(1,2,\ldots,2N)$ 的所有排列的得分，并将这些得分中的最大值记为 $M$。请你求出 $(1,2,\ldots,2N)$ 的排列中得分等于 $M$ 的排列个数除以 $998244353$ 的余数。

## 说明/提示

### 限制条件

- $1 \leq N \leq 2\times 10^5$
- 输入均为整数

### 示例解释 1

在 $24$ 种可能的排列中，得分的最大值 $M$ 是 $14$。得分等于 $14$ 的排列有 $16$ 种。例如，对于排列 $(1,2,3,4)$，当分割为 $A=(1,3)$，$B=(2,4)$ 时，$\sum_{i=1}^{N}A_i B_i = 14$。

### 示例解释 2

请输出除以 $998244353$ 的余数。

## 样例 #1

### 输入
```
2
```

### 输出
```
16
```

## 样例 #2

### 输入
```
10000
```

### 输出
```
391163238
```

### 综合分析与结论
这些题解的核心思路都是先证明相邻两个数配对（即 $\forall |A_i - B_i| = 1$）时 $\sum_{i = 1}^{N}A_iB_i$ 能取得最大值，然后通过计数原理计算得分等于最大值的排列个数。具体来说，通过交换 $(A_i,B_i)$ 与 $(A_j,B_j)$ 、交换 $A_i$ 与 $B_i$ 得到部分方案数，再利用卡特兰数计算剩余的方案数，最后将各部分方案数相乘得到最终结果。

### 所选的题解
- **liangbowen（5星）**
    - **关键亮点**：思路清晰，先给出直观的证明说明相邻配对最优，然后详细阐述了计数的各个部分，包括交换对子、交换对中元素以及卡特兰数的应用，最后给出了代码链接。
- **hhhqx（4星）**
    - **关键亮点**：有代码实现，对思路的阐述较为详细，从题意分析入手，逐步推导出最终的答案表达式，并且对卡特兰数的应用有形象的解释。
- **liyixin0514（4星）**
    - **关键亮点**：将问题巧妙地转化为合法括号序列问题，通过卡特兰数计算方案数，思路简洁明了，代码实现也较为清晰。

### 重点代码
#### hhhqx 的代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL mod = 998244353;
const int MAXN= 4e5 + 3;

LL qpow(LL A, LL B){
    LL ret = 1;
    while(B > 0){
        if(B & 1) ret = ret * A % mod;
        A = A * A % mod, B >>= 1;
    }
    return ret;
}

LL fac[MAXN], ifac[MAXN];
int n, m;

LL C(int A, int B){ return fac[B] * ifac[A] % mod * ifac[B - A] % mod; }
LL Catalan(int A){ return (C(A, A + A) - C(A - 1, A + A) + mod) % mod; }

int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= 4e5; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = qpow(fac[i], mod - 2);
    cin >> n;
    cout << qpow(2, n) * fac[n] % mod * Catalan(n) % mod;
    return 0;
}
```
**核心实现思想**：先预处理阶乘和阶乘的逆元，然后通过快速幂计算幂次，利用组合数公式计算卡特兰数，最后根据公式 $2^n \times n! \times Catalan(n)$ 计算最终答案。

#### liyixin0514 的代码
```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
typedef long long ll;
const int N=2e5+3,mod=998244353;
int n;
ll jc(ll a){
    ll s=1;
    for(int i=1;i<=a;i++){
        s=s*i%mod;
    }
    return s;
}
ll ksm(ll a,ll b){
    ll s=1;
    while(b){
        if(b&1) s=s*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return s;
}
int main(){
    sf("%d",&n);
    pf("%lld\n",jc(2*n)*ksm(jc(n)*jc(n+1)%mod,mod-2)%mod*jc(n)%mod*ksm(2,n)%mod);
}
```
**核心实现思想**：定义了阶乘函数 `jc` 和快速幂函数 `ksm`，通过公式 $\dfrac{(2n)!}{(n + 1)!\times n!}\times n!\times 2^n$ 计算最终答案，其中使用快速幂计算逆元。

### 最优关键思路或技巧
- **配对策略**：通过数学推导证明相邻两个数配对能使 $\sum_{i = 1}^{N}A_iB_i$ 取得最大值，这是解决问题的关键。
- **卡特兰数的应用**：将问题转化为合法括号序列问题，利用卡特兰数计算满足条件的排列个数，简化了计数过程。

### 可拓展之处
同类型题或类似算法套路：
- 涉及排列组合的计数问题，如计算满足特定条件的排列或组合的个数。
- 利用卡特兰数解决的问题，如栈的进出序列、二叉树的形态数等。

### 推荐洛谷题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：经典的卡特兰数应用问题，与本题中利用卡特兰数计算合法括号序列个数的思路相似。
- [P3200 [HNOI2009]有趣的数列](https://www.luogu.com.cn/problem/P3200)：同样是利用卡特兰数解决计数问题的题目。
- [P1754 球迷购票问题](https://www.luogu.com.cn/problem/P1754)：也是卡特兰数的应用场景，通过卡特兰数计算满足条件的排列个数。

### 个人心得摘录与总结
- **hhhqx**：“蒟蒻第一次写卡特兰数的题解，如果有问题希望能被指正！” 总结：作者首次写卡特兰数相关题解，态度谦虚，希望得到指正。

---
处理用时：48.26秒