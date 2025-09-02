# Enchanted Matrix

## 题目描述

This is an interactive problem.

There exists a matrix $ a $ of size $ n \times m $ ( $ n $ rows and $ m $ columns), you know only numbers $ n $ and $ m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, and columns of the matrix are numbered from $ 1 $ to $ m $ from left to right. The cell on the intersection of the $ x $ -th row and the $ y $ -th column is denoted as $ (x, y) $ .

You are asked to find the number of pairs $ (r, c) $ ( $ 1 \le r \le n $ , $ 1 \le c \le m $ , $ r $ is a divisor of $ n $ , $ c $ is a divisor of $ m $ ) such that if we split the matrix into rectangles of size $ r \times c $ (of height $ r $ rows and of width $ c $ columns, each cell belongs to exactly one rectangle), all those rectangles are pairwise equal.

You can use queries of the following type:

- ? $ h $ $ w $ $ i_1 $ $ j_1 $ $ i_2 $ $ j_2 $ ( $ 1 \le h \le n $ , $ 1 \le w \le m $ , $ 1 \le i_1, i_2 \le n $ , $ 1 \le j_1, j_2 \le m $ ) — to check if non-overlapping subrectangles of height $ h $ rows and of width $ w $ columns of matrix $ a $ are equal or not. The upper left corner of the first rectangle is $ (i_1, j_1) $ . The upper left corner of the second rectangle is $ (i_2, j_2) $ . Subrectangles overlap, if they have at least one mutual cell. If the subrectangles in your query have incorrect coordinates (for example, they go beyond the boundaries of the matrix) or overlap, your solution will be considered incorrect.

You can use at most $  3 \cdot \left \lfloor{ \log_2{(n+m)} } \right \rfloor $ queries. All elements of the matrix $ a $ are fixed before the start of your program and do not depend on your queries.

## 说明/提示

In the example test the matrix $ a $ of size $ 3 \times 4 $ is equal to:

```
<pre class="verbatim"><br></br>1 2 1 2<br></br>3 3 3 3<br></br>2 1 2 1<br></br>
```

## 样例 #1

### 输入

```
3 4
1
1
1
0```

### 输出

```
? 1 2 1 1 1 3
? 1 2 2 1 2 3
? 1 2 3 1 3 3
? 1 1 1 1 1 2
! 2```

# 题解

## 作者：zjjws (赞：6)

$\texttt{updata-2021-03-08}$ 感谢 @Winterspell 的 hack！修正了思路里最后一部分的一个失误，以及代码的错误。（一天审核了三次，麻烦管理员了）


$\texttt{updata-2021-03-08}$ 更正了两处手残错误。


---


“天无二日，@flying2018 是我们永远的红太阳。”$\ \ \ $ ——鲁迅


---

## 题意

对于一个 $n\times m$ 的矩形，将其行 $\frac{n}{r}$ 等分，列 $\frac{m}{w}$ 等分（$r,w$ 就表示子矩阵的长和宽），如果这样分出来的所有子矩形都相同，那么称 $(r,w)$ 为一组合法的二元组。

你每次可以询问两个不相交的矩形是否相等，请在 $3\cdot \lfloor\log_2 (n+m)\rfloor$ 次询问内确定合法解的个数。

---

## Solution

#### Part 1 行列独立

这里是一个很显然的结论：$(r,w)$ 的 **真假** 可以转化成 $(r,m)\&(n,w)$。

前推后显然，后推前也很好证。

那么接下来我们就把问题转为了一维。

---

#### Part 2 单维内寻找最短循环节

就拿行这一维举例。

这里是一个字符串题的常用套路：对于这种分多段全等的问题，只需要找它的最短循环节即可。

我们一开始已知 $n$ 是一个合法解，$n=\prod p_i^{k_i}$，表示成这样的形式之后，由于最短循环节 $r'|n$，所以可以将质因子一个一个试除，来得到 $r'$。

---

#### Part 3 询问策略

如何检测一个长度是否是合法的？

显然按照刚刚的检查策略的话，我们对于一次检测长度 $r'$ 是否合法的时候，只有最多 $3$ 次机会。

