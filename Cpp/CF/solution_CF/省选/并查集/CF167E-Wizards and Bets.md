# Wizards and Bets

## 题目描述

给定 $n(1 \le n \le 600)$ 个点 $m(0 \le m \le 10^5)$ 条边的有向无环图，其中没有入度的点被视为源点，没有出度的点被视为汇点。保证源点和汇点数目相同。考虑所有把源汇点两两配对，并用两两不相交的路径把它们两两连接起来的所有方案。

如果这个方案中，把源点按标号 $1$ 到 $n(1 \le n \le 600)$ 排序后，得到的对应汇点序列的逆序数对的个数是奇数，那么 A 给 B 一块钱，否则 B 给 A 一块钱。问最后 A 的收益，对质数 $p(2 \le p \le 10^9 + 7)$ 取模。

## 说明/提示

在第一个示例中，正好有一组路径 $(1 \to 3), (2 \to 4)$。反转数为 $0$，即偶数。因此，A 玩家得到 $1$ 枚硬币。

在第二个示例中，正好有一组路径 $(4 \to 1), (3 \to 2)$。正好有一个反转。因此，A 玩家得到 $-1$ 枚硬币。

在第三个示例中，有两组路径，它们以相反的符号计数。

在第四个样本中，没有任何一组路径。

在第五个样本中，有三个源（$2, 3, 5$）和三个汇（$1, 2, 4$）。对于单组路径 $(5 \to 1), (3 \to 4), (2 \to 2)$ 有 $2$ 个反转，即它们的数量是**偶数**。

## 样例 #1

### 输入

```
4 2 1000003
1 3
2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2 1000003
4 1
3 2
```

### 输出

```
1000002
```

## 样例 #3

### 输入

```
4 4 1000003
2 1
2 4
3 1
3 4
```

### 输出

```
0
```

## 样例 #4

### 输入

```
6 5 1000003
1 4
1 5
1 6
2 6
3 6
```

### 输出

```
0
```

## 样例 #5

### 输入

```
5 2 1000003
5 1
3 4
```

### 输出

```
1
```

# 题解

## 作者：Endline (赞：5)

# CF167E 题解

## LGV 引理

对于一张有向图，我们做如下定义：

- 给出一些起点 $a$、一些终点 $b$（起点和终点数目相等），从起点 $a_i$ 到终点 $b_i$ 的一条路径称为 $p_{i,j}$，长度为经过的权值之和 $\sum\limits _{p:a_i\rightarrow b_j}w_{a_i,a_j}$。

那么对于每一对起点和终点 $a_i,b_j$，可以对应一个 $n$ 阶方阵：

$$
M=\begin{bmatrix}
 p_{a_1,b_1} & p_{a_1,b_2} & \cdots & p_{a_1,b_n}\\
 p_{a_2,b_1} & p_{a_2,b_2} & \cdots & p_{a_2,b_n}\\
\vdots & \vdots & \ddots & \vdots\\
 p_{a_n,b_1} & p_{a_n,b_1} & \cdots & p_{a_n,b_n}
\end{bmatrix}
$$

那么该引理告诉我们：（$\sigma(S)$ 表示对于每一种 $a$ 与 $b$ 的对应关系排列中的逆序对个数，$S:a\rightarrow b$ 表示从 $a$ 到 $b$ 的所有不相交路径）

$$
\det(M)=\sum\limits_{S:a\rightarrow b}(-1)^{\sigma(S)}\prod\limits_{i=1}^n S_i
$$

有了这个引理，我们再来看这个题：

## 做法

很显然，这就是 LGV 引理的一个模板。

我们将起点到终点的权值之和设为从该起点到该终点的方案数，那么利用这个引理，把它们乘起来就可以得到对于某一种对应关系的所有 A 的收益/亏损。

再利用它自带的逆序对奇偶性所带来的加/减，我们可以非常优美地解决这个问题。

那么如何处理方案数呢？考虑动态规划。将终点的 $dp$ 值设置为 $1$，利用 `dfs` 反过来向起点递推：

$$
dp_u=\sum\limits_{u\rightarrow v} dp_v
$$

