# Serious Business

## 题目描述

Dima is taking part in a show organized by his friend Peter. In this show Dima is required to cross a $ 3 \times n $ rectangular field. Rows are numbered from $ 1 $ to $ 3 $ and columns are numbered from $ 1 $ to $ n $ .

The cell in the intersection of the $ i $ -th row and the $ j $ -th column of the field contains an integer $ a_{i,j} $ . Initially Dima's score equals zero, and whenever Dima reaches a cell in the row $ i $ and the column $ j $ , his score changes by $ a_{i,j} $ . Note that the score can become negative.

Initially all cells in the first and the third row are marked as available, and all cells in the second row are marked as unavailable. However, Peter offered Dima some help: there are $ q $ special offers in the show, the $ i $ -th special offer allows Dima to mark cells in the second row between $ l_i $ and $ r_i $ as available, though Dima's score reduces by $ k_i $ whenever he accepts a special offer. Dima is allowed to use as many special offers as he wants, and might mark the same cell as available multiple times.

Dima starts his journey in the cell $ (1, 1) $ and would like to reach the cell $ (3, n) $ . He can move either down to the next row or right to the next column (meaning he could increase the current row or column by 1), thus making $ n + 1 $ moves in total, out of which exactly $ n - 1 $ would be horizontal and $ 2 $ would be vertical.

Peter promised Dima to pay him based on his final score, so the sum of all numbers of all visited cells minus the cost of all special offers used. Please help Dima to maximize his final score.

## 说明/提示

In the first example, it is optimal to use Peter's second offer of $ 4 $ rubles and go through the cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ , $ (3, 4) $ , earning $ 1 + 0 + 2 + 9 + 4 + 1 - 4 = 13 $ rubles in total.

In the second example, it is optimal to use Peter's second and third offers of $ 2 $ and $ 3 $ rubles, respectively, and go through the cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , earning $ -20 + 1 + 3 + 3 + 6 + 6 + 2 - 2 - 3= -4 $ rubles.

## 样例 #1

### 输入

```
4 3
1 0 2 -1
-3 1 9 2
3 2 4 1
1 2 5
2 3 4
1 4 14```

### 输出

```
13```

## 样例 #2

### 输入

```
5 4
-20 -10 -11 -10 1
1 3 3 6 3
14 -20 3 6 2
1 5 13
1 2 2
3 5 3
2 3 1```

### 输出

```
-4```

# 题解

## 作者：gyh20 (赞：19)

由于没学过最短路，只有用线段树来做一做。

可以发现，这道题如果想 DP 的话初始的状态非常难设计，于是我们考虑设计一个可 DP 的状态，然后花一定的代价合并找到答案。

我们最开始设 $f_i$ 表示从 $(1,1)$ 走到 $(2,i)$，**并且选择的区间的右端点恰好覆盖到 $i$** 的最大收益，枚举当前使用的区间 $x$，这个转移分为两类。

$1.$ 从 $f_{L_x-1}\sim f_{i-1} $ 中的一个转移过来，表示在该位置的基础上延伸。

$2.$ 直接从 $(1,1)$ 走到 $(1,k)$ 再走到 $(2,k)$ 最后走到 $(2,i)$，此时需要保证 $L_x\leq k\leq i$。

两种情况拆一个前缀和都可以用线段树维护（或许可以用树状数组，因为都是后缀询问）。

发现上述 DP 最大的问题在于，我们选择区间覆盖到的右端点不一定是走到的最右端点，但我们发现，至多只有一个区间的右端点没有被走到，否则显然可以少用一个区间。

枚举没有覆盖满的一个区间，那么答案就是区间中的一个 $f_i$ 和一个向下的拐点组成，令拐点的位置为 $j$，拆一个前缀和就变成了区间 $f_i+g_j(i<j)$ 的最大值。（如果你仔细想想会发现这个 $i<j$ 不需要，这个前缀和刚好凑起来了，但是是错的！！！！！！！需要考虑 $f_i$ 是第二种情况转移过来的情况）。

最后需要特判只选了一个区间，此时区间内不存在 $f_i$，具体的问题也形如 $\max(A_i+B_j)(i<j)$。

线段树有点多，要跑 $2s$。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int n,m,a[4][500002],s[4][500002],v1[500002],v2[500002],L[500002],R[500002],W[500002],f[500002];
vector<int>V[500002];
struct SEG{
	int mn[2000002];
	inline void cg(re int p,re int l,re int r,re int x,re int y){
		if(l==r){
			mn[p]=y;
			return;
		}
		re int mid=l+r>>1;
		if(x<=mid)cg(p<<1,l,mid,x,y);
		else cg(p<<1|1,mid+1,r,x,y);
		mn[p]=max(mn[p<<1],mn[p<<1|1]);
	}
	inline int ask(re int p,re int l,re int r,re int x,re int y){
		if(x<1)x=1;
		if(y>n)y=n;
		if(x>y)return -1e18;
		if(l>=x&&r<=y)return mn[p];
		re int mid=l+r>>1,s=-1e18;
		if(x<=mid)s=max(s,ask(p<<1,l,mid,x,y));
		if(y>mid)s=max(s,ask(p<<1|1,mid+1,r,x,y));
		return s;
	}
}T1,T2;
int mx1[2000002],mx2[2000002],Mx,Mx1,Ans[2000002];
inline void build(re int p,re int l,re int r){
	if(l==r){
		mx1[p]=v1[l],mx2[p]=v2[l],Ans[p]=mx1[p]+mx2[p];
		return;
	}
	re int mid=l+r>>1;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	mx1[p]=max(mx1[p<<1],mx1[p<<1|1]),mx2[p]=max(mx2[p<<1],mx2[p<<1|1]);
	Ans[p]=max(Ans[p<<1],Ans[p<<1|1]);
	Ans[p]=max(Ans[p],mx2[p<<1|1]+mx1[p<<1]);
}
inline void Ask(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y){
		Mx=max(Mx,Ans[p]);
		Mx=max(Mx,mx2[p]+Mx1),Mx1=max(Mx1,mx1[p]);
		return;
	}
	re int mid=l+r>>1;
	if(x<=mid)Ask(p<<1,l,mid,x,y);
	if(y>mid)Ask(p<<1|1,mid+1,r,x,y);
}
signed main(){
	n=read(),m=read();
	for(re int i=1;i<=3;++i)
		for(re int j=1;j<=n;++j)a[i][j]=read(),s[i][j]=s[i][j-1]+a[i][j];
	for(re int i=1;i<=m;++i)L[i]=read(),R[i]=read(),W[i]=read(),V[R[i]].push_back(i);
	for(re int i=1;i<=n;++i)v1[i]=s[1][i]-s[2][i-1],v2[i]=s[3][n]-s[3][i-1]+s[2][i];
	build(1,1,n);
	for(re int i=1;i<=n;++i)T2.cg(1,1,n,i,s[1][i]-s[2][i-1]);
	for(re int i=1;i<=n;++i){
		f[i]=-1e18;
		for(re int j=0;j<V[i].size();++j){
			re int l=L[V[i][j]],r=R[V[i][j]],w=W[V[i][j]];
			re long long ss=-1e18;
			ss=max(ss,T1.ask(1,1,n,l-1,r-1)+s[2][i]-w);
			ss=max(ss,T2.ask(1,1,n,l,r)+s[2][i]-w);
			f[i]=max(f[i],ss);
		}
		T1.cg(1,1,n,i,f[i]-s[2][i]);
	}
	for(re int i=1;i<=n;++i)f[i]-=s[2][i];
	int ans=-1e18;
	for(re int i=1;i<=m;++i){
		Mx=-1e18,Mx1=-1e18;
		Ask(1,1,n,L[i],R[i]);
		ans=max(ans,Mx-W[i]);
	}
	for(re int i=1;i<=n;++i)v1[i]=f[i],v2[i]=s[2][i]-s[3][i-1]+s[3][n];
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		Mx=-1e18,Mx1=-1e18;
		Ask(1,1,n,max(1ll,L[i]-1),R[i]);
		ans=max(ans,Mx-W[i]);
	}
	printf("%lld",ans);
}

```


---

## 作者：lzqy_ (赞：15)

一种可能更好想的DP方式（？

设 $f_x$ 表示走到 $(2,x)$ 的最小价值，那么答案显然为：

$$\max\limits_{1\le i \le n}\{f_i+s_i\}$$

其中 $s$ 为第三行的后缀和。

考虑转移。显然第 $x$ 个格子至少需要被一个区间覆盖，枚举该区间：

$f_x=\max\limits_{l_i \le x \le r_i}\{...\}$

确定了使用的区间 $i$ 后，有两种可能，即只使用区间 $i$，或继续使用其他区间。

- 只使用区间 $i$

	要从 $[l_i,x]$ 中选择位置 $k$ 拐到第一行，即：
    
    $$\max\limits_{l_i \le k\le x}\{p_{1,k}+p_{2,x}-p_{2,k-1}-v_i\}$$
    
    
    
其中，$p_{1/2}$ 为 $1/2$ 行的前缀和，$v_i$ 为第 $i$ 个区间使用的代价。


- 继续使用其他区间

	为了使答案更优，则拐点位置要 $\le l_i$：
    
   $$f_{l_i-1}+p_{2,x}-p_{2,l_i-1}-v_i$$
   
带回原式：

$$f_x=\max\limits_{l_i \le x \le r_i}\{\max(f_{l_i-1}+p_{2,x}-p_{2,l_i-1}-v_i,\max\limits_{l_i \le k\le x}\{p_{1,k}-p_{2,k-1}-v_i+p_{2,x}\})\}$$


$$=\max\limits_{l_i \le x \le r_i}\{\max(f_{l_i-1}-p_{2,l_i-1}-v_i,\max\limits_{l_i \le k\le x}\{p_{1,k}-p_{2,k-1}-v_i\})\}+p_{2,x}$$


前面一坨显然可以维护，把区间按 $l$ 排序后依次加入线段树即可。

对于后面那一坨，考虑当区间 $i$ 第一次加入线段树时，一定有 $l_i=x$，也就是说此时 $k$ 等于 $x$，即 $p_{1,x}-p_{2,x-1}-v_i$。

当每次 $x+1$ 时（显然外层循环枚举 $x$），对于所有 $ l_i\le x$，相当于 $k$ 多了一种取值，即 $p_{1,x+1}-p_{2,x}-v_i$。

那就再开一棵线段树，存储每个 $r=x$ 位置的 $\max\{p_{1,x+1}-p_{2,x}-v_i\}$ **以及取最大值时 $v_i$ 的值**，显然 $x+1$ 更新时 $v_i$ 的值不变，于是就可以比较扭曲地用线段树维护后面那坨东西了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e18;
const int maxn=500010;
const int N=maxn<<2;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
struct Que{
	int l,r,k;
	bool operator <(Que a)const{return l<a.l;}
}a[maxn];
ll data1[N],data2[N],lz[N],K2[N];
ll f[maxn],pm[maxn];
ll p[3][maxn],s[maxn];
int c[4][maxn],n,m;
//K2:当x位置取最大值时,vi的值
//显然pushdown的时候 MIN(K2) 最优 
void Insert1(int i,int l,int r,int x,ll k){
	if(l==r){
		data1[i]=max(data1[i],k);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) Insert1(i<<1,l,mid,x,k);
	else Insert1(i<<1|1,mid+1,r,x,k);
	data1[i]=max(data1[i<<1],data1[i<<1|1]);
}
void pushdown(int i){
	if(lz[i]==-inf) return ;
	data2[i<<1]=max(data2[i<<1],lz[i]-K2[i<<1]);
	data2[i<<1|1]=max(data2[i<<1|1],lz[i]-K2[i<<1|1]);
	lz[i<<1]=max(lz[i<<1],lz[i]),lz[i<<1|1]=max(lz[i<<1|1],lz[i]);
	lz[i]=-inf;return ;
}
void Insert2(int i,int l,int r,int x,ll k,int kk){
	if(l==r){
		if(k>data2[i]) data2[i]=k,K2[i]=kk;
		return ;
	}
	pushdown(i);
	int mid=l+r>>1;
	if(x<=mid) Insert2(i<<1,l,mid,x,k,kk);
	else Insert2(i<<1|1,mid+1,r,x,k,kk);
	K2[i]=min(K2[i<<1],K2[i<<1|1]);
	data2[i]=max(data2[i<<1],data2[i<<1|1]);
}
ll Query1(int i,int l,int r,int suf){
	if(r<suf) return -inf;
	if(l>=suf) return data1[i];
	int mid=l+r>>1;
	return max(Query1(i<<1,l,mid,suf),Query1(i<<1|1,mid+1,r,suf));
}
ll Query2(int i,int l,int r,int suf){
	if(r<suf) return -inf;
	if(l>=suf) return data2[i];
	pushdown(i);
	int mid=l+r>>1;
	return max(Query2(i<<1,l,mid,suf),Query2(i<<1|1,mid+1,r,suf));
}
void build(int i,int l,int r){
	data1[i]=data2[i]=lz[i]=-inf,K2[i]=inf;
	if(l==r||l>r) return ;
	int mid=l+r>>1;
	build(i<<1,l,mid),build(i<<1|1,mid+1,r);
}
void Modify(int i,int l,int r,int suf,ll x){
	if(data2[i]==-inf) return ;
	if(l>=suf){
		lz[i]=max(lz[i],x);
		data2[i]=max(data2[i],x-K2[i]);
		return ;
	}
	pushdown(i);
	int mid=l+r>>1;
	if(mid>=suf) Modify(i<<1,l,mid,suf,x);
	Modify(i<<1|1,mid+1,r,suf,x);
	data2[i]=max(data2[i<<1],data2[i<<1|1]);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=3;i++)
		for(int j=1;j<=n;j++)
			c[i][j]=read();
	for(int j=1;j<=n;j++){
		p[1][j]=p[1][j-1]+c[1][j];
		p[2][j]=p[2][j-1]+c[2][j];
		s[n-j+1]=s[n-j+2]+c[3][n-j+1];
	}
	for(int i=1;i<=m;i++)
		a[i].l=read(),a[i].r=read(),a[i].k=read();
	sort(a+1,a+1+m),build(1,1,n);
	int cnt=1;
	for(int i=1;i<=n;i++){
		Modify(1,1,n,i,p[1][i]-p[2][i-1]);
		while(cnt<=m&&a[cnt].l<=i){
			if(a[cnt].l>1) Insert1(1,1,n,a[cnt].r,f[a[cnt].l-1]-p[2][a[cnt].l-1]-a[cnt].k);
        //注意,如果要用两个区间,那靠前的区间左边界至少要大于1才行(或者给f[0]赋个最大值也行)
			Insert2(1,1,n,a[cnt].r,p[1][i]-p[2][i-1]-a[cnt].k,a[cnt].k),cnt++;
		} 		
		f[i]=max(Query1(1,1,n,i),Query2(1,1,n,i))+p[2][i];
	}
	ll ans=-inf;
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]+s[i]);
	printf("%lld\n",ans);
	return 0;
}
```

