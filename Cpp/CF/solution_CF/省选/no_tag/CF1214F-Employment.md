# Employment

## 题目描述

两家大型公司“Cecsi”和“Poca Pola”长期以来一直在相互竞争。为了击败对手，“Poca Pola”启动了一个超级机密项目，该项目在所有办公室总共有 $n$ 个空缺职位。经过多轮测试和面试后，选出了 $n$ 名候选人，现在只剩下雇佣他们这一步。

由于所有候选人的能力相同，因此他们在哪个办公室工作并没有区别。因此，公司决定将候选人分配到各个工作地点，使得所有候选人从家到工作地点的总距离最小。

众所周知，地球是圆的，因此可以用一个圆来描述，地球上的 $m$ 个城市可以表示为这个圆上的点。所有城市从 $1$ 到 $m$ 编号，对于每个 $i$（$1 \le i \le m - 1$），编号为 $i$ 和 $i+1$ 的城市是相邻的，编号为 $1$ 和 $m$ 的城市也是相邻的。人们只能沿着圆移动。任意两个城市之间的距离等于从一个城市到另一个城市所需经过的最少相邻城市数。特别地，一个城市到自身的距离为 $0$。

“Poca Pola”的空缺职位分布在城市 $a_1, a_2, \ldots, a_n$。候选人居住在城市 $b_1, b_2, \ldots, b_n$。可能有多个职位在同一个城市，也可能有多个候选人住在同一个城市。

“Poca Pola”的管理层因为太忙于超级机密项目，所以请你帮忙，将候选人分配到各个工作地点，使得所有候选人从家到工作地点的总距离最小。

## 说明/提示

在第一个样例中，每个候选人到其工作地点的距离均为 $1$（从 $1$ 到 $10$，从 $4$ 到 $5$，从 $6$ 到 $5$）。

在第二个样例中：

- 第二位候选人被分配到第一个工作地点，城市 $3$ 到 $1$ 的距离为 $2$。
- 第三位候选人被分配到第二个工作地点，城市 $6$ 到 $4$ 的距离为 $2$。
- 第一位候选人被分配到第三个工作地点，城市 $8$ 到 $8$ 的距离为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10 3
1 5 5
10 4 6
```

### 输出

```
3
1 2 3 ```

## 样例 #2

### 输入

```
10 3
1 4 8
8 3 6
```

### 输出

```
4
2 3 1 ```

# 题解

## 作者：duyi (赞：18)

我们把人和办公室都按位置排序。如果不考虑环形，此时的答案一定是第$1$个人匹配第$1$个办公室，第$2$个人匹配第$2$个办公室，以此类推。证明：如果交换两个相邻的匹配，则总距离要么变长，要么不变。

推广到环形上，如果我们确定了$a_1$匹配$b_i$，则$a_2$一定匹配$b_{i+1}$，以此类推。可以理解为，我们需要找一个$b_i$，在$b_i-1$和$b_i$之间把环断成一条链。

如果我们枚举这个断点$i$，复杂度是$O(n^2)$的。

本质上我们有$n$种匹配方式，即对于$p\in [0,n)$，令$a_i$匹配$b_{i+p}$。

不能依次枚举匹配方式，我们就反过来考虑**每个点对每种匹配方式下距离和的贡献**。

假设有一个办公室坐标为$x$，它匹配了坐标为$y$一个的人。即$a_i=x$匹配到了$b_j=y$。它们对距离和的贡献可能有如下四种情况：

- $x\geq y,x-y\leq \lfloor\frac{m}{2}\rfloor$，距离为$x-y$，$a_i$的贡献为$x$。


- $x\geq y,x-y>\lfloor\frac{m}{2}\rfloor$，距离为$m-x+y$，$a_i$的贡献为$-x$。

- $x<y,y-x\leq \lfloor\frac{m}{2}\rfloor$，距离为$y-x$，$a_i$的贡献为$-x$。

- $x<y,y-x>\lfloor\frac{m}{2}\rfloor$，距离为$m-y+x$，$a_i$的贡献为$x$。

距离中$m$的贡献可以摊到$a_i$或$b_j$中计算，即：强行视作$a_i$的贡献或$b_j$的贡献。

我们发现，如果枚举$i$，能使$a_i$产生某类贡献的$j$是一个特定的区间，这个区间可以二分出来。而这个区间的$i-j$的值也恰好也对应了$[0,n)$中的某一段$p$。我们要维护每个$p$下的距离和，那么此时我们只需对这段$p$的距离和加上$a_i$对它的贡献即可。这个区间加的操作可以用差分维护。


复杂度$O(n\log n)$。


#### 参考代码：


```cpp
//problem:CF1214F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fst first
#define scd second

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

