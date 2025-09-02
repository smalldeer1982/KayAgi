# 题目信息

# Marin and Anti-coprime Permutation

## 题目描述

Marin wants you to count number of permutations that are beautiful. A beautiful permutation of length $ n $ is a permutation that has the following property: $ $$$ \gcd (1 \cdot p_1, \, 2 \cdot p_2, \, \dots, \, n \cdot p_n) > 1,  $ $  where  $ \\gcd $  is the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a>.</p><p>A permutation is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array) and  $ \[1,3, 4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4$$$ in the array).

## 说明/提示

In first test case, we only have one permutation which is $ [1] $ but it is not beautiful because $ \gcd(1 \cdot 1) = 1 $ .

In second test case, we only have one beautiful permutation which is $ [2, 1] $ because $ \gcd(1 \cdot 2, 2 \cdot 1) = 2 $ .

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
1000```

### 输出

```
0
1
0
4
0
36
665702330```

# AI分析结果

### 题目内容
# Marin和互质排列

## 题目描述
Marin希望你统计出美丽排列的数量。一个长度为 $n$ 的美丽排列是具有以下性质的排列：
$$ \gcd (1 \cdot p_1, \, 2 \cdot p_2, \, \dots, \, n \cdot p_n) > 1,  $$ 
其中 $\gcd$ 是[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

一个排列是由从 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$ \[2,3,1,5,4\]$ 是一个排列，但 $ \[1,2,2\]$ 不是排列（数组中 $2$ 出现两次），$ \[1,3, 4\]$ 也不是排列（$n = 3$ 但数组中有 $4$）。

## 说明/提示
在第一个测试用例中，我们只有一个排列 $ [1] $，但它不美丽，因为 $\gcd(1 \cdot 1) = 1$ 。

在第二个测试用例中，我们只有一个美丽排列 $ [2, 1] $，因为 $\gcd(1 \cdot 2, 2 \cdot 1) = 2$ 。

## 样例 #1
### 输入
```
7
1
2
3
4
5
6
1000
```
### 输出
```
0
1
0
4
0
36
665702330
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕对题目中最大公约数条件的数学分析展开。多数题解先证明了 $\gcd(1 \cdot p_1,2 \cdot p_2,\cdots,n \cdot p_n)\leq2$ ，原因是在 $1$ 到 $n$ 以及排列 $p$ 中，$a$（$a > 2$）的倍数个数有限，使得满足 $a$ 整除所有 $i \cdot p_i$ 的情况不存在。然后分奇偶讨论：当 $n$ 为奇数时，必然存在 $i \cdot p_i$ 是奇乘偶的形式，导致 $\gcd$ 为 $1$，无解；当 $n$ 为偶数时，让奇数与偶数交叉相乘可使所有 $i \cdot p_i$ 为偶数，答案为 $((n/2)!)^2$ 。各题解思路本质相同，差异主要在证明过程的详细程度和代码实现的简洁性上。

### 所选的题解
- **作者：Jerrlee✅ (4星)**
  - **关键亮点**：思路清晰简洁，直接从奇偶性角度分类讨论，快速得出结论。先判断 $n$ 的奇偶性，奇数时直接输出 $0$；偶数时通过简单循环计算 $((n/2)!)^2$ 。
  - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        long long n,ans=1;
        cin>>n;
        if(n%2){cout<<"0\n";continue;}
        for(int i=2;i<=n/2;i++){
            ans*=i*i;
            ans%=998244353;
        }
        cout<<ans<<endl;
    }
}
```
  - **核心思想**：先判断输入的 $n$ 是否为奇数，若是则直接输出 $0$。若 $n$ 为偶数，通过循环累乘 $i \times i$（$i$ 从 $2$ 到 $n/2$），计算 $((n/2)!)^2$ 并取模输出。
- **作者：JS_TZ_ZHR (4星)**
  - **关键亮点**：从质数 $p$ 的倍数角度深入分析，得出 $\gcd$ 只能为 $2$ 且 $n$ 为偶数的结论，逻辑严谨。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
#define mod 998244353
using namespace std;
int T,n,ans=1,a[N],gcd;

signed main() {
    cin>>T;
    while(T--){
        cin>>n;
        if(n&1)cout<<0<<endl;
        else {
            for(int i=2;i<=n;i+=2){
                int tmp=i/2;
                ans=(ans*tmp)%mod;
                ans=(ans*tmp)%mod;
            }
            cout<<ans<<endl;
            ans=1;
        }
    }
}
```
  - **核心思想**：先读入测试用例数 $T$ ，对每个 $n$ ，判断奇偶性，奇数输出 $0$ 。偶数时，通过循环以步长 $2$ 遍历，每次循环计算 $((i/2)\times(i/2))$ 并累乘取模，计算 $((n/2)!)^2$ 。
- **作者：IvanZhang2009 (4星)**
  - **关键亮点**：通过设 $\gcd = g$ ，从倍数关系角度详细推导得出只有 $g = 2$ 且 $2|n$ 时才有解，推导过程清晰。
  - **核心代码**：
```cpp
int t;
cin>>t;
while(t--){
    int x;
    cin>>x;
    if(x%2){
        cout<<0<<endl;
    }
    else{
        long long ans=1;
        for(int i=1;i<=x/2;i++)
            ans=(ans*i*i)%998244353;
        cout<<ans<<endl;
    }
}
```
  - **核心思想**：读入测试用例数 $t$ ，对每个输入的 $x$ ，判断奇偶性，奇数输出 $0$ 。偶数时，通过循环累乘 $i \times i$（$i$ 从 $1$ 到 $x/2$），计算 $((x/2)!)^2$ 并取模输出。

### 最优关键思路或技巧
通过对 $\gcd$ 性质及排列中数的倍数关系进行数学分析，快速得出问题无解或有解的条件，并利用排列组合知识计算有解情况下的方案数。这种从数学原理出发分析问题的思维方式是解决此类问题的关键。

### 可拓展之处
同类型题常围绕数论相关的性质，如最大公约数、最小公倍数、质数合数等，结合排列组合知识进行考察。类似算法套路是先对给定条件进行数学推导，分析出关键的限制条件，再根据这些条件进行分类讨论和计算。

### 推荐洛谷题目
- **P1072 [NOIP2009 普及组] Hankson 的趣味题**：通过对最大公约数和最小公倍数的性质分析，求解满足特定条件的数的个数，与本题类似地考察数论知识。
- **P2152 [SDOI2009] SuperGCD**：高精度计算两个数的最大公约数，涉及高精度运算和数论知识，加深对最大公约数计算的理解。
- **P2613 【模板】有理数取余**：结合数论中的逆元知识解决有理数取模问题，锻炼对数论知识在不同场景下的应用能力。 

---
处理用时：66.50秒