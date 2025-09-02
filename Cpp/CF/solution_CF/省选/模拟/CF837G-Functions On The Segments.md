# Functions On The Segments

## 题目描述

You have an array $ f $ of $ n $ functions.The function $ f_{i}(x) $ ( $ 1<=i<=n $ ) is characterized by parameters: $ x_{1},x_{2},y_{1},a,b,y_{2} $ and take values:

- $ y_{1} $ , if $ x<=x_{1} $ .
- $ a·x+b $ , if $ x_{1}&lt;x<=x_{2} $ .
- $ y_{2} $ , if $ x&gt;x_{2} $ .

There are $ m $ queries. Each query is determined by numbers $ l $ , $ r $ and $ x $ . For a query with number $ i $ ( $ 1<=i<=m $ ), you need to calculate the sum of all $ f_{j}(x_{i}) $ where $ l<=j<=r $ . The value of $ x_{i} $ is calculated as follows: $ x_{i}=(x+last) $ mod $ 10^{9} $ , where $ last $ is the answer to the query with number $ i-1 $ . The value of $ last $ equals $ 0 $ if $ i=1 $ .

## 样例 #1

### 输入

```
1
1 2 1 4 5 10
1
1 1 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
3
2 5 1 1 1 4
3 6 8 2 5 7
1 3 5 1 4 10
3
1 3 3
2 3 2
1 2 5
```

### 输出

```
19
17
11
```

# 题解

## 作者：wgyhm (赞：7)

# CF837G Functions On The Segments

## 题目大意

有 $n$ 个分段函数，$f_i(x)$ 有 $6$ 个参数 $x_1,x_2,y_1,a,b,y_2$。

$$f(x)=\begin{cases}y_1&x\le x_1\\ax+b&x_1<x\le x_2\\y_2&x_2<x\end{cases}$$

有 $m$ 个询问，**强制在线**，记上一次答案为 $last$，第一个询问 $last=0$，每次给出 $l,r,x$ 三个整数，$x_i=(last+x)\bmod10^9$，求 $\sum\limits_{j=l}^rf_j(x_i)$ 的值。

## 思路

首先看到区间查询，想到先预处理出 $\sum\limits_{j=1}^rf_j(x_i)$ 的值，再前缀和查询即可。

然后我们将函数变形：

$$f(x)=\begin{cases}0x+y_1&x\le x_1\\ax+b&x_1<x\le x_2\\0x+y_2&x_2<x\end{cases}$$

得到：

$$\sum\limits_{j=1}^rf_j(x_i)=\sum\limits_{j=1}^ra_j\times x_i+\sum\limits_{j=1}^rb_j$$

也就是要预处理时区间修改 $a,b$ 的值，单点查询，用动态开点线段树维护一个差分数组就好。

对于每一次差分，只会改变 $6$ 个点的大小，用主席树瞎搞一下，然后就是板子了。

注意：记得开long long，空间开满。

Code:

```cpp
#include<bits/stdc++.h>
#define rg register
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	x*=f;
}
inline void readl(long long &x){
	int f=1;x=0;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	x*=f;
}
//------------------上边是一大串快读------------------
const long long mod=1e9;
const int maxn=75005;
int head,tail;
long long k1,k2;
struct node{
	long long x,y;
	node(long long a=0,long long b=0){
		x=a;y=b;
	}
	node operator +(const node a) const{return node(x+a.x,y+a.y);}
	node operator -(const node a) const{return node(x-a.x,y-a.y);}
};
struct yyy{
	int ls,rs;
	long long sum1,sum2;
}f[30000005];
int root[maxn],cnt;
inline int Update(int l,int r,int pre){
	int rt=++cnt;f[rt]=f[pre];
	if (l==r) {f[rt].sum1+=k1;f[rt].sum2+=k2;return rt;}
	f[rt].sum1+=k1;f[rt].sum2+=k2;
	int mid=l+r>>1;
	if (head<=mid) f[rt].ls=Update(l,mid,f[rt].ls);
	else f[rt].rs=Update(mid+1,r,f[rt].rs);
	return rt;
}
inline node Query(int l,int r,int rt){
	if (head<=l&&r<=tail) return node(f[rt].sum1,f[rt].sum2);
	int mid=l+r>>1;node ans(0,0);
	if (head<=mid) ans=ans+Query(l,mid,f[rt].ls);
	if (tail>mid) ans=ans+Query(mid+1,r,f[rt].rs);
	return ans;
}
int main(){
//	freopen("1.in","r",stdin);
	rg int i,x,y,xx,yy,a,b,n,m;
	rg long long last=0,k;
	rg node ans;
	read(n);
	for (i=1;i<=n;i++){
		read(x);read(xx);read(y);read(a);read(b);read(yy);
		head=0;k1=0;k2=y;root[i]=Update(0,mod,root[i-1]);
		head=x+1;k1=a;k2=b-y;root[i]=Update(0,mod,root[i]);
		head=xx+1;k1=-a;k2=yy-b;root[i]=Update(0,mod,root[i]);
	}
	read(m);
	for (i=1;i<=m;i++){
		node ans(0,0);read(x);read(y);readl(k);k=(k+last)%mod;
		head=0;tail=k;ans=ans+Query(0,mod,root[y]);
		if (x) head=0,tail=k,ans=ans-Query(0,mod,root[x-1]);
		last=ans.x*k+ans.y;
		printf("%lld\n",last);
	}
	return 0;
}
```

