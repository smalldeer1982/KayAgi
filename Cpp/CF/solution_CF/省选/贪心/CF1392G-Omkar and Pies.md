# Omkar and Pies

## 题目描述

Omkar has a pie tray with $ k $ ( $ 2 \leq k \leq 20 $ ) spots. Each spot in the tray contains either a chocolate pie or a pumpkin pie. However, Omkar does not like the way that the pies are currently arranged, and has another ideal arrangement that he would prefer instead.

To assist Omkar, $ n $ elves have gathered in a line to swap the pies in Omkar's tray. The $ j $ -th elf from the left is able to swap the pies at positions $ a_j $ and $ b_j $ in the tray.

In order to get as close to his ideal arrangement as possible, Omkar may choose a contiguous subsegment of the elves and then pass his pie tray through the subsegment starting from the left. However, since the elves have gone to so much effort to gather in a line, they request that Omkar's chosen segment contain at least $ m $ ( $ 1 \leq m \leq n $ ) elves.

Formally, Omkar may choose two integers $ l $ and $ r $ satisfying $ 1 \leq l \leq r \leq n $ and $ r - l + 1 \geq m $ so that first the pies in positions $ a_l $ and $ b_l $ will be swapped, then the pies in positions $ a_{l + 1} $ and $ b_{l       + 1} $ will be swapped, etc. until finally the pies in positions $ a_r $ and $ b_r $ are swapped.

Help Omkar choose a segment of elves such that the amount of positions in Omkar's final arrangement that contain the same type of pie as in his ideal arrangement is the maximum possible. Note that since Omkar has a big imagination, it might be that the amounts of each type of pie in his original arrangement and in his ideal arrangement do not match.

## 说明/提示

In the first test case, the swaps will go like this:

- Swap $ 1 $ and $ 3 $ : 11000 becomes 01100
- Swap $ 3 $ and $ 5 $ : 01100 becomes 01001
- Swap $ 4 $ and $ 2 $ : 01001 becomes 00011

 The final arrangement is the same as the ideal arrangement 00011, so there are $ 5 $ positions with the same type of pie, which is optimal. In the second test case, the swaps will go like this:

- Swap $ 1 $ and $ 3 $ : 11000 becomes 01100
- Swap $ 1 $ and $ 5 $ : 01100 becomes 01100
- Swap $ 4 $ and $ 2 $ : 01100 becomes 00110
- Swap $ 1 $ and $ 5 $ : 00110 becomes 00110

 The final arrangement has $ 3 $ positions with the same type of pie as the ideal arrangement 00011, those being positions $ 1 $ , $ 2 $ , and $ 4 $ . In this case the subsegment of elves $ (l, r) = (2, 3) $ is more optimal, but that subsegment is only length $ 2 $ and therefore does not satisfy the constraint that the subsegment be of length at least $ m = 3 $ .

## 样例 #1

### 输入

```
4 2 5
11000
00011
1 3
3 5
4 2
3 4```

### 输出

```
5
1 3```

## 样例 #2

### 输入

```
4 3 5
11000
00011
1 3
1 5
2 4
1 5```

### 输出

```
3
1 4```

# 题解

## 作者：crashed (赞：10)

