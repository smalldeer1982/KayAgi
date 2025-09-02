# Binary Table

## 题目描述

有一个 $n$ 行 $m$ 列的表格，每个元素都是 $0/1$ ，每次操作可以选择一行或一列，把 $0/1$ 翻转，即把 $0$ 换为 $1$ ，把 $1$ 换为 $0$ 。请问经过若干次操作后，表格中最少有多少个 $1$ 。

## 样例 #1

### 输入

```
3 4
0110
1010
0111
```

### 输出

```
2
```

# 题解

## 作者：BFLSTiger (赞：33)

这里说一个不用 FWT 的 dp 做法，虽然复杂度大一些，但是仍然能过此题。~~不想学 FWT 的懒癌晚期选手的福音。~~

我们不妨将题意转化为，我们需要至少多少次单点翻转，使得该矩阵可以通过行翻转和列翻转变为全0矩阵。

显然我们只需要通过单点修改和列翻转使得所有列都相同就好了。

由于 $n \le 20$，我们可以考虑状压，将每列压起来。

不妨设 $dp[i][j]$ 表示进行 $i$ 次互不相同的单点修改可以达到状态 $j$ 的列的个数。这里可以通过 $O(n^2*2^n)$ 的复杂度暴力进行转移。

最后答案即为：

$$\min \limits_{j=0}^{2^n-1} \sum \limits_{i=0}^n dp[i][j]*min(i,n-i)$$

之所以是乘 $min(i,n-i)$ 是因为我们不仅可以通过 $i$ 次单点修改得到 $j$，也可以通过 $n-i$ 次单点修改再进行一次列翻转得到 $j$。

时间复杂度 $O(n^2*2^n)$。

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
namespace Dango
{
	const int MAXN=25,MAXM=100005;
	string st;
	int n,m;
	int num[MAXM];
	int dp[MAXN][(1<<20)+5];
	int ans;
	int work()
	{
		ios::sync_with_stdio(false);
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>st;
			for(int j=0;j<st.length();j++)
				num[j+1]=(num[j+1]<<1)+(st[j]-'0');
		}
		for(int i=1;i<=m;i++)
			dp[0][num[i]]++;
		for(int i=0;i<n;i++)
			for(int j=n;j>=1;j--)
				for(int k=0;k<(1<<n);k++)
					dp[j][k]+=dp[j-1][k^(1<<i)];
		ans=n*m;
		for(int i=0;i<(1<<n);i++)
		{
			int res=0;
			for(int j=0;j<=n;j++)
				res+=dp[j][i]*min(j,n-j);
			ans=min(ans,res);
		}
		cout<<ans;
		return 0;
	}
}
int main()
{
	return Dango::work();
}
```

---

## 作者：AubRain (赞：28)

~~我居然做出了tourist都没有现场切的题？~~


**暴力**：$n$ 很小，所以 $2^n$ 枚举每一行翻转不翻转，然后这样的话每一列当前的状态就是已知的， $ans$ 加上每一列 $0/1$ 的较小值就行了。复杂度 $O(m*2^n)$

**正解：**

一共有 $m$ 种列状态，设 $a[i]$ 表示 $i$ 这种状态的出现次数，$b[i]$ 表示二进制数 $i$ 的 $0/1$ 较小值。

于是，当枚举的行翻转状态为 $now$ 的时候，此时 $$ans=\sum_{i=0}^{2^n} a[i]*b[i\;⊕\;now]$$

转换个形式，设 $f[i]$ 表示状态为 $i$ 时候的答案，所以
$$f[i]=\sum_{j⊕k=i}a[j]*b[k]$$

这就是异或卷积形式了，直接上模板就行了。

复杂度 $O(2^n*log(2^n))=O(n*2^n)$

~~算是FWT模板题？~~

```cpp
#include<bits/stdc++.h>
#define N 2000005
#define int long long
using namespace std;

char s[N];
int n,m,lim,ans=2e15;
int cnt[N],g[N];
int a[N],b[N];

void FWT(int *f){
	for(int d=1;d<lim;d<<=1)
		for(int i=0;i<lim;i+=(d<<1))
			for(int j=0;j<d;j++){
				int x=f[i+j],y=f[i+j+d];
				f[i+j]=x+y;f[i+j+d]=x-y;
			}
}
void IFWT(int *f){
	for(int d=1;d<lim;d<<=1)
		for(int i=0;i<lim;i+=(d<<1))
			for(int j=0;j<d;j++){
				int x=f[i+j],y=f[i+j+d];
				f[i+j]=x+y>>1;f[i+j+d]=x-y>>1;
			}
}
signed main(){
	scanf("%lld%lld",&n,&m);lim=1<<n;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		for(int j=0;j<m;j++)
			if(s[j]=='1') g[j]|=(1<<i);
	}
	for(int i=0;i<m;i++) a[g[i]]++;
	for(int i=1;i<lim;i++)
		cnt[i]=cnt[i>>1]+(i&1);
	for(int i=0;i<lim;i++)
		b[i]=min(cnt[i],n-cnt[i]);
	FWT(a);FWT(b);
	for(int i=0;i<lim;i++) a[i]*=b[i];
	IFWT(a);
	for(int i=0;i<lim;i++)
		ans=min(ans,a[i]);
	cout<<ans;
}
```



---

## 作者：Fading (赞：21)

这里好像讲得不太清楚，为什么就变成卷积了呢？

我们观察$n\leq20,$而$m$达到了惊人的$100000!!!$

所以我们考虑枚举反转了多少行。

设$X$表示翻转了哪些行$(X$是一个整数，表示压缩后的状态$)$

对于任意一列，设第$i$列的状态为$S_i$

比如有一列为
```
0
1
1
1
```
这一列的状态就是$(1110)_2=(14)_{10}$

我们枚举这一列变成了什么东西

设第$i$列经过翻转变成了状态$Y_i$

显然有$Y_i=S_i\ \texttt{xor}\ X$

然后我们发现，对于一个相同的$X$，最优答案是惟一的，而且$X$最多只有$2^{20}=1048576$个，这是可以接受的。

所以我们枚举$X$。

我们发现，由于每一列可以自由翻转，所以根据贪心原理，我们对于每一个列预先翻转到最少个$1$为止，设列状态为$i$时经过翻转这个二进制数最少有$F_i$个$1$

比如$n=3,F_3,(3)_{10}=(011)_2,$翻转后为$(100)_2$

$∴F_3=1$

然后我们想方设法凑出$F_i$

此时答案就是

$$\sum_{i=1}^mF_{X\ \texttt{xor}\ S_i}$$


这样复杂度是$O(2^nm)$的，炸的很惨

我们考虑枚举$Y_i=S_i\ \texttt{xor}\ X$


此时答案为

$$\sum_{i=1}^m\sum_{Y=0}^{2^n}[Y==S_i\ \texttt{xor}\ X]F_Y$$

两个$\sum$了有什么用呢？

考虑丢掉前面的$\sum,$设所有列中有$Q_i$列状态为$i$

所以前面的枚举就废了

$$\Leftrightarrow\sum_{S=0}^{2^n}\sum_{Y=0}^{2^n}[Y==S\ \texttt{xor}\ X]F_Y\times Q_S$$

这样枚举每一个$S$就可以了。不需要枚举$[1,m]$了

不过好像还是多了一个$\sum$，复杂度变成$O(2^{2n})$了,还是凉凉

怎么办呢？

把式子变一下

$$\Leftrightarrow\sum_{S=0}^{2^n}\sum_{Y=0}^{2^n}[Y\ \texttt{xor}\ S==S\ \texttt{xor}\ X\ \texttt{xor}\ S]F_Y\times Q_S$$

$$\Leftrightarrow\sum_{S=0}^{2^n}\sum_{Y=0}^{2^n}[Y\ \texttt{xor}\ S==X]F_Y\times Q_S$$

等等，这不就变成[$FWT$](https://www.luogu.org/problemnew/show/P4717)模板了吗？？？

如果你还没发现，继续变：

$\Leftrightarrow\sum_{Y\ \texttt{xor}\ S=X}F_Y\times Q_S$

发现设$Ans[X]=\sum_{Y\ \texttt{xor}\ S=X}F_Y\times Q_S$

$Ans$就是$F,Q$的$\texttt{xor}$卷积

所以套一下模板就好啦！

复杂度优化为了完美的$O(n2^n),n=20\ $轻松解决

简单清爽的代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();};
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();};
    return x*f; 
}
ll n,m,g[21][100201],Q[1400021],F[1400022],S[1400201];
inline void FWTxor(ll *a,int id,int lim){
    for (int len=1;len<lim;len<<=1){
        for (int i=0;i<lim;i+=len<<1){
            ll *a1=a+i,*a2=a1+len;
            for (int j=0;j<len;j++){
                ll x=a1[j],y=a2[j];
                a1[j]=(x+y)/(id==1?1:2);
                a2[j]=(x-y)/(id==1?1:2);
            }
        }
    }
}
inline int getch(){//读入单个数字
    char s=getchar();
    while (!isdigit(s)) s=getchar();
    return s-'0';
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            g[i][j]=getch();
        }
    }
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++){
            S[i]|=(1<<j-1)*g[j][i];//预处理S、
        }
    }
    for (int i=0;i<=(1<<n);i++){
        Q[i]=Q[i>>1]+(i&1);
    }
    for (int i=0;i<=(1<<n);i++){
        Q[i]=min(Q[i],n-Q[i]);//预处理Q
    }
    for (int i=1;i<=m;i++){
        F[S[i]]++;//预处理F
    }
    FWTxor(F,1,1<<n);FWTxor(Q,1,1<<n);
    for (int i=0;i<(1<<n);i++) F[i]*=Q[i];//FWT优化
    FWTxor(F,-1,1<<n);
    ll x=999999999;
    for (int i=0;i<(1<<n);i++) x=min(F[i],x);
    cout<<x<<endl;
}
```

