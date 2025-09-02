# Cutting a Fence

## 题目描述

Vasya the carpenter has an estate that is separated from the wood by a fence. The fence consists of $ n $ planks put in a line. The fence is not closed in a circle. The planks are numbered from left to right from 1 to $ n $ , the $ i $ -th plank is of height $ a_{i} $ . All planks have the same width, the lower edge of each plank is located at the ground level.

Recently a local newspaper "Malevich and Life" wrote that the most fashionable way to decorate a fence in the summer is to draw a fuchsia-colored rectangle on it, the lower side of the rectangle must be located at the lower edge of the fence.

Vasya is delighted with this idea! He immediately bought some fuchsia-colored paint and began to decide what kind of the rectangle he should paint. Vasya is sure that the rectangle should cover $ k $ consecutive planks. In other words, he will paint planks number $ x $ , $ x+1 $ , $ ... $ , $ x+k-1 $ for some $ x $ $ (1<=x<=n-k+1) $ . He wants to paint the rectangle of maximal area, so the rectangle height equals $ min\ a_{i} $ for $ x<=i<=x+k-1 $ , $ x $ is the number of the first colored plank.

Vasya has already made up his mind that the rectangle width can be equal to one of numbers of the sequence $ k_{1},k_{2},...,k_{m} $ . For each $ k_{i} $ he wants to know the expected height of the painted rectangle, provided that he selects $ x $ for such fence uniformly among all $ n-k_{i}+1 $ possible values. Help him to find the expected heights.

## 说明/提示

Let's consider the first sample test.

- There are three possible positions of the fence for $ k_{1}=1 $ . For the first position $ (x=1) $ the height is 3, for the second one $ (x=2) $ the height is 2, for the third one $ (x=3) $ the height is 1. As the fence position is chosen uniformly, the expected height of the fence equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212D/600a596c50e02741a32b22d7848d1d9bd697d1fa.png);
- There are two possible positions of the fence for $ k_{2}=2 $ . For the first position $ (x=1) $ the height is 2, for the second one $ (x=2) $ the height is 1. The expected height of the fence equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212D/d8c78108bbe97570655d46138ac5fa6c3f66cb3d.png);
- There is the only possible position of the fence for $ k_{3}=3 $ . The expected height of the fence equals 1.

## 样例 #1

### 输入

```
3
3 2 1
3
1 2 3
```

### 输出

```
2.000000000000000
1.500000000000000
1.000000000000000
```

## 样例 #2

### 输入

```
2
1 1
3
1 2 1
```

### 输出

```
1.000000000000000
1.000000000000000
1.000000000000000
```

# 题解

## 作者：LuckyCloud (赞：15)

~~真的，已经不想说什么了，这道题出的真的太好了……orzorzorz~~


- 对于每个数a[x]在它左边找一个离它最近的小于它的数，在它右边找一个离它最近     的小于等于它的数

  记所找到左边数的位置为 _l_ ,所找到右边数的位置为 _r_ 。

  **那么在[ _l_ +1, _r_ -1]中的所有子区间，只要包含a[x]，最小值都是a[x]**


