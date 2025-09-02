# [CSGRound3] 出游

## 题目描述

学校组织了一次暑期出游活动，报名将在第 $T$ 天截止。

一共有 $n$ 位同学，第 $i$ 位同学有 $a_i$ 位朋友。朋友关系是单向的，换句话说，小 Z 有一个朋友是小 Y，并不意味着小 Y 一定也有一个朋友是小 Z。另外，自己也可能是自己的朋友。

第 $0$ 天时，每位同学会决定自己是否参加活动。第 $i$ 位同学有 $p_i$ 的概率决定参加，$1-p_i$ 的概率决定不参加。

接下来的 $T$ 天里，每位同学会重新决定自己是否参加活动。第 $i$ 位同学这一天决定参加活动，当且仅当至少有一个他的朋友在前一天决定参加，否则便不参加。

你需要求出参加活动的同学人数期望，答案对 $998244353$ 取模。

## 说明/提示

**【样例 1 解释】**

| 天数 | 第一位同学去的概率 | 第二位同学去的概率 | 第三位同学去的概率 |
| :--: | :----------------: | :----------------: | :----------------: |
| $0$  |        $1$         |        $0$         |     $\frac 12$     |
| $1$  |    $\frac 12 $     |    $\frac 12 $     |        $0$         |

---

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（3 points）：$T = 0$。
- Subtask 2（14 points）：$T = 1$。
- Subtask 3（33 points）：$n \le 10$。
- Subtask 4（20 points）：$T \le 5 \times 10^3$。
- Subtask 5（15 points）：$n \le 100$。
- Subtask 6（15 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 500$，$0 \le T \le 10^9$，$0 \le p_i < 998244353$，$0 \le a_i \le n$ 且朋友互不相同。

## 样例 #1

### 输入

```
3 1
1 2 2 3
0 1 3
499122177 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3
1 2 2 3
0 1 3
233 1 2```

### 输出

```
466
```

# 题解

## 作者：万弘 (赞：12)

//upd:修复了最后时间复杂度分析的错误,增加代码注释


首先,如果$A$发生的概率$p_a=\frac{b1}{a1}+\frac{b2}{a2}$  
且$\frac{b1}{a1}\equiv p_1(mod\ P),\frac{b2}{a2}\equiv p_2(mod\ P)$  
那么$p_a\equiv p_1+p_2(mod\ P)$  
所以概率/期望加法的时候,直接加然后取模就可以了,不用求逆元之类.

接下来开始讲做法:  
先特判$T=0$:  
第一天的概率即为最后一天的概率.每一个人的贡献就是$p_i$,总期望值$E=\sum_{i=1}^n1*p_i=\sum_{i=1}^np_i$

$T=1$:  
记$trans_{i,j}$表示当$i$去则下一天$j$是否必须去(是则为1,否则为0)  
考虑$i$最后去的概率$last_i$的反面,即$i$不去.这需要所有他的朋友前一天都没去.那么
$$1-last_i=\prod_{trans_{j,i}=1} (1-p_j)$$
暴力求即可,时间复杂度$O(n^2)$

算法1:  
设$trans_{i,j}^k$表示如果$i$第0天去了,$j$在第$k$天是否必须去.
那么
$$trans_{i,j}^k=OR_{p=1}^n trans^{k-1}_{i,p}and\ trans_{p,j}$$

