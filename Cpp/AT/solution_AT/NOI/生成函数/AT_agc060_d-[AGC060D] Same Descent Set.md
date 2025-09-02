# [AGC060D] Same Descent Set

## 题目描述

求满足以下条件的 $(1,2,\cdots,N)$ 的排列对 $(P,Q)=((P_1,P_2,\cdots,P_N),(Q_1,Q_2,\cdots,Q_N))$ 的个数，并将结果对 $998244353$ 取模。

- 对于所有 $i$（$1 \leq i \leq N-1$），以下任意一个条件成立：
  - $P_i < P_{i+1}$ 且 $Q_i < Q_{i+1}$
  - $P_i > P_{i+1}$ 且 $Q_i > Q_{i+1}$

## 说明/提示

### 限制条件

- $2 \leq N \leq 2 \times 10^5$
- 输入的数均为整数

### 样例解释 1

$(P,Q)=((1,2),(1,2))$ 和 $(P,Q)=((2,1),(2,1))$ 这两组满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2```

### 输出

```
2```

## 样例 #2

### 输入

```
3```

### 输出

```
10```

## 样例 #3

### 输入

```
4```

### 输出

```
88```

## 样例 #4

### 输入

```
10```

### 输出

```
286574791```

# 题解

## 作者：苹果蓝17 (赞：9)

本文中 $\text{SEQ(F(x))}=\dfrac{1}{1-F(x)}$。

显然 $P,Q$ 应该一起计数。考虑枚举每两个相邻位置间的大小关系，计算满足限制的排列数量，答案即所有等价类大小的平方和。

假设枚举了每两个相邻位置间的大小关系，如何计算满足限制的排列数量？

这是一个经典问题，将所有 $\texttt{<}$ 容斥成 $\texttt{>}$ 或无限制，记所有 $\texttt{>}$ 形成的极长连续段长度分别为 $l_1,l_2,\cdots,l_t$，则方案数为 $\dbinom{n}{l_1+1,l_2+1,\cdots,l_t+1}$。

记 $f(S)$ 表示集合 $S$ 中的符号都是“无限制”，其它位置都钦定为 $\texttt{>}$ 时的上述方案数。于是答案为：

$$
\begin{aligned}
Ans &=\sum\limits_{S \subseteq [n-1]} (\sum\limits_{T \subseteq S} (-1)^{|S|-|T|} f(T))^2\\
&=\sum\limits_{T_1 \subseteq [n-1]} \sum\limits_{T_2 \subseteq [n-1]} (-1)^{|T_1|+|T_2|} 2^{n-1-|T_1 \bigcup T_2|} f(T_1) f(T_2)\\
&=2^{n-1} \sum\limits_{T_1 \subseteq [n-1]} \sum\limits_{T_2 \subseteq [n-1]} (-1)^{|T_1|+|T_2|} 2^{-|T_1|-|T_2|+|T_1 \bigcap T_2|} f(T_1) f(T_2)\\
&=2^{n-1} \sum\limits_{T_1 \subseteq [n-1]} \sum\limits_{T_2 \subseteq [n-1]} 2^{|T_1 \bigcap T_2|} (-\dfrac{1}{2})^{|T_1|+|T_2|} f(T_1) f(T_2)\\
&=2^{n+1} \sum\limits_{T_1 \subseteq [n-1]} \sum\limits_{T_2 \subseteq [n-1]} 2^{|T_1 \bigcap T_2|} (-\dfrac{1}{2})^{|T_1|+1} f(T_1) (-\dfrac{1}{2})^{|T_2|+1} f(T_2)\\
\end{aligned}
$$

注意到要统计 $|T_1 \bigcap T_2|$，那么再次容斥，钦定一些位置在 $T_1$ 与 $T_2$ 中均为“无限制”，这样就将序列划分为若干段。

容斥系数是什么呢？设钦定无限制，钦定均为“无限制”，钦定不均为“无限制”的容斥系数分别为 $A,B,C$，则要求 $A+B=2,A+C=1$。取 $A=B=1,C=0$ 即可。

考虑计算答案。先处理每一段的方案数，设其生成函数为 $G(x)$（注意 $x$ 次数代表点的个数而不是边），容易得到：

$$F(x)=\text{SEQ}(-\dfrac{1}{2} \sum\limits_{i \geq 0} \dfrac{x^i}{i!})$$

$$G(x)=\sum\limits_{i \geq 0} f_i^2 x^i$$

再处理最后答案的生成函数 $H(x)$。由于无限制，钦定均为 $\texttt{<}$ 的容斥系数均为 $1$，可以认为就是若干 $\mathcal{G}$ 中的元素拼在一起。

$$H(x)=\text{SEQ}(G(x))$$

最后答案即为 $2^{n+1} n! h_n$。

多项式求逆实现，总时间复杂度 $O(n \log n)$。

**Code**

```cpp
...
int n;
int F[N],G[N];
 