- 设a[x]到a[ _l_ +1]长度为L，a[x]到a[ _r_ -1]长度为R

  当第二问的区间长度为K时(K是个变量)，把所有长度为K的区间最小值的和设为Sum
  
  我们开始分类讨论

  设L<=R

  ① 当1<=K<=L,会有K个长度为K的区间的最小值是a[x]，Sum=Sum+K*a[x]

  ② 当L+1<=K<=R 会有L个长度为K的区间的最小值是a[x],Sum=Sum+L*a[x]

  ③ 当R+1<=K<=L+R-1 会有L+R-K个长度为K的区间的最小值a[x],
  
  Sum=Sum+a[x] (L+R-K)=Sum+a[x] (L+R)-K*a[x]

  对于每一个a[x]，我们需要把它**对所有区间长度询问的答案贡献**求出
  也就是对于每个Len(1<=len<=L+R-1)，我们都要根据上面分类讨论得出的结论，
  算出对Sum的贡献。观察关于Sum的式子可以发现，只有K*a[x]才是一个会变化的值，   其余都是定值。
  
  我们不妨设C1[K]是区间长度为K时,所有需要乘K的a[x]的和，C2[K]是区间长度为K时，所有定值的和。
  
  设ans[K]是区间长度为K的答案，ans[K]=(K*C1[K]+C2[K])/(n-K+1)
  
  我们需要预处理出所有区间长度的答案，然后O(1)解出每一个询问。
  
  显然对于每一个a[x] (1<=x<=n),都会有一系列的K满足前面的三种讨论情况，
  而每一个K，都会有一个C1[K],C2[K]，会发现，当连续的几个K都处于同一种情况的时候，所对应的C1[],C2[]增加的值是相等的，这就可以看作是区间加，可以用差分来做。
  
  For Example
  
  2 5 5 5 3 5 5 5 5 5 5 2
  
  a[6]=3, L=4, R=7
  
  当K取[1,4]时，对于a[6]会有4个区间满足最小值是a[6]的条件
  
  那么
  
  C1[1]=C1[1]+a[6], 
  
  C1[2]=C1[2]+a[6], 
  
  C1[3]=C1[3]+a[6], 
  
  C1[4]=C1[4]+a[6]
  
  ——显然一个区间加
  
  当K取[5,7]时,对于a[6]会有5个区间满足最小值是a[6]的条件
  
  那么
  
  C2[5]=C2[5]+4*a[6]
  
  C2[6]=C2[6]+4*a[6]
  
  C2[7]=C2[7]+4*a[6]
  
  ——显然一个区间加
  
  当K取[8,10]时,对于a[6]会有11-K个区间满足最小值是a[6]的条件
  
  那么
  
  C1[8]=C1[8]+11*a[6]
  
  C1[9]=C1[9]+11*a[6]
  
  C1[10]=C1[10]+11*a[6]
  
  ——显然一个区间加
  
  C2[8]=C2[8]-a[6]
  
  C2[9]=C2[9]-a[6]
  
  C2[10]=C2[10]-a[6]
  
  ——显然一个区间加
  
  至于为什么对于每个数a[x]一个是找离它最近的小于它的数，另一个是找右边离它最近的小于等于它的数？
  
  同一个区间内最小值有多个的话，也只需要算一次，比如样例二的这种数据是会被多次计算的，[1,2]这个区间，a[1]的时候算一次，a[2]的时候算一次，所以为什么要这么做，你可以感性的理解为去重。
  
  OK,OK，其余就看代码吧！
  
  
  
 ```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,m,R[1000100],a[1000100],k,x,L[1001000],y,C1,C2;
long long c1[1001000],c2[1001000];
double ans[1001000];
inline long long read()
{
  long long cnt=0,f=1;char ch=getchar();
  while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
  while (ch>='0'&&ch<='9'){cnt=cnt*10+ch-48;ch=getchar();}
  return cnt*f;
}
int main()
{
  n=read();
  for (int i=1;i<=n;i++)
   a[i]=read();
  a[n+1]=-((long long)1<<60);
  a[0]=-((long long)1<<60);
  for (int i=n;i;i--)
   {
   	if (a[i+1]<=a[i]) R[i]=i+1;
   	else
   	for (int j=R[i+1];j<=n+1;j=R[j])
   	 if (a[j]<=a[i]) {R[i]=j;break;}
   }
  for (int i=1;i<=n;i++)
   {
   	if (a[i-1]<a[i]) L[i]=i-1;
   	else
   	for (int j=L[i-1];j>=0;j=L[j])
   	 if (a[j]<a[i]) {L[i]=j;break;}
   }
  for (int i=1;i<=n;i++)
  {
   L[i]=i-L[i];
   R[i]=R[i]-i;
  }
  for (int i=1;i<=n;i++)
   {
     x=L[i];y=R[i];
     if (x>y) swap(x,y);
     c1[1]+=a[i];c1[x+1]-=a[i];
     c2[x+1]+=a[i]*x;c2[y+1]-=a[i]*x;
     c2[y+1]+=a[i]*(x+y);c2[x+y]-=a[i]*(x+y);
     c1[y+1]-=a[i];c1[x+y]+=a[i];
   }
  for (int i=1;i<=n;i++)
   {
   	C1+=c1[i];
   	C2+=c2[i];
   	ans[i]=((C1*i+C2)*1.0)/((n-i+1)*1.0);
   }
  m=read();
  for (int i=1;i<=m;i++)
   {
    k=read();
    printf("%.9lf\n",ans[k]);
   }   
  return 0;
}
```
    LuckyCloud

---

