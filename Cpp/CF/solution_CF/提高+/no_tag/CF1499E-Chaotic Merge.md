# Chaotic Merge

## 题目描述

You are given two strings $ x $ and $ y $ , both consist only of lowercase Latin letters. Let $ |s| $ be the length of string $ s $ .

Let's call a sequence $ a $ a merging sequence if it consists of exactly $ |x| $ zeros and exactly $ |y| $ ones in some order.

A merge $ z $ is produced from a sequence $ a $ by the following rules:

- if $ a_i=0 $ , then remove a letter from the beginning of $ x $ and append it to the end of $ z $ ;
- if $ a_i=1 $ , then remove a letter from the beginning of $ y $ and append it to the end of $ z $ .

Two merging sequences $ a $ and $ b $ are different if there is some position $ i $ such that $ a_i \neq b_i $ .

Let's call a string $ z $ chaotic if for all $ i $ from $ 2 $ to $ |z| $ $ z_{i-1} \neq z_i $ .

Let $ s[l,r] $ for some $ 1 \le l \le r \le |s| $ be a substring of consecutive letters of $ s $ , starting from position $ l $ and ending at position $ r $ inclusive.

Let $ f(l_1, r_1, l_2, r_2) $ be the number of different merging sequences of $ x[l_1,r_1] $ and $ y[l_2,r_2] $ that produce chaotic merges. Note that only non-empty substrings of $ x $ and $ y $ are considered.

Calculate $ \sum \limits_{1 \le l_1 \le r_1 \le |x| \\ 1 \le l_2 \le r_2 \le |y|} f(l_1, r_1, l_2, r_2) $ . Output the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example there are:

- $ 6 $ pairs of substrings "a" and "b", each with valid merging sequences "01" and "10";
- $ 3 $ pairs of substrings "a" and "bb", each with a valid merging sequence "101";
- $ 4 $ pairs of substrings "aa" and "b", each with a valid merging sequence "010";
- $ 2 $ pairs of substrings "aa" and "bb", each with valid merging sequences "0101" and "1010";
- $ 2 $ pairs of substrings "aaa" and "b", each with no valid merging sequences;
- $ 1 $ pair of substrings "aaa" and "bb" with a valid merging sequence "01010";

Thus, the answer is $ 6 \cdot 2 + 3 \cdot 1 + 4 \cdot 1 + 2 \cdot 2 + 2 \cdot 0 + 1 \cdot 1 = 24 $ .

## 样例 #1

### 输入

```
aaa
bb```

### 输出

```
24```

## 样例 #2

### 输入

```
code
forces```

### 输出

```
1574```

## 样例 #3

### 输入

```
aaaaa
aaa```

### 输出

```
0```

## 样例 #4

### 输入

```
justamassivetesttocheck
howwellyouhandlemodulooperations```

### 输出

```
667387032```

# 题解

## 作者：Fairicle (赞：15)

先来考虑**对整串 DP**。

设 $f[i][j]$ 表示 $x$ 串选到 $i$，$y$ 串选到 $j$ 的时候方案数。

考虑**相邻不相等的限制条件**，所以加入第三维表示这次选的是 $x$ 串的字符还是 $y$ 串的字符。

也就是说 $f[i][j][0]$ 表示 $x$ 串选到 $i$，$y$ 串选到 $j$ 的时候，最后一个选了 $x$ 串的第 $i$ 个字符的方案数；

$f[i][j][1]$ 表示 $x$ 串选到 $i$，$y$ 串选到 $j$ 的时候，最后一个选了 $y$ 串的第 $j$ 个字符的方案数。

如果暴力的话，就是对每对这种串计算一遍答案，全部加起来，复杂度显然是不可接受的。

考虑子串是怎样的。子串是从前面删一些字符，从后面删一些字符。

对于从后面删的部分，我们可以通过对每个 $f[i][j]$ 都统计答案表示它在这里已经结束。

对于从前面删的部分，我们可以通过在每个 $i,j$ 的位置都初始化一下，表示这个串从这里开始。