int main(){
	init(N-5);
	cin>>n;
	F[0]=1;
	for(int i=1;i<=n;i++) F[i]=mod-1ll*inv[i]*(mod-inv2)%mod;
	INV::solve(F,F,n);
	
	G[0]=1;
	for(int i=1;i<=n;i++) G[i]=mod-1ll*F[i]*F[i]%mod;
	INV::solve(G,G,n);
	
	cout<<1ll*G[n]*mul[n]%mod*mul[n]%mod*pw[n+1]%mod;
}
```

---

## 作者：syzf2222 (赞：4)

此题被 xzy 怒喷是菜题了。这篇题解是 lh 那篇的翻译。

不是很懂该怎么做啊，整个被牵着鼻子走。

---

设 $G(S)$ 表示填 `<` 的位置集合恰为 $S$ 的方案数，$F(S)$ 表示钦定 $S$ 以外的都填 `>` 的方案数。

则有 $G(S)=\sum\limits_{T\subseteq S} (-1)^{|S|-|T|}F(T)$。

而 $F(S)$ 的含义即是有 $S$ 个分割点把原排列分成了 $|S|+1$ 个连续的 `>` 段。

假设每个段的长度为 $l_i$，则方案数为 $\binom{n}{l_1,...,l_k}$，也即每个段是独立的。

$$
\sum\limits_{S} G(S)^2=\sum_{S}\sum_{T_1,T_2\subseteq S}(-1)^{|T1|+|T2|}F(T_1)F(T_2)
$$
$$
=\sum_{T_1,T_2} F(T_1)F(T_2)(-1)^{|T_1|+|T_2|}2^{n-1-|T_1\cup T_2|}
$$
$$
=2^{n+1}\sum_{T_1,T_2} \frac{F(T_1)}{(-2)^{|T1|+1}}\frac{F(T_2)}{(-2)^{|T_2|+1}}2^{|T_1\cap T_2|}
$$

注意到把 $(-2)^{|T|}$ 多配一个 $+1$ 是因为这样就相当于给每个连续段分配一个 $-\frac 12$。

现在难点在于处理 $2^{|T_1\cap T_2|}$，还是考虑容斥。钦定一些分割点两个都有，然后每段是独立的。注意到一个分割方案会在其所有子集都算到一次，所以容斥系数就是 $1$。

总结一下，设 $F_1,F_2,F_3,F_4$ 分别为考虑一个或两个排列的一个段的，整个排列的生成函数，有：

$$
F_1=-\frac 12 e^x,F_2=\frac 1{1-F_1},F_{3,i}=F_{2,i}^2,F_4=\frac 1{1-F_3}
$$

时间复杂度 $O(n\log n)$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int mod=998244353;
const int G=3;
const int iG=(mod+1)/3;
const int iv2=(mod+1)/2;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}return res;
}
int tr[maxn];
int n,c[maxn],F1[maxn],F2[maxn],F3[maxn],F4[maxn];
inline void ntt(int *f,int len,int flag){
    for(int i=0;i<len;i++)
        if(i<tr[i])swap(f[i],f[tr[i]]);
    for(int i=2;i<=len;i<<=1){
        int w=ksm(flag?G:iG,(mod-1)/i);
        for(int j=0,p=i>>1;j<len;j+=i){
            int wi=1;
            for(int k=j;k<j+p;k++){
                int tt=1ll*wi*f[k+p]%mod;
                f[k+p]=(f[k]-tt+mod)%mod;
                f[k]=(f[k]+tt)%mod;
                wi=1ll*wi*w%mod;
            }
        }
    }
    if(flag==0){
        int iv=ksm(len,mod-2);
        for(int i=0;i<len;i++)
            f[i]=1ll*f[i]*iv%mod;
    }
}
inline void workinv(int deg,int *a,int *b){
	if(deg==1)return void(b[0]=ksm(a[0],mod-2));
	workinv((deg+1)>>1,a,b);
	int len=1;for(;len<=(deg<<1);len<<=1);
	for(int i=0;i<len;i++)
		tr[i]=(tr[i>>1]>>1)|((i&1)?len>>1:0);
	for(int i=0;i<deg;i++)c[i]=a[i];
	for(int i=deg;i<len;i++)c[i]=0;
	ntt(c,len,1);ntt(b,len,1);
	for(int i=0;i<len;i++)
		b[i]=1ll*b[i]*(2-1ll*b[i]*c[i]%mod+mod)%mod;
	ntt(b,len,0);
	for(int i=deg;i<len;i++)b[i]=0;
}
int fac[maxn],inv[maxn],ifc[maxn];
int main(){
	n=read();inv[1]=fac[0]=ifc[0]=1;
	for(int i=2;i<=n;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=n;i++)ifc[i]=1ll*ifc[i-1]*inv[i]%mod;
	for(int i=1;i<=n;i++)F1[i]=1ll*iv2*ifc[i]%mod;F1[0]=1;
	workinv(n+1,F1,F2);F3[0]=1;
	for(int i=1;i<=n;i++)F3[i]=(mod-1ll*F2[i]*F2[i]%mod)%mod;
	workinv(n+1,F3,F4);
	printf("%d\n",1ll*ksm(2,n+1)*fac[n]%mod*fac[n]%mod*F4[n]%mod);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：云浅知处 (赞：3)

钦定左右的小于号集合**恰好**是 $S,T\subseteq\{1,2,\cdots,n-1\}$，那么限制相当于 $S=T$。

枚举这一集合 $S$，设 $f(S)$ 表示小于号集合**恰好**为 $S$ 的方案数，$g(S)$ 表示不对 $S$ 以内的元素进行约束，但钦定 $S$ 以外的元素都是大于号的方案数，那么有 $f(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}g(T)$，答案即
$$
\begin{aligned}
\sum_{S}f^2(S)&=\sum_{S}\sum_{T_1,T_2\subseteq S}(-1)^{|T_1|}g(T_1)\times (-1)^{|T_2|}g(T_2)\\
&=\sum_{T_1,T_2}(-1)^{|T_1|}g(T_1)\times (-1)^{|T_2|}g(T_2)\times 2^{n-1-|T_1\cup T_2|}\\
&=2^{n-1}\sum_{T_1,T_2}(-1)^{|T_1|}g(T_1)\times (-1)^{|T_2|}g(T_2)\times 2^{-|T_1|-|T_2|+|T_1\cap T_2|}\\
&=2^{n-1}\sum_{T_1,T_2}\left(-\frac{1}{2}\right)^{|T_1|}g(T_1)\times \left(-\frac{1}{2}\right)^{|T_2|}g(T_2)\times 2^{|T_1\cap T_2|}
\end{aligned}
$$
我们把 $2^{|T_1\cap T_2|}$ 看作枚举一个 $S\subseteq (T_1\cap T_2)$，然后交换求和顺序
$$
2^{n-1}\sum_{S}\sum_{T_1,T_2\supseteq S}\left(-\frac{1}{2}\right)^{|T_1|}g(T_1)\times \left(-\frac{1}{2}\right)^{|T_2|}g(T_2)
$$
回忆 $g(T)$ 的计算方法：设 $T=\{p_1,p_2,\cdots,p_k\}$，其中 $p_1<p_2<\cdots<p_k$，那么相当于把序列分成了若干段，每段必须递增，段之间随意，因此有
$$
g(T)=\dfrac{n!}{p_1!(p_2-p_1)!\cdots(p_k-p_{k-1})!(n-p_k)!}
$$
考虑算出长为 $L$ 的一段的容斥系数 $h_L$，不难得到
$$
h_1=1,h_L=1-\frac{1}{2}\times\sum_{j=1}^{L-1}G_j\binom{L}{j}
$$
然后设 $\text{dp}_i$ 表示考虑了前 $i$ 个位置，且钦定 $i\in S$ 时对答案的贡献之和，那么就有
$$
\text{dp}_0=1,\text{dp}_i=h_i^2+\sum_{j=1}^{i-1}\frac{1}{4}h_{i-j}^2\times \text{dp}_{j}\times \binom{i}{j}^2
$$
这两部分都可以用分治 NTT 或多项式求逆解决。于是就可以做到 $O(n\log^2n)$ 或 $O(n\log n)$ 了。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
mt19937 rnd(time(0));
int randint(int l,int r){return rnd()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

void Assert(bool c,int L=0){if(!c){cout<<"Assertion Failed at "<<L<<endl;exit(0);}}

void cmax(int &x,int v){x=max(x,v);}
void cmin(int &x,int v){x=min(x,v);}

const int N=4e5+5;
int f[N],g[N],n;

int fac[N],ifac[N];
void init(int V){
    fac[0]=1;for(int i=1;i<=V;i++)fac[i]=1ll*fac[i-1]*i%mod;
    ifac[V]=inv(fac[V])%mod;for(int i=V-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
    if(x<y)return 0;
    return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int rev[N<<1];
const int rg=3,irg=inv(rg);
void dft(vector<int>&A,int m,int tag){// A[0...2^m-1]
	for(int i=0;i<(1<<m);i++)rev[i]=((rev[i>>1]>>1)|((i&1)<<(m-1)));
	for(int i=0;i<(1<<m);i++)if(i<rev[i])swap(A[i],A[rev[i]]);
	for(int i=1;i<=m;i++){
		int p=(1<<(i-1)),q=(1<<i),wn=ksm(tag==1?rg:irg,(mod-1)>>i);
		for(int l=0,r=p;r<(1<<m);l+=q,r+=q){
			for(int k=l,w=1;k<r;k++,w=1ll*w*wn%mod){
				int x=A[k],y=1ll*A[k+p]*w%mod;
				Mod(A[k]=x+y),Mod(A[k+p]=x-y+mod);
			}
		}
	}
	if(tag==-1){
		int iv=inv(1<<m);
		for(int &x:A)x=1ll*x*iv%mod;
	}
}

vector<int>F,G;
int Iv;

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	init(N-5);n=read();
	int M=1,d=0;while(M<n)M<<=1,d++;

	for(int i=1;i<=n;i++)g[i]=ifac[i];Iv=inv(2);
	function<void(int,int,int)> solveG=[&](int l,int r,int d){
		if(l==r)return ;int mid=(l+r)>>1;
		solveG(l,mid,d-1);
		F.resize(1<<(d+1),0),G.resize((1<<(d+1)),0);
		for(int i=l;i<=mid;i++)F[i-l]=g[i];
		for(int i=1;i<=r-l;i++)G[i]=ifac[i];
		dft(F,d+1,1),dft(G,d+1,1);
		for(int i=0;i<=(1<<(d+1));i++)F[i]=1ll*F[i]*G[i]%mod;
		dft(F,d+1,-1);
		for(int i=mid+1;i<=r;i++)add(g[i],mod-1ll*Iv*F[i-l]%mod);
		vector<int>().swap(F),vector<int>().swap(G);
		solveG(mid+1,r,d-1);
	};
	
	solveG(1,M,d);
	for(int i=1;i<=n;i++)g[i]=1ll*g[i]*g[i]%mod;
	
	f[0]=1;Iv=1ll*Iv*Iv%mod;
	for(int i=1;i<=n;i++)f[i]=g[i];
	
	function<void(int,int,int)> solveF=[&](int l,int r,int d){
		if(l==r)return ;int mid=(l+r)>>1;
		solveF(l,mid,d-1);
		F.resize(1<<(d+1),0),G.resize((1<<(d+1)),0);
		for(int i=l;i<=mid;i++)F[i-l]=f[i];
		for(int i=1;i<=r-l;i++)G[i]=g[i];
		dft(F,d+1,1),dft(G,d+1,1);
		for(int i=0;i<=(1<<(d+1));i++)F[i]=1ll*F[i]*G[i]%mod;
		dft(F,d+1,-1);
		for(int i=mid+1;i<=r;i++)add(f[i],1ll*Iv*F[i-l]%mod);
		vector<int>().swap(F),vector<int>().swap(G);
		solveF(mid+1,r,d-1);
	};
	
	solveF(1,M,d);
	cout<<1ll*f[n]*ksm(2,n-1)%mod*fac[n]%mod*fac[n]%mod<<endl;

	return 0;
}
```

