# Vasya and Binary String

## 题目描述

Vasya 有一个长度为 $n$ 的字符串 $s$，该字符串只包含数字 $0$ 和 $1$。他还有一个长度为 $n$ 的数组 $a$。

Vasya 会不断进行如下操作，直到字符串变为空：选择一段连续且字符相同的子串，将其从字符串中删除，并将剩余部分拼接起来（剩余部分可以为空）。例如，如果他从字符串 111110 中删除子串 111，他将得到字符串 110。每当他删除长度为 $x$ 的子串时，他会获得 $a_x$ 分。

Vasya 想要让自己的总得分最大，请你帮助他实现这个目标。

## 说明/提示

在第一个样例中，最优的删除顺序为：1101001 $\rightarrow$ 111001 $\rightarrow$ 11101 $\rightarrow$ 1111 $\rightarrow$ $\varnothing$。

在第二个样例中，最优的删除顺序为：10101 $\rightarrow$ 1001 $\rightarrow$ 11 $\rightarrow$ $\varnothing$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
1101001
3 4 9 100 1 2 3
```

### 输出

```
109
```

## 样例 #2

### 输入

```
5
10101
3 10 15 15 15
```

### 输出

```
23
```

# 题解

## 作者：Karry5307 (赞：17)

### 题意

给定一个 $01$ 串，消除一段长度为 $i$ 的全 $0$ 或全 $1$ 串获得分值 $a_i$，求将这个串消除完的最大分数。

$\texttt{Data Range:}1\leq n\leq 100$

### 题解

区间 DP 存档文。

很明显是区间 DP，所以一开始有一个很不成熟的想法是设 $f_{i,j}$ 表示消除区间 $[i,j]$ 的答案，但是有可能存在消掉 $j$ 右边一段的决策。

这个时候类似于 UVa10559，设 $f_{i,j,k}$ 表示消除区间 $[i,j]$ 及 $j$ 右边恰好 $k$ 个与位置 $j$ 相同字符的答案，那么很明显有两种转移：

- 直接消掉 $j$ 及右边 $k$ 个。

- 枚举一个与 $j$ 同字符的位置 $l$，通过消掉 $[l+1,j+1]$ 将这两个区间合并起来。

所以说就得到有 $f_{i,j,k}=\max(f_{i,j-1,0}+a_{k+1},f_{l+1,j-1,0}+f_{i,l,k+1})$，直接转移是 $O(n^4)$ 的，可以通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=151;
ll n;
ll f[MAXN][MAXN][MAXN],x[MAXN];
char ch[MAXN];
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
int main()
{
	n=read(),scanf("%s",ch+1);
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=n;i;i--)
	{
		for(register int j=i;j<=n;j++)
		{
			for(register int k=0;k<n;k++)
			{
				f[i][j][k]=f[i][j-1][0]+x[k+1];
				for(register int l=i;l<j;l++)
				{
					if(ch[l]==ch[j])
					{
						f[i][j][k]=max(f[i][j][k],f[l+1][j-1][0]+f[i][l][k+1]);
					}
				}
			}
		}
	}
	printf("%lld\n",f[1][n][0]);
}
```

---

## 作者：LJC00118 (赞：13)

用 $ f_{i,j,k} $ 表示区间 $ [i, j] $ 右边还有 $ k $ 个和 $ j $ 的颜色相同的块消掉后得到的最大权值

两种转移

- $ f_{i,j,k} = f_{i,j-1,0} + v_{k+1} $ （将 $ j $ 和后面 $ k $ 个和 $ j $ 颜色相同的东西删掉
- $ f_{i,j,t} = f_{k+1,j-1,0} + f_{i,k,t+1} $ （$ k $ 和 $ j $ 同色，先将 $ [k + 1, j - 1] $ 删掉，剩下 $ [i, k] $ 和 $ j $ 右边的 $ t $ 个与 $ k $ 同色的，即为 $ f_{i,k,t+1} $

可以发现，每一种删除方式都被这两种转移所包含，$ n^3 $ 个状态，每个状态最多 $ n $ 个转移，复杂度 $ n^4 $ （跑不满

```cpp
#include <bits/stdc++.h>
#define int long long
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 105;

char c[N];
int f[N][N][N];
int sum[N], v[N];
int n;

#undef int
int main() {
#define int long long
    read(n); scanf("%s", c + 1);
    for(register int i = 1; i <= n; i++) read(v[i]);
    for(register int i = 2; i <= n; i++) {
        for(register int j = 1; j < i; j++) v[i] = max(v[i], v[j] + v[i - j]);
    }
    for(register int i = 1; i <= n; i++) {
        for(register int j = i + 1; j <= n; j++) sum[i] += (c[i] == c[j]);
    }
    for(register int i = n; i >= 1; i--) {
        for(register int j = i; j <= n; j++) {
            for(register int k = i; k < j; k++) {
                if(c[j] == c[k]) {
                    for(register int t = 0; t <= sum[j]; t++) {
                        f[i][j][t] = max(f[i][j][t], f[k + 1][j - 1][0] + f[i][k][t + 1]);
                    }
                }
            }
            for(register int k = 0; k <= sum[j]; k++) f[i][j][k] = max(f[i][j][k], f[i][j - 1][0] + v[k + 1]);
        }
    }
    cout << f[1][n][0] << endl;
    return 0;
}
```

