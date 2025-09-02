# [ARC182C] Sum of Number of Divisors of Product

## 题目描述

我们称长度在 $1$ 到 $N$ 之间、每个元素在 $1$ 到 $M$ 之间的整数序列为**良好数列**。

对于一个良好数列，其**得分**定义为该序列所有元素的乘积 $X$ 的正约数个数。

良好数列共有 $\displaystyle\sum_{k=1}^{N} M^k$ 个，请你求出所有良好数列得分的总和，并对 $998244353$ 取余。

## 说明/提示

## 限制条件

- $1 \leq N \leq 10^{18}$
- $1 \leq M \leq 16$
- 输入均为整数

## 样例解释 1

良好数列有 $(1),(2),(3),(4),(5),(6),(7)$ 共 $7$ 个。它们的得分分别为 $1,2,2,3,2,4,2$，因此 $1+2+2+3+2+4+2=16$，答案为 $16$。

## 样例解释 2

例如 $(8,11)$ 或 $(1,8,2)$ 都是良好数列。计算这些数列的得分过程如下：
- $(8,11)$ 的元素乘积为 $8\times 11=88$。$88$ 的正约数有 $1,2,4,8,11,22,44,88$ 共 $8$ 个，因此 $(8,11)$ 的得分为 $8$。
- $(1,8,2)$ 的元素乘积为 $1\times 8\times 2=16$。$16$ 的正约数有 $1,2,4,8,16$ 共 $5$ 个，因此 $(1,8,2)$ 的得分为 $5$。

## 样例解释 3

