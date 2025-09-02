# [USACO19JAN] Cow Poetry G

## 题目背景

USACO19 年一月金组第一题

## 题目描述

不为 Farmer John 所知的是，Bessie 还热衷于资助艺术创作！最近，她开始研究许多伟大的诗人们，而现在，她想要尝试创作一些属于自己的诗歌了。
Bessie 认识 $N$（$1 \leq N \leq 5000$）个单词，她想要将她们写进她的诗。Bessie 已经计算了她认识的每个单词的长度，以音节为单位，并且她将这些单词划分成了不同的“韵部”。每个单词仅与属于同一韵部的其他单词押韵。

Bessie 的每首诗由 $M$ 行组成（$1 \leq M \leq 10^5$），每一行必须由 $K$（$1 \leq K \leq 5000$）个音节构成。此外，Bessie 的诗必须遵循某个指定的押韵模式。

Bessie 想要知道她可以写出多少首符合限制条件的不同的诗。

## 说明/提示

在这个例子中，Bessie 认识三个单词。前两个单词押韵，长度分别为三个音节和四个音节，最后一个单词长度为三个音节，不与其他单词押韵。她想要写一首三行的诗，每行包含十个音节，并且第一行和最后一行押韵。共有 $960$ 首这样的诗。以下是一首满足要求的诗（其中 $1,2,3$ 分别代表第一个、第二个、第三个单词）：$\text{121 123 321}$。

## 样例 #1

### 输入

```
3 3 10
3 1
4 1
3 2
A
B
A```

### 输出

```
960```

# 题解

## 作者：Henry_he (赞：18)

### 简单的计数题
有题意得知，每一行都只关心最后一个词的韵部

所以前面的词可以随便乱填（好诗~）

规定$ f\left[ j \right] $表示音节填了$ j $ 位的方案总数

```cpp
for(int j=0;j<=k;j++)
	for(int i=1;i<=n;i++)
		f[j+s[i]]+=f[j];
```
(直接复制可能会有一些小问题~)

然后再统计最后一个词的韵部的方案数

只要枚举单词给它空个位置就好啦

```cpp
g[c[i]]+=f[k-s[i]]
```

然后就可以啦~

最后把每个韵部要求统计的行数都就求出来就好了

丑陋的代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 5005
using namespace std;
typedef long long LL;
int n,m,k;
LL s[N],c[N];
LL f[N],g[N];
LL nd[30];
const LL mod=1000000007;
LL ksm(LL b,LL k)
{
	if(k==0) return 1;
	if(k==1) return b%mod;
	LL q=ksm(b,k>>1);
	if(k&1) return q*q%mod*b%mod;
	else return q*q%mod;
}
bool cmp(LL x,LL y)
{
	return x>y;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&s[i],&c[i]);
	f[0]=1;
	for(int j=0;j<=k;j++)
	if(f[j]) 
		for(int i=1;i<=n;i++)
			if(j+s[i]<=k)	f[j+s[i]]=(f[j+s[i]]+f[j])%mod;
	for(int i=1;i<=n;i++)
		g[c[i]]=(g[c[i]]+f[k-s[i]])%mod;
	while(m--)
	{
		char s[5];
		scanf("%s",s);
		nd[s[0]-'A']++;
	}
	sort(nd,nd+26,cmp);
	sort(g+1,g+n+1,cmp);
	LL ans=1;
	for(int i=0;i<26&&nd[i];i++)
	{
		LL x=nd[i],sum=0;
		for(int j=1;j<=n&&g[j];j++)
			sum=(sum+ksm(g[j],x))%mod;
		ans=ans*sum%mod; 	
	}
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：CYJian (赞：16)

正解还是挺简单的。。

可以发现，两句诗之间相互影响的只有最后一个词语的韵律。这样的话我们就可以考虑设置状态$f[i][j]$表示长度为$i$句子，且最后一个词语的韵律为$j$的方案数。

设总韵律数为$S$，第$i$个单词的韵律为$y[i]$，长度为$l[i]$。

转移也非常简单，可以考虑枚举长度$i$，最后一个单词为$j$，上一个单词的韵律为$k$，则有：

$$f[i][Y]=\sum_{y[j]=Y}\sum_{k=1}^S f[i-l[j]][k]$$

发现是$O(N^2K)$，不能接受。考虑优化：

我们设：

$$g[i]=\sum_{k=1}^{S} f[i][k]$$

那么就有：

$$f[i][Y]=\sum_{y[j]=Y}g[i-l[j]]$$

复杂度$O(NK)$

这就可以了。。

然后考虑句子的做法。

由于相同的字母之间只有韵律相同的限制，所以我们枚举韵律后直接这样算就好了：

$$Ans[i]=\sum_{j=1}^{S} (f[k][j])^{cnt[i]}$$

最后把所有出现过的字母的$Ans[i]$乘起来就好了。