## 作者：LSG_waterlyf (赞：6)

一道奇怪的二次差分被我用奇怪的数据结构过了。

我的做法：笛卡尔树+线段树，复杂度$O(nlogn)$,人傻常数大的我勉强卡过。

首先题目要求的是若干个长度为$1-n$的区间在数轴上移动，其中的最低点的期望, 我们可以把所有情况的答案都算出来再除以总数即为所求。

根据笛卡尔树的性质，我们可以算出每个最低点$k$**能够控制的区间** 即在$l-r$范围内的最小值都为$h[k]$. 也就是说在$l-r$内所有**经过**$k$的区间都将被累加$h[k]$的贡献,对于一个长为$x$的区间，它将被累加$min(r-k+1,k-l+1)*h[k]$的贡献，我们手模一下发现如果$k$这个点对于长度为$1-x$的区间有贡献，那么贡献一定是随着长度$i$**先递增，再不变，再递减**。所以我们可以很方便的用前缀和来维护区间的答案。因为涉及区间加的操作，所以用线段树来维护。

最终长度为$i$ 的区间的答案为 $ask(1,1,i)/(n-i+1)$.

最后贴上代码方便理解

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000010
#define ll long long
#define lb double
#define int long long
int n,m,a[N],ls[N],rs[N],siz[N],rt,top,sta[N];
void read(int &x)
{
    x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
}
struct tree{int l,r;ll sum,lz;}tr[N*4];
void build(int k,int l,int r)
{
    tr[k].l=l;tr[k].r=r;
    if(l==r) return;
    int mid=(l+r)/2;
    build(k*2,l,mid);build(k*2+1,mid+1,r);
}
void down(int k)
{
    ll lz=tr[k].lz;tr[k].lz=0;
    tr[k*2].sum+=lz*(tr[k*2].r-tr[k*2].l+1);
    tr[k*2+1].sum+=lz*(tr[k*2+1].r-tr[k*2+1].l+1);
    tr[k*2].lz+=lz;tr[k*2+1].lz+=lz;
}
void change(int k,int l,int r,ll w)
{
    //if(l>r) return;
    if(r<tr[k].l||l>tr[k].r) return;
    if(l<=tr[k].l&&r>=tr[k].r) 
      {tr[k].sum+=w*(tr[k].r-tr[k].l+1),tr[k].lz+=w;return;}
    down(k);change(k*2,l,r,w);change(k*2+1,l,r,w);
    tr[k].sum=tr[k*2].sum+tr[k*2+1].sum;
}
ll ask(int k,int l,int r)
{
    if(r<tr[k].l||l>tr[k].r)return 0;
    if(l<=tr[k].l&&r>=tr[k].r) return tr[k].sum;
    down(k);return ask(k*2,l,r)+ask(k*2+1,l,r);
}
void dfs(int u)
{
    if(ls[u]) dfs(ls[u]);
    if(rs[u]) dfs(rs[u]);
    siz[u]=siz[ls[u]]+siz[rs[u]]+1;
     
    //printf("i=%d h=%d l=%d r=%d\n",u,a[u],u-siz[ls[u]],u+siz[rs[u]]);
    int Min=min(siz[ls[u]],siz[rs[u]]),Max=max(siz[ls[u]],siz[rs[u]]);
    if(!ls[u]||!rs[u]) {change(1,1,1,a[u]);change(1,Max+2,Max+2,-a[u]);}
    else {
    change(1,1,Min+1,a[u]);change(1,Min+2,Min+2,-a[u]*(Min+1));
    //if(u==2) printf("Min=%d Max=%d\n",Min,Max);
    if(Max>Min){change(1,Min+2,Min+2,(Min+1)*a[u]);change(1,Min+2+Max-Min,Min+2+Max-Min,-(Min+1)*a[u]);}
    change(1,siz[u]-Min+1,siz[u]-Min+1,Min*a[u]);change(1,siz[u]-Min+2,siz[u]+1,-a[u]);}
    //printf("i=%d h=%d\n",u,a[u]);
/*  for(int i=1;i<=n;i++) printf("%d ",ask(1,1,i));
    puts("\n=============================");*/
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=n;i++)
    {
        while(top&&a[sta[top]]>=a[i]) ls[i]=sta[top--];
        if(top) rs[sta[top]]=i;sta[++top]=i;
    }
    build(1,1,n);rt=sta[1];dfs(rt);
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int k;read(k);
        printf("%.15lf\n",(lb)ask(1,1,k)/(lb)(n-k+1));
    }
    return 0;
}
```


---

## 作者：Unnamed114514 (赞：4)

离线下来。

单调栈得到每个数 $a_i$ 覆盖的范围 $[l_i,r_i]$。

因为 $\sum\limits_{i=1}^n\min\{i-l_i+1,r_i-i+1\}=O(n\log n)$。

理解方法就是笛卡尔树启发式合并。

然后你就暴力就行了，维护一个区间加，用差分就行。

$O(n\log n)$。

---

## 作者：JasonL (赞：3)

## CF212D Cutting a Fence

[题目传送门](https://www.luogu.com.cn/problem/CF212D)

### 题目解析

题解区里主要是二阶差分的做法。这里给出一个只用一阶差分的做法。

（其实就是二阶差分提前处理，但仍然能做到 $O(n\log n) $）

首先我们用单调栈预处理出 $lp_i,rp_i$ ，分别表示 $i$ 管辖区间的左端点和右端点。管辖区间表示，在这段区间内，任意一个跨过 $i$ 的区间的贡献都是 $a_i$ 。

接下来我们对每个 $i$ 处理出它对答案的贡献。有一种很显然的方法是，枚举某一边的每一个端点（即，枚举左端点或枚举右端点），然后用一个一阶差分处理。最后再扫一遍答案即可。但是这么做并不能保证复杂度。

用类似于启发式合并的思想，我们每次选择区间大小较小的那一边，然后枚举端点。注意到在 $[lp_i,rp_i]$ 内， $i$ 将该区间分成了更小的两块区间 $[lp_i,i),(i,rp_i]$ ，所以从底向上可以看做区间的合并。

每次枚举是 $O(size)$ ，因而根据启发式合并得到 $O(n \log n)$ 。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1001000;
int n,mod;
int a[maxn];
int S[maxn],st;
int lp[maxn],rp[maxn];
double f[maxn];
inline int read(){
	int res=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return res;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	st=0;
	for(int i=1;i<=n;++i){
		while(st&&a[i]<a[S[st]])--st;
		lp[i]=S[st]+1;
		S[++st]=i;
	}
	st=0;S[st]=n+1;
	for(int i=n;i;--i){
		while(st&&a[i]<=a[S[st]])--st;
		rp[i]=S[st]-1;
		S[++st]=i;
	}
	for(int i=1;i<=n;++i){
		if(i-lp[i]<rp[i]-i){
			for(int j=i;j>=lp[i];--j){
				f[i-j+1]+=a[i];
				f[rp[i]-j+2]-=a[i];
			}
		}
		else{
			for(int j=i;j<=rp[i];++j){
				f[j-i+1]+=a[i];
				f[j-lp[i]+2]-=a[i];
			}
		}
	}
	for(int i=1;i<=n;++i){
		f[i]+=f[i-1];f[i-1]/=n-i+2;
	}
	int T=read();
	while(T--)
		printf("%.9lf\n",f[read()]);
	return 0;
}
```


