# Smile House

## 题目描述

n个点，m条边，无向图但一条无向边的两个方向的边权不同，求图上最小正环的大小（定义正环为从一个点出发再回到这个点经过所有边边权之和为正）（定义最小正环的含义为这个正环经过的点数最少）

## 样例 #1

### 输入

```
4 4
1 2 -10 3
1 3 1 -10
2 4 -10 -1
3 4 0 -3
```

### 输出

```
4
```

# 题解

## 作者：chihik (赞：9)


## Solution 1

设 $dp_{s,i,j}$ 表示走了不超过 $s$ 条边，$i \to j$ 的最长路径(走不通为极小值)

如果有 $u \to v$ 的一条边，那么 $dp_{1,u,v}=w$ （$w$为这条边的权值）

转移为：
$$
dp_{s,i,j}=\max_{1 \le k \le n}\{dp_{s-1,i,k}+dp_{1,k,j}\}
$$

显然，答案为使得 $∃i \in [1,n],\ dp_{k,i,i}>0$ 的最小 $k$。 

时间复杂度 $\mathcal O(n^4)$

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 300;
int n , m , x , y , z , w , Ans;
int dp[ MAXN + 5 ][ MAXN + 5 ][ MAXN + 5 ];

int main( ) {
    memset( dp , 0xcf , sizeof( dp ) );

    scanf("%d %d",&n,&m);
    for( int i = 1 ; i <= m ; i ++ ) {
        scanf("%d %d %d %d",&x,&y,&z,&w);
        dp[ 1 ][ x ][ y ] = z;
        dp[ 1 ][ y ][ x ] = w;
    }
    for( int s = 2 ; s <= n ; s ++ ) {
        for( int k = 1 ; k <= n ; k ++ )
            for( int i = 1 ; i <= n ; i ++ ) {
                for( int j = 1 ; j <= n ; j ++ )
                    dp[ s ][ i ][ j ] = max( dp[ s ][ i ][ j ] , dp[ s - 1 ][ i ][ k ] + dp[ 1 ][ k ][ j ] );
                if( dp[ s ][ i ][ i ] > 0 ) {
                    Ans = s;
                    goto there;
                }
            }     
    } 
    there:;
    printf("%d",Ans);
    return 0;
}
```

## Solution 2

我们有必要重新定义一下 $dp$ ，设 $dp_{s,i,j}$ 表示走了不超过 $2^s$ 条边，$i \to j$ 的最长路径(走不通为极小值)。

转移为：

$$
dp_{s,i,j}=\max_{1 \le k \le n}\{dp_{s-1,i,k}+dp_{s-1,k,j}\}
$$

可以使用倍增 $\mathcal O(n^3 \log_n)$ 求得。

在我们计算答案时，我们用类似倍增爬树的方法。

先从小到大尝试不超过 $2^s$ 条边的路径是否有正环。

1.如果没有正环，说明答案大于$2^s$ , 那么下一步**增加**$2^{s-1}$条边

转移时需用到上一次状态，需额外记录上一次尝试 $i \to j$ 的最长路径。

2.如果有正环，说明答案小于等于$2^s$，那么下一步**尝试**$2^{s-1}$条边

总时间复杂度$\mathcal O(n^3\log_n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 300 , MAXK = 10;
int n , m , x , y , z , w , Ans;
int dp[ MAXK + 5 ][ MAXN + 5 ][ MAXN + 5 ];
int tmp[ MAXN + 5 ][ MAXN + 5 ] , now[ MAXN + 5 ][ MAXN + 5 ];

int main( ) {
    memset( now , 0xcf , sizeof( now ) );
    memset( dp , 0xcf , sizeof( dp ) );

    scanf("%d %d",&n,&m);
    for( int i = 1 ; i <= m ; i ++ ) {
        scanf("%d %d %d %d",&x,&y,&z,&w);
        dp[ 0 ][ x ][ y ] = z;
        dp[ 0 ][ y ][ x ] = w;
    }
    for( int i = 1 ; i <= n ; i ++ )
        now[ i ][ i ] = 0 , dp[ 0 ][ i ][ i ] = 0;
    
    for( int s = 1 ; s <= MAXK ; s ++ )		//预处理
        for( int k = 1 ; k <= n ; k ++ )
            for( int i = 1 ; i <= n ; i ++ )
                for( int j = 1 ; j <= n ; j ++ )
                    dp[ s ][ i ][ j ] = max( dp[ s ][ i ][ j ] , dp[ s - 1 ][ i ][ k ] + dp[ s - 1 ][ k ][ j ] );
    
    for( int s = MAXK ; s >= 0 ; s -- ) {
        memset( tmp , 0xcf , sizeof( tmp ) );

        for( int k = 1 ; k <= n ; k ++ )	//转移
            for( int i = 1 ; i <= n ; i ++ )
                for( int j = 1 ; j <= n ; j ++ )
                    tmp[ i ][ j ] = max( tmp[ i ][ j ] , now[ i ][ k ] + dp[ s ][ k ][ j ] );

        bool f = 0;
        for( int i = 1 ; i <= n ; i ++ )
            if( tmp[ i ][ i ] > 0 ) {
                f = 1;
                break;
            }
        if( f ) continue;	//有正环
        else {				//无正环
            for( int i = 1 ; i <= n ; i ++ )
                for( int j = 1 ; j <= n ; j ++ )
                    now[ i ][ j ] = tmp[ i ][ j ];
            Ans += 1 << s;
        }
    }
    printf("%d\n", Ans >= n ? 0 : Ans + 1 );
    return 0;
}
```


