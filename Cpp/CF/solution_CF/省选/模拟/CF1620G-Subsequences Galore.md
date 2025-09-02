# Subsequences Galore

## 题目描述

For a sequence of strings $ [t_1, t_2, \dots, t_m] $ , let's define the function $ f([t_1, t_2, \dots, t_m]) $ as the number of different strings (including the empty string) that are subsequences of at least one string $ t_i $ . $ f([]) = 0 $ (i. e. the number of such strings for an empty sequence is $ 0 $ ).

You are given a sequence of strings $ [s_1, s_2, \dots, s_n] $ . Every string in this sequence consists of lowercase Latin letters and is sorted (i. e., each string begins with several (maybe zero) characters a, then several (maybe zero) characters b, ..., ends with several (maybe zero) characters z).

For each of $ 2^n $ subsequences of $ [s_1, s_2, \dots, s_n] $ , calculate the value of the function $ f $ modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
a
b
c```

### 输出

```
92```

## 样例 #2

### 输入

```
2
aa
a```

### 输出

```
21```

## 样例 #3

### 输入

```
2
a
a```

### 输出

```
10```

## 样例 #4

### 输入

```
2
abcd
aabb```

### 输出

```
124```

## 样例 #5

### 输入

```
3
ddd
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaabbbbbbbbbbbcccccccccccciiiiiiiiiiiiiiiiiiiiiiooooooooooqqqqqqqqqqqqqqqqqqvvvvvzzzzzzzzzzzz```

### 输出

```
15706243380```

# 题解

## 作者：LinkZelda (赞：6)

考虑把集合用二进制数的方法表示。

设 $S[x]$ 表示现在集合在二进制表示下为 $x$，该集合中所有字符串的子序列的交集元素个数。

因为给定的字符串中字符串是排好序了的，所以这个是好求的，我们设集合 $x$ 中所有字符串某个字符 $c$ 出现次数的最小值是 $minn_c$，那么 $S[x]=\prod_{c\in[a,z]}(minn_c+1)$。

然后题目要求的 $f(x)$ 是表示在集合在二进制表示下为 $x$，该集合中所有字符串的子序列的并集元素个数。

对于这种交集转化为并集，我们可以考虑容斥原理，即
$$
f(x)=\sum_{y\subseteq x}(-1)^{size(x)-1}S[x]
$$

就是对于加上所有集合大小为奇数的 $S[x]$，同时减去所有集合大小为偶数的 $S[x]$。

我们可以分别对集合大小为奇数和偶数的 $S[x]$ 做高维前缀和，然后就可以 $O(1)$ 计算每个 $f(x)$ 了。

时间复杂度为 $O(n\cdot 2^n)$。

[参考代码](https://www.luogu.com.cn/paste/gp2ljbu0)

---

## 作者：Richard_Whr (赞：1)

来一种暴力优化做法。

很容易想到记录 $f_{i,s}$ 表示当前已经考虑了前 $i$ 种字母，仍能和构造的字符串匹配上的极大集合为 $s$ 下的方案数。

记录极大集合是为了防止算重复。

对于第 $i$ 种字符的转移，考虑这一种字符填 $x,x\ge 0$ 个，然后就能知道所有字符串在这一个字母上有至少 $x$ 的极大集合 $s$，给 $w_s$ 加 $1$。

转移方程就是：

$$f_{i+1,s \&t}\leftarrow f_{i,s} \times w_t$$

求答案的柿子是：

$$ans_{s}=\sum\limits_{t}[s \& t\not=0]f_t$$

这个容易使用容斥算所有的减去无交的算。

前面转移是一个 FWT 能做的东西，直接暴力就可以做到 $O(n \times |S| \times 2^n)$

卡卡常应该只能过 $21$ 左右，考虑优化。

每次对 $f$ 数组做一遍 FWT 是没有意义的，我们可以一直让 $f$ 保留 $fwt_f$ 形态，最后再变回来。只需要优化 $w$ 数组的计算。

考虑“与”下 FWT 的实际意义：所有超集的和。注意到按照上面那个求法，$w$ 的所有值都形如 $cnt_{rk_k}-cnt_{rk_{k-1}}$。对于他们求和本质上就是找到 $s$ 集合中最小的数，也就是说 $w_s=\min\limits_{i}\{cnt_i\}+1$，最后加的是空集。

这下做到了 $O(|S| \times 2^n+n\times 2^n)$，可以通过。

好像和别的题解本质相同，不过不失为一种更易理解的做法。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=23,M=26,V=(1<<N),mod=998244353;
int cnt[N][M];
char str[V];
int f[V],w[V];
int p[N];
int ans[V];
int n;

void solve(int c)
{
	for(int i=0;i<n;i++) p[i]=i;
	
	sort(p,p+n,[&](int x,int y){return cnt[x][c]<cnt[y][c];});
	
	w[0]=2e4+1;
	for(int s=1;s<(1<<n);s++)
	{
		int j=__builtin_ctz(s);
		w[s]=min(w[s^(1<<j)],cnt[j][c]+1);
	}
	w[0]=0;
}

inline void Add(int &a,int b)
{
	if(b<0) b+=mod;
	if(a+b>=mod) a=a-mod+b;
	else a=a+b;
}

inline void And(int *a,int op)
{
	for(int i=0;i<n;i++)
	{
		for(int s=0;s<(1<<n);s++)
		{
			if((s>>i)&1) Add(a[s^(1<<i)],a[s]*op);
		}
	}
}

inline void Or(int *a,int op)
{
	for(int i=0;i<n;i++)
	{
		for(int s=0;s<(1<<n);s++)
		{
			if((s>>i)&1) Add(a[s],a[s^(1<<i)]*op);
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
	
	double st=clock();
	
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>(str);
		int len=strlen(str);
		for(int j=0;j<len;j++) cnt[i][str[j]-'a']++;
	}
	
	f[(1<<n)-1]=1;
	And(f,1);
	for(int c=0;c<M;c++)
	{
		//memset(w,0,sizeof w);
		solve(c);
		//And(w,1);
		//And(f,1);
		for(int s=0;s<(1<<n);s++) f[s]=(LL)f[s]*w[s]%mod;
		//And(f,-1);
	}
	And(f,-1);
	
	Or(f,1);
	
	for(int s=0;s<(1<<n);s++) ans[s]=(f[(1<<n)-1]-f[((1<<n)-1)^s]+mod)%mod;
	
	LL res=0;
	for(int s=1;s<(1<<n);s++)
	{
		int sz=0,sum=0;
		for(int i=0;i<n;i++) if((s>>i)&1) sz++,sum+=(i+1);
		res^=(LL)ans[s]*sz*sum;
	}
	
	cout<<res<<"\n";
	
	double ed=clock();
	cerr<<(ed-st)/CLOCKS_PER_SEC<<"\n";
	
	return 0;
}
```