~~突然想安利一下我那完美的$FWT$板子~~

---

## 作者：Great_Influence (赞：10)

简单的$FWT$模板题。

这道题有一个简单的做法，就是考虑枚举列状态，然后$O(m)$计算。

这样是$O(2^nm)$的，显然过不去。考虑使用优化。

设$dp[i]=min\{bit[i],bit[i\otimes (2^n-1)]\}$，其中$bit[i]$表示$i$的二进制位有多少个$1$。设$f[i]$表示所有的行中出现$i$的次数。设$ans[i]$表示列翻转状态为$i$的答案最小值。

$\because i\otimes (i\otimes j)=j$

所以存在转移:

$\displaystyle ans[i]=\sum_{j\otimes k=i}f[j]*dp[k]$

利用$FWT$优化转移即可。时间复杂度$O(2^nn)$。

代码:

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
#define Chkmin(a,b) a=a<b?a:b
#define Chkmax(a,b) a=a>b?a:b
#define pb push_back
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;
void file()
{
#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
#endif
}

const int MAXN=1e5+7;

static int n,m;

static int a[MAXN];

inline void get(char &x){for(x=getchar();!isdigit(x);x=getchar());}

static long long cnt[1<<20],dp[1<<20];

static int bit[1<<20],maxx;

inline void init()
{
	read(n);read(m);maxx=(1<<n)-1;
	static char x;
	Rep(i,1,n)Rep(j,1,m)get(x),a[j]<<=1,a[j]+=x^48;
	Rep(i,1,m)++cnt[a[i]];
	Rep(i,1,maxx)bit[i]=bit[i>>1]+(i&1);
	Rep(i,1,maxx)dp[i]=min(bit[i],bit[i^maxx]);
}

inline void FWT(long long *a,int Len)
{
	static long long t;
	for(register int i=2,ii=1;i<=Len;i<<=1,ii<<=1)
		for(register int j=0;j<Len;j+=i)
			Rep(k,0,ii-1)
			{
				t=a[j+k];
				a[j+k]+=a[j+k+ii];
				a[j+k+ii]=t-a[j+k+ii];
			}
}

inline void IFWT(long long *a,int Len)
{
	static long long t;
	for(register int i=2,ii=1;i<=Len;i<<=1,ii<<=1)
		for(register int j=0;j<Len;j+=i)
			Rep(k,0,ii-1)
			{
				t=a[j+k];
				a[j+k]+=a[j+k+ii];
				a[j+k+ii]=t-a[j+k+ii];
				a[j+k]>>=1;a[j+k+ii]>>=1;
			}
}

static int ans;

inline void solve()
{
	FWT(dp,maxx+1);FWT(cnt,maxx+1);
	Rep(i,0,maxx)dp[i]*=cnt[i];
	IFWT(dp,maxx+1);
	ans=n*m;
	Rep(i,0,maxx)Chkmin(ans,dp[i]);
	printf("%d\n",ans);
}

int main()
{
	file();
	init();
	solve();
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}


```

---

## 作者：louhao088 (赞：7)

这道题非常妙。


------------

我们首先考虑暴力，因为 $n$ 比较小，我们考虑枚举每一种行翻转情况的最小列翻转。具体的，如果在某一种行翻转已经确定的情况下，若某一列 1 个数较多则翻转，否则不翻转。 复杂度 $O(2^n m)$。


------------

我们令 $g_i$ 表示列情况为 i 时的最小 1 数，令 x 表示翻转了那些行，$a_i$ 表示每一列原本状态。则答案为 $\min_{x \in[0,2^n]} (\sum_{i=1}^m g_{x \oplus a_i})$ 。

这样并不好处理，我们考虑增加枚举量。把原式变为 $\min_{x \in[0,2^n]} (\sum_{i=1}^m \sum_{y=0}^{2^n} [y==(a_i \oplus x)]g[y])$。

我们令所有列中初始有 $b_i$ 列的状态为 $i$ 。则有  $ans= \min_{x \in[0,2^n]} (\sum_{i=0}^{2^n} \sum_{j=0}^{2^n} [j==(i \oplus x)]g[j]\times b[i])$。

两边同时异或 $i$ 得到 $ans=\min_{x \in[0,2^n]} (\sum_{i=0}^{2^n} \sum_{j=0}^{2^n} [i \oplus j==x]g[j]\times b[i])$。

我们发现后面的一坨就是标准的异或卷积，我们只要令 $f_x=\sum_{i=0}^{2^n} \sum_{j=0}^{2^n} [i \oplus j==x]g[j]\times b[i]$ 。最后枚举最小值即可。这个用 FWT 模板即可得出。


------------

复杂度 $ O(n 2^n)$ 。



------------
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit(x) (x&-x)
#define get(x) __builtin_popcount(x)
#define int long long
const int maxn=1e6+50005,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,k,a[maxn],b[maxn],c[maxn],g[maxn],ans=1e9;
char s[22][maxn];
void fwt(int *a,int f){
	for(int k=1;k<n;k=k*2)
		for(int len=k*2,i=0;i<n;i+=len)
			for(int j=0;j<k;j++){
				int x=a[i+j],y=a[i+j+k];
				a[i+j+k]=x-y;a[i+j]=x+y;
				if(!f)a[i+j]/=2,a[i+j+k]/=2;
			}
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int j=1;j<=m;j++){
		int res=0;
		for(int i=1;i<=n;i++)
			res=res+((s[i][j]-'0')<<(i-1));
		a[res]++;
	}
	k=n,n=(1<<n);
	for(int i=0;i<n;i++)b[i]=min(1ll*get(i),k-get(i));
	fwt(a,1);fwt(b,1);for(int i=0;i<n;i++)a[i]=a[i]*b[i];fwt(a,0);
	for(int i=0;i<n;i++)ans=min(ans,a[i]);cout<<ans<<endl;
 	return 0;
}

```




---

## 作者：AlanSP (赞：5)

### Description

> 有一个 n行 m 列的表格，每个元素都是 0/1 ，每次操作可以选择一行或一列，把 0/1翻转，即把 0换为 1，把 1换为 0。请问经过若干次操作后，表格中最少有多少个 1。
>
> $n\le20,m\le 10^5$

---

### Solution

n很小，我们可以考虑状压n，表示第i列的状态。

对于行的反转，我们也可以状压。

用 $0/1$ 表示当前这一行反转或未反转。

**对于一个状态为i的列，当反转情况为k时，它当前列的状态为 $i\oplus k$ 。**

可以用 $ans_k$ 记录当前反转状态为k的答案。

 $f_i$ 表是列状态为i的的行数。

那么我们如何体现每一列的反转呢？

注意到，对于一列的反转，它的 $0$ 变为 $1$，$1$  变为 $0$。

**所以只要将列状态为i的0/1个数取min，便完成了列的反转。**

记 $g_j$ 表示状态为j的0/1个数取min的结果。

那么有
$$
ans_k=\sum_if_i\times g_{i\oplus k}
$$


令 $j=i\oplus k$，则有 $k=i\oplus j$。

所以：
$$
ans_k=\sum_{i\oplus j=k}f_i\times g_j
$$
这就是异或卷积了，直接FWT就好。

---

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int N=(1<<20)+9,M=1e5+9;
int n,m,f[N],g[N],a[M],num[N];
char s[M];

inline void FWT(int *f,int flag)
{
	for(int mid=2,k=1;mid<=n;mid<<=1,k<<=1)
		for(int i=0;i<n;i+=mid)
			for(int j=0;j<k;j++)
				f[i+j]+=f[i+j+k],
				f[i+j+k]=f[i+j]-f[i+j+k]-f[i+j+k],
				f[i+j]/=flag,f[i+j+k]/=flag;
}

signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			if(s[j]=='1') 
				a[j]|=(1<<i-1);
	}
	for(int i=1;i<=m;i++) f[a[i]]++;
	for(int i=0;i<(1<<n);i++) num[i]=num[i>>1]+(i&1);
	for(int i=0;i<(1<<n);i++) g[i]=min(num[i],n-num[i]);//体现出对某一列的反转
	n=(1<<n);
	FWT(f,1),FWT(g,1); 
	for(int i=0;i<n;i++) f[i]*=g[i];
	FWT(f,2);
	int ans=1e15;
	for(int i=0;i<n;i++)
		ans=min(ans,f[i]);
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：1saunoya (赞：4)