还有一点需要注意，只有 $x,y$ 中的字符都被选了才能算进答案。所以再加一维 $s$ 表示选过的集合，也就是一个两位的二进制数，只有这两位都为 $1$ 才会算进答案。 

看代码比较易于理解。

code：

```cpp
#define ll long long
#define ri register int
#define N 1010
char s[N],t[N];
int f[N][N][2][4],n,m;
inline int lowbit(int x){return x & ( - x ) ;}
#define mod 998244353
inline void add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(ri i=0;i<=n;++i)
	for(ri j=0;j<=m;++j){
        if(i<n) add(f[i+1][j][0][1],1);//初始化，加了新串
        if(j<m) add(f[i][j+1][1][2],1);//初始化，加了新串
        for(ri st=0;st<4;++st){
            if(i<n&&s[i]!=s[i+1]) add(f[i+1][j][0][st|1],f[i][j][0][st]);
            if(j<m&&s[i]!=t[j+1]) add(f[i][j+1][1][st|2],f[i][j][0][st]);
            if(i<n&&t[j]!=s[i+1]) add(f[i+1][j][0][st|1],f[i][j][1][st]);
            if(j<m&&t[j]!=t[j+1]) add(f[i][j+1][1][st|2],f[i][j][1][st]);
        }
    }
    int ans=0;
    for(ri i=1;i<=n;++i) for(ri j=1;j<=m;++j) add(ans,f[i][j][0][3]),add(ans,f[i][j][1][3]);//在i,j结束的串
    cout<<ans;
    return 0;
}

```


---

## 作者：walk_alone (赞：4)

提供另一种思考方法。

我们首先考虑一个最基础的 DP：定义 $f[l][i][r][j][k]$ 为 $x$ 串的 $[l,i]$ 子串与 $y$ 串的 $[r,j]$ 子串为研究对象，以 $k=0$ 时 以 $x$ 串中字符结束、以 $k=1$ 时 以 $y$ 串中字符结束时 构成的 chaotic 串数目。那么显然这个东西的转移是线性的，也是非常基础的：

1. 如果 $a[i+1]\neq a[i]$，则 $f[l][i+1][r][j][0]$ 可由 $f[l][i][r][j][0]$ 转移而来。

1. 如果 $a[i+1]\neq b[j]$，则 $f[l][i+1][r][j][0]$ 可由 $f[l][i][r][j][1]$ 转移而来。

1. 如果 $b[j+1]\neq a[i]$，则 $f[l][i][r][j+1][1]$ 可由 $f[l][i][r][j][0]$ 转移而来。

1. 如果 $b[j+1]\neq b[j]$，则 $f[l][i][r][j+1][1]$ 可由 $f[l][i][r][j][1]$ 转移而来。

同时有一些边界条件：（1）若其中一串为空，则不可从该串为末尾转移；（2）若 $z$ 串只有一个字符那么对应的 $f$ 应该为1。

其实我们很容易注意到一个事情：$l$ 和 $r$ 变量都在这个转移中并没有起到任何的作用；这个转移只与 $a[i+1]$ 与 $a[i],b[j]$、$b[j+1]$ 与 $a[i],b[j]$ 有关。因而，我们可以认为，这个相对关系是一种特殊的运算规则——它作用于所有合法的 $l,r$，并对其进行转移。因而，我们可以重新构造一个新的 DP 状态：$\displaystyle sum[i][j][k]= \sum_{s=1}^{i} \sum_{t=1}^{j} f[s][i][t][j][k]$。那么这个 $sum$ 仍然适用于上面的 $4$ 个方程。同时对于每一个 $i,j$，我们都会加 $1$，它代表了 $l=i,r=j$ 的新状态，用作第二边界条件。

但是我们显然容易注意到一个事情：在原始的 DP 转移方程中，我们允许某一串作为空串存在，作为第一边界条件的存在；而在这里，由于这个运算规则并不能作用于其中一串为空串，因而不能直接加入方程。但是如果不加入的话，这会导致答案的错误因为会少加一部分。

因而我们需要改进我们的 DP 状态：加入每个串是否为空，同时在转移的时候顺带维护串是否为空。（此处的处理参考了 Fairicle 的转移处理）

