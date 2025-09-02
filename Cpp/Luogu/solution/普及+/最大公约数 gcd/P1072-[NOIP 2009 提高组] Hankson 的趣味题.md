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

# 题解

## 作者：zzlzk (赞：482)

- LaTex写公式有点麻烦，所以我用以前写好的代替了

- 想看原版可以戳[这里](http://blog.csdn.net/nuclearsubmarines/article/details/77603154)

- 首先来分析一下这个题目



![](https://i.loli.net/2017/08/26/59a16f6ad2018.png)

证明:



![](https://i.loli.net/2017/08/26/59a16fb56c248.png)

- 把上面的结论推广一下，得到结论$P$


>对于两个正整数$a,b$，设$gcd(a,b)=k$，则存在$gcd(a/k,b/k)=1$

- 应用结论$P$



![](https://i.loli.net/2017/08/26/59a170dc98ec0.png)

- 整理一下式子



![](https://i.loli.net/2017/08/26/59a1711685e4f.png)

用心体会这两个式子，你会发现$x$是$a_1$的整数倍而且是$b_1$的因子


~~好像这个由gcd和lcm也可以得到？~~嗯，就这样


于是得到一种解题思路


>$\sqrt b_1$枚举$b_1$的因子(也就是$x$)，如果这个数是$a_1$的整数倍并且满足那两个式子，则$ans++$

- code

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
                int y=b1/x;//得到另一个因子
                if(x==y) continue; 
                if(y%a1==0&&gcd(y/a1,p)==1&&gcd(q,b1/y)==1) ans++;
            }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：KesdiaelKen (赞：105)

这道题其实有一个优化算法，可以跑得更快。

并且，因为下面的题解似乎都没有很好地讲解这道题的思路，因此本人将详细地演示一下这道题的推算过程：

首先，我们知道这两个等式：$(a0,x)=a1,[b0,x]=b1$

于是，我们可以设：$x=a1*p,b1=x*t$

于是有：$a1*p*t=b1$

所以我们令：$b1/a1=s$

则：$p*t=s$

即：$t=s/p$

又由最大公约数与最小公倍数的定义与性质可得：

$(a0/a1,p)=1,(b1/b0,t)=1$

所以我们令：$a0/a1=m,b1/b0=n$

则有：$(p,m)=1,(s/p,n)=1$

这就是第一个结论，我们称其为结论一。事实上，我们其实已经可以由结论一整理出可以AC的方法，即用sqrt(s)的复杂度枚举s的因数，然后将每个因数放到结论一中，看看是否成立，再统计所有符合结论一的因数的个数，然后输出即可。这种算法的复杂度是：O(sqrt(s)\*log(s)\*n)。这样其实也能卡过数据，但是还是没有达到理论上的通过。所以我们还要继续优化。

我们考虑(s/p,n)=1。如果s/p与n有相同质因数，则意思那个无法使(s/p,n)=1成立。于是，我们可以将s与n所有相同的质因数从s中去掉，得到剩余的数l（这一点还是很需要技巧的，在程序中会有解析）。于是，s/p就必须是l的约数。

我们继续考虑(p,m)=1。因为s/p是l的约数，那么p就一定可以表示为这样的形式：

$p=(s/l)*r$

即：p一定是s/l的倍数（因为s/p是l的约数）。而r也必须是l的约数。于是就又有：

$r|l,(r,m)=1$

这就是第二个结论，我们称其为结论二。而解决结论二的方法便很明显了。我们可以用与解决结论一相似的方法，将l与m所有相同的质因数从l中去掉，得到剩余的数q。那么这样，所有符合条件的r都是q的因数了。然后，我们可以用sqrt(q)的复杂度枚举q的所有因数，输出q的因数个数就行了。这样，复杂度便降到了：O((sqrt(s)+log(s))\*n)，从理论来说也不会超时了。

还有一点需要注意，那就是特判没有符合要求的x的情况。这种情况出现只有四种可能：

###1、s不为整数

###2、m不为整数

###3、n不为整数

###4、(s/l,m)≠1，即因为p是s/l的倍数，所以无论r取何值，都会有(p,m)≠1

加上这四个特判，这道题便做完了。

总结一下，这道题，代码虽不长，但是思路需要很精细，也难想到，是一道不错的题。

下为代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int ssqrt;
int cf(int a,int b)//去掉a中与b共有的质因数。思想：将b质因数分解，同时将a中与b共有的质因数去掉。
{
    ssqrt=sqrt(b);
    for(int i=2;i<=ssqrt;i++)//sqrt(b)复杂度质因数分解b
    {
        if(b%i==0)while(a%i==0)a/=i;//去掉a中与b共有的质因数，将a分解
        while(b%i==0)b/=i;//将b质因数分解
    }
    if(b!=1)while(a%b==0)a/=b;//注意：此时b可能还不是1，因为b可能有比sqrt(b)更大的质因数，但至多只有一个，且它的次幂至多是1。所以如果b不是1，那就只能是一个质数。于是此时继续分解a。
    return a;//返回剩下的a
}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}//辗转相除求最大公约数
int main()
{
    int a0,a1,b0,b1;
    int gs;
    int m,n,s,l,q;
    scanf("%d",&gs);
    int cnt;
    while(gs--)
    {
        scanf("%d%d%d%d",&a0,&a1,&b0,&b1);
        if(a0%a1|b1%b0|b1%a1){printf("0\n");continue;}//如果m、n、s中有小数，则直接输出0。这里的代码用到了一些位运算
        m=a0/a1,n=b1/b0,s=b1/a1;l=cf(s,n);//求出m、n、s，然后求出l
        if(gcd(max(s/l,m),min(s/l,m))!=1){printf("0\n");continue;}//如果不互质，则直接输出0
        q=cf(l,m);cnt=0,ssqrt=sqrt(q);//求出q，开始枚举q的因数，求出q的因数个数
        for(int i=1;i<=ssqrt;i++)if(q%i==0)cnt+=i==q/i?1:2;//这里注意，如果i==q/i，则只加1，否则加2
        printf("%d\n",cnt);//输出
    }
    return 0;
}
```

---

## 作者：皎月半洒花 (赞：63)

没错我不是来宣传正解的，我是来说一种毒瘤解法的 $233$。

哦哦，如果你不想看讲基本做法。你可以向下翻$233$。

嗯，其实遇到这种单纯的$gcd  \ \ or \ \  lcm$的题，我们都可以用一种比较简单的方法分析：唯一分解定理。

嗯，是整数域的唯一分解，不是多项式域的唯一分解。

那么其实其他的大佬已经解释得很清楚了，关于这种解法，大部分来讲都是先筛出数据范围上限$\sqrt n$即可。但是有个$Bug$就是对于每个合数$k$，都最多有一个质因子是大于$\sqrt k$的由于数据范围过大窝萌没法直接筛，而我正是解决了这个问题（虽然有点慢$233$）.

我们思考对于$a_0$和$a_1$而言，假设$gcd(x,a_0)=a_1$

那么我们会有比较浅显的结论：若

$$
a_0=\prod\limits_{i=1}^{m}p_i^{c_i}~~,~~x=\prod\limits_{i=1}^{n}p_i^{d_i}
$$

那么
$$
a_1=\prod\limits_{i=1}^{max(m,n)}p_i^{min(c_i,d_i)}
$$
那我们反着考虑，对于他们的 $gcd$——$a_1$ 里的 $p_i$ 来讲，要么是$a_0$中的，要么是$x$中的。换句话说，如果$c_i = min(c_i,d_i)$，那么$d_i$只需要$\geq~c_i$即可，也就是说$d_i$可以在区间 $[c_i,\infty)$ 上随便取，我们现在称这个$x$为**自由未知数（$free\ \ uknown -number$）**，称这个区间为**自由区间（$free\ \ ranges$）**。

而如果不一样，就只可能是 $c_i>min(d_i,c_i)$，此时没有任何取法，只有可能是 $d_i=min(d_i,c_i)$，所以就只能有一种选法，我们现在称这个$x$为**非自由未知数（$unfree\ \ uknown-number$）**。

同理，$lcm$那部分也一样。

但是这个地方需要注意的是，我们需要考虑$2^2$种不同情况：

$1$、两个方程的$x$均非自由，那么如果不同的话就会无解。

$2 \&3$、$gcd$或者$lcm$中有一个非自由，我们需要判断这个非自由的解是否是在另一个的自由区间内，不在就是不合法。

$4$、都是自由的，那么就做个差留到最后乘法原理。


代码大概长这样：

```cpp
inline void Linearity(){
    T = qr() ;
    Chk[1] = Chk[0] = 1 ;
    for (i = 2 ; i <= MAX ; ++ i){
        if (!Chk[i]) P[++ P[0]] = i ;
        for (j = 1; j <= P[0] && i * P[j] <= MAX ; ++ j){
            Chk[i * P[j]] = 1 ;
            if (i % P[j] == 0) break ;
        }
    }
}
inline void work(int ST, int ED){
    for(i = ST; i <= ED ; ++ i){
        N1 = N2 = N3 = N4 = 0 ;
        while (!(A0 % P[i])) A0 /= P[i], ++ N1 ;
        while (!(A1 % P[i])) A1 /= P[i], ++ N2 ;
        while (!(B0 % P[i])) B0 /= P[i], ++ N3 ;
        while (!(B1 % P[i])) B1 /= P[i], ++ N4 ;
 		if (N1 > N2 && N3 < N4){
            if (N2 == N4) A[i] = B[i] = 1 ;
            else {mark = 0; break ;}
            continue ;
        }
        if (N1 > N2){
            if (N4 >= N2) A[i] = B[i] = N2 ;
            else {mark = 0; break ;}
            continue ;
        }
        if (N3 < N4){
            if (N4 >= N2) A[i] = B[i] = N3 ;
            else {mark = 0; break ;}
            continue ;
        }
        else {
            if (N4 >= N2) A[i] = N2, B[i] = N4 ;
            else {mark = 0; break ;}
        }
    }
}
```

那么接下来的问题就是该怎么确定最后一个质因子。有一个很显然的做法是由于是最后一个质因子，所以我们只需要判断一下分解完质因数每一个是不是$1$即可，不是$1$的话，那就肯定是未筛到的，我们直接让他加入$prime$数组即可。哦，对，还需要再筛一遍，详情看代码即可。

```cpp
#include <cstdio>
#include <bitset>
#include <iostream>
#define MAX 45000
#define ll long long

using namespace std ;
bitset <MAX> Chk ; int A0, A1, B0, B1 ;
int Ans, T, i, j, P[MAX >> 2] ; bool mark ;
int N1, N2, N3, N4, A[MAX >> 2], B[MAX >> 2], Txt ;

inline int qr(){
    int k = 0 ; char c = getchar() ;
    while(!isdigit(c)) c = getchar() ;
    while(isdigit(c)) k = (k << 1) + (k << 3) + c - 48, c = getchar() ;
    return k ;
}
inline void Linearity(){
    T = qr() ;
    Chk[1] = Chk[0] = 1 ;
    for (i = 2 ; i <= MAX ; ++ i){
        if (!Chk[i]) P[++ P[0]] = i ;
        for (j = 1; j <= P[0] && i * P[j] <= MAX ; ++ j){
            Chk[i * P[j]] = 1 ;
            if (i % P[j] == 0) break ;
        }
    }
}
inline void work(int ST, int ED){
    for(i = ST; i <= ED ; ++ i){
        N1 = N2 = N3 = N4 = 0 ;
        while (!(A0 % P[i])) A0 /= P[i], ++ N1 ;
        while (!(A1 % P[i])) A1 /= P[i], ++ N2 ;
        while (!(B0 % P[i])) B0 /= P[i], ++ N3 ;
        while (!(B1 % P[i])) B1 /= P[i], ++ N4 ;
 		if (N1 > N2 && N3 < N4){
            if (N2 == N4) A[i] = B[i] = 1 ;
            else {mark = 0; break ;}
            continue ;
        }
        if (N1 > N2){
            if (N4 >= N2) A[i] = B[i] = N2 ;
            else {mark = 0; break ;}
            continue ;
        }
        if (N3 < N4){
            if (N4 >= N2) A[i] = B[i] = N3 ;
            else {mark = 0; break ;}
            continue ;
        }
        else {
            if (N4 >= N2) A[i] = N2, B[i] = N4 ;
            else {mark = 0; break ;}
        }
    }
}
int main(){
    freopen("son.in", "r", stdin) ;
    freopen("son.out", "w", stdout) ;
    Linearity() ;
    while(T --){
        Ans = 1, mark = 1 ;
        A0 = qr(), A1 = qr(), B0 = qr(), B1 = qr() ;
        work(1, P[0]) ;
        if (A0 != 1 || A1 != 1 || B0 != 1 || B1 != 1){
            Txt = P[0] + 1 ;
            if (B1 != 1) P[++ P[0]] = B1 ;
            if (A1 != 1 && A1 != B1) P[++ P[0]] = A1 ;
            if (A0 != 1 && A0 != B1 && A0 != A1) P[++ P[0]] = A0 ;
            if (B0 != 1 && B0 != B1 && B0 != A1 && B0 != A0) P[++ P[0]] = B0 ;
            work(Txt, P[0]) ;
        }
        for(i = 1; i <= P[0] && mark ; ++ i) Ans *= (B[i] - A[i] + 1) ;
        if (!mark) putchar('0'), putchar('\n') ;
        else printf("%d\n", Ans) ;
    }
}

```

最后还有彩蛋哦：

$1$、这个题中的关键代码，就是work函数是在作者事先考虑清楚，事中如同做梦，事后不可思议的情况下写出来的……也就是说当时写代码的时候码力突然增强了一个量级$2333$

$2$、关于什么自由不自由的定义……哈哈哈哈那只是我的突发奇想而已~~不是故意哲学!不是！~~但是你会发现以下的文字阐述确实会简练好多啊

$3$、其实你如果去不找另一个比较大的质数，也是可以得$90$分的！从$loj$的数据来看，前面的测试点一路顺风，只有最后一个测试点是专门卡这一点的，因为出现了好多行答案不相同的情况$2333$

$4$、其实我觉得我最后的操作是跟$AlphaGo$动态学习处理信息有点异曲同工之处的，所以为了这个必须来写题解！

---

## 作者：Ebola (赞：33)

**这一题最重要的就是数学推理！**

首先当然是得打素数表，实际上我们只要打到前 $4000$ 个素数就可以了，多打无害。

那么，我们来推理。

假如 $a$ 与 $b$ 的最大公因数是 $c$，我们把它们分解质因数，将 $a$ 分解后的结果中含有素数 $p$ 的个数记为 $an$，将 $b$ 分解后的结果中含有素数 $p$ 的个数记为 $bn$，将 $c$ 分解后的结果中含有素数 $p$ 的个数记为 $cn$。

如果 $an=cn$，那么 $bn$ 只要大于 $cn$ 大可随意取值

如果 $an>cn$，那么 $bn$ 必须等于 $cn$（自己思考）

如果 $an<cn$，那么这游戏没法玩了，直接输出 $0$ 退出程序。


假如 $a$ 与 $b$ 的最小公倍数是 $c$，我们把它们分解质因数，将 $a$ 分解后的结果中含有素数 $p$ 的个数记为 $an$，将 $b$ 分解后的结果中含有素数 $p$ 的个数记为 $bn$，将 $c$ 分解后的结果中含有素数 $p$ 的个数记为 $cn$。

如果 $an=cn$，那么 $bn$ 只要小于 $cn$ 并大于等于 $0$，大可随意取值

如果 $an<cn$，那么 $bn$ 必须等于 $cn$（自己思考）

如果 $an>cn$，那么这游戏没法玩了，直接输出 $0$ 退出程序。


那么，如果上述两项讨论中均出现 $an=cn$ 的情况，我们就可以发现，$bn$ 只能取 $cn$ (第一项讨论中的) $\sim cn$  (第二项讨论中的) 之间的数。

将情况组合 (这里直接相乘) 即为解


好吧，推理结束，程序就好写了。我们只要写一个过程，将我们的推理结果表述一遍，并将素数表前 $4000$ 的数据代到 $p$ 里面去运算就好了。


AC 代码奉上，仅供参考。





```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int prime[5000]={99999999,2,3,5,7};
int primenum=4;
int n,a0,a1,b0,b1;
int result;
void work(int p)
{
    int a0n=0,a1n=0,b0n=0,b1n=0;
    while(a0%p==0){a0n++;a0/=p;}
    while(a1%p==0){a1n++;a1/=p;}
    while(b0%p==0){b0n++;b0/=p;}
    while(b1%p==0){b1n++;b1/=p;}
    if((a0n<a1n)||(b0n>b1n))
    {
        result=0;
        return;
    }
    if((a0n==a1n)&&(b0n==b1n))
    {
        if(a1n<=b1n) result*=(b1n-a1n)+1; else result=0;
        return;
    }
    if(((a0n==a1n)&&(b0n<b1n))||((a0n>a1n)&&(b0n==b1n)))
    {
        if(a1n<=b1n) result*=1; else result=0;
        return;
    }
    if((b0n<b1n)&&(a0n>a1n))
    {
        if(b1n==a1n) result*=1;else result=0;
        return;
    }
}
int main()
{
    int i,j;
    for(i=11;i<45000;i++)
    {
        for(j=1;((j<=prime[0])&&(prime[j]*prime[j]<=i)&&(i%prime[j]));j++);
        if(prime[j]*prime[j]>i || j>prime[0])
        {
            primenum++;
            prime[primenum]=i;
        }
    }
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a0>>a1>>b0>>b1;
        result=1;
        for(j=1;j<=4000;j++)
            work(prime[j]);
        if(a0>1)
            work(a0);
        else
            if((b1>1)&&(b1!=a0))
                work(b1);
        cout<<result<<endl;
    }
    return 0;
}
```

---

## 作者：HCl_Violet (赞：24)

## 传送门：[hankson的趣味 ~~（毒瘤）~~ 题](https://www.luogu.org/problem/P1072)

$gcd(a,b)=p_1^{min(r_1,t_1)}p_2^{min(r_2,t_2)}...p_s^{min(r_s,t_s)}$

$lcm(a,b)=p_1^{max(r_1,t_1)}p_2^{max(r_2,t_2)}...p_s^{max(r_s,t_s)}$

根据以上两个式子，我们可以对$a_0,a_1,b_0,b_1$进行质因数分解，对每一个$p_i$分别将其指数记录为$num_{a_0},num_{a_1},num_{b_0},num_{b_1}$;记录x在$p_i$的指数上能有几种情况；

所以，一个素数表是必不可少的。

然后就是质因数分解啦。

分别记录$gcd,lcm$公共的种数情况;

---
接下来分类讨论：

$PS:$讨论情况~~应该~~有先后顺序

- 如果$num_{a_0}<num_{a_1}$ --> 0种
- 如果$num_{b_0}>num_{b_1}$ --> 0种
- 如果$gcd=lcm=1$ 

	 ①$num_{a_1}=num_{b_1}$ --> 1种
     
     ②$num_{a_1}>num_{b_1}$ --> 0种
- 如果$gcd<lcm$,那么此时$gcd$的情况一定是$lcm$的子集 --> $gcd$种
- 如果$gcd$有无穷种
     
     ①$lcm$只有取0这一种 --> 1种
     
     ②$lcm$不只取0这一种 --> $num_{b_1}-num_{a_1}+1$种；
     
     $For~example: lcm$能取8种，满足≤7；$gcd$能取无穷种，但满足≥6，
     那么此时应该有6、7两种，即7-6+1；
     
- 最后，把每一个$p_i$指数的情况相乘即可

- $PS:$

  ①如果最后剩余满足$b_0=b_1≠1$且$b_0≠a_0=a_1$，否则只有一种（指数取0）,那么剩下的肯定是一个质数，这时$p_i$指数的取值有2种情况（指数取0或取1）
  
  ②道理相似,如果最后剩余满足$a_0=a_1≠1$且$a_0≠b_0=b_1$,此时应该只有0种情况，否则就有1种情况（指数取0）；
  
~~emmm,其实我也不知道对不对。~~

## $\mathfrak {Code}:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50000;
int prime[N],tot;
bool vis[N];

void getprime()
{
	for(int i=2;i<=50000;i++){
		if(!vis[i]){
			prime[++tot]=i;
		}
		for(int j=1;j<=tot&&i*prime[j]<=50000;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
}

int work(){
	int ans=1;
	int a,aa,b,bb;
	cin>>a>>aa>>b>>bb;
	if(a<aa||b>bb){
		return 0;
	}
	for(int i=1;i<=tot&&prime[i]<=bb;i++){ 
		int numa=0,numaa=0,numb=0,numbb=0;
		int qcda=1e9,lcmb=1;
		int x=prime[i];
		while(a%x==0){a/=x;numa++;}
		while(aa%x==0){aa/=x;numaa++;}
		while(b%x==0){b/=x;numb++;}
		while(bb%x==0){bb/=x;numbb++;}
		int m;
		if(numa<numaa||numb>numbb){
			return 0;
		}
		if(numa>numaa)qcda=1;
		if(numa==numaa)qcda=1e9;
		if(numb==numbb)lcmb=numbb+1;
		if(numb<numbb)lcmb=1;
		if(numaa>numbb){
			return 0;
		}
		if(lcmb==1&&qcda==1){//都是一种 
			if(numaa==numbb){//如果相同 
				m=1;//就为一种 
			}
			else{//如果不同，0种
				return 0;
			}
		}
		else if(lcmb>qcda){//如果lcm多种，qcd为1种;
		/*因为numbb>=numaa,所以qcd一定是lcm的子集，即m=1*/ 
			m=qcda;
		}
		else if(qcda==1e9&&lcmb>1){//如果qcd为无限种;
		/*例如:qcd中要保证>=6,lcm中要保证<=7,m应该为7-6+1，即2*/ 
			m=numbb-numaa+1;
		}
		else if(lcmb==1&&qcda==1e9){
			m=1;
		}
		ans*=m;
	}
	if(b==bb&&bb!=1&&b!=a&&b!=aa)ans*=2;
	return ans;
}

int main()
{
	getprime();
	int T;
	cin>>T;
	while(T--){
		cout<<work()<<endl;
	}
	
}
```


---

## 作者：_std_O2 (赞：11)

# P1072 [NOIP2009 提高组] Hankson 的趣味题题解
## description
[there](https://www.luogu.com.cn/problem/P1072)
## solution
我们令集合 $P$ 为将 $b_{1}$ 质因数分解后所能组成的数的集合。
 
根据最大公因数和最小公倍数的性质容易发现 $answer \in  P$。

那我们就可以将集合 $P$ 中的数挨个 check 看是否满足：

1. $x$ 和 $a_0$ 的最大公因数是 $a_1$。
2. $x$ 和 $b_0$ 的最小公倍数是 $b_1$。

## 时间复杂度计算
对于任意一个数 $p$ 都可以拆成如下形式：

$a_{1}^{b_{1}} \cdot a_{2}^{b_{2}}   \cdot …  \cdot a_{n}^{b_{n}} $。

其中 $a_1,a_2...a_n$ 为质数， $b_1,b_2...b_n \in \mathbb N*$。

用 $p$ 的质因数组合的情况数为 $(b_1 + 1) \cdot (b_2 + 1) \cdot ... \cdot (b_n + 1) $。

不难得到 在最坏情况下 $a$ 数组为 $\set{2, 3, 5, 7 ...}$。

经验证，当到 $a_{11}$ 时，总和会爆 int。

所以在最坏情况下，有 $2^{10}$ 种情况，不会爆炸。

~~注：本题解来自机房某[大佬](https://www.luogu.com.cn/user/1308003)，本蒟蒻只是借鉴。~~

## code

```cpp
#include<bits/stdc++.h>
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

---

## 作者：zsq9 (赞：6)

[AC 记录](https://www.luogu.com.cn/record/198326758)

## 题目大意

已知正整数 $a_0,a_1,b_0,b_1$，设某未知正整数 $x$ 满足：

1. $x$ 和 $a_0$ 的最大公约数是 $a_1$；

2. $x$ 和 $b_0$ 的最小公倍数是 $b_1$。

求解满足条件的 $x$ 的个数。

## 思路

这题看到有大佬打素数表，根本没必要，我们注意到题目中 $x$ 和 $b_0$ 的最小公倍数是 $b_1$。所以 $x$ 一定是 $b_1$ 的因数，我们又可以注意到 $n$ 最大只有 **$2000$** 并且 $b_1$ 最大 $2 \times 10^9$，所以直接暴力枚举每个 $b_1$ 的因数就可以了，复杂度也是 $O(n \sqrt{b_1})$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll,sb;
int a0,a1,b0,b1,ans=0,n=0;
ll lcm(ll a,ll b){
    return a*b/__gcd(a,b);
}    
int main(){
    cin>>n;
	for(ll j=1;j<=n;j++){
   		cin>>a0>>a1>>b0>>b1;
  		ans=0;
    	for(int i=1;i<=b1/i;i++){//一定是b1的因子，所以只要找到根号b1就可以了 
        	if(b1%i==0){
     	 	    if(a1==__gcd(a0,i)&&b1==lcm(i,b0)){//如果满足条件就加上      
				   	ans++;
      		    }   
     			if(a1==__gcd(a0,b1/i)&&b1==lcm(b1/i,b0)){//平方的时候只算一次 
     	      		if(b1/i!=i)ans++;
     			}       
        }   
    }
	cout<<ans<<"\n";
}
 
 
return 0;
}
```

---

## 作者：cyh_toby (赞：5)

# 题意
原题：[P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)

给定 $a,b,c,d$ 四个正整数，求使下条件同时成立的正整数 $x$ 的个数。

- $\gcd(x,a)=b$

- $\text{lcm}(x,c)=d$

# 分析
第一个条件不好入手找 $x$ ，考虑从第二个条件攻破。

显然 $x$ 必须是 $d$ 的因数，而找出一个数的因数的复杂度是 $O(\sqrt{n})$ ，故可以考虑枚举 $x$ 。

枚举 $x$ 判断是否满足条件即可。

一次 $\gcd$ 复杂度 $\log\,n$ 。

总复杂度 $O(Tn\log n)$ ，$n$ 为值域最大值。

勉强可以过。

# 源码
```cpp
/**********************************

Problem: [NOIp2009TG] - Hankson的趣味题 

State: Accepted

From: [NOIp2009TG]

Algorithm: 数论, gcd 

Author: cyh_toby

Last updated on 2020.3.15

**********************************/
#include <cstdio>
using namespace std;
const int N = 50005;
int a, b, c, d, n, div[N], cnt, ans;
int gcd(int x, int y) {
	if (y == 0)
		return x;
	return gcd(y, x % y);
}
int main()
{
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		int t = d;
		ans = cnt = 0;
		for (int i = 1; i <= t/i; i++) {
			if (t % i == 0) {
				div[++cnt] = i;
				if (i * i != t)
					div[++cnt] = t/i;
			}
		}
		for (int i = 1; i <= cnt; i++) {
			int e = div[i];
			if(gcd(e, a) == b && e*c == d*gcd(e,c))
				ans++; 
		}
		printf("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：Cold_Eyes_bystander (赞：3)

考虑根号算法。

先思考暴力的思路，就是枚举，对每一个满足条件的数都做一次统计，可以骗到 50 分。

```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int cnt=0;
        for(int i=1;i<=d;i++)
        {
            if(d%i==0)
            {
                if(__gcd(i,a)==b&&i/__gcd(i,c)*c==d) cnt++;
            }
            
        }
        printf("%d\n",cnt);
    }
}
```

发现上面的代码执行的次数连整数类型都存不下，所以我们猜测需要根号时间复杂度等。

我们发现很多枚举次数都是不需要的，联想到判断质数时只需枚举到根号，因为除了平方根外，剩下的因数都成对分布在一左一右。

那我们只需枚举到根号，大于根号的因数都用小因数除出来。

```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int cnt=0;
        for(int i=1;i<=sqrt(d);i++)
        {
            if(d%i==0)
            {
                if(__gcd(i,a)==b&&i/__gcd(i,c)*c==d) cnt++;
                int x=d/i;
                if(x!=i&&__gcd(x,a)==b&&x/__gcd(x,c)*c==d) cnt++;
            }
            
        }
        printf("%d\n",cnt);
    }
}
```

---

## 作者：zhuangjinning (赞：2)

## 题目大意

给出四个整数 $a_0$，$a_1$，$b_0$，$b_1$，问满足以下条件的整数 $x$ 的个数。

* $\gcd(x,a_0)=a_1$。

* $\operatorname{lcm}(x,b_0)=b_1$。

## 解析

首先，这道题最暴力的方法就是从 $1$ 枚举到 $b_1$，判断是否符合条件，但这种方法复杂度太高，无法通过本题，所以需要一些更快的方法。

经过观察发现，$\operatorname{lcm}(x,b_0)=b_1$ 表明 $x$ 为 $b_1$ 的约数，所以枚举所有 $b_1$ 的约数即可，由于约数是成对出现的，所以只需枚举到 $b_1$ 即可，复杂度为 $O(\sqrt{b_1})$，可以通过此题。

另外，此题有一些细节。

第一，如果 $b_1$ 不整除 $a_1$，直接输出 $0$。

第二，设枚举到的约数为 $t$，那么如果 $t=b_1/t$，那么 $t$ 的贡献只用算一次即可，不能算两遍。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int a0;
int a1;
int b0;
int b1;
int ans;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int lcm(int a,int b){
	return a/gcd(a,b)*b;
}
signed main(){
	cin>>t;//多测
	while(t--){
		ans=0;//多测清空
		cin>>a0>>a1>>b0>>b1;
		if(b1%a1!=0){//特判
			cout<<0<<endl;
			continue;
		}
		for(int x=1;x*x<=b1;x++){
			if(b1%x==0){
				if(lcm(x,b0)==b1 and gcd(x,a0)==a1){
					ans++;
				}
				int y=b1/x;
				if(x!=y and lcm(y,b0)==b1 and gcd(y,a0)==a1){//如果不相等才能加
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：syx_2014 (赞：2)

显然直接暴力不行，复杂度 $O(n \times b_1)$，会 TLE。

我们发现，$x$ 肯定是 $b_1$ 的因数，而除了平方数，因数都是成对的，所以我们在 $1$ 和 $\sqrt{b_1}$ 里枚举 $x$ 和 $\dfrac{b_1}{x}$ 是否满足条件就行了（因为 $x$ 是 $b_1$ 的因数，所以 $\dfrac{b_1}{x}$ 一定是整数）。

但是 $b_1$ 如果是 $x$ 的平方的话，那 $x$ 就与 $\dfrac{b_1}{x}$ 相等了，会导致 $x$ 被计数两遍。所以我们要特判一下 $b_1$ 是 $x^2$ 的情况，这时只需要判断一遍就可以了。

温馨提示：

- C++ 里求最大公因数的函数是 ```__gcd()```，```__gcd(x,y)``` 是求 $x$ 和 $y$ 的最大公因数。
- $$\operatorname{lcm}(x,y)= \dfrac{xy}{\gcd(x,y)}$$

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	for(int o=1;o<=T;o++){
		int ans=0;
		int a0,a1,b0,b1;
		cin>>a0>>a1>>b0>>b1;
		int qq=(int)sqrt(b1);
		for(int i=1;i<=qq;i++){
//注意 if 的顺序
			if(b1%i==0&&b1/i==i){
                //注意：求最小公倍数时，先除后乘，防止溢出。
				if(__gcd(i,a0)==a1&&i/__gcd(i,b0)*b0==b1) ans++;
				break;
			}
			else if(b1%i==0){
				if(__gcd(i,a0)==a1&&i/__gcd(i,b0)*b0==b1){
					ans++;
				}
				if(__gcd(b1/i,a0)==a1&&(b1/i)/__gcd(b1/i,b0)*b0==b1){
					ans++;
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：LiJunze0501 (赞：2)

# 审题
先看标签。
#### 数学、枚举、最大公约数 gcd。
再看题面。
> 已知正整数 $a0$，$a1$，$b0$，$b1$，设某未知正整数 $x$ 满足：  
> $x$ 和 $a0$ 的最大公约数是 $a1$；  
> $x$ 和 $b0$ 的最小公倍数是 $b1$。
# 分析
我们立马就能想到枚举 $x$，验证是否符合条件。因为 $x$ 是 $b1$ 的约数，所以枚举到 $b1$ 就好了。  
但看数据范围，$1\le b1\le2\times10^9$，瞬间放弃这种念头。  
怎么优化呢？我们只需要枚举到 $\sqrt {b1}$ 就好了。当枚举的 $x$ 是 $b1$ 约数时，另一个约数就是 $\frac{b1}{x}$。再将两个都验证一下就好了。
# 温馨提示
$x^2$ 就是 $b1$ 时，不要重复考虑！
# AC Code
参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a0,a1,b0,b1;
int gcd(int x,int y){
	return __gcd(x,y);
}
int lcm(int x,int y){
	return x/__gcd(x,y)*y;
}
int main(){
	cin>>t;
	while(t--){
		cin>>a0>>a1>>b0>>b1;
		int cnt=0;
		for(int x=1;x*x<=b1;x++)
			if(b1%x==0){
				if(lcm(x,b0)==b1&&gcd(x,a0)==a1) cnt++;
				int y=b1/x;
				if(y!=x&&lcm(y,b0)==b1&&gcd(y,a0)==a1) cnt++;
			}
		cout<<cnt<<endl; 
	}
}
```