写法虽然很扭曲，但整个思考过程是顺畅的。

---

## 作者：GaryH (赞：11)

## CF1648D 题解

在这里分享两种做法，分别是 $O(n\log^2n)$ 的 `cdq` 分治，和 $O(n\log n)$ 的线段树，

由于笔者学艺不精，故如有错误或笔误之处欢迎提出，笔者将不胜感激。

**题意**：

给一条 $3$ 行 $n$ 列的带权（可以为负）网格，最初时第二行的所有格子是黑色，其它格子是白色。

你有一些三元组 $(L_p,R_p,k_p)$，代表可以花费 $k_p$ 的代价把第二行在区间 $[L_p,R_p]$ 内的格子染黑。

你需要找到一条从 $(1,1)$ 到 $(n,m)$ 的纯黑色路径，并最大化经过格子的权值和减去染色的代价。

**做法**：

设 $(i,j)$ 处格子的权为 $v_{i,j}$，我们记 $s_{x,y}=\sum\limits_{i=1}^yv_{x,i},a_l=s_{1,l}-s_{2,l-1},b_r=s_{3,n}-s_{3,r-1}+s_{2,r}$，则：

问题等价于求 $\max\limits_{1\le l\le r\le n}(a_l+b_r-cost(l,r))$，其中 $cost(l,r)$ 是将第二行中区间 $[l,r]$ 染黑的最小代价。

我们考虑如何计算 $cost$ 函数的值，这时可以考虑一个暴力的 `DP`，即：

初始值是：$\forall l\in[1,n],cost(l,l-1)=0$，即初始时第二行所有格子都不是黑色；

转移式为：$cost(l,i)=\min\limits_{\exists p\space:\space i,j\in[L_p,R_p],j\le i}(cost(l,j-1)-k_p)$，即用第 $p$ 个三元组拓宽已染黑的区间。

发现 $cost(l,r)$ 在转移时其 $l$ 不变，且转移仅与 $r$ 有关，那我们记 $f(r)=\max\limits_{l\le r}(a_l-cost(l,r))$，

则此时 $f$ 函数也能用 `DP` 的方式计算，即：$f(r)=\max\limits_{\exists p\space:\space L_p\le l\le r\le R_p}(f(l-1)-k_p)$。

这个式子是容易得到的，将 $f$ 函数的定义式里的 $cost$ 函数表示为其转移式就行。

那么最后的答案就等于 $\max\limits_{r=1}^n(b_r+f(r))$，我们也就得到了一个 $O(n^2)$ 的做法，但其实可以继续优化。

我们可以用 `cdq` 分治为 $f$ 函数的计算加速，具体来说，我们对当前分治区间 $[l,r]$ 及区间中点 $mid$，

我们先递归处理区间 $[l,mid]$ 的 $f$ 值，若三元组 $(L_p,R_p,k_p)$ 满足 $L_p\le mid<R_p$，

则对 $\forall \max(l,L_p)\le i\le mid<j\le\min(R_p,r)$，我们都可以花费 $k_p$ 的代价从 $f(i-1)$ 转移到 $f(j)$。

那么，我们可以将所有满足上面条件的转移 $i-1\rightarrow j$ 拆成三步，即：

先从 $f(i-1)$ 转移到 $f(L_p)$，再从 $f(L_p)$ 转移到 $f(R_p)$，最后从 $f(R_p)$ 转移到 $f(j)$。

容易发现，如果你用做后缀 $\max$ 的方式去维护第一步和第三步，并暴力的维护第二步，

那么复杂度递推式就是：$T(l,r)=T(l,mid)+T(mid+1,r)+O(r-l)+O(num(l,r))$，

其中 $num(l,r)$ 为对 $[l,r]$ 能产生影响的三元组个数，故 $T(l,r)=O(n\log^2n)$， 

原因是三元组最多只会影响到 $O(\log n)$ 个分治区间的转移，

这个可以用线段树区间操作的复杂度来证明，即可以将任意 $[l,r]$ 拆成 $O(\log n)$ 个线段树上的区间，

而对分治区间 $[l,r]$，若 $\exists p,q$ 作为两个三元组的编号，满足 $[l,r]\subseteq[L_p,R_p],[l,r]\subseteq[L_q,R_q]$，

则 $p$ 和 $q$ 中 $k$ 值较大的那个一定是无用的。

以上只是介绍了一种对本题中 `cdq` 分治的复杂度的一种理解方式，而并不是更严谨的证明，

更严谨的证明可能还需要一些讨论，但由于笔者写的不是这种做法，故当时并没有做严谨的证明，

但相信强大的读者们一定能够自行完成这个证明。

事实上，上面的 `DP` 式还有一种优化方式，即减少无用转移以优化转移复杂度。

为了方便说明我们是如何优化转移的，在此我们先说明一些定义。

我们首先定义 “ $f(i)$ 能转移一次后到 $f(j)$ ” 为，$f(j)$ 最终的最优解可以由 $f(i)$ 的转移而取到，

即 $f(i)$ 可以作为 $f(j)$ 在 `DP` 的最优转移的 `DAG` 中的前驱。

为了使叙述更便捷，我们用 $f(i)\rightarrow f(j)$ 来代替 “ $f(i)$ 能转移一次后到 $f(j)$ ” 。

自然的，对于 $\forall m>1$，我们可以定义 “ $f(i)$ 能转移 $m$ 次后到 $f(j)$ ” 为，存在序列 $p[1\cdots m]$，满足：

$f(i)\rightarrow f(s_1),\forall q\in [1,m-1], f(p_q)\rightarrow f(p_{q+1}),f(p_m)\rightarrow f(j)$ 这些条件全部成立。

那么，考虑这样的序列可能会有很多种，相应的，我们也就做了很多次无用转移，

因为我们只需要所有合法序列中的一个就可以从 $i$ 转移到 $j$。

那么，我们可以考虑适当并合理地减少转移量，使对 $\forall i,j,m(i<j)$，合法的序列 $ p[1\cdots m]$ 唯一。

这等价于给出一些限制并按照限制来调整 $p$ 序列，最后再给出一种新的转移方式，

使得这个转移方式的实际效果与调整后的 $p$ 序列是一致的，且这个新转移的复杂度更低或可以优化。

那我们先考虑如何合理的调整 $p$ 序列。

一个想法是，我们在保证序列合法的前提下，将 $p$ 中每一个位置调整地尽量靠左，

以达到类似去重的目的。注意到为什么这里的 ” 尽量靠左 “ 的限制没有给出一个调整的先后顺序，

是因为：如果将位置 $p_t$ 调整成 $p'_t$ 后 $p$ 序列仍合法，

则 $p_t$ 所能转移到的位置集，必须与 $p'_t$ 所能转移到的位置集一致，否则一定能构造出不合法的例子，

故此时确定调整顺序是不必要的，且按任意一种调整顺序去调整到尽量靠左，最后结果都是一致的。

一种更直观的的证明，是考虑原序列 $p$ 一定有一个对应的有序三元组集合，

这个集合的每个元素，分别为 $i,p_1,p_2,\cdots,p_m,j$ 这些位置中的每对相邻位置，提供了转移的条件，

故这个集合的大小是 $m+1$，而 $p_t$ 可以调整到的合法位置就是 $[L_t,R_t]\cap[L_{t+1}-1,R_{t+1}]$，

再进一步发现，此时一定有 $[L_t,R_t]\cap[L_{t+1}-1,R_{t+1}]=[L_{t+1}-1,R_t]$，原因是：

这些区间显然不会有包含或不交的情况，而因为 `DP` 转移时下标单增，

故这个有序三元组集一定满足：$\forall t\in[1,m],L_t<L_{t+1},R_t<R_{t+1}$，即可证明上面结论。

而由于我们想让每个元素尽量靠左，故此时对 $\forall t\in[1,m]$，$p_t$ 就会被调整到 $L_{t+1}-1$ 位置。

那么我们考虑应该如何转移，才能使转移的实际效果，与按照上面方式来调整后得到的序列 $p$ 一致。

发现新的转移方式等价于，每次转移到的新点，都是某个三元组对应区间 $[L_q,R_q]$ 的左端点减一，

而这个三元组 $(L_q,R_q,k_q)$ 也一定会被下一次转移所依赖，即下一次转移靠的就是这个三元组。

也就是说，我们除了在第一次转移时会从任意位置出发，

以后的每次转移的起点都是某个三元组对应区间 $[L_p,R_p]$ 的左端点，终点是这个区间内的所有点。

这时我们需要支持区间与某数取 $\max$ 和单点查询的数据结构，而线段树已经足以支持这一点了，

但实际上我们没必要写区间取 $\max$ 数据结构 ，而是考虑将第二行整体翻转后，转移的形式。

发现此时转移等价于：除了最后一次转移的终点可以是任意点，

其余每次转移的起点是某个三元组对应区间 $[L_q,R_q]$ 内所有点，终点是 $R_q+1$，

原因也是好理解的，即我们将第二行翻转后，三元组对应区间的左端点减一，就变成了右端点加一。

那么，除最后一步以外的转移，我们只需要区间查询 $\max$ 值，单点修改的数据结构就能快速维护。

而最后一步，我们可以把统计的答案稍作修改，即：$\max\limits_{\exists p\space:\space1\le L_p\le l\le r\le R_p\le n}(f(l)+b_r-k_p)$，

