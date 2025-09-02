# Paths

## 题目描述

You are given a positive integer $ n $ . Let's build a graph on vertices $ 1,2,...,n $ in such a way that there is an edge between vertices $ u $ and $ v $ if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/c23ed97fe13a97ab9d4221da3ee57148bf19e74e.png). Let $ d(u,v) $ be the shortest distance between $ u $ and $ v $ , or $ 0 $ if there is no path between them. Compute the sum of values $ d(u,v) $ over all $ 1<=u<v<=n $ .

The $ gcd $ (greatest common divisor) of two positive integers is the maximum positive integer that divides both of the integers.

## 说明/提示

All shortest paths in the first example:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/3e40931641babdd9752cd39292d234015759308e.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/6041d67223ddc985153dc52c9e7a7e1d48075179.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/3e29ecae5595c93d38537b4ca1a7d7fc6ca1fa60.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/c648e4ad2596633a70de4e6c388b5f81739e78ae.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/d7426e9934723e8754848fe5e8743b6ef00be8ab.png)
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF870F/f09a0e8516170bfe135732c6c4dc8bd6c28ccd78.png)

There are no paths between other pairs of vertices.

The total distance is $ 2+1+1+2+1+1=8 $ .

## 样例 #1

### 输入

```
6
```

### 输出

```
8
```

## 样例 #2

### 输入

```
10
```

### 输出

```
44
```

# 题解

## 作者：command_block (赞：13)

**题意** ： 给定一张 $n$ 个点的图，点编号为 $1\sim n$。

对于点 $i,j$。若 $\gcd(i,j)>1$ ，则 $i$ 到 $j$ 有一条长度为 $1$ 的无向边。

记 $dis(i,j)$ 表示从 $i$ 到 $j$ 的最短路长度，如果 $i$ 无法到 $j$ ，则 $dis(i,j)=0$。

求节点两两之间距离之和。

$n\leq 10^7$，时限$\texttt{4s}$。

------------

对于两个数 $u,v$ ，考虑如何快速求出 $dis(u,v)$。

在判定两个数能不能连边时，只需要考虑质因子集合，不需要考虑质因子次数。

- 若 $u,v$ 中有一个为 $1$ ，则 $dis(u,v)=0$ ，直接将 $1$ 忽略。

- 若两个数不互质，则直接连接。（ `Case #A` ）

- 对于两个互质的数 $u,v$ ，取出各自的最小质因子 $p_u,p_v$。

  若 $p_up_v\leq n$ ，则 $u\rightarrow p_up_v\rightarrow v$ ，$dis(u,v)=2$。（ `Case #B` ）
  
  若 $p_up_v>n$ 且 $p_u,p_v\leq n/2$ ，则 $u\rightarrow 2p_u\rightarrow 2p_v\rightarrow v$。$dis(u,v)=3$。（ `Case #C` ）
  
  若 $\max(p_1,p_2)>n/2$ ，则 $dis(u,v)=0$。（ `Case #D` ）
  
下面对每种情况分别统计贡献。

- ## Case #A

$$=\tbinom{n-1}{2}-\sum\limits_{i=2}^n\varphi(i)-1$$

线性筛即可。
  
- ## Case #B

算出互质数对的总数，再减去其他情况。

- ## Case #C

记 $p_{\min}(n)$ 为 $n$ 的最小质因子。

$$=\sum\limits_{p_u\in P}^{n/2}\sum\limits_{p_v\in P}^{n/2}[p_u<p_v][p_up_v>n]\sum\limits_{u,v}[p_{\min}(u)=p_u][p_{\min}(v)=p_v][u\perp v]$$

这里由于 $p_up_v>n$ ，故一个数不可能同时含有 $p_u,p_v$ （或更大的素因子）。

因此，有 $p_{\min}(u)=p_u,p_{\min}(v)=p_v\Rightarrow u\perp v$。

$$=\sum\limits_{p_u\in P}^{n/2}\sum\limits_{p_v\in P}^{n/2}[p_u<p_v][p_up_v>n]\bigg(\sum\limits_{u=1}^n[p_{\min}(u)=p_u]\bigg)\bigg(\sum\limits_{v=1}^n[p_{\min}(v)=p_v]\bigg)$$

预处理 $S(p)=\sum\limits_{k=1}^n[p_{\min}(k)=p]$

