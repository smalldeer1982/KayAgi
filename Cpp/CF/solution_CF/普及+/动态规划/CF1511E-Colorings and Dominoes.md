# Colorings and Dominoes

## 题目描述

You have a large rectangular board which is divided into $ n \times m $ cells (the board has $ n $ rows and $ m $ columns). Each cell is either white or black.

You paint each white cell either red or blue. Obviously, the number of different ways to paint them is $ 2^w $ , where $ w $ is the number of white cells.

After painting the white cells of the board, you want to place the maximum number of dominoes on it, according to the following rules:

- each domino covers two adjacent cells;
- each cell is covered by at most one domino;
- if a domino is placed horizontally (it covers two adjacent cells in one of the rows), it should cover only red cells;
- if a domino is placed vertically (it covers two adjacent cells in one of the columns), it should cover only blue cells.

Let the value of the board be the maximum number of dominoes you can place. Calculate the sum of values of the board over all $ 2^w $ possible ways to paint it. Since it can be huge, print it modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3 4
**oo
oo*o
**oo```

### 输出

```
144```

## 样例 #2

### 输入

```
3 4
**oo
oo**
**oo```

### 输出

```
48```

## 样例 #3

### 输入

```
2 2
oo
o*```

### 输出

```
4```

## 样例 #4

### 输入

```
1 4
oooo```

### 输出

```
9```

# 题解

## 作者：Mophie (赞：6)

有个比较重要但很显然的结论：

横竖不互相影响，也就是说如果一个格子能横着放，就不可能竖着放。

~~这个应该很显然吧~~

然后我们直接看横竖即可，然后计算每一条链的贡献。

设长度为 $i$ 的链的价值（指除去其他点）为 $p_{i}$，白点有 $cnt$ 个。

那么每一条长度为 $len$ 的链对答案的贡献就为 $p_{len}\times2^{cnt-len}$。

那么 $p_i$ 改怎么求呢？

我们考虑第一格的颜色，我们设 $0$ 为不能扩展，$1$ 为可以扩展。

那么若第一格为 $0$ 则就是 $p_{i-1}$

如果第一格为 $1$ 第二格为 $0$ 就是 $p_{i-2}$

如果第一格为 $1$ 第二格为 $1$ 就是 $p_{i-2}+2^{i-2}$ 

所以 $p_i=p_{i-1}+2 \times p_{i-2}+2^{i-2}$，然后就很简单了。

注意因为 $n,m$ 范围有 $3*10^5$ ，所以要用 vector。

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
const int mod=998244353;
int n,m,cnt,ans;
int p[300009];
int pown[300009];
char x[300009];
vector<int> a[300009];
signed main()
{
	n=read(),m=read();
	for(int i=0;i<n;i++)
	{
		cin>>x;
		for(int j=0;j<m;j++)
			if(x[j]=='*')
			{
				a[i].push_back(0);
			}
			else
			{
				a[i].push_back(1);cnt++;		
			}
	}	
	pown[0]=1;
	for(int i=1;i<=n*m;i++)pown[i]=pown[i-1]*2%mod;
	p[2]=1,p[3]=3;
	for(int i=4;i<=n*m;i++)p[i]=(p[i-1]+2*p[i-2]+pown[i-2])%mod;
	for(int i=0;i<n;i++)
	{
		int now=0;
		for(int j=0;j<m;j++)
			if(a[i][j]==1)now++;
			else 
			{
				if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
	//			cout<<now<<endl;
				now=0;
			}
	//	cout<<now<<endl;
		if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
	//	cout<<ans<<endl;
	}
	for(int i=0;i<m;i++)
	{
		int now=0;
		for(int j=0;j<n;j++)
			if(a[j][i]==1)now++;
			else 
			{
				if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
			//	cout<<now<<endl;
				now=0;
			}
		//cout<<now<<endl;
		if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}


```


---

## 作者：E1_de5truct0r (赞：2)

## 思路

首先，由于横着放的多米诺只能是红色，竖着放的多米诺只能是蓝色，所以我们对每个格子染色之后，相当于强制了所有的“十字路口”位置究竟是横着放还是竖着放。

那么明显就有一个结论：横着放的方案数和竖着放的方案数可以分开算贡献，是互不影响的。

那么我们只需要考虑每一个 $1 \times l$ 的连续段的方案数即可。这个可以使用递推解决，令 $f_i$ 表示 $1 \times i$ 的连续段的方案数。

