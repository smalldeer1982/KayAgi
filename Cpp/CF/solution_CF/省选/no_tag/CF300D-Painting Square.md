# Painting Square

## 题目描述

Vasily the bear has got a large square white table of $ n $ rows and $ n $ columns. The table has got a black border around this table.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/ddbad6e90fff9934de05472a83c397e11ee2a641.png)The example of the initial table at $ n $ = 5.Vasily the bear wants to paint his square table in exactly $ k $ moves. Each move is sequence of actions:

1. The bear chooses some square inside his table. At that the square must have a black border painted around it. Also, the square shouldn't contain a black cell. The number of cells in the square shouldn't be less than $ 2 $ .
2. The bear chooses some row and some column inside the chosen square. Then he paints each cell of this row and this column inside the chosen square. After that the rectangles, formed by the square's border and the newly painted cells, must be squares of a non-zero area.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/2f670f9945e1926b1278ff5823ebb3aa45519652.png)  An example of correct painting at $ n $ = 7 и $ k $ = 2.The bear already knows numbers $ n $ and $ k $ . Help him — find the number of ways to paint the square in exactly $ k $ moves. Two ways to paint are called distinct if the resulting tables will differ in at least one cell. As the answer can be rather large, print the remainder after dividing it by $ 7340033 $ .

## 说明/提示

All possible painting ways for the test $ n=7 $ and $ k=2 $ are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/1f5221421bd715ed9c40286f4e2330edd5cee6fd.png)

## 样例 #1

### 输入

```
8
1 0
1 1
3 0
3 1
2 0
2 1
3 2
7 2
```

### 输出

```
1
0
1
1
1
0
0
4
```

# 题解

## 作者：xtx1092515503 (赞：2)