```cpp
for (int k = 0; k <= 3;k++)//直接枚举整体状态。对于不存在的情况，由于不会被转移到，因而恒为0，可以直接加上去不受影响。我们主要是做到这种情况不会被转移到。
{
	if(i<x && a[i+1]!=a[i])//x串后接x串
		f[i + 1][j][0][k | 1] = (f[i + 1][j][0][k | 1] + f[i][j][0][k]) % mod;
	if(i<x && a[i+1]!=b[j])//x串后接y串
		f[i + 1][j][0][k | 1] = (f[i + 1][j][0][k | 1] + f[i][j][1][k]) % mod;
	if(j<y && b[j+1]!=a[i])//y串后接x串
		f[i][j + 1][1][k | 2] = (f[i][j + 1][1][k | 2] + f[i][j][0][k]) % mod;
	if(j<y && b[j+1]!=b[j])//y串后接y串
		f[i][j + 1][1][k | 2] = (f[i][j + 1][1][k | 2] + f[i][j][1][k]) % mod;
}
```
在代码实现上基本没有大的创新，仅提供一种思想方法。

---

## 作者：Lynkcat (赞：2)

发一个略有区别的做法，本质应该一样。

设 $f(i,j,0/1/2)$ 表示两个串右端点分别在 $i$ 及之后和 $j$ 及之后的答案，$0/1/2$ 表示上一个序列上一个是 $0/1/$空 。这个过程可以动态规划求解，具体转移就是分成两部分加起来再加上 $1$ 。

想的不仔细一点就以为答案是 $\sum f(i,j,2)$ 了，但是其实并非如此，当第一个串指针一直不动或者第二个串指针一直不动的时候这些答案其实是不能算进去的，但是这里算进去了，这个时候只需要分别预处理一下从固定点往后能扩展多少，然后减去这两部分的答案即可，注意两个指针都不移动的情况减了两次，要 $+1$ 。

代码中的转移过程使用了记忆化搜索实现。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
#define N 1005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int s[N][N][5],vis[N][N][5],ans,b[N],c[N];
int n,m;
string st,st1;
int work(int x,int y,int ls)
{
	if (vis[x][y][ls]) return s[x][y][ls];
	vis[x][y][ls]=1;
	s[x][y][ls]=1; 
	char ch=' ';
	if (ls==0) ch=st[x-1];
	else if (ls==1) ch=st1[y-1];
	if (x+1<=n)
	{
		if (st[x]!=ch) s[x][y][ls]+=work(x+1,y,0),s[x][y][ls]%=mod;
	}
	if (y+1<=m)
	{
		if (st1[y]!=ch)
			s[x][y][ls]+=work(x,y+1,1),s[x][y][ls]%=mod;
	}
	return s[x][y][ls];
}
signed main()
{
	cin>>st>>st1;
	n=st.length(),m=st1.length();
	st=st+'8';st1=st1+'4';
	for (int i=0;i<=n;i++)
	{
		b[i]=1;
		for (int j=i+1;j<=n;j++)
		{	
			b[i]++;
			if (st[j]==st[j-1]) break;
		}
	}//预处理第一个串中固定点往后能扩展多少个状态 
	for (int i=0;i<=m;i++)
	{
		c[i]=1;
		for (int j=i+1;j<=m;j++)
		{	
			c[i]++;
			if (st1[j]==st1[j-1]) break;
		}
	}//预处理第二个串中固定点往后能扩展多少个状态 
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
		{
			ans=(ans+work(i,j,2))%mod;
			ans=(ans-c[j]+mod)%mod;
			ans=(ans-b[i]+mod)%mod;
			ans=(ans+1)%mod;
		}
	writeln(ans);
}
/*
*/

