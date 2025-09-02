# [JOI 2021 Final] 雪球 / Snowball

## 题目描述

在一条无限长的数轴上，有 $N$ 个雪球，这 $N$ 个雪球编号为 $1 \sim N$，第 $i$ 个雪球在第 $A_i$ 个点上。刚开始，整条数轴覆盖满了雪，接下来 $Q$ 天将会刮起大风，第 $j$ 天的风力强度为 $W_j$，如果 $W_j$ 为正数，所有雪球都朝右移动 $W_j$ 个单位长度，如果 $W_j$ 为负数，所有雪球都朝左移动 $-W_j$ 个单位长度。

当一个区间 $[a,a+1]$ 被雪覆盖时，雪球滚上去雪球的质量会加一，这一个区间里的雪也会被清空。刚开始每一个雪球的质量均为 $0$，而这 $Q$ 天里也没有再下雪。

你想问这 $Q$ 天结束后每个雪球的质量是怎样的。

## 说明/提示

#### 样例 1 解释

雪球初始位置为 $-2,3,5,8$，初始质量为 $0,0,0,0$。

- 第一天过后，雪球位置为 $0,5,7,10$，质量为 $2,2,2,2$。
- 第二天过后，雪球位置为 $-4,1,3,6$，质量为 $4,4,2,3$。
- 第三天过后，雪球位置为 $3,8,10,13$，质量为 $5,4,2,6$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（33 pts）：$N,Q \le 2000$。
- Subtask 2（67 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N,Q \le 2 \times 10^5$，$|A_i|,|W_j| \le 10^{12}$，$A_i<A_{i+1}$。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round B 雪玉的英文翻译 Snowball](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t2-en.pdf)。

## 样例 #1

### 输入

```
4 3
-2 3 5 8
2
-4
7```

### 输出

```
5
4
2
6```

## 样例 #2

### 输入

```
1 4
1000000000000
1000000000000
-1000000000000
-1000000000000
-1000000000000```

### 输出

```
3000000000000```

## 样例 #3

### 输入

```
10 10
-56 -43 -39 -31 -22 -5 0 12 18 22
-3
0
5
-4
-2
10
-13
-1
9
6```

### 输出

```
14
8
7
9
11
10
9
8
5
10```

# 题解

## 作者：xyin (赞：8)

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2021ho_b)

手玩样例，我们能发现一些特殊性质：

* 对于每一个雪球来说，能对它的质量产生贡献的位置和起来是一个**区间**。

顺着这个思路往下想，就能想到对每一个雪球维护一个能延伸到的**最远**的端点值（前提条件是对它的质量有贡献），最终的答案就是 $r_i-l_i$。

怎么维护这个端点值呢？

**解法一**：

考虑枚举天数，根据每一天的风力强度 $W_j$ 和上一次的坐标（设为 $last$）更新 $i$ 的端点值，最后直接输出就行。

记得在更新端点值的时候比较相邻两个雪球的端点值（看是否对 $i$ 产生贡献），判断是否能更新。

