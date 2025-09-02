# Two Arrays

## 题目描述

You are given two integers $ n $ and $ m $ . Calculate the number of pairs of arrays $ (a, b) $ such that:

- the length of both arrays is equal to $ m $ ;
- each element of each array is an integer between $ 1 $ and $ n $ (inclusive);
- $ a_i \le b_i $ for any index $ i $ from $ 1 $ to $ m $ ;
- array $ a $ is sorted in non-descending order;
- array $ b $ is sorted in non-ascending order.

As the result can be very large, you should print it modulo $ 10^9+7 $ .

## 说明/提示

In the first test there are $ 5 $ suitable arrays:

- $ a = [1, 1], b = [2, 2] $ ;
- $ a = [1, 2], b = [2, 2] $ ;
- $ a = [2, 2], b = [2, 2] $ ;
- $ a = [1, 1], b = [2, 1] $ ;
- $ a = [1, 1], b = [1, 1] $ .

## 样例 #1

### 输入

```
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
10 1```

### 输出

```
55```

## 样例 #3

### 输入

```
723 9```

### 输出

```
157557417```

# 题解

## 作者：bwartist (赞：14)

![](https://cdn.luogu.com.cn/upload/image_hosting/9prh67vp.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/f3dess4i.png)

不难发现：把b数组所有数倒着放在 a 后面，就会形成一个长度为 2*m 的序列

所以题目转化成求组成一个长度为 2*m 的的不下降序列的方案数，序列中每个值为 1~n.

然后可以用dp解决。`dp[i][j]` 表示前 i 个数，最后一个数为 j 的方案数。

转移方程就很好推了，`dp[i][j]=sum[i-1][j]`。

`sum[i][j]` 表示前 i 个数，最后一个数小于等于 j 的总方案数，即 `dp[i][1]` 到 `dp[i][j]` 的和。

最后的答案就是 `sum[2*m][n]`.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mo=1e9+7;
int n,m;
typedef long long ll;
ll dp[25][1005],sum[25][1005];
int main(){
	scanf("%d%d",&n,&m);
	m*=2;
	for(int i=1;i<=n;i++)	dp[1][i]=1,sum[1][i]=i;
	for(int i=2;i<=m;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=sum[i-1][j];
			sum[i][j]=((sum[i][j-1]+dp[i][j])%mo+mo)%mo;
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++)	ans=((ans+dp[m][i])%mo+mo)%mo;
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：万弘 (赞：9)

我的$O(n^2m)$做法被爆踩了。但还是先讲一下这个做法。  
因为A单调递增，B单调递减，所以只要$A_n\le B_n,$则$i\in[1,n],A_i\le B_i$
所以只需要考虑每一对$A_n\le B_n$的贡献。  
先dp预处理`a[i][j]表示长度为i且结尾是j的单调递增序列数`，转移就暴力枚举前一个数，即$f[i][j]=\sum_{k=1}^jf[i-1][k]$  
同理预处理`b[i][j]表示长度为i且结尾是j的单调递减序列数`  
那么每一对$(A_n,B_n)\ (A_n\le B_n)$的贡献就是$a[m][A_n]\times b[m][B_n]$.暴力枚举并统计即可。时间复杂度$O(n^2m)$,足以AC。
[code](https://codeforces.com/contest/1288/submission/68835487)

DxTsT大佬提供了更nb的方法：  
结论：$a[m][i]=C_{m+i-2}^{m-1},b[m][i]=C_{m+n-i-1}^{m-1}$,证明是用隔板法 ~~O(EIS)~~

显然先可以预处理阶乘和逆元求组合数。  
统计答案的时候同样可以优化：
$$ans=\sum_{i=1}^n\sum_{j=1}^i C_{m+j-2}^{m-1}\times C_{m+n-i-1}^{m-1}$$
预处理$C_{m+j-2}^{m-1}$的前缀和$sum[i]=\sum_{j=1}^iC_{m+j-2}^{m-1}$
$$ans=\sum_{i=1}^nC_{m+n-i-1}^{m-1}\times sum[i]$$
时间复杂度$O(n+m)$
[code](https://codeforces.com/contest/1288/submission/68849020)

---

## 作者：培淇2021 (赞：5)

- 前言

这道题好像在哪里见过！

花絮的代码有密码保护。

- 题意

有两个长度为 $m$ 的数列 $a,b$，它们的所有元素都在 $1\sim n$ 之间。

其中 $a$ 非严格单调递增，$b$ 非严格单调递减。

而且对任意的 $1\le i\le m$，都有 $a_i\le b_i$。

求构造 $a,b$ 的方案数对 $10^9+7$ 取模的值。

- 思路

首先，我们用线段图表示 $a,b$，下图中上面的为 $b_i$，下面的为 $a_i$，参数为 $m=5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wjd6s70m.png)

通过这张图，可以发现保证 $a_m\le b_m$ 即可。

因为 $a_1\le a_2\le ...\le a_m$，$b_m\le b_{m-1}\le ...\le b_1$。

所以只要 $a_m\le b_m$，

就有 $a_1\le a_2\le ...\le a_m\le b_m\le b_{m-1}\le ...\le b_1$。

还可以发现 $a_i,b_i$ 只能由 $a_{i-1},b_{i-1}$ 影响，所以考虑二维 `dp`。

- 花絮 1

我们设 `f[i][j][k]` 表示目前是 $a_i,b_i$ 时，$a_i$ 为 $j$，$b_i$ 为 $k$ 时的方案数。

可以发现这个状态要由 `f[i-1][...][...]` 转移，

所以枚举比 $j$ 小的 $x$，比 $k$ 大的 $y$，注意这两个都是非严格比大小（类似这种）。

然后就 `f[i][j][k]+=f[i-1][x][y]`。

初始状态为 `f[1][i][j]`，由意义得全是 $1$。

答案为所有 $x\le y$ 的 `f[n][x][y]` 之和。

时间复杂度为 $O(mn^4)$，空间复杂度为 $O(mn^2)$。

结果！空间没爆，时间爆炸，如何优化？

我们又发现，把这个 $x,y$ 点对看成平面直角坐标系上的点，区域就是矩形！矩形变一下可以看成删除、加上一个 $1\times t$（$t$ 是一个变量）的矩形，这个可以 $O(n^2)$ 预处理！

或者更简单点，这不就是个二维前缀和的板子吗！时间复杂度也一样。

所以我们可以在每次循环时，处理一下 条形区域和/二维前缀和，下一次循环时就可以用到了。

时间复杂度 $O(mn^2)$，量级 $10^7$。

[代码](https://www.luogu.com.cn/paste/mv1gk5po)

- 思路+

但是，继续看这张图，我们会发现 $a,b$ 好像被**隔板**（伏笔）隔开了一样，没有重要的关系！

所以，我们发现，可以两边都 dp 一下，最后乘法原理！

- 花絮 2

下面表达的都是 $a_i$，因为 $a,b$ 对称。

我们设 `f[i][j]` 表示目前是 $a_i$ 时，$a_i$ 为 $j$ 时的方案数。

可以发现这个状态要由 `f[i-1][...]` 转移。

所以枚举比 $j$ 小的 $k$，注意这两个都是非严格比大小（类似这种）。

然后就 `f[i][j]+=f[i-1][k]`。

我当时做这道题的时候，初始状态是 `f[0][1]=1`，这样从 $1$ 开始循环即可。

对答案，枚举 $i,j$，其中 $i\le j$，则不妨设 $a_m=i,b_m=j$。

则由乘法原理，答案应该加上 `f[m][n-j+1]*f[m][i]`。

时间复杂度为 $O(mn^2)$，空间复杂度为 $O(mn)$。

其实这个也可以用前缀和优化。

那么时间复杂度就 $O(n^2)$，量级 $10^6$。

[代码](https://www.luogu.com.cn/paste/mv1gk5po)

- 思路++

思考一下，`f[i][j]` 可不可以有简便求法？

我们把它的差分数列 $t_i$ 求出来，就可以发现 $t_1=0,\displaystyle \sum_{k=1}^it_k=j$。

这个好像球盒问题！所以我们就可以这样理解！

就是相同的球有 $j$ 个，有 $i$ 个不同的盒子，现在每个盒子里没有要求，要求方案数，就可以用球盒问题解。

换句话说，是[这道题](https://www.luogu.com.cn/problem/P5824)的 $\text{VII}$ 部分，就可以用**隔板**法来做了。

我们套公式，可得 $\displaystyle f_{i,j}=C_{i+j-2}^{i-1}$。

所以这道题就变成了数数题~~好像原来就是数数题啊~~

所以答案就是 $\displaystyle \sum_{i=1}^n\sum_{j=i}^n C_{m+i-2}^{m-1}\times C_{m+n-j-1}^{m-1}$。

- 花絮 3

根据这个式子，预处理阶乘和阶乘逆元，然后计算组合数即可。

时间复杂度 $O(n^2)$，常数小。 

其实这个也可以用前缀和优化。

那么时间复杂度就 $O(n)$，量级 $10^3$。

- 思路+++

既然变成了计数题，那就化简式子。

$\displaystyle \sum_{i=1}^n\sum_{j=i}^n C_{m+i-2}^{m-1}\times C_{m+n-j-1}^{m-1}$

$\displaystyle =\sum_{i=1}^nC_{m+i-2}^{m-1}\sum_{j=i}^n C_{m+n-j-1}^{m-1}$

$\displaystyle =\sum_{i=1}^nC_{m+i-2}^{m-1}\sum_{j=m-1}^{m+n-i-1} C_{j}^{m-1}$

根据组合恒等式 $\displaystyle \sum_{i=N}^MC_{i}^{N}=C_{M+1}^{N+1}$，可得这里的 $N=m-1,M=m+n-i-1$。

化简式子得：

$\displaystyle =\sum_{i=1}^nC_{m+i-2}^{m-1} C_{m+n-i}^m$

- 花絮 4

根据这个式子，预处理阶乘和阶乘逆元，然后计算组合数即可。

时间复杂度 $O(n)$，常数更小。

- 思路++++

组合意义 上线了。

我们考虑这个式子的组合意义，发现好像是 $(m+i-2)+(m+n-i)=2m+n-2$ 个位置，每个位置最多放一个 $1$，一共选 $2m-1$ 个 $1$ 的方案数？

下面的**球**的意思为 $1$。

为什么这么说？首先我们把 $m+i-2$ 当作一个**隔板**，把两端隔开，左边放 $m-1$ 个球，右边放 $m$ 个球。

所以，每一组放球的方案都对应着一种组合数相乘。

为什么？

因为当 $i=1$ 时，$m+i-2=m-1$，此时正好是左边全放满的方案数，右边也差不多。

哦！所以我们直接算 $C_{2m+n-2}^{2m-1}$ 就可以啦！快点写吧！！！

啊不对，不完全对。

为什么？因为算重了。

我们考虑极端情况，**最**左边放了 $m-1$ 个，**最**右边放了 $m$ 个。

那么我们发现，所有组合数相乘都可以表示这个方案！

我们又发现，既然左右是相对对称的，我们就可以只考虑左边。

所以我们看看只考虑左边怎么做。

既然组合数出了重复，答案又是组合数，我们只能......把这个重复替换成等效的简单一点的组合数求和。

刚才我们的式子是用选球，那么我们用这个重复机制，继续选球。

怎么选？我们会发现，只算左边的方案数重复的时刻在于隔板在靠右最后一个球（只算前 $m-1$ 个球）的右面会算重。

所以，我们可以想一下，如果我们就是前 $m-1$ 选一次，前 $m$ 选一次，一直到最右边 $2m+n-2$ 个选一次即可。

我们就可以列出这个式子：$\displaystyle \sum_{i=2m-1}^{2m+n-2}C_{i}^{2m-1}$

接下来发现还是那个组合恒等式！

根据组合恒等式 $\displaystyle \sum_{i=N}^MC_{i}^{N}=C_{M+1}^{N+1}$，可得这里的 $N=2m-1,M=2m+n-2$。

所以答案就是 $C_{2m+n-1}^{2m}$！

- 最终算法

$O(n)$ 求出一个阶乘两个阶乘逆元，再乘一下，时间复杂度 $O(n)$，我的代码这样写，此时是最优解。

其实可以打个表，把阶乘和阶乘逆元都打下来，$O(1)$，更优解。

- 彩蛋

还记得那张图吗？其实我们最终的算法在一开始就有了。

>首先，我们用线段图表示 $a,b$，下图中上面的为 $b_i$，下面的为 $a_i$，参数为 $m=5$。
>
>![](https://cdn.luogu.com.cn/upload/image_hosting/wjd6s70m.png)
>
>通过这张图，可以发现保证 $a_m\le b_m$ 即可。
>
>因为 $a_1\le a_2\le ...\le a_m$，$b_m\le b_{m-1}\le ...\le b_1$。
>
>所以只要 $a_m\le b_m$，
>
>就有 $a_1\le a_2\le ...\le a_m\le b_m\le b_{m-1}\le ...\le b_1$。

有没有发现，我们最后是合成了一个长度为 $2m$ 的一个非严格上升序列！所以就是从这个值域里选 $2m$ 个数，可以用**隔板**法！

>我们把它的差分数列 $t_i$ 求出来，就可以发现 $t_1=0,\displaystyle \sum_{k=1}^it_k=j$。
>
>这个好像球盒问题！所以我们就可以这样理解！
>
>就是相同的球有 $j$ 个，有 $i$ 个不同的盒子，现在每个盒子里没有要求，要求方案数，就可以用球盒问题解。
>
>换句话说，是[这道题](https://www.luogu.com.cn/problem/P5824)的 $\text{VII}$ 部分，就可以用**隔板**法来做了。
>
>我们套公式，可得 $\displaystyle f_{i,j}=C_{i+j-2}^{i-1}$。

至于为什么算出来是原来没计算重复的答案，那是因为上界需要枚举啊！枚举完之后用那个组合恒等式即可！

答案完全一致。

好的本篇题解到这里结束了，初次交稿时间 2022/7/16 10:38:41。

---

## 作者：MspAInt (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1288C)

先考虑怎么计算单调不降序列的个数，计数当然要 dp。设 $dp_{i,j}$ 表示长度为 $i$，最后一个数是 $j$ 的不降序列个数。转移很显然：$dp_{i,j}=\sum_{k=1}^j dp_{i-1,k}$。

这有什么用呢？考虑一个非常妙的转换。

根据题意：

$a_1\le a_2\le\dots\le a_{m-1}\le a_m$

$b_1\ge b_2\ge\dots\ge b_{m-1}\ge b_m$

$a_m\le b_m\le b_1$

因此 $a_1\le a_2\le\dots\le a_{m-1}\le a_m\le b_m\le b_{m-1}\le\dots\le b_2\le b_1$

这时只要求长度为 $2\times m$ 的不降序列个数即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=30,M=1e3+10,mod=1e9+7;
int n,m,dp[N][M];
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d",&m,&n);n<<=1;
    for(int i=1;i<=m;i++)dp[0][i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=1;k<=j;k++)
                dp[i][j]=(dp[i-1][k]+dp[i][j])%mod;
    printf("%d\n",dp[n][m]);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123912706)

---

## 作者：封禁用户 (赞：3)

### 题目传送门：

[洛谷](https://www.luogu.com.cn/problem/CF1288C)

[CF](https://codeforces.com/problemset/problem/1288/C)

### 分析：

题意翻译得很清楚，就不赘述了。

发现：

$a_{1} \le a_{2} \le a_{3} \le \cdots \le a_{n-1} \le a_{n}$

$b_{n} \le b_{n-1} \le b_{n-2} \le \cdots \le b_{2} \le b_{1}$

而 $a_{n} \le b_{n}$。

所以有 $1 \le a_{1} \le a_{2} \le a_{3} \le \cdots \le a_{n-1} \le a_{n} \le b_{n} \le b_{n-1} \le b_{n-2} \le \cdots \le b_{2} \le b_{1} \le m$。

所以令其初始数字为 $1$，其差分数组，必然为和不超过 $m-1$ 的自然数。

显然差分数组和原数组一一对应，所以原题转化为：**一个长为 $2n$ 的自然数序列，和不超过 $m-1$ 的方案数**。

故答案为：$C_{2n+m-1}^{m-1}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)
#define ll long long
#define N 3000010
const int mod = 1e9 + 7;
ll fac[N],inv[N];
int n,m;
int main()
{
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	F(i,2,3e6) fac[i] = fac[i-1] * i % mod;
	F(i,2,3e6) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	F(i,2,3e6) inv[i] = inv[i] * inv[i-1] % mod;
	read(m),read(n);
	write(fac[m-1+n*2] * inv[n*2] % mod * inv[m-1] % mod);
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：2)

模拟赛写的垃圾 $\operatorname{O}(n^2)$ 记搜。

------------

考虑 $\max\limits_{1\le i\le m} a_i\le\min\limits_{1\le i\le m}(b_i)$，所以直接枚举这两个数。

设 $dp_{i,j}$ 表示前 $i$ 个，第 $i$ 个为 $j$ 的方案数。

分别记搜 $a$，$b$ 方案数的乘积，求和即可。

复杂度最大为 $\operatorname{O}(n^2)$。

------------

真没想到一遍过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll n,m,ans,a[12][1005],b[12][1005];
inline ll dfsa(ll ad,ll val){
    if(ad==1)
        return 1;
    if(a[ad][val]!=-1)
        return a[ad][val];
    a[ad][val]=0;
    for(int i=1;i<=val;i++)
        a[ad][val]=(a[ad][val]+dfsa(ad-1,i))%mod;
    return a[ad][val];
}
inline ll dfsb(ll ad,ll val){
    if(ad==1)
        return 1;
    if(b[ad][val]!=-1)
        return b[ad][val];
    b[ad][val]=0;
    for(int i=val;i<=n;i++)
        b[ad][val]=(b[ad][val]+dfsb(ad-1,i))%mod;
    return b[ad][val];
}
int main(){
    memset(a,-1,sizeof(a));
    memset(b,-1,sizeof(b));
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            ans=(ans+dfsa(m,i)*dfsb(m,j)%mod)%mod;
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Mine_King (赞：2)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/CF1288C.html)

## Problem

[CF1288C Two Arrays](https://www.luogu.com.cn/problem/CF1288C)

**题目大意：**

构造两个长度为 $m$，值域为 $n$ 的序列 $a,b$，满足 $a$ 单调不降，$b$ 单调不升，且 $\forall i \in [1,m],a_i \le b_i$，求合法方案数。

## Solution

提供一种 $O(n)$ 做法。

发现有这样三条性质：

- $a_1 \le a_2 \le a_3 \le \cdots \le a_m$
- $b_1 \ge b_2 \ge b_3 \ge \cdots \ge b_m$
- $a_m \le b_m$

于是有：

$$a_1 \le a_2 \le a_3 \le \cdots \le a_n \le b_m \le b_{m-1} \le b_{m-2} \le \cdots \le b_1$$

也就是说，我们把 $b$ 翻转一下接到 $a$ 后面，原问题就转化成了求长度为 $2m$，值域为 $n$ 的单调不降序列的个数。

这个问题与“将 $2m$ 个相同的元素放到 $n$ 个集合中，允许有集合为空的方案数”双射。

上面这个问题显然可以用插板法解决，答案为 $\binom{2m+n-1}{n-1}$。

上面这个式子可以直接 $O(n)$ 预处理阶乘和阶乘的逆元，然后就做完了。


---

## 作者：qwq___qaq (赞：2)

首先，因为 $a$ 单调不降，$b$ 单调不升，可以将条件 $3$ 转化为 $a_m\le b_m$，由于我们需要维护 $a$，$b$ 的末尾的元素，可以考虑 `dp`：

维护 $a$：定义 $dp1_{i,j}$ 表示前 $i$ 个数构成的一个单调不降的序列的最后一个数为 $j$ 的方案数，因为 $a_i\le a_{i-1}$，所以 $dp1_{i,j}\gets\sum\limits_{k=1}^jdp1_{i-1,k}$；初始化，对于同一个元素，在第一位放它可以得到唯一的一种方案，所以 $dp1_{1,i\in[1,n]}\gets1$。

维护 $b$：同理，定义 $dp2_{i,j}$ 表示前 $i$ 个数构成的单调不升的序列的最后一个数为 $j$ 的方案数，所以 $dp2_{i,j}\gets\sum\limits_{k=j}^ndp2_{i-1,k}$，初始化 $dp2_{1,i\in[1,n]}\gets 1$。

因为 $a_m\le b_m$，所以答案就是 $\sum\limits_{i=1}^n\sum\limits_{j=i}^ndp1_{m,i}\times dp2_{m,j}$。

---

## 作者：_Life_ (赞：2)

### 题意
输入两整数 $n,m$，求有多少对正整数序列 $a_i,b_i$ 满足：
- $a_i,b_i$ 的长度为 $m$
- $a_i,b_i$ 中所有元素的值小于等于 $n$
- 对于所有 $1\le i\le m$，$a_i\le b_i$
- 序列 $a$ 单调不降，序列 $b$ 单调不升

答案对 $10^9+7$ 取模。

### 题解
**大力DP**
###### 状态
设状态 $dp[i][j][k]$，表示当前长度为 $i,a_i=j,b_i=k$ 的序列个数。
###### 边界
因为对于所有 $1\le i\le m$，$a_i\le b_i$，所以 $k\ge j$。
$$dp[1][j][k]=\begin{cases}0&(k<j)\\1&(k\ge j)\end{cases}$$
###### 转移
因为序列 $a$ 单调不降，序列 $b$ 单调不升，所以 $j$ 从小于等于 $j$ 的地方转移而来，$k$ 从大于等于 $k$ 的地方转移而来。得到柿子：
$$dp[i][j][k]=\sum_{p=1}^j\sum_{q=k}^ndp[i-1][p][q]$$
###### 优化
用上面的柿子硬算显然会 `TLE` ，观察柿子发现可以用二维前缀和优化，然后又发现这道题就这样做完了。

时间复杂度$O(n^2m)$

### 代码
示例代码加了滚动数组优化，请谨慎食用
```cpp
#include<cstdio>
#define MAXN 1005
#define int long long
#define mod 1000000007
using namespace std;
int n,m,dp[2][MAXN][MAXN],sum[2][MAXN][MAXN];
//dp[i][j][k] i=length,j=ai,k=bi (k>=j)
//dp[i][j][k]=sum(dp[i-1][1~j][k~n])
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			dp[1][i][j]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[1][i][j]=sum[1][i-1][j]+sum[1][i][j-1]-sum[1][i-1][j-1]+dp[1][i][j];
	for(int i=2;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			for(int k=j;k<=n;k++)
			{
				dp[i&1][j][k]=sum[(i-1)&1][j][n]-sum[(i-1)&1][j][k-1]-sum[(i-1)&1][0][n]+sum[(i-1)&1][0][k-1];
				dp[i&1][j][k]%=mod;
			}
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				sum[i&1][j][k]=sum[i&1][j-1][k]+sum[i&1][j][k-1]-sum[i&1][j-1][k-1]+dp[i&1][j][k];
	}
	printf("%lld",(sum[m&1][n][n]%mod+mod)%mod);
}
```

---

## 作者：OIerAlbedo (赞：1)

我觉得这道题难度比D要大呀，为什么C比D多做出来那么多人。

首先根据题目要求可以列出这样一个暴力方程 $ f[i][j][k] $ 表示前 $ i $ 个里，$ a_i $ 为 $ j $ , $ b_i $ 为 $ k $ 所能有的方案数，那么根据题目要求 $ k\ge j $ 有下面的转移方程。
$$
f[i][j][k]=\sum_{it=1}^j \sum_{jt=j}^{n} f[i-1][it][jt]
$$
然后发现这个方程直接做会T飞，但是我们发现上面的式子是可以前缀和（也不知道是不是这样定义）优化的，我们记 $ e[i][j][k] $ 为所有 $ it $ 小于等于 $ j $ 并且 $ jt $ 大于等于 $ k $的 $ f[i][it][jt] $的总和，那么容易得到 $ e[i][j][k]=e[i][j-1][k]+e[i][j][k+1]-e[i][j-1][k+1]+f[i][j][k] $ ,然后就可以用这个 $ e[i][j][k] $ 去优化了，然后就过了。
# Code
```cpp

#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
  long long x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
long long pow(long long x,long long y,long long p)
{
	long long ans=1;
	for (;y;y>>=1,x=x*x % p)
		if (y&1) ans=ans*x % p;
	return ans;
}
long long gcd(long long x,long long y)
{
	if (y==0) return x;
	long long ans=gcd(y,x % y);return ans;
}
long long MOD,sum,ans,m,n,i,j,jt,j2,j3,j4,e[11][1003][1003],f[11][1003][1003];
long long x;
int main()
{
	n=read();m=read();MOD=1e9+7;
	//f[1][1]=2;f[1][2]=1
	//f[2][1]=3,f[2][2]=2;
	//f[3][1]=3,f[3][2]=4;
	//f[3][1]=4,f[3][2]=5;
   // for (i=1;i<=n;i++) f[1][i]=n-i+1;	
	for (i=1;i<=n;i++)
	   for (j=n;j>=i;j--) 
	       {
	       	x=e[1][i-1][j]+e[1][i][j+1]-e[1][i-1][j+1]+1;x=x% MOD;x=(x+MOD) % MOD;
	       e[1][i][j]=x;
		   f[1][i][j]=1;
	       }
	for (i=2;i<=m;i++)
	    {
	/*	for (jt=1;jt<=n;jt++)
		   for (j2=n;j2>=jt;j2--)
		      for (j3=1;j3<=jt;j3++)
		         for (j4=max(j3,j2);j4<=n;j4++)
		            f[i][jt][j2]+=f[i-1][j3][j4];*/
		/*2,1,2->1,2&1,3
		2,2,1->*/
	   for (jt=1;jt<=n;jt++)
	      {
	      	
	       for (j2=n;j2>=jt;j2--)
	           {
			   f[i][jt][j2]=e[i-1][jt][j2];
			   x=e[i][jt-1][j2]+e[i][jt][j2+1]-e[i][jt-1][j2+1]+f[i][jt][j2];x=(x % MOD+MOD) % MOD;
			   e[i][jt][j2]=x;
		       }
	      }
	}
	for (i=1;i<=n;i++)
	   for (j=i;j<=n;j++)
	       {
	      ans=(ans+f[m][i][j]) % MOD;
	      } 
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：beyoursven (赞：0)

说一个和现有题解不同的思路

### 状态定义
$dp[i][j]$ ：两序列长度为 $i$，且两序列第 $i$ 个数字之差为 $j$，即 $b_i-a_i==j$ 时的方案数，$1\le i \le m,0 \le j \le n-1$

### 状态转移
$dp[i][j]=\sum_{k=j}^{k=n-1}dp[i-1][k]*(k-j+1)$

其中 $k-j+1$ 表示从末尾数字之差为 $k$ 的序列对，加一个数字后末尾数字之差变为 $j$的序列对的数量

### 状态初始化
$dp[1][j]=n-j,0 \le j \le n-1$

### 空间复杂度
$O(n*m)$

### 时间复杂度
有 $n*m$ 个状态，每个状态最多花费 $O(n)$ 时间转移

暴力DP的时间复杂度为 $O(n^2*m)$

前缀和优化转移后的时间复杂度为 $O(n*m)$

### 后记
当我看到官方题解时，顿时觉得自己就很SB

把两个序列排成 $a_1,a_2,...,a_m,b_m,b_{m-1},...,b_1$

这是一个长度为 $2m$ 的不下降序列

问题可以直接转换成，求从 $1$ 到 $n$ 中选取 $2m$ 个元素的**可重组合**数 $C_{n+2m-1}^{m}$

这样子就可以直接 $O(n+m)$ 用线性求逆元的方法求出所有阶乘的逆元

我是SX

---

## 作者：YLWang (赞：0)

这种傻逼计数题居然写了20min。没脸见人了。

首先我们观察到，因为$a$单调不降，$b$单调不升，所以$a_i \leqslant b_i$ 等价于$a_m \leqslant b_m$

为了思考方便，我们不妨将$a$翻转一下，将其变为单调不升。$b$同理。

我们现在只需要枚举$a$与$b$的开始，就可以算出两者各自的方法数，乘一下得到这种开始下的总方案数。

计算的过程是个很经典的问题，可以使用dp来做。

看到jly好像用了个排列组合方法秒了这题，到时候去学习一下。

```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define reaD() read()
#define pb push_back
#define mkp make_pair
#define mst(a,b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(register int i = (k); i >= (j); i--)
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define DEBUG fprintf(stderr, "***IAKIOI***\n")
#define CDEBUG cerr << "***IAKIOI***" << endl;
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
const int MOD = 1000000007; //
using namespace std;
inline void ckmax(int &a, int b) {a = max(a, b);}
inline void ckmin(int &a, int b) {a = min(a, b);}
inline void addmod(int &a, int b) {int t = a + b; a = (t >= MOD ? t - MOD : t); }
inline int read() {
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag=-1;
    for(;c>='0'&&c<='9';num=num*10+c-48,c=getchar());
    return num*flag;
}
const int MAXN = 1005, MAXM = 15;
int n, m, dp[MAXN][MAXM][MAXN];
signed main()
{
	cin >> n >> m;
	// a_1 <= b_1, a_i >= a[i+1], b_i <= b[i+1]
	For(i, 1, n) {
		dp[i][1][i] = 1;
		For(j, 1, m) {
			if(j != 1) 
				For(k, i, n)
					dp[i][j][k] = dp[i][j-1][k];
			For(k, i, n)
				addmod(dp[i][j][k], dp[i][j][k-1]);
		}
	}
	long long ans = 0;
	For(i, 1, n) {
		For(j, i, n) {
			ll v1 = dp[n-i+1][m][n], v2 = dp[j][m][n]; 
			ans = (ans + 1ll * v1 * v2) % MOD;
		}
	}
	cout << ans << endl;
    return 0;
}



```

---