# 题目
[点这里](https://www.luogu.com.cn/problem/CF1392G)看题目。   
# 分析
~~这种题目显然需要转化。~~   
   
考虑我们该怎么枚举区间。由于操作顺序是从前到后的，因此可以想到**将一段操作区间拆分成两段操作的后缀**。   
   
那么，如何实现操作的 " 减法 " 呢？也就是说，我们应如何**消去另一后缀的影响**？   
   
注意到，如果我们同时对 $s$ 和 $t$ 执行操作的话，我们就相当于没操作。因此，如果我们要执行 $[L,R]$ 的操作，我们可以对 $s$ 执行 $[L,n]$ 的操作，对 $t$ 执行 $[R+1,n]$ 操作。这样 $[R+1,n]$ 的操作就相当于被 " 抵消 " 了。   
   
于是，现在可以将问题修改为：   
   
> 有序列 $a$ 和 $b$，其中 $a_i$ 为对 $s$ 施加了 $[i,n]$  的操作后的串；$b_i$ 为对 $t$ 施加了 $[i,n]$ 的操作后的串。令 $w(S,T)$ 为两串中相同位置的数量。  
> 求出 $\max\{w(a_i,b_j)|1\le i,j\le n,|i-j|\ge m\}$。   
   
$a$ 和 $b$ 两个序列都可以 $O(nk)$ 预处理出来。   

考虑 $a$ 和 $b$ 相同数位如何计算。设 $p$ 为 $a$ 中 1 的个数，$q$ 为 $b$ 中 1 的个数，$r$ 为 $a,b$ 共同的 1 的个数，那么相同数位的数量就是 $(k-p-q+r)+r=2r+k-p-q$。由于 $k,p,q$ 在一开始就确定了，所以我们只需要最大化 $r$ 就好了。   
   
因此我们可以直接枚举最终的 $a_i$ 和 $b_j$ 的公共的 1 的状态，并求出此时在 $a$ 中的最小位置和 $b$ 中的最大位置。可以利用 DP：   
   
$$
\begin{aligned}
f(0,S)=\min\{i|S\subset a_i\}\\
f(1,S)=\max\{i|S\subset b_i\}
\end{aligned}
$$   
   
其中的 $A\subset B$ 表示 $A$ 的所有的 1 在 $B$ 中都有。这个 DP 可以 $O(2^k\times k)$ 地转移出来：   
   
最后我们只需要枚举 $S$，并且检查 $f(1,S)-f(0,S)$ 是否 $\ge m$。如果可以就更新答案。   
   
时间复杂度是 $O(nk+2^k\times k)$。       
  
# 代码
```cpp
#include <cstdio>
 
#define Count __builtin_popcount 
 
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 5, MAXK = 25, MAXS = ( 1 << 20 ) + 5;
 
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
void swapp( _T &x, _T &y )
{
    _T t = x; x = y, y = t;
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
 
int N, M, K;
 
typedef struct Permutation
{
    int p[MAXK] = {};
    
    Permutation() 
    {
        for( int i = 1 ; i <= K ; i ++ )
            p[i] = i;
    }
    
    int& operator [] ( const int indx ) { return p[indx]; }
}Per;
 
int f[2][MAXS];
Per suf[MAXN], s, t;
 
Per operator + ( Per a, Per p )
{
    Per ret;
    for( int i = 1 ; i <= K ; i ++ )
        ret[i] = a[p[i]];
    return ret;
}
 
int Transform( Per num )
{
    int ret = 0;
    for( int i = 1 ; i <= K ; i ++ )
        ret = ret << 1 | num[i];
    return ret;
}
 
int main()
{
    read( N ), read( M ), read( K );
    for( int i = 1 ; i <= K ; i ++ ) scanf( "%1d", &s[i] );
    for( int i = 1 ; i <= K ; i ++ ) scanf( "%1d", &t[i] );
    for( int i = 1, a, b ; i <= N ; i ++ )
        read( a ), read( b ), suf[i] = Permutation(),
        swapp( suf[i][a], suf[i][b] );
    suf[N + 1] = Permutation();
    for( int i = N ; i ; i -- ) 
        suf[i] = suf[i] + suf[i + 1];
    int upper = 1 << K;
    for( int S = 0 ; S < upper ; S ++ )
        f[0][S] = INF, f[1][S] = -INF;
    for( int i = N + 1 ; i ; i -- )
    {
        int val = Transform( s + suf[i] );
        f[0][val] = MIN( f[0][val], i );
        val = Transform( t + suf[i] );
        f[1][val] = MAX( f[1][val], i ); 
    }
    int a = Count( Transform( s ) ), 
        b = Count( Transform( t ) ), 
        c, ans = -INF, L, R, val;
    for( int S = upper - 1 ; ~ S ; S -- )
    {
        for( int i = 0 ; i < K ; i ++ )
            if( ! ( S >> i & 1 ) )
                f[0][S] = MIN( f[0][S], f[0][S | ( 1 << i )] ),
                f[1][S] = MAX( f[1][S], f[1][S | ( 1 << i )] );
        if( f[1][S] - f[0][S] >= M )
        {
            c = Count( S );
            val = 2 * c - a - b + K;
            if( val > ans ) L = f[0][S], R = f[1][S] - 1, ans = val;
        }
    }
    write( ans ), putchar( '\n' ); 
    write( L ), putchar( ' ' ), write( R ), putchar( '\n' );
    return 0;
} 
```

---

## 作者：Froggy (赞：6)

方便起见，先规定一些东西：

$w(a,b)$ 表示 01 串 $a$ 和 $b$ 的“相似度”（即相同的位数）。

$s\xrightarrow{p(l,r)}s'$ 表示 01 串 $s$ 经过依次完成操作序列中的 $p_l,p_{l+1},\cdots,p_r$ 得到 $s'$。

$s\xrightarrow{p'(l,r)}s'$ 表示 01 串 $s$ 经过依次完成操作序列中的 $p_r,p_{r-1},\cdots,p_l$ 得到 $s'$。

---

再来几个定理及引理。

### 定理 1：

>$\forall p,l,r$，若 $s\xrightarrow{p(l,r)}s'$ 且 $t\xrightarrow{p(l,r)}t'$，则 $w(s,t)=w(s',t')$。

证明：把 $s$ 和 $t$ 的对应位都看成一对，操作后都不会拆开。

虽然比较显然，但是**至关重要**。

### 引理 1：

>$\forall p,l,r$，若 $s\xrightarrow{p(l,r)}s'$ 且 $t\xrightarrow{p'(l,r)}t'$，则 $w(s',t)=w(s,t')$。

证明：$s\xrightarrow{p(l,r)}s'\xrightarrow{p'(l,r)}s$。


### 引理 2：

>$\forall p,l,r$，若 $s\xrightarrow{p(l,r)}s'$，$s\xrightarrow{p'(1,l-1)}s''$，$t\xrightarrow{p'(1,r)}t''$，则 $w(s',t)=w(s'',t'')$。

证明：（根据引理 1 和定理 1 不难得到，请自行思考）。

### 定理 2：

>最大化 $w(s,t)$ 就相当于最大化 $s$ 和 $t$ 同时是 $1$ 的位数。

证明：设 $s$ 有 $a$ 位为 $1$，$t$ 有 $b$ 位为 $1$，$s$ 和 $t$ 同时是 $1$ 的位数有 $c$ 位，$s,t$ 的长度均为 $k$。不难得到 $w(s,t)=2c+k-a-b$。由于此题 $a,b,k$ 都是固定的，所以最大化 $w(s,t)$ 就相当于最大化 $c$。 


---

设 $s\xrightarrow{p'(1,i)}s_i$，$t\xrightarrow{p'(1,i)}t_i$。特别地，$s=s_0$，$t=t_0$。

那么题目就转化为求 $\max\limits_{p2-p1\geq m}w(s_{p1},t_{p2})$。再根据**定理 2**可知，只需求 $\max\limits_{p2-p1\geq m}s_{p1}\text{和}t_{p2}\text{同时是}1\text{的位数}$。

考虑把 01 串化成二进制数然后用状压 dp 求解。

$dp_{0,x}$ 表示 $\min\limits_{x\in s_i}i$，$dp_{1,x}$ 表示 $\max\limits_{x\in t_i}i$。

从大到小 $x$ 然后 $\mathcal{O}(k)$ 枚举 $x$ 为 $1$ 的位进行转移即可。

若 $dp_{1,x}-dp_{0,x}\geq m$ 则说明存在 $p1,p2$ 满足 $p2-p1\geq m$ 且 $x$ 是 $s_{p1}$ 和 $t_{p2}$ 的交集的子集。可以用 $\mathrm{popcount}(x)$ 更新答案。

