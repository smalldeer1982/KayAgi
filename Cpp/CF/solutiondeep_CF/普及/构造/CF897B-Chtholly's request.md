# 题目信息

# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100
```

### 输出

```
33
```

## 样例 #2

### 输入

```
5 30
```

### 输出

```
15
```

# AI分析结果

### 题目翻译
### 珂朵莉的请求

#### 题目描述
——非常感谢你今天的陪伴。
——我经历了那么多美好的事情。
——你给了我如梦般的回忆……但我现在不得不离开了……
——最后一个请求，你能……
——帮我解决一道Codeforces的题目吗？
——......
——什么？

珂朵莉已经为一道题想了好几天了：

如果一个数是回文数，并且它去掉前导零后的十进制表示长度为偶数，我们称它为zcy数。一个数是回文数意味着当用十进制表示时，它没有前导零，并且从前往后读和从后往前读是一样的。例如，12321和1221是回文数，而123和12451不是。此外，1221是zcy数，而12321不是。

给定整数 $k$ 和 $p$，计算最小的 $k$ 个zcy数的和，并输出这个和对 $p$ 取模的结果。

不幸的是， Willem 不擅长解决这类问题，所以他向你寻求帮助！

#### 说明/提示
在第一个样例中，最小的zcy数是11，第二小的zcy数是22。
在第二个样例中，[此处有图片但无法显示]。

#### 样例 #1
##### 输入
```
2 100
```
##### 输出
```
33
```

#### 样例 #2
##### 输入
```
5 30
```
##### 输出
```
15
```

### 综合分析与结论
这些题解的核心思路都是通过构造的方式生成zcy数。因为zcy数是长度为偶数的回文数，所以可以由一个整数和它的倒序数拼接而成。通过枚举整数 $i$ 从1到 $k$，构造出对应的zcy数并累加求和，最后对 $p$ 取模。

算法要点在于如何高效地构造zcy数和进行累加取模操作。难点在于处理数据范围，由于结果可能很大，需要使用 `long long` 类型来避免溢出。

### 所选题解
- **作者：chengni (赞：8)  ★★★★**
    - **关键亮点**：思路清晰，代码简洁，使用快速读入优化，详细解释了zcy数的构造原理。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    char ch=getchar();ll x=0,f=1;
    while(ch>'9' || ch<'0'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
    ll n=read(),p=read();
    ll sum=0;
    for(int i=1;i<=n;i++){
        ll tmp=i;
        int k=i;
        while(k){
            tmp=tmp*10+k%10;
            k/=10;
        }
        sum+=tmp;
        sum%=p;
    }
    cout<<sum;	
}
```
核心实现思想：通过快速读入获取 $n$ 和 $p$，然后枚举 $i$ 从1到 $n$，将 $i$ 与它的倒序数拼接成zcy数，累加到 $sum$ 中并取模。

- **作者：XL4453 (赞：3)  ★★★★**
    - **关键亮点**：简洁明了地阐述了构造zcy数的思路，代码结构清晰。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
long long n,MOD,ans,num,now;
int main(){
    scanf("%lld%lld",&n,&MOD);
    for(int i=1;i<=n;i++){
        num=i;
        now=i;
        while(now){
            num*=10;
            num+=now%10;
            now/=10;
        }
        ans=(ans+num%MOD)%MOD;
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：使用 `scanf` 读取 $n$ 和 $MOD$，枚举 $i$ 从1到 $n$，构造zcy数并累加到 $ans$ 中取模。

- **作者：Sai0511 (赞：3)  ★★★★**
    - **关键亮点**：不仅给出了满分做法，还提供了30分的暴力算法思路，对题目的理解和分析较为全面。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,i,j,k,t,p,i1,s,s1,s2;
namespace Fastio{  
    inline ll read(){
        ll x=0;char c=getchar();
        while(!isdigit(c)) c=getchar();
        while(isdigit(c)){x=x*10+c-48;c=getchar();}
        return x;
    }
    void write(ll x){   
        if(x/10>0) write(x/10);
        putchar(x%10+48);
        return;
    }
}
using namespace Fastio;
int main(){
    k=read();p=read();
    for(i=1;i<=k;i++){
        j=1;
        while(j<=i) j*=10;
        s=(i*j)%p;
        i1=i;s1=0;
        while(i1>0){
            ll shu=i1%10;
            s1=s1*10+shu;
            i1/=10;
        }
        s=(s+s1)%p;
        s2=(s2+s)%p;  
    }
    write(s2);
}
```
核心实现思想：使用快速读入和输出，枚举 $i$ 从1到 $k$，先计算 $i$ 乘以合适的10的幂，再加上 $i$ 的倒序数，累加到 $s2$ 中取模。

### 最优关键思路或技巧
- **构造法**：利用zcy数的特性，通过一个整数和它的倒序数拼接来构造zcy数，避免了暴力枚举所有数并判断是否为回文数的高复杂度。
- **取模运算**：在累加过程中不断取模，防止结果溢出。
- **快速读入**：使用快速读入优化输入效率。

### 可拓展之处
同类型题可以是求前 $k$ 个长度为奇数的回文数的和，或者求满足其他特定条件的回文数的和。类似算法套路是通过构造满足条件的数，然后进行累加和取模操作。

### 推荐题目
1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)（可结合回文数的特性进行拓展）
3. [P1015 [NOIP1999 普及组] 回文数](https://www.luogu.com.cn/problem/P1015)

### 个人心得摘录与总结
- **Sai0511**：提到这可能是最水的珂朵莉题，还给出了30分的暴力算法和满分做法，总结了不同做法的思路和复杂度。说明在解题时可以先从暴力算法入手，再逐步优化。
- **Eason_AC**：提醒代码要用C++14及以上的语言提交，否则会WA，强调了注意代码语言版本的重要性。 

---
处理用时：39.03秒