---

## 作者：_Album_ (赞：2)

更好的阅读：[传送门](https://payphone-x.top/2019/10/29/CF147B/)

------------------------------

## 分析

一道看起来很像搜索的动态规划。~~(考场上爆搜打挂的我哭出声来)~~

不难看出，这题是在图上做的，且这题的数据范围极小。很容易就能想到$Floyd$。

而$Floyd$的本质是$DP$。考虑如何在$Floyd$的基础上$DP$。

设$f[l][i][j]$表示从$i$到$j$经过$l$条边的路径大小，可得状态转移方程
$$f[l][i][j] = max(f[l][i][j] , f[l - 1][i][k] + f[1][k][j])$$

其中，$l,i,j,k$均需要在转移时枚举，时间复杂度为$O(n^4)$，无法通过$100\%$的数据。

考虑如何优化这个$DP$。由于这个$DP$基于$Floyd$，因此$i , j , k$必须进行枚举，而$l$却可以使用倍增来优化。

则我们重新设计状态。设$f[l][i][j]$表示从$i$到$j$经过$2^l$条边的路径大小，可得状态转移方程
$$f[l][i][j] = max(f[l][i][j] , f[l - 1][i][k] + f[l - 1][k][j])$$

这个过程的时间复杂度是$O(n^3 \log n)$的。

之后我们采用类似于倍增爬树的方法来求解答案。首先，我们先尝试走$2^l$条边从$i$到$j$的路径大小。

若不存在正环(即$f[l][i][i] < 0$)，则证明答案大于$2^l$。下一次转移时**增加**$2^{l - 1}$条边即可。

否则的话证明答案小等于$2^l$，下一次转移时仅**尝试**$2^{l - 1}$条边即可。

时间复杂度为$O(n^3 \log n)$，足以通过本题。

剩下的见代码注释。



## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define I inline
#define N 301

using namespace std;

int n, m, ans;
int u , v , d1 , d2;
int f[15][N][N];
int tmp[N][N], last[N][N];

int main(){
    memset(last, -0x3f3f3f3f, sizeof(last));
    memset(f, -0x3f3f3f3f, sizeof(f));

    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        cin >> u >> v >> d1 >> d2;
        f[0][u][v] = d1;
        f[0][v][u] = d2;
    }
    for (int i = 1; i <= n; i++){
        last[i][i] = 0;
        f[0][i][i] = 0;
    }

    for (int l = 1; l <= 10; l++){
        for (int k = 1; k <= n; k++){
            for (int i = 1; i <= n; i++){
                for (int j = 1; j <= n; j++){
                    f[l][i][j] = max(f[l][i][j], f[l - 1][i][k] + f[l - 1][k][j]);
                }
            }
        }
    } 
    for (int l = 10; l >= 0; l--){
        memset(tmp, -0x3f3f3f3f, sizeof(tmp));

        for (int k = 1; k <= n; k++){
            for (int i = 1; i <= n; i++){
                for (int j = 1; j <= n; j++){
                    tmp[i][j] = max(tmp[i][j], last[i][k] + f[l][k][j]);
                }
            } 
        }

        bool flag = false;
        for (int i = 1; i <= n; i++){
            if (tmp[i][i] > 0){
                flag = true;
                break;
            }
        }

        if (flag) continue; 
        else{ 
            for (int i = 1; i <= n; i++){
                for (int j = 1; j <= n; j++){
                    last[i][j] = tmp[i][j];
                }  
            }
                
            ans += 1 << l;
        }
    }
    cout << (ans >= n ? 0 : ans + 1) << "\n";
    return 0;
}
```

---------------------------------------

# THE END


---

## 作者：_Ch1F4N_ (赞：1)

考虑二分一个答案 $mid$，然后你发现走 $mid$ 步一个点走出的最大权路径可以使用 $\max +$ 矩阵快速幂在 $O(n^3 \log n)$ 时间内求出。

然后你注意到可以把倍增和二分放在一起，具体而言从高往低按位确定出答案，用预处理出的转移矩阵的幂来 check 即可做到 $O(n^3 \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 314;
const int inf = 1e9+114;
int n,m;
struct matrix{
	int a[maxn][maxn];
	matrix(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) a[i][j]=-inf;
	}
	matrix operator*(matrix &x){
		matrix res=matrix();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++) res.a[i][k]=max(res.a[i][k],a[i][j]+x.a[j][k]);
			}
		}
		return res;
	}
}e,_pow[maxn];
int main(){
	cin>>n>>m;
	e=matrix();
	for(int i=1;i<=n;i++) e.a[i][i]=0;
	_pow[0]=matrix();
	for(int i=1;i<=m;i++){
		int x,y,z,w;
		cin>>x>>y>>z>>w;
		_pow[0].a[x][y]=max(_pow[0].a[x][y],z);
		_pow[0].a[y][x]=max(_pow[0].a[y][x],w);
	}
	for(int i=1;i<=n;i++) _pow[0].a[i][i]=0;
	for(int i=1;i<9;i++) _pow[i]=_pow[i-1]*_pow[i-1];
	matrix c=e*_pow[8]*_pow[7];
	bool flag=false;
	for(int i=1;i<=n;i++){
		if(c.a[i][i]>0) flag=true;
	}
	if(flag==false){
		cout<<0<<'\n';
		return 0;
	}
	int ans=0;
	for(int i=8;i>=0;i--){
		matrix New=e*_pow[i];
		bool flag=false;
		for(int j=1;j<=n;j++) 
			if(New.a[j][j]>0) flag=true;
		if(flag==false){
			ans+=(1<<i);
			e=New;
		}
	}
	cout<<ans+1<<'\n';
	return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

暴力可过，所以不写郑洁了！！111

考虑一个经典 dp。设 $f_{k,i,j}$ 表示从 $i$ 走到 $j$，且走了 $k$ 步，经过的路径的最大权值的和是多少。显然初始条件：对于每一条边 $u\to v$，且其边权为 $w$，都有 $f_{1,u,v}=w$。转移是简单的：枚举中转点 $x$，则 $f_{k,i,j}\leftarrow f_{k-1,i,x}+f_{1,x,y}$，可以做到 $O(n^4)$，氰微卡常可过。

考虑优化。中间这个中转点看着就很能优化，显然可以倍增一下做到 $O(n^3\log n)$，但是不想写了。

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <bits/stdc++.h>
// #define int long long
#define eb emplace_back
using namespace std;
const int N = 510;
const int mod = 998244353;
int f[310][310][310], mp[310][310];
void chkmax(int &x, int y) {
    if (x < y) x = y;
}
signed main() {
    int n, m;
    cin >> n >> m;
    memset(f, -0x3f, sizeof f);
    memset(mp, -0x3f, sizeof mp);
    for (int i = 0; i < m; ++i) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        f[1][x][y] = z;
        f[1][y][x] = w;
        mp[x][y] = z;
        mp[y][x] = w;
    }
    for (int _ = 2; _ <= n; ++_)
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j)
                    chkmax(f[_][i][j], f[_ - 1][i][k] + mp[k][j]);
                if (f[_][i][i] > 0) {
                    cout << _ << '\n';
                    return 0;
                }
            }
    cout << "0\n";
    return 0;
}
```