## 题外话

每天一个爆零小技巧：

![](https://cdn.luogu.com.cn/upload/image_hosting/8e7dctht.png)

---

## 作者：ifffer_2137 (赞：2)

大家好我很喜欢暴力分块。

所以我使用根号算法耗时 `4187ms` 通过了本题。
### 题意
给一个分段函数序列，强制在线询问一个区间在 $x$ 处的点值之和。
### 分析
看到数据范围容易想到根号算法。

因为是强制在线，所以直接分块。散块直接暴力，考虑快速求整块在某点的函数值之和。

然后 $x$ 的范围是 $10^9$。我丢，那怎么做。块内离散化以后查询要多只二分的 log，寄飞了。

我丢，$x_1,x_2$ 范围是 $2\times10^5$，空间还是 `1000MB`，这不直接线根时空预处理所有情况吗，大于 $2\times10^5$ 的询问显然都和 $2\times10^5+1$ 一样啊。然后查询每个整块只要 $O(1)$ 了。

然后这样预处理直接枚举 $x$ 了，考虑快速求总和。首先你需要把 $x_1\le x$ 和 $x_2<x$ 的 function 全都分别拿出来，然后把 $y_1,y_2$ 求和，这不就值域上维护个前后缀和吗。

然后再考虑取一次函数的部分，就是剩下的 function。由于乘法分配律，只要求 $\sum k$ 和 $\sum b$ 就可以了。所以先求个总和，在前面值域上前后缀和的同时滚一个 $k$ 和 $b$ 的信息，减一减就行了。

然后块长取根号就做完了。时间复杂度 $\Theta(V\sqrt{n}+m\sqrt{n})$。
### 代码
注意优化 `long long` 的使用。但 `5000ms` 应该是不怎么卡常的。
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=7.5e4+5;
const int maxm=2e5+5;
const int N=2e5;
const int maxb=280;
const int V=1e9;
int n,q,B;
ll ans;
struct func{
	int lx,rx,ly,ry;
	int k,b;
	ll val(int x){
		if(x<=lx) return ly;
		else if(x<=rx) return 1ll*k*x+b;
		return ry;
	}
}a[maxn];
int col[maxn],L[maxn],R[maxn];
ll res[maxb][maxm];
int prek[maxm],preb[maxm];
ll prey[maxm];
int sufk[maxm],sufb[maxm];
ll sufy[maxm];
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();B=sqrt(n);
	for(int i=1;i<=n;i++){
		col[i]=(i-1)/B+1;
		if(!L[col[i]]) L[col[i]]=i;
		R[col[i]]=i;
	}
	for(int i=1;i<=n;i++) a[i].lx=read(),a[i].rx=read(),a[i].ly=read(),a[i].k=read(),a[i].b=read(),a[i].ry=read();
	for(int i=1;i<=col[n];i++){
		memset(prek,0,sizeof(prek));
		memset(preb,0,sizeof(preb));
		memset(prey,0,sizeof(prey));
		memset(sufk,0,sizeof(sufk));
		memset(sufb,0,sizeof(sufb));
		memset(sufy,0,sizeof(sufy));
		int sk=0,sb=0;
		for(int j=L[i];j<=R[i];j++){
			prek[a[j].rx]+=a[j].k;
			preb[a[j].rx]+=a[j].b;
			prey[a[j].rx]+=a[j].ry;
			sufk[a[j].lx]+=a[j].k;
			sufb[a[j].lx]+=a[j].b;
			sufy[a[j].lx]+=a[j].ly;
			res[i][N+1]+=a[j].ry;
			sk+=a[j].k,sb+=a[j].b;
		}
		for(int j=1;j<=N;j++) prek[j]+=prek[j-1];
		for(int j=1;j<=N;j++) preb[j]+=preb[j-1];
		for(int j=1;j<=N;j++) prey[j]+=prey[j-1];
		for(int j=N-1;j>=0;j--) sufk[j]+=sufk[j+1];
		for(int j=N-1;j>=0;j--) sufb[j]+=sufb[j+1];
		for(int j=N-1;j>=0;j--) sufy[j]+=sufy[j+1];
		for(int j=0;j<=N;j++){
			res[i][j]+=prey[j-1]+sufy[j];
			int kk=sk-prek[j-1]-sufk[j],bb=sb-preb[j-1]-sufb[j];
			res[i][j]+=1ll*kk*j+bb;
		}
	}
	q=read();
	while(q--){
		int l=read(),r=read(),x=(read()+ans)%V;ans=0;
		if(x>N) x=N+1;
		for(int i=l;i<=min(r,R[col[l]]);i++) ans+=a[i].val(x);
		if(col[l]==col[r]){
			cout<<ans<<'\n';
			continue;
		}
		for(int i=col[l]+1;i<=col[r]-1;i++) ans+=res[i][x];
		for(int i=L[col[r]];i<=r;i++) ans+=a[i].val(x);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17787282.html)**

**[洛谷](https://www.luogu.com.cn/problem/CF837G) [CF](https://codeforces.com/problemset/problem/837/G)**

> - 有 $n$ 个分段函数，第 $i$ 个函数形如：
>
> $$f_i(x)=\begin{cases}y1_i,\space \space \space \space \space \space \space \space\space \space \space \space x\le x1_i\\a_ix+b_i,\space \space \space \space x1_i<x\le x2_i\\ y2_i,\space \space \space \space \space \space \space \space\space \space \space \space x>x2_i\end{cases}$$
>
> - 有 $m$ 次询问，每次询问给出 $l,r,x$，求 $\sum\limits_{i=l}^r f_i(x)$。
>
> - $n\le 7.5\times 10^4$，$m\le 5\times 10^5$。**强制在线**。

首先，所有函数都可以表达成**一次分段函数**的**形式**（注意这里强调的是形式上相同）。

即 $f_i(x)=p_ix+q_i$，其中：

- 当 $x\le x1_i$ 时，$p_i=0,q_i=y1_i$。

- 当 $x1_i<x\le x2_i$ 时，$p_i=a_i,q_i=b_i$。

- 当 $x>x2_i$ 时，$p_i=0,q_i=y2_i$。

考虑对于一次查询，求的就是：

$$\sum_{i=l}^r f_i(x)= \sum_{i=l}^r (p_ix+q_i)=\left(\sum _{i=l}^rp_i\right)\cdot x+\sum_{i=l}^r q_i$$

$x$ 给定，只需要维护 $p_i$ 以及 $q_i$ 的区间和即可。

最大的麻烦是 $p_i$ 和 $q_i$ 在动态变化。不过我们考虑将所有分段函数分段的起点全部存到一个数组 $P$ 里面。并将其从小到大排序，设其大小为 $k$。

则对于同一条分段函数 $f_i(x)$ 来说，当自变量 $x$ 取值为 $x_1,x_2$，满足存在一个 $j\,(1\le j< k)$ 使得 $x_1,x_2\in[P_j,P_{j+1})$ 时，**$\boldsymbol{f_i(x_1)=f_i(x_2)}$**。

就是说将这些点投影到数轴上时，这些点将数轴分成若干段，若自变量 $x$ 取在相同的一段里时，则函数值相同。

很好理解，因为同一段内不存在一个分段函数的起点，对于任意函数来说不存在一个函数发生变化的地方。

因此我们对于数轴上的每一段，维护这一段对应的 $p_i,q_i$ 的区间和。由于强制在线，考虑使用可持久化线段树维护每一段的信息。

将所有变化表示成差分的形式并离线扫描线。当开启一个新段的时候，在上一段版本的基础上扫描并进行这一段的修改。由于每一段可能产生多次修改，因此主席树上的版本仍然记“第几次修改之后”，再维护一个新数组记录每一段的最终版本（即最后一次修改的版本）。

查询时，先二分找到 $x$ 在哪一段，然后在对应的版本上查询即可。

时间复杂度为 $\mathcal{O}((n+m)\log n)$，空间复杂度为 $\mathcal{O}(n\log n)$。

**[提交记录（含代码）](https://codeforces.com/contest/837/submission/229649492)**



---

## 作者：jucason_xu (赞：2)

我们考虑 $\sum_{i=l}^r{f_i(x)}$ 是个什么东西。首先这个奇怪的东西很好离线做，所以尽管题目要求强制在线，我们还是离线下来试试。

我们发现，我们可以 $x$ 坐标从 $1$ 到 $200000$ 扫过去，对于每个 $f_i$，在 $x_{i,1}+1$ 和 $x_{i,2}+1$ 两个位置打标记进行更改。这样整个扫描过程就是 $O(k+n)$ 的。然后考虑维护答案，我们发现，$y=y_1$ 和 $y=y_2$ 其实可以写成 $y=0x+y_1,y=0x+y_2$ 的形式。那么，我们的 $f_i(x)$ 就可以统一写成 $ax+b$ 的形式。则 $\sum_{i=l}^r{f_i(x)}=(\sum_{i=l}^r{a_i})x+\sum_{i=l}^r{b_i}$。

这样，我们就只需要维护 $a$ 和 $b$ 的区间和。我们分别开两个线段树维护 $a$ 和 $b$ 的区间和。每次更改，就单点修改位置 $i$ 上面的 $a_i$ 和 $b_i$。然后我们提前把所有的询问挂在自己的 $x_i$ 上，处理完当前 $x$ 上的所有操作之后，对所有的 $[l,r]$ 询问进行查询得到 $\sum_{i=l}^r{a_i}$ 和 $\sum_{i=l}^r{b_i}$。

但是现在强制在线，怎么做呢？

我们发现，只要我们存储下每个 $x$ 所对应的 $a$ 和 $b$ 序列，就可以每次快速得到答案。但是存储 $a$ 和 $b$ 显然不现实，我们就考虑可持久化线段树。我们找到原先的所有操作：单点修改、区间查询，这恰好是可以使用主席树完成的工作。又因为是静态的，我们完全可以把主席树处理出来之后，带到询问里去计算。

还有一个小小的问题，询问时的 $x$ 是可能达到 $10^9$ 的，如何做呢？我们发现 $2\cdot 10^5$ 之后的 $x$ 都已经到了第三阶段，也就是 $y=y_2$，可以直接处理其前缀和，然后 $O(1)$ 计算答案。

注意我们同一个 $x$ 上可能有很多的操作，也可能没有操作，不能把 $x$ 作为主席树的时间轴，而应当对每个 $x$ 上的所有操作执行完之后，记录当前主席树的最新版本。

如果我们记 $k$ 为 __更改__ 操作中出现的最大 $x$，那么时间复杂度就是 $O(k+(n+m)\log n)$，空间复杂度 $O(n\log n)$。

```cpp
#define rd(i,n) for(ll i=0;i<n;i++)
#define rp(i,n) for(ll i=1;i<=n;i++)
#define rep(i,a,b) for(ll i=a;i<=b;i++)
typedef long long ll;
class pst{
private:
	ll sum[10000005];
	int ls[10000005],rs[10000005],cnt,Len;
	int root[400005],Ti;
	inline void Init(int &i,int l,int r,int* a){
		i=++cnt;
		if(l==r){
			sum[i]=a[l];
			return;
		}
		int mid=l+r>>1;
		Init(ls[i],l,mid,a);
		Init(rs[i],mid+1,r,a);
		sum[i]=sum[ls[i]]+sum[rs[i]];
	}
	inline void Modify(int &i,int his,int x,int v,int l,int r){
		i=++cnt;
		if(l==r){
			sum[i]=v;
			return;
		}
		int mid=l+r>>1;
		if(x<=mid){
			rs[i]=rs[his];
			Modify(ls[i],ls[his],x,v,l,mid);
		}else{
			ls[i]=ls[his];
			Modify(rs[i],rs[his],x,v,mid+1,r);
		}
		sum[i]=sum[ls[i]]+sum[rs[i]];
	}
	inline ll Query(int i,int L,int R,int l,int r){
		if(!i)return 0;
		if(L<=l&&r<=R)return sum[i];
		int mid=l+r>>1;
		ll res=0;
		if(ls[i]&&L<=mid)res+=Query(ls[i],L,R,l,mid);
		if(rs[i]&&R>mid)res+=Query(rs[i],L,R,mid+1,r);
		return res;
	}
public:
	inline void init(int len,int* a){
		Len=len;
		Init(root[0],1,len,a);
	}
	inline void modify(int x,int v){
		int cnt=++Ti;
		Modify(root[cnt],root[cnt-1],x,v,1,Len);
	}
	inline ll query(int ti,int l,int r){
		return Query(root[ti],l,r,1,Len);
	}
	inline int curver(){
		return Ti;
	}
}ta,tb;
const int N=75005;
const int M=200000;
const int P=1000000000;
int n,m,q,l,r,x,xl[N],xr[N],yl[N],yr[N],a[N],b[N],Empty[N];
ll sum[N];
int vera[M+5],verb[M+5];
vt<int>v1[M+5],v2[M+5];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	n=in();
	rp(i,n)xl[i]=in(),xr[i]=in(),yl[i]=in(),a[i]=in(),b[i]=in(),yr[i]=in();
	rp(i,n)v1[xl[i]+1].pb(i),v2[xr[i]+1].pb(i);
	ta.init(n,Empty);tb.init(n,yl);
	rep(ti,1,M){
		for(auto j:v1[ti]){
			ta.modify(j,a[j]);
			tb.modify(j,b[j]);
		}
		for(auto j:v2[ti]){
			ta.modify(j,0);
			tb.modify(j,yr[j]);
		}
		vera[ti]=ta.curver();
		verb[ti]=tb.curver();
	}
	rp(i,n)sum[i]=sum[i-1]+yr[i];
	q=in();
	ll ans=0;
	rd(_,q){
		l=in(),r=in(),x=in();
		x=(x+ans)%P;
		if(x<=M){
			ans=ta.query(vera[x],l,r)*x+tb.query(verb[x],l,r);
		}else{
			ans=sum[r]-sum[l-1];
		}
		out(ans)('\n');
	}
	return 0;
}
//Crayan_r
```

---

## 作者：cike_bilibili (赞：0)

我看到 $n \le 75000$ 和五秒时限就去想根号了。

将函数序列分块，散块暴力算，整块的话注意到 $x_1,x_2 \le 2 \times 10^5$，直接大力预处理 $x$ 取所有值的时候的 $y_1,y_2$ 的和还有 $a,b$ 的和，分别计算即可，当然如果 $x > 2 \times 10^5$ 的话所有函数的值都是 $y_2$。

然后会 TLE，卡常的话就是这些数组是可以求块间前缀的，预处理一下能省掉枚举整块的常数，还有 $y1,y2$ 本质上是相同的，可以一起处理。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
int n;
struct func{
    int l,r,y1,a,b,y2;
}a[75005];
int st[75005],ed[75005],id[75005],cnt;
const int N=75000,B=300,V=200000;
int sa[N/B+5][V+5],sb[N/B+5][V+5];
ll sy1[N/B+5][V+5];
ll val[N/B+5];
void build(){
    for(int i=1;i<=n;i+=B){
        st[++cnt]=i,ed[cnt]=min(i+B-1,n);
        for(int j=i;j<=ed[cnt];j++)id[j]=cnt;
    }
}
void init(){
    for(int i=1;i<=cnt;i++){
        val[i]=val[i-1];
        for(int j=st[i];j<=ed[i];j++){
            sy1[i][0]+=a[j].y1,sy1[i][a[j].l+1]-=a[j].y1;
            sy1[i][a[j].r+1]+=a[j].y2;
            sa[i][a[j].l+1]+=a[j].a,sa[i][a[j].r+1]-=a[j].a;
            sb[i][a[j].l+1]+=a[j].b,sb[i][a[j].r+1]-=a[j].b;
            val[i]+=a[j].y2;
        }
        for(int j=1;j<=V;j++){
            sy1[i][j]+=sy1[i][j-1];
            sa[i][j]+=sa[i][j-1],sb[i][j]+=sb[i][j-1];
        }
        for(int j=0;j<=V;j++){
            sy1[i][j]+=sy1[i-1][j];
            sa[i][j]+=sa[i-1][j],sb[i][j]+=sb[i-1][j];
        }
    }
}
ll f(int id,int x){
    if(x<=a[id].l)return a[id].y1;
    else if(x<=a[id].r)return 1ll*a[id].a*x+a[id].b;
    else return a[id].y2;
}
ll ask(int l,int r,int x){
    ll ans=0;
    if(id[l]==id[r]){
        for(int i=l;i<=r;i++)ans+=f(i,x);
        return ans;
    }
    for(int i=l;i<=ed[id[l]];i++)ans+=f(i,x);
    for(int i=r;i>=st[id[r]];i--)ans+=f(i,x);
    if(x>V)ans+=val[id[r]-1]-val[id[l]];
    else ans+=sy1[id[r]-1][x]-sy1[id[l]][x]+1ll*(sa[id[r]-1][x]-sa[id[l]][x])*x+(sb[id[r]-1][x]-sb[id[l]][x]);
    return ans;
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i].l=read(),a[i].r=read(),a[i].y1=read(),a[i].a=read(),a[i].b=read(),a[i].y2=read();
    }
    build();
    init();
    ll lst=0;
    int Q=read();
    while(Q--){
        int l=read(),r=read(),x=(read()+lst)%1000000000;
        cout<<(lst=ask(l,r,x))<<'\n';
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

无修改，考虑预处理 $\sum_{i=1}^jf_i(x)$，询问时差分。

考虑使用主席树，把常数项和系数分开建两棵主席树。差分，在若干个点上更新。对于常数项，询问的时候直接查询前缀和。对于系数，查询前缀和后乘上一个 $x$。注意这里指的是主席树内查询前缀和，用 $rt_r$ 位置的这个值减去 $rt_{l-1}$ 位置的即可。

总复杂度是 $O((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int rt1[75005],rt2[75005];
struct sgt{
	int f[10000005],lp[10000005],rp[10000005],cnt;
	int add(int now,int l,int r,int ql,int qr,int cg){
		int i=++cnt;
		if(l==r){
			f[i]=f[now]+cg;
			return i;
		}
		lp[i]=lp[now],rp[i]=rp[now];
		if(ql<=mid) lp[i]=add(lp[now],l,mid,ql,qr,cg);
		if(qr>mid) rp[i]=add(rp[now],mid+1,r,ql,qr,cg);
		f[i]=f[lp[i]]+f[rp[i]];
		return i;
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(lp[i],l,mid,ql,qr);
		if(ql>mid) return qry(rp[i],mid+1,r,ql,qr);
		return qry(lp[i],l,mid,ql,qr)+qry(rp[i],mid+1,r,ql,qr);
	}
}tree1,tree2;
int x1[75005],x2[75005],y1[75005],a[75005],b[75005],y2[75005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x1[i]>>x2[i]>>y1[i]>>a[i]>>b[i]>>y2[i];
		rt1[i]=tree1.add(rt1[i-1],0,200001,0,0,y1[i]);
		rt1[i]=tree1.add(rt1[i],0,200001,x1[i]+1,x1[i]+1,b[i]-y1[i]);
		rt1[i]=tree1.add(rt1[i],0,200001,x2[i]+1,x2[i]+1,y2[i]-b[i]);
		rt2[i]=tree2.add(rt2[i-1],0,200001,x1[i]+1,x1[i]+1,a[i]);
		rt2[i]=tree2.add(rt2[i],0,200001,x2[i]+1,x2[i]+1,-a[i]);
	}
	int q; cin>>q;
	int ans=0;
	while(q--){
		int l,r,x; cin>>l>>r>>x;
		x=(x+ans)%((int)1e9);
		int fx=min(x,200001ll);
		ans=(tree1.qry(rt1[r],0,200001,0,fx)-tree1.qry(rt1[l-1],0,200001,0,fx))+(tree2.qry(rt2[r],0,200001,0,fx)-tree2.qry(rt2[l-1],0,200001,0,fx))*x;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

差分之后一眼可持久化区修区查线段树，然而貌似不好写的样子？

所以我们考虑在线段树上打永久化标记，具体这样做：从根节点往下跳是正常维护子段和，但是碰到可以返回的节点时，额外打一个标记表示这个子树内每个节点都加了一个值。这样查询时不用下传标记，而是直接记录这样的标记和，再乘上区间大小即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 75010;
long long n, m, x[N][3], y[N][3], a[N], b[N], lst;
int rt[N * 8], idx, id[N * 8], tot;
struct SGT
{
	int ls, rs;
	long long sum, tag;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define sum(x) tree[x].sum
	#define tag(x) tree[x].tag
}tree[N * 487];
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
}
inline void insert(int his, int &now, int l, int r, int L, int R, int num)
{
	now = ++idx;
	ls(now) = ls(his); rs(now) = rs(his);
	sum(now) = sum(his); tag(now) = tag(his);
	if(L <= l && r <= R) {tag(now) += num; return ;}
	sum(now) += (min(R, r) - max(L, l) + 1) * num;
	int mid = l + r >> 1;
	if(L <= mid) insert(ls(his), ls(now), l, mid, L, R, num);
	if(mid < R) insert(rs(his), rs(now), mid + 1, r, L, R, num);
}
inline long long ask(int now, int l, int r, int L, int R, long long sig)
{
	sig += tag(now);
	if(L <= l && r <= R) {return sig * (r - l + 1) + sum(now);}
	int mid = l + r >> 1; long long ans = 0;
	if(L <= mid) ans += ask(ls(now), l, mid, L, R, sig);
	if(mid < R) ans += ask(rs(now), mid + 1, r, L, R, sig);
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	build(rt[tot], 0, 200002);
	for(int i = 1; i <= n; ++i)
	{
		cin >> x[i][1] >> x[i][2] >> y[i][1] >> a[i] >> b[i] >> y[i][2];
		++tot;
		insert(rt[tot - 1], rt[tot], 0, 200002, 0, 0, y[i][1]);
		++tot;
		insert(rt[tot - 1], rt[tot], 0, 200002, x[i][1] + 1, x[i][1] + 1, -y[i][1] + b[i] + a[i] * x[i][1]);
		++tot;
		insert(rt[tot - 1], rt[tot], 0, 200002, x[i][1] + 1, x[i][2], a[i]);
		++tot;
		insert(rt[tot - 1], rt[tot], 0, 200002, x[i][2] + 1, x[i][2] + 1, y[i][2] - b[i] - a[i] * x[i][2]);
		id[i] = tot;
	}
	cin >> m;
	for(int i = 1; i <= m; ++i)
	{
		long long l, r, x; cin >> l >> r >> x;
		x = (x + lst) % 1000000000;
		lst = (ask(rt[id[r]], 0, 200002, 0, (int)x, 0) - ask(rt[id[l - 1]], 0, 200002, 0, (int)x, 0));
		cout << lst << '\n';
	}
	return 0;
}
```

---

## 作者：Kappa6174 (赞：0)

**观前提示：本题解可能需要一定卡常。**

### Statement:

给定 $n$ 个分段函数 $f_i(x)$ 为：
$$f_i(x)=\begin{cases}y_1,&x\le x_1\\ax+b,&x_1<x\le x_2\\y_2,&x>x_2\end{cases}$$
其中 $x_1,x_2,y_1,y_2,a,b$ 为给定的参数。

$m$ 次询问，每次询问给出 $l,r,x$，求 $\sum\limits_{i=l}^{r}f_i(x)$，**强制在线**。

$n\leq 7.5\times 10^4$，$x_1,x_2\leq 2\times 10^5$，$x,y_1,y_2\leq 10^9$，$a,b\leq 10^4$，$m\leq 5\times 10^5$，$1\leq l\leq r\leq n$。 

### Solution:
树套树。

先考虑这个分段函数，容易发现每一段都能表示成 $kx+b$ 的形式，如下：
$$f_i(x)=\begin{cases}0\times x+y_1,&x\le x_1\\a\times x+b,&x_1<x\le x_2\\0\times x+y_2,&x>x_2\end{cases}$$

答案具有可差分性，所以我们只用考虑 $l=1$ 的情况，容易发现：
$$\sum\limits_{i=1}^{r}{f_i(x)}=\sum\limits_{i=1}^{r}{(a_ix+b_i)}=\sum\limits_{i=1}^{r}{a_i\times x}+\sum\limits_{i=1}^{r}b_i$$

内层预处理分段函数需要区间加，询问需要单点查 $\sum\limits{a}$ 和 $\sum\limits{b}$，线段树可以解决。外层要维护前缀线段树，因此需要套一个树状数组维护。

时间复杂度 $O((n+m)\log n\log X)$，空间复杂度 $O(n\log n\log X)$，其中 $X$ 为 $x_1,x_2$ 值域。

喜提最劣解。

[Code](https://www.luogu.com.cn/paste/5e1krt9c)。



---