此时你有了一份 $O(nq)$ 的代码，得分 $33$ 分，[记录详情](https://www.luogu.com.cn/record/172635700)。

```cpp
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++)
	  last[i]=l[i]=r[i]=read();
	for (int i=1;i<=q;i++)
	  w[i]=read();
	for (int i=1;i<=q;i++)//枚举天数 
		for (int j=1;j<=n;j++){//枚举雪球 
	  	last[j]+=w[i];
	  	if (last[j]<l[j]){//如果新的位置小于左端点->“尝试 ”更新 
	  		if (j==1) l[j]=last[j];
	  		else if (last[j]>=r[j-1]) //能更新 
	  		  l[j]=last[j];
	  		else l[j]=r[j-1];//不能 
		  }
		else if (last[j]>r[j]){//如果新的位置大于右端点 
			if (j==n) r[j]=last[j];
			else if (last[j]<=l[j+1])//同上 
			  r[j]=last[j];
			else r[j]=l[j+1];//同上 
		}
	  }
	for (int i=1;i<=n;i++)
	  printf("%lld\n",r[i]-l[i]);
	return 0;
}
```

**解法二**：

考虑能不能优化上述方法，我们其实还能发现一些其它性质：

* 经过 $Q$ 天以后，雪球 $i$ 的运动路径其实是一条**折线**（不断做往复运动），折线的端点其实并没有 $Q$ 这么多。

我们尝试将折线的**几次**沿这直线的运动（不折返）**浓缩**为**一次**，直到它折返。

但这只是我们对常数的小优化，实际复杂度还是 $O(nq)$，别对它报什么期望。得分 $33$ 分，[记录详情](https://www.luogu.com.cn/record/172635333)能看出确实比之前快了不少（还多过了两个点），但还是 T 了很多点___*( ￣皿￣)/#____。

```cpp
//cnt 记录浓缩后的段数 
//tag的含义：1->此时正在处理>0的数，0->正在处理<=0的数 
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++)
	  last[i]=l[i]=r[i]=read();
	for (int i=1,x;i<=q;i++){
		x=read();
		if (i==1) {
			if (x>0) tag=1;
			else tag=0;
			tot+=x;
		}
	  	else if (x<=0){
	  		if (tag==1) 
			  w[++cnt]=tot,tag=0,tot=x;
	  		else tot+=x;
		  }
		else {
			if (tag==1) tot+=x;
			else w[++cnt]=tot,tag=1,tot=x;
		}
	}
	w[++cnt]=tot;
	for (int i=1;i<=cnt;i++)//这一部分与之前一样 
	{
		for (int j=1;j<=n;j++){
	  	last[j]+=w[i];
	  	if (last[j]<l[j]){
	  		if (j==1) l[j]=last[j];
	  		else if (last[j]>=r[j-1]) 
	  		  l[j]=last[j];
	  		else l[j]=r[j-1];
		  }
		else if (last[j]>r[j]){
			if (j==n) r[j]=last[j];
			else if (last[j]<=l[j+1])
			  r[j]=last[j];
			else r[j]=l[j+1];
		}
	  }
	}
	for (int i=1;i<=n;i++)
	  printf("%lld\n",r[i]-l[i]);
	return 0;
}
```

**解法三**：

终于来到了正解，我们考虑能优化哪一维，最终输出答案时你肯定必须枚举雪球（~~怎么都甩不开~~），所以只能在 $q$ 上下功夫。

观察数据范围 $1\le N,Q \le 2\times 10^5$，最终复杂度肯定是 $O(n\log q)$ 的，说实话，看到 $\log$ 你应该考虑考虑**二分**的。

我们来看看答案是否具有二分的性质：

* 端点值的更新肯定是单调的（只会扩张不会缩减）。

* 当某天雪球滚动完之后，若它和它**相邻**的雪球，在左（右）端点值更新时出现了**冲突**之后，该点的左（右）端点值再也不会更新，同样相邻点的右（左）端点值也再也不会更新。

* 当两个相邻的雪球出现冲突时，这段冲突区间到底是谁的贡献（根据风的**正负**）其实很好判断。

有了这几个性质就万事大吉了，我们直接二分冲突时间 $t$ 就行了，复杂度 $O(n\log q)$，得分 $100$ 分，[记录详情](https://www.luogu.com.cn/record/172603069)。

代码写得重复啰嗦，马蜂丑陋。

```cpp
int last,q,n,a[maxn],ans1,ans2;
int L[maxn],R[maxn],w[maxn];
bool check1(int x,int i){
	if (a[i-1]+R[x]>a[i]+L[x]) return 0;
	return 1;
}
bool check2(int x,int i){
	if (a[i+1]+L[x]<a[i]+R[x]) return 0;
	return 1;
}
int solve(int i,int k1,int k2){
	int ans=0;
	ans+=R[k2]-L[k1];
	if (i==1) ans+=-L[q];
	else if (k1<q&&w[k1+1]<0)
	  ans+=a[i]+L[k1]-a[i-1]-R[k1];
	if (i==n) ans+=R[q];
	else if (k2<q&&w[k2+1]>0)
	  ans+=a[i+1]+L[k2]-a[i]-R[k2];
	return ans; 
}
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++) 
	  a[i]=read();
	for (int i=1;i<=q;i++){
		w[i]=read();last+=w[i];
		R[i]=R[i-1];L[i]=L[i-1];
		if (last>R[i]) R[i]=last;
		else if (last<L[i]) L[i]=last;
	}
	for (int i=1;i<=n;i++){
		ans1=ans2=0;
		if (i!=1){
			int l=1,r=q;
			while (l<=r){
				int mid=(l+r)>>1;
				if (check1(mid,i)) 
				  l=mid+1,ans1=mid;
				else r=mid-1;
			}
		}
		if (i!=n){
			int l=1,r=q;
			while (l<=r){
				int mid=(l+r)>>1;
				if (check2(mid,i))
				  l=mid+1,ans2=mid;
				else r=mid-1;
			}
		}
		printf("%lld\n",solve(i,ans1,ans2));
	}
	return 0;
}
```

---

## 作者：Thunder_S (赞：4)

# Solution

$a_i$ 表示 $i$ 雪球的初始位置。

考虑两个相邻雪球 $i,j(i<j)$，如果雪球 $i$ 到达的最右边在雪球 $j$到达的最左边的右边，那么雪球 $i$ 之后无论怎么往右走都无法增加质量，因为雪球 $j$ 肯定在 $i$ 之前把雪清空。

有了这个想法，先求出相邻两个雪球间的距离 $dis_i$，然后从小到大排序。

对于每次移动，记录向左的总路程（记为 $L$）和向右的总路程（记为 $R$）以及每个雪球的最左和最右 $ml_i,mr_i$。

设一个指针 $j$ 指向当前最小的距离满足 $L+R<dis_j$，每次移动的时候更新每段到达的最左边和最右边。如果两个雪球出现了交集，也就是 $L+R\ge dis$，那右边( $y$ )雪球的最左边 = 左边( $x$ )雪球的最右边= $a_y-L$ 或者 $a_x+R$。根据当前移动是什么方向来判断，向右前者，向左后者。同时更新 $j$。

对于左右边界没更新的雪球，它们的最左和最右就分别是 $a_i-L,a_i+R$。

最后每个雪球的质量就为 $mr_i-ml_i$。

# Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 200005
using namespace std;
struct node
{
	int pos;
	ll dis;
}c[N];
int n,q,x,y;
ll w,p,ml,mr,a[N],l[N],r[N];
bool cmp(node x,node y) {return x.dis<y.dis;}
int main()
{
	memset(l,-1,sizeof(l));
	memset(r,-1,sizeof(r));
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	for (int i=1;i<n;++i)
		c[i].dis=a[i+1]-a[i],c[i].pos=i;
	sort(c+1,c+n,cmp);
	int j=1;
	for (int i=1;i<=q;++i)
	{
		scanf("%lld",&w);
		p+=w;
		if (p>0) mr=max(mr,p);
		else ml=max(ml,-p);
		while (j<n&&ml+mr>=c[j].dis)
		{
			x=c[j].pos;y=c[j].pos+1;
			if (p>0) l[y]=a[y]-ml;
			else l[y]=a[x]+mr;
			r[x]=l[y];
			++j;
		}
	}
	for (int i=1;i<=n;++i)
	{
		if (l[i]==-1) l[i]=a[i]-ml;
		if (r[i]==-1) r[i]=a[i]+mr;
	}
	for (int i=1;i<=n;++i)
		printf("%lld\n",r[i]-l[i]);
	return 0;
}
```



---

## 作者：Felix72 (赞：3)

我们换参考系，把雪球移动看成若干段积雪在移动，并且碰到一些位置就会堆积。

如果不考虑一段雪会消失，那么除最左最右两条射线的积雪外，每段积雪距离左右两个点的值组成的二元组是相等的，维护这个二元组，就可以整体修改。然后考虑计算每次减少的积雪量，并按照顺序求出消失的积雪段，可以通过在线段树上“锁点”的方式去除影响。最后特判只有一个雪球的情况即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
long long n, q, x[N], w[N];
long long ans[N], len[N], dl[N], dr[N];
int tot;
struct node {int len, id;} s[N];
inline bool cmp(node x, node y) {return x.len < y.len;}
struct Tree
{
	int rt, idx;
	struct SGT
	{
		int ls, rs, lck;
		long long sum, tag;
		#define ls(x) tree[x].ls
		#define rs(x) tree[x].rs
		#define sum(x) tree[x].sum
		#define lck(x) tree[x].lck
		#define tag(x) tree[x].tag
	}tree[N * 4];
	inline void pushdown(int now)
	{
		if(tag(now))
		{
			if(ls(now) && !lck(ls(now))) tag(ls(now)) += tag(now), sum(ls(now)) += tag(now);
			if(rs(now) && !lck(rs(now))) tag(rs(now)) += tag(now), sum(rs(now)) += tag(now);
			tag(now) = 0;
		}
	}
	inline void build(int &now, int l, int r)
	{
		if(!now) now = ++idx;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		if(l <= mid) build(ls(now), l, mid);
		if(mid < r) build(rs(now), mid + 1, r);
	}
	inline void insert(int now, int l, int r, int pos)
	{
		if(l == r) {lck(now) = true; return ;}
		pushdown(now);
		int mid = (l + r) >> 1;
		if(pos <= mid) insert(ls(now), l, mid, pos);
		if(mid < pos) insert(rs(now), mid + 1, r, pos);
	}
	inline void dance(int now, int l, int r)
	{
		if(l == r) return ;
		pushdown(now);
		int mid = (l + r) >> 1;
		if(l <= mid) dance(ls(now), l, mid);
		if(mid < r) dance(rs(now), mid + 1, r);
	}
	inline long long ask(int now, int l, int r, int pos)
	{
		if(l == r) return sum(now);
		pushdown(now);
		int mid = (l + r) >> 1;
		if(pos <= mid) return ask(ls(now), l, mid, pos);
		else return ask(rs(now), mid + 1, r, pos);
	}
};
Tree T1, T2;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i) cin >> x[i];
	for(int i = 1; i <= q; ++i) cin >> w[i];
	for(int i = 2; i <= n; ++i)
	{
		s[++tot].len = x[i] - x[i - 1];
		s[tot].id = i;
	}
	sort(s + 1, s + tot + 1, cmp);
	T1.build(T1.rt, 1, n);
	T2.build(T2.rt, 1, n);
	T1.insert(T1.rt, 1, n, 1);
	T2.insert(T2.rt, 1, n, n);
	long long fl = 0, fr = 0, cost = 0, p1 = 1, p2 = 1;
	for(int i = 1; i <= q; ++i)
	{
		long long num = ((w[i] > 0) ? w[i] : (-w[i]));
		if(w[i] < 0)
		{
			if(dr[1] > num) dr[1] -= num;
			else ans[1] += num - dr[1], dr[1] = 0;
			dl[n + 1] += num;
			fl += num;
			cost += max(0ll, (num - fr));
			while(p1 <= tot && s[p1].len <= cost)
			{
				ans[s[p1].id] += s[p1].len - (cost - max(0ll, (num - fr)));
				T1.insert(T1.rt, 1, n, s[p1].id), ++p1;
			}
			while(p2 <= tot && s[p2].len <= cost)
				T2.insert(T2.rt, 1, n, s[p2].id - 1), ++p2;
			T1.tree[T1.rt].tag += max(0ll, num - fr);
			T1.tree[T1.rt].sum += max(0ll, num - fr);
			fr -= num;
			fr = max(fr, 0ll);
		}
		if(w[i] > 0)
		{
			if(dl[n + 1] > num) dl[n + 1] -= num;
			else ans[n] += num - dl[n + 1], dl[n + 1] = 0;
			dr[1] += num;
			fr += num;
			cost += max(0ll, (num - fl));
			while(p1 <= tot && s[p1].len <= cost)
				T1.insert(T1.rt, 1, n, s[p1].id), ++p1;
			while(p2 <= tot && s[p2].len <= cost)
			{
				ans[s[p2].id - 1] += s[p2].len - (cost - max(0ll, (num - fl)));
				T2.insert(T2.rt, 1, n, s[p2].id - 1), ++p2;
			}
			T2.tree[T2.rt].tag += max(0ll, num - fl);
			T2.tree[T2.rt].sum += max(0ll, num - fl);
			fl -= num;
			fl = max(fl, 0ll);
		}
	}
	T1.dance(T1.rt, 1, n);
	T2.dance(T2.rt, 1, n);
	if(n == 1)
	{
		cout << (ans[1] + T1.ask(T1.rt, 1, n, 1) + T2.ask(T2.rt, 1, n, 1)) / 2 << '\n';
		return 0;
	}
	for(int i = 1; i <= n; ++i) cout << ans[i] + T1.ask(T1.rt, 1, n, i) + T2.ask(T2.rt, 1, n, i) << '\n';
	return 0;
}
/*
2 2
-10 10
-5 5

4 3
-2 3 5 8
2 -4 7

1 4
1000000000000
1000000000000 -1000000000000 -1000000000000 -1000000000000

10 10
-56 -43 -39 -31 -22 -5 0 12 18 22
-3 0 5 -4 -2 10 -13 -1 9 6
*/
```

---

## 作者：7KByte (赞：3)

提供一个好想的方法。

观察到对于第 $i$ 个雪球，跨过第 $i-1$ 或第 $i+1$ 个雪球的贡献为零。

所以我们只用考虑相邻两个雪球之间的一段，多少属于左端点，多少属于右端点。

断点具有单调性，我们直接二分答案即可。

时间复杂度 $\mathcal{O}(N\log Q)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define int long long
using namespace std;
int n,m,ll[N],rr[N],a[N],ans[N];
void calc(int x,int len){
	if(ll[m]+rr[m]<=len){ans[x]+=rr[m],ans[x+1]+=ll[m];return ;}
	int l=1,r=m,ed=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ll[mid]+rr[mid]>len)ed=mid,r=mid-1;
		else l=mid+1;
	}
	if(ll[ed]==ll[ed-1])ans[x+1]+=ll[ed],ans[x]+=len-ll[ed];
	else ans[x]+=rr[ed],ans[x+1]+=len-rr[ed];
}
signed main(){
	scanf("%lld%lld",&n,&m);
	rep(i,1,n)scanf("%lld",&a[i]);
	int cur=0;
	rep(i,1,m){
		int x;scanf("%lld",&x);cur+=x;
		ll[i]=max(ll[i-1],-cur);
		rr[i]=max(rr[i-1],cur);
	}
	ans[1]+=ll[m];ans[n]+=rr[m];
	rep(i,1,n-1)calc(i,a[i+1]-a[i]);
	rep(i,1,n)printf("%lld \n",ans[i]);
	return 0;
} 
```

---

## 作者：喵仔牛奶 (赞：2)

# Solution

记号：记 $s_i$ 是 $i$ 时刻及以前 $w$ 的总和，即 $i$ 时刻的偏移量。记 $p,q$ 是 $\max s_i,-\min s_i$，记当前向左 / 右的最大偏移量。

我们发现雪球的相对位置是不变的，我们考虑两个雪球之间雪的归属情况单独考虑。设两个雪球是 $i,i+1$，容易发现若 $p+q<i$，则 $[a_i,a_i+p]$ 属于 $i$，$[a_{i+1}-q,a_{i+1}]$ 属于 $i+1$。否则两边相交，且之后的移动对 $i,i+1$ 之间的雪**没有影响**（因为以及用完了）。

取出所有 $(i,i+1)$ 这种空隙，按长度从小到大排序，每次处理相交的雪即可。

时间复杂度 $\mathcal{O}(\text{sort}(n))$，拿个基数排序啥的就可以线性。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, m, x, s, t, p, q, a[N], L[N], R[N];
	vector<pii> b;
	int main() {
		cin >> n >> m;
		REP(i, 1, n) cin >> a[i], L[i] = R[i] = 1e18;
		REP(i, 2, n) b.pb(a[i] - a[i - 1], i);
		sort(b.begin(), b.end());
		REP(i, 1, m) {
			cin >> x, s += x;
			if (s > 0) p = max(p, s);
			else q = max(q, -s);
			while (t < b.size() && p + q >= b[t].fi) {
				int y = b[t].se, x = y - 1;
				R[x] = L[y] = (s < 0 ? a[x] + p : a[y] - q), t ++;
			}
		}
		REP(i, 1, n) {
			if (L[i] == 1e18) L[i] = a[i] - q;
			if (R[i] == 1e18) R[i] = a[i] + p;
			cout << R[i] - L[i] << '\n';
		}
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：sndd (赞：1)

题目连接->[P7405](https://www.luogu.com.cn/problem/P7405)

双倍经验->[ AT_joi2021ho_b](https://www.luogu.com.cn/problem/AT_joi2021ho_b)

## 思路

容易发现每个雪球都可以形成一段区间，区间端点 $R-L$ 的值即为贡献。

于是维护区间端点，每次检查位置是否到了已覆盖区间。

时间复杂度 $O(nq)$，能拿 $33$ 分。

# 优化

因为要求每个点的贡献，所以避免不了枚举 $n$，考虑优化 $q$。

雪球间位置应是两两相对静止，影响区间端点的只有**相邻两区间**的**冲突**。

于是可以**二分**求得两端冲突时间，复杂度 $O(n \log n)$。

具体做法：

*  预处理每个时间的两端点最远相对位移。
*  枚举 $n$，分别用二分求出两端端点的冲突时间。
*  根据冲突时间 $O(1)$ 查询答案。

注：这里查询的时候要看看是谁先覆盖到的。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;

int n,Q;
int pos[N];
int ll[N],rr[N];	//两端点每个时间相对最远位移 
int ans1,ans2;		//分别记录两端点冲突时间 

bool check1(int num,int t){
	return (pos[num]+ll[t]<pos[num-1]+rr[t]);
}
bool check2(int num,int t){
	return (pos[num]+rr[t]>pos[num+1]+ll[t]);
}

int solve(int num,int l,int r){			//O(1)查答案 
	if(l==0) l=pos[num]+ll[Q];
	else l=min(pos[num-1]+rr[l],pos[num]+ll[l-1]);		//这里看看是谁先覆盖然后再加贡献 
	if(r==0) r=pos[num]+rr[Q];
	else r=max(pos[num+1]+ll[r],pos[num]+rr[r-1]);
	return r-l;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++) cin>>pos[i];
	int now=0;
	for(int i=1,W;i<=Q;i++){			//预处理相对位移 
		cin>>W;
		now+=W;
		ll[i]=ll[i-1],rr[i]=rr[i-1];
		if(now<ll[i]) ll[i]=now;
		if(now>rr[i]) rr[i]=now;
	}
	for(int i=1;i<=n;i++){
		ans1=ans2=0;			//二分冲突时间 
		if(i!=1){
			int l=1,r=Q;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check1(i,mid)){
					ans1=mid;
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
		}
		if(i!=n){
			int l=1,r=Q;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check2(i,mid)){
					ans2=mid;
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
		}
		cout<<solve(i,ans1,ans2)<<"\n";
	}
	return 0;
}
```

---

## 作者：lzdll (赞：1)

## 思路

可以想到，雪球的相对位置是不变的，所以雪球 $i$，雪球 $i+1$ 之间的区域只可能加到雪球 $i$ 和 $i+1$ 的质量上。

我们可以 $O(n)$ 求出第 $i$ 个风刮完之后，每一个雪球向左或向右最多能滚多远。

然后枚举 $\left[1,n-1\right]$ 之间的每一个雪球。

如果风刮完之后，第i个雪球向右滚的长度加上第 $i+1$ 个雪球向左滚的长度不超过 $i$ 和 $i+1$ 之间的长度，那么它们之间互不影响。

否则的话，说明它们之间有影响。我们要求出使它们能够互相影响的第一个风的编号，使用二分。
具体看代码。

## 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 200005
#define R(x) x=read()
#define int long long
using namespace std;

inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<3)+(x<<1)+(e^'0');
		e=getchar();
	}
	return x*y;
}
int n,q,x[N];
int l[N],r[N];
int ans[N];
int nw,a[N];
signed main() {
	R(n),R(q);// 读入qwq
	for(int i=1; i<=n; ++i) {
		R(x[i]);
	}
	for(int i=1; i<=q; ++i) {
		R(a[i]);
		nw+=a[i];
		l[i]=min(l[i-1],nw),r[i]=max(r[i-1],nw);//计算每一个雪球向左或向右最多能滚多远
		//向左滚取长度的时候要变号 
	}
	int L=l[q],R=r[q];
	ans[1]+=(-L)/*变号*/,ans[n]+=R;
	//第一个雪球向左滚不受任何影响，最后一个雪球向右滚同理  
	
	for(int i=1;i<n;++i){
		//x[i+1]-x[i]为区间长度 
		if(R-L<=x[i+1]-x[i]) {//i,i+1互不影响 
			ans[i]+=R,ans[i+1]+=(-L);
		} else {
			int ll=1,rr=q,mid,midd=q;//因为l,r都被定义过了,这里用ll、rr表示 
			while(ll<=rr) {//二分 
				mid=ll+rr>>1; 
				if(r[mid]-l[mid]<=x[i+1]-x[i]) {
					ll=mid+1;
				} else {
					midd=mid;
					rr=mid-1;
				}
			}
			if(a[midd]>0) {//向右 
				ans[i]+=(x[i+1]-x[i]+l[midd-1]);
				ans[i+1]+=(-l[midd-1]) ;
			} else {//向左 
				ans[i]+=r[midd-1];
				ans[i+1]+=(x[i+1]-x[i]-r[midd-1]);
			}
		}
	}
	for(int i=1; i<=n; ++i) {
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：masonpop (赞：1)

很好的思维题。~~但是被我暴力破解了~~。

考虑一个雪球向左向右滚到的最大范围。显然，如果相邻雪球这样的区间都不相交的话，答案就是区间长度。

否则，我们就需要判断相交的这段，是哪边的雪球先滚到。首先，可以二分出两边区间最后一次不交的时刻，假设在第 $x$ 次操作。然后，只需判断第 $x+1$ 次操作，区间的哪一侧扩张了即可。

复杂度 $O(n\log q)$。[代码](https://www.luogu.com.cn/paste/icfx1bix)。

---

## 作者：xs_siqi (赞：1)

我们发现，由于所有雪球的速度方向是一致的，所以相对位置不变。

根据这个，我们发现按 $x$ 排序后，只有第一个雪球可以无限向左或者最后一个雪球无限向右，其它雪球都是有限制区间的。限制区间长就是 $dis_i=x_i-x_{i-1}$。

根据我们上面发现的性质，我们可以记录一个 $maxl$ 和 $maxr$，分别记录雪球最左走了多远，最右走了多远。当 $maxr+maxl\ge dis_i$ 时，说明这个区间左边的那个雪球已经走了 $maxr$ 的路程，右边的雪球已经走了 $maxl$ 的路程，这两段路径已经相交了，这段区间的雪全没了，那么这个区间就没有意义了。

然后容易想到这个东西可以用优先队列来维护，每次判断最小的是否满足即可。所有元素最多被判断一次，因此复杂度是 $O(n\log n)$ 的。

写的时候注意一件事情：一开始雪球在的地方是有雪的，换句话说就是雪球初始质量为 $0$。这个东西特判一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
const int inf=9000000000000000000;
int n,m,x[maxn],w[maxn],Q,maxl,maxr,now,ans[maxn][2];
bool fl,fll;
struct node{
	int x,id;
	bool friend operator < (node x,node y){return x.x>y.x;}}u;
priority_queue<node> q;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&x[i]);
	for(int x,i=1;i<=m;i++){
		scanf("%lld",&x);
		if(x)w[++Q]=x;}
	if(w[1]==0)fll=1;
	if(w[1]>0)w[1]--,fl=1;
	else w[1]++;
	x[0]=-inf,x[n+1]=inf;
	for(int i=1;i<=n+1;i++)q.push(node{x[i]-x[i-1]-1,i-1});
	for(int i=1;i<=Q;i++){
		now+=w[i];
		if(now<0)maxl=max(maxl,-now-(fl==1));
		if(now>0)maxr=max(maxr,now-(fl==0));
		u=q.top();
		while(maxl+maxr>=u.x){
			if(w[i]<0ll)ans[u.id][0]=u.x-maxr,ans[u.id][1]=maxr;
			else ans[u.id][0]=maxl,ans[u.id][1]=u.x-maxl;
			q.pop(),u=q.top();}}
	while(!q.empty()){
		u=q.top(),q.pop();
		if(u.id!=n)ans[u.id][0]=maxl;
		if(u.id!=0)ans[u.id][1]=maxr;}
	for(int i=1;i<=n;i++)
		printf("%lld\n",fll?0:ans[i-1][0]+ans[i][1]+1);
	return 0;}

```


---

## 作者：djh0314 (赞：1)

[**洛谷**](https://www.luogu.com.cn/problem/P7405)。

## 题意

应该好理解的。

## 分析

我们的所有雪球在同一时间之间的距离都是相同的，因此一段雪，要么是它左侧的第一个所取，要么右侧第一个所取，要么不被取，并且，我们每一个雪球所占有的雪是连续的一段。

我们令 $L_i$ 表示第 $i$ 步前所能走的最左点，$R_i$ 表示第 $i$ 步前所能走的最后点。

我们分析两个雪球初始位之间的雪地的分割情况，两点间距离为 $len$：

1. 左侧与右侧并不相接，即 $R_m-L_m\le len$，那么左侧的雪球就可以增加 $\left | L_m \right | $，右侧雪球就可以增加 $R_m$。
2. 会有某一段收到两个争夺，那么，我们先找到最大的 $k$，使得 $R_k-L_k\le len$，先将这一段分割，接着，假如说这一步是向左，那么这一段就是属于右侧的，假如说这一步是向右，那么这一步就属于左侧，因为这一步过后，这一段必然会被某一端所占领。

~~~cpp
a[0]=-INF,a[n+1]=INF;
int mx=lenth[m];
for(int i=1; i<=n+1; ++i) {
	int len=a[i]-a[i-1];
	if(len>=mx) {
		ans[i]+=abs(L[m]);
		ans[i-1]+=abs(R[m]);
	} else {
		int T=upper_bound(lenth+1,lenth+m+1,len)-lenth-1;
		ans[i]+=abs(L[T]),ans[i-1]+=abs(R[T]);
		if(b[T+1]>0) ans[i-1]+=len-lenth[T];
		else ans[i]+=len-lenth[T];
	}
}
~~~



---

## 作者：1234567890sjx (赞：0)

大水题。但是水平就是不够，就是没能写出来啊。

~~写出来就解锁新成就：AK 一次 CSP-S 模拟赛~~

容易发现初始 $i$ 点和 $i+1$ 点之间的地方只有 $i$ 和 $i+1$ 才可能清扫到。因此考虑计算相邻两个点 $i$ 和 $i+1$ 对答案的贡献。

因此分类讨论：如果 $i$ 和 $i+1$ 之间的空隙没有被用完那么就是每一边走了多少就是多少，否则二分出最后一次对区间有贡献的操作然后计算一下即可。时间复杂度为  $O(n\log n)$。

```cpp
const int N=1000100,mod=998244353;
int zuo[N],you[N],res[N],a[N];
signed main(){
	int n,m;cin>>n>>m;
	F(i,1,n)cin>>a[i];
	int p=0;
	F(i,1,m){
		int x;cin>>x;
		p+=x;
		zuo[i]=max(zuo[i-1],-p);
		you[i]=max(you[i-1],p);
	}
	res[1]+=zuo[m];
	res[n]+=you[m];
	F(i,1,n-1){
		if(zuo[m]+you[m]<=a[i+1]-a[i]){
			res[i]+=you[m];
			res[i+1]+=zuo[m];
		}else{
			int l=1,r=m,best=m;
			while(l<=r){
				int mid=l+r>>1;
				if(zuo[mid]+you[mid]>a[i+1]-a[i])
					best=mid,r=mid-1;
				else
					l=mid+1;
			}
			if(zuo[best-1]==zuo[best]){
				res[i+1]+=zuo[best];
				res[i]+=a[i+1]-a[i]-zuo[best];
			}else{
				res[i]+=you[best];
				res[i+1]+=a[i+1]-a[i]-you[best];
			}
		}
	}
	F(i,1,n)
		cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
看完题目，不难发现对于一个位置的雪，只有可能被它初始位置相邻的两个雪球所合并，因为雪球是一起移动的，如果当前位置被其他雪球覆盖，那必定先前被其他节点覆盖。

于是我们考虑二分，求一个前缀和，并求当前位置前后的最远点，二分**当前雪球前面的雪堆恰好不被前面的雪球覆盖（就是不交叉）**，对应的 $q_i$ 值。

但这样可能会有一段区间取不到，于是便看 $q_{i+1}$ 是减少还是增加，即可判断是属于前还是后（根据前面二分的定义，必然能保证这一段的雪球是取完的，$i=n$ 时除外）。

思想比较抽象，请读者结合代码理解。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5000005],w[5000005],maxn[5000005],minn[5000005],ans[5000005],n,q,l,r,mid,res;
bool check(long long x,long long i)
{
	if(maxn[x]-minn[x]<=a[i+1]-a[i]) return 1;
	else return 0;
}
int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=q;i++) 
    {
        scanf("%lld",&w[i]);
        w[i]+=w[i-1];
        maxn[i]=max(maxn[i-1],w[i]);
        minn[i]=min(minn[i-1],w[i]);
    }
    for(int i=1;i<=n;i++)
    {
        l=1,r=q,res=0;
        if(i==n)
        {
            ans[i]+=maxn[q];
            continue;
        }
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid,i)) l=mid+1,res=mid;
            else r=mid-1;
        }
        if(res==n) ans[i]+=maxn[res],ans[i+1]-=minn[res];
        else
        {
            ans[i]+=maxn[res],ans[i+1]-=minn[res];
            if(maxn[res]==maxn[res+1]) ans[i+1]+=min(a[i+1]-a[i]-maxn[res]+minn[res],minn[res]-minn[res+1]);
            else if(minn[res]==minn[res+1])ans[i]+=min(a[i+1]-a[i]-maxn[res]+minn[res],maxn[res+1]-maxn[res]);
        }
    }
    ans[1]-=minn[q];
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：Msents (赞：0)