## AC 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 602
#define MAXM 100002
using namespace std;
using ll=long long;
int n,m,mod,cnt,cnta,cntb;
bool vis[MAXN<<1];
int head[MAXN<<1];
int ind[MAXN<<1],outd[MAXN<<1];
int a[MAXN],b[MAXN];
ll dp[MAXN<<1][MAXN<<1];
struct edge
{
    int v,nxt;
}e[MAXM];
struct Matrix
{
    ll a[MAXN][MAXN];
    ll*operator[](int x){return a[x];}
    inline ll det()
    {
        ll res=1,f=1;
        for(int i=1;i<=cnta;i++)
        {
            int max=i;
            for(int j=i+1;j<=cnta;j++)
                if(a[j][i]>a[max][i])max=j;
            if(max!=i)swap(a[max],a[i]),f=-f;
            if(!a[i][i])return 0;
            for(int j=i+1;j<=cnta;j++)
            {
                if(a[j][i]>a[i][i])swap(a[j],a[i]),f=-f;
                while(a[j][i])
                {
                    ll l=a[i][i]/a[j][i];
                    for(int k=i;k<=cnta;k++)
                        a[i][k]=(a[i][k]-a[j][k]*l%mod+mod)%mod;
                    swap(a[j],a[i]),f=-f;
                }
            }
            (res*=a[i][i])%=mod;
        }
        return (res*f+mod)%mod;
    }
}M;
inline void addedge(int u,int v)
{
    e[++cnt]={v,head[u]};
    head[u]=cnt;
    return;
}
void dfs(int u)
{
    if(!outd[u])dp[u][u]=1;
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(!vis[v])
        {
            vis[v]=true;
            dfs(v);
        }
        for(int j=1;j<=cntb;j++)
            (dp[u][b[j]]+=dp[v][b[j]])%=mod;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>mod;
    for(int i=1,u,v;i<=m;i++)
    {
        cin>>u>>v;
        addedge(u,v);
        outd[u]++,ind[v]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(!ind[i])a[++cnta]=i;
        if(!outd[i])b[++cntb]=i;
    }
    for(int i=1;i<=cnta;i++)
        if(!vis[a[i]])vis[a[i]]=true,dfs(a[i]);
    for(int i=1;i<=cnta;i++)
        for(int j=1;j<=cntb;j++)
            M[i][j]=dp[a[i]][b[j]];
    printf("%lld\n",M.det());
    return 0;
}
```

---

## 作者：chihik (赞：3)


首先，我们将所有源点与汇点筛出来，然后从每一个源点dfs求出它到各汇点的路径数，题目中保证源点与汇点数量相同，我们记为$cnt$。
那么，我们可以得到一个$cnt * cnt$的矩阵。

先考虑路径不相交的情况（似乎大家思路都是这样），题目求的是一个排列的逆序对数，记为$\tau(\sigma)$。那么，题目等价于求：

$$
\sum(-1)^{\tau(\sigma)}*\prod{f_{~i~\sigma_i}}
$$

其中，$f_{i~\sigma_i}$表示i号源点走到$\sigma_i$号汇点的路径数。

结合上文，~~不难~~很难想到行列式。然后，你会发现，矩阵的行列式就是答案。

***
然后，我们考虑路径相交的情况，发现答案不变。

![graph _1_.png](https://i.loli.net/2019/08/23/1XjfSGzKki9Ynqy.png)

显然，$(1 \to 4),(2 \to 5)$路径相交了

我们考虑交换$4,5$位置

![graph.png](https://i.loli.net/2019/08/23/WK5MHdtu8pBLo7U.png)

~~还是相交的~~。

这虽然不能解决我们的问题，但我们发现，经过交换后，**汇点序列的逆序对数奇偶性变了**，也就是矩阵行列式的其中一项变号。同时，路径数却没有变。所以，两种情况相互抵消了！！！

所以，路径相交并不会影响答案，直接算行列式即可。

***
本代码由@Krain大佬修改，可能神似请见谅。

同时，求矩阵行列式时消元必须在整数范围内运算，需要用到辗转相除的高斯消元，此处不再赘述。

```cpp
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 600;
int n , m , x , y , p , cnt;
int Ind[ MAXN + 5 ] , Outd[ MAXN + 5 ];
int s[ MAXN + 5 ][ MAXN + 5 ];
int tmp[ MAXN + 5 ] , f[ MAXN + 5 ][ MAXN + 5 ];
vector< int > Graph[ MAXN + 5 ];
vector< int > S , T;

