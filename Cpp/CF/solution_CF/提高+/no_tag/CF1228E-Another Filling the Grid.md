# Another Filling the Grid

## 题目描述

给定一个 $n \times n$ 的正方形网格和一个整数 $k$。请在每个格子中填入一个整数，要求满足以下条件：

- 网格中所有数字都在 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）。
- 第 $i$ 行的最小值为 $1$（$1 \le i \le n$）。
- 第 $j$ 列的最小值为 $1$（$1 \le j \le n$）。

请计算有多少种填数方案。由于答案可能非常大，请输出答案对 $10^9+7$ 取模后的结果。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228E/461043b230da4734e02a378fa88336fd5a76ad41.png) 上图为 $n=k=2$ 时，合法和不合法的网格示例。

## 说明/提示

在第一个样例中，共有 $7$ 种合法方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228E/50e0a56b2ebcb373865c65f252219c6e6fb65791.png) 在第二个样例中，请确保输出的答案对 $10^9+7$ 取模。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
123 456789
```

### 输出

```
689974806
```

# 题解

## 作者：Yukikaze_ (赞：48)

这里提供一个便于理解的容斥写法：

首先，一行的所有数合法的情况数为 $k^n-(k-1)^n$ （即所有情况减去最小值大于 $1$ 的情况）。

然后，我们枚举至少 $i$ 列不合法（严格上来说是容斥的辅助数组），相当于每行中钦定了 $i$ 个数最小值大于 $1$ ，则每行的合法方案数为 $k^{n-i}(k-1)^i-(k-1)^n$ ，乘上组合数并把每一行乘起来得到 $\tbinom{n}{i}(k^{n-i}(k-1)^i-(k-1)^n)^n$ 。

最后容斥，答案为 $\displaystyle\sum_{i=0}^n(-1)^i\tbinom{n}{i}(k^{n-i}(k-1)^i-(k-1)^n)^n$ ，时间复杂度 $O(n\log n)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,mod=1e9+7;
ll n,k,jc[N],jv[N],mi1[N],mi2[N],ans;
ll ksm(ll di,ll mi) {ll res=1; for(di%=mod;mi;mi>>=1,di=di*di%mod) if(mi&1) res=res*di%mod; return res;}
ll c(ll a,ll b) {return jc[a]*jv[b]%mod*jv[a-b]%mod;}
int main()
{
	int i,j;
	for(cin>>n>>k,jc[0]=mi1[0]=mi2[0]=i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod,mi1[i]=mi1[i-1]*k%mod,mi2[i]=mi2[i-1]*(k-1)%mod;
	for(jv[n]=ksm(jc[n],mod-2),i=n-1;~i;i--) jv[i]=jv[i+1]*(i+1)%mod;
	for(i=0;i<=n;i++) ans=(ans+(i&1? mod-1:1)*(c(n,i)*ksm(mi1[n-i]*mi2[i]+mod-mi2[n],n)%mod))%mod;
	cout<<ans;
	return 0;
}
```


---

## 作者：Pelom (赞：10)

[更好的阅读体验](https://pelom.top/archives/75/)

# 题意

一个$n \times n$的矩形，每个格子里可以填$[1,k]$内的整数，求保证每行每列的最小值为$1$的方案数

**数据范围：**$1 \le n \le 250,1 \le k \le 10^9$

# 题解

直接计算难以解决，考虑容斥原理

枚举有$i$行$j$列的最小值$> 1$，选择方案有
$$\sum_{i=0}^n \sum_{j=0}^n (-1)^{i+j} C_n^i C_n^j$$

乘上每个格子的选择

- $$(k-1)^{ni+nj-ij}$$
	这$i$行$j$列必须$> 1$

- $$k^{n^2-ni-nj+ij}$$
	其余格子可以任意选

最终为
$$\sum_{i=0}^n \sum_{j=0}^n (-1)^{i+j} C_n^i C_n^j (k-1)^{ni+nj-ij} k^{n^2-ni-nj+ij}$$

复杂度$O(n^2 \log{n})$

**代码：**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int mod=1e9+7;
const int N=250+10;
int n,k;
int fac[N],invf[N];
int ans;
inline int Pow(int a,int b){
    int res=1;
    for(;b;b>>=1){
        if(b&1)
            res=1ll*res*a%mod;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int inv(int x){
    return Pow(x,mod-2);
}
inline int C(int n,int m){
    return 1ll*fac[n]*invf[m]%mod*invf[n-m]%mod;
}
int main(){
    scanf("%d%d",&n,&k);
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%mod;
    invf[n]=inv(fac[n]);
    for(int i=n-1;~i;i--)
        invf[i]=1ll*invf[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++){
            int p=n*i+n*j-i*j;
            ans=(1ll*ans+1ll*Pow(-1,i+j)*C(n,i)%mod*C(n,j)%mod*Pow(k-1,p)%mod*Pow(k,n*n-p)%mod)%mod;
        }
    ((ans%=mod)+=mod)%=mod;
    printf("%d",ans);
    return 0;
}
```

**优化：**

对
$$(k-1)^{ni+nj-ij} k^{n^2-ni-nj+ij}$$
变形得

$$
\begin{aligned}
&(k-1)^{(n-j)i} (k-1)^{nj} k^{(n-i)(n-j)} \\
=&[(k-1)^i k^{n-i}]^{n-j}[(k-1)^n]^j
\end{aligned}
$$

与前面的$(-1)^j C_n^j$一同，可以应用**二项式定理**，得
$$[(k-1)^i k^{n-i}-(k-1)^n]^n$$

最终为
$$\sum_{i=0}^n (-1)^i C_n^i [(k-1)^i k^{n-i}-(k-1)^n]^n$$

复杂度$O(n \log{n})$

**代码：**

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long LL;
const int mod=1e9+7;
const int N=250+10;
int n,k;
int fac[N],invf[N];
int ans;
inline int Pow(int a,int b){
    int res=1;
    for(;b;b>>=1){
        if(b&1)
            res=1ll*res*a%mod;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int inv(int x){
    return Pow(x,mod-2);
}
inline int C(int n,int m){
    return 1ll*fac[n]*invf[m]%mod*invf[n-m]%mod;
}
int main(){
    scanf("%d%d",&n,&k);
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%mod;
    invf[n]=inv(fac[n]);
    for(int i=n-1;~i;i--)
        invf[i]=1ll*invf[i+1]*(i+1)%mod;
    for(int i=0;i<=n;i++)
        ans=(1ll*ans+1ll*Pow(-1,i)*C(n,i)%mod*Pow(((1ll*Pow(k-1,i)*Pow(k,n-i)%mod-Pow(k-1,n))%mod+mod)%mod,n)%mod)%mod;
    ((ans%=mod)+=mod)%=mod;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：AThousandSuns (赞：10)

简单二项式反演。

先特判 $k=1$。下文假设 $k\ge 2$。

设 $f_{i,j}$ 是恰好 $i$ 行不满足要求，恰好 $j$ 列不满足要求的方案数。要求是 $f_{0,0}$。

设 $g_{i,j}$ 是对于所有方案中，选出 $i$ 行不满足要求，$j$ 列不满足要求的方案数之和。很明显有 $g_{i,j}=\binom{n}{i}\binom{n}{j}(k-1)^{n^2-(n-i)(n-j)}k^{(n-i)(n-j)}$。

根据定义，$g_{i,j}=\sum\limits_{x=i}^n\sum\limits_{y=j}^n\binom{x}{i}\binom{y}{j}f_{x,y}$。

二项式反演，$f_{i,j}=\sum\limits_{x=i}^n\sum\limits_{y=j}^n\binom{x}{i}\binom{y}{j}(-1)^{(x-i)+(y-j)}g_{x,y}$。

时间复杂度 $O(n^2\log k)$。可能可以进一步优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=100010,mod=1000000007;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,k,ans,fac[maxn],invfac[maxn];
int qpow(int a,ll b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
	return ans;
}
int C(int n,int m){
	return 1ll*fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
int main(){
	n=read();k=read();
	if(k==1) return puts("1"),0;
	fac[0]=1;
	FOR(i,1,n) fac[i]=1ll*fac[i-1]*i%mod;
	invfac[n]=qpow(fac[n],mod-2);
	ROF(i,n-1,0) invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
	FOR(i,0,n) FOR(j,0,n){
		int sum=1ll*C(n,i)*C(n,j)%mod*qpow(k-1,1ll*n*n-1ll*(n-i)*(n-j))%mod*qpow(k,1ll*(n-i)*(n-j))%mod;
//		printf("i=%d,j=%d,sum=%d\n",i,j,sum);
		if((i+j)%2==0) ans=(ans+sum)%mod;
		else ans=(ans-sum+mod)%mod;
	}
	printf("%d\n",ans);
}
```


---

## 作者：wsyhb (赞：7)

## 二元二项式反演

本题解使用了**二元二项式反演**，故先进行讲解。

### 结论

$$\begin{aligned}
f(x,y)&=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)\\
\Leftrightarrow g(x,y)&=\sum_{i=x}^{n}\sum_{j=y}^{m}(-1)^{i+j-x-y}\binom{i}{x}\binom{j}{y}f(i,j)
\end{aligned}$$

其中 $n,m$ 是定值。

P.S. 通过**容斥原理**，其实可以较为感性地理解这个结论。

### 证明

先写出**初始恒等式**：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)[i=x \land j=y]$$

（根据反演套路，初始恒等式与前一个式子极其相似）

再写出**交错和公式**：

$$\sum_{i=0}^{n}(-1)^i\binom{n}{i}=[n=0]$$

（证明可使用**二项式定理**，或统计大小为 $n$ 的集合的奇子集和偶子集的个数）

由 $[i=x \land j=y]=[i-x=0][j-y=0]$ 得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)(\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{i-x}{a}\binom{j-y}{b})$$

