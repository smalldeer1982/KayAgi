# 题目信息

# [ABC356D] Masked Popcount

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_d

整数 $ N,M $ が与えられるので、 $ \displaystyle\ \sum_{k=0}^{N} $ $ \rm{popcount} $$ (k\ \mathbin{\&amp;}\ M) $ を $ 998244353 $ で割った余りを求めてください。

ただし、 $ \mathbin{\&amp;} $ はビット単位 $ \rm{AND} $ 演算を表します。

 ビット単位 $ \rm{AND} $ 演算とは？ 非負整数 $ a $ と非負整数 $ b $ とのビット単位 $ \rm{AND} $ 演算の結果 $ x\ =\ a\ \mathbin{\&amp;}\ b $ は次のように定義されます。  
- $ x $ は全ての非負整数 $ k $ について以下の条件を満たすただ $ 1 $ つの非負整数である。
- $ a $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位と $ b $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位が共に $ 1 $ なら、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 1 $ である。
- そうでないとき、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 0 $ である。
 
 
 例えば $ 3=11_{(2)},\ 5=101_{(2)} $ なので、 $ 3\ \mathbin{\&amp;}\ 5\ =\ 1 $ となります。  $ \rm{popcount} $ とは？ $ \rm{popcount} $$ (x) $ は、 $ x $ を $ 2 $ 進法で書き下した際に登場する $ 1 $ の個数を表します。  
 例えば $ 13=1101_{(2)} $ なので、 $ \rm{popcount} $$ (13)\ =\ 3 $ となります。

## 说明/提示

### 制約

- $ N $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
- $ M $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
 
### Sample Explanation 1

\- $ \rm{popcount} $$ (0\mathbin{\&amp;}3)\ =\ 0 $ - $ \rm{popcount} $$ (1\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (2\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (3\mathbin{\&amp;}3)\ =\ 2 $ - $ \rm{popcount} $$ (4\mathbin{\&amp;}3)\ =\ 0 $ であり、これらの和は $ 4 $ です。

### Sample Explanation 2

$ N=0 $ である場合や $ M=0 $ である場合もあります。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1152921504606846975 1152921504606846975```

### 输出

```
499791890```

# AI分析结果

### 题目中文重写
## [ABC356D] 掩码汉明重量

### 题目描述
[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_d

给定整数 $N$ 和 $M$，请计算 $\displaystyle\ \sum_{k=0}^{N} $ $\rm{popcount}$ $(k\ \mathbin{\&}\ M)$ 除以 $998244353$ 的余数。

其中，$\mathbin{\&}$ 表示按位与运算。

#### 按位与运算说明
非负整数 $a$ 与非负整数 $b$ 的按位与运算结果 $x = a\ \mathbin{\&}\ b$ 定义如下：
- $x$ 是满足以下条件的唯一非负整数：对于所有非负整数 $k$，若 $a$ 写成二进制时 $2^k$ 位和 $b$ 写成二进制时 $2^k$ 位均为 $1$，则 $x$ 写成二进制时 $2^k$ 位为 $1$；否则，$x$ 写成二进制时 $2^k$ 位为 $0$。

例如，$3 = 11_{(2)}$，$5 = 101_{(2)}$，所以 $3\ \mathbin{\&}\ 5 = 1$。

#### $\rm{popcount}$ 函数说明
$\rm{popcount}(x)$ 表示 $x$ 写成二进制时出现的 $1$ 的个数。

例如，$13 = 1101_{(2)}$，所以 $\rm{popcount}(13) = 3$。

### 说明/提示
#### 限制条件
- $N$ 是 $0$ 以上 $2^{60}$ 以下的整数。
- $M$ 是 $0$ 以上 $2^{60}$ 以下的整数。

#### 示例解释 1
- $\rm{popcount}(0\mathbin{\&}3) = 0$
- $\rm{popcount}(1\mathbin{\&}3) = 1$
- $\rm{popcount}(2\mathbin{\&}3) = 1$
- $\rm{popcount}(3\mathbin{\&}3) = 2$
- $\rm{popcount}(4\mathbin{\&}3) = 0$
这些值的和为 $4$。

#### 示例解释 2
可能出现 $N = 0$ 或 $M = 0$ 的情况。

#### 示例解释 3
请务必注意计算除以 $998244353$ 的余数。

### 样例 #1
#### 输入
```
4 3
```
#### 输出
```
4
```

### 样例 #2
#### 输入
```
0 0
```
#### 输出
```
0
```

### 样例 #3
#### 输入
```
1152921504606846975 1152921504606846975
```
#### 输出
```
499791890
```

### 综合分析与结论
这些题解主要围绕计算 $\sum_{k = 0}^{N}\text{popcount}(k \& M) \bmod 998244353$ 展开。由于 $N$ 和 $M$ 的数据范围较大，直接暴力计算不可行，各题解普遍采用按位计算的思路，即对于 $M$ 二进制中为 $1$ 的位，计算 $0$ 到 $N$ 中该位为 $1$ 的数的个数，再将这些个数累加得到结果。

### 各题解评分与分析
- **LuukLuuk（5星）**
    - **关键亮点**：思路清晰，通过打表发现二进制位的循环规律，给出明确的数学公式计算每一位的贡献，代码简洁易懂。
    - **核心代码**：
```cpp
#include <cstdio>
using namespace std;
#define int long long

const int mod = 998244353;
int ans;
int n, m, x; 

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; m; ++i) {
        if (m & 1) {
            int j = (1ll << (i - 1));
            ans += (((n + 1) / (2 * j)) * j);
            ans %= mod;
            x = ((n + 1) % (2 * j) - j);
            if (x > 0) ans += x;
            ans %= mod;
        }
        m >>= 1;
    }
    printf("%lld", ans);
    return 0;
}
```
    - **核心实现思想**：遍历 $M$ 的二进制位，对于为 $1$ 的位，根据规律计算 $0$ 到 $N$ 中该位为 $1$ 的数的个数，分为完整循环部分和不完整循环部分分别计算。
- **Harrylzh（4星）**
    - **关键亮点**：同样利用二进制位的循环规律，使用 `lowbit` 函数枚举 $M$ 中为 $1$ 的位，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long lowbit(long long x)
{
    return x&(-x);
}
long long ans=0;
const long long P=998244353;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(long long i=m;i;i-=lowbit(i))//枚举是一的位置
    {
        long long lt=lowbit(i);
        long long cj=0;
        cj+=(n+1)/(2*lt)*lt%P;
        cj%=P;
        if((n+1)%(2*lt)>lt)cj+=(n+1)%(2*lt)-lt;//找规律计算
        cj%=P;
        ans+=cj;
        ans%=P;//记得取模
    }
    cout<<ans<<"\n";
}
```
    - **核心实现思想**：通过 `lowbit` 函数找到 $M$ 中为 $1$ 的位，然后根据规律计算该位的贡献，包括完整循环和不完整循环部分。
