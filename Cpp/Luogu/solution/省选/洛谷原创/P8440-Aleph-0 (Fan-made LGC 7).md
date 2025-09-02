# Aleph-0 (Fan-made LGC 7)

## 题目背景

Rolling_Code 是一个喜欢音游的女孩子。

![](https://cdn.luogu.com.cn/upload/image_hosting/rnkqui18.png)

Rolling_Code 打 $\aleph_0$ 的成绩如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/q298dfbe.png)

~~然而这并不是 IN。~~

慢报：Rolling_Code 将 Aleph-0 [IN 15(15.7)] All Perfect 了！

## 题目描述

LeaF 作为数学教师开办了一系列完美数学课堂，参加的学生包括了：Rolling_Code，你，美穗。助教：琪露诺。

第一节课，考试。

做出这道题目的同学可以获得特殊版 $\aleph_0$ 的率先游玩机会哦！——LeaF

~~Aleph-0 (Legacy - SP Lv.?)~~

Rolling_Code 对音游非常感兴趣，所以也非常想要获得这首曲子。但是它打开题面的时候震惊了：

> $f(x)=\begin{cases}0&x=0\\1&x=1\\2f(\frac{x}{2})&2|x\operatorname{and} x>0 \\ 2f(\frac{x-1}{2})+\frac{2}{x-1}f(\frac{x-1}{2})+x&\text{otherwise}\end{cases}$

求 $S=\left(\sum\limits_{i=0}^{r} f^k(i)\right)\bmod (10^9+7)$。

其中 $f^k(i)=(f(i))^k$。

本来是想要求 $r\rightarrow\aleph_0$ 的答案，可惜了啊，没有被定义，那就把 $r$ 范围放小一点吧。——LeaF

由于某些原因，LeaF 定义 $0^0=1$。

为了增加趣味，LeaF 还增加了多次对于 $r,k$ 的询问。

Rolling_Code 不会做，因此找你求助。


## 说明/提示


**本题采用捆绑测试。**

**本题有多组数据。**

对于 $100\%$ 的数据，保证 $1\le t\le 10^3,1\le r\le 2^{63}-1,0\le k\le 30$。

Subtask 1：对于 $5\%$ 的数据，保证 $1\le t\le 100,1\le r\le 10^4$。

Subtask 2：对于 $10\%$ 的数据，保证 $1\le t\le 1000,1\le r\le 10^5$，**依赖于 Subtask 1**。

Subtask 3：对于 $10\%$ 的数据，保证 $1\le t\le 1000,1\le r\le 10^6,k$ 为定值。

Subtask 4：对于 $25\%$ 的数据：保证 $k=2$。

Subtask 5：对于最后 $50\%$ 的数据，无特殊限制，**依赖于 Subtask 1，2，3，4**。

---

### 样例解释

$f_0=0,f_1=1,f_2=2,f_3=6,f_4=4$。

对于 $r=4,k=2$ 的情况，$\text{Ans}=0^2+1^2+2^2+6^2+4^2=57$。

## 样例 #1

### 输入

```
5
1 2
14 2
51 2
4 2
1919810 2```

### 输出

```
1
6480
495741
57
936062395```

## 样例 #2

### 输入

```
5
43752 25
26701 25
43734 25
37553 25
67839 25```

### 输出

```
252345090
86394269
406573405
129371352
118835650```

# 题解

## 作者：donghanwen1225 (赞：9)

$\text{upd on 2022.08.02}$：修复一些 LaTeX 的错误，以及 phigros 萌新已经把 Aleph-0 打到 S 959057（acc 98.57%）了（

------------

$\text{step 1.}$ 我们考虑 $f(x)$ 的值代表了什么。

我们先进行一些打表：

$$\begin{aligned}f(0)&=0\\f(1)&=1\\f(2)&=2f(1)=2=2\times1\\f(3)&=2f(1)+
\dfrac{2}{3-1}f(1)+3=6=3\times2\\f(4)&=2f(2)=4=4\times1\\f(5)&=2f(2)+\dfrac{2}{5-1}f(2)+5=10=5\times2\\f(6)&=2f(3)=12=6\times2\\f(7)&=2f(3)+\dfrac{2}{7-1}f(3)+7=21=7\times3\end{aligned}$$