整理一下式子：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{i}{x}\binom{i-x}{a}\binom{j}{y}\binom{j-y}{b}g(i,j)$$

考虑对组合数进行阶乘展开并重组成其它组合数：

$$\begin{aligned}
\binom{i}{x}\binom{i-x}{a}&=\frac{i!}{x!(i-x)!}\cdot\frac{(i-x)!}{a!(i-x-a)!}\\
&=\frac{1}{x!a!}\cdot\frac{i!}{(i-x-a)!}\\
&=\frac{(x+a)!}{x!a!}\cdot\frac{i!}{(x+a)!(i-x-a)!}\\
&=\binom{x+a}{x}\binom{i}{x+a}
\end{aligned}$$

（同理有 $\binom{j}{y}\binom{j-y}{b}=\binom{y+b}{y}\binom{j}{y+b}$）

代入前述式子得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{x+a}{x}\binom{i}{x+a}\binom{y+b}{y}\binom{j}{y+b}g(i,j)$$

令 $a \leftarrow x+a$，$b \leftarrow y+b$ 得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=x}^{i}\sum_{b=y}^{j}(-1)^{a+b-x-y}\binom{a}{x}\binom{i}{a}\binom{b}{y}\binom{j}{b}g(i,j)$$

交换求和符号：

$$g(x,y)=\sum_{a=x}^{n}\sum_{b=y}^{m}(-1)^{a+b-x-y}\binom{a}{x}\binom{b}{y}(\sum_{i=a}^{n}\sum_{j=b}^{m}\binom{i}{a}\binom{j}{b}g(i,j))$$

代入结论中的前一个式子得：

$$g(x,y)=\sum_{a=x}^{n}\sum_{b=y}^{m}(-1)^{a+b-x-y}\binom{a}{x}\binom{b}{y}f(a,b)$$

即结论中的后一个式子。

除最后一步外，所有的步骤都是恒等变形，所以**结论中的两个式子等价，且没有任何限制条件**。

## 题解

回到本题，设 $f(x,y)$ 为**至少**有 $x$ 行 $y$ 列的最小值 $>1$ 的方案数，$g(x,y)$ 为**恰好**有 $x$ 行 $y$ 列的最小值 $>1$ 的方案数。

注意：我们定义此处的 $f(x,y)$ 的计算方法为，从所有行列中选出 $x$ 行 $y$ 列，并指定这 $x$ 行 $y$ 列满足条件，而其余行列任意，因此 **$f$ 是包含重复情况的**。（这是为了使用二项式反演）

由 $f$ 和 $g$ 的定义知：

$$f(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{n}\binom{i}{x}\binom{j}{y}g(i,j)$$

由二元二项式反演知：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{n}(-1)^{i+j-x-y}\binom{i}{x}\binom{j}{y}f(i,j)$$

题目的答案即为：

$$g(0,0)=\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}f(i,j)$$

根据 $f$ 的定义，其计算方法如下：

$$f(x,y)=\binom{n}{x}\binom{n}{y}k^{(n-x)(n-y)}(k-1)^{n^2-(n-x)(n-y)}$$

