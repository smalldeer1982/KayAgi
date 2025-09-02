# 『STA - R5』ReLyna

## 题目背景

![](https://pic.imgdb.cn/item/661a29dd68eb93571321ac89.webp)

## 题目描述

你手中有一个数字 $x$。走到位置 $i$ 时你可以将手中的数字变为 $x+a_i$ 或 $x\times b_i$。

有 $m$ 次操作。

- `1 x y z`，执行 $a_x\gets y$，$b_x\gets z$。

- `2 l r`，查询若你从 $[l,r]$ 的所有子区间中等概率选择一个子区间 $[l',r']$，则你从 $l'$ 走到 $r'$ 后手中的数的最大值的期望是多少？答案对 $10^9+7$ 取模。每次行动开始前你手中的数字都会归零。

如果你不知道有理数如何取模，可以参考 [P2613 有理数取余](https://www.luogu.com.cn/problem/P2613)。

可参考样例解释理解题意。

## 说明/提示

**样例解释**

对于第一次询问，令 $f(i,j)$ 为你从 $i$ 开始顺次走到 $j$ 后手中的数的最大值，则答案为 $\frac{1}{3}[f(2,2)+f(2,3)+f(3,3)]=\frac{1}{3}(52+156+8)=72$。

**数据范围**

| 子任务编号 | $n$ | $m$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Subtask #1 | $50$ | $50$ | 无 | 5 |
| Subtask #2 | $500$ | $500$ | 无 | 5 |
| Subtask #3 | $10^5$ | $10^5$ | 保证任何时刻 $a_i=1$ | 25 |
| Subtask #4 | $10^5$ | $50$ | 无 | 25 |
| Subtask #5 | $10^5$ | $10^5$ | 没有修改操作 | 25 |
| Subtask #6 | $10^5$ | $10^5$ | 无 | 15 |

对于所有数据，$1\le n,m\le 10^5$，$0<a_i<10^9+7$，$1<b_i<10^9+7$，保证操作合法，保证所有输入均为整数。

## 样例 #1

### 输入

```
5 4
48 52 8 27 34 
3 4 3 2 2 
2 2 3
2 1 5
1 1 34 4
2 1 3
```

### 输出

```
72
133333711
333333468```

# 题解

## 作者：Nopain (赞：6)

先将求期望转为求和，最后除掉方案数。

### 算法 1

我们发现每次贪心选择收益最大的即使最优方案。因为我们可以将后续的选择视为若干一次函数的嵌套，其结果仍是一次函数，且斜率截距均 $\ge 0$。所以对于任意操作形成的函数，设其为 $f(x)=kx+b\ (k,b\ge 0)$，若 $x_1>x_2$ 则 $kx_1+b>kx_2+b$。所以贪心即是最优策略。

基于上述观察，我们可以在 $O(n)$ 的时间内计算任意 $f(i,j)$，解决本题时间复杂度为 $O(mn^3)$ 或 $O(mn^2)$，可以获得 5 或 10 分。

### 算法 2

基于贪心原则，我们发现在 $a_i=1$ 时除第一个操作选择加法，其余时刻均选择乘法一定不劣。于是可以将暴力改为扫描 $i$，维护 $sum_i=\sum\limits_{j=l}^i f(j,i)$。注意到 $sum_i=sum_{i-1}\times b_i+1$，可以使用矩阵乘法快速维护，于是可以在 $O(\log n)$ 的时间内回答一次询问，结合算法 1 可以获得 35 分。

### 算法 3

修改和询问数很少，这要求我们在低于 $O(n^2)$ 的复杂度回答询问。我们考虑扫描 $i$，维护 $\sum\limits_{j=l}^i f(j,i)$。注意到 $\forall j,\ f(j,i)> f(j+1,i)$，于是我们发现一定存在一个位置 $p$，使得 $p$ 之前均选择乘法， $p$ 及以后均选择加法。这启发我们使用线段树维护 $f(j,i)$，利用不等式 $a_i+f(j,i)>b_i\times f(j,i)$ 二分得到位置 $p$。该线段树需要支持区间加/乘，维护区间 max 的真实值而非取模后的值，维护全局和。一次询问的复杂度降为 $O(n\log n)$，总复杂度为 $O(mn\log n)$。结合算法 1，2 可以获得 60 分。

在实现细节上，注意到 $a_i+mod<b_i\times mod$ 恒成立，所以线段树维护 max 时可以维护其与 mod 的 min，不影响二分结果。

### 算法 4

没有修改操作启发我们通过预处理信息拼出答案。我们注意到在经过至多 $L=1+\lceil log_2\ mod\rceil$ 次操作后一定会选择乘法。因为选择 $L$ 次乘法后，$f(i,j)$ 至少为 $2^L > mod$，所以 $a_i+f(i,j)<b_i\times f(i,j)$ 恒成立。这启发我们对 $len=i-j+1$ 的长度进行分类讨论：

$len\le L$ 时，利用算法 1 或 3 预处理 $s_i=\sum\limits_{j=\max(1,i-L+1)}^i f(j,i)$，查询时查询 $\sum\limits_{i=l}^{l+B-1}\sum\limits_{j=i}^{l+B-1}f(i,j)+\sum\limits_{k=l+B}^r s_k$ 即可。复杂度为 $O(mL^2)$ 或 $O(mL\log L)$。

$len>L$ 时，因为其一定会选择乘法，我们仿照算法 2，利用算法 1 预处理 $e_i=f(i-L,i)$，维护 $sum_i=\sum\limits_{j=l}^i f(j,i)$，有 $sum_i=sum_{i-1}\times b_i+e_i$，可以使用矩阵乘法加速。复杂度为 $O(mL+m\log n)$，总复杂度为 $O(mL^2)$ 或 $O(mL\log L)$。结合算法 1，2，3，4 可以获得 85 分。

### 算法 5

该部分与正解没有关系，但该做法是 Subtask #5 的最优做法。

没有修改操作，考虑将询问离线并使用扫描线求解。我们沿用算法 3 的核心，扫描到 $i$ 时使用线段树维护 $f(j,i)$，此时我们还需要在算法 3 的基础上维护区间历史和。可以在线段树上利用矩阵维护当前和及历史和，所有线段树修改操作均可以使用矩阵乘法表示，时间复杂度为 $O(m\log n)$，可以获得 85 分。

### 算法 6

我们沿用算法 4 的分讨思路，考虑修改会对哪些预处理信息产生影响，发现我们只需要重新计算 $s_i,e_i$ 即可。我们发现单点修改只会影响其及以后 $L$ 个点的 $s_i,e_i$，于是使用算法 1 暴力重新计算即可，每次维护完成后朴素的执行 $L$ 次线段树单点修改。时间复杂度为 $O(mL^2)$，常数极小，可以获得 100 分。以下为参考代码：

```
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define B 31
#define ll long long
const int mod=1e9+7;
int n,m,a[N],b[N],s[N],e[N];
struct mat{ll a[3][3];} st;
mat operator*(const mat &a,const mat &b){
	mat c;memset(c.a,0,sizeof c.a);
	for(int i=0;i<=2;++i) for(int j=0;j<=2;++j) for(int k=0;k<=2;++k) (c.a[i][j]+=a.a[i][k]*b.a[k][j])%=mod;
	return c;
}
mat operator&(const mat &a,const mat &b){
	mat c;memset(c.a,0,sizeof c.a);
	for(int j=0;j<=2;++j) for(int k=0;k<=2;++k) (c.a[0][j]+=a.a[0][k]*b.a[k][j])%=mod;
	return c;
}
namespace sgt{
	mat t[N<<2];
	void build(int p,int l,int r,int ql,int qr){
		int mid=(l+r)>>1;
		if(ql<=l&&r<=qr){
			if(l==r){
				t[p].a[0][0]=t[p].a[0][1]=b[l],t[p].a[1][1]=t[p].a[2][2]=1,t[p].a[2][0]=e[l];
				return;
			}
			build(p<<1,l,mid,ql,qr),build(p<<1|1,mid+1,r,ql,qr);
		}else{
			if(ql<=mid) build(p<<1,l,mid,ql,qr);
			if(qr>mid) build(p<<1|1,mid+1,r,ql,qr);	
		} t[p]=t[p<<1]*t[p<<1|1];
	}
	mat query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p];
		int mid=(l+r)>>1;
		if(qr<=mid) return query(p<<1,l,mid,ql,qr);
		if(ql>mid) return query(p<<1|1,mid+1,r,ql,qr);
		return query(p<<1,l,mid,ql,qr)*query(p<<1|1,mid+1,r,ql,qr);
	}	
}
namespace Sgt{
	int t[N<<2];
	void build(int p,int l,int r,int ql,int qr){
		int mid=(l+r)>>1;
		if(ql<=l&&r<=qr){
			if(l==r){t[p]=s[l];return;}
			build(p<<1,l,mid,ql,qr),build(p<<1|1,mid+1,r,ql,qr);
		}else{
			if(ql<=mid) build(p<<1,l,mid,ql,qr);
			if(qr>mid) build(p<<1|1,mid+1,r,ql,qr);
		}
		t[p]=(t[p<<1]+t[p<<1|1])%mod;
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p];
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid) ans=query(p<<1,l,mid,ql,qr);
		if(qr>mid) ans+=query(p<<1|1,mid+1,r,ql,qr);
		return ans%mod;
	}
}
inline int calc(int l,int r){
	int ans=0;
	for(int i=l,fl;i<=r;++i){
		ll cur=0;fl=0;
		for(int j=i;j<=r;++j){
			if(fl) (cur*=b[j])%=mod;
			else{
				cur=max(cur+a[j],cur*b[j]);
				if(cur>=mod) cur%=mod,fl=1;
			}
			(ans+=cur)%=mod;
		}
	} return ans;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1,j,fl;i<=n;++i){
		ll cur=0;fl=0;
		for(int l=1;l<=B;++l){
			j=i+l-1;
			if(j>n) break;
			if(fl) (cur*=b[j])%=mod;
			else{
				cur=max(cur+a[j],cur*b[j]);
				if(cur>=mod) cur%=mod,fl=1;
			}
			(s[j]+=cur)%=mod;
			if(l==B) e[j]=cur;
		}
	} sgt::build(1,1,n,1,n),Sgt::build(1,1,n,1,n);
	st.a[0][2]=1;
	for(int op,x,y,z,out;m--;){
		cin>>op>>x>>y;
		if(op==1){
			cin>>z;
			for(int i=max(1,x-B+1),j,fl;i<=x;++i){
				ll cur=0;fl=0;
				for(int l=1;l<=B;++l){
					j=i+l-1;
					if(j>n) break;
					if(fl) (cur*=b[j])%=mod;
					else{
						cur=max(cur+a[j],cur*b[j]);
						if(cur>=mod) cur%=mod,fl=1;
					}
					(s[j]+=mod-cur)%=mod;
				}
			}
			a[x]=y,b[x]=z;
			for(int i=max(1,x-B+1),j,fl;i<=x;++i){
				ll cur=0;fl=0;
				for(int l=1;l<=B;++l){
					j=i+l-1;
					if(j>n) break;
					if(fl) (cur*=b[j])%=mod;
					else{
						cur=max(cur+a[j],cur*b[j]);
						if(cur>=mod) cur%=mod,fl=1;
					}
					(s[j]+=cur)%=mod;
					if(l==B) e[j]=cur;
				}
			} sgt::build(1,1,n,x,min(n,x+B-1)),Sgt::build(1,1,n,x,min(n,x+B-1));
		}else{
			if(y-x+1<B) cout<<calc(x,y)<<'\n';
			else{
				out=(calc(x,x+B-2)+Sgt::query(1,1,n,x+B-1,y))%mod;
				out+=(st&sgt::query(1,1,n,x+B-1,y)).a[0][1]%mod;
				cout<<out%mod<<'\n';
			}
		}
	}
}
```

### 算法 7

我们考虑在算法 6 的基础上进一步优化，发现瓶颈有三处，分别为计算 $\sum\limits_{i=l}^{l+B-1}\sum\limits_{j=i}^{l+B-1}f(i,j)$，重新计算 $s_i,e_i$ 和在线段树上执行 $L$ 次**连续的**单点修改。

对于计算 $\sum\limits_{i=l}^{l+B-1}\sum\limits_{j=i}^{l+B-1}f(i,j)$ 和重计算 $s_i,e_i$，其核心是类似的，我们使用算法 3 即可。单次操作复杂度降为 $O(L\log L)$。

对于最后一处瓶颈，我们可以将 $L$ 次修改一起执行。具体的，先在线段树上将区间分解为线段树维护的区间，然后从这些区间向下暴力重构整个子树。这里的复杂度为 $O(\log n+L)$。

证明：找到线段树区间分解的复杂度为 $O(\log n)$。线段树的任一子树还是线段树，而线段树的节点个数与其维护的区间长度同级，所以这几个子树节点个数和与 $L$ 同级，故复杂度为 $O(\log n+L)$。

至此，我们以 $O(mL\log L)$ 的时间复杂度解决了该问题，可以获得 60 或 100 分。因为这玩意常数太大了。以下是参考代码。

```
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define B 31
#define ll long long
const int mod=1e9+7;
int n,m,a[N],b[N],s[N],e[N];
struct mat{ll a[3][3];} st;
mat operator*(const mat &a,const mat &b){
	mat c;memset(c.a,0,sizeof c.a);
	for(int i=0;i<=2;++i) for(int j=0;j<=2;++j) for(int k=0;k<=2;++k) (c.a[i][j]+=a.a[i][k]*b.a[k][j])%=mod;
	return c;
}
mat operator&(const mat &a,const mat &b){
	mat c;memset(c.a,0,sizeof c.a);
	for(int j=0;j<=2;++j) for(int k=0;k<=2;++k) (c.a[0][j]+=a.a[0][k]*b.a[k][j])%=mod;
	return c;
}
namespace sgt{
	mat t[N<<2];
	void build(int p,int l,int r,int ql,int qr){
		int mid=(l+r)>>1;
		if(ql<=l&&r<=qr){
			if(l==r){
				t[p].a[0][0]=t[p].a[0][1]=b[l],t[p].a[1][1]=t[p].a[2][2]=1,t[p].a[2][0]=e[l];
				return;
			}
			build(p<<1,l,mid,ql,qr),build(p<<1|1,mid+1,r,ql,qr);
		}else{
			if(ql<=mid) build(p<<1,l,mid,ql,qr);
			if(qr>mid) build(p<<1|1,mid+1,r,ql,qr);	
		} t[p]=t[p<<1]*t[p<<1|1];
	}
	mat query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p];
		int mid=(l+r)>>1;
		if(qr<=mid) return query(p<<1,l,mid,ql,qr);
		if(ql>mid) return query(p<<1|1,mid+1,r,ql,qr);
		return query(p<<1,l,mid,ql,qr)*query(p<<1|1,mid+1,r,ql,qr);
	}	
}
namespace Sgt{
	int t[N<<2];
	void build(int p,int l,int r,int ql,int qr){
		int mid=(l+r)>>1;
		if(ql<=l&&r<=qr){
			if(l==r){t[p]=s[l];return;}
			build(p<<1,l,mid,ql,qr),build(p<<1|1,mid+1,r,ql,qr);
		}else{
			if(ql<=mid) build(p<<1,l,mid,ql,qr);
			if(qr>mid) build(p<<1|1,mid+1,r,ql,qr);
		}
		t[p]=(t[p<<1]+t[p<<1|1])%mod;
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p];
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid) ans=query(p<<1,l,mid,ql,qr);
		if(qr>mid) ans+=query(p<<1|1,mid+1,r,ql,qr);
		return ans%mod;
	}
}
namespace Seg{
	struct node{ll mx,t,mul,add,ma,mm;} a[N<<2];
	void build(int p,int l,int r){
		a[p].mul=a[p].mm=1,a[p].ma=a[p].add=a[p].mx=a[p].t=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	}
	inline void pushdown(int p,int l,int r){
		int mid=(l+r)>>1;
		a[p<<1].add=(a[p<<1].add*a[p].mul+a[p].add)%mod,a[p<<1].mul=a[p<<1].mul*a[p].mul%mod;
		a[p<<1|1].add=(a[p<<1|1].add*a[p].mul+a[p].add)%mod,a[p<<1|1].mul=a[p<<1|1].mul*a[p].mul%mod;
		a[p<<1].mx=min((ll)mod,a[p<<1].mx*a[p].mm+a[p].ma),a[p<<1|1].mx=min((ll)mod,a[p<<1|1].mx*a[p].mm+a[p].ma);
		a[p<<1].ma=min((ll)mod,a[p<<1].ma*a[p].mm+a[p].ma),a[p<<1].mm=min((ll)mod,a[p<<1].mm*a[p].mm);
		a[p<<1|1].ma=min((ll)mod,a[p<<1|1].ma*a[p].mm+a[p].ma),a[p<<1|1].mm=min((ll)mod,a[p<<1|1].mm*a[p].mm);
		a[p<<1].t=(a[p<<1].t*a[p].mul+1ll*(mid-l+1)*a[p].add)%mod;
		a[p<<1|1].t=(a[p<<1|1].t*a[p].mul+1ll*(r-mid)*a[p].add)%mod;
		a[p].add=a[p].ma=0,a[p].mul=a[p].mm=1;
	}
	inline void update(int p){a[p].t=(a[p<<1].t+a[p<<1|1].t)%mod,a[p].mx=max(a[p<<1].mx,a[p<<1|1].mx);}
	void modify(int p,int l,int r,int ql,int qr,int v,int op){
		if(ql<=l&&r<=qr){
			if(op==1) a[p].mx=min(a[p].mx+v,(ll)mod),a[p].add=(a[p].add+v)%mod,a[p].t=(a[p].t+1ll*(r-l+1)*v)%mod,a[p].ma=min((ll)mod,a[p].ma+v);
			else a[p].mx=min(a[p].mx*v,(ll)mod),a[p].add=(a[p].add*v)%mod,a[p].mul=a[p].mul*v%mod,a[p].t=a[p].t*v%mod,a[p].ma=min((ll)mod,a[p].ma*v),a[p].mm=min((ll)mod,a[p].mm*v);
			return;
		} pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(ql<=mid) modify(p<<1,l,mid,ql,qr,v,op);
		if(qr>mid) modify(p<<1|1,mid+1,r,ql,qr,v,op);
		update(p);
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return a[p].t;
		pushdown(p,l,r);
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid) ans=query(p<<1,l,mid,ql,qr);
		if(qr>mid) ans+=query(p<<1|1,mid+1,r,ql,qr);
		return ans%mod;
	}
	int find(int p,int l,int r,int v){
		if(l==r) return l;
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(a[p<<1|1].mx>=v) return find(p<<1|1,mid+1,r,v);
		return find(p<<1,l,mid,v);
	}
}
inline int calc(int l,int r){
	ll ans=0;
	Seg::build(1,l-1,r);
	Seg::modify(1,l-1,r,l-1,l-1,mod,1);
	for(int i=l,p;i<=r;++i){
		p=Seg::find(1,l-1,r,ceil(1.0*a[i]/(b[i]-1)));
		if(p>=l) Seg::modify(1,l-1,r,l,p,b[i],0);
		Seg::modify(1,l-1,r,p+1,i,a[i],1);
		ans=(ans+Seg::query(1,l-1,r,l-1,r))%mod;
	} return ans%mod;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1,j,fl;i<=n;++i){
		ll cur=0;fl=0;
		for(int l=1;l<=B;++l){
			j=i+l-1;
			if(j>n) break;
			if(fl) cur=cur*b[j]%mod;
			else{
				cur=max(cur+a[j],cur*b[j]);
				if(cur>=mod) cur%=mod,fl=1;
			}
			s[j]=(s[j]+cur)%mod;
			if(l==B) e[j]=cur;
		}
	} sgt::build(1,1,n,1,n),Sgt::build(1,1,n,1,n);
	st.a[0][2]=1;
	ll out;
	for(int op,x,y,z,l,r;m--;){
		cin>>op>>x>>y;
		if(op==1){
			cin>>z;
			l=max(1,x-B+1),r=min(n,x+B-1);
			Seg::build(1,l-1,r);
			Seg::modify(1,l-1,r,l-1,l-1,mod,1);
			for(int i=l,p;i<=r;++i){
				p=Seg::find(1,l-1,r,ceil(1.0*a[i]/(b[i]-1)));
				if(p>=l) Seg::modify(1,l-1,r,l,p,b[i],0);
				Seg::modify(1,l-1,r,p+1,i,a[i],1);
				if(i>=x) s[i]=(s[i]+mod-Seg::query(1,l-1,r,max(1,i-B+1),i))%mod;
			}
			a[x]=y,b[x]=z;
			Seg::build(1,l-1,r);
			Seg::modify(1,l-1,r,l-1,l-1,mod,1);
			for(int i=l,p;i<=r;++i){
				p=Seg::find(1,l-1,r,ceil(1.0*a[i]/(b[i]-1)));
				if(p>=l) Seg::modify(1,l-1,r,l,p,b[i],0);
				Seg::modify(1,l-1,r,p+1,i,a[i],1);
				if(i>=x){
					s[i]=(s[i]+Seg::query(1,l-1,r,max(1,i-B+1),i))%mod;
					if(i>=B) e[i]=Seg::query(1,l-1,r,i-B+1,i-B+1);
				}
			}
			sgt::build(1,1,n,x,min(n,x+B-1)),Sgt::build(1,1,n,x,min(n,x+B-1));
		}else{
			if(y-x+1<B) cout<<calc(x,y)<<'\n';
			else{
				out=calc(x,x+B-2)+Sgt::query(1,1,n,x+B-1,y)+(st&sgt::query(1,1,n,x+B-1,y)).a[0][1];
				cout<<out%mod<<'\n';
			}
		}
	}
}
```

### 琐记

本题开 5s 的原因纯纯因为算法 7 太慢，需要跑 4.5s。但实际上对于 $n,m=3\times 10^5$ 的数据算法 6 都能在 2s 内通过。为了让写正解的选手（真的有吗）可以通过，我开小了数据，毕竟哪有卡正解放错解的。

唉实在不会卡错解放正解，如果有高手能优化正解的实现，卡卡常数，欢迎私信我接受我的膜拜。

---

## 作者：Miss_SGT (赞：2)

~~为什么暴力剪枝有 35 分。~~

期望转求和。

因为 $a_i \ge 1$ 且 $b_i \ge 2$，所以在往右走了 $\ge \log V$ 次后一定全是乘法。所以我们将原序列每 $B(B\ge 30)$ 个数分成一块在，这样一个数的加法就只在相邻两个块里。

询问时，我们对于边界的块暴力做，中间的暴力跳。修改时暴力重构相邻两个块即可。大概需要对于每一个块预处理系数和、答案和、乘积。

时间复杂度是 $O(\frac{nm}{B} + mB^2)$ 的，实测 $B \in [30,64]$ 都可以在 $700ms$ 内轻松通过。官方题解好像就是把中间暴力跳块改成用线段树。

代码极短：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mod=1e9+7,B=64;
int n,m,a[N],b[N];
int mulk[N],ansk[N],sk[N],sumk[N],L[N],R[N];
inline void Mod(int &x){return (x>=mod)&&(x-=mod),void();}
int sufs[N],sufm[N];
inline pair<int,int> BL(int l,int mid,int r){
	int mul=1,ans=0,sum=0;
	sufs[r+1]=0,sufm[r+1]=1;
	for(int i=r;i>=l;--i) sufm[i]=1ll*sufm[i+1]*b[i]%mod,sufs[i]=1ll*(sufs[i+1]+1)*b[i]%mod;
	for(int i=l;i<=mid;++i){
		long long x=0;
		bool flag=1;
		for(int j=i;j<=r;++j){
			x=max(x+a[j],x*b[j]);
			if(x>=mod){
				Mod(ans+=x%mod*(1+sufs[j+1])%mod);
				Mod(sum+=x%mod*sufm[j+1]%mod);
				flag=0;break;
			}
			Mod(ans+=x);
		}
		if(flag) Mod(sum+=x);
	}
	return {ans,sum};
}
inline int query(int l,int r){
	const int kl=l>>5,kr=r>>5;
	if(kr-kl<=1) return BL(l,r,r).first;
	auto p=BL(l,R[kl],R[kl+1]);
	int ans=p.first,sum=p.second;
	for(int i=kl+2;i<kr;++i){
		ans=(1ll*sum*sk[i]+ans+ansk[i-1])%mod;
		sum=(1ll*sum*mulk[i]+sumk[i-1])%mod;
	}
	for(int i=L[kr];i<=r;++i) sum=1ll*sum*b[i]%mod,Mod(ans+=sum);
	return (ans+BL(L[kr-1],r,r).first)%mod;
}
inline void change(int i){
	auto p=BL(L[i],R[i],R[min(i+1,n>>5)]);
	ansk[i]=p.first,sumk[i]=p.second;
	mulk[i]=1,sk[i]=0;
	for(int j=R[i];j>=L[i];--j) mulk[i]=1ll*mulk[i]*b[j]%mod,sk[i]=1ll*(sk[i]+1)*b[j]%mod;
}
inline int Inv(int x){
	int ans=1;
	for(int y=mod-2;y;y>>=1,x=1ll*x*x%mod)
		if(y&1) ans=1ll*ans*x%mod;
	return ans;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i) cin>>b[i];
	for(int i=1;i<=n;++i){
		if(!L[i>>5]) L[i>>5]=i;
		R[i>>5]=i;
	}
	for(int i=0;i<=(n>>5);++i) change(i);
	while(m--){
		int op;cin>>op;
		if(op==1){
			int x;
			cin>>x>>a[x]>>b[x];
			change(x>>5);
			if(x>>5) change((x>>5)-1);
		}else{
			int l,r;
			cin>>l>>r;
			cout<<1ll*query(l,r)*Inv(1ll*(1+r-l+1)*(r-l+1)/2%mod)%mod<<'\n';
		}
	}
	return 0;
}
```

---

