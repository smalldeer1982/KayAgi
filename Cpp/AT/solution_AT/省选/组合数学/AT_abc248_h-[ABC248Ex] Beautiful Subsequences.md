# [ABC248Ex] Beautiful Subsequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_h

$ (1,\ldots,N) $ を並び替えて得られる長さ $ N $ の順列 $ P=(P_1,\ldots,P_N) $、及び整数 $ K $ が与えられます。

以下の条件を全て満たす整数組 $ (L,R) $ の個数を求めてください。

- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $
- $ \mathrm{max}(P_L,\ldots,P_R)\ -\ \mathrm{min}(P_L,\ldots,P_R)\ \leq\ R\ -\ L\ +\ K $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1.4\times\ 10^5 $
- $ P $ は $ (1,\ldots,N) $ を並び替えて得られる順列
- $ 0\ \leq\ K\ \leq\ 3 $
- 入力は全て整数

### Sample Explanation 1

条件を満たす組 $ (L,R) $ は以下の $ 9 $ 個です。 - $ (1,1) $ - $ (1,3) $ - $ (1,4) $ - $ (2,2) $ - $ (2,3) $ - $ (2,4) $ - $ (3,3) $ - $ (3,4) $ - $ (4,4) $ $ (L,R)\ =\ (1,2) $ は $ \mathrm{max}(A_1,A_2)\ -\mathrm{min}(A_1,A_2)\ =\ 4-1\ =\ 3 $ 、$ R-L+K=2-1+1\ =\ 2 $ となるので、条件を満たしません。

## 样例 #1

### 输入

```
4 1
1 4 2 3```

### 输出

```
9```

## 样例 #2

### 输入

```
2 0
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10 3
3 7 10 1 9 5 4 8 6 2```

### 输出

```
37```

# 题解

## 作者：syzf2222 (赞：11)

这是个简单题啊。

考虑到 $\max(p_l,...,p_r)-\min(p_{l},...,p_r)-r+l\geqslant 0$，所以只有当这个值为 $0\sim k$ 时才满足条件，这只有 $4$ 个值。

于是我们考虑扫描线，对于每个 $r$，维护每个左区间的这个值，并维护区间前 $4$ 小值和出现次数。考虑单调栈，这个值的维护就可以转化为若干次区间加了。

