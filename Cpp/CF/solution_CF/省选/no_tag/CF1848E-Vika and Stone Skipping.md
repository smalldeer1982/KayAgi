# Vika and Stone Skipping

## 题目描述

In Vika's hometown, Vladivostok, there is a beautiful sea.

Often you can see kids skimming stones. This is the process of throwing a stone into the sea at a small angle, causing it to fly far and bounce several times off the water surface.

Vika has skimmed stones many times and knows that if you throw a stone from the shore perpendicular to the coastline with a force of $ f $ , it will first touch the water at a distance of $ f $ from the shore, then bounce off and touch the water again at a distance of $ f - 1 $ from the previous point of contact. The stone will continue to fly in a straight line, reducing the distances between the points where it touches the water, until it falls into the sea.

Formally, the points at which the stone touches the water surface will have the following coordinates: $ f $ , $ f + (f - 1) $ , $ f + (f - 1) + (f - 2) $ , ... , $ f + (f - 1) + (f - 2) + \ldots + 1 $ (assuming that $ 0 $ is the coordinate of the shoreline).

Once, while walking along the embankment of Vladivostok in the evening, Vika saw a group of guys skipping stones across the sea, launching them from the same point with different forces.

She became interested in what is the maximum number of guys who can launch a stone with their force $ f_i $ , so that all $ f_i $ are different positive integers, and all $ n $ stones touched the water at the point with the coordinate $ x $ (assuming that $ 0 $ is the coordinate of the shoreline).

After thinking a little, Vika answered her question. After that, she began to analyze how the answer to her question would change if she multiplied the coordinate $ x $ by some positive integers $ x_1 $ , $ x_2 $ , ... , $ x_q $ , which she picked for analysis.

Vika finds it difficult to cope with such analysis on her own, so she turned to you for help.

Formally, Vika is interested in the answer to her question for the coordinates $ X_1 = x \cdot x_1 $ , $ X_2 = X_1 \cdot x_2 $ , ... , $ X_q = X_{q-1} \cdot x_q $ . Since the answer for such coordinates can be quite large, find it modulo $ M $ . It is guaranteed that $ M $ is prime.

## 说明/提示

In the first sample, to make the stone touch the water at a point with coordinate $ 2 $ , it needs to be thrown with a force of $ 2 $ . To make the stone touch the water at a point with coordinate $ 2 \cdot 3 = 6 $ , it needs to be thrown with a force of $ 3 $ or $ 6 $ .

In the second sample, you can skim a stone with a force of $ 5 $ or $ 14 $ to make it touch the water at a point with coordinate $ 7 \cdot 2 = 14 $ . For the coordinate $ 14 \cdot 13 = 182 $ , there are $ 4 $ possible forces: $ 20 $ , $ 29 $ , $ 47 $ , $ 182 $ .

## 样例 #1

### 输入

```
1 2 179
2 3```

### 输出

```
1
2```

## 样例 #2

### 输入

```
7 5 998244353
2 13 1 44 179```

### 输出

```
2
4
4
8
16```

## 样例 #3

### 输入

```
1000000000 10 179
58989 49494 8799 9794 97414 141241 552545 145555 548959 774175```

### 输出

```
120
4
16
64
111
43
150
85
161
95```

# 题解

## 作者：EuphoricStar (赞：5)

感觉比这场的 F 简单。

发现我们要进行 $x$ 不断乘一些数然后求答案的操作，猜测答案与 $x$ 的因数有关。如果你对数字比较敏感，不难发现答案就是 $x$ 的奇因子个数。

官方题解的证明：

> 设 $f + (f - 1) + \cdots + (f - (c - 1)) = x$，由等差数列求和公式可得 $x = \frac{(2f - (c - 1))c}{2}$。

> 若 $c$ 为奇数，那么 $x = (f - \frac{c - 1}{2}) \times c = p \times (2k + 1)$，其中 $k = \frac{c - 1}{2}, p = f - k$。因为 $c - 1 < f$，所以 $p > k$。

> 若 $c$ 为偶数，那么 $x = (2f - (c - 1)) \times \frac{c}{2} = (2k + 1) \times p$，其中 $p = \frac{c}{2}, k = f - p$。因为 $c \le f$，所以 $p \le k$。

> 我们发现对于 $x$ 的每个奇因子 $2k + 1$，都能唯一对应一个 $p$。所以答案就是 $x$ 的奇因子个数。