如果我们统计的是这个答案，那么我们对最后一步的转移，就也可以与其它转移一样了，

因为此时，最后一步只转移到了倒数第二个用来染色的三元组对应区间 $[L_m,R_m]$ 的右端点加一，

而此时 $R_p+1$ 一定在最后一个用来染色的三元组对应区间 $[L_{m+1},R_{m+1}]$ 内，

故上面的答案统计一定是正确的，而快速维护答案的方法，我们也只需要一棵线段树即可，

具体来说，我们算好 $f$ 函数后，枚举三元组 $p$，则你需要查询 $\max\limits_{L_p\le l\le r\le R_p}(f(l)+b_r)$，

而这个式子放在线段树上是具有结合律的信息，我们可以用类似于维护区间最大子段和的方法做到。

这样的时间复杂度就是 $O(n\log n)$ 的，下面放个代码，代码里的实现可能与题解中所讲略有不同。

```
#include <bits/stdc++.h>

#define fi first
#define se second
#define vi vector
#define db double
#define mp make_pair
#define pb push_back
#define LL long long
#define emp emplace_back
#define pii pair < int , int >
#define SZ(x) ((int)(x.size()))
#define all(x) x.begin(), x.end()
#define ckmax(a, b) ((a) = max((a), (b)))
#define ckmin(a, b) ((a) = min((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define edg(i, v, u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define rt 1, 1, n
#define mid ((l + r) >> 1)
#define lsn p << 1, l, mid
#define rsn p << 1 | 1, mid + 1, r
using namespace std;
int read (char ch = 0, int x = 0, int f = 1) { 
	// 快读就不放了
}
void write (int x) { 
	// 快输也不放了
}

const int N (5e5 + 5);
const LL INF (4e18 + 5);

int n, q;
LL x[4][N];
LL s[4][N];
LL s2[2][N];
LL a[N];
LL b[N];

struct Node {
	int l, r; LL k;
} seg[N];
struct Data {
	LL lmx, rmx, val;
};
bool cmp (Node u, Node v) {
	return u.r < v.r;
}
Data mrg (Data u, Data v) { //查询最后答案时，合并区间信息
	Data r;
	r.lmx = max (u.lmx, v.lmx);
	r.rmx = max (u.rmx, v.rmx);
	r.val = max ({u.val, v.val, u.lmx + v.rmx});
	return r;
}
struct SGTlft { // 用来维护转移的线段树
	LL t[N << 2];
	void push_up (int p) {
		t[p] = max (t[p << 1], t[p << 1 | 1]);
	}
	void build (int p, int l, int r) {
		t[p] = -INF;
		if (l == r) t[p] = s[1][l] - s2[0][l - 1];
		else build (lsn), build (rsn), push_up (p);
	}
	LL qmax (int p, int l, int r, int ql, int qr, LL ret = -INF) {
		if (ql <= l && qr >= r) return t[p];
		if (ql <= mid) ckmax (ret, qmax (lsn, ql, qr));
		if (qr > mid)  ckmax (ret, qmax (rsn, ql, qr));
		return ret;
	}
	void upd (int p, int l, int r, int pos, LL val) {
		if (l == r) return ckmax (t[p], val), void();
		if (pos <= mid) upd (lsn, pos, val);
		else upd (rsn, pos, val);
		push_up (p); 
	}
} t1;

struct SGTmax { //最后用来查询答案的线段树
	Data t[N << 2];
	void push_up (int p) {
		t[p] = mrg (t[p << 1], t[p << 1 | 1]);
	}
	void build (int p, int l, int r) {
		t[p] = {-INF, -INF, -INF};
		if (l == r) t[p] = {a[l], b[l], a[l] + b[l]};
		else build (lsn), build (rsn), push_up (p);
	}
	Data qry (int p, int l, int r, int ql, int qr, LL ret = -INF) {
		if (ql <= l && qr >= r) return t[p];
		Data lft = {-INF, -INF, -INF}, rht = {-INF, -INF, -INF};
		if (ql <= mid) lft = qry (lsn, ql, qr);
		if (qr > mid) rht = qry (rsn, ql, qr);
		return mrg (lft, rht);
	}
} t2;

int main() {
	LL res = -INF;
	n = read(), q = read();
	rep (i, 1, 3) rep (j, 1, n) x[i][j] = read();
	rep (i, 1, n) s[1][i] = s[1][i - 1] + x[1][i], 
				  s2[0][i] = s2[0][i - 1] + x[2][i];
	per (i, n, 1) s[3][i] = s[3][i + 1] + x[3][i],
				  s2[1][i] = s2[1][i + 1] + x[2][i];
	rep (i, 1, q) 
	  seg[i].l = read(), seg[i].r = read(), seg[i].k = read();
	sort (seg + 1, seg + q + 1, cmp), t1.build (rt);
	rep (i, 1, q) {
		int l = seg[i].l, r = seg[i].r; LL k = seg[i].k;
		LL val = t1.qmax (rt, l, r) - k; t1.upd (rt, r + 1, val);
	}
	rep (i, 1, n) a[i] = t1.qmax (rt, i, i), b[i] = s[3][i] - s2[1][i + 1];
	t2.build (rt);
	rep (i, 1, q) {
		int l = seg[i].l, r = seg[i].r; LL k = seg[i].k;
		ckmax (res, t2.qry (rt, l, r).val - k);
	}
	printf ("%lld\n", res + s2[0][n]);
	return 0;
}
```



---

## 作者：cwfxlh (赞：10)

## [CF1648D](https://www.luogu.com.cn/problem/CF1648D)  
感觉 DP 的题解都写得有点模糊，研究了一周多才搞明白，所以来写一篇题解作为更清晰的一份参考，尽量讲清楚吧。      
考虑 DP。令 $dp_i$ 表示从 $(1,1)$ 走到 $(2,i)$ 的最大收益，则答案就是 $\max(dp_i+pre3_n-pre3_{i-1})$，所以我们考虑求 $dp_i$。对于每一个区间，令其覆盖的范围为 $[l,r]$，代价为 $cst$，则有 
$$dp_x=\max(dp_{l-1}+pre2_x-pre2_{l-1}-cst,\max_{l\le j\le x}(pre1_j+pre2_x-pre2_{j-1}-cst))$$
$$dp_x=\max(dp_{l-1}-pre2_{l-1}-cst,\max_{l\le j\le x}(pre1_j-pre2_{j-1}-cst))+pre2_x$$

于是就变成了两个式子，前面一部分很明显可以线段树随便转移，难点在于后半部分（这部分的转移我在所有的题解里都没有看懂）。   

先把前半部分抛开，因为可以处理完后半部分再转移前半部分。    

后半部分的式子只与 $j$ 和选择的区间有关，所以说满足的条件就是 $l_i\le j\le x\le r_i$，这里出现了两个关于区间的限制，所以我们考虑消掉右端点的限制，方式就是从后往前扫 $x$，不断加入区间，这样可以保证 $x\le r_i$。    

这里需要用到一种线段树技巧，就是统计区间最大 $A(x)+B(y)$，$x\le y$。对于每个线段树区间，维护 $A$ 的最大值，$B$ 的最大值，$A(x)+B(y)$ 的最大值，于是 pushup 的时候，$A$ 与 $B$ 的最大值直接上传，$A(x)+B(y)$ 的最大值可以先把左右两边继承了，然后继承左边的 $Amax$ 与右边的 $Bmax$ 的和。   

于是现在的限制就变成了 $1\le l_i\le j\le x$，令区间是 $[1,x]$，于是查询的就是 $[1,x]$ 内的 $A(x)+B(y)$ 最大值且要求 $x\le y$（这里 $x$ 的含义变化了），其中 $A(x)$ 意味着 $x$ 作为某个区间的左端点时最大的 $(-cst)$，$B(y)$ 表示 $pre1_j-pre2_{j-1}$，后者可以提前插入，前者在 $x$ 从后往前扫的时候插入即可。   

复杂度 $\Theta(n\log n)$。