预处理组合数 $\binom{n}{i}$，以 $k$ 和 $k-1$ 为底数的幂，即可在 $O(n^2)$ 的时间复杂度内解决本题。

## 代码

题解中的代码是通过如下递推式算得组合数 $\binom{n}{i}$ 的：

$$\binom{n}{i}=\frac{n-i+1}{i}\binom{n}{i-1}$$

（将组合数阶乘展开即证）

当然也可以预处理阶乘及阶乘逆元，直接使用阶乘展开式进行计算。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=250+5;
int inv[max_n];
const int mod=1e9+7;
int C[max_n],f[max_n][max_n],g[max_n][max_n];
const int max_n2=250*250+5;
int fac_k_minus_1[max_n2],fac_k[max_n2];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	C[0]=1;
	for(int i=1;i<=n;++i)
		C[i]=1ll*C[i-1]*inv[i]%mod*(n-(i-1))%mod;
	fac_k_minus_1[0]=fac_k[0]=1;
	int n2=n*n;
	for(int i=1;i<=n2;++i)
	{
		fac_k_minus_1[i]=(k-1ll)*fac_k_minus_1[i-1]%mod;
		fac_k[i]=1ll*k*fac_k[i-1]%mod;
	}
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
			f[i][j]=1ll*C[i]*C[j]%mod*fac_k_minus_1[n2-(n-i)*(n-j)]%mod*fac_k[(n-i)*(n-j)]%mod;
	int ans=0;
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
		{
			if((i^j)&1)
			{
				ans-=f[i][j];
				ans+=ans<0?mod:0;
			}
			else
			{
				ans+=f[i][j];
				ans-=ans>=mod?mod:0;
			}
		}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：ReseeCher (赞：6)

直接容斥

枚举有i行j列不满足条件，那么这些位置就只有K-1种填法(不能填1)，其他位置有K种填法

设 $u=i*n+j*n-i*j$ 表示不满足条件的位置个数，那么答案就是

$\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}C_n^iC_n^j(K-1)^uK^{n*n-u}$

