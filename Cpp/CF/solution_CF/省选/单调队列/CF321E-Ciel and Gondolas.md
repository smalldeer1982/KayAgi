# Ciel and Gondolas

## 题目描述

Fox Ciel is in the Amusement Park. And now she is in a queue in front of the Ferris wheel. There are $ n $ people (or foxes more precisely) in the queue: we use first people to refer one at the head of the queue, and $ n $ -th people to refer the last one in the queue.

There will be $ k $ gondolas, and the way we allocate gondolas looks like this:

- When the first gondolas come, the $ q_{1} $ people in head of the queue go into the gondolas.
- Then when the second gondolas come, the $ q_{2} $ people in head of the remain queue go into the gondolas. ...
- The remain $ q_{k} $ people go into the last ( $ k $ -th) gondolas.

Note that $ q_{1} $ , $ q_{2} $ , ..., $ q_{k} $ must be positive. You can get from the statement that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321E/5aa86331c628d3d47e29fa23648bea351737ffff.png) and $ q_{i}>0 $ .

You know, people don't want to stay with strangers in the gondolas, so your task is to find an optimal allocation way (that is find an optimal sequence $ q $ ) to make people happy. For every pair of people $ i $ and $ j $ , there exists a value $ u_{ij} $ denotes a level of unfamiliar. You can assume $ u_{ij}=u_{ji} $ for all $ i,j $ $ (1<=i,j<=n) $ and $ u_{ii}=0 $ for all $ i $ $ (1<=i<=n) $ . Then an unfamiliar value of a gondolas is the sum of the levels of unfamiliar between any pair of people that is into the gondolas.

A total unfamiliar value is the sum of unfamiliar values for all gondolas. Help Fox Ciel to find the minimal possible total unfamiliar value for some optimal allocation.

## 说明/提示

In the first example, we can allocate people like this: {1, 2} goes into a gondolas, {3, 4, 5} goes into another gondolas.

In the second example, an optimal solution is : {1, 2, 3} | {4, 5, 6} | {7, 8}.

## 样例 #1

### 输入

```
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0
```

### 输出

```
0
```

## 样例 #2

### 输入

```
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0
```

### 输出

```
7
```

## 样例 #3

### 输入

```
3 2
0 2 0
2 0 3
0 3 0
```

### 输出

```
2
```

# 题解

## 作者：皎月半洒花 (赞：40)

诶，这题虽然是决策单调性，但是没人证啊(虽然比较显然)。

那我就来简单证一下叭：

考虑四边形不等式，如果是最小值问题，那大概长这样：

$$a\leq b<c\leq d$$

$$w(a,c)+w(b,d)\le w(a,d)+w(b,c)$$

那么如果满足这个，就说明其满足最小值时的决策单调性。证明起来很简单，因为 $a\to d,b\to c$ 的转移的值要更大些，所以 $a\to c,b\to d$ 的转移会更优，据此可得 $f$ 有决策单调性。

考虑拿四边形不等式来证明。对于 $a\leq b<c\leq d$ 而言，记 $s(a,c)$ 表示矩阵中左上角为 $(a,a)$ 右下角为 $(c,c)$ 的这么一个矩阵中元素的和，那么 
$$w(a,c)+w(b,d)=\frac{s(a,c)+s(b,d)}{2}$$

$$w(a,d)+w(b,c)=\frac{s(a,d)+s(b,c)}{2}$$
注意到
$$s(a,d) = s(a,c)+s(b,d)-s(b,c)+s(a,b)+s(c,d)$$
那么就显然
$$w(a,c)+w(b,d)\le w(a,d)+w(b,c)$$
十分满足决策单调性（其实画出图来更显然，就是多了两块矩阵）。

这个东西可以用分治来做。因为每一层决策与本层无关，即 $k-1\to k$ 。于是就可以 `solve(l,r,ql,qr)` 表示 $l\sim r$ 是从区间 $(ql\sim qr)$ 转移过来的。那么每次取 $mid=\frac{l+r}{2}$，然后找出 $f_{mid}$ 对应的最优决策所在位置，这样就可以分治了。复杂度 $O(nk\log n)$ 。

