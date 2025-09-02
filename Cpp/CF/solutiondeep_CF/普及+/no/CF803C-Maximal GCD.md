# 题目信息

# Maximal GCD

## 题目描述

You are given positive integer number $ n $ . You should create such strictly increasing sequence of $ k $ positive numbers $ a_{1},a_{2},...,a_{k} $ , that their sum is equal to $ n $ and greatest common divisor is maximal.

Greatest common divisor of sequence is maximum of such numbers that every element of sequence is divisible by them.

If there is no possible sequence then output -1.

## 样例 #1

### 输入

```
6 3
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
8 2
```

### 输出

```
2 6
```

## 样例 #3

### 输入

```
5 3
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 最大公约数

## 题目描述
给定正整数 $n$ 。你需要创建一个长度为 $k$ 的严格递增正整数序列 $a_{1},a_{2},\cdots,a_{k}$ ，使得它们的和等于 $n$ ，并且最大公约数最大。

序列的最大公约数是指能整除序列中每个元素的最大数。

如果不存在这样的序列，则输出 -1 。

## 样例 #1
### 输入
```
6 3
```
### 输出
```
1 2 3
```

## 样例 #2
### 输入
```
8 2
```
### 输出
```
2 6
```

## 样例 #3
### 输入
```
5 3
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
所有题解的核心思路都是基于数学原理，利用序列和与最大公约数之间的关系来解题。关键在于认识到 $n$ 一定能被最大公约数整除，且满足一定的和的条件才能构造出合法序列。各题解的不同主要体现在判断条件的写法、枚举因数的方式以及对边界条件和精度问题的处理上。

### 所选的题解
- **作者：dz_ice (5星)**
    - **关键亮点**：思路清晰，不仅详细阐述了判断序列可构造的两个条件，还注意到不等式判断时可能出现的 long long 范围溢出问题，并给出了转换后的不等式写法，代码实现完整且注释详细。
    - **个人心得**：考试时因未处理好不等式判断中的范围溢出问题调试很久，强调了此细节的重要性。
    - **重点代码核心实现思想**：先预处理出 $n$ 的所有因子，从大到小枚举因子，通过转换后的不等式判断因子是否满足条件，若满足则按规则构造并输出序列。
    - **核心代码片段**：
```cpp
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,k,sqr,sum,sum1,sum2,yin[50003];
int main()
{
    cin>>n>>k;
    sqr=sqrt(n);
    if((2*n)/k<1+k)
    {
        cout<<-1;
        return 0;
    } 
    for(long long i=1; i<=sqr; i++)
        if(n%i==0)
        {
            sum1++,yin[sum1]=i;
            if(n/i!=i)
                sum1++,yin[sum1]=n/i;
        } 
    sort(yin+1,yin+sum1+1);
    for(long long i=sum1; i>=1; i--)
        if((2*n)/k>=yin[i]+k*yin[i])  
        {
            for(long long j=1; j<=k; j++)
                if(j!=k)
                {
                    cout<<j*yin[i]<<" ";
                    sum+=j*yin[i];
                }
                else
                    cout<<n-sum;
            return 0;
        }
    cout<<-1;
    return 0;
}
```
- **作者：Jμdge (4星)**
    - **关键亮点**：代码简洁，通过 $O(\sqrt n)$ 枚举 $n$ 的约数作为 $k$ 个数的最大公约数 $d$，利用移项将乘法改成除法避免精度问题，整体思路和实现较为清晰。
    - **个人心得**：因手抽把 % 打成 & 导致 WA，强调了编码时细心的重要性。
    - **重点代码核心实现思想**：先判断无解情况，然后枚举 $n$ 的约数，通过自定义函数判断约数能否作为最大公约数，找到最大的符合条件的约数后构造并输出序列。
    - **核心代码片段**：
