# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13
```

### 输出

```
Full
2
```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13
```

### 输出

```
Full
1
```

## 样例 #3

### 输入

```
20 1
3 19
```

### 输出

```
Hungry
```

# 题解

## 作者：Kelin (赞：27)

### 题意:

有$2\times n$的时间去煎一块两面的肉

给你$k$个不相交时间区间$[l_i,r_i]$ 

你可以在这些区间的时间内任意次翻转这块肉

问是否存在合法的方案使得两面恰好都只煎了$n$分钟

求最少翻转次数

$n\le10^5,k\le100$ 

---
考虑暴力$DP,f_{i,j}$表示前$i$秒,没有被烤的那一面(简称为对面,另一面称正面)被烤了$j$秒的最少翻转次数

$f_{i,j}=f_{i-1,j}$不翻转,上一个状态对面还是只烤了$j$秒

$f_{i,j}=f_{i-1,i-j}+1$翻转,当前状态的正面是上一个状态的正面,总时间是$i,$当前对面烤了$j$秒,那么正面就烤了$i-j$秒

这个暴力显然是$O(n^2)$的,第二个转移只能在$[l,r]$内发生

---
可以发现$O(nk)$是可以过的,并且上一个$DP$中第一个转移几乎是没有用的,中间区间外的空挡是一路复制过去的

然后所有的区间又没有交集,设第$i$区间右端点是$r$,所以可以考虑这样一种$DP,f_{i,j}$表示前$r$秒,对面烤了$j$秒的最少翻转次数

然后我们可以想到,在一个区间里我们最多翻转两次,多的都可以转化为翻一次或者两次

#### 只翻一次

枚举一个时间$k$,表示翻转过后的正面多烤了$k$秒,$k\le r-l$

考虑$f_{i,j}$由什么转移过来

当前时间是$r$,那么当前正面就烤了$r-j$秒,因为多烤了$k$秒

所以翻转点正面就烤了$r-j-k$秒,又翻转之前当前正面是对面

$f_{i,j}=min\{f_{i-1,r-j-k}\}+1$

考虑用单调队列维护最优决策点$p=r-j-k$

当$k\gt r-l\Rightarrow p\lt r-j-(r-l)=l-j$时就不合法了,并且可以发现这个是要倒推的

#### 翻转两次

同样枚举一个时间$k$表示翻转之后的正面烤了$k$秒,$k\le r-l$

考虑到翻转两次相当于当前的对面翻过去多烤了$k$秒,然后又翻回来了

$\Rightarrow f_{i,j}=min\{f_{i-1,j-k}\}+2$

同样用单调队列维护最优决策点$p=j-k$

当$k\gt r-l\Rightarrow p\lt j-(r-l)$时就不合法了,并且可以发现这个是要顺推的

可以发现这个$DP$是可以滚动的,**注意数组大小**
```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
const int N=2e5+5,inf=1e9;
typedef int arr[N];
int n,k,p;arr q,f[2];
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n),sd(k);int l,r,h,t;
    f[0][0]=0;fp(i,1,n)f[0][i]=inf;
    while(k--){
    	sd(l),sd(r);p^=1;h=1,t=0;
    	memcpy(f[p],f[p^1],sizeof f[p]);
    	fp(j,0,min(n,r)){
    		while(h<=t&&f[p^1][j]<=f[p^1][q[t]])--t;
    		while(h<=t&&q[h]<j-(r-l))++h;q[++t]=j;
    		cmin(f[p][j],f[p^1][q[h]]+2);
    	}h=1,t=0;
    	fd(j,r,0){
    		while(h<=t&&f[p^1][r-j]<=f[p^1][q[t]])--t;
    		while(h<=t&&q[h]<l-j)++h;q[++t]=r-j;
    		cmin(f[p][j],f[p^1][q[h]]+1);
    	}
    }
    if(f[p][n]^inf)printf("Full\n%d",f[p][n]);
    else puts("Hungry");
return 0;
}
```

---

## 作者：yc20170111 (赞：20)

# \[ 动态规划·单调队列优化 \]

观察数据范围：$1 \leq n \leq 10^5,1 \leq K \leq 100$ , 不难发现，$O(nK)$ 的算法是可以过的。

考虑朴素DP：

设 $f[i][j]$ 表示前 $i$ 分钟，当前煎的是正面，**背面** 煎了 $j$ 分钟的最小翻面次数。

则有：
$$
f[i][j]=\min(f[i-1][j],f[i-1][j-1]+1) (i 属于某个 [l,r])
$$

$$
f[i][j]=f[i-1][j] (i 不属于任何一个 [l,r])
$$
不难发现，对于两个区间之间的 $i$ ，是可以直接跳过的。（背面煎的时间不变）

因此，令 $f[i][j]$ 表示前 $i$ 个区间，到 $r_i$ 时间，背面煎了 $j$ 分钟的最小翻面次数。

考虑在任意一个区间内，可以发现最多会翻两次面，分类讨论：

只翻一次面：

* 枚举在翻面前煎了 $k(k \leq r-l)$ 秒，则 $f[i][j]=\min(f[i-1][r-j-k]+1)$
* 即 $j+k$ 是上一轮背面（这翻面后正面）被煎的秒数。由于 $k \leq r-l$ 因此 $r-j-k \geq l-j$ ，可以维护单调队列。

翻两次面：
* 枚举煎了 $k(k\leq r-l)$ 秒后又翻回去，则 $f[i][j] = \min(f[i-1][j-k]+2)$ 
* 即 上一轮的背面到这一轮还是背面。由于 $k \leq r-l$ 因此 $j-k \geq j+l-r$ ，也可以用单调队列维护

观察到随着 $j$ 递增，翻一次面的决策点 $r-j-k$ 是递减的，翻两次面的决策点 $j-k$ 是递增的，因此，要分两次维护。

AC 代码
```cpp
#include<cstring>
#include<cstdio>
#define N 100010
#define INF 0x3f3f3f3f
#define Min(a,b) (a<b?a:b)

int h,t,q[N<<1];
int n,K,l,r,f[2][N<<1];

int main(){
	memset(f[0],0x3f,sizeof(f[0])); f[0][0]=0;
	
	scanf("%d%d",&n,&K);
	for(int i=1;i<=K;++i){
		scanf("%d%d",&l,&r);
		for(int j=0;j<=n;++j)
			f[i&1][j]=f[!(i&1)][j];
		h=1; t=0; //下面枚举的对应题解中 r-(j+k) 中 j+k 的值 
		for(int j=r;j>=0;--j){ 
			while(h<=t&&q[h]<l-j) ++h;
			while(h<=t&&f[!(i&1)][q[t]]>f[!(i&1)][r-j]) --t;
			q[++t]=r-j; f[i&1][j]=Min(f[i&1][j],f[!(i&1)][q[h]]+1); 
		}
		h=1; t=0; //下面枚举的对应题解中 j-k 的值
		for(int j=0,mj=Min(n,r);j<=mj;++j){ 
			while(h<=t&&q[h]<j-r+l) ++h;
			while(h<=t&&f[!(i&1)][q[t]]>f[!(i&1)][j]) --t;
			q[++t]=j; f[i&1][j]=Min(f[i&1][j],f[!(i&1)][q[h]]+2);
		}
	}
	if(f[K&1][n]==INF)printf("Hungry\n");
	else printf("Full\n%d\n",f[K&1][n]);
}
```

---

## 作者：leozhang (赞：6)

好神奇的dp...

首先有一个很简单的思想：设dp[i][j]表示目前到了第i分钟，朝上的面被烤了j分钟的情况下所需的最小交换次数

那么有转移：dp[i][j]=min(dp[i-1][j],dp[i-1][i-j]+1)

这一点很好理解，就是讨论现在向上这面上一分钟的状态：如果上一分钟这一面也朝上，那么就直接继承，如果上一分钟这一面朝下，那么就要翻一次，同时之前朝上的面的被烤的时间就是i-j

但这个转移显然是O（n^2）的，这样做过不去这道题。

所以我们考虑优化

可是，这个转移在某种意义上已经达到了最优，所以不太好优化了...

那么我们只能重构状态

我们发现，能对肉进行翻面的时间只有这k个给定的时间段，且k<=100，那么我们考虑：能否把一个时间段整体更新，将时间复杂度降成O（nk）呢？

这样我们必须重新设计状态：记状态dp[i][j]表示目前到了第i个时间段的结尾，朝上这一面的肉被烤的时间为j

那么我们就要重新考虑转移：

首先我们观察一下规律：

可以发现：在一段可以翻转的区间内，真正翻转的次数只可能有0,1或2三种，所以我们只需按这三种情况分别讨论转移即可

（关于上面这句话的解释：如果你翻转了三次或更多，那么你一定可以将某几次翻转合并后变成上述情况，也就是说上述情况就足够覆盖所有状态）