---

## 作者：sunny12888 (赞：2)

## 题目大意
已知四个数 $ a , b , c , d $ ，问有多少个满足题意的数（描述为 $x$ ），使得 $ \gcd(x,a)=b $ 且 $ \operatorname{lcm} (x,c)=d $ 。
## 题目解法
### 方法一：暴力枚举（50分）
直接从 $1$ 枚举到 $d$ ，满足题意的， $total$ 加一。

代码非常好理解：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define happy cin
#define s2025 cout
#define years endl
// 求最大公约数（辗转相除法）
int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
}
// 求最小公倍数
int lcm(int a, int b) {
    return a/gcd(a,b)*b;
}
int main() {
    int n;
    happy>>n;
	while(n--) {
        int a0,a1,b0,b1;
        cin>>a0>>a1>>b0>>b1;
        int total = 0;
        for (int x = 1; x<= b1; x++) {
            if (b1 % x == 0) {
                if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                    total++;
                }
                
            }
            
        }
        s2025<<total<<years;
    }


    return 0;
}

```

### 方法二：正解做法（100分）
方法一的时间复杂度过高（最多要执行 $2 \times 10^9$ 次）

尝试剪枝。我们先尝试打表：

若 $a=3,b=1,c=5,d=10$ 时：



|$i$|$\dfrac{d}{i}$ ，并向下取整|$i$ 是否满足题意|$\dfrac{d}{i}$ 是否满足题意|
|:-:|:-:|:-:|:-:|
|1|10|否|是|
|2|5|是|否|
|3|3|否|否|
|4|2|否|是（已重复）|
|5|2|否|是（已重复）|
|6|1|否|否|
|7|1|否|否|
|8|1|否|否|
|9|1|否|否|
|10|1|是（已重复）|否|

我们惊讶的发现一个事实：无论 $a,b,c,d$ 为何值，只有前 $ \sqrt{d} $ 的值有效计算。

于是剪枝代码就很快写出来了：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define happy cin
#define s2025 cout
#define years endl
// 求最大公约数（辗转相除法）
int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
}
// 求最小公倍数
int lcm(int a, int b) {
    return a/gcd(a,b)*b;
}
int main() {
    int n;
    happy>>n;
	while(n--) {
        int a0,a1,b0,b1;
        cin>>a0>>a1>>b0>>b1;
        int total = 0;
        for (int x = 1; x * x <= b1; x++) {
            if (b1 % x == 0) {
                if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                    total++;
                }
				int y=b1/x;
                // 如果 x 和 y 不同，也检查 y
                if (x != y && gcd(y, a0) == a1 && lcm(y, b0) == b1) {
                    total++;
                }
            }
        }
		s2025<<total<<years;
    }


    return 0;
}

```
欢迎大家提出问题，感谢！

