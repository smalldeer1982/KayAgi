# [CEOI 2016] kangaroo

## 题目描述

有一个园子，里面有 $n$ 个草丛排成一排，标号 $1\sim n$，有一个袋鼠，从 $s$ 出发，每次跳一步跳到一个其他的草丛，经过每个草丛恰好一次，最终到达 $t$。显然他会跳跃 $n-1$ 次。为了不被人类发现，袋鼠每次跳跃的方向必须与前一次不同。

具体地，如果他现在在 $now$，他是从 $prev $ 跳跃一次到达 $now$ 的，然后他跳跃一次到达 $next$：

- 那么如果 $prev<now$，就必须有 $next<now$；

- 如果 $now<prev$，就必须有 $now<next$。

问从 $s$ 到 $t$ 的方案数模 $10^9+7$ 的结果。

两个路线不同，当且仅当草丛被访问的顺序不同。

保证至少有一种方案。

初始时可以往任意方向跳。

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 2\times 10^3$，$1\le s,t\le n$

## 样例 #1

### 输入

```
4 2 3```

### 输出

```
2```

# 题解

## 作者：_lxy_ (赞：76)

[更好的阅读体验](https://www.cnblogs.com/lxy-2022/p/P5999-Solution.html)
#### 分析

一个妙妙的 trick。

首先原题可以转化成求有多少 $1 \sim n$ 的排列 $p$ 满足 $\forall i\in(1,n)$，$p_i$ 两边的数同时小于或大于 $p_i$，且 $p_1=s,p_n=t$。这类题都可以采用插入法 dp。

首先设状态，$dp_{i,j}$ 表示前 $i$ 个数，分成 $j$ 段的方案数。从小到大加入每一个数，考虑现在枚举到 $i$，若 $i \neq s$ 且 $i\neq t$，则可以分三种情况讨论：

1. 新开一段

   由于后加入的一定比 $i$ 大，所以以后插入在 $i$ 两边的数一定比 $i$ 大，所以总是合法。此时上一步操作完有 $j-1$ 段，所以有 $(j-1)+1=j$ 个空可以放。但是如果 $i>s$ 说明头不能放，同理 $i>t$ 说明尾不能放。因此有转移：
   $$
   dp_{i,j}=(j-[i>s]-[i>t]) \times dp_{i-1,j-1}
   $$

2. 接在某一段头/尾

   这样的话以后一定会有一个 $>i$ 的数接在 $i$ 另一侧，$i$ 两侧就有一个大于它的和一个小于它的，与题意不符，所以不会有这种情况。

3. 将两段连起来

   此时 $i$ 两侧的都比它小，与题意相符。上一步操作完有 $j+1$ 段，有 $j+1-1=j$ 个空可以插，因此有转移：
   $$
   dp_{i,j}=j\times dp_{i-1,j+1}
   $$

最后一定是整体一段，故答案为 $dp_{n,1}$。

#### 核心代码

```cpp
const int MAXN=2e3+7;
const int mod=1e9+7;
int n,s,t,dp[MAXN][MAXN];
signed main(){
    qread(n,s,t);int i,j;dp[1][1]=1;
    for(i=2;i<=n;i++){
        for(j=1;j<=i;j++){
            if(i!=s&&i!=t) dp[i][j]=(j*(dp[i-1][j+1])%mod+(j-(i>s)-(i>t))*dp[i-1][j-1]%mod)%mod;
            else dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
        }
    }printf("%lld\n",dp[n][1]);
    return 0;
}
```


---

## 作者：Aleph1022 (赞：61)

提供一个线性做法。

容斥信息应该是

$$
\begin{aligned}
&\quad\; \prod_{i=1}^{n-2} ([p_i<p_{i+1}](1-[p_{i+1}<p_{i+2}])+(1-[p_i<p_{i+1}])[p_{i+1}<p_{i+2}])\\
&= \prod_{i=1}^{n-2} ([p_i<p_{i+1}]+[p_{i+1}<p_{i+2}]-2[p_i<p_{i+1}][p_{i+1}<p_{i+2}])
\end{aligned}
$$

我们自然要考虑这样一个展开式如何划分出极长的 $<$ 段。注意到开头和结尾两段较为特殊，于是设 $F, G$ 表示序列中间的某一段 $[l, r]$，没有钦定 $p_{l-1}<p_l$，钦定了 $p_l<p_{l+1}<\dots<p_r$，是否钦定 $p_r<p_{r+1}$ 的关于长度的 GF；$F^\ast, G^\ast$ 表示在开头。可得方程

$$
\begin{cases}
F(x) = x^2 + x F(x) + x G(x) \\
G(x) = -x^2 - 2 x F(x) - x G(x) \\
F^\ast(x) = x + x F^\ast(x) + x G^\ast(x) \\
G^\ast(x) = -2 x F^\ast(x) - x G^\ast(x)
\end{cases}
$$

可以解得

$$
\begin{cases}
F(x) = \frac{x^2}{1+x^2} = \sum_{k\ge 1} (-1)^{k-1} x^{2k} \\
F^\ast(x) = \frac{x(1+x)}{1+x^2} = \sum_{k\ge 1} (-1)^{k-1} (x^{2k-1}+x^{2k})
\end{cases}
$$

因此容斥应该就是用两个 $F^\ast(x)$ 和任意个 $F(x)$ 拼接。注意到我们可以取 $s>t$，从而可以忽略仅有一段的情况。

从而我们将所有数划分为 $[1, t-1], [t+1, s-1], [s+1, n]$，取 $a = t-1, b = s-t-1, c = n-s$，用 $x,y,z$ 分别计量三种数。  
于是 $F^\ast(x)$ 会变成

$$
\sum_{k\ge 0} (-1)^k \left(\frac{x^{2k}}{(2k)!}+\frac{x^{2k+1}}{(2k+1)!}\right) = \frac12\left[(1-i)\mathrm e^{ix} + (1+i)\mathrm e^{-ix}\right]
$$

和 $\frac12\left[(1-i)\mathrm e^{iz} + (1+i)\mathrm e^{-iz}\right]$。$F(x)$ 会变成

$$
\sum_{k\ge 1} (-1)^{k-1} \sum_{u+v+w=2k} \frac{x^uy^vz^w}{u!v!w!} = 1-\frac12\left[\mathrm e^{i(x+y+z)}+\mathrm e^{-i(x+y+z)}\right]
$$

即需要计算

$$
\frac14\left[\frac{x^ay^bz^c}{a!b!c!}\right]\left[(1-i)\mathrm e^{ix} + (1+i)\mathrm e^{-ix}\right]\left[(1-i)\mathrm e^{iz} + (1+i)\mathrm e^{-iz}\right] \frac1{\frac12\left[\mathrm e^{i(x+y+z)}+\mathrm e^{-i(x+y+z)}\right]}
$$

由于 $a+b+c=n-2$，根据载谭 Binomial Sum 的经验，我们首先要计算

$$
\begin{aligned}
f(w) &= \frac1{\frac12[(1+w)+(1+w)^{-1}]} \bmod w^{n-1} \\
&= \frac{1+w}{1+w+\frac{w^2}2} \bmod w^{n-1} \\
&= -w f(w) - \frac{w^2}2 f(w) + 1 + w + \Delta_0 w^{n-1} + \Delta_1 w^n \\
&= \frac{1 + w + \Delta_0 w^{n-1} + \Delta_1 w^n}{1+w+\frac{w^2}2}
\end{aligned}
$$

从而我们只需要求出

$$
f(w-1) = \frac{2(w + \Delta_0 (w-1)^{n-1} + \Delta_1 (w-1)^n)}{1+w^2}
$$

的各项系数。记 $u_j = [w^j] f(w-1)$，答案就是

$$
\frac14\sum_{j=0}^{n-2} u_j \left[\frac{x^ay^bz^c}{a!b!c!}\right]\left[(1-i)\mathrm e^{ix} + (1+i)\mathrm e^{-ix}\right]\left[(1-i)\mathrm e^{iz} + (1+i)\mathrm e^{-iz}\right] \mathrm e^{j\cdot i(x+y+z)}
$$

另外注意到答案显然没有虚部，可以减少一些无用运算。

时间复杂度 $O(n)$。

---

## 作者：JiaY19 (赞：36)

**[更好的阅读体验](https://www.cnblogs.com/mfeitveer/p/16664136.html)**

感觉这样的 $\text{dp}$ 题还比较多，思路都比较的神奇。

个人感觉比较像区间 $\text{dp}$ 的一类变种。

但又和区间 $\text{dp}$ 的维护方式极不一样。

### 对于此类 $\text{dp}$

这一类 $\text{dp}$ 主要维护的是一个一个的块，可以理解成连通块。

将 $f_{i,j}$ 看作放置 $\text{i}$ 个元素，形成了 $\text{j}$ 个块的方案数。

有三类操作。

#### 1. 将某个块的元素个数加一

那么每一个块都有可能加一。

所以。

$$f_{i,j}=f_{i-1,j}\times j$$

#### 2. 新增一个块

类似插空的思路。

原来有 $j - 1$ 个块，所以有 $\text{j}$ 个空。

$$f_{i,j}=f_{i-1,j-1}\times j$$

#### 3. 合并两个块

与第二点类似，但是不能在两边插空。

所以还是只有 $\text{j}$ 个空。

$$f_{i,j}=f_{i-1,j+1}\times j$$

时间复杂度 $O(n^2)$。

这就是这一类问题的基本操作。

### 关于本题

我们发现，对于一般的 $\text{dp}$ 而言，不怎么好去维护这个问题。

就可以考虑一下上面所说的 $\text{dp}$。

我们从小到大去给元素排位置。

还是从三种情况去讨论。

1. 新增元素 

可以发现，对于一个新增加的元素，他的前面必然是比他小的，而后面必然会加一个更大的，所以没有这种情况。

2. 新增块

这种情况肯定是可以的，因为前后都没有元素。

3. 合并块

可以发现，合并两个块是，周围的两个元素一定都比新加入的元素小，所以都可以。

4. 一个细节

此题有 $\text{s,t}$ 的限制，这个不是很难，直接判一下就可以了。

代码实现还是比较简单的。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

int n , s , t , f[N][N];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

signed main()
{
    f[1][1] = 1;
    n = read() , s = read() , t = read();
    for(int i = 2;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            if(i == s || i == t)
            {
                f[i][j] += f[i - 1][j - 1] + f[i - 1][j];
                f[i][j] %= mod;
                continue;
            }
            int res = (i > s) + (i > t);
            f[i][j] += f[i - 1][j - 1] * (j - res);
            f[i][j] += f[i - 1][j + 1] * j;
            f[i][j] %= mod;
        }
    }
    cout << f[n][1] << endl;
    return 0;
}

```

---

## 作者：yyxmy (赞：25)

神级dp题，可以把题意转化一下。

我们需要求长度为$n$的满足以下性质的排列数，对于每个位置$i$填的值$a_i$, 要么其两边填的值都比它大， 要么其两边的填的值都比它小， 且起点为$s$, 终点为$t$; 

这种题有一种很常见的套路， 我们考虑一种插入型的dp。

按从小到大的顺序将数字填到排列中， 我们设一个$dp$状态为$dp[i][j]$表示前i个数被分成了$j$段的方案数， 在这里我们不要纠结填的位置， 因为每个数都是插进来的。对于新加进来的这个数， 我们会有几种选择：

1. 把前面的两段连接起来， 在这里因为是从小到大填的， 所以我们保证了它左右两边的值都要小于它， 有$dp[i][j] = dp[i - 1][j + 1] * (j + 1) * j$
2. 新开一段，后来插入它两端的的数一定会大于它， 所以也符合题目给的条件， 有
$dp[i][j] = dp[i - 1][j - 1]$

们要注意s 和 t需要特判， 因为它们最多只能连接一段， 具体细节可以康康代码。
然后考虑这种计数为什么不会算漏算重， 因为dp的过程是一个类似建笛卡尔树的过程， 
每一个排列都对应着唯一的笛卡尔树， 可以感性理解一下。
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n, s, t, dp[4111][4111];
signed main(){
    cin >> n >> s >> t;
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= i; j++){
            if(i != s && i != t){

            (dp[i][j] += 1ll * dp[i - 1][j + 1] * ((j + 1)* (j + (i > s) + (i > t))) % mod) % mod;
            if(j) (dp[i][j] += dp[i - 1][j - 1]) %= mod;
            }
            else {
                (dp[i][j] += dp[i - 1][j]) %= mod;
                if(j) (dp[i][j - 1] += dp[i - 1][j] * j) %= mod;  
            }
        }
    }
    cout << dp[n - 1][0] << endl;
    //cout << dp[4][2] << endl;
}
```
写完这道题之后，推荐写下

[CF704B](https://www.luogu.com.cn/problem/CF704B)  
[JOI Open 2016摩天大楼](https://loj.ac/problem/2743)

是差不多的套路。

---

## 作者：Mariposa (赞：22)

前言：$OI$中有一些奇思妙想，可能第一次自己想不出来，不要懊恼，不要沮丧，认真地去学习它，下次遇到就不怕了^_^

正文：考虑$dp$，设状态量$dp[i][j]$表示前$i$个数分$j$段（任意一段满足条件）的方法数。

先给出状态转移方程：

$$dp[i][j]=(j-c)*dp[i-1][j-1]+j*dp[i-1][j+1]\quad i\ne s,i\ne t,c=(i>s)+(i>t)$$

$$dp[i][j]=dp[i-1][j-1]+dp[i-1][j]\quad i=s\quad or\quad i=t$$

原因解释：

1.$i\ne s,i\ne t$时，可将$i$单独成段，插在任意位置（若$s$以过则不能插首，若$t$已过则不能插尾），则贡献为$(j-c)*dp[i-1][j-1]$。

或将$i$用于两段的合并，插在任意夹缝中，易知$i$比两段大，故操作合法，贡献为$j*dp[i-1][j+1]$。

2.$i=s\quad or\quad i=t$时，$i$只能放在首或尾，可与相邻段落合并，可单独成段，故贡献为$dp[i-1][j-1]+dp[i-1][j]$。

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e3+10;
const int mod=1e9+7;
int n,s,t;
ll dp[maxn][maxn];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int main(){
	n=read();s=read(),t=read();
	dp[1][1]=1;
	for(int i=2;i<=n;i++)
		if(i!=s&&i!=t)
			for(int j=1;j<=i;j++)
				dp[i][j]=(dp[i-1][j-1]*(j-(i>s)-(i>t))+dp[i-1][j+1]*j)%mod;
		else for(int j=1;j<=i;j++)
				dp[i][j]=(dp[i-1][j-1]+dp[i-1][j])%mod;
	printf("%lld\n",dp[n][1]);
	return 0;
}
```
深深地感到自己的弱小。



---

## 作者：LittleMoMol (赞：15)

## 前言

有些题目照常 DP 不是很好做，感觉像是区间 DP，但是怎么设状态都不好转移，那么可以考虑一种维护块儿的 DP，就是这道题要用到的知识点。

## 背景分析

如果每次跳跃的点的编号形成一个序列的话，那么这个序列满足“波浪形”，即 $a_1 < a_2,\ a_2>a_3, \ a_3<a_4 \dots$ 或者 $a_1>a_2,\ a_2<a_3, \ a_3>a_4 \dots$

那么转化问题，求 $1\sim n$ 的所有排列中，满足该排列构成的序列是“波浪形”的排列有几个。

## 前置知识

该题这种 DP 维护的是一个个块，可以设状态 $f_{i,j}$ 表示填好了 $1 \sim n$ 中的数，共有了 $j$ 个块。

比如：$f_{7,3}$ 表示前 7 个数里共有 3 个块，这 3 个块里面的信息可以是 $[1][2][3,4,5,6,7]$，也可以是 $[4,1,5][2,3][6,7]$，怎样都行。

每新填一个数，这个数可以开一个新块儿，也可以根据这个数合并之前的块儿，还可以将这个数加入已有块当中，我们具体分析。

### 加新块

如果加数字 $i$ 之前已经有了 $j - 1$ 个块，这些块儿会形成 $j$ 个空，那么这个数字 $i$ 单独形成的块儿就可以查到这 $j$ 个空中的一个，所以 $f_{i,j} = f_{i-1,j-1} \times j$。

### 合并块

如果加数字 $i$ 之前已经有了 $j + 1$ 个块，这些块儿会形成 $j+2$ 个空，但是，**如果你把数字 $i$ 放到最前面或者最后面，那么因为最前（后）面没有块儿，就无法合并，所以实际上合法的空只有 $j$ 个。**

所以方程是 $f_{i,j} = f_{i-1,j+1} \times j$。

## 这道题目

首先，对于每一个数不可能有**添加到已有块**的操作，举个例子：原来的局面是：$[2][1]$，你把数 3 加入到已有块变成 $[2,3][1]$，那么$[2,3]$ 这个块儿最终要和 $[1]$ 这个块儿合并，由于加入的数是递增的，最后 $[2,3,x,1]$ 必然有 $2<3<x$，不符合条件，感性理解。

我们依旧是填数，从 $1$ 填到 $n$，那么对于当前数 $i$，之前填的数都比这个数小，之后填的数都比这个数大，那么**加新块、合并块**这两个操作都是合法的，无论你放在哪里（**此时还不考虑 $s,t$ 的影响**）。

考虑到 $s$ 和 $t$，由于最终的块一定合并成了一个，且以 $s$ 开头、以 $t$ 结尾，那么他会影响到**加新块**的操作。

为什么？

如果 $s$ 已经填好了，那么 $s$ 所在的位置必然是**第一个块的首部**，此时你若加新块，**必然不能加到 $s$ 所在块的前面去**，因为这样做会使**最后合并的块无法满足 $s$ 开头**。

如果 $t$ 已经填好了，那么 $t$ 所在的位置必然是**最后一个块的尾部**，此时你若加新块，**必然不能加到 $t$ 所在块的后面去**，因为这样做会使**最后合并的块无法满足 $t$ 结尾**。

那么加新块的状态转移方程为：$f_{i,j} = f_{i-1,j-1}(j - [i>s] - [i>t])$。

$[\cdots]$ 表示如果中括号内条件满足返回 1，否则返回 0。

若 $i>s$ 满足，则其表示填 $i$ 的时候，$s$ 已经填好了，那么第一个块的前面就不能再放了，所以要减一，$i>t$ 同理。

对于**合并块**的操作无影响。

那么对于 $i=s,i=t$ 的情况，该怎么办呢？我们拿 $i=s$ 作说明，$i=t$ 同理。

$i=s$，如果要加新块，必然要加到最前面，所以只有一个位置合法，转移方程 $f_{i,j} = f_{i-1,j-1} \times 1$；如果要合并块，你也只能把 $s$ 放到第一个块的最前面，这样做块数是不变的，且只有一个合法位置，转移方程 $f_{i,j} = f_{i-1,j}$。

## Code

```cpp
#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;
const LL N = 2e3 + 10;
const LL mod = 1e9 + 7;

LL n, s, t;
LL f[N][N];

int main()
{
    cin >> n >> s >> t;
    f[1][1] = 1;
    for (LL i = 2; i <= n; i ++ )
    {
        for (LL j = 1; j <= i; j ++ )
        {
            if (i == s || i == t)
            {
                f[i][j] = (f[i][j] + f[i - 1][j - 1] + f[i - 1][j]) % mod;
                continue;
            }
            f[i][j] = (f[i][j] + f[i - 1][j - 1] * (j - (i > s) - (i > t))) % mod;
            f[i][j] = (f[i][j] + f[i - 1][j + 1] * j) % mod;
        }
    }
    cout << f[n][1] << endl;
    return 0;
}
```

## 尾声

自己做不会，看题解也挺蒙的，搞了一下午才明白。

完结撒花！

---

## 作者：lgswdn_SA (赞：8)

一个很有趣的 DP trick。 

考虑我们第 $i$ 个数插在哪里。一开始我们只有一个 $1$。设计状态 $f(i,j)$ 表示已经填入了 $1\dots i$，此时已经填的数形成了 $j$ 个连续段。

我们考虑转移。要么它连接两个连续段；要么它新开一个连续段。不能只接在一个连通块上，这样会导致后面更大的数插入到这里后出现问题。

1. 新开连续段

此时的贡献为 $j\times f(i-1,j-1)$。注意要特判当 $i > s$ 或者 $j < s$ 那么前面的系数不是 $j$ 而要减去 $1$ 或者 $2$。

2. 连接两个连续段

此时要考虑连接哪两个连续段。此时的贡献为 $j\times f(i-1,j+1)$。

对于边界情况需要特判。

```cpp
int n,s,t,f[N][N];
signed main() {
	n=read(), s=read(), t=read();
	f[0][0]=1;
	rep(i,1,n) {
		rep(j,1,i)
			if(i==s||i==t) f[i][j]=(f[i-1][j]+f[i-1][j-1])%mod;
			else f[i][j]=((j-(i>s)-(i>t))*f[i-1][j-1]+j*f[i-1][j+1])%mod;
	}
	printf("%lld\n",f[n][1]);
	return 0;
}
```

---

## 作者：KaguyaH (赞：7)

首先想到一个朴素 DP：$f_{i, j, k, 0/1}$ 表示 $i$ 个位置、起点为 $j$、终点为 $k$，当前方向为向左 / 向右的方案数，转移可以考虑插入一个位置作为新的终点。

这样子显然复杂度过高。考虑将 $s \to t$ 拆成 $s \to 1 \to t$，进而变为 $1 \to s$ 和 $1 \to t$。那么由于起点总在最左侧，我们并不需要 $j$ 这一维。前缀和优化一下可以在 $O(n^2)$ 的时空复杂度内 DP 出 $f_{i, k}$ 表示 $i$ 个位置、起点为 $1$、终点为 $k$ 的方案数。

接下来考虑合并。枚举 $(1, s), (s, t), [t + 1, n]$ 中分别有多少位置在 $1 \to s$ 这段中即可。这看似是 $O(n^3)$ 的，不过最坏运算次数大概是 $(\frac n 3)^3$，有 $\frac 1 {27}$ 的常数。加上一些有关内存访问的优化之后可以轻松通过本题，极限数据 0.8s 左右。

时间复杂度 $O(n^3)$（常数大概 $\frac 1 {27}$），空间复杂度 $O(n^2)$。

发现了之前一个模拟题的经验，写篇题解玩。

---

## 作者：Coros_Trusds (赞：5)

退役前最后一篇题解。

# 题目大意

有一个园子，里面有 $n$ 个草丛排成一排，标号 $1\sim n$，有一个袋鼠，从 $s$ 出发，每次跳一步跳到一个其他的草丛，经过每个草丛恰好一次，最终到达 $t$。显然他会跳跃 $n-1$次为了不被人类发现，袋鼠每次跳跃的方向必须与前一次不同。

具体地，如果他现在在 $now$，他是从 $prev $ 跳跃一次到达 $now$ 的，然后他跳跃一次到达 $next$：

- 那么如果 $prev<now$，就必须有 $next<now$；

- 如果 $now<prev$，就必须有 $now<next$。

问从 $s$ 到 $t$ 的方案数模 $10^9+7$的结果。

两个路线不同，当且仅当草丛被访问的顺序不同。

保证至少有一种方案初始时可以往任意方向跳。

# 题目分析

显然是一道计数 Dp。

题意可以看做：有一个 $1\sim n$ 的排列 $p$，这个排列不会出现长度超过 $2$ 的连续递增或递减的子串，求这个排列有多少个。

从小到大向这个排列 $p$ 插入数，令 $dp[i,j]$ 表示插到了第 $i$ 个数，序列被分成 $j$ 段的方案总数，**每一段内部都满足条件。**

然后推状态转移方程，有两种情况：

+ $i\neq s$ 且 $i\neq t$，此时 $i$ 插入在任何位置，因为从小到大插数，所以插的位置的两边都小于当前插入的这个 $i$，一定满足条件，当然也可以单独成段，这里必须满足这个数不能插到 $s$ 前面也不能插到 $t$ 后面，有 $dp[i,j]=dp[i-1,j-1]\times (j-[i>s]-[i>t])+dp[i-1,j+1]\times j$。

+ $i=s$ 或 $i=t$，此时只能插在最前面或最后面，有 $dp[i,j]=dp[i-1,j-1]+dp[i-1,j]$。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;
const int N = 2005;
int dp[N][N];//插入到第 i 个数,序列被分成了 j 段时的方案数
int n,s,t;
int32_t main() {
    cin >> n >> s >> t;
    dp[1][1] = 1;
    for (int i = 2;i <= n; ++ i) {
        for (register int j = 1;j <= i; ++ j) {
            if (i == s || i == t) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                dp[i][j] %= mod;
            } else {
                dp[i][j] = (dp[i - 1][j + 1] * j) % mod + (dp[i - 1][j - 1] * (j - (i > s) - (i > t))) % mod;
                dp[i][j] %= mod;
            }
        }
    }
    cout << dp[n][1] << "\n";

    return 0;
}
```

---

## 作者：Yang818 (赞：5)

## 题目

每一次与之前的跳跃方向不一样。

把所有跳跃的点组合起来就是 $1-n$ 的一个排列，而这个排列会呈现出一个波浪形。

求一种排列，使得开头是 $s$ ，结尾是 $t$。

------------

## 分析

数据范围是 $2000$，如果暴力搜索，你自己可以算算要多少年。

我算了一下，大概要 $10^{5000}$ 年。

可以~~只能~~换一种想法，思考某个数字要填在哪个位置。

~~网上有些人叫它插入型dp，也有人叫它填坑型dp反正说法不一~~

设 $f(i,j)$ 表示填 $i$ 的时候分 $j$ 段。

方程式就是：
![11](https://cdn.luogu.com.cn/upload/image_hosting/u3pzpbz2.png)

其实就像我们小学时学的插板法。

别忘了取 mod！！！！

------------
程序可供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e3+10;
const int MOD=1e9+7;
int num,start,end;
long long g_k[MAXN][MAXN];
int main(){
	cin>>num;
	cin>>start;
	cin>>end;
	g_k[1][1]=1;
	for(int i=2;i<=num;i++){
		if(i!=start&&i!=end)
			for(int j=1;j<=i;j++)
				g_k[i][j]=(g_k[i-1][j-1]*(j-(i>start)-(i>end))+g_k[i-1][j+1]*j)%MOD;
		else
			for(int j=1;j<=i;j++)
				g_k[i][j]=(g_k[i-1][j-1]+g_k[i-1][j])%MOD;
	}
	cout<<g_k[num][1];
	return 0;
} 
```

2022-3-5 upd: 代码错了，抱歉

---

## 作者：程门立雪 (赞：4)

## kangaroo 题解

#### 转化题意：

我们需要求满足以下条件的序列的数目：

1. 长度为 $n$。
2. 如果当前为第 $i$ 个数，第 $i-1$ 和 $i + 1$ 个数要么同时大于第 $i$ 个数, 要么同时小于第 $i$ 个数。

#### 题解：

设 $f_{i, j}$ 表示 前 $i$ 个数分 $j$ 段且任意一段满足要求的方法数。

1. 当 $i \not = s$，$i \not = t$ 时，可以将 $i$ 看做单独的一段，可以插在任意位置。若 $i > s$ 就不能插在首，若 $i > t$ 就不能插在尾，所以分别要减去 $1$ 个方案数。贡献为 $(j - c)\times f_{i - 1, j - 1}$，$c = (i > s) + (i > t)$。

   $i$ 还可以用作两端的合并，因为 $i$ 为从小到大枚举，一定比两边大，所以一定是可以合并的，贡献为 $j \times f_{i - 1, j +1}$。

   所以, $f_{i, j} = (j - c) \times f_{i - 1, j - 1} + j \times f_{i- 1, j +1}$。

2. 当 $i = s$，$i = t$ 时，$i$ 只能放在首或尾，或者单独成一段。
   $f_{i, j} = f_{i-1, j - 1} + f_{i - 1, j}$。
   
   
```c
#include <iostream>
#include <cstdio>
#define orz cout << "AK IOI"
#define int long long 

using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e3 + 10;

inline int read()
{
	int f = 0, x = 0; char ch = getchar();
	while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline void print(int X)
{
	if(X < 0) {X = ~(X - 1); putchar('-');}
	if(X > 9) print(X / 10);
	putchar(X % 10 + '0');
}
int n, s, t, f[maxn][maxn];
signed main()
{
	
    n = read(), s = read(), t = read();
    f[1][1] = 1;
    for(int i = 2; i <= n; i++)
    {
    	if(i != s && i != t)
			for(int j = 1; j <= i; j++)
				f[i][j] = (f[i - 1][j - 1] * (j - (i > s) - (i > t)) + f[i - 1][j + 1] * j) % mod;
		else 
		for(int j = 1; j <= i; j++)
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
	}
	print(f[n][1]); 
	return 0;
}

```

   

---

## 作者：Dita (赞：2)

[题面](https://www.luogu.com.cn/problem/P5999)

> 生成一个长度为 n 的排列，给定排列的第一个和最后一个元素，同时要求该排列的每个数至少都满足以下的一条性质：
>
> - $a_{i} < a_{i + 1}~ \&\&~a_{i} < a_{i - 1}$
> - $a_i > a_{i + 1}~\& \&~a_i > a_{i - 1}$
>
> 求有多少种合法的排列 ?

一道奇妙的 dp 题。 

**solution**

插数 dp。

我们可以从小到大向序列中插数。

**状态：**$f_{i, j}$ 表示插到了第  $i$ 个数，将序列分成了 $j$ 段，并且每一段都符合条件的方案数。

**转移：** 

- 当 $i\neq s$，$i\neq t$ 时。

$f_{i, j} = (j - (i > s) - (i > t)) \times f_{i - 1,j - 1} + j\times f_{i - 1,j + 1}$

当插入的数不是起点或终点的时候。

插入的数可以插入原来两段之间把两段连起来，也可以单独成段。

**注意：** 当插入的数比起点大的时候不能插入到最左边，因为数是从小到大插入的，如果比起点大证明起点已经插入了，如果比终点大的时候同理也不能插入到最右边。

- 当 $i = s$ 或 $i=t$ 时。

$f_{i, j} = f_{i - 1, j - 1} + f_{i - 1, j}$

当插入的时候是起点或终点的时候。

插入的数只能放在两边，可以单独成段，也可以与已有的段合并。

**注意转移时候数可插入的位置个数，很容易出错。**

**code**

```c++
/*
work by:Ariel_
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#define int long long
#define rg register
using namespace std;
const int mod = 1e9 + 7;
const int MAXN = 2e3 + 5;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, s, t, f[MAXN][MAXN];
signed main(){
   n = read(), s = read(), t = read();
   f[1][1] = 1;
   for (int i = 2; i <= n; i++) {
   	 for (int j = 1; j <= i; j++) {
   	     if (i != s && i != t) 
   	     f[i][j] = (f[i - 1][j - 1] * (j - (i > t) - (i > s)) + f[i - 1][j + 1] * j) % mod;
   	     else 
   	     f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % mod;
	   }
   }
   printf("%lld", f[n][1]);
   puts("");
   return 0;
}

```

---