---

## 作者：chihik (赞：30)

各位大佬都用的 $wqs$ 二分，蒟蒻介绍一种简单方法。

$dp$ 式很好列:

$$
dp[i][j]=min( dp[i-1][k-1] + calc( k , j ) )
$$

$calc(k,j)$表示将 $k$ 到 $j$ 的贞鱼在同一车的怨气值 ， 决策具有单调性。

不如将当前的决策点区间记为 $ [optl,optr] $  , 处理 $dp$ 的区间为 $ [L,R] $

我们可以暴力计算 $dp[s][mid]$ 的值 $(mid=\frac{L+R}{2})$ ， 并记录当前的决策点$opt$。

然后我们可以递归计算 $dp[s][l...(mid-1)]$ 与 $dp[s][(mid+1)...r]$

因为决策具有单调性 ， 所以计算 $dp[s][l...(mid-1)]$时只需用$[optl,opt]$ , 计算 $dp[s][(mid+1)...r]$时只需用$[opt,optr]$。

这种方法仅适用于有**决策单调性**的题，时间复杂度为$\Theta(k*n*log_2n)$

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

void Read( int &x ) {
	x = 0; int f = 1;
	char s = getchar( );
	for( ; s < '0' || s > '9' ; s = getchar( ) ) f = s == '-' ? -f : f;
	for( ; s >= '0' && s <= '9' ; s = getchar( ) ) x = x * 10 + s - '0';
	x *= f;
}
void Write( int x ) {
	if( x < 0 )
		putchar('-') , x = -x;
	if( x >= 10 ) Write( x / 10 );
	putchar( x % 10 + '0' );
}

const int MAXK = 800 , MAXN = 4000;
int n , k , x , sum[ MAXN + 5 ][ MAXN + 5 ];
int dp[ MAXK + 5 ][ MAXN + 5 ];

int Calc( int u , int v ) {
	return sum[ v ][ v ] - sum[ v ][ u - 1 ] - sum[ u - 1 ][ v ] + sum[ u - 1 ][ u - 1 ];
}
void dfs( int s , int L , int R , int optl , int optr ) {
	if( L > R ) return;
	
	int Mid = ( L + R ) / 2 , opt;
	dp[ s ][ Mid ] = INF;
	for( int i = optl ; i <= min( optr , Mid ) ; i ++ ) {
		if( dp[ s ][ Mid ] > dp[ s - 1 ][ i - 1 ] + Calc( i , Mid ) ) {
			dp[ s ][ Mid ] = dp[ s - 1 ][ i - 1 ] + Calc( i , Mid );
			opt = i;
		}
	}
	dfs( s , L , Mid - 1 , optl , opt );
	dfs( s , Mid + 1 , R , opt , optr );
}

int main( ) {
	Read( n ) , Read( k );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ )
			Read( x ) , sum[ i ][ j ] = sum[ i - 1 ][ j ] + sum[ i ][ j - 1 ] - sum[ i - 1 ][ j - 1 ] + x;
	for( int i = 1 ; i <= n ; i ++ )
		dp[ 0 ][ i ] = INF;
	for( int i = 1 ; i <= k ; i ++ )
		dfs( i , 1 , n , 1 , n );
	Write( dp[ k ][ n ] / 2 );
	return 0;
}
```


---

## 作者：皎月半洒花 (赞：30)

这里再讲一种比除了 $wqs$ 二分之外都要优的 $O(n^2)$ 做法（神奇的与 $k$ 无关）。

首先决策单调性不再证明了，直接考虑怎么实现。

考虑记录一下每个点的决策范围。发现设状态 $(n,k)$ 最优决策位置记作 $opt(n,k)$ 的话，一定有
$$
opt(n,k-1)\leq opt(n,k)\leq opt(n+1,k)
$$
那么可以这么写：

```cpp
for j : 1 to k
  for i : n to 1
    for p : opt(i, j - 1) to opt(i + 1, j)
      if [f(p, j - 1) < f(i, j)] opt(i, j) = p, f(i, j) := f(p, j - 1) ; 
