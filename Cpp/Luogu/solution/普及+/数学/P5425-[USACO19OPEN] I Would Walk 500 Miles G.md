# [USACO19OPEN] I Would Walk 500 Miles G

## 题目描述

Farmer John 想要将他的编号为 $ 1 \ldots N $ 的 $ N $ 头奶牛（ $ N \leq 7500 $ ）分为非空的 $ K $ 组（ $ 2 \leq K \leq N $ ），使得任意两头来自不同组的奶牛都需要走一定的距离才能相遇。奶牛 $ x $ 和奶牛 $ y $ （其中 $ 1 \leq x<y \leq N $ ）愿意为了见面走 $ (2019201913x+2019201949y) \mod 2019201997 $ 英里。

给定一个将 $ N $ 头奶牛分为 $ K $ 个非空小组的分组方案，令 $ M $ 为任意两头来自不同组的奶牛愿意为了见面行走的英里数的最小值。为了测试奶牛们相互之间的忠诚度，Farmer John 想要将 $ N $ 头奶牛以最佳的方式分为 $ K $ 组，使得 $ M $ 尽可能大。 

## 说明/提示

在这个例子中，奶牛 $1$ 和奶牛 $2$ 愿意为了见面走 $2019201817$ 英里。奶牛 $2$ 和奶牛 $3$ 愿意走 $2019201685$ 英里。奶牛 $1$ 和奶牛 $3$ 愿意走 $2019201769$ 英里。所以，将奶牛 $1$ 单独分为一组，奶牛 $2$ 和奶牛 $3$ 分为一组，$M = \min(2019201817, 2019201769) = 2019201769$（这是我们在这个问题中能够达到的最佳结果）。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2019201769```

# 题解

## 作者：ix35 (赞：30)

一道很搞笑的结论题。

唯一一篇题解中有提到图论的部分，但是我刚看到这玩意真不觉得是个图论。首先先拆式子吧。

设$P=2019201997$，则$x<y$产生的代价为$((P-84)x+(P-48)y)\mod P$，这个大数看着有点心烦，想办法把它拆去：

$((P-84)x+(P-48)y)\mod P=((-84x-48y)\mod P+P)\mod P$

我们发现由于$N\leq 7500$，因此$-84x-48y$远远不到$-P$，所以内层的取模时可以去掉的，另外由于它总是个负数，因此加上P后不必再取模，外层的取模实际上也是可以去掉的，所以代价为：

$$-84x-48y+P$$

下面让它的最小值取最大值。有一个很显然的结论，最小值一定由$N$和另一个数产生，假设不是这样，那么设最小值由$r<s$组成，那么其中必有一个数与$N$不在一组（否则$r,s$一组矛盾），于是将其中一个换成$N$得到结果更小。

那么当$N$确定时，这个式子的值尽量大，其实就是$x$尽量小，由于$K$组都非空，所以我们让$1...K-1$各自单独一组，最后$K...N$一组，那么$(K-1,N)$可以组成最大的最小值，即：

$$-84(K-1)-48N+P$$

于是就...

注意这玩意看上去大，实际上超小，不会超int，所以随便过。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int main () {
	scanf("%d%d",&n,&k);
	printf("%d\n",-12*(7*(k-1)+4*n)+2019201997);
	return 0;
}
```


---

## 作者：ModestCoder_ (赞：8)

首先通过打表能找到性质：

$x+y$越大，最终产生的距离是越小的

以$n=7500$为例

$7500,7499$产生的数肯定是最小的，这两个数必须归到一组

接下来依次是

$7498,7500;7498,7499……$

发现可以最大的一堆数分到同一组里，那么从几开始不行了呢

当然是$k-1$与$n$

所以直接出结论$x=k-1,y=n$的时候就是答案

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 7510
#define maxm 1210000
#define LL long long
using namespace std;
const LL X = 2019201913, Y = 2019201949, p = 2019201997;
LL n, k;