这里$OR$是我自创的符号,类似于$\sum$,即$(trans^{k-1}_{i,1}and\ trans_{1,j})\ or\ (trans^{k-1}_{i,2}and\ trans_{2,j})\ or\ (trans^{k-1}_{i,3}and\ trans_{3,j})...or\ (trans^{k-1}_{i,n}and\ trans_{n,j})$)  
嗯于是暴力递推计算这个式子,最后把$trans_{i,j}^k$算出,时间复杂度$O(n^3T)$  
最后的式子变成
$$1-last_i=\prod_{trans_{j,i}^k=1} (1-p_j)$$
~~似乎还是同样的17pts~~  
算法2:  
求$trans$的式子非常类似矩阵乘法.并且$or$运算满足结合律,所以使用矩阵快速幂优化.时间复杂度$O(n^3logT)$  
关键部分:
```cpp
#define MAXN 511
struct mat
{
    bool a[MAXN][MAXN];
    void operator *=(const mat& t)
    {
        bool res[MAXN][MAXN];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                res[i][j]=0;
                for (int k = 1; k <= n; ++k)
                    res[i][j]|=(a[i][k]&t.a[k][j]);
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                a[i][j]=res[i][j];
    }
}trans;
......
mat Qpow(ll m)//矩阵快速幂,m是乘的次数,即T
{
    --m;//注意T=0要特判掉的
    mat res=trans,a=trans;
    while(m)
    {
        if(m&1)res*=a;
        a*=a;
        m>>=1;
    }
    return res;//即trans^k
}
```
时间复杂度$O(n^3logT)$,直接就85pts了,很优秀.  
算法3:  
再观察下矩阵乘法那里.整个矩阵都是01矩阵,那么每一行,每一列都是01向量.考虑每一行压进一个bitset,加快乘法效率.  
先把程序中的$t$按对角线对称得到$t'$,即$t'[j][k]=t[k][j]$  
那么
$$res[i][j]=OR_{p=1}^na[i][k]\ and\ t'[j][k]$$
$a,t'$压成bitset,得到
$$res[i][j]=a[i]\ and\ t'[j]$$
(注意$res[i][j]$是bool,$a[i]\ and\ t'[j]$是bitset,所以这里赋值符应该是$a[i]\ and\ t'[j]$中是否有1)
矩阵乘法的时间复杂度优化为$O(\frac{n^3}{w})$,总时间复杂度$O(\frac{n^3logT}{w})$,AC.

代码存在一些变量名于题解不一致的情况,读者不必拘泥于代码
```cpp
/**********/省略快读
#define MAXN 511
const ll mod=998244353;
ll n,m;//人数,天数
struct mat
{
    std::bitset<MAXN>a[MAXN];
    void operator *=(const mat& t)//bitset优化矩阵乘法
    {
        std::bitset<MAXN>res[MAXN],tmp[MAXN];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                tmp[i][j]=t.a[j][i];
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                res[i][j]=(a[i]&tmp[j]).any();
        }
        for (int i = 1; i <= n; ++i)
            a[i]=res[i];
    }
}trans;
ll p[MAXN],f[MAXN];//初始概率,结束概率(即1-last)
ll update(ll x)//对mod取模
{
    return (x%mod+mod)%mod;
}
......
mat Qpow(ll m)//矩阵快速幂
{
    --m;
    mat res=trans,a=trans;
    while(m)
    {
        if(m&1)res*=a;
        a*=a;
        m>>=1;
    }
    return res;
}
int main()
{
    n=read(),m=read();
    for (int i = 1; i <= n; ++i)
    {
        p[i]=read();f[i]=1;(一开始是1,即假设不去)
        ll x=read();
        while(x--)
        {
            ll v=read();
            trans.a[v][i]=1;//如果v去,i必须去
        }
    }
    if(m==0)
    {
        ll ans=0;
        for (int i = 1; i <= n; ++i)ans=update(ans+p[i]);
        printf("%lld",ans);
        return 0;
    }
    mat g=Qpow(m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if(g.a[i][j])f[j]=update(f[j]*(1-p[i]));//上面的式子反过来,变成i对j的贡献(实现的时候这样写了,但写题解的时候发现那样更好理解
    ll ans=0;
    for (int i = 1; i <= n; ++i)ans=update(ans+1-f[i]);//最后直接求和了
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：xht (赞：9)

套路题。

给定一张 $n$ 个点的有向图，一开始选择一些点，这些点每次走一步，问 $T$ 步后这些点可能在哪些位置。

类似这样的问题都可以用 bitset 优化矩阵乘法做到 $\mathcal O(\frac{n^3\log T}w)$，比如 [CF576D Flights for Regular Customers](https://www.luogu.com.cn/problem/CF576D)。

~~我这题代码就是从那题的代码改的。~~

最终你会得到一个矩阵 $a$，$a_{i,j}$ 表示一开始如果 $i$ 被选择了，那么最终 $j$ 会被选。

那么 $j$ 最后不参加的概率就是所有 $a_{i,j} = 1$ 的 $i$ 一开始不参加的概率。

人数的期望就是所有人参加的概率之和。

```cpp
const int N = 500;
int n, m;
modint p[N], ans;
#define bt bitset<N>
struct mt {
	bt a[N];
	inline friend mt operator * (mt x, mt y) {
		mt z;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (x.a[i][j]) z.a[i] |= y.a[j];
		return z;
	}
} a, b;