代码：

```
#include <bits/stdc++.h>

using namespace std;

#define reg register
#define ge getchar()
#define Re read()
#define FI "poetry.in"
#define FO "poetry.out"
#define MAXN 5000
#define mod 1000000007

inline int read() {
	reg int x = 0, ch;
	while(!isdigit(ch = ge)) ;
	while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = ge;
	return x;
}

int f[MAXN + 1][MAXN + 1];
int s[MAXN + 1];
int l[MAXN + 1];
int y[MAXN + 1];
int cnt[26];

inline int quick_pow(reg int x, reg int k) {
	reg int s = 1;
	while(k) {
		if(k & 1) s = (1LL * s * x) % mod;
		x = (1LL * x * x) % mod;
		k >>= 1;
	}
	return s;
}

int main() {
	freopen(FI, "r", stdin);
	freopen(FO, "w", stdout);
	reg int n = Re;
	reg int m = Re;
	reg int k = Re;
	s[0] = 1;
	for(reg int i = 1; i <= n; i++) l[i] = Re, y[i] = Re;
	for(reg int i = 1; i <= k; i++) {
		for(reg int j = 1; j <= n; j++) {
			if(i >= l[j]) {
				f[i][y[j]] = (f[i][y[j]] + s[i - l[j]]) % mod;
				s[i] = (s[i] + s[i - l[j]]) % mod;
			}
		}
	}
	for(reg int i = 1; i <= m; i++) {
		reg char ch;
		while(!isalpha(ch = ge)) ;
		cnt[ch - 'A']++;
	}
	reg int res = 1;
	for(reg int i = 0; i < 26; i++) {
		if(!cnt[i]) continue;
		reg int ans = 0;
		for(reg int j = 1; j <= n; j++)
			if(f[k][j])
				ans = (ans + quick_pow(f[k][j], cnt[i])) % mod;
		res = 1LL * res * ans % mod;
	}
	cout << res << endl;
	return 0;
}
```

Upd: 公式炸了, 修复完毕

---

## 作者：IAWNA (赞：7)

一道教练上课的题目。