假设当前多米诺骨牌要求的颜色为 1，不符合的为 0。考虑最后两位的状态：

- 00：均不符合，所以贡献是 $f_{i-2}$。

- 01：虽然有一个 1，但是明显不够填一块，所以还是 $f_{i-2}$。

- 10：这个时候可以考虑从倒数第二位开始填，贡献是 $f_{i-1}$。

- 11：可以放下这一块，然后前面的随便选都会产生大小为 1 的贡献，所以总共就是 $2^{i-2}$。

所以递推的方程为：$f_i=f_{i-1}+2 \times f_{i-2}+2^{i-2}$。

有了 $f$ 数组，我们就一行一行求出连续的 `o`，一个长度为 $x$ 的段的贡献显然就是 $f_x$ 乘上其他 `o` 随便填的贡献。假设有 $w$ 个 `o`，那么就是 $f_x \times 2^{w-x}$。每一列的贡献计算也同理。

复杂度 $O(nm)$。

## 代码

[Code & Submission](https://codeforces.com/contest/1511/submission/219434443)

---

## 作者：FutaRimeWoawaSete (赞：1)

最后才发现是把 dp 敲错了……                

我们显然不能枚举 $2 ^ w$ 种情况计数，我们考虑最后答案的组成就是骨牌的覆盖量，所以我们只要知道每种骨牌会被计算多少次就好了。          

为了避免重复计数，我们先考虑贪心处理。由于蓝色红色是互不影响的，所以我们对于所有红色的情况可以发现是问行贡献，对于所有蓝色情况可以发现是问列贡献，将其抽象成这么个子问题：             

- 对于一条长为 $x$ 的可涂色格子段，枚举所有的两个连续位置铺骨牌，问方案数之和。              

我们不难发现对于一条连续的同色格子，从左往右/上至下铺一定可以得到最多的骨牌，所以如果两个连续位置要铺骨牌，那么前面必然有偶数个连续的同色格子。             

于是我们只要 dp 算就好了，刚开始的时候因为自己 sb 了不小心写错了结果手算出来和推出来的结果不一样……索性就把 dX 的 dp 拿下来拍了下才发现写错了（不过我到现在都没看懂 dX 的 dp ，为什么要分奇偶讨论啊），这里略提一下这个 dp 。           

定义 $dp_x$ 表示当可涂色格子段长为 $x$ 时，若最后两个格子要铺骨牌时总的方案数。          

我们考虑 $x$ 和 $x - 1$ 两个位置的颜色都是固定的，那么如果 $x - 2$ 是一个异色格子的话满足条件，并且 $x - 2$ 以前的位置可以任意铺，这一段的贡献是 $2 ^ {x - 3}$ 。            

如果 $x - 2$ 是同色格子，那么 $x - 3$ 必须也是同色格子才行，这一类的情况等同于 $dp_{x - 2}$ 。              

所以最后的式子就是 $dp_x = 2 ^ {x - 3} + dp_{x - 2}$ 。                    

最后别忘了把其他地方的可涂色格子考虑进去。     

看来现在什么都不会了（    

```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 998244353;
const int Len = 3e5 + 5;
int Num;
int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b = b >> 1;
	}
	return res;
}
char s[Len];
vector<int> v[Len];
int DP[Len],n,m;
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%s",s + 1);
		for(int j = 1 ; j <= m ; j ++)
		{
			Num += (s[j] == 'o');
			v[i].push_back((s[j] == 'o'));
		}
	}
	DP[2] = DP[3] = 1;
	for(int i = 4 ; i <= Num ; i ++) DP[i] = (qpow(2 , i - 3) + DP[i - 2]) % mod;
	for(int i = 2 ; i <= Num ; i ++) DP[i] = DP[i] * qpow(2 , Num - i) % mod;
	int Ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int now = 0;
		for(int j = 0 ; j < m ; j ++) 
		{
			now = v[i][j] * now + v[i][j];
			Ans = (Ans + DP[now]) % mod;
		}
	}
	for(int j = 0 ; j < m ; j ++)
	{
		int now = 0;
		for(int i = 1 ; i <= n ; i ++) 
		{
			now = v[i][j] * now + v[i][j];
			Ans = (Ans + DP[now]) % mod;
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：丛雨 (赞：1)

## CF1511E Colorings and Dominoes

这里提供一个不同的思路



我们考虑对于每对相邻的位置，单独地计算它的贡献



先只考虑横着的情况



我们发现只有当钦定的方格两旁红色格子数同偶时才会计入答案，贡献为 1 : $(RR)\underline{(RR)}(RR)$



而异奇偶时贡献 $1\over 2$ : $(O\underline{(RR)}(RR)$ 与 $(R\underline{R)O}(RR)$ ，二者同样为最大答案



而同奇时不计入答案 $(R\underline{R)(R}R)$



所以设此对格子 $(x,y)(x,y+1)$ 左右能延伸到的最长空位(含自己)分别为 $L,R$



对于每种情况单独维护，先考虑同偶时贡献(设总空位数为 cnt ):

$\sum_{i=2k+1,i\in[1,L]}\sum_{j=2t+1,j\in[1,R]}2^{cnt-i-j-[i\not= L]-[j\not =R]}$

为什么呢？因为我们相当于枚举了这段红块的长度，而红块的两旁需要为空或者蓝色

直接操作发现是$O((nm)^3)$的，考虑优化

$$
\begin{aligned}

&\sum_{i=2k+1,i\in[1,L]}\sum_{j=2t+1,j\in[1,R]}2^{cnt-i-j-[i\not= L]-[j\not =R]}\\
=&2^{cnt}\left(\sum_{i=2k+1,i\in[1,L]}2^{-i-[i\not= L]}\right)\left(\sum_{j=2t+1,j\in[1,R]}2^{-j-[j\not =R]}\right)

\end{aligned}
$$

这里已经是 $O(nm(n+m))$ 了,因为发现遍历过程中每次只会 $++L,--R$ 以及在每一空段的开头 $O(len)$ 地处理，所以每次移动只会更改$\Sigma$内 2 项的值，可以动态维护括号内的累和

这样时间复杂度 $O(nm)$ ,这里由于赛时敲傻了，所以打的比较复杂，实际上可以非常简单的

---


```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define mod 998244353
# define inv2 499122177ll
char *str[300005];
int n,m;
ll qkpow(ll n,int m){
	ll t=1;
	for(;m;m>>=1,n=n*n%mod)
		if(m&1)t=t*n%mod;
	return t;
}ll Invp[300010];
ll Qkpow(int x){return Invp[-x];} 
int main(){
	n=read,m=read;*str=new char[m+5]();
	str[n+1]=new char[m+5]();
	for(int i=1;i<=n;++i){
		str[i]=new char[m+5]();
		scanf("%s",str[i]+1);
	}int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(str[i][j]=='o')
				++cnt;
	Invp[0]=1;
	for(int i=1;i<=n+m+5;++i)Invp[i]=Invp[i-1]*inv2%mod;
	ll ans=0,t1,t2,t3,t4,va=qkpow(2,cnt);
	for(int i=1;i<=n;++i)
		for(int j=1,l=0,r=0;j<m;++j,++l,--r)
			if(str[i][j]=='o'&&str[i][j+1]=='o'){
				if(r<=0){
					l=r=0;
					for(int k=j;str[i][k]=='o';--k)++l;
					for(int k=j+1;str[i][k]=='o';++k)++r;
					t1=0,t2=0,t3=0,t4=0;
					for(int o=1;o<=l;o+=2)
						(t1+=Qkpow(-o-(l!=o)))%=mod;
					for(int p=1;p<=r;p+=2)
						(t2+=Qkpow(-p-(r!=p)))%=mod;
					for(int o=2;o<=l;o+=2)
						(t3+=Qkpow(-o-(l!=o)))%=mod;
					for(int p=2;p<=r;p+=2)
						(t4+=Qkpow(-p-(r!=p)))%=mod;
				}else{
					int o=l-1;if(~o&1)--o;
					t1=(t1-Qkpow(-o-(l-1!=o))+Qkpow(-o-(l!=o)))%mod;
					o=l-1;if(o&1)--o;
					t3=(t3-Qkpow(-o-(l-1!=o))+Qkpow(-o-(l!=o)))%mod;
					if(l&1)t1=(t1+Qkpow(-l))%mod;
					else t3=(t3+Qkpow(-l))%mod;
					
					int p=r-1;if(~p&1)++p;
					t2=(t2-Qkpow(-p-(r+1!=p))+Qkpow(-p-(r!=p)))%mod;
					p=r-1;if(p&1)++p;
					t4=(t4-Qkpow(-p-(r+1!=p))+Qkpow(-p-(r!=p)))%mod;
					if(r&1)t4=(t4-Qkpow(-r-1))%mod;
					else t2=(t2-Qkpow(-r-1))%mod;
				}
				ans=(ans+(t1*t2+t1*t4%mod*inv2+t2*t3%mod*inv2)%mod*va)%mod;
			}
	for(int j=1;j<=m;++j)
		for(int i=1,l=0,r=0;i<n;++i,++l,--r)
			if(str[i][j]=='o'&&str[i+1][j]=='o'){
				if(r<=0){
					l=r=0;
					for(int k=i;str[k][j]=='o';--k)++l;
					for(int k=i+1;str[k][j]=='o';++k)++r;
					t1=0,t2=0,t3=0,t4=0;
					for(int o=1;o<=l;o+=2)
						(t1+=Qkpow(-o-(l!=o)))%=mod;
					for(int p=1;p<=r;p+=2)
						(t2+=Qkpow(-p-(r!=p)))%=mod;
					for(int o=2;o<=l;o+=2)
						(t3+=Qkpow(-o-(l!=o)))%=mod;
					for(int p=2;p<=r;p+=2)
						(t4+=Qkpow(-p-(r!=p)))%=mod;
				}else{
					int o=l-1;if(~o&1)--o;
					t1=(t1-Qkpow(-o-(l-1!=o))+Qkpow(-o-(l!=o)))%mod;
					o=l-1;if(o&1)--o;
					t3=(t3-Qkpow(-o-(l-1!=o))+Qkpow(-o-(l!=o)))%mod;
					if(l&1)t1=(t1+Qkpow(-l))%mod;
					else t3=(t3+Qkpow(-l))%mod;
					
					int p=r-1;if(~p&1)++p;
					t2=(t2-Qkpow(-p-(r+1!=p))+Qkpow(-p-(r!=p)))%mod;
					p=r-1;if(p&1)++p;
					t4=(t4-Qkpow(-p-(r+1!=p))+Qkpow(-p-(r!=p)))%mod;
					if(r&1)t4=(t4-Qkpow(-r-1))%mod;
					else t2=(t2-Qkpow(-r-1))%mod;
					 
				}
				ans=(ans+(t1*t2+t1*t4%mod*inv2+t2*t3%mod*inv2)%mod*va)%mod;
			}cout<<(ans+mod)%mod;
	return 0;
}

```



---

## 作者：dead_X (赞：1)

## 题意
一张 $n\times m$ 的网格图中的每个格子都为黑格或白格。

现在将每个白格都染成红色或者蓝色。

一块骨牌可以放在两个处于同一行且相邻的红色网格或两个处于同一列且相邻的蓝色网格上。

对于一种染法，定义它的价值为能放上的最多骨牌数。

求所有染法的价值总和对 $998244353$ 取模的值。

$nm\leq 3\times 10^5$。
## 思路
显然对于一个长度为 $x$ 的连续蓝/红格，我们贪心地将其从左到右或从上到下放骨牌就是最优的。

考虑计算每两个位置的贡献，显然这两个位置能放一个骨牌，当且仅当它是从左往右或从上到下的第 $2i+1,2i+2$ 个格子。

于是我们只要计算它们左边的格子的合法方案数即可。
## 代码
```cpp
// Problem: E. Colorings and Dominoes
// Contest: Codeforces - Educational Codeforces Round 107 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1511/problem/E
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
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
vector<bool> v[300003];
vector<int> v1[300003],v2[300003];
int F[300003];
#define f(x) F[x]
signed main()
{
    int n=read(),m=read();
    F[2]=F[3]=1,F[4]=2;
    for(int i=5; i<=300000; i+=2) F[i]=(F[i-2]*4+1)%p;
    for(int i=6; i<=300000; i+=2) F[i]=(F[i-2]*4+2)%p;
    for(int i=4; i<=300000; i+=2) F[i]=(F[i]+1)%p;
    int C=0;
    for(int i=0; i<n; ++i)
    {
    	scanf("%s",s+1);
    	for(int j=1; j<=m; ++j) 
    		C+=(s[j]=='o'),
    		v[i].push_back((s[j]=='o')),
    		v1[i].push_back((s[j]=='o')),
    		v2[i].push_back((s[j]=='o'));
    }
    for(int i=1; i<=C; ++i) F[i]=F[i]*qp(2,C-i)%p;
    int ans=0;
    for(int i=1; i<n; ++i) for(int j=0; j<m; ++j)
    if(v1[i][j]) v1[i][j]+=v1[i-1][j],ans=(ans+f(v1[i][j]))%p;
    for(int i=0; i<n; ++i) for(int j=1; j<m; ++j)
    if(v2[i][j]) v2[i][j]+=v2[i][j-1],ans=(ans+f(v2[i][j]))%p;
    printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：mango2011 (赞：1)

这一道题目我们暴力枚举每一种状态显然不可行。

于是我们考虑对于每一个骨牌计算贡献。

但是，当我们遇到了连续三个或者更多的白格子之后就会发现我们很难枚举每个骨牌，容易出现重复的现象。

于是，我们考虑把连续的段找出来：

比如，在第一个样例中，有三个白格子构成一列（其实列与行的贡献完全相同），于是我们要尝试求出这一列的贡献，再乘 $2^{cnt-len}$（$cnt$ 为总的白格子个数，$len$ 为当前列（行）的长度）即可得到结果。

那么这一行（列与行相同，只说行）的贡献怎么计算呢？

令 $f_{i,0}$ 为第 $i$ 格是蓝色总的能放骨牌的个数；$f_{i,1}$ 为第 $i$ 格是红色总的能放骨牌的个数。有：

初始值：$f_{1,0}=f_{1,1}=f_{0,0}=0$，考虑 $i\ge2$ 的情形：

$f_{i,0}=f_{i-1,0}+f_{i-1,1}$（这一格是蓝色，放了和没放一样）。

$f_{i,1}=f_{i-1,0}+f_{i-2,1}+f_{i-2,0}+2^{i-2}$。（考虑上一位填什么：填 $0$，则是 $f_{i-1,0}$，填 $1$，那么这里先算上贡献，再加上 $i-2$ 时的情形，最后每一种都加 $1$，共加 $2^{i-2}$）。

于是我们就把大致思路都做完了！

最后说一点细节：

+ 读入的图比较恶心，可以用二维 vector 进行存储，方便快捷。

+ 行列贡献都要计算。

+ 注意取模！

放代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5;
const long long mod=998244353;
long long P[N+10];
long long f[N+10][2];
signed main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	int n,m;
	long long ans=0,cnt=0;
	cin>>n>>m;
	vector<vector<int> >c(n+1,vector<int>(m+1));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			if(x=='o'){
				c[i][j]=1;
				cnt++;
			}
			else{
				c[i][j]=0;
			}
		}
	}
	P[0]=1;
	P[1]=2;
	for(int i=2;i<=n*m;i++){
		f[i][0]=f[i-1][0]+f[i-1][1];
		f[i][0]%=mod;
		f[i][1]=f[i-1][0]+f[i-2][1]+f[i-2][0]+P[i-2];
		f[i][1]%=mod;
		P[i]=P[i-1]*2%mod;
	}
	for(int i=1;i<=n;i++)
	{
		int now=0;
		for(int j=1;j<=m;j++){
			if(!c[i][j]){
				ans+=(f[now][0]+f[now][1])*P[cnt-now];
				ans%=mod;
				now=0;
			}
			else{
				now++;
			}
		}
		ans+=(f[now][0]+f[now][1])*P[cnt-now];
		ans%=mod;
	}
	for(int j=1;j<=m;j++){
		int now=0;
		for(int i=1;i<=n;i++){
			if(!c[i][j]){
				ans+=(f[now][0]+f[now][1])*P[cnt-now];
				ans%=mod;
				now=0;
			}
			else{
				now++;
			}
		}
		ans+=(f[now][0]+f[now][1])*P[cnt-now];
		ans%=mod; 
	} 
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：subcrip (赞：0)

