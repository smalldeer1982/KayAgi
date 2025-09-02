# [OOI 2025] Order Statistics

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

给定一个由整数组成的数组 $a_1, a_2, \ldots, a_n$，以及整数 $k$ 和 $m$。
对该数组执行以下操作 $m$ 次：

- 选出数组 $a$ 中 $k$ 个最大元素的位置 $i_1, i_2, \ldots, i_k$。如果两个元素相等，则认为数组中较早出现的元素更大。
- 将 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$ 的值各减 $1$。

对于从 $1$ 到 $n$ 的 $x$，令 $F_{m,k}(x)$ 表示对数组 $a$ 应用 $m$ 次参数为 $k$ 的操作后得到的数组中第 $x$ 个顺序统计量的值。对于从 $1$ 到 $n$ 的 $x$，数组 $a_1, a_2, \ldots, a_n$ 的第 $x$ 个顺序统计量是指如果将数组 $a$ 按非递减顺序排序后，位于位置 $x$ 的元素。

对于所有满足 $1 \le l \le r \le n$ 的 $l, r$，令 $S_{m,k}(l,r)$ 表示所有从 $l$ 到 $r$ 的整数 $x$ 的 $F_{m,k}(x)$ 之和。
更正式地：
$$
S_{m,k}(l,r)=\sum_{x=l}^r F_{m,k}(x)
$$
给定整数 $m_0$ 和 $k_0$。
你必须计算所有从 $1$ 到 $n$ 的 $x$ 的 $F_{m_0,k_0}(x)$ 的值。

之后，你必须处理 $q$ 个查询。第 $j$ 个查询（$1 \le j \le q$）可以是以下三种类型之一：

- 计算 $F_{m_j,k_j}(x_j)$ 的值。
- 将 $a_{p_j}$ 的值修改为 $v_j$。
- 计算 $S_{m_j,k_j}(l_j,r_j)$ 的值。

所有函数 $F$ 和 $S$ 的计算每次都是独立进行的，并且不会改变数组。第二种类型查询对数组的所有修改都会保留到后续查询中。

## 说明/提示

**样例解释**

在样例中，$n=8$，$m_0=3$，$k_0=2$，$q=16$。初始时，数组 $a$ 为 $[3, 1, 2, -1, 0, 2, -1, 4]$。
让我们看看如果用参数 $k_0$ 对数组应用 $m_0$ 次操作，数组会如何变化：

- 数组为 $[3,1,2,-1,0,2,-1,4]$。两个最大的元素位于位置 $1$ 和 $8$。将它们减 $1$ 后，数组变为 $[2,1,2,-1,0,2,-1,3]$。
- 数组为 $[2,1,2,-1,0,2,-1,3]$。两个最大的元素位于位置 $1$ 和 $8$。将它们减 $1$ 后，数组变为 $[1,1,2,-1,0,2,-1,2]$。
- 数组为 $[1,1,2,-1,0,2,-1,2]$。两个最大的元素位于位置 $3$ 和 $6$。将它们减 $1$ 后，数组变为 $[1,1,1,-1,0,1,-1,2]$。

我们发现，对数组 $a$ 应用 $3$ 次参数为 $2$ 的操作后，它变成了 $[1,1,1,-1,0,1,-1,2]$。如果对这个数组排序，会得到数组 $[-1,-1,0,1,1,1,1,2]$。因此，顺序统计量为 $F_{3,2}(1)=-1$，$F_{3,2}(2)=-1$，$F_{3,2}(3)=0$，$F_{3,2}(4)=1$，$F_{3,2}(5)=1$，$F_{3,2}(6)=1$，$F_{3,2}(7)=1$，$F_{3,2}(8)=2$。