inline void ksm(mt x, int y, mt &z) {
	while (y) {
		if (y & 1) z = z * x;
		x = x * x, y >>= 1;
	}
}

int main() {
	rd(n), rd(m);
	for (int i = 0, k; i < n; i++) {
		rd(p[i]), rd(k);
		for (int j = 0, x; j < k; j++)
			rd(x), a.a[--x][i] = 1;
		b.a[i][i] = 1;
	}
	ksm(a, m, b);
	for (int i = 0; i < n; i++) {
		modint o = 1;
		for (int j = 0; j < n; j++)
			if (b.a[j][i]) o *= 1 - p[j];
		ans += 1 - o;
	}
	print(ans);
	return 0;
}
```

---

## 作者：Karry5307 (赞：6)

### 题面

有 $n$ 个人，第 $0$ 天每个人去出游的概率为 $p_i$。从第 $1$ 天开始，如果一个人至少有一个朋友选择去出游，则他也选择去，否则就不去。求第 $T$ 天出游人数的期望。

$\texttt{Data Range:}n\leq 500,T\leq 10^3$

### 题解

好题。

先来看一个似乎正确的思路：

我们设 $x$ 的所有朋友构成的集合为 $f_x$，第 $i$ 个人第 $j$ 天出游的概率为 $dp_{i,j}$，那么有

$$\begin{cases}dp_{i,0}=p_i\\dp_{i,j}=(1-\prod\limits_{x\in f_i}(1-dp_{x,j-1}))\end{cases}$$

我们把下面那个式子变形一下，有

$$1-dp_{i,j}=\prod\limits_{x\in f_i}(1-dp_{x,j-1})$$

我们设 $f_{i,j}=1-dp_{i,j}$，那么有

$$\begin{cases}f_{i,0}=1-p_i\\f_{i,j}=\prod\limits_{x\in f_i}f_{x,j-1}\end{cases}$$

然而这种 $\texttt{dp}$ 是错的，被 Mital 神仙 hack 了，具体错误原因可以看[这里](https://www.luogu.com.cn/discuss/show/185580)

注意到，一个初始局面决定了后面的所有状态。

我们自然考虑如果 $i$ 有朋友 $j$ 那就连 $j\rightarrow i$ 的边，因为 $i$ 某一天的决策受到 $j$ 昨天的决策的影响。

那么完结局面等价于在这张图上初始存在一些关键点，走 $T$ 步能到达的点的贡献的乘积。

所以说，某一个点的答案取决于那些走 $T$ 步能够到达他的点的贡献的乘积。

这种东西我们可以建反图，问题变成从这个点走 $T$ 步能到达哪些点。这是一个经典的可达性问题，于是用 $\texttt{bitset}$ 优化邻接矩阵的 $k$ 次幂可以用 从 $n^3$ 变成 $\frac{n^3}{32}$。

时间复杂度 $O(\frac{n^3\log T}{32})$，可以过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=501,MOD=998244353;
struct Matrix{
	bitset<MAXN>num[MAXN];
	Matrix()
	{
		memset(num,0,sizeof(num));
	}
	inline bitset<MAXN> &operator [](const ll &x)
	{
		return num[x];
	}
	inline const bitset<MAXN> &operator [](const ll &x)const
	{
		return num[x];
	}
};
Matrix mat;
ll cnt,x,ccnt,y;
li res,cur;
ll prob[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline Matrix operator *(Matrix x,Matrix y)
{
	Matrix res;
	for(register int k=0;k<cnt;k++)
	{
		for(register int i=0;i<cnt;i++)
		{
			if(x[i][k])
			{
				res[i]|=y[k];
			}
		}
	}
	return res;
}
inline Matrix qpow(Matrix base,ll exponent)
{
	Matrix res;
	for(register int i=0;i<cnt;i++)
	{
		res[i][i]=1;
	}
	while(exponent)
	{
		if(exponent&1)
		{
			res=res*base;
		}
		base=base*base,exponent>>=1;
	}
	return res;
}
int main()
{
	cnt=read(),x=read();
	for(register int i=0;i<cnt;i++)
	{
		prob[i]=998244354-read(),ccnt=read();
		for(register int j=0;j<ccnt;j++)
		{
			mat[i][read()-1]=1;
		}
	}
	mat=qpow(mat,x);
	for(register int i=0;i<cnt;i++)
	{
		cur=1;
		for(register int j=0;j<cnt;j++)
		{
			cur=mat[i][j]?cur*prob[j]%MOD:cur;
		}
		res+=998244354-cur;
	}
	printf("%lld\n",res%MOD);
}
```