这题同机房的大佬[bye_wjx](https://www.luogu.com.cn/user/575994)和[m256i](https://www.luogu.com.cn/user/370281)都发了题解，

~~不过wjx的代码没开long long被教练的数据卡掉了~~

题意很清楚，就不多说了。

其实这题就是一个背包问题。

首先我们先考虑一行诗的情况。

设 $dp[i][j]$ 为 $i$ 个音节，结尾韵部为 $j$ 的方案数，

可以得到状态转移方程：

$$dp[i][j]=\sum\limits_{y[k]=j}\sum\limits_{l=1}^{mx} dp[i-len[k]][l]$$

其中 $mx$ 是最大韵脚，$len[i]$ 为第 $i$ 个单词的音节数，$y[i]$ 为第 $i$ 个单词的韵脚。

可是这样我们还得从 $1$ 到 $k$ 枚举 $i$，复杂度为 $O(n^2k)$，显然需要优化。

观察发现，$dp[i][j]$ 只与上一阶段的长度的方案数有关，与其结尾韵脚无关，

于是我们可以设 $fdp[i]$ 表示长度为 $i$ 的方案数，

状态转移方程为：

$$fdp[i]=\sum\limits_{j=1}^nfdp[i-l[j]]$$

$$dp[i][j]=\sum\limits_{y[k]=j}fdp[i-len[k]]$$

时间复杂度 $O(n^2)$。

然后我们再考虑整首诗的情况，

把每一个押韵模式出现的次数用一个桶记录下来，（比如为 $t$）

则第 $i$ 个模式压第 $j$ 个韵脚的方案数为：

$${dp[k][j]}^{t[i]}$$

则第 $i$ 个模式的方案数为：

$$\sum\limits_{j=1}^{mx}{dp[k][j]}^{t[i]}$$

然后根据乘法原理，把所有模式的方案数都乘起来就行啦~

最后答案为：

$$\prod\limits_{i=1}^{26}\sum\limits_{j=1}^{mx}{dp[k][j]}^{t[i]}$$

不要忘了用快速幂优化噢~

# 代码

```cpp
#include<cstdio>
#include<algorithm>
const long long Mod=1000000007;
inline long long qpower(int a,int b)
{
	long long res=1,p=a;
	while(b)
	{
		if(b&1)res=res*p%Mod;
		b>>=1;p=p*p%Mod;
	}
	return res;
}
int dp[5005][5005];
int fdp[5005];
int len[5005],y[5005];
int t[26],mx;
char c;
inline void in(int j)
{
	scanf("%d%d",&len[j],&y[j]);
	mx=std::max(mx,y[j]);
}
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)in(i);
	fdp[0]=1;
	for(int i=1;i<=k;++i)
	{
		for(int j=1;j<=n;++j)
		{
			fdp[i]=(fdp[i]+fdp[i-len[j]])%Mod;
			dp[i][y[j]]=(dp[i][y[j]]+fdp[i-len[j]])%Mod;
		}
	}
	for(int i=1;i<=m;++i)
	{
		getchar();
		c=getchar();
		++t[c-'A'];
	}
	long long ans=1,nans;
	for(int i=0;i<26;++i)
	if(t[i])
	{
		nans=0;
		for(int j=1;j<=mx;++j)
		if(dp[k][j])
		nans=(nans+qpower(dp[k][j],t[i]))%Mod;
		ans=ans*nans%Mod;
	}
	printf("%lld",ans);
}
```

---

## 作者：trsins (赞：4)

非常 naive 的完全背包求方案数的问题。

这题的转移太过明显，而我的做法人菜常数大，所以有点 naive。

由于一个单词的韵脚只决定最后一个单词，所以倘若你有一个转移，如果你是将韵脚与方案数为参数的方程，那么它可以非常好的从任意韵脚的方案转移。

所以，我们的转移应该有两个：

1. $f[i]$ 表示长为 $i$ 的诗句方案数。
	
   这个是次要的转移，用于辅助我们的主转移。
   
   状态转移非常显然：
   
   ```cpp
	f[i]+=f[i-a[j]]
	```

2. $s[i][j]$ 表示长为 $i$ 的诗句韵脚为 $j$ 的方案总数。

	由于 $s[i][j]$ 可以从任何韵脚转移，所以需要弄一个 $f$ 数组来统计。
    
    状态转移可以像这样：
    
    ($f,s$ 数组如上所述，$a$ 数组为单词长度)
    
    ```cpp
	s[i][c[j]]+=f[i-a[j]]

	```
然后对于后面描述的 Bessie 的想要的押韵模式搞一个桶装进去。

然后等状态转移完后将 $i$ 从 $'a'\to 'z'$ 跑一遍，看看桶内是否有东西，若有，则将 $j$ 从 $1\to n$ ，查询 $s[k][j]$ 是否为空，若行则返回 $s[k][j]$ 的某次方，这里的“某”指当前 $i$ 所指向的桶内的要求个数。$ans$ 累乘。

然后是这道题恶心的地方。

可能是我的做法太 naive 了，不知道为什么总是 $\mathtt{MLE}$。

一开始 ```#define int long long```的，然后 $\mathtt{MLE}$了 $6$ 个点，然后去掉后又 $RE$，最后将 $ans$ 和快速幂 开 $long\ long$后过了。

可是空间依旧大的离谱，$\mathtt{96.13MB}$。我看了一下其他人的提交记录全几乎没有（好吧还是有一两个）像我这样空间特大时间也是压线过的。不过能过就行。

人菜常数大，naive 的做法。
    


---

## 作者：Hisaishi_Kanade (赞：3)

### 前言

~~这是我们今天课上一道练习，结果全班就我一个过了。~~

看到这道题我就有了思路（

不过还是调了很久。

### Solution

题意明白，不多赘述。

首先考虑对于**一行**诗，凑足 $k$ 个音节有几种方案。

这个很类似于零一背包问题，和[采药](https://www.luogu.com.cn/problem/P1048)几乎一样。

我们设 $f[i]$ 表示凑成 $k$ 个音节的方案总数。

枚举最后一个单词，得到转移方程：

$$
f[i]=\sum f[i-s[q]]
$$

其中 $s[q]$ 就是某个单词的长度，只有 $i\ge s[q]$ 时才能转移。

- - -

一行诗的情况解决，然后考虑一整首诗。

由题意，两行诗押韵只考虑最后一个字母的韵部。

那么容易想到在上面的方程上加一维，表示最后一个单词的韵部，将之改为：

$$
f[i][j]=\sum f[i-s[q]][p]
$$

$p$ 为任意的韵部。

聪明的你会发现，这一次转移是 $n^2$ 的。

但是我们发现，$p$ 的枚举是不必要的。

设 $sum[i]=\sum f[i][p]$，则上面的转移方程变为 $f[i][j]=\sum sum[i-s[q]]$。

时间复杂度骤降为 $O(n)$。

然后是如何计算总方案数？很简单。

我们设 $X_i$ 表示 字母 $i$ 出现的次数。

则我们可以**令某一个字母** $i$ 押的韵是 $j$，因为题目还**没有要求不同字母押不同的韵**，所以这些答案可以使用乘法原理和加法原理加起来。。

推一下柿子得到结果

$$
\prod_{i=1}^{26}\sum_{p=1}^n f[k][p]^{X[i]}
$$

其中 $\Pi$ 枚举字母，$k$ 是题目给的参数，$p$ 是任意颜色。

- - -

### 代码

```cpp
#include <stdio.h>
typedef long long ll;
namespace root
{
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define lowbit(id) (id&-id)
#define repeat(times) while(times--)
	static const int Buf_size=1<<25,Int_size=25;
	static char F[Int_size];
	static char _c;
	static bool _f;
	static int _x,__cnt;
	static const signed int base_10=10,zero(48),nine(57),flag_signed(45);
	inline int abs(const int &_x)
	{
		return _x<0?-_x:_x;
	}
	inline int max(const int &_x,const int &_y)
	{
		return _x>_y?_x:_y;
	}
	inline int min(const int &_x,const int &_y)
	{
		return _x<_y?_x:_y;
	}
	inline void swap(int &_x,int &_y)
	{
		static int _z;
		_z=_x;
		_x=_y;
		_y=_z;
		return;
	}
#define digit() (zero<=_c&&_c<=nine)
	char buf[Buf_size],*p1=buf,*p2=buf;
//#define getchar() *p1++
	static char obuf[Buf_size],*p3=obuf;
#define putchar(x) (p3-obuf<Buf_size)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
//	template<typename _Tp,const bool is_signed=false>inline void read(_Tp&_x){if(!is_signed){_x=0;_c=getchar();while(!digit())_c=getchar();while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return;}else{_x=0;_f=false;_c=getchar();while(!digit()){if(_c==flag_signed)_f=true;_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}if(_f)_x=-_x;return;}}
	inline int read()
	{
		_x=0;
		_c=getchar();
		while(!digit())_c=getchar();
		while(digit())
		{
			_x=_x*10+(_c^zero);
			_c=getchar();
		}
		return _x;
	}
	template<typename _Tp>inline void write(_Tp _x)
	{
		if(_x<0)
		{
			putchar(flag_signed);
			_x=-_x;
		}
		if(_x<base_10)
		{
			putchar(_x^zero);
			return;
		}
		write(_x/base_10);
		putchar(_x%base_10^zero);
	}
	inline void out(int x,const char end='\n')
	{
		if(!x)
		{
			putchar(zero);
			putchar(end);
			return;
		}
		if(x<0)
		{
			x=-x;
			putchar(flag_signed);
		}
		__cnt=0;
		while(x)
		{
			F[++__cnt]=x%base_10;
			x/=base_10;
		}
		while(__cnt)
		{
			putchar(F[__cnt]^zero);
			--__cnt;
		}
		putchar(end);
		return;
	}
}//一些函数，缺省源。
namespace solve
{
	const int mod=1000000007;//记得取模
	using namespace root;
	long long base,ret;
	int repow(int a,int b)
	{
		int res=1;
		for(;b;b>>=1)
		{
			if(b&1)
				res=(ll)res*a%mod;
			a=(ll)a*a%mod;
		}
		return res;
	}//快速幂
	char now;
	long long res=1,mid;
	int sum[5005],s[5005],c[5005],t[5005],f[5005][5005];
	void main()
	{
//		fread(buf,1,Buf_size,stdin);
		register int i,j;
//		freopen("poetry.in","r",stdin);
//		freopen("poetry.out","w",stdout);
		sum[0]=1;
		register int n=read(),m=read(),k=read();
		for(i=1; i<=n; ++i)
		{
			s[i]=read();
			c[i]=read();
		}
		for(i=1; i<=k; ++i)
		{
			for(j=1; j<=n; ++j)
			{
				if(i>=s[j])
				{
					(f[i][c[j]]+=sum[i-s[j]])%=mod;
					(sum[i]+=sum[i-s[j]])%=mod;
				}
			}//这就是转移一行内的方案
		}
		for(i=1; i<=m; ++i)
		{
			++t[getchar()-'A'];//t[]就是上面的X[]
			getchar();
		}
		for(i=0; i<26; ++i)
		{
			if(t[i]==0)
				continue;
			mid=0;
			for(j=1; j<=n; ++j)
				mid+=repow(f[k][j],t[i]);
			(res*=mid%mod)%=mod;
		}//这就是最后那个柿子
		printf("%lld",res);
		return;
	}
}
int main()
{
	solve::main();
	return 0;
}
```

---

## 作者：DengDuck (赞：2)

简单计数题。

首先我们算出用任意单词填出 $i$ 个音节的方案数 $f_i$，由于要考虑顺序，DP 的方式不同于背包。

我们考虑先枚举使用的音节，再枚举使用的单词，得方程：

$$
f_i=\sum_{j=1}^nf_{i-s_j}
$$

由此，对于每个韵脚，我们枚举结尾的单词，利用 $f_i$ 求出每种韵脚的方案数 $cnt_i$。

最后，对于每个字母，枚举其使用的韵脚，显然这个字母的每一行都可以在 $cnt_i$ 个方案中选择，可以直接快速幂算。

最后将所有字母的方案相乘即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=1e9+7;
const LL N=5e3+5;
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
LL n,m,k,x[N],y,f[N],cnt[N],b[26],ans=1;
vector<LL>v[N];
char s[15];
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x[i],&y);
		v[y].push_back(x[i]);
	}
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(x[j]<=i)f[i]=(f[i]+f[i-x[j]])%mod;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(LL j:v[i])
		{
			cnt[i]=(cnt[i]+f[k-j])%mod;
		}
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		b[s[0]-'A']++;
	}
	for(int i=0;i<26;i++)
	{
		LL t=0;
		if(b[i]==0)continue;
		for(int j=1;j<=n;j++)
		{
			t=(t+ksm(cnt[j],b[i]))%mod;
		}
		ans=ans*t%mod;
	}
	printf("%lld",ans);
}
```

---

## 作者：ZnPdCo (赞：1)

看错题了，这告诉我们读题要仔细，比赛时看成必须不同，想到两个 dp 杂交去了，结果后程在打暴力（当时看到暴力结果和我的代码一模一样但和题目输出不一样内心十分沸腾）：

> 不同 $e_i$ 值的行**并非**必须以不同的韵部的单词结尾。

我以为要**必须不同**……

如果可以相同那么就很简单了，就是一个完全背包方案数。很容易可得到：
$$
f[i][j] \text{为背包容量为 i 且结束韵部为 j 的最大容量}
$$

$$
f[i][j]+=f[i-w][1]+f[i-w][2]+f[i-w][3]+\cdots+f[i-w][n]=\sum_{k = 1}^n f[i-w][k]
$$

如果这么打铁超时。

所以我们干脆：
$$
f[i] \text{为背包容量为 i 的最大容量}
$$

$$
f[i]+=f[i-w]
$$

但是这又不能很好的储存最后的结束韵部，怎么办呢？

---

可以发现我们只需要 $f[n]$ 的结束韵部（前面的可以乱玩），我们开一个新的 dp：
$$
g[i] \text{为背包容量为 n 且结束韵部为 i 的最大容量}
$$
更新时判断一下如果 `i == n` 就更新 $g[i]$。

---

结果为（以下用 $p$ 表示某个韵部结尾的情况数）：
$$
(p_1)^2
\times((p_1)^1+(p_2)^1)+(p_2)^2
\times((p_1)^1+(p_2)^1)=((p_1)^2+(p_2)^2)\times((p_1)^1+(p_2)^1)
$$
当然如果我们这么看感觉会很枯燥，我解释一下：我们把相同的韵部看作一组，即一组有多个相同的韵部。

那么韵部 $A$ 因为有两个，它的结果有 $((p_1)^2+(p_2)^2)$。

韵部 $B$ 因为有一个，它的结果有 $((p_1)^1+(p_2)^1)$。

把韵部的所有情况计算出来（加法原理），再用乘法原理相乘，即可。

```c++
#include <cstdio>
#define P 1000000007
#define ll long long
ll n, m, k, res = 1;
ll s[5010], c[5010];
char e[100010];
ll f[5010];
ll g[5010];