在样例中，我们需要处理 $16$ 个查询；让我们详细分析前 $10$ 个查询：
- 第一个查询类型为 $t_1=3$，参数为 $m_1=3$，$k_1=2$，$l_1=2$，$r_1=6$，需要计算 $S_{3,2}(2,6)$ 的值。我们已经计算了从 $1$ 到 $8$ 的 $x$ 的 $F_{3,2}(x)$ 值，由此可以找到查询的答案：$$S_{3,2}(2,6)=F_{3,2}(2)+F_{3,2}(3)+F_{3,2}(4)+F_{3,2}(5)+F_{3,2}(6)=(-1)+0+1+1+1=2$$
- 第二个查询类型为 $t_2=1$，参数为 $m_2=3$，$k_2=2$，$x_2=4$，需要计算 $F_{3,2}(4)$ 的值。我们已经计算过，它等于 $1$。
- 第三个查询类型为 $t_3=3$，参数为 $m_3=4$，$k_3=5$，$l_3=3$，$r_3=5$，需要计算 $S_{4,5}(3,5)$ 的值，即计算对数组 $a$ 应用 $m_3=4$ 次参数为 $k_3=5$ 的操作后得到的数组中，从第三个到第五个顺序统计量的和。在第三个查询时，数组 $a$ 为 $[3, 1, 2, -1, 0, 2, -1, 4]$。五个最大的元素位于位置 $1,2,3,6,8$。将它们减 $1$，得到数组 $[2,0,1,-1,0,1,-1,3]$。再应用三次操作，得到数组 $[-1,-2,-2,-2,-1,-1,-1,0]$。排序后变为 $[-2,-2,-2,-1,-1,-1,-1,0]$。因此，查询的答案是 $$S_{4,5}(3,5)=F_{4,5}(3)+F_{4,5}(4)+F_{4,5}(5)=(-2)+(-1)+(-1)=-4$$
- 第四个查询类型为 $t_4=1$，参数为 $m_4=4$，$k_4=5$，$x_4=6$。在应用 $4$ 次参数为 $5$ 的操作并对数组 $a$ 排序后，数组将变为 $[-2,-2,-2,-1,-1,-1,-1,0]$，所以第六个顺序统计量是 $-1$。
- 第五个查询类型为 $t_5=2$，参数为 $p_5=5$ 和 $v_5=-1$。它将 $a_5$ 的值修改为 $-1$，之后数组 $a$ 变为 $[3,1,2,-1,-1,2,-1,4]$。
- 第六个查询类型为 $t_6=2$，参数为 $p_6=6$ 和 $v_6=3$。它将 $a_6$ 的值修改为 $3$，之后数组 $a$ 变为 $[3,1,2,-1,-1,3,-1,4]$。
- 第七个查询需要找到 $F_{3,2}(1)$ 的值。在第七个查询时，数组 $a$ 为 $[3,1,2,-1,-1,3,-1,4]$。应用 $3$ 次参数为 $2$ 的操作后，它将变为 $[1, 1, 1, -1, -1, 2, -1, 2]$。这个数组的第一个顺序统计量是 $-1$。
- 第八、第九和第十个查询需要找到 $F_{3,2}(3)$、$F_{3,2}(4)$ 和 $F_{3,2}(8)$ 的值，即数组 $[1, 1, 1, -1, -1, 2, -1, 2]$ 中的第三、第四和第八个顺序统计量。它们分别等于 $-1$、$1$ 和 $2$。

**说明提示**

本题的测试点包含十二个分组。每个分组的分数只有在该分组的所有测试点以及所有依赖分组的测试点都通过时才能获得。请注意，通过样例测试点对于某些分组不是必需的。**Offline-evaluation** 表示该分组的测试结果将在比赛结束后才可查看。

如果某个子任务对 $m$ 或 $k$ 有限制，那么这些限制同时适用于 $m_0$ 和 $k_0$，以及所有第一类和第三类查询的参数。