---

## 作者：BFqwq (赞：2)

# P6016
调题调的超级难受，一直被取余之类的弄出好多毛病qaq

最后暴怒了，暴怒的结果就是：
```cpp
#define int __int128
```
## 最开始的想法
直接前一天每个人去的期望来推后一天每个人**不**去的期望。

令 $f_{i,j}$ 表示第 $i$ 个人第 $j$ 天去的概率，$b_i$ 为每个人的朋友数，

令 $a_{i,1},a_{i,2}\dots a_{i,b_i}$ 为每个人的朋友，

则：

$$f_{i,j}=(\prod_{1\le k\le b_i}f_{a_{i,k},j-1})$$

然而这种做法是错误的，因为没有考虑到两个朋友同时报名的情况的影响。

但是如果只有一天，这样是就正确的，因为他们的总答案相同（的确挺玄学的）。

## 正解
直接考虑一个人通过 $T$ 步会走到哪些点，

然后这个点的初始状态只会影响到那几个点。

比如 $T=100$ 那么 $1$ 在第 $0$ 天去不去只会影响到 $1$ 点走 $100$ 步能走到的点。

然后就是我没有想到的地方：bitset优化矩阵快速幂qaq

（由于不擅长STL而战败）

最后再统计答案：（这时相当于一步走到了，也就是无后效性，所以就可以用上面的式子了）

$$f_{i}=(\prod_{1\le k\le b_i}f_{a_{i,k}})$$