不要忘记对 $998244353$ 取余。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 7```

### 输出

```
16```

## 样例 #2

### 输入

```
3 11```

### 输出

```
16095```

## 样例 #3

### 输入

```
81131 14```

### 输出

```
182955659```

# 题解

## 作者：wangshulin (赞：12)

# 前言
没有前言。
# 思路
考虑 dp，带点推公式。

首先，众所周知，计算正因数个数是有公式的：设 $x=\prod p_{i}^{c_{i}}$，其中 $p_{i}$ 都为质数，$c_{i}$ 都为非负整数，那么 $x$ 的正因数个数为 $\prod (c_{i}+1)$。

接着，假设在原来正因数个数为 $\prod (c_{i}+1)$ 的基础上乘上一个数 $x$，设 $g_{x,i}$ 表示 $x$ 最多能整除多少个 $p_{i}$，正因数个数就会变成 $\prod (c_{i}+g_{x,i}+1)$，但是，在 dp 的过程中不可能记录下来所有 $c_{i}$ 的值，只能记录整体的乘积，所以我们需要把公式中的 $g_{x,i}$ 拆出来，这么一来，设可能拥有的质因数集合为 $S$，那么：
$$
\prod (c_{i}+g_{x,i}+1)=\sum_{T \subset S}\left(\prod_{i \in T}(c_{i}+1)\right)\left(\prod_{i \in S,i \notin T} g_{x,i}\right)
$$
这样，我们就只需要记录对于所有的 $T$ 的 $\prod_{i \in T}(c_{i}+1)$ 就好了。

那么，dp 状态就出来了：$f_{i,S}$ 代表长度为 $i$ 的，只计算集合 $S$ 内的质因数的贡献值之和。

dp 转移即为：
$$
f_{i,S}=\sum_{T \subset S} f_{i-1,T} \sum_{j=1}^{m}\prod_{k \in S,k \notin T} g_{j,k}
$$

但是，朴素的 dp 时间复杂度为 $O(n \times m \times \pi(m) \times 3^{\pi(m)})$，而 $n$ 的值域极大，所以不能通过。

想到矩阵乘法优化 dp：设 $F_{i}$ 为矩阵 $[\begin{matrix} f_{i,0}&f_{i,1} & ... &\end{matrix}]$——所有 $f_{i,S}$ 依次排列的矩阵，考虑如何构造出矩阵 $R$，使得 $F_{i}=F_{i-1} \times R$。先展开矩阵乘的式：
$$
F_{i,k}=\sum_{j} F_{i-1,j} \times R_{j,k}
$$
然后对比上方 dp 转移式，发现对于集合 $S$：
$$
\forall T \subset S,R_{T,S}=\sum_{j=1}^{m}\prod_{k \in S,k \notin T} g_{j,k} \\
\forall T \not\subset S,R_{T,S}=0
$$
然后你发现还没做完——它要求所有 dp 值的和吧！？

其实我们可以在矩阵 $F_{i}$ 的最后一位弄一个表示前对于所有的 $j \le i$ 和任意 $S$，$f_{j,S}$ 的和，设这一位为 $P$，那么：
$$
\begin{aligned}
F_{i,P}&=F_{i-1,P}+\sum_{S} F_{i,S} \\
&=F_{i-1,P}+\sum_{S} \sum_{T} F_{i-1,T} \times R_{T,S}
\end{aligned}
$$
而，展开矩阵式，又有：
$$
F_{i,P}=\sum_{j} F_{i-1,j} \times R_{j,P}
$$
对比上方式子，可以推出：
$$
R_{T,P}=\sum_{S \supset T} R_{T,S} \\
R_{P,P}=1
$$
所以，$R$ 矩阵总算构造完成啦！

对矩阵 $R$ 做矩阵快速幂就做完啦！

预处理时间复杂度：$O(m \times \pi(m) \times 3^{\pi(m)})$。

矩阵快速幂时间复杂度：$O(\log n \times (2^{\pi(m)}+1)^3)$。

可以通过本题。
# 代码

```cpp
#include<stdio.h>
#include<string.h>
#define ll long long
const int M=17,K=6,MO=998244353;
int m,ans,pri[]={2,3,5,7,11,13},g[M][K];
ll n;
struct Matrix{
	int a[(1<<K)+1][(1<<K)+1];
	Matrix(){memset(a,0,sizeof(a));}
	Matrix operator*(const Matrix &o)const{
		Matrix t;
		for(int i=0;i<=(1<<K);i++){
			for(int j=0;j<=(1<<K);j++){
				for(int k=0;k<=(1<<K);k++){
					t.a[i][k]+=1ll*a[i][j]*o.a[j][k]%MO,t.a[i][k]%=MO;
				}
			}
		}
		return t;
	}
};
Matrix R;
void get_g(){
	for(int i=1;i<=m;i++){
		int x=i;
		for(int j=0;j<6;j++){
			while(x%pri[j]==0) g[i][j]++,x/=pri[j]; 
		}
	}
}
void get_R(){
	for(int S=0;S<(1<<K);S++){
		for(int T=S;;T=(T-1)&S){
			for(int j=1;j<=m;j++){
				int p=1;
				for(int k=0;k<6;k++){
					if((S&(1<<k))&&!(T&(1<<k))) p=1ll*p*g[j][k]%MO;
				}
				R.a[T][S]+=p,R.a[T][S]%=MO;
			}
			R.a[T][1<<K]+=R.a[T][S];
			if(!T) break;
		}
	}
	R.a[1<<K][1<<K]=1;
}
Matrix fp(Matrix x,ll y){
	Matrix t=x;
	y--;
	while(y){
		if(y&1) t=t*x;
		x=x*x,y>>=1;
	}
	return t;
}
int main(){
	scanf("%lld%d",&n,&m);
	get_g();
	get_R();
	R=fp(R,n);
	printf("%d\n",R.a[0][1<<K]);
	return 0;
}
```

---

## 作者：PrinceX (赞：7)

[link](https://www.luogu.com.cn/problem/AT_arc182_c)

爆标做法：可以将本题加强到 $m\le 1000$。

本做法大概也能说明为什么本题的 BM 的递推式会出奇的短，是 $O(\pi(m))$ 级别的。

考虑完全舍弃普通的增加一个数维护每个质数次数变化的思路。考虑一个事实：$d(a_1a_2\dots a_k)=\sum_{b[1\dots k],b_i\mid a_i}[\forall 1\le i<j\le n,\gcd(b_i,b_j)=1]$。证明由于每个质因子贡献独立，分开考虑即可。

我们先简化原问题，即我们只需要求 $len=n$ 的答案。

你注意到值域非常小，我们考虑枚举 $S\subseteq\{2,3,\dots,m\}$，表示 $S$ 中的数都在 $b$ 中出现过。你注意到 $b$ 中大于 $1$ 的数只能出现一次，那么 $b$ 中的所有数就都确定了（剩下的空位只能填 $1$）。这样子计算贡献是简单的。对于一个 $b_i\ne 1$，那么其对应的 $a_i$ 就有 $\lfloor\frac m{b_i}\rfloor$ 种选择，同时填 $1$ 的位置每一个 $a$ 都有 $m$ 种选择。那么设 $s2=\prod_{x\in S}\lfloor \frac m{x}\rfloor$，贡献即为 $s2\times \prod _{i=1}^{|S|}(n-i+1)\times m^{n-|S|}$。注意到后面两部分贡献只和 $|S|$ 有关，而 $|S|$ 的上限容易发现是 $O(\pi (m))$ 的，于是后面那部分可以在后面一起算。这样**暴力**算简化后的问题复杂度就是 $O(2^m+\pi(m)\log n)$ 的。

设一个集合的贡献是 $s2=\prod_{x\in S} \lfloor \frac m{x}\rfloor$，注意到后面的组合系数只和 $|S|$ 有关，所以我们可以将问题分成两部分：先将集合大小相同的 $|S|$ 贡献求和，再把组合系数算上。

### Part 1

第一部分注意到两两 $\gcd$ 为 $1$ 的限制，我们可以考虑记录质因子出现的集合然后进行 DP。

设 $T(x)$ 表示 $x$ 的质因子集合。我们按顺序加入 $[2,m]$。所以可以设 $f_{i,S}$ 表示现在集合中有 $i$ 个数，质因子出现集合为 $S$，那么转移即若 $S\&T(x)=0$，则 $f_{i+1,S|T(x)}\gets f_{i,S}\times \lfloor \frac m x\rfloor$。直接实现复杂度是 $O(m\pi(m)2^{\pi(m)})$。

但是还可以优化！你注意到大质数记录它就非常地无用。设 $maxp(x)$ 表示 $x$ 最大的质因子，你发现一个 $>\sqrt m$ 的质因子只会在一个数中出现一次，那么我们按 $maxp(x)$ 小到大的顺序加入 $[2,m]$，并同时加入 $maxp$ 相同的数，那么那些 $>\sqrt m$ 的质因子在加入后就不会在之后的数中出现，也就不用记录进状态里。时间复杂度 $O(m\pi(m)2^{\pi(\sqrt m)})$，可以轻松过 $m\le 1000$；经过简单优化甚至可以跑 $m\le 5000$（空间 1.4G）。

### Part 2

本来这题可以没有 Part 2（求的不是长度 $\le n$ 的答案和而是 $=n$ 的答案），但是出题人太坏了。

实际上问题是求 $\pi(m)+1$ 次 $\sum_{i=1}^{n}i^{\underline k}m^i$（$0\le k\le \pi(m)$）。由于 $i^{\underline k}$ 可以展开成关于 $i$ 的 $k$ 次多项式，而从 $x^i$ 到 $(x+1)^i$ 的递推是容易用 $(i+1)\times (i+1)$ 的矩阵维护的。将 $\sum_{i=1}^ni^{\underline k}m^i$ 看作多项式 $f(n)$，可以猜测 $f(n)$ 的递推式很短（实际上长度确实是 $k+eps$ 的）。跑 $\pi(m)+1$ 次 BM 算法，时间复杂度 $O(\pi(m)^3\log n)$ 或 $O(\pi(m)^3+\pi(m)^2\log \pi(m)\log n)$，仍能通过 $m\le 1000$。

但是跑 $\pi(m)+1$ 次 BM 算法就很唐！实际上你可以直接跑出 $n\le 2\pi(m)+eps$ 的答案（求出 $=n$ 的答案是容易做到 $O(\pi(m))$ 的），然后对这个直接跑一次 BM 即可，这样复杂度可以去掉一个 $\pi(m)$。

[提交记录](https://atcoder.jp/contests/arc182/submissions/59532972)

---

## 作者：_ANIG_ (赞：5)

[传送门](https://www.luogu.com.cn/problem/AT_arc182_c)

要求 $\sum\prod(a_i+1)$，其中，$a_i$ 为第 $i$ 个质数的指数和。

一位一位考虑，假设当前已经确定前 $n-1$ 为，枚举第 $n$ 位的值 $x$。

设 $b_i$ 为 $x$ 中第 $i$ 个质数的指数，则答案为 

$$\sum\prod(a_i+b_i+1)$$

$$=\sum\sum\limits_{S}\prod\limits_{i\in S}(a_i+1)\prod\limits_{i\notin S}b_i$$

设 $f_{n,S}\sum\sum\limits_{S}\prod\limits_{i\in S}(a_i+1)$，$g_{x,i}$ 为 $x$ 中第 $i$ 个质数的指数。

则 $f_{n,S}=\sum\limits_{x=1}^m\sum\limits_{T\subseteq S}f_{n-1,T}\prod\limits_{i\in S,i\notin T}g_{x,i}$。

矩阵乘法优化，复杂度 $O(T^3\log n)$，其中 $T=64$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mods=998244353,N=66,M=20,T=6,p[6]={2,3,5,7,11,13};
struct node{
	int w[N][N];
	friend node operator*(node a,node b){
		node c;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				c.w[i][j]=0;
				for(int k=0;k<N;k++){
					c.w[i][j]+=a.w[i][k]*b.w[k][j];
					c.w[i][j]%=mods; 
				}
			}
		}
		return c;
	}
}cs,zy;
node pows(node a,int b){
	if(b==1)return a;
	node res=pows(a,b>>1);
	res=res*res;
	if(b&1)res=res*a;
	return res;
}
int n,m,sm[M][6],res;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=0;j<6;j++){
			int x=i;
			while(x%p[j]==0)x/=p[j],sm[i][j]++;
		}
	}
	for(int i=0;i<(1<<T);i++)cs.w[0][i]=1;
	for(int j=1;j<=m;j++){
		for(int k=0;k<(1<<T);k++){
			zy.w[k][k]++;
			for(int l=k;l;l=l-1&k){
				int ans=1;
				for(int r=0;r<6;r++){
					if(l>>r&1^1)continue;
					ans=ans*sm[j][r]%mods;
				}
				zy.w[k^l][k]+=ans;
				zy.w[k^l][k]%=mods;
			}
		}
	}
	zy.w[(1<<T)-1][1<<T]=zy.w[1<<T][1<<T]=1;
	cs=cs*pows(zy,n);
	cout<<(cs.w[0][1<<T]-1+cs.w[0][(1<<T)-1])%mods;
}
```