```

---

## 作者：double_zero (赞：1)

一个暴力是显然的，$f(i,j,k)$ 表示当前已经使用 $a$ 的前 $i$ 位，$b$ 的前 $j$ 位，最后一位是 $a$ 还是 $b$ 的。然后 $O(n^2)$ 枚举起点跑下去即可。为啥这个是对的呢？考虑每次转移都是加 $1/0$，显然之后在约束之下的转移本质不同。

第一眼我的想法是从如何对 $2$ 个整串入手，手玩了一下过程，显然考虑增量法构造，然后在写了这个 dp 后再证了正确性。由此可见先猜想后证明的重要性。但其实这个 dp 的状态设计是很显然的，考虑 LCS 的那个 dp 不难想到。抑或是通过增量法，从上一个状态的本质不同加以限制转移到当前状态的本质不同。值得学习！

但我们发现，起点仅仅只是关系到初始值，但期间的转移是固定的。也就是说，对于 $f(r,R)$ 它的起点可能很多，但是 $f(r,R)\to f(r+1,R) \ or \ f(r,R+1)$ 的是否可以转移都是不被起点的选择所影响的。于是，不难类矩阵加速的图论意义一样（限制转移多少次）类比到图上，发现即是一个多源的 DAG 拓扑问题，然后对 $2$ 个串都不能为空多加一维限制即可。然后就做完了。

在 debug 中可能会出现非超级源点所连的链的末尾是 $T$，虽然起点不能从超源获取权值，但是也需要跑，因为其间的点可能有权值，不然会影响 $T$ 的答案转移。

注意有点卡常，于是不能像其他 dp 做法一样使用 $[1,3]$ 来限定是否某方为空串，发现永远不会有末尾是 $T$ 但状态中表示只选 $S$ 的情况，于是只是用 $[0,1]$，表示当前是否只选择了当前末尾的这一类（即不是末尾的那个字符串选的是个空串）即可。

**998244353 莫 ```#define int long long```**

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define ADD(x,y) ((x+y>=mod)?x+y-mod:x+y)
using namespace std;
const int N=1002,mod=998244353;
bool bs;
char s[N],t[N];
int n,m,ans,S,T,tot,id[N][N][2][2];
int v[N*N*2*2],du[N*N*2*2];
queue<int>q;
vector<int>g[N*N*2*2];
bool bt;
void solve() {
	q.push(S); v[S]=1;
	for(int i=2;i<=tot;i++) if(!du[i]) q.push(i); 
	while(!q.empty()) {
		int x=q.front(); q.pop();
//		if(x==T) 
//		cout<<x<<" "<<v[x]<<'\n';
		for(int y:g[x]) {
			v[y]=ADD(v[x],v[y]);
			--du[y];
//			cout<<du[y]<<" "<<y<<'\n';
			if(!du[y]) q.push(y);
		}
	}
}