---

## 作者：Narcissusany (赞：2)

> 给出 $a[1...n]$ 。
> 定义 $f$ ：
>
> $$f(i,k)=\min_{i\leq j\leq i+k-1}\{a[j]\}$$
>
> 之后有 $m$ 个询问，每个询问给出一个数 $k$，问所有 $f(j,k) (1\leq j\leq n-k+1)$ 的平均值。
> $1\leq n,m\leq 10^6$.

首先不难知道要求出每个 $a_i$ 对包含其区间的贡献，然后对于长度为 $1\sim n$ 的区间分别计算其和，最终除以 $n-k+1$ 即为答案。

考虑两遍单调栈求出每个元素 $x$ 左/右边第一个比他小的元素下标 $l,r$，可知 $x$ 的贡献区间即为 $[l+1,r-1]$。枚举 $x$ ，那么区间 $l+1,r-1$ 的所有跨过 $x$ 的子区间都会存在贡献。此处假设 $x-l<r-x$，考虑分类讨论子区间长度 $L$ ： 

1、 $1\leq L\leq x-l$ ，这种区间每个元素都可以是 $x$ ，所以贡献为 $L\cdot a_x$ 。

2、$x-l+1\leq L\leq r-x$ ，这种区间最多只能取到 $x-l$ 次 $x$ ，所以贡献为 $(x-l)\cdot a_x$ 。