---

## 作者：OtoriEmu (赞：3)

闲话一句，这个题非常的难讲…… AT 上的题解可以说是不得已而为之了，这篇可能说了半点人话，还是请读者对着题解多思考一下吧。

假设 `>` 的位置构成集合 $S$（$S$ 只有 $n-1$ 个元素），记 $g(S)$ 为只有 $S$ 里面为 `>` 其他为 `<` 的方案数，则答案可以写作 $\displaystyle \sum_{S ⊆ U} g^2(S)$。

到这里毫无进展，注意到 $g(S)$ 可以容斥，于是再记 $f(S)$ 表示钦定 $S$ **外面的所有位置为 `<`** 而 $S$ 里面的位置任意，则 $\displaystyle g(S) = \sum_{T ⊆ S} f(T) (-1)^{|S|-|T|}$。

带回到答案，写作 $\displaystyle \sum_{S ⊆ U} \left( \sum_{T ⊆ S} f(T) (-1)^{|S|-|T|} \right)^2 = \sum_{S ⊆ U} \left( \sum_{T ⊆ S} f(T) (-1)^{|T|} \right)^2$。

仍然是死局，不如直接把平方拆开，发现直接枚举 $T_1,T_2$ 可以选择的 $S$ 的个数容易计算，

$$\begin{aligned}
\displaystyle \operatorname{Ans} &= \sum_{S ⊆ U} \sum_{T_1 ⊆ S,T_2 ⊆ S} f(T_1) f(T_2) (-1)^{|T_1|+|T_2|}\\
&= \sum_{T_1 ⊆ U,T_2 ⊆ U} f(T_1) f(T_2) (-1)^{|T_1|+|T_2|} 2^{n-1-|T_1 \cup T_2|} \\
\end{aligned}$$

在这里我们得到了一个带 $\cup$ 的东西，这个东西看起来就不好看……实际上我们只能选择枚举一个东西表示 $T_1 \cup T_2$，虽然我们又要重新枚举 $S$，但是和一开始的东西本质上是有区别的：

$$\begin{aligned}
\displaystyle \operatorname{Ans} &= \sum_{S ⊆ U} \sum_{T_1 \cap T_2  = S} (-1)^{|T_1|+|T_2|} f(T_1) f(T_2) 2^{n-1-|T_1| - |T_2| + |S|} \\
\end{aligned}$$

这里可以把 $2^{n-1}$ 提到最外层，$2^{|S|}$ 提到第一层，根据组合意义改写和式：

$$\begin{aligned}
\displaystyle \operatorname{Ans} &= 2^{n-1} \sum_{S ⊆ U} \sum_{S ⊆ T_1,S ⊆ T_2} \dfrac{f(T_1)}{(-2)^{|T_1|}} \dfrac{f(T_2)}{(-2)^{|T_2|}} \\
\end{aligned}$$

到这里对这个和式的基本研究就到这里。先考虑 $f(S)$ 的意义，$S$ 中所有的位置将原序列拆分成若干个子段，内部有序（参考 $f(S)$ 的定义），因此枚举 $S$ 的过程相当于集合划分（对于所有的划分方案均可以对应一个 $S$ 的状态）。则记 $S[i]$ 表示 $S$ 中的第 $i$ 个位置（令 $S[0]=0,S[|S|+1]=n$），则 $f(S) = \dfrac{n!}{\prod_{i=1}^{|S|+1}(S[i]-S[i-1])!} = \dbinom{n}{S[1],S[2],\cdots , S[|S|]}$。

再回去考虑如何计算上面的和式。还是没有很好的办法，于是考虑子问题。记 $\displaystyle F(n) = \sum_{S \in \{1,2,\cdots ,n-1\}} \dfrac{f(S)}{(-2)^{|S|}}$。这个东西实际上可以计算：从 $F(n)$ 转移到 $F(m)$，多出了 $n-m$ 个位置可以枚举，这里的系数实际上是 $F(n-m)$。于是计算 $F(n)$ 可以用分治 FFT 或者多项式求逆解决，这不是难点。

同样的回到答案的式子，一样考虑计算 $\displaystyle G(n) = 2^{n-1} \sum_{S ⊆ \{1,2,\cdots ,n-1\}} \sum_{S ⊆ T_1,S ⊆ T_2} \dfrac{f(T_1)}{(-2)^{|T_1|}} \dfrac{f(T_2)}{(-2)^{|T_2|}} = 4 \times 2^{n-1} \sum_{S ⊆ \{1,2,\cdots ,n-1\}} \sum_{i=1}^{|S|+1} \dfrac{f^2(S[i]-S[i-1])}{4}$（最外层有一个 $4$ 的系数，容易发现我们强制让 $[S[|S|],n]$ 分段，乘回去即可），然后从 $G(n)$ 转移到 $G(m)$，相当于多出一个子段，也就是子段划分。可以发现 $G(n+m) = \dfrac{G(n)G(m)}{4}$。这样问题求的就是 $G(n)$，$O(n \log^2 n)$ 的做法就是再用一次分治 FFT 来计算 $G(n)$。

有没有更好的做法？答案是有的：

$$\begin{aligned}
\displaystyle G(n) &= 2^{n+1} \sum_{\{a_k\},\sum a=n} \left(n! (\tfrac{-1}{2})^{k}\prod_{i=1}^k \dfrac{F(a_i)}{a_i!}\right)^2 \\
&= 2^{n+1}(n!)^2 \sum_{\{a_k\},\sum a=n} \prod_{i=1}^k \dfrac{F^2(a_i)}{4\times (a_i!)^2}
\end{aligned}$$