signed main() {
	cin.tie(0); ios::sync_with_stdio(false);
//	cout<<abs(&bs-&bt)/1024.0/1024.0;
	cin>>s+1>>t+1;
	n=strlen(s+1); m=strlen(t+1);
	S=++tot;
	for(int i=0;i<=n;i++) {
		for(int j=0;j<=m;j++) {
			for(int k=0;k<=1;k++) {
				for(int kk=0;kk<=1;kk++) {
					id[i][j][k][kk]=++tot;
				}
			}
			if(i>=1) {
				g[S].pb(id[i][j][0][0]);
				++du[id[i][j][0][0]];
			}
			if(j>=1) {
				g[S].pb(id[i][j][1][0]);
				++du[id[i][j][1][0]];
			}
		}
	}
	T=++tot;
	for(int i=0;i<=n;i++) {
		for(int j=0;j<=m;j++) {
//			if(i>=1) {
//				g[id[i][j][0][2]].pb(T);
//				++du[T];
//			}
			if(i>=1&&j>=1) {
				g[id[i][j][0][1]].pb(T);
				++du[T];
				g[id[i][j][1][1]].pb(T);
				++du[T];
			}
		}
	}
	for(int i=0;i<=n;i++) {
		for(int j=0;j<=m;j++) {
			if(i>=1) {
				if(i+1<=n&&s[i]!=s[i+1]) {
//					for(int k=1;k<=3;k++) {
//						if(k==2) continue ;
//						g[id[i][j][0][k]].pb(id[i+1][j][0][k|1]);
//						++du[id[i+1][j][0][k|1]];
//					}
					g[id[i][j][0][0]].pb(id[i+1][j][0][0]);
					++du[id[i+1][j][0][0]];
					if(j>=1) {
						g[id[i][j][0][1]].pb(id[i+1][j][0][1]);
						++du[id[i+1][j][0][1]];
					}
				}
				if(j+1<=m&&s[i]!=t[j+1]) {
//					for(int k=1;k<=3;k++) {
//						if(k==2) continue ;
//						g[id[i][j][0][k]].pb(id[i][j+1][1][k|2]);
//						++du[id[i][j+1][1][k|2]];
//					}
					g[id[i][j][0][0]].pb(id[i][j+1][1][1]);
					++du[id[i][j+1][1][1]];
					if(j>=1) {
						g[id[i][j][0][1]].pb(id[i][j+1][1][1]);
						++du[id[i][j+1][1][1]];
					}
				}
			}
			if(j>=1) {
				if(i+1<=n&&t[j]!=s[i+1]) {
//					for(int k=2;k<=3;k++) {
//						g[id[i][j][1][k]].pb(id[i+1][j][0][k|1]);
//						++du[id[i+1][j][0][k|1]];
//					}
					g[id[i][j][1][0]].pb(id[i+1][j][0][1]);
					++du[id[i+1][j][0][1]];
					if(i>=1) {
						g[id[i][j][1][1]].pb(id[i+1][j][0][1]);
						++du[id[i+1][j][0][1]];
					}
				}
				if(j+1<=m&&t[j]!=t[j+1]) {
//					for(int k=2;k<=3;k++) {
//						g[id[i][j][1][k]].pb(id[i][j+1][1][k|2]);
//						++du[id[i][j+1][1][k|2]];
//					}
					g[id[i][j][1][0]].pb(id[i][j+1][1][0]);
					++du[id[i][j+1][1][0]];
					if(i>=1) {
						g[id[i][j][1][1]].pb(id[i][j+1][1][1]);
						++du[id[i][j+1][1][1]];
					}
				}
			}
		}
	}
//	cout<<g[0].size()<<" "<<du[0]<<'\n';
	solve();
	cout<<v[T];
//	v[1]=1;
//	dfs(1);
//	cout<<v[T];
	return 0;
} 
```

---

## 作者：thostever (赞：1)

~~刚看到的时候 2400 下了我一跳~~

结果发现是道大水题。。。

直接令 $dp_{i,j}$ 表示 $\sum f(l_1,i,r_1,j)$。即以 $x_i$ 结尾的所有子串和以 $y_i$ 结尾的所有子串的生成混乱字符串的不同合并序列个数。（不太会解释）

由于要生成混乱字符串，所以我们在 dp 的最后添上一维 $0/1$，表示最后一个字符取得是 $x_i$ 还是 $y_i$。

考虑转移。我们以 $dp_{i,j,0}$ 为例：

1.它可以由 $dp_{i-1,j,0}$ 转移过来，前提是 $x_i\neq x_{i-1}$。

2.它可以由 $dp_{i-1,j,1}$ 转移过来，前提是 $x_i\neq y_j$。

3.考虑特殊情况，我们可以让 $x_i$ 只取一位（即子串长度只有 1 ），这样就可以由 $dp_{0,j,1}$ 转移过来，前提是 $x_i\neq y_j$ 且 $i>1$。（ $i>1$ 是因为初始化会导致多加一个，~~感性理解一下~~）

对于 $dp_{i,j,1}$ 来说，是同理的，此处不再列举。

答案便是 $\sum_{i=1}^n\sum_{j=1}^m dp_{i,j,0}+dp_{i,j,1}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m;
char a[1010],b[1010];
int dp[1010][1010][2];
signed main()
{
	cin>>a+1>>b+1;
	n=strlen(a+1); m=strlen(b+1);
	dp[1][0][0]=1; for(int i=2;i<=n;i++) dp[i][0][0]=(a[i]==a[i-1]?1:dp[i-1][0][0]+1);
	dp[0][1][1]=1; for(int j=2;j<=m;j++) dp[0][j][1]=(b[j]==b[j-1]?1:dp[0][j-1][1]+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i]!=a[i-1]) dp[i][j][0]+=dp[i-1][j][0];
			if(a[i]!=b[j]) dp[i][j][0]+=dp[i-1][j][1];
			if(i>1&&a[i]!=b[j]) dp[i][j][0]+=dp[0][j][1];
			if(b[j]!=b[j-1]) dp[i][j][1]+=dp[i][j-1][1];
			if(a[i]!=b[j]) dp[i][j][1]+=dp[i][j-1][0];
			if(j>1&&a[i]!=b[j]) dp[i][j][1]+=dp[i][0][0];
			dp[i][j][0]%=mod; dp[i][j][1]%=mod;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) ans+=dp[i][j][0]+dp[i][j][1],ans%=mod;
	cout<<ans;
	return 0;
}
```