时间复杂度：$\mathcal{O}(nk+2^kk)$。

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000100
#define K 23
const int inf=0x3f3f3f3f;
int dp[2][1<<20];
int n,m,k,p[K],a[K],b[K],ans,L,R;
char s[K],t[K];
void Trans(int *a,char *s){
	for(int i=1;i<=k;++i){
		a[p[i]]=s[i]-'0';
	}
}
int main(){
	n=read(),m=read(),k=read();
	scanf("%s",s+1);
	scanf("%s",t+1);
	for(int i=1;i<=k;++i){
		p[i]=i;
	}
	memset(dp[0],0x3f,sizeof(dp[0])); //S
	memset(dp[1],~0x3f,sizeof(dp[1])); //T
	for(int i=0;i<=n;++i){
		if(i){	
			int x=read(),y=read();
			swap(p[x],p[y]);
		}
		int ga=0,gb=0;
		Trans(a,s),Trans(b,t);
		for(int j=1;j<=k;++j){
			ga=ga<<1|a[j];
			gb=gb<<1|b[j];
		}
		dp[0][ga]=min(dp[0][ga],i);
		dp[1][gb]=max(dp[1][gb],i);
	}
	ans=-inf;
	for(int i=(1<<k)-1;i>=0;--i){
		for(int j=0;j<k;++j){
			if((i>>j)&1){
				dp[0][i^(1<<j)]=min(dp[0][i^(1<<j)],dp[0][i]);
				dp[1][i^(1<<j)]=max(dp[1][i^(1<<j)],dp[1][i]);
			}
		}
		if(dp[1][i]-dp[0][i]>=m){
			if(__builtin_popcount(i)>ans){	
				ans=max(ans,__builtin_popcount(i));
				L=dp[0][i]+1,R=dp[1][i];
			}
		}
	}
	ans<<=1;
	ans+=k;
	for(int i=1;i<=k;++i){
		ans-=(s[i]=='1')+(t[i]=='1');
	}
	printf("%d\n%d %d\n",ans,L,R);
	return 0;
}

```

---

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!







---

## 作者：缪凌锴_Mathew (赞：4)

[cnblogs](https://www.cnblogs.com/Mathew-Miao/articles/18706186)

### 前言

这篇题解复杂度不对，不是正解（~~大力数据结构~~）。

### 解法

称 $A_{i,j}$ 为 $A$ 经过 $i\sim j$ 的操作后的值。

那么 $s_{i,j}\oplus t=s_{i,n}\oplus t_{j+1,n}$

预处理 $S_i=s_{i,n},T_i=t_{i,n}$。

枚举 $s$ 的开头 $i$，相当于求出 $\min\limits_{j=i+m}^{n+1} \operatorname{popcount}(S_i\oplus T_j)$。

扫描线 $i$，动态加点查询异或 $\operatorname{popcount}$ 最大值，似乎很难。

[rpxleqxq](https://www.luogu.com.cn/problem/P7906) 里面的那个 trie 似乎就可以。

开一棵 $1024$ 叉的 trie（共 $2$ 层），即开一个 $1024\times 1024$ 的数组 $tr$。

$tr_{x,i}$ 表示二进制 $T_j$ 前 $10$ 位为 $x$，$S_i$ 后 $10$ 位为 $i$ 的答案。

$\gdef\f#1{\lfloor\frac{#1}{1024}\rfloor}$
$\gdef\df#1{\Big\lfloor\dfrac{#1}{1024}\Big\rfloor}$
$\gdef\g#1{#1\operatorname{bitand}1023}$

加点 $v$ 的时候修改底层的答案：$tr_{\f v,i}\gets\min\Big(tr_{\f v,i},\operatorname{popcount}((\g v)\oplus i)\Big)$。

查询 $v$ 的时候遍历顶层：$\min_{i=0}^{1023}\Big(tr_{i,\g v}+\operatorname{popcount}(\df v\oplus i)\Big)$。

记得再记一个数组记录最大位置（因为要 $r-l$ 最大）

时间复杂度 $O(n 2^{\frac k 2})$ 了。

算了一下，大概 $10^9$ 左右，但是常数小！！！

加上一些剪枝，相同的 $S_i$ 取最前的，相同的 $T_i$ 取最后的。

修改比查询快，改为 $512\times2048$ 的 trie。

然后就过了？

### 代码

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<numeric>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=(1<<20)+10;
const int N=1e6;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
int n,m,k,s,t;
int ans=INF,ansl,ansr;
int a[MAXN],b[MAXN];
int p[25];
int S[MAXN],T[MAXN];
int cnt[2048];
int res[512][2048],pos[512][2048];
bool vis[MAXN];
int L,R;
inline void add(int p,int v){
	if(vis[v]){
		return ;
	}
	vis[v]=true;
	int x=v>>11,y=v&(R-1);
	for(int i=0;i<R;i++)
	{
		if(res[x][i]>cnt[i^y]){
			res[x][i]=cnt[i^y];
			pos[x][i]=p;
		}
	}
}
inline int qry(int v){
	int x=v>>11,y=v&(R-1),rsv=INF,rsp=n+1;
	for(int i=0;i<L;i++)
	{
		int val=cnt[x^i]+res[i][y];
		if(rsv>val){
			rsv=val;
			rsp=pos[i][y];
		}
		else if(rsv==val){
			rsp=max(rsp,pos[i][y]);
		}
	}
	return rsp;
}
int fir[MAXN];
inline void solve(){
	scanf("%d%d%d",&n,&m,&k);
	auto read=[&](){
		static char str[MAXN];
		scanf("%s",str);
		int res=0;
		for(int i=0;i<k;i++)
		{
			if(str[i]^'0'){
				res|=1<<i;
			}
		}
		return res;
	};
	s=read();
	t=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		a[i]--;
		b[i]--;
	}
	iota(p,p+k,0);
	S[n+1]=s;
	T[n+1]=t;
	for(int i=n;i;i--)
	{
		swap(p[a[i]],p[b[i]]);
		for(int j=0;j<k;j++)
		{
			if(s&(1<<j)){
				S[i]|=1<<p[j];
			}
			if(t&(1<<j)){
				T[i]|=1<<p[j];
			}
		}
	}
	memset(res,0x3f,sizeof(res));
	L=1<<max(0,k-11);
	R=min(2048,1<<k);
	for(int i=0;i<R;i++)
	{
		cnt[i]=__builtin_popcount(i);
	}
	for(int i=n;i;i--)
	{
		fir[S[i]]=i;
	}
	for(int i=n-m+1;i;i--)
	{
		#define val(j) __builtin_popcount(S[i]^T[j])
		add(i+m,T[i+m]);
		if(fir[S[i]]^i){
			continue;
		}
		int p=qry(S[i]);
		if(val(p)<ans){
			ans=val(p);
			ansl=i;
			ansr=p-1;
		}
		else if(val(p)==ans&&p-i>=ansr-ansl+1){
			ansl=i;
			ansr=p-1;
		}
	}
	printf("%d\n%d %d\n",k-ans,ansl,ansr);
}
signed main(){
	#ifdef LOCAL
	atexit([](){fprintf(stderr,"%.3lfs\n",(double)clock()/CLOCKS_PER_SEC);});
	#endif
	solve();
	return 0;
}
```

---

## 作者：yyyyxh (赞：4)