因为 $F,G$ 的本质就是划分，因此这样枚举 $a_k$ 相当于直接枚举 $S[i]-S[i-1]$，和为 $n$。于是 $G(n)$ 可以直接求逆算，求解 $F(n)$ 类似。

[评测记录](https://atcoder.jp/contests/agc060/submissions/37620789)。

---

## 作者：strapplE (赞：1)

看了一圈其它题解，感觉做法都有推式子，太麻烦了，比较不牛。这里宣传一下 @[pp_orange](https://www.luogu.com.cn/user/224443) 老师的“算子法”。

设 $A_i,B_i,A'_i,B'_i$ 表示四种限制，分别对应 $p_i<p_{i+1},p_i>p_{i+1},q_i<q_{i+1},q_i>q_{i+1}$，$C_i=A_i+B_i,C'_i=A'_i+B'_i$ 表示对这里无限制。则答案为：

$$\#[\prod\limits_{i=1}^{n-1}(A_iA'_i+B_iB'_i)]$$

$$=\#[\prod\limits_{i=1}^{n-1}(A_iA'_i+(C_i-A_i)(C'_i-A'_i))]$$

$$=\#[\prod\limits_{i=1}^{n-1}(C_iC'_i-A_iC'_i-C_iA'_i+2A_iA'_i)]$$

$$=\dfrac{1}{2^{n-1}}\#[\prod\limits_{i=1}^{n-1}(C_iC'_i+(C_i-2A_i)(C'_i-2A'_i))]$$

注意到 $C_iC'_i$ 相当于没有限制。所以把算式展开，变成若干个独立的 part。

也就是说，设 $f_m=\#[\prod\limits_{i=1}^{m-1}(C_i-2A_i)(C'_i-2A'_i)]$，则有：

$$F=\sum\limits_{i=1}^{n}\dfrac{f_i}{i!i!},ans=[\dfrac{x^n}{n!n!}]\dfrac{1}{1-F}$$

也就是算出 $f_m$ 之后做一次多项式求逆即可。

又显然 $f_m=\#^2[\prod\limits_{i=1}^{m-1}(C_i-2A_i)]$，而这里面的东西可以用完全一样的套路，也就是设 $g_k=\#[\prod\limits_{i=1}^{k-1}(-2A_i)]$，再做一次多项式求逆即可。

因此算出答案只需要两次多项式求逆，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define poly vector<int>
#define N 20
using namespace std;
void output(poly a){
	for(auto cu:a)printf("%d ",cu);
	printf("\n");
}
poly mul(int k,poly a){
	int sz=a.size();
	poly b;
	for(int i=0;i<sz;++i)b.emplace_back(1ll*k*a[i]%mod);
	return b;
}
poly plu(poly a,poly b){
	poly c;
	int s1=a.size(),s2=b.size();
	c.resize(max(s1,s2));
	for(int i=0;i<s1;++i)c[i]=(c[i]+a[i])%mod;
	for(int i=0;i<s2;++i)c[i]=(c[i]+b[i])%mod;
	return c;
}
poly mns(poly a,poly b){
	poly c;
	int s1=a.size(),s2=b.size();
	c.resize(max(s1,s2));
	for(int i=0;i<s1;++i)c[i]=(c[i]+a[i])%mod;
	for(int i=0;i<s2;++i)c[i]=(c[i]-b[i]+mod)%mod;
	return c;
}
int powdv(int x,int y=mod-2){
	int ans=1;
	while(y){
		if(y&1)ans=1ll*ans*x%mod;
		y>>=1,x=1ll*x*x%mod;
	}
	return ans;
}
int a[1<<N],b[1<<N],ap[1<<N],bp[1<<N];
int rev[1<<N];
void getrev(int l){
	rev[0]=0;
	for(int i=1;i<=l;++i){
		for(int j=0;j<(1<<(i-1));++j){
			rev[j^(1<<(i-1))]=rev[j]^(1<<(l-i));
		}
	}
}
void ntt(int l,int *c,int *d,int cd){
	for(int i=0;i<(1<<l);++i)d[i]=c[rev[i]];
	for(int i=1;i<(1<<l);i<<=1){
		int o1=powdv(3,(mod-1)/i/2);
		if(cd==-1)o1=powdv(o1);
		for(int j=0;j<(1<<l);j+=i+i){
			int o=1;
			for(int k=j;k<j+i;++k){
				int A=d[k],B=d[k+i];
				d[k]=(A+1ll*o*B)%mod,d[k+i]=(A-1ll*o*B)%mod;
				o=1ll*o*o1%mod;
			}
		}
	}
	if(cd==-1){
		int ny=powdv(1<<l);
		for(int i=0;i<(1<<l);++i)d[i]=1ll*d[i]*ny%mod;
	}
}
poly multi(vector<poly>g){
	int sz=0;
	for(auto p:g)sz+=p.size()-1;
	int ss=sz+1;
	while(ss&(ss-1))++ss;
	int l=__builtin_ctz(ss);
	getrev(l);
	for(int i=0;i<(1<<l);++i)ap[i]=1;
	for(auto p:g){
		int zz=p.size();
		for(int i=0;i<(1<<l);++i){
			a[i]=(i<zz?p[i]:0);
		}
		ntt(l,a,bp,1);
		for(int i=0;i<(1<<l);++i)ap[i]=1ll*ap[i]*bp[i]%mod;
	}
	ntt(l,ap,b,-1);
	poly ans;
	for(int i=0;i<=sz;++i)ans.emplace_back((b[i]+mod)%mod);
	return ans;
}
poly deri(poly a){
	if((signed)a.size()==1)return {0};
	int sz=a.size();
	poly b;
	for(int i=1;i<sz;++i)b.emplace_back(1ll*i*a[i]%mod);
	return b;
}
int id[1<<N],di[1<<N],ny[1<<N];
void init(int sz){
	di[0]=1;
	for(int i=1;i<=sz;++i)di[i]=1ll*i*di[i-1]%mod;
	id[sz]=powdv(di[sz]);
	for(int i=sz-1;i>=0;--i)id[i]=1ll*id[i+1]*(i+1)%mod;
	for(int i=1;i<=sz;++i)ny[i]=1ll*id[i]*di[i-1]%mod;
}
poly inte(poly a){
	int sz=a.size();
	init(sz);
	poly b;
	b.emplace_back(0);
	for(int i=0;i<sz;++i)b.emplace_back(1ll*ny[i+1]*a[i]%mod);
	return b;
}
poly mo(poly a,int n){
	poly b;
	int sz=min((signed)a.size(),n);
	for(int i=0;i<sz;++i)b.emplace_back(a[i]);
	return b;
}
poly inver(poly a,poly b,int n,int cs){
	if(cs==0)return b;
	int zz=min(2*(signed)b.size(),n);
	b=mo(plu(mul(2,b),mul(mod-1,multi({b,b,mo(a,2*b.size())}))),zz);
	return inver(a,b,n,cs-1);
}
poly inv(poly a,int n){
	poly b={1};
	int cc=1,gs=1;
	while(cc<=n)cc*=2,++gs;
	return inver(a,b,n,gs);
}
poly ln(poly a){
	poly pp=mo(multi({deri(a),inv(a,a.size())}),a.size()-1);
	return inte(pp);
}
poly rep(poly a){
	reverse(a.begin(),a.end());
	return a;
}
const int B=16;
int aa[200005],bb[200005];
void solve(int l,int r){
	if(r-l<=50){
		for(int i=l;i<r;++i){
			int he=0;
			for(int j=l;j<i;++j){
				he=(he+1ll*bb[j]*aa[i-j])%mod;
			}
			bb[i]=1ll*(bb[i]+he)*ny[i]%mod;
		}
		return;
	}
	int fd[B+5];
	for(int i=0;i<B;++i)fd[i]=l+(r-l)/B*i;
	fd[B]=r;
	int mx=0;
	for(int i=0;i<B;++i)mx=max(mx,fd[i+1]-fd[i]);
	int pp=mx;
	mx=3*mx+1;
	while(mx&(mx-1))++mx;
	int L=__builtin_ctz(mx);
	getrev(L);
	vector<int>vv;
	for(int i=0;i<(1<<L);++i)vv.emplace_back(rev[i]);
	vector<int>pt[B];
	for(int i=0;i<B;++i){
		for(int j=0;j<(1<<L);++j)a[j]=0;
		for(int j=fd[i]-l;j<fd[i]-l+2*pp&&j<r;++j)a[j-fd[i]+l]=aa[j];
		ntt(L,a,ap,1);
		for(int j=0;j<(1<<L);++j)pt[i].emplace_back(ap[j]);
	}
	vector<int>tp[B];
	for(int i=0;i<B;++i){
		for(int k=0;k<(1<<L);++k)ap[k]=0;
		for(int j=0;j<i;++j){
			for(int k=0;k<(1<<L);++k)
				ap[k]=(ap[k]+1ll*tp[j][k]*pt[i-j-1][k])%mod;
		}
		ntt(L,ap,a,-1);
		for(int k=fd[i];k<fd[i+1];++k)
			bb[k]=(bb[k]+a[k-fd[i]+(fd[1]-fd[0])])%mod;
		solve(fd[i],fd[i+1]);
		for(int k=0;k<(1<<L);++k)rev[k]=vv[k];
		for(int k=0;k<(1<<L);++k){
			a[k]=(k<fd[i+1]-fd[i]?bb[fd[i]+k]:0);
		}
		ntt(L,a,ap,1);
		for(int k=0;k<(1<<L);++k)tp[i].emplace_back(ap[k]);
	}
}
poly exp(poly a){
	int n=a.size();
	init(n);
	for(int i=0;i<n;++i)aa[i]=1ll*i*a[i]%mod,bb[i]=0;
	bb[0]=1;
	for(int i=1;i<n;++i)bb[i]=(bb[i]+aa[i])%mod;
	solve(1,n);
	poly b;
	for(int i=0;i<n;++i)b.emplace_back((bb[i]+mod)%mod);
	return b;
}
poly modu(poly a,poly b){
	int n=a.size()-1,m=b.size()-1;
	poly c=rep(mo(multi({rep(a),inv(rep(b),n-m+1)}),n-m+1));
	return mo(mns(a,multi({b,c})),m);
}
poly qmod(int k,poly a){
	if(k+1<(signed)a.size()){
		poly pp(k+1);
		pp[k]=1;
		return pp;
	}
	int kk=k/2;poly qq=qmod(kk,a);
	poly zz=multi({qq,qq});
	if(k&1){
		zz.resize(zz.size()+1);
		for(int i=zz.size()-1;i>=0;--i)zz[i+1]=zz[i];
		zz[0]=0;
	}
	return modu(zz,a);
}
int n,m;
int ax[300005],fx[300005],an[300005];
poly qs[150005],qt[150005];
void build(int l,int r,int o){
	if(l==r){
		qs[o]={1,mod-fx[l]};
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	qs[o]=multi({qs[o<<1],qs[o<<1|1]});
}
poly az;
poly jianfa(poly x,poly y,int cd=0){
	poly z(cd?cd:y.size()-x.size()+1);
	reverse(x.begin(),x.end());
	poly xy=multi({x,y});
	for(int i=0;i<(signed)z.size();++i)z[i]=xy[x.size()-1+i];
	return z;
}
pair<poly,poly>moduu(poly a,poly b){
	int n=a.size()-1,m=b.size()-1;
	poly c=rep(mo(multi({rep(a),inv(rep(b),n-m+1)}),n-m+1));
	return make_pair(c,mo(mns(a,multi({b,c})),m));
}
poly dn[100005];
poly up(int n){
	if(n==0)return {1};
	if(dn[n].size())return dn[n];
	if((n&1)||dn[n-1].size()){
		dn[n]=up(n-1);
		dn[n].resize(n+1);
		for(int i=n-1;i>=0;--i){
			dn[n][i+1]=(dn[n][i+1]+dn[n][i])%mod;
			dn[n][i]=1ll*(n-1)*dn[n][i]%mod;
		}
		return dn[n];
	}
	int nn=n/2;
	poly a=up(nn);
	poly a1,a2;
	for(int i=0;i<=nn;++i)
		a1.emplace_back(1ll*di[i]*a[i]%mod);
	int cj=powdv(nn,nn),cc=powdv(nn);
	for(int i=0;i<=nn;++i)
		a2.emplace_back(1ll*cj*id[nn-i]%mod),cj=1ll*cj*cc%mod;
	poly c=multi({a1,a2}),cp;
	for(int i=nn;i<=nn+nn;++i)cp.emplace_back(1ll*c[i]*id[i-nn]%mod);
	return dn[n]=multi({a,cp});
}
poly down(int n){
	poly uu=up(n);
	for(int i=n-1;i>=0;i-=2)uu[i]=mod-uu[i];
	return uu;
}
poly pzhux(poly a){
	if((signed)a.size()<=2)return a;
	int n=a.size(),nn=(n+1)/2;
	poly po=down(nn);
	auto au=moduu(a,po);
	poly p1=pzhux(au.second);
	int n2=n-nn;
	poly z1(n2),z2(n2),af(n2);
	for(int i=0;i<n2;++i)z1[i]=1ll*di[n2-1-i]*au.first[n2-1-i]%mod;
	int cj=1;
	for(int i=0;i<n2;++i){
		z2[i]=1ll*cj*id[i]%mod;
		cj=1ll*cj*nn%mod;
	}
	poly zz=multi({z1,z2});
	for(int i=0;i<n2;++i)af[i]=1ll*id[i]*zz[n2-1-i]%mod;
	poly p2=pzhux(af);
	poly an;
	for(auto cu:p1)an.emplace_back(cu);
	for(auto cu:p2)an.emplace_back(cu);
	return an;
}
int main(){
	int n;
	scanf("%d",&n);
	init(n);
	poly f(n+1);f[0]=1;
	int cj=mod-1;
	for(int i=1;i<=n;++i){
		f[i]=1ll*cj*id[i]%mod;
		cj=1ll*cj*(mod-2)%mod;
	}
	poly g=inv(f,n+1);g[0]=1;
	for(int i=1;i<=n;++i)g[i]=mod-1ll*g[i]*g[i]%mod;
	poly h=inv(g,n+1);
	int ans=1ll*di[n]*(h[n]+mod)%mod*di[n]%mod;
	ans=1ll*ans*powdv((mod+1)/2,n-1)%mod;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc060_d)

**题目大意**

> 求有多少个 $n$ 阶排列对 $(p,q)$ 使得 $(p_{i+1}-p_i)(q_{i+1}-q_i)>0$ 恒成立。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

定义排列 $p$ 的 Descent Set 为 $D(p)=\{i\mid p_i>p_{i+1}\}$。

设 $f(S)$ 表示 $D(p)=\overline S$ 的排列数，$g(S)$ 表示 $\overline{D(p)}\subseteq S$ 的方案数，即钦定 $\overline S$ 中的元素一定是 Descent 的。

那么设 $g(S)=\{s_1,s_2,\dots,s_k\}(s_i<s_{i+1})$，那么 $\overline S$ 中的元素构成若干连续段，每个连续段内都是严格递减的，我们只需要把 $n$ 个元素分到每个连续段内即可 $g(S)=\dfrac{n!}{s_1!(s_2-s_1)!\cdots(n-s_k)!}$。

根据容斥原理我们有 $f(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}g(T)$，化简一下答案：
$$
\begin{aligned}
\mathrm{Answer}
&=\sum_Sf(S)^2\\
&=\sum_S\left(\sum_{T\subseteq S}(-1)^{|S|-|T|}g(T)\right)^2\\
&=\sum_S\sum_{T_1\subseteq S}\sum_{T_2\subseteq S} (-1)^{|S|-|T_1|}g(T_1)(-1)^{|S|-|T_2|}g(T_2)\\
&=\sum_S\sum_{T_1\subseteq S}\sum_{T_2\subseteq S} (-1)^{|T_1|+|T_2|}g(T_1)g(T_2)\\
&=\sum_{T_1}\sum_{T_2}(-1)^{|T_1|+|T_2|}g(T_1)g(T_2)2^{n-1-|T_1\cup T_2|}\\
&=\sum_{T_1}\sum_{T_2}(-1)^{|T_1|+|T_2|}g(T_1)g(T_2)2^{n-1-|T_1|-|T_2|+|T_1\cap T_2|}\\
&=2^{n+1}\sum_{T_1}\sum_{T_2}\dfrac{g(T_1)}{(-2)^{|T_1|+1}}\times \dfrac{g(T_2)}{(-2)^{|T_2|+1}}\times 2^{|T_1\cap T_2|}
\end{aligned}
$$
最后几步的组合意义是：已知 $T_1,T_2$，满足 $T_1\cup T_2\subseteq S$ 的 $S$ 只有 $2^{n-1-|T_1\cup T_2|}$，然后容斥原理拆开化简。

根据 $g(T)$ 的组合意义，我们可以看成先枚举 $Q\subseteq T_1\cap T_2$，把 $1\sim n$ 划分成若干段，然后每一段内用 $T_1$ 和 $T_2$ 分别切割一遍，切割的段长为 $k$，那么就有一个 $\dfrac{1}{-2k!}$ 的系数。

注意到此时一个 $T_1\cap T_2$ 的每个子集都会算一次 $(T_1,T_2)$ 的贡献，此时总贡献恰好为 $2^{|T_1\cap T_2|}$。

因此设 $g_i$ 表示单个 $T$ 分 $i$ 阶排列的答案，那么 $g_i=\sum_{j<i}\dfrac{g_j}{-2(i-j)!}$。

设 $f_i$ 表示 $i$ 阶排列的答案，那么 $f_i=\sum_{j<i} f_jg^2_{i-j}$。

答案为 $2^{n+1}n!^2f_n$，两次分治 NTT 计算即可。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace P {
const int MOD=998244353,N=1<<19,G=3;
int rev[N],inv[N],w[N<<1];
int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) ret=1ll*ret*a%p;
	return ret;
}
void poly_init() {
	inv[1]=1;
	for(int i=2;i<N;++i) inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	for(int k=1;k<=N;k<<=1) {
		int x=ksm(G,(MOD-1)/k); w[k]=1;
		for(int i=1;i<k;++i) w[i+k]=1ll*x*w[i+k-1]%MOD;
	}
}
int plen(int x) { int y=1; for(;y<x;y<<=1); return y;  }
void ntt(int *f,bool idft,int n) {
	for(int i=0;i<n;++i) {
		rev[i]=(rev[i>>1]>>1);
		if(i&1) rev[i]|=n>>1;
	}
	for(int i=0;i<n;++i) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=2,x,y;k<=n;k<<=1) {
		for(int i=0;i<n;i+=k) {
			for(int j=i;j<i+k/2;++j) {
				x=f[j],y=1ll*f[j+k/2]*w[k+j-i]%MOD;
				f[j]=(x+y>=MOD)?x+y-MOD:x+y,f[j+k/2]=(x>=y)?x-y:x+MOD-y;
			}
		}
	}
	if(idft) {
		reverse(f+1,f+n);
		for(int i=0,x=ksm(n);i<n;++i) f[i]=1ll*f[i]*x%MOD;
	}
}
void poly_mul(const int *f,const int *g,int *h,int n,int m) {
	static int a[N],b[N];
	for(int i=0;i<n;++i) a[i]=f[i];
	for(int i=0;i<m;++i) b[i]=g[i];
	int len=plen(n+m-1);
	ntt(a,0,len),ntt(b,0,len);
	for(int i=0;i<len;++i) h[i]=1ll*a[i]*b[i]%MOD;
	ntt(h,1,len);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
}
}
const int N=1<<19,MOD=998244353,i2=(MOD+1)/2;
int f[N],g[N],a[N],b[N],c[N],fac[N],ifac[N];
void cdq1(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	int len=P::plen((r-l+1)*2);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
	memset(c,0,sizeof(int)*len);
	for(int i=0;i<=mid-l;++i) a[i]=g[i+l];
	for(int i=0;i<=r-l;++i) b[i]=1ll*(MOD-i2)*ifac[i]%MOD;
	P::poly_mul(a,b,c,mid-l+1,r-l+1);
	for(int i=mid+1;i<=r;++i) g[i]=(c[i-l]+g[i])%MOD;
	cdq1(mid+1,r);
}
void cdq2(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	cdq2(l,mid);
	int len=P::plen((r-l+1)*2);
	memset(a,0,sizeof(int)*len);
	memset(b,0,sizeof(int)*len);
	memset(c,0,sizeof(int)*len);
	for(int i=0;i<=mid-l;++i) a[i]=f[i+l];
	for(int i=0;i<=r-l;++i) b[i]=1ll*g[i]*g[i]%MOD;
	P::poly_mul(a,b,c,mid-l+1,r-l+1);
	for(int i=mid+1;i<=r;++i) f[i]=(c[i-l]+f[i])%MOD;
	cdq2(mid+1,r);
}
signed main() {
	P::poly_init();
	for(int i=fac[0]=ifac[0]=1;i<N;++i) ifac[i]=P::ksm(fac[i]=1ll*fac[i-1]*i%MOD);
	int n;
	scanf("%d",&n);
	g[0]=1,cdq1(0,n);
	f[0]=1,cdq2(0,n);
	printf("%lld\n",1ll*f[n]*P::ksm(2,n+1)%MOD*fac[n]%MOD*fac[n]%MOD);
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：0)