翻转次数为0的情况很好判断，直接继承上一次的状态即可

如果翻转次数为2，那么这相当于原来朝上的面现在还朝上，原来朝下的面现在还朝下，只是中途把朝上的面翻过去烤了一下而已。

那么我们可以枚举在之前朝上的面在这一段时间内被烤的时间k，那么在这段区间之前这一面被烤的之间就是j-k

于是可以进行转移：dp[i][j]=min(dp[i-1][j-k]+2)

但是这样做显然时间不够优越，所以我们要采取策略来优化！

我们推一发式子，发现可以用单调队列维护。

从小向大枚举j，然后推进单调队列中维护即可

至于翻转次数为1的情况，相当于现在朝上的面原先朝下，那么如果现在朝上的面被烤的时间为j，枚举现在朝下的面在这一区间内被烤的时间为k，那么r-j就是现在朝下的面被烤的时间，而我们枚举了朝下的面在这一区间内被烤的时间为k，那么在进入这一区间之前现在朝下的面原来朝上，已经被烤过的时间就是r-j-k！

这样有转移：dp[i][j]=min(dp[i-1][r-j-k])+1!

用类似上述的方法，同样构造单调队列转移，注意此时要倒序枚举，因为我们枚举的东西事实上起到的是j+k的作用，所以r-枚举的东西就要倒序

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int dp[2][1000005];
int que[1000005];
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	int now=1,past=0;
	memset(dp[past],0x3f,sizeof(dp[past]));
	dp[0][0]=0;
	while(k--)
	{
		memcpy(dp[now],dp[past],sizeof(dp[now]));
		int l,r;
		scanf("%d%d",&l,&r);
		int head=1,tail=0;
		for(int i=0;i<=min(n,r);i++)
		{
			while(head<=tail&&dp[past][que[tail]]>=dp[past][i])
			{
				tail--;
			}
			que[++tail]=i;
			while(head<=tail&&que[head]<i-(r-l))
			{
				head++;
			}
			dp[now][i]=min(dp[now][i],dp[past][que[head]]+2);
		}
		head=1,tail=0;
		for(int i=r;i>=0;i--)
		{
			while(head<=tail&&dp[past][que[tail]]>=dp[past][r-i])
			{
				tail--;
			}
			while(head<=tail&&que[head]<l-i)
			{
				head++;
			}
			que[++tail]=r-i;
			dp[now][i]=min(dp[now][i],dp[past][que[head]]+1);
		}
		swap(now,past);
	}
	if(dp[past][n]>=0x3f3f3f3f)
	{
		printf("Hungry\n");
	}else
	{
		printf("Full\n%d\n",dp[past][n]);
	}
	return 0;
} 

```

---

## 作者：「QQ红包」 (赞：6)

我的[博客](http://redbag.pw/)

[更好的阅读体验](http://redbag.pw/2018/02/25/939F-Cutlet-dp/)

考虑暴力，
$dp_{i,j} $
 表示前$ i $秒，当前没在烤的面被烤过$j$
秒，所需要的最少的翻面次数。

很显然 

$$
dp_{i,j}=\min(dp_{i−1,j},dp_{i−1,j−1}+1)
$$
 
然而这个肯定会T掉。
不过很容易发现，只有
k段
$dp_{i,j}$ 能从
$ dp_{i−1,j−1}$  转移，于是我们可以优化。

$ f_{i,j} $
表示在第 $ R_i $
秒，目前没在烤的面烤了
$ j $秒，需要翻面的最小次数
$f_{i,j}=min(f_{i−1,j−k})+2 (0≤k≤ri−li)$

翻过去烤k秒再翻回来

$f_{i,j}=min(f_{i−1,ri−j−k})+1    (0≤k≤ri−li) $

当前面烤了
$r_{i}−j$
 秒，相当于某个时刻翻过来继续烤了
k
秒。
然后可以用单调队列优化（单调队列维护最值，见[另一篇文章](http://redbag.pw/2017/12/03/USACO12MAR-花盆Flowerpot-单调队列-二分/)）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void qmax(int &x,int y) {if (x<y) x=y;}
void qmin(int &x,int y) {if (x>y) x=y;}
inline int read()
{
    char s;
    int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(isdigit(s)));
    if(s==EOF)exit(0);
    if(s=='-')base=-1,s=getchar();
    while(isdigit(s)){k=k*10+(s^'0');s=getchar();}
    return k*base;
}
inline void write(int x)
{
    static char cnt,num[15];cnt=0;
    if (!x)
    {
        putchar('0');
        return;
    }
    for (;x;x/=10) num[++cnt]=x%10;
    for (;cnt;putchar(num[cnt--]+48));
}
const int maxn=2e5+10;
const int maxk=110;
int n,k;
int L[maxk],R[maxk];
int dp[maxk][maxn];
struct node
{
    int l,r;
    int q[maxn];
    void clean()
    {
        l=1;r=0;
        memset(q,0,sizeof(q));
    }
    void insert(int x,int y)
    {
        while (l<=r&&dp[x][q[r]]>=dp[x][y]) r--;
        r++;q[r]=y;
    }
} a,b;
int main()
{
    n=read();k=read();
    for (int i=1;i<=k;i++) L[i]=read(),R[i]=read();
    memset(dp,0x3f3f3f3f,sizeof(dp));
    dp[0][0]=0;
    for (int i=1;i<=k;i++)
    {
        a.clean();
        for (int j=0;j<=n;j++) dp[i][j]=dp[i-1][j];
        for (int j=0;j<=n;j++)
        {
            a.insert(i-1,j);
            while (a.l<=a.r&&a.q[a.l]<j-R[i]+L[i]) a.l++;
            qmin(dp[i][j],dp[i-1][a.q[a.l]]+2);
        }
        b.clean();
        int Min=max(R[i]-n,0);
        int l1=L[i]+1,r1=R[i]+1;
        for (int j=R[i];j>L[i];j--) b.insert(i-1,j);
        for (int j=0;j<=n;j++)
        {
            l1--;
            r1--;
            while (b.l<=b.r&&b.q[b.l]>r1) b.l++;
            if (l1>=0) b.insert(i-1,l1);
            if (b.l<=b.r) qmin(dp[i][j],dp[i-1][b.q[b.l]]+1);
        }
    }
    if (dp[k][n]<=2333) printf("Full\n%d\n",dp[k][n]);
    else printf("Hungry");
    return 0;
}
```

---

## 作者：Wu_Qi_Tengteng (赞：3)

一开始想的是设 $f_{i,j}$ 表示前 $i$ 秒，当前面烤了 $j$ 秒的最少反转次数。那么有转移：
$$
f_{i,j}=\min \{f_{i-1,j-1},f_{i-1,i-j}+1\}
$$
但是这东西没有什么前途啊。

我们发现这些区间中有很多的间隔，而在这些间隔中另一面烤的时间是一直不变的。也就是说随着烤的时间增加，翻面的次数也是不变的。我们想将中间这些无效转移直接跳过。

所以我们不妨换一种状态，设 $f_{i,j}$ 表示到了第 $i$ 秒，背面烤了 $j$ 秒的最少反转次数。转移：
$$
f_{i,j}=\min\{f_{i-1,j},f_{i-1,i-j}+1\}
$$
这个时候区间之外的状态就不需要了，所以我们只需要知道上一个区间的最后一秒的状态就可以转移了。

所以再优化一下状态，设 $f_{i,j}$ 表示到了第 $r_i$ 秒，背面烤了 $j$ 秒的最少反转次数。

但是这个时候我们还需要考虑区间内的转移，还是不太能优化。我们再观察，发现一个区加内最多只能反转两次，那么分讨一下：

**翻转一次：**

枚举一个 $k$ 表示我这一面在之前被烤的时间，那么有：
$$
f_{i,j}=\min^{r_i-j}_{k=-j+l_i} \{f_{i-1,k}+1\}
$$
来看看这道题转移点 $k$ 的范围。我们发现当 $j$ 变大的时候转移区间是整体左移了一格的，那么这个就可以用单调队列来优化了。

**翻转两次：**

枚举一个 $k$ 表示当前的背面在之前被烤的时间，那么有：
$$
f_{i,j}=\min_{k=j-r_i+l_i}^{j-1}\{f_{i-1,k}+2\}
$$
而这个显然也可以用单调队列优化。

那么总时间复杂度就是 $\mathcal{O}(nm)$。

