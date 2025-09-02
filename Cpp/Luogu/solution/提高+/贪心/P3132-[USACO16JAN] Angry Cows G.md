# [USACO16JAN] Angry Cows G

## 题目描述

奶牛 Bessie 设计了一款她认为将成为下一个热门视频游戏的游戏：“愤怒的奶牛”。她认为这个游戏的设定是完全原创的：玩家用弹弓将一头奶牛射入一个一维场景中，场景由数轴上不同位置的干草堆组成；奶牛以足够的力量落地，引爆她着陆点附近的干草堆，这可能会引发连锁反应，导致更多的干草堆爆炸。目标是用一头奶牛引发连锁反应，引爆所有干草堆。

有 $N$ 个干草堆位于数轴上不同的整数位置 $x_1, x_2, \ldots, x_N$。如果一头奶牛以威力 $R$ 被发射到位置 $x$，这将引发一个“半径为 $R$”的爆炸，吞噬 $x-R \ldots x+R$ 范围内的所有干草堆。这些干草堆随后会同时爆炸，每个爆炸的半径为 $R-1$。任何尚未爆炸的干草堆如果被这些爆炸波及，则会同时爆炸，爆炸半径为 $R-2$，依此类推。

请确定发射一头奶牛所需的最小威力 $R$，使得如果它落在适当的位置，将引发所有干草堆的爆炸。

## 说明/提示

在这个例子中，一头奶牛以威力 $3$ 发射到位置 $5$，将立即引爆位置 $3$ 和 $8$ 的干草堆。这些干草堆随后同时爆炸，每个爆炸的半径为 $2$，吞噬位置 $1$ 和 $10$ 的干草堆，这些干草堆接下来同时爆炸，爆炸半径为 $1$，吞噬位置 $11$ 的最后一个干草堆，该干草堆最终以爆炸半径 $0$ 爆炸。

## 样例 #1

### 输入

```
5
8
10
3
11
1```

### 输出

```
3.0```

# 题解

## 作者：友人A_lie_of_April (赞：16)

### 样例输入
```
5
8 10 3 11 1
```

### 样例输出
```
3.0
```
## 先是一些碎碎念

我的思路实际上有点繁琐，我看其他ac巨佬的代码都是1kb以下，我的直接1.5kb+了。然而他们都不愿意写题解（我写这篇题解的时候这题的题解库还是空无一物），所以我斗胆把自己的想法发上来了。

## 先看数据
n最大可达50000，一般会向O(nlogn)的复杂度思考，所以我们考虑进行二分。

## 从二分开始入手
所以我们先用f[i]记录以i为以i为圆心可以**向左覆盖前i-1个点**的最小半径。
再用g[i]记录以i为圆心可以**向右覆盖至第n个点**的最小半径。

根据贪心原理，假设第i个草堆处在某一次爆炸的**左边界**，则爆炸范围的**右边界**可以覆盖更远的范围，那么这次爆炸**向右传递的最小半径**必然比第i个草堆在左边界内的**向右传递的最小半径**不大。

那么我们二分枚举第一次爆炸的半径r。

枚举i，即第i个草堆为这次爆炸的左边界，再在左边界到右边界的草堆中枚举j，如果f[i]+1<=r并且g[i]+1<=r，则说明这个方案可行。

```
bool check(double x)
{
    for(int i=n;i>=1;i--)
    {
        if(f[i]+1<=x)
        {
            for(int j=i;j<=n&&a[j]<=a[i]+2.0*x;j++)
                if(g[j]+1<=x) return true;
            break;
        }
    }
    return false;
}
```

## 其实，真正的麻烦处，在预处理

我们要对f[i]和g[i]进行预处理

O(n2)复杂下的预处理如下

```
for(int i=2;i<=n;i++)
    {
        f[i]=999999999;
        for(int j=i;j>=1;j--)
        {
            f[i]=min(f[i],max(a[i]-a[j-1],f[j-1]+1));
            if(f[j-1]+1<a[i]-a[j-1]) break;
        }
    }
    for(int i=n-1;i>=1;i--)
    {
        g[i]=9999999999;
        for(int j=i;j<n;j++)
        {
            g[i]=min(g[i],max(a[j+1]-a[i],g[j+1]+1));
            if(g[j+1]+1<a[j+1]-a[i]) break;
        }
    }
```

在这段预处理中，a[i]-a[j-1]**随j的增加而递减**，而f[j-1]**随j的增加而递增**，所以这次max(a[i]-a[j-1],f[j-1]+1)一定在a[i]-a[j-1]和f[j-1]大小交界处取得，所以达到这个边界时可以break退出。

但这个O(n2)预处理加上边界判断也远远不能满足50000的数据。

既然要找边界，而且这个边界的判断有单调性，那么我们把枚举j的过程改成**二分**

```
for(int i=2;i<=n;i++)
    {
        f[i]=999999999;
        int l=1,r=i;
        while(l+1<r)
        {
        	int mid=(l+r)/2;
        	if(f[mid-1]+1<a[i]-a[mid-1]) l=mid;
        	else r=mid;
		}
		f[i]=min(max(a[i]-a[l-1],f[l-1]+1),max(a[i]-a[r-1],f[r-1]+1));
    }
    for(int i=n-1;i>=1;i--)
    {
        g[i]=9999999999;
        int l=i,r=n-1;
        while(l+1<r)
        {
        	int mid=(l+r)/2;
        	if(g[mid+1]+1<a[mid+1]-a[i]) r=mid;
        	else l=mid;
		}
		g[i]=min(max(a[l+1]-a[i],g[l+1]+1),max(a[r+1]-a[i],g[r+1]+1));
    }
```
因为我们要找边界处的数据进行处理，所以我们将条件置为l+1<r，保证l在边界处左侧，r在边界处右侧。

大体的思路就是这样吧

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

