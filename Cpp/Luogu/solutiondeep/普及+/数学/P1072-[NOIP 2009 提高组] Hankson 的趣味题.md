# 题目信息

# [NOIP 2009 提高组] Hankson 的趣味题

## 题目描述

Hanks 博士是 BT（Bio-Tech，生物技术) 领域的知名专家，他的儿子名叫 Hankson。现在，刚刚放学回家的 Hankson 正在思考一个有趣的问题。

今天在课堂上，老师讲解了如何求两个正整数 $c_1$ 和 $c_2$ 的最大公约数和最小公倍数。现在 Hankson 认为自己已经熟练地掌握了这些知识，他开始思考一个“求公约数”和“求公倍数”之类问题的“逆问题”，这个问题是这样的：已知正整数 $a_0,a_1,b_0,b_1$，设某未知正整数 $x$ 满足：

1. $x$ 和 $a_0$ 的最大公约数是 $a_1$；

2. $x$ 和 $b_0$ 的最小公倍数是 $b_1$。

Hankson 的“逆问题”就是求出满足条件的正整数 $x$。但稍加思索之后，他发现这样的 $x$ 并不唯一，甚至可能不存在。因此他转而开始考虑如何求解满足条件的 $x$ 的个数。请你帮助他编程求解这个问题。


## 说明/提示

**【样例解释】**

第一组输入数据，$x$ 可以是 $9,18,36,72,144,288$，共有 $6$ 个。

第二组输入数据，$x$ 可以是 $48,1776$，共有 $2$ 个。

**【数据范围】**

- 对于 $50\%$ 的数据，保证有 $1\leq a_0,a_1,b_0,b_1 \leq 10000$ 且 $n \leq 100$。
- 对于 $100\%$ 的数据，保证有 $1 \leq a_0,a_1,b_0,b_1 \leq 2 \times 10^9$ 且 $n≤2000$。

NOIP 2009 提高组 第二题


## 样例 #1

### 输入

```
2 
41 1 96 288 
95 1 37 1776 ```

### 输出

```
6 
2```

# AI分析结果

### 综合分析与结论

本题的核心是通过给定的条件求解满足特定最大公约数和最小公倍数的正整数 \( x \) 的个数。大多数题解采用了枚举 \( b_1 \) 的因数并结合最大公约数和最小公倍数的性质进行判断。部分题解通过数学推导进一步优化了枚举的范围和条件判断，减少了不必要的计算。

### 所选高星题解

#### 1. **题解作者：KesdiaelKen**
- **星级：★★★★★**
- **关键亮点**：
  - 通过数学推导将问题转化为枚举 \( b_1 \) 的因数，并结合最大公约数和最小公倍数的性质进行判断。
  - 优化了枚举的范围，减少了计算量，复杂度为 \( O(\sqrt{b_1} \log b_1) \)。
  - 代码简洁且高效，逻辑清晰。