$$=\sum\limits_{p_u\in P}^{n/2}S(p_u)\sum\limits_{p_v\in P}\Big[p_v\in\big(\max(\lfloor n/p_u\rfloor,p_u),n/2\big]\Big]S(p_v)$$

- ## Case #D

$$=\sum\limits_{p_u\in P}S(p_u)\sum\limits_{p_v\in P}\Big[p_v\in\big(\max(n/2,p_u),n\big]\Big]S(p_v)$$

总复杂度 $O(n)$。

本题的妙处在于， 四种情况的统计并不是一样难的，需要适当运用正难则反思想。

关键在于 $p_up_v>n,p_{\min}(u)=p_u,p_{\min}(v)=p_v\Rightarrow u\perp v$ 的一步转化。

```cpp
#include<algorithm>
#include<cstdio>
#define ll long long
#define MaxN 10050000
using namespace std;
int n,m,tp[MaxN],phi[MaxN],p[MaxN>>3],tn,s[MaxN];
void sieve()
{
  phi[1]=1;
  for (int i=2;i<=n;i++){
    if (!phi[i])
      phi[p[++tn]=tp[i]=i]=i-1;
    for (int j=1;j<=tn&&i*p[j]<=n;j++){
      tp[i*p[j]]=p[j];
      if (i%p[j]==0){
        phi[i*p[j]]=phi[i]*p[j];
        break;
      }phi[i*p[j]]=phi[i]*(p[j]-1);
    }
  }
  for (int i=2;i<=n;i++)s[tp[i]]++;
  for (int i=1;i<=n;i++)s[i]+=s[i-1];
}
int calc(int l,int r)
{return (l>=r) ? 0 : s[r]-s[l];}
int main()
{
  scanf("%d",&n);sieve();
  ll perp=0;
  for (int i=2;i<=n;i++)perp+=phi[i]-1;
  ll ans1=1ll*(n-1)*(n-2)/2-perp,ans3=0,ans4=0;
  for (int i=1;i<=tn;i++){
    int buf=s[p[i]]-s[p[i]-1];
    ans3+=1ll*buf*calc(max(n/p[i],p[i]),n/2);
    ans4+=1ll*buf*calc(max(n/2,p[i]),n);
  }printf("%lld",ans1+(perp-ans3-ans4)*2+ans3*3);
  return 0;
}
```

---

## 作者：Ynoi (赞：13)

分类讨论

显然1是不会和任何节点连线的，下面的分析默认忽略1

有这么几种情况

1.两个数不互质，有直接连线

有 $\frac{(n-1)*(n-2)}{2} -\sum_{i=1}^{n}
(\phi(i)-1)$ 个数对
（总的数对 减去 互质 节点对 ）

2. 两个数互质 ，且最小质因数 乘积 <= n

  设这两个数 A , B,最小质因数 a , b
  
   则可以 A -> ab -> B，两步到达
   
   这个可以将所有互质的节点对数减去下面的情况
   
   3.两个数互质 ， 最小质因数 乘积  > n  且 较大的最小质因数 * 2 <= n
   
 设这两个数 A , B,最小质因数 a , b
 
  不妨设 a  < b
 
 则可以 $A->a*2->b*2->B$

 话说 B = b*2 咋办啊
 
 因为b是B的最小质因数，而若这样的话
 B就有一个质因数是2了 所以b = 2   但是 a又是小于b的，所以不可能存在这样的情况
 
 至于处理方法我们可以先统计每个质数作为最小质因数的次数，枚举质数。
 
 设这个质数为p，则 最小质因数在区间[max(p+1,n/p+1) , n/2+1]内的可以形成这种情况的数对，
 
 4.两个数互质 ， 最小质因数 乘积  > n  且 较大的最小质因数 * 2 > n 则这种情况不联通
 
 处理方法同情况3,只是区间改为 [max(p+1,n/2+1),n]
 
 code
 