直接算就行了，时间复杂度$O(n^2logn)$

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define F(x,y,z) for(int x=y;x<=z;++x)
#define D(x,y,z) for(int x=y;x>=z;--x)
using namespace std;
const int Mod=1000000007;
const int N=310;
LL Min(LL x,LL y){return x<y?x:y;}
LL Max(LL x,LL y){return x>y?x:y;}
LL R(){
    LL ans=0,f=1;char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') f=-1;
    for(;c>='0'&&c<='9';c=getchar()) ans=ans*10+c-'0';
    return ans*f;
}
LL n,K,ans;
LL C[N][N];
LL Pow(LL x,LL bs){
	LL an=1;
	for(;bs;bs>>=1,x=x*x%Mod)
		if(bs&1)an=an*x%Mod;
	return an;
}
int main(){
	n=R();K=R();
	F(i,0,260)C[i][0]=1;
	F(i,1,260)
		F(j,1,i)C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
	ans=0;
	F(i,0,n)F(j,0,n){
		LL fg=1;
		if((i+j)%2==1)fg=-1;
		LL an=C[n][i]*C[n][j]%Mod;
		LL mj=(i+j)*n-i*j;
		an=an*Pow(K-1,mj)%Mod;
		an=an*Pow(K,n*n-mj)%Mod;
		ans=(ans+an*fg+Mod)%Mod;
	}
	cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Qiiiiiii_ (赞：6)

## 前置知识：FMT

前言：由于本人不太喜欢推容斥式子，就借助了前人的智慧，整了个 $FMT$ 做法。

分析题目给出的限制条件：每行每列的最小值为 $1$ 。由于同时涉及到行列，就不太好用正常的方式来描述该限制条件。那么，我们就将各行分开考虑。

接下来考虑如何处理各行之间的关系，由于同一列可以选若干个 $1$ ，而每一行每一列都得有 $1$，一个比较暴力的想法是：或卷积。

对于 $n$ 很小的时候，首先我们将矩阵按行拆开成 $n$ 个长度为 $n$ 的向量，由于每个值的选择只有 $1$ 或者非 $1$ 两种选择，我们不妨设每行的选择情况为 $T$ (一个二进制数)，其中第 $k$ 位为 $1$ 表示在向量中第 $k$ 个位置填上 $1$ ，为 $0$ 则表示填上其他数。那么，我们可以写出它的集合幂级数（卷积定义为或卷积）：

$$\displaystyle f(x)=\sum_{T\neq \emptyset}(K-1)^{n-pop(T)} x^T$$

其中 $pop(T)$ 表示二进制数 $T$ 中 $1$ 的个数。有了该式之后，我们将其自卷 $n$ 次后的最高项系数就是答案。具体的，将 $f(x)$ 进行 $FMT$ 后再将每一项都取 $n$ 次幂再 $IFMT$ 回来即可。即（设 $U$ 为最高次项）：

$$ ans=[x^{U}] f^n(x) $$

由于该做法的复杂度是 $O(n2^n)$ ，当 $n$ 略大的时候，由于该集合幂级数是指数级别增长的，这个做法似乎就裂开了。

其实不然，当我们深入分析该式子后，发现当 $pop(T)$ 相同的项其系数也相同，那么我们就不必将各个项分开考虑，只需按 $pop(T)$ 分类即可。 重新分好类之后，我们还得考虑在当前情况下如何做 $FMT$ ，根据或卷积的 $FMT$ 的定义（设 $\hat f(x)$ 为 $f(x)$ 莫比乌斯变换之后的结果）：

$$ \displaystyle \hat f(x)=\sum_{T}\sum_{S\subseteq T} [x^{S}]f(x) x^{T} $$

我们同理可以给幂次定义为 $pop(T)$ 的多项式类似地进行 $FMT$ ：

$$ \displaystyle \hat f(x)=\sum _i \sum_{j=1}^i \binom{i}{j}(K-1)^{n-j} x^i$$ 

你也许想对其做卷积，但是模数 $1e9+7$ 要写任意模就会把我们劝退。事实上，后式就是个二项式定理的形式，简单化一下式子就可得到：

$$\displaystyle \hat f(x)=\sum_i (K-1)^n*((\frac{K}{K-1})^i-1) x^i$$ 

将每一项系数取 $n$ 次幂后就得考虑如何做 $IFMT$ 变回来，不过剩下的工作和以上基本相同。还是先给出 $IFMT$ 的定义：

$$ \displaystyle \hat f(x)=\sum_{T}\sum_{S\subseteq T} (-1)^{|T|-S} [x^{S}]f(x) x^{T} $$ 

由于我们只需要求最高次项系数，即 $pop(T)=n$ 的情况，以下也就只给出第 $n$ 位做 $IFMT$ 后的结果：

$$ \displaystyle ans=\sum_{i=1}^n \binom{n}{i} (-1)^{n-i} [x^i]\hat f(x) $$ 

各部分时间复杂度基本都是 $O(n)$ ，仅自乘处复杂度为 $O(n\log n)$ ，所以总时间复杂度 $O(n\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define re register int 
#define ll long long
#define LL inline ll
#define V inline void
#define I inline int
#define FOR(i,a,b) for(re i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(re i=(a),i##i=(b);i>=i##i;--i)
//#define gc getchar()
#define gc (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<18,stdin),ft==fs))?0:*fs++
using namespace std;
char *fs,*ft,buf[1<<18];
const int N=2e5+10,mo=1e9+7;
ll inf=1e14;
LL read(){
	ll p=0,w=0; char ch=gc;
	while(!isdigit(ch)) w=ch=='-',ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
int n,K;
LL Pow(ll x,ll y){ ll as=1; for(;y;y>>=1,x=x*x%mo) if(y&1) as=as*x%mo; return as;}
V ipt(){ n=read(),K=read();} 
ll f[N],g[N],h[N],fc[N],fv[N],pw[N],ans;
LL get(ll x,ll y){ return x>=y?fc[x]*fv[y]%mo*fv[x-y]%mo:0;}
V init(){
	fc[0]=1,pw[0]=1;
	FOR(i,1,n) fc[i]=fc[i-1]*i%mo;
	fv[n]=Pow(fc[n],mo-2);
	ROF(i,n,1) fv[i-1]=fv[i]*i%mo;
	return ; 
} 
V sol(){
	ll inv=Pow(K-1,mo-2)*K%mo,us=Pow(K-1,n);
	pw[0]=1;
	FOR(i,1,n) pw[i]=pw[i-1]*inv%mo;
	FOR(i,1,n) f[i]=us*(pw[i]-1+mo)%mo;
	FOR(i,1,n) f[i]=Pow(f[i],n);
	FOR(i,1,n) ans=(ans+((n-i)&1?mo-1:1)*get(n,i)%mo*f[i])%mo;
	cout<<ans;
	return ;
}
int main(){
	ipt();
	init();
	if(K!=1) sol();
	else cout<<1;
	return 0;
}

---

## 作者：Tony102 (赞：5)

[Link](http://codeforces.com/problemset/problem/1228/E)

[My Blog](https://tony102.com/archives/140/)

## Sol

容斥练习题。其实跟 [【JSOI2015】染色问题](https://www.luogu.com.cn/problem/P6076) 差不多，异曲同工之妙。可以先看看那道题。

枚举有多少行没有填 $1$，假设有 $i$ 行，那么这 $i$ 行填数字的方案数是 $(k-1)^i$，剩余 $n-i$ 行的填数字的方案数是 $k^{n-i}$。此外，还应减去全部都没填 $1$ 的方案数：$(k-1)^n$。

这一类题目有一个共同的性质，也是可以像上述那样计算的基础：行和列之间独立。我们刚才那样是填一行的，$n$ 行全填只需要 $n$ 次幂即可。

所以：

$$Ans = \sum\limits_{i=0}^{n} (-1)^i \binom{n}{i} ((k-1)^i \cdot k^{n-i} - (k-1)^n)^n$$

可以在 $O(n \log n)$ 内的时间计算完。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2.5e2, SIZE = N + 5;
const int mod = 1e9 + 7;

int n, k;
int fac[SIZE], inv[SIZE], pw[SIZE], pw1[SIZE];

namespace GTR {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (c < 48 || c > 57) b ^= c == '-', c = fetch();
		while (c >= 48 && c <= 57) a = (a << 1) + (a << 3) + c - 48, c = fetch();
		return b ? a : -a;
	}
} using GTR::read;

int qPow(int a, int b) {
    int ans = 1ll;
    for ( ; b; b >>= 1, a = a * a % mod) {
        if (b & 1) ans = ans * a % mod;
    }
    return ans % mod;
}

void init() {
    fac[0] = pw[0] = pw1[0] = 1ll;
    for (int i = 1; i <= N; ++ i)
        fac[i] = fac[i - 1] * i % mod,
        pw[i] = pw[i - 1] * k % mod, pw1[i] = pw1[i - 1] * (k - 1) % mod;
    inv[N] = qPow(fac[N], mod - 2ll);
    for (int i = N - 1; ~i; -- i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int C(int x, int y) {
    if (x < y) return 0ll;
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

signed main() {
    n = read(), k = read(); init();
    int ans = 0;
    for (int i = 0; i <= n; ++ i) {
        int p = qPow(((pw1[i] * pw[n - i] % mod) - pw1[n] + mod) % mod, n) % mod;
        if (i & 1) ans = (ans - (C(n, i) * p % mod) + mod) % mod;
        else ans = (ans + (C(n, i) * p % mod)) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：raincity (赞：5)

## 分析

这道题我竟然没看出来是容斥。。。/wtcl, 多校联考的容斥也没做出来，要补一补了。

进入正题。

这道题直接做显然不好。我们如果直接分类讨论，需要讨论哪些位置是1，直接爆炸。

所以容斥。

我们可以计算出**至少**有 $i$ 个行， $j$ 个列不满足条件的方法数。设为 $cnt_{i,j}$。

则 $ans = \sum_{i=0}^n\sum_{j=1}^ncnt_{i,j} \times (2 \times [2|i+j] - 1)$

（注：$[condition]$ 表示当 $condition$ 成立时为1，否则为0）。

用~~小学奥数~~容斥原理很容易~~理解~~证明。

所以我们考虑如何求出 $cnt_{i,j}$。

首先，我们需要求出对于每一对 $(i,j)$，有多少格子里填的数必须大于1。

这里又要用到容斥原理（容斥原理里面用容斥原理，/yun）。

对于这 $i$ 行有 $n \times i$ 个格子， 对于这 $j$ 行有 $n \times j$ 个格子。既属于这 $i$ 行又属于这 $j$ 行的格子有 $i \times j$ 个。

所以一共有 $n \times i + n \times j - i \times j$ 个格子，只能填大于1的数，也就是有 $k-1$ 种数可以填。

剩下的格子里有 $k$ 中填法。不用担心有别的行或者列中的最小值大于1，应为前面说了**至少**。

我们还需要乘上一个组合数：$\binom{n}{i} \times \binom{n}{j}$，用来选出这 $i$ 行和这 $j$ 列。不用担心重复，因为本来就是在容斥。中间每一步计算的结果可能都不对，但是最终的结果一定正确。

预处理出 $(k-1)^x, k^x, \binom{x}{y}$，就可以 $O(n^2)$ 解决。

貌似和现有题解重了？我是自己想的啊啊啊。
（不过我的复杂度更优一点点，因为我会预处理。。。）

## 解决

$\texttt{\color{blue}{code:}}$

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 255, Mod = 1e9 + 7;
int n, k, ans, power_k[N * N], power_kd1[N * N], C[N][N];

int main() {
    scanf("%d%d", &n, &k);
    power_k[0] = power_kd1[0] = 1;
    for (register int i = 1; i <= n * n; i++) {
        power_k[i] = (long long)power_k[i - 1] * k % Mod;
        power_kd1[i] = (long long)power_kd1[i - 1] * (k - 1) % Mod;
    }
    C[0][0] = 1;
    for (register int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (register int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
    }
    for (register int i = 0; i <= n; i++)
        for (register int j = 0; j <= n; j++) {
            int kd1 = i * n + j * (n - i);
            int res = (long long)power_kd1[kd1] * power_k[n * n - kd1] % Mod
             * C[n][i] % Mod * C[n][j] % Mod;
            if ((i + j) & 1)
                ans = (ans - res) % Mod;
            else
                ans = (ans + res) % Mod;
        }
    cout << (ans % Mod + Mod) % Mod << endl;
    return 0;
}
```

---

## 作者：Erusel (赞：4)

显然，我们可以用$f[i][j]$表示前$i$行,前$j$列最小值为1的方案数

我们可以得到$f[i][j]=\sum_{k=0}^{j}C_{n-k}^{j-k}(m-1)^{n-j}m^kf[i-1][k]$

这样可以利用预处理达到$O(n^3)$的时间复杂度

我们也可以考虑容斥，对于合法的方案数

定义$t=n(i+j)-ij$（即$i$行$j$列的格子）

$ans=\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}(m-1)^tC_{n}^{i}C_{n}^{j}m^{n^2-t}$

其中$n^2-t$表示没有限制的位置

考虑对这个柿子进行化简

因为$n^2-t=n^2-n(i+j)+ij=(n-i)(n-j)$

所以，我们可以考虑把$(m-1)^t$拆成$(m-1)^{(n-i)j}$和$(m-1)^{ni}$

然后把$(m-1)^{(n-i)j}$与前面组合,中间部分分离出来

可以得到:

$\sum_{i=0}^n(-1)^iC_n^{i}(m-1)^{ni}(m^{n-i}-(m-1)^{n-i})^n$

$=> \sum_{i=0}^n(-1)^iC_n^{i}(m^{n-i}(m-1)^i-(m-1)^n)^n$

只要预处理$(m-1)^k$和$m^k$，就可以做到$O(nlogn)$的时间复杂度

**Code:**

```
#include<bits/stdc++.h>
 
#define rd(x) x=read()
 
#define N 505
 
using namespace std;
 
int n,m;
const int p=1e9+7;
int s[N],t[N];
int C[N][N];
int ans;
 
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
 
inline int fastPow(int a,int b){int ans=1;for(;b;b>>=1,a=1ll*a*a%p)if(b&1)ans=1ll*ans*a%p;return ans;}
 
int main()
{
	rd(n),rd(m);
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
	}s[0]=t[0]=1;
	for(int i=1;i<=n;i++)s[i]=1ll*s[i-1]*m%p,t[i]=1ll*t[i-1]*(m-1)%p;
	for(int i=0;i<=n;i++)
	{
		int res=1ll*C[n][i]*fastPow((1ll*t[i]*s[n-i]%p-t[n]+p)%p,n)%p;
		if(i&1)ans=(ans-res+p)%p;else ans=(ans+res)%p;
	}
	cout<<ans<<endl;
	
	
	
	return 0;
}
```

---

## 作者：whiteqwq (赞：2)

[CF1228E Another Filling the Grid](https://www.luogu.com.cn/problem/CF1228E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1750945)

## 题意
- 给定一个$n\times n$的矩阵，用$[1,k]$中的数填充；
- 要使每行每列最小值都为$1$，问有多少种写法（对$10^9+7$取模）。
- $1\leqslant n\leqslant 250,1\leqslant k\leqslant 10^9$。

## 分析

~~容斥又不会做，就是反演这种东西，才能维持的了生活。~~

首先，因为要使每行每列最小值为$1$，所以每一行都要有$1$。

正难则反，我们不能很快地计算$i$行$j$列每一行列都有$1$，可以尝试设$f_{i,j}$表示矩阵中**恰好**$i$行$j$列全部没有$1$，$g_{i,j}$表示矩阵中有$i$行$j$列全部没有$1$。

$g_{i,j}$很容易计算，设$now=n^2-(n\cdot i)(n\cdot j)$，则有
$$g_{i,j}={n\choose i}{m\choose j}(k-1)^{now}k^{n^2-now}$$

根据$g_{i,j}$的定义，很显然有：
$$g_{i,j}=\sum_{x=i}^n\sum_{y=j}^n{x\choose i}{y\choose j}f_{x,y}$$

对于上面的式子，我们可以使用二项式反演来得到另一个式子：
$$f_{i,j}=\sum_{x=i}^n\sum_{y=i}^n{x\choose i}{y\choose j}(-1)^{(x-i)+(y-j)}g_{x,y}$$

最后，我们的答案就是$f_{0,0}$了。

具体地，我们可以首先$O(n+\log mod)$预处理逆元，然后$O(n^2)$求$g$数组，然后通过$i=0,j=0$带入上式得到$\sum_{x=0}^n\sum_{y=0}^n{x\choose 0}{y\choose 0}(-1)^{(x-0)+(y-0)}g_{x,y}=\sum_{x=0}^n\sum_{y=0}^n(-1)^{x+y}g_{x,y}$，直接$O(n^2)$计算就好了。

复杂度：$O(n^2)$。

## 代码
```
#include<stdio.h>
#define int long long
const int maxn=2005,mod=1000000007;
int n,k,ans;
int fac[maxn],nfac[maxn],g[maxn][maxn],f[maxn][maxn],amul[maxn*maxn],bmul[maxn*maxn];
inline int c(int n,int m){
	return fac[n]*nfac[n-m]%mod*nfac[m]%mod;
}
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
signed main(){
	fac[0]=1;
	for(int i=1;i<maxn;i++)
		fac[i]=fac[i-1]*i%mod;
	nfac[maxn-1]=ksm(fac[maxn-1],mod-2);
	for(int i=maxn-1;i>=1;i--)
		nfac[i-1]=nfac[i]*i%mod;
	scanf("%lld%lld",&n,&k);
	amul[0]=bmul[0]=1;
	for(int i=1;i<=n*n;i++)
		amul[i]=amul[i-1]*(k-1)%mod,bmul[i]=bmul[i-1]*k%mod;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++){
			g[i][j]=c(n,i)*c(n,j)%mod*amul[n*n-(n-i)*(n-j)]%mod*bmul[(n-i)*(n-j)]%mod;
		}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++){
			if((i+j)%2==0)
				ans=(ans+g[i][j])%mod;
			else ans=(ans-g[i][j]+mod)%mod;
		}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```

## 二项式反演证明
二维二项式反演证明（这里式子不太一样，但原理差不多，懒得改了）：
$$f_{n,m}=\sum_{i=0}^n\sum_{j=0}^m{n\choose i}{m\choose j}g_{i,j}\Rightarrow g_{n,m}=\sum_{i=0}^n\sum_{j=0}^m{n\choose i}{m\choose j}(-1)^{(n-i)+(m-j)}f_{i,j}$$

设$F_i=f_{i,m}$，$G_i=\sum_{j=0}^m{m\choose j}g_{i,j}$，那么由上式得：
$$F_n=\sum_{i=0}^n{n\choose i}G_i$$

然后由二项式反演得：
$$G_n=\sum_{i=0}^n{n\choose i}(-1)^{n-i}F_i$$

展开有：
$$\sum_{j=0}^m{m\choose j}g_{n,j}=\sum_{i=0}^n{n\choose i}(-1)^{n-i}f_{i,m}$$

再设$F_i'=\sum_{j=0}^n{n\choose j}(-1)^{n-j}f_{j,i}$，$G_i'=g_{n,i}$，那么代入上式有：

$$F_m'=\sum_{j=0}^m{m\choose j}G_j'$$

然后继续二项式反演：
$$G_m'=\sum_{j=0}^m{m\choose j}(-1)^{m-j}F_j'$$

展开有：
$$g_{n,m}=\sum_{j=0}^m{m\choose j}(-1)^{m-j}\sum_{i=0}^n{n\choose i}(-1)^{n-i}f_{i,j}$$

然后整理一下就有上面的式子了：
$$g_{n,m}=\sum_{i=0}^n\sum_{j=0}^m{n\choose i}{m\choose j}(-1)^{(n-i)+(m-j)}f_{i,j}$$

---

## 作者：x义x (赞：2)

本题解是一个并不是很优秀但是出题人放过去了的$O(n^3)$DP。

定义$F[i][j]$是只填了前$i$行，有且仅有共$j$列上有1。

首先有一个显然的边界：$F[1][c]=C^c_n\cdot(k-1)^{n-c}$。很好理解：从$n$列选出$i$列填1，其他$n-i$列可以填任何非1的数。

$F[r][c]$可以由任意$F[r-1][c0](c0<c)$转移得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/lrrynml7.png)

- $c$比$c0$多了$c-c0$个有1列，这些列要从原来$n-c0$的无1列中选出，因而贡献乘$C_{n-c0}^{c-c0}$；

- 原来有1的$c0$列可以完全随便填，因而贡献乘$k^{c0}$；

- 原来没1现在也没1的$n-c$列可以随便填非1的数，因而贡献乘$(k-1)^{n-c}$；

- 别忘了$F[r-1][c0]$本身。于是总共贡献了：

$$C_{n-c0}^{c-c0}\cdot k^{c0}\cdot (k-1)^{n-c}\cdot F[r-1][c0]$$

$F[r][c]$也可以由$F[r-1][c]$转移得到。

- 注意，原来有1的$c$列中至少有1列，使得它在这一行也填了1，否则这一行就没1了。所以贡献乘$k^c-(k-1)^c$；（所有方案数-没1的方案数=至少有一个1的方案数）

- 剩下$n-c$列可以任意填非1数，所以贡献乘$(k-1)^{n-c}$；

- 别忘了$F[r-1][c]$本身。于是总共贡献了

$$(k^c-(k-1)^c)\cdot (k-1)^{n-c}\cdot F[r-1][c]$$

于是预处理一下组合数和$k,k-1$的幂即可。代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int p=1000000007;

int N,K;
int inv[305];
int powK[305],powK1[305];
int C[305][305];
int F[305][305];//第i行，共j列有1 
int qpow(int a,int k){
	int ans=1;
	while(k){
		if(k&1) ans=1LL*ans*a%p;
		a=1LL*a*a%p;
		k>>=1;
	}
	return ans;
}

int d;

int main(){
	scanf("%d%d",&N,&K);
	powK[0]=powK1[0]=1;
	inv[1]=1;
	for(int i=2;i<=N;i++) inv[i]=1LL*(p-p/i)*inv[p%i]%p;
	for(int i=1;i<=N;i++) powK[i]=1LL*powK[i-1]*K%p,powK1[i]=1LL*powK1[i-1]*(K-1)%p;
	for(int i=1;i<=N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=1LL*C[i][j-1]*(i-j+1)%p*inv[j]%p;
	}
	
	for(int i=1;i<=N;i++)
		F[1][i]=1LL*C[N][i]*powK1[N-i]%p;
	for(int i=2;i<=N;i++)
	for(int j=1;j<=N;j++){
		for(int k=1;k<j;k++)
			F[i][j]=((ll)F[i][j]+1LL*powK[k]*C[N-k][j-k]%p*powK1[N-j]%p*F[i-1][k]%p)%p;
		F[i][j]=((ll)F[i][j]+1LL*(powK[j]-powK1[j]+p)%p*powK1[N-j]%p*F[i-1][j]%p)%p;
	}
	
	printf("%d\n",F[N][N]);
	
	return 0;
}
```


---

## 作者：KaisuoShutong (赞：1)

## CF1228E Another Filling the Grid

提供完整的思路。

### 题意

略。

### 题解

先假设所有条件中行必满足条件。

对于列，设 $f(i)$ 表示恰好 $i$ 个列没有的答案，$g(i)$ 表示至少（钦定）$i$ 个列没有的答案。

易知：$ans = f(0)$。

根据条件，有等式：  
$$\displaystyle g(n)=\sum^N_{i=n} \binom{i}{n} f(i)$$

二项式反演。

$$\displaystyle f(n)=\sum^N_{i=n} (-1)^{i-n}\binom{i}{n}g(i)$$

考虑怎么算 $g$。

$g(n)$ 等价于行合法时，钦定 $n$ 列没有 $1$ 的方案数。  
也就是 $N$ 行，$N-n$ 列的行合法方案再乘上 $(K-1)^{nN}$（列钦定方案）和 $\binom{N}{n}$（选择列方案）。

考虑行合法怎么算。然后你发现：  
行又会算重！

所以换一种算法，用减法原理，全集减去不合法，即为 $K^{N(N-n)} - (K-1)^{N*(N-n)}$。

提一个 $N$ 次方，得：

$$g(n) = (((K^{(N-n)}-(K-1)^{(N-n)})(K-1)^n)^N$$

带入原式即可。

点个赞吧。

```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
using namespace std;
const int maxn = 300, mod = 1e9+7;
int pw[maxn],pw_1[maxn],n,ans,fac[maxn],inf[maxn],K;
int ksm(int x,int y) {int r=1;while(y) y&1?r=1ll*r*x%mod:0,x=1ll*x*x%mod,y>>=1;return r;}
int C(int x,int y) {return x<y?0:1ll*fac[x]*inf[y]%mod*inf[x-y]%mod;}
void ini(int mx) {
	fac[0]=1;for(int i=1;i<=mx;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inf[mx]=ksm(fac[mx],mod-2);for(int i=mx-1;~i;i--) inf[i]=1ll*inf[i+1]*(i+1)%mod;
}
signed main() {
	cin>>n>>K,ini(n);
	pw_1[0]=pw[0]=1;for(int i=1;i<=n;i++) pw_1[i]=pw_1[i-1]*(K-1ll)%mod,pw[i]=1ll*pw[i-1]*K%mod;
	for(int i=0,r=1;i<=n;r=mod-r,i++) ans=(ans+1ll*r/**C(i,0)*/*C(n,i)%mod*ksm(1ll*(pw[n-i]+mod-pw_1[n-i])*pw_1[i]%mod,n))%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Soulist (赞：1)

~~我昨晚一定是降智了~~

回归正题，首先可以注意到没列一定是有一个$1$的，然后$n$还比较小，所以应该是一道$dp$

考虑强制令每一列都有一个$1$那么我们只需要$dp$出行的结果即可

设$dp_{i,j}$表示$dp$到第$i$列，有$j$行空着的方案数

转移的话就考虑填入$1/$其他

显然的是我们可以枚举一个$k$然后转移，这样应该是$O(n^3)$的

$$dp_{i,j}=dp_{i-1,k}*(m-1)^{n-j}(m)^k*\rm C_{n-k}^{j-k}$$

然后这样会错

这是因为对于$j>k$我们通过组合数(实际上是一定需要额外填入$1$)保证了每一列至少有一个$1$

但对于两者相等的情况肯定还是会重复的(必须要填入$1$)

所以对于$j=k$的直接容斥一下就好了，复杂度$O(n^3)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i ) 
#define re register
#define int long long
int gi() {
    int cn = 0 ; char cc = getchar() ;
    while( cc > '9' || cc < '0' ) cc = getchar() ;
    while( cc >= '0' && cc <= '9' ) cn = cn * 10 + cc - '0', cc = getchar() ;
    return cn ; 
}
const int P = 1e9 + 7 ;
const int N = 250 + 5 ; 
int n, m, C[N][N], dp[N][N], inv[N], fac[N] ;
signed main(){
    n = gi(), m = gi() ; C[0][0] = 1, fac[0] = inv[0] = 1 ;
    rep( i, 1, n ) {
          C[i][0] = 1, inv[i] = ( inv[i - 1] * m ) % P, fac[i] = ( fac[i - 1] * ( m - 1 ) ) % P ; 
          rep( j, 1, n ) C[i][j] = ( C[i - 1][j] + C[i - 1][j - 1] ) % P;
    }
    dp[0][0] = 1 ;
    rep( i, 1, n ) {
        rep( j, 1, n ) {
            dp[i][j] = dp[i - 1][j] * fac[n - j] % P * ( inv[j] - fac[j] + P ) % P ; 
            rep( k, 0, j - 1 ) {
                dp[i][j] = ( dp[i][j] + dp[i - 1][k] * ( C[n - k][j - k] ) % P * 
                inv[k] % P * fac[n - j] % P ) % P ;
            }
        }
    }
    printf("%I64d\n", dp[n][n] % P ) ;
    return 0 ;
}
```

---

## 作者：SoyTony (赞：0)

简单容斥，设条件 $P_i$ 为某一行或列的最小值为 $1$（定义 $i\in [1,n]$ 表示行，$i\in [n+1,2n]$ 表示列），满足条件 $P_i$ 的集合 $A_i$，$S=[1,2n]\cap \mathbb{Z}$，欲求：
$$\left|\bigcap_{i\in S} A_i\right|$$

根据容斥原理的两个式子：
$$\left|\bigcap_{i\in S} A_i\right|=|U|-\left|\bigcup_{i\in S}\overline{A_i}\right|$$
$$\left|\bigcup_{i\in S}\overline{A_i}\right|=\sum_{T\subseteq S,T\neq\varnothing}(-1)^{|T|-1} \left|\bigcap_{j\in T} \overline{A_j}\right|$$

于是我们只需要考虑当 $x+y=|T|$ 时，即分别**保证** $x$ 行 $y$ 列的最小值不为 $1$ 的方案数。

先考虑这 $x$ 行 $y$ 列分别是什么，在此基础上在这 $x$ 行 $y$ 列涉及到的 $n^2-(n-x)(n-y)$ 个位置可以填大于 $1$ 的共 $k-1$ 个数，剩余位置填任意数。

也就是：

$$f(x,y)=\dbinom{n}{x}\dbinom{n}{y}(k-1)^{n^2-(n-x)(n-y)}k^{(n-x)(n-y)}$$


再代入容斥即可。

```cpp
inline int q_pow(int x,int p){
    int res=1;
    while(p){
        if(p&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        p>>=1;
    }
    return res;
}

int n,k;
int C[255][255];
int f[255][255];
int ans;
int main(){
    n=read(),k=read();
    C[0][0]=1;
    for(int i=1;i<=n;++i){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j){
            f[i][j]=1ll*q_pow(k-1,n*(i+j)-(i*j))*q_pow(k,(n-i)*(n-j))%mod*C[n][i]%mod*C[n][j]%mod;
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j){
            if(!i&&!j) continue;
            if((i+j)&1) ans=(ans+f[i][j])%mod;
            else ans=(ans-f[i][j]+mod)%mod;
        }
    }
    ans=(f[0][0]-ans+mod)%mod;
    printf("%d\n",ans);
    return 0;
}
```

也可以使用二元二项式反演，即根据一般形式（此时 $f$ 定义同上）：
$$f(x,y)=\sum_{i=x}^n\sum_{j=y}^n \dbinom{i}{x}\dbinom{j}{y} g(i,j)$$

反演得到：
$$g(x,y)=\sum_{i=x}^n\sum_{j=y}^n (-1)^{(i-x)+(j-y)}\dbinom{i}{x}\dbinom{j}{y} f(i,j)$$

---

## 作者：Calculatelove (赞：0)

[CF 1228E](https://codeforces.com/problemset/problem/1228/E)。

## Description

有一个 $n \times n$ 的网格图，对于网格图中的每一个格点，都可以用 $1 \sim k$ 中的任意一个数字来填充这个格点。

问有多少种填充方案，使得每行每列的最小值均为 $1$。答案对 $10^9 + 7$ 取模。

数据范围：$1 \leq n \leq 250$，$1 \leq k \leq 10^9$。  
时空限制：$1000 \ \mathrm{ms} / 250 \ \mathrm{MiB}$。

## Solution

不失一般性，可以钦定所有行是合法的，以针对列的合法性。在满足所有行是合法的情况下，**钦定** $i$ 列不合法的方案数为：
$$
\binom{n}{i}\left(k^{n - i}(k - 1)^i - (k - 1)^n\right)^n
$$

运用容斥计算答案，可以证明容斥的系数为 $\pm 1$ 交替，故答案为：
$$
\sum\limits_{i = 0}^n (-1)^i \binom{n}{i} \left(k^{n - i}(k - 1)^i - (k - 1)^n\right)^n
$$
时间复杂度 $\mathcal{O}(n \log n)$，瓶颈在于快速幂。

#### 证 1

考虑**恰好** $j(j \geq 1)$ 列不合法的方案数，那么在考虑**钦定** $0 \sim j - 1$ 列不合法的方案数时，会将该组方案多算这么多次：
$$
\begin{aligned}
\mathbf{cnt}
& = \sum\limits_{i = 0}^{j - 1} (-1)^i \binom{j}{i} \\
& = \sum\limits_{i = 0}^{j}(-1)^i \binom{j}{i} - (-1)^j \\
& = \left(1 + (-1)\right)^j - (-1)^j \\
& = -(-1)^j
\end{aligned}
$$
既然多算了 $-(-1)^j$ 次，就可以将当前的容斥系数设为 $(-1)^j$，此时恰好 $j$ 列不合法的方案数就被抵消了。

Q.E.D

#### 证 2

设**恰好** $i$ 列不合法的方案数为 $f(i)$，**钦定** $i$ 列不合法的方案数为 $g(i)$，易得：
$$
g(i) = \binom{n}{i}\left(k^{n - i}(k - 1)^i - (k - 1)^n\right)^n
$$
$$
g(i) = \sum\limits_{j = i}^n \binom{j}{i} f(j)
$$
运用二项式反演，可得：
$$
f(i) = \sum\limits_{j = i}^n (-1)^{j - i} \binom{j}{i} g(j)
$$
则：
$$
\begin{aligned}
\mathbf{ans}
& = f(0) \\
& = \sum\limits_{i = 0}^n(-1)^i \binom{i}{0} g(i) \\
& = \sum\limits_{i = 0}^n (-1)^i \binom{n}{i} \left(k^{n - i}(k - 1)^i - (k - 1)^n\right)^n
\end{aligned}
$$
Q.E.D

---

## 作者：wwlw (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1228E)
-----------

### Solution

不知道怎么就想到了……用 $G(x,y)$ 表示恰好有 $x$ 和 $y$ 行没有 $1$，那么答案就是 $G(0,0)$

用 $F(x,y)$ 表示强制有 $x$ 行 $y$ 列没有 $1$ ，剩下的随便填的可重方案，那么
$$F(x,y)=\binom{n}{x}\binom{n}{y}k^{(n-x)(n-y)}\times k^{n^2-(n-x)(n-y)}$$
组合意义为先选 $x$ 行 $y$ 列没有 $1$ ，对于这选了的部分，除去不能选 $1$，那么共有 $(k-1)^{n^2-(n-x)(n-y)}$ 种，对于没有选的，可以随便填数。

容易发现
$$F(x,y)=\sum_{i=x}^n \sum_{j=y}^n \binom{i}{x}\binom{j}{y}G(i,j)$$

反演一下，得到
$$G(x,y)=\sum_{i=x}^n \sum_{j=y}^n (-1)^{i+j-x-y} \binom{i}{x}\binom{j}{y} F(i,j)$$
代入 $x=0,y=0$ ，答案即为
$$\sum_{i=0}^n \sum_{j=0}^n (-1)^{i+j} \binom{n}{i}\binom{n}{j} k^{(n-i)(n-j)}\times k^{n^2-(n-i)(n-j)}$$

$O(n^2\log n)$ 暴力求解即可。


---

## 作者：xxbbkk (赞：0)

# 题目

[Luogu](https://www.luogu.com.cn/problem/CF1228E)

[CF](https://codeforces.com/problemset/problem/1228/E)

给定一个$n\cdot n$的矩阵，用$1$到$k$填充，要求每行每列至少有$1$个$1$​，求方案数。

# Sol

感觉和一道三色填充的题有一些共同之处。[CF997C](https://www.luogu.com.cn/problem/CF997C)

但是这道题可以$O(n^3)$（应该吧）。

所以仔细转化一下题意就可以有容斥的思路。

枚举$i,j$，表示钦定$i$行$j$列不合法，剩下的随便放。

如何保证不合法呢？强制只能选取$2$到$k$的整数就行了。
$$
ans=\sum\limits_{i=0}^n\sum\limits_{j=0}^n(-1)^{i+j}\binom{n}{i}\binom{n}{j}k^{(n-i)(n-j)}(k-1)^{n\cdot n-(n-i)(n-j)}
$$
$k^{(n-i)(n-j)}$的意思是除去强制不合法的$i$​行$j$列以外其余的随便放。

复杂度$O(n^2log\ n)$。

可以预处理快速幂省掉一个$log$​，但没必要。

# Code

在[这里](https://www.cnblogs.com/xxbbkk/p/15361928.html)

# 完结撒花❀

---