[code](https://codeforces.com/contest/939/submission/290548983)

---

## 作者：hstt (赞：3)

设 $f_{i,j}$ 表示在第 $i$ 秒末，**朝上的一面**煎了 $j$ 秒的最少翻转次数。

由于不能翻转的部分，**朝上的一面**煎的时间不会变化，不会对 $f$ 造成影响，所以重新设 $f_{i,j}$ 表示在第 $r_i$ 秒末，**朝上的一面**煎了 $j$ 秒的最少翻转次数。

注意到在每个 $[l_i,r_i]$ 内，最多翻转 $2$ 次。

**翻转 $0$ 次的情况**：

$$f_{i,j}=f_{i-1,j}$$

**翻转 $1$ 次的情况**：

$$f_{i,j}=\min\{f_{i-1,r_i-j-k}\}+1,0 \leq k\leq r_i-l_i$$

对于每个 $j$，能转移到它的 $f_{i-1}$ 的区间是 $[r_i-j-(r_i-l_i),r_i-j]$，也就是 $[l_i-j,r_i-j]$。

这让我们想起了[滑动窗口](https://www.luogu.com.cn/problem/P1886)，随着 $j$ 的增大窗口向左滑动，我们可以写一个单调队列。

**翻转 $2$ 次的情况**：

$$f_{i,j}=\min\{f_{i-1,j-k}\}+2,0 \leq k\leq r_i-l_i$$

对于每个 $j$，能转移到它的 $f_{i-1}$ 的区间是 $[j-(r_i-l_i),j]$，也就是 $[j-r_i+l_i,j]$。

随着 $j$ 的增大窗口向右移动，我们再写一个单调队列。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,K=105,INF=0x3f3f3f3f;
int n,k;
int f[2][N<<1];
int q[N<<1],h,t;
int main() {
    scanf("%d%d",&n,&k);
    memset(f[0],0x3f,sizeof f[0]);
    f[0][0]=0;
    int L=0,l,r;
    for(int i=1;i<=k;i++) {
        L^=1;
        scanf("%d%d",&l,&r);
        //翻转 0 次
        for(int j=0;j<=n*2;j++) f[L][j]=f[L^1][j];
        //翻转 1 次
        h=1,t=0;
        //因为 j=0 从 [l,r] 转移，先加入一部分
        for(int j=r;j>l;j--) q[++t]=j;
        for(int j=0;j<=r;j++) {
            while(h<=t&&q[h]>r-j) ++h;
            if(j<=l) {
                while(h<=t&&f[L^1][q[t]]>=f[L^1][l-j]) --t;
                q[++t]=l-j;
            }
            f[L][j]=min(f[L][j],f[L^1][q[h]]+1);
        }
        //翻转 2 次
        h=1,t=0;
        for(int j=0;j<=r;j++) {
            while(h<=t&&q[h]<j-r+l) ++h;
            while(h<=t&&f[L^1][q[t]]>=f[L^1][j]) --t;
            q[++t]=j;
            f[L][j]=min(f[L][j],f[L^1][q[h]]+2);
        }
    }
    if(f[L][n]==INF) printf("Hungry");
    else printf("Full\n%d",f[L][n]);
    return 0;
}
```

---

## 作者：Kx_Triumphs (赞：3)

### 前置

单调队列（没学过或忘了点[这里](https://www.luogu.com.cn/problem/P1886)）

### 简化题意

有一块牛排，要求对它烹饪 $2n$ 秒，可在给定的 $k$ 个时间段中将它翻转任意次，使得牛排两面都受到了 $n$ 秒的烹饪。

### 状态设计

- 可以发现当总共煮了 $i$ 秒，其中一面如果煮了 $j$ 秒，自然可以求出另一面为 $i-j$ 秒，所以我们可以设状态为 前 $i$ 秒没在烤的面煮了 $j$ 秒的最小翻转次数，但由于时间 $n$ 最大为 $10^5$ ，所以这个状态必然是 **开不下** 的。

- 不过，可以发现题目要求必须在 **给定的 $k$ 个区间内才能翻转** ，所以可以以每个区间作为一个状态。设 $dp_{i,j}$ 表示第 $i$ 个区间结束时，没烤的面煮了 $j$ 秒的最小翻转次数。最终答案为 $dp_{k,n}$ 。

### 转移

考虑有哪些情况会构成转移：

- 一种情况是不翻转，这时没煮的面煮的 **时间没有增加** ，所以直接继承上一个区间的状态。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/amv97dbk.png)

  则转移方程为 $dp_{z,j}=dp_{z-1,j}$ 。

- 考虑在一个区间内翻转多次（钦定每次翻转都在 $z-1$ 区间结束后）：

  - 如图所示，翻转很多次可以转换为翻转 **一次** 或翻转 **两次** 的情况。（附：每个区间 $z-1$ 到下一个区间 $z$ 都看作在区间 $z-1$ 结束时 **立刻翻转** ）

    - 翻转 **一次** ：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/bc8txqfa.png)

    1. 由图，可以得出转移 $dp_{z,j} = \min ( dp_{z-1,i-j-k} ) +1$ 。

    2. 因为只能在区间 $r_z$ 至 $l_z$ 之内翻转，且结束时间为 $r_{z}$ ，所以 $( r_{z}-k \ge l_{z} ) \to ( 0\le k\le r_{z}-l_{z}) $ ，并且满足 $( r_{z} -  j - k \ge l_{z} )$ 。

    3. 至于 $j$ ，我们可以发现蓝色的枚举范围 $( 0 \le j \le r_{z} ) $ ，但如果再算上 $k$ ，且两者都取最大值，那么 $i-j-k$ 很可能会得到负数，造成越界，所以想用 **暴力** 拿部分分也是较为 **困难** 的。

    4. 因为所设状态为 **区间结束时间** ，所以 $i$ 无需枚举，为 $r_z$ ，方程则变为 $ dp_{z,j} = \min \limits_{ 0 \le k \le r_{z} - l_{z} } ( dp_{ z-1,r_{z}-j-k } )+1$ 。

    - 翻转 **两次** ：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/9mkyaak9.png)

    1. 由图，可以得出转移 $ dp_{z,j} = \min ( dp_{z-1,j-q} )+2 $ ，同上 $({ 0 \le q \le r_{z} - l_{z} })$ ，且满足 $( l_{z} \le j-q \le r_{z} )$ 。

       

  则所有 **转移方程** 如下(为了方便这里 $i$ 为第 $i$ 个区间)：

  $$
  dp_{i,j}=\begin{cases}dp_{i-1,j}&{0\le j\le r_{i}}\\ 
  \min(dp_{i-1,r_{i}-j-k})+1&{0\le k\le r_{i}-l_{i}}\\ 
  \min{(dp_{i-1,j-q})+2}&{0\le q\le r_{i}-l_{i}}\end{cases}
  $$

### 优化

- 在分析翻转 **一次** 的方程时，我们发现用暴力跑 $dp$ 是会越界的，且 $( 0 \le n \le 10^5 )$ ,且枚举 $j$ 与 $k$ 也会 **$TLE$** 。那么，怎么办呢？
- 根据翻转 **一次** 和 **两次** 的方程中，我们可以发现，每当枚举到一个新的值，都会和原来的值取更小值，最终会取得这一区间内的最小值。每次更新，都会更新更小值，这是符合 **单调性** 的，所以可以使用 **单调队列** 进行优化。
- 由于变成在一个范围内取最小值，所以 $k$ 和 $q$ 取 **最大**范围 $r_{i}-l_{i}$ 。
- 具体的，我们可以将翻转 **一次** 的方程看作在 $ dp_{ i-1,r_{i}-j-k } $ 到 $dp_{ i-1,r_{i} }$ 之间取最小值，将翻转 **两次** 的方程看作在 $ dp_{i-1,j-q} $ 到 $ dp_{i-1,j} $ 之间取最小值(这里 $ r_{i}-j-k $ 化简后为 $ l_{i}-j $ ，它作为 **出队条件** ，所以不用担心越界)。
- 则最终方程如下：

$$
dp_{i,j} = \begin {cases} dp_{i-1,j} & { 0 \le j \le r_{i} } \\ 
 \min ( dp_{i-1,r_{i}-j-k})+1 \to \min (dp_{ i-1,r_{i}-j-(r_{i}-l_{i}) })+1 \to \min (dp_{ i-1,l_{i}-j })+1&{ 0 \le j \le r_{i} } \\ 
 \min ( dp_{i-1,j-q} )+2 \to \min (dp_{ i-1,j-(r_{i}-l_{i}) })+2 \to \min (dp_{ i-1,j-r_{i}+l_{i} })+2&{ 0 \le j \le r_{i} } \end {cases}
$$

到了这，这题就解完了，欢迎指出题解中错误，如需代码也可以私我。

---

## 作者：Register_int (赞：3)

喵喵题。

显然正面与反面是对称的，所以我们把肉翻面，相当于将肉的正反面交换（废话）。这就说明我们可以钦定 **煎的永远是正面**。

设 $dp_{i,j}$ 为考虑了前 $i$ 个区间，前 $r_i$ 秒中 **反面** 煎了 $j$ 秒的最小代价。任意一个区间内，肉最多被翻两次。对于翻一次的情况：

- 枚举之前反面煎了 $k$ 秒，在第 $j$ 秒翻面。此时正反面交换，因此总共煎了 $j$ 秒，反面（即原先的正面）煎了 $j-k$ 秒。有转移：

$$dp_{i,j-k}\to\min(dp_{i,j-k},dp_{i-1,k}+1)$$

对于翻两次的情况：

- 枚举之前反面煎了 $k$ 秒，翻两次面后反面多煎了 $j$ 秒。此时正反面不变，因此反面煎了 $j+k$ 秒。有转移：

$$dp_{i,j+k}\to\min(dp_{i,j+k},dp_{i-1,k}+2)$$

事实上可以枚举现在反面煎的秒数，两个转移可以整合成：

$$dp_{i,k}\to\min_{l_i\le j\le r_i}(dp_{i,k},dp_{i-1,j-k}+1)$$
$$dp_{i,k}\to\min_{0\le j\le r_i-l_i}(dp_{i,k},dp_{i-1,k-j}+2)$$

也即：

$$dp_{i,k}\to\min_{l_i-k\le j\le r_i-k}(dp_{i,k},dp_{i-1,j}+1)$$
$$dp_{i,r_i-k}\to\min_{l_i-k\le j\le r_i-k}(dp_{i,r_i-k},dp_{i-1,j}+2)$$

然后你会发现对于同一个 $k$ 这俩转移的是固定的区间，并且左右端点都单调递减。上个单调队列就没了。第一位滚掉，时间复杂度 $O(nm)$。

代码里为了方便把整个枚举方向倒过来了。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, l[MAXN], r[MAXN];

int dp[MAXN], f[MAXN]; deque<int> q;

int main() {
	scanf("%d%d", &n, &m), memset(dp, 0x3f, sizeof dp), *dp = 0;
	for (int i = 1; i <= m; i++) scanf("%d%d", &l[i], &r[i]);
	for (int i = 1; i <= m; i++) {
	    q.clear();
		for (int j = 0; j <= n; j++) f[j] = dp[j];
		for (int k = 0; k <= r[i]; k++) {
			for (; !q.empty() && q[0] < k - r[i] + l[i]; q.pop_front());
			for (; !q.empty() && dp[q.back()] >= dp[k]; q.pop_back());
			q.push_back(k), f[k] = min(f[k], dp[q[0]] + 2);
			f[r[i] - k] = min(f[r[i] - k], dp[q[0]] + 1);
		}
		for (int j = 0; j <= n; j++) dp[j] = f[j];
	}
	if (dp[n] <= 1e9) printf("Full\n%d", dp[n]);
	else puts("Hungry");
}
```

---

## 作者：lmgoat (赞：3)

因为只有那 $k$ 个区间是有用的，而且 $O(nk)$ 能过，所以设 $f[i][j]$ 表示已经经过了前 $i$ 个可以翻转的区间，背面已经煎了 $j$ 秒（当前在煎的区间是正面，另一面是背面）。设背面的时间是因为方便转移，而且这样的话答案就是 $f[k][n]$。

同一个区间内最多翻转两次。因为我们只关心两个事情：两面各煎了多久和进这个区间时与出这个区间时相比有没有翻面，所以翻一次和翻两次就能包含所有情况。

在一个区间内有三种情况：

不翻转：$f[i][j]=f[i-1][j]$。因为一直在煎正面，所以背面的时间不变。

翻一次：$f[i][j]=\min_{0\le k\le r[i]-l[i]}\{f[i-1][r[i]-j-k]\}+1$。枚举的 $k$ 是翻转后煎的时间。因为翻转了一次，上个区间的背面就是当前区间的正面。当前的总时间减去当前背面再减去当前区间新煎的正面的时间就是上个区间的背面的时间。

翻两次：$f[i][j]=\min_{0\le k \le r[i]-l[i]}\{f[i-1][j-k]\}+2$。枚举的 $k$ 是两次翻转之间煎的时间。

发现 $f[i][j]$ 只会从 $f[i-1][k]$ 转移过来（此时 $k$ 没有意义，只是单纯作为一个变量），所以可以滚动数组。

考虑用单调队列优化翻一次和翻两次的转移，对于两种状态分别维护不同的单调队列。

翻一次：因为 $0\le k\le r[i]-l[i]$，所以 $l[i]-j \le r[i]-j-k\le r[i]-j$。$l[i]-j$ 和 $r[i]-j$ 都随 $j$ 的增大而单调递减。所以在单调队列中维护 $j$ 下标递减，$f[i-1][j]$ 单调递增。

翻两次：因为 $0\le k\le r[i]-l[i]$，所以 $j+l[i]-r[i] \le j-k\le j$。$j+l[i]-r[i]$ 和 $j$ 都随 $j$ 的增大而单调递增。所以在单调队列中维护 $j$ 下标递增，$f[i-1][j]$ 单调递增。

```cpp
#include <bits/stdc++.h>
using namespace std;
int read() {
	int x(0),f(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=100005,K=105;
int n,k,l[K],r[K],l1,r1,l2,r2,q1[N*2],q2[N*2],f[2][N*2],inf;
signed main() {
	n=read(),k=read();
	for(int i=1;i<=k;++i) l[i]=read(),r[i]=read();
	memset(f,0x3f,sizeof f),inf=f[0][0];
	f[0][0]=0;
	int now=0,lst=1;
	for(int i=1;i<=k;++i) {
		now^=1,lst^=1;
		l1=l2=r2=1,r1=0;
		for(int j=r[i];j>=l[i];--j) {
			while(l1<=r1&&f[lst][j]<f[lst][q1[r1]]) --r1;
			q1[++r1]=j;
		}
		for(int j=0;j<=r[i];++j) {
			f[now][j]=f[lst][j];
			while(l1<r1&&q1[l1]>r[i]-j) ++l1;
			f[now][j]=min(f[now][j],f[lst][q1[l1]]+1);
			if(j!=r[i]&&l[i]-j-1>=0) {
				while(l1<=r1&&f[lst][l[i]-j-1]<f[lst][q1[r1]]) --r1;
				q1[++r1]=l[i]-j-1;
			}
			while(l2<r2&&q2[l2]<j-r[i]+l[i]) ++l2;
			f[now][j]=min(f[now][j],f[lst][q2[l2]]+2);
			if(j!=r[i]) {
				while(l2<=r2&&f[lst][j+1]<f[lst][q2[r2]]) --r2;
				q2[++r2]=j+1;
			}
		}
	}
	if(f[now][n]>=inf) puts("Hungry");
	else printf("Full\n%d",f[now][n]);
	return 0;
}
```

---

## 作者：A1443356159 (赞：2)

# CF939F Cutlet题解

这个状态设计得有点博弈论dp得滋味。

设 $dp_{i,j}$ 表示经过了 $i$ 秒，当前朝上的那一面煎了 $j$ 秒所需要的最少翻的次数。 

首先有一个很好推的dp式子。

$dp_{i,j}=min(dp_{i-1,j},dp_{i-1,i-j})$，$i$ 别任意一个区间包含。

$dp_{i,j}=dp_{i-1,j}$ ，$i$ 不被任意一个区间包含。

这是 $O(n^2)$ 显然不行。

注意到 $k$ 很小，而且当一个位置没有被任意一个区间包含时 $dp$ 结果是直接继承的。

先说一个很显然的结论，对于任意一个区间，最多翻2次（大于两次可以用2次替换）。

我们重新设计状态 $dp_{i,j}$ 表示在第 $r_i$ 秒，当前正面朝上的那一面煎了 $j$ 秒需要的最少翻的次数。

分类讨论，

+ 第 $i$ 个区间翻了0次，$dp_{i,j}=dp_{i-1,j}$，没什么好说的。

+ 第 $i$ 个区间翻了2次，我们枚举翻了两次后朝上那面多煎了 $k$ 秒，因为翻了两次后，朝上的那一面还是朝上的那一面，所以

$dp_{i,j}=min(dp_{i,j},dp_{i-1,j-k}+2)$，因为 $0\le k\le r_i-l_i$，我们枚举 $j$ 问题转化为 $dp_{i-1,j}$ ~ $dp_{i-1,j-r_i+l_i}$ 的最小值，可以用单调队列优化。

+ 第 $i$ 个区间翻了1次，枚举翻了一次后朝下的那面多煎了 $k$ 秒，翻了一次后，朝下的那面就是翻之前朝上的那一面，所以

$dp_{i,j}=min(dp_{i,j},dp_{i-1,r_i-j-k}+1)$，$0\leq k\le r_i-l_i$，同样是枚举 $j$ 问题转化为 $dp_{i-1,r_i-j}$ ~ $dp_{i-1,r_i-j-(r_i-l_i)}$的最小值 ，还是可以用单调队列优化。

其实上述2，3情况中的 $k$ 应该是满足 $k\ge1$ 的，但由于当 $k=0$ 时肯定不会更新答案（第一情况就算了更好的），所以为了方便就当 $k\ge0$。

```cpp
#include<stdio.h>
#include<cstring> 
using namespace std;
const int N=2e5+5;
int read() {
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int n,l[N],r[N],dp[2][N],K,q[N],t,w;//dp[i]表示当前朝上的那面煎了iS最小花费
int min(int x,int y){return x<y?x:y;}
int main() {
	n=read();K=read();
	for(int i=1;i<=K;++i) {
		l[i]=read();
		r[i]=read();
	}
	memset(dp,0x3f,sizeof(dp));
	int p=0;
	dp[p][0]=0;
	for(int i=1;i<=K;++i) {
		p^=1;
		memset(dp[p],0x3f,sizeof(dp[p]));
		for(int j=0;j<=min(r[i],n);++j)dp[p][j]=dp[p^1][j]; 
		//没翻 
		t=1;w=0;
		//翻两次 
		for(int j=0;j<=min(r[i],n);++j) {
			while(t<=w&&dp[p^1][j]<=dp[p^1][q[w]])--w;
			while(t<=w&&q[t]<j-r[i]+l[i])++t;
			q[++w]=j;
			dp[p][j]=min(dp[p][j],dp[p^1][q[t]]+2);
		}
		t=1;w=0;
        //翻一次
		for(int j=r[i];j>=0;--j) {//注意这里能写j=min(r[i],n)，因为要将之前的东西加入单调队列
			while(t<=w&&dp[p^1][r[i]-j]<=dp[p^1][q[w]])--w;
			while(t<=w&&q[t]<l[i]-j)++t;
			q[++w]=r[i]-j;
			dp[p][j]=min(dp[p][j],dp[p^1][q[t]]+1);
		}
	}
	if(dp[p][n]<1e9)printf("Full\n%d",dp[p][n]);
	else printf("Hungry");
	return 0;
}
```



---

## 作者：Eltaos_xingyu (赞：1)

比较好的一道 DP 题。

不难发现暴力转移：设 $dp_{i,j,k}$ 是第 $i$ 个时刻最开始朝上那一面煎了 $j$ 秒，目前正在煎第 $k$ 面。当 $i\in[l_p,r_p]$ 时有转移：
$$
dp_{i,j,0}=\min(dp_{i-1,j-1,0},dp_{i-1,j,1}+1)
$$
$$
dp_{i,j,1}=\min(dp_{i-1,j,1},dp_{i-1,j-1,0}+1)
$$
考虑优化这个 DP。

首先，后面的 $j,k$ 可以压成只有 $j$。状态为目前朝上的一面煎了 $j$ 秒。由于 $O(nk)$ 的复杂度可过，我们就把第一个状态 $i$ 改成 $O(k)$ 级别的，于是设 $dp_{i,j}$ 为第 $i$ 个区间的右端点时朝上的一面已经煎了 $j$ 秒的最小翻转次数。

显然，一个区间有三种选择，即翻转 $0,1,2$ 次，这里分开讨论。

- 当翻转 $0$ 次时，正面朝上的那面被煎秒数不变，有：

$$
dp_{i,j}\leftarrow dp_{i-1,j}
$$

- 当翻转 $1$ 次时，我们把之前煎的过程抽象成先煎了 $j'$ 秒目前朝上的一面，然后一直煎现在煎的这一面，然后在当前区间转回去了。设转回去一共 $k$ 秒，那么有 $dp_{i,r_i-(j'+k)}\leftarrow dp_{i,j'}+1$，令 $j=r_i-(j'+k)$，那么有 $j'=r_i-j-k$，有如下转移：