代码（写得很烂）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[4][500003],pre1[500003],pre2[500003],pre3[500003],ans,f[500003];
int k1,k2,k3,k4,k5,k6,k7,k8,k9;
struct pr{
	int kk1;
	int kk2;
	int kk3;
}bl4;
class SP_SegTree{
	public:
		int st[2000003],ed[2000003],v[2000003],v2[2000003],v3[2000003];
		void build(int now,int l,int r){
			st[now]=l;
			ed[now]=r;
			v2[now]=v3[now]=-214748364800000000;
			if(l==r){
				v[now]=pre1[l]-pre2[l-1];
				return;
			}
			build(now*2,l,((l+r)>>1));
			build(now*2+1,((l+r)>>1)+1,r);
			v[now]=max(v[now*2],v[now*2+1]);
			return;
		}
		void modify(int now,int wz,int val){
			if(st[now]>wz||ed[now]<wz)return;
			if(st[now]==ed[now]){
				v2[now]=max(val,v2[now]);
				v3[now]=max(v3[now],v[now]+v2[now]);
				return;
			}
			modify(now*2,wz,val);
			modify(now*2+1,wz,val);
			v2[now]=max(v2[now*2],v2[now*2+1]);
			v3[now]=max(v3[now*2],v3[now*2+1]);
			v3[now]=max(v3[now],v2[now*2]+v[now*2+1]);
			return;
		}
		pr Query(int now,int l,int r){
			if(st[now]>r||ed[now]<l)return {-214748364800000000,-214748364800000000,-214748364800000000};
			if(st[now]>=l&&ed[now]<=r)return {v[now],v2[now],v3[now]};
			register pr bl1=Query(now*2,l,r),bl2=Query(now*2+1,l,r);
			bl1.kk3=max(bl1.kk3,bl2.kk3);
			bl1.kk3=max(bl1.kk3,bl2.kk1+bl1.kk2);
			bl1.kk1=max(bl1.kk1,bl2.kk1);
			bl1.kk2=max(bl1.kk2,bl2.kk2);
			return bl1;
		}
}T2;
class SegTree{
	public:
		int st[2000003],ed[2000003],v[2000003],lzmk[2000003];
		void build(int now,int l,int r){
			st[now]=l;
			ed[now]=r;
			lzmk[now]=v[now]=-214748364800000000;
			if(l==r)return;
			build(now*2,l,((l+r)>>1));
			build(now*2+1,((l+r)>>1)+1,r);
			return;
		}
		void pushdown(int now){
			v[now*2]=max(v[now*2],lzmk[now]);
			lzmk[now*2]=max(lzmk[now*2],lzmk[now]);
			v[now*2+1]=max(v[now*2+1],lzmk[now]);
			lzmk[now*2+1]=max(lzmk[now*2+1],lzmk[now]);
			return;
		}
		void modify(int now,int l,int r,int val){
			if(st[now]>r||ed[now]<l)return;
			if(st[now]>=l&&ed[now]<=r){
				v[now]=max(val,v[now]);
				lzmk[now]=max(val,lzmk[now]);
				return;
			}
			pushdown(now);
			modify(now*2,l,r,val);
			modify(now*2+1,l,r,val);
			v[now]=max(v[now*2],v[now*2+1]);
			return;
		}
		int Query(int now,int l,int r){
			if(st[now]>r||ed[now]<l)return -214748364800000000;
			if(st[now]>=l&&ed[now]<=r)return v[now];
			pushdown(now);
			return max(Query(now*2,l,r),Query(now*2+1,l,r));
		}
}T;
struct Seq{
	int st;
	int ed;
	int cst;
}P[500003];
bool comp(Seq X,Seq Y){
	return X.st<Y.st;
}
vector<int>lst[500003];
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=3;i++){
		for(int j=1;j<=n;j++)scanf("%lld",&a[i][j]);
	}
	ans=-214748364800000000;
	for(int i=1;i<=n;i++){
		pre1[i]=pre1[i-1]+a[1][i];
		pre2[i]=pre2[i-1]+a[2][i];
		pre3[i]=pre3[i-1]+a[3][i];
	}
	T.build(1,1,n);
	T2.build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%lld%lld%lld",&P[i].st,&P[i].ed,&P[i].cst);
		lst[P[i].ed].emplace_back(i);
	}
	for(int i=n;i;i--){
		for(auto j:lst[i])T2.modify(1,P[j].st,-P[j].cst);
		bl4=T2.Query(1,1,i);
		f[i]=bl4.kk3;
	}
	for(int i=1;i<=n;i++)T.modify(1,i,i,f[i]);
	sort(P+1,P+q+1,comp);
	for(int i=1;i<=q;i++){
		if(P[i].st>1){
			k1=T.Query(1,P[i].st-1,P[i].st-1)-P[i].cst;
			T.modify(1,P[i].st,P[i].ed,k1);
		}
	}
	for(int i=1;i<=n;i++){
		k6=T.Query(1,i,i)+pre2[i]+pre3[n]-pre3[i-1];
		ans=max(ans,k6);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：周子衡 (赞：8)

原题可以简化为这样一个模型：每个点有两个权值 $c_i,b_i$，你需要选出两个点 $l\leq r$，最小化把区间 $[l,r]$ 的格子全部覆盖的代价与 $a_l,b_r$ 的和。推推式子可以知道 $c_i=-\sum_{j=1}^ia_{j,1}+\sum_{j=1}^{i-1}a_{j,2}$，$b_i=-\sum_{j=1}^ia_{j,2}+\sum_{j=1}^{i-1}a_{j,3}-\sum_{j=1}^na_{j,3}$。覆盖区间的代价又可以向图论方向转化。最终，我们可以转化成这样一个最短路模型：有两排点 $A_{1\sim n},B_{1\sim n}$，源点向 $A_i$ 连权值为 $c_i$ 的边，$B_i$ 向汇点连权值为 $b_i$ 的边；对每个输入中给定的区间 $[l,r]$ 以及价值 $k$，对每个 $l\leq i\leq j\leq r$，从 $A_i$ 向 $B_j$ 连边，也从 $B_{i-1}$ 向 $B_j$ 连边，边权为 $k$。从源点到汇点的最短路就是答案。

直接线段树优化建图然后跑最短路算法的时间复杂度是 $O(n\log^2 n)$，应该不能通过此题。考虑更快的做法。发现由于所有的边都是从左往右连的，我们可以从左往右来递推出到每个 $B_i$ 的最短路，进而最后求出到汇点的最短路。但是直接递推又非常困难，我们这里采取一种离线的思想——CDQ 分治。

假定我们要计算 $[1,n]$ 的最短路。我们取 $[1,n]$ 的中点 $mid$，然后将所有输入中给出的区间分为三类：完全在左边的区间、跨过中点的区间、完全在右边的区间，记这些区间构成的集合分别为 $L,M,R$。我们假装已经能求出在只有 $L$ 存在的情况下，到 $B_{1\sim mid}$ 的最短路了。这时我们来考虑 $M$。可以发现，$M$ 会带来这些以下三类影响：

- 对 $i\leq j\leq mid$，$i$ 可以借助 $M$ 的某个区间走到 $B_j$；
- 对 $i\leq  mid < j$，$i$ 可以借助 $M$ 的某个区间走到 $B_j$；
- 对 $mid< i\leq j$，$i$ 可以借助 $M$ 的某个区间走到 $B_j$。

同时可以知道，上面每类影响都至多经过 $1$ 个区间（比如说，对 $i\leq j\leq mid$，我们不可能选两个跨过 $mid$ 的区间来从 $B_i$ 走到 $B_j$，因为这样一定是浪费的）。因而我们可以通过求解一些前缀最大值、后缀最大值之类的东西来处理 $M$ 带来的影响。这时右边每个 $B_i$ 有了一个初始的最短路，我们再递归下去处理右区间和 $R$ 就可以了。前面“假装求出在只有 $L$ 存在的情况下，到 $B_{1\sim mid}$ 的最短路”也是递归实现的。

这样的总时间复杂度 $O(n\log n)$，写得好的话应该能过。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const long long INF=1e15;

struct nd
{
	int l,r;long long val,dat;
	nd(int _l=0,int _r=0,long long _val=0):l(_l),r(_r),val(_val),dat(0){}
};
bool lcmp(nd A,nd B){return A.l<B.l;}
bool rcmp(nd A,nd B){return A.r<B.r;}

int n,q;
long long a[600000][3],val[600000][3],f[600000];

void Solve(int l,int r,vector<nd> X)
{
	if(l==r||X.size()==0)return;
	
	int mid=(l+r)>>1;vector<nd> L,R,M;
	for(int i=0;i<X.size();i++){if(X[i].r<=mid)L.push_back(X[i]);else if(X[i].l>mid)R.push_back(X[i]);else M.push_back(X[i]);}
	
	Solve(l,mid,L);
	
	//printf("Solve: %d %d\n",l,r);
	//for(int i=0;i<=n;i++)printf("%lld ",val[i][1]);puts("");
	sort(M.begin(),M.end(),lcmp);
	long long a=INF,b=INF;
	for(int i=l,j=-1;i<=mid;i++)
	{
		while(j+1<M.size()&&M[j+1].l<=i)
		{
			j++;a=min(M[j].val,a);
		}
		val[i][1]=min(val[i][1],b);//printf("%lld %lld\n",a,b);
		b=min(b,a+min(val[i][0],val[i][1]));
	}
	//for(int i=0;i<=n;i++)printf("%lld ",val[i][1]);puts("");
	a=INF;
	for(int i=M.size()-1,p=mid;i>=0;i--)
	{
		while(p>=M[i].l)
		{
			a=min(a,min(val[p][0],val[p][1]));p--;
		}
		M[i].dat=a;
	}
	//for(int i=0;i<M.size();i++)printf("%d %d %lld %lld\n",M[i].l,M[i].r,M[i].val,M[i].dat);
	sort(M.begin(),M.end(),rcmp);
	
	a=INF;
	for(int i=mid+1;i<=r;i++)f[i]=INF;
	for(int i=r,j=M.size();i>mid;i--)
	{
		while(j-1>=0&&M[j-1].r>=i)
		{
			j--;a=min(a,M[j].dat+M[j].val);f[i]=min(f[i],M[j].val);
		}
		val[i][1]=min(val[i][1],a);
		if(i<r)f[i]=min(f[i],f[i+1]);
	}
	
	a=INF;
	for(int i=mid+1;i<=r;i++)
	{
		val[i][1]=min(val[i][1],a+f[i]);
		a=min(a,min(val[i][0],val[i][1]));
	}
	
	//for(int i=0;i<=n;i++)printf("%lld ",val[i][1]);puts("");
	
	Solve(mid+1,r,R);
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int j=0;j<3;j++)for(int i=1;i<=n;i++)scanf("%lld",&a[i][j]),a[i][j]+=a[i-1][j];
	
	for(int i=0;i<=n;i++)for(int j=0;j<3;j++)val[i][j]=INF;
	for(int i=1;i<=n;i++)
	{
		val[i][2]=-(a[i][1]+a[n][2]-a[i-1][2]);
		val[i-1][0]=-(a[i][0]-a[i-1][1]);
	}
	
	//for(int j=0;j<3;j++){for(int i=0;i<=n;i++)printf("%lld ",val[i][j]);puts("");}
	vector<nd> X;
	for(int i=1,l=0,r=0,v=0;i<=q;i++)
	{
		scanf("%d%d%d",&l,&r,&v);X.push_back(nd(l-1,r,v));
	}
	
	Solve(0,n,X);
	long long ans=INF;
	//for(int i=0;i<=n;i++)printf("%lld ",val[i][1]);puts("");
	for(int i=0;i<=n;i++)ans=min(ans,val[i][1]+val[i][2]);
	printf("%lld",-ans);
}
```

---

## 作者：Felix72 (赞：4)

分享一个无式子、不拆意义的线段树做法。

我们先不考虑第一行和第三行的问题，想想第二行的转移方法：如果买下一个区间，我们一定会从这个区间左边的位置出发走若干距离再走出去（可能是走到第三行，也可能是走出区间右边），这启示我们使用线段树优化建图。对于每条点连区间的边，边权为区间的代价。

然而问题随之而来：第二行的点权如何快速加和？这个也可以在线段树内解决。我们发现，如果我们从线段树的一个节点走到了右儿子，就一定会经过左儿子所包含的位置，这个可以在线段树内部赋边权实现，对于叶子节点，特判即可。

刚才的建图能解决第二行的问题，但无法处理第一次进入第二行产生的贡献，因此接下来考虑从第一行走到第二行的情况：因为只需考虑一个区间，所以把拐点的信息塞进另一棵线段树，再加上区间操作即可。这样就能实现初始值的问题。

最后，对于枚举每个位置，计算它走到第三行后的后缀和，取最大值得到答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
queue < int > q;
int n, m, rd[N * 3]; long long a[4][N], p[4][N], dp[N * 3], ans = -2e15;
struct node {int l, r; long long val;} s[N];
inline bool cmp(node x, node y) {return x.r < y.r;}

int h[N * 8], cnt;
struct edge {int to, next; long long val;} e[N * 48];
inline void add(int x, int y, long long z)
{e[++cnt].to = y, e[cnt].next = h[x], e[cnt].val = z, h[x] = cnt;}

struct SGT1
{
	int rt, idx;
	struct SGT1node
	{
		int ls, rs; long long sum;
		#define ls1(x) tree1[x].ls
		#define rs1(x) tree1[x].rs
		#define sum1(x) tree1[x].sum
	}tree1[N * 5];
	inline void pushup(int now) {sum1(now) = sum1(ls1(now)) + sum1(rs1(now));}
	inline void build(int &now, int l, int r)
	{
		if(!now)
		{
			if(l == r) now = l;
			else now = ++idx;
		}
		if(l == r) {sum1(now) = a[2][l]; return ;}
		int mid = (l + r) >> 1;
		build(ls1(now), l, mid), build(rs1(now), mid + 1, r);
		add(now, ls1(now), 0 + (l == mid) * sum1(ls1(now)));
		add(now, rs1(now), sum1(ls1(now)) + (mid + 1 == r) * sum1(rs1(now)));
		pushup(now);
	}
	inline void insert(int now, int l, int r, int L, int R, int from, long long num)
	{
		if(L <= l && r <= R)
		{
			add(from, now, num + (l == r) * sum1(now) + (p[2][l - 1] - p[2][L - 1]));
			return ;
		}
		int mid = (l + r) >> 1;
		if(L <= mid) insert(ls1(now), l, mid, L, R, from, num);
		if(mid < R) insert(rs1(now), mid + 1, r, L, R, from, num);
	}
}T1;
struct SGT2
{
	int rt, idx;
	struct SGT2node
	{
		int ls, rs; long long tag, org, sum;
		#define ls2(x) tree2[x].ls
		#define rs2(x) tree2[x].rs
		#define tag2(x) tree2[x].tag
		#define org2(x) tree2[x].org
		#define sum2(x) tree2[x].sum
	}tree2[N * 2];
	inline void pushup(int now)
	{
		org2(now) = max(org2(ls2(now)), org2(rs2(now)));
		sum2(now) = max({sum2(ls2(now)), sum2(rs2(now)), org2(now) + tag2(now)});
	}
	inline void build(int &now, int l, int r)
	{
		if(!now) now = ++idx, tag2(now) = sum2(now) = -1e15;
		if(l == r) {org2(now) = p[1][l] - p[2][l - 1]; return ;}
		int mid = (l + r) >> 1;
		build(ls2(now), l, mid), build(rs2(now), mid + 1, r);
		pushup(now);
	}
	inline void insert(int now, int l, int r, int L, int R, long long num)
	{
		if(L <= l && r <= R)
		{
			tag2(now) = max(tag2(now), num);
			sum2(now) = max(sum2(now), org2(now) + tag2(now));
			return ;
		}
		int mid = (l + r) >> 1;
		if(L <= mid) insert(ls2(now), l, mid, L, R, num);
		if(mid < R) insert(rs2(now), mid + 1, r, L, R, num);
		pushup(now);
	}
	inline long long ask(int now, int l, int r, int L, int R, long long num)
	{
		num = max(num, tag2(now));
		if(L <= l && r <= R) return max(sum2(now), num + org2(now));
		int mid = (l + r) >> 1; long long ans = -2e15;
		if(L <= mid) ans = max(ans, ask(ls2(now), l, mid, L, R, num));
		if(mid < R) ans = max(ans, ask(rs2(now), mid + 1, r, L, R, num));
		return ans;
	}
}T2;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	memset(dp, -0x3f, sizeof(dp));
	T1.idx = n;
	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> a[i][j], p[i][j] = p[i][j - 1] + a[i][j];
	for(int i = 1; i <= m; ++i) cin >> s[i].l >> s[i].r >> s[i].val;
	T1.build(T1.rt, 1, n);
	T2.build(T2.rt, 1, n);
	sort(s + 1, s + m + 1, cmp);
	for(int i = 1; i <= m; ++i)
	{
		int pos = s[i].l - 1;
		if(pos) T1.insert(T1.rt, 1, n, s[i].l, s[i].r, pos, -s[i].val);
	}
	int at = m;
	for(int i = n; i >= 1; --i)
	{
		while(s[at].r == i)
		{
			T2.insert(T2.rt, 1, n, s[at].l, s[at].r, -s[at].val);
			--at;
		}
		dp[i] = p[2][i] + T2.ask(T2.rt, 1, n, 1, i, -2e15);
	}
	for(int i = 1; i <= T1.idx; ++i)
	{
		for(int j = h[i]; j; j = e[j].next)
		{
			int to = e[j].to;
			++rd[to];
		}
	}
	for(int i = 1; i <= T1.idx; ++i) if(rd[i] == 0) q.push(i);
	while(!q.empty())
	{
		int now = q.front(); q.pop();
		for(int i = h[now]; i; i = e[i].next)
		{
			int to = e[i].to;
			--rd[to];
			if(rd[to] == 0) q.push(to);
			dp[to] = max(dp[to], dp[now] + e[i].val);
		}
	}
	for(int i = 1; i <= n; ++i)
		ans = max(ans, dp[i] + p[3][n] - p[3][i - 1]);
	cout << ans << '\n';
	return 0;
}
/*
8 4
-6 -7 -1 -5 -7 -11 2 -2 
0 -4 4 4 -5 4 -5 -13 
0 -2 -12 -9 -8 -4 3 -11 
4 7 1
8 8 9
2 5 10
1 1 4

-29
*/
```