int main(){
	scanf("%lld%lld", &n, &k);
	printf("%lld\n", (X * (k - 1) + Y * n) % p);
	return 0;
}
```


---

## 作者：Great_Influence (赞：6)

算法 $1$:

我们将所有的边选出来，然后从小到大一条条加入，当剩下集合数量 $< K$ 的时候就结束。答案为加入的最后一条边的大小。

复杂度 $O(N^2\log N)$ 。

过不去，不贴代码。

算法 $2$:

观察上述算法，发现导致集合数量下降的边一定在最小生成树上。(算法 $1$ 其实等价于 $kruskal$) 因此，我们选择将最小生成树求出，然后答案就是最小生成树上边权第 $N-K+1$ 小的边长。

利用 $prim$ 求解，复杂度 $O(N^2)$ 。

代码:

```cpp
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iostream>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mp make_pair
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using IO::read;
using IO::write;
using IO::getc;
using IO::flush;

inline void Chkmin(int&u,int v){u>v?u=v:0;}

inline void Chkmax(int&u,int v){u<v?u=v:0;}

inline void file()
{
#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
#endif
}

const int MAXN=7507;

static int n,k;

inline void init()
{
	read(n),read(k);
}

static int dis[MAXN][MAXN];

static int ds[MAXN],vs[MAXN];

static int w[MAXN];

inline void solve()
{
	Rep(i,1,n-1)Rep(j,i+1,n)dis[j][i]=dis[i][j]=(2019201913ll*i+2019201949ll*j)%2019201997;

	Rep(i,2,n)ds[i]=dis[1][i];
	vs[1]=1,ds[0]=2147483647;
	register int rt=1;
	Rep(i,1,n-1)
	{
		Rep(j,1,n)Chkmin(ds[j],dis[rt][j]);
		rt=0;
		Rep(j,2,n)if(!vs[j]&&ds[j]<ds[rt])rt=j;
		vs[rt]=1,w[i]=ds[rt];
	}
	sort(w+1,w+n);
	cout<<w[n-k+1]<<endl;
}

int main()
{
    file();
    init();
    solve();
    return 0;
}