$$
dp_{i,j}\leftarrow dp_{i-1,r_i-j-k}+1(0\leq k \leq r_i-l_i)
$$

- 当翻转 $2$ 次时，同样将之前煎的过程抽象成先煎了 $j'$ 秒目前朝上的一面，那么翻转两次等同于朝上的一面不变，那么有 $dp_{i,j'+k}\leftarrow dp_{i-1,j'}+2$。令 $j=j'+k$，那么有转移：

$$
dp_{i,j}\leftarrow dp_{i-1,j-k}+2(0\leq k\leq r_i-l_i)
$$

对于翻转一次时，由于 $r_i-j-k\leq r_{i-1}$，那么就有 $j+k\geq r_i-r_{i-1}$。而 $k\leq r_i-l_i$，所以有 $j\geq l_i-r_{i-1}$。然后我们就直接讨论最极端情况 $j=0$，我们发现 $r_i-j-(r_i-l_i)=l_i>r_{i-1}$，此时 $dp_{i-1,r_i-k}$ 一定是 $+\infty$。其他情况手推也可发现直接计算是对答案没有影响的。

那么直接上单调队列优化 DP 即可。

```cpp
// Problem: F. Cutlet
// Contest: Codeforces - Codeforces Round 464 (Div. 2)
// URL: https://codeforces.com/problemset/problem/939/F
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Start coding at 2024-01-22 16:32:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,k;
int l,r;
int dp[101][200005];
deque<int> q;
void clear(){
	while(!q.empty())q.pop_back();
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=2*n;i++)dp[0][i]=1e9;
	dp[0][0]=0;
	for(int i=1;i<=k;i++){
		cin>>l>>r;
		clear();
		for(int j=0;j<=2*n;j++)dp[i][j]=dp[i-1][j];
		//change 2 times
		q.push_back(0);
		int len=r-l;
		for(int j=1;j<=r;j++){
			if(!q.empty()&&q.front()<j-len)q.pop_front();
			while(!q.empty()&&dp[i-1][q.back()]>dp[i-1][j])q.pop_back();
			q.push_back(j);
			dp[i][j]=min(dp[i][j],dp[i-1][q.front()]+2);
		}
		clear();
		//change 1 time
		for(int ri_j=0;ri_j<=r;ri_j++){
			int j=r-ri_j;
			if(!q.empty()&&q.front()<ri_j-len)q.pop_front();
			while(!q.empty()&&dp[i-1][q.back()]>dp[i-1][ri_j])q.pop_back();
			q.push_back(ri_j);
			dp[i][j]=min(dp[i][j],dp[i-1][q.front()]+1);
		}
	}
	if(dp[k][n]>=1e9)cout<<"Hungry";
	else cout<<"Full\n"<<dp[k][n];
	return 0;
}
```



---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF939F)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难看出是$dp$题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一个非常粗暴的$dp$是很好想出来的：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i,j,0/1)$：第$i$秒后，第$i+1$前，正面（规定有一面是正面，有一面是背面，并且总是从正面开始煎）已经煎了$j$秒，第$i+1$秒将要煎正面/反面的最小翻动次数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移：  
$$f(i,j,0)=\begin{cases}\min\{f(i-1,j-1,0),f(i-1,j,1)+1\}&\exists k,s.t.l_k\le i\le r_k\\
f(i-1,j-1,0)&otherwise\end{cases}$$  
$$f(i,j,1)=\begin{cases}\min\{f(i-1,j,1),f(i-1,j-1,0)+1\}&\exists k,s.t.l_k\le i\le r_k\\f(i-1,j,1)&otherwise\end{cases}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这样做的时间是$O(n^2)$的，无法再优化（状态便是$O(n^2)$，并且不存在特殊的区间更新方式）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面考虑修改状态。根据题意，实际上在每个区间里面人最多会翻动两次（两次以上的话就可以用两次以下的翻动等效替代）。所以我们可以在每个区间结束后计算答案，于是有了新的状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$g(i,j,0/1)$：区间$i$结束后，$r_i+1$秒前，正面煎了$j$秒，$r_i+1$秒要煎正面/反面的最小翻动次数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移比较复杂，分不翻，翻一次，翻两次的情况讨论。但是实际上，如果理解了上面转移其实并不难推，所以姑且~~偷懒~~略过。如果实在推不出来转移就请看正解代码前面的朴素转移的代码。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;朴素的转移是$O(kn^2)$。~~虽然比暴力还慢，~~ 其状态只有$O(kn)$，所以考虑优化转移。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难发现对于每一种转移，它决策点是一段区间，并且区间在从小到大枚举$j$的时候左端点不会左移。所以不难想到用单调队列优化转移。时间就降到了$O(kn)$。  
# 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;朴素的$O(kn^2)$转移：  
```cpp
	//pre记录g(i-1)，nxt记录g(i)
	for( int i = 1 ; i <= K ; i ++ )
	{
		for( int j = 0 ; j <= N ; j ++ ) nxt[j][0] = INF, nxt[j][1] = pre[j][1];
		for( int j = r[i] - r[i - 1] ; j <= N ; j ++ ) nxt[j][0] = pre[j - ( r[i] - r[i - 1] )][0];
		//不翻 
		for( int j = 0 ; j <= N ; j ++ )
			for( int k = MAX( l[i], r[i] - j ) ; k <= r[i] ; k ++ )
				nxt[j][0] = MIN( nxt[j][0], pre[j - r[i] + k][1] + 1 );
		for( int j = 0 ; j <= N ; j ++ )
			for( int k = l[i] ; k <= MIN( r[i], j + r[i - 1] ) ; k ++ )
				nxt[j][1] = MIN( nxt[j][1], pre[j - k + r[i - 1]][0] + 1 );
		//翻一次
		for( int j = 0 ; j <= N ; j ++ )
			for( int k = MAX( l[i] + 1, l[i] - r[i - 1] + r[i] - j ) ; k <= r[i] ; k ++ )
				nxt[j][0] = MIN( nxt[j][0], pre[j - r[i] + k - l[i] + r[i - 1]][0] + 2 );
		for( int j = 0 ; j <= N ; j ++ )
			for( int k = l[i] + 1 ; k <= MIN( r[i], j + l[i] ) ; k ++ )
				nxt[j][1] = MIN( nxt[j][1], pre[j - k + l[i]][1] + 2 );
		//翻两次 
		std :: swap( pre, nxt );
	}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;正解，优化的$O(kn)$转移：  
```cpp
#include <cstdio>
#include <iostream>

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5, MAXK = 105;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
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