```

这样做显然是对的。于是来考虑这么做的时间复杂度。

发现对于这个决策矩阵的每一条穿过 $opt(i,j)$  和 $opt(i+1,j+1)$ 的斜线，每条斜线的代价是 $O(n)$ 的，原因是考虑斜线 $opt(i,j),opt(i+1,j+1)$ 这条斜线的决策来自于 $opt(i,j-1),opt(i+1,j)$ 这条斜线。那么也就是说，每个斜线的转移都是 $O(n)$ 的，共有 $O(n+k)$ 条斜线，所以复杂度 $O(n^2)$ 。


代码就不给了，这个伪代码写的还是很规整的吧？

---

## 作者：foreverlasting (赞：13)

[题面](https://www.lydsy.com/JudgeOnline/problem.php?id=5311)

DP凸优化。

这居然都能变成一种套路题，那可真是让我大吃一惊呢。首先DP式应该可以迅速得出。记$dp[i][j]$表示前$i$个分成$j$段的最小代价，$sum[i][j]$表示前$i$个贞鱼与前$j$个贞鱼的总代价。那么转移方程也就很好写了：$dp[i][j]=min(dp[p][j-1]+(sum[i][i]+sum[p][p]-2*sum[i][p])/2)$。

这显然是$O(n^2*k)$的复杂度，考虑如何优化。

首先发现好像不能斜率优化哎，但是有决策单调性可以搞。所以可以维护一个单调队列，然后让复杂度变成$O(n*k*logn)$。但这个复杂度还是太大，于是我们考虑一种叫做$wqs$二分的神奇做法，去查找$p$的位置（断开的位置），然后使复杂度变成$O(n*logn*logk)$。

事实上呢，这种决策单调性+$wqs$二分的合体是一种基本套路了，我们把它称作凸优化。为什么要叫凸优化呢？这里我找到这样一段话：

 _凸优化解决的是一类选择恰好 k 个某种物品的最优化问题。一般来说这样的题目在不考虑物品数量限制的条件下会有一个图像，表示选择的物品数量与问题最优解之间的关系。_ 

 _问题能够用凸优化解决还需要满足图像是凸的，直观地理解就是选的物品越多的情况下多选一个物品，最优解的增长速度会变慢。_ 

 _解决凸优化类型的题目可以采用二分的方法，即二分凸壳上最优值所在点的斜率，然后忽略恰好 k 个的限制做一次原问题。_ 

 _这样每次选择一个物品的时候要多付出斜率大小的代价，就能够根据最优情况下选择的物品数量来判断二分的斜率与实际最优值的斜率的大小关系。_ 

 _理论上这个斜率一定是整数，由于题目性质可能会出现二分不出这个数的情况，这时就需要一些实现上的技巧保证能够找到这个最优解。_ 
 
说明白一点，就是因为$dp$数组是一个凸函数，我们就可以把限制取$k$段的条件变成斜率，直接去这个凸函数的极值点，这样答案就可以直接用函数值来表示掉。
 
于是这种类型的题目我们都可以用这么一种叫做凸优化的做法二分查找到答案，然后过了这种类型的题。

code:
```
//2018.9.7 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
#define RG register
namespace io{
    const int MAXBUF=1<<15;
    const int OUTPUT=1<<24;
    char b[MAXBUF],*S=b,*T=b;
#define getc() (S==T&&(T=(S=b)+fread(b,1,MAXBUF,stdin),S==T)?0:*S++)
#define O(x) __attribute__((optimize("-O"#x)))
#define inline __inline__ __attribute__((always_inline))
    template<class Type> inline Type read(){
        RG Type aa=0;
        RG bool bb=0;
        RG char ch,*S=io::S,*T=io::T;
        for(ch=getc();(ch<'0'||ch>'9')&&ch!='-';ch=getc());
        for(ch=='-'?bb=1:aa=ch-'0',ch=getc();'0'<=ch&&ch<='9';ch=getc())aa=aa*10+ch-'0';
        io::S=S,io::T=T;
        return bb?-aa:aa;
    }
    inline int gets(RG char *s){
        RG char *iter=s,*S=io::S,*T=io::T;
        while(*iter=getc(),*iter==' '||*iter=='\n'||*iter=='\r');
        while(*++iter=getc(),*iter&&*iter!=' '&&*iter!='\n'&&*iter!='\r');
        *iter=0;
        io::S=S,io::T=T;
        return iter-s;
    }
    char buff[OUTPUT],*iter=buff;
    template<class T> inline void P(RG T x, RG char ch = '\n'){
        static int ST[110];
        res O=0;
        RG char *iter=io::iter;
        if(!x)*iter++='0';
        else{
            (x<0)?x=-x,*iter++='-':1;
            for(;x;x/=10)ST[++O]=x%10;
            for(;O;*iter++='0'+ST[O--]);
        }
        *iter++=ch,io::iter=iter;
    }
    inline void output(){fwrite(buff, 1, iter - buff, stdout),iter=buff;}
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
const int N=4e3+10;
namespace MAIN{
    int n,k;
    int sum[N][N];
    int dp[N],siz[N];
    struct Queue{
        int x,l,r;
        Queue() {}
        Queue(res x,res l,res r):x(x),l(l),r(r) {}
    }Q[N];
    int he,ta;
    inline void init(){
        dp[0]=siz[0]=ta=0;
        he=1;
    }
    inline int func(res i,res j,res lim){
        return (sum[i][i]+sum[j][j]-sum[i][j]*2)/2+lim+dp[j];
    }
    inline void calc(res lim){
        init();
        Q[++ta]=Queue(0,1,n);
        for(res i=1;i<=n;i++) {
            while(he<ta&&Q[he].r<i)he++;
            dp[i]=func(i,Q[he].x,lim),siz[i]=siz[Q[he].x]+1;
            if(func(n,i,lim)>=func(n,Q[ta].x,lim))continue;
            while(he<ta&&func(Q[ta].l,Q[ta].x,lim)>func(Q[ta].l,i,lim))ta--;
            res l=Q[ta].l,r=Q[ta].r+1;
            while(l<r){
                res mid=(l+r)>>1;
                if(func(mid,i,lim)<func(mid,Q[ta].x,lim))r=mid;
                else l=mid+1;
            }
            Q[ta].r=r-1;
            Q[++ta]=Queue(i,r,n);
        }
    }
    inline void MAIN(){
        res (*F)()=io::read<int>;
        n=F(),k=F();
        for(res i=1;i<=n;i++)
            for(res j=1;j<=n;j++)
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+F();
        res l=0,r=sum[n][n];
        while(l<r){
            res mid=(l+r)>>1;
            calc(mid);
            if(siz[n]>k)l=mid+1;
            else r=mid;
        }
        calc(r);
        io::P(dp[n]-r*k);
    }
}
int main(){
    MAIN::MAIN();
    io::output();
    return 0;
}
```

---

## 作者：Zzzzzzzm (赞：6)

单调队列优化 $dp$

## 题目思路
~~很容易就可以看出来这道题是 $dp$~~，如果设 $dp[i][j]$ 表示 $i$ 个人使用 $j$ 条船的最优解，$sum[i][j]$ 表示二维前缀和，很容易就可以得出式子：
$$
dp[i][j]=min(dp[k-1][j-1]+sum[k][i]/2),k\in[j-1,i-1]
$$
$k$ 的取值范围是考虑优化不能让前面的船空了，也不能让新来的船没人。

决策是具有单调性的，因此想到用单调队列优化dp。

如果 $dp[i][k]>dp[j][k]$ 且 $i<j$ 则决策 $j$ 比 $i$ 优，可以确定决策 $i$不会被用到了就直接出队，外层枚举船，内层枚举人，可以容易证明决策是无后效性的。对于每个人二分查找最优解，时间复杂度 $O(nk\log n)$，可以通过。

## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, dp[4005][4005], k, a[4005][4005], sum[4005][4005], head, tail;		//dp[i][j]表示前i个人用j条船的最优解 
struct node{
	int num, l, r;
}t;
deque<node> q;

template<typename T>
inline void read(T&x){
	x = 0; char q; bool f = 1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1) + (x<<3) + (q^48);
		q = getchar();
	}
	x = f?x:-x;
}

template<typename T>
inline void write(T x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)	write(x/10);
	putchar(x%10^48);
}

int val(int k, int u, int v){
	return dp[u][k-1]+(sum[u][u]+sum[v][v]-sum[u][v]-sum[v][u])/2;
}

int main(){
	read(n), read(k);
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= n; ++j)
			read(a[i][j]);
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= n; ++j)
			sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];		//预处理前缀和 
	memset(dp, 0x3f, sizeof(dp));
	for(register int i = 1; i <= n; ++i)	dp[i][1] = sum[i][i]/2;			//dp[i][1]表示前i个全在1条船上的情况 
	for(register int j = 2; j <= k; ++j){									//枚举每一条船 
		q.clear();															//单调队列初始化 
		t.num = 0, t.l = 1, t.r = n;										//l,r记录人在船的区间,num记录最优人数 
		q.push_back(t);
		for(register int i = 1; i <= n; ++i){								//枚举人数 
			while(q.size() > 1 && q.front().r < i)	q.pop_front();			//当还存在不止一个解且最优人数区间小于需求人数i时直接出队 
			q.front().l = i;												//最小人数为i 
			dp[i][j] = val(j, q.front().num, i);							//k条船i个人最优解等于k-1条船预处理最优人数+剩余人数在一条船上的值 
			while(q.size() > 1 && val(j, i, q.back().l) <= val(j, q.back().num, q.back().l))	q.pop_back();
			int l = q.back().l, r = q.back().r;
			while(l < r){													//二分查找最优长度 
				int mid = (l+r) >> 1;
				if(val(j, q.back().num, mid) >= val(j, i, mid))	r = mid;	//队尾的值长度与二分长度判断 
				else l = mid+1;
			}
			if(val(j, q.back().num, q.back().r) <= val(j, i, q.back().r))	l++;
			if(l != q.back().l)	q.back().r = l-1;							//若边界不在队中，则修改队尾 
			else	q.pop_back();											//否则将队尾弹出 
			if(l <= n){														//将第p条船的信息加入队中 
				t.num = i, t.l = l, t.r = n;
				q.push_back(t);
			}
		}
	}
	write(dp[n][k]);
	return 0;
}
```


---

## 作者：elijahqi (赞：1)