---

## 作者：Soulist (赞：9)

emm这道题还是很套路的但是我dp做少了所以想了那么久= =


考虑暴力$dp$，记$dp_{i,j,k,0/1}$表示到区间$[i,j]$还剩余$k$个$0/1$的最大权值

这样就得到了一个$O(n^5)$的优秀做法qwq

枚举分界点，两边的剩余个数即可

接下来是这一类区间$dp$中较为常见被人注意到的性质：

首先你要意识到，两个不相交的删除的方案，相对顺序并没有影响


这样的话对于一个区间$[i,j]$考虑最右边的$j$所对应的点，显然有其最后必然被消掉

考虑最后的答案，对于区间$[1,n]$，显然操作应当是先消除一些，使得$n$前面有一些连续的相同的一段，再消除$x\to n$这一连续的点，再消除其他所有的点

不过知道这一点后会发现消除的相对顺序之类的对于答案并没有影响


比如它可以变成：

先消除一些，再消除其他所有的影响，最后消除$x\to n$这一连续的点且其与$n$相同


于是考虑$dp$，记$dp_{i,j,k}$表示区间$[i,j]$消成最后与$c_j$相同为$k$时的最大权值

则由于我们已经规定让$j$最后消除，所以$j$必然是保留的，于是可以考虑枚举分割点$t$，然后将$t+1\to j$均被消除即可，值得注意的是$c_t=c_j$的情况下我们才能转移，不过此情况仅在$k\ne 1$时生效

特别的，我们需要特殊转移$dp_{i,j,0}$其来自于$\max_{k=1}^{len}dp_{i,j,k}+a_k$

不过由于一些初始化的问题，就采用了一些特殊手段啥的= =，看思路就好了

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 150 + 5 ; 
int n, dp[N][N][N], a[N], c[N] ; 
signed main()
{
	n = gi() ; rep( i, 1, n ) c[i] = getchar() - '0' ;
	rep( i, 1, n ) a[i] = gi() ; memset( dp, -63, sizeof(dp) ) ;
	for( re int i = 1; i <= n; ++ i ) dp[i][i][1] = 0, dp[i][i][0] = a[1] ;
	for( re int l = 2; l <= n; ++ l ) {
		for( re int i = 1; i <= n - l + 1; ++ i ) {
			int j = i + l - 1 ; 
			for( re int k = 1; k <= l; ++ k ) {
				for( re int t = i; t < j; ++ t )
				if( c[t] == c[j] || k == 1 ) dp[i][j][k] = max( dp[i][j][k], dp[i][t][k - 1] + max( 0ll, dp[t + 1][j - 1][0] ) ) ;
			}
			for( re int k = 1; k <= l; ++ k ) dp[i][j][0] = max( dp[i][j][0], dp[i][j][k] + a[k] ) ;
		}
	}
	printf("%I64d\n", dp[1][n][0] ) ;
	return 0 ;
} 
```

---

## 作者：whiteqwq (赞：6)

[CF1107E Vasya and Binary String](https://www.luogu.com.cn/problem/CF1107E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1713721)

## 前言
有两道比较相似的题目，可以先做完：[CF1132F Clear the String](https://www.luogu.com.cn/problem/CF1132F)与[SP6340 ZUMA - ZUMA](https://www.luogu.com.cn/problem/SP6340)。

## 题意
题意：给定一个长度为$n$的$01$串$s$与得分数组$a$，每次可以从$s$中删除任意子串（子串中所有字符必须相同），可以获得$a[子串长度]$的得分，求删除完$s$的最大得分。

数据范围：$1\leqslant n\leqslant 100$。

## 分析
首先观察题目，可以通过经验得到这道题是区间$dp$。

尝试设二维$dp$数组$f[l][r]$，代表删除区间$[l,r]$的最大得分，答案便是$f[1][n]$。

但是这个转移不好写（至少我不会写），而且加上数据范围很小，因此两维应该是不够的。

按照[SP6340 ZUMA - ZUMA](https://www.luogu.com.cn/problem/SP6340)的经验，我们尝试设三维$dp$数组$f[l][r][k]$指删除区间前的$k$个与$l$颜色相同的数与区间$[l,r]$的最大得分，这样转移就很显然了：

1. 可以将前面附加的数与第$l$个数一起删除，就可以从$f[l+1][r][0]$转移来，也就是```f[l][r][k]=min(f[l][r][k],f[l+1][r][0]+a[k+1]);```
2. 枚举所有与区间$[l,r]$第一个数相同的断点$p$，这样可以先删除区间$l+1,p-1$，然后删除前面附加的数$+$第$l$个数$+$区间$[p,r]$，也就是```f[l][r][k]=min(f[l][r][k],f[l+1][p-1]+f[p][r][k+1]);```

然后就是区间$dp$的常规做法了。

## 代码
```
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
const int maxn=105;
int i,j,k,m,n,p,len;
int a[maxn],f[maxn][maxn][maxn];
string s;
int main(){
	scanf("%d",&n);
	cin>>s;
	s=" "+s;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=2;i<=n;i++)
		for(j=1;j<i;j++)
			a[i]=max(a[i],a[j]+a[i-j]);
	for(len=1;len<=n;len++)
		for(i=1;i+len-1<=n;i++){
			int j=i+len-1;
			for(k=0;k<=n;k++){
				f[i][j][k]=max(f[i][j][k],f[i+1][j][0]+a[k+1]);
				for(p=i+1;p<=j;p++)
					if(s[i]==s[p])
						f[i][j][k]=max(f[i][j][k],f[i+1][p-1][0]+f[p][j][k+1]);
			}
		}
	printf("%d\n",f[1][n][0]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：6)