---

## 作者：linyihdfj (赞：1)

## CF1620G Subsequences Galore
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
题意很抽象，稍微转化一下：$f([t_1,t_2,\cdots,t_m])$ 代表的是 $t_1,t_2,\cdots,t_m$ 的子序列的并集。

稍微尝试一下就会发现并集其实不好求，但是交集很好求。

因为我们的字母都是按顺序排列的，所以对于每种字母出现的次数取个 $\min$ 然后乘起来就是交集，既然交集好球并集不好求显然可以直接容斥一下就好了。

那么最后的答案就是奇数个数的减去偶数个数的。

稍微形象一点就是这样的：

设 $f(S)$ 表示 $S$ 内这些字符串的子序列的交集，则：
$$
f(S) = \prod_{c \in [a,z]} (mn_c + 1)
$$
其中 $mn_c$ 代表 $c$ 这种字符最少的出现次数。

设 $g(S)$ 表示 $S$ 内这些字符串的子序列的并集，可得：
$$
g(S) = \sum_{T \subseteq S} (-1)^{|T| - 1} f(T)
$$
可以对于奇数个和偶数个的分开处理，然后做一次高维前缀和就结束了。

但是在实现的时候需要注意，在计算 $f(S)$ 的时候稍微精细一下，因为如果完全暴力计算的话是会被最大的一个点卡掉的。