不需要 DP 的做法，时间 $O(nm)$ 空间 $O(nm)$，空间主要是存储输入的矩阵以及 $2$ 的幂。

首先横着的骨牌和竖着的是不互相影响的，所以分成横竖两部分考虑。每次将“$(i,j)$ 作为某个横/竖骨牌的右/下部分出现的次数”计入答案。

显然这样做会对于连续放置的奇数个格子产生问题，例如如果有 $5$ 个连续的空格，我们只能放入 $2$ 个骨牌。所以我们钦定当遇到这种情况时总是优先往左/上的格子中放，最后空出一个右/下的格子。同时这也要求当前考虑的格子的左/上方向连续的同色格子只能是偶数个。

因此，以横着的骨牌为例，假设我们正要计算某个空格 $(i,j)$ 的贡献，并且它和它左边一共有 $l$ 个连续空格，则贡献为

$$
2^{tot-l}\sum_{j=1}^{\lfloor(l-1)/2\rfloor}2^{l-(2j+1)}=2^{tot-1}\times\dfrac14\times\dfrac{1-\left(\dfrac14\right)^{\left\lfloor\frac{l-1}2\right\rfloor}}{1-\dfrac14},
$$

其中 $tot$ 为矩阵中空格的总数量。此外，当 $l$ 是偶数时，还有一种方案是把所有 $l$ 个格子全部染成同样的颜色，它的额外贡献是 $2^{tot-l}$。这样就解决了本题。