## code
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
const int maxn=520;
const int p=998244353;
int n,cnt,T,gl[maxn],ans;
struct mt{
	bitset<maxn> a[maxn];
	friend mt operator *(mt b,mt c){
		mt res;
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=n;j++)
            	if(b.a[j][i])
                	res.a[j]|=c.a[i];
        return res;
    }
}m; 
mt fp(mt a,int b){
	b--;mt r=a;
    while(b!=0){
    	if(b&1) r=r*a;
    	a=a*a;
    	b>>=1;
    }
    return r;
}
signed main(){
	n=read();T=read();
	for(int i=1;i<=n;i++){
		gl[i]=read();int q=read();
		for(int j=1;j<=q;j++){
			int l=read();m.a[l][i]=1;
		}
	}
	if(T==0){
        for (int i=1;i<=n;++i)ans=ans+gl[i];
        write(ans%p);
        return 0;
    }
	m=fp(m,T);
	for (int i=1;i<=n;i++) {
        int res=1;
        for (int j=1;j<=n;j++){
            if (m.a[j][i]) res*=1-gl[j];
            res=(res%p+p)%p; 
        }
        ans+=1-res;
    }
	write((ans%p+p)%p);
	return 0;
}
```


---

## 作者：sry_ (赞：1)

简单来说问题就是在有向图中问从 $u$ 开始走 $T$ 步的点集。

发现 $T\leq 10^9$ ，矩阵快速幂即可。

但是你不需要 $bitset$ 只要用一下底层优化就能够通过最后 $1$ 个测试包的大多数点。

然后再用 $36$ 行优化即可，时间复杂度 $O(n^3\log T)$ $=O($能过$)$


```cpp
#pragma GCC optimize("O3")
#pragma GCC optimize("O2")

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define LL long long
#define mod 998244353
using namespace std;
inline int read(){
	int f=1,ans=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return ans*f;
}
const int MAXN=501;
int p[MAXN],N,T;
LL Ans;
struct Matrix{
	bool A[MAXN][MAXN];
	void clear(){memset(A,0,sizeof(A));return;}
}F,G;
inline Matrix operator*(Matrix x1,Matrix x2){
	Matrix x3;x3.clear();
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			bool r=x1.A[i][k];if(!r) continue;
			for(int j=1;j<=N;j++) x3.A[i][j]|=x2.A[k][j];
		}
	}
	return x3;
}
inline Matrix ksm(Matrix a,int b){
	Matrix ans;ans.clear();
	for(int i=1;i<=N;i++) ans.A[i][i]=1;
	while(b){
		if(b&1) ans=ans*a;
		a=a*a,b>>=1;
	}return ans;
}
int main(){
	N=read(),T=read();
	for(int i=1;i<=N;i++){
		p[i]=read();
		int c=read();for(int j=1;j<=c;j++) F.A[i][read()]=1;
	}
	G=ksm(F,T);
	for(int s=1;s<=N;s++){
		LL Mul=1ll;
		for(int i=1;i<=N;i++) if(G.A[s][i]) Mul*=(LL)(1ll+mod-p[i]),Mul%=mod;
		Ans+=1ll+mod-Mul;Ans%=mod;
	}printf("%lld\n",Ans);return 0;
}
```


---

## 作者：再不见 (赞：0)

### subtask1,2
略
### subtask3
#### 方法一
容易发现只要确定了第0天每个人去不去，就可以通过dp得到第$T$天每个人去不去。

dp状态：$f[i]$表示某一天第$i$个人去（1）or 不去（0），$g[i]$表示前一天第$i$个人去（1）or 不去（0）

转移方程：$f[i] |= g[j] $ （其中$j$是$i$的朋友）

因此，可以dfs枚举第0天每个人去不去，再进行dp

时间复杂度$O(2^nTn^2)$

期望得分：17（算上subtask1、2）

核心代码：
```cpp
void dfs(int u , int sum) {
	if(u > n) {
		For(i , 1 , n) g[i] = opt[i];
		For(i , 1 , T) {
			For(j , 1 , n) {
				f[j] = 0;
				Next(k , j) f[j] |= g[e[k].to]; 
			}
			For(j , 1 , n) g[j] = f[j]; 
		}
		For(i , 1 , n) cnt += g[i];
		Ans += sum * cnt % P ; Ans %= P;
		return ;
	}
	opt[u] = 0;
	dfs(u + 1 , sum * (((1 - p[u]) % P + P) % P) % P );
	opt[u] = 1;
	dfs(u + 1 , sum * p[u] % P); 
	opt[u] = 0;
}

