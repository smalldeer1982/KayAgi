# Wonderful XOR Problem

## 题目描述

你是...算了，直接解决这个问题吧。

有 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \ldots [l_n, r_n]$。对于每个 $x$ 从 $0$ 到 $2^m - 1$，求满足以下条件的序列 $a_1, a_2, \ldots a_n$ 的数量（模 $998\,244\,353$）：

- 对于所有 $i$ 从 $1$ 到 $n$，有 $l_i \leq a_i \leq r_i$；
- $a_1 \oplus a_2 \oplus \ldots \oplus a_n = x$，其中 $\oplus$ 表示[按位异或运算符](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

对于第一个测试用例，$f_x$ 的值如下：

- $f_0 = 2$，因为有 $2$ 个有效序列：$[1, 1]$ 和 $[2, 2]$；
- $f_1 = 2$，因为有 $2$ 个有效序列：$[0, 1]$ 和 $[2, 3]$；
- $f_2 = 2$，因为有 $2$ 个有效序列：$[0, 2]$ 和 $[1, 3]$；
- $f_3 = 3$，因为有 $3$ 个有效序列：$[0, 3]$、$[1, 2]$ 和 $[2, 1]$。

$g_x$ 的值如下：

- $g_0 = f_0 \cdot 2^0 = 2 \cdot 2^0 = 2$；
- $g_1 = f_1 \cdot 2^1 = 2 \cdot 2^1 = 4$；
- $g_2 = f_2 \cdot 2^2 = 2 \cdot 2^2 = 8$；
- $g_3 = f_3 \cdot 2^3 = 3 \cdot 2^3 = 24$。

因此，输出的值为 $2 \oplus 4 \oplus 8 \oplus 24 = 22$。

对于第二个测试用例，$f_x$ 的值如下：

- $f_{0} = 120$；
- $f_{1} = 120$；
- $f_{2} = 119$；
- $f_{3} = 118$；
- $f_{4} = 105$；
- $f_{5} = 105$；
- $f_{6} = 106$；
- $f_{7} = 107$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 2
0 2
1 3
5 3
3 7
1 3
0 2
1 5
3 6
10 14
314 1592
653 5897
932 3846
264 3383
279 5028
841 9716
939 9375
105 8209
749 4459
230 7816
1 5
0 29```

### 输出

```
22
9812
75032210
1073741823```

# 题解

## 作者：喵仔牛奶 (赞：5)

## Solution

约定：定义 $x$ 的乘法为异或卷积，即 $x^p\times x^q=x^{p\oplus q}$。令 $v=2^m-1$，定义 $x\odot y=\text{popcount}(x\oplus y)$。

---

考虑这么一个问题：求 $\prod_{i=1}^{n}(a_i+b_ix^{c_i})$。

设答案为 $S$，考虑：
$$
\begin{aligned}
[x^k]\text{FWT}(S)=&\prod_{i=1}^{n}[x^k]\text{FWT}(a_i+b_ix^{c_i})\\
=&\prod_{i=1}^{n}(a_i+b_i(-1)^{c_i\odot k})
\end{aligned}
$$

可以用类似 XOR-FWT 的方法直接求出这个式子，然后就可以求出 $S$ 了。

会了这个就可以通过 CF1906K、ABC367G、CF1119H。

---

考虑本题：求 $\prod_{i=1}^{n}\sum_{j=L_i}^{R_i}x^j$。

仍然令答案为 $S$。我们希望把 $\sum_{j=L_i}^{R_i}x^j$ 化成 $(a_i+b_ix^{c_i})$ 的形式。

区间可以表示为前缀作差，不妨考虑 $L_i=0$ 的情况，考虑：
$$[x^k]\text{FWT}(\sum_{i=0}^{r}x^i)=\sum_{i=0}^{r}(-1)^{i\odot k}$$

设 $p=2^{\text{lowbit}(k)}$，则：
- 对于任意正整数 $c$，$\sum_{i=0}^{2pc-1}(-1)^{i\odot k}=0$。根据对称性可证。
- $(-1)^{i\odot k}=(-1)^{\lfloor\frac{i}{2p}\rfloor\odot\lfloor\frac{k}{2p}\rfloor}\cdot(-1)^{i\odot p}$。

因此令 $c=\lfloor\frac{r}{2p}\rfloor$，有：
$$
\begin{aligned}
\sum_{i=0}^{r}(-1)^{i\odot k}=&\sum_{i=2pc}^{r}(-1)^{i\odot k}\\
=&(-1)^{c\odot\lfloor\frac{k}{2p}\rfloor}\sum_{i=2pc}^{r}(-1)^{i\odot p}\\
=&(-1)^{c\odot\lfloor\frac{k}{2p}\rfloor}\sum_{i=0}^{r\bmod 2p}(-1)^{i\odot p}
\end{aligned}
$$

发现 lowbit 相同的 $k$ 不同之处只有指数上的 $\lfloor\frac{k}{2p}\rfloor$，看起来可以一起处理。枚举 $p$，考虑同时算出所有 $2^{\text{lowbit}(k)}=p$  的 $k$ 的 $[x^k]\text{FWT}(S)$。

设 $s(x)=\sum_{i=0}^{x\bmod 2p}(-1)^{i\odot p}$，令 $k'=\lfloor\frac{k}{2p}\rfloor$，$c_i=\lfloor\frac{R_i}{2p}\rfloor$，$a_i=s(R_i)$，$d_i=\lfloor\frac{L_i-1}{2p}\rfloor$，$b_i=-s(L_i-1)$。则：
$$
\begin{aligned}
[x^k]\text{FWT}(\sum_{i=L_i}^{R_i}x^i)=&a_i(-1)^{k'\odot c_i}+b_i(-1)^{k'\odot d_i}\\
=&[x^{k'}]\text{FWT}(a_ix^{c_i}+b_ix^{d_i})\\
=&[x^{k'}]\text{FWT}(x^{c_i}\times(a_i+b_ix^{c_i\oplus d_i}))
\end{aligned}
$$

用前面的方法算出 $\prod_{i=1}^{n}x^{c_i}\times\prod_{i=1}^{n}(a_i+b_ix^{c_i\oplus d_i})$ 就可以算出 $\text{FWT}(S)$ 了。注意这里要特判 $L_i=0$ 的情况。

每个 $p$ 算出的位拼到一起进行 IFWT 就是答案 $S$，注意 $[x^{\varnothing}]\text{FWT}(S)=\prod_{i=1}^{n}(R_i-L_i+1)$ 要单独算。

由于每次 $k'$ 的值域为 $[0,\frac{2^m}{p})$，复杂度是 $\mathcal O(nm+m2^m)$。[code](https://codeforces.com/contest/2096/submission/320654570)。

---

## 作者：Richard_Whr (赞：2)

神仙题。

直接考虑集合幂级数：

写出每个 $i$ 的集合幂级数：

$$[x^k]f_i=\sum\limits_{j=L_i}^{R_i}x^j$$

最终求的是对于所有 $k$：

$$[x^k]\prod\limits_{i=1}^{n}f_i$$

考虑使用 $\operatorname{FWT}$ 变成点积，考虑对于某个 $i$ 的 FWT 怎么求：

$$[x^k]FWT_f=\sum\limits_{i=0}^{2^m-1}(-1)^{|k \operatorname{and} j|}[x^i]f$$

设 $s(k,j)=(-1)^{|k \operatorname{and} j|}$，上面可以改写为：

$$[x^k]FWT_f=\sum\limits_{i=L_i}^{R_i}s(k,i)$$

显然可以使用差分转化为一段前缀求和，先考察一段前缀能不能进一步化简：

设 $f(k,r)=\sum\limits_{j \le r}s(k,j)$。

注意到如果我们固定了一段二进制数的前缀是顶着 $r$ 的，且下一位填的比 $r$ 小，则后面任意。如果此时 $k$ 最后面的这几位中有一个 $1$，由于对称性，此时求和一定为 $0$。

用形式化的柿子刻画上面的条件：设 $p=\operatorname{lowbit}(k),c=\lfloor\frac{r}{2^{p+1}}\rfloor$，则有：

$$f(k,2^{p+1} \times c -1)=0$$

现在可以改写 $f$ 为：

$f(k,r)=\sum\limits_{j=c \times 2^{p+1}}^{r}s(j,k)$

对于 $j$ 来说，二进制里面 $>p$ 位的部分是固定的，对于 $k$ 来说，二进制里面 $\le p$ 位的部分是固定的，这启发我们将这两部分分开考虑：

对于此时满足求和式条件的 $j$ 来说有：
$$s(j,k)=s(\lfloor\frac{j}{2^{p+1}}\rfloor,\lfloor\frac{k}{2^{p+1}}\rfloor) \times s(j,2^p)$$

$$f(r,k)=s(c,\lfloor\frac{k}{2^{p+1}}\rfloor) \times \sum\limits_{j=c \times 2^{p+1}}^{r}s(j,2^p)$$

前面是一个关于 $p,r$ 的定值，后面也是一个关于 $p,r$ 的定值，因此我们把它设出来：

- $k'=\lfloor \frac{k}{2^{p+1}} \rfloor$；

- $c_i=\lfloor\frac{R_i}{2^{p+1}}\rfloor$；

- $a_i=\sum\limits_{j=c_i \times 2^{p+1}}^{R_i}s(j,2^p)$；

- $d_i=\lfloor\frac{L_i}{2^{p+1}}\rfloor$；

- $b_i=-\sum\limits_{j=d_i \times 2^{p+1}}^{L_i}s(j,2^p)$；

$$f(r,k)=a_i \times s(k',c_i)+b_i \times s(k',d_i)$$；

这正好是 $[x^{k'}]\operatorname{FWT}(a_i \times x^{c_i}+b_i \times x^{d_i})$

我们设 $B_i=a_i \times x^{c_i}+b_i \times x^{d_i}$，有：

$$[x^k]\prod\limits_{i=1}^{n}\operatorname{FWT}(f_i)= [x^{k'}]\prod \limits_{i=1}^{n}\operatorname{FWT}(B_i)$$

我们希望对于每个相同的指数统计出来他的系数之和，方便使用 $\operatorname{FWT}$ 算法，先对 $B$ 做归一化处理：

$$a_i \times x^{c_i}+b_i \times x^{d_i}=(x^{c_i}+0) * (b_i \times x^{c_i \oplus d_i}+a_i)$$

用三元组 $(a,b,k)$ 代指一个集合幂级数形式。

对于指数相同的，有运算：

$$(a+b \times x^k)*(c+d \times x^k)=(a \times c + b \times d)+(a \times d+b \times c) \times x^k$$

这样我们求出一个 $B'_i = \sum\limits_{j=1}^{n}(a,b,k)[k=i]$。

现在我们的目标转化为了:

$$[x^k]\prod\limits_{i=0}^{2^k-1}\operatorname{FWT}(B'_i)=\prod\limits_{i=0}^{2^k-1}(a_i+b_i\times(-1)^{|k \operatorname{and}i|})$$

至此我们已经将问题转化为了可以使用普通 $\operatorname{FWT}$ 解决的经典问题。

我们直接枚举所有可能的 $\operatorname{lowbit(k)}$，算出来满足条件的 $k$ 的 $\operatorname{FWT}$ 即可。

最后再做一次 $\operatorname{IFWT}$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=2e5+10,M=18,V=(1<<M),mod=998244353,inv2=(mod+1)/2;
typedef pair<int,int> PII;
int L[N],R[N],a[N],b[N],c[N],d[N];
int f[V],g[V];
int suf[V];
PII B[V];
int Ans[V];
int n,m;

inline PII operator*(const PII &A,const PII &B)
{
	return {(A.x*B.x+A.y*B.y)%mod,(A.x*B.y+A.y*B.x)%mod};
}

void Fwt(int m)
{
	for(int len=1;len<(1<<m);len<<=1)
	{
		for(int p=0;p<(1<<m);p+=len*2)
		{
			for(int i=p,j=p+len;i<p+len;i++,j++)
			{
				int fa=f[i],ga=g[i],fb=f[j],gb=g[j];
				f[i]=fa*fb%mod;
				g[i]=ga*gb%mod;
				f[j]=fa*gb%mod;
				g[j]=ga*fb%mod;
			}
		}
	}
}

void IFwt()
{
	for(int len=1;len<(1<<m);len<<=1)
	{
		for(int p=0;p<(1<<m);p+=len*2)
		{
			for(int i=p,j=p+len;i<p+len;i++,j++)
			{
				int x=Ans[i],y=Ans[j];
				Ans[i]=(x+y)*inv2%mod;
				Ans[j]=(x-y)*inv2%mod;
			}
		}
	}
}

int T;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int s=0;s<(1<<m);s++) Ans[s]=0;
		Ans[0]=1;
		for(int i=1;i<=n;i++) cin>>L[i]>>R[i],L[i]--,Ans[0]=Ans[0]*(R[i]-L[i])%mod;
		
		for(int p=0;p<m;p++)
		{
			int t=m-p-1;
			suf[(1<<m)]=0;
			for(int s=(1<<m)-1;s>=0;s--)
			{
				suf[s]=(suf[s+1]+(((s>>p)&1)?-1:1));
			}
			for(int s=0;s<(1<<t);s++) B[s]={1,0};
			for(int i=1;i<=n;i++) a[i]=b[i]=c[i]=d[i]=0;
			for(int i=1;i<=n;i++)
			{
				a[i]=suf[(R[i]>>(p+1))<<(p+1)]-suf[R[i]+1];
				c[i]=(R[i]>>(p+1));
				if(L[i]>=0)
				{
					b[i]=suf[(L[i]>>(p+1))<<(p+1)]-suf[L[i]+1];
					b[i]=(mod-b[i])%mod;
					d[i]=(L[i]>>(p+1));
				}
				B[c[i]^d[i]]=B[c[i]^d[i]]*(PII){a[i],b[i]};
				B[c[i]]=B[c[i]]*(PII){0,1};
			}
			for(int s=0;s<(1<<t);s++) f[s]=(B[s].x+B[s].y)%mod,g[s]=(B[s].x-B[s].y)%mod;
			Fwt(t);
			for(int s=0;s<(1<<t);s++) Ans[(s<<1|1)<<p]=f[s];
		}	
		IFwt();
		int res=0;
		for(int s=0,pw=1;s<(1<<m);s++,pw=pw*2%mod)
		{
			int v=(Ans[s]%mod+mod)%mod;
			v=v*pw%mod;
			res^=v;
		}
		
		cout<<res<<"\n";
	}
	
	return 0;
}
```

---

## 作者：spdarkle (赞：1)

# CF 2096 H

注意到实为计算：
$$
\prod_{i=1}^n(z^{l_i}+z^{l_i+1}+\dots +z^{r_i})
$$
显然我们需要使用 $FWT$ 进行转化问题，设 $v(i,j)=(-1)^{|i\cap j|}$。

不妨设 $F_i(z)=z^{l_i}+z^{l_i+1}+\dots +z^{r_i}$
$$
[z^k]IFWT(FWT\prod_{i=1}^n F_i(z))=\prod_{i=1}^n(\sum_{j=l_i}^{r_i}v(k,j))
$$
设 $s(i,j)=\sum_{k=0}^jv(i,k)$

即，求：
$$
\prod_{i=1}^n(s(k,r_i)-s(k,l_i-1))
$$
考虑 $s$ 怎么求。

注意到对于 $k$ 而言，如二进制位 $t$ 上是 $1$，那么对于 $x$ 与 $x\oplus 2^t$ 两者的 $v$ 值相反。

这启发我们：设 $t$ 为 $k$ 的 lowbit，则有 $s(k,2^{t+1}-1)=0$，以至于更多的循环节，也即 $\forall c\in \mathbb{N},s(k,c2^{t+1}-1)=0$。

那么就会有：
$$
\begin{aligned}
s(k,r)&=s(k,\lfloor\frac{r}{2^{t+1}}\rfloor2^{t+1}-1)+\sum_{i=\lfloor \frac{r}{2^{t+1}}\rfloor2^{t+1}}^rv(k,i)\\
&=\sum_{i=\lfloor \frac{r}{2^{t+1}}\rfloor2^{t+1}}^rv(k,i)\\
&=\sum_{i=\lfloor \frac{r}{2^{t+1}}\rfloor2^{t+1}}^rv(\lfloor\frac{k}{2^{t+1}}\rfloor,\lfloor\frac{i}{2^{t+1}}\rfloor)\times v(2^{t+1},i)\\
&=v(\lfloor\frac{k}{2^{t+1}}\rfloor,\lfloor\frac{r}{2^{t+1}}\rfloor)\times \sum_{i=\lfloor \frac{r}{2^{t+1}}\rfloor2^{t+1}}^rv(2^{t+1},i)\\
&=v(\lfloor\frac{k}{2^{t+1}}\rfloor,\lfloor\frac{r}{2^{t+1}}\rfloor)\times \sum_{i=0}^{r\bmod 2^{t+1}}v(2^{t+1},i)
\end{aligned}
$$
当确定 $t$ 时，有 $s(k,r)=v(\lfloor\frac{k}{2^{t+1}}\rfloor,\lfloor\frac{r}{2^{t+1}}\rfloor)\times s(\lfloor\frac{k}{2^{t+1}}\rfloor,r\bmod 2^{t+1})$

注意到前面就是 $[z^{\lfloor\frac{k}{2^{t+1}}\rfloor}]FWT(z^{\lfloor\frac{r}{2^{t+1}}\rfloor})$，而后面的可以预处理计算。

不妨设：
$$
a_i=s(\lfloor\frac{k}{2^{t+1}}\rfloor,r\bmod 2^{t+1}),A_i=\lfloor\frac{r}{2^{t+1}}\rfloor
$$

$$
b_i=-s(\lfloor\frac{k}{2^{t+1}}\rfloor,(l-1)\bmod 2^{t+1}),B_i=\lfloor\frac{l-1}{2^{t+1}}\rfloor
$$
当 $l=0$ 时令 $b_i=B_i=0$。让 $k'=\lfloor\frac{k}{2^{t+1}}\rfloor$

那么 $s(k,r)-s(k,l-1)=[z^{k'}](a_iz^{A_i}+b_iz^{B_i})$

也就是说：
$$
[z^k]\prod_{i=1}^nFWT(F_i(z))=[z^{k'}]\prod_{i=1}^nFWT(a_iz^A_i+b_iz^{B_i})
$$
考虑求出后面这个多项式。

不妨再分解一下：
$$
(a_iz^{A_i}+b_iz^{B_i})=(a_i+b_iz^{A_i\oplus B_i})z^{A_i}
$$
然后，我们将指数上相同的多项式进行合并，合并是容易的：
$$
(a_1+b_1z^c)(a_2+b_2z^c)=(a_1a_2+b_1b_2+(a_1b_2+a_2b_1)z^c)
$$
那么我们就可以将其转化为：设 $p_i,r_i$ 为合并后的对应 $z^i$ 这个式的系数。

也就有：
$$
\prod_{i=1}^nFWT(a_iz^A_i+b_iz^{B_i})=\prod_{i=0}^{2^{m}-1}FWT(p_i+q_iz^i)
$$
那么 $[z^{k'}]$ 的系数是：
$$
\prod_{i=0}^{2^m-1}(p_i+v(k',i)q_i)
$$
这个东西的计算可以仿照一般的 $FWT$，维护 $ad_i=p_i+q_i,de_i=p_i-q_i$，那么在 $FWT$ 过程中就有：
$$
\begin{cases}
ad_{x}'=ad_{x}ad_{x+2^t},de_x'=de_xde_{x+2^t}\\
ad_{x+2^{i}}'=ad_{x}de_{x+2^t},de'_{x+2^t}=de_xad_{x+2^t}
\end{cases}
$$
那么这个题就解决了。

枚举 $t$，就可以计算一个长度为 $2^{m-t-1}$ 的多项式，然后将所有 $lowbit$ 为 $t$ 的 $k$ 的答案就算出来了。

最后还原即可。

注意 $0$ 的值特殊计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define N 1050500
const int p=998244353;
int le[N],ri[N];
struct node{
	int ad,de;
}f[N],h[N],tmp[N];
int n,m,a[N],val[N],b[N],c[N],d[N],g[N],na[N],nb[N],bit[N];
void sol(){
	cin>>n>>m;g[0]=1;bit[0]=1;
	for(int i=1;i<(1<<m);++i)bit[i]=-bit[i^(i&-i)];
	for(int i=1;i<=n;++i){
		cin>>le[i]>>ri[i];++ri[i];++le[i];
		g[0]=g[0]*(ri[i]-le[i]+1)%p;
	}
	for(int i=0;i<(1<<m);++i){
		val[i]=na[i]=nb[i]=0;
	}
	for(int t=m-1;~t;--t){
		for(int i=0;i<(1<<m);++i)val[i]=bit[(1<<t)&i];
		for(int i=1;i<(1<<m);++i)val[i]+=val[i-1];
		for(int i=0;i<(1<<m);++i)na[i]=1,nb[i]=0;
		for(int i=1;i<=n;++i){
			a[i]=val[(ri[i]-1)%(1<<t+1)],b[i]=le[i]>1?-val[(le[i]-2)%(1<<t+1)]:0;
			c[i]=(ri[i]-1)>>t+1,d[i]=le[i]>1?(le[i]-2>>t+1):0;
			int a1=na[c[i]^d[i]],b1=nb[c[i]^d[i]];
			na[c[i]^d[i]]=a1*a[i]%p+b1*b[i]%p;
			nb[c[i]^d[i]]=a1*b[i]%p+a[i]*b1%p;
			a1=na[c[i]],b1=nb[c[i]];
			na[c[i]]=0ll*a1+1ll*b1;
			nb[c[i]]=a1*1ll+0ll*b1;
		}
		for(int i=0;i<(1<<m-t-1);++i){
			f[i].ad=((na[i]+nb[i])%p+p)%p,f[i].de=((na[i]-nb[i])%p+p)%p,tmp[i]=f[i];
		}
		for(int len=1;len<(1<<m-t-1);len<<=1)for(int j=0;j<(1<<m-t-1);j+=len<<1)for(int k=0;k<len;++k){
			node a=f[j+k],b=f[j+k+len];
			f[j+k].ad=a.ad*b.ad%p,f[j+k].de=a.de*b.de%p;
			f[j+k+len].ad=a.ad*b.de%p;f[j+k+len].de=a.de*b.ad%p;
		}
		for(int k=0;k<(1<<m);++k)if((k&-k)==(1<<t))g[k]=f[k>>t+1].ad%p;
	}
	for(int len=1;len<(1<<m);len<<=1)for(int j=0;j<(1<<m);j+=len<<1)for(int k=0;k<len;++k){
		int x=g[j+k],y=g[j+k+len];
		g[j+k]=(x+y)%p*(p+1>>1)%p;
		g[j+k+len]=(x-y)%p*(p+1>>1)%p;
	}int ans=0;
	for(int i=0,mul=1;i<(1<<m);++i,mul=mul*2ll%p)g[i]=(g[i]*mul%p+p)%p,ans^=g[i];
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)sol();
}
```

---

## 作者：Union_of_Britain (赞：0)

设 $I_i=[l_i,r_i]$，等价于要求

$$\prod_i \sum_{j\in I_i}z^j$$

FWT 后是

$$[x^p]\hat F=\prod_i \sum_{j\in I_i}(-1)^{j\odot p}$$

这里可以利用一个区间的性质是拆成 $O(\log V)$ 个高位给定，低位任意的区间，这里设为 $t_{i,k},d_{i,k}$ 意为确定的高位加上低位全 $0$ 为 $t$，任意的低位位数是 $d$，化简

$$\sum_{j=t}^{t+2^d-1}(-1)^{j\odot p}=2^d[d\le d(p)](-1)^{t\odot p}$$

其中 $d(p)$ 表示 $p$ 为 $0$ 的连续低位位数。

这样若枚举 $\hat F$ 的 $d(p)$，就化为了 $O(\log V)$ 个项的 [Triple](https://www.luogu.com.cn/problem/CF1119H) 问题（有 $d$ 项时复杂度为 $O(V2^d(\log V+d))$），当然这是不够的。

考察分出的区间。设 $d$ 为最低的 $d$ 使得 $k\times 2^d\in I$。则 $k\times 2^d$ 向右 $O(\log V)$ 个区间的 $t$ 由上一个 $t$ 加上上一个项的 $2^d$ 得到。而已经得到 $d\le d(p)$，所以加入的 $2^d$ 是不影响 $t\odot p$ 的值的。故左右分别直接化为了一项，即只需解决两项的 Triple 问题。

最终复杂度是 $O(V\log V)$。

---