Code:

```cpp
using mll = MLL<PRIME>;  // 同余运算类
constexpr int N = 3e5 + 10;
mll pw[N];

void prep() {  // 预处理 2 的幂
    pw[0] = 1;
    for (int i = 1; i < N; ++i) {
        pw[i] = pw[i - 1] * 2;
    }
}

void solve() {
    read(int, n, m);
    vector a(n, vector<int>(m));
    int tot = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            read(char, c);
            a[i][j] = c == 'o';
            tot += a[i][j];
        }
    }

    mll res = 0;

    // 处理横着的骨牌.
    for (int i = 0; i < n; ++i) {
        int prev = -1;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0) {
                prev = j;
            } else {
                int l = j - prev;
                res += pw[tot - 1] * (1 - 1 / pw[(l - 1) / 2 * 2]) / 3;
                if (l % 2 == 0) {
                    res += pw[tot - l];
                }
            }
        }
    }

    // 处理竖着的骨牌.
    for (int j = 0; j < m; ++j) {
        int prev = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i][j] == 0) {
                prev = i;
            } else {
                int l = i - prev;
                res += pw[tot - 1] * (1 - 1 / pw[(l - 1) / 2 * 2]) / 3;
                if (l % 2 == 0) {
                    res += pw[tot - l];
                }
            }
        }
    }

    cout << res << endl;
}
```