时间复杂度 $O(n\log n)$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define ll long long
ll ans;
struct node{
	int Mn[5],C[5],laz;
	node(){
		Mn[1]=Mn[2]=Mn[3]=Mn[4]=inf;
		laz=C[1]=C[2]=C[3]=C[4]=0;
	}
}tr[maxn<<2],ept;
int Mn[10],C[10];
inline node merge(node x,node y){
	int top=0;node z;
	for(int i=1;i<=4;i++)
		Mn[++top]=x.Mn[i],Mn[++top]=y.Mn[i];
	sort(Mn+1,Mn+1+top);
	top=unique(Mn+1,Mn+1+top)-Mn-1;
	for(int i=1;i<=top;i++)C[i]=0;
	for(int i=1;i<=4;i++){
		C[lower_bound(Mn+1,Mn+1+top,x.Mn[i])-Mn]+=x.C[i];
		C[lower_bound(Mn+1,Mn+1+top,y.Mn[i])-Mn]+=y.C[i];
	}for(int i=1;i<=4;i++)z.Mn[i]=Mn[i],z.C[i]=C[i];
	return z;
}
int n,m,k,P[maxn];
int S1[maxn],t1,S2[maxn],t2;
inline void pushup(int h,int z){
	tr[h].laz+=z;
	for(int i=1;i<=4;i++)tr[h].Mn[i]+=z;
}
inline void pushdown(int h){
	if(!tr[h].laz)return;
	pushup(h<<1,tr[h].laz);
	pushup(h<<1|1,tr[h].laz);
	tr[h].laz=0;
}
inline void Modify(int h,int l,int r,int x){
	if(l==r){tr[h].Mn[1]=0,tr[h].C[1]=1;return;}
	int mid=(l+r)>>1;pushdown(h);
	if(mid>=x)Modify(h<<1,l,mid,x);
	else Modify(h<<1|1,mid+1,r,x);
	tr[h]=merge(tr[h<<1],tr[h<<1|1]);
}
inline void modify(int h,int l,int r,int x,int y,int z){
	if(l>y||r<x)return;
	if(l>=x&&r<=y)return void(pushup(h,z));
	int mid=(l+r)>>1;pushdown(h);
	modify(h<<1,l,mid,x,y,z);
	modify(h<<1|1,mid+1,r,x,y,z);
	tr[h]=merge(tr[h<<1],tr[h<<1|1]);
}
inline node query(int h,int l,int r,int x,int y){
	if(l>y||r<x)return ept;
	if(l>=x&&r<=y)return tr[h];
	int mid=(l+r)>>1;pushdown(h);
	return merge(query(h<<1,l,mid,x,y),query(h<<1|1,mid+1,r,x,y));
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)P[i]=read();
	for(int i=1;i<=n;i++){
		while(t1&&P[S1[t1]]>P[i])
			modify(1,1,n,S1[t1-1]+1,S1[t1],P[S1[t1]]),--t1;
		S1[++t1]=i;modify(1,1,n,S1[t1-1]+1,i,-P[i]);
		while(t2&&P[S2[t2]]<P[i])
			modify(1,1,n,S2[t2-1]+1,S2[t2],-P[S2[t2]]),--t2;
		S2[++t2]=i;modify(1,1,n,S2[t2-1]+1,i,P[i]);
		modify(1,1,n,1,i,-1);Modify(1,1,n,i);
		node res=query(1,1,n,1,i);
		for(int j=1;j<=4;j++)
			if(res.Mn[j]<=k)ans+=res.C[j];
	}printf("%lld\n",ans);
	return 0;
}
```

深深地感动自己的弱小。

---

## 作者：lzyqwq (赞：10)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17788161.html)**

**[洛谷](https://www.luogu.com.cn/problem/AT_abc248_h) [AT](https://atcoder.jp/contests/abc248/tasks/abc248_h)**

> - 给定长度为 $n$ 的排列 $a_1\sim a_n$ 以及整数 $k$，求有多少个区间 $[l,r]$ 满足 ：
>
> $$\max\limits_{i=l}^r a_i-\min\limits_{i=l}^r a_i \le r-l+k $$
>
> - $n \le 1.4\times 10^5$，$k\le 3$。

你看到这个 $k\le 3$ 以为复杂度多少和 $k$ 有点关系，但是我想告诉你：

> 两只 $\log$ 跑得快，序列分治真可爱。
>
> 特殊性质不依赖，$n,k$ 同阶照样快。

考虑分治，设当前分治区间为 $[L,R]$，中点 $mid=\left\lfloor\dfrac{L+R}{2}\right\rfloor$。考虑如何统计跨过中点的贡献。

考虑 $mid\rightarrow L$ 扫描左端点 $i$，统计怎样的右端点 $j\,(j\in(mid,R])$ 合法。

预处理数组 $pmx_x=\max\limits_{u=mid+1}^x a_u,pmn_x=\min\limits_{u=mid+1}^x a_u$。在扫描的过程中同时记录 $mx=\max\limits_{u=i}^{mid}a_u,mn=\min\limits_{u=i}^{mid}a_u$。

维护两个指针 $jmx,jmn$，使得：

- 当 $j\in (mid,jmx)$ 时，$\max\limits_{u=i}^j a_u = mx$；当 $j\in [jmx,R]$ 时，$\max\limits_{u=i}^j a_u = pmx_j$。

- 当 $j\in (mid,jmn)$ 时，$\min\limits_{u=i}^j a_u = mn$；当 $j\in [jmn,R]$ 时，$\min\limits_{u=i}^j a_u = pmn_j$。

**不难发现当 $\boldsymbol i$ 单调递减时，$\boldsymbol{jmx,jmn}$ 单调不降。**

分两大种、六小种情况讨论（加粗的是结论）：

- 当 $jmn\le jmx$ 时：

    - 当 $j\in(mid,jmn)$ 时，满足的条件等价于 $mx-mn\le j-i+k$，变形成 $j\ge mx-mn + i - k$。
    
      **即统计有多少 $\boldsymbol j$ 满足 $\boldsymbol{j\in (mid,jmn)}$ 且 $\boldsymbol{j\ge mx-mn+i-k}$**。
    
    - 当 $j\in [jmn,jmx)$ 时，满足的条件等价于 $mx-pmn_j\le j-i+k$，变形成 $j+pmn_j\ge i+mx-k$。
    
      **即统计有多少 $\boldsymbol{j}$ 满足 $\boldsymbol{j\in[jmn,jmx)}$ 且 $\boldsymbol{j+pmn_j\ge i+mx-k}$**。
    
    - 当 $j\in [jmx,R]$ 时，满足的条件等价于 $pmx_j-pmn_j\le j-i+k$，变形成 $j-pmx_j+pmn_j\ge i-k$。
    
      **即统计有多少 $\boldsymbol{j}$ 满足 $\boldsymbol{j\in[jmx,R]}$ 且 $\boldsymbol{j-pmx_j+pmn_j\ge i-k}$**。
      
- 当 $jmn>jmx$ 时：

    - 当 $j\in(mid,jmx)$ 时，满足的条件等价于 $mx-mn\le j-i+k$，变形成 $j\ge mx-mn + i - k$。
    
      **即统计有多少 $\boldsymbol j$ 满足 $\boldsymbol{j\in (mid,jmx)}$ 且 $\boldsymbol{j\ge mx-mn+i-k}$**。
      
    - 当 $j\in[jmx,jmn)$ 时，满足的条件等价于 $pmx_j-mn\le j-i+k$，变形成 $j-pmx_j\ge i-mn-k$。
    
      **即统计有多少 $\boldsymbol j$ 满足 $\boldsymbol{j\in [jmx,jmn)}$ 且 $\boldsymbol{j-pmx_j\ge i-mn-k}$**。
      
    - 当 $j\in [jmn,R]$ 时，满足的条件等价于 $pmx_j-pmn_j\le j-i+k$，变形成 $j-pmx_j+pmn_j\ge i-k$。
    
      **即统计有多少 $\boldsymbol{j}$ 满足 $\boldsymbol{j\in[jmn,R]}$ 且 $\boldsymbol{j-pmx_j+pmn_j\ge i-k}$**。
      
我们发现六种情况本质上是四类统计，每一类统计都是二维数点。

具体地，建立四棵主席树 $t1,t2,t3,t4$，分别对于每个前缀 $(mid,p]\,(p\in(mid,R])$ 版本，在节点 $[l,r]$ 内维护这个前缀中有多少个 $j,j+pmn_j,j-pmx_j,j-pmx_j+pmn_j$ 的值在 $[l,r]$ 这个范围内。

统计的时候，先看是哪一大类，再对于三种小类，运用结论得到要统计的**权值**区间，并将 $j$ 所在的范围拆成两个前缀版本相减的形式去做区间求和即可。

边界：当 $L=R$ 时，返回 $1$。

时间复杂度为 $\mathcal{O}(n\log^2 n)$，空间复杂度为 $\mathcal{O}(n\log n)$。据说二维数点的时候有更高明的桶做法，但是我太弱了不会。

**[提交记录（含代码）](https://atcoder.jp/contests/abc248/submissions/46924548)**

---

## 作者：云浅知处 (赞：7)

提供一个 $O(N\log ^2N)$ 的做法，不依赖于 $0\le K\le 3$ 这一限制。

考虑分治，对于「$[l,r]$ 有多少个子区间符合条件」这一问题，取 $m=\lfloor\frac{l+r}{2}\rfloor$，算出跨过 $m$ 的区间个数，把被 $[l,m],[m+1,r]$ 包含的区间看成子问题分治下去。

设 $a_i,b_i,c_i,d_i$ 表示左右两侧距离为 $i$ 的最大值与最小值，那么条件合法当且仅当
$$
\max(a_i,c_j)-\min(b_i,d_j)\le i+j+K-1
$$

枚举 $i$，钦定 $a_i\ge c_j$ 即 $\max(a_i,c_j)=a_i$，分两种情况讨论：

- 若 $b_i\le d_j$，则要求 $a_i-b_i-i-K+1\le j$
- 若 $b_i>d_j$，则要求 $a_i-i-K+1\le j+d_j$

**注意到 $a,c$ 均单调递增，$b,d$ 均单调递减**，因此 $a_i,b_i$ 那两维的约束都可以表示成「$j$ 在某个区间内」这样的约束。这样就只有两维数点了，可以做到 $O(N\log N)$。总复杂度 $O(N\log ^2N)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}

const int N=2e5+5;

int n,K,p[N];
vector<int>A,B,C,D;
vector<vector<int> >Add,Del;

struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i))c[i]+=k;}
	int sum(int x,int res=0){for(int i=x;i;i-=lowbit(i))res+=c[i];return res;}
}T;

#define ll long long

struct Lsh{
	vector<int>lsh;
	void clr(){lsh.clear();}
	void ins(int x){lsh.emplace_back(x);}
	void work(){
		sort(lsh.begin(),lsh.end());
		lsh.resize(unique(lsh.begin(),lsh.end())-lsh.begin());
	}
	int getv(int x){
		return lower_bound(lsh.begin(),lsh.end(),x)-lsh.begin()+1;
	}
}Yoimiya;

ll calc(){
	Add.clear(),Del.clear(),Yoimiya.clr();
	Add.resize(C.size()),Del.resize(D.size());
	
	ll res=0;
	int L=A.size()-1,R=C.size()-1;
	for(int i=1;i<=L;i++){
		int p=upper_bound(C.begin(),C.end(),A[i])-C.begin()-1;
		int q=0,nl=1,nr=R;
		while(nl<=nr){
			int mid=(nl+nr)>>1;
			if(D[mid]>=B[i])q=mid,nl=mid+1;
			else nr=mid-1;
		}
		
		res+=max(0ll,min(p,q)-max(A[i]-B[i]-i-K+1,1ll)+1),q++;
		if(q<=p){
			int val=-(A[i]-i-K+1);
			Yoimiya.ins(val);
			Del[q-1].emplace_back(val),Add[p].emplace_back(val);
		}
	}
	for(int i=1;i<=R;i++)Yoimiya.ins(-(i+D[i]));
	Yoimiya.work();
	for(int i=1;i<=R;i++){
		int w=Yoimiya.getv(-(i+D[i]));T.add(w,1);
		for(int x:Add[i])res+=T.sum(Yoimiya.getv(x));
		for(int x:Del[i])res-=T.sum(Yoimiya.getv(x));
	}
	for(int i=1;i<=R;i++)T.add(Yoimiya.getv(-(i+D[i])),-1);
	
	return res;
}

ll ans=0;
void solve(int l,int r){
	if(l==r){ans++;return ;}
	int mid=(l+r)>>1;
	A.resize(mid-l+2),B.resize(mid-l+2),C.resize(r-mid+1),D.resize(r-mid+1);
	A[0]=C[0]=0,B[0]=D[0]=n+1;
	for(int i=mid,mx=0,mn=n+1;i>=l;i--)mx=max(mx,p[i]),mn=min(mn,p[i]),A[mid-i+1]=mx,B[mid-i+1]=mn;
	for(int i=mid+1,mx=0,mn=n+1;i<=r;i++)mx=max(mx,p[i]),mn=min(mn,p[i]),C[i-mid]=mx,D[i-mid]=mn;
	ans+=calc(),swap(A,C),swap(B,D),ans+=calc();
	solve(l,mid),solve(mid+1,r);
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read(),K=read();
	for(int i=1;i<=n;i++)p[i]=read();
	solve(1,n);
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：harmis_yz (赞：3)

这么爽。 

## 分析

拿到这种题的时候相信你已经秒了，因为这题纯套路。

式子的 $r-l$ 不好看，换成区间长度，即：$\max\limits_{i=l}^{r} P_i - \min\limits_{i=l}^{r} P_i -(r-l+1) \le k-1$（虽然做完之后会发现它没什么用，但是曼波喜欢，别喷曼波 pwp）。

考虑序列上分治。定义 $f(L,R)$ 表示区间 $[L,R]$ 的答案，则 $f(L,R)=f(L,mid)+f(mid+1,R)+w(L,R)$，其中 $w(L,R)$ 表示跨 $mid$ 的答案。

难点在 $w(L,R)$ 怎么算。对于一个 $l|L \le l \le mid$，找到最大的 $j$ 与 $k$，使得：$\min\limits_{i=l}^{mid} P_i = \min\limits_{i=l}^{j} P_i \land \max\limits_{i=l}^{mid} P_i = \max\limits_{i=l}^{k} P_i$。得到 $3$ 种情况：

1. $mid+1 \le r \le \min(j,k)$，此时 $min$ 与 $max$ 的值确定。

2. $\min(j,k) < r \le \max(j,k)$，此时 $min$ 或 $max$ 的值确定。

3. $\max(j,k) < r \le R$，此时 $min$ 与 $max$ 的值确定。

对于第 $1$ 种情况，有：

$$max - min-(r-l+1) \le k\\
max-min+l-1-k \le r
$$
所以任意一个 $[\max(mid+1,max-min+l-1-k),\min(j,k)]$ 中的 $r$ 都满足条件。

对于第 $2$ 种情况，分类讨论一下。拿 $j\le k$ 的情况举例，此时 $max$ 一定。令 $a_i=\min\limits_{j=mid+1}^{i} P_j,b_i =\max\limits_{j=mid+1}^{i} P_j$。有：

$$
max-a_r+l-1-k \le r\\
max+l-1-k \le r+a_r
$$
可以用任意方式维护，这里我使用的是离线后树状数组。$j >k$ 的情况同理，这里不再赘述。

对于第 $3$ 种情况，有：

$$
b_r-a_r+l-1-k \le r\\
l-1-k \le r+a_r-b_r
$$
也可以用任意方式维护。

复杂度为 $O(n \log n) \sim O(n \log^2 n)$。我的做法是 $O(n \log^2 n)$ 的。

## 代码

```cpp
il void work(int l,int r){
	if(l==r){
		ans+=(a[l]-a[l]-(r-l+1)<=K);
		return ;
	}
	int mid=l+r>>1;
	work(l,mid),work(mid+1,r);
	for(re int i=mid;i<=r+1;++i){
		v1[i].clear(),
		v2[i].clear(),
		v3[i].clear();
	}
	Max[mid+1]=Min[mid+1]=a[mid+1];
	for(re int i=mid+2;i<=r;++i){
		Max[i]=max(Max[i-1],a[i]),
		Min[i]=min(Min[i-1],a[i]);
	}
	int mx=a[mid],mi=a[mid];
	for(re int L=mid,j=mid,k=mid;L>=l;--L){
		mi=min(mi,a[L]),mx=max(mx,a[L]);
		while(j+1<=r&&Min[j+1]>=mi) ++j;
		while(k+1<=r&&Max[k+1]<=mx) ++k;
		ans+=max(0ll,min(j,k)-max(mx-mi+L-1-K,mid+1)+1);//1
		if(j<=k){//2.1
			int s=+mx+L-1-K;
			v1[min(j,k)].push_back({s,-1});
			v1[max(j,k)].push_back({s, 1});
		}
		else{//2.2
			int s=-mi+L-1-K;
			v2[min(j,k)].push_back({s,-1});
			v2[max(j,k)].push_back({s, 1});
		}
		int s_=L-1-K;
		v3[max(j,k)+1].push_back(s_);//3
	}
	
	for(re int R=mid+1;R<=r;++R){//2.1
		add(Min[R]+R,1);
		for(auto x:v1[R]) ans+=x.y*query(x.x);
	}
	for(re int R=mid+1;R<=r;++R) add(Min[R]+R,-1);
	
	for(re int R=mid+1;R<=r;++R){//2.2
		add(R-Max[R],1);
		for(auto x:v2[R]) ans+=x.y*query(x.x);
	}
	for(re int R=mid+1;R<=r;++R) add(R-Max[R],-1);
	
	for(re int R=r;R>=mid+1;--R){//3
		add(R+Min[R]-Max[R],1);
		for(auto x:v3[R]) ans+=query(x);
	}
	for(re int R=r;R>=mid+1;--R) add(R+Min[R]-Max[R],-1);
	return ;
}
```

---

## 作者：Cx114514 (赞：2)

### 题目链接：[[ABC248Ex] Beautiful Subsequences](https://www.luogu.com.cn/problem/solution/AT_abc248_h)

套路地，将一段区间 $\left[l,r\right]$ 转化为二维平面上的一个点 $\left(l,r\right)$。

令二维平面上的一点的权值表示该区间的极差。

不难发现，所有最小或最大值相同的区间在二维平面上构成一个矩形（左端点与右端点均在一段连续区间内，具体可以用单调栈维护）。这样，我们就可以求得每个点的极差（最大值 $-$ 最小值）。

此问题可以用扫描线解决：

记极差为 $t$。

用一根扫描线从左向右扫这个二维平面，对于每个点，我们需要维护 $t-r+l$，使其小于 $k$。因为 $0\le k \le 3$，所以我们开线段树维护区间前 $k+1$ 小的值及其数量。这里有个细节：为了考虑 $l$ 和 $r$ 对其造成的贡献，我们线段树的初始值可以赋为 $-1,-2,\cdots,-n$，在每次扫描线右移时整体 $+1$。对于一个矩形，在左右两侧进行区间加操作即可。

时间复杂度为 $O\left(nk\log n\log k\right)$，其中 $O\left(k\log k\right)$ 是线段树 push_up 的复杂度。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[15];

void write(int x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

int n, k, ans, a[140005], minl[140005], maxl[140005], minr[140005], maxr[140005], tag[600005];

stack < int > s;

struct node
{
	int min1, min2, min3, min4, cnt1, cnt2, cnt3, cnt4;
} tree[600005];

struct node2
{
	int k, l, r, x;
} eve[600005];

struct node3
{
	int val, cnt; 
} b[15];

bool cmp(node2 q, node2 p)
{
	return q.k < p.k;
}

bool cmp2(node3 q, node3 p)
{
	return q.val < p.val;
}

void build(int rt, int l, int r)
{
	if (l == r) tree[rt] = {-l, 1145141919810, 1145141919810, 1145141919810, 1, 0, 0, 0};
	else
	{
		int mid = (l + r) / 2;
		build(rt * 2, l, mid);
		build(rt * 2 + 1, mid + 1, r);
		node t = tree[rt * 2];
		b[1] = {t.min1, t.cnt1};	
		b[2] = {t.min2, t.cnt2};
		b[3] = {t.min3, t.cnt3};
		b[4] = {t.min4, t.cnt4};
		t = tree[rt * 2 + 1];
		b[5] = {t.min1, t.cnt1};
		b[6] = {t.min2, t.cnt2};
		b[7] = {t.min3, t.cnt3};
		b[8] = {t.min4, t.cnt4};
		sort(b + 1, b + 9, cmp2);
		for (int i = 1; i < 8; i++)
			if (b[i].val == b[i + 1].val)
			{
				b[i].cnt += b[i + 1].cnt;
				b[i + 1].val = 1145141919810;
				b[i + 1].cnt = 0;
			} 
		sort(b + 1, b + 9, cmp2);
		tree[rt] = {b[1].val, b[2].val, b[3].val, b[4].val, b[1].cnt, b[2].cnt, b[3].cnt, b[4].cnt};
	}
}

void update(int rt, int l, int r, int tl, int tr, int x)
{
	if (tr < tl) return;
	if (tl <= l && r <= tr)
	{
		tree[rt].min1 += x;
		tree[rt].min2 += x;
		tree[rt].min3 += x;
		tree[rt].min4 += x;
		tag[rt] += x;
	}
	else
	{
		int mid = (l + r) / 2;
		if (tag[rt] != 0)
		{
			tree[rt * 2].min1 += tag[rt];
			tree[rt * 2].min2 += tag[rt];
			tree[rt * 2].min3 += tag[rt];
			tree[rt * 2].min4 += tag[rt];
			tag[rt * 2] += tag[rt];
			tree[rt * 2 + 1].min1 += tag[rt];
			tree[rt * 2 + 1].min2 += tag[rt];
			tree[rt * 2 + 1].min3 += tag[rt];
			tree[rt * 2 + 1].min4 += tag[rt];
			tag[rt * 2 + 1] += tag[rt];
			tag[rt] = 0;
		}
		if (tl <= mid) update(rt * 2, l, mid, tl, tr, x);
		if (tr > mid) update(rt * 2 + 1, mid + 1, r, tl, tr, x);
		node t = tree[rt * 2];
		b[1] = {t.min1, t.cnt1};	
		b[2] = {t.min2, t.cnt2};
		b[3] = {t.min3, t.cnt3};
		b[4] = {t.min4, t.cnt4};
		t = tree[rt * 2 + 1];
		b[5] = {t.min1, t.cnt1};
		b[6] = {t.min2, t.cnt2};
		b[7] = {t.min3, t.cnt3};
		b[8] = {t.min4, t.cnt4};
		sort(b + 1, b + 9, cmp2);
		for (int i = 1; i < 8; i++)
			if (b[i].val == b[i + 1].val)
			{
				b[i].cnt += b[i + 1].cnt;
				b[i + 1].val = 1145141919810;
				b[i + 1].cnt = 0;
			} 
		sort(b + 1, b + 9, cmp2);
		tree[rt] = {b[1].val, b[2].val, b[3].val, b[4].val, b[1].cnt, b[2].cnt, b[3].cnt, b[4].cnt};
	}
}

signed main()
{
	n = read(), k = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	s.push(0);
	for (int i  = 1; i <= n; i++)
	{
		while (a[s.top()] > a[i]) s.pop();
		minl[i] = s.top();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	s.push(n + 1);
	for (int i = n; i >= 1; i--)
	{
		while (a[s.top()] > a[i]) s.pop();
		minr[i] = s.top();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	a[0] = n + 1;
	s.push(0);
	for (int i = 1; i <= n; i++)
	{
		while (a[s.top()] < a[i]) s.pop();
		maxl[i] = s.top();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	a[n + 1] = n + 1;
	s.push(n + 1);
	for (int i = n; i >= 1; i--)
	{
		while (a[s.top()] < a[i]) s.pop();
		maxr[i] = s.top();
		s.push(i);
	}
	for (int i = 1; i <= n; i++)
	{
		eve[4 * i - 3] = {minl[i] + 1, i, minr[i] - 1, -a[i]};
		eve[4 * i - 2] = {i + 1, i, minr[i] - 1, a[i]};
		eve[4 * i - 1] = {maxl[i] + 1, i, maxr[i] - 1, a[i]};
		eve[4 * i] = {i + 1, i, maxr[i] - 1, -a[i]}; 
	}
	sort(eve + 1, eve + 4 * n + 1, cmp);
	build(1, 1, n);
	int now = 0;
	for (int i = 1; i <= n; i++)
	{
		update(1, 1, n, 1, n, 1);
		update(1, 1, n, 1, i - 1, 1145141919);
		while (now < 4 * n && eve[now + 1].k <= i)
		{
			now++;
			update(1, 1, n, eve[now].l, eve[now].r, eve[now].x);
		}
		if (tree[1].min1 <= k) ans += tree[1].cnt1;
		if (tree[1].min2 <= k) ans += tree[1].cnt2;
		if (tree[1].min3 <= k) ans += tree[1].cnt3;
		if (tree[1].min4 <= k) ans += tree[1].cnt4;
	}
	write(ans);
	putchar('\n');
    return 0;
}
```