---

## 作者：wyl_AC (赞：0)

这道题，看着像图论，算正环，当然可以用floyd，但是你要求出最小的正环，就可以用dp做法。

dp[c][i][j]:表示走了不超过c条边的i,j的最大的边权和。folyd*枚举c    =O（n^4）

看到这种一条一条边爬的算法，是不是就有有点想LCA的爬山，那么我们可以用倍增优化;

f[c][i][j]:表示走了不超过2^c条边从i走到了j的最小边权和（预处O(logn * n^3),然后再二分答案M，把M拆成二进制:再用每一位上的对应位去拼凑答案（O(logn * n^3）），dp[M][i][j]，在判断答案是否正确。floyd*拼凑M*二分答案 =O(n^3*logn*logn)

还是有可能超时，再观察，在步数增大的同时，正环会增多，而不会减少，那么我们可以把答案M也给一起倍增了。比如说2^s次方可以凑出，那我们就去尝试2^(s-1),不行就去试2^s+2^(s-1),直到刚好只差一步就有正环。

那么就有点数为凑出的答案（走过变数）加1。但如果走了n步，即使之前一直没走走过的点，那么这里必然走回去了，那么如果点数>n+1,边数>n即为误解，输出0。

我的代码，咋一眼看像是矩阵加速，但仔细一看就是floyd。主要是我看的标程来自[这里](https://www.cnblogs.com/mle-world/p/11167595.html)(我总觉得会有说抄题解，还是贴在这了，他是没有解释的)

code
```cpp
#include<cstdio>
#include<cmath>
#include<vector>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define LL long long
#define Log 10
#define M 315
#define Mod 12345
const double eps=1e-9;
LL read() {
    LL x=0;
    LL f=1;
    char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-')
            f=-f;
        c=getchar();
    }
    while(c>='0'&&c<='9') {
        x=x*10+c-'0';
        c=getchar();
    }
    x*=f;
    return x;
}
LL n,m;
struct matrix{
	LL s[M][M];
	void inti(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				s[i][j]=-0x3f3f3f3f;
		return ;
	}
	matrix operator *(matrix b)const{
		matrix f;
		f.inti();
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					f.s[i][j]=max(f.s[i][j],s[i][k]+b.s[k][j]);
		return f;
	}
}t[Log],now,p;
int main(){
	n=read(),m=read();
	t[0].inti();
	for(int i=1;i<=n;i++)
		t[0].s[i][i]=0;
	for(int i=1;i<=m;i++){
		LL u = read(),v= read();
		t[0].s[u][v]=read();
		t[0].s[v][u]=read();
	}
	for(int i=1;i<Log;i++)
		t[i] = t[i-1] * t[i-1];
	now.inti(),p.inti();
	for(int i=1;i<=n;i++)
		now.s[i][i]=0;
	LL ans=0;
	for(int i=Log-1;~i;i--){
		p=now * t[i];
		bool flag=0;
		for(int j=1;j<=n;j++)
			if(p.s[j][j]>0){
				flag=1;
				break;
			}
		if(flag)
			continue;
		ans+=(1<<i),now=p;	
	}
	if(ans>n)
		puts("0");
	else
		printf("%lld",ans+1);
}
```




---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF147B)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到环就可以想到$Floyd$；但是此题要求两个最优——边权和尽量大，边数尽量少。于是我们只能选择将边数放到状态里面。便有了状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(l,u,v)$：从$u$起经过不超过$l$条边到达$v$的最大边权和。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移是$O(n^4)$，会$T$的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;退而求其次，我们考虑一下倍增。设$f(k,u,v)$表示从$u$起经过不超过$2^k$条边后到达$v$的最大边权和。先用$O(n^3log_2n)$预处理出$f$数组，然后$DP$数组就可以确定$l$的情况下用$O(n^3log_2n)$处理出来。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;另外，我们发现答案具有单调性——如果在$DP(k,u,v)$中存在正权环，那么在$DP(k+1,u,v)$中也会存在。所以我们二分答案，组合出$DP$数组后检查。时间$O(n^3log_2^2n)$，虽然很悬，但是能$A$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过，答案也是可以倍增搞出来的。模仿倍增跳$LCA$的做法，我们下降地构造答案。假如正确答案为$ans$，当前的为$r$，枚举到了二进制上的第$s$位。如果在$r+2^s$的$DP$里面找到了正权环，则我们知道$ans\leq r+2^s$，可以继续枚举第$s-1$位；否则我们在答案中累加$2^s$，并且枚举第$s-1$位（根据上一步的推论，我们知道$r+2^s\leq ans<r+2^{s+1}$）。最后就能得到答案。    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~于是我还是写了二分的方法，如果想看倍增就请移步楼上（楼下？）~~
# 代码
```cpp
#include <cmath>
#include <cstdio>

const int MAXN = 305, MAXLOG = 10, INF = 0x3f3f3f3f, inf = 0x3f3f3f3f;

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

int dis[MAXLOG][MAXN][MAXN], DP[2][MAXN][MAXN];
int N, M, lg2;

bool chk( const int len )
{
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= N ; j ++ )
			DP[0][i][j] = i == j ? 0 : -INF;
	int now = 0;
	for( int t = 0 ; ( 1 << t ) <= len ; t ++ )
	{
		if( len & ( 1 << t ) )
		{
			now ^= 1;
			for( int i = 1 ; i <= N ; i ++ )
				for( int j = 1 ; j <= N ; j ++ ) DP[now][i][j] = -INF;
			for( int k = 1 ; k <= N ; k ++ )
				for( int i = 1 ; i <= N ; i ++ )
					for( int j = 1 ; j <= N ; j ++ )
						DP[now][i][j] = MAX( DP[now][i][j], DP[now ^ 1][i][k] + dis[t][k][j] );
		}
	}
	for( int i = 1 ; i <= N ; i ++ )
		if( DP[now][i][i] > 0 ) return true;
	return false;
}

int main()
{
	int fr, to, w1, w2;
	read( N ), read( M );
	lg2 = log2 ( N );
	for( int k = 0 ; k <= lg2 ; k ++ )
		for( int i = 1 ; i <= N ; i ++ )
			for( int j = 1 ; j <= N ; j ++ )
				dis[k][i][j] = i == j ? 0 : -INF;
	for( int i = 1 ; i <= M ; i ++ )
	{
		read( fr ), read( to );
		read( w1 ), read( w2 );
	    dis[0][fr][to] = w1, dis[0][to][fr] = w2;
	}
	for( int t = 1 ; t <= lg2 ; t ++ )
		for( int k = 1 ; k <= N ; k ++ )
			for( int i = 1 ; i <= N ; i ++ )
				for( int j = 1 ; j <= N ; j ++ )
					dis[t][i][j] = MAX( dis[t - 1][i][k] + dis[t - 1][k][j], dis[t][i][j] );
	int l = 2, r = N + 1, mid;
	while( r > l )
	{
		mid = ( l + r ) >> 1;
		if( chk( mid ) ) r = mid;
		else l = mid + 1;
	}
	write( l % ( N + 1 ) ), putchar( '\n' );
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

一道十分典型的 `dp` 题。有三个关键点分别是定义状态、优化和答案的统计。

- 首先定义状态，定义 $f_{i,j,p}$ 表示 $i \to j$ 号节点，共走了**不超过** $p$ 条边，且是 $i \to j$ 的**最长路径**。不超过 $p$ 条边是为了方便转移，而最长路径如果都为负环，说明需要走更多的边，实际上也是为了方便转移。但是这样是 $O(n^4)$ 转移的，所以用一个很常见的 trick 就是倍增。将状态定义变成这样：$f_{i,j,p}$ 表示 $i \to j$ 号节点，共走了不超过$2^p$ 条边，且是 $i \to j$ 的最长路径。然后状态转移便是 $O(n^3\operatorname{log}n)$ 的，状态转移方程为 $f_{i,j,p}=f_{i,k,p-1}+f_{k,j,p-1}$，可以类比 `Floyd` 算法的转移。

- 然后就是统计答案，注意在这时，你需要枚举 $p$，如果 $2^p$ 步可以达到最小正环，便继续考虑 $2^{p-1}$ 是否可行。如果不行，就累加答案，仍然继续考虑 $2^{p-1}$。

注意数组赋成 $-\infty$ 以及细节的处理。

---