```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000005
#define LL long long
#define int long long

int n,m,nn,mm;
int phi[MAXN],p[MAXN],a[MAXN],r[MAXN],c[MAXN];
bool isp[MAXN];
LL ans;

void QAQ() {
	mm = n;
	isp[1] = 1;
	
	for(int i = 2; i <= n; i ++) {
		if(isp[i] == 0) {
			nn ++;
			p[nn] = i;
			a[i] = i;
			if(i*2 > n) {
				mm --;
			}
		} 
		for(int j =1; j <= nn; j ++) {
			if(i*p[j] > n) break;
			isp[i*p[j]] = 1;
			a[i*p[j]] = p[j];
			if(i%p[j]  == 0) break;
		}
	}
		
	for(int i = 2; i <= n; i ++) 
		c[a[i]] ++;
		
	phi[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!isp[i]) {
			phi[i] = i-1;
			continue;
		}

		if((i/a[i])%a[i] == 0) 
			phi[i] = phi[i/a[i]]*(a[i]);
		else  phi[i] = phi[i/a[i]]*(a[i]-1);
	}
	for(int i = 1; i <= n; i ++)
		c[i] += c[i-1];
}

int QwQ(int l,int r) {
	if(r < l) return 0;
	return c[r] - c[l-1];
}

signed main()
{
	cin >> n;
	QAQ();
	LL fk = 0,md;
	for(int i  = 2; i <= n; i ++) {
		fk += (phi[i]-1);
	}
	md = ((n-1)*(n-2))>>1;
	md -= fk;
	ans = fk*2+md;
	int cnt = 0;
	for(int i = 1; i <= nn; i ++) {;
		int yy = c[p[i]] - c[p[i]-1];
		ans += yy*QwQ(max(p[i]+1,n/p[i]+1),max(p[i]+1,(n>>1)+1)-1);
		ans -= 2*yy*QwQ(max(p[i]+1,(n>>1)+1),n);
	}
	cout<<ans;
	return 0;
}

```
   
 

---

## 作者：_Fontainebleau_ (赞：3)

今天模拟赛遇到的一道题

## 题意

- 给定一张 $n$ 个顶点的图。
- 对于点 $i,j$，如果 $\gcd(i,j) \not= 1$，则 $i,j$ 间有一条长度为 $1$ 的边。
- 定义 $\operatorname{d}(i,j)$ 表示从 $i$ 到 $j$ 的最短路长度。若 $i,j$ 不连通， $\operatorname{d}(i,j)=0$。
- 求 $\sum\limits_{1\le i<j\le n} \operatorname{d}(i,j)$ 。
- $n\le 10^7$，时限 $\texttt{4s}$。

## 分析

对于两个点 $x,y$ 分类讨论 $\operatorname{d}(x,y)$ 的值。

定义 $p_i$ 表示 $i$ 的最小质因数，$num_i= \sum\limits_{j=1}^{n}[p_j=i]$

- 若 $x,y$ 其中一个为 $1$ 则 $\operatorname{d}(x,y)=0$，我们可以直接把 $1$ 忽略。
- 情况 1：若 $x,y$ 不互质，则 $x,y$ 可以直达， $\operatorname{d}(x,y)=1$。
- $x,y$ 互质。
- - 情况 2：$p_x p_y \le n$， 那么一定有一条 $x \rightarrow p_x p_y \rightarrow y$ 的路， $\operatorname{d}(x,y)=2$ 。
- - 情况 3：$p_x p_y > n$ 且 $p_x,p_y \le \dfrac{n}{2}$，则一定有一条 $x \rightarrow 2p_x \rightarrow 2p_y \rightarrow y$ 的路， $\operatorname{d}(x,y)=3$。很容易证得其他连接方式一定不会更优于此种 $2$ 倍的方式。
- - 情况 4： $p_x,p_y$ 中其中一数大于 $\dfrac{n}{2}$，$\operatorname{d}(x,y)=0$。

以上就是所有可能的情况，我们一个一个来看。

（定义 $ans1,ans2,ans3,ans4$ 分为情况 1,2,3,4 的个数）

### 情况 1

很显然，因为去除了 $1$ ，所以 
$$ans1=C_2^{n-1}- \sum\limits_{i=2}^{n}(\varphi(i)-1)$$

线性筛 $O(n)$ 求 $1\sim n$ 的欧拉函数即可。

### 情况 2

感觉挺难的，那正难则反，我们先算出 $ans3,ans4$， $ans2=C_2^{n-1}-ans1-ans3-ans4$ 。

### 情况 3
不妨令 $p_x < p_y$

易得 
$$ans3=\sum_{i \in \mathbb{P}} \sum _{j\in \mathbb{P},j>i,j\le \lfloor \frac{n}{2}\rfloor ,ij>n} \sum\limits_{x,y,p_x=i,p_y=j}[\gcd(x,y)=1]$$

