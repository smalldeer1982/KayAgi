# Parking Lot

## 题目描述

Petya's been bored at work and he is killing the time by watching the parking lot at the office. The parking lot looks from above like an $ n×m $ table (a cell of the table corresponds to a single parking spot). Some spots in the parking lot are taken, others are empty.

Petya watches cars riding into the parking lot one by one. After a car settles down at the parking spot, Petya amuzes himself by counting what maximum square of empty spots (i.e. a square subtable) can be seen on the parking lot if we look at it from above. Also, he takes notes of the square's size (side length) in his notebook.

You task is: given the state of the parking lot at the initial moment of time and the information about where the arriving cars park, restore what Petya wrote in his notebook. It is midday, so nobody leaves the lot.

## 样例 #1

### 输入

```
7 8 4
........
X.....X.
........
........
.X......
........
........
1 5
6 4
3 5
4 6
```

### 输出

```
5
4
4
3
```

# 题解

## 作者：Ace_FutureDream (赞：4)

观察到答案单调不升，并且求直接答案非常困难，感觉非常难受，所以直接离线。毕竟考虑加一个限制所带来的贡献是比删一个限制所带了的贡献难求的多。

显然我们可以发现一个很好的性质：若删掉这调限制能够更新答案，那么最大的正方形**一定**包含这个点。

现在的问题变成了如何快速求得最大的正方形。考虑 $\text{dp}$，$f_{i,j}$ 表示点 $(i,j)$ 最多能向下拓展多少格，$g_{i,j}$ 表示最多能向上覆盖多少格。

处理出这个有什么用呢？考虑将求最值问题转化为判定类问题。那么如何判定边长为 $x$ 的正方形，最暴力的办法是直接枚举第 $i$ 行，并枚举右端点 $j$，如果存在一个区间 $[j-x+1,j]$ 使得 $\min\limits_{k=j-x+1}^j f_{i,k}+\min\limits_{k=j-x+1}^j g_{i,k}-1\ge x$，则存在一个边长为 $x$ 正方形。解释一下这个式子，显然最大能向上/下拓宽的长度就是这两个东西的和，减一是因为自己多算了一遍。

观察这个东西，需要 $O(n\times m^2)$ 的时间才能求出来，再乘上一个 $k$，复杂度直接爆炸。

不过还记得之前很好的性质吗，因为更新后最大的正方形一定包含这个点，所以我们可以直接钦定 $i$ 为上一次操作的 $x$。然后再配合上单调队列优化，我们可以做到 $O(n)$ 完成判定。

那么我们暴力从 $0$ 枚举 $ans$，直到没有更大的正方形为止，那么枚举 $ans$ 的复杂度为均摊 $O(\min(n,m))$。每次操作更新 $\text{dp}$ 数组的复杂度为 $O(k\times n)$，预处理 $\text{dp}$ 数组 $O(n\times m)$。所以最终复杂度为 $O(n^2)$（假定 $n,m,k$ 同阶）。

## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[2010][2010];
int f[2010][2010];
int g[2010][2010];
int x[2010],y[2010];
int tmp1[2010],tmp2[2010];
int n,m,k;
bool check(int x,int i,int id){
	memset(tmp1,0,sizeof(tmp1));//f的区间最小值 
	memset(tmp2,0,sizeof(tmp2));//g的区间最小值 
	deque<int>q;
	for(int j=1;j<x;j++)q.push_back(j);
	for(int j=1;j<=m;j++){
		while(!q.empty()&&q.front()<j-x+1)q.pop_front();
		while(!q.empty()&&f[i][q.back()]>=f[i][j])q.pop_back();
		q.push_back(j);
		if(j>=x)
			tmp1[j]=f[i][q.front()];
	}
	q.clear();
	for(int j=1;j<=m;j++){
		while(!q.empty()&&q.front()<j-x+1)q.pop_front();
		while(!q.empty()&&g[i][q.back()]>=g[i][j])q.pop_back();
		q.push_back(j);
		if(j>=x)
			tmp2[j]=g[i][q.front()];
	}
	//单调队列判定 
	for(int j=1;j<=m;j++){
		if(tmp1[j]+tmp2[j]-1>=x)
			return true;
	}
	return false;
}
int qw[2010];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;
			cin>>c;
			a[i][j]=(c=='X');
		}
	}
	for(int i=1;i<=k;i++){
		cin>>x[i]>>y[i];
		a[x[i]][y[i]]=1;
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			if(a[i][j])f[i][j]=0;
			else f[i][j]=f[i+1][j]+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j])g[i][j]=0;
			else g[i][j]=g[i-1][j]+1;
		}
	}
	//预处理f,g 
	int ans=0;
	for(int i=1;i<=n;i++)
		while(check(ans+1,i,i))ans++;
	for(int i=k;i>=1;i--){
		while(check(ans+1,x[i+1],i))ans++;
		qw[i]=ans;
		a[x[i]][y[i]]=0;
		for(int j=n;j>=1;j--){
			if(a[j][y[i]])f[j][y[i]]=0;
			else f[j][y[i]]=f[j+1][y[i]]+1;
		}
		for(int j=1;j<=n;j++){
			if(a[j][y[i]])g[j][y[i]]=0;
			else g[j][y[i]]=g[j-1][y[i]]+1;
		}
		//更新f,g 
	}
	for(int i=1;i<=k;i++)cout<<qw[i]<<'\n';
	return 0;
}
```

---

## 作者：crashed (赞：4)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF480E)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到这种单向修改并且答案随修改具有单调性的题，我们可以考虑离线下来询问，以保证答案是递增的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以我们把整道题离线，并且倒着处理这个问题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先可以把最终状态的方格的形态处理出来，并且一个$DP$扫出最后的最大正方形。所以我们知道了最后一次修改后的答案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑进行一次修改。此时修改总是由$'X'$变$'.'$。所以此时的倒着做的答案必然是递增的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;显然，此时新出的答案的正方形的行范围必然包含了当前操作的那一行。所以我们可以考虑扫描那一行，并且计算出这一行上最大正方形的大小，与原来的答案进行比较得到新的答案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑“悬线法”。我们预处理出两个函数$f$和$g$。$f(i,j)$表示$(i,j)$向上的连续空格子的长度；$g(i,j)$表示向下的。如果当前格子没被占，两个函数都应该算上自己这一格。每一次修改需要维护一下$f$和$g$。可以发现，只有当前修改的这一列的会被改，所以时间是$O(nk)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑计算新的答案。设当前行为$X$。对于区间$[l,r]$，我们要求的就是最长的区间，并且满足$\min_{l\le i\le r}\{f(X,i)\}+\max_{l\le i\le r}\{g(X,i)\}\ge r-l+2$。如果区间的长度确定，不等式右边就为区间长度$+1$，不等式左边可以扫一遍区间然后单调队列维护。所以考虑二分区间长度，然后按照上述方法检查答案。时间$O(kn\log_2n)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;类似的，我们可以用尺取法把$O(\log_2n)$优化掉，所以本题的最优时间就是$O(nk)$。（我写的$O(nk+kn\log_2n)$）  
# 代码
```cpp
#include <cstdio>

const int MAXN = 2005, MAXM = 2005, MAXK = 2005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct deque
{
	int q[MAXN];
	int h, t;
	deque() { h = 1, t = 0; }
	void clear() { h = 1, t = 0; }
	int front() const { return q[h]; }
	int back() const { return q[t]; }
	void push_front( const int val ) { q[--h] = val; }
	void push_back( const int val ) { q[++t] = val; }
	void pop_front() { h ++; }
	void pop_back() { t --; }
	bool empty() const { return h > t; }
}deq1, deq2;

int DP[MAXN][MAXM];
int up[MAXN][MAXM], down[MAXN][MAXM];
int x[MAXN], y[MAXN], ans[MAXN];
int N, M, K;
char tmp[MAXN];
bool mp[MAXN][MAXN];

bool chk( const int x, const int len )
{
	deq1.clear(), deq2.clear();
	for( int i = 1 ; i < len ; i ++ )
	{
		while( ! deq1.empty() && up[x][deq1.back()] >= up[x][i] ) deq1.pop_back();
		deq1.push_back( i );
		while( ! deq2.empty() && down[x][deq2.back()] >= down[x][i] ) deq2.pop_back();
		deq2.push_back( i );
	}
	for( int i = len ; i <= M ; i ++ )
	{
		while( ! deq1.empty() && deq1.front() <= i - len ) deq1.pop_front();
		while( ! deq2.empty() && deq2.front() <= i - len ) deq2.pop_front();
		while( ! deq1.empty() && up[x][deq1.back()] >= up[x][i] ) deq1.pop_back();
		deq1.push_back( i );
		while( ! deq2.empty() && down[x][deq2.back()] >= down[x][i] ) deq2.pop_back();
		deq2.push_back( i );
		if( up[x][deq1.front()] + down[x][deq2.front()] - 1 >= len ) return true;
	}
	return false;
}