int Mo( long long x ) {
	return ( x % p + p ) % p;
}
int Gauss( ) {
	int Sign = 1;
    for( int i = 1 ; i <= cnt ; i ++ ) {
    	for( int j = i + 1 ; j <= cnt ; j ++ ) {
    		int A = f[ i ][ i ] , B = f[ j ][ i ];
    		while( B ) {
    			int t = A / B; A %= B; swap( A , B );
    			for( int k = i ; k <= n ; k ++ )
    				f[ i ][ k ] = Mo( 1ll * f[ i ][ k ] - 1ll * t * f[ j ][ k ] );
    			
    			swap( f[ i ] , f[ j ] );
    			Sign *= -1;
			}
		}
    	if( !f[ i ][ i ] ) return 0;
    }
    int Ans = 1;
    for( int i = 1 ; i <= cnt ; i ++ )
        Ans = ( 1ll * Ans * f[ i ][ i ] ) % p;
    return Mo( 1ll * Ans * Sign );
}

bool vis[ MAXN + 5 ];
void dfs( int u ) {
	vis[ u ] = 1;
    if( !Outd[ u ] ) s[ u ][ u ] = 1;
    for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
        int v = Graph[ u ][ i ];
        if( !vis[ v ] ) dfs( v );
        for( int j = 0 ; j < T.size() ; j ++ )
        	s[ u ][ T[ j ] ] = Mo( 1ll * s[ u ][ T[ j ] ] + s[ v ][ T[ j ] ] );
    } 
}
int main( ) {
    scanf("%d %d %d",&n,&m,&p);
    for( int i = 1 ; i <= m ; i ++ ) {
        scanf("%d %d",&x,&y);
        Graph[ x ].push_back( y );
        Outd[ x ] ++ , Ind[ y ] ++;
    }
    for( int i = 1 ; i <= n ; i ++ ) {
    	if( !Ind[ i ] )
    		S.push_back( i );
    	if( !Outd[ i ] )
    		T.push_back( i );
	}
    for( int i = 1 ; i <= n ; i ++ )
        if( !Ind[ i ] ) dfs( i );
    
    for( int i = 0 ; i < S.size() ; i ++ )
    	for( int j = 0 ; j < T.size() ; j ++ )
    		f[ i + 1 ][ j + 1 ] = s[ S[ i ] ][ T[ j ] ];
    cnt = S.size();
    printf("%d",Gauss( ));
    return 0;
}
```


---

## 作者：Rainybunny (赞：3)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[题目链接](https://www.luogu.org/problem/CF167E).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;相信没人能看懂鬼畜翻译, 在此描述简要提议:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于远点与汇点的匹配, 我们将其看做二元组$(a_i,b_i)$, 以$a$升序排列后, $A$将获得收益$(-1)^{\tau_\sigma}$, 其中$\sigma$是$b$此时值的排列, $\tau$是常见的逆序对统计记号. 形象来说:  
![](https://i.loli.net/2019/08/21/ZTp7eiKwSCR3ytb.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( $\tau$代表右侧数列的逆序对数 ).  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看这如此熟悉的式子, 你想到[行列式](https://baike.baidu.com/item/%E8%A1%8C%E5%88%97%E5%BC%8F/2010180?fr=aladdin)了吗? ( 我没有 ). 设$A$是一个$n\times n$的矩阵, 则:  
![3.png](https://i.loli.net/2019/08/21/2e3iXHBETplPQxd.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这也提示了我们使用行列式求解. 首先考察无路径相交限制的问题 ( 好像思路都长这样唉... ), 设$f_{ij}$表示原点$i$走到汇点$j$的方案数, 设原点有$m$个, 我们对$F$求行列式:  
![4.png](https://i.loli.net/2019/08/21/RxNYakS1wnm3HOd.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们把抽象的符号放在题面上理解:  
- 枚举的排列$\sigma$: 如上, 二元组排序后的$b$数列.  

- 系数$(-1)^{\tau_{\sigma}}$: $A$的收益.  

- 累乘$\prod_{i=1}^mf_{i\sigma_i}$: 乘法原理, 每个原点$i$到汇点$\sigma_i$方案数之积.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$OMG!$行列式的值不就是这个问题的答案吗?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;等等, 我们还需要回归到本题对边相交的限制, 发现答案竟然没变! 这是因为对于任一种两条路径相交的方案$x$, 选择这对路径上相交的最后一个点, 将这个点之后的路径反转, 一定会映射到另一种路径相交的方案$y$, 而由于逆序对的改变, 这两种非法状态的收益会相互抵消掉. 当然, 希望直观的画面更能"一图惊人":  
![2.png](https://i.loli.net/2019/08/21/1qvOufjiQ2xSL7U.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;图中交叉点代表路径的交点, 而蓝色匹配方案与红色匹配方案的唯一差别是在计算收益时, $b_x$与$b_y$交换了位置. 显然, 这会改变逆序对的奇偶性, 所以, 这两种方案相互抵消了!  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;到此, 我们可以用$DFS$或$Floyd$求出$F$矩阵, 再使用[$Gauss$消元](https://baike.baidu.com/item/%E9%AB%98%E6%96%AF%E6%B6%88%E5%85%83%E6%B3%95)就可以哒! ( $ps$. 再模意义下的行列式也能直接消元, 不需要求逆元哟! )
```cpp
#include <cstdio>
#include <vector>
#include <assert.h>