---

## 作者：shyyhs (赞：0)

首先连续的'.'是不相互影响的.

所以可以一次一次的计算它们的贡献...其他点对于这段连续的贡献是${2^{sum-cnt}}$,${sum}$为所有'.'的数量,${cnt}$为这段'.'的数量.

考虑这段连续的'.'的贡献,定义${f_i}$为连续'.'数量为${i}$的数量.

转移方程分几种情况考虑：

1.假如把${i}$这个点设置为不能遍历的点.那么答案+${f_{i-1}}$.

2.假如把${i}$设置为可以遍历的点,那么假如${i-1}$也可以遍历,那么前${i-1}$个点对于,这个积木的贡献为${2^{i-2}}$,然后前${i-2}$的贡献为${f_{i-2}}$.然后假如${i-1}$不能遍历,那么贡献为${f_{i-2}}$.

综上${f_i=f_{i-1}+2*f_{i-2}+2^{i-2}}$.

code:

```c
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
const int mod=998244353;
string s[N];
ll p[N],f[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	p[0]=1;
	for(int i=1;i<=n*m;i++)	p[i]=p[i-1]*2%mod;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
	}
	int sum=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='o')	sum++;
		}
	}
	int len=max(n,m);
	for(int i=2;i<=len;i++)
	{
		f[i]=(f[i-1]+2ll*f[i-2]+p[i-2])%mod;
	}
	ll ans=0;
	for(int i=0;i<n;i++)
	{
		int cnt=0;
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='o')
			{
				cnt++;
			}
			if(s[i][j]=='*'||j==m-1)
			{
				ans=(ans+f[cnt]*p[sum-cnt]%mod)%mod;
				cnt=0;
			}
		}
	}
	for(int i=0;i<m;i++)
	{
		int cnt=0;
		for(int j=0;j<n;j++)
		{
			if(s[j][i]=='o')
			{
				cnt++;
			}
			if(s[j][i]=='*'||j==n-1)
			{
				ans=(ans+f[cnt]*p[sum-cnt]%mod)%mod;
				cnt=0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