还是记一下这个 trick 吧，虽然很简单但是我认为十分有趣！本质上是 [Maximize the Difference](https://codeforces.com/problemset/problem/1930/F) 做法的扩展。（似乎有人称作 [RainFestivalTree](https://www.luogu.com/article/zr9ophgf)？？？）

这个题经过一些简单转化可以转化为这样一个问题：给定有二进制数序列 $A,B$，求 $\max_{r-l\ge m} |A_l\oplus B_r|$（$|x|$ 即二进制位下一的个数，$\oplus$ 是异或）。

由于这个题有特殊性质，即序列 $A,B$ 中所有元素的 popcount 都相等，所以我们只关注 $|A_l\cap B_r|$，所以绝大多数题解给出了一个基于普通高维后缀和的 $O(k2^k)$。

但是假设序列 $A,B$ 没有任何特殊性质，这个题仍然可以做！我们考虑到异或信息也是可以 FWT 的，我们给 FWT 数组再开一维记录 popcount，合并的时候更新一下，就扩展到了序列任意的情况。这也是环一周和叉老师在模拟赛场上的写法，复杂度为 $O(2^kk^2)$，空间复杂度 $O(2^kk)$。

那我场上又写了个啥抽象玩意呢？事实上，对于上面这个问题，我们可以做到在线维护！

这个做法的基本思想是对于一般的 FWT 问题，假设你要增量维护其结果，你可以暴力 dfs 子集/超集，遇到已经访问了的就回退，这样每个集合只会被增广一次。

那么对于此题中的多带了一维的异或 FWT，其也可以施加暴力 dfs 的技巧。具体地，我们增量维护一个集合 $S$，并记录 $f$ 数组表示对于所有长为 $k$ 数到 $S$ 中数的最小汉明距离，即 $f_x=\min_{y\in S} |x\oplus y|$。

每次往 $S$ 加入一个元素 $x$ 时，我们暴力 dfs 这个元素的邻域，如果当前元素 $y$ 到 $x$ 的距离不小于 $f_y$ 就直接返回。这样，对于每一个元素，其 $f$ 只会至多被更新 $O(k)$ 次，每次更新至多耗费 $O(k)$ 的时间复杂度。总时间复杂度也是 $O(2^kk^2)$，但空间做到了 $O(2^k)$ 且可以强制在线。

如果到当前元素汉明距离比当前答案还大的话还可以剪枝，数据基本不可能卡满而且除了一堆常数，所以事实上这个算法竟然能跑过一大堆 $O(2^kk)$。

```cpp
#include <cstdio>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=x*10+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=10000003,K=20,INF=0x3f3f3f3f;
int n,m,k,o;
int res=INF,ix=-1,iy=-1;
int f[1<<K],ps[1<<K];
bool vis[1<<K];
int px[N],py[N],p[N];
int A[N],B[N];
void dfs(int s,int d,int lim){
	if(d>=res||f[s]<=d) return;
	f[s]=d;
	if(ps[s]>=o+m) res=d,ix=o,iy=ps[s];
	for(int i=lim;i<k;++i) dfs(s^(1<<i),d+1,i+1);
}
int main(){
	n=read();m=read();k=read();
	char cc=getchar();
	while(cc!='0'&&cc!='1') cc=getchar();
	for(int i=0;i<k;++i){
		if(cc=='1') A[n+1]|=(1<<i);
		cc=getchar();
	}
	while(cc!='0'&&cc!='1') cc=getchar();
	for(int i=0;i<k;++i){
		if(cc=='1') B[n+1]|=(1<<i);
		cc=getchar();
	}
	for(int i=0;i<k;++i) p[i]=i;
	for(int i=1;i<=n;++i) px[i]=read()-1,py[i]=read()-1;
	for(int i=n;i;--i){
		int X=p[px[i]],Y=p[py[i]];
		p[px[i]]=Y;p[py[i]]=X;
		px[i]=X;py[i]=Y;
	}
	for(int i=n;i;--i){
		A[i]=A[i+1];B[i]=B[i+1];
		if(((A[i]>>px[i])^(A[i]>>py[i]))&1) A[i]^=(1<<px[i])^(1<<py[i]);
		if(((B[i]>>px[i])^(B[i]>>py[i]))&1) B[i]^=(1<<px[i])^(1<<py[i]);
	}
	for(int i=1;i<=n+1;++i) ps[B[i]]=i;
	for(int s=0;s<(1<<k);++s) f[s]=INF;
	for(o=1;o<=n+1;++o) dfs(A[o],0,0);
	printf("%d\n%d %d\n",k-res,ix,iy-1);
	return 0;
}
```

---

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/18706560)。妈的，第一步就没想到。不过是好题！

---

肯定是考虑将区间拆成 $O(1)$ 个前后缀结构去维护。赛时一直在想前缀，发现做不了。。。

但是考虑后缀就是对的，具体就是注意到若同时给 $S,T$ 进行操作，那么位置数量不变，于是将 $[l,r]$ 拆成 $S$ 上操作 $[l,n]$ 操作、$T$ 上操作 $[r+1,n]$ 操作，这样后面的部分就被抵消了，然后就拆成区间了。

后面都比较套路了。记 $f_i,g_i$ 分别表示 $S,T$ 操作 $[i,n]$ 操作后形成的字符串状态。这个可以记录每个元素具体跑到了哪里去，$O(N)$ 直接求出。

此时答案即为

$$k-\min\limits_{1\le l\le r\le n+1,r-l\ge m}\operatorname{popcount}(f_l\oplus g_r)$$

发现两串的 popcount 恒不变，手玩一下发现答案也可以描述为

$$k-\operatorname{popcount}(S)-\operatorname{popcount}(T)+2\times\max\limits_{1\le l\le r\le n+1,r-l\ge m}\operatorname{popcount}(f_l\cap g_r)$$

转换视角，枚举 $st=f_l\cap g_r$，对每个 $st$ 记录 $st\subseteq f_l$ 的最小的 $l$、$st\subseteq g_r$ 的最大的 $r$。这个可以高维后缀和求出。然后直接 check 每个 $st$ 是否合法并统计答案即可，这一部分是 $O(k2^k)$ 的。