int deq[MAXN], h, t;
int pre[MAXN][2], nxt[MAXN][2];
int l[MAXK], r[MAXK];
int N, K;

int main()
{
	read( N ), read( K );
	for( int i = 1 ; i <= K ; i ++ ) read( l[i] ), read( r[i] );
	for( int i = 0 ; i <= N ; i ++ ) pre[i][0] = pre[i][1] = INF;
	pre[0][0] = 0;
	int rig;
	for( int i = 1 ; i <= K ; i ++ )
	{
		for( int j = 0 ; j <= N ; j ++ ) nxt[j][0] = INF, nxt[j][1] = pre[j][1];
		for( int j = r[i] - r[i - 1] ; j <= N ; j ++ ) nxt[j][0] = pre[j - ( r[i] - r[i - 1] )][0];
		//不翻 
		h = 1, t = 0, rig = 0;
		for( int j = 0 ; j <= N ; j ++ )
		{
			while( rig <= j ) 
			{ while( h <= t && pre[deq[t]][1] >= pre[rig][1] ) t --; deq[++ t] = rig ++; }
			while( h <= t && deq[h] < MAX( 0, j - r[i] + l[i] ) ) h ++;
			if( h <= t ) nxt[j][0] = MIN( nxt[j][0], pre[deq[h]][1] + 1 );
		}
		h = 1, t = 0, rig = 0;
		for( int j = 0 ; j <= N ; j ++ )
		{
			while( rig <= j - l[i] + r[i - 1] )
			{ while( h <= t && pre[deq[t]][0] >= pre[rig][0] ) t --; deq[++ t] = rig ++; }
			while( h <= t && deq[h] < MAX( 0, j - r[i] + r[i - 1] ) ) h ++;
			if( h <= t ) nxt[j][1] = MIN( nxt[j][1], pre[deq[h]][0] + 1 );
		}
		//翻一次
		h = 1, t = 0, rig = 0;
		for( int j = 0 ; j <= N ; j ++ )
		{
			while( rig <= j - l[i] + r[i - 1] )
			{ while( h <= t && pre[deq[t]][0] >= pre[rig][0] ) t --; deq[++ t] = rig ++; }
			while( h <= t && deq[h] < MAX( 0, j - r[i] + r[i - 1] + 1 ) ) h ++;
			if( h <= t ) nxt[j][0] = MIN( nxt[j][0], pre[deq[h]][0] + 2 );
		}
		h = 1, t = 0, rig = 0;
		for( int j = 0 ; j <= N ; j ++ )
		{
			while( rig <= j - 1 )
			{ while( h <= t && pre[deq[t]][1] >= pre[rig][1] ) t --; deq[++ t] = rig ++; }
			while( h <= t && deq[h] < MAX( 0, j - r[i] + l[i] ) ) h ++;
			if( h <= t ) nxt[j][1] = MIN( nxt[j][1], pre[deq[h]][1] + 2 );
		}
		//翻两次 
		std :: swap( pre, nxt );
	}
	int res = pre[N][1];
	if( 2 * N - r[K] <= N ) res = MIN( res, pre[N - ( 2 * N - r[K] )][0] );
	if( res == INF ) { puts( "Hungry" ); return 0; }
	puts( "Full" ), write( res ), putchar( '\n' );
	return 0;
}
```


---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF939F) & [CodeForces题目页面传送门](https://codeforces.com/contest/939/problem/F)

>题意见洛谷里的翻译。

~~这是一道毒瘤的div. 2 F，我是不可能比赛的时候做出来的。。。~~

（以下设两面都要煎$n$分钟，有$m$个可翻转时间区间，第$i$个为$[l_i,r_i]$）

废话不多说，这题可以考虑DP。数据范围告诉我们标算大概是$\mathrm{O}(nm)$的，不难想到可以把一个可翻转区间和与之相邻的不可翻转区间当作一个整体作为阶段。设$dp_{i,j}$表示当前考虑到时刻$l_{i+1}$（那么这个阶段需要考虑的时间段就是$[l_i,l_{i+1}]$，即可翻转区间$[l_i,r_i]$加上不可翻转区间$[r_i,l_{i+1}]$，特殊地，$l_0=0,r_0=-1,l_{m+1}=2n$），最后一刻煎的那一面一共煎了$j$秒，所需要翻的最少次数。那么目标就是$dp_{m,n}$。很显然，边界是$dp_{0,j}=\begin{cases}\infty&j\ne l_1\\0&j=l_1\end{cases}$，因为前$l_1$秒是翻不了的。而转移的时候只需要考虑在$[l_i,l_{i+1}]$里翻$0,1,2$次的情况即可，因为翻更多次都可以转化为翻$1$或$2$次（感性理解一下）。那么状态转移方程就出来了：

$$dp_{i,j}=\min\left(dp_{i-1,j-(l_{i+1}-l_i)},\min\limits_{k=l_i}^{r_i}\{dp_{i-1,l_i-(j-(l_{i+1}-k))}+1\},\min\limits_{k=l_i}^{r_i}\{dp_{i-1,j-(l_{i+1}-k)}+2\}\right)$$

将上面那个式子去去括号变变形，得

$$dp_{i,j}=\min\left(dp_{i-1,j-l_{i+1}+l_i},\min\limits_{k=l_i-j+l_{i+1}-r_i}^{l_i-j+l_{i+1}-l_i}\{dp_{i-1,k}\}+1,\min\limits_{k=j-l_{i+1}+l_i}^{j-l_{i+1}+r_i}\{dp_{i-1,k}\}+2\right)$$

不难发现，最外面的$\min$里有$3$部分，分别是翻$0,1,2$次的情况。翻$0$次的转移是$\mathrm{O}(1)$的，而另外$2$个是$\mathrm{O}(n)$的。朴素地转移总时间复杂度为$\mathrm{O}\left(n^2m\right)$~~，爆炸不多说~~。不难发现，在同一个阶段里，随着$j$的增加，翻$1$次的$\min$的上下界同时减少，翻$2$次的则同时增加。这$2$个都可以用单调队列来优化到每个阶段均摊$\mathrm{O}(n)$（一个倒着单调队列，一个正着），于是总共$\mathrm{O}(nm)$。~~（如果你想不到单调队列，也可以在到达一个阶段的时候，把上一个阶段的DP值打个ST表，或者线段树维护，但那都是带$\log$的，过不掉hhhh，所以只能单调队列）~~

对了，我的代码里还用了滚动数组优化了一下空间。（其实根本不用，$\mathrm{O}(nm)$的空间在CodeForces上应该是可以过的，但保险起见）

下面贴AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100000,M=100;
int n/*每面要煎的秒数*/,m/*可翻转区间数*/;
int l[M+1],r[M+1];//每个区间的左右端点 
int dp[2][2*N+1];//dp[i][j]表示当前考虑到时刻l[i+1]，最后一刻煎的那一面一共煎了j秒，所需要翻的最少次数
int q[2*N],head,tail;//单调队列 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",l+i,r+i);
	l[m+1]=2*n;//dp[m][j]应当考虑完整个2n秒的时间了 
	memset(dp[0],0x3f,sizeof(dp[0]));//边界 
	dp[0][l[1]]=0;//边界 
	for(int i=1;i<=m;i++){
		int now=i&1,prv=!now;//滚动数组 
		memset(dp[now],0x3f,sizeof(dp[now]));//初始化为inf 
		for(int j=0;j<=2*n;j++)dp[now][j]=min(dp[now][j],j-l[i+1]+l[i]<0?inf:dp[prv][j-l[i+1]+l[i]]);//翻0次 
		head=tail=0;//清空单调队列 
		for(int j=max(0,l[i]-2*n+l[i+1]-r[i]);j<-2*n+l[i+1];j++){//翻1次，因为是倒着的，所以从2n开始 
			while(head<tail&&dp[prv][q[tail-1]]>=dp[prv][j])tail--;
			q[tail++]=j;
		}
		for(int j=2*n;~j;j--){//翻1次，倒着单调队列 
//			cout<<j<<":\t+1=\t"<<l[i]-j+l[i+1]-r[i]<<"~"<<-j+l[i+1]<<"\n";
			while(head<tail&&q[head]<l[i]-j+l[i+1]-r[i])head++;
			if(-j+l[i+1]>=0){
				while(head<tail&&dp[prv][q[tail-1]]>=dp[prv][-j+l[i+1]])tail--;
				q[tail++]=-j+l[i+1];
			}
			dp[now][j]=min(dp[now][j],head==tail?inf:dp[prv][q[head]]+1);
		}
		head=tail=0;//清空单调队列 
		for(int j=max(0,-l[i+1]+l[i]);j<-l[i+1]+r[i];j++){//翻2次，因为是正着的，所以从0开始 
			while(head<tail&&dp[prv][q[tail-1]]>=dp[prv][j])tail--;
			q[tail++]=j;
		}
		for(int j=0;j<=2*n;j++){//翻2次，正着单调队列 
//			cout<<j<<":\t+2=\t"<<j-l[i+1]+l[i]<<"~"<<j-l[i+1]+r[i]<<"\n";
			while(head<tail&&q[head]<j-l[i+1]+l[i])head++;
			if(j-l[i+1]+r[i]>=0){
				while(head<tail&&dp[prv][q[tail-1]]>=dp[prv][j-l[i+1]+r[i]])tail--;
				q[tail++]=j-l[i+1]+r[i];
			}
			dp[now][j]=min(dp[now][j],head==tail?inf:dp[prv][q[head]]+2);
		}
//		for(int j=0;j<=2*n;j++)printf("dp[%d][%d]=%d\n",i,j,dp[now][j]);
	}
	printf(dp[m&1][n]<inf?"Full\n%d\n":"Hungry",dp[m&1][n]);//目标是dp[m][n] 
	return 0;
}
```