3、$r-x+1\leq L\leq r-l-1$ ，这种区间最多只能取到 $r-l-L$ 次，所以贡献为 $(r-l-L)\cdot a_x$ 。

然后观察这些修改，发现 $L\cdot a_x$ 这东西，对于一个区间是在加一个等差数列的形式，$(x-l)\cdot a_x$ 和 $(r-l)\cdot a_x$ 都是区间加一个常数的形式。于是可以维护二阶差分。复杂度线性。

至于二阶差分怎么维护…可以左转 P4231三步必杀。

```cpp
int s ; 
int n, q ;
int L[N] ; 
int R[N] ;
ll base[N] ;
ll ans1[N] ;
ll ans2[N] ;

il void add1(int x, ll v){ ans1[x] += v ; }
il void add2(int x, ll v){ ans2[x] += v ; }

int main(){
	cin >> n ; int m ;
	for (int i = 1 ; i <= n ; ++ i) base[i] = qr() ;
	for (int i = 1 ; i <= n ; ++ i){
		while (!s.empty() && base[s.top()] > base[i]) s.pop() ; 
		L[i] = s.empty() ? 0 : s.top() ; s.push(i) ; 
	}
	while (!s.empty()) s.pop() ; 
	for (int i = n ; i >= 1 ; -- i){
		while (!s.empty() && base[s.top()] >= base[i]) s.pop() ; 
		R[i] = s.empty() ? n + 1 : s.top() ; s.push(i) ; 
	}
	for (int i = 1 ; i <= n ; ++ i){
		ll l = i - L[i] ; 
		ll r = R[i] - i ;
		ll t = l + r ; 
		ll L = l + 1 ;
		ll R = r + 1 ;  
		if (l > r){
			swap(l, r) ;
			swap(L, R) ;  
		}
		add1(L, l * base[i]) ; 
		add1(R, - l * base[i]) ;  
		add1(r + 1, t * base[i]) ; 
		add1(l + r, - t * base[i]) ; 
		
		add2(1, base[i]) ;
		add2(L, - base[i] * L) ; add2(L + 1, base[i] * l) ; 
		add2(R, - R * base[i]) ; add2(R + 1, r * base[i]) ;
		add2(t, base[i] * t) ; add2(t + 1, -base[i] * (t - 1)) ; 
	}
	for (int i = 1 ; i <= n ; ++ i) ans2[i] += ans2[i - 1] ; 
	for (int i = 1 ; i <= n ; ++ i) ans2[i] += ans2[i - 1] ; 
	for (int i = 1 ; i <= n ; ++ i) ans1[i] += ans1[i - 1] ; 
	for (int i = 1 ; i <= n ; ++ i) ans1[i] += ans2[i] ; cin >> q ; 
	while (q --) m = qr(), printf("%.10lf\n", (db)ans1[m] / (db)(n - m + 1)) ; return 0 ; 
}










```


---

## 作者：wangyibo201026 (赞：0)

## 前提一笔

> 这道题是多么的美好啊！优雅而不失自然。  ——XXX


这道题耗费了本人大量的时间，写作不易，~~请一键三连~~。

## 题意

给你一个长度为 $n$ 的序列 $a$，每次询问给出一个 $k$，求这个序列所有长度为 $k$ 的子串内的最小值的平均值。

## 思路

这道题目肯定会有人想直接用数据结构解决这些问题，但是明显不可行。

看着题意很复杂，但是我们可以把它化简成两个问题：

- 所有长度为 $k$ 的子串个数。

- 所有长度为 $k$ 的子串中最小值之和。

显然第一个问题的答案就是 $n - k + 1$，我们把注意力放在第二个问题。

我们这么想，如果没有 $k$ 的限制，变成所有子串的最小值之和，我们该怎么办？

这是一个经典的问题，考虑每一个数对答案的贡献，我们设 $L_i$ 为 $1 \sim i - 1$ 内**从右往左**数第一个**小于等于** $a_i$ 的数的下标，如果不存在则为 $0$，$R_i$ 为 $i + 1 \sim n$ 内**从左往右**数第一个**小于** $a_i$ 的下标，如果没有则为 $n + 1$。