---

## 作者：sunzz3183 (赞：4)

# [ARC182C] Sum of Number of Divisors of Product 题解

## 题意

给你 $N,M$ 让你找对于所有长度 $\le N$，值域在 $[1,M]$ 之间的序列的乘积求因子个数再求和。

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ M\ \leq\ 16 $

## 分析

看到 $m\le 16$ 先找出所有质数 $2,3,5,7,11,13$，一共有 $6$ 个，考虑状压也只有 $64$。

进一步发现 $n$ 巨大，但是状压状态很少，可以想到矩阵快速幂。

考虑怎么构造原 DP 序列和矩阵进行转移：

- 首先要求对于每个长度求和所以肯定要设一维来统计前缀和。

- 其次我们写出转移，并构造转移矩阵：

> 发现如果设“某一状态为某一质数有没有”无法转移，所以我们先令第 $i(0\le i<6)$ 个质数的编号为 $i$，个数为 $a_i$（$a_i=0$ 表示没有这个质数），则显然一个序列的答案为 $(a_0+1)(a_1+1)(a_2+1)(a_3+1)(a_4+1)(a_5+1)$ 而如果我们在序列末尾加入一个 $6$ 则答案就变成 $(a_0+2)(a_1+2)(a_2+1)(a_3+1)(a_4+1)(a_5+1)$。
>
> 根据 $c(a+x)(b+y)=c(ab+ay+bx+xy)$，设 $c=(a_2+1)(a_3+1)(a_4+1)(a_5+1)$ 原式子即为：
>
> $$(a_0+2)(a_1+2)c=(a_0+1)(a_1+1)c+(a_0+1)c+(a_1+1)c+c$$
>
> 所以我们设某一状态 $f_S$ 表示 $(a_i+1)(a_j+1)(a_k+1)\cdots(a_l+1),(i,j,k,\dots,l\in S)$ 的和。
>
> 那么转移就很简单了，我们枚举每一位和 $[1,m]$ 间的每一位数字，来看看对于原序列的系数是多少，然后给转移矩阵增加即可，因为一个数字最多有两个不同的质数，找两个变量记录一下即可。
>
> 式子形如：$f_{S}=f_S+f_{S-\{i\}}+f_{S-\{j\}}+f_{S-\{i\}-\{j\}}$
>
> 注意 $12=2\times 2\times 3$，所以所带系数不一定为 $1$，读者可试着自己推一下便于理解。
>
> 初始状态 $f_S=1,0\le S <64$，长度为 $len$ 时答案为 $f_{\{0,1,2,3,4,5\}}$。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
    while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*f;
}
const int N=66,mod=998244353;
struct Matrix{
    int n,m,num[N][N];
    Matrix(){
        n=m=0;
        memset(num,0,sizeof(num));
    }
}a,b;
Matrix operator*(const Matrix &x,const Matrix &y){
    Matrix c;c.n=x.n;c.m=y.m;
    for(int i=0;i<x.n;i++)
        for(int j=0;j<y.m;j++)
            for(int k=0;k<x.m;k++) 
                (c.num[i][j]+=x.num[i][k]*y.num[k][j]%mod)%=mod;
    return c;
}
Matrix ksm(Matrix a,int b){
    Matrix t;
    t.n=t.m=a.n;
    for(int i=0;i<a.n;i++)t.num[i][i]=1;
    for(;b;b>>=1,a=a*a)if(b&1)t=t*a;
    return t;
}
int n,m;
int id[17];
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    id[2]=1;id[3]=2;id[5]=3;id[7]=4;id[11]=5;id[13]=6;
    n=read();m=read();
    a.n=1,a.m=65;
    for(int i=0;i<64;i++)a.num[0][i]=1;
    b.n=b.m=65;
    b.num[64][64]=b.num[63][64]=1;
    for(int i=0;i<64;i++)
        for(int k=1;k<=m;k++){
            int t=k,t1=-1,t2=-1,s1=0,s2=0;
            for(int l=2;l<=t;l++)
                if(t%l==0){
                    if(~t1){t2=id[l]-1;while(t%l==0)t/=l,s2++;}
                    else{t1=id[l]-1;while(t%l==0)t/=l,s1++;}
                }
            b.num[i][i]++;
            if(t1>=0&&(i>>t1&1))b.num[i^(1<<t1)][i]+=s1;
            if(t2>=0&&(i>>t2&1))b.num[i^(1<<t2)][i]+=s2;
            if(t1>=0&&(i>>t1&1)&&t2>=0&&(i>>t2&1))b.num[i^(1<<t1)^(1<<t2)][i]+=s1*s2;
        }
    a=a*ksm(b,n+1);
    printf("%lld\n",a.num[0][64]-1);
    return 0;
}
```

---

## 作者：eastcloud (赞：2)

别写矩乘了，直接倍增转移更快也更方便。

这个题常规的方法不太好做，如果你枚举所有质因子的贡献显然不好算 14 这种有两个质因子的数的情况，又考虑到 $n$ 的范围，分治或者递推显然是比较好的选择。

这里我们先只算等于 $n$ 的情况，考虑如果你知道了长度为 $x$ 的答案为 $\sum_i a_{i,1}a_{i,2} \cdots a_{i,6}$，其中 $a_{i,k}$ 为第 $i$ 一种方案第 $k$ 个质因子的个数，这里先不考虑额外的 $+1$，那长度为 $x+y$ 的答案显然就是 $\sum_i \sum_j (a_{i,1}+a_{j,1}) \cdots (a_{i,6}+a_{j,6})$。

把求积的部分拆开就会发现这实际上是在枚举每一位选 $i$ 还是选 $j$ 然后把对应的部分乘起来，你把这样枚举划分的过程提到最外面，就会变成两边各枚举一个子集，要求子集不交且并等于全集，然后所有这样的方案乘积之和。

于是你只要维护所有质因子子集的贡献，这部分转移的时候也是类似枚举两个不交子集乘起来，由于质因子个数很少可以直接暴力 $3^n$，也可以集合幂级数做占位卷积优化变成 $2^nn$，但是没啥必要。

最后还得把前面少加的 1 加上，以及做小于等于而非等于的情况，前者转移类似，后者倍增的时候额外处理一下就行。


```cpp
#include<bits/stdc++.h>