[portal to luogu](https://www.luogu.com.cn/problem/CF300D)

[portal to CF](codeforces.com/problemset/problem/300/D)

~~看见没有题解就跑过来水题解了~~

CF上有FFT的tag，但是这题不需要FFT（虽然当$k$再大一点就需要了）。

首先，对于任何一个正方形，它都只能进行唯一的操作：切一刀，分成四个一模一样的正方形。我们定义一个正方形的深度为：对于一个正方形，一直照着切完后左上角的正方形切，直到切不了为止。例如，一个$5\times 5$正方形的深度为$1$（切一刀切出四个$2\times 2$的），一个$7\times 7$正方形的深度为$2$（切一刀切出$3\times 3$，再切切出$1\times 1$），一个$100\times 100$正方形的深度为$0$（一刀都切不了）。

我们考虑DP。设$f_{i,j}$表示：在一个深度为$i$的正方形中，切$j$刀，所能得到的不同局面数。

则我们有$f_{x,y}=\sum\limits_{i+j+k+l=y-1}f_{x-1,i}\times f_{x-1,j}\times f_{x-1,k}\times f_{x-1,l}$。它的意义是分别在切出来的四个小正方形中切$i,j,k,l$刀的种数。

我们可以设$g_{x,y}=\sum\limits_{i+j=y}f_{x,i}\times f_{x,j}$，则$f_{x,y}=\sum\limits_{i+j=y-1}g_{x-1,i}\times g_{x-1,j}$。

一个正方形的深度是$\log$级别的。暴力转移是$k^2$的。则这个DP的复杂度为$k^2\log n$，刚好可以通过本题。

我们不妨考虑一下如果$k$再大一点，比如$5\times 10^3$或$1\times 10^4$。这时，这个暴力DP就可能卡不过去。

我们观察一下转移式：$g_{x,y}=\sum\limits_{i+j=y}f_{x,i}\times f_{x,j}$，卷积的气息！也就是说，$g_x=(f_x)^2$。

$f_{x,y}=\sum\limits_{i+j=y-1}g_{x-1,i}\times g_{x-1,j}$，也就是说，$f_x=(g_{x-1})^2$。采取NTT，复杂度优化为$O(k\log n\log k)$（$7340033$是NTT质数，原根为$3$）。

虽然可以用NTT，但这并不意味着暴力DP不可以（~~其实是因为我太懒了懒得写NTT了~~）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n,K,T,f[100][10000],g[100][10000];
const int mod=7340033;
void init(){
	for(int i=0;i<=30;i++)f[i][0]=g[i][0]=1;//for squares of any size, if we do not have any cuts, there will only be one situation
	for(int i=1;i<=30;i++)for(int j=1;j<=1000;j++){
		for(int k=0;k<j;k++)f[i][j]=(1ll*g[i-1][k]*g[i-1][j-k-1]%mod+f[i][j])%mod;
		for(int k=0;k<=j;k++)g[i][j]=(1ll*f[i][k]*f[i][j-k]%mod+g[i][j])%mod;
	}
}
int main(){
	init();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&K),cnt=0;
		for(;(n&1)&&(n>1);n>>=1)cnt++;
		printf("%d\n",f[cnt][K]);
	}
	return 0;
}
```


---

## 作者：Leap_Frog (赞：1)

### P.S.
其实挺申必的，但是题目刚开始看错了。  

### Description.
每次正方形必须切成四个正方形。  
问给定正方形被切 $k$ 次后能形成几个不一样的正方形。  

### Solution.
首先，我们发现，每次切割转移类似于 $i\rightarrow 2i+1$。  
那么我们可以大力 dp，设状态 $f_{i,j}$ 表示边长为 $i$，切 $j$ 刀的方案数。  
那么我们显然有转移，如下。  
$$f_{2i+1,a+b+c+d-1}\leftarrow f_{i,a}\times f_{i,b}\times f_{i,c}\times f_{i,d}$$  
~~好然后就做完了~~  
做完个 dam，优良复杂度 $O(n\times K^4)$。  
~~松一松？（（（~~  
好，然后我们来考虑如何优化。  
这个 $O(K^4)\rightarrow O(K^2)$ 是基于一个套路。  
观察转移式子，发现其中的 $a,b,c,d$ 本质都是相同的。  
那么我们每 $\sqrt4=2$ 个转移分一组，然后先组内转移，组内转移完之后组见转移。  
具体的，设辅助数组 $g_{2i+1,a+b}\leftarrow g_{i,a}\times g_{i,b}$。  
那么显然有转移如下。  
$$\begin{cases}f_{2i+1,a+b-1}\leftarrow g_{i,a}\times g_{i,b}\\g_{2i+1,a+b}\leftarrow f_{2i+1,a}\times f_{2i+1,b}\end{cases}$$  
然后就做完了。  
桥豆麻袋，我们发现 $n\le 10^9$，然后复杂度原地爆炸。  
如何优化这个 $n$ 呢？我们考虑把它变成 $\log n$  
我们观察转移式，我们发现，每次都是 $n\rightarrow 2n+1$。  
那么我们定义偶数点为无法转移点。  
然后每个可转移点 $x$ 都是每次变成 $\frac{x-1}2$，至多 $\log x$ 次后就变成了无法转移点。  
同时，每个可转移点都显然是相同的。  
而我们发现，每次转移答案都是本质一样的。  
我们定义一个点可以转移直至非转移点的次数为它的深度。  
那么我们证明了，任意两个同深度的点，它们的答案相同。  
所以我们只需要记录每个结点的深度就好了。  
复杂度变成了 $O(K^2\log n)$，足以通过此题。  
### Coding.
~~代码不放了，有手就行。~~  
[代码链接](https://codeforces.com/contest/300/submission/111345601)  

---

## 作者：chihik (赞：1)

定义一个正方形的深度为只操作任意一角的正方形的最大操作次数。

$f_{m,k}$: 深度为 m 的正方形操作 k 次后不同数量。

显然有：

$$f_{m,k}=\sum_{k_1+k_2+k_3+k_4=k-1} f_{m-1,k_1} \times f_{m-1,k_2} \times f_{m-1,k_3} \times f_{m-1,k_4}$$

注意到 $m$ 最多为 $\log n$，所以我们得到了一个 $k^4\log n$ 的垃圾做法。

若干个下标的和为定值，根据套路构造卷积。

令 $g_{m,k}=\displaystyle \sum_{k_1+k_2=k} f_{m-1,k_1} \times f_{m-1,k_2}$

那么有：

$$f_{m,k}=\sum_{k_1+k_2=k-1}g_{m,k_1} \times g_{m,k_2}$$

$f,g$ 的转移均为卷积，使用 ntt 转移，时间复杂度 $\mathcal{O(k\log k \log n)}$。

```cpp
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 4000 , Mod = 7340033;
int Add( int x , int y ) { x += y; return x >= Mod ? x - Mod : x; }
int Sub( int x , int y ) { x -= y; return x < 0 ? x + Mod : x; }
int Mul( int x , int y ) { return 1ll * x * y % Mod; }
int Quick_pow( int x , int po ) { int Ans = 1; for( ; po ; po >>= 1 , x = Mul( x , x ) ) if( po & 1 ) Ans = Mul( Ans , x ); return Ans; }
int Inv( int x ) { return Quick_pow( x , Mod - 2 ); }