> CF1107E

> 题意：给出一个长度为 $n$ 的 $01$ 字符串，你重复下列操作若干次直到字符串为空：

> - 选择一段长度为 $len$ 的连续区间，满足这个区间中的字符都相等并将这个区间删除，可以获得 $a_{len}$ 分。

> 求将字符串变为空串最多可以获得多少分。

> 数据范围：$1 \leq n \leq 100$

一道挺神的题。

类似地题目有 CF1132F/POJ1390

先回顾一下 CF1132F 的解法：

$dp(l,r)$ 表示消除完 $[l,r]$ 的字符所需的最小代价。

考虑转移：我们可以直接消去 $l$ 或 $r$，更新 $\min(dp(l+1,r),dp(l,r-1))+1$。也可以在 $[l+1,r]$ 中枚举一个 $i$ 使得 $s_i=s_l$，然后我们先将 $[l+1,i-1]$ 中所有字符消去，这样 $l$ 与 $i$ 相邻，并且它们字符相同，就可以看成一个合体字符了，消除字符 $i$ 就可以看成将字符 $l$ 和 $i$ 一起消除，再消除 $[i,r]$ 就可以了。

但是上述解法套用到这道题上就不行了

因为将 $[l+1,i-1]$ 消除完后，$l$ 与 $i$ 相邻，由 $1$ 个连续的字符变为 $2$ 个连续的字符，在 CF1132F 中不管消除多少个连续的字符代价都是 $1$，但是在这题中就不一样了。因此我们还需加一个第三维 $k$，$dp(l,r,k)$ 表示消除区间 $[l,r]$，其中 $l$ 是 $k$ 个与 $s_l$ 相同的字符的合体，那么这样转移：

- 如果 $l$ 与 $r$ 相等，那么没别的办法，只能将这 $k$ 个字符一并消去，直接返回 $a_k$。

- 否则，按照上一题的套路，我们找到一个 $i$ 满足 $a_l=a_i$，进行 $dp(l+1,i-1,1)$，表示消去 $[l+1,r-1]$，这样 $i$ 就变成了原本 $l$ 的 $k$ 个字符与它自己的 $k+1$ 个字符的合体，执行 $dp(i,r,k+1)$

- 也可以直接消去 $l$，更新 $dp(l+1,r,1)+a_k$，然后就好了。

还有一点要注意，就是比如说 $a$ 数组长这样：

```
2 1
```

