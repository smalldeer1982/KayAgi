# Sharing Chocolate

## 题目描述

（摘自《算法竞赛入门经典训练指南》，刘汝佳 陈峰 著）

给出一块长为 $x$, 宽为 $y$ 的矩形巧克力，每次操作可以沿一条直线把一块巧克力切割成两块长宽均为整数的巧克力（一次不能同时切割多块巧克力）。 

问：是否可以经过若干次操作得到 $n$ 块面积分别为 $a_1, a_2, ..., a_n$ 的巧克力。

## 样例 #1

### 输入

```
4
3 4
6 3 2 1
2
2 3
1 5
0```

### 输出

```
Case 1: Yes
Case 2: No```

# 题解

## 作者：CreeperLordVader (赞：9)

我先看的LRJ的书再写的，中间写不出来了自己推的。。。

所以我只是题解的搬运工

### LRJ说，对于此题，很多状态其实都是不合法的,因此，如果我们用记忆化搜索作为DP框架，实际上可以剪去许多不合法的决策，只搜索合法的决策

设$ d(x,S) $为当巧克力的较短边长为$ x $,切出的面积集合为$ S $的可行性

则可以发现，状态$ d(x,S) $可行，当且仅当

$S$的面积能整除$ x $(以下直接使用集合来代替集合的面积)

存在$ S_0 \in S$且$S_0$的面积可整除$x$且$S_0$切成的两块都合法

设$x*y_0==S_0$    
$ x*y==S$

即$ d(y_0,S_0) ==1$且$d(y-y_0,S-S_0)$

需要注意的是，状态的定义中$x$是较小的边，所以要在作为递归参数传递前要和$y_0$取$min$