inline int read(){
	int f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline ll readll(){
	ll f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN=2e5+5;
int n,m,va[MAXN],vb[MAXN],res[MAXN];
pii a[MAXN],b[MAXN];
ll s[MAXN];
inline void add(int l,int r,int x){
	if(l<0 && r<0)l+=n,r+=n;
	if(l<0)s[l+n]+=x,l=0;
	s[l]+=x;s[r+1]-=x;
}
int main() {
	m=read();n=read();
	for(int i=1;i<=n;++i)a[i].fst=read(),a[i].scd=i;
	for(int i=1;i<=n;++i)b[i].fst=read(),b[i].scd=i;
	sort(a+1,a+n+1);sort(b+1,b+n+1);
	for(int i=1;i<=n;++i)va[i]=a[i].fst,vb[i]=b[i].fst;
	for(int i=1;i<=n;++i){
		int x=b[i].fst;
		if((x-1)<=m-(x-1)){
			int l=1,r=x;
			int ql=lob(va+1,va+n+1,l)-va;
			int qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,x);
		}else{
			int l=x-m/2,r=x;
			int ql=lob(va+1,va+n+1,l)-va;
			int qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,x);
			r=l-1;l=1;
			ql=lob(va+1,va+n+1,l)-va;
			qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,m-x);
		}
		if((m-x)<=m-(m-x)){
			int l=x+1,r=m;
			int ql=lob(va+1,va+n+1,l)-va;
			int qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,-x);
		}else{
			int l=x+1,r=x+m/2;
			int ql=lob(va+1,va+n+1,l)-va;
			int qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,-x);
			l=r+1,r=m;
			ql=lob(va+1,va+n+1,l)-va;
			qr=upb(va+1,va+n+1,r)-va-1;
			add(i-qr,i-ql,m+x);
		}
	}
	for(int i=1;i<=n;++i){
		int x=a[i].fst;
		if((x-1)<=m-(x-1)){
			int l=1,r=x-1;
			int ql=lob(vb+1,vb+n+1,l)-vb;
			int qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,x);
		}else{
			int l=x-m/2,r=x-1;
			int ql=lob(vb+1,vb+n+1,l)-vb;
			int qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,x);
			r=l-1;l=1;
			ql=lob(vb+1,vb+n+1,l)-vb;
			qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,-x);
		}
		if((m-x)<=m-(m-x)){
			int l=x,r=m;
			int ql=lob(vb+1,vb+n+1,l)-vb;
			int qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,-x);
		}else{
			int l=x,r=x+m/2;
			int ql=lob(vb+1,vb+n+1,l)-vb;
			int qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,-x);
			l=r+1;r=m;
			ql=lob(vb+1,vb+n+1,l)-vb;
			qr=upb(vb+1,vb+n+1,r)-vb-1;
			add(ql-i,qr-i,x);
		}
	}
	ll ans=1e18;int pos=0;
	for(int i=0;i<n;++i){
		if(i)s[i]+=s[i-1];
		if(s[i]<ans)ans=s[i],pos=i;
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i)if(i+pos<=n)res[a[i].scd]=b[i+pos].scd;else res[a[i].scd]=b[i+pos-n].scd;
	for(int i=1;i<=n;++i)printf("%d ",res[i]);puts("");return 0;
}
```


---

## 作者：ljc20020730 (赞：6)

首先，最优的方案必然满足：

> 按照$a,b$升序排列，指定$a_1$对应$b_k$，那么$a_i$必然对应$b_{(k+i-1)\% n + 1}$

换句话说，只要确定一个断环的位置，那么最优的方案就唯一确定了，在断环后的序列中，每一个人都去寻找自己最近的一个目标。

可以用微扰法简单证明。

> 若存在两个相邻元素$x,y$，设其目标为$b_x,b_y$，但是$p_{b_x} > p_{b_y}$，那么显然交换两个元素的目标，答案会更优。

通过这个贪心，问题就转化为：


> 对$a,b$排序后，设$d\in[0,n)$为增量 ， 求$\min\limits_{d=0}^{n-1} \{\sum\limits_{i=1}^{n} dist(a_i,b_{i+d})\}$

于是我们可以用$O(n^2)$来求解。

为了更快速的解决问题，我们需要对上述算法优化。

假设 $j = i + d$，那么区间长度为$d = j - i$。

- $a_i \leq b_j$ , $b_j - a_i \leq a_i - b_j + m$ , 贡献为$(-a_i) + (b_j)$
- $a_i \leq b_j$ , $b_j - a_i >  a_i - b_j + m$ , 贡献为$(-a_i+ m)  + (b_j)$
- $a_i > b_j$ , $a_i - b_j \leq b_j - a_i + m$ , 贡献为$(a_i) - (b_j)$
- $a_i > b_j$ , $a_i - b_j > b_j - a_i + m$ , 贡献为$(-a_i) + (b_j +m)$

对于每一个增量$d$的答案是$f_d$，那么显然这些$f_d$都是分别由$a_i$和$b_i$来贡献的。

我们可以使用$O(n)$的复杂度确定一个$a_i$，然后将符合条件的$b_j$来归成四种可能中的一种，分别用$a_i$对应的贡献，去更新$f_{j-i}$的值。

具体来说，若指定的$a_i$让$b_j$在区间$j \in [l,r]$中满足：

- $2a_i \leq 2b_j \leq 2a_i+m$ , 我们就用$-a_i$的贡献去更新$d \in [l-i,r-i]$
- $2a_i + m+ 1\leq 2b_j $ , 我们就用$a_i + m$的贡献去更新$d \in [l-i,r-i]$
- $2a_i - m\leq 2b_j\leq 2a_i - 1 $ , 我们就用$a_i$的贡献去更新$d \in [l-i,r-i]$
-  $ 2b_j\leq 2a_i - m-1 $ , 我们就用$-a_i$的贡献去更新$d \in [l-i,r-i]$

注意到，上述的分类讨论我们发现对于一个确定的$a_i$，对于$b_j$数组来说，被切分为最多$4$段，对于每一段里的$d = j - i $都使用相同的关于$a_i$的贡献来区间更新。

这显然可以使用差分来维护。

同理，如果我们使用$O(n)$的复杂度去确定一个$b_j$，那么对应位$a_i$同样会被切分成最多$4$段，每段都使用相同的关于$b_j$的贡献来更新。

本题总复杂度$O(n \ log_2 \  n )$。

```cpp
# pragma GCC optimize(3)
# include<bits/stdc++.h>
# define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],aa[N],bb[N],c[N],ans[N];
int n,m;
pair<int,int>t1[N],t2[N];
inline int read() {
    int X=0,w=0; char c=0;
    while(c<'0'||c>'9') {w|=c=='-';c=getchar();}
    while(c>='0'&&c<='9') X=(X<<3)+(X<<1)+(c^48),c=getchar();
    return w?-X:X;
}
void update(int l,int r,int d){c[l]+=d; c[r+1]-=d;}
void modify(int l,int r,int d) {
	if (l>r) return;
	l=((l+n)%n+n)%n; r=((r+n)%n+n)%n;
	if (l>r) update(l,n-1,d),update(0,r,d);
	else update(l,r,d);
}
signed main()
{
	m=read();n=read();
	for (int i=1;i<=n;i++) t1[i]=make_pair(read(),i);
	for (int i=1;i<=n;i++) t2[i]=make_pair(read(),i);
	sort(t1+1,t1+1+n); sort(t2+1,t2+1+n);
	for (int i=1;i<=n;i++) {
		a[i]=t1[i].first; aa[i]=a[i]<<1;
		b[i]=t2[i].first; bb[i]=b[i]<<1;
	}
	for (int i=1;i<=n;i++) {
		int l=1,r=upper_bound(bb+1,bb+1+n,aa[i]-m-1)-bb-1;
		modify(l-i,r-i,-a[i]);
		l=r+1; r=upper_bound(bb+1,bb+1+n,aa[i]-1)-bb-1;
		modify(l-i,r-i,a[i]);
		l=r+1; r=upper_bound(bb+1,bb+1+n,aa[i]+m)-bb-1;
		modify(l-i,r-i,-a[i]);
		l=r+1; r=n;
		modify(l-i,r-i,a[i]+m);
	}
	for (int i=1;i<=n;i++) {
		int l=1,r=upper_bound(aa+1,aa+1+n,bb[i]-m-1)-aa-1;
		modify(i-r,i-l,-b[i]);
		l=r+1; r=upper_bound(aa+1,aa+1+n,bb[i])-aa-1;
		modify(i-r,i-l,b[i]);
		l=r+1; r=upper_bound(aa+1,aa+1+n,bb[i]+m)-aa-1;
		modify(i-r,i-l,-b[i]);
		l=r+1; r=n;
		modify(i-r,i-l,b[i]+m);
	}
	int pos=0;
	for (int i=1;i<n;i++)
		c[i]+=c[i-1],pos=(c[i]<c[pos])?i:pos;
	printf("%lld\n",c[pos]);
	for (int i=1,j=pos+1;i<=n;i++,j=(j==n)?1:j+1) ans[t1[i].second]=t2[j].second;
	for (int i=1;i<=n;i++) printf("%lld ",ans[i]);
	puts("");
	return 0;
}
```


---

## 作者：AutumnKite (赞：5)

[题目传送门](http://codeforces.com/contest/1214/problem/F)

## 题意

有一个大小为 $m$ 的环，还上有 $n$ 个点有工作单位，并且有 $n$ 个点上住着一个人。你需要为每个人分配一个工作单位，使得所有人到工作单位的距离之和最短。输出一个方案。

$m\le 10^9,n\le 2\times 10^5$

## 题解

下面的数组都从 $0$ 开始标号。先将 $a,b$ 数组分别从小到大排序，然后把 $b$ 数组变成 $b_0,b_1,b_2,\cdots,b_{n-1},b_0+m,b_1+m,\cdots,b_{n-1}+m,b_0+2m,b_1+2m,\cdots,b_{n-1}+2m$，把 $a$ 数组变成 $a_0+m,a_1+m,a_2+m,\cdots,a_{n-1}+m$。

考虑贪心，显然两个人的路径不能“交叉”，所以一定是小的和小的匹配，大的和大的匹配。问题变成了求 $\min\limits_{0\le x\le 2n} \sum\limits_{i=0}^{n-1} |a_i-b_{i+x}|$ 的值。

记 $ans_x=\sum\limits_{i=0}^{n-1} |a_i-b_{i+x}|$，把绝对值拆开，则变成了

$$\begin{aligned}ans_x&=\sum\limits_{i=0}^{n-1} |a_i-b_{i+x}| \\ &=\sum\limits_{i=0}^{n-1} ([a_i > b_{i+x}]a_i-[a_i < b_{i+x}]a_i-[a_i > b_{i+x}]b_{i+x}+[a_i < b_{i+x}]b_{i+x})\end{aligned}$$

记 $sa_{x}=\sum\limits_{i=0}^{n-1} ([a_i > b_{i+x}]a_i-[a_i < b_{i+x}]a_i),sb_{x}=\sum\limits_{i=0}^{n-1} ([a_i < b_{i+x}]b_{i+x}-[a_i > b_{i+x}]b_{i+x})$。考虑单独计算。

我们将 $sa$ 差分，发现 $sa_x-sa_{x-1}=\sum\limits_{i=0}^{n-1} ([a_i > b_{i+x}]a_i-[a_i < b_{i+x}]a_i-[a_i > b_{i+x-1}]a_i+[a_i < b_{i+x-1}]a_i)$，发现若 $a_i \le b_{i+x-1} \le b_{i+x}$ 或 $b_{i+x-1} \le b_{i+x} \le a_i$ 时，这个式子恰好为 $0$，只有当 $b_{i+x-1} < a_i < b_{i+x}$ 时，这个式子的值为 $-2a_i$，而这个 $x$ 又是唯一的。于是对于每个 $a_i$ 求出这个唯一的 $x$，在差分数组上直接修改即可。

我们依次考虑每个 $b_i$，发现当 $x$ 小于某个值时，$b_i$ 对 $sb_x$ 的贡献是负的，否则是正的。于是我们求出这个值，然后区间加贡献即可。这个也可以用差分简单的实现。

发现求 $sa_x,sb_x$ 在实现的过程中都需要差分，不需要分开计算。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, ansi, ansid[N];
long long m, ans[N << 1], Ans;
struct node{
	long long v;
	int id;
	bool operator < (const node &rhs) const {
		return v < rhs.v;
	}
}a[N], b[N * 3];
long long abs(long long a){
	return a > 0 ? a : -a;
}
void add(int l, int r, long long v){
	ans[l] += v, ans[r] -= v;
}
int main(){
	m = read(), n = read();
	for (register int i = 0; i < n; ++i) a[i].v = read(), a[i].id = i;
	for (register int i = 0; i < n; ++i) b[i].v = read(), b[i].id = i;
	std :: sort(a, a + n), std :: sort(b, b + n);
	for (register int i = 0; i < n; ++i) a[i].v += m;
	for (register int i = 0; i < (n << 1); ++i) b[i + n] = b[i], b[i + n].v += m;
	for (register int i = 0; i < n; ++i) ans[0] += a[i].v;
	for (register int i = 0; i < n; ++i){
		int j = std :: lower_bound(b, b + 3 * n, a[i]) - b;
		if (j > i && j <= i + (n << 1)) ans[j - i] -= 2 * a[i].v;
	}
	for (register int j = 0; j < 3 * n; ++j){
		if (j < n){ add(0, j + 1, -b[j].v); continue; }
		if (j >= (n << 1)){ add(j - n + 1, (n << 1) + 1, b[j].v); continue; }
		int i = std :: upper_bound(a, a + n, b[j]) - a;
		add(j - i + 1, j + 1, b[j].v), add(j - n + 1, j - i + 1, -b[j].v);
	}
	Ans = ans[0], ansi = 0;
	for (register int i = 1; i <= (n << 1); ++i){
		ans[i] += ans[i - 1];
		if (ans[i] < Ans) Ans = ans[i], ansi = i;
	}
	for (register int i = 0; i < n; ++i)
		ansid[a[i].id] = b[(i + ansi) % n].id;
	printf("%lld\n", Ans);
	for (register int i = 0; i < n; ++i) printf("%d ", ansid[i] + 1);
}
```