- **刘梓轩2010（4星）**
    - **关键亮点**：详细分析了每一位的贡献计算方法，将问题转化为计算 $[0, n]$ 中满足条件的数的个数，代码结构清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const int p=998244353;
int n,m;
int ans;
int fun(int i,int n)
{
    int p2=(1ll<<i);
    int k=n/(2*p2);
    int res=k*p2;
    int l=n%(2*p2);
    if(l>=p2) res+=(l-p2+1);
    return res%p;
}
signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=0;i<60;i++)
    {
        if((1ll<<i)&m) 
        {
            ans+=fun(i,n);
            ans%=p;
        }
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：定义 `fun` 函数计算某一位的贡献，对于 $M$ 中为 $1$ 的位，调用 `fun` 函数计算并累加结果。

### 最优关键思路或技巧
- **按位计算**：由于直接计算每个数的 $\text{popcount}$ 复杂度高，通过按位计算 $M$ 中为 $1$ 的位的贡献，将复杂度降低到 $O(\log n)$。
- **寻找规律**：观察二进制位的循环规律，将 $0$ 到 $N$ 中的数按位分组，分别计算完整循环和不完整循环部分的贡献。

### 拓展思路
同类型题目通常涉及位运算和数学规律的结合，例如计算某个范围内满足特定位条件的数的个数等。类似算法套路包括按位枚举、寻找循环规律、分情况讨论等。

### 推荐洛谷题目
- [P4317 花神的数论题](https://www.luogu.com.cn/problem/P4317)
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)（涉及区间动态规划和位运算思想）
- [P2150 [NOI2015] 寿司晚宴](https://www.luogu.com.cn/problem/P2150)（涉及状态压缩和位运算）

### 个人心得摘录与总结
- **LuukLuuk**：通过打表找到二进制位的循环规律，同时注意整数除法向下取整和取模运算，以及第二项小于 $0$ 时的处理。
- **Crazyouth**：注意到求和可以看成是 $1\sim n$ 的 $\text{popcount}$ 求和减去被 $m$ 消掉的部分，利用公式计算。 

---
处理用时：59.95秒