```cpp
//by Judge
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=(a),I=(b)+1;i<I;++i)
#define ll long long
using namespace std;
char sr[1<<21],z[20];int CCF=-1,Z;
inline void cmax(ll& x,ll y){if(x<y)x=y;}
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr=' '){
    if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} ll n,k,ans=1;
inline bool ask(ll x){ return k+1<=x*2/k; }
int main(){ cin>>n>>k;
    if(k+1>n*2/k) return!printf("-1\n");
    if(k==1) return!printf("%I64d\n",n);
    fp(i,2,sqrt(n)) if(!(n%i)){
        if(ask(n/i)) cmax(ans,i);
        if(ask(i)) cmax(ans,n/i);
    }
    fp(i,1,k-1) print(ans*i),n-=ans*i;
    return print(n,'\n'),Ot(),0;
}
```
- **作者：zhfaz123 (4星)**
    - **关键亮点**：利用二分查找在 $n$ 的因数中寻找最大的满足要求的因数，通过等差数列求和公式构造和最小的单调序列来判断因数是否符合条件，思路有一定独特性。
    - **重点代码核心实现思想**：先求出 $n$ 的所有因数，通过自定义函数判断因数能否构成满足要求的序列，利用二分查找确定最大的符合条件的因数，最后构造并输出序列。
    - **核心代码片段**：
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<stack>
#include<algorithm>
#include<queue>
#include<deque>
#include<cstring>
#include<string>
#include<set>
#include<utility>
#include<set>
#include<map>
#include<climits>
#include<unordered_set>
#include<unordered_map>
#include<bitset>
constexpr int N=1e5,M=1e4;
using namespace std;
long long n,m,k;
vector<long long> vc;
void inline init()
{
    vc.reserve(55);
    vector<long long> tp;
    tp.reserve(55);
    for(long long i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            vc.push_back(i);
            tp.push_back(n/i);
        }
    }
    for(auto i=(tp.rbegin());i!=tp.rend();i++)
    {
        vc.push_back(*i);
    }
}
bool inline check(const long long& v)
{
    return ((k*(k+1))/2)*v<=n;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    if(k*(k+1)/2>n||k>=1e6) cout<<"-1",exit(0);
    init();
    int l=0,r=vc.size()-1;
    while(l<r)
    {
        int mid=(l+r+1)>>1;
        if(check(vc[mid]))
        {
            l=mid;
        }
        else
        {
            r=mid-1;
        }
    }
    long long sum=0;
    for(long long i=1;i<k;i++) cout<<i*vc[r]<<" ",sum+=i*vc[r];
    cout<<n-sum;
    return 0;
}
```

### 最优关键思路或技巧
1. **数学关系推导**：利用序列和与最大公约数的整除关系，以及严格递增序列和的最小值（通过等差数列求和公式得到）来确定最大公约数的可能取值范围。
2. **避免精度问题**：在判断条件时，通过移项等方式将可能导致 long long 溢出的乘法运算转换为除法运算，保证计算的正确性。
3. **枚举与查找策略**：采用 $O(\sqrt n)$ 枚举 $n$ 的因数，或结合二分查找在因数中找到最大的满足条件的最大公约数，提高算法效率。

### 拓展与举一反三
同类型题目通常围绕数论中的整除、最大公约数、等差数列等知识点，结合序列构造的条件来设计。类似算法套路是先通过数学分析找出关键的限制条件和关系，再利用枚举、二分等方法在满足条件的范围内寻找最优解。

### 洛谷推荐题目
1. **P1072 [NOIP2009 普及组] Hankson 的趣味题**：同样涉及数论中最大公约数和最小公倍数的知识，通过枚举和判断来求解满足特定条件的数。
2. **P2613 【模板】有理数取余**：需要运用数论中的逆元知识，结合取模运算来解决有理数取余问题，对数论知识的运用有一定要求。
3. **P1572 计算分数**：考查分数运算以及数论中的约分、最大公约数等知识，通过模拟分数的运算过程来解题。 

---
处理用时：72.67秒