```

#### 方法二
仔细观察发现上述的dp可以用矩阵乘法优化

时间复杂度$O(2^nlogT)$

期望得分：50（算上subtask1、2）

核心代码：
```cpp
struct Mat {
	int h , l , a[15][15];  
} f , g;

inline Mat operator * (Mat A , Mat B) {
	Mat C ; C.h = A.h , C.l = A.l;
	memset(C.a , 0 , sizeof(C.a));
	For(i , 1 , A.h) 
		For(j , 1 , B.l)
			For(k , 1 , A.l) {
				C.a[i][j] |= (A.a[i][k] & B.a[k][j]);
			}
	return C;
}

inline Mat qpow(Mat x , int y) {
	if(y == 1) return x;
	Mat ans = x  , res = x; -- y; 
	while(y) {
		if(y & 1) ans = ans * res;
		y>>= 1; res = res * res;
	} return ans;
}

void dfs(int u , int sum) {
	if(u > n) {
		f.h = 1 , f.l = n ; 
        For(i , 1 , f.l) f.a[1][i] = opt[i];
		if(T > 0) f = f * qpow(g , T);
		int cnt = 0; 
		For(i , 1 , n) cnt += f.a[1][i];
		Ans += sum * cnt % P ; Ans %= P;
		return ;
	}
	opt[u] = 0;
	dfs(u + 1 , sum * (((1 - p[u]) % P + P) % P) % P );
	opt[u] = 1;
	dfs(u + 1 , sum * p[u] % P); 
	opt[u] = 0;
}

```
### subtask4、5

结合上述方法，能够发现，其实不需要枚举第0天的初始状态。不管第0天状态如何转移的矩阵都是一样的。我们可以先算给邻接矩阵的$T$次方,再和初始状态的$pi$相乘，得到结果。

时间复杂度$O(n^3logT)$

期望得分：85

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
#define For(i , x , y) for(ri i = x ; i <= y ; ++ i)
#define Next(i , x) for(ri i = head[x] ; i ; i = e[i].nxt)
inline int read() {
	int s = 0 , w = 1; char ch = getchar();
	while(ch < 48 || ch > 57) {if(ch == '-') w = -1; ch = getchar();}
	while(ch >= 48 && ch <= 57) s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar();
	return s * w;
}
const int N = 1e6 + 5 , P = 998244353;

int n , T , p[N] , tot , head[N] , Ans;
struct Edge{int to , nxt;} e[N << 1];
inline void addedge(int x , int y) {e[++ tot] = (Edge){y , head[x]} , head[x] = tot;}

int opt[N] ;

struct Mat {
	int h , l , a[505][505];  
} f , g; // g是邻接矩阵

inline Mat operator * (Mat A , Mat B) {
	Mat C ; C.h = A.h , C.l = A.l;
	memset(C.a , 0 , sizeof(C.a));
	For(i , 1 , A.h) 
		For(j , 1 , B.l)
			For(k , 1 , A.l) {
				C.a[i][j] |= (A.a[i][k] & B.a[k][j]);
			}
	return C;
}

inline Mat qpow(Mat x , int y) {
	if(y == 1) return x;
	Mat ans = x  , res = x; -- y; 
	while(y) {
		if(y & 1) ans = ans * res;
		y>>= 1; res = res * res;
	} return ans;
}

signed main() {
	g.h = g.l = n = read() , T = read();
	For(i , 1 , n) {
		p[i] = read();
		int x = read();
		For(j , 1 , x) {
			int y = read() ; g.a[y][i] = 1;
		}
	}
	For(i , 1 , n) p[i] = ((1 - p[i]) % P + P) % P;
	if(T > 0) g = qpow(g , T);
	For(i , 1 , n) {
		int tot = 1;
		For(j , 1 , n) 
			if(g.a[j][i]) tot = tot * p[j] % P;
		Ans += ( (1 - tot) % P + P ) % P; Ans %= P;
	}
	cout << Ans << endl;
	return 0;
}

```
### 正解

