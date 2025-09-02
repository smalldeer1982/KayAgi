# Gambling Nim

## 题目描述

As you know, the game of "Nim" is played with $ n $ piles of stones, where the $ i $ -th pile initially contains $ a_{i} $ stones. Two players alternate the turns. During a turn a player picks any non-empty pile and removes any positive number of stones from it. The one who is not able to make a move loses the game.

Petya and Vasya are tired of playing Nim, so they invented their own version of the game and named it the "Gambling Nim". They have $ n $ two-sided cards, one side of the $ i $ -th card has number $ a_{i} $ written on it, while the other side has number $ b_{i} $ . At the beginning of the game the players put all the cards on the table, each card only one of its sides up, and this side is chosen independently and uniformly. Thus they obtain a sequence $ c_{1},c_{2},...,c_{n} $ , where $ c_{i} $ is equal to $ a_{i} $ or $ b_{i} $ . Then they take $ n $ piles of stones, with $ i $ -th pile containing exactly $ c_{i} $ stones and play Nim. Petya takes the first turn.

Given that both players play optimally, find the probability of Petya's victory. Output the answer as an irreducible fraction.

## 样例 #1

### 输入

```
2
1 1
1 1
```

### 输出

```
0/1
```

## 样例 #2

### 输入

```
2
1 2
1 2
```

### 输出

```
1/2
```

## 样例 #3

### 输入

```
3
0 4
1 5
2 3
```

### 输出

```
1/1
```

# 题解

## 作者：Miracle_1024 (赞：2)

### 思路：
判断先手必胜即判断所有数异或值是否为 $0$。   

直接判断的话不大好实心，那就换一种思路，不妨先强制所有数选 $a$，然后再看有几种方案使得选一些 $b$ 让序列异或值为 $0$。   

假如想让位置 $i$ 从 $a\to b$，要异或上 $a_i \oplus  b_i$。

那么，就先求出所有 $a_i$ 的异或和 $sum$，然后将 $a_i \oplus  b_i$ 扔到线性基里，看看有几种方案使得线性基里异或和等于 $sum$。            

根据线性基的相关定理，每种异或和出现次数都是相同，所有输出 $ (2^s-1)/2^s$
即可。

### 代码：
```
#include <cstdio>
#include <algorithm>  
#define N 64  
#define ll long long
#define setIO(s) freopen(s".in","r",stdin)  
using namespace std;
ll p[63];      
int cnt=0;
int ins(ll x) { 
    for(int i=62;i>=0;--i) { 
        if(x&(1ll<<i)) {  
            if(p[i])
                x^=p[i];   
            else { 
                p[i]=x;  
                ++cnt; 
                return 1;
            }
        }    
    } 
    return 0;
}
int main() { 
    // setIO("input");
    int n; 
    scanf("%d",&n); 
    ll sum=0;
    for(int i=1;i<=n;++i) { 
        ll a,b;    
        scanf("%lld%lld",&a,&b);
        sum^=a; 
        ins(a^b);
    }  
    if(ins(sum)) printf("1/1\n");  
    else {
        printf("%lld/%lld\n",(1ll<<cnt)-1,1ll<<cnt);    
    }
    return 0;
}
```


---

## 作者：wcyQwQ (赞：1)

一个挺巧妙的转化。

假设我们这次随机到了 $a_{p_1}, \ldots, a_{p_m}$ 和 $b_{p_{m + 1}}, \ldots, b_{p_n}$，那么根据 Nim 游戏的结论，先手必败当且仅当
$$
a_{p_1} \oplus \cdots \oplus a_{p_m} \oplus b_{p_{m + 1}} \oplus \cdots b_{p_n} = 0
$$
这个式子变化的量太多了，不是很好处理，所以我们考虑左右两边同时异或上 $\oplus_{i = 1}^n a_i$，这样式子就变为
$$
(b_{p_{m + 1}} \oplus a_{p_{m + 1}}) \oplus \cdots \oplus (b_{p_n} \oplus a_{p_n}) = \oplus_{i = 1}^n a_i
$$
我们记 $A = \oplus_{i = 1}^n a_i$，$S = \{a_i \oplus b_i\}$，这样我们的问题就变为了从 $S$ 中选一个子集异或和为 $A$ 的概率。

显然把线性基搞出来，记线性基大小为 $sz$，那么如果 $A$ 不能被表示出来，概率显然为 $1$，如果 $A$ 能被表示出来，概率为 $1 - \dfrac{2^{n - sz}}{2^n} = \dfrac{2^{sz} - 1}{2^{sz}}$。