---

## 作者：Richard_Whr (赞：0)

比较套路的东西。

先考虑固定两个串怎么做：

设 $f_{i,j,0/1}$ 表示当前放了前 $i$ 个，前 $j$ 个，最后一个是哪个串的，转移是简单的。

初始值有小细节，注意到要求非空，但其实只有一个串的时候是好算的，我们直接跳过空串期直接进入同时存在的情况，这样 $f_{i,j,0}=g2_j[s_i\not=t_j]$，其中 $g2_j$ 表示只有第二个串的时候能不能一直放到 $j$。$f_{i,j,1}$ 同理。

那么我们枚举所有起点，在所有终点统计答案即可。

注意到本质上是统计所有从 $(p_1,p_2)$ 到 $(t_1,t_2)$ 的合法路径数量，直接合并在一起算就行了、

初始值还有小细节，我们得统计所有可能的起点单串情况，也就是在 $j$ 的时候算 $\sum g2_{i,j}$，直接递推就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,mod=998244353;
char s[N],t[N];
int f[N][N][2];
int s1[N],s2[N];
int n,m;

void Add(int &a,int b)
{
	if(a+b>=mod) a=a-mod+b;
	else a=a+b;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>(s+1)>>(t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++) 
	{
		if(s[i]!=s[i-1]) s1[i]=s1[i-1]+1;
		else s1[i]=1;
	}
	for(int i=1;i<=m;i++) 
	{
		if(t[i]!=t[i-1]) s2[i]=s2[i-1]+1;
		else s2[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[i][j][0]=(s[i]!=t[j])*(s2[j]);
			f[i][j][1]=(s[i]!=t[j])*(s1[i]);
		}
	}
	
	int res=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			Add(f[i][j][0],f[i-1][j][0]*(s[i]!=s[i-1]));
			Add(f[i][j][0],f[i-1][j][1]*(s[i]!=t[j]));
			Add(f[i][j][1],f[i][j-1][0]*(t[j]!=s[i]));
			Add(f[i][j][1],f[i][j-1][1]*(t[j]!=t[j-1]));
			Add(res,f[i][j][0]);
			Add(res,f[i][j][1]);
		}
	}
	
	cout<<res<<"\n";
	
	return 0;
}
```

---

## 作者：sinsop90 (赞：0)

考虑到对于一个区间对 $P = ((l_1, r_1), (l_2, r_2))$ 到 $((l_1, r_1 + 1), (l_2, r_2))$ 或 $((l_1, r_1), (l_2, r_2+1)$ 的转移只关心该区间对合并序列的最后一个字母和 $x_{r_1}, y_{r_2}$，假设合并序列最后一个字母为 $T_p$，达成该要求的方案数为 $G_p$，则设 $f_{i, j, k} = \sum_{P_{r_1} = i, P_{r_2} = j, T_P = k}G_P$。

转移方式类似于 $LCP$ 的转移，我们只需要比较当前字母和状态中的 $k$ 即可。注意到这样会算多，多的是选出的两个子串中有空串的情况，最后减掉即可。

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005, mod = 998244353;
char s[maxn], t[maxn];
int n, m, f[maxn][maxn][35], ans;
void add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}
int main() {
	cin >> s + 1;
	cin >> t + 1;
	n = strlen(s + 1), m = strlen(t + 1);
	f[0][0][26] = 1;
	for(int i = 0;i <= n;i++) {
		for(int j = 0;j <= m;j++) {
			if(!i && !j) continue;
			for(int k = 0;k <= 26;k++) {
				if(s[i] - 'a' != k && i) add(f[i][j][s[i] - 'a'], f[i - 1][j][k]);
				if(t[j] - 'a' != k && j) add(f[i][j][t[j] - 'a'], f[i][j - 1][k]);
			}
			add(f[i][j][26], 1);
			for(int k = 0;k <= 25;k++) add(ans, f[i][j][k]);
		}
	}
	for(int i = 1;i <= n;i++) {
		int now = i;
		while(now < n && s[now + 1] != s[now]) now ++;
		ans = (ans - 1ll * (now - i + 1) * (m + 1) % mod + mod) % mod;
	}
	for(int i = 1;i <= m;i++) {
		int now = i;
		while(now < m && t[now + 1] != t[now]) now ++;
		ans = (ans - 1ll * (now - i + 1) * (n + 1) % mod + mod) % mod;
	}
	cout << ans << '\n';
}
```