> 24.10.26 修正了一些笔误。绿色是修正的部分。

直接从数量出发设状态比较难，考虑设集合。设 $f(S)$ 表示 $n-1$ 个符号恰好 $S$ 的位置是 $<$，则答案为 $\sum_S f^2(S)$。考虑容斥，设 $g(S)$ 表示钦点 $S$ 中的符号无限制，$\overline{S}$ 全填 $>$，则 $f(S)=\sum_T(-1)^{|S|-|T|}g(T)$。（为什么从这个方向容斥稍后说明）

先考虑算 $g(S)$。设 $S=s_1,s_2,\ldots,s_{|S|}$，则 $g(S)=\dbinom{n}{s_1,s_2-s_1,\ldots,n-s_{|S|}}$，即“不限”把序列**划分**成若干段，每段内部要求降序。

答案即

$$\begin{aligned}
ans &=\sum_S\sum_{T_1,T_2\subseteq S}(-1)^{|T_1|}g(T_1)(-1)^{|T_2|}g(T_2)
\\

&= \sum_{T_1,T_2}(-1)^{|T_1|}g(T_1)(-1)^{|T_2|}g(T_2)\sum_{S\supseteq T_1,T_2}1
\\

&= 2^{n-1}\sum_{T_1,T_2}(-1)^{|T_1|}g(T_1)(-1)^{|T_2|}\green{g(T_2)}2^{-|T_1\cup T_2|}
\end{aligned}$$