因为此时 $i,j$ 是 $x,y$ 的最小质因数，且 $ij>n$ ，所以 $x$ 一定不会有大于等于 $p_y$ 的因数，$x,y$ 一定互质。

所以 
$$ans3=\sum_{i\in \mathbb{P}}num_i\sum _{j\in \mathbb{P},j>i,j\le \lfloor \frac{n}{2}\rfloor ,ij>n} num_j$$

此时 $j$ 的取值区间为 $[\max(i+1,\lfloor\frac{n}{i}\rfloor+1),\lfloor \frac{n}{2}\rfloor]$， 这个时候我们直接一波前缀和就行了。

### 情况 4

跟情况 3 一样。

$$ans4=\sum_{i \in \mathbb{P}} \sum _{j\in \mathbb{P},j>i,j> \lfloor \frac{n}{2}\rfloor ,ij>n} \sum\limits_{x,y,p_x=i,p_y=j}[\gcd(x,y)=1]$$

$$ans4=\sum_{i\in \mathbb{P}}num_i\sum _{j\in \mathbb{P},j>i,j> \lfloor \frac{n}{2}\rfloor ,ij>n,j\le n} num_j$$

此时 $j$ 的取值范围为 $[\max(i+1,\lfloor\frac{n}{2}\rfloor+1),n]$，同样是前缀和即可。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<10000007> used;
int p[1000006],cnt;
int phi[10000007],n;
int minn[10000007],s[10000007];
long long ans1,ans2,ans3,ans4;
inline void getphi()
{
	phi[1]=1;
	used[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!used[i])
			p[++cnt]=i,phi[i]=i-1,minn[i]=i;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++)
		{
			int val=i*p[j];
			used[val]=1;
			minn[val]=p[j];
			phi[val]=phi[i]*(i%p[j]?p[j]-1:p[j]);
			if(i%p[j]==0)	break;
		}
	}
	for(int i=2;i<=n;i++)	s[minn[i]]++;
	for(int i=1;i<=n;i++)	s[i]+=s[i-1];
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline long long Calc(int l,int r)
{
	return l>r?0:s[r]-s[l-1];
}
int main()
{
	n=read();
	getphi();
	ans1=1ll*(n-1)*(n-2)/2;
	for(int i=1;i<=n;i++)	ans1-=(phi[i]-1);
	for(int i=1;i<=cnt;i++)
	{
		ans3+=Calc(p[i],p[i])*Calc(max(p[i],n/p[i])+1,n/2);
		ans4+=Calc(p[i],p[i])*Calc(max(p[i],n/2)+1,n);
	}
	ans2=1ll*(n-1)*(n-2)/2-ans1-ans3-ans4;
	printf("%lld\n",ans1*1+ans2*2+ans3*3);
	return 0;
}
```


---

## 作者：whiteqwq (赞：3)

[CF870F Paths](https://www.luogu.com.cn/problem/CF870F)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1795131)

[Codeforces Round 870考试总结](https://zybuluo.com/xiaoziyao/note/1795123)

## 题意

$n$个顶点的图，对于点对$i,j$，如果$\gcd(i,j)>1$那么$i,j$之间有一条长度为$1$的无向边，求图上点对两两之间距离之和。（如果无法到达则距离为$0$）

## 分析

好题。

下面令$\mathbb{P}$为质数集合。

首先不难发现$1$不可能与其他结点连边，因此直接不管$1$。

然后对于点对$(x,y)$分情况讨论（设$minn_x$为$x$的最小质因子，$cnt_x$为$x$作为最小质因子在$[1,n]$的出现次数）：

- $\gcd(x,y)>1$：$x$与$y$有一条长度为$1$的无向边，距离为$1$，这一类边的数量$tot1$显然等于$\frac{(n-1)(n-2)}{2}-\sum_{i=2}^n(\varphi(n)-1)$
- $\gcd(x,y)=1$，继续分情况讨论：
- - $minn_x\times minn_y\leqslant n$，很显然$x$可以到达$minn_x\times minn_y$，然后再到达$y$，距离为$2$，这一类边我不知道为什么总会统计错，最后只能用总点对减去无法到达与其他距离的点对来计算/kk。
- - $minn_x\times minn_y>n$，继续分情况讨论（不妨设$minn_x\leqslant minn_y$）：
- - - $minn_y\leqslant \lfloor\frac{n}{2}\rfloor$，此时有一条这样的路径：$x\leftrightarrow 2minn_x\leftrightarrow2minn_y\leftrightarrow y$（很显然用$3$以及更大的数作为倍数一定不优于$2$），距离为$3$，这一类边的数量为：
$$tot3=\sum_{i\in\mathbb{P}} \sum_{j\in \mathbb{P},j>i,j\leqslant\lfloor\frac{n}{2}\rfloor,ij>n}\sum_{x,y,minn_x=i,minn_y=j}[\gcd(x,y)=1]$$
此时因为$i,j$分别是$x,y$的最小质因子，且$ij>n$，因此枚举的$x,y$的$\gcd$一定为一，那么化简一下：
$$tot3=\sum_{i\in\mathbb{P}}cnt_i\sum_{j\in \mathbb{P},j>i,j\leqslant\lfloor\frac{n}{2}\rfloor,ij>n}cnt_j$$
不难发现$j$的取值是一个区间$[\max\{\lfloor\frac{n}{i}\rfloor+1,i+1\},\lfloor\frac{n}{2}\rfloor]$，记$sum$为$cnt$的前缀和就可以快速计算了。
- - - $minn_y>\lfloor\frac{n}{2}\rfloor$，此时发现无论如何都没有办法从$x$到达$y$，距离为$0$，这一类边的数量为：
$$tot4=\sum_{i\in\mathbb{P}}cnt_i\sum_{j\in\mathbb{P},j>i,j>\lfloor\frac{n}{2}\rfloor,ij>n}cnt_j$$
同样发现$j$的取值范围是区间$[\max\{\lfloor\frac{n}{2}\rfloor+1,i+1\},n]$。（这里没有在左区间的$\max$放入$\lfloor\frac{n}{i}\rfloor+1$的原因是它一定小于等于$\lfloor\frac{n}{2}\rfloor+1$）

上述数组可以用一次线性筛处理出来，加上统计时间复杂度仍为$O(n)$。

## 代码

```
#include<stdio.h>
#define int long long
const int maxn=10000005;
int n,pcnt,all,tot1,tot2,tot3,tot4;
int p[maxn],c[maxn],phi[maxn],cnt[maxn],minn[maxn],sum[maxn];
inline int max(int a,int b){
	return a>b? a:b;
}
inline int calc(int l,int r){
	return l>r? 0:sum[r]-sum[l-1];
}
signed main(){
	scanf("%lld",&n);
	c[1]=phi[1]=1;
	for(int i=2;i<=n;i++){
		if(c[i]==0)
			p[++pcnt]=i,minn[i]=i,phi[i]=i-1;
		for(int j=1;j<=pcnt;j++){
			if(i*p[j]>n)
				break;
			c[i*p[j]]=1,minn[i*p[j]]=p[j];
			if(i%p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
		cnt[minn[i]]++;
	}
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+cnt[i];
	all=tot1=(n-1)*(n-2)/2;
	for(int i=2;i<=n;i++)
		tot1-=(phi[i]-1);
	for(int i=1;i<=pcnt;i++){
		tot3+=cnt[p[i]]*calc(max(n/p[i]+1,p[i]+1),n/2);
		tot4+=cnt[p[i]]*calc(max(n/2+1,p[i]+1),n);
	}
	tot2=(n-1)*(n-2)/2-tot1-tot3-tot4;
	printf("%lld\n",tot1*1+tot2*2+tot3*3+tot4*0);
	return 0;
}
```


---

## 作者：shinkuu (赞：1)

感觉完全没有 `*2700`？

看到题，猜测 $\max dis$ 不会很大，于是按照路径种类分类讨论一下路径 $(i,j)$。下设 $f_i$ 为最小质因数，并且更下面的情况不包括上面的情况。

- $\gcd(i,j)>1$

这种显然 $dis=1$，数量则为 $\sum\limits_n(i-1-\varphi(i))$。

- $f_i\times f_j\le n$

这种可以设置一个中转点为 $f_i\times f_j$。路径则为 $i\to f_i\times f_j\to j$。

考虑怎样计数。发现对于一个 $i$ 计算有多少个满足条件的 $j<i$ 且 $(i,j)$ 不满足上面情况是困难的，但是如果不加后两个要求则是简单的，于是先算总数再减去不满足两个要求的。

计算总数可以考虑对于每个质数 $x$ 找出最大的满足 $x\times y\le n$ 的质数 $y$。并记录一个 $cnt_i$ 表示有多少个 $j$ 满足 $f_j=i$，再对 $cnt$ 做一个前缀和，就可以快速计算了。

然后减去 $i=j$ 和 $\gcd(i,j)>1$ 的情况就行了。

- $f_i\le \dfrac{n}{2}\land f_j\le\dfrac{n}{2}$

思考发现这种的路径即为 $i\to 2\times f_i\to 2\times f_j\times j$。理论上来说这种是比较难计数的，但是还是和上一种一样的思路，正难则反。所有满足上述条件的减去满足前两个条件的数量。就可以轻松解决。

需要线性筛预处理，没什么细节，具体可以参考代码。

code：

```cpp
int n,m,pm[N],c[N],f[N],g[N],phi[N],h[N],s[N];
bool vis[N];
void Yorushika(){
	scanf("%d",&n);
	ll sphi=0;
	rep(i,2,n){
		if(!vis[i]){
			pm[++m]=i,c[m]++;
			f[i]=i,g[i]=m,phi[i]=i-1;
		}
		rep(j,1,m){
			if(i>n/pm[j])break;
			int k=i*pm[j];
			vis[k]=1,f[k]=pm[j];
			c[g[pm[j]]]++;
			if(i%pm[j]==0){phi[k]=phi[i]*pm[j];break;}
			phi[k]=phi[i]*(pm[j]-1);
		}
		sphi+=i-1-phi[i];
	}
	int j=m;
	pm[0]=1;
	rep(i,1,m){
		while(pm[i]>n/pm[j])j--;
		h[i]=j,s[i]=s[i-1]+c[i];
	}
	ll sum=0,cnt=0;
	rep(i,2,n){
		sum+=s[h[g[f[i]]]];
		sum-=f[i]<=n/f[i];
		cnt+=f[i]<=n/2;
	}
	sum/=2,cnt=cnt*(cnt-1)/2;
	printf("%lld\n",(sum-sphi)*2+sphi+(cnt-sum)*3);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：daniEl_lElE (赞：0)

首先，容易观察到 $dis(i,j)\leq 3$。

设 $i$ 的最小非 $1$ 因子为 $sp_i$。

对于可达的 $i,j$，存在一条路径 $i\to 2sp_i\to 2sp_j\to j$。如果 $2sp_i>n$，那么容易发现 $i$ 无法到达任何位置。

$dis(i,j)=1$ 是容易计算的，我们只需要计算出 $\gcd(i,j)=1$ 的位置，从总数中减去即可。

对于 $dis(i,j)\leq2$，我们发现一定存在一条路径为 $i\to sp_i\times sp_j\to j$，计算出 $sp_i=x$ 的数量然后双指针即可计算。

对于 $dis(i,j)\leq3$，根据上文，可以到达的充要条件是 $2sp_i,2sp_j\leq n$，直接统计即可。

最后差分计算一下即可。总复杂度 $O(n)$。

```cpp
#pragma GCC optimize("Ofast","inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool isp[10000005];
int prm[1000005],mu[10000005],mind[10000005],tot;
int cnt[10000005];
signed main(){
	int n; cin>>n;
	for(int i=2;i<=n;i++) isp[i]=1;
	mu[1]=mind[1]=1;
	for(int i=2;i<=n;i++){
		if(isp[i]) prm[++tot]=i,mind[i]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*prm[j]<=n;j++){
			isp[i*prm[j]]=0;
			mu[i*prm[j]]=mu[i]*-1;
			mind[i*prm[j]]=prm[j];
			if(i%prm[j]==0){
				mu[i*prm[j]]=0; break;
			}
		}
	}
	int tp1=0;
	for(int i=1;i<=n;i++) tp1+=(n/i)*(n/i-1)/2*mu[i]; tp1=n*(n-1)/2-tp1;
	int tp2=0;
	for(int i=2;i<=n;i++) cnt[mind[i]]++;
	int sum=n-1,r=n; 
	for(int i=2;i<=n;i++){
		sum-=cnt[i];
		while(i*r>n){
			sum-=cnt[r];
			r--;
		}
		if(sum<0) break;
		tp2+=cnt[i]*sum+cnt[i]*(cnt[i]-1)/2*(i*i<=n);
	}
	int tp3=0;
	for(int i=2;i<=n;i++) if(mind[i]<=n/2) tp3++;
	tp3=tp3*(tp3-1)/2;
	cout<<tp1+(tp2-tp1)*2+(tp3-tp2)*3;
	return 0;
}
```

---

## 作者：EastPorridge (赞：0)

### 题目分析：

提供一种用莫比乌斯反演解决的方法。

用 $mi_x$ 表示数 $x$ 的最小质因子，分类讨论。

1. $1$ 和大于 $\frac{n}{2}$ 的素数没有贡献，排除掉。
2. $\gcd(x,y) \ne 1$，贡献为 $1$，对于数 $x$ 的方案就是 $x -\varphi(x)-1$，$\varphi$ 表示欧拉函数。
3. $mi_x \times mi_y \le n$，贡献为 $2$，太长了要放底下写。
4. 剩余方案可以通过 $x \rightarrow 2\times mi_x \rightarrow 2\times mi_y \rightarrow y$ 联系，贡献为 $3$。

具体对第三种情况讨论，

$$\sum_{i=1}^{n}\sum_{j=1}^{n}[\gcd(i,j)=1][mi_i \times mi_j \le n]$$

使用莫比乌斯反演，

$$\sum_{i=1}^{n}\sum_{j=1}^{n}[\gcd(i,j)=1][mi_i \times mi_j \le n] = \sum_{d=1}^{n} \mu(d)\sum_{d \mid i} \sum_{d \mid j}[mi_i \times mi_j \le n] $$

把 $d=1$ 拿走单列，剩下的就是，

$$\sum_{i=1}^{n}\sum_{j=1}^{n}[mi_i \times mi_j \le n] +\sum_{d=2}^{n} \mu(d)\sum_{d \mid i} \sum_{d \mid j}[mi_i \times mi_j \le n]$$

$d=1$ 直接前缀和开桶搞一下，后面的再分类讨论，

当 $d \le \sqrt n$ 时，因为 $d \mid i$，所以 $mi_i \le mi_d$，则 $mi_i \times mi_j \le {mi_d}^2 \le n$，合法方案数就是 ${\lfloor \frac{n}{d} \rfloor}^2$。

当 $d > \sqrt n$ 时，$i = k_1 \times d,j=k_2 \times d$，因为 $d > \sqrt n$，所以 $k_1,k_2 \le \sqrt n$，

当 $k_1,k_2 \ne 1$ 时，$k_1 \times k_2 \le n$，合法。

当 $k_1 =1,k_2 \ne 1$ 时，就是 $k_2 \times d =j \le n$，合法。

当 $k_1 =1,k_2 = 1$ 时，$d$ 不为质数，则一定有一个质因子 $\le \sqrt n$，$mi_i \times mi_j \le {mi_d}^2 \le n$，合法。

唯一不合法的情况就是 $k_1 =k_2=1$ 且 $d$ 为质数，此时 $mi_i \times mi_j > n$，若出现就该把这个方案减掉，合法方案数就是 ${\lfloor \frac{n}{d} \rfloor}^2-1$。

第四种情况就是总方案数减掉前三种方案，写完了。

### Code.

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e7+10; vector<int> pri; ll s1,s2,pl,tmp;
int n,m,pi[N],mu[N],cnt[N],sum[N],st[N];
signed main()
{
    pi[1]=mu[1]=1; scanf("%d",&n); m=sqrt(n);
    for(int i=2;i<=n;i++)
	{
        if(! st[i]) pri.emplace_back(i),st[i]=i,pi[i]=i-1,mu[i]=-1;
        for(int j : pri)
        {
        	if(i*j > n) break ; st[i*j]=j;
            if(! (i%j)) {pi[i*j]=pi[i]*j; mu[i*j]=0; break;}
            pi[i*j]=pi[i]*(j-1); mu[i*j]=mu[j]*mu[i];
		}
    }
    for(int i=2;i<=n;i++) if(st[i] != i || i <= n/2) pl++,cnt[st[i]]++; pl=pl*(pl-1)/2;
    for(int i=2;i<=n;i++) s1+=i-1-pi[i],sum[i]=sum[i-1]+cnt[i];
    for(int i=2;i<=n;i++) if(st[i] != i || i <= n/2) s2+=sum[n/st[i]];
    for(int i=2;i<=n;i++) {tmp=0; tmp+=1ll*(n/i)*(n/i); if(st[i] == i && i > m) tmp--; s2+=mu[i]*tmp;}
    s2>>=1ll; printf("%lld",1ll*s1+s2*2+(pl-s1-s2)*3);
    return 0;
}
```

---