| Subtask | 分数 | 限制条件：$n$ | $m$ | $k$ | $q$ | 依赖组别 | 说明 |
| :--- | :--- | :------------- | :-- | :-- | :-- | :-------- | :---- |
| 0    | 0    | --             | --  | --  | --  | --        | 样例测试点。 |
| 1    | 4    | $n \le 1000$   | $m \le 1000$  | --  | $q=0$ | --        | -- |
| 2    | 5    | --             | --  | $k=1$  | $q=0$ | --        | -- |
| 3    | 6    | --             | --  | $k=1$  | $q \le 100\,000$ | 2  | 所有查询中 $t_j=1$。 |
| 4    | 7    | --             | --  | $k=1$  | $q \le 100\,000$ | 2, 3  | 所有查询中 $t_j \ne 3$。 |
| 5    | 11   | --             | --  | $k=2$  | $q=0$ | --        | -- |
| 6    | 9    | --             | $m \le 10^6$  | --  | $q=0$ | 1  | -- |
| 7    | 10   | $n \le 1000$   | --  | --  | $q=0$ | 1  | -- |
| 8    | 7    | --             | --  | --  | $q=0$ | 1, 2, 5 -- 7  | -- |
| 9    | 11   | --             | --  | --  | $q \le 100\,000$ | 1 -- 3, 5 -- 8 | 所有查询中 $t_j=1$。 |
| 10   | 13   | --             | --  | --  | $q \le 100\,000$ | 1 -- 3, 5 -- 9 | 所有查询中 $t_j\ne 2$。 |
| 11   | 9    | --             | --  | --  | $q \le 100\,000$ | 0 -- 10  | -- |
| 12   | 8    | --             | --  | --  | --  | 0 -- 11  | **Offline-evaluation.** |

## 样例 #1

### 输入

```
8 3 2 16
3 1 2 -1 0 2 -1 4
3 3 2 2 6
1 3 2 4
3 4 5 3 5
1 4 5 6
2 5 -1
2 6 3
1 3 2 1
1 3 2 3
1 3 2 4
1 3 2 8
1 0 5 6
2 1 5
3 1 3 7 8
3 2 3 5 8
3 3 3 4 7
3 4 3 4 7```

### 输出

```
-1 -1 0 1 1 1 1 2
2
1
-4
-1
-1
-1
1
2
3
7
8
4
2```

# 题解

## 作者：TimSwn090306 (赞：7)

思考数十分钟后仍不会 $m=10^9,q=0,n=10^5,1\le k\le n$，痛定思痛，遂作此篇。

### Description

给定序列 $a_n$，定义 $F_{m,k}(x)$ 表示每次对前 $k$ 大的值 $-1$，进行 $m$ 次后第 $x$ 大的值是多少。需要支持单点修改 $a$，查询 $\sum_{i\in[l,r]}F_{m,k}(i)$。

$m,k$ 每次询问给出。

数据范围：$1\le k\le n\le 2\times 10^5,1\le q\le 2\times 10^5,-10^9\le a_i\le 10^9,0\le m \le 10^9$。

### Solution

不妨将 $a$ 排序，问题可以转化为每次选 $k$ 个位置的值 $-1$，操作后序列仍需单调不降，重复 $m$ 次，最大化最终每个下标的前缀和。

> Proof：显然“每次选 $k$ 个位置的值 $-1$，操作后序列仍需单调不降”操作与原操作是等价的。不妨设在某次操作中，$i<j,a_i<a_j$，然而对 $a_i$ 执行 $-1$，而没有对 $a_j$ 执行 $-1$，则对于最终在 $[i,j-1]$ 前缀和会造成 $-1$ 的贡献。由于原问题中不会出现上述情况，故“最大化最终每个下标的前缀和”等价于原问题。

令 $f_i(x)$ 表示当 $a_i$ 最终变为 $x$ 时，$a_{1\thicksim i}$ 至少要减多少次 $1$；$g_i(x)$ 表示当 $a_i$ 最终变为 $x$ 时，$a_{(i+1)\thicksim n}$ 至多能减多少次 $1$。则有：