剩下 $2^{-|T_1\cup T_2|}$ 不好办，考虑再次容斥：

$$\begin{aligned}
ans &= 2^{n-1}\sum_{T_1,T_2}(-1)^{|T_1|}g(T_1)(-1)^{|T_2|}g(T_2)2^{|T_1\cap T_2|-|T_1|-|T_2|}
\\

&= 2^{n-1}\sum_{T_1,T_2}(-\frac 1 2)^{|T_1|}g(T_1)(-\frac 1 2)^{|T_2|}g(T_2)2^{|T_1\cap T_2|}
\end{aligned}$$

可以看到并集的逆被转化成了交集，但还是需要处理。考虑枚举交集（把 $2^S$ 转换成枚举交集）进行展开：

$$\begin{aligned}
ans &= 2^{n-1}\sum_S\sum_{S\in T_1,T_2}(-\frac 1 2)^{|T_1|}g(T_1)(-\frac 1 2)^{|T_2|}g(T_2)
\\

&= 2^{n-1}\sum_S\sum_{S\in T_1,T_2}
	(-\frac 1 2)^{|T_1|}
    \left( n!t1_1!(t1_2-t1_1)!\cdots(n-t1_{|T_1|}\green{)!} \right)
    (-\frac 1 2)^{|T_2|}
    \left( n!t2_1!(t2_2-t2_1)!\cdots(n-t2_{|T_2|}\green{)!} \right)