这是横着切，竖着切同理，这里不列出

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,kase,r,c;
int a[16],sum[1<<16];
int d[101][1<<16];
bool vis[101][1<<16];
bool ans;
bool read(int& x)
{
	char c=getchar();
	x=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int bitcount(int s)
{
	int cnt=0;
	while(s)
	{
		if(s&1)cnt++;
		s>>=1;
	}
	return cnt;
}
bool dp(int x,int s)
{
	if(vis[x][s])return d[x][s];
	vis[x][s]=1;
	if(bitcount(s)==1)return d[x][s]=1;
	int y=sum[s]/x;
	for(int s0=(s-1)&s;s0;s0=(s0-1)&s)
	{
		int x0=sum[s0]/y;
		int y0=sum[s0]/x;
		int x1=sum[s^s0]/y;
		int y1=sum[s^s0]/x;
		if(!(sum[s0]%x)&&dp(min(x,y0),s0)&&dp(min(x,y1),s^s0))return d[x][s]=1;
		if(!(sum[s0]%y)&&dp(min(x0,y),s0)&&dp(min(x1,y),s^s0))return d[x][s]=1;
	}
	return d[x][s]=0;
}
int main()
{
	while(read(n))
	{
		read(r);
		read(c);
		if(r>c)swap(r,c);
		memset(vis,0,sizeof(vis));
		memset(d,0,sizeof(d));
		memset(sum,0,sizeof(sum));
		for(int i=0;i<n;i++)read(a[i]);
		for(int s=0;s<(1<<n);s++)
			for(int i=0;i<n;i++)
				if(s&(1<<i))sum[s]+=a[i];
		if(sum[(1<<n)-1]!=r*c||sum[(1<<n)-1]%r)ans=0;
		else ans=dp(r,(1<<n)-1);
		printf("Case %d: ",++kase);
		ans?printf("Yes\n"):printf("No\n");
	}
}
```


---

## 作者：Prurite (赞：2)

这道题算是一个比较好的记忆化搜索+状压的例子吧。

## 题目大意

现有一块大小为 $x*y$ 的巧克力，每次切了之后切成的两块必须都是矩形，问能否把它切成大小分别为 $a_1, a_2, ..., a_n$ 的 $n$ 块（没有剩余）。

## 分析与解

### 思想

**状压，记忆化搜索，转化（逆向思考）**

### 思路

因为此题要切成的块数较少，我们可以采用状态压缩的思想进行解题。

> 为表述清晰，设 `集合m` 表示经过状压之后构成的数为 $m$ 表示的选的块的集合，`矩形m` 表示由集合 $m$ 中的块组成的矩形。

容易想到的是，首先进行一次特判，如果要求切成的总面积不等于当前巧克力的总面积，直接输出 `No` 。

因为此题涉及到切分，不便处理，我们可以将其转化为“拼接”，递归地进行搜索时从小向大进行处理。

首先预处理出 `s[m]` 表示集合 $m$ 中所有块的面积和，用 `dp[a][m]` 表示集合 $m$ 中的块是否可以组成宽为 $a$ 的矩形。记忆化搜索时，我们可以设集合 $m$ 是由集合 $m_1$ 和$m_2$ 组成的，表示当前我们假设矩形 $m$ 是由矩形 $m_1$ 和矩形 $m-m_1$ 组合而成的，然后查询矩形 $m_1$ 和矩形 $m_2$ 是否存在，如果存在，就表明矩形 $m$ 存在。边界条件：当集合 $m$ 里只存在一个块时，显而易见地矩形 $m$ 存在。注意枚举的时候考虑横向组合和纵向组合两种情况。

这道题涉及到的一种比较巧妙的思路就是当我们**使用二进制数表示集合时枚举子集和补集的方法**。设 $m$ 表示集合 $S$ ，则
```
for ( int m1=(m-1)&m; m1; m1=(m1-1)&m )
```
时 $m_1$ 是可以遍历到 $m$ 的所有子集的。又设 $m_2$ 是 $m$ 的一个子集，则 $m-m_2$ 是它的补集。具体证明可以手推一下。

（作者未正式学过集合，书写不规范之处敬请谅解。）

## 代码
```cpp
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=15, MAXL=100+1;
int dp[MAXL][1<<MAXN];
int s[1<<MAXN];
int c[MAXN]; // c[i]表示第i块的面积
int n;

inline int digit( int x )
{
	int ans=0;
	for ( int i=0; i<31; i++ )
		if ( x&1<<i )
			ans++;
	return ans;
}
inline int min( int a, int b ) { return a<b?a:b; }

inline int dfs( int a, int m );

int main( )
{
	int T1=0;
	while ( ~scanf( "%d", &n ) && n!=0 )
	{
		T1++;
		memset( s, 0, sizeof s );
		memset( dp, -1, sizeof dp );
		int a, b;
		scanf( "%d %d", &a, &b );
		for ( int i=1; i<=n; i++ )
			scanf( "%d", &c[i] );
		for ( int m=0; m<1<<n; m++ )
			for ( int i=1; i<=n; i++ )
				if ( m&1<<i-1 )
					s[m]+=c[i];
		if ( s[(1<<n)-1]!=a*b || s[(1<<n)-1]%a!=0 )
			dp[a][(1<<n)-1]=0;
		else
			dfs( a, (1<<n)-1 );
		printf( "Case %d: %s\n", T1, dp[a][(1<<n)-1] ? "Yes" : "No" );
	}
	return 0;
}

inline int dfs( int a, int m )
{
	int b=s[m]/a;
	if ( dp[a][m]!=-1 ) // 如果已经搜索过了
		return dp[a][m];
	if ( digit( m )==1 ) // 如果m里只有一个块
		return dp[a][m]=1;
	for ( int m1=(m-1)&m; m1!=0; m1=(m1-1)&m )
	{
		int s1=s[m1];
		if ( s1%a==0 ) // m1的面积能被宽整除，相当于在长上切开
			if ( dfs( min( a, s1/a ), m1 ) && dfs( min( a, b-s1/a ), m-m1 ) )
//			如果两个小矩形都存在
				return dp[a][m]=1;
		if ( s1%b==0 ) // m1的面积能被长整除，相当于在宽上切开
			if ( dfs( min( b, s1/b ), m1 ) && dfs( min( b, a-s1/b ), m-m1 ) )
				return dp[a][m]=1;
	}
	return dp[a][m]=0;
}
```
[提交记录](https://www.luogu.org/recordnew/show/8556444)

---

## 作者：Stinger (赞：1)

这道题一看 $n\leq 15$，状压DP无疑了……

我们可以设出一个显而易见的状态：$f[x][y][s]$ 表示在 $x\times y$ 的矩形中分成 $s$ 中的每一块巧克力是否可行。

这样空间显然会炸，我们可以发现，$f$ 数组中保存了太多的无用状态——有了 $x$ 和 $s$，$y$ 就可以唯一确定了。这样只需要用 $f[x][s]$ 表示在一条边长为 $x$ 的矩形中分成 $s$ 中的每一块巧克力是否可行即可。这样数组大小缩到了3276800，还是bool数组，稳过。

为了方便计算矩形的另一条边长，我们可以预处理出 $Sum[s]$ 数组表示 $S$ 中的巧克力的总面积。

方程很好列了，枚举子集 $s0$ 再判断是否能整除即可。详见代码。

**~~另外希望大家不要忘了register与inline的重要性！论怎样不开O2卡进最优解。~~**

# $Code:$

```cpp
#include <cstdio>
#include <cstring>
#include <cassert>
#define min(x, y) (x < y ? x : y)

int Sum[1 << 15], A[16], n, x, y, sum;
bool f[105][1 << 15], Visit[105][1 << 15], flag[1 << 15];

inline bool scan() {
	sum = 0;
	scanf("%d", &n);
	if (n == 0) return false;
	scanf("%d%d", &x, &y);
	for (register int i(1); i <= n; ++ i) scanf("%d", A + i), sum += A[i]; 
	memset(f, false, sizeof(f));
	memset(flag, false, sizeof(flag));
	memset(Visit, false, sizeof(Visit));
	memset(Sum, 0, sizeof(Sum));
	for (register int s(1); s < 1 << n; ++ s)
	for (register int i(0); i < n; ++ i) if (s & 1 << i) Sum[s] += A[i + 1];
	for (register int i(0); i < n; ++ i) flag[1 << i] = true;
	return true;
}

inline bool dfs(int x, int s) {
	if (Visit[x][s]) return f[x][s];
	if (Visit[Sum[s] / x][s]) return f[Sum[s] / x][s];//能让搜索量减半的东西，不用每次取min，这里加一行就好了。
	Visit[x][s] = true;
	if (flag[s]) return f[x][s] = true;
	register int y(Sum[s] / x);
	for (register int s0(s - 1 & s); s0; s0 = s0 - 1 & s) {
		if (!(Sum[s0] % x) && dfs(x, s0) && dfs(x, s ^ s0)) return f[x][s] = true;
		if (!(Sum[s0] % y) && dfs(y, s0) && dfs(y, s ^ s0)) return f[x][s] = true;
	}
	return f[x][s];
}

int main() {
	int kase(0);
	while (scan())
		printf("Case %d: ", ++ kase),
		puts(!(sum % x) && sum == x * y && dfs(x, (1 << n) - 1) ? "Yes" : "No");
}
```

---