$$f_i(x)=\sum_{j=1}^i \max(a_j-x,0)$$

$$g_i(x)=\sum_{j=i+1}^n \min(a_j-x,m)$$

上述函数定义域均为 $[a_i-m,a_i]$。由于 $a$ 单调不降，$f_i(x),g_i(x)$ 可以在 $O(\log n)$ 时间内维护。

最终下标 $i$ 的最大前缀和即为 $(\sum_{j=1}^i a_j)-\min_{x\in[a_i-m,a_i]}(\max(f_i(x),mk-g_i(x)))$。由于 $f_i(x)$ 单调不增，$(mk-g_i(x))$ 单调不减，二分交点可以得出 $\min_{x\in[a_i-m,a_i]}(\max(f_i(x),mk-g_i(x)))$ 的值。

每个下标的最大前缀和可以同时取到，区间 $F_{m,k}(i)$ 的和可以通过两个最大前缀和相减得到。

单点修改 $a$ 不难用树状数组或平衡树维护，具体的，只需要支持点修，全局比某个值小的数的个数与和。

时间复杂度 $O(n\log^2 n)$，略需精细实现。

### Code

```cpp
#include <bits/stdc++.h>
#define fin(str) freopen(str,"r",stdin)
#define fout(str) freopen(str,"w",stdout)
#define ll long long
#define int long long
using namespace std;
inline int rd(){
	register int x=0,f=1; char ch=getchar();
	while (ch<'0' || ch>'9'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar('0'+(x%10));
}

bool MEM_beg;

const int maxn=4e5+5;
const ll inf=1e15+5;

struct query{
	int m,k,l,r;
}q[maxn];

int n,m0,k0,qtot,a[maxn];
ll btot,b[maxn];
ll vn;

inline int get(int x){
	return upper_bound(b+1,b+btot+1,x)-b-1;
}

struct BIT{
	ll c[maxn];
	inline int lowbit(int x) {return x&-x; }
	inline void add(int x,int k) {for (int i=x;i<=btot;i+=lowbit(i)) c[i]+=k; }
	inline ll ask(int x){
		ll res=0;
		for (int i=x;i;i-=lowbit(i)) res=res+c[i];
		return res;
	}
	inline ll all(){
		return ask(btot);
	}
}CNT,SUM;

inline int getkth(int x){
	int l=1,r=btot;
	while (l<=r){
		int mid=(l+r)>>1;
		if (CNT.ask(mid)<x) l=mid+1;
		else r=mid-1;
	}
	return b[l];
}
inline ll getsum(int id,int val,int nw){//前id小的和
	if (!id) return 0ll;
	if (val==inf) val=getkth(id);
	if (nw==-1) nw=get(val);
	ll S=SUM.ask(nw-1),C=CNT.ask(nw-1);
	return S+1ll*(id-C)*val;
}
inline ll getsum_max(int id,int val,int x,int v_nw,int x_nw){//前id小分别-x然后对0取max的和
	if (!id) return 0ll;
	if (x_nw==-1) x_nw=get(x);
	int cnt_temp=0;
	if ((cnt_temp=CNT.ask(x_nw))<=id) return (getsum(id,val,v_nw)-SUM.ask(x_nw))-(id-cnt_temp)*x;
	else return 0ll;
}
inline ll getsum_min(int id,int val,int x,int v_nw,int x_nw){//前id小分别-x然后对0取min的和
	if (!id) return 0ll;
	if (x_nw==-1) x_nw=get(x);
	int cnt_temp=0;
	if ((cnt_temp=CNT.ask(x_nw))<=id) return (SUM.ask(x_nw))-cnt_temp*x;
	else{
		return (getsum(id,val,v_nw))-1ll*id*x;
	}
}

inline bool check(int id,int val,int mid,int m,int k,int v_nw,int vn_nw,int mid_nw,int midm_nw){
	return getsum_max(id,val,mid,v_nw,mid_nw)+getsum_min(n,vn,mid+m,vn_nw,midm_nw)-getsum_min(id,val,mid+m,v_nw,midm_nw)+1ll*m*(n-id)>=1ll*m*k;
}
inline ll calc(int id,int val,int x,int m,int k,int v_nw,int vn_nw,int x_nw,int xm_nw){
	return max(1ll*m*k-(getsum_min(n,vn,x+m,vn_nw,xm_nw)-getsum_min(id,val,x+m,v_nw,xm_nw)+1ll*m*(n-id)),getsum_max(id,val,x,v_nw,x_nw));
}
inline ll solve(int id,int m,int k,int flag){
	if (id<=0) return 0;
	
	int val=getkth(id),v_nw=get(val),vn_nw=get(vn);
	ll l=val-m,r=val;
	while (l<=r){
		ll mid=(l+r)/2;
		if (check(id,val,mid,m,k,v_nw,vn_nw,get(mid),get(mid+m))) l=mid+1;
		else r=mid-1;
	}
	
	ll fin=inf; int p=-1;
	for (int i=l-1;i<=l;i++){
		if (i>=val-m && i<=val){
			ll res=calc(id,val,i,m,k,v_nw,vn_nw,get(i),get(i+m));
			if (res<fin){
				fin=res;
				p=i;
			}
		}
	}
	
	if (!flag) return getsum(id,val,v_nw)-fin;
	return p;
}

bool MEM_end;
signed main(){
	n=rd(),m0=rd(),k0=rd(),qtot=rd();
	for (int i=1;i<=n;i++){
		a[i]=rd();
		b[++btot]=a[i];
	}
	
	for (int i=1,opt;i<=qtot;i++){
		opt=rd();
		if (opt==1) q[i].m=rd(),q[i].k=rd(),q[i].l=rd(),q[i].r=q[i].l;
		else if (opt==2) q[i].l=rd(),q[i].k=rd(),q[i].r=-1,q[i].m=-1,b[++btot]=q[i].k;
		else if (opt==3) q[i].m=rd(),q[i].k=rd(),q[i].l=rd(),q[i].r=rd();
	}
	
	b[++btot]=-inf;
	b[++btot]=+inf;
	sort(b+1,b+btot+1);
	btot=unique(b+1,b+btot+1)-b-1;
	
	for (int i=1;i<=n;++i){
		int nw=get(a[i]);
		CNT.add(nw,1);
		SUM.add(nw,a[i]);
	}
	vn=getkth(n);
	
	for (int i=1;i<=n;++i) write(solve(i,m0,k0,0)-solve(i-1,m0,k0,0)),putchar(' ');
	putchar('\n');
	
	for (int i=1;i<=qtot;++i){
		if (q[i].r==-1){
			int nw=get(q[i].k),org=get(a[q[i].l]);
			CNT.add(org,-1);
			SUM.add(org,-a[q[i].l]);
			a[q[i].l]=q[i].k;
			CNT.add(nw,1);
			SUM.add(nw,a[q[i].l]);
			
			vn=getkth(n);
		}else{
			if (q[i].l!=q[i].r) write(solve(q[i].r,q[i].m,q[i].k,0)-solve(q[i].l-1,q[i].m,q[i].k,0));
			else write(solve(q[i].r,q[i].m,q[i].k,1));
			putchar('\n');
		}
	}
	
	cerr<<"\nMemory : "<<1.0*abs(&MEM_end-&MEM_beg)/1048576<<" MB\n";
	return 0;
}
```

