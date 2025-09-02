# Hard Brackets Inserting

## 题目描述

小 S 有一个长度为 $n$ 的**合法**括号序列。

现在小 K 看到了，想在其中插入若干括号，使之成为一个长度为 $m$ 的括号序列（不一定合法）。但是她不想完全破坏这个序列，于是她希望对于她这种添加括号的方式，仅存在一种合法的且长度为 $n$ 的括号序可以通过插入若干括号来得到小 K 改后的序列，这样小 S 就可以轻松还原出原来的括号序列了（也就是说在保证删完后的括号序列长度为 $n$ 且合法的情况下，无论小 S 如何删除括号，都只能得到她初始的括号序列）。

求小 K 插入括号的方案数模 $998244353$。两种插入括号的方案不同当且仅当我们将最终的括号序列按照是小 K 所插入的还是原有的两类分别染成红色和黑色，得到的带颜色的括号序列不同。

## 说明/提示

### 样例解释

对于第一组样例，我们有如下 $8$ 种插入方式：

$\textcolor{red}{)}(())$

$((\textcolor{red}{)}))$

$(()\textcolor{red}{)})$

$(())\textcolor{red}{)}$

$\textcolor{red}{(}(())$

$(\textcolor{red}{(}())$

$((\textcolor{red}{(}))$

$(())\textcolor{red}{(}$

其中红色的括号表示小 K 插入的括号。

如下的方式是不可行的：

$(\textcolor{red}{)}())$

因为你可以通过删除第二个括号或第四个括号来获得如下两种括号序列：$(()),()()$。

### 数据范围

**本题采用捆绑测试**

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $m\le 10$ |
| $1$ | $30$ | $m\le 100$ |
| $2$ | $20$ | $n=2$ |
| $3$ | $30$ | $n\ne 2$ |

对于所有数据，保证 $1\le n\le m$ 且 $\sum m\le 10^6$，$1\le T\le 100$。

## 样例 #1

### 输入

```
2
4 5
(())
2 3
()```

### 输出

```
8
6```

# 题解

## 作者：dead_X (赞：8)

## 前言
考场降智想到了性质但是没有考虑那一类情况，于是寄了。
## 思路
首先 $n=2$ 的情况是平凡的，我们直接判掉就行了。

下文用“最后一段”指最右边的极长左括号段，我们考虑新加入的左括号：

* 在最后一段之前，例如 $\texttt{(())(())}\to\texttt{(()}\color{red}\texttt{(}\color{black}\texttt{)(())}$。

删除最后一段的一个括号，加入这个括号，显然仍然合法，因此不能插入。

* 加入最后一段，例如 $\texttt{(())(())}\to\texttt{(())}\color{red}\texttt{(}\color{black}\texttt{(())}$ 或者 $\texttt{(()())}\to\texttt{(()}\color{red}\texttt{(}\color{black}\texttt{())}$。

如果删除倒数第二段的一个括号，加入这个括号仍然合法，那么不能插入，否则可以插入。

给出的例子中，第一个是合法的，而第二个是不合法的。

通过观察和验证不难发现这个条件等价于**这段括号后左括号和右括号的数量不相等**。

* 加入最后一段之后，但是右侧仍然存在一个右括号，例如 $\texttt{(())(())}\to\texttt{(())(()}\color{red}\texttt{(}\color{black}\texttt{)}$。

删除最后一段的一个括号，加入这个括号，显然仍然合法，因此不能插入。

* 加入末尾，例如 $\texttt{(())(())}\to\texttt{(())(())}\color{red}\texttt{(}$。

显然不可能选这个括号，于是还是合法，因此可以插入。 

右括号是同理的，于是我们证明了只能在如上所述的地方插入新的括号的必要性。不难发现在最开始插入右括号和在最后插入左括号都没有意义，而剩下的情况中插入的括号要么只能形成 $\texttt{((...()...))}$，要么根本没有交集，因此充分性也可以证明。

计数是平凡的，设 $f_i$ 为插入 $i$ 个左括号的情况。

如果左括号只能在最后插入，那么 $f_i=1$。

如果左括号可以在最后或最后一段左括号插入，记最后一段左括号长度为 $l$，那么 $f_i=\sum\limits_{j=0}^i\binom{l+i}{i}$。

合并左括号和右括号的方案数即可，时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
char s[1000003];
int fac[1000003],ifac[1000003];
int C(int n,int m)
{
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int A(int x,int y,int z)
{
	int res=0;
	if(x!=z) return 1;
	for(int i=0; i<=y; ++i)
		res=(res+C(x+i,i))%p; 
	return res;
}
int F[1000003],G[1000003];
signed main()
{
	const int N=1000000;
	fac[0]=ifac[0]=1;
	for(int i=1; i<=N; ++i) fac[i]=fac[i-1]*i%p;
	ifac[N]=qp(fac[N],p-2);
	for(int i=N-1; i>=1; --i) ifac[i]=ifac[i+1]*(i+1)%p;
	for(int T=read();T--;)
	{
		int n=read(),m=read();
		scanf("%s",s+1);
		if(n==2) printf("%lld\n",(m*(m-1)/2)%p*qp(2,m-n)%p);
		else
		{
			m-=n;
			int fir=1,lst=n,fc=0,lc=0,ffc=0,llc=0;
			while(s[fir]=='(') ++ffc,++fir;
			while(s[lst]==')') ++llc,--lst;
			while(s[fir]==')') ++fc,++fir;
			while(s[lst]=='(') ++lc,--lst;
			int ans=0;
			F[0]=G[0]=1;
			for(int i=1; i<=m; ++i) 
			{
				F[i]=F[i-1];
				if(fc==ffc) F[i]=(F[i]+C(fc+i,i))%p;
			}
			for(int i=1; i<=m; ++i) 
			{
				G[i]=G[i-1];
				if(lc==llc) G[i]=(G[i]+C(lc+i,i))%p;
			}
			for(int i=0; i<=m; ++i) ans=(ans+F[i]*G[m-i])%p;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：yyandy (赞：2)

这题不是很好想啊，感觉质量还是很高的。

首先考虑加一个括号，再删除一个括号的情况。

如果考虑清楚怎么加括号是合法的，后面的计数就是水到渠成了。

容易发现加入左括号的情况可由加入右括号的情况同理得到，因此我们先只考虑加入右括号。

最简单的情况就是将这个右括号加到最左边，

此时为了保证逆操作后的序列合法，这个右括号必然得删除，于是序列唯一。

接下来考虑其他情况：

有一个显然的事实：对于一连串的右括号，无论从中删除哪一个产生的序列都相同（为了方便，下文将连续的右括号子段称为“右括号串”）。

这启示我们将右括号加到一串右括号中间，这时候无论删除这一串右括号中的哪一个右括号，都只能得到原来的序列。

但是，我们加入一个右括号的时候，删除的右括号不一定是在该“右括号串”中的，比如：
```
原括号序列：(()())
加入一个括号后的序列：(()()))
删除一个括号后的序列：((()))
```
当删除的右括号不在该“右括号串”中的时候，得到的序列一定是与原括号序列不同的，我们要避免这一种情况。

发现加入一个右括号后如果删除从左往右第一个右括号，那么留下的序列一定合法，因此我们必须得保证插入的右括号和第一个右括号在同一个“右括号串”中。

再结合删除后面的右括号的情况就可以得到充要条件：

设第一个右括号所在的“右括号串”的结束位置是 $pos$。

当前 $\frac{pos}{2}$ 个都是 `（`，接下来 $\frac{pos}{2}$ 个都是 `)`。

这时能够插入一个右括号到这第一个“右括号串中”。

这一个右括号串的长度是 $\frac{pos}{2}$，也就有 $\frac{pos}{2}+1$ 个空可供插入括号。

再算上插入到最左侧的情况，一共有 $\frac{pos}{2}+2$ 个空可以插入。（对于第一个“右括号串”不满足上述条件的情况，只能插入到最左边，也就是只有一个空可以插入括号）

这就解决了插入一个右括号的情况，也就解决了插入一个括号的情况。



------------

往一个空里面插入任意多个括号都不会影响方案合法性，

于是如果只加入右括号的话我们是可以算的。

设加入了 $k$ 个右括号，有 $p$ 个空可以插入右括号。

因为每一个空可以插可以不插，所以方案数是 $\binom{k+p}{k}$。

而左右括号其实是相互独立的，因此加入多个括号就很容易想到枚举加入左括号的个数和右括号的个数，将左右括号的插入方案的乘积求和即可。

------------
还要考虑特殊的 $n=2$ 的情况。（这一点在题目的数据范围里已经提示了）

$n=2$ 时无论怎么插入都是合法的，先考虑将新插入的括号划分为三个部分的方案数是 $\binom{m-n+2}{2}$。

然后每一个新插入的括号可以是左括号也可以是右括号，方案数应该再乘上 $2^{m-n}$。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int md=998244353;

int fac[1020000],inv[1020000];
char c[1020000];
inline int pw(int x,int y){
	if(!y)return 1;
	ll ans=pw(x,y>>1);
	if(y&1)return ans*ans%md*x%md;
	return ans*ans%md;
}
inline int C(int x,int y){
	return 1ll*fac[x]*inv[y]%md*inv[x-y]%md;
}
inline void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%md;
	inv[n]=pw(fac[n],md-2);
	for(int i=n-1;~i;--i)
		inv[i]=1ll*inv[i+1]*(i+1)%md;
}
int main(){
	int T;
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init(1000005);
	cin>>T;
	while(T--){
		int n,m,tot1=0,tot2=0,ans=0;
		cin>>n>>m;for(int i=1;i<=n;++i)cin>>c[i];
		if(n==2){cout<<1ll*C(m-n+2,2)*pw(2,m-n)%md<<'\n';continue;}
		for(int i=1,mx=0,pre=0;i<=n;++i){
			mx=max(mx,pre+=((c[i]=='(')*2-1));
			if(!pre){tot1=(mx*2==i)*(mx+1);break;}
		}
		for(int i=n,mx=0,pre=0;i;--i){
			mx=max(mx,pre+=((c[i]==')')*2-1));
			if(!pre){tot2=(mx*2==n-i+1)*(mx+1);break;}
		}
		for(int i=0,j=m-n;i<=m-n;++i,--j)ans=(ans+1ll*C(tot1+i,i)*C(tot2+j,j))%md;
		cout<<ans<<'\n';
	}
}
```



---