---

## 作者：Asuka二号机 (赞：1)

这个题 有点难的 彻底理解是真的用了很长时间

文字是空虚的我们直接上图

![](https://cdn.luogu.com.cn/upload/pic/62958.png)

抽象一下题目，我们后面就用白色黑色代替表述了，总之都是相对方向不影响做题。红色道道表示火热的炙烤——

设定fij表示第i个区间，结束这个区间的时刻没有被烤的那一面（即白色面）累计被烤j单位时间的最优决策

我们肉眼可以看出，在同个区间里翻来翻去毫无疑问是木大的，所以一个区间至多只会被翻两次

**第一种情况：只翻一次。（如上半张图）**

我们可以发现：

1、黑色一共被烤了j的时间

2、时间一共是r

1+2->3、白色一共被烤了r-j

4、本序列，白色被烤了k时间

3+4->5、上一序列，白色被烤了r-j-k

所以fij=max f[i-1][r-j-k]+1

**第二种情况：翻两次。（下半张图）**

1、黑色一共被烤了j的时间

2、本次，黑色被烤了k

3、上一序列结尾，黑色被烤了j-k

所以fij=max f[i-1][j-k]

然后单调队列滚一滚就好啦

相信大家都会写啦






---

## 作者：zxh_mc (赞：1)

## 题意简述

有一个正反面都为 $0$ 的卡片，每过 $1$ 分朝下那一面的数值就会增加 $1$，你可以在几个区间的时间内翻转卡片，求经过 $2n$ 秒后能否让这个卡片的正反面的数都为 $n$，求最小翻转数。

## 暴力

为了简单起见，我们定义一面为正面，一面为反面，$1$ 表示正面，$0$ 表示反面。

一眼看出来 dp，$dp_{i,j,1/0}$ 表示在第 $i$ 个区间结束后，正面数字为 $j$，$1/0$ 面朝上的最小翻转数。

那么状态转移方程为：

$dp_{i,j,1}=\min(dp_{i-1,j-p,1}+2,dp_{i-1,j-q,0}+1,dp_{i-1,j-g,1})$


$dp_{i,j,0}=\min(dp_{i-1,j-p,1}+1,dp_{i-1,j-q,0}+2,dp_{i-1,j,0})$

其中满足：

区间间隔 $\le p \le$ 两个区间右端点间隔。

区间长度 $\le q \le$ 两个区间右端点间隔。

$g$ 表示两个区间右端点间隔。

不难发现，这样的转移是 $O(n)$ 的，再加上我们需要计算 $nk$ 个 dp 值，这样做显然超时。需要考虑优化。

## 优化

不难发现，在计算一个区间完成后的值时，如果我们从 $n$ 到 $0$ 来计算，每次计算值所需要遍历区间的上限和下限都时逐渐减少的，那么我们就可以采取单调队列优化了。

这里用到一个小技巧：

如果一开始遍历区间的下限不为最低，那么我们可以令一个变量 $idx$ 一开始指向第一个区间的下限，然后逐渐降低，分批入队。

这个单调队列可以滚动掉一维，只需要保留它记录 dp 值的 $0/1$ 就行了。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, K = 110, INF = 0x3f3f3f3f;

int dp[K][N * 2][2];
int g[K], n, k, idx[2];

deque <int> q[2];

struct line {
	int l, r;
	bool operator < (const line& rhs) const {
		return l < rhs.l;
	}
}lines[K];

inline void q_push (int i, int j, int op) {
	while (q[op].size() && dp[i][q[op].back()][op] >= dp[i][j][op]) q[op].pop_back();
	q[op].push_back(j);
} 

inline void q_pop (int i, int j, int op) {
	while (q[op].size() && j - q[op].front() < 0) q[op].pop_front();
}

inline void init () {
	q[1].clear(); q[0].clear();
	idx[0] = idx[1] = 2 * n;
}

int main () {
	memset(dp, INF, sizeof(dp));
	scanf("%d%d", &n, &k);
	for (int i = 1;i <= k;i++) scanf("%d%d", &lines[i].l, &lines[i].r);
	sort(lines + 1, lines + 1 + k);
	g[1] = lines[1].l; g[k + 1] = 2 * n - lines[k].r;
	for (int i = 2;i <= k;i++) g[i] = lines[i].l - lines[i - 1].r;
	for (int j = lines[1].l;j <= lines[1].r;j++) {
		dp[1][j][1] = 2;
		dp[1][j][0] = 1;
	}
	dp[1][lines[1].r][1] = 0;
	for (int i = 2;i <= k;i++) {
		int l = lines[i].r - lines[i - 1].r, lg = lines[i].r - lines[i].l;
		init();
		for (int j = lines[i].r;j >= 0;j--) {
			while (j - l <= idx[1] && idx[1] > 0) q_push(i - 1, idx[1]--, 1);
			while (j - lg <= idx[0] && idx[0] > 0) q_push(i - 1, idx[0]--, 0);
			q_pop(i - 1, j - g[i], 1); q_pop(i - 1, j, 0);
			dp[i][j][1] = min(dp[i][j][1], (q[1].size() ? dp[i - 1][q[1].front()][1] + 2 : INF));
			dp[i][j][1] = min(dp[i][j][1], (q[0].size() ? dp[i - 1][q[0].front()][0] + 1 : INF));
			dp[i][j][1] = min(dp[i][j][1], (j - l >= 0 ? dp[i - 1][j - l][1] : INF));
//			cout << i << " " << j << " 1: " << dp[i][j][1] << endl;
		}
		init();
		for (int j = lines[i].r;j >= 0;j--) {
			while (j - l <= idx[1] && idx[1] > 0) q_push(i - 1, idx[1]--, 1);
			while (j - lg <= idx[0] && idx[0] > 0) q_push(i - 1, idx[0]--, 0);
			q_pop(i - 1, j - g[i], 1); q_pop(i - 1, j, 0);
			dp[i][j][0] = min(dp[i][j][0], (q[1].size() ? dp[i - 1][q[1].front()][1] + 1 : INF));
			dp[i][j][0] = min(dp[i][j][0], (q[0].size() ? dp[i - 1][q[0].front()][0] + 2 : INF));
			dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0]);
//			cout << i << " " << j << " 0: " << dp[i][j][0] << endl; 
		}
	}
	if (min(n - g[k + 1] >= 0 ? dp[k][n - g[k + 1]][1] : INF, dp[k][n][0]) < INF) printf("Full\n%d\n", min(n - g[k + 1] >= 0 ? dp[k][n - g[k + 1]][1] : INF, dp[k][n][0]));
	else printf("Hungry\n");
	return 0;
} 
```



---

## 作者：zhangxy__hp (赞：0)

首先有一个 $O(n^2)$ 的 DP：设 $f_{i,j}$ 表示前 $i$ 分钟，当前朝上的面煎了 $j$ 分钟的最小翻面次数。于是有方程：

$$
f_{i,j}=\min(f_{i-1,j},f_{i-1,i-j}+1)
$$

其中第二种转移是翻面的，即仅当 $\exist k,i\in[l_k,r_k]$ 时可以转移。

那么如果 $i$ 不在可以翻面的区间里，直接移过来就行了。于是只考虑可翻面的区间。设 $f_{i,j}$ 表示前 $r_i$ 分钟，朝上的面煎了 $j$ 分钟的最小翻面次数。

考虑当在同一区间内如果翻面次数 $\ge 2$，那一不如只翻 $1$ 次或 $2$ 次。于是只需考虑这两个转移。

- 翻 $1$ 次

  枚举当前朝下的面在这个区间内煎的时间 $k$。当前朝下的面显然总共煎了 $r_i-j$ 分钟，那么在这个区间开始前它就煎了 $r_i-j-k$ 分钟。而这个区间前这一面正好就是朝上的。于是 $f_{i,j}=\min(f_{i-1,r_i-j-k})$。
- 翻 $2$ 次

  枚举当前朝上的面在这个区间内煎的时间 $k$。在这个区间前这一面也是朝上的，煎了 $j-k$ 分钟。于是 $f_{i,j}=min(f_{i-1,j-k})$。

用单调队列优化这两个转移即可。时间复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline

using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=2e5+5;
const int inf=0x3f3f3f3f;
int n,m,duil[maxn];
int f[105][maxn];
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
//	cout<<cplx::usdmem();
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m;
	memset(f[0],0x3f,sizeof f[0]);
	f[0][0]=0;
	for(int i=1,l,r,hd,tl;i<=m;i++){
		for(int j=0;j<=n;j++){
			f[i][j]=f[i-1][j];
		}
		cin>>l>>r;
		hd=1,tl=0;
		for(int j=0;j<=min(r,n);j++){
			while(hd<=tl&&f[i-1][duil[tl]]>f[i-1][j]){
				tl--;
			}
			duil[++tl]=j;
			while(hd<=tl&&duil[hd]<j-(r-l)){
				hd++;
			}
			f[i][j]=min(f[i][j],f[i-1][duil[hd]]+2);
		}
		hd=1,tl=0;
		for(int j=r;~j;j--){
			while(hd<=tl&&f[i-1][duil[tl]]>f[i-1][r-j]){
				tl--;
			}
			duil[++tl]=r-j;
			while(hd<=tl&&duil[hd]<l-j){
				hd++;
			}
			f[i][j]=min(f[i][j],f[i-1][duil[hd]]+1);
		}
	}
//	for(int i=0;i<=m;i++){
//		for(int j=0;j<=n;j++){
//			cout<<f[i][j]<<" ";
//		}
//		puts("");
//	}
	printf(f[m][n]>=inf?"Hungry":"Full\n%d",f[m][n]);
	return 0;
}
}
int main(){return asbt::main();}
/*
10 1
0 20
*/
```