int main()
{
	read( N ), read( M ), read( K );
	for( int i = 1 ; i <= N ; i ++ )
	{
		scanf( "%s", tmp + 1 );
		for( int j = 1 ; j <= M ; j ++ ) mp[i][j] = tmp[j] == 'X';
	}
	for( int i = 1 ; i <= K ; i ++ )
		read( x[i] ), read( y[i] ), mp[x[i]][y[i]] = true;
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= M ; j ++ )
		{
			up[i][j] = mp[i][j] ? 0 : up[i - 1][j] + 1;
			down[N - i + 1][j] = mp[N - i + 1][j] ? 0 : down[N - i + 2][j] + 1;
		}
	int res = 0;
	for( int i = 1 ; i <= N ; i ++ ) DP[i][1] = ! mp[i][1], res = MAX( res, DP[i][1] );
	for( int i = 1 ; i <= M ; i ++ ) DP[1][i] = ! mp[1][i], res = MAX( res, DP[1][i] );
	for( int i = 2 ; i <= N ; i ++ )
		for( int j = 2 ; j <= M ; j ++ )
			DP[i][j] = mp[i][j] ? 0 : MIN( DP[i - 1][j - 1], MIN( DP[i - 1][j], DP[i][j - 1] ) ) + 1,
			res = MAX( res, DP[i][j] ); 
	ans[K] = res;
	int l, r, mid;
	for( int k = K ; k ; k -- )
	{
		mp[x[k]][y[k]] = false;
		for( int i = 1 ; i <= N ; i ++ )
		{
			up[i][y[k]] = mp[i][y[k]] ? 0 : up[i - 1][y[k]] + 1;
			down[N - i + 1][y[k]] = mp[N - i + 1][y[k]] ? 0 : down[N - i + 2][y[k]] + 1;
		}
		l = 0, r = M;
		while( r - l > 1 )
		{
			mid = ( l + r ) >> 1;
			if( chk( x[k], mid ) ) l = mid;
			else r = mid - 1;
		}
		if( chk( x[k], r ) ) res = MAX( res, r );
		else res = MAX( res, l );
		ans[k - 1] = res; 
	}
	for( int i = 1 ; i <= K ; i ++ )
		write( ans[i] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：2)