现在答案就显然了，区间要包含 $i$ 的话，那么答案的贡献即是 $(i - L_i) \times (R_i - i)$，就是 $i$ 左边的比它大的数以及 $i$ 跟 $i$ 右边比它大的数以及 $i$ 两两配对成一段区间，所有的区间内最小值一定为 $a_i$。

那么我们再回到原问题，原问题要求上述所配对的区间长度必须为 $k$，那么就相当于给配对的区间加上了一个长度的限制，我们考虑怎么做。

**请注意**：在解题过程中，我们保证所有的 $L_i$ 和 $R_i$ 满足 $(i - L_i) < (R_i - i)$。

我们分成三种情况考虑（这种问题常见的方法之一就是分类讨论）：

1. $k < (i - L_i)$，即在长度为 $k$ 的配对区间中，左端点碰不到 $L_i$，右端点碰不到 $R_i$。

2. $(i - L_i) \le k < (R_i - i)$，即在长度为 $k$ 的配对区间中，左端点可以为 $L_i$，但右端点碰不到 $R_i$。

3. $(R_i - i) \le k$，即在长度为 $k$ 的配对区间中，左端点可以为 $L_i$，右端点可以为 $R_i$。

接着看个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mltp84dw.png)

横轴代表在变化的 $k$，而纵轴表示的是在 $k$ 变化过程中，配对区间的变化过程。

可以看出，$a_i$ 对答案的贡献分为三个段，也对应三种情况，第一个段是一个形如 $1, 2 ... (i - L_i)$ 的等差数列（指配对区间个数），而第二段则是形如 $(i - L_i) ... (i - L_i)$，第三段形如 $(R_i - i - 1) ... 1$。对答案的贡献显然可以用二维差分解决。

而上面的 $L_i$ 和 $R_i$ 则可以用二分加 ST 表解决。

总时间复杂度 $O(n \log_2 n)$。

---

## 作者：青鸟_Blue_Bird (赞：0)

#### [AC传送门！](https://www.luogu.com.cn/problem/CF212D)

看题目，首先肯定是要先想想我们应该用什么处理方法。1e6的询问题，我们肯定是不能在线处理的，因此先确定：

#### 先尽可能预处理出最终答案，然后输出

于是乎，开始动手吧：

根据题目中f的定义，我们要找到许多区间中的最小值。那么，假设我们的一个数 $a_x$ (1≤x≤n)，如何找到一个区间使得其最小值为$a_x$呢？  

并不难，只要我们找到了它最左边的第一个小于它的数$a_l$,以及它右边第一个小于等于它的数$a_r$，那么对于区间[l+1, r-1],其最小值就是$a_x$。

即： 对于一个数$a_x$,其作为最小值得区间为 [l + 1 , r - 1],（其中$a_l$ < $a_x$ 且 $a_r$ < $a_x$, l,r均为区间 [l , x]与 [x , r]中的最小值)

那么，我们设变量 L 为左区间 [l + 1, x] 的长度， R 为右区间 [x, r - 1] 的长度。

我们~~强制~~假设L ≤ R

### 那么，对情况进行分类讨论：

为了方便，我们把“有x个区间符合要求” 暂时定义为 “有x个区间满足有$min_x$ = $a_x$"

1、如果 k $\in$ [1 , L] 那么就会有 k 个区间符合要求

2、如果 k $\in$ [L + 1, R] ,那么会有 L 个区间符合要求。

3、如果 k $\in$ [R + 1, L + R - 1] 那么会有(L + R - K)个区间满足要求。

那么，对于一个数对应的贡献 $sum_x$ ，对应有：

1、$sum_x$ = $sum_x$ + k * $a_x$

2、$sum_x$ = $sum_x$ + L * $a_x$

3、$sum_x$ = $sum_x$ + $a_x$ * (L + R) - k * $a_x$

观察以上~~柿子~~，不难发现，他们都是： $a_x$ * k + B   的格式。也就是说，除了变量K，剩下的都是定值。

#### 那么，我们为什么不快速求出每一个~~柿子~~的 B 呢？

于是，我们改变一下，以 K 参考系:

设$S_1$ = $\sum_{}a_x$(满足上述条件) -> 即为上文所述的所要乘上k的 $a_x$ 的和。