由此可以猜想：$f(x)=x\times\text{popcount}(x)$。以下归纳证明此式：

$(1)$ 当 $n=0,1$ 时，有 $f(0)=0,f(1)=1$ 满足此式。

$(2)$ 假设 $n\leq k\;(k\geq 1)$ 时均已满足此式。考虑当 $n=k+1$ 时，

若 $k+1$ 是奇数，则 $k$ 是偶数且 $f(k+1)=2f\left(\dfrac{k}{2}\right)+\dfrac{2}{k}f\left(\dfrac{k}{2}\right)+(k+1)=f(k)+\dfrac{f(k)}{k}+(k+1)=(k+1)(\text{popcount}(k)+1)=(k+1)\text{popcount}(k+1)$，满足此式；

若 $k+1$ 是偶数，则 $f(k+1)=2f\left(\dfrac{k+1}{2}\right)=(k+1)\text{popcount}\left(\dfrac{k+1}{2}\right)=(k+1)\text{popcount}(k+1)$，也满足此式。

于是题目所求的式子即为 $\sum\limits_{i=0}^{r}i^k\text{popcount}^k(i)$。

$\text{step 2.}$ 注意到 $r$ 很大，但 $k$ 较小，这提示我们思考数位 dp。

设 $dp_{i,j,k}$ 表示不超过 $2^i-1$ 的数中，满足 $\text{popcount}(x)=j$ 的 $x$ 的 $k$ 次方和。注意到我们没有把 $j^k$ 也乘进去，这是为了后面方便。

考虑当 $k=0$ 时，$dp_{i,j,0}$ 就表示 $\text{popcount}$ 为 $j$ 的数字个数，显然应当为 $C_{i}^{j}$。

考虑当 $i=1$ 时，我们只考虑 $1$，则有 $dp_{1,1,k}=1$。

接下来，我们考虑如何由 $i-1$ 的状态转移到 $i$ 的状态。首先我们令 $dp_{i,j,k}=dp_{i-1,j,k}$，则只需考虑形如 $2^{i-1}+p\;(p\in[0,2^{i-1}-1])$ 的数的贡献；

对于每个满足 $\text{popcount(p)}=j$ 的 $p$，它的贡献是 $(2^{i-1}+p)^k(j+1)^k=(j+1)^k\left(\sum\limits_{l=0}^{k}C_{k}^{l}\left(2^{i-1}\right)^lp^{k-l}\right)$。

观察此式，如果不考虑 $(j+1)^k$，后面式子中 $p^{k-l}$ 之和应当为 $dp_{i-1,j,k-l}$。这意味着 $dp_{i,j+1,k}=\sum\limits_{l=0}^{k}C_{k}^{l}\left(2^{i-1}\right)^ldp_{i-1,j,k-l}$。

于是我们就完成了 $dp_{i,j,k}$ 的预处理。这部分的时间复杂度为 $O\left(\log^2rk^2\right)=63^2\times30^2\approx3.5\times10^6$。

接下来对于每次询问的 $r$，我们只需对于其每个二进制位，用数位 dp 的方法进行计算。转移与上述过程一样，但是要注意统计当前已经考虑过的部分之和与二进制位为 $1$ 的个数，并把这部分贡献加入（具体参考代码的主函数部分）。