---

## 作者：Aftglw (赞：4)

### 前言
关于此题，CF 的官方题解是利用线段树优化 DP，但在赛后，hehezhou 提出过一种利用 cdq 分治优化 DP 的解法，然后蒟蒻便在神仙 [$\text{\color{balck}{B}\color{red}{indir0}}$](https://www.luogu.com.cn/user/116368) 的帮助下成功用 cdq 分治通过了本题

### 题解
设 $dp_i$ 表示从 $(1, 1)$ 到 $(2, i)$ 的最大权值，有转移：

$$
dp_i = \max\limits_{j < i}\{dp_j + s_{2, i} - s_{2,j} - \text{cost}(i, j)\}
$$

$s_{i, j} = \sum_{k\le j} a_{i,k}$，$\text{cost}(i, j)$ 表示同时包含 $(2,i), (2, j)$ 的花费最小的一个 `offer`

初始值：

$$
dp_i = s_{1,i} + a_{2, i} - \text{cost}(i, i)
$$

那个 $\max\limits_{j \le i}$ 很烦，要 $O(n^2)$ 做，直接 cdq 分治变为 $O(n\log n)$

在来看如何快速地求 $\text{cost}(i, j)$ 

在 cdq 分治时，设当前分治范围为 $[L, R]$，中点为 $mid$，我们可以考虑将跨过 $mid$ 的 `offer` 存下来用来转移

设 `offer` 的覆盖范围为 $[l, r]$，花费为 $w$，我们便可以把 $\text{cost}(i, j)$ 视作 $w$， 试着将 $i \in [l,mid]$ 的 $dp_i$ 转移给 $j \in (mid, r]$ 的 $dp_j$，但这个暴力转移时间复杂度显然是不对的

转化 DP 式子：

$$
\begin{aligned}
dp_i &= \max\limits_{j < i}\{dp_j + s_{2, i} - s_{2,j} - w\}\\
&= \max\limits_{j < i}\{dp_j - s_{2, j}\} + s_{2, i} - w
\end{aligned}
$$

所以将跨中点的 `offer` 按右端点降序排序，维护 $[L, mid]$ 的后缀最大值，双指针转移即可

暴力找跨中点的 `offer` 时，如果当前 `offer` 涉及了左区间，就传给左儿子 $[L, mid]$，右儿子同理，这样就能保证扫到的 `offer` 不会在范围外，优化一点时间

但是这样会被卡，考虑 `offer` 的范围都是 $[1, n]$， 那么每个 `offer` 就会被扫到 $4n$ 次，直接 T 飞

其实在分治时，可以多维护一个 $mn$，表示**包含**当前区间所有 `offer` 的最小花费

显然这个 $mn$ 可以更新跨当前 $mid$ 的任何转移，并且可以遍历 `offer` 时，用包含儿子的 `offer` 的花费来更新 $mn$ 以递归，同时这些包含儿子的 `offer` 也不用传递给儿子了

这样可以保证每个 `offer` 只会被扫到 $O(2 \log n)$ 次，可以接受

至此，总时间复杂度 $O(n\log^2n)$

### 细节

I. 如果给一个 $dp_i$ 赋初值所用的 `offer` 的花费，再一次被用来将 $dp_i$ 转移给其他的 $dp_j$，那么就会算重

比如下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6f2gjpj7.png)

黑色的是 cdq 分治区间，红色的是一个花费为 $w$ 的 `offer` ，$1, 2$ 是两个分治区间的叶子，那么我给 $dp_1$ 赋初的初值是 $a_{1,1} + a_{2, 1} - w$ 

此时我要利用 $dp_1$ 来转移 $dp_2$，由于这个 `offer` 是同时包含了 $1, 2$ 的，所以我可以让 $dp_2 = max\{dp_2, dp_1 + a_{2, 2} - w\}$，而此时 $w$ 就被减了两次，出锅了

我们只需再转移时多取一个 $\max$，即 

$$
dp_i = \max\limits_{j < i}\{dp_j + s_{2, i} - s_{2,j} - w, s_{1, j} + s_{2, i} - s_{2, j - 1} - w\}
$$

相当于把进入 $(2, i)$ 和 $(2, j)$ 的费用一起考虑了

所以再维护后缀最大值时要维护两种情况的

II. 发现一个左端点为 $mid + 1$ 的 `offer` 也可以用来转移！

因为 $dp_{mid}$ 表示的是到 $(2, mid)$ 的最大权值，所以我还可通过这个 `offer` 将 $dp_{mid}$ 转移给右儿子，因此对于一个 $[l, r]$ 的 `offer`，实际可转移的范围为 $[l - 1, r]$，前提是用 $dp_{l - 1}$ 来转移，而不能用 $s_{1, l - 1}$（必须保证在 $(2, l - 1)$ 这个点）