 http://www.elijahqi.win/archives/3794
 https://blog.csdn.net/elijahqi/article/details/80759000

设dp[i][j]表示前i个分成j段的代价
于是有朴素方程
然后利用决策单调性可以优化为n*k*log
即我们考虑其中两个决策点j1,j2对于后面的影响 因为这个s是单增的 所以如果dp[j1]>dp[j2]且j1< j2那么 j1将会永远不优  但是因为我们每次增加的这个东西并不是单调的
即我们考虑如果我们尝试去斜率优化可以发现 小于号右边的东西并不单调和所在决策点有关所以无法斜率优化 但是利用我们刚刚所说的决策单调性我们可以做到一个log 即每次入队的i时候比较一下队尾的元素相比起来谁不优的时间早如果后面的比前面的早说明队尾一定弹出
```
#include<bits/stdc++.h>
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0,f=1;char ch=gc();
	while(!isdigit(ch)) {if (ch=='-') f=-1;ch=gc();}
	while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
	return x*f;
}
const int N=4040;
const int inf=0x3f3f3f3f;
int n,k,sum,s[N][N],K,dp[N][1000],q[N];
inline int gao(int x,int y){
	return s[y][y]-s[y][x];
}
inline int calc(int x,int y){
	int l=y+1,r=n,res=n+1;
	while(l<=r){
		int mid=l+r>>1;
		if (dp[x][k-1]+gao(x,mid)>=dp[y][k-1]+gao(y,mid)) res=mid,r=mid-1;else l=mid+1;
	}return res;
}
int main(){
	freopen("bzoj5311.in","r",stdin);
	n=read();K=read();sum=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j) if(j<=i) s[i][j]=read(),sum+=s[i][j];else read();
	for (int i=1;i<=n;++i) for (int j=1;j<=i;++j) s[i][j]+=s[i-1][j];
	for (int i=1;i<=n;++i) for (int j=1;j<=i;++j) s[i][j]+=s[i][j-1];
	for (int i=0;i<=n;++i) dp[i][0]=inf;dp[0][0]=0;
	for (k=1;k<=K;++k){
		int op=1,cl=1;q[op]=0;
		for (int i=1,j;i<=n;++i){
			while(op<cl&&calc(q[op],q[op+1])<=i)++op;
			j=q[op];dp[i][k]=dp[j][k-1]+gao(j,i);
			while(op<cl&&calc(q[cl-1],q[cl])>=calc(q[cl],i)) --cl;
			q[++cl]=i;
		}
		//for (int i=1;i<=n;++i) printf("%d ",dp[i][k]);puts("");
	}printf("%d\n",dp[n][K]);
	return 0;
}
```
对于k的限制因为bzoj上仍然过不去我们考虑wqs二分

在wqs二分的时候我限制了如果相同取越小越好  因为会存在例如3的时候比答案大4的时候比k小 因为枚举的整数所以才导致没有切上其实是两个点都相切造成的影响那么我们算答案的时候就必须知道答案点被属于了哪一个切点

注意细节！！！ 可以看代码..
```
#include<bits/stdc++.h>
using namespace std;
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0,f=1;char ch=gc();
	while(!isdigit(ch)) {if (ch=='-') f=-1;ch=gc();}
	while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
	return x*f;
}
const int N=4040;
const int inf=0x3f3f3f3f;
int n,k,sum,s[N][N],K,dp[N],q[N],cnt[N];
inline int gao(int x,int y){
	return s[y][y]-s[y][x];
}
inline int calc(int x,int y){
	int l=y+1,r=n,res=n+1;
	while(l<=r){
		int mid=l+r>>1;
		int t1=dp[x]+gao(x,mid),t2=dp[y]+gao(y,mid);
		if (t1>t2||(t1==t2&&cnt[x]>cnt[y])) res=mid,r=mid-1;else l=mid+1;
	}return res;
}
inline bool check(int mid){
	int op=1,cl=1;q[op]=0;
	for (int i=1,j;i<=n;++i){
		while(op<cl&&calc(q[op],q[op+1])<=i) ++op;
		j=q[op];dp[i]=dp[j]+gao(j,i)+mid;cnt[i]=cnt[j]+1;
		while(op<cl&&calc(q[cl-1],q[cl])>calc(q[cl],i)) --cl;
		q[++cl]=i;
	}return cnt[n]<=K;
}
int main(){
	freopen("bzoj5311.in","r",stdin);
	n=read();K=read();sum=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j) if(j<=i) s[i][j]=read(),sum+=s[i][j];else read();
	for (int i=1;i<=n;++i) for (int j=1;j<=i;++j) s[i][j]+=s[i-1][j];
	for (int i=1;i<=n;++i) for (int j=1;j<=i;++j) s[i][j]+=s[i][j-1];
	int l=0,r=sum,ans=0,nm,v;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=dp[n]-mid*K,r=mid-1;else l=mid+1;
	}
	 printf("%d\n",ans);
	return 0;
}
```

---