---

## 作者：OIbishop (赞：2)

# 前言
由于某道卡常题的需要，代码十分的丑。
# 解法
先考虑如果不是环怎么做，其实就是排序一遍，然后对位算贡献。是环就枚举一个起点就行了。  
根据题意，我们发现其实我们就是要求  
$$\min_{x=1}^n \sum_{i=1}^n \min(|a_i-b_{i+x}|,m-|a_i-b_{i+x}|)$$
发现其中有一个取最小值不好处理，于是将 $b_i$ 复制三遍，第一份不变，第二份都加 $m$ ，第三份都加 $2m$。再将 $a_i$ 都加上 $m$ 即可去除取最小值。所以现在就是求
$$\min_{x=1}^{n\times2+1} \sum_{i=1}^n |a_i-b_{i+x}|$$
绝对值不好处理，于是考虑算每一个 $a_i,b_i$ 的贡献。显然，对于 $a_i \ge b_i$，$a_i$ 贡献为正，反之，$a_i$ 贡献为负。$b_i$ 同理。对 $a_i,b_i$ 排序后，贡献为正的区间连续，贡献为负的同样连续。所以可以双指针求出区间。令 $c_i$ 为上式 $x=i$ 时的答案，可以用差分维护。
## 代码
代码有点丑。最好是在草稿纸上画一画，自己推出来。

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma optimize(2)
#pragma optimize(3,"Ofast","inline")
using namespace std;
#define gc getchar ()
template <class T>
inline void read (T &s)
{
	s = 0; bool q = false; char c = gc;
	while (!isdigit (c)) {if (c == '-') q = true; c = gc;}
	while (isdigit (c)) {s = (s << 1) + (s << 3) + (c ^ 48); c = gc;}
	if (q) s = -s;
}
template <class T , class ...Args>
inline void read (T &s , Args &...x) {read (s) , read (x...);}
#undef gc