ll num['z'];

ll qpow(ll x, ll y) {
    if(y == 0) return 1;
    if(y % 2 == 0) {
        ll res = qpow(x, y / 2);
        return res * res % P;
    }
    return qpow(x, y - 1) * x % P;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    scanf("%lld %lld %lld", &n, &m, &k);
    for(ll i = 1; i <= n; i++) {
        scanf("%lld %lld", &s[i], &c[i]);
    }
    for(ll i = 1; i <= m; i++) {
        char s[10];
        scanf("%s", s);
        e[i] = s[0];
        num[e[i]]++;
    }

    f[0] = 1;
    for(ll i = 0; i <= k; i++) {
        for(ll j = 1; j <= n; j++) {
            if(i < s[j]) continue;
            (f[i] += f[i - s[j]]) %= P;
            if(i == k) {
                (g[c[j]] += f[i - s[j]]) %= P;
            }
        }
    }

    for(ll i = 'A'; i <= 'Z'; i++) if(num[i]) {
        ll ans = 0;
        for(ll j = 1; j <= n; j++) {
            if(g[j]) {
                (ans += qpow(g[j], num[i])) %= P;
            }
        }
        (res *= ans) %= P;
    }
    printf("%lld", res);
}
```

---

## 作者：m256i (赞：1)

令 $S_i$ 为韵部为 $i$ 单词的长度构成的集合。

每种押韵模式的结果乘起来就是最终结果。因此对每种模式分别考虑，假设共有 $\mathrm{cnt}_c$ 行采用第 $c$ 种模式。令 $f_i$ 为一行以韵部为 $i$ 结尾单词的方案数，则第 $c$ 种答案显然为 $\displaystyle\sum_{i=1}^nf_i^{\mathrm{cnt}_c}$。

令 $d_i$ 为用单词排列出 $n$ 个音节的方案数，则容易得到 $f_i=\displaystyle\sum_{s \in S_i}d_{k-s}$。

现在考虑怎么计算 $d_i$。容易发现题目中的排列区分顺序（$\mathsf{123}$ 和 $\mathsf{132}$ 是两种不同的排列），且允许同种元素出现多次（即 $\mathsf{113}$）。那么容易联想到解析组合里的 $\operatorname{SEQ}$。

记 $b_i$ 为 $i$ 个音节单词的个数。设单词长度的组合类为 $\mathcal B$，生成函数为 $B(x)$，则 $d_i$ 的组合类为 $\operatorname{SEQ}(\mathcal B)$，生成函数为 $D(x)=\dfrac{1}{1-B(x)}$。

方便起见，设 $G(x)=1-B(x)$，$i$ 次项系数为 $g_i$。则 $g_0=1$，且 $i>0$ 时有 $b_i=-g_i$。

显然有 $D(x)G(x)=1$，此时 $d_0=1$，且对于任意 $k>0$ 都有 $\displaystyle\sum_{i=0}^kd_ig_{k-i}=0$。提取一项 $d_kg_0$ 出来：

$$
\begin{aligned}
d_kg_0+\sum_{i=0}^{k-1}d_ig_{k-i}&=0\\
d_k+\sum_{i=0}^{k-1}d_ig_{k-i}&=0
\end{aligned}
$$

容易得到 $d_k$ 的表达式：

$$
\begin{aligned}
d_k&=-\sum_{i=0}^{k-1}d_ig_{k-i}\\
&=\sum_{i=0}^{k-1}d_i(-g_{k-i})\\
&=\sum_{i=0}^{k-1}d_ib_{k-i}
\end{aligned}
$$

递推即可，复杂度 $\Theta(k^2)$。

当然可以直接多项式求逆，但是 $k$ 很小，并且模数不能 NTT，暴力 $\Theta(k^2)$ 求逆甚至可能比 $\Theta(k \log k)$ 的任意模数求逆快。

代码（瞎写了一个，然后直接 187ms 最优解）：

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
inline T max(T a, T b){return (a>b) ? a : b;}
template <typename T>
inline T min(T a, T b){return (a<b) ? a : b;}

template <typename T>
void read(T &x){
	static char ch;
	x = 0;
	while (!isdigit(ch=getchar()));
	do x = (x<<3)+(x<<1)+(ch^'0');
	while (isdigit(ch=getchar()));
}

template <typename T>
void write(T x, char c = ' '){
	static char st[100], *p;
	if (x < 0) putchar('-'), x = -x;
	if (x == 0) putchar('0');
	for (p = st; x; x /= 10) *++p = x%10;
	for (; p != st; --p) putchar(*p|'0');
	putchar(c);
}

template <typename T>
inline void writeln(T x){write(x, '\n');}

constexpr ll P = 1e9+7;

ll pow(ll x, ll y){
	ll ans = 1;
	while (y){
		if (y&1) ans = ans*x%P;
		x = x*x%P;
		y >>= 1;
	}
	return ans;
}

std::vector<int> s[5005];
ll b[5005], dp[5005], f[5005];
int cnt[127];

int main(){
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	dp[0] = 1;
	int n, m, k; read(n), read(m), read(k);
	for (int i = 1; i <= n; ++i){
		int y, c; read(y), read(c);
		s[c].push_back(y); ++b[y];
	}
	dp[0] = 1;
	for (int i = 1; i <= k; ++i){
		for (int j = 0; j < i; ++j) dp[i] += dp[j]*b[i-j];
		dp[i] %= P;
	}
	for (int i = 1; i <= n; ++i){
		for (int x : s[i]) f[i] += dp[k-x];
		f[i] %= P;
	}
	for (int i = 1; i <= m; ++i){
		unsigned char ch; while (isspace(ch=getchar())); ++cnt[ch];
	}
	ll ans = 1;
	for (unsigned char c = 'A'; c <= 'Z'; ++c){
		if (!cnt[c]) continue;
		ll s = 0;
		for (int i = 1; i <= n; ++i) s += pow(f[i], cnt[c]);
		ans = s%P*ans%P;
	}
	writeln(ans);
	
	
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：有 $n$ 种物品，每种具类型 $c_i$ 和价值 $s_i$，求满足将一系列物品分为 $m$ 组，每组总价值一定且一些组最后一个物品类型相同的方法数。

核心思想：DP

解：

令总长度为 $x$ 的词的排列方式数为 $f(x)$, 总长度为 $x$ 的词结束在韵部 $y$ 的排列方式数为 $g(x, y)$，且韵部 $y$ 的单词数有 $c_y$ 个，长度为 $l(i)(1\le i\le c)$，则有 $f(0)=1$，$\forall x,y\ge 1,f(x)=\sum_{i=1}^ng(x, i)$ 且 $g(x, y)=\sum_{i=1}^{c_y}f(x-l(i))$，DP 即可。

容易发现，所有行的排列除最后一个词的选择外是相互独立的。可以将所有行分为至多 $26$ 组，每组末词韵部相同。若第 $i$ 组有 $a_i$ 行，则共有 $\prod_{i=1}^{26}\sum_{j=1}^nc_j^{i}$ 种排列方式。快速幂即可。总复杂度 $O(nk+n\log m)$，可以通过。如果全部使用 ```long long``` 空间会不足，因此 $g(x,y)$ 部分可以改用 ```int```，占空间约 $95MB$，足够。

代码：
```
#include <bits/stdc++.h>
using namespace std;