III. 注意将 $dp$ 初始化为 $-\infty$ 时，不要赋得太小，导致爆 `long long` 炸成 $+\infty$

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
const int N = 5e5 + 5;
const ll inf = 1e17;
int n, m;
ll s[4][N];
struct node
{
    int l, r;
    ll w;
}a[N];
ll dp[N], mx[2][N];
vector<int> v[N << 2];
inline bool cmp(const int &x, const int &y) {return a[x].r > a[y].r;}
inline void cdq(int p, int l, int r, ll mn)
{
    if (l == r) return dp[l] = max(dp[l], s[1][l] + s[2][l] - s[2][l - 1] - mn), void();
    int mid = l + r >> 1;
    vector<int> link;
    ll lmn = mn, rmn = mn;
    for (auto i : v[p])
    {
        if (a[i].l <= l && a[i].r >= mid) lmn = min(lmn, a[i].w);
        else if (a[i].l <= mid) v[p << 1].push_back(i);
        if (a[i].l <= mid + 1 && a[i].r >= r) rmn = min(rmn, a[i].w);
        else if (a[i].r > mid) v[p << 1 | 1].push_back(i);
        if (a[i].l - 1 <= mid && a[i].r > mid) link.push_back(i);
    }
    cdq(p << 1, l, mid, lmn);
    mx[0][mid + 1] = mx[1][mid + 1] = -inf;
    int L = max(l - 1, 1);
    for (re int i = mid; i >= L; --i)
        mx[0][i] = max(mx[0][i + 1], s[1][i] - s[2][i - 1]),
        mx[1][i] = max(mx[1][i + 1], dp[i] - s[2][i]);
    sort(link.begin(), link.end(), cmp);
    auto now = link.begin();
    ll MX = max(mx[0][l], mx[1][L]) - mn;
    for (re int i = r; i > mid; --i)
    {
        while (now != link.end() && a[*now].r >= i)
        {
            MX = max(MX, max(mx[0][max(a[*now].l, l)], mx[1][max(a[*now].l - 1, L)]) - a[*now].w);
            ++now;
        }
        dp[i] = max(dp[i], MX + s[2][i]);
    }
    cdq(p << 1 | 1, mid + 1, r, rmn);
}
signed main()
{
    n = read(), m = read();
    for (re int i = 1; i <= 3; ++i)
        for (re int j = 1; j <= n; ++j) s[i][j] = s[i][j - 1] + read();
    for (re int i = 1; i <= m; ++i) a[i] = {read(), read(), read()};
    ll mn = inf;
    for (re int i = 1; i <= m; ++i)
    {
        if (a[i].l <= 1 && a[i].r >= n) mn = min(mn, a[i].w);
        else v[1].push_back(i);
    }
    for (re int i = 1; i <= n; ++i) dp[i] = -inf;
    cdq(1, 1, n, mn);
    ll ans = -inf;
    for (re int i = 1; i <= n; ++i)
    {
        ll val = dp[i] + s[3][n] - s[3][i - 1];
        ans = max(ans, val);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：tuxuanming2024 (赞：3)

一个只用一棵线段树的做法。

## 题意

有三个长度为 $n$ 的数组 $a,b,c$，定义 $V(l,r) = \sum_{i=1}^{l} a_i + \sum_{i=l}^r b_i +\sum_{i=r}^n c_i$。有 $q$ 个区间 $l_i,r_i$，每个区间都有个权值 $k_i$。你可以选择一个区间集合 $S$，和一对 $L,R$，满足 $[L,R] \subseteq \bigcup_{i \in S} [l_i,r_i]$。最大化 $V(L,R)-\sum_{i \in S} k_i$ 的值。

## 题解

设 $L,R$ 为最终选择的区间。将 $a,b$ 前缀和起来，$c$ 后缀和起来（下文中直接用 $a,b,c$ 表示前后缀和后的数组），那么 $V(l,r) = a_l+b_r-b_{l-1}+c_r$。

注意到 $V(l,r) = (a_l-b_{l-1}) + (b_r+c_r)$。这启示我们似乎可以枚举右端点，左端点数据结构来维护。

我们将 $q$ 个区间按右端点排序，对于当前第 $i$ 个区间，考虑如下几种组成答案的方式：

- $L,R$ 都在这个区间内，即 $l_i \le L \le R \le r_i$。

- $L$ 在 $i$ 之前的区间，$R$ 在 $i$ 区间内，即 $L \le l_i \le R \le r_i$。

第一种情况用线段树很好维护，我们主要考虑第二种情况。

设 $f_i$ 表示 $L \le r_i$，且 $R > r_i$ 时的 $a_L-b_{L-1}$ 减选择的区间的权值和 的 最大值。说白了就是强制 $[L,R]$ 跨过 $r_i$，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ipcenlui.png)

转移也就比较显然了，每个点要么继承之前区间的左端点，要么左端点在当前区间：

$$f_i = \max(\max_{l_i \le r_j \le r_i}f_j,\max_{k=l_i}^{r_i}\{a_k-b_{k-1}\})-k_i$$

那么就可以这么更新答案，对于每个 $i$：

$$\text{ans} = \max_{l_i \le r_j \le r_i} \{f_j+\max_{k=r_j}^{r_i} \{b_k+c_k\}\}-k_i$$

现在就是怎么维护 $f_j+\max \{b_k+c_k\}$ 的问题。

我们维护一个指针 $p$，每加入一个区间 $i$，就将 $r_i$ 之前的所有位置都作为右端点尝试一遍，用 $f_j+b_p+c_p$ 去更新 $j \le p$ 的上式的值。

这就形如一个经典问题：两个数组 $A,B$，两种操作，对 $i \in [l,r]$ 的 $B_i$ 对某个值取 $\max$，以及询问一个区间的 $A_i + B_i$ 的最大值。

在线段树上记录 $A_i$ 的最大值、$A_i+B_i$ 的最大值、以及 $B$ 取最大值的 $\text{tag}$。每次更新的时候就用 $A_{\max}+\text{tag}$ 来更新结果就行了。

那么这个题就做完了。复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005;
int n,m;
ll a[3][N],st[N][20],ans=-1e18;
struct Node
{
    int l,r,k;
    bool operator < (const Node &a)const {return r<a.r;}
}b[N];
struct node {int l,r; ll res,mx,tag;}t[N<<2];
void pushup(int x)
{
    t[x].res=max(t[x<<1].res,t[x<<1|1].res);
    t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
}
void upd(int x,ll v) {t[x].tag=max(t[x].tag,v),t[x].res=max(t[x].res,t[x].mx+v);}
void pushdown(int x)
{
    if(t[x].tag!=-1e18) upd(x<<1,t[x].tag),upd(x<<1|1,t[x].tag),t[x].tag=-1e18;
}
void build(int x,int l,int r)
{
    t[x].l=l,t[x].r=r,t[x].tag=t[x].mx=t[x].res=-1e18;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(x<<1,l,mid),build(x<<1|1,mid+1,r);
}
void add(int x,int l,int r,ll v)
{
    if(r<t[x].l||l>t[x].r) return;
    if(l<=t[x].l&&r>=t[x].r) {upd(x,v); return;}
    pushdown(x);
    add(x<<1,l,r,v),add(x<<1|1,l,r,v);
    pushup(x);
}
void modify(int x,int k,ll v)
{
    if(t[x].l==t[x].r)
    {
        t[x].mx=max(t[x].mx,v);
        // cout<<"modify "<<t[x].l<<" "<<t[x].mx<<'\n';
        t[x].res=max(t[x].res,v+t[x].tag);
        return;
    }
    pushdown(x);
    int mid=(t[x].l+t[x].r)>>1;
    modify(x<<1|(k>mid),k,v),pushup(x);
}
ll ask(int x,int l,int r)
{
    if(r<t[x].l||l>t[x].r) return -1e18;
    if(l<=t[x].l&&r>=t[x].r) return t[x].res;
    pushdown(x);
    return max(ask(x<<1,l,r),ask(x<<1|1,l,r));
}
ll askmx(int x,int l,int r)
{
    if(r<t[x].l||l>t[x].r) return -1e18;
    if(l<=t[x].l&&r>=t[x].r) return t[x].mx;
    pushdown(x);
    return max(askmx(x<<1,l,r),askmx(x<<1|1,l,r));
}
ll stask(int l,int r) {int x=__lg(r-l+1); return max(st[l][x],st[r-(1<<x)+1][x]);}
int main()
{
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    scanf("%d %d",&n,&m);
    for(int i=0;i<3;i++)
        for(int j=1;j<=n;j++) scanf("%lld",&a[i][j]);
    for(int i=1;i<=n;i++) a[0][i]+=a[0][i-1],a[1][i]+=a[1][i-1];
    for(int i=n;i>=1;i--) a[2][i]+=a[2][i+1],st[i][0]=a[0][i]-a[1][i-1];
    for(int j=1;1<<j<=n;j++)
        for(int i=1;i<=n-(1<<j)+1;i++) st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    for(int i=1;i<=m;i++) scanf("%d %d %d",&b[i].l,&b[i].r,&b[i].k);
    sort(b+1,b+1+m);
    build(1,0,n);
    int p=1;
    for(int i=1;i<=m;i++)
    {
        while(p<=b[i].r) add(1,0,p,a[1][p]+a[2][p]),p++;
        ans=max(ans,ask(1,b[i].l-1,b[i].r)-b[i].k);
        modify(1,b[i].r,max(askmx(1,b[i].l-1,b[i].r),stask(b[i].l,b[i].r))-b[i].k);
    }
    build(1,0,n),p=1;
    for(int i=1;i<=m;i++)
    {
        while(p<=b[i].r) modify(1,p,a[0][p]-a[1][p-1]),add(1,0,p,a[1][p]+a[2][p]),p++;
        ans=max(ans,ask(1,b[i].l,b[i].r)-b[i].k);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：hj23308 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1648D)

### $\mathcal{Problem}$

有一个 $3$ 行 $n$ 列的矩阵，第 $2$ 行所有位置无法通过，而第 $1$ 行和第 $3$ 行所有位置都可以通过。

有 $q$ 个可任选的操作，第 $i$ 个操作可以使第 $2$ 行 $l_i\sim r_i$ 个位置可以被通过，代价为 $k_i$。

在选择这些操作后，需要从第 $1$ 行第 $1$ 列走到第 $3$ 行第 $n$ 列，且在第 $i$ 行第 $j$ 列只能走到第 $i+1$ 行第 $j$ 列（$i<3$）或第 $i$ 行第 $j+1$ 列（$j<n$），收益为经过的所有位置的数字之和。

你需要最大化收益减代价的差，输出这个差。

$1 \leq n,q \le 500\ 000,-10^9\le a_{i,j}\le 10^9,1\le l_i\le r_i\le n,1\le k_i\le 10^9$。

### $\mathcal{Solution}$ 

我们用 $X, Y, Z$ 分别表示三行数字的前缀和。

#### Step 1: 处理上两行的移动。

首先分析进行的操作所满足的性质：对于任一操作，其代价均为正值，故操作的区间不应该出现一个完全包含另一个的情况，且最后覆盖成一个连续的区间。

将操作所对应区间按右端点排序，按顺序考虑每个操作是否进行，使用动态规划。

具体的，我们用 $ dp _ i $ 表示从 $(1, 1)$ 开始进行若干次移动，到达 $(1, i)$ 或 $(2, i-1)$，且位置 $(2, i)$ **还未被操作覆盖**时的最大得分（收益减代价），初始值 $dp_i=X_i$。

对于一个操作 $(l, r, k)$，有转移 $ dp _ {r + 1} \gets \max\left(dp_{r + 1}, Y _ r - k + \max\{dp _ i - Y_{i - 1} \mid l \le i \le r\}\right) $，按照 $r$ 从小到大转移。涉及到一个单点修改、区间求最大值的数据结构，可以简单的用线段树维护。

#### Step 2: 处理下两行的移动。

回顾在 Step 1 中 $dp_i$ 的定义，此时 $ (2, i) $ 是**还未被覆盖的**，无法经过 $ (2, i) $ 到达 $(3, n)$。为了经过 $(2, i) $，我们还需要一次额外操作，然后经过一个拐点 $ j $，走到 $ (3, n) $，具体路线为 $ \dots \to (1, i) / (2, i - 1) \to (2, i) \to \dots \to (2, j) \to (3, j) \to \dots \to (3, n) $。

考虑枚举额外的操作。对于额外的操作 $ (l, r, k) $，要求 $ l\le i\le r $，枚举拐点 $ j $，最大得分为 $ (dp_i + Z_n - Y_{i - 1}) + \max\{Y _ j - Z_{j - 1} - k \mid i \le j \le r\} $。

分析此式如何快速计算：

- 前半部分：为定值，不用考虑。

- 后半部分：

	- 维护某种数据结构，从左到右枚举 $i$，操作 $(l, r, k)$ 在 $ l = i $ 时加入数据结构里，解决 $l \le i$ 的限制。

	- 而对于其他限制是一个经典模型：

	- > 给一个初始的数组 $A$，一个等长且初值均为 $-\infin$ 的数组 $B$，若干次修改和查询。
		>
		> - 修改：形如 $(l, r, k)$，表示修改 $\forall l\le i\le r,B_i\gets\max(B_i, A_i + k)$。
		> - 查询：形如 $(l, r)$，表示询问 $\max\{B_i\mid l\le i\le r\}$。

	- 可以使用线段树加懒标记（表示修改）维护（具体见代码）。

时间复杂度 $\mathcal O(n\log n)$，空间复杂度 $\mathcal O(n)$。

### [$ \mathcal{Record} $](https://codeforces.com/contest/1648/submission/239778597)

### $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>

using namespace std;

#define REP(i, l, r) for (int i = l; i <= r; i++)
#define PER(i, r, l) for (int i = r; i >= l; i--)

const int maxN = 5e5 + 2;

const long long inf = 0x3f3f3f3f3f3f3f3f;

int n, q;
vector<pair<int, int>> opt[maxN];
long long dp[maxN];
long long sum1[maxN], sum2[maxN], sum3[maxN];

namespace SegmentTree1 {
	long long mx[maxN << 2];

#define M(u) mx[u]
#define LS(u) (u << 1)
#define RS(u) (u << 1 | 1)

	void pushUp(int u) { M(u) = max(M(LS(u)), M(RS(u))); }

	void Build(int u = 1, int L = 1, int R = n) {
		if (L > R) return;
		if (L == R) return M(u) = dp[L] - sum2[L - 1], void();
		int mid = (L + R) >> 1;
		Build(LS(u), L, mid);
		Build(RS(u), mid + 1, R);
		pushUp(u);
	}

	void Modify(int x, long long v, int u = 1, int L = 1, int R = n) {
		if (R < x || x < L) return;
		if (L == R) return M(u) = max(M(u), v - sum2[L - 1]), void();
		int mid = (L + R) >> 1;
		Modify(x, v, LS(u), L, mid);
		Modify(x, v, RS(u), mid + 1, R);
		pushUp(u);
	}

	long long Query(int l, int r, int u = 1, int L = 1, int R = n) {
		if (R < l || r < L) return -inf;
		if (l <= L && R <= r) return M(u);
		int mid = (L + R) >> 1;
		return std::max(Query(l, r, LS(u), L, mid), Query(l, r, RS(u), mid + 1, R));
	}

#undef M
#undef LS
#undef RS
}

namespace SegmentTree2 {
	struct Node {
		long long sum, tag, mx;

		void updateTag(long long x) {
			mx = max(mx, sum + x);
			tag = max(tag, x);
		}
	} nodes[maxN << 2];

#define LS(u) (u << 1)
#define RS(u) (u << 1 | 1)
#define S(u) nodes[u].sum
#define T(u) nodes[u].tag
#define M(u) nodes[u].mx

	void pushUp(int u) {
		S(u) = max(S(LS(u)), S(RS(u)));
		M(u) = max(M(LS(u)), M(RS(u)));
	}

	void pushDown(int u) {
		if (T(u) != -inf) {
			nodes[LS(u)].updateTag(T(u));
			nodes[RS(u)].updateTag(T(u));
			T(u) = -inf;
		}
	}

	void Build(int u = 1, int L = 1, int R = n) {
		if (L > R) return;
		T(u) = -inf;
		if (L == R) return M(u) = -inf, S(u) = sum2[L] - sum3[L - 1], void();
		int mid = (L + R) >> 1;
		Build(LS(u), L, mid);
		Build(RS(u), mid + 1, R);
		pushUp(u);
	}

	void Modify(int l, int r, long long v, int u = 1, int L = 1, int R = n) {
		if (R < l || r < L) return;
		if (l <= L && R <= r) return nodes[u].updateTag(v), void();
		int mid = (L + R) >> 1;
		pushDown(u);
		Modify(l, r, v, LS(u), L, mid);
		Modify(l, r, v, RS(u), mid + 1, R);
		pushUp(u);
	}

	long long Query(int l, int r, int u = 1, int L = 1, int R = n) {
		if (R < l || r < L) return -inf;
		if (l <= L && R <= r) return M(u);
		int mid = (L + R) >> 1;
		pushDown(u);
		return max(Query(l, r, LS(u), L, mid), Query(l, r, RS(u), mid + 1, R));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int x;
	cin >> n >> q;
	REP(i, 1, n) cin >> x, dp[i] = sum1[i] = sum1[i - 1] + x;
	REP(i, 1, n) cin >> x, sum2[i] = sum2[i - 1] + x;
	REP(i, 1, n) cin >> x, sum3[i] = sum3[i - 1] + x;
	vector<tuple<int, int, int>> t(q);
	for (auto &[r, l, k]: t) cin >> l >> r >> k, opt[l].emplace_back(r, k);
	sort(t.begin(), t.end());
	SegmentTree1::Build();
	for (auto [r, l, k]: t) {
		if (r == n) continue;
		long long res = SegmentTree1::Query(l, r) + sum2[r] - k;
		dp[r + 1] = max(dp[r + 1], res);
		SegmentTree1::Modify(r + 1, res);
	}

	SegmentTree2::Build();
	long long ans = -inf;
	REP(i, 1, n) {
		long long res = dp[i] + sum3[n] - sum2[i - 1];
		for (auto [r, k]: opt[i]) SegmentTree2::Modify(i, r, -k);
		long long tmp = SegmentTree2::Query(i, n);
		ans = max(ans, res + tmp);
	}
	cout << ans << '\n';

	return 0;
}

/*
 * Step 1: 处理上两行的情况，dp[i] 表示未覆盖 i，由 (2, i - 1) 或 (1, i) 结尾的最大价值。
 *  Case 1: 由一个区间得来，此时有 dp[i] = sum1[i]。
 *  Case 2: 由多个区间合并得来，有 dp[r + 1] = sum2[r] - k + max{max(dp[i] - sum2[i - 1] | l <= i <= r}，是好求的。
 * Step 2: 处理下两行的情况，枚举最后一个加的区间，用 dp[i] 辅助求答案。
 *  由 (2, i) 开始移动，初始价值 dp[i]，需要再操作一个 (l, r, k) 使得 l <= i <= r，
 *  对于某个合法的 (l, r, k)，ans = (dp[i] + sum3[n] - sum2[i - 1]) + max{sum2[j] - sum3[j - 1] | l <= j <= r} - k
 *  分析此式：
 *   前半部分：为定值，不用考虑。
 *   后半部分：
 *    从左到右扫描，当 i = l 时把 (l, r, k) 加入数据结构里，解决 l <= i 限制，
 *    而对于其他限制，把 -k 移到 max{...} 部分里，可以发现是一个类似三级跳的结构，直接维护。
 * 时间复杂度 O(n log n)。
 */
```

---

## 作者：dead_X (赞：3)

## 思路
记一条路径在第二行经过了 $[l,r]$ 段，激活的区间价值和为 $f(l,r)$，那么这个路径的价值就是 $A_l-f(l,r)+B_r$，其中 $A_i,B_i$ 都可以通过每个格子的权值平凡预处理，时间复杂度 $O(n)$。

不难发现最优策略中，除了最后一个线段，其它线段都是走满的~~然后做完了~~，我们可以尝试先在每个线段都走满的情况下，对于每个 $r$ 求出 $F_r=\min\{A_l-f(l,r)\}$。

我们不难计算出从 $(1,1)$ 开始，走了若干个满的段到 $(2,x)$ 的费用，这里的转移就是 $f_x=\min\limits_{y=l}^r\{f_y\}+k$，这可以用线段树平凡解决，时间复杂度 $O(q\log n)$。

最后我们枚举最后一段，这里要解决的是 $\min\limits_{l\leq x\leq y\leq r}F_x+B_y$，这个也可以线段树做，时间复杂度 $O(q\log n)$。 

---

## 作者：hegm (赞：2)

### [CF1648D Serious Business](https://www.luogu.com.cn/problem/CF1648D)

先不考虑最后一行。

那么处理出 $f_i$ 表示 $(1,1)\to(2,i)$ 所能得到的最大金币数量。

答案就是 $\max\limits_{i=1}^n(f_i+\sum\limits_{j=i}^n w_{3,j})$

考虑如何转移 $f_i$。

$s_{i,j}$ 为第 $i$ 行 $1\sim j$ 的金币和。

$v_i$ 表示的是第 $i$ 个区间的花费。

分情况讨论下。

1. 操作多个区间。
	
    对于区间$j:$ $l\sim r$ 那么既然是多个区间，所以一定是从 $(2,l-1)$ 过来的，因此 $f_i=\max(f_i,f_{l-1}-v_j+s_{2,i}-s_{2,l-1})$。
    
    为了转移方便，设 $g_i=f_i-s_{2,i}$。
    
    式子变为 $g_i=\max(g_i,g_{l-1}-v_j)$。
    
    这玩意线段树维护就好了。
    
2. 操作只有一个区间。

	这时候有两种情况：
    
    - 直接从 $(1,i)$ 到 $(2,i)$。
    
    $g_i=\max(g_i,s_{1,i}-s_{2,i-1}-v_j)$
    
    - 从之前的某个 $(2,j)$ 到 $(2,i)$（$j$ 在 $l\sim r$ 中）
    $g_i=\max\limits_{j=l}^i (g_i,g_j)$
    
    注意这里的 $g_j$ 是在 $s_{1,j}-s_{2,j-1}-v_j$ 意义下的。
    
    所以可以直接写成 $g_i=\max\limits_{j=l}^i (g_i,s_{1,j}-s_{2,j-1}-v_j)$
    
    但是这玩意不太好维护（可能有大佬觉得很简单）
    
    不妨这么操作，首先修改的是 $l\sim r$ 的区间，由于整体的变化只有取 $\max$ 的 $l$ 限制和 $v_j$ 所以只考虑记录他们两个。
    
    但是发现如果直接用懒标记记录是无法合并的，因此换一种形式，对于一个线段树区间 $L\sim R$，将 $l\sim L-1$ 的 $g_i,s_{1,j}-s_{2,j-1}-v_j$ 最大值找出来直接当做懒标记打上去，那么此时 $l$ 就可以不用记录了，因为 $L\sim R$ 的点都会被这种操作影响。因此只需要记录 $v_j$，那么 $v_j$ 可以直接合并，贪心取最小的就好。
    
    那么如何下传，考虑如果 $L\sim R$ 被 $v$ 包含了，那么 $i\in [L,R]$ 都有 $\max\limits_{j=L}^i (g_i,s_{1,j}-s_{2,j-1}-v_j)$ 没有操作，考虑左侧，可以直接将 $v$ 下传，而右侧先找到 $\max\limits_{j=L}^{mid} (g_i,s_{1,j}-s_{2,j-1}-v_j)$，将它作为取 $\max$ 打在右侧的懒标记上就好了。然后下传 $v_j$。
    

---

## 作者：赵悦岑 (赞：2)

[My Blog](https://2745518585.github.io/post/CF1648-solution/)

### 题意

给定一个 $3 \times n$ 的矩阵，每个位置有一个值。第一行和第三行可以走，第二行不可以。共有 $q$ 个操作，第 $i$ 个操作可以用 $k_i$ 的代价把第二行 $[l_i,r_i]$ 变为可以走，求经过的位置的价值和减去总代价的最大值。

### 解法

显然在第二行经过的位置是一段连续的区间，所以选择的操作的区间也是连续的，且除了第一段和最后一段区间之外全部会走满。我们把总价值拆成两部分：$a_l-b_{l-1}$ 与 $b_r+(c_n-c_{r-1})$，其中 $a,b,c$ 分别是三行的价值， $l,r$ 是进入和离开第二行的位置。我们考虑把第一部分贡献转移到最后一段区间：首先把 $a_j-b_{j-1}$ 转移到 $f_j$，由于第一个和中间的区间都是走到了区间末尾的，所以区间 $i$ 的贡献就是把 $\max\limits_{l_i \leq j \leq r_i} f_j-k_i$ 贡献到 $f_{r_i}$。用线段树维护。

然后我们需要把在同一个区间的两种贡献合并，也就是对于区间 $i$，对于任意 $j,p \in [l_i,r_i],j \leq p$，把 $f_j + b_p+(c_n-c_{p-1}) -p_i$ 贡献到总答案。这里需要保证 $j \leq p$，也可以用线段树维护，每次把左子树最大的 $f_j$ 和右子树最大的 $b_p+(c_p-c_{p-1})$ 相加贡献到答案即可。

### code

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m;
ll a[N],b[N],c[N];
struct str
{
    int x,y,k;
    str(){}
    str(int x,int y,int k):x(x),y(y),k(k){}
};
vector<str> d[N],e;
struct tree
{
    int l,r;
    ll s,t1,t2,s2;
}T[N<<2];
void pushup(tree &T,tree T1,tree T2)
{
    T.s=max(T1.s,T2.s);
    T.s2=max(T1.t1+T2.t2,max(T1.s2,T2.s2));
    T.t1=max(T1.t1,T2.t1);
    T.t2=max(T1.t2,T2.t2);
}
void build(int x,int l,int r)
{
    T[x].l=l;
    T[x].r=r;
    if(l==r)
    {
        T[x].s=a[l]-b[l-1];
        T[x].t1=a[l]-b[l-1];
        T[x].t2=b[l]+(c[n]-c[l-1]);
        T[x].s2=T[x].t1+T[x].t2;
        return;
    }
    int z=l+r>>1;
    build(x<<1,l,z);
    build(x<<1|1,z+1,r);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
void add(int x,int q,ll k)
{
    if(T[x].l==T[x].r)
    {
        T[x].s=max(T[x].s,k);
        T[x].t1=max(T[x].t1,k);
        T[x].s2=T[x].t1+T[x].t2;
        return;
    }
    int z=T[x].l+T[x].r>>1;
    if(q<=z) add(x<<1,q,k);
    else add(x<<1|1,q,k);
    pushup(T[x],T[x<<1],T[x<<1|1]);
}
ll sum(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x].s;
    }
    int z=T[x].l+T[x].r>>1;
    ll s=-1e18;
    if(l<=z) s=max(s,sum(x<<1,l,r));
    if(r>z) s=max(s,sum(x<<1|1,l,r));
    return s;
}
tree sum2(int x,int l,int r)
{
    if(T[x].l>=l&&T[x].r<=r)
    {
        return T[x];
    }
    int z=T[x].l+T[x].r>>1;
    tree s;
    if(l<=z&&(!(r>z))) s=sum2(x<<1,l,r);
    else if((!(l<=z))&&r>z) s=sum2(x<<1|1,l,r);
    else pushup(s,sum2(x<<1,l,r),sum2(x<<1|1,l,r));
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&b[i]);
        b[i]+=b[i-1];
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&c[i]);
        c[i]+=c[i-1];
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        d[y].push_back(str(x,y,k));
        e.push_back(str(x,y,k));
    }
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        ll s=-1e18;
        for(auto j:d[i])
        {
            s=max(s,sum(1,j.x,j.y)-j.k);
        }
        if(i<n) add(1,i+1,s);
    }
    ll s=-1e18;
    for(auto i:e)
    {
        s=max(s,sum2(1,i.x,i.y).s2-i.k);
    }
    printf("%lld",s);
    return 0;
}
```



---

## 作者：zyc070419 (赞：2)

# [[CF1648D]Serious Business](https://www.luogu.com.cn/problem/CF1648D) 题解

首先容易想到一个 $dp$ 转移式子：
$$
dp_{i}=\max_{j\le i} s_{1,j}-cost_{j,i}-s_{2,j-1}+s_{2,i}+s_{3,n}-s_{3,i-1}
$$
其中 $dp_i$ 表示到第 $2$ 行的第  $i$ 列处移动至第 $3$ 行的最大价值， $cost_{j,i}$ 表示第 $2$ 行 $j$ 到 $i$ 联通的最小代价， $s_{i}$ 为第 $i$ 行的前缀和数组。

其余部分都是可以预处理的，只有 $cost_{j,i}$ 这一块儿是没法快速求出的，其实可以考虑枚举哪一条线段包含了 $i$ 然后进行转移，大概形式为：
$$
dp_{i}=\max_{l_j\le i \le r_j}val_{j}+s_{2,i}+s_{3,n}-s_{3,i-1}
$$
其中 $val_j$ 表示选择的最靠右的线段为 $j$ 时，并且当前没有走到 $i$ 的最大价值。

而 $val_j$ 其实有两种情况：第一种是只使用了 $j$ 这一个线段；另一种是使用了超过一条线段，并且所有选择的线段的并也是一条完整的线段。

两种情况的 $dp$ 式子为：
$$
\left\{
\begin{matrix}
&dp_i&=&\max_{l_j\le i\le r_j}&\{\max_{l_j\le t\le i}s_{1,t}-s_{2,t-1}\}-k_j+s_{2,i}+s_{3,n}-s_{3,i-1}\\\\
&dp_{i}&=&\max_{l_j\le i\le r_j}&dp_{l_j-1}-k_j-s_{2,l_j-1}+s_{2,i}+s_{3,n}-s_{3,i-1}
\end{matrix}
\right.
$$
先看第一个式子。因为是求区间 $\max$ ，所以说可以考虑用一下线段树去优化转移。

因为是 $\max$ 套 $\max$ ，所以说我们线段树去维护转移点时也可以分两段去维护。第一个维护的值是区间的 $\min k_j$ ，第 $j$ 条线段对于 $i$ 点转移的额外贡献为 $k_j$ ，影响区间为 $[l_j,r_j]$ ，所以可以写一个区间取 $\min$ 。

然后看内层枚举  $t$ 如何维护。考虑 $t$ 能作为哪些 $i$ 的决策点，显然是 $i\in[t,n]$ 的点，所以说可以再写一个区间取 $\max$ ，每次在一个后缀插入 $s_{1,t}-s_{2,t-1}$ 。

有了这两个值的维护，也就可以同时求出第一个式子的转移式子了。

但是有两个区间修改，还要动态维护这两个值的差的最大值，不是很好维护，这里有一个小 $trick$ 可以用一下：

因为考虑到每一次 $t$ 的值的修改都是一个后缀，而我们插入线段没有必要一次性全插进去，可以当进行 $dp_i$ 的转移时再把所有 $l_j\le i$ 的线段插入线段树，所以说其实可以把线段的修改由 **区间修改** 转变为 **前缀修改** ，所以说其实可以再进一步抽象，把 **前缀修改** 变为在 $r_j$ 处的单点修改，并且查询由 **单点查询** 变为 **后缀查询** ，可以发现，这样正确性是有保障的（其实前缀变成单点，然后查询再把后缀查了，就是相当于把原来能够干预到 $i$ 的所有线段都计算了一遍），而这样修改只有一个区间修改，就会非常好操作。

现在说一下第二个式子，这个就比较简单了，可以维护一个 $set$ ，维护当前所有 $l_j\le i\le r_j$ 的线段的 $dp_{l_j-1}-k_j-s_{2,l_j-1}$ 的值，然后当 $i>r_j$ 时就把 $j$ 对应的值删掉即可。

下面给出 **[代码](https://www.luogu.com.cn/paste/hd9my47d)** 。

---

## 作者：Leasier (赞：1)

首先你肯定是这样走：$(1, 1) \to (1, i) \to (2, i) \to (2, j) \to (3, j) \to (3, n)$。

考虑 dp，设从 $(1, 1)$ 走到 $(2, i)$ 所需最少代价，处理出每行的前缀和（记为 $sum_{i, j}$），则答案为 $\displaystyle\max_{i = 1}^n (dp_i + (sum_{3, n} - sum_{3, i - 1}))$。

现在我们考虑一个线段 $[l, r]$，其代价为 $w$，我们将所有线段按 $l$ 升序插入并更新 dp 值。不妨考虑一个 $i \in [l, r]$。

1. 对于某个 $j \in [l, i]$，从 $(1, j) \to (2, j) \to (2, i)$ 并使用当前线段

此时 $dp_i \leftarrow \max(dp_i, sum_{1, j} + (sum_{2, i} - sum_{2, j - 1}) - w)$。

2. 对于某个 $j \in [1, l)$，从 $(1, j) \to (2, j) \to (2, i)$ 并使用当前线段

贪心地，我们会尽量多地使用当前线段（即全部用完），此时 $dp_i \leftarrow \max(dp_i, dp_{l - 1} + (sum_{2, i} - sum_{2, l - 1}) - w)$。

但直接做是 $O(nq)$ 的，考虑优化。

首先转移 2 看上去是容易的，设 $f_i = dp_i - sum_{2, i}$，则转移 2 可以表示为：$f_i \leftarrow \max(f_i, f_{l - 1} - w)$，我们只需要维护单点查询和区间 chkmax 操作即可。

现在我们把转移 1 也写成 $f$ 的形式：$f_i \leftarrow \max(f_i, sum_{1, j} - sum_{2, j - 1} - w)$。

我们仍然考虑在线段树上维护该操作。

对于一个区间 $[l, r]$ 的操作，我们考虑维护一个引用变量 $val$，例如我们在线段树递归的过程中找到了一个它的极大子区间 $[l', r']$，则该区间本身的答案要与 $val - w$ 取 max，然后令 $val \leftarrow \max(val, \displaystyle\max_{i = l'}^{r'} (sum_{1, i} - sum_{2, i - 1}))$，后半部分是可以对线段树上每个区间预处理的。当然，我们也需要维护每个区间可以取到的 $w$ 的最小值。

现在最麻烦的是如何 pushdown。

$w$ 的最小值直接取 min 下传即可，左儿子的答案直接取 max 即可。

对于右儿子，我们把每个区间的转移 1 带来的贡献分为**父亲这棵子树外**和**左儿子子树外**两种情况。

对于第一种情况，继承父亲的 tag 即可。

对于第二种情况，将右儿子的答案与 $\displaystyle\max_{i = l'}^{r'} (sum_{1, i} - sum_{2, i - 1}) - minw$，其中 $[l', r']$ 为左儿子管辖区间，$minw$ 为下传到父亲的 $w$ 中最小者。

处理完所有线段后，在线段树上 dfs 并沿路 pushdown 即可，注意最终 $f_i$ 为线段树上当前点的最大值与 $sum_{1, i} - sum_{2, i - 1} - minw$ 取最大值，因为后面这种情况我们在之前没有讨论（我们始终讨论的是不同区间之间产生的贡献）。

时间复杂度为 $O(n + q \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	int l;
	int r;
	ll tag1;
	ll tag2;
	ll tag3;
	ll min;
	ll max1;
	ll max2;
} Node;

typedef struct {
	int l;
	int r;
	int cost;
} Segment;

ll sum[7][500007];
Node tree[2000007];
Segment segment[500007];

bool operator <(const Segment a, const Segment b){
	return a.l < b.l;
}

inline int read(){
	int sign = 1, ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') sign = -sign;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return sign * ans;
}

inline void update(int x){
	tree[x].max1 = max(tree[x * 2].max1, tree[x * 2 + 1].max1);
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].tag1 = tree[x].min = 9e18;
	tree[x].tag2 = tree[x].tag3 = -9e18;
	if (l == r){
		tree[x].max1 = sum[1][l] - sum[2][l - 1];
		tree[x].max2 = -9e18;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	update(x);
}

inline void pushdown(int x){
	int ls = x * 2, rs = x * 2 + 1;
	ll t = max(tree[x].tag3, tree[ls].max1 - tree[x].tag1);
	tree[ls].tag1 = min(tree[ls].tag1, tree[x].tag1);
	tree[rs].tag1 = min(tree[rs].tag1, tree[x].tag1);
	tree[ls].tag2 = max(tree[ls].tag2, tree[x].tag2);
	tree[rs].tag2 = max(tree[rs].tag2, tree[x].tag2);
	tree[ls].tag3 = max(tree[ls].tag3, tree[x].tag3);
	tree[rs].tag3 = max(tree[rs].tag3, t);
	tree[ls].min = min(tree[ls].min, tree[x].tag1);
	tree[rs].min = min(tree[rs].min, tree[x].tag1);
	tree[ls].max2 = max(tree[ls].max2, max(tree[x].tag2, tree[x].tag3));
	tree[rs].max2 = max(tree[rs].max2, max(tree[x].tag2, t));
	tree[x].tag1 = 9e18;
	tree[x].tag2 = tree[x].tag3 = -9e18;
}

ll get_val(int x, int pos){
	if (tree[x].l == tree[x].r) return max(tree[x].max2, tree[x].max1 - tree[x].min);
	pushdown(x);
	if (pos <= ((tree[x].l + tree[x].r) >> 1)) return get_val(x * 2, pos);
	return get_val(x * 2 + 1, pos);
}

void maximize(int x, int l, int r, ll k){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag2 = max(tree[x].tag2, k);
		tree[x].max2 = max(tree[x].max2, k);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) maximize(x * 2, l, r, k);
	if (r > mid) maximize(x * 2 + 1, l, r, k);
}

void solve(int x, int l, int r, int k, ll &val){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag1 = min(tree[x].tag1, (ll)k);
		tree[x].min = min(tree[x].min, (ll)k);
		tree[x].tag3 = max(tree[x].tag3, val - k);
		tree[x].max2 = max(tree[x].max2, val - k);
		val = max(val, tree[x].max1);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) solve(x * 2, l, r, k, val);
	if (r > mid) solve(x * 2 + 1, l, r, k, val);
}

ll dfs(int x){
	if (tree[x].l == tree[x].r) return max(tree[x].max2, tree[x].max1 - tree[x].min) + sum[2][tree[x].l] - sum[3][tree[x].l - 1];
	pushdown(x);
	return max(dfs(x * 2), dfs(x * 2 + 1));
}

int main(){
	int n = read(), q = read();
	for (register int i = 1; i <= 3; i++){
		for (register int j = 1; j <= n; j++){
			int a = read();
			sum[i][j] = sum[i][j - 1] + a;
		}
	}
	build(1, 1, n);
	for (register int i = 1; i <= q; i++){
		segment[i].l = read();
		segment[i].r = read();
		segment[i].cost = read();
	}
	sort(segment + 1, segment + q + 1);
	for (register int i = 1; i <= q; i++){
		ll val = -9e18;
		if (segment[i].l > 1) maximize(1, segment[i].l, segment[i].r, get_val(1, segment[i].l - 1) - segment[i].cost);
		solve(1, segment[i].l, segment[i].r, segment[i].cost, val);
	}
	cout << dfs(1) + sum[3][n];
	return 0;
}
```

---

## 作者：pengyule (赞：0)

> 一个 $3\times n$ 的矩阵 $a$，一三行可行、第二行全是障碍物。有 $q$ 个可选操作：耗费 $w_i$ 将 $a_{2,[l_i,r_i]}$ 炸掉。从 $(1,1)$ 出发去往 $(3,n)$，经过 $(i,j)$ 获得 $a_{i,j}$ 价值，求总价值减总代价的最大值。$n,q\le 5\times 10^5$

如果从第二行的位置入手的话很难列状态，应该从操作入手看能更新哪些 $f[i]$。具体地，设 $f[i]$ 表示 $(1,1)$ 去 $(2,i)$ 的最小代价（这个很好想到），对于一个区间 $[l,r]$，有：
$$
f[i]\gets f[l-1]+pre_{2,i}-pre_{2,l-1}-w,\forall i\in [l,r]\\
f[i]\gets \min_{j\in[l,i]}(pre_{1,j}+pre_{2,i}-pre_{2,j-1}-w),\forall i\in[l,r]
$$

两个式子中的 $pre_{2,i}$ 都可以拎出来最后算。对于第一个式子，$f[i](i\ge l)$ 用 $f[l-1]$，说明应按左端点递增顺序处理操作，进而常规区间修改。对于第二个式子，相当于是这次 $[l,r]$ 内部所有人对后面的人做 $pre_{1,j}-pre_{2,j-1}$（常数，记为 $t_j$）的贡献，利用算法本质特征，在每次线段树左边回溯时带上来左边已经更新的 $t_j$ 的最大值，接下去做右边；对于线段树一个节点代表一个区间的，就先用 $\text{tag}$ 保存标记，在 `pushdown` 时做类似性质的操作。
答案就是 $\max(f[i]+pre_{3,n}-pre_{3,i-1})$。

---