[My Blog](https://www.cnblogs.com/lyttt/p/14039264.html)

[题目链接](http://codeforces.com/problemset/problem/480/E)

### 题目解析

~~被拿来作为考试题，我以为我会做来着，然而并不会（怎么好多人都做过这道题，果然是我太菜了嘤嘤嘤~~

（三种做法的代码都放在了最后面

#### 法一

如果你什么都不会，就像我一样，那么可以先敲出一个大暴力出来。

$a[i][j]$表示点$(i,j)$前面一列最大的连续空地长度，然后$n^2$枚举每个点作为正方形左上角，再枚举一个变量表示往右边延伸多少，一边枚举一边判断。

~~（其实是因为想起了 [这道题](https://blog.csdn.net/CQBZLYTina/article/details/99227832)~~

容易发现，这种方法求答案是$n^3$的（虽然普通情况下不会跑满，加上询问总时间复杂度$n^4$

然后你就得到了$20pts$的好成绩~~（要知道全场只有我一个人得到了这个奇怪的分数~~

考场上尝试优化，因为每次修改一个点之后，只有这个点周围的答案会改变，因为这个点可能把原来的答案正方形劈成很多半。但是发现有可能会存在很多个答案正方形，修改之后你无法判断这一坨会不会影响答案。

#### 法二

~~怎么大家都会这种$dp$的方法啊~~

定义$f[i][j]$表示以点$(i,j)$为右下角的最大正方形的边长。

如果$(i,j)$是障碍点，那么$f[i][j]=0$，否则有$f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1$

这个也比较好理解，考虑$(i-1,j-1)$往右下移一格，而$(i-1,j),(i,j-1)$的答案也会造成限制，所以取最小值，再加上拓展出来的$1$

这个做法修改$O(1)$，每次查询$O(n^2)$，总时间复杂度$O(n^3)$

然后你就得到了$50pts$的好成绩（大众分

#### 法三

我们想起了法一那个中道崩殂的优化，那个优化不可行，主要是因为修改之后最大值会变小，而我们不知道别的地方有没有其它最大值。

但如果把询问离线下来，把加障碍变成减障碍，那么最大值就只会变大，而这个变大的最大值只能来源于修改的那一部分（冤有头债有主），所以就可以只处理修改的那一部分了。

具体怎么求答案呢？

如果有更大的答案的话，那么一定是包含这个障碍点的，也就是跨过这个障碍点所在行、所在列的。我们不妨从列的角度来考虑，先类似于悬线法那样预处理出每个点最多能够向左右延伸多远，这个在修改时可以$O(n)$更新。查询时，由于修改点那一列一定在答案正方形内部，我们可以用单调队列来维护这一列向左向右延伸的距离，如果队首限制了正方形的发展，就弹出队首。由于需要一个具体的限制，所以可以用$check$的方式，去$check$更大的答案是否可行。平均下来查询大概是$O(n)$的吧，可能常数会有点大，总复杂度$O(n^2)$。

然后你就得到了$100pts$的真·好成绩

------

### ►Code View Ver.1

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 2005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,m,T;
char s[N][N];
int a[N][N],ans;
int calc()
{
	int res=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int p=j,len=a[i][j];
			while(p-j+1<=len) 
			{
				len=min(len,a[i][++p]),res=max(res,min(p-j+1,len));
				if(res==ans) return ans;
			}
		}
	return ans=res;
}
int main()
{
	freopen("parking.in","r",stdin);
	freopen("parking.out","w",stdout);
	n=rd(),m=rd(),T=rd();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=m;i++)
		if(s[1][i]=='.') a[1][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='.')
				a[i][j]=a[i-1][j]+1;
	while(T--)
	{
		int x=rd(),y=rd();
		for(int i=x+1;i<=n;i++)
		{
			if(!a[i][y]) break;
			a[i][y]-=a[x][y];
		}
		a[x][y]=0;
		calc();
		printf("%d\n",ans);
	}
	return 0;
}


```

### ►Code View Ver.2 

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 2005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,m,T;
char s[N][N];
int f[N][N],ans;
void dp()
{
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='X') f[i][j]=0;
			else f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;
			ans=max(ans,f[i][j]);
		}
}
int main()
{
	freopen("parking.in","r",stdin);
	freopen("parking.out","w",stdout);
	n=rd(),m=rd(),T=rd();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	while(T--)
	{
		int x=rd(),y=rd();
		s[x][y]='X';
		dp();
		printf("%d\n",ans);
	}
	return 0;
}
```

### ►Code View Ver.3

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define N 2005
#define INF 0x3f3f3f3f
#define LL long long
int rd()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return f*x;
}
int n,m,T;
char s[N][N];
int f[N][N],ans,res[N];
int l[N][N],r[N][N];
pair<int,int> q[N];
int xx,yy;
int Q[N],hd,tl,tmp[N];
void dp()
{
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='X') f[i][j]=0;
			else f[i][j]=min(f[i-1][j-1],min(f[i-1][j],f[i][j-1]))+1;
			ans=max(ans,f[i][j]);
		}
}
void Init()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='X') l[i][j]=0;
			else l[i][j]=l[i][j-1]+1;
		}
		for(int j=m;j>=1;j--)
		{
			if(s[i][j]=='X') r[i][j]=0;
			else r[i][j]=r[i][j+1]+1;
		}
	}
}
bool check(int x)
{
	hd=1,tl=0;
	for(int i=1;i<=n;i++)
	{//维护左边 
		while(hd<=tl&&l[Q[tl]][yy]>=l[i][yy]) tl--;
		//维护单调增队列 如果当前可到位置比队列里的大 那么队列里的元素就不会成为瓶颈 
		Q[++tl]=i;
		while(hd<=tl&&Q[hd]<=i-x) hd++;//队首成为了限制
		tmp[i]=l[Q[hd]][yy];
	}
	hd=1,tl=0;
	for(int i=1;i<=n;i++)
	{//维护右边 
		while(hd<=tl&&r[Q[tl]][yy]>=r[i][yy]) tl--;
		Q[++tl]=i;
		while(hd<=tl&&Q[hd]<=i-x) hd++;
		tmp[i]+=r[Q[hd]][yy]-1;
	}
	for(int i=x;i<=n;i++)
		if(tmp[i]>=x) return 1;
	return 0;
}
int main()
{
	freopen("parking.in","r",stdin);
	freopen("parking.out","w",stdout);
	n=rd(),m=rd(),T=rd();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=T;i++)
	{
		q[i].first=rd(),q[i].second=rd();
		s[q[i].first][q[i].second]='X';
	}
	dp();
	res[T]=ans;
	Init();
	for(int i=T-1;i>=1;i--)
	{
		xx=q[i+1].first,yy=q[i+1].second;
		s[xx][yy]='.';
		for(int j=1;j<=m;j++)
		{
			if(s[xx][j]=='X') l[xx][j]=0;
			else l[xx][j]=l[xx][j-1]+1;
		}
		for(int j=m;j>=1;j--)
		{
			if(s[xx][j]=='X') r[xx][j]=0;
			else r[xx][j]=r[xx][j+1]+1;
		}
		while(check(ans+1)) ans++;
		res[i]=ans;
	}
	for(int i=1;i<=T;i++)
		printf("%d\n",res[i]);
	return 0;
}