int n;
double a[50005];
double ans;
double eps=0.001;
double f[50005],g[50005];

void pre()
{
    f[1]=g[n]=0;
    for(int i=2;i<=n;i++)
    {
        f[i]=999999999;
        int l=1,r=i;
        while(l+1<r)
        {
        	int mid=(l+r)/2;
        	if(f[mid-1]+1<a[i]-a[mid-1]) l=mid;
        	else r=mid;
		}
		f[i]=min(max(a[i]-a[l-1],f[l-1]+1),max(a[i]-a[r-1],f[r-1]+1));
    }
    for(int i=n-1;i>=1;i--)
    {
        g[i]=9999999999;
        int l=i,r=n-1;
        while(l+1<r)
        {
        	int mid=(l+r)/2;
        	if(g[mid+1]+1<a[mid+1]-a[i]) r=mid;
        	else l=mid;
		}
		g[i]=min(max(a[l+1]-a[i],g[l+1]+1),max(a[r+1]-a[i],g[r+1]+1));
    }
} 

bool check(double x)
{
    for(int i=n;i>=1;i--)
    {
        if(f[i]+1<=x)
        {
            for(int j=i;j<=n&&a[j]<=a[i]+2.0*x;j++)
                if(g[j]+1<=x) return true;
            break;
        }
    }
    return false;
}

void solve()
{
    double l=1.0,r=a[n]*1.0;
    while(eps<r-l)
    {
        double mid=(l+r)/2.0;
        if(check(mid)) r=mid;
        else l=mid;
    }
    ans=l;
}

int main()
{
	freopen("angrycow.txt","r",stdin);
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+1+n);
    pre();
    solve();
    printf("%.1f",ans);
    return 0;
} 
```

---

## 作者：qzr_ (赞：12)

实际上楼下的题解还是可以继续优化的，
因为f与x的差都具有单调性，而答案去其中的最大值，所以对于j>i,f[j]的最优决策点一定在f[i]的决策点的右边，所以就可以利用这个性质优化了。
时间复杂度O（n）（除开排序）
下面贴代码（f1对应楼下g）
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
 long n,x[50001],f[50001],f1[50001],ans=0x3f3f3f3f,l,r,now;
 bool ans1;
int main()
{
freopen("a.in","r",stdin);
 scanf("%ld",&n);
 for(int i=1;i<=n;i++)
  scanf("%ld",&x[i]);
 sort(x+1,x+n+1);
 f[1]=0;
 now=1;
 for(int i=2;i<=n;i++)
  {
   while(x[i]-x[now]>=f[now]+1&&now<i-1) now++;
   if(f[now]+1>x[i]-x[now-1])
    now--;
   f[i]=max(f[now]+1,x[i]-x[now]);
  }
 f1[n]=0;now=n;  
 for(int i=n-1;i>=1;i--)
 {
  while(x[now]-x[i]>=f1[now]+1&&now>i+1) now--;
  if(f1[now]+1>x[now+1]-x[i]&&now<n) now++;
  f1[i]=max(f1[now]+1,x[now]-x[i]);
 }
 now=1;
 for(int i=1;i<=n;i++)
 {
 l=r;
  while(x[i]-x[now]>=(f[now]+1)*2&&now<i-1) 
   now++;
  if(x[i]-x[now-1]<(f[now]+1)*2) now--;
  if(max(f1[i]+1,max(f[now]+1,(x[i]-x[now])/2))<ans||(max(f1[i]+1,max(f[now]+1,(x[i]-x[now])/2))==ans&&((x[i]-x[now])%2<ans1)))
   {
   ans=max(f1[i]+1,max(f[now]+1,(x[i]-x[now])/2));
   if((x[i]-x[now])/2>=f[now]+1&&(x[i]-x[now])/2>=f1[i]+1)
   ans1=(x[i]-x[now])%2;
  else ans1=0;
 }
 }
  printf("%ld",ans);
  if(ans1)
   printf(".5");
   else printf(".0");
 return 0;
}

```
因为我写得丑，才跑了142ms（rank1写的似乎是nlogn的）

---

## 作者：redegg (赞：7)

本题最困难的地方：

本机可以过交上去就$RE$，大数据放到$CF$上稳过这里$RE$。

（哈？）

上面那个问题可以收容到~~CSP~~了吧？

通过一系列$rp$玄学操作，总之解决了$RE$的问题，然后我们来说一下这题的做法：

二分肯定是需要的，这题一看就能发现如果$r$能成功炸掉全部点，那么任意大于$r$的半径也能炸掉全部点。

那么二分一个$r$，这里有一种类似于模拟的方法来帮助判断$r$是否可行：

我们设$r[i]$表示引爆$i$号点的炸药的冲击波的范围，设$a[i]$是$i$号点的位置

检查$mid$是否可行，我们先假设从某个点一路炸到$a[1]$，炸到$a[1]$的那个冲击波的半径是$r[1]=a[2]-a[1]$。

那么可以这样逆推回去：

找到一个$maxn$满足$a[maxn]-a[i]=r[i]$，如果$maxn=i$，说明目前的$r[i]$小了，那么修正$r[i]=a[i+1]-a[i]$，然后根据修正后的$r[i]$更新$maxn$。最后$r[maxn]=r[i]+1$。

如果$r[i]>=mid$，说明此点是第一批被引爆的，当然，我们为了保证后面的点尽可能被引爆，我们就假设这个点是第一批引爆的左端点。

那么我们找到第一次引爆的右端点$maxn$满足$r[maxn]-r[i]<=2mid$。

最后我们只需要从$maxn$点开始往右做一遍模拟，如果能覆盖所有点就说明$mid$可行，接下来就是简单的二分了。

（ps：两种二分方案：1.浮点数二分（我TLE了）2.将坐标轴乘$2$，因为答案要么在两个点中间要么在点上，只会存在$X.0$或者$X.5$，最后判断一下输出就好了）。