于是现在问题变成了，你初始有一个整数 $x$，$q$ 次操作，每次操作给出 $y$，令 $x \gets x \times y$，每次操作后输出 $x$ 的奇因子个数。

对 $x$ 分解质因数，得到 $x = p_1^{k_1} p_2^{k_2} \cdots p_m^{k_m}$。考虑 $x$ 的奇因子是怎么凑成的。对于每个奇质因子 $p_i$，都可以选 $[0, k_i]$ 个。因此答案是 $\prod\limits_{2 \nmid p_i} (k_i + 1)$。

直接的想法是用 `map` 动态维护答案，每次操作时，若奇质因子 $p_i$ 的指数改变，就乘一个之前它的 $k_i + 1$ 的逆元，再乘上现在的 $k_i + 1$。但是尽管题目保证模数是质数，仍然有可能存在 $k_i + 1$ 不存在逆元的情况（$mod \mid k_i + 1$）。

于是考虑改用线段树维护 $p_i \in [1, 10^6]$，$\prod\limits_{2 \nmid p_i} (k_i + 1)$。每次操作就相当于单点修改，查询就是查询全局积。对于 $p_i > 10^6$，因为它只可能在初始的 $x$ 中出现，所以提前预处理好即可。

时间复杂度 $O(\sqrt{x} + q \log^2 V)$。