---

## 作者：_HCl_ (赞：0)

# CF939F 题解

**题意简述**

在 $2n$ 的时间内煎一块肉，要求正反面都刚好煎时间 $n$。

给定 $k$ 个不交的时间段，只能在这些时间段内进行翻面。求是否可行，并给出最少的翻面次数。

**思路引导**

由于我们要求的是最小翻面次数，因此我们应当把状态设成这个，也就是 $f_{i,j}$ 表示前 $i$ 分钟，当前不在被煎的那一面，已经煎过 $j$ 分钟，最小的翻面次数。

我们考虑在一段时间内，多次翻面是没有意义的。具体地，奇数次翻面都可以化简为 $1$ 次，偶数次翻面都可以化简为 $0$ 次或 $2$ 次。因此我们在考虑一个时间段内时，只用考虑翻面 $1$ 次和翻面 $2$ 次的情况。

- 翻面 $1$ 次

设翻面后到 $r$ 的时间是 $k$。

因为只翻面 $1$ 次，时间段后两面反转，因此 $f_{i,j}$ 中没被煎的面就是转移前被煎的那一面。因此应当从 $f_{i-1,r-j-k}$ 转移而来。

（$r-k$ 是总时间，减去 $j$ 相当于取反。）

因此有 $f_{i,j}=\max_{0\leq k\leq r-l}\limits(f_{i-1,r-j-k})+1=\max_{l-j\leq p\leq i-1}\limits(f_{i-1,p})+1$。在 DP 时，注意要倒序处理。