\end{aligned}$$

这时候这个式子相当于选出若干 $t1_i$ 和 $t2_i$，钦点一些 $t1_i=t2_j$ 进入 $S$。即

$$
=2^{n+1}(n!)^2\sum_{\color{red}{S\subseteq T_1,T_2}}\left(\sum_{\sum l1_i = n}\prod_i\frac{1}{l1_i!}\right)\left(\sum_{\sum l2_i = n}\prod_i\frac{1}{l2_i!}\right)
$$

单独拎出常数，通过组合意义考虑一个 DP：从前往后选点，$h_i$ 表示钦点 $i$ 在 $S$ 中时的答案，枚举上个 $S$ 中的点在哪里，则 $h_i=\sum_{j<i}h_jc_{i-j}$，其中 $c_i=\left(\sum_{t_j=i}\prod_{j}\frac{1}{t_j}\right)^2$ 即中间任意选择“不限”或“钦定为 $>$”的方案数。这些均能多项式求逆解决。

> 另一个方向的容斥：设 $g(S)$ 表示钦定 $S$ 中全为 $<$ 而其余的任意。答案是 $\sum_S \sum_{S\subseteq T_1, T_2}(-1)^{|T_1|+|T_2|}g(T_1)g(T_2)$。然而这个式子不能直接优化。序列会被划分成 $n-|T|$ 个连续段，而已知连续段求方案数需要知道每个段的长度，该信息不方便由 $T$ 直接提供，而方便 $\overline{T}$ 提供；于是回到了上面的做法。

---

## 作者：tzc_wk (赞：0)

先推式子。设 $f(S)$ 表示 decent 集合恰好为 $S$ 的排列个数，$g(S)$ 表示 $S$ 是 $p$ 的 decent 集合的一个子集的排列 $p$ 个数，$g'(\{a_1,a_2,\cdots,a_k\})=\dfrac{n!}{a_1!(a_2-a_1)!(a_3-a_2)!\cdots(a_k-a_{k-1})!(n-a_k)!}$，那么有：
$$
\begin{aligned}
ans=&\sum_{S}f(S)^2\\
=&\sum\limits_{S}(\sum\limits_{S\subseteq T_1}(-1)^{|T_1|-|S|}g(T_1))(\sum\limits_{S\subseteq T_2}(-1)^{|T_2|-|S|}g(T_2))\\
=&\sum\limits_{T_1}\sum\limits_{T_2}g(T_1)(-1)^{|T_1|}·g(T_2)(-1)^{|T_2|}·2^{|T_1\cap T_2|}\\
=&\sum\limits_{T_1}\sum\limits_{T_2}g'(T_1)(-1)^{|T_1|+1}·g'(T_2)(-1)^{|T_2|+1}·2^{n-1-|T_1\cup T_2|}\\
=&\sum\limits_{T_1}\sum\limits_{T_2}g'(T_1)(-0.5)^{|T_1|+1}·g'(T_2)(-0.5)^{|T_2|+1}·2^{n+1+|T_1\cap T_2|}\\
=&\sum\limits_{T_1}\sum\limits_{T_2}g'(T_1)(-0.5)^{|T_1|+1}·g'(T_2)(-0.5)^{|T_2|+1}·2^{n+1}(\sum\limits_{S\subseteq T_1,S\subseteq T_2}1)
\end{aligned}
$$
考虑最后一个式子的含义，相当于我先将 $n$ 个元素划分为 $p$ 个部分 $a_1,a_2,\cdots,a_p$ 使得 $\sum a_p=n$，再对于每个 $a_i$，构造两个序列 $b_{i,1},b_{i,2},\cdots,b_{i,q_i}$ 和 $c_{i,1},c_{i,2},\cdots,c_{i,r_i}$，使得 $\sum b_{i,j}=\sum c_{i,j}=a_i$，方案数为 $\prod -\dfrac{1}{2(b_{i,j}!)}·\prod-\dfrac{1}{2(c_{i,j}!)}$，我们考虑设 $f_i$ 为将长度为 $i$ 的部分划分为若干个小部分的系数之和，显然 $f_i=\sum\limits_{j=0}^{i-1}f_j·(-\dfrac{1}{2(i-j)!})$，再设 $g_i$ 表示将长度为 $i$ 的序列划分为若干个大部分的贡献之和，有 $g_i=\sum\limits_{j=0}^{i-1}g_if_{i-j}^2$，两部分都可以分治 NTT 或者多项式求逆，时间复杂度 $O(n\log n)$ 或 $O(n\log^2n)$。