[$\texttt{myblog}$](https://www.cnblogs.com/Isaunoya/p/12021450.html)

[CF662C Binary Table](https://www.luogu.com.cn/problem/CF662C)

一道 FWT 的板子…比较难想就是了

有一个 $n$ 行 $m$ 列的表格,每个元素都是 $0/1$,每次操作可以选择一行或一列，把 $0/1$ 翻转，即把 $0$ 换为 $1$ ，把 $1$ 换为 $0$ 。请问经过若干次操作后，表格中最少有多少个 $1$。

$1 \leq n \leq 20$
$1 \leq m \leq 10^5$

先说说 FWT 干嘛的吧

$F_k = \sum_{i \oplus j=k} a_i * b_j$

首先呢 这题其实是有个暴力做法的

（认为是 n 行 m 列的一个矩阵）
复杂度大概是 $2^n * m$

就是你暴力搞 $n$ 枚举每个状态复杂度自然是 $2^n$ 的 然后你每次搜索/状压 搞到一个地方之后 算当前列的 0/1 个数取 $min$ 因为列是可以翻转的…
暴力做法 没了 ~~但是这种做法在CF里并不给分所以没啥用~~

但是对以下的做题有大用处

你可以把最开始矩阵 $m$ 列状压 $n$ 这样就成了个二进制

然后 $a$ 数组计数
$b_i$ 数组表示 i 的 0的个数，1的个数取 min
然后如果对矩阵变换也可以表示成状态 那么就是最开始的状态 $i \oplus k$

然而可以发现

$i\oplus j=k$ 可以变成 $i\oplus k=j$

然后 FWT 还是可以用的

直接跑板子 
因为你最开始变换的是 $k$ 最后要枚举取个 $min$ 求最优解
这题没了…

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(a , b , c) for(int a = b ; a <= c ; ++ a)
#define Rep(a , b , c) for(int a = b ; a >= c ; -- a)
#define go(u) for(int i = G.head[u] , v = G.to[i] , w = G.dis[i] ; i ; v = G.to[i = G.nxt[i]] , w = G.dis[i])

using namespace std ;
using ll = long long ;
using pii = pair < int , int > ;
using vi = vector < int > ;

int read() {
  int x = 0 ; bool f = 1 ; char c = getchar() ;
  while(c < 48 || c > 57) { if(c == '-') f = 0 ; c = getchar() ; }
  while(c > 47 && c < 58) { x = (x << 1) + (x << 3) + (c & 15) ; c = getchar() ; }
  return f ? x : -x ;
}

template <class T> void print(T x , char c = '\n') {
  static char st[100] ; int stp = 0 ;
  if(! x) { putchar('0') ; }
  if(x < 0) { x = -x ; putchar('-') ; }
  while(x) { st[++ stp] = x % 10 ^ 48 ; x /= 10 ; }
  while(stp) { putchar(st[stp --]) ; } putchar(c) ;
}

template <class T> void cmax(T & x , T y) { x < y ? x = y : 0 ; }
template <class T> void cmin(T & x , T y) { x > y ? x = y : 0 ; }

const int _N = 1e6 + 10 ;
struct Group {
  int head[_N] , nxt[_N << 1] , to[_N] , dis[_N] , cnt = 1 ;
  Group () { memset(head , 0 , sizeof(head)) ; }
  void add(int u , int v , int w = 1) { nxt[++ cnt] = head[u] ; to[cnt] = v ; dis[cnt] = w ; head[u] = cnt ; }
} ;

const int N = 1 << 21 ;
typedef int arr[N] ;

int n , m ;
void FWT(int * a) {
	for(int d = 1 ; d <= n - 1 ; d <<= 1) {
		for(int i = 0 ; i <= n - 1 ; i += (d << 1))
			rep(j , 0 , d - 1) {
				int x = a[i + j] , y = a[i + j + d] ;
				a[i + j] = x + y ;
				a[i + j + d] = x - y ;
			}
	}
}
void IFWT(int * a) {
	for(int d = 1 ; d <= n - 1 ; d <<= 1) {
		for(int i = 0 ; i <= n - 1 ; i += (d << 1))
			rep(j , 0 , d - 1) {
				int x = a[i + j] , y = a[i + j + d] ;
				a[i + j] = x + y >> 1 ;
				a[i + j + d] = x - y >> 1 ;
			}
	}
}
int digit() {
	char c = getchar() ;
	while(! (c >= 48 && c <= 57)) c = getchar() ;
	if(c == 49) return 1 ;
	return 0 ;
}
arr a , b , f , g , cnt ;
signed main() {
	n = read() ; m = read() ;
	rep(i , 0 , n - 1) {
		rep(j , 0 , m - 1) {
			if(digit()) 
				g[j] |= (1 << i) ;
		}
	}
	rep(i , 0 , m - 1) a[g[i]] ++ ;
	int nn = n ;
	n = 1 << n ;
	rep(i , 1 , n - 1) cnt[i] = cnt[i >> 1] + (i & 1) ;
	rep(i , 0 , n - 1) b[i] = min(cnt[i] , nn - cnt[i]) ;
	FWT(a) ; FWT(b) ;
	rep(i , 0 , n - 1) a[i] *= b[i] ;
	IFWT(a) ;
	ll ans = 1e18 ;
	rep(i , 0 , n - 1) ans = min(ans , a[i]) ;
	print(ans) ;
	return 0 ;
}
```

---

## 作者：Soulist (赞：3)

发现$n$很小但是$m$很大

我们考虑暴力，事实上先翻转行/先翻转列对于答案答案没有影响，所以先翻转行和先翻转列等效

考虑翻转行后管列于是可以得到一个暴力做法：

先枚举行的翻转状态$s$，对于每一列，其状态为$now\oplus s$，然后考虑这一列翻转优还是不反转优，其实就是求这一列是$0$少还是$1$少

于是可以$O(m)$的检查

考虑令$g_x$表示对于状态$x$其中$0/1$较少者的数量

令$f_x$表示列状态为$x$的出现次数

则可以知道，假设翻转状态为$s$，答案为：

$$\sum_{i=0}^{2^n}f_i\times g_{i\oplus s}$$

这个好像有点棘手，但是改写一下就是：

$$\sum_{i=0}^{2^n}f_i\times\sum_{k=0}^{{2^n}} g_{k}[i\oplus s=k]$$

$$[i\oplus s=k]\to [i\oplus k=s]$$

假设$p_k$表示状态为$k$时候的答案则有：

$$p_k=\sum_{i=0}^{2^n}\sum_{j=0}^{2^n}f_ig_j[i\oplus j=k]$$

然后上个$FWT$就好了....

然后简单讲讲$FWT$，大致思路和FFT差不多，就是考虑构造一个FWT变化使得：$FWT(c)_i=FWT(a)_i\times FWT(b)_i$

这样需要分配系数，被一些神仙大佬证明，逐位考虑的$FWT$系数$c(i,j)$满足为其二进制下个位系数的$c$值乘积，于是可以按照最高位为$0/1$递归操作下去，对于$xor$卷积，其$FWT$系数为:

$$c(0,0)=1,c(0,1)=1,c(1,0)=1,c(1,1)=-1$$

然后逆$FWT$的系数也就是对上面这个系数矩阵求逆的结果...居然刚好是乘一个$\dfrac{1}{2}$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 20 + 5 ;
const int M = 1e5 + 5 ; 
const int K = 1 << 21 ; 
int n, m, s, f[K], g[K], ans[K], limit ;
char a[N][M] ; 
void FWT( int *a, int type ) {
	for( re int k = 1; k < limit; k <<= 1 ) 
	for( re int i = 0; i < limit; i += ( k << 1 ) ) 
	for( re int j = i; j < i + k; ++ j ) {
		int Nx = a[j], Ny = a[j + k] ;
		a[j] = ( Nx + Ny ) / ( type == 1 ? 1 : 2 ) ;
		a[j + k] = ( Nx - Ny ) / ( type == 1 ? 1 : 2 ) ; 
	} 
} 
int get( int x ) {
	int ans = 0 ; while( x ) {
		if( x & 1 ) ++ ans ;
		x >>= 1 ; 
	} return ans ; 
}
signed main()
{
	n = gi(), m = gi() ; int s = ( 1 << n ) - 1 ; limit = s + 1 ; 
	rep( i, 1, n ) scanf("%s", a[i] + 1 ) ;
	rep( i, 1, m ) {
		int u = 0 ; rep( j, 1, n ) u = ( u << 1 ) | ( a[j][i] - '0' ) ; 
		++ f[u] ; 
	}
	rep( i, 0, s ) g[i] = min( get(i), n - get(i) ) ;
	FWT( f, 1 ), FWT( g, 1 ) ;
	rep( i, 0, s ) ans[i] = f[i] * g[i] ;
	FWT( ans, 0 ) ; int Ans = n * m + 1 ; 
	rep( i, 0, s ) Ans = min( Ans, ans[i] ) ;
	printf("%lld\n", Ans ) ;
	return 0 ;
}
```

---

## 作者：wcyQwQ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF662C)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/02/19/CF662C%20Binary%20Table/)

$\text{FWT}$ 好题。

## 分析

首先有一个 $O(2^nm)$ 的暴力，就是枚举行被反转的状态，然后每一列取 $0$ 的数量和 $1$ 的数量的较小值再相加。形式化的，我们记 $g_i = \min(\text{popcnt}(i), \text{popcnt}(i \oplus (2^n - 1)))$，那么此时的结果就是
$$
\min_S \left\{ \sum_{i = 1}^m g_{f_i \oplus S} \right\}
$$
其中 $f_i$ 表示当前列状态压缩的结果，但是这很显然不是 $\text{FWT}$ 的形式，所以我们要变化一下，考虑有很多 $f_i$ 会重复，所以考虑开桶，记 $h_i = \sum_{j = 1}^m [f_j = i]$，这样我们的式子就变为了
$$
\min_S \left\{ \sum_{i = 0}^{2^n - 1} g_{i \oplus S} \cdot h_i \right\}
$$
因为始终有 $(i \oplus S) \oplus i = S$，所以上面的式子可以改写为
$$
\min_S \left\{ \sum_{i \oplus j = S} g_i \cdot h_j \right\}
$$
这样就是一个 $\text{FWT}$ 的形式了，直接计算即可。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); i++)
#define R(i, j, k) for(int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define int long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 21, M = 1e5 + 10;
int a[N][M], f[1 << N], g[1 << N];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int popcnt(int x) {
    int res = 0;
    while (x) x -= x & -x, res++;
    return res;
}

inline void fwtXOR(int a[], int n, int flg) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1)
        for (int i = 0; i < n; i += o)
            L(j, 0, k - 1) {
                int x = a[i + j], y = a[i + j + k];
                a[i + j] = (x + y) / flg;
                a[i + j + k] = (x - y) / flg;
            }
}