发现消除 $2$ 个连续的数的最大分数并不是 $a_2$，因为可以通过消除 $2$ 个连续的 $1$ 得到，因此我们要用一遍简单的背包预处理出真正的 $a$。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int a[105],n=read(),dp[105][105][105];
char s[105];
inline int dfs(int l,int r,int k){
	if(l>r)		return 0;
	if(l==r)	return a[k];
	if(~dp[l][r][k])	return dp[l][r][k];
	dp[l][r][k]=dfs(l+1,r,1)+a[k];
	fz(i,l+1,r){
		if(s[l]==s[i])	dp[l][r][k]=max(dp[l][r][k],dfs(l+1,i-1,1)+dfs(i,r,k+1));
	}
	return dp[l][r][k];
}
signed main(){
	cin>>s+1;
	fz(i,1,n){
		a[i]=read();
		fz(j,1,i-1)	a[i]=max(a[i],a[j]+a[i-j]);
	}
	fill1(dp);
	cout<<dfs(1,n,1)<<endl;
	return 0;
}
```

---

## 作者：litble (赞：6)

# 题目分析

个人博客->[QvQ](https://blog.csdn.net/litble/article/details/87290658)

令$f(i)$表示$i$个一样的连在一起的元素，被消完的最大分数，一个完全背包可以搞定。

然后将连续的一段相同元素合成一个点，原序列变成了若干黑白交错的点，记点$i$中的元素个数为$sz(i)$。

令$g(l,r,k)$表示现在要消完$[l,r]$这一段点（和后面的$k$个元素），点$r$后面有$k$个与$r$点颜色相同的元素。那么$r$可以选择跟前面的元素一起消，也可以不一起消。

不一起消：$g(l,r-1,0)+f(sz(r)+k)$

一起消：（$i$是$[l,r-1]$中一个和$r$颜色相同的点）$g(i+1,r-1,0)+g(l,i,k+sz(r))$

记忆化搜索，跑不满，加上CF评测姬快如闪电，可以过。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
typedef long long LL;
const int N=105;
int n,cnt;LL a[N],f[N],g[N][N][N];char S[N];
struct node{int sz,col;}b[N];

void prework() {
    for(RI i=1;i<=n;++i)
        for(RI j=i;j<=n;++j) f[j]=max(f[j],f[j-i]+a[i]);
    int now=0;
    for(RI i=1;i<=n;++i) {
        if(i==1||S[i]==S[i-1]) ++now;
        else ++cnt,b[cnt].sz=now,b[cnt].col=S[i-1]-'0',now=1;
    }
    ++cnt,b[cnt].sz=now,b[cnt].col=S[n]-'0';
}
LL DP(int l,int r,int k) {
    if(l==r) {return g[l][r][k]=f[b[l].sz+k];}
    if(g[l][r][k]!=-1) return g[l][r][k];
    LL re=DP(l,r-1,0)+f[b[r].sz+k];
    for(RI i=l;i<r-1;++i)
        if(b[i].col==b[r].col)
            re=max(re,DP(i+1,r-1,0)+DP(l,i,b[r].sz+k));
    return g[l][r][k]=re;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",S+1);
    for(RI i=1;i<=n;++i) scanf("%lld",&a[i]);
    prework();
    memset(g,-1,sizeof(g));
    printf("%lld\n",DP(1,cnt,0));
    return 0;
}
```

---

## 作者：gyh20 (赞：4)