- **个人心得**：
  - 通过数学推导将问题简化，避免了暴力枚举的低效性。
  - 强调了特判的重要性，确保代码的鲁棒性。

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int ssqrt;
int cf(int a,int b){
    ssqrt=sqrt(b);
    for(int i=2;i<=ssqrt;i++){
        if(b%i==0)while(a%i==0)a/=i;
        while(b%i==0)b/=i;
    }
    if(b!=1)while(a%b==0)a/=b;
    return a;
}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main(){
    int a0,a1,b0,b1;
    int gs;
    int m,n,s,l,q;
    scanf("%d",&gs);
    int cnt;
    while(gs--){
        scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
        if(a0%a1|b1%b0|b1%a1){printf("0\n");continue;}
        m=a0/a1,n=b1/b0,s=b1/a1;l=cf(s,n);
        if(gcd(max(s/l,m),min(s/l,m))!=1){printf("0\n");continue;}
        q=cf(l,m);cnt=0,ssqrt=sqrt(q);
        for(int i=1;i<=ssqrt;i++)if(q%i==0)cnt+=i==q/i?1:2;
        printf("%d\n",cnt);
    }
    return 0;
}
```

#### 2. **题解作者：zzlzk**
- **星级：★★★★☆**
- **关键亮点**：
  - 通过枚举 \( b_1 \) 的因数并结合最大公约数和最小公倍数的性质进行判断。
  - 代码简洁，逻辑清晰，适合初学者理解。
- **个人心得**：
  - 强调了枚举因数的技巧，避免了暴力枚举的低效性。

```cpp
#include<cstdio>
using namespace std;
int gcd(int a,int b) {
    return b==0?a:gcd(b,a%b);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int a0,a1,b0,b1;
        scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
        int p=a0/a1,q=b1/b0,ans=0;
        for(int x=1;x*x<=b1;x++) 
            if(b1%x==0){
                if(x%a1==0&&gcd(x/a1,p)==1&&gcd(q,b1/x)==1) ans++;
                int y=b1/x;
                if(x==y) continue; 
                if(y%a1==0&&gcd(y/a1,p)==1&&gcd(q,b1/y)==1) ans++;
            }
        printf("%d\n",ans);
    }
    return 0;
}
```

#### 3. **题解作者：_std_O2**
- **星级：★★★★☆**
- **关键亮点**：
  - 通过枚举 \( b_1 \) 的因数并结合最大公约数和最小公倍数的性质进行判断。
  - 代码简洁，逻辑清晰，适合初学者理解。
- **个人心得**：
  - 强调了枚举因数的技巧，避免了暴力枚举的低效性。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1145;
int tot=0,ans=0;
int a0,a1,b0,b1,B1,a[N];
int top;
int lcm(int a,int b){
    return (a/__gcd(a,b)*b);
}
struct node{
    int val,num;
};
vector<node> pri;

bool check(int x){
    if(__gcd(x,a0)==a1 && lcm(x,b0)==b1)  return 1;
    return 0;
}

void dfs(int x,int sum){
    if(x==tot){
        if(check(sum))ans++;
        return; 
    }
    for(int i=0;i<=pri[x].num;i++)
        dfs(x+1, pow(pri[x].val,i)*sum);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        top=0;
        cin>>a0>>a1>>b0>>b1;
        B1=b1;
        pri.clear();
        memset(a,0,sizeof(a));
        for(int i=2;i<=sqrt(b1);i++){
            while(B1%i==0){
                B1/=i;
                a[++top]=i;
            }
        }
        if(B1!=1) a[++top]=B1;
        int res=0;
        for(int i=1;i<=top+1;i++){
            if(a[i]!=a[i-1]){
                pri.push_back({a[i-1],res});
                res=1,tot++;
            } 
            else res++;
        }
        tot = pri.size();
        if (tot == 0) tot = 1; 
        ans=0;
        dfs(1,1);
        cout<<ans<<endl;
    }
}
```

### 最优关键思路与技巧

1. **枚举因数的优化**：通过枚举 \( b_1 \) 的因数，并结合最大公约数和最小公倍数的性质进行判断，避免了暴力枚举的低效性。
2. **数学推导简化问题**：通过数学推导将问题转化为更简单的形式，减少计算量。
3. **特判的重要性**：在代码中加入特判，确保代码的鲁棒性和正确性。

### 可拓展之处

1. **类似算法套路**：在处理最大公约数和最小公倍数相关的问题时，可以通过枚举因数并结合数学性质进行优化。
2. **同类型题目**：可以尝试解决其他涉及最大公约数和最小公倍数的题目，如求解满足特定条件的整数个数等。

### 推荐题目

1. **P1072 [NOIP2009 提高组] Hankson 的趣味题**（本题）
2. **P1029 [NOIP2001 提高组] 最大公约数和最小公倍数问题**
3. **P1069 [NOIP2009 提高组] 细胞分裂**

### 个人心得总结

- **调试经历**：在编写代码时，特判的加入是非常重要的，可以避免很多边界情况下的错误。
- **踩坑教训**：在枚举因数时，需要注意因数的重复计算问题，避免重复计数。
- **顿悟感想**：通过数学推导将问题简化，可以大大提高代码的效率和可读性。

---
处理用时：49.04秒