const long long mod=1000000007;
long long n, m, k, s[5001], c[5001], e[27], b[100001], t, flag, res=1;
int a[5001][5001];
char ch;

long long qp(long long x, long long y)
{
	if(y==0)
		return 1;
	long long t=qp(x, y/2);
	if(y%2==0)
		return t*t%mod;
	else
		return t*t%mod*x%mod;//快速幂 
} 

int main()
{
	cin>>n>>m>>k;
	for(long long i=1; i<=n; i++)
		cin>>s[i]>>c[i];
	for(long long i=1; i<=m; i++)
	{
		cin>>ch;
		e[ch-64]++;
		flag=max(flag, e[ch-64]);//行分组 
	}
	a[0][0]=1;
	for(long long i=1; i<=k; i++)
		for(long long j=1; j<=n; j++)
			if(i>=s[j])
			{
				a[i][0]=((long long)a[i][0]+(long long)a[i-s[j]][0])%mod;
				a[i][c[j]]=((long long)a[i][c[j]]+(long long)a[i-s[j]][0])%mod;//求算f(x, y) 
			}
//	for(long long i=1; i<=k; i++)
//	{
//		for(long long j=1; j<=n; j++)
//			cout<<a[i][j]<<" ";
//		cout<<endl;
//	}
	for(long long i=1; i<=26; i++)
	{
		t=0;
		for(long long j=1; j<=n; j++)
			t=(t+qp(a[k][j], e[i]))%mod;
		if(e[i]==0)
			t=1;
		res=res*t%mod;//乘得结果 
	}
	cout<<res;
	return 0;
}
```

---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

想略过这一部分，因为和后面的讲解重合了，而且题目有点绕，我认为三言两语我讲不通，所以烦请。

## 解题思路

解题主要分两部分。

首先因为每行的字数相同，所以我们可以预处理出长度为 $k$ 音节的句子每种韵部的方案数。

定义一个 $f$ 数组来解决这个问题吧，先不考虑韵部，令 $f_i$ 为能凑成长度为 $k$ 的句子的方案数。

我们显然可以用 $O(nk)$ 的复杂度预处理出 $f$ 数组。

然后再想每个韵部，设当前的单词长为 $s_i$，归属于韵部 $c_i$，则我们可以对 $r_i$（长度为 $k$ 的句子结尾恰好为韵部 $i$ 的方案数）累加 $f_{k-s_i}$，这段的代码实现如下：

```cpp
f[0]=1;
for(int i=0;i<=k;i++)
    for(int type=1;type<=n;type++)
		if(i+s[type]<=k){
			f[i+s[type]] = (f[i+s[type]]+f[i])%mod;
			if(i+s[type]==k)
				r[c[type]] = (r[c[type]]+f[i])%mod;
		}