#define ll long long
#define pi pair<ll,ll>
#define fi first
#define se second
#define cpy(x,y,s) memcpy(x,y,sizeof(x[0])*(s))
#define mem(x,v,s) memset(x,v,sizeof(x[0])*(s))
#define all(x) begin(x),end(x)
#define vi vector<ll> 
#define arr array
#define pb push_back
#define mp make_pair

#define mod 998244353

using namespace std;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}

void add(ll &x,ll y){x=(x+y>=mod?x+y-mod:x+y);}

vi f[63],g[63];
ll p[20];

vi merge(vi x,vi y){
    vi res(1<<6);
    for(ll S=0;S<(1<<6);S++){
        for(ll T=S;;T=S&(T-1)){
            add(res[S],x[T]*1ll*y[S^T]%mod);
            if(!T)break;
        }
    }
    return res;
}

int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    ll n=read(),m=read();
    f[0].resize((1<<6));
    p[1]=2;p[2]=3;p[3]=5;p[4]=7;p[5]=11;p[6]=13;
    for(ll i=1;i<=m;i++){
        for(ll j=0;j<(1<<6);j++){
            ll res=1;
            for(ll k=1;k<=6;k++){
                if(!(j&(1<<(k-1))))continue;
                ll c=0,tmp=i;
                while(tmp%p[k]==0)c++,tmp/=p[k];
                res=(res*1ll*c)%mod;
            }
            add(f[0][j],res);
        }
    }
    g[0]=f[0];
    for(ll i=1;i<=62;i++){
        g[i]=merge(g[i-1],g[i-1]);
        vi tmp=merge(f[i-1],g[i-1]);
        f[i].resize(1<<6);
        for(int j=0;j<(1<<6);j++)add(f[i][j],(f[i-1][j]+tmp[j])%mod);
    }
    ll flag=0;vi res((1<<6));
    for(ll i=62;i>=0;i--){
        if(n&(1ll<<i)){
            if(!flag)res=f[i];
            else{
                vi tmp=merge(g[i],res);
                for(int j=0;j<(1<<6);j++)add(tmp[j],f[i][j]),res[j]=tmp[j];
            }
            flag=1;
        }
    }
    vi S(1<<6);
    for(int j=0;j<(1<<6);j++)S[j]=1;
    res=merge(res,S);
    write(res[(1<<6)-1]);
}
```

---

## 作者：大眼仔Happy (赞：2)

简要题意：

定义一个序列 $X$ 的价值为 $\sigma_0(\prod X_i)$。

求所有长度 $\le n$，值域为 $[1, m]$ 的序列的价值总和。

---

$M\le 16$，说明只有 $\pi(16)=6$ 个质因数。

我们用一个向量 $[t_1, t_2, t_3, t_4, t_5, t_6]$ 表示一个序列的 $\prod$ 所对应的质因数的次数 $+1$，那么价值则为向量元素的积。

现在你知道 $\sum (\prod t_i)$，然后加入一个元素 $x$，相当于变成了 $\sum \prod({t_i + a_i})$。其中 $a_i$ 是 $x$ 表示的向量。

把括号展开一下，不就是 $\sum(\sum_{T\subseteq S}(\prod_{i\in T}t_i\times \prod_{i\in S-T} a_i))$ 吗？

而且虽然是 $M$ 个数，但是你发现可以并到一个 $a$ 上去吧。

于是矩阵乘法优化一下，$\mathbf A_{S,T} = a_{S-T}$。时间复杂度是 $O(8^k\log n)$，其中 $k=6$。

想到之后剩了 22min，但是并没有写出来。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 6, V = (1 << N), U = V - 1;
#define ll long long
const ll mod = 998244353;
ll inline read() {
    ll num = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        num = (num << 3) + (num << 1) + (ch ^ 48);
        ch = getchar();
    }
    return num * f;
}
ll n, m;
ll inc(const ll &x, const ll &y) {
    return x + y >= mod ? x + y - mod : x + y;
}
struct Matrix {
    ll M[65][65];
    Matrix(bool isT = 0) {
        memset(M, 0, sizeof(M));
        if (isT)for (int i = 0; i <= V; i++)M[i][i] = 1;
    }
    ll* operator [](const int x) {
        return M[x];
    }
    const ll *operator [](const int x)const {
        return M[x];
    }
    friend Matrix operator *(const Matrix &A, const Matrix &B) {
        Matrix res;
        for (int i = 0; i <= V; i++)
            for (int j = 0; j <= V; j++)
                for (int k = 0; k <= V; k++)
                    res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % mod;
        return res;
    }
    void print()const {
        for (int i = 0; i <= V; i++) {
            for (int j = 0; j <= V; j++)
                printf("%lld ", M[i][j]);
            printf("\n");
        }
    }
} A, ans;
int a[V], b[17][N];
void init() {
    for(int i = 1; i <= m; i++) {
        int x = i;
        while(x % 2 == 0)b[i][0]++, x /= 2;
        while(x % 3 == 0)b[i][1]++, x /= 3;
        while(x % 5 == 0)b[i][2]++, x /= 5;
        while(x % 7 == 0)b[i][3]++, x /= 7;
        while(x % 11 == 0)b[i][4]++, x /= 11;
        while(x % 13 == 0)b[i][5]++, x /= 13;
    }
    for(int S = 0; S < V; S++) {
        for(int i = 1; i <= m; i++) {
            int prod = 1;
            for(int j = 0; j < N; j++)
                if((S >> j) & 1)prod *= b[i][j];
            a[S] += prod; 
        }
    }
    for(int S = 0; S < V; S++) {
        A[S][0] = a[S];
        for(int T = S; T; T = (T - 1) & S) {
            A[S][T] = a[S ^ T];
        }
    }
    A[V][V] = 1;
    for(int i = 0; i < V; i++)A[V][i] = A[U][i];
    for(int i = 0; i < V; i++)ans[i][0] = 1;
}
Matrix qp(Matrix A, ll n) {
    Matrix res(1);
    while(n) {
        if(n & 1)res = res * A;
        A = A * A, n >>= 1;
    }
    return res;
}
int main() {
#ifdef file
    freopen("ARC182C.in", "r", stdin);
    freopen("ARC182C.out", "w", stdout);
#endif
    n = read(), m = read(), init();
    ans = qp(A, n) * ans; 
    printf("%lld", ans[V][0]);
    return 0;
}
```