```



---

## 作者：chihik (赞：1)


显然，如果每次删一个点，答案可能会减小，而且你还不知道在哪里减小的...

所以我们反向思考，如果每次加一个点，那么答案肯定是不减的，而且如果答案变大，新矩阵一定包含该点。

$up[i][j]$表示以$(i,j)$为起点出发向上能到达的 $'.~'$ 的个数。（遇到 $'X~'$ 停止）

$down[i][j]$表示以$(i,j)$为起点出发向下能到达的 $'.~'$ 的个数。（遇到 $'X~'$ 停止）

$up,down$都可以预处理，同时，我们也能用$dp$算出在所有点都无法选时（最后状态）的答案，记为$Ans$，不知道的看一下这道题：[P1387 最大正方形](https://www.luogu.org/problem/P1387)。

***

设当前加入的点为$(x,y)$,首先，我们可以暴力更新$up,down$,我们只需要知道当前区间最小的$up+down-1$，如果$Ans$小于它，就将$Ans+1$ , 同时向两旁扩展一格（边长加1）显然我们可以用线段树维护。不用担心两旁遇到障碍的情况 , 这时的$up，down$都为$0$,无法对答案造成影响。


注意这里的线段树每次加点都要重建（$up,down$在变）。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define ls x << 1
#define rs x << 1 | 1
#define INF 0x3f3f3f3f

const int MAXN = 2000;
int n , m , k , Minu , Mind , Map[ MAXN + 5 ][ MAXN + 5 ];
int up[ MAXN + 5 ][ MAXN + 5 ] , down[ MAXN + 5 ][ MAXN + 5 ];
struct node{
	int x , y , Ans;
}q[ MAXN + 5 ];

struct Point{
	int l , r , minu , mind;
};
struct Segment_Tree{
	Point Tree[ 4 * MAXN + 5 ];
	
	void Pushup( int x ) {
		Tree[ x ].minu = min( Tree[ ls ].minu , Tree[ rs ].minu );
		Tree[ x ].mind = min( Tree[ ls ].mind , Tree[ rs ].mind );
	}
	void Build( int dex , int x , int l , int r ) {
		Tree[ x ].l = l , Tree[ x ].r = r;
		if( l == r ) {
			Tree[ x ].minu = up[ dex ][ l ];
			Tree[ x ].mind = down[ dex ][ l ];
			return;
		}
		int Mid = ( l + r ) / 2;
		Build( dex , ls , l , Mid );
		Build( dex , rs , Mid + 1 , r );
		Pushup( x );
	}
	void Find( int x , int l , int r ) {
		if( r < Tree[ x ].l || Tree[ x ].r < l )
			return;
		if( l <= Tree[ x ].l && Tree[ x ].r <= r ) {
			Minu = min( Minu , Tree[ x ].minu );
			Mind = min( Mind , Tree[ x ].mind );
			return;
		}
		Find( ls , l , r );
		Find( rs , l , r );
	}
}Tree;

int dp[ MAXN + 5 ][ MAXN + 5 ];
void Dp( ) {
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ )
			if( Map[ i ][ j ] ) {
				dp[ i ][ j ] = min( dp[ i - 1 ][ j - 1 ] , min( dp[ i ][ j - 1 ] , dp[ i - 1 ][ j ] ) ) + 1;
				q[ k ].Ans = max( q[ k ].Ans , dp[ i ][ j ] );
			}
}

bool check( int x , int row ) {
	if( x > n || x > m ) return 0;
	for( int i = max( 1 , row - x + 1 ) ; i <= m - x + 1 ; i ++ ) {
		Minu = Mind = INF; Tree.Find( 1 , i , i + x - 1 );
		if( Minu + Mind - 1 >= x ) return 1;
	}
	return 0;
}

char s;
int main( ) {
	scanf("%d %d %d",&n,&m,&k);
	for( int i = 1 ; i <= n ; i ++ ) {
		getchar( );
		for( int j = 1 ; j <= m ; j ++ ) {
			scanf("%c",&s);
			Map[ i ][ j ] = ( s == '.' );
		}
	}
	for( int i = 1 ; i <= k ; i ++ ) {
		scanf("%d %d",&q[ i ].x,&q[ i ].y);
		Map[ q[ i ].x ][ q[ i ].y ] = 0;
		q[ i ].Ans = 0;
	}
	
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= m ; j ++ )
			up[ i ][ j ] = Map[ i ][ j ] ? up[ i - 1 ][ j ] + 1 : 0;
	for( int i = n ; i >= 1 ; i -- )
		for( int j = 1 ; j <= m ; j ++ )
			down[ i ][ j ] = Map[ i ][ j ] ? down[ i + 1 ][ j ] + 1 : 0;
	Dp( );
	int Ans = q[ k ].Ans;
	for( int i = k ; i >= 1 ; i -- ) {
		int x = q[ i ].x , y = q[ i ].y; q[ i ].Ans = Ans;
		Map[ x ][ y ] = 1;
		
		up[ x ][ y ] = up[ x - 1 ][ y ] + 1;
		for( int t = x + 1 ; t <= n && Map[ t ][ y ] ; t ++ )
			up[ t ][ y ] += up[ x ][ y ];
		down[ x ][ y ] = down[ x + 1 ][ y ] + 1;
		for( int t = x - 1 ; t >= 1 && Map[ t ][ y ] ; t -- )
			down[ t ][ y ] += down[ x ][ y ];
		Tree.Build( x , 1 , 1 , m );
		while( check( Ans + 1 , y ) ) Ans ++;
	}
	for( int i = 1 ; i <= k ; i ++ )
		printf("%d\n",q[ i ].Ans);
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

# 前言
其实没做出来这道题还是有点难过的，考场上的一道题，

已经想到了离线倒序处理，并且发现了如果更新了答案那么这个值就要被包含在新正方形内这个性质，    

接着就发现寻找新正方形及其困难，想到用线段树维护一些信息，也全被自己 $Hack$ 或者说太难实现就放弃了，    

最后很遗憾地打了个暴力上去甚至连 $O(n^2k)$ 都不是。  

# 步入正题    
其实如果做过[最大正方形](https://www.luogu.com.cn/problem/P1387)并且能完全理解其原理的话，这道题垒个 $2h$ 怎么都做得出来，可惜的是我不仅忘了这道题并且那时做题也是没弄清楚原理，这都是过去知识掌握不牢的后果啊。    

先讲一下黄题水平的 $O(n^2k)$ 暴力吧，直接每次加点的时候跑个最大正方形就行了。    

```cpp
void DP()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
			if(mp[i][j])
			{
				dp[i][j] = min(dp[i - 1][j - 1] , min(dp[i - 1][j] , dp[i][j - 1])) + 1;
				//Print[k] = max(Print[k] , dp[i][j]);
			}
}
```

这里粗略证明一下这个 $DP$ 式，如果此时我们枚举到了 $dp_{i,j}$ 的话，我们考虑 $dp_{i - 1 , j - 1}$ 的信息，发现就是多了一行一列而已，而我们只要知道此时向上和向左最多能往外扩展多少就行了，这时再和我们的 $dp_{i - 1 , j - 1}$ 的大小取个 ```min``` 就是我们当前最大能扩展到哪里的值即 $dp_{i,j}$ 值，而且你会发现 $dp_{i - 1 , j - 1}$ 也制约着当前行列的最远扩展，由于本来就是取 ```min``` 值，所以我们直接把 $dp_{i - 1, j}$ 和 $dp_{i , j - 1}$ 值拿来用就好了，更详细的证明就参考[最大正方形](https://www.luogu.com.cn/problem/P1387)吧。    

接着我们考虑优化一下，我们发现直接来的话未免太难了，所以我们倒序处理，并且得到了如前言所述的性质。     

我们此时发现，如果我们能通过枚举当前的行区间然后在 $O(m)$ 以下的时间复杂度进行区间查询判断区间查询是否合法，那么 $O(nqlogm)$ 的时间复杂度是完全可以接受的。     

然后就得想到这道题一个比较关键的东西：   
- $up[i][j]$ 维护点 $(i , j)$ 以上能扩散的最远距离。   
- $down[i][j]$ 维护点 $(i , j)$ 以下能扩散的最远距离。    
 
很显然的是我们都可以通过 $O(n ^ 2)$ 预处理出这两组信息，并且可以在每次加点时 $O(n)$ 暴力修改。    

那么我们岂不是只要知道当前区间里所有 $up$ 的最小值和 $down$ 的最小值就知道当前这个区间可以扩出来的最大值了啊，这玩意儿显然线段树啊，由于答案单调递增我们每次就看前一个答案在当前是否能增大就好了啊。    

到此整道题的关键思路就完了，其实在我看来最关键的就是要想到 $up$ 与 $down$ ， 欸思考力还是欠佳……    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 2005,Inf = 1e9;
int n,m,k,qx[Len],qy[Len],Print[Len],dp[Len][Len],minu,mind,mp[Len][Len],up[Len][Len],down[Len][Len],ansu[Len << 2],ansd[Len << 2];
char s[Len];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ansu[x] = min(ansu[ls(x)] , ansu[rs(x)]) , ansd[x] = min(ansd[ls(x)] , ansd[rs(x)]);}
void build(int p,int l,int r,int h)
{
	if(l == r)
	{
		ansu[p] = up[h][l];
		ansd[p] = down[h][l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid , h);
	build(rs(p) , mid + 1 , r , h);
	push_up(p);
}
void Fmin(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r)
	{
		minu = min(minu , ansu[p]);
		mind = min(mind , ansd[p]);
		return;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) Fmin(ls(p) , l , mid , nl , nr);
	if(nr > mid) Fmin(rs(p) , mid + 1 , r , nl , nr);
}
void DP()
{
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
			if(mp[i][j])
			{
				dp[i][j] = min(dp[i - 1][j - 1] , min(dp[i - 1][j] , dp[i][j - 1])) + 1;
				Print[k] = max(Print[k] , dp[i][j]);
			}
}
bool check(int Sec,int nowy)
{
	if(Sec > n || Sec > m) return 0;
	for(int i = max(1 , nowy - Sec + 1) ; i <= m - Sec + 1 ; i ++)
	{
		minu = mind = Inf;Fmin(1 , 1 , m , i , i + Sec - 1);
		if(minu + mind - 1 >= Sec) return 1;
	}
	return 0;
}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%s",s + 1);
		for(int j = 1 ; j <= m ; j ++) mp[i][j] = (s[j] == '.');
	}
	for(int i = 1 ; i <= k ; i ++)
	{
		scanf("%d %d",&qx[i],&qy[i]);
		mp[qx[i]][qy[i]] = 0;
	}
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= m ; j ++)
		{
			if(mp[i][j]) up[i][j] = up[i - 1][j] + 1;
			else up[i][j] = 0;
		}
	for(int i = n ; i >= 1 ; i --)
		for(int j = 1 ; j <= m ; j ++)
		{
			if(mp[i][j]) down[i][j] = down[i + 1][j] + 1;
			else down[i][j] = 0;
		}
	DP();
	int res = Print[k];
	for(int i = k ; i >= 1 ; i --)
	{
		mp[qx[i]][qy[i]] = 1 , Print[i] = res;
		up[qx[i]][qy[i]] = up[qx[i] - 1][qy[i]] + 1;
		for(int j = qx[i] + 1 ; j <= n ; j ++) 
		{
			if(!mp[j][qy[i]]) break;
			up[j][qy[i]] += up[qx[i]][qy[i]];
		}
		down[qx[i]][qy[i]] = down[qx[i] + 1][qy[i]] + 1;
		for(int j = qx[i] - 1 ; j >= 1 ; j --)
		{
			if(!mp[j][qy[i]]) break;
			down[j][qy[i]] += down[qx[i]][qy[i]];
		}
		build(1 , 1 , m , qx[i]);
		while(check(res + 1 , qy[i])) res ++;
	}
	for(int i = 1 ; i <= k ; i ++) printf("%d\n",Print[i]);
	return 0;
}
```