```

算法 $3$:

观察边权，可以发现 $(i,j)$ 之间连的边长度为 $2019201997-84i-48j$ 。

因此，这棵最小生成树的形态一定为一朵以 $N$ 为根的菊花树，且边权分别为 $2019201997-84i-48N$ 。

那么，第 $N-K+1$ 小的边长度就是:

$$2019201997-84(K-1)-48N$$

$$=2019202081-84K-48N$$

复杂度 $O(1)$ 。

代码就不贴了。

---

## 作者：hanzhongtlx (赞：2)

## [更好的阅读体验点这里](https://www.cnblogs.com/tlx-blog/p/12251013.html)
### ~~所以这道题为什么可以这样做~~ 
嗯，我也不知道，不过我是来填坑的（其实只是提供另一种证法）。  
$Q$：为什么要把牛分成$1$,$1$......$N-K+1$这样的$K$组呢？   
$A$:我们设第$i$组分到$n_i$头牛，当然我们知道共有$\dfrac{N(N-1)}{2}$条可连的边，保证被吃掉的边最多即可。    
显然，被吃掉的边数为      
$\sum\limits_{i=1}^K \dfrac{n_i(n_i-1)}{2}= \dfrac {\sum\limits_{i=1}^K n_i^2-\sum\limits_{i=1}^K n_i}{2}=\dfrac {\sum\limits_{i=1}^K n_i^2-N}{2}$   

是$\sum\limits_{i=1}^K n_i^2$决定着大小。  

又因为   
$\sum\limits_{i=1}^K n_i^2 =$（$\sum\limits_{i=1}^K n_i$）$^2$ $-2\sum\limits_{i=1}^K\sum\limits_{j=1}^K(i!=j)n_in_j$    

那我们应保证 $2\sum\limits_{i=1}^K\sum\limits_{j=1}^K(i!=j)n_in_j$ 最小，回想一个小学的结论，相同的周长的矩形中，正方形的面积最大，即长宽相差越大，面积越小，正可以推广到这里。   

得证。

---

## 作者：Saliеri (赞：2)

### 神仙结论题
___

一句话题意：

给你 $n,k$ ,求 将 1~n  $n$ 个数划分为 $k$ 组中，跨组的两数$i,j$中 

$Min[(2019201913i + 2019201949 j)mod2019201997]$的最大值

___

怎么办呢

大数看着烦，先令$X = 2019201997$

代回原式子

原式$= [(X-84)i+(X-48)j]mod \ X $(为美观先去掉$Min$)

$ = [Xi + Xj - 84i - 48j]mod \ X$

$ = [-84i -48j + X] mod \ X$(其实可以把外层mod去掉）

$ = -84i -48j + X$

使这个式子最小值最大

构造一个最小值

$j$ 肯定 $=n$(毕竟是最小值)

使 $i$ 在保证是全式最小值时最小

所以

就有策略了
___

将$1,2,3,4...k-1$分别分为一组，

$k,k+1...,n$为一组

$i$就可以尽量最小了（$i = k-1$）
___

$Ans = -84*(k-1)-48*N + 2019201997$

___
#### Code
```cpp
#include <cstdio>
using namespace std;
int n,k;
int main(){
	scanf("%d %d",&n,&k);
	printf("%lld",(long long)-84*(k-1)-48*n+2019201997);
	return 0;
}
```

---

## 作者：tommymio (赞：1)

在模意义下，题目给出的那个柿子可以写作 $-84x-48y$，并且我们发现当 $n\leq 7500$ 时，这个式子的值不会超过给出的模数，所以可以直接把它写成 $2019201997-84x-48y$。

现在要令这个柿子的最小值最大。我们发现最小值一定在 $y=N$ 时取到，又因为在不同组之间都会取这样的一个值，所以我们希望 $L\sim N$ 被分到一组。题目要求我们只能分 $K$ 个非空组，那么我们就把 $1,2,...K-1$ 单独分组，$K\sim N$ 分为一组，这样的话最小值一定最大，为 $2019201997-84(K-1)-48N$。

---

## 作者：泰勒斯威夫特 (赞：0)

> 获取更好的阅读体验,请[点击此处](https://www.cnblogs.com/TaylorSwift13/p/11169057.html)

介绍一种从思维难度/时间复杂度/代码复杂度总体来看**性价比**比较高的做法.

我们可以把$x$奶牛与$y$奶牛"愿意为了见面行走的英里数"**表示成一个函数**:

$$g(x,y)=(2019201913 \times min(x,y)+2019201949 \times max(x,y))\mod 2019201997$$

同时我们定义
$$f(i)=min(g(i,j))\quad 1\leq j\leq n,i\ne j $$

那么显然答案是**这$n$头奶牛的$f(i)$值由大到小排序的第$k-1$个**,对应的情况是$f(i)$值由大到小排序的第$1$个动物到第$k-1$个动物每$1$个自成$1$组,剩下的所有动物成$1$组,共$k$组.

时间复杂度$O(n^2)$,空间复杂度$O(n)$.

这个解法**可以拓展到$g(x,y)$这个函数略有变化的情况**,只要$g(x,y)$可以$O(1)$求出来,都可以用该解法解决.

**代码**

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define SIZE 7505
#define INF 0x7FFFFFFF
const long long P1=2019201913;
const long long P2=2019201949;
const long long Mod=2019201997;
inline int Fx(long long u,long long v){return (int)((P1*u+P2*v)%Mod);}
int n,k,x[SIZE];

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)x[i]=INF;
    for(int u=1;u<=n;u++)
        for(int v=u+1;v<=n;v++)//题目要求第一个数小于第二个数
        {
            int Tem=Fx(u,v);
            x[u]=min(x[u],Tem);
            x[v]=min(x[v],Tem);
        }
    sort(x+1,x+1+n);
    printf("%d\n",x[n-(k-2)]);//由大到小的第k-1个数,下标应该是n-(k-1)+1
    return 0;
}
```





---

