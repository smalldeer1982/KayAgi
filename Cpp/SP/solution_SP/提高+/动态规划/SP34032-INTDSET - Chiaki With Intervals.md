# INTDSET - Chiaki With Intervals

## 题目描述

给你一个有 $n$ 个区间的集合 $A$，求有多少个子集 $S$ 满足条件：任意区间 $a \in A$ 且 $a \notin S$ 均与 $S$ 的至少一个子集有交集。

答案对 $10^9+7$ 取模。

注意 $A$ 本身是一个合法的答案。

## 样例 #1

### 输入

```
2
3
1 2
3 4
5 6
3
1 4
2 4
3 4```

### 输出

```
1
7```

# 题解

## 作者：Mr_Az (赞：4)

# [SP34032 INTDSET - Chiaki With Intervals](https://www.luogu.com.cn/problem/SP34032)

## Solution:

[简单版本](https://www.luogu.com.cn/problem/SP34063)

题意：在一些区间中选择一些区间，使得其余区间均有与被选择的区间有交。

首先将所有的区间按照右端点从小到大排序，依次选择。

考虑 DP，设计 DP 状态 $dp_{i,j}$ 表示当前已经考虑了前 $i$ 个区间，与 $1-j$ 区间均有交的方案数。

考虑转移，如果当前第 $i$ 个区间不选择，则 $dp_{i,j} \leftarrow dp_{i-1,j}$。

如果选择第 $i$ 个区间，我们考虑该区间往左边和往右边最远的与其有交的区间，记作 $L_i,R_i$，这个东西分别可以通过二分和双指针简单处理得到。那么转移就为：
$$
\begin{cases}
dp_{i,R_i} \leftarrow \displaystyle\sum_{j \in [L_i-1,n]} dp_{i-1,j}\\
dp_{i,j} \leftarrow dp_{i-1,j}(j \notin [L_i-1,n])
\end{cases}
$$
第一个转移很好理解，在这个区间里的 $k$ 在经过选择了第 $i$ 个区间后可以直接转移到第 $R_i$ 个区间，反之，选择了之后中间仍有空缺，所以有效的部分仍然还是在 $k$，但是这与上面不选择是两种情况，所以相当于 $\times 2$。

线段树维护第二维即可，只需要支持单点加，区间 $\times 2$，区间查询和即可。

## Code:

```cpp
const int N=2e5+8,mod=1e9+7;
int n;
int two[N],L[N],R[N];
struct seq{int l,r;}a[N];
struct tree{
	int x,lazy;
	#define x(p) t[p].x
	#define lazy(p) t[p].lazy
}t[N*4];
#define mid (l+r>>1)
inline int md(int x){
	if(x<0) return x+mod;
	if(x>=mod) return x-mod;
	return x;
}
void build(int p,int l,int r){
	x(p)=lazy(p)=0;
	if(l==r) return ;
	build(ls,l,mid);build(rs,mid+1,r);
}
inline void update(int p){x(p)=md(x(ls)+x(rs));}
inline void spread(int p){
	if(lazy(p)){
		x(ls)=x(ls)*two[lazy(p)]%mod;
		x(rs)=x(rs)*two[lazy(p)]%mod;
		lazy(ls)+=lazy(p);
		lazy(rs)+=lazy(p);
		lazy(p)=0;
	}
	return ;
}
void add(int p,int l,int r,int pos,int k){
	if(l==r&&l==pos){x(p)=md(x(p)+k);return ;}
	spread(p);
	if(pos<=mid) add(ls,l,mid,pos,k);
	else add(rs,mid+1,r,pos,k);
	update(p);
	return ;
}
void mul(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R){x(p)=md(x(p)*2),lazy(p)++;return ;}
	spread(p);
	if(L<=mid) mul(ls,l,mid,L,R);
	if(R>mid)  mul(rs,mid+1,r,L,R);
	update(p);
	return ;	
}
int ask(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R) return x(p);
	spread(p);
	int res=0;
	if(L<=mid) res=md(res+ask(ls,l,mid,L,R));
	if(R>mid)  res=md(res+ask(rs,mid+1,r,L,R));
	return res;
}
#undef mid
int T;
inline void solve(){
	read(n);
	for(rint i=1;i<=n;i++) read(a[i].l,a[i].r);
	build(1,0,n);
	sort(a+1,a+n+1,[](seq A,seq B){return A.r<B.r;});
	for(rint i=1;i<=n;i++){
		int l=1,r=i;
		while(l<r){
			int mid=(l+r)>>1;
			if(a[mid].r>=a[i].l) r=mid;
			else l=mid+1;
		}
		L[i]=l;
	}
	for(int i=1,j=1;i<=n;i++){
		while(j<n&&a[j+1].l<=a[i].r) j++;
		R[i]=j;
	}
	add(1,0,n,0,1);
	for(rint i=1;i<=n;i++){
		add(1,0,n,R[i],ask(1,0,n,L[i]-1,n));
		if(L[i]>1) mul(1,0,n,0,L[i]-2);
	}
	cout<<ask(1,0,n,n,n)<<endl;
}
signed main(){
	two[0]=1;
	for(rint i=1;i<=N-8;i++) two[i]=md(two[i-1]*2);
	read(T);
	while(T--) solve();
	return 0;
}
```

---