signed main() {
    int n = read(), m = read(), lim = 1 << n;
    L(i, 1, n) L(j, 1, m) {
        char c; cin >> c;
        a[i][j] = c - '0';
    }
    L(i, 1, m) {
        int s = 0;
        L(j, 1, n) s |= (1 << (j - 1)) * a[j][i];
        f[s]++;
    }
    L(i, 0, lim - 1) g[i] = min(popcnt(i), popcnt(i ^ (lim - 1)));
    fwtXOR(f, lim, 1), fwtXOR(g, lim, 1);
    L(i, 0, lim - 1) f[i] *= g[i];
    fwtXOR(f, lim, 2);
    int res = 1ll << 60;
    L(i, 0, lim - 1) res = min(res, f[i]);
    printf("%lld\n", res); 
    return 0;
}
```



---

## 作者：yijan (赞：2)

考虑把每一列当成一个不超过 $2^{n}$ 之内的数，于是进行完行的修改后相当于是每个数 xor 上了一个值 $x$ ，于是我们写成式子，这种情况答案就是
$$
\sum_{i=1}^m \min\{popcount(a_i\ xor \ x),n-popcount(a_i\ xor\ x)\}
$$
我们可以设 
$$
f(x) = \min\{popcount(x),n-popcount(x)\}
$$
于是枚举 xor 出来的值
$$
\sum_{a_i\ xor\ x = t} f(t)
$$
稍微移下项
$$
\sum_{a_i\ xor\ t = x} f(t)
$$
我们设 $t[x]$ 为 $a[i]=x$ 的 $i$ 的个数，那么上面东西就是
$$
\sum_{a\ xor\ t = x} f(t)t(a)
$$
这就是个 xor 卷积，然后取 min 就好了。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , m;
ll A[MAXN] , a[( 1 << 20 ) + 6] , f[( 1 << 20 ) + 6];
char ch[MAXN];

void FWT( ll A[] , int len ) {
	ll a1 , a2;
	for( int mid = 2 ; mid <= len ; mid <<= 1 ) 
		for( int i = 0 ; i < len ; i += mid ) 
			for( int j = 0 ; j < ( mid >> 1 ) ; ++ j ) {
				a1 = A[i + j] , a2 = A[i + ( mid >> 1 ) + j];
				A[i + j] = ( a1 + a2 ) , A[i + ( mid >> 1 ) + j] = ( a1 - a2 );
			}
}

void IFWT( ll A[] , int len ) {
	ll a1 , a2;
	for( int mid = 2 ; mid <= len ; mid <<= 1 ) 
		for( int i = 0 ; i < len ; i += mid ) 
			for( int j = 0 ; j < ( mid >> 1 ) ; ++ j ) {
				a1 = A[i + j] , a2 = A[i + ( mid >> 1 ) + j];
				A[i + j] = ( a1 + a2 ) / 2 , A[i + ( mid >> 1 ) + j] = ( a1 - a2 ) / 2;
			}
}

void solve() {
	cin >> n >> m;
	rep( i , 1 , n ) {
		scanf("%s",ch + 1);
		rep( j , 1 , m ) A[j] |= ( ch[j] - '0' << ( n - i ) );
	}
	rep( j , 1 , m ) ++ a[A[j]];
	int len = ( 1 << n );
	rep( i , 0 , len - 1 ) f[i] = min( __builtin_popcount( i ) , n - __builtin_popcount( i ) );
	FWT( a , len ) , FWT( f , len );
	rep( i , 0 , len - 1 ) a[i] = a[i] * f[i];
	IFWT( a , len );
	ll mn = 0x3f3f3f3f3f3f3f3f;
	rep( i , 0 , len - 1 ) mn = min( mn , a[i] );
	cout << mn << endl;
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}


```



---

## 作者：fanfansann (赞：2)

**CF662C Binary Table** 

**Link**