来源：[我的 60 题进阶计划:1](https://www.luogu.com.cn/blog/gyh20/post-60-ti-jin-jie-ji-hua)

以前一直以为区间 DP 都是模板，这道题让我大开眼界！

普通区间 DP 只是二维 $dp_{i,j}$，然后枚举中间点合并两个区间。

但在此题中出现了一个问题，原先的区间不能直接由两个区间拼成，比如样例二，假如 $a_3$ 特别大，那么整个区间最优时由三个 $1$ 拼起来，无法只由两个区间拼出。

考虑到 $n$ 只有 $100$，可以多加一维，这一维的状态十分难设计，由于我们求的东西是连续个数，考虑这样设计状态： $f_{l,r,k}$ 表示区间 $l,r$  ，其中 $k$ 代表的是 $l$ 左方（包括 $l$）有连续 $k$ 个相等的数。可以巧妙避免合并区间，于是 DP 方程就很明显了。

首先，边界： $l=r,dp_{l,r,k}=a_k$ 

方程 $dp_{l,r,k}=dp_{l+1,r,1}+a_k$（直接合并）

设中间点为 $x$， $dp_{l,r,k}=\max([s_l=s_x]dp_{l+1,x-1}+dp_{x,r,k+1})$（合并中间一段，左边和右边到一起了）

注意初始 $a_i$ 要类似背包转移，找到最优。

具体实现用记忆化比较方便。

```
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,a[102],dp[102][102][102];
char s[102];
inline int ask(re int l,re int r,re int k){
	if(l>r)return 0;
	if(l==r)return a[k];
	if(~dp[l][r][k])return dp[l][r][k];
	dp[l][r][k]=ask(l+1,r,1)+a[k];
	for(re int i=l+1;i<=r;++i)if(s[i]==s[l])dp[l][r][k]=max(dp[l][r][k],ask(l+1,i-1,1)+ask(i,r,k+1));
	return dp[l][r][k];
}
signed main(){
	n=read();
	scanf("%s",s+1);
	for(re int i=1;i<=n;++i){
		a[i]=read();
		for(re int j=i-1;j;--j)a[i]=max(a[i],a[j]+a[i-j]);
	}
	memset(dp,-1,sizeof(dp));
	printf("%lld",ask(1,n,1));
}
```


---

## 作者：2huk (赞：3)

[Codeforces Round 59 (Div. 2) E - Vasya and Binary String](https://codeforces.com/problemset/problem/1107/E)

## 题目描述

给你一个长度为 $n$ 的 $01$ 串 $s$，从 $s$ 中删除一段连续的长度为 $i$ 的所有字符都相同的子串将会得到 $a_i$ 的分数，如果执行上述操作直到 $s$ 被删除完，求最大分数和。

$1 \le n \le 100$

## 分析

显然是区间 `DP`。

如果要删去 $i$ 个相同的 $0/1$ 的最大收益不一定是 $a_i$，所以 `DP` 前需要做一个完全背包，令 $w_i$ 表示删去 $i$ 个相同的 $0/1$ 的最大收益。

```cpp
for (re int i = 1; i <= n; i ++ )
	for (re int j = i; j <= n; j ++ )
		w[j] = max(w[j], w[j - i] + a[i]);
```

接下来设状态 $f_{l, r}$ 表示删除完 $l \sim r$ 这段区间所能得到的最大价值。

对于一个区间 $l \sim r$，它一定是将两段区间分别消除再拼起来的。如果两端区间分别为 $l \sim k$ 和 $k + 1 \sim r$，那么一定是左边剩了 $k_1$ 个 $0/1$，右边剩了 $k_2$ 个 $0/1$，拼起来一共剩了 $k_1 + k_2$ 个 $0/1$。因此还需要额外统计剩余若干个 $0/1$ 的最大收益。

设 $g_{l, r, t, 0/1}$ 表示删去 $l \sim r$ 这段区间后剩 $t$ 个 $0/1$ 的最大收益。那么两个状态间就可以互相转移了。

如果 $l \sim r$ 这段区间还剩下 $t$ 个 $c$，那么会得到 $w_t$ 的收益。因此 $f_{l, r}$ 是最大的 $g_{l, r, t, s_r} + w_t$。

对于 $g$ 的求解，需要像普通区间 `DP` 一样分段求解。即枚举分割点 $k$，$k$ 左面的可以直接调用 $g_{l, k, t, 0/1}$，右面的则需要直接消除而不剩余，即 $f_{k + 1, r}$。

另外一种情况，对于 $s_r$ 这个点，也可以把它加进前面的贡献，即 $g_{l, r - 1, t - 1, s_r}$。

完整的转移如下：
$$
g_{l, r, t, s_r} = g_{l, r - 1, t - 1, s_r}$$
$$
g_{l, r, t, 0} = \max\limits_{k = l}^{r - 1}(g_{l, k, t, 0} + f_{k + 1, r})$$
$$
g_{l, r, t, 1} = \max\limits_{k = l}^{r - 1}(g_{l, k, t, 1} + f_{k + 1, r})$$
$$
f_{l, r} = \max\limits_{t = 0}^{r - l + 1}(\max(g_{l, r, t, 0}, g_{l, r, t, 1}) + w_t)
$$
显然最终答案为 $f_{1, n}$。

[$\text{Code}$](https://www.luogu.com.cn/paste/u185o658)

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1107E)

[CFlink](https://codeforces.com/problemset/problem/1107/E)

简要题意：

给定 01 串 $s$，每次从 $s$ 中删除一个所有字符都相同的字段并获得 $a_k$（$k$ 为字段长度）的分数，问将 $s$ 删成空串能获得的最大分数。

# $\text{Solution}$

歪解警告，一开始想区间 dp 没想到什么好的做法，于是突发奇想想到了下面这个做法。

显然可以先 $O(n^2)$ 处理 $a$ 数组，处理成单增。

设 $f_s$ 表示将字符串 $s$ 删成空串的最大分数，用 ``umap`` 存储，用记忆化搜索转移。

如果暴力去转移的话时间复杂度肯定是错误的，但是我们将 $a$ 处理成单增的了，所以将相同的字符尽可能放在一起删一定是更优的。

所以我们令当前字符串的第一个字符为基准字符，将开头连续的基准字符一次性处理一定是更优的。

接着遍历后面的字符，每当遇到与基准字符相同的字符，则考虑将这之间的字符抠出来，将这一段先删掉，然后其他的拼起来再处理。

语文水平不是很好，大家可以按下面这个图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/3pk6jnl9.png)

整个字符串为 $s$，前面连续的一段子段为 $A$，中间抠掉的部分为 $T$，剩下的部分为 $B$。

那么 $f_{A+B}+f_{T}$ 就是一种可能更新 $f_s$ 的值（$A+B$ 表示将 $B$ 接在 $A$ 后面）。

感谢 [YK](https://www.luogu.com.cn/user/263112) 大神证明了这个算法的复杂度：

$A+B$ 是一个全 0/1 前缀加上一个字符串，所以状态应该是 $O(n^3)$ 的，总复杂度为 $O(n^4)$。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 105
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,a[N];
string s;
unordered_map<string,int>f;//用 umap 代替 map 可以有效提高程序效率
string sub(string s,int l,int r){
	string t="";
	for(int i=l;i<=r;++i) t+=s[i];
	return t;
}
int dfs(string s){
	if(s.size()<=1) return a[s.size()];
	if(f.count(s)) return f[s];
	int res=0,p=0,len=s.size();
	while(p<len && s[0]==s[p]) ++p;
	res=max(res,dfs(sub(s,p,len-1))+a[p]);
	for(int i=p;i<len;++i) if(s[i]==s[0]) res=max(res,dfs(sub(s,p,i-1))+dfs(sub(s,0,p-1)+sub(s,i,len-1)));
	return f[s]=res;
}
signed main(){
	n=read();cin>>s;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=2;i<=n;++i) for(int j=1;j<=i;++j) a[i]=max(a[i],a[j]+a[i-j]);
	printf("%lld",dfs(s));
	return 0;
}
```

---

## 作者：EricQian (赞：2)

刚做完 [P5336 [THUSC2016]成绩单](https://www.luogu.com.cn/problem/P5336)，同学推荐我来做这道类似的题，发现转移方法和现有题解不太一样，故来交份题解分享一下我的思路。

首先我们算出删去一段长度固定的相同序列的最大价值，记为 $val(i)$，可以用背包轻松解决。

考虑设 $g(l,r)$ 表示消除 $[l,r]$ 区间内的左右元素所需要的代价，但是我们发现这样无法转移，根据 P5336 的启发，我们不难想到用一个辅助数组来帮助我们转移。

我们设 $f(l,r,0/1,k)$ 表示将区间消除到**只剩下** $k$ 个 $0$ 或 $k$ 个 $1$ 的最大收益（注意是到达这个状态），那么 $f$ 可以这么转移：

+ 将 $s_r$ 添加到剩余序列中，$f(l,r,s_r,k)=f(l,r-1,s_r,k-1)$。

+ 删去区间右侧的一段区间，$f(l,r,0/1,k)=f(l,p,0/1,k)+g(p+1,r)$。

$g$ 数组可以用 $f$ 转移：

$$g(l,r)=f(l,r,0/1,k)+val(k)$$

最终答案就是 $g(l,r)$ 啦！

推荐一道思路基本相同的题目：[UVA10559 方块消除 Blocks](https://www.luogu.com.cn/problem/UVA10559)

```cpp
// Author:A weak man named EricQian
#include<bits/stdc++.h>
using namespace std;
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define Maxn 105
typedef long long ll;
inline int rd()
{
	 int x=0;
	 char ch,t=0;
	 while(!isdigit(ch = getchar())) t|=ch=='-';
	 while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	 return x=t?-x:x;
}
inline ll maxll(ll x,ll y){ return x>y?x:y; }
inline ll minll(ll x,ll y){ return x<y?x:y; }
inline ll absll(ll x){ return x>0ll?x:-x; }
inline ll gcd(ll x,ll y){ return (y==0)?x:gcd(y,x%y); }
int n;
char s[Maxn];
ll c[Maxn],f[Maxn];
ll g[Maxn][Maxn];
ll dp[Maxn][Maxn][2][Maxn];
int main()
{
	 n=rd(),scanf("%s",s+1);
	 for(int i=1,x;i<=n;i++)
	 {
	 	 x=rd(),c[i]=s[i]-'0';
	 	 for(int j=i;j<=n;j++) f[j]=max(f[j],f[j-i]+x);
	 }
	 memset(dp,-infll,sizeof(dp)),memset(g,-infll,sizeof(g));
	 for(int i=1;i<=n;i++)
	 {
	 	 g[i][i]=f[1];
		 dp[i][i][c[i]][1]=0,dp[i][i][c[i]][0]=f[1];
		 dp[i][i][c[i]^1][0]=0;
	 }
	 for(int len=2;len<=n;len++)
	 {
	 	 for(int l=1,r;l<=n-len+1;l++)
	 	 {
	 	 	 r=l+len-1;
 	 	 	 for(int p=1;p<=len;p++)
 	 	 	 {
 	 	 	 	 dp[l][r][c[r]][p]=maxll(dp[l][r][c[r]][p],dp[l][r-1][c[r]][p-1]);
 	 	 	 	 for(int k=l;k<r;k++) for(int opt=0;opt<2;opt++)
 	 	 	 	 	 dp[l][r][opt][p]=maxll(dp[l][r][opt][p],dp[l][k][opt][p]+g[k+1][r]);
			 }
			 for(int p=1;p<=len;p++) for(int opt=0;opt<=1;opt++)
			 	 g[l][r]=maxll(g[l][r],dp[l][r][opt][p]+f[p]);
		 }
	 }
	 printf("%lld\n",g[1][n]);
	 return 0;
}
```

---

## 作者：duyi (赞：1)

[更更更更更更更更更更好的阅读体验！！！](https://www.cnblogs.com/dysyn1314/p/14194683.html)


# CF1107E Vasya and Binary String

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1107/E)

给定一个长度为 $n$ 的 01 串 $s$，和一个长度为 $n$ 的正整数序列 $a$。

你需要进行若干次操作，直到字符串 $s$ 为空。每步操作中，可以选择当前串 $s$ 里的一段相同字符组成的连续子串，并将其删掉。然后它两边的字符会自动拼接起来。设当前删除的子串长为 $x$，那么可以获得 $a_x$ 的收益。

求所有操作完成后，能获得的收益之和的最大值。

数据范围：$1\leq n\leq 100$，$1\leq a_i\leq 10^9$。

## 本题题解

考虑区间 DP。容易想到的一个状态设计是：$\text{dp}(i,j,k,0/1)$，表示只考虑 $[i,j]$ 这段区间，还剩下 $k$ 个 $0$ 或 $1$ 没有删除时，能得到的最大收益（不包括这 $k$ 个 $0/1$ 的收益）。转移需要枚举 $i,j$ 中间的断点，再枚举左边剩多少个 $0/1$ 没有删掉（左边的知道了，用 $k$ 减左边的就是右边的）。特别地，$k = 0$ 时可以把两边的、剩余的部分一起消掉，并产生一个收益。时间复杂度 $\mathcal{O}(n^5)$，无法通过本题。另外，如果把状态简单定义为 $\text{dp}(i,j)$，也能得到一个 $\mathcal{O}(n^5)$ 做法，这里不细说了。

我们需要更巧妙的状态设计。

强行钦定区间的最后一位（$j$）是还没有被删掉的，或者说是和非当前区间里的数一起删掉的。可以理解为是上一种状态里的 "$k$" 个位置中的一员。

定义新状态 $\text{dp}_2(i,j,x)$ 表示只考虑 $[i,j]$ 这段区间，$j$ 后面有 $x$ 个数是（要在之后的过程里）和它一起被删掉的。当然，既然只考虑了区间 $[i,j]$，那我们也不知道 $j$ 后面的串长什么样。所以这 $x$ 个数是我们想象出来的，可能根本不存在这些数，但这不重要，我们只要保证能从符合实际的状态转移到答案即可。答案就是 $\text{dp}(1,n,0)$。

转移有两种：

- 把一段数删掉。这段是就是指 $j$ 和它后面的数。于是有转移：$\text{dp}_2(i,j,x)\leftarrow \text{dp}_2(i,j,0) + a_{x + 1}$。
- 合并两段区间。枚举断点 $p\in[i,j)$，则：$\text{dp}_2(i,j,x)\leftarrow \text{dp}_2(i,p,x + 1) + \text{dp}_2(p + 1, j - 1, 0)$。这相当于把 $p$、$j$、以及 $j$ 后面的 $x$ 个数，一起删掉，所以执行这种转移的前提是 $s_{p} = s_{j}$。并且，这次删除的收益已经算在 $\text{dp}_2(i,j,x)$ 里了，所以这里不需要加上。

感性理解：在第一种转移里，我们算上想象中的 $x$ 的收益，相当于是开出了一张空头支票。而第二种转移，发现 $x$ 减小了 $1$，这代表这我们的承诺在一步步兑现。具体来说，就是最后的那一位 $j$，从空头支票里走到了现实中。

于是，这个复杂的操作过程，就被转化为了简单的“开支票，再不断兑现”的过程。并且同一时间只需要处理一张支票，这是因为任意两个操作区间，要么相互并列，要么完全包含，不可能出现相交。$[p + 1, j - 1]$ 其实就是这种“完全包含”的情况，它是一个完全自闭的区间（自我封闭，也就是已经完结了）。特别地，这个区间的长度可能为 $0$，即 $p + 1 = j$，此时我们认为 $\text{dp}_2(p + 1, j - 1, 0) = 0$。

转移的复杂度主要来自于枚举 $p$，是 $\mathcal{O}(n)$ 的。总时间复杂度 $\mathcal{O}(n^4)$。

## 参考代码

```cpp
// problem: CF1107E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 100;
const ll LL_INF = 1e15;

int n, a[MAXN + 5];
char s[MAXN + 5];

ll dp[MAXN + 5][MAXN + 5][MAXN + 5];

int main() {
	cin >> n;
	cin >> (s + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			for (int k = 0; k <= n; ++k) {
				dp[i][j][k] = -LL_INF;
			}
		}
		for (int k = 0; k <= n - i; ++k) {
			dp[i][i][k] = a[k + 1];
		}
	}
	
	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			for (int k = 0; k <= n - j; ++k) {
				ckmax(dp[i][j][k], dp[i][j - 1][0] + a[k + 1]);
			}
			
			for (int k = 0; k <= n - j; ++k) {
				for (int l = i; l <= j - 1; ++l) if (s[l] == s[j]) {
					ckmax(dp[i][j][k], dp[i][l][k + 1] + dp[l + 1][j - 1][0]);
				}
			}
		}
	}
	cout << dp[1][n][0] << endl;
	
	return 0;
}
```



---

## 作者：Paris_Commune (赞：0)

### 分析

区间 dp，$k$ 是核心，在这里想了好久。

步骤：

- 首先枚举一个区间的两个端点 $[i,j]$。

- 找到一个 $k$，使得 $[j,k]$ 区间内的所有字符相同。

  - 删除 $[j,k]$。
  - $q$ 与 $j$ 同色，消除 $[q+1,j+1]$，合并。

设 $f_{i,j,k}$，$i,j,k$ 意义如上，表示该区间最大值。

则转移分别是 $f_{i,j,k}=f_{i,j-1,k}+a_{k+1}$ 和 $f_{i,j,k}=f_{q+1,j-1,0}+f_{i,q,k+1}$，第二个方程要取最大值。

---

## 作者：intel_core (赞：0)

看到这题 $n\le 100$ 直接联想到一个简单的区间 `DP` ：

* $f_{l,r}$ 表示将 $[l,r]$ 中的元素都消掉的最大分数。

* 转移单次 $O(n)$ 即可。

这样 `DP` 连样例都过不了，原因出在 $[l,r]$ 之间消去后左边，右边的元素没有考虑进来。

我们增加一维 $k$ ，使其表示 $[l,r]$ 右边还有 $k$ 个与 $s_r$ 相同的被消掉。

每次转移复杂度 $O(n)$ ，总复杂度 $O(n^4)$ ，但实际上有 $\frac{1}{6}$ 左右的常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=110;
int n,a[NR],f[NR][NR][NR];
char s[NR];

void upd(int &x,int y){x=max(x,y);}
signed main(){
	cin>>n;
	scanf(" %s",s+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;i+j<=n;j++)upd(a[i+j],a[i]+a[j]);
	for(int len=1;len<=n;len++)
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			for(int k=0;k<=n;k++){
				upd(f[i][j][k],f[i+1][j][0]+a[k+1]);
				for(int p=i+1;p<=j;p++)
					if(s[i]==s[p])upd(f[i][j][k],f[i+1][p-1][0]+f[p][j][k+1]);
			}
		}
	cout<<f[1][n][0]<<endl;
	return 0;
}
```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1107E)