---

## 作者：薛定谔的鱼 (赞：0)

- 首先，考虑暴力，如果对每一个加点进行一遍扫描，那么，可以跑到天荒地老了。。。
- 其次，如果像以前的dp一样跑呢？因为是动态的，所以不行。。。
- 很容易想到，这个面积一定是单调不增的，于是，就可以倒序来，变成加点，离线做。
- 那么，有了加点就可以跑暴力了吗？很显然不行。。。
- 那怎么办呢？

# solution：

（以下初始思路来自老师）

这个正方形可能出现在哪里？
1. 点上下左右
2. 点左上
3. 点左下
1. 点右上
1. 点右下

一个正方形由长和宽构成，要找最大边长，其实就是要维护两个东西：长和宽。

分别考虑长宽如何维护（好吧差不多都是边长）

宽：它可能经过一个点，也就是这个点在宽这条边上。

于是不太容易想到：维护两个dp数组，存每个点向左右能拓展的长度。

但是，如果依旧暴力更新，还是会炸成渣滓。。。

瞪大眼看题，当一个点更新时，只有它所在的一行会变，所以就可以O（n）更新dp数组了。

于是，只要在每个点加上后更新dp数组，然后查出最大正方形，就完事了

下面考虑列：

能不能像刚刚那样继续dp嘞？（像cdq那样dp套dp呢？？？）如果这样做，那可能会得到一个错位的正方形。。。很麻烦.....