> 搞笑的是第一次快读没用 long long，第二次 $n$ 没用 long long，然后 WA/TLE 两发。

---

## 作者：WrongAnswer_90 (赞：2)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18356106)

### [[ARC182C] Sum of Number of Divisors of Product](https://www.luogu.com.cn/problem/AT_arc182_c)

见过一万遍的套路啊啊啊啊啊。

首先如果序列乘积是 $\prod c_i^{p_i}$，答案就是 $\prod (p_i+1)$。$M$ 以内的质数个数只有 $6$ 个：$\{2,3,5,7,11,13\}$。

然后考虑这个式子的组合意义：对于每个质因子，可以看成在其每次出现的时候可以选它，这样每个质因子需要恰好被选一次。对于 $+1$ 的问题可以一开始就把所有无论选还是不选的答案设成 $1$。

状压上面这个东西，$0$ 表示这一位还没选，$1$ 表示选了。预处理转移矩阵，因为要求序列长度 $\leq n$，所以还要开一维记答案，总复杂度 $\mathcal O(T^3\log n)$，其中 $T=65$。

```cpp
int n,m,v[6];
struct Matrix{int f[65][65];Matrix(){memset(f,0,sizeof(f));}}M;
struct Vector{int f[65];Vector(){memset(f,0,sizeof(f));}}F;
inline Matrix operator *(const Matrix x,const Matrix y)
{
	Matrix z;
	for(int i=0;i<65;++i)for(int j=0;j<65;++j)for(int k=0;k<65;++k)
	Madd(z.f[i][j],Cmul(x.f[i][k],y.f[k][j]));
	return z;
}
inline Vector operator *(const Vector x,const Matrix y)
{
	Vector z;
	for(int j=0;j<65;++j)for(int k=0;k<65;++k)
	Madd(z.f[j],Cmul(x.f[k],y.f[k][j]));
	return z;
}
const int P[6]={2,3,5,7,11,13};
inline void mian()
{
	read(n,m),M.f[64][64]=1;
	for(int i=1;i<=m;++i)
	{
		int x=i;memset(v,0,sizeof(v));
		for(int j=0;j<6;++j)while(x%P[j]==0)++v[j],x/=P[j];
		for(int j=0;j<64;++j)
		{
			for(int k=j;;k=(k-1)&j)
			{
				int s=1;
				for(int l=0;l<6;++l)if((k^j)>>l&1)Mmul(s,v[l]);
				Madd(M.f[k][j],s);
				if(j==63)Madd(M.f[k][64],s);
				if(!k)break;
			}
		}
	}
	for(int i=0;i<64;++i)F.f[i]=1;
	for(;n;n>>=1,M=M*M)if(n&1)F=F*M;
	write(F.f[64]);
}
```