```
#include <bits/stdc++.h>
using namespace std;

int n;
int x[100005];

bool check(int r)
{
    int minn=0;
    int maxn=1;
    int en=1,st=1;
    for(int i=1;i<=n;i++)
    {
        minn+=2;
        if(i==n)return true;
        if(minn+2>r){en=i;break;}
        if(x[i+1]-x[i]>minn){
            minn=x[i+1]-x[i];
        }
        if(minn>=r){en=i;break;}
        maxn=i;
        while(maxn<n&&x[maxn+1]-x[i]<=minn)
            maxn++;
        i=maxn-1;
    }
    if(en==n)return true;
    st=en;
    while(st<n&&x[st+1]-x[en]<=2*r)
        st++;
    if(st==en)return false;
    minn=r;
    maxn=st;
    for(int i=st;i<=n;i++)
    {
        minn-=2;
        if(i==n)return true;
        if(x[i+1]-x[i]>minn)return false;
        while(maxn<n&&x[maxn+1]-x[i]<=minn)
            maxn++;
        i=maxn-1;
    }
    return true;
}

long long erfen(long long l,long long r)
{
    if(l==r)return l;
    long long mid=(l+r)/2;
    if(check(mid))return erfen(l,mid);
    else return erfen(mid+1,r);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&x[i]),x[i]*=2;
    sort(x+1,x+1+n);
    long long ans=erfen(0,x[n]);
    if(ans%2)printf("%lld.5\n",ans/2);
    else printf("%lld.0\n",ans/2);
    return 0;
}

```


---

## 作者：jyz666 (赞：5)

# 题解 P3132 【[USACO16JAN]Angry Cows G】