---

## 作者：lsj2009 (赞：0)

### Solution

很厉害的 dp 题。

先考虑 $l_1=l_2=1$ 时怎么做。

考虑设 $f_{i,j,0/1}$ 表示当前串 $1$ 选到第 $i$ 个数，串 $2$ 选到第 $j$ 个数，且最后一个是串 $1$ 还是串 $2$ 的方案总数。

转移方程显然，这里不多赘述。

那么 $l_1,l_2\ne 1$ 时怎么做呢？我们不妨考虑令 $f_{i+1,j,0}$ 和 $f_{i,j+1,1}$ 初始时全部加 $1$，这样子就相当于我们给每个串都钦定了一个新的开头！

但是这样子有个问题就是，题目要求第一个串选出的字串和第二个串选出的子串非空，但是我们这里可能会出现一直挪第一个串结尾/第二个串结尾的情况，从而使得某个串为空怎么办？事实上，这是简单的，我们再多开一维 $s$，状压一下，表示第一个串和第二个有没有挪过就可以了。

复杂度 $\Theta(n^2)$，其于细节详见代码。


### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e3+5,MOD=998244353;
int f[N][N][2][4];
char s[N],t[N];
void add(int &a,int b) {
    a+=b;
    if(a>=MOD)
        a-=MOD;
}
signed main() {
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	rep(i,0,n) {
		rep(j,0,m) {
			if(i!=n)
				add(f[i+1][j][0][1],1);
			if(j!=m)
				add(f[i][j+1][1][2],1);
			rep(S,0,3) {
				if(i!=n&&s[i]!=s[i+1])
					add(f[i+1][j][0][S|1],f[i][j][0][S]);
				if(i!=n&&t[j]!=s[i+1])
					add(f[i+1][j][0][S|1],f[i][j][1][S]);
				if(j!=m&&s[i]!=t[j+1])
					add(f[i][j+1][1][S|2],f[i][j][0][S]);
				if(j!=m&&t[j]!=t[j+1])
					add(f[i][j+1][1][S|2],f[i][j][1][S]);
			}
		}
	}
	int res=0;
	rep(i,1,n) {
		rep(j,1,m)
			add(res,(f[i][j][0][3]+f[i][j][1][3])%MOD);
	}
	printf("%d\n",res);
    return 0;
}