可以很容易想到四条性质：

- 一个雪球滚起的雪的范围是连续的，也就是一个区间。
- 雪球的大小随着天数的增加只会增大，滚起雪的区间也只会左右延长。
- 因为这些雪球都同时向左向右移动一段距离，所以不会出现任何左边的雪球滚起的雪在任何右边的雪球滚起的雪右边，相反的类似。
- 如果这些雪球左右移动的距离小到一定程度，它们滚起雪的区间不会相碰，那么雪球的答案就是经过的区间的大小，而它们的答案都是相同的，同样它们延长出去的左右距离都是一样的。

如果中途有些雪球的区间相碰了，因为区间只会左右延长，不会缩小，两个区间相碰的两个端点就固定在一个位置了，因为每次所有区间右端点或者左端点中只有一者可能会延长，根据风的方向可以轻松得出这个位置。

显然的，两个雪球之间的相对距离越短，它们的区间左右端点就会越先被固定。

若向右延长出去的最远距离加上向左延长出去的最远距离大于等于了相对距离，那这两个雪球的左右端点就固定住了。

于是可以将两两雪球的相对距离排序，中途从小到大更新。

剩下没有更新到的直接设成最远的

这题还是挺水的，想想很快就能做出来了。

偷懒打了优先队列，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=200100;
int n,q,a[MaxN+1],c[MaxN+1],la[MaxN+1],ra[MaxN+1];
bool vstl[MaxN+1],vstr[MaxN+1];
struct Comparer{
	bool operator()(pair<int,int>&a,pair<int,int>&b)const{
		return a.second>b.second;
	}
};
void Solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)c[i]=a[i]-a[i-1];
	c[1]=LLONG_MAX;
	c[n+1]=LLONG_MAX;
	priority_queue<pair<int,int>,vector<pair<int,int> >,Comparer>que;
	for(int i=1;i<=n;i++)que.emplace(i,c[i+1]);
	int now=0,l=0,r=0;
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		now+=x;
		int rawL=l,rawR=r;
		l=max(l,-now);
		r=max(r,now);
		while(!que.empty()&&l+r>=que.top().second){
			int id=que.top().first,dis=que.top().second;
			que.pop();
			if(now>0){
				ra[id]=dis-rawL;
				la[id+1]=rawL;
			}else{
				ra[id]=rawR;
				la[id+1]=dis-rawR;
			}
			vstl[id+1]=true;
			vstr[id]=true;
		}
	}
	for(int i=1;i<=n;i++)if(!vstl[i])la[i]=l;
	for(int i=1;i<=n;i++)if(!vstr[i])ra[i]=r;
	for(int i=1;i<=n;i++)cout<<la[i]+ra[i]<<'\n';
}
#undef int
int main(){
//	freopen("snowball.in","r",stdin);
//	freopen("snowball.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int T;
//	cin>>T;
//	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：0)

注意到最终每个雪球对答案的贡献一定是一个区间。

注意到所有雪球的每一时刻的区间左右端点单调递增。

考虑第 $i$ 个雪球分别向左右滚到的第一个已经被别的雪球滚到过的位置，这个位置一定分别被第 $i-1$ 和 $i+1$ 个雪球滚到过，于是我们只需要对第 $i$ 个雪球考虑 $i-1$ 和 $i+1$。

对于第 $i$ 个雪球，记 $p_i$ 为第 $i$ 时刻的位置，我们需要分别找到第一个 $j$ 使得 $p_j$ **在此时**被左区间覆盖过，$p_j$ 被右区间覆盖过，相当于是找这样一个**瓶颈**。

二分即可。

---

## 作者：LiveZoom (赞：0)

### Description

[link](https://www.luogu.com.cn/problem/P7405)

### Solution

容易发现能对雪球产生贡献的雪地一定是连续的，那么我们就可以对于雪球 $i$，二分能对于它产生贡献的雪地的左端点，右端点就是雪球 $i$ 能到的最大的长度和 $i+1$ 的左端点的较小值。

考虑如何二分。假设当前二分雪球 $x$ 的左端点，二分的范围就是 $a[x-1]\sim a[x]$，如果当前的答案是 $k$，那么我们就再用一个二分找到雪球 $i$ 第一次经过 $k$ 的时间，那么只要看 $i-1$ 在这个时间之前（包括这个时间）有没有到过 $k$，如果到过 $k$ 那么就不行，而没到过就表示 $k$ 可行。

时间复杂度：$O(n\log q\log 10^{12})$，这东西显然跑不满，所以能 比 较 快 地通过。

貌似正解是线性的，wtcl/kk

### Code

```cpp
#include <bits/stdc++.h>

#define int long long
#define db(x) cerr << #x << '=' << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define dbg debug("*** Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)

using namespace std;

const int kMaxN = 2e5 + 5, kInf = 1e18;

int n, q;
int a[kMaxN], w[kMaxN], mx[kMaxN], mi[kMaxN], ml[kMaxN], mr[kMaxN];

bool checkl(int x, int kk) {
  int L = -1, R = q + 1, res = kInf;
  while (L + 1 < R) {
    int mid = (L + R) >> 1;
    if (mi[mid] <= kk - a[x]) R = res = mid;
    else L = mid;
  }
  if (res == kInf) return 0;
  if (a[x - 1] + mx[res] > kk) return 0;
  else return 1;
}

int getl(int x) {
  int L = a[x - 1] - 1, R = a[x] + 1, res = a[x];
  while (L + 1 < R) {
    int mid = (L + R) >> 1;
    if (checkl(x, mid)) R = res = mid;
    else L = mid;
  }
  return res;
}

signed main() {
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  a[0] = -kInf, a[n + 1] = kInf;
  int cur = 0;
  for (int i = 1; i <= q; ++i) {
    cin >> w[i]; cur += w[i];
    mx[i] = max(mx[i - 1], cur), mi[i] = min(mi[i - 1], cur);
  }
  for (int i = 1; i <= n; ++i) {
    ml[i] = getl(i);
  }
  ml[n + 1] = kInf;
  for (int i = 1; i <= n; ++i) {
    mr[i] = min(ml[i + 1], a[i] + mx[q]);
    cout << mr[i] - ml[i] << endl;
  }
  return 0;
}
```

---

## 作者：tyukp233 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2021ho_b)

***

### 定义：
$$pos_i=\sum_{k=1}^{i}W_k$$
$$L_i=\min_{0\le k\le i}pos_k$$
$$R_i=\max_{0\le k\le i}pos_k$$
$$X_i=A_{i+1}-A_i$$
其中 $X_i$ 为初始位置为 $A_i$ 与 $A_{i+1}$ 的雪球间隔的大小，后文对当前雪球均只考虑该间隔。以 $m$ 代指题中的 $Q$。

***

### 本题从间隔入手。

#### 考虑雪球间隔足够大的时候，

手动模拟可知，雪球 $i$ 滚过的区域 $[A_i+L_m,A_i+R_m]$，此时 $X_i\ge R_m-L_m$。

#### 当间隔较小时，

注意到雪球之间相对位置不变，故当前雪球能够到达的区域，若被不相邻的雪球滚过，则一定被相邻的雪球滚过。下面只考虑相邻雪球的影响。

雪球 $i$ 会在某一次移动后到达相邻雪球滚过的区域，记该次移动为第 $t$ 次，则 $R_{t-1}-L_{t-1}<X_i$ 且 $R_t-L_t\ge X_i$。

由定义，$t$ 关于 $X_i$ 是不减的，我们可以对 $X_i$ 进行排序，然后枚举 $t$。

令 $W_t>0$，我们有 $R_t> R_{t-1}$。此前雪球 $i$ 滚过 $[A_i,A_i+R_{t-1}]$ 的区域，雪球 $i+1$ 滚过 $[A_{i+1}+L_{t-1},A_{i+1}]$ 的区域，两区域不相交。故雪球 $i$ 新增的区域为 $[A_i+R_{t-1},A_{i+1}+L_{t-1}]$。

即雪球 $i$ 在间隔 $X_i$ 中占有 $[A_i,A_{i+1}+L_{t-1}]$，而雪球 $i+1$ 占有 $[A_{i+1}+L_{t-1},A_{i+1}]$。将该部分加到答案里。

$W_i<0$ 的情况同理。

另外，对于雪球 $1$ 和雪球 $n$，我们额外计算 $L_m$ 和 $R_m$ 即可。

***

该算法的时间复杂度为 $O(n\log n+m)$，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
int n,m,pt=1;
ll pos=0;
ll L,R;
ll a[N],b[N];
pair<ll,int> mid[N];
ll ans[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<n;i++)mid[i]={a[i+1]-a[i],i};
	sort(mid+1,mid+n);
	for(int i=1;i<=m;i++){
		pos+=b[i];
		L=min(L,pos);
		R=max(R,pos);
		while(pt<n&&mid[pt].first<=R-L){
			if(b[i]>0){
				ans[mid[pt].second+1]+=(-L);
				ans[mid[pt].second]+=(mid[pt].first+L);
			}else {
				ans[mid[pt].second]+=R;
				ans[mid[pt].second+1]+=(mid[pt].first-R);
			}
			pt++;
		}
	}
	while(pt<n){
		ans[mid[pt].second]+=R;
		ans[mid[pt].second+1]+=(-L);
		pt++;
	}
	ans[1]+=(-L);
	ans[n]+=R;
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：P7GAB (赞：0)

### 思路

由于雪球之间的相对位置是不会改变的，所以对于一个雪球，越过相邻的雪球的初始位置一定不会令其变大。

如果雪球的滚动范围没有交集，答案显然就是区间长度。但如果有了交集，我们必须判断哪个雪球先滚到，一个区间便分为了分属左右两雪球的两个区间，于是就要找出两边最后一次不交的那个断点。

由于断点具有单调性，直接二分启动。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=2e5+5;
ll n,q;
ll a[maxn],w[maxn];
ll L[maxn],R[maxn],ans[maxn];
void solve(ll x,ll len) {
	if(L[q]+R[q]<=len) {
		ans[x]+=R[q];
		ans[x+1]+=L[q];
		return;
	}
	ll l=1,r=q;
	while(l<r) {
		ll mid=(l+r)/2;
		if(L[mid]+R[mid]>len)
			r=mid;
		else
			l=mid+1;
	}
	if(L[l]==L[l-1]) {
		ans[x]+=len-L[l];
		ans[x+1]+=L[l];
	} else {
		ans[x]+=R[l];
		ans[x+1]+=len-R[l];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(ll i=1; i<=n; i++)
		cin>>a[i];
	ll sum=0;
	for(ll i=1; i<=q; i++) {
		cin>>w[i];
		sum+=w[i];
		L[i]=max(L[i-1],-sum),R[i]=max(R[i-1],sum);
	}
	ans[1]+=L[q],ans[n]+=R[q];
	for(ll i=1; i<n; i++)
		solve(i,a[i+1]-a[i]);
	for(ll i=1; i<=n; i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