#define Int register int

using namespace std;

typedef long long int LL;

const int MAXN = 600, MAXM = 100000;
bool Vis[MAXN + 5] = {};
int n, m, p, Cnte, Head[MAXN + 5] = {};
int f[MAXN + 5][MAXN + 5] = {}, ind[MAXN + 5] = {}, outd[MAXN + 5] = {};
LL det[MAXN + 5][MAXN + 5] = {};
vector<int> Sink, Source;

struct Edge {
	int To, _nxt;
} Graph[MAXM + 5] = {};

inline int Fix ( const LL x ) {
	return ( x % p + p ) % p;
}

inline void Link ( const int From, const int To ) {
	Graph[++ Cnte] = { To, Head[From] };
	Head[From] = Cnte, ++ ind[To], ++ outd[From];
}

inline void DFS ( const int u ) {
	Vis[u] = true;
	if ( ! outd[u] ) f[u][u] = 1;
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ! Vis[v = Graph[i].To] ) DFS ( v );
		for ( unsigned int j = 0; j ^ Sink.size (); ++ j ) {
			f[u][Sink[j]] = Fix ( 1LL * f[u][Sink[j]] + f[v][Sink[j]] );
		}
	}
}

inline void Calculate ( const int n ) {
	LL Ans = 1, f = 1;
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = i + 1; j <= n; ++ j ) {
			int x = i, y = j;
			while ( det[y][i] ) {
				LL t = det[x][i] / det[y][i];
				for ( Int k = i; k <= n; ++ k ) {
					det[x][k] = Fix ( det[x][k] - 1LL * det[y][k] * t % p );
				}
				swap ( x, y );
			}
			if ( x ^ i ) {
				swap ( det[i], det[x] );
				f = -f;
			}
		}
		if ( ! det[i][i] ) {
			puts ( "0" );
			return ;
		} else {
			Ans = 1LL * Ans * det[i][i] % p;
		}
	}
	Ans = Fix ( Ans * f );
	printf ( "%lld\n", Ans );
}

inline void Work () {
	scanf ( "%d %d %d", &n, &m, &p );
	for ( Int i = 1, s, t; i <= m; ++ i ) {
		scanf ( "%d %d", &s, &t );
		Link ( s, t );
	}
	for ( Int i = 1; i <= n; ++ i ) {
		if ( ! ind[i] ) {
			Source.push_back ( i );
		}
		if ( ! outd[i] ) {
			Sink.push_back ( i );
		}
	}
	for ( Int i = 1; i <= n; ++ i ) {
		if ( ! ind[i] ) {
			DFS ( i );
		}
	}
	assert ( Source.size () == Sink.size () );
	for ( unsigned int i = 0; i ^ Source.size (); ++ i ) {
		for ( unsigned int j = 0; j ^ Sink.size (); ++ j ) {
			det[i + 1][j + 1] = f[Source[i]][Sink[j]];
		}
	}
	Calculate ( Sink.size () );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：uenohara_ayano (赞：1)

~~刚刚在机房看 zhihu 被抓摆了，教练让我落实这道题并下午分享，好难w。~~

题意：给出一个 DAG，然后有源点和汇点，要求源点和汇点两两匹配，并且将他们连接在一起的路径不能有相交部分，配对后源点从小到大排序，对应出来的汇点的序列的逆序对数量如果是偶数就有 $1$ 的贡献，否则就有 $-1$ 的贡献。

我们先考虑找出源点和汇点，然后在 DAG 上 dp 求出每个源点到每个汇点的方案数，把这个丢进一个矩阵 $S$ 里。

然后考虑先忽略掉路径不能重复的限制条件，考虑假设现在汇点序列为 $T$，那么很明显的对答案的贡献为 $(-1)^{\sigma(T)}\prod_{i=1}^n S_{i,T_i}$，其中 $\sigma(T)$ 为序列 $T$ 的逆序对数量。

你发现排列 $T$ 是一个全排列，你再来看这个式子，你发现他像一个行列式求和对吧。

不对，因为还有相交的，但是相交的我们可以不去考虑他，如果路径相交意味着路径可替换，替换之后逆序对数量的奇偶性变化，大白话来讲，俩方案抵消了不产生贡献，所以相交的可以直接不考虑了。

所以直接行列式求和就做完了。

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF167E)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看翻译首先会看到这样一句非常拗口的话：  