$S_2$ = $\sum_{}^{}n$($n$为任意实数） -> 即为上文所述的B


对于一个数K，$ans_k$ = ($S_1$ * k + $S_2$) / (n - k + 1)

具体的例子，我觉得大家可以参考[PinkCloud大佬的博客](https://www.luogu.com.cn/blog/LuckyCloud/solution-cf212d)：


那么，我们如何实现快速求和呢？ 对$S_1$和$S_2$数组分别进行差分即可。


具体实现还是看代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define ll long long

inline ll read(){
	ll x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-')s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = x * 10 + (c ^ '0');
		c = getchar();
	}
	return x * s;
}

ll n, m, r[N], l[N], a[N];
ll s1[N], s2[N];
double ans[N];

void search(){
	for(int i = n; i; i--){  /*向右找到第一个小于等于这个数的位置*/
		if(a[i + 1] <= a[i]) r[i] = i + 1;
		else 
			for(int j = r[i + 1]; j <= n + 1; j = r[j])  /*一直向右跑*/
				if(a[j] <= a[i]){
					r[i] = j;
					break;
				}
	}
	for(int i = 1;i <= n; i++){  /*同上，向左找*/
		if(a[i - 1] < a[i]) l[i] = i - 1;
		else 
			for(int j = l[i - 1]; j >= 0; j = l[j])	
				if(a[j] < a[i]) {
					l[i] = j;
					break;
				}
				
	}
	for(int i = 1;i <= n; i++){  /*换算成距离 L 和 R*/
		l[i] = i - l[i];   
		r[i] = r[i] - i;
	}
	return ;
}

void prepare(){  /*进行差分以及预处理答案*/
		for(int i = 1;i <= n; i++){
		int x = l[i], y = r[i];
		if(x > y) swap(x, y);  /*保持 L < S*/
		s1[1] += a[i];
		s1[x + 1] -= a[i];
		s2[x + 1] += a[i] * x;
		s1[y + 1] -= a[i];
		s2[y + 1] += a[i] * y;
		s1[x + y] += a[i]; 
		s2[x + y] -= a[i] * (x + y);
	}
	ll num1 = 0, num2 = 0;
	for(int i = 1;i <= n; i++){
		num1 += s1[i], num2 += s2[i];
		ans[i] = ((num1 * i + num2) * 1.00) / ((n - i + 1) * 1.00); /*预处理出所有答案*/
	}
	return ;
}

int main(){
	n = read();
	for(int i = 1;i <= n; i++)
		a[i] = read();
	a[n + 1] = (ll)(-(1 << 50));/*两端插入极小值，避免下一步越界或者出现错误*/
	a[0] = (ll)(-(1 << 50));
	search(); /*先搜索距离*/
	prepare();  /*然后处理答案*/
	m = read();
	while(m--){
		ll k = read();
		printf("%.9lf\n", ans[k]); 	
	}
	return 0;
}
```







---

## 作者：__ycx2010__ (赞：0)

### 思路

考虑点对区间的贡献，设 $l_i$ 为 $i$ 左侧第一个小于它的点， $r_i$ 为 $i$ 为右侧第一个小于它的点，设 $L = i-l_i, R=r_i -i$。

设 $f_k$ 表示点 $i$ 对长度为 $k$ 的贡献，则一定呈梯形。

所以用二维差分维护。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int a[N], l[N], r[N], q[N];
long long b[N]; 

int main() {
	int n, m;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	int tt = 0;
	for (int i = 1; i <= n; i ++ ) {
		while (tt && a[q[tt]] >= a[i]) tt -- ;
		l[i] = q[tt] + 1;
		q[++ tt] = i;
	}
	tt = 0;
	q[0] = n + 1;
	for (int i = n; i >= 1; i -- ) {
		while (tt && a[q[tt]] > a[i]) tt -- ;
		r[i] = q[tt] - 1;
		q[++ tt] = i;
	}
	for (int i = 1; i <= n; i ++ ) {
		int L = i - l[i] + 1, R = r[i] - i + 1;
		b[1] += a[i];
		b[min(L, R) + 1] -= a[i];
		b[max(L, R) + 1] -= a[i];
		b[L + R + 1] += a[i];
	}
	for (int i = 1; i <= n; i ++ ) b[i] += b[i - 1];
	for (int i = 1; i <= n; i ++ ) b[i] += b[i - 1];
	scanf("%d", &m);
	while (m -- ) {
		int k;
		scanf("%d", &k);
		printf("%.12lf\n", b[k] * 1.0 / (n - k + 1));
	}
	return 0;
}
```

---