```

---

## 作者：guosoun (赞：0)

[博客](https://gzy-blog.pages.dev/posts/cf1499e-chaotic-merge-%E9%A2%98%E8%A7%A3/)

定义 $dp(i,j,0)$ 表示：生成出的混乱的字符串中，**$x$ 串和 $y$ 串都出现过字符**，且最后一个来自 $x$ 串的字符是 $x_i$，最后一个来自 $y$ 串的字符是 $y_j$，并且这个混乱的字符串最后一个字符来自 $x$ 串的混乱字符串数量。

定义 $dp(i,j,1)$ 表示：（前面同上）……并且这个混乱的字符串最后一个字符来自 $y$ 串的混乱字符串数量。
$$
ans=\sum_{i=1}^n\sum_{j=1}^mdp(i,j,0)+dp(i,j,1)
$$
考虑 $dp(i,j,0)$ 的转移，$dp(i,j,1)$ 同理。

当前状态是 $dp(i,j,0)$，这代表着合并字符串最后一个字符一定是 $x_i$，去掉 $x_i$ 之后，**若还有来自 $x$ 串的字符**，则最大的一定是 $x_{i-1}$，所以 $dp(i,j,0)$ 一定会从 $dp(i-1,j,0)$ 或 $dp(i-1,j,1)$ 转移。

来自考虑生成串前一个字符是什么：

- 如果前一个字符也来自 $x$ 串，则生成串前一个字符一定是 $x_{i-1}$；

   为了保证混乱，只有在 $x_{i}\neq x_{i-1}$ 进行转移，$dp(i,j,0)\gets dp(i,j,0)+dp(i-1,j,0)$。

- 如果前一个字符来自 $y$ 串，则生成串前一个字符一定是 $y_{j}$；

   为了保证混乱，只有在 $x_i\neq y_j$ 进行转移，$dp(i,j,0)\gets dp(i,j,0)+dp(i-1,j,1)$

只有这些情况吗？考虑 $dp(i,j,0)$ 去掉 $x_i$ 之后，没有来自 $x$ 的字符了，即 $x_i$ 是生成串中唯一来自 $x$ 的字符，删掉则生成串只由 $y$ 组成了，注意到 $dp$ 的定义中，不允许生成串由单独 $x$ 或 $y$ 组成，所以这种情况无法通过 $dp$ 数组推得。

考虑预处理 （方式~~自己想~~后面再将）：

- $fx(i)$ 表示生成串只由 $x$ 串组成，且后一个字符是 $x_i$ ，生成的混乱字符串数量。

- $fy(i)$ 表示生成串只由 $y$ 串组成，且后一个字符是 $y_i$ ，生成的混乱字符串数量。

我们可以通过他俩来求得上面 $dp(i,j,0)$ 转移中少考虑的情况：

如果 $x_i\neq y_j$ ，则 $dp(i,j,0)\gets dp(i,j,0)+fy(j)$，代表着 $dp(i,j,0)$ 中**只有**最后一个字符来自 $x$ 串的情况。

---

关于预处理 $fx(i)$：

- 如果 $x_i\neq x_{i-1}$，则所有 $fx(i-1)$ 的串都可以加上 $x_i$，当然也可以只由 $x_i$ 一个字符组成， $fx(i)\gets fx(i-1)+1$；
- 如果 $x_i= x_{i-1}$，则生成串只能有 $x_i$ 一个字符，再往前多选一个都不行， $fx(i)\gets 1$；

$fy$ 同理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,p=998244353;
int dp[N][N][2],n,m,fx[N],fy[N],ans;
char x[N],y[N];
int main(){
    cin>>(x+1)>>(y+1);
    int n=strlen(x+1),m=strlen(y+1);
    for(int i=1;i<=n;i++) (x[i]!=x[i-1])?fx[i]=fx[i-1]+1:fx[i]=1;
    for(int i=1;i<=m;i++) (y[i]!=y[i-1])?fy[i]=fy[i-1]+1:fy[i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //求dp[i][j][0]
            if(x[i]!=y[j])dp[i][j][0]+=fy[j],dp[i][j][0]%=p;

            if(x[i-1]!=x[i]) dp[i][j][0]+=dp[i-1][j][0],dp[i][j][0]%=p;
            if(y[j]!=x[i]) dp[i][j][0]+=dp[i-1][j][1],dp[i][j][0]%=p;

            //求dp[i][j][1]
            if(x[i]!=y[j]) dp[i][j][1]+=fx[i],dp[i][j][1]%=p;
            
            if(x[i]!=y[j]) dp[i][j][1]+=dp[i][j-1][0],dp[i][j][1]%=p;
            if(y[j-1]!=y[j]) dp[i][j][1]+=dp[i][j-1][1],dp[i][j][1]%=p;
            
            ans+=(dp[i][j][0]+dp[i][j][1])%p;ans%=p;
        }
    }
    cout<<ans<<'\n';
}


---

