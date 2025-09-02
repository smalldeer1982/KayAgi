# koishi的数学题

## 题目描述

Koishi 在 Flandre 的指导下成为了一名数学大师，她想了一道简单的数学题。

输入一个整数 $n$，设 $\displaystyle f(x) = \sum_{i=1}^n x \bmod i$，你需要输出 $f(1), f(2), \ldots , f(n)$。

按照套路，Koishi 假装自己并不会做这道题，就来求你帮忙辣。

## 说明/提示

对于 $20\%$ 的数据，$n \le 1000$。  
对于 $60\%$ 的数据，$n \le 10^5$。  
对于 $100\%$ 的数据，$1 \le n \le 10^6$。


## 样例 #1

### 输入

```
10
```

### 输出

```
9 16 22 25 29 27 29 24 21 13
```

# 题解

## 作者：crazydave (赞：30)



#思路#
老师上课讲的例题，方法真的很神奇。

观察样例，如果没有发现什么的话，就模拟打出一张表好了：(横坐标为x, 纵坐标为y)
![](https://img-blog.csdn.net/20180207191535238?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQ3JhenlfX0RhdmU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


显然每一横行加起来就是答案，神奇的是在于纵行！~~（不要问我怎么发现的）~~。

每一纵行的意义即是，对于一个固定的i, x递增时的$x ~mod ~ i$。可以发现它是以i个为循环的数列。

处理上面一个数列复杂度较高，但是我们可以这样处理：发现对于一个固定的i, x递增时的 x-（x mod  i），它便是每i项增加i的一个数列。于是我们可以每i个数打一个标记，标记意为增加i。

然后我们可以发现，f(x)可以从f(x-1)推到，便是f(x-1)+n-1-标记。（类似于前缀和+差分维护吧）
#代码#

```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
long long n,j,temp,ans,tag[MAXN]; //tag数组即为标记

int main(){
  scanf("%lld",&n);
  for(int i=2; i<=n; i++)
	  for(int j=i; j<=n; j+=i)
		  tag[j]+=i;  //处理tag数组,每i位加i
  for(int i=1; i<=n; i++)
  {
      ans+=n-tag[i]-1;
	  printf("%lld ",ans); //递推得出答案
  }
  return 0;
}
```

---

## 作者：asuldb (赞：18)

这道题还是挺不错的


$$f(x)=\sum_{i=1}^nx\ mod \ i$$

求$1...n$所有的$f$

发现这个带着$mod$的东西还是挺不好求的，于是考虑一下化开这个式子

$$\sum_{i=1}^nx\ mod\ i=\sum_{i=1}^nx-\left \lfloor \frac{x}{i} \right \rfloor \times i$$

也就是

$$nx-\sum_{i=1}^n\left \lfloor \frac{x}{i} \right \rfloor i$$

我们只要对于每一个$x$求出后面那个式子就好了

好像整除分块随便做啊

确实是这样的，一次要你求这么多显然不是让你暴力整除分块的，毕竟复杂度$O(n\sqrt{n})$

我们考虑一下递推，就是从$f(x)$推到$f(x+1)$

不管前面的式子，后面的式子就会变成

$$\sum_{i=1}^n\left \lfloor \frac{x+1}{i} \right \rfloor i$$

我们考虑一下$x$变成$x+1$会使得那些$i$的值发生变化

显然是当$i$为$x+1$的约数时，$\left \lfloor \frac{x}{i} \right \rfloor$会比$\left \lfloor \frac{x+1}{i} \right \rfloor$小$1$

这个非常显然了，因为$x+1$和$x$一定是互质的，所以$x+1$的约数肯定不是$x$的约数，于是当$x$变成$x+1$之后这些$x+1$的约数在下去整符号里的值也会变大$1$

乘上后面的$i$显然后面的式子就是增加了$x+1$的所有约数的和

这个当然是积性函数可以线筛了，但是调和级数过百万好像也不错

代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define LL long long
#define maxn 1000005
int n;
LL f[maxn],ans[maxn];
int main()
{
	scanf("%d",&n);
	for(re int i=1;i<=n;i++)
		for(re int j=i;j<=n;j+=i) f[j]+=i;
	ans[1]=1;
	for(re int i=2;i<=n;i++)
		ans[i]=ans[i-1]+f[i];
	for(re int i=1;i<=n;i++)
		printf("%lld ",(LL)n*(LL)i-ans[i]);
	return 0;
}

```

---

## 作者：wyx150137 (赞：11)

正解的做法好神啊 想不到怎么办 我们来一点更好想的吧


我们考虑现在已经知道了 $F(t)$ 的值想要知道 $F(t+1)$ 的值该怎么办。考虑一定是一堆数字+1，另外一堆数字变成了0.


那么哪坨数字变成了0呢？


当然这些数字是$i$的约数啊，只有这样他们 $i$ 膜上他们才是0。所以我们只需要枚举每一个$t$,然后枚举 $t$的约数就可以啦~


枚举约数通过预处理可以做到 $O(n\log{n})$,具体做法是枚举每个数的若干倍然后统计



---

## 作者：Karry5307 (赞：10)

### 题意

给定整数 $n$，设 $f(x)=\sum\limits_{i=1}^{n}x\bmod i$，对于 $1\leq i\leq n$ 求 $f(i)$。

$\texttt{Data Range:}1\leq n\leq 10^6$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13678532.html)

做完这题之后看了一下题解区，都写的啥啊，来写篇思路清晰点的。

考虑推下式子：

$$\sum\limits_{i=0}^{n}x\bmod i=nx-\sum\limits_{i=1}^{n}i\left\lfloor\frac{x}{i}\right\rfloor$$

接下来考虑差分：

$$\sum\limits_{i=1}^{n}i\left(\left\lfloor\frac{x}{i}\right\rfloor-\left\lfloor\frac{x-1}{i}\right\rfloor\right)=\sum\limits_{i=1}^{n}i[i\mid x]=\sigma(x)$$

所以

$$\sum\limits_{i=0}^{n}x\bmod i=nx-\sum\limits_{i=1}^{x}\sigma(i)$$

线性筛出 $\sigma(i)$ 的前缀和即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e6+51;
ll n,ptot;
li cur;
ll np[MAXN],prime[MAXN],low[MAXN];
li sum[MAXN],sigma[MAXN];
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
inline void sieve(ll limit)
{
	np[1]=low[1]=sum[1]=sigma[1]=1;
	for(register int i=2;i<=limit;i++)
	{
		if(!np[i])
		{
			prime[++ptot]=i,low[i]=i,sum[i]=sigma[i]=i+1;
		}
		for(register int j=1;i*prime[j]<=limit;j++)
		{
			np[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				low[i*prime[j]]=low[i]*prime[j];
				sum[i*prime[j]]=sum[i]+low[i*prime[j]];
				sigma[i*prime[j]]=sigma[i]/sum[i]*sum[i*prime[j]];
				break;
			}
			low[i*prime[j]]=prime[j],sum[i*prime[j]]=prime[j]+1;
			sigma[i*prime[j]]=sigma[i]*sigma[prime[j]];
		}
	}
}
int main()
{
	sieve(n=read());
	for(register int i=1;i<=n;i++)
	{
		cur+=sigma[i],printf("%lld ",(li)i*n-cur);
	}
}
```

---

## 作者：Zoewilly (赞：8)

看了一眼题解，复杂度是nlogn的，不过我觉得如果数据大点会被卡掉

说一下我的做法：

考虑一下递推，考虑每一行和下一行的关系 比如说：

8%1  8%2  8%3  8%4  8%5  8%6  8%7  8%8  8%9  8%10 --------> f[8]

9%1  9%2  9%3  9%4  9%5  9%6  9%7  9%8  9%9  9%10 --------> f[9]


考虑一下f[8]和f[9] 的大小关系，可以发现，对于有些对应项,(9%1)=(8%1)+1,,,(9%2)=(8%2)+1........

但对于有些对应项 9%3=0 8%3=2

由于相邻两个数是互质的，他们不会有大于1的最大公约数，即不会出现x>1，使得8%x=0 && 9%x=0

所以对于9的因数x(x>1), a[9,x]=a[8,x]-(x-1);

所以f[9]=f[8]+10-(9的因数和)



推广： 对于f[x],f[x-1],在模(1....p)意义下,f[x]=f[x-1]+p-(x的因数和)

所以递推公式就出来了，边界条件f[1]=p-1; 递推的时间复杂度为O(N)

因数和怎么处理呢？已知因数和是积性函数（由积性函数定义可知），所以线性筛就可将其预处理，时间复杂度O(N)

综合一下，时间复杂度为O(N)





```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000000
typedef long long LL;
LL f[N+1],ans[N+1];
int prim[N+1],t[N+1],tot,n;
bool flag[N+1];
void init(void)//因数和线性筛
{
    f[1]=1;
    for (int i=2;i<=n;i++) 
    {
        if (!flag[i]) 
        {
            prim[++tot]=i;
            f[i]=i+1;
            t[i]=i;
        }
        for (int j=1;j<=tot;j++)
        {
            int k=prim[j]*i;
            if (k>n) break;
            flag[k]=1;
            if (i%prim[j]==0)
            {
                t[k]=t[i]*prim[j];
                if (k==t[k])
                    for (int w=1;w<=k;w*=prim[j]) f[k]+=w;
                else 
                    f[k]=f[t[k]]*f[k/t[k]];
                break;
            }
            t[k]=prim[j];
            f[k]=f[prim[j]]*f[i];
        }
    }
}
int main()
{
    scanf("%d",&n);
    init();
    ans[1]=n-1;
    for (int i=2;i<=n;i++) ans[i]=ans[i-1]+n-f[i];
    for (int i=1;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：fjzzq2002 (赞：6)

注意到对于固定的i，$x~mod~i$为$0,1,2,...,i-1,0,1,2...$这样循环。


考察$x~mod~i-x$的值，那么它就为$0,0,...,0,i,i,...,2i,2i...$这样，每个i的倍数差值增加i。


那么我们只要用一个数组记录$x~mod~i-x$的值，每次枚举i的倍数将其减i，最后前缀和一下。对于每个i都这么做，最后一起前缀和即可。


$\sum_{i=1}^n \frac{n}{i}=O(nlogn)$。


---

## 作者：fscbti (赞：5)

这是一道比较神奇数论题。可以从暴力写起。但是，先要想一下，确定大概的一个框架。

很简单的思路：当模数$i>x$时，明显得到仍是$x$，这样就可以把解题分为两块：**1**.$x>i$；
**2**.$x<i$（当$x=i$时，明显余数为0，无需计算）。对于情况**1**直接可以求出为$(n-x)*x$ ，而本题的难点也就是求出情况**2**的值（答案就是情况**1**加情况**2**）

$20pts$的暴力应该很简单的了
直接给出代码，时间复杂度为$O(n^2)$
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,s,x;
signed main(){
    n=read();printf("%d ",n-1);
    for(int i=2;i<=n;i++){
        x=i;s=x*(n-x);int j;
        for(j=2;j<=x;j++){
            if(x%j)s+=x%j;
        }
        printf("%d ",s);
    }
    printf("\n");
    return 0;
}
```
接着就要改进思路了。

可以这样想：当$x$和$x-1$都不整除$i$，那么x%i就等于(x-1)%i+1了。因此，可以求出(x-1)对所有小于它的数取模的总值，而x对所有小于它的数取模的总值只要在其基础上稍微变化了：

1. 假设x不整除所有比它小的数，只要加上(x-2)了，因为1明显去除，x本身也要去除。表示对每个小于x（除1以外）的数取模都加1
1. 当x可以整除i时，要减去i，因为(x-1)%i肯定是(i-1)了，之前有加了1，所以多算了i
这样，思路就优化多了

可以直接码出$60pts$了,时间复杂度为$O(nsqrt(n))$
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,x,tot=0;
signed main(){
    n=read();printf("%d ",n-1);
    if(n==1)return 0;
    printf("%d ",2*(n-2));
    for(int i=3;i<=n;i++){
        tot+=(i-2);x=i;
        for(int j=2;j<=x/j;j++){
            if(j*j==x){tot-=j;break;}
            if(x%j==0)tot-=(j+x/j);
        }
        printf("%d ",tot+(n-i)*i);
    }
    printf("\n");
    return 0;
}
```
因为数据比较大，所以还要优化。

可以用筛法，预处理每个数的因数和，这样就可以$AC$了

满分代码如下，时间复杂度为$O(nlogn)$
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,tot=0,a[1000005];
void prime(){
    for(int i=2;i<=n;i++){
        for(int j=i;j<=n/i;j++){
            a[i*j]+=i+j;
            if(i==j)a[i*j]-=i;
        }
    }
}
signed main(){
    n=read();printf("%d ",n-1);
    if(n==1)return 0;
    printf("%d ",2*(n-2));
    prime();
    for(int i=3;i<=n;i++){
        tot+=(i-2);
        tot-=a[i];
        printf("%d ",tot+(n-i)*i);
    }
    printf("\n");
    return 0;
}
```
这是道很有意义的数论题。

---

## 作者：忘怀星 (赞：4)

菜菜的我看到这题首先想到了 [这道题](www.luogu.com.cn/problem/P2261) ,虽然仔细看了一下除了长得像并没有什么关系 。

好了，题解开始！

首先我们当然是要将式子变形 

$f(x) = \sum\limits_{i=1}^n x\bmod i\ =\ \sum\limits_{i=1}^n \left(x-\left\lfloor \frac{x}{i}\right\rfloor\times i\right) \ =\ n\times x - \sum\limits_{i=1}^n \left\lfloor \frac{x}{i}\right\rfloor\times i$

我们发现如果我们单纯的依赖这个式子计算复杂度是一定不行的，我们考虑递推。我们比较一下 $f(x)$ 和 $f(x+1)$ 的区别，方便我们进行递推。

$f(x) = n\times x - \sum\limits_{i=1}^n \left\lfloor \frac{x}{i}\right\rfloor\times i$

$f(x+1) = n\times \left(x + 1\right) - \sum\limits_{i=1}^n \left\lfloor \frac{x+1}{i}\right\rfloor\times i$

$f(x+1) - f(x) = n-\sum\limits_{i=1}^n\left(\left\lfloor \frac{x+1}{i}\right\rfloor - \left\lfloor \frac{x}{i}\right\rfloor\right)\times i$

我们考虑怎么计算 $\sum\limits_{i=1}^n \left(\left\lfloor \frac{x+1}{i}\right\rfloor - \left\lfloor \frac{x}{i}\right\rfloor\right)\times i$

显然，只有当 $i\mid \left(x+1\right)$ 时，才有 $\left\lfloor \frac{x+1}{i}\right\rfloor - \left\lfloor \frac{x}{i}\right\rfloor = 1$ 否则 $\left\lfloor \frac{x+1}{i}\right\rfloor - \left\lfloor \frac{x}{i}\right\rfloor = 0$

因此 $\sum\limits_{i=1}^n \left(\left\lfloor \frac{x+1}{i}\right\rfloor - \left\lfloor \frac{x}{i}\right\rfloor\right)\times i = \sum\limits_{d\mid \left(x+1\right)}i$

也就是等于 $x$ 的约数和。

我们来看如何求一个数字的约数和，我们使用线性筛的求法。


[跳转](https://oi-wiki.org/math/sieve/#_8)

~~吐槽这里wiki讲的好简略~~

给wiki补充一下 $g(x)$ 的意义大概是 $\sum\limits_{i=0}^{c_p} p^i$ 其中 $p$ 是 $x$ 的最小质因数。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
int read()
{
    int a = 0,x = 1;char ch = getchar();
    while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
    return a*x;
}
const int N=1e6+7;
int n,vis[N];
int f[N],g[N];
int pri[N],cnt;
void init()
{
    f[1] = 1,g[1] = 1;
    for(int i = 2;i <= n;i ++) {
        if(!vis[i]) {pri[++cnt] = i;g[i] = f[i] = i+1;}
        for(int j = 1;j <= cnt && i*pri[j] <= n;j ++) {
            vis[i*pri[j]] = 1;
            if(i%pri[j] == 0) {
                g[i*pri[j]] = g[i]*pri[j]+1;
                f[i*pri[j]] = f[i]/g[i]*g[i*pri[j]];
                break;
            } else {
                f[i*pri[j]] = f[i]*f[pri[j]];
                g[i*pri[j]] = pri[j]+1
            }
        }
    }
}

signed main()
{
    n = read();init();
    int ans = 0;
    for(int i = 1;i <= n;i ++)
        printf("%lld ",ans = ans+n-f[i]);
    return 0;
}
```

---

## 作者：tututu (赞：4)

我太菜了看不懂官方题解orz

感觉有些像..

看看样例的例子:

```cpp
造了一张i mod j的表... 
  i=1   2   3   4   5   6   7   8   9   10
j↓ 
1---0   0   0   0   0   0   0   0   0   0
2---1   0   1   0   1   0   1   0   1   0
3---1   2   0   1   2   0   1   2   0   1
4---1   2   3   0   1   2   3   0   1   2
5---1   2   3   4   0   1   2   3   4   0
6---1   2   3   4   5   0   1   2   3   4
7---1   2   3   4   5   6   0   1   2   3
8---1   2   3   4   5   6   7   0   1   2
9---1   2   3   4   5   6   7   8   0   1
10--1   2   3   4   5   6   7   8   9   0
   
ans=9   16  22  25  29  27  29  24  21  13
``` 
案就是算出每列的和,只能找每列与前一列的关系了.

某列的每个数都比前一列对应位置的数大1,或变成了0,那么第j行出现0的位置都是j的整数倍...

而这些0的位置是可以枚举的,在f[k\*j]的位置-j..~~(就和官方一样了)~~

答案就是上一个答案+n-f[i]..蒟蒻想减小下常数就把第一行忽略了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
long long n,f[1000002],sum;
int main(){
  cin>>n;
  rep(i,2,n) for(int j=i;j<=n;j+=i) f[j]+=i;
  rep(i,1,n) printf("%lld ",sum=sum+n-1-f[i]);
  return 0;
}
```

---

## 作者：Fuyuki (赞：3)

观察一下对于$k\in[1,n]$，其对于每个位置的贡献为多少：

$1,2,3,...,k-1,0,1,2,3,...$

差分一次。

$1,1,1,...,1,1-k,1,1,1,...$

再差分一次。

$1,0,0,0,0,0,-k,k,0,0,...$

那么直接在$O(nlogn)$的时间内求出原数组的二阶差分再还原即可。

```cpp
#include<iostream>
using namespace std;
#define rnt register int
#define FOR(i,a,b) for(rnt i=a;i<=b;i++)
int n;
long long a[1000001];
int main(){
	cin>>n,a[1]=n-1;
	FOR(i,2,n)for(rnt j=i;j<=n;j+=i)
    	a[j]-=i,a[j+1]+=i;
	FOR(i,1,n)a[i]+=a[i-1];
	FOR(i,1,n)cout<<(a[i]+=a[i-1])<<' ';
	return 0;
}
```


---

## 作者：Sweetlemon (赞：3)

本题是要求从1到n每一个整数的f函数值，且n较大，可以想到使用递推的方法。

现在让我们想一想，从f(x)到f(x+1)，f值有什么变化呢？

如果不考虑取余，那么f(x+1)=f(x)+n。但是由于x+1%y可能为0，而我们在处理时却把它认为是y了，因此我们只要减去y，就可以得到正确的结果了。

那些数会成为这样的y呢？自然就是x+1所有的因数。因此我们只要用类似筛法的方法计算出每个数的y的和，就可以递推了。

程序中由于因数1和x+1不方便计算，在递推时做了处理。

另外，由于本题的输出较多，使用了输出优化。

代码如下：

```c
#include <stdio.h>
typedef unsigned long long ull;
void out(ull);

char tmp[30];
unsigned long f[1000001]={0}; //这么大的数组，必须作为全局变量，否则爆栈
//本程序中的f[x]指x的所有大于1且小于x的因数之和

int main(void){
    int n,i,j,ndiv2;
    ull ans;

    scanf("%d",&n);
    ndiv2=(n>>1);
    
    for (i=2;i<=ndiv2;i++)
        for (j=(i<<1);j<=n;j+=i) //从2i开始,枚举2i, 3i, 4i, ...
            f[j]+=i;
    
    ans=n-1; //f(1)=n-1
    out(ans);
    for (i=2;i<=n;i++){
        ans=ans+n-1-f[i]-i; //f(x)=f(x-1)+n-所有的y之和
        out(ans);
    }
    return 0;
}

void out(ull x){
    int i=0;
    while (x){
        tmp[i++]=(x%10)+'0';
        x/=10;
    }
    for (i--;i>=0;i--)
        putchar(tmp[i]);
    putchar(' ');
}
```
另外说一句，这是我4月月赛R2 AC的唯一一题(而且交了3次)，还真的要提高知识水平啊！


---

## 作者：Prean (赞：1)

题面很直白，就不说了罢qaq

首先很明显，$ \sum_{i=1}^n x \bmod i = nx - \sum_{i=1}^n i\lfloor \frac x i \rfloor $

这道题要是直接求的话复杂度是不对的，而他让我们求 $ f(0) $ ~ $ f(n-1) $ 所有的值，所以考虑从 $ f(i) $ 得到 $ f(i+1) $
$$ f(i) - f(i-1) = n - \sum_{i=1}^ni(\lfloor \frac x i \rfloor -\lfloor \frac {x-1} i \rfloor) $$
对于后面的 $ \sum $ 分类讨论：

1. $ i|n $ 很明显多了一个 $ i $
2. 反正没有多

所以，后面的 $ \sum $ 相当于是 $ \sum_{d|x}d $，也就是 $ \sigma(x) $

所以就可以 $ O(n) $线性筛或 $ O(nlogn) $ 的暴力计算 $ \sigma $ 来解决此题啦！

由于自己太菜，不会线性筛 $ \sigma $，所以就只能写暴力啦

code：
```cpp
#include<cstdio>
const int M=1e6+5;
int n;
long long ans,sigma[M];
signed main(){
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		for(j=i;j<=n;j+=i){
			sigma[j]+=i;
		}
	}
	for(i=1;i<=n;++i){
		printf("%lld ",ans+=n-sigma[i]);
	}
}
```

---

## 作者：Caicz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/P3708)

------------
一道有趣的数学题。

#### 20pts
首先一看到本题，我们就以及有了一个 $O(n^2)$的暴力，则直接可以通过20pts的数据
#### 60/100pts
对于60pts，对于原式要求的
$$
f_n(x)=\sum_{i=1}^{n}{x\mod i} 
$$

我们可以轻松看出当 n 增加时对于每个$x<n$，我们都有
$$
	f_n(x)=f_{n-1}(x)+x
$$
于是我们可以得到
$$
f_n(x)=f_x(x)+(n-x)\times x
$$

但是问题来了，如何得到每一个$f_x(x)$?~~如果你是一个懒得推式子的人~~，通过打表我们可以发现以上规律，同时也可以发现对于所有的$f_x(x)$是无序的

于是我们只能从式子本身入手进行推导.

首先我们知道$\gcd(n,n-1)==1(n>2)$
同时我们观察式子
$$
\sum_{i=1}^{n}{n\mod i}\text{与}\sum_{i=1}^{n-1}{(n-1)\mod i}
$$

可以发现，对于 所有的 
$$
i\in1\to n-1\space\text{且}n-1\mod i=i-1
$$
**即 $n\mod i==0$ ，在 $f_{n-1}(n-1)$ 中贡献为 $i-1$ ，在$f_n(n)$ 中贡献为 $0$，同时对于所有不满足上述条件的 $i$ 在 $f_n(n)$ 中对答案的贡献都在比 $f_{n-1}(n-1)$ 多 $1$**

所以我们得出关于 $f_x(x)$ 的递推式为：
$$
f_n(n)=f_{n-1}(n-1)+n-1-\sum_{i=1}^{n-1}i(\text{if i|n})
$$
我们每次暴力查找符合条件的 $i$ ，复杂度为$O(n\sqrt n)$，只能通过60pts的数据

#### 100pts

对60pts的做法进行改进，我们提前预处理出 $3\to n$每个数的**因数和**.

这里我们可以暴力枚举因子$O(n\log n)$，也可以线筛$O(n)$预处理，这里不再累述
$$
\large\color{grey}{\text{Talk is cheap , show you the code}}
$$
```cpp
signed main(void)
{
	cin>>n;
	f[1]=0;
	for(register int i=2;i<=n;++i)
		for(register int j=0;j<=n;j+=i)
			num[j]+=i;
	for(register int i=2;i<=n;++i)
		f[i]=f[i-1]+2*i-1-num[i]-1;
	for(register int i=1;i<=n;++i)printf("%lld ",1ll*(n-i)*i+f[i]);
}
```



---

