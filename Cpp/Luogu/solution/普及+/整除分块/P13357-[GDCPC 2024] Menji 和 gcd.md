# [GDCPC 2024] Menji 和 gcd

## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>

## 题目描述

Menji 喜欢最大公约数，特别是最大公约数大的正整数对。

令 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数，多次给定 $L,R$，保证 $L<R$，求 $\max\limits_{L\leq x<y\leq R}\gcd(x,y)$。

## 样例 #1

### 输入

```
10
1 2
2 4
6 10
11 21
147 154
1470 1540
2890 3028
998244353 1000000007
34827364537 41029384775
147147147147 154154154154```

### 输出

```
1
2
3
7
7
70
126
1754385
5861340682
7007007007```

# 题解

## 作者：Zskioaert1106 (赞：5)

题目传送门：[P13357 [GDCPC 2024] Menji 和 gcd](https://www.luogu.com.cn/problem/P13357)

### 题目分析

首先问题可以转化为寻找最大的 $i$，使得 $i+R \bmod i \leqslant R-L$。意思是区间 $[L,R]$ 内至少有两个 $i$ 的倍数，最大的那个与 $R$ 的距离是 $R \bmod i$，次大的那个不能小于 $L$。

数据范围肯定是不够我们一个一个遍历的，考虑什么样的 $i$ 不需要看。

对于 $\lfloor \dfrac{R}{i} \rfloor = \lfloor \dfrac{R}{i+1} \rfloor$：

$$
\begin{aligned}
&i+1 + R \bmod (i+1) \\
=\ &i+1 + R - \lfloor\dfrac{R}{i+1}\rfloor \cdot (i+1) \\
=\ &i+1 + R - \lfloor\dfrac{R}{i}\rfloor \cdot i - \lfloor\dfrac{R}{i}\rfloor \\
=\ &(i + R \bmod i) +1 -\lfloor\dfrac{R}{i}\rfloor
\end{aligned}
$$

所以此时只需要看最大的一个 $i$ 是否满足条件，这样我们可以用整除分块。

整除分块就是通过枚举所有除 $n$ 下取整不同的 $i$ 来在 $O(\sqrt{n})$ 复杂度内快速求出一些信息的方法,在每次枚举时将 $i$ 变成 $\lfloor\dfrac{R}{\lfloor\dfrac{R}{i}\rfloor}\rfloor +1$，但是这样的话它遍历到的是每种 $i$ 中最小的一个，所以我们要比较的是 $\lfloor\dfrac{R}{\lfloor\dfrac{R}{i}\rfloor}\rfloor$。

这样一个复杂度合适的枚举方法就呼之欲出了。

### 代码实现

```cpp
#include<iostream>
using namespace std;
long long L,R,i,ans;
void solve(){
    for(i=1;i<=R-L;i++){
        i=R/(R/i);
        if(i+R%i<=R-L)ans=i; // 这里不需要取 max
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>L>>R;
        solve();
        cout<<ans<<'\n';
        ans=0;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/225875633)，时间复杂度 $O(T\sqrt{R})$。

---

## 作者：xiazha (赞：3)

最优解，取之。

转化题目，求一个最大的 $d$，满足 $\lfloor \frac{r}{d}\rfloor-\lfloor \frac{l-1}{d}\rfloor\ge 2$。

为便于叙述，设 $p=\lfloor \frac{r}{d}\rfloor$。

首先发现解决这个问题无非两种方法，一个是枚举 $p$，另一个是枚举 $d$。

枚举 $d$ 是简单的，考虑枚举 $p$ 该怎么做。

此时我们需满足两个条件：

1. $\lfloor \frac{r}{d}\rfloor=p$

1. $\lfloor \frac{l-1}{d}\rfloor\le p-2$

对于第一个条件，显然若想最大化 $d$ 则使 $d=\lfloor \frac{r}{p}\rfloor$ 可满足。

对于第二个条件，使 $\lfloor \frac{l-1}{d}\rfloor = p-1$ 最大的 $d$ 为 $\lfloor \frac{l-1}{p-1}\rfloor$，则满足第二个条件需 $d>\lfloor \frac{l-1}{p-1}\rfloor$。

综上，枚举 $p$，当 $\lfloor \frac{r}{p}\rfloor >\lfloor \frac{l-1}{p-1}\rfloor$ 时 $d$ 可取 $\lfloor \frac{r}{p}\rfloor$，从小到大找到第一个满足条件的 $p$ 即使最优答案。

然后考虑根号分治，

-  $r-l > 10^6$

  发现这时从 $\lfloor \frac{r}{r-l}\rfloor$ 开始枚举 $p$ 很快就能找到答案，最多不超过 $5$ 次（不会证为什么，直觉告诉我这么分治的）。

  -  $r-l \le 10^6$

 即 $d\le10^6$，枚举 $d$ 即可。

 按理来说时间复杂度是 $O(t \sqrt V)$，但是我怎么只跑了 4ms。

---

## 作者：qwqerty (赞：3)

首先那个 $\gcd$ 非常恶心。考虑把它弄掉。  
令答案为 $d$，最后选择的两个数为 $x$ 和 $y$。则有 $x=kd$，$y=(k+l)d$ 且 $l\perp k$。  
注意到若 $(k+l)d\le r$ 则一定有 $(k+1)d\le r$。所以答案选择 $kd$ 和 $(k+1)d$ 一定是最优的。   
式子可以写为 $l\le kd<(k+1)d\le r$。然后把 $k$ 和 $k+1$ 依次除过去得到 $\dfrac{l}{k}\le d\le \dfrac{r}{k}$ 和 $\dfrac{l}{k+1}\le d\le \dfrac{r}{k+1}$。  
下限取最小，上限取最大，然后枚举可做到 $O(\sum R)$。  
这样是过不了的，我们也没有想到什么优化方案。数据范围提示我们要使用 $O(\sum \sqrt{R})$。  
但我们有 $(k+1)d\le R$，所以 $k$ 和 $d$ 中必有一者不超过 $\sqrt{R}$。依次枚举 $k$ 和 $d$ 即可。  
[submit.](https://www.luogu.com.cn/record/225694113)

---

## 作者：Vct14 (赞：2)

刚好最近学了数论分块，来写篇题解。

有一个朴素的思路是暴力枚举因子，判断区间内是否有两个该因子的倍数，即是否有 $\left\lfloor\frac{R}{x}\right\rfloor-\left\lfloor\frac{L-1}{x}\right\rfloor\ge2$，然后更新答案。但是这样显然超时。

注意到我们判断的是 $\left\lfloor\frac{R}{x}\right\rfloor$ 和 $\left\lfloor\frac{L-1}{x}\right\rfloor$，考虑使用[数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)，将 $\left\lfloor\dfrac nx\right\rfloor$ 相同的数打包同时计算并更新答案。时间复杂度 $O(T\sqrt R)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    int t;cin>>t;
    while(t--){
        int L,R;cin>>L>>R;
        int l=1,ans=0;
        while(l<=R){
            int r=min(R/(R/l),(L-1)/l==0?LLONG_MAX:(L-1)/((L-1)/l));
            if(R/l-(L-1)/l>=2) ans=max(ans,r);
            l=r+1;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
注意：当 $l>(L-1)$ 时，$\left\lfloor\frac{L-1}{l}\right\rfloor=0$，则求 $\left\lfloor\dfrac{L-1}{\left\lfloor\frac{L-1}{l}\right\rfloor}\right\rfloor$ 会导致 RE，记得特判。

---

## 作者：封禁用户 (赞：0)

### 题目分析
不难发现，题目的意思就是寻找一个最大的 $d$，使得区间 $[L,R]$ 中存在两个或以上 $d$ 的倍数。

区间 $[0,L-1]$ 中 $d$ 的倍数有 $\lfloor \frac{L-1}{d} \rfloor$ 个，区间 $[0,R]$ 中 $d$ 的倍数有 $\lfloor \frac{R}{d} \rfloor$ 个，所以区间 $[L,R]$ 中有 $\lfloor \frac{R}{d} \rfloor-\lfloor \frac{L-1}{d} \rfloor$ 个 $d$ 的倍数，所以最后问题就是求最大的 $d$，使得 $\lfloor \frac{R}{d} \rfloor-\lfloor \frac{L-1}{d} \rfloor\ge2$。

另外容易发现，$d$ 的最大值不会超过 $R-L$，同时根据鸽笼原理，当 $d=\lfloor\frac{R-L}{2}\rfloor$ 时，区间 $[L,R]$ 内必定存在 2 个或以上 $d$ 的倍数，所以 $d$ 的值域区间是 $[\lfloor\frac{R-L}{2}\rfloor,R-L]$。

下面根据 $d$ 的取值进行分析处理：

1. 如果 $L\lt\lfloor\frac{R-L}{2}\rfloor$，则对于所有 $d$，都有 $\lfloor \frac{L-1}{d} \rfloor=0$，所以 $d$ 的最大值是 $\lfloor\frac{R}{2}\rfloor$，直接输出答案。

2. 如果 $(R-L)-\lfloor\frac{R-L}{2}\rfloor\le10^6$，直接从 $R-L$ 递减枚举所有的 $d$，找到第一个 $d$ 满足 $\lfloor \frac{R}{d} \rfloor-\lfloor \frac{L-1}{d} \rfloor\ge2$ 即可。

3. 如果 $(R-L)-\lfloor\frac{R-L}{2}\rfloor\gt10^6$，此时明显不能暴力枚举所有的 $d$。考虑到 $\lfloor \frac{R}{d} \rfloor$ 不同的值最多只有 $\sqrt{R}$ 个，同理 $\lfloor \frac{L-1}{d} \rfloor$ 不同值的数量也不会很多，所以考虑枚举 $\lfloor \frac{L-1}{d} \rfloor$ 和 $\lfloor \frac{R}{d} \rfloor$ 所有的不同值。

   具体地，设 $a=\lfloor\frac{L-1}{d}\rfloor$，则 $a$ 的值域区间是 $[\lfloor\frac{L-1}{R-L}\rfloor,\lfloor\frac{L-1}{\lfloor\frac{R-L}{2}\rfloor}\rfloor]$，枚举区间中所有的 $a$，计算所有满足 $\lfloor\frac{L-1}{d}\rfloor=a$ 的 $d$ 的数量 $c_a$，容易知道 $c_a=\lfloor\frac{L-1}{a}\rfloor-\lfloor\frac{L-1}{a+1}\rfloor$，这里需要注意 $d$ 的值域区间，如果 $\lfloor\frac{L-1}{a}\rfloor$ 或 $\lfloor\frac{L-1}{a+1}\rfloor$ 在 $d$ 的值域区间外，则需要根据 $d$ 的值域区间进行调整，另外还需要注意 $a=0$ 情况。枚举完成后，我们把 $(a,c_a)$ 这样的元组按 $a$ 从小到大存放到一个数组 $A$ 中。


   类似地我们可以枚举 $\lfloor\frac{R}{d}\rfloor$ 的情况，设 $b=\lfloor\frac{R}{d}\rfloor$，$b$ 的值域区间是 $[\lfloor\frac{R}{R-L}\rfloor,\lfloor\frac{R}{\lfloor\frac{R-L}{2}\rfloor}\rfloor]$，枚举区间中所有的 $b$，计算 $c_b$，然后把 $(b,c_b)$ 这样的元组按 $b$ 从小到大存放到数组 $B$ 中。


   上面两步枚举完成后，我们可以得到数组 $A$ 和 $B$，他们的内容大概如下：

   $$A=[(a_0,c_{a_0}),(a_1,c_{a_1})...]$$

   $$B=[(b_0,c_{b_0}),(b_1,c_{b_1})...]$$

   现在我们检测 $A$ 和 $B$ 的首项，如果 $b_0-a_0\ge2$，则答案就是 $R-L$，否则，对比 $c_{a_0}$ 和 $c_{b_0}$ 哪个较大，删除较小者，较大者保留并减去较小者，并维护记录一个所有被删的较小 $c$ 的和 $sum_c$，例如，如果 $c_{a_0}\lt c_{b_0}$，则把 $A$ 的第一项删除，而 $B$ 的第一项变成 $(b_0,c_{b_0}-c_{a_0})$，$sum_c=sum_c+c_{a_0}$，重复上面步骤，直到出现 $b_i-a_j\ge 2$ 为止，此时答案就是 $(R-L)-sum_c$。另外这里重复步骤中如果出现 $c_{a_j}=c_{b_i}$，则需删除两者，而 $sum_c$ 只需加上其中一个即可。


上面理论时间复杂度是 $O(T\sqrt{R})$。可能测试数据没有覆盖，加上枚举时从最大值递减枚举可较快跳出循环，实际执行所需时间只有 6ms。

---