[三倍经验](https://www.luogu.com.cn/training/303429#problems)

设 $dp(i,j)$ 为删除 $s_i \sim s_j$ 后的最大分数和，但是需要考虑删除右边。

设 $dp(i,j,k)$ 为 $s_i \sim s_j$ 这一段以及 $j$ 后面 $k$ 个和 $s_j$ 相同的字符皆被删除后的最大分数和。

$dp(i,j,k,q)$ 表示和上述一样，只是加上了 $q$ 表示删除的是 0 或 1，这显然会超时。

我们可以按照区间 DP 的正常解题思路来考虑，弄一个 $l$ 来将 $i\sim j$ 分成两段，这时候我们想：消掉 $s_{l+1}\sim s_{j-1}$ 自然是消掉了一个和 $s_j$ 相同的字符，因此每一次枚举 $l$ 我们需要先给 $dp(i,j,k)$ 赋一个 $dp(i,l,k+1)$，为什么呢？因为 $i\sim l$ 的后面肯定有 $l$，而 $k+1$ 变成 $k$ 则是表示 $l$ 被消去了，因此 $k$ 要减一。但是 $dp(i,j,k)$ 还要加上它的另一段也就是 $dp(l+1,j-1,0)$，这一段的后面没有删除任何数，因此 $k$ 为 0，$j$ 算在被删除的之中，因此为 $j-1$。

为什么考虑删掉 $k$ 个数时删除 $s_j$ 呢？很显然是因为转移时需要从 $k$ 变化的状态转移过来的同时从区间变化的状态转移过来，而 $j$ 就很好地充当了这个桥梁。实际上，$l$ 作为分隔者不一定存在，我们也可以让 $l$ 作为区间最右边，也就是说直接把 $j$ 和右边 $k$ 个消掉。

复杂度理论上是 $O(n^4)$ 的，实际上远远小于这个时间。

PS：其实不一定要三维，也可以类似状态拆分，用一个辅助数组 $g$ 来表示删除右边。

最后贴码码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    static int n,c[111],a[111],dp[111][111][111];
    cin>>n,cin>>s;
    for(int i=1;i<=n;i++)cin>>a[i]; 
    for(int i=0;i<s.length();i++)c[i+1]=s[i];
    for(int i=s.length();i>=1;i--)
	{
		for(int l=1;i+l-1<=s.length();l++)
		{
			int j=i+l-1;
			for(int k=0;k<n;k++)
			{
				dp[i][j][k]=dp[i][j-1][0]+a[k+1];
				for(int l=i;l<j;l++)
				{
					if(c[j]==c[l])dp[i][j][k]=max(dp[i][j][k],dp[i][l][k+1]+dp[l+1][j-1][0]);
				}
			}
		}
	} 
	cout<<dp[1][s.length()][0];
    return 0;
}
```


---