---

## 作者：suzhikz (赞：2)

$n$ 的范围比较大，再加上和因数之类的有关，会想到枚举质数。

对于一个质数 $p$，思考它对答案的贡献，首先对题目给的四个数分解质因数，看他们有多少个该质数因子。

然后就是分类讨论，直接给代码，分解质因数就不给了。


```cpp
//输入比较怪，a,b,c,d对应的是a0,b0,a1,b1
if(ma>mc){
if(mb<md&&mc==md)ans*=1;
  else if(mb==md&&mc<=md){
  	ans*=1;
  }else{
  	ans=0;
  }
}else if(ma==mc){
  if(mb>md)ans=0; 
	else{
		if(mb<md&&mc<=md)ans*=1;
		else if(mb==md&&mc<=md)ans*=(md-mc+1);
		else ans=0;
	}
}else{
  ans=0;
  }
}
```

然后还有我们的质因数只枚举到根号级别，可能还有大质数，所以要特判下。


```cpp
if(a!=1||b!=1||c!=1||d!=1){
	if(a==c&&a!=1)ans*=2;
	if(b==d&&b!=1)ans*=2;
}
```

---

## 作者：array2022 (赞：1)

### 题目分析
- 看到题目后可以先考虑暴力枚举，枚举 $1$ 到 $b_1$ 之间的数。时间复杂度 $O(nb_1)$。