### 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
const int MOD = 998244353;
const int N = 2e4+5;
int cnt[30][30],mn[1<<23],s[2][1<<24];
char t[N];
int mod(int x){
	return x >= MOD ? x - MOD : x;
}
int lowbit(int x){
	return x & (-x);
}
int get(int x){
	int cnt = 0;
	while(x){
		cnt++;
		x /= 2;
	}
	return cnt;
}
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1; i<=n; i++){
		scanf("%s",t+1);
		int m = strlen(t+1);
		for(int j=1; j<=m; j++)	cnt[i][t[j] - 'a']++;
	}
	for(int i=0; i<26; i++){
		memset(mn,0x3f,sizeof(mn));
		for(int j=1; j<(1<<n); j++){
			int tmp1 = __builtin_popcount(j);
			mn[j] = min(mn[j ^ lowbit(j)],cnt[get(lowbit(j))][i]);
			s[tmp1&1][j] = ((s[tmp1&1][j]==0) ? (mn[j]+1) : (s[tmp1&1][j] * (mn[j] + 1))%MOD);
		}
	}
	for(int i=1; i<=n; i++){   //高维前缀和 
		for(int j=1; j<(1<<n); j++){
			if((j >> (i-1)) & 1){
				s[1][j] = mod(s[1][j] + s[1][j ^ (1<<(i-1))]);
				s[0][j] = mod(s[0][j] + s[0][j ^ (1<<(i-1))]);
			}
		}
	}
	int ans = 0;
	for(int i=1; i<(1<<n); i++){
		int tmp1 = 0,tmp2 = 0;
		for(int j=1; j<=n; j++){
			if((i >> (j-1)) & 1){
				tmp1++;
				tmp2+=j;
			}
		}
		ans ^= tmp1 * tmp2 * mod(s[1][i] - s[0][i] + MOD);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

因为字符串内部是排好了序的，所以对于一个字符串，它的子串数量是很好算的，记 $c_i$ 为第 $i$ 个字符的出现次数，那么方案数就是 $\prod(c_i+1)$。

容易想到对于所有的答案，我们可以考虑容斥，先把每个的方案加上，然后再减去重复的方案。

注意到在容斥的时候，直接枚举子集是 $O(3^n)$ 的，会 T，容易想到容斥时对于 $-1$ 这个系数仅跟集合大小的奇偶性相关，因此对奇数和偶数分别作子集和就行了，一个状态的答案就是用奇数的子集和减去偶数的子集和。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,ans,cnt[23][26],w[1<<23],c[26],f[1<<23],g[1<<23];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;++i){
		string s;
		cin>>s;
		for(auto c:s) ++cnt[i][c-'a'];
	}
	for(int state=1;state<(1<<n);++state){
		memset(c,0x3f,sizeof(c));
		for(int i=0;i<n;++i) if(state>>i&1) for(int j=0;j<26;++j) c[j]=min(c[j],cnt[i][j]);
		w[state]=1;
		for(int i=0;i<26;++i) w[state]=w[state]*(c[i]+1)%mod;
		if(__builtin_popcount(state)&1) f[state]=w[state];
		else g[state]=w[state];
	}
	for(int i=0;i<n;++i) for(int j=1;j<(1<<n);++j) if(j>>i&1){
		f[j]=(f[j]+f[j^(1<<i)])%mod;
		g[j]=(g[j]+g[j^(1<<i)])%mod;
	}
	for(int state=1;state<(1<<n);++state){
		int res=(f[state]-g[state]+mod)%mod,s=0;
		for(int i=0;i<n;++i) if(state>>i&1) s+=(i+1);
		ans^=(res*s*__builtin_popcount(state));
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
模拟赛前开的题，模拟赛刚好做到了高维前缀和，突然就感觉这题挺 ez 的了。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
首先第一眼能看到 $n\le23$。

$23$ 是不太常见的，常见的应该是 $20,21$ 等，所以我们看一眼时空限制。

$10$ 秒，那大致的就可以猜到复杂度里 $2^n$ 跑不了了。

回归正题，我们发现题目给的这个异或式子是无从下手的，这个式子没有任何的特殊性质，只能暴力算。

也就是我们肯定要对于每一种集合算出其可能的答案。

那对于一个集合，答案如何计算？

注意到答案要求的是**并集**，我们不妨尝试用**容斥原理**将其转化为**交集**。

交集是好求的，字符已经排序，所以可能的字符串形如 $a\dots ab\dots b\dots$。

我们对于每一种字符取一个 $\min$，不妨设其中一种字符的 $\min$ 为 $x$，那么交集就是可以选择 $0,1,\dots,x$ 个这种字符。

根据乘法原理简单数出交集即为 $\prod\limits_{i\in S}(mn_i+1)$，其中 $S$ 为字符集。

然后我们使用容斥原理把并集变成交集，这里暴力做复杂度 $O(2^{2n})$ 显然又爆了。

既然容斥原理本身就是一个枚举子集的东西，那么我们可以考虑用高维前缀和来优化。

但是容斥原理他是奇数减偶数加的，还需要变符号，好像不会了？

既然奇偶不同，那么我们直接划分等价类，对于奇数做一个高维前缀和，再对偶数也做一遍高维前缀和，再作差就可以得到正确的答案了。

如此，我们使用高维前缀和把复杂度压到了 $O(n\cdot 2^n)$。

但是其实这题瓶颈在于求交集的预处理，所以总复杂度是 $O(n\cdot 2^n\cdot |S|)$，$|S|$ 为字符集大小。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
// #define int long long
using namespace std;
const int N=2e4+10,M=8.5e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,a[N][27],mn[M][27],f[2][M];char s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read();for(int i=1,l;i<=n;i++)
    {
        l=0,rd(s,l);
        for(int j=1;j<=l;j++) a[i][s[j]-'a']++;
        for(int j=0;j<(1<<n);j++) if(j&(1<<i-1))
            for(int k=0;k<26;k++) mn[j][k]=min(mn[j][k],a[i][k]);
    }long long ans=0;
    for(int j=1,w=1;j<(1<<n);j++)
    {
        for(int i=0;i<26;i++) w=1ll*w*(mn[j][i]+1)%mod;
        f[__builtin_popcount(j)&1][j]=w;w=1;
    }for(int i=0;i<n;i++) for(int j=0;j<(1<<n);j++) if(j&(1<<i))
        f[0][j]=(f[0][j]+f[0][j^(1<<i)])%mod,f[1][j]=(f[1][j]+f[1][j^(1<<i)])%mod;
    for(int j=0;j<(1<<n);j++)
    {
        int s1=0,s2=0;
        for(int i=1;i<=n;i++) if(j&(1<<i-1)) s1++,s2+=i;
        ans^=1ll*s1*s2*((f[1][j]-f[0][j]+mod)%mod);
    }print(ans);
}
signed main()
{
    int T=1;memset(mn,0x3f,sizeof mn);
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：DerrickLo (赞：0)

我们先求出对于每个子集，有多少个字符串是这个子集中所有串的子序列。记 $cnt_{i,j}$ 表示第 $i$ 个串中第 $j$ 个字符出现的次数，那么因为所有串的字符都单调递增，所以我们可以求出这个问题的答案 $\displaystyle{f_S=\prod_{i=0}^{25}(\min_{j\in S}\{cnt_{j,i}\}+1)}$。

然后考虑容斥。记 $g_S$ 表示集合 $S$ 的答案，那么：

$$g_S=\sum_{V\subset S}(-1)^{|V|+1}\times f_V$$

这个可以直接对 $|S|$ 为奇数和偶数分别做一次高维前缀和来得到。

时间复杂度 $\mathcal O(n2^n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int n,cnt[28][28],f[28][8400005],f1[8400005],f2[8400005];
long long ans;
string s[25];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		for(char c:s[i])cnt[i][c-'a']++;
	}
	for(int i=0;i<26;i++)f[i][0]=1e9;
	for(int i=1;i<(1<<n);i++){
		long long now=1,pos=0;
		for(int j=1;j<=n;j++)if(i&(1<<j-1))pos=j;
		for(int j=0;j<26;j++)f[j][i]=min(f[j][i^(1<<pos-1)],cnt[pos][j]),now*=f[j][i]+1,now%=mod;
		if(((int)__builtin_popcount(i))&1)f1[i]+=now,f1[i]%=mod;
		else f2[i]+=now,f2[i]%=mod;
	}
	for(int i=1;i<=n;i++)for(int j=0;j<(1<<n);j++)if(j&(1<<i-1))f1[j]+=f1[j^(1<<i-1)],f1[j]%=mod;
	for(int i=1;i<=n;i++)for(int j=0;j<(1<<n);j++)if(j&(1<<i-1))f2[j]+=f2[j^(1<<i-1)],f2[j]%=mod;
	for(int i=0;i<(1<<n);i++){
		int sum=0,cnt=0;
		for(int j=1;j<=n;j++)if(i&(1<<j-1))sum+=j,cnt++;
		ans^=1ll*(f1[i]-f2[i]+mod)%mod*sum*cnt;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

降智了，为什么只想到差分不想到前缀和……

首先考虑给定一个字符串，怎么计算不同子序列数。容易得到，答案即为 $\prod_{c\in V}(cnt_c+1)$。其中 $V$ 为字符集，$cnt_i$ 为字符 $i$ 出现的次数。

考虑一个集合 $S$ 的答案怎么计算。发现可以简单容斥解决。但是如果直接每个做一遍容斥就是 $O(3^n)$ 级别的。不能通过。

所以考虑拆开，发现做的所有容斥中出现过的不同的值最多有 $O(2^n)$ 个，并且一个集合的所有子集都会对它产生贡献。可能有点抽象，举个例子，集合 $\varnothing,\{s_1\},\{s_2\},\{s_1,s_2\}$ 会对 $\{s_1,s_2\}$ 产生贡献。发现这可以写成一个高维前缀和的形式。预处理每个集合所产生的贡献，即上述“不同的值”，即可 $O(n\times 2^n)$ 解决。

code：

```cpp
int n,m,c[M][V],f[N][V],s[N],pw[M];
char t[M];
inline int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		scanf("%s",t+1);
		m=strlen(t+1);
		rep(j,1,m){
			c[i][t[j]-'a']++;
		}
	}
	pw[0]=1;
	rep(i,1,4e4){
		pw[i]=2ll*pw[i-1]%mod;
	}
	const int k=1<<n;
	rep(i,0,25){
		f[0][i]=inf;
	}
	rep(i,1,k-1){
		int x=i^(i&(-i)),y=__lg(i&(-i))+1,cnt=1;
		rep(j,0,25){
			f[i][j]=min(f[x][j],c[y][j]);
			cnt=1ll*cnt*(f[i][j]+1)%mod;
		}
		s[i]=__builtin_popcount(i)&1?cnt:mod-cnt;
	}
	rep(i,0,n-1){
		int x=1<<i;
		rep(j,0,k-1){
			if(x&j)
				s[j]=Mod(s[j],s[j^x]);
		}
	}
	ll ans=0;
	rep(i,0,k-1){
		int cnt=0,sum=0;
		rep(j,1,n){
			if((i>>(j-1))&1)
				cnt++,sum+=j;
		}
		ans^=1ll*s[i]*cnt*sum;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：zztqwq (赞：0)

由于字母有序，所以我们可以将一个字符串表示成一个 $26$ 元组 $(c_{0},c_{1},c_{2},\cdots,c_{25})$ 表示每个字母出现次数。一个字符串能够表示为一堆字符串的子序列当且仅当他被其中任意一个字符串 $26$ 维偏序，那这题本质上就是 $n$ 个 $26$ 维超立方体，对于所有子集求体积并。并不好求，考虑求交之后子集容斥出来。设 $f(S)$ 表示 $S$ 为 $1$ 这些二进制位所代表的超立方体的交，$g(S)$ 表示并，那么有：
$$
g(S)=\sum_{T\subseteq S} (-1)^{|T|+1}f(T)
$$
这是一个高维前缀和的形式，可以在 $\mathcal O(2^nn)$ 的复杂度内求解。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
const int N=1<<23,M=2e4+10,mod=998244353;
int v[N],cnt[26][25],pos[N],pop[N],sum[N],g[N];
char s[M];ll f[N];
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(int j=1;j<=len;j++)cnt[s[j]-'a'][i]++;
	}
	for(int i=0;i<(1<<n);i++)v[i]=1;
	for(int i=1,j=1;i<(1<<n);i<<=1,j++)pos[i]=j;
	for(int i=1;i<(1<<n);i++)
	{
		pop[i]=pop[i>>1]+(i&1);
		sum[i]=sum[i^(i&-i)]+pos[i&-i];
	}
	for(int i=0;i<26;i++)
	{
		memset(g,0x3f,sizeof(g));
		for(int s=1;s<(1<<n);s++)
		{
			g[s]=min(g[s^(s&-s)],cnt[i][pos[s&-s]]);
			v[s]=1ll*v[s]*(g[s]+1)%mod;
		}
	}
	for(int i=1;i<(1<<n);i++)f[i]=(pop[i]&1)?v[i]:mod-v[i];
	for(int i=0;i<n;i++)
	{
		for(int s=0;s<(1<<n);s++)
		{
			if(s&(1<<i))continue;
			f[s^(1<<i)]+=f[s],f[s^(1<<i)]%=mod;
		}
	}
//	for(int i=0;i<(1<<n);i++)printf("f[%d]=%d\n",i,f[i]);
	ll ans=0;
	for(int i=0;i<(1<<n);i++)ans^=1ll*f[i]*pop[i]*sum[i];
	printf("%lld",ans);
}
```





---