```

这一部分解决了，我们来看第二部分。

这一部分限定了押韵方式，但是容易发现方式与顺序无关，所以我们用一个数组 $a$ 来存下每种押韵方式有几行。

```cpp
for(int i=1;i<=m;i++){
	do{
		ch=getchar();
	}while(ch<'A' || ch>'Z');
	a[ch]++;
}
```

然后遍历押韵方式，对于每一种押韵方式 $k$，都有 $n$ 种可能的取值，所以答案需要累乘 $\sum_{i=1}^n r_i^{a_k}$。

```cpp
for(int i='A';i<='Z';i++)
	if(a[i]){
		tr=0;
		for(i64 j=1;j<=n;j++)
			tr = (tr + fpow(r[j],a[i])%mod)%mod;
		res = (res*(tr%mod))%mod;
	}
```

最终代码如下：

```cpp
#include<stdio.h>

#define maxn 6007
#define mod 1000000007
typedef long long i64;

i64 s[maxn],c[maxn],f[maxn],r[maxn],n,m,k,res=1,tr,a[300];

char ch;

i64 fpow(i64 x,i64 p){
	i64 res=1;
	while(p){
		if(p&1)
			res = (res*x) % mod;
		p>>=1;
		x = (x*x) % mod;
	}
	return res % mod;
}