发现邻接矩阵的值$\in [0,1]$ , 可以用bitset优化

时间复杂度$O(\frac{n^3logT}{w})$

期望得分 100

核心代码：
```cpp
struct Mat {
	int h , l;
	bitset <505> a[505] ;  
} f , g;
bitset <505> tmp[505];
inline Mat operator * (Mat A , Mat B) {
	Mat C ; C.h = A.h , C.l = A.l;
	For(i , 1 , C.h) C.a[i].reset() , tmp[i].reset();
	
	For(i , 1 , B.h)
		For(j , 1 , B.l) 
			tmp[j][i] = B.a[i][j];
			 
	For(i , 1 , A.h) 
		For(j , 1 , B.l) {
			C.a[i][j] = (A.a[i] & tmp[j]).any();
		}
	return C;
}
```

---

## 作者：LCuter (赞：0)

根据期望的线性性，我们可以通过计算出每个学生去不去的概率，然后相加就是答案。

对于一个朋友关系 $(u,v)$ 连一条 $v\rightarrow u$ 的边。考虑第 $T$ 天会对点 $x$ 产生影响的节点 $y$ 必须满足存在一条从 $y$ 到 $x$ 的路径，且路径经过 $T$ 条边。

对于定长路径问题，我们在邻接矩阵上做矩阵快速幂，这个比较经典，按下不表。

上面的复杂度是 $O(n^3\log T)$ 的，还是过不了最后一个 Subtask，考虑优化。

对于本题而言，我们实际上只需考虑存在性，而非数量，那么用 bitset 优化即可，实际操作时，原来是乘积求和，现在我们将左边的矩阵的对应行与右边矩阵的对应列求与，然后判断其中是否有 $1$。复杂度 $O(\frac{n^3\log n}{w})$。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define REG register
#define MAXN 505
#define MOD 998244353
using namespace std;
inline int read(){
    REG int x(0);
    REG char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x*10)+(c^48),c=getchar();
    return x;
}

inline int Add(int a,int b){int sum=a+b;return sum>=MOD?sum-MOD:sum;}
inline int Del(int a,int b){int del=a-b;return del<0?del+MOD:del;}

int n,t;

int P[505];

struct Martix{
	bitset<505> H[505];
    bitset<505> L[505];
    inline void Init(){
        for(REG int i=1;i<=n;++i)
            H[i].reset(),L[i].reset();
    }
    inline void toI(){
        for(REG int i=1;i<=n;++i)
            H[i].set(i),L[i].set(i);
    }
    Martix operator*(Martix x){
        Martix res;
        res.Init();
        for(REG int i=1;i<=n;++i)
            for(REG int j=1;j<=n;++j)
                res.H[i].set(j,(H[i]&x.L[j]).count()>0),
                res.L[j].set(i,(H[i]&x.L[j]).count()>0);
        return res;
    }
}G;
Martix Pow(Martix a,int p){
	Martix res;
	res.Init();
	res.toI();
	while(p){
		if(p&1) res=res*a;
		a=a*a;
		p>>=1;
	}
	return res;
}

void Work(){
    G.Init();
    n=read(),t=read();
    for(REG int i=1;i<=n;++i){
        P[i]=read();
        int tmp=read();
        for(REG int j=1;j<=tmp;++j){int v=read();G.H[v].set(i,1),G.L[i].set(v,1);}
    }
    Martix res=Pow(G,t);
    int ans=0;
    for(REG int i=1;i<=n;++i){
        LL tmp=1;
        for(REG int j=1;j<=n;++j)
            if(res.H[j][i])
                tmp=(tmp*Del(1,P[j]))%MOD;
        ans=Add(ans,Del(1,tmp));
    }

    printf("%d\n",ans);
}

signed main(){Work();}

```

---