### 部分分代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
int gcd(int a,int b){
	return __gcd(a,b); // 内置函数。 
}
int lcm(int a,int b){
	return a/gcd(a,b)*b; // 防止超过 int 范围。 
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	while (n--){
		int a0,a1,b0,b1,ans=0;
		cin>>a0>>a1>>b0>>b1;
		for (int i=1;i<=b1;i++){
			if (gcd(i,a0)==a1&&lcm(i,b0)==b1) ans++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
### 优化
- 由于有 $\operatorname{lcm}(x,b_0)=b_1$，肯定有 $x\mid b_1$，可以由此减少枚举次数。枚举 $b_1$ 的 $1$ 到 $\sqrt {b_1}$ 的所有约数（设为 $y$），那么另一个约数就是 $\dfrac{b_1}{y}$，这样就可以减小运行时间。时间复杂度 $O(n\sqrt{b_1})$。这个技巧在其他题目中也有应用。
- **注意上述枚举的过程中有 $y^2=b_1$ 的特殊情况。**

### 通过代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int gcd(int a,int b){
	return __gcd(a,b); // 内置函数。 
}
int lcm(int a,int b){
	return a/gcd(a,b)*b; // 防止超过 int 范围。 
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	while (n--){
		int a0,a1,b0,b1,ans=0;
		cin>>a0>>a1>>b0>>b1;
		for (int i=1;i<=b1/i;i++){
			if (b1%i!=0) continue; // 枚举约数。
			if (gcd(i,a0)==a1&&lcm(i,b0)==b1) ans++;
			if (b1!=i*i){ // 注意排除特殊情况。
				if (gcd(b1/i,a0)==a1&&lcm(b1/i,b0)==b1) ans++;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：jiqihang (赞：1)

给定 $a,b,c,d$，求下列条件同时成立的正整数 $x$ 的个数。

1. $\gcd(x,a)=b$
2. $\operatorname{lcm}(x,c)=d$

暴力枚举 $x$，看 $x$ 是否满足，满足在满足的个数上加 $1$ 即可。

题目中的“若不存在这样的 $x$，请输出 $0$”很有迷惑性。很多人特判了。其实不必，因为如果不存在，计数器则还是 $0$，直接输出和特判一下没差别。

算一下时间复杂度 $O(Tn \log n)$，可过。

---

## 作者：qhr2023 (赞：1)

## solution

对于每组数据，我们可以枚举 $b_1$ 的因数作为 $x$，判断 $x$ 和 $a_0$ 的最大公约数是否为 $a_1$，$x$ 和 $b_0$ 的最小公倍数是否为 $b_1$，若都满足答案加一。

对于求最大公因数，我们可以用自带的 ```__gcd``` 来解决。而 $A$ 和 $B$ 的最小公倍数就是 $A \times B \div \gcd(A, B)$，证明如下。

先将 $A$ 和 $B$ 质因数分解，得到 $A=p_1^{a_1} \times p_2^{a_2} \times p_3^{a_3} \times ...$ 和 $B=p_1^{b_1} \times p_2^{b_2} \times p_3^{b_3} \times ...$，其中 $a_i$ 和 $b_i$ 都是非负整数，$p_i$ 是质数。

那么 $A \times B=p_1^{a_1+b_1} \times p_2^{a_2+b_2} \times p_3^{a_3+b_3} \times ...$，依据最大公因数定义，$\gcd(A, B)=p_1^{\min(a_1, b_1)} \times p_2^{\min(a_2, b_2)} \times p_3^{\min(a_3, b_3)} \times ...$，依据最小公倍数定义，$A$ 和 $B$ 的最小公倍数就是 $p_1^{\max(a_1, b_1)} \times p_2^{\max(a_2, b_2)} \times p_3^{\max(a_3, b_3)} \times ...$。

显然 $a_1+b_1 - \min(a_1, b_1)=\max(a_1, b_1)$，那么同理 $p_1^{a_1+b_1 - \min(a_1, b_1)} \times p_2^{a_2+b_2 - \min(a_2, b_2)} \times p_3^{a_3+b_3 - \min(a_3, b_3)} \times ...$ 就等于 $p_1^{\max(a_1, b_1)} \times p_2^{\max(a_2, b_2)} \times p_3^{\max(a_3, b_3)} \times ...$，所以 $A$ 和 $B$ 的最小公倍数就是 $A \times B \div \gcd(A, B)$。

时间复杂度是 $\mathcal O(n \sqrt{b_1} \log b_1)$，这么看计算量会超过 $2 \times 10^9$，但是 $2 \times 10^9$ 范围内因数最多不会超过 $1500$，也就是说每组数据只求了不超过 $1500$ 次的最大公因数，计算量大大减小，事实上这也远远跑不满，[实测很快](https://www.luogu.com.cn/record/198236563)。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a, a1, b, b1, n; 
long long lcm (long long a, long long b) {
	return a*b/__gcd(a, b);
}
bool check(long long x){
	return (__gcd(x, a)==a1&&lcm(x, b)==b1);
} 
int main(){
	cin >> n;
	while(n--){
		cin >> a >> a1 >> b >> b1;
		int ans=0;
		for(long long i=1; i*i<=b1; i++)
			if(b1%i==0)
				ans+=check(i)+check(b1/i)-(i==b1/i&&check(i));
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

呃呃呃，考完 csp 第一次在 luogu 上写题解。

### 题意

给予四个整数 $a,b,c,d$，求满足 $\gcd (a,x)=b, \operatorname{lcm}(c,x)=d$ 的正整数 $x$ 的个数。

### 思路

对于条件一，$x$ 的范围过于宽泛，~~难道你要扫描 $b$ 的所有倍数吗？~~

所以我可以将 $x$ 的大致范围锁定在条件二中，即 $x$ 为 $d$ 的约数。

锁定 $d$ 的所有约数只需要 $O(\sqrt{d})$ 的复杂度。

具体的来说，所有约数，除 $\sqrt{d}$ 以外，都是成对出现的，若有一个约数是 $i$，则必有另一个为 $d/i$。

所以，我们只需要扫描 $1$ 到 $\sqrt{d}$ 即可，每扫描到一个约数 $i$，将 $i$ 和 $d/i$ 放入放约数的数组（$\sqrt{d}$ 除外，特判一下）。

谨记：$1$ 也要扫描，题目中没要排除 $1$。

然后将扫描出来的约数每一个判断一下是否满足题目中的条件即可。

### AC Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int gcd(int a,int b){ return b ? gcd(b,a%b) : a;} 
int lcm(int a,int b){return a*b/gcd(a,b);} 
int a,b,c,d,ans;
int primes[N],p,t;
void solve(){
	p=0,ans=0;
	cin>>a>>b>>c>>d;
	for(int i=1;i<=sqrt(d);i++)if(d%i==0&&i*i!=d)primes[++p]=i,primes[++p]=d/i; else if(d%i==0)primes[++p]=i;//码风不好，请谅解一下。
	for(int i=1;i<=p;i++){
		if(primes[i]*c==d*gcd(primes[i],c)&&gcd(a,primes[i])==b){
			++ans;
		}
	}
	cout<<ans<<"\n";
}
int main(){
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：kungeruyi (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/P1072)**

**解题思路：**

根据最大公约数和最小公倍数的性质，设 $x=k×a_1$（$k$ 为正整数），因为 $x$ 和 $a_0$ 的最大公约数是 $a_1$，所以与 $\frac{a_0}{a_1}$ 互质。

又因为 $x$ 和 $b_0$ 的最小公倍数是，所以 $k$ 是 $\frac{b_1}{b_0}$ 的约数。

先求出 $\frac{a_0}{a_1}$ 和 $\frac{b_1}{b_0}$，然后找出 $\frac{b_1}{b_0}$ 的所有约数，对于每个约数 $d$，判断 $d$ 与 $\frac{a_0}{a_1}$ 是否互质，如果互质，则 $d×a_1$ 是满足条件的 $x$，统计满足条件的 $x$ 的个数

以输入样例为例，第一组数据 $41$，$1$，$96$，$288$，$\frac{a_0}{a_1}=41$，$\frac{b_1}{b_0}=3$，$3$ 的约数为 $1$ 和 $3$，$1$ 与 $41$ 互质，$3$ 与 $41$ 也互质，所以 $x$ 可以是 $1×1=1$，$3×1=3$，但 $1$ 不满足最小公倍数是 $288$，$3$ 满足，同理 $9,18,36,72,144,288$ 也满足，共 $6$ 个；第二组数据 $95$，$1$，$37$，$1776$，$\frac{a_0}{a_1}=95$，$\frac{b_1}{b_0}=48$,$48$ 的约数中与 $95$ 互质且满足条件的 $x$ 有 $48$ 和 $1776$，共 $2$ 个。

---

## 作者：Wish_kazdel (赞：1)

~~其实还是挺难的一道题，也可能是我太弱了。~~

---

## 分析
我们可以从第一个条件出发，因为 $x$ 和 $a_0$ 的最大公约数是 $a_1$，那么 $x$ 就必须是 $a_0$ 的倍数。

然后再看第二个条件，因为 $x$ 和 $b_0$ 的最小公倍数是 $b_1$，那么 $x$ 就必须是 $b_1$ 的因数。

---

## 思路
我们开始根据分析进行模拟。

首先，先验证条件的可行性。如果 $a_0$ 不能被 $a_1$ 整除或者 $b_1$ 不能被 $b_0$ 整除，那么直接输出 $0$。
然后我们寻找可能的 $x$ 值，检查 $x$ 和 $a_0$ 的最大公约数是否为 $a_1$，和 $b_0$ 最小公倍数是否为 $b_1$。
如果满足其中任意一个条件，计数器加 $1$。最后输出结果即可。

---

## 算法
可以直接运用辗转相除法以及最大公约数和最小公倍数之间的关系来计算最小公倍数，感兴趣可以自行去搜索证明方式。

---

## 作者：FastIO_DP (赞：0)

## 题目理解

找出满足两个条件的正整数 $x$ 并统计次数：

1. $x$ 和 $a_0$ 的最大公约数必须是 $a_1$。
2. $x$ 和 $b_0$ 的最小公倍数必须是 $b_1$。

## 分析

第一个条件 $\gcd(x, a_0) = a_1$，可以知道：

- $x$ 必须是 $a_1$ 的倍数。
- $x$ 与 $a_0 $ 或 $\gcd(x, a_0)$ 互质。

第二个条件 $\text{lcm}(x, b_0) = b_1$，可以知道：

- $x$ 必须是 $b_1$ 或 $b_0$ 的倍数。
- $x$ 与 $b_0$ 的最小公倍数恰好为 $b_1$。

## 解题思路

考虑枚举。

枚举 $x$ 的可能值。可以这样想：

1. $x$ 一定是 $b_1$ 的因子。
2. 对每个 $b_1$ 的因子，检查是否满足两个条件。

然后就来写代码了：

首先，枚举 $b_1$ 的所有因子 $x$。
其次对每个 $x$，检查 $\gcd(x, a_0) = a_1$。
然后同时检查 $\text{lcm}(x, b_0) = b_1$。
最后统计满足条件的 $x$ 的个数就完成了。

## 代码实现

```cpp
#include <iostream>
using namespace std;


// 求最大公约数（辗转相除法）
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


// 求最小公倍数
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}


int main() {
    int n;
    cin >> n;


    while (n--) {
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;


        int cnt = 0;
        // 枚举 b1 的因子
        for (int x = 1; x * x <= b1; x++) {
            if (b1 % x == 0) {
                int y = b1 / x;

                // 检查 x 是否满足条件
                if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                    cnt++;
                }

                // 如果 x 和 y 不同，也检查 y
                if (x != y && gcd(y, a0) == a1 && lcm(y, b0) == b1) {
                    cnt++;
                }
            }
        }


        cout << cnt << endl;
    }


    return 0;
}
```

## 复杂度分析

- 时间复杂度：$O(n \times \sqrt{b_1} \times \log{b_1})$。
  
  - $n$ 次询问。
  
  - 枚举了 $b_1$ 的因子。
  
  - 对每个因子进行 $\gcd$ 和 $\text{lcm}$ 计算。

- 空间复杂度：$O(1)$。
  
  - 只存储了变量。

---

## 作者：x_faraway_x (赞：0)

**题意**：给出 $a_0$, $a_1$, $b_0$, $b_1$, 求出正整数 $x$ 的个数，$x$ 满足：

$gcd(x,a_0)=a_1$ , $lcm(x, b_0)=b_1$ 。

**题解**：预备知识：设 $a= {p_1}^{a_1}{p_2}^{{a_2}}{p_3}^{{a_3}}...{p_n}^{{a_n}}$，$b= {p_1}^{b_1}{p_2}^{{b_2}}{p_3}^{{a_3}}...{p_n}^{{b_n}}$ ，则有：

 $gcd(a,b)={p_1}^{min(a_1,b_1)}{p_2}^{min(a_2,b_2)}{p_3}^{min(a_3,b_3)}...{p_n}^{min(a_n,b_n)}$

 $lcm(a,b)={p_1}^{max(a_1,b_1)}{p_2}^{max(a_2,b_2)}{p_3}^{max(a_3,b_3)}...{p_n}^{max(a_n,b_n)}$
 
 （ $p_i$ 为质因数）
 
根据题目结合上面的性质可以得到如下做法：

考虑枚举质因数 ${p_x}$ ，设 $a_0$ 的质因数中 $p_x$ 的次数为 $t_1$ ，$a_1$ 的次数为 $t_2$ , $x$ 的次数为 $t$ ，由前面性质可得：$min(t, t_1)=t_2$ 。分情况讨论：如果 $t_1 < t_2$ ，那么无解；如果 $t_1=t_2$ , 那么 $t$ 要满足 $t \geq t_2$ ；如果 $t_1 \gt t_2$ ，那么 $t = t_2$ .

同理，设 $b_0$ 的质因数中 $p_x$ 的次数为 $t_3$ ，$a_1$ 的次数为 $t_4$ , $x$ 的次数为 $t$ ，由前面性质可得：$max(t, t_3)=t_4$ 。分情况讨论：如果 $t_3 \gt t_4$ ，那么无解；如果 $t_3=t_4$ , 那么 $t$ 要满足 $t \leq t_4$ ；如果 $t_3 \lt t_4$ ，那么 $t = t_4$ .

把上面两个合并分类讨论可得：当 $t_2=t_1$ 且 $t_4=t_3$ 且 $t_4 \ge t_2$ ，此时 $t_2 \le t \le t_4$ , $ans$ *= $t_4-t_2+1$ .

下面是无解的 $3$ 种情况（可简化）：

1. $t_2=t_1$ 且 $t_4=t_3$ 且 $t_4 \lt t_2$，无解
2. $t_2 \lt t_1$ 或 $t_4 \gt t_3$ ，无解
3. $t_2 \gt t_1$ 且 $t_4 \lt t_3$  且 $ t_2 ≠ t_4$，无解

其他情况对 $ans$ 无影响 ( $ans$ *= $1$ ).
枚举质因数范围为 $\sqrt{b_1}$ （仅枚举 $b_1$ 的质因数），故总时间复杂度约为  $O(n\sqrt{b_1})$  ，可以通过。
（不优化的正解跑不过暴力，挺让人感慨的……）

```cpp
#include<cstdio>
inline int _read()
{
	int x=0; char c;
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+c-'0';
	return x;
}
const int N=100000;
bool b[N];
int prime[N],tot,a0,a1,b0,b1,ans;
void GetPrime()
{
	for(int i=2;i<=50000;i++)
		if(!b[i])
		{
			prime[++tot]=i;
			for(long long j=1ll*i*i;j<=50000;j+=i) b[j]=true;
		}
}
void work(int p)
{
	int t1=0,t2=0,t3=0,t4=0;
	for(;a0%p==0;a0/=p)t1++;//求次数
	for(;a1%p==0;a1/=p)t2++;
	for(;b0%p==0;b0/=p)t3++;
	for(;b1%p==0;b1/=p)t4++;
	if(t1==t2&&t3==t4)
	{
		if(t1<=t3) ans*=(t3-t1+1);
		else ans=0; //ans=0即无解
	}
	if(t1<t2||t3>t4) ans=0;
	if(t1>t2&&t3<t4&&t2!=t4) ans=0;
}
int main()
{
	int T=_read();
	GetPrime(); //预处理质数
	while(T--)
	{
		ans=1;
		a0=_read(),a1=_read(),b0=_read(),b1=_read();
		for(int i=1;i<=tot;i++)
			if(b1%prime[i]==0) work(prime[i]);
          	//枚举b1的质因数
		if(b1>1) work(b1);
		printf("%d\n",ans);
	}
}
```

---

## 作者：Kexi_ (赞：0)

比较水的一道绿题吧，枚举加上简单剪枝即可。

先看范围，暴力枚举肯定行不通的，线性复杂度跑单组数据都费劲，所以肯定是要根据 $\gcd$ 枚举剪枝优化到 $O(\sqrt{n})$ 。

先放个朴素代码。

```cpp
#include <bits/stdc++.h>
int ans,t,a1,b1,a0,b0;
namespace P1072
{
	using namespace std;
	inline int gcd(int a,int b){return b==0? a:gcd(b,a%b);}
	inline void solve()
	{
		for(int i=1;i*a1<=b1;i++)
		{
			int x=i*a1;
			if(gcd(x,a0)==a1&&x*b0/gcd(x,b0)==b1){ans++;}
		}
	}
	void main()
	{
		ios::sync_with_stdio(0); cin>>t;
		while(t--)
		{
			cin>>a0>>a1>>b0>>b1; ans=0;
			solve();
			cout<<ans<<'\n';
		}
	}
}
int main(){P1072::main();}
```

由于 $x$ 和 $b0$ 最小公倍数是 $b1$ ，所以 $x$ 肯定是小于 $b1$ 的，正常枚举即可。此时复杂度 $O(b1)$ 。

但是由于 $x$ 会重复枚举，效率并不高。注意到可以把 $x$ 的取值限制在 $\sqrt{b1}$ 内，通过操作一起枚举两个量，不遗漏的枚举所有可能取值。那么单次循环复杂度变为 $O(\sqrt{b1})$ 。

没听懂？具体操作看代码。


```cpp
#include <bits/stdc++.h>
long long ans,t,a1,b1,a0,b0;
namespace P1072
{
	using namespace std;
	
	inline int gcd(int a,int b){return b==0? a:gcd(b,a%b);}
	
	inline void solve()
	{
		for(int x=1;x<=sqrt(b1);x++)
		{
			if(b1%x) continue;//确保b1整除x
			int y=b1/x;//一次枚举两个量
			if(!(x%a1)&&gcd(x,a0)==a1&&x*b0/gcd(x,b0)==b1){ans++;}//由于跟朴素代码枚举方式有区别，所以要特判整除
			if(x==y) continue;//一样的量加一次即可
			if(!(y%a1)&&gcd(y,a0)==a1&&y*b0/gcd(y,b0)==b1){ans++;}//同上
		}
	}
	void main()
	{
		ios::sync_with_stdio(0); cin>>t;
		while(t--)
		{
			cin>>a0>>a1>>b0>>b1; ans=0;
			solve();
			cout<<ans<<'\n';
		}
	}
}
int main(){P1072::main();}
```

---