时间复杂度 $O(n\log V)$。[Code](https://codeforces.com/contest/662/submission/206617173)

---

## 作者：foreverlasting (赞：1)

[专业推销博客](https://foreverlasting1202.github.io/)

线性基。
<!--more-->

挺简单的一道题。$sum$表示所有$a_i$的异或和，$c_i=a_i$^$b_i$，然后考虑$NIM$游戏，那么就是求$c$的子集中有多少个异或和等于$sum$。

这个东西是基本思路了，考虑高斯消元异或方程组，前后解不变的原理。于是就只用求出这个向量空间自由元的个数就可以了。异或方程自由元的个数显然用线性基就做完了，非常简单是不是。

code:
```cpp
//2019.3.22 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-10
#define RG register
inline int read() {
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _abs(const res &x) {
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
const int N=5e5+10;
namespace MAIN {
    int n;
    LL a[N],b[N],ret;
    struct LB{
        int cnt;
        LL p[100+10];
        inline bool insert(RG LL x){
            for(res i=1;i<=cnt+1;i++)x=min(x,p[i]^x);
            if(x){p[++cnt]=x;return 1;}
            return 0;
        }
    }A;
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++)scanf("%lld%lld",&a[i],&b[i]),A.insert(a[i]^b[i]),ret^=a[i];
        if(A.insert(ret))printf("%d/%d\n",1,1);
        else printf("%lld/%lld\n",(1LL<<A.cnt)-1,1LL<<A.cnt);
    }
}
int main() {
//    freopen("graph.in","r",stdin);
//    freopen("graph.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：_ChongYun_ (赞：0)

### Solution



由 $\mathrm{Nim}$ 游戏结论，对于一种情况先手必败，当且仅当：

$$\bigg(\bigoplus_{i=1}^k a_{\mathrm{pos}_i}\bigg) \oplus \bigg( \bigoplus_{i=k+1}^{n} b_{\mathrm{pos}_i }\bigg)=0$$

其中 $k$ 表示选择正面的数量，$\mathrm{pos}_i$ 表示选择的位置。

该条件中的位置以及选择方案都是不确定的。考虑将等式两边同时异或 $\bigoplus_{i=1}^n a_i$。

$$\bigg(\bigoplus_{i=k+1}^{n} a_{\mathrm{pos}_i } \oplus b_{\mathrm{pos}_i }\bigg)=\bigoplus_{i=1}^n a_i$$

令 $c_i=a_i \oplus b_i$。于是问题转化成了选出若干个位置 $\mathrm{pos}_i$ 使得这些位置的 $c_i$ 的异或和为 $\bigoplus_{i=1}^n a_i$。

考虑将所有的 $c_i$ 丢进线性基。若无法表示 $\bigoplus_{i=1}^n a_i$，先手必胜的概率为 $1$。否则令 $\mathrm{siz}$ 表示线性基的大小，先手必胜的概率为 $1-\frac{2^{n-\mathrm{siz}}}{2^{n}}=\frac{2^{\mathrm{siz}}-1}{2^{\mathrm{siz}}}$。

### Code


```cpp
/* ChongYun */
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n,sum=0;
struct Node{
    int p[63],siz=0;
    int size(){ return siz; }
    int insert(int x){
        for(int i=62;i>=0;i--){
            if(!(x>>i)) continue;
            if(!p[i]){
                p[i]=x;
                ++siz;
                return 1;
            }
            x^=p[i];
        }
        return 0;
    }
}S;
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        int a=read(),b=read();
        sum^=a,S.insert(a^b);
    }
    if(S.insert(sum)) printf("1/1\n");
    else printf("%lld/%lld\n",(1ll<<S.size())-1,(1ll<<S.size()));
    return 0;
}
```

---

## 作者：wyyqwq (赞：0)

$Nim$ 游戏的结论是先手必败当且仅当 $c1 \oplus c2 \oplus c3 \oplus ... \oplus cn  = 0$。

令 $c_i = a_i \oplus b_i$，$sum$ 为 $a$ 数组的异或和，不难转化得就是要求解 $c$ 有多少个子集异或起来等于 $sum$。我们把 $a_i \oplus b_i$ 插入线性基里，再在最后把 $sum$ 插入，若能成功插入，根据线性基的性质说明不可能有异或起来等于 $sum$，即先手必胜。若不能成功插入，根据线性基的又一性质，若能插入线性基的个数为 $k$ 个，总共 $n$ 个，那么每种异或的方案是 $2 ^ {n - k}$，因此先手必赢的概率为 $\frac{2 ^ {n - k}}{2 ^ n}$，化简得 $1 - \frac{1}{2^k}$，或表示为 $\frac{2^k - 1}{2^k}$。

 

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 7;
ll p[N];
int k;
bool insert(ll x) {
    for(int i = 62; i >= 0; i --) {
        if(x & (1ll << i)) {
            if(p[i]) x ^= p[i];
            else {
                p[i] = x;
                k ++;
                return 1;
            }
        }
    }
    return 0;
}

signed main() {
    ll aa = 0;
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        aa ^= a;
        insert(a ^ b);
        
    }
    if(insert(aa)) printf("1/1\n");
    else printf("%lld/%lld\n", (1ll << k) - 1, (1ll << k));
    return 0;
}




```

---