---

## 作者：lingziyi2025 (赞：2)

# [ARC182C] Sum of Number of Divisors of Product 题解

[link](ttps://www.luogu.com.cn/problem/AT_arc182_c)

看到 $n\le 10^{18},m\le 16$，且每次转移过程相同，想到矩乘。

根据题意，想到把每个数的贡献拆成质数统计，贡献即 $(c_2+1)(c_3+1)(c_5+1)(c_7+1)(c_{11}+1)(c_{13}+1)$。

于是共 $6$ 个质数，假如选了个 $12$，那么在原来的基础上有 $(c_2+2)(c_3+1)c_5c_7c_{11}c_{13}$。

考虑设状态，发现暴力地，如果要算当前贡献，就必须将 $c_i$ 存下来，这样是不行的。

考虑变换式子，拆开，得到 $c_2c_3c_5c_7c_{11}c_{13}+2c_3c_5c_7c_{11}c_{13}+c_2c_5c_7c_{11}c_{13}+2c_5c_7c_{11}c_{13}$。

发现是增加了 $2c_3c_5c_7c_{11}c_{13}+c_2c_5c_7c_{11}c_{13}+2c_5c_7c_{11}c_{13}$。

就是说，把上一次的 $c_3c_5c_7c_{11}c_{13}$ 乘上一个系数，然后累加到 $c_2c_3c_5c_7c_{11}c_{13}$ 里面。

结合 $6$ 个质数，想到可以开 $2^{6}\times 2^6$ 的矩阵，然后按照上面的转移方式进行矩乘转移。

发现题目还要求前缀和，可以再开一行，每次将 $c_2c_3c_5c_7c_{11}c_{13}$ 的贡献累加入这一行，这样就能实现前缀和效果。

```c++
#include<bits/stdc++.h>
#define rg register int
#define fo(i,l,r) for(rg i=l;i<=r;i++)
#define dfo(i,r,l) for(rg i=r;i>=l;i--)
#define frein freopen("in.txt","r",stdin);
#define freout freopen("out.txt","w",stdout);
#define fre(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define outa(l,r,a) {fo(i,l,r)cout<<a[i]<<" ";cout<<"\n";}
#define outm(l1,r1,l2,r2,a) {fo(i,l1,r1){fo(j,l2,r2)cout<<a[i][j]<<" ";cout<<"\n";}cout<<"\n";}
#define BZ cout<<"----------------\n";
#define ll long long
using namespace std;
#define mo 998244353
void add(int &x,int y){x+=y,x=x>mo?x-mo:x;}
const int N=70;ll n;bool pd;
int m,k,np,al,tp;
int pr[6]={2,3,5,7,11,13};
int c[17][6]={
	{0,0,0,0,0,0},
	
	{0,0,0,0,0,0},
	{1,0,0,0,0,0},
	{0,1,0,0,0,0},
	{2,0,0,0,0,0},
	{0,0,1,0,0,0},
	
	{1,1,0,0,0,0},
	{0,0,0,1,0,0},
	{3,0,0,0,0,0},
	{0,2,0,0,0,0},
	{1,0,1,0,0,0},
	
	{0,0,0,0,1,0},
	{2,1,0,0,0,0},
	{0,0,0,0,0,1},
	{1,0,0,1,0,0},
	{0,1,1,0,0,0},
	{4,0,0,0,0,0},
};
bool bit(int x,int y){return ((x>>y)&1);}
struct mat{int a[N][N];}x,ans;
mat operator*(mat a,mat b){
	mat c;
	fo(i,0,k)
	fo(j,0,k){
		c.a[i][j]=0;
		fo(l,0,k)add(c.a[i][j],1ll*a.a[i][l]*b.a[l][j]%mo);
	}return c;
}
mat mksm(ll y){
	mat res;
	fo(i,0,k)
	fo(j,0,k)res.a[i][j]=(i==j);
	while(y){
		if(y&1)res=res*x;
		x=x*x;y>>=1;
	}return res;
}
int main(){
	cin>>n>>m;np=5;
	if(m==1){cout<<n%mo;return 0;}
	fo(i,0,5)if(pr[i]>m){np=i-1;break;}
	k=(1<<(np+1));
	fo(S,0,k-1){
		fo(i,1,m){
			al=0;
			fo(j,0,np)if(c[i][j]!=0&&bit(S,j))al|=(1<<j);
			fo(T,0,k-1){
				if((al&T)!=T)continue;tp=1;
				fo(j,0,np)if(bit(T,j))tp=tp*c[i][j];
				x.a[S][S^T]+=tp;
			}
		}
	}
	fo(j,0,k-1)x.a[k][j]=x.a[k-1][j];x.a[k][k]=1;
	fo(i,0,k-1)ans.a[i][0]=1;
	x=mksm(n);ans=x*ans;
	cout<<ans.a[k][0];
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

参考了其他大佬的题解。

> 求所有长度小于等于 $n$，值域在 $[1,m]$ 的序列的元素乘积的因子个数之和。$n\leq 10^{18},m\leq 16$。

显然因子个数跟每个质因子有关，发现值域很小，$16$ 以内的质数只有 $6$ 个，于是可以往状压质数状态的方向去想。记 $m$ 以内有 $t$ 个质数。

对于乘积 $S$，设他的质因子分解得到 $S=\prod_{i=1}^t p_i^{c_i}$，那么因数个数为 $d(S)=\prod_{i=1}^t(c_i+1)$，如果对他再乘以一个数 $x$，$x=\prod_{i=1}^t g_i$，则 $d(Sx)=\prod(c_i+g_i+1)$。

这个乘积的因数个数感觉不能直接从两个数得到，考虑类似乘法分配律的方式分开计算贡献。我们记 $f_S$ 表示质因子属于 $S$ 集合内的 $\prod (c_i+1)$。那么针对乘上一个数 $x$，因为：

$$\prod_{i\in S} (c_i+g_i+1)=\sum_{T\subseteq S}\left(\prod_{i\in T} (c_i+1)\right)\left(\prod_{i\in S\wedge i\notin T}g_i\right).$$

所以令 $c_{x,i}$ 表示 $x$ 含有质因子 $p_i$ 的个数，则有转移：

$$f'_S=\sum_{T\subseteq S}f_T\sum_{x=1}^m\prod_{d\in S\wedge d\notin T}^tc_{x,d}.$$

上面那个等式可以通过乘法分配律拆出括号得到。然后我们就得到了一个 $O(nm\cdot \pi(m)\cdot3^{\pi(m)})$ 的 dp。

容易发现，$n$ 奇大无比而这个 dp 的状态数比较少，考虑矩阵快速幂即可。矩阵的系数就是上面的递推式后面的系数，即矩阵元素 $A_{T,S}$ 为：

$$A_{T,S}=\sum_{x=1}^m\prod_{d\in S\wedge d\notin T}^tc_{x,d}.$$

然后直接快速幂即可。但是所求的是所有长度的方案之和，我们考虑在矩阵最后塞一维求和的即可,记这个求和的元素为 $P$，dp 转移为：

$$P_i=P_{i-1}+\sum_{S}f_{i,S}=P_{i-1}+\sum_{S}\sum_{T\subseteq S}f_{i-1,T}\cdot A_{T,S}.$$

即：

$$P_i=P_{i-1}+\sum_{T}f_{i-1,T}\sum_{S\supseteq T}A_{T,S}.$$

那么就得到了矩阵中 $P$ 的转移系数：

$$A_{T,P}=\sum_{S\supseteq T}A_{T,S}.$$

以及自己对自己的贡献 $A_{P,P}=1$，然后做完了。时间复杂度 $O(m\cdot\pi(m)\cdot3^{\pi(m)}+2^{3\pi(m)}\log n)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 65;
const LL MOD = 998244353;
int m, tot, len, prime[N]; LL n;
bool check(int x) {
	for (int i = 2; i * i <= x; i ++) if (x % i == 0) return 0;
	return 1;
}
struct Matrix {
	LL a[N][N];
	void clear() { memset(a, 0, sizeof a); }
};
const Matrix operator*(const Matrix& a, const Matrix& b) {
	Matrix c; c.clear();
	for (int i = 0; i < len; i ++) for (int k = 0; k < len; k ++) for (int j = 0; j < len; j ++)
		c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % MOD) % MOD;
	return c;
}
Matrix mat; int cnt[N];
Matrix Qpow(Matrix x, LL k) {
	Matrix ret, tmp = x; for (int i = 0; i < len; i ++) ret.a[i][i] = 1;
	while (k) {
		if (k & 1) ret = ret * tmp;
		tmp = tmp * tmp; k >>= 1;
	} return ret;
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 2; i <= m; i ++) if (check(i)) prime[tot ++] = i;
	len = (1 << tot) + 1;
	for (int i = 1; i <= m; i ++) {
		for (int j = 0, tmp = i; j < tot; j ++) while (tmp % prime[j] == 0) cnt[j] ++, tmp /= prime[j];
		for (int j = 0; j < 1 << tot; j ++) {
			for (int k = j; ; k = (k - 1) & j) {
				LL prod = 1;
				for (int l = 0; l < tot; l ++) if (!((k >> l) & 1) && ((j >> l) & 1)) prod *= cnt[l];
				mat.a[k][j] = (mat.a[k][j] + prod) % MOD;
				if (!k) break;
			}
		}
		for (int j = 0, tmp = i; j < tot; j ++) while (tmp % prime[j] == 0) cnt[j] --, tmp /= prime[j];
	} mat.a[1 << tot][1 << tot] = 1;
	for (int j = 0; j < 1 << tot; j ++) for (int k = j; ; k = (k - 1) & j) { 
		mat.a[k][1 << tot] = (mat.a[k][1 << tot] + mat.a[k][j]) % MOD; if (!k) break; 
	} mat = Qpow(mat, n); cout << mat.a[0][1 << tot];
	return 0;
}
```

---

## 作者：xishanmeigao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc182_c)

首先将数质因数分解，两个数相乘就是指数相加，答案就是指数加一再相乘，可以用矩阵维护。

显然我们要维护 $\sum \prod\limits_{i=1} ^6(c_i+1)$（只有 $6$ 个质数）。每次加入一个数会变成 $\sum \prod \limits_{i=1}^6(c_i+1+c_i')$。多项式展开后，其实我们要维护的就是一个子集卷积的过程。设 $f_s=\prod \limits_{i\in s}c_i$，将矩阵 $g$ 初始化为 $1$，显然转移就是 $g'_s=\sum\limits_{t\sub s} g_t \times f_{s/t}$。拿矩阵维护一下这个东西就好了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=(1<<6)+10,M=(1<<6),MOD=998244353;
const int p[7]={0,2,3,5,7,11,13};

LL n;
int m;
int c[20][10],f[N];

void addm(int &x,int y){(x+=y<0? MOD+y:y)%=MOD;}

struct Matrix
{
	int v[N][N];

	Matrix(){memset(v,0,sizeof(v));}

	friend Matrix operator * (const Matrix &A,const Matrix &B)
	{
		Matrix C;
		for(int i=0; i<=M; i++)
			for(int j=0; j<=M; j++)
				for(int k=0; k<=M; k++)
					addm(C.v[i][j],1LL*A.v[i][k]*B.v[k][j]%MOD);
		return C;
	}
}A,Ans;

void divide(int x)
{
	int tmp=x;
	for(int i=1; i<=6; i++)
		while(tmp%p[i]==0)
			c[x][i]++, tmp/=p[i];
	for(int s=0; s<M; s++)
	{
		int cur=1;
		for(int i=1; i<=6; i++)
			if(s&(1<<(i-1))) cur*=c[x][i];
		f[s]+=cur;
	}
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	scanf("%lld%d",&n,&m);

	for(int i=1; i<=m; i++)
		divide(i);

	for(int i=0; i<M; i++)
		Ans.v[0][i]=1;
	for(int s=0; s<M; s++)
	{
		A.v[0][s]=f[s];
		if(s==M-1) A.v[0][M]=f[s];
		for(int t=s; t; t=(t-1)&s)
		{
			A.v[t][s]=f[s^t];
			if(s==M-1) A.v[t][M]=f[s^t];
		}
	}
	A.v[M][M]=1;

	while(n)
	{
		if(n&1) Ans=Ans*A;
		A=A*A; n>>=1;
	}	

	printf("%d\n",Ans.v[0][M]);
	
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[arc182c](https://www.luogu.com.cn/problem/AT_arc182_c)
### 思路
有 $6$ 个小于 $14$ 的质数，设这 $6$ 个质数的指数分别为 $x_1,\dotsb,x_6$。$ans=\sum (\prod_{i=1}^d (x_i+1))$。状压这 $6$ 个数，维护 $val_s=\prod_{i=1}^6 (x_i\times [s二进制第 i位为1]+[s二进制第 i位为0])$。当加入一个数时，某些 $x_i$ 会加 $d$，$s$ 二进制第 $i$ 位为 $1$ 的 $val_s$ 会从 $s$ 的子集且一些二进制第 $i$ 位为 $0$ 的 $t$ 的 $val_t$ 转移来。

矩阵快速幂维护转移。额外维护一个位置 $p$ 表示答案之和，所有的 $e_{s,p}=1$。

### code
```cpp
int n,m,l=64;
struct mat{
	int e[66][66];
	mat(){
		for(int i=0;i<=l;i++){
			for(int j=0;j<=l;j++)e[i][j]=0;
		}
	}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<=l;i++){
			for(int j=0;j<=l;j++){
				for(int k=0;k<=l;k++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}bas,mul;
mat one(){
	mat res;
	for(int i=0;i<=l;i++)res.e[i][i]=1;
	return res;
}
mat ksm(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int pre[6]={2,3,5,7,11,13};
void work(){
	n=read();m=read();
	mul.e[0][0]=1;
	for(int s=0;s<l;s++)bas.e[s][l]=1,bas.e[s][s]=m;
	bas.e[l][l]=1;
	for(int i=1;i<=m;i++){
		for(int s=0;s<l;s++){
			for(int t=1;t<=s;t++)if((s&t)==t){
				bool fl=1;
				for(int j=0;j<6;j++)if(i%pre[j]!=0&&(t&(1<<j)))fl=0;
				if(!fl)continue;
				int val=1,x=i;
				for(int j=0;j<6;j++)if(t&(1<<j)){
					int cnt=0;
					while(x%pre[j]==0)x/=pre[j],++cnt;
					val=val*cnt;
				}
				bas.e[s^t][s]+=val;
			}
		}
	}
	mul=mul*ksm(bas,n+1);
	printf("%lld\n",mul.e[0][l]-1);
}
```

---