constexpr int N = 6e5 + 5;
int t , m , n , pos[N];
struct node {
    int v , id;
    inline friend bool operator < (node x , node y) {
        return x.v < y.v;
    }
} a[N] , b[N * 3];
long long c[N * 2] , ans;
inline void add (int l , int r , int v) {if (l > r) return ; c[l] += v , c[r + 1] -= v;} 
signed main ()
{
//	freopen ("road.in" , "r" , stdin);
//	freopen ("road.out" , "w" , stdout);
    read (m , n);
    int p1 = 0 , p2 = 0;
    ans = 1e18;
    for (int i = 1; i <= n; i++) read (a[i].v) , a[i].v += m , a[i].id = i;
    for (int i = 1; i <= n; i++) read (b[i].v) , b[i].id = i;
    sort (a + 1 , a + n + 1); sort (b + 1 , b + n + 1);
    for (int i = n + 1; i <= n * 3; i++) b[i] = b[i - n] , b[i].v += m ;
    for (int i = 1; i <= n; i++) 
    {
        add (1 , i , - b[i].v);
        add (1 , n - i + 1 , a[i].v);
        add (2 * n + 1 - i + 1 , 2 * n + 1 , -a[i].v);
        i += n * 2;
        add (i - n + 1 , i , b[i].v);
        i -= n * 2;
        while (p2 < n && b[p2 + n + 1].v <= a[i].v ) p2 ++ ;
        add (n + 1 - i + 1 , n * 2 - i + 1 , -a[i].v);
        add (n + 1 - i + 1 , p2 + n - i + 1 , 2 * a[i].v);
        i += n;
        while (p1 < n && a[p1 + 1] < b[i]) p1 ++ ;
        add (i - n + 1 , i , -b[i].v);
        add (i - p1 + 1 , i , b[i].v * 2); 
        i -= n;
    } c[0] = 0;
    for (int i = 1; i <= n * 2 + 1; i++) 
    {
        c[i] += c[i - 1];
        if (ans > c[i]) 
            ans = c[i] , p1 = i;
    }
    cout << ans << "\n";
    for (int i = p1; i <= p1 + n - 1; i++)
        pos[a[i - p1 + 1].id] = b[i].id;
    for (int i = 1; i <= n; i++) cout << pos[i] << " ";
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：2)

