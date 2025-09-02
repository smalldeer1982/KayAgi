# [USACO18JAN] Sprinklers P

## 题目描述

农夫约翰有块田，这块田可视为一个 $N×N$  的正方形网格。西南角为 $(0,0)$ ，东北角为 $(N-1, N-1)$ 。  
在某些格子中有双头喷头，每一个都能够同时喷洒水和肥料。一个位于 $(i,j)$  的双头喷头会
* 将水洒在所有满足 $N≥x≥i,$  $N≥y≥j$  的格子 $(x,y)$  上；
* 将肥料洒在所有满足 $0≤x≤i$  和 $0≤y≤j$  的格子 $(x,y)$  上。

农民约翰想在这块田里切割出一个矩形种甜玉米。矩形的边不能把格子切开。矩形内的所有格子都必须能由双头喷头灌溉和施肥。  
求切割矩形的方案数。由于这个数字可能很大，所以输出对 $10^9+7$  取模。

## 样例 #1

### 输入

```
5
0 4
1 1
2 2
3 0
4 3```

### 输出

```
21```

# 题解

## 作者：whiteqwq (赞：8)

[P4184 [USACO18JAN]Sprinklers P](https://www.luogu.com.cn/problem/P4184)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1785840)

第$600$道紫题，庆祝一下。

## 题意
有一个$n\times n$的矩阵，有$n$个关键点落在格点上（保证每行与每列有且仅有一个），求有多少个非空子矩阵满足左上方有一个关键点，右下方也有一个关键点（两个关键点均可以落在矩阵的边缘）。（$1\leqslant n\leqslant 10^5$）

## 分析
题解里差分写法看不懂，来一发比较套路的dp优化吧。

首先不难发现能选用的格点会形成一个类似这样的图形：
```
.xxx.
.xxx.
.xxx.
xxxx.
xxxx.
```
每一行能选用的格点是连续的，且左端点，右端点随着行数的增加而不断左移。

那么就很容易预处理：$l_i$（代表第$i$行区间的左端点的列号），$r_i$（代表第$i$行区间的右端点的列号），$up_i$（表示第$i$列能选用的最上方格点的行号）

然后就可以列出式子（$(i,j)$为矩阵的右下角，$(p,k)$为矩阵的左上角）：

$$\sum_{i=1}^n\sum_{j=l_i}^{r_i}\sum_{k=l_i}^{j-1}\sum_{p=up_k}^{i-1}1$$

那么剩下的工作就很显然了，这个式子可以优化到$O(n)$，有经验的选手可以跳过下面的部分。

$$\sum_{i=1}^n\sum_{j=l_i}^{r_i}\sum_{k=l_i}^{j-1}\sum_{p=up_k}^{i-1}1=\sum_{i=1}^n\sum_{j=l_i}^{r_i}\sum_{k=l_i}^{j-1}i-up_k=\sum_{i=1}^n(\sum_{j=l_i}^{r_i}(j-l_i\times i)-\sum_{k=l_i}^{r_i-1}\sum_{j=k+1}^{r_i}up_k)\\=\sum_{i=1}^n(\frac{(r_i-l_i+1)(r_i-l_i)}{2}\times i-\sum_{k=l_i}^{r_i-1}(r_i-k)\times up_k)$$

设$sum1_x=\sum_{i=1}^x up_i,sum2_x=\sum_{i=1}^x i\times up_i$，那么就可以继续化：

$$\sum_{i=1}^n\sum_{j=l_i}^{r_i}\sum_{k=l_i}^{j-1}\sum_{p=up_k}^{i-1}1=\sum_{i=1}^n(\frac{(r_i-l_i+1)(r_i-l_i)}{2}\times i-r_i\times(sum1_{r_i-1}-sum1_{l_i-1})+(sum2_{r_i-1}-sum2_{l_i-1}))$$

利用关键点的坐标为$[0,n-1]$的整数，很容易做到$O(n)$。

## 代码
注意题目中关键点的坐标是从$0$开始的。
```
#include<stdio.h>
const int maxn=100005,mod=1000000007;
int n,pos,ans;
int l[maxn],r[maxn],up[maxn],y[maxn],sum1[maxn],sum2[maxn];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		a++,b++,y[a]=b;
	}
	l[0]=n;
	for(int i=1;i<=n;i++)
		l[i]=min(l[i-1],y[i]);
	r[n+1]=0;
	for(int i=n;i>=1;i--)
		r[i]=max(r[i+1],y[i]);
	pos=r[1];
	for(int i=1;i<=n;i++)
		while(pos>=1&&pos>=l[i])
			up[pos]=i,pos--;
	for(int i=1;i<=n;i++)
		sum1[i]=(sum1[i-1]+up[i])%mod;
	for(int i=1;i<=n;i++)
		sum2[i]=(sum2[i-1]+1ll*i*up[i]%mod)%mod;
	for(int i=1;i<=n;i++)
		ans=(ans+1ll*i*(1ll*(r[i]-l[i])*(r[i]-l[i]+1)/2ll%mod)%mod-1ll*(sum1[r[i]-1]-sum1[l[i]-1]+mod)%mod*r[i]%mod+(sum2[r[i]-1]-sum2[l[i]-1]+mod)%mod)%mod;
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：5)

~~模拟赛2h上肝出此题，故发题解纪念一下~~

首先，我们先根据样例画一幅图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p0jexiz9.png)

其中，粉色格子是肥料和水全喷到的地方。

我们发现，对于一行里面，粉色格子的左界是**在这一行上面的所有蓝点中，最靠左的那一个**，而右界是**在这一行下面的所有蓝点中，最靠右的那一个**。

如果这不太清楚的话，我们再提供一组样例及它对应的图：

```
11
0 5
1 4
2 8
3 3
4 2
5 1
6 10
7 6
8 0
9 9
10 7
```
![](https://cdn.luogu.com.cn/upload/image_hosting/48ixhw6a.png)

是不是明白了？

我们接下来考虑如何对于一行求答案。设每一行的左界是$dw_i$，右界是$up_i$。

则我们将第$i$行当作矩形下界，枚举一个$j\leq i$当作矩形上界。则矩形左界是$dw_j$，右界是$up_i$。设$L=dw_j,R=up_i$，则以$i$为下界，$j$为上界的矩形的方案数为$\dfrac{(R-L)(R-L+1)}{2}$。

这样预处理出来$up$和$dw$后，枚举$i$和$j$，复杂度就是$O(n^2)$的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,up[100100],dw[100100],res;
pair<int,int>p[100100];
int main(){
	scanf("%d",&n),dw[0]=0x3f3f3f3f;
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	for(int i=n-1;i;i--)up[i]=max(up[i+1],p[i+1].second);
	for(int i=1;i<n;i++)dw[i]=min(dw[i-1],p[i].second);
//	for(int i=1;i<n;i++)printf("%d %d\n",up[i],dw[i]);
	for(int i=1;i<n;i++)for(int j=i;j>=1&&dw[j]<up[i];j--)(res+=(1ll*(up[i]-dw[j])*(up[i]-dw[j]+1)/2)%mod)%=mod;
	printf("%lld\n",res);
	return 0;
} 
```
然后，考虑优化。

当$i$增加的时候，最大的有$L\leq R$的$j$也是递增的。因为对于$\dfrac{(R-L)(R-L+1)}{2}$差分后，得到$\dfrac{(R-L)(R-L+1)}{2}=\sum\limits_{i=0}^{R-L}i$，因此我们可以通过差分地更新它。

具体地说，我们设两个值$k$和$l$，其中$k=\sum\limits_{q=j}^{i}R_q-L_q$，$l=\sum\limits_{q=j}^{i}\dfrac{(R_q-L_q)(R_q-L_q+1)}{2}$。

则，当$R$减小$1$时，有$l$减小$k$和$k$减小$(i-j+1)$。

因此就可以差分地在$O(n)$时间内完成。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,up[100100],dw[100100],res;
pair<int,int>p[100100];
int main(){
	scanf("%d",&n),dw[0]=up[0]=n;
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	for(int i=n-1;i;i--)up[i]=max(up[i+1],p[i+1].second);
	for(int i=1;i<n;i++)dw[i]=min(dw[i-1],p[i].second);
//	for(int i=1;i<n;i++)printf("U:%d D:%d\n",up[i],dw[i]);
	for(int i=1,j=1,k=0,l=0;i<n;i++){
		if(up[i-1]>=dw[i])(k+=up[i-1]-dw[i])%=mod,(l+=(1ll*(up[i-1]-dw[i])*(up[i-1]-dw[i]+1)/2)%mod)%=mod;
		for(int q=up[i-1];q>up[i];q--){
			while(dw[j]==q)j++;
			(l-=k)%=mod,(k-=(i-j+1))%=mod;
		}
//		printf("(%d,%d,%d,%d)\n",i,j,k,l);
		(res+=l)%=mod;
	}
	printf("%lld\n",res);
	return 0;
} 
```


---

## 作者：夏色祭 (赞：2)

思路楼下的爷讲的已经很清楚了。

补充几点：

1."有一些可接受的区间[L，R]作为Y2的值"可接受的区间$[L,R]$的L和R是单调不增的。

2."第一个量可以用一个简单的公式来计算"简单的公式是:$\frac{R(R+1)}{2}*X2$

3."计算这一个量又有一个简单的封闭形式的公式"简单的封闭形式的公式是:$\frac{(2R-L+1)L}{2}*X2$

4."有一些left（y）"$left_{y}$指第y列从左往右第一个合法的点左边那个点的x。

Orz Oscar写的线段树~~虽然我一开始思路也是线段树(逃~~

```
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
#define ll long long
#define For(i,x,y) for (register int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (register int i=(x);i>=(y);i--)
#define cross(i,k) for (register int i=first[k];i;i=last[i])
inline ll read(){
    ll x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 1e5+10, mod = 1e9+7;
int n,x,y,a[N],l[N],r[N],L[N];
ll sum1,sum2,sum3,ans,sum[N],Sum[N];
int main(){
	n=read();
	For(i,1,n) x=read(),y=read(),a[x]=y;
	l[0]=a[0];
	For(i,1,n-1) l[i]=min(l[i-1],a[i]);
	Dow(i,n-1,0) r[i]=max(r[i+1],a[i]);
	For(i,l[0],n-1) L[i]=0;
	For(i,1,n-1)
		if (l[i]!=l[i-1]) For(j,l[i],l[i-1]-1) L[j]=i;
	For(i,0,l[n-1]-1) L[i]=n;
	Dow(i,n-1,0) sum[i]=(sum[i+1]+L[i])%mod;
	Dow(i,n-1,0) Sum[i]=(Sum[i+1]+1ll*L[i]*(n-1-i))%mod;
	For(i,0,n-1){
		sum1=1ll*(1+r[i])*r[i]*i/2%mod;
		sum2=1ll*(2*r[i]-l[i]+1)*l[i]/2*i%mod;
		sum3=Sum[l[i]]-Sum[r[i]+1]-1ll*(sum[l[i]]-sum[r[i]+1])*(n-1-r[i])%mod;
		for ((ans+=sum1-sum2-sum3)%=mod;ans<0;ans+=mod){}
	}
	printf("%lld",ans);
}
```

---

## 作者：daniEl_lElE (赞：1)

记 $minv_i$ 为 $i$ 行及以前列编号最小的喷头的列编号，$maxv_i$ 为 $i$ 行及以后列编号最大的喷头的列编号。

考虑一个上面在 $x$ 行，下面在 $y$ 行的矩形。不难发现他的列 $l,r$ 一定满足 $minv_x\leq l\leq r<maxv_y$。

考虑用一线段树维护列右边在 $r$ 时，前面所有行**不符合要求**的 $l$ 总共有多少个，用另一个线段树维护列右边在 $r$，存在 $l$ 符合要求的列数。

容易发现答案就是第二个线段树 $maxv_y-1$ 位置的前缀和乘上 $maxv_y$ 再减去第一个线段树 $maxv_y-1$ 位置的前缀和。修改是容易的，每次添加一行相当于给 $minv_x\sim n$ 位置的第二个线段树加上 $1$，第一个线段树每个位置加上这个位置的编号。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1) 
#define int long long
using namespace std;
const int mod=1e9+7;
int col[100005],minv[100005],maxv[100005],qz[100005];
struct sgt{
	int siz[400005],f[400005],lzt[400005];
	void pushdown(int i){
		(f[i*2]+=lzt[i]*siz[i*2])%=mod;
		(f[i*2+1]+=lzt[i]*siz[i*2+1])%=mod;
		(lzt[i*2]+=lzt[i])%=mod;
		(lzt[i*2+1]+=lzt[i])%=mod;
		lzt[i]=0;
	}
	void pushup(int i){
		f[i]=(f[i*2]+f[i*2+1])%mod;
		siz[i]=(siz[i*2]+siz[i*2+1])%mod;
	}
	void build(int i,int l,int r){
		if(l==r){
			siz[i]=qz[l];
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		pushup(i);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			(lzt[i]+=cg)%=mod;
			(f[i]+=siz[i]*cg)%=mod;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		pushup(i);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 0;
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return (qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr))%mod;
	}
}tree1,tree2;
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		int u,v; cin>>u>>v;
		col[u+1]=v+1;
	}
	for(int i=1;i<=n;i++) minv[i]=maxv[i]=col[i];
	for(int i=2;i<=n;i++) minv[i]=min(minv[i],minv[i-1]);
	for(int i=n-1;i>=1;i--) maxv[i]=max(maxv[i],maxv[i+1]);
	for(int i=1;i<=n;i++) qz[i]=i; tree1.build(1,1,n);
	for(int i=1;i<=n;i++) qz[i]=1; tree2.build(1,1,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		(ans+=tree2.qry(1,1,n,1,maxv[i]-1)*(maxv[i])%mod+mod-tree1.qry(1,1,n,1,maxv[i]-1))%=mod;
		tree1.change(1,1,n,minv[i],n,1);
		tree2.change(1,1,n,minv[i],n,1);
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Tsawke (赞：1)

# [LG-P4184 [USACO18JAN]Sprinklers P](https://www.luogu.com.cn/problem/P4184) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P4184-Solution)

### 题面

$ n \times n $ 的网格图（$ n $个格点，从 $ (0, 0) $ 到 $ (n - 1, n - 1) $），给定 $ n $ 个点的坐标 $ (i, j) $，保证任意两个坐标的横或纵均不相等，每个点会对 $ \forall(x, y), x \in [i, n - 1], y \in [j, n - 1] $ 进行洒水，对 $ \forall(x, y), x \in [0, i], y \in [0, j] $ 进行施肥，要求选出一片矩形，使得其中每个格点都既浇水又施肥，求方案数。

或者也可以描述为，给定 $ n $ 个关键点，要求选一个矩形使得其中左上右下各自至少有一个关键点，求方案数。

$ 1 \le n \le 10^5 $。

### Solution

前言：核心思路参考自 [这篇Blog](https://www.luogu.com.cn/blog/xiaoziyaoxzy/solution-p4184)，主要是我太弱了，有点没太看懂这个大佬柿子的精妙推导，于是尝试自己推了一遍，用比较低端的方法也成功推到 $ O(n) $ 了，故提供一种更无脑一些的推柿子的方法。

一道奇怪的题，最终可以转化为无脑推柿子。

首先借一个题解区的图（图片来自 [这篇Blog](https://www.luogu.com.cn/blog/Troverld/solution-p4184)）：

![从Luogu搬的图，如果你看到这段文字那么说明Luogu的图挂了](https://cdn.luogu.com.cn/upload/image_hosting/48ixhw6a.png)

不难发现一个妙妙性质，即在第 $ i $ 行里，我们假设可行的矩形的左右端点为 $ [l_i, r_i] $，那么 $ l_i $ 即为在其**不在**其下面的所有关键点横坐标的最小值，$ r_i $ 为**不在**其上面的最大值，按照这个规律我们也可以处理出来对于每一列纵坐标可行的最小值 $ up_i $，然后可以写一个 $ O(n^4) $ 的类似二位数~~点~~矩形的东西，再化简。前面这里如果还是看不懂可以去翻翻题解区，这里不再重复赘述。令 $ (i, j) $ 为右下端点，$ (x, y) $ 为左上端点，有答案为：
$$
\begin{aligned}
\sum_{i = 1}^{n} \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1} \sum_{x = up_y}^{i - 1} 1
	&= \sum_{i = 1}^{n} \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1}(i - up_y) \\
	&= \sum_{i = 1}^{n}\left( \sum_{j = l_i}^{r_i}(j - l_i)i - \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1}up_y \right) \\
	&= \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(l_i + r_i)(r_i - l_i + 1) - (r_i - l_i + 1)l_i \right) - \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1}up_y \right) \\
	&= \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1}up_y \right)
\end{aligned}
$$
然后我们令 $ sum1_n = \sum_{i = 1}^{n}up_i $，再令 $ sum2_n = \sum_{i = 1}^{n}sum1_i $，有：
$$
\begin{aligned}
&\sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - \sum_{j = l_i}^{r_i} \sum_{y = l_i}^{j - 1}up_y \right) \\
	=& \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - \sum_{j = l_i}^{r_i}(sum1_{j - 1} - sum1_{l_i - 1}) \right) \\
	=& \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - \sum_{j = l_i}^{r_i}sum1_{j - 1} + (r_i - l_i + 1)sum1_{l_i - 1} \right) \\
	=& \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - \sum_{j = l_i - 1}^{r_i - 1}sum1_{j} + (r_i - l_i + 1)sum1_{l_i - 1} \right) \\
	=& \sum_{i = 1}^{n}\left( i\left( \dfrac{1}{2}(r_i - l_i)(r_i - l_i + 1) \right) - sum2_{r_i - 1} + sum2_{l_i - 2} + (r_i - l_i + 1)sum1_{l_i - 1} \right)
\end{aligned}
$$
然后就成功从 $ O(n^4) $ 推到 $ O(n) $ 了。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (ll)(1e9 + 7)
#define GetSum1(x) ((x) > 0 ? sum1[x] : 0)
#define GetSum2(x) ((x) > 0 ? sum2[x] : 0)

template< typename T = int >
inline T read(void);

int N;
int y[110000];
int l[110000], r[110000], up[110000];
ll sum1[110000];
ll sum2[110000];

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        int rx = read() + 1, ry = read() + 1;
        y[rx] = ry;
    }l[0] = INT_MAX; r[N + 1] = -1;
    for(int i = 1; i <= N; ++i)l[i] = min(l[i - 1], y[i]);
    for(int i = N; i >= 1; --i)r[i] = max(r[i + 1], y[i]);
    int cur = r[1];
    for(int i = 1; i <= N; ++i)while(cur && cur >= l[i])up[cur] = i, --cur;
    for(int i = 1; i <= N; ++i)sum1[i] = (sum1[i - 1] + up[i]) % MOD;
    for(int i = 1; i <= N; ++i)sum2[i] = (sum2[i - 1] + sum1[i]) % MOD;
    ll ans(0);
    for(int i = 1; i <= N; ++i){
        ans = (ans + ((ll)r[i] - l[i]) * (r[i] - l[i] + 1) / 2ll % MOD * i % MOD) % MOD;
        ans = (ans - GetSum2(r[i] - 1) + GetSum2(l[i] - 2) + MOD) % MOD;
        ans = (ans + ((ll)r[i] - l[i] + 1) * GetSum1(l[i] - 1) % MOD) % MOD;
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_11_03 初稿

---

## 作者：阿陶陶陶 (赞：1)

[P4184 \[USACO18JAN\]Sprinklers P](https://www.luogu.com.cn/problem/P4184) ：

来提供一个小常数跑的飞快的树状数组 $O(nlogn)$ 做法，思维也比较简洁。

### 暴力

我们首先可以预处理出每一行被水和肥料覆盖的范围，然后枚举矩形上下两条边所在的行，这时矩形的左右边界变化范围是确定的，具体的说，记第 $i$ 行被水洒到的范围是 $[w_i,n-1]$ ，被肥料洒到的范围是 $[0,f_i]$ ，则上边界为 $j$ ，下边界为 $i$ 的矩形的左右边界变化范围就是 $[w_j,f_i]$ ，这就变成了一个线段计数问题，所有这样的矩形的个数就是 $\dfrac {(f_i-w_j)(f_i-w_j+1)}{2}$ ，我们对于所有 $w_j \leq f_i$ 的 $i,j$ 累加答案即可：

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=1e5+10,M=1e6+10,INF=0x3f3f3f3f,mod=1e9+7,inv2=5e8+4;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

int n,water[N],fat[N];
int node[N];

int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		int x=read(),y=read();
		node[x]=y;
	}
	for(int i=0,now=n-1;i<n;++i)
	{
		now=min(now,node[i]);
		water[i]=now;
	}
	for(int i=n-1,now=0;i>=0;--i)
	{
		now=max(now,node[i]);
		fat[i]=now;
	}
	LL ans=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<i;++j)
		{
			if(water[j]>=fat[i])	continue;
			ans=(ans+1ll*(fat[i]-water[j])*(fat[i]-water[j]+1)%mod*inv2%mod)%mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```

然后交上去发现只有 $8$ 分……~~搞不好还是样例分~~，我们需要优化。

### 优化

我们观察暴力的求和式：
$$
Ans=\sum_{i=0}^{n-1}\sum_{j=0}^{i-1}[w_j\leq f_i]\dfrac{(f_i-w_j)(f_i-w_j+1)}{2}
$$
将其展开：
$$
Ans=\dfrac{1}{2}\sum_{i=0}^{n-1}\sum_{j=0}^{i-1}[w_j\leq f_i]{(f_i^2+f_i-2f_iw_j-w_j+w_j^2)}
$$
记:
$$
A=\sum_{j=0}^{i-1}[w_j\leq f_i]
$$

$$
B=\sum_{j=0}^{i-1}[w_j\leq f_i]w_j
$$

$$
C=\sum_{j=0}^{i-1}[w_j\leq f_i]w_j^2
$$

则原式化为：
$$
Ans=\dfrac{1}{2}\sum_{i=0}^{n-1}[A(f_i^2+f_i)-B(2f_i+1)+C]
$$
对于一个确定的 $i$ ， $f_i$ 的值是一个常数，问题转化为如何快速求出：
$$
\sum_{j=0}^{i-1}[w_j\leq f_i]
$$

$$
\sum_{j=0}^{i-1}[w_j\leq f_i]w_j
$$

$$
\sum_{j=0}^{i-1}[w_j\leq f_i]w_j^2
$$

在上面三个求和式中有两个限制条件，其一是 $j<i$ ，另一个是 $w_j\leq f_i$ ，只需要用三个树状数组分别维护 $w$ 的零次项、一次项、二次项的前缀和，询问时查询 $\leq f_i$ 的答案，在对每个 $i$ 求出答案后，将当前的 $w_i$ 位置分别给三个树状数组加上对应的值即可。

树状数组的小常数跑的飞快，在不开 $O2$ 的情况下 $306ms$ ，在最优解排名里也比较靠前。

$Code:$ 

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=1e5+10,M=1e6+10,INF=0x3f3f3f3f,mod=1e9+7,inv2=5e8+4;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

int n,water[N],fat[N];
int node[N];

struct BIT
{
	LL val[N];
	void add(int p,LL v)
	{
		++p;
		for(;p<n;p+=p&(-p))
			val[p]+=v;
	}
	LL ask(int p)
	{
		++p;
		LL res=0;
		for(;p;p-=p&(-p))
			res+=val[p];
		return res;
	}
}t1,tw,tw2;

int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		int x=read(),y=read();
		node[x]=y;
	}
	for(int i=0,now=n-1;i<n;++i)
	{
		now=min(now,node[i]);
		water[i]=now;
	}
	for(int i=n-1,now=0;i>=0;--i)
	{
		now=max(now,node[i]);
		fat[i]=now;
	}
	LL ans=0;
	for(int i=0;i<n;++i)
	{
		LL now=0;
		now=(now+(t1.ask(fat[i])*fat[i]%mod*(fat[i]+1)%mod)%mod)%mod;
		now=((now-tw.ask(fat[i])*(2ll*fat[i]%mod+1)%mod)%mod+mod)%mod;
		now=(now+tw2.ask(fat[i]))%mod;
		ans=(ans+now*inv2%mod)%mod;
		t1.add(water[i],1);
		tw.add(water[i],water[i]);
		tw2.add(water[i],1ll*water[i]*water[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：babingbaboom (赞：1)

我们基本上是要求计算格点对的个数（x1，y1），（x2，y2），其中X1 < X2，Y1 < Y2 ，且在N×N的方格中，在每一列有间隔的点。此外，当x轴的横坐标增加，对应的列减少或保持相同的终点。



线性扫描X2。对于每个X2，有一些可接受的区间[L，R]作为Y2的值。不去计算可接受的三元组数（X1，Y1，Y2），我们将计算X1＜X2，Y1 < Y2且L≤Y2≤R的三元组数目，并从三元组总数减去这个数。



注意如果Y2＜L，那么Y1＜L，因此对于区间端点的单调性，（x1，y1）它本身是一个不可接受的点。因此我们可以完全不考虑Y2≥l。



我们必须计算两个量：



1）所有（x1，y1）中，X1＜X2，Y1 < Y2 ≤R的总数。



2）所有不可接受的（x1，y1）中，X1＜X2，Y1 < Y2 ≤R的总数。



第一个量可以用一个简单的公式来计算。对于计算第二个量，我们把它分为两个量：y1＜R的总和，和y1≥R的总和.



如果Y1＜R，那么（x1，y1）对于所有X1＜X2都是一个不可接受的点，所以计算这一个量又有一个简单的封闭形式的公式。我们把我们的注意力放到Y1≥R.对于每个Y，有一些left（y）使得（x，y）是不可接受的当且仅当X≤left（Y）。对于Y1≥R，这个界不大于X2。所以不可接受的（X1，Y1）集合， 其中X1＜X2实际上对于X2是独立的。所以我们可以预先计算left（y）的前缀和和Y⋅left（Y）的前缀和，并在我们的扫描中，对于每个X2，我们可以计算（Y1≥R）的情况的前缀和。

---

## 作者：Nuyoah_awa (赞：0)

看好多题解都写的线段树，来补一篇~~通俗易懂的~~线段树详解。

### 题目大意

在一个 $n \times n$ 的棋盘上，每行每列都有且仅有一个点，每个点的西南方向均可被覆盖上颜色一（以下简称覆盖一），东北方向均可被覆盖上颜色二（简称为覆盖二）。

问有多少种取矩形的方法，使得矩形中的格子都被两种颜色覆盖。

### 题目分析

首先观察样例，样例下标是 $0 \sim n-1$，我比较习惯 $1 \sim n$，所以整体向右上移动一格，如下图：

![P4184-1](https://s21.ax1x.com/2024/03/22/pFh1rlt.jpg)

由于答案很大，常规思路是枚举右上顶点，然后计算左下顶点有多少种可选方案（反之亦然）。

由于所选矩形中的所有点都要被两种颜色覆盖，所以很明显右上顶点一定是覆盖一内的，而左下顶点一定是覆盖二内的，反之，若满足上述条件则所选矩形一定合法（简证如图）：

![P4184-2](https://s21.ax1x.com/2024/03/22/pFh1xpR.jpg)

对于本题的特殊条件：每行只有一个点，我们可以考虑枚举每个点，然后维护每一列有多少个可选的左下点（被覆盖二覆盖的）即为 $a_i$。

设枚举的右上顶点为 $B(x,y)$，则对答案的贡献为 $f_i = \sum\limits_{i=0}^{i<x}a_i$。于是我们对于每个“喷头”$A(x,y)$，枚举顶点在这一行上的情况 $\forall i \in [1,x]B(i,y)$，再计算答案。然后更新 $A$ 点右边的 $a_i$ 值。

由于是区间修改、区间查询，所以可以用线段树维护，时间复杂度为 $\mathcal O(n ^2 \log n)$。

但是 $n$ 是 $10 ^5$ 量级的，很明显过不去，我们考虑怎么优化，由于我们要枚举 $B$ 点计算每个点的 $f_i$ 导致时间很慢，所以我们不妨再引入一个新的变量 $g_i = \sum\limits_{j=i}^{j\le i}f_j$，于是对于每个点 $A(x,y)$，我们只需要计算 $g_x$ 即可。

于是问题来到了如何维护 $g$。

我们观察每个点对于 $g$ 的贡献：

![P4184-3](https://s21.ax1x.com/2024/03/23/pFhUlMd.jpg)

不难看出，每个点对于这个点右边的 $g$ 会有贡献，其贡献是一个首项为 $1$，公差为 $1$ 的等差数列。

问题就是维护这个多个等差数列的和并且支持区间查询。

这就是 [P1438 无聊的数列](https://www.luogu.com.cn/problem/P1438) 的标准做法。

这道题的题意就是对于区间 $l\sim r$，加上一个首项为 $k$，公差为 $d$ 的等差数列，最后求第 $p$ 项。

大体思路就是对于区间 $l\sim r$，先将他们都加上 $k-l\times d$，然后再加上 $id \times d$，$id$ 为该点编号，证明略。

所以我们只需要维护两个值，一个是区间加的值，另一个是这个数加上下标乘几，正常线段树区间修改即可。

对于本题，只需要将单点查询改为区间查询即可，但是由于是区间查询，不是每回都会递归到线段树上的叶子结点，所以为了确保查询时间复杂度需要标记下沉并且动态维护线段树上答案。

最后时间复杂度 $\mathcal O(n \log n)$。

ps：取模记得开 `long long`。

### code
```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

const int N = 1e5 + 5, MOD = 1e9 + 7;
int n, z[N], x, y, out, ls[N * 4], rs[N * 4], base[N * 4], add[N * 4], ans[N * 4], mx[N], mn[N];

void build(int p, int l, int r)
{
	base[p] = add[p] = 0;
	if(l == r)
		return ;
	int mid = (l + r) >> 1;
	build(ls[p] = p << 1, l, mid);
	build(rs[p] = ls[p] + 1, mid + 1, r);
}

int sum(int l, int r){return ((l + r) * (r - l + 1) / 2) % MOD;}
//等差数列求和

void push_down(int p, int l, int r)
{
	(base[ls[p]] += base[p]) %= MOD, (base[rs[p]] += base[p]) %= MOD;
	(add[ls[p]] += add[p]) %= MOD, (add[rs[p]] += add[p]) %= MOD;
	(ans[p] += (r - l + 1) * base[p] % MOD + sum(l, r) * add[p] % MOD) %= MOD;
	base[p] = add[p] = 0;
}

int query(int p, int l, int r, int ll, int rr)
{
	if(ll <= l && r <= rr)
		return (ans[p] + (r - l + 1) * base[p] % MOD + sum(l, r) * add[p] % MOD) % MOD;		//ans 是之前已经计算过的，base 和 add 是还没算的，记得加上
	push_down(p, l, r);
	int mid = (l + r) >> 1, res = 0;
	if(ll <= mid)	(res += query(ls[p], l, mid, ll, rr)) %= MOD;
	if(rr > mid)	(res += query(rs[p], mid + 1, r, ll, rr)) %= MOD;
	return res;
}

void update(int p, int l, int r, int ll, int rr, int k, int d)
{
	if(ll <= l && r <= rr)
	{
		(base[p] += k) %= MOD;
		(add[p] += d) %= MOD;
		push_down(p, l, r);
		return ;
	}
	push_down(p, l, r);
	int mid = (l + r) >> 1;
	if(ll <= mid)	update(ls[p], l, mid, ll, rr, k, d);
	if(rr > mid)	update(rs[p], mid + 1, r, ll, rr, k, d);
	ans[p] = ans[ls[p]] + ans[rs[p]];
	return ;
}//fhq-treap

signed main()
{
	scanf("%lld", &n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld %lld", &x, &y);
		z[x+1] = y + 1;
	}
	build(1, 1, n);
	for(int i = n;i >= 1;i--)
		mx[i] = max(mx[i+1], z[i]);
	mn[0] = n + 1;
	for(int i = 1;i <= n;i++)
		mn[i] = min(mn[i-1], z[i]);
	for(int i = 1;i <= n;i++)
	{
		if(mx[i] > 1)			//注意线段树查询下标从 1 开始，防止越界
			(out += query(1, 1, n, 1, mx[i]-1)) %= MOD;
		update(1, 1, n, mn[i], n, 1 - mn[i], 1);
	}
	printf("%lld\n", out);
	return 0;
}
```

---

## 作者：by_chance (赞：0)

[Link](https://www.luogu.com.cn/problem/P4184)

记所有喷头的坐标为 $(i,a_i)$。考虑直接从矩形的角度去计数：对于一个左下角在 $(x,y)$，右上角在 $(z,w)$ 的矩形，它要被水覆盖，当且仅当点 $(x,y)$ 被水覆盖，也就是要存在 $i\le x$ 使得 $a_i\le y$。被肥料覆盖同理，需要存在 $i\ge z$ 使得 $a_i\ge w$。

固定 $x$，可以得到 $y$ 的范围是 $[f_x,n-1]$，这里 $f_x=\min_{i\le x}a_i$。固定 $z$，可以得到 $w$ 的范围是 $[1,g_z]$，这里 $g_z=\max_{i\ge z}a_i$。那么枚举 $x,z$，需要满足 $x\lt z,f_x\le y\lt w\le g_z$。额外需要一个限制 $f_x\le g_z$，这可以二分或者双指针求解。记 $h_x=\max_{g_z\ge f_x}z$，则目标式就是

$$\sum_{x=0}^{n-1}\sum_{z=x+1}^{h_x}\sum_{y=f_x}^{g_z}\sum_{w=y+1}^{g_z}1=\sum_{x=0}^{n-1}\sum_{z=x+1}^{h_x}\frac{1}{2}(g_z-f_x)(g_z-f_x+1)$$

把 $x$ 看作常量，后面的式子可以写成 $\sum_{z=L}^{R}(Ag_z^2+Bg_z+C)$，$A,B,C,L,R$ 均与 $z$ 无关，所以只需要维护 $g_z,g_z^2$ 的前缀和，枚举 $x$ 即可求解。如果用双指针求 $h$ 数组的话，复杂度可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,P=1e9+7;
inline void pls(int&a,int b){a+=b;if(a>=P)a-=P;}
int n,b[N],f[N],g[N],s1[N],s2[N],ans;
int main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        b[x+1]=y;
    }
    f[1]=b[1];g[n]=b[n];
    for(int i=2;i<=n;i++)f[i]=min(b[i],f[i-1]);
    for(int i=n-1;i>=1;i--)g[i]=max(b[i],g[i+1]);
    for(int i=1;i<=n;i++){
        s1[i]=g[i];s2[i]=1ll*g[i]*g[i]%P;
        pls(s1[i],s1[i-1]);pls(s2[i],s2[i-1]);
    }
    for(int x=1;x<n;x++){
        int L=x+1,R=n,pos=x;
        while(L<=R){
            int mid=(L+R)>>1;
            if(g[mid]>=f[x])pos=mid,L=mid+1;
            else R=mid-1;
        }
        pls(ans,(s2[pos]-s2[x]+P)%P);
        pls(ans,1ll*(s1[pos]-s1[x]+P)*(2*P+1-2*f[x])%P);
        pls(ans,(1ll*f[x]*f[x]%P-f[x]+P)*(pos-x)%P);
    }
    ans=1ll*ans*(P+1)/2%P;
    printf("%d\n",ans);
    return 0;
}
```

---