#define Poly vector< int >
#define len( x ) ( (int)x.size() )

const int G = 3 , IG = 2446678;
int lim , ilim , rev[ MAXN + 5 ];
void ntt( Poly &f , int ty ) {
	for( int i = 0 ; i < lim ; i ++ ) if( i < rev[ i ] ) swap( f[ i ] , f[ rev[ i ] ] );
	for( int len = 2 ; len <= lim ; len <<= 1 ) {
		int w = Quick_pow( ty == 1 ? G : IG , ( Mod - 1 ) / len );
		for( int l = 0 ; l < lim ; l += len ) {
			for( int i = l , wk = 1 ; i < l + len / 2 ; i ++ , wk = Mul( wk , w ) ) {
				int t = Mul( wk , f[ i + len / 2 ] );
				f[ i + len / 2 ] = Sub( f[ i ] , t ); f[ i ] = Add( f[ i ] , t ); 
			}
		}
	}
	if( ty == -1 ) for( int i = 0 ; i < lim ; i ++ ) f[ i ] = Mul( f[ i ] , ilim );
}
Poly operator * ( Poly f , Poly g ) {
	int n = len( f ) + len( g ) - 1; for( lim = 1 ; lim < n ; lim <<= 1 ); ilim = Inv( lim );
	for( int i = 0 ; i < lim ; i ++ ) rev[ i ] = ( rev[ i >> 1 ] >> 1 ) | ( i & 1 ? lim >> 1 : 0 );
	f.resize( lim ); g.resize( lim );
	ntt( f , 1 ); ntt( g , 1 );
	for( int i = 0 ; i < lim ; i ++ ) f[ i ] = Mul( f[ i ] , g[ i ] );
	ntt( f , -1 ); f.resize( min( n , 1001 ) );
	return f;
}

Poly f[ 35 ] , g[ 35 ];
void Dp( ) {
	f[ 0 ].resize( 1 ); f[ 0 ][ 0 ] = 1;
	for( int i = 1 ; i <= 30 ; i ++ ) {
		g[ i ] = f[ i - 1 ] * f[ i - 1 ];
		f[ i ] = g[ i ] * g[ i ];

		int t = f[ i ].back();
		for( int j = len( f[ i ] ) - 1 ; j >= 1 ; j -- ) f[ i ][ j ] = f[ i ][ j - 1 ];
		f[ i ].push_back( t );
	}
}