[code](https://codeforces.com/contest/1848/submission/214191583)

---

## 作者：Bear203 (赞：2)

## 思路

设石头入水 $g$ 次，有 $x \prod X_i=\sum_{i=f-g+1}^f i$，即 $2x \prod X_i=(2f-g+1)g$。显然每个合法 $f$ 与 $2x \prod X_i$ 的一个奇因子一一对应，所求即 $2x \prod X_i$ 的奇因子数。令 $x'=\frac{x}{\operatorname{lowbit(x)}}$，$X'_i=\frac{X_i}{\operatorname{lowbit(X_i)}}$，答案为 $x'\prod X'_i$  的因数个数。

于是，问题转化为：

一个长 $O(\frac{n}{\ln{n}})$ 初始全 $1$ 序列，$O(q\log{V})$ 次单点修改，$O(q)$ 次查询模意义下全局积，可以使用数组维护。

## 算法流程
- 线性筛最小质因子 $d_i$。
- 直接分解 $x$。
- 每组询问利用 $d_i$ 分解 $x_i$，$O(\log{V})$ 次单点加入、删除。
- 每次加入/删除，若修改 $0$，更新 $0$ 的个数 $cnt$，否则直接更新答案。
- 查询若 $cnt$ 非零，输出 $0$，否则输出当前答案。

时间复杂度 $O(\sqrt{x}+V+q\log{m}\log{V})$。
预处理逆元之后为 $O(\sqrt{x}+V+q\log{V})$。

此外，若使用线段树维护，复杂度多一个 $\log{V}$。
## code
```cpp
#include<bits/stdc++.h>
#define LL long long
#define Un unsigned
#define For1(i,a,b) for(i=(a);i<=(b);++i) 
#define For2(i,a,b) for(i=(a);i<(b);++i) 
#define FoR1(i,a,b) for(i=(a);i>=(b);--i) 
#define FoR2(i,a,b) for(i=(a);i>(b);--i) 
#define For_L(i,x) for(int i=ft[x];i;i=nt[i])
#define fir first
#define sec second
#define mkp std::make_pair 
#define pii std::pair<int,int>
#define pb emplace_back
#define il inline
template<class T1>
il void cmax(T1&x,T1 y){if(x<y)x=y;}
template<class T1>
il void cmin(T1&x,T1 y){if(x>y)x=y;}
#define FI using std::cin;std::ios::sync_with_stdio(0),cin.tie(0)
int mod;
int add(int x,int y){return (x+=y)<mod?x:x-mod;}
il void addd(int &x,int y){if((x+=y)>=mod)x-=mod;}
int sub(int x,int y){return (x-=y)<0?x+mod:x;}
void subb(int &x,int y){if((x-=y)<0)x+=mod;}
int mul(int x,int y){return 1ll*x*y%mod;}
void mull(int &x,int y){x=1ll*x*y%mod;}
int pow(int x,int y){int res=1;
    while(y){
        if(y&1)mull(res,x);
        mull(x,x);
        y>>=1;
    }
    return res;
}
int inv(int x){return pow(x,mod-2);}
const int A=1000111,P=A>>2;
bool bk[A];
int pr[P],ans1[P],d[A],n,q,cnt,x,tlp,ans2=1;
void mdf(int x){//修改
	addd(ans1[x],1);
	if(ans1[x]==0)--cnt;
	else mull(ans2,inv(ans1[x])); 
	if(add(ans1[x],1)==0)++cnt;
	else mull(ans2,add(ans1[x],1));
}
int main(){FI;int i,j,t1;
	cin>>x>>q>>mod;
	For2(i,2,A){//预处理最小质因子
		if(!bk[i])pr[++tlp]=i,d[i]=tlp;
		for(j=1;j<=tlp&&(t1=i*pr[j])<A;++j){
			d[t1]=j;
			bk[t1]=1;
			if(i%pr[j]==0)break;
		}
	}
	x/=(x&-x);
	For1(j,1,tlp){//加入x
		while(x%pr[j]==0)mdf(j),x/=pr[j];
	}
	if(x>1)pr[++tlp]=x,mdf(tlp);
	while(q--){
		cin>>x;
		x/=(x&-x);
		while(x>1){//加入X_i
			mdf(d[x]);
			x/=pr[d[x]];
		}
		if(cnt)printf("0\n");
		else printf("%d\n",ans2);
	}
	return 0;
} 
```

使用 Pollard-Rho 算法可以优化到 $O(x^\frac{1}{4}+V+q\log{V})$，做到 $x \le 10^{18}$。

---

## 作者：MiniLong (赞：0)

设 $x = \prod\limits X$，题目就是要求 $\sum\limits_{f} [\exist_{t \in [0,f)} \sum\limits_{i=t+1}^f i = x]$，推导一下就是 $\sum\limits_f [\exist_{t \in [0,f)} (f-t)(f+t+1)=2x]$。设 $d | 2x,(f-t)=d$，解一下就会发现 $f = \dfrac{\frac{2x}{d}+d-1}{2},t=\dfrac{x}{d}-\dfrac{d+1}{2}$，因为 $f,t\in \N$，所以 $\dfrac{d(d+1)}{2} \le x$。再观察 $d$ 的奇偶性。

- 当 $2 \nmid d$ 时，$2 | \dfrac{2x}{d}$，$2|(d-1)$，此时合法。

- 当 $2 \mid d$ 时，当且仅当 $2 \nmid \dfrac{2x}{d}$ 时合法。

观察到 $2 \nmid d$ 和 $2\nmid \dfrac{2x}{d}$ 是对称的，所以 $d(d+1)\le 2x$ 这个限制可以去掉。

所以答案就是 $\sum\limits_{d | 2x} [2\nmid d]$。

所以暴力将 $x$ 分解质因数，设 $x$ 的所有 **奇质因数** 和它们的幂是 $p_i,e_i$，则 $ans = \prod (e_i + 1)$。那么开个桶去存每个奇质因数的幂就好了。**注意，因为模数可能较小，所以要记录 $e_i+1$ 是 $M$ 倍数的个数**。

---

## 作者：skyskyCCC (赞：0)

## 前言。
数论题，和筛。还是很值得一做的。

题意简述：给定一个初始值 $x$ 并且给出询问，对于每一个询问 $X_i$ 你需要求出有多少对 $\left(l,r\right)$ 使得 $\sum_{k=l}^rk=X_i$。举个例子，第一次询问的 $X_1=x\times y_1$ 之后就是 $X_i=X_{i-1}\times y_i$。对 $M$ 取模。

注意区分本文中的 $x$ 和 $X$ 它们不是一个东西。
## 分析。
对于一个数 $X_i$ 我们显然有一个公式，根据等差数列公式我们不难得到 $X_i=\frac{\left(l+r\right)\times\left(r+l-1\right)}{2}$。同时去分母可以得到：
$$2\times X_i=\left(l+r\right)\times\left(r+l-1\right)$$
令 $a=l+r$ 同时 $b=r+l-1$ 则可以化为 $l=\frac{a-b+1}{2}$ 则 $r=\frac{a+b-1}{2}$。

现在就很显然了，因为 $l$ 和 $r$ 必须为任意值，但是为正整数，所以我们需要保证的就是上面的两个式子的分子都是偶数即可，这样就可以整除了。那么因为有一个 $1$ 存在，所以直接可以得出 $a$ 和 $b$ 为一奇一偶，我们不妨假设 $a$ 为偶数 $b$ 为奇数。这个假设显然成立，其实反过来还是这个结果。

现在的问题就是，对于一个数 $2\times X_i$ 有多少个 $\left(a,b\right)$ 使得 $a\times b=2\times X_i$ 且 $a$ 为偶数 $b$ 为奇数。

有一个很经典的思路就是素因子分解，就是 $2\times X_i$ 总的所以素因子 $2$ 必然都属于 $a$。这个可以考虑反证。如果素因子中的 $2$ 不都属于 $a$ 则一定存在某一个 $2$ 属于 $b$ 则 $b$ 一定为偶数，这与我们的前提 $b$ 为奇数相悖，所以得证。那么对于剩下的分解出来的素因子，显然直接随便分给 $a$ 或者 $b$ 即可，分配的可能方案数就是答案。

很好，我们现在就可以求了，直接记录素因子的每一个的出现次数，那么每一个素因子的贡献就是这个素因子出现次数加上一。这是因为可以有从 $0$ 到这个出现次数个可能情况分给 $a$。但是真的有这么简单吗？

我们注意到 $x$ 最大可以取到 $10^9$ 则显然直接朴素的素因子分解会超时。但是我们还有 $y_i\leq 10^6$。这个是破解此题的关键。我们不妨假设我们已经预处理出来了所有的素因子出现的个数 $p_i$ 次，则可以直接求出答案。如果我们计算 $X_i+1=X_i\times y_{i+1}$ 时我们只需要去修改 $y_{i+1}$ 的素因子对应的 $p_i$ 即可。既然我们没有办法直接筛 $x$ 我们可以筛 $y_i$ 啊。

此时问题又转换成了：求出 $x$ 对应的 $p_i$ 然后新乘上一个 $y_i$ 时，使用素因子分解维护其对应的 $p_i$ 然后动态更新答案。

具体来说，我们对于整个 $x$ 的 $p_i$ 没有办法都求出来，但是 $y_i$ 的限制条件告诉我们只有一个 $\leq10^6$ 的素数对应的 $p_i$ 才会被修改。而 $\geq 10^6$ 的素数的数量是固定的，只有一个。证明如下：因为 $x\leq 10^9$ 则如果存在它存在两个 $\geq10^6$ 的素因子，则 $x$ 一定不小于 $10^{12}$ 但这与题目的限制条件相悖，所以不可能存在两个，所以得证。

所以我们直接分解 $x$ 中 $\leq 10^6$ 的素因子即可。如果最后有剩余，那么一定存在一个大于 $10^6$ 的素因子，我们给它记作 $p_k$。这个 $p_k$ 对答案的贡献就是取或者不取，贡献为 $2$ 然后加到答案中去即可。那么我们在后面操作的时候会改变这个的值吗？我们知道这样的数只存在一个，所以对后续的答案没有变化。

设 $p_i$ 现在增加了 $Q$ 个则统计答案就是下面的式子：
$$ans_i=\frac{ans_i}{\left(p_i+1\right)}\times\left(p_i+Q+1\right)$$
然后逆元处理出来即可。

然后稍微处理一下 $M$ 的情况即可。因为 $0$ 不存在逆元，所以需要考虑一下因子 $M$ 然后在进行答案计算删掉它即可。具体来说，如果存在 $0$ 就是答案，如果不存在就直接输出。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
long long x,M,xi,Q;
long long ans=1,s_num[1000005],p[1000005],flag;
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
long long ksm(long long a,long long b){
	long long res=1;
	a%=M;
	while(b){
		if(b&1){
		    res=res*a%M;
		}
		a=a*a%M;
		b>>=1;
	}
	return res;
}
void work(long long x){
	while(x%M==0){
		flag--;
		x/=M;
	}
	ans=ans*ksm(x,M-2)%M;
}
void mul(long long x){
	while(x%M==0){
		flag++;
		x/=M;
	}
	ans=ans*x%M;
}
int main(){
	read(x);
	read(Q);
	read(M);
    for (int i=3;i<=1000000;i+=2){
        if(s_num[i]){
            continue;
        }
        for (int j=i;j<=1000000;j+=i){
		    s_num[j]=i;
		}
    }
	while(!(x&1)){
	    x>>=1;
	}//过滤掉素因子2。 
	for(int i=3;i<=1000000;i+=2){
		while(x%i==0){
			work(p[i]+1);
			p[i]++;
			mul(p[i]+1);
			x/=i; 
		}
	}
	if(x>1){
	    ans=ans*2%M;
	}
	while(Q--){
		read(xi);
		while(!(xi&1)){
		    xi>>=1;
		}
		while(xi>1){
			work(p[s_num[xi]]+1); 
			p[s_num[xi]]++; 
			mul(p[s_num[xi]]+1);
			xi/=s_num[xi];
		}
		if(flag){
		    cout<<"0\n";
		}
		else cout<<ans<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_HCl_ (赞：0)

思路很好想到，式子很好推出，~~但代码我没写出来~~。（我太菜了）

# CF1848E 题解

**题意简述**

求有多少种 $f$ 满足存在 $\sum\limits_{i=0}^{k}(f-k)=x$。

**思路引导**

首先，对式子进行变形。

$$\begin{aligned}\sum_{i=0}^{k}(f-k)=x\\(k+1)f-\frac{k(k+1)}{2}=x\\-k^2+(2f-1)k+2f-2x=0\end{aligned}$$

因为我们需要求出合法的 $f$，所以考虑将上式视为以 $k$ 为主元的二次方程。根据求根公式，舍去负数解，有：

$$k=\frac{\sqrt{(2f+1)^2-8x}+2f-1}{2}$$

由于 $k$ 是整数，所以有 $\sqrt{(2f+1)^2-8x}$ 是整数且是奇数。我们设：

$$\begin{aligned}(2f+1)^2-8x=d^2\\(2f+1+d)(2f+1-d)=8x\end{aligned}$$


又因为 $d$ 是奇数，所以我们要将 $8x$ 分解成两个偶数。又因为 $\dfrac{(2f+1+d)+(2f+1-d)}{2}=2f+1$ 是奇数，所以两个数除以 $2$ 之后异奇偶。

换言之，也就是 $(2f+1+d)$ 和 $(2f+a-d)$ 两个数中，其中一个数分解后，质因子 $2$ 的指数为 $1$，另外一个数质因子 $2$ 的指数大于 $1$。

因为 $(2f+1+d)$ 和 $(2f+1-d)$ 有大小区分，所以分解时可以忽略其顺序，也就是只考虑分解的方案。接下来考虑分解 $8x$。

首先，对于质因子 $2$，其分配唯一。对于奇质因子的分配，是随意的。那么答案就是 $\prod(cnt_p+1)$，其中 $p$ 是 $8x$ 的奇质因子，也就是 $x$ 的奇质因子，$cnt_p$ 是 $p$ 的指数。

对于修改操作，就是将当前当前答案 $ans$ 修改为 $ans\cdot\dfrac{cnt_p+b_p+1}{cnt_p+1}$，其中 $b_p$ 是 $y$ 中 $p$ 的指数。

但是我们的答案是在模 $M$ 意义下的，因此我们先要除去 $M$ 的因子，再进行乘除操作。乘除操作中除去的 $M$，我们用 $cnt_k$ 去记录，也就是 $ans$ 中 $M$ 的指数。

**代码**

Code References from @[huangrenheluogu](https://www.luogu.com.cn/user/461359)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6;
int M,cntk,ans,cnt[MAXN+5];
struct typ{
	int p,b;
};
vector<typ> num[MAXN+5];
int qpow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(x*x)%M)if(y&1)res=(res*x)%M;
	return res;
}
void calc(int id,int x){//分解 x 
	for(int i=2;i*i<=x;++i)
		if(x%i==0){
			int count=0;
			while(x%i==0)count++,x/=i;
			num[id].push_back(typ{i,count});
		}
	if(x>1)num[id].push_back(typ{x,1});
}
void mul(int x){//乘法 
	while(x%M==0)x/=M,cntk++;
	ans=ans*x%M;
}
void div(int x){//除法 
	while(x%M==0)x/=M,cntk--;
	ans=ans*qpow(x,M-2)%M;
}
int x,q;
void init(){//分解 8x 
	x*=8;
	ans=1;
	int tmp=x;
	while(tmp%2==0)
		cnt[2]++,tmp/=2;
	for(int i=3;i<=MAXN;++i)cnt[i]=1;
	for(int i=3;i*i<=tmp;++i){
		while(tmp%i==0)cnt[i]++,tmp/=i;
		mul(cnt[i]);
	}
	if(tmp>1){
		if(tmp<=MAXN)cnt[tmp]++;
		ans=ans*2%M;
	}
	for(int i=1;i<=MAXN;++i)calc(i,i);//预处理出每一个数的分解 
}
void solve(){
	int y;
	scanf("%d",&y);
	for(auto t:num[y]){
		if(t.p==2)cnt[2]+=t.b;
		else{
			div(cnt[t.p]);
			cnt[t.p]+=t.b;
			mul(cnt[t.p]);
		}
	}
	if(cntk)cout<<0<<"\n";//ans 中有 M 这个因子 
	else cout<<ans<<"\n";
}
signed main(){
	cin>>x>>q>>M;
	init();
	while(q--)solve();
} 
```

---

## 作者：huangrenheluogu (赞：0)

闲话：听说 F 更简单？但是赛时没开。还是写 Sol 纪念一下 VP 的时候差点切掉的 E 吧。

闲话 && 警钟：如果 `Wrong Answer on test 15`，那么需要把原来的乘除改成特判，先除掉 $M$ 的因子，然后再做乘除。

声明：为了我的习惯，距离是 $s_1$。

首先，我们要求解 $\sum\limits_{i=f-x}^fi=s_1$ 使得存在整数解 $x$，那么这个 $f$ 就可行。

接下来，我们化简一下。

$\sum\limits_{i=f-x}^fi=s\Leftrightarrow\dfrac{(2f-x)(x+1)}{2}=s\Leftrightarrow x^2+(1-2f)+(2s_1-2f)=0$。

因为 $2s_1$ 是常数，所以令 $s=2s_1$。

那么算一下 $\Delta=(1-2f)^2-4(s-2f)=4f^2+4f+1+4s=(2f+1)^2+4s$。

因为 $x$ 是整数，那么 $\sqrt{\Delta}$ 必然是整数，所以令 $\Delta=n^2,n>0$。

移项，平方差，可以得到 $(2f+1-n)(2f+1+n)=4s$。

现在好像很难处理，不管了，先算算 $x$。

$x_1=\dfrac{2f-1+n}{2},x_2=\dfrac{2f-1-n}{2}$。

发现为了让 $x\in \mathbb{N}$，需要 $n\equiv1(\bmod 2)$。

所以可以发现，$(2f+1-n)$ 和 $(2f+1+n)$ 都是偶数。

继续考察性质，发现 $(2f+1-n)+(2f+1+n)=2(2f+1)$，所以，这两个因式的平均数需要为奇数。

因为 $s$ 因子中至少有 $2$ 个 $2$，$4s$ 因子中至少有 $3$ 个 $2$，所以需要一个因式只有一个 $2$，其他 $2$ 在另外一个因式。

考虑到右边这个因式和 $x_2$ 满足 $2x_1+2=2f+1+n$，那么一个右边的因式可以唯一确定一个 $x_1$，同时，一个 $x_1$ 可以唯一确定一个 $f$。

那么就做完了。

记录每一个奇质因数 $p$ 的个数，记为 $cnt_p$，那么答案就是 $\prod\limits_{p\in prime}(cnt_p+1)$。

因为 $ans$ 里面包含 $M^k$，处理一下 $k$ 的取值是容易的。

对于更改，可以先预处理每一个数质因数及其个数。比如 $x$ 中有 $tot$ 个 $p$，那么乘上 $cnt_p+1$ 的逆元再乘上 $cnt_p+tot+1$ 即可。注意改变 $cnt_p$。同时，除法也要注意判断 $ans$ 里包含 $M^k$ 的指数 $k$ 的变化。

预处理复杂度 $O(V\sqrt{V})$，其中 $V$ 是值域（$10^6$），但是远远达不到这个上界，实测可以过。

询问的复杂度 $O(qnum_x\log p)$，其中 $num_x$ 是 $x$ 中因子的种数，不会超过 $10$ 个。

[code](https://codeforces.com/contest/1848/submission/239461963)

那个读优是因为本来想用 `__int128` 的，但是用洛谷的 C++14 必须用 `long long`，而且此题不用 `__int128`。

---