况且我们要去最大的不是吗？这好像有什么提示.....

想想我学过的维护最值的数据结构（qsort rmq 线段树 单调队列 主席树 平衡树 树套树）

再结合一下问题实际：找长度，不太容易想到，对于每一个答案，进行一次check。这个check，有点像二分，对于每一个可行答案进行判断然后更新最优解。而这个可行答案，就是看是否能找到更大的正方形。

对此，只需要枚举是否能找到比当前更大的边长就行了。因为它是正方形，所以长宽相等，这里列问题就转化为了：

对于每一个定长区间，找最大的一个之前处理出的dp数组里是否有一个长度大于等于它的值，也就是最大值。

这就很明朗了，线段树，单调队列。

两者差距在哪里呢？线段树O（nlogn）单调队列O（n）；

我用了单调队列。

这份代码给我的感觉就是：代码还可以继续化简，逻辑运算符可以有效增加效率和增加美观度

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2050;
char s[maxn];
int n,m,k;
int a[maxn][maxn];
struct node
{
    int x,y,res;
}ans[maxn];
int f[maxn][maxn];
int l[maxn][maxn];
int r[maxn][maxn];

void init()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
        {
            a[i][j]=(s[j]=='.');
        }
    }
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&ans[i].x,&ans[i].y);
        a[ans[i].x][ans[i].y]=0;
    }
}