[https://codeforces.com/contest/662/problem/C](https://codeforces.com/contest/662/problem/C)


**Problem**

给你一个 $n\times m$ 的 $01$ 矩阵，每次操作：你可以挑选任意的某一行或者某一列翻转（ $0$ 变 $1$，$1$ 变 $0$ ），然后你需要使得整个矩阵的 $1$ 的数量尽可能少，问你最少数量是多少。

$n≤20,m≤10^5$

**Solution**

我们发现序列翻转实际上就是全部的数与1做异或操作。我们将矩阵按列压成二进制。 


先看数据：$n≤20,m≤10^5$

所以我们肯定先考虑 $n$

我们可以先想暴力的做法，因为最多只有 $n\le 20$ 行，也就是最多只有 $2^{20}$ 种状态，我们就先可以 $2^n$ 暴力枚举所有的状态（表示
的实际意义就是当前状态是一个二进制数 $x$  表示 $n$ 行里，每一行翻转还是不翻转），这样的话对于每一列当前的状态我们都可以
得到，我们只需要再考虑每一列翻转还是不翻转就行了。所以我们对于当前枚举到的行的状态再枚举每一列，$ans$ 加上这一列里当前状态的 $min\{num_0,num_1\}$ 





注意本文一共出现了两种状态：

一个是**行翻转状态**，代表 $n$ 行，每一行翻转为 $1$，不翻转为 $0$，状压之后是一个 $n$ 位二进制数 ，共有 $2^n$ 种。

一个是**列状态**，尽管一共有 $m\le 10^{5}$ 列，但是每列只有 $n$ 行，同样最多只有 $2^n$ 种情况。



我们用 $X_i$ 表示 $2^n$ 次枚举，枚举到的**行翻转状态**，每一列的状态实际上就是这一列的 $n$ 行表示的是啥， $X_i$ 就意味着这一列的这 $n$ 行将要进行什么样的翻转。

对于任意一列，第 $i$ 列的状态为 $S_i$ 。

则第 $i$ 列最后经翻转后实际的状态 $Y_i=S_i\oplus X_i$。

由于每一列都可以自由翻转，那么它翻转还是不翻转取决于这一列的 $min\{num_0,num_1\}$。取 $0$ 的话实际意义就是把这一行翻转成 $1$ 嘛，题目想要求的是最少数目的 $1$ 所以取 $min$ ，**这样就贪心地 $O(1)$ 完成了列的翻转** ！

因此我们设 $b[x]$ 表示列状态（n行） $x$ 的 $0/1$ 的较小值即 $min\{num_0,num_1\}$ 

设当前枚举到的行翻转状态为 $now$，则此时的答案为 


$$
ans=\sum_{i=1}^{m}b[i\oplus now]
$$
我们枚举 $2^n$ 个 $now$ 答案取最小值即可。

总时间复杂度为 $\mathcal O(m\times 2^n)$，而 $n\le 10,m\le10^5$，肯定是不可行的。

所以考虑优化：



状压枚举行状态是没什么问题， $2^{20}$ 的复杂度非常的美丽，所以考虑如何优化枚举每一列的这个操作。

发现尽管一共有 $m$ 列，每列是 $n$ 行，每列的的列状态是一个 $n$ 位二进制数，也就意味着一共就只有 $2^{n}$ 种列状态，我们设 $a[x]$ 表示列状态为 $x$ 的出现次数，$b[x]$ 表示列状态 $x$ 的 $0/1$ 的较小值即 $min\{num_0,num_1\}$ ，也就是一列的状态为 $x$ 的时候对答案的贡献。

我们同样 $2^{n}$ 枚举行的翻转状态。

假设当前的行翻转状态为 $now$ ，我们枚举所有可能出现的列状态，一共只有 $2^n$ 种，因为我们统计过了每种状态出现次数，所以如果没有这个状态，$a[i]=0$ ，这种行翻转状态 $now$  的答案为：
$$
ans=\sum_{i=0}^{2^n} a[i]\times b[i ⊕ now]
$$
有点 FWT 那味了hhh，因为 $i\oplus now=j,i\oplus j=now$，所以我们可以转一个形式：

设 $f[now]$ 表示**行翻转状态**为 $now$ 时候的答案，所以有：

$$
f[now]=\sum_{i⊕j=now}a[i]\times b[j]
$$


发现这就是 FWT 的模板，直接卷就完了。

复杂度 $O(2^n\times log_22^n)=O(n\times 2^n)$，$n=20$。完美 ~ 


**Code**
 


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
typedef int itn;
typedef unsigned long long ull;
const int N = (1 << 20) + 7, M = 1e5+ 7, mod = 1e9 + 7;
const ll INF = 4e18;
itn dcnt;
#define de(x) cout << x << " x" << endl
#define de1() cout << ++ dcnt << "ok" << endl
itn t;
int n, m;
ll a[N], b[N], f[N], S[N], num[N];
char s[N];

void XOR(ll *f, int n, int x = 1)
{
    for(int o = 2; o <= n; o <<= 1) {
        for(int i = 0, k = o >> 1; i < n; i += o) {
            for(int j = 0; j < k; ++ j) {
                ll X = f[i + j];
                ll Y = f[i + j + k];
                f[i + j] = X + Y;
                f[i + j + k] = X - Y;
                if(x == -1) {
                    f[i + j] = (X + Y) / 2;
                    f[i + j + k] = (X - Y) / 2;
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++ i) {
        scanf("%s", s + 1);
        for(int j = 1; j <= m; ++ j) {
            if(s[j] == '1')
                S[j] |= 1 << i - 1;
        }//S 是列状态
    }
    for(int i = 1; i <= m; ++ i)
        a[S[i]] ++ ;
    for(int i = 0; i < (1 << n); ++ i)
        num[i] = num[i >> 1] + (i & 1);
    for(int i = 0; i < (1 << n); ++ i)
        b[i] = min(num[i], n - num[i]);
    XOR(a, 1 << n), XOR(b, 1 << n);
    for(int i = 0; i < (1 << n); ++ i)
        f[i] = a[i] * b[i];
    XOR(f, 1 << n, -1);
    ll ans = INF;
    for(int i = 0; i < (1 << n); ++ i)
        ans = min(ans, f[i]);
    printf("%lld\n", ans);
    return 0;
}
```

附官方题解的神仙DP：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210222233148325.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210222233153108.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)




```cpp
#include<bits/stdc++.h>

using namespace std;

char s[100000];
int col[100000], dp[21][1 << 20];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf(" %s", s);

        for (int j = 0; j < m; j++) col[j] |= (s[j] - '0') << i;
    }

    for (int i = 0; i < m; i++) dp[0][col[i]]++;

    for (int k = 1; k <= n; k++)
        for (int mask = 0; mask < (1 << n); mask++) {
            int sum = k > 1 ? (k - 2 - n) * dp[k - 2][mask] : 0;
            for (int p = 0; p < n; p++) sum += dp[k - 1][mask ^ (1 << p)];

            dp[k][mask] = sum / k;
        }

    int ans = n * m;
    for (int mask = 0; mask < (1 << n); mask++) {
        int cnt = 0;
        for (int k = 0; k <= n; k++) cnt += min(k, n - k) * dp[k][mask];

        ans = min(ans, cnt);
    }

    printf("%d\\n", ans);

    return 0;
}
```


---

## 作者：nofind (赞：2)

## [题意](https://www.luogu.com.cn/problem/CF662C)

先考虑一个暴力，我们发现$n$很小，因此$2^n$枚举操作哪些行，对于每列，我们将$0/1$中最小的那个加入答案。复杂度$O(m2^n)$。

设$now$为哪些行被操作了（$0$是未操作，$1$是操作），$f_i$表示初始的$m$列中，列状态为$i$的个数，$g_i$表示状态$i$中$0/1$中个数最小为多少。  
$ans=\sum f_s\times g_{s\ xor\ now}$。

发现这是异或卷积的形式，可以$FWT$求出所有$now$的答案，取最小值即可。

注意$f,g$要开$long\ long$，因为$FWT$后相乘值会爆$int$。

code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=21;
const int maxm=100010;
const int inf=1e9;
int n,m,ans=inf;
int a[maxm],size[1<<maxn];
ll f[1<<maxn],g[1<<maxn];
char s[maxm];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
inline void FWT(ll *a,int n,int op)
{
	for(int l=1;l<(1<<n);l<<=1)
		for(int i=0;i<(1<<n);i+=l<<1)
			for(int j=0;j<l;j++)
			{
				ll x=a[i+j],y=a[i+l+j];
				if(~op)a[i+j]=x+y,a[i+l+j]=x-y;
				else a[i+j]=(x+y)>>1,a[i+l+j]=(x-y)>>1;
			}
}
signed main()
{
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)if(s[j]=='1')a[j]|=1<<i-1;
	}
	for(int i=1;i<=m;i++)f[a[i]]++;
	for(int i=0;i<(1<<n);i++)size[i]=size[i>>1]+(i&1);
	for(int i=0;i<(1<<n);i++)g[i]=min(size[i],n-size[i]);
	FWT(f,n,1);FWT(g,n,1);
	for(int i=0;i<(1<<n);i++)f[i]*=g[i];
	FWT(f,n,-1);
	for(int i=0;i<(1<<n);i++)ans=min(ans,(int)f[i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：vicky2048_2 (赞：1)

结合题意，不难发现**同一行/列进行两次操作等于啥也没干**。

也就是说，对于每一行/列，我们只需要决定要进行 $0/1$ 次操作，即对于每一行/列，我们**只需要决定是否进行翻转操作**。

看一眼数据范围：

$$n\leq 20,m\leq 10^5$$

好耶！行数小于等于 $20$，这不妥妥暴力枚举嘛。QwQ

显然我们通过暴力枚举决定每一行是否翻转就可以在 $O(2^n)$ 的时间复杂度内枚举出仅进行**翻转当前行**的操作所能的得到的所有状态。

但是**翻转当前列**的操作显然是不能直接枚举得到的。

此时我们似乎找不到解决该题的突破点了，于是我们从最质朴的解题方式：暴力，开始进行新的思考。

设第 $i$ 列的状态为 $Line_i$，第 $i$ 列的状态为 $Column_i$，每一个状态都为一个二进制数。

对于“状态”的解释，拿样例来举例子。

```
n=3，m=4

0110
1010
0111
```

我们称第 $1$ 行的状态 $Line_1$ 为 $(0110)_2$，第 $1$ 列的状态 $Column_1$ 为 $(010)_2$。

翻转一行显然会对每一列都产生影响，于是我们开始考虑进行若干次行操作会对每一列产生什么样的影响。

我们设一个 $n$ 位二进制数 $k$，$k$ 的第 $i$ 位为 $1$ 表示我们对第 $i$ 行进行翻转操作，第 $i$ 位为 $0$ 则表示我们对 $i$ 行不进行操作。

还是拿样例进行解释。

$k=(000)_2$ 表示我们对 $3$ 行都不进行翻转操作，$k=(111)_2$ 表示我们对 $3$ 行都进行翻转操作，$k=(011)_2$ 表示我们对第 $2$、$3$ 行进行翻转操作。

我们经过思考便不难发现，对于每一个原来的列状态 $Column_i$，我们在不进行任何**列翻转操作**，进行了若干次**行翻转操作**之后，当前列状态都会变为 $Column_i\text{ xor } k$。

证明也很简单，若我们对第 $j$ 行进行了翻转操作，那么对应的每一列的第 $j$ 位也会被翻转，我们可以利用异或的性质 $\text{1 xor 0=1,1 xor 1= 0}$ 对 $Column_i$ 进行翻转，每当我们翻转了第 $j$ 行的时候，每一个列状态 $Column_i$ 的二进制第 $j$ 位也需要进行翻转，此时我们将 $k_j$ 设为 $1$，即可通过异或将 $Column_i$ 的二进制第 $j$ 位翻转过来。

~~我觉得这应该是这道题最难的地方了，但是似乎其它奆佬们都认为这十分的显然阿……~~

~~是我拉低 OIer 的平均智商了。~~

接下来的部分其实只要对 $FWT_{xor}$ 有较正确且深刻的认识就不难想到了。

设经过若干操作，我们能得到的最少的 $1$ 的个数为 $ans$，对于一个行/列的二进制状态，我们设该状态 $1$ 的个数为 $bit(i)$，且在最初始的状态下，二进制列状态 $Column_i$ 的个数为 $num(Column_i)$。

暴力求解 $ans$ 的思路是十分显然的，我们只需要枚举每一行是否翻转（$k:0\sim 2^n-1$），然后枚举每一种原来的列状态（$state:0\sim 2^n-1$），暴力计算在翻转了若干行的局面下，每一种列状态最少贡献多少个 $1$，对于一种列状态 $Column_i$，它最少贡献的 $1$ 的个数为它 $0$ 的个数和 $1$ 的个数的最小值，即每一种列状态最少贡献的 $1$ 的个数为 $min\_bit(state)=\min(bit(state),n-bit(state))$。

$$ans=\left(\sum\limits_{state=0}^{2^n-1}num(state)\times min\_bit(state\text{ xor }k)\right)_{\min}$$

考虑优化式子。

发现只有一个求和符号，故似乎不可交换求和符号得到进一步推导。

但发现 $num(state)$ 和 $min\_bit(state\text{ xor }k)$ 都可以通过预处理分别存进数组 $num$ 和 $min\_bit$ 中，求和时直接调用两个数组的值即可。

这个时候我们发现什么？

求和过程中调用的两个数组下标异或值固定为 $k$！

更清晰地阐述，即在计算 $num_{state}\times min\_bit_{state\text{ xor }k}$ 时数组 $num$ 和 $min\_bit$ 的下标 $state$ 和 $state\text{ xor }k$ 异或得到的结果为 $state \text{ xor } (state\text{ xor }k)=k$。

学过异或卷积的各位或多或少都能反应过来了吧。

$$ans=\left(\sum\limits_{state=0}^{2^n-1}num_{state}\times min\_bit_{state\text{ xor }k}\right)_{\min}[0\leq k\leq 2^n-1]$$

$$=\left(\sum\limits_{i\text{ xor }j=k}num_i\times min\_bit_j\right)_{\min}[0\leq k\leq 2^n-1]$$

这啥？这不 $FWT$ 板题嘛？

不会 $FWT$ 的建议先看看这个：[P4717 【模板】快速莫比乌斯/沃尔什变换(FMT/FWT)](https://www.luogu.com.cn/problem/P4717)。

那么此时思路就很显然了吧，求异或卷积 $C=num\times min\_bit$。

那么 $C_k=\sum\limits_{i\text{ xor }j=k}num_i\times min\_bit_j$。

直接预处理出 $num$ 和 $min\_bit$，然后跑一次 $FWT$，从 $0$ 到 $2^n-1$ 枚举 $k$ 求 $C_k$ 的最小值即可。

渐进时间复杂度 $O(n2^n)$，能过。

一点小细节：

记得开 ```long long``` QwQ。

详情请见 [this](https://www.luogu.com.cn/discuss/606734)。

代码在上面的帖子里面也有了，这里就不放来占位置了。

---

## 作者：KaisuoShutong (赞：1)

CF662C Binary Table 题解。

算是一个更容易清楚的做法（？）

显然 $n$ 那维压缩成一个二进制数；

那就相当于 $m$ 个 $n$ 位二进制数（称为原数），可以翻转所有数中的某一位，也可以翻转一个数。

考虑设置一个 $n$ 位二进制数，$0$ 表示不集体翻转某一位，$1$ 表示要。称此数为模式数。

可以得到的关系是：原数 xor 模式数 = $S$，而答案即为 ${\rm popcount}(S)$。

由于我们需要对于每个模式数分别统计答案，因此变换关系式，可以得到：原数 xor $S$ = 模式数。

那么设置两个数组，$a_i$ 表示原数为 $i$ 的有多少个，$b_i={\rm popcount}(i)$。做对称差卷积即可。

得到的数组中 $i$ 位置存放模式串为 $i$ 的答案。

有个问题，这样没有处理原数翻转的情况。

重定义 $b_i=min({\rm popcount}(i),{\rm popcount}((2^n-1) \oplus i))$ 即可。

时间复杂度 $O(n\cdot 2^n)$。

---

## 作者：FutaRimeWoawaSete (赞：1)

不行啊，没见过 min 怎么化卷积，丢脸丢大了（

但是不应该成为没化出来的理由。

----------------------------------------------

首先显然的是行与列只有不翻和翻两种情况。

看到 $n$ 只有 $20$，$m$ 是 $10 ^ 5$，显然状压行的选择情况。

一种显然的想法是状压过后直接扫每个列翻还是不翻，可以做到优秀的 $O(2 ^ n \times m)$。

考虑扫 $m$ 极其难优化，发现最后答案的贡献与列的标号无关只与列的初始状态相关，用一个函数 $b(j)$ 表示列的初始状态状压后为 $j$ 的列的数量。

记 $a(i)$ 为 $i$ 状态二进制下 $0,1$ 个数少的一方的数量，$ans_x$ 表示行的状压情况为 $x$ 时最优选择的 $1$ 的数量。

尝试求出所有 $ans_x$：

$ans_x = \sum_{i = 0} ^ {2 ^ n} a(i \bigoplus x) \times b(i)$

直接将 $i \bigoplus x$ 设出来为 $j$。

$ans_x = \sum_{i = 0} ^ {2 ^ n}\sum_{j = 0} ^ {2 ^ n}[j = i \bigoplus x] \times a(j) \times b(i)$

显然 $[j = i \bigoplus x]$ 与 $[x = i \bigoplus j]$ 等价。

$ans_x = \sum_{i \bigoplus j = x} a(j)b(i)$。

使用 fwt 卷一下就行了。

时间复杂度 $O(2 ^ {20} \times 20)$。

```cpp
/*
重新失考一下。
状压 1 << 20。
我 tmd 还不信了我硬凑一个卷积出来不行吗。
After reading the solution
嘻嘻嘻我是真的没看出来这个 min 还可以这么化卷积，脑瘫了。
但是这个强制提一个卷积出来真的好难受…… 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = (1 << 20) + 5 , mod = 998244353;
int qpow(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b = b >> 1;
	}
	return res;
}
const int Div = qpow(2 , mod - 2);
int n,m;
int F[Len],G[Len],a[Len],b[Len];
void init(int *p,int *P,int N){for(int i = 0 ; i < N ; i ++) p[i] = P[i];}
void Mul(int *F,int *Q,int N){for(int i = 0 ; i < N ; i ++) F[i] = 1ll * F[i] * Q[i] % mod;}
inline void MOD(int &x){if(x > mod) x -= mod;if(x < 0) x += mod;}
void XOR(int *f,int N,int fg)
{
	int A = 0 , B = 0;
	for(int o = 2 , k = 1 ; o <= N ; o <<= 1 , k <<= 1)
		for(int i = 0 ; i < N ; i += o)
			for(int j = 0 ; j < k ; j ++)
			{
				A = f[i + j] , B = f[i + j + k];
				f[i + j] = A + B;
				f[i + j + k] = A - B;
				MOD(f[i + j]) , MOD(f[i + j + k]);
				f[i + j] = 1ll * f[i + j] * fg % mod;
				f[i + j + k] = 1ll * f[i + j + k] * fg % mod;
			}
}
//f 函数直接暴力做，g 函数也可以暴力求 
char s[Len];
int num[25][Len];
#define btp __builtin_popcount
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%s",s + 1);
		for(int j = 1 ; j <= m ; j ++) num[i][j] = s[j] - '0';
	}
	for(int i = 0 ; i < (1 << n) ; i ++) F[i] = min(n - btp(i) , btp(i));
	for(int i = 1 ; i <= m ; i ++)
	{
		int x = 0;
		for(int j = 1 ; j <= n ; j ++) x = (x << 1) + num[j][i];
		G[x] ++;
	}
	init(a , F , (1 << n)) , init(b , G , (1 << n)) , XOR(a , (1 << n) , 1) , XOR(b , (1 << n) , 1) , Mul(a , b , (1 << n)) , XOR(a , (1 << n) , Div);
	int ans = n * m;
	for(int i = 0 ; i < (1 << n) ; i ++) ans = min(ans , a[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：NashChen (赞：1)

刚学FWT就被大佬拉到这道题面前劝退。。。

不得不说，这是一道很好的思维题+FWT~~入门~~题

# 【题意】

给定一个 $0/1$ 矩阵，可以对行或列翻转。求可能得到的矩阵最少的 $1$ 的个数。

$$n\leq 20,m\leq10^5$$

# 【分析】

这道题特意给了可以承受复杂度 $O(2^n)$ 的行数数据范围，那么一定要利用上。

我们又发现一件事：当行的翻转状态确定的时候，答案是唯一的。因为每一列都是独立的，而且只有翻转或不翻转两种状态。

于是我们就开始愉快地枚举行的翻转状态啦。

---

将每一列设为一个 $n$ 位二进制数集合 $S_k$ ，将行翻转状态也设成一个 $n$ 位二进制数集合 $X$ 。

设一个状态中 $0$ 的个数和 $1$ 的个数中较小的值为

$$f(S)=\min\{cnt_0(S),cnt_1(S)\}$$

$f$ 可以通过预处理得出。

那么

$$Ans=\min\limits_{X=0}^{2^n-1} \sum\limits_{k=1}^mf(S_k\text{ xor }X)$$

复杂度 $O(m2^n)$ ，原地爆炸。

我觉得我还可以抢救一下。

于是我们考虑将式子化成形式对称的卷积来优化。

---

原理大概是这样的

$$c_k=\sum_i\sum_j[i\oplus j=k]a_ib_j$$

看起来右边要 $O(n^2)$ ，但是其实写FWT的话只用 $O(n\log n)$

我们就先考虑化成 $O(4^n)$。

---

简单地化一下形式

$$ans[X]=\sum\limits_{k=1}^mf(S_k\text{ xor }X)$$

$$Ans=\min\limits_{X=0}^{2^n-1}\{ans[X]\}$$

把$k$对列的枚举也整成对集合状态的枚举。

将每一列也看作一个状态。设 $g(S)$ 为集合 $S$ 在所有的列 $\{S_k\}$ 中出现的次数。$g$ 也是可以预处理出来的。那么

$$ans[X]=\sum\limits_{j=0}^{2^n-1}f(j\text{ xor }X)g(j)$$

$$ans[X]=\sum\limits_{j=0}^{2^n-1}\sum\limits_{i=0}^{2^n-1}[j\text{ xor }X=i]f(i)g(j)$$

不要忘了异或这种神奇的运算是支持移项的

$$ans[X]=\sum\limits_{j=0}^{2^n-1}\sum\limits_{i=0}^{2^n-1}[i\text{ xor }j=X]f(i)g(j)$$

它就是

$$ans[X]=\sum\limits_{i\text{ xor }j=X}f(i)g(j)$$

游戏结束。

[题目] CF662C 触发了 [被动] 奥义·FWT

[题目] CF662C [复杂度] 降为$O(n2^n)$

[题目] CF662C 被 [代码] 击杀

## 附：代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=100005;

int N,M,A[25][100005];
long long f[1500005],g[1500005],ans[1500005],minans=123456789012345ll;

void FWT(long long *a,long long d){
	for(int n=2;n<=(1<<N);n<<=1)
		for(int i=0;i<(1<<N);i+=n)
			for(int j=i;j<i+(n>>1);++j){
				long long t1=a[j],t2=a[j+(n>>1)];
				a[j]=t1+t2;a[j+(n>>1)]=t1-t2;
				if(d!=1) {a[j]>>=1;a[j+(n>>1)]>>=1;}
			}
	return;
}

void precalc(){
	for(int i=0;i<(1<<N);++i)
		f[i]=f[i>>1]+(i&1);
	for(int i=0;i<(1<<N);++i)
		f[i]=min(f[i],N-f[i]);
	for(int j=1;j<=M;j++){
		long long tmp=0;
		for(int i=1;i<=N;i++)
			tmp+=(A[i][j]<<(i-1));
		g[tmp]++;
	}
	return;
}

void Input(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i)
		for(int j=1;j<=M;++j){
			char c=getchar();
			if(c!='0' && c!='1') c=getchar();
			A[i][j]=c-'0';
		}
	return;
}

int main(){
	Input();
	precalc();
	FWT(f,1);FWT(g,1);
	for(int i=0;i<(1<<N);++i) ans[i]=f[i]*g[i];
	FWT(ans,-1);
	for(int i=0;i<(1<<N);++i) minans=min(minans,ans[i]);
	printf("%lld\n",minans);
	return 0;
}
```

---

## 作者：nosta (赞：1)

（排版哪儿有问题了？？）

不妨规定先翻转某些行，再翻转某些列。

设$F[x]=\min(\mathbb{pop}(x),\mathbb{pop}((2^n-1)\veebar x))$，$S_i$为第$i$列的表格状态。

枚举每一行的翻转情况$p$，此时的答案为$\sum_i F[S_i\veebar p]$。

整体答案
$$ans\min_{p=0}^{2^n-1} \sum_{i=0}^{m-1} F[S_i\veebar p]$$
$$=\min_{p=0}^{2^n-1} \sum_{q=0}^{2^n-1}F[q]\sum_{i=0}^{m-1} [S_i\veebar p=q]$$

记$T[x]=\sum_{i=0}^{m-1}[S_i=x]$，则
$$ans=\min_{p=0}^{2^n-1} \sum_{q=0}^{2^n-1}F[q]T[p\veebar q]$$
$$=\min_{p=0}^{2^n-1} \sum_{x=0}^{2^n-1}\sum_{y=0}^{2^n-1}[x\veebar y=p]F[x]T[y]$$

因此直接对$F,T$做XOR卷积，拿出结果的最小值即可。

~~### 我受够了你谷公式渲染, 求您们修修MathJax吧~~

~~~cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int L=1<<20;
const int N=1e5;

int n,m,s[N];
ll F[L],T[L]; 

void FWT_XOR(ll a[],int len) {
	for(int m=1; m<len; m<<=1)
	for(int i=0,s=m<<1; i<len; i+=s)
	for(int j=0; j<m; ++j) {
		ll x=a[i+j], y=a[i+m+j];
		a[i+j]=x+y, a[i+m+j]=x-y;
	}
}
void IFWT_XOR(ll a[],int len) {
	for(int m=1; m<len; m<<=1)
	for(int i=0,s=m<<1; i<len; i+=s)
	for(int j=0; j<m; ++j) {
		ll x=a[i+j], y=a[i+m+j];
		a[i+j]=(x+y)/2;
		a[i+m+j]=(x-y)/2;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	int len=1<<n,col;
	for(int i=0; i<n; ++i)
	for(int j=0; j<m; ++j) 
		scanf("%1d",&col),s[j]|=col<<i;
	for(int i=0; i<len; ++i) 
		F[i]=min(__builtin_popcount(i),__builtin_popcount((len-1)^i));
	for(int i=0; i<m; ++i) T[s[i]]++;
	FWT_XOR(F,len);
	FWT_XOR(T,len);
	for(int i=0; i<len; ++i) F[i]*=T[i];
	IFWT_XOR(F,len);
	printf("%lld\n",*min_element(F,F+len));
	return 0;
}

~~~

---

## 作者：Terac (赞：0)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF662C)

## 题意

给定一个 $n\times m$ 的 $01$ 矩阵，每次操作可以对一行或一列取反，问若干次操作后 $1$ 的个数的最小值。

数据范围：$1\le n\le20,1\le m\le2\times10^5$

## 题解

之前听 yls 讲过个不太类似的题，但也是根据本质不同的列的个数较小来做的，这个题就比较有思路。

容易发现取反次数不超过 $1$，操作顺序对结果不影响。

行数很小，用 $a_i$ 表示矩阵第 $i$ 列，把这一列的信息压成一个值。

有个暴力是枚举每一行是否翻转，状态 $s$ 的第 $i$ 位表示第 $i$ 行是否取反，每行取反后的 $a_i$ 就是初始的 $a_i \oplus s$，每次扫所有的列，考虑是否整列取反，即在 $a_i$ 中取 $0$ 和 $1$ 个数较小值，时间复杂度 $O(m2^n)$。

这个时间复杂度跟 $m$ 有关，不太好优化。

发现本质不同的列数只有 $O(2^n)$ 个，用 $f_i$ 表示状态为 $i$ 的列数有多少个，预处理出 $g_i$ 表示状态 $i$ 中 $0$ 和 $1$ 个数的较小值，令 $ans_i$ 表示每行取反状态为 $i$ 的答案，易得

$$ans_i=\sum\limits_{j}f_jg_{i\oplus j}$$

即

$$ans_i=\sum\limits_{j\oplus k=i}f_jg_k$$

那这个卷积形式不是跑个 FWT 就做完了？

时间复杂度为 $O(n2^n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, M = (1 << 20) + 10;
int n, m, a[N];
ll f[M], g[M];
char s[N];
void FWT(ll *f, int T) {
    for(int mid = 1; mid < n; mid <<= 1)
        for(int i = 0; i < n; i += mid << 1)
            for(int j = 0; j < mid; j++) {
                ll x = f[i + j], y = f[i + j + mid];
                f[i + j] = (x + y) / T;
                f[i + j + mid] = (x - y) / T;   
            }
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", s + 1);
        for(int j = 1; j <= m; j++)
        	if(s[j] - '0') a[j] |= 1 << i;
    }
    for(int i = 1; i <= m; i++)
        f[a[i]]++;
    for(int i = 0, w; i < 1 << n; i++) {
        w = __builtin_popcount(i);
        g[i] = min(w, n - w);
    }
    n = 1 << n;
    FWT(f, 1), FWT(g, 1);
    for(int i = 0; i < n; i++)
        f[i] *= g[i];
    FWT(f, 2);
    ll ans = 1e9;
    for(int i = 0; i < n; i++)
        ans = min(ans, f[i]);
    printf("%lld", ans);
}
```


---

## 作者：Alex_Wei (赞：0)

> [CF662C Binary Table](https://www.luogu.com.cn/problem/CF662C)

当每行翻转的状态确定时，每列是否翻转独立。令第 $i$ 列等于 $1$ 的行集合为 $T_i$，枚举翻转行集合 $S$，答案即 $\min\limits_{S} \sum\limits_{i = 1} ^ m \min(|S\oplus T_i|, n - |S\oplus T_i|)$。

枚举 $P = S\oplus T_i$，得 $\min\limits_{S}\sum\limits_P f(P\oplus S) \cdot \min(|P|, n - |P|)$，其中 $f(T)$ 表示等于 $T$ 的 $T_i$ 数量。

令 $g(P)$ 表示 $\min(|P|, n - |P|)$，因 $S = P\oplus T$，故令 $h$ 为 $f, g$ 的异或卷积，则答案即 $\min\limits_S h(S)$。

时间复杂度 $\mathcal{O}(n 2 ^ n)$，[代码](https://codeforces.com/contest/662/submission/163757130)。

另一种做法（笔者做法）：我们只关心 $\mathrm{popcount}$ 而非具体数值，因此考虑设计类似异或卷积的分治做法。设 $f_{i, j, k}$ 表示考虑完低 $i$ 位，其余位与 $j$ 相同，且使得与 $j$ 异或起来在低 $i$ 位 $\mathrm{popcount} = k$ 的 $T$ 的数量。

形式化地，令 $L_k(S)$ 表示 $S$ 的低 $k$ 位，$H_k(S)$ 表示 $S$ 的高 $k$ 位即 $S\backslash L_{n - k}(S)$，则 
$$
f_{i, j, k} = \sum\limits_{p = 1} ^ m [H_{n - i}(T_p) = H_{n - i}(j) \land |L_i(T_p \oplus j)| = k]
$$
转移类似 FWT 枚举 $f_{i, j}$ 和 $f_{i, j + 2 ^ i}$，将其视为关于 $k$ 这一维的多项式 $f_{i, j, k} = [x ^ k]$。因为不同的位异或起来才等于 $1$，所以 $f_{i + 1, j} = f_{i, j} + f_{i, j + 2 ^ i} \times x$，同理 $f_{i + 1, j + 2 ^ i} = f_{i, j} \times x + f_{i, j + 2 ^ i}$。

显然，答案为 $\min\limits_{j = 0} ^ {2 ^ n - 1} \sum\limits_{p = 0} ^ n f_{n, j, p} \times \min(p, n - |p|)$，时间复杂度 $\mathcal{O}(n ^ 2 2 ^ n)$，[代码](https://codeforces.com/contest/662/submission/157274326)。

---

## 作者：Demoe (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF662C)

## 题意

- $n$ 行 $m$ 列的 $01$ 矩阵，可以任意对行/列操作，使其全部元素变为另一取值。

- 问最后 $1$ 的个数最小值。

## 题解

题目有一个很瞩目的条件 $1\le n\le 20$。

一看就知道最后复杂度肯定有 $O(2^n)$ 嘛。

我们朝着 $O(2^n)$ 的方向想。

$2^n$ 是啥呢？

行翻转二进制压缩后状态总数是 $2^n$。

列状态二进制压缩后可以用 $2^n$ 的数表示，总数也是 $2^n$。

你看有行有列了。~~有内味了。~~

---

我们先从行的角度出发。

枚举行翻转状态。

对每一列，我们预先求好每列压缩后状态，异或上行翻转状态，然后数一数 $1$ 的个数。

这样时间复杂度 $O(nm2^n)$。炸飞了呜呜。

考虑到列状态一共只有 $2^n$ 个，我们可以预先求好所有状态 $1$ 的个数（也可以直接求 $0$、$1$ 较少的个数啦），这样预处理 $O(n2^n)$，后面只有 $O(m2^n)$ 啦。

~~还是炸飞了。~~

---

呜呜看看还有什么性质能用的。

这个行的大概是拓展不了了。

我们考虑优化列。

我们发现之前是这么说的。

>对每一列，我们预先求好每列压缩后状态，**异或**上行翻转状态，然后数一数 $1$ 的个数。

令行翻转状态为 $S$，列初始状态为 $Q_i$，$b_Q$ 表示列状态为 $Q$ 时该列 $1$ 的最少个数。

对于每个 $S$，我们的答案即为 $\sum\limits^m_{i=1}b_{Q_i \texttt{ xor } S}$。

我们考虑桶计数一下，用 $a_Q$ 表示列初始状态为 $Q$ 的列数。

答案即为 $\sum\limits^{2^n-1}_{i=0}a_{i}\times b_{i \texttt{ xor } S}$。

这个 $i \texttt{ xor } S$ 在坐标上很难受，我们令 $j = i \texttt{ xor } S$。

答案可写为 $\sum\limits^{2^n-1}_{i=0}a_{i}\times b_{j}$。

看看，有没有想到什么。

FWT 的异或式是 $c_i=\sum\limits_{j \texttt{ xor } k=i}a_j\times b_k$，也可以改成范围即 $c_i=\sum\limits^{2^n-1}_{j=0}\sum\limits^{2^n-1}_{k=0}[j \texttt{ xor } k=i]a_j\times b_k$。

我们再来看看我们这题答案 $\sum\limits^{2^n-1}_{i=0}a_{i}\times b_{j}$，再看看 FWT 的式子。

发现 $\sum\limits^{2^n-1}_{i=0}a_{i}\times b_{j}=\sum\limits^{2^n-1}_{i=0}\sum\limits^{2^n-1}_{j=0}[j=i \texttt{ xor } S]a_{i}\times b_{j}$。

~~好像差了点啥，那个条件好像不太对。~~

若 $j=i \texttt{ xor } S$，则 $j \texttt{ xor } i=i \texttt{ xor } S \texttt{ xor } i$，即 $S=i \texttt{ xor } j$。

答案即为 $\sum\limits^{2^n-1}_{i=0}\sum\limits^{2^n-1}_{j=0}[S=i \texttt{ xor } j]a_{i}\times b_{j}$。

FWT 后对每个 $S$ 的答案取最小值即可。

时间复杂度 $O(n2^n+nm)$。

## 代码

```cpp
const int N=(1<<20)+5,M=1e5+5,inv2=499122177;
ll n,m,a[N],b[N],g,c[M],ans=2e7+5;
char s[21][M];

inline void XOR(ll *f,int op){
	for(re s=2,k=1;s<=n;s<<=1,k<<=1)
		for(re i=0;i<n;i+=s)
			for(re j=0;j<k;++j){
				ll x=f[i+j],y=f[i+j+k];
				f[i+j]=x+y,f[i+j+k]=x-y;
				if(op==0) f[i+j]=f[i+j]/2,f[i+j+k]=f[i+j+k]/2;
			}
}// FWT op=1 IFWT op=inv

inline void mul(ll *f,ll *g){
	for(re i=0;i<n;++i) f[i]=f[i]*g[i];
}

inline void print(int *f){
	for(re i=0;i<n;++i) wr(f[i]),putchar(' ');puts("");
}

// ---------- FWT & IFWT ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);
	for(re i=0;i<n;++i) scanf("%s",s[i]);
	for(re j=0;j<m;++j)
		for(re i=0;i<n;++i)
			if(s[i][j]=='1') c[j]|=(1<<i);
	for(re i=0;i<m;++i) ++a[c[i]];
	for(re i=0;i<(1<<n);++i) b[i]=b[i>>1]+(i&1);
	for(re i=0;i<(1<<n);++i) b[i]=min(b[i],n-b[i]);
	n=(1<<n);
	XOR(a,1);XOR(b,1);mul(a,b);XOR(a,0);
	for(re i=0;i<n;++i) ans=min(ans,a[i]);
	wr(ans);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：duyi (赞：0)

# CF663E Binary Table

## 本题题解

因为 $n$ 很小，考虑枚举每行的状态（操作或不操作），把它们压缩成一个二进制数，记为 $x$。同时，我们把输入的矩阵的每一列也压缩起来，记为 $s_{1\dots m}$。

假如枚举了 $x$，那么每列的选择互不相关，于是可以贪心计算出答案。具体来说：
$$
\text{ans}(x) = \sum_{i = 1}^{m} \min(\text{bitcnt}(x\operatorname{xor}s_i), n - \text{bitcnt}(x\operatorname{xor}s_i))
$$
对于任意二进制数 $t$，设 $g(t) = \min(\text{bitcnt}(t), n - \text{bitcnt}(t))$。则：
$$
\text{ans}(x) = \sum_{i = 1}^{m} g(x\operatorname{xor}s_i)
$$
注意到 $s_i$ 和 $x$ 一样，取值只有 $2^n$ 种。于是**把每个值的出现次数用一个桶记下来**。具体来说，我们定义：$f(t) = \sum_{i = 1}^{m}[s_i = t]$。则：
$$
\text{ans}(x) = \sum_{i = 0}^{2^n - 1}f(i)\times g(x\operatorname{xor}i)
$$
一个重要的发现是，相乘的 $f, g$ 的下标，**异或和全部为一个定值** $x$。这其实就是 fwt 中的 $\operatorname{xor}$ 卷积。

因此，我们对 $f, g$ 这两个数组做 fwt - xor 卷积，得到的结果就是 $\text{ans}$ 数组了。

时间复杂度 $\mathcal{O}(mn + 2^nn)$。

## 参考代码

```cpp
// problem: CF663E
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 21;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 21;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

const int MAXN = 20, MAXM = 1e5;
const int INF = 1e9;
const int MOD = 1e9 + 7;
inline int mod1(int x) { return x < MOD ? x : x - MOD; }
inline int mod2(int x) { return x < 0 ? x + MOD : x; }
inline void add(int &x, int y) { x = mod1(x + y); }
inline void sub(int &x, int y) { x = mod2(x - y); }
inline int pow_mod(int x, int i) {
	int y = 1;
	while (i) {
		if (i & 1) y = (ll)y * x % MOD;
		x = (ll)x * x % MOD;
		i >>= 1;
	}
	return y;
}

int inv_2;

int n, m;
char s[MAXN + 5][MAXM + 5];

int bitcnt[1 << MAXN];
int f[1 << MAXN], g[1 << MAXN];

void fwt_xor(int* a, int n, int flag) {
	for (int i = 1; i < n; i <<= 1) {
		for (int j = 0; j < n; j += (i << 1)) {
			for (int k = 0; k < i; ++k) {
				int x = a[j + k], y = a[i + j + k];
				if (flag == 1) {
					a[j + k] = mod1(x + y);
					a[i + j + k] = mod2(x - y);
				} else {
					a[j + k] = (ll)mod1(x + y) * inv_2 % MOD;
					a[i + j + k] = (ll)mod2(x - y) * inv_2 % MOD;
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> (s[i] + 1);
	}
	for (int i = 1; i < (1 << n); ++i) {
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);
		g[i] = min(bitcnt[i], n - bitcnt[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int mask = 0;
		for (int j = 1; j <= n; ++j) {
			if (s[j][i] == '1') {
				mask |= (1 << (j - 1));
			}
		}
		f[mask]++;
	}
	
	inv_2 = pow_mod(2, MOD - 2);
	
	fwt_xor(f, 1 << n, 1);
	fwt_xor(g, 1 << n, 1);
	for (int i = 0; i < (1 << n); ++i) {
		f[i] = (ll)f[i] * g[i] % MOD;
	}
	fwt_xor(f, 1 << n, -1);
	
	int ans = INF;
	for (int i = 0; i < (1 << n); ++i) {
		ckmin(ans, f[i]);
	}
	cout << ans << endl;
	return 0;
}
```





---

## 作者：lahlah (赞：0)

[CF662C Binary Table](https://www.luogu.org/problem/CF662C)

FWT~~入门~~ 好题

~~据说tourist都没有当场做出来~~

注意到$n$很小

所以这题一个朴素的暴力就是 $2^n$枚举行是否翻转

然后每一列对应一个整数 

把这个整数和枚举翻转的数异或一下就是行翻转后的状态

然后考虑列是否翻转

即看0的个数多还是1的个数多

设$f[i]$表示列对应的整数位$i$的列的个数

设$g[i]$表示$min(cnt_0, cnt_1)$即0，1出现个数少的那一个

然后可以很容易的发现

$ans[i] = \sum g[i⊕j] * f[j]$

明显的一个卷积形式

可以变为

$ans[k] = \sum_{i⊕j = k} g[i] * f[j]$

然后就可以愉快的FWT了

code:
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define ll long long
using namespace std;
const int N = (1 << 20) + 5;

void fwt_xor(ll *a, int len, int opt){//板子
	for(int i = 2; i <= len; i <<= 1)
		for(int p = i >> 1, j = 0; j + i <= len; j += i)
			for(int k = j; k < j + p; k ++){
				int X = a[k], Y = a[k + p];
				a[k] = (X + Y) % mod, a[k + p] = (X - Y + mod) % mod;
				if(opt == -1) a[k] = a[k] * 499122177 % mod, a[k + p] = a[k + p] * 499122177 % mod;
			}
				
}

int n, m;
ll a[21][N], b[N], f[N], g[N];
int main(){
	scanf("%d%d", &n, &m);
	
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++){
			char c;
			scanf(" %c", &c);
			a[i][j] = c - '0';//输入
		}
	for(int i = 0; i < (1 << n); i ++) g[i] = __builtin_popcount(i), g[i] = min(g[i], n - g[i]);//处理g
	for(int i = 1; i <= m; i ++){
		int t = 0;
		for(int j = 1; j <= n; j ++) t = t * 2 + a[j][i];//把这一列转换为一个整数
		f[t] ++;//统计个数
	}
	int len = (1 << n);
	fwt_xor(f, len, 1), fwt_xor(g, len, 1);//FWT
	for(int i = 0; i < len; i ++) f[i] = f[i] * g[i] % mod;
	fwt_xor(f, len, -1);
	ll ans = n * m + 1;
	for(int i = 0; i < len; i ++) ans = min(ans, f[i]);
	printf("%lld", ans);	
	return 0;
}

```

---