int t , n , k;
int main( ) {
	Dp();
	scanf("%d",&t);
	while( t -- ) {
		scanf("%d %d",&n,&k);
		int cnt = 0;
		for( int x = n ; ( x & 1 ) && x != 1 ; x = x / 2 , cnt ++ );
		printf("%d\n", len( f[ cnt ] ) <= k ? 0 : f[ cnt ][ k ] );
	}
	return 0;
}
```

---

## 作者：rubbishZZZ (赞：0)

## CF300D Painting Square
 

### 题意：

- 小熊瓦西里有一张大的正方形白色桌子，这张桌子由 $n$ 行 $n$ 列组成。整张桌子的边缘已经被涂成了黑色。

  例如，在 $n = 5$ 时初始桌子的样子如下：

  （图略，可视为一圈黑色边框，中心是白格）

  瓦西里想通过恰好 $k$ 步操作来涂色这张桌子。每一步操作包括以下几个动作：

  1. 小熊从桌子上选择一个**正方形区域**，该正方形满足：
     - 这个正方形的边框已经被涂成了黑色；
     - 正方形的内部（不包括边框）不能包含任何已经被涂黑的格子；
     - 正方形的边长不少于 $2$（即包含的格子数不少于 $2 \times 2$）；

  2. 然后，小熊在该正方形内部选择一行和一列，将该正方形内部这行和这列的所有格子都涂黑。

  3. 此操作后，由正方形的黑色边框和新涂黑的行、列所形成的若干矩形区域，必须都是面积大于 $0$ 的**正方形**。

  现在，瓦西里已经知道桌子的大小 $n$ 和他打算执行的操作次数 $k$。请你帮他计算：有多少种不同的方式可以在**恰好 $k$ 步操作后完成涂色**。

  如果两个方案最终得到的桌子在**至少一个格子上不同**，则认为这两个方案是不同的。

  由于答案可能很大，请输出对 $7340033$ 取模后的结果。



### 解法：

- 非常暴力的做：设 $f_{i,j}$ 表示边长为 $i$ 操作 $j$ 次的方案数，转移如下：

  1. 若 $2\mid i$，则 $f_{i,j}=[j=0]$。
  2. 若 $2\nmid i,j=0$，$f_{i,j}=1$。
  3. 若 $2\nmid i,j\gt 0$，$f_{i,j}=\sum\limits_{a+b+c+d=j-1} f_{\frac{i-1}{2},a}\times f_{\frac{i-1}{2},b},\times f_{\frac{i-1}{2},c}\times f_{\frac{i-1}{2},d}$

  暴力做是 $O(k^2n) $ 的。

  进一步，我们发现 $i$ 的值没那么重要，只和 $V_2(i+1)$ 有关，$V_2(i+1)$ 为 $i+1$ 中 $2$ 的幂次。

  那么这个值是 $\leq \log n$ 的，因此可以 $O(k^2\log n)$ 预处理出 $f$。

  求答案时，只需要算出 $V_2(b+1)$ 然后直接输出与处理好的 $f$ 即可。

  复杂度 $O(k^2\log n+Q\log n)$



### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef long double db;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int N=1005,mod=7340033;
int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void Fplus(int&x,int y){x=fplus(x,y);}
int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
void Fminus(int&x,int y){x=fminus(x,y);}
int f[35][N],g[N];

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	f[0][0]=1;
	rep(i,1,32){
		f[i][1]=1;
		rep(o,0,3){
			memset(g,0,sizeof g);
			rep(j,0,1000)rep(k,0,1000-j){
				Fplus(g[j+k],(ll)f[i][j]*f[i-1][k]%mod);
			}
			memcpy(f[i],g,sizeof g);
		}
		f[i][0]=1;
	}
	for(int Q=read();Q--;){
		int x=read(),k=read(),c=0;
		while(x>1&&(x-1)%2==0)c++,x/=2;
		printf("%d\n",f[c][k]);
	}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
感觉挺好的一道题，思路的三个层次挺分明的。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先方案数都要取模了，肯定会很多，再加之这是一个动态变化的过程，考虑用计数 dp 来解决。

设计 $f_{i,j}$ 表示大小为 $i$ 的正方形，操作 $j$ 步的方案数。

那么我们可以得到转移方程式 $f_{2i+1,a+b+c+d-1}=f_{i,a}\times f_{i,b}\times f_{i,c}\times f_{i,d}$。

其意义即为把边长为 $2i+1$ 的正方形花一步切割为 $4$ 个小的边长为 $i$ 的正方形，这四个正方形分别给 $a,b,c,d$ 步切割。

复杂度达到 $O(nk^4)$，面对 $n\le 10^9,k\le 10^3$ 不知道挂哪去了。

考虑来优化这个过程。

首先对 $k^4$ 下手，显然的是如果一个正方形能分割，那么分割出的 $4$ 个小正方形显然是相等的。

那么这四个小正方形的答案显然是等价的。

那么我们可以考虑不要暴力枚举这 $4$ 个正方形来合并，考虑两两合并即可。

定义 $g_{i,a+b}=f_{i,a}\times f_{i,b}$。

那么转移式就是 $f_{2i+1,a+b-1}=g_{i,a}\times g_{i,b}$。

这样复杂度来到 $O(nk^2)$，面对这个 $n\le10^9$ 还是挂飞。

接着考虑如何把 $n$ 优化下去。

发现转移式里有 $2i+1$ 这个东西，如果能利用这玩意就可以把复杂度降到 $O(\log nk^2)$。

不难发现有大量的正方形的情况是重复的。

区分两种不同情况其实就是其最大可分割次数的不同。

例如对于 $n=3,5$ 时，任取 $k$ 的答案都是相同的。

因为正方形的大小并不影响方案数，只有分割与不分割影响。

接着就是考虑如何求出最大可分割次数。

显然的是一个边长为 $n$ 的正方形分割一次后边长变为 $\frac{n-1}{2}$，如果不能整除就是不能分割了。

化成二进制也就是末尾连续 $1$ 数量 $-1$，这个显然是 $\log$ 的。

所以复杂度就是 $O(\log nk^2)$。

注意预处理出所有可能性直接回答，因为题目没有多测的数据总和保证，如果每次处理会直接挂飞。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010,V=1e6,INF=0x3f3f3f3f3f3f3f3f,mod=7340033;
int T,n,k,f[35][N],g[35][N];
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
    inline void put(string s) { for(char c:s) put(c); }
    inline void print(int x)
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
signed main()
{
    T=read();
    for(int i=0;i<=30;i++) f[i][0]=g[i][0]=1;
    for(int i=1;i<=30;i++)
        for(int j=1;j<=1000;j++)
        {
            for(int k=0;k<j;k++) f[i][j]=(f[i][j]+g[i-1][k]*g[i-1][j-k-1])%mod;
            for(int k=0;k<=j;k++) g[i][j]=(g[i][j]+f[i][k]*f[i][j-k])%mod;
        }
    while(T--)
    {
        n=read(),k=read();int tot=0;
        while((n&1)&&(n^1)) tot++,n>>=1;
        print(f[tot][k]),put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：Godのfather (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF300D)

这是一道~~恶评~~题($CF$上$2300$,洛谷上是一道紫题)

这题其实并不难(当然用$FFT$的当我没说)

## （〇）前置知识

1.动态规划

2.~~FFT~~

## （一）解题思路

这个$DP$应该是很容易看出来的。

题目有$k$次操作，每次操作可以将$1$个正方形划分成$4$个正方形，给出一个$n\times n$的正方形，问有多少种不同的划分方案。

需要注意的是，每次操作会占用正方形最中间的一行和最中间的一列，且每次必须要将一个大正方形划分为四个小正方形(即划分方案中不能存在非正方形)。

初看题目，很容易想到$DP$。$DP$的状态也很容易表示，设$f(n,k)$表示将一个大小为$n$的正方形划分$k$次的方案数。

状态转移方程很显然。即

$$f(n,k)=\sum\limits_{i+j+x+y=k-1}f(\dfrac{n-1}{2},i)\times f(\dfrac{n-1}{2},j)\times f(\dfrac{n-1}{2},x)\times f(\dfrac{n-1}{2},y)$$

于是我们很开心地看了一眼数据范围:$1\leq n\leq10^9,0\leq k\leq 1000$~~GG~~

空间和时间都爆了。

首先我们来解决空间问题。不难发现(假设$n$很大)，我们需要用到的只有$f(n,k)$和$f(\dfrac{n-1}{2},k)$中间$n-1$到$\dfrac{n-1}{2}+1$的空间其实都浪费了。

而且，由于每次必须切成四个正方形，所以当$n\%2=0$时，是无法划分出正方形的。换句话说，当二进制下$n$的末尾为$0$时，$ans=0$，后面$\dfrac{n-1}{2}$
的情况我们也不需要考虑了。

由此，我们需要的空间大大减小了，只需要关注$\dfrac{n-1}{2}$和二进制下$n$的末尾不为$0$的情况。

用一个$cnt$记录$n$满足以上条件的$n$的数量。那么$cnt$实质上就等于二进制下$n$的末尾连续$1$的个数(当然当$n=1$时，按照题目要求我们同样不考虑)。

显然$cnt\leq 29$

再解决时间复杂度的问题。

观察状态转移方程，我们发现其实$k^4$的枚举做了很多无用功，很多$i+j+x+y\not= x$的情况都被枚举了。下面是$FFT$惯用伎俩。

考虑将状态转移方程拆分。变为

$\sum\limits_{i+j=l}f(\dfrac{n-1}{2},i)\times f(\dfrac{n-1}{2},j)$和$\sum\limits_{x+y=z}f(\dfrac{n-1}{2},x)\times f(\dfrac{n-1}{2},y)$

其中$l+z=k-1$。感觉到了卷积吗？

最终的答案其实就是上述两个多项式相乘(这个不用解释吧)

设$g(x,y)=\sum\limits_{i+j=y}f(x,i)\times f(x,j)$

那么原状态转移方程就变为:

$$f(n,k)=\sum\limits_{i+j=k-1}g(\dfrac{x-1}{2},i)\times g(\dfrac{x-1}{2},j)$$

显然上述两个式子都能用$FFT$快速求出来。然而数据范围告诉我们不用$FFT$。所以~~我才不用FFT呢，谁用谁***~~。当然数据范围扩大就必须用了。~~建议扩大数据范围~~

---