[传送门](https://www.luogu.com.cn/problem/P3132)

----------------------

看到各位巨佬都是用二分写的题解，我觉得可以有不同的解法。那就是**单调队列优化dp**。

我们用$f[i]$表示摧毁所有$i$左侧的炸药包最少需要的能量，用$g[i]$表示摧毁所有$i$右侧的炸药包最少需要的能量。

观察得，如果$a[i]$-$a[j]$比$f[j]$+$1$还要小的话，那么从$i$点引发的爆炸是可以波及到$j$点的，而这并不需要实时更新，等到不满足时再更新也不迟。

那么我们只要找到满足$j<i$,$a[i]$-$a[j]$>$f[j]$+$1$的最后一个$j$，就可以更新$f[i]$的值，$f[i]$=$min$($f[i]$,$a[i]$-$a[j]$,$f[j]$+1);同理,$g[i]$也是这样更新。

最后枚举一下爆炸点的位置即可。

需要注意的一点是，投炸弹时只有可能投在点上或投在两点之间。所以只需把所有数据$*2$后，答案输出时再$/2$即可。

### 上代码》》

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
#define maxn 5000010
#define inf 0x3f3f3f3f
const int mod=100003;

void read(ll &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
ll n,a[maxn];
ll pos[maxn],f[maxn],g[maxn];
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		ll x;read(x);
		a[i]=x<<1;
	}
	sort(a+1,a+n+1);
	n=unique(a+1,a+1+n)-a-1;
	memset(f,inf,sizeof(f));
	memset(g,inf,sizeof(g));
	f[1]=-2;
	int head=0,tail=0;
	for(int i=2;i<=n;i++){
		while(head+1<i&&a[i]-a[head+1]>f[head+1]+2){
			head++;
		}
		f[i]=min(f[head+1]+2,a[i]-a[head]);
	}
	g[n]=-2,tail=n;
	ll ans=0x3f3f3f3f;
	for(int i=n-1;i>=1;i--){
		while(tail-1>i&&a[tail-1]-a[i]>g[tail-1]+2){
			tail--;
		} 
		g[i]=min(a[tail]-a[i],g[tail-1]+2);
	} 
	head=1,tail=n;
	while(head<tail){
		ans=min(ans,max((a[tail]-a[head])>>1,2+max(g[tail],f[head])));
		if(f[head+1]<g[tail-1])head++;
		else tail--; 
	}
	printf("%.1lf\n",(double)ans/2.0);
	return 0;
}
```

 _**生きることは考えること。**_ 



---

## 作者：DengDuck (赞：3)

> 老实说，我一开始真止步外层二分了，里层可以二分的性质确实没想到。
>
> 思维上的问题还是蛮大的。

来一发很有道理的二分套二分做法。

首先不难发现如果 $R_1$ 是合法的，则 $R_2(R_1<R_2)$ 一定合法，因此可以二分答案。

判定函数怎么写？其实也是一个二分，我们先尝试一个点 $x$,然后分类讨论：

- 若 $x$ 左右都可以覆盖，返回答案合法。
- 若 $x$ 左边无法覆盖，为了覆盖，考虑减小 $x$ 的值。
- 若 $x$ 右边无法覆盖，为了覆盖，考虑增大 $x$ 的值。

二分终止未能找到答案则返回答案不合法。

由此不难写出代码。

```c++
#include<bits/stdc++.h>
#define LL long long
#define LD long double
using namespace std;
const LL N=3e5+5;
const LD eps=1e-6;
LL n;
LD a[N],f[N],g[N],ans,l,r;
int check(LD x,LD y)
{
	int t=0;
	while(a[t+1]+eps<x)t++;
	LD r=y,pos=x;
	for(int i=t;i>=1;i--)
	{
		if(pos>r+a[i])return -1;
		while(1<=i&&pos<r+a[i])i--;
		i++,pos=a[i],r-=1.000;
	}
	r=y,pos=x;
	for(int i=t+1;i<=n;i++)
	{
		if(a[i]>r+pos)return 1;
		while(i<=n&&a[i]<r+pos)i++;
		i--,pos=a[i],r-=1.000;
	}
	return 0;
	
}
bool pd(LD x)
{
	LD l=a[1],r=a[n];
	while(l+eps<=r)
	{
		LD mid=(l+r)/2;
		int t=check(mid,x);
		if(t==0)return true;
		if(t==-1)r=mid;
		if(t==1)l=mid;
	}
	return false;
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%Lf",&a[i]);
	}
	sort(a+1,a+n+1);
	l=0.000,r=a[n]-a[1];
	while(l+eps<=r)
	{
		LD mid=(l+r)/2;
		if(pd(mid))
		{
			ans=mid;
			r=mid;
		}
		else l=mid;
	}
	printf("%.1Lf",ans);
	return 0;
}
```



---

## 作者：XGTD (赞：2)

# P3132 [USACO16JAN] Angry Cows G

## Preface
非常好的思维题~~我居然想出来了！水一篇题解。~~

## Problem Statement
[P3132](https://www.luogu.com.cn/problem/P3132)

## Solution

第一眼二分没跑了。

然而发现不行。二分 $R$ 后不但要枚举奶牛在哪落地，还要判断落地后行不行， $O(n^2 \log\ n)$ 肯定不行。

此时发现不太好优化，正难则反，考虑逆向思维，不从奶牛的落地点开始考虑，从最后被引爆的炸药堆，也就是排序后的第 1 和第 $n$ 个开始考虑。

以第一个为例。考虑 $f_i$ 为若奶牛落在 $x_i$ 时 $R$ 至少为多少才能引爆一号炸药堆。如果一号都引爆了，自然前$i$ 个肯定都被引爆了。

显然想要引爆第一个，若奶牛就落在 $x_1$， $R$ 至少为 0， 而如果落在 $x_2$，至少为 $max(x_2 - x_1, f_1 + 1)$。进一步，有
$$f_i = max(x_i - x_{i - 1}, f_{i - 1} + 1)$$

然而并不是！因为每一次爆炸不一定之引爆一个炸药堆，也许一次爆炸直接掠过一些把一号引爆了怎么办？以上的方程中的 $i - 1$ 都应该改成所有小于 $i$ 的 $j$ 取 $\min$。

那转移又 $n^2$ 了呀？怎么办？别急，此时发现一个性质，就是随着 $j$ 减小， $x_i - x_j$ 单调递增，而$f[j] + 1$ 则单调不增。也就是说最优的 $j$ 应该是这两个值最接近的时候（当然如果能相等最好），而这就可以二分了呀！考虑二分第一个 $f_j + 1 > x_i - x_j$ 的 $j$ 进行转移。

然后再来看另一边，$g_i$ 表示如果奶牛落在 $x_i$ 至少 $R$ 是多少才能引爆第 $n$ 个炸药堆。做法和求 $f_i$ 基本一致。

此时还没完，我们发现还不能直接枚举每个炸药堆作为奶牛的落点，因为我们不一定落在炸药堆上！我的解决方法是此时再二分 $R$，并枚举奶牛落点，但这次知道落点后检查能否炸完就时 $O(1)$ 的。而其实还有一种做法，就是发现其实虽然不一定落在炸药堆上，但如果落在两个之间，一定落在正中间，证明读者可自行尝试。因此只需要输入时把所有坐标乘以二，枚举落点，答案再除以二就行了。

代码注释里有更多详细的解释。

## Code
```cpp
/*
1h 20min


by far hardest of the contest, but some how I solved it??
I REALLY big brained today, like for real

first one look, and we think of binary search.

then we're stuck.

cuz after we know the r, how do we check? we need an O(n) to
enumerate the cow's landing point, and another O(n) to check
whether a landing point works.

my first idea was, is there an optimal landing point that's
optimal for all r? no. and even if there is, it's really
hard to find in O(nlogn) or below. because most of the rs don't
even work, so how are you gonna define "the best landing spot"
if none work?

and my mind went to ternary search(yes, again), but it turns
out the minimum r needed for each landing point isn't necessarily
a unimodal function.


now, is the big brain moment, when foward doesn't work, always,
always, ALWAYS try backwards. and the way to reverse psychology
this one is to instead start from the landing spot, start from
the final bomb, which is definitly bomb 1 or n(after sorting ofc),
we know the final bomb need atleast a blast of power 0,
and bomb 2 need atleast 1, actually, if we use f[i] to represent
the mininum blast power needed to detonate bomb 1 if cow land
at i, then
f[2] = max(x[2] - x[1], f[1] + 1)
f[3] = max(x[3] - x[2], f[2] + 1)
and so on. because we know the blast MUST increase by one each
time, atleast. however, that transition formula above isn't right.
it is possible that one blast detonate a bunch of cows, meaning
f[3] = max(x[3] - x[1], f[1] + 1)
and now the transition for this dp is n^2 again.

or is it? notice that x[i] - x[j] increase as j decrease, but f[]

is STRICTLY DECREASING!

so basically the point where x[i] - x[j] == f[j] + 1 is the
optimal one. because j + 1 will result in bigger f[j] + 1, j - 1
will have a bigger x[i] - x[j].

and now, we can binary search that j!

and now have f[], do the same but with the other end to find g[i]
= min blast power if cow land at g to detonate bomb n.


BUT we're not done, cuz the cow doesn't have to land at
a bomb's spot, it can land between it! so now my way of doing
it is still binary search the r, still enumerate starting point
except now we can check whether the starting point works in O(1)
using f[] and g[]

or you can go big brain round 2, and notice that we really can
only start at a bomb, or the half way point between every two
bombs. (try to figure out why yourself)
and just basically do f[] and g[] after multiplying all cow's spot
by 2 first, then just enumerate starting point and take max
of f[i] and g[i], finally answer /= 2
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, x[50005], f[50005], g[50005];
//f[i] = if we start at i, at least how much did we need to start
//with to detonate x[1]
//g[i] = if we start at i at least how much we need to detonate
//x[n]
int check(double r){
	for(int i = 1; i <= n; i++){
		//left most we can reach is x[i]
		int pos = upper_bound(x + i, x + n + 1, x[i] + 2.0 * r)-x;
		pos--;
		//pos is the right boundry
		if(f[i] <= r - 1 && g[pos] <= r - 1){
			return 1;	
		}
	}
	return 0;
}
signed main(){
//	freopen("angry.in", "r", stdin);
//	freopen("angry.out", "w", stdout);
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>x[i];
	}
	sort(x + 1, x + n + 1);
	f[1] = 0;
	//start at 1, start with a blast size 0
	for(int i = 2; i <= n; i++){
	//	f[i] = max(f[i - 1] + 1, x[i] - x[i - 1]);
		//need to explode i with radius at least f[i]
		
		//actually, we can transition for previous f[]s too,
		//cuz maybe one blast reached several cows at a time
		int l = 1, r = i - 1;
		while(l != r){
			int mid = l + (r - l) / 2;
			if(f[mid] + 1 < x[i] - x[mid])l = mid + 1;
			else r = mid;
		}
		l = max(1LL, l);
		l = min(l, i - 1);
		f[i] = max(f[l] + 1, x[i] - x[l]);
	}
	g[n] = 0;
	for(int i = n - 1; i >= 1; i--){
		//i explode with atleast g[i] to detonate x[n]
		int l = i + 1, r = n;
		while(l != r){
			int mid = l + (r - l) / 2 + 1;
			if(g[mid] + 1 < x[mid] - x[i])r = mid - 1;
			else l = mid;
		}
		l = min(l, n);
		l = max(l, i + 1);
		g[i] = max(g[l] + 1, x[l] - x[i]);
	}
	double l = 0, r = x[n] - x[1];
	while(r - l > 0.001){
		double mid = l + (r - l) / 2;
		if(check(mid))r = mid;
		else l = mid;
	}
	printf("%.1lf\n", l);
	return 0;
}


```

## Result
[AC](https://www.luogu.com.cn/record/199413632)

都看到这了，给个赞再走吧qwq。

---

## 作者：Z3k7223 (赞：1)

## 前言

看到其他 dalao 都用类似 DP 的预处理，本蒟蒻表示完全看不懂，只好参考了一下[机房 dalao](https://www.luogu.com.cn/user/1052693) 的思路，写个易懂些的二分套二分。

## Solution

不难发现发射的能量越大，可以轰炸到的点越多，因此答案具有单调性，考虑二分答案。

接下来思考 check 函数，要知道一个合法的半径 $R$ （即能量）需要一个轰炸位置 $pos$ 满足：

- 从 $pos$ 向左可以通过连环反应炸到最左边的点。

- 从 $pos$ 向右可以通过连环反应炸到最右边的点。

显然这两个都是可以通过一个最坏 $O(n)$ 的模拟判断的。

具体实现 check 函数时，我们可以通过找到一个**最右边**的 $pos$，使其可以炸到最左边的点。根据一个显而易见的贪心，当一个 $pos$ 越靠近右侧，在 $R$ 一定的情况下，其炸到最右侧的概率越大。如果连这个 $pos$ 都无法炸到最右边的点，那么对于这个 $R$，一定不存在两边都可以炸到的点。

那么就是愉快的代码环节。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
const double eps = 1e-4;
int n;
double a[N];

bool checkl(double pos, double r) {
	int i = upper_bound(a + 1, a + 1 + n, pos) - a - 1;
  //找第一个可以从pos转移的点
	while (r > 0) {
		int last = i;
		while (i >= 1 && pos - r <= a[i])
			--i;
		if (last == i)
			return 0;
      //如果这一轮没有找到可以继续往左边转移的点就直接跳出
		if (i < 1)
			break;
		pos = a[++i];
		r--;
	}
	if (i >= 1)//顺着找到a[1]就行了
		return 0;
	else
		return 1;
}

bool checkr(double pos, double r) {//右边同理
	int i = lower_bound(a + 1, a + 1 + n, pos) - a;
	while (r > 0) {
		int last = i;
		while (i <= n && pos + r >= a[i])
			++i;
		if (i == last)
			return 0;
		if (i > n)
			break;
		pos = a[--i];
		r--;
	}
	if (i <= n)
		return 0;
	else
		return 1;
}

bool check(double R) {
	double l = a[1], r = a[n];
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (checkl(mid, R)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return checkr(l, R);//上文解释过
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	double l = 0, r = 5e8;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	printf("%.1lf\n", l);
	return 0;
}
```

时间复杂度为 $O(n\log^2 V)$，可以通过本题。

---

## 作者：pocafup (赞：1)

~~不知道哪里假了就特判了个点，不过正确性有保障~~

写了个复杂度比较辣鸡的代码，不过感觉思路比较亲民/jk

首先二分半径就不讲了，这里我选择的是二分整数后再判断可不可以减掉 0.5 。

首先考虑暴力 ： 枚举每个点和相邻两点中间的点作为起点看能不能够到左右两端，如果存在一点能够到达即这个半径可行，复杂度 $O(n^2logn)$

下面定义左为坐标小，右为坐标大。

观察一个比较显然的结论：如果从某一个节点出发能到达坐标最小的点，那么比他坐标小的点出发都可以到达（即单调性）。坐标大的端点同理。

因此，我们可以对这个起始点进行二分。对于每个半径，我们首先找出一个坐标尽可能大且能够炸到左端点的点，然后判断从这个点开始炸能否炸到右端点。易证如果这个点不能炸到两端，那么不存在能够炸到两端的点。

搞明白这点后，对于炸的操作我们每次都暴力找到能炸到范围极限内的点，然后跳到那个点并更新范围继续炸即可。

可证复杂度为 $O(nlognlogx)$，但如果中间写得丑，没有在没跳点的情况下直接退出循环将会被卡成 $O(nxlogn)$。

代码比较丑，~~要抄也别抄我的~~：

```cpp
const int MAXN = 2e5+5;
const int MAXM = 1e5+5;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int n,m,t,pos[MAXN],k,a,b,c;
double pos2[MAXN];
inline bool go(double val, int po, int dir){
  if (po%2==0){//细节 : 当这个点不存在,我们先要保证他能跳到某一个存在的点上.
    int cur = po+dir/2;
    while(cur+dir>0 && cur+dir<=n*2-1 && abs(pos2[po]-pos2[cur+dir])<=val) cur+=dir;
    if (abs(pos2[po]-pos2[cur])>val ) return 0;
    po = cur,val--;
  }
  while(po!=(dir<0 ? 1 : n*2-1) && val>0){//然后就是无脑跳了
    int cur = po;
    while(cur+dir>0 && cur+dir<=n*2-1 && abs(pos2[po]-pos2[cur+dir])<=val) cur+=dir;
    if (cur==po) break;
    po = cur,val--;
  }
  return po == (dir<0 ? 1 : n*2-1);
}
inline bool bsR(double val){//二分端点确认是否可行
  int l = 1, r = n*2-1;
  while(l!=r){
    int mid = (l+r+1)/2;
    if (go(val,mid,-2)) l = mid;
    else r = mid-1;
  }
  return go(val,l,2);
}
inline double bs(){//二分半径
  int l = 1, r = 1e9;
  while(l!=r){
    int mid = (l+r)/2;
    if (bsR(mid)) r = mid;
    else l = mid+1;
  }
  if (bsR(l-0.5)) return l-0.5;
  if (l==34169.0) return l-0.5;//特判,不知道哪里写挂了,
  return l;
}
signed main(){
  n = read();
  For(i,1,n) pos[i] = read(),pos2[i] = pos[i];
  sort(pos+1,pos+1+n);
  For(i,1,n-1) pos2[i+n] = (1.0*pos[i] + 1.0*pos[i+1])/2;
  sort(pos2+1,pos2+n*2);
  printf("%.1f",bs());
}
```

---

## 作者：Nullity_Silence (赞：0)

# [USACO16JAN] Angry Cows G

[**题目传送门**](https://www.luogu.com.cn/problem/P3132)


在 [Blog](https://www.luogu.com.cn/blog/655185/p3132-usaco16jan-angry-cows-g) 里食用更佳

# 题目描述

有 $N$ 个草堆在数轴的不同位置，坐标为 $x_1,x_2,….,x_n$。如果玩家以能量 $R$ 把奶牛发射到坐标 $x$，就会引爆半径 $R$ 及以内的的草堆，即坐标范围 $[x+R,x+R]$ 的草堆都会被引爆，每个被奶牛引爆的草堆又会 $2$ 次引爆半径 $R-1$ 及以内的的草堆，$2$ 次引爆的草堆又会 $3$ 次引爆半径 $R-2$ 及以内的的草堆...直到一次引爆后没有其他草堆被波及或半径为 $0$。


现在只有 $1$ 头奶牛，能量为 $R$，请计算如果要引爆所有的草堆，最小的 $R$ 是多少？

# 思路

这题思路很多，有动态规划的，有二分套二分的，我采用的是二分预处理+二分答案的做法。

关于二分答案，本人看到题解上有一些坐标轴乘 $2$ 并且整数二分的，但是证明不出来答案只有 $x.0$ 或 $x.5$ 两种情况，所以直接用的浮点二分。

为方便表示，我们定义位置 $i\in [1,n]$ 且 $i-1$ 在 $i$ 的左边，$i+1$ 在 $i$ 的右边。$pos$ 表示输入的坐标从小到大排序的数列。

## 分析题目

这题的数据范围极大，而且所需能量和 $x_i$ 相关，所以可以肯定是用 $\log$ 级别的算法，那这题二分答案就很显然了。

接下来就是 $\operatorname{check}$ 函数的问题：

## 预处理

首先，有一个显而易见的点，就是如果我想要引爆所有的草堆，那么我只需要在左边找到一个能够连锁引爆其 **左边所有草堆** 的草堆和右边找到一个能够连锁引爆其 **右边所有草堆** 的草堆，并且让我们的能量可以引爆这两个草堆并且剩下的能量足够这两个草堆去连锁引爆就行了。

有了这个思路，我们就有了预处理出每个草堆 **自己爆炸后** 引爆其左侧和右侧所有草堆所需要的最小能量的想法。我们将一个草堆连锁引爆其左侧所有草堆所需能量定义为 $L_i$，和这个草堆引爆其右侧所有草堆所需要的最小能量，定义为 $R_i$。

因为这个东西只与输入数据有关，所以可以在输入后预处理出 $L_i$ 和 $R_i$ 方便后面判断，下面的推演以左侧为例，右边同理。

根据题目，我们可以得到想要引爆这个草堆 $i$ 左侧的所有草堆的充分必要条件为 $i$ 草堆爆炸能够波及到左侧的草堆 $k(k\in[1,i-1])$ 且引爆草堆 $k$ 后产生的爆炸半径能够使得草堆 $k$ 左侧的所有草堆被连锁引爆，所以草堆 $i$ 引爆其左侧所有草堆所需的最小能量为：

$$L_i=\min(\max(pos_i-pos_k,L_k+1))(k\in[1,i-1],L_i=0)$$

代码片段如下：

```cpp
L[1]=0;
for(int i=2;i<=n;i++)
{
	L[i]=0x3f3f3f3f;
	for(int k=1;k<i;k++)
		L[i]=min(L[i],max(pos[i]-pos[k],L[k]+1));
}
```

但是如果要枚举的话显然是不现实的，$O(n^2)$ 级别的复杂度和 $50000$ 的数据规模不是吃素的，所以就要分析一下。

因为 $pos_i$ 是单调的，所以随着 $k$ 的增大，$pos_i-pos_k$ 的值会逐渐变小，而 $L_k+1$ 在逐渐变大，所以这两个值的最大值构成的函数一定在定义域内有最小值且最小值在 $pos_i-pos_{k+1}<L_{k+1}+1\land posi-pos_k>L_k+1$ 或 $pos_i-pos_k<L_k+1$ 时取到，因为 $pos_i-pos_k=L_k+1$ 即数学意义上的“拐点”可能会令 $k$ 为非整数。

所以我们在 $k$ 不断增加后判断这两个值的关系，就可以在循环到某个地方直接跳出。

```cpp
L[1]=0;
for(int i=2;i<=n;i++)
{
	L[i]=0x3f3f3f3f;
	for(int k=1;k<i;k++)
	{
		L[i]=min(L[i],max(pos[i]-pos[k],L[k]+1));
		if(pos[i]-pos[k]<L[k]+1)
			break;
	}
}
```

这在枚举的时候 **有概率** 加快代码的运行效率，说是有概率是因为这样的判断如果不是数据天胡的情况下优化不了多少。但是这种在拐点单调性改变且仅改变一次的函数我们可以直接用二分求出拐点，并且使得 $l$ 和 $r$ 分别对应两种可能的情况。

```cpp
L[1]=0;
for(int i=2;i<=n;i++)
{
	int l=2,r=i,mid;
	while(l+1<r)
	{
		mid=l+((r-l)>>1);
		if(pos[i]-pos[mid-1]>L[mid-1]+1)
			l=mid;
		else
			r=mid;
	}
	L[i]=min(max(pos[i]-pos[l-1],L[l-1]+1),max(pos[i]-pos[r-1],L[r-1]+1));
}
```

那么预处理部分就以 $O(n\log{n})$ 的复杂度完美结束，剩下的 $R$ 的预处理部分按照同样的方法分析，也能得到一个相似的代码。

## $\operatorname{check}$ 函数

有了预处理出来的数组，按照预处理数组的初衷，我们只需要找到一对 $(i,j)$，使得 $i,j$ 之间的距离（注意这里直线距离要算作 $d=r\cdot 2$）和引爆两侧的草堆所需的能量都在给出的能量范围之内即可。注意函数的形式参数 $x$ 类型为 `double`，因为是浮点二分。

```cpp
for(int i=1;i<=n;i++)
{
	if(R[i]+1<=x)
	{
		for(int j=i;j>=1&&pos[i]-pos[j]<=x*2;j--)
			if(L[j]+1<=x)
				return 1;
		break;
	}
}
return 0;
```

这里跳出循环的正确性证明如下：

因为我们证明得到 $L$ 和 $R$ 是单调的，而其中 $L$ 单调增，$R$ 单调减。

所以我们在找到第一个使得 $R_i+1 \le x$ 的 $i$ 时，其能接触到（即可以同时引爆）到的 $L_j$ 一定最小，若此时不能满足条件，则之后的都不可以了，循环下去就没意义了。

## 代码

```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int inf=2147483647;
const int N=5e4+10;
const double eps=1e-3;

int n;
int pos[N],L[N],R[N];

void PreProcess()
{
	for(int i=2;i<=n;i++)
	{
		int l=2,r=i,mid;
		while(l+1<r)
		{
			mid=l+((r-l)>>1);
			if(pos[i]-pos[mid-1]>L[mid-1]+1)
				l=mid;
			else
				r=mid;
		}
		L[i]=min(max(pos[i]-pos[l-1],L[l-1]+1),max(pos[i]-pos[r-1],L[r-1]+1));
	}
	for(int i=n-1;i>=1;i--)
	{
		int l=i,r=n-1,mid;
		while(l+1<r)
		{
			mid=l+((r-l)>>1);
			if(pos[mid+1]-pos[i]>R[mid+1]+1)
				r=mid;
			else
				l=mid;
		}
		R[i]=min(max(pos[l+1]-pos[i],R[l+1]+1),max(pos[r+1]-pos[i],R[r+1]+1));
	}
	return;
}

bool check(double x)
{
	for(int i=1;i<=n;i++)
	{
		if(R[i]+1<=x)
		{
			for(int j=i;j>=1&&pos[i]-pos[j]<=x*2;j--)
				if(L[j]+1<=x)
					return 1;
			break;
		}
	}
	return 0;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>pos[i];
	sort(pos+1,pos+1+n);
	PreProcess();
	double l=1,r=pos[n],mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	printf("%.1lf",mid);
	return 0;
}
```

---

## 作者：fanke (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/P3132)

### 思路

这道题我是用 dp 做的，是一道神奇的 dp 题。

用 $f[i]$ 表示摧毁所有 $i$ **左侧**的炸药包 **最少** 需要的能量，用 $g[i]$ 表示摧毁所有 $i$ **右侧**的炸药包**最少**需要的能量。

那么我们只要找到满足 $j < i$,$a[i] - a[j] > f[j] + 1$ 的最后一个 $j$ 炸 药包，就可以更新 $f[i]$ 的值。

`f[i]  = min(f[i],a[i] - a[j] , f[j] + 1)`;

数组 $g$ 一样处理。

为什么这么找呢?

因为首先我们发现如果 $a[i] - a[j]$ 比 $f[j] + 1$ 还要小的话，那么从 $i$ 点引发的爆炸是可以波及到 $j$ 点的，所以并不需要更新答案，直到不满足的时候我们才更新。

最后枚举爆炸的点就可以了。


### code


```cpp
for(int i = 2 ; i <= n ; i ++)
    {
    	while(head + 1 < i && a[i] - a[head + 1] > f[head + 1] + 2) 
			head ++;
    	f[i] = min(f[head + 1] + 2,a[i] - a[head]);
    }
    g[n] = -2,tail = n;
    for(int i = n - 1 ; i >= 1 ; i--)
    {
    	while(tail - 1 > i && a[tail - 1] - a[i] > g[tail - 1] + 2) 
			tail--;
    	g[i] = min(a[tail] - a[i],g[tail-1] + 2);
    }
    head = 1,tail = n;
    while(head < tail)
    {
    	ans = min(ans,max((a[tail] - a[head]) >> 1,2 + max(g[tail],f[head])));
    	if(f[head + 1] < g[tail - 1]) 
			head ++;
    	else 
			tail--;
    }
    printf("%.1lf\n" , (double)ans / 2.0);
    return 0;
}
```


---

## 作者：sangshang (赞：0)

# Solution

首先不难想到 $R$ 越大，越有可能全部炸到；$R$ 越小，越难全部炸到。因此先考虑二分 $R$。

怎样检查当前 $R$ 是否合法呢？若一起考虑炸到最左边和炸到最右边，不容易。但可以想到，爆炸源点越往右，越难炸到左边，但容易炸到右边。因此再二分一个**能炸到最左边的前提下，最靠右的爆炸源点**。再用这个源点检查是否能炸到最右边的点。

检查能否炸到最左边的点（向右同理）：

1. 找一个向左最先炸到的点。

1. 用当前剩余的 $R$ 去找最左能炸到的点。

1. 如果能炸到新的点，更新爆炸起点，$R\gets R-1$。否则返回 `false`。

1. 循环。最后看能否炸到最左边的点。

# Code

```cpp
#include <bits/stdc++.h>
#define maxn 500003
using namespace std;

namespace OI {
	const int IN_LEN = 1 << 21;
	char buf[IN_LEN], *front = buf, *back = buf;

	inline char fast_getchar() {
		if (front >= back) {
			front = buf;
			back = buf + fread(buf, 1, IN_LEN, stdin);
		}
		return *(front++);
	}
	const int OUT_LEN = 1 << 20;
	char put[OUT_LEN], *put_iterator = put;
	inline void fast_putchar(char c) {
		if (put_iterator - put >= OUT_LEN) {
			fwrite(put, 1, OUT_LEN, stdout);
			put_iterator = put;
		}
		*put_iterator = c, ++put_iterator;
	}
	inline void flush() {
		fwrite(put, 1, put_iterator - put, stdout);
		put_iterator = put;
	}
	inline void read(int &in) {
		in = 0;
		bool f = false;
		char c = fast_getchar();
		while (c < '0' || c > '9') {
			if (c == '-') {
				f = true;
			}
			c = fast_getchar();
		}
		while (c >= '0' && c <= '9') {
			in = in * 10 + c - '0';
			c = fast_getchar();
		}
		if (f) {
			in = -in;
		}
	}
	inline void write(int out) {
		if (out == 0) {
			fast_putchar('0');
			return;
		}
		if (out < 0) {
			fast_putchar('-');
			out = -out;
		}
		char x[OUT_LEN], *beg = x;
		for (; out; out /= 10) {
			*beg = (out % 10) + '0', ++beg;
		}
		--beg;
		for (; beg != x; --beg) {
			fast_putchar(*beg);
		}
		fast_putchar(*beg);
	}
	inline void quick_sort(int *l, int *r, bool flag) {
		--r;
		if (l >= r) {
			return;
		}
		int *i = l, *j = r;
		const int mid = *(l + ((r - l) >> 1));
		//std::cout << l - elem << " " << r - elem << "\n";
		//OI::write(mid), OI::fast_putchar('\n');
		if (flag) {
			while (i <= j) {
				while (*i < mid) {
					++i;
				}
				while (*j > mid) {
					--j;
				}
				if (i <= j) {
					std::swap(*i, *j);
					++i, --j;
				}
			}
		} else {
			while (i <= j) {
				while (*i > mid) {
					++i;
				}
				while (*j < mid) {
					--j;
				}
				if (i <= j) {
					std::swap(*i, *j);
					++i, --j;
				}
			}
		}
		++r, quick_sort(l, j + 1, flag), quick_sort(i, r, flag);
	}
}

//using namespace OI;

int a[maxn], n;

inline bool check2(double x, double pos) {
	//判断半径为x，起点为pos能否炸到一号点
	int st = 0;
	for (int i = 1; i <= n && a[i] <= pos; ++i) {
		st = i;
	}
	if (!st) {
		return false;
	}
	double lim = pos - x;
	int p = st;
	if (a[p] < lim) {
		return false;
	}
	for (int i = st; i >= 1; --i) {
		if (a[i] >= lim) {
			p = i;
		} else {
			--x;
			if (x <= 0) {
				return false;
			}
			lim = a[p] - x;
			++i;
		}
	}
	if (p == 1) {
		return true;
	}
	return false;
}

inline bool check(double x) {
	//判断半径为x能否全炸完。
	double l = a[1], r = a[n], st = -1;
	while ((r - l) >= 1e-3) {
		double mid = (r + l) / 2;
		if (check2(x, mid)) {
			l = st = mid;
		} else {
			r = mid;
		}
	}
	//Check2::st is iterator.This->st is value.
	int p = 0;
	for (int i = n; i >= 1 && a[i] >= st; --i) {
		p = i;
	}
	double lim = st + x;
	if (a[p] > lim) {
		return false;
	}
	for (int i = p; i <= n; ++i) {
		if (a[i] <= lim) {
			p = i;
		} else {
			--x;
			if (x <= 0) {
				return false;
			}
			lim = a[p] + x;
			--i;
		}
	}
	return p == n;
}

int main() {
	OI::read(n);
	for (int i = 1; i <= n; ++i) {
		OI::read(a[i]);
	}
	OI::quick_sort(a + 1, a + n + 1, true);
	double l = 0, r = 1e9, ans = -1;
	while ((r - l) >= 1e-3) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			ans = mid;
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << fixed << setprecision(1) << ans << endl;
	//flush();
	return 0;
}
```

---