- 翻面 $2$ 次

设两次翻面之间的时间是 $k$。

由于翻转两次，时间段后两面不变，因此可以理解成中间多了一段用来煎另一面。

那么就有 $f_{i,j}=\max_{0\leq k\leq r-l}\limits(f_{i-1,j-k})+2=\max_{j-r+l\leq p\leq i-1}\limits(f_{i-1,p})+2$。这里的 DP 时正序。

对于 $f_{i-1,p}$ 的处理，可以用单调队列来维护。对于第一维的 $i$，可以用滚动数组优化掉。

最终的复杂度为 $\mathcal{O}(kn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int f[2][N<<2];
int n,k;
struct typ{
	int id,num;
};
deque<typ> q;
int main(){
	cin>>n>>k;
	memset(f[0],0x3f,sizeof(f));
	f[0][0]=0;
	while(k--){
		int l,r;
		scanf("%d%d",&l,&r);
		for(int i=0;i<=n;++i)f[1][i]=f[0][i];
		q.clear();
		for(int i=r;i>=0;--i){
			while(!q.empty()&&q.front().id<l-i)q.pop_front();
			while(!q.empty()&&q.back().num>f[0][r-i])q.pop_back();
			q.push_back(typ{r-i,f[0][r-i]});
			f[1][i]=min(f[1][i],q.front().num+1);
		}
		q.clear();
		for(int i=0;i<=min(r,n);++i){
			while(!q.empty()&&q.front().id<i-r+l)q.pop_front();
			while(!q.empty()&&q.back().num>f[0][i])q.pop_back();
			q.push_back(typ{i,f[0][i]});
			f[1][i]=min(f[1][i],q.front().num+2);
		}
		for(int i=0;i<=n;++i)f[0][i]=f[1][i];
	}
	if(f[1][n]>=1e9)cout<<"Hungry";
	else cout<<"Full\n"<<f[1][n];
}
```

---

## 作者：大菜鸡fks (赞：0)

又没调出来。wa在13个点

套路题。可以发现最多每段翻2次，考虑对每段单独dp，f[i][j]表示已经完成第i段操作，另外一面烤了j分钟的最少反转次数
f[i][j]=min(f[i−1][j−k])+2,f[i][j]=min(f[i−1][ri−j−k])+1

那么就是第一个转移正着枚举，第二个转移倒着枚举

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5,K=105,INF=1e9;
int n,k,l[K],r[K];
inline void init(){
	n=read(); k=read();
	for (int i=1;i<=k;i++) l[i]=read(),r[i]=read();
}
inline void upd(int &x,int w){
	x=min(x,w);
}
int q[N],dp[2][N],cur;
inline void solve(){
	for (int i=1;i<=n;i++) dp[0][i]=INF;
	for (int i=1;i<=k;i++){
		int h=1,t=0;
		for (int j=0;j<=n;j++) dp[cur^1][j]=dp[cur][j];
		for (int j=0;j<=min(n,r[i]);j++){
			while (h<=t&&j-l[i]+r[i]>q[h]) h++;
			while (h<=t&&dp[cur][j]<=dp[cur][q[t]]) t--;
			q[++t]=j; upd(dp[cur^1][j],dp[cur][q[h]]+2);  
		}
		h=1,t=0;
		for (int j=r[i];j>=0;j--){
			while (h<=t&&l[i]-j>q[h]) h++;
			while (h<=t&&dp[cur][r[i]-j]<=dp[cur][q[t]]) t--;
			q[++t]=r[i]-j; upd(dp[cur^1][j],dp[cur][q[h]]+1);
		}
		cur^=1;
	}
	if (dp[cur][n]>=INF) puts("Hungry");
		else puts("Full"),writeln(dp[cur][n]);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