## 做法

首先 $O(n^2)$ 的做法是简单的。  
我们对序列 $a$ 和 $b$ 都排一遍序，定义 $f(i)$ 为从序列 $a$ 的第 $1$ 项、序列 $b$ 的第 $i$ 项开始，一一配对得到的答案。  
然后枚举 $f(i)$（$1\le i \le n$）即可，正确性显然。  

接下来考虑乱搞，我们把所有的 $f(i)$ 都列出来，观察几个样例可以发现，这个函数的图像大概长成下面这个样子：  

![](https://cdn.luogu.com.cn/upload/image_hosting/n0tmg4xd.png)

观察图像，显然答案只可能在两个最低处出现，如何找到它呢？  
发现 $f(i)$ 看上去很像一个单峰函数，但是它的两侧又有凸起的部分。  
于是考虑把这个函数在最高点处分成两部分，这样左右两部分就可以上三分求解了。  
然而最高点并不好找，考虑到我们正在考虑乱搞，我们直接以 $\lfloor \frac{n}{2} \rfloor$ 为分界点即可。  
设 $p$ 为我们找到的最低点，为了贯彻乱搞的理念，我们枚举 $[p-10,p+10]$ 并取最小值。  

另外如果 $n\le 5000$，直接上 $O(n^2)$ 暴力解决。  
因为当 $n$ 很大时，最高点一般不会距离 $\lfloor \frac{n}{2} \rfloor$ 很远，但 $n$ 比较小时就不一定了。  

这个做法显然是不太正确的，但是它能过 CF 的数据和校模拟赛的部分分。  
如果有 hack 数据，欢迎联系笔者。  

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define epb emplace_back
#define all(x,l,r) &(x)[l],&(x)[r]+1
#define cto const auto
template <class T> bool chkmn(T &x,T y){return x>y?(x=y,1):0;}
template <class T> bool chkmx(T &x,T y){return x<y?(x=y,1):0;}
bool mbs;void cntime();
const int N=2e5+5,inf=1e18;
#define w(i,j) min(abs(i-j),m-abs(i-j))
struct node{
    int x,id;
    friend bool operator <(const node &x,const node &y){
        return x.x<y.x;
    }
}a[N],b[N];
int n,m,ans,cnt,ansa[N],tub[N*4];
int calc(int j){
    if(j<1||j>n) return inf;
    int res=0;
    per(i,1,n){
        res+=w(a[i].x,b[j].x);
        if((++j)>n) j-=n;
    }
    return res;
}
int binary(int l,int r){
    l=max(l,1ll);r=min(n,r);
    int mid,f1,f2,fc1,fc2;
    while(r-l>=2){
        mid=(r-l+1)/3;
        f1=calc(l+mid);f2=calc(r-mid);
        if(f1>f2) l+=mid;
        else r-=mid;
    }
    return (l+r)>>1;
}
void output(int j){
    per(i,1,n){
        ansa[a[i].id]=b[j].id;
        if((++j)>n) j-=n;
    }
    per(i,1,n) cout<<ansa[i]<<" \n"[i==n];
}
void main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>m>>n;ans=inf;
    per(i,1,n) cin>>a[i].x,a[i].id=i;
    per(i,1,n) cin>>b[i].x,b[i].id=i;
    sort(all(a,1,n));
    sort(all(b,1,n));
    if(n<=5000){
        per(i,1,n) if(chkmn(ans,calc(i))) cnt=i;
    }else{
        int x=binary(1,(n>>1));
        per(i,x-10,x+10) if(chkmn(ans,calc(i))) cnt=i;
        x=binary((n>>1)+1,n);
        per(i,x-10,x+10) if(chkmn(ans,calc(i))) cnt=i;
    }
    cout<<ans<<'\n';
    output(cnt);
    return cntime();
}
bool mbe;void cntime(){
    cerr<<"Time: "<<1e3*clock()/CLOCKS_PER_SEC<<" ms\n";
    cerr<<"Memory: "<<abs(&mbe-&mbs)/1024./1024.<<" MB\n";
}}
signed main(){
    fisher::main();
    return 0;
}
```

---

## 作者：sunzh (赞：1)

## CF1214F 

如果我们按点的位置排序，同时把b拆成三个线段，下标分别是$[1\to n],[n+1\to 2*n],[2*n+1\to 3*n]$值域分别在$[-m \to 0],[1\to m],[m+1\to 2m]$区间内，不难发现，最终结果一定是
$$ans=\min_{x=0}^{2*n}\sum_{i=1}^n|a_i-b_{i+x}|$$

分类讨论一下，

$ans=\min_{x=0}^{2*n}\sum_{i=1}^n([a_i>=b_{i+x}]a_i-[a_i<b_{i+x}]a_i-[a_i>=b_{i+x}]b_{i+x}+[a_i<b_{i+x}]b_{i+x})$

可以发现，$a_i$在$x=[0, p)$区间内取$a_i$,在$x=[p,2*n]$取$-a_i$,$p$为$a_i$匹配b中第一个$>a_i$的位置的x的值

如果我们做一个差分，就可以得到下面这段代码（c是差分数组）

```c++
for(int i=1;i<=n;++i) c[0]+=a[i].val;
for(int i=1;i<=n;++i){
	int j=upper_bound(b+1,b+3*n+1,a[i])-b;
	if(j>i&&j<=i+2*n) c[j-i]-=2*a[i].val;
}
```

然后我们考虑$b$

把三段分开讨论

对于$[-m \to 0]$，我们始终有$b_i<a_j$,因此对于$x=[0,i-1]$,$b_i$的贡献都为$-b_i$

对于$[m+1\to 2*m]$,我们始终有$b_i>a_j$,因此对于$x=[i-n,\min(i-1,n*2-1)]$,$b_i$的贡献为$b_i$

对于中间这段，我们可以通过上面的式子，得出如下结论：

​		对于$a_{i-x}>=b_i$，$b_i$的贡献是$-b_i$

​		否则，$b_i$的贡献为$b_i$

也就是从第一个$a_{i-x}>=b_i$开始，$b_i$的贡献由$b_i$变为$-b_i$

因此贡献取$b_i$的$x$的下界（$i-x$的上界，也就是$x$的下界）是$i-j+1$，而贡献$-b_i$的上界就是$i-j$

```c++
	for(int i=1;i<=3*n;++i){
		if(i<=n){
			add(0,i-1,-b[i].val);continue ;
		}
		if(i>(n<<1)){
			add(i-n,n<<1,b[i].val);continue ;
		}
		int j=lower_bound(a+1,a+n+1,b[i])-a;
		add(i-j+1,i-1,b[i].val);add(i-n,i-j,-b[i].val);
	}
```
核心代码已贴出，如果需要看提交记录请转 CF 

[地址:https://codeforces.ml/contest/1214/submission/93045711 ]( https://codeforces.ml/contest/1214/submission/93045711 )

---