总复杂度 $O(n+k2^k)$。[code](https://codeforces.com/contest/1392/submission/305116696)

---

## 作者：rainygame (赞：2)

省选模拟赛 T1。学长讲了一个很妙的做法，写一下。

交换两个位置这个操作非常不好做，连交换律都没有，也没有单调性。但是注意到如果 $s$ 和 $t$ 同时交换相同的数对，那么就相当于没有交换。根据这个性质，可以将进行 $[l,r]$ 的交换转化为对 $s$ 进行 $[l,n]$ 的交换和对 $t$ 进行 $(r,n]$ 的交换。

那么就可以令 $S_i$ 表示进行了 $[i,n]$ 的交换之后的 $s$，$T_i$ 同理（注意要按顺序进行交换，具体实现可以维护一个 $p_i$ 表示 $i$ 转到了哪里）。那么问题转化成对于 $i-j\ge m$，求 $\text{popcount}(S_i\oplus T_j)$ 的最大值（$\oplus$ 表示异或）。考虑枚举 $x=S_i\oplus T_j$，问题转化为对于一个 $x$，问 $\max\limits_{S_i\oplus T_j=x} i-j$ 是否不小于 $m$。

这样问题就转化成了卷积的形式，但是 $\max$ 不可逆，无法进行异或卷积。又注意到因为 $\text{popcount}(S_i)$ 和 $\text{popcount}(T_j)$ 是固定的，所以 $\text{popcount}(S_i\oplus T_j)=k-\text{popcount}(S_i)-\text{popcount}(T_j)+2\text{popcount}(S_i\wedge T_j)$ 也是只和 $S_i\wedge T_j$ 有关（$\wedge$ 表示按位与）。因此考虑枚举 $x=S_i\wedge T_j$，问题即为求 $\max\limits_{S_i\wedge T_j=x} i-j$ 是否不小于 $m$。

根据 [[ARC100E] Or Plus Max](https://www.luogu.com.cn/problem/AT_arc100_c) 的 trick，注意到将问题改为 $\max\limits_{S_i\wedge T_j\subset x} i-j$ 不影响答案，因为若 $S_i\wedge T_j=x^\prime>x$，那么在 $x^\prime$ 处必定也会进行答案的更新。而这个就可以转化为求 $\max\limits_{S_i\subset x}i-\max\limits_{T_j\subset x}j$，通过两次 SOSDP 即可求出。

时间复杂度 $O(nk+k2^k)$。[submission](https://codeforces.com/contest/1392/submission/305112057)

---

## 作者：Purslane (赞：2)

# Solution

记 $A_i$ 为 $i$ 进行了 **$i$ 以后所有操作的结果**（为什么是 $i$ 之后？如果是 $i$ 之前，不能差分，因为前方操作是会影响后面的结构的）

同样设 $B_i$。于是我们就求
$$
\min \text{popcount}_{r - l \ge m,1 \le l ,r \le n+1} A_l \oplus B_r
$$
注意到 $A$ 和 $B$ 的 $\text {popcount}$ 都是恒定的，所以我们需要最大化 $A \cap B$。

一种方法是**动态插入 $B$，动态查询 $A$**。将 $B$ 插入时，通过一些手段将其所有**未被覆盖的子集全找出来**（注意，为了找一个子集，最多遍历 $k^2$ 次，所以找子集复杂度也是 $O(k^22^k)$），然后将他们全部加入集合 $S$ 中。再暴力维护 $S$ 的高维前缀和，每个位置最多被更新 $k$ 次，可以做到 $O(k^2 2^k)$（注意他可能会浪费很多邻域，但是你维护一个指针加上及时剪枝可以跑得特别快）。这样更容易扩展，而且是在线的。

PS：这部分复杂度偏高都是由讨厌的邻域造成的，所以有没有什么方法可以保证每次遍历都是有效的，如果你会请在这篇题解下面 comment 一下谢谢。

另一种方法是直接对每个 $S$ 求出 $A_i$ 包含 $S$ 的最小下标和 $B_i$ 包含 $S$ 的最大下标，直接判断是否符合要求。这样是 $O(k2^k)$ 的，不过离线。

实现了第二种。本题最困难的地方应该就是通过**操作 $B$ 实现差分**，以及发现**必须在后缀而不是前缀上做文章**。

---

## 作者：RainySoul (赞：2)

这个操作我们不能直接做的原因是有 $l,r$ 两个参数。

考虑一个事情，如果一段操作我对着 $S$ 做了一次，又对着 $T$ 做了一次，那么就相当于没有做。

因此对 $S$ 做 $[l,n]$ 得到 $s$，对 $T$ 做 $[r+1,n]$ 得到 $t$，**$s$ 与 $t$ 相同位置个数就等于对 $S$ 做 $[l,r]$ 后与 $T$ 的相同位置个数**。处理出来俩个字符串数组 $a_i$ 表示对 $T$ 做 $[i,n]$ 操作得到的字符串，$b_i$ 同理。这部分可以 $O(nk)$ 办到。

注意只有对后缀做才是正确的，因为对 $S$ 做 $[1,l-1]$ 并对 $T$ 做 $[1,r]$ 和做对 $S$ 做 $[l,r]$ 并不等价。这个时候相当于对 $T$ 做 $[l,r]$ 了。

然后考虑你知道了两个串 $s,t$ 如何快速求得他们两个的相同位置数，设 $s$ 中 $1$ 的个数为 $p$，$t$ 中 $1$ 的个数为 $q$，$s$ 与 $t$ 相同位置上的 $1$ 的个数为 $z$。现在这两个串的相同位置数就可以直接求了，$0$ 与 $1$ 匹配的个数是 $(p+q)-2z$，那么剩下的就是相同位置数 $k-((p+q)-2z)=2z-p-q+k$ 了，由于 $p,q,k$ 都是固定的，现在问题转变成求 $\max(z)$。

观察到关键性质：$k \le 20$，可以直接暴力枚举出相同的 $1$ 的位置集合 $S$，然后对于这个 $S$ 找出最小的 $i$ 满足 $S \subseteq a_i$，最大的 $j$ 满足 $S \subseteq b_j$。

找出 $i,j$ 怎么做？先将 $a,b$ 数组初始化进 $\text{dp}$ 数组，然后从大到小枚举 $S$，转移只需要从 $k$ 个更高位转移，具体实现见代码。

时间复杂度 $O(nk+2^kk)$。

Code：

```
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=1000010;
unordered_map<string,int> a,b;
int n,m,k,l[N],r[N],temp[30],now[30],dp[2][(1<<20)+10];
string S,T;
int to_int(string a){
    int x=0;
    for(int i=0;i<(int)a.size();i++)x=x*2+a[i]-'0';
    return x;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    cin>>S>>T;
    for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
    int p=0,q=0;
    for(int i=0;i<k;i++)if(S[i]=='1')p++;
    for(int i=0;i<k;i++)if(T[i]=='1')q++;
    for(int i=1;i<=k;i++)now[i]=i;
    for(int i=n;i>=1;i--){
        for(int j=1;j<=k;j++)temp[j]=j;
        swap(temp[l[i]],temp[r[i]]);
        for(int j=1;j<=k;j++)now[j]=temp[now[j]];
        string s="";
        for(int j=1;j<=k;j++)s+=S[now[j]-1];
        a[s]=i;
    }
    for(int i=1;i<=k;i++)now[i]=i;
    b[T]=n+1;
    for(int i=n;i>=1;i--){
        for(int j=1;j<=k;j++)temp[j]=j;
        swap(temp[l[i]],temp[r[i]]);
        for(int j=1;j<=k;j++)now[j]=temp[now[j]];
        string t="";
        for(int j=1;j<=k;j++)t+=T[now[j]-1];
        if(b[t]==0)b[t]=i;
    }
    for(int i=0;i<(1<<k);i++)dp[0][i]=inf,dp[1][i]=0;
    for(auto it=a.begin();it!=a.end();it++){
        int temp=to_int((*it).first);    
        dp[0][temp]=min(dp[0][temp],(*it).second);
    }
    for(auto it=b.begin();it!=b.end();it++){
        int temp=to_int((*it).first);
        dp[1][temp]=max(dp[1][temp],(*it).second);
    }
    int ans=0,ansl=n,ansr=n;
    for(int S=(1<<k)-1;S>=0;S--){
        for(int i=0;i<k;i++){
            if(((S>>i)&1)==0){
                dp[0][S]=min(dp[0][S],dp[0][S|(1<<i)]);
                dp[1][S]=max(dp[1][S],dp[1][S|(1<<i)]);
            }
        }
        int l=dp[0][S],r=dp[1][S]-1;
        if(r-l+1>=m){
            int res=2*__builtin_popcount(S)-p-q+k;
            if(res>ans){
                ans=res;
                ansl=l,ansr=r;
            }
            else if(res==ans){
                if(r-l>ansr-ansl){
                    ansl=l,ansr=r;
                }
                else if((r-l==ansr-ansl)&&l<ansl){
                    ansl=l,ansr=r;
                }
            }
        }
    }
    cout<<ans<<'\n';
    cout<<ansl<<" "<<ansr;
    return 0;
}
```

---

## 作者：FjswYuzu (赞：1)

因为 $k \leq 20$，所以我们将两个 01 串压缩成 $S,T$。

注意到，我们对 $S$ 顺序操作一段区间 $[l,r]$，相当于先对 $S$ 操作 $[l,n]$，再对 $T$ 操作 $[r+1,n]$。原因是显然的：我们在操作完 $[l,r]$ 之后，将 $S$ 和 $T$ 一并操作 $[r+1,n]$，整个过程不会有任何影响。

注意到，对 $S,T$ 的操作，现在已经形似操作区间 $[p,n]$。于是我们定义 $S_i$ 表示 $S$ 操作完区间 $[i,n]$ 后状态为 $S_i$，$T_i$ 同理，花费 $O(nk)$ 的时间去求出这个东西。求法是，求 $S_i$，相当于在 $S_{i+1}$ 的基础上往前面加入一个交换操作 $(x_i,y_i)$，本质上是交换 $S_{i+1}$ 中 $x_i,y_i$ 表示的位置上的 0 或 1。这个东西可以维护当前排列和这个排列的反函数，不赘述。

最后考虑怎么算答案。如果一定要再次枚举 $S,T$，显然过不了。注意到我们现在只关心 $S ∩ T$ 中 $1$ 的个数 $p$（因为，令 $S$ 中 $1$ 的个数为 $s$，$T$ 中 $1$ 的个数为 $t$，答案可以写成 $k-s-t+2p$）。我们枚举 $S ∩ T$（相当于 $S \& T$，其中 $\&$ 为按位与），如何判断这个 $S ∩ T$ 是否合法？

我们定义 $L_i$（其中 $i$ 是一个状态）表示，$i ⊆ S_{L_i}$ 且 $L_i$ 是满足这个条件的最小的值。$R_i$ 同样可以算，相当于反着求最大的值。这个问题非常的简单，我们直接预处理，然后枚举子集转移取最大最小值就可以了。

这样我们就可以判断合不合法了。注意特判答案为 $0$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int lowbit(int x){return x&(-x);}
int popcount(int x)
{
	int ans=0;
	while(x)	x^=lowbit(x),++ans;
	return ans;
}
int k,m,n,Sp[1000005],Tp[1000005],X[1000005],Y[1000005],swp[25],pos[25],Sc,Tc,dpS[(1<<20)+5],dpT[(1<<20)+5];
int main(){
	scanf("%d %d %d",&k,&m,&n);
	for(int i=1,x;i<=n;++i)	scanf("%1d",&x),Sp[k+1]|=(x<<(i-1)),Sc+=x;
	for(int i=1,x;i<=n;++i)	scanf("%1d",&x),Tp[k+1]|=(x<<(i-1)),Tc+=x;
	for(int i=1;i<=k;++i)	scanf("%d %d",&X[i],&Y[i]);
	for(int i=1;i<=n;++i)	swp[i]=pos[i]=i;
	for(int i=k;i;--i)
	{
		swap(swp[pos[X[i]]],swp[pos[Y[i]]]);
		swap(pos[X[i]],pos[Y[i]]);
		for(int j=1;j<=n;++j)
		{
			int st=swp[j];
			if((Sp[k+1]>>(st-1))&1)	Sp[i]|=(1<<(j-1));
			if((Tp[k+1]>>(st-1))&1)	Tp[i]|=(1<<(j-1));
		}
	}
	memset(dpS,63,sizeof dpS);
	for(int i=k+1;i;--i)	dpS[Sp[i]]=i;
	for(int S=(1<<n)-1;S;--S)	for(int i=1;i<=n;++i)	if((S>>(i-1))&1)	dpS[S^(1<<(i-1))]=min(dpS[S^(1<<(i-1))],dpS[S]);
	for(int i=1;i<=k+1;++i)	dpT[Tp[i]]=i;
	for(int T=(1<<n)-1;T;--T)	for(int i=1;i<=n;++i)	if((T>>(i-1))&1)	dpT[T^(1<<(i-1))]=max(dpT[T^(1<<(i-1))],dpT[T]);
	int ans=0,l=0,r=0;
	for(int S=0,pc=0;S<(1<<n);++S,pc=popcount(S))	if(dpT[S]-dpS[S]>=m && n+2*pc-Sc-Tc>ans)	ans=n+2*pc-Sc-Tc,l=dpS[S],r=dpT[S];
	if(ans==0)	printf("0\n1 %d\n",k);
	else	printf("%d\n%d %d",ans,l,r-1);
	return 0;
}
```

---

## 作者：11400F (赞：1)

[不知道怎么样的阅读体验](https://www.11490dx.net/2025/02/05/R702-practice-log/#t1-%E4%BA%A4%E6%8D%A2)

---

这道题的 $k$ 非常小，似乎可以设状态来状态压缩。

首先看到连续一段区间操作，现在想知道对于每个 $i$，执行第 $i\sim j$ 个操作之后，$s$ 会变成什么。设其为 $s^{\prime}_{i\sim j}$。那么可以先求出后缀，即所有的 $s^{\prime}_{i \sim n}$。暴力做不行，肯定要优化。

假如说我们已经求出来了依次执行操作 $i+1 \sim n$ 之后 $s$ 变成了什么。我们用一个排列 $p$ 来表示。这个排列表示的是操作之后，原本的 $s$ 第 $i$ 项变为了新的第 $p_i$ 项。然后求出 $s$ 在操作 $i$ 之后变成了什么是容易的，令这个排列为 $c$。我们考虑如何把这两个排列“加起来”。

实际上因为操作是连续的，要从操作 $i\sim i$ 得到的 $c$ 变为操作 $i\sim n$ 得到的 $c$，只需要 $c_i \gets p_{c_i}$ 即可。最后把其从排列解码即可。这样就求得了所有的 $s^{\prime }_{i\sim n}$。

现在后缀已经求出来了。考虑如何从后缀变为区间。因为不可能从 $s^{\prime}_{i\sim n}$ 直接推出来 $s^{\prime}_{i \sim j}$。那么就转化一下思路。可以把 $t$ 变为 $t^{\prime}_{j+1 \sim n}$。然后这样，就相当于是首先 $s$ 变为了 $s^{\prime}_{i \sim j}$，这段改变了 $s$ 和 $t$ 的相对位置关系。而后面改变 $j+1\sim n$ 并没有改变 $s$ 和 $t$ 的相对位置关系。所以这两个相当于是等价的。

这样，计算所有区间变化后的结果，即 $s^{\prime}_{i \sim n}$ 和 $t^{\prime}_{i \sim n}$ 的时间复杂度从 $O(n^2k)$ 变为了 $O(nk)$。

---

然后开始计算答案。因为最后的答案一定是某个 $s^{\prime}_{i \sim n}$ 和 $t^{\prime}_{j\sim n}$ 的最长匹配，我们可以枚举串 $s^{\prime}_{i \sim n}$ 和 $t^{\prime}_{j\sim n}$ 的公共 $1$ 串 $u$（但是 $u$ **不一定是最长**的）。具体来说，若 $u$ 的某位值为 $1$，$s^{\prime},t^{\prime}$ 在该位的值一定为 $1$。然而若 $s^{\prime}$ 的某位值为 $1$，$u^{\prime}$ 在该位的值不一定为 $1$。$t^{\prime}$ 串也是这样。相当于是，将 $s^{\prime},t^{\prime},u$ 看作 $3$ 个集合，那么 $u \subset s^{\prime} \land u \subset t^{\prime}$。

而因为我们原来是知道 $s$ 的 $1$ 的个数 $sc$，和 $t$ 的 $1$ 的个数 $tc$，和现在枚举的 $u$ 的 $1$ 的个数 $uc$，那么，现在的答案就是 $k - (sc-uc) - (tc-uc)$。因为 $uc$ 是两个串的公共部分显然吧，那么 $s$ 还剩下 $sc-uc$ 个 $1$ 失配，$t$ 还剩下 $tc-uc$ 个 $1$ 失配，删掉失配的位之后，剩下的位数就是能匹配的位数 $k-(sc-uc)-(tc-uc)$ 了。

这种方法虽然不保证做得到不重，但是一定能做得到不漏。

然而，直接对于 $i$ 和 $j$ 暴力枚举 $s^{\prime}$ 和 $t^{\prime}$ 的公共串的时间复杂度是 $O(n^2)$ 的，不行，于是我们可以考虑记录两个数组：

- $f_{stat}$ 表示可以包含 $stat$ 的 $s^{\prime}_{i\sim n}$ 的最小 $i$。
- $g_{stat}$ 表示可以包含 $stat$ 的 $t^{\prime}_{i+1\sim n}$ 的最大 $i$。

这两个数组相当于就是枚举了包含状态 $stat$ 所可以达到的最小左端点和最大右端点。刚好满足了题目的要求。

那么就首先设置 $f_{s^{\prime}_{i\sim n}} = i, g_{s^{\prime}_{i\sim n}} = i-1$。然后转移的 $stat$ 从大到小转移：枚举当前 $stat$ 的每一个 $1$ 被删除了的情况，为 $newst$ ，然后 $f_{newst} \gets \min(f_{newst}, f_{stat}), g_{newst} \gets \max(g_{newst}, g_{stat})$。

最后枚举每一个 $stat$，然后看 $g_{stat} - f_{stat} + 1$ 是否 $\ge m$。若是，则按照要求更新答案。否则不管。于是这道题就做完了。

Code here:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+6;
int a[N], b[N];
const int K = 21;
int pl[K]; //原本的 1,2,...,k 经过从前往后的一些变化操作之后，新的排列是什么呢？
int lstpl[K];
int n, m, k;
char s[K], t[K];
int scode[K], tcode[K];
int f[1<<20], g[1<<20];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>k;
    cin>>(s+1); cin>>(t+1);
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    int sstat = 0, tstat = 0;
    int s1cnt=0, t1cnt=0;
    for(int i=1;i<=k;i++){
        scode[i] = s[i] - '0', tcode[i] = t[i] - '0';
        s1cnt += scode[i], t1cnt += tcode[i];
        sstat += (scode[i]<<(i-1)), tstat += (tcode[i]<<(i-1));
    }
    for(int stat=0;stat<(1<<k);stat++){
        f[stat] = n+1;
        // g[stat] = 0;
    }
    g[tstat] = n;
    for(int j=1;j<=k;j++){
        lstpl[j] = j;
    }
    // cout<<tstat<<'\n';
    for(int i=n;i>=1;i--){
        for(int j=1;j<=k;j++){
            pl[j] = j;
        }
        swap(pl[a[i]], pl[b[i]]);
        sstat = 0, tstat = 0;
        for(int j=1;j<=k;j++){
            pl[j] = lstpl[pl[j]];
            sstat += (scode[j]<<(pl[j]-1)), tstat += (tcode[j]<<(pl[j]-1));
        }
        for(int j=1;j<=k;j++){
            lstpl[j] = pl[j];
        }
        f[sstat] = min(f[sstat], i);
        g[tstat] = max(g[tstat], i-1);
    }

    for(int stat=(1<<k)-1;stat>=0;stat--){
        for(int j=1;j<=k;j++){
            if((stat>>(j-1))&1){
                f[stat^(1<<(j-1))] = min(f[stat^(1<<(j-1))], f[stat]);
                g[stat^(1<<(j-1))] = max(g[stat^(1<<(j-1))], g[stat]);
            }
        }
    }
    int segl=1,segr=1,ans=0;
    for(int stat=0;stat<(1<<k)-1;stat++){
        if(g[stat]-f[stat]+1>=m){
            int len = g[stat]-f[stat]+1;
            int ppcnt = __builtin_popcount(stat);
            // cout<<ppcnt<<'\n';
            if(ppcnt > ans){
                ans = ppcnt;
                segl = f[stat], segr = g[stat];
            }else if(ppcnt == ans && (len>segr-segl+1 || (len == segr-segl+1 && f[stat] < segl))){
                segl = f[stat], segr = g[stat];
            }
        }
    }
    s1cnt -= ans, t1cnt -= ans;
    cout<<(k-s1cnt-t1cnt) <<'\n'<<segl<<' '<<segr<<'\n';
    return 0;
}
```

---

## 作者：Composite_Function (赞：0)

做了 1h，还是太菜了。

怎么会有人把这么难的题放在模拟赛 T1 啊。

---

首先注意到交换很奇怪，因为最终要算的答案与一段操作有关。注意到 $k \le 20$，这启发我们维护交换串是原串的排列，求出这个排列是什么。求出排列只需要 $O(nk)$。

假设做前 $i$ 个操作所得到的排列是 $p_i$。那么 做第 $l,...,r$ 个操作所得到的是 $p_{l-1}^{-1} \circ p_r$。

那么区间 $l,...,r$ 所对应的答案就是 $\sum_{i=1}^n[s_i=t_{p_{l-1}^{-1}(p_r(i))}]$，其实就是 $\sum_{i=1}^n[s_{p_{l-1}^{-1}(i)}=t_{p_{r}^{-1}(i)}]$。

然后开始思考这个怎么做。一个比较直接的想法是扔到一张图里去，把只有一位不同的两个 $k$ 维 $01$ 数组 $u$ 和 $v$ 连一条边权为 $1$ 的边。这样把所有源点和汇点扔进去跑 bfs 即可。复杂度 $O(2^kk)$。

但是这个不对！注意到要有 $r-l+1 \ge m$ 的限制。一种错误的想法是记录最短路的同时记录了达到最短路的最小 $l$ 或最大 $r$。这很明显是错的，因为有时候非最短路能满足限制但最短路不能。

于是我们把 $l$ 从依次跑。这样能保证正确性。但是复杂度飙升至 $O(n2^kk)$ 肯定不行。但是我们可以给出一个优化，就是把 $l$ 从小往大依次插入，只有当前最短路严格小于原来的最短路才更新。这样做是因为完全一样的状态下明显 $l$ 越小越优。根据这张图的性质，最短路最大值才 $O(k)$，所以复杂度不会超过 $O(2^kk^2)$。

但是要注意到这个远远跑不满。因为刚插入几个后最短路会快速下降。所以远远跑不满！具体复杂度不会算（），但是最终只跑了 796ms。

---

代码还是非常简短的。以及认为自己的缺省源太长了就去掉了。

```cpp
const int N = 1e6 + 10, K = 21;
int n, m, k, a[N], b[N], p[N][K], ip[N][K];
int dis[1 << K], dst[1 << K];
int ans = INT_MAX, l = INT_MAX, r;
char s[K], t[K];

inline int trs(char *str, int *ip) {
	int res = 0;
	for (int i = 1; i <= k; ++i)
		if (str[ip[i]] == '1') res |= 1 << (i - 1);
	return res;
}

signed main() {
	rin >> n >> m >> k;
	cin >> (s + 1) >> (t + 1);
	for (int i = 1; i <= k; ++i) p[0][i] = ip[0][i] = i;
	for (int i = 1; i <= n; ++i) {
		rin >> a[i] >> b[i];
		for (int j = 1; j <= k; ++j) p[i][j] = p[i - 1][j];
		swap(p[i][a[i]], p[i][b[i]]);
		for (int j = 1; j <= k; ++j) ip[i][p[i][j]] = j;
	}
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; ++i) {
		int T = trs(t, ip[i]);
		dst[T] = max(dst[T], i);
	}
	for (int i = 1; i <= n; ++i) {
		int S = trs(s, ip[i - 1]);
		if (dis[S] == 0) continue;
		queue<int> q;
		dis[S] = 0, q.push(S);
		while (!q.empty()) {
			int u = q.front();
//			cout << u << " " << dis[u] << " " << ans << endl;
			q.pop();
			if (dis[u] > ans) break;
			if (dst[u] - i + 1 >= m) {
				if (ans == dis[u]) {
					if (r - l + 1 < dst[u] - i + 1) {
						r = dst[u];
						l = i;
					}
				} else if (ans > dis[u]) {
					ans = dis[u];
					r = dst[u];
					l = i;
				}
			}
			if (dis[u] == ans) continue;
			for (int i = 0; i < k; ++i)
				if (dis[u ^ (1 << i)] > dis[u] + 1) {
					dis[u ^ (1 << i)] = dis[u] + 1;
					q.push(u ^ (1 << i));
				}
		}
	}
	ans = k - ans;
	cout << ans << endl << l << " " << r << endl;
	return 0;
}
```

---