int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",s+i,c+i);

   f[0]=1;
	for(int i=0;i<=k;i++)
	    for(int type=1;type<=n;type++)
			if(i+s[type]<=k){
				f[i+s[type]] = (f[i+s[type]]+f[i])%mod;
				if(i+s[type]==k)
					r[c[type]] = (r[c[type]]+f[i])%mod;
			}
	
	for(int i=1;i<=m;i++){
		do{
			ch=getchar();
		}while(ch<'A' || ch>'Z');
		a[ch]++;
	}
	
	for(int i='A';i<='Z';i++)
		if(a[i]){
			tr=0;
			for(i64 j=1;j<=n;j++)
				tr = (tr + fpow(r[j],a[i])%mod)%mod;
			res = (res*(tr%mod))%mod;
		}

	printf("%lld",res%mod);
	return 0;
}
```

---

## 作者：2021changqing52 (赞：0)

# 思路：
由题意可知每一行最后一个词要满足要求，前面的词**可以乱填**。

于是我们可以定义 $q_i$ 表示一行中填 $i$ 个音节的方案总数（注意给最后一个单词空出位置），再用 $p_i$ 表示以某韵部结尾的方案数，最后按要求计数即可。
# Code:
```cpp
#include<bits/stdc++.h>
#define N 5005
#define LL long long
using namespace std;
int n,m,k;char u[5];
LL s[N],c[N],q[N],p[N],nd[30];
const LL mod=1000000007;
LL qpow(LL b,LL k){//递归版快速幂
	if(k==0)return 1;
	if(k==1)return b%mod;
	LL q=qpow(b,k>>1);
	if(k&1)return q*q%mod*b%mod;
	else return q*q%mod;
}
int main(){
   	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>s[i]>>c[i];
	q[0]=1;for(int j=0;j<=k;j++)
	if(q[j])for(int i=1;i<=n;i++)//一个小优化，如果方案数是0不用去填，反正不会改变
	if(j+s[i]<=k)q[j+s[i]]=(q[j+s[i]]+q[j])%mod;;//能填进去，加方案数
	for(int i=1;i<=n;i++)p[c[i]]=(p[c[i]]+q[k-s[i]])%mod;//空出位置给最后一个单词
	while(m--){
	    cin>>u;
		nd[u[0]-'A']++;//统计
	}
	sort(nd,nd+26,greater<int>());
	sort(p+1,p+n+1,greater<int>());
	LL ans=1;
	for(int i=0;i<26&&nd[i];i++){
		LL x=nd[i],sum=0;
		for(int j=1;j<=n&&p[j];j++)sum=(sum+qpow(p[j],x))%mod;
		ans=ans*sum%mod; 	
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：鹤箩芠 (赞：0)


序：为啥要发这个题解呢 ， 因为我有一些小优化 ， 跑的速度只比开了 $O_{2}$的慢 ， 话说这空间卡的那么死吗(

step1:求出所有每个韵脚再最后的方案数。
考虑性质 由于一行的方案数只和最后一个单词有关系 ， 再看一眼$n 和 k$的数据范围,可以轻松跑dp. 设$f_{i , j}$当前长度为i的方案数 ， 且若$i=k，j$就表示最后一个单词的韵脚。

初始化：$f_{0,0}=1$

$if(i + length_{j}\ne k)\Longrightarrow f_{i + length_{j} , 0} +=f_{i,0}$
$if(i + length_{j}= k)\Longrightarrow f_{i + length_{j} , c_{j}} +=f_{i,0}$

这样我们就愉快的求出来了以每个韵脚当结尾的方案数 。
友情提示：若按照我的状态转移直接做 ， 会MLE因为要开一个二维数组 ， 其实只要再拿一个一位数组来代替第二维就可以惹~（雾。

```cpp
	f[0] = 1 ;
	for (int i = 0 ; i <= k ; i ++) {
		for (int j = 1 ; j <= n ; j ++) {
			if (i + p[j].len > k) continue ;
			else if (i + p[j].len == k) {
				G[p[j].c] = (f[i] + G[p[j].c]) % mod ;  
			}
			else if (i + p[j].len < k) {
				f[i + p[j].len] = (f[i] + f[i + p[j].len]) % mod ;

			}
		}
	}
```


 step2:求出答案。
对于每行的韵脚要求 ， 我们可以知道对于$ch_{i}$可以是任意一个韵脚 ， 只需要简单的乘法原理就可以轻松求出惹 
即：
$ans = \prod_{i=1}^{m} {\sum_{j = 1}^{n}G_{j}^{cnt_i}}$ 当然对于每种字母 ， 我们只能算一次。
 快速幂优化即可求出ans~
 
这个小优化其实很简单 ， 也就是说我们对于相同字母的$cnt_{i}$贡献自然也是一样的 ， 我们可以用记忆话搜索的思想进行优化即可。


---

