# Fox and Perfect Sets

## 题目描述

福克斯·夏尔正在学习数论。

她认为一个非负非空集合$S$是完美的，当且仅当其中任意元素$a,b\in S$（$a$可以等于$b$），且$a\bigoplus b\in S $。其中，$\bigoplus $代表异或运算，详见https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin 。

请计算以小于等于$k$的非负整数构成的完美集合的个数。这个答案可能会很大，所以请对$1000000007\ (10^9+7)$取模。

## 说明/提示

在样例1中，这里有两个满足条件的集合：$\{0\}$和$\{0,1\}$。其中，集合$\{1\}$并不是完美集合，这是因为$1\bigoplus1=0$,但是集合$\{1\}$中并不包含元素$0$。

在样例4中，有6个满足条件的集合：$\{0\},\{0,1\},\{0,2\},\{0,3\},\{0,4\},\{0,1,2,3\}$。

翻译提供者：David_Lei

## 样例 #1

### 输入

```
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
```

### 输出

```
5
```

## 样例 #4

### 输入

```
4
```

### 输出

```
6
```

# 题解

## 作者：Rainbow_qwq (赞：9)

[CF388D Fox and Perfect Sets](https://www.luogu.com.cn/problem/CF388D)

---

题目求的就是线性基计数，要求线性基中的数异或最大值 $\le n$ 。

为了计数不重不漏，只计数满足下面条件的线性基个数：

**对于一个线性基的每一位，如果它是某个基的最高位，则只有那一个基的这一位为 1 ，反之任何最高位大于这一位的基的这一位可以为任意数**

可以数位 dp 。

设 $f(i,j,0/1)$ 表示线性基的前 $i$ 位已经填好，前 $i$ 位有 $j$ 位填了数，这 j 个基的最高位到第 i 位已确定，异或最大值 $+2^i$ 是否 $<n$ 

## $k=0$

此时不受 $n$ 的限制。

当第 $i$ 位填数，那根据上面的规则，第 $i$ 位只能填 $10000......$ ，前面所有 $j$ 个填的数第 $i$ 位也只能填 $0$ 了，只有一种情况， $f(i-1,j+1,0)+=f(i,j,0)\times 1$

当第 $i$ 位不填数，前面所有 $j$ 个填的数第 $i$ 位随便，共 $2^j$ 种， $f(i-1,j,0)+=f(i,j,0)\times 2^j$

## $k=1$

#### 1. $n$ 第 $i$ 位为 $0$

那这位就不能填数了，并且前面所有 $j$ 个填的数要有偶数个是 $1$。

设 $even=C(j,0)+C(j,2)+C(j,4)...$，$odd=C(j,1)+C(j,3)+C(j,5)...$

那么 $f(i-1,j,1)+=even\times f(i,j,1)$

#### 1. $n$ 第 $i$ 位为 $1$

如果这位填数，那么与上文一样 $f(i-1,j+1,1)+=f(i,j,1)\times 1$

如果这位不填数，那如果面所有 $j$ 个填的数要有偶数个是 $1$ ，就不卡满了，所以 $f(i-1,j,0)+=f(i,j,1)*even$

如果面所有 $j$ 个填的数要有偶数个是 $1$ ，就还是卡满了，所以 $f(i-1,j,1)+=f(i,j,1)*odd$

 $even$ 和 $odd$ 怎么求？
 
找规律发现：

$j=0,odd=0,even=1$

$j>0,odd=2^{j-1},even=2^{j-1}$

那就做完了 , 复杂度$O(30^2)$。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define mod 1000000007
inline int qpow(int a,int b=mod-2){
	int res=1;
	for(;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
	return res;
}
inline void add(int&a,int b){
	a+=b;if(a>mod)a%=mod;
	if(b<0)exit(-1);
}
int n,res,f[33][33][2];
signed main()
{
	n=read();
	f[30][0][1]=1;
	Rep(i,30,1)
		For(j,0,30)
		{
			//cout<<i<<' '<<j<<endl;
			add(f[i-1][j+1][0],f[i][j][0]);
			add(f[i-1][j][0],qpow(2,j)*f[i][j][0]%mod);
			int even=j?qpow(2,j-1):1; //C(j,0)+C(j,2)+C(j,4)...
			int odd=j?qpow(2,j-1):0; //C(j,1)+C(j,3)+C(j,5)...
			if(!(n>>(i-1)&1))
				add(f[i-1][j][1],even*f[i][j][1]%mod);
			else{
				add(f[i-1][j+1][1],f[i][j][1]);
				add(f[i-1][j][0],f[i][j][1]*even%mod);
				add(f[i-1][j][1],f[i][j][1]*odd%mod);
			} 
		}
	For(i,0,30)add(res,f[0][i][0]),add(res,f[0][i][1]);
	cout<<res;	
    return 0;
}
```

---

## 作者：David_Lei (赞：8)

设$f[i][j][k]$表示从第$i$位到最高位，已经选了$j$个基，且由基$\bigoplus$得到的最大值与$n$的差值是否在$2^i$以内（满足则$k=1$，反之$k=0$）的方案数。
### 况一：当$k=0$（异或最大值$+2^i<n$）时，考虑第$i-1$位。
- 如果该位要作为单独一个基，那么有$f[i-1][j+1][0]+=f[i][j][0]$，该位单独作基，则新增情况数为之前有的情况，视为在之前每种情况上$x$新增一个$2^{i-1} $的基，由设可保证新构成的集合异或最大值与$n$的差值在$2^{i-1}$之外，所以算在$f[i-1][j+1][0]$中。
- 如果该位不单独作基，而是放入已经拥有的j个基中，那么对于每个基，都有放与不放两种选择，共$2^j$种，$f[i-1][j][0]+=2^j*f[i][j][0]$。

### 况二：当$k=1$（异或最大值$+2^i>=n$）时，考虑第$i-1$位。
讨论$n$在第$i-1$位是否为$1$：
#### 1. $n$在第$i-1$位不为$1$，异或最大值$+2^{i-1}>n$：
- 此时最大值无法新增一个$2^{i-1}$。
- 那么，我们只能继承令第$i-1$位为偶数个$1$的情况，因为只有这样，最大值才不会改变，共$2^{j-1}$种。

#### 2. $n$在第$i-1$位为$1$，异或最大值$+2^{i-1}≤n$：
##### 如果在第$i-1$位取$0$，那么新得到的集合异或最大值$+2^{i-1}≤n$，因此应存入$f[i-1][j][0]$中，共$2^{j-1}$种。
##### 如果在第$i-1$位取$1$，那么新得到的集合异或最大值$+2^{i-1}≥n$，因此应存入$f[i-1][?][1]$中。
- 对于第$i-1$位单独作基的情况，可以有$f[i][j][1]$种，存入$f[i-1][j+1][1]$中,$f[i-1][j+1][1]+=f[i][j][1]$。
- 对于第$i-1$位不单独作基的情况，可以对每个基选择放与不放，且必须放奇数个，共$2^{j-1}$种选择，因此$f[i-1][j][1]+=2^{j-1}*f[i][j][1]$。


注意： 对于所有情况，当$j=0$,对于选择第$i-1$位为$0$的情况，$2^{j-1}$算作$1$；对于选择第$i-1$位为$1$的情况，$2^{j-1}$算作$0$,因为就算你没有选择一个基，你的异或和仍可以视作$0$。

### 代码如下：
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
#define MAXN 0x7fffffff
typedef long long LL;
const int mod=1e9+7;
using namespace std;
inline int Getint(){
	register int x=0,f=1;
	register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int ans,f[35][35][2];
void Add(int &x,int y){x=((x+y>=mod)?(x+y-mod):(x+y));}
int main(){
	int n=Getint();
	f[30][0][1]=1;
	for(int i=30;i>0;i--)
		for(int j=0;j<=30;j++){
			Add(f[i-1][j][0],(1LL<<j)*f[i][j][0]%mod);
			Add(f[i-1][j+1][0],f[i][j][0]);
			int x=j?(1<<(j-1)):1,y=j?(1<<(j-1)):0;
			if(n>>(i-1)&1){
				Add(f[i-1][j][0],(LL)x*f[i][j][1]%mod);
				Add(f[i-1][j][1],(LL)y*f[i][j][1]%mod);
				Add(f[i-1][j+1][1],f[i][j][1]);
			}else Add(f[i-1][j][1],(LL)x*f[i][j][1]%mod);
		}
	for(int i=0;i<=30;i++)
		Add(ans,f[0][i][0]),Add(ans,f[0][i][1]);
	cout<<ans;
	return 0;
}

```

---

## 作者：SDNetFriend (赞：2)

## CF388D Fox and Perfect Sets 题解

来一篇记忆化搜索的题解，顺便把做题思路给捋捋。

### 题意这里不再赘述

[CF388D Fox and Perfect Sets](https://www.luogu.com.cn/problem/CF388D)

### 朴素分析

看着题里面给出的限制，我们可以意识到，一个完美集合的所有元素一定可以表达成一组线性基及其互相异或得到的值加上个 $0$ 的形式。

那不难想到，这题我们可以从线性基计数入手来处理这题。首先有个问题，即一个完美集合可能可以由多组线性基生成，可能会重复计算。为了避免这种情况，可以使用一个方法对线性基进行重构，而我们只需要统计重构后的线性基个数即可。

了解线性基的朋友可能知道，如果想要求所有异或值的 $kth$，就需要对线性基进行重构，即要保证在排名上高位的基底的贡献要严格大于低位的基底。什么意思呢？总结起来就是**若第 $i$ 位对应的基底存在，那么其它的任意基底第 $i$ 位都应是 $0$，否则不受限制**。

以这种构造方式，查找 $kth$ 时可以直接从高位向低位贪心，用来重构的代码大概长这样：（注意不是本题的代码）

```cpp
inline void rbu(){
	for(rint i=B;i>=0;--i){
		for(rint j=i-1;j>=0;--j)
			if(_p[i]>>j&1)_p[i]^=_p[j];
		if(_p[i])p[bt++]=_p[i];
	}
}
```

那么如果进行了这样的重构，我们就可以保证，本质相同（即产生的完美集合相同）的线性基都会变成同一个线性基。并且这样重构还有一个优秀的性质：**异或最大值恰好是所有基底的异或和**，那么有了这些条件，我们就可以发现这可以转化为 DP 的形式，接下来我们分析如何 DP。

### DP 分析

我们发现从高位向低位考虑是比较方便的，那我们可以设状态 $f_{i,j,0/1}$ 表示从高到低考虑到第 $i$ 位（正着从 $0$ 开始数），大于等于 $i$ 位的基底有 $j$ 个（这个接下来会用到），当前位是否顶到了 $n$ 对应位置的上界的答案。

然后就是个比较正常的数位 DP 了。DP 过程中我们要假定低于当前位的那些位置在所有的基底里面都是 $0$，等到考虑到那里再往里面加。

至于为什么要记录这个 $j$，根据刚才重构后的线性基特点，如果让当前位没有对应的线性基，那么高位的基底对应位可以任取。那我们想要控制异或最大值当前位是 $0$ 还是 $1$，因为异或最大值是前面基底的异或和，所以相当于我们要控制前面基底对应位有奇数个还是偶数个 $1$，那假设前面有 $j>0$ 个基底，奇数个偶数个的情况均是 $2^{j-1}$ 种，就可以进行转移。

### 最后

没有解释太多的转移方程，但在代码里注释写的比较全，具体转移方程可以看代码。

这里“顶位”意思即当前位及之后是否卡住了 $n$ 的上界。

### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline lint read(){
	char c;lint f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const lint B=30,md=1e9+7;
lint f[B+5][B+5][2],n,ans,cnt[B+5],mx=-1;
inline void add(lint &x,lint y)
	{x=(x+y%md)%md;}
//从高到低考虑到第i位 已有j个基 到当前位是否顶位 
lint F(int i,int j,int k){
	if(f[i][j][k]!=-1)
		return f[i][j][k];
	if(!j&&!cnt[i]){//特判边缘情况 
		if(k)return f[i][j][k]=1;
		else return f[i][j][k]=0;
	}else if(j>max(cnt[i],mx-i))//如果i位及以后不可能拥有j个基底 
		return f[i][j][k]=0;
	lint res=0,x=j?(1ll<<j-1):0,y=j?(1ll<<j-1):1;
	//x为奇数情况对应 y为偶数情况对应 
	if(k){//当前位顶位则高位也需要顶位
		//需要在最大值上多出一个当前位
		if(n>>i&1){
			//独自成一基
			if(j)add(res,F(i+1,j-1,1));
			//没有当前位的基 高位有奇数个1
			add(res,F(i+1,j,1)*x); 
		}else//否则高位有偶数个1 
			add(res,F(i+1,j,1)*y);
	}else{//当前位不顶位
		//高位也不顶位 
		//独自成基
		if(j)add(res,F(i+1,j-1,0));
		//不独立成基 剩下位乱搞
		add(res,F(i+1,j,0)<<j);
		//高位顶位 n当前位为1且最大值该位为0
		if(n>>i&1)add(res,F(i+1,j,1)*y);
	}
	return f[i][j][k]=res;
}
int main(){
	n=read();
	memset(f,-1,sizeof f);
	for(rint i=B;i>=0;--i){
		cnt[i]=cnt[i+1]+(n>>i&1);
		if(mx==-1&&cnt[i])
			mx=i;
		//cnt记录当前位及以后有多少个1
		//mx记录最高位的1的位置 
	}
	for(rint i=0;i<=B;++i){
		add(ans,F(0,i,0));
		add(ans,F(0,i,1));
	}
	printf("%lld",ans);
	return 0;
}


```


---

## 作者：王熙文 (赞：0)

曾经有个模拟赛考到了这题，只有 _HMZ_ 切了，他说他找出规律了。但实际上这题跟找规律没啥关系，不太懂。

## 思路

首先可以发现，完美集合的定义等价于在集合中取一个子集，满足异或和在集合内。因为新的条件一定包含原来的条件，且如果满足原来的条件，设子集 $T=\{a_1,a_2,\cdots,a_k\} \subseteq S$，那么 $a_1 \oplus a_2 \in S,(a_1\oplus a_2) \oplus a_3 \in S$（因为 $a_1\oplus a_2$ 也在集合内），这样推下去就可以得到新的条件。那么这个问题转化为了有多少个集合满足大小等于 $2$ 的线性基主元个数的次方。

考虑对集合求出高斯消元解出的线性基。这个线性基满足所有主元所在的位置这一列只有它是 $1$。可以发现，能得到这个线性基的集合只有全选线性基能组成的所有数才是完美集合（否则不满足大小的条件）。而且对于一个完美集合，高斯消元解出的线性基唯一。这是因为考虑先求出任意一组线性基，那么线性基的每一个数都必须存在（如果不存在，因为不能用高位的主元，一定凑不出这一位）。又因为主元的个数唯一（线性代数相关知识），所以这个线性基是唯一的。所以完美集合和高斯消元解出的线性基是双射关系，只需要统计高斯消元解出的线性基个数即可。

因此现在将问题转化为了求有多少个高斯消元解出的线性基满足它凑出的最大值，即所有数异或起来（因为非主元位置无法控制，主元位置都可以选）小于等于 $k$。这个问题可以使用数位 dp 解决。设 $dp_{i,j,0/1}$ 表示前 $i$ 位选了 $j$ 个主元，当前异或起来的值是否顶到了 $k$ 的前 $i$ 位。如果当前位有主元，那其他主元的当前位必然为 $0$。否则其他主元的当前位可 $0$ 可 $1$。讨论当前位异或起来是 $0$ 还是 $1$ 即可转移。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int pow2[110];
int n;
int tot=0,dig[110];
int dp[110][110][2];
signed main()
{
	pow2[0]=1; for(int i=1; i<=100; ++i) pow2[i]=pow2[i-1]*2%mod;
	cin>>n;
	while(n!=0) dig[++tot]=n%2,n/=2;
	reverse(dig+1,dig+tot+1);
	dp[0][0][1]=1;
	for(int i=0; i<tot; ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			dp[i+1][j+1][0]=(dp[i+1][j+1][0]+dp[i][j][0])%mod;
			dp[i+1][j][0]=(dp[i+1][j][0]+dp[i][j][0]*pow2[j])%mod;
			if(dig[i+1]==1) dp[i+1][j+1][1]=(dp[i+1][j+1][1]+dp[i][j][1])%mod;
			dp[i+1][j][dig[i+1]==0]=(dp[i+1][j][dig[i+1]==0]+dp[i][j][1]*(j==0?1:pow2[j-1]))%mod;
			if(dig[i+1]==1) dp[i+1][j][1]=(dp[i+1][j][1]+dp[i][j][1]*(j==0?0:pow2[j-1]))%mod;
		}
	}
	int sum=0;
	for(int i=0; i<=tot; ++i) sum=(sum+dp[tot][i][0]+dp[tot][i][1])%mod;
	cout<<sum;
	return 0;
}
```

---

## 作者：bmatrix (赞：0)

题意：

>给定非负整数 $n$，定义一个自然数集合 $S$ 是好的，当且仅当 $\forall x\in S,x\le n$ 且 $\forall x,y\in S,x\oplus y\in S$，其中 $\oplus$ 表示按位异或。
>
>问好集合 $S$ 的个数，对 $10^9+7$ 取模。

约定：

- $\oplus$ 表示按位异或。
- $x[i]$ 表示二进制自然数 $x$ 从低到高第 $i$ 位，$i$ 从 $0$ 起。显然 $x[i]\in\{0,1\}$。
- $h(x)=\left\lfloor\log_2x\right\rfloor$，表示使得 $x[k]=1$ 的最大的 $k$，$h(0)$ 未定义。
- $\gg$ 表示右移运算。

将每个自然数看做一个 $t$ 维异或向量（$t=h(n)$），那么一个满足 $\forall x,y\in S,x\oplus y\in S$ 的 $S$ 就是一个线性空间，可以用一个线性基表示。

但是每个线性空间可能对应多个线性基，于是考虑对每一个线性空间选一个特殊的线性基 $B$，**它是由对这个线性空间的每个元素高斯消元得到的**，它满足性质：$\forall i\in[0,t-1]$，如果 $\exists x\in B,h(x)=i$，那么 $\forall y\in B\vee y\neq x,y[i]=0$，因为如果 $\exists y\in B, y\neq x,y[i]=1$，我们可以令 $y\leftarrow y\oplus x$ 使 $y[i]=0$ 并不破坏线性基的性质。如果 $\exists x\in B,h(x)=i$，那么我们称第 $i$ 位是“**有效**”的。这样的线性基还有一个性质，它能组成的最大数就是其中每个数的异或和，记这个数为 $m$。

考虑从高位到低位 DP，因为低位对 $m$ 的大小的影响比高位的影响更小。

设 $f(i,j)$ 表示处理到第 $i$ 位，线性基中有 $j$ 个数（有 $j$ 个有效位），总共的方案数。然后我们发现这样无法处理 $m\le n$ 的限制，于是考虑再添加一个状态 $k$，如果目前为止的 $m$ 是否满足 $m\gg i=n\gg i$，则 $k=1$，如果 $m\gg i<n\gg i$ 则 $k=0$，$m\gg i>n\gg i$ 的情况没有贡献，不用考虑。

初始状态显然 $f(t-1,0,0)=f(t-1,1,1)=1$。

当处理到第 $i$ 位时，有两种决策：令第 $i$ 位有效或无效。当 $j=0$ 时，$B=\varnothing,m=0$，所以 $f(i,0,0)=1$，$f(i,0,1)=0$。接下来分类讨论 $k$ 和 $n[i]$。

- $k=0,n[i]=0$：如果高位的 $m$ 已经小于 $n$ 了（$k=0$），那么这位是否有效都没关系，有效的贡献为 $f(i+1,j-1,0)$，如果无效则其他元素这一位可以随便填，贡献为 $f(i+1,j,0)\times2^j$。如果高位 $m=n$ 卡死（$k=1$），则不能转移到这个状态。
- $k=0,n[i]=1$：有效的贡献还是 $f(i+1,j-1,0)$。如果无效，可以和上一中一样由 $k=0$ 的状态转移，贡献为 $f(i+1,j,0)\times2^j$，还可以由 $k=1$ 的状态转移，这时要保证这一位的异或和为 $0$，也就是恰好填了偶数个 $1$，随便填的方案是 $2^j$，奇偶对称，偶数的方案就是 $2^{j-1}$，所以这部分的贡献是 $f(i+1,j,1)\times2^{j-1}$。
- $k=1,n[i]=0$：必须卡死，所以只能由 $k=1$ 的状态转移来。又因为 $n[i]=0$，所以这一位必须无效，且只能有偶数个 $1$，所以 $f(i,j,1)=f(i+1,j,1)\times2^{j-1}$。
- $k=1,n[i]=1$：同理只能由 $k=1$ 的状态转移来。有效的贡献是 $f(i+1,j-1,1)$，无效要使这一位有奇数个 $1$，因为奇偶对称所以还是 $2^{j-1}$ 种填法，因此贡献为 $f(i+1,j,1)\times2^{j-1}$。

最后的答案就是 $\sum\limits_{i=0}^{t}f(0,i,0)+f(0,i,1)$。

时间复杂度 $O(\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 31, mod = 1e9 + 7;
int n, a[N], f[N][N][2], pw[N];
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> n;
    if(n == 0) cout << "1\n", exit(0);
    pw[0] = 1;
    rep(i, 1, 30) pw[i] = pw[i - 1] * 2 % mod;
    int t = 0;
    for(; n; ++t, n >>= 1) 
        a[t] = n & 1;
    f[t - 1][0][0] = 1;
    f[t - 1][1][1] = 1;
    per(i, t - 2, 0) {
        f[i][0][0] = 1;
        rep(j, 1, t - i) {
            f[i][j][0] = (f[i + 1][j - 1][0] + f[i + 1][j][0] * pw[j]) % mod;
            if(a[i]) (f[i][j][0] += f[i + 1][j][1] * pw[j - 1]) %= mod;
            if(a[i]) f[i][j][1] = (f[i + 1][j - 1][1] + f[i + 1][j][1] * pw[j - 1]) % mod;
            else f[i][j][1] = (f[i + 1][j][1] * pw[j - 1]) % mod;
        }
    }
    int ans = 0;
    rep(i, 0, t) (ans += f[0][i][0] + f[0][i][1]) %= mod;
    cout << ans << endl;
    return 0;
}
```

---