```cpp
const int MAXN=2e5;
const int MAXP=1<<19;
const int pr=3;
const int ipr=332748118;
const int MOD=998244353;
const int INV2=MOD+1>>1;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int rev[MAXP+5];
void NTT(vector<int>&a,int len,int type){
	int lg=31-__builtin_clz(len);
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<lg-1);
	for(int i=0;i<len;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=qpow((type<0)?ipr:pr,(MOD-1)/i);
		for(int j=0;j<len;j+=i){
			for(int k=0,w=1;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*a[(i>>1)+j+k]*w%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(!~type){
		int iv=qpow(len,MOD-2);
		for(int i=0;i<len;i++)a[i]=1ll*a[i]*iv%MOD;
	}
}
vector<int>conv(vector<int>a,vector<int>b){
	int LEN=1;while(LEN<a.size()+b.size())LEN<<=1;
	a.resize(LEN,0);b.resize(LEN,0);NTT(a,LEN,1);NTT(b,LEN,1);
	for(int i=0;i<LEN;i++)a[i]=1ll*a[i]*b[i]%MOD;
	NTT(a,LEN,-1);return a;
}
int n,res,fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++)ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD; 
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int f[MAXN+5],g[MAXN+5];
void calc_f(int l,int r){
	if(l==r)return;vector<int>A,B,C;int mid=l+r>>1;calc_f(l,mid);
	for(int i=l;i<=mid;i++)A.pb(f[i]);
	for(int i=0;i<=r-l;i++)B.pb(1ll*ifac[i]*(MOD-INV2)%MOD);
	C=conv(A,B);
	for(int i=mid+1;i<=r;i++)f[i]=(f[i]+C[i-l])%MOD;
	calc_f(mid+1,r);
}
void calc_g(int l,int r){
	if(l==r)return;vector<int>A,B,C;int mid=l+r>>1;calc_g(l,mid);
	for(int i=l;i<=mid;i++)A.pb(g[i]);
	for(int i=0;i<=r-l;i++)B.pb(1ll*f[i]*f[i]%MOD);
	C=conv(A,B);
	for(int i=mid+1;i<=r;i++)g[i]=(g[i]+C[i-l])%MOD;
	calc_g(mid+1,r);
}
int main(){
	scanf("%d",&n);init_fac(MAXN);f[0]=g[0]=1;calc_f(0,n);calc_g(0,n);
	printf("%d\n",1ll*g[n]*qpow(2,n+1)%MOD*fac[n]%MOD*fac[n]%MOD);
	return 0;
}
```



---

## 作者：_lbw_ (赞：0)

会忽略一些细节。

容易将问题变为求 $\sum\limits_S c_S^2$，$S$ 表示大于号集合。

然后小推一波式子：

$$\sum\limits_S c_S^2$$

对 $c_S$ 容斥，设 $p(S)=\sum\limits_{S\subseteq a}c_a$。

$$=\sum\limits_S(\sum\limits_{S\subseteq T}(-1)^{|T|-|S|}\sum\limits_{Q\subseteq T}c_Q)^2=\sum\limits_S(\sum\limits_{T\subseteq S}(-1)^{|T|-|S|}p(T))^2$$

$$=\sum_S\sum_{S\subseteq T_1,T_2}(-1)^{|T_1|+|T_2|}p(T_1)p(T_2)$$

我们考虑 $p$ 怎么求，将极长大于号连续段长度设为 $l_i$，那么：$p(S)=\dfrac{n!}{\prod l_i!}$。

$$=\sum_{T_1,T_2}(-1)^{|T_1|+|T_2|}p(T_1)p(T_2)\sum_{S\subseteq T_1,T_2}1$$

$$=\sum_{T_1,T_2}(-1)^{|T_1|+|T_2|}p(T_1)p(T_2)2^{|T_1\cap T_2|}$$

然后我们就裂开了。难点在于交的部分，我们比较艰难的想到把都为 1 改成都为 0 计算，设 $c_0(T_1,T_2)$ 为 $T_1,T_2$ 均为 $0$ 的位置。

$|T_1\cap T_2|=|T_1|+|T_2|-|T_1\cup T_2|=|T_1|+|T_2|-(n-1-c_0(T_1,T_2))$

然后忽略掉 $n-1$：

$$=\sum_{T_1,T_2}(-2)^{|T_1|+|T_2|}p(T_1)p(T_2)2^{c_0(T_1,T_2)}$$

我们知道当 $T_1,T_2$ 均为 $0$ 时 $l_i$ 会中断，对 $T_1,T_2$ 均为 $0$ 的点 dp，可以用 GF 将其表示。

射当 $T_1,T_2$ 没有均为 $0$ 时长度为 $k$ 的 $\sum_{T_1,T_2}(-2)^{|T_1|+|T_2|}p(T_1)p(T_2)$ 为 $[x^k]G(x)$ 。

再射 $[x^k]F(x)$ 为长度为 $k$ 时乱选的 $\sum_{T_1,T_2}(-2)^{|T_1|+|T_2|}p(T_1)p(T_2)$ 。

(注：$F,G$ 均为 EGF。)

容易发现 $[x^k]F(x)=(\sum_{T}(-2)^{|T|}p(T))^2$，设里面的 EGF 为 $H$。

又容易发现 $H=(-2)^{n-1}\textsf{SEQ}(-e^x/2)$，通过它可以很快算出 $F$。

艰难的发现 $F=G(F+1)$ 可以通过枚举第一个均为 0 得出。

于是：

$$G=\dfrac{F}{F+1},H=(-2)^{n-1}\textsf{SEQ}(-e^x/2)$$

本题得到解决！

（atcoder 的 modint 太好用了，还有 convolution。）









---

## 作者：歌吟入梦 (赞：0)

答案是

$$\sum_S(n!\sum_{S\subset T}(-1)^{|T|-|S|}\prod\frac{1}{l_i!})$$
$$=(n!)^2\sum_{T_1,T_2}(-1)^{|T_1|+|T_2|}\prod\frac{1}{l_{i1}}\prod\frac{1}{l_{i2}}2^{|T_1\cap T_2|}$$
$$=(n!)^2\sum_{T_1}(-2)^{|T_1|}\prod\frac{1}{l_{i1}}\sum_{T_2}(-2)^{|T_2|}\prod\frac{1}{l_{i2}}(\frac 12)^{n-1-\sum_{i}[i\notin T_1\&\&i\notin T_2 ]}$$

其中 $l_i$ 表示把 $T$ 集合中的位置填上大于号后形成的由大于号连接起来的若干连续段的长度。

注意到 $(-2)^{|T_1|}=(-2)^{n-1-\sum_{i}{[i\notin T_1]}}$，所以把 $(-2)^{n-1}$ 提到最前面之后可以看成每有一个 $i\notin T_1$ 就对答案有 $-\frac 12$ 的贡献，$T_2$ 同理，最后的 $(\frac 12)^{n-1-\sum_{i}[i\notin T_1\&\&i\notin T_2 ]}$ 可以看成每有一个 $i\notin T_1\&\&i\notin T_2$ 就对答案有 $2$ 的贡献。

考虑生成函数，一个长为 $n$ 的连续段对答案的贡献是 $-\frac 1{2n!}$，所以 $H=\frac{1}{1-(-\frac 12)(e^x-1)}$ 就是只考虑 $T_1$ 这一个集合，若干个总长为 $n$ 的连续段对答案的贡献的生成函数，令 $G$ 满足 $[x^0]G=0,[x^i]G=([x^i]H)^2(i\geq 1)$，那么 $G$ 就是同时考虑了 $T_1$ 和 $T_2$ 这两个集合对答案的贡献的生成函数。

现在还没考虑贡献的部分只剩下 $2^{[i\notin T_1\&\&i\notin T_2]}$ 了，满足 $i\notin T_1\&\&i\notin T_2$ 的位置 $i$ 把整个序列分成若干段，每段满足每个 $i$ 至少属于 $T_1$ 和 $T_2$ 中的一个，对答案贡献是 $2$，生成函数是 $F$。可以套路地得到 $G=F+GF$，组合意义就是讨论是否已经满足 $i$ 至少属于 $T_1$ 和 $T_2$ 中的一个这个限制，如果不满足枚举第一个既不属于 $T_1$ 又不属于 $T_2$ 的 $i$，则 $F=\frac{G}{G+1}$。

最后答案就是 $[x^n](2F+4F^2+...)$ 乘上前面提出来的系数，即 $(n!)^22^n[x^n]\frac{1}{1-2F}$

---