时间复杂度为 $O(t\log^2rk)\approx1.2\times10^8$（由于 $k$ 是给定的，可以减少一个枚举 $k$ 的复杂度），因为常数很小，可以通过此题。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1000000007;
typedef long long ll;
int t,k,fj[65];ll r,dp[65][65][31],C[65][65];
ll ksm(ll d,ll cf)
{
	ll ans=1;
	while(cf)
	{
		if(cf&1) ans=ans*d%mod;
		d=d*d%mod;cf>>=1;
	}
	return ans;
}
void init()
{
	C[0][0]=1;
	for(int i=1;i<=64;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=1;i<=30;i++) dp[1][1][i]=1;
	for(int i=1;i<=63;i++)for(int j=0;j<=i;j++)dp[i][j][0]=C[i][j];
	for(int i=2;i<=63;i++)
		for(int j=1;j<=i;j++)
			for(int k=1;k<=30;k++)
			{
				dp[i][j][k]=dp[i-1][j][k];ll q=(1ll<<(i-1))%mod;
				if(j==1){dp[i][j][k]=(dp[i][j][k]+ksm(q,k))%mod;continue;}
				for(int l=0;l<=k;l++)
					dp[i][j][k]=(dp[i][j][k]+C[k][l]*ksm(q,k-l)%mod*dp[i-1][j-1][l]%mod)%mod;
			}
}
int main()
{
	init();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld%d",&r,&k);
		if(k==0){printf("%lld\n",(r%mod+1)%mod);continue;}
		int ws=0;ll tr=r;memset(fj,0,sizeof(fj));
		while(tr){fj[++ws]=tr&1;tr>>=1;}
		int cur=0;ll dq=0,ans=0;
		for(int i=ws;i>=1;i--)
			if(fj[i]==1)
			{
				for(int j=0;j<=i-1;j++)
				{
					ll tmp=ksm(cur+j,k);
					if(j==0){ans=(ans+tmp*ksm(dq,k)%mod)%mod;continue;}
					for(int l=0;l<=k;l++)
						ans=(ans+tmp*C[k][l]%mod*ksm(dq,k-l)%mod*dp[i-1][j][l]%mod)%mod;
				}
				cur++;dq=(dq+(1ll<<(i-1)))%mod;
			}
		printf("%lld\n",(ans+ksm(r%mod*cur%mod,k))%mod);
	}
	return 0;
}
```

---

## 作者：Rubidium_Chloride (赞：4)

$\aleph_0\ \mathcal{Solution}$

~~最后一个 Subtask 本来是没有的。~~

前面的 $25$ 分都是暴力做法。

第一档是给你暴力 $\mathcal{O}(tr\log r\log k)$ 的。

~~不要问我为什么给了这么奇怪的东西。~~

第二档是你预处理 $\operatorname{popcount}$ 函数然后 $\mathcal{O}(tr\log k)$ 的。

第三档是给你预处理所有的 $f$ 然后求 $f^k$ 的前缀和然后 $\mathcal{O}(r\log k)-\mathcal{O}(1)$ 的。

## 1. Analysis-EZ Version

~~Sub4 是原来的这题。~~

首先发现 $f(i)=i\times \operatorname{popcount}(i)$。

可以用数学归纳法证明。

考虑一次询问，尝试用 $\mathcal{O}(\log r)$ 的时间内解决。

## 2. How to Calculate

按位考虑。令 $r=2^{a_1}+2^{a_2}+\dots 2^{a_p},a_1>a_2>\cdots >a_p$。

则 $S=\sum\limits_{i=1}^{p}\left(\sum\limits_{j=\left(\sum\limits_{k=1}^{i-1} 2^{a_k}\right)}^{\left(\sum\limits_{k=1}^{i-1} 2^{a_k}\right)+2^{a_i}-1}  f^2(j)\right)+f^2(r)$

首先可以在 $\mathcal{O}(\log r)$ 的时间内计算最后一项。

比如我们现在取出中间的一段，需要算的是 $Q=\sum\limits_{i=s}^{s+2^m-1} f^2(i)$，其中 $s$ 为 $r$ 的二进制表示中一个前缀，且 $s+2^m$ 也是 $r$ 的二进制表示中一个前缀。

做如下变换，另设 $\operatorname{popcount}(s)=t$：

$\begin{aligned}Q&=\sum\limits_{i=s}^{s+2^m-1} f^2(i)\\&=\sum\limits_{i=0}^{2^m-1} f^2(i+s)\\&=\sum\limits_{i=0}^{2^m-1}(i+s)^2\operatorname{popcount}^2(i+s)\\&=\sum\limits_{i=0}^{2^m-1}(i+s)^2(\operatorname{popcount}(i)+t)^2\end{aligned}$

然后开始大力展开。

~~为了方便书写 popcount 变成了 pop~~

$\global\def\pop{{\operatorname{pop}}}Q=\sum\limits_{i=0}^{2^m-1}\left(i^2\pop^2(i)+2si\pop^2(i)+s^2\pop^2(i)+2ti^2\pop(i)+4sti\pop(i)+2s^2t\pop(i)+t^2i^2+2st^2i+s^2t^2\right)$

柿子看起来非常长非常恐怖……

个鬼啊。

整理一下：

$\global\def\pop{{\operatorname{pop}}}Q=\sum\limits_{i=0}^{2^m-1}i^2\pop^2(i)+2s\sum\limits_{i=0}^{2^m-1}i\pop^2(i)+s^2\sum\limits_{i=0}^{2^m-1}\pop^2(i)+2t\sum\limits_{i=0}^{2^m-1}i^2\pop(i)+4st\sum\limits_{i=0}^{2^m-1}i\pop(i)+2s^2t\sum\limits_{i=0}^{2^m-1}\pop(i)+t^2\sum\limits_{i=0}^{2^m-1}i^2+2st^2\sum\limits_{i=0}^{2^m-1}i+s^2t^2\sum\limits_{i=0}^{2^m-1} 1$

很显然的我们只要预计算 $\global\def\pop{{\operatorname{pop}}}i^2\pop^2(i),i^2\pop(i),i^2,i\pop^2(i),i\pop(i),i,\pop^2(i),\pop(i),1$ 在每个 $2^k-1$ 处的前缀和就可以了。下文将会叙述如何计算。

预处理可以做到 $\mathcal{O}(\log r)$。

复杂度 $\mathcal{O}(\log r)-\mathcal{O}(\log r)$。

## 3. Analysis-HD Version

既然已经考虑到了怎么计算 $k=2$ 为什么不继续算呢......？

$k\neq 2$ 时，展开柿子。

$\begin{aligned}Q&=\sum\limits_{i=s}^{s+2^m-1} f^k(i)\\&=\sum\limits_{i=0}^{2^m-1} f^k(i+s)\\&=\sum\limits_{i=0}^{2^m-1}(i+s)^k\operatorname{pop}^k(i+s)\\&=\sum\limits_{i=0}^{2^m-1}(i+s)^k(\operatorname{pop}(i)+t)^k\end{aligned}$

二项式展开！

$\begin{aligned}Q&=\sum\limits_{i=0}^{2^m-1}\sum\limits_{a=0}^{k}\sum\limits_{b=0}^{k} i^{a}s^{k-a}\operatorname{pop}^b(i)t^{k-b}\\&=\sum\limits_{a=0}^{k}\sum\limits_{b=0}^{k}s^{k-a}t^{k-b}\sum\limits_{i=0}^{2^m-1}i^a\operatorname{pop}^b(i)\end{aligned}$

然后我们只需要预处理 $\sum\limits_{i=0}^{2^x-1} i^a\operatorname{pop}^b(i)$ 的值就可以了。

$\sum\limits_{i=0}^{2^x-1} i^a\operatorname{pop}^b(i)=\sum\limits_{i=0}^{2^{x-1}-1}i^a\operatorname{pop}^b(i)+\sum\limits_{i=0}^{2^{x-1}-1}(i+2^{x-1})^a(\operatorname{pop}(i)+1)^b$

二项式展开计算即可。

预处理组合数，$2$ 的幂次，并且在预处理，询问时精细化处理可做到省去快速幂复杂度。

复杂度：预处理 $\mathcal{O}(k^4\log r)$（$k^2\log r$ 个状态，$k^2$ 转移）。

总询问复杂度：$\mathcal{O}(tk^2\log r)$（$\log r$ 位，每位计算 $k^2$）。


贴个代码好了：


```cpp
#include<bits/stdc++.h>
#define P 1000000007
#define N 39
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll t,r,k,npop[70][N][N],bin[N][N],pw[2000+9],ans;//npop{x}{i}{j}:sum of n^i pop^j,0 to 2^x-1
ll qpow(ll x,ll pw){ll ans=1;for(;pw;pw>>=1,x=x*x%P) if(pw&1) ans=ans*x%P;return ans;}
#define binom(n,m) bin[n][m]
void init(){
    for(int i=0;i<=30;i++) bin[i][0]=1;
    for(int i=1;i<=30;i++)
        for(int j=1;j<=30;j++) bin[i][j]=(bin[i-1][j]+bin[i-1][j-1])%P;
    pw[0]=1;for(int i=1;i<=2000;i++) pw[i]=(pw[i-1]<<1)%P;
    for(int i=0;i<=30;i++) for(int j=0;j<=30;j++) npop[1][i][j]=1;
    npop[1][0][0]=2,npop[0][0][0]=1;
    for(int i=2;i<=62;i++)
        for(int a=0;a<=30;a++)
            for(int b=0;b<=30;b++){
                npop[i][a][b]=npop[i-1][a][b];
                for(int p=0;p<=a;p++){
                    ll p1=binom(a,p)*pw[(i-1)*(a-p)]%P;
                    for(int q=0;q<=b;q++)
                        npop[i][a][b]+=(npop[i-1][p][q]*p1%P*binom(b,q)%P),npop[i][a][b]%=P;
                }
                    
            }
}
void solve(ll stp,ll s,ll t){
    while(~stp){
        if(!(r&(1ll<<stp))){stp--;continue;}
        for(ll p=k,p1=1;p>=0;p--,p1=p1*s%P){
            ll c1=binom(k,p)*p1%P;
            for(ll q=k,q1=1;q>=0;q--,q1=q1*t%P) ans+=(npop[stp][p][q]%P*c1%P*binom(k,q)%P*q1%P),ans%=P;
        }
        s=(s+pw[stp])%P,t++,stp--;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    init(),t=read();
    while(t--){
        r=read(),k=read(),ans=0;
        solve(62,0,0);
        ans+=qpow(r%P*__builtin_popcountl(r)%P,k),ans%=P;
        printf("%lld\n",ans);
    }
    return 0;
}
```


## INF. 后记

如果有人认为代码卡常，这里特此说明：代码框架是我写的，卡常是应 $\text{U}\color{red}\text{nyieldingTrilobite}$ 的要求加入的。

如果你们愿意的话，我可以把这题时限弄成 500ms。

原因：std 最慢点跑了 240ms。

---

## 作者：Y_B_X (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P8440)

>题意：  
设 $f(x)=\begin{cases}0&x=0\\1&x=1\\2f\left(\dfrac{x}{2}\right)&2|x,x>0\\\dfrac{2x}{x-1}f\left(\dfrac{x-1}{2}\right)+x &\text{otherwise}\end{cases}$  
给出 $T$ 组询问 $N,k$ ，求 $\ \displaystyle \sum_{n=0}^Nf(n)^k\bmod 10^9+7$  
$T\leq 10^3\ ,\ N\leq 2^{63}-1\ ,\ k\leq 30$

## $\text{Step 1}:\text{Simplification}$

先尝试化简 $f(i)$，由于 $2\mid i,i>1$ 时 $\dfrac{f(i)}{2}=f\left(\dfrac{i}{2}\right)$，  
所以当 $2\nmid i,i>0$ 时 $f(i)=i+\dfrac{2i}{1-i}\dfrac{f(i-1)}{2}=i\left(\dfrac{f(i-1)}{i-1}+1\right)$

~~打表~~发现 $f(i)$ 全是整数，于是尝试归纳证明 $\forall_{i\geq2}\ i\mid f(i)$。  

假设已知 $i\mid f(i)$，则:
$\begin{cases}f(2i)=2f(i)&2i|f(2i)\\f(2i+1)=(2i+1)\left(\dfrac{f(2i)}{2i}+1\right)&2i+1|f(2i+1)\end{cases}$

因此可以考虑设 $g(i)=\dfrac{f(i)}{i}$，再带回 $f$ 的递归式得到：

$$g(i)=\begin{cases}0&i=0\\1&i=1\\g\left(\dfrac{i}{2}\right) &2|i\\g\left(\dfrac{i-1}{2}\right)+1&\text{otherwise}\end{cases}$$

再化简一下，有 $g(0)=0,g(i)=g\left(\left\lfloor\dfrac{i}{2}\right\rfloor\right)+[2\nmid i]$

于是我们发现 $g(i)=\operatorname{popcount}(i)$，也就是 $f(i)=i\operatorname{popcount}(i)$。

将其带回答案式子：

 $$\sum_{n=0}^Nf(n)^k=\sum_{n=0}^Nn^k\operatorname{popcount}(n)^k=\sum_{t=0}^{63}t^k\sum_{n=0}^Nn^k\left[\operatorname{popcount}(n)=t\right]$$
 
## $\text{Step 2}:\text{DP}$

按着上面式子枚举 $t$，然后对 $n$ 进行 $2$ 进制拆分，考虑 $dp$ 求答案。

设 $S_{i,j}$ 为当前填了前 $i$ 位中，有 $j$ 个 $1$ 的数 $n$ 的集合，

也即 $S_{i,j}=\left\{n|0\leq n<2^{i+1},\operatorname{popcount}(n)=j\right\}$

然后设 $f_{i,j}=\displaystyle \sum_{n\in S_{i,j}}n^k$，对当前第 $i$ 位是否填 $1$ 写出转移式：

$$f_{i,j}=f_{i-1,j}+\sum_{n\in S_{i-1,j-1}}\left(n+2^i\right)^k$$

此处因为 $+2^i$ 的存在不好将求和与 $f_{i-1,j-1}$ 相联系。

由于本人过于愚蠢，想到将 $f_{i,j}$ 用多项式表示，设 $\displaystyle F_{i,j}(x)=\sum_{n\in S_{i,j}}(n+x)^k$

于是 $\displaystyle F_{i,j}(x)=F_{i-1,j}(x)+F_{i-1,j-1}\left(x+2^i\right)$。

而多项式的次数为 $k$，可以单次暴力 $O(k^2)$ 转移。

具体地，对 $\displaystyle F(x)=\sum_{i=0}^kf_ix^k$，用二项式定理拆开 $F(x+d)$ 得到：

$$F(x+d)=\sum_{i=0}^kx^i\sum_{j=i}^k\binom{j}{i}f_jd^{j-i}$$

再考虑如何求答案，即 $\displaystyle \sum_{t=0}^{63}t^k\sum_{n=0}^Nn^k\left[\operatorname{popcount}(n)=t\right]$

首先按式子枚举 $t$，再考虑 $n\leq N$ 的限制，

这可以对 $N$ 枚举每一个二进制下是 $1$ 的位置的 $i$，

然后让 $[0,i-1]$ 的二进制位随意放 $0$ 或 $1$ ，$i$ 位放 $0$，$[i+1,63]$ 位不动，能满足组成的 $n<N$

设将 $N$ 的二进制下 $[0,i]$ 位设为 $0$，其他位不动的数是 $d$，其中包含 $c$ 个 $1$，

那当前的贡献便是 $\displaystyle \sum_{n\in S_{i-1,t-c}}(n+d)^k=F_{i-1,t-c}(d)$，能方便求出。

## $\text{Time Complexity}$

对一个 $k$ 处理出全部 $F_{i,j}(x)$ 的时间复杂度为 $O(W^2K^2)$，其中 $W=64,K=30$。

而 $k$ 仅有 $30$ 个，没必要对每组询问都算一遍，对 $k$ 预处理 $F$ 可做到 $O(W^2K^3)$。

虽然算算有 $10^8$ 量级，但 $F_{i,j}(x)$ 中 $j\leq i+1$ 且求 $F(x+d)$ 时循环内 $j\geq i$，  
再加上 $k^3$ 前缀和，因此会自带 $\dfrac{1}{2}\times\dfrac{1}{2}\times\dfrac{1}{4}=\dfrac{1}{16}$ 的小常数，跑得挺快。

每次询问下要枚举 $t,i$，并计算一个多项式单点求值，复杂度为 $O(W^2K)$

故而总的时间复杂度为 $O(W^2K^3+TW^2K)$。

一个小优化：将 $F(x)=\sum\limits_{i=0}^kf_i\ x^i$ 改设成 $\sum\limits_{i=0}^k f_i\ i!\ x^i$ 能在求 $F(x+d)$ 时将乘法减少很多次。

#### $\texttt{code:}$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int W=64,K=31;
const int N=1e3+10;
int T,k,w,c;ll n,d,fack;
int f[K][W][W][K];ll fk[K];
int kk[N];ll nn[N],pwd[K];bool bk[K];
ll ifac[K],s[K],pw[W][K],res,ans,tmp;
inline int add(int x,int y){
	return x+y<mod?x+y:x+y-mod;
}
inline void qpow(ll x,int k){
	res=1;
	while(k){
		if(k&1)res=res*x%mod;
		x=x*x%mod;k>>=1;
	}
}
void pre_work(int k){
	register int i;ifac[0]=i=1;
	for(;i<=k;++i)ifac[i]=ifac[i-1]*i%mod;
	qpow(ifac[k],mod-2);ifac[k]=res;
	for(i=k;i;--i)ifac[i-1]=ifac[i]*i%mod;
} 
inline void poly_add(int *f,int *g){
	static int i;
	for(i=0;i<=k;++i)f[i]=add(f[i],g[i]);
}
inline void poly_trans(int *f,int *g,ll d){
	static int i,j;
	for(res=1,i=0;i<=k;++i)
		pwd[i]=res*ifac[i]%mod,res=res*d%mod;
	for(i=0;i<=k;++i){
		res=0;
		for(j=i;j<=k;++j)res+=pwd[j-i]*g[j]%mod;
		f[i]=res%mod;
	}
}
inline void poly_calc(int *f,int d){
	static int i;tmp=0;
	for(res=1,i=0;i<=k;++i)
		tmp+=res*f[i]%mod*ifac[i]%mod,res=res*d%mod;
}
template<typename ArrT>
void solve(int w,ArrT f){
	register int i,j;
	for(fk[0]=1,i=0;i^k;++i)
		fk[i+1]=fk[i]*(k-i)%mod;
	f[0][0][k]=fk[k];
	for(i=0;i<=k;++i)f[0][1][i]=fk[i];
	for(i=1;i<=w;++i){
		f[i][0][k]=fk[k];
		for(j=1;j<=i+1;++j){
			poly_trans(f[i][j],f[i-1][j-1],(1ll<<i)%mod);
			poly_add(f[i][j],f[i-1][j]);
		}
	}
}
template<typename ArrT>
inline void solve(ll n,int k,ArrT f){
	static int i,j;
	for(i=W-1;~i;--i)if(n&(1ll<<i))break;
	w=i;ans=(k==0);d=c=0;
	for(i=w;~i;--i)if(n&(1ll<<i)){
		for(j=1;j<=i;++j){
			poly_calc(f[i-1][j],d);
			ans+=tmp%mod*pw[j+c][k]%mod;
		}
		d+=(1ll<<i);++c;
		qpow(d%=mod,k);
		ans+=res*pw[c][k]%mod;
	}
}
char ch;
inline void read(int &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
inline void read(ll &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
}
void write(int x){
	if(x>9)write(x/10);putchar(48|(x%10));
}
main(){
	pre_work(30);read(T);
	register int i,j;
	for(i=1;i<=T;++i)
		read(nn[i]),read(kk[i]),
		nn[i]>n?n=nn[i]:0,bk[kk[i]]=1;
	for(i=W-1;~i;--i)if(n&(1ll<<i))break;
	w=i;
	for(fack=1,k=0;k<=30;){
		if(bk[k])solve(w,f[k]);
		++k,fack=fack*k%mod;
	}
	for(i=1;i<=w;++i){
		res=1;
		for(k=0;k<=30;++k)
			pw[i][k]=res,res=res*i%mod;
	}
	for(i=1;i<=T;++i){
		k=kk[i];
		solve(nn[i],k,f[k]);
		write(ans%mod);putchar('\n');
	}
}
```

---