> 把源点按标号1到n排序后，得到的对应汇点序列的逆序数对的个数是奇数，那么A给B一块钱，否则B给A一块钱。 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;把它翻译成数学的语言，就相当于一个二元组$(a,b)$的排列，以$a$为关键字排列后，$b$对应的排列$p$的逆序对数$t(p)$，则$A$的收益就是$(-1)^{t(p)}$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;想到了什么？  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;行列式！  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一个$n\times n$的矩阵的行列式就是：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![行列式示例.png](https://i.loli.net/2019/08/21/jL4PYJHZEw5duCA.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是我们就很自然地想到了构造一个矩阵后求它的行列式。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先考虑路径不相交的情况，此时$a_{ij}$就是从第$i$个源点走到第$j$个汇点的方案总数，这个可以记忆化搜索，或者$DP$，或者$Floyed$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后考虑路径相交的情况。如果两条路径相交，比如，$u$号源点到$v$号汇点的路径和$p$号源点到$q$号汇点的路径相交了，那么我们找到了两条路径的最后一个交点$x$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![show1.png](https://i.loli.net/2019/08/21/RGj7MtSXcQTwYio.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们翻转路径$(x,v)$和$(x,q)$，这样路径就变成了$(u,q)$和$(p,v)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![show2.png](https://i.loli.net/2019/08/21/jd5HWh4yfai612r.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;需要注意的是，现在两条路径还是相交的，所以它们还是不合法。**不过**，由于终点翻转，所以此时这个路径对应的行列式系数就要乘上一个$-1$，在最后的计算中，这两个不合法方案就会**互相抵消**。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;也就是说，相交路径压根就不会影响答案......  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以求出点到点的方案之后放到矩阵里面直接求它的行列式就可以了。高斯消元$O(n^3)$
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long LL;

const int MAXN = 605, MAXM = 1e5 + 5;

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

int p;

struct edge
{
	int to, nxt;
}Graph[MAXM];

struct matrix
{
	int mat[MAXN][MAXN];
	int n, m;
	matrix()
	{
		memset( mat, 0, sizeof( mat ) );
		n = m = 0;
	}
	int* operator [] ( const int indx )
	{
		return mat[indx];
	}
}dp;

int f[MAXN][MAXN];
int sta[MAXN], tar[MAXN];
int into[MAXN], outo[MAXN];
int head[MAXN];
int N, M, cnt1, cnt2, cnt;
bool visited[MAXN] = {};

void addEdge( const int from, const int to )
{
	cnt ++;
	Graph[cnt].to = to;
	Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

int qkpow( int base, int indx )
{
	int res = 1;
	while( indx )
	{
		if( indx & 1 )
		{
			res = 1ll * res * base % p;
		}
		base = 1ll * base * base % p;
		indx >>= 1;
	}
	return res % p;
}

int inv( const int a )
{
	return qkpow( a, p - 2 );
}

int fix( const int a )
{
	return ( 1ll * a % p + p ) % p;
}

int det()
{
	int n = dp.n;
	int opt = 1, indx, tmp, coe = 1, inver;
	for( int i = 1 ; i <= n && opt <= n ; i ++, opt ++ )
	{
		indx = -1;
		for( int j = i ; j <= n ; j ++ )
		{
			if( dp[j][opt] )
			{
				indx = j;
				break;
			}
		}
		if( indx == -1 )
		{
			i --;
			continue;
		}
		if( indx ^ i ) coe = -coe;
		std :: swap( dp.mat[indx], dp.mat[i] );
		inver = inv( dp[i][opt] );
		for( int j = i + 1 ; j <= n ; j ++ )
		{
			tmp = p - 1ll * dp[j][opt] * inver % p;
			for( int k = 1 ; k <= n ; k ++ )
			{
				dp[j][k] = ( dp[j][k] + 1ll * dp[i][k] * tmp % p ) % p;
			}
		}
	}
	int res = 1;
	for( int i = 1 ; i <= n ; i ++ )
	{
		res = 1ll * res * dp[i][i] % p;
	}
	if( coe < 0 ) res = -res;
	return ( res % p + p ) % p;
}

void dfs( const int u )
{
	visited[u] = true;
	if( ! outo[u] )
	{
		f[u][u] = 1;
		return;
	}
	int v;
	for( int i = head[u] ; i ; i = Graph[i].nxt )
	{
		v = Graph[i].to;
		if( ! visited[v] ) dfs( v );
		for( int j = 1 ; j <= cnt2 ; j ++ )
		{
			f[u][tar[j]] = ( f[u][tar[j]] + f[v][tar[j]] ) % p;
		}
	}
}

signed main()
{
	int fr, to;
	read( N ), read( M ), read( p );
	for( int i = 1 ; i <= M ; i ++ )
	{
		read( fr ), read( to );
		addEdge( fr, to );
		outo[fr] ++, into[to] ++;
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		if( ! into[i] ) sta[++cnt1] = i;
		if( ! outo[i] ) tar[++cnt2] = i;
	}
	for( int i = 1 ; i <= cnt1 ; i ++ ) 
		dfs( sta[i] );
	dp.n = dp.m = cnt1;
	for( int i = 1 ; i <= cnt1 ; i ++ )
	{
		for( int j = 1 ; j <= cnt1 ; j ++ )
		{
			dp[i][j] = f[sta[i]][tar[j]];
		}
	}
	write( det() ), putchar( '\n' );
	return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF167E Wizards and Bets

首先这题意一股浓浓的行列式的味道，毕竟选择的排列的逆序对奇偶决定值的正负号。

定义行列式 $A$，其中 $a_{i,j}$ 表示源点 $i$ 到汇点 $j$ 的路径方案数，在不考虑路径重合的情况下，答案就是行列式的值 $|A|$。

可这题要求路径两两不相交！（但其实不影响的！）

考虑路径 $S_1\to T_1,S_2\to T_2$，只要它们相交，那么路径 $S_1\to T_2,S_2\to T_1$ 肯定也是相交的不合法路径，在行列式的意义上  $S_1\to T_1,S_2\to T_2$ 和 $S_1\to T_2,S_2\to T_1$ 相当于交换 $S_1,S_2$ 两行的选择的列的编号，逆序对奇偶性发生改变，于是就相加为 $0$，直接抵消掉了！

所以我们不用考虑任何路径相交，只需用拓扑排序独立求出每个源点到每个汇点的路径方案数，再高斯消元求行列式的值就行了，时间复杂度为 $O(N(N+M)+N^2(N+\log V))$。（用 $\%$ 取模有点太慢，建议加法直接手写取模）

```code
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=605,M=1e5+100;
int n,m,mod,ind[N],outd[N],cnt,ids[N],idt[N];
vector<int> s,t,E[N];
int f[N][N],a[N][N];
queue<int> q;
void add(int &v,int u){
	v=(u+v>=mod)?u+v-mod:u+v;
}
void topsort(){
	rep(i,1,cnt) f[i][s[i-1]]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(auto y:E[x]){
			rep(i,1,cnt) add(f[i][y],f[i][x]);
			if(!--ind[y]) q.push(y);
		}
	}
	rep(i,1,cnt) rep(j,1,cnt) a[i][j]=f[i][t[j-1]];
}
void Gauss(){
	int ans=1,mu=1;
	rep(i,1,cnt){
		rep(j,i+1,cnt){
			while(a[i][i]){
				int tmp=a[j][i]/a[i][i];
				rep(k,1,n) add(a[j][k],-1ll*tmp*a[i][k]%mod+mod);
				swap(a[i],a[j]),mu=mod-mu;
			}
			swap(a[i],a[j]),mu=mod-mu;
		}
	}
	rep(i,1,cnt) ans=1ll*ans*a[i][i]%mod;
	ans=1ll*ans*mu%mod;
	write(ans,'\n');
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,m,mod);int u,v;
	rep(i,1,m){
		read(u,v);
		E[u].pb(v);ind[v]++,outd[u]++;
	}
	rep(i,1,n) if(!ind[i]) ids[i]=++cnt,s.pb(i),q.push(i);
	cnt=0;
	rep(i,1,n) if(!outd[i]) idt[i]=++cnt,t.pb(i);
	topsort();
	Gauss();
	return 0;
}
```



---

## 作者：C20203030 (赞：0)

## 一、题目

**题目：**
![在这里插入图片描述](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3Uub3JnL3VwbG9hZC9waWMvNzM4NTEucG5n) 

## 二、解法

先考虑不相交路径的限制，令$a[i][j]$为从第$i$个入度为0的点走到第$j$出度为0的点的方案数，由于行列式的定义，这个矩阵的矩阵的行列式的值就是答案。

再考虑路径不相交的情形，发现答案不变，这是因为对于任一种两条路径相交的方案$x$，选择这对路径上相交的最后一个点，将这个点之后的路径反转，一定会映射到另一种路径相交的方案$y$。

怎么更清楚的理解它呢？在行列式生成的排列中，我们交换$bx$和$by$，由于求和中的累乘值不会改变，我们只需要考虑交换后逆序对数的变化，由于会生成两个$bx，by$位置相反的序列，所以交换后正负还是会抵消，说明了反转对答案没有影响。

我们先跑一遍dfs，再把矩阵消成一个上三角行列式，对角线求乘积即可，注意高斯消元的写法会与约旦高斯消元法有些区别。（本篇题解没什么公式，想要更理解请参照[WXK](https://krain.blog.luogu.org/solution-cf167e)大佬的博客）。


```cpp
#include <cstdio>
#include <vector>
#include <iostream>
#define LL long long
using namespace std;
const LL MAXN = 100005;
LL read()
{
	LL x=0,flag=1;char c;
	while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
	while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*flag;
}
LL n,m,mod,tot,f[605],in[605],out[605];
LL a[605][605],t[605][605];
bool vis[605];
vector<LL> fr,to;
struct edge
{
	LL v,next;
}e[MAXN];
void dfs(LL u)
{
	vis[u]=1;
	if(!out[u]) t[u][u]=1;
	for(LL i=f[u];i;i=e[i].next)
	{
		LL v=e[i].v;
		if(!vis[v]) dfs(v);
		for(LL i=0;i<to.size();i++)
			t[u][to[i]]=(t[u][to[i]]+t[v][to[i]])%mod;
	}
}
LL qkpow(LL a,LL b)
{
	LL res=1;
	while(b>0)
	{
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
void gauss(LL n)
{
	LL mark=1;
	for(LL i=1;i<=n;i++)
	{
		LL r=i;
		for(;r<=n;r++)
			if(a[r][i])
				break;
		if(i^r) mark=-mark;
		swap(a[r],a[i]);
		for(LL j=i+1;j<=n;j++)
		{
			LL tmp=a[j][i]*qkpow(a[i][i],mod-2)%mod;
			for(LL k=i;k<=n;k++)
				a[j][k]=(a[j][k]-a[i][k]*tmp%mod+mod)%mod;
		}
	}
	LL ans=mark;
	for(LL i=1;i<=n;i++)
		ans=ans*a[i][i]%mod;
	printf("%lld\n",(ans%mod+mod)%mod);
}
int main()
{
	n=read();m=read();mod=read();
	for(LL i=1;i<=m;i++)
	{
		LL u=read(),v=read();
		e[++tot]=edge{v,f[u]},f[u]=tot;
		in[v]++;out[u]++;
	}
	for(LL i=1;i<=n;i++)
	{
		if(!in[i]) fr.push_back(i);
		if(!out[i]) to.push_back(i);
	}
	for(LL i=1;i<=n;i++)
		if(!in[i])
			dfs(i);
	for(LL i=0;i<fr.size();i++)
		for(LL j=0;j<to.size();j++)
			a[i+1][j+1]=t[fr[i]][to[j]];
	gauss(fr.size());
}
```



---