---

## 作者：_liuyi_ (赞：2)

一个与 $k$ 无关的做法。

考虑分治，不跨过分治中心的区间的贡献直接递归统计即可，难点主要在跨过分治中心的区间的贡献。

$\max$ 和 $\min$ 在计数时比较难处理，不妨钦定它们分别在左半区间还是在右半区间，分别计算每种情况的贡献，因为这是排列所以是不重不漏的。

1. $\max$ 和 $\min$ 在左半区间。枚举区间的左端点，此时右端点是单调不降的。直接双指针维护即可。

2. $\max$ 和 $\min$ 在右半区间。和第一种情况是本质相同的。

3. $\max$ 在左半区间，$\min$ 在右半区间。同样枚举区间的左端点，考虑右端点的取值范围，不难发现右端点的取值范围是一个区间。因为 $\max$ 限制了右端点的上界，而 $\min$ 限制了右端点的下界，随着左半区间的后缀最小值不断变小，右端点下界肯定是递增的，而上界同理。所以问题变为对于一个区间满足一个不等式的点数，二维数点即可。

4. $\min$ 在左半区间，$\max$ 在右半区间，与情况三同理。

实现时，二维数点我用的主席树，所以时间复杂度 $O(n \log^2 n)$，代码写的比较唐，[code](https://atcoder.jp/contests/abc248/submissions/58894178)。

---

## 作者：zzxLLL (赞：2)


[弱化版](https://www.luogu.com.cn/problem/CF526F)

---

令 $M(l, r) = \max\limits_{i = l}^r P_i - \min\limits_{i = l}^r P_i$。

因为 $P$ 是 $1 \sim n$ 的排列，所以有 $M(l, r) \ge r - l$，当 $P_{l, \cdots, r}$ 刚好是 $l \sim r$ 的排列时取等。

满足条件的 $(l, r)$ 有 $M(l, r) \leq r - l + k$，移项得 $M(l, r) - r + l \le k$。考虑对右端点扫描线，对于每个 $R$ 求出 $f_L = M(l, r) - r + l$，有多少个 $L$ 满足 $f_L \le k$。注意到 $k$ 很小，而 $M(l, r) - r + l \ge 0$ 成立。维护 $f_L$ 的前 $k$ 小值以及它们的出现次数即可。

当 $R \gets R + 1$ 时，用单调栈求出 $\max\limits_{i = L}^R P_i$ 和 $\min\limits_{i = L}^R P_i$ 的变化，于是就是对 $f_L$ 的区间加。

区间加区间前 $k$ 小，容易用线段树解决。时间复杂度 $O(nk \log n \log k)$

```cpp
#include<array>
#include<cstdio>
#include<vector>
#include<algorithm>

const int M = 1.5e5 + 10;
const int inf = 1e9 + 7;

typedef std::array<std::pair<int, int>, 4> ia;
std::vector<int>vec;

int n, p[M], k;

struct node {
    ia val;
    int l, r, lzy;
}tr[M << 2];
ia merge(ia A, ia B) {
    ia C;
    vec.clear();
    for (int i = 0; i < 4; i++) C[i] = { inf, 0 };
    for (int i = 0; i < 4; i++) vec.push_back(A[i].first);
    for (int i = 0; i < 4; i++) vec.push_back(B[i].first);
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    for (int i = 0; i < std::min((int)vec.size(), 4); i++) C[i] = { vec[i], 0 };
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (A[i].first == C[j].first) C[j].second += A[i].second;
            if (B[i].first == C[j].first) C[j].second += B[i].second;
        }
    return C;
}
void tag(int k, int v) {
    for (int i = 0; i < 4; i++)
        if (tr[k].val[i].first != inf) tr[k].val[i].first += v;
    tr[k].lzy += v;
}
void pushdown(int k) {
    if (tr[k].lzy)
        tag(k << 1, tr[k].lzy), tag(k << 1 | 1, tr[k].lzy), tr[k].lzy = 0;
}
void build(int k, int l, int r) {
    tr[k].l = l, tr[k].r = r;
    if (l == r) {
        for (int i = 0; i < 4; i++) tr[k].val[i] = { inf, 0 };
        tr[k].val[0] = { l, 1 };
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tr[k].val = merge(tr[k << 1].val, tr[k << 1 | 1].val);
}
void add(int k, int l, int r, int v) {
    if (l > r) return;
    if (l <= tr[k].l && tr[k].r <= r) return tag(k, v);
    pushdown(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (l <= mid) add(k << 1, l, r, v);
    if (r > mid)  add(k << 1 | 1, l, r, v);
    tr[k].val = merge(tr[k << 1].val, tr[k << 1 | 1].val);
}
ia qry(int k, int l, int r) {
    if (l <= tr[k].l && tr[k].r <= r) return tr[k].val;
    pushdown(k);
    int mid = (tr[k].l + tr[k].r) >> 1;
    if (r <= mid) return qry(k << 1, l, r);
    if (l > mid)  return qry(k << 1 | 1, l, r);
    return merge(qry(k << 1, l, r), qry(k << 1 | 1, l, r));
}

int stkmin[M], topmin;
int stkmax[M], topmax;
long long ans;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    build(1, 1, n);

    for (int i = 1; i <= n; i++) {
        add(1, 1, n, -1);
        while (topmax && p[stkmax[topmax]] < p[i]) {
            add(1, stkmax[topmax - 1] + 1, stkmax[topmax], -p[stkmax[topmax]]);
            topmax--;
        }
        add(1, stkmax[topmax] + 1, i, p[i]), stkmax[++topmax] = i;
        while (topmin && p[stkmin[topmin]] > p[i]) {
            add(1, stkmin[topmin - 1] + 1, stkmin[topmin], p[stkmin[topmin]]);
            topmin--;
        }
        add(1, stkmin[topmin] + 1, i, -p[i]), stkmin[++topmin] = i;
        ia res = qry(1, 1, i);
        for (auto qwq : res)
            if (qwq.first <= k) ans += qwq.second;
    }
    printf("%lld\n", ans);
    return 0;
}
```

用 cdq 分治，分 $\min, \max$ 分别在左/右区间讨论，可以做到不依赖 $k \le 3$。

---

## 作者：Tsawke (赞：2)

#  [[ABC248Ex] Beautiful Subsequences](https://www.luogu.com.cn/problem/AT_abc248_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC248Ex)

## 题面

给定排列 $ P_n $ 和整数 $ k $，求满足如下条件的点对 $ (l, r) $ 数量。

* $ 1 \le l \le r \le n $。
* $ \max_{i = l}^rP_i - \min_{i = l}^rP_i \le r - l + k $。

## Solution

首先为了方便我们令 $ mx = \max_{i = l}^rP_i, mn = \min_{i = l}^rP_i $，原式转化为 $ mx - mn \le r - l + k $，发现 $ k \in [0, 3] $，所以可以考虑将不等式转化为等式，枚举 $ k $，对于每个 $ k $，合法方案满足 $ mx - mn = r - l + k $。于是原式可以转化为对于每个 $ r \in [1, n] $，求满足 $ l \in [1, r], k \in [0, K], l + mx - mn = r + k $ 的个数，此时 $ l, r, k $ 均为固定的，所以我们只需要求出此时的区间 $ \max, \min $，即可确定是否合法。换句话说，对于枚举的 $ r $，要找其左侧所有点的 $ l + mx - mn $ 的值与 $ r + k $ 相等的个数。

于是到此问题可转化为，求区间最大值最小值，然后再求区间等于 $ r $ 的数量。对于求区间最大值最小值，这个东西我们发现求的是对于每个 $ r $ 的所有后缀最大最小值，这个东西用单调栈维护即可。具体地，对于一个新的值，显然其只有可能更新它前面的点的最值，其自己在第一次插入的时候后缀的区间为 $ [i, i] $，最值显然均为 $ a_i $，但是这个时候我们却不需要更新最值，因为我们要的值是 $ mx - mn $，既然最值相同那么这个东西为 $ 0 $，所以可以忽略。然后对于一个新的值，要去尝试更新前面值的最值，如对于最大值需要维护单调递减的栈，即栈顶最小，如果新的值更小直接丢到栈上，否则更新栈顶和次栈顶之间区间的最大值。把这些维护完之后直接求所有值为 $ r $ 的点即可。

然后考虑如何维护区间等于 $ r + k $ 的个数，有一个比较好想的就是维护一棵线段树，对于每个节点都维护一个 `basic_string < pair < int, int > >`，存储对应值有多少个，合并的时候直接把两个加起来即可，然后去个重。同时此时查询的时候可以不用枚举 $ k $，直接找 $ r + k $ 大于等于对应值即可。以此我们便可很直观地写出如下实现，但是这个是错误的。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MAXN (150000)

template< typename T = int >
inline T read(void);

int N, K;
int val[MAXN];

struct MyPair{
    int first, second;
    friend const bool operator < (const MyPair &a, const MyPair &b){
        return a.first == b.first ? a.second < b.second : a.first < b.first;
    }
};

struct Node{
    basic_string < MyPair/*val, cnt*/ > vals;
    int lz;
    Node operator = (const Node &b){
        this->vals = b.vals;
        this->lz = b.lz;
        return *this;
    }
    friend const Node operator + (const Node &a, const Node &b){
        Node ret{a.vals + b.vals, 0};
        sort(ret.vals.begin(), ret.vals.end());
        for(auto it = ret.vals.begin(); next(it) != ret.vals.end();)
            if(it->first == next(it)->first)next(it)->second += it->second, it = ret.vals.erase(it);
            else advance(it, 1);
        return ret;
    }
    friend Node operator += (Node &a, const int &val){
        for(auto &nod : a.vals)nod.first += val;
        a.lz += val;
        return a;
    }
};
class SegTree{
private:
    Node tr[MAXN << 2];
    #define LS (p << 1)
    #define RS (LS | 1)
    #define MID ((gl + gr) >> 1)
public:
    void Pushup(int p){tr[p] = tr[LS] + tr[RS];}
    void Pushdown(int p){
        if(!tr[p].lz)return;
        tr[LS].lz = tr[RS].lz = tr[p].lz;
        tr[LS] += tr[p].lz, tr[RS] += tr[p].lz;
        tr[p].lz = 0;
    }
    void Build(int p = 1, int gl = 1, int gr = N){
        if(gl == gr)return tr[p].vals += {gl = gr, 1}, void();
        Build(LS, gl, MID), Build(RS, MID + 1, gr);
        Pushup(p);
    }
    void Modify(int l, int r, int val, int p = 1, int gl = 1, int gr = N){
        if(l <= gl && gr <= r)return tr[p] += val, void();
        Pushdown(p);
        if(l <= MID)Modify(l, r, val, LS, gl, MID);
        if(r >= MID + 1)Modify(l, r, val, RS, MID + 1, gr);
        Pushup(p);
    }
    Node Query(int l, int r, int p = 1, int gl = 1, int gr = N){
        if(l <= gl && gr <= r)return tr[p];
        Pushdown(p);
        if(l > MID)return Query(l, r, RS, MID + 1, gr);
        if(r < MID + 1)return Query(l, r, LS, gl, MID);
        return Query(l, r, LS, gl, MID) + Query(l, r, RS, MID + 1, gr);
    }
}st;
ll Cal(int R){
    ll ret(0);
    auto vals = st.Query(1, R).vals;
    //r + k >= l + max - min
    for(auto nod : vals)if(R + K >= nod.first)ret += nod.second;
    return ret;
}

int mx[MAXN]/*Query Min*/, mn[MAXN]/*Query Max*/;
int mxp(0), mnp(0);

int main(){
    N = read(), K = read();
    for(int i = 1; i <= N; ++i)val[i] = read();
    st.Build();
    ll ans(0);
    for(int R = 1; R <= N; ++R){
        while(mxp && val[R] > val[mx[mxp]])st.Modify(mx[mxp - 1] + 1, mx[mxp], val[R] - val[mx[mxp]]), --mxp;
        while(mnp && val[R] < val[mn[mnp]])st.Modify(mn[mnp - 1] + 1, mn[mnp], val[mn[mnp]] - val[R]), --mnp;
        mx[++mxp] = mn[++mnp] = R;
        ans += Cal(R);
        // printf("R = %d, Cal = %lld\n", R, Cal(R));
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
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

不过这个东西我们简单分析以下复杂度就会发现，每次合并和修改之后的 `Pushup` 都会使其重构然后耗费大量时间，所以最后复杂度是 $ O(\texttt{玄学}) $ 的，提交后就会发现 AT 上只能过十多个点。。感觉复杂度直接退化到暴力了。

然后对于 `basic_string < pair < int, int > >` 还有个很严重的问题，对于一般的 C++14 及以下都不会有任何问题，但是在 C++17 之后，因为 `basic_string.h` 中有如下语段：

```cpp
#if __cplusplus >= 201703L
# include <string_view>
#endif
```

然而引入的这个头文件中还存在如下语句：

```cpp
static_assert(is_trivial_v<_CharT> && is_standard_layout_v<_CharT>);
```

此时我们发现，这东西会 CE！测试后发现如下语段会输出 $ 0 $：

```cpp
cout << is_trivial < pair< int, int > >::value << endl;
```

众所周知 `is_trivial` 一般就是用于判断类型的构造函数是否为默认构造函数，而 `pair` 的构造函数似乎是用初始化列表写的，可能是因为这个原因，就会导致其无法通过这个 `assert`，于是就寄了。然而 AT 上默认的不知道是 C++17 还是 20 或者更高，所以无法过编。这个或许可以通过一些高妙的方式解决，~~但是我不会~~，于是考虑自定义一个结构体实现跟 `pair` 一样但是使用默认构造函数即可。

所以话说回来，这个做法本身就是错误的，于是现在我们考虑正解：

思考什么东西比较好维护区间最值和区间等于 $ x $ 的数量，不难想到分块，维护的方式和上面说的差不多，只是用分块替换线段树即可，这个东西的复杂度就是 $ O(k n \sqrt{n}) $，可以通过，似乎也是官方正解，但是~~我不太喜欢分块~~这个复杂度不够优秀，所以这里就不给代码实现了，我们考虑一些更优秀的做法。

考虑分治，思路来自机房大佬 @sssmzy，发现对于每一个区间，如果我们令 $ l \in [L, mid], r \in [mid + 1, R] $ 是可以快速维护答案的，于是我们只需要以此为基础，计算完答案后分别二分下去即可。

具体地，对于维护答案的过程，我们发现最大值和最小值的位置无法确定，所以考虑枚举最大值在左侧或右侧，以左侧为例子，我们按照类似猫树的思想，从 $ mid $ 向两侧维护后/前缀最值，不难想到，以前缀最大值为例，显然扩展时最大值是单调不降的，最小值同理，然而我们需要让最大值取在左侧，那么显然存在一个分割点 $ sp1 $，在其左的右侧点是合法的，同时也存在一个分割点 $ sp2 $，满足在其左的点最小值取左侧，其右的取右侧，然后发现这个东西是单调的，所以可以直接双（三）指针，枚举 $ l $，考虑 $ sp1, sp2 $，同时维护桶记录所有可能的合法的值的数量。然后讨论 $ r $ 位置与分割点的关系，如果在 $ [mid + 1, \min(sp1, sp2)] $ 那么显然此时最大最小值都在左侧，也就是此时确定 $ k $ 之后直接就有 $ r = l + mx - mn - k $，判断 $ \texttt{RHS} $ 是否在范围内即可。否则在 $ (sp1, sp2] $ 之间的话，最大值在左侧和 $ l $ 相关，最小值在右侧和 $ r $ 相关，此时有 $ r - mn = l + mx - k $，同样将对应 $ \texttt{RHS} $ 的桶加上即可。然后再考虑 $ mx $ 再右侧同理算一遍即可，注意此时因为索引可能为负，所以需要加个 $ n $ 转正。

当前区间算完之后二分下去分别求解即可，这样最终复杂度 $ O(k n \log n) $，跑得飞快。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MAXN (150000)

template < typename T = int >
inline T read(void);

int N, K;
int a[MAXN];
ll ans(0);
int mx[MAXN], mn[MAXN];
int buc[MAXN << 1];

void Divide(int gl = 1, int gr = N){
    if(gl == gr)return ++ans, void();
    int MID = (gl + gr) >> 1;
    mx[MID] = mn[MID] = a[MID], mx[MID + 1] = mn[MID + 1] = a[MID + 1];
    for(int i = MID - 1; i >= gl; --i)mx[i] = max(mx[i + 1], a[i]), mn[i] = min(mn[i + 1], a[i]);
    for(int i = MID + 2; i <= gr; ++i)mx[i] = max(mx[i - 1], a[i]), mn[i] = min(mn[i - 1], a[i]);
    int sp1(MID), sp2(MID);
    for(int l = MID; l >= gl; --l){
        while(sp1 + 1 <= gr && mx[sp1 + 1] <= mx[l])++sp1, buc[sp1 + mn[sp1]]++;
        while(sp2 + 1 <= gr && mn[sp2 + 1] >= mn[l])++sp2, buc[sp2 + mn[sp2]]--;
        for(int k = 0; k <= K; ++k){
            int r = l + mx[l] - mn[l] - k;
            int idx = l + mx[l] - k;
            if(MID + 1 <= r && r <= min(sp1, sp2))++ans;
            if(sp2 < sp1 && idx > 0)ans += buc[idx];
        }
    }for(int i = MID + 1; i <= gr; ++i)buc[i + mn[i]] = 0;
    sp1 = MID + 1, sp2 = MID + 1;
    for(int r = MID + 1; r <= gr; ++r){
        while(sp1 - 1 >= gl && mx[sp1 - 1] <= mx[r])--sp1, buc[sp1 - mn[sp1] + N]++;
        while(sp2 - 1 >= gl && mn[sp2 - 1] >= mn[r])--sp2, buc[sp2 - mn[sp2] + N]--;
        for(int k = 0; k <= K; ++k){
            int l = r - mx[r] + mn[r] + k;
            int idx = r - mx[r] + k + N;
            if(max(sp1, sp2) <= l  && l <= MID)++ans;
            if(sp1 < sp2 && idx > 0)ans += buc[idx];
        }
    }for(int i = gl; i <= MID; ++i)buc[i - mn[i] + N] = 0;
    Divide(gl, MID), Divide(MID + 1, gr);
}

int main(){
    N = read(), K = read();
    for(int i = 1; i <= N; ++i)a[i] = read();
    Divide();
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
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

update-2022_11_22 初稿

---

## 作者：CQ_Bab (赞：1)

# 前言
简单分治题。
# 思路
看到这种序列上的询问可以往分治上想了，首先我们对于当前区间 $l\sim r$ 讨论一下最大值在 $l\sim mid$ 中还是 $mid+1\sim r$ 中，然后就要分类讨论了。

- 对于最大值在 $i\sim mid$（我们当前枚举到了 $i$ 且 $i$ 在 $l\sim mid$ 中）中的情况，再讨论一下最小值是否在 $i\sim mid$ 中，我们假设最大值在 $i\sim mid$ 中时最大能取的右端点为 $R$ 当最小值在 $i\sim mid$ 能取的最靠右的点为 $L$，然后我们发现此时的最大值和最小值还有一个端点都固定了，那么柿子为 $Max-Min-k+i\leq r$ 左边都可知所以只需要用加减法就可以求出 $r$ 的个数了，个数为 $\min(L,R)-\max(mid+1,Max-Min-k+i)$。
- 对于最大值还是在 $i\sim mid$ 中但是最小值在另一边的情况，发现右端点只能在 $L\sim R$ 中取，此时的柿子为 $Max+i-k\leq r+Min$ 此时我们只需要开一颗主席树就可以维护出 $r+Min$ 大于 $Max-k+i$ 的数量了。
- 当最大值在右边时（注意这里必须是绝对最大值因为在上面的两种情况最大值可以左右都有，所以为了不算重就要时绝对最大值），并且此时最小值也要在 $mid+1\sim i$ 中，然后求出当前最大值在 $mid+1\sim i$ 时左端点最少能取到 $L$ 以及最小值在 $mid+1\sim i$ 中左端点最多能取到 $R$ 然后就成了求 $Max-Min-i-k\leq -l$ 中 $l$ 的个数，这里最好将负号消掉成了 $-(Max-Min-i-k)\geq l$，所以个数就为 $\min(mid,-(Max-Min-i-k))-\max(L,R)$。
- 最后一种情况就是当最大值在 $mid+1\sim i$ 中但是最小值在 $l\sim mid$ 中时此时就是要求 $Max-i-k\leq -l+Min$ 中 $l$ 的数量，也是直接开主席树维护即可（要让 $l$ 在 $L\sim R-1$ 中）。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,k;
const int N=4e5+10; 
int f[N][20],lg[N],g[N][20];
int Ans(int x,int y) {
	int len=lg[y-x+1];
	return max(f[x][len],f[y-(1<<len)+1][len]);
}
int Ans1(int x,int y) {
	int len=lg[y-x+1];
	return min(g[x][len],g[y-(1<<len)+1][len]);
}
int a[N],res;
int find(int x,int l,int r) {
	int res=l-1;
	int ll=l;
	while(l<=r) {
		int mid=l+r>>1;
		if(Ans(ll,mid)<=x) l=mid+1,res=mid;
		else r=mid-1;
	}
	return res;
}
int find1(int x,int l,int r) {
	int res=l-1,ll=l;
	while(l<=r) {
		int mid=l+r>>1;
		if(Ans1(ll,mid)>=x) l=mid+1,res=mid;
		else r=mid-1;
	}
	return res;
}
struct node{
	int l,r;
	int sum;
}tr[N<<5];
void up(int x) {
	tr[x].sum=tr[tr[x].l].sum+tr[tr[x].r].sum;
}
int rt[N],idx;
int modify(int u,int l,int r,int k) {
	int p=++idx;
	tr[p]=tr[u];
	if(l==r) {
		tr[p].sum++;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) tr[p].l=modify(tr[p].l,l,mid,k);
	else tr[p].r=modify(tr[p].r,mid+1,r,k);
	up(p);
	return p;
}
int Ans(int u,int l,int r,int p) {
	if(!u) return false;
	if(l==r) return tr[u].sum;
	int mid=l+r>>1;
	if(mid>=p) return Ans(tr[u].l,l,mid,p)+tr[tr[u].r].sum;
	return Ans(tr[u].r,mid+1,r,p);
}
int findl(int x,int l,int r) {
	int rr=r,res=r+1;
	while(l<=r) {
		int mid=l+r>>1;
		if(Ans(mid,rr)<x) r=mid-1,res=mid;
		else l=mid+1;
	}
	return res;
}
int findr(int x,int l,int r) {
	int rr=r,res=r+1;
	while(l<=r) {
		int mid=l+r>>1;
		if(Ans1(mid,rr)>=x) r=mid-1,res=mid;
		else l=mid+1;
	}
	return res;
}
void solve(int l,int r) {
	if(l==r) {
		if(0<=r-l+k) res++;
		return ;
	}
	if(l>r) return;
	int mid=l+r>>1;
	solve(l,mid);
	solve(mid+1,r);
	idx=false;
	rt[l-1]=false;
	rep(i,l,mid) {
		rt[i]=rt[i-1];
		rt[i]=modify(rt[i],0,N*5,Ans1(i,mid)-i+N*3);
	}
	rep(i,mid+1,r) {
		rt[i]=rt[i-1];
		rt[i]=modify(rt[i],0,N*5,Ans1(mid+1,i)+i+N*3);
	}
	rep(i,l,mid) {
		int Max=Ans(i,mid);
		int R=find(Max,mid,r);
		int Min=Ans1(i,mid);
		int L=find1(Min,mid,r);
		int now=Max-Min+i-k;
		now=max(now,mid+1);
		res+=max(0ll,min(L,R)-now+1);
		int sum=Max+i-k;
		if(L<R) res+=Ans(rt[R],0,N*5,sum+N*3)-Ans(rt[L],0,N*5,sum+N*3);
	}
	rep(i,mid+1,r) {
		int Max=Ans(mid+1,i);
		int L=findl(Max,l,mid);
		int Min=Ans1(mid+1,i);
		int R=findr(Min,l,mid);
		int now=Max-Min-i-k;
		now=-now;
		if(now>=max(L,R)) res+=max(0ll,min(now,mid)-max(L,R)+1);
		int sum=Max-i-k;
		if(R>L) res+=Ans(rt[R-1],0,N*5,sum+N*3)-Ans(rt[L-1],0,N*5,sum+N*3);
	}
}
void solve() {
	in(n),in(k);
	rep(i,1,n) in(a[i]),f[i][0]=g[i][0]=a[i];
	rep(i,2,n) lg[i]=lg[i/2]+1;
	rep(j,1,lg[n]) {
		rep(i,1,n-(1<<j)+1) {
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
			g[i][j]=min(g[i][j-1],g[i+(1<<j-1)][j-1]);
		}
	}
	solve(1,n);
	printf("%lld\n",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：ABookCD (赞：1)

### [V. ABC248Ex Beautiful Subsequences](https://www.luogu.com.cn/problem/AT_abc248_h)(Diff. 2,835)

> 摘自文章[序列分治](https://www.cnblogs.com/arizonayyds/articles/fenzhi.html) V. ABC248Ex Beautiful Subsequences

与文章中的 IV.[CF526F Pudding Monst ](http://codeforces.com/problemset/problem/526/F) 在建模之后式子几乎一样，只是多了个 $k$，变成了不等式关系 。

以下部分内容摘自第四题。

考虑序列分治。

同时维护右边前缀 $\max$ 和 $\min$ 两个序列，枚举左端点 $lpos$，当前左区间的 $\max$ 和 $\min$ 分别为 $lmax$ 和 $lmin$，与 [NOIP2022 比赛] 的 $52$ 分做法类似地根据右端点前缀 $\max$ 和 $\min$ 与当前 $lmax$ 和 $lmin$ 的位置将右端点分成四段。

设当前考虑的右端点前缀 $\max$ 和 $\min$ 分别为 $rmax$ 和 $rmin$。

将 $\min$ 和 $\max$ 拆开以后，我们对每一段将式子中跟左端点和右端点有关的值分成两部分，每一类都构成一个不等关系。

如满足 $lmax \le rmax \land lmin\ge rmin$ 的类别，也就是两个双指针都没走到的位置，我们可以写出式子
$$
\begin{aligned}
\\rmax-rmin \le (mid-l+1)+(r-mid)+k-1
\\rmax-rmin+(r-mid)\le (mid-l+1)+k-1
\end{aligned}
$$
其他三类同理。

我们对于每一个右端点的这个值，加入一个数据结构内维护，那么每次查找相当于对一段区间内的查询，当双指针向右移动的时候就把它取出，加入别的类，可以用一个数组来记录当前属于的类别。

同 III.[P4755 Beautiful Pair](https://www.luogu.com.cn/problem/P4755)  的套路，不难想到用离散化后的值域线段树来维护，时间复杂度 $O(n\ log^2 n)$，空间复杂度 $O(n)$。

移动右端点时的细节见代码。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,a[300010],ans;
int qzamax[300010],qzamin[300010];
int blt[300010];
int tr[5][5700010],k;
// S1   lmax-lmin<=cl+cr+k-1  
// s2   lmax-rmin<=cl+cr+k-1
// S3   rmax-lmin<=cl+cr+k-1
//s4    rmax-rmin<=cl+cr+k-1
//S1   cr+k-1           >=       lmax-lmin-cl
//s2    cr+rmin+k-1       >=     lmax-cl
//s3    rmax-cr-(k-1)     <=    cl+lmin 
//s4     rmax-rmin-cr-(k-1) <=    cl
int tmp[5][300010],idx[5];
void pushup(int op,int id){
	tr[op][id]=(tr[op][id<<1]+tr[op][id<<1|1]);
}
void build(int op,int id,int l,int r){
	tr[op][id]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(op,id<<1,l,mid);
	build(op,id<<1|1,mid+1,r);
}
void update(int op,int id,int l,int r,int x,int v){
	if(l==r){
		tr[op][id]+=v;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(op,id<<1,l,mid,x,v);
	else update(op,id<<1|1,mid+1,r,x,v);
	pushup(op,id);
}
int query(int op,int id,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return tr[op][id];
	}
	int mid=(l+r)>>1,res=0;
	if(ql<=mid) res+=query(op,id<<1,l,mid,ql,qr);
	if(qr>mid) res+=query(op,id<<1|1,mid+1,r,ql,qr);
	return res;
}
void solve(int l,int r){
	if(l==r){
		ans+=(0<=r-l+1+k);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	
	int lemax=0,rxenda=mid,rxendi=mid,lemin=1e9;
	qzamax[mid]=0,qzamin[mid]=1e9;
	for(int i=1;i<=4;i++) idx[i]=0;
	for(int i=mid+1;i<=r;i++) qzamax[i]=max(qzamax[i-1],a[i]),qzamin[i]=min(qzamin[i-1],a[i]);
	for(int i=mid+1;i<=r;i++){
		tmp[1][++idx[1]]=i-mid+k-1;
		tmp[2][++idx[2]]=i-mid+k-1+qzamin[i];
		tmp[3][++idx[3]]=qzamax[i]-(i-mid)-(k-1);
		tmp[4][++idx[4]]=qzamax[i]-qzamin[i]-(i-mid)-(k-1);
		blt[i]=4;
	}
	map<int,int> mp[5];
	for(int i=1;i<=4;i++){
		sort(tmp[i]+1,tmp[i]+idx[i]+1);
		idx[i]=unique(tmp[i]+1,tmp[i]+idx[i]+1)-tmp[i]-1; 
		for(int j=1;j<=idx[i];j++) mp[i][tmp[i][j]]=j;
		build(i,1,1,idx[i]);
	}
	
	for(int i=mid+1;i<=r;i++){
		update(4,1,1,idx[4],mp[4][qzamax[i]-qzamin[i]-(i-mid)-(k-1)],1);
	}
	for(int lpos=mid;lpos>=l;lpos--){
		lemax=max(lemax,a[lpos]);
		lemin=min(lemin,a[lpos]);
		while(rxenda<r&&qzamax[rxenda+1]<lemax){
			rxenda++;
			if(blt[rxenda]==4){
				blt[rxenda]=2;
				update(4,1,1,idx[4],mp[4][qzamax[rxenda]-qzamin[rxenda]-(rxenda-mid)-(k-1)],-1);
				update(2,1,1,idx[2],mp[2][qzamin[rxenda]+(rxenda-mid)+k-1],1);
			}
			if(blt[rxenda]==3){
				blt[rxenda]=1;
				update(3,1,1,idx[3],mp[3][qzamax[rxenda]-(rxenda-mid)-(k-1)],-1);
				update(1,1,1,idx[1],mp[1][(rxenda-mid)+k-1],1);
			}
		}
		while(rxendi<r&&qzamin[rxendi+1]>lemin){
			rxendi++;
			if(blt[rxendi]==4){
				blt[rxendi]=3;
				update(4,1,1,idx[4],mp[4][qzamax[rxendi]-qzamin[rxendi]-(rxendi-mid)-(k-1)],-1);
				update(3,1,1,idx[3],mp[3][qzamax[rxendi]-(rxendi-mid)-(k-1)],1);
			}
			if(blt[rxendi]==2){
				blt[rxendi]=1;
				update(2,1,1,idx[2],mp[2][qzamin[rxendi]+(rxendi-mid)+k-1],-1);
				update(1,1,1,idx[1],mp[1][(rxendi-mid)+k-1],1);
			}
		}
		int cl=(mid-lpos+1);
		int q1=lower_bound(tmp[1]+1,tmp[1]+idx[1]+1,lemax-lemin-cl)-tmp[1];
		if(q1!=idx[1]+1)ans+=query(1,1,1,idx[1],q1,idx[1]);
		
		int q2=lower_bound(tmp[2]+1,tmp[2]+idx[2]+1,lemax-cl)-tmp[2];
		if(q2!=idx[2]+1) ans+=query(2,1,1,idx[2],q2,idx[2]);
		
		int q3=upper_bound(tmp[3]+1,tmp[3]+idx[3]+1,cl+lemin)-tmp[3]-1;
		if(q3) ans+=query(3,1,1,idx[3],1,q3);
		
		int q4=upper_bound(tmp[4]+1,tmp[4]+idx[4]+1,cl)-tmp[4]-1;
		if(q4) ans+=query(4,1,1,idx[4],1,q4);
	}
	
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc248_h)

# 前置知识

[树状数组](https://oi-wiki.org/ds/fenwick/) | 序列分治

# 解法

考虑序列分治，设因 $\max$ 和 $\min$ 形成的分节点先后为 $k_{1},k_{2}$。

对于 $j \in (mid,k_{1}]$，等价于统计满足 $\max\limits_{h=i}^{mid} \{ a_{h} \}-\min\limits_{h=i}^{mid} \{ a_{h} \} \le j-i+k$ 的 $j$ 的数量，容易求解。

对于 $j \in (k_{1},k_{2}]$，以 $[i,j]$ 的 $\max$ 落在 $(k_{1},k_{2}]$ 为例，需要统计满足 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-\min\limits_{h=i}^{mid} \{ a_{h} \} \le j-i+k$ 的 $j$ 数量，移项得到 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-j \le \min\limits_{h=i}^{mid} \{ a_{h} \}-i+k$，移动指针的过程中树状数组维护 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-j$ 的桶数组即可。

对于 $j \in (k_{2},r]$，需要统计 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-\min\limits_{h=mid+1}^{j} \{ a_{h} \} \le j-i+k$ 的 $j$ 数量，移项得到 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-\min\limits_{h=mid+1}^{j} \{ a_{h} \}-j \le -i+k$，移动指针的过程中树状数组维护 $\max\limits_{h=mid+1}^{j} \{ a_{h} \}-\min\limits_{h=mid+1}^{j} \{ a_{h} \}-j$ 的桶数组即可。

注意下标移位。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int a[140010],pre_max[140010],pre_min[140010],n,m;
ll ans=0;
struct BIT
{
	int c[500010];
	int lowbit(int x)
	{
		return (x&(-x));
	}
	void add(int n,int x,int val)
	{
		for(int i=x;i<=n;i+=lowbit(i))
		{
			c[i]+=val;
		}
	}
	void del(int n,int x)
	{
		for(int i=x;i<=n;i+=lowbit(i))
		{
			c[i]=0;
		}
	}
	int getsum(int x)
	{
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))
		{
			ans+=c[i];
		}
		return ans;
	}
}T[3];
void solve(int l,int r)
{
	if(l==r)
	{
		ans++;
		return;
	}
	int mid=(l+r)/2,suf_max=0,suf_min=0x7f7f7f7f;
	pre_max[mid+1]=pre_min[mid+1]=a[mid+1];
	for(int i=mid+2;i<=r;i++)
	{
		pre_max[i]=max(pre_max[i-1],a[i]);  pre_min[i]=min(pre_min[i-1],a[i]);
	}
	for(int i=mid+1;i<=r;i++)  T[0].add(500000,pre_max[i]-pre_min[i]-i+300000,1);
	for(int i=mid,k1=mid,k2=mid;i>=l;i--)
	{
		suf_max=max(suf_max,a[i]);  suf_min=min(suf_min,a[i]);
		while(k1+1<=r&&suf_max>=pre_max[k1+1]&&suf_min<=pre_min[k1+1])
		{
			k1++;
			T[1].add(500000,pre_max[k1]-k1+300000,-1);
			T[2].add(500000,-k1-pre_min[k1]+300000,-1);
		}
		while(k2+1<=r&&(suf_max>=pre_max[k2+1]||suf_min<=pre_min[k2+1]))
		{
			k2++;
			T[0].add(500000,pre_max[k2]-pre_min[k2]-k2+300000,-1);
			T[1].add(500000,pre_max[k2]-k2+300000,1);
			T[2].add(500000,-k2-pre_min[k2]+300000,1);
		}
		ans+=max(0,k1-max(mid+1,suf_max-suf_min-m+i)+1);
		ans+=T[0].getsum(m-i+300000);
		ans+=(suf_min<=pre_min[k2])?T[1].getsum(suf_min-i+m+300000):T[2].getsum(-suf_max-i+m+300000);
	}
	for(int i=mid+1;i<=r;i++)  T[0].del(500000,pre_max[i]-pre_min[i]-i+300000);
	for(int i=mid+1;i<=r;i++)  T[1].del(500000,pre_max[i]-i+300000);
	for(int i=mid+1;i<=r;i++)  T[2].del(500000,-i-pre_min[i]+300000);
	solve(l,mid);
	solve(mid+1,r);
}
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	solve(1,n);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

本题为 [CF526F Pudding Monsters](https://www.luogu.com.cn/problem/CF526F) 的小加强版。

扫描线右端点，单调栈维护 $\max, \min$，支持区间加，维护区间前严格 $k$ 小值和出现的次数即可。

合并过程可以归并 $O(k)$，但是本人有点懒，直接 $O(k^2)$ 暴力合并的，时间复杂度为 $O(k^2 N \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct St{
	int data[4];
	int cnt[4];
	St(){
		for(int i = 0; i < 4; ++i)
		  data[i] = cnt[i] = 0;
	}
};
struct Node{
	int l, r, tag;
	St now;
}X[N << 2];
ll ans = 0;
int n, k, top;
int a[N], T[N];
vector<pair<pair<int, int>, int>> E[N];
inline St merge(St a, St b){
	vector<int> V;
	St ans;
	for(int i = 0; i < 4; ++i){
		V.push_back(a.data[i]);
		V.push_back(b.data[i]);
	}
	sort(V.begin(), V.end());
	auto it = unique(V.begin(), V.end());
	V.erase(it, V.end());
	if(V.size() < 4){
		for(int i = 0; i < (int)V.size(); ++i){
			ans.data[i] = V[i];
			for(int j = 0; j < 4; ++j){
				if(a.data[j] == V[i])
				  ans.cnt[i] += a.cnt[j];
				if(b.data[j] == V[i])
				  ans.cnt[i] += b.cnt[j];
			}
		}
		for(int i = V.size(); i < 4; ++i)
		  ans.data[i] = 1e9;
	}
	else{
		for(int i = 0; i < 4; ++i){
			ans.data[i] = V[i];
			for(int j = 0; j < 4; ++j){
				if(a.data[j] == V[i])
				  ans.cnt[i] += a.cnt[j];
				if(b.data[j] == V[i])
				  ans.cnt[i] += b.cnt[j];
			}
		}		
	}
	return ans;
}
inline void pushup(int k){
	X[k].now = merge(X[k << 1].now, X[k << 1 | 1].now);
}
inline void add(int k, int v){
	for(int i = 0; i < 4; ++i)
	  if(X[k].now.data[i] != 1e9)
	    X[k].now.data[i] += v;
	X[k].tag += v;
}
inline void push_down(int k){
	if(X[k].tag){
		add(k << 1, X[k].tag);
		add(k << 1 | 1, X[k].tag);
		X[k].tag = 0;
	}
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].now.data[0] = X[k].now.data[1] = X[k].now.data[2] = X[k].now.data[3] = 1e9;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l, int r, int v, bool f = 0){
	if(X[k].l == l && r == X[k].r){
		if(f){
			X[k].now.data[0] = 0;
			X[k].now.cnt[0] = 1;
		}
		else
		  add(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v, f);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v, f);
	else{
		update(k << 1, l, mid, v, f);
		update(k << 1 | 1, mid + 1, r, v, f);
	}
	pushup(k);
}
bool End;
int main(){
	n = read(), k = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	a[n + 1] = 2e9, top = 0;;
	for(int i = 1; i <= n + 1; ++i){
		while(top && a[T[top]] < a[i]){
			int l = T[top], r = i - 1;
			E[l].push_back({{T[top - 1] + 1, T[top]}, a[T[top]]});
			E[r + 1].push_back({{T[top - 1] + 1, T[top]}, -a[T[top]]});
			--top;
		}
		T[++top] = i;
	}
	a[n + 1] = 0, top = 0;
	for(int i = 1; i <= n + 1; ++i){
		while(top && a[T[top]] > a[i]){
			int l = T[top], r = i - 1;
			E[l].push_back({{T[top - 1] + 1, T[top]}, -a[T[top]]});
			E[r + 1].push_back({{T[top - 1] + 1, T[top]}, a[T[top]]});
			--top;
		}
		T[++top] = i;
	}
	build(1, 1, n);
	for(int i = 1; i <= n; ++i){
		if(i > 1)
	      update(1, 1, i - 1, -1);
	    update(1, i, i, 0, 1);
		for(auto t : E[i])
		  update(1, t.fi.fi, t.fi.se, t.se);
		for(int j = 0; j < 4; ++j)
		  if(X[1].now.data[j] <= k)
		    ans += X[1].now.cnt[j];
//		    cerr << X[1].now.data[j] << ' ' << X[1].now.cnt[j] << ',';
//		cerr << '\n';
	}
	write(ans);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# Beautiful Subsequences 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc248_h)

### 思路

**本做法不受限于 $0\le k\le 3$**。

首先我们可以得出一个 $O(n^2)$ 的做法，先用一些数据结构帮助你快速算出区间最值，比方说 ST 表，然后枚举区间端点即可。

我们可以使用分治来优化这一过程。显然对于一个区间 $[l,r]$ **内部**的贡献，我们可以将其平均分为两个子区间 $[l,mid],[mid+1,r]$ 来算。对于两个子区间**内部**的贡献，又可以分治下去算，所以现在我们只需要处理跨区间的贡献。

我们设 $a_i,b_i$ 为 $[l,mid]$ 中距离 $mid+1$ 为 $i$ 的后缀的最大值，最小值；$c_i,d_i$ 为 $[mid+1,r]$ 中距离 $mid$ 为 $i$ 的前缀的最大值，最小值。

这时题目中给的式子就可以变成下面这样：

$$\max(a_i,c_j)-\min(b_i,d_j)\le i+j-1+k$$

不妨对于每一个 $i$，只计算满足 $a_i\ge c_j$ 的 $j$ 的答案，因为不满足的部分我们可以同时交换 $a,c$ 和 $b,d$ 再算一遍（因为 $p$ 是排列，所以事实上取不到等号，换句话说不会算重）。

现在发现式子变成这样了：

$$a_i-\min(b_i,d_j)\le i+j-1+k$$

于是我们对 $b_i,d_j$ 的大小关系分类讨论：

+ $b_i\le d_j$ 得出 $a_i-b_i\le i+j-1+k$，移项得 $a_i-b_i-i-k+1\le j$。

+ $b_i>d_j$ 得出 $a_i-d_j\le i+j+k-1$，移项得 $a_i-i-k+1\le d_j+j$。

下面我们默认 $j$ 需要满足 $c_j\le a_i$ 的要求。

不难注意到随着 $i,j$ 增加，$a_i,c_j$ 单调不降，$b_i,d_j$ 单调不增。我们设 $p$ 是最大的点使得 $d_j\ge b_i$。

所以对于第一种情况，满足条件的 $j$ 在 $p$ 之前。合法 $j$ 的个数是好求的，$p$ 是合法区间右端点，$a_i-b_i-i-k+1$ 是合法区间左端点（注意区间可能为空）。

接下来考虑如何求第二种情况造成的贡献。首先注意到满足第二种情况的 $j$ 在 $p$ 之后。

不妨设上一次满足第二种情况的 $j$ 在 $[l,r]$ 范围内，考虑这次 $l,r$ 的变化，显然两者都是单调不降的，于是我们使用双指针和树状数组维护 $[l,r]$ 内所有的 $d_j+j$ 即可。树状数组求后缀和是套路的，这里不再讲了。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 140005
#define pii pair<int,int>
#define pcc pair<char,char>
#define x first
#define y second
#define pct __builtin_popcount
#define mod 998244353
#define inf 2e18
#define pi acos(-1)
#define eps 1e-2
using namespace std;
int T=1,n,m,k,p[N],res;
vector<int>a,b,c,d;
struct bit{
	int c[N<<1];
	void add(int x,int v){
		while(x<=m){
			c[x]+=v;
			x+=x&-x;
		}
	}
	int qry(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=x&-x;
		}
		return res;
	}
}t;
int calc(int x,int y){
	int s=0;
	int s1=a.size(),s2=c.size();
	int l=1,r=0;
	for(int i=1;i<s1;i++){
		int j=upper_bound(c.begin(),c.end(),a[i])-c.begin()-1;//找到j的上界 
		if(j==0)continue;
		int L=0,R=s2-1,pos=0;
		while(L<=R){
			int mid=L+R>>1;
			if(d[mid]>=b[i]){
				L=mid+1;
				pos=mid;
			}
			else R=mid-1;
		} 
		s+=max(0ll,min(j,pos)-max(1ll,(a[i]-b[i]-i-k+1))+1);//情况1 
		while(r+1<=j){
			t.add(d[r+1]+r+1,1);
			r++;
		}
		while(l<=r&&d[l]>=b[i]){
			t.add(d[l]+l,-1);
			l++;
		}
		s+=t.qry(m)-t.qry(max(a[i]-i-k,0ll));//树状数组求后缀和，情况2 
	}
	while(l<=r){//注意清空不能memset 
		t.add(d[l]+l,-1);
		l++;
	}
	return s;
}
void work(int l,int r){
	if(l==r){
		res++;
		return;
	}
	int mid=l+r>>1;
	a.resize(mid-l+2);
	b.resize(mid-l+2);
	c.resize(r-mid+1);
	d.resize(r-mid+1);
	a[0]=c[0]=0;
	b[0]=d[0]=n+1;
	for(int i=mid;i>=l;i--){
		a[mid-i+1]=max(a[mid-i],p[i]);
		b[mid-i+1]=min(b[mid-i],p[i]);
	}
	for(int i=mid+1;i<=r;i++){
		c[i-mid]=max(c[i-mid-1],p[i]);
		d[i-mid]=min(d[i-mid-1],p[i]);
	}
	res+=calc(l,r);//这里传参是为了方便调试，事实上可以不传 
	swap(a,c);
	swap(b,d);
	res+=calc(l,r);
	work(l,mid);
	work(mid+1,r);
}
void solve(int cs){
	cin>>n>>k;
	m=n<<1;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	work(1,n);
	cout<<res<<'\n';
}
void solution(){
    /*
    nothing here
    */
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//	init();
//	cin>>T;
    for(int cs=1;cs<=T;cs++){
        solve(cs);
    }
    return 0;
}
```


### 参考资料

[学长的题解](https://www.luogu.com.cn/article/8z642b48)

---

## 作者：_LiWenX_ (赞：0)

给一个不用写任何数据结构的做法，思路是分治序列。

也就是说，对于当前考虑的区间 $[l,r]$，求出跨过分治中心 $mid$ 的答案。

由于这个 $\min,\max $ 很烦人，所以我的处理方法是直接大力分类讨论，首先是两个比较简单的情况：最小值和最大值都在左边部分取到，或者都在右半部分取到。由于两个情况本质相同，所以只考虑都在左半部分。

我们去枚举左端点 $i$，那么为了不破坏最大最小值都在左侧，右端点的范围会收到限制，具体来说，合法的右端点应该形如一个类似 $[mid+1,pos]$ 的区间。并且，这个 $pos$ 会随着 $i$ 的减小而增大，于是直接使用双指针维护 $pos$ 的具体值。

然后推一下式子，题目要求是 $\max-\min\le r-l+k$，首先注意到一点，由于这是排列，所以 $\max-\min\ge r-l$，所以问题等价于对于所有 $0\le x\le k$，求区间 $\max-\min=r-l+x$ 的个数。我们使用套路，将已知量放左边，得到 $\max-\min+l-x=r$。

发现如果我们此时枚举 $x$，可以唯一确定一个合法右端点 $r$，那么我们只用判断 $r$ 是否落在了 $[mid+1,pos]$ 中即可。

这部分的复杂度是 $O(nk\log n)$ 的，原因是分治枚举一侧的同时，还枚举了一下 $x$ 的值。

然后是钦定最大值在左半部分取到，最小值在右半部分取到的答案，（对称的问题依然本质相同，直接略过）。

依然枚举左端点 $i$，假如我们计算了 $[i,mid]$ 中的最大最小值 $maxn,minn$，发现按照我们的要求，这个最大值和最小值会分别划分出一个合法右端点的区间，表示这个区间的右端点到 $mid+1$ 的最大值不超过 $maxn$，最小值必须超过 $minn$，那么这两个区间取交必然也是一个区间，并且这两个端点在随着 $i$ 的减小也是递增的，所以依然可以双指针维护出来。

然后还是套路化的推式子：$\max-\min=r-l+x$，得到 $\max+l-x=r+\min$。由于最小值必然在右侧取到，所以设前缀最小值 $pre_p=\min\limits_{i=mid+1}^p a_i$，$\min=pre_r$，所以是 $\max+l-x=r+pre_r$，发现右侧只与 $r$ 有关，要求的其实就是区间内 $r+pre_r=\max+i-x$ 的数量，这是一个二维数点，但是没必要，因为每次询问区间的变化量是均摊 $O(1)$ 的，所以可以直接开一个桶，然后模仿莫队的写法维护桶的变化，查询就是查桶内的某个下标元素个数。这部分复杂度依然是 $O(nk\log n)$。

所以这个做法总复杂度是 $O(nk\log n)$，主要优势是没写一个数据结构，代码好写，而且可以拓展到 $k$ 很大的情况，每次查询相当于查一个区间的数的个数，这个时候就要使用数据结构维护了。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int a[300005],n;
int t[600005],pre[300005],suf[300005];
int ans=0;int K;
void solve(int l,int r){
	if(l>=r){
		if(l==r) ans++;
		return ;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	// min = l ,max = l
	int pos=mid;
	int maxn=0,minn=1e9;
	for(int i=mid;i>=l;i--){
		maxn=max(maxn,a[i]);
		minn=min(minn,a[i]);suf[i]=n+minn-i;
		while(pos+1<=r&&a[pos+1]>=minn&&a[pos+1]<=maxn) pos++;
		for(int k=0;k<=K;k++){
			int R=maxn-minn+i-k;
			if(mid<R&&R<=pos) ans++;
		}
	}
	// min = r ,max = r
	pos=mid+1;
	maxn=0,minn=1e9;
	for(int i=mid+1;i<=r;i++){
		maxn=max(maxn,a[i]);
		minn=min(minn,a[i]);pre[i]=minn+i+n;
		while(pos-1>=l&&a[pos-1]>=minn&&a[pos-1]<=maxn) pos--;
		for(int k=0;k<=K;k++){
			int L=i-maxn+minn+k;
			if(pos<=L&&L<=mid) ans++;
		}
	}
	// max = l ,min = r
	int posl=mid+1,posr=mid;
	maxn=0,minn=1e9;
	for(int i=mid;i>=l;i--){
		maxn=max(maxn,a[i]);
		minn=min(minn,a[i]);
		while(posl+1<=r&&a[posl]>minn){
			t[pre[posl]]--;
			posl++;
		}
		while(posr+1<=r&&a[posr+1]<maxn){
			posr++;
			t[pre[posr]]++;
		}
		if(a[posl]<minn){
			for(int k=0;k<=K;k++){
				if(t[maxn+i-k+n]>=0) ans+=t[maxn+i-k+n];
			}
		}
	}
	for(int i=l;i<=r;i++) t[pre[i]]=0;
	// max = r ,min = l 
	posl=mid,posr=mid+1;
	maxn=0,minn=1e9;
	for(int i=mid+1;i<=r;i++){
		maxn=max(maxn,a[i]);
		minn=min(minn,a[i]);
		while(posr-1>=l&&a[posr-1]<maxn){
			posr--;
			t[suf[posr]]++;
		}
		while(posl-1>=l&&a[posl]>minn){
			t[suf[posl]]--;
			posl--;
		}
		if(a[posl]<minn){
			for(int k=0;k<=K;k++){
				if(t[maxn-i+n-k]>=0) ans+=t[maxn-i+n-k];
			}
		}
	}
	for(int i=l;i<=r;i++) t[suf[i]]=0;
}
signed main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	solve(1,n);
	cout<<ans;
}
```

---

## 作者：Arghariza (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/rft7d5d2.png)

然而这个经典做法是分治，我不太会做，但这确实是一道经典题。

考虑扫描线，对从左到右每个点 $r$，统计以 $r$ 作为右端点的区间个数。

由于 $r$ 端点固定，$S(l)=\max\limits_{i=l}^r{P_i}-\min\limits_{i=l}^r{P_i}-r+l\ge 0$，所以只需要统计 $S(l)$ 在 $[0,k]$ 区间处的 $l$ 的个数，于是只需要维护前 $k+1$ 小值即可。由于 $k$ 比较小，可以使用线段树维护前 $k+1$ 小值。

考虑移动端点 $r$ 对 $S(l)$ 的贡献，这是个经典问题，可以用两个分别维护了最大值和最小值的单调栈做。每次的贡献就拆成若干段区间，进行区间修改即可。

复杂度 $O(nk\log k\log n)$，精细实现可以 $O(nk\log n)$。

---