以下称分成的段数 $\frac{n}{r'}$ 为 $L$。

这里又是一个字符串题的常见套路：你此时把每按检测长度 $r'$ 分好的每一段 **看作一个元素**，然后就是一个询问是否全部相等的问题。

- 对于只有两个元素的话，直接询问即可。

- 大于等于三个元素的话，此时 $L$ 因为是大于 $2$ 的质因数，所以必定为奇。考虑如果没有不能重叠这个限制，我们可以直接问 $[1,L-1],[2,L]$ 是否相等。对于这个不能重叠的限制的话，我们也可以利用这个原理，不过是找到另一个 **公共串** 来进行询问。具体的，对于我们想询问是否全等的串 $[l,r]$，我们可以将 $[l,r-1]$ 和 $[l+1,r]$ 分别与 $[1,r-l]$ 进行询问，这也就要求 $r<2l$。我们可以利用这个原理来查询 $[\frac{L+1}{2},L]$ 是否完全相等，并且也可以知道 $[1,\frac{L-1}{2}]$ 与 $[\frac{L+1}{2},L-1]$ 相等，从而推出所有元素相等。

---

## Code

```cpp
#include <queue>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define LL long long
using namespace std;
inline int rin()
{
    int s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
inline void jh(int &x,int &y){if(x^y)x^=y^=x^=y;return;}
inline void jh(LL &x,LL &y){if(x^y)x^=y^=x^=y;return;}

const int N=1e5+3;
int n,m,nm;
bool tag;
int sk[N];
inline int find(int L,int R,int x)
{
    if(tag)printf("? %d %d %d %d %d %d\n",n,x,1,L,1,R);
    else printf("? %d %d %d %d %d %d\n",x,m,L,1,R,1);fflush(stdout);
    return rin();
}
inline int que(int L,int R)
{
    if(L==2)return find(1,R+1,R);
    int mid=R*(L>>1);return find(1,mid+R+1,mid)&&find(1,mid+1,mid)&&find(R+1,mid+R+1,mid);
}
inline void def(LL ans){printf("! %lld\n",ans);fflush(stdout);return;}
inline void init()
{
    n=rin();m=rin();nm=max(n,m);
    for(int i=1;i<=nm;i++)sk[i]=i;
    for(int i=2;i<=nm;i++)for(int j=i<<1;j<=nm;j+=i)sk[j]=min(i,sk[j]);
    return;
}
inline void work()
{
    init();
    int n_R=n,m_R=m;
    int cutt_n=0,cutt_m=0;
    tag=false;for(int i=n;i>1;i/=sk[i])if(que(sk[i],n_R/sk[i]))n_R/=sk[i];
    tag=true;for(int i=m;i>1;i/=sk[i])if(que(sk[i],m_R/sk[i]))m_R/=sk[i];
    
    int n_L=n,m_L=m;n_L/=n_R;m_L/=m_R;
    for(int i=1;i<=n_L;i++)if(!(n_L%i))cutt_n++;
    for(int i=1;i<=m_L;i++)if(!(m_L%i))cutt_m++;
    def(1LL*cutt_n*cutt_m);
    return;
}
int main()
{
    work();
    return 0;
}
```

---

## 作者：Hiiragi_Utena (赞：5)

翻译里有个地方说的不太清楚，题目要求 $r|n,c|m$。

求出题目答案则相当于是找出最小的循环节 $r_{min},c_{min}$，最终答案为 $\dfrac{n}{r_{min}}$ 的约数个数与 $\dfrac{m}{c_{min}}$ 的约数个数之积。可以行和列单独考虑，把问题转化为一维的问题。

拿行来举例。不妨假设 $n=\prod p_i^{\alpha_i}$，其中 $p_i$ 为指数。对于每个 $p_i$，需要求出 $c_{min}$ 中 $p_i$ 的次数 $x_i$。

可以先判断 $\dfrac{n}{p_i}$ 是不是整个序列的循环节。若是，则继续判断 $\dfrac{n}{p_i^2}$ 是不是序列中前 $\dfrac{n}{p_i}$ 项的循环节。如果还是的话，就代表 $\dfrac{n}{p_i^2}$ 是整个序列的循环节，继续以此类推。若检查到某项 $\dfrac{n}{p_i^t}$ 发现不是循环节，则 $x_i=\alpha_i-t+1$。

于是问题转化为如何检查序列中 $[1,r]$ 项存不存在长度为 $\dfrac{r}{p_i}$ 的循环节。这个过程将会最多执行 $\alpha_i$ 次。

考虑倍增：询问 $[1,\dfrac{r}{p_i}]$ 与 $[\dfrac{r}{p_i}+1,\dfrac{r}{p_i}\times2]$ 是否相等，$[1,\dfrac{r}{p_i}\times2]$ 与 $[\dfrac{r}{p_i}\times2+1,\dfrac{r}{p_i}\times4]$ 是否相等，$[1,\dfrac{r}{p_i}\times4]$ 与 $[\dfrac{r}{p_i}\times4+1,\dfrac{r}{p_i}\times8]$ 是否相等……

上述过程最多使用 $\log p_i$ 次询问。对于 $n$ 行总询问次数为 $\sum\alpha_i\times\log p_i=\sum\log p_i^{\alpha_i}=\log n$。可以通过此题。

---

## 作者：Leap_Frog (赞：3)

### Description.
略  

### Solution.
本质是找循环节，而且行列可以拆开，分别判断。  
~~但是我寻思 $\mathcal O(\log n+\log m)$ 不是应该 $=\mathcal O(\log nm)$ 吗，为什么会给个 $\mathcal O(\log_2(n+m))$~~  
判循环节可以直接分解质因数然后试除，复杂度已经有一个 $\mathcal O(\log n)$ 了。  
所以我们需要 $O(1)$ 判断一个串是否是循环节。  

有一个很显然的做法就是和判断循环节一样，判断 $[1,n-l]$ 是否等于 $[l+1,n]$。  
但是发现原题不让重叠，这怎么办呢？  

首先如果循环数量是 $2$，那直接判就行了。  
但是如果循环数量是 $3$，一次肯定无法判断。  
发现 $3\log_2(2\times 10^3)\approx 30$，而 $2\log_3(2\times 10^3)\approx 14$，所以对于 $3$ 及以上的循环数量，可以用 $2$ 步来判断。  

考虑试除的过程，我们是枚举每个质数来判断能否构成这么多个循环节。  
所以如果循环数量不是 $2$ 就肯定是一个奇质数。  
用两步，可以考虑增加一个辅助变量。  
我们可以把它拆成两段，则有一段多一个，设是右边那段。  
然后可以分别匹配（左段和右段去头）和（左段和右段去尾）。  
这样如果都匹配成功，则右段是循环串，左段和右段基本相同，也是循环串。  
这样就用两次 check 了一个奇质数。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=1005;int n,m,tx[105],xt,ty[105],yt,rn,rm;
const int V=1005;int pr[V],pc,ls[V],ph[V],mu[V];char pv[V];//prinit{{{
inline void prinit(int n=V-1)
{
	pv[1]=mu[1]=ph[1]=1,ls[1]=0;for(int i=1;i<=n;i++)
	{
		if(!pv[i]) pr[++pc]=i,mu[i]=-1,ph[i]=i-1,ls[i]=i;
		for(int j=1;j<=pc&&i*pr[j]<=n;j++)
		{
			ls[i*pr[j]]=pr[j],mu[i*pr[j]]=i%pr[j]?-mu[i]:0;
			ph[i*pr[j]]=ph[i]*(pr[j]-!!(i%pr[j]));
			pv[i*pr[j]]=1;if(i%pr[j]==0) break;
		}
	}
}//}}}
inline int qryn(int len,int l,int r)
{
	printf("? %d %d %d %d %d %d\n",len,m,l,1,r,1);
	int vl;fflush(stdout),read(vl);return vl;
}
inline int qrym(int len,int l,int r)
{
	printf("? %d %d %d %d %d %d\n",n,len,1,l,1,r);
	int vl;fflush(stdout),read(vl);return vl;
}
inline char chkn(int cnt)
{
	if(cnt==2) return qryn(rn/2,1,rn/2+1);
	int ln=rn/cnt,md=cnt/2;
	return qryn(md*ln,1,md*ln+1)&&qryn(md*ln,1,(md+1)*ln+1);
}
inline char chkm(int cnt)
{
	if(cnt==2) return qrym(rm/2,1,rm/2+1);
	int ln=rm/cnt,md=cnt/2;
	return qrym(md*ln,1,md*ln+1)&&qrym(md*ln,1,(md+1)*ln+1);
}
int main()
{
	read(n,m),prinit();int xx=0,yy=0,rs=1,c1=1,c2=1;
	int x=n;rn=n;while(x!=1) tx[++xt]=ls[x],x/=ls[x];
	int y=m;rm=m;while(y!=1) ty[++yt]=ls[y],y/=ls[y];
	for(int i=1;i<=xt;i++) if(chkn(tx[i])) rn/=tx[i],tx[++xx]=tx[i];
	for(int i=1;i<=yt;i++) if(chkm(ty[i])) rm/=ty[i],ty[++yy]=ty[i];
	for(int i=1;i<=xx;i++) if(tx[i]==tx[i-1]) c1++;else rs*=c1,c1=2;
	for(int i=1;i<=yy;i++) if(ty[i]==ty[i-1]) c2++;else rs*=c2,c2=2;
	return printf("! %d\n",rs*c1*c2),fflush(stdout),0;
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

人类智慧题。

首先发现行和列可以拆开来询问。

也就是如果 $(1,1)-(n,d),(1,d+1)-(n,2d),\cdots,(1,m-d+1)-(n,m)$ 均相等，且 $(1,1)-(c,m),(c+1,1)-(2c,m),\cdots,(n-c+1,m)-(n,m)$ 均相等，则 $\frac{m}{d}-1$ 条竖分割线和 $\frac{n}{c}-1$ 条横分割线构成的每个方格也必然全部相等。

接下来只考虑行的情况。首先如果我们判定 $d$ 已经是一个合法答案，则我们询问 $c$ 是否合法时，只需要询问 $(1,d)$ 的内容即可。我们考虑每次看一下把 $(1,d)$ 分成 $p$ 段是否合法，其中 $p$ 是 $d$ 的最小质因数，因为如果分成 $p$ 段都不合法，则分成 $kp$ 段必然也不合法，再判 $p$ 的次小质因数……以此类推即可。至多判 $\Theta(\log{n})$ 遍。

则现在问题在于，如何在较少的次数内判断将 $(1,d)$ 分成 $p$ 段是否合法。

首先 $p=2$ 时可以暴力做，我们考虑 $p\ge 3$ 的情况。

我们考虑先看一下前 $\frac{p}{2}$ 段和后 $\frac{p}{2}$ 段是否合法，如果合法，我们需要判断 $\frac{d}{p}$ 是否是 $(1,\frac{d}{2})$ 的一个循环节，这是一个经典结论（类似于字符串 border（？），~~但是我也不会证~~，判一下 $(1,\frac{d}{2})$ 和 $(1+\frac{d}{p},\frac{d}{2}+\frac{d}{p})$ 是否相等即可。这样子我们就在 $3$ 次询问判定了分成 $p\ge 3$ 段是否合法。

至于询问次数：由于长度为 $2$ 只需要问两遍，所以当 $2$ 很多时不优，所以我们尽可能让 $n$ 的质因子当中 $3$ 尽可能多。

也就是要问 $2\cdot(\log_3{n}+\log_3{m})\le 4\cdot \log_3{n}\le 4\cdot \frac{\log_2{n}}{\log_2{3}}\le 2.52\log_2{n}\le 3\cdot \lfloor \log_2{(n+m)}\rfloor$ 次。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e3+5;
int d[N],n,m;
void init() {
    cl(d,0x3f);
    int p=max(n,m);
    rep(i,2,p) {
        rep(j,1,p/i)
            chkmin(d[i*j],i);
    }
}
bool ask(int l,int r,int x,bool op) {
    if(op)
        printf("? %d %d %d %d %d %d\n",x,m,l,1,r,1);
    else
        printf("? %d %d %d %d %d %d\n",n,x,1,l,1,r);
    fflush(stdout);
    int c;
    scanf("%d",&c);
    return c;
}
bool check(int len,int x,bool op) {
	if(x==2) 
        return ask(1,len/2+1,len/2,op);
	int l=len/x,k=x/2;
	return ask(1,k*l+1,k*l,op)&&ask(1,(k+1)*l+1,k*l,op);
}
int solve(int n,bool op) {
    int tmp=n,res=n;
    while(n!=1) {
        if(check(res,d[n],op))
            res/=d[n];
        n/=d[n];
    }
    int t=tmp/res,cnt=0;
    rep(i,1,t) {
        if(t%i==0)
            ++cnt;
    }
    return cnt;
}
signed main() {
    scanf("%d%d",&n,&m);
    init();
	int res1=solve(n,1),res2=solve(m,0);
    printf("! %lld\n",1ll*res1*res2);
	fflush(stdout);
    return 0;
}
```

---

## 作者：Anonymely (赞：1)

模拟赛碰到的题，来写一发。

关于循环节问题肯定是要找最小循环节，而二维矩形明显能拆成两个一维问题，最后乘起来即可，下面以行为例。

然后考虑循环节一定是 $n$ 的因子，于是对于一个质因数 $p$，每次考虑检验前 $\frac{n}{p^x}$ 个中，按照 $\frac{n}{p^{x+1}}$ 分成的 $p$ 块是否相等，不相等时即可知道最小循环节有多少个 $p$。

检验的话考虑倍增，每次询问 $[1,2^i]$ 块和 $[2^i+1,2^{i+1}]$ 块是否相等，最后一点单独处理。

总次数为 $\sum k_i \times \log p_i= \sum \log p_i^{k_i}= \log n$。


```cpp
int simons(int a, int b, int c, int d, int e, int f) {
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
	int w;
	cin >> w;
	return w;
}

int truth(int n, int m) {
	auto div = [&](int x) {
		vector < pair <int, int> > p;
		for (int i = 2; i <= x; i++) {
			if (x % i == 0) {
				int c = 0;
				while (x % i == 0) x /= i, c++;
				p.emplace_back(i, c);
			}
		}
		return p;
	};

	auto p = div(n);
	int nres = 1;
	for (auto [x, c] : p) {
		int lst = n, cc = 0;
		for (int i = 1; i <= c; i++) {
			int nw = lst / x;

			auto chk = [&](int r) -> bool {
				int lst = 0;
				for (int i = 1; i * 2 <= x; i *= 2) {
					if (!simons(i * r, m, 1, 1, i * r + 1, 1)) return 0;
					lst = i * 2;
				}
				lst = x - lst;
				if (!lst) return 1;
				return simons(lst * r, m, 1, 1, r * x - lst * r + 1, 1);
			};

			if (!chk(nw)) break;
			lst /= x;
			cc++;
		}
		nres *= pow(x, c - cc);
	}

	p = div(m);
	int mres = 1;
	for (auto [x, c] : p) {
		int lst = m, cc = 0;
		for (int i = 1; i <= c; i++) {
			int nw = lst / x;

			auto chk = [&](int r) -> bool {
				int lst = 0;
				for (int i = 1; i * 2 <= x; i *= 2) {
					if (!simons(n, i * r, 1, 1, 1, i * r + 1)) return 0;
					lst = i * 2;
				}
				lst = x - lst;
				if (!lst) return 1;
				return simons(n, lst * r, 1, 1, 1, r * x - lst * r + 1);
			};

			if (!chk(nw)) break;
			lst /= x;
			cc++;
		}
		mres *= pow(x, c - cc);
	}

	nres = n / nres, mres = m / mres;
	// debug(nres, mres);
	auto cal = [&](int x) {
		int cc = 0;
		for (int i = 1; i <= x; i++) {
			if (x % i == 0) cc++;
		}
		return cc;
	};
	return cal(nres) * cal(mres);
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑对于 $n$ 和 $m$ 的因子判断是否为循环节，以 $n$ 为例。设 $n=\prod_{i=1}^kp_i^{q_i}$，那么我们只需要判断 $\frac{n}{p_i^j}$ 是否为循环节即可，其中 $1\leq j\leq q_i$。

容易构造出一种仅需两步的方案，即，询问前 $(p_i^j-1)\times\frac{n}{p_i^j}$ 行与后 $(p_i^j-1)\times\frac{n}{p_i^j}$ 行是否相等即可。如果相等，那么第 $\frac{n}{p_i^j}\times k+1\sim \frac{n}{p_i^j}\times (k+1)$ 与 $\frac{n}{p_i^j}\times (k+1)+1\sim \frac{n}{p_i^j}\times (k+2)$ 行相等，进而推得 $\frac{n}{p_i^j}$ 是一个循环节。

最后将所有质因子得到的最大的 $j$ 加一相乘即为行的答案。

对于列同样处理即可。

精细分析一下是在交互次数内的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool query(int a,int b,int c,int d,int e,int f){
	cout<<"? "<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<"\n";
	fflush(stdout);
	bool ok; cin>>ok;
	return ok;
}
signed main(){
	int n,m; cin>>n>>m;
	int ans=1;
	{
		int t=n;
		int tot=1;
		for(int i=2;i<=t;i++){
			if(t%i==0){
				if(i==2){
					for(int j=i,k=1;;j*=i,k++){
						int ok=query(n/j,m,1,1,n/j+1,1);
						if(!ok){
							tot*=k;
							break;
						}
						if(t%(j*i)!=0){
							tot*=(k+1);
							break;
						}
					}
				}
				else{
					int ok=1,p;
					p=query(n/i*(i/2),m,1,1,n/i*(i/2)+1,1); ok&=p;
					p=query(n/i*(i/2),m,1,1,n/i*(i/2+1)+1,1); ok&=p;
					if(ok){
						if(t%(i*i)!=0){
							tot*=2;
						}
						else{
							for(int j=i*i,k=2;;j*=i,k++){
								int ok=query(n/j*(i-1),m,1,1,n-n/j*(i-1)+1,1);
								if(!ok){
									tot*=k;
									break;
								}
								if(t%(j*i)!=0){
									tot*=(k+1);
									break;
								}
							}
						}
					}
				}
				while(t%i==0) t/=i;
			}
		}
		ans*=tot;
	}
	{
		int t=m;
		int tot=1;
		for(int i=2;i<=t;i++){
			if(t%i==0){
				if(i==2){
					for(int j=i,k=1;;j*=i,k++){
						int ok=query(n,m/j,1,1,1,m/j+1);
						if(!ok){
							tot*=k;
							break;
						}
						if(t%(j*i)!=0){
							tot*=(k+1);
							break;
						}
					}
				}
				else{
					int ok=1,p;
					p=query(n,m/i*(i/2),1,1,1,m/i*(i/2)+1); ok&=p;
					p=query(n,m/i*(i/2),1,1,1,m/i*(i/2+1)+1); ok&=p;
					if(ok){
						if(t%(i*i)!=0){
							tot*=2;
						}
						else{
							for(int j=i*i,k=2;;j*=i,k++){
								int ok=query(n,m/j*(i-1),1,1,1,m-m/j*(i-1)+1);
								if(!ok){
									tot*=k;
									break;
								}
								if(t%(j*i)!=0){
									tot*=(k+1);
									break;
								}
							}
						}
					}
				}
				while(t%i==0) t/=i;
			}
		}
		ans*=tot;
	}
	cout<<"! "<<ans;
	return 0;
}z
```

---

## 作者：Exp10re (赞：0)

### 解题思路

不难注意到行和列的询问是独立的，求出列的答案和行的答案相乘即为最终答案，问题转化为数列上求两个区间是否全等。

考虑 $r_1=\frac n {t_1}$ 满足条件的充分非必要条件：存在 $r_2=\frac n {t_2}$ 满足条件，其中 $t_2=kt_1,k\in \mathbb{Z}^+$。

故将 $n$ 质因数分解，对每一个质因数以及其的次幂 $t=p^k$ 产生的 $r=\frac n t$ 进行判断是否有解，其是 $\log_2 n$ 规模的。

考虑判定 $r$ 的方法：记其被分割成 $t$ 块，根据 $t$ 的奇偶性可以得到以下做法：

- 若 $t \mid 2$，询问第 $1,\cdots,\frac t 2$ 块与第 $\frac t 2+1,\cdots,t$ 块是否全等，询问第 $2,\cdots,\frac t 2$ 块与第 $\frac t 2+1,\cdots,t-1$ 块是否全等，若均全等则所有块全等。
- 若 $t \nmid 2$，询问第 $1,\cdots,\frac {t-1} 2$ 块与第 $\frac {t-1} 2+1,\cdots,t-1$ 块是否全等，询问第 $1,\cdots,\frac {t-1} 2$ 块与第 $\frac {t-1} 2+2,\cdots,t$ 块是否全等，若均全等则所有块全等。

证明可以考虑：对于一次询问 $l_1,\cdots,l_1+k$，$l_2,\cdots,l_2+k$ 是否全等，若答案是全等，则第 $l_1+i$ 块向第 $l_2+i$ 块连边，两块全等当且仅当其在一个连通块内，不难发现，上述询问方案若都全等最最终的结果是所有块都在一个连通块内。

故两次询问可以判断一个 $r$ 是否合法，$c$ 同理，故询问次数为 $\lfloor 4\log_2 (n+m)\rfloor$，加上优化（即：若 $p^k$ 有解则 $p^{k-\Delta}$ 有解，并且不进行重复的询问）可以卡到 $\lfloor 2\log_2 (n+m)\rfloor +eps$，可以通过。

---