void dp()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            if(!a[i][j])
            continue;
            if(i==1||j==m)
            {
                f[i][j]=1;
                ans[k].res=max(ans[k].res,1);
                continue;
            }
            f[i][j]=min(f[i-1][j],f[i][j+1]);
            if(a[i-f[i][j]][j+f[i][j]])f[i][j]++;
            ans[k].res=max(ans[k].res,f[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            l[i][j]=a[i][j]*(l[i][j-1]+1);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            r[i][j]=a[i][j]*(r[i][j+1]+1);
        }
    }
}

int tmp[maxn];
int q[maxn];

bool check(int x,int y)
{
    int head=1,tail=0;
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=n;i++)
    {
        while(head<=tail&&l[q[tail]][y]>=l[i][y])
        tail--;
        q[++tail]=i;
        while(q[head]<=i-x)
        head++;
        tmp[i]+=l[q[head]][y];
    }
    head=1;tail=0;
    for(int i=1;i<=n;i++)
    {
        while(head<=tail&&r[q[tail]][y]>=r[i][y])
        tail--;
        q[++tail]=i;
        while(q[head]<=i-x)
        head++;
        tmp[i]+=r[q[head]][y]-1;
    }
    for(int i=x;i<=n;i++)
    {
        if(tmp[i]>=x)
        return 1;
    }
    return 0;
}

void solve()
{
    int tem=ans[k].res;
    for(int i=k;i>=2;i--)
    {
        ans[i].res=tem;
        int x=ans[i].x;
        int y=ans[i].y;
        a[x][y]=1;
        for(int j=1;j<=m;j++)
        {
            l[x][j]=a[x][j]*(l[x][j-1]+1);
        }
        for(int j=m;j>=1;j--)
        {
            r[x][j]=a[x][j]*(r[x][j+1]+1);
        }
        while(check(tem+1,y))
        tem++;
    }
    ans[1].res=tem;
    for(int i=1;i<=k;i++)
    {
        printf("%d\n",ans[i].res);
    }
}

int main()
{
    init();
    dp();
    solve();
    return 0;
}
```
（萌新求过）

---