---

## 作者：Edward2019 (赞：5)

- 题目中的过程等价于：重复 $ mk $ 次，每次选择最大的还未被选择 $ m $ 次的数，将其减少 1。
- 最后的数列一定形如：最小的一些数不变，之后一段 $ t - 1 $ 和一段 $ t $，最大的若干个数减少 $ m $，且减少后 $ \geq t $。
- 二分 $ t $ 的值，用树状数组求出能减少的次数。然后求出上述的段，就能回答所有询问。
- 时间复杂度 $ O((n + q) \log^2 n) $。


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
const int N=4e5+10;
struct BIT{
	int tr[N];
	inline void add(int x,int y){for(;x<N;x+=x&-x)tr[x]+=y;}
	inline int get(int x){int sum=0;for(;x;x-=x&-x)sum+=tr[x];return sum;}
	inline int query(int l,int r){l=max(l,1ll);if(l>r)return 0;return get(r)-get(l-1);}
}cnt,val;
int n,a[N],q,op[N],m[N],k[N],l[N],r[N],to[N],cn;
inline int chk(int t,int m){
	int u=upper_bound(to+1,to+1+cn,t+m)-to,v=lower_bound(to+1,to+1+cn,t)-to;
	return m*cnt.query(u,cn)+val.query(v,u-1)-t*cnt.query(v,u-1);
}
inline int query(int l,int r,int d){
	if(l>r)return 0;
	int L=l,R=r+1;
	while(L<R){
		int mid=(L+R+1)>>1;
		if(cnt.query(mid,r)<d)R=mid-1;
		else L=mid;
	}
	return val.query(L,r)+to[L]*(d-cnt.query(L,r));
}
inline int solve(int t,int m,int mlen,int q){
	if(!q)return 0;
	int ans=0,u=upper_bound(to+1,to+1+cn,t+m)-to;
	int x=cnt.query(u,cn);
	if(x<q)ans+=val.query(u,cn)-m*cnt.query(u,cn),q-=x;
	else{
		ans+=query(u,cn,q)-m*q;
		return ans;
	}u--;
	int v=lower_bound(to+1,to+1+cn,t-1)-to;
	x=cnt.query(v,u);
	if(x<q)ans+=(t-1)*(x-mlen)+t*mlen,q-=x;
	else{
		if(q<=mlen)ans+=t*q;
		else ans+=(t-1)*(q-mlen)+t*mlen;
		return ans;
	}
	return ans+query(1,v-1,q);
}
inline int work(int m,int k,int ql,int qr){
	int l=-2e9,r=to[cn];
	while(l<r){
		int t=(l+r)>>1;
		if(chk(t,m)>m*k)l=t+1;
		else r=t;
	}
	int t=l,mlen=chk(t-1,m+1)-m*k-chk(t+m,1);
	return solve(t,m,mlen,n-ql+1)-solve(t,m,mlen,n-qr);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m[0]>>k[0]>>q;
	for(int i=1;i<=n;i++)cin>>a[i],to[++cn]=a[i];
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1)cin>>m[i]>>k[i]>>l[i],r[i]=l[i];
		if(op[i]==2)cin>>m[i]>>k[i],to[++cn]=k[i];
		if(op[i]==3)cin>>m[i]>>k[i]>>l[i]>>r[i];
	}
	sort(to+1,to+1+cn),cn=unique(to+1,to+1+cn)-to-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(to+1,to+1+cn,a[i])-to;
	for(int i=1;i<=q;i++)if(op[i]==2)k[i]=lower_bound(to+1,to+1+cn,k[i])-to;
	for(int i=1;i<=n;i++)cnt.add(a[i],1),val.add(a[i],to[a[i]]);
	for(int i=1;i<=n;i++)cout<<work(m[0],k[0],i,i)<<" ";cout<<"\n";
	for(int i=1;i<=q;i++){
		if(op[i]==2)cnt.add(a[m[i]],-1),val.add(a[m[i]],-to[a[m[i]]]),a[m[i]]=k[i],cnt.add(a[m[i]],1),val.add(a[m[i]],to[a[m[i]]]);
		else cout<<work(m[i],k[i],l[i],r[i])<<"\n";
	}
	return 0;
}
